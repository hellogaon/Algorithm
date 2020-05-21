// Hu_Shing : 행렬 곱셈 순서 O(NlgN) 알고리즘
// https://www.acmicpc.net/problem/18237
// http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/0211028.pdf
// http://www.cs.ust.hk/mjg_lib/bibs/DPSu/DPSu.Files/0213017.pdf
struct Arc{
  int u, v;
  int mn_idx, mn;
  ll mul, base_bunmo;
  ll bunja, bunmo;
  Arc(int _u, int _v, int _mn_idx, int _mn, ll _mul, ll _base_bunmo){
    u = _u;
    v = _v;
    mn_idx = _mn_idx;
    mn = _mn;
    mul = _mul;
    base_bunmo = _base_bunmo;
    bunmo = base_bunmo;
  }
  // C값 재계산
  void update_bunja(ll mn_poly_mul){
    bunja = mn * (bunmo + mul - mn_poly_mul);
  }
  ll S() const{
    return bunja/bunmo;
  }
  bool contains(Arc& o){
    return u <= o.u && o.v <= v;
  }
  bool operator < (const Arc& o)const{
    return S() < o.S();
  }
  bool operator <= (const Arc& o)const{
    return S() <= o.S();
  }
};

struct Hu_Shing{
  int N, root;
  vector<ll> w;
  vector<ll> CP;
  vector<Arc> arcs; // Potential h-arc
  vector<vector<int> > arcs_tree; // 각 arc의 child arc의 idx
  vector<vector<int> > connect; // 각 정점이 ceiling의 후보자들과 연결된 arc의 idx
  vector<priority_queue<Arc> > ceiling; // 각 arc에서의 ceiling 후보자

  Hu_Shing(vector<ll> &v){
    N = v.size();
    w = v;
  }

  void init(){
    CP.resize(N+1);
    arcs_tree.resize(N+1);
    ceiling.resize(N+1);
    connect.resize(N+1);
    // w1을 가장 작은 값으로 하여 rotate
    rotate(w.begin(), min_element(w.begin(), w.end()), w.end());
    w.pb(w[0]);
    // fan모양으로 펼쳐졌을 때의 값을 빠르게 구하기 위한 전처리
    for(int i=1;i<=N;i++){
      CP[i] += CP[i-1];
      CP[i] += w[i] * w[i-1];
    }
  }

  void add_Arc(int u, int v){
    int mn_idx = (w[u] < w[v]) ? u : v;
    ll mn = min(w[u], w[v]);
    ll mul = w[u] * w[v];
    ll base_bunmo = CP[v] - CP[u] - mul;
    arcs.pb(Arc(u, v, mn_idx, mn, mul, base_bunmo));
  }

  // Potential h-arc를 구하는 one sweep algorithm
  void one_sweep(){
    vector<int> st;
    for(int i=0;i<N;i++){
      while(st.size() >= 2 && w[st.back()] > w[i]){
        if(st[st.size() - 2]) add_Arc(st[st.size() - 2], i);
        st.pop_back();
      }
      st.pb(i);
    }
    add_Arc(0, N);
  }

  // w1-w1를 root로 하는 트리 생성
  void generate_tree(){
    int narc = arcs.size();
    root = narc - 1;
    stack<int> st;
    for(int i=0;i<narc;i++){
      Arc a = arcs[i];
      while(!st.empty() && a.contains(arcs[st.top()])){
        arcs_tree[i].pb(st.top());
        st.pop();
      }
      st.push(i);
    }
  }

  void add_arc(int idx){
    ceiling[idx].push(arcs[idx]);
    connect[arcs[idx].u].pb(idx);
		connect[arcs[idx].v].pb(idx);
  }

  void remove_arc(int idx){
    Arc arc = ceiling[idx].top();
    connect[arc.u].pop_back();
    connect[arc.v].pop_back();
    ceiling[idx].pop();
  }

  // (u:v)를 구할 때, 해당 polygon에서 min(u, v)쪽에 해당하는 한 변의 mul을 제거해 주어야하므로 이 값을 구해주는 함수
  ll mn_poly_mul(int idx){
    if(idx == root) return w[0] * (w[1] + w[N-1]);
    Arc arc = arcs[idx];
    if(arc.u == arc.mn_idx){
      if(connect[arc.u].empty() || !arc.contains(arcs[connect[arc.u].back()]))
        return w[arc.u] * w[arc.u+1];
      return arcs[connect[arc.u].back()].mul;
    }
    else{
      if(connect[arc.v].empty() || !arc.contains(arcs[connect[arc.v].back()]))
        return w[arc.v] * w[arc.v-1];
      return arcs[connect[arc.v].back()].mul;
    }
  }

  // 자식부터 값을 구해나가며 dfs 진행
  void dfs(int now){
    // leap 노드 일 경우,
    if(arcs_tree[now].empty()){
      arcs[now].update_bunja(mn_poly_mul(now));
      add_arc(now);
      return;
    }
    // dfs를 진행하며 S와 ceiling 후보자 업데이트
    for(int i=0;i<arcs_tree[now].size();i++){
      int nxt = arcs_tree[now][i];
      dfs(nxt);
      arcs[now].bunmo -= arcs[nxt].base_bunmo;
      while(!ceiling[nxt].empty()){
        ceiling[now].push(ceiling[nxt].top());
        ceiling[nxt].pop();
      }
    }
    arcs[now].update_bunja(mn_poly_mul(now));
    // 현재 arc가 negative일 경우, 아래 자손 모두 negative. remove 이후 S값 재계산
    while(!ceiling[now].empty() && arcs[now].mn <= ceiling[now].top().S()){
      arcs[now].bunmo += ceiling[now].top().bunmo;
      remove_arc(now);
      arcs[now].update_bunja(mn_poly_mul(now));
    }
    // 현재 arc의 child가 son 관계일 경우 remove하여 ceiling 후보자에서 제외
    // S(hi/hj) = a/b, S(hj/hk) = c/d 일 때, S(hi/hk) = (a+c)/(b+d)
    while(!ceiling[now].empty() && arcs[now] <= ceiling[now].top()){
      arcs[now].bunja += ceiling[now].top().bunja;
      arcs[now].bunmo += ceiling[now].top().bunmo;
      remove_arc(now);
    }
    add_arc(now);
  }

  ll get_ans(){
    ll ans = 0;
    while(!ceiling[root].empty()){
      ans += ceiling[root].top().bunja;
      ceiling[root].pop();
    }
    return ans;
  }

  ll solve(){
    init();
    one_sweep();
    generate_tree();
    dfs(root);
    return get_ans();
  }
};