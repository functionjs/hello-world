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

const int MaxN=1e5;
 const int MaxA=MaxN;
  const int MaxB=MaxA-1;
const int MaxMilk=1e9;
const int MaxD=1e9;
const int MOD = 1e9+7; 

int N, D;   //    D is number of Days 
int A, B;   // A is Jhon active bottles, B is Nohj one
long M[MaxN];  // Milks in N bottles
map <long, int> RLE;  // Run Length Encoding  to get rid of total sorting
map <long, int> ::iterator it;

long result = 0;

     void printRLE(){
        cout << "RLE{m,c}: \n";
          for(auto& e : RLE){
              cout << e.first << "->" <<e.second << endl;
          } 
     }

int main(){
    cin >> N >> D;
    cin >> A >> B;
     for(int i = 0; i <= N; i++) 
        cin >> M[i];

      sort(M+0, M+N);  // sort in ascending of M[] from 0-th element to N-1 element
      int nonTouchedBottles=N-A; // bottles from [0] to [N-A-1] are nontouchable by the optimal game flow 
       for(int i=0; i<nonTouchedBottles; i++)result += M[i]*M[i];
 
       //Make RLE from M[] from  nonTouchedBottles to N
       for(int i = nonTouchedBottles; i < N; ) {
             int m=M[i]; //m is current key (milks quantity in bottle)
             int c=1;    //c is value (count of bottles with that (m) quantity of milk) 
              for(i++; M[i]==m; i++)c++; //while M[j]==m we count bottles
               RLE.insert(make_pair(m, c));
                
        }

          int a=A-B; //a - active bottles with smallest number of milk drips 
            // Simulating   of game day by day (not too efficiently)
           for(int d=0; d<D; d++){
               it = RLE.begin();
                //deleting lowest unusable (with zeros quantities of bottles) elements of RLE
                while(it->second==0)it = RLE.erase(it);
                
                 int a_=a;
                 //ascending in RLE to find element  with current a_ <= it->second 
                  while(a_ > it->second){ a_ -= it->second; ++it;}
                   //increase next step bottles by a_,  may be creating next step if it does not exists
                   RLE[it->first +1] += a_;
                   //decrease current step of bottle by a_   
                   it->second -= a_;
                    if(a_==a){
                      //printRLE();                
                       continue;
                    }
                     --it;
                    //descending in RLE to RLE.begin() adding milk drips in bottles 
                      while(true){
                               //increase next step bottles by current it->second;  may be creating next step if it does not exists
                                 RLE[it->first +1] += it->second;
                                  it->second = 0; 
                                   if(it== RLE.begin())break;
                                    --it;  
                                 }
                    //printRLE();                
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
