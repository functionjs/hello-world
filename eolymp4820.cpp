/*
Выход из лабиринта
https://basecamp.eolymp.com/ru/problems/4820
*/
#include <iostream>
#include <queue>

using namespace std;


using Coordinates = pair<int,int>;
using  QCoordinates = queue <Coordinates>;
struct Coord {int x,y;};
using   QCoord = queue <Coord>;

int labirint[1001][1001];
bool visited[1001][1001];



int main()
{
    int N, M, x1, y1, x2, y2;
    cin>>N>>M;
    for(int i=1; i<=N; ++i){
        for(int j=1; j<=M; ++j){
            cin>>labirint[i][j];
        }
    }
    cin>>x1>>y1;
    cin>>x2>>y2;
    
    cout<<"N="<<N<<" M="<<M<<endl;
    cout << "labirint[][]:"<<endl;
    for(int i=1; i<=N; ++i){
        for(int j=1; j<=M; ++j){
            cout<<labirint[i][j];
            cout<<" ";
        }
        cout<<"\n";
    }
     
   
     cout<<"x1 = "<< x1 << " y1 = " << y1 << endl;
     cout<<"x2 = "<< x2 << " y2 = " << y2 << endl;
   
      
      QCoord Q;
              Q.push({x1,y1}); 
              visited[x1][y1]=true;
               while(!Q.empty()){
                Coord point = Q.front();
                  //......
                  //....

               }

               
              



      return 0;
}   
/*
Ввод #1
4 6
1 0 1 1 1 0
0 0 1 0 0 0
1 0 1 1 0 0
0 0 0 0 0 0
2 1
5 3
Ответ #1
7



 1  @  1  1  1  0
(2)(1) 1  0  0  0
 1 (2) 1  1 (7) 0
(4)(3)(4)(5)(6)(7)
*/