/*
 * Solution.cpp
 */

#include "Solution.hpp"

using namespace std;

/*
 * todo comments
 */
Solution::Solution() {

}

Solution::Solution(const Solution &toCopy) {
    totalCost = toCopy.totalCost;
//    for (int i = 0; i < toCopy.cells.size(); i++) {
//        cells.push_back(toCopy.cells[i]);
//    }
    cells = toCopy.cells; // Should be faster and uses copy constructors
}

/*
 * initialSolution = eventuale soluzione iniziale di cui generare il vicinato. (null = genera nuova soluzione)
 * n = numero di celle da lasciare invariate nella generazione del vicinato
 * N = numero di celle in totale [parametro del problema]
 * null implica n = 0
 * populateSolution popola se stessa partendo da una initial solution di cui ne tiene n
 */
void Solution::populateSolution(Solution *initialSolution, int keptSolCells, int *tasks, int sizeOfTasks, int ***people,
                                CostMatrix *costs, int N) {
    std::cout << "populateSolution(...) called" << std::endl;

    // People is a matrix Time x TypePerson x CellNumber
    // TODO: Add exception / full control of passed parameters
    int *remainingTask = new int[sizeOfTasks];
    // TODO: [available/pickable]People never used/initialized
    this->totalCost = 0;
    for (int i = 0; i < sizeOfTasks; i++)
        remainingTask[i] = tasks[i];
    printTasks(remainingTask, tasks, N);
    if (initialSolution != nullptr) {
        double keptCellProbability = ((double) keptSolCells / (double) initialSolution->cells.size());
        for (int i = 0; i < keptSolCells; i++) {
            /*
             * Codice commentato poichè abbiamo pensato di ottimizzare
             * facendo scorrere un'unica volta la lista e controllando
             * volta per volta la probabilità che esca.
             * Inoltre, abbiamo modificato il tutto in modo da non
             * distruggere la initialSolution.
             * */
            /*int r = (int) ((rand() / RAND_MAX) * initialSolution->cells.size());
            //choose which cells of previous solution has to be picked
            SolutionCell toAdd = initialSolution->cells[r]; //TODO remove cell[r]
            remainingTask[toAdd.getJ()] -= toAdd.getX();
            people[toAdd.getTime()][toAdd.getType()][toAdd.getI()] -= toAdd.getX();
            totalCost += costs->getCost(toAdd.getI(), toAdd.getJ(), toAdd.getTime(), toAdd.getType());
            addSolutionCell(toAdd);*/
            vector<SolutionCell>::iterator it;
            for (it = initialSolution->cells.begin(); it != initialSolution->cells.end(); it++) {
                double r = ((double) rand()) / RAND_MAX;
                if (r >= keptCellProbability) {
                    // TODO: Valuta se usare addSolutionCell [ Meno efficiente. Probabilmente è già ordinata ]
//                SolutionCell cellToAdd = *it;
//                this->cells.insert(this->cells.begin(), cellToAdd);
//                remainingTask[cellToAdd.getJ()] -= cellToAdd.getX();
//                people[cellToAdd.getTime()][cellToAdd.getType()][cellToAdd.getI()] -= cellToAdd.getX();
//                totalCost += costs->getCost(cellToAdd.getI(), cellToAdd.getJ(), cellToAdd.getType(), cellToAdd.getTime());
                    this->cells.insert(this->cells.begin(), *it);
                    remainingTask[it->getJ()] -= it->getX();
                    people[it->getTime()][it->getType()][it->getI()] -= it->getX();
                    totalCost += costs->getCost(it->getI(), it->getJ(), it->getType(), it->getTime());
                }
            }
        }
    }



    for (int j = 0; j < N; j++) {

        int x = 0;
        if (remainingTask[j] <= 0) continue;
        vector<CostMatrix::CostCoordinates> *minsVector = costs->getMinimumTaskCost(j, remainingTask[j], people);

        vector<CostMatrix::CostCoordinates>::iterator it = minsVector->begin();

        while (it != minsVector->end() && remainingTask[j] > 0) {
            x = 0;
            //cout << "People picked from i[" << it->i << "]; m[" << it->m << "]; t[" << it->t << "]; " << "People there: " << people[it->t][it->m][it->i] << " ";

            while (people[it->t][it->m][it->i] > 0 && remainingTask[j] > 0) {
                remainingTask[j] -= (it->m + 1);
                people[it->t][it->m][it->i]--;
                x++;
            }
            //cout << "People updated: " << people[it->t][it->m][it->i] << endl;
            if (remainingTask[j] < 0) remainingTask[j] = 0;
            addSolutionCell(new SolutionCell(it->i, it->j, it->m, it->t, x));
            it++;
        }
        printTasks(remainingTask, tasks, N);

//        switch (m) {
//            //TODO fare in modo che persone di tipo 1 e 2 possano fare meno di 2 e 3 task rispettivamente
//            case 0: {
//                if (remainingTask[j] >= people[t][m][i]) {
//                    remainingTask -= people[t][m][i];
//                    x = people[t][m][i];
//                    people[t][m][i] = 0;
//                } else {
//                    people[t][m][i] -= remainingTask[j];
//                    remainingTask[j] = 0;
//                }
//                break;
//            }
//            case 1: {
//                if (remainingTask[j] >= 2 * people[t][m][i]) {
//                    remainingTask -= 2 * people[t][m][i];
//                    people[t][m][i] = 0;
//                } else {
//
//                    people[t][m][i] -= remainingTask[j] / 2;
//                    remainingTask[j] = remainingTask[j] % 2;
//                }
//                break;
//            }
//            case 2: {
//                if (remainingTask[j] >= 3 * people[t][m][i]) {
//                    remainingTask -= 3 * people[t][m][i];
//                    people[t][m][i] = 0;
//                } else {
//                    people[t][m][i] -= remainingTask[j] / 3;
//                    remainingTask[j] = remainingTask[j] % 3;
//                }
//                break;
//            }
//            default:;  // TODO throw exception
//        }
        delete (minsVector);
        //TODO: addSolutionCell must check for cases where <i,j,m,t> for the new entry equals those of an old entry
    }
    delete (remainingTask);
}

