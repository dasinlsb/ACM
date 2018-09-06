/*
一开始想以怎样的连边顺序才能保证答案字典序最小，但是发现不可做，还是要枚举每一位是否能放0跑一次二分图匹配来逐位确定
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=35;
int R,C;
vector<int >G[maxn];
int T,links[maxn],vis[maxn];
int dfs(int x){
  for(int v:G[x])if(vis[v]!=T){
    vis[v]=T;
    if(links[v]==-1||dfs(links[v])){
      return links[v]=x,1;
    }
  }
  return 0;
}
bool matched(char x,char y){
  return x=='?'||y=='?'||x==y;
}
int calc(vector<string >&rows,vector<string >&columns){
  for(int i=0;i<C;i++){
    G[i].clear();
    links[i]=-1;
  }
  for(int i=0;i<C;i++){
    for(int j=0;j<C;j++){
      int ban=0;
      for(int k=0;k<R;k++){
        if(!matched(rows[k][i],columns[j][k])){
          ban=1;
        }
      }
      if(!ban)G[i].push_back(j);
    }
  }
  for(int i=0;i<C;i++){
    if(++T,!dfs(i))return 0;
  }
  return 1;
}
class P8XMatrixRecovery{
	public:
	vector <string> solve(vector <string> rows, vector <string> columns){
		// $CARETPOSITION$
    R=rows.size();
    C=rows[0].size();
    for(int i=0;i<R;i++){
      for(int j=0;j<C;j++){
        if(rows[i][j]!='?')continue;
        rows[i][j]='0';
        if(calc(rows,columns)==0){
          rows[i][j]='1';
        }
      }
    }
    return rows;

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"10?"
,"?11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"01"
,"10"
,"1?"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"101", "011" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0"
,"?"
,"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0?1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0", "0", "1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"10"
,"01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"10"
,"01"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10", "01" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"??0"
,"11?"
,"?01"
,"1?1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1???"
,"?111"
,"0?1?"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"010", "110", "101", "101" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	P8XMatrixRecovery ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
