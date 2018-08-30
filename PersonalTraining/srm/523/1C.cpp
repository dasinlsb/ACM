/*
显然可以枚举路径中点bfs跑出长度为11的答案然后meet in the middle
这题内存限制64MB会卡掉一些正常的写法...
在bfs的过程中，由于不能往回走，所以除了第一层，其他层每个状态都只有3种转移
但是直接bfs，21*21*(C(21,11)/3^10)两种写法内存都是无法接受的
内存要避免和n*m挂钩，可以牺牲一点时间跑dfs，在跑到长度恰好为11时更新路径数
时间复杂度O(n*m*(4*3^9+(C(21,11)^2))
*/
//#line 2 "AlphabetPaths.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int dr[4]={-1,0,1,0};
const int dc[4]={0,1,0,-1};
int n,m,T;
vector<string>a;
int pos[1<<21];
ll f[352716];
int vis[352716];
void dfs(int r,int c,int s,int v){
  //printf("dp  %d %d %d %d %d %d\n",r,c,s,v,pos[s],__builtin_popcount(s));
  if(pos[s]!=-1){
    if(vis[pos[s]]!=T)f[pos[s]]=0,vis[pos[s]]=T;
    f[pos[s]]+=v;
    return;
  }
  for(int i=0;i<4;i++){
    int _r=r+dr[i],_c=c+dc[i];
    if(_r>=0&&_r<n&&_c>=0&&_c<m){
      if(a[_r][_c]!='.'&&((1<<a[_r][_c]-'A')&s)==0){
        dfs(_r,_c,s|(1<<a[_r][_c]-'A'),v);
      }
    }
  }
}
const char new_char[21]={
'A','B','C','D','E','F','Z','H','I','K','L','M','N','O','P','Q','R','S','T','V','X'
};
int id[200];
class AlphabetPaths {
	public:  
	long long count(vector <string> letterMaze)  {  
		// $CARETPOSITION$  
    for(int i=0;i<21;i++)id[new_char[i]]=i;
    a=letterMaze;
    n=SZ(a);
    m=SZ(a[0]);
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++)if(a[i][j]!='.'){
        a[i][j]=id[a[i][j]]+'A';
      }
    }
    vector<int>num;
    memset(pos,-1,sizeof(pos));
    for(int S=1;S<1<<21;S++){
      if(__builtin_popcount(S)==11){
        num.pb(S);
        pos[S]=SZ(num)-1;
      }
    }
    int all=(1<<21)-1;
    ll ans=0;
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++)if(a[i][j]!='.'){
        int x=a[i][j]-'A';
        T++;dfs(i,j,1<<x,1);
        for(int k=0;k<SZ(num);k++)if((1<<x&num[k])!=0){
          int k2=pos[(all^num[k])|1<<x];
          if(vis[k2]==T&&vis[k]==T){
            ans+=f[k]*f[k2];
          }
        }
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ABCDEFZHIXKLMNOPQRST",
 "...................V"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"TBCDE.PQRSA", 
 "FZHIXKLMNOV"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AlphabetPaths ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
