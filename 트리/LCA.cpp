const int MAXN = 100001;
const int MAXH = 18;

vector<int> adj[MAXN];
int N,par[MAXN][MAXH],d[MAXN];

void dfs(int x, int p){
  for(int nxt: adj[x]){
    if(nxt == p) continue;
    d[nxt] = d[x] + 1;
    par[nxt][0] = x;
    dfs(nxt, x);
  }
}

void init(){
  for(int j=1;j<MAXH;j++)
    for(int i=1;i<=N;i++)
      par[i][j] = par[par[i][j-1]][j-1];
}

int LCA(int u, int v){
  if(d[u] < d[v]) swap(u, v);
  int diff = d[u]-d[v];
  for(int i=0;i<MAXH;i++)
    if(diff & (1<<i)) u = par[u][i];
  if(u == v) return u;
  for(int i=MAXH-1;i>=0;i--){
    if(par[u][i] != par[v][i]){
      u = par[u][i]; v = par[v][i];
    }
  }
  return par[u][0];
}

int getDist(int u, int v){
  int lca = LCA(u, v);
  return d[u] + d[v] - 2 * d[lca];
}

dfs(root, 0);
init();