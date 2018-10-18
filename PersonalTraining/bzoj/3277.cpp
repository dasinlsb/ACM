/*
对所哟串建广义后缀自动机
那么对于每个串，可以暴力枚举右端点在SAM上跑，需要的信息是SAM上每个点代表的状态在多少个原串中出现过，这个可以松set+启发式合并预处理
首先肯定每一步都存在转移，然后最优的情况肯定是前缀匹配到第i个就给答案贡献i，实际上这么长的串出现次数可能小于k，要不断往fail跳直到合法才能贡献答案
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxm=maxn<<1;
int n,kk;
string str[maxn];
int last,tot,root;
int len[maxm],fail[maxm],son[maxm][26];
set<int>items[maxm];
vector<int>G[maxm];
int id[maxm],sum[maxm];
int clone(int p,int c){
  int q=son[p][c];
  int nq=++tot;
  len[nq]=len[p]+1;
  for(int i=0;i<26;i++)son[nq][i]=son[q][i];
  fail[nq]=fail[q];
  fail[q]=nq;
  for(;p && son[p][c]==q;p=fail[p])son[p][c]=nq;
  return nq;
}
void expand(int c,int k){
  int p=last;
  if(son[p][c]){
    int q=son[p][c];
    // items[q].insert(k);
    if(len[q]==len[p]+1)last=q;
    else{
      int nq=clone(p,c);
      last=nq;
    }
  }else{
    int np=++tot;
    len[np]=len[p]+1;
    // items[np].insert(k);
    for(;p && !son[p][c];p=fail[p])son[p][c]=np;
    if(!p)fail[np]=root;
    else{
      int q=son[p][c];
      if(len[q]==len[p]+1)fail[np]=q;
      else{
        int nq=clone(p,c);
        fail[np]=nq;
      }
    }
    last=np;
  }
  items[last].insert(k);
}
int merge(int x,int y){
  if(items[x].size()>items[y].size())swap(x,y);
  for(set<int>::iterator it=items[x].begin();it!=items[x].end();it++){
    items[y].insert(*it);
  }
  return y;
}
void dfs(int x){
  for(int i=0;i<G[x].size();i++){
    dfs(G[x][i]);
    id[x]=merge(id[x],id[G[x][i]]);
  }
  sum[x]=items[id[x]].size();
}
void print(int x){
  printf("fail %d : %d %d\n",x,fail[x],sum[x]);
  // for(int v:items[x])printf("pass %d : %d\n",x,v);
  for(int i=0;i<26;i++){
    if(son[x][i]){
      printf("son %d %c: %d\n",x,i+'a',son[x][i]);
      print(son[x][i]);
    }
  }
}
int main(){
  freopen("aa.in","r",stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin>>n>>kk;
  root=last=++tot;
  for(int i=1;i<=n;i++){
    cin>>str[i];
    for(int j=0;j<str[i].size();j++){
      expand(str[i][j]-'a',i);
    }
    last=root;
  }
  for(int i=1;i<=tot;i++){
    id[i]=i;
    G[fail[i]].push_back(i);
  }
  dfs(1);
  // print(root);puts("");
  for(int i=1;i<=n;i++){
    int v=root;
    long long res=0;
    for(int j=0;j<str[i].size();j++){
      int c=str[i][j]-'a';
      v=son[v][c];
      for(;v!=root && sum[v]<kk;){
        v=fail[v];
      }
      if(sum[v]>=kk){
        res+=len[v];
      }
    }
    cout<<res<<" ";
  }
  return 0;
}