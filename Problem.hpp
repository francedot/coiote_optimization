/*
 * Problem.hpp
 */

#ifndef Problem_hpp
#define Problem_hpp

#include <stdio.h>
#include <iostream>
#include "Solution.hpp"

using namespace std;

class Problem {

public:
    /*
     * todo comments
     */
    Problem(string inputPath, string outputPath);

    void load();

    void writeSolution(bool printScreen);

    int solve(Solution *finalSolution);

private:
    /*
     * todo comments
     */
    string inputPath;
    string outputPath;
    int cellsNumber;
    int periodsNumber;
    int peopleTypes;
    int timesNumber;
    int *totalTasks;
    int *remainingTasks;
    Solution *population;

    int innerSolve(Solution *initialSolution, Solution *finalSolution);

    Solution *generateInitialSolution();
};

#endif /* ProblemData_hpp */
