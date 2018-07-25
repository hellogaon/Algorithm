//최소 스패닝 트리 - 프림 알고리즘
//그래프의 정점 전부와 간선의 부분 집합으로 구성된 부분 그래프
//시간복잡도 - O(V^2+E)
#include <cstdio>
#include <vector>
#include <queue>
#define MAX_V 10001
#define INF 987654321
using namespace std;

int V,E;
vector<pair<int,int> > adj[MAX_V];

// 주어진 그래프에 대해 최소 스패닝 트리에 포함된 간선의 목록을 selected에
// 저장하고 가중치의 합을 반환한다.
int prim(vector<pair<int,int> >& selected){
  selected.clear();
  // 해당 정점이 트리에 포함되어 있나?
  vector<bool> added(V,false);
  // 트리에 인접한 간선 중 해당 정점에 닿는 최소 간선의 정보를 저장한다.
  vector<int> parent(V,-1);
  priority_queue<pair<int,int> > pq;

  int ret = 0;
  // 0번 정점을 시작점으로 항상 트리에 가장 먼저 추가한다.
  pq.push(make_pair(0,0));
  parent[0] = 0;
  while(!pq.empty()){
    int cost = -pq.top().first, u = pq.top().second;
    pq.pop();
    if(added[u]) continue;
    //(parent[u],u)를 트리에 추가한다
    if(parent[u] != u)
      selected.push_back(make_pair(parent[u],u));
    ret += cost;
    added[u] = true;
    for(int i=0;i<adj[u].size();i++){
      int v = adj[u][i].first, weight = adj[u][i].second;
      if(!added[v]){
        parent[v] = u;
        pq.push(make_pair(-weight,v));
      }
    }
  }
  return ret;
}

int main(){
  scanf("%d %d",&V,&E);
  for(int i=0;i<E;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    adj[A-1].push_back(make_pair(B-1,C));
    adj[B-1].push_back(make_pair(A-1,C));
  }
  vector<pair<int,int> > selected;
  printf("%d\n",prim(selected));
}