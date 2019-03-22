const int MAXC = 26;
int toNumber(char ch) { return ch - 'a'; }

struct Trie{
  int terminal;
  // Trie* fail;
  // vector<int> output;
  Trie* c[MAXC];
  Trie() : terminal(-1){
    memset(c, 0, sizeof(c));
  }
  void insert(char* key, int num){
    if(*key == 0) terminal = num;
    else{
      int next = toNumber(*key);
      if(c[next] == NULL)
        c[next] = new Trie();
      c[next]->insert(key+1,num);
    }
  }
  Trie* find(char* key){
    if(*key == 0) return this;
    int next = toNumber(*key);
    if(c[next] == NULL) return NULL;
    return c[next]->find(key+1);
  }
};