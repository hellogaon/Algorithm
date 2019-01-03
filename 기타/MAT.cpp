//K차 피보나치의 N번째 항 구현 
int K,N;

struct MAT{
  ll m[50][50];
  MAT operator * (const MAT &ot)const{
    MAT ret;
    for(int i=0;i<K;i++)
      for(int j=0;j<K;j++){
        ret.m[i][j] = 0;
        for(int k=0;k<K;k++)
          ret.m[i][j] = (ret.m[i][j] + (m[i][k]*ot.m[k][j])%MOD)%MOD;
      }
    return ret;
  }
} I,V;
 
int main(){
  scanf("%d %d",&K,&N);
  for(int i=0;i<K;i++)
    I.m[i][i] = V.m[0][i] = 1;
  for(int i=1;i<K;i++)
    V.m[i][i-1] = 1;
  for(;N;N>>=1,V=V*V)
    if(N&1) I = I*V;
  printf("%d\n", I.m[0][1]);
}