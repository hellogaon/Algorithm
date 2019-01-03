//이분매칭 O(VE)
const int MAXN = 1001;
const int MAXM = 1001;

vector<int> adj[MAXN];
//각 정점에 매칭된 상대 정점의 번호를 저장
vector<int> aMatch, bMatch;
vector<bool> visited;

bool dfs(int a){
  if(visited[a]) return false;
  visited[a] = true;
  for(int i=0;i<adj[a].size();i++){
    int b = adj[a][i];
    if(bMatch[b] == -1 || (!visited[bMatch[b]] && dfs(bMatch[b]))){
      aMatch[a] = b;
      bMatch[b] = a;
      return true;
    }
  }
  return false;
}

int BM(int n, int m){
  aMatch = vector<int>(n,-1);
  bMatch = vector<int>(m,-1);
  int size = 0;
  for(int i=0;i<n;i++){
    visited = vector<bool>(n,false);
    if(dfs(i)) size++; 
  }
  return size;
}