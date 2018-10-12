/*
可以在原图外层再加一层白色，然后只要两个图的联通块包含关系相同关系相同即可
由于题目给出的性质，这个包含关系肯定是一棵树，固定最外面的白色为树根然后树hash或者求括号序列的最小表示判一下同构即可
*/
#include<bits/stdc++.h>
using namespace std;  
const int maxn=55;
const int maxm=2505;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int n;
struct Gragh{
int tot;
int id[maxn][maxn];
bool grid[maxn][maxn];
bool deeper[maxm][maxm];
int vis[maxn][maxn];
vector<int>G[maxm];
string hs[maxm];
void clear(){
  tot=0;
  memset(id,0,sizeof(id));
  memset(grid,0,sizeof(grid));
  memset(vis,0,sizeof(vis));
  memset(deeper,0,sizeof(deeper));
}
int is_valid(int x){
  return x>=0 && x<n+2;
}
void paint(int x,int y,int z,bool in){
  vis[x][y]=z;
  if(in)deeper[id[x][y]][z]=1;
  for(int i=0;i<4;i++){
    int _x=x+dx[i];
    int _y=y+dy[i];
    if(!is_valid(_x) || !is_valid(_y))continue;
    if(vis[_x][_y]==z || id[_x][_y]==z)continue;
    paint(_x,_y,z,in);
  }
}
void set_id(int x,int y,int z){
  id[x][y]=z;
  for(int i=0;i<4;i++){
    int _x=x+dx[i];
    int _y=y+dy[i];
    if(!is_valid(_x)||!is_valid(_y))continue;
    if(id[_x][_y] || grid[_x][_y]!=grid[x][y])continue;
    set_id(_x,_y,z);
  }
}
void print_id(){
  for(int i=0;i<n+2;i++){
    for(int j=0;j<n+2;j++){
      printf("%d ",id[i][j]);
    }
    puts("");
  }
  puts("");
}
void build(vector<string>&str){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)if(str[i][j]=='.'){
      grid[i+1][j+1]=1;
    }
  }
  for(int i=0;i<=n+1;i++){
    for(int j=0;j<=n+1;j++)if(!id[i][j]){
      set_id(i,j,++tot);
    }
  }
  for(int now=1;now<=tot;now++){
    if(now!=1)paint(0,0,now,0);
    for(int i=0;i<n+2;i++){
      for(int j=0;j<n+2;j++)if(id[i][j]!=now && vis[i][j]!=now){
        paint(i,j,now,1);
      }
    }
  }
  // for(int i=1;i<=tot;i++){
  //   for(int j=1;j<=tot;j++)if(deeper[i][j]){
  //     printf("deeper %d %d\n",i,j);
  //   }
  // }
  for(int i=1;i<=tot;i++){
    G[i].clear();
  }
  for(int i=2;i<=tot;i++){
    int p=1;
    for(int j=1;j<=tot;j++)if(deeper[i][j] && deeper[j][p])p=j;
    G[p].push_back(i);
  }
}
void dfs(int x){
  hs[x]="(";
  for(int v:G[x])dfs(v);
  sort(G[x].begin(),G[x].end(),[&](int a,int b){
    return hs[a]<hs[b];
  });
  for(int v:G[x])hs[x]+=hs[v];
  hs[x]+=")";
}

}a,b;
class Balance{
	public:
	string canTransform(vector <string> initial, vector <string> target){
		// $CARETPOSITION$
    n=initial.size();
    a.clear();
    b.clear();
    a.build(initial);
    b.build(target);
    a.dfs(1);
    b.dfs(1);
    return a.hs[1]==b.hs[1]?"Possible":"Impossible";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(0, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"..",
 ".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {".#",
 "##"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(1, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...",
 ".#.",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"###",
 "#.#",
 "###"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(2, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {".#.#.......",
 "####.###...",
 ".....####..",
 "..##.#.##.#",
 ".##..#.##.#",
 ".#######...",
 ".#....###.#",
 ".##.#.#....",
 "..#...#...#",
 "..#####...#",
 "..........."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"...........",
 ".###....#..",
 ".#.#..#....",
 ".###.......",
 ".#####.....",
 ".#...#####.",
 ".#.#.....#.",
 ".#.#####.#.",
 ".#.......#.",
 ".#########.",
 "..........."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(3, Arg2, canTransform(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {".....",
 ".###.",
 ".....",
 ".###.",
 "....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {".....",
 ".#.#.",
 ".#.#.",
 ".#.#.",
 "....."}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(4, Arg2, canTransform(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	Balance ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
