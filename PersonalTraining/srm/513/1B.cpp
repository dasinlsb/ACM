/*
可以用f[n][m]表示现在还剩n种值没有翻出2张，其中m种已经翻出一张
不过注意是一张一张翻的，分别讨论一下分别在m和2*(n-m)种哪一堆来转移即可
*/
//#line 2 "PerfectMemory.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=1300;
int vis[maxN][maxN];
double f[maxN][maxN];
double DP(int n,int m){
  //printf("%d %d\n",n,m);
  if(vis[n][m])return f[n][m];
  vis[n][m]=1;
  if(n==0)return f[n][m]=0.0;
  double res=0.0;
  if(m>=1)res+=1.0*m/(2*n-m)*DP(n-1,m-1);
  if((n-m)>=1){
    double p=2.0*(n-m)/(2*n-m);
    if(m>=1)res+=p*m/(2*n-m-1)*(DP(n-1,m)+1.0);
    res+=p*1/(2*n-m-1)*DP(n-1,m);
    if(2*(n-m-1)>=1)res+=p*(2*(n-m-1))/(2*n-m-1)*DP(n,m+2);
  }
  return f[n][m]=res+1.0;
}
class PerfectMemory {
	public:  
	double getExpectation(int N, int M)  {  
		// $CARETPOSITION$  
    int n=N*M/2;
    memset(vis,0,sizeof(vis));
    double ans=DP(n,0);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; double Arg2 = 1.0; verify_case(0, Arg2, getExpectation(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; double Arg2 = 2.6666666666666665; verify_case(1, Arg2, getExpectation(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; double Arg2 = 4.333333333333334; verify_case(2, Arg2, getExpectation(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 4; double Arg2 = 12.392984792984793; verify_case(3, Arg2, getExpectation(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	PerfectMemory ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
