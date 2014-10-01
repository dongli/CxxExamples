/**
 *  This example shows one of the data race cases, The 'critical' directive
 *  is used to restrict the access to the shared memory.
 *
 *  History:
 *
 *      2014-10-01
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <vector>
#include <random>

typedef std::mt19937 RNG;
typedef std::uniform_real_distribution<double> Dist;

int main(int argc, char const *argv[])
{
    RNG rng(clock());
    Dist dist(0.0, 9.0);
    int n = 1000, error;
    std::vector<int> a(n), b(n), c(n), d(n);

    for (int i = 0; i < a.size(); ++i) {
        a[i] = static_cast<int>(dist(rng));
        b[i] = 0;
    }

    for (int i = 0; i < a.size(); ++i) {
        b[a[i]]++;
    }

#pragma omp parallel for
    for (int i = 0; i < a.size(); ++i) {
        c[a[i]]++;
    }

#pragma omp parallel for
    for (int i = 0; i < a.size(); ++i) {
#pragma omp critical
        d[a[i]]++;
    }

    error = 0;
    for (int i = 0; i < a.size(); ++i) {
        error += b[i]-c[i];
    }
    std::cout << "Data race occurs with error " << error << std::endl;

    error = 0;
    for (int i = 0; i < a.size(); ++i) {
        error += b[i]-d[i];
    }
    std::cout << "Data race is avoided with error " << error << std::endl;

    return 0;
}