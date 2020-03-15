//디닉: min(O(Ef),O(V^2E))
const int MAXV = 1005;
const int S = MAXV-2;
const int E = MAXV-1;

struct Edge{
  int t,c,f;
  Edge* rev;
  int r() const { return c - f; }
  void push(int amt){
    f += amt;
    rev->f -= amt;
  }
};

int level[MAXV], work[MAXV];
vector<Edge*> adj[MAXV];

void addEdge(int u, int v, int c){
  Edge* uv = new Edge(), *vu = new Edge();
  uv->t = v; uv->c = c; uv->f = 0; uv->rev = vu;
  vu->t = u; vu->c = 0; vu->f = 0; vu->rev = uv;
  adj[u].pb(uv);
  adj[v].pb(vu);
}

bool bfs(int s, int e){
  memset(level,-1,sizeof(level));
  level[s] = 0;
  queue<int> q;
  q.push(s);
  while(!q.empty()){
    int here = q.front(); q.pop();
    for(auto ed: adj[here]){
      int there = ed->t;
      if(ed->r() > 0 && level[there] == -1){
        q.push(there);
        level[there] = level[here] + 1;
      }
    }
  }
  return level[e] != -1;
}

int dfs(int here, int sink, int flow){
  if(here == sink) return flow;
  for(int &i=work[here];i<adj[here].size();i++){
    Edge* e = adj[here][i];
    int there = e->t;
    if(e->r() > 0 && level[there] == level[here]+1){
      int sz = dfs(there, sink, min(e->r(), flow));
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
  while(bfs(s,e)){
    memset(work,0,sizeof(work));
    while(1){
      int flow = dfs(s, e, INF);
      if(flow == 0) break;
      ret += flow;
    }
  }
  return ret;
}

const int NEW_S = MAXV-4;
const int NEW_E = MAXV-3;
int lsum;

void add_LR_edge(int u, int v, int l, int r){
  lsum += l;
  addEdge(u, v, r-l);
  addEdge(NEW_S, v, l);
  addEdge(u, NEW_E, l);
}

bool solveLR(int s, int e){
  addEdge(e, s, INF);
  return lsum == solve(NEW_S, NEW_E);
}