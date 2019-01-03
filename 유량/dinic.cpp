//디닉: O(V^2E)
const int MAXN = 1005;
const int S = MAXN-2;
const int E = MAXN-1;

struct Edge{
  int t,c,f;
  Edge* rev;
  int r() const { return c - f; }
  void push(int amt){
    f += amt;
    rev->f -= amt;
  }
};

int level[MAXN], work[MAXN];
vector<Edge*> adj[MAXN];

void addEdge(int u, int v, int c){
  Edge* uv = new Edge(), *vu = new Edge();
  uv->t = v; uv->c = c; uv->f = 0; uv->rev = vu;
  vu->t = u; vu->c = 0; vu->f = 0; vu->rev = uv;
  adj[u].pb(uv);
  adj[v].pb(vu);
}

bool bfs(){
  memset(level,-1,sizeof(level));
  level[S] = 0;
  queue<int> q;
  q.push(S);
  while(!q.empty()){
    int here = q.front(); q.pop();
    for(int i=0;i<adj[here].size();i++){
      Edge* e = adj[here][i];
      int there = e->t;
      if(e->r() > 0 && level[there] == -1){
        q.push(there);
        level[there] = level[here] + 1;
      }
    }
  }
  return level[E] != -1;
}

int dfs(int here, int sink, int flow){
  if(here == sink) return flow;
  for(int &i=work[here];i<adj[here].size();i++){
    Edge* e = adj[here][i];
    int there = e->t;
    if(e->r() > 0 && level[there] == level[here]+1){
      int sz = dfs(there,sink,min(e->r(),flow));
      if(sz > 0){
        e->push(sz);
        return sz;
      }
    }
  }
  return 0;
}

int solve(int s, int e){
  int ret = 0;
  while(bfs()){
    memset(work,0,sizeof(work));
    while(1){
      int flow = dfs(S,E,INF);
      if(flow == 0) break;
      ret += flow;
    }
  }
  return ret;
}

void add_LR_edge(int u, int v, int l, int r){
  lsum += l;
  addEdge(u+2,v+2,r-l);
  addEdge(NEW_S,v+2,l);
  addEdge(u+2,NEW_E,l);
}

lsum = 0;
int solveLR(int s, int e){
  addEdge(e+2,s+2,INF);
  int ret = 0;
  while(bfs()){
    memset(work,0,sizeof(work));
    while(1){
      int flow = dfs(NEW_S,NEW_E,INF);
      if(flow == 0) break;
      ret += flow;
    }
  }
  return ret;
}