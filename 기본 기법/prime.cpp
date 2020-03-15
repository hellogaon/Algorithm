//에라토스테네스의 체
const int MAXN = 1000001;

int prime[MAXN] = {1,1};

void init(){
  for(ll i=2;i*i<MAXN;i++){
    if(!prime[i]){
      for(ll j=i*i;j<MAXN;j+=i) prime[j] = 1;
    }
  }
}
