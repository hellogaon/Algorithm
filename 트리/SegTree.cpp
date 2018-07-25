//세그먼트 트리 with Lazy
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
const int MAX_INT = 987654321;

struct SegTree{
  int n;
  //각 구간의 합
  vector<int> rangeSum;
  vector<int> lazy;
  SegTree(const vector<int>& array){
    n = array.size();
    rangeSum.resize(n * 4);
    lazy.resize(n * 4);
    init(array, 0, n-1, 1);
  }
  //node노드가 array[left..right]배열을 표현할 때
  //node를 루트로 하는 서브트리를 초기화하고 이 구간의 합을 반환
  int init(const vector<int>& array, int left, int right, int node){
    if(left == right) return rangeSum[node] = array[left];
    int mid = (left + right) / 2;
    int leftSum = init(array, left, mid, node*2);
    int rightSum = init(array, mid+1, right, node*2+1);
    return rangeSum[node] = leftSum + rightSum;
  }
  //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
  //이 범위와 array[left..right]의 교집합의 합을 구한다.
  int query(int left, int right, int node, int nodeLeft, int nodeRight){
    update_lazy(nodeLeft,nodeRight,node);
    if(right < nodeLeft || nodeRight < left) return 0;
    if(left <= nodeLeft && nodeRight <= right) return rangeSum[node];
    int mid = (nodeLeft + nodeRight) / 2;
    return query(left, right, node*2, nodeLeft, mid) + query(left, right, node*2+1, mid+1, nodeRight);
  }
  int query(int left, int right){
    return query(left, right, 1, 0, n-1);
  }
  //array[index]=newValue로 바뀌었을 때 node를 루트로 하는 구간트리를 갱신
  int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
    if(index < nodeLeft || nodeRight < index) return rangeSum[node];
    if(nodeLeft == nodeRight) return rangeSum[node] = newValue;
    int mid = (nodeLeft + nodeRight) / 2;
    return rangeSum[node] = update(index, newValue, node*2, nodeLeft, mid) + update(index, newValue, node*2+1, mid+1, nodeRight);
  }
  int update(int index, int newValue){
    return update(index, newValue, 1, 0, n-1);
  }
  void update_lazy(int left, int right, int node){
    // lazy값이 존재 할 경우
    if(lazy[node] != 0){
      rangeSum[node] += (right-left+1)*lazy[node];
      // 리프노드가 아니면 자식에게 lazy를 미룬다.
      if(left != right){
        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
      }
      lazy[node] = 0;
    }
  }
  // left~right구간을 diff만큼 증가하였을 때 node를 루트로 하는 구간트리를 갱신
  void update_range(int left, int right, int diff, int node, int nodeLeft, int nodeRight){
    update_lazy(nodeLeft,nodeRight,node);
    if(right < nodeLeft || nodeRight < left) return;
    if(left <= nodeLeft && nodeRight <= right){
      rangeSum[node] += (nodeRight-nodeLeft+1)*diff;
      if(nodeLeft != nodeRight){
        lazy[node*2] += diff;
        lazy[node*2+1] += diff;
      }
      return;
    }
    int mid = (nodeLeft + nodeRight) / 2;
    update_range(left, right, diff, node*2, nodeLeft, mid);
    update_range(left, right, diff, node*2+1, mid+1, nodeRight);
    // 마지막에 자식들의 값을 사용해 다시 자신의 값 갱신
    rangeSum[node] = rangeSum[node*2] + rangeSum[node*2+1];
  }
  void update_range(int left, int right, int diff){
    update_range(left, right, diff, 1, 0, n-1);
  }
};


int main(){
  int N,M,K;
  scanf("%d %d %d",&N,&M,&K);
  vector<int> arr;
  for(int i=0;i<N;i++){
    int X; scanf("%d",&X);
    arr.push_back(X);
  }
  SegTree* ST = new SegTree(arr);
  for(int i=0;i<M+K;i++){
    int a; scanf("%d",&a);
    if(a==1){
      int b,c,d;
      scanf("%d %d %d",&b,&c,&d);
      ST->update_range(b-1,c-1,d);
    }
    if(a==2){
      int b,c;
      scanf("%d %d",&b,&c);
      printf("%d\n",ST->query(b-1,c-1));
    }
  }
}
