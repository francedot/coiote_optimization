/*
 * CostMatrix.cpp
 */

#include <cstdlib>
#include "CostMatrix.hpp"
#include "util.hpp"
#include <math.h>
/*
 * This constructor initializes the costs matrix and the two average and stnd dev arrays (for welford)
 */
CostMatrix::CostMatrix(int cellsNumber, int peopleTypes, int timePeriods) {
    this->cellsNumber = cellsNumber;
    this->peopleTypes = peopleTypes;
    this->timePeriods = timePeriods;
    costs = new int ***[cellsNumber]();
    for (int j = 0; j < cellsNumber; j++) {
        costs[j] = new int **[cellsNumber]();
        for (int i = 0; i < cellsNumber; i++) {
            costs[j][i] = new int *[peopleTypes]();
            for (int m = 0; m < peopleTypes; m++) {
                costs[j][i][m] = new int[timePeriods]();
                for (int t = 0; t < timePeriods; t++) {
                    costs[j][i][m][t] = 0;
                }
            }
        }
    }
    averageCostsPerTask = new double[cellsNumber]();
    stdvCostsPerTask = new double[cellsNumber]();
    for (int i = 0; i < cellsNumber; i++) {
        averageCostsPerTask[i] = 0;
        stdvCostsPerTask[i] = 0;
    }
}

/*
 * load the cost matrix from the inputFileStream
 */
int CostMatrix::load(ifstream *inputFileStream) {
    string line;    // contains a line of the Input file
    string word;    // contains a single word (into a line)
    int m;          // index for peopleTypes
    int t;          // index for timePeriods

    int cost;    // for using updateAvgCostsPerTask
    long index[cellsNumber];
    for (int i = 0; i < cellsNumber; i++)
        index[i] = 0;
    for (m = 0; m < peopleTypes; m++) {
        for (t = 0; t < timePeriods; t++) {
            // jump line with m and t indexes
            getline(*inputFileStream, line);

            for (int i = 0; i < cellsNumber; i++) {
                getline(*inputFileStream, line);
                istringstream inputStringStream(line);
                for (int j = 0; j < cellsNumber; j++) {
                    inputStringStream >> word;
                    cost = costs[j][i][m][t] = atoi(word.c_str());
                    index[j]++;
                    this->updateAvgCostsPerTask(j, ((double) cost) / (m + 1), index[j]);
                }
            }
        }
    }
    for (int k = 0; k < 3; k++) {
        *(stdvCostsPerTask + k) = sqrt(*(stdvCostsPerTask + k) / index[k]); // Aggiorna std_dev
        cout << "Media per task: " << *(averageCostsPerTask + k) << " DevStd: " << *(stdvCostsPerTask + k) << endl;
    }
    /*for (int m = 0; m < peopleTypes; m++) {
        cout << "Type: " << m + 1 << "\n" << endl;
        for (int t = 0; t < timePeriods; t++) {
            cout << "At time: " << t << "\n" << endl;
            for (int j = 0; j < cellsNumber; j++) {
                for (int i = 0; i < cellsNumber; i++) {
                    cout << costs[j][i][m][t] << ", ";
                }
                cout << "\n" << endl;
            }
        }
    }*/

    return 1;
}

/*
 * TODO [DAVIDE]:
 *                Dando per scontato che la CostMatrix abbia i parametri in quest'ordine:
 *                [j][i][m][t]. Per la funzione getMinimumCost vorremmo che in fase di
 *                lettura per ogni j venisse salvata la media di ogni costo <i,m,t>.
 *                La classe CostMatrix deve avere un array di size j in cui ogni elemento
 *                ci sia la media di tutti i costi <i,m,t>.
 *                Sembra un impiccio ma porta ad un'ottimizzazione sostanziale (vedi getMinimumCost)
 *
 *                Per il calcolo della media di un enorme numero di elementi letti volta per volta
 *                abbiamo scritto la funzione welford in util.cpp
 *
 *
*/
//void CostMatrix::getMinimumCost(int j, int *i, int *m, int *t, int ***people, int tSize, int mSize, int iSize) {
//    /*
//     *      Visto che Costmatrix::averageCosts[j] ha la media dei costi per
//     *      j, posso evitare di cercare ogni volta tutta la matrice prendendo il primo
//     *      costo che sia sostanzialmente più piccolo della media per j.
//     *      Se sai qual è il costo medio cAvg, ad ogni iterazione prendi il primo
//     *      elemento elem di costMatrix <= (0.5 * cAvg)
//     */
//    // tenere traccia di tutti i "minimi" richiesti leggendo una sola volta
//    double maxDistanceFromMin = 0.5;
//    for (int t_ = 0; t_ < tSize; t_++) {
//        for (int m_ = 0; m_ < mSize; m_++) {
//            for (int i_ = 0; i_ < iSize; i_++) {
//                if (people[t_][m_][i_] > 0) {
//                    if (this->costs[j][i_][m_][t_] <= (maxDistanceFromMin * averageCosts[j])) {
//                        *i = i_;
//                        *m = m_;
//                        *t = t_;
//                    }
//                }
//            }
//        }
//    }
//
//}

