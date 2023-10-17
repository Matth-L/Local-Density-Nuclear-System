/**
 * @file hermiteTest.h
 * @author Lapu Matthias
 * @brief the test class for hermite
 */
#ifndef HERMITETEST_H
#define HERMITETEST_H

#include "../code/headers/hermite.h"
#include <armadillo>
#include <cxxtest/TestSuite.h>
using namespace arma;

/**
 * Method to test
 * - the constructor (2 of them)
 * - the setZ method
 * - the getPolynomeMat method
 * - the fillPolynomeHermite method
 */

/**
 * @brief this class tests the hermite's polynome
 *
 */
class HermiteTest : public CxxTest::TestSuite
{
public:
    /**
     * @brief array of values used for testing
     *
     */
    vec input = {2, 3, 4, 5, 6, 7};

    /**
     * @brief N used for testing
     *
     */
    int n = 7;

    /**
     * @brief Second N used for testing
     *
     */
    int secondN = 4;

    /**
     * @brief first object
     *
     */
    Hermite test = Hermite(n, input);
    /**
     * @brief second object (supposed to be the same as the first one)
     *
     */
    Hermite test2 = Hermite(n, 2, 7, 6);
    /**
     * @brief third object with different value than the others
     *
     */
    Hermite testWithRealHermite = Hermite(secondN, {1, 2, 3, 4, 5});

    /**
     * @test this function tests the constructor
     * of the Hermite class
     * it tests each attributes
     */
    void testConstructor(void)
    {
        TS_TRACE("Starting constructor test");

        // test N
        TS_TRACE("Starting N test");
        TS_ASSERT_EQUALS(test.getN(), 7);
        TS_ASSERT_EQUALS(test2.getN(), 7);
        TS_ASSERT_EQUALS(test.getN(), test2.getN());
        TS_TRACE("Test N is DONE");

        // test Z
        TS_TRACE("Starting Z test");
        vec emptyTest = {};

        // empty test
        TS_TRACE("Starting vacuity test");
        TS_ASSERT(size(test.getZ()) != size(emptyTest));
        TS_ASSERT(size(test2.getZ()) != size(emptyTest));
        TS_TRACE("Vacuity test is DONE");

        // size of elements
        TS_TRACE("Starting size test");
        TS_ASSERT((size(test.getZ()) == size(test2.getZ())));
        TS_TRACE("Size test is DONE");

        // test to see if test1 = test 2
        TS_TRACE("Starting equality test");
        TS_ASSERT(arma::all(test.getZ() == test2.getZ()));
        TS_TRACE("Equality test is DONE");

        TS_TRACE("Finishing constructor test");
    };

    /**
     * @test this function tests the filling method of the Hermite class
     * the test is done by comparing the result of the function
     * with values that were calculated by hand.
     * It also compares values with 2 similar objects that were initialized
     * differently
     * @warning the tolerance is set to 1e-6
     */
    void testFill(void)
    {
        const double tolerance = 1e-6;

        //----------------------------------------

        TS_TRACE("Starting fill");
        test.fillPolynomeHermite();
        test2.fillPolynomeHermite();
        testWithRealHermite.fillPolynomeHermite();
        TS_TRACE("filling DONE with test1 and test2");

        //----------------------------------------

        TS_TRACE("Starting comparison test");
        TS_TRACE("Testing with Z = {1,2,3,4,5}");
        mat hermiteMatrix =
        {
            {1, 2, 2, -4, -20},
            {1, 4, 14, 40, 76},
            {1, 6, 34, 180, 876},
            {1, 8, 62, 464, 3340},
            {1, 10, 98, 940, 8812},
        };

        mat hermiteFetch = testWithRealHermite.getPolynomeMat();

        // Vérifiez si les deux matrices sont approximativement égales
        TS_ASSERT(
            arma::approx_equal(hermiteMatrix, hermiteFetch, "absdiff", tolerance));

        TS_TRACE("Comparison test DONE with theorical values");

        //----------------------------------------

        // testing if the first values is a col of 1 for test1 and test 2
        // this test is now useless, because we test all the value in the next test
        TS_TRACE("Starting first column test");
        TS_ASSERT(arma::all(test.getPolynomeMat().col(0) == 1));
        TS_ASSERT(arma::all(test2.getPolynomeMat().col(0) == 1));
        TS_ASSERT(arma::all(test.getPolynomeMat().col(0) ==
                            test2.getPolynomeMat().col(0)));
        TS_TRACE("first column test DONE");

        //----------------------------------------

        // testing if all the values are the same for test1 and test 2, due to
        // floating point error, we use a tolerance
        TS_TRACE("Starting comparison test between similar object");
        for (int i = 0; i < test.getN(); i++)
        {
            TS_ASSERT(arma::approx_equal(test.getPolynomeMat().col(i),
                                         test2.getPolynomeMat().col(i), "absdiff",
                                         tolerance));
        }
        TS_TRACE("Comparison test DONE");
        TS_TRACE("Starting comparison test with true value ");
        TS_TRACE("Comparison test DONE");
    };
};

#endif
