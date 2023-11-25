#include <iostream>
#include <armadillo>
#include <cmath>
#include <chrono>
#include "../headers/basis.h"
#include "../headers/poly.h"
using namespace arma;

std::string cubeToDf3(const arma::cube &m)
{
  std::stringstream ss(std::stringstream::out | std::stringstream::binary);
  int nx = m.n_rows;
  int ny = m.n_cols;
  int nz = m.n_slices;
  ss.put(nx >> 8);
  ss.put(nx & 0xff);
  ss.put(ny >> 8);
  ss.put(ny & 0xff);
  ss.put(nz >> 8);
  ss.put(nz & 0xff);
  double theMin = 0.0;
  double theMax = m.max();
  for (uint k = 0; k < m.n_slices; k++)
  {
    for (uint j = 0; j < m.n_cols; j++)
    {
      for (uint i = 0; i < m.n_rows; i++)
      {
        uint v = 255 * (fabs(m(i, j, k)) - theMin) / (theMax - theMin);
        ss.put(v);
      }
    }
  }
  return ss.str();
}

int main()
{
  mat rho;

  rho.load("./code/src/rho.arma", arma_ascii);

  auto start = std::chrono::high_resolution_clock::now();

  Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

  uint i = 0;
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
  std::cout << "Temps d'exécution : " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() << "s" << std::endl;

  result.save("./bin/test.csv", csv_ascii);
  // result.print();
}
