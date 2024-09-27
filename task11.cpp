/*
https://basecamp.eolymp.com/ru/problems/11
Дана рациональная дробь m / n. Запишите её в виде десятичной дроби с точностью k знаков после запятой.
Входные данные
В одной строке записано 3 числа m, n, k. 0 < m, n ≤ 100, 0 ≤ k ≤ 1000.

Выходные данные
Вывести k точных значащих цифр после десятичной точки искомого числа.

Ввод #1
1 2 3
Ответ #1
0.500

*/

#include <iostream>

using namespace std;

char format [10];

int main(){
    int m,n,k;
     cin >> m >> n >> k;

      double r = (double)m/(double)n;
       
       //cout << r;
       
       int   l=sprintf (format, "%%.%ldf", k);
         printf(format,r);
//         printf("format length=%d\n",l);  
//          printf("format=%s\n",format);  
            return 0;
}
/*
2 7 48 
0.285714285714285714285714285714285714285714285714

??
0.285714285714285698425385362497763708233833312988
*/