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
float v(int i, int N, float Q)
{
  return (N + 2) * pow(Q, 2 / 3) + 0.5 - i * Q;
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
  while (res < 1)
  {
    i++;
    res = v(i, N, Q);
  }
  mMax = i;

  arma::ivec nMax(mMax);
  nMax.fill(0);
  // TODO
};

/**
 * @brief
 *
 * @param m
 * @return float
 */
float Basis::nMax(int m)
{
  // a faire dans le constructeur puis on recup via le vecteur
  return 0.5 * (mMax - m - 1) + 1;
};

/**
 * @brief
 *
 * @param m
 * @param n
 * @return float
 */
float Basis::n_zMax(int m, int n)
{
  // a faire dans le constructeur puis on recup via la matrice
  return v(m + 2 * n + 1, N, Q);
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
