//논리식을 논리곱 정규형으로 표현했을 때 각 절에 두 개의 변수만이 존재하는 경우에 대해 참인 결과를 내보낸다.
int opp(int n) { return n%2 ? n-1 : n+1; }

adj[opp(A)].pb(B);
adj[opp(B)].pb(A);

for(int i=2;i<2*(N+1);i++)
	if(discovered[i] == -1) scc(i);
	
for(int i=1;i<=N;i++)
  if(sccId[2*i] == sccId[2*i+1]) return !printf("0\n");
printf("1\n");

vector<pii> nd;
for(int i=1;i<=N;i++){
	nd.pb(mp(-sccId[i*2], i*2));
	nd.pb(mp(-sccId[i*2+1], i*2+1));
}
sort(nd.begin(), nd.end());
vector<int> ans(N+1,-1);
for(auto p: nd){
	int val = p.second;
	int now = val/2, isTrue = val%2 == 0;
	if(ans[now] != -1) continue;
	ans[now] = !isTrue;
}
