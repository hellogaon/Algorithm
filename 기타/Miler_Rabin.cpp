// 밀러-라빈 소수 판별법 : 어떤 홀수 N이 소수인지 확률적으로 판별해주는 알고리즘
// s를 N−1 = d*2^s 라 할 때, 다음 중 하나가 성립
// A^d ≡ 1 (mod N)
// r = 0,1,2, ..., s-1 중 적어도 하나에 대해 A^(d*2^r) ≡ -1 (mod N)
// N < 2^32 : A = {2, 7, 61}
// N < 2^64 : A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}

typedef unsigned long long ull;

ull pow(ull a, ull x, ull mod){
  a %= mod;
  ull ret = 1ULL;
  while(x){
    if(x % 2) ret = (ret * a) % mod;
    a = (a * a) % mod;
    x /= 2;
  }
  return ret;
}

bool miler_rabin(ull n, ull a){
  ull d = n-1, s = 0;
  while(d % 2 == 0){
    if(pow(a, d, n) == n-1) return true;
    d /= 2;
  }
  ull ret = pow(a, d, n);
  if(ret == 1 || ret == n-1) return true;
  return false;
}

bool is_prime(ull n){
  if(n <= 1) return false;
  if(n == 2) return true;
  if(n <= 10000ULL){
    for(ull i=2;i*i<=n;i++)
      if(n % i == 0) return false;
    return true;
  }
  for(auto a : {2, 7, 61}){
    if(!miler_rabin(n, a)) return false;
  }
  return true;
}
