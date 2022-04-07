//벨만포드: O(VE)
const int MAXV = 501;

int V,E;
vector<pii> adj[MAXV];

vector<int> bf(int src){
  vector<int> dist(MAXV,INF);
  dist[src] = 0;
  for(int iter=1;iter<=V;iter++){
    bool update = false;
    for(int i=1;i<=V;i++){
      for(auto p: adj[i]){
        int nxt = p.first, cost = p.second;
        if(dist[i] != INF && dist[nxt] > dist[i] + cost){
          update = true;
          dist[nxt] = dist[i] + cost;
        }
      }
    }
    if(!update) break;
    if(iter == V && update) dist.clear();
  }
  return dist;
}