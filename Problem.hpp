//
//  ProblemData.hpp
//  ProvaOpt
//
//  Created by Gabriele Mosca on 17/11/16.
//  Copyright © 2016 Gabriele Mosca. All rights reserved.
//

#ifndef Problem_hpp
#define Problem_hpp

#include <stdio.h>
#include <iostream>
#include "Solution.hpp"

using namespace std;

class Problem {
public:
    Problem(string inputPath, string outputPath);

    int load();

    void writeSolution(bool printScreen);

    int
    solve(Solution *finalSolution);                                 //generate initial solution and solve the problem running innerSolve
private:

    int innerSolve(Solution *initialSolution, Solution *finalSolution); //uses the heuristic
    Solution *generateInitialSolution();

    string inputPath;
    string outputPath;

    Solution *population;
    int cellsNumber;
    int usersTypeNumber;
    int timesNumber;
    int *tasks;
    int *taskAtRuntime;
};

#endif /* ProblemData_hpp */
