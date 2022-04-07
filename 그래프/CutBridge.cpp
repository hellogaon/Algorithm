//무향그래프에서 삭제했을 때 그래프가 두 개 이상의 컴포넌트로 분리되는 간선
int V,E;
int vcnt;
vector<int> adj[MAXV];
vector<int> visited(MAXV,-1);
vector<pii> isCB;

int cb(int here, int par){
  int ret = visited[here] = vcnt++;
  for(int next: adj[here]){
    if(next == par) continue;
    if(visited[next] == -1){
      int sub = cb(next, here);
      if(sub > visited[here])
        isCB.pb(mp(min(here, next), max(here, next)));
      ret = min(ret, sub);
    }
    else ret = min(ret, visited[next]);
  }
  return ret;
}

for(int i=1;i<=V;i++)
  if(visited[i] == -1) cb(i, 0);