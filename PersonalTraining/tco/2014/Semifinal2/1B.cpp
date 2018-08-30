/*
如果一组(s,t)在同一个边双里面肯定可以满足，只需要考虑在不同的边双的情况，由于(s,t)很少，直接2^|(s,t)|枚举即可
*/
//#line 2 "RoadsReform.cpp"  
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
const int maxM=505;
int ed,T,fir[maxN],faEdge[maxN],cut[maxM*2],bel[maxN],dep[maxN],dir[maxM*2],fa[maxN];
int dfn[maxN],low[maxN];
int gNew[maxN][maxN];
struct Edge{int v,nxt,cut;}e[maxM*2];
void addedge(int x,int y){
  e[++ed].v=y;e[ed].nxt=fir[x];fir[x]=ed;
}
void tarjan(int x){
  dfn[x]=low[x]=++T;
  for(int i=fir[x];i;i=e[i].nxt){
    if(!dfn[e[i].v]){
      faEdge[e[i].v]=i/2;
      tarjan(e[i].v);
      low[x]=min(low[x],low[e[i].v]);
    }else if(faEdge[x]!=i/2){
      low[x]=min(low[x],dfn[e[i].v]);
    }
  }
  if(faEdge[x]&&dfn[x]==low[x]){
    cut[faEdge[x]]=1;
  }
}
void dfs(int x,int y){
  bel[x]=y;
  for(int i=fir[x];i;i=e[i].nxt)if(bel[e[i].v]==-1&&!cut[i>>1]){
    dfs(e[i].v,y);
  }
}
void dfsNew(int x){
  for(int i=fir[x];i;i=e[i].nxt)if(e[i].v!=fa[x]){
    fa[e[i].v]=x;
    faEdge[e[i].v]=i/2;
    dep[e[i].v]=dep[x]+1;
    dfsNew(e[i].v);
  }
}
int chkDir(int x,int y){
  if(dir[x]==1-y)return 0;
  return dir[x]=y,1;
}
int paint(int x,int y){
  for(;dep[x]>dep[y];x=fa[x]){
    if(!chkDir(faEdge[x],1))return 0;
  }
  for(;dep[y]>dep[x];y=fa[y]){
    if(!chkDir(faEdge[y],0))return 0;
  }
  for(;x!=y;x=fa[x],y=fa[y]){
    if(!chkDir(faEdge[x],1))return 0;
    if(!chkDir(faEdge[y],0))return 0;
  }
  return 1;
}
class RoadsReform {
	public:  
	int getMax(int n, vector <int> e1, vector <int> e2, vector <int> s, vector <int> t)  {  
		// $CARETPOSITION$  
    ed=1;
    memset(fir,0,sizeof(fir));
    for(int i=0;i<SZ(e1);i++){
      addedge(e1[i],e2[i]);
      addedge(e2[i],e1[i]);
    }
    T=0;
    memset(faEdge,0,sizeof(faEdge));
    memset(cut,0,sizeof(cut));
    memset(dfn,0,sizeof(dfn));
    tarjan(0);
    memset(bel,-1,sizeof(bel));
    int blkCnt=0;
    for(int i=0;i<n;i++)if(bel[i]==-1){
      dfs(i,blkCnt++);
    }
    vector<pii> qry;
    for(int i=0;i<SZ(s);i++){
      if(bel[s[i]]!=bel[t[i]]){
        qry.pb(make_pair(bel[s[i]],bel[t[i]]));
      }
    }
    memset(gNew,0,sizeof(gNew));
    ed=1;
    memset(fir,0,sizeof(fir));
    for(int i=0;i<SZ(e1);i++){
      int x=bel[e1[i]];
      int y=bel[e2[i]];
      if(x==y)continue;
      if(x>y)swap(x,y);
      if(!gNew[x][y]){
        addedge(x,y);
        addedge(y,x);
        gNew[x][y]=1;
        //printf("new %d %d\n",x,y);
      }
    }
    dfsNew(0);
    int ans=0;
    for(int qS=0;qS<1<<SZ(qry);qS++){
      int ok=1;
      int bitCnt=0;
      for(int i=0;i<=ed;i++)dir[i]=-1;
      for(int i=0;i<SZ(qry);i++)if(1<<i&qS){
        bitCnt++;
        if(!paint(qry[i].fi,qry[i].se)){ok=0;break;}
      }
      if(ok)ans=max(ans,bitCnt);
    }
    for(int i=0;i<SZ(s);i++)if(bel[s[i]]==bel[t[i]]){
      ++ans;
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 1; verify_case(0, Arg5, getMax(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 4; int Arr1[] = {0, 1, 2}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 1, 3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {3, 3, 2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 2; verify_case(1, Arg5, getMax(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 6; int Arr1[] = {0, 1, 1, 2, 3, 4}	; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3, 4, 4, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {4, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 2; verify_case(2, Arg5, getMax(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 8; int Arr1[] = {0, 0, 1, 1, 3, 4, 4, 4}		; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 2, 3, 4, 5, 6, 7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 1, 4, 5, 6}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {5, 7, 5, 0, 2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 3; verify_case(3, Arg5, getMax(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 20; int Arr1[] = {1, 2, 7, 9, 10, 11, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18, 19, 19, 19, 19}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 1, 5, 8, 4, 3, 8, 9, 5, 7, 10, 4, 10, 0, 6, 14, 0, 15, 3, 9, 1, 1, 3, 11, 13}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 6, 7, 9, 12, 13, 14, 16, 19, 19}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {7, 19, 12, 15, 16, 4, 7, 0, 13, 14}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 7; verify_case(4, Arg5, getMax(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	RoadsReform ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
