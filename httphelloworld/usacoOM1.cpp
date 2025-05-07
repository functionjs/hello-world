//USACO Ooh Milk! ( may 7 2025) by three steps!
// N D
// A B
// m1 ... mN
/*
5 4
4 2
4 10 8 10 10
---
546
---
10 5
5 1
1 2 3 4 5 6 7 8 9 10
---
777
---
5 1000000000
3 1
0 1 2 3 4
---
10
*/
#include <bits/stdc++.h>
using namespace std;


using Map = map <long, int>; 
using MapIt = Map ::iterator;
//const int MaxN=1e5;
// const int MaxA=MaxN;
//  const int MaxB=MaxA-1;
const int MaxMilk=1e9;
//const int MaxD=1e9;
const int MOD = 1e9+7; 

int N;   //    N is number of bottles 
int D;   //    D is number of Days 
int A, B;   // A is Jhon active bottles, B is Nohj one

vector <long> Milk; //[MaxN];  // Milks in N bottles
Map RLE;  // Run Length Encoding  to get rid of total sorting
MapIt it, it_next, it_cut; // smart pointers to element of RLE

int a=A-B; //a - active bottles with smallest number of milk drips 
int base=0;  // base height for left part of stairs
int base_width=0; // base width

long result = 0;  // result

     void printRLE(){
        cout << "RLE{milk,pos}["<<RLE.size()<<"]: \n";
          for(auto& e : RLE){
              cout << e.first << " -> " <<e.second  ;
               if(e.second>0 and a>=e.second) cout << " *" ;
                cout << endl;
          } 
     }

     void changeKeyRLE(long cur_level, long new_level  ){
                                                         auto element = RLE.extract(cur_level);
                                                          element.key() = new_level;
                                                           RLE.insert(move(element));
     }                                                   

     MapIt floodBasin(MapIt it, long flood_volume){// it - first step of Basin, flood_volume of milk 
         cout << "floodBasin:  flood_volume = " << flood_volume << endl;    
           if(flood_volume==0) return it; 

            long pos_of_bottles = 0;
            long pos_of_bottles_of_prev_step = 0 ; //by default; 
            long stepW = 0; 
            long stepH = MaxMilk;//by default;
            long cur_level = 0;
            long next_level = MaxMilk; //by default;
            long v = 0;  // volume of current step    
             do{
                pos_of_bottles_of_prev_step=0 ;//by default; 
                pos_of_bottles = it->second ; 
                 if(pos_of_bottles>0) 
                   pos_of_bottles_of_prev_step = prev(it)->second ; 
                  
                  stepW =  pos_of_bottles - pos_of_bottles_of_prev_step;    
    
                stepH = MaxMilk; //by default
                cur_level = it->first;
                next_level = MaxMilk; //by default;
                it_next = next(it); //next step pointer 
                 if(it_next != end(RLE)){ //if next exists
                     next_level = it_next->first;
                      stepH = next_level - cur_level; //hight of current step; 
                 }    
                  v= stepW*stepH;     // volume of current step    
                   cout << "floodBasin: stepW = " << stepW << " stepH = " << stepH << " v = " << v << endl;   
    
                   if(flood_volume<v){
//                     cout << "   floodBasin: if(flood_volume<v)"<< endl;
                       long delta_level      = flood_volume/stepW;
//                       cout << "   floodBasin: delta_level ="<<delta_level <<endl;
                       long partial_on_level = flood_volume%stepW;  
//                       cout << "   floodBasin: partial_on_level="<<partial_on_level <<endl;
                        long new_level = cur_level + delta_level;
//                        cout << "   floodBasin: new_level="<<new_level <<endl;
                         if(delta_level>0){
                                           changeKeyRLE(cur_level, new_level  );  
                                          // auto element = RLE.extract(cur_level);
                                          //       element.key() = new_level;
                                          //        RLE.insert(move(element));
                                                   it = RLE.find(new_level);
//                            cout << "   floodBasin: delta_level>0 it: "<<it->first <<"->"<< it->second<<endl;                                                   
                         }
                          if(partial_on_level>0) {
                              RLE[new_level] -=  partial_on_level;                    
                               RLE[new_level+1] = RLE[new_level] + partial_on_level;                 
//                              cout << "   floodBasin: partial_on_level>0 RLE[new_level]="<<RLE[new_level] <<" RLE[new_level+1] ="<< RLE[new_level+1]<<endl;                                                   
                          }
                           return it;
                   }
                   // else common case (flood_volume >= v)
                    flood_volume -= v;   // correct remaining flood_volume by volume v  
                    cout<< " ... floodBasin: flood_volume="<<flood_volume<<endl;
                    it = it_next;       //  now we go to next step
                     RLE.erase(cur_level); //fully flooded current step with volume v does not exists
                } while(flood_volume>0);  
             
                  return it;  
     }

