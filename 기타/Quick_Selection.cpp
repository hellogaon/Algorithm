//Quick_Selection 구현
//nth_element
#include <cstdio>

int N,K,arr[5000001];

void swap(int * ptr1, int * ptr2){
  int temp=*ptr1;
  *ptr1=*ptr2;
  *ptr2=temp;
}

int partition(int * arr, int left, int right, int pivot){
  int idx = left, pivotVal = arr[pivot];
  swap(&arr[pivot],&arr[right]);
  for(int i=left;i<right;i++){
    if(arr[i]<pivotVal)
      swap(&arr[i],&arr[idx++]);
  }
  swap(&arr[idx],&arr[right]);
  return idx;
}

int Quick_Selection(int * arr, int left, int right, int k){
  while(left <= right){
    int pivotIdx = partition(arr,left,right,(left+right)/2);
    if(pivotIdx==k) return arr[pivotIdx];
    else if(pivotIdx<k) left = pivotIdx+1;
    else right = pivotIdx-1;
  }
  return 0;
}

int main(){
  int N,K;
  scanf("%d %d",&N,&K);
  for(int i=0;i<N;i++)
    scanf("%d",&arr[i]);
  printf("%d\n",Quick_Selection(arr,0,N-1,K-1));;
}
