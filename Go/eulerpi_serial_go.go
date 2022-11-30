// =================================================================
//
// File: eulerpi_serial_go.go
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
	"time"
)

const SIZE = 100_000_000
const N = 10

func calculatePi(size int) float64{
	pi:=0.0

	for i:=0; i<size; i++{
		pi += math.Pow(-1, float64(i))*4/((float64 (i)*2)+1)
	}

	return pi
}

func main(){
	var start time.Time
	var elapsed time.Duration
	var result float64

	fmt.Println("Starting...")
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