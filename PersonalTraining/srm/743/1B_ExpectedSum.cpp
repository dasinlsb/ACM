#include <bits/stdc++.h>
using namespace std;
const int maxn = 51;
double f[2][maxn * maxn][maxn * maxn];
class ExpectedSum {
  public:
    double solve(vector<int> seq, vector<int> probMinus) {
      int n = seq.size();
      memset(f, 0, sizeof f);
      f[0][0][0] = 1.0;
      double ans = 0.0;
      for (int i = 0; i <= n; i++) {
        int offset = 50 * i;
        int _offset = 50 * (i + 1);
        for (int hist = 0; hist <= _offset; hist++) {
          for (int last = 0; last <= _offset; last++) {
            f[~i & 1][hist][last] = 0.0;
          }
        }
        int _last;
        for (int hist = 0; hist <= offset; hist++) {
          for (int last = 0; last <= offset; last++) {
            if (i == n) {
              ans += f[i & 1][hist][last] * hist;
              continue;
            }
            _last = last + seq[i];
            f[~i & 1][max(hist, _last)][_last] += (1.0 - 0.01 * probMinus[i]) * f[i & 1][hist][last];
            _last = max(last - seq[i], 0);
            f[~i & 1][max(hist, _last)][_last] += 0.01 * probMinus[i] * f[i & 1][hist][last];
          }
        }
      }
      return ans;
    }
};
int main() {
  ExpectedSum res;
  auto _res = res.solve({10, 20, 30}, {0, 0, 0});
  cout << _res << endl;
  return 0;
}