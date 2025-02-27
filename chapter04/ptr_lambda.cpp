#include <iostream>
#include <vector>
#include <memory>
using namespace std;
/*
C++11 introduced three main types of smart pointers: std::unique ptr,
std::shared ptr, and std::weak ptr. These smart pointers provide varying ownership
models and are designed to cover different memory management scenarios. To understand their
value, it is important to explore their characteristics, use cases, and how they relate to the
concept of ownership.
*/

class MyClass
{
public:
    void greet() const { std::cout << "Hello, World!" << std::endl; }
};
// where single pointer is used by single instance
void using_unique_ptr()
{
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();
    // ptr1 owns MyClass
    ptr1->greet();

    // Ownership can be transferred, but not copied
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
    // Ownership transferred to ptr2

    // ptr1 is now null (nullptr) and cannot be used
    ptr2->greet(); // ptr2 owns MyClass

    // When ptr2 goes out of scope, MyClass is destroyed automatically
}

// Where multiple objects can point to the same pointer, shared ownership
class MyClass2
{
public:
    void greet() const { std::cout << "Hello from shared_ptr" << std::endl; }
};

void using_shared_ptr()
{
    // ptr1 owns MyClass2,
    // make_shared creates sharable pointer where multiple object can use, will disposed ones it's not used by any instances
    std::shared_ptr<MyClass2> ptr1 = std::make_shared<MyClass2>();
    std::shared_ptr<MyClass2> ptr2 = ptr1;
    ptr1->greet();
    ptr2->greet();
    //// When both ptr1 and ptr2 go out of scope, MyClass is destroyed automatically
}

void using_weak_ptr()
{
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = ptr1;

    // Lock the weak_ptr to access the object
    if (auto tempPtr = weakPtr.lock())
    {
        tempPtr->greet();
        // Object is still alive
    }
    else
    {
        std::cout << "Object no longer exists." << std::endl;
    }
    // Object is deleted here because ptr1 goes out of scope
    ptr1.reset();

    // Now the object is deleted, and weakPtr.lock() will return nullptr
    if (auto tempPtr = weakPtr.lock())
    {
        tempPtr->greet();
        // This won't execute, object is deleted
    }
    else
    {
        std::cout << "Object has been deleted." << std::endl;
    }
}

void using_lambda_expressions()
{
    int x = 5, y = 10;
    // 1) Define a lambda that adds two integers
    auto add = [](int a, int b) -> int
    {
        return a + b;
    };
    // Call the lambda and print the result
    std::cout << "Sum: " << add(x, y) << std::endl; // Output: Sum: 15

    // 2) passing by ref
    vector<int> vec = {1, 2, 3, 4, 5, 6};
    for (auto &x : vec)
    {
        x++;
        cout << x << " ";
    }
    cout << endl;
    auto addOne = [&](int a) -> int
    { return a + 1; };

    for (auto x : vec)
    {
        cout << addOne(x) << " ";
    }
    // 3) capture all by value
    int a = 5, b = 10;
    auto addByValue = [=]()
    {
        std::cout << "Sum by value: " << a + b << std::endl;
        // Captures 'a' and 'b' by value
    };

    // 4) Capture all by reference
    auto addByReference = [&]()
    {
        a = 100; // Modifies 'a' in the outer scope
        std::cout << "Sum by reference: " << a + b << std::endl;
    };

    addByValue();
    // Output: Sum by value: 15
    addByReference();
    // Output: Sum by reference: 200
    std::cout << "Updated a: " << a << std::endl;

    // 5) Explicit Capture for Individual Variables byvalue and byref
    //  Capture 'a' by value, 'b' by reference
    a = 5, b = 10;
    auto add_byVal_byRef_explicityly = [a, &b]()
    {
        std::cout << "Sum: " << a + b << std::endl; // 'a' is captured by value, 'b' by reference
        b = 20;                                     // Modifies the original 'b'
    };
    add_byVal_byRef_explicityly();
    // Output: Sum: 15
    std::cout << "Updated b: " << b << std::endl; // Output: Updated b: 20

    // 6) We ca set the default capture mode except specific variable
    a = 5, b = 10;
    int c = 15;
    auto add_all_beref_except_c = [&, c]()
    {
        std::cout << "Sum: " << a + b + c << std::endl;
        // Default capture by reference, except for 'c' captured by value
        // Modify 'a' and 'b' (they are captured by reference)
        a = 100;
        b = 200;
    };
    add_all_beref_except_c();
    std::cout << "Updated a: " << a << ", Updated b: " << b << std::endl;
    // Output: Updated a: 100, Updated b: 200
    std::cout << "Original c: " << c << std::endl;
    // Output: Original c: 15 (unchanged)

    // 7) Return Type Deduction and Explicit Return Type
    // means return explicit datatype regardless the type of the parameters
    auto add_explicit_return = [](int x, int y) -> double { return x + y + 0.5; };
    std::cout << "Result: " << add_explicit_return(5, 10) << std::endl;
    // Output: Result: 15.5

}

int main()
{
    // using_unique_ptr();
    // using_shared_ptr();
    // using_weak_ptr();
    using_lambda_expressions();
    return 0;
}