// =================================================================
//
// File: Eulerpi_serial_java.java
// Author(s):
//          Roberto Carlos Guzmán Cortés A01702388
//
// Description: This file contains the code to calculate an
//              approximation of pi using the euler series
//              algorithm. How to compile:
//              javac Eulerpi_serial_java.java
//
// SIZE = 100_000_000
// Serial time:  3244.6 ms
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

public class Eulerpi_serial_java{
    private static final int SIZE = 100_000_000;
	private double result;

    public Eulerpi_serial_java(){
        result = 0;
    }

    public double getResult(){
        return result;
    }

    public void calculatePi(){
        result = 0;
        
        for(int i=0; i<SIZE; i++){
            result += Math.pow(-1, i)*4 / ((i*2)+1);
        }
    }

    public static void main (String args[]){
        long startTime, stopTime;
		double acum = 0;

        Eulerpi_serial_java e = new Eulerpi_serial_java();
        System.out.printf("Starting...\n");
		for (int i = 0; i < Utils.N; i++) {
			startTime = System.currentTimeMillis();

			e.calculatePi();

			stopTime = System.currentTimeMillis();

			acum += (stopTime - startTime);
		}
		System.out.println("sum = " + e.getResult());
		System.out.println("avg time = " + (acum / Utils.N) + "ms");
    }
}