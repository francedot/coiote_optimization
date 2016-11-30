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
using namespace std;

class Problem {

public:
    /*
     * todo comments
     */
    Problem(string inputPath, string outputPath);

    void load();

    void writeSolution(bool printScreen);

    int solve(Solution *finalSolution, int populationDimension);

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


    int innerSolve(Solution *initialSolution, Solution *finalSolution);

    Solution *generateInitialSolution();
};

#endif /* ProblemData_hpp */
