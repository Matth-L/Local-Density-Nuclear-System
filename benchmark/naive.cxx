#include <iostream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include "../code/headers/basis.h"
#include "../code/headers/poly.h"
using namespace arma;

int naive()
{
    mat rho;

    rho.load("./code/src/rho.arma", arma_ascii);

    Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

    uint i = 0;
    arma::vec zVals = {-10.1, -8.4, -1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    arma::vec rVals = {3.1, 2.3, 1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
    mat result = zeros(zVals.n_rows, zVals.n_rows);

    auto start = std::chrono::high_resolution_clock::now();

    for (int m = 0; m < basis.mMax; m++)
    {
        for (int n = 0; n < basis.nMax(m); n++)
        {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
            {
                uint j = 0;
                for (int mp = 0; mp < basis.mMax; mp++)
                {
                    for (int np = 0; np < basis.nMax(mp); np++)
                    {
                        for (int n_zp = 0; n_zp < basis.n_zMax(mp, np); n_zp++)
                        {
                            // cout << "m = " << m << " n = " << n << " n_z = " << n_z << " mp = " << mp << " np = " << np << " n_zp = " << n_zp << endl;
                            arma::mat funcA = basis.basisFunc(m, n, n_z, zVals, rVals);
                            arma::mat funcB = basis.basisFunc(mp, np, n_zp, zVals, rVals);
                            result += funcA % funcB * rho(i, j);
                            j++; // mat += mat % mat * double
                        }
                    }
                }
                i++;
            }
        }
    }

    // temps en seconde
    int temps = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    return temps;
}
