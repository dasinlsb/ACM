/*
好像有结论不过不会，可以直接dp
可以看成两行数交替取，直接用f[i][j]表示当前进行了i轮，牌堆顶为j，每次枚举每一行这一次取哪个数转移
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=105;

inline void up(int&x,int y){
  if(y>x)x=y;
}
int f[maxn][maxn];
class YetAnotherCardGame{
	public:
	int maxCards(vector <int> petr, vector <int> snuke){
		// $CARETPOSITION$
    int n=petr.size();
    vector<int>a[2];
    a[0]=petr;
    a[1]=snuke;
    memset(f,0,sizeof(f));
    for(int col=0;col<n;col++){
      for(int k=0;k<2;k++){
        int now=col*2+k;
        for(int high=0;high<=100;high++){
          up(f[now+1][high],f[now][high]);
          for(int i=0;i<n;i++)if(a[k][i]>high){
            up(f[now+1][a[k][i]],f[now][high]+1);
          }
        }
      }
    }
    int ans=0;
    for(int high=0;high<=100;high++){
      up(ans,f[2*n][high]);
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, maxCards(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, maxCards(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1, 4, 6, 7, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 7, 1, 5, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(2, Arg2, maxCards(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {19, 99, 86, 30, 98, 68, 73, 92, 37, 69, 93, 28, 58, 36, 86, 32, 46, 34, 71, 29}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28, 29, 22, 75, 78, 75, 39, 41, 5, 14, 100, 28, 51, 42, 9, 25, 12, 59, 98, 83}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 28; verify_case(3, Arg2, maxCards(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	YetAnotherCardGame ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
