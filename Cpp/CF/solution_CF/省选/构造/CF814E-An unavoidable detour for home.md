# An unavoidable detour for home

## 题目描述

Those unwilling to return home from a long journey, will be affected by the oddity of the snail and lose their way. Mayoi, the oddity's carrier, wouldn't like this to happen, but there's nothing to do with this before a cure is figured out. For now, she would only like to know the enormous number of possibilities to be faced with if someone gets lost.

There are $ n $ towns in the region, numbered from $ 1 $ to $ n $ . The town numbered $ 1 $ is called the capital. The traffic network is formed by bidirectional roads connecting pairs of towns. No two roads connect the same pair of towns, and no road connects a town with itself. The time needed to travel through each of the roads is the same. Lost travelers will not be able to find out how the towns are connected, but the residents can help them by providing the following facts:

- Starting from each town other than the capital, the shortest path (i.e. the path passing through the minimum number of roads) to the capital exists, and is unique;
- Let $ l_{i} $ be the number of roads on the shortest path from town $ i $ to the capital, then $ l_{i}>=l_{i-1} $ holds for all $ 2<=i<=n $ ;
- For town $ i $ , the number of roads connected to it is denoted by $ d_{i} $ , which equals either $ 2 $ or $ 3 $ .

You are to count the number of different ways in which the towns are connected, and give the answer modulo $ 10^{9}+7 $ . Two ways of connecting towns are considered different if a pair $ (u,v) $ ( $ 1<=u,v<=n $ ) exists such there is a road between towns $ u $ and $ v $ in one of them but not in the other.

## 说明/提示

In the first example, the following structure is the only one to satisfy the constraints, the distances from towns $ 2,3,4 $ to the capital are all $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/41aec6960c240a1fb09480a0a613ecf71bad9b6b.png)In the second example, the following two structures satisfy the constraints.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/5dfe5b5d19d9938739604a89ad14ef6620891ff1.png)

## 样例 #1

### 输入

```
4
3 2 3 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 3 3 2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
2 2 2 2 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
20
2 2 2 2 3 2 3 2 2 2 2 2 2 2 2 2 2 3 3 2
```

### 输出

```
82944
```

# 题解

## 作者：Karry5307 (赞：11)

### 题意

给定长度为 $n$ 的序列 $d$，求出 $n$ 个点的无向无权图数量，满足

- 每个点到 $1$ 的最短路存在且唯一。

- 设 $l_i$ 为 $i$ 到 $1$ 的最短路，要保证对于所有 $2\leq i\leq n$ 有 $l_i\geq l_{i-1}$ 成立。

- $i$ 号点的度数为 $d_i$。


$\texttt{Data Range:}1\leq n\leq 300,2\leq d_i\leq 3$

### 题解

[更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13050641.html)

神仙题。

$\texttt{CF}$ 上的数据比较水，$n$ 只有 $50$，以题意上的数据范围为准。

首先证明一个结论：符合要求的图的边集肯定能被划分成原图的 $\texttt{bfs}$ 树加上一些同深度的点连的边。

首先抠出原图的一棵 $\texttt{bfs}$ 树，考虑某条非树边 $(u,v)$ 与 $1$ 到 $u$ 和 $1$ 到 $v$ 的距离构成的环的长度 $l$ 的奇偶性，那么有

- 如果这个环是偶环，那么存在一个点 $w$ 使得它走树边到 $1$ 的距离为 $\frac{l}{2}$。注意到这个图是无权图，所以最短路树就是 $\texttt{bfs}$ 树，即 $\operatorname{dist}(w,1)=\frac{l}{2}$。

  注意到这个环的长度是 $l$，那么 $w$ 经过非树边走到 $1$ 的距离是 $l-\frac{l}{2}=\frac{l}{2}=\operatorname{dist}(w,1)$，所以最短路不唯一，矛盾。

- 如果这个环是个奇环，那么不妨设 $u$ 是深度较小的那个点。

  如果 $dep_u\neq dep_v$ 的话，那么 $dep_v\geq dep_u+2$，此时有两条路径到达 $v$。其中先走树边到达 $u$ 再到达 $v$ 的距离为 $dep_u+1$，而直接走树边走到 $v$ 的距离为 $dep_v$。很显然，前者更短，但是根据最短路树，后者是 $1$ 到 $v$ 的“最短路”，矛盾。

所以如果 $u$ 和 $v$ 不是同一深度的点那么怎么样都能推出矛盾。

接着考虑 $\texttt{dp}$。设 $f_{i,j}$ 表示已经考虑了前 $i$ 个点，最后 $j$ 个点与第 $i$ 个点在同一层的方案数。

同时设 $g_{i,j,k}$ 表示这一层有 $i$ 个点，上一层度数为 $2$ 的点有 $j$ 个，度数为 $3$ 的点有 $k$ 个，这一层与上一层的树边和上一层的非树边的方案数。

根据定义我们可以得到答案为 $\sum\limits_{i=1}^{n-1}f_{n,i}g_{0,c_0,c_1}$，其中 $c_0$ 和 $c_1$ 分别为最后 $i$ 个点中度数为 $2$ 和 $3$ 的点的数量。

考虑如何转移 $f$，枚举上一层有多少个点，我们可以得到这样的式子：

$$f_{i,j}=\sum\limits_{k=1}^{i-j-1}f_{i-j}{k}g_{j,c_0,c_1}$$

其中 $c_0$ 和 $c_i$ 分别为从 $i$ 开始倒着数 $k$ 个点中度数为 $2$ 和 $3$ 的点的数量。

注意到这个式子是 $O(n^3)$ 的，如果 $g$ 也可以 $O(n^3)$ 转移的话那就万事大吉了。

考虑分情况讨论一下，首先有初始状态 $g_{0,0,0}=1$。

- 如果 $i=j=0,k\neq 0$ 的话，那么所有的上层节点都是 $3$ 度的。除去往父亲连的边之外，每一个点都有两条边连向同一层的点，所以构成了一些环。枚举一下环的大小（不能等于 $2$）就可以写出以下式子（这里平移了下标）：

$$g_{0,0,k}=\sum\limits_{l=2}^{k-1}g_{0,0,k-l-1}\binom{j-1}{k}\frac{k!}{2}$$

- 如果 $i=0,j\neq 0$ 的话，考虑在上一层找个 $2$ 度点，那么通过把他拿掉并且讨论同一层连的那个点的度数的方法得到这个式子：

$$g_{0,j,k}=(j-1)g_{0,j-2,k}+kg_{0,j,k-1}$$

- 如果 $i\neq 0$ 的话，类似上面的思路，在这一层找一个点，我们得到：

$$g_{i,j,k}=jg_{i-1,j-1,k}+kg_{i-1,j+1,k-1}$$

  这里后面那个 $g$ 的 $j$ 要 $+1$ 的原因是减少了一个 $3$ 度的点，但是产生了一个 $2$ 度的点。

