//호프크로프트 카프: O(V^(1/2)E)
const int MAXN = 1000001;
const int MAXM = 1000001;

vector<int> adj[MAXN];
vector<int> aMatch, bMatch;
vector<int> level;
vector<bool> visited;

//A 그룹의 각 정점에 레벨을 매김
void bfs(int n){
  queue<int> q;
  for(int i=0;i<n;i++){
    if(!visited[i]){
      level[i] = 0;
      q.push(i);
    }
    else level[i] = INF;
  }
  while(!q.empty()){
    int here = q.front(); q.pop();
    for(int i=0;i<adj[here].size();i++){
      int there = adj[here][i];
      if(bMatch[there] != -1 && level[bMatch[there]] == INF){
        level[bMatch[there]] = level[here] + 1;
        q.push(bMatch[there]);
      }
    }
  }
}

bool dfs(int a){
  for(int i=0;i<adj[a].size();i++){
    int b = adj[a][i];
    if(bMatch[b] == -1 || (level[bMatch[b]] == level[a]+1 && dfs(bMatch[b]))){
      visited[a] = true;
      aMatch[a] = b;
      bMatch[b] = a;
      return true;
    }
  }
  return false;
}

int HK(int n, int m){
  aMatch = vector<int>(n,-1);
  bMatch = vector<int>(m,-1);
  level = vector<int>(n,0);
  visited = vector<bool>(m,false);
  int size = 0;
  while(1){
    bfs(n);
    int flow = 0;
    for(int i=0;i<n;i++)
      if(!visited[i] && dfs(i)) flow++;
    if(flow == 0) break;
    size += flow;
  }
  return size;
}