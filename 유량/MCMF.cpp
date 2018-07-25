//MCMF (최소 비용 최대 유량)
//네트워크의 각 간선마다 유량을 1 흘려보낼 때 드는 비용이 정해져 있을 때
//최대 유량을 어떻게 흘려보내야 비용의 합을 최소화 할 수 있을지
//시간 복잡도 O(VEf)
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define MAX_N 400
#define MAX_M 400
#define S MAX_V-2
#define E MAX_V-1
#define MAX_V MAX_N+MAX_M+2
#define INF 987654321

using namespace std;

int N,M;
vector<int> adj[MAX_V];
// c[u][v] = u에서 v로 보낼 수 있는 용량
// f[u][v] = u에서 v로 흘러가는 유량 (방향이 반대일 경우 음수)
// d[u][v] = u에서 v로 흘러가는 비용
int c[MAX_V][MAX_V], f[MAX_V][MAX_V], d[MAX_V][MAX_V];
// f[][]를 계산하고 총 유량을 반환
pair<int,int> MCMF(int source, int sink){
  memset(f,0,sizeof(f));
  int mcmf = 0;
  int totalflow = 0;
  while(true){
    // SPFA 탐색으로 증가 경로를 찾는다
    vector<int> par(MAX_V,-1);
    vector<int> dist(MAX_V,INF);
    vector<bool> inQ(MAX_V,false);
    queue<int> q;
    par[source] = source;
    dist[source] = 0;
    inQ[source] = true;
    q.push(source);
    while(!q.empty()){
      int here = q.front(); q.pop();
      inQ[here] = false;
      for(int i=0;i<adj[here].size();i++){
        int there = adj[here][i];
        if(c[here][there]-f[here][there] > 0 && dist[there] > dist[here] + d[here][there]){
          dist[there] = dist[here] + d[here][there];
          par[there] = here;
          if(!inQ[there]){
            q.push(there);
            inQ[there] = true;
          }
        }
      }
    }
    if(par[sink] == -1) break;
    int amount = INF;
    for(int p = sink; p != source; p = par[p])
      amount = min(c[par[p]][p] - f[par[p]][p],amount);
    for(int p = sink; p != source; p = par[p]){
      mcmf += amount * d[par[p]][p];
      f[par[p]][p] += amount;
      f[p][par[p]] -= amount;
    }
    totalflow += amount;
  }
  return make_pair(totalflow,mcmf);
}

int main(){
  scanf("%d %d",&N,&M);
  for(int i=0;i<N;i++){
    c[S][i] = 1;
    adj[S].push_back(i);
    adj[i].push_back(S);
  }
  for(int i=N;i<N+M;i++){
    c[i][E] = 1;
    adj[i].push_back(E);
    adj[E].push_back(i);
  }
  for(int i=0;i<N;i++){
    int A; scanf("%d",&A);
    for(int j=0;j<A;j++){
      int X,D; scanf("%d %d",&X,&D);
      c[i][N+X-1] = 1;
      d[i][N+X-1] = D;
      d[N+X-1][i] = -D;
      adj[i].push_back(N+X-1);
      adj[N+X-1].push_back(i);
    }
  }
  pair<int,int> p = MCMF(S,E);
  printf("%d\n%d\n",p.first,p.second);
}