/*
 * main.cpp
 */

#include "Problem.hpp"
#include <ctime>

using namespace std;

int _populationDimension = 20;
int _eliteDimension = 4;

/*
 * CONFIGURATIONS
 * parameters whose name starts with _ come from file "config.h"
 */

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        cout << "Error: invalid Input arguments" << endl;
        cout << "Use: " << argv[0] << " [inputPath] [outputPath]" << endl;
        return 1;
    }
    // todo x francesco: blocco try catch
    cout << "Creating Problem\n";
    /*
     * temporary constructor (without file loader)
     */
//    int cellsNumber, peopleTypes, timePeriods;
//    cellsNumber = 30;
//    peopleTypes = 3;
//    timePeriods = 20;
//    Problem *problem = new Problem(cellsNumber, peopleTypes, timePeriods);
    /*
     * argv[1] = inputPath
     * argv[2] = outputPath
     */
    time_t begin, end;
    Problem *problem = new Problem(argv[1], argv[2]);
    time(&begin);
    problem->solve(_populationDimension, _eliteDimension);
    time(&end);
    cout << "Progam ended. \nProblem probably solved\n" << endl;
    double difference = difftime(end, begin);
    printf("time taken for function solve %.2lf seconds.\n", difference);
    cout << "Final best cost found: " << problem->getBestSolution()->evaluate() << endl;
    for (int i = 0; i < problem->getBestSolution()->getSize(); i++) {
        problem->getBestSolution()->getCell(i)->print(1);
    }
    problem->getBestSolution()->printForTypes();
    return 0;
}
