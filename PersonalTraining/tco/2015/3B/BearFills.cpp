/*
枚举要用的最大的正方形是哪个递归成子问题，加一个剪枝，剩下的正方形边长总和如果小于max(A,B)就直接返回0，这个剪枝实际上比面积剪枝要强的多，可以通过本题
*/
#include<bits/stdc++.h>
using namespace std;  
const long long inf=1e18;
long double pw2[125];
long long dfs(int N,long long A,long long B){
  if(A>B)swap(A,B);
  if((1LL<<N)-1<B)return 0;
  long long result=0;
  for(int i=N-1;i>=0;i--){
    if((1LL<<i)>=B){
      result+=1LL<<i;
    }
    else if((1LL<<i)>=A){
      result+=dfs(i,A,B-(1LL<<i));
    }
    else break;
  }
  return result;
}
class BearFills{
	public:
	long long countSets(int N, long long W, long long H){
		// $CARETPOSITION$
    pw2[0]=1.0;
    for(int i=1;i<125;i++)pw2[i]=pw2[i-1]*2.0;
    return dfs(N,W,H);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; long long Arg1 = 1LL; long long Arg2 = 3LL; long long Arg3 = 5LL; verify_case(0, Arg3, countSets(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; long long Arg1 = 3LL; long long Arg2 = 5LL; long long Arg3 = 1LL; verify_case(1, Arg3, countSets(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 60; long long Arg1 = 3LL; long long Arg2 = 2LL; long long Arg3 = 1152921504606846972LL; verify_case(2, Arg3, countSets(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; long long Arg1 = 5LL; long long Arg2 = 4LL; long long Arg3 = 56LL; verify_case(3, Arg3, countSets(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	BearFills ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
