ll gcd(ll a, ll b){
  return b ? gcd(b, a%b) : a;
}

ll lcm(ll a, ll b){
  return a*b/gcd(a, b);
}

//확장 유클리드 호제법
//as + bt = gcd(a,b)에서의 s,t 값을 구한다.
//해가 존재하려면 As + Bt = C에서 C가 gcd(A,B)의 배수여야 한다.
//ax + My = 1일 때 x는 a의 M에 대한 곱셈의 역원
ll extended_gcd(ll a, ll b, ll &s, ll &t){
  if(!b){
    s = 1, t = 0;
    return a;
  }
  ll q = a/b, r = a%b, sp, tp;
  ll g = extended_gcd(b, r, sp, tp);
  s = tp; t = sp-tp*q;
  return g;
}