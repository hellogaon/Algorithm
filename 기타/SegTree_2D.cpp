// 좌표의 범위를 P라 할 때,
// 2D segTree init : O(P^2)
// 2D segTree query : O(lgP * lgP)
const int MAXP = 1505;

struct SegTree_2D{
  int mat[MAXP][MAXP];
  int mx[MAXP * 4][MAXP * 4];

  int x_init(int y_node, int y, int x_node, int nl, int nr){
    if(nl == nr) return mx[y_node][x_node] = mat[y][nl];
    int mid = (nl + nr)/2;
    return mx[y_node][x_node] = max(x_init(y_node, y, x_node*2, nl, mid), x_init(y_node, y, x_node*2+1, mid+1, nr));
  }
  void yx_init(int y_node, int nl, int nr){
    if(nl == nr){
      x_init(y_node, nl, 1, 0, MAXP);
      return;
    }
    int mid = (nl + nr)/2;
    yx_init(y_node*2, nl, mid);
    yx_init(y_node*2+1, mid+1, nr);
    for(int i=1;i<MAXP * 4;i++)
      mx[y_node][i] = max(mx[y_node*2][i], mx[y_node*2+1][i]);
  }
  void init(){
    yx_init(1, 0, MAXP);
  }

  int x_query(int y_node, int xl, int xr, int x_node, int nl, int nr){
    if(xr < nl || nr < xl) return 0;
    if(xl <= nl && nr <= xr) return mx[y_node][x_node];
    int mid = (nl + nr)/2;
    return max(x_query(y_node, xl, xr, x_node*2, nl, mid), x_query(y_node, xl, xr, x_node*2+1, mid+1, nr));
  }
  int yx_query(int yl, int yr, int xl, int xr, int y_node, int nl, int nr){
    if(yr < nl || nr < yl) return 0;
    if(yl <= nl && nr <= yr) return x_query(y_node, xl, xr, 1, 0, MAXP);
    int mid = (nl + nr)/2;
    return max(yx_query(yl, yr, xl, xr, y_node*2, nl, mid), yx_query(yl, yr, xl, xr, y_node*2+1, mid+1, nr));
  }
  int query(int y1, int y2, int x1, int x2){
    return yx_query(y1, y2, x1, x2, 1, 0, MAXP);
  }
};