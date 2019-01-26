//모스 알고리즘
//원소의 수정은 없고 구간 내에서 어떤 결과를 찾는 종류의 쿼리만 있을 경우
//구간을 한 칸씩 넓히거나 줄이는 데 T(N)의 시간이 든다고 하면
//O(M + T(N)*N*(sqrt(N)))
//이 문제는 13547번 문제로 A[i] .. A[j]에 존재하는 서로 다른 수의 개수를 출력하는 문제
const int MAXN = 1000001;
const int MAX_VAL = 1000001;

int A[MAXN], cnt[MAX_VAL], ret[MAXN];
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

QueryNode Q[MAXN];

int main(){
  int N,M;
  scanf("%d",&N);
  for(int i=0;i<N;i++)
    scanf("%d",&A[i]);
  scanf("%d",&M);
  sqrtN = sqrt(N);
  for(int i=0;i<M;i++){
    int L,R;
    scanf("%d %d",&L,&R);
    Q[i] = QueryNode(L-1,R,i);
  }
  sort(Q,Q+M);
  int c = 0;
  int s = Q[0].s, e = Q[0].e;
  for(int i=s;i<e;i++)
    if(cnt[A[i]]++ == 0) c++;
  ret[Q[0].n] = c;
  for(int i=1;i<M;i++){
    while(Q[i].s < s) if(cnt[A[--s]]++ == 0) c++;
    while(e < Q[i].e) if(cnt[A[e++]]++ == 0) c++;
    while(Q[i].s > s) if(--cnt[A[s++]] == 0) c--;
    while(e > Q[i].e) if(--cnt[A[--e]] == 0) c--;
    ret[Q[i].n] = c;
  }
  for(int i=0;i<M;i++)
    printf("%d\n",ret[i]);
}