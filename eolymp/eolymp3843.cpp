/*
Primes
https://basecamp.eolymp.com/en/problems/3843
Execution time limit is 10 seconds

Runtime memory usage limit is 256 megabytes
Let m and n (2<=m<n<=10^7) be two integers. 

Consider the following set:
Prime(m,n) = { p | p prime and m<=p<=n }.

Find the cardinality of the set Prime(m,n).

Input
Consists of several tests. 
The input of each test is represented on a single line. 
Any two consecutive tests are separated by an empty line. 
For each test, the values for m and n are given on the same line, 
separated by exactly one space.

Output
For each test, the result will be written on a different line 
(the tests will have the same order as in the input). 
The results of any two consecutive tests will be separated by an empty line. 
For each test, the result will be the cardinal of the set Prime (m,n).

Examples
Input1
4 12

70 110

5 150
Answer1
3

10

33
*/
#include <bits/stdc++.h>
using namespace std;

const int Max=1e7;
 bool notP[1+Max]; //not Prime: default notP[x]=false :  all x are primes by default
 bool M[1+Max];   //Memorized: default M[x]=false
 int  prefixSum[1+Max];

     
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
 
 void evaluatePrefixSum(){
      for(int x=2; x<=Max; x++)prefixSum[x] = prefixSum[x-1] + !notP[x];  
 }

     int cardinalityOfPrimes(int m,int n){
           int c = !notP[m];
                c+= prefixSum[n] - prefixSum[m];  
                 return c;
     }

int main() {
//int t0=clock();
   initBySieveOfEratosthenes();
//int t1=clock();
    evaluatePrefixSum();
//int t2=clock();    
// cout << "initBySieveOfEratosthenes() time="<< (t1-t0)/1000000.0 <<"s"<<endl;
// cout << "evaluatePrefixSum() time="<< (t2-t1)/1000000.0 <<"s"<<endl;

    int m, n;
     while(cin>>m>>n)
           cout<<cardinalityOfPrimes(m,n)<<endl<<endl;
    
      return 0;
}

// approximated number of primes in [1..n] is n/log(n)