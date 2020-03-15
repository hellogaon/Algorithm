// LCS:최장 공통 부분열
// LCS(i,j) = LCS(i-1,j-1)+1 (s1[i]==s2[j])
//            max(LCS(i-1,j),LCS(i,j-1)) (s1[i]!=s2[j])
const int MAXN = 1001;

int dp[MAXN][MAXN];
string s1,s2,ans;

int main(){
  cin >> s1 >> s2;
  for(int i=1;i<=s1.size();i++){
    for(int j=1;j<=s2.size();j++){
      if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
      else dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
    }
  }
  printf("%d\n",dp[s1.size()][s2.size()]);

  int idx = dp[s1.size()][s2.size()];
  for(int i=s1.size();i>0;i--){
    for(int j=s2.size();j>0;j--){
      if(s1[i-1]==s2[j-1] && idx==dp[i][j]){
        ans=s1[i-1]+ans;
        idx--; i--;
      }
    }
  }
  printf("%s\n",ans.c_str());
}