int main(){
    cout << "Ooh Milk by 3 steps!"<<endl;
    cin >> N >> D;
    cin >> A >> B;
    cout << "N="<<N<<" D="<<D<<" A="<<A<< " B="<<B<<endl;
     Milk.resize(N);
//    cout << "resized M[]:"; for(int i = 0; i < N; i++)cout << Milk[i] <<" "; cout << endl; 
     a=A-B;
//    cout << " active bottles = " << a <<endl;  
     for(int i = 0; i < N; i++){
        cin >> Milk[i];
     }   
//    cout << " Milk[]:";for(int i = 0; i < N; i++)cout << Milk[i] <<" ";  cout << endl; 
     
      sort(Milk.begin(), Milk.end());  // sort in ascending of M[] from 0-th element to N-1 element
//     cout << "after sorting Milk[]:";for(int i = 0; i < N; i++)cout << Milk[i] <<" ";  cout << endl; 
      
      int nonTouchedBottles=N-A; // bottles from [0] to [N-A-1] are nontouchable by the optimal game flow 
//     cout << " nonTouchedBottles="<< nonTouchedBottles <<endl;      
       for(int i=0; i<nonTouchedBottles; i++)result += Milk[i]*Milk[i];
 
    //Make RLE from M[] from  nonTouchedBottles to N-1
    int  sumb = 0; //sum of bottles
        RLE[0L]=0;
         it = RLE.begin();
          for(int i = nonTouchedBottles; i < N; ) {
                long m=Milk[i]; //m is current key (milks quantity in bottle)
                int c=1;    //c is value (count of bottles with that (m) quantity of milk) 
                 i+=1;
                  while((i<N) && (Milk[i]==m)){//while Milk[i]==m we count bottles
                         c++; 
                         i+=1;
                  }
                   sumb += c; 
                    RLE[m]=sumb; 
                     if(sumb<=a){
                        base_width=sumb;
                        ++it;
                     }
           }
            printRLE();
            cout << "base = "<< base << " base_width="<<base_width<<endl;                 
            cout << " active noncutted RLE element: "<<it->first << "->" <<it->second << endl;
            
            //1) first: flooding right basin by flood_volume=yellowWitdh*Days
             long yellowWidth = a - it->second;
              long flood_volume = yellowWidth*D;
               cout << "yellowWidth="<<yellowWidth<<" volume1="<<flood_volume<<endl;
               it_cut = floodBasin(next(it), flood_volume);
                printRLE();
                long h_cut = it_cut->first; 
                 cout << " it_cut: " << h_cut << "->"<< it_cut->second << endl; 
            //2) lifing left part and  cutting horizontally and then calulating pooped volume 
             cout << " active noncutted RLE element afte flooding: "<<it->first << "->" <<it->second << endl;     
            long v_milk_tsunami = 0;
             for(auto i=it; i != RLE.begin(); ){
                   long h= i->first;
                    long h_new = h + D;  
                     long diff =  h_new - h_cut; 
                    cout << "h="<<  h <<" diff="<< diff <<" "<<i->first  <<  "->" << i->second << endl;
                       if(diff<0)break;
                        v_milk_tsunami += diff;
                         --i;
                          RLE.erase(h);
             }
            cout << "v_milk_tsunami = "<< v_milk_tsunami<< endl;
            printRLE();
            //3) second (tsunami) flooding of modified right basin 
              floodBasin(it_cut, v_milk_tsunami);
              cout<<" after tsunami:" << endl;
               printRLE(); 
        /*    
           // Simulating   of game by increasing days by h (to increase efficiency)
           cout << "Simulating of "<<D<<" days game by increasing days by ? (to increase efficiency):"<<endl;
           for(long d=0; d<D; ){
              it_next = next(it, 1); 
               long h = MaxMilk;  // by default step is last and has "Max" height
                if(it_next != end(RLE))
                   h = it_next->first - it->first; //green hight
                 cout << "day "<< d << " it: <"<< it->first <<", "<< it->second<< "> it_next: <"<< it_next->first <<", "<< it_next->second <<">"<<" h="<<h<<endl; 
          
               base +=h;
              int w = a - it->second;   //yellow width
               long mm = h*w;           // milk quantity to flood rigth ladder basin
              long h_next = LLONG_MAX;  // by default next step is last and has "infinity" height
              long next_step_volume = LLONG_MAX; // by default next_step_volume is "infinity"
              MapIt it_next_next = next(it_next, 1); // test if there exists next_next step
               if(it_next_next!=end(RLE)){
                   h_next = it_next_next->first - it_next->first;
                    next_step_volume = it_next->second  * h_next;
               } else{// last step
                       w_next= it_next->second - it_->second; 
                        long dh = mm/w_next;
                        long dw = mm%w_next;
                         it_next->first += dh;
                          if(dw>0){
                              long new_step_m = it_next->first + 1;      
                              int new_step_p = it_next->second;
                               RLE[new_step_m]= new_step_p;
                               it_next->second -= dw; 
                           }

                     }                

                cout << "h="<<h << " base="<<base<< " w="<<w <<" mm="<<mm<< " h_next="<<h_next <<endl; 
               if(mm >= next_step_volume ) {
                   //it_next->erase();

               }
             // int milk_to_basin = 
          
               it=it_next; 
               d +=h ; //? 
            }                   
        */
          
          for(it= RLE.begin(), it_next=next(it); it_next!=RLE.end(); it=it_next, it_next=next(it)){
             long q = it_next->second - it->second;
             long m = it_next->first;
              result +=  m*m * q;
          }   
              cout << result%MOD<< endl;

            return 0;
}

