//행렬 곱셈
const int MSIZE = 51;

struct MAT{
  ll m[MSIZE][MSIZE];
  MAT operator *(const MAT &ot)const{
    MAT ret;
    for(int i=0;i<MSIZE;i++)
      for(int j=0;j<MSIZE;j++){
        ret.m[i][j] = 0;
        for(int k=0;k<MSIZE;k++)
          ret.m[i][j] += (m[i][k] * ot.m[k][j]) % MOD;
        ret.m[i][j] %= MOD;
      }
    return ret;
  }
} I,V;

MAT matN(ll n){
  for(int i=0;i<MSIZE;i++)
    for(int j=0;j<MSIZE;j++)
      I.m[i][j] = (i == j);
  MAT ret = I;
  for(;n;n>>=1,V=V*V) if(n&1) ret=ret*V;
  return ret;
}