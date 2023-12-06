/**
 * @file hermite.h
 * @author Lapu Matthias
 */

#ifndef POLY_H
#define POLY_H
#include <armadillo>
#include <iostream>

/**
 * @brief Hermite's object containing :
 * - the value of n (int)
 * - a vector Z with all the values to be computed
 * - a matrix containing the value of the hermite's polynome
 */
class Poly
{
public:
    /**
     * @brief this matrix contains
     * n = 0 is a col of 1 ...
     */
    arma::mat polynomeMat;

    /**
     * @brief the cube that contains the value of the laguerre's polynome
     */
    arma::cube polynomeLaguerre;

    /**
     * @brief get the matrix of the hermite's polynome
     *
     * @return arma::mat
     */
    arma::mat getPolynomeMat();

    /**
     * @brief get the row of the hermite's matrix
     */
    arma::vec hermite(int);

    /**
     * @brief getting the value of the laguerre's polynome
     *
     * @return arma::vec
     */
    arma::vec laguerre(int, int);

    /**
     * @brief compute the value of the hermite's polynome using n and a vector of values Z
     */
    void calcHermite(int, arma::vec);

    /**
     * @brief compute the value of the laguerre's polynome using n and a vector of values Z
     */
    void calcLaguerre(int, int, arma::vec);
};

#endif // POLY_H
