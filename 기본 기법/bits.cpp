// 비트마스크 응용
//집합에 포함된 원소의 수 : __builtin_popcount(S)
//집합에 포함된 최하위 비트 번호 : __builtin_ctz(S)

// 1 ~ N까지의 수를 이진수로 표현했을 때 1의 개수 합 구하기
ll sum(ll N){
  ll tmp = 2, ret = 0, n = N;
  while(n){
    ret += (N/tmp) * (tmp/2);
    if((N&(tmp-1)) > (tmp/2)-1) ret += (N&(tmp-1)) - (tmp/2) + 1;
    tmp *= 2; n /= 2;    
  }
  return ret;
}