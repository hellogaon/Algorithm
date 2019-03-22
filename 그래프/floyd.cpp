//플로이드 와샬: O(V^3)
const int MAXV = 101;

int V,E;
int mat[MAXV][MAXV];
int path[MAXV][MAXV];

void init(){
	memset(path,-1,sizeof(path));
  for(int i=1;i<=V;i++)
    for(int j=1;j<=V;j++)
      mat[i][j] = (i == j) ? 0 : INF;
}

void floyd(){
  for(int k=1;k<=V;k++)
    for(int i=1;i<=V;i++)
      for(int j=1;j<=V;j++){
        if(mat[i][j] > mat[i][k] + mat[k][j]){
					path[i][j] = k;
          mat[i][j] = mat[i][k] + mat[k][j];
        }
  }
}

// u에서 v전까지 가는 최단 경로를 계산해 path에 저장한다 
vector<int> p;
void getpath(int u, int v){
	if(path[u][v] == -1){
		p.pb(u); return;
	}
	getpath(u,path[u][v]);
	getpath(path[u][v],v); 
}