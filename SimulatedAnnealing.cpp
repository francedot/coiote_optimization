//
// Created by Gabriele Mosca on 30/11/16.
//

#include "SimulatedAnnealing.hpp"
#include <math.h>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing() {
    maxTemperature = 100;
    currentTemperature = maxTemperature;
    invariantCellsOfNeighborhoodPercentage = 20;
}

SimulatedAnnealing::SimulatedAnnealing(Solution *initialSolution) {
    currentSolution = initialSolution;
    maxTemperature = 100;
    currentTemperature = maxTemperature;
    invariantCellsOfNeighborhoodPercentage = 20;
}

SimulatedAnnealing::SimulatedAnnealing(Solution *initialSolution, int maxTemperature) {
    currentSolution = initialSolution;
    this->maxTemperature = maxTemperature;
    currentTemperature = maxTemperature;
    invariantCellsOfNeighborhoodPercentage = 20;
}

void SimulatedAnnealing::decreaseKeptCellsPercentage() {
    if (invariantCellsOfNeighborhoodPercentage < 80)
        invariantCellsOfNeighborhoodPercentage += 15;
}

int SimulatedAnnealing::getInvariantCellsOfNeighborhoodPercentage() {
    return invariantCellsOfNeighborhoodPercentage;
}

void SimulatedAnnealing::resetInvariantCellsOfNeighborhoodPercentage() {
    invariantCellsOfNeighborhoodPercentage = 20;
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
void
SimulatedAnnealing::run(double keptSolCellsPercentage, int *tasks, int sizeOfTasks, PeopleMatrix *people,
                        CostMatrix *costs,
                        int N, int steps) {
    //std::cout << "run(...) called" << std::endl;
    for (int step = 0; step < steps; step++) {
        runStep(keptSolCellsPercentage, tasks, sizeOfTasks, people, costs, N);
        currentTemperature *= 0.95;
    }
}

/*
 * This method runs a single step of the SimulatedAnnealing by generating a neighboor until the selection logic
 * selects and replaces the "currentSolution" of this SimulatedAnnealing instance.
 */
void
SimulatedAnnealing::runStep(double keptSolCellsPercentage, int *tasks, int sizeOfTasks, PeopleMatrix *people,
                            CostMatrix *costs,
                            int N) {
    //std::cout << "runStep(...) called" << endl;
    Solution *newSol;
    for (int instance = 0; instance < 20; instance++) { // TODO L = 20 (L ha lo stesso significato che nel libro)
        newSol = currentSolution->generateNeighbor(keptSolCellsPercentage, tasks, sizeOfTasks, people, costs, N);

        int difference = newSol->evaluate() - currentSolution->evaluate();
        if (difference <= 0) {
            currentSolution = newSol;
        } else {
            double r = ((double) rand()) / RAND_MAX;
            if (r >= exp(-((double) difference) / currentTemperature)) {
                // TODO: implementare distribuzione esponenziale
                currentSolution = newSol;
            }
        }
    }
    //cout << "new current: " << currentSolution->evaluate() << endl;
}