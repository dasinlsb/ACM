/*
有一种直接的想法是行列交替地去选整条的，不过样例3是反例，我一直想不出什么好的补丁，就换了个做法
显然要么全部行都被选过，要么全部列都被选过，但是不可能全部行列都被选过，且每行每列最多选一次
那么可以枚举一下没选的那行或那列，假设枚举某一行k没选，那么列的染色是唯一确定的
对于某一行i,要么对应位置和第k行完全相同，要么不同的位置上的颜色只有一种，那么行的染色也是唯一确定的
剩下的问题就是如何确定行列染色的先后顺序，可以考虑把所有约束加到第k行上去
对于矩阵的每个位置，可能可以确定这个位置是先被对应行染色还是先被对应列染色，也可能无法断言
对于每一行可以断言的若干列，可以添加第x列必定先于第y列染色的约束，扫描完全部行如果这些约束存在冲突则无解
时间复杂度O(n^4)，不过很不满
*/
//#line 2 "ColorfulBoard.cpp"  
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
const int inf=123;
int solve(vector<string>&a,int n,int m){
  static int vis[maxN],g[maxN][maxN];
  int ans=inf;
  for(int i=0;i<n;i++){
    int ok=1;
    memset(g,0,sizeof(g));
    int res=m;
    for(int j=0;j<n;j++){
      int val=-1;
      memset(vis,0,sizeof(vis));
      for(int k=0;k<m;k++){
        if(a[j][k]!=a[i][k]){
          vis[k]=1;
          if(val==-1){
            val=a[j][k];
          }else if(a[j][k]!=val){
            ok=0;
          }
        }
      }
      if(val!=-1){
        res++;
        for(int k1=0;k1<m;k1++)if(vis[k1]==0&&a[j][k1]!=val){
          for(int k2=0;k2<m;k2++)if(vis[k2]==1){
            if(g[k1][k2]==-1){
              ok=0;
            }
            g[k1][k2]=1;
            g[k2][k1]=-1;
          }
        }
      }
    }
    if(ok){
      ans=min(ans,res);
    }
  }
  return ans;
}
class ColorfulBoard {
	public:  
	int theMin(vector <string> board)  {  
		// $CARETPOSITION$  
    int n=SZ(board);
    int m=SZ(board[0]);
    int ans=solve(board,n,m);
    vector<string>rot(m);
    for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
        rot[i].pb(board[j][i]);
      }
    }
    ans=min(ans,solve(rot,m,n));
    return ans==inf?-1:ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"SSS",
 "SRR",
 "SMM"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, theMin(Arg0)); }
	void test_case_1() { string Arr0[] = {"BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(1, Arg1, theMin(Arg0)); }
	void test_case_2() { string Arr0[] = {"Ab",
 "bA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, theMin(Arg0)); }
	void test_case_3() { string Arr0[] = {"iiiii",
 "iwiwi"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, theMin(Arg0)); }
	void test_case_4() { string Arr0[] = {"ffffffffff",
 "xfxxoofoxo",
 "ffffffffff",
 "xfxxoofoxo",
 "ffffffffff",
 "ooxxoofoxo",
 "xfxxoofoxo",
 "xfxxoxfxxo",
 "ffxxofffxo",
 "xfxxoxfxxo"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 17; verify_case(4, Arg1, theMin(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	ColorfulBoard ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
