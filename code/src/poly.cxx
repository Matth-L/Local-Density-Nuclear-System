/**
 * @file hermite.cxx
 * @brief implementation of the hermite's polynome
 */
#include "../headers/poly.h"
#include <stdexcept>
using namespace arma;

/**
 * @brief get the matrix
 *
 * @return arma::mat
 */
mat Poly::getPolynomeMat()
{
    return polynomeMat;
};

/**
 * @brief get the cube of the laguerre's polynome
 *
 * @param n number of the hermite's polynome
 * @return vec the hermite's polynome
 */
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
 * @param n number of the hermite's polynome
 * @param z vector of the z values
 * @return vec the hermite's polynome
 */
void Poly::calcHermite(int n, vec z)
{
    polynomeMat = mat(z.n_elem, n + 1);
    vec twoZ = 2 * z;
    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            // n=0 => H0 = 1
            polynomeMat.col(i) = ones(z.n_elem);
        }
        else if (i == 1)
        {
            // n=1 => H1 = 2z
            polynomeMat.col(i) = twoZ;
        }
        else
        {
            // n => Hn = 2zHn-1 - 2(n-1)Hn-2
            polynomeMat.col(i) = twoZ % polynomeMat.col(i - 1) -
                                 2 * (i - 1) * polynomeMat.col(i - 2);
        }
    }
}

/**
 * @brief compute the value of the laguerre's polynome
 *
 * @param m the slice of the cube
 * @param n the col of the slice
 * @return vec the laguerre's polynome
 */
vec Poly::laguerre(int m, int n)
{
    return polynomeLaguerre.slice(m).col(n);
};

/**
 * @brief compute the value of the laguerre's polynome
 *
 * @param mInput number M of the laguerre's polynome
 * @param nInput number N of the laguerre's polynome
 * @param z vector of the z values
 */
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

    polynomeLaguerre = cube(z.n_elem, nInput, mInput);
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
                // splitting the formula in two parts what depends on z and what doesn't
                polynomeLaguerre.slice(m).col(n) =
                    (2.0 + (m - 1.0 - z) / n) % a - (1.0 + (m - 1.0) / n) * b;
            }
        }
    }
}
