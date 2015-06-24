/**
 *  This example shows how to use Boost.variant to do polymorphic tasks.
 *
 *  History:
 *
 *      2015-06-24
 *
 *          Li Dong     First creation.
 */

#include <boost/variant.hpp>
#include <iostream>
#include <string>

using boost::variant;
using namespace std;

typedef variant<int, double, string> types;

types foo(int x) {
    types res;
    if (x == 1) {
        res = 1;
    } else if (x == 2) {
        res = 1.0;
    } else if (x == 3) {
        res = "1";
    }
    return res;
}

int main(void) {
    types a = foo(1);
    types b = foo(2);
    types c = foo(3);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
}
