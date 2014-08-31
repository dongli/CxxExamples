/**
 *  This example is similar to metaprogramming_exam01, but demostrates how to
 *  use template argument to conditionally select method from multiple versions.
 *
 *  History:
 *
 *      2014-01-13
 *
 *          Li Dong     First creation.
 */

#include <type_traits>
#include <iostream>
#include <iomanip>
 
using namespace std;
 
// -----------------------------------------------------------------------------
// a template class with multiple versions of method 'f'
template <int C>
class Foo {
public:
    template <int U = C>
    typename enable_if<U == 1, int>::type f() {
        cout << "[Notice]: Foo<1>::f is called." << endl;
        return 0;
    }

    template <int U = C>
    typename enable_if<U == 2, int>::type f() {
        cout << "[Notice]: Foo<2>::f is called." << endl;
        return 0;
    }
};
 
// -----------------------------------------------------------------------------
// two derived classes with different template argument 'C'
class Bar1 : public Foo<1> {
};

class Bar2 : public Foo<2> {
};
 
// -----------------------------------------------------------------------------
// output:
//
//      [Notice]: Foo<1>::f is called.
//      [Notice]: Foo<2>::f is called.
//
int main(int argc, const char *argv[])
{
    Bar1 bar1;
    Bar2 bar2;
    bar1.f();
    bar2.f();
    return 0;
}
