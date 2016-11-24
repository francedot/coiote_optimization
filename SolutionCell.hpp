/*
 * SolutionCell.hpp
 */

#ifndef SolutionCell_hpp
#define SolutionCell_hpp

#include "SolutionCell.hpp"
#include <stdio.h>
#include <stdlib.h>

class SolutionCell {

public:
    /*
     * todo comments
     */
    SolutionCell(int i, int j, int m, int t, int x);

    void printCell();

    int getI();

    int getJ();

    int getType();

    int getTime();
    int getX();

    int setX();

    int setI();

    int setJ();

    int setType();

    int setTime();

private:
    /*
     * todo comments
     */
    int i, j;
    int type;
    int x;
    int t;
};

#endif /* SolutionCell_hpp */
