/*
限制相当于每一个二进制位要么全0，要么最多有一个数字能放1
f[i][S]表示已经从高到低dp到二进制第i位，当前所有数的[是否等于上界]的情况是S
枚举下一位是否放1以及在哪个放1转移
*/
//#line 2 "YetAnotherORProblem.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int mod=((int)1e9)+9;
int f[66][1<<10];
inline void add(int&x,int y){
  x=x+y<mod?x+y:x+y-mod;
}
class YetAnotherORProblem {
	public:  
	int countSequences(vector<long long> R)  {  
		// $CARETPOSITION$  
    int i,j;
    int n=SZ(R);
    for(i=0;i<=61;++i)for(j=0;j<1<<10;++j)f[i][j]=0;
    f[61][(1<<n)-1]=1;
    for(int bit=60;~bit;--bit){
      for(int S=0;S<1<<n;++S)if(f[bit+1][S]){
        int T=S;
        for(i=0;i<n;++i)if(((1<<i)&S)&&((1LL<<bit)&R[i]))T^=(1<<i);
        add(f[bit][T],f[bit+1][S]);
        for(i=0;i<n;++i){
          if(((1<<i)&S)&&!((1LL<<bit)&R[i]))continue;
          int _T=T;
          if(((1<<i)&S)&&((1LL<<bit)&R[i]))_T|=(1<<i);
          add(f[bit][_T],f[bit+1][S]);
          //int _T=T|(1<<i);     
          //add(f[bit][_T],f[bit+1][S]);
        }
      }
    }
    int ans=0;
    for(i=0;i<1<<n;++i)add(ans,f[0][i]);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {3,5}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(0, Arg1, countSequences(Arg0)); }
	void test_case_1() { long Arr0[] = {3,3,3}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(1, Arg1, countSequences(Arg0)); }
	void test_case_2() { long Arr0[] = {1,128}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 194; verify_case(2, Arg1, countSequences(Arg0)); }
	void test_case_3() { long Arr0[] = {26,74,25,30}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8409; verify_case(3, Arg1, countSequences(Arg0)); }
	void test_case_4() { long Arr0[] = {1000000000,1000000000}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 420352509; verify_case(4, Arg1, countSequences(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	YetAnotherORProblem ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
