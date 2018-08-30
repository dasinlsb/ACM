/*
由于上面的方块的放置取决于下面的方块，考虑最底层的方块
这一层的这些方块肯定是可以分成若干段连续区间，显然这些区间分别往上扩展的方案就是独立的子问题，可以dp解决
f[i][j]表示对于所有0<=h<=i，底层是一段长度为j的连续区间，这种情况下的方案数
背包预处理g[i]表示拼一段单层的长度为i的连续区间的方案数
考虑第i位，如果不放方块就是f[i][j-1]
如果放的话枚举一下往前连续一段延伸到j，那么可以得到转移
f[i][j]=f[i][j-1]+\sum_{1<=j<=i}f[i][j-2]*g[i-j+1]*f[h-1][i-j+1]
时间复杂度O(n^3)
*/
//#line 2 "BricksN.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=55;
const int mod=1000*1000*1000+7;
inline void up(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
int seg[maxN];
int f[maxN][maxN];
int solve(int W,int H,int K){
  memset(seg,0,sizeof(seg));
  seg[0]=1;
  for(int i=1;i<=W;i++){
    for(int j=1;j<=K&&j<=i;j++){
      up(seg[i],seg[i-j]);
    }
  }
  memset(f,0,sizeof(f));
  for(int i=0;i<=W;i++)f[0][i]=1;
  int ans=0;
  for(int h=1;h<=H;h++){
    f[h][0]=1;
    for(int i=1;i<=W;i++){
      f[h][i]=f[h][i-1];
      up(f[h][i],(ll)seg[i]*f[h-1][i]%mod);
      for(int j=2;j<=i;j++){
        up(f[h][i],(ll)f[h][j-2]*seg[i-j+1]%mod*f[h-1][i-j+1]%mod);
      }
    }
  }
  return f[H][W];
}
class BricksN {
	public:  
	int countStructures(int w, int h, int k)  {  
		// $CARETPOSITION$  
    return solve(w,h,k);
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; int Arg3 = 13; verify_case(0, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 3; int Arg3 = 83; verify_case(1, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 1; int Arg3 = 6; verify_case(2, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 3; int Arg3 = 288535435; verify_case(3, Arg3, countStructures(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	BricksN ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
