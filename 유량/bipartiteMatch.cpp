//이분 매칭
//이분 그래프에서 최대 매칭을 구하는 문제
//시간복잡도 O(|V||E|)
//격자 그래프가 나온다면 가로와 세로, 두 대각선을 이분하여 생각해볼 것
#include <cstdio>
#include <vector>
#define MAX_N 1001
#define MAX_M 1001

using namespace std;

//A와 B의 정점의 개수
int N,M;
//adj[i][j]=Ai와 Bj가 연결되어 있는가?
vector<int> adj[MAX_N];
//각 정점에 매칭된 상대 정점의 번호를 저장
vector<int> aMatch, bMatch;
//dfs()의 방문 여부
vector<bool> visited;

//A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다
bool dfs(int a){
  if(visited[a]) return false;
  visited[a] = true;
  for(int i=0;i<adj[a].size();i++){
    int b = adj[a][i];
    // b가 매칭되어 있지 않다면 bMatch[b]에서 부터 시작해 증가 경로를 찾는다.
    if(bMatch[b] == -1 || (!visited[bMatch[b]] && dfs(bMatch[b]))){
      // 증가 경로 발견!! a와 b를 매치시킨다.
      aMatch[a] = b;
      bMatch[b] = a;
      return true;
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
  for(int i=0;i<N;i++){
    visited = vector<bool>(N,false);
    if(dfs(i)) size++; 
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
  printf("%d\n",bipartiteMatch());
}