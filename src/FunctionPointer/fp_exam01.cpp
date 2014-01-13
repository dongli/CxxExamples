/**
 *  This example shows the function pointer as a template parameter.
 *
 *  History:
 *
 *      2014-01-13
 *
 *          Li Dong     First creation.
 */

#include <iostream>

using namespace std;

// -----------------------------------------------------------------------------
// define a class with a static member function
class Foo {
    static int i;
public:
    Foo(int i_) {
        i = i_;
        cout << "[Notice]: Set static Foo::i to " << i << "." << endl;
    }

    static void f() {
        cout << "[Notice]: Foo::i = " << i << "." << endl;
    }
};

int Foo::i;

// -----------------------------------------------------------------------------
template <void f()>
void g() {
    cout << "[Notice]: Call function 'f' in function template 'g'." << endl;
    f();
}

// -----------------------------------------------------------------------------
int main(int argc, const char *argv[])
{
    Foo foo(5);
    g<Foo::f>();
    return 0;
}
