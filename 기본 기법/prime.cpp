//에라토스테네스의 체
const int MAXN = 1000001;

int prime[MAXN];

int main(){
  for(int i=2;i*i<MAXN;i++){
    if(prime[i]==0){
      for(int j=i*i;j<MAXN;j+=i) prime[j]=1;
    }
  }
}
