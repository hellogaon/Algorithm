//Manacher - 펠린드롬 판별 알고리즘 : O(N)
const int MAXN = 2000001;

int pal[MAXN*2+1];

void manacher(char *str){
  char s[MAXN*2+1] = {};
  int len = strlen(str);
  for(int i=0;i<len;i++){
    s[i*2] = str[i];
    if(i != len-1) s[i*2+1] = '#';
  }
  int c = 0, r = 0; len = strlen(s);
  for(int i=0;i<len;i++){
    int mirr = i-2*(i-c);
    if(i < r) pal[i] = min(r-i,pal[mirr]);
    while(i-pal[i]>0 && i+pal[i]-1<len && s[i-pal[i]-1]==s[i+pal[i]+1]) pal[i]++;
    if(pal[i]+i > r) r = pal[i]+i, c = i;
  }
}