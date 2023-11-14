#include <iostream>
#include <armadillo>
#include <cmath>
#include "../headers/basis.h"
using namespace arma;

int main()
{
  uint N = 14;
  float Q = 1.3;
  Basis basis(1.935801664793151,2.829683956491218,N,Q);
  std::cout << "br:" << basis.br << std::endl; 
  std::cout << "bz:" << basis.bz << std::endl;
  std::cout << "N:" << basis.N << std::endl; 
  std::cout << "Q:" << basis.Q << std::endl;  
  std::cout << "mMax:" << basis.mMax << std::endl; 
  std::cout << "nMax:" << basis.nMax << std::endl;
  std::cout << "n_zMax:" << basis.n_zMax << std::endl;  
  return 0;
}
