//두 다항식 a, b의 곱 : O(nlgn)
typedef complex<double> base;
// typedef complex<long double> base;

long double PI = acos(-1.0L);

void fft(vector<base> &a, bool inv){
  int n = a.size();
  for(int i=1,j=0;i<n;i++){
    int bit = n >> 1;
    for (;j>=bit;bit>>=1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }
  for(int len=2;len<=n;len<<=1){
    long double ang = 2*PI/len*(inv?-1:1);
    base wlen(cos(ang), sin(ang));
    for (int i=0;i<n;i+=len){
      base w(1);
      for (int j=0;j<len/2;j++){
        base u = a[i+j], v = a[i+j+len/2]*w;
        a[i+j] = u+v;
        a[i+j+len/2] = u-v;
        w *= wlen;
      }
    }
  }
  if(inv) for(int i=0;i<n;i++) a[i] /= n;
}
 
vector<ll> multiply(vector<ll> &a, vector<ll> &b){
  vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while(n < max(a.size(), b.size())) n <<= 1; n <<= 1;
  fa.resize(n); fb.resize(n);
  fft(fa, 0); fft(fb, 0);
  for(int i=0;i<n;i++) fa[i] *= fb[i];
  fft(fa, 1);
  vector<ll> ret(n);
  for(int i=0;i<n;i++)
    ret[i] = ll(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
  return ret;
}