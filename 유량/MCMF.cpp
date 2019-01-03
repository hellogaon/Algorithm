//MCMF: O(VEf)
//네트워크의 각 간선마다 유량을 1 흘려보낼 때 드는 비용이 정해져 있을 때
//최대 유량을 어떻게 흘려보내야 비용의 합을 최소화 할 수 있을지
const int MAXN = 1005;
const int S = MAXN-2;
const int E = MAXN-1;

int N,M;
vector<int> adj[MAXN];
int c[MAXN][MAXN], f[MAXN][MAXN], d[MAXN][MAXN];

pii MCMF(int src, int sink){
  memset(f,0,sizeof(f));
  int mcmf = 0;
  int tf = 0;
  while(true){
    vector<int> par(MAX_V,-1);
    vector<int> dist(MAX_V,INF);
    vector<bool> inQ(MAX_V,false);
    queue<int> q;
    par[src] = src;
    dist[src] = 0;
    inQ[src] = true;
    q.push(src);
    while(!q.empty()){
      int here = q.front(); q.pop();
      inQ[here] = false;
      for(int i=0;i<adj[here].size();i++){
        int there = adj[here][i];
        if(c[here][there]-f[here][there] > 0 && dist[there] > dist[here] + d[here][there]){
          dist[there] = dist[here] + d[here][there];
          par[there] = here;
          if(!inQ[there]){
            q.push(there);
            inQ[there] = true;
          }
        }
      }
    }
    if(par[sink] == -1) break;
    int sz = INF;
    for(int p = sink; p != src; p = par[p])
      sz = min(c[par[p]][p] - f[par[p]][p],sz);
    for(int p = sink; p != src; p = par[p]){
      mcmf += sz * d[par[p]][p];
      f[par[p]][p] += sz;
      f[p][par[p]] -= sz;
    }
    tf += sz;
  }
  return mp(tf,mcmf);
}

int main(){
  scanf("%d %d",&N,&M);
  for(int i=0;i<N;i++){
    c[S][i] = 1;
    adj[S].pb(i);
    adj[i].pb(S);
  }
  for(int i=N;i<N+M;i++){
    c[i][E] = 1;
    adj[i].pb(E);
    adj[E].pb(i);
  }
  for(int i=0;i<N;i++){
    int A; scanf("%d",&A);
    for(int j=0;j<A;j++){
      int X,D; scanf("%d %d",&X,&D);
      c[i][N+X-1] = 1;
      d[i][N+X-1] = D;
      d[N+X-1][i] = -D;
      adj[i].pb(N+X-1);
      adj[N+X-1].pb(i);
    }
  }
  pii p = MCMF(S,E);
  printf("%d\n%d\n",p.first,p.second);
}