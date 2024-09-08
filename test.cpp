#include <iostream>
#include <stdio.h>
#include <cmath>
#include <omp.h>
//testing real acceleration on computer
using namespace std;


        long double function(long double t) { 
          return (4.0 / (1.0 + t * t)); 
        }


    void calculate_pi(long n, int num_threads) {
      long double h, x, sum, pi;
    
       h = 1.0 / n;
      
        double t0 = omp_get_wtime();
         sum =0.0;       
          ////////////////////////////////////////////////////////////////////////////
          #pragma omp parallel for private(x) num_threads(num_threads) reduction(+:sum) 
           for (long long i = 0; i < n; i++) {
             x = h * (i - 0.5);
              sum += function(x);
           }
            double t1 = omp_get_wtime();
      
             pi = h * sum;
              printf("threads: %d | pi = %Lf | time = %f \n", num_threads, pi, t1-t0);
    }

int main() { 
  long long ns = 10;
   for(int pown = 4; pown <= 10; pown+=2){
     long long n = pow(ns,pown);
      printf("n = 10^%d_= %lld_________________________________\n", pown, n);
       for(int threads = 1; threads <= 8; threads+=1){
         calculate_pi(n, threads);
       }
   }
}
