/**
 * @file hermite.cxx
 * @author Matthias Lapu
 * @brief implementation of the hermite's polynome
 */
#include "../headers/poly.h"
#include <stdexcept>
using namespace arma;

/*/**
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
 */
void Poly::calcHermite(int n, vec z)
{
  // TODO .col au lieu d'insert_cols
  vec twoZ = 2 * z;
  for (unsigned int i = 0; i <= n; i++)
  {
    if (i == 0)
    {
      // n=0 => H0 = 1
      polynomeMat.insert_cols(i, ones(size(z)));
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

void Poly::calcLaguerre(int mInput, int nInput, vec z)
{

  for (uint m = 0; m < mInput; m++)
  {
    for (uint n = 0; n < nInput; n++)
    {
      if (n == 0)
      {
        // 1 => (m,0)
        ones();
      }
      else if (n == 1)
      {
        // 1 + m - z => (m,1)
        polynomeLaguerre[m, 1]
      }
    }
  }
}

vec Poly::laguerre(int m, int n)
{
  return 0;
};
