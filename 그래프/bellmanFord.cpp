//벨만포드: O(VE)
//단일 시작점 최단 경로 알고리즘 시작 정점 s에서부터 다른 정점까지의 최단거리
//간선의 비용이 음수일 때도 사용 가능 
const int MAXN = 501;

int V,E;
vector<pii> adj[MAXN];

// 음수 사이클이 있을 경우 텅 빈 배열을 반환
vector<int> BF(int src){
	vector<int> upper(V+1, INF);
	upper[src] = 0;
	bool updated;
	for(int iter=0;iter<V;iter++){
		updated = false;
		for(int here=1;here<=V;here++)
			for(int i=0;i<adj[here].size();i++){
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if(upper[here]!=INF && upper[there] > upper[here] + cost){
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		if(!updated) break;
	}
	if(updated) upper.clear();
	return upper; 
}
 
int main(){
	scanf("%d %d",&V,&E);
	for(int i=0;i<E;i++){
		int A,B,C;
		scanf("%d %d %d",&A,&B,&C);
		adj[A].pb(mp(B,C));
	}
	vector<int> dist = BF(1);
	if(dist.empty()) printf("-1\n");
}
