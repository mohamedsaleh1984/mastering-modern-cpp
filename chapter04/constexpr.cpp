#include <iostream>
using namespace std;
/*
    constexpr can be used in different forms
    1. declation specifier : declares that it is possible to evaluate the value of the function or the variable at the compile time.
    - it's type must be a LiteralType
    2. if statment
    3. lambda

    in the nutshell, constexpr expression, function are being injected in the code during the compile time.
    which means NO functional call in the assembly level, the function call will be replace by the actual code
    and the parameters will be treated normally in the assembly level... making constexpr faster
    because we don't have to retain the stack pointer or adding bytes for memory alignment or restore the Stack pointer back to the original state before the call
    also another great advantage is Type Checking.

    constexpre x = 10; can't be changed later like const

    Note: generics eval types in the compile time.

*/

constexpr int square(int x)
{
    return x * x;
}

constexpr int factorial(int n)
{
    return (n == 0) ? 1 : n * factorial(n - 1);
}

constexpr int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

template <int N>
constexpr int square()
{
    return N * N;
}

constexpr int add(int a, int b)
{
    return a + b;
}

int main()
{
    constexpr int value = square<4>();

    cout << "Should Overflow " << add(__INT_MAX__, 1) << endl;

    return 0;
}