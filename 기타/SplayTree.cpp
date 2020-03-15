//Splay Tree
//(0 ~ N-1) 대신 (1 ~ N)을 사용하는 것이 좋음

struct Node{
  Node *l, *r, *p;
  int key, cnt;
  ll value, sum, lazy;
  bool inv;
};

struct SplayTree{
  Node *root;

  // 노드 개수만큼 연결
  void init(int n){
    Node *x;
    root = x = new Node;
    x->l = x->r = x->p = NULL;
    x->cnt = n;
    x->sum = x->value = x->lazy = x->inv = 0;
    for(int i=1;i<n;i++){
      x->r = new Node;
      x->r->p = x;
      x = x->r;
      x->l = x->r = NULL;
      x->cnt = n - i;
      x->sum = x->value = x->lazy = x->inv = 0;
    }
  }

  // i번째 원소에 값 z를 더함
  void add(int i, ll z){
    kth(i);
    root->sum += z;
    root->value += z;
  }

  void add(int l, int r, ll z){
    interval(l,r);
    Node *x = root->r->l;
    x->sum += x->cnt * z;
    x->lazy += z;
  }

  void update(Node *x){
    x->cnt = 1;
    x->sum = x->value;
    if(x->l){
      x->cnt += x->l->cnt;
      x->sum += x->l->sum;
    }
    if(x->r){
      x->cnt += x->r->cnt;
      x->sum += x->r->sum;
    }
  }

  //x를 위로 올림
  void rotate(Node *x){
    Node *p = x->p;
    Node *b;
    lazy(p);
    lazy(x);
    if(x == p->l){
      p->l = b = x->r;
      x->r = p;
    }
    else{
      p->r = b = x->l;
      x->l = p;
    }
    x->p = p->p;
    p->p = x;
    if(b) b->p = p;
    (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
    update(p);
    update(x);
  }

  //x를 루트로 올림
  void splay(Node *x){
    while(x->p){
      Node *p = x->p;
      Node *g = p->p;
      if(g) rotate((x == p->l) == (p == g->l) ? p : x);
      rotate(x);
    }
  }

  // key를 삽입. 마지막에 삽입한 노드를 splay
  void insert(int key){
    Node *p = root, **pp;
    if(!p){
      Node *x = new Node;
      root = x;
      x->l = x->r = x->p = NULL;
      x->key = key;
      return;
    }
    while(1){
      if(key == p->key) return; // 중복
      if(key < p->key){
        if(!p->l){
          pp = &p->l;
          break;
        }
        p = p->l;
      }
      else{
        if(!p->r){
          pp = &p->r;
          break;
        }
        p = p->r;
      }
    }
    Node *x = new Node;
    *pp = x;
    x->l = x->r = NULL;
    x->p = p;
    x->key = key;
    splay(x);
  }

  // key를 검색. 마지막에 검색한 노드를 splay
  bool find(int key){
    Node *p = root;
    if(!p) return false;
    while(p){
      if(key == p->key) break;
      if(key < p->key){
        if(!p->l) break;
        p = p->l;
      }
      else{
        if(!p->r) break;
        p = p->r;
      }
    }
    splay(p);
    return key == p->key;
  }

  //key를 삭제. 먼저 삭제할 노드를 splay
  void erase(int key){
    if(!find(key)) return;
    Node *p = root;
    if(p->l && p->r){
      root = p->l;
      root->p = NULL;
      Node *x = root;
      while(x->r) x = x->r;
      x->r = p->r;
      p->r->p = x;
      splay(x);
      delete p;
      return;
    }
    if(p->l){
      root = p->l;
      root->p = NULL;
      delete p;
      return;
    }
    if(p->r){
      root = p->r;
      root->p = NULL;
      delete p;
      return;
    }
    delete p;
    root = NULL;
  }

  //K번째 원소 찾기. K번째 원소를 splay. K는 0-based
  void kth(int k){
    Node *x = root;
    lazy(x);
    while(1){
      while(x->l && x->l->cnt > k){
        x = x->l;
        lazy(x);
      }
      if(x->l) k -= x->l->cnt;
      if(!k--) break;
      x = x->r;
      lazy(x);
    }
    splay(x);
  }

  //구간 l~r 사이의 합
  ll sum(int l, int r){
    interval(l,r);
    return root->r->l->sum;
  }

  //l이 구간 왼쪽 끝이거나 r이 구간 오른쪽 끝인 경우 예외처리 필요
  //(0 ~ N-1) 대신 (1 ~ N)을 사용하는 것이 좋음
  void interval(int l, int r){
    kth(l - 1);
    Node *x = root;
    root = x->r;
    root->p = NULL;
    kth(r - l + 1);
    x->r = root;
    root->p = x;
    root = x;
  }

  void lazy(Node *x){
    //합 lazy
    x->value += x->lazy;
    if(x->l){
      x->l->lazy += x->lazy;
      x->l->sum += x->l->cnt * x->lazy;
    }
    if(x->r){
      x->r->lazy += x->lazy;
      x->r->sum += x->r->cnt * x->lazy;
    }
    x->lazy = 0;

    //뒤집기 lazy
    if(!x->inv) return;
    Node *t = x->l;
    x->l = x->r;
    x->r = t;
    x->inv = false;
    if(x->l) x->l->inv = !x->l->inv;
    if(x->r) x->r->inv = !x->r->inv;
  }

  //구간 l~r을 뒤집기
  void reverse(int l, int r){
    interval(l,r);
    Node *x = root->r->l;
    x->inv = !x->inv;
  }
};