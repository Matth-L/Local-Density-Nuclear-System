/**
 * @file solutionsTest.h
 * @author Lapu Matthias
 * @brief Test class for Solutions
 */

#ifndef SOLUTIONSTEST_H
#define SOLUTIONSTEST_H

#include "../code/headers/solutions.h"
#include <cxxtest/TestSuite.h>
using namespace arma;

/**
 * @brief this class tests the Solutions class
 *
 */
class SolutionsTest : public CxxTest::TestSuite
{
public:
    /**
     * @brief first object, all parameters are supposed to be 1
     *
     */
    Solutions x1 = Solutions();

    /**
     * @brief second object (supposed to be the same as the first one)
     *
     */
    Solutions x2 = Solutions(1, 1, 1);

    /**
     * @brief third object, with different units
     *
     */
    Solutions x3 = Solutions(2, 9, 5);

    /**
     * @test this function tests the constructor
     * of the Solutions class.
     * With 3 different Solutions objects.
     */
    void testConstructorSolutions(void)
    {
        TS_TRACE("Starting test");

        // testing the values inside the constructor
        // and between the constructors

        // test m
        TS_TRACE("Starting M test");
        TS_ASSERT(x1.getM() == 1);
        TS_ASSERT(x2.getM() == 1);
        TS_ASSERT(x2.getM() == x1.getM());
        TS_ASSERT(x2.getM() != x3.getM());
        TS_TRACE("Test M is DONE");

        // test hbar
        TS_TRACE("Starting Hbar test");
        TS_ASSERT(x1.getHbar() == 1);
        TS_ASSERT(x2.getHbar() == 1);
        TS_ASSERT(x2.getHbar() == x1.getHbar());
        TS_ASSERT(x2.getHbar() != x3.getHbar());
        TS_TRACE("Test Hbar is DONE");

        // test omega
        TS_TRACE("Starting Omega test");
        TS_ASSERT(x1.getOmega() == 1);
        TS_ASSERT(x2.getOmega() == 1);
        TS_ASSERT(x2.getOmega() == x1.getOmega());
        TS_ASSERT(x2.getOmega() != x3.getOmega());
        TS_TRACE("Test Omega is DONE");

        TS_TRACE("Test is DONE");
    }

    /**
     * @test this function tests the orthonormality
     * with 3 different Solutions objects.
     * It tests the orthonormality of the first 24 polynomes
     * if i == j then the result should be 1
     * Otherwise it should be 0
     * @warning the delta is 1e-6
     */
    void testOrthonormality(void)
    {
        const double delta = 1e-6;
        TS_TRACE("Starting orthonormality test");

        // if i == j then the result should be 1
        // otherwise it should be 0
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                double a = x1.verifOrthonormality(i, j);
                double b = x2.verifOrthonormality(i, j);
                double c = x3.verifOrthonormality(i, j);
                if (i == j)
                {
                    TS_ASSERT_DELTA(a, 1, delta);
                    TS_ASSERT_DELTA(b, 1, delta);
                    TS_ASSERT_DELTA(c, 1, delta);
                }
                else
                {
                    TS_ASSERT_DELTA(a, 0, delta);
                    TS_ASSERT_DELTA(b, 0, delta);
                    TS_ASSERT_DELTA(c, 0, delta);
                }
            }
        }
        TS_TRACE("Orthonormality is DONE");
    }
};

#endif // SOLUTIONSTEST_H
