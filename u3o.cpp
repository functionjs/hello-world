//USACO 2024 December Contest, Silver
//Problem 3. 2D Conveyor Belt
//https://usaco.org/index.php?page=viewproblem2&cpid=1448

#include <bits/stdc++.h>
//#include <iostream>
//#include <vector>
//#include <algorithm>
using namespace std; 
 
const int MAX = 1005;
const int di[] = {0, 0, -1, 1};
const int dj[] = {-1, 1, 0, 0};
const char allDirs[] = {'L', 'R', 'U', 'D'};
 
int n, q, curGood, good[MAX][MAX], dir[MAX][MAX]; 
 
            bool inside(int i, int j){
                return i >= 1 and i <= n and j >= 1 and j <= n;
            }
        bool isGood(int i, int j){
            // Checks if in and is usable
            if (!inside(i, j))
                return false;
         
             for (int d = 0; d < 4; d++){
                 // If it has a direction and d is not that direction
                 if (dir[i][j] != -1 and d != dir[i][j])
                     continue;
          
                  int ni = i + di[d];
                  int nj = j + dj[d];
          
                   // Good if pointing outside or towards an good cell
                   if (!inside(ni, nj) or good[ni][nj])
                      return true;
             }
              return false;
        }

    void dfs(int i, int j){
        if (!isGood(i, j) or good[i][j])
            return;
        
         good[i][j] = true;
         curGood++;
     
          for (int d = 0; d < 4; d++)
              dfs(i + di[d], j + dj[d]);
    }
 
int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0); 
    //cin >> n >> q;
    scanf("%d %d", &n, &q);
     
    // -1 meaning it can be anything
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dir[i][j] = -1;
    
    vector<int> res;
     vector<tuple<int, int, char>> upds(q);

     for (auto &[r, c, t] : upds){
         //cin >> r >> c >> t;
          scanf("%d %d %c", &r, &c, &t);
          dir[r][c] = find(allDirs, allDirs + 4, t) - allDirs;
     }
 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dfs(i, j);
    
    reverse(upds.begin(), upds.end());
 
    for (auto [r, c, t] : upds){
        res.push_back(n * n - curGood);
 
        dir[r][c] = -1;
        dfs(r, c);
    }
 
    reverse(res.begin(), res.end());
 
    for (int i : res)
       // cout << i << "\n";
        printf("%d\n", i);
}