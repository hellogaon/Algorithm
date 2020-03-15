// Manacher - 펠린드롬 판별 알고리즘 : O(N)
// r = 현재까지 발견된 가장 오른쪽에서 끝나는 팰린드롬의 끝 점
// k = 그 때의 i 값
const int MAXN = 2000001;

int S[MAXN*2+1], p[MAXN*2+1];

void manacher(int len){
  len = len*2+1;
  for(int i=len-1;i>=0;i--){
    if(i % 2 == 0) S[i] = -1;
    else S[i] = S[i/2];
  }
  int r = 0, k = 0;
  for(int i=0;i<len;i++){
    // 2*k-i와 대칭이므로 구해온 값 사용
    if(i <= r) p[i] = min(p[2*k-i], r-i);
    // 양 끝을 넓혀가며 확인
    while(i-p[i] > 0 && i+p[i]+1 < len && S[i-p[i]-1] == S[i+p[i]+1]) p[i]++;
    // r, k 업데이트
    if(r < i+p[i]) r = i+p[i], k = i;
  }
}