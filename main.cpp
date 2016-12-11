/*
 * main.cpp
 */

#include "Problem.hpp"
#include "config.h"

using namespace std;

/*
 * CONFIGURATIONS
 * parameters whose name starts with _ come from file "config.h"
 */

int main(int argc, const char *argv[]) {

    if (argc != 3) {
        cout << "Error: invalid Input arguments" << endl;
        cout << "Use: " << argv[0] << " [inputPath] [outputPath]" << endl;
        return 1;
    }

    // todo x francesco: blocco try catch
    cout << "Creating Problem\n";


    /*
     * temporary constructor (without file loader)
     */
//    int cellsNumber, peopleTypes, timePeriods;
//    cellsNumber = 30;
//    peopleTypes = 3;
//    timePeriods = 20;
//    Problem *problem = new Problem(cellsNumber, peopleTypes, timePeriods);


    /*
     * argv[1] = inputPath
     * argv[2] = outputPath
     */
    Problem *problem = new Problem(argv[1], argv[2]);
    problem->solve(_populationDimension, _eliteDimension);
    cout << "Problem probably solved\n";
    problem->getBestSolution()->print(1, NULL);

    return 0;
}
