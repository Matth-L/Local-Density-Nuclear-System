#include <iostream>
#include <armadillo>
#include <cmath>
#include "../headers/basis.h"
#include "../headers/poly.h"
using namespace arma;

int main()
{
  Poly poly;
  arma::vec z = {-10.1, -8.4, -1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
  poly.calcLaguerre(1, 1, z);
  uint N = 14;
  float Q = 1.3;
  Basis basis(1.935801664793151, 2.829683956491218, N, Q);
  std::cout << "br:" << basis.br << std::endl;
  std::cout << "bz:" << basis.bz << std::endl;
  std::cout << "N:" << basis.N << std::endl;
  std::cout << "Q:" << basis.Q << std::endl;
  std::cout << "mMax:" << basis.mMax << std::endl;
  std::cout << "nMax:" << basis.nMax << std::endl;
  std::cout << "n_zMax:" << basis.n_zMax << std::endl;

  cout << "zFunc" << endl;
  arma::vec res = basis.zPart(z, 15);
  res.print();

  cout << "rFunc" << endl;
  arma::vec r = {3.1, 2.3, 1.0, 0.0, 0.1, 4.3, 9.2, 13.7};
  arma::vec res2 = basis.rPart(r, 8, 2);
  res2.print();
  return 0;
}
