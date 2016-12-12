/*
 * Problem.hpp
 */

#ifndef Problem_hpp
#define Problem_hpp

#include <iostream>
#include <fstream>
#include <sstream>

#include "Solution.hpp"
#include "PeopleMatrix.hpp"
#include "SimulatedAnnealing.hpp"
#include "ExceptionManager.h"

using namespace std;

class Problem {

public:
    Problem(string inputPath, string outputPath);

    Problem(int cellsNumber, int peopleTypes, int timePeriods);
    void dummyLoad();

    //stampa i valori delle obj function per le soluzioni delle popolazioni evidenziando l'elite
    void printValues(bool screen = 0, string path = "");

    int solve(int populationDimension, int eliteDimension);

    Solution *getBestSolution();

private:
    string inputPath;
    string outputPath;

    int cellsNumber;        // number of cells of the matrix where people moves
    int timePeriods;        // number of time periods considered while people moves into the matrix
    int peopleTypes;        // number of different types of people moving into the matrix
    int *tasksUserCanDo;    // contains the number of task that each type of user can do (dim: peopleTypes)
    int *totalTasks;        // contains the number of task to do in each cell of the matrix (dim: cellsNumber)

    // it defines the cost for making a person of type [m] (0 - peopleTypes) at time [t] (0 - timePeriods) move from
    // cell [i] (0 - cellsNumber) to cell [j] (0 - cellsNumber)
    CostMatrix *costs;

    // it defines the number of people of type [m] (0 - peopleTypes) staring in each cell [i] (0 - cellsNumber) at time
    // t (0 - timePeriods)
    PeopleMatrix *people;

    SimulatedAnnealing *simAnnealings;

    Solution *currentBestSolution;

    void printInputFileRead();
    void load();
    //return 1 if elite has been updated, 0 otherwise
    bool
    updateElite(SimulatedAnnealing *simAnnealingInstances, int simAnnealingDimension, vector<int> *elite, int eliteDim);
};

#endif /* ProblemData_hpp */
