//큰 두수를 곱하는 n^2 알고리즘
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;
void normalize(vector<int>& num){
  num.push_back(0);
  for(int i=0;i<num.size();i++){
    num[i+1]+=num[i]/10;
    num[i]%=10;
  }
  while(num.size()>1&&num.back()==0) num.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b){
  vector<int> c(a.size()+b.size()+1,0);
  for(int i=0;i<a.size();i++)
    for(int j=0;j<b.size();j++)
      c[i+j]+=a[i]*b[j];
  normalize(c);
  return c;
}

int main(){
  char x[100]={0},y[100]={0};
  int xlen,ylen;
  scanf("%s %s",x,y);
  xlen=strlen(x); ylen=strlen(y);
  vector<int> a(xlen);
  vector<int> b(ylen);
  for(int i=0;i<xlen;i++) a[i]=x[xlen-1-i]-'0';
  for(int i=0;i<ylen;i++) b[i]=y[ylen-1-i]-'0';
  vector<int> c = multiply(a,b);
  for(int i=c.size()-1;i>=0;i--)
    printf("%d",c[i]);
  printf("\n");
}
