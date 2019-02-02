//크루스칼: O(ElgE)
const int MAXV = 501;

int V,E;
vector<pii> adj[MAXV];

struct DS{
  vector<int> par, rank;
  DS(int n) : par(n), rank(n,1){
    for(int i=0;i<n;i++)
      par[i]=i;
  }
  int find(int u){
    if(u == par[u]) return u;
    return par[u] = find(par[u]);
  }
  void merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v) return;
    if(rank[u] > rank[v]) swap(u,v);
    par[u] = v;
    if(rank[u] == rank[v]) ++rank[v];
  }
};

int kruskal(vector<pii>& edges){
  int ret = 0;
  edges.clear();
  vector<pair<int,pii> > e;
  for(int u=0;u<V;u++){
    for(int i=0;i<adj[u].size();i++){
      int v = adj[u][i].first, cost = adj[u][i].second;
      e.pb(mp(cost, mp(u,v)));
    }
  }
  sort(e.begin(),e.end());
  DS sets(V);
  for(int i=0;i<e.size();i++){
    int cost = e[i].first;
    int u = e[i].second.first, v = e[i].second.second;
    if(sets.find(u)==sets.find(v)) continue;
    sets.merge(u,v);
    edges.pb(mp(u,v));
    ret += cost;
  }
  return ret;
}

int main(){
  scanf("%d %d",&V,&E);
  for(int i=0;i<E;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    adj[A-1].pb(mp(B-1,C));
  }
  vector<pii> edges;
  printf("%d\n",kruskal(edges)); 
}
