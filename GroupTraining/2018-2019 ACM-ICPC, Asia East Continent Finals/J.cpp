/*
假设可以预处理出一个矩阵a[][],其中a[i][j]表示第i个后缀和第j个后缀的LCP，那么相当于求一个概率分布p，使得p和行的点积的最小值最大
先把所有后缀按照字典序重排，那么除了主对角线，其他位置a[i][j]的值就是min{height[(i+1)..(j)]}
考虑整个矩阵的最小值h[i]所在的(i,i),显然右上部分和左下部分的所有位置的值都是h[i]
若只考虑上半部分，概率分布p在大于等于i处的取值差异对答案没有影响，也就是只要考虑[1..(i-1)]这个子矩阵对应的[1..(i-1)]的概率分布就行了，下半部分同理
考虑如何合并，假设左上矩形分配权重p,那么右下矩形就会分配到1-p，这样的话目标就是在[0,1]上取一个点使得两个一次函数的最小值尽可能大,要么在端点要么在内部交点(如果有的话)取到最优，分类讨论即可
*/
#include <bits/stdc++.h>
using namespace std;
using namespace placeholders;
const int maxn = 200005;
const int maxk = 18;
char s[maxn];
int n;
int sa[maxn], rk[maxn], h[maxn];
void SA(char* s, int n, int m) {
  static int tmp[maxn], cnt[maxn];
  int i, j, k;
  fill(cnt, cnt + max(n, m), 0);
  for (i = 0; i < n; i++) cnt[rk[i] = s[i]]++;
  for (i = 1; i < m; i++) cnt[i] += cnt[i - 1];
  for (i = 0; i < n; i++) sa[--cnt[s[i]]] = i;
  for (k = 1; k <= n; k <<= 1) {
    for (i = 0; i < n; i++) {
      j = sa[i] - k;
      if (j < 0) j += n;
      tmp[cnt[rk[j]]++] = j;
    }
    sa[tmp[cnt[0] = 0]] = j = 0;
    for (i = 1; i < n; i++) {
      if (rk[tmp[i]] != rk[tmp[i - 1]]
        ||rk[tmp[i] + k] != rk[tmp[i - 1] + k])
        cnt[++j] = i;
      sa[tmp[i]] = j;
    }
    for (i = 0; i < n; i++) {
      rk[i] = sa[i], sa[i] = tmp[i];
    }
    if (j >= n - 1) break;
  }
  fill(h, h + n, 0);
  for (i = k = 0; i < n; i++) {
    if (k) k--;
    for (j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
    h[rk[i]] = k;
  }
}
int LOG[maxn];
pair<int, int> info[maxk][maxn];
pair<int, int> ask(int l, int r) {
  int d = LOG[r - l + 1];
  return min(info[d][l], info[d][r - (1 << d) + 1]);
}
const double eps = 1e-10;
double calc(pair<double, double>& f1, pair<double, double>& f2, double& x) {
  return min(f1.first * x + f1.second, f2.first * x + f2.second);
}
double solve(int l, int r) {
  if (l == r) {
    return 1.0 * (n - sa[l]);
  }
  auto sep = ask(l + 1, r);
  int mid = sep.second - 1;
  // printf("solve %d %d %d\n", l, r, mid);
  double u = solve(l, mid),
          d = solve(mid + 1, r),
          o = sep.first;
  auto fu = make_pair(u - o, o),
        fd = make_pair(o - d, d);
  auto _calc = [&](double k) {
    return make_pair(calc(fu, fd, k), k);
  };
  auto res = max(_calc(0.0), _calc(1.0));
  double fenmu = u - o - o + d;
  if (fabs(fenmu) > eps){
    double _p = (d - o) / fenmu;
    if (_p > 0 && _p < 1.0) res = max(res, _calc(_p));
  }
  // cout << "fin " << l << " " << r << " " << p << " " << _calc(p) << endl;
  return res.first;
}
int main() {
  freopen("aa.in", "r", stdin); 
  // clock_t _st = clock();
  for (int i = 2; i < maxn; i++) {
    LOG[i] = LOG[i >> 1] + 1;
  }
  int _;
  scanf("%d", &_);
  for (; _--;) {
    scanf("%s", s);
    n = strlen(s);
    for (int i = 0; i < n; i++) s[i] = s[i] - 'a' + 1;
    SA(s, n + 1, 30);
    for (int i = 2; i <= n; i++) info[0][i] = make_pair(h[i], i);
    for (int j = 1; j < maxk; j++) {
      for (int i = 2; i + (1 << j) - 1 <= n; i++) {
        info[j][i] = min(info[j - 1][i], info[j - 1][i + (1 << j - 1)]);
      }
    }
    double ans = solve(1, n);
    printf("%.12lf\n", ans);
  }
  // clock_t _ed = clock();
  // cerr << "time: " << 1.0 * (_ed - _st) / CLOCKS_PER_SEC << endl;
  return 0;
}