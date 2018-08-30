/*
快速幂里面套FWT即可
*/
//#line 2 "Nim.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=1<<17;
const int mod=1000*1000*1000+7;
const int inv2=500000004;
int vis[maxN];
int pn,prim[maxN];
int a[maxN],b[maxN];
void FWT(int a[],int n){
  for(int d=1;d<n;d<<=1){
    for(int i=0;i<n;i+=d+d){
      for(int j=0;j<d;j++){
        int x=a[i+j],y=a[i+j+d];
        a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
      }
    }
  }
}
void UFWT(int a[],int n){
  for(int d=1;d<n;d<<=1){
    for(int i=0;i<n;i+=d+d){
      for(int j=0;j<d;j++){
        int x=a[i+j],y=a[i+j+d];
        a[i+j]=(ll)inv2*(x+y)%mod,a[i+j+d]=(ll)inv2*(x-y)%mod;
      }
    }
  }
}
void mul(int a[],int b[],int n){
  for(int i=0;i<n;i++)a[i]=(ll)a[i]*b[i]%mod;
}
class Nim {
	public:  
	int count(int K, int L)  {  
		// $CARETPOSITION$  
    //printf("tmp %d\n",pow_mod(2,mod-2,mod));
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(vis,0,sizeof(vis));
    pn=0;
    for(int i=2;i<=L;i++){
      if(!vis[i])prim[++pn]=i,b[i]++;
      for(int j=1;j<=pn&&i*prim[j]<=L;j++){
        vis[i*prim[j]]=1;
        if(i%prim[j]==0)break;
      }
    }
    int len=1;
    for(;len<=2*L;len<<=1);
    a[0]=1;
    FWT(a,len);
    FWT(b,len);
    for(;K;K>>=1){
      if(K&1){
        mul(a,b,len);
      }
      mul(b,b,len);  
    }
    UFWT(a,len);
    return a[0];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 7; int Arg2 = 6; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 13; int Arg2 = 120; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 294844622; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123456789; int Arg1 = 12345; int Arg2 = 235511047; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	Nim ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