/*
 * TODO: Description
 * Note: Remember to delete the returned vector, which is allocated inside
 */
vector<CostMatrix::CostCoordinates> *CostMatrix::getMinimumTaskCost(int j, int remainingTasksForJ, PeopleMatrix *people) {
    /*
     *      Visto che Costmatrix::averageCosts[j] ha la media dei costi per
     *      j, posso evitare di cercare ogni volta tutta la matrice prendendo il primo
     *      costo che sia sostanzialmente più piccolo della media per j.
     *      Se sai qual è il costo medio cAvg, ad ogni iterazione prendi il primo
     *      elemento elem di costMatrix <= (0.5 * cAvg)
     */
    // TODO: Tenere traccia di tutti i "minimi" richiesti leggendo una sola volta

    vector<CostMatrix::CostCoordinates> *minsVector = new vector<CostMatrix::CostCoordinates>;
    double maxDistanceFromMin = 0.5;
    int peopleTemp;
    for (int t_ = 0; t_ < timePeriods; t_++) {
        for (int i_ = 0; i_ < cellsNumber; i_++) {
            if (i_ == j) continue;
            for (int m_ = 0; m_ < peopleTypes; m_++) {
                if ((peopleTemp = people->getPeople(t_, m_, i_)) > 0) {
                    if (costs[j][i_][m_][t_] / (m_ + 1) <= (maxDistanceFromMin * averageCostsPerTask[j])) {
                        CostMatrix::CostCoordinates *currentCoordinates = new CostMatrix::CostCoordinates();
                        currentCoordinates->j = j;
                        currentCoordinates->i = i_;
                        currentCoordinates->m = m_;
                        currentCoordinates->t = t_;
                        minsVector->push_back(*currentCoordinates);
                        if ((remainingTasksForJ -= (m_ + 1) * peopleTemp) <= 0) {
                            /*
                             * Solution 1: Guarantees no waste of resources (people) at the
                             * computational cost of extending the reasarch at the end (last
                             * cells)
                             */

                            /*
                            if (remainingTasksForJ != 0) {
                                minsVector->pop_back();
                                remainingTasksForJ += (m_ + 1) * peopleTemp;
                            } else {
                                return minsVector;
                            }
                             */

                            /*
                             * Solution 2: here the remainingTasks might be negative, in the
                             * sense that a person of type 2 [1] or 3 [2] is being used for
                             * less than the max jobs that could accomplish. The advantage is
                             * that the research is the minimum for a given distanceFromAvg
                             */
                            return minsVector;
                        }
                    }
                }
            }
        }
    }
}

/*
 * TODO: Description
 * Note: Remember to delete the returned vector, which is allocated inside
 */
vector<CostMatrix::CostCoordinates> *CostMatrix::getMinimumTaskCostDiversified(int j, int remainingTasksForJ, PeopleMatrix *people) {
    /*
     *      Visto che Costmatrix::averageCosts[j] ha la media dei costi per
     *      j, posso evitare di cercare ogni volta tutta la matrice prendendo il primo
     *      costo che sia sostanzialmente più piccolo della media per j.
     *      Se sai qual è il costo medio cAvg, ad ogni iterazione prendi il primo
     *      elemento elem di costMatrix <= (0.5 * cAvg)
     */
    // TODO: Tenere traccia di tutti i "minimi" richiesti leggendo una sola volta

    vector<CostMatrix::CostCoordinates> *minsVector = new vector<CostMatrix::CostCoordinates>;

    double maxDistanceFromMin = 0.5;
    int peopleTemp;

    for (int t_ = 0; t_ < timePeriods; t_++) {
        for (int i_ = 0; i_ < cellsNumber; i_++) {
            for (int m_ = 0; m_ < peopleTypes; m_++) {
                if ((peopleTemp = people->getPeople(t_, m_, i_)) > 0) {
                    if (this->costs[j][i_][m_][t_] / (m_ + 1) <= (maxDistanceFromMin * averageCostsPerTask[j])) {
                        CostCoordinates *currentCoordinates = new CostCoordinates();
                        currentCoordinates->j = j;
                        currentCoordinates->i = i_;
                        currentCoordinates->m = t_;
                        currentCoordinates->t = m_;
                        minsVector->push_back(*currentCoordinates);
                        if ((remainingTasksForJ -= (m_ + 1)) <= 0) {
                            /*
                             * Solution 1: Guarantees no waste of resources (people) at the
                             * computational cost of extending the reasarch at the end (last
                             * cells)
                             */
                            if (remainingTasksForJ != 0) {
                                minsVector->pop_back();
                                remainingTasksForJ += (m_ + 1);
                            } else {
                                return minsVector;
                            }
                            /*
                             * Solution 2: here the remainingTasks might be negative, in the
                             * sense that a person of type 2 [1] or 3 [2] is being used for
                             * less than the max jobs that could accomplish. The advantage is
                             * that the research is the minimum for a given distanceFromAvg
                             */
//                           return minsVector;
                        }
                    }
                }
            }
        }
    }
}

