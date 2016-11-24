/*
 * Solution.cpp
 */

#include "Solution.hpp"

/*
 * TODO WRITE DESCRIPTION HERE
 */
Solution::Solution() {


}

/*
 * TODO WRITE DESCRIPTION HERE
 */
void Solution::populateSolution(Solution *initialSolution, int n, int *remainingTask, int ***people, CostMatrix *costs,
                                int N) {
    int *availablePeolpe;
    int pickablePeople;
    totalCost = 0;

    for (int i = 0; i < n; i++) {
        int r = (int) (rand() / RAND_MAX *
                       initialSolution->cells.size());     //choose which cells of previous solution has to be picked
        SolutionCell toAdd = initialSolution->cells.;
        remainingTask[toAdd.getJ()] -= toAdd.getX();
        people[toAdd.getTime()][toAdd.getType()][toAdd.getI()] -= toAdd.getX();
        totalCost += costs->get(toAdd.getI(), toAdd.getJ());
        addSolutionCell(toAdd);
    }
    for (int j = 0; j < N; j++) {
        while (remainingTask[j] > 0) {
            int i, t, m;
            costs->getMinimumCost(i, &j, &i, &m, &t);           //search best parameters
            if (remainingTask[j] >= people[t][m][i]) {
                remainingTask -= people[t][m][i];
                SolutionCell toAdd(i, j, m, t, people[t][m][i]);
                addSolutionCell(toAdd);
                people[t][m][i] = 0;
            } else {
                people[t][m][i] -= remainingTask[j];
                SolutionCell toAdd(i, j, m, t, remainingTask[j]);
                addSolutionCell(toAdd);
                remainingTask[j] = 0;
            }
        }
    }
}

void Solution::generateInitialSolution(int *remainingTask, int ***people, CostMatrix *costs, int N) {
    populateSolution(nullptr, 0, remainingTask, people, costs, N);
}

void Solution::addSolutionCell(SolutionCell toAdd) {

}


