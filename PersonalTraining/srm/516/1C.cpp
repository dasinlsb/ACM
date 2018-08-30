/*
fleury无法处理有回溯的情况，所以只能逐位确定，问题转化为给定无向图，如何判定是否存在除了起点和终点以外相邻边权不相等的欧拉回路
直接在图上判定这个条件是比较困难的，因为起点终点之间的边有特殊性
考虑一个简化的问题，包括起点终点，如何判定以上情况是否成立，只要在起点连出去两条不同的边即可转化回去
对于每个点考虑所有和它相连的边，这些边在最后的回路种可能是出边也可能是入边，每有一条边权为x的入边，就要有一条非x的出边
也就是对于这个点，任意相连边的边权个数都不能占超过一半的比例
考虑添加两个辅助点n,n+1并维护一条路径，假设当前点为x，下一个可行点为y，(x,y)边权为w
那么维护的路径可以由(0,n,n+1,x)变为(0,n,n+1,y)
也就是删掉(n+1,x),(x,y)，增加一条(n+1,y)的边权为w的边
剩下的子问题也是求欧拉回路
*/
//#line 2 "LexSmallestTour.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=45;
int n,e_tot;
int g[maxN][maxN];
int deg[maxN];
int vis[maxN];
vector<int>path;
void add_edge(int x,int y,int z){
  g[x][y]=g[y][x]=z;
  deg[x]++;deg[y]++;
  e_tot++;
}
void cut_edge(int x,int y){
  g[x][y]=g[y][x]=0;
  deg[x]--;deg[y]--;
  e_tot--;
}
void dfs(int x){
  vis[x]=1;
  for(int i=0;i<=n+1;i++)if(g[x][i]&&!vis[i]){
    dfs(i);
  }
}
int chk(){
  static vector<int>q;
  for(int i=0;i<=n+1;i++)if(deg[i]){
    q.clear();
    for(int j=0;j<=n+1;j++)if(g[i][j])q.pb(g[i][j]);
    sort(q.begin(),q.end());
    for(int j=0;j<SZ(q);){
      int k=j;
      for(;j<SZ(q)&&q[j]==q[k];j++);
      if(j-k>SZ(q)/2)return 0;
    }
  }
  for(int i=0;i<=n+1;i++)if(deg[i]&1)return 0;
  memset(vis,0,sizeof(vis));
  for(int i=0;i<=n+1;i++)if(deg[i]){
    dfs(i);
    break;
  }
  for(int i=0;i<=n+1;i++)if(deg[i]&&!vis[i])return 0;
  return 1;
}
class LexSmallestTour {
	public:  
	vector <int> determineTour(vector <string> roads, vector <int> queries)  {  
		// $CARETPOSITION$  
    n=SZ(roads);
    memset(g,0,sizeof(g));
    memset(deg,0,sizeof(deg));
    e_tot=0;
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        if(roads[i][j]!='.'){
          add_edge(i,j,roads[i][j]);
        }
      }
    }
    add_edge(0,n,'$');
    add_edge(0,n+1,'#');
    add_edge(n,n+1,'@');
    if(chk()==0)return vector<int>();
    //puts("mid");
    path.clear();
    int x=0,y=-1;
    for(int i=e_tot-3;i;i--){
      for(int j=0;j<n;j++)if(g[x][j]&&g[x][j]!=y){
        int w1=g[x][n+1];
        cut_edge(x,n+1);
        int w2=g[x][j];
        cut_edge(x,j);
        add_edge(n+1,j,w2);
        if(chk()==1){
          path.pb(x);
          //printf("path %d\n",x);
          y=w2;
          x=j;
          break;
        }
        cut_edge(n+1,j);
        add_edge(x,j,w2);
        add_edge(x,n+1,w1);
      }
    }
    path.pb(0);
    vector<int>ans(SZ(queries));
    for(int i=0;i<SZ(queries);i++){
      //if(queries[i]>=SZ(path))while(1);
      //assert(queries[i]<SZ(path));
      ans[i]=path[queries[i]];
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {".AB"
,"A.C"
,"BC."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 2, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, determineTour(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {".A..C"
,"A.ABB"
,".A.C."
,".BC.."
,"CB..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 3, 4, 5, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 3, 2, 1, 4, 0 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, determineTour(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {".aa"
,"a.A"
,"aA."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, determineTour(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"..A.A"
,"...A."
,"A...A"
,".A..."
,"A.A.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, determineTour(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	LexSmallestTour ___test;  
 	___test.run_test(3);  
	return 0;  
}  
// END CUT HERE  
