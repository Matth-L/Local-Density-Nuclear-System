#include <iostream>
#include <armadillo>
#include <cmath>
using namespace arma;

int main()
{
  int m, n, sizeZ;
  n = 3;
  sizeZ = 4;
  m = 5;
  // cube (3,4,5)
  cube x = cube(4, 4, 3); // il y a 5 matrice de taille 3x4

  cout << x.slice(0) << endl;
}
