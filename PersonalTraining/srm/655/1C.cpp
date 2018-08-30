/*
先求出蓝点的凸包，相当于选出若干红点完全包裹住这个凸包的概率
对于凸包内的红点肯定不用考虑，对于任意凸包外的红点，必定存在恰好两条切线
这可以类比过圆外一点作圆的两条切线，如果凸包是一个圆，那么选出的红点合法当且仅当这些切线对应的弧覆盖了整个圆周
凸包的情形也类似，过交点做切线的垂线，两条垂线交于一点形成一个角，选出的红点合法当且仅当这些角覆盖了2*PI
将环倍长转换成序列上的问题
f[now][l][r][has]表示将所有区间按左端点排序后，当前正在选第now个，前面都已经确定好
l,r表示当前区间的左右端点，has表示之前有没有选过至少一个区间
枚举每个区间选货不选即可
时间复杂度O(n^3)
*/
//#line 2 "BichromeSky.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=105;
const double PI=acos(-1.0);
const double eps=1e-10;
int sgn(double x){
  if(x>eps)return 1;
  if(x<-eps)return -1;
  return 0;
}
struct P{
  double x,y;
  P(){}P(double _x,double _y){x=_x,y=_y;}
  P operator-(P t){return P(x-t.x,y-t.y);}
  P operator+(P t){return P(x+t.x,y+t.y);}
	void print(){printf("[%.2lf %.2lf] ",x,y);}
}red[maxN],blue[maxN],con[maxN];
struct Info{
  double l,r,p;
  Info(){}Info(double _l,double _r,double _p){l=_l,r=_r,p=_p;}
}que[maxN];
bool cmpxy(P a,P b){
  if(!sgn(a.x-b.x))return a.y<b.y;
  return a.x<b.x;
}
double cross(P a,P b){
  return a.x*b.y-a.y*b.x;
}
int convexHull(P a[],P b[],int n){
  static P q[maxN];
  int i,j,t=0;
  sort(a+1,a+1+n,cmpxy);
  for(i=1;i<=n;++i){
    for(;t>1&&sgn(cross(a[i]-q[t],q[t]-q[t-1]))<=0;--t);
    q[++t]=a[i];
  }
  int tt=t;
  for(i=n-1;i;--i){
    for(;t>tt&&sgn(cross(a[i]-q[t],q[t]-q[t-1])<=0);--t);
    q[++t]=a[i];
  }
  b[0]=q[t-1];
  for(i=1;i<=t;++i)b[i]=q[i];
  return t-1;
}
double calArea(P a[],int n,P s){
  double res=0;
  for(int i=1;i<=n;++i)res+=fabs(cross(a[i]-s,a[i+1]-s));
  return res;
}
int tot;
int vis[maxN][maxN][maxN][2];
double f[maxN][maxN][maxN][2];
double dp(int now,int l,int r,int has){
	//if(now>tot)return 0;
	if(que[r].r-que[l].l+eps>2*PI)return 1;
  if(now>tot)return 0;
	if(vis[now][l][r][has])return f[now][l][r][has];
	double res=0;
	if(!has){
		res+=que[now].p*dp(now+1,now,now,1);
	}else{
		if(que[now].l-eps>que[r].r){
			res+=que[now].p*dp(now+1,now,now,1);
		}else{
			int _r=que[now].r>que[r].r?now:r;
			res+=que[now].p*dp(now+1,l,_r,1);
		}
	}
	res+=(1.0-que[now].p)*dp(now+1,l,r,has);
	vis[now][l][r][has]=1;
	//printf("f %d %d %d %d : %.2lf\n",now,l,r,has,res);
	return f[now][l][r][has]=res;	
}
bool cmpl(Info a,Info b){
	if(!sgn(a.l-b.l))return a.r<b.r;
	return a.l<b.l;
}
class BichromeSky {
	public:  
	double totallyCovered(vector <int> redX, vector <int> redY, vector <int> prob, vector <int> blueX, vector <int> blueY)  {  
		// $CARETPOSITION$  
    int i,j,k;
    int rn=SZ(redX);
    int bn=SZ(blueX);
    for(i=0;i<rn;++i)red[i+1]=P(redX[i],redY[i]);
    for(i=0;i<bn;++i)blue[i+1]=P(blueX[i],blueY[i]);
    int cn=convexHull(blue,con,bn);
		//printf("con %d\n",cn);for(i=1;i<=cn;++i)con[i].print();puts("");
    double areac=calArea(con,cn,con[1]);
    tot=0;
    for(i=1;i<=rn;++i){
      double areat=calArea(con,cn,red[i]);
      if(!sgn(areat-areac))continue;
      P l,r;
      for(j=1;j<=cn;++j){
        int x=sgn(cross(red[i]-con[j],con[j-1]-con[j]));
        int y=sgn(cross(con[j]-red[i],con[j+1]-con[j]));
        if(x>=0&&y<=0)l=P(-(red[i]-con[j]).y,(red[i]-con[j]).x);
				if(x<=0&&y>=0)r=P(-(con[j]-red[i]).y,(con[j]-red[i]).x);
      }
      double lv=atan2(l.y,l.x);
      double rv=atan2(r.y,r.x);
      if(rv<lv)rv+=2*PI;
      que[++tot]=Info(lv,rv,0.001*prob[i-1]);
			//printf("que %.2lf %.2lf  %.2lf\n",lv/2/PI,rv/2/PI,0.001*prob[i-1]);
    }
		sort(que+1,que+1+tot,cmpl);
		for(i=0;i<=tot;++i){
			for(j=0;j<=tot;++j){
				for(k=0;k<=tot;++k){
					for(int t=0;t<2;++t){
						f[i][j][k][t]=0;
						vis[i][j][k][t]=0;
					}
				}
			}
		}
		double ans=dp(1,0,0,0);
    return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,-3,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {400,500,600}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,0,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,0}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.12; verify_case(0, Arg5, totallyCovered(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arr0[] = {3,-3,3,-3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,3,-3,-3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {200,300,400,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,1,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {-1,-2,-2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.088; verify_case(1, Arg5, totallyCovered(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arr0[] = {3,-3,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {400,500,600}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,0,-1,123456}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,0,-654321}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.0; verify_case(2, Arg5, totallyCovered(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arr0[] = {0,-2,-3,-4,-3,-2,0,2,3,4,3,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,3,2,0,-2,-3,-4,-3,-2,0,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {501,502,503,504,505,506,507,508,509,510,511,512}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,-1,-1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,1,-1,-1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.6555037822772468; verify_case(3, Arg5, totallyCovered(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arr0[] = {0,1,-3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,-2,-2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {200,300,400,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,-1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,-1,-1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.06; verify_case(4, Arg5, totallyCovered(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arr0[] = {10,-17,12,-11,-13,-10,-15,14,-4,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8,17,-13,-19,-14,11,17,8,-8,-15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {412,360,656,876,984,160,368,873,223,128}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-9,-3,6,-9,-5,4,-3,10,-7,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {-6,10,10,-9,-10,-6,2,-10,-9,6}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.34037052019900405; verify_case(5, Arg5, totallyCovered(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	BichromeSky ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
