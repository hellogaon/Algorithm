//Persistent Segment Tree : N개의 Segment Tree
//update 질의가 없는 2D range query
//시간복잡도 : O(lgN)
const int MAX_DEPTH = 18; // 세그먼트 트리의 높이
const int MAX_ST = 1<<MAX_DEPTH; // 초기화에 사용되는 노드 개수
const int MAX = 100001; // 점의 개수
const int MAX_RANGE = 100001; // 좌표값의 범위
const int MAX_NODE = MAX_ST + MAX*MAX_DEPTH; // 전체에서 사용되는 노드 개수의 상한

struct Node{
  int val;
  int nl, nr, nNum, lNum, rNum;
  Node(): val(-1), nl(-1), nr(-1) {}
  Node(int nl1, int nr1, int nNum1){
    val = 0;
    nl = nl1, nr = nr1, nNum = nNum1;
    lNum = -1, rNum = -1;
  }
};

struct PersistentSegTree{
  int TN;
  int ncnt;
  int root[MAX];
  Node node[MAX_NODE];

  PersistentSegTree(){
    TN = 0, ncnt = 0;
    fill(root,root+MAX,-1);
    root[TN++] = init(0,MAX_ST/2-1);
  }

  int init(int l, int r){
    Node &curr = node[ncnt] = Node(l,r,ncnt);
    ncnt++;
    if(l != r){
      int mid = (l+r)/2;
      curr.lNum = init(l,mid);
      curr.rNum = init(mid+1,r);
    }
    return curr.nNum;
  }
  // 새 트리를 만들면서 인덱스 y인 리프 노드에 val만큼 더한다.
  void addNode(int y, int val){
    root[TN] = addNode(node[root[TN-1]],y,val,0,MAX_ST/2-1);
    TN++;
  }
  int addNode(Node &shadow, int y, int val, int l, int r){
    if(r < y || y < l) return shadow.nNum;
    Node &curr = node[ncnt] = Node(l,r,ncnt);
    ncnt++;
    if(l == r) curr.val = shadow.val + val;
    else{
      int mid = (l+r)/2;
      curr.lNum = addNode(node[shadow.lNum],y,val,l,mid);
      curr.rNum = addNode(node[shadow.rNum],y,val,mid+1,r);
      curr.val = node[curr.lNum].val + node[curr.rNum].val;
    }
    return curr.nNum;
  }
  //tn번째 트리의 구간 [l, r]의 합을 구한다.
  int sum(int tn, int l, int r){
    return sum(node[root[tn]],l,r);
  }
  int sum(Node &curr, int l, int r){
    if(r < curr.nl || curr.nr < l) return 0;
    if(l <= curr.nl && curr.nr <= r) return curr.val;
    return sum(node[curr.lNum],l,r) + sum(node[curr.rNum],l,r);
  }
  //인덱스 [l, r] 내에서 k번째로 작은 값을 찾아온다. (k는 0-based)
  int kth(int l, int r, int k){
    return kth(node[root[l-1]], node[root[r]], k);
  }
  int kth(Node &sNode, Node &eNode, int k){
    if(eNode.nl == eNode.nr) return eNode.nl;
    int pivot = node[eNode.lNum].val - node[sNode.lNum].val;
    if(k < pivot) return kth(node[sNode.lNum],node[eNode.lNum],k);
    else return kth(node[sNode.rNum],node[eNode.rNum],k-pivot);
  }
};
