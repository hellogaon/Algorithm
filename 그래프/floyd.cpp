//플로이드 와샬: O(V^3)
const int MAXV = 501;

int V,E;
int adj[MAXV][MAXV];
int path[MAXV][MAXV];

void floyd(){
	for(int i=1;i<=V;i++) adj[i][i] = 0;
	memset(path,-1,sizeof(path));
	for(int k=1;k<=V;k++)
		for(int i=1;i<=V;i++)
			for(int j=1;j<=V;j++)
				if(adj[i][j] > adj[i][k] + adj[k][j]){
					path[i][j] = k;
					adj[i][j] = adj[i][k] + adj[k][j];
				}
}

// u에서 v로 가는 최단 경로를 계산해 path에 저장한다 
void getpath(int u, int v, vector<int>& path){
	if(path[u][v] == -1){
		path.pb(u);
		if(u != v) path.pb(v);
	}
	else{
		int w = path[u][v];
		getpath(u,w,path);
		path.pop_back();
		getpath(w,v,path); 
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
} 
