/*
 * SolutionCell.cpp
 */

#include "SolutionCell.hpp"

/*
 * todo comments
 */
SolutionCell::SolutionCell(int i, int j, int m, int t, int x) {
    this->i = i;
    this->j = j;
    this->type = m;
    this->t = t;
    this->x = x;
}

SolutionCell *SolutionCell::clone() {
    return new SolutionCell(i, j, type, t, x);
}

/*
 * todo comments
 */
int SolutionCell::getI() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::getJ() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::getType() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::getTime() {
    return 0;
}

int SolutionCell::getX() {
    return x;
}

/*
 * todo comments
 */
int SolutionCell::setX() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::setI() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::setJ() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::setType() {
    return 0;
}

/*
 * todo comments
 */
int SolutionCell::setTime() {
    return 0;
}

/*
 * todo comments
 */
void SolutionCell::printCell() {

}
