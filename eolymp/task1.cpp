#include <iostream>
using namespace std;

    int f(int number){
                      int l(0);
                    	 for (int i=0; i<number; i++)
                   	     for (int j=i+1; j<number; j++){
                   			     l += 1;
                   	     }
                         return l;
    }
int main() {
	int n;
	 cin>>n;
    cout << f(n)<<endl; 
     return 0;
}