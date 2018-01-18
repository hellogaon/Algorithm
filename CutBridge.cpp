// 무향그래프에서 절단선 찾는 알고리즘
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int V,E,counter;
vector<vector<int> > adj(100001);
vector<int> discovered(100001,-1);
vector<pair<int,int> > isCutBridge;

int findCutBridge(int here, int parent){
	discovered[here] = counter++;
	int ret = discovered[here];
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(there == parent) continue;
		if(discovered[there] == -1){
			int subtree = findCutBridge(there,here);
			if(subtree > discovered[here])
				isCutBridge.push_back(make_pair(min(here,there),max(here,there)));
			ret = min(ret,subtree);
		}
		else
			ret = min(ret,discovered[there]);
	}
	return ret;
}
int main(){
	scanf("%d %d",&V,&E);
	for(int i=0;i<E;i++){
		int A,B;
		scanf("%d %d",&A,&B);
		adj[A].push_back(B);
		adj[B].push_back(A);
	}
	for(int i=1;i<=V;i++){
		if(discovered[i]==-1)
			findCutBridge(i,0);
	}
	printf("%lu\n",isCutBridge.size());
	sort(isCutBridge.begin(),isCutBridge.end());
	for(int i=0;i<isCutBridge.size();i++)
		printf("%d %d\n",isCutBridge[i].first,isCutBridge[i].second);
}