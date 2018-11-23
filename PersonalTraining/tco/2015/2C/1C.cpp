/*
jls博客里好像有复杂度正确的做法，不过只看懂了一部分还是不会，最后看了Petr的代码，原来是爆搜剪枝过的
如果已知[0,2^k)的轨迹S及其终点P，那么[2^k,2^{k+1})的轨迹肯定是S把起点移到P，形态逆时针旋转90度
点在2^k-1时刻所在的位置同样可以根据上面观察来递推
所以问题转化为在[0,2^k)的轨迹中查找(x,y)是否被染黑，可以分别假设(x,y)在[0,2^k)以及在[2^k,2^{k+1})上来递归到两个规模更小的子问题
打表可以发现点在2^k时刻所在点的x,y坐标的绝对值上界大约是2^{k/2}，可以以此来剪枝就能过了...
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxs=62;
struct P{
  long long x,y;
  P(){}
  P(long long _x,long long _y){x=_x,y=_y;}
  P rotn(){return P(-y,x);}
  P operator +(const P&t){return P(x+t.x,y+t.y);}
  void print(){printf("p[%lld,%lld]\n",x,y);}
}p[maxs];
int calc(int x,int y,int t,long long T){
  if(T<=0)return 0;
  if(t==1){
    return y == 0 && (x == 0 || x == 1 && T>1);
  }
  long long bound=1LL<<(t+1>>1);
  if(abs(x)>bound || abs(y)>bound)return 0;
  if(calc(x,y,t-1,T))return 1;
  return calc(y-p[t-1].y,p[t-1].x-x,t-1,T-(1LL<<t-2));
}
class PopcountRobot{
	public:
	int countBlack(long long T, int Q, int M, int x, int y){
		// $CARETPOSITION$
    // clock_t _st=clock();
    p[1]=P(1,0);
    for(int i=2;i<maxs;i++){
      p[i]=p[i-1]+p[i-1].rotn();
    }
    // for(int i=-5;i<=-5;i++){
    //   for(int j=-5;j<=-5;j++){
    //     printf("check %d %d %d\n",i,j,calc(i,j,maxs-1,25));
    //   }
    // }
    int ans=0;
    for(int i=0;i<Q;i++){
      if(calc(x,y,maxs-1,T)) ans++;
      x = (int)((1LL*(x + M) * 7180087LL + 5205425) % (2 * M + 1) - M);
	    y = (int)((1LL*(y + M) * 6132773LL + 9326231) % (2 * M + 1) - M);
    }
    // clock_t _ed=clock();printf("time %.5lf\n",1.0*(_ed-_st)/CLOCKS_PER_SEC);
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 5LL; int Arg1 = 10; int Arg2 = 2; int Arg3 = -1; int Arg4 = -2; int Arg5 = 2; verify_case(0, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { long long Arg0 = 30LL; int Arg1 = 500000; int Arg2 = 5; int Arg3 = 3; int Arg4 = 4; int Arg5 = 0; verify_case(1, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { long long Arg0 = 2015LL; int Arg1 = 500000; int Arg2 = 50; int Arg3 = 12; int Arg4 = 34; int Arg5 = 40000; verify_case(2, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { long long Arg0 = 1000000000000000000LL; int Arg1 = 500000; int Arg2 = 1000000000; int Arg3 = 94296562; int Arg4 = -42562967; int Arg5 = 32306; verify_case(3, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { long long Arg0 = 720875421873LL; int Arg1 = 500000; int Arg2 = 312; int Arg3 = -288; int Arg4 = 36; int Arg5 = 68000; verify_case(4, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	PopcountRobot ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
