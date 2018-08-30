/*
同构肯定是某些集合内部互相等价，肯定是写成若干个阶乘独立相乘的形式，这个可以记忆话搜索
假设age可以分解成\prod_{1<=i<=k}(a_i!)，那么有一种构造方法是开k个关键点形成一条链，链上每个点挂a_i个子节点
为了破坏整体的对称性，可以在链的某一端加两个点
*/
//#line 2 "AutomorphicTree.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
ll fac[25];
VI tear;
map<ll,int>can;
int dfs(ll n){
  //if(n<100005&&~vis[n])return vis[n];
  if(can.count(n))return can[n];
  for(int i=2;i<=19&&fac[i]<=n;i++)if(n%fac[i]==0){
    if(dfs(n/fac[i]))return tear.pb(i),can[n]=1;//n<100005?(vis[n]=1):1;
  }
  return can[n]=0;
  //return n<100005?(vis[n]=0):0;
}
class AutomorphicTree {
	public:  
	vector <int> construct(long long age)  {  
		// $CARETPOSITION$  
    fac[0]=1;
    for(int i=1;i<=19;i++){
      fac[i]=fac[i-1]*i;
    }
    VI ans;
    if(age==1){ans.pb(1);return ans;}
    tear.clear();can.clear();
    can[1]=1;
    if(!dfs(age))return ans;
    ans.pb(2);
    for(int i=0;i<SZ(tear);i++){
      ans[0]+=tear[i]+1;
    }
    int leaf=SZ(tear)+2;
    for(int i=0;i<SZ(tear);i++){
      for(int j=0;j<tear[i];j++){
        ans.pb(i);
        ans.pb(leaf++);
      }
      ans.pb(i);
      ans.pb(i+1);
    }
    ans.pb(SZ(tear));
    ans.pb(SZ(tear)+1);
    assert(SZ(ans)==2*ans[0]-1);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 1LL; int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { long long Arg0 = 8LL; int Arr1[] = {6, 0, 1, 1, 2, 3, 4, 4, 5, 4, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { long long Arg0 = 1000000000000000000LL; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, construct(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AutomorphicTree ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
