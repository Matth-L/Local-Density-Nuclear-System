#include "naive.cxx"
#include "v1.cxx"
#include "v2.cxx"
#include "v3.cxx"
#include "v4.cxx"
#include "v5.cxx"
#include <iostream>
#include <armadillo>
#include <array>

using namespace arma;

int main(int argc, char const *argv[])
{
    cout << "Benchmarking..." << endl;
    // on compte le nombre d'arguments
    int count = 0;
    while (argv[++count] != NULL)
        ;
    // si le nombre d'arguments est différent de 2, on fait 1 test
    int numberToDo = 1;
    if (count != 2)
    {
        cout << "Usage: ./benchmark <number of tests>" << endl;
        cout << "the number of tests is set to 1" << endl;
    }
    else
        numberToDo = atoi(argv[1]);

    // argc correspond au nombre de fois que chaque test sera effectué
    vec timeVect = zeros(6);

    // on effectue chaque test argc fois, et on somme les temps d'exécution
    // chaque case correspond à un test
    for (int i = 0; i < numberToDo; i++)
    {
        timeVect(0) += naive();
        cout << "naive done" << endl;
        timeVect(1) += v1();
        cout << "v1 done" << endl;
        timeVect(2) += v2();
        cout << "v2 done" << endl;
        timeVect(3) += v3();
        cout << "v3 done" << endl;
        timeVect(4) += v4();
        cout << "v4 done" << endl;
        timeVect(5) += v5();
        cout << "v5 done" << endl;
    }
    // on calcule la moyenne des temps d'exécution
    timeVect /= numberToDo;
    timeVect.save("./benchmark.csv", csv_ascii);

    return EXIT_SUCCESS;
}