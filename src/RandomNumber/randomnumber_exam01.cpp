/**
 *  This example shows how to use random number generator with uniform
 *  distribution.
 *
 *  History:
 *
 *      2014-03-04
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <random>

typedef std::mt19937 RNG;
typedef std::uniform_real_distribution<double> Dist;

int main(int argc, const char *argv[])
{
    RNG rng(clock());
    Dist dist(0.0, 1.0);

    for (int i = 0; i < 10; ++i) {
        std::cout << dist(rng) << std::endl;
    }

    return 0;
}
