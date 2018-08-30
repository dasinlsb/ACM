/*
直接跑O(n^3)的dp
f[l][r]表示[l,r]这段的答案，枚举中间的分割点转移，再讨论一下两端就行了
*/
//#line 2 "MissingParentheses.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=55;
int f[maxN][maxN];
inline void up(int&x,int y){
  if(y<x)x=y;
}
class MissingParentheses {
	public:  
	int countCorrections(string par)  {  
		// $CARETPOSITION$  
    int n=SZ(par);
    memset(f,0,sizeof(f));
    for(int r=0;r<n;r++){
      for(int l=r;l>=0;l--){
        f[l][r]=r-l+1;
        up(f[l][r],min(f[l+1][r],f[l][r-1])+1);
        for(int i=l;i<r;i++){
          up(f[l][r],f[l][i]+f[i+1][r]);
        }
        if(par[l]=='('&&par[r]==')'){
          up(f[l][r],f[l+1][r-1]);
        }
        //printf("f %d %d : %d\n",l,r,f[l][r]);
      }
    }
    return f[0][n-1];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "(()(()"; int Arg1 = 2; verify_case(0, Arg1, countCorrections(Arg0)); }
	void test_case_1() { string Arg0 = "()()(()"; int Arg1 = 1; verify_case(1, Arg1, countCorrections(Arg0)); }
	void test_case_2() { string Arg0 = "(())(()())"; int Arg1 = 0; verify_case(2, Arg1, countCorrections(Arg0)); }
	void test_case_3() { string Arg0 = "())(())((()))))()((())))()())())())()()()"; int Arg1 = 7; verify_case(3, Arg1, countCorrections(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	MissingParentheses ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
