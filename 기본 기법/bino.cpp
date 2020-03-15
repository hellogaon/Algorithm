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
