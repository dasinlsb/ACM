/*
简单dp
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
long long f[maxn][maxn][2][maxn*maxn/2];
class DevuAndBeautifulSubstrings{
	public:
	long long countBeautifulSubstrings(int n, int cnt){
		// $CARETPOSITION$
    memset(f,0,sizeof(f));
    f[1][1][0][1]=1;
    f[1][1][1][1]=1;
    long long ans=0;
    for(int i=1;i<=n;i++){
      for(int len=1;len<=i;len++){
        for(int last=0;last<2;last++){
          int max_now=i*(i+1)/2;
          for(int now=0;now<=max_now;now++){
            if(i==n && now==cnt){
              ans+=f[i][len][last][now];
              continue;
            }
            f[i+1][1][last][now+1]+=f[i][len][last][now];
            f[i+1][len+1][last^1][now+len+1]+=f[i][len][last][now];
          }
        }
      }
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; long long Arg2 = 2LL; verify_case(0, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; long long Arg2 = 0LL; verify_case(1, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 4; long long Arg2 = 4LL; verify_case(2, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 15; int Arg1 = 35; long long Arg2 = 642LL; verify_case(3, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 40; int Arg1 = 820; long long Arg2 = 2LL; verify_case(4, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 50; int Arg1 = 94; long long Arg2 = 32357325751902LL; verify_case(5, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	DevuAndBeautifulSubstrings ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
