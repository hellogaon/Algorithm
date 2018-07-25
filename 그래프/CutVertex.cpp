// 벌텍스 컷 - 무향그래프에서 절단점 찾는 알고리즘
// 절단점 : 삭제했을 때 해당 정점이 포함된 그래프가 두 개 이상의 컴포넌트로 분리되는 정점
#include <cstdio>
#include <vector>

using namespace std;

int V,E,counter;
vector<vector<int> > adj(10001);
vector<int> discovered(10001,-1);
vector<bool> isCutVertex(10001,false);

int findCutVertex(int here, bool isRoot){
	discovered[here] = counter++;
	int ret = discovered[here];
	int children = 0;
	for(int i=0;i<adj[here].size();i++){
		int there = adj[here][i];
		if(discovered[there] == -1){
			++children;
			//이 서브트리에서 갈 수 있는 가장 작은 정점의 번호
			int subtree = findCutVertex(there,false);
			//그 정점의 번호가 자신 번호보다 크다면 현재 위치는 절단점
			if(!isRoot && subtree >= discovered[here])
				isCutVertex[here] = true;
			ret = min(ret,subtree);
		}
		else
			ret = min(ret,discovered[there]);
	}
	//루트인 경우 절단점 판정은 서브트리의 개수
	if(isRoot) isCutVertex[here] = (children >= 2);
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
			findCutVertex(i,true);
	}

	vector<int> ans;
	for(int i=1;i<=V;i++)
		if(isCutVertex[i]) ans.push_back(i);
	printf("%lu\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d ",ans[i]);
	printf("\n");
}