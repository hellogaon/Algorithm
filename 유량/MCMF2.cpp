// MCMF 인접리스트로 구현 : O((V+E)f)
// 네트워크의 각 간선마다 유량을 1 흘려보낼 때 드는 비용이 정해져 있을 때
// 최대 유량을 어떻게 흘려보내야 비용의 합을 최소화 할 수 있을지
// 비용만 최소화하고 싶을 경우 비용이 0 이상 되면 그냥 끊어버리면 된다.
const int MAXV = 1005;
const int S = MAXV-2;
const int E = MAXV-1;

// 간선 구조체
struct Edge {
  int t,c,f,d;
  // 역방향 간선의 포인터
  Edge* rev;
  // 이 간선의 잔여 용량을 계산
  int r() const { return c - f; }
  // 이 간선을 따라 용량 amt를 보낸다
  void push(int amt){
    f += amt;
    rev->f -= amt;
  }
};

vector<Edge*> adj[MAXV];

void addEdge(int u, int v, int c, int d){
  Edge* uv = new Edge(), *vu = new Edge();
  uv->t = v; uv->c = c; uv->f = 0; uv->d = d; uv->rev = vu;
  vu->t = u; vu->c = 0; vu->f = 0; vu->d = -d; vu->rev = uv;
  adj[u].pb(uv);
  adj[v].pb(vu);
}

pii MCMF(int s, int e){
  int mcmf = 0;
  int tf = 0;
  while(true){
    vector<int> par(MAXV,-1);
    vector<int> dist(MAXV,INF);
    vector<bool> inQ(MAXV,false);
    Edge* path[MAXV];
    queue<int> q;
    par[s] = s;
    dist[s] = 0;
    inQ[s] = true;
    q.push(s);
    while(!q.empty()){
      int here = q.front(); q.pop();
      inQ[here] = false;
      for(int i=0;i<adj[here].size();i++){
        Edge* ed = adj[here][i];
        int there = ed->t, cost = ed->d;
        if(ed->r() > 0 && dist[there] > dist[here] + cost){
          dist[there] = dist[here] + cost;
          par[there] = here;
          path[there] = ed;
          if(!inQ[there]){
            q.push(there);
            inQ[there] = true;
          }
        }
      }
    }
    if(par[e] == -1) break;
    int sz = INF;
    for(int p = e; p != s; p = par[p])
      sz = min(sz, path[p]->r());
    for(int p = e; p != s; p = par[p]){
      mcmf += sz * path[p]->d;
      path[p]->push(sz);
    }
    tf += sz;
  }
  return mp(tf, mcmf);
}
