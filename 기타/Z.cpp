// Z 알고리즘 - p[i] = 0 ≤ i < n인 i에 대해 pi를 S[0..k]=S[i..i+k]인 가장 큰 k의 값 : O(N)
// r = 현재까지 발견된 가장 오른쪽에서 끝나는 점
// l = 그 때의 i 값
const int MAXN = 2000001;

int S[MAXN], p[MAXN];

void prefix(int len){
  int l = 0, r = 0;
  for(int i=1;i<len;i++){
    if(i <= r) p[i] = min(r-i, p[i-l]);
    while(i+p[i]+1 < len && S[p[i]+1] == S[i+p[i]+1]) p[i]++;
    if(r < i+p[i]) r = i+p[i], l = i;
  }
}
