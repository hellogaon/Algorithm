//가장 긴 펠린드롬 부분 문자열의 개수: O(N)
char S[200003];
int pal[200003];

int palin(char* str){
  int c = 0, r = 0, len = strlen(S);
  for(int i=0;i<len;i++){
    int mirr = i-2*(i-c);
    if(i < r)
      pal[i] = min(r-i,pal[mirr]);
    while(i-pal[i]>0 && i+pal[i]-1<len && S[i-pal[i]-1]==S[i+pal[i]+1])
      pal[i]++;
    if(pal[i]+i > r){
      r = pal[i]+i;
      c = i;
    }
  }
  int ret = 0;
  for(int i=0;i<len;i++)
    ret = max(ret,pal[i]);
  return ret;
}

int main(){
  scanf("%s",S);
  int len = strlen(S);
  len = len * 2 + 1;
  for(int i=len;i>=0;i--){
    if(i % 2 == 0) S[i] = '#';
    else S[i] = S[i/2];
  }
  printf("%d\n",palin(S));
}