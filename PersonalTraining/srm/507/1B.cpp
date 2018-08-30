/*
枚举最终的大长方体的较短两边长，仔细算一下复杂度发现似乎是差不多对的(?)
枚举两边之后优先放边长为L的方块，剩下的贪心的铺边长为1的方块
*/
//#line 2 "CubePacking.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

class CubePacking {
	public:  
	int getMinimumVolume(int Ns, int Nb, int L)  {  
		// $CARETPOSITION$  
    int top=Nb*L*L*L+Ns+L*L;
    int ans=top;
    for(ll i=L;i*i*i<=top;++i){
      for(ll j=i;j*j*i<=top;++j){
        ll s=(i/L)*(j/L);
        ll k=(Nb/s+(Nb%s!=0))*L;
        if(!k)continue;
        ll res=i*j*k;
        ll empty=res-Nb*L*L*L;
        if(Ns>empty)res+=((Ns-empty)/(i*j)+((Ns-empty)%(i*j)!=0))*(i*j);
        //if(res==12)printf(" chk %d %d %d ",i,j,k);
        if(res<ans)ans=res;
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 20; verify_case(0, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 19; int Arg1 = 1; int Arg2 = 2; int Arg3 = 27; verify_case(1, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 51; int Arg1 = 7; int Arg2 = 5; int Arg3 = 950; verify_case(2, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 12345; int Arg1 = 987; int Arg2 = 10; int Arg3 = 999400; verify_case(3, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	CubePacking ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
