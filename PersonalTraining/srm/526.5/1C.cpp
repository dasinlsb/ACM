/*
这个题题意组合的真的是毫无瑕疵..
原题所求可以看作，有n个点，每个点有二维坐标(x[i],y[i])，以及价值mathes[i]
要求选出一个数量最多的非空点集，要求这个点集没有任何一个非空子集的价值异或和为0，在满足上述情况下最小化(\sum_{}x_i)*(\sum_{}y_i)
容易联想到最小乘积生成树，设X=\sum_{}x_i,Y=\sum_{}y_i，那么任意一种合法方案都可以看作新的二维平面上的一个点(X,Y)
接下来直接套最小乘积生成树，求合法方案时直接排好序从小到大插入线性基，这样每次选出的点集大小肯定是最大的且满足权值和最小
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
const int maxb=20;
int n;
long long ans;
struct Node{
  int x,y,s;long long v;
  Node(){}
  Node(int _x,int _y,long long _v){x=_x,y=_y,v=_v;}
  bool operator <(const Node&t)const{
    return v<t.v;
  }
}env[maxn];
struct P{
  long long x,y;
  P(){x=y=0;}
  P(long long _x,long long _y){x=_x,y=_y;}
  P operator-(P t){return P(x-t.x,y-t.y);}
  void print(){printf("p[%lld,%lld]\n",x,y);}
};
long long cross(P a,P b){
  return a.x*b.y-a.y*b.x;
}
P calc(){
  static int pos[maxb];
  memset(pos,0,sizeof pos);
  sort(env,env+n);
  P res;
  int cnt=0;
  for(int i=0;i<n;i++){
    int cur=env[i].s;
    for(int j=maxb-1;~j;j--)if(cur>>j&1){
      if(pos[j])cur^=pos[j];
      else{
        pos[j]=cur;
        res.x+=env[i].x;
        res.y+=env[i].y;
        ++cnt;
        break;
      }
    }
  }
  return res;
}
/*
(a.x,a.y)
(b.x,b.y)
(c.x,c.y)

(b.x-c.x,b.y-c.y)*(a.x-c.x,a.y-c.y)
(b.x-c.x)*(a.y-c.y)-(b.y-c.y)*(a.x-c.x)
-bx*cy-cx*ay+cx*cy-(-by*cx-cy*ax+cx*cy)
cx*(by-ay)+cy*(ax-bx)[maxi]

\sum_{}red'_i+
*/
void solve(P a,P b){
  for(int i=0;i<n;i++){
    env[i].v=-(env[i].x*(b.y-a.y)+env[i].y*(a.x-b.x));
  }
  P c=calc();
  ans=min(ans,c.x*c.y);
  if(cross(b-c,a-c)<=0)return;
  solve(a,c);
  solve(c,b);
}
class MagicMatchesGame{
	public:
	long long minimumArea(vector <int> matches, vector <int> red, vector <int> blue){
		// $CARETPOSITION$
    n=matches.size();
    for(int i=0;i<n;i++){
      env[i].x=red[i];
      env[i].y=blue[i];
      env[i].s=matches[i];
    }
    for(int i=0;i<n;i++){
      env[i].v=env[i].x;
    }
    P pl=calc();
    for(int i=0;i<n;i++){
      env[i].v=env[i].y;
    }
    P pr=calc();
    ans=min(pl.x*pl.y,pr.x*pr.y);
    solve(pl,pr);
    return ans;

	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 24LL; verify_case(0, Arg3, minimumArea(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {9,8,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 153LL; verify_case(1, Arg3, minimumArea(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,5,6,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20,11,12,23,21,52,65}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {23,10,31,18,13,10,13}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 2255LL; verify_case(2, Arg3, minimumArea(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1037, 2220, 6908, 4179, 4243, 4396, 679, 179, 163, 818, 9767, 5199, 3973, 2065, 8060}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {724, 123, 178, 262, 628, 981, 882, 814, 752, 495, 906, 904, 265, 329, 470}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {664, 134, 254, 798, 290, 753, 941, 264, 200, 369, 547, 628, 120, 833, 928}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 42628758LL; verify_case(3, Arg3, minimumArea(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {10095, 16913, 10198, 12528, 15264, 19224, 16442, 14595, 12060, 11858, 17900, 19304, 10619, 15818, 11670}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9419, 9448, 9722, 9030, 9591, 9451, 9871, 9124, 9012, 9047, 9024, 9984, 9163, 9852, 9203}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {9706, 9436, 9454, 9585, 9592, 9145, 9356, 9797, 9523, 9032, 9178, 9472, 9594, 9637, 9256}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 17324432487LL; verify_case(4, Arg3, minimumArea(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {1000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 100000000LL; verify_case(5, Arg3, minimumArea(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	MagicMatchesGame ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
