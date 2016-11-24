/*
 * SolutionCell.hpp
 */

#ifndef SolutionCell_hpp
#define SolutionCell_hpp

#include <stdio.h>
#include <stdlib.h>

class SolutionCell {
    public:
        /*
         * TODO WRITE DESCRIPTION HERE
         */
        SolutionCell(int i, int j, int m, int t, int x);

        /*
         * GETTERS
         */
        int getI();
        int getJ();
        int getType();
        int getTime();

    int getX();

        /*
         * SETTERS
         */
        int setI();
        int setJ();
        int setType();
        int setTime();
        void printCell();

    private:
        /*
         * source (i) and destination (j) of the move
         */
        int i, j;

        /*
         * type of user asked to move
         */
        int type;

        /*
         * number of users with same characteristics asked to move
         */
        int x;

        /*
         * time period of the move
         */
        int t;
};

#endif /* SolutionCell_hpp */
