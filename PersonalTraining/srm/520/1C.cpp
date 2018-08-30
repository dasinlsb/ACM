/*
很多细节看了题解才想通，太难辣..
首先原序列可以按照是否叉过别人和是否被成功叉过分成4类,d[0/1][0/1]
但是直接拿这4类各自的数量和转移规则去跑dp肯定是无法接受的
考虑固定特殊性较强的一类:d[1][1]
题目中要求的是合法的表格数量，那么在任意一个从上到下按时间递增的合法表格中，假设进行叉的人在第一列，被叉的人在第二列
任意一个d[1][1]必定出现在某个第i行的第1列，以及某个第j行的第二列，满足i<j
可以用dp解决放置d[1][1]的合法方案这样一个子问题
用f[i][j]表示共i行放置j个d[1][1]的方案
假设第一行第一列没有d[1][1]，那么就是f[i-1][j]
假设第一行第一列有d[1][1]，那么假设下面的i-1行都已经放完了j-1个,第二列会剩下i-j个空位，都是合法的，那么就转移到(i-j)*f[i-1][j-1]
显然整个表格是d[1][0]+d[1][1]行，现在已经分别在两列中的若干行中填入d[1][1]
显然第一列剩下的都是d[1][0],第二列剩下的优先填d[0][1]，然后就随便了，注意不要叉自己就行了
最后由于带标号，还要乘上对应的系数
*/
//#line 2 "SRMChallengePhase.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=2505;
const int mod=1000*1000*1000+7;
int pow_mod(int x,int y){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=(ll)t*x%mod;
    x=(ll)x*x%mod;
  }
  return t;
}
int fac[maxN],inv[maxN];
int f[maxN][maxN];
int comb(int x,int y){
  return (ll)fac[x]*inv[y]%mod*inv[x-y]%mod;
}
class SRMChallengePhase {
	public:  
	int countWays(vector <string> codersAttempted, vector <string> codersChallenged)  {  
		// $CARETPOSITION$  
    string str[2];
    for(int i=0;i<SZ(codersAttempted);i++){
      str[0]+=codersAttempted[i];
    }
    for(int i=0;i<SZ(codersChallenged);i++){
      str[1]+=codersChallenged[i];
    }
    int n=SZ(str[0]);
    int d[2][2];
    memset(d,0,sizeof(d));
    for(int i=0;i<n;i++){
      d[str[0][i]=='Y'][str[1][i]=='Y']++;
    }
    if(d[1][0]<d[0][1])return 0;
    if(n==1)return d[0][0]==1;
    memset(f,0,sizeof(f));
    for(int i=1;i<=d[1][1]+d[1][0];i++){
      f[i][0]=1;
      for(int j=1;j<=i;j++){
        f[i][j]=(f[i][j]+f[i-1][j]+(ll)(i-j)*f[i-1][j-1])%mod;
      }
    }
    fac[0]=1;
    for(int i=1;i<maxN;i++)fac[i]=(ll)fac[i-1]*i%mod;
    inv[maxN-1]=pow_mod(fac[maxN-1],mod-2);
    for(int i=maxN-1;i;i--)inv[i-1]=(ll)inv[i]*i%mod;
    int ans=(ll)f[d[1][1]+d[1][0]][d[1][1]]*fac[d[1][1]]%mod*fac[d[1][0]]%mod;
    ans=(ll)ans*comb(d[1][0],d[0][1])%mod*fac[d[0][1]]%mod*pow_mod(n-1,d[1][0]-d[0][1])%mod;
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"YY", "NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"N", "NYY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"YNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYY", "Y"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"N"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"YYY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 24; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"YY", "N", "YYYY", "NN", "YYYYY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"N", "YYYYY", "N", "Y", "N", "YYYY", "N"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 807026001; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	SRMChallengePhase ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
