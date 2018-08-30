/*
f[i][j][k]在结果图表中，当前已选了若干个，三个表的最大值分别为i,j,k
可以规定f[i][j][k]只能从f[i-1][j][k],f[i][j-1][k],f[i][j][k-1]转移过来
转移的时候只要判断i,j,k是否可以在之前选掉，可以选的话直接算更新答案，具体在哪里选不用考虑
对于i，假设i对应第t项数值a[t][0/1/2]，那么i可选当且仅当a[t][1]<=j&&a[t][2]<=k。j,k同理
时间复杂度O(n^3)
*/
//#line 2 "SlimeXSlimeRancher.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
int cut(vector<string>&s,ll a[]){
  int i,j,k=0;
  for(i=0;i<SZ(s);++i){
    for(j=0;j<SZ(s[i]);){
      for(;j<SZ(s[i])&&s[i][j]==' ';++j);
      if(j==SZ(s[i]))break;
      a[++k]=0;
      if(!j&&i&&s[i-1].back()!=' ')--k;
      for(;j<SZ(s[i])&&s[i][j]>='0'&&s[i][j]<='9';++j)a[k]=a[k]*10+s[i][j]-'0';
    }
  }
  //printf("test %d :",k);for(i=1;i<=k;++i)printf("%d ",a[i]);puts("");
  return k;
}
const int maxN=155;
const ll inf=(ll)1e12;
int n,D,id[3][maxN];
ll a[3][maxN],f[maxN][maxN][maxN];
bool cmp(int x,int y){return a[D][x]<a[D][y];}
void cmin(ll&x,ll y){if(y<x)x=y;}
class SlimeXSlimeRancher  
{  
  public:  
  long long train(vector <string> first_slime, vector <string> second_slime, vector <string> third_slime)  
  {  
    //$CARETPOSITION$  
    int i,j,k;
    n=cut(first_slime,a[0]);
    i=cut(second_slime,a[1]);
    j=cut(third_slime,a[2]);
    assert(n==i&&n==j);
    for(i=1;i<=n;++i)for(j=1;j<=n;++j)for(k=1;k<=n;++k)f[i][j][k]=inf;
    for(D=i=0;i<3;++i){
      for(j=1;j<=n;++j)id[i][j]=j;
      sort(id[i]+1,id[i]+1+n,cmp);++D;
    }
    for(i=1;i<=n;++i)for(j=1;j<=n;++j)for(k=1;k<=n;++k){
      int x=id[0][i],y=id[1][j],z=id[2][k];
      f[i][j][k]=inf;
      if(a[1][x]<=a[1][y]&&a[2][x]<=a[2][z]){
        cmin(f[i][j][k],f[i-1][j][k]+a[1][y]-a[1][x]+a[2][z]-a[2][x]);
      }else cmin(f[i][j][k],f[i-1][j][k]);
      if(a[0][y]<=a[0][x]&&a[2][y]<=a[2][z]){
        cmin(f[i][j][k],f[i][j-1][k]+a[0][x]-a[0][y]+a[2][z]-a[2][y]);
      }else cmin(f[i][j][k],f[i][j-1][k]);
      if(a[0][z]<=a[0][x]&&a[1][z]<=a[1][y]){
        cmin(f[i][j][k],f[i][j][k-1]+a[0][x]-a[0][z]+a[1][y]-a[1][z]);
      }else cmin(f[i][j][k],f[i][j][k-1]);
    }
    return f[n][n][n];
  }
      
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 6 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1 3 5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"5 4 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 5LL; verify_case(0, Arg3, train(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"3 2 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"6 5 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"9 8 7"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, train(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1 2", "3 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"12 3 ", "4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 ", "34"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 36LL; verify_case(2, Arg3, train(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"1 1 1 1000000000 1000000000 1000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1000000000 1000000000 1000000000 1 1 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 1 1 2 2 2"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 2999999997LL; verify_case(3, Arg3, train(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        SlimeXSlimeRancher ___test;  
        ___test.run_test(-1);  
        return 0;  
}  
// END CUT HERE  
