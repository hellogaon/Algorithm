vector<ll> lazy;
lazy.resize(4 * n);

//query 첫 줄에 추가
update_lazy(nl,nr,node);

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
  int mid = (nl+nr)/2;
  update_range(l,r,diff,node*2,nl,mid);
  update_range(l,r,diff,node*2+1,mid+1,nr);
  sum[node] = sum[node*2] + sum[node*2+1];
}