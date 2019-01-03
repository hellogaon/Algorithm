//이항계수 dp
int T,M,N,dp[30][30];

int bino(int n, int r){
  if(r==0 || n==r) return 1;
  if(dp[n][r] != -1) return dp[n][r];
  return dp[n][r] = bino(n-1,r-1)+bino(n-1,r);
}