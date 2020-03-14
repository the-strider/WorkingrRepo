/*input
1
5
1 2 1 2 2
3
1 1
2 3
2 5
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

ll MOD = 998244353;
const int SINF = 1000000009;
const ll INF =  1000000000000000018;

#define sp          cout << " "
#define nl          cout << "\n"
#define inv(a)      powr((a), (MOD - 2))
#define all(c)      (c).begin(),(c).end()
#define rep(i,a,b)  for(ll i = (a); i < (b); i ++)
#define prec(n)     cout << fixed << setprecision(n)
#define PI          3.14159265358979323846264338327951
#define ifalse      ios_base::sync_with_stdio(false), cin.tie(NULL)

template<typename T> void toInt(string s, T &a) { istringstream(s) >> a; }
ll gcd(ll a, ll b) { ll t; while(a) { t = a; a = b%a; b = t; } return b; }
ll sub(ll a, ll b) { a -= b; a = (a + MOD) % MOD; return a; }
ll mul(ll a, ll b) { return ((a % MOD) * (b % MOD)) % MOD; }
ll add(ll a, ll b) { a += b; a %= MOD; return a; }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }

ll powr(ll a, ll b) {
  ll x = 1LL;
  while(b) {
    if(b & 1) x = mul(x, a);
    a = mul(a, a), b >>= 1;
  }
  return x;
}

bool check(ll n)
{
  if(n == 1) return 0;
  if(n == 2 or n == 3) return 1;
  if(n%2 == 0 or n%3 == 0) return 0;
  for(ll i = 5; i*i <= n; i += 6) if(n%i == 0 or n % (i+2) == 0) return 0;
  return 1;
}

/*********************************START**********************************/
const int N = 100005;

ll pre_inv[N];
ll fact[N];

void init()
{
  fact[0] = 1;
  pre_inv[0] = 1;
  for(int i = 1; i < N; i ++) {
    fact[i] = mul(fact[i - 1], i);
    pre_inv[i] = powr(fact[i], MOD - 2);
  }
}

ll compute(ll n, ll r)
{
  ll d1 = fact[n];
  ll d2 = mul(pre_inv[r], pre_inv[n - r]);
  return mul(d1, d2);
}

int main()
{
  ifalse;
  init();
  int t;
  cin >> t;
  while(t --) {
    int n;
    cin >> n;
    vector < ll > v(n);
    for(auto &x: v) {
      cin >> x;
    }

    int q;
    cin >> q;
    while(q --) {
      int l, r;
      cin >> l >> r;
      l --, r --;
      map < ll, int > mp;
      for(int i = l; i <= r; i ++) {
        mp[v[i]] ++;
      }
      ll d = 0;
      for(auto x: mp) {
        d ^= x.second;
      }
      ll ans = 0;
      for(auto x: mp) {
        ll u = (x.second ^ d);
        if(u < x.second) {
          ans = add(ans, compute(x.second, x.second - u));
        }
      }
      cout << ans, nl;
    }
  }
  return 0;
}