//카탈란 수 : 1,2,5,14,42,132,429...
//Cn = 1 / n+1 * (2n n)
//C0 = 1 and Cn = (Ci * Cn-1-i) (sigma i = 0~n-1)
ll C[10001] = {1};

//방법 1 - O(N)
ll mul(ll X, ll N){
  if(N==0) return 1;
  if(N%2==1) return (mul(X, N-1)*X)%MOD;
  ll half = mul(X, N/2)%MOD;
  return (half*half)%MOD;
}

for(int i=1;i<=2*N;i++) fac[i] = (fac[i-1]*i) % MOD;
  for(int i=0;i<=N;i++)
    C[i] = (fac[2*i]*mul((mul(fac[i], 2)*(i+1))%MOD, MOD-2)) % MOD; 

//방법 2 - O(N^2)
for(int i=1;i<=N;i++)
  for(int j=0;j<i;j++)
    C[i] = (C[i] + ((C[j] * C[i-1-j]) % MOD)) % MOD;

