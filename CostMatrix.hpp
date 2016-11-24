/*
 * CostMatrix.hpp
 */

#ifndef CostMatrix_hpp
#define CostMatrix_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class CostMatrix {
    public:
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        CostMatrix(int dim);

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int loadMatrix(istream inputFile);
        // TODO check why it makes the build fail


    private:
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int dim;

        /*
         * TODO WRITE DESCRIPTION HERE
         */
        int **costs;
};

#endif /* CostMatrix_hpp */
