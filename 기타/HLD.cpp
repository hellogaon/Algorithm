//Heavy-Light Decomposition
//트리에서 세그먼트 트리를 사용하기 위하여 트리를 여러 개의 그룹으로 나누기 위한 과정
//무거운 간선을 타고 내려간다면 u에서 v로 가는 경로에서 최대 O(lgN)개의 그룹을 마주치게 된다.
//트리의 간선의 가중치의 값이 바뀔 때 - O(lgN)
//트리의 두 정점이 주어질 때 두 정점 사이의 경로 상에서 합, 최대 가중치 등을 구할 때 - O((lgN)^2)
const int MAXN = 100005;

struct HLD{
  int dn;
  vector<pii> adj[MAXN];
  //원래 정점 번호로 참조
  int par[MAXN], sub[MAXN], lv[MAXN], dfsn[MAXN];
  //새 정점 번호로 참조하여 원래 정점 번호를 반환
  int chain[MAXN], tail[MAXN];
  SegTree ST;

  void init(int root){
    dn = 0;
    dfs1(root,-1);
    memset(chain,-1,sizeof(chain));
    memset(tail,-1,sizeof(tail));
    dfs2(root,-1,root);
    vector<ll> a(MAXN);
    for(int i=1;i<MAXN;i++){
      for(auto &t: adj[i]){
        int next = t.first, w = t.second;
        int v = dfsn[next];
        if(lv[i] < lv[next])
          a[v] = w;
      }
    }
    ST = SegTree(a);
  }
  
  // 첫 번째 DFS: 각 정점의 서브트리 크기 구하기
  void dfs1(int x, int p){
    par[x] = p; sub[x] = 1;
    for(auto &t: adj[x]){
      int next = t.first;
      if(next != p){
        lv[next] = lv[x] + 1;
        dfs1(next, x);
        sub[x] += sub[next];
      }
    }
  }
  
  // 두 번째 DFS: 각 간선을 그룹별로 분류
  void dfs2(int x, int p, int cn){
    dfsn[x] = dn;
    chain[dn] = cn;
    tail[cn] = dn++;
    int idx = -1;
    for(auto &t: adj[x]){
      int next = t.first;
      if(next != p && (idx == -1 || sub[next] > sub[idx]))
        idx = next;
    }
    if(idx != -1) dfs2(idx, x, cn);
    for(auto &t: adj[x]){
      int next = t.first;
      if(next != p && next != idx)
        dfs2(next, x, next);
    }
  }

  //u와 v를 잇는 간선의 가중치를 k로 바꿈
  void update(int u, int v, int k){
    if(lv[u] < lv[v]) swap(u, v);
    ST.update(dfsn[u],k);
  }

  //u정점과 v정점의 경로 상에서의 최대 가중치를 반환
  ll query(int u, int v){
    ll ret = -INF;
    u = dfsn[u], v = dfsn[v];
    while(chain[u] != chain[v]){
      int uHead = chain[u], vHead = chain[v];
      if(lv[uHead] > lv[vHead]){
        ret = max(ret, ST.query(dfsn[uHead], u));
        u = dfsn[par[uHead]];
      }
      else{
        ret = max(ret, ST.query(dfsn[vHead], v));
        v = dfsn[par[vHead]];
      }
    }
    ret = max(ret, ST.query(min(u, v)+1, max(u, v)));
    return ret;
  }
};