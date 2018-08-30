//#line 2 "AnEasyProblem.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int inf=10000*10000;
class AnEasyProblem {
	public:  
	int solve(long long sum)  {  
		// $CARETPOSITION$  
    int h=1;
    for(;(ll)h*h<sum;h++);
    int r=1;
    ll nowsum=(ll)h*h;
    int ans=inf;
    for(;(ll)h*(1+h)/2<=sum;nowsum+=h+h+1,h++){
      for(;r<h&&nowsum>sum;r++)nowsum-=r;
      if(nowsum==sum)ans=min(ans,h+h-r);
    }
    return ans==inf?-1:ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 6LL; int Arg1 = 3; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { long long Arg0 = 7LL; int Arg1 = -1; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { long long Arg0 = 100LL; int Arg1 = 15; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { long long Arg0 = 1000000000000LL; int Arg1 = 1428571; verify_case(3, Arg1, solve(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AnEasyProblem ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
