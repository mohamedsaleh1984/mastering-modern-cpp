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
    return 0;
}
