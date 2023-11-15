#include <iostream>
#include <armadillo>
#include <cmath>
#include "../headers/basis.h"
#include "../headers/poly.h"
using namespace arma;

int main()
{
  mat rho;
  rho.load("rho.arma", arma_ascii);
  Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

  uint i = 0;
  // for (int m = 0; m < basis.mMax; m++)
  //   for (int n = 0; n < basis.nMax(m); n++)
  //     for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
  //     {
  //       std::cout << "Basis vector " << i << ": m=" << m << " n=" << n << " n_z=" << n_z << std::endl;
  //       i++;
  //     }
  mat result = zeros(64, 64); // number of points on r- and z- axes
  vec zVals = linspace(-20, 20, 64);
  vec rVals = linspace(-20, 20, 64);
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

  result.print();
}
