/**
 *  This example shows how to use basic OpenMP functions.
 *
 *  History:
 *
 *      2014-03-04
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <vector>
#include <omp.h>

int main(int argc, const char *argv[])
{
    std::vector<double> a(10);

#pragma omp parallel for
    for (int i = 0; i < a.size(); ++i) {
        a[i] = i;
    }

    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i] << std::endl;
    }

    return 0;
}
