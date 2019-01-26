#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define maxN 1000000

using namespace std;
 
typedef long long ll;

struct line{ // y = a*x + b
  ll a,b;
};
 
struct convexhull_trick{
  int s=0,e=0;
  int idx[maxN+5];
  line deq[maxN+5];
  double cross(int a, int b) {
    return 1.0 * (deq[a].b - deq[b].b) / (deq[b].a - deq[a].a);
  }
  void insert(line v,int line_idx){
    deq[e] = v;
    idx[e] = line_idx;
    while(s+1<e && cross(e - 2, e - 1) > cross(e - 1, e)){
      deq[e-1] = deq[e];
      idx[e-1] = idx[e];
      e--;
    }
    e++;
  }
  pair<ll,ll> query(ll x){  // query가 증가수열일 경우
    while(s+1<e && deq[s+1].b - deq[s].b >= x * (deq[s].a - deq[s+1].a))
        s++;
    return mp(deq[s].a*x+deq[s].b,idx[s]);
  }
  pair<ll,ll> query2(ll x){ // 일반 query
    int l = 0, r = e - 1;
    while (l != r) {
      int m = (l + r) / 2;
      if (cross(m, m + 1) <= x) l = m + 1;
      else r = m;
    }
    return mp(deq[l].a*x+deq[l].b,idx[l]);
  }
  void clear(){s = e = 0;}
}cht;

ll N,A,B,C;
ll X[maxN+5];
ll sum[maxN+5];
ll dp[maxN+5];

int main(){
    cht.clear();
    scanf("%lld %lld %lld %lld",&N,&A,&B,&C);
    for(int i=1;i<=N;i++){
      scanf("%lld",&X[i]);
      sum[i] = sum[i-1] + X[i];
    }
    line ins;
    ins.a = B;
    ins.b = 0;
    cht.insert(ins,0);
    for(int i=1;i<=N;i++){
      dp[i] = C+A*sum[i]*sum[i]+cht.query2(sum[i]).first;
      ins.a = -2*A*sum[i]+B;
      ins.b = dp[i]-B*sum[i]+A*sum[i]*sum[i];
      cht.insert(ins,i);
    }
    printf("%lld\n",dp[N]);
}