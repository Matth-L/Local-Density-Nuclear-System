#include <iostream>
#include <armadillo>
#include <cmath>
#include <fstream>
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

  Basis basis(1.935801664793151, 2.829683956491218, 14, 1.3);

  uint i = 0;
  // for (int m = 0; m < basis.mMax; m++)
  //   for (int n = 0; n < basis.nMax(m); n++)
  //     for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
  //     {
  //       std::cout << "Basis vector " << i << ": m=" << m << " n=" << n << " n_z=" << n_z << std::endl;
  //       i++;
  //     }
  mat result = zeros(64, 32); // number of points on r- and z- axes
  vec zVals = linspace(-20, 20, 64);
  vec xVals = linspace(-10, 10, 32);
  vec yVals = linspace(-10, 10, 32);

  vec rVals = sqrt(xVals % xVals + yVals % yVals);
  vec tVals = atan(yVals / xVals); // donne le meme résultat a revoir
  std::cout << rVals << std::endl;
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

  result.save("./bin/test.csv", csv_ascii);
  // result.print();

  // pas comme ça

  // cube RZTresult = zeros(64, 64, 64);
  // for (int mSum = 0; mSum < 2 * basis.mMax - 1; mSum++)
  // {
  //   for (int i = 0; i < RZTresult.n_slices; i++)
  //   {
  //     RZTresult.slice(i) = result * exp((i * mSum) * tVals);
  //   }
  // }
  // cube &ref = RZTresult;
  // std::ofstream outFile("serialized.txt");
  // outFile << cubeToDf3(ref);

  // cube XYZresult = zeros(64, 64, 64);
  // for (int r = 0; r < RZTresult.n_rows; r++)
  // {
  //   for (int z = 0; z < RZTresult.n_cols; z++)
  //   {
  //     for (int t = 0; t < RZTresult.n_slices; t++)
  //     {
  //       // c'est nul
  //     }
  //   }
  // }
}
