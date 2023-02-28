#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
    int N = 0;
    int x = 0;
    double sumXi = 0, sumXiSquared = 0;
    double average = 0, standardDeviationSquared = 0;
    while(1){
        scanf("%i", &x);
        if(x == -1) break;
        N++;
        sumXi += x;
        sumXiSquared += pow(x, 2);
    }
    average = (1/(float)N) * sumXi;
    standardDeviationSquared = (1/(float)N)*(sumXiSquared - 2*average*sumXi + ((float)N)*pow(average, 2));
    double standardDeviation = sqrt(standardDeviationSquared);

    printf("Media = %lf\n", average);
    printf("Desvio = %lf\n", standardDeviation);
}