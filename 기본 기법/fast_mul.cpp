ll fast_mul(ll x, ll n){
  if(n == 0) return 1LL;
  if(n % 2 == 1) return (fast_mul(x, n-1) * x) % MOD;
  ll h = fast_mul(x, n/2) % MOD;
  return (h * h) % MOD;
