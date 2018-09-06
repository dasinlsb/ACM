/*
每个点度数>=1，直接跑背包就行了
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=55;
inline void up(int&x,int y){
  if(x<y)x=y;
}
int f[maxn][maxn*2];
class P8XGraphBuilder{
	public:
	int solve(vector <int> scores){
		// $CARETPOSITION$
    int n=scores.size()+1;
    memset(f,-1,sizeof(f));
    f[0][0]=0;
    int total=2*(n-1);
    for(int i=0;i<n;i++){
      for(int j=0;j<=total;j++)if(~f[i][j]){
        for(int k=1;k<n;k++)if(j+k<=total){
          up(f[i+1][j+k],f[i][j]+scores[k-1]);
        }
      }
    }
    return f[n][total];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 3, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { int Arr0[] = {5, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 3, 2, 5, 3, 7, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(4, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	P8XGraphBuilder ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
