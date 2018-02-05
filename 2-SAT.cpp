// SCC를 응용한 2-SAT문제
// 각 절의 변수 개수가 최대 2개인 문제에 대해 참인 결과를 내보내준다.
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int vars = 10001;
vector<vector<int> > adj(vars*2);
vector<int> sccId(vars*2,-1);
vector<int> discovered(vars*2,-1);
stack<int> st;
int sccCounter, vertexCounter;

int scc(int here){
	int ret = discovered[here] = vertexCounter++;
	st.push(here);
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(discovered[there] == -1)
			ret = min(ret, scc(there));
		else if(sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}
	if(ret == discovered[here]){
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

int opp(int n) { return n%2 ? n-1 : n+1; }

int main(){
	int N,M;
	scanf("%d %d",&N,&M);
	for(int i=0;i<M;i++){
		int A,B;
		scanf("%d %d",&A,&B);
		A = (A>0 ? A*2 : -A*2+1);
		B = (B>0 ? B*2 : -B*2+1);
		adj[opp(A)].push_back(B);
		adj[opp(B)].push_back(A);
	}
	for(int i=2;i<2*(N+1);i++)
		if(discovered[i] == -1) scc(i);
	for(int i=2;i<2*(N+1);i+=2)
		if(sccId[i] == sccId[i+1])
			return printf("0\n");
	printf("1\n");

	// // SCC번호의 역순으로 각 정점을 정렬하면 위상 정렬 순서가 된다.
	vector<int> value(vars*2, -1);
	vector<pair<int, int> > order;
	for(int i=2;i<2*(N+1);i++)
		order.push_back(make_pair(-sccId[i],i));
	sort(order.begin(), order.end());

	for(int i=0;i<2*N;i++){
		int vertex = order[i].second;
		int variable = vertex/2, isTrue = vertex%2 == 0;
		if(value[variable] != -1) continue;
		// not A가 먼저 나왔을 경우 A는 참
		// A가 not A보다 먼저 나왔을 경우 A는 거짓
		value[variable] = !isTrue;
	}
	
	for(int i=1;i<=N;i++)
		printf("%d ",value[i]);
	printf("\n");
}