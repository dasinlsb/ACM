/*
先把原矩阵拆成一个全一矩阵和另一个矩阵A的和
相当于对于所有i of [0,k]，求出A中选出恰好i个不同行不同列的格子的乘积之和
这是一个经典的二分图匹配问题，强制规定右半边点数较小，设左右点数分别为X, Y，那么可以用O(K*2^Y)的时间复杂度解决
但是当两边点数都比较多时会比较慢，有另一种做法是先求出任一生成树，然后2^c枚举非数边选取情况然后树形dp，时间复杂度是O(2^(K-X-Y+1)*(X+Y)^2)
两种算法取最优可以保证时间复杂度是正确的
*/
#include <bits/stdc++.h>
using namespace std;
const int maxk = 52;
const int mod = 1e9 + 7;
void add(int& x, int y) {
  if (x += y, x >= mod) x -= mod;
}
int mul(int x, int y) {
  return 1LL * x * y % mod;
}
vector<int> solve_line(vector<int> side[2], 
                      vector<vector<pair<int, int> > > G) {
  static int f[2][1 << 20];
  // cerr << "line" << endl;
  fill(f[0], f[0] + (1 << side[1].size()), 0);
  f[0][0] = 1;
  for (int l = 0; l < side[0].size(); l++) {
    fill(f[~l & 1], f[~l & 1] + (1 << side[1].size()), 0);
    for (int rs = 0; rs < 1 << side[1].size(); rs++) {
      if (!f[l & 1][rs]) continue;
      add(f[~l & 1][rs], f[l & 1][rs]);
      for (auto pv : G[l]) {
        int v = pv.second - side[0].size();
        if (rs >> v & 1) continue;
        add(f[~l & 1][rs | 1 << v], mul(f[l & 1][rs], pv.first));
      }
    }
  }
  vector<int> res(side[1].size() + 1);
  for (int rs = 0; rs < 1 << side[1].size(); rs++) {
    add(res[__builtin_popcount(rs)], f[(int)side[0].size() & 1][rs]);
  }
  return res;
}
vector<int> solve_tree(vector<int> side[2], 
                      vector<vector<pair<int, int> > > G) {
  // cerr << "tree" << endl;
  static int vis[maxk], is_removed[maxk], sz[maxk];
  static int dp[maxk][2][maxk];
  vector<pair<int, pair<int, int> > > more;
  function<void(int, int)> 
  dfs_init = [&](int x, int f) {
    sz[x] = 1;
    for (auto pv : G[x]) {
      int v = pv.second;
      if (!sz[v]) dfs_init(v, x), sz[x] += sz[v];
      else if (v != f && x < v) {
        more.push_back(make_pair(pv.first, make_pair(x, v)));
      }
    }
  };
  int n = side[0].size() + side[1].size();
  fill(sz, sz + n, 0);
  dfs_init(0, -1);
  assert(more.size() <= 20);
  vector<int> res(side[1].size() + 1);
  for (int status = 0 ; status < 1 << more.size(); status++) {
    fill(is_removed, is_removed + n, 0);
    int cost = 1;
    bool is_legal = true;
    for (int i = 0 ; i < more.size(); i++) {
      if (status >> i & 1) {
        auto [x,y] = more[i].second;
        if (is_removed[x] || is_removed[y]) {
          is_legal = false; break;
        }
        is_removed[x] = is_removed[y] = 1;
        cost = mul(cost ,more[i].first);
      }
    }
    if (!is_legal) continue;
    fill(vis, vis + n, 0);
    function<void(int)> dfs_dp = [&](int x) {
      vis[x] = 1;
      fill(dp[x][0], dp[x][0] + sz[x], 0);
      fill(dp[x][1], dp[x][1] + sz[x], 0);
      dp[x][0][0] = 1;
      sz[x] = 1;
      for (auto pv : G[x]) {
        int v = pv.second;
        if (vis[v]) continue;
        dfs_dp(v);
        fill(dp[n][0], dp[n][0] + sz[x] + sz[v], 0);
        fill(dp[n][1], dp[n][1] + sz[x] + sz[v], 0);
        for (int i = 0; i < sz[x]; i++) {
          for (int j = 0; j < sz[v]; j++) {
            if (!is_removed[x] && !is_removed[v]) {
              add(dp[n][1][i + j + 1], mul(mul(dp[x][0][i], dp[v][0][j]), pv.first));
            }
            for (int di : {0, 1}) {
              for (int dj : {0, 1}) {
                add(dp[n][di][i + j], mul(dp[x][di][i], dp[v][dj][j]));
              }
            }
          }
        }
        sz[x] += sz[v];
        for (int di : {0, 1}) {
          for (int i = 0; i < sz[x]; i++) {
            dp[x][di][i] = dp[n][di][i];
          }
        }
      }
    };
    dfs_dp(0);
    for (int i = 0; i < n; i++) {
      int _i = i + __builtin_popcount(status);
      if (_i < res.size()) {
        add(res[_i], mul(cost, dp[0][0][i] + dp[0][1][i]));
      }
    }
  }
  return res;
}
int main() {
  srand(time(0));
  int n, kk; 
  scanf("%d%d", &n, &kk);
  map<int, vector<pair<int, int> > > G;
  for (int i = 0; i < kk; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    x-- ; y--; z--;
    G[x].push_back(make_pair(z, n + y));
    G[n + y].push_back(make_pair(z, x));
  }
  vector<int> dp(kk + 1);
  dp[0] = 1;
  vector<int> pside(n * 2, -1);
  for (int x = 0; x < n; x++) {
    if (!G.count(x) || ~pside[x]) continue;
    vector<int> side[2];
    function<void(int, int)>
    dfs = [&](int x, int d) {
      pside[x] = side[d].size();
      side[d].push_back(x);
      for (auto pv : G[x]) {
        int v = pv.second;
        if (~pside[v]) continue;
        dfs(v, d ^ 1);
      }
    };
    dfs(x, 0);
    if (side[0].size() < side[1].size()) {
      swap(side[0], side[1]);
    }
    vector<vector<pair<int, int> > > _G(side[0].size() + side[1].size());
    for (int x : side[0]) {
      int idx = pside[x];
      for (auto pv : G[x]) {
        int idv = side[0].size() + pside[pv.second];
        // cerr << "_G " << idx << " " << idv << endl;
        _G[idx].push_back(make_pair(pv.first, idv));
        _G[idv].push_back(make_pair(pv.first, idx));
      }
    }
    vector<int> sub_dp;
    if (side[1].size() <= 20) {
      sub_dp = solve_line(side, _G);
    } else {
      sub_dp = solve_tree(side, _G);
    }
    sub_dp.resize(kk + 1, 0);
    for (int i = kk; i >= 0; i--) {
      dp[i] = mul(dp[i], sub_dp[0]);
      for (int j = 1; j < sub_dp.size() && j <= i; j++) {
        add(dp[i], mul(dp[i - j], sub_dp[j]));
      }
    }
  }
  int fac = 1, ans = 0;
  for (int i = 1; i <= n; i++) {
    fac = 1LL * fac * i % mod;
    if (i >= n - kk) add(ans, mul(fac, dp[n - i]));
  }
  printf("%d\n", ans);
  return 0;
}