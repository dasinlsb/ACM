/*
枚举r对所有x%M==r的x的合法性计数
相当于给出r,M+r,2M+r...kM+r,这样的序列，但是序列长度，即k，可能很大，考虑将k对mod r的余数再将这个序列分割
枚举所有0<=i<r，判断所有(i+kr)M+r的合法性，等价于对f((i+kr)M+r)判断合法性
展开后就是iM/r+kM+1，这和上面那个公差为M的等差数列是一样的，相当于转化为一个子问题
可以大胆猜测(?)，对于所有r符合条件的i的总数并不多，可以爆搜，不过要对所有r预处理出所有合法的i
*/
//#line 2 "AlwaysDefined.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

vector<ll> que[4005];
ll count(ll n,ll w,ll r){
  return n<r?0:(n-r)/w+1;
}
ll dfs(ll n,ll w,ll r){
  //printf("%lld %lld %lld\n",n,w,r);
  if(!n)return 0;
  if(r==1LL){
    return n;
  }
  ll res=0;
  for(int i=0;i<SZ(que[r]);++i){
    ll tr=(que[r][i]*w+r)/r;
    res+=dfs(count(n-1,r,que[r][i]),w,tr);
  }
  return res;
}
class AlwaysDefined {
	public:  
	long long countIntegers(long long L, long long R, int W)  {  
		// $CARETPOSITION$  
    ll ans=0;
    for(int r=1;r<=W;++r){
      que[r].clear();
      for(ll i=0;i<r;++i){
        if(i*W%r==0)que[r].pb(i);
      }
    }
    for(int r=1;r<W;++r){
      ans+=dfs(count(R,W,r),W,r);
      ans-=dfs(count(L-1,W,r),W,r);
      //printf("r %d %lld\n",r,ans);
    }
    return ans;
	}  

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 10LL; long long Arg1 = 10LL; int Arg2 = 4; long long Arg3 = 1LL; verify_case(0, Arg3, countIntegers(Arg0, Arg1, Arg2)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 99LL; int Arg2 = 2; long long Arg3 = 50LL; verify_case(1, Arg3, countIntegers(Arg0, Arg1, Arg2)); }
	void test_case_2() { long long Arg0 = 1282LL; long long Arg1 = 1410LL; int Arg2 = 10; long long Arg3 = 42LL; verify_case(2, Arg3, countIntegers(Arg0, Arg1, Arg2)); }
	void test_case_3() { long long Arg0 = 29195807LL; long long Arg1 = 273209804877LL; int Arg2 = 42; long long Arg3 = 31415926535LL; verify_case(3, Arg3, countIntegers(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AlwaysDefined ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
