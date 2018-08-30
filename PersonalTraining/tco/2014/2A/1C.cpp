/*
假设当前红点在x节点，如果某个子树y不全是黑点，那么必定可以至少往那边移动一步
但是如果想要移动更多，或者子树y本来就是满的，就不能直接移动红点了
要想子树y中的黑点出去，x必定要有至少一个邻接块不全是黑点
至于具体有多少并不重要，只要x可以往那边移动使得子树y中的黑点可以移出去就行了
可以考虑在无根树上dp,用f[x][y][z]表示当前红点在x,那个可供x临时安放的邻接块在y子树，除了y子树，x的其他子树中一共有z个黑点是否有可能
显然一旦把x临时移动到y节点后，其他子树中的黑点可以任意互相转移，转移十分方便
状态数O(n^2)，转移O(n)，总时间复杂度大约是O(n^3)
*/
//#line 2 "TreePuzzle.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=505;
int n,ed,size_q,qe[maxN*2],sz[maxN][maxN],sb[maxN][maxN],vis[maxN*2][maxN],que[maxN*2*maxN],pos[maxN][maxN];
VI g[maxN];
void dfs1(int x,int y,VI&token){
  sz[x][y]=1;
  sb[x][y]=token[x-1];
  for(int i=0;i<SZ(g[x]);++i)if(g[x][i]!=y){
    dfs1(g[x][i],x,token);
    sz[x][y]+=sz[g[x][i]][x];
    sb[x][y]+=sb[g[x][i]][x];
  }
}
void add(int k,int z){
  if(vis[k][z])return;
  vis[k][z]=1;
  que[++size_q]=k<<10|z;
}
void addedge(int x,int y){
  g[x].pb(y);
  qe[++ed]=x<<10|y;
  pos[x][y]=ed;
}
class TreePuzzle {
	public:  
	vector <int> reachable(vector <int> parent, vector <int> token)  {  
		// $CARETPOSITION$  
    n=SZ(parent);
    ed=0;
    for(int i=1;i<=n;++i){
      g[i].clear();
    }
    int sumb=0;
    for(int i=1;i<n;++i)sumb+=token[i];
    for(int i=1;i<n;++i){
      int x=i+1,y=parent[i]+1;
      addedge(x,y);
      addedge(y,x);
    }
    for(int i=1;i<=n;++i){
      for(int j=0;j<SZ(g[i]);++j){
        dfs1(g[i][j],i,token);
      }
    }
    size_q=0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<SZ(g[1]);++i){
      int v=g[1][i];
      if(sz[v][1]!=sb[v][1]){
        add(pos[1][v],sb[v][1]);
      }
    }
    VI ans(n,0);
    ans[0]=1;
    for(int pl=1;pl<=size_q;++pl){
      int S_x=qe[que[pl]>>10]&1023;
      int S_y=qe[que[pl]>>10]>>10;
      int S_b=que[pl]&1023;
      //printf("s %d %d %d\n",S_x,S_y,S_b);
      ans[S_x-1]=1;
      add(pos[S_x][S_y],sumb-S_b);
      int S_w=n-sz[S_y][S_x]-1-S_b;
      if(!S_w)continue;
      for(int i=0;i<SZ(g[S_x]);++i){
        int v=g[S_x][i];
        if(v==S_y)continue;
        int low=max(0,sz[v][S_x]-S_w);
        int high=min(sz[v][S_x]-1,S_b);
        for(int j=low;j<=high;++j){
          add(pos[S_x][v],j);
        }
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {-1, 0, 0, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 0, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 1, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, reachable(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-1, 0, 1, 0, 3, 2, 5, 6, 7, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1, 1, 0, 0, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 0, 0, 1, 0, 0, 0, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, reachable(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1, 0, 0, 2, 1, 1, 5, 0, 0, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, reachable(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-1, 0, 1, 2, 3, 4, 5, 0, 7, 6, 8, 9, 11, 0, 11, 2, 15, 13, 15, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, reachable(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-1, 0, 1, 2, 3, 4, 0, 5, 7, 8, 6, 10, 11, 9, 13, 14, 12, 16, 16, 18,
15, 10, 17, 2, 23, 22, 21, 20, 27, 24, 19, 30, 28, 29, 17, 21, 34, 35, 31, 30,
36, 32, 31, 39, 26, 40, 3, 38, 45, 25, 49, 46, 41, 44, 51, 47, 18, 54, 48, 36,
43, 57, 52, 56, 60, 59, 53, 61, 64, 68, 37, 55, 71, 32, 26, 73, 28, 50, 75, 72,
70, 67, 74, 66, 79, 76, 78, 63, 69, 41, 83, 86, 80, 18, 82, 87, 58, 62, 42, 20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, reachable(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	TreePuzzle ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
