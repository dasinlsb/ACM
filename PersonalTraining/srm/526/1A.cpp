/*
暴力枚举左上角位置然后暴力跑匈牙利好像会直接爆炸
不过贪心策略也非常容易想到，不失一般性，可以只考虑醉最终鸭子都排在同一行的情况
显然这一行所在位置必须是各鸭子行号的中位数
剩下的可以直接O(m)枚举最终区间的起点，然后肯定是从左到右贪心地匹配
时间复杂度O(n^2)
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=55;
const int inf=(int)1e8;
int Abs(int x){
  return x>0?x:-x;
}
int solve(vector<string >&G,int total){
  int n=G.size();
  int m=G[0].size();
  int pre=0;
  int row=-1;
  vector<int >ver,hor;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++)if(G[i][j]=='o'){
      pre++;
      ver.push_back(i);
      hor.push_back(j);
    }
    if(row==-1&&pre>total/2){
      row=i;
    }
  }
  //printf("row %d\n",row);
  int res=inf;
  sort(hor.begin(),hor.end());
  for(int i=0;i+total-1<m;i++){
    int tmp=0;
    for(int j=0;j<total;j++){
      tmp+=Abs(i+j-hor[j]);
    }
    //printf("hor %d %d\n",i,tmp);
    res=min(res,tmp);
  }
  for(int i=0;i<total;i++){
    res+=Abs(ver[i]-row);
  }
  return res;
}
class DucksAlignment{
	public:
	int minimumTime(vector <string> grid){
		// $CARETPOSITION$
    int n=grid.size();
    int m=grid[0].size();
    int total=0;
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
        if(grid[i][j]=='o')total++;
      }
    }
    int ans=solve(grid,total);
    //printf("fir %d\n",ans);
    vector<string >rot(m);
    for(int i=0;i<m;i++){
      rot[i].resize(n);
      for(int j=0;j<n;j++){
        rot[i][j]=grid[j][i];
      }
    }
    ans=min(ans,solve(rot,total));
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".o",
 "o."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minimumTime(Arg0)); }
	void test_case_1() { string Arr0[] = {".o...",
 "..o..",
 "....o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, minimumTime(Arg0)); }
	void test_case_2() { string Arr0[] = {"o..........",
 "..o........",
 ".......o...",
 "...........",
 "...........",
 "...........",
 "........o..",
 "..........."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(2, Arg1, minimumTime(Arg0)); }
	void test_case_3() { string Arr0[] = {".........",
 "....o....",
 "........."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, minimumTime(Arg0)); }
	void test_case_4() { string Arr0[] = {"...o..........................",
 "............................o.",
 ".o............................",
 "............o.................",
 ".................o............",
 "......................o.......",
 "......o.......................",
 "....o.........................",
 "...............o..............",
 ".......................o......",
 "...........................o..",
 ".......o......................"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 99; verify_case(4, Arg1, minimumTime(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	DucksAlignment ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
