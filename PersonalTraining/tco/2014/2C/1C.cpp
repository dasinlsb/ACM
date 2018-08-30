/*
确定序列定义域和值域可以看作匹配问题
对于三元组(A_i,B_i,ans_i)，可以将所有k<=ans_i向[A_i,B_i连边，通过最大流验证合法性
但是当相等的ans有多个区间的时候要特殊处理，答案肯定是区间交，也就是ans_i这个单独的点只能向区间交连边
而所有k满足k<ans_i在不和其他限制冲突的前提下和区间并连边
*/
//#line 2 "InverseRMQ.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int inf=((int)1e9)+5;
namespace ISAP{
  const int maxN=200;
  const int maxM=maxN*maxN*2;
  int ed,tot,S,T,fir[maxN],h[maxN],gap[maxN];
  struct Edge{int v,w,nxt;}e[maxM];
  void adde(int x,int y,int z){
    //printf("adde %d %d %d\n",x,y,z);
    e[++ed].v=y;e[ed].w=z;e[ed].nxt=fir[x];fir[x]=ed;
    e[++ed].v=x;e[ed].w=0;e[ed].nxt=fir[y];fir[y]=ed;
  }
  int sap(int x,int flow){
    if(x==T)return flow;
    int minh=tot,dec=0;
    for(int i=fir[x];i;i=e[i].nxt)if(e[i].w){
      if(h[x]==h[e[i].v]+1){
        int tmp=sap(e[i].v,min(flow-dec,e[i].w));
        e[i].w-=tmp;e[i^1].w+=tmp;dec+=tmp;
        if(h[S]>=tot)return dec;
        if(dec==flow)return flow;
      }
      minh=min(minh,h[e[i].v]);
    }
    if(!dec){
      if(!(--gap[h[x]]))h[S]=tot;
      gap[h[x]=minh+1]++;
    }
    return dec;
  }
  void clear(){
    ed=1;tot=0;
    fill(fir,fir+maxN,0);
    fill(gap,gap+maxN,0);
    fill(h,h+maxN,0);
  }
  int maxFlow(){
    int res=0;
    for(gap[0]=tot;h[S]<tot;res+=sap(S,inf));
    return res;
  }
}
struct Info{
  int x,v,t;
  Info(){}Info(int _x,int _v,int _t){x=_x,v=_v,t=_t;}
  bool operator<(Info a)const{return x<a.x;}
};
bool cmpx(Info a,Info b){
  return a.x<b.x;
}
string YES="Possible";
string NO="Impossible";
const int maxN=55;
int qx[maxN*2],qv[maxN],lmin[maxN],lmax[maxN],rmin[maxN],rmax[maxN],del[maxN*2];
class InverseRMQ {
	public:
  //using namespace ISAP;
	string possible(int n, vector <int> A, vector <int> B, vector <int> ans)  {  
		// $CARETPOSITION$  
    int i,j;
    int m=SZ(A);
    int xn=0,vn=0;
    for(i=0;i<m;++i){
      qx[++xn]=A[i];
      qx[++xn]=B[i]+1;
      qv[++vn]=ans[i];
    }
    qx[++xn]=1;
    qx[++xn]=n+1;
    qv[++vn]=n+1;
    sort(qx+1,qx+1+xn);
    sort(qv+1,qv+1+vn);
    xn=unique(qx+1,qx+1+xn)-qx-1;
    vn=unique(qv+1,qv+1+vn)-qv-1;
    //printf("xn %d , vn %d\n",xn,vn);
    ISAP::clear();
    ISAP::tot=xn+vn*2+10;
    ISAP::S=++ISAP::tot;
    ISAP::T=++ISAP::tot;
    for(i=1;i<=vn;++i){
      lmax[i]=rmax[i]=1;
      lmin[i]=rmin[i]=n;
      for(j=0;j<m;++j)if(ans[j]==qv[i]){
        lmax[i]=max(lmax[i],A[j]);
        lmin[i]=min(lmin[i],A[j]);
        rmax[i]=max(rmax[i],B[j]);
        rmin[i]=min(rmin[i],B[j]);
      }
      if(lmax[i]>rmin[i])return NO;
    }
    fill(del+1,del+1+xn,0);
    //printf("v ");for(i=1;i<=vn;++i)printf("%d ",qv[i]);puts("");
    //printf("x ");for(i=1;i<=xn;++i)printf("%d ",qx[i]);puts("");
    for(i=1;i<=vn;++i){
      ISAP::adde(ISAP::S,i*2-1+xn,qv[i]-qv[i-1]-1);
      if(i!=vn)ISAP::adde(ISAP::S,i*2+xn,1);
      for(j=1;j<xn;++j)if(!del[j]){
        ISAP::adde(i*2-1+xn,j,inf);
        if(i!=vn&&qx[j]>=lmax[i]&&qx[j+1]-1<=rmin[i]){
          ISAP::adde(i*2+xn,j,inf);
        }
      }
      for(j=1;j<xn;++j)if(qx[j]>=lmin[i]&&qx[j+1]-1<=rmax[i]){
        del[j]=1;
      }
    }
    for(i=1;i<xn;++i){
      ISAP::adde(i,ISAP::T,qx[i+1]-qx[i]);
    }
    int res=ISAP::maxFlow();
    return res==n?YES:NO;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {1,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,4,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,4,5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "Possible"; verify_case(0, Arg4, possible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,3,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "Impossible"; verify_case(1, Arg4, possible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 600; int Arr1[] = {1,101,201,301,401,501}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100,200,300,400,500,600}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {100,200,300,400,500,600}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "Possible"; verify_case(2, Arg4, possible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1000000000; int Arr1[] = {1234,1234}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5678,5678}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {10000,20000}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "Impossible"; verify_case(3, Arg4, possible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 8; int Arr1[] = {1,2,3,4,5,6,7,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,3,4,5,6,7,8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,8,2,5,6,3,7,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "Possible"; verify_case(4, Arg4, possible(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 1000000000; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000000000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {19911120}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arg4 = "Impossible"; verify_case(5, Arg4, possible(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	InverseRMQ ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
