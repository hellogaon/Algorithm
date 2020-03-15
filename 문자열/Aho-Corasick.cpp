void failFunc(Trie* root){
  queue<Trie*> q;
  root->fail = root;
  q.push(root);
  while(!q.empty()){
    Trie* here = q.front(); q.pop();
    for(int i=0;i<MAXC;i++){
      Trie* child = here->c[i];
      if(!child) continue;
      if(here == root) child->fail = root;
      else{
        Trie* t = here->fail;
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
vector<pii> AC(string& s, Trie* root){
  vector<pii> ret;
  Trie* now = root;
  for(int i=0;i<s.size();i++){
    int chr = toNumber(s[i]);
    while(now!=root && now->c[chr]==NULL)
      now = now->fail;
    if(now->c[chr]) now = now->c[chr];
    for(int j=0;j<now->output.size();j++)
      ret.pb(mp(i, now->output[j]));
  }
  return ret;
}

failFunc(&root);
vector<pii> ret = AC(s, &root);