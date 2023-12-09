#include <iostream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include "../code/headers/basis.h"
#include "../code/headers/poly.h"
using namespace arma;

int v3()
{
    mat rho;

    rho.load("./code/src/rho.arma", arma_ascii);

    Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

    arma::vec zVals = {-10.1, -8.4, -1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    arma::vec rVals = {3.1, 2.3, 1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    mat result = zeros(rVals.n_rows, zVals.n_rows); // number of points on r- and z- axes
    uint i = 0;

    // car la fonction B est calculé pour chaque m, n et n_z, elle est donc calculé trop de fois
    // on la précalcule donc dans un cube qui est un vecteur de matrices
    std::vector<arma::mat> funcA(374);
    int k = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int mp = 0; mp < basis.mMax; mp++)
    {
        for (int np = 0; np < basis.nMax(mp); np++)
        {
            for (int n_zp = 0; n_zp < basis.n_zMax(mp, np); n_zp++)
            {
                funcA[k] = basis.basisFunc(mp, np, n_zp, zVals, rVals);
                k++;
            }
        }
    }

    for (int i = 0; i < 374; i++)
    {

        for (int j = 0; j < 374; j++)
        {
            result += funcA[i] % funcA[j] * rho(i, j);
        }
    }

    int temps = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    return temps;
}
