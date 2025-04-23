#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

using Coord = pair<int, int>;
using Vi = vector<int>;
using VVi = vector<Vi>;

const int n = 8;
VVi maze;
int Dir[4][2] = { {+1, 0}, {-1, 0}, {0, +1}, {0, -1} };

    void resizeAndInitializeMaze(int m, int n) {
        maze.resize(m, Vi(n, -1));
    }

    void createChamber(int x, int y, int width, int height) {

        for (int i = x; i < x + width && i < n - 1; i++) {
            for (int j = y; j < y + height && j < n - 1; j++) {
                maze[i][j] = 0;
            }
        }


        /* bad code
        for (int i =  x + width-1; i>=x && i < n - 1; i--) {
            for (int j =  y + height-1; j>=y && j < n - 1; j--) {
                maze[i][j] = 0;
            }
        }
       */ 
    }

    void linkChambers(int x1, int y1, int x2, int y2) {
        if (x1 == x2) {
            for (int j = min(y1, y2); j <= max(y1, y2); j++) {
                maze[x1][j] = 0;
            }
        }
        else if (y1 == y2) {
                for (int i = min(x1, x2); i <= max(x1, x2); i++) {
                    maze[i][y1] = 0;
                }
             }
    }

void generateMaze() {
    resizeAndInitializeMaze(n, n);
    //srand(unsigned(time(0)));
    //createChamber(4, 4,  4, 4);
    
    createChamber(1, 1, 3, 3);
    createChamber(1, 5, 3, 3);
    createChamber(5, 1, 3, 3);
    createChamber(5, 5, 3, 3);
     linkChambers(2, 3, 5, 3);
     linkChambers(3, 2, 3, 5);
     linkChambers(6, 3, 6, 5);
     linkChambers(5, 6, 2, 6);
     
}

void cravePath(int startX, int startY) {
    stack<Coord> s;
     s.push({ startX, startY });
    maze[startX][startY] = 0;
    random_device rd;
     mt19937 g(rd());

      while (!s.empty()) {
          Coord current = s.top();
          s.pop();
          int x = current.first;
          int y = current.second;
          shuffle(begin(Dir), end(Dir), g);
  
          for (int i = 0; i < 4; ++i) {
              int newX = x + Dir[i][0] * 2;
              int newY = y + Dir[i][1] * 2;
              if (newX >= 0 && newX < n && newY >= 0 && newY < n && maze[newX][newY] == -1) {
                  maze[newX][newY] = 0;
                  maze[x + Dir[i][0]][y + Dir[i][1]] = 0;
                  s.push({ newX, newY });
              }
          }
      }
}

void invertMaze() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            maze[i][j] = -maze[i][j] - 1;
        }
    }
}

void printMaze(int a, int b, int d = 0) {
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

int main() {
    int counter=0;
    for(int i = 0; i<=9; ++i){
        for(int j = i+1; j<=9; ++j)
            for(int k = j+1; k<=9; ++k)        
         // if(i<j)
            {
             counter++ ;  
             cout<< " {" << i << "," << j << "," << k <<"}\t";
            }
             cout << endl;
    }
    cout << "counter="<<counter<<endl;
    cout<< "\n Generating 8x8 bidirectional maze with clear chambers and paths!\n";
    generateMaze();
    printMaze(1, 1);
    invertMaze();
    printMaze(1, 1);
    return 0;
}

/*

      1    2     3    4   5   6   7   8   9   10
  1 (1 1) (1 2) (1 3)
  2
  3
  4
  5
  6
  7
  8
  9
  10
*/