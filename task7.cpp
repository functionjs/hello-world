/*
https://basecamp.eolymp.com/ru/problems/7
Римские числа

Посчитать сумму двух натуральных чисел A и B, 
записанных в римской системе счисления.
 Ответ также записать в римской системе счисления.
M = 1000, D = 500, C = 100, L = 50, X = 10, V = 5, I = 1. 
 Все числа – не превышают 2000.

Пример 1
Ввод 
III+XV
Ответ
XVIII

Пример 2
Ввод 
III+XVI
Ответ
XIX
*/
#include <iostream>

using namespace std;

const int M = 1000, D = 500, C = 100, L = 50, X = 10, V = 5, I = 1;
char R[] = {'I','V','X','L','C','D','M'}; // R[0]=I; R[1]=V; R[2]=X; ...

          int c;
          string getRomeCiphersFrom_c(){
                                 if(c==4){c-=4; return "IV";}
                                 if(c==9){c-=9; return "IX";}
                                 if(c/10 == 4){c-=40; return "XL"; }
                                 if(c/10 == 9){c-=90; return "XC"; }
                                 if(c/100 == 4){c-=400; return "CD"; }
                                 if(c/100 == 9){c-=900; return "CM"; }

                                  if(c>=M){c-=M; return "M";}
                                  else if(c>=D){c-=D; return "D";}
                                       else if(c>=C){c-=C; return "C";}
                                            else if(c>=L){c-=L; return "L";}
                                                 else if(c>=X){c-=X; return "X";}
                                                      else if(c>=V){c-=V; return "V";}
                                                           else if(c>=I){c-=I; return "I";}
                                   return "?";
          }
 
          int Y[15];
          void translateFromRomeToInt(string Z){ // string Z --> int Y[]
                int length = Z.length();
                 for(int j=0; j<length; j++){
                       char r=Z[j]; 
                        if(r=='L')Y[j]=L;
                        if(r=='I')Y[j]=I;
                        if(r=='M')Y[j]=M;
                        if(r=='D')Y[j]=D;
                        if(r=='C')Y[j]=C;
                        if(r=='X')Y[j]=X;
                        if(r=='V')Y[j]=V;
                 }
          } 
     int getValue(string Z)
         {
           translateFromRomeToInt(Z); // string Z --> int Y[]
           int z=0; 
           int length = Z.length();
            for(int j=0; j<length-1; j++){
                  int r=Y[j]; 
                  int q=Y[j+1]; 
                   z+= (r>=q)? r :-r;  
            }
             z+= Y[length-1];
              return z;
         } 

int main(){
    string A="",B="", S;
     cin >> S;
      int l=S.length();
    int i;
       for(i=0; i<l; i++){
          if(S[i]=='+') break;
           A += S[i];
       }   
        for(i++; i<l; i++){
             B += S[i];
        } 
         int a = getValue(A);
         int b = getValue(B);
          c = a+b; 
           while(c>0)cout <<  getRomeCiphersFrom_c();
            cout << endl ;
             return 0;
}
