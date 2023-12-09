/**
 * @file basis.cxx
 * @author Louati Roméo
 * @brief implementation of basis.h
 *
 */

#include "../headers/basis.h"
#include "../headers/poly.h"
#include <cmath>
using namespace arma;

/**
 * @brief used for the basis truncation
 *
 * @param i index
 * @param N basis truncation parameter
 * @param Q basis truncation parameter
 * @return float
 */
int v(int i, int N, float Q)
{
    return (N + 2) * pow(Q, 2.0 / 3) + 0.5 - i * Q;
}
/**
 * @brief Construct a new Basis:: Basis object
 *
 * @param brInput value for the br parameter
 * @param bzInput value for the bz parameter
 * @param NInput uint value for N (basis truncation parameter)
 * @param QInput float value for Q (basis truncation parameter)
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
    for (int i = 0; i < mMax; i++)
    {
        nMax[i] = 0.5 * (mMax - i - 1) + 1;
    }
    n_zMax.zeros(mMax, max(nMax));
    for (int m = 0; m < mMax; m++)
    {
        for (int n = 0; n < nMax[m]; n++)
        {
            int result = v(m + 2 * n + 1, 14, 1.3);
            if (result < 0)
                continue;
            n_zMax(m, n) = result;
        }
    }
};

/**
 * @brief compute the rPart of the basis function
 *
 * @param r all the values that r can take
 * @param m the m parameter
 * @param n the n parameter
 * @return arma::vec
 */
arma::vec Basis::rPart(arma::vec r, int m, int n)
{
    int am = abs(m);
    double c = (1 / (br * sqrt(M_PI))) * sqrt(tgamma(n + 1) / tgamma(n + am + 1));
    vec r2 = pow(r, 2);
    double val = -1 / (2 * br * br);

    Poly poly;
    poly.calcLaguerre(am + 1, n + 1, r2 * (1 / (br * br)));

    return c * exp(r2 * val) % pow(r * (1 / br), am) % poly.laguerre(am, n);
};

/**
 * @brief computes the zPart of the basis function
 *
 * @param z all the values that z can take
 * @param nz the nz parameter
 * @return arma::vec
 */
arma::vec Basis::zPart(arma::vec z, int nz)
{
    Poly poly;
    poly.calcHermite(nz + 1, z / bz);

    double c = 1 / (sqrt(bz) * sqrt(pow(2, nz) * sqrt(M_PI) * tgamma(nz + 1)));
    double val = -1 / (2 * bz * bz);
    vec z2 = pow(z, 2);

    return c * exp(z2 * val) % poly.hermite(nz);
};

/**
 * @brief compute the basis function
 *
 * @param m the m parameter
 * @param n the n parameter
 * @param n_z the nz parameter
 * @param z all the values that r can take
 * @param r all the values that z can take
 * @return matrice with values of basis function
 */
arma::mat Basis::basisFunc(int m, int n, int n_z, arma::vec z, arma::vec r)
{
    return zPart(z, n_z) * rPart(r, m, n).t();
};
