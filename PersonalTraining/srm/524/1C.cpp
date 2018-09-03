/*
有个显然的结论是任意交换Front或Left中的元素的顺序对答案都是没有影响的
4|
3|
2|
1|
  _______
  1 1 2 4
不妨先将它们升序排列，形成类似上图的形式
首先它们必须共享相等的最大值，这会在右上角形成一个[a行b列矩形每行每列最大值都是v]的子问题，这个问题可以归类到接下来要讨论的更一般的问题中去，所以可以暂时不解决
接下来我们按值递减考虑，假设下一个值为v，有两种情况
一种是行列都有v，旋转一下差不多是下面这个图
###----|
###    | d
###____|
| |  c
| |b
---
a
这个问题可以表示为f[a][b][c][d][v]
而之前全局最大值形成的矩形可以用f[a][0][0][d][v]表示
还有一种就是只有行或只有列有v，这个可以用f[a][0][c][d][v]或f[a][b][0][d][v]表示
只要解决了f这个子问题，剩下的就是把每一部分的方案乘起来就行了
对于上图，可以从上往下递推，那么整个递推显然可以根据是否在a*b矩形上方分为两个阶段
考虑从第一阶段递推到第二阶段必须记录哪些信息，其实只要知道前d行递推完之后前a列中恰有x(0<=x<=a)列放了v方案g[x]即可
只要想清楚状态表示剩下的就是很基础的转移了
时间复杂度O(n^4)
*/
//#line 2 "AxonometricProjection.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxn=55;
const int mod=1000*1000*1000+9;
int comb[maxn][maxn];
int pw[10005][maxn];
void add(int&x,int y){
  if(x+=y,x>=mod)x-=mod;
}
int Pow(long long x,int y){
  long long t=1;
  for(;y;y>>=1){
    if(y&1)t=t*x%mod;
    x=x*x%mod;
  }
  return (int)t;
}
vector< int >calc_dp(int a,int c,int d,int v){
  static int f[maxn][maxn];
  memset(f,0,sizeof(f));
  f[0][0]=1;
  for(int i=0;i<d;i++){
    for(int j=0;j<=a;j++)if(f[i][j]){
      for(int out=0;out+j<=a;out++){
          int mul=1LL*comb[a-j][out]*pw[v][a-j-out]%mod*(pw[v+1][j+c]-(out==0)*pw[v][j+c]+mod)%mod;
          add(f[i+1][j+out],1LL*mul*f[i][j]%mod);
      }
    }
  }
  vector<int>result;  
  for(int i=0;i<=a;i++)result.push_back(f[d][i]);
  return result;
}
/*
###----|
###    | d
###----|
| |b  c
---
a
value=[0,v]
*/
int solve(int a,int b,int c,int d,int v){
  int result=0;
  if(b==0&&c==0){
    vector<int>f=calc_dp(a,0,d,v);
    result=f[a];
  }
  else if(a==0){
    result=Pow((pw[v+1][c]-pw[v][c]+mod)%mod,d);
  }
  else if(d==0){
    result=Pow((pw[v+1][b]-pw[v][b]+mod)%mod,a);
  }else{
    vector<int>f=calc_dp(a,c,d,v);
    for(int i=0;i<=a;i++){
      int mul=Pow((pw[v+1][b]-pw[v][b]+mod)%mod,a-i);
      mul=1LL*mul*Pow(pw[v+1][b],i)%mod;
      add(result,1LL*f[i]*mul%mod);
    }
  }
  //printf("solve %d %d %d %d %d : %d\n",a,b,c,d,v,result);
  return result;
}
class AxonometricProjection {
	public:  
	int howManyWays(vector <int> heightsOfLeftView, vector <int> heightsOfFrontView)  {  
    for(int i=0;i<10005;i++){
      pw[i][0]=1;
      for(int j=1;j<55;j++)pw[i][j]=1LL*pw[i][j-1]*i%mod;
    }
		// $CARETPOSITION$  
    comb[0][0]=1;
    for(int i=1;i<maxn;i++){
      comb[i][0]=1;
      for(int j=1;j<=i;j++){
        comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
      }
    }
    vector<int >&Left=heightsOfLeftView;
    vector<int >&Front=heightsOfFrontView;
    // Front.clear();
    // Left.clear();
    // Front.push_back(1);
    // Front.push_back(2);
    // Left.push_back(1);
    // Left.push_back(2);
    sort(Left.begin(),Left.end());
    sort(Front.begin(),Front.end());
    if(Front.back()!=Left.back())return 0;
    int p1=Front.size()-1,p2=Left.size()-1;
    int result=1;
    for(;~p1||~p2;){
      int now_v;
      if(p1<0)now_v=Left[p2];
      else if(p2<0)now_v=Front[p1];
      else now_v=max(Front[p1],Left[p2]);
      int t1=p1,t2=p2;
      for(;t1>=0&&Front[t1]==now_v;t1--);
      for(;t2>=0&&Left[t2]==now_v;t2--);
      result=1LL*result*solve(p1-t1,(int)Left.size()-1-p2,(int)Front.size()-1-p1,p2-t2,now_v)%mod;
      p1=t1,p2=t2;
    }
    return result;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(0, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {50,50,50,50,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {524,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 104060401; verify_case(1, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,2,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,2,4,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 429287; verify_case(3, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {5,2,4,52,24,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,20,24,500,504,520,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 97065655; verify_case(4, Arg2, howManyWays(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AxonometricProjection ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
