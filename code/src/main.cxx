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

  vec zVals = linspace(-20, 20, 64);
  vec rVals = linspace(-20, 20, 64);

  // car la fonction B est calculé pour chaque m, n et n_z, elle est donc calculé trop de fois
  // on la précalcule donc dans un cube qui est un vecteur de matrices
  std::vector<arma::mat> funcA(374);
  int k = 0;
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

  uint i = 0;
  mat result = zeros(64, 64); // number of points on r- and z- axes
  for (int i = 0; i < 374; i++)
  {

    for (int j = 0; j < 374; j++)
    {
      result += funcA[i] % funcA[j] * rho(i, j);
    }
  }

  // temps en seconde
  std::cout << "Temps d'exécution : " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "s" << std::endl;

  result.save("./bin/test.csv", csv_ascii);
  // result.print();
}
