// 세그비츠
// break-condition이나 tag-condition에 걸리지 않는 경우가 적어야 함 (구간에서 다른 성질을 가지는 값들이 빠르게 줄어들어야 함)
// A[i] = min(A[i], X) (L <= i <= R)
// max(Ai) (L <= i <= R)
// sum(Ai) (L <= i <= R)
struct Node{
  ll mx, mx2, cntmx, sum;
};

struct SegTreeBeats{
  int n;
  vector<Node> tree;

  SegTreeBeats(ll *arr, int siz){
    n = siz;
    tree.resize(4 * n);
    init(arr, 1, 0, n-1);
  }

  Node merge(Node a, Node b){
    if(a.mx == b.mx) return {a.mx, max(a.mx2, b.mx2), a.cntmx + b.cntmx, a.sum + b.sum};
    if(a.mx < b.mx) swap(a, b);
    return {a.mx, max(a.mx2, b.mx), a.cntmx, a.sum + b.sum};
  }

  Node init(ll* arr, int node, int nl, int nr){
    if(nl == nr) return tree[node] = {arr[nl], -INF, 1, arr[nl]};
    int mid = (nl+nr)/2;
    return tree[node] = merge(init(arr, node*2, nl, mid), init(arr, node*2+1, mid+1, nr));
  }

  void push(int node, int l, int r){
    if(l == r) return;
    for(auto i : {node*2, node*2+1})
      if(tree[node].mx < tree[i].mx){
        tree[i].sum -= tree[i].cntmx * (tree[i].mx - tree[node].mx);
        tree[i].mx = tree[node].mx;
      }
  }

  void update(int l, int r, ll v, int node, int nl, int nr){
    push(node, nl, nr);
    if(r < nl || nr < l || tree[node].mx <= v) return;
    if(l <= nl && nr <= r && tree[node].mx2 < v){
      // 현재 node에 lazy값을 준 뒤 push
      tree[node].sum -= tree[node].cntmx * (tree[node].mx - v);
      tree[node].mx = v;
      push(node, nl, nr);
      return;
    }
    int mid = (nl+nr)/2;
    update(l, r, v, node*2, nl, mid);
    update(l, r, v, node*2+1, mid+1, nr);
    tree[node] = merge(tree[node*2], tree[node*2+1]);
  }
  void update(int l, int r, ll v){
    update(l, r, v, 1, 0, n-1);
  }

  ll mx_query(int l, int r, int node, int nl, int nr){
    push(node, nl, nr);
    if(r < nl || nr < l) return 0LL;
    if(l <= nl && nr <= r) return tree[node].mx;
    int mid = (nl+nr)/2;
    return max(mx_query(l, r, node*2, nl, mid), mx_query(l, r, node*2+1, mid+1, nr));
  }
  ll mx_query(int l, int r){
    return mx_query(l, r, 1, 0, n-1);
  }

  ll sum_query(int l, int r, int node, int nl, int nr){
    push(node, nl, nr);
    if(r < nl || nr < l) return 0LL;
    if(l <= nl && nr <= r) return tree[node].sum;
    int mid = (nl+nr)/2;
    return sum_query(l, r, node*2, nl, mid) + sum_query(l, r, node*2+1, mid+1, nr);
  }
  ll sum_query(int l, int r){
    return sum_query(l, r, 1, 0, n-1);
  }
};