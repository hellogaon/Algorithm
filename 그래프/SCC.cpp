//Strongly Connected Component 강한 연결 요소
//방향그래프 상에서 두 정점 u와 v에 대해 양방향으로 가는 경로가 모두 있을 때 같은 SCC
//scc함수가 종료하기 직전에 SCC를 생성하기에 SCC는 위상 정렬의 역순으로 번호가 매겨진다.
//시간복잡도 - 정점 개수가 V 간선 개수가 E 일 때 O(V + E)
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int V,E;
vector<vector<int> > adj(10001);
//각 정점의 컴포넌트 번호
vector<int> sccId(10001,-1);
vector<int> discovered(10001,-1);
//정점의 번호를 담는 스택
stack<int> st;
int sccCounter, vertexCounter;

int scc(int here){
	int ret = discovered[here] = vertexCounter++;
	st.push(here);
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(discovered[there] == -1)
			ret = min(ret, scc(there));
		//there가 무시해야 하는 교차 간선이 아니라면
		else if(sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}
	//here에서 부모로 올라가는 간선을 끊어야 할 지 확인
	if(ret == discovered[here]){
		//here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컨포넌트로 묶는다.
		while(true){
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if(t == here) break;
		}
		++sccCounter;
	}
	return ret;
}

int main(){
	scanf("%d %d",&V,&E);
	for(int i=0;i<E;i++){
		int A,B;
		scanf("%d %d",&A,&B);
		adj[A].push_back(B);
	}
	for(int i=1;i<=V;i++)
		if(discovered[i] == -1) scc(i);
	
	printf("%d\n",sccCounter);
	vector<vector<int> > ans;
	for(int i=0;i<sccCounter;i++){
		vector<int> v;
		for(int j=1;j<=V;j++)
			if(sccId[j]==i) v.push_back(j);
		sort(v.begin(),v.end());
		v.push_back(-1);
		ans.push_back(v);
	}
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++){
		for(int j=0;j<ans[i].size();j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
}