/*
 * Useful/general-use functions
 * TODO: Valuta se inserirle altrove, in base alla funzione
*/

#ifndef COIOTE_PROJECT_UTIL_HPP
#define COIOTE_PROJECT_UTIL_HPP

/*
 * welford: Computes average and standard variation of possibly huge
 * number of values without risk of overflow.
*/
void welford(double new_val, double *avg, double *stdv, long *index);

#endif //COIOTE_PROJECT_UTIL_HPP
