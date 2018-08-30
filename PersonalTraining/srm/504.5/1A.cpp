#line 2 "TheNumbersWithLuckyLastDigit.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
  
class TheNumbersWithLuckyLastDigit  
{  
        public:  
        int find(int n)  
        {  
                //$CARETPOSITION$  
          int i,j;
          int ans=300;
          for(i=0;i<=100;++i)for(j=0;j<=100;++j)if(i+j){
            if((i*4+j*7)%10==n%10&&i*4+j*7<=n)ans=min(ans,i+j);
          }
          ans=max(ans,1); 
          return ans==300?-1:ans;
        }  
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 99; int Arg1 = 4; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { int Arg0 = 11; int Arg1 = 2; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { int Arg0 = 13; int Arg1 = -1; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { int Arg0 = 1234567; int Arg1 = 1; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        TheNumbersWithLuckyLastDigit ___test;  
        ___test.run_test(-1);  
        return 0;  
}  
// END CUT HERE  
