//USACO 2023 December Contest, Silver
//Problem 2. Cycle Correspondence
//https://usaco.org/index.php?page=viewproblem2&cpid=1351
#include <iostream> // import sys
#include <vector>
#include <map>

using namespace std;

using V = vector<int>;

int N,K, x,y;
V a,b,S;

int main(){
    cout << "Hello cycles correspondence!!!"<<endl;
    cin >> N >> K;
     a.resize(K);  // a[] Annabelle cycle labels has size K
     b.resize(K);  // b[]    Bessie cycle labels has size K
     S.resize(N+1);  // S[] (vector of set of all labels) has size N but we use S[] from index 1 to index N 

      for(int i=0; i<K; i++) cin >> a[i]; //input a[]
      for(int j=0; j<K; j++) cin >> b[j]; //input b[]
      // array b[] is primitive map   j -->b[j]  
      // We can create M[] -- inverse map  b[j]-->j  to quick search position of label b[j] in Bessie cycle
      map<int,int> M;
       for(int j=0; j<K; j++) M[b[j]]=j;
        cout << "M:"<<endl; for(int j=0; j<K; j++) cout << b[j] << "-->"<< M[b[j]]<<endl;
        
     // External part (x)
      for(int n=1; n<=N; n++) S[n] = 1;  // generate set S
       // E = S - a - b 
       for(int i=0; i<K; i++) S[a[i]] =0 ;
       for(int j=0; j<K; j++) S[b[j]] =0 ;

        for(int n=1; n<=N; n++) if(S[n]>0) x++;  // count external parts

     // Internal part (y)
        V count(K, 0);
       /* 
        // first brute force variant 
         for(int shift=0; shift<K; shift++){
             for(int i=0; i<K; i++){
                  int j= i+shift;
                   if(j>=K)j-=K;
                    if(a[i]==b[j]) count[shift]++;  
             }
              if(y<count[shift])y=count[shift];
         }
       */

        // second brute force variant 
         //iterate over all elements of a vector a[]
        /* 
         for(int i=0; i<K; ++i){
             // Bessie clockwise cycle search b[j] for shift
             for(int j=0; j<K; ++j){
                  if(a[i]==b[j]){
                     int shift = i - j;  
                      if(shift<0) shift+=K; 
                       count[shift]++; 
                  }
             }
              // find maximal of counts for all clockwise cycle shifts
              for(int shift=0; shift<K; ++shift){
                  if(y<count[shift]) y=count[shift];
              }
         }
        */ 
         //---
          for (int i = 0; i<K; ++i){
              if (M.find(a[i]) != M.end()) {
                  int J = M[a[i]];
                    cout << " for a["<<i<<"]="<<a[i] << " Bessie index J="<<J<<endl;
                   int shift = (i - J + K) % K;
                    count[shift]++;
              }
          }
           for (int shift = 0l shift<K; ++shift){
               y = max(y, count[shift]);
           }
         //---
         /*
          count.clear();
         //iterate over all elements of a vector a[]
         for(int i=0; i<K; ++i){
             // Bessie counterclockwise cycle search b[j] for shift
             for(int j=0; j<K; ++j){
                  if(a[i]==b[j]){
                     int shift = j - i;
                      if(shift<0) shift+=K; 
                       count[shift]++; 
                  }
             }
              // find maximal of counts for all shifts
              for(int shift=0; shift<K; ++shift){
                  if(y<count[shift]) y=count[shift];
              }
         }
         */
         /*
         for(int shift=0; shift<K; shift++){
            count=0;
             for(int i=0; i<K; i++){
                  int j= K-i-1-shift;
                   if(j<0)j+=K;
                  if(a[i] == b[j]) count++;  
            }
              if(y<count)y=count;
         }
         */
/*
 cout <<"N="<< N  << " K=" << K <<endl;
 
    for(int i=0; i<K; i++) cout << a[i] << " ";
     cout << endl;
     for(int i=0; i<K; i++) cout << b[i] << " ";
     cout << endl;
      for(int i=1; i<=N; i++) cout << S[i] << " ";
     cout << endl;
       cout << " x=" << x<< endl;
       cout << " y=" << y<< endl;
*/
        cout 
            //<< " answer is " 
             << x+y << endl;

 return 0;
}

/*
SAMPLE INPUT:
6 3
1 2 3
2 3 1
SAMPLE OUTPUT:
6
*/

/*
input = sys.stdin.readline()
print = sys.stdout.write()
*/

/*
    position 1  2  3  4  5
Vector  b:  [2, 5, 3, 1, 4] 2 5 3 1 4 

Invector  :  [4  1  3  5  2]
 position b   1  2  3  4  5




    position 1   2   3  4   5
Vector  b:  [20, 13, 5, 1,  6] 
Vector  a:  [7 , 4, 20, 5, 13] 

 We make 0 different elements of a and b 
 Vector  b1:  [20, 13, 5,  0,  0] 
 Vector  a1:  [0 , 0 , 20, 5, 13] 
 
  We renumerate non  zero elements of a and b 
  Vector  b2: [1,  2, 3,  0,  0] 
  Vector  a2: [0 , 0 , 1, 3,  2] 
 
*/
