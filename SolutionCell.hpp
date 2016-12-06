/*
 * SolutionCell.hpp
 */

#ifndef SolutionCell_hpp
#define SolutionCell_hpp

#include "SolutionCell.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

class SolutionCell {

public:
    /*
     * todo comments
     */
    SolutionCell(int i, int j, int m, int t, int x);

    SolutionCell *clone();

    int getI();

    int getJ();

    int getType();

    int getTime();
    int getX();

    int setX(int x);

    int setI(int i);

    int setJ(int j);

    int setType(int m);

    int setTime(int t);

    void print(bool screen = 0, std::string path);

private:
    /*
     * todo comments
     */
    int i, j;
    int m;
    int x;
    int t;
};

#endif /* SolutionCell_hpp */
