/*
先分解成不超过16的质数的乘积
剩下的是类似背包的问题，不过物品数过多无法接受
首先11，13肯定是对答案没有贡献的
对于5,7由于它们的幂较小，可以暴力枚举10,14,15的个数
剩下的问题就是2，3有多少种方案拼成2,3,4,6,8,9,12,16
2^n*3^m<=10^2500->两边取对数然后算计一下发现n*m空间是可以接受的，直接上vector套vector跑背包
不过这样会TLE一个点，在枚举10,14,15的个数的时候可以优化一下，先枚举10，14的个数，剩下的枚举可以换成前缀和
*/
//#line 2 "VerySmoothDecompositions.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) (int((x).size()))
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int prim[6]={2,3,5,7,11,13};
const int mod=1000*1000*1000+9;
inline void up(int&x,int y){
  x+=y;
  if(x>=mod)x-=mod;
}
int str_mod_int(string&s,int n){
  int res=0;
  for(int i=0;i<SZ(s);i++){
    res=(res*10+s[i]-'0')%n;
  }
  return res;
}
void str_divide_int(string&s,int n){
  int x=0;
  for(int i=0;i<SZ(s);i++){
    x=x*10+s[i]-'0';
    s[i]=x/n+'0';
    x%=n;
  }
  for(;s[0]=='0';){
    s.erase(0,1);
  }
}
int cnt[6];
const int cost[6][2]={
  {2,0},{1,1},{3,0},{0,2},{2,1},{4,0}
};//4,6,8,9,12,16
class VerySmoothDecompositions {
	public:  
	int solve(vector <string> digits)  {  
		// $CARETPOSITION$  
    string num="";
    for(int i=0;i<SZ(digits);i++){
      num+=digits[i];
    }
    for(int i=0;i<6;i++){
      cnt[i]=0;
      for(;str_mod_int(num,prim[i])==0;){
        str_divide_int(num,prim[i]);
        cnt[i]++;
        //printf("prim %d\n",prim[i]);
      }
    }
    if(!(SZ(num)==1&&num[0]=='1'))return 0;
    vector<vector<int> >f(cnt[0]+1,vector<int>(cnt[1]+1,1));
    for(int i=0;i<6;i++){
      for(int j=cost[i][0];j<=cnt[0];j++){
        for(int k=cost[i][1];k<=cnt[1];k++){
          up(f[j][k],f[j-cost[i][0]][k-cost[i][1]]);
        }
      }
    }
    for(int i=0;i<=cnt[0];i++){
      for(int j=1;j<=cnt[1];j++){
        up(f[i][j],f[i][j-1]);
      }
    }
    int ans=0;
    for(int s14=min(cnt[0],cnt[3]);s14>=0;s14--){
      for(int s10=min(cnt[0]-s14,cnt[2]);s10>=0;s10--){
        up(ans,f[cnt[0]-s14-s10][cnt[1]]);
        int low=cnt[1]-min(cnt[1],cnt[2]-s10);
        if(low!=0){
          up(ans,mod-f[cnt[0]-s14-s10][low-1]);
        }
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"47"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {"10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"36"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { string Arr0[] = {"1","21"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, solve(Arg0)); }
	void test_case_5() { string Arr0[] = {"1024"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 23; verify_case(5, Arg1, solve(Arg0)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	VerySmoothDecompositions ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
