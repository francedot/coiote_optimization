/*
 * Solution.hpp
 */

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "SolutionCell.hpp"
#include "CostMatrix.hpp"
#include "PeopleMatrix.hpp"

using namespace std;

class Solution {

public:
    /*
     * todo comments
     */
    Solution(PeopleMatrix *peopleMatrix);

    Solution(const Solution &toCopy);

    vector<Solution *> *generateNeighborhood(int size, int kept, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N);

    void generateInitialSolution(int *remainingTask, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N);

    void addSolutionCell(SolutionCell *toAdd);

    Solution *
    generateNeighbor(double kept, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N);

    int getSize();

    PeopleMatrix *getSolutionPeople();

    void setSolutionPeople(PeopleMatrix peopleToSet);

    SolutionCell *getCell(int i);

    int evaluate();

    void print(bool screen = 0, string path = nullptr);

    void printForTypes();

private:
    /*
     * todo comments
     */
    vector<SolutionCell> cells;
    PeopleMatrix *solutionPeople;

    void populateSolution(Solution *initialSolution, double n, int *task, int sizeOfTasks, CostMatrix *costs, int N);

    int totalCost;

    void printTasks(int *remainingTask, int N);
};

#endif /* Solution_hpp */
