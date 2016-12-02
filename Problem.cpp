/*
 * Problem.cpp
 */

#include "Problem.hpp"
#include <fstream>
#include <sstream>

using namespace std;

/*
 * get inputPath and outputPath from command line
 */
Problem::Problem(string inputPath, string outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}


/*
 * load Input file
 */
void Problem::load() {
    string line; // contains a line of the Input file
    string word; // contains a single word (into a line)

    // open Input file
    ifstream inputFileStream(Problem::inputPath.c_str());

    if (!inputFileStream.is_open()) {
        // todo lancia eccezione
        throw new Exception("Error: unable to open " + Problem::inputPath);
    }

    /*
     * read first line: cellsNumber periodsNumber peopleTypes
     */
    getline(inputFileStream, line);
    istringstream inputStringStream(line);

    inputStringStream >> word;

    return;
}

/*
 * todo comments
 */
void Problem::writeSolution(bool printScreen) {
    
}

/*
 * generate initial solution and solve the problemi with population-based simulated annealing
 * Parameters meaning explained in-line
 */
int Problem::solve(Solution *finalSolution, int populationDimension, int eliteDimension) {

    Solution *initialSolution;
    vector<int> eliteIndexes;                       //The elite is an vector of the indexes of the best solution
    bool flag;                                      //Flag used to distinguish solutions in the elite
    int invariantCellsOfNeighborhood = 5;           //This is the number of cells invariant in the generation of neighborhood
    int stepsPerWave = 2;                           //A step means a decrement of temperature
    int stableWaves = 0;                            //Parameter necessary to stop the algorithm
    int maxStableWaves = 10;                        //Parameter necessary to stop the algorithm

    initialSolution->generateInitialSolution(totalTasks, cellsNumber, people->getPeopleMatrix(), costs, cellsNumber);
    currentBestSolution = initialSolution;          //at the beginning the best solution is the initial solution

    /*
     * below a population of instances of standard Simulation Annealing is declared, each one with his current solution stored inside,
     * provided in the first wave of the algorithm by making a copy (with copy-constructor) of the initial solution generated above;
     */
    SimulatedAnnealing simAnnealings[populationDimension];

    //First wave is performed separatly to be able to assign each instance of Simulated Annealing his own starting solution
    for (int i = 0; i < populationDimension; i++) {
        simAnnealings[i].setInitialSolution(new Solution(*initialSolution));
        simAnnealings[i].resetTemperature();                                                //temperature set to max
        simAnnealings[i].run(invariantCellsOfNeighborhood, totalTasks, cellsNumber,
                             people->getPeopleMatrix(), costs, cellsNumber, stepsPerWave);
    }
    updateElite(simAnnealings, populationDimension, eliteIndexes, eliteDimension);
    //end of first wave, the elite contains the best solutions up to now

    //successive waves, the cycle is stopped when the best solution has not been updated for "maxStableWaves" consecutive waves
    while (stableWaves < maxStableWaves) {
        for (int i = 0; i < populationDimension; i++) {
            flag = false;
            for (int j = 0; j < eliteDimension; j++)
                if (i = eliteIndexes[j]) flag = 1;       //checking if this solution is part of the elite

            if (flag) {     //if the Solution belongs to the elite the Simulated Annealing simply resume from the point it left
                simAnnealings[i].run(invariantCellsOfNeighborhood, totalTasks, cellsNumber,
                                     people->getPeopleMatrix(), costs, cellsNumber, stepsPerWave);
            } else {          //if the Solution doesn't belongs to the elite it restart at max temperatur with currentBestSolution as starting Solution
                simAnnealings[i].setInitialSolution(new Solution(*currentBestSolution));
                simAnnealings[i].resetTemperature();
                simAnnealings[i].run(invariantCellsOfNeighborhood, totalTasks, cellsNumber,
                                     people->getPeopleMatrix(), costs, cellsNumber, stepsPerWave);
            }
        }//end of wave;
        if (updateElite(simAnnealings, populationDimension, eliteIndexes, eliteDimension)) {
            stableWaves = 0;
        } else stableWaves++;
    }
    return 0;
}

/*
 *      This method updates the elite with the current best solutions found after a new wave of the algorithm.
 *      It eventually also update the general current Best Solution of the Problem
 *
 *      Parameters:
 *      simAnnealingInstances -> this parameter is required to have access to all current solutions in the population and their evaluations
 *      elite -> this is a vector storing the indexes in simAnnealingInstances of the members of the elite.
 *      using std::vector for a better implementation of insertion sort
 *
 *      This method return true if the best solution of the problem has been updated. False otherwise
 */
bool Problem::updateElite(SimulatedAnnealing *simAnnealingInstances, int simAnnealingDimension, vector<int> elite,
                          int eliteDim) {
    vector<int>::iterator it;
    bool flag = 0;
    for (int i = 0; i < simAnnealingDimension; i++) {
        for (it = elite.begin(); it < elite.end(); it++) {
            if (simAnnealingInstances[i].getCurrSolution()->evaluate() <
                simAnnealingInstances[*it].getCurrSolution()->evaluate()) {
                elite.insert(it - 1, i);
                while (elite.size() > eliteDim)
                    elite.pop_back();    //riporta la dimensione dell'elite a quella corretta
            }
        }
    }
    //checking if current best solution has to be updated.
    if (simAnnealingInstances[elite[0]].getCurrSolution()->evaluate() < currentBestSolution->evaluate()) {
        currentBestSolution = simAnnealingInstances[elite[0]].getCurrSolution();
        flag = true;
    }
    return flag;
}


