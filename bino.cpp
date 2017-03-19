//이항계수 dp
#include <cstdio>
#include <cstring>

int T,M,N,cache[30][30];

int bino(int n, int r){
  if(r==0 || n==r) return 1;
  if(cache[n][r] != -1) return cache[n][r];
  return cache[n][r] = bino(n-1,r-1)+bino(n-1,r);
}

int main(){
  memset(cache,-1,sizeof(cache));
  scanf("%d",&T);
  while(T--){
    scanf("%d %d",&N,&M);
    printf("%d\n",bino(M,N));
  }
}
