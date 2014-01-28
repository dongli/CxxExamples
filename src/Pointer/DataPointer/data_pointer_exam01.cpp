/**
 *  This example shows the data pointer to any data type. There are two ways for
 *  doing such task. One is old fashion by using void pointer, and the other
 *  uses Boost::Any. Boost::Any is safer than void pointer when casting content.
 *
 *  History:
 *
 *      2014-01-21
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <boost/any.hpp>

using namespace std;

void use_void_ptr() {
    void *a = NULL;
    int b = 1;
    a = &b;
    cout << "[Notice]: typeid(<void*>) is " << typeid(a).name() << "." << endl;
    cout << "[Notice]: typeid(*<void*>) is " << typeid(*a).name() << "." << endl;
    cout << "[Notice]: typeid(<int>) is " << typeid(b).name() << "." << endl;
    cout << "[Notice]: (static_cast<int*>(<void*>) != NULL) is " << (static_cast<int*>(a) != NULL) << "." << endl;
    cout << "[Notice]: *static_cast<int*>(<void*>) is " << *static_cast<int*>(a) << "." << endl;
    cout << "[Warning]: *static_cast<double*>(<void*>) is " << *static_cast<double*>(a) << "." << endl;
}

void use_boost_any() {
    boost::any a;
    int b = 1;
    a = &b;
    cout << "[Notice]: typeid(boost::any) is " << typeid(a).name() << "." << endl;
    cout << "[Notice]: typeid(boost::any) == typeid(int*) is " << (typeid(a) == typeid(&b)) << "." << endl;
    cout << "[Notice]: <boost::any>.type() == typeid(int*) is " << (a.type() == typeid(&b)) << "." << endl;
    try {
        int c = *boost::any_cast<double*>(a);
    } catch (const boost::bad_any_cast &e) {
        cout << "[Notice]: Catch bad cast from int pointer to double pointer!" << endl;
    }
}

// -----------------------------------------------------------------------------
// output:
//
//      [Notice]: typeid(<void*>) is Pv.
//      [Notice]: typeid(*<void*>) is v.
//      [Notice]: typeid(<int>) is i.
//      [Notice]: (static_cast<int*>(<void*>) != NULL) is true.
//      [Notice]: *static_cast<int*>(<void*>) is 1.
//      [Warning]: *static_cast<double*>(<void*>) is 4.87727e+151.
//      [Notice]: typeid(boost::any) is N5boost3anyE.
//      [Notice]: typeid(boost::any) == typeid(int*) is false.
//      [Notice]: <boost::any>.type() == typeid(int*) is true.
//      [Notice]: Catch bad cast from int pointer to double pointer!
//
int main(int argc, char const *argv[])
{
    cout << boolalpha;
    use_void_ptr();
    use_boost_any();
    return 0;
}