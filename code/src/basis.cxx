/**
 * @file basis.cxx
 * @author Louati Roméo
 * @brief implementation of basis.h
 *
 */

#include "../headers/basis.h"
#include <cmath>
using namespace arma;

/**
 * @brief used for the basis truncation
 *
 * @param i
 * @return float
 */
int v(int i, int N, float Q)
{
  return (N + 2) * pow(Q, 2.0 / 3) + 0.5 - i * Q;
}
/**
 * @brief Construct a new Basis:: Basis object
 *
 * @param br
 * @param bz
 * @param N
 * @param Q
 */
Basis::Basis(double brInput, double bzInput, uint NInput, float QInput)
{
  br = brInput;
  bz = bzInput;
  N = NInput;
  Q = QInput;

  int i = 0;
  float res = v(i, N, Q);
  while (res > 1)
  {
    i++;
    res = v(i, N, Q);
  }
  mMax = i;

  nMax.zeros(mMax);
  for (int i = 0; i<mMax;i++)
  {
    nMax[i] = 0.5 * (mMax - i - 1) + 1;
  }
  n_zMax.zeros(mMax,max(nMax));
  for (int m = 0;m<mMax;m++)
  {
      for (int n = 0;n<nMax[m];n++)
      {
          int result = v(m+2*n+1,14,1.3);
          if (result<0) continue;
          n_zMax(m,n) = result;
      }
  }
};

/**
 * @brief compute the rPart of the basis function
 *
 * @return arma::vec
 */
arma::vec Basis::rPart(arma::vec, int, int)
{
  // TODO
  return 0;
};

/**
 * @brief compute the zPart of the basis function
 *
 * @return arma::vec
 */
arma::vec Basis::zPart(arma::vec, int)
{
  // TODO
  return 0;
};

/**
 * @brief compute the basis function
 *
 * @return arma::mat
 */
arma::mat Basis::basisFunc(int, int, int, arma::vec, arma::vec)
{
  // TODO
  return 0;
};
