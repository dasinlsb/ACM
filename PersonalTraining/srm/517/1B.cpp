/*
对于每个区间暴力枚举第一个交换的位置，这个位置两边会相互隔离，判一下最大最小是否符合即可
如果直接递推复杂度是O(n^5)，实际上有很多状态无效，可以记忆化搜索
*/
//#line 2 "AdjacentSwaps.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef long long ll;  
typedef pair<int,int> pii;  
const int mod=1000*1000*1000+7;
const int maxN=55;
const int inf=55;
int n;
int LOG[maxN];
int seg_max[maxN][7];
int seg_min[maxN][7];
int c[maxN][maxN];
int f[maxN][maxN][maxN][maxN];
int ask_max(int l,int r){
  int d=LOG[r-l+1];
  return max(seg_max[l][d],seg_max[r-(1<<d)+1][d]);
}
int ask_min(int l,int r){
  int d=LOG[r-l+1];
  return min(seg_min[l][d],seg_min[r-(1<<d)+1][d]);
}
int DP(int l,int r,int x,int y,vector<int>&p){
  //printf("dp %d %d %d %d\n",l,r,x,y);
  if(l==r)return l==x&&r==y;
  if(l+1==r)return l==y&&r==x;
  int now_max=max(ask_max(l+1,r-1),max(x,y));
  int now_min=min(ask_min(l+1,r-1),min(x,y));
  if(now_min!=l||now_max!=r)return 0;
  if(f[l][r][x][y]!=-1)return f[l][r][x][y];
  int res=0;
  if(l==p[l+1])res=(res+DP(l+1,r,x,y,p))%mod;
  if(r==p[r-1])res=(res+DP(l,r-1,x,y,p))%mod;
  for(int i=l+2;i<r;i++){
    res=(res+(ll)c[r-l-1][i-l-1]*DP(l,i-1,x,p[i],p)%mod*DP(i,r,p[i-1],y,p))%mod;
  }
  //printf("dp %d %d %d %d :%d\n",l,r,x,y,res);
  return f[l][r][x][y]=res;
}
class AdjacentSwaps {
	public:  
	int theCount(vector <int> p)  {  
		// $CARETPOSITION$  
    n=SZ(p);
    c[0][0]=1;
    for(int i=1;i<maxN;i++){
      c[i][0]=1;
      for(int j=1;j<=i;j++){
        c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
      }
    }
    for(int i=2;i<maxN;i++)LOG[i]=LOG[i>>1]+1;
    for(int i=0;i<n;i++){
      seg_max[i][0]=p[i];
      seg_min[i][0]=p[i];
    }
    for(int j=1;j<7;j++){
      for(int i=0;i+(1<<j)-1<n;i++){
        seg_max[i][j]=max(seg_max[i][j-1],seg_max[i+(1<<j-1)][j-1]);
        seg_min[i][j]=min(seg_min[i][j-1],seg_min[i+(1<<j-1)][j-1]);
      }
    }
    memset(f,-1,sizeof(f));
   //printf("chk %d\n",DP());
    int ans=DP(0,n-1,p[0],p[n-1],p);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, theCount(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, theCount(Arg0)); }
	void test_case_2() { int Arr0[] = {2, 0, 3, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, theCount(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 0, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, theCount(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 3, 0, 5, 2, 7, 4, 8, 10, 6, 12, 9, 14, 11, 16, 13, 18, 15, 19, 17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 716743312; verify_case(4, Arg1, theCount(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AdjacentSwaps ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
