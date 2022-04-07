// Persistent LiCho Tree with Dynamic Segment Tree
// 직선이 실시간으로 추가되는 Convex Hull Trick을 해결하기 위한 자료구조

// X가 문제에서 주어진 x좌표의 범위의 길이일 때,
// 1) 직선 y = ax + b를 집합에 추가 - O(lgX)
// 2) 집합에 존재하는 직선 중, x위치에서의 최댓값 출력 - O(lgX)
// 3) 가장 최근에 삽입한 직선을 삭제 (Persistent Rollback) - O(lgX)
// http://www.secmem.org/blog/2019/01/03/lichao-tree/
// https://panty.run/dynamic-lichao-tree/

struct Line{
  ll a, b;
  Line(ll a1, ll b1): a(a1), b(b1) {}
  
  ll f(ll x){
    return a * x + b;
  }
};

struct Node{
  // 왼쪽, 오른쪽 자식 번호 (없으면 -1)
  int left, right;
  // 해당 노드가 담당하는 x의 촤소, 최댓값
  ll s, e;
  Line l;  
};

// struct Info{
//   int left, right;
//   ll a,b;
// }

struct LiChoTree{
  vector<Node> tree;
  ll LONG_INF = 2e18;

  // int idx = 0; 
  // map<int, vector<pair<int, Info> > > change;

  LiChoTree(ll x_min, ll x_max){
    tree.pb({-1, -1, x_min, x_max, {0, -LONG_INF}});
  }

  void insert(int n, Line l){
    ll s = tree[n].s, e = tree[n].e;
    ll m = (s + e) >> 1;

    // change[idx].pb({n, {tree[n].left, tree[n].right, tree[n].l.a, tree[n].l.b}});
    
    Line low = tree[n].l, high = l;
    if(low.f(s) > high.f(s)) swap(low, high);

    if(low.f(e) <= high.f(e)){
      tree[n].l = high;
      return;
    }
    else if(low.f(m) < high.f(m)){
      tree[n].l = high;
      if(tree[n].right == -1){
        tree[n].right = tree.size();
        tree.pb({-1, -1, m+1, e, {0, -LONG_INF}});
      }
      insert(tree[n].right, low);
    }
    else{
      tree[n].l = low;
      if(tree[n].left == -1){
        tree[n].left = tree.size();
        tree.pb({-1, -1, s, m, {0, -LONG_INF}});
      }
      insert(tree[n].left, high);
    }
  }
  void insert(Line l){
    insert(0, l);
    idx++;
  }

  ll query(int n, ll x){
    if(n == -1) return -LONG_INF; 

    ll s = tree[n].s, e = tree[n].e;
    ll m = (s + e) >> 1;
    
    if(x <= m) return max(tree[n].l.f(x), query(tree[n].left, x));
    return max(tree[n].l.f(x), query(tree[n].right, x));
  }
  ll query(ll x){
    return query(0, x);
  }

  // void del(){
  //   for(auto& [n, info]: change[--idx]){
  //     tree[n].left = info.left;
  //     tree[n].right = info.right;
  //     tree[n].l.a = info.a;
  //     tree[n].l.b = info.b;
  //   }
  //   change[idx].clear();
  // }
};