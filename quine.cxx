#include <iostream>
#include <string>
using namespace std;
char n=10, q=34, z=44;
string K[] = {
"#include <iostream>",
"#include <string>",
"using namespace std;",
"char n=10, q=34, z=44;",
"string K[] = {",
"};",
"int main(){",
"string S;",
"for(int i=0; i<5; i++)S+=K[i]+n;",
" for(int i=0; i<14; i++)S+=q+K[i]+q+z+n;",
"  for(int i=5; i<14; i++)S+=K[i]+n;",
"   for(int j=0; j<100; j++)S+=to_string(j)+K[14];",
"    cout<<S<<endl;",
"}",
"Max",
};
int main(){
string S;
for(int i=0; i<5; i++)S+=K[i]+n;
 for(int i=0; i<15; i++)S+=q+K[i]+q+z+n;
  for(int i=5; i<14; i++)S+=K[i]+n;
   for(int j=0; j<100; j++)S+=to_string(j)+K[14];
    cout<<S<<endl;
}
