// 비트마스크 응용
#include <cstdio>

int bitCount(int x){
  if(x == 0) return 0;
  return x % 2 + bitCount(x / 2);
}

int main(){
  int pizza, toppings;
  // 최소 원소 찾기
  int firstTopping = (toppings & -toppings);
  // 최소 원소 지우기
  toppings &= (toppings - 1);
  // 모든 부분 집합 순회
  for(int subset = pizza; subset; subset = ((subset-1) & pizza)){
    // subset은 pizza의 부분 집합
  }
}
