//에라토스테네스의 체
#include <cstdio>

int prime[1000001];

int main(){
  for(int i=2;i*i<1000001;i++){
    if(prime[i]==0){
      printf("%d ",i);
      for(int j=i*i;j<1000001;j+=i) prime[j]=1;
    }
  }
}
