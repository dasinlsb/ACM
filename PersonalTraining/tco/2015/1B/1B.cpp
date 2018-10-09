/*
数据范围很小直接暴力算每个点有多少概率贡献答案然后累加即可
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
int g[maxn][maxn];
class TheTips{
	public:
	double solve(vector <string> clues, vector <int> probability){
		// $CARETPOSITION$
    int n=clues.size();
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        g[i][j]=(clues[i][j]=='Y' || i==j);
      }
    }
    for(int k=0;k<n;k++){
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          g[i][j]|=(g[i][k]&g[k][j]);
        }
      }
    }
    double ans=0.0;
    for(int i=0;i<n;i++){
      double t=1;
      for(int j=0;j<n;j++)if(g[j][i])t*=(1.0-probability[j]*0.01);
      ans+=1.0-t;
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.5; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"YN","NY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100,50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.5; verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"YYY","NYY","NNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.0; verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NNN","NNN","NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(3, Arg2, solve(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"NYYNYYNNNN","NNNNYNNNYN","YNNYYYYYNN","YYNYNNNNYN","NYNNNNNNNY","YNYYNNYNNY","NYNNYYYYYY","NYYYYNNNNN","YYNYNNYYYN","NNYYNYNYYY"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {11,66,99,37,64,45,21,67,71,62}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 9.999891558057332; verify_case(4, Arg2, solve(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"NNY","NNY","NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {50, 50, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.7525; verify_case(5, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	TheTips ___test;  
 	 ___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  