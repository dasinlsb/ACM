/*
由于每一列最多只能当一个竖着的，可以考虑从左到右dp
但是如果要记录右边界的所有情况肯定是无法接受的，但是可以取其中某些肯定会出现的情况当作状态
由于W,H>=2，有边界要么是整个竖直的，要么是有一段长为H的凸出，也就是有连续的H行已经放到第i列，而其他行已放的列数相等，且都小于i
凸出的H行不一定是放竖直的板，也可能是放H条横着的板,O(n^2)的状态，O(1)转移
*/
//#line 2 "PlankTiling.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=1005;
const int mod=1000*1000*1000+7;
int f[maxN][maxN];
inline void add(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
class PlankTiling {
	public:  
	int sumup(int H, int W)  {  
		// $CARETPOSITION$  
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<W;i++){
      for(int j=0;j<=i;j++)if(f[i][j]){
        if(i==j){
          add(f[i+1][i],(ll)H*f[i][j]%mod);
          if(i+H<=W)add(f[i+H][i+H],f[i][j]);        
        }else{
          add(f[i+1][i-j+1==H?i+1:j],f[i][j]);
          if(i+H<=W)add(f[i+H][j+H],f[i][j]);
        }
      }
    }
    return f[W][W];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 4; int Arg2 = 11; verify_case(0, Arg2, sumup(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 4; int Arg2 = 5; verify_case(1, Arg2, sumup(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 9; int Arg2 = 121; verify_case(2, Arg2, sumup(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 29; int Arg1 = 841; int Arg2 = 193514715; verify_case(3, Arg2, sumup(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	PlankTiling ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
