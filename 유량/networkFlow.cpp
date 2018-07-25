//네트워크 플로우
//각 간선에 용량이라는 추가 속성이 존재하는 그래프
//시간복잡도 - min(O(|E|f),O(|V||E|^2)
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define MAX_V 1005
#define S MAX_V-2
#define E MAX_V-1
#define INF 987654321

using namespace std;

int V;
vector<int> adj[MAX_V];
// c[u][v] = u에서 v로 보낼 수 있는 용량
// f[u][v] = u에서 v로 흘러가는 유량 (방향이 반대일 경우 음수)
int c[MAX_V][MAX_V], f[MAX_V][MAX_V];
// f[][]를 계산하고 총 유량을 반환
int networkflow(int source, int sink){
  memset(f,0,sizeof(f));
  int totalflow = 0;
  while(true){
    // 너비우선 탐색으로 증가 경로를 찾는다
    vector<int> par(MAX_V,-1);
    queue<int> q;
    par[source] = source;
    q.push(source);
    while(!q.empty() && par[sink] == -1){
      int here = q.front(); q.pop();
      for(int i=0;i<adj[here].size();i++){
        int there = adj[here][i];
        if(c[here][there]-f[here][there] > 0 && par[there] == -1) {
          q.push(there);
          par[there] = here;
        }
      }
    }
    if(par[sink] == -1) break;
    int amount = INF;
    for(int p = sink; p != source; p = par[p])
      amount = min(c[par[p]][p] - f[par[p]][p],amount);
    for(int p = sink; p != source; p = par[p]){
      f[par[p]][p] += amount;
      f[p][par[p]] -= amount;
    }
    totalflow += amount;
  }
  return totalflow;
}

int main(){
  scanf("%d",&V);
  for(int i=0;i<V;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    c[A][B] += C;
    adj[A].push_back(B);
    adj[B].push_back(A);
  }
  printf("%d\n",networkflow(S,E));
}