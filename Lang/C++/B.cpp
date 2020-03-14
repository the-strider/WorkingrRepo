/*input
1
8 30
2 3 1 4 5 6 7 8 
1 3 6 2 5 7 4 8 
1 2 3 6 4 5 8 7 
1 6 3 5 2 7 4 8 
1 3 2 4 6 5 7 8 
1 3 2 6 5 4 7 8 
1 2 6 3 4 5 8 7 
1 3 2 6 5 4 8 7 
1 3 2 4 6 8 5 7 
2 3 1 5 4 6 8 7 
1 6 3 5 2 4 7 8 
1 3 5 2 4 6 8 7 
2 1 3 6 5 4 7 8 
1 2 3 4 6 5 7 8 
2 1 3 5 4 6 7 8 
1 6 2 3 4 5 8 7 
1 6 2 3 5 4 8 7 
1 2 6 3 4 8 5 7 
1 3 2 6 4 5 7 8 
1 3 5 2 6 4 7 8 
2 1 6 3 5 7 4 8 
2 1 6 3 4 5 7 8 
1 6 2 3 4 8 5 7 
1 2 3 6 4 8 5 7 
1 2 3 6 5 4 8 7 
1 3 5 2 6 7 4 8 
1 3 2 5 4 6 7 8 
1 6 3 2 4 5 8 7 
1 6 3 2 4 8 5 7 
1 6 2 3 5 4 7 8 



*/

// Yet antother working brute force
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
const int N = 510;
bool pre[N][N];
int out_deg[N];
int n, k, deg;
vector < int > v[N / 5];
unordered_map < string, int > mp;

bool check(int a, int b)
{
  for(int j = 0; j < k; j ++) {
    int flag2 = 0;
    for(int l = 0; l < n; l ++) {
      if(a == v[j][l]) {
        flag2 = 1;
      }
      if(b == v[j][l] and flag2 == 1) {
        return 1;
      } 
    }
  }
  return 0;
}

void preprocess() 
{
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= n; j ++) {
      pre[i][j] = check(j, i);
    }
  }
}

void func(int visited[], int in[], int in_deg) 
{
  // string s = "";
  // for(int i = 1; i <= n; i ++) {
  //   s += to_string(visited[i]) + "|"; 
  // }
  // s += to_string(in_deg);

  // if(mp.find(s) != mp.end()) {
  //   return;
  // }
  for(int i = 1; i <= n; i ++) {
    if(visited[i] != 0) continue;
    for(int j = 1; j <= n; j ++) {
      if(i == j) continue;
      if(pre[i][j]) continue;

      visited[i] = j;
      in[j] ++;

      bool flag = (in[j] == 1);
      func(visited, in, in_deg - flag);

      visited[i] = 0;
      in[j] --;
    }
  }

  // mp[s] = 1;
  if(deg > in_deg) {
    deg = in_deg;
    for(int i = 1; i <= n; i ++) {
      out_deg[i] = visited[i];
    }
  }
}

int main()
{
  ifalse;
  int t;
  cin >> t;
  while(t --) {
    cin >> n >> k;
    for(int i = 0; i < k; i ++) {
      for(int j = 0; j < n; j ++) {
        int x;
        cin >> x;
        v[i].push_back(x);
      }
    }
  
    preprocess();
    
    deg = SINF;
    int visited[n + 1] = {0};
    int in[n + 1] = {0};

    func(visited, in, n);

    
    cout << deg, nl;
    for(int i = 1; i <= n; i ++) {
      cout << out_deg[i], sp;
    }
    nl;
    
    for(int i = 0; i <= k; i ++) {
      v[i].clear();
    }
    mp.clear();
    memset(out_deg, 0, sizeof(out_deg));
  }
  return 0;
}