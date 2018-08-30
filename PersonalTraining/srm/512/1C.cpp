/*
原问题相当于给定一个单调不降的序列b，求有多少种序列a满足将其排序之后a_i<=b_i
如果考虑无序地填充要涉及状压无法接受，考虑有序地填入a_i
有个直接的dp是设状态f[i][j]表示前i个，最大不超过j
f[i][j]=\sum_{S[k+1]>=j&&k<=i}f[k][j-1]*comb[i][k]
但是由于值域很大仍然无法接受
由于n很小，而且(a_i,a_{i+1}]这个区间里的所有数能填充的位置的限制是完全相同的
可以考虑用f[i][j]表示前i个，最大不超过(a_{j-1},a_j],转移只要在i-k个空位任意填充区间内的数即可
时间复杂度O(n^3)
*/
//#line 2 "PickAndDelete.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=205;
const int mod=1000*1000*1000+7;
int decode(vector<string>&S,int a[]){
  string s="";
  for(int i=0;i<SZ(S);i++)s+=S[i];
  int n=0;
  for(int i=0;i<SZ(s);i++){
    a[++n]=0;
    for(;i<SZ(s)&&s[i]>='0'&&s[i]<='9';i++){
      a[n]=a[n]*10+s[i]-'0';
    }
  }
  return n;
}
int c[maxN][maxN];
int init[maxN],val[maxN];
int f[maxN][maxN];
class PickAndDelete {
	public:  
	int count(vector <string> S)  {  
		// $CARETPOSITION$  
    int n=decode(S,init);
    c[0][0]=1;
    for(int i=1;i<=n;i++){
      c[i][0]=1;
      for(int j=1;j<=i;j++){
        c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
      }
    }
    sort(init+1,init+1+n);
    for(int i=1;i<=n;i++)val[i]=init[i];
    int dn=1;
    for(int i=2;i<=n;i++){
      if(val[i]!=val[i-1]){
        val[++dn]=val[i];
      }
    }
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=1;i<=dn;i++){
      for(int j=1;j<=n;j++){
        int mul=(val[i]-val[i-1]);
        f[i][j]=f[i-1][j];
        for(int k=j-1;k>=0&&init[k+1]>=val[i];k--){
          f[i][j]=(f[i][j]+(ll)f[i-1][k]*c[j][k]%mod*mul)%mod;
          mul=(ll)mul*(val[i]-val[i-1])%mod;
        }
      }
    }
    return f[dn][n];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {"2 2 2 2 2 2 2 2 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 512; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"5", " 1 ", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 34; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"3 ", "14159 265", "3589 7", " 932"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 353127147; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	PickAndDelete ___test;  
 	___test.run_test(-1);  
   //vector<string>a;
   //a.pb("1 1 2 2");
   //int res=___test.count(a);
   //printf("self %d\n",res);
	return 0;  
}  
// END CUT HERE  
