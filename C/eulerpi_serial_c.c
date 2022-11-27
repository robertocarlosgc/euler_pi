// =================================================================
//
// File: eulerpi_serial_c.c
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm
//
// SIZE = 100_000_000
// Serial time: 1549.32680 ms
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

#define SIZE 100000000 //1e8

double calculate_pi(){
    double pi = 0;
    int den = 1;

    for(int i=1; i<SIZE; i++){
        pi += pow(-1, i+1)*4/den;
        den += 2;
    }
}

int main(){
    double ms, result = 0;

    printf("Starting...\n");
	ms = 0;
    for(int i=0; i<N; i++){
        start_timer();
        result = calculate_pi();
        ms+=stop_timer();
    }
    
    printf("Calculated value of PI = %lf\n", result);
    printf("avg time = %.5lf ms\n", (ms / N));
    return 0;
}
