/**
 * @file hermite.cxx
 * @author Matthias Lapu
 * @brief implementation of the hermite's polynome
 */
#include "../headers/poly.h"
#include <stdexcept>
using namespace arma;

/**
 * @brief get the matrix of the hermite's polynome
 *
 * @return arma::mat
 */
mat Poly::getPolynomeMat()
{
  return polynomeMat;
};

vec Poly::hermite(int n)
{
  return polynomeMat.col(n);
}

/**
 * @brief compute the value of the hermite's polynome
 *
 * [
 * [ z0 z1 z2 z3 ]
 * [ z0 z1 z2 z3 ]
 * [ z0 z1 z2 z3 ]
 * ]
 * n = 0 is a col of 1 ...
 */
void Poly::calcHermite(int n, vec z)
{
  vec twoZ = 2 * z;
  // TODO .col au lieu d'insert_cols
  for (int i = 0; i <= n; i++)
  {
    if (i == 0)
    {
      // n=0 => H0 = 1
      polynomeMat.insert_cols(i, ones(z.n_elem));
    }
    else if (i == 1)
    {
      // n=1 => H1 = 2z
      polynomeMat.insert_cols(i, twoZ);
    }
    else
    {
      // n => Hn = 2zHn-1 - 2(n-1)Hn-2
      polynomeMat.insert_cols(i, twoZ % polynomeMat.col(i - 1) -
                              2 * (i - 1) * polynomeMat.col(i - 2));
    }
  }
}

vec Poly::laguerre(int m, int n)
{
  return polynomeLaguerre.slice(m).col(n);
};

void Poly::calcLaguerre(int mInput, int nInput, vec z)
{

  /*
       [
        m = 0
        [
          [1, ....]
          [1, ....]
          [1, ....]
          [1, ....]
        ]
       ]
  */

  // cube of dim : row = size of z  , col = n , depth = m

  polynomeLaguerre = cube(z.n_elem, nInput, mInput);

  cout << size(polynomeLaguerre) << endl;
  for (int m = 0; m < mInput; m++)
  {
    for (int n = 0; n < nInput; n++)
    {
      if (n == 0)
      {
        polynomeLaguerre.slice(m).col(0) = ones(z.n_elem);
      }
      else if (n == 1)
      {
        polynomeLaguerre.slice(m).col(1) = 1 + m - z;
      }
      else if (n > 1)
      {

        vec a = polynomeLaguerre.slice(m).col(n - 1);
        vec b = polynomeLaguerre.slice(m).col(n - 2);
        // séparer en ce qui dépend de z et ce qui ne dépend pas
        polynomeLaguerre.slice(m).col(n) =
          (2.0 + (m - 1.0 - z) / n) % a - (1.0 + (m - 1.0) / n) * b;
      }
    }
  }
}
