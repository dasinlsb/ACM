#include<bits/stdc++.h>
using namespace std;  

const int maxn=305;
double prob[maxn][2];
double f[maxn][maxn][2];
class Bitwisdom{
	public:
	double expectedActions(vector <int> p){
		// $CARETPOSITION$
    int n=p.size();
    for(int i=0;i<n;i++){
      prob[i][1]=0.01*p[i];
      prob[i][0]=1.0-0.01*p[i];
    }
    for(int i=1;i<=n;i++){
      for(int j=1;j<=i;j++){
        for(int last=0;last<2;last++){
          f[i][j][last]=0.0;
        }
      }
    }
    f[1][1][0]=prob[0][0];
    f[1][1][1]=prob[0][1];
    double ans=0.0;
    for(int i=1;i<=n;i++){
      for(int j=1;j<=i;j++){
        for(int last=0;last<2;last++){
          if(i==n){
            ans+=f[i][j][last]*(j-1);
            continue;
          }
          for(int nxt=0;nxt<2;nxt++){
            f[i+1][j+(nxt!=last)][nxt]+=prob[i][nxt]*f[i][j][last];
          }
        }
      }
    }

    double tmp=1.0;
    for(int i=0;i<n;i++)tmp*=prob[i][1];
    ans+=tmp;
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(0, Arg1, expectedActions(Arg0)); }
	void test_case_1() { int Arr0[] = {50, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.75; verify_case(1, Arg1, expectedActions(Arg0)); }
	void test_case_2() { int Arr0[] = {0, 40, 50, 60}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.4; verify_case(2, Arg1, expectedActions(Arg0)); }
	void test_case_3() { int Arr0[] = {37, 63, 23, 94, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.6820475464; verify_case(3, Arg1, expectedActions(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	Bitwisdom ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
