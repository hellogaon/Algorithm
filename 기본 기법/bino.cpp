//이항계수 dp
int cache[1001][1001];

int dp(int n, int k){
  if(k == 0 || k == n) return 1;
  int& ret = cache[n][k];
  if(ret != -1) return ret;
  ret = (dp(n-1,k-1) + dp(n-1,k)) % MOD;
  return ret;
}