  /*
对于每一个询问(l,r)，可以直接暴力枚举第一个删除的字母x,删除区间内所有x之后显然会分成组合的Nim游戏，可以用类似分块的方法预处理出一部分答案
而预处理也可以看作是一个询问，递归的解决即可，不过要注意预处理的顺序
  */
  #include <bits/stdc++.h>
  using namespace std;
  const int maxn=100005;
  int n;
  char s[maxn];
  int pre[26][maxn],nxt[26][maxn];
  int pre_f[26][maxn],suf_f[26][maxn];
  int sum[maxn];
  int ask(int l,int r){
    static int vis[26];
    if(l>r)return 0;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<26;i++)if(pre[i][r]>=l){
      int v=suf_f[i][l]^sum[pre[i][r]]^sum[nxt[i][l]]^pre_f[i][r];
      vis[v]=1;
    }
    for(int i=0;;i++){
      if(!vis[i]){
        return i;
      }
    }
  }
  int main(){
    freopen("aa.in","r",stdin);
      scanf("%s",s+1);
    n=strlen(s+1);  
    for(int i=0;i<26;i++){
      for(int j=1;j<=n;j++){
        pre[i][j]=(s[j]=='a'+i)?j:pre[i][j-1];
      }
      nxt[i][n+1]=n+1;
      for(int j=n;j;j--){
        nxt[i][j]=(s[j]=='a'+i)?j:nxt[i][j+1];
      }
    }
    for(int i=1;i<=n;i++){
      int ch=s[i]-'a';
      int L=pre[ch][i-1];
      if(L)sum[i]=pre_f[ch][i-1]^sum[L];
      for(int j=i-1;j>L;j--){
        suf_f[ch][j]=ask(j,i-1);
      }
      vector<pair<int,int > >seg;
      for(int j=0;j<26;j++)if(j!=ch&&pre[j][i]!=0){
        seg.push_back(make_pair(pre[j][i]+1,j));
      }
      sort(seg.begin(),seg.end());
      reverse(seg.begin(),seg.end());
      for(pair<int,int>x:seg){
        pre_f[x.second][i]=ask(x.first,i);
      }
    }
    int qn;scanf("%d",&qn);
    for(;qn--;){
      int l,r;scanf("%d%d",&l,&r);
      printf("%s\n",ask(l,r)?"Alice":"Bob");
    }
    return 0;
  }