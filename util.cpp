/*
 * Useful/general-use functions
 * TODO: Valuta se inserirle altrove, in base alla funzione
*/

/*
 * welford: Computes average and standard variation of possibly huge
 * number of values without risk of overflow.
 *
 * Params:  new_val: just read value
 *          avg / stdv: pointers to avg / stdv
 *          index: a long that keeps track of the number of read values
 *                 pass it initialized to 0.
*/

void welford(double new_val, double *avg, double *stdv, long index) {
    double diff = new_val - (*avg);
    (*stdv) = (*stdv) + (diff * diff * (index) / (index + 1));
    (*avg) = (*avg) + (diff / (index + 1));
}