/*
 * CostMatrix.cpp
 */

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

#include "CostMatrix.hpp"

/*
 * todo comments
 */
CostMatrix::CostMatrix(int dim) {

}

/*
 * todo comments
 */
int CostMatrix::loadMatrix(istream inputFile) {
    // TODO check why it makes the build fail
    return 0;
}

void CostMatrix::getMinimumCost(int j, int *i, int *m, int *t, int ***people, int tSize, int mSize, int iSize) {
    /*
     *      Visto che Costmatrix::averageCosts[j] ha la media dei costi per
     *      j, posso evitare di cercare ogni volta tutta la matrice prendendo il primo
     *      costo che sia sostanzialmente più piccolo della media per j.
     *      Se sai qual è il costo medio cAvg, ad ogni iterazione prendi il primo
     *      elemento elem di costMatrix <= (0.5 * cAvg)
     */
    // TODO: Tenere traccia di tutti i "minimi" richiesti leggendo una sola volta
    double maxDistanceFromMin = 0.5;
    for (int t_ = 0; t_ < tSize; t_++) {
        for (int m_ = 0; m_ < mSize; m_++) {
            for (int i_ = 0; i_ < iSize; i_++) {
                if (people[t_][m_][i_] > 0) {
                    if (this->costs[j][i_][m_][t_] <= (maxDistanceFromMin * averageCosts[j])) {
                        *i = i_;
                        *m = m_;
                        *t = t_;
                    }
                }
            }
        }
    }

}

void CostMatrix::getMinimumTaskCost(int j, int *i, int *m, int *t, int ***people, int tSize, int mSize, int iSize) {
    /*
     *      Visto che Costmatrix::averageCosts[j] ha la media dei costi per
     *      j, posso evitare di cercare ogni volta tutta la matrice prendendo il primo
     *      costo che sia sostanzialmente più piccolo della media per j.
     *      Se sai qual è il costo medio cAvg, ad ogni iterazione prendi il primo
     *      elemento elem di costMatrix <= (0.5 * cAvg)
     */
    // TODO: Tenere traccia di tutti i "minimi" richiesti leggendo una sola volta

}

int CostMatrix::getCost(int j, int i, int m, int t) {
    return costs[j][i][m][t];
}
