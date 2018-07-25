//소인수분해 간단한 방법
#include <cstdio>
#include <vector>

using namespace std;

int main(){
  int N;
  scanf("%d",&N);
  vector<int> factor;
  for(int i=2;i*i<=N;i++){
    while(N%i==0){
      N/=i;
      factor.push_back(i);
    }
  }
  if(N>1) factor.push_back(N);
  for(int i=0;i<factor.size();i++){
    printf("%d\n",factor[i]);
  }
}