发现这个东西是 $O(n^3)$ 的，于是总复杂度也是 $O(n^3)$，可以通过。

下面的代码可以在 LOJ 上通过，但是在 CF 上会被卡空间，解决方法是将 `MAXN` 改成 $51$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=551,MOD=1e9+7,INV2=5e8+4;
ll n,res;
ll fact[MAXN],finv[MAXN],d[MAXN],f[MAXN][MAXN],g[MAXN][MAXN][MAXN];
ll c[2];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void setup(ll cnt)
{
    fact[0]=fact[1]=finv[0]=1;
    for(register int i=2;i<=cnt;i++)
    {
        fact[i]=(li)fact[i-1]*i%MOD;
    }
    finv[cnt]=qpow(fact[cnt],MOD-2);
    for(register int i=cnt-1;i;i--)
    {
        finv[i]=(li)finv[i+1]*(i+1)%MOD;
    }
}
inline ll binom(ll m,ll n)
{
    return (li)fact[m]*finv[n]%MOD*finv[m-n]%MOD;
}
inline void calc()
{
    ll x;
    g[0][0][0]=1;
    for(register int i=0;i<=n;i++)
    {
        for(register int j=0;j<=n-i;j++)
        {
            if(i==0&&j==0)
            {
                continue;
            }
            if(!i)
            {
                for(register int k=2;k<j;k++)
                {
                    x=(li)g[0][i][j-k-1]*binom(j-1,k)%MOD*fact[k]%MOD*INV2%MOD;
                    g[0][i][j]=(g[0][i][j]+x)%MOD;
                }
            }
            else
            {
                if(i>=2)
                {
                    g[0][i][j]=(g[0][i][j]+(li)(i-1)*g[0][i-2][j]%MOD)%MOD;
                }
                if(j>=1)
                {
                    g[0][i][j]=(g[0][i][j]+(li)j*g[0][i][j-1]%MOD)%MOD;
                }
            }
        }
    }
    for(register int i=1;i<n;i++)
    {
        for(register int p=1,j;p<n-i;p++)
        {
            for(register int k=0;k<=p;k++)
            {
                j=p-k;
                if(j)
                {
                    g[i][j][k]=(g[i][j][k]+(li)j*g[i-1][j-1][k]%MOD)%MOD;
                }
                if(k)
                {
                    g[i][j][k]=(g[i][j][k]+(li)k*g[i-1][j+1][k-1]%MOD)%MOD;
                }
            }
        }
    }
}
int main()
{
    setup(n=read()),calc();
    for(register int i=1;i<=n;i++)
    {
        d[i]=read();
    }
    f[d[1]+1][d[1]]=1;
    for(register int i=d[1]+2;i<=n;i++)
    {
        for(register int j=1;j<=i-d[1]-1;j++)
        {
            c[0]=c[1]=0;
            for(register int k=1;k<i-j;k++)
            {
                c[d[i-j-k+1]==3]++;
                f[i][j]=(f[i][j]+(li)g[j][c[0]][c[1]]*f[i-j][k]%MOD)%MOD;
            }
        }
    }
    c[0]=c[1]=0;
    for(register int i=1;i<n;i++)
    {
        c[d[n-i+1]==3]++;
        res=(res+(li)f[n][i]*g[0][c[0]][c[1]]%MOD)%MOD;
    }
    printf("%d\n",res);
}
```

---

## 作者：CXY07 (赞：8)

> 题目链接：[CF814E An unavoidable detour for home](https://www.luogu.com.cn/problem/CF814E)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/121/)**

题意：

> 给出 $n$ 个点，和每个点的度数 $d_i$，要求计数无向图满足：

> - $1$ 到 $i$ 的最短路有且仅有一条。
> - 设 $l_i$ 是 $1$ 到 $i$ 的最短路，则 $\forall i\in[1,n),l_i\le l_{i+1}$。

> $3\le n\le 50,2\le d_i\le 3$。


首先由于 $l_i\le l_{i+1}$，容易意识到，对于 $l$ 相同的节点，他们的编号一定构成一个区间。容易发现，第 $2$ 层的节点编号一定是 $[2,d_1+1]$。


当我们划分了区间之后，第 $i$ 层可以向第 $i+1$ 层连边，第 $i$ 层内部可以连边，其他的边都是不合法的了。

现在考虑第 $i$ 层的连边情况，设从第 $i-1$ 层连下来了 $m$ 条边，这说明第 $i$ 层恰好有 $m$ 个节点。设其中 $2$ 度点有 $x$ 个，$3$ 度点有 $y$ 个，他们分别和上层连一条边，所以实际上是 $1$ 度点 $x$ 个，$2$ 度点 $y$ 个。

设该层内部有 $z$ 条边，那么给下层引出的边有 $x+2y-2z$ 条，他们可以任意排列，共 $(x+2y-2z)!$ 种方案。

再考虑层内部的 $z$ 条边，把 $2$ 度点看做两个点，则选出 $z$ 个不相交无序二元组的方案数是：

$$
\dfrac{(x+2y)!}{(x+2y-2z)!\times 2^z\times z!}
$$

即首先选出 $2z$ 个数，相邻两两一对。除去每一对内部的顺序，除去 $z$ 个对之间的顺序。

但由于将 $2$ 度点看做了两个点，所以可能出现重边、自环的情况。考虑容斥，钦定出现了 $p$ 条重边，$q$ 个自环，那么从 $y$ 个 $2$ 度点中选出他们的方案数是：

$$
\dfrac{y!\times 2^p}{(y-2p-q)!\times p!\times q!\times 2^p}
$$

即：

$$
\dfrac{y!}{(y-2p-q)!\times p!\times q!}
$$

上面要乘一个 $2^p$ 是因为一组重边有两种连接方式，比如 $(1,2),(1',2')$ 和 $(1,2'),(1',2)$。由于在容斥，所以前面还有一个 $(-1)^{p+q}$ 的容斥系数。

设 $s=2p+q$，则已经选出了 $s$ 条边，$2s$ 个点。那么剩下的 $x+2y-2s$ 个点中，还需要选出 $z-s$ 条边，方案就是：

$$
\dfrac{(x+2y-2s)!}{(x+2y-2z)!\times 2^{z-s}\times (z-s)!}
$$

因此在 $x$ 个 $1$ 度点，$y$ 个 $2$ 度点中，内部连 $z$ 条边，同时往下一层引出 $x+2y-2z$ 条边的贡献就是：

$$
\sum_{s=2p+q,s\le\min(y,z)} \frac{(-1)^{p+q}y!}{(y-s)! p! q!}\times \dfrac{(x+2y-2s)!}{(x+2y-2z)!2^{z-s} (z-s)!}\times (x+2y-2z)!\times \frac{1}{2^y}
$$

最后一个要乘 $\dfrac{1}{2^y}$ 是因为 $y$ 个 $2$ 度点被认为是两个点，需要取消顺序。

设：

$$
v_s=\sum_{2p+q=s} \dfrac{(-1)^{p+q}}{p!\times q!}
$$

那么上式可以化简为：

$$
\sum_{0\le s\le \min(y,z)} \dfrac{y!(x+2y-2s)!v_s}{(y-s)!2^y}\times \dfrac{1}{(z-s)!2^{z-s}}
$$

于是就可以设 $\text{dp}_{i,j}$ 表示已经考虑了前 $i$ 个点，最后一层向下一层引出了 $j$ 条边，那么新的一层的节点就是 $i+1,i+2\cdots i+j$，设其中有 $x$ 个 $2$ 度点，$y$ 个 $3$ 度点。

那么可以通过枚举 $z$，再枚举 $s$，从 $\text{dp}_{i,j}$ 转移到 $\text{dp}_{i+j,x+2y-2z}$。这样就是 $\mathcal{O}(n^4)$ 的了。

考虑分部进行转移，我们发现 $z=s+(z-s)$，令 $d=z-s$，则可以先枚举 $s$，再枚举一次 $d$：

$$
\text{dp}_{i,j}\stackrel{s}{\longrightarrow} g_{i+j,x+2y-2s}\stackrel{d=z-s}{\longrightarrow} \text{dp}_{i+j,x+2y-2z}
$$

于是就可以做到时间复杂度 $\mathcal{O}(n^3)$，空间复杂度 $\mathcal{O}(n^2)$。

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define file(FILENAME) freopen(FILENAME".in", "r", stdin), freopen(FILENAME".out", "w", stdout)
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define LINE() cout << "LINE = " << __LINE__ << endl
#define debug(x) cout << #x << " = " << x << endl
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb push_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'

const int MAXN = 110;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int n, m, iv2 = (mod + 1) >> 1;
int d[MAXN], v[MAXN], dp[MAXN][MAXN], g[MAXN][MAXN];
int ip2[MAXN], fac[MAXN], ifac[MAXN];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {a = a * 10 + (c ^ 48); c = getchar();}
	return a *= f, true;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) {return read(x) && read(y...);}

int qpow(int x, int b) {
	int res = 1;
	for(; b; b >>= 1, (x *= x) %= mod) if(b & 1) (res *= x) %= mod;
	return res;
}

void init() {
	fac[0] = ifac[0] = ip2[0] = 1;
	for(int i = 1; i < MAXN; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		ip2[i] = ip2[i - 1] * iv2 % mod;
	}
	ifac[MAXN - 1] = inv(fac[MAXN - 1]);
	for(int i = MAXN - 2; i; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

signed main () {
#ifdef FILE
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
	read(n); init();
	for(int i = 1; i <= n; ++i) read(d[i]);
	for(int s = 0; s <= n; ++s)
		for(int p = 0, q; (p << 1) <= s; ++p) {
			q = s - (p << 1);
			(v[s] += ifac[p] * ifac[q] % mod * (((p + q) & 1) ? mod - 1 : 1)) %= mod;
		}
	dp[1][d[1]] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= (i << 1); ++j) {
			if(!g[i][j]) continue;
			for(int d = 0; (d << 1) <= j; ++d)
				(dp[i][j - (d << 1)] += g[i][j] * ip2[d] % mod * ifac[d]) %= mod;
		}
		for(int j = 1, x, y; j <= n - i; ++j) {
			if(!dp[i][j]) continue;
			x = 0, y = 0;
			for(int k = i + 1; k <= i + j; ++k) d[k] == 2 ? x++ : y++;
			for(int s = 0, coe; s <= y; ++s) {
				coe = fac[y] * fac[x + (y << 1) - (s << 1)] % mod * v[s] % mod * ifac[y - s] % mod * ip2[y] % mod;
				(g[i + j][x + (y << 1) - (s << 1)] += dp[i][j] * coe) %= mod;
			}
		}
	}
	printf("%lld\n", dp[n][0]);
	return 0;
}
```

