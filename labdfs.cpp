#include <iostream>
#include <stack>  // Stack for Depth-First Search
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

using Coord = pair<int, int>;  // Coordinates
using Vi = vector<int>;
using VVi = vector<Vi>;

const int n = 8;  // Maze size
VVi maze;  // Maze representation
int Dir[4][2] = {
    {+1, 0},  // Down
    {-1, 0},  // Up
    {0, +1},  // Right
    {0, -1}   // Left
};

   void resizeAndInitializeMaze(int m, int n) {
       maze.resize(m, Vi(n, -1));  // Initialize maze cells
   }
       // Random generator function for shuffling directions
       int g(int i) { return rand() % i; }

   void generateHoles(){
    resizeAndInitializeMaze(n, n);  // Initialize the maze
    srand(unsigned(time(0)));
     for(int h=0; h<n/2; h++){
         int X = rand() % (n - 2) + 1;
         int Y = rand() % (n - 2) + 1;    
          maze[X][Y]=0;
     }
   }       

   void cravePath(int startX, int startY, int (*g)(int)) {
       stack<Coord> s;  // Stack for DFS
        s.push({ startX, startY });
        maze[startX][startY] = 0;
   
        while (!s.empty()) {
            Coord current = s.top();
             s.pop();
   
             int x = current.first;
             int y = current.second;
   
            // Shuffle directions for random exploration
            random_shuffle(begin(Dir), end(Dir), g);
   
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



void generateMaze() {
    resizeAndInitializeMaze(n, n);  // Initialize the maze
    srand(unsigned(time(0)));
    int startX = rand() % (n - 2) + 1;
    int startY = rand() % (n - 2) + 1;
    cout << " Starting point for maze generation: (" << startX << "," << startY << ")\n";

     cravePath(startX, startY, g);  // Generate maze using DFS

      //for (int i = 0; i < n; ++i) {
      //    maze[i][0] = maze[i][n - 1] = -1;  // Wall boundaries
      //    maze[0][i] = maze[n - 1][i] = -1;
      //}
}
void invertMaze(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
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
    cout << "\n Generating 8x8 maze using DFS!\n";
    
    //generateMaze();
    generateHoles();
     printMaze(1, 5);  // Print the maze
      invertMaze();
        printMaze(1, 5);  // Print the maze
    return 0;
}
