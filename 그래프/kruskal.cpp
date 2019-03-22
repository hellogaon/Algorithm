//크루스칼: O(ElgE)
const int MAXV = 1001;

int V,E;
vector<pii> adj[MAXV];

ll kruskal(){
  ll ret = 0;
  vector<pii> edges;
  vector<pair<int,pii> > e;
  for(int i=1;i<=V;i++){
    for(auto p: adj[i]){
      int next = p.first, cost = p.second;
      e.pb(mp(cost,mp(i,next)));
    }
  }
  sort(e.begin(),e.end());
  DS ds(V+1);
  for(int i=0;i<e.size();i++){
    int cost = e[i].first;
    int u = e[i].second.first, v = e[i].second.second;
    if(ds.find(u) == ds.find(v)) continue;
    ds.merge(u,v);
    edges.pb(mp(u,v));
    ret += cost;
  }
  return ret;
}