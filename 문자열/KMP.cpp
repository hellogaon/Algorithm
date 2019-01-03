//pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getpi(string& N){
  int n = N.size();
  vector<int> pi(n,0);
  int match = 0;
  for(int i=1;i<n;i++){
    while(match > 0 && N[i] != N[match])
      match = pi[match-1];
    if(N[i] == N[match]){
      match++;
      pi[i] = match;
    }
  }
  return pi;
}

//M의 부분문자열로 N이 출현하는 시작 위치들을 모두 반환
vector<int> kmp(string& M, string& N){
  int m = M.size(), n = N.size();
  vector<int> ret;
  vector<int> pi = getpi(N);
  int match = 0;
  for(int i=0;i<m;i++){
    while(match > 0 && M[i] != N[match])
      match = pi[match-1];
    if(M[i] == N[match]){
      match++;
      if(match == n){
        ret.pb(i-n+1);
        match = pi[match-1];
      }
    }
  }
  return ret;
}