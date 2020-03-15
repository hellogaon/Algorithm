struct SegTree{
  int n;
  vector<ll> sum;
  SegTree(ll *arr, int siz){
    n = siz;
    sum.resize(4 * n);
    init(arr, 1, 0, n-1);
  }
  
  ll init(ll *arr, int node, int nl, int nr){
    if(nl == nr) return sum[node] = arr[nl];
    int mid = (nl+nr)/2;
    return sum[node] = init(arr, node*2, nl, mid) + init(arr, node*2+1, mid+1, nr);
  }

  ll query(int l, int r, int node, int nl, int nr){
    if(r < nl || nr < l) return 0LL;
    if(l <= nl && nr <= r) return sum[node];
    int mid = (nl+nr)/2;
    return query(l, r, node*2, nl, mid) + query(l, r, node*2+1, mid+1, nr);
  }
  ll query(int l, int r){
    return query(l, r, 1, 0, n-1);
  }

  ll update(int idx, ll val, int node, int nl, int nr){
    if(idx < nl || nr < idx) return sum[node];
    if(nl == nr) return sum[node] = val;
    int mid = (nl+nr)/2;
    return sum[node] = update(idx, val, node*2, nl, mid) + update(idx, val, node*2+1, mid+1, nr);
  }
  ll update(int idx, ll val){
    return update(idx, val, 1, 0, n-1);
  }
  
  int kth(int k, int node, int nl, int nr){
    if(nl == nr) return nl;
    int mid = (nl+nr)/2;
    if(k < sum[node*2]) return kth(k, node*2, nl, mid);
    else return kth(k - sum[node*2], node*2+1, mid+1, nr);
  }
  int kth(int k){
    return kth(k, 1, 0, n-1);
  }
};