/*
首先可以考虑面值大的硬币和面值小的硬币各自在哪些地方是非用不可的
对于面值大的硬币，这个面值本身可以作为一种方案，而且必定可以由面值小的硬币组合得到
但是之所以在组合的时候还要考虑面值小的硬币，是因为仅仅用大面值硬币不一定能恰好组合成coins_sum，这时只能用面值小的硬币补上
也就是说，在能用大面值的时候就要尽量用，这种策略可以唯一地将coins_sum划分成若干段
剩下的问题如何就是将每一段组合起来，因为答案是计算集合数，所以可以强制规定从小段到大段的value是升序排列的
可以考虑这样一个dp,f[k][i][l][r]表示长为k*value[i]的一段，最左端是value[l],最右端是value[r]的方案数
f[k+1][i][l][r]=\sum_{}f[k][i][l][m1]*f[1][i][[m2][r]
可以发现这个转移和矩阵十分类似，可以考虑稍微修改f的定义，最右端不超过value[r]
那么转移就可以写成 f[k+1][i][l][r]=\sum_{}f[k][i][m]*f[1][i][m][r]
且对于不同的面值有这样的转移f[1][i+1][l][r]=\sum{}f[value[i+1]/value[i]][i][l][r]+[l>=i+1]
*/
#include<bits/stdc++.h>
using namespace std;  
const int mod=1000003;
const int maxn=45;
inline void add(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
void mul(int a[maxn][maxn],int b[maxn][maxn],int n){
  static int c[maxn][maxn];
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      c[i][j]=0;
      for(int k=0;k<n;k++){
        add(c[i][j],1LL*a[i][k]*b[k][j]%mod);
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      a[i][j]=c[i][j];
    }
  }
}
void set1(int a[maxn][maxn],int n){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      a[i][j]=i==j?1:0;
    }
  }
}
void Pow(int a[maxn][maxn],int b[maxn][maxn],int n,long long k){
  static int c[maxn][maxn];
  //printf("pow %d %lld\n",n,k);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      c[i][j]=a[i][j];
    }
  }
  set1(b,n);
  for(;k;k>>=1){
    if(k&1LL){
      mul(b,c,n);
    }
    mul(c,c,n);
  }
}
long long cnt[maxn];
int G[maxn][maxn][maxn];
int g[maxn][maxn],f[maxn][maxn];
void print(int a[maxn][maxn],int n){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      printf("%d ",a[i][j]);
    }
    puts("");
  }
  puts("");
}
class P8XCoinChange{
	public:
	int solve(long long coins_sum, vector<long long> values){
		// $CARETPOSITION$
    int n=values.size();
    memset(G,0,sizeof(G));
    for(int i=0;i<n;i++){
      for(int r=i;r<n;r++){
        add(G[i][i][r],1);
      }
      if(i==n-1)break;
      Pow(G[i],G[i+1],n,values[i+1]/values[i]);
    }
    for(int i=n-1;i>=0;i--){
      cnt[i]=coins_sum/values[i];
      coins_sum%=values[i];
    }
    set1(f,n);
    for(int i=0;i<n;i++){
      Pow(G[i],g,n,cnt[i]);
      mul(f,g,n);
    }
    int ans=0;
    for(int i=0;i<n;i++)add(ans,f[i][n-1]);
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 4LL; long Arr1[] = {1, 3}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 4LL; long Arr1[] = {1, 2, 4}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 3LL; long Arr1[] = {1, 5}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 11LL; long Arr1[] = {1, 2, 6}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(3, Arg2, solve(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 1000000000000000000LL; long long Arr1[] = {1, 1000000000, 1000000000000000000LL}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 997005; verify_case(4, Arg2, solve(Arg0, Arg1)); }
	void test_case_5() { long long Arg0 = 961320341778342848LL; long long Arr1[] = {1,2,10,30,150,300,1200,2400,4800,14400,
28800,57600,288000,576000,2304000,9216000,
18432000,73728000,221184000,663552000,
1327104000LL,5308416000LL,31850496000LL,
95551488000LL,191102976000LL,764411904000LL,
1528823808000LL,6115295232000LL,18345885696000LL,
36691771392000LL,73383542784000LL,220150628352000LL,
440301256704000LL,1320903770112000LL,3962711310336000LL,
15850845241344000LL,31701690482688000LL,95105071448064000LL,
475525357240320000LL,951050714480640000LL}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 245264; verify_case(5, Arg2, solve(Arg0, Arg1)); }
	void test_case_6() { long long Arg0 = 1000000000000000000LL; long long Arr1[] = {1, 2}; vector<long long> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 499989; verify_case(6, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	P8XCoinChange ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
