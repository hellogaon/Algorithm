//이분 매칭 - 호프크로프트 카프 알고리즘
//시간복잡도 O(|E||V|^(1/2))
//격자 그래프가 나온다면 가로와 세로, 두 대각선을 이분하여 생각해볼 것
#include <cstdio>
#include <vector>
#include <queue>
#define MAX_N 10001
#define MAX_M 10001
#define INF 987654321

using namespace std;

//A와 B의 정점의 개수
int N,M;
//adj[i][j]=Ai와 Bj가 연결되어 있는가?
vector<int> adj[MAX_N];
//각 정점에 매칭된 상대 정점의 번호를 저장
vector<int> aMatch, bMatch;
//level[i] : (A 그룹의 i번 정점의 레벨)
vector<int> level;
//dfs()의 방문 여부
vector<bool> visited;

//호프크로프트 카프 전용 bfs함수 : A그룹의 각 정점에 레벨을 매김
void bfs(){
  queue<int> q;
  //매칭에 안 속한 A그룹의 정점만 레벨 0인 채로 시작
  for(int i=0;i<N;i++){
    if(!visited[i]){
      level[i] = 0;
      q.push(i);
    }
    else level[i] = INF;
  }
  //BFS를 통해 A그룹 정점에 레벨을 매긴다.
  while(!q.empty()){
    int here = q.front(); q.pop();
    for(int i=0;i<adj[here].size();i++){
      int there = adj[here][i];
      if(bMatch[there] != -1 && level[bMatch[there]] == INF){
        level[bMatch[there]] = level[here] + 1;
        q.push(bMatch[there]);
      }
    }
  }
}

//호프크로프트 카프 전용 dfs함수 : 새 매칭을 찾으면 true
bool dfs(int a){
  for(int i=0;i<adj[a].size();i++){
    int b = adj[a][i];
    //이분매칭 코드와 상당히 유사하나 level배열에 대한 조건이 추가로 붙음
    if(bMatch[b] == -1 || (level[bMatch[b]] == level[a]+1 && dfs(bMatch[b]))){
      visited[a] = true;
      aMatch[a] = b;
      bMatch[b] = a;
      return true;
    }
  }
  return false;
}

//aMatch, bMatch 배열을 계산하고 최대 매칭의 크기를 반환
int HopcroftKarp(){
  //처음에는 어떤 정점도 연결되어 있지 않다.
  aMatch = vector<int>(N,-1);
  bMatch = vector<int>(M,-1);
  level = vector<int>(N,0);
  visited = vector<bool>(N,false);
  int size = 0;
  while(1){
    //각 정점에 레벨을 매기고 시작
    bfs();
    //A그룹의 정점을 순회하며 매칭 증가량을 찾는다.
    int flow = 0;
    for(int i=0;i<N;i++)
      if(!visited[i] && dfs(i)) flow++;
    //더 이상 증가경로를 못찾으면 알고리즘 종료
    if(flow == 0) break;
    //찾았을 경우 반복
    size += flow;
  }
  return size;
}

int main(){
  scanf("%d %d",&N,&M);
  for(int i=0;i<N;i++){
    int S; scanf("%d",&S);
    for(int j=0;j<S;j++){
      int X; scanf("%d",&X);
      adj[i].push_back(X-1);
    }
  }
  printf("%d\n",HopcroftKarp());
}