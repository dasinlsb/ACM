//#line 2 "SpamChecker.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
  
class SpamChecker {
	public:  
	string spamCheck(string judgeLog, int good, int bad)  {  
		// $CARETPOSITION$  
    int i,j;
    int ans=0;
    for(i=0;i<SZ(judgeLog);++i){
      if(judgeLog[i]=='o')ans+=good;
      else ans-=bad;
      if(ans<0)return "SPAM";
    }
    return "NOT SPAM";
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ooooxxxo"; int Arg1 = 2; int Arg2 = 3; string Arg3 = "SPAM"; verify_case(0, Arg3, spamCheck(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "ooooxxxo"; int Arg1 = 3; int Arg2 = 4; string Arg3 = "NOT SPAM"; verify_case(1, Arg3, spamCheck(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "xooooooooooooooooooooooooooo"; int Arg1 = 1000; int Arg2 = 1; string Arg3 = "SPAM"; verify_case(2, Arg3, spamCheck(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "oxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; int Arg1 = 1000; int Arg2 = 1; string Arg3 = "NOT SPAM"; verify_case(3, Arg3, spamCheck(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "ooxoxoxooxoxxoxoxooxoxoxoxxoxx"; int Arg1 = 15; int Arg2 = 17; string Arg3 = "SPAM"; verify_case(4, Arg3, spamCheck(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "oooxoxoxoxoxoxooxooxoxooxo"; int Arg1 = 16; int Arg2 = 18; string Arg3 = "NOT SPAM"; verify_case(5, Arg3, spamCheck(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	SpamChecker ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