---

## 作者：Styx (赞：8)

题意：给出$n$个点，和每个点的度让你构造出一张无向图满足以下两条性质：

> 1.点$1$到点$i$仅有**唯一**一条最短路  

> 2.点$1$到点$i$的最短路长度大于等于点$1$到点$i-1$的最短路长度

求能构成满足条件的无向图的个数？

首先我们可以根据上面的两点推出一些结论：

> 1.根据第一条性质显然这张图是由一棵树加上一些平边构成的（连接深度相同两点的边） 

> 2.根据第二条性质显然$i$所在的点一定在点$i-1$的同层或下一层  

由此可知，对于两层之间的方案数转移，我们只需要考虑这一层有几个点，上一层有几个度为$2$的点，有几个度为$3$的点。

假设$g[i][j][k]$表示当前层有$i$个点，上一层有$j$个度为$2$的点，$k$个度为$3$的点的方案数。  

开始考虑这个转移：  
$i=0,j=0,k=0$  
> $g[0][0][0]=1$，相当于只有不取一种方案  

$i=0,j=0,k>0$
> $g[0][0][k]=\sum_{l=2}^{l<k}(g[0][0][k-l-1]*C_{k-1}^{l}*\frac{(l)!}{2})$  
每个点度都为$2$所以一定是若干个项链，为了避免重复计算，**我们假设项链里一定包含最后一个点**，所以方案数为——将最后一个点拿出来与之前任选两个、三个……k-1个点分别构成项链的种类数之和，其中项链数表示选$i$个点构成排列，首尾成环且翻转算重复的方案数，$f(x)=\frac{(x-1)!}{2}$，这里l+1取大于二的原因是因为题目中说两个点之间不能有两条边，所以两个点组成的项链不符合题意。

$i=0,j>0,k>0$  
> $g[0][j][k]=g[0][j-2][k]*(j-1)+g[0][j][k-1]*k$  
同样是连接最后一个点使其度数为$2$  
第一种情况表示在$j-1$个可能变成$2$的点里取一个和最后的点连成两个度数为2的点  
第二种情况表示在$k$个可能变成$3$的点里取一个和最后的点连接，之前二度的点变成三度，最后一个点变成二度，所以转移时$j$不变，$k$从$k-1$转移

$i>0,j>0,k>0$
> $g[i][j][k]=g[i-1][j-1][k]*j+g[i-1][j+1][k-1]*k$  
第一种情况表示上一行选出一个可能变成$2$的点，和当前行最后一个点相连，显然上一行只有一个数变成了二度，所以从$j-1$转移   
第二种情况为上一行选出一个可能变成$3$的点，和当前行最后一个点相连，显然上一行原来有一个二度的点变成了三度，所以$j$从$j+1$转移，$k$从$k-1$转移

好的，我们思考完了$g[i][j][k]$的转移，开始引入下一个数组

定义 $f[i][j]$表示当前点是第$i$个，之前的$i-1$、$i-2$……等$j-1$个点与$i$在同一层的方案数

