// 플로이드-워셜 알고리즘 
// 3중포문 - (거치는 점 - 출발 점 - 도착점)순으로 한 후 비교 
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_V 101
#define INF 987654321 

using namespace std; 

int V,E;
int adj[MAX_V][MAX_V];
// via[u][v] = u에서 v까지 가는 최단 경로가 경유하는 점 중 가장 번호가 큰 정점 
int via[MAX_V][MAX_V];

void floyd(){
	for(int i=1;i<=V;i++) adj[i][i] = 0;
	memset(via,-1,sizeof(via));
	for(int k=1;k<=V;k++)
		for(int i=1;i<=V;i++)
			for(int j=1;j<=V;j++)
				if(adj[i][j] > adj[i][k] + adj[k][j]){
					via[i][j] = k;
					adj[i][j] = adj[i][k] + adj[k][j];
				}
}

// u에서 v로 가는 최단 경로를 계산해 path에 저장한다 
void reconstruct(int u, int v, vector<int>& path){
	// 기저 사례
	if(via[u][v] == -1){
		path.push_back(u);
		if(u != v) path.push_back(v);
	}
	else{
		int w = via[u][v];
		reconstruct(u,w,path);
		path.pop_back(); // w가 중복으로 들어가므로
		reconstruct(w,v,path); 
	}
}

int main(){
	scanf("%d %d",&V,&E);
	
	for(int i=1;i<=V;i++)
		for(int j=1;j<=V;j++)
			adj[i][j] = INF;

	for(int i=0;i<E;i++){
		int A,B,C;
		scanf("%d %d %d",&A,&B,&C);
		adj[A][B] = min(adj[A][B],C);
	}
	
	floyd();
	
	for(int i=1;i<=V;i++){
		for(int j=1;j<=V;j++)
			printf("%d ",adj[i][j]!=INF ? adj[i][j] : 0);
		printf("\n");
	}
} 
