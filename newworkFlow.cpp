#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX_V = 1001;
const int INF = 987654321;
int V;
//capacity[u][v] = u에서 v로 보낼 수 있는 용량
//flow[u][v] = u에서 v로 흘러가는 유량 (방향이 반대일 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
//flow[][]를 계산하고 총 유량을 반환
int networkFlow(int source, int sink){
  memset(flow,0,sizeof(flow));
  int totalFlow = 0;
  while(true){
    vector<int> parent(MAX_V,-1);
    queue<int> q;
    parent[source] = source;
    q.push(source);
    while(!q.empty() && parent[sink] == -1){
      int here = q.front(); q.pop();
      for(int there = 0; there < V; there++){
        if(capacity[here][there] - flow[here][there] > 0 &&
          parent[there] == -1) {
          q.push(there);
          parent[there] = here;
        }
      }
    }
    if(parent[sink] == -1) break;
    int amount = INF;
    for(int p = sink; p != source; p = parent[p])
      amount = min(capacity[parent[p]][p] - flow[parent[p]][p],amount);
    for(int p = sink; p != source; p = parent[p]){
      flow[parent[p]][p] += amount;
      flow[p][parent[p]] -= amount;
    }
    totalFlow += amount;
  }
  return totalFlow;
}
