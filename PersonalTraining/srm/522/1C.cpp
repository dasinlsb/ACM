/*
直接在原图上模拟删点去dp是非常困难的，因为每次删掉的点可能不是一段连续区间，难以记录到合适的状态上
显然有些点是不可能被删掉的，即最上面一层，最下面一层，最左边一个和最右边一个
画一画就能发现除了这些点，还可能被保留的只可能是y坐标和最左边或最右边相同的点，也就是最多只有两层的点需要讨论
但是每次删除操作还是要考虑两层点，比较困难
还有一个性质是考虑最上面一层(L1->R1,y_max)和最下面一层(L2->R2,y_min)
取(min(L1,L2)/max(R1,R2),y_max/y_min)四个点表示的矩形
这个矩形内部的点总是一定会被删除，画一画就能看出来
那么这个矩形会把整个序列分成左右两份，而这个矩形的上下界会同时作用到左右两个子序列，也就是说左右部分是相互独立的
这样每次删除就只需要考虑一层点，也就是一段一维上的连续区间即可
假设现在只考虑左边部分，用f[i][j]表示前i位，保留j位是否可行
如果y[i]!=y[0],那么i这个点最后一定会被删除，讨论一下在删除它之前是否利用它删除其他点
假设不利用，那么f[i][j]=f[i-1][j],1<=j<=n
否则枚举一下上一个合法的配对点k，将(k,i)之间的点删除，f[i][j]=f[k][j],1<=j<=n
如果y[i]==y[0],这个点在目前为止的决策下一定会被保留，f[i][j]=f[i-1][j-1],1<=j<=n
时间复杂度O(n^3)
*/
//#line 2 "PointErasing.cpp"  
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
int y_val[maxN];
int f[maxN][maxN];
int pos[maxN];
class PointErasing {
	public:  
	vector <int> getOutcomes(vector <int> y)  {  
		// $CARETPOSITION$  
    // y.clear();
    // y.pb(2);
    // y.pb(3);
    // y.pb(3);
    int n=SZ(y);
    if(n==1)return vector<int>(1,1);
    for(int i=0;i<n;i++){
      y_val[i]=y[i];
    }
    sort(y_val,y_val+n);
    int len=unique(y_val,y_val+n)-y_val;
    for(int i=0;i<n;i++){
      y[i]=lower_bound(y_val,y_val+len,y[i])-y_val;
    }
    int y_max=len-1;
    int y_min=0;
    if(y_max==y_min)return vector<int>(1,n);
    vector<int>q_max,q_min;
    for(int i=0;i<n;i++){
      if(y[i]==y_max)q_max.pb(i);
      if(y[i]==y_min)q_min.pb(i);
    }
    int L=min(q_max[0],q_min[0]);
    int R=max(q_max.back(),q_min.back());
    memset(f,0,sizeof(f));
    f[0][L!=0]=1;
    pos[0]=0;
    for(int i=1;i<=L;i++){
      pos[i]=y[i]-y[0];
      if(pos[i]!=0){
        for(int k=1;k<=n;k++){
          f[i][k]|=f[i-1][k];
          for(int j=0;j<i-1;j++)if(pos[j]*pos[i]<0||pos[j]&&i==L){
            f[i][k]|=f[j][k];
          }
        }
      }else{
        for(int k=1;k<=n;k++){
          f[i][k]|=f[i-1][k-1];
        }
      }
      // for(int j=0;j<=n;j++)if(f[i][j]){
      //   printf("pre %d %d\n",i,j);
      // }
    }
    f[n-1][R!=n-1]=1;
    pos[n-1]=0;
    for(int i=n-2;i>=R;i--){
      pos[i]=y[i]-y[n-1];
      if(pos[i]!=0){
        for(int k=1;k<=n;k++){
          f[i][k]=f[i+1][k];
          for(int j=i+2;j<n;j++)if(pos[j]*pos[i]<0||pos[j]&&i==R){
            f[i][k]|=f[j][k];
          }
        }
      }else{
        for(int k=1;k<=n;k++){
          f[i][k]|=f[i+1][k-1];
        }
      }
      // for(int j=0;j<=n;j++)if(f[i][j]){
      //   printf("suf %d %d\n",i,j);
      // }
    }
    set<int>vis;
    for(int i=0;i<=n;i++)if(f[L][i]){
      for(int j=0;j<=n;j++)if(f[R][j]){
        vis.insert(i+j+SZ(q_max)+SZ(q_min));
      }
    }
    vector<int>ans;
    for(int i:vis)ans.pb(i);
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = { 1, 2, 1, 1, 0, 4, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getOutcomes(Arg0)); }
	void test_case_1() { int Arr0[] = { 0, 0, 4, 4, 8, 8, 4, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getOutcomes(Arg0)); }
	void test_case_2() { int Arr0[] = { 522 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getOutcomes(Arg0)); }
	void test_case_3() { int Arr0[] = { 19, 19, 19, 19, 19, 19 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getOutcomes(Arg0)); }
	void test_case_4() { int Arr0[] = { 0, 1, 2, 3, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getOutcomes(Arg0)); }
	void test_case_5() { int Arr0[] = { 7, 8, 8, 7, 6, 7, 9, 3, 5, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, getOutcomes(Arg0)); }
	void test_case_6() { int Arr0[] = { 3, 2, 3, 3, 4, 3, 4, 3, 3, 1, 5, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 5, 6, 7, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(6, Arg1, getOutcomes(Arg0)); }
	void test_case_7() { int Arr0[] = { 5, 5, 4, 4, 5, 8, 5, 5, 5, 5, 5, 9, 2, 0, 9, 4, 5, 5, 3, 4, 4, 4, 4, 7, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 7, 8, 10, 11, 12, 13, 15, 16, 17 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(7, Arg1, getOutcomes(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	PointErasing ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
