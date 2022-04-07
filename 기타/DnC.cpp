//Divide & Conquer Optimization: O(KNlgN)
//D(t,i) = min(k<i){ D(t-1,k) + C(k,i) }
//조건 1) C함수가 quadrangle inequality를 만족
//a≤b≤c≤d일 때 C(a,c)+C(b,d) ≤ C(a,d)+C(b,c)
//K[t][i] = D[t][i]가 최소가 되기 위한 가장 작은 k일 때
//위 조건을 만족할 경우
//K[t][i] ≤ K[t][i+1]이므로 분할정복을 이용하여 계산
const int MAXK = 501;
const int MAXN = 501;
ll D[MAXK][MAXN], K[MAXK][MAXN], C[MAXK][MAXN];

void dnc(int t, int l, int r, int s, int e){
  if(l > r || s > e) return;
  int m = (l+r)/2;
  for(int k=s;k<=e&&k<m;k++){
    ll tmp = D[t-1][k] + C[k][m]; 
    if(D[t][m] > tmp){
      D[t][m] = tmp;
      K[t][m] = k;
    }
  }
  dnc(t, l, m-1, s, K[t][m]);
  dnc(t, m+1, r, K[t][m], e);
}


for(int j=0;j<N;j++)
  D[1][j] = C[0][j];
    
for(int i=2;i<=K;i++)
  for(int j=0;j<N;j++)
    D[i][j] = INF;

for(int t=2;t<=K;t++)
  dnc(t, 0, N-1, 0, N-1);
