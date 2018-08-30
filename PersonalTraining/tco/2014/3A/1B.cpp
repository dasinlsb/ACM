/*
因为每次是从已选点集和未选点集中各随机选一个点，所以对于已选点集，需要的信息并不是0号点到每个点的期望距离，只要知道平均的期望距离就够了
avgS[S]表示已选点集为S的情况下，S中每个点到0号点的平均期望距离，probS[S]表示选择过程中出现S的概率
枚举不在S中的点i转移,如果i和1一开始就在同一个联通块，那么可以直接计入答案
时间复杂度O(2^n*n^2)
*/
//#line 2 "RandomFlights.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
const int maxN=18;
double dist[maxN][maxN];
double avgDist[maxN];
double probS[1<<maxN];
double avgS[1<<maxN];;
int bitCnt[1<<maxN];
int reach[maxN];
double getDist(double x,double y){
  return sqrt(x*x+y*y);
}
class RandomFlights {
	public:  
	double expectedDistance(vector <int> x, vector <int> y, vector <string> flight)  {  
		// $CARETPOSITION$  
    int n=SZ(x);
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        dist[i][j]=flight[i][j]=='1'?getDist(x[i]-x[j],y[i]-y[j]):1e5;
      }
      dist[i][i]=0;
    }
    for(int k=0;k<n;k++){
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
          dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
        }
      }
    }
    if(dist[0][1]<1e4){
      return dist[0][1];
    }
    for(int i=0;i<1<<n;i++){
      bitCnt[i]=bitCnt[i>>1]+i%2;
    }
    for(int i=0;i<n;i++){
      reach[i]=0;
      avgDist[i]=0;
      for(int j=0;j<n;j++)if(dist[i][j]<1e4){
        reach[i]|=1<<j;
        avgDist[i]+=dist[i][j];
      }
      avgDist[i]/=bitCnt[reach[i]];
      //printf("out %d : %d %.2lf\n",i,reach[i],avgDist[i]);
    }
    for(int i=0;i<1<<n;i++){
      probS[i]=0;
      avgS[i]=0;
    }
    probS[reach[0]]=1;
    avgS[reach[0]]=avgDist[0];
    double ans=0;
    for(int nowS=1;nowS<1<<n;nowS++){
      //printf("nowS %d\n",nowS);
      for(int nxt=0;nxt<n;nxt++)if((1<<nxt&nowS)==0){
        //printf("  nxt %d\n",nxt);
        double probOne=1.0/(n-bitCnt[nowS]);
        double avgMid=0;
        for(int i=0;i<n;i++)if(1<<i&nowS){
          avgMid+=getDist(x[i]-x[nxt],y[i]-y[nxt]);
        }
        avgMid/=bitCnt[nowS];
        if((reach[nxt]&2)!=0){
          //printf("add ans %.2lf %.2lf %.2lf\n",probS[nowS],probOne,(avgS[nowS]+avgMid+dist[nxt][1]));
          ans+=probOne*(avgS[nowS]+probS[nowS]*(avgMid+dist[nxt][1]));
        }else{
          int nxtS=nowS|reach[nxt];
          probS[nxtS]+=probS[nowS]*probOne;
          avgS[nxtS]+=probOne*(avgS[nowS]*bitCnt[nowS]+(avgS[nowS]+probS[nowS]*(avgMid+avgDist[nxt]))*bitCnt[reach[nxt]])/bitCnt[nxtS];
        }
      }
    }
    return ans;
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {7, 10, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"000",
 "001",
 "010"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.7169892001050897; verify_case(0, Arg3, expectedDistance(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {4, 1, 5, 6, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 5, 10, 3, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"00110",
 "00101",
 "11000",
 "10001",
 "01010"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 8.927446638338974; verify_case(1, Arg3, expectedDistance(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {7, 10, 9, 7, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 3, 6, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"00001",
 "00000",
 "00010",
 "00100",
 "10000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 6.2360162308285005; verify_case(2, Arg3, expectedDistance(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {97, 27, 20, 34, 30, 37, 65, 21, 74, 27, 84, 79, 15, 78, 16, 7, 11, 24}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 72, 20, 73, 58, 55, 45, 19, 48, 4, 33, 22, 25, 95, 100, 85, 65, 53}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"000000000000000100",
 "001010000001000000",
 "010010000000000000",
 "000000000000100001",
 "011000000001000000",
 "000000001000000010",
 "000000000000010000",
 "000000000000000100",
 "000001000100001010",
 "000000001000000010",
 "000000000000100000",
 "010010000000000000",
 "000100000010000001",
 "000000100000000000",
 "000000001000000010",
 "100000010000000000",
 "000001001100001000",
 "000100000000100000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 255.25627726422454; verify_case(3, Arg3, expectedDistance(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {35, 8, 71, 81, 43, 76, 55, 15, 72, 39, 99, 23, 14, 77, 47, 43, 60, 67}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {68, 96, 98, 16, 7, 74, 52, 63, 98, 77, 52, 93, 52, 4, 56, 11, 75, 63}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000",
 "000000000000000000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 138.0804889521365; verify_case(4, Arg3, expectedDistance(Arg0, Arg1, Arg2)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	RandomFlights ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
