/*
首先有个性质对于任意一点(i,j)，都有a[i+H2][j+W2]+a[i][j]==a[i+H2][j]+a[i][j+W2]，也就是以(i,j)为左上角的宽高分别为W2,H2的矩形对角和相等
只要对于任意(i,j)上述条件都成立即可，接下来可以讨论一下
1.当a[i+H2][j+W2]==a[i][j+W2]时，有a[i][j]==a[i+H2][j]成立，接着可以推出对于所有(i'=i(mod H2),j'=j(mod W2))都有该性质，也就是只要确定最上边的H2*W的矩阵的值就可以确定整个矩阵
2.当a[i+H2][j+W2]==a[i+H2][j]时同理
所以，如果将原矩阵的点划分成H2*W2组(i'=i(mod H2),j'=j(mod W2))，每组内的点肯定至少会满足1，2其中一个条件
那么可以2^(H2*W2)来枚举每组满足的是哪个条件，为了避免重复可以规定如果某一组在状态二进制表示下为1则可以满足条件1，也可以同时满足条件2，二进制下为0则只满足条件2，这样可以避免算重
在这样的规定下，二进制下为1的答案非常好算，考虑二进制下为0且H2=W2=4的答案
现在要解决的子问题相当于有一个n*4的矩阵，要在每一位填上0/1，使得没有任意一列全0或全1，且每一行0/1的个数都相同
考虑枚举每一行有多少个1
ans[0]=ans[4]=0
1的答案可以用全集减去反面，反面的答案可以枚举在整个矩阵中1在多少列中出现过
  ans[1]=ans[3]=4^n[每一行C(4,1)种放法]-4[整列都是1的情况]-C(4,2)*(2^n-2)[剩下两列不能出现2种整列全0/全1]-C(4,3)*(3^n-3-3*(2^n-2))[剩下三列不能有整列全0/全1]
2的答案可以容斥，相当于要求每列至少1个0，1个1
  ans[2]=res[每列至少0个0，0个1]-[至少一列全1]-[至少一列全0]+[全1全0列都出现过]
        =6^n-2*(4*(3^n-3)+6)+(2*C(4,2)*(2^n-2)+C(4,2))
*/
#include<bits/stdc++.h>
using namespace std;  
const int mod=1e9+7;
int c[6][6],row[4],col[4];
class SubRectangles{
	public:
  int Pow(long long x,int y){
    long long t=1;
    for(;y;y>>=1){
      if(y&1)t=t*x%mod;
      x=x*x%mod;
    }
    return t;
  }
	int countWays(int H, int W, int H2, int W2){
		// $CARETPOSITION$
    memset(c,0,sizeof c);
    c[0][0]=1;
    for(int i=1;i<=5;i++){
      c[i][0]=1;
      for(int j=1;j<=i;j++)c[i][j]=c[i-1][j-1]+c[i-1][j];
    }
    int ans=0;
    for(int S=0;S<1<<H2*W2;S++){
      memset(row,0,sizeof row);
      memset(col,0,sizeof col);
      for(int i=0;i<H2*W2;i++){
        col[i%W2]+=(S>>i&1);
        row[i/W2]+=(~S>>i&1);
      }
      int res=1;
      for(int i=0;i<W2;i++){
        int n=(W-i+W2-1)/W2;
        int tmp=0;
        for(int j=0;j<=col[i];j++){
          tmp=(tmp+Pow(c[col[i]][j],n))%mod;
        }
        res=1LL*res*tmp%mod;
      }
      for(int i=0;i<H2;i++){
        int n=(H-i+H2-1)/H2;
        int tmp;
        if(row[i]==0)tmp=1;
        else if(row[i]==1)tmp=0;
        else if(row[i]==2)tmp=(Pow(2,n)-2)%mod;
        else if(row[i]==3)tmp=(2LL*Pow(3,n)-6LL*Pow(2,n)+6LL)%mod;
        else tmp=(1LL*Pow(6,n)+2LL*Pow(4,n)-16LL*Pow(3,n)+24LL*Pow(2,n)-14LL)%mod;
        if(tmp<0)tmp+=mod;
        res=1LL*res*tmp%mod;
      }
      ans=(ans+res)%mod;
    }
    return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2015; int Arg1 = 666; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; verify_case(0, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 3; int Arg3 = 2; int Arg4 = 160; verify_case(1, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 3; int Arg2 = 4; int Arg3 = 1; int Arg4 = 346; verify_case(2, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 20; int Arg2 = 3; int Arg3 = 3; int Arg4 = 705820974; verify_case(3, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 123456789; int Arg1 = 987654321; int Arg2 = 3; int Arg3 = 4; int Arg4 = 841175976; verify_case(4, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 1000000000; int Arg1 = 1000000000; int Arg2 = 4; int Arg3 = 4; int Arg4 = 294775952; verify_case(5, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE  
int main(){
	SubRectangles ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
