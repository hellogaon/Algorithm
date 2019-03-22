//다익스트라: O(ElgV)
const int MAXV = 10001;

int V,E,K;
vector<pii> adj[MAXV];

vector<int> dij(int src){
  vector<int> dist(MAXV,INF);
  dist[src] = 0;
  priority_queue<pair<ll,int> > pq;
  pq.push(mp(0,src));
  while(!pq.empty()){
    int cost = -pq.top().first, here = pq.top().second;
    pq.pop();
    if(dist[here] < cost) continue;
    for(auto p: adj[here]){
      int there = p.first, nextCost = cost + p.second;
      if(nextCost < dist[there]){
        dist[there] = nextCost;
        pq.push(mp(-nextCost,there));
      }
    }
  }
  return dist;
}