// =================================================================
//
// File: eulerpi_serial_cpp.cpp
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile using math.h library:
//              g++ eulerpi_serial_cpp.cpp -lm
//
// SIZE = 100_000_000
// Serial time: 2373.42 ms
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include<iostream>
#include <math.h>
#include "utils.h"

#define SIZE 100000000 //1e8

using namespace std;

class CalculatePI{
    private:
        int size;
        double result;
    
    public:
        CalculatePI(int s) : size(s){}
    
    double getResult() const{
        return result;
    }

    void calculate(){
        result = 0;

        for(int i=0; i<size; i++){
            result += pow(-1, i)*4 / ((i*2)+1);
        }
    }
};


int main(){
    double ms, result = 0;

    cout << "Starting..." << endl;
	ms = 0;
    CalculatePI obj(SIZE);
    for(int i=0; i<N; i++){
        start_timer();
        obj.calculate();
        ms+=stop_timer();
    }
    
    cout << "Calculated value of PI = " << obj.getResult() << endl;
    cout << "Real PI = " << M_PI << endl;
    cout << "Percent error = " << abs(obj.getResult()-M_PI)/M_PI << endl;
    cout << "avg time = " << (ms / N) << " ms" << endl;
    return 0;
}