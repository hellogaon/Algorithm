//아호코라식 문자열 검색 알고리즘
//긴 문서에서 많은 문자열을 동시에 찾아야 할 때
//시간복잡도 - N : 짚더미의 길이 M : 바늘 문자열의 길이의 합 P : 바늘의 출현 횟수 일 떄 O(N+M+P)
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <vector>

using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'a'; }

struct TrieNode{
  //현 위치에서 끝나는 문자열의 번호
  int terminal;
  //실패 연결: 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속
  //이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열
  TrieNode* fail;
  //출력 문자열 목록: 이 노드가 방문 되었을 때 등장하는 바늘 문자열들의 번호
  vector<int> output;
  TrieNode* children[ALPHABETS];
  TrieNode() : terminal(-1){
    memset(children, 0, sizeof(children));
  }
  ~TrieNode(){
    for(int i=0;i<ALPHABETS;i++)
      if(children[i])
        delete children[i];
  }
  //이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
  void insert(const char* key, int num){
    //문자열이 끝나면 terminal만 num으로 바꾸고 종료
    if(*key == 0)
      terminal = num;
    else{
      int next = toNumber(*key);
      //해당 자식 노드가 없다면 생성한다.
      if(children[next] == NULL)
        children[next] = new TrieNode();
      children[next]->insert(key+1,num);
    }
  }
};

//트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산
void computeFailFunc(TrieNode* root){
  //루트에서부터 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결을 계산
  queue<TrieNode*> q;
  //루트의 실패 연결은 자기 자신
  root->fail = root;
  q.push(root);
  while(!q.empty()){
    TrieNode* here = q.front();
    q.pop();
    //here의 모든 자손에 대해 실패 연결을 계산하고 이들을 큐에 넣는다.
    for(int edge=0;edge<ALPHABETS;edge++){
      TrieNode* child = here->children[edge];
      if(!child) continue;
      //1레벨 노드의 실패 연결은 항상 루트
      if(here == root)
        child->fail = root;
      else{
        //아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다.
        TrieNode* t = here->fail;
        while(t!=root && t->children[edge]==NULL)
          t = t->fail;
        if(t->children[edge]) t = t->children[edge];
        child->fail = t;
      }
      //출력 문자열 목록: 실패 연결을 따라간 노드를 복사해온 뒤
      //이 위치에서 끝나는 바늘 문자열이 있으면 추가한다.
      child->output = child->fail->output;
      if(child->terminal != -1){
        child->output.push_back(child->terminal);
      }
      q.push(child);
    }
  }
}

//trie에 포함된 패턴들을 s에서 찾는다
//s내에서 패턴이 출현할 때마다 (마지막 글자, 패턴 번호)의 쌍을 저장
vector<pair<int,int> > ahoCorasick(const string& s, TrieNode* root){
  vector<pair<int,int> > ret;
  TrieNode* state = root;
  for(int i=0;i<s.size();i++){
    int chr = toNumber(s[i]);
    while(state!=root && state->children[chr]==NULL)
      state = state->fail;
    if(state->children[chr]) state = state->children[chr];
    for(int j=0;j<state->output.size();j++)
      ret.push_back(make_pair(i,state->output[j]));
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
  computeFailFunc(&root);
  int Q;
  scanf("%d",&Q);
  for(int i=0;i<Q;i++){
    char ch[10001];
    scanf("%s",ch);
    vector<pair<int,int> > ret = ahoCorasick(ch,&root);
    if(ret.size()) printf("YES\n");
    else printf("NO\n");
  }
}
