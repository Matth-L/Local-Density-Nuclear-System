#include "../headers/solutions.h"
#include "../headers/hermite.h"
using namespace arma;

/**
 * @brief Construct a new Solutions::solutions object
 * 
 * @param float m
 * @param float hbar
 * @param float omega
 */
Solutions::Solutions(float mInput, float hbarInput, float omegaInput)
{
  m = mInput;
  hbar = hbarInput;
  omega = omegaInput;
}

/**
 * @brief Construct a new Solutions::solutions object
 */
Solutions::Solutions()
{
  m = 1;
  hbar = 1;
  omega = 1;
}

/**
 * @brief get the particle's mass
 * 
 * @return float mass
 */
float Solutions::getM(){ return m;}

/**
 * @brief get hbar
 * 
 * @return float hbar
 */
float Solutions::getHbar(){ return hbar;}

/**
 * @brief get omega
 * 
 * @return float omega
 */
float Solutions::getOmega(){ return omega;}

/**
 * @brief Calcutate the solutions of the 1D quantum harmonic oscillator for 1 to n
 * using the given z values
 * Outputs a [n+1,number of z] matrix like the following:
 * [
 *  [z1, z2, ..., zp]
 *  [ψ0(z0), ψ0​(z2),...,ψ0(zp)] n=0
 *  [ψ1(z0), ψ1​(z2),...,ψ1(zp)] n=1
 *  ...
 *  [ψn(z0), ψn​(z2),...,ψn(zp)] n=n
 * ]
 * @return mat
 */
mat Solutions::solutions(unsigned int n, mat z){
    float cons = sqrt((m * omega) / hbar);
    Hermite hermiteMat = Hermite(n, cons * z); // creates the value of the Hermite polynomial
    hermiteMat.fillPolynomeHermite();

    z = z.t();
    mat z2 = pow(z, 2);           // z to the power of 2
    mat A = mat(n + 1, z.n_cols); // A is the first part of the equation without Hn
    for (unsigned int i = 0; i < n + 1; i++)
    {
        A.row(i) = (1 / (sqrt(pow(2, i) * tgamma(i + 1)))) * pow((m * omega) / (M_PI * hbar), 0.25) * exp(-((m * omega * z2) / (2 * hbar))); // filling up the matrix
    }

    mat sol = A % hermiteMat.getPolynomeMat().t(); // calculates the actual solution
    sol.insert_rows(0, z);                         // adding the z values to the solution
    return sol;
}

/**
 * @brief Calcutate the solutions of the 1D quantum harmonic oscillator for 1 to n.
 * The method calculates the z values maching the parameters
 * Outputs a [n+1,number of z] matrix like the following:
 * [
 *  [z1, z2, ..., zp]
 *  [ψ0(z0), ψ0​(z2),...,ψ0(zp)] n=0
 *  [ψ1(z0), ψ1​(z2),...,ψ1(zp)] n=1
 *  ...
 *  [ψn(z0), ψn​(z2),...,ψn(zp)] n=n
 * 
 * @param n 
 * @param start 
 * @param end 
 * @param increment 
 * @return mat 
 */
mat Solutions::solutions(unsigned int n, float start, float end, unsigned int increment)
{
    mat z = linspace(start, end, increment); // creates all the values for z
    return Solutions::solutions(n,z);
    
}

float Solutions::verifOrthonormality(unsigned int p, unsigned int q)
{
    int deg = p + q;
    int n = deg - deg % 10 + 10;    //finds the smaller multiple of ten above p + q

    float C = (1 / (sqrt(pow(2, p) * tgamma(p + 1)))) * pow((m * omega) / (M_PI * hbar), 0.25)
            * (1 / (sqrt(pow(2, q) * tgamma(q + 1)))) * pow((m * omega) / (M_PI * hbar), 0.25)
            * sqrt(hbar / (m * omega));
    mat A;
    A.load("../code/data/nodes_weights", arma::csv_ascii);
    mat x = A.row(n/5 - 2);    //nodes
    mat w = A.row(n/5 - 1);    //weight

    int i = 0;
    while (i < (int) x.n_cols)
    {
        if (x(i) == 0)
        {
            break;
        }
        i++;
    }

    x.reshape(i,1);
    w.reshape(i,1);


    Hermite hermiteMat = Hermite(std::max(p,q), x); // creates the value of the Hermite polynomial
    hermiteMat.fillPolynomeHermite();
    mat H = w % hermiteMat.getPolynomeMat().col(p) % hermiteMat.getPolynomeMat().col(q);
    return arma::accu(H)*C;
}