/*
如果n是质数，那就分成(1,n-1)，否则直接(n)
还要特判n=1,3...
*/
//#line 2 "MagicDiamonds.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=1000005;
int np;
int vis[maxN];
int prim[maxN];
class MagicDiamonds {
	public:  
	long long minimalTransfer(long long n)  {  
		// $CARETPOSITION$  
    if(n==1|n==3)return n;
    memset(vis,0,sizeof(vis));
    np=0;
    for(int i=2;i<maxN;i++){
      if(!vis[i])prim[++np]=i;
      for(int j=1;j<=np&&i*prim[j]<maxN;j++){
        vis[i*prim[j]]=1;
        if(i%prim[j]==0)break;
      }
    }
    if(n<maxN)return vis[n]?1:2;
    ll m=n;
    for(int i=1;i<=np;i++){
      for(;m%prim[i]==0;m/=prim[i]);
    }
    return m==n?2:1;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 2LL; long long Arg1 = 2LL; verify_case(0, Arg1, minimalTransfer(Arg0)); }
	void test_case_1() { long long Arg0 = 4294967297LL; long long Arg1 = 1LL; verify_case(1, Arg1, minimalTransfer(Arg0)); }
	void test_case_2() { long long Arg0 = 2147483647LL; long long Arg1 = 2LL; verify_case(2, Arg1, minimalTransfer(Arg0)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 1LL; verify_case(3, Arg1, minimalTransfer(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	MagicDiamonds ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
