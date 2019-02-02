//무향그래프에서 삭제했을 그래프가 두 개 이상의 컴포넌트로 분리되는 간선
const int MAXV = 10001;

int V,E,cnt;
vector<vector<int> > adj(MAXV);
vector<int> visited(MAXV,-1);
vector<pii> isCB;

int findCB(int here, int par){
	visited[here] = cnt++;
	int ret = visited[here];
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(there == par) continue;
		if(visited[there] == -1){
			int subtree = findCB(there,here);
			if(subtree > visited[here])
				isCB.pb(mp(min(here,there),max(here,there)));
			ret = min(ret,subtree);
		}
		else
			ret = min(ret,visited[there]);
	}
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
			findCB(i, 0);
	}
	printf("%lu\n",isCB.size());
	sort(isCB.begin(),isCB.end());
	for(int i=0;i<isCB.size();i++)
		printf("%d %d\n",isCB[i].first,isCB[i].second);
}