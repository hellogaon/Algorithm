// 네트워크 플로우 인접리스트로 구현
// 시간복잡도 min(O(|E|f),O(|V||E|^2)
const int MAXV = 1005;
const int S = MAXV-2;
const int E = MAXV-1;

// 간선 구조체
struct Edge {
  int t,c,f;
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

// 유량 네트워크의 인접리스트
vector<Edge*> adj[MAXV];
// u에서 v로 가는 간선을 추가
void addEdge(int u, int v, int c){
  Edge* uv = new Edge(), *vu = new Edge();
  uv->t = v; uv->c = c; uv->f = 0; uv->rev = vu;
  vu->t = u; vu->c = 0; vu->f = 0; vu->rev = uv;
  adj[u].pb(uv);
  adj[v].pb(vu);
}

int networkflow(int s, int e){
  int ret = 0;
  while(true){
    // 너비우선 탐색으로 증가 경로를 찾는다
    vector<int> par(MAXV,-1);
    Edge* path[MAXV];
    queue<int> q;
    par[s] = s;
    q.push(s);
    while(!q.empty() && par[e] == -1){
      int here = q.front(); q.pop();
      for(int i=0;i<adj[here].size();i++){
        Edge* ed = adj[here][i];
        int there = ed->t;
        if(ed->r() > 0 && par[there] == -1){
          q.push(there);
          par[there] = here;
          path[there] = ed;
        }
      }
    }
    if(par[e] == -1) break;
    int amt = INF;
    for(int p = e; p != s; p = par[p])
      amt = min(amt, path[p]->r());
    for(int p = e; p != s; p = par[p])
      path[p]->push(amt);
    ret += amt;
  }
  return ret;
}
