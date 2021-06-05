/*
 * main.cpp
 *
 *  Created on: Jun 4, 2021
 *      Author: d-w-h
 *
 *      A dynamic programming solution to computing derivatives of
 *      an arbitrary one dimensional function func(x)
 *
 */

#include <stdio.h>
#include <cmath>
#include "calc_derivatives.hpp"

//Declare table f
t_elem ***f_table;

//Track number of calls
static int num_calls_dp = 0;
static int num_calls_no_dp = 0;

//Function of which the derivative is computed
long double func(long double x) {
    return x*x*x*x - sqrt(x);
}

//Function to compute derivatives of func(x)
long double df_dx(long double xo, long double x, int n) {
    long double f = 0.0;
    long double dx = 0.0001;

    //Count number of calls
    num_calls_dp++;

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

//Function to compute derivatives of func(x) without DP
long double df_dx_no_DP(long double x, int n) {
    long double f = 0.0;
    long double dx = 0.0001;

    //Count number of calls
    num_calls_no_dp++;

    if(n == 0) {
        f = func(x);
    }
    else if(n > 0) {
        f = (df_dx_no_DP(x + dx, n - 1) - df_dx_no_DP(x, n - 1))/dx;
    }

    return f;
}

int main(int argc, char* argv[]) {

    //Highest derivative order
    int N = 4;

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

    //Compute derivative of order N using dynamic programming
    long double x = 1.0;
    long double y = df_dx(x, x, N);

    //Print results
    printf("y: %f\n", (double) y);

    //Compute derivative of order N using dynamic programming and obj
    CalcDerivative* der = new CalcDerivative(x, N);
    long double y2 = der->get_result();

    //Print results
    printf("y: %f\n", (double) y2);

    //Compute the derivative without dynamic programming solution
    long double y3 = df_dx_no_DP(x, N);

    //Print results
    printf("y: %f\n", (double) y3);

    //Print number of calls
    printf("number of calls using dp: %i\n", num_calls_dp);
    printf("number of calls without dp: %i\n", num_calls_no_dp);

    printf("done\n");

    return 0;
}
