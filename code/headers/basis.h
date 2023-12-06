/**
 * @file basis.h
 * @author Louati Roméo
 */

#ifndef BASIS_H
#define BASIS_H
#include <armadillo>
#include <iostream>

/**
 * @brief Basis contains:
 * - 4 values br, bz, N, Q, for the basis deformation and the basis truncation
 * - mMax, nMax, n_zMax, possibles values for m,n,n_z
 */
class Basis
{
public:
  /**
   * @brief br is a basis deformation parameter for rPart
   *
   */
  double br;

  /**
   * @brief bz is a basis deformation parameter for zPart
   *
   */
  double bz;

  /**
   * @brief N is a basis truncation parameter
   *
   */
  uint N;

  /**
   * @brief Q is a basis truncation parameter
   *
   */
  float Q;

  /**
   * @brief mMax is the maximum value for the quantum number m (excluded)
   *
   */
  int mMax;

  /**
   * @brief nMax are the maximum values for the quantum number n (excluded)
   *
   */
  arma::ivec nMax;

  /**
   * @brief n_vMax are the maximul values for the quantum number n_z (excluded)
   *
   */
  arma::imat n_zMax;

  /**
   * @brief Construct a new Basis object, with the basis deformation parameters and the basis truncation parameters
   *
   * @param double value for the br parameter
   * @param double value for the bz parameter
   * @param uint value for N
   * @param float value for Q
   */
  Basis(double, double, uint, float);

  /**
   * @brief compute the rPart of the basis function
   *
   * @param arma::vec all the values that r can take
   * @param int the m parameter
   * @param int the n parameter
   * @return arma::vec the result
   */
  arma::vec rPart(arma::vec, int, int);

  /**
   * @brief compute the zPart of the basis function
   *
   * @param arma::vec all the values that z can take
   * @param int the nz parameter
   * @return arma::vec the result
   */
  arma::vec zPart(arma::vec, int);

  /**
   * @brief compute the basis function
   * 
   * @param int the m parameter
   * @param int the n parameter
   * @param int the nz parameter
   * @param arma::vec all the values that r can take
   * @param arma::vec all the values that z can take
   * @return arma::mat the result
   */
  arma::mat basisFunc(int, int, int, arma::vec, arma::vec);
};

#endif