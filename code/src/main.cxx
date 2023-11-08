#include "../headers/hermite.h"
#include "../headers/solutions.h"
#include "../headers/schrodinger.h"
#include <iostream>
#include <armadillo>
#include <cmath>
using namespace arma;

int main()
{
  double m = 0.510998950;              //[MeV/c^2]
  double hbar = 6.582119569509067e-07; //[MeV.fs]
  double omega = sqrt((1 /*[N/m]*/ * 6.24151e-9 /*[MeV/c^2]*/) / m);
  int n = 2;

  Solutions solUnit = Solutions(m, hbar, omega);
  Solutions sol = Solutions();
  mat res = solUnit.solutions(n, -1, 1, 500);

  res.save("./bin/test.csv", csv_ascii);

  Schrodinger x = Schrodinger();
  mat schrodingerEquation = x.schrodinger1DEquation(res, hbar, omega, m);

  cout << "Energie (theorique) :" << endl;
  for (int i = 0; i < n + 1; i++)
  {
    cout << x.energyLevels(hbar, omega, i) << endl;
  }

  res.shed_row(0);
  res.shed_col(0);
  res.shed_col(res.n_cols - 1);

  mat energie = schrodingerEquation * pinv(res);
  cout << "Energie:" << sum(energie) << endl;

  cout << "Orthonormalité:" << solUnit.verifOrthonormality(0, 0) << endl;

  return 0;
}
