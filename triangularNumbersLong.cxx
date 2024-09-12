#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>

//Hello Max! How are you now?


using namespace std;
// const int base=16;  //   0 1 2 3 4 5 6 7 8 9 A B C D E F
const int base = 10; //     0 1 2 3 4 5 6 7 8 9
using digit = char;
using num   =  int;


// O(N^2)
const num  N=9;
 // digit X[N]={8,7,2};
digit X[N] = {9,8,7,6,5,4,3,2,1};//{4,3,2,1,5,4,3,2,1};
digit Y[N] = {0};//{9,8,7,6,5,4,3,2,1};//{9,8,7,6,0,0,0,0,0};
digit Zero[N]={0}; 

digit qu[N];
digit rem;
// digit Y[N]={5,3,0};
 digit Z[N];
 digit C[N];
    
     // DRY = Don't Repeat Yourself
     void print(digit R[],int n=N){
                             if(n>N)n=N;
                              for (num i=0; i<n; i++)cout << (int)R[i]<<" ";
                               if(n<N)cout<<" ... ";
                                cout<<endl;
     }
     void rprint(digit R[],int n=N){
                           if(n>N)n=N;
                            cout<<"[ "; 
                             if(n<N)cout<<" ... ";
                              for (num i=n-1; i>=0; i--)cout << (int)R[i]<<" ";
                               cout<<"]"<<endl;
    }

     void set1234_(digit R[],int n){//R[]={0,1,2,3,...,n}%base
                              for (num i=0; i<n; i++){
                                  R[i] = i % base ;
                                  //  X[i] = (int)(abs(sin(i))*i) % base ;
                              }
     }
     void set0000_(digit R[],int n){//R[]={0,0,0,....,0,0}
                               for (num i=0; i<n; i++)R[i] = 0; //  *(R+i) = 0;
     }
     void memset0000_(digit R[],int n){//R[]={0,0,0,....,0,0}
                               memset(R,'\0',n*sizeof(digit)); 
     }
     void set1111_(digit R[],int n){//Q[]={1,1,1,....,1,1}
                                    for (num i=0; i<n; i++)R[i] = 1;
     }
     void memset1111_(digit R[],int n){//Q[]={1,1,1,....,1,1}
                                        memset(R,'\1',n*sizeof(digit)); 
     }
     void set111_0(digit R[],int n){//Q[]={1,1,1,....,1,0}
                                     for (num i=0; i<n-1; i++)R[i] = 1;
     }

     void addD(digit Q[], digit x){// Q[] += x;
                                   digit  carry = 0;
                                   Q[0] += x;
                                    for (int i=0; i<N-1 and (carry =  (Q[i]>=base)?1:0) ;++i) {
                                         Q[i] %= base;
                                         Q[i+1] += carry;  
                                    }    
     }
            void multDigits(digit a, digit b,  digit& p, digit& q){
                                                                   num x = a*b;
                                                                    p = x%base;
                                                                    q = x/base;
            }
        void multD(digit Q[], digit x){// Q[] *= x
                                      C[0]=0;
                                       for(int i=0; i<N-1; i++){
                                           multDigits(Q[i],x,  Q[i],C[i+1]);
                                            Q[i] %= base;
                                       }
                                        for(int i=1; i<N; i++){
                                                 Q[i] += C[i];
                                        }
                                     
       }
/*  Test example of multiplition of long number by digit (multD)
     (1)(3)(4)(0)  -- carry values
         2  7  8
  *      0  0  5 
        --------
         0  5  0    q- mult values (mod base)

  +   1  3  4  0     
      ------------
      1  3  9  0     -- result is  summ of q mult values and carry values
*/
        void copyWithShift(digit Q[], digit P[], int shift=0){//Q[]=P[]
                                                   for(int i=0; i<shift; i++) {
                                                       Q[i] = 0;
                                                    }
                                                     for(int i=0; i+shift<N; i++) {
                                                        Q[i+shift] = P[i];
                                                     }
        }
        void add(digit Q[], digit P[]){  // Q[]+=P[]
                                     digit carry=0;
                                      for(int i=0; i<N; i++)
                                      {
                                        Q[i] += (P[i]+carry);
                                         //carry = Q[i]/base;
                                          if(Q[i]>=base){
                                                         carry=1;
                                                         Q[i] -= base;
                                                        } 
                                               else       carry=0;     
                                      }
        }
    void mult(digit Q[], digit P[]){  // Q[] *= P[]
                                  digit W[N]; //W[] -- work array (accumulator) for long multiplication
                                  digit U[N]; //U[] -- additional work array for long multiplication
                                   copyWithShift(W,Q,0); //W[]=Q[]  -- initial assignment of W[]
                                    multD(W,P[0]);        //W[]*=P[0]  -- initial multiplication of W[] by P[0]  
                                     for(int i=1; i<N/2; i++) {//N/2 -- number of safe digits in P[] and Q[] for multiplication
                                       copyWithShift(U,Q,i);    //U[] = (Q[] shifted by i digits)
                                        multD(U,P[i]);           //U[]*=P[i] -- multiplication of U[] by digit P[i]
                                         add(W,U);                // W[]+=U[] -- accumulation of multiplication results
                                        }
                                      copyWithShift(Q,W);          //Q[] = resulted W[]
    }

