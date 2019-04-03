//Manacher - 펠린드롬 판별 알고리즘 : O(N)
const int MAXN = 2000001;

int S[MAXN*2+1], pal[MAXN*2+1];

void manacher(int len){
  len = len*2+1;
  for(int i=len-1;i>=0;i--){
    if(i % 2 == 0) S[i] = -1;
    else S[i] = S[i/2];
  }
  int r = 0, p = 0;
  for(int i=0;i<len;i++){
    if(i <= r) pal[i] = min(pal[2*p-i],r-i);
    while(i-pal[i]>0 && i+pal[i]+1<len && S[i-pal[i]-1]==S[i+pal[i]+1]) pal[i]++;
    if(r < i+pal[i]) r = i+pal[i], p = i;
  }
}
