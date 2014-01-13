/**
 *  This example shows how to conditionally declare member functions in a class
 *  template using SFINAE techniques.
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
// SFINAE codes
template <typename T, typename CheckStruct>
struct has_member_impl {
    typedef char yes;
    typedef long no;
 
    template <typename C>
    static yes test(typename CheckStruct::template get<C>*);
 
    template <typename C>
    static no  test(...);
 
    static const bool value = (sizeof(test<T>(0)) == sizeof(yes));
};
 
template <typename T, typename CheckStruct>
struct has_member
    : std::integral_constant<bool, has_member_impl<T, CheckStruct>::value> {};
 
struct check_has_g {
    template <typename T, void (T::*)() = &T::g> // function signature
    struct get {};
};
 
template <typename T>
struct has_g : has_member<T, check_has_g> {};
 
// -----------------------------------------------------------------------------
// a class template with conditional member function 'f'
template <typename T>
class Foo {
public:
    // Member function 'f' is declared only if 'T' has member function 'g'.
    // TODO: Maybe we should also check if 'T' is a class or not.
    // method 1
    template <typename = typename enable_if<has_g<T>::value>::type>
    int f() {
        cout << "[Notice]: Foo<T>::f is called." << endl;
        return 0;
    }
 
    // method 2
    // template <typename U = T>
    // typename enable_if<has_g<U>::value, int>::type f() {
    //     cout << "[Notice]: Foo<T>::f is called." << endl;
    //     return 0;
    // }
};
 
// -----------------------------------------------------------------------------
// two testing classes
class Bar1 {
public:
    void g() {}
};
 
class Bar2 {
};
 
// -----------------------------------------------------------------------------
 
int main(int argc, const char *argv[])
{
    cout << "[Notice]: Does 'Bar1' has member function 'g': ";
    cout << boolalpha << has_g<Bar1>::value << "." << endl;
    cout << "[Notice]: Does 'Bar2' has member function 'g': ";
    cout << boolalpha << has_g<Bar2>::value << "." << endl;
    Foo<Bar1> bar1;
    Foo<Bar2> bar2;
    bar1.f();
    // The following line will not be compiled, since bar2 has no member
    // function 'f'.
    // bar2.f();
    return 0;
}