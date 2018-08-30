/*
设f[n][m]为n行m列的答案，枚举一下行有多少等价类，列有多少等价类
f[n][m]=C^{n*m}-\sum_{0<=i<n,0<=j<m}S2(n,i)*S2(m,j)*f[i][j],S2是第二类stirling数
实际上某一维是可以单独直接算出来的，比如强制规定n=N
f[N][m]=(C^m)*(C^m-1)*(C^m-2)*...(C^m-N+1)-\sum_{0<=j<m}S2[m][j]*f[N][m]
时间复杂度O(n^2)
*/
//#line 2 "CountTables.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=4005;
const int mod=1000*1000*1000+7;
int pwC[maxN],S2[2][maxN],way[maxN];
class CountTables {
	public:  
	int howMany(int N, int M, int C)  {  
		// $CARETPOSITION$  
    pwC[0]=1;
    for(int i=1;i<=M;i++){
      pwC[i]=(ll)pwC[i-1]*C%mod;
    }
    S2[0][0]=1;
    way[0]=1;
    for(int j=1;j<=M;j++){
      way[j]=1;
      for(int i=1;i<=N;i++){
        way[j]=(ll)way[j]*(pwC[j]-i+1+mod)%mod;
      }
      for(int i=0;i<=j;i++){
        S2[j&1][i]=((i==j?0:(ll)i*S2[~j&1][i])+(i?S2[~j&1][i-1]:0))%mod;
        if(i!=j)way[j]=(way[j]-(ll)S2[j&1][i]*way[i]%mod+mod)%mod;
      }
    }
    return way[M];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 10; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 4000; int Arg3 = 4000; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 5; int Arg3 = 13740; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 4000; int Arg1 = 1; int Arg2 = 4000; int Arg3 = 593395757; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 1; int Arg3 = 0; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 4000; int Arg1 = 4000; int Arg2 = 4000; int Arg3 = 237003303; verify_case(5, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	CountTables ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
