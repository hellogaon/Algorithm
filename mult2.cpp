//카라추바 알고리즘
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void normalize(vector<int>& num, int *numlen){
  num.push_back(0);
  (*numlen)++;
  for(int i=0;i<*numlen;i++){
    if(num[i]<0){
      int borrow = (abs(num[i])+9)/10;
      num[i+1]-=borrow;
      num[i]+=borrow*10;
    }
    else{
      num[i+1]+=num[i]/10;
      num[i]%=10;
    }
  }
  while(*numlen>1&&num.back()==0){
    num.pop_back();
    (*numlen)--;
  }
}

void addTo(vector<int>& a, vector<int>& b, int k, int *an, int bn){
  if(bn==0) return;
  int temp = max(0,bn-*an+k);
  for(int i=0;i<temp;i++){
    a.push_back(0); (*an)++;
  }
  for(int i=0;i<bn;i++)
    a[i+k]+=b[i];
}

void subFrom(vector<int>& a, vector<int>& b, int bn){
  if(bn==0) return;
  for(int i=0;i<bn;i++) a[i]-=b[i];
}

vector<int> multiply(vector<int>& a, vector<int>& b, int an, int bn){
  int cn=an+bn+1;
  vector<int> c(cn,0);
  for(int i=0;i<an;i++)
    for(int j=0;j<bn;j++)
      c[i+j]+=a[i]*b[j];
   return c;
}

vector<int> karatsuba(vector<int>& a, vector<int>& b, int an, int bn){
  if(an<bn) return karatsuba(b,a,bn,an);
  if(an==0 || bn==0) return vector<int>();
  if(an<=96) return multiply(a,b,an,bn);
  int hhalf = an/2, half = an/2;
  vector<int> a0(a.begin(),a.begin()+half);
  vector<int> a1(a.begin()+half,a.end());
  int bhalf = min<int>(bn,half);
  vector<int> b0(b.begin(),b.begin()+bhalf);
  vector<int> b1(b.begin()+bhalf,b.end());
  vector<int> z2 = karatsuba(a1,b1,an-half,bn-bhalf);
  int z2len=z2.size();
  vector<int> z0 = karatsuba(a0,b0,half,bhalf);
  int z0len=z0.size();
  addTo(a0,a1,0,&half,an-half);
  addTo(b0,b1,0,&bhalf,bn-bhalf);
  vector<int> z1 = karatsuba(a0,b0,half,bhalf);
  int z1len=z1.size();
  subFrom(z1,z0,z0len);
  subFrom(z1,z2,z2len);
  int retlen=0;
  vector<int> ret;
  addTo(ret,z0,0,&retlen,z0len);
  addTo(ret,z1,hhalf,&retlen,z1len);
  addTo(ret,z2,hhalf+hhalf,&retlen,z2len);
  return ret;
}

int main(){
  char x[300001]={0},y[300001]={0},ans[600001]={0};
  int i,xlen,ylen,top=0;
  scanf("%s %s",x,y);
  xlen=strlen(x); ylen=strlen(y);
  vector<int> a(300000); vector<int> b(300000);
  for(i=0;i<min(xlen,ylen);i++){
    a[i]=x[xlen-1-i]-'0';
    b[i]=y[ylen-1-i]-'0';
  }
  if(xlen>ylen) for(int j=i;j<xlen;j++) a[j]=x[xlen-1-j]-'0';
  else for(int j=i;j<ylen;j++) b[j]=y[ylen-1-j]-'0';
  vector<int> c = karatsuba(a,b,xlen,ylen);
  int cn=c.size();
  normalize(c,&cn);
  for(int i=cn-1;i>=0;i--)
  ans[top++]=c[i]+'0';
  printf("%s\n",ans);
}
