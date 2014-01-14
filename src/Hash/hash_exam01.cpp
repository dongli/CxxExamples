/**
 *  This example shows the how to extend the std::hash to handle vector<int>
 *  type.
 *
 *  History:
 *
 *      2014-01-14
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// -----------------------------------------------------------------------------
// extend the std::hash to handle vector<int> type by using XOR operator
namespace std {

template <>
struct hash<vector<int> > {
    size_t operator()(const vector<int> &x) const {
        size_t res = x[0];
        for (int i = 1; i < x.size(); ++i) {
            res = res ^ x[i];
        }
        return res;
    }
};

}

// -----------------------------------------------------------------------------
// output:
//
//      [Notice]: The hash value of vector<int> x {99,43,3} is 75.
//
int main(int argc, const char *argv[])
{
    vector<int> x;
    x.push_back(99);
    x.push_back(43);
    x.push_back(3);
    hash<vector<int> > hashFunction;

    cout << "[Notice]: The hash value of vector<int> x {";
    for (int i = 0; i < x.size()-1; ++i) {
        cout << x[i] << ",";
    }
    cout << x[x.size()-1] << "} is " << hashFunction(x) << "." << endl;

    return 0;
}
