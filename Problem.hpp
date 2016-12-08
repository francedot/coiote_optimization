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

    Problem(string inputPath, string outputPath);

    Problem(int cellsNumber, int peopleTypes, int timePeriods);

    void load();

    void dummyLoad();

    void printValues(bool screen = 0,
                     string path);                //stampa i valori delle obj function per le soluzioni delle popolazioni evidenziando l'elite

    int solve(int populationDimension, int eliteDimension);

    Solution *getBestSolution();

private:
    /*
     * todo comments
     */
    string inputPath;
    string outputPath;
    int cellsNumber;
    int timePeriods;
    int peopleTypes;
    int *totalTasks;
    Solution *population;
    CostMatrix *costs;
    PeopleMatrix *people;
    Solution *currentBestSolution;

    bool updateElite(SimulatedAnnealing *simAnnealingInstances, int simAnnealingDimension, vector<int> elite,
                     int eliteDim); //return 1 if elite has been updated, 0 otherwise
};

#endif /* ProblemData_hpp */
