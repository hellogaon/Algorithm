//뫼비우스 함수 Mobius function
//완전제곱수를 약수로 가지지 않으면서 서로 다른 소인수가 짝수 개라면 1
//완전제곱수를 약수로 가지지 않으면서 서로 다른 소인수가 홀수 개라면 −1
//완전제곱수를 약수로 가지면 0
//n이하의 Square Free 개수 = simga (1 <= i <= sqrt(n)) { M(i) * ceil(n / i^2) }

const int MAXN = 100005;

int M[MAXN];

//n이하의 Square Free 개수 - O(sqrt(n))
ll square_free(ll n){
  ll ret = 0;
  for(int i=1;i*i<=n;i++)
    ret += M[i] * (n/(i*i));
  return ret;
}

//뫼비우스 함수 생성 - O(sqrt(N))
for(int i=1;i<MAXN;i++) M[i] = 1;
for(int i=2;i*i<MAXN;i++){
  if(M[i] == 1){
    for(int j=i;j<MAXN;j+=i) M[j] *= -i;
    for(int j=i*i;j<MAXN;j+=i*i) M[j] = 0;
  }
}
for(int i=2;i<MAXN;i++){
  if(M[i] == i) M[i] = 1;
  else if(M[i] == -i) M[i] = -1;
  else if(M[i] < 0) M[i] = 1;
  else if(M[i] > 0) M[i] = -1;
}
