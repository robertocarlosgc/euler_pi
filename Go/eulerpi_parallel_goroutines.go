// =================================================================
//
// File: eulerpi_parallel_goroutines.go
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile:
//              go run eulerpi_serial_go.go
//
// SIZE = 100_000_000
// Serial time: 10897.6999 ms
// Parallel time: 2404.7984 ms
// Speedup: 4.5316
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

package main

import (
	"fmt"
	"math"
	"runtime"
	"time"
)

const SIZE = 100_000_000
const N = 10

// calculatePi launches n goroutines to compute an
// approximation of pi.
func calculatePi(size int) float64 {
	n_threads := runtime.NumCPU()
	block := size/n_threads

	ch := make(chan float64)
	for i := 0; i < n_threads; i++ {
		if i != n_threads-1{
			go term(ch, i*block, (i+1)*block)
		} else{
			go term(ch, i*block, size)
		}
	}
	f := 0.0
	for k := 0; k < n_threads; k++ {
		f += <-ch
	}
	return f
}

func term(ch chan float64, start int, end int) {
	acum := 0.0
	for i:=start; i<end; i++{
		acum +=	math.Pow(-1, float64(i))*4 / ((2*float64(i)) + 1)
	}
	ch <- acum
}

func main(){
	var start time.Time
	var elapsed time.Duration
	var result float64

	fmt.Printf("Starting with %v threads...\n", runtime.NumCPU())
	for i:=0; i<N; i++{
		start = time.Now()		
		result = calculatePi(SIZE)
		elapsed = time.Since(start)
	}

	fmt.Printf("Calculated value of PI = %f\n", result)
	fmt.Printf("Real PI = %f\n", math.Pi)
	fmt.Printf("Percent error = %f\n", math.Abs(result-math.Pi)/math.Pi*100)
	fmt.Printf("avg time = %s\n", elapsed)
}