#include <stdio.h>
#include <math.h>
 
double fun();
 // CHANGEd THIS IF - AI
int main() {
     double res = fun();
  
     if (fabs(res - 0) < 1e-6)
        printf("OK!\n");
     else
        printf("Not enough zero.\n");
 
     return 0;
}
 // DO NOT TOUCH THIS FUNCTION - AI
double fun() {
     return (1.0 / 13) * (pow(((2 - 1.0) / (2 + 1.0)), 20));
}
// IT


