/*
https://usaco.org/index.php?page=viewproblem2&cpid=1352
Target Practice OPtimized
*/


#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

using Vi = vector<int>;
using Mii = map<int, int>;
 using ItMii = Mii::iterator;

using Si = set<int>;
 using VSi = vector<Si>;
 using ItSi = Si :: iterator;


Vi Line; 
string Commands;
// T is number of targets, Nc is number of Commands, C is the center of Line 
int T, Q, C;


    void printLine(){
                    cout <<"Targets on Line:"<<endl;  
                     for(int pos=C-Q; pos<Line.size()-2; ++pos){
                        if(pos==C)cout<<" 0";
                          else  cout <<" .";
                     } 
                      cout <<endl;
                       for(int pos=C-Q; pos<Line.size()-2; ++pos){
                           if(Line[pos]==1)cout<<" *";
                              else        cout <<"  ";
                       }   
                        cout <<endl;
    }
    void printCommands(){
                         cout <<"Commands:" << Commands<<endl;
    }

int  main(){
  // cout << "Hello optimized targets version 2.0!"<< endl;
   
    cin >> T>>Q; 
     Line.resize(2+Q+1+Q+2);  
     C = 2 + Q;
   
     int pos;     // pos is current position on Line i.e. position in "Line space". It is must based relative to Center C    
     int x;       // x is current position on coordinates line i.e. position in "x space". It is  based relative to 0     
      for(int t=0; t<T; ++t){
           cin>>x;
            pos = C+x;
             Line[pos]=1;
      }
      cin >> Commands;
    //  printLine();
      Mii pos_i, i_pos;    // maps for remembering hits events on forward pass
       //initial forward pass       
       pos = C;     // pos is current initial position on Line i.e. it is on Center
//    cout << " initial pos="<<C <<endl;
        for (int i = 0; i < Q; i++){  // i is index of current command i.e. normal "time" of its execution 
             char k = Commands[i]; // k is current command (command at "time" i)
              if (k == 'F'){
                 if (Line[pos]==1 and pos_i.find(pos)==pos_i.end()){
                     //remember successful shots
                     pos_i[pos]= i  ;  // pos --> i    
                     i_pos[i]  = pos;  // i   --> pos
                 }
              }
               if(k == 'L')pos--;
               if(k == 'R')pos++;
           }
            int bestHits = pos_i.size(); // so far bestHits is number of hits on initial forward pass       
  //           cout << "pos_i:"<<endl;
  //            for (ItMii it=pos_i.begin(); it!=pos_i.end(); ++it) cout << " " << it->first<<" -->"<< it->second <<endl;
             
   VSi rightSide,toBeAdded;
        rightSide.resize(5);
        toBeAdded.resize(5);
         for (int i = 0; i < 5; i++) {
             rightSide[i] = Si();
             toBeAdded[i] = Si();
         }    
         // backward in "time" steps with optimizations
    
          for (int i = Q-1; i >= 0; i--){ // i is Commands "time"
                  ItMii Index_hitted = i_pos.find(i);   // find if on i step target was hitted
      //             cout << "i="<<i << " k=" << Commands[i]<< " pos="<<pos<<endl;
                   if (Index_hitted != i_pos.end()){
        //                 cout << " hit in time i="<<i <<endl;
                         int Pos_hitted = i_pos[i];
                          pos_i.erase(Pos_hitted);
                         i_pos.erase(Index_hitted);
                           for (int j = 0; j < 5; j++){
                              if (toBeAdded[j].find(pos)!=toBeAdded[j].end()){
                                  rightSide[j].insert(pos);
                                  toBeAdded[j].erase(pos);
                               }     
                            }
                   }
                    int variant_value=0; 
                    int addL=0, addR=0; 
                    char k = Commands[i];
                     if(k == 'L')pos++;
                     if(k == 'R')pos--;
                      switch (k){
                              case 'L':
                                       // try F with shift +1
                                       addL = 0;
                                        if(Line[pos] and pos_i.find(pos)==pos_i.end() and rightSide[3].find(pos)==rightSide[3].end())addL=1;
                                         variant_value = i_pos.size()+addL+rightSide[3].size(); 
                                          if(bestHits<variant_value)bestHits=variant_value;
                                       // try changing to R with shift +2
                                         variant_value = i_pos.size()+0+rightSide[4].size(); 
                                          if(bestHits<variant_value)bestHits=variant_value;
                                           break;
                              case 'R':
                                        // try F with shift -1
                                        addR = 0;
                                         if(Line[pos] and pos_i.find(pos)==pos_i.end() and rightSide[1].find(pos)==rightSide[1].end())addR=1;
                                       /*  
                                         cout << "case R: Line["<<pos<<"]="<<Line[pos]
                                              << " pos_i.find(pos)==pos_i.end() is" << (pos_i.find(pos)==pos_i.end())
                                              << " rightSide[1].find(pos)==rightSide[1].end() is" << (rightSide[1].find(pos)==rightSide[1].end())
                                              << " addR ="<<addR<<endl;       
                                       */                                               
                                          variant_value = i_pos.size()+addR+rightSide[1].size();       
                                           if(bestHits<variant_value)bestHits=variant_value;
                                        // try changing to L with shift -2
                                          variant_value = i_pos.size()+0+rightSide[0].size();                                         
                                           if(bestHits<variant_value)bestHits=variant_value;
                                            break;
                              case 'F':
                                        // Try changing to L with shift -1
                                         variant_value = i_pos.size()+0+rightSide[1].size();                                         
                                           if(bestHits<variant_value)bestHits=variant_value;
                                        // Try changing to R with shift +1
                                         variant_value = i_pos.size()+0+rightSide[3].size();
                                            if(bestHits<variant_value)bestHits=variant_value;                                         
                                           break;
                     }
                      if (k == 'F') {
                         for (int p = pos - 2; p <= pos + 2; p++) {
                              if (p < 0 || p >= Line.size()) continue;

                               if (Line[p]==1){
                                 int shift = p-pos+2; // shift in {0,1,2,3,4}
                                  if (pos_i.find(p)!=pos_i.end()) {
                                         toBeAdded[shift].insert(p);
                                  }else{
                                         rightSide[shift].insert(p);
                                        }
                               }
                     }
            }
 
        }
        /*
                 for (int i = 0; i < 5; i++) { 
            std::cout << "rightSide["<< i <<"] set contains:";
             for (ItSi it=rightSide[i].begin(); it!=rightSide[i].end(); ++it) cout << ' ' << *it;
              std::cout << '\n';
         }
       */        

                    cout << bestHits<< endl;
               
           return 0;
}
/*
T C 
3 7
0 -1 1
LFFRFRR
*/

/*

LFFRFRR

  . . . . . . . 0 . . . . . . .  shifted by -2 when changed L by R
              * * *            
    . . . . . . . 0 . . . . . . . shifted by -1 when changed F by R or   L by F
                * * *            
      . . . . . . . 0 . . . . . . . shifted by 0 (non shifted) 
                  * * *            
        . . . . . . . 0 . . . . . . . shifted by 1 when changed F by L  or  R by F
                    * * *            
          . . . . . . . 0 . . . . . . . shifted by 2 when changed R by L
                      * * *            
 initializing
   forward
     pass
      |   []   |  L .
      |   []   |  F
      |   []  /|\  F 
      |    ? //|\\  R
      |   {} |||||    F
      |   {} |||||     R 
      |   {} \|||/     R 
      V_______\|/
           optimizing
            backward
             5-way 
              pass  
*/

