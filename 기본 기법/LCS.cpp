// LCS - 최장 공통 부분열 Longest Common Subsequence
// LCS(i,j) = LCS(i-1,j-1)+1 (s1[i]==s2[j])
//            max(LCS(i-1,j),LCS(i,j-1)) (s1[i]!=s2[j])
// LCS 뒤에서부터 보면서 출력
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int dp[1001][1001];
string s1,s2,ans;

string backTracking(int i, int j){
  if(i==0||j==0) return "";
  if(s1[i-1]==s2[j-1])
    return backTracking(i-1,j-1) + s1[i-1];
  else{
    if(dp[i][j-1] > dp[i-1][j])
      return backTracking(i,j-1);
    else
      return backTracking(i-1,j);
  }
}

int main(){
  cin >> s1 >> s2;
  for(int i=1;i<=s1.size();i++){
    for(int j=1;j<=s2.size();j++){
      if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
      else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
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
  printf("%s\n",ans.c_str()); // LCS출력 반복문 버전
  printf("%s\n",backTracking(s1.size(),s2.size()).c_str()); //LCS출력 재귀함수 버전
}
