/*
暴力dp
*/
//#line 2 "TheAlmostLuckyNumbersDivOne.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
  
ll calc(ll num){
  static int a[20];
  static ll f[20][2][2][2];
  int n=0;
  for(ll t=num;t;t/=10){
    a[++n]=int(t%10);
  }
  reverse(a+1,a+1+n);
  for(int i=0;i<=n;++i){
    for(int j=0;j<2;++j){
      for(int k=0;k<2;++k){
        for(int t=0;t<2;++t){
          f[i][j][k][t]=0;
        }
      }
    }
  }
  f[0][0][0][1]=1;
  ll res=0;
  for(int i=0;i<=n;++i){
    for(int plus=0;plus<2;++plus){
      for(int cnt=0;cnt<2;++cnt){
        if(i==n){res+=f[n][plus][cnt][0]+f[n][plus][cnt][1];continue;}
        for(int nxt=0;nxt<10;++nxt){
          int _cnt=(nxt!=4&&nxt!=7)+cnt;
          int _plus=plus|nxt!=0;
          if(!_plus)_cnt--;
          if(_cnt>=2)continue;
          f[i+1][_plus][_cnt][0]+=f[i][plus][cnt][0];
          if(nxt<=a[i+1]){
            f[i+1][_plus][_cnt][nxt==a[i+1]]+=f[i][plus][cnt][1];
          }
        }
      }
    }
  }
  //printf("%lld %lld\n",num,res);
  return res;
}
class TheAlmostLuckyNumbersDivOne {
	public:  
	long long find(long long a, long long b)  {  
		// $CARETPOSITION$  
    int i,j;
    return calc(b)-calc(a-1);
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 4LL; long long Arg1 = 7LL; long long Arg2 = 4LL; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 8LL; long long Arg1 = 19LL; long long Arg2 = 4LL; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 28LL; long long Arg1 = 33LL; long long Arg2 = 0LL; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 12345678900LL; long long Arg1 = 98765432100LL; long long Arg2 = 91136LL; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	TheAlmostLuckyNumbersDivOne ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
