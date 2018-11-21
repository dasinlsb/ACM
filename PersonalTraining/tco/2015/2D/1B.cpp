/*
等价于确定一段长度为k的区间的第一位
也就是，问题可以转化为在[1,N-K+1]这个区间内，每次选一个点i，可能发生两种情况
(不失一般性，不妨假设当前区间为[1,m])
一种情况是这个点是空的，问题转化为[1,i-k]+[i+1,m]
另一种情况是这个点非空，问题转化为[max(i-k+1,1),i],此时的最优策略显然是用二分查找来优化暴力
第一种情况比较显然是每次取i==m最优，也就是每次可以使可能的区间长度减少k
虽然每一步进行之后都有可能出现上述两种情况
但是最坏情况显然第二种情况在最后出现
*/
#include<bits/stdc++.h>
using namespace std;  

class BallsInBoxes{
	public:
	long long maxTurns(long long N, long long K){
		// $CARETPOSITION$
    long long ans=0;
    N=N-K+1;
    if(N>2*K){
      long long d=(N-2*K-1)/K+1;
      ans+=d;
      N-=d*K;
    }
    for(;N>1;){
      ans++;
      N=(N+1)/2;
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 10LL; long long Arg1 = 10LL; long long Arg2 = 0LL; verify_case(0, Arg2, maxTurns(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 100LL; long long Arg1 = 1LL; long long Arg2 = 99LL; verify_case(1, Arg2, maxTurns(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 1000LL; long long Arg1 = 999LL; long long Arg2 = 1LL; verify_case(2, Arg2, maxTurns(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 10LL; long long Arg1 = 5LL; long long Arg2 = 3LL; verify_case(3, Arg2, maxTurns(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	BallsInBoxes ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
