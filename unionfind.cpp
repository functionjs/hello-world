/*
https://basecamp.eolymp.com/ru/problems/8798
ДСУ

Problem Statement
We have an undirected graph with N vertices and 0 edges. 
Process the following Q queries in order:
t_i = 0 u_i v_i  : Add an edge 
t_i = 1 u_i v_i  : If vertices u,v are connected, print 1
                   Otherwise, print 0

Constraints
1≤N≤2×10^5
1≤Q≤2×10^5
0≤u_i,v_i<N
 
Sample
#1
4 7
1 0 1
0 0 1
0 2 3
1 0 1
1 1 2
0 0 2
1 1 3

Reply
0
1
0
1

*/

#include <iostream>

using namespace std;


const int MaxSize = 2e5;

  // structures and methods of Disjoint Sets Union                             
  int Parent[MaxSize];
        void make_one_element_set (int v) {
   	                                        Parent[v] = v;
        }
                                   
       int findSuperParentOf(int v) {
                                       int p = Parent[v];
       	                                 if (v == p)return p; // in this situation v is self Super Parent
                                         
                                           Parent[v] = findSuperParentOf(p);
       	                                     return Parent[v];
       }
    
   void union_sets_of(int v1, int v2) {
   	                                int  p1 = findSuperParentOf(v1);
   	                                int  p2 = findSuperParentOf(v2);
   	                                 if (p1 != p2) Parent[p2] = p1;
   }

   int main(){
     int n, q;
      cin >> n >> q;
       for(int i=1; i<=n; ++i){
           make_one_element_set(i);
       }
          
      int T, a,b;
       for(int k=0; k<q;++k){
           cin >> T >> a >> b;
            // todo!
            if(T==0){
               union_sets_of(a, b);   
            } 
            if(T==1){
                int SP1 = findSuperParentOf(a);
                int SP2 = findSuperParentOf(b);
                 cout << (SP1==SP2) <<endl;
            }
       }
     


   }