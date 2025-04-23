#include <iostream>
#include <vector>

using namespace std;

using num = int;
using digit=int;
const digit base=10;
 using Num = vector<digit>;
  using constNum = const Num;
  


 
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
    Num operator+(const Num Q, const digit x){ return add_D(Q,x); }

        Num add(const Num Q, const Num P){  // R[] = Q[]+ P[] ; add to long number Q[] long number P[] and return result R[]
                                             Num R(Q);
                                             num N= Q.size();
                                              R.resize(N); 
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

int main(){
    cout << "Hello Max from cout! Welcome Github!!!!"<<endl; 
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

     /*
      printf("size of v is %ld \n",v.size() );
       for(int i=100; i<110; ++i) v.push_back(i);

        v.resize(20);
         for(int i=0; i<v.size(); ++i)cout << v[i]<<endl;
     */
       

           return 0; 
}