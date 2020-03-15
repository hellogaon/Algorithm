// PollardRho와 Miler Rabin을 이용한 큰 수 소인수분해 (2^62-1)
typedef unsigned long long ull;

ull gcd(ull a, ull b) {
	return b ? gcd(b, a%b) : a;
}

ull abs(ull a){
  return a > 0 ? a : -a;
}

ull ull_add(ull n, ull k, ull mod){
  n %= mod; k %= mod;
  ull ret = 0;
  while(k){
    if(k % 2) ret = (ret + n) % mod;
    n = (n + n) % mod;
    k /= 2;
  }
  return ret;
}

ull ull_pow(ull a, ull x, ull mod){
  a %= mod;
  ull ret = 1;
  while(x){
    if(x % 2) ret = ull_add(ret, a, mod);
    a = ull_add(a, a, mod);
    x /= 2;
  }
  return ret;
}

ull f(ull a, ull c, ull mod){
  return (ull_pow(a, 2, mod) + c + mod) % mod;
}

bool miler_rabin(ull n, ull a){
  ull d = n-1, s = 0;
  while(d % 2 == 0){
    if(ull_pow(a, d, n) == n-1) return true;
    d /= 2;
  }
  ull ret = ull_pow(a, d, n);
  if(ret == 1 || ret == n-1) return true;
  return false;
}

bool is_prime(ull n){
  if(n <= 1) return false;
  if(n == 2) return true;
  if(n <= 10000000000ULL){
    for(ull i=2;i*i<=n;i++)
      if(n % i == 0) return false;
    return true;
  }
  for(auto a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
    if(!miler_rabin(n, a)) return false;
  }
  return true;
}

ull PollardRho(ull n){
  if(!(n % 2)) return 2;
  ull p0 = (rand() % (n-2)) + 2;
  ull c = (rand() % (n-1)) + 1;
  ull x = p0, y = p0, d = 1;
  while(d == 1){
    x = f(x, c, n);
    y = f(f(y, c, n), c, n);
    d = gcd(abs(x - y), n);
    if(d == n) return PollardRho(n);
  }
  return d;
}

vector<ull> ans;

void ull_factor(ull n){
  while(n != 1 && !is_prime(n)){
    ull d;
    bool is_ans = false;
    d = PollardRho(n);
    if(is_prime(d))
      ans.pb(d);
    else ull_factor(d);
    n /= d;
  }
  ans.pb(n);
  sort(ans.begin(), ans.end());
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL)); 

  ull N;
  cin >> N;
  ull_factor(N);
  for(ull factor: ans)
    cout << factor << '\n';
}