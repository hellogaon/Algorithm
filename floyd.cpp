// 플로이드-워셜 알고리즘
// mat[][] 전체를 무한대로 초기화 시키고 저장
// ans[][] 두 정점을 잇는 경로의 최소 비용 테이블
// ans[][]는 초기값이 mat[]와 같고 mat[i][i]=0으로!
// 3중포문 - (거치는 점 - 출발 점 - 도착점)순으로 한 후 비교
#include <cstdio>
#include <algorithm>
#define INF 987654321

using namespace std;

int N,M;
int mat[101][101],ans[101][101];

void floyd(){
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      ans[i][j]=mat[i][j];
  for(int i=1;i<=N;i++)
    ans[i][i]=0;
  for(int k=1;k<=N;k++)
    for(int i=1;i<=N;i++)
      for(int j=1;j<=N;j++)
        if(ans[i][j]>ans[i][k]+ans[k][j])
          ans[i][j]=ans[i][k]+ans[k][j];
}
int main(){
  scanf("%d %d",&N,&M);
  for(int i=1;i<=N;i++)
    for(int j=1;j<=N;j++)
      mat[i][j]=INF;
  for(int i=0;i<M;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    mat[A][B]=min(mat[A][B],C);
  }
  floyd();
  for(int i=1;i<=N;i++){
    for(int j=1;j<=N;j++){
      printf("%d ",ans[i][j]);
    }
    printf("\n");
  }
}
