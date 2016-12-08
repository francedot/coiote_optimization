/*
 * CostMatrix.hpp
 */

#ifndef CostMatrix_hpp
#define CostMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

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

    int loadMatrix(istream inputFile);

//    void getMinimumCost(int j, int *i, int *m, int *t, int ***people, int tSize, int mSize, int iSize);

    vector<CostMatrix::CostCoordinates> *
    getMinimumTaskCost(int j, int remainingTasksForJ, int ***people);

    vector<CostMatrix::CostCoordinates> *
    getMinimumTaskCostDiversified(int j, int remainingTasksForJ, int ***people);

    int getCost(int j, int i, int m, int t);

//    int getSize();

    int getAvgCostsPerTask(int j);

    int ****getMatrix();

    void setValue(int j, int i, int m, int t, int value);

    void updateAvgCostsPerTask(int j, int newValue, long index);

private:
    /*
     * todo comments
     */
    int ****costs;                  // Indexes are j, i, m, t, in this order
    int cellsNumber;                // Number of cells
    int timePeriods;                // Number of time periods
    int peopleTypes;                // Number of types of people
    double *averageCostsPerTask;    // Array of size N of avg costs. See "updateAverageCostsPerTask()" for more info
    double *stdvCostsPerTask;
};

#endif /* CostMatrix_hpp */
