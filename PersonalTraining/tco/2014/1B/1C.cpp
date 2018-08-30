/*
设f[x][i]表示用了i次机会恰好走到x(没有向x的子节点走)的概率
p_x为从根走到x的概率
对于v of son_x ,f[v][j]=f[x][i]*(1-p)^{j-i-1}*p
ans=\sum_{x}f[x][K]
*/
//#line 2 "EagleInZoo.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=105;
int n,maxk,fa[maxN];
double f[maxN][maxN];
VI g[maxN];
void adde(int x,int y){
  //printf("add e%d %d\n",x,y);
  g[x].pb(y);
  g[y].pb(x);
}
void dfs(int x,double p){
  int son=0;
  for(int i=0;i<SZ(g[x]);++i)if(g[x][i]!=fa[x])++son;
  for(int i=0;i<SZ(g[x]);++i)if(g[x][i]!=fa[x]){
    int v=g[x][i];
    fa[v]=x;
    p/=son;
    for(int j=1;j<=maxk;++j){
      double tp=p;
      f[v][j]=0;
      for(int k=j-1;k;--k){
        f[v][j]+=f[x][k]*tp;
        tp*=(1.0-p);
      }
    }
    dfs(v,p);
    p*=son;
  }
}
class EagleInZoo {
	public:  
	double calc(vector <int> parent, int K)  {  
		// $CARETPOSITION$  
    int i,j;
    n=SZ(parent)+1;
    maxk=K;
    for(i=0;i<n;++i)g[i].clear();
    for(i=1;i<n;++i){
      adde(parent[i-1],i);
    }
    f[0][1]=1.0;
    dfs(0,1.0);
    double ans=0;
    for(i=0;i<n;++i){
      ans+=f[i][maxk];
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 1.0; verify_case(0, Arg2, calc(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arg2 = 0.5; verify_case(1, Arg2, calc(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0,1,0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 0.75; verify_case(2, Arg2, calc(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0,0,1,1,2,4,4,4,5,5,6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; double Arg2 = 0.14595168754091617; verify_case(3, Arg2, calc(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,1,2,3,2,1,1,7,0,9,10,11,12,13,14,15,16,17,18,14,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; double Arg2 = 0.3272154791654077; verify_case(4, Arg2, calc(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0,1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; double Arg2 = 0.0; verify_case(5, Arg2, calc(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	EagleInZoo ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
