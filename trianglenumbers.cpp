#include <iostream>
#include <vector>

using namespace std;

using num = int;
using digit=int;
const digit base=10;
 using Num = vector<digit>;
  using constNum = const Num;
  
int MyVar;
int MyVar1;

 
 // DRY = Don't Repeat Yourself
     void print(Num R, num n=0){
                              num N = R.size();  
                               if(n>N or n==0)n=N;
                                for (num i=0; i<n; i++)cout << (num)R[i]<<" ";
                                 if(n<N)cout<<" ... ";
                                  cout<<endl;
     }
     void rprint(Num R, num n=0){
                               num N = R.size();
                                if(n>N or n==0)n=N;
                                 cout<<"[ "; 
                                  if(n<N)cout<<" ... ";
                                   for (num i=n-1; i>=0; i--)cout << (num)R[i]<<" ";
                                    cout<<"]"<<endl;
     }

   void addD(Num &Q, digit x){// Q[] += x; add to  long number Q[] digit x 
             Q[0] += x;
             for (int i=0; i<Q.size()-1;++i) {
                     if(Q[i]>=base){
                                 Q[i] -= base;
                                 Q[i+1] += 1;  
                     } else break; 
             }    
     
   }
  
        Num add_D(const Num Q, const digit x){// R[]= Q[] + x; add to long number Q[] digit x and return result R[]
                     Num R(Q);
                     num N= Q.size();
                      R[0] += x;
                       for (int i=0; i<N;++i) {
                            if(R[i]>=base){
                                            R[i] -= base;
                                            if(i==N-1){R.resize(N+1);}
                                             R[i+1] += 1;  
                            } else break; 
                       }    
                         return R; 
        } 
    Num operator+(const digit x,const Num Q){ return add_D(Q,x); }    
    Num operator+(const Num &Q, const digit x){ return add_D(Q,x); }

        Num add(const Num &Q, const Num &P){  // R[] = Q[]+ P[] ; add to long number Q[] long number P[] and return result R[]
                                             Num R(Q);
                                             num M = Q.size();
                                             num N = P.size();
                                             
                                              //R.resize(N); 
                                             //cout << "\n add: Q=";rprint(Q);
                                             //cout << "\n add: P=";rprint(P);
                                             //cout << "\n add: R(Q)=";rprint(R);
                                             // cout << endl; 
                                             digit carry=0;
                                               for(int i=0; i<N; i++)
                                               {
                                                 R[i] += (P[i]+carry);
                                                  if(R[i]>=base){
                                                                  if(i==N-1){R.resize(N+1); R[N]=1;}
                                                                  carry=1;
                                                                  R[i] -= base;
                                                                 } 
                                                        else       carry=0;     
                                               }
                                              // cout << "\n add: R=Q+P=";rprint(R);
                                              //  cout << endl; 
                                                return R;
        }
    Num operator+(const Num Q, const Num P){ return add(Q,P);}      


     using D2 = pair<digit,digit>;
            D2 multDigits(const digit a, const digit b){ //multiply two digits a,b and return p(least digit of product), q(major digit of product == carry))
                                                         digit p, q;   
                                                         num x = a*b;
                                                          p = x%base;
                                                          q = x/base;
                                                           return make_pair(p,q);
            }
        Num multD(const Num Q, const digit x){// Q[] *= x; multiply Q[] by digit x
                                    num N=Q.size();
                                     Num C;
                                      C.resize(N,0);
                                    Num R(Q);
                                    
                                    D2 t;
                                     for(int i=0; i<N; i++) {
                                      t = multDigits(Q[i],x);
                                       R[i]=t.first;
                                        if(i==N-1 and t.second>0){R.resize(N+1); C.resize(N+1);}
                                         C[i+1]=t.second;
                                     }
                                        //R = R+C;
                                        return R+C;
        }
        Num operator*(const Num Q, const digit x) {return multD(Q,x);}
        Num operator*(const digit x, const Num Q) {return multD(Q,x);}

            Num copyWithShift(const Num P, const int shift=0){//Q[] <---shift--- P[]
                              num N = P.size(); 
                               num M = N +shift;
                              Num Q;
                                Q.resize(M, 0);     
                                 for(int i=N-1; i>=0; i--) Q[i+shift] = P[i];
                                 //cout << "\n copyWithShift (shift="<<shift<<") before return : Q=";rprint(Q);
                                  return Q;
            }
        Num mult(const Num Q, const Num P){  // Q[] *= P[]
                                    num M = Q.size();
                                    num N = P.size();
                                    cout << "\n mult: Q=";rprint(Q);
                                    cout << endl;
                                    /*
                                    
                                    cout << "\n mult: P=";rprint(P);
                                    cout << "\n mult: Q.size()="<<M;
                                    cout << "\n mult: P.size()="<<N<<endl;
                                    */
                                     num K = M + N;
                                    Num W(Q); //W[] -- work array (accumulator) for long multiplication
                                          W.resize(K);
                                    /*      
                                    cout << "\n mult: W=";rprint(W);                                          
                                    cout << endl;
                                    */
                                    Num U; //U[] -- additional work array for long multiplication
                                     
                                     W = W*P[0] ;        //W[]*=P[0]  -- initial multiplication of W[] by P[0]  
                                     cout << "\n mult: W_0 = W*"<< P[0] <<"=";rprint(W);                                          
                                      for(int i=1; i<N; i++) {
                                          U = copyWithShift(Q, i);    //U[] = (Q[] shifted by i digits)
                                          cout << "\n mult: U=copyWithShift(Q,"<< i <<")=";rprint(U);                                          
                                           
                                           U = U*P[i];           //U[]*=P[i] -- multiplication of U[] by digit P[i]
                                            cout << "\n mult:  U = U*"<< P[i] <<"=";rprint(U);                                          
                                            cout << "\n mult: before accumaluation W_"<<i<<" = ";rprint(W);                                          
                                            W = W + U;                // W[]+=U[] -- accumulation of multiplication results
                                            cout << "\n mult: W_"<<i<<" = W+=U =";rprint(W);                                          
                                       }
                                       cout << endl;
                                       if(W[K-1]==0)W.resize(K-1);
                                        return W ;          // resulted W[]
         }
        


