/*
https://usaco.org/index.php?page=viewproblem2&cpid=1352
Target Practice
*/

#include <iostream>
#include <vector>

using namespace std;

using Vi = vector<int>;
// T is number of targets, C is number of commands 
int T, C;
Vi TargetPosition;
Vi Line; 
string Commands;
string MyCommands;
string LRF ="LRF";

    void printLine(){
                    cout <<"Targets on Line:"<<endl;  
                     for(int i=0; i<2*C+1; ++i){
                        if(i==C)cout<<" 0";
                          else  cout <<" .";
                     } 
                      cout <<endl;
                       for(int i=0; i<2*C+1; ++i){
                           if(Line[i]==1)cout<<" *";
                              else       cout <<"  ";
                       }   
                        cout <<endl;
    }
    void printCommands(){
                         cout <<"Commands:" << Commands<<endl;
    }
    void printMyCommands(){
                         cout <<"MyCommands:"<< MyCommands<<endl;
    }    
    void initLine(){ 
                    for(int t=0; t<T; ++t) Line[C+TargetPosition[t]]=1; 
                   }
    int interpretMyCommands(){
                              initLine(); 
                               int p=0;
                               int hits=0;
                                for(int c=0;c<C;++c){
                                    if(MyCommands[c]=='L'){
                                        p--;
                                         continue;
                                    }
                                    if(MyCommands[c]=='R'){
                                        p++;
                                         continue;
                                    } 
                                    if(MyCommands[c]=='F'){
                                        hits+= Line[C+p];
                                         Line[C+p]=0;
                                      }          
                                }
                                 return hits;
    }               

int  main(){
   //cout << "Hello targets version 1.3!"<< endl;
    cin >> T>>C; 
      TargetPosition.resize(T); 
       for(int t=0; t<T; ++t)cin>>TargetPosition[t];
        cin >> Commands;

      Line.resize(C+1+C);  

    int bestHits=0;
           for (int i = 0; i<C; i++){
                MyCommands=Commands;
                 for (int j = 0; j<3; j++){
                      MyCommands[i]=LRF[j]; 
                       int hits=interpretMyCommands();
                        if(bestHits<hits)bestHits=hits;
                 }
           }
            cout << bestHits<< endl;
        
    return 0;
}
/*
T C 
3 7
0 -1 1
LFFRFRR
*/