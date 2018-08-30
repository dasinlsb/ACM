/*
由于榜有单调性，可以dp,f[i][j]表示前i个，第i个总分为j的方案数
由于会出现总分相同，三道题各自得分不同而导致方案不同，所以要预处理每一层i单层总分为j的方案数g[i][j]
f和g的转移都是区间到区间，可以枚举其中一维，另一维前缀和搞搞
时间复杂度O(n*3*20W)
*/
//#line 2 "SRMIntermissionPhase.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxM=200001;
const int mod=1000*1000*1000+7;
inline void up(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
int f[22][maxM+5];
int g[maxM+5];
int h[maxM+5];
class SRMIntermissionPhase {
	public:  
	int countWays(vector <int> points, vector <string> description)  {  
		// $CARETPOSITION$  
    vector<string>&des=description;
    int n=SZ(des);
    memset(f,0,sizeof(f));
    f[0][maxM]=1;
    for(int i=0;i<n;i++){
      int low=0;
      int top=0;
      memset(g,0,sizeof(g));
      g[0]=1;
      for(int j=0;j<3;j++)if(des[i][j]=='Y'){
        for(int k=1;k<=maxM;k++)up(g[k],g[k-1]);
        memset(h,0,sizeof(h));
        for(int k=1;k<=maxM;k++){
          up(h[k],g[k-1]);
          if(k-points[j]>0)up(h[k],mod-g[k-points[j]-1]);
        }
        for(int k=0;k<=maxM;k++)g[k]=h[k];
        low++;
        top+=points[j];
      }
      for(int j=low+1;j<=maxM;j++){
        up(f[i+1][low],f[i][j]);
        up(f[i+1][min(top,j-1)+1],mod-f[i][j]);
      }
      for(int j=1;j<=maxM;j++){
        up(f[i+1][j],f[i+1][j-1]);
      }
      for(int j=0;j<=maxM;j++){
        f[i+1][j]=(ll)f[i+1][j]*g[j]%mod;
      }
    }
    int ans=0;
    for(int i=0;i<=maxM;i++){
      up(ans,f[n][i]);
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {25000, 50000, 100000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"YNN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 25000; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {30000, 60000, 90000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYN",
 "NYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 799969993; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {25000, 45000, 110000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "YYY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {25600, 51200, 102400}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYY",
 "YNY",
 "YYY",
 "YNN",
 "YYN",
 "NNY",
 "NYN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 867560805; verify_case(3, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	SRMIntermissionPhase ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
