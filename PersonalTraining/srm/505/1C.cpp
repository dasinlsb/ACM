#line 2 "PerfectSequences2.cpp"  
/*
如果全部数都大于2的话，只可能是{2,2}，所以可以考虑分类讨论是否有0,1,-1，直接爆搜出方案
爆搜的时候一个简单但很有效的剪枝是abs(mul)-abs(sum)>n-k+1，k表示当前已经确定了k位 
*/
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
#define MP make_pair
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int N=55;
const ll inf=(ll)1e11;
const ll S=50;
int n;ll ans,a[N],b[N];
ll Abs(ll x){return x>0?x:-x;}
map<pair<pair<ll,ll>,int>,ll> f;
ll dfs(ll sum,ll mul,ll pre,int k){
	if(k>n)return sum==mul?0:inf;
	if(Abs(mul)-Abs(sum)>n-k+1)return inf;
	pair<pair<ll,ll>,int>now=MP(MP(sum,mul),k);
	if(f.count(now))return f[now];
	ll res=inf;
	if(a[k]&&mul*a[k]<=(ll)1e9)res=min(res,dfs(sum+a[k],mul*a[k],a[k],k+1));
	for(ll i=-S;i<=S;++i)if(i)res=min(res,dfs(sum+i,mul*i,i,k+1)+Abs(a[k]-i));
	return f[now]=res;
}
class PerfectSequences2 {
	public:
	long long minimumMoves(vector<int> seq){
		int i,j,k;
		ans=inf;f.clear();
		n=SZ(seq);
		if(n==1)return 0;
    for(i=1;i<=n;++i)a[i]=seq[i-1];
    sort(a+1,a+1+n);
    ll s=0;
    for(i=1;i<=n;++i)s+=a[i];
    for(i=1;i<=n;++i)ans=min(ans,Abs(a[i])+Abs(s-a[i]));
    ans=min(ans,dfs(0,1,-S,1));
    return ans;
	}
  
};  
  


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
