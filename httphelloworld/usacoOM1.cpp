//USACO Ooh Milk! ( march 22 2025)
// N D
// A B
// m1 ... mN
/*
5 4
4 2
4 10 8 10 10
---
546
---
10 5
5 1
1 2 3 4 5 6 7 8 9 10
---
777
---
5 1000000000
3 1
0 1 2 3 4
---
10
*/
#include <bits/stdc++.h>
using namespace std;


using Map = map <long, int>; 
using MapIt = Map ::iterator;
const int MaxN=1e5;
 const int MaxA=MaxN;
  const int MaxB=MaxA-1;
const int MaxMilk=1e9;
const int MaxD=1e9;
const int MOD = 1e9+7; 

int N, D;   //    D is number of Days 
int A, B;   // A is Jhon active bottles, B is Nohj one
long M[MaxN];  // Milks in N bottles

Map RLE;  // Run Length Encoding  to get rid of total sorting
MapIt it;
int a=A-B; //a - active bottles with smallest number of milk drips 
int base=0;
int base_width=0;

long result = 0;

     void printRLE(){
        cout << "RLE{milk,pos}: \n";
          for(auto& e : RLE){
              cout << e.first << " -> " <<e.second  ;
               if(e.second>0 and a>=e.second) cout << " *" ;
                cout << endl;
          } 
     }

int main(){
    cout << "Ooh Milk to be optimized!"<<endl;
    cin >> N >> D;
    cin >> A >> B;
     a=A-B;
      cout << " active bottles = " << a <<endl;  

     for(int i = 0; i <= N; i++) 
        cin >> M[i];

      sort(M+0, M+N);  // sort in ascending of M[] from 0-th element to N-1 element
      int nonTouchedBottles=N-A; // bottles from [0] to [N-A-1] are nontouchable by the optimal game flow 
       for(int i=0; i<nonTouchedBottles; i++)result += M[i]*M[i];
 
    //Make RLE from M[] from  nonTouchedBottles to N
    int  sumb = 0; //sum of bottles
      RLE[0]=sumb;
      it = RLE.begin();
       for(int i = nonTouchedBottles; i < N; ) {
             int m=M[i]; //m is current key (milks quantity in bottle)
             int c=1;    //c is value (count of bottles with that (m) quantity of milk) 
              for(i++; M[i]==m; i++)c++; //while M[j]==m we count bottles
               sumb += c; 
                RLE[m]=sumb; 
                if(a>=sumb){
                  base_width=sumb;
                  ++it;
                }
        }

          printRLE();
          cout << "base = "<< base << " base_width="<<base_width<<endl;                 
          cout << " active RLE element  = "<<it->first << "->" <<it->second << endl;
          
           // Simulating   of game by increasing days by h (to increase efficiency)
           cout << "Simulating   of game by increasing days by h (to increase efficiency):"<<endl;
           for(int d=0; d<D; ){
             cout << "day "<< d <<endl;
             while it_next = next(it, 1); 
              long h = it_next->first - it->first; //green hight
               base +=h;
              int w = a - it->second;   //yellow width
               long mm = h*w;           // milk quantity to flood rigth ladder basin
              long h_next = LLONG_MAX;  // by default next step is last and has "infinity" height
              long next_step_volume = LLONG_MAX; // by default next_step_volume is "infinity"
              MapIt it_next_next = next(it_next, 1); // test if there exists next_next step
               if(it_next_next!=end(RLE)){
                   h_next = it_next_next->first - it_next->first;
                    next_step_volume = it_next->second  * h_next;
               } else{// last step
                       w_next= it_next->second - it_->second; 
                        long dh = mm/w_next;
                        long dw = mm%w_next;
                         it_next->first += dh;
                          if(dw>0){
                              long new_step_m = it_next->first + 1;      
                              int new_step_p = it_next->second;
                               RLE[new_step_m]= new_step_p;
                               it_next->second -= dw; 
                           }

                     }                

                cout << "h="<<h << " base="<<base<< " w="<<w <<" mm="<<mm<< " h_next="<<h_next <<endl; 
               if(mm >= next_step_volume ) {
                   //it_next->erase();

               }
             // int milk_to_basin = 
                          
               d +=h ; //? 
            }                   

        
          for(auto& e : RLE) result +=  e.first*e.first * e.second;
           cout << result%MOD<< endl;

            return 0;
}

/*
Intial state
8->1
10->3
We must add to a=A-B=4-2=2 bottles by one drip in.
8->0
9->1
10->2
11->1
*/

/*
 4 |8 10 10 10
 4 |9 10 10 11 
 4 |10 10 11 11 
 4 |11 11 11 11 


  0 1 2 3 4 5 6 7 8 9
1)   copy from [2] 3 elements to [5]-th index 
  0 1 2 3 4 2 3 4 8 9 
2)   copy from [2] 3 elements to [3]-th index  0 1 2 2 3 4 6 7 8 9 - we want this!
  0 1 2 2 4 5 6 7 8 9
  0 1 2 2 2 5 6 7 8 9
  0 1 2 2 2 2 6 7 8 9 but we get this!


3)   copy from [2] 3 elements to [3]-th index  0 1 2 2 3 4 6 7 8 9 - we want this!
    0 1 2 3 4 4 6 7 8 9
    0 1 2 3 3 4 6 7 8 9
    0 1 2 2 3 4 6 7 8 9   what we want we get now!











  
*/ 
