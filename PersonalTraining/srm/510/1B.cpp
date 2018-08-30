/*
预处理所有lucky数然后双指针扫一下即可
双指针有点难写，可以直接枚举两个区间判断是否可行
*/
//#line 2 "TheLuckyGameDivOne.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=(1<<12)+5;
int pre[maxN];
ll ten[15];
pair<ll,int>q[maxN];
class TheLuckyGameDivOne {
	public:  
	int find(long long a, long long b, long long jLen, long long bLen)  {  
		// $CARETPOSITION$  
    int i,j;
    int n=0;
    for(ten[0]=i=1;i<=10;++i)ten[i]=ten[i-1]*10;
    for(int bit=1;bit<=10;++bit){
      for(int S=0;S<1<<bit;++S){
        ll t=0;
        for(i=0;i<bit;++i){
          t+=ten[i]*(((1<<i)&S)?4:7);
        }
        ll l=max(1LL,t-bLen+1),r=t+1;
        q[++n]=make_pair(l,1);
        q[++n]=make_pair(r,-1);
      }
    }
    q[++n]=make_pair(1,0);
    sort(q+1,q+1+n);
    ll len=jLen-bLen+1;
    for(j=1,i=2;i<=n;++i)if(q[i].fi==q[j].fi)q[j].se+=q[i].se;else q[++j]=q[i];n=j;
    for(i=1;i<=n;++i)q[i].se+=q[i-1].se;
    q[n+1].fi=(ll)1e11;
    int ans=0;
    for(i=1;i<=n;++i){
      int res=q[i].se;
      for(j=i;j<=n;++j){
        res=min(res,q[j].se);
        ll l=a,r=b-bLen+1;
        l=max(l,q[i].fi);r=min(r,q[j+1].fi-1);
        if(l>=q[i+1].fi||r<q[j].fi)continue;
        if(len<=q[j].fi-q[i+1].fi||len>r-l+1)continue;
        //printf("q %lld %d\n",q[i].fi,q[j].fi);
        //printf("goto %lld %lld %lld\n",l,r,res);
        ans=max(ans,res);
      }
    }
    return ans;
  }
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 10LL; long long Arg2 = 2LL; long long Arg3 = 1LL; int Arg4 = 0; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 100LL; long long Arg2 = 100LL; long long Arg3 = 100LL; int Arg4 = 6; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { long long Arg0 = 4LL; long long Arg1 = 8LL; long long Arg2 = 3LL; long long Arg3 = 2LL; int Arg4 = 1; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 100LL; long long Arg2 = 75LL; long long Arg3 = 50LL; int Arg4 = 2; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
};

// BEGIN CUT HERE
int main(){
	TheLuckyGameDivOne ___test;
 	___test.run_test(-1);
  // int res=___test.find(77,474,96,65);
	return 0;
}
// END CUT HERE  
