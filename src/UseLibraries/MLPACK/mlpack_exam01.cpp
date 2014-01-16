/**
 *  This example shows how to use MLPACK to do k-nearest-neighbor search task.
 *
 *  History:
 *
 *      2014-01-15
 *
 *          Li Dong     First creation.
 */

#include <mlpack/methods/neighbor_search/neighbor_search.hpp>

using namespace mlpack;

// -----------------------------------------------------------------------------
// output:
//
//      Dataset:
//         1.0000  -1.0000  -1.0000   1.0000
//         1.0000   1.0000  -1.0000  -1.0000
//      Neighbor indices:
//              3        2        3        2
//              1        0        1        0
//              2        3        0        1
//      Neighbor distances:
//         2.0000   2.0000   2.0000   2.0000
//         2.0000   2.0000   2.0000   2.0000
//         2.8284   2.8284   2.8284   2.8284
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

    // AllkNN is a typedef, the actual type is:
    //  NeighborSearch<NearestNeighborSort, metric::SquaredEuclideanDistance>
    AllkNN a(dataset);

    // search neighbors
    arma::Mat<size_t> neighbors;
    arma::mat distances;
    a.Search(3, neighbors, distances);

    neighbors.print("Neighbor indices:");
    distances.print("Neighbor distances:");

    return 0;
}
