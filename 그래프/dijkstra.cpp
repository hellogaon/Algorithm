//다익스트라: O(ElgV)
//딘일 시작점 최단 경로 알고리즘 시작 정점 s에서부터 다른 정점까지의 최단거리
//모든 거리의 비용이 음수가 아닐 경우
const int MAXN = 501;

int V,E;
vector<pii> adj[MAXN];
vector<int> par(MAXN,-1);

vector<int> dijkstra(int src){
  vector<int> dist(V+1,INF);
  dist[src]=0;
  priority_queue<pii> pq;
  pq.push(mp(0,src));
  while(!pq.empty()){
    int cost = -pq.top().first, here = pq.top().second;
    pq.pop();
    if(dist[here]<cost) continue;
    for(int i=0;i<adj[here].size();i++){
      int there = adj[here][i].first;
      int nextDist = cost + adj[here][i].second;
      if(dist[there] > nextDist){
        dist[there] = nextDist;
        par[there] = here;
        pq.push(mp(-nextDist, there));
      }
    }
  }
  return dist;
}

vector<int> getpath(int v){
  vector<int> path(1,v);
  while(par[v] != -1){
    v = par[v];
    path.pb(v);
  }
  reverse(path.begin(),path.end());
  return path;
}