/*
一开始把每个管道内部的coin整体考虑，但是后面的管道对前面的影响太多了，发现情况讨论不完
其实可以只考虑硬币,管道只是减少某些硬币之间的最短路径，而硬币两两之间的最短路是可以O(n^3)预处理出来的，虽然可以O(n^2)但是讨论很麻烦，尝试了一下还是放弃了
接下来就不会了，看了策爷的题解发现有个结论，整个过程虽然中间可能跳过一些点，但是最多转向两次，得知这个结论之后虽然无法证明，但是想想感觉相当有道理
不转向直接暴力扫一遍，转向一次肯定是在右端点转，考虑转向两次的情况
可以设f[p0][p1][p2][state]，因为转向两次肯定整个移动序列有三段，可以记录每一段上一个位置是p_i
同时第一段和第二段的转折点r，第二段和第三段的转折点l也会把硬币序列分成三段，state记录一下当前到了第几段即可
时间复杂度O(n^3)
*/
//#line 2 "PlumbersCoins.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=55;
const ll inf=(ll)1e11;
ll dis[maxN*2][maxN*2],f[maxN][maxN][maxN][3],g[maxN][maxN][3];
VI wait[maxN],pos;
inline void update(ll&x,ll y){
  if(x==-1||y<x)x=y;
}

class PlumbersCoins {
	public:  
	int minTime(vector <int> tubes, vector <int> coins)  {  
		// $CARETPOSITION$  
    coins.pb(0);
    for(int i=SZ(coins)-2;~i;i--)coins[i+1]=coins[i];
    coins[0]=0;
    pos.clear();
    for(int i=0;i<SZ(coins);i++)pos.pb(coins[i]);
    for(int i=0;i<SZ(tubes);i++)pos.pb(tubes[i]);
    for(int i=0;i<SZ(pos);i++){
      for(int j=0;j<SZ(pos);j++){
        dis[i][j]=abs(pos[i]-pos[j]);
      }
    }
    for(int i=0;i<SZ(tubes);i+=2){
      dis[i+SZ(coins)][i+1+SZ(coins)]=1;
    }
    for(int k=0;k<SZ(pos);k++){
      for(int i=0;i<SZ(pos);i++){
        for(int j=0;j<SZ(pos);j++){
          dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        }
      }
    }
    for(int i=0;i<SZ(coins);i++){
      wait[i].clear();
    }
    for(int i=0;i<SZ(coins);i++){
      for(int j=0;j<SZ(coins);j++){
        for(int k=0;k<SZ(coins);k++){
          wait[max(i,max(j,k))].pb(i<<12|j<<6|k);
        }
      }
    }
    memset(f,-1,sizeof(f));
    f[0][0][0][0]=0;
    ll ans=coins.back();
    for(int now=0;now<SZ(coins);now++){
      for(int i=0;i<SZ(wait[now]);i++){
        int p0=wait[now][i]>>12;
        int p1=(wait[now][i]>>6)&63;
        int p2=wait[now][i]&63;
        for(int state=0;state<3;state++)if(~f[p0][p1][p2][state]){
          if(now==SZ(coins)-1){
            if(state==2){
              ans=min(ans,f[p0][p1][p2][state]);
            }
            continue;
          }
          if(state==0){
            update(f[now+1][p1][p2][0],f[p0][p1][p2][0]+dis[p0][now+1]);
            update(f[p0][now+1][now+1][1],f[p0][p1][p2][0]);
          }
          if(state==1){
            update(f[now+1][p1][p2][1],f[p0][p1][p2][1]+dis[p0][now+1]);
            update(f[p0][now+1][p2][1],f[p0][p1][p2][1]+dis[p1][now+1]);
            update(f[p0][p1][now+1][1],f[p0][p1][p2][1]+dis[p2][now+1]);
            update(f[now+1][now+1][p2][2],f[p0][p1][p2][1]+dis[p0][now+1]+dis[p1][now+1]);
          }
          if(state==2){
            update(f[p0][p1][now+1][2],f[p0][p1][p2][2]+dis[p2][now+1]);
          }
        }
      }
    }
    memset(g,-1,sizeof(g));
    g[0][0][0]=0;
    for(int now=0;now<SZ(coins);now++){
      for(int empty=0;empty<SZ(coins);empty++){
        for(int state=0;state<3;state++)if(~g[now][empty][state]){
          if(now==SZ(coins)-1){
            if(state==2){
              ans=min(ans,g[now][empty][state]);
            }
            continue;
          }
          if(state==0){
            update(g[now+1][empty][0],g[now][empty][0]+dis[now][now+1]);
            update(g[now+1][now][1],g[now][empty][0]);
          }
          if(state==1){
            update(g[now+1][empty][1],g[now][empty][1]+dis[now][now+1]);
            update(g[now+1][now][1],g[now][empty][1]+dis[empty][now+1]);
            update(g[now+1][now+1][2],g[now][empty][1]+dis[now][now+1]+dis[empty][now+1]);
          }
        }
      }
    }
    ll oneTime=0;
    for(int i=1;i<SZ(coins);i++){
      oneTime+=dis[i-1][i];
    }
    ans=min(ans,oneTime);
    return (int)ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 18}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(0, Arg2, minTime(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {10, 20, 30, 40}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {15, 39}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 32; verify_case(1, Arg2, minTime(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1, 105, 106, 119, 120, 200}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {117, 121}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(2, Arg2, minTime(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,13}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7,8,14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; verify_case(3, Arg2, minTime(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1, 7000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 100, 1000, 1000000, 6000000, 7000001}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3000002; verify_case(4, Arg2, minTime(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {11990077,86497123,155806046,182547019,423754766,514490485,540050520,562549306,569114639,952908416}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {361042502,497737263,510014274,529291145}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 368861292; verify_case(5, Arg2, minTime(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	PlumbersCoins ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
