/*
把合法当作1，非法当作0，那么原序列肯定是一段黑一段白这样
那么黑和白的段数各占一半左右，也就是22-23,这个范围是可以状压的
直接暴力枚举黑区间的选取情况检验
时间复杂度O(2^(n/2)*n/2)
*/
//#line 2 "ZooExchangeProgram.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
ll seg[25];
class ZooExchangeProgram {
	public:  
	int getNumber(vector <int> label, int lower, int upper)  {  
		// $CARETPOSITION$  
    int n=SZ(label);
    int pl,pr;
    int seg_n=0;
    for(pl=0;pl<n&&(label[pl]<lower||label[pl]>upper);pl++);
    for(;pl<n;){
      seg[seg_n]=0;
      for(pr=pl;pr<n&&label[pr]>=lower&&label[pr]<=upper;pr++){
        seg[seg_n]|=1LL<<label[pr];
      }
      seg_n++;
      for(pl=pr;pl<n&&(label[pl]<lower||label[pl]>upper);pl++);
    }
    int ans=100;
    ll goal=(1LL<<upper+1)-(1LL<<lower);
    for(int nowS=0;nowS<1<<seg_n;nowS++){
      ll vis=0;
      int cnt=0;
      for(int i=0;i<seg_n;i++)if(1<<i&nowS){
        vis|=seg[i];cnt++;
      }
      if(vis==goal)ans=min(ans,cnt);
    }
    return ans==100?-1:ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 1, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {3, 4, 1, 3, 4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; int Arg3 = 2; verify_case(1, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {3, 4, 3, 1, 6, 2, 5, 7, 5, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 6; int Arg3 = 2; verify_case(2, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {3, 1, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; int Arg3 = -1; verify_case(3, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {2, 1, 3, 1, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; int Arg3 = 1; verify_case(4, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {7, 12, 2, 12, 10, 13, 6, 5, 3, 3, 4, 11, 12, 4, 3, 1, 8, 11, 4, 7, 6, 5, 47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 7; int Arg3 = 3; verify_case(5, Arg3, getNumber(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	ZooExchangeProgram ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
