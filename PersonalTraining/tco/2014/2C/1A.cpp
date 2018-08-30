/*
因为优先要字典序最小，从前往后考虑左端点l,右端点r要尽可能小,如果S[r]<S[l]那么就记录所有这样的r以及对应反转后的串
不过[l,r]可能还可以向两端延伸，都记录之后最多n个长度为n的串以及二元组，扫一遍取最小即可
如果对于所有左端点l都找不到r使得S[r]<S[l]，那么翻转必定不能使字典序比原串更小，取(x,y)=(0,0)即可
*/
//#line 2 "SubstringReversal.cpp"  
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
string f[maxN];
pii seg[maxN];
class SubstringReversal {
	public:  
	vector <int> solve(string S)  {  
		// $CARETPOSITION$  
    int n=SZ(S);
    int tot=0;
    VI ans;
    for(int l=0;l<n;l++){
      for(int r=l+1;r<n;r++){
        if(S[r]<S[l]){
          f[++tot]=S.substr(0,l);
          for(int i=l;i<=r;++i)f[tot].append(1,S[r-(i-l)]);
          f[tot]+=S.substr(r+1,n-1-r);
          seg[tot]=pii(l,r);
          for(;seg[tot].fi-1>=0&&seg[tot].se+1<=n-1&&S[seg[tot].fi-1]==S[seg[tot].se+1];){
            seg[tot].fi--;seg[tot].se++;
          }
        }
      }
      if(tot){
        int p=1;
        for(int i=2;i<=tot;i++){
          if(f[i]<f[p]||f[i]==f[p]&&seg[i]<seg[p]){
            p=i;
          }
        }
        ans.pb(seg[p].fi);
        ans.pb(seg[p].se);
        return ans;
      }
    }
    ans.pb(0);
    ans.pb(0);
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "abdc"; int Arr1[] = {2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arg0 = "aabbcc"; int Arr1[] = {0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arg0 = "misof"; int Arr1[] = {0, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arg0 = "ivan"; int Arr1[] = {0, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { string Arg0 = "thisseemstobeaneasyproblem"; int Arr1[] = {0, 13 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, solve(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	SubstringReversal ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
