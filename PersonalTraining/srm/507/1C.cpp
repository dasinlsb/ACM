/*
一种直接的想法是先按行再按列dp,具体的状态如果设为f[r][g][b]表示当前三种颜色分别已用r,g,b个，转移的时候要三维卷积时间接受不了
实际上这些方块的颜色都可以最后确定，可以考虑先dp整体的形态
f[i][j][k]表示NS方向，前i列，最大高度j，总共用了k个方块
WE方向可以设g[i][j][k]表示前i列，每一列最大高度加起来为j，总共用了k个方块
染色的时候枚举可以看到多少个方块以及染哪种颜色
时间复杂度O(n^5)
*/
//#line 2 "CubeBuilding.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int mod=((int)1e9)+7;
int c[80][80],f[30][80][80],g[30][80][80];
inline void add(int&x,int y){
  x=x+y<mod?x+y:x+y-mod;
}
int cal(int x,int y,int z){
  if(x-y<0)return 0;
  return (ll)c[x][y]*c[x-y][z]%mod;
}
void clear(){
  for(int i=0;i<30;++i){
    for(int j=0;j<80;++j){
      for(int k=0;k<80;++k){
        f[i][j][k]=0;
        g[i][j][k]=0;
      }
    }
  }
}
class CubeBuilding {
	public:  
	int getCount(int R, int G, int B, int N)  {  
		// $CARETPOSITION$  
    int i,j;
    clear();
    int S=R+G+B;
    for(c[0][0]=i=1;i<=S;++i){
      for(c[i][0]=j=1;j<=i;++j){
        c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
      }
    }
    f[0][0][0]=1;
    for(int row=0;row<N;++row){
      for(int sum=0;sum<=S;++sum){
        for(int high=0;high<=sum;++high){
          for(int nxt=0;nxt+sum<=S;++nxt){
            add(f[row+1][sum+nxt][max(high,nxt)],f[row][sum][high]);
          }
        }
      }
    }
    // for(int sum=0;sum<=S;++sum){
    //   for(int high=0;high<=sum;++high){
    //     printf("f %d %d : %d\n",sum,high,f[N][sum][high]);
    //   }
    // }
    g[0][0][0]=1;
    for(int col=0;col<N;++col){
      for(int ss=0;ss<=S;++ss){
        for(int sh=0;sh<=ss;++sh){
          for(int nxts=0;nxts+ss<=S;++nxts){
            for(int nxth=0;nxth<=nxts;++nxth){
              add(g[col+1][ss+nxts][sh+nxth],(ll)g[col][ss][sh]*f[N][nxts][nxth]%mod);
            }
          }
        }
      }
    }
    // for(int sum=0;sum<=S;++sum){
    //   for(int high=0;high<=sum;++high){
    //     printf("g %d %d : %d\n",sum,high,g[N][sum][high]);
    //   }
    // }
    int ans=0;
    for(int sh=1;sh<=S;++sh){
      int mul=0;
      add(mul,cal(S-sh,R,G));
      add(mul,cal(S-sh,R,B));
      add(mul,cal(S-sh,G,B));
      //printf("mul %d : %d\n",sh,mul);
      add(ans,(ll)mul*g[N][S][sh]%mod);
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 1; int Arg3 = 2; int Arg4 = 4; verify_case(0, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 2; int Arg3 = 1; int Arg4 = 0; verify_case(1, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 3; int Arg4 = 162; verify_case(2, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 10; int Arg3 = 12; int Arg4 = 372185933; verify_case(3, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	CubeBuilding ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
