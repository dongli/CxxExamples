/**
 *  This example shows how to use OpenMP with std::list.
 *
 *  History:
 *
 *      2014-03-04
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <list>
#include <omp.h>

int main(int argc, const char *argv[])
{
    std::list<double> a(10);

#pragma omp parallel
#pragma omp single
    {
        auto it = a.begin();
        for (; it != a.end(); ++it) {
#pragma omp task firstprivate(it)
            *it = 1.0;
        }
    }

    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}
