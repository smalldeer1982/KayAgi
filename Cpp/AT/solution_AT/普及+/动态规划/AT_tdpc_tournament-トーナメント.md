# トーナメント

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_tournament

入力は以下の形式で標準入力から与えられる。

> $ K $ $ R_1 $ $ … $ $ R_{2^K} $

 答えを $ 2^K $ 行出力せよ。$ i $ 行目は人 $ i $ が優勝する確率であり、絶対誤差が $ 10^{-6} $ 以下のとき正当と判定される。 ```

1
2200
2600
```

```

0.090909091
0.909090909
```

```

3
2000
2500
2300
2700
2100
2400
2600
2200
```

```

0.000086893
0.122042976
0.005522752
0.493464665
0.000651695
0.053982389
0.321828438
0.002420190
```

## 说明/提示

### Constraints

 $ 2^K $ 人が参加するトーナメントがある。このトーナメントでは以下の形式で試合を行う。

- 第 1 ラウンドでは、1 と 2、3 と 4、… が試合を行う。
- 第 2 ラウンドでは、(1 と 2 の勝者) と (3 と 4 の勝者), (5 と 6 の勝者) と (7 と 8 の勝者), … が試合を行う。
- 第 3 ラウンドでは、((1 と 2 の勝者) と (3 と 4 の勝者) の勝者) と ((5 と 6 の勝者) と (7 と 8 の勝者) の勝者), ((9 と 10 の勝者) と (11 と 12 の勝者) の勝者) と ((13 と 14 の勝者) と (15 と 16 の勝者) の勝者), … が試合を行う。
- 以下同様に第 $ K $ ラウンドまで行う。
 
 第 $ K $ ラウンドの終了後に優勝者が決定する。人 $ i $ の Elo Rating が $ R_i $ であるとき、人 $ i $ の優勝確率を求めよ。   
 ただし、Elo Rating $ R_P $ の人 P と Elo Rating $ R_Q $ の人 Q が対戦した場合、人 P が勝つ確率は $ 1\ /\ (1\ +\ 10^{(R_Q\ -\ R_P)\ /\ 400}) $ であり、異なる試合の勝敗は独立であるとする。 - - - - - -

- $ 1\ <\ =\ K\ <\ =\ 10 $
- $ 0\ <\ =\ R_i\ <\ =\ 4000 $

# 题解

## 作者：fa_555 (赞：1)

