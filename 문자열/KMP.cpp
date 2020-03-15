//pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getpi(string& N){
  int n = N.size();
  vector<int> pi(n, 0);
  for(int i=1,j=0;i<n;i++){
    while(j > 0 && N[i] != N[j]) j = pi[j-1];
    if(N[i] == N[j]) pi[i] = ++j;
  }
  return pi;
}

//M의 부분문자열로 N이 출현하는 시작 위치들을 모두 반환
vector<int> kmp(string& M, string& N){
  int m = M.size(), n = N.size();
  vector<int> ret, pi = getpi(N);
  for(int i=0,j=0;i<m;i++){
    while(j > 0 && M[i] != N[j]) j = pi[j-1];
    if(M[i] == N[j]){
      ++j;
      if(j == n){
        ret.pb(i-n+1); j = pi[j-1];
      }
    }
  }
  return ret;
}