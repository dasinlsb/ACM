/*
差分之后变成单点-1，下一位+1，要求最后获得一个单调不降序列
有个贪心策略是从左到右扫，每一次都用尽量小的代价去保证前缀的单调性
具体地比如说现在扫到的右端点为r，那么不断去找是否存在i<=r使得a[i-1]>a[i]
如果有，那么往前调整,经过一次这样的调整后整个序列最前面的那个a[j-1]>a[j]的位置肯定会以最小的代价满足条件，也就是重复若干次之后必定会终止
*/
//#line 2 "ConvexSequence.cpp"  
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
ll b[maxN];
class ConvexSequence {
	public:  
	long long getMinimum(vector <int> a)  {  
		// $CARETPOSITION$  
    int n=SZ(a);
    for(int i=1;i<n;i++){
      b[i]=a[i]-a[i-1];
    }
    ll ans=0;
    for(int i=2;i<n;i++){
      for(;;){
        int j;
        for(j=i;j>1&&b[j-1]<=b[j];j--);
        if(j==1)break;
        for(;j>1&&b[j-1]>b[j];j--){
          ll d=(b[j-1]-b[j]+1)/2;
          b[j]+=d;
          b[j-1]-=d;
          ans+=d;
        }
      }
    }
    //for(int i=2;i<n;i++)if(b[i]<b[i-1])puts("shit");
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {6,5,1,5,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 7LL; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { int Arr0[] = {3,0,1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { int Arr0[] = {1,1,1,0,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { int Arr0[] = {854159326, 317144183, 781399725, 287076509, 894967145, 882577367, 174517516, 134415519,
 274494874, 709819883, 59717133, 732212854, 40551288, 232526958, 811785438, 930853743,
 946882902, 321325300, 397702677, 376192501, 599310562, 889156198, 135776890, 882710939,
 823196361, 681959076, 318666702, 94469186, 536320456, 116468376, 530320850, 436708006,
 903344748, 659080120, 774722507, 967315412, 566063635, 43970906, 497687103, 781266213,
 876086123, 366960001, 587364849, 191948103, 172568553, 539762057, 83507466, 71569625,
 686305822, 663789601}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 20178337330LL; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { int Arr0[] = {5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(4, Arg1, getMinimum(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	ConvexSequence ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
