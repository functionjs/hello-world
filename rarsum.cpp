/*

https://judge.yosupo.jp/problem/range_affine_range_sum

Range Affine Range Sum

Problem Statement
Given a size N, integer sequence  a_0,a_1,…,a_{N-1}.
 Process Q queries as follows:

0 l r b c: For each  i=l,l+1,…,r−1    a_i ← b×a_i + c.
                 r−1
1 l r    : Print  ∑ a_i mod 998244353.
                 i=l                 ​ 
Constraints: 
1 ≤ N,Q  ≤ 5×10^5
0 ≤ a_i,c< 998244353
1 ≤ b  <   998244353
0 ≤ l< r ≤ N

Input
N Q
a_0 a_1  ... a_{N−1}
Query_0
Query_1
:
Query_{Q−1}
​
 
#1 Input example
5 7
1 2 3 4 5
1 0 5
0 2 4 100 101
1 0 3
0 1 3 102 103
1 2 5
0 2 5 104 105
1 0 5
#1 Output
15
404
41511
4317767
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using Vi = vector<int>;

 Vi SegTree, B, C;
int n, m;
int h, H;
int neutral_b = 1;  // neutral b  part for b*a+c
int neutral_c = 0;  // neutral c  part for b*a+c

      //
     ////
    ////////


        void build(int v, int L, int R){
            if (L == R) return;
    
              int C = (L + R) / 2;
               build(v*2,     L,     C);
               build(v*2 + 1, C + 1, R);
                SegTree[v] = SegTree[v*2] + SegTree[v*2 + 1];
        }
    void buildTree(){
                 build(1, 0, (1 << h) - 1);
    }

           //
          ////
         /////
         int getSum(int v,  int lpos, int rpos,  int left, int right){
                           if (L > r || R < l)
                     if (left > right) return neutral_element;
                     if (left==lpos  and right == rpos) return SegTree[v];

                      int mid = (lpos + rpos)/2;
                       return __gcd(getGCD(2*v,     lpos,     mid,  left      , min(right, mid)),
                                    getGCD(2*v + 1, mid + 1, rpos,  max(left, mid + 1), right));
         }
    int querySum(int l, int r) {
                                return getSum(1, 0,1<<h -1,  l,r,);    
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
    void changeValues(int l, int r, b,c ){
                                   update(1, 0, 1<<h -1,  l,r , b,c);
    };   

int main(){
    cout << "Hello Range Affine Range Sum! v0.9"<<endl;

     h = (int)(ceil(log2(n)); // segTree height without leafs
      H = 1<< (h+1);                     //  segTree volume
       SegTree.resize(H, neutral_element);
       B.resize(H/2, 1);
       C.resize(H/2, 0);

        for(int i=0; i<n; i++)
            cin >> SegTree[H/2 + i]; //input in segTree leafs
         buildTree();       // build segTree upper nodes 

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