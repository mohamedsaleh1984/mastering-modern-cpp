#include <iostream>
using namespace std;

/*
Virtual Inheritance and Resolving Ambiguities
When a class inherits from multiple base classes, ambiguities can arise if the base classes have
methods or data members with the same name. C++ handles this situation using virtual inheritance.

Virtual inheritance ensures that the derived class only has one instance of the
common base class when multiple inheritance is involved.
*/

class A
{
public:
    void show() { std::cout << "A\n"; }
};


class B : virtual public A
{
};
class C : virtual public A
{
};
class D : public B, public C
{
};
int main()
{
    // Correctly calls A's show method without ambiguity
    D d;
    d.show();

    C c;
    c.show();
    
    return 0;
}