// TODO: invece di dare i primi validi se non si trovano elementi che soddisfino la media, prova ad aumentare k!
// OSS: profiling mostra che la maggior parte del tempo ( a volte 50%)nt viene passata in questa funzione, e nei casi in cui ci sono
//      gli optimality gap più alti il rapporto failed/total (cfr sotto) è altissimo, per cui ha senso cercare di
//      velocizzare e rendere migliore questa funzione.
CostMatrix::CostCoordinates *CostMatrix::getMinimumCost(int j, PeopleMatrix *solutionPeople, int *remainingtasks,
                                                        int cellsNumber, int peopleTypes, int timePeriods) {
    // These two static longs tell us the percentage of failed getMinimumExtractions
    static long total_entries = 0;
    total_entries++;
    static long total_fails = 0;
    CostMatrix::CostCoordinates *c = new CostCoordinates();
    bool restartFlagT = true, restartFlagM = true, restartFlagI = true;
    int stopT = timePeriods, stopM = peopleTypes, stopI = cellsNumber;
    int startT = rand() % timePeriods;
    int startM = rand() % peopleTypes;
    int startI = rand() % cellsNumber;
    bool flag = true;
    int tmpPeople = 0;
    int tmpTasks = 0;
    restartFlagT = true;
    for (int t = startT; t < stopT && (flag); t++) {
        restartFlagM = true;
        for (int m = startM; m < stopM && (flag); m++) {
            restartFlagI = true;
            for (int i = startI; i < stopI && (flag); i++) {
                tmpPeople = solutionPeople->getPeople(t, m, i);
                tmpTasks = remainingtasks[j];
                if (!((i == j) || (remainingtasks[j] == 0) || solutionPeople->getPeople(t, m, i) == 0)) {
                    if ((costs[j][i][m][t] / (m + 1)) <= averageCostsPerTask[j]) {
                        c->j = j;
                        c->i = i;
                        c->m = m;
                        c->t = t;
                        flag = false;
                    }
                }
                if (i == stopI - 1 && restartFlagI) {
                    i = 0;
                    stopI = startI;
                    restartFlagI = false;
                }
            }
            if (m == stopM - 1 && restartFlagM) {
                m = 0;
                stopM = startM;
                restartFlagM = false;
            }
        }
        if (t == stopT - 1 && restartFlagT) {
            t = 0;
            stopT = startT;
            restartFlagT = false;
        }
    }
    if (flag) {
        //se il ciclo precedente fallisce perchè non vi sono più celle che permettano un costo inferiore alla media
        //vengono restituite le prime cordinate valide disponibili
        total_fails++;
        if (total_entries % 1100 == 0) // non stampare ad ogni giro
            cout << "getMinimumCost: Percentage of misses: " << ((double) total_fails / total_entries) << "|| Misses: "
                 << total_fails << "|| Entries" << total_entries << endl;
        for (int t = 0; t < timePeriods && (flag); t++) {
            for (int m = 0; m < peopleTypes && (flag); m++) {
                for (int i = 0; i < cellsNumber && (flag); i++) {
                    if (!((i == j) || (remainingtasks[j] == 0) || solutionPeople->getPeople(t, m, i) == 0)) {
                        c->j = j;
                        c->i = i;
                        c->m = m;
                        c->t = t;
                        flag = false;
                    }
                }
            }
        }
    }
    //a returned nullptr should be interpreted as a failure of the algorythm. if there are enough people to complete all tasks this should never happen
    return c;
}

