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
         * TODO WRITE DESCRIPTION HERE
         */
        Problem(string inputPath, string outputPath);

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int load();

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        void writeSolution(bool printScreen);

        /*
         * generate initial solution and solve the problem running innerSolve
         */
        int solve(Solution *finalSolution);

    private:
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        string inputPath;
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        string outputPath;

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int cellsNumber;

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int usersTypeNumber;

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int timesNumber;

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int *totalTasks;

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int *remainingTasks;

        /*
         * WRITE DESCRIPTION HERE
         */
        Solution *population;

        /*
         * uses the heuristic
         */
        int innerSolve(Solution *initialSolution, Solution *finalSolution);

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        Solution *generateInitialSolution();
};

#endif /* ProblemData_hpp */
