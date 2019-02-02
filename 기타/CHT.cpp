//CHT - Convex Hull Trick: O(NlgN)
//dp(i) = min(0≤j<i){ dp(j) + a[i]b[j] }
struct Line{ // f(x) = ax + b, x >= s
  ll a,b;
  double s;
  Line(): a(1), b(0), s(0) {}
  Line(ll a1, ll b1): a(a1), b(b1), s(0) {}
};

//두 직선 f, g의 교점의 x좌표를 구함
double cross(Line &f, Line &g){
  return (double)(g.b-f.b)/(f.a-g.a);
}

struct CHT{
  vector<Line> f;
  int n, top;

  CHT(int num){
    n = num; top = 0; f.resize(n);
  }

  void insert(Line g){
    while(top > 0){
      g.s = cross(g,f[top-1]);
      if(f[top-1].s < g.s) break;
      // 쌓기 전에 top과 교점을 구해서 top의 시작점보다 교점이 앞일 경 pop
      --top;
    }
    f[top++] = g;
  }
  
  //주어진 x좌표를 포함하는 선분의 번호(fpos)를 이분탐색으로 찾음
  ll query(int x){
    int fpos = top-1;
    if(x < f[top-1].s){
      int lo = 0, hi = top-1;
      while(lo+1 < hi){
        int mid = (lo+hi)/2;
        if(x < f[mid].s)
          hi = mid;
        else
          lo = mid;
      }
      fpos = lo;
    }
    return f[fpos].a * x + f[fpos].b;
  }
};