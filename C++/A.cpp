/*input
4 1
3
2 1 1
3 2 3
3
4 1 3
3 5 2
3
5 4 6
1 3 2
2
1 1
1 1
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

ll MOD = 1000000007;
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

int main()
{
  ifalse;
  int t, s;
  cin >> t >> s;
  while(t --) {
    int n;
    cin >> n;
    vector < int > v1(n), v2(n);
    for(auto &x: v1) {
      cin >> x;
    }
    for(auto &x: v2) {
      cin >> x;
    }

    sort(all(v1));
    sort(all(v2));

    bool flag = 0;
    for(int i = 0; i < n; i ++) {
      if(v1[i] >= v2[i]) {
        flag = 1;
        break;
      }
    }
    map < int, int > mp;
    mp[v1[0]] = mp[v2[0]] = 1;
    for(int i = 1; i < n; i ++) {
      if(mp[v1[i]]) {
        mp[v2[i]] = 1;
      } else {
        flag = 1;
        break;
      }
    }
    if(!flag) {
      cout << "YES";
    } else {
      cout << "NO";
    }
    nl;
  }
  return 0;
}