/*******Test example of multiplition of long number 278 by long number 035 (for mult)
         2  7  8
  *      0  3  5 
        --------
         0  5  0 
     (1)(3)(4)(0)
                         1 3 9 0    
      6  1  4  .      
  (0)(2)(2)
                       0 8 3 4 0 
  +   1  3  4  0      ============
                       0 9 7 3 0    
      ------------
      1  3  9  0 
*********************/

/*  Test example for division of long number by digit (divD)
        0 5 5  -- qoutient
    5 | 2 7 8  -- whole dividend,  2 -- current dividend, 27 -- next current dividend
        0   |
        2 5 |    
        --- V
        0 2 8  -- next next current dividend
          2 5
          ---
          0 3  -- remainder
*/
        void divD(digit Q[], digit d,  digit Quot[], digit &rem){//  (Q[]/d)->(Quot[],rem)
                                num q=0; 
                                 for(int i=N-1; i>=0;i-=1){
                                     q = q*base + Q[i]; // evaluating current dividend
                                      Quot[i] = q/d;  // Euclid division -- getting current Quotient digit by dividing current dividend by one digit divisor d
                                       q%=d;          // Euclid division -- getting current remainder
                                 }     
                                  rem = q;            // last remainder is result too!    
        }
/*
      123451234
    - 000006789
      ---------
      123455555
   -      1111  <-- carries 
      ------------          
      123444445
*/
             //To Do!
             void subD(digit Q[], digit x){ //
                 
             }    

             void sub(digit Q[], digit P[]){  // Q[]-=P[]
                     digit carry=0;
                      for(int i=0; i<N; i++)
                         {
                           Q[i] -= (P[i]+carry);
                            if(Q[i]<0){
                                       carry=1;
                                       Q[i] += base;
                                      } 
                                  else  carry=0;     
                         }
             }
            // To Do! Hello Max! How are you now?
             bool ge(digit Q[], digit P[]){  // Q[] >= P[]  return true  but if Q[] < P[] return false
                for (int i=N-1; i>=0; --i){
                    if (Q[i] > P[i])return true;
                    if (Q[i] < P[i])return false;
                }
                 return true;
             }    
             bool eq(digit Q[], digit P[]){  // if Q[] == P[]  (return true) else (return false)
                 for (int i=N-1; i>=0; --i){
                     if (Q[i] != P[i])return false;
                 }
                  return true;
              }    


        // let it be simple (dumb?) universal algorithm without bothering about sizes of numbers  
        void dumbdiv(digit Q[], digit P[],  digit Quot[], digit Rem[]){//  (Q[]/P[])->(Quot[],Rem[])
                  // Copy Q into Rem to start the division process
                  if(eq(P, Zero)) {cout<<"Division by zero!"<<endl; exit(13);}
                  copyWithShift(Rem, Q); 
                   while(ge(Rem, P)){// while  Rem[] > P[]
                                      sub(Rem, P); // Rem[] -= P[]
                                      addD(Quot, 1);  //Quot[] += 1;
                                   }
        }    
         // How to optimize that code?
        void optimizeddiv(digit Q[], digit P[],  digit Quot[], digit Rem[]){//  (Q[]/P[])->(Quot[],Rem[])
              // Copy Q into Rem to start the division process
              
              copyWithShift(Rem, Q); 
               while(ge(Rem, P)){// while  Rem[] > P[]
                                  sub(Rem, P);
                                  addD(Quot, 1);
               }  
        }    
