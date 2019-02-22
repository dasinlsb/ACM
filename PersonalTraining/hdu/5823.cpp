#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 18;
using val_t = unsigned int;
int n;
val_t pw[maxn], f[2][maxn];
bool vis[maxn];

void fwt(val_t* a, int t) {
  if (t == 1) {
    for (int d = 1; d < 1 << n; d <<= 1) {
      for (int i = 0; i < 1 << n; i += d + d) {
        for (int j = 0; j < d ; j++) {
          auto &x = a[i + j], &y = a[i + j + d];
          a[i + j + d] = x + y;
        }
      }
    }
  } else {
    for (int d = 1; d < 1 << n; d <<= 1) {
      for (int i = 0; i < 1 << n; i += d + d) {
        for (int j = 0; j < d ; j++) {
          auto &x = a[i + j], &y = a[i + j + d];
          a[i + j + d] = y - x;
        }
      }
    }
  }
}
val_t update(val_t c, val_t* f) {
  val_t res = 0;
  for (int s = 1; s < 1 << n; s++) {
    if (!vis[s] && f[s]) {
      vis[s] = 1;
      res += c * pw[s];
    }
  }
  return res;
}
int main(){
  pw[0] = 1;
  for (int i = 1; i < maxn; i++) 
    pw[i] = (val_t)233 * pw[i - 1];
  int _; cin >> _;
  for (; _--;) {
    cin >> n;
    fill(vis, vis + (1 << n), false);
    fill(f[0], f[0] + (1 << n), 0);
    vector<string> G(n);
    for (int i = 0; i < n; i++) {
      cin >> G[i];
    }
    f[0][0] = 1;
    for (int s = 1; s < 1 << n; s++) {
      int i;
      for (i = 0; i < n && (~s >> i & 1); i++);
      if (!f[0][s ^ 1 << i]) continue;
      f[0][s] = 1;
      for (int j = 0; j < n; j++) {
        if ((s >> j & 1) && G[i][j] == '1') {
          f[0][s] = 0; break;
        }
      }
    }
    val_t ans = 0;
    ans += update(1, f[0]);
    memcpy(f[1], f[0], (1 << n) * sizeof(val_t));
    fwt(f[0], 1);
    for (int c = 2; c <= n; c++) {
      fwt(f[1], 1);
      for (int s = 0; s < 1 << n; s++) f[1][s] *= f[0][s];
      fwt(f[1], -1);
      // for (int s = 0; s < 1 << n; s++) {
      //   cerr << s << " " << f[1][s] << endl;
      // }
      for (int s = 0; s < 1 << n; s++) f[1][s] = f[1][s] > 0;
      ans += update(c, f[1]);
    }
    cout << ans << endl;
  }
  return 0;
}