/*
由于所有初始权值为正的点和起点终点的坐标都不一样，所以必然0必定要起跳一次，之后至少还要再跳一次，显然最短路可以是起点到终点的曼哈顿距离
将点排序之后设f[l][r][k]表示l点到r点加恰好k次权值的方案
枚举l到r路径上第一个遇到的正权值点mid,h[l][r][k]=\sum_{mid,i}g[l][mid][i]*f[mid][r][k-i]即至少经过一个正权值的方案数
设g[l][r][k]为l到r完全不经过正权值点的方案数，考虑用all(l,r,k)减去至少经过一个正权值点的方案，即all(l,r,k)-\sum_{mid,i}g[l][mid][i]*all(mid,r,k-i)
f[l][r][k]=h[l][r][k]+g[l][r][k]
*/
//#line 2 "NumberLabyrinthDiv1.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=125;
const int maxM=2000005;
const int mod=1000*1000*1000+9;
inline void add(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
struct Node{
  int x,y,v;
  Node(){}Node(int _x,int _y,int _v){x=_x,y=_y,v=_v;}
}p[maxN];
int fac[maxM],inv[maxM];
int comb(int x,int y){
  if(x<0||y<0||x<y)return 0;
  int res=(ll)fac[x]*inv[y]%mod*inv[x-y]%mod;
  return res;
}
bool cmp(Node a,Node b){
  return a.x<b.x||a.x==b.x&&a.y<b.y;
}
int All(int x,int y,int k){
  int res=0;
  if(!k)return !x&&!y;
  if(!x)return comb(y-1,k-1);
  if(!y)return comb(x-1,k-1);
  for(int i=1;i<k;++i){
    add(res,(ll)comb(x-1,i-1)*comb(y-1,k-i-1)%mod*comb(k,i)%mod);
  }
  return res;
}
int f[maxN][maxN][12];
int g[maxN][maxN][12];
class NumberLabyrinthDiv1 {
	public:  
	int getNumberOfPaths(vector <int> X, vector <int> Y, vector <int> val, int xFinish, int yFinish, int K)  {  
		// $CARETPOSITION$
    int i,j,k;
    for(fac[0]=i=1;i<maxM;++i)fac[i]=(ll)fac[i-1]*i%mod;
    for(inv[0]=inv[1]=1,i=2;i<maxM;++i)inv[i]=mod-(ll)mod/i*inv[mod%i]%mod;
    for(i=1;i<maxM;++i)inv[i]=(ll)inv[i]*inv[i-1]%mod;
    int n=SZ(X);
    int maxk=K;
    int tot=0;
    p[++tot]=Node(0,0,0);
    p[++tot]=Node(xFinish,yFinish,0);
    for(i=0;i<n;++i){
      p[++tot]=Node(X[i],Y[i],val[i]);
    }
    for(i=0;i<n;++i){
      int x=X[i]+val[i],y=Y[i];
      for(j=1;j<=tot;++j)if(x==p[j].x&&y==p[j].y)break;
      if(j>tot)p[++tot]=Node(x,y,0);
      x=X[i],y=Y[i]+val[i];
      for(j=1;j<=tot;++j)if(x==p[j].x&&y==p[j].y)break;
      if(j>tot)p[++tot]=Node(x,y,0);
    }
    sort(p+1,p+1+tot,cmp);
    for(i=1;i<=tot;++i){
      for(j=i+1;j<=tot;++j){
        for(k=0;k<=maxk;++k){
          f[i][j][k]=0;
          g[i][j][k]=0;
        }
      }
    }
 	  for(k=0;k<=maxk;++k){
      for(int r=1;r<=tot;++r){
        for(int l=r-1;l;--l)if(p[l].y<=p[r].y){
          if(!p[l].v){
            g[l][r][k]=All(p[r].x-p[l].x,p[r].y-p[l].y,k);
            for(i=l+1;i<r;++i)if(p[i].v&&p[i].y>=p[l].y&&p[i].y<=p[r].y){
              for(j=0;j<=k;++j){
                add(g[l][r][k],mod-(ll)g[l][i][j]*All(p[r].x-p[i].x,p[r].y-p[i].y,k-j)%mod);
                add(f[l][r][k],(ll)g[l][i][j]*f[i][r][k-j]%mod);
              }
            }
            add(f[l][r][k],g[l][r][k]);
          }else{
            for(i=l+1;i<=r;++i){
              if(p[i].x==p[l].x+p[l].v&&p[i].y==p[l].y){
                add(f[l][r][k],i==r?(k==0):f[i][r][k]);
              }
              if(p[i].x==p[l].x&&p[i].y==p[l].y+p[l].v){
                add(f[l][r][k],i==r?(k==0):f[i][r][k]);
              }
            }
          }
        }
      }
    }
    for(i=1;i<=tot;++i)if(p[i].x==xFinish&&p[i].y==yFinish)break;
    int end=i,ans=0;
    for(i=0;i<=maxk;++i)add(ans,f[1][end][i]);
    return ans;
  }
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; int Arg5 = 2; int Arg6 = 2; verify_case(0, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arr0[] = {}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; int Arg5 = 3; int Arg6 = 14; verify_case(1, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arr0[] = {2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; int Arg5 = 3; int Arg6 = 18; verify_case(2, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arr0[] = {1, 3, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; int Arg4 = 5; int Arg5 = 4; int Arg6 = 210; verify_case(3, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arr0[] = {1, 19, 20, 21, 21, 21, 20, 19, 19}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 11, 11, 11, 10, 9, 9, 9, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 2, 2, 2, 2, 2, 2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 20; int Arg4 = 10; int Arg5 = 4; int Arg6 = 1778; verify_case(4, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_5() { int Arr0[] = {1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 391012, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] =  {1000000, 106, 1, 998765, 3977, 14632, 45, 998762, 998762, 48119, 998764, 99917, 256792, 504613, 164302, 9005, 752037, 992193, 841, 998761}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1237, 735, 998762, 2, 4978, 998763, 803, 1, 2, 11374, 1, 3, 517344, 103689, 295891, 90912, 246725, 3741, 2, 29}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; int Arg4 =998763; int Arg5 = 9; int Arg6 = 5; verify_case(5, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	NumberLabyrinthDiv1 ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
