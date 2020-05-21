// Berlekamp-Massey : O(k^2log(m))
// 선형 점화식에 대하여 dp[n]이 k개의 이전 항으로 이루어져 있을 때
// 3k개의 항을 제공하면 알 수 있음 (이 때, 모듈러가 소수여야 가능)
// k*k의 행렬 생성 : O(k^2)
// 점화식의 m번째 항 : O(k^2log(m))
// https://koosaga.com/231

ll ipow(ll x, ll p){
	ll ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % MOD;
		piv = piv * piv % MOD;
		p >>= 1;
	}
	return ret;
}

vector<int> berlekamp_massey(vector<int> x){
	vector<int> ls, cur;
	int lf, ld;
	for(int i=0; i<x.size(); i++){
		ll t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + 1ll * x[i-j-1] * cur[j]) % MOD;
		}
		if((t - x[i]) % MOD == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % MOD;
			continue;
		}
		ll k = -(x[i] - t) * ipow(ld, MOD - 2) % MOD;
		vector<int> c(i-lf-1);
		c.pb(k);
		for(auto &j : ls) c.pb(-j * k % MOD);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % MOD;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % MOD);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % MOD + MOD) % MOD;
	return cur;
}

int get_nth(vector<int> rec, vector<int> dp, ll n){
	int m = rec.size();
	vector<int> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<int> v, vector<int> w){
		int m = v.size();
		vector<int> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] += 1ll * v[j] * w[k] % MOD;
				if(t[j+k] >= MOD) t[j+k] -= MOD;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += 1ll * t[j] * rec[k-1] % MOD;
				if(t[j-k] >= MOD) t[j-k] -= MOD;
			}
		}
		t.resize(m);
		return t;
	};
	while(n){
		if(n & 1) s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	ll ret = 0;
	for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % MOD;
	return ret % MOD;
}

int guess_nth_term(vector<int> x, ll n){
	if(n < x.size()) return x[n];
	vector<int> v = berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v, x, n);
}

struct elem{int x, y, v;}; // A_(x, y) <- v, 0-based. no duplicate please..

vector<int> get_min_poly(int n, vector<elem> M){
	// smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
	vector<int> rnd1, rnd2;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub){
		return uniform_int_distribution<int>(lb, ub)(rng);
	};
	for(int i=0; i<n; i++){
		rnd1.pb(randint(1, MOD - 1));
		rnd2.pb(randint(1, MOD - 1));
	}
	vector<int> gobs;
	for(int i=0; i<2*n+2; i++){
		int tmp = 0;
		for(int j=0; j<n; j++){
			tmp += 1ll * rnd2[j] * rnd1[j] % MOD;
			if(tmp >= MOD) tmp -= MOD;
		}
		gobs.pb(tmp);
		vector<int> nxt(n);
		for(auto &i : M){
			nxt[i.x] += 1ll * i.v * rnd1[i.y] % MOD;
			if(nxt[i.x] >= MOD) nxt[i.x] -= MOD;
		}
		rnd1 = nxt;
	}
	auto sol = berlekamp_massey(gobs);
	reverse(sol.begin(), sol.end());
	return sol;
}

ll det(int n, vector<elem> M){
	vector<int> rnd;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub){
		return uniform_int_distribution<int>(lb, ub)(rng);
	};
	for(int i=0; i<n; i++) rnd.pb(randint(1, MOD - 1));
	for(auto &i : M){
		i.v = 1ll * i.v * rnd[i.y] % MOD;
	}
	auto sol = get_min_poly(n, M)[0];
	if(n % 2 == 0) sol = MOD - sol;
	for(auto &i : rnd) sol = 1ll * sol * ipow(i, MOD - 2) % MOD;
	return sol;
}

vector<int> x(3 * k);
cout << guess_nth_term(x, m) << '\n';