under 题解 [AT682](https://www.luogu.com.cn/problem/AT682)

同步发布于[个人博客](https://fa555.github.io/2020/某At的dp场/#C-トーナメント)

### problem

~~翻译是我交的~~

有 $2^K \ (1 \le K \le 10)$ 人参加一场锦标赛，这场锦标赛按以下的形式进行。

*译者注：我知道可读性很差，但是很好理解，日语原题面就是这样的*

- 第 1 轮，1 和 2，3 和 4，… 进行比赛。
- 第 2 轮，(1 和 2 的胜者)和(3 和 4 的胜者)，(5 和 6 的胜者)和(7 和 8 的胜者)，… 进行比赛。
- 第 3 轮，((1 和 2 的胜者)和(3 和 4 的胜者)的胜者)和((5 和 6 的胜者)和(7 和 8 的胜者)的胜者)，((9 和 10 的胜者)和(11 和 12 的胜者)的胜者)和((13 和 14 的胜者)和(15 和 16 的胜者)的胜者)，… 进行比赛。
- 重复相同的过程，直到第 $K$ 轮。

第 $K$ 轮结束后将会决出优胜者。如果第 $i$ 个人的 Elo Rating 为 $R_i \ (1 \le R_i \le 4000)$，求出每个人成为优胜者的概率。

规定：如果 Elo Rating 为 $R_P$ 的人 $P$ 和 Elo Rating 为 $R_Q$ 的人 $Q$ 对战，人 $P$ 的获胜概率为 $1 / (1 + 10^{(R_Q - R_P) / 400})$。假设不同的比赛的胜负是互相独立的。

### solution

显然是道概率 dp（

设 $f_{k, i}$ 表示第 $k$ 轮比赛中第 $i$ 个人获胜的概率。不难得到这样的转移方程：

$$
f_{k, i} = f_{k - 1, i} \times \sum_{j \in S}{(f_{k - 1, j} \times P)}
$$

其中 $S$ 表示第 $k$ 轮中可能与 $i$ 比赛的人；$P$ 表示第 $j$ 个人此时获胜的概率。

边界条件 $f_{i, 0} = 1$。

答案即为 $f_{K, i} \ (1 \le i \le 2^K)$。总复杂度 $O(K \times 2^K)$。

### code

``` cpp
using db = double;

int R[1<<10|1];
db f[11][1<<10|1];

inline db calc(int p, int q) {
  return 1 / (1 + pow(10., (R[q] - R[p]) / 400.));
}

int main() {
  int K, N;
  
  cin >> K;
  N = 1 << K;
  for (int i = 1; i <= N; ++i)
    cin >> R[i];
  for (int i = 1; i <= N; ++i)
    f[0][i] = 1;
  for (int k = 1, len; k <= K; ++k) {
    len = 1 << k;
    for (int i = 1, mn, mx, mid, l, r; i <= N; ++i) {
      db now = 0;
      mx = (i - 1) / len * len + len, mn = mx - len + 1;
      mid = ((mn + mx) >> 1) + 1;

      if (i < mid) l = mid, r = mx;
      else l = mn, r = mid - 1;
      // 此处的 l ~ r 为可能此时和第 j 个人比赛的编号区间

      for (int j = l; j <= r; ++j)
        now += f[k - 1][j] * calc(i, j);
      f[k][i] = now * f[k - 1][i];
    }
  }
  for (int i = 1; i <= N; ++i)
    printf("%.9lf\n", f[K][i]);
  return 0;
}

```

---

## 作者：Shizaki_Crazy_Three (赞：0)

# [题目链接](https://www.luogu.com.cn/problem/AT_tdpc_tournament)

一道简单概率 dp 题，设 $f_{i}(x)$ 表示第 $i$ 轮第 $x$ 个人胜出的概率是多少。转移柿子不难推出

$$
f_{i}(x)=f_{i-1}(x)\times \sum_{y\in S}^{}f_{i-1}(y)\times w(x,y)
$$

$S$ 就是可以和 $x$ 对战的人的集合，$w(x,y)$ 就是题中给出的函数，接下来处理一下对战的人的区间这道题就做完了。时间复杂度 $O(k \cdot 2^{2k})$

### code

```cpp
#define LOCAL
#include<bits/stdc++.h>
#include<unistd.h>
#include<bits/extc++.h>
// #define getchar my_gechar
#define ll long long
#define lll __int128
#define db double
#define ldb long double
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int> 
#define vec Point
// #define max(a,b) ((a)<(b)?(b):(a))
// #define min(a,b) ((a)<(b)?(a):(b))
#define vi vector<int> 
#define vl vector<ll>
#define lowbit(x) (x)&(-x)
//#define sort stable_sort
using namespace std;
using namespace __gnu_pbds;
// char buffer[32769];
// unsigned li = 0;
// inline char my_gechar(){
    // if(buffer[li] == '\0') buffer[read(0, buffer, 32768)] = '\0',li = 0;
    // return buffer[li++];
// }
namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;

            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
                  inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline db read(double &x){return scanf("%lf",&x);}
            inline ldb read(long double &x){return scanf("%Lf",&x);}
            inline void dwrite(const double &x,int y=6,bool flag=1){printf("%.*lf",y,x),flag?putchar(' '):putchar(' ');}
            inline void dwrite(const long double &x,int y=6,bool flag=1){printf("%.*Lf",y,x),flag?putchar(' '):putchar(' ');}
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const char *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch[50];read(ch),x=ch;}
            inline void write(const string &x){int len=x.length();for(int i=0;i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>
            inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar(' ');}
            inline __int128 read(){static __int128 x;return read(x);}
            template<typename type>
            inline type put(type x,bool flag=1){write(x),flag?putchar(' '):putchar(' ');return x;}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;
struct Point{
	int x,y;
	Point operator +(const Point& b)const{return {x+b.x,y+b.y};}
	Point operator -(const Point& b)const{return {x-b.x,y-b.y};}
	bool operator <(const Point& b)const{
		if(x!=b.x)return x<b.x;
		return y<b.y;
	}
};
const int N=1e5+5;
const int M=1e6+5;
const int inf=1e9+5;
const int mod=1e9+7;
const int bit=50;
//mt19937 sj(chrono::steady_clock::now().time_since_epoch().count());
int B=705;
db rp[10005],f[11][10005];
inline db calc(int p,int q){
	return 1/(1+pow(10.0,(rp[q]-rp[p])/400.0));
}
int n,k;
inline void solve(){
	read(k);
	for(int i=1;i<=(1<<k);++i) read(rp[i]);
	for(int i=1;i<=(1<<k);++i) f[0][i]=1;
	for(int i=1;i<=k;++i){
		int len=1<<i;// 区间长度
		for(int j=1;j<=(1<<k);++j){
			int R=(j-1)/len*len+len,L=R-len+1;
			int mid=L+R>>1;
			int l,r;
			if(j<=mid) l=mid+1,r=R;
			else l=L,r=mid;
			db ans=0;
			for(int op=l;op<=r;++op){
				ans+=f[i-1][op]*calc(j,op);
			}
			f[i][j]=ans*f[i-1][j];
		}
	}
	for(int i=1;i<=(1<<k);++i){
		dwrite(f[k][i],10);
		cout<<endl;
	}
} 

signed main()
{   
    int _=1;
    while(_--) solve();
    return (0-0);
}
```

---

## 作者：cosf (赞：0)

## [Tournament](https://www.luogu.com.cn/problem/AT_tdpc_tournament)

标准 dp 题。

我们令 $dp_{i, j}$ 表示 $i$ 经过第 $j$ 轮后获胜的概率。默认 $dp_{i, 0} = 1$。

我们假设 $S_j, S_{j + 1}$ 表示第 $l$ 轮中可能会对战的两个集合。

例如第 $2$ 轮时，$S_0 = \{1, 2\}, S_1 = \{3, 4\}, \dots$。

则 $\forall m \in S_j, o \in S_{j + 1} (\frac{j}{2} \in \mathbb{Z}), dp_{m, l} \overset{+}{\gets}dp_{m, l - 1}\times dp_{o, l - 1}\times R, dp_{o, l} \overset{+}{\gets}dp_{m, l - 1}\times dp_{o, l - 1}\times (1 - R)$，$R$ 是 $m$ 获胜的概率。


```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAXN 1050
#define MAXL 15

using ld = long double;

ld val[MAXN];
ld dp[MAXN][MAXL];

ld calc(ld a, ld b)
{
    return 1.0l / (1 + pow(10.0l, (b - a) / 400.0l));
}

int k;

int main()
{
    cin >> k;
    int n = (1 << k);
    for (int i = 0; i < n; i++)
    {
        cin >> val[i];
        dp[i][0] = 1.0l;
    }
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < n; j += (1 << i))
        {
            int l = j + (1 << (i - 1)), r = j + (1 << i);
            for (int m = j; m < l; m++)
            {
                for (int o = l; o < r; o++)
                {
                    ld p = calc(val[m], val[o]);
                    dp[m][i] += dp[m][i - 1] * dp[o][i - 1] * p;
                    dp[o][i] += dp[m][i - 1] * dp[o][i - 1] * (1 - p);
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << fixed << setprecision(9) << dp[i][k] << endl;
    }
    return 0;
}

```


---

