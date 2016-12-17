//
// Created by Gabriele Mosca on 30/11/16.
//

#ifndef COIOTE_PROJECT_SIMULATEDANNEALING_HPP
#define COIOTE_PROJECT_SIMULATEDANNEALING_HPP

#include "Solution.hpp"

class SimulatedAnnealing {

public:
    SimulatedAnnealing();

    SimulatedAnnealing(Solution *initialSolution);

    SimulatedAnnealing(Solution *initialSolution, int maxTemperature);

    Solution *getCurrSolution();

    void setInitialSolution(Solution *initialSolution);

    void resetTemperature();

    void runStep(double keptSolCells, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N);

    void
    run(double keptSolCells, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N, int steps);

    void decreaseKeptCellsPercentage();

    int getInvariantCellsOfNeighborhoodPercentage();

    void resetInvariantCellsOfNeighborhoodPercentage();

private:
    int currentTemperature;
    int maxTemperature = 100;
    Solution *currentSolution;
    double invariantCellsOfNeighborhoodPercentage;
};


#endif //COIOTE_PROJECT_SIMULATEDANNEALING_HPP
