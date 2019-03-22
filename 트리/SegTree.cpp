struct SegTree{
  int n;
  vector<ll> sum;
  SegTree(vector<ll>& a){
    n = a.size();
    sum.resize(4 * n);
    init(a,1,0,n-1);
  }
  ll init(vector<ll>& a, int node, int nl, int nr){
    if(nl == nr) return sum[node] = a[nl];
    int mid = (nl+nr)/2;
    return sum[node] = init(a,node*2,nl,mid) + init(a,node*2+1,mid+1,nr);
  }
  ll query(int l, int r, int node, int nl, int nr){
    if(r < nl || nr < l) return 0;
    if(l <= nl && nr <= r) return sum[node];
    int mid = (nl+nr)/2;
    return query(l,r,node*2,nl,mid) + query(l,r,node*2+1,mid+1,nr);
  }
  ll update(int idx, ll val, int node, int nl, int nr){
    if(idx < nl || nr < idx) return sum[node];
    if(nl == nr) return sum[node] = val;
    int mid = (nl+nr)/2;
    return sum[node] = update(idx,val,node*2,nl,mid)+update(idx,val,node*2+1,mid+1,nr);
  }
};