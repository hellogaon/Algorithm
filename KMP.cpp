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
  int begin = 1, matched = 0;
  while(begin + matched < n){
    if(N[begin + matched] == N[matched]){
      matched++;
      pi[begin+matched-1] = matched;
    }
    else{
      if(matched == 0)
        begin++;
      else{
        begin += matched - pi[matched-1];
        matched = pi[matched-1];
      }
    }
  }
  return pi;
}

//H의 부분문자열로 N이 출현하는 시작 위치들을 모두 반환
vector<int> kmpSearch(string& M, string& N){
  int m = M.size(), n = N.size();
  vector<int> ret;
  vector<int> pi = getPartialMatch(N);
  int begin = 0, matched = 0;
  while(begin <= m-n){
    if(matched < n && M[begin+matched] == N[matched]){
      matched++;
      if(matched==n) ret.push_back(begin);
    }
    else{
      if(matched == 0)
        begin++;
      else{
        begin += matched - pi[matched-1];
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
