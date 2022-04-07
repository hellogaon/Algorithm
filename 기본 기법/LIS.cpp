// LIS : O(NlogN)
// LIS의 마지막 값이 추가하는 배열의 값보다 작으면 추가.
// 그렇지 않으면 추가하는 배열의 값보다 큰 수 중 가장 작은 수와 교체.
// path[i] = LIS에서 i가 몇번 째에 있었는 지.
int LIS(vector<int>& v){
  vector<int> lis;
  for(int i=0;i<v.size();i++){
    auto it = lower_bound(lis.begin(), lis.end(), v[i]);
    if(it == lis.end()) lis.pb(v[i]);
    else *it = v[i];
  }
  return (int)lis.size();
}

pair<int, vector<int> > LIS_with_path(vector<int>& v){
  int n = v.size();
  vector<int> lis;
  vector<int> p(n);
  for(int i=0;i<n;i++){
    auto it = lower_bound(lis.begin(), lis.end(), v[i]);
    p[i] = (int)(it-lis.begin())+1;
    if(it == lis.end()) lis.pb(v[i]);
    else *it = v[i];
  }  

  int LIS = (int)lis.size();

  stack<int> s;
  int idx = n-1;
  for(int i=LIS;i>0;idx--){
    if(p[idx] == i){
      s.push(v[idx]); i--;
    }
  }
  vector<int> path;
  while(!s.empty()){
    path.pb(s.top());
    s.pop();
  }
  
  return mp(LIS, path);
}

// pair LIS
// 두 순서쌍에 대해 (a,b) < (c,d)가 a < c && b < d라 정의할 떄,
// 순서쌍 열에 대해 LIS를 구함
struct PairSet{
  set<pii> s;
  bool operator <(const pii& p) const{
    auto it = s.lower_bound(p);
    return it != s.begin() && (--it)->snd < p.snd;
  }
  void add(const pii& p){
    auto it = ++s.insert(p).fst;
    while(it != s.end() && p.snd < it->snd) it = s.erase(it);
  }
};
int pair_LIS(vector<pii>& v){
  vector<PairSet> lis;
  for(int i=0;i<v.size();i++){
    auto it = lower_bound(lis.begin(), lis.end(), v[i]);
    if(it == lis.end()) lis.pb({{ v[i] }});
    else it->add(v[i]);
  }
  return (int)lis.size();
}

