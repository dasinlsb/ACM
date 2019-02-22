/*
O(n)枚举LCP，问题转化为快速求出 规定首元素0/1,长度为n，满足c[][]限制的方案数
10和01肯定是交替出现的，11和00的放置就是[把n个物品分成m堆可空]的方案，可以直接用组合数解决
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
const int mod = 1e9 + 7;
void add(int& x, int y) {
  if (x += y, x >= mod) x -= mod;
}
int mul(int x, int y) {
  return 1LL * x * y % mod;
}
int fac[maxn], inv[maxn], inv_fac[maxn];
int main() {
  // freopen("aa.in", "r", stdin);
  string A, B;
  cin >> B >> A;
  vector<vector<int> > c(2, vector<int>(2));
  for (auto& x : c) for (auto& y : x) cin >> y;
  fac[0] = 1;
  for (int i = 1; i < maxn; i++) fac[i] = 1LL * fac[i - 1] * i %mod;
  inv[0] = inv[1] = 1;
  for (int i = 2; i < maxn; i++) inv[i] = mod - 1LL * mod / i * inv[mod % i] % mod;
  inv_fac[0] = 1;
  for (int i = 1; i < maxn; i++) inv_fac[i] = 1LL * inv_fac[i - 1] * inv[i] % mod;
  auto C = [&](int x, int y) {
    if (x < 0 || y < 0) return 0;
    if (x < y) return 0;
    return (int)(1LL * fac[x] * inv_fac[y] % mod * inv_fac[x - y] % mod);
  };
  auto solve_all = [&](int p, int n, vector<vector<int> > c) {
    int cs = 0;
    for (auto& x : c) {
      for (auto& y : x) {
        if (y < 0) return 0;
        cs += y;
      }
    }
    if (cs != n) return 0;
    if (n == 0) return 1;
    int delta = c[p][1-p] - c[1-p][p];
    if (delta != 1 && delta != 0) return 0;
    if (c[p][1-p] == 0) return c[p][p] == n ? 1 : 0;
    auto divide = [&](int n, int m) {
      if (!n && !m) return 1;
      return C(n + m - 1, m - 1);
    };
    if (delta == 1) {
      return mul(divide(c[p][p], c[p][1-p]),
                  divide(c[1-p][1-p], c[1-p][p] + 1));
    } else {
      return mul(divide(c[p][p], c[p][1-p] + 1),
                  divide(c[1-p][1-p], c[1-p][p]));
    }
  };
  auto solve = [&](string s, vector<vector<int> > c) {
    vector<int> a;
    int n = s.size();
    for (int i = 0; i < n; i++) a.push_back(s[i] - '0');
    int res = 0;
    for (int i = 1; i < n; i++) {
      add(res, solve_all(1, n - i - 1, c));
    }
    // cerr << "0th: " << res << endl;
    for (int i = 1; i < n; i++) {
      c[a[i - 1]][0]--;
      if (a[i] == 1) {
        add(res, solve_all(0, n - i - 1, c));
      }
      // cerr << i << "th: " << res << endl;
      c[a[i - 1]][0]++;
      c[a[i - 1]][a[i]]--;
    }
    return res;
  };
  int ans = solve(A, c);
  add(ans, mod - solve(B, c));
  auto check_one = [&](string s, vector<vector<int> > c) {
    for (int i = 1; i < s.size(); i++) {
      c[s[i - 1] - '0'][s[i] - '0']--;
    }
    for (auto x : c) for (auto y : x) if (y) return false;
    return true;
  };
  if (check_one(A, c)) add(ans, 1);
  cout << ans << endl;
  return 0;
}