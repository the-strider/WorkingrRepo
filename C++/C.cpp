/*input
93
"kazxkmmctdgtrplfggliycskmbfzjkrsthahcrxaaylpdykqfyejwteexytvxgjrbviconioomfpznawsseisfcpfkuvx"
"lajtokckoizywvirjhccouuhjkkshdtzchzmiccujzpeqzcvfekdqjgrbkzrwfnfwhyvzrrrakiausbleeimmthaqqouh"
"kpvphwnkrtxuiuhb"

7
aabkhjk
dfssdfs
acac
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
string evil;
string s;
int lps[N];
ll dp[N][55][2][2];

void compute()
{
  int len = 0, i = 1;
  lps[0] = 0;
  while(i < evil.length()) {
    if(evil[i] == evil[len]) {
      len ++;
      lps[i] = len;
      i ++;
    } else {
      if(len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i ++;
      }
    }
  }
}

ll func(int idx, int idx2, bool flag, bool ok, string res_str)
{
  if(ok)  return 0;
  if(idx == s.length()) return 1;
  if(dp[idx][idx2][flag][ok] > -1) return dp[idx][idx2][flag][ok];

  ll res = 0;
  char c = 'z';
  if(!flag) {
    c = s[idx] - 1;
    string str2 = res_str + s[idx];
    if(evil[idx2] == s[idx]) {
      if(idx2 + 1 == evil.length()) {
        res = add(res, func(idx + 1, 0, 0, true, str2));
      } else {
        res = add(res, func(idx + 1, idx2 + 1, 0, false, str2));
      }
    } else {
      if(idx2 == 0) {
        res = add(res, func(idx + 1, idx2, 0, false, str2));
      } else {
        int j = lps[idx2 - 1];
        while(j > 0 and evil[j] != s[idx]) {
          j = lps[j - 1];
        }
        if(j == 0) {
          if(s[idx] == evil[j]) {
            res = add(res, func(idx + 1, 1, 0, false, str2));
          } else {
            res = add(res, func(idx + 1, 0, 0, false, str2));
          }
        } else {
          res = add(res, func(idx + 1, j + 1, 0, false, str2));
        }
      }
    }
  } 

  for(char i = 'a'; i <= c; i ++) {
    string str2 = res_str + i;
    if(evil[idx2] == i) {
      if(idx2 + 1 == evil.length()) {
        res = add(res, func(idx + 1, 0, 1, true, str2));
      } else {
        res = add(res, func(idx + 1, idx2 + 1, 1, false, str2));
      }
    } else {
      if(idx2 == 0) {
        res = add(res, func(idx + 1, idx2, 1, false, str2));
      } else {
        int j = lps[idx2 - 1];
        while(j > 0 and evil[j] != i) {
          j = lps[j - 1];
        }
        if(j == 0) {
          if(i == evil[j]) {
            res = add(res, func(idx + 1, 1, 1, false, str2));
          } else {
            res = add(res, func(idx + 1, 0, 1, false, str2));
          }
        } else {
          res = add(res, func(idx + 1, j + 1, 1, false, str2));
        }
      }
    }
  }
  return dp[idx][idx2][flag][ok] = res;
}

bool check(string &s1) 
{
  if(s1.find(evil) == string::npos) {
    return 1;
  } 
  return 0;
}

int main()
{
  ifalse;
  int n;
  string s1, s2;
  cin >> n >> s1 >> s2 >> evil;

  compute();

  s = s1;
  memset(dp,  -1, sizeof(dp));
  ll a = func(0, 0, 0, 0, "");

  s = s2;
  memset(dp, -1, sizeof(dp));
  ll b = func(0, 0, 0, 0, "");

  cout << add(sub(b, a), check(s1)), nl;
  return 0;
}