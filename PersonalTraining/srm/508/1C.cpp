/*
由于回文串肯定是两边两两对称的，所以用f[l][r]表示把原串[l,r]之间变为回文串的最小代价，只要枚举两端点l,r的改变情况即可，floyd预处理空串以及26个字母之间的最小转化代价
*/
//#line 2 "PalindromizationDiv1.cpp"  
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
const int inf=50000*10000;
int str[maxN],g[27][27],f[maxN][maxN];
inline void cmin(int&x,int y){if(y<x)x=y;}
int change(string&s,int p){
  int x=0;
  for(;p<SZ(s);++p){
    assert(s[p]>='0'&&s[p]<='9');
    x=x*10+s[p]-'0';
  }
  return x;
}
class PalindromizationDiv1 {
	public:  
	int getMinimumCost(string word, vector <string> operations)  {  
		// $CARETPOSITION$  
    int i,j;
    int n=SZ(word);
    for(i=0;i<n;++i)str[i+1]=word[i]-'a';
    vector<string>&op=operations;
    for(i=0;i<=26;++i){
      for(j=0;j<=26;++j){
        g[i][j]=inf;
      }
      g[i][i]=0;
    }
    for(i=0;i<SZ(op);++i){
      if(op[i].substr(0,3)=="add"){
        //printf("add %d\n",op[i][4]-'a');
        g[26][op[i][4]-'a']=change(op[i],6);
      }
      if(op[i].substr(0,5)=="erase"){
        //printf("erase %d\n",op[i][6]-'a');
        g[op[i][6]-'a'][26]=change(op[i],8);
      }
      if(op[i].substr(0,6)=="change"){
        //printf("change %d %d\n",op[i][7]-'a',op[i][9]-'a');
        assert(op[i][9]>='a'&&op[i][9]<='z');
        g[op[i][7]-'a'][op[i][9]-'a']=change(op[i],11);
      }
    }
    for(int k=0;k<=26;++k){
      for(i=0;i<=26;++i){
        for(j=0;j<=26;++j){
          g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
        }
      }
    }
    //
    for(int d=2;d<=n;++d){
      for(int l=1;l+d-1<=n;++l){
        int r=l+d-1;
        f[l][r]=inf;
        for(i=0;i<=26;++i){
          cmin(f[l][r],f[l+1][r-1]+g[str[l]][i]+g[str[r]][i]);
          cmin(f[l][r],f[l+1][r]+g[str[l]][i]+g[26][i]);
          cmin(f[l][r],f[l][r-1]+g[str[r]][i]+g[26][i]);
        }
      }
    }
    return f[1][n]<inf?f[1][n]:-1;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "racecar"; string Arr1[] = {}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "topcoder"; string Arr1[] = {"erase t 1", "erase o 1", "erase p 1", "erase c 1", "erase d 1", "erase e 1", "erase r 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "topcoder"; string Arr1[] = {"erase t 10", "erase o 1", "erase p 1", "erase c 1", "erase d 1", "erase e 1", "erase r 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(2, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "caaaaaab"; string Arr1[] = {"change b a 100000", "change c a 100000", "change c d 50000", "change b e 50000", "erase d 50000", "erase e 49999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 199999; verify_case(3, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "moon"; string Arr1[] = {"erase o 5", "add u 7", "change d p 3", "change m s 12", "change n d 6", "change s l 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(4, Arg2, getMinimumCost(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	PalindromizationDiv1 ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  

