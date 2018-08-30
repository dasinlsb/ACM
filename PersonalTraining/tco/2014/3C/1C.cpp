/*
问题相当于求n个点的完全图有多少个带标号生成树有t条原树没有的边,0<=t<=k
考虑矩阵树定理，答案中每个1由n-1个1相乘得到，如果将原图中存在的边边权设1，不存在的边的边权设x
那么答案多项式中的x^r项的系数显然就是t=r时的答案
拉格朗日插值插到行列式里算即可
*/
//#line 2 "TreeDistance.cpp"  
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
const int mod=1000000007;
int pw(int x,int y){
  int t=1;
  for(;y;y>>=1){
    if(y&1)t=(ll)t*x%mod;
    x=(ll)x*x%mod;
  }
  return t;
}
int inv(int x){
  if(!x)return 1;
  if(x<0)x+=mod;
  return pw(x,mod-2);
}
int det(int a[][maxN],int n){
  int i,j,k;
  int sgn=1;
  for(i=1;i<=n;++i){
    for(k=j=i;j<=n;++j)if(a[j][i]>a[k][i])k=j;
    if(a[k][i]==0)return 0;
    if(k!=i){
      sgn^=1;
      for(j=1;j<=n;++j)swap(a[i][j],a[k][j]);
    }
    for(j=i+1;j<=n;++j){
      int v=(ll)inv(a[i][i])*(mod-a[j][i])%mod;
      for(k=i;k<=n;++k)a[j][k]=(a[j][k]+(ll)a[i][k]*v)%mod;
    }
  }
  int res=1;
  for(i=1;i<=n;++i)res=(ll)res*a[i][i]%mod;
  return sgn?res:mod-res;
}
int g[maxN][maxN],a[maxN][maxN],b[maxN],c[maxN],Y[maxN];
class TreeDistance {
	public:  
	int countTrees(vector <int> p, int K)  {  
		// $CARETPOSITION$  
    int i,j,k;
    int n=SZ(p)+1;
    for(i=1;i<=n;++i){
      for(j=1;j<=n;++j){
        g[i][j]=0;
      }
    }
    for(i=0;i<n-1;++i){
      g[i+2][p[i]+1]=1;
      g[p[i]+1][i+2]=1;
    }
    for(int x=1;x<=n;++x){
      for(i=1;i<=n;++i){
        a[i][i]=0;
        for(j=1;j<=n;++j)if(i!=j){
          if(g[i][j]){
            a[i][i]++;
            a[i][j]=mod-1;
          }else{
            a[i][i]+=x;
            a[i][j]=mod-x;
          }
        }
      }
      Y[x]=det(a,n-1);
      //printf("x %d %d\n",x,Y[x]);
    }
    fill(c,c+n,0);
    for(i=1;i<=n;++i){
      fill(b,b+n,0);
      b[0]=1;
      int mul=1;
      for(j=1;j<=n;++j)if(i!=j){
        for(k=n-2;~k;--k){
          b[k+1]=(b[k+1]+b[k])%mod;
          b[k]=(ll)b[k]*(mod-j)%mod;
        }
        mul=(ll)mul*inv(i-j)%mod;
      }
      mul=(ll)mul*Y[i]%mod;
      for(j=0;j<n;++j){
        b[j]=(ll)b[j]*mul%mod;
        c[j]=(c[j]+b[j])%mod;
      }
    }
    //for(i=0;i<n;++i)printf("%d ",c[i]);puts("");
    int ans=0;
    for(i=0;i<=min(n-1,K);++i)ans=(ans+c[i])%mod;
    return ans;
	}  

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; verify_case(0, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 1, 2, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 28; verify_case(1, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 1, 2, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 222; verify_case(2, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 1, 2, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; int Arg2 = 1296; verify_case(3, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0, 1, 2, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; verify_case(4, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0, 1, 0, 3, 3, 4, 4, 5, 6, 8, 3, 1, 12, 12, 13, 10, 4, 8, 13, 17, 2, 10, 12, 20, 2, 14, 17, 19, 15, 0, 22, 15, 3, 8, 3, 17, 27, 2, 12, 38, 37, 4, 40, 29, 9, 22, 43, 32, 37}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7124; verify_case(5, Arg2, countTrees(Arg0, Arg1)); }
	void test_case_6() { int Arr0[] = {0, 0, 0, 0, 2, 3, 1, 2, 3, 7, 3, 10, 8, 8, 9, 1, 2, 0, 7, 17, 19, 2, 17, 2, 0,
6, 4, 9, 12, 14, 8, 12, 10, 30, 20, 30, 8, 36, 28, 22, 8, 2, 2, 13, 26, 14, 46, 6, 25}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 310259667; verify_case(6, Arg2, countTrees(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	TreeDistance ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