/*
Intial state
8->1
10->3
We must add to a=A-B=4-2=2 bottles by one drip in.
8->0
9->1
10->2
11->1
*/

/*
 4 |8 10 10 10
 4 |9 10 10 11 
 4 |10 10 11 11 
 4 |11 11 11 11 


  0 1 2 3 4 5 6 7 8 9
1)   copy from [2] 3 elements to [5]-th index 
  0 1 2 3 4 2 3 4 8 9 
2)   copy from [2] 3 elements to [3]-th index  0 1 2 2 3 4 6 7 8 9 - we want this!
  0 1 2 2 4 5 6 7 8 9
  0 1 2 2 2 5 6 7 8 9
  0 1 2 2 2 2 6 7 8 9 but we get this!


3)   copy from [2] 3 elements to [3]-th index  0 1 2 2 3 4 6 7 8 9 - we want this!
    0 1 2 3 4 4 6 7 8 9
    0 1 2 3 3 4 6 7 8 9
    0 1 2 2 3 4 6 7 8 9   what we want we get now!







0 step 
0             [0] 
1********     [8]
2**********   [10]
3**********   [10]
4**********   [10]

1 step 
0                   [0] 
1******************        [18]
2*************     [13]
3*************     [13]
4**************    [14]

2 step 
0                   [0] 
1*************|*****        [18]
2*************|     [13]
3*************|     [13]
4**************     [14]

3 step 
0                   [0] 
1**************     [14]
2**************     [14]
3***************     [15]
4***************     [15]


*/ 
