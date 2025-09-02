# Research Rover

## 题目描述

Unfortunately, the formal description of the task turned out to be too long, so here is the legend.

Research rover finally reached the surface of Mars and is ready to complete its mission. Unfortunately, due to the mistake in the navigation system design, the rover is located in the wrong place.

The rover will operate on the grid consisting of $ n $ rows and $ m $ columns. We will define as $ (r,c) $ the cell located in the row $ r $ and column $ c $ . From each cell the rover is able to move to any cell that share a side with the current one.

The rover is currently located at cell $ (1,1) $ and has to move to the cell $ (n,m) $ . It will randomly follow some shortest path between these two cells. Each possible way is chosen equiprobably.

The cargo section of the rover contains the battery required to conduct the research. Initially, the battery charge is equal to $ s $ units of energy.

Some of the cells contain anomaly. Each time the rover gets to the cell with anomaly, the battery looses half of its charge rounded down. Formally, if the charge was equal to $ x $ before the rover gets to the cell with anomaly, the charge will change to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/5e007d05e4d6f2ed51d5f62962d41cc3679ff923.png).

While the rover picks a random shortest path to proceed, compute the expected value of the battery charge after it reaches cell $ (n,m) $ . If the cells $ (1,1) $ and $ (n,m) $ contain anomaly, they also affect the charge of the battery.

## 说明/提示

In the first sample, the rover picks one of the following six routes:

1. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/9ec03018ca0f56c6c2f6d978bba5abe354af00a2.png), after passing cell $ (2,3) $ charge is equal to $ 6 $ .
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/c33021a457ac8c5bc889f817a80d61835c80a6b0.png), after passing cell $ (2,3) $ charge is equal to $ 6 $ .
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/f31c3021594dce78e1218b41ad36645544e3eb2f.png), charge remains unchanged and equals $ 11 $ .
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/d616d340616d474f1cf131e388bc97ff077c00fd.png), after passing cells $ (2,1) $ and $ (2,3) $ charge equals $ 6 $ and then $ 3 $ .
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/58b582f83e30271c9a15562ebd2f560f6b5dd797.png), after passing cell $ (2,1) $ charge is equal to $ 6 $ .
6. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/856271589dd61834f189db966542ee9a7b753d25.png), after passing cell $ (2,1) $ charge is equal to $ 6 $ .

Expected value of the battery charge is calculated by the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/56e29a53ed442392bc44fee422ffcf414eab5cce.png).

Thus $ P=19 $ , and $ Q=3 $ .

 $ 3^{-1} $ modulo $ 10^{9}+7 $ equals $ 333333336 $ .

 $ 19·333333336=333333342 (mod 10^{9}+7) $

## 样例 #1

### 输入

```
3 3 2 11
2 1
2 3
```

### 输出

```
333333342
```

## 样例 #2

### 输入

```
4 5 3 17
1 2
3 3
4 1
```

### 输出

```
514285727
```

## 样例 #3

### 输入

```
1 6 2 15
1 1
1 5
```

### 输出

```
4
```

# 题解

## 作者：Limit (赞：14)

# 题目大意

给出一张 $n\cdot m$ 的图,图上有 $k$ 个特殊点,在初始点有一个贡献 $t$ 每经过一个特殊点会导致贡献变为 $\lceil\frac{t}{2}\rceil$.求到 $(n,m)$ 时的期望贡献.

# 分析

$n,m$ 的范围都有 $10^5$ 显然不能 $\mathcal{O}(nm)$ 的 dp,考虑只会在特殊点时贡献才会改变,所以用 $f_{i,j}$ 表示终点在第 $i$ 个点,总共经过了 $j$ 个点的方案数.这个东西看起来是 $k^2$ 的,而且转移也需要 $\mathcal{O}(k)$,时间复杂度 $\mathcal{O}(k^3)$ 不能过.但是一个数经过了 $\log$ 次除二向上取整后就会变成 $1$,所以对于 $f_{i,j}(\log_2t<j)$ 的方案是没有用的,所以时间复杂度就变成了 $\mathcal{k^2\log_2t}$ 可以通过本题.

下面考虑如何转移 $f_{i,j}$,因为在计算 $x_i,y_i$ 这个点时需要把所以 $x_j\leq x_i\land y_j\leq y_i$ 的点全部计算出来,所以要先对所有点按 $x$ 的大小($y$ 的大小)排序.但是这个 $f_{i,j}$ 的转移好像还是很麻烦,不如把 $f_{i,j}$ 所代表的意义改成到第 $i$ 个点时**至少**经过 $j$ 个特殊点的方案数.那么转移方程就是:
$$
f_{i,j}=\sum_{k\in[1,i]\land x_k\leq x_i\land y_k\leq y_i}C^{x_i+y_i-x_k-y_k+2}_{x_i-x_k+1}\cdot f_{k,j-1}
$$
对于第 $i$ 个特殊点经过恰好 $j$ 次的方案数就是 $f_{i,j}-f_{i,j+1}$.

然后会发现第一个样例就过不去.