// TODO: invece di dare i primi validi se non si trovano elementi che soddisfino la media, prova ad aumentare k!
// OSS: profiling mostra che la maggior parte del tempo ( a volte 50%)nt viene passata in questa funzione, e nei casi in cui ci sono
//      gli optimality gap più alti il rapporto failed/total (cfr sotto) è altissimo, per cui ha senso cercare di
//      velocizzare e rendere migliore questa funzione.
CostMatrix::CostCoordinates *
CostMatrix::getMinimumTaskCostByDistance(int j, PeopleMatrix *solutionPeople, int *remainingtasks,
                                         int cellsNumber, int peopleTypes, int timePeriods) {
//    cout << "Entering getCost... \n";
    double avgFactor = 0.01;

    int startT = rand() % timePeriods;
    int startM = rand() % peopleTypes;

    bool restartedT = false, restartedM = false;

    int tempCost = 0, minFeasibleFoundCost = 100000000;

    CostCoordinates *currentCoordinates = new CostCoordinates();

    for (int i_ = j + 1; i_ != j; (i_ = (i_ >= cellsNumber) ? 0 : i_ + 1)) {
        if (i_ == cellsNumber) {
            continue;
        }
        for (int t_ = startT; (!restartedT || t_ != startT);) {
            for (int m_ = startM; (!restartedM || m_ != startM);) {
                if (solutionPeople->getPeople(t_, m_, i_) > 0) {
                    tempCost = (int) (((double) this->costs[j][i_][m_][t_]) / (m_ + 1));
                    if (tempCost <= (avgFactor * averageCostsPerTask[j])) {
                        currentCoordinates->j = j;
                        currentCoordinates->i = i_;
                        currentCoordinates->m = m_;
                        currentCoordinates->t = t_;
                        return currentCoordinates;
                    }
                    /* Now, updates the minimum feasible coordinates found */
                    if (tempCost < minFeasibleFoundCost) {
                        minFeasibleFoundCost = tempCost;
                        currentCoordinates->j = j;
                        currentCoordinates->i = i_;
                        currentCoordinates->m = m_;
                        currentCoordinates->t = t_;
                    }
                }
                m_++;
                if (m_ == peopleTypes) {
                    m_ = 0;
                    restartedM = true;
                }
            }
            restartedM = false;
            t_++;
            if (t_ == timePeriods) {
                t_ = 0;
                restartedT = true;
            }
        }
        restartedT = false;
    }
    return currentCoordinates;
}


int min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

