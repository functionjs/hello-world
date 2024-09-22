#include <iostream>
#include <queue>   // Мы используем priority_queue
#include <stack>  // Добавляем заголовочный файл для стека
#include <vector>
#include <cmath>
#include <limits.h>

using namespace std;
using  Coord = pair<int,int>; //coordinates
using   GreedCoord = pair<int,Coord>; // greedness with coordinates
using  GreedyFunction = int (int, int); // interface for my greedy functions
using  Vi = vector<int>;
using   VVi = vector<Vi>;

const auto n = 8;
const auto max_dist = n - 1;
int L[n][n];
VVi maze;
bool visited[n][n];    
auto D = 1;
auto exitFound = false;
int x_0, y_0;
int x_1, y_1;
int Dir[4][2] = {
    {+1, 0},
    {-1, 0},
    {0, +1},
    {0, -1}
};


        int abs(int x) {
            if (x < 0) return -x;
                       return x;
        }

            void resizeAndInitializeMaze(int m, int n) {
                                                        maze.resize(m, Vi(n, -1));
            }

            void cravePath(int x, int y){
                                          maze[x][y] = 0;
                                           // to do: 
                                           //auto neighbors 
                                           // ........
            }

        void generateMaze(){
                             resizeAndInitializeMaze(n,n);
                             srand(time(0));
                              int startX = rand() % n;
                              int startY = rand() % n;
                               if(startX % 2==0) startX++;
                               if(startY % 2==0) startY++;
                                cravePath(startX, startY);
        }
        void printMaze(int a, int b, int d=0) {
              cout << "\n";
               for (int i = 0; i < n; i++) {
                  for (int _ = 0; _ < d; ++_) printf("  ");
                   for (int j = 0; j < n; j++) {
                       int q = maze[i][j];
                        if (a == i && b == j) printf("  *");
                        else if (q == 0) printf("  .");
                             else if (q < 0) printf("  #");
                                  else       printf("%+3d", q);
                   }
                    cout << endl;
               }
         }

    void readL() {
                  for (int i = 0; i < n; i++)
                      for (int j = 0; j < n; j++) {
                          cin >> L[i][j];
                      }
    }
    void printL(int a, int b, int d) {
         cout << "\n";
          for (int i = 0; i < n; i++) {
             for (int _ = 0; _ < d; ++_) printf("  ");
              for (int j = 0; j < n; j++) {
                  int q = L[i][j];
                   if (a == i && b == j) printf("  *");
                   else if (q == 0) printf("  .");
                        else if (q < 0) printf("  #");
                             else       printf("%+3d", q);
              }
               cout << endl;
          }
    }

    void printVisited(int a, int b, int d) {
         cout << "\n";
          for (int i = 0; i < n; i++) {
             for (int _ = 0; _ < d; ++_) printf("  ");
              for (int j = 0; j < n; j++) {
                  int q = L[i][j];
                   if (a == i && b == j or visited[i][j]) printf("  *");
                   else if (q == 0) printf("  .");
                        else if (q < 0) printf("  #");
                             else       printf("%+3d", q);
              }
               cout << endl;
          }
    }

        bool isExit(int i, int j) { return (L[i][j] == 100); }
    

    void findExit() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (isExit(i, j)) { y_1 = i; x_1 = j; exitFound = true; L[i][j] = 0; return; }
    }
           
             int manhattanGreedness(int i, int j){// manhattan distance to (y_0, x_0)
                  return max_dist - (abs(i - y_0) + abs(j - x_0));
             };                                  
             int EuclidGreedness(int i, int j) {//euclid distance to (y_0, x_0)
                 int di = i - y_0;
                 int dj = j - x_0;
                  return max_dist - sqrt(di * di + dj * dj);
             }
             int maxGreedness(int i, int j) {//max distance to (y_0, x_0)
                  return max_dist - max(abs(i - y_0), abs(j - x_0));
             }
         ////--------------------------------------------------- 
                                              /*example of callback*/  
         int GreednessWithCallback(int i, int j, GreedyFunction g) {
                                                                     return g(i,j);
         } 
                      /* G - ссылка на какую-то конкретную функцию жадности*/      
         GreedyFunction &G = manhattanGreedness; // G is functional reference to concrete Greedness function, for example, to manhattanGreedness()
    void greedyWaveFloodLabirint() {
        priority_queue <GreedCoord> q; // priority queue for (max)greedy choosing coordinates
        int greedness= G(y_1, x_1);   // Начальное значение жадности при использовании вышевыбранной функции жадности 
         L[y_1][x_1] = greedness;
         q.push({greedness,{y_1, x_1}});   // Начальное состояние очереди с приоритетом (жадность, координаты)
           //Главный цикл заполнения лабиринта цифрочками
           while (!q.empty()) {
                 GreedCoord top = q.top(); // Здесь мы должны получать из очереди с приоритетом очередную самую перспективную клеточку для ее раскрытия
                  q.pop();
                  int i = top.second.first;
                  int j = top.second.second;
     
                     // Check all 4 directions
                     for (int k = 0; k < 4; ++k) {
                       int ni = i + Dir[k][0];  // neighbour coordinate i
                       int nj = j + Dir[k][1];  // neighbour coordinate j
                          if (0 <= ni && ni < n && 0 <= nj && nj < n && L[ni][nj] == 0) {
                             greedness = G(ni, nj);
                              L[ni][nj] = greedness;
                              q.push({greedness,{ni, nj}});// ?
                          }
                     }
           }
    }    
    
    void gradientSearchPath() {
        cout << "\nGradient Search path:" << endl;    
        

         for (int x = 0; x < n; ++x) 
         for (int y = 0; y < n; ++y) 
            visited[x][y] = false;

        int i = y_0, j = x_0;    
        stack<pair<int, int>> path;
         path.push(make_pair(i, j));
          while (!path.empty()) {
                 pair<int, int> current = path.top();
                  int ci = current.first, cj = current.second;
                   cout << "(" << ci << "," << cj << ")-->";
                   visited[ci][cj] = true;

                   if (ci == y_1 && cj == x_1) {
                      cout << "(" << y_1 << "," << x_1 << ")\n";
                       return;
                   }

                    int next_i = ci, next_j = cj;
                    int best_i = ci, best_j = cj;
                    int best_cost = INT_MAX;  // Начальное значение для наихудшего случая
                    bool found_next = false;
                     for (int k = 0; k < 4; ++k) {
                         next_i = ci + Dir[k][0];
                         next_j = cj + Dir[k][1];
                          if (0 <= next_i && next_i < n && 0 <= next_j && next_j < n && !visited[next_i][next_j]) {
                             int cost = L[next_i][next_j];
                              if (cost > 0 && cost < best_cost) {
                                  best_cost = cost;
                                  best_i = next_i;
                                  best_j = next_j;
                                  found_next = true;
                              }
                          }
                      }
                       if (found_next) {
                           path.push(make_pair(best_i, best_j));
                       } else {
                               cout << " Stuck! Backtracking.\n";
                               path.pop();
                              }
    }

    cout << "No available moves.\n";
}

