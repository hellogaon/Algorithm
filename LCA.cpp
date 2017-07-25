//LCA(Lowest Common Ancestor) 최소 공통 조상
//두 노드의 가장 가까운 공통 조상을 찾는 알고리즘
//1. depth[u] > depth[v] 일 때 u를 parent[u]로 대체
//2. u != v일 때 u를 parent[u], v를 parent[v]로 동시에 대체
//parent[u][k] = 정점 u의 2^k번째 부모
//parent[u][k+1] = parent[parent[u][k]][k]
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX 18

using namespace std;

int par[100001][MAX],d[100001];
bool chk[100001];
vector<int> t[100001];

void dfs(int here){
  chk[here]=true;
  for(int i=0;i<t[here].size();i++){
    int next = t[here][i];
    if(chk[next]) continue;
    par[next][0] = here;
    d[next] = d[here]+1;
    dfs(next);
  }
}

int lca(int u, int v){
  if(d[u]<d[v]) swap(u,v);
  for(int i=MAX-1;i>=0;i--)
    if(d[u]-d[v] >= (1<<i))
      u = par[u][i];
  if(u == v) return u;
  for(int i=MAX-1;i>=0;i--)
    if(par[u][i]!=par[v][i])
      u = par[u][i], v = par[v][i];
  return par[u][0];
}

int main(){
  int N,M;
  scanf("%d",&N);
  for(int i=1;i<N;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    t[u].push_back(v);
    t[v].push_back(u);
  }
  dfs(1);
  for(int j=0;j<MAX-1;j++)
    for(int i=2;i<=N;i++)
        par[i][j+1]=par[par[i][j]][j];
  scanf("%d",&M);
  for(int i=0;i<M;i++){
    int u,v;
    scanf("%d %d",&u,&v);
    printf("%d\n",lca(u,v));
  }
}
