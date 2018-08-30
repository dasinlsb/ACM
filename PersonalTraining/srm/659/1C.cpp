//#line 2 "PublicTransitHard.cpp" 
/*
可以枚举其中一个端点，dfs判断另一个端点的可行性
假设起点，也就是根，为x，当前dfs到y节点，设路径[x->y]上的点为p_i
显然在dfs的过程中，p_i连出去的若干子树（不在路径[x->y]上）之间的距离合法性是可以直接判断的
接下来考虑对于i!=j，p_i子树和p_j子树之间的合法性
对于dep[p_i]<dep[p_j]，dis(p_i,p_j)定义为min(dep[p_j]-dep[p_i]+mx[p_i]+mx[p_j],dep[y]-dep[p_j]+dep[p_i]-dep[x]+mx[p_i]+mx[p_j])
这个式子非法当且仅当min()中的两项都大于X
也就是在固定p_j之后，对于所有p_i满足-dep[p_i]+mx[p_i]>X-dep[p_j]-mx[p_j]都有:
dep[y]>X+dep[p_j]-dep[p_i]+dep[x]-mx[p_i]-mx[p_j]恒成立，这相当于不断加一个对于dep[y]的限制，支持撤销操作，单点取max,后缀求max，树状数组维护即可

*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=2005;
const int inf=maxN*5;
int n,ans,from,lim,bad[maxN],dep[maxN];
VI g[maxN];
vector<pii>mxl[maxN],mxd[maxN];
bool cmp(pii x,pii y){return x.fi>y.fi;}
void dfs1(int x,int y){
  mxd[x].clear();
  mxl[x].clear();
  bad[x]=0;
  for(int i=0;i<SZ(g[x]);++i)if(g[x][i]!=y){
    int v=g[x][i];
    dep[v]=dep[x]+1;
    dfs1(v,x);
    mxd[x].pb(pii(mxd[v][0].fi+1,v));
    bad[x]|=bad[v];
    mxl[x].pb(pii(bad[v],v));
  }
  mxd[x].pb(pii(0,0));
  mxd[x].pb(pii(0,0));
  mxl[x].pb(pii(0,0));
  sort(mxd[x].begin(),mxd[x].end(),cmp);
  sort(mxl[x].begin(),mxl[x].end(),cmp);
  bad[x]|=(mxd[x][0].fi+mxd[x][1].fi>lim);
}
int top,T[maxN*3];
pii stk[maxN*100];
const int offset=maxN;
void dfs2(int x,int y,int con){//dep must<=con 
  int i,j;
  if(dep[x]>con)return;
  //printf("from %d to %d\n",from,x);
  if(x>=from&&!bad[x]){
    int mxY=-inf;
    for(i=offset-(lim-mxd[x][0].fi-dep[x]+1);i>0;i-=i&-i)mxY=max(mxY,T[i]);
    if(lim-mxd[x][0].fi+dep[x]-mxY>=dep[x])++ans;
  }
  for(i=0;i<SZ(g[x]);++i)if(g[x][i]!=y){
    int v=g[x][i];
    if(mxl[x][v==mxl[x][0].se].fi)continue;//{printf("cut %d\n",v);continue;}
    int k=0,l=0;
    for(j=0;j<3;++j)if(k<2&&mxd[x][j].se!=v){l+=mxd[x][j].fi;++k;}
    if(l>lim)continue;
    int d=mxd[x][v==mxd[x][0].se].fi;
    int mxY=-inf;
    for(j=offset-(lim-d-dep[x]+1);j>0;j-=j&-j)mxY=max(mxY,T[j]);
    int low=top;
    for(j=offset-(d-dep[x]);j<maxN*3;j+=j&-j){
      stk[++top]=pii(j,T[j]);
      T[j]=max(T[j],d+dep[x]);
    }
    //printf("next %d add con %d\n",v,lim-mxY-d+dep[x]);
    dfs2(v,x,min(con,lim-mxY-d+dep[x]));
    for(;top>low;--top)T[stk[top].fi]=stk[top].se;
  }
}
class PublicTransitHard  
{  
    public:  
    int countValidTeleporters(int N, vector <int> edges, int X){  
      //$CARETPOSITION$ 
      int i;
      n=N;lim=X;
      for(i=1;i<=n;++i)g[i].clear();
      for(i=0;i<SZ(edges);++i){
        g[i+2].pb(edges[i]+1);
        g[edges[i]+1].pb(i+2);
      }
      ans=0;
      for(i=1;i<=n;++i){
        //int pre=ans;
        from=i;
        dep[i]=0;
        dfs1(i,0);
        for(int j=1;j<maxN*3;++j)T[j]=-inf;
        dfs2(i,0,n);
        //for(int j=1;j<maxN*3;++j)assert(T[j]==0);
        //assert(top==0);
        //printf("%d : %d\n",i,ans-pre);
      }
      return ans;
    }  
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = {0, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 6; verify_case(1, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 6; int Arr1[] = {0, 0, 0, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 1; verify_case(2, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 7; int Arr1[] = {0, 1, 0, 1, 2, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 0; verify_case(3, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 16; int Arr1[] = {0, 1, 0, 2, 0, 0, 4, 5, 8, 9, 10, 11, 8, 4, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; int Arg3 = 31; verify_case(4, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 56; int Arr1[] = {0, 1, 1, 3, 1, 5, 1, 0, 8, 8, 10, 10, 12, 10, 10, 8, 16, 16, 18, 19, 19, 21, 19, 19, 24, 25, 25, 27, 18, 0, 30, 30, 30, 33, 34, 34, 34, 30, 38, 39, 39, 38, 42, 43, 0, 45, 45, 45, 48, 45, 45, 51, 45, 53, 54}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; int Arg3 = 610; verify_case(5, Arg3, countValidTeleporters(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        PublicTransitHard ___test;  
        ___test.run_test(-1);
        return 0;
}  
// END CUT HERE  
