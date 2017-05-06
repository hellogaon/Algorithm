#include <cstdio>
#include <vector>
#define MAX_N 201
#define MAX_M 201

using namespace std;

//A와 B의 정점의 개수
int N,M;
//adj[i][j]=Ai와 Bj가 연결되어 있는가?
bool adj[MAX_N][MAX_M];
//각 정점에 매칭된 상대 정점의 번호를 저장
vector<int> aMatch, bMatch;
//dfs()의 방문 여부
vector<bool> visited;
//A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다
bool dfs(int a){
  if(visited[a]) return false;
  visited[a] = true;
  for(int b=0;b<M;b++){
    if(adj[a][b]){
      // b가 매칭되어 있지 않다면 bMatch[b]에서 부터 시작해 증가 경로를 찾는다.
      if(bMatch[b]==-1 || dfs(bMatch[b])){
        // 증가 경로 발견!! a와 b를 매치시킨다.
        aMatch[a] = b;
        bMatch[b] = a;
        return true;
      }
    }
  }
  return false;
}

//aMatch, bMatch 배열을 계산하고 최대 매칭의 크기를 반환
int bipartiteMatch(){
  //처음에는 어떤 정점도 연결되어 있지 않다.
  aMatch = vector<int>(N,-1);
  bMatch = vector<int>(M,-1);
  int size = 0;
  for(int start = 0; start<N; start++){
    visited = vector<bool>(N,false);
    if(dfs(start)) size++;
  }
  return size;
}

int main(){
  scanf("%d %d",&N,&M);
  for(int i=0;i<N;i++){
    int S; scanf("%d",&S);
    for(int j=0;j<S;j++){
      int X; scanf("%d",&X);
      adj[i][X-1] = true;
    }
  }
  printf("%d\n",bipartiteMatch());
}
