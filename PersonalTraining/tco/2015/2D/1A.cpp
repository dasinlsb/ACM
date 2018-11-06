/*
如果直接枚举支点，当支点两边质量都为0时可能算重，可以特判解决....
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=2505;
int t,q[maxn];
int cnt[maxn*maxn];
class BalancedSubstrings{
	public:
	int countSubstrings(string s){
		// $CARETPOSITION$
    int n=s.size();
    int ans=0;
    for(int mid=0;mid<n;mid++){
      int val=0;
      for(int i=mid;i>=0;i--){
        val+=(mid-i)*(s[i]-'0');
        q[++t]=val;
        cnt[val]++;
      }
      val=0;
      int res=0;
      for(int i=mid;i<n;i++){
        val+=(i-mid)*(s[i]-'0');
        if(s[mid]=='1' || val)res+=cnt[val];
      }
      ans+=res;
      // printf("res %d %d\n",mid,res);
      for(;t;t--)cnt[q[t]]--;
    }
    for(int i=0;i<n;i++)if(s[i]=='0'){
      int j=i;
      for(;j<n && s[j]=='0';j++);
      ans+=(j-i+1)*(j-i)/2;
      i=j-1;
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "011"; int Arg1 = 4; verify_case(0, Arg1, countSubstrings(Arg0)); }
	void test_case_1() { string Arg0 = "10111"; int Arg1 = 10; verify_case(1, Arg1, countSubstrings(Arg0)); }
	void test_case_2() { string Arg0 = "00000"; int Arg1 = 15; verify_case(2, Arg1, countSubstrings(Arg0)); }
	void test_case_3() { string Arg0 = "0000001000000"; int Arg1 = 91; verify_case(3, Arg1, countSubstrings(Arg0)); }
	void test_case_4() { string Arg0 = "100110001001"; int Arg1 = 49; verify_case(4, Arg1, countSubstrings(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	BalancedSubstrings ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
