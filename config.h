/*
 * config.h
 */

#ifndef config_h
#define config_h

#include <string>
#include "Problem.hpp"

int populationSize;
int eliteSize;


typedef struct problemData {
    string inputPath;
    string outputPath;
    int cellsNumber;
    int periodsNumber;
    int peopleTypes;
    int timesNumber;
    int *totalTasks;
    Solution *population;
} ProblemData;

problemData *probData() {
    problemData *probData = new problemData();
    // TODO:
    probData->cellsNumber = 5;


}


#endif /* config_h */
