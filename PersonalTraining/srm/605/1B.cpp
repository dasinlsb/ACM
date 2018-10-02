/*
和div2C差不多思路，f[i][S][j]表示从小到大当前考虑到i，前K个数未匹配/已匹配的状态S，再之前的数有j个未匹配的方案数
对于每个数i,枚举一下是新开一列使得i进入[未匹配]的状态还是插入S之前，如果是插入到S之前，当且仅当(S==0 && j==0)转移系数是2，其他情况都是1
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=105;
const int maxk=10;
const int mod=1000*1000*1000+7;
int f[maxn][1<<maxk][maxn];
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
class AlienAndSetDiv1{
	public:
	int getNumber(int N, int K){
		// $CARETPOSITION$
    memset(f,0,sizeof(f));
    f[0][0][0]=1;
    for(int i=0;i<2*N;i++){
      for(int S=0;S<1<<K;S++){
        for(int j=0;j<=i;j++){
          if(f[i][S][j]==0)continue;
          int _S=S<<1;
          int _j=j;
          if(_S>>K&1)_S^=(1<<K),_j++;
          if(_j)up(f[i+1][_S][_j-1],f[i][S][j]);
          up(f[i+1][_S|1][_j],(1+(S+j==0))*f[i][S][j]%mod);
        }
      }
    }
    return f[2*N][0][0];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 20; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 14; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 7; int Arg2 = 40; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	AlienAndSetDiv1 ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
