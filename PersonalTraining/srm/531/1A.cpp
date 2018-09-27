/*
f[i][j]表示前i个用了j种颜色的方案数
假设下一位用新的颜色，那么转移系数就是(N-j)
假设用旧的颜色，在之前确定的序列都合法的前提下，最后的M位肯定互不相同，所以种类只能从j-M种中任选一种
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=105;
const int mod=1000*1000*1000+7;
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int f[maxn][maxn];
class NoRepeatPlaylist{
	public:
	int numPlaylists(int N, int M, int P){
		// $CARETPOSITION$
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=0;i<P;i++){
      for(int j=0;j<=N;j++){
        up(f[i+1][j+1],1LL*f[i][j]*(N-j)%mod);
        if(j>=M){
          up(f[i+1][j],1LL*f[i][j]*(j-M)%mod);
        }
      }
    }
    return f[P][N];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 3; int Arg3 = 0; verify_case(1, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 3; int Arg3 = 6; verify_case(2, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 0; int Arg2 = 4; int Arg3 = 24; verify_case(3, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(4, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 50; int Arg1 = 5; int Arg2 = 100; int Arg3 = 222288991; verify_case(5, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	NoRepeatPlaylist ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
