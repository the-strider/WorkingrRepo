/*input
7
aabkhjk
dfssdfs
acac

6
"aabkhj"
"dfssdf"
"aaac"

7
aabkhjk
dfssdfs
acac



11
"aabkhjkaaka"
"dfssdfsaaaa"
"aaac"


93
kazxkmmctdgtrplfggliycskmbfzjkrsthahcrxaaylpdykqfyejwteexytvxgjrbviconioomfpznawsseisfcpfkuvx
lajtokckoizywvirjhccouuhjkkshdtzchzmiccujzpeqzcvfekdqjgrbkzrwfnfwhyvzrrrakiausbleeimmthaqqouh
kpvphwnkrtxuiuhb

7
aabkhjk
dfssdfs
acac

93
kazxkmmctdgtrplfggliycskmbfzjkrsthahcrxaaylpdykqfyejwteexytvxgjrbviconioomfpznawsseisfcpfkuvx
lajtokckoizywvirjhccouuhjkkshdtzchzmiccujzpeqzcvfekdqjgrbkzrwfnfwhyvzrrrakiausbleeimmthaqqouh
kpvphwnkrtxuiuhb
8
pzdanyao
wgpmtywi
sdka
3
aaa
ccc
ab
3
aaa
ccc
bb

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
string s, evil;
int len;
int evlen;
ll dp[505][2][55][2];
int lps[55];

void compute(string &s1)
{
  int len = 0;
  lps[0] = 0;
  int i = 1;
  while(i < s1.length()) {
    if(s1[i] == s1[len]) {
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

// ll func(int idx, bool flag, int idx2, bool ok)
// {
//   if(ok) return 0;
//   if(idx == len) return 1;
//   if(dp[idx][flag][idx2][ok] > -1) return dp[idx][flag][idx2][ok];

//   ll res = 0;
//   if(flag) {
//     for(char i = 'a'; i <= 'z'; i ++) {
//       if(evil[idx2] == i) {
//         if(idx2 + 1 == evlen) {
//           res = add(res, func(idx + 1, 1, 0, true));
//         } else {
//           res = add(res, func(idx + 1, 1, idx2 + 1, false));
//         }
//       } else {
//         if(idx2 == 0) {
//           res = add(res, func(idx + 1, 1, 0, false));
//         } else {
//           if(evil[lps[idx2 - 1]] == i) {
//             res = add(res, func(idx + 1, 1, lps[idx2 - 1] + 1, false));  
//           } else {
//             res = add(res, func(idx + 1, 1, 0, false));
//           }
//         }
//       }
//     }
//   } else {
//     char c = s[idx];
//     if(evil[idx2] == c) {
//       if(idx2 + 1 == evlen) {
//         res = add(res, func(idx + 1, 0, 0, true));
//       } else {
//         res = add(res, func(idx + 1, 0, idx2 + 1, false));
//       }
//     } else {
//       if(idx2 == 0) {
//         res = add(res, func(idx + 1, 0, 0, false));
//       } else {
//         if(evil[0] == c) {
//           res = add(res, func(idx + 1, 0, 0 + 1, false));  
//         } else {
//           res = add(res, func(idx + 1, 0, 0, false));
//         }
//       }
//     }
//     for(char i = 'a'; i < c; i ++) {
//       if(evil[idx2] == i) {
//         if(idx2 + 1 == evlen) {
//           res = add(res, func(idx + 1, 1, 0, true));
//         } else {
//           res = add(res, func(idx + 1, 1, idx2 + 1, false));
//         }
//       } else {
//         if(idx2 == 0) {
//           res = add(res, func(idx + 1, 1, 0, false));
//         } else {
//           if(evil[0] == i) {
//             res = add(res, func(idx + 1, 1, 0 + 1, false));  
//           } else {
//             res = add(res, func(idx + 1, 1, 0, false));
//           }
//         }
//       }
//     }
//   }
//   return dp[idx][flag][idx2][ok] = res;
// }

ll func(int idx, bool flag, int idx2, bool ok, string res_str)
{
  if(idx == len) {
    if(ok == false) {
      // cout << res_str, nl;
      return 1;
    }
    // cout << res_str, nl;
    return 0;
  }
  if(ok) {
    // cout << res_str, nl;
    return 0;
  }

  if(dp[idx][flag][idx2][ok] > -1) {
    return dp[idx][flag][idx2][ok];
  }

  ll res = 0;
  if(flag) {
    for(char i = 'a'; i <= 'z'; i ++) {
      if(evil[idx2] == i) {
        if(idx2 + 1 == evlen) {
          res = add(res, func(idx + 1, 1, 0, true, res_str + char(i)));
        } else {
          res = add(res, func(idx + 1, 1, idx2 + 1, false, res_str + char(i)));
        }
      } else {
        if(idx2 == 0) {
          res = add(res, func(idx + 1, 1, 0, false, res_str + char(i)));
        } else {
          cout << res_str << " " << idx2 << " " << i << " " << lps[idx2] << " " << lps[idx2 - 1], nl;
          if(evil[0] == i) {
            res = add(res, func(idx + 1, 1, 0 + 1, false, res_str + char(i)));  
          } else {
            res = add(res, func(idx + 1, 1, 0, false, res_str + char(i)));
          }
        }
      }
    }
  } else {
    char c = s[idx];
    if(evil[idx2] == c) {
      if(idx2 + 1 == evlen) {
        res = add(res, func(idx + 1, 0, 0, true, res_str + char(c)));
      } else {
        res = add(res, func(idx + 1, 0, idx2 + 1, false, res_str + char(c)));
      }
    } else {
      if(idx2 == 0) {
        res = add(res, func(idx + 1, 0, 0, false, res_str + char(c)));
      } else {
        if(evil[0] == c) {
          res = add(res, func(idx + 1, 0, 0 + 1, false, res_str + char(c)));  
        } else {
          res = add(res, func(idx + 1, 0, 0, false, res_str + char(c)));
        }
      }
    }
    for(char i = 'a'; i < c; i ++) {
      if(evil[idx2] == i) {
        if(idx2 + 1 == evlen) {
          res = add(res, func(idx + 1, 1, 0, true, res_str + char(i)));
        } else {
          res = add(res, func(idx + 1, 1, idx2 + 1, false, res_str + char(i)));
        }
      } else {
        if(idx2 == 0) {
          if(i == 'c') {
            cout << "hello " << " " << res_str,nl;
          }
          res = add(res, func(idx + 1, 1, 0, false, res_str + char(i)));
        } else {
          if(evil[0] == i) {
            res = add(res, func(idx + 1, 1, 0 + 1, false, res_str + char(i)));  
          } else {
            res = add(res, func(idx + 1, 1, 0, false, res_str + char(i)));
          }
        }
      }
    }
  }
  return dp[idx][flag][idx2][ok] = res;
}

bool check(string &s1)
{
  for(int i = 0; i < s1.length(); i ++) {
    int j = i;
    int idx = 0;
    while(idx < evlen and s1[j] == evil[idx]) {
      idx ++;
      j ++;
    }
    if(idx == evlen) {
      return 0;
    }
  }
  return 1;
}
int main()
{
  ifalse;
  int n;
  string s1, s2;
  cin >> n >> s1 >> s2 >> evil;
  evlen = evil.length();

  compute(evil);
  for(int i = 0; i < evil.length(); i ++) {
    cout << lps[i], sp;
  }
  len = s1.length();
  s = s1;
  memset(dp, -1, sizeof(dp));
  ll a = func(0, 0, 0, 0, "");
  
  s = s2;
  memset(dp, -1, sizeof(dp));
  ll b = func(0, 0, 0, 0, "");

  cout << add(sub(b, a), check(s1)), nl;
  return 0; 
}