在最后的贡献中 $(1,1)\to(2,1)\to(2,2)\to(2,3)\to(3,3)$ 会计算两次,但是如果 $f_{k,j}$ 表示的是第 $k$ 个点时**恰好**经过 $j$ 个特殊点的方案数,那么是对的.所以需要在每次计算出**至少**的方案数后直接计算出**恰好**的方案数.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=2005;
const int MAXNUM=1e6+5;
const long long MOD=1e9+7;
long long Pow(long long a,long long b,long long mod=MOD)
{
	long long result=1;
	while(b)
	{
		if(b&1)
		{
			result*=a;
			result%=mod;
		}
		a*=a;
		a%=mod;
		b/=2;
	}
	return result;
}
#define INV(a) Pow(a,MOD-2)
long long fac[MAXNUM],inv[MAXNUM];
void PreCom()
{
	fac[0]=1;
	REP(i,1,MAXNUM-1)
	{
		fac[i]=fac[i-1]*i%MOD;
	}
	inv[MAXNUM-1]=INV(fac[MAXNUM-1]);
	DOW(i,MAXNUM-2,0)
	{
		inv[i]=inv[i+1]*(i+1)%MOD;
	}
}
long long C(int n,int m)
{
	if(n<m)
	{
		return 0;
	}
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
int n,m,k,s;
struct Point
{
	int x,y;
}point[MAXN];
bool Cmp(Point a,Point b)
{
	if(a.x==b.x)
	{
		return a.y<b.y;
	}
	return a.x<b.x;
}
long long f[MAXN][23];
int arr[23];
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&s);
	PreCom();//预处理组合数
	point[0].x=1;
	point[0].y=1;
	REP(i,1,k)
	{
		scanf("%d%d",&point[i].x,&point[i].y);
	}
	point[k+1].x=n;
	point[k+1].y=m;
	sort(point+1,point+1+k,Cmp);//按 x 排序
	f[0][0]=1;
	REP(i,1,k+1)
	{
		REP(j,0,i-1)
		{
			if(point[j].x<=point[i].x&&point[j].y<=point[i].y)//找到可以转移过来的点
			{
				int len=point[i].x-point[j].x+1;
				int wide=point[i].y-point[j].y+1;
				long long c=C(len+wide-2,len-1);//计算两点间的路径条数
				REP(p,1,22)
				{
					f[i][p]+=f[j][p-1]*c%MOD;//dp 至少经过 p 个特殊点的方案数
					f[i][p]%=MOD;
				}
			}
		}
		REP(p,1,22)
		{
			f[i][p]-=f[i][p+1];//将至少经过 p 个特殊点的方案数变为恰好经过 p 个特殊点的方案数
			f[i][p]+=MOD;
			f[i][p]%=MOD;
		}
	}
	arr[1]=s;
	REP(i,2,21)
	{
		arr[i]=(arr[i-1]+1)/2;
	}
	long long all=C(n+m-2,n-1);
	long long answer=0;
	REP(i,1,21)//计算经过小于等于 log 次的方案数的贡献
	{
		answer+=f[k+1][i]*arr[i];
		all-=f[k+1][i];
		all%=MOD;
		all+=MOD;
		all%=MOD;
		answer%=MOD;
	}
	answer+=all;
	answer%=MOD;
	printf("%lld\n",answer*INV(C(n+m-2,n-1))%MOD);//计算期望并输出
	return 0;
}
```



---

## 作者：奇米 (赞：9)

## 题解- CF722E 

* **题目意思**

	题目就是让你从$(1,1)$走到$(n,m)$的道路中有$k$个特殊点，没经过一个特殊点会使分数变为原来一半，问从$(1,1)$到$(n,m)$的期望得分（对$10^9+7$取模）
    
* $Sol$
	
    我们首先把$(1,1),(n,m)$也看成特殊点，但是分数不用除二，然后为了保证每次是向下或向右先对$x$排序即可，接下来就是$Dp$啦。
    
    这道题目如果把状态设为$f_{i,j}$表示到$i$点经过$j$个特殊点的方案数的话，转移就很麻烦了。所以我们把状态改为$f_{i,j}$表示表示到$i$点**至少**经过$j$个特殊点的方案数，这样就可以避免一些很麻烦的容斥。
    
    然后我们再设$g_{i,j}$表示从$i$到$j$点的方案数，那么这就变为一个清新的组合数问题，我们考虑一共走了$(i+j)$次，最后选$i$次向上，所以
    
    $g_{i,j}=C^{|x_i-x_j|}_{|x_i-x_j|+|y_i-y_j|}$
    
    对于$f_{i,j}$的转移我们考虑从$j-1$转移过来，这里很好的体现状态设计的正确性，我们计算正好$j$次，所以
    
    $f_{i,j}=\sum f_{k,j-1}-f_{k,j}(x_k\leq x_i,y_k\leq y_i)$
    
    其中$(f_{k,j-1}-f_{k,j})$表示经过$j-1$个特殊点到达$i$的方案数。
    
    那么最后的答案就是$(C^{n}_{n+m})$ $^{-1} \times \sum(f_{k,i}-f_{k,i+1}) \times (s/2^{i})$
    

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int N=1e5+5;

inline int ksm(int x,int y)
{
	int ret=1ll;
	while(y)
	{
		if(y&1) ret=ret*x%mod;
		x=x*x%mod;
		y>>=1ll;
	}
	return ret;
}

int n,m,s,k,f[N][31],ans,jc[N*2],inv[N*2];

struct nood
{
	int x,y;
	inline bool friend operator < (const nood &b,const nood &c)
	{
		if(b.x==c.x) return b.y<c.y;
		return b.x<c.x;
	}
};
nood a[N];

inline int C(int x,int y)
{
	return jc[x]%mod*inv[x-y]%mod*inv[y]%mod;
}

inline int calc(nood b,nood c)
{
	return C(c.x-b.x+c.y-b.y,c.x-b.x);
}

signed main()
{
	n=read();
	m=read();
	k=read();
	s=read();
	inv[0]=jc[0]=1;
	for ( int i=1;i<=n+m;i++ ) jc[i]=jc[i-1]*i%mod;
	for ( int i=1;i<=n+m;i++ ) inv[i]=ksm(jc[i],mod-2)%mod;
	for ( int i=1;i<=k;i++ ) a[i]=(nood){read(),read()};
	sort(a+1,a+k+1);
	if(a[1].x!=1||a[1].y!=1) 
	{
		a[++k]=(nood){1,1};
		s*=2;
	}
	if(a[k].x!=n||a[k].y!=m) a[++k]=(nood){n,m};
	//加入虚拟点(1,1)/(n,m) 
	else s=(s+1)/2;
	int gs=log2(s)+1;
	//最多经过gs个特殊点 
	sort(a+1,a+k+1);
	f[1][0]=1;
	//f(i,j)：到点i经过（至少）j个特殊点的方案数 
	for ( int i=2;i<=k;i++ )
	{
		f[i][1]=calc(a[1],a[i]);
		for ( int j=2;j<=gs;j++ )
			for ( int t=1;t<i;t++ ) 
				if(a[t].x<=a[i].x&&a[t].y<=a[i].y)
				{
					f[i][j]+=(f[t][j-1]*calc(a[t],a[i]))%mod;
					f[i][j]=(f[i][j]+mod)%mod;
					f[i][j]-=(f[t][j]*calc(a[t],a[i]))%mod;
					f[i][j]=(f[i][j]+mod)%mod;
				}
	}
	int ans=0;
	for ( int i=1;i<=gs;i++ ) 
	{
		s-=s/2;
		ans=(ans+(f[k][i]-f[k][i+1])*s%mod+mod)%mod;
	}
	ans=(ans*ksm(calc(a[1],a[k]),mod-2)+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
/*
3 3 2 11
2 1
2 3
*/
	
```


---

## 作者：伟大的王夫子 (赞：7)

