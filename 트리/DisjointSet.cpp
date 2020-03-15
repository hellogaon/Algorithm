struct DS{
  vector<int> par, rank, size;
  DS(int n) : par(n), rank(n, 1), size(n, 1){
    for(int i=0;i<n;i++)
      par[i] = i;
  }
  int find(int u){
    if(u == par[u]) return u;
    return par[u] = find(par[u]);
  }
  int merge(int u, int v){
    u = find(u), v = find(v);
    if(u == v) return size[u];
    if(rank[u] < rank[v]) swap(u, v);
    par[v] = u;
    if(rank[u] == rank[v]) rank[u]++;
    size[u] += size[v];
    return size[u];
  }
};