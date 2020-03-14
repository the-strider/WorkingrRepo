/*input
1
8 30
1 4 3 2 6 8 5 7 
1 3 2 6 4 8 5 7 
1 2 3 4 7 6 8 5 
1 3 4 7 2 6 8 5 
1 2 4 3 6 5 8 7 
1 3 2 4 5 6 7 8 
1 2 3 6 4 8 7 5 
1 3 2 4 5 6 8 7 
1 2 4 3 6 7 8 5 
1 4 3 7 2 6 5 8 
1 3 4 7 2 5 6 8 
1 3 2 4 6 5 8 7 
1 4 2 7 3 6 5 8 
1 2 3 4 5 7 6 8 
1 4 2 3 6 7 5 8 
1 3 4 2 5 6 8 7 
1 3 4 2 6 5 8 7 
1 2 3 6 8 4 5 7 
1 2 4 7 3 5 6 8 
1 3 2 4 6 7 5 8 
1 4 3 2 6 7 8 5 
1 4 3 2 5 6 8 7 
1 3 4 2 5 7 6 8 
1 2 3 6 4 5 7 8 
1 2 3 6 4 7 5 8 
1 3 2 4 6 8 5 7 
1 2 4 3 6 8 5 7 
1 3 4 2 6 8 5 7 
1 3 4 2 6 8 7 5 
1 3 4 2 6 5 7 8 
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
const int N = 505;
vector < int > v[N];
vector < int > graph[N];
vector < int > v1;
int in[N];
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
				in[j] ++;
			}
		}
	}
}

int visited[N];
vector < int > v2;	// store nodes
void dfs(int s)
{
	visited[s] = 1;
	v2.push_back(s);
	for(auto x: graph[s]) {
		if(!visited[x]) {
			dfs(x);
		}
	}
}

int deg = SINF, prev_deg = 0;
int out[N];
void dfs2(int s, int edge[], int indegree[])
{
	bool ok = 0;
	if(edge[s]) return;
	for(auto x: graph[s]) {
		if(!indegree[x]) continue;
		edge[s] = x;
		indegree[x] = 1;
		dfs2(x, edge, indegree);
		edge[s] = 0;
		indegree[x] = 0;
		ok = 1;
	}

	if(!ok) {
		int cnt = 0;
		for(int i = 1; i <= n; i ++) {
			cnt += (indegree[i] == 0);
		}
		if(deg > prev_deg + cnt) {
			deg = prev_deg + cnt;
			for(int i = 1; i <= n; i ++) {
				out[i] = edge[i];
			}
		}
	}
}

void func(int s)
{
	v2.clear();
	dfs(s);
	int edge[N], indegree[N];
	for(int i = 1; i <= n; i ++) {
		edge[i] = out[i];
		indegree[out[i]] = 1;
	}
	dfs2(s, edge, indegree);
	prev_deg = deg;
	for(auto x: v2) {
		if(out[x] == 0) {
			for(int i = 1; i <= n; i ++) {
				edge[i] = out[i];
				indegree[out[i]] ++;
			}
			dfs2(x, edge, indegree);
			prev_deg = deg;
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
  	
  	for(int i = 1; i <= n; i ++) {
  		if(in[i] == 0) {
  			v1.push_back(i);
  		}
  	}

  	memset(in, 0, sizeof(in));

  	for(auto x: v1) {
  		func(x);
  	}
  	cout << prev_deg, nl;
  	for(int i = 0; i < N; i ++) {
  		graph[i].clear();
  		v[i].clear();
  	}
  }
  return 0;
}