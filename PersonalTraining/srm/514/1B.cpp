/*
直接拿n*1或1*m或n*m的块去状压dp肯定是无法接受的
由于任意长度为n,m的条的权值之和奇偶性都相同，那么a[i][j]和a[i+p*n][j+q*m]肯定是奇偶性相同的
把所有a[i][j]归类到同一个等价类a[(H-1-i)%n][(W-1-j)%m]中去，判断是否存在冲突，以及等价类的奇偶性，?的个数
剩下的问题就是求一个n*m的矩阵行列和都为奇数的方案，预处理g[i][S]表示第i行放奇偶性为S的方案数，直接暴力转移
时间复杂度O(4^10*10)
*/
//#line 2 "MagicalGirlLevelTwoDivOne.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int mod=1000*1000*1000+7;
int cnt[55][55];
int dot[55][55];
int g[11][1<<11];
int f[11][1<<11];
int change(char x){
  return x=='.'?-1:((x-'0')%2);
}
void update(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
int pow_mod(int x,int y){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=(ll)t*x%mod;
    x=(ll)x*x%mod;
  }
  return t;
}
class MagicalGirlLevelTwoDivOne {
	public:  
	int theCount(vector <string> palette, int n, int m)  {  
		// $CARETPOSITION$  
    int H=SZ(palette);
    int W=SZ(palette[0]);
    memset(cnt,-1,sizeof(cnt));
    memset(dot,0,sizeof(dot));
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
        int x=change(palette[H-1-i][W-1-j]);
        if(x==-1)dot[i%n][j%m]++;
        else{
          if(cnt[i%n][j%m]==1-x)return 0;
          cnt[i%n][j%m]=x;
        }
      }
    }
    for(int i=0;i<n;i++){
      for(int S=0;S<1<<m;S++){
        g[i][S]=1;
        int bit=0;
        for(int j=0;j<m;j++){
          int x=S>>j&1;
          bit^=x;
          if(cnt[i][j]==1-x){
            g[i][S]=0;
            break;
          }
          g[i][S]=(ll)pow_mod(x?5:4,dot[i][j])*g[i][S]%mod;
        }
        if(bit==0)g[i][S]=0;
      }
    }
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<n;i++){
      for(int T=0;T<1<<m;T++)if(g[i][T]){
        for(int S=0;S<1<<m;S++)if(f[i][S]){
          update(f[i+1][S^T],(ll)f[i][S]*g[i][T]%mod);
        }
      }
    }
    return f[n][(1<<m)-1];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"12",
 "2."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 5; verify_case(0, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"21",
 "1."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 4; verify_case(1, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1953125; verify_case(2, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"..58..",
 "..47.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 0; verify_case(3, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"...1.2.3",
 "4.5.6...",
 "...7.8.9",
 "1.2.3..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 4; int Arg3 = 886073030; verify_case(4, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "....................",
 "...................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 10; int Arg3 = 240076532; verify_case(5, Arg3, theCount(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	MagicalGirlLevelTwoDivOne ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
