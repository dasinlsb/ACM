/*
十分有趣的题目
直接搜路径无法接受，有一种非常巧妙的想法，跑一次floyd后，把所有g[0][i]==1&&g[i][n-1]==1的点单独考虑
因为其他点肯定不影响答案，对这些点，从0出发构造一棵有向的生成树，显然肯定可以构造出来
在这棵生成树上,0到n-1的路径显然只有一条，对于所有不在这棵生成树中的边(x,y)，如果满足g[0][x]&&g[x][n-1]，那么这条边肯定对应一条0到n-1的路径
所以答案就是所有合法边-生成树边+1
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
int g[maxn][maxn];
class GogoXMarisaKirisima{
	public:
	int solve(vector <string> choices){
		// $CARETPOSITION$
    int n=choices.size();
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        g[i][j]=(i==j || choices[i][j]=='Y');
      }
    }
    for(int k=0;k<n;k++){
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          g[i][j]|=(g[i][k]&g[k][j]);
        }
      }
    }
    if(!g[0][n-1])return 0;
    int ans=1;
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++)if(choices[i][j]=='Y' && g[0][i] && g[j][n-1]){
        ans++;
      }
    }
    for(int i=1;i<n;i++)if(g[0][i] && g[i][n-1])ans--;
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN"
,"YNY"
,"NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"NNY"
,"YNY"
,"YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {"NN"
,"NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYYY"
,"NNNY"
,"NNNY"
,"NNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	GogoXMarisaKirisima ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
