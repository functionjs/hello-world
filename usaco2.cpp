//usaco 2025 february task2 c++ solution
#include <bits/stdc++.h>

using namespace std;
using Vi = vector<int>;
using Si = set<int>;
 using VSi = vector<Si>; 

int N;
Vi P;
VSi C;
Vi L;
Vi W;

    void printP(){
                   cout << "P[]: ";
                    for (auto num: P) {
                        cout << num << " ";
                    } 
                     cout << endl;
     }

     void printC(){
                    for (int i = 1; i <= N; i++) {
                        cout << "C["<<i<<"]: ";
                        for (auto num : C[i]) 
                            cout << num << " ";
                         cout << endl;     
                    }
      
     }

     void printL(){
                    cout << "L[]: ";
                     for (auto num: L) {
                          cout << num << " ";
                     } 
                      cout << endl;
     }


int main() {
     cin >> N;
      P.resize(N + 1);
      P[0] = -1;
       for (int i = 1; i <= N; i++) {
         cin >> P[i];
       }
        C.resize(N + 1);
         for (int i = 1; i <= N; i++) {
           C[P[i]].insert(i);
         }
          L.resize(N + 1, 0);
           for (int i = 1; i <= N; i++) {
                L[i] = L[P[i]] + 1;
          }
            int x;
             while(cin>>x) W.push_back(x);

              for(unsigned int i=0; i<W.size()-1; i++){
                 int widx = W[i];
                  int ci = widx;
                  int pi = P[widx];
                   while(C[pi].size() == 1){
                       ci = pi;
                        pi = P[pi];
                   }
                    cout << L[pi] + 1 <<endl; 
                    C[pi].erase(ci); // Complexity is O(log(n)) where n is the C[pi] length
              }        
               cout << 0 << endl;

                return 0;
}