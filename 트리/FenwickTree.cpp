struct FW{
  vector<ll> tree;
  FW(int n) : tree(n+1) {}
  // sum(pos) : A[0...pos] 의 부분 합
  ll sum(int pos){
    ++pos;
    ll ret = 0;
    while(pos > 0){
      ret += tree[pos];
      pos &= (pos-1);
    }
    return ret;
  }
  // A[pos]에 val을 더함
  void add(int pos, ll val){
    ++pos;
    while(pos < tree.size()){
      tree[pos] += val;
      pos += (pos & -pos);
    }
  }
};