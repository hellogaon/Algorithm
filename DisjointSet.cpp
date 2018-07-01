// 상호 베타적 집합 자료구조
// 유니온 파인드
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct DisjointSet{
  vector<int> parent, rank, size;
  DisjointSet(int n) : parent(n), rank(n,1), size(n,1){
    for(int i=0;i<n;i++)
      parent[i]=i;
  }
  int find(int u){
    if(u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }
  int merge(int u, int v){
    u = find(u); v = find(v);
    if(u == v) return size[v];
    if(rank[u] > rank[v]) swap(u,v);
    parent[u] = v;
    if(rank[u] == rank[v]) ++rank[v];
    size[v] += size[u];
    return size[v];
  }
};

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  DisjointSet ds(N);
  for(int i=0;i<M;i++){
    int s,a,b;
    scanf("%d %d %d",&s,&a,&b);
    if(s==0)
      ds.merge(a,b);
    if(s==1){
      if(ds.find(a)==ds.find(b))
        printf("YES\n");
      else
        printf("NO\n");
    }
  }
}
