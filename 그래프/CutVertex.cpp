//무향그래프에서 삭제했을 때 해당 정점이 포함된 그래프가 두 개 이상의 컴포넌트로 분리되는 정점
const int MAXV = 10001;

int V,E,cnt;
vector<vector<int> > adj(MAXV);
vector<int> visited(MAXV,-1);
vector<bool> isCV(MAXV,false);

int getCV(int here, bool isRoot){
	visited[here] = cnt++;
	int ret = visited[here];
	int c = 0;
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(visited[there] == -1){
			++c;
			//이 서브트리에서 갈 수 있는 가장 작은 정점의 번호
			int subtree = getCV(there,false);
			//그 정점의 번호가 자신 번호보다 크다면 현재 위치는 절단점
			if(!isRoot && subtree >= visited[here])
				isCV[here] = true;
			ret = min(ret,subtree);
		}
		else
			ret = min(ret,visited[there]);
	}
	//루트인 경우 절단점 판정은 서브트리의 개수
	if(isRoot) isCV[here] = (c >= 2);
	return ret;
}
int main(){
	scanf("%d %d",&V,&E);
	for(int i=0;i<E;i++){
		int A,B;
		scanf("%d %d",&A,&B);
		adj[A].pb(B);
		adj[B].pb(A);
	}
	for(int i=1;i<=V;i++){
		if(visited[i] == -1)
			getCV(i,true);
	}
	vector<int> ans;
	for(int i=1;i<=V;i++)
		if(isCV[i]) ans.pb(i);
	printf("%lu\n",ans.size());
}