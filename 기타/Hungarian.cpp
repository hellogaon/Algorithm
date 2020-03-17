// 헝가리안 알고리즘 : O(N^3)
// assignment problem : N명의 사람한테 중복없이 N개의 일을 부여하는 방식
// https://github.com/hongjun7/Competitive-Programming/blob/master/Library/C%2B%2B/Graph/hungarian.cpp
const int MAXN = 505;

int mat[MAXN][MAXN];
int mats[MAXN], matt[MAXN];
int Ls[MAXN], Lt[MAXN];
int revs[MAXN], revt[MAXN];
int valt[MAXN];
bool chks[MAXN], chkt[MAXN];

void init(int n){
  for(int i=1;i<=n;i++)
    Lt[i] = -INF;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      Lt[j] = max(Lt[j], mat[i][j]);
}

vector<int> Vu;
void vpush(int p, int n){
  chks[p] = 1;
  for(int i=1;i<=n;i++){
    if(!valt[i]) continue;
    if(valt[i] > Ls[p] + Lt[i] - mat[p][i]){
      valt[i] = Ls[p] + Lt[i] - mat[p][i];
      revt[i] = p;
      if(!valt[i]) Vu.pb(i);
    }
  }
}

pair<int, vector<pii> > hungarian(int n, int m){
  n = max(n, m);
  init(n);

  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++) chks[j] = chkt[j] = 0;
    for(int j=1;j<=n;j++) valt[j] = INF;
    for(int j=1;j<=n;j++) revs[j] = revt[j] = 0;	
    int p = n+1;
    for(int j=1;j<=n;j++)
      if(!mats[j]){
        p = j; break;
      }
    vpush(p, n);
    while(1){
      if(!Vu.empty()){
        int t = Vu.back();
        Vu.pop_back();
        chkt[t] = 1;
        if(!matt[t]){
          vector<int> Vu2;
          Vu2.pb(t);
          while(1){
            Vu2.pb(revt[Vu2.back()]);
            if(Vu2.back() == p) break;
            Vu2.pb(revs[Vu2.back()]);
          }
          reverse(Vu2.begin(), Vu2.end());
          for(int j=0;j<Vu2.size();j+=2){
            int s = Vu2[j], t = Vu2[j+1];
            mats[s] = t;
            matt[t] = s;
          }
          break;
        }
        else{
          int s = matt[t];
          revs[s] = t;
          vpush(s, n);
        }
      }
      else{
        int mn = INF;
        for(int j=1;j<=n;j++)
          if(!chkt[j]) mn = min(mn, valt[j]);
        for(int j=1;j<=n;j++){
          if(chks[j]) Ls[j] -= mn;
          if(chkt[j]) Lt[j] += mn;
          else{
            valt[j] -= mn;
            if(valt[j] == 0) Vu.pb(j);
          }
        }
      }
    }
    Vu.clear();
  }

  int ans = 0;
  vector<pii> ret;
  for(int i=1;i<=n;i++){
    ans += Ls[i] + Lt[i];
    if(mat[i][mats[i]]) ret.pb(mp(i,mats[i]));
  }
  return mp(ans, ret);
}