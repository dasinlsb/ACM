#include <bits/stdc++.h>
using namespace std;
int mod;
void add(int&x, int y) {
  if (x += y, x >= mod) x -= mod;
}
int dfs(vector<int>& perm, vector<pair<int, int> >& comp, int k) {
  if (k == comp.size()) return 1;
  int x = comp[k].first;
  int y = comp[k].second;
  if (perm[x] > perm[y]) return 0;
  swap(perm[x], perm[y]);
  int res = dfs(perm, comp, k + 1);
  swap(perm[x], perm[y]);
  add(res, dfs(perm, comp, k + 1));
  return res;
}
int main() {
  // freopen("aa.in", "r", stdin);
  int _;
  scanf("%d", &_);
  for (; _--;) {
    int n, k;
    scanf("%d%d%d", &n, &k, &mod);
    vector<pair<int, int> > comp;
    for (int i = 0; i < k; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      x--; y--;
      comp.push_back(make_pair(x, y));
    }
    reverse(comp.begin(), comp.end());
    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i;
    int ans = dfs(perm, comp, 0);
    auto print = [](vector<int> a) {
      for (int x : a) cerr << x << " "; cerr << endl;
    };
    for (int i = 0; i < n; i++) {
      for (int j = i - 1; j >= 0; j--) {
        swap(perm[j], perm[j + 1]);
        add(ans, dfs(perm, comp, 0));
      }
      for (int j = 0; j < i; j++) {
        swap(perm[j], perm[j + 1]);
      }
      for (int j = i + 1; j < n; j++) {
        swap(perm[j - 1], perm[j]);
        if (j > i + 1) add(ans, dfs(perm, comp, 0));
      }
      for (int j = n - 1; j > i; j--) {
        swap(perm[j], perm[j - 1]);
      }
    }
    
    printf("%d\n", ans);
  }
  return 0;
}