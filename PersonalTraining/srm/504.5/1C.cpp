/*
f[n][m]对于同一个n，将所有m对应的f[n][m]用f[n][1]表示
*/
//#line 2 "TheTicketsDivOne.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
#define MP make_pair
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=1005;
double f[maxN][maxN];
class TheTicketsDivOne  
{
  public:  
  double find(int n, int m){  
    //$CARETPOSITION$
    int i,j;
    f[1][1]=1;
    for(i=2;i<=n;++i){
      double x=1,y=0;
      for(j=2;j<=i;++j){
        x=x/2;
        y=y/2+f[i-1][j-1]/3;
      }
      f[i][1]=(y+1.0/3)/(2-x);
      for(j=2;j<=i;++j){
        f[i][j]=f[i][j-1]/2+f[i-1][j-1]/3;
      }
    }
    return f[n][m];
  }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; double Arg2 = 0.4444444444444444; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; double Arg2 = 0.5555555555555556; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; double Arg2 = 1.0; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 2; double Arg2 = 0.31746031746031744; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        TheTicketsDivOne ___test;  
        ___test.run_test(-1);  
        return 0;  
}  
// END CUT HERE  
