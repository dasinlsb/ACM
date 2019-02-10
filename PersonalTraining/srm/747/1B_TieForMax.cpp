#include <bits/stdc++.h>
using namespace std;
const int maxn = 52;
double f[maxn][maxn][maxn][2];
double c[maxn][maxn];
class TieForMax {
  public:
    double getProbability(int t, int p) {
      c[0][0] = 1;
      for (int i = 1; i < maxn; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
          c[i][j] = c[i - 1][j - 1] / p + c[i - 1][j];
        }
      }
      f[0][0][0][0] = 1;
      for (int pile = 0; pile < p; pile++) {
        for (int use = 0; use <= t; use++) {
          for (int mx = 0; mx <= use; mx++) {
            for (int two = 0; two < 2; two++) {
              for (int nxt = 0; use + nxt <= t; nxt++) {
                int _two = nxt < mx ? two : (nxt == mx);
                f[pile + 1][use + nxt][max(mx, nxt)][_two]
                  += c[use + nxt][nxt] * f[pile][use][mx][two];
              }
            }
          }
        }
      }
      double ans = 0;
      for (int i = 1; i <= t; i++) {
        ans += f[p][t][i][1];
      }
      return ans;
    }
};
int main() {
  freopen("aa.in", "r", stdin);
  TieForMax _dasin;
  auto res = _dasin.getProbability(
3,
3
  );
  cout << res << endl;
  return 0;
}