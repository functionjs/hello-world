/*
https://basecamp.eolymp.com/en/problems/37
Mail of Sponsor

Input
First line contains three integers — the number of post offices n (1≤n≤10^5),
 the number of post office the sponsor uses s (1≤s≤n) 
 and the number of links between the pairs of offices k (0≤k≤10^5).

Each of the next k lines contains two numbers: a and b — the numbers of post offices, 
 between which the mail transportation exists 
  (a and b are different numbers from interval [1;n]). 
   All the pairs (a,b) are different.

Output
Print one number — the minimum possible number of new connections to be created, 
 so that the mail can be delivered from s to any other post office.

Examples
Input #1
5 1 4
1 2
2 3
1 3
4 5
Answer #1
1
*/
#include <bits/stdc++.h>
//#include <iostream>
//#include <vector>
//#include <set?>

using namespace std;
using Vi= vector<int>; 
using Si= set<int>; 
using  VVi= vector<Vi>; 

int n;
int s;
int k;
int a,b; 
 VVi Adj;
 //Vi Visited;  
 Si notVisited;  
int c=0; // number of clouds (ans = c-1)

    void dfs(int node){ // dfs frome the node
         if(!notVisited.contains(node))return;
         
         //Visited[node] = true;
         notVisited.erase(node);
          for(int neighbor : Adj[node]) {
             if (notVisited.contains(neighbor)) {
                dfs(neighbor);
             }
          }
    }

int main(){
   cout << "Version2.0\n";
   cin >> n >> s >> k;
    Adj.resize(1+n);
    for(int node=1; node<=n; node++)
        notVisited.insert(node);
    //Visited.resize(1+n); // Visited vector[1+n] consisted of 0 (false)
     for(int i=0; i<k; i++) {
         cin >> a >> b;
          Adj[a].push_back(b);
          Adj[b].push_back(a);
     }
      
       for(auto node: notVisited){
               c++;
               cout << "notVisited.size()="<< notVisited.size() << " node="<< node <<" c="<<c<<endl;
                dfs(node);
               cout << "after dfs(node);"<< " notVisited.size()="<< notVisited.size()<<endl;
                
       }
        cout << c-1 << endl;   
         return 0;
}
/*
Adjacency matrix for these data
   1  2  3  4  5  n
1  .  *  *  .  .
2  *  .  *  .  .
3  *  *  .  .  .
4  .  .  .  .  *
5  .  .  .  *  . 
n

Adjacency List
1: 2 3
2: 1 3
3: 1 2
4: 5
5: 4   



Incidence matrix
  1 2 3 4 5  n
1 * * . . .
2 . * * . .
3 * . * . .
4 . . . * *
k
*/










    