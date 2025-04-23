/*
https://basecamp.eolymp.com/en/problems/3728
The undirected graph is given. Two types of operations are performed on graph in the given order:
cut — cut a graph, or delete an edge from a graph;
ask — check, whether two given vertices lie in the same connected component.

It is known that after performing all types of cut operations there is no edges left in the graph. Give the result for each ask operation.

Input
The first line contains three integers — the number of vertices n in a graph, 
 the number of edges m and the number of operations k 
 (1≤n≤50000,0≤m≤10^5,m≤k≤150000).



Examples
Input #1
3 3 7
1 2
2 3
3 1
ask 3 3
cut 1 2
ask 1 2
cut 1 3
ask 2 1
cut 2 3
ask 3 1
Answer #1
YES
YES
NO
NO

*/
#include <iostream>

using namespace std;


const int MaxN = 1+50000;
const int MaxM = 1e5;
const int MaxK = 150000;
int Query[MaxK][3];
string ans[MaxK];

   // structures and methods of Disjoint Sets Union                             
   int Parent[MaxN];
         void make_one_element_set (int v) {
    	                                        Parent[v] = v;
         }
                                    
        int findSuperParentOf(int v) {
                                        int p = Parent[v];
        	                                 if (v == p)return p; // in this situation v is self Super Parent

        	                                   return Parent[v] = findSuperParentOf(p);
        }
     
    void union_sets_of(int v1, int v2) {
    	                                int  p1 = findSuperParentOf(v1);
    	                                int  p2 = findSuperParentOf(v2);
    	                                 if (p1 != p2) Parent[p2] = p1;
                                       
    }

int main(){

  int n, m, k;
   cin >> n >> m >> k;
  int u, v;
   for (int i=0; i<m; i++) {
       cin >> u >> v; //dumb input of (u,v) because we will restore whole net from cuts!
   }
  string a; // a may be "cut" else "ans"
  int L=0, T; // L is number of answers, T is the type of query: 0=cut 1=ans 
    for (int j=0; j<k; j++) {
       cin >> a >> u >> v;
        T= (a=="ask");
         L += T;
         Query[j][0]=T;
        Query[j][1]=u;
        Query[j][2]=v;
    }
      //cout << "l="<<l<<endl;

      //initialization of sets in DSU
      for (int i=1; i<=n; i++) make_one_element_set(i);
      
       // from last to first query:   
       int l=L-1;
       for(int j=k-1; j>=0; j--){
        // todo with ans[], cut queries and DSU
        // .....
         u = Query[j][1];
         v = Query[j][2];
          if (Query[j][0] == 0) {
           union_sets_of(u, v);
          } else {
               int  p1 = findSuperParentOf(u);
    	         int  p2 = findSuperParentOf(v);
    	          if (p1 != p2) ans[l]="NO";
                    else      ans[l]="YES";
                 l--;   
                   
            }
       }

        //"reverse" output of ans[]
        for(int l=0; l<L; l++){  
           cout << ans[l] << endl;
        }

   return 0;
}