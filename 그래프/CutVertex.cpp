//무향그래프에서 삭제했을 때 해당 정점이 포함된 그래프가 두 개 이상의 컴포넌트로 분리되는 정점
const int MAXV = 10001;

int V,E;
int vcnt;
vector<int> adj[MAXV];
vector<int> visited(MAXV,-1);
vector<bool> isCV(MAXV,false);

int cv(int here, bool root){
  int ret = visited[here] = vcnt++;
  int c = 0;
  for(int next: adj[here]){
    if(visited[next] == -1){
      int sub = cv(next, false);
      if(!root && sub >= visited[here])
        isCV[here] = true;
      ret = min(ret, sub);
      c++;
    }
    else ret = min(ret, visited[next]);
  }
  if(root) isCV[here] = (c >= 2);
  return ret;
}

for(int i=1;i<=V;i++)
  if(visited[i] == -1) cv(i,true);