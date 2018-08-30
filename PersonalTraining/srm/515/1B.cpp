/*
由于每个顾客只会来一次，所以在dp的时候要记录一下之前某个顾客有没有来过
f[i][j][S]表示前i个小时，还剩j把剑，顾客是否来过的状态为S
如果S记到2^24肯定是是无法接受的，实际上对于只来一次的顾客是没必要记录的，这样最多只有2^(25/2)种状态
为方便转移可以将p[i][j]的意义改为在第j次以及之后中，顾客i恰好在第j次来的概率，new_p[i][j]=p[i][j]/(1.0-p[i][1]-p[i][2]-...p[i][j-1])
直接枚举每个小时里面顾客是否来，以及是否卖来转移即可
*/
//#line 2 "NewItemShop.cpp"  
#include<bits/stdc++.h>
using namespace std;  
#define pb push_back  
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;  
typedef long long ll;  
typedef pair<int,int> pii;  
int move(string&s,int&p){
  int x=0;
  for(;p<SZ(s)&&s[p]>='0'&&s[p]<='9';p++)x=x*10+s[p]-'0';
  //printf("move %d\n",x);
  return x;
}
int t[55][25],c[55][25];
double p[55][25];
int cnt[55];
pair<int,int>id[25];
int pos_q[55],que[30];
double f[25][55][1<<12];
class NewItemShop {
	public:  
	double getMaximum(int swords, vector <string> customers)  {  
		// $CARETPOSITION$  
    vector<string>&str=customers;
    int n=SZ(str);
    int tot=0;
    for(int i=0;i<24;i++)id[i].fi=-1;
    for(int i=0;i<n;i++){
      cnt[i]=0;
      double all=100.0;
      for(int j=0;j<SZ(str[i]);){
        t[i][cnt[i]]=move(str[i],j);j++;
        id[t[i][cnt[i]]]=pii(i,cnt[i]);
        c[i][cnt[i]]=move(str[i],j);j++;
        p[i][cnt[i]]=move(str[i],j)/all;j++;
        all-=p[i][cnt[i]]*all;
        cnt[i]++;
      }
      if(cnt[i]>=2){
        pos_q[i]=tot;
        que[tot++]=i;
      }
    }
    for(int i=23;i>=0;i--){
      for(int j=0;j<=swords;j++){
        for(int S=0;S<1<<tot;S++){
          if(id[i].fi==-1){
            f[i][j][S]=f[i+1][j][S];
          }else{
            int x=id[i].fi;
            int y=id[i].se;
            //printf("xy %d %d\n",x,y);
            if(cnt[x]<2){
              //printf("A\n");
              f[i][j][S]=p[x][y]*f[i+1][j][S];
              if(j)f[i][j][S]=max(f[i][j][S],p[x][y]*(f[i+1][j-1][S]+c[x][y]));
              f[i][j][S]+=(1.0-p[x][y])*f[i+1][j][S];
            }else if(1<<pos_q[x]&S){
              //printf("B\n");
              f[i][j][S]=f[i+1][j][S];
            }else{
              //printf("C\n");
              f[i][j][S]=p[x][y]*f[i+1][j][S|1<<pos_q[x]];
              if(j)f[i][j][S]=max(f[i][j][S],p[x][y]*(f[i+1][j-1][S|1<<pos_q[x]]+c[x][y]));
              f[i][j][S]+=(1.0-p[x][y])*f[i+1][j][S];
            }
          }
          //printf("f %d %d %d: %.4lf\n",i,j,S,f[i][j][S]);
        }
      }
    }
    return f[0][swords][0];
	}  
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; string Arr1[] = { "8,1,80 16,100,11", "12,10,100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 19.0; verify_case(0, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = { "8,1,80 16,100,11", "12,10,100" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 21.8; verify_case(1, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; string Arr1[] = { "0,90,25 2,90,25 4,90,25 6,90,25", "7,100,80" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 90.0; verify_case(2, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 3; string Arr1[] = { "17,31,41 20,59,26 23,53,5", "19,89,79", "16,32,38 22,46,26", "18,43,38 21,32,7" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 135.5121414; verify_case(3, Arg2, getMaximum(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 5; string Arr1[] = { "1,1,10", "2,2,9", "3,3,8", "4,4,7", "5,5,6", "6,6,5", "7,7,4", "8,8,3", "9,9,2", "10,10,1" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.1999744634845344; verify_case(4, Arg2, getMaximum(Arg0, Arg1)); }

// END CUT HERE
  
};  

// BEGIN CUT HERE  
int main() {
	NewItemShop ___test;  
 	___test.run_test(-1);  
	return 0;  
}  
// END CUT HERE  
