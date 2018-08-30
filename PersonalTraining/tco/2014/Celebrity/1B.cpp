/*
推一下式子移项就能看出来了
*/
//#line 2 "ConcatenateNumbers.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=100005;
const int mod=1000*1000*1000+7;
int decimalCount(int x){
  int t=0;
  for(;x;x/=10)++t;
  return t;
}
int pw(int x,int y){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=(ll)t*x%mod;
    x=(ll)x*x%mod;
  }
  return t;
}
int val[maxN];
int inv[maxN];
map<int,int>valCnt;
class ConcatenateNumbers {
	public:  
	long long numberOfSegments(int L, int R, int v)  {  
		// $CARETPOSITION$  
    int inv10=pw(10,mod-2);
    inv[0]=1;
    for(int i=L;i<=R;i++){
      val[i-L+1]=((ll)val[i-L]*pw(10,decimalCount(i))+i)%mod;
      inv[i-L+1]=(ll)inv[i-L]*pw(inv10,decimalCount(i))%mod;
    }
    valCnt.clear();
    ll ans=0;
    for(int i=L;i<=R;i++){
      valCnt[(ll)val[i-L]*inv[i-L]%mod]++;
      int now=(ll)(val[i-L+1]-v+mod)*inv[i-L+1]%mod;
      ans+=valCnt[now];
      //printf("add at %d : %d\n",i,valCnt[now]);
    }
    return ans;
	}   
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 11; int Arg1 = 13; int Arg2 = 111213; long long Arg3 = 1LL; verify_case(0, Arg3, numberOfSegments(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 11; int Arg1 = 13; int Arg2 = 11213; long long Arg3 = 0LL; verify_case(1, Arg3, numberOfSegments(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 11; int Arg1 = 13; int Arg2 = 14; long long Arg3 = 0LL; verify_case(2, Arg3, numberOfSegments(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 100000; int Arg2 = 12345; long long Arg3 = 10LL; verify_case(3, Arg3, numberOfSegments(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 999900001; int Arg1 = 1000000000; int Arg2 = 0; long long Arg3 = 7LL; verify_case(4, Arg3, numberOfSegments(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
  freopen("tmp.txt","w",stdout);
	ConcatenateNumbers ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
