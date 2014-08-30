/**
 *  This example shows the use of new 'auto' keyword in C++11. The container is
 *  from Armadillo library.
 *
 *  History:
 *
 *      2014-08-30
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

// -----------------------------------------------------------------------------
// output:
//
//      [Notice]: Use auto to access the elements of a field<double> object.
//      0
//      1
//      2
//      3
//
int main(int argc, char const *argv[])
{
    field<double> data;
    data.set_size(2, 2);
    int i = 0;
    for (auto &d : data) {
        d = i++;
    }
    cout << "[Notice]: Use auto to access the elements of a field<double> object." << endl;
    for (auto &d : data) {
        cout << d << endl;
    }
    return 0;
}