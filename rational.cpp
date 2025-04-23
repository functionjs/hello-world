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
#include <sstream>


using namespace std;
using num=long;

num K;

 class Rational {
                 //-fields and  methods of class  Rational
                
 public:    
            static int N; // declaration of public static variable N of class Rational
             
            static  void Print(Rational R){
                                     std::cout << R.numerator<<"/"<<R.denominator;  
                    }
            static  void PrintChain (Rational R){
                          cout <<"[";
                           num q = R.numerator/R.denominator;
                            cout <<q <<";";
                             // to do !
                              cout<<" ... ";
                             cout <<"]";

                    }        

                 static  num GCD(num a, num b){
                                           if(a==0)return b;
                                            return GCD(b%a, a);
                    }
            static  num LCM(num a, num b){
                                            return a/GCD(a,b) *b;
                    }        


            static num Simplify(Rational &z){
                         num g = GCD(z.numerator, z.denominator); 
                          z.numerator /= g;   
                          z.denominator /= g;  
                           if(g>1)cout << "Simplifyed by "<<g<<endl; 
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
                                       num g = gcd(n, d); 
                                        numerator  = n/g;
                                        denominator= d/g;   
           }
           Rational (const Rational &q){ 
                                        numerator  = q.numerator;
                                        denominator= q.denominator;   
           }

           Rational  operator=(const num x){
                                             numerator  = x;
                                             denominator= 1; 
                                              return *this;
           }

           bool  operator==(const Rational &y) const {
                                                      return (numerator ==y.numerator) and (denominator==y.denominator);
           }
            
           // methods of objects  
           num getNumerator(){return  numerator;}
           num getDenominator(){return  denominator;} 
                  int simplify(){
                                  num g = gcd(numerator, denominator); 
                                   numerator   /= g;
                                   denominator /= g;
                                    return g;   
                  }
              void crudeAdd(Rational y){
                 num l = LCM(denominator,y.denominator);
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
            Rational operator+(const Rational &y){
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
 // N in Z in Q in A in R in C 
///////////////////////////////////////////////////////////////////////
int main(){
 cout << "Hello Rational numbers!"<<endl;   

 Rational* z = new Rational(4, 8);  
 cout << "z->getNumerator() = "<< z->getNumerator();  // (*z).getNumerator()
  cout << endl;
 Rational::Print(*z);
  cout << endl;

 Rational w(10, -25);  
  cout<< "w = 10/-25 = "<< (string)w <<" ~= " << w << endl; 

 Rational x(10, 25);  
 Rational::Print(x);
 Rational y(5, 7);  
   //cout << "gcd(36,24)="<< Rational.gcd(36,24)<<endl;
  cout<<endl; 
  cout<< "x numerator is " << x.getNumerator()<<endl;
  cout<< "x denominator is " << x.getDenominator()<<endl;
  cout<< "x = " << x.getNumerator()<<"/"<<x.getDenominator()<<endl;
  cout<< "y = " << y.getNumerator()<<"/"<<y.getDenominator()<<endl;
    //x.add(y);
    //x.mult(y);
    //Rational q = Rational::Sum(x,y);
    Rational q = x+y;
      cout<< " q = x+y = " << (string)q<<" ~= "<<q<<endl;      
      
       q = x*y; 
        cout<< " q = x*y = " << (string)q<<" ~= "<<(double)q<< endl; 
        cout<<"to_string(q)="<<to_string(q)<<endl;  

        cout<< "Chain fraction: " ;      
         Rational::PrintChain(q) ;
          cout << endl;      
          /*
          // Try to know what is 1/2+1/4+1/8+1/16+.......
           q = 0; 
            cout<< " q = 0 ~= " <<to_string(q)<< endl;
           num d=1;
            for(int  i=1;i<32; i++){
                d*=2; //current denominator d = 2^i
                 Rational x(1, d);  // x=1/d
                 cout <<i<<") x = "<< (string)x << endl;
                  //q = q + x;
                  q += x;  
                   cout<< "    q = " << (string)q << " ~= "<<q<< endl;
            }
           */    
             num M=800;  
                 K=0;
             num C=0;
           /*  
              for(num n1=1; n1<=M; n1++)
                for(num d1=n1+1; d1<=M; d1++)
                  for(num n2=1; n2<=M; n2++)
                    for(num d2=n2+1; d2<=M; d2++)
                    {
                      Rational a(n1,d1);
                      Rational b(n2,d2);
                      C++;
                       Rational c = a + b;
                    }
                 cout << "from C="<< C<<" sum of proper fractions we have K="<< K << " that was simplified!"<< endl;   
                 Rational Q(K,C);
                 cout << "Ratio of  random reducible fractions sums is "<<(string) Q<< " ~= "<< Q << endl;     

             K=0;
             C=0;
              for(num n1=1; n1<=M; n1++)
                for(num d1=n1+1; d1<=M; d1++)
                  for(num n2=1; n2<=M; n2++)
                    for(num d2=n2+1; d2<=M; d2++)
                    {
                      Rational a(n1,d1);
                      Rational b(n2,d2);
                      C++;
                       Rational c = a + b;
                    }
                 cout << "from C="<< C<<" fine sum of proper fractions we have K="<< K << " that were simplified!"<< endl;   
                  Q = *new Rational(K,C);
                 cout << "Ratio of  random reducible fractions sums is "<<(string) Q<< " ~= "<< Q << endl;     

                 K=0;
                 C=0;
              for(num n1=1; n1<=M; n1++)
                for(num d1=n1+1; d1<=M; d1++)
                  for(num n2=1; n2<=M; n2++)
                    for(num d2=n2+1; d2<=M; d2++)
                    {
                      Rational a(n1,d1);
                      Rational b(n2,d2);
                      C++;
                       a.crudeAdd(b);
                    }
                 cout << "from C="<< C<<" crude sum of proper fractions we have K="<< K << " that were simplified!"<< endl;   
                  Q = *new Rational(K,C);
                   cout << "Ratio of random reducible fractions crude sums is "<<(string) Q<< " ~= "<< Q << endl;     
  
             K=0;
             C=0;    
             for(num n1=1; n1<=M*M; n1++)
                for(num d1=n1+1; d1<=M*M; d1++)
                    {
                      C++;
                       if(Rational::GCD(n1, d1)>1)K++;
                    }
               Q = *new Rational(K,C);
              cout << "from C="<< C<<" different fractions we have K="<< K << " that were simplified!"<< endl;
              cout << "Ratio of  random proper reducible fractions is "<<(string) Q<< " ~= "<< Q << endl;
          Rational::N++;
          cout << "Rational::N="<<Rational::N<<endl;
        */
             num k=0;
             Rational one(1);
             cout << " one is "<< string(one)<<endl;
              for(num d1=2; d1<=M; d1++)
                for(num d2=d1; d2<=M; d2++)
                  for(num d3=d2; d3<=M; d3++)
                    //for(num d4=d3; d4<=M; d4++)
                    {
                      Rational a(1,d1);
                      Rational b(1,d2);
                      Rational c(1,d3);
                       Rational abc = a + b + c;
                       if(abc>=1) continue;
                        Rational _abc = -abc;
                         Rational d = one + -abc;
                      C++;
                        
                       //Rational e = a + b + c + d;
                        //cout << string(e) << endl;
                        if(d.numerator==1 and d.denominator>=c.denominator)
                        //if(C<10)
                        {
                         // cout << " a + b + c = "<< (string)abc <<  "    -(a + b + c) = "<< (string)_abc <<endl;
                          k++;
                          cout 
                               << k<<") "
                               << string(a) <<" + "
                               << string(b) <<" + "
                               << string(c) <<" + "
                               << string(d) <<" = 1"<<endl;                                         
                               
                        }
                    }
                 cout << "from C="<< C<<" sum of fractions 1/a + 1/b + 1/c + 1/d we have k="<< k << " that are equals 1!"<< endl;   
                  Rational Q(k,C);
                  cout << "Ratio of  sums 1/a + 1/b + 1/c + 1/d = 1 is "<<(string) Q<< " ~= "<< Q << endl;     
       
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

  1/2+1/4+1/8+1/16+.......=1

  1/2+1/3+1/4+1/5 + .....=? 

*/