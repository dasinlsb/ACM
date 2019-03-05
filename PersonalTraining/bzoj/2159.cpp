/*
S(x) = \sum_{0<=i<=K}stiring2(K, i) * i! * \sum_{1<=j<=N}C(dist[x][j], i)
后面的组合数部分可以考虑C(n, m) = C(n - 1, m - 1) + C(n - 1, m)
dp[x][j]表示子树x内所有点的C(dist[x][], j)之和，可以直接按照上式转移
然后再dfs一遍求出每个点的答案即可
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 50005;
const int maxk = 155;
const int mod = 10007;
int n, kk, ed;
int fa[maxn], fir[maxn];
int S[maxk][maxk], fac[maxk], f[maxn][maxk], ans[maxn];
struct Edge{int v, nxt;} e[maxn * 2];
void adde(int x, int y) {
  e[++ed].v = y; 
  e[ed].nxt = fir[x];
  fir[x] = ed;
}
void add(int &x, int y) {
  if (x += y, x >= mod) x -= mod;
}
void sub(int &x, int y) {
  if (x -= y, x < 0) x += mod;
}
int mul(int x, int y) {
  return x * y % mod;
}
void dfs1(int x) {
  f[x][0] = 1;
  for (int i = fir[x]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[x]) continue;
    fa[v] = x;
    dfs1(v);
    for (int j = 0; j <= kk; j++) {
      add(f[x][j], f[v][j]);
      if (j) add(f[x][j], f[v][j - 1]);
    }
  }
}
void dfs2(int x) {
  for (int i = 0; i <= kk; i++) {
    // cerr << "f " << x << " " << i << " " << f[x][i] << endl;
    add(ans[x], mul(mul(S[kk][i], fac[i]), f[x][i]));
  }
  for (int i = fir[x]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa[x]) continue;
    for (int j = 0; j <= kk; j++) {
      sub(f[x][j], f[v][j]);
      if (j) sub(f[x][j], f[v][j - 1]);
    }
    for (int j = 0; j <= kk; j++) {
      add(f[v][j], f[x][j]);
      if (j) add(f[v][j], f[x][j - 1]);
    }
    dfs2(v);
    for (int j = 0; j <= kk; j++) {
      sub(f[v][j], f[x][j]);
      if (j) sub(f[v][j], f[x][j - 1]);
    }
    for (int j = 0; j <= kk; j++) {
      add(f[x][j], f[v][j]);
      if (j) add(f[x][j], f[v][j - 1]);
    }
  }
}
void Uncompress() { 
  int N, k, L, i, now, A, B, Q, tmp; 
  scanf("%d%d%d", &N, &k, &L); 
  ::n = N; ::kk = k;
  scanf("%d%d%d%d", &now, &A, &B, &Q); 
  for (i = 1; i < N; i ++) { 
    now = (now * A + B) % Q; tmp = (i < L) ? i : L; 
    int x = i - now % tmp;
    int y = i + 1;
    adde(x, y); adde(y, x);
  }
}
void read() {
  scanf("%d%d", &n, &kk);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    adde(x, y); adde(y, x);
  }
}
int main(){
  fac[0] = 1;
  for (int i = 1; i < maxk; i++) fac[i] = mul(fac[i - 1], i);
  S[0][0] = 1;
  for (int i = 1; i < maxk; i++) {
    for (int j = 1; j <= i; j++) {
      S[i][j] = (S[i - 1][j - 1] + mul(S[i - 1][j], j)) % mod;
    }
  }
  Uncompress();
  // read();
  dfs1(1);
  dfs2(1);
  for (int i = 1; i <= n; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}