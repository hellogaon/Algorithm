//강한 연결 요소: O(V+E)
//방향그래프 상에서 두 정점 u와 v에 대해 양방향으로 가는 경로가 모두 있을 때 같은 SCC
//scc함수가 종료하기 직전에 SCC를 생성하기에 SCC는 위상 정렬의 역순으로 번호가 매겨진다.
const int MAXV = 10005;

int V,E;
vector<int> adj[MAXV];
int scccnt,vcnt;
vector<int> sccId(MAXV,-1);
vector<int> visited(MAXV,-1);
stack<int> st;

int scc(int here){
  int ret = visited[here] = vcnt++;
  st.push(here);
  for(int next: adj[here]){
    if(visited[next] == -1)
      ret = min(ret, scc(next));
    else if(sccId[next] == -1)
      ret = min(ret, visited[next]);
  }
  if(ret == visited[here]){
    while(1){
      int t = st.top(); st.pop();
      sccId[t] = scccnt;
      if(t == here) break;
    }
    scccnt++;
  }
  return ret;
}

for(int i=1;i<=V;i++)
	if(visited[i] == -1) scc(i);