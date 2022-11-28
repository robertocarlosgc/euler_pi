// =================================================================
//
// File: Eulerpi_parallel_forkjoin.java
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile:
//              javac Eulerpi_parallel_forkjoin.java
//
// SIZE = 100_000_000
// Serial time:  3244.6 ms
// Parallel time: 634.2 ms
// Speedup: 5.1160
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class Eulerpi_parallel_forkjoin extends RecursiveTask<Double>{
    private static final int SIZE = 100_000_000;
	private static final int MIN = 100_000;
	private int start, end;

    public Eulerpi_parallel_forkjoin(int start, int end) {
		this.start = start;
		this.end = end;
	}

    protected Double computeDirectly() {
		double result = 0;
		for (int i = start; i < end; i++) {
			result += Math.pow(-1, i)*4 / ((i*2)+1);
		}
		return result;
	}

    @Override
    protected Double compute() {
        // TODO Auto-generated method stub
        if ( (end - start) <= MIN ) {
			return computeDirectly();
		} else {
			int mid = start + ( (end - start) / 2 );
			Eulerpi_parallel_forkjoin lowerMid = new Eulerpi_parallel_forkjoin(start, mid);
			lowerMid.fork();
			Eulerpi_parallel_forkjoin upperMid = new Eulerpi_parallel_forkjoin(mid, end);
			return upperMid.compute() + lowerMid.join();
		}
    }

    public static void main(String args[]){
        long startTime, stopTime;
		double ms, result = 0;
		ForkJoinPool pool;

        System.out.println("Starting with "+ Utils.MAXTHREADS +" threads");
		ms = 0;
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			pool = new ForkJoinPool(Utils.MAXTHREADS);
			result = pool.invoke(new Eulerpi_parallel_forkjoin(0, SIZE));

			stopTime = System.currentTimeMillis();
			ms += (stopTime - startTime);
		}
		System.out.println("sum = " + result);
		System.out.println("avg time = " + (ms / Utils.N) + " ms");
    }

}