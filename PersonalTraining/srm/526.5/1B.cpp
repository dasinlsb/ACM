/*
这题可以把平方差分掉然后递推，不过有一种我感觉更有意思的方法
对于\sum_{}x^2可以换个角度考虑，相当于关于x的点值数组自己和自己做一个点积然后求和
也就是说就相当于求有多少点对(i,j)满足第i个ball和第j个ball落在同一个格子内
对于不同的魔法师，他们的施法肯定是相互独立的，range小的那个人的任意一个球不管落在哪里，range大的那个人都有1/area的概率落在那里，这是一个点对的答案，他们之间一共有amount[i]*amount[j]个点对
对于同一个魔法师，假设i!=j,那么他的第i个ball和第j个ball显然也是独立的，计算方法和上面一样，但是如果i==j，那么这个点对一定落在同一个格子，也就是一定会贡献1的概率，这样的点对(i,i)对于这个魔法师x来说有amount[x]个
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
const int maxm=10005;
int calc(int x){
  return (x*2+1)*(x*2+1);
}
class MagicBlizzard{
	public:
	double expectation(vector <int> range, vector <int> amount){
		// $CARETPOSITION$
    double ans=0;
    for(int i=0;i<range.size();i++){
      for(int j=0;j<range.size();j++){
        if(i!=j){
          ans+=1.0*amount[i]*amount[j]/calc(max(range[i],range[j]));
        }else{
          ans+=amount[i]+1.0*amount[i]*(amount[i]-1)/calc(range[i]);
        }
      }
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.2222222222222223; verify_case(0, Arg2, expectation(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.666666666666667; verify_case(1, Arg2, expectation(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {5,2,6,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 8.46525111252384; verify_case(2, Arg2, expectation(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {7,11,2,13,3,19,5,17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {16,8,4,15,12,9,10,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 98.55659436211914; verify_case(3, Arg2, expectation(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.0E10; verify_case(4, Arg2, expectation(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	MagicBlizzard ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
