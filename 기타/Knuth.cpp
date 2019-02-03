//Knuth Optimization: O(N^2)
//D(i,j) = min(i<k<j){ (D(i,k)+D(k,j) } + C(i,j)
//조건 1) C함수가 quadrangle inequality를 만족
//a≤b≤c≤d일 때 C(a,c)+C(b,d) ≤ C(a,d)+C(b,c)
//조건 2) C함수가 구간 단조성을 만족
//a≤b≤c≤d일 때 C(b,c) ≤ C(a,d)
//K[i][j] = D[i][j]가 최소가 되기 위한 가장 작은 k일 때
//위 조건을 만족할 경우
//K[i][j-1] ≤ K[i][j] ≤ K[i+1][j] 가 성립
const int MAXN = 501;
int D[MAXN][MAXN], K[MAXN][MAXN];

for(int i=2;i<=N;i++){
  D[i-1][i] = 0; K[i-1][i] = i;
}

for(int d=2;d<=N;d++){
  for(int i=1;i+d<=N;i++){
    int j = i+d;
    D[i][j] = INF;
    for(int k=K[i][j-1];k<=K[i+1][j];k++){
      int tmp = D[i][k] + D[k][j];
      if(D[i][j] > tmp){
        D[i][j] = tmp;
        K[i][j] = k;
      }
    }
    D[i][j] += C[i][j];
  }
}