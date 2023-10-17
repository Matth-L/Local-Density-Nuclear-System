/**
 * @file schrodingerTest.h
 * @author Matthias Lapu
 * @brief Test class for Schrodinger
 */

#ifndef SCHRODINGERTEST_H
#define SCHRODINGERTEST_H

#include "../code/headers/schrodinger.h"
#include "../code/headers/solutions.h"
#include <cxxtest/TestSuite.h>

using namespace arma;

/**
 * @brief this class tests the Schrodinger equation
 *
 */
class SchrodingerTest : public CxxTest::TestSuite
{
public:
    /**
     * @test This function tests the energy levels
     * of the Schrodinger equation
     * using the formula : E_n = hbar * omega * (n + 1/2)
     * The test is done with different values of hbar and omega (1 and random)
     * and with different values of n
     */
    void testEnergyLevels(void)
    {
        TS_TRACE("Starting energy level test");

        // the energy formula is :
        // E_n = hbar * omega * (n + 1/2)

        // testing for hbar = 1, omega = 1
        TS_TRACE("Starting hbar = 1, omega = 1 test");
        for (int i = 0; i < 25; i++)
        {
            Schrodinger x = Schrodinger();
            TS_ASSERT(x.energyLevels(1, 1, i) == 1 * 1 * (i + 0.5));
        }
        TS_TRACE("Test hbar = 1, omega = 1 is DONE");

        // testing for hbar = random number, omega = random number

        TS_TRACE("Starting hbar = random, omega = random test");
        int hbar = rand() % 100;
        int omega = rand() % 100;

        for (int i = 0; i < 25; i++)
        {
            Schrodinger x = Schrodinger();
            TS_ASSERT(x.energyLevels(hbar, omega, i) == hbar * omega * (i + 0.5));
        }

        TS_TRACE("Test hbar , omega is DONE");
        TS_TRACE("Test is DONE");
    }

    /**
     * @test this function tests the second derivative matrix
     * The test is done by comparing the result of the function
     * with 2 values that were calculated by hand.
     * @warning the tolerance is set to 1e-2
     */
    void testSecondDerivative(void)
    {
        const double tolerance = 1e-2;

        //--------------------------------------------
        TS_TRACE("Starting second derivative test");

        // testing for n=1 , interval = [-1, 1], nodes = 3
        TS_TRACE("Starting n=1 , interval = [-1, 1], nodes = 3 test");
        int n = 1;

        vec test = {-0.591, 0};
        Schrodinger x = Schrodinger();
        Solutions sol = Solutions();
        mat psi = sol.solutions(n, -1, 1, 3);
        mat snd = x.secondDerivative(psi);

        // testing with approximation for all the nodes
        for (int i = 0; i < snd.n_rows - 1; i++)
        {
            TS_ASSERT_DELTA(snd(i, 0), test(i, 0), tolerance);
        }
        TS_TRACE("Test n=1 , interval = [-1, 1], nodes = 3 is DONE");

        //--------------------------------------------

        TS_TRACE("Starting dx test");

        // testing if dx squared is correct
        double dx = 1;
        double dxToTest = psi(0, 1) - psi(0, 0);
        TS_ASSERT_DELTA(dx, dxToTest * dxToTest, tolerance);

        TS_TRACE("Test dx is DONE");

        //--------------------------------------------

        // testing for n=2 , interval = [-1, 1], nodes = 3
        TS_TRACE("Starting n=2 , interval = [-1, 1], nodes = 3 test");
        n = 2;

        vec test2 = {-0.591, 0, 1.7064};

        snd = x.secondDerivative(sol.solutions(n, -1, 1, 3));

        for (int i = 0; i < snd.n_rows - 1; i++)
        {
            TS_ASSERT_DELTA(snd(i, 0), test2(i, 0), tolerance);
        }
        TS_TRACE("Test n=2 , interval = [-1, 1], nodes = 3 is DONE");

        //--------------------------------------------

        TS_TRACE("Second derivative is DONE");
    }

    /**
     * @test this function tests the left part of the Schrodinger equation *
     * psi^-1 with the right part of the Schrodinger equation (the energy)
     * @warning the tolerance is 1e-3 , beyond the test wont pass
     */
    void testEnergyComparison(void)
    {
        TS_TRACE("Starting energyComparison ");
        // left part
        int n = 4;
        int hbar = 1;
        int omega = 1;
        int m = 1;
        double tolerance = 1e-3;

        Solutions solUnit = Solutions(m, hbar, omega);

        TS_TRACE("Building Solution");
        mat res = solUnit.solutions(n, -5, 5, 500);

        Schrodinger x = Schrodinger();

        TS_TRACE("Building Schrodinger");
        mat schrodingerEquation = x.schrodinger1DEquation(res, hbar, omega, m);

        TS_TRACE("Computing energy");

        res.shed_row(0);
        res.shed_col(0);
        res.shed_col(res.n_cols - 1);
        mat energie = schrodingerEquation * pinv(res);
        mat summedEnergie = sum(energie);

        TS_TRACE("Starting Loop");
        for (int i = 0; i < summedEnergie.n_cols - 1; i++)
        {
            // absdiff
            TS_ASSERT_DELTA(summedEnergie(0, i), x.energyLevels(hbar, omega, i),
                            tolerance);
        }
        TS_TRACE("TEST DONE");
    }
};

#endif // SCHRODINGERTEST_H
