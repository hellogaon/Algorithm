//최소 편집 거리 알고리즘 Minimum Edit Distance
// dp(i,j) = dp(i-1,j-1) (s1[i]==s2[i])
//         = min(min(dp(i,j-1)+1,dp(i-1,j)+1),dp(i-1,j-1)+1) (s1[i]!=s2[i])
int dp[1001][1001];

int main(){
  string s,t;
  cin >> s >> t;
  for(int i=0;i<=s.size();i++)
    dp[i][0] = i;
  for(int j=0;j<=t.size();j++)
    dp[0][j] = j;
  for(int i=1;i<=s.size();i++){
    for(int j=1;j<=t.size();j++){
      if(s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1];
      else dp[i][j] =min(min(dp[i][j-1]+1, dp[i-1][j]+1), dp[i-1][j-1]+1);
    }
  }
  printf("%d\n",dp[s.size()][t.size()]);
}