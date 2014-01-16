/**
 *  This example shows how to use MLPACK to finding neighbors within a range.
 *
 *  History:
 *
 *      2014-01-16
 *
 *          Li Dong     First creation.
 */

#include <mlpack/methods/range_search/range_search.hpp>

using namespace mlpack;
using namespace std;

// -----------------------------------------------------------------------------
// output:
//
//      Dataset:
//         1.0000  -1.0000  -1.0000   1.0000
//         1.0000   1.0000  -1.0000  -1.0000
//      Neighbor indices:
//               1         3
//               0         2
//               1         3
//               0         2
//      Neighbor distances:
//               2         2
//               2         2
//               2         2
//               2         2
int main(int argc, char const *argv[])
{
    // prepare dataset
    arma::mat dataset(2, 4);

    dataset(0, 0) =  1.0;
    dataset(1, 0) =  1.0;
    dataset(0, 1) = -1.0;
    dataset(1, 1) =  1.0;
    dataset(0, 2) = -1.0;
    dataset(1, 2) = -1.0;
    dataset(0, 3) =  1.0;
    dataset(1, 3) = -1.0;

    dataset.print("Dataset:");

    range::RangeSearch<> a(dataset);

    // search neighbors
    vector<vector<size_t> > neighbors;
    vector<vector<double> > distances;

    math::Range r(0.0, 2.1);

    a.Search(r, neighbors, distances);

    cout << "Neighbor indices:" << endl;
    for (int i = 0; i < neighbors.size(); ++i) {
        for (int j = 0; j < neighbors[i].size(); ++j) {
            cout << setw(10) << neighbors[i][j];
        }
        cout << endl;
    }

    cout << "Neighbor distances:" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        for (int j = 0; j < distances[i].size(); ++j) {
            cout << setw(10) << distances[i][j];
        }
        cout << endl;
    }

    return 0;
}