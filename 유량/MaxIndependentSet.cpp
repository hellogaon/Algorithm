//최대 독립 집합
//정점들을 가능한 한 많이 선택하되 선택된 정점끼리는 서로 인접하지 않게
//최대 독립 집합의 크기 = 정점의 수 - 최대 매칭의 크기
//최소 버텍스 커버
//정점들을 최소한으로 선택하여 버텍스 커버에 포함된 정점들과 그 정점에 연결된 간선들을
//제거하였을 때 간선이 하나도 남지 않게 되는 집합
//최소 버텍스 커버의 크기 = 최대 매칭의 크기
//최소 버텍스 커버와 최대 독립 집합은 여집합 관계

//aChosen[i] = 최대 독립 집합에 A_i가 포함되었는가?
//bChosen[i] = 최대 독립 집합에 B_i가 포함되었는가?
vector<bool> aChosen, bChosen; 

//이분 그래프의 정보가 주어질 때 실제 최대 독립 집합을 계산한다.
void MI(int n, int m){
  int C = BM(n,m);
  //1. A의 모든 정점들을 선택하고 B에서 대응되지 않은 정점들을 선택한다.
  aChosen = vector<bool>(n, true);
  bChosen = vector<bool>(m, false);
  for(int i=0;i<m;i++)
    if(bMatch[i] == -1)
      bChosen[i] = true;
  //2. 두 정점이 연결되어 있을 경우 그중 A의 정점을 지우고 B의 대응된 정점을
  //대신 선택한다. 더이상 변화가 일어나지 않을 때까지 반복한다.
  while(true){
    bool changed = false;
    for(int a=0;a<n;a++)
      for(int i=0;i<adj[a].size();i++){
        int b = adj[a][i];
        if(aChosen[a] && bChosen[b]){
          aChosen[a] = false;
          bChosen[aMatch[a]] = true;
          changed = true;
        }
      }
    if(!changed) break;
  }
}