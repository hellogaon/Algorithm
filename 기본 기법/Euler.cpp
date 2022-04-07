//오일러경로, 오일러회로 알고리즘
//오일러 회로에서 시작점과 종점을 잇고 똑같이.
int N, mat[1001][1001];
vector<int> ans;

void dfs(int n){
  for(int i=0;i<N;i++){
    while(mat[n][i] > 0){
      mat[n][i]--;
      mat[i][n]--;
      dfs(i);
    }
  }
  ans.pb(n);
}