// LIS NlogN
// LIS의 마지막 값이 추가하는 배열의 값보다 작으면 추가.
// 그렇지 않으면 추가하는 배열의 값보다 큰 수 중 가장 작은 수와 교체.
// path[i] = LIS에서 i가 몇번 째에 있었는 지.
// 이후 뒤에서부터 보면서 출력.
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

vector<int> v;
int N, arr[1000001], path[1000001];

int main(){
  scanf("%d",&N);
  for(int i=0;i<N;i++){
    scanf("%d",&arr[i]);
    auto it = lower_bound(v.begin(),v.end(),arr[i]);
    path[i] = (int)(it-v.begin())+1;
    if(it==v.end()) v.push_back(arr[i]);
    else *it = arr[i];
  }
  printf("%lu\n",v.size());

  //경로 탐색
  stack<int> s;
  int idx = N-1;
  for(int i=v.size();i>0;idx--){
    if(path[idx]==i){
      s.push(arr[idx]); i--;
    }
  }
  while(!s.empty()){
    printf("%d ",s.top());
    s.pop();
  }
  printf("\n");
}
