/*
模拟一下样例发现很像差分约束，暴力的做法可能是1,2,3...这样一个一个点加进来，看一下有没有环
这样直接暴力是O(ans^2)，答案显然不超过50*1000，但这个上界如果跑满的话是跑不过O(ans^2)的
二分答案可以通过这个上界，但实际上更严格的上界是1000*2，这个暴力是可以过的...
*/
//#line 2 "LongestSequence.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=60005;
int vis[maxN];
int dfs(int x,int lim,vector<int>&c){
  vis[x]=1;
  for(int i=0;i<SZ(c);i++){
    if(x+c[i]<=lim&&x+c[i]>=0&&vis[x+c[i]]!=2){
      if(vis[x+c[i]]==1||dfs(x+c[i],lim,c))return 1;
    }
  }
  return vis[x]=2,0;
}
class LongestSequence {
	public:  
	int maxLength(vector <int> C)  {  
		// $CARETPOSITION$  
    int l=1,r=60000;
    for(;l<=r;){
      int mid=(l+r)/2;
      int cir=0;
      memset(vis,0,sizeof(vis));
      for(int i=mid;i>=0;i--)if(!vis[i]){
        if(dfs(i,mid,C)){cir=1;break;}
      }
      if(cir)r=mid-1;
      else l=mid+1;
    }
    return r>55555?-1:r;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, maxLength(Arg0)); }
	void test_case_1() { int Arr0[] = {524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, maxLength(Arg0)); }
	void test_case_2() { int Arr0[] = {1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, maxLength(Arg0)); }
	void test_case_3() { int Arr0[] = {11,-7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(3, Arg1, maxLength(Arg0)); }
	void test_case_4() { int Arr0[] = {-227,690,590,-524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 713; verify_case(4, Arg1, maxLength(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	LongestSequence ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
