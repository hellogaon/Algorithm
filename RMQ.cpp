//RMQ 구간 최소 쿼리
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();

struct RMQ{
  int n;
  //각 구간의 최소치
  vector<int> rangeMin;
  RMQ(const vector<int>& array){
    n = array.size();
    rangeMin.resize(n * 4);
    init(array, 0, n-1, 1);
  }
  //node노드가 array[left..right]배열을 표현할 때
  //node를 루트로 하는 서브트리를 초기화하고 이 구간의 최소치를 반환
  int init(const vector<int>& array, int left, int right, int node){
    if(left == right) return rangeMin[node] = array[left];
    int mid = (left + right) / 2;
    int leftMin = init(array, left, mid, node*2);
    int rightMin = init(array, mid+1, right, node*2+1);
    return rangeMin[node] = min(leftMin, rightMin);
  }
  //node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
  //이 범위와 array[left..right]의 교집합의 최소치를 구한다.
  int query(int left, int right, int node, int nodeLeft, int nodeRight){
    if(right < nodeLeft || nodeRight < left) return MAX_INT;
    if(left <= nodeLeft && nodeRight <= right) return rangeMin[node];
    int mid = (nodeLeft + nodeRight) / 2;
    return min(query(left, right, node*2, nodeLeft, mid),
                query(left, right, node*2+1, mid+1, nodeRight));
  }
  int query(int left, int right){
    return query(left, right, 1, 0, n-1);
  }
  //array[index]=newValue로 바뀌었을 때 node를 루트로 하는 구간트리를 갱신
  int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
    if(index < nodeLeft || nodeRight < index) return rangeMin[node];
    if(nodeLeft == nodeRight) return rangeMin[node] = newValue;
    int mid = (nodeLeft + nodeRight) / 2;
    return rangeMin[node] = min(
      update(index, newValue, node*2, nodeLeft, mid),
      update(index, newValue, node*2+1, mid+1, nodeRight));
  }
  int update(int index, int newValue){
    return update(index, newValue, 1, 0, n-1);
  }
};
