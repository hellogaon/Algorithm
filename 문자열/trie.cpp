const int MAXC = 26;
int toNumber(char ch) { return ch - 'a'; }

struct TrieNode{
  int terminal;
  TrieNode* fail;
  vector<int> output;
  TrieNode* c[MAXC];
  TrieNode() : terminal(-1){
    memset(c, 0, sizeof(c));
  }
  ~TrieNode(){
    for(int i=0;i<MAXC;i++)
      if(c[i])
        delete c[i];
  }
  void insert(const char* key, int num){
    if(*key == 0)
      terminal = num;
    else{
      int next = toNumber(*key);
      if(c[next] == NULL)
        c[next] = new TrieNode();
      c[next]->insert(key+1,num);
    }
  }
  TrieNode* find(const char* key){
    if(*key == 0) return this;
    int next = toNumber(*key);
    if(c[next] == NULL) return NULL;
    return c[next]->find(key+1);
  }
};