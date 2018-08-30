/*
考虑一种十分直接的暴力，每次在同时知道两种故事的点集中枚举子集来划分成两个集合，分别讲两种故事
这样做状态数十分爆炸，考虑冗余出现在哪里，显然每个人每种故事只要说一次即可
唯一需要决策的地方就是某个时刻某个人同时得知两种故事，这种情况在整个过程中每个人最多遇到一次
也就是说最多只有n<=16个需要决策的地方，暴力2^n枚举优先级然后模拟剩下的即可
*/
//#line 2 "Rumor.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxn=16;

class Rumor {
	public:  
  int f[maxn+6][maxn],vis[maxn];
  int chk(int f[],int n){
    for(int i=0;i<n;i++)if(f[i]!=3)return 1;
    return 0;
  }
	int getMinimum(string knowledge, vector <string> graph)  {  
		// $CARETPOSITION$  
    int n=knowledge.size();
    int ans=n+5;
    for(int S=0;S<1<<n;S++){
      memset(f,0,sizeof(f));
      for(int i=0;i<n;i++){
        f[0][i]=(knowledge[i]=='Y'?3:0);
        vis[i]=0;
      }
      int d=0;
      for(;chk(f[d],n)&&d<n+5;d++){
        for(int i=0;i<n;i++){
          if(f[d][i]==0)continue;
          int k;
          if(f[d][i]==3){
            if(!vis[i])vis[i]=k=(S>>i&1)+1;
            else k=3-vis[i];
          }else{
            vis[i]=k=f[d][i];
          }
          for(int j=0;j<n;j++)if(graph[i][j]=='Y'){
            f[d+1][j]|=k;
          }
          f[d+1][i]|=f[d][i];
        }
      }
      ans=min(ans,d);
    }
    return ans==n+5?-1:ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNN"; string Arr1[] = {"NYN"
,"NNY"
,"NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "YNNY"; string Arr1[] = {"NYYN"
,"YNNY"
,"YNNY"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "YYYY"; string Arr1[] = {"NYNN"
,"YNYN"
,"NYNY"
,"NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "YYYYYN"; string Arr1[] = {"NYYYYN"
,"YNYYYN"
,"YYNYYN"
,"YYYNYN"
,"YYYYNN"
,"NNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "NNNY"; string Arr1[] = {"NNNN"
,"YNNN"
,"YNNN"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_5() { string Arg0 =  "NNNNNNNYYY"; string Arr1[] = {"NYNNYNNYNN"
,"NNYNYNNNNY"
,"YYNNNYNNNN"
,"YNNNYNYNNN"
,"NNYNNYNNYN"
,"NNNNYNNNYY"
,"NYNYNYNNNN"
,"NNNNNNYNYY"
,"NNNYNNNYNY"
,"NYYNNNNYNN"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(5, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	Rumor ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
