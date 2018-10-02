/*
由于是两两匹配，可以用0/1来记录某个数是否已经匹配，这样就不用在递推的过程中知道序列的详细信息了
f[i][S][j]表示从小到大考虑到i,i之前K个已匹配/未匹配的状态为S的方案数
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=105;
const int mod=1000*1000*1000+7;
int f[maxn][1<<10];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
class AlienAndSetDiv2{
	public:
	int getNumber(int N, int K){
		// $CARETPOSITION$
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<2*N;i++){
      for(int S=0;S<1<<K;S++){
        if(S&1){
          up(f[i+1][S>>1],f[i][S]);
        }else{
          if(S==0){
            up(f[i+1][1<<K-1],2LL*f[i][S]%mod);
          }else{
            up(f[i+1][(S^(S&-S))>>1],f[i][S]);
            up(f[i+1][(S>>1)|(1<<K-1)],f[i][S]);
          }
        }
      }
    }
    return f[2*N][0];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 4; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 8; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 44; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 184756; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	AlienAndSetDiv2 ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
