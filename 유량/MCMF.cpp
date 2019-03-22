//MCMF: O(VEf)
//네트워크의 각 간선마다 유량을 1 흘려보낼 때 드는 비용이 정해져 있을 때
//최대 유량을 어떻게 흘려보내야 비용의 합을 최소화 할 수 있을지
const int MAXN = 1005;
const int S = MAXN-2;
const int E = MAXN-1;

vector<int> adj[MAXN];
int c[MAXN][MAXN], f[MAXN][MAXN], d[MAXN][MAXN];

pii MCMF(int s, int e){
  memset(f,0,sizeof(f));
  int mcmf = 0;
  int tf = 0;
  while(true){
    vector<int> par(MAXN,-1);
    vector<int> dist(MAXN,INF);
    vector<bool> inQ(MAXN,false);
    queue<int> q;
    par[s] = s;
    dist[s] = 0;
    inQ[s] = true;
    q.push(s);
    while(!q.empty()){
      int here = q.front(); q.pop();
      inQ[here] = false;
      for(auto next: adj[here]){
        if(c[here][next]-f[here][next] > 0 && dist[next] > dist[here] + d[here][next]){
          dist[next] = dist[here] + d[here][next];
          par[next] = here;
          if(!inQ[next]){
            q.push(next);
            inQ[next] = true;
          }
        }
      }
    }
    if(par[e] == -1) break;
    int sz = INF;
    for(int p = e; p != s; p = par[p])
      sz = min(c[par[p]][p] - f[par[p]][p],sz);
    for(int p = e; p != s; p = par[p]){
      mcmf += sz * d[par[p]][p];
      f[par[p]][p] += sz;
      f[p][par[p]] -= sz;
    }
    tf += sz;
  }
  return mp(tf,mcmf);
}