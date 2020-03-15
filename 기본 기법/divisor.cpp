//약수의 개수, 합 구하기 - O(Nsqrt(N))
const int MAXN = 1000000;

for(int i=1;i<=MAXN;i++){
  for(int j=1;j<=MAXN/i;j++)
    cnt[i*j]++;
}

for(int i=1;i<=MAXN;i++){
  for(int j=1;j<=MAXN/i;j++)
    sum[i*j] += i;
}