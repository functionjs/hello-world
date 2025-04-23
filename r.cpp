/*
What do we want to do?
We want to construct a class for rational numbers.

What is it functional:

1. Create rational numbers 
   Example/.
  If we want to deal with rational number  2/3 then we may create it by our class constructor:
  Rational x(2, 3);
  or
  Rational x = new Rational(2, 3);
  Rational x = new Rational(2, -3); -->  Rational(-2, 3);

  We want to get numerator and denominator
  for example 
       x.getNumerator();
       x.getDenominator();
 
 We want also set numerator and denominator:
       x.setNumerator();
       x.setDenominator();

2.  We know that 10/15 is equal to 2/3
   Then we want that if we create fraction
  Rational x(10, 15);  
  we must automatically fraction  x(2, 3).
  How to simplify 10/15 to 2/3 ?
   What algorithm can find common factor - Euclidean algorithm

3. We want to develop set of algebraic operation with fractions
    + - * /  and command .simplify()

4. We want smart print of fraction
    For example
    if we create x=Rational(2,3);
    then we may print them by command 
      cout << x; 
      and get 2/3
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;
using num = long;
using  CF = vector<num>; //Continued Fraction repesentation

static int M = 0;
num K;

 class Rational {
                 //-fields and  methods of class  Rational
                
 public:    
            static int N ; // declaration of public static variable N of class Rational
             
            static  void Print(const Rational &R){
                                     std::cout << R.numerator<<"/"<<R.denominator;  
                    }
/*
 5/7 = 
       1/[7/5] = 
          R1      1/[1+2/5] =
                     q  R1_      1/[1+1/[5/2]] = 
                                              1/[1+1/[2 +1/2]] = 
                                                                0 + 1/[1 + 1/[2 +1/[2+ 0/1 ]]] 
                                                                *      *      *     *
 5/7= [0; 1 2 2]
*/
            static  Rational makeRational(const CF &cf){
                           num l =  cf.size();
                           num c =  cf.capacity();
                            if(c==0){
                                     Rational r(0,0);
                                      return r;
                            }
                             if(l==0){
                                      Rational r(1,0);
                                       return r;
                             }

                             num n = 0, d=1; 
                              for(num k=l-1; k>=0; --k){
                                       n += cf[k]*d;
                                        swap(d, n);  
                                         cout << "n="<<n << " d="<<d<<endl;
                              }
                               Rational r(d,n);
                                return r;
            }

            static  Rational makeMaxRational(const CF &cf){
                           num l =  cf.size();
                           if (l == 0) {
                              return Rational(0, 0);
                           }
                  
                            Rational r(cf[l - 1], 1);
                            for (int i = l - 2; i >= 0; --i) {
                              r.inverse();
                               r += Rational(cf[i], 1);
                            }
                                return r;
            }
            static  CF makeContinued(const Rational &R){
                                     CF cf;
                                     num n = R.numerator;
                                     num d = R.denominator;
                                      // 0/0 --> [] and capacity is 0
                                      if(n==0 and d==0){cf.reserve(0);return cf;}
                                       // d/0 --> []
                                       if(d==0){return cf;}
                                      // 0/d --> [0]
                                        if(n==0){
                                                cf.push_back(0);
                                                 return cf;
                                        }
                                         // n/1 --> [n]
                                         if(d==1){
                                                 cf.push_back(n);
                                                  return cf;
                                         }

                                          num q,r;
                                           do {
                                               q=n/d;
                                               r=n%d;
                                                cf.push_back(q);
                                                n=d;
                                                 d=r;
                                           } while(r != 0);    
                                            return cf;
          }

            
            static  void Print(const CF cf){
                                            num l = cf.size(); 
                                            cout <<"[";              
                                             for(num i=0; i<l; ++i) cout<<cf[i]<<" ";
                                              cout <<"]";              
            }
            static  void PrintAsContinued(const Rational &R){Print(makeContinued(R));}
            static  void PrintAsContinued_(const Rational &R){
                          cout <<"[";
                           
                           num q = R.numerator/R.denominator;
                           num r = R.numerator%R.denominator;
                            Rational R_next(r, R.denominator);
                            cout <<q <<" ";
                             
                            while (r != 0) {
                               R_next.inverse();

                                q = R_next.numerator / R_next.denominator;
                                r = R_next.numerator % R_next.denominator;

                                cout << q <<" ";

                                  R_next.numerator=r;
                            }      
                             cout <<"]";

                             
                       } 

                 static  num GCD(num a, num b){
                                           if(a==0)return b;
                                            return GCD(b%a, a);
                    }
            static  num LCM(num a, num b){
                                           if(a==0 or b==0) return 0;  
                                            return a/GCD(a,b) *b;
                    }        


            static num Simplify(Rational &z){
                                      num n = z.numerator;
                                      num d = z.denominator;
                                       if(n==0 and d==0) return 0;
                                        if(d==0) {
                                                   z.numerator  = 1;
                                                    return 1;
                                        }
                                         if(n==0) {
                                                   z.denominator= 1;   
                                                    return 1;
                                         }
                                          if(d==1) {
                                                      return n;
                                          }

                                            num g = GCD(n, d); 
                                             z.numerator   /= g;   
                                             z.denominator /= g;  
                                              return g;
                         }        

           static Rational Sum(Rational x, Rational y){
                                num d = LCM(x.denominator,y.denominator);
                                 num n =  x.numerator*(d/x.denominator) + y.numerator*(d/y.denominator);
                                  Rational z(n, d); 
                                   return z; 
           } 



  //-fields, constuctors and  methods of object of class  Rational
  private: 
           //utility function  
           num gcd(num a, num b){
                    if(a==0)return b;
                     return gcd(b%a, a);
                  }



  public:  
           num numerator;
           num denominator;    
           

           // constructors (initializers) of object data
           Rational (num n){ 
                                        numerator   = n;
                                        denominator = 1;
           }
           Rational (num n, num d){ 
                                       if(n==0 and d==0) {
                                                          numerator  = 0;
                                                          denominator= 0;   
                                                           return;
                                       }
                                        if(d==0) {
                                                   numerator  = 1;
                                                   denominator= 0;   
                                                    return;
                                        }
                                         if(n==0) {
                                                   numerator  = 0;
                                                   denominator= 1;   
                                                    return;
                                         }
                                         /*
                                               if(n==1 or d==1) {
                                                     numerator  = n;
                                                     denominator= d;   
                                                      return;
                                          }
                                         */ 

                                           num g = gcd(n, d); 
                                            numerator  = n/g;
                                            denominator= d/g;   
           }
           Rational (const Rational &q){ 
                                        numerator  = q.numerator;
                                        denominator= q.denominator;   
           }

           Rational (CF V){
                               /*
                                    num l = V.size();   
                                    Rational R(0);
                                     for(num k=l-1; k>=0; --k){ 
                                            Rational v(V[k]);
                                            cout << k<<") "<<(string)R << " v=" <<v<<endl;
                                             R.inverse();
                                              cout << "    R.inverse()= "<< (string)R <<endl;
                                              R +=  v;
                                               cout << "    R.inverse() + v  = "<<(string)R <<endl;
                                     } 
                                      // R = V[0] + R;
                                        R.simplify();
                                         numerator = R.numerator;
                                         denominator = R.denominator;
                               */            
                               Rational R = makeRational(V);
                                         R.simplify();
                                          numerator = R.numerator;
                                          denominator = R.denominator;

           } 

           Rational  operator=(const num x){
                                             numerator  = x;
                                             denominator= 1; 
                                              return *this;
           }

           bool  operator==(const Rational &y) const {
                                                      return (numerator==y.numerator) and (denominator==y.denominator);
           }
            
           // methods of objects  
           num getNumerator(){return  numerator;}
           num getDenominator(){return  denominator;} 

           void inverse(){
                          swap(numerator,denominator);  
                          /*
                            num temp =  denominator;
                             denominator = numerator;
                              numerator    = temp;
                          */    
                          /*
                          (denominator, numerator) = (numerator=3 , 
                                                       denominator=numerator*numerator, 
                                                         denominator+6 ); 
                          */                               
           } 
                  num simplify(){
                                 if(numerator==0 and denominator==0) return 0;
                                  if(denominator==0){
                                           numerator = 1;
                                            return 1;
                                  }
                                    if(numerator==0){
                                               denominator = 1;   
                                                return 1;
                                    }
                                      if(denominator==1) {
                                                return numerator;
                                      }
                                      if(numerator==1) {
                                                return denominator;
                                      }

                                       num g = gcd(numerator, denominator); 
                                        numerator   /= g;
                                        denominator /= g;
                                         return g;   
                  }
              void crudeAdd(Rational y){
                 //num l = LCM(denominator,y.denominator);
                 //cout << " l=LCM("<<denominator<<","<<y.denominator<<")="<<l<<endl;
                 Rational x_(*this);
                  numerator = numerator*y.denominator + y.numerator*denominator;
                   denominator *= y.denominator;
                    num g = simplify();
                     if(g>1){
                       K++;
                       // cout << K <<") " << (string)x_<<"+"<<(string)y<<" simplifyed by "<<g<<endl;
                     }
              }

              //   x.add(y)     x->add(y)
              // 3/4 + 5/6 = (3*(12/4)+ 5*(12/6)) /12 
              void add(Rational y){
                // n/d + 0/y.d = n/d
                if(y.numerator==0)return;  
                // n/0 + y.n/y.d = 1/0
                // n/d + y.n/0   = 1/0
                if(denominator==0 or y.denominator==0){numerator=1; denominator=0;return;} 
                // 0/d + y.n/y.d = y.n/y.d 
                if(numerator==0){ 
                                  numerator = y.numerator;
                                  denominator = y.denominator ; 
                                   return;
                                }  
                 num l = LCM(denominator,y.denominator);
                 //cout << " l=LCM("<<denominator<<","<<y.denominator<<")="<<l<<endl;
                 Rational x_(*this);
                  numerator = numerator*(l/denominator) + y.numerator*(l/y.denominator);
                   denominator = l;
                    num g = simplify();
                     if(g>1){
                       K++;
                       // cout << K <<") " << (string)x_<<"+"<<(string)y<<" simplifyed by "<<g<<endl;
                     }
              }
            // syntactic sugar for add()  
   /*this*/  Rational operator+(const Rational &y){
                                                  Rational x_(*this);
                                                   x_.add(y);
                                                    return x_;
             } 
            Rational operator - (void) {
                                                    return Rational(-numerator,denominator);
            }
            Rational operator+=(const Rational y){
                                                  add(y);
                                                   return *this;

            }

                //   x.mult(y)   
                // 3/4 * 5/6 = (3/(gcd(3,6))*5/gcd(5,4)) / ... 
                void mult (Rational y){
                                       num g1 = GCD(numerator, y.denominator);
                                       num g2 = GCD(y.numerator, denominator);
                                        numerator   = (numerator/g1) * (y.numerator/g2);
                                        denominator = (denominator/g2)*(y.denominator/g1);                     ;
                } 
            // syntactic sugar for mult()
          Rational operator* (const Rational &y){
                                                Rational x_(*this);
                                                 x_.mult(y);
                                                  return x_;
          }

          operator string() const{
                                  return to_string(numerator) + "/" + to_string(denominator);
          }
          operator double() const{
                                  return (double)numerator/denominator;
          }


};
int Rational::N=0; //initialization of public static variable N of class Rational

 // Big Sets of Numbers: N in Z in Q in A in R in C in ?

