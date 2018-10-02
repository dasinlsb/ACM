/*
O(n^2)暴力枚举2-5这条路径然后O(1)计算对答案的贡献
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=2005;
const int mod=1000*1000*1000+7;
int n;
vector<int>G[maxn];
int sz[maxn],fa[maxn],dep[maxn],sz2[maxn];
int Pow(long long x,int y){
  long long t=1;
  for(;y;y>>=1){
    if(y&1)t=t*x%mod;
    x=x*x%mod;
  }
  return t;
}
inline void up(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
void dfs(int x){
  sz[x]=1;
  sz2[x]=0;
  for(int v:G[x]){
    dep[v]=dep[x]+1;
    fa[v]=x;
    dfs(v);
    sz[x]+=sz[v];
    sz2[x]=(sz2[x]+sz[v]*sz[v]);
  }
}
int ask(int x,int y){
  int down=((sz[x]-1)*(sz[x]-1)-sz2[x])%mod;
  int mid=((sz[fa[y]]-sz[y]-1)*(sz[fa[y]]-sz[y]-1)-(sz2[fa[y]]-sz[y]*sz[y]))%mod;
  return 1LL*down*mid%mod*dep[fa[y]]%mod;
}
class TheTreeAndMan{
	public:
	int solve(vector <int> parent){
		// $CARETPOSITION$
    n=parent.size()+1;
    for(int i=0;i<n;i++){
      G[i].clear();
    }
    for(int i=0;i<n-1;i++){
      G[parent[i]].push_back(i+1);
    }
    dfs(0);
    int ans=0;
    // for(int i=0;i<n;i++){
    //   printf("ifno %d dep %d %d\n",i,dep[i],sz[i]);
    // }
    for(int x=0;x<n;x++){
      int y=x;
      for(;y;y=fa[y]){
        int res=ask(x,y);
        up(ans,res);
        // printf("ask %d %d %d\n",x,fa[y],res);
      }
    }
    ans=1LL*ans*Pow(4,mod-2)%mod;
    return ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,1,1,1,4,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { int Arr0[] = {0,0,2,2,2,4,0,4,7,2,10,11,9,0,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { int Arr0[] = {0,0,2,2,3,1,0,1,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { int Arr0[] = {0,0,0,2,3,5,2,5,3,7,7,7,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { int Arr0[] = {0,0,1,2,2,2,1,4,2,9,0,1,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, solve(Arg0)); }
	void test_case_5() { int Arr0[] = {0,0,0,2,4,2,5,6,5,9,5,0,3,8,8,15,0,17,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(5, Arg1, solve(Arg0)); }
	void test_case_6() { int Arr0[] = {0,0,0,3,0,1,3,5,6,8,2,7,1,9,1,5,13,6,3,7,8,4,2,18,12,11,17,13,10,25,11,26,22,32,32,18,35,33,25,31,24,38,41,34,43,42,32,
43,31,35,47,49,36,35,39,42,36,39,47,53,40,61,60,43,47,61,51,56,67,69,53,53,63,56,71,55,76,73,70,74,67,76,64,80,68,85,78,
69,79,73,70,75,77,81,80,94,85,88,88,99,83,99,93,90,85,100,89,96,96,103,107,96,105,95,100,97,97}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9864; verify_case(6, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	TheTreeAndMan ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
