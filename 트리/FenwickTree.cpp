//팬윅트리 - 빠르고 간단한 구간 합
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

struct Fenwicktree {
  vector<ll> tree;
  Fenwicktree(int n) : tree(n+1) {}
  // sum(pos) : A[0...pos] 의 부분 합을 구한다.
  // 맨 오른쪽에 있는 1인 비트를 지우는 연산
  ll sum(int pos){
    ++pos;
    ll ret = 0;
    while(pos > 0){
      ret += tree[pos];
      pos &= (pos-1);
    }
    return ret;
  }
  // A[pos]에 val을 더한다.
  // 맨 오른쪽애 있는 1인 비트를 스스로에게 더해 주는 연산
  void add(int pos, ll val){
    ++pos;
    while(pos < tree.size()){
      tree[pos] += val;
      pos += (pos & -pos);
    }
  }
};

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  vector<int> v(N+1);
  Fenwicktree tree(N+1);
  for(int i=0;i<M;i++){
    int A,B,C;
    scanf("%d %d %d",&A,&B,&C);
    if(A == 0){
      if(B > C) swap(B,C);
      printf("%lld\n",tree.sum(C)-tree.sum(B-1));
    }
    else{
      tree.add(B,C-v[B]);
      v[B] = C;
    }
  }
}

