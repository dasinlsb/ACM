/*
可以扩张到无限大肯定是1出发到某个环上，然后环上某一点有连向环外的边
强连通分量缩起来判一下即可
剩下的情况每个强连通分量都是一个点或者一个环，每次消失一个产生一个，内部只会产生一个单位的贡献，只要拓扑dp一下取出度为0的分量累加到答案即可
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
const int mod=1000*1000*1000+7;
int n,T,scc_cnt;
vector<int>G[maxn],Gs[maxn],scc[maxn];
int dfn[maxn],low[maxn];
bool in_stk[maxn];
int bel[maxn],deg[maxn];
vector<int>stk;
void Tarjan(int x){
  dfn[x]=low[x]=++T;
  stk.push_back(x);
  in_stk[x]=1;
  for(int v:G[x]){
    if(!dfn[v]){
      Tarjan(v);
      low[x]=min(low[x],low[v]);
    }else if(in_stk[v]){
      low[x]=min(low[x],dfn[v]);
    }
  }
  if(dfn[x]==low[x]){
    scc_cnt++;
    int y;
    do{
      y=stk.back();
      bel[y]=scc_cnt;
      scc[scc_cnt].push_back(y);
      in_stk[y]=0;
      stk.pop_back();
    }while(y!=x);
  }
}
int topo_dp(){
  static int q[maxn],f[maxn];
  int h=1,t=0;
  for(int i=1;i<=scc_cnt;i++)if(!deg[i]){
    q[++t]=i;
  }
  memset(f,0,sizeof(f));
  f[bel[1]]=1;
  int res=0;
  for(;h<=t;){
    int x=q[h++];
    if(!Gs[x].size()){
      res=(res+f[x])%mod;
    }
    for(int v:Gs[x]){
      f[v]=(f[v]+f[x])%mod;
      deg[v]--;
      if(!deg[v])q[++t]=v;
    }
  }
  return res;
}
class MonsterFarm{
	public:
	int numMonsters(vector <string> transforms){
		// $CARETPOSITION$
    vector<string>&trans=transforms;
    n=trans.size();
    scc_cnt=T=0;stk.clear();
    for(int i=1;i<=n;i++){
      G[i].clear();
      scc[i].clear();
      dfn[i]=low[i]=deg[i]=0;
      in_stk[i]=0;
    }
    for(int i=0;i<n;i++){
      for(int p=0;;){
        for(;p<trans[i].size() && (trans[i][p]<'0' ||trans[i][p]>'9');p++);
        if(p==trans[i].size())break;
        int x=trans[i][p]-'0';
        for(p++;p<trans[i].size() && (trans[i][p]>='0' && trans[i][p]<='9');p++){
          x=x*10+trans[i][p]-'0';
        }
        G[i+1].push_back(x);
      }
    }
    Tarjan(1);
    for(int i=1;i<=scc_cnt;i++){
      Gs[i].clear();
      int tot_edge=0;
      int inside_edge=0;
      for(int x:scc[i]){
        for(int v:G[x]){
          tot_edge++;
          if(bel[v]==i)inside_edge++;
          else{
            Gs[i].push_back(bel[v]);
            deg[bel[v]]++;
          }
        }
      }
      if(inside_edge>=1 && tot_edge>scc[i].size())return -1;
    }
    return topo_dp();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, numMonsters(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, numMonsters(Arg0)); }
	void test_case_2() { string Arr0[] = {"2", "3", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, numMonsters(Arg0)); }
	void test_case_3() { string Arr0[] = {"1", "3 4", "2", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, numMonsters(Arg0)); }
	void test_case_4() { string Arr0[] = {"2 2", "3", "4 4 4", "5", "6", "7 7 7 7", "7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(4, Arg1, numMonsters(Arg0)); }
	void test_case_5() { string Arr0[] = {"2 3","5 7","2 4","5","6","4","7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, numMonsters(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	MonsterFarm ___test;  
 	___test.run_test(-1);  
   vector<string>tmp;
   tmp.push_back("2");
   tmp.push_back("3 4");
   tmp.push_back("1");
   tmp.push_back("4");
  int res=___test.numMonsters(tmp);
  printf("%d\n",res);
	return 0;  
}  
// END CUT HERE  