$f[i][j]$的转移方程还是好求的：$f[i][j]=\sum_{k=1}^{k<=i-j}f[i-j][k]*g[j][n][m]$   
其中$n$、$m$分别表示这$k$个数中有$n$个度为$2$的点，$m$个度为$3$的点，这个方程就不讲解了，可以根据之前的定义自己感受一下。

那么答案就出来了

$ans=\sum_{j=1}^{j<n}f[n][j]*g[0][n][m]$  
其中$n$、$m$分别表示这$j$个数中有$n$个度为$2$的点，$m$个度为$3$的点

代码如下：
```cpp
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mod 1000000007
using namespace std;

int n,d[60];
long long a[60],g[60][60][60],f[60][60],c[60][60];

int main()
{
	a[0]=a[1]=0;
	a[2]=a[3]=1;
	for(int i=4;i<=50;i++)
	{
		a[i]=a[i-1]*(i-1)%mod;
	}
	for(int i=0;i<=50;i++)
	{
		c[i][i]=c[i][0]=1;
	}
	for(int i=1;i<=50;i++)
	{
		for(int j=1;j<i;j++)
		{
			c[i][j]=c[i-1][j-1]+c[i-1][j];
			c[i][j]%=mod;
		}
	}
	g[0][0][0]=1;
	for(int j=0;j<=50;j++)
	{
		for(int k=0;k<=50-j;k++)
		{
			if(j==0&&k>0)
			{
				for(int l=2;l<k;l++)
				{
					g[0][j][k]+=(g[0][j][k-l-1]*c[k-1][l])%mod*a[l+1]%mod;
					g[0][j][k]%=mod;
				}
			}
			else
			{
				if(j>=2) g[0][j][k]+=(g[0][j-2][k]*(j-1))%mod,g[0][j][k]%=mod;
			if(k>=1) g[0][j][k]+=(g[0][j][k-1]*k)%mod,g[0][j][k]%=mod;
			}
			
		}
	}
	for(int i=1;i<=50;i++)
	{
		for(int j=0;j<=50-i;j++)
		{
			for(int k=0;k<=50-i-j;k++)
			{
				if(j>=1) g[i][j][k]+=(g[i-1][j-1][k]*j)%mod,g[i][j][k]%=mod;
				if(k>=1) g[i][j][k]+=(g[i-1][j+1][k-1]*k)%mod,g[i][j][k]%=mod;
			}
		}
	}
	int c1,c2;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&d[i]);
	f[d[1]+1][d[1]]=1;
	for(int i=d[1]+2;i<=n;i++)
	{
		for(int j=1;j<=i-d[1]-1;j++)
		{
			c1=c2=0;
			for(int k=1;k<=i-j;k++)
			{
				if(d[i-j-k+1]==2) c1++;
				else c2++;
				f[i][j]+=f[i-j][k]*g[j][c1][c2]%mod;
				f[i][j]%=mod;
			}
		}
	}
	c1=c2=0;
	long long ans=0;
	for(int j=1;j<n;j++)
	{
		if(d[n-j+1]==2)c1++;
		else c2++;
		ans+=f[n][j]*g[0][c1][c2]%mod;
		ans%=mod;
	}
	printf("%lld\n",ans);
}
```

