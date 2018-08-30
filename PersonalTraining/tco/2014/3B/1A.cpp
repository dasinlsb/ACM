/*
每个人可能在turns中的某一轮的死亡，也可能一直没死，一共有turns+1种状态，k个人一共有(turns+1)^k种可能
不过最优做法要一开始先拿走一瓶
*/
//#line 2 "IntoTheMatrix.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

class IntoTheMatrix {
	public:  
	int takePills(int turns, int N)  {  
		// $CARETPOSITION$  
    N--;
    int ans=0;
    for(;N;N/=turns+1)++ans;
    return ans;

	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 0; verify_case(0, Arg2, takePills(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 3; verify_case(1, Arg2, takePills(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 1000; int Arg2 = 7; verify_case(2, Arg2, takePills(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 2; int Arg2 = 1; verify_case(3, Arg2, takePills(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 4; int Arg1 = 50; int Arg2 = 3; verify_case(4, Arg2, takePills(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	IntoTheMatrix ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
