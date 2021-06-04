/*
 * calc_derivatives.hpp
 *
 *  Created on: Jun 5, 2021
 *      Author: d-w-h
 */

#ifndef CALC_DERIVATIVES_HPP_
#define CALC_DERIVATIVES_HPP_

#include "user_types.hpp"

class CalcDerivative {
private:
    t_elem ***f_table;
public:
    int N = 4;
    long double x;

    CalcDerivative(long double x, int N) {
        this->x = x;
        this->N = N;

        //Initialize table for memoization
        f_table = new t_elem**[N+1];

        for(int i = 0; i < N + 1; ++i) {
            f_table[i] = new t_elem*[N+1];
        }

        for(int i = 0; i < N + 1; ++i) {
            for(int j = 0; j < N + 1; ++j) {
                f_table[i][j] = new t_elem;
                f_table[i][j]->elem_is_set = false;
                f_table[i][j]->f = 0.0;
            }
        }
    }

    long double func(long double x);
    long double df_dx(long double xo, long double x, int n);
    long double get_result();
};

#endif /* CALC_DERIVATIVES_HPP_ */
