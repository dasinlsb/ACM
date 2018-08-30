/*
每一维显然独立，考虑一维线段上有20个关键点，起点为0，终点为final，每次可以沿某个关键点翻折，每个关键点只能用一次
最优解肯定是按一定顺序翻折然后最后暴力移动，如果依次沿a_1,a_2...翻折，最终位置肯定是2*a_1-2*a_2+2*a_3-...
meet in the middle优化一下3^20的枚举即可
*/
//#line 2 "Reflections.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const ll inf=(ll)1e15;
inline ll ask(set<ll>&S,ll x){
  static set<ll>::iterator it;
  ll res=inf;
  it=S.lower_bound(x);
  if(it!=S.end())res=min(res,(*it)-x);
  if(it!=S.begin()){
    it--;
    res=min(res,x-(*it));
  }
  return res;
}
int bit[1<<20];
ll solve(VI&pos,ll fin){
  static set<ll>set_mid[15][15];
  if(SZ(pos)==0)return fin>0?fin:-fin;
  int n=SZ(pos);
  int num[2];
  num[0]=n<12?n:12;
  num[1]=n-num[0];
  for(int i=0;i<=num[0];i++){
    for(int j=0;j<=num[0];j++){
      set_mid[i][j].clear();
    }
  }
  for(int S=0;S<1<<num[0];S++){
    for(int S2=S;;S2=(S2-1)&S){
      int S1=S^S2;
      ll res=0;
      for(int i=0;i<num[0];i++){
        if((1<<i)&S2)res+=2LL*pos[i];
        if((1<<i)&S1)res-=2LL*pos[i];
      }
      set_mid[bit[S2]][bit[S1]].insert(res);
      if(S2==0)break;
    }
  }
  ll ans=inf;
  for(int S=0;S<1<<num[1];S++){
    for(int S2=S;;S2=(S2-1)&S){
      int S1=S^S2;
      ll res=0;
      for(int i=0;i<num[1];i++){
        if((1<<i)&S2)res+=2LL*pos[i+num[0]];
        if((1<<i)&S1)res-=2LL*pos[i+num[0]];
      }
      for(int i=0;i<=num[0];i++){
        for(int j=0;j<2;j++){
          int k=bit[S2]-bit[S1]+i-j;
          if(k>=0&&k<=num[0])ans=min(ans,i+k+bit[S2]+bit[S1]+ask(set_mid[i][k],fin-res));
        }
      }
      if(S2==0)break;
    }
  }
  return ans;
}
class Reflections {
	public:  
	long long minimumMoves(vector <int> mirrorX, vector <int> mirrorY, vector <int> mirrorZ, vector <int> finalPosition)  {  
		// $CARETPOSITION$  
    for(int i=1;i<1<<20;i++)bit[i]=bit[i>>1]+i%2;
    ll ans=solve(mirrorX,finalPosition[0]);
    ans+=solve(mirrorY,finalPosition[1]);
    ans+=solve(mirrorZ,finalPosition[2]);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3, 0, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 3LL; verify_case(0, Arg4, minimumMoves(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {-5, 1, 4, 2, 3, 6, -6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {9, 0, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 2LL; verify_case(1, Arg4, minimumMoves(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 0, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 4LL; verify_case(2, Arg4, minimumMoves(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {10, 12, -1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 5LL; verify_case(3, Arg4, minimumMoves(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {8, -3, 21}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-7, -2, -1, 7, 14}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {40, -4, 31}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 10LL; verify_case(4, Arg4, minimumMoves(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	Reflections ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
