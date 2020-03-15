// 네트워크 플로우
// 시간복잡도 min(O(|E|f),O(|V||E|^2)
const int MAXV = 1001;

vector<int> adj[MAXV];
// c[u][v] = u에서 v로 보낼 수 있는 용량
// f[u][v] = u에서 v로 흘러가는 유량 (방향이 반대일 경우 음수)
int c[MAXV][MAXV], f[MAXV][MAXV];
// f[][]를 계산하고 총 유량을 반환
int networkflow(int s, int e){
  memset(f,0,sizeof(f));
  int ret = 0;
  while(true){
    // 너비우선 탐색으로 증가 경로를 찾는다
    vector<int> par(MAXV,-1);
    queue<int> q;
    par[s] = s;
    q.push(s);
    while(!q.empty() && par[e] == -1){
      int here = q.front(); q.pop();
      for(int i=0;i<adj[here].size();i++){
        int there = adj[here][i];
        if(c[here][there] - f[here][there] > 0 && par[there] == -1) {
          q.push(there);
          par[there] = here;
        }
      }
    }
    if(par[e] == -1) break;
    int amt = INF;
    for(int p = e; p != s; p = par[p])
      amt = min(c[par[p]][p] - f[par[p]][p], amt);
    for(int p = e; p != s; p = par[p]){
      f[par[p]][p] += amt;
      f[p][par[p]] -= amt;
    }
    ret += amt;
  }
  return ret;
}
