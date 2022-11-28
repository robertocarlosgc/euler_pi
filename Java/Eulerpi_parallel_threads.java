// =================================================================
//
// File: Eulerpi_parallel_threads.java
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile:
//              javac Eulerpi_parallel_threads.java
//
// SIZE = 100_000_000
// Serial time:  3244.6 ms
// Parallel time: 641.0 ms
// Speedup: 5.0617
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

public class Eulerpi_parallel_threads extends Thread{
    private static final int SIZE = 100_000_000;
    private int start, end;
	private double result;

    public Eulerpi_parallel_threads(int start, int end) {
		this.start = start;
		this.end = end;
		this.result = 0;
	}

    public double getResult() {
		return result;
	}

	public void run() {
		result = 0;
		for (int i = start; i < end; i++) {
			result += Math.pow(-1, i)*4 / ((i*2)+1);
		}
	}

    public static void main(String args[]){
        long startTime, stopTime;
		int block;
		Eulerpi_parallel_threads threads[];
		double ms;
		double result = 0;

        block = SIZE / Utils.MAXTHREADS;
		threads = new Eulerpi_parallel_threads[Utils.MAXTHREADS];

        System.out.println("Starting with "+ Utils.MAXTHREADS +" threads...");
        ms = 0;
        for (int j = 1; j <= Utils.N; j++) {
			for (int i = 0; i < threads.length; i++) {
				if (i != threads.length - 1) {
					threads[i] = new Eulerpi_parallel_threads( (i * block), ((i + 1) * block) );
				} else {
					threads[i] = new Eulerpi_parallel_threads( (i * block), SIZE);
				}
			}

			startTime = System.currentTimeMillis();
			for (int i = 0; i < threads.length; i++) {
				threads[i].start();
			}
			/** -------- */
			for (int i = 0; i < threads.length; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			stopTime = System.currentTimeMillis();
			ms +=  (stopTime - startTime);

			if (j == Utils.N) {
				result = 0;
				for (int i = 0; i < threads.length; i++) {
					result += threads[i].getResult();
				}
			}
		}
		System.out.println("sum = " + result);
		System.out.println("avg time = " + (ms / Utils.N) + " ms");
    }
}