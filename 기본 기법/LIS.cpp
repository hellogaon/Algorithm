// LIS : O(NlogN)
// LIS의 마지막 값이 추가하는 배열의 값보다 작으면 추가.
// 그렇지 않으면 추가하는 배열의 값보다 큰 수 중 가장 작은 수와 교체.
// path[i] = LIS에서 i가 몇번 째에 있었는 지.
const int MAXN = 10000001;

vector<int> v(MAXN); 
vector<int> path(MAXN);

int LIS(vector<int>& a, int n){
  vector<int> lis;
  for(int i=0;i<n;i++){
    auto it = lower_bound(lis.begin(),lis.end(),a[i]);
    path[i] = (int)(it-lis.begin())+1;
    if(it == lis.end()) lis.pb(a[i]);
    else *it = a[i];
  }
  return (int)lis.size();
}

void getpath(vector<int>& a, int lis, int n){
  stack<int> s;
  int idx = n-1;
  for(int i=lis;i>0;idx--){
    if(path[idx]==i){
      s.push(a[idx]); i--;
    }
  }
  while(!s.empty()){
    printf("%d ",s.top());
    s.pop();
  }
  printf("\n");
}

int main(){
  int N;
  scanf("%d",&N);
  for(int i=0;i<N;i++)
    scanf("%d",&v[i]);
  int ans = LIS(v,N);
  printf("%d\n",ans);
  getpath(v,ans,N);
}