感谢liu_cheng_ao在[loj](https://loj.ac/article/37)上发表的题解以及残念在[csdn](https://blog.csdn.net/qq_31759205/article/details/77715991)上发表的题解对我的启发

---

## 作者：Acetyl (赞：4)

上次模拟的时候遇到这题，数据范围 $n \le 1000$。前面几篇题解都提供了时间复杂度 $\mathcal O(n^3)$ 的做法，但是由于空间复杂度也是 $\mathcal O(n^3)$，所以还是无法通过。这里分享一个空间复杂度为 $\mathcal O(n^2 )$ 的做法，下面是正文。

## 题意

有 $n$ 个点，编号从 $1$ 到 $n$，现在需要连一些权值为 $1$ 的边，使得：

+ 没有重边和自环；
+ 第 $i$ 个点度数为 $d_i$，保证 $2≤d_i≤3$；
+ 对于所有 $2≤i≤n$，$1$ 到 $i$ 的最短路唯一；
+ 设 $l_i$ 为 $1$ 到 $i$ 的最短路，则对于所有 $2≤i<n$，有 $l_i≤l_{i+1}$ 。

求这样的图的个数。数据范围 $n≤1000$。

## 思路

### $\mathcal O(n^4 )$

考虑构建一棵最短路树，由于这题要求 $1$ 到每个点的最短路唯一，所以最短路树上的非树边只能在同一层中连接。同时，我们需要将所有 $i≠1$ 的 $d_i$ 减 $1$，表示每个点在最短路树上向下的自由基数量（即剩余的可向下连边或同层连边的度数，这里减去的 $1$ 表示它向父亲节点的连边）。这样，除了 $1$ 以外，每个点 $i$ 都满足 $1≤d_i≤2$。

这题保证没有重边和自环，这个条件看似小清新，实则大毒瘤，因为这样的话如果我们直接按层进行 dp 就比较麻烦，需要处理大量重边和自环的情况（之后会讲怎么按层进行 dp），所以考虑按节点进行 dp。

设 $f(i, j, c_1,c_2 )$ 表示考虑到第 $i$ 个点，上一层还有 $j$ 个自由基，当前这一层有 $c_1$ 个点还剩一个自由基，$c_2$ 个点还剩两个自由基，有多少种连边方案。初始状态 $f(1, d_1, 0, 0)=1$。

对于一个 $i$，首先需要把 $f(i-1, 0,c_1,c_2 )$ 转移到 $f(i-1, c_1+2c_2, 0, 0)$（即已经结束了一层，开启了下一层），顺便在这时候先把下面 $c_1+2c_2$ 个点的放置方案求出来：为 $\frac{(c_1+2c_2 )!}{2^{c_2}}$（除以 $2^{c_2}$  表示有 $c_2$ 组点的顺序无关，每一组是同一个点的两个儿子）。总的转移式子是：$f(i-1, c_1+2c_2, 0, 0)←\frac{(c_1+2c_2 )!}{2^{c_2}}f(i-1, 0, c_1,c_2 )$。

接下来，对于一个状态 $f(i, j, c_1,c_2 )$，枚举当前点有几个自由基与前面的点匹配：

+ 0 个，直接转移到 $f(i,j-1,nc_1,nc_2 )$ 即可，其中 $nc_1$ 和 $nc_2$ 为加入了当前点之后的 $c_1$  和 $c_2$ 。
+ 1 个（此时要求 $d_i≥1$），枚举匹配到什么类型的点：
	+ 匹配到剩下一个自由基的点：$f(i, j-1, nc_1-1, nc_2 )←c_1⋅f(i-1, j, c_1,c_2 )$；
	+ 匹配到剩下两个自由基的点：$f(i, j-1, nc_1+1, nc_2-1)←c_2⋅f(i-1, j, c_1,c_2 )$。
+ 2 个（此时要求 $d_i≥2$），还是枚举匹配到什么类型的点：
	+ 两个 1 自由基：$f(i, j-1, nc_1-2, nc_2 )←\binom{c_1}{2}f(i-1, j, c_1,c_2 )$；
	+ 一个 1 自由基，一个 2 自由基：$f(i, j-1, nc_1, nc_2-1)←c_1 c_2⋅f(i-1, j, c_1,c_2 )$；
	+ 两个 2 自由基：$f(i, j-1, nc_1+2, nc_2-2)←\binom{c_2}2f(i-1, j, c_1,c_2 )$。

最后 $f(n, 0, 0, 0)$ 即为答案，时间复杂度 $\mathcal O(n^4 )$，使用滚动数组之后空间复杂度 $\mathcal O(n^3 )$，实测可以过 $n≤300$。

### $\mathcal O(n^3 )$

上面的做法没法直接优化到 $\mathcal O(n^3 )$ 时间复杂度，所以要想过 $n≤1000$ 还需要换一种方法。之前说过按层转移比较麻烦，现在就考虑怎么按层转移。

首先需要预处理一些值：

+ 将 $k$ 个点两两匹配的方案数 $M_k$，此处 $k$ 必须为偶数，$M_k=1 × 3 × 5 ×… × (k-1)$（即 $\frac{k!}{(\frac k2)!\cdot 2^{k/2}}$）。
+ 对于 $k$ 个点，设由这 $k$ 个点组成若干个自环和 $i$ 组重边的方案数为 $X_{k,i}$，则 $X_{k, i}=\binom k{2i} M_2i$。
+ 由于我们需要容斥，所以需要对上面的 $X_{k,*}$ 带上容斥系数后求和，设 $Y_k=\sum_{i=0}^{\lfloor k/2\rfloor}(-1)^k (-2)^i X_{k,i}$，这里乘以 $2^i$ 是因为每一组重边有两种形态（$(a_1→b_2,a_2→b_1 )$ 和 $(a_1→b_1,a_2→b_2 )$），直接计算时，这两种形态会被各计算一遍，所以减的时候需要减两遍。

设 $g(l,r)$ 表示下一层中的点编号从 $l+1$ 开始到 $r$ 结束，当前层及上面的层的方案数。下面考虑转移。

枚举当前这一层中编号最大的点 $r$，设 $H(i)$ 表示当前这一层剩下 $i$ 个自由基没有考虑的方案数。首先选出这一层中用于制造自环和重边的点（由于无论是自环还是重边对于每个点都需要两个自由基，所以只需要从剩下两个自由基的点当中选即可），枚举 $l$ 和当前这一层自环与重边的点数 $k$，设当前有 $c_1$ 个点还剩一个自由基，有 $c_2$ 个点还剩两个自由基，则将 $H(c_1+2(c_2-k))$  加上 $g(l-1,r)⋅Y_k⋅2^{c_2}$ 即可。

之后，由于我们还需要在剩下的自由基中选一些两两匹配，设剩下 $i$ 个自由基，则枚举匹配的自由基个数 $j$，将 $H(i-j)$ 加上 $H(i)\binom ij M_j$ 即可。

最后，枚举最终剩下的自由基个数 $i$，将 $H(i)⋅i!$ 加到 $g(r, i+r)$ 即可。最终 $g(n,n)$ 即为答案。

时间复杂度 $\mathcal O(n^3 )$，空间复杂度 $\mathcal O(n^2 )$，实测可以通过 $n≤1000$ 的点。

## 代码

### $\mathcal O(n^4 )$

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, a) for (int i = 0; i < (a); ++i)
#define cont(i, a) for (int i = 1; i <= (a); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c) for (int i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define parse(it, x) for (auto &it : (x))
#define pub push_back
#define pob pop_back
#define emb emplace_back
#define mak make_pair
#define mkt make_tuple
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
 
const int jt = 1000000007;
void inline add(int &a, int b) { a += b - jt; a += (a >> 31) & jt; }
void inline sub(int &a, int b) { a -= b; a += (a >> 31) & jt; }
void inline mul(int &a, int b) { a = (ll)a * b % jt; }
int inline Add(int a, int b) { return a + b >= jt ? a + b - jt : a + b; }
int inline Sub(int a, int b) { return a - b < 0 ? a - b + jt : a - b; }
int inline Mul(int a, int b) { return (ll)a * b % jt; }
 
int inline ksmii(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) mul(res, a);
        mul(a, a); b >>= 1;
    }
    return res;
}
 
int dp[2][305][305][305];
int n;
int d[305];
int jc[305], mii[305];
int C2[305];
 