///////////////////////////////////////////////////////////////////////
int main(){
 cout << "Hello Rational numbers!"<<endl;   
 Rational::N=1;
  cout <<  "Rational::N ="  <<  Rational::N     << endl;

 Rational X(13, 47);
  cout <<  "X = "  <<  (string)X    << endl;
  /*
   All natural solutions to equation 
    1/a + 1/b + 1/c + 1/d = 1
    For example, 
     for a=2 b=3 c=7 d=? 
    we have 
    1/2 + 1/3 + 1/7 + 1/42 = 1
  */
  // 1/2.0 +1/3.0 +1/7.0 + 1/42.0 
  long double a,b,c,d,e; 
  long double x,y,z,w, s, one, eps;
  int T;
  one = 1;
  eps = 0.000000000000000001;
   T = eps;
   a = 2;
   b = 3;
   c = 7;
   d = 42;   
    x = 1/a;    
    y = 1/b;  // 0.0101010101....  
    z = 1/c;    
    w = 1/d;
     s = x + y + z + w;
      

   
    printf (" x=%18.18Lf\n", x); 
    printf (" y=%18.18Lf\n", y); 
    printf (" z=%18.18Lf\n", z); 
    printf (" w=%18.18Lf\n", w); 
    printf ("  s =x + y + x + w = %18.18Lf\n", s); 
     printf (" T=eps= %18i\n", T); 

          
        // s == one
    if(abs(s - one) < eps){
       cout << setprecision(15)<< "1/2.0 +1/3.0 +1/7.0 + 1/42.0 = 1 = " << 1/2.0 +1/3.0 +1/7.0 +1/42.0 << endl;
    }
    else {
       cout << setprecision(15)<< "1/2.0 +1/3.0 +1/7.0 + 1/42.0 ="<< s << " != 1 " << endl;
    }
   
   M=100;
   num counter=0;
   num solution_counter=0;
     for(a=1; a<=M; a++){
         for(b=a; b<=M; b++){
             for(c=b; c<=M; c++){
                for(d=c; d<=M; d++){
               //      for(e=d; e<=M; e++){
                     
                         //if(abs(1/a + 1/b + 1/c + 1/d +1/e - 1)<eps)
                       if(abs(1/a + 1/b + 1/c +1/d - 1)<eps) 
                      // if(abs(1/a + 1/b + 1/c - 1)<eps)
                         {
                            solution_counter++;
                      //       cout<<solution_counter<<") "<<a<<", "<<b<<", "<<c<<", "<<d<<", "<<e<<endl;
                               cout<<solution_counter<<") "<<a<<", "<<b<<", "<<c<<", "<<d<<endl;
                             // cout<<solution_counter<<") "<<a<<", "<<b<<", "<<c<<endl;
                           
                         }
                //     }    
                       counter++; 
                 }
             }
         }
     }        
     
     cout << solution_counter <<" solutions from "<< counter << " tries"<< endl;

         
       

  return 0;
}
/*
 5/7 = 
       1/[7/5] = 
                  1/[1+2/5] =
                              1/[1+1/[5/2]] = 
                                              1/[1+1/[2 +1/2]] = 
                                                                 1/[1+1/[2 +1/[2/1]]] 

 5/7= [0; 1 2 2]

   0|  2  | 
    |1   2|

*/
/*

  1/2 + 1/4 + 1/8 + 1/16 + ....... ~=1

  1/1 + 1/2 + 1/3 + 1/4 + 1/5 + .....+ 1/N ~= ln(N) 

  1/a + 1/b + 1/c + 1/d = 1

  1/2 + 1/3 + 1/7 + 1/42 = 1
  1/4 + 1/4 + 1/4 + 1/4 = 1    

*/
