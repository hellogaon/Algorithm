//페어로 짠 다익스트라 최단경로와 경로추적
//입력: 노드수 간선수 시작노드
//이후 간선 수 만큼 간선의 시작노드 끝노드 간선의크기
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#define MAX_VALUE 100000000

using namespace std;

class my_greater{
public:
  bool operator()(const pair<int,int>& arg1, const pair<int,int>& arg2) const{
    return arg1.second > arg2.second;
  }
};

int main(){
  int V,E,K; //노드수 간선수 시작노드
  scanf("%d %d %d",&V,&E,&K);
  vector<int> dist(V+1,MAX_VALUE); //최단경로
  vector<int> path(V+1,-1); //경로추적
  vector<vector<pair<int,int> > > adj(V+1);
  priority_queue<pair<int,int>,vector<pair<int,int> >,my_greater> pq;

  for(int i=0;i<E;i++){
    int u,v,w; //시작노드 끝노드 간선의크기
    scanf("%d %d %d",&u,&v,&w);
    adj[u].push_back(make_pair(v,w));
  }

  dist[K]=0; path[K]=0;
  pq.push(make_pair(K,0));

  while(!pq.empty()){
    int id=pq.top().first,d=pq.top().second;
    pq.pop();
    if(dist[id]<d) continue;
    for(int i=0;i<adj[id].size();i++){
      int n = adj[id][i].first, v = adj[id][i].second;
      if(dist[n]>dist[id]+v){
        dist[n]=dist[id]+v;
        pq.push(make_pair(n,dist[n]));
        path[n]=id;
      }
    }
  }
  //경로추적
  for(int i=1;i<=V;i++){
    printf("%d -> %d 경로 : ",K,i);
    if(path[i]==-1){
      printf("없음\n"); continue;
    }
    stack<int> s;
    s.push(i);
    while(s.top()!=K)
      s.push(path[s.top()]);
    while(s.size()>1){
      printf("%d -> ",s.top());
      s.pop();
    }
    printf("%d\n",s.top());
  }
  //최단경로
  for(int i=1;i<=V;i++){
    if(dist[i]!=MAX_VALUE) printf("%d\n",dist[i]);
    else printf("INF\n");
  }
}
