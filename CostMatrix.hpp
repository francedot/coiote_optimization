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

    CostMatrix();
    /*
     * todo comments
     */

    struct CostCoordinates {
        int i;
        int m;
        int t;
    } typedef CostCoordinates;

    CostMatrix(int cellsNumber, int periodsNumber, int peopleTypes);

    int loadMatrix();

    void getMinimumCost(int j, int *i, int *m, int *t, int ***people, int tSize, int mSize, int iSize);

    vector<CostMatrix::CostCoordinates> *
    getMinimumTaskCost(int j, int remainingTasksForJ, int ***people, int tSize, int mSize, int iSize);

    vector<CostMatrix::CostCoordinates> *
    getMinimumTaskCostDiversified(int j, int remainingTasksForJ, int ***people, int tSize, int mSize, int iSize);

    int getCost(int j, int i, int m, int t);

private:
    /*
     * todo comments
     */
    int dim;
    int ****costs;
    double *averageCosts; // Array of size N of avg costs
};

#endif /* CostMatrix_hpp */
