//
// Created by Gabriele Mosca on 30/11/16.
//

#include "SimulatedAnnealing.hpp"
#include <math.h>


SimulatedAnnealing::SimulatedAnnealing(Solution *initialSolution) {
    currentSolution = initialSolution;
    maxTemperature = 100;
    currentTemperature = maxTemperature;
}

SimulatedAnnealing::SimulatedAnnealing(Solution *initialSolution, int maxTemperature) {
    currentSolution = initialSolution;
    this->maxTemperature = maxTemperature;
    currentTemperature = maxTemperature;
}

void
SimulatedAnnealing::run(int kept, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N, int steps) {
    for (int i = 0; i < steps; i++) {
        runStep(kept, tasks, sizeOfTasks, people, costs, N);
        currentTemperature -= 10;
    }
}

void SimulatedAnnealing::runStep(int kept, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N) {
    Solution *newSol;
    for (int i = 0; i < 20; i++) { // TODO L = 20 (L ha lo stesso significato che nel libro)
        newSol = currentSolution->generateNeighbor(kept, tasks, sizeOfTasks, people, costs, N);
        int difference = newSol->evaluate() - currentSolution->evaluate();
        if (difference <= 0) {
            delete currentSolution;
            currentSolution = newSol;
        } else {
            double r = ((double) rand()) / RAND_MAX;
            if (r >= exp(-((double) difference) / currentTemperature)) {
                // TODO: implementare distribuzione esponenziale
                delete currentSolution;
                currentSolution = newSol;
            }
        }
    }
}