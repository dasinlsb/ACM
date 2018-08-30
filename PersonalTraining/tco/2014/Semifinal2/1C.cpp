/*
n>=2时候形成的树肯定是轴对称的，可以推出递推式，生成函数高高就行了
*/
//#line 2 "TwiceTwiceTree.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=510;
int pw(int x,int y,int mod){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=(ll)t*x%mod;
    x=(ll)x*x%mod;
  }
  return t;
}
void ploy_mul(int a[],int b[],int n,int mod){
  static int c[maxN];
  memset(c,0,sizeof(c));
  for(int i=0;i<n;i++){
    for(int j=0;i+j<n;j++){
      c[i+j]=(c[i+j]+(ll)a[i]*b[j])%mod;
    }
  }
  memcpy(a,c,n*sizeof(int));
}
void ploy_pw(int poly[],int n,int k,int mod){
  static int a[maxN];
  static int b[maxN];
  memcpy(a,poly,n*sizeof(int));
  memset(b,0,sizeof(b));
  b[0]=1;
  for(;k;k>>=1){
    if(k&1)ploy_mul(b,a,n,mod);
    ploy_mul(a,a,n,mod);
  }
  memcpy(poly,b,n*sizeof(int));
}
int coef[maxN];
int coefNew[maxN];
class TwiceTwiceTree {
	public:  
	int sumup(int N, int D, int P)  {  
		// $CARETPOSITION$  
    memset(coef,0,sizeof(coef));
    coef[0]=coef[1]=1;
    ploy_pw(coef,D+8,2*N,P);
    for(int i=D+5;i;--i)coef[i]=P-coef[i-1];coef[0]=0;
    coef[1]=(coef[1]+pw(2,N,P))%P;
    memset(coefNew,0,sizeof(coefNew));
    coefNew[0]=coef[0];
    coefNew[1]=(coef[1]+2LL*coefNew[0])%P;
    for(int i=2;i<=D;i++){
      coefNew[i]=(coef[i]+2LL*coefNew[i-1]+coefNew[i-2])%P;
    }
    coefNew[0]=(coefNew[0]+1)%P;
    return coefNew[D];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 1000000007; int Arg3 = 8; verify_case(0, Arg3, sumup(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 503; int Arg3 = 0; verify_case(1, Arg3, sumup(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 503; int Arg3 = 17; verify_case(2, Arg3, sumup(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 5; int Arg2 = 1000000009; int Arg3 = 21352; verify_case(3, Arg3, sumup(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 987654321; int Arg1 = 500; int Arg2 = 1000000009; int Arg3 = 420937613; verify_case(4, Arg3, sumup(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	TwiceTwiceTree ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
