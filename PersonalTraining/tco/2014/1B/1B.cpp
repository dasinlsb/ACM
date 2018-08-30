/*
由于要在二维平面上画线，难以直接贪心得到答案，可以考虑2^(n-1)枚举其中一维，假设枚举水平分割线
现在方格被分割成若干水平的横条，每个横条的竖直方向首先要保证不能同时出现黑白，否则无解
在相邻的黑白块之间形成一段区间，要求最后至少有一条竖线在这个区间中，把所有区间拿出来按左端点排序后贪心即可
时间复杂度O(2^(n-1)*nmlog(nm))
*/
//#line 2 "WolvesAndSheep.cpp"  
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
const int inf=maxN*2;
int n,m,f[maxN],g[maxN][maxN];
pii que[maxN*maxN];
int change(char c){
  if(c=='W')return 2;
  if(c=='S')return 1;
  return 0;
}
int calc(int S){
  int i,j,k;
  int tot=0;
  int res=0;S|=(1<<n-1);
  for(i=0;i<m;++i)f[i]=0;
  for(i=0;i<n;++i){
    for(j=0;j<m;++j){
      f[j]|=g[i][j];
      if(f[j]==3)return inf;
    }
    if((1<<i)&S){
      if(i!=n-1)res++;
      for(j=0;j<m-1;++j)if(f[j]!=f[j+1]){
        for(k=j+1;k<m&&f[k]==0;++k);--k;
        if(k+1<m&&f[j]+f[k+1]==3)que[++tot]=pii(j,k);
        //if(S==12)printf("add %d : %d %d\n",i,j,k);
        j=k;
      }
      for(j=0;j<m;++j){
        f[j]=0;
      }
    }
  }
  //if(S==12)printf("pre %d\n",res);
  if(!tot)return res;
  sort(que+1,que+1+tot);
  int R=-1;
  for(i=1;i<=tot;++i){
    //printf("seg %d %d\n",que[i].fi,que[i].se);
    if(R==-1||que[i].fi>R){
      ++res;R=que[i].se;
    }else R=min(R,que[i].se);
  }
  //if(S==12)printf("S %d %d\n",S,res);
  return res;
}
class WolvesAndSheep{
	public:  
	int getmin(vector <string> field)  {  
		// $CARETPOSITION$  
    int i,j;
    n=SZ(field);
    m=SZ(field[0]);
    for(i=0;i<n;++i){
      for(j=0;j<m;++j){
        g[i][j]=change(field[i][j]);
      }
    }
    int ans=inf;
    for(int S=0;S<1<<(n-1);++S){
      ans=min(ans,calc(S));      
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"W.WSS",
 "WW.S.",
 ".SSS.",
 "SSS.S",
 ".SS.S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arr0[] = {".....",
 ".....",
 "....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arr0[] = {".SS",
 "...",
 "S..",
 "W.W"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arr0[] = {"WWWSWWSSWWW",
 "WWSWW.SSWWW",
 "WS.WSWWWWS."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arr0[] = {".W.S.W.W",
 "W.W.S.W.",
 ".S.S.W.W",
 "S.S.S.W.",
 ".S.W.W.S",
 "S.S.W.W.",
 ".W.W.W.S",
 "W.W.S.S."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arr0[] = {"W.SSWWSSSW.SS",
 ".SSSSW.SSWWWW",
 ".WWWWS.WSSWWS",
 "SS.WSS..W.WWS",
 "WSSS.SSWS.W.S",
 "WSS.WS...WWWS",
 "S.WW.S.SWWWSW",
 "WSSSS.SSW...S",
 "S.WWSW.WWSWSW",
 ".WSSS.WWSWWWS",
 "..SSSS.WWWSSS",
 "SSWSWWS.W.SSW",
 "S.WSWS..WSSS.",
 "WS....W..WSS."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(5, Arg1, getmin(Arg0)); }
	void test_case_6() { string Arr0[] = {"WW..SS",
 "WW..SS",
 "......",
 "......",
 "SS..WW",
 "SS..WW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(6, Arg1, getmin(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	WolvesAndSheep ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
