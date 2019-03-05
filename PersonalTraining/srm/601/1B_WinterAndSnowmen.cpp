#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005;
const int maxb = 11;
const int mod = 1e9 + 7;
class WinterAndSnowmen{
  public:
    int dp[2][1 << maxb][2][2];
    void add(int &x, int y) {
      if (x += y, x >= mod) x -= mod;
    }
    int getNumber(int N, int M) {
      int ans = 0;
      for (int p = 0; p < maxb; p++) {
        memset(dp[0], 0, (1 << maxb) * 2 * 2 * sizeof(int));
        dp[0][0][0][0] = 1;
        for (int i = 0; i < max(N, M); i++) {
          memset(dp[~i & 1], 0, (1 << maxb) * 2 * 2 * sizeof(int));
          for (int s = 0; s < 1 << maxb - p - 1; s++) {
            for (int x = 0; x < 2; x++) {
              for (int y = 0; y < 2; y++) {
                int v = (i + 1) >> p + 1;
                if (i + 1 <= N) add(dp[~i & 1][s ^ (i + 1 >> p + 1)][x ^ (i + 1 >> p & 1)][y], dp[i & 1][s][x][y]);
                if (i + 1 <= M) add(dp[~i & 1][s ^ (i + 1 >> p + 1)][x][y ^ (i + 1 >> p & 1)], dp[i & 1][s][x][y]);
                add(dp[~i & 1][s][x][y], dp[i & 1][s][x][y]);
              }
            }
          }
        }
        add(ans, dp[max(N, M) & 1][0][0][1]);
      }
      return ans;
    }
};

int main(){
  WinterAndSnowmen res;
  auto _res = res.getNumber(47, 74);
  cout << _res << endl;
  return 0;
}