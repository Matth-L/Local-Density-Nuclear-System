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

  cube basisFuncs(64, 64, 374);
  int k = 0;
  for (int m = 0; m < basis.mMax; m++)
  {
    for (int n = 0; n < basis.nMax(m); n++)
    {
      for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
      {
        basisFuncs.slice(k) = (basis.basisFunc(m, n, n_z, zVals, rVals));
        k++;
      }
    }
  }

  mat result = zeros(64, 64);

  for (size_t i = 0; i < basisFuncs.n_slices; i++)
  {
    mat basisProduct = basisFuncs.slice(i) % basisFuncs.slice(i);
    result += basisProduct * rho(i, i);

    for (size_t j = 0; j < i; j++)
    {
      basisProduct = 2 * basisFuncs.slice(i) % basisFuncs.slice(j);
      result += basisProduct * rho(i, j);
    }
  }
  std::cout << "Temps d'exécution : " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "ms" << std::endl;

  result.save("./bin/test.csv", csv_ascii);
  // result.print();

  return 0;
}