int main() {
    #ifndef HCl10
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    #endif
    scanf("%d", &n);
    cont(i, n) {
        scanf("%d", d + i);
        if (i > 1) --d[i];
    }
    cont(i, n) C2[i] = i * (i - 1) / 2;
    jc[0] = 1;
    cont(i, n) jc[i] = Mul(jc[i - 1], i);
    mii[0] = 1; mii[1] = (jt + 1) / 2;
    circ(i, 2, n) mii[i] = Mul(mii[i - 1], mii[1]);
    dp[0][d[1]][0][0] = 1;
    int now = 1, lst = 0;
    circ(i, 2, n) {
        loop(k, n + 1) loop(l, n + 1) if (k + l * 2 <= n) {
            add(dp[lst][k + l * 2][0][0], Mul(dp[lst][0][k][l], Mul(jc[k + l * 2], mii[l])));
        }
        loop(j, n - i + 2) loop(k, n - j + 4) loop(l, ((n - k) >> 1) + 2) dp[now][j][k][l] = 0;
        cont(j, n - i + 1) loop(k, n - j + 2) loop(l, ((n - k) >> 1) + 1) if (dp[lst][j][k][l]) {
            // select none
            if (d[i] == 1) {
                if (k >= 1) add(dp[now][j - 1][k - 1][l], Mul(k, dp[lst][j][k][l]));
                if (l >= 1) add(dp[now][j - 1][k + 1][l - 1], Mul(l, dp[lst][j][k][l]));
            }
            else if (d[i] == 2) {
                if (k >= 2) add(dp[now][j - 1][k - 2][l], Mul(C2[k], dp[lst][j][k][l]));
                if (k >= 1 && l >= 1) add(dp[now][j - 1][k][l - 1], Mul(Mul(k, l), dp[lst][j][k][l]));
                if (l >= 2) add(dp[now][j - 1][k + 2][l - 2], Mul(C2[l], dp[lst][j][k][l]));
            }
            // select one
            if (d[i] == 1) {
                add(dp[now][j - 1][k + 1][l], dp[lst][j][k][l]);
            }
            else if (d[i] == 2) {
                if (k >= 1) add(dp[now][j - 1][k][l], Mul(k, dp[lst][j][k][l]));
                if (l >= 1) add(dp[now][j - 1][k + 2][l - 1], Mul(l, dp[lst][j][k][l]));
            }
            // select two
            if (d[i] == 2) {
                add(dp[now][j - 1][k][l + 1], dp[lst][j][k][l]);
            }
        }
        swap(now, lst);
    }
    printf("%d\n", dp[lst][0][0][0]);
    return 0;
}
```

### $\mathcal O(n^3 )$

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, a) for (int i = 0; i < (a); ++i)
#define cont(i, a) for (int i = 1; i <= (a); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c) for (int i = (a); (c) > 0 ? i <= (b) : i >= (b); i += (c))
#define parse(it, x) for (auto &it : (x))
#define pub push_back
#define pob pop_back
#define emb emplace_back
#define mak make_pair
#define mkt make_tuple
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
 
const int jt = 1000000007;
void inline add(int &a, int b) { a += b - jt; a += (a >> 31) & jt; }
void inline sub(int &a, int b) { a -= b; a += (a >> 31) & jt; }
void inline mul(int &a, int b) { a = (ll)a * b % jt; }
int inline Add(int a, int b) { return a + b >= jt ? a + b - jt : a + b; }
int inline Sub(int a, int b) { return a - b < 0 ? a - b + jt : a - b; }
int inline Mul(int a, int b) { return (ll)a * b % jt; }
 
int n, m;
int d[1005];
int dp[1005][1005];
int C[2005][2005], pd[2005], ff[2005];
int tmp[2005];
 
int main() {
    #ifndef HCl10
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    #endif
    scanf("%d", &n); m = n << 1;
    cont(i, n) scanf("%d", d + i);
    loop(i, m + 1) C[i][0] = 1;
    cont(i, m) cont(j, i) C[i][j] = Add(C[i - 1][j], C[i - 1][j - 1]);
    pd[0] = 1;
    range(i, 2, m, 2) pd[i] = Mul(i - 1, pd[i - 2]);
    loop(i, m + 1) {
        int co = (i & 1) ? jt - 1 : 1;
        loop(j, (i >> 1) + 1) {
            // j is #multi-edge-pairs, i - 2j is #self-loops
            add(ff[i], Mul(co, Mul(C[i][j << 1], pd[j << 1])));
            mul(co, jt - 2);
        }
    }
    dp[1][d[1] + 1] = 1;
    circ(r, d[1] + 1, n) {
        memset(tmp, 0, sizeof(tmp));
        int r1 = 0, r2 = 0, co = 1;
        range(i, r, 1, -1) {
            ++(d[i] == 3 ? r2 : r1);
            if (d[i] == 3) mul(co, (jt + 1) >> 1);
            loop(j, r2 + 1) add(tmp[r1 + (j << 1)], Mul(Mul(dp[i - 1][r], co), Mul(C[r2][j], ff[r2 - j])));
        }
        cont(i, r1 + (r2 << 1)) range(j, min(i - 2, n - r - ((n + r + i) & 1)), 0, -2) {
            add(tmp[j], Mul(tmp[i], Mul(C[i][j], pd[i - j])));
        }
        co = 1;
        loop(i, n - r + 1) {
            if (i) mul(co, i);
            add(dp[r][i + r], Mul(tmp[i], co));
        }
    }
    printf("%d\n", dp[n][n]);
    return 0;
}
```

*本题解写于 OneNote，手动转换为 Markdown，如有格式问题请立即指出，谢谢。*


---

## 作者：Lunch (赞：3)

## [题意](https://www.luogu.org/problemnew/show/CF814E)
- 给出$n$个点，和每个点的度数（只有可能是$2$或$3$），让你构造出一张无向图满足以下两条性质：
 -  点$1$到点$i$仅有唯一一条最短路。
 - 点$1$到点$i$的最短路长度大于等于点$1$到点$i - 1$的最短路长度
。
- 求能构成满足条件的无向图的个数？（$n \le 50$）

首先挖掘性质：

- 1.构建出这个图的一棵BFS树，同一层的节点编号都相邻。
- 2.BFS树上多出来的边一定连接了深度相同的点。

那么我们就可以根据这个性质DP了，设$g(i,j,k)$为当前层有$i$个点已经和上一层的点连了边，上一层有$j$个度数为$2$，$k$个度数为$3$的点已经连好了边的方案数，那么可以分类讨论来转移。

