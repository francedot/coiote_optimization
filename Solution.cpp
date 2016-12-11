/*
 * Solution.cpp
 */

#include "Solution.hpp"

using namespace std;

/*
 * todo da eliminare ?
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
void Solution::populateSolution(Solution *initialSolution, int keptSolCells, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N) {
    // People is a matrix Time x TypePerson x CellNumber
    // TODO: Add exception / full control of passed parameters
    int *remainingTask = new int[sizeOfTasks];
    // TODO: [available/pickable]People never used/initialized
    this->totalCost = 0;
    for (int i = 0; i < sizeOfTasks; i++)
        remainingTask[i] = tasks[i];
    //se c'è una soluzione di partenza parte di essa viene riutilizzata

    if (initialSolution != nullptr) {
        double keptCellProbability = ((double) keptSolCells / (double) initialSolution->cells.size());

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
        int kept = 0;
        while (kept < keptSolCells) {
            for (vector<SolutionCell>::iterator it = initialSolution->cells.begin();
                 it != initialSolution->cells.end() && kept < keptSolCells; it++) {
                double r = ((double) rand()) / RAND_MAX;
                if (r >= keptCellProbability) {
                    // TODO: Valuta se usare addSolutionCell [ Meno efficiente. Probabilmente è già ordinata ]
                    SolutionCell cellToAdd(*it);
                    this->cells.insert(this->cells.begin(), cellToAdd);
                    remainingTask[cellToAdd.getJ()] -= cellToAdd.getX() * (cellToAdd.getType() + 1);
//                    people[cellToAdd.getTime()][cellToAdd.getType()][cellToAdd.getI()] -= cellToAdd.getX();
//                    totalCost += costs->getCost(cellToAdd.getI(), cellToAdd.getJ(), cellToAdd.getType(), cellToAdd.getTime());
//                    addSolutionCell(new SolutionCell(*it));
                    remainingTask[it->getJ()] -= (it->getX() * (it->getType() + 1));
                    if (remainingTask[it->getJ()] < 0)
                        remainingTask[it->getJ()] = 0;
//                    printTasks(remainingTask, N);
                    people->setValue(it->getTime(), it->getType(), it->getI(), (people->getPeople(it->getTime(), it->getType(), it->getI()) - it->getX()));
                    totalCost += costs->getCost(it->getI(), it->getJ(), it->getType(), it->getTime()) * it->getX();
                    kept++;
                }
            }
        }

    }
    //   printTasks(remainingTask, N);
    vector<CostMatrix::CostCoordinates> *minsVector;
    vector<CostMatrix::CostCoordinates>::iterator it;
    for (int j = 0; j < N; j++) {
        int x = 0;
        if (remainingTask[j] <= 0) continue;
        minsVector = costs->getMinimumTaskCost(j, remainingTask[j], people);
        it = minsVector->begin();
        if (it == minsVector->end()) exit(8);
        while (it != minsVector->end() && remainingTask[j] > 0) {
            x = 0;
            //SI PIANTA ALLA RIGA QUI SOTTO
            while (people->getPeople(it->t, it->m, it->i) > 0 && remainingTask[j] > 0) {
                remainingTask[j] -= (it->m + 1);
                people->setValue(it->t, it->m, it->i, (people->getPeople(it->t, it->m, it->i) - 1));
                x++;
            }
            if (remainingTask[j] < 0) remainingTask[j] = 0;

            totalCost += (costs->getCost(j, it->i, it->m, it->t) * x);

            addSolutionCell(new SolutionCell(it->i, it->j, it->m, it->t, x));
            it++;
        }
        free(minsVector);
        //printTasks(remainingTask, N);
    }
}

/*
 * todo comments
 */
void Solution::generateInitialSolution(int *remainingTask, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N) {
    populateSolution(nullptr, 0, remainingTask, sizeOfTasks, people, costs, N);
}


void Solution::addSolutionCell(SolutionCell *toAdd) {
    // Adds a solution cell using an insertion sort
    if (toAdd == NULL) {
        exit(101);
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

vector<Solution *> *Solution::generateNeighborhood(int size, int keptSolCells, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N) {
    vector<Solution *> *neighborhood = new vector<Solution *>((unsigned long) size);
    for (int i = 0; i < size; i++) {
        neighborhood->push_back(generateNeighbor(keptSolCells, tasks, sizeOfTasks, people, costs, N));
    }
    return neighborhood; //Use delete[] to delete this array;
}

Solution *Solution::generateNeighbor(int keptSolCells, int *tasks, int sizeOfTasks, PeopleMatrix *people, CostMatrix *costs, int N) {
    Solution *newSol = new Solution();
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

void Solution::printTasks(int *remainingTask, int N) {
    if (remainingTask != nullptr) {
        std::cout << "Tasks: ";
        for (int h = 0; h < N; h++) {
            std::cout << remainingTask[h] << " ";
        }
    }
    std::cout << std::endl;
}