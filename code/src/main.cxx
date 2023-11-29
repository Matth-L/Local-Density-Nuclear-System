#include <iostream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include "../headers/basis.h"
#include "../headers/poly.h"
using namespace arma;

int main()
{
  mat rho;
  rho.load("./code/src/rho.arma", arma_ascii);

  auto start = std::chrono::high_resolution_clock::now();

  Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

  vec zVals = linspace(-20, 20, 64);
  vec rVals = linspace(-20, 20, 64);

  std::vector<arma::mat> basisFuncs;
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

  uint i = 0;
  mat result = zeros(64, 64);

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
              result += basisFuncs[i] % basisFuncs[j] * rho(i, j);
              j++;
            }
          }
        }
        i++;
      }
    }
  }

  std::cout << "Temps d'exécution : " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "ms" << std::endl;

  result.save("./bin/test.csv", csv_ascii);

  return 0;
}
