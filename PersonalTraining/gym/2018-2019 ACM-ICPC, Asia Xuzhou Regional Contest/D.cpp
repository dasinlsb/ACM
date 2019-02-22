/*
先转化为求三个A[]的合法公共子序列个数
考虑dp，f[i][j][k]表示三个串分别考虑了前i,j,k个
暴力转移是直接枚举下一个合法的(i',j',k')
但可以每一维分开转移，假设当前(i,j,k)满足a[i]==a[j]==a[k]
那么i这一维的递增需考虑M[a[j]][a[i']]==1，满足则转移到(i',j,k)
j，k维的递增只要满足a[j']==a[i]和a[k']==a[i]即可
在dp状态中增加一维[0/1/2]表示当前在考虑i/j/k的递增
时间复杂度O(3*n^3)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int mod = 1e9 + 7;

int n, a[maxn], M[maxn][maxn];
int f[maxn][maxn][maxn][3];

void up(int& x, int y) {
  if (x += y, x >= mod) x -= mod;
}
int main() {
  freopen("aa.in", "r", stdin);
  int _;
  scanf("%d", &_);
  for (; _--;) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) {
      static char s[maxn];
      scanf("%s", s);
      for (int j = 1; j <= n; j++) M[i][j] = s[j-1] - '0';
    }
    for (int i = 0; i <= n; i++) M[0][i] = 1;
    memset(f, 0, sizeof(f));
    f[0][0][0][0] = 1;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= n; k++) {
          // printf("%d %d %d: ", i, j, k);
          // for (int t = 0; t < 3; t++) {
          //   printf("%d ",f[i][j][k][t]);
          // }
          // puts("");
          //0
          up(f[i+1][j][k][0], f[i][j][k][0]);
          if (i+1 <= n && M[a[j]][a[i+1]])
            up(f[i+1][j][k][1], f[i][j][k][0]);
          //1
          up(f[i][j+1][k][1], f[i][j][k][1]);
          if (j+1 <= n && a[j+1] == a[i])
            up(f[i][j+1][k][2], f[i][j][k][1]);
          //2
          up(f[i][j][k+1][2], f[i][j][k][2]);
          if (k+1 <= n && a[k+1] == a[i])
            up(f[i][j][k+1][0], f[i][j][k][2]);
          
        }
      }
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        up(ans, f[n][j][k][0]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}