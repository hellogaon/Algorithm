// 문자열 조합 개수
// 같은 숫자가 여러 개 남아있다면 그 중 가장 먼저 오는 것만 선택
// 1. 없거나 2. 이번 자리수랑 다르거나 3. 이미 사용되었을 경우에만 선택
string e,digits;
int n;
bool taken[15];

void perm(string price, bool taken[15]){
  if(price.size()==n){
    cout << price << endl;
    return;
  }
  for(int i=0;i<n;i++){
    if(!taken[i] && (i==0 || digits[i-1] != digits[i] || taken[i-1])){
      taken[i] = true;
      perm(price + digits[i], taken);
      taken[i] = false;
    }
  }
}

int main(){
  cin >> e;
  n = e.size();
  digits = e;
  sort(digits.begin(),digits.end());
  perm("",taken);
}
