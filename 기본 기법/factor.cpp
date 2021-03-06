//에라토스테네스 체를 이용한 소인수분해
const int MAXN = 10000001;

int minFactor[MAXN];

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