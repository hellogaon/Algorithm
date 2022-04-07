const int MAXC = 26;
int toNumber(char ch) { return ch - 'A'; }

struct Trie{
  int terminal;
  // Trie* fail;
  // vector<int> output;
  Trie* c[MAXC];
  Trie() : terminal(-1){
    memset(c, 0, sizeof(c));
  }
  void insert(string& key, int num, int idx=0){
    if(idx == key.size()) terminal = num;
    else{
      int nxt = toNumber(key[idx]);
      if(c[nxt] == NULL) c[nxt] = new Trie();
      c[nxt]->insert(key, num, idx+1);
    }
  }
  Trie* find(string& key, int idx=0){
    if(idx == key.size()) return this;
    int nxt = toNumber(key[idx]);
    if(c[nxt] == NULL) return NULL;
    return c[nxt]->find(key, idx+1);
  }
};