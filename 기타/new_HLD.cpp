//Heavy-Light Decomposition
//트리에서 세그먼트 트리를 사용하기 위하여 트리를 여러 개의 그룹으로 나누기 위한 과정
//무거운 간선을 타고 내려간다면 u에서 v로 가는 경로에서 최대 O(lgN)개의 그룹을 마주치게 된다.
//트리의 간선의 가중치의 값이 바뀔 때 - O(lgN)
//트리의 두 정점이 주어질 때 두 정점 사이의 경로 상에서 합, 최대 가중치 등을 구할 때 - O((lgN)^2)
const int MAXN = 100005;

struct HLD{
  SegTree ST;
  // v의 부모가 u고 이떄의 간선의 비용이 e일 때
  // adj[u] = mp(v, e), adj[v] = mp(u, e)
  // tadj[u]: u의 자식들만 연결. tadj[u][0]에는 가장 무거운 간선을 타고 내려갔을 때의 정보가 들어있음.
  vector<pii> adj[MAXN];
  vector<pii> tadj[MAXN];
  // in[v]: 새 정점 번호를 반환
  // top[v]: v가 포함되는 heavy path의 가장 위 정점
  // top[v]부터 v까지의 경로는 in[top[v]] 부터 in[v]까지 대응
  ll a[MAXN];
  int t, lv[MAXN], par[MAXN], sz[MAXN], in[MAXN], top[MAXN];

  void init(int root){
    top[root] = 1;
    dfs_adj(root, -1);
    dfs_sz(root);
    dfs_hld(root);
    ST = SegTree(a,t);
  }

  void dfs_adj(int u, int parent){
    for(auto &p: adj[u]){
      int &v = p.first;
      if(v == parent) continue;
      tadj[u].pb(p);
      dfs_adj(v, u);
    }
  }
  
  void dfs_sz(int u){
    sz[u] = 1;
    for(auto &p: tadj[u]){
      int &v = p.first;
      dfs_sz(v);
      sz[u] += sz[v];
      if(sz[v] > sz[tadj[u][0].first]) swap(p, tadj[u][0]);
    }
  }

  void dfs_hld(int u){
    in[u] = t++;
    for(auto &p: tadj[u]){
      int &v = p.first, d = p.second;
      par[v] = u;
      lv[v] = lv[u] + 1;
      top[v] = (v == tadj[u][0].first ? top[u] : v); dfs_hld(v);
      a[in[v]] = d;
    }
  }
  
  //u와 v를 잇는 간선의 가중치를 k로 바꿈
  void update(int u, int v, int k){
    if(lv[u] < lv[v]) swap(u, v);
    ST.update(in[u],k);
  }

  // //u정점과 v정점의 경로 상에서의 최대 가중치를 반환
  ll query(int u, int v){
    ll ret = -INF;
    // 서로 다른 그룹에 속해 있을 경우 깊은 쪽부터 참조
    while(top[u] != top[v]){
      int uTop = top[u], vTop = top[v];
      if(lv[uTop] > lv[vTop]){
        ret = max(ret, ST.query(in[uTop], in[u]));
        u = par[uTop];
      }
      else{
        ret = max(ret, ST.query(in[vTop], in[v]));
        v = par[vTop];
      }
    }
    // u와 v가 동시에 속한 마지막 그룹 내 구간 연산
    ret = max(ret, ST.query(min(in[u], in[v])+1, max(in[u], in[v])));
    return ret;
  }
};
