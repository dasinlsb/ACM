/*
显然任一时刻最上方最多有3层不满，手动列一下发现本质不同的只有9种状态
麻烦的是直接列出每种状态的转移是针对块而不是层，要想矩阵快速幂乘上去还要再按每层的转移化简一下
学习了一下官方题解上贴出来的rng_58的写法
由于每次增加一块最多只会使完整的层数+1，于是可以用[0,9),[9,18]一共18个的初始状态，这些状态之间的转移是很好写的
跑一遍dp可以得到[0,9)->[9,18)之间的转移系数，将这个映射到一个9*9的转移矩阵，直接拿这个矩阵跑就行了
*/
//#line 2 "Chimney.cpp"  
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
int mul(int a[18][18],int b[18][18],int n){
  static int c[18][18];
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      c[i][j]=0;
      for(int k=0;k<n;k++){
        c[i][j]=(c[i][j]+(ll)a[i][k]*b[k][j])%mod;
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      a[i][j]=c[i][j];
    }
  }
}
int g[18][18];
int h[18][18];
int f[18][18];
class Chimney {
	public:  
	int countWays(long long n)  {  
		// $CARETPOSITION$  
    memset(g,0,sizeof(g));
    g[0][1]=4;
    g[1][2]=g[2][5]=g[3][5]=g[4][6]=g[5][6]=2;
    g[1][3]=g[2][4]=g[5][9]=g[6][7]=g[6][10]=g[7][8]=g[7][11]=g[8][13]=1;
    memset(h,0,sizeof(h));
    for(int i=0;i<18;i++){
      h[i][i]=1;
      for(int j=i+1;j<18;j++){
        for(int k=i;k<j;k++){
          h[i][j]=(h[i][j]+(ll)h[i][k]*g[k][j])%mod;
        }
      }
    }
    memset(g,0,sizeof(g));
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        g[i][j]=h[i][j+9];
        //if(g[i][j])printf("g %d %d : %d\n",i,j,g[i][j]);
      }
    }
    memset(f,0,sizeof(f));
    for(int i=0;i<9;i++)f[i][i]=1;
    for(;n;n>>=1){
      if(n&1LL){
        mul(f,g,9);
      }
      mul(g,g,9);
    }
    return f[0][0];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; int Arg1 = 24; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { long long Arg0 = 2LL; int Arg1 = 1088; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { long long Arg0 = 5LL; int Arg1 = 110198784; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { long long Arg0 = 6LL; int Arg1 = 138284509; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { long long Arg0 = 100000LL; int Arg1 = 19900327; verify_case(4, Arg1, countWays(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	Chimney ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
