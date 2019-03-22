//투포인터
while(1){
  if(sum >= M) sum -= A[lo++];
  else if(hi == N) break;
  else sum += A[hi++];
  if(sum == M) ans++;
}