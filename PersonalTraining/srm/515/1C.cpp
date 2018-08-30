/*
有个显然的性质是每个三元组(F,L,R)的汇聚点都在某两点的最短路上
由于F,R很少，可以考虑枚举F,R之后bfs得出每个点到F,R的距离dis[0],dis[1]
接下来讨论L点的位置，假设L就在F,R的最短路上，那么最短路长度也就是dis[0][L]+dis[1][L]就是这个三元组的贡献
如果L不在F,R的最短路上，显然L到汇聚点的路径肯定是L到(F,R某条最短路上)的某点的最短路，这可以从L开始bfs得出
但是枚举L是无法接受的，所以可以考虑反向，将F,R最短路上的点固定一个标号即 dis[0][x]+dis[1][x]，从这些点集开始bfs，每次遇到L时其距离就是三元组的贡献

*/
//#line 2 "MeetInTheMaze.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  

const int _L=0;
const int _F=1;
const int _R=2;
const int maxN=55;
int n,m;
vector<string>pic;
int disF[maxN*maxN];
int disR[maxN*maxN];
int disL[maxN*maxN*3];
int isL[maxN*maxN*3];
vector<int>pos[3];
vector<int>g[maxN*maxN*3];
void bfs1(int S,int dis[]){
  static int q[maxN*maxN];
  int h=1,t=0;
  q[++t]=S;
  memset(dis,-1,sizeof(int)*n*m);
  dis[S]=0;
  for(;h<=t;){
    int x=q[h++];
    int r=x/m,c=x%m;
    for(int i=-1;i<=1;i++){
      for(int j=-1;j<=1;j++)if(!(i&&j)){
        int r1=r+i,c1=c+j;
        if(r1>=0&&r1<n&&c1>=0&&c1<m&&dis[r1*m+c1]==-1&&pic[r1][c1]!='#'){
          dis[r1*m+c1]=dis[x]+1;
          q[++t]=r1*m+c1;
        }
      }
    }
  }
}
ll bfs2(int S,int dis[]){
  static int q[maxN*maxN*3];
  ll res=0;
  int cntL=0;
  int h=1,t=0; 
  q[++t]=S;
  memset(dis,-1,sizeof(int)*n*m*3);
  dis[S]=0;
  for(;h<=t;){
    int x=q[h++];
    if(isL[x]){
      res+=dis[x];
      cntL++;
    }
    for(int i=0;i<SZ(g[x]);i++)if(dis[g[x][i]]==-1){
      dis[g[x][i]]=dis[x]+1;
      q[++t]=g[x][i];
    }
  }
  if(cntL!=SZ(pos[_L]))return -1;
  return res;
}
int rebuild(){
  for(int i=0;i<3*n*m;i++){
    g[i].clear();
  }
  for(int i=0;i<2*n*m-1;i++){
    g[n*m+i].pb(n*m+i+1);
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if(disF[i*m+j]==-1||disR[i*m+j]==-1)continue;
      g[n*m+disF[i*m+j]+disR[i*m+j]-1].pb(i*m+j);
      //printf("adde %d %d %d\n",disF[i*m+j]+disR[i*m+j],i,j);
      if(i)g[i*m+j].pb((i-1)*m+j);
      if(i<n-1)g[i*m+j].pb((i+1)*m+j);
      if(j)g[i*m+j].pb(i*m+j-1);
      if(j<m-1)g[i*m+j].pb(i*m+j+1);
    }
  }
  return n*m;
}
ll gcd(ll x,ll y){
  return y?gcd(y,x%y):x;
}
void print_map(){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      printf("(%d) ",disF[i*m+j]+disR[i*m+j]);
    }
    puts("");
  }
  puts("");
}
class MeetInTheMaze {
	public:  
	string getExpected(vector <string> maze)  {  
		// $CARETPOSITION$  
    pic=maze;
    n=SZ(maze);
    m=SZ(maze[0]);
    //printf("nm %d %d\n",n,m);
    memset(isL,0,sizeof(isL));
    for(int i=0;i<3;i++)pos[i].clear();
    for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
        if(maze[i][j]=='L')pos[_L].pb(i*m+j),isL[i*m+j]=1;
        else if(maze[i][j]=='F')pos[_F].pb(i*m+j);
        else if(maze[i][j]=='R')pos[_R].pb(i*m+j);
      }
    }
    ll ans=0;
    for(int i=0;i<SZ(pos[_F]);i++){
      bfs1(pos[_F][i],disF);
      for(int j=0;j<SZ(pos[_R]);j++){
        bfs1(pos[_R][j],disR);
        //print_map();
        int s0=rebuild();
        ll res=bfs2(s0,disL);
        if(res==-1)return "";
        ans+=res;
      }
    }
    //printf("ans %lld\n",ans);
    ll down=(ll)SZ(pos[_L])*SZ(pos[_F])*SZ(pos[_R]);
    ll d=gcd(ans,down);
    return to_string(ans/d)+"/"+to_string(down/d);
	} 
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "#########", 
  "####F####", 
  "##L...R##", 
  "####L####", 
  "#########" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "9/2"; verify_case(0, Arg1, getExpected(Arg0)); }
	void test_case_1() { string Arr0[] = { "LR", 
  "RF" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "2/1"; verify_case(1, Arg1, getExpected(Arg0)); }
	void test_case_2() { string Arr0[] = { "..F.#...", 
  "L.F.#..L", 
  "..F.#...", 
  ".R.#..L.", 
  "...#....", 
  "..R#.L.." }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(2, Arg1, getExpected(Arg0)); }
	void test_case_3() { string Arr0[] = { ".L..L..L..", 
  "..........", 
  "..........", 
  "..........", 
  "........R.", 
  "...R......", 
  "..........", 
  "..........", 
  "..........", 
  ".......F.." }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "40/3"; verify_case(3, Arg1, getExpected(Arg0)); }
	void test_case_4() { string Arr0[] = { "#.#....#...#.#", 
  "#...#..#......", 
  ".L#...#R#..#F.", 
  "#...#......#..", 
  "#......#.....#", 
  ".R.....F....L.", 
  "##..#.......#.", 
  "#........##...", 
  ".F...##L#..#R#" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "362/27"; verify_case(4, Arg1, getExpected(Arg0)); }
	void test_case_5() { string Arr0[] = { "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLFLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFFLLLLLLLLLLRLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLFLLLLLLLLLLLLLLF", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLF", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLFLLL", 
  "LLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRRL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLR", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLFFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLFLLLLLLLLLRLLLLLLLLLLLLLLLLLLLRLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLFLLLLLLLLLLLLLLLLRLLLLLLLLLRLLLLLLLLLLLLRLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLRLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "FLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLRLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL", 
  "LLLLLLLLLLLLLLLLLLLLLLLLLLLFLLLLLLLLLLLLLLLLLLLLLL" }
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "210623/4100"; verify_case(5, Arg1, getExpected(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	MeetInTheMaze ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