/*
     let Q[] has N digits, P[] has M digits,  
     then Quot[]= Q[]/P[] has maximum N-M+1 digits (if N>=M),
          Rem[] = Q[]%P[] has maximum M digits

     123456789/1234  Quot[] = 100046 has 6 digits Rem[]=0025 has 2 digits
     123456789/2345  Quot[] =  52646 has 5 digits Rem[]=1919 has 4 digits
      Numerator   Denominator
     123456789 | 000001234
                              <----- Quotient





                     <====  remander        
*/
     void divByBot(digit Q[], digit P[], digit Quot[], digit Rem[]) {
    digit temp[N]; // Temporary array to hold intermediate results
    memset0000_(Quot, N); // Initialize Quotient array to 0
    memset0000_(Rem, N);  // Initialize Remainder array to 0

     // Copy Q into Rem to start the division process
     copyWithShift(Rem, Q); 

      for (int i = N - 1; i >= 0; i--) {
         // Shift remainder left by base to incorporate next digit of Q
         for (int j = N - 1; j > 0; j--) {
             Rem[j] = Rem[j - 1];
         }
          Rem[0] = 0;

           // Add current digit of Q to the remainder
           Rem[0] = Q[i];

           // Find the largest digit d such that d * P <= Rem
           for (digit d = base - 1; d > 0; d--) {
               memset0000_(temp, N);
                copyWithShift(temp, P);
                 multD(temp, d);
               bool canSubtract = true;
                  for (int j = N - 1; j >= 0; j--) {
                       if (Rem[j] < temp[j]) {
                                              canSubtract = false;
                                               break;
                       } else if (Rem[j] > temp[j]) {
                                                     break;
                              }
                 }  

                 if (canSubtract) {
                                   Quot[i] = d;
                                    add(Rem, temp); // Subtraction is effectively adding the negative
                                     break;
                 }
        }
    }
}

int main() {
   /* 
    int z=10;
         z=z+z-z; // perplexing for some c++ compilers
          z*=z;
           z*=z;
            z*=z;
             z*=z; //Huge number ?
              X[z]=1;  // breaking the program!
   */  
   
int a = 0;
int b = 1;
 int c = 0;
      c = a/b;
  cout<<c<<endl;
   
bool XeqY = eq(X,Y);
bool YeqZero = eq(Y,Zero);
 cout << "eq(X,Y)="<< XeqY<<endl; 
 cout << "eq(Y,Zero)="<< YeqZero<<endl; 
         
     cout<<"X[]: ";rprint(X);
     cout<<"Y[]: ";rprint(Y);
     cout<<"initial value of Z[]: ";rprint(Z);
     cout<<"initial value of C[]: ";rprint(C);

      //int Ntest=987654321;       
      //for(int i=0; i< Ntest; i++) addD(Z,1);       
      // cout<<"value of Z[] after " <<  Ntest << " addition of 1 is  ";rprint(Z);
  //return 0;
long t0=clock();  
      dumbdiv(X,Y,Z,C);
long t1=clock();  
  cout <<"Time to divide array X[] by Y[] is "<<t1-t0<<" μs"<<endl;
       cout<<"Z[]=X[]/Y[]: ";rprint(Z);
       cout<<"C[]=X[]%Y[]: ";rprint(C);
        return 0;
    
  t0=clock();  
    memset1111_(X, N/2);
  t1=clock();  
     cout <<"Time to initialize array is "<<t1-t0<<" μs"<<endl;
    set1111_(Y, N/2);
     cout << "X[]   :"; print(X,20);
     cout << "Y[]   :"; print(Y,20);
t0=clock();    
       mult(X, Y);
t1=clock();    
        cout << "X[]*Y[]: "; print(X,20);
        cout <<"Time to multiply super long numbers ("<<N/2<<" digits) is "<<t1-t0<<" μs"<<endl;
         return 0;
}

// IDE -  Integrated Development Environment

// 1 + 2 + 3 + ...  + n-2 + n-1 + n =  (1+n)n/2
// Proof 1
// (1 + (2 + (3 + ...  + n-2) + n-1) + n) =  (1+n)n/2
// Proof 2
//  1 +  2  +  3  + ... + n-2 + n-1 + n
//  n + n-1 + n-2 + ... + 3   +  2  + 1
// +------------------------------------------
// 1+n 1+n ...........................1+n     =(1+n)n  

// #include <iostream>

// using namespace std;

// int main() {
//   cout << "How many circular and trianglular numbers?\n Input n:";
//   int n;
//   cin >> n;
//   int counter = 0;
//   for (int i = 0; i <= n; i++) {
//     int triangular = i * (i + 1) / 2;
//     if (triangular%10 == 0) {
//       cout << triangular << endl;
//       counter++;
//     }
//   }
//   return 0;
// }

// i*(i+1)/2
// i = multiple of 4
