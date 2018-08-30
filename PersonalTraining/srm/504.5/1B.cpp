//#line 2 "TheJackpotDivOne.cpp"  
/*
每n轮全局最小和全局最大的差至少减半，所以直接暴力跑到全部都相等然后直接分
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

class TheJackpotDivOne  {
  public:  
  vector<long long> find(vector<long long> money, long long jackpot){  
    //$CARETPOSITION$ 
    int i,j;
    int n=SZ(money);
    ll m=jackpot;
    vector<ll>ans;
    if(n==1)return ans.pb(money[0]+m),ans;
    multiset<ll>q;
    ll x=0,y=0;
    for(i=0;i<n;++i){
      q.insert(money[i]);
      x+=money[i]/n;
      y+=money[i]%n;
      if(y>=n)y-=n,++x;
    }
    for(;m&&*q.begin()!=*q.rbegin();){
      ll low=*q.begin();
      ll add=min(m,x-low+1);
      y+=add;
      x+=y/n;
      y%=n;
      q.erase(q.begin());
      q.insert(low+add);
      assert(1.0*low+add<9e18);
      m-=add;
    }
    for(;SZ(q);){
      ans.pb(*q.begin());
      q.erase(q.begin());
    }
    if(m){
      for(i=0;i<n;++i)ans[i]+=m/n;
      for(i=0;i<m%n;++i)ans[n-1-i]++;
    }
    return ans;
  }  
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long Arr0[] = {1, 2, 3, 4}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; long Arr2[] = {2, 3, 3, 4 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {4}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 7LL; long Arr2[] = {11 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { long Arr0[] = {4, 44, 7, 77}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 47LL; long Arr2[] = {24, 34, 44, 77 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {4, 10, 8, 3, 6, 5, 8, 3, 7, 5}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1000LL; long Arr2[] = {105, 106, 106, 106, 106, 106, 106, 106, 106, 106 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
        TheJackpotDivOne ___test;  
        ___test.run_test(-1);  
        return 0;  
}  
// END CUT HERE  
