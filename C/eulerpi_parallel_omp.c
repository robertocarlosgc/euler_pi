// =================================================================
//
// File: eulerpi_parallel_omp.c
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile using math.h
//              and the omp.h libraries:
//              gcc eulerpi_parallel_omp.c -lm -fopenmp
//
// SIZE = 100_000_000
// Serial time: 1,532.68780 ms
// Parallel time: 250.30 ms
// Speedup: 6.123403
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "utils.h"

#define SIZE 100000000 //1e8

double calculate_pi(int size){
    double pi = 0;

    #pragma omp parallel for shared(size) reduction(+:pi)
    for(int i=0; i<size; i++){
        pi += pow(-1, i)*4 / ((i*2)+1);
    }

    return pi;
}

int main(){
    double ms, result = 0;

    printf("Starting...\n");
	ms = 0;
    for(int i=0; i<N; i++){
        start_timer();
        result = calculate_pi(SIZE);
        ms+=stop_timer();
    }
    
    printf("Calculated value of PI = %lf\n", result);
    printf("Real PI = %f\n", M_PI);
    printf("Percent error = %f\n", abs(result-M_PI)/M_PI * 100);
    printf("avg time = %.5lf ms\n", (ms / N));
    return 0;
}
