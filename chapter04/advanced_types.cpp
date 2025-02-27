#include <iostream>
#include <vector>
#include <map>
using namespace std;

// auto, decltype, and range-based for loops.
void using_auto()
{
    auto x = 5;
    auto y = 3.14;
    cout << "x :" << x << ", y: " << y << endl;

    cout << endl;

    vector<int> vec = {1, 2, 3, 3, 5, 4};
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// decltype

int func()
{
    return 10;
}
/*
decltype is used to deduce the type of an expression without evaluating it. It allows you to examine
the type of an expression at compile time, which is useful when the type is complex or not immediately apparent.
*/
void using_decltype()
{

    int a = 5;
    double b = 10.5;
    // Using decltype to deduce the type of the sum of 'a' and 'b'
    decltype(a + b) result = a + b;

    // result is deduced as double
    // since adding an int and a double results in a double.
    std::cout << "Result: " << result << std::endl;

    // Use decltype to get the return type of func
    decltype(func()) x = func();               // x is deduced as int
    std::cout << "Result: " << x << std::endl; // Output: Result: 10
    cout << endl;
}

void using_auto_decltype()
{
    std::vector<int> vec = {10, 2, 3, 4};
    // Auto deduces iterator type
    auto it = vec.begin();
    // Decltype deduces the value type (int)
    decltype(*it) value = *it;
    std::cout << "First value: " << value << std::endl;
    cout << endl;
}
struct Point
{
    int x, y;
};

void using_range_based_for_loops()
{
    std::vector<int> container = {10, 20, 30, 40};
    // passing for reference
    for (auto &element : container)
        std::cout << element << " ";

    // passing by value && passing by value
    std::vector<Point> points = {{1, 2}, {3, 4}, {5, 6}};
    for (auto &point : points)
    {
        point.x += 1;
        // Modify each element
        point.y += 1;
    }

    // Print the modified points
    for (auto point : points)
    {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }
}

void using_range_based_for_loops_with_maps()
{
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    // Iterate over map using range-based for loop
    for (const auto &pair : m)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    // modify the values
    for (auto &pair : m)
    {
        pair.second  = pair.second  + " :) ";
        std::cout << pair.first << ": " << pair.second  << std::endl;
    }
    // view values after change
    for (const auto &pair : m)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main()
{
    using_auto();
    using_decltype();
    using_auto_decltype();
    using_range_based_for_loops();
    using_range_based_for_loops_with_maps();
    return 0;
}