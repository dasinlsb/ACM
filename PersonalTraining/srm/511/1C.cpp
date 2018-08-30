/*
连续块数>=2的区间肯定永远不会变色，那么任何序列都可以分割成若干段长度>=2的全黑，全白，和若干段长度>=1的黑白交替这样三种
可以考虑将原串倍长后枚举全黑和全白区间的起点st,同时起点颜色为lc
设f[i][use][rc][0/1]表示当前到第i个点，已加入的在T单位时间后有use个黑块，当前最后一位颜色为rc,当前的状态是全黑全白区间的起点(0)还是终点(1)
只要在i>n的时候，不从全黑全白区间起点转移出去即可
最后还有一些特殊情况要特判，比如整个序列黑白交替，整个序列全黑全白
时间复杂度O(n^4)
*/
//#line 2 "GameOfLifeDivOne.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=110;
int str[maxN];
int all[maxN][maxN][2];
int side[maxN][maxN][2];
int afterT[maxN][2];
ll f[maxN][maxN][2][2];

class GameOfLifeDivOne {
	public:  
	long long theCount(string init, int T, int K)  {  
		// $CARETPOSITION$  
    int n=SZ(init);
    for(int i=0;i<n;i++){
      str[i+1]=init[i]=='?'?-1:(init[i]-'0');
      str[i+1+n]=str[i+1];
    }
    for(int i=1;i<=2*n;i++){
      int k=0;
      for(int j=i;j<=2*n;j++){
        all[i][j][0]=(j==i?1:all[i][j-1][0])&(str[j]!=1);
        all[i][j][1]=(j==i?1:all[i][j-1][1])&(str[j]!=0);
        side[i][j][0]=(j==i?1:side[i][j-1][0])&(str[j]!=1-k);
        side[i][j][1]=(j==i?1:side[i][j-1][1])&(str[j]!=k);
        k^=1;
      }
    }
    for(int i=1;i<=n;i++){
      for(int j=0;j<2;j++){
        if(i%2){
          afterT[i][j]=j?max(0,i/2+1-T):min(i/2+T,i);
        }else{
          afterT[i][j]=i/2;
        }
        //printf("after %d %d : %d\n",i,j,afterT[i][j]);
      }
    }
    ll ans=0;
    //int find=0;
    for(int lc=0;lc<2;lc++){
      for(int st=1;st<=n;st++)if(all[st][st+1][lc]){
        //find=1;
        memset(f,0,sizeof(f));
        f[st][0][lc][0]=1;
        for(int i=st;i<st+n;i++){
          for(int use=0;use<=n;use++){
            for(int rc=0;rc<2;rc++){
              if(f[i][use][rc][0]&&i<=n){
                for(int j=i+1;j<st+n;j++){
                  if(!all[i][j][rc])break;
                  f[j][use+(rc?j-i+1:0)][rc][1]+=f[i][use][rc][0];
                }
              }
              if(f[i][use][rc][1]){
                f[i+1][use][rc^1][0]+=f[i][use][rc][1];
                for(int j=i+1;j<st+n;j++){
                  if(!side[i+1][j][rc^1])break;
                  f[j+1][use+afterT[j-i][rc^1]][rc^((j-i+1)&1)][0]+=f[i][use][rc][1];
                }
              }
            }
          }
        }
        //printf("chk %I64d\n",f[5][4][1]);
        ll res=0;
        for(int use=K;use<=n;use++){
          res+=f[st+n][use][lc][0];
        }
        ans+=res;
        //printf("st %d %lld\n",st,res);
      }
      //if(find==1)break;
    }
    if(all[1][n][0]&&K==0)ans++;
    if(all[1][n][1])ans++;
    //printf("mid %I64d\n",ans);
    if(n%2==0&&n/2>=K){
      if(side[1][n][0])ans++;
      if(side[1][n][1])ans++;
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "0?1"; int Arg1 = 1; int Arg2 = 1; long long Arg3 = 1LL; verify_case(0, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "?????????"; int Arg1 = 0; int Arg2 = 1; long long Arg3 = 511LL; verify_case(1, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "??0???????"; int Arg1 = 58; int Arg2 = 6; long long Arg3 = 151LL; verify_case(2, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "?????????1"; int Arg1 = 47; int Arg2 = 3; long long Arg3 = 453LL; verify_case(3, Arg3, theCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "?????????1???0???1??1??????0??????0??0????1???????"; int Arg1 = 12; int Arg2 = 40; long long Arg3 = 31577324313LL; verify_case(4, Arg3, theCount(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	GameOfLifeDivOne ___test;  
 	___test.run_test(-1);  
  //ll res=___test.theCount("????",0,1);
  //printf("%I64d\n",res);
	return 0;  
}  
// END CUT HERE  