$$g(i,j,k)=\left\{\begin{array}{cc} 1, & (i=j=k=0)\\\sum\limits_{l= 3}^kg(i,j,k-l)\times\binom {k-1}{l-1}\times A(l), & (i=j=0,k>0)\\g(i,j-2,k)\times(j-1)+g(i,j,k-1)\times k,& (i=0,j,k>0)\\g(i-1,j-1,k)\times j+g(i-1,j+1,k-1)\times k,& (i >0)\end{array}\right.$$

前三个转移是考虑上一层为最后一层的情况。

第一个转移对应的情况就是什么都不选。

第二个转移就是一层中如果只有度数为$3$的点的话，那么形成的都是项链（连向BFS树父亲的边让他们度数只剩下$2$了），那么设$A(x)$为长度为$x$的项链方案数，那么就是$\frac {n!}{n\times2}$，第一个除去的是旋转同构，第二个除去的是翻转同构的，转移就是枚举新加进去这个点所在项链的大小。

第三个转移是考虑加入点后新增了一个度数为$2$的点还是一个度数为$3$的点，如果加入度数为$2$的点那么它原来肯定也不在这一层中所以要一起加入，当前点肯定是一个新增的度数为$2$的点，另一个点从剩下度数为$2$的$j-1$个点选一个就好了。如果加入了度数为$3$的点那么原来它是一个度数为$2$的点，还是考虑哪个点是在新点加入后成为度数为$3$的点，那么就是从这$k$个点中选一个，当前点变成了一个度数为$2$的点，所以度数为$2$的点个数不变。

第四个转移是上一层不是最后一层的情况了，那么还要连当前层到上一层的父亲边，当前层的不在BFS树上的边暂不考虑。转移与上面类似，这里就不赘述了。

最后设$f(i,j)$为$[i-j+1,i]$这个区间的点现在是最后一层的方案数，这个转移的话枚举一个$k$，$f(i+k,k)=f(i,j)\times g(k,c_2,c_3)$，$c_x$代表$[i-j+1,i]$区间中度数为$x$的点的个数。

统计答案的时候连上最后一层不在BFS树上的边，$ans=\sum_{i = 1}^{n-1}f(n,i)\times g(0,c_2,c_3)$，复杂度$O(\text{n}^3)$。

```cpp
#include <bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define mp make_pair
#define inf (0x3f3f3f3f)
#define Set(a, b) memset(a, b, sizeof(a))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Rep(i, a) for (int i = 0; i < a; ++ i)
#define For(i, a, b) for (int i = a; i <= b; ++ i)
#define Forr(i, a, b) for (int i = a; i >= b; -- i)
#define Travel(i, x) for (int i = head[x]; i; i = nxt[i])

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

template<class T>inline T read(T &_) {
	T __ = getchar(), ___ = 1; _ = 0;
	for (; !isdigit(__); __ = getchar()) if (__ == '-') ___ = -1;
	for (; isdigit(__); __ = getchar()) _ = (_ << 3) + (_ << 1) + (__ ^ 48);
	return _ *= ___;
}

template<class T>inline bool chkmax(T &_, T __) { return _ < __ ? _ = __, 1 : 0; }
template<class T>inline bool chkmin(T &_, T __) { return _ > __ ? _ = __, 1 : 0; }

inline void proStatus() {
	ifstream t("/proc/self/status");
	cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>());
}

const int N = 400 + 3;
const int mod = 1e9 + 7;

int fac[N], ifac[N];

int qpow(int a, int x) { 
	int ret = 1; 
	while (x) {
		if (x & 1) ret = 1ll * ret * a % mod;
		x >>= 1, a = 1ll * a * a % mod;
	}
	return ret;
}

void Math_Init(int n) {
	fac[0] = ifac[0] = 1; 
	For(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	Forr(i, n, 1) ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

int Lian(int n) { return 1ll * fac[n - 1] * ifac[2] % mod; }
int C(int n, int m) { return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int g[N][N][N], f[N][N];

int main() {

	freopen("CF814E.in", "r", stdin);
	freopen("CF814E.out", "w", stdout);

	int n, ans = 0, de[N], c[4];

	Math_Init(N - 3);

	read(n);
	For(i, 1, n) read(de[i]);

	g[0][0][0] = 1; 
	For(i, 0, n) For(j, 0, n - i) For(k, 0, n - i - j) {
		if (!i) {
			if (!j) For(l, 3, k) 
				(g[i][j][k] += 1ll * g[i][j][k - l] * C(k - 1, l - 1) % mod * Lian(l) % mod) %= mod;
			else {
				if (j >= 2) (g[i][j][k] += 1ll * g[i][j - 2][k] * (j - 1) % mod) %= mod;
				if (k >= 1) (g[i][j][k] += 1ll * g[i][j][k - 1] * k % mod) %= mod;
			}
		} else {
			if (j >= 1) (g[i][j][k] += 1ll * g[i - 1][j - 1][k] * j % mod) %= mod;
			if (k >= 1) (g[i][j][k] += 1ll * g[i - 1][j + 1][k - 1] * k % mod) %= mod;
		}
	}

	f[de[1] + 1][de[1]] = 1; 
	For(i, de[1] + 1, n) {
		c[2] = c[3] = 0;
		For(j, 1, i) {
			++ c[de[i - j + 1]];
			For(k, 1, n - i) (f[i + k][k] += 1ll * f[i][j] * g[k][c[2]][c[3]] % mod) %= mod;
		}
	}

	c[2] = c[3] = 0;
	For(i, 1, n - 1) {
		++ c[de[n - i + 1]];
		(ans += 1ll * f[n][i] * g[0][c[2]][c[3]] % mod) %= mod;
	}

	cout << ans << endl;

	return 0;
}

```

---

## 作者：约瑟夫用脑玩 (赞：3)

$\ast$2600

CF 有些评分真是一眼难尽，你说 CF1477E:$\ast$3300 我认了，但你说 CF1083F:$\ast$3300 高的过分吧，你说这道题 $\ast$2600 我觉得也低了。（或者是我太菜了）

------------

首先由最短路的性质每条边只能在同层和下层的点之间连边，否则会被松弛。

又由于最短路唯一，故每个下层的点在上层只有唯一的父亲，是棵最短路树加上一些同层边。

题目还有个要求是树上点编号递增，于是同层的点编号必定连续，考虑一层一层的转移。

一号点比较特殊，没有父亲必须往下层连 $d_i$ 个点，特殊搞掉后考虑 DP。

------------

下文参考了 kls，但它的公式和定义解释实在是不堪入目。

设 $f_{i,j}$ 表示已经考虑了前 $i$ 个点，最后 $j$ 个点与第 $i$ 个点在同一层的方案数。

同时设 $g_{i,j,k}$ 表示这一层有 $i$ 个点，上一层度数为 $2$ 的点有 $j$ 个，度数为 $3$ 的点有 $k$ 个，这一层与上一层的树边和上一层的非树边的方案数。

注意：这里不考虑这层 $i$ 个点内部以及向下一层的连边，即这层的 $i$ 个点都当做度数为 $1$ 用于接到当前的最短路树上。

同时上层的点都默认用了 $1$ 的度数接到最短路树上，也即实际上为 $j$ 个度数剩余为 $1$ 的点和 $k$ 个度数剩余为 $2$ 的点。

------------

令 $cnt2_{i,j}=\sum_{k=i}^j[d_k=2],cnt3_{i,j}=\sum_{k=i}^j[d_k=3]$，即区间内度数为 $2/3$ 的点数下面是简单的式子。

- $f$ 的初值：

  $$f_{du_1+1,du_1}=1$$
  
- 最后的答案：

  $$ans=\sum_if_{n,i}\times g_{0,cnt2_{n-i+1,n},cnt3_{n-i+1,n}}$$
- $f$ 的转移：

  $$f_{i,j}=\sum_kf_{i-j,k}\times g_{j,cnt2_{i-j-k+1,i-j},cnt3_{i-j-k+1,i-j}}$$
- $g$ 的初值：

  $$g_{0,0,0}=1$$
- $g_{0,0,k},k>0$ 的转移：

  $$g_{0,0,k}=\sum_{l=2}^{k-1}g_{0,0,k-l-1}\binom{k-1}{l}\frac{l!}2$$

  这个有必要解释一下，可能是全题唯一要动下脑子的式子。
  
  由于当前层全是度数为 $3$（度数剩余为 $2$）的点，而且下层无点，于是肯定是内部连出多个环。
  
  考虑包含最后一个点的那个环，枚举这个环大小为 $l+1$。
  
  首先最后一个点已经被钦定了，于是从 $k-1$ 个点里选出 $l$ 个点，方案数 $\binom{k-1}{l}$。
  
  考虑把这 $l+1$ 个点排成环，环排列方案是 $l!$，但这道题换物顺序，有翻转同构于是要 $\div 2$，即 $\frac {l!}2$。
  
- $g_{0,j,k},j>0,k\ge0$ 的转移：

  $$g_{0,j,k}=g_{0,j-2,k}\times (j-1)+g_{0,j,k-1}\times k$$

  考虑先搞掉最后一个 $2$ 度（剩余度数为 $1$）点，要么和另一个 $2$ 度配对，否则一个 $3$ 度点掉成 $2$ 度点。
  
- $g_{i,j,k},i>0,j\ge0,k\ge0$ 的转移：

  $$g_{i,j,k}=g_{i-1,j-1,k}\times j+g_{i-1,j+1,k-1}\times k$$

  考虑先搞掉最后一个当前层的点，要么和另一个 $2$ 度配对，要么一个 $3$ 度点掉成 $2$ 度点。
  
空间复杂度 $O(n^3)$，时间复杂度 $O(n^3)$。

代码写着挺舒服，直接放这里吧：

```cpp
signed main()
{
	#ifndef ONLINE_JUDGE
	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	#endif
	int i,j,k,l;n=read();for(i=1;i<=n;i++)du[i]=read();
	for(fac[0]=i=1;i<=n;i++)fac[i]=Ml(fac[i-1],i);
	for(C[0][0]=i=1;i<=n;i++)for(C[i][0]=j=1;j<=n;j++)C[i][j]=Ad(C[i-1][j-1],C[i-1][j]);
	int*g1=G[0][0];
	for(g1[0]=k=1;k<=n;k++)for(l=2;l<k;l++)Add(g1[k],Ml(g1[k-l-1],Ml(C[k-1][l],Ml(fac[l],Inv2))));
	#define g2 G[0]
	for(j=1;j<=n;j++)for(k=0;k<=n;k++)g2[j][k]=Ad(j>1?Ml(g2[j-2][k],j-1):0,k?Ml(g2[j][k-1],k):0);
	for(i=1;i<=n;i++)for(j=0;j<=n;j++)for(k=0;k<=n;k++)G[i][j][k]=Ad(j?Ml(G[i-1][j-1][k],j):0,k?Ml(G[i-1][j+1][k-1],k):0);
	for(i=1;i<=n;i++)ct2[i]=ct2[i-1]+(du[i]==2),ct3[i]=ct3[i-1]+(du[i]==3);
	for(F[du[1]+1][du[1]]=1,i=du[1]+2;i<=n;i++)
	{
		int*f1=F[i];
		for(j=1;j<=i;j++)
		{
			int*f2=F[i-j];
			for(k=1;k<=i-j;k++)Add(f1[j],Ml(f2[k],G[j][ct2[i-j]-ct2[i-j-k]][ct3[i-j]-ct3[i-j-k]]));
		}
	}
	int*f=F[n];
	for(i=1;i<=n;i++)Add(ans,Ml(f[i],g2[ct2[n]-ct2[n-i]][ct3[n]-ct3[n-i]]));
	writenum(ans,10);
	return output;
}
```

---

## 作者：daniEl_lElE (赞：2)

不难发现这玩意其实是分层图，且每一个下层点有且仅有一个对应上层点。

考虑同层之间的连边，显然是一些环和链组成的。

不想推式子，于是设计 $pre_{i,j}$ 表示 $i$ 个 $1$ 度点，$j$ 个 $2$ 度点有多少种方案。这个容易三方算。

有了这个就很容易计算一层原来 $i_1,j_1$ 个 $1/2$ 度点，后来 $i_2,j_2$ 个 $1/2$ 度点的方案。

考虑 $dp_{i,j,k}$ 表示看到第 $i$ 个点，这一层有 $j$ 个 $1$ 度点 $k$ 个 $2$ 度点的方案。

先按上面的原来 $i_1,j_1$ 个 $1/2$ 度点，后来 $i_2,j_2$ 个 $1/2$ 度点的方案把本层之间的连边考虑了，然后向后转移即可。复杂度 $O(n^5)$ 显然跑不满。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7,inv2=(mod+1)/2;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int C[105][105],fac[105],inv[105];
int pre[55][55],f[55][55][55][55],dp[55][55][55],pp[55][55],pre2[55],pre3[55];
signed main(){
	fac[0]=1; for(int i=1;i<=100;i++) fac[i]=fac[i-1]*i%mod;
	inv[100]=qp(fac[100],mod-2); for(int i=99;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=0;i<=100;i++) C[i][0]=1;
	for(int i=1;i<=100;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	int n; cin>>n;
	int a[n+1]; for(int i=1;i<=n;i++) cin>>a[i],pre2[i]=pre2[i-1]+(a[i]==2),pre3[i]=pre3[i-1]+(a[i]==3);
	pre[0][0]=1;
	for(int l1=0;l1<=n;l1++) for(int l2=0;l2<=n;l2++){
		for(int p=3;l1+2<=n&&l2+p-2<=n;p++){
			(pre[l1+2][l2+p-2]+=pre[l1][l2]*C[l1+2][2]%mod*C[l2+p-3][p-3]%mod*fac[p-2])%=mod;
		}
		for(int p=3;l2+p<=n;p++){
			(pre[l1][l2+p]+=pre[l1][l2]*C[l2+p-1][p-1]%mod*fac[p-1]%mod*inv2)%=mod;
		}
	}
	for(int l1=n;l1>=0;l1--) for(int l2=n;l2>=0;l2--) for(int p=1;l1+p*2<=n;p++) (pre[l1+p*2][l2]+=pre[l1][l2]*C[l1+p*2][l1]%mod*fac[p*2]%mod*qp(inv2,p)%mod*inv[p])%=mod;
	for(int l1=0;l1<=n;l1++){
		for(int l2=0;l1+l2<=n;l2++){
			for(int f10=0;f10<=l1;f10++){
				for(int f20=0;f20<=l2;f20++){
					for(int f21=0;f20+f21<=l2;f21++){
						(f[l1][l2][l1-f10+f21][l2-f20-f21]+=pre[f10+f21][f20]*C[l1][f10]%mod*C[l2][f20+f21]%mod*C[f20+f21][f20])%=mod;
					}
				}
			}
		}
	}
	int fs=0;
	if(a[1]==2){
		dp[3][(a[2]==2)+(a[3]==2)][(a[2]==3)+(a[3]==3)]=1; fs=3;
	}
	if(a[1]==3){
		dp[4][(a[2]==2)+(a[3]==2)+(a[4]==2)][(a[2]==3)+(a[3]==3)+(a[4]==3)]=1; fs=4;
	}
	for(int i=fs;i<=n;i++){
		memset(pp,0,sizeof(pp));
		for(int l1=0;l1<=n;l1++){
			for(int l2=0;l1+l2<=n;l2++){
				for(int t1=0;t1<=n;t1++){
					for(int t2=0;t1+t2<=n;t2++){
						(pp[t1][t2]+=dp[i][l1][l2]*f[l1][l2][t1][t2])%=mod;
					}
				}
			}
		}
		for(int l1=0;l1<=n;l1++) for(int l2=0;l1+l2<=n;l2++) dp[i][l1][l2]=pp[l1][l2];
		for(int l1=0;l1<=n;l1++){
			for(int l2=0;l1+l2<=n;l2++){
				int tn=l1+l2*2+i;
				if(tn==i||tn>n) continue;
				int c1=pre2[tn]-pre2[i],c2=pre3[tn]-pre3[i];
				(dp[tn][c1][c2]+=dp[i][l1][l2]*qp(inv2,l2)%mod*fac[tn-i])%=mod;
			}
		}
	}
	cout<<dp[n][0][0];
	return 0;
}
```

---

