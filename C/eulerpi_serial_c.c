#include <stdio.h>
#include <math.h>

int main(){
    double pi = 0;
    int i, den = 1;

    for(i=1; i<100; i++){
        pi += pow(-1, i+1)*4/den;
        den += 2;
    }
    printf("Calculated value of PI = %lf", pi);
    return 0;
}
