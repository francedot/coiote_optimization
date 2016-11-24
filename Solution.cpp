/*
 * Solution.cpp
 */

#include "Solution.hpp"

/*
 * todo comments
 */
Solution::Solution() {

}

/*
 * initialSolution = eventuale soluzione iniziale di cui generare il vicinato. (null = genera nuova soluzione)
 * n = numero di celle da lasciare invariate nella generazione del vicinato
 * null implica n = 0
 * populateSolution popola se stessa partendo da una initial solution di cui ne tiene n
 */
void Solution::populateSolution(Solution *initialSolution, int n, int *tasks, int ***people, CostMatrix *costs, int N) {
    // People is a matrix Time x TypePerson x CellNumber
    int *remainingTask;
    int *availablePeolpe;
    int pickablePeople;
    totalCost = 0;

    //TODO copiare tasks in remaningTasks

    for (int i = 0; i < n; i++) {
        int r = (int) (rand() / RAND_MAX *
                       initialSolution->cells.size());     //choose which cells of previous solution has to be picked
        SolutionCell toAdd = this->cells[r]; //TODO remove cell[r]
        remainingTask[toAdd.getJ()] -= toAdd.getX();
        people[toAdd.getTime()][toAdd.getType()][toAdd.getI()] -= toAdd.getX();
        totalCost += costs->getCost(toAdd.getI(), toAdd.getJ(), toAdd.getTime(), toAdd.getType());
        addSolutionCell(toAdd);
    }
    for (int j = 0; j < N; j++) {
        while (remainingTask[j] > 0) {
            int x = 0, i = 0, t = 0, m = 0;
            costs->getMinimumCost(j, &i, &m, &t, people);      //search best parameters
            switch (m) {
                //TODO fare in modo che persone di tipo 1 e 2 possano fare meno di 2 e 3 task rispettivamente
                case 0: {
                    if (remainingTask[j] >= people[t][m][i]) {
                        remainingTask -= people[t][m][i];
                        x = people[t][m][i];
                        people[t][m][i] = 0;
                    } else {
                        people[t][m][i] -= remainingTask[j];
                        remainingTask[j] = 0;
                    }
                    break;
                }
                case 1: {
                    if (remainingTask[j] >= 2 * people[t][m][i]) {
                        remainingTask -= 2 * people[t][m][i];
                        people[t][m][i] = 0;
                    } else {

                        people[t][m][i] -= remainingTask[j] / 2;
                        remainingTask[j] = remainingTask[j] % 2;
                    }
                    break;
                }
                case 2: {
                    if (remainingTask[j] >= 3 * people[t][m][i]) {
                        remainingTask -= 3 * people[t][m][i];
                        people[t][m][i] = 0;
                    } else {
                        people[t][m][i] -= remainingTask[j] / 3;
                        remainingTask[j] = remainingTask[j] % 3;
                    }
                    break;
                }
                default:;  // TODO throw exception
            }
            SolutionCell toAdd(i, j, m, t, x);
            addSolutionCell(toAdd);
            // TODO: addSolutionCell must check for cases where <i,j,m,t> for the new entry equals those of an old entry
        }
    }
}

/*
 * todo comments
 */
void Solution::generateInitialSolution(int *remainingTask, int ***people, CostMatrix *costs, int N) {
    populateSolution(nullptr, 0, remainingTask, people, costs, N);
}


void Solution::addSolutionCell(SolutionCell toAdd) {
    // Adds a solution cell using an insertion sort
    vector<SolutionCell>::iterator it;
    for (it = cells.begin(); (toAdd.getI() > it->getI()) && (it != cells.end()); it++);
    if (it == cells.end()) {
        cells.push_back(toAdd);
        return;
    }
    for (; (toAdd.getI() == it->getI()) && (toAdd.getJ() > it->getJ()) && (it != cells.end()); it++);
    cells.insert(it, toAdd);
    return;
}