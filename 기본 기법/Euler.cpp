//오일러경로, 오일러회로 알고리즘
//오일러 회로에서 시작점과 종점을 잇고 똑같이.
vector<vector<int> > adj;

void Euler(int here, vector<int>& ans){
  for(int there = 0; there < adj.size(); ++there)
    while(adj[here][there] > 0){
      adj[here][there]--;
      adj[there][here]--;
      Euler(there, ans);
    }
    ans.pb(here);
}

int main(){
  int N;
  vector<int> odd;
  scanf("%d",&N);
  for(int i=0;i<N;i++){
    vector<int> v(N);
    int cnt = 0;
    for(int j=0;j<N;j++){
      scanf("%d",&v[j]);
      if(v[j]) cnt+=v[j];
    }
    if(cnt%2) odd.pb(i);
    adj.pb(v);
  }
  if(!(odd.size()==0 || odd.size()==2)){
    printf("-1\n");
    return 0;
  }
  int start = 0;
  if(odd.size()){
    int n = odd[0], m = odd[1];
    adj[n][m]++; adj[m][n]++;
    start = n;
  }
  vector<int> ans;
  Euler(start,ans);
  for(int i=ans.size()-1;i>=0;i--){
    if(!(odd.size() && i==0))
      printf("%d ",ans[i]+1);
  }
  printf("\n");
}
