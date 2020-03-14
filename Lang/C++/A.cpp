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
const int N = 503;
vector < int > v[N];
vector < int > graph[N];
int n, k;

bool check(int a, int b)
{
  // a -> b
  for(int j = 0; j < k; j ++) {
    int flag = 0;
    for(int l = 0; l < n; l ++) {
      if(b == v[j][l]) {
        flag = 1;
      }
      if(a == v[j][l] and flag == 1) {     // if b -> a return 0
        return 0;
      } 
    }
  }
  return 1;
}

void preprocess() 
{
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= n; j ++) {
      if(i == j) continue;
      if(check(i, j)) {
        graph[i].push_back(j);
      }
    }
  }
}

int deg = SINF, prev_deg = 0;
int out[N];
bool visited[N];
void dfs2(int s, int edge[], int indegree[])
{
  if(edge[s]) return;
  for(auto x: graph[s]) {
    if(indegree[x]) continue;
    edge[s] = x;
    indegree[x] = 1;
    dfs2(x, edge, indegree);
    edge[s] = 0;
    indegree[x] = 0;
  }
  int cnt = 0;
  for(int i = 1; i <= n; i ++) {
    cnt += (indegree[i] == 0);
  }
  if(deg > cnt) {
    deg = cnt;
    for(int i = 1; i <= n; i ++) {
      out[i] = edge[i];
    }
  }
}

void dfs3(int s, int edge, int indegree[])
{
  if(edge[s]) return;
  for(auto x: graph[s]) {
    if(indegree[x]) continue;
    edge[s] = x;
    indegree[x] = 1;
    dfs3(x, edge, indegree);
    edge[s] = 0;
    indegree[x] = 0;
  }
  int cnt = 0;
  for(int i = 1; i <= n; i ++) {
    cnt += (indegree[i] == 0);
  }
  if(cnt == deg) {
    for(int i = 1; i <= n; i ++) {
      out[i] = edge[i];
    }
  }
}
void func(int s)
{
  deg = SINF;
  memset(visited, 0, sizeof(visited));
  visited[s] = 1;
  int edge[N] = {0}, indegree[N] = {0};
  for(int i = 1; i <= n; i ++) {
    out[i] = 0;
  }

  dfs2(s, edge, indegree);
  // for(int x = 1; x <= n; x ++) {
  //   if(out[x] == 0) {
  //     for(int i = 1; i <= n; i ++) {
  //       edge[i] = out[i];
  //       indegree[out[i]] = out[i] ? 1: 0;
  //     }
  //     deg = SINF;
  //     dfs2(x, edge, indegree);
  //   }
  // }
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

    int res_deg = SINF, res[N] = {0};
    for(int x = 1; x <= n; x ++) {
      func(x);
      int indegree[N] = {0};
      int cnt = 0;
      for(int i = 1; i <= n; i ++) {
        if(out[i] == 0) continue;
        indegree[out[i]] = 1;
      }
      for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
          if(indegree[j] or out[i] or !check(i, j)) continue;
          out[i] = j;
          indegree[j] = 1;
        }
      }
      for(int i = 1; i <= n; i ++) {
        cnt += (indegree[i] == 0);
      }
      if(res_deg > cnt) {
        res_deg = cnt;
        for(int i = 1; i <= n; i ++) {
          res[i] = out[i];
        }
      }
    }
    
    cout << res_deg, nl;
    for(int i = 1; i <= n; i++) {
      cout << res[i], sp;
    }
    nl;
    for(int i = 0; i < N; i ++) {
      graph[i].clear();
      v[i].clear();
    }
    memset(out, 0, sizeof(out));
  }
  return 0;
}