#define ONLINEJUDGE
#include <bits/stdc++.h>
using namespace std;
const int maxn=150005;
int size[2],son[2][maxn][2],num[2][maxn],fa[2][maxn],isLeaf[2][maxn]; 
int _size[2],_son[2][maxn][2],_isLeaf[2][maxn];
vector<int> id[2],_id[2];
int tot[2];
void dfs(int k,int x){
	isLeaf[k][x]=(!son[k][x][0] && !son[k][x][1]);
  for(int i=0;i<2;i++){
    if(son[k][x][i]){
      fa[k][son[k][x][i]]=x;
      dfs(k,son[k][x][i]);
    }
    if(i==0)num[k][x]=++tot[k];
  }
}
int isLegal(int k,int x){
  for(int i=0;i<2;i++){
		if(!son[k][x][i] || !isLeaf[k][son[k][x][i]])return 0;
	}
  return 1;
}
void remove(int p){
  int x=id[p].back();
  size[p]-=2;
  son[p][x][0]=son[p][x][1]=0;
  isLeaf[p][x]=1;
  if(fa[p][x] && isLegal(p,fa[p][x])){
    id[p].back()=fa[p][x];
  }else{
    id[p].pop_back();
  }
}
int same(int x,int y){
	if(!x||!y)return x+y==0;
	if(!same(son[0][x][0],son[1][y][0]))return 0;
	if(!same(son[0][x][1],son[1][y][1]))return 0;
	return 1;
}
void output(int k,int x){
  if(!x)return;
	printf("%d %d\n",num[k][son[k][x][0]],num[k][son[k][x][1]]);
  for(int i=0;i<2;i++){
    output(k,son[k][x][i]);
  }
}
void dfs2(int k,int x){
  if(!x)return;
	num[k][x]=++tot[k];
	for(int i=0;i<2;i++){
    dfs2(k,son[k][x][i]);
	}
}

int main(){
  #ifdef ONLINEJUDGE
	freopen("lca.in","r",stdin);
	freopen("lca.out","w",stdout);
  #else
  freopen("aa.in","r",stdin);
  #endif
	for(;;){
		tot[0]=tot[1]=0;
		for(int i=0;i<2;i++){
			scanf("%d",size+i);
			if(size[i]==0)exit(0);
			for(int j=1;j<=size[i];j++){
				scanf("%d%d",&son[i][j][0],&son[i][j][1]);
			}
		}
    int init_size=max(size[0],size[1]);
		for(int t=0;t<2;t++){
      dfs(t,1);
      id[t].clear();
      id[t].push_back(0);
      for(int j=1;j<=size[t];j++){
        if(isLegal(t,j))id[t].push_back(j);
      }
      sort(id[t].begin(),id[t].end(),[&](int x,int y){
        if(!x||!y)return !x;
        return num[t][x]<num[t][y];
      });
    }
		int p=size[1]>size[0];
		for(;size[p]>size[p^1];)remove(p);
		int l=0,r=size[0]-1>>1;
		for(int t=0;t<2;t++){
			_id[t]=id[t];
			_size[t]=size[t];
			for(int i=1;i<=init_size;i++){
				_son[t][i][0]=son[t][i][0];
				_son[t][i][1]=son[t][i][1];
				_isLeaf[t][i]=isLeaf[t][i];
			}
		}
		for(;l<r;){
			int mid=l+r>>1;
			for(int round=mid;round--;){
				remove(0);
				remove(1);
			}
			if(same(1,1))r=mid;
			else l=mid+1;
			for(int t=0;t<2;t++){
				id[t]=_id[t];
				size[t]=_size[t];
				for(int i=1;i<=init_size;i++){
					son[t][i][0]=_son[t][i][0];
					son[t][i][1]=_son[t][i][1];
					isLeaf[t][i]=_isLeaf[t][i];
				}
			}
		}
		for(int round=l;round--;){
			remove(0);
			remove(1);
		}
		tot[0]=0;
		dfs2(0,1);
		printf("%d\n",size[0]);
    output(0,1);
	}
	return 0;
}
