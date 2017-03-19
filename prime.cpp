//에라토스테네스의 체
#include <stdio.h>

int main(){
  int prime[6000001]={};
  for(int i=2;i*i<6000001;i++){
    if(prime[i]==0){
      printf("%d ",i);
      for(int j=i*i;j<6000001;j+=i) prime[j]=1;
    }
  }
}
