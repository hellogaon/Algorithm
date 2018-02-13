// 벨만-포드 알고리즘
// 간선의 비용이 음수일 때도 사용 가능 
#include <cstdio>
#include <vector>
#define MAX_V 501
#define INF 987654321

using namespace std;

int V,E;
vector<pair<int,int> >  adj[MAX_V];

// 음수 사이클이 있을 경우 텅 빈 배열을 반환
vector<int> bellmanFord(int src){
	// 시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
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
	// V번째 순회에서도 완화가 성공했다면 음수사이클이 있다.
	if(updated) upper.clear();
	return upper; 
}
 
int main(){
	scanf("%d %d",&V,&E);
	for(int i=0;i<E;i++){
		int A,B,C;
		scanf("%d %d %d",&A,&B,&C);
		adj[A].push_back(make_pair(B,C));
	}
	vector<int> dist = bellmanFord(1);
	
	if(dist.empty()) return printf("-1\n");

	for(int i=2;i<=V;i++)
		printf("%d\n",dist[i]!=INF ? dist[i] : -1);
}