本题思路与 [CF559C](https://www.luogu.com.cn/problem/CF559C) 十分类似，但本题难度略高一些。本质上都是先求出方案总数，然后再减去不合法的方案数。

为了方便，我们多设置一个特殊点 $r_{k+1} = n$，$c_{k+1}=m$。

不妨设 $dp_{i, j}$ 为到达第 $i$ 个点，并且经过了 $\le j$ 个特殊点的方案个数。由于每次经过一个特殊点，$s$ 的值会除以二，所以 $j$ 的范围是 $O(\log s)$。我们只需在 $O(k)$ 的时间完成转移即可。

我们先无视 $j$，给 $dp_{i, j}$ 赋初值 $\binom{r_i+c_i-2}{r_i-1}$，即从 $(1,1)$ 走到 $(r_i,c_i)$ 的方案数。然后，我们考虑有哪些不合法的方案。

考察一个点从 $(1,1)$ 走到 $(r_i,c_i)$ 的路径，如果最终经过的特殊点数大于 $j$，那么必定在中间一个特殊点经过特殊点数等于 $j$，并且这个点是唯一的。利用这个性质，我们枚举中间这个点 $k$，减去到达这个点时**刚好**经过 $j$ 个特殊点时的方案数 $dp_{k, j} - dp_{k, j - 1} $ 与从第 $k$ 个点到达第 $i$ 个点的方案数。这个计算不合法方案的时间复杂度是 $O(k)$。总共有 $O(k \log s)$ 个状态，所以时间复杂度为 $O(k ^ 2 \log s)$。

做这类计数问题最重要的是不重不漏。然后多注意细节。有一个坑点，就是在我们程序中 $j$ 的最大值大概为 21、22 左右，但是经过次数比这些大的方案数我们仍然要统计一下，因为到了最后，$s$ 的值再怎么除以 2 也会大于等于 1。否则会在第 10 个点 WA。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005, P = 1e9 + 7, M = 200005;
int n, m, s, K, f[25];
typedef long long LL;
LL dp[N][25], jcinv[M], jc[M];
struct QAQ {
	int x, y;
} a[N];
LL power(LL a, LL b) {
	LL c = 1;
	for (; b; b >>= 1) {
		if (b & 1) c = c * a % P;
		a = a * a % P;
	}
	return c;
}
LL C(int n, int m) {
	return jc[n] * jcinv[m] % P * jcinv[n - m] % P;
}
int main() {
	scanf("%d%d%d%d", &n, &m, &K, &s);
	f[0] = s;
	for (int i = 1; i <= 24; ++i) f[i] = (f[i - 1] - 1) / 2 + 1;	
	for (int i = 1; i <= K; ++i) scanf("%d%d", &a[i].x, &a[i].y);
	jc[0] = jcinv[0] = 1;
	for (int i = 1; i <= n + m; ++i) jc[i] = jc[i - 1] * i % P;
	jcinv[n + m] = power(jc[n + m], P - 2);
	for (int i = n + m - 1; i; --i) jcinv[i] = jcinv[i + 1] * (i + 1) % P;
 	sort(a + 1, a + K + 1, [](const QAQ &a, const QAQ &b) {return a.x < b.x || (a.x == b.x && a.y < b.y);});
	a[K + 1].x = n, a[K + 1].y = m;
	for (int i = 1; i <= K + 1; ++i)
		for (int j = 1; j <= 24; ++j) {
			dp[i][j] = C(a[i].x + a[i].y - 2, a[i].x - 1);
			for (int k = 1; k < i; ++k) {
				if (a[k].x > a[i].x || a[k].y > a[i].y) continue;
				dp[i][j] -= (dp[k][j] - dp[k][j - 1] + P) % P * C(a[i].x + a[i].y - a[k].x - a[k].y, a[i].x - a[k].x) % P;
				dp[i][j] = (dp[i][j] + P) % P;
			} 
		}
	LL ans = 0;
	for (int i = 1; i <= 24; ++i) {
		ans += f[i - 1] * (dp[K + 1][i] - dp[K + 1][i - 1] + P) % P;
		ans %= P;
	}
	ans += (C(n + m - 2, n - 1) - dp[K + 1][24] + P) % P;
	ans %= P;
	ans = ans * power(C(n + m - 2, n - 1), P - 2) % P;
	printf("%lld", ans);
}
```

如有写错误的地方，欢迎评论区或私信指出。

---

## 作者：Alex_Wei (赞：5)

- Update on 2022.10.18：修改表述。

> [CF722E Research Rover](https://www.luogu.com.cn/problem/CF722E)

设 $f_{i, j}$ 表示从 $(1, 1)$ 到关键点 $j$ **恰好** 经过 $i$ 个关键点的方案数。关键点以 $x$ 为第一关键字从小到大，$y$ 为第二关键字从小到大排序，保证后面的关键点不会转移到前面。

朴素想法是直接 $f_{i, j} = \sum\limits_{k = 0} ^ {j - 1} f_{i - 1, k} p(k, j)$，其中 $p(k, j)$ 表示 $k$ 到 $j$ 的方案数，可以组合数 $\mathcal{O}(1)$ 计算。但我们无法保证 $k\to j$ 的路径上不经过其它关键点，会算重。

任何一条以 $k, j$ 之间某个点 $q(q\neq k\land q\neq j)$ 作为下一个关键点的路径均会被算到 $f_{i, q}$ 里面去，所以我们只需用不限制其它关键点时 $k$ 作为路径上第 $i - 1$ 个关键点到 $j$ 的方案数，减去不限制其它关键点时 $k$ 作为路径上第 $i$ 个关键点到 $j$ 的方案数。

综上，我们通过 **差分容斥**，得到转移 $f_{i, j} = \sum\limits_{k = 0} ^ {i - 1} (f_{k, j - 1} - f_{k, j}) \times p(k, i)$。

第一维只需开到 $\log_2 s$ 大小，剩下来的方案数可以用总方案数减去经过关键点个数 $\leq \log_2 s$ 的方案数。

时间复杂度 $\mathcal{O}(n + k ^ 2\log s)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using uint = unsigned int;
using ld = long double;
// using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(ll x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 2e5 + 5;
constexpr int K = 2e3 + 5;
constexpr int C = 22;
constexpr int mod = 1e9 + 7;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
int fc[N], ifc[N], coef[K][K];
int bin(int n, int m) {return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;}
int n, m, k, s, ans, f[C + 1][K];
pii x[K];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  for(int i = fc[0] = 1; i < N; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[N - 1] = ksm(fc[N - 1], mod - 2);
  for(int i = N - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  cin >> n >> m >> k >> s;
  for(int i = 1; i <= k; i++) cin >> x[i].fi >> x[i].se;
  sort(x + 1, x + k + 1);
  f[0][0] = 1, x[0] = {1, 1}, x[++k] = {n, m};
  for(int i = 0; i <= k; i++) 
    for(int j = i + 1; j <= k; j++) {
      pii u = x[i], v = x[j];
      if(u.fi > v.fi || u.se > v.se) continue;
      coef[i][j] = bin(v.fi - u.fi + v.se - u.se, v.fi - u.fi);
    }
  for(int i = 1; i < C; i++) {
    for(int j = 1; j <= k; j++) {
      for(int l = 0; l < j; l++) {
        add(f[i][j], 1ll * f[i - 1][l] * coef[l][j] % mod);
        add(f[i][j], mod - 1ll * f[i][l] * coef[l][j] % mod);
      }
    }
  }
  f[C][k] = coef[0][k];
  for(int i = 1; i < C; i++) add(f[C][k], mod - f[i][k]);
  for(int i = 1; i <= C; i++, s -= s >> 1) add(ans, 1ll * s * f[i][k] % mod);
  cout << 1ll * ans * ksm(coef[0][k], mod - 2) % mod << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/10/10
author: Alex_Wei
start coding at 
finish debugging at 
*/
```

---

## 作者：hdkk (赞：3)

为啥题解区都是神秘差分做法，来发不用脑子的二项式反演。

首先恰好转成钦定，我们设 $dp_{i,j}$ 为走到了第 $i$ 个点，钦定经过了 $j$ 个黑点的方案数，转移就是枚举上一个钦定的黑点和钦定的个数，复杂度 $O(n^3)$ 显然过不去。

那么我们发现实际上经过黑点次数大于 $\log s$ 的话权值一定为 $1$，不需要我们关注，考虑把容斥系数压到 dp 过程里的优化，我们写出二项式反演的式子。

$$f_i=\sum_{j=1}^n(-1)^{j-i}\binom{j}{i}g_j$$

$$(-1)^if_i=\sum_{j=i}^n(-1)^j\binom{j}{i}g_j$$

可以每次钦定都乘上 $-1$ 的容斥系数，$\binom{j}{i}$ 可以看成在 $j$ 个钦定的点中选出 $i$ 个的方案数。

于是我们重新设计 dp 状态：设 $dp_{i,j}$ 表示走到了第 $i$ 个点，在钦定的点中选了 $j$ 个的方案数。


$$dp_{i,j}=-\sum_k \binom{x_i-x_k+y_i-y_k}{x_i-x_k}(dp_{k,j}+dp_{k,j-1})$$

第二维是 $O(\log s)$ 的，所以复杂度是 $O(n^2 \log s)$。

代码：


```cpp
#include<bits/stdc++.h>

using namespace std;
const int M=2005,md=1e9+7,N=2e6+5;
int ks(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=1ll*res*a%md;
		a=1ll*a*a%md;
		b>>=1;
	}
	return res;
}
struct node{
	int x,y;
	friend bool operator<(const node &r1,const node &r2)
	{
		if(r1.x!=r2.x) return r1.x<r2.x;
		return r1.y<r2.y;
	}
}a[M];
int fac[N],ifac[N],n,m,k,s,f[M][M],g[M];
void inline add(int &x,int y)
{
	x+=y;
	if(x>=md) x-=md;
 } 
void inline del(int &x,int y)
{
	x-=y;
	if(x<0) x+=md;
}
int inline inc(int x,int y)
{
	return x+y-(x+y>=md?md:0);
}
int inline inc1(int x,int y)
{
	return x-y+(x<y?md:0);
}
int c(int n,int m)
{
	return 1ll*fac[n]*ifac[m]%md*ifac[n-m]%md;
}
signed main()
{
	fac[0]=fac[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=2e6;i++)
		fac[i]=1ll*fac[i-1]*i%md,ifac[i]=1ll*ifac[md%i]*(md-md/i)%md;
	for(int i=2;i<=2e6;i++)
		ifac[i]=1ll*ifac[i-1]*ifac[i]%md;
	cin>>n>>m>>k>>s;
	for(int i=1;i<=k;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+k);
	for(int i=1;i<=k;i++)
	{
		int x=a[i].x,y=a[i].y;
		//cout<<x<<' '<<y<<endl;
		del(f[i][0],c(x-1+y-1,x-1));
		del(f[i][1],c(x-1+y-1,x-1));
		for(int j=1;j<i;j++)
		{
			if(a[j].x>x||a[j].y>y) continue;
			int v=c(x-a[j].x+y-a[j].y,x-a[j].x);
			//cout<<v<<endl;
			del(f[i][0],1ll*f[j][0]*v%md);
			for(int l=1;l<=20;l++)
				del(f[i][l],1ll*f[j][l]*v%md),del(f[i][l],1ll*f[j][l-1]*v%md);
		}
		//cout<<f[i][0]<<' '<<f[i][1]<<' '<<f[i][2]<<endl;
		for(int j=0;j<=20;j++) add(g[j],1ll*c(n-x+m-y,n-x)*f[i][j]%md);
	}
	add(g[0],c(n-1+m-1,n-1));
	for(int i=1;i<=20;i+=2) g[i]=inc1(0,g[i]);
	int sum=c(n-1+m-1,n-1),ans=0;
	for(int i=0;i<=20;i++)
	{
		add(ans,1ll*s*g[i]%md);
		del(sum,g[i]);
		//cout<<g[i]<<endl;
		s=(s+1)/2;
	}
	add(ans,sum);
	cout<<1ll*ans*ks(c(n-1+m-1,n-1),md-2)%md;
}
```

---

## 作者：Immortal_Bird (赞：3)


###  date : 2019.7.24

题目大意：

给出一个n*m的方格阵，从(1,1)走到(n,m)，只能向下或向右走，(1,1)会有一个初始分数s。在整个图中有k个特殊点，每经过一个点，都会将目前剩余的分数除以2且向上取整。求(1,1)到(n,m)的期望得分。

1<=n,m<=1e5;0<=k<=2000;1<=s<=1e6;

 


------------

 

DP+容斥。

 

1. 要求期望就好好求嘛，反正我看不懂某篇题解为什么答案只算经过k个特殊点的方案数

2. 由于n,m<=1e5，显然不能暴力枚举点,yy出复杂度不含n、m. ,所以我们可以枚举特殊点。

3. 仔细分析，发现当k>log2s的时候s到(n,m)的值就为1了。所以最多枚举20个特殊点左右。

4. 枚举特殊点就要将特殊点排序，那么就以横坐标为第一关键字，以纵坐标为第二关键字。

5. 然后就容斥搞啊

6. 倒着来。

 

	令d[i][j]表示从点i走到点j的方案总数，
根据小学组合数我们可以知道$ d[i][j] = C(a[j].x-a[i].x+a[j].y-a[i].y , a[j].x - a[i].x) $ 

	设
g[i][j]
表示从点i到(n,m)**恰好经过**j个障碍点（不包括点i）的方案数。

	显然很难求。那么我们添加一个辅助变量，
f[i][j]
表示从点i到点(n,m)**至少经过**j个点的方案数。

	所以f数组的求法就是将总数减去**超过j**个点的方案数。

	$ f[i][j] = d[i][(n,m)] - ∑(g[k][j]*d[i][k]), $
	满足 $ a[k].x >= a[i].x,a[k].y>=a[i].y; $
    （此时的用到的g已经算出来了，它是从大到小枚举的）

	所以, $ g[i][j] =f[i][j] - f[i][j-1] $。 

	**最后一步有点像前缀和。**



	代码里合并在一起了。

 


Code:




```cpp
#include<bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxn = 2e5+5;

int a[30],fac[maxn],ine[maxn],g[maxn][30];

struct node{
    int x,y;
}e[3000];

bool cmp(node a,node b){
    return a.x == b.x?a.y < b.y:a.x < b.x;
}

int C(int x,int y){
    return 1ll * fac[x]*ine[y]%mod*ine[x-y]%mod;
}

int qpow(int x,int y){
    int cnt = 1;
    while(y){
        if(y&1)cnt = 1ll*cnt*x%mod;
        y>>=1;x = 1ll*x*x%mod;
    }
    return cnt;
}

int main(){
    int n,m,k,s;
    cin>>n>>m>>k>>s;
    fac[0] = 1;
    for(int i = 1;i<=n+m;++i)fac[i] = 1ll*fac[i-1]*i%mod;
    ine[n+m] = qpow(fac[n+m],mod-2);
    for(int i = n+m;i>=1;--i)ine[i-1] = 1ll*ine[i]*(i)%mod;
    int len = 0;a[0] = s;
    for(len = 1;s != 1;len++)a[len] = s = (s+1)/2;
    len--;
    for(int i = 1;i<=k;++i)cin>>e[i].x>>e[i].y;
    sort(e+1,e+k+1,cmp);e[0].x = e[0].y = 1;
    for(int i = k;i>=0;--i){
        for(int j = 0;j<len;++j){
            g[i][j] = C(n-e[i].x+m-e[i].y,n-e[i].x);
            for(int l = k;l>i;--l){
                if(e[i].y <= e[l].y){
                    g[i][j] = (g[i][j]-1ll*g[l][j]*C(e[l].x-e[i].x+e[l].y-e[i].y,e[l].x-e[i].x))%mod;
                }
            }
        }//上面的g数组相当于f数组。
        g[i][len] = C(n-e[i].x+m-e[i].y,n-e[i].x);
        for(int j = len;j>=1;--j)g[i][j] = (g[i][j]-g[i][j-1])%mod;
    }
    int ans = 0;
    for(int i = 0;i<=len;++i)ans = (ans + 1ll*(g[0][i]+mod)*a[i])%mod;
    ans = 1ll*ans*qpow(C(n+m-2,n-1),mod-2)%mod;
    cout<<ans<<endl;
}
```
```


 

 

 

---

## 作者：worldvanquisher (赞：1)

## 题目大意
$n\times m$ 的棋盘，有 $k$ 个点，每次只能向下或向右走。初始有权值 $s$ ，每经过一个点会使其除以 $2$ 向上取整。问走到 $(n,m)$ 时的期望权值。
## 分析
首先看到题面就知道显然不是 $O(nm)$ 暴力 dp。观察一下数据范围发现果然如此。考虑一个和 $k$ 相关的 dp。

观察到 $k$ 只有 $2000$，这启示我们可以枚举两层 $k$ 来解决问题。我们可以设 $dp[i][j]$ 为考虑到第 $i$ 个点，前面已经经过了 $j$ 个点的方案数，然后三层循环，第一层枚举 $i$，第二层枚举从哪个点转移过来，第三层枚举 $j$，进行转移，复杂度 $O(k^3)$。

然后观察到每次经过一个点都会使权值 $x$ 变成 $\left\lceil \dfrac x2\right\rceil$，也就是说第二维 $j$ 只有 $O(\log s)$ 个状态，复杂度变为 $O(k^2\log s)$，可以通过。

最后考虑怎么转移。为了方便，我们把起点 $(1,1)$ 看作第 $0$ 个点，终点 $(n,m)$ 看作第 $k+1$ 个点。在扫一个点之前，我们需要扫完它左上角的所有点，也就是按照 $x,y$ 两个关键字对所有点排一遍序。那么转移的时候考虑 $(x_1,y_1)$ 和 $(x_2,y_2)$ 两点间的路径数就是 $\binom{x_2-x_1+y_2-y_1}{x_2-x_1}$，有转移方程：
$$dp[i][j]=\sum_{x_k\le x_i,y_k\le y_i} dp[k][j-1]\times \binom{x_i-x_k+y_i-y_k}{x_i-x_k} $$
然而我们这样转移，如果 $i,k$ 两点之间有其他的点，那么就会算重。去重比较麻烦，不如直接改变状态定义：$dp[i][j]$ 为考虑到第 $i$ 个点，经过的点数 $\ge j$ 的方案数，然后按照上式进行 dp，每次循环后再做一次差分转换成只经过 $j$ 个点的方案数即可。
## 代码
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
const int mod=1000000007;
int n,m,K,s,dp[2010][30],x[2010],y[2010],jc[200010],inv[200010],a[30];
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int C(int n,int m){
    return 1ll*jc[n]*inv[m]%mod*inv[n-m]%mod;
}
struct node{
    int x,y;
    bool operator<(const node &s)const{
        return x==s.x?y<s.y:x<s.x;
    }
}p[2010];
int main(){
    scanf("%d%d%d%d",&n,&m,&K,&s);jc[0]=inv[0]=1;
    p[0].x=p[0].y=1;
    for(int i=1;i<=K;i++)scanf("%d%d",&p[i].x,&p[i].y);
    K++;p[K].x=n;p[K].y=m;
    sort(p+1,p+K+1);
    for(int i=1;i<=n+m;i++)jc[i]=1ll*jc[i-1]*i%mod;
    inv[n+m]=qpow(jc[n+m],mod-2);
    for(int i=n+m-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
    dp[0][0]=1;
    int lg=1;a[1]=s;
    for(int i=2;;i++,lg++){
        a[i]=(a[i-1]+1)>>1;
        if(a[i]==1)break;
    }
    lg++;
    for(int i=1;i<=K;i++){
        for(int j=0;j<i;j++){
            if(p[j].x>p[i].x||p[j].y>p[i].y)continue;
            for(int k=1;k<=lg;k++){
                dp[i][k]=(dp[i][k]+1ll*dp[j][k-1]*C(p[i].x-p[j].x+p[i].y-p[j].y,p[i].x-p[j].x)%mod)%mod;
            }
        }
        for(int j=1;j<=lg;j++)dp[i][j]=(dp[i][j]-dp[i][j+1]+mod)%mod;
    }
    int ans=0;
    for(int i=1;i<=lg;i++)ans=(ans+1ll*dp[K][i]*a[i]%mod)%mod;
    ans=1ll*ans*qpow(C(n+m-2,n-1),mod-2)%mod;
    printf("%d\n",ans);
    return 0;
}
```
## 后记
在学校的数学题单里发现了[CF599C](https://www.luogu.com.cn/problem/CF559C)，感到十分相似，遂发一篇题解。各位大佬做完后不妨把这个题切掉。

---

## 作者：Purslane (赞：0)

# Solution

为啥我看不懂题解在讲什么，是我太菜了吗。感觉为什么能直接差分都没怎么讲明白啊。

考虑 $dp_{i,j}$ 表示从原点到第 $i$ 个关键点，一共经过了 $j$ 个关键点的总方案数。转移就是枚举在它左上角的关键点 $k$，$dp_{i,j} \leftarrow dp_{i,j} + dp_{k,j-1} \times f(k,i)$，其中 $f(k,i)$ 表示从 $k$ 到 $i$，不经过任何其他点的方案数。

显然 $f(k,i)$ 可以用容斥原理算。具体而言，他可以看做 $g(k,i) = \dbinom{x_i+y_i-x_k-y_k}{x_i-x_k}$ 减去所有的中继节点 $j$，删去 $f(k,j) g(j,i)$。

因此 $dp_{k,j-1} \times f(k,i)$ 实际可以看做 $dp_{k,j-1} \times (g(k,i) - \sum_w f(k,w)g(w,i))$。

我们知道了 $\sum dp_{k,j-1}f(k,w)$ 实际就是 $dp_{w,j}$。因此设 $tmp_{i,j}$ 为 $\sum_k dp_{k,j-1} \times g(k,i)$，则 $dp_{i,j} = tmp_{i,j} - tmp_{i,j+1}$。

而第二维只需要开到 $\log_2 s$，因此在 $O(m^2 \log s)$ 的复杂度内解决了本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MAXM=2e6+10,MOD=1e9+7;
int n,m,k,s,f,ans,frac[MAXM],inv[MAXM],dp[MAXN][25];
struct Node {int x,y;}a[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {return frac[d]*inv[u]%MOD*inv[d-u]%MOD;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k>>s;
	ffor(i,1,k) cin>>a[i].x>>a[i].y;
	sort(a+1,a+k+1,[](Node A,Node B) {
		return A.x+A.y<B.x+B.y;
	});
	if(a[k].x!=n||a[k].y!=m) s*=2,k++,a[k]={n,m};
	frac[0]=1; int t=n+m;
	ffor(i,1,t) frac[i]=frac[i-1]*i%MOD;
	inv[t]=qpow(frac[t],MOD-2)%MOD;
	roff(i,t-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	ffor(i,1,k) {
		dp[i][1]=C(a[i].x-1,a[i].x+a[i].y-2);
		ffor(j,1,23) ffor(l,1,i-1) if(a[l].x<=a[i].x&&a[l].y<=a[i].y) 
			dp[i][j+1]=(dp[i][j+1]+dp[l][j]*C(a[i].x-a[l].x,a[i].x+a[i].y-a[l].x-a[l].y))%MOD;
		ffor(j,1,23) dp[i][j]=(dp[i][j]-dp[i][j+1])%MOD;
	}
	ffor(i,1,24) {
		int x=s;
		ffor(j,1,i) x=x-x/2;
		x--;
		ans=(ans+x*dp[k][i])%MOD;	
	}
	ans=ans*qpow(C(n-1,n+m-2),MOD-2)%MOD;
	cout<<((ans+1)%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Nelofus (赞：0)

显然至多经过 $\log s$ 次除法，权值将变为 $1$。

设 $f_{i,j}$ 表示当前为第 $i$ 个关键点，当前经过了**恰好** $j$ 次除法的方案数。

但显然这样是没法转移的，因为中间可能会经过其他的关键点。所以考虑容斥，设 $g_{i,j}$ 表示当前为第 $i$ 个关键点，**至少**经过了 $j$ 个关键点的方案数。这样转移就容易了，而且有 $f_{i,j}=g_{i,j}-g_{i,j+1}$。

如果直接用 $g$ 转移自己会算重，要在算出 $g$ 后算出 $f$ 了，再用 $f$ 转移 $g$。时间复杂度 $\mathcal O(k^2\log s)$。

[Code](https://codeforces.com/contest/722/submission/277294040)

---

## 作者：Hanx16Kira (赞：0)

# Research Rover

[CF722E (Luogu)](https://www.luogu.com.cn/problem/CF722E)


## Solution

模拟赛的 T4，赛时就写了个 DFS 的暴力就了事了，听学长评讲结果学长又把自己讲迷糊了，所以就来看是不是 CF 的原题。学习了一下题解，并按照自己的写法把代码给写了出来，希望能有帮助。

首先先来想一想最基础的东西：在 $n\times m$ 的方格图中，从左上到右下有多少种合法路径，很显然可以想到用递推的方式求解。以 $3\times 4$ 的方格图为例，可以得出以下的结果：

$$
\begin{matrix}
1&1&1&1\\
1&2&3&4\\
1&3&6&10
\end{matrix}
$$

如果将这张表格顺时针旋转 $45^\circ$ 的话，不难发现，这张表格变成了杨辉三角的一部分，也就是说，$n\times m$ 方格图的路径数是可以用杨辉三角来计算的，路径数为 $\displaystyle \begin{pmatrix}n+m-2\\n-1\end{pmatrix}$。我们可以将这个公式推广成为方格图中两个点之间的路径数，即方格图中两个点（坐标分别为 $(x_1,y_1) ,(x_2,y_2)$ 的两个点，假设可以从前者到达后者）之间的路径数为 $\displaystyle \begin{pmatrix}x_2-x_1+y_2-y_1\\x_2-x_2\end{pmatrix}$，如果将第一个点表示为 $p_1$，第二个点表示为 $p_2$，那么为了方便方程的书写，我把这个结果记作 $way(p_1,p_2)$。

注意题目的数据范围，因为 $n,m$ 的范围均在 $1\times 10^5$ 这一级别，所以肯定不能使用 $\mathcal O(nm)$ 这类的算法来解决，同时注意到 $k$ 的范围仅有 $2\times 10^{3}$，所以考虑将障碍点作为状态转移的位置。为了满足无后效性原则，先将所有特殊点按照先 $x$ 后 $y$ 的顺序从小到大进行排序。同时可以发现 $S$ 的范围是 $1\times 10^6$，并且每经过一个障碍点会变成 $\displaystyle \lceil \frac{S}{2} \rceil$，这也就意味着只要我们知道当前路径经过了多少特殊点，就可以知道目前的 $S$ 值为多少，同时 $S$ 的取值最多只有 $\lceil \log S \rceil$ 个，因此可以尝试考虑一种时间复杂度为 $\mathcal O(k^2 \log S)$ 的做法。

先考虑计算从起点出发不经过其他特殊点到达第 $i$ 个特殊点的方案数，记作 $f_i$，会发现直接计算的话状态并不好转移，所以考虑用容斥的方法来计算。记起点为 $st$，那么可以得出 $f_i$ 的转移方程：

$$
f_i=way(st,i)-\sum \limits_{j=1}^{i-1} f_j\times way(j,i)
$$

解释下方程的含义：先计算出不做任何限制到达第 $i$ 个特殊点的方案数，然后容斥掉经过其他特殊点的方案数，这些特殊点的方案数总和就是 $\displaystyle \sum \limits_{j=1}^{i-1} f_j\times way(j,i)$。

那么根据这种做法，可以推广到从起点出发恰好经过 $j$ 个特殊点到达第 $i$ 个特殊点的方案数，记作 $f_{i,j}$，那么用上面方程同样的推导方式，可以推出 $f_{i,j}$ 的转移方程：

$$
f_{i,j}=way(st,i) - \sum \limits _{t=1}^{i-1} f_{t,j-1} \times way(t,i) -\sum \limits_{t=1}^{j-1} f_{i,t}
$$

同样来解释方程的含义：与上面的方程类似，先计算出不做任何限制到达第 $i$ 个特殊点的方案数，减去上一个点经过了其他特殊点的方案数 $\displaystyle \sum \limits _{t=1}^{i-1} f_{t,j-1} \times way(t,i)$，而最后一部分是因为要保证恰好，所以要将前面经过 $[1,j-1]$ 个特殊点的情况减去，并且可以注意到这一部分的值是一个前缀和，所以维护这个前缀和可以省下这部分的枚举时间。

此外需要注意的是，因为需要从起点出发并到达终点，所以在起点和终点不是特殊点的时候将这俩加入特殊点，并且在统计答案的时候还有另外需要注意的（待会代码注释里会讲）。因为 $S$ 的取值只有 $\lceil \log S \rceil$ 种情况，所以上面方程中 $j$ 的枚举只需要枚举 $\lceil \log S \rceil$ 个即可，所以上面方程的时间复杂度就是 $\mathcal O(k^2\log S)$。

计算组合数和答案的时候要用到除法，所以需要计算逆元，用费马小定理计算即可。需要知道的是，组合数计算的时候用到的逆元都是某个数阶乘的逆元，所以这部分的逆元可以预处理来减多一个 $\log$ 的时间。

还有一些小细节会在代码中提到。

### Code

```c++
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof a)
#define int long long
using namespace std;
template<typename T> void read(T &k)
{
    k=0;T flag=1;char b=getchar();
    while (!isdigit(b)) {flag=(b=='-')?-1:1;b=getchar();}
    while (isdigit(b)) {k=k*10+b-48;b=getchar();}
    k*=flag;
}
void write(int x) {if (x<0) putchar('-'),write(-x);if (x>9) write(x/10);putchar(x%10+'0');}
void writewith(int x,char c) {write(x);putchar(c);}//快读快输模板
const int barrierSize=2000,mod=1e9+7,mapSize=1e5;
int n,m,k,S;
struct POINT{//存点，按照x，y的顺序排序
    int x,y;
    bool operator<(const POINT &a) const {return (x!=a.x)?x<a.x:y<a.y;}
}bar[barrierSize+5];
int Fpow(int x,int y)//快速幂，用于求逆元
{
    int res=1,base=x%mod;
    while (y) 
    {
        if (y&1) res=res*base%mod;
        base=base*base%mod,y>>=1;
    }
    return res;
}
int Inv[(mapSize<<1)+5];
int inv(int x) {return Inv[x];}
int fac[(mapSize<<1)+5];
void preWork()//预处理阶乘和逆元
{
    fac[0]=1;
    for (int i=1;i<=(mapSize<<1);i++) fac[i]=fac[i-1]*i%mod;//阶乘
    Inv[mapSize-1]=Fpow(fac[mapSize-1],mod-2);
    for (int i=mapSize-1;i;i--) Inv[i-1]=Inv[i]*i%mod;//用递推的方法求阶乘的逆元，即Inv[i]表示i!的逆元
}
int C(int x,int y) {return fac[x]*inv(y)%mod *inv(x-y)%mod;}//计算组合数，直接调用提前计算好的阶乘和逆元即可
int way(POINT b,POINT a) {return C(a.x-b.x+a.y-b.y,a.x-b.x);}//计算从b到a的路径数
int f[barrierSize+5][barrierSize+5];//存答案，第二维可以只开到25
bool flag1=0,flag2=0;//flag1表示起点是否是特殊点，flag2表示终点是否是特殊点
signed main()
{
    preWork();
    read(n),read(m),read(k),read(S);
    for (int i=1;i<=k;i++)
        read(bar[i].x),read(bar[i].y),
        flag1=(bar[i].x==1 && bar[i].y==1)?1:flag1,flag2=(bar[i].x==n && bar[i].y==m)?1:flag2;//维护flag1，flag2
    if (!flag1) bar[++k]=(POINT){1,1};flag1^=1;//如果起点非特殊点，则加入特殊点内，flag1取反的含义在统计答案的时候会提
    if (!flag2) bar[++k]=(POINT){n,m};flag2^=1;//将终点加入特殊点
    sort(bar+1,bar+k+1);
    int maxBar=ceil(log2(S))+1;//最大可能的j，直接取21也可以
    int sum=0;
    for (int i=1;i<=k;i++)
    {
        sum=0;//用于优化掉转移方程中的最后一部分
        for (int j=1;j<=maxBar;j++)
        {
            f[i][j]=C(bar[i].x+bar[i].y-2,bar[i].x-1);//不加限制的总路径
            for (int t=1;t<=i-1;t++)
                if (bar[t].x<=bar[i].x && bar[t].y<=bar[i].y) f[i][j]=((f[i][j]-f[t][j]*way(bar[t],bar[i]))%mod+mod)%mod;//如果可以从t到i，那么就将这部分重复的减去
            f[i][j]=((f[i][j]-sum)%mod+mod)%mod;//减去最后一部分，注意处理负数的情况
            sum=(sum+f[i][j])%mod;//更新前缀和
        }
    }
    int all=C(n+m-2,n-1),answer=0;//因为超过了log2(S)的部分的体力值都为1，所以这部分对答案的贡献就是这部分的方案数
    for (int i=flag1+flag2;i<=maxBar;i++)//因为f[i][j]表示的是经过了j个特殊点的方案数，而我们将起点和终点给作为了特殊点处理，所以需要减去起点和终点多算的特殊点数量，这部分数量就是flag1+flag2
    {
        answer=(f[k][i]*S+answer)%mod;//计算总体力值，即方案数*对应体力值
        S-=(S/2);//ceil(S/2)
        all=((all-f[k][i])%mod+mod)%mod;//all用于统计体力值为1的部分对答案的贡献，所以需要将前面这部分的方案数减去
    }
    answer=(answer+all)%mod;//加上体力值为1的情况
    writewith(answer*Fpow(C(n+m-2,n-1),mod-2)%mod,'\n');//需要注意的是总方案数的逆元是不能调用Inv数组的，因为Inv数组是阶乘的逆元，所以这里用快速幂重新算逆元来记录答案
    return 0;
}

```

一道很有意思的题目，值得多想一想。

---

## 作者：demon_yao (赞：0)

## 题目大意
从(1,1)走到(n,m)的道路中有k个特殊点，经过一个特殊点会使分数变为原来一半(向上取整)，问从(1,1)到(n,m)的期望得分。

## 思路
为了方便，我们可以把(1,1)和(n,m)看成特殊点，之后为了方便枚举走过的点，可以对输入的点按横纵坐标排序（这样可以省去枚举很多不可能经过的点）。

之后就可以进行DP啦qwq。我们设$f[i][j]$表示到i点至少经过j个特殊点的总方案数

这里有一个常识，从(x1,y1)走到(x2,y2)的总方案数为
$C_{|x1-x2|+|y1-y2|}^{|x1-x2|}$(应该不用我说叭)

之后我们就可以推出状态转移方程了：
$f[i][j]=\sum{f[k][j-1]-f[k][j]}$

 $(\sum{f[k][j-1]-f[k][j]})$表示经过j-1个特殊点到达i的方案数。
 
 在这之后我们就可以得出答案了qwq：
 $ans=({C^n_{n+m}})^{-1} * \sum({f[k][i]-f[k][i+1]})*(s/2^i)$
 
代码中有一丢丢注释，帮助理解，(还是萌新，有不足之处望各位大佬多多指出qwq）

```cpp




#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod= 1e9+7;
const int  N= 1e5+5;
int n,m,k,s,ans;
int f[N][33],jc[N*2],inv[N*2];

int mi(int x,int y)//快速幂 
{
	int res=1ll;
	while(y){
		if(y%2==1) res=res*x%mod;
		x=x*x%mod;
		y>>=1ll;
	}
	return res%mod;
}


struct node{
	int x,y;
	inline bool friend operator < (const node &b,const node &c){
		if(b.x==c.x) return b.y<c.y;
		return b.x<c.x;
	}
}a[N];

int C(int x,int y){return jc[x]%mod*inv[x-y]%mod*inv[y]%mod;}
//计算排列组合

int calc(node b,node c) {return C(c.x-b.x+c.y-b.y,c.x-b.x);}
//求从(b1,b2)到(c1,c2)的方案数

signed main()
{
	cin>>n>>m>>k>>s;
	inv[0]=jc[0]=1;
	for(int i=1;i<=n+m;i++) jc[i]=jc[i-1]*i%mod;//一大堆的预处理
	for(int i=1;i<=n+m;i++) inv[i]=mi(jc[i],mod-2)%mod;
	for(int i=1;i<=k;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
	}
	sort(a+1,a+k+1);
	if(a[1].x!=1||a[1].y!=1) {a[++k]=(node){1,1};s*=2;}
	if(a[k].x!=n||a[k].y!=m) a[++k]=(node){n,m};//处理开头与结尾	
	else s=(s+1)/2;
	int gs=log2(s)+1;
	sort(a+1,a+k+1);//按坐标排序
	f[1][0]=1;
	for(int i=2;i<=k;i++){
		f[i][1]=calc(a[1],a[i]);
		for(int j=2;j<=gs;j++)//j是最多经过的点数
			for(int t=1;t<i;t++){//t是中转点
				if(a[t].x<=a[i].x&&a[t].y<=a[i].y)
				{
					f[i][j]+=(f[t][j-1]*calc(a[t],a[i]))%mod;
					f[i][j]=(f[i][j]+mod)%mod;
					f[i][j]-=(f[t][j]*calc(a[t],a[i]))%mod;
					f[i][j]=(f[i][j]+mod)%mod;				
			}
	}
}
	ans=0;
	for(int i=1;i<=gs;i++){
		s-=s/2;ans=(ans+(f[k][i]-f[k][i+1])*s%mod+mod)%mod;}
	ans=(ans*mi(calc(a[1],a[k]),mod-2)+mod)%mod;
	cout<<ans;
	return 0;
}
```


---

