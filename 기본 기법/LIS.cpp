// LIS : O(NlogN)
// LIS의 마지막 값이 추가하는 배열의 값보다 작으면 추가.
// 그렇지 않으면 추가하는 배열의 값보다 큰 수 중 가장 작은 수와 교체.
// path[i] = LIS에서 i가 몇번 째에 있었는 지.
const int MAXN = 10000001;

int N,A[MAXN],path[MAXN];

int LIS(){
  vector<int> lis;
  for(int i=0;i<N;i++){
    auto it = lower_bound(lis.begin(), lis.end(), A[i]);
    path[i] = (int)(it-lis.begin())+1;
    if(it == lis.end()) lis.pb(A[i]);
    else *it = A[i];
  }
  return (int)lis.size();
}

vector<int> getpath(int lis){
  stack<int> s;
  int idx = N-1;
  for(int i=lis;i>0;idx--){
    if(path[idx] == i){
      s.push(A[idx]); i--;
    }
  }
  vector<int> ret;
  while(!s.empty()){
    ret.pb(s.top());
    s.pop();
  }
  return ret;
}