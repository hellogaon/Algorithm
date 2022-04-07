//이항계수 dp
int cache[1001][1001];

int dp(int n, int k){
  if(n < k) return 0;
  if(k == 0 || k == n) return 1;
  int& ret = cache[n][k];
  if(ret != -1) return ret;
  ret = (dp(n-1, k-1) + dp(n-1, k)) % MOD;
  return ret;
}

memset(cache, -1, sizeof(cache));

// 페르마의 소정리
ll mul(ll x, ll n){
  if(n == 0) return 1LL;
  if(n % 2 == 1) return (mul(x, n-1) * x) % MOD;
  ll h = mul(x, n/2) % MOD;
  return (h * h) % MOD;
}

ll nCk(int n, int k){
  if(n < k) return 0;
  ll a = 1, b = 1;
  for(int i=1;i<=n;i++)
    a = (a * i) % MOD;
  for(int i=1;i<=k;i++)
    b = (b * i) % MOD;
  for(int i=1;i<=n-k;i++)
    b = (b * i) % MOD;
  return (a * mul(b, MOD - 2)) % MOD;
}

// 뤼카의 정리
// 작은 소수 p에 대해 이항 계수
int lucas(int n, int k, int m){
  int ret = 1;
  while(n || k){
    ret *= dp(n%m, k%m, (m == 97 ? 0 : 1));
    n /= m, k /= m, ret %= m;
  }
  return ret;
}
