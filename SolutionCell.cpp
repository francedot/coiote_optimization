/*
 * SolutionCell.cpp
 */

#include <iomanip>
#include "SolutionCell.hpp"

using namespace std;

/*
 * todo comments
 */
SolutionCell::SolutionCell(int i, int j, int m, int t, int x) {
    this->i = i;
    this->j = j;
    this->m = m;
    this->t = t;
    this->x = x;
}

SolutionCell::SolutionCell(const SolutionCell &toCopy) {
    i = toCopy.i;
    j = toCopy.j;
    m = toCopy.m;
    t = toCopy.t;
    x = toCopy.x;
}

/*
 * GETTERS
 */
int SolutionCell::getX() {
    return x;
}

int SolutionCell::getI() {
    return i;
}

int SolutionCell::getJ() {
    return j;
}

int SolutionCell::getType() {
    return m;
}

int SolutionCell::getTime() {
    return t;
}

/*
 * SETTERS
 */
int SolutionCell::setX(int x) {
    this->x = x;
    return x;
}

int SolutionCell::setI(int i) {
    this->i = i;
    return i;
}

int SolutionCell::setJ(int j) {
    this->j = j;
    return j;
}

int SolutionCell::setType(int m) {
    this->m = m;
    return m;
}

int SolutionCell::setTime(int t) {
    this->t = t;
    return t;
}

/*
 * todo comments
 */
void SolutionCell::print(bool screen, string path) {
    if (screen) {
        cout << "i = " << setw(4) << i << "; j = " << setw(4) << j << "; m = " << setw(4) << m << "; t = " << setw(4)
             << t << "; x = " << setw(4) << x << "." << endl;
    }
    //todo print on output file
}

double SolutionCell::getCostOfSolutionCell(CostMatrix *costs) {
    //return (costs->getCost(getJ(), getI(), getType(), getTime()) * getX());
    return (costs->getCost(getJ(), getI(), getType(), getTime()) / (getType() + 1));
}


