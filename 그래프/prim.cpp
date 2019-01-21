//프림: O(ElgV)
const int MAXN = 1001;

int V,E;
vector<pii> adj[MAXN];

int prim(vector<pii>& edges){
  edges.clear();
  vector<bool> added(V,false);
  vector<int> par(V,-1);
  priority_queue<pii> pq;
  int ret = 0;
  pq.push(mp(0,0));
  par[0] = 0;
  while(!pq.empty()){
    int cost = -pq.top().first, u = pq.top().second;
    pq.pop();
    if(added[u]) continue;
    if(par[u] != u)
      edges.pb(mp(par[u],u));
    ret += cost;
    added[u] = true;
    for(int i=0;i<adj[u].size();i++){
      int v = adj[u][i].first, weight = adj[u][i].second;
      if(!added[v]){
        par[v] = u;
        pq.push(mp(-weight,v));
      }
    }
  }
  return ret;
}

int main(){
  scanf("%d %d",&V,&E);
  for(int i=0;i<E;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    adj[A-1].pb(mp(B-1,C));
    adj[B-1].pb(mp(A-1,C));
  }
  vector<pii> edges;
  printf("%d\n",prim(edges));
}
