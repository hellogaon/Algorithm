//트라이 - 문자열의 집합을 표현하는 자료구조
//시간복잡도 - 문자열의 길이가 M일 때 insert: O(M) find: O(M)
#include <cstdio>
#include <cstring>

const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'A'; }

struct TrieNode{
  TrieNode* children[ALPHABETS];
  //이 노드가 종료 노드인가?
  bool terminal;
  TrieNode() : terminal(false){
    memset(children, 0, sizeof(children));
  }
  ~TrieNode(){
    for(int i=0;i<ALPHABETS;i++)
      if(children[i])
        delete children[i];
  }
  //이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
  void insert(const char* key){
    //문자열이 끝나면 terminal만 참으로 바꾸고 종료
    if(*key == 0)
      terminal = true;
    else{
      int next = toNumber(*key);
      //해당 자식 노드가 없다면 생성한다.
      if(children[next] == NULL)
        children[next] = new TrieNode();
      children[next]->insert(key+1);
    }
  }
  //이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
  //없으면 NULL을 반환한다.
  TrieNode* find(const char* key){
    if(*key == 0) return this;
    int next = toNumber(*key);
    if(children[next] == NULL) return NULL;
    return children[next]->find(key+1);
  }
};

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  TrieNode trie;
  for(int i=0;i<N;i++){
    char ch[11];
    scanf("%s",ch);
    trie.insert(ch);
  }
  for(int i=0;i<M;i++){
    char ch[11];
    scanf("%s",ch);
    TrieNode* node = trie.find(ch);
    if(node == NULL || !node->terminal) printf("NO\n");
    else printf("YES\n");
  }
}
