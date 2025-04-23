//USACO 2024 December Contest, Silver
//Problem 3. 
// Solution by Reversing Operations

#include <iostream>   // std::cin, std::cout, std::endl,  printf();
#include <algorithm> // reverse(..)

using namespace std;


const int _MaxN_ = 1+1000+1;  // Max padded size of Field[][]
const int QMax = 2E5;         // Max quantity of Queries   
struct QueryStruct{
                   int a,b;
                   char c;  
} ;
int  N, _N_, Q;   // variables for current size of Field[][], current padded size of Field and current quantities of Queries 
 char Field[_MaxN_][_MaxN_];  
 QueryStruct Query[QMax];
 bool   Goodness[_MaxN_][_MaxN_];    // good cells  -- initially not 
 bool   Tested[_MaxN_][_MaxN_];  // tested cells -- initially not
 bool   Visiting[_MaxN_][_MaxN_];  // visiting cells  for loops detection in recursion search
int NumOfBadCells = 0; 
int NumOfGoodCells = 0; 
int NumOfAllCells = 0; 

   

/***********print  utilities ********************************/
    void printField(){
                       printf(" padded Field[][] :\n"); 
                        for(int a=0; a<=N+1; ++a){
                           for(int b=0; b<=N+1; ++b){
                              char c = Field[a][b]; 
                               if(c>0)printf(" %c ", c);
                               else   printf(" ? ");
                           }  
                            printf("\n");
                        }
                 
    }
    void printQueries(){
                        cout << "Queries:"<<endl; 
                         for(int q=0; q<Q; ++q){
                               printf(" %d %d %c\n", Query[q].a, Query[q].b, Query[q].c);
                            }  
                       }

    void printGoodness(){
                       printf("padded Good Cells:\n"); 
                        for(int a=0; a<=N+1;++a){
                           for(int b=0; b<=N+1; ++b){
                              bool good = Goodness[a][b]; 
                               if(good)printf(" + ");
                               else   printf(" - ");
                           }  
                            printf("\n");
                        }
                 
    }       
    void printTested(){
                       printf("padded Tested Cells:\n"); 
                        for(int a=0; a<=N+1; ++a){
                           for(int b=0; b<=N+1; ++b){
                              bool tested = Tested[a][b]; 
                               if(tested)printf(" t ");
                               else   printf(" _ ");
                           }  
                            printf("\n");
                        }
                 
    }       
    void printVisited(){
                       printf(" padded Visited Cells:\n"); 
                        for(int a=0; a<=N+1; ++a){
                           for(int b=0; b<=N+1; ++b){
                              bool visited = Visiting[a][b]; 
                               if(visited)printf(" v ");
                               else   printf(" . ");
                           }  
                            printf("\n");
                        }
                 
    }       
    
/************************************************************/

    bool recursiveTestCell(int a, int b) {
                                          if(Tested[a][b])return Goodness[a][b];
                                          //else  test on visiting loop                                          
                                            if(Visiting[a][b])return false; // loop is not Good for our Task!
                                            //else      
                                             Visiting[a][b] = true; // That's right - we stood on this cell
                                             char c = Field[a][b]; 
                                              if(c=='U'){
                                                if(Field[a-1][b]=='D'){Goodness[a][b]=false;                    Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}
                                                /*else*/              {Goodness[a][b]=recursiveTestCell(a-1, b);Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}    
                                              }
                                              if(c=='D'){
                                                if(Field[a+1][b]=='U'){Goodness[a][b]=false;                    Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}
                                                /*else*/              {Goodness[a][b]=recursiveTestCell(a+1, b);Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}                                                        
                                              }
                                              if(c=='L'){
                                                if(Field[a][b-1]=='R'){Goodness[a][b]=false;                    Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}
                                                /*else*/              {Goodness[a][b]=recursiveTestCell(a, b-1);Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}
                                              }
                                              if(c=='R'){
                                                if(Field[a][b+1]=='L'){Goodness[a][b]=false;                    Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}
                                                /*else*/              {Goodness[a][b]=recursiveTestCell(a, b+1);Tested[a][b]=true;Visiting[a][b] = false;return Goodness[a][b];}                                                        
                                              }
                                             //else
                                              //if(c=='?') Checking on all four sides!!!!
                                               Goodness[a][b] =   recursiveTestCell(a-1, b)  //    search Up                    
                                                               or recursiveTestCell(a+1, b)  // or search Down                   
                                                               or recursiveTestCell(a, b-1)  // or search Left                   
                                                               or recursiveTestCell(a, b+1); // or search Right                    
                                                Tested[a][b]=true;
                                                Visiting[a][b] = false; // we returning and wipe our visiting mark
                                                 return  Goodness[a][b];                         



    } 


