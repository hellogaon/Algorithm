const int MAXN = 100001, MAXC = 18;

int par[MAXN][MAXC],d[MAXN];
bool visited[MAXN];
vector<int> t[MAXN];

void dfs(int here){
  visited[here]=true;
  for(int i=0;i<t[here].size();i++){
    int next = t[here][i];
    if(visited[next]) continue;
    par[next][0] = here;
    d[next] = d[here]+1;
    dfs(next);
  }
}

int lca(int u, int v){
  if(d[u]<d[v]) swap(u,v);
  for(int i=MAXC-1;i>=0;i--)
    if(d[u]-d[v] >= (1<<i))
      u = par[u][i];
  if(u == v) return u;
  for(int i=MAXC-1;i>=0;i--)
    if(par[u][i]!=par[v][i])
      u = par[u][i], v = par[v][i];
  return par[u][0];
}

int main(){
  int N,M;
  scanf("%d",&N);
  for(int i=1;i<N;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    t[u].pb(v);
    t[v].pb(u);
  }
  dfs(1);
  for(int j=0;j<MAXC-1;j++)
    for(int i=2;i<=N;i++)
      par[i][j+1]=par[par[i][j]][j];
  scanf("%d",&M);
  for(int i=0;i<M;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    printf("%d\n",lca(u,v));
  }
}
