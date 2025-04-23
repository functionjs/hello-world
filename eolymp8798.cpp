/*
https://basecamp.eolymp.com/ru/problems/8798
ДСУ

В Ужляндии есть n городов, пронумерованных от 1 до n. В настоящее время в Ужляндии нет дорог, но со временем они появятся.
Турист Василий попросил вас ответить на q запросов двух типов:
1 a b — Создана двусторонняя дорога между городами a и b.
2 a b — Можно ли из города a доехать в город b, используя дороги? (Если да, выведите "YES" без кавычек, если нет — выведите "NO" без кавычек.)

Входные данные
В первой строке записаны числа n и q. (1 ≤ n, q ≤ 2*10^5*)
В следующих q строках записаны запросы.

Выходные данные
Выведите ответы на запросы типа 2.

Примеры
Входные данные №1
5 7
1 1 2
1 1 3
2 1 2
1 2 3
2 1 1
1 1 5
2 5 4
Ответ №1
YES
YES
NO
*/

#include <iostream>

using namespace std;


const int MaxSize = 1 + 2e5;

  // structures and methods of Disjoint Union Sets                             
  int Parent[MaxSize];
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

   int main(){
     int n, q;
      cin >> n >> q;
       for(int i=1; i<=n; ++i){
           make_one_element_set(i);
       }
          
      int T, a,b;
       for(int k=0; k<q;++k){
           cin >> T >> a >> b;
            // todo!
            if(T==1){
               union_sets_of(a, b);   
            } 
            if(T==2){
                int SP1 = findSuperParentOf(a);
                int SP2 = findSuperParentOf(b);
                 if(SP1==SP2)cout << "YES"<<endl;
                 else        cout << "NO"<<endl;
            }
       }
     


   }