const double PI = 2.0 * acos(0.0);

struct vector2{
  double x,y;
  explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){}
  bool operator == (const vector2& rhs) const{
    return x == rhs.x && y == rhs.y;
  }
  bool operator < (const vector2& rhs) const{
    return x != rhs.x ? x < rhs.x : y < rhs.y;
  }
  //벡터의 덧셈과 뺄셈
  vector2 operator + (const vector2& rhs) const{
    return vector2(x + rhs.x, y + rhs.y);
  }
  vector2 operator - (const vector2& rhs) const{
    return vector2(x - rhs.x, y - rhs.y);
  }
  vector2 operator * (double rhs) const{
    return vector2(x * rhs, y * rhs);
  }
  //벡터의 길이 반환
  double norm() const{
    return hypot(x, y);
  }
  //단위벡터 (영벡터 제외)
  vector2 normalize() const{
    return vector2(x/norm(),y/norm());
  }
  //x축 양의 방향부터 이 벡터까지 반시계 방향으로 잰 각도
  double polar() const{
    return fmod(atan2(y, x) + 2*PI, 2*PI);
  }
  //내적 외적
  double dot(const vector2& rhs) const{
    return x * rhs.x + y * rhs.y;
  }
  double cross(const vector2& rhs) const{
    return x * rhs.y - rhs.x * y;
  }
  //사영한 결과
  vector2 project(const vector2& rhs) const{
    vector2 r = rhs.normalize();
    return r * r.dot(*this);
  }
};

//세 점 p,a,b가 주어졌을 때, a가 b보다 p에 얼마나 더 가까운 지
double closer(vector2 p, vector2 a, vector2 b){
  return (b - p).norm() - (a - p).norm();
}

//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환
double ccw(vector2 a, vector2 b){
  return a.cross(b);
}

//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0
double ccw(vector2 p, vector2 a, vector2 b){
  return ccw(a-p, b-p);
}

//(a,b)를 포함하는 선과 (c,d)를 포함하는 선의 교점을 x에 반환
//두 선이 평행이면 거짓, 아니면 참
const double EPSILON = 1e-9;
bool lineIs(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x){
  double det = (b - a).cross(d - c);
  if(fabs(det) < EPSILON) return false;
  x = a + (b - a) * ((c - a).cross(d - c) / det);
  return true;
}

//(a,b) (c,d)가 평행한 두 선분일 때 이들이 겹치는 지 확인
//겹칠 경우 선분의 교점을 p에 반환
bool paraSeg(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p){
  if(b < a) swap(a, b);
  if(d < c) swap(c, d);
  //한 직선 위에 없거나 두 선분이 겹치지 않는 경우
  if(ccw(a, b, c)!=0 || b < c || d < a) return false;
  // 교차점 찾기
  if(a < c) p = c; else p = a;
  return true;
}
//a,b,p가 일직선에 있다고 가정 할 때, a,b를 잇는 선분위에 p가 있는 지
bool inSeg(vector2 p, vector2 a, vector2 b){
  if(b < a) swap(a, b);
  return p==a || p==b || (a<p && p<b);
}
//(a,b)선분과 (c,d)선분의 교점을 p에 반환
//교점이 여러 개일 경우 아무 점 이나 반환
//두 선분이 교차하지 않을 경우 false를 반환
bool segIs(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p){
  //두 직선이 평행인 경우
  if(!lineIs(a, b, c, d, p))
    return paraSeg(a, b, c, d, p);
  //p가 두 선분에 포함되어 있는 경우에만 참
  return inSeg(p, a, b) && inSeg(p, c, d);
}

//두 선분이 서로 접촉하는 지 여부를 반환
bool segIs2(vector2 a, vector2 b, vector2 c, vector2 d){
  double ab = ccw(a, b, c) * ccw(a, b, d);
  double cd = ccw(c, d, a) * ccw(c, d, b);
  //두 선분이 한 직선 위에 있거나 끝 점이 겹치는 경우
  if(ab==0 && cd==0){
    if(b < a) swap(a, b);
    if(d < c) swap(c, d);
    return !(b<c || d<a);
  }
  return ab<=0 && cd<=0;
}

//점 p에서 (a,b) 직선에 내린 수선의 발
vector2 foot(vector2 p, vector2 a, vector2 b){
  return a + (p-a).project(b-a);
}
//점 p와 (a,b) 직선 사이의 거리
double dist(vector2 p, vector2 a, vector2 b){
  return (p - foot(p, a, b)).norm();
}

//주어진 단순 사각형 p의 넓이 p는 각 꼭지점의 위치 벡터의 집합
double area(const vector<vector2>& p){
  double ret = 0;
  for(int i=0;i<p.size();i++){
    int j=(i+1)%p.size();
    ret += p[i].x * p[j].y - p[j].x * p[i].y;
  }
  return fabs(ret) / 2.0;
}