int main(){
    cout << "Hello arrow-belts with Reverse Ops v1.3!!!"<<endl;
     cin >> N >> Q;  // get size of Field and quantity of Queries
      _N_ = 1+N+1;   // evaluate size of padded Field;
      NumOfAllCells = N*N;
         // initial set true Goodness[][] and Tested[][] on paddings 
         for(int a=0; a<=_N_; ++a)Tested[a][0]    =Goodness[a][0]    =true;
         for(int a=0; a<=_N_; ++a)Tested[a][_N_-1]=Goodness[a][_N_-1]=true;
         for(int b=0; b<=_N_; ++b)Tested[0][b]    =Goodness[0][b]    =true;
         for(int b=0; b<=_N_; ++b)Tested[_N_-1][b]=Goodness[_N_-1][b]=true;

           printf("\n Initially:\n");
            printTested();
             printGoodness();
             printf(" NumOfAllCells=%d and so far NumOfGoodCells=%d \n", NumOfAllCells, NumOfGoodCells); 

     int a,b;
     char c; 
      for(int q=0; q<Q; ++q){
        cin >> a >> b >> c;
          Field[a][b] = c;  
          Query[q]= {a,b,c};
      }  
       printField();  


       printQueries();
        reverse(Query, Query+Q); 
         printf("Reverse ");
          printQueries();


          for(int a=1; a<=N; ++a){
            for(int b=1; b<=N; ++b){
                NumOfGoodCells += recursiveTestCell(a, b);
            }    
          }      
            
            printf("\nAfter executing all %d queries:\n",Q);
              printTested();
              printGoodness();
  
           NumOfBadCells = NumOfAllCells - NumOfGoodCells;
         printf(" NumOfAllCells=%d and finally NumOfGoodCells=%d NumOfBadCells=%d \n", NumOfAllCells, NumOfGoodCells, NumOfBadCells); 
        
          printf("\n Backward deleting queries:\n");
           for(int a=1; a<=N; ++a){
              for(int b=1; b<=N; ++b){
                Tested[a][b]=false; // not true!;
              }
           }     
           for(int q=Q-1; q>0; --q){
                QueryStruct query = Query[q];
                  int a  = query.a; 
                  int b  = query.b; 
                  char c = query.c; 
                   Field[a][b]='\0';
                   Goodness[a][b]=false; // not true!; 
                    printf("  for deleted %d query %d %d %c \n", q+1, a,b,c);
                    // to do -- procedure for testing bad cells - neighbors , beginning from current cell [a][b]
                     printf("   to do -- procedure for testing bad cells - neighbors , beginning from current cell [%d][%d]...\n",a,b);
                     printField();  
           }
              

    return 0;   
}    
/*

SAMPLE INPUT:
3 5
1 1 R
3 3 L
3 2 D
1 2 L
2 1 U
SAMPLE OUTPUT:
0
0
0
2
3
The conveyor belt after the fifth day is shown below.
RL?
U??
?DL



SAMPLE INPUT:
3 8
1 1 R
1 2 L
1 3 D
2 3 U
3 3 L
3 2 R
3 1 U
2 1 D
SAMPLE OUTPUT:
0
2
2
4
4
6
6
9
The conveyor belt after the eighth day is shown below.
RLD
D?U
URL
*/