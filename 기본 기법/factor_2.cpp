//에라토스테네스 체를 이용한 소인수분해
#include <cstdio>
#include <vector>

using namespace std;

int minFactor[10000001];

void eratosthenes(int n){
  minFactor[0] = minFactor[1] = -1;
  for(int i=2;i<=n;i++)
    minFactor[i]=i;
  for(int i=2;i*i<=n;i++){
    if(minFactor[i]==i){
      for(int j=i*i;j<=n;j+=i){
        if(minFactor[j]==j)
          minFactor[j]=i;
      }
    }
  }
}

int main(){
  int N;
  scanf("%d",&N);
  eratosthenes(N);
  vector<int> factor;
  while(N>1){
    factor.push_back(minFactor[N]);
    N/=minFactor[N];
  }
  for(int i=0;i<factor.size();i++){
    printf("%d\n",factor[i]);
  }
}
