//s의 접미사 배열과 LCP(Longest Common Prefix)
//SA: 어떤 문자열 S의 모든 접미사를 사전순으로 정렬해 둔 것
//LCP: SA[i]와 SA[i-1]를 인덱스로 가지는 S[i..] 와 S[j..]의 가장 긴 공통 접두사
//시간복잡도 - SA: O(N*logN*logN) LCP: O(N)
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Comparator{
  const vector<int>& group;
  int t;
  Comparator(const vector<int>& _group, int _t): group(_group), t(_t){}
  bool operator() (int a, int b){
    // 첫 t글자가 다르면 이들을 이용해 비교.
    if(group[a] != group[b])
      return group[a] < group[b];
    // S[a+t..]와 S[b+t..]의 첫 t글자를 비교.
    return group[a+t] < group[b+t];
  }
};

vector<int> getSuffixArray(const string& s){
  int n = s.size();
  int t = 1;
  // group[i] = 접미사들을 첫 t글자 기준으로 정렬했을 때, S[i..]가 들어가는 그룹 번호
  // t=1일 때에는 정렬할 것 없이 S[i..]의 첫 글자로 그룹 번호를 정해 줘도 같은 효과
  vector<int> group(n+1);
  for(int i=0;i<n;i++)
    group[i] = s[i];
  group[n] = -1;
  // 결과적으로 접미사 배열이 될 반환 값. 이 배열을 logN번 정렬
  vector<int> perm(n);
  for(int i=0;i<n;i++)
    perm[i] = i;
  while(t < n){
    Comparator compareUsing2T(group,t);
    sort(perm.begin(),perm.end(),compareUsing2T);
    t*=2;
    if(t>=n) break;
    // 2t글자를 기준으로 한 그룹 정보.
    vector<int> newGroup(n+1);
    newGroup[n] = -1;
    newGroup[perm[0]] = 0;
    for(int i=1;i<n;i++)
      if(compareUsing2T(perm[i-1],perm[i]))
        newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
      else
        newGroup[perm[i]] = newGroup[perm[i-1]];
      group = newGroup;
  }
  return perm;
}

// 접미사 배열내의 인접한 접미사와 비고.
// LCP[i] = SA[i]와 SA[i-1]를 인덱스로 가지는 S[i..] 와 S[j..]의 가장 긴 공통 접두사
// 전 len정보를 가지고 len 업데이트 이후 LCP[i]에 대입.
vector<int> getLCP(const string& s, vector<int> SA){
  int n = s.size();
  vector<int> LCP(n);
  vector<int> rank(n);
  for(int i=0;i<n;i++)
    rank[SA[i]]=i;
  int len = 0;
  for(int i=0;i<n;i++){
    if(rank[i]){
      int j = SA[rank[i]-1];
      while(s[j+len] == s[i+len]) len++;
      LCP[rank[i]] = len;
    }
    len = max(len-1,0);
  }
  return LCP;
}

int main(){
  string s;
  cin >> s;
  vector<int> SA = getSuffixArray(s);
  vector<int> LCP = getLCP(s,SA);
  for(int i=0;i<SA.size();i++)
    printf("%d ",SA[i]);
  printf("\nx ");
  for(int i=1;i<LCP.size();i++)
    printf("%d ",LCP[i]);
  printf("\n");
}
