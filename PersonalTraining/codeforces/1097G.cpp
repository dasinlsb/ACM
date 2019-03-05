/*
\sum_{X}f[x]^K = \sum_{0<=i<=K}stiring2(K, i)*i!*\sum_{X}C(f[x], i)
后面的\sum_{X}C(f[x], i)的组合意义就是对于每种选i条边的选边方案，有多少个点集的生成树包括这些边
如果确定了一种选边方案，那么合法点集数肯定是若干个2^x和若干个2^y-1的乘积
考虑树形dp，对于每种选边方案都在[第一次出现这种方案时]在[所有边的LCA处]统计答案
考虑当前在子树x，正在考虑子树v的合并，讨论一下x,v两棵树分别是否非空一共4种情况
只要保证当前子树中最下面一层已选边的上方的点集的贡献是2^x,下方点集贡献是若干个2^y-1即可
dp过程中可能产生边集不是当前子树根的情况，所以可以考虑分开求dp数组和贡献数组
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
const int maxk = 205;
const int mod = 1e9 + 7;
const int inv2 = 50000 * 10000 + 4;
int n, kk;
int fa[maxn], sz[maxn], f[maxn][maxk], res[maxk];
int fac[maxn], inv[maxn], pw[maxn], inv_pw[maxn], S[maxk][maxk];

vector<int> G[maxn];

void add(int &x, int y) {
  if (x += y, x >= mod) x -= mod;
}
int mul(int x, int y) {
  return 1LL * x * y % mod;
}
void dfs1(int x) {
  static int g[maxk];
  sz[x] = 1;
  f[x][0] = 2;
  for (int v : G[x]) {
    if(v == fa[x]) continue;
    fa[v] = x;
    dfs1(v);
    fill_n(g, min(kk + 1, sz[x] + sz[v]), 0);
    int out_sz = n - sz[x] - sz[v];
    auto has = [&](int x) {
      return mul(inv_pw[x], pw[x] - 1);
    };
    for (int i = 0; i <= kk && i < sz[x]; i++) {
      for (int j = 0; i + j <= kk && j < sz[v]; j++) {
        int fv = mul(f[x][i], f[v][j]);
        add(g[i + j], fv);
        add(g[i + j + 1], j ? fv : mul(fv, has(sz[v])));
        if (i && j) {
          add(res[i + j], mul(pw[out_sz], fv));
          add(res[i + j + 1], mul(pw[out_sz], fv));
        } else if (!i && !j) {
          add(res[i + j + 1], mul(pw[sz[v]] - 1, pw[n - sz[v]] - 1));
        } else if (!j) {
          add(res[i + j + 1], mul(mul(pw[out_sz], f[x][i]), pw[sz[v]] - 1));
        } else if (!i) {
          add(res[i + j + 1], mul(pw[n - sz[v]] - 1, f[v][j]));
        }
      }
    }
    sz[x] += sz[v];
    for (int i = 0; i <= kk && i < sz[x]; i++) {
      f[x][i] = g[i];
      // cerr << "finish " << v << " " << i << "=" << g[i] << endl;
    }
    // for (int i = 0; i <= kk; i++) {
    //   cerr << "F " << res[i] << endl;
    // }
  }
  // cerr << endl;
}
int main() {
  fac[0] = 1;
  for (int i = 1; i < maxn; i++) fac[i] = mul(fac[i - 1], i);
  pw[0] = 1;
  for (int i = 1; i < maxn; i++) pw[i] = mul(pw[i - 1], 2);
  inv_pw[0] = 1;
  for (int i = 1; i < maxn; i++) inv_pw[i] = mul(inv_pw[i - 1], inv2);
  S[0][0] = 1;
  for (int i = 1; i < maxk; i++) {
    for (int j = 1; j <= i; j++) {
      S[i][j] = (S[i - 1][j - 1] + mul(S[i - 1][j], j)) % mod;
    }
  }
  scanf("%d%d", &n, &kk);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dfs1(1);
  int ans = 0;
  // cerr << "ans" << endl;
  for (int i = 0; i <= kk; i++) {
    // cerr << i << " " << res[i] << endl;
    add(ans, mul(res[i], mul(S[kk][i], fac[i])));
  }
  printf("%d\n", ans);
  return 0;
}