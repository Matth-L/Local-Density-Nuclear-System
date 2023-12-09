#include <iostream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include "../code/headers/basis.h"
#include "../code/headers/poly.h"
using namespace arma;

int v4()
{
    mat rho;
    rho.load("./code/src/rho.arma", arma_ascii);

    Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

    arma::vec zVals = {-10.1, -8.4, -1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    arma::vec rVals = {3.1, 2.3, 1.0, 0.0, 0.1, 4.3, 9.2, 13.7};

    mat result = zeros(rVals.n_rows, zVals.n_rows); // number of points on r- and z- axes
    std::vector<arma::mat> basisFuncs;
    auto start = std::chrono::high_resolution_clock::now();
    for (int m = 0; m < basis.mMax; m++)
    {
        for (int n = 0; n < basis.nMax(m); n++)
        {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
            {
                basisFuncs.push_back(basis.basisFunc(m, n, n_z, zVals, rVals));
            }
        }
    }

    size_t basisFuncsSize = basisFuncs.size();

    for (size_t i = 0; i < basisFuncsSize; i++)
    {
        mat basisProduct = basisFuncs[i] % basisFuncs[i];
        result += basisProduct * rho(i, i);

        for (size_t j = 0; j < i; j++)
        {
            basisProduct = 2 * basisFuncs[i] % basisFuncs[j];
            result += basisProduct * rho(i, j);
        }
    }

    int temps = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    return temps;
}
