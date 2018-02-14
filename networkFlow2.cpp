// 네트워크 플로우 인접리스트로 구현
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define MAX_V 1001
#define INF 987654321

using namespace std;

// 간선 구조체
struct Edge {
  int t,c,f;
  // 역방향 간선의 포인터
  Edge* rev;
  // 이 간선의 잔여 용량을 계산
  int r() const { return c - f; }
  // 이 간선을 따라 용량 amt를 보낸다
  void push(int amt){
    f += amt;
    rev->f -= amt;
  }
};

int V,S,E;
// 유량 네트워크의 인접리스트
vector<Edge*> adj[MAX_V];
// u에서 v로 가는 간선을 추가
void addEdge(int u, int v, int c){
  Edge* uv = new Edge(), *vu = new Edge();
  // u에서 v로 가는 간선을 초기화한다.
  uv->t = v;
  uv->c = c;
  uv->f = 0;
  uv->rev = vu;
  // v에서 u로 가는 간선을 초기화한다. 이 간선의 용량은 0이다
  vu->t = u;
  vu->c = 0;
  vu->f = 0;
  vu->rev = uv;
  adj[u].push_back(uv);
  adj[v].push_back(vu);
}

int networkflow(int source, int sink){
  int totalflow = 0;
  while(true){
    // 너비우선 탐색으로 증가 경로를 찾는다
    vector<int> parent(MAX_V,-1);
    Edge* path[MAX_V];
    queue<int> q;
    parent[source] = source;
    q.push(source);
    while(!q.empty() && parent[sink] == -1){
      int here = q.front(); q.pop();
      for(int i=0; i<adj[here].size();i++){
        Edge* e = adj[here][i];
        int there = e->t;
        if(e->r() > 0 && parent[there] == -1) {
          q.push(there);
          parent[there] = here;
          path[there] = e;
        }
      }
    }
    if(parent[sink] == -1) break;
    int amount = INF;
    for(int p = sink; p != source; p = parent[p])
      amount = min(amount,path[p]->r());
    for(int p = sink; p != source; p = parent[p])
      path[p]->push(amount);
    totalflow += amount;
  }
  return totalflow;
}

int ctoi(char c){
  if(c <= 'Z') return c-'A';
  return c-'a'+26;
}

int main(){
  scanf("%d %d %d",&V,&S,&E);
  for(int i=0;i<V;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    addEdge(A,B,C);
  }
  printf("%d\n",networkflow(S,E));
}