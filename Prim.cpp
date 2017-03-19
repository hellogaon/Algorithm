//최소 스패닝 트리 - 프림 알고리즘
//모든 노드를 이었을 때 최소 간선 비용
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class my_greater{
public:
  bool operator()(const pair<int,int>& arg1, const pair<int,int>& arg2) const{
    return arg1.second > arg2.second;
  }
};

int V,E;  //노드수 간선수
vector<vector<pair<int,int> > > adj(1001);
vector<int> check(1001);
priority_queue<pair<int,int>,vector<pair<int,int> >,my_greater> pq;

int prim(){
  int N=0, ans=0;
  pq.push(make_pair(1,0));
  while(N!=V){
    int id=pq.top().first, d=pq.top().second;
    pq.pop();
    if(check[id]==-1) continue;
    check[id]=-1; N+=1; ans+=d;
    for(int i=0;i<adj[id].size();i++)
      pq.push(make_pair(adj[id][i]));
  }
  return ans;
}

int main(){
  scanf("%d %d",&V,&E);
  for(int i=0;i<E;i++){
    int u,v,w; //시작노드 끝노드 간선의크기
    scanf("%d %d %d",&u,&v,&w);
    adj[u].push_back(make_pair(v,w));
    adj[v].push_back(make_pair(u,w));
  }
  printf("%d\n",prim());
}
