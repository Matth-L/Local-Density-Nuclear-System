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
     * TODO Faire les commetaires , n = 0 correspond à la colonne
     * it will contains the value of the hermite's polynome for each z
     */
    arma::mat polynomeMat;

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
     * @brief compute the value of the hermite's polynome using n and a vector of values Z
     */
    void calcHermite(int, arma::vec);

    arma::cube polynomeLaguerre;

    void calcLaguerre(int, int, arma::vec);

    arma::vec laguerre(int, int);
};

#endif // POLY_H
