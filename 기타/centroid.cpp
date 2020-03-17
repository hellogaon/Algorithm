// centroid decomposition
// N개의 노드를 가지는 트리에서 특정 노드 v를 지웠을 때,
// 나눠지는 subtree가 모두 N/2이하라면 v를 트리의 centroid라 칭함.

// centroid tree
// 트리의 모든 경로를 표현 가능
// centroid tree에서의 u -> lca(u, v) -> v는 원래 트리에도 존재하는 경로
// 높이는 lgN
const int MAXN = 100005;

vector<int> siz(MAXN);
vector<bool> visit(MAXN);
vector<pii> adj[MAXN];
vector<int> cent_tree[MAXN];

int get_size(int u, int par){
  siz[u] = 1;
  for(pii p: adj[u]){
    int v = p.first, cost = p.second;
    if(v == par || visit[v]) continue;
    siz[u] += get_size(v, u);
  }
  return siz[u];
}

int get_cent(int u, int par, int cap){
  for(pii p: adj[u]){
    int v = p.first, cost = p.second;
    if(v == par || visit[v]) continue;
    if(siz[v] > cap) return get_cent(v, u, cap);
  }
  return u;
}

int make_cent(int u){
  int cap = get_size(u, -1) / 2;
  int cent = get_cent(u, -1, cap);
  visit[cent] = true;
  for(pii p: adj[cent]){
    int v = p.first, cost = p.second;
    if(visit[v]) continue;
    int nxt_cent = make_cent(v);
    cent_tree[cent].pb(nxt_cent);
  }
  return cent;
}

void travel_cent(int u){
  visit[u] = true;

  //conquer
  for(pii p: adj[u]){
    int v = p.first, cost = p.second;
    if(visit[v]) continue;
    
  }

  //divide
  for(int v: cent_tree[u])
    travel_cent(v);
}

int cent = make_cent(1);
fill(visit.begin(), visit.end(), false);
travel_cent(cent);