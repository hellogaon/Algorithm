// Offline dynamic connectivity : O(Qlg^2Q)
// 1) 정점 u, v를 잇는 간선 추가
// 2) 정점 u, v를 잇는 간선 제거
// 3) 그래프 상에서 두 정점이 연결되어 있는 지 체크
// 위와 같은 질의가 주어졌을 때 이러한 질의를 빠르게 응답하는 방법을 찾는 문제

//간선의 lifetime을 계산한 뒤, 분할정복을 이용하여 계산
// https://koosaga.com/121
// https://www.acmicpc.net/problem/16911
const int MAXN = 100005;
const int MAXQ = 100005;

struct Query{
  int t, a, b;
  Query() {}
  Query(int _t, int _a, int _b){
    t = _t; a = _a; b = _b;
  }
};

struct Edge{
  int u, v, s, e;
  Edge() {}
  Edge(int _u, int _v, int _s, int _e){
    u = _u, v = _v, s = _s, e = _e;
  }
};

struct DS{
  vector<int> par, rank;
  stack<pair<pii, bool> > st;
  DS(int n) : par(n), rank(n, 1){
    for(int i=0;i<n;i++)
      par[i] = i;
  }
  int find(int u){
    if(u == par[u]) return u;
    return find(par[u]);
  }
  int merge(int u, int v){
    u = find(u), v = find(v);
    if(u == v) return 0;
    if(rank[u] < rank[v]) swap(u, v);
    par[v] = u;
    st.push(mp(mp(u, v), (rank[u] == rank[v]) ? true : false));
    if(rank[u] == rank[v]) rank[u]++;
    return 1;
  }
  void rollback(int cnt){
    while(cnt--){
      pair<pii, bool> p = st.top(); st.pop();
      int u = p.first.first, v = p.first.second;
      bool chk = p.second;
      if(chk) rank[u]--;
      par[v] = v;
    }
  }
};

int N,Q;
map<pii,int> ed_m;
vector<Edge> ed;
DS ds(MAXN);
Query q[MAXQ];

void solve(int s, int e, vector<Edge>& edges){
  int cnt = 0;
  int mid = (s+e)/2;
  vector<Edge> s_edges, e_edges;
  for(int i=0;i<edges.size();i++){
    if(edges[i].s <= s && e <= edges[i].e)
      cnt += ds.merge(edges[i].u, edges[i].v);
    else{
      if(edges[i].s <= mid) s_edges.pb(edges[i]);
      if(mid+1 <= edges[i].e) e_edges.pb(edges[i]);
    }
  }
  if(s == e && q[s].t == 3)
    cout << (ds.find(q[s].a) == ds.find(q[s].b)) << '\n';
  if(s < e){
    solve(s, mid, s_edges);
    solve(mid+1, e, e_edges);
  }
  ds.rollback(cnt);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> Q;
  for(int i=0;i<Q;i++){
    int T,A,B;
    cin >> T >> A >> B;
    if(A > B) swap(A,B);
    q[i] = Query(T,A,B);
    if(T == 1) ed_m[mp(A,B)] = i;
    else if(T == 2){
      int s = ed_m[mp(A,B)];
      int e = i;
      ed.pb(Edge(A, B, s, e));
      ed_m.erase(mp(A,B));
    }
  }
  for(auto iter=ed_m.begin();iter!=ed_m.end();iter++){
    pii p = iter->first;
    int s = iter->second;
    int e = Q;
    ed.pb(Edge(p.first, p.second, s, e));
  }
  solve(0, Q, ed);
}