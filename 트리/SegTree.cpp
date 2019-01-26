struct SegTree{
  int n;
  vector<ll> sum;
  vector<ll> lazy;
  SegTree(const vector<ll>& a){
    n = a.size();
    sum.resize(n * 4);
    lazy.resize(n * 4);
    init(a, 0, n-1, 1);
  }
  ll init(const vector<ll>& a, int l, int r, int node){
    if(l == r) return sum[node] = a[l];
    int mid = (l + r) / 2;
    ll lSum = init(a, l, mid, node*2);
    ll rSum = init(a, mid+1, r, node*2+1);
    return sum[node] = lSum + rSum;
  }
  ll query(int l, int r, int node, int nl, int nr){
    update_lazy(nl,nr,node);
    if(r < nl || nr < l) return 0;
    if(l <= nl && nr <= r) return sum[node];
    int mid = (nl + nr) / 2;
    return query(l, r, node*2, nl, mid) + query(l, r, node*2+1, mid+1, nr);
  }
  ll query(int l, int r){
    return query(l, r, 1, 0, n-1);
  }
  //array[index]=newValue로 바뀌었을 때 node를 루트로 하는 구간트리를 갱신
  ll update(int index, ll newValue, int node, int nl, int nr){
    if(index < nl || nr < index) return sum[node];
    if(nl == nr) return sum[node] = newValue;
    int mid = (nl + nr) / 2;
    return sum[node] = update(index, newValue, node*2, nl, mid) +
              update(index, newValue, node*2+1, mid+1, nr);
  }
  ll update(int index, ll newValue){
    return update(index, newValue, 1, 0, n-1);
  }
  void update_lazy(int l, int r, int node){
    if(lazy[node] != 0){
      sum[node] += (r-l+1)*lazy[node];
      if(l != r){
        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
      }
      lazy[node] = 0;
    }
  }
  // left~right구간을 diff만큼 증가하였을 때 node를 루트로 하는 구간트리를 갱신
  void update_range(int l, int r, ll diff, int node, int nl, int nr){
    update_lazy(nl,nr,node);
    if(r < nl || nr < l) return;
    if(l <= nl && nr <= r){
      sum[node] += (nr-nl+1)*diff;
      if(nl != nr){
        lazy[node*2] += diff;
        lazy[node*2+1] += diff;
      }
      return;
    }
    int mid = (nl + nr) / 2;
    update_range(l, r, diff, node*2, nl, mid);
    update_range(l, r, diff, node*2+1, mid+1, nr);
    sum[node] = sum[node*2] + sum[node*2+1];
  }
  void update_range(int l, int r, ll diff){
    update_range(l, r, diff, 1, 0, n-1);
  }
};