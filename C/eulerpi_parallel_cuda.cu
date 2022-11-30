// =================================================================
//
// File: eulerpi_parallel_cuda.cu
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile using math.h library:
//              nvcc eulerpi_parallel_cuda.cu -lm
//
// SIZE = 100_000_000
// Serial time: 1,527.14200 ms
// Parallel time: 0.00300 ms
// Speedup: 509,047.3333
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>
#include "utils.h"

#define SIZE 100000000 //1e8
#define THREADS	256
#define BLOCKS	MMIN(32, ((SIZE / THREADS) + 1))

__global__ void calculate_pi(double *result) {
    __shared__ double cache[THREADS];

    int tid = threadIdx.x + (blockIdx.x * blockDim.x);
	int cacheIndex = threadIdx.x;

    double acum = 0;
	while (tid < SIZE) {
		acum += pow(-1, tid)*4 / ((tid*2)+1);
		tid += blockDim.x * gridDim.x;
	}

    cache[cacheIndex] = acum;

	__syncthreads();

    int i = blockDim.x / 2;
	while (i > 0) {
		if (cacheIndex < i) {
			cache[cacheIndex] += cache[cacheIndex + i];
		}
		__syncthreads();
		i /= 2;
	}

	if (cacheIndex == 0) {
		result[blockIdx.x] = cache[cacheIndex];
	}
}

int main(int argc, char* argv[]){
    double *results, *d_r;
    double ms;

    results = (double*) malloc( BLOCKS * sizeof(double));
    cudaMalloc( (void**) &d_r, BLOCKS * sizeof(double) );

    printf("Starting...\n");
    ms = 0;
    for(int i=0; i<N; i++){
        start_timer();
        calculate_pi<<< BLOCKS, THREADS >>>(d_r);
        ms += stop_timer();
    }

    cudaMemcpy(results, d_r, BLOCKS * sizeof(long), cudaMemcpyDeviceToHost);
    double acum = 0;
    for (int i = 0; i < BLOCKS; i++) {
		acum += results[i];
	}

    printf("Calculated PI = %lf\n", acum);
    printf("Real PI = %f\n", M_PI);
    printf("Percent error = %f\n", abs(acum-M_PI)/M_PI * 100);
	printf("avg time = %.5lf ms\n", (ms / N));

	cudaFree(d_r);

	free(results);
    return 0;
}