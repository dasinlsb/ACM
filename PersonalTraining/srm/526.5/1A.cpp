/*
从1开始倒推不断还原序列，可以发现每个数的变化轨迹是恒定的，比如在某一轮有个7，那么在接下来的几轮的变化一定是7->5->3->2->1
反之最后要想成为1，那么这个数之前的取值一定在这个序列当中，发现这个序列是一个差不多等差数列的东西，增长很快，直接暴力算上去就行了
*/
#include<bits/stdc++.h>
using namespace std;  

class MagicCandy{
	public:
	int whichOne(int n){
		// $CARETPOSITION$
    int now=1;
    for(int i=1;;i++){
      now+=i;
      if(n<now)return now-i;
      now+=i;
      if(n<now)return now-i;
    }
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; verify_case(0, Arg1, whichOne(Arg0)); }
	void test_case_1() { int Arg0 = 9; int Arg1 = 7; verify_case(1, Arg1, whichOne(Arg0)); }
	void test_case_2() { int Arg0 = 20; int Arg1 = 17; verify_case(2, Arg1, whichOne(Arg0)); }
	void test_case_3() { int Arg0 = 5265; int Arg1 = 5257; verify_case(3, Arg1, whichOne(Arg0)); }
	void test_case_4() { int Arg0 = 20111223; int Arg1 = 20110741; verify_case(4, Arg1, whichOne(Arg0)); }
	void test_case_5() { int Arg0 = 1; int Arg1 = 1; verify_case(5, Arg1, whichOne(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	MagicCandy ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
