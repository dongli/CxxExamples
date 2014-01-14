#include <iostream>
#include <list>

using namespace std;

template <typename T>
void f(const list<T> &x) {
    cout << "[Notice]: You should add 'typename' before ";
    cout << "list<T>::const_iterator in a template!" << endl;
    // We must use 'typename' to tell compiler that this is a declaration,
    // since compile does not know what T is until we instantiate it.
    typename list<T>::const_iterator i = x.begin();
//  ^^^^^^^^
}

int main(int argc, char const *argv[])
{
    list<int> a;
    f<int>(a);
    return 0;
}