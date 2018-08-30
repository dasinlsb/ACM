//#line 2 "FizzBuzzTurbo.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
  
class FizzBuzzTurbo {
	public:  
	vector<long long> counts(long long A, long long B)  {  
		// $CARETPOSITION$  
    vector<ll>ans;
    ll x,y,z;
    z=B/15-(A-1)/15;
    x=B/3-(A-1)/3-z;
    y=B/5-(A-1)/5-z;
    ans.pb(x);ans.pb(y);ans.pb(z);
    return ans;
    
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 4LL; long Arr2[] = {1, 0, 0 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, counts(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 2LL; long long Arg1 = 6LL; long Arr2[] = {2, 1, 0 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, counts(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 150LL; long long Arg1 = 165LL; long Arr2[] = {4, 2, 2 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, counts(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 474747LL; long long Arg1 = 747474LL; long Arr2[] = {72728, 36363, 18182 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, counts(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	FizzBuzzTurbo ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
