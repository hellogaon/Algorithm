// Bitset, hirschberg LCS
// 시간복잡도 : O(NM/64)
// 공간복잡도 : O(M/64)
typedef unsigned long long ull;

const int MAXN = 50001; // 문자열의 최대 길이
const int MAXC = 26; // 가능한 문자 집합
const int MAXSIZ = (MAXN >> 6) + 1;

int toNumber(char ch) { return ch - 'A'; }

int bit_get(vector<ull> &a, int x){ return ((a[x >> 6] >> (x & 63)) & 1) == 1; }

void bit_set(vector<ull> &a, int x){ a[x >> 6] |= 1ULL << (x & 63); }

vector<ull> LCS(string &A, string &B){
  int N = A.size(), M = B.size();
  int SIZ = (M >> 6) + 1;
  vector<ull> D(SIZ);
  vector<vector<ull> > S(MAXC, vector<ull>(SIZ));
  
  for(int j=0;j<M;j++)
    bit_set(S[toNumber(B[j])], j);
  
  for(int j=0;j<M;j++)
    if(A[0] == B[j]){
      bit_set(D, j);
      break;
    }
  
  for(int i=1;i<N;i++){
    ull bef_LSB = 1, bef_carry = 0;
    for(int j=0;j<SIZ;j++){
      ull x = S[toNumber(A[i])][j] | D[j];
      ull r = ((D[j] << 1) | bef_LSB);
      bef_LSB = (D[j] >> 63);

      ull y = x;
      y -= (r + bef_carry);
      bef_carry = (y > x);
      
      D[j] = x & (x ^ y);
    }
  }
  return D;
}

int get_size(string &A, string &B){
  int ret = 0;
  vector<ull> D = LCS(A, B);
  for(int j=0;j<B.size();j++)
    if(bit_get(D, j)) ret++;
  return ret;
}

int f[MAXN], g[MAXN];

string substr(string &A, int s, int e){
  string ret;
  ret.resize(e-s+1);
  for(int i=0;i<e-s+1;i++)
    ret[i] = A[s+i];
  return ret;
}

void update_f_g(string &A, string &B, int a1, int a2, int b1, int b2){
  int a_mid = (a1 + a2)/2;
  int a_siz = a2 - a1 + 1;
  int b_siz = b2 - b1 + 1;
  string A1 = substr(A, a1, a_mid);
  string A2 = substr(A, a_mid+1, a2);
  string B1 = substr(B, b1, b2);
  string B2 = B1;
  reverse(A2.begin(), A2.end());
  reverse(B2.begin(), B2.end());

  vector<ull> D1 = LCS(A1, B1);
  vector<ull> D2 = LCS(A2, B2);
  for(int j=1;j<=b_siz;j++){
    f[b1+j] = f[b1+j-1] + bit_get(D1,j-1);
    g[b1+j] = g[b1+j-1] + bit_get(D2,j-1);
  }
}

string hirschberg(string &A, string &B, int a1, int a2, int b1, int b2){
  if(a1 == a2){
    for(int i=b1;i<=b2;i++)
      if(A[a1] == B[i]){
        string ret;
        ret += A[a1];
        return ret;
      }
    return "";
  }

  int a_mid = (a1 + a2)/2;
  update_f_g(A, B, a1, a2, b1, b2);

  int b_mid = b1, mx = -1;
  for(int i=b1;i<=b2+1;i++){
    if(mx < f[i] + g[b2-i+b1+1]){
      mx = f[i] + g[b2-i+b1+1];
      b_mid = i;
    }
  }
  return hirschberg(A, B, a1, a_mid, b1, b_mid-1) + hirschberg(A, B, a_mid+1, a2, b_mid, b2);
}

string get_path(string &A, string &B){
  return hirschberg(A, B, 0, A.size()-1, 0, B.size()-1);
}