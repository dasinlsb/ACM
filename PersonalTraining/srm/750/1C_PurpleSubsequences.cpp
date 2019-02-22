/*
是A的子序列，这个限制可以用一维i表示匹配到A[i]来记录
LIS长度>=L，由于L<=6，所以对于all i of [1..L-1]分别记录当前长度为i的LIS的最小结尾数字是[1..20]哪一个
状态数大概是60 * 20 ^ 5，由于后面的20 ^ 5的状态是单调的，可以预处理剪掉很多
*/
#include <bits/stdc++.h>
using namespace std;
const int maxN = 60;
const int maxV = 20;
const int maxL = 6;
int encode_status(vector<int> a, int L) {
  assert(a.size() == L - 1);
  int s = 0;
  for (int i = (int)a.size() - 1; i >= 0; i--) {
    s = s * (maxV + 1) + a[i];
  }
  return s;
}
vector<int> decode_status(int s, int L) {
  vector<int> a;
  for (int i = 0; i < L - 1; i++) {
    a.push_back(s % (maxV + 1));
    s /= (maxV + 1);
  }
  return a;
}
const int maxS = 55000;
int sid[420 * 10000];
int trans_s[maxS][maxV + 2], trans_i[maxN + 5][maxV + 2];
long long dp[maxN + 5][maxS];
void dfs(vector<int>& valid, int& L, int cur, bool is_last, int s) {
  static int a[maxL];
  if (cur == -1) {
    sid[s] = valid.size();
    valid.push_back(s);
    return;
  }
  for (int i = 0; i <= (is_last ? 20 : a[cur + 1]); i++) {
    a[cur] = i;
    dfs(valid, L, cur - 1, false, s * (maxV + 1) + i);
  }
}
class PurpleSubsequences {
  public:
    long long count(vector<int> A, int L) {
      int n = A.size();
      for (int i = 0; i < n; i++) A[i]--;
      int total_status = 1;
      for (int i = 0; i < L - 1; i++) total_status *= (maxV + 1);
      vector<int> valid;
      dfs(valid, L, L - 2, true, 0);
      // cerr << "total " << total_status << " " << valid.size() << endl;
      int full = valid.size();
      for (int cur = 0; cur < valid.size(); cur++) {
        int status = valid[cur];
        auto a = decode_status(status, L);
        // cerr << "init "; for (auto i : a) cerr << i << " "; cerr << endl;
        for (int nxt = 0; nxt < 20; nxt++) {
          if (L == 1 || nxt > a[L - 2]) {
            trans_s[cur][nxt] = full;
            continue;
          }
          auto b = a;
          for (int i = L - 2; i >= 0; i--) {
            if (!i || i && nxt > a[i - 1]) b[i] = min(b[i], nxt);
          }
          // cerr << "after "; for (auto i : b) cerr << i << " "; cerr << endl;
          int _status = encode_status(b, L);
          trans_s[cur][nxt] = sid[_status];
        }
      }
      for (int nxt = 0; nxt < 20; nxt++) {
        trans_s[full][nxt] = full;
      }
      for (int i = 0; i < n; i++) {
        for (int nxt = 0; nxt < 20; nxt++) {
          int j = i;
          for (; j < n && A[j] != nxt; j++);
          trans_i[i][nxt] = j + 1;
        }
      }
      // auto it = decode_status(valid[210], L);
      // for (auto x : it) cerr << x << " "; cerr << endl;
      int empty = sid[encode_status(vector<int>(L - 1, 20), L)];
      // cerr << "empty " << empty << endl;
      // for (int i = 0; i < 20; i++) {
      //   cerr << i << " " << trans_s[empty][i] << endl;
      // }
      memset(dp, 0, sizeof(dp));
      dp[0][empty] = 1;
      for (int i = 0; i < n; i++) {
        for (int status = 0; status <= valid.size(); status++) {
          for (int nxt = 0; nxt < 20; nxt++) {
            dp[trans_i[i][nxt]][trans_s[status][nxt]] += dp[i][status];
          }
        }
      }
      // cerr << "check " << dp[sid[encode_status({20, 20}, L)]][0] << endl;
      long long ans = 0;
      for (int i = 1; i <= n; i++) {
        ans += dp[i][full];
      }
      return ans;
    }
};

int main() {
  PurpleSubsequences res;
  auto _res = res.count(
    vector<int>(60, 1),
    6
  );
  cerr << _res << endl;
  return 0;
}