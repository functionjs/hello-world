/*
https://basecamp.eolymp.com/en/problems/4481
https://basecamp.eolymp.com/en/problems/4481#editorial
In the Country of Unlearned Lessons
Input
The first line contains the number of elements n (1≤n≤10^5) in array. 
The second line contains n integers — the elements a_i (1≤a_i≤10^9 )of array. 
The third line gives the number of queries m (1≤m≤10^5).
Each of the next m lines contains three integers q,l,r (1≤l≤r≤n).

If q=1, find the GCD of elements on an interval [l,r];
If q=2, change the element at position l to number r.

Output
For each query with number 1 print the answer on a separate line.

Examples
Input #1
5
2 4 6 10 8
6
1 1 5
1 2 3
2 5 15
2 3 10
1 3 5
1 1 5
Answer #1
2
2
5
1
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using Vi = vector<int>;

 Vi SegTree;
int n, m;
int H;
int neutral_element = 0;  // neutral element for gcd

      //
     ////
    ////////
    void buildTree(int v, int lpos, int rpos){
          if(v>=H/2)return;
           int mid = (lpos + rpos)/2;
              buildTree(2*v,     lpos, mid);
              buildTree(2*v + 1, mid + 1, rpos);
               SegTree[v] = __gcd(SegTree[2*v], SegTree[2*v + 1]);
    }
           //
          ////
         /////
         int getGCD(int v,  int lpos, int rpos,  int left, int right){
                     if (left > right) return neutral_element;
                     if (left==lpos  and right == rpos) return SegTree[v];

                      int mid = (lpos + rpos)/2;
                       return __gcd(getGCD(2*v,     lpos,     mid,  left      , min(right, mid)),
                                    getGCD(2*v + 1, mid + 1, rpos,  max(left, mid + 1), right));
         }
    int queryGCD(int l, int r) {
                                return getGCD(1, 1,H/2,  l,r);    
    }

           //
            //
         //
        void update(int v,  int lpos, int rpos,    int pos, int val){
          if (lpos == rpos) SegTree[v] = val;
          else{
               int mid = (lpos + rpos)/2;
                if (pos <= mid) update(2*v,     lpos,    mid,    pos, val);
                else            update(2*v + 1, mid + 1, rpos,   pos, val);
                  SegTree[v] = __gcd(SegTree[2*v], SegTree[2*v + 1]);
          }
        }
    void changeValue(int l, int r){
                                   update(1, 1, H/2,  l,r);
    };   

int main(){
    cout <<"100!:" ;
     long f=1;
     for(int i=1; i <=100; i++){f*=i; cout << f << " ";}  
      cout << endl;
    cin >> n;
     int h = (int)(ceil(log2(n))+1); // segTree height
      H = 1<< h;                     //  segTree volume
       SegTree.resize(H, neutral_element);
        for(int i=0; i<n; i++)
            cin >> SegTree[H/2 + i]; //input in segTree leafs
         buildTree(1, 1, H/2);       // build segTree upper nodes 

         cin >> m;
         int q,l,r;    
          for (int i=0; i<m; i++) {
            cin >>q >>l >>r; 
             if(q==1) cout << queryGCD(l,r) << endl;   // query GCD on segment [l,r]  
             else            changeValue(l,r);        // change value in position l to r
          }
          
           return 0;
}
/*
a: 21  15  3   6
     segTree
        _3
    _21     3  
  21 _42  3   6

 [0][1][2][3][4][5][6][7] 
  0  3  3  3 21 15  3  6


a: 2  4  6  10  8
           segTree
              2
        2            8 
     2     2      8     0
   2  4  6  10  8   0  0  0
                    neutral element of gcd is 0  


   2 
     2 8 
         2 2 8 0 
                 2 4 6 10 8 0 0 0  

   gcd(a,b) 
     neutral element of gcd is 0 ! 
     a@b    ?@b=b     0@b=b     

   lcm(a,b)
     neutral element of lcm is 1 ! 
     a#b      
*/