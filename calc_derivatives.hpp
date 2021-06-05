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

    CalcDerivative(long double x, int N);
    long double func(long double x);
    long double df_dx(long double xo, long double x, int n);
    long double get_result();
};

#endif /* CALC_DERIVATIVES_HPP_ */
