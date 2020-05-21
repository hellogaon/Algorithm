// Subset XOR Maximization
// N개의 원소를 가진 집합에서 XOR값을 최대로 하는 부분집합의 XOR를 구하는 문제
// 사다리꼴 행렬을 만들어 basis를 구한 뒤, 그리디 한 방법으로 이 basis를 사용할 지 말 지 결정
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fst first
#define snd second

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int INF = 987654321;
const int MOD = 1000000007;

ll A[100001];
ll basis[61];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;
  for(int i=0;i<N;i++)
    cin >> A[i];
  for(int i=0;i<N;i++){
    ll x = A[i];
    for(int j=60;j>=0;j--){
      if((x & (1LL << j)) > 0){
        if(!basis[j]){
          basis[j] = x;
          break;
        }
        else x ^= basis[j];
      }
    }
  }
  ll ans = 0;
  for(int i=60;i>=0;i--)
    ans = max(ans, ans ^ basis[i]);
  cout << ans << '\n';
}