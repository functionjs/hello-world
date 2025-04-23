//USACO 2024 December Contest, Silver
//Problem 3. 2D Conveyor Belt
//https://usaco.org/index.php?page=viewproblem2&cpid=1448
// Demo of using Disjoint Set Union structure procedures (DSU)

#include <iostream> 

using namespace std;



const int MaxSize = 1000;
int  N, Q;
 char Field[MaxSize][MaxSize];  //  Field[i][j] -->  *(Field+(j+ Size*i))
 int Parent[MaxSize*MaxSize];
 


                           //     v =  (x-1) + Size*(y-1)
    inline int _ (int x, int y){return (x-1) + N*(y-1);}  
  // methods of Disjoint Union Sets                             
        void make_one_element_set (int v) {
   	                                        Parent[v] = v;
        }
                                   
       int findSuperParentOf(int v) {
                                       int p = Parent[v];
                                        if(p<0)return -1;

       	                                 if (v == p)return p; // in this situation v is self Super Parent
                                         
                                           Parent[v] = findSuperParentOf(p);
       	                                     return Parent[v];
       }
    
   void union_sets_of(int v1, int v2) {
   	                                int  p1 = findSuperParentOf(v1);
   	                                int  p2 = findSuperParentOf(v2);
   	                                 if (p1 != p2) Parent[p2] = p1;
   }
/********************************************/


/***********print  utilities ********************************/
    void printField(){
                       cout << "Field:"<<endl; 
                        for(int y=1; y<=N; ++y){
                           for(int x=1; x<=N; ++x){
                              char c = Field[y-1][x-1]; 
                               if(c>0)printf(" %c ", c);
                               else   printf(" ? ");
                           }  
                            printf("\n");
                        }
                 
     }
    void printSetsElements(){
                    cout << "Sets elements:"<<endl; 
                     for(int y=1; y<=N; ++y){
                       for(int x=1; x<=N; ++x){
                           int v= _(x,y);   
                           if(Parent[v]>=0) printf("%2d ", _(x,y));
                               else         printf(" - ");
                       }    
                        printf("\n");
                     } 
    }
    void printSetWithParent(int p){
                    printf("Set with parent %d :\n", p);
                     for(int y=1; y<=N; ++y){
                       for(int x=1; x<=N; ++x){
                           int v= _(x,y);
                            int P = Parent[v];   
                            if(P>=0 and P==p) printf("%2d ", v);
                                else          printf(" - ");
                       }    
                        printf("\n");
                     } 
    }
    void printSetWithSuperParent$(int p){
                    printf("Set with Super Parent %d :\n", p);
                     for(int y=1; y<=N; ++y){
                       for(int x=1; x<=N; ++x){
                           int v= _(x,y);   
                            int SP = findSuperParentOf(v); 
                             if(SP>=0 and SP==p) printf("%2d ", v);
                                else             printf(" - ");
                       }    
                        printf("\n");
                     } 
    
    }
    void printParents(){
                    cout << "Parents:"<<endl; 
                     for(int y=1; y<=N; ++y){
                       for(int x=1; x<=N; ++x){
                          int v= _(x,y);   
                           if(Parent[v]>=0)printf("%2d ",Parent[v] );
                               else        printf(" . ");
                       }    
                        printf("\n");
                     } 
    }
    void printSuperParents$(){
                      cout << "Super Parents :"<<endl; 
                       for(int y=1; y<=N; ++y){
                         for(int x=1; x<=N; ++x){
                            int v= _(x,y); 
                             int SP = findSuperParentOf(v); 
                               if(SP>=0) printf("%2d ", SP);
                                  else   printf(" , ");  
                         }    
                          printf("\n");
                       } 
      }  
/************************************************************/

int main(){
    cout << "Hello arrow-belts with DSU v1.2!!!"<<endl;
     cin >> N >> Q;
     int x,y;
     char c; 
      
      // initialization of "parents" of empty set elements
      for(int y=1; y<=N; ++y){
         for(int x=1; x<=N; ++x){
            Parent[_(x,y)] = -1; 
         }  
      }
       int NumOfEmptySets = N*N;
        printf("After empty set elements initialization "); 
         printParents();
          printf("Number Of Empty Sets is %d\n",NumOfEmptySets);
      int y_, x_;    
      for(int i=0; i<Q; ++i){
        cin >> y >> x >> c;
         y_ = y-1;
         x_ = x-1;
          Field[y_][x_] = c;  
           make_one_element_set(_(x,y)); 
      
      }  

       printField();  
       printSetsElements();
       printParents();

        union_sets_of(0,3); 
        union_sets_of(1,3); 
        union_sets_of(7,8); 
 
         printf("after 0in{0} U 3in{3} and after 1in{1} U 3in{0,3}  \n"); 
          printSetsElements();
          printParents();

           printSetWithParent(0);
           printSetWithParent(1);
           printSetWithParent(3);
            printSetWithSuperParent$(1);
             printSetWithParent(1);

             printSetWithParent(7);

              printSuperParents$();


    return 0;   
}    

/*
  Coding 
   0 - empty cell 
   1 - Up
   2 - Left
   3 - Down
   4 - Rigth

Input
3 5
1 1 R
3 3 L
3 2 D
1 2 L
2 1 U

Output
0
0
0
2
3


Example of disjoint Sets with Parents :
 {2,3,7} , {1,4,5}, {6}
  | | |     | | |    | 
  V V V     V V V    V
  2 2 2     5 5 5    6

  How it may be coded by array:
  index  :    1 2 3 4 5 6 7      The elements of Sets were coded by index of array 
  Parent : [  5 2 2 5 5 6 2 ]    Their Set "names" were coded by Parent value at the index. 


Example of initial disjoint Sets :
  {2},{3},{7} , {1},{4},{5}, {6}
   |   |   |     |   |   |    | 
   V   V   V     V   V   V    V
   2   3   7     1   4   5    6

  How it may be coded by array:
  index  :    1 2 3 4 5 6 7 
  Parent : [  1 2 3 4 5 6 7 ]



Behaviour of reccurent call of limited discrete function.
For example, for limited function f(x)   ( 0<= f(x) <10 )  
  f(x) = (x^2 + 3) mod 10  
 we have such reccurent sequence of  x1=f(x0), x2=f(x1), x3=f(x2), ... :
   0 --> 3 --> (2 --> 7 --> 2 --> 7 --> 2 --> ....)  
     f()   f()    f()   f()   f()    f()  f()  ... 

     
       
*/