/*
直接爆搜会在最后几个测试点TLE，乱搞又比较难写
比较正确的做法应该是状压DP.用f[S][x]表示点集S且根是x的答案
枚举一下S^(1<<x)的子集T来确定x的第一个儿子对应的子树，再枚举一下该子树的根就能转移了
时间复杂度O(3^n*n^2)
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=10;
int n;
double dis[maxn][maxn];
double f[1<<maxn][maxn];
double sq(int x){
  return 1.0*x*x;
}
class BearCharges{
	public:
	double minTime(vector <int> x, vector <int> y){
		// $CARETPOSITION$
    n=x.size();
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        dis[i][j]=sqrt(sq(x[i]-x[j])+sq(y[i]-y[j]));
      }
    }
    int ALL=(1<<n)-1;
    for(int curS=1;curS<1<<n;curS++){
      for(int x=0;x<n;x++){
        if(~curS>>x&1)continue;
        int sonS=curS^(1<<x);
        if(sonS==0){
          f[curS][x]=0.0;
          continue;
        }
        f[curS][x]=1e50;
        for(int firS=sonS;firS;firS=(firS-1)&sonS){
          for(int y=0;y<n;y++){
            if(~firS>>y&1)continue;
            double t1=f[firS][y]+dis[x][y];
            double t2=f[curS^firS][x]+(firS==sonS?0.0:dis[x][y]);
            f[curS][x]=min(f[curS][x],max(t1,t2));
          }
        }
      }
    }
    double ans=f[ALL][0];
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10, 11, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.414213562373095; verify_case(0, Arg2, minTime(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 1, -2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.0; verify_case(1, Arg2, minTime(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0,0,0,-1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,0,-1,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.0; verify_case(2, Arg2, minTime(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-2,0,0,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,-1,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 4.23606797749979; verify_case(3, Arg2, minTime(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-500000000, -300000000, -100000000, 200000000, 300000000, 400000000, 600000000, 900000000, 950000000, 1000000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0,0,0,0,0,0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.5E9; verify_case(4, Arg2, minTime(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	BearCharges ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
