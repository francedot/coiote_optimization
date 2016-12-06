//
// Created by Gabriele Mosca on 30/11/16.
//

#include "SimulatedAnnealing.hpp"
#include <math.h>


SimulatedAnnealing::SimulatedAnnealing() {
    maxTemperature = 100;
    currentTemperature = maxTemperature;
}

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

Solution *SimulatedAnnealing::getCurrSolution() {
    return currentSolution;
}

/*
 * This method sets the local variable "currentSolution" to point to the object pointed by
 * the parameter "initialSolution".
 */
void SimulatedAnnealing::setInitialSolution(Solution *initialSolution) {
    currentSolution = initialSolution;
}

/*
 * This method sets the variable "currentTemperature" to the value "maxTemperature".
 */
void SimulatedAnnealing::resetTemperature() {
    currentTemperature = maxTemperature;
}

/*
 * This method runs the instance of the SimulatedAnnealing for "steps" steps.
 * At each steps it calls the function "runStep(...)" that runs the heuristic just once.
 * (After it ends, the caller might decrement the temperature)
 */
void SimulatedAnnealing::run(int keptSolCells, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs,
                             int N, int steps) {
    for (int i = 0; i < steps; i++) {
        runStep(keptSolCells, tasks, sizeOfTasks, people, costs, N);
        currentTemperature -= 5;
    }
}

/*
 * This method runs a single step of the SimulatedAnnealing by generating a neighboor until the selection logic
 * selects and replaces the "currentSolution" of this SimulatedAnnealing instance.
 */
void
SimulatedAnnealing::runStep(int keptSolCells, int *tasks, int sizeOfTasks, int ***people, CostMatrix *costs, int N) {
    Solution *newSol;
    for (int i = 0; i < 20; i++) { // TODO L = 20 (L ha lo stesso significato che nel libro)
        newSol = currentSolution->generateNeighbor(keptSolCells, tasks, sizeOfTasks, people, costs, N);
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