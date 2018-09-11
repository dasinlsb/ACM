/*
直接暴力dp的话可以考虑f[i][j][k]表示已经考虑前i个物品，还需要j个p1,k个p2来弥补之前产生的空位
但是这样做不光状态十分巨大，而且难以转移，因为最后要求完美匹配时的答案，实际上每个物品不一定要用完，
可以考虑二分答案，判断可行性，可以考虑dp，f[i][j]表示前i个物品，p1一共用了j次的情况下，p2最多用几次，显然合法当且仅当f[n][k]>=k,k为二分出来的ans/(P1+p2)
考虑枚举下一个物品用t次p1,那么显然剩下都要给p2,但是可能给多了，要对k-t取min,因为每次选出的物品必须不同
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
inline void up(int&x,int y){
  if(x==-1||x<y)x=y;
}
int f[maxn][maxn*40];
int calc(vector<int>&c,int p1,int p2,int val){
  memset(f,-1,sizeof(f));
  f[0][0]=0;
  int n=c.size();
  for(int i=0;i<n;i++){
    for(int use=0;use<=40*i;use++)if(~f[i][use]){
      for(int j=0;j*p1<=c[i];j++){
        int k=(c[i]-j*p1)/p2;
        k=min(k,val-j);
        up(f[i+1][use+j],f[i][use]+k);
      }
    }
  }
  return f[n][val]>=val;
}
class ColorfulCookie{
	public:
	int getMaximum(vector <int> cookies, int P1, int P2){
		// $CARETPOSITION$
    int sum=0;
    for(int i=0;i<cookies.size();i++){
      sum+=cookies[i];
    }
    int L=1,R=sum/(P1+P2);
    for(;L<=R;){
      int mid=(L+R)/2;
      if(calc(cookies,P1,P2,mid))L=mid+1;
      else R=mid-1;
    }
    return R*(P1+P2);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 50; int Arg3 = 200; verify_case(0, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {50, 250, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 100; int Arg3 = 300; verify_case(1, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 200; int Arg3 = 0; verify_case(2, Arg3, getMaximum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {123, 456, 789, 555}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; int Arg2 = 158; int Arg3 = 1728; verify_case(3, Arg3, getMaximum(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	ColorfulCookie ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
