/**
 *  This example shows how to use variable length arguments in C++11 standards,
 *  and also shows how to deal with class hierarchy by using polymorphism.
 *
 *  History:
 *
 *      2014-03-13
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <initializer_list>

// -----------------------------------------------------------------------------
// class hierarchy
class A {
public:
    A() {}
    virtual ~A() {}
};

template <int N>
class B : public A {
public:
    B() : A() {}
    virtual ~B() {}
};

template <int N>
class C : public B<N> {
public:
    C() : B<N>() {}
    virtual ~C() {}
};

// -----------------------------------------------------------------------------
// a function that accepts variable length arguments
void func(std::initializer_list<A*> args) {
    int i = 0;
    for (auto arg : args) {
        // Note: Lower hierarchy class should be on the top!
        if (dynamic_cast<C<3>*>(arg) != NULL) {
            std::cout << "[Notice]: Argument " << i << " is a C<3> pointer." << std::endl;
        } else if (dynamic_cast<B<2>*>(arg) != NULL) {
            std::cout << "[Notice]: Argument " << i << " is a B<2> pointer." << std::endl;
        } else if (dynamic_cast<A*>(arg) != NULL) {
            std::cout << "[Notice]: Argument " << i << " is a A pointer." << std::endl;
        }
        i++;
    }
}

// -----------------------------------------------------------------------------
// output:
//
//  [Notice]: Argument 0 is a A pointer.
//  [Notice]: Argument 1 is a B<2> pointer.
//  [Notice]: Argument 2 is a C<3> pointer.
//
int main(int argc, const char *argv[])
{
    A a;
    B<2> b;
    C<3> c;
    func({&a, &b, &c});
    return 0;
}
