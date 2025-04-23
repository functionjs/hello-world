/*
https://basecamp.eolymp.com/en/problems/11498
Maximum prime factor
Medium
Found an issue or missing something? Help us improve this problem.
Execution time limit is 1 second
Runtime memory usage limit is 128 megabytes
Find the largest prime factor of a number n.

Input
One positive integer n(n≤10^14).

Output
Print the largest prime factor of a number n.

Examples
Input #1
100
Answer #1
5
*/
#include <bits/stdc++.h>
using namespace std;

const int Max=1e7;
 bool notP[1+Max]; //not Prime: default notP[x]=false :  all x are primes by default
 bool M[1+Max];   //Memorized: default M[x]=false
    void initBySieveOfEratosthenes(){
      notP[0]=true;M[0]=true;
      notP[1]=true;M[1]=true;
      
      notP[2]=false;M[2]=true;
      for(int i=2*2; i<=Max; i+=2){
          notP[i]=true;
          M[i]   =true;
      }
      int q=sqrt(Max);
       for(int x=3; x<=q; x+=2){
          if(M[x])continue;

            M[x]=true;
            //notP[x]=false; //by default
            for(int i=x*x; i<=Max; i+=2*x){
               notP[i]=true;
               M[i]   =true;
            };
      }  
}

    inline bool isPrime(int x){
                     return not notP[x];   
        }

     long maxPrime(long n){
         long mP=n; //init assumption
          if(mP<=Max and isPrime(mP))return mP;

            int q=sqrt(mP);
             for(int x=2; x<=q; x++){
                 if(notP[x])continue; // x is not prime
                   //here x is prime
                   if(mP%x > 0) continue; // maxP is not divided by prime x
                     //here x is prime  and maxP is divided by x
                     while(mP%x ==0){
                            mP/=x;
                     }
                      if(mP==1)return x; //because x is last prime that divided maxP  
                      if(mP<=Max and isPrime(mP))return mP;

                        q=sqrt(mP);  
               }               
                 return mP;
     }

     long MaxPrime(long n){
                       
                  if(n==2) return 2;
                  if(n==3) return 3;
                 
                   
                    while(n%2==0)n/=2;
                     if(n==1)return 2;

                       while(n%3==0)n/=3;
                        if(n==1)return 3;

                        int q=sqrt(n);
                         while(q*q==n){
                               n=q; 
                                q=sqrt(n); 
                         }    
                          for(int x=5; x<=q; x+=2){
                             if(n%x>0)continue; 
                              while(n%x==0){
                                   n/=x;
                              }
                               if(n==1)return x;
                                q=sqrt(n);
                          }   
                            return n;
     } 

int main() {
  // initBySieveOfEratosthenes();
    long n;
     cin>>n;
      long mp = MaxPrime(n);
       cout<<mp<<endl;

        return 0;
}

// Example 1
//  46 = 2*23
// Example 2
//  2*2*2*2*2*2*11 = 352
// Example 3
//  11*13*13 = 1829    sqrt(1829)=42.7....
// Example 2
//  2*2*2*2*2*2*11*13 = 9152
//    2*2*2*2*2*11*13 = 4576
//      2*2*2*2*11*13 = 2288
//        2*2*2*11*13 = 1144
//          2*2*11*13 =  572
//            2*11*13 =  286
//              11*13 =  143
//                 13 =  13

// Primes in segement [9999900, 10000000] 
//9999901, 9999907, 9999929,  9999931,  9999937,  9999943, 9999971, 9999973, 9999991 (9 primes)

// 99998020009801 = 9999901*9999901,  time to evaluate = 0.014498 s
// 99998080009207 = 9999901*9999907,  time to evaluate = 0.014494 s