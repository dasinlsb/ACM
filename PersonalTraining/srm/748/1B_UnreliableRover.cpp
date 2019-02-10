/*
如果把每个?看作向四个方向分别分裂出四个相同的图形，这个过程形成的图形十分难以维护
如果暴力4^|?|枚举每个?的具体方向，那最终结果是矩形，很方便维护，但是时间复杂度无法接受
首先把所有?都放在操作序列的最后，这样显然不影响结果
这样之前的非?可以生成一个A*B的初始矩形
接下来考虑每个?所有可能的取值，假设向上向右向下向左分别有a[0..3]个，那么最终也会形成一个矩形，而且这个矩形是在初始矩形的基础上向四个方向分别扩展a[0..3]形成的
最终的矩形显然是关于竖直和水平中心轴对称的
考虑求出其中某个角，比如右上角的图形，这只要O(2^|?|)的时间复杂度，即枚举每个?变成向上还是向右即可
*/
#include <bits/stdc++.h>
using namespace std;
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};
struct Point {
  int x, y;
  Point() {x = y = 0;}
  Point(int _x, int _y): x(_x), y(_y) {}
  Point operator - (Point t) {return Point(x - t.x, y - t.y);}
  void move(int dir, int step) {
    x += DX[dir] * step;
    y += DY[dir] * step;
  }
  void print() {
    printf("[%d, %d]\n", x, y);
  }
};
struct Rectangle {
  Point dl, ur;
  void move(int dir, int mins, int maxs) {
    if (dir == 2 || dir == 3) {
      dl.move(dir, maxs);
      ur.move(dir, mins);
    } else {
      dl.move(dir, mins);
      ur.move(dir, maxs);
    }
  }
  void print() {
    printf("Rec\n");
    ur.print();
    dl.print();
  }
};
int getDir(char c) {
  if (c == 'N') return 0;
  if (c == 'E') return 1;
  if (c == 'S') return 2;
  if (c == 'W') return 3;
  return -1;
}
class UnreliableRover{
  public:
    long long getArea(string direction, vector<int> minSteps, vector<int> maxSteps) {
      Rectangle init;
      vector<int> can;
      for (int i = 0; i < direction.size(); i++) {
        int c = getDir(direction[i]);
        if (c == -1) {
          can.push_back(maxSteps[i]);
        } else {
          init.move(c, minSteps[i], maxSteps[i]);
        }
      }
      // init.print();
      init.ur.x = init.ur.x - init.dl.x + 1;
      init.ur.y = init.ur.y - init.dl.y + 1;
      vector<pair<int, int> > part;
      for (int status = 0; status < 1 << can.size(); status++) {
        int sum[2] = {0, 0};
        for (int i = 0; i < can.size(); i++) {
          sum[status >> i & 1] += can[i];
        }
        part.push_back(make_pair(sum[0], sum[1]));
      }
      sort(part.begin(), part.end());
      // for (auto it : part) printf("part %d %d\n", it.first, it.second);
      assert(part[0].first == 0);
      assert(part.back().second == 0);
      long long areaUR = 0;
      for (int i = 1; i < part.size(); i++) {
        areaUR += 1LL * part[i].second 
                * (part[i].first - part[i - 1].first);
      }
      long long areaU = 1LL * init.ur.x * part[0].second;
      long long areaR = 1LL * init.ur.y * part.back().first;
      long long areaM = 1LL * init.ur.x * init.ur.y;
      // printf("area %lld %lld %lld %lld\n", areaU, areaR, areaM, areaUR);
      return areaM + 2LL * (areaU + areaR) + 4LL * areaUR;
    }
};

int main() {
  // freopen("aa.in", "r", stdin);
  UnreliableRover _dasin;
  auto res = _dasin.getArea(
"?",
{0},
{10}
);
  cout << res << endl;
  return 0;
}