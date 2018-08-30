/*
直接暴力n^3 dp
*/
//#line 2 "RedPaint.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=505;
double f[2][maxN][maxN];
class RedPaint {
	public:  
	double expectedCells(int N)  {  
		// $CARETPOSITION$  
    int i,j;
    for(i=1;i<=N;++i){
      for(j=1;j<=N;++j){
        f[0][i][j]=0;
      }
    }
    f[0][1][1]=1.0;
    for(int n=0;n<N;++n){
      for(int m=1;m<=n+2;++m){
        for(i=1;i<=m;++i){
          f[~n&1][i][m]=0;
        }
      }
      for(int m=1;m<=n+2;++m){
        for(i=1;i<=m;++i){
          double g=f[n&1][i][m]*0.5;
          if(i==1)f[~n&1][1][m+1]+=g;
          else f[~n&1][i-1][m]+=g;
          if(i==m)f[~n&1][m+1][m+1]+=g; 
          else f[~n&1][i+1][m]+=g;
        }
      }
    }
    double ans=0;
    for(int m=1;m<=N+1;++m){
      for(i=1;i<=m;++i){
        ans+=m*f[N&1][i][m];
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 0; double Arg1 = 1.0; verify_case(0, Arg1, expectedCells(Arg0)); }
	void test_case_1() { int Arg0 = 1; double Arg1 = 2.0; verify_case(1, Arg1, expectedCells(Arg0)); }
	void test_case_2() { int Arg0 = 2; double Arg1 = 2.5; verify_case(2, Arg1, expectedCells(Arg0)); }
	void test_case_3() { int Arg0 = 4; double Arg1 = 3.375; verify_case(3, Arg1, expectedCells(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	RedPaint ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
