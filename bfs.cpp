//bfs와 연결리스트 구현
//노드의 수 간선의 수 입력 받아 간선의 수 만큼 시작노드 끝노드 입력
//이 알고리즘은 연결 요소의 개수를 구한다.
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

vector <vector<int> > v(1005); //연결리스트
queue <int> q;

int arr[1000]={0},check=1; //체크리스트

void bfs(int num){
  q.push(num);
  arr[num]=1;
  while(!q.empty()){
    int x=q.front(); q.pop();
    for(int i=0;i<v[x].size();i++){
      if(arr[v[x][i]]==0){
        q.push(v[x][i]);
        arr[v[x][i]]=1;
      }
    }
  }
}

int main(){
  int N,M;
  scanf("%d %d",&N,&M); //노드의 수, 간선의 수
  for(int i=0;i<M;i++){
    int U,V;
    scanf("%d %d",&U,&V);
    v[U].push_back(V);
    v[V].push_back(U); //방향없는 그래프 이기 때문에.
  }
  for(int i=1;i<=N;i++){
    if(arr[i]==0){
      bfs(i);
      check++;
    }
  }
  printf("%d\n",check-1);
}
