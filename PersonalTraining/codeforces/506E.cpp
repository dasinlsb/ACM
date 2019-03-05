/*
设f[l][r]表示从最终串的两边往中间还原，还未匹配原串s[l..r]，由于求的是本质不同的回文串数量，所以在转移的时候一旦可以匹配原串就必须匹配
先只考虑n+m为偶数的情况，这样可以列出一个O(n^2)点数的状态转移图，除了终点以外的所有点都有边权为25/24的自环，直接暴力矩阵快速幂无法接受，考虑压缩状态
通过拓扑dp求出g[x][(n+1-x)/2]表示到终点路径上恰有x个24自环的路径数
接下来需要构造的技巧..一个25->x可以拆成24->x,25->x，24->25，因为从24走一步到25的决策等价于原地不动
这样的话状态变成(i,0)和(n,i)，可以发现两维是分别单调不降的，排成一排从左连到右，再加上自环和连向终点的路径即可，点数1.5*n，可以直接矩阵快速幂
考虑n+m为奇数的情况，唯一非法的情况是xx->__这种最后恰好从xx走到__的方案数，其他方案比如x->_可以看作把最后一次加的两个字母合并成一个，都可以一一映射合法方案
相当于少走一步并将终点改为xx，这样和恰好多走一步走到__的方案恰好一一对应
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int mod = 10007;

void add(int &x, int y) {
  if (x += y, x >= mod) x -= mod;
}
int mul(int x, int y) {
  return x * y % mod;
}
char s[maxn];
int n, m;
int ways[maxn][maxn][maxn], totalWays[2][maxn][maxn];

auto solve(int steps) {
  int maxDiff = n; 
  int maxSame = n + 1 >> 1; 
  int fin_state = maxDiff + maxSame + 1;
  int mat_sz = fin_state + 1;
  vector<vector<int> > g(mat_sz, vector<int>(mat_sz));
  auto adde = [&](int x, int y, int z) {
    g[x][y] = z;
    // cerr << "adde " << x << " " << y << " " << z << endl;
  };
  for (int i = 1; i < fin_state; i++) {
    if (i != fin_state - 1) adde(i, i + 1, 1);
    adde(i, fin_state, totalWays[0][min(maxDiff, i)][max(0, i - maxDiff)]);
    adde(i, i, i > maxDiff ? 25 : 24);
  }
  adde(fin_state, fin_state, 26);
  auto mul_matrix = 
  [&](vector<vector<int> > &a, 
      vector<vector<int> > &b) {
    static int c[maxn * 2][maxn * 2];
    for (int i = 0; i < a.size(); i++) {
      for (int j = 0; j < b[0].size(); j++) {
        c[i][j] = 0;
        for (int k = 0; k < b.size(); k++)
          add(c[i][j], mul(a[i][k], b[k][j]));
      }
    }
    for (int i = 0; i < a.size(); i++){
      for (int j = 0; j < a[0].size(); j++)
        a[i][j] = c[i][j];
    }
  };
  auto _f = g, _g = g;
  for (int i = 0; i < mat_sz; i++) {
    for (int j = 0; j < mat_sz; j++) {
      _f[i][j] = i == j ? 1 : 0;
    }
  }
  for (int k = steps - 1; k > 0; k >>= 1) {
    if (k & 1) mul_matrix(_f, g);
    mul_matrix(g, g);
  }
  auto f = _f;
  mul_matrix(f, _g);
  int ans = f[1][fin_state];
  // cerr << "init " << ans << endl;
  if (n + m & 1) {
    for (int i = 1; i < fin_state; i++) {
      int x = (i <= maxDiff ? i : maxDiff);
      int y = (i <= maxDiff ? 0 : i - maxDiff);
      // cerr << x << " " << y << " " << _f[1][fin_state] << " " << totalWays[0][x][y] << endl;
      add(ans, mod - mul(_f[1][i], totalWays[1][x][y]));
    }
  }
  return ans;
}
int main() {
  scanf("%s%d", s + 1, &m);
  n = strlen(s + 1);
  ways[1][n][0] = 1;
  for (int d = n; d; d--) {
    for (int l = 1; l + d - 1 <= n; l++) {
      int r = l + d - 1;
      for (int cntDiff = n; cntDiff >= 0; cntDiff--) {
        int cntSame = n - cntDiff + 1 >> 1;
        if (s[l] != s[r]) {
          ways[l][r][cntDiff] = cntDiff ? ways[l][r][cntDiff - 1] : 0;
        }
        if (d == 1) {
          add(totalWays[0][cntDiff][cntSame], ways[l][r][cntDiff]);
        } else if (d == 2 && s[l] == s[r]) {
          add(totalWays[0][cntDiff][cntSame], ways[l][r][cntDiff]);
          add(totalWays[1][cntDiff][cntSame], ways[l][r][cntDiff]);
        } else {
          if (s[l] != s[r]) {
            add(ways[l + 1][r][cntDiff], ways[l][r][cntDiff]);
            add(ways[l][r - 1][cntDiff], ways[l][r][cntDiff]);
          } else {
            add(ways[l + 1][r - 1][cntDiff], ways[l][r][cntDiff]);
          }
        }
      }
    }
  }
  for (int s = 0; s < 2; s++) {
    for (int i = 0; i <= n; i++) {
      for (int j = n; j > 0; j--) {
        add(totalWays[s][i + 1][j], totalWays[s][i][j]);
        add(totalWays[s][i + 1][j - 1], totalWays[s][i][j]);
      }
    }
  }
  int ans = solve(n + m + 1 >> 1);
  printf("%d\n", ans);
  return 0;
} 