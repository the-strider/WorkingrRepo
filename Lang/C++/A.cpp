/*input
2
3 3
1 2
2 3
3 1
7 6
1 2
2 3
3 4
4 5
5 6
6 7
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
const int N = 25;
set < int > v[N];
vector < pair < int, int > > v1;
bool flag = 0;
string ans = "";
int n, m;
bool flag2 = 0;
bool visited[N] = {0};
bool instack[N] = {0};
map < string, int > mp;

void dfs(int c, int parent)
{
  visited[c] = 1;
  instack[c] = 1;
  for(auto x : v[c]) {
    if(x != parent and visited[x] and instack[x]) {
      flag2 = 1; // Cycle is present
    }
    if(!visited[x]) {
      dfs(x, c);
    }
  }
  instack[c] = 0;
}

bool checkEggSum() 
{
  memset(visited, 0, sizeof(visited));
  memset(instack, 0, sizeof(instack));
  flag2 = 0;

  for(int i = 1; i <= n; i ++) {
    if(not visited[i]) dfs(i, 0);
  }

  if(flag2) {
    return 0;
  }
  for(int i = 1; i <= n; i ++) {
    for(auto x: v[i]) {
      for(auto y: v[i]) {
        if(x == y) continue;
        if((v[x].find(y) == v[x].end()) and (v[y].find(x) == v[y].end())) {
          return 0;
        }
      }
    }
  }
  return 1;
}

void func(int idx, string res)
{
  if(flag) {
    return;
  }
  if(mp.find(res) !=  mp.end()) {
    cout << "hello";
    return;
  }
  if(idx == m) {
    for(int i = 1; i <= n; i ++) {
      v[i].clear();
    }
    for(int i = 0; i < m; i ++) {
      if(res[i] == '^') {
        v[v1[i].first].insert(v1[i].second);
      } else {
        v[v1[i].second].insert(v1[i].first);
      }
    }
    if(checkEggSum()) {
      ans = res;
      flag = 1;
    }
    return;
  }

  res += '^';
  func(idx + 1, res);
  res[res.length() - 1] = 'v';
  func(idx + 1, res);
}

int main()
{
  ifalse;
  int t;
  cin >> t;
  while(t --) {
    cin >> n >> m;
    for(int i = 0; i < m; i ++) {
      int x, y;
      cin >> x >> y;
      v1.push_back({x, y});
    }

    ans = "";
    flag = 0;
    func(0, "");
    if(flag) {
      cout << ans, nl;
    } else {
      cout << "No solution", nl;
    }

    for(int i = 1; i <= n; i ++) {
      v[i].clear();
    }
    mp.clear();
    v1.clear();
  }
  return 0;
}