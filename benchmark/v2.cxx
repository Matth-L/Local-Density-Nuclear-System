#include <iostream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include "../code/headers/basis.h"
#include "../code/headers/poly.h"
using namespace arma;

int v2()
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
    std::vector<arma::mat> funcB;
    auto start = std::chrono::high_resolution_clock::now();
    for (int mp = 0; mp < basis.mMax; mp++)
    {
        for (int np = 0; np < basis.nMax(mp); np++)
        {
            for (int n_zp = 0; n_zp < basis.n_zMax(mp, np); n_zp++)
            {
                funcB.push_back(basis.basisFunc(mp, np, n_zp, zVals, rVals));
            }
        }
    }

    for (int m = 0; m < basis.mMax; m++)
    {
        for (int n = 0; n < basis.nMax(m); n++)
        {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
            {
                uint j = 0;
                arma::mat funcA = basis.basisFunc(m, n, n_z, zVals, rVals);
                // ducoup pour chaque fonction B, on calcule la fonction A et on la multiplie par la densité
                // la fonction B est déja précalculé un for each suffit donc
                for (auto &func : funcB)
                {
                    result += funcA % func * rho(i, j);
                    j++;
                }
                i++;
            }
        }
    }

    int temps = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
    return temps;
}
