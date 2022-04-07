//트리의 지름
const int MAXN = 200005;

vector<pii> adj[MAXN];
bool visited[MAXN];

void dfs(int n, int &far_idx, int sum, int& dia){
  visited[n] = true;
  if(sum > dia){
    dia = sum; far_idx = n;
  }
  for(auto p: adj[n]){
    int nxt = p.fst, val = p.snd;
    if(!visited[nxt]) dfs(nxt, far_idx, sum+val, dia);
  }
  visited[n] = false;
}

int a, b = 1, dia = 0;
dfs(b, a, 0, dia);
dfs(a, b, 0, dia);