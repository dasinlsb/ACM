/*
一种比较直接的想法是枚举路径交然后向上向下统计答案，但是枚举的复杂度是O(n^2)，且统计答案比较复杂
首先路径交长度为[L,R]可以拆成>=L和>=R+1，这样感觉可能可以少推一些式子
然后可以在dfs的过程中同时枚举路径交的顶端(如果枚举底端，那么顶端延伸出去的可能交在朝下的路径上，不符合good path的定义)
然后就要控制底端延伸出去的路径任意，顶端延伸出去的路径不交，这个可以通过预处理每次O(1)回答
时间复杂度O(n)
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int mod=1000*1000*1000+7;
int n,L,R;
int sz[maxn],fa[maxn],dep[maxn];
long long sz2[maxn];
vector<int>G[maxn];
inline void up(int&x,int y){
    if(x+=y,x>=mod)x-=mod;
}
void dfs(int x){
    sz[x]=1;
    sz2[x]=0;
    for(int v:G[x])if(v!=fa[x]){
        fa[v]=x;
        dep[v]=dep[x]+1;
        dfs(v);
        sz[x]+=sz[v];
        sz2[x]=(sz2[x]+1LL*sz[v]*sz[v]);
    }
}
int stk[maxn],top;
int solve(int x,int d){//>=d
    int res=0;
    stk[++top]=x;
    if(top-d>=1){
        int y=stk[top-d+1];
        int up0=((1LL*(n-sz[y])*(n-sz[y])-(sz2[fa[y]]-1LL*sz[y]*sz[y]+1LL*(n-sz[fa[y]])*(n-sz[fa[y]]))-1)/2)%mod;
        int up1=1;
        int down0=(1LL*(sz[x]-1)*sz[x]/2)%mod;
        int down1=sz[x];
        res=(2LL*up0*down0+1LL*up0*down1+1LL*up1*down0)%mod;
    }
    for(int v:G[x])if(v!=fa[x]){
        res=(res+solve(v,d))%mod;
    }
    top--;
    return res;
}
int main(){
    freopen("aa.in","r",stdin);
    scanf("%d%d%d",&n,&L,&R);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1);
    int ans1=solve(1,L);
    int ans2=solve(1,R+1);
    int ans=(ans1-ans2+mod)%mod;
    printf("%d\n",ans);
    return 0;
}