/*
 * todo comments
 */
void Solution::generateInitialSolution(int *remainingTask, int sizeOfTasks, int ***people, CostMatrix *costs, int N) {
    populateSolution(nullptr, 0, remainingTask, sizeOfTasks, people, costs, N);
}


void Solution::addSolutionCell(SolutionCell *toAdd) {
    // Adds a solution cell using an insertion sort
    if (toAdd == NULL) {
        // TODO: Throw exception
    }
    vector<SolutionCell>::iterator it;
    for (it = cells.begin(); (it != cells.end()) && (toAdd->getI() > it->getI()); it++);
    if (it == cells.end()) {
        cells.push_back(*toAdd);
        return;
    }
    for (; (toAdd->getI() == it->getI()) && (toAdd->getJ() > it->getJ()) && (it != cells.end()); it++);
    cells.insert(it, *toAdd);
    return;
}

vector<Solution *> *Solution::generateNeighborhood(int size, int keptSolCells, int *tasks, int sizeOfTasks,
                                                   int ***people, CostMatrix *costs, int N) {
    vector<Solution *> *neighborhood = new vector<Solution *>(size);
    for (int i = 0; i < size; i++) {
        neighborhood->push_back(generateNeighbor(keptSolCells, tasks, sizeOfTasks, people, costs, N));
    }
    return neighborhood; //Use delete[] to delete this array;
}

Solution *Solution::generateNeighbor(int keptSolCells, int *tasks, int sizeOfTasks,
                                     int ***people, CostMatrix *costs, int N) {
    Solution *newSol = new Solution();
    cout << "ORIGINAL ";
    printTasks(nullptr, tasks, N);
    newSol->populateSolution(this, keptSolCells, tasks, sizeOfTasks, people, costs, N);
    return newSol;
}

int Solution::evaluate() {
    return totalCost;
}

void Solution::print(bool screen, string path) {
    if (screen)
        for (int i = 0; i < cells.size(); i++)
            cells[i].print(1, path);
    //todo print on output file
}

void Solution::printTasks(int *remainingTask, int *originalTask, int N) {
    if (remainingTask != nullptr) {
        std::cout << "Remaining Tasks: " << std::endl;
        for (int h = 0; h < N; h++) {
            std::cout << remainingTask[h] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Original Tasks: " << std::endl;
    for (int h = 0; h < N; h++) {
        std::cout << originalTask[h] << " ";
    }
    std::cout << std::endl;
}