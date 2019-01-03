void failFunc(TrieNode* root){
  queue<TrieNode*> q;
  root->fail = root;
  q.push(root);
  while(!q.empty()){
    TrieNode* here = q.front();
    q.pop();
    for(int i=0;i<MAXC;i++){
      TrieNode* child = here->c[i];
      if(!child) continue;
      if(here == root)
        child->fail = root;
      else{
        TrieNode* t = here->fail;
        while(t!=root && t->c[i]==NULL)
          t = t->fail;
        if(t->c[i]) t = t->c[i];
        child->fail = t;
      }
      child->output = child->fail->output;
      if(child->terminal != -1){
        child->output.pb(child->terminal);
      }
      q.push(child);
    }
  }
}

//s내에서 패턴이 출현할 때마다 (마지막 글자, 패턴 번호)의 쌍을 저장
vector<pii> AC(const string& s, TrieNode* root){
  vector<pii> ret;
  TrieNode* now = root;
  for(int i=0;i<s.size();i++){
    int chr = toNumber(s[i]);
    while(now!=root && now->c[chr]==NULL)
      now = now->fail;
    if(now->c[chr]) now = now->c[chr];
    for(int j=0;j<now->output.size();j++)
      ret.pb(mp(i,now->output[j]));
  }
  return ret;
}

int main(){
  int N;
  scanf("%d",&N);
  TrieNode root;
  for(int i=0;i<N;i++){
    char ch[101];
    scanf("%s",ch);
    root.insert(ch,i);
  }
  failFunc(&root);
  int Q;
  scanf("%d",&Q);
  for(int i=0;i<Q;i++){
    char ch[10001];
    scanf("%s",ch);
    vector<pii> ret = AC(ch,&root);
    if(ret.size()) printf("YES\n");
    else printf("NO\n");
  }
}
