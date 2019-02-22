/*
首先可能的答案不会超过n个，先预处理这可能的一组解空间，a[] += a[i]，i任取都可以
考虑如何判定一个数k是否可能被算出，肯定0,k同组，1,k-1一组，以此类推，如果把两组按0/1标号，就是问[0,k]和[0,k+m]是否是回文串
将a[]数组的空隙，根据空隙长度编号即可使串长维持在线性级别
*/
#include <bits/stdc++.h>
using namespace std;

template<typename T>
void cmin(T& x, T y) {if (y < x) x = y;}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  auto a2 = a;
  for (int i = 0; i < n; i++) {
    a2.push_back(a[i] + m);
  }
  vector<int> b;
  b.push_back(a2[0]);
  b.push_back(-5);
  for (int i = 1; i < a2.size(); i++) {
    b.push_back(a2[i] - a2[i - 1]);
    b.push_back(-5);
  }
  b.push_back(2 * m - 1 - a2.back());
  auto print = [](string pre, vector<int> a) {
    cerr << pre;
    for (auto x : a) cerr << x << " "; cerr << endl;
  };
  // print("b: ", b);
  auto manacher = [](vector<int> a) {
    vector<int> b;
    b.push_back(-2);
    for (int x : a) {
      b.push_back(x);
      b.push_back(-3);
    }
    b.back() = -4;
    vector<int> f(b.size());
    f[0] = 1;
    int p = 0, r = 1;
    for (int i = 1; i < b.size(); i++) {
      f[i] = (r > i ? min(r - i, f[p * 2 - i]) : 1);
      for (; b[i - f[i]] == b[i + f[i]]; f[i]++);
      if (r < i + f[i]) {
        r = i + f[i];
        p = i;
      }
    }
    vector<int> pre(b.size(), b.size());
    for (int i = 0; i < pre.size(); i++) {
      cmin(pre[i + f[i] - 1], i);
    }
    for (int i = (int)pre.size() - 2; i >= 0; i--) {
      cmin(pre[i], pre[i + 1]);
    }
    for (int i = 0; i < pre.size(); i++) {
      pre[i] = 2 * pre[i] - i;
    }
    return pre;
  };
  auto pre = manacher(b);
  auto check = [](vector<int>& A, vector<int>& pre, int p) {
    int _p = (int)(upper_bound(A.begin(), A.end(), p) - A.begin()) - 1;
    if (_p == -1) return true;
    // cerr << "pre " << _p << " " << pre[(_p * 2 + 1) * 2 + 1] << endl;
    return pre[(_p * 2 + 1) * 2 + 1] == 3 && p - A[_p] == A[0];
  };
  vector<int> ans;
  for (auto x : a) {
    x = (x + a[0]) % m;
    if (check(a2, pre, x) && check(a2, pre, x + m)) {
      ans.push_back(x);
    }
  }
  // cerr << "check: " << check(a2, pre, 2) << "\n" << check(a2, pre, 6) << endl;
  sort(ans.begin(), ans.end());
  printf("%d\n", static_cast<int>(ans.size()));
  for (int i = 0; i < ans.size(); i++) {
    printf("%d%c", ans[i], i == (int)ans.size() - 1 ? '\n' : ' ');
  }
  return 0;
}