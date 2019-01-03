//강한 연결 요소: O(V+E)
//방향그래프 상에서 두 정점 u와 v에 대해 양방향으로 가는 경로가 모두 있을 때 같은 SCC
//scc함수가 종료하기 직전에 SCC를 생성하기에 SCC는 위상 정렬의 역순으로 번호가 매겨진다.
const int MAXN = 100001;

int V,E;
vector<vector<int> > adj(MAXN);
vector<int> sccId(MAXN,-1);
vector<int> visited(MAXN,-1);
stack<int> st;
int scccnt, vcnt;

int scc(int here){
	int ret = visited[here] = vcnt++;
	st.push(here);
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(visited[there] == -1)
			ret = min(ret, scc(there));
		else if(sccId[there] == -1)
			ret = min(ret, visited[there]);
	}
	if(ret == visited[here]){
		while(true){
			int t = st.top();
			st.pop();
			sccId[t] = scccnt;
			if(t == here) break;
		}
		++scccnt;
	}
	return ret;
}

int main(){
	for(int i=1;i<=V;i++)
		if(visited[i] == -1) scc(i);
	printf("%d\n",scccnt);
}