int main() {
   /*
    ((2+11)*(x-100)^3 +7)/(30-10)
    1. Lucashevich
       2 11 + x 100 - 3 ^ * 7 + 30 10 - /
    2. SSA
       a = 2+11;    
       b = x-100;
       f = 30-10;     
        c =  b^3;
         d = a*c;  
          e = d+7;
           g = e/f;
         
   
   */ 
   cout << "\n Generate Maze 8x8!\n";
    generateMaze();
     printMaze(4, 4);       
    cout << "\n Hello BFS +Greedy Search Labirint!\n";
     readL();
     y_0 = 6; x_0 = 1;
      cout << "Точка старта в лабиринте: (" << y_0 << "," << x_0 << ")" << endl;
       printL(y_0, x_0, 1);
        findExit();
         if (!exitFound) {
             cout << "Из этого лабиринта выхода нет - дайте другой лабиринт!" << endl;
              return 13;
         } else {
             cout << "Выход из этого лабиринта - в точке (" << y_1 << "," << x_1 << ")" << endl;
           }

            cout << "\n greedy Wave Flood step ------------------------" << endl;
             greedyWaveFloodLabirint();
              printL(y_0, x_0, 1);
               cout << "\n gradient Search Path step ------------------------" << endl;
                gradientSearchPath();
                printVisited(y_0, x_0, 1);
    
                   return 0;
}
