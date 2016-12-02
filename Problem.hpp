/*
 * Problem.hpp
 */

#ifndef Problem_hpp
#define Problem_hpp

#include <stdio.h>
#include <iostream>
#include "Solution.hpp"
#include "PeopleMatrix.hpp"
#include "SimulatedAnnealing.hpp"
#include "ExceptionManager.h"
using namespace std;

class Problem {

public:
    /*
     * todo comments
     */
    Problem(string inputPath, string outputPath);

    void load();

    void writeSolution(bool printScreen);

    int solve(Solution *finalSolution, int populationDimension, int eliteDimension);

private:
    /*
     * todo comments
     */
    string inputPath;
    string outputPath;
    int cellsNumber;
    int periodsNumber;
    int peopleTypes;
    int *totalTasks;
    Solution *population;
    CostMatrix *costs;
    PeopleMatrix *people;
    Solution *currentBestSolution;


    int innerSolve(Solution *initialSolution, Solution *finalSolution);

    Solution *generateInitialSolution();

    bool updateElite(SimulatedAnnealing *simAnnealingInstances, int simAnnealingDimension, vector<int> elite,
                     int eliteDim); //return 1 if elite has been updated, 0 otherwise
};

#endif /* ProblemData_hpp */
