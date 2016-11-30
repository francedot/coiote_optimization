//
// Created by Gabriele Mosca on 30/11/16.
//

#ifndef COIOTE_PROJECT_SIMULATEDANNEALING_HPP
#define COIOTE_PROJECT_SIMULATEDANNEALING_HPP

#include "Solution.hpp"

class SimulatedAnnealing {
public:
    SimulatedAnnealing(Solution *initialSolution);

    SimulatedAnnealing(Solution *initialSolution, int maxTemperature);

    void runStep(int kept, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N);

    void run(int kept, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N, int steps);

private:
    int currentTemperature;
    int maxTemperature = 100;
    Solution *currentSolution;
};


#endif //COIOTE_PROJECT_SIMULATEDANNEALING_HPP
