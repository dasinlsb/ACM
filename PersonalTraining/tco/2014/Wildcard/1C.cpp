/*
普通的bfs记录f[r][c][e]为r行c列能量为e是否有可能，时间和空间都无法接受
因为能量只能减少不能增加，所以可以记录到达每个点最大可能的能量
接下来考虑优化转移，如果对于每个点暴力枚举[0,maxe]转移出去会TLE
为了同时保证正确性和转移的复杂度
可以考虑每次从当前点(r,c,e)转移到上下左右离(r-e,c),(r+e,c),(r,c-e),(r,c+e)尽可能近的点
也就是控制每一步能量的变化最小，实际上可能转移到更近的地方
为了之后能加入这些合法转移，可以记录转移过来的方向，要额外考虑往回走尽可能小的一步的情况
按照能量从大到小分层即可确定顺序
过程中队列的状态数很多，在TC上交vector会MLE
*/
//#line 2 "EnergyGameOnGrid.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=2005;
int n,m;
int grid[maxN][maxN];
int nxt[maxN][maxN][4];
int dis[maxN][maxN];
int disD[maxN][maxN][4];
struct Node{
  int r,c,d;
  Node(){}Node(int _r,int _c,int _d){r=_r,c=_c,d=_d;}
};
queue<Node>que[maxN];
void map_init(int N,int M,vector <int>&p,int r1,int c1,int r2,int c2){
    ll x = N + 2 * M + 3 * r1 + 4 * c1 + 5 * r2 + 6 * c2;

for(int i = 0; i < N; i++){
	for(int j = 0; j < M; j++){
		grid[i][j] = 0;
	}
}

for(int i = 0; i < SZ(p); i += 5){
	for(int j = p[i]; j <= p[i + 2]; j++){
		for(int k = p[i + 1]; k <= p[i + 3]; k++){
			x = (x * 1103515245 + 12345) % 2147483648LL;
			if(x < p[i + 4]){
				grid[j][k] = 1;
			} else {
				grid[j][k] = 0;
			}
		}
	}
}
grid[r1][c1] = 0;
grid[r2][c2] = 0;
}
void expand(int r,int c,int e){
  int tr=nxt[max(r-e,0)][c][2],tc=c;
  if(tr<r)que[r-tr].push(Node(tr,tc,2));
  tr=r,tc=nxt[r][min(c+e,m-1)][3];
  if(tc>c)que[tc-c].push(Node(tr,tc,3));
  tr=nxt[min(r+e,n-1)][c][0],tc=c;
  if(tr>r)que[tr-r].push(Node(tr,tc,0));
  tr=r;tc=nxt[r][max(c-e,0)][1];
  if(tc<c)que[c-tc].push(Node(tr,tc,1));
}
class EnergyGameOnGrid {
	public:  
	string isReachable(int N, int M, vector <int> p, int r1, int c1, int r2, int c2, int E)  {  
		// $CARETPOSITION$  
    map_init(N,M,p,r1,c1,r2,c2);
    n=N,m=M;
    for(int i=0;i<N;i++){
      int p=-1;
      for(int j=0;j<M;j++){
        if(grid[i][j]==0)p=j;
        nxt[i][j][3]=p;
      }
      p=M;
      for(int j=M-1;~j;--j){
        if(grid[i][j]==0)p=j;
        nxt[i][j][1]=p;
      }
    }
    for(int j=0;j<M;j++){
      int p=-1;
      for(int i=0;i<N;i++){
        if(grid[i][j]==0)p=i;
        nxt[i][j][0]=p;
      }
      p=N;
      for(int i=N-1;~i;i--){
        if(grid[i][j]==0)p=i;
        nxt[i][j][2]=p;
      }
    }
    for(int i=0;i<=E;i++){
      for(;SZ(que[i]);)que[i].pop();
    }
    memset(dis,-1,sizeof(dis));
    memset(disD,-1,sizeof(disD));
    dis[r1][c1]=E;
    for(int i=0;i<4;i++){
      disD[r1][c1][i]=E;
    }
    expand(r1,c1,E);
    //int tot=0;
    for(int e=E;e;e--){
      //printf("e %d\n",e);
      for(;que[e].size();){
        int r=que[e].front().r,c=que[e].front().c,d=que[e].front().d;que[e].pop();
        //assert(r>=0&&r<n&&c>=0&&c<m);
        //printf("e[%d] %d %d %d\n",e,r,c,d);
        if(dis[r][c]==-1){
          dis[r][c]=e;
          expand(r,c,e);
        }
        if(disD[r][c][d]==-1){
          disD[r][c][d]=e;
          if(d==0){
            if(r-1>=0&&e-(r-nxt[r-1][c][0])>0){
              //assert((r-nxt[r-1][c][0])>0);
              que[e-(r-nxt[r-1][c][0])].push(Node(nxt[r-1][c][0],c,0));
            }
          }else if(d==1){
            if(c+1<m&&e-(nxt[r][c+1][1]-c)>0){
              //assert((nxt[r][c+1][1]-c)>0);
              que[e-(nxt[r][c+1][1]-c)].push(Node(r,nxt[r][c+1][1],1));
            }
          }else if(d==2){
            if(r+1<n&&e-(nxt[r+1][c][2]-r)>0){
              //assert((nxt[r+1][c][2]-r)>0);
              que[e-(nxt[r+1][c][2]-r)].push(Node(nxt[r+1][c][2],c,2));
            }
          }else{
            if(c-1>=0&&e-(c-nxt[r][c-1][3])>0){
              //assert((c-nxt[r][c-1][3])>0);
              que[e-(c-nxt[r][c-1][3])].push(Node(r,nxt[r][c-1][3],3));
            }
          }
        }
      }
      //tot+=SZ(que[e]);
      //printf("SZ e %d : %d\n",e,SZ(que[e]));
    }
    //printf("tot %d\n",tot);
    if(~dis[r2][c2])return "Possible";
    return "Impossible";
	}  
};
	


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
