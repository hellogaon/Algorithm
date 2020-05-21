//모스 알고리즘
//원소의 수정은 없고 구간 내에서 어떤 결과를 찾는 종류의 쿼리만 있을 경우
//구간을 한 칸씩 넓히거나 줄이는 데 T(N)의 시간이 든다고 하면
//O(M + T(N)*N*(sqrt(N)))
int sqrtN;

struct QueryNode{
  int s,e,n; //[s,e)를 처리. n은 쿼리 번호
  QueryNode(): s(0), e(0), n(-1){}
  QueryNode(int s1, int e1, int n1): s(s1), e(e1), n(n1){}
  // (s/sqrtN, e) 순으로 오름차순 정렬
  bool operator <(const QueryNode &O)const{
    if(s/sqrtN != O.s/sqrtN) return (s/sqrtN < O.s/sqrtN);
    return (e < O.e);
  }
};

void add(int idx){

}

void del(int idx){

}

QueryNode Q[100005];

//첫 쿼리는 직접 구한 뒤 그 구간을 한 칸씩 넓히거나 줄이면서 진행 add 연산 먼저 진행할 것!
sqrtN = sqrt(N);
sort(Q,Q+M);
int s = Q[0].s, e = Q[0].e;
for(int i=s;i<=e;i++) add(i);

while(Q[i].s < s) add(--s);
while(e < Q[i].e) add(++e);
while(Q[i].s > s) del(s++);
while(e > Q[i].e) del(e--);
