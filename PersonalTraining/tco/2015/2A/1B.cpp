/*
非常有意思的题
实际上是一个匹配的问题，但是合法匹配的条件和普通的二分图的完全匹配不一样
由于图是一棵树，那么最后聚集形成联通块也会是一棵树，不妨枚举这棵树的根
对于每个子树中的fox,显然移到根就足够优了，不需要再移动到别的子树中,在这里可以二分答案检验
非法的情况发生在某些fox向根移动过程中，能到达的最高点都没有到根，那么最高点上方的部分就需要别的fox去填充
这一部分的合法情况恰好是二分图完全匹配的情况
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
const int inf=5000005;
int n,ed;
int fir[maxn];
int dist[maxn][maxn];
int fa[maxn][maxn];
vector< pair<int,int> >path[maxn][maxn];
struct Edge{
  int v,w,nxt;
}e[maxn*2];
inline void adde(int x,int y,int z){
  e[++ed].v=y;e[ed].nxt=fir[x];e[ed].w=z;fir[x]=ed;
}
void dfs1(int x,int from){
  for(int i=fir[x];i;i=e[i].nxt)if(e[i].v!=fa[from][x]){
    fa[from][e[i].v]=x;
    dist[from][e[i].v]=dist[from][x]+e[i].w;
    dfs1(e[i].v,from);
  }
}
int vis[maxn],links[maxn];
int root;
int bad[maxn];
vector<int>G[maxn];
int dfs2(int x){
  for(int v:G[x])if(!vis[v]){
    vis[v]=1;
    if(!links[v] || dfs2(links[v])){
      return links[v]=x,1;
    }
  }
  return 0;
}
int test(vector<int>&foxes,int D){
  memset(bad,0,sizeof(bad));
  for(int x:foxes){
    int y=x;
    for(;y && dist[root][x]-dist[root][y]<=D;y=fa[root][y]);
    for(;y;y=fa[root][y])bad[y]=1;
  }
  for(int i=1;i<=n;i++)if(bad[i]){
    G[i].clear();
    for(int x:foxes)if(dist[i][x]<=D){
      G[i].push_back(x);
    }
  }
  memset(links,0,sizeof(links));
  for(int i=1;i<=n;i++)if(bad[i]){
    memset(vis,0,sizeof(vis));
    if(!dfs2(i))return 0;
  }
  return 1;
}
class FoxMeeting{
	public:
	int maxDistance(vector <int> A, vector <int> B, vector <int> L, vector <int> foxes){
		// $CARETPOSITION$
    n=A.size()+1;
    ed=0;
    for(int i=1;i<=n;i++){
      fir[i]=0;
    }
    for(int i=0;i<n-1;i++){
      adde(A[i],B[i],L[i]);
      adde(B[i],A[i],L[i]);
    }
    for(int i=1;i<=n;i++){
      fa[i][i]=0;
      dist[i][i]=0;
      dfs1(i,i);
    }
    int ans=inf;
    for(int i=1;i<=n;i++){
      root=i;
      int l=0,r=ans;
      for(;l<r;){
        int mid=(l+r)/2;
        if(test(foxes,mid))r=mid;
        else l=mid+1;
      }
      ans=min(ans,l);
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(0, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(1, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {10,8,3,7,2,6,9,1,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,5,8,10,5,5,6,10,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {71846,10951,42265,37832,29439,95676,83661,28186,21216}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(3, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {8,15,22,24,2,25,13,26,18,4,9,29,1,12,3,16,14,21,19,27,17,7,20,10,30,11,6,5,23}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {28,28,8,8,28,28,25,2,13,24,24,22,22,29,4,22,8,4,1,24,21,14,18,16,13,21,14,1,25}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {79374,40629,43195,73589,24200,63937,35339,7598,65109,51764,11142,84017,51078,58051,81387,22035,34883,92710,52283,57337,79309,3383,41904,35839,38242,43208,82062,24676,71838}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,5,7,9,10,14,17,19,20,21,24,25,28}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 107013; verify_case(4, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {34,14,22,9,24,19,11,37,33,21,5,30,1,43,7,31,45,27,6,12,13,35,23,47,49,50,26,40,16,10,48,25,29,15,28,46,4,20,44,17,39,32,38,2,42,8,36,3,41}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {18,18,18,14,9,34,9,24,34,11,18,14,21,21,43,1,22,7,1,30,14,33,13,18,9,5,1,1,26,19,50,33,50,40,29,48,50,37,16,40,48,14,30,22,47,37,7,50,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {22051,11109,85275,6691,43705,47374,27748,5411,62549,84079,89542,38006,82198,24083,16847,66335,3542,72495,37378,73973,85703,51682,68688,94295,31337,
90071,99317,63484,43244,99079,55857,34503,79709,82140,91137,27033,91599,61168,52345,49569,58919,38133,43361,
40718,2115,79278,88841,40966,42023}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,12,13,18,23,27,28,29,32,33,34,35,36,37,40,42,43,47,48,49,50}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 89342; verify_case(5, Arg4, maxDistance(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	FoxMeeting ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
