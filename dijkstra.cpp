// 다익스트라 알고리즘
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX_V 20001
#define INF 987654321

using namespace std;

int V,E,S;
vector<pair<int,int> > adj[MAX_V];

vector<int> dijkstra(int src){
  vector<int> dist(V+1,INF);
  dist[src]=0;
  priority_queue<pair<int,int> > pq;
  pq.push(make_pair(0,src));
  while(!pq.empty()){
    int cost = -pq.top().first, here = pq.top().second;
    pq.pop();
    if(dist[here]<cost) continue;
    for(int i=0;i<adj[here].size();i++){
      int there = adj[here][i].first;
      int nextDist = cost + adj[here][i].second;
      if(dist[there] > nextDist){
        dist[there] = nextDist;
        pq.push(make_pair(-nextDist, there));
      }
    }
  }
  return dist;
}

int main(){
  scanf("%d %d %d",&V,&E,&S);
  for(int i=0;i<E;i++){
    int u,v,w;
    scanf("%d %d %d",&u,&v,&w);
    adj[u].push_back(make_pair(v,w));
  }
  vector<int> dist = dijkstra(S);
  for(int i=1;i<=V;i++){
    if(dist[i]==INF) printf("INF\n");
    else printf("%d\n",dist[i]);
  }
}
