//다익스트라: O(ElgV)
const int MAXV = 10001;

vector<pii> adj[MAXV];
vector<int> par(MAXV,-1);

vector<ll> dij(int src){
  vector<ll> dist(MAXV, INF);
  dist[src] = 0;
  priority_queue<pair<ll,int> > pq;
  pq.push(mp(0, src));
  while(!pq.empty()){
    int cost = -pq.top().first, here = pq.top().second;
    pq.pop();
    if(dist[here] < cost) continue;
    for(auto p: adj[here]){
      int there = p.first, nextCost = cost + p.second;
      if(nextCost < dist[there]){
        dist[there] = nextCost;
        par[there] = here;
        pq.push(mp(-nextCost, there));
      }
    }
  }
  return dist;
}

vector<int> getpath(int v){
  vector<int> path(1, v);
  while(par[v] != -1){
    v = par[v];
    path.pb(v);
  }
  reverse(path.begin(), path.end());
  return path;
}
