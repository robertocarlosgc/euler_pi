// =================================================================
//
// File: eulerpi_parallel_tbb.cpp
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile using math.h library:
//              g++ eulerpi_parallel_tbb.cpp -lm -ltbb
//
// SIZE = 100_000_000
// Serial time: 2373.42 ms
// Parallel time: 392.131 ms
// Speedup: 6.0526
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include<iostream>
#include <iomanip>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include <math.h>
#include "utils.h"

#define SIZE 10000 //1e8

using namespace std;
using namespace tbb;

class CalculatePI{
    private:
        int size;
        double result;
    
    public:
        CalculatePI(int s) : size(s){}
        CalculatePI(CalculatePI &x, split): result(0) {}
    
    double getResult() const{
        return result;
    }

    void operator()(const blocked_range<int> &r){
        for(int i=r.begin(); i!=r.end(); i++){
            result += pow(-1, i)*4 / ((i*2)+1);
        }
    }

    void join(const CalculatePI &x) {
		result += x.result;
	}
};


int main(){
    double ms, result = 0;

    cout << "Starting..." << endl;
	ms = 0;
    CalculatePI obj(SIZE);
    for(int i=0; i<N; i++){
        start_timer();
        parallel_reduce(blocked_range<int>(0, SIZE), obj);
        result = obj.getResult();
        ms+=stop_timer();
    }
    
    cout << "Calculated value of PI = " << result/N << endl;
    cout << "Real PI = " << M_PI << endl;
    cout << "Percent error = " << abs((result/N)-M_PI)/M_PI << endl;
    cout << "avg time = " << (ms / N) << " ms" << endl;
    return 0;
}