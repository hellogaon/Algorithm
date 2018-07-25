//최대 독립 집합
//정점들을 가능한 한 많이 선택하되 선택된 정점끼리는 서로 인접하지 않게
//최대 독립 집합의 크기 = 정점의 수 - 최대 매칭의 크기
//최소 버텍스 커버
//정점들을 최소한으로 선택하여 버텍스 커버에 포함된 정점들과 그 정점에 연결된 간선들을
//제거하였을 때 간선이 하나도 남지 않게 되는 집합
//최소 버텍스 커버의 크기 = 최대 매칭의 크기
//최소 버텍스 커버와 최대 독립 집합은 여집합 관계
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
//aChosen[i] = 최대 독립 집합에 A_i가 포함되었는가?
//bChosen[i] = 최대 독립 집합에 B_i가 포함되었는가?
vector<bool> aChosen, bChosen; 

//A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다
bool dfs(int a){
  if(visited[a]) return false;
  visited[a] = true;
  for(int i=0;i<adj[a].size();i++){
    int b = adj[a][i];
    // b가 매칭되어 있지 않다면 bMatch[b]에서 부터 시작해 증가 경로를 찾는다.
    if(bMatch[b]==-1 || (!visited[bMatch[b]] && dfs(bMatch[b]))){
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

//이분 그래프의 정보가 주어질 때 실제 최대 독립 집합을 계산한다.
void calcMaxIndependentSet(){
  //aMatch[]와 bMatch[]를 계산한다.
  int C = bipartiteMatch();
  //1. A의 모든 정점들을 선택하고 B에서 대응되지 않은 정점들을 선택한다.
  aChosen = vector<bool>(N, true);
  bChosen = vector<bool>(M, false);
  for(int i=0;i<M;i++)
    if(bMatch[i] == -1)
      bChosen[i] = true;
  //2. 두 정점이 연결되어 있을 경우 그중 A의 정점을 지우고 B의 대응된 정점을
  //대신 선택한다. 더이상 변화가 일어나지 않을 때까지 반복한다.
  while(true){
    bool changed = false;
    for(int a=0;a<N;a++)
      for(int i=0;i<adj[a].size();i++){
        int b = adj[a][i];
        if(aChosen[a] && bChosen[b]){
          aChosen[a] = false;
          bChosen[aMatch[a]] = true;
          changed = true;
        }
      }
    if(!changed) break;
  }
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
  calcMaxIndependentSet();
}