//에라토스테네스의 체
const int MAXN = 1000001;

int prime[MAXN];

void init(){
  for(ll i=2;i*i<MAXN;i++){
    if(prime[i]==0){
      for(ll j=i*i;j<MAXN;j+=i) prime[j]=1;
    }
  }
}
