#include "../headers/hermite.h"
#include "../headers/solutions.h"
using namespace arma;

int main()
{
  Solutions sol = Solutions();
  mat res = sol.solutions(2, -10, 10, 100);
  res.print("result");

  // arma::vec input = {2, 3, 4, 5, 6, 7};
  // Hermite test = Hermite(7, input);
  // test.fillPolynomeHermite();

  // arma::mat Result = test.getPolynomeMat();
  // Result.print("result");

  res.save("../bin/test.csv", csv_ascii);
  return 0;
}
