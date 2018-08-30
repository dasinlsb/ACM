/*
如果直接数每一行和每一列中1的个数为i的有cnt_i个然后和合法方案比较是有问题的
因为比如对于不同行之间，它们对另一维的需求集合可能一样，但是顺序完全不能保证，可能是冲突的
看了题解之后发现一种正确的方法是先确定行中2^i所在位置，这个只要有n个合法位置就可以任意分配
然后对应列中2^i所在的位置，这个是唯一的，然后通过2^i的组合就可以确定所有数的位置，检验一下冲突即可
*/
//#line 2 "AndPicture.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=70;
int row[maxN][2],col[maxN][2];
int posR[maxN],posC[maxN];
string YES="Possible";
string NO="Impossible";
class AndPicture {
	public:  
	string isPossible(int n, vector <string> picture)  {  
		// $CARETPOSITION$  
    VI waitR;
    for(int i=0;i<1<<n;i++){
      row[i][0]=row[i][1]=0;
      for(int j=0;j<1<<n;j++){
        row[i][picture[i][j]-'0']++;
      }
      if(row[i][1]*2==(1<<n)){
        waitR.pb(i);
      }
    }
    if(SZ(waitR)!=n){
      return NO;
    }
    VI waitC;
    for(int j=0;j<1<<n;j++){
      col[j][0]=col[j][1]=0;
      for(int i=0;i<1<<n;i++){
        col[j][picture[i][j]-'0']++;
      }
      if(col[j][1]*2==(1<<n)){
        waitC.pb(j);
      }
    }
    if(SZ(waitC)!=n){
      return NO;
    }
    memset(posR,-1,sizeof(posR));
    memset(posC,-1,sizeof(posC));
    for(int i=0;i<n;i++){
      posR[1<<i]=waitR[i];
    }
    for(int i=0;i<n;i++){
      posC[1<<i]=-1;
      for(int j=0;j<n;j++){
        if(picture[waitR[i]][waitC[j]]=='1'){
          if(~posC[1<<i])return NO;
          posC[1<<i]=waitC[j];
        }
      }
    }
    for(int i=0;i<1<<n;i++){
      int val=0;
      for(int j=0;j<n;j++){
        if(picture[i][posC[1<<j]]=='1'){
          val|=1<<j;
        }
      }
      posR[val]=i;
    }
    for(int j=0;j<1<<n;j++){
      int val=0;
      for(int i=0;i<n;i++){
        if(picture[posR[1<<i]][j]=='1'){
          val|=1<<i;
        }
      }
      posC[val]=j;
    }
    for(int i=0;i<1<<n;i++){
      if(posR[i]==-1||posC[i]==-1)return NO;
      for(int j=0;j<i;j++){
        if(posR[i]==posR[j])return NO;
        if(posC[i]==posC[j])return NO;
      }
    }
    return YES;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; string Arr1[] = {"0011",
 "1010",
 "0000",
 "1011"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(0, Arg2, isPossible(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"0011",
 "1000",
 "0001",
 "1011"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(1, Arg2, isPossible(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; string Arr1[] = {"01",
 "00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(2, Arg2, isPossible(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 3; string Arr1[] = {"01010011",
 "11110111",
 "11110011",
 "00000000",
 "11110101",
 "11010111",
 "11110000",
 "11000101"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(3, Arg2, isPossible(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 4; string Arr1[] = {"0000000000000000",
 "0000011111100000",
 "0000000110000000",
 "0000000110000000",
 "0000000110000000",
 "0000000000000000",
 "0000011111000000",
 "0000110000000000",
 "0000110000000000",
 "0000011111000000",
 "0000000000000000",
 "0000001111100000",
 "0000011000110000",
 "0000011000110000",
 "0000001111100000",
 "0000000000000000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(4, Arg2, isPossible(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	AndPicture ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
