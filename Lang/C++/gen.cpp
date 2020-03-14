/*input
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll , ll> PLL;
typedef long double ld;

#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
int mod = 1000000007;
#define PI 3.14159265
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl;
#define MAX 1501

template < typename T > T GCD(T a, T b)            { ll t; while(a) { t = a; a = b % a; b = t; } return b; }
template < typename T > string toString(T a)       { return to_string(a); }
template < typename T > void toInt(string s, T &x) { stringstream str(s); str >> x;}
inline int add(ll a, ll b) {a += b; if (a < 0) a += mod; return a;}
inline int sub(ll a, ll b) {a -= b; if (a < 0) a += mod; return a;}
inline int mul(ll a, ll b) {return (a * 1ll * b) % mod;}
inline int pwr(ll x, ll y) {
    int ans = 1 % mod;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ans;
}
inline int inv(int a) {return pwr(a, mod - 2);}

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

#define MIN_PER_RANK 1 /* Nodes/Rank: How 'fat' the DAG should be.  */
#define MAX_PER_RANK 5
#define MIN_RANKS 3    /* Ranks: How 'tall' the DAG should be.  */
#define MAX_RANKS 5
#define PERCENT 30     /* Chance of having an Edge.  */

int main (void)
{
  
  srand (time (NULL));

  int mxx = 8;
  for(int test = 1; test <= 2000; test ++) {
    int i, j, k,nodes = 0;
    int ranks = MIN_RANKS
                + (rand () % (MAX_RANKS - MIN_RANKS + 1));

    vector < pair < int, int > > v;
    int ma = 0;
    for (i = 0; i < ranks; i++) {
      /* New nodes of 'higher' rank than all nodes generated till now.  */
      int new_nodes = MIN_PER_RANK + (rand () % (MAX_PER_RANK - MIN_PER_RANK + 1));

      /* Edges from old nodes ('nodes') to new ones ('new_nodes').  */
      // cout << nodes << "\n";
      for (j = 0; j < nodes; j++) {
        for (k = 0; k < new_nodes; k++) {
          if ( (rand () % 100) < PERCENT) {
            v.push_back({j + 1, k + nodes + 1});
            ma = max({ma, j + 1, k + nodes + 1});
          }
          if(ma > mxx) break;
        }
        if(ma > mxx) break;
      }
      if(ma > mxx) break;
      nodes += new_nodes; /* Accumulate into old node set.  */
    }
    if(ma <= mxx and ma != 0) {
      cout << ma << " " << v.size() << "\n";
      for(auto x: v) {
        cout << x.first << " " << x.second << "\n";
      }
      break;
    }
  }
  return 0;
}