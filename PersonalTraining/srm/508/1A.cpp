/*
显然两种操作的顺序可以互换，可以规定取模操作必定在前，枚举一下因数除掉即可
*/
//#line 2 "DivideAndShift.cpp"  
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
int np,vis[maxN],p[maxN],q[22];
class DivideAndShift {
	public:  
	int getLeast(int N, int M)  {  
		// $CARETPOSITION$  
    int i,j;--M;
    fill(vis,vis+maxN,0);
    for(np=0,i=2;i<maxN;++i){
      if(!vis[i])p[++np]=i;
      for(j=1;j<=np&&i*p[j]<maxN;++j){
        vis[i*p[j]]=1;
        if(i%p[j]==0)break;
      }
    }
    int t=N,cnt=0;
    for(i=1;i<=np;++i){
      for(;t%p[i]==0;t/=p[i]){
        q[cnt++]=p[i];
      }
    }
    //printf("cnt %d\n",cnt);
    int ans=N;
    for(int S=0;S<1<<cnt;++S){
      int k=0,t=N;
      for(i=0;i<cnt;++i)if((1<<i)&S){
        ++k;t/=q[i];
      }
      ans=min(ans,k+min(M%t,t-M%t));
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 56; int Arg1 = 14; int Arg2 = 3; verify_case(0, Arg2, getLeast(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 49; int Arg1 = 5; int Arg2 = 2; verify_case(1, Arg2, getLeast(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 256; int Arg1 = 7; int Arg2 = 6; verify_case(2, Arg2, getLeast(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 0; verify_case(3, Arg2, getLeast(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 77777; int Arg1 = 11111; int Arg2 = 2; verify_case(4, Arg2, getLeast(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	DivideAndShift ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
