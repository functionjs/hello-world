#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>

//Hello Max! How are you now?


using namespace std;
using digit = char;
 // const digit base=16;  //   0 1 2 3 4 5 6 7 8 9 A B C D E F
 const digit base = 10; //     0 1 2 3 4 5 6 7 8 9
using num  =  int;
 const num  N = 10;
  using Num   =  digit[N];


// O(N^2)

  // char X[N]={8,7,2};
  // char * X;
  // char X[];

 // digit X[N]={8,7,2};
 // digit Y[N]={5,3,0};
static Num X = {9,8,7,6,5,4,3,2,1};//{4,3,2,1,5,4,3,2,1};
static Num Y = {4,3,2,1};//{9,8,7,6,5,4,3,2,1};//{9,8,7,6,0,0,0,0,0};
static Num Zero ={0}; 
static Num One={1};

static Num qu;
static digit rem;

 static Num Z;
 static Num C;
    
     // DRY = Don't Repeat Yourself
   static  void print(Num R, num n=N){
                             if(n>N)n=N;
                              for (num i=0; i<n; i++)cout << (digit)R[i]<<" ";
                               if(n<N)cout<<" ... ";
                                cout<<endl;
     }
   static   void rprint(Num R, num n=N){
                           if(n>N)n=N;
                            cout<<"[ "; 
                             if(n<N)cout<<" ... ";
                              for (num i=n-1; i>=0; i--)cout << (int)R[i]<<" ";
                               cout<<"]"<<endl;
    }


     void set0000_(Num R, const num n=N){//R[]={0,0,0,...}
                               for (num i=0; i<n; i++)R[i] = 0; //  *(R+i) = 0;
     }
     void memset0000_(Num R, num n=N){//R[]={0,0,0,...}
                               memset(R,'\0',n*sizeof(digit)); 
     }
     void set1111_(Num R, num n=N){//R[]={1,1,1,...}
                                    for (num i=0; i<n; i++)R[i] = 1;
     }
     void memset1111_(Num R, num n=N){//Q[]={1,1,1,...}
                                        memset(R,'\1',n*sizeof(digit)); 
     }
     void setx(Num R, digit x=1, num n=N){//R[]={x,x,x,...}
                                for (num i=0; i<n; i++)R[i] = x;
     }
     void set0123_(Num R, num n=N){//R[]={0,1,2,3,...}%base
                          for (num i=0; i<n; i++)R[i] = i % base ;
     }
    void setPseudoRandom(Num R, num n=N, num seed=0){//R[]={?,??,???,????,...}%base
                      for (num i=0; i<n; i++)R[i] = (digit)(abs(sin(i+seed))*i) % base;
                      
    }

     void addD(Num Q, digit x){// Q[] += x; add to  long number Q[] digit x 
                                   Q[0] += x;
                                    for (int i=0; i<N-1;++i) {
                                         if(Q[i]>=base){
                                                        Q[i] -= base;
                                                        Q[i+1] += 1;  
                                         } else break; 
                                    }    
     }
                void sum(Num Q, const Num P){ // Q[i]+=P[i];  simple sum of the elements of array Q with the corresponding elements of array P  
                                 for(int i=0; i<N; i++)Q[i]+=P[i];
                }
                void getCarryAndNormalize(Num Q, Num C){
                                      C[0]=0;
                                      for(int i=0; i<N-1; i++){
                                          C[i+1]=0;
                                           if(Q[i]>=base){
                                                          C[i+1]=1;
                                                          Q[i] -= base;
                                                         } 
                                      }    
                }
            void add_(Num Q, Num P){  // Q[]+=P[] ; add to long number Q[] long number P[]
                                            Num C; // Carry vector
                                            sum(Q,P);        // 9 9 9 + 9 9 9  = 18 18 18
                                             getCarryAndNormalize(Q, C);  // Q[]= 8 8 8  C[] = 1 1 1 0
                                              sum(Q,C);        // 8 8 8 + 1 1 1 0 = 1 9 9 8
            }
            void add(Num Q, Num P){  // Q[]+=P[] ; add to long number Q[] long number P[]
                                         digit carry=0;
                                          for(int i=0; i<N; i++)
                                          {
                                            Q[i] += (P[i]+carry);
                                             if(Q[i]>=base){
                                                             carry=1;
                                                             Q[i] -= base;
                                                            } 
                                                   else       carry=0;     
                                          }
            }
                                                          //digit *p, digit *q  
            void multDigits(const digit a, const digit b,  digit& p, digit& q){ //multiply two digits a,b and return p(least digit of product), q(major digit of product == carry))
                                                                   num x = a*b;
                                                                    p = x%base;
                                                                    q = x/base;
            }
        void multD(Num Q, digit x){// Q[] *= x; multiply Q[] by digit x
                                      C[0]=0;
                                       for(int i=0; i<N-1; i++) multDigits(Q[i],x,  Q[i],C[i+1]);
                                        add(Q,C);
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

        void copyWithShift(Num Q, Num P, int shift=0){//Q[] <---shift--- P[]
                                                   for(int i=N-(shift+1); i>=0; i--) Q[i+shift] = P[i];
                                                   for(int i=0; i<shift; i++) Q[i] = 0;
        }
        num length(Num Q){
            for(int length=N-1; length>=0 ; length--) if(Q[length]!=0) return length+1;
             return 0;
        }    
    void mult(Num Q, Num P){  // Q[] *= P[]
                            Num W; //W[] -- work array (accumulator) for long multiplication
                            Num U; //U[] -- additional work array for long multiplication
                             copyWithShift(W,Q); //W[]=Q[]  -- initial assignment of W[]
                              multD(W,P[0]);        //W[]*=P[0]  -- initial multiplication of W[] by P[0]  
                               for(int i=1; i<N/2; i++) {//N/2 -- number of safe digits in P[] and Q[] for multiplication
                                   copyWithShift(U,Q, i);    //U[] = (Q[] shifted by i digits)
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

/*  Test example for division of long number by digit (divD)
        0 5 5  -- qoutient
    5 |(2)7 8  -- whole dividend,  2 -- current dividend, 27 -- next current dividend
        0    
        --
        (2)7     
        ---
          (2)8  -- next next current dividend
          ---
            (3)  -- remainder
*/
        void divD(Num Q, digit d,  Num Quot, digit &rem){//  (Q[]/d)->(Quot[],rem)
                                num r=0; 
                                 for(int i=N-1; i>=0;i-=1){
                                     r = r*base + Q[i]; // evaluating current dividend
                                      Quot[i] = r/d;  // Euclid division -- getting current Quotient digit by dividing current dividend by one digit divisor d
                                       r%=d;          // Euclid division -- getting current remainder
                                 }     
                                  rem = r;            // last remainder is result too!    
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
             void subD(Num Q, digit x){ //Q[] -= x; subtract from long number Q[] digit x
                 
             }    

             void sub(Num Q, Num P){  // Q[]-=P[]
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

             bool gt(Num Q, Num P){  // Q[] > P[]  return true  but if Q[] <= P[] return false
                                   for (int i=N-1; i>=0; --i){
                                       if (Q[i] > P[i])return true;
                                       if (Q[i] < P[i])return false;
                                   }
                                    return false;
             }    
             bool ge(Num Q, Num P){  // Q[] >= P[]  return true  but if Q[] < P[] return false
                                   for (int i=N-1; i>=0; --i){
                                       if (Q[i] > P[i])return true;
                                       if (Q[i] < P[i])return false;
                                   }
                                    return true;
             }    
             bool eq(Num Q, Num P){  // if Q[] == P[]  (return true) else (return false)
                                   for (int i=N-1; i>=0; --i){
                                       if (Q[i] != P[i])return false;
                                   }
                                    return true;
              }    


        // simple (dumb?) universal algorithm without bothering about sizes of numbers  
        void dumbdiv(Num Q, Num P,    Num Quot, Num Rem){//  (Q[]/P[])->(Quot[],Rem[])
                     if(eq(P, Zero)) {cout<<"Division by zero! Program terminated."<<endl; exit(13);}
                       // Copy Q into Rem to start the division process
                       copyWithShift(Rem, Q); //Rem[]= Q[]
                        while(ge(Rem, P)){// while  Rem[] >= P[]
                                          sub(Rem, P); // Rem[] -= P[]
                                          addD(Quot, 1);  //Quot[] += 1;
                                         }
                         // return;  
        }    
         // How to optimize that code?
        void optimizeddiv(Num Q, Num P,    Num Quot, Num Rem){//  (Q[]/P[])->(Quot[],Rem[])
                          
                          if(eq(P, Zero)) {cout<<"Division by zero! Program terminated."<<endl; exit(13);}
                          if(eq(Q, Zero)) {set0000_(Quot); set0000_(Rem); return;}           
                          if(eq(Q, P))    {set1111_(Quot,1); set0000_(Rem); return;}           
                          if(eq(P, One))  {copyWithShift(Quot, Q); set0000_(Rem); return;} 
            
                           num lQ=length(Q);
                           num lP=length(P);
                           // Copy Q into Rem to start the division process
                           copyWithShift(Rem, Q); 
                           set0000_(Quot);
                            if(lQ<lP) return; 
                            if(lQ==lP){ 
                               if(gt(P,Rem))return;
                                
                                while(ge(Rem,P)){// while  Rem[] >= P[]
                                                 sub(Rem, P); //Rem[] -= P[]
                                                 addD(Quot, 1); // Quot[] +=1;
                                }  
                                 return;
                            }

                            // lQ>lP  (most complex case)
                            Num X;
                            Num P_;
                            num shift;
                             while(ge(Rem,P)){  
                                              shift = length(Rem)-lP;
                                               copyWithShift(X, One, shift);
                                               copyWithShift(P_, P, shift);
                                                if(ge(Rem,P_)){
                                                   copyWithShift(P_, P, shift-1);
                                                   copyWithShift(X, One, shift-1);
                                                }
                                                 while(ge(Rem,P_)){// while  Rem[] >= P[]
                                                                sub(Rem, P_); //Rem[] -= P_[]
                                                                add(Quot, X); // Quot[] +=X[];
                                                 }  
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
    memset0000_(Quot); // Initialize Quotient array to 0
    memset0000_(Rem);  // Initialize Remainder array to 0

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
              X[z]=1;  // breaking the program for clang compiler ? No! It is only runtime exception...
  */  
  /*  
    set0000_(X);
    set0000_(Y);
     //set0123_(X,5);
     cout << "X length = "<<length(X)<<endl; 
     rprint(X);
       copyWithShift(X, X, 3); 
        rprint(X);
         cout << "new X length = "<<length(X)<<endl; 
*/         
   /* 
    set0000_(Y);
     set0123_(Y,7);
     rprint(Y);
     add_(X,Y);
      rprint(X);
   */   
cout << "Test division by zero of integer numbers (clang++):" <<endl;   
int a = -4;
int b = 0;
 int c = 0;
  double x=(double)a/double(b); 
   double y=1/x; 
  cout << "x=a/b="<< x << "   y=1/x="<<y<<"  x*y=" <<x*y<<endl; 
    try {
          x= sqrt(a);
          c = a/b;  // anomalous behavior of that program line for clang compiler? No! It throws "Floating point exception (core dumped)"!  
    }
     catch(exception& ex) {
        cout << "Cathed Error during division!!! Denominator is 0 ... "<< ex.what() << endl;
    }
    
     
      cout<<"Result of division is "<<c<<endl;
  
    
//bool XeqY = eq(X,Y);
//bool YeqZero = eq(Y,Zero);
// cout << "eq(X,Y)="<< XeqY<<endl; 
// cout << "eq(Y,Zero)="<< YeqZero<<endl; 
         
     cout<<"X[]: ";rprint(X);
     cout<<"Y[]: ";rprint(Y);
     cout<<"initial value of Z[]: ";rprint(Z);
     cout<<"initial value of C[]: ";rprint(C);

      //int Ntest=987654321;       
      //for(int i=0; i< Ntest; i++) addD(Z,1);       
      // cout<<"value of Z[] after " <<  Ntest << " addition of 1 is  ";rprint(Z);
  //return 0;
long t0=clock();  
          optimizeddiv(X,Y, Z,C);
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