/*
从上到下贪心地让每个？尽量成为？，这样的话每个level结束后的序列是唯一确定的
*/
//#line 2 "SwitchingGame.cpp"  
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
int f[maxN];
int s[maxN][maxN];
int F(char x){
  if(x=='?')return -1;
  if(x=='+')return 1;
  if(x=='-')return 0;
}
class SwitchingGame {
	public:  
	int timeToWin(vector <string> states)  {  
		// $CARETPOSITION$
    int n=SZ(states);
    int m=SZ(states[0]);
    for(int i=0;i<=n;i++){
      for(int j=0;j<m;j++)s[i][j]=i?F(states[i-1][j]):0;
    }
    for(int i=0;i<m;++i)f[i]=0;
    int ans=n;
    for(int i=1;i<=n;++i){
      int change[2]={0,0};
      for(int j=0;j<m;++j){
        if(f[j]==-1){
          f[j]=s[i][j];
          continue;
        }
        if(~f[j]&&~s[i][j]&&f[j]!=s[i][j]){
          change[f[j]]=1;
          f[j]=s[i][j];
        }
      }
      for(int j=0;j<m;++j){
        if(~f[j]&&s[i][j]==-1){
          f[j]=change[f[j]]?-1:f[j];
        }
      }
      ans+=change[0]+change[1];
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"++--",
 "--++"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, timeToWin(Arg0)); }
	void test_case_1() { string Arr0[] = {"+-++",
 "+-++"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, timeToWin(Arg0)); }
	void test_case_2() { string Arr0[] = {"++",
 "+?",
 "?+",
 "++"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(2, Arg1, timeToWin(Arg0)); }
	void test_case_3() { string Arr0[] = {"+", 
 "?",
 "?",
 "?",
 "-"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, timeToWin(Arg0)); }
	void test_case_4() { string Arr0[] = {"+??+++",
 "++??+-",
 "?++??+",
 "?-+-??",
 "??+?++",
 "++-?+?",
 "?++?-+",
 "?--+++",
 "-?\?-?+"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(4, Arg1, timeToWin(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	SwitchingGame ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
