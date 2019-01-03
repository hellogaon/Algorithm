int gcd(int a, int b){
  return b ? gcd(b, a%b) : a;
}

int lcm(int a, int b){
  return a*b/gcd(a,b);
}

//확장 유클리드 호제법
//as + bt = gcd(a,b)에서의 s,t 값을 구한다.
int extended_gcd(int a, int b, int &s, int &t){
  if(!b){
    s = 1, t = 0;
    return a;
  }
  int q = a/b, r = a%b, sp, tp;
  int g = extended_gcd(b,r,sp,tp);
  s = tp; t = sp-tp*q;
  return g;
}