/*
 * main.cpp
 */

#include <iostream>
#include "Problem.hpp"
#include "util.h"

using namespace std;

int main(int argc, const char *argv[]) {

    if (argc != 3) {
        cout << "Error: invalid Input arguments" << endl;
        cout << "Use: " << argv[0] << " [inputPath] [outputPath]" << endl;
        return 1;
    }

    /*
     * argv[0] = inputPath
     * argv[1] = outputPath
     */

    int populationDimension = 20;
    int eliteDimension = 5;

    Problem *problem = new Problem(argv[1], argv[2]);
    try {
        problem->load();
        problem->solve(populationDimension, eliteDimension);
        problem->getBestSolution()->print(1);
    }
    catch (Exception exception1) {

    }

    return 0;
}
