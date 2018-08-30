/*
建出ac自动机直接dp,沿着fail转移
*/
//#line 2 "RequiredSubstrings.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=333;
const int mod=1000*1000*1000+9;
inline void up(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
int tot,root;
int son[maxN][26],fail[maxN],en[maxN];
int bit[1<<6];
int f[55][maxN][1<<6];
int new_node(){
  int x=++tot;
  for(int i=0;i<26;i++)son[x][i]=0;
  en[x]=0;fail[x]=0;
  return x;
}
void make(){
  static int q[maxN];
  int h=0,t=-1;
  for(int i=0;i<26;i++)if(son[root][i]){
    q[++t]=son[root][i];
  }
  for(;h<=t;){
    int x=q[h++];
    en[x]|=en[fail[x]];
    for(int i=0;i<26;i++){
      if(son[x][i]){
        fail[son[x][i]]=son[fail[x]][i];
        q[++t]=son[x][i];
      }else{
        son[x][i]=son[fail[x]][i];
      }
    }
  }
}
class RequiredSubstrings {
	public:  
	int solve(vector <string> words, int C, int L)  {  
		// $CARETPOSITION$  
    tot=-1;
    root=new_node();
    for(int i=0;i<SZ(words);i++){
      int x=root;
      for(int j=0;j<SZ(words[i]);j++){
        int w=words[i][j]-'a';
        if(son[x][w]==0){
          son[x][w]=new_node();
        }
        x=son[x][w];
      }
      en[x]|=1<<i;
    }
    make();
    for(int i=1;i<1<<6;i++){
      bit[i]=bit[i>>1]+(i&1);
    }
    memset(f,0,sizeof(f));
    f[0][0][0]=1;
    int ans=0;
    for(int i=0;i<=L;i++){
      for(int x=0;x<=tot;x++){
        for(int S=0;S<1<<SZ(words);S++){
          if(i==L&&bit[S]==C){
            up(ans,f[i][x][S]);
            continue;
          }
          for(int c=0;c<26;c++){
            up(f[i+1][son[x][c]][S|en[son[x][c]]],f[i][x][S]);
          }
        }
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"a","aa","aaa","aaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 50; verify_case(0, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 7; int Arg3 = 31810104; verify_case(1, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7; int Arg3 = 0; verify_case(2, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"a","b","c","d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; int Arg3 = 24; verify_case(3, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"ab","bc","xy","yz"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 2; verify_case(4, Arg3, solve(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	RequiredSubstrings ___test;  
 	___test.run_test(-1);  
  return 0;  
}  
// END CUT HERE  