int main(){
    cout << "MyVar ="<<MyVar<<endl; 
    cout << "MyVar1="<<MyVar1<<endl; 
    cout << " &MyVar="<<&MyVar<<endl; 
    cout << "&MyVar1="<<&MyVar1<<endl; 
    int MyVarinmain;
    int MyVar1inmain;
    cout << "MyVarinmain="<<MyVarinmain<<endl; 
    cout << "MyVar1inmain="<<MyVar1inmain<<endl; 
    cout << "&MyVarinmain="<<&MyVarinmain<<endl; 
    cout << "&MyVar1inmain="<<&MyVar1inmain<<endl; 
    int  * MyDynamicVarPointer = new int;
    cout << "*MyDynamicVarPointer="<<*MyDynamicVarPointer<<endl; 
    cout << "address of MyDynamicVar="<<MyDynamicVarPointer<<endl; 

    cout << "Hello Max from cout! Welcome Github!!!!"<<endl; 
    return 0; 
    printf("Hello Max from printf()! 123456789 = %x \n", 123456789);
    printf(" char with code %d is char a, char with code 0 is %c and string %s\n", 'a', 0, "a");
    Num V, U, Q;
   /* 
    constNum c = {1, 2, 3};
              c[1] = 5;
   const int x = 1;
              x =2;     
               x++;
                cout << "x="<<x<<endl;
               rprint(c);
   */               
     V = {1,9,9};

      try {
               V.at(1000)=7; //Safe code, but slow! 
            // V[1000]=7; //Danger code, but quick?!!!!
      }
       catch(exception& ex) {
        cout <<  ex.what() << endl;
       }
     
      cout<<"V = ";rprint(V);
       V = add_D(V, 5);
       cout<<" V = add_D(V, 5) =  ";rprint(V);
        U = 3 + V;    
         cout<<"  U = V + 3 = ";rprint(U);
         Q = U + V; 
          cout<<"   Q = U + V = ";rprint(Q);
           D2 test = multDigits(9,9);
            cout<<"9*9 = "<<test.second<< " " <<test.first <<endl;                
             cout<<"V = ";rprint(V);
               V = multD(V, 2);
                cout<<"V*2 = ";rprint(V);
               V =  2 * V;
                cout<<"V*2*2 = ";rprint(V);
                V= mult(U,Q);
                 cout<<"U*Q= ";rprint(V);
                 //1993005

     /*
      printf("size of v is %ld \n",v.size() );
       for(int i=100; i<110; ++i) v.push_back(i);

        v.resize(20);
         for(int i=0; i<v.size(); ++i)cout << v[i]<<endl;
     */
       

           return 0; 
}