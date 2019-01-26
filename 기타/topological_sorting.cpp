//위상정렬
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int> > mat(1001);
int in[1001];
queue<int> q;
vector<int> ans;

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  for(int i=0;i<M;i++){
    int A,B;
    scanf("%d %d",&A,&B);
    mat[A].pb(B);
    in[B]++;
  }
  for(int i=1;i<=N;i++)
    if(in[i] == 0) q.push(i);
  for(int i=0;i<N;i++){
    if(q.empty()){
      printf("0\n");
      return 0;
    }
    int now = q.front(); q.pop();
    ans.pb(now);
    for(int j=0;j<mat[now].size();j++){
      int next = mat[now][j];
      in[next]--;
      if(in[next] == 0) q.push(next);
    }
  }
  for(int i=0;i<N;i++)
    printf("%d\n",ans[i]);
}