CostMatrix::CostCoordinates *
CostMatrix::getMinimumCostByDistanceFromJ(int j, PeopleMatrix *solutionPeople, int *remainingtasks,
                                          int cellsNumber, int peopleTypes, int timePeriods) {
    static long total_entries = 0, total_fails = 0;
    total_entries++;
    int startTime;
    bool flag = true;
    CostCoordinates *c = new CostCoordinates();
    int maxTimeChangingRetries = max(5, timePeriods / 2);
    int currentTry = 0;
    int startingI, endingI;
    bool directionRight;
    int maxLengthOfScan = cellsNumber;
    /*
     * OSS: Non è detto che aumentando maxLengthOfScan ed altri parametri
     *      che migliorano la ricerca locale si peggiori il tempo. L'algoritmo
     *      si ferma quando non riesce a migliorare l'ottimo, per cui esiste un
     *      tradeoff in questo senso: se miglioro la ricerca locale ci metto molto
     *      tempo nel fare operazioni, ma 'arrivo prima' al punto di stop.
    */
    int scanIndex;
    double curMinValue = 100000.0;
    int curI;
    double minForType[peopleTypes];
    for (int q = 0; q < peopleTypes; q++)
        minForType[q] = 10000.0;
    bool endArray;
    while (currentTry < maxTimeChangingRetries) {
        startTime = rand() % timePeriods;
        if (j < (cellsNumber / 2)) {
            directionRight = true;
            startingI = j;
            endingI = cellsNumber - 1;
            maxLengthOfScan = min(maxLengthOfScan, cellsNumber - 1 - j);
        } else {
            directionRight = false;
            startingI = j;
            endingI = 0;
            maxLengthOfScan = min(j, maxLengthOfScan);
        }
        scanIndex = 0;
        //if(total_entries < 100) cout << directionRight << " " << startingI << " " << endingI << " " << maxLengthOfScan << endl;
        while (scanIndex <= maxLengthOfScan) {
            if (directionRight) {
//                curI = startingI + scanIndex;
                curI = 0 + scanIndex;
                endArray = (curI <= endingI);
            } else {
//                curI = startingI - scanIndex;
                curI = cellsNumber - 1 - scanIndex;
                endArray = (curI >= endingI);
            }
            //cout << endArray << endl;
            if (endArray) {
                for (int l = 0; l < peopleTypes; l++) {
                    double costPerTask = ((double) costs[j][curI][l][startTime]) / (l + 1);
                    // if(total_entries < 100) cout << "CostPerTask: " << costPerTask << endl;
//                    if (!((curI == j) || (costPerTask > averageCostsPerTask[j]) || (remainingtasks[j] == 0) ||
                    if (!((curI == j) || (remainingtasks[j] == 0) ||
                          solutionPeople->getPeople(startTime, l, curI) == 0)) {
                        //if(total_entries < 100) cout << "Entered" << endl;
                        if (costPerTask <= minForType[l]) {
                            minForType[l] = costPerTask;
                            //if(total_entries < 100)
                            //cout << "New min for type: " << l+1 << " :" << costPerTask << endl;
                            if (minForType[l] <= curMinValue) {
                                // if(total_entries < 100) cout << "New curMinValue: " << costPerTask << endl;
                                curMinValue = costPerTask;
                                c->i = curI;
                                c->j = j;
                                c->m = l;
                                c->t = startTime;
                                flag = false;
                            }
                        }
                    }
                }
            }
            scanIndex++;
        }

        currentTry++;
    }
    //if(total_entries < 100)
    //cout << "Entry: " << total_entries << " Min: " << curMinValue << " i:" << c->i << " j:" << c->j << "  m: " << c->m <<" t:"<<c->t<< endl;
    if (flag) {
        cout << "MISS!!!\n";
        //se il ciclo precedente fallisce perchè non vi sono più celle che permettano un costo inferiore alla media
        //vengono restituite le prime cordinate valide disponibili
        // Antonio: ci sono pochissime probabilità di entrare in questo ciclo, ma va tenuto per sicurezza
        total_fails++;
        if (total_entries % 10000 == 0) // non stampare ad ogni giro
            cout << "getMinimumCost: Percentage of misses: " << ((double) total_fails / total_entries) << "|| Misses: "
                 << total_fails << "|| Entries" << total_entries << endl;
        for (int t = 0; t < timePeriods && (flag); t++) {
            for (int m = 0; m < peopleTypes && (flag); m++) {
                for (int i = 0; i < cellsNumber && (flag); i++) {
                    if (!((i == j) || (remainingtasks[j] == 0) || solutionPeople->getPeople(t, m, i) == 0)) {
                        c->j = j;
                        c->i = i;
                        c->m = m;
                        c->t = t;
                        flag = false;
                    }
                }
            }
        }
    }
    return c;
}






































/*
 * It sets the value of the cost matrix corrisponding to cell "i" "j", person type "m", time period "t".
 */
void CostMatrix::setValue(int j, int i, int m, int t, int value) {
    costs[j][i][m][t] = value;
}

/*
 * It returns the value of the cost matrix corrisponding to cell "i" "j", person type "m", time period "t".
 */
int CostMatrix::getCost(int j, int i, int m, int t) {
    return costs[j][i][m][t];
}

/*
 * This method returns the average cost per task for the given destination cell "j".
 */
int CostMatrix::getAvgCostsPerTask(int j) {
    return averageCostsPerTask[j];
}

/*
 * Updates the avg and the stdv of costs-per-task. The param "index" is the number of the value so that the first
 * value passed (independently from the j) will have index 0, the second value passed will have index 1 and so on.
 * The last value to be inserted will have "index" = N_of_cells - 1.
 * Remember to divide the cost by the number of tasks that the person of that type can perform. In this way
 * "newValue" will hold the costPerTask (Example: if for a person of type m = 2 the cost is 30, then the cost per
 * task will be 10 because that person can fullfill 3 tasks for that single bigger cost)
 */
void CostMatrix::updateAvgCostsPerTask(int j, double newValue, long index) {
    welford(newValue, averageCostsPerTask + j, stdvCostsPerTask + j, index);
}

/*
 * It returns the internal representation of the cost matrix. Should be used with caution.
 */
int ****CostMatrix::getMatrix() {
    return costs;
}

//int CostMatrix::getSize() {
//    return size;
//}

/*
 * screen print of the cost matrix
 */
void CostMatrix::print() {
    for (int t = 0; t < timePeriods; t++) {
        for (int m = 0; m < peopleTypes; m++) {
            std::cout << m << " " << t << std::endl;
            for (int j = 0; j < cellsNumber; j++) {
                for (int i = 0; i < cellsNumber; i++) {
                    std::cout << costs[j][i][m][t] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}
