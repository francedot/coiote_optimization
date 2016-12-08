/*
 * main.cpp
 */

#include <iostream>
#include "Problem.hpp"
#include "util.hpp"

using namespace std;

int main(int argc, const char *argv[]) {

//    if (argc != 3) {
//        cout << "Error: invalid Input arguments" << endl;
//        cout << "Use: " << argv[0] << " [inputPath] [outputPath]" << endl;
//        return 1;
//    }

    /*
     * argv[1] = inputPath
     * argv[2] = outputPath
     */

    int cellsNumber = 30;
    int peopleTypes = 3;
    int timePeriods = 10;

    int populationDimension = 20;
    int eliteDimension = 5;

//    Problem *problem = new Problem(argv[1], argv[2]);
//    try {
    Problem *problem = new Problem(cellsNumber, peopleTypes, timePeriods);
    problem->dummyLoad();
    problem->solve(populationDimension, eliteDimension);
    problem->getBestSolution()->print(1, NULL);
//    }
//    catch (Exception exception1) {
//
//    }

    return 0;
}
