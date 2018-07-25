//KMP - 문자열 검색 알고리즘
//시간복잡도 - O(H + N)
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//N에서 자기자신을 찾으면서 나타내는 부분일치를 이용해 pi계산
//pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatch(string& N){
  int n = N.size();
  vector<int> pi(n,0);
  int matched = 0;
  for(int i=1;i<n;i++){
    while(matched > 0 && N[i] != N[matched])
      matched = pi[matched-1];
    if(N[i] == N[matched]){
      matched++;
      pi[i] = matched;
    }
  }
  return pi;
}

//M의 부분문자열로 N이 출현하는 시작 위치들을 모두 반환
vector<int> kmpSearch(string& M, string& N){
  int m = M.size(), n = N.size();
  vector<int> ret;
  vector<int> pi = getPartialMatch(N);
  int matched = 0;
  for(int i=0;i<m;i++){
    while(matched > 0 && M[i] != N[matched])
      matched = pi[matched-1];
    if(M[i] == N[matched]){
      matched++;
      if(matched == n){
        ret.push_back(i-n+1);
        matched = pi[matched-1];
      }
    }
  }
  return ret;
}

int main(){
  string M,N;
  getline(cin,M);
  getline(cin,N);
  vector<int> ans = kmpSearch(M,N);
  printf("%lu\n",ans.size());
  for(int i=0;i<ans.size();i++){
    printf("%d\n",ans[i]);
  }
}
