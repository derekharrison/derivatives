/*
 * calc_derivatives.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: d-w-h
 */

#include <cmath>
#include "calc_derivatives.hpp"
#include "user_types.hpp"

//Get the derivative result
long double CalcDerivative::get_result() {
    return CalcDerivative::df_dx(x, x, N);
}

//The function of which the derivative is taken
long double CalcDerivative::func(long double x) {
    return x*x*x*x - sqrt(x);
}

//Function to compute derivatives of func(x)
long double CalcDerivative::df_dx(long double xo, long double x, int n) {
    long double f = 0.0;
    long double dx = 0.0001;

    //Map x coordinate to table index
    int table_index = (int) round((x - xo)/dx);

    //Return memoized result
    if(f_table[table_index][n]->elem_is_set == true) {
        f = f_table[table_index][n]->f;
    }
    else {
        if(n == 0) {
            f = func(x);
        }
        else if(n > 0) {
            f = (df_dx(xo, x + dx, n - 1) - df_dx(xo, x, n - 1))/dx;
        }

        //Memoize result
        f_table[table_index][n]->f = f;
        f_table[table_index][n]->elem_is_set = true;
    }

    return f;
}
