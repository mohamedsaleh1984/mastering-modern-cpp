#include <iostream>
using namespace std;
// General template
template <typename T>
T getMax(T a, T b)
{
    return (a > b) ? a : b;
}
// Template specialization for char
template <>
char getMax<char>(char a, char b)
{
    cout << "Specialized function for char!" << endl;
    return (a > b) ? a : b;
}
/*********************************************************************/
// Specialized Template.

// General template
template <typename T>
class Printer
{
public:
    void print(T value)
    {
        cout << "Generic print: " << value << endl;
    }
};
// Template specialization for int
template <>
class Printer<int>
{
public:
    void print(int value)
    {
        cout << "Specialized print for int: " << value << endl;
    }
};

// Class template with two type parameters, as in keyvalue pair
template <typename T, typename U>
class Pair
{
private:
    T first;
    U second;

public:
    Pair(T a, U b) : first(a), second(b) {}
    void print()
    {
        cout << "First: " << first << ", Second: " << second << endl;
    }
};
/************************************* Variadic Templates with function *******************************/
// allows a function/class to accept any number of argument
template <typename T>
void print(T t)
{
    cout << t << endl;
    // Base case: print a single argument
}
template <typename T, typename... Args>
void print(T t, Args... args)
{
    cout << t << " "; // Print the first argument
    print(args...);   // Recursively call print for the remaining
}
/************************************* Variadic Templates with classes *******************************/
template <typename... Args>
class Storage
{
private:
    tuple<Args...> data;
    // Tuple to store multiple values of different types
public:
    Storage(Args... args) : data(args...) {}
    void print()
    {
        printHelper(data);
        // Call helper function to print the stored values
    }
    // Helper function for recursion
    void printHelper(const tuple<> &t) {}

    // Base case for empty tuple
    template <std::size_t I = 0, typename placeHolder>
    void printHelper(const placeHolder &t)
    {
        if constexpr (I < std::tuple_size<placeHolder>::value)
        {
            cout << get<I>(t) << " ";
            printHelper<I + 1>(t);
            // Print the I-th element of the
            // Recursively call for next element
        }
    }
};

/*********************************Specialization and SFINAE (Substitution Failure Is Not An Error) **************************/
// While templates are incredibly powerful, sometimes you need to adjust the behavior of a template based on specific types or conditions.
// Template specialization allows you to provide custom logic for particular
// types, while SFINAE enables you to selectively disable or enable template instantiation based on
// type traits.

// // Function template that only accepts integral types
template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type 
printValue(T t)
{
    cout << "Integral type: " << t << endl;
}

// Function template that only accepts floating-point types
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type
printValue(T t)
{
    cout << "Floating point type: " << t << endl;
}

int main()
{
    cout << "Max of 10 and 20 is " << getMax(10, 20) << endl;
    // Calls
    // general template
    cout << "Max of 'A' and 'Z' is " << getMax('A', 'Z') << endl; // Calls specialized template

    Printer<double> printer1;
    printer1.print(3.14);
    // Calls generic print
    Printer<int> printer2;
    printer2.print(42);
    // Calls specialized print for int

    Pair<int, double> p(10, 3.14);
    p.print();

    //**********************************/
    // Variadic Template
    print(1, 2.5, "Hello", 'A');

    //
    Storage<int, double, string> storage(10, 3.14, "Hello");
    storage.print();
    cout << endl;
    // Prints: 10 3.14 Hello

    // SFINAE
    printValue(42);// Calls integral version
    printValue(3.14);// Calls floating-point version
    printValue(false);
    return 0;
}
