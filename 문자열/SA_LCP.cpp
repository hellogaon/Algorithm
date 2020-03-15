//SA: O(N*logN*logN) LCP: O(N)
struct Comparator{
  const vector<int>& g;
  int t;
  Comparator(const vector<int>& _g, int _t): g(_g), t(_t){}
  bool operator() (int a, int b){
    if(g[a] != g[b]) return g[a] < g[b];
    return g[a+t] < g[b+t];
  }
};

//SA: 어떤 문자열 S의 모든 접미사를 사전순으로 정렬해 둔 것
vector<int> getSA(string& s){
  int n = s.size(), t = 1;
  vector<int> g(n+1), p(n);
  for(int i=0;i<n;i++) g[i] = s[i];
  g[n] = -1;
  for(int i=0;i<n;i++) p[i] = i;
  while(t < n){
    Comparator cmp(g, t);
    sort(p.begin(), p.end(), cmp);
    t*=2;
    if(t>=n) break;
    vector<int> ng(n+1);
    ng[n] = -1; ng[p[0]] = 0;
    for(int i=1;i<n;i++)
      if(cmp(p[i-1], p[i]))
        ng[p[i]] = ng[p[i-1]] + 1;
      else
        ng[p[i]] = ng[p[i-1]];
      g = ng;
  }
  return p;
}

//LCP: SA[i]와 SA[i-1]를 인덱스로 가지는 S[i..] 와 S[j..]의 가장 긴 공통 접두사
vector<int> getLCP(string& s, vector<int> SA){
  int n = s.size(), len = 0;
  vector<int> LCP(n),rank(n);
  for(int i=0;i<n;i++) rank[SA[i]]=i;
  for(int i=0;i<n;i++){
    if(rank[i]){
      int j = SA[rank[i]-1];
      while(s[j+len] == s[i+len]) len++;
      LCP[rank[i]] = len;
    }
    len = max(len-1, 0);
  }
  return LCP;
}