struct DS{
  vector<int> par, rank, size;
  DS(int n) : par(n), rank(n,1), size(n,1){
    for(int i=0;i<n;i++)
      par[i]=i;
  }
  int find(int u){
    if(u == par[u]) return u;
    return par[u] = find(par[u]);
  }
  int merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v) return size[v];
    if(rank[u] > rank[v]) swap(u,v);
    par[u] = v;
    if(rank[u] == rank[v]) ++rank[v];
    size[v] += size[u];
    return size[v];
  }
};
