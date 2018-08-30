/*
直接枚举正方形的具体位置感觉十分困难，因为可能存在正方形的某些边不经过任何给出的点的情况
考虑任意合法的正方形的摆放，肯定内部框住一些点的形式
那么肯定也可以用一个在正方形内部的[极大的]矩形去框这些点
矩形可以O(n^4)去枚举，接下来的问题就是判断矩形是否极大
如果现在枚举出了某个矩形，那么它的四条边肯定是可以上下左右浮动的
我们可以将每个矩形的边浮动的边界规定为x,y坐标相邻项
如果这个矩形从当前状态扩大到恰好不碰到边界整个过程中，存在一个合法正方形包裹住它，那么就是这个点集就是合法的
时间复杂度O(n^5)
*/
//#line 2 "RangeSquaredSubsets.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

class RangeSquaredSubsets {
	public:  
	long long countSubsets(int nlow, int nhigh, vector <int> x, vector <int> y)  {  
		// $CARETPOSITION$  
    int n=SZ(x);
    vector<int>vx,vy;
    for(int i=0;i<n;i++){
      vx.pb(x[i]);
      vy.pb(y[i]);
    }
    sort(vx.begin(),vx.end());    
    sort(vy.begin(),vy.end());
    set<ll>set_v;
    for(int xl=0;xl<n;xl++)for(int xr=xl;xr<n;xr++){
      for(int yl=0;yl<n;yl++)for(int yr=yl;yr<n;yr++){
        int d=max(vx[xr]-vx[xl],vy[yr]-vy[yl]);
        if(d>nhigh)continue;
        d=max(d,nlow);
        if(xl>0&&xr<n-1&&vx[xr+1]-vx[xl-1]<=d)continue;
        if(yl>0&&yr<n-1&&vy[yr+1]-vy[yl-1]<=d)continue;
        ll res=0;
        for(int i=0;i<n;i++){
          if(vx[xl]<=x[i]&&x[i]<=vx[xr]&&vy[yl]<=y[i]&&y[i]<=vy[yr]){
            res|=1LL<<i;
          }
        }
        if(res){
          set_v.insert(res);
        }
      }
    }
    // for(auto it:set_v){
    //   printf("set %lld\n",it);
    // }
    return SZ(set_v);
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; int Arr2[] = {-5,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 5LL; verify_case(0, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 10; int Arr2[] = {-5,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 5LL; verify_case(1, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 100; int Arr2[] = {-5,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 6LL; verify_case(2, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 100000000; int Arr2[] = {-1,-1,-1,0,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-1,0,1,1,-1,0,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 21LL; verify_case(3, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 64; int Arg1 = 108; int Arr2[] = {-56,-234,12,324,-12,53,0,234,1,12,72}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {6,34,2,235,234,234,342,324,234,234,234}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 26LL; verify_case(4, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	RangeSquaredSubsets ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
