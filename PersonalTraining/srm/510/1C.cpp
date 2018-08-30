/*
设n=\sum_{0<=i<=k}a_i*B^i,讨论k的大小
当k>=3时,B<=n^{1/3}，直接暴力枚举即可
当k==2,1时从大到小枚举a_i加点剪枝解
当k==0时判一下无解
*/
//#line 2 "TheLuckyBasesDivOne.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=(1<<17)+5;
int tot;
ll que[maxN];
int bin(ll v){
  int l=1,r=tot;
  for(;l<r;){
    int mid=(l+r)/2;
    if(v>que[mid])l=mid+1;
    else r=mid;
  }
  return l>=1&&l<=tot&&que[l]==v?l:0;
}
ll solve1(ll n){
  ll res=0;
  for(int i=1;;++i){
    ll lim=n-que[i]*que[i];
    if(lim<0)break;
    for(int j=1;j<=tot&&que[j]<=lim;++j){
      if((n-que[j])%que[i]==0){
        if((n-que[j])/que[i]>max(que[i],que[j]))++res;
      }
    }
  }
  //printf("solve1 %lld\n",res);
  return res;
}
int chk(ll a,ll b,ll c,ll n){
  double d=1.0*b*b-4.0*a*(c-n);
  if(d<-0.5)return 0;
  ll s=(-b+ll(sqrt(d+0.5)+0.5))/a/2;
  if(s>a&&s>b&&s>c&&a*s*s+b*s+c==n)return 1;--s;
  if(s>a&&s>b&&s>c&&a*s*s+b*s+c==n)return 1;
  return 0;
}
ll solve2(ll n){
  ll res=0;
  for(int i=1;;++i){
    ll lim=n-que[i]*que[i]*que[i];
    if(lim<0)break;
    for(int j=1;j<=tot;++j){
      ll xlow=max(que[i],que[j]);
      ll lim2=n-que[i]*xlow*xlow-que[j]*xlow;
      if(lim2<0)break;
      for(int k=1;k<=tot&&que[k]<=lim2;++k){
        ll xlow2=max(xlow,que[k]);
        if(que[i]*xlow2*xlow2+que[j]*xlow2+que[k]>n)break;
        if(chk(que[i],que[j],que[k],n))++res;
      }
    }
  }
  //printf("solve2 %lld\n",res);
  return res;
}
ll solve3(ll n){
  ll res=0;
  for(ll B=2;B*B*B<=n;++B){
    ll t=n;
    for(;t;t/=B){
      if(!bin(t%B))break;
    }
    if(!t)++res;
  }
  //printf("solve3 %lld\n",res);
  return res;
}
ll ten[17];
class TheLuckyBasesDivOne {
	public:  
	long long find(long long n){  
		// $CARETPOSITION$  
    //clock_t _stt=clock();
    int i,j,k;
    tot=0;
    for(ten[0]=i=1;i<=16;++i){
      ten[i]=ten[i-1]*10;
    }
    for(int bit=1;bit<=16;++bit){
      for(int S=0;S<1<<bit;++S){
        ll t=0;
        for(i=0;i<bit;++i){
          t+=ten[i]*(((1<<i)&S)?4:7);
        }
        que[++tot]=t;
      }
    }
    sort(que+1,que+1+tot);
    if(bin(n))return -1;
    ll ans=0;
    ans+=solve1(n);
    //clock_t _t1=clock();
    ans+=solve2(n);
    //clock_t _t2=clock();
    //printf("solve2 time %.3lf\n",1.0*(_t2-_t1)/CLOCKS_PER_SEC);
    ans+=solve3(n);
    //clock_t _enn=clock();
    //printf("%.3lf\n",1.0*(_enn-_stt)/CLOCKS_PER_SEC);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 255LL; long long Arg1 = 2LL; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { long long Arg0 = 474LL; long long Arg1 = -1LL; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { long long Arg0 = 13LL; long long Arg1 = 0LL; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { long long Arg0 = 4748LL; long long Arg1 = 5LL; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	TheLuckyBasesDivOne ___test;  
 	___test.run_test(-1);  
  printf("%I64d\n",___test.find(100458529411078LL));
	return 0;  
}  
// END CUT HERE  
