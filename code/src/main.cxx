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

  mat result = zeros(64, 16); // number of points on r- and z- axes
  vec xVals = linspace(-10, 10, 32);
  vec yVals = linspace(-10, 10, 32);
  vec zVals = linspace(-20, 20, 64);

  // vec rVals = sqrt(xVals % xVals + yVals % yVals);

  // vec tVals = zeros(32);

  vec rVals = linspace(0, 10, 16); // 16
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

  result.save("./bin/test.csv", csv_ascii);

  cube cubeResult = zeros(32, 32, 64);

  for (int x = 0; x < 32; x++)
  {
    for (int y = 0; y < 32; y++)
    {
      int distance = static_cast<int>(std::sqrt(std::pow(x - 16, 2) + std::pow(y - 16, 2)));
      cout << "x: " << x << " y: " << y << " distance:" << distance << endl;
      for (int z = 0; z < 64; z++)
      {
        // on fait la moyenne entre 2 points
        if (distance < 16)
        {
          if (distance <= 0)
          {
            cubeResult(x, y, z) = result(z, 0);
          }
          else
          {
            cubeResult(x, y, z) = 0.5 * (result(z, distance - 1) + result(z, distance));
          }
        }
        else
        {
          cubeResult(x, y, z) = 0;
        }
      }
    }
  }

  std::string df3 = cubeToDf3(cubeResult);
  std::ofstream file("example.df3", std::ios::binary | std::ios::out);
  file << df3;
  file.close();
}