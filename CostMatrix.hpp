/*
 * CostMatrix.hpp
 */

#ifndef CostMatrix_hpp
#define CostMatrix_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "PeopleMatrix.hpp"

using namespace std;

class CostMatrix {

public:
    /*
     * The following struct contains the four coordinates of an element of the costs matrix.
     * It is used as a return type for the vector of coordinates of least cost for a certain task cells.
     */
    struct CostCoordinates {
        int j;
        int i;
        int m;
        int t;
    } typedef CostCoordinates;

    CostMatrix(int cellsNumber, int periodsNumber, int peopleTypes);
    int load(ifstream *inputFileStream);

//    void getMinimumCost(int j, int *i, int *m, int *t, int ***people, int tSize, int mSize, int iSize);

    vector<CostMatrix::CostCoordinates> *getMinimumTaskCost(int j, int remainingTasksForJ, PeopleMatrix *people);

    vector<CostMatrix::CostCoordinates> *getMinimumTaskCostDiversified(int j, int remainingTasksForJ, PeopleMatrix *people);

    CostCoordinates *
    getMinimumCost(int j, PeopleMatrix *people, int *remainingtasks, int cellsNumber, int peopleTypes, int timePeriods);

    CostCoordinates *
    getMinimumCostByDistanceFromJ(int j, PeopleMatrix *people, int *remainingtasks, int cellsNumber, int peopleTypes,
                                  int timePeriods);

    void setValue(int j, int i, int m, int t, int value);

    int getCost(int j, int i, int m, int t);

    int getAvgCostsPerTask(int j);

    void updateAvgCostsPerTask(int j, double newValue, long index);

    int ****getMatrix();

//    int getSize();

    void print();

private:
    int ****costs;                  // Indexes are j, i, m, t, in this order
    int cellsNumber;                // Number of cells
    int timePeriods;                // Number of time periods
    int peopleTypes;                // Number of types of people
    double *averageCostsPerTask;    // Array of size N of avg costs. See "updateAverageCostsPerTask()" for more info
    double *stdvCostsPerTask;       // todo description
};

#endif /* CostMatrix_hpp */
