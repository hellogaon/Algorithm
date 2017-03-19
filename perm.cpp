//조합 출력. 순서대로는 아니다!
//N개의 숫자 중에 K개를 골라 조합을 구현한다.
#include <cstdio>

using namespace std;

int N,K;

void print(int * arr){
  for(int i=0;i<K;i++)
    printf("%d ",arr[i]);
  printf("\n");
}

void swap(int * arr, int i, int j){
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void perm(int * arr, int depth){
  if(depth == K){
    print(arr);
    return;
  }
  for(int i=depth;i<N;i++){
    swap(arr,i,depth);
    perm(arr,depth+1);
    swap(arr,i,depth);
  }
}

int main(){
  int arr[4]={1,2,3,4};
  N=4, K=4;
  perm(arr,0);
}
