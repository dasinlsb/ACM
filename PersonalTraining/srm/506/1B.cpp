
/*
对于相邻的districts，要么完全走路，要么经过某个car所在的城市在开车到终点，由于每个car是一次性的，显然是一个图的最小权匹配的模型
*/
//#line 2 "SlimeXGrandSlimeAuto.cpp"  
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
const int inf=(int)1e8;
int map_value(char c){
  if(c=='.')return inf;
  if(c>='0'&&c<='9')return c-'0'+1;
  if(c>='a'&&c<='z')return c-'a'+11;
  if(c>='A'&&c<='Z')return c-'A'+37;
}
int n;
namespace KM{
  int n,m,T;
  int w[maxN*2][maxN*2],vis[maxN*4],links[maxN*2],lx[maxN*2],ly[maxN*2],slk[maxN*2];
  int dfs(int x){
    vis[x]=T;
    for(int i=1;i<=m;++i)if(vis[n+i]!=T){
      int d=lx[x]+ly[i]-w[x][i];
      if(!d){
        vis[n+i]=T;
        if(!links[i]||dfs(links[i]))return links[i]=x,1;
      }else slk[i]=min(slk[i],d);
    }
    return 0;
  }
  int work(){
    int i,j;
    T=0;
    fill(vis+1,vis+1+n+m,0);
    fill(lx+1,lx+1+n,-inf);
    fill(ly+1,ly+1+m,0);
    fill(links+1,links+1+m,0);
    for(i=1;i<=n;++i){
      for(j=1;j<=m;++j)lx[i]=max(lx[i],w[i][j]);
    }
    for(i=1;i<=n;++i){
      fill(slk+1,slk+1+m,inf);
      for(;++T,!dfs(i);){
        int dec=inf;
        for(j=1;j<=m;++j)if(vis[j+n]!=T)dec=min(dec,slk[j]);
        for(j=1;j<=n;++j)if(vis[j]==T)lx[j]-=dec;
        for(j=1;j<=m;++j)if(vis[j+n]==T)ly[j]+=dec;
      }
    }
    int res=0;
    for(i=1;i<=n;++i)res+=lx[i];
    for(i=1;i<=m;++i)res+=ly[i];
    return res;
  }
}
int dis[maxN][maxN];
class SlimeXGrandSlimeAuto{
  public:  
  int travel(vector <int> cars, vector <int> districts, vector <string> roads, int inverseWalkSpeed, int inverseDriveSpeed){  
    //$CARETPOSITION$
    int i,j;
    n=SZ(roads);
    int cn=SZ(cars);
    int dn=SZ(districts);
    for(i=0;i<cn;++i)cars[i]++;
    for(i=0;i<dn;++i)districts[i]++;
    for(i=0;i<n;++i)for(j=0;j<n;++j)dis[i+1][j+1]=map_value(roads[i][j]);
    for(i=1;i<=n;++i)dis[i][i]=0;
    for(int k=1;k<=n;++k)for(i=1;i<=n;++i)for(j=1;j<=n;++j)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    //for(i=1;i<=n;++i)for(j=1;j<=n;++j)printf("dis %d %d : %d\n",i,j,dis[i][j]);
    int ans=0;
    for(i=0;i<dn;++i){
      int pre=i?districts[i-1]:1;
      int now=districts[i];
      int low=dis[pre][now]*inverseWalkSpeed;
      //printf("pre now %d %d\n",pre,now);
      ans+=low;
      for(j=0;j<cn;++j){
        KM::w[i+1][j+1]=low-dis[pre][cars[j]]*inverseWalkSpeed-dis[cars[j]][now]*inverseDriveSpeed;
      }
      for(j=0;j<dn;++j)KM::w[i+1][cn+j+1]=0;
    }
    KM::n=dn;
    KM::m=dn+cn;
    int res=KM::work();
    //printf("%d %d\n",ans,res);
    return ans-res;
  }  
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
"..0.",
"...1",
"0..2",
".12."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; int Arg4 = 1; int Arg5 = 36; verify_case(0, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".A.",
"A.B",
".B."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 1; int Arg5 = 262; verify_case(1, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arr0[] = {2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".a4",
"a..",
"4.."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 1; int Arg5 = 95; verify_case(2, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".B.",
"B.A",
".A."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 1; int Arg5 = 262; verify_case(3, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arr0[] = {2,5,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,5,1,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".12.4.",
"1....7",
"2..3..",
"..3..5",
"4.....",
".7.5.."}
; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 53; int Arg4 = 37; int Arg5 = 1259; verify_case(4, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        SlimeXGrandSlimeAuto ___test;  
        ___test.run_test(-1);  
        return 0;  
}  
// END CUT HERE  
