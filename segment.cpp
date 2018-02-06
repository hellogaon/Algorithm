//세그먼트트리
//리프노드: 배열의 그 수 자체
//다른노드: 왼쪽 자식과 오른쪽 자식의 합을 저장
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

long long init(vector<long long> &a, vector<long long> &tree, int node, int start, int end){ //초기 트리 생성
  if(start==end) return tree[node]=a[start];
  return tree[node]=init(a,tree,node*2,start,(start+end)/2)+init(a,tree,node*2+1,(start+end)/2+1,end);
}
long long update(vector<long long> &tree, int node, int start, int end, int index, long long diff){
  if(index<start || index>end) return tree[node];
  if(start==end) return tree[node]=diff;
  return tree[node] = update(tree,node*2,start,(start+end)/2,index,diff)+update(tree,node*2+1,(start+end)/2+1,end,index,diff);
}
// node가 담당하는 구간이 start~end이고, 구해야하는 합의 범위는 left~right  
long long sum(vector<long long> &tree, int node, int start, int end, int left, int right){
  if(left>end || right<start) return 0;
  if(left<=start && end<=right) return tree[node];
  return sum(tree,node*2,start,(start+end)/2,left,right)+sum(tree,node*2+1,(start+end)/2+1,end,left,right);
}

int main(){
  int N,M,K; //수의 개수 N, 수의 변경 M, 구간의 합 K
  scanf("%d %d %d",&N,&M,&K);
  vector<long long> a(N);
  int H = (int)ceil(log2(N));
  int tree_size = (1<<(H+1)); //필요한 배열의 크기 = 2^(H+1)-1;
  vector<long long> tree(tree_size);
  for(int i=0;i<N;i++) scanf("%lld",&a[i]);
  init(a,tree,1,0,N-1); //tree[1]에 a[0]~a[N-1]까지의 합
  int all = M+K;
  while(all--){
    int A;
    scanf("%d",&A);
    if(A==1){ //수의 변경 b번째 수를 c로 바꾼다
      int B; long long C;
      scanf("%d %lld",&B,&C);
      B--; a[B]=C; 
      update(tree,1,0,N-1,B,C);
    }
    else if(A==2){ //배열의 합 b부터 c까지의 합을 출력
      int B,C;
      scanf("%d %d",&B,&C);
      printf("%lld\n",sum(tree,1,0,N-1,B-1,C-1));
    }
  }
}