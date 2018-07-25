//디닉 알고리즘 - 인접리스트로 구현
//시간복잡도 - O(V^2E)
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define MAX_V 1005
#define S MAX_V-2
#define E MAX_V-1
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

int V;
// 유량 네트워크의 인접리스트
vector<Edge*> adj[MAX_V];
// 레벨 그래프에서 정점의 레벨 (S가 0)
int level[MAX_V];
// dfs 중, 이 정점이 몇 번째 간선까지 탐색했는 지 기억하는 용도
int work[MAX_V];

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

// 디닉 전용 bfs 함수
bool bfs(){
  memset(level,-1,sizeof(level));
  level[S] = 0;
  queue<int> q;
  q.push(S);
  while(!q.empty()){
    int here = q.front(); q.pop();
    for(int i=0;i<adj[here].size();i++){
      Edge* e = adj[here][i];
      int there = e->t;
      if(e->r() > 0 && level[there] == -1){
        q.push(there);
        level[there] = level[here] + 1;
      }
    }
  }
  return level[E] != -1;
}

// 디닉 전용 dfs 함수 : here에서 sink까지 최대 flow만큼의 유량을 보낼 것
int dfs(int here, int sink, int flow){
  // base case : dest에 도달함
  if(here == sink) return flow;
  // 현재 정점에서 인접한 정점들을 탐색
  // 이 때, 이번 단계에서 이미 쓸모없다고 판단한 간선은 다시 볼 필요가 없으므로
  // work배열로 간선 인덱스를 저장해 둔다.
  for(int &i=work[here];i<adj[here].size();i++){
    Edge* e = adj[here][i];
    int there = e->t;
    // next의 레벨이 curr의 레벨+1이고 간선에 r이 남아있어야만 이동
    if(e->r() > 0 && level[there] == level[here]+1){
      // df : flow와 다음 dfs함수의 결과 중 최소값
      // 결과적으로 경로상의 간선들 중 가장 작은 r이 된다.
      int amount = dfs(there,sink,min(e->r(),flow));
      if(amount > 0){
        e->push(amount);
        return amount;
      }
    }
  }
  // 증가 경로를 찾지 못함 : 유량 0 흘림
  return 0;
}

int main(){
  scanf("%d",&V);
  for(int i=0;i<V;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    addEdge(A,B,C);
  }
  // 디닉 알고리즘 수행
  int totalflow = 0;
  // 레벨 그래프를 구축하여 싱크가 도달 가능한 동안 반복
  while(bfs()){
    memset(work,0,sizeof(work));
    // 차단 유량 구하기
    while(1){
      int flow = dfs(S,E,INF); // dfs를 사용해 각 경로를 찾음
      if(flow == 0) break;
      totalflow += flow;
    }
  }
  printf("%d\n",totalflow);
}