//점 q가 다각형 p안에 포함되어 있을 경우 참, 아닌 경우 거짓
//q가 다각형의 경계 위에 있는 경우의 반환 값은 정의 X
bool isIn(vector2 q, const vector<vector2>& p){
  int crosses = 0;
  for(int i=0;i<p.size();i++){
    int j = (i+1)%p.size();
    if((p[i].y > q.y) != (p[j].y > q.y)){
      double atX = (p[j].x - p[i].x) * (q.y - p[i].y) /
                    (p[j].y - p[i].y) + p[i].x;
      if(q.x < atX)
        crosses++;
    }
  }
  return crosses % 2 > 0;
}

//두 다각형이 서로 닿거나 겹치는 지 여부를 반환
//한 점이라도 겹친다면 true
bool polyIs(const polygon& p, const polygon& q){
  int n=p.size(), m=q.size();
  //한 다각형이 다른 다각형에 포함되어 있는 경우
  if(isIn(p[0],q) || isIn(q[0],p)) return true;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      if(segIs2(p[i], p[(i+1)%n],q[j], q[(j+1)%m]))
        return true;
  return false;
}

//서덜랜드 호지맨 알고리즘을 이용한 다각형 클리핑
typedef vector<vector2> polygon;
//(a,b)를 포함하는 직선으로 다각형 p를 자른 뒤, (a,b)의 왼쪽에 있는 부분 반환
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b){
  int n=p.size();
  vector<bool> inside(n);
  for(int i=0;i<n;i++)
    inside[i]=ccw(a, b, p[i]) >= 0;
  polygon ret;
  for(int i=0;i<n;i++){
    int j=(i+1)%n;
    if(inside[i]) ret.pb(p[i]);
    if(inside[i]!=inside[j]){
      vector2 cross;
      if(lineIs(p[i], p[j], a, b, cross))
        ret.pb(cross);
    }
  }
  return ret;
}
polygon Is(const polygon& p, double x1, double y1, double x2, double y2){
  vector2 a(x1, y1),b(x2, y1),c(x2, y2),d(x1, y2);
  polygon ret = cutPoly(p, a, b);
  ret = cutPoly(ret, b, c);
  ret = cutPoly(ret, c, d);
  ret = cutPoly(ret, d, a);
  return ret;
}

//볼록 껍질을 찾는 그라함스캔 알고리즘
//시간복잡도 O(NlogN)
typedef vector<vector2> polygon;
//points에 있는 점들을 모두 포함하는 최소의 볼록다각형
vector2 pivot;
bool cmp(const vector2& a, const vector2& b){
  double val = ccw(pivot, a, b);
  if(val > 0) return true;
  if(val < 0) return false;
  return (a-pivot).norm() < (b-pivot).norm();
}
polygon grahamScan(vector<vector2>& points){
  int n = points.size();
  //pivot점을 제일 아래 제일 왼쪽으로 지정
  int leastY = 0;
  for(int i=1;i<n;i++){
    if(points[i].y < points[leastY].y)
      leastY = i;
    else if(points[i].y == points[leastY].y)
      if(points[i].x < points[leastY].x)
        leastY = i;
  }
  swap(points[0], points[leastY]);
  pivot = points[0];
  //0번을 제외한 점들을 반시계 방향으로 정렬
  sort(points.begin()+1, points.end(), cmp);
  // 많은 점들을 볼록껍질로 가지고 싶을 경우
  // int idx = n-1;
  // for(;idx>=1;idx--) if(ccw(pivot, points[idx], points[idx-1])) break;
  // reverse(points.begin()+idx, points.end());
  polygon hull;
  for(int i=0;i<n;i++){
    //스택에 2개 이상의 점이 남아 있는 한 스택 최상단 점 2개와 다음 점의 관계가 CCW일 때까지 pop
    while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), points[i]) <= 0)
      hull.pop_back();
    hull.pb(points[i]);
  }
  return hull;
}

//불록 다각형의 지름을 재는 회전하는 캘리퍼스 알고리즘
//시계 반대 방향으로 주어진 볼록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환
double diameter(const polygon& p){
  int n = p.size();
  int left = min_element(p.begin(), p.end())-p.begin();
  int right = max_element(p.begin(), p.end())-p.begin();
  vector2 calipersA;
  double ret = (p[right]-p[left]).norm();
  vector<vector2> toNext(n);
  for(int i=0;i<n;i++)
    toNext[i] = p[(i+1)%n]-p[i];
  int a = left, b = right;
  for(int i=0;i<p.size();i++){
    if(toNext[a].cross(toNext[b]) <= 0){
      //thetaA < thetaB
      calipersA = toNext[a];
      a = (a + 1) % n;
    }
    else{
      calipersA = toNext[b] * (-1.0);
      b = (b + 1) % n;
    }
    ret = max(ret, ((p[a]-p[b]).norm()));
  }
  return ret;
}
