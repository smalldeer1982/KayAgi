# Balanced Domino Placements

## 题目描述

Consider a square grid with $ h $ rows and $ w $ columns with some dominoes on it. Each domino covers exactly two cells of the grid that share a common side. Every cell is covered by at most one domino.

Let's call a placement of dominoes on the grid perfectly balanced if no row and no column contains a pair of cells covered by two different dominoes. In other words, every row and column may contain no covered cells, one covered cell, or two covered cells that belong to the same domino.

You are given a perfectly balanced placement of dominoes on a grid. Find the number of ways to place zero or more extra dominoes on this grid to keep the placement perfectly balanced. Output this number modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the initial grid looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237F/23d2c7832fa87b26433f4443e57f8a2c61335a78.png)

Here are $ 8 $ ways to place zero or more extra dominoes to keep the placement perfectly balanced:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237F/f39e74c5e6c5abc41daa487ad47333c83b2084c2.png)

In the second example, the initial grid looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237F/7739b264ee73fb643402600eb5d0f9454c11a61d.png)

No extra dominoes can be placed here.

## 样例 #1

### 输入

```
5 7 2
3 1 3 2
4 4 4 5
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 4 2
1 2 2 2
4 3 4 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
23 42 0
```

### 输出

```
102848351
```

# 题解

## 作者：灵茶山艾府 (赞：9)

下文用 $n$ 表示行数，$m$ 表示列数。

## 从特殊到一般

想一想，如果只能竖着放骨牌，有多少种方案？

设初始有 $\textit{emptyC}$ 列是空的（没有骨牌），枚举竖着放**恰好** $i$ 个骨牌，那么问题可以拆分为：

1. 有 $\textit{emptyC}$ 列可以竖着放骨牌，从中选 $i$ 列的**排列数**，即 $P_{\textit{emptyC}}^{i}$。
2. 有 $n$ 行，其中某些行不能放骨牌（因为初始已经放了骨牌），从中选择 $i$ 个**连续两行**（用来竖着放骨牌）的方案数。

由于第一个问题只和列有关，第二个问题只和行有关，所以两个问题互相独立，根据乘法原理，可以分别计算再相乘。

### 第一个问题

为什么要计算的是排列数，而不是组合数？

假如可以：

- 在第 $1$ 列的第 $1,2$ 行竖着放一个骨牌。
- 在第 $2$ 列的第 $3,4$ 行竖着放一个骨牌。
- 在第 $3$ 列的第 $5,6$ 行竖着放一个骨牌。

根据题目约束，这 $3$ 个骨牌也可以这样放：

- 在第 $1$ 列的第 $3,4$ 行竖着放一个骨牌。
- 在第 $2$ 列的第 $5,6$ 行竖着放一个骨牌。
- 在第 $3$ 列的第 $1,2$ 行竖着放一个骨牌。

也就是说，只要我能竖着放 $3$ 个骨牌，那么这 $3$ 个骨牌之间就有 $3!$ 种不同方案。

### 第二个问题

这可以用 DP 解决。

定义 $f_{i,j}$ 表示从前 $i$ 行选 $j$ 个连续两行的方案数。

考虑选或不选，有

$$
f_{i,j} = f_{i-1,j} + f_{i-2,j-1}
$$

其中 $f_{i-2,j-1}$ 只有当第 $i-1$ 行和第 $i$ 行都是空的才能转移（选）。

初始值 $f_{i,0} = 1$。

有 $n$ 行，其中某些行不能放骨牌，从中选择 $i$ 个连续两行（用来竖着放骨牌）的方案数即 $f_{n,i}$。

## 回到原问题

假设我们已经把 $i$ 个骨牌竖着放在棋盘上，那么剩下要解决的问题，就是在此基础上，计算横着放 $j$ 个骨牌的方案数。思考方式同上。

但是，如果横着放 $j$ 个骨牌，就会导致有额外的 $2j$ 列是不能竖着放骨牌的，所以对排列数会有影响。具体分析如下。

设初始有 $\textit{emptyR}$ 行是空的（没有骨牌），有 $\textit{emptyC}$ 列是空的。

枚举竖着放**恰好** $i$ 个骨牌，横着放**恰好** $j$ 个骨牌，那么问题可以拆分为：

1. 有 $\textit{emptyC}-2j$ 列可以竖着放骨牌，从中选 $i$ 列的排列数，即 $P_{\textit{emptyC}-2j}^{i}$。
2. 有 $\textit{emptyR}-2i$ 行可以横着放骨牌，从中选 $j$ 行的排列数，即 $P_{\textit{emptyR}-2i}^{j}$。
3. 有 $n$ 行，其中某些行不能放骨牌，从中选择 $i$ 个连续两行（用来竖着放骨牌）的方案数。
4. 有 $m$ 列，其中某些列不能放骨牌，从中选择 $j$ 个连续两列（用来横着放骨牌）的方案数。

和 $f_{n,i}$ 一样，用同样的方法计算有 $m$ 列，其中若干列不能放骨牌，从中选择 $j$ 个连续两列（用来横着放骨牌）的方案数，记作 $g_{m,j}$。

上述四个问题的方案数相乘，即

$$
f_{n,i}\cdot g_{m,j}\cdot P_{\textit{emptyC}-2j}^{i}\cdot P_{\textit{emptyR}-2i}^{j}
$$

枚举 $i$ 和 $j$，答案为

$$
\sum_{i=0}^{\lfloor n/2 \rfloor} \sum_{j=0}^{\lfloor m/2 \rfloor}f_{n,i}\cdot g_{m,j}\cdot P_{\textit{emptyC}-2j}^{i}\cdot P_{\textit{emptyR}-2i}^{j}
$$

## AC 代码（Golang）

```go
package main
import . "fmt"

func main() {
	const mod = 998244353
	const mx = 3600
	pow := func(x, n int) int {
		res := 1
		for ; n > 0; n /= 2 {
			if n%2 > 0 {
				res = res * x % mod
			}
			x = x * x % mod
		}
		return res
	}
	F := [mx + 1]int{1}
	for i := 1; i <= mx; i++ {
		F[i] = F[i-1] * i % mod
	}
	invF := [...]int{mx: pow(F[mx], mod-2)}
	for i := mx; i > 0; i-- {
		invF[i-1] = invF[i] * i % mod
	}
	perm := func(n, k int) int {
		return F[n] * invF[n-k] % mod
	}

	var n, m, k, r1, c1, r2, c2, ans int
	Scan(&n, &m, &k)
	banR := make([]bool, n)
	banC := make([]bool, m)
	for ; k > 0; k-- {
		Scan(&r1, &c1, &r2, &c2)
		banR[r1-1] = true
		banR[r2-1] = true
		banC[c1-1] = true
		banC[c2-1] = true
	}

	calc := func(ban []bool) ([]int, int) {
		n := len(ban)
		f := make([][]int, n+1)
		for i := range f {
			f[i] = make([]int, n/2+1)
			f[i][0] = 1
		}
		for i := 1; i < n; i++ {
			for j := 1; j <= (i+1)/2; j++ {
				f[i+1][j] = f[i][j]
				if !ban[i] && !ban[i-1] {
					f[i+1][j] = (f[i+1][j] + f[i-1][j-1]) % mod
				}
			}
		}
		empty := 0
		for _, b := range ban {
			if !b {
				empty++
			}
		}
		return f[n], empty
	}

	f, emptyR := calc(banR)
	g, emptyC := calc(banC)
	for i, v := range f { // i 个竖放
		for j, w := range g { // j 个横放
			if j > emptyR-i*2 || i > emptyC-j*2 {
				break
			}
			ans = (ans + v*w%mod*perm(emptyC-j*2, i)%mod*perm(emptyR-i*2, j)) % mod
		}
	}
	Print(ans)
}
```

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：Achtoria (赞：9)

基于观察不难发现骨牌横着放会一起占两列，占一行；竖着放会占两行，占一列。

因为原问题过于具体，考虑抽象一下这个问题。

不难发现问题可以很简单地被抽象为每一行可以一次选择连续的两行放一个物品 $A$，或者选一行放一个物品 $B$。

那么问题就转化成行和列都要选择放若干个物品 $A, B$ 且行放的 $A$ 的数量等于列放的 $B$ 的数量，行放的 $B$ 的数量等于列放的 $A$ 的数量。

但是你会发现这样一个放物品的过程会对应原来很多个放骨牌的方案，因为行与列之间 $A, B$ 可以配对。

并且，对于任意一个配对方案都对应着原来放骨牌的一个方案。

可以发现行放的 $A, B$ 之间配对是不影响的，因此配对的方案数应该是 $|A|!|B|!$。

于是我们就只需要考虑有多少种选择上述的选择物品 $A, B$ 的方法了。

不难发现的是，行和列是独立开来的，因此我们可以分开考虑行和列的方案数，然后通过乘法原理相乘。下面以计算行的方案数为例。

首先不难发现一个暴力，令 $f_{i, j, k}$ 表示当前考虑完前 $i$ 行，$A$ 放了 $j$ 个，$B$ 放了 $k$ 个的方案数。

但是状态是 $n ^ 3$ 的，显然不可取，只能从状态上下手优化。

你会发现实际上 $B$ 的放置方法大可不必如此计算，因为只要有一个空位就能放一个 $B$，我们只要知道最后的空位数量就可以直接计算出放 $k$ 个 $B$ 的方案数。

那么可以考虑令 $f_{i, j}$ 表示考虑完前 $i$ 行，$A$ 放了 $j$ 个且还没有放 $B$ 的方案数，转移是 $O(1)$ 的。

那么最后可以放 $B$ 的空位就有 $cnt - 2 \times j$（其中 $cnt$ 为除去题目中已放置的骨牌还剩下的行数），放 $k$ 个 $B$ 就有 $\dbinom{cnt - 2 \times j}{k}$ 种方案。

最后合并时因为只需要枚举行选了多少个 $A$ 多少个 $B$ 就可以确定列选择的数量，因此合并的复杂度也是 $O(n ^ 2)$ 的。

于是我们就在 $O(n ^ 2)$ 的时间复杂度内完成了这个问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; ++i)
const int N = 3600 + 5;
const int Mod = 998244353;
bool row[N], com[N];
int n, m, k, x, y, L, rc, cc, xx, yy, ans, fac[N], f[N][N], g[N][N], C[N][N];
int read() {
    char c; int x = 0, f = 1;
    c = getchar();
    while (c > '9' || c < '0') { if(c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int Inc(int a, int b) { return (a += b) >= Mod ? a - Mod : a;}
int Mul(int a, int b) { return 1ll * a * b % Mod;}
int main() {
    n = read(), m = read(), k = read();
    rep(i, 1, k) {
        x = read(), y = read(), xx = read(), yy = read();
        row[x] = row[xx] = com[y] = com[yy] = 1, --rc, --cc;
        if(x != xx) --rc; if(y != yy) --cc;
    }
    rc += n, cc += m;
    L = max(n, m), fac[0] = C[0][0] = 1;
    rep(i, 1, L) fac[i] = Mul(fac[i - 1], i), C[i][0] = 1;
    rep(i, 1, L) rep(j, 1, i) C[i][j] = Inc(C[i - 1][j - 1], C[i - 1][j]);
    f[0][0] = 1;
    rep(i, 1, n) rep(j, 0, i / 2) {
        f[i][j] = Inc(f[i][j], f[i - 1][j]);
        if(i >= 2 && !row[i] && !row[i - 1]) f[i][j] = Inc(f[i][j], f[i - 2][j - 1]);
    }
    g[0][0] = 1;
    rep(i, 1, m) rep(j, 0, i / 2) {
        g[i][j] = Inc(g[i][j], g[i - 1][j]);
        if(i >= 2 && !com[i] && !com[i - 1]) g[i][j] = Inc(g[i][j], g[i - 2][j - 1]);
    }
    rep(i, 0, rc / 2) rep(j, 0, (cc - i) / 2) if(2 * i + j <= rc && i + 2 * j <= cc){
        ans = Inc(ans, Mul(f[n][i], Mul(g[m][j], Mul(C[rc - 2 * i][j], Mul(C[cc - 2 * j][i], Mul(fac[i], fac[j]))))));
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Owen_codeisking (赞：7)

计数~~套路~~题。

首先有一个 $O(\text{不能过})$ 的暴力，状压列放的情况，再记一下上一行是否放了骨牌， $dp$ 一下。

~~这对实力有什么提升吗~~

我们发现可以先决定横的骨牌放哪些相邻列，竖的骨牌放哪些相邻行，把这些列剔除掉以后再决定横的骨牌放哪些列，竖的骨牌放哪些行，这样是不会冲突的。

你明白了这个以后就可以设计 $dp$ 了。

$sumx,sumy$ 分别表示放完初始骨牌后还剩的行/列数。

$f[i][j]$ 表示前 $i$ 行选 $j$ 个相邻行的方案数。

$g[i][j]$ 表示前 $i$ 列选 $j$ 个相邻列的方案数。

$f[i][j]=f[i-1][j]$

$f[i][j]+=f[i-2][j-1](i\ge 2,j\ge 1,\text{i和i-1行没有放骨牌})$

$g[i][j]$ 的 $dp$ 设计类似。

$$ans=\sum_{i=0}^{\lfloor \frac {sumx}{2} \rfloor}\sum_{j=0}^{\lfloor \frac {sumy}{2} \rfloor}f[r][i]\times g[c][j]\times {sumy-2\times j\choose i}\times {sumx-2\times i\choose j}\times i!\times j!$$

时间复杂度 $O(n^2)$。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=3605;
const int mod=998244353;
int h,w,n;
bool visx[maxn],visy[maxn];
ll f[maxn][maxn],g[maxn][maxn],fac[maxn],inv_fac[maxn];
inline ll A(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*inv_fac[n-m]%mod;
}
int main()
{
	fac[0]=fac[1]=inv_fac[0]=inv_fac[1]=1;
	for(int i=2;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<maxn;i++) inv_fac[i]=(mod-mod/i)*inv_fac[mod%i]%mod;
	for(int i=2;i<maxn;i++) inv_fac[i]=inv_fac[i]*inv_fac[i-1]%mod;
	scanf("%d%d%d",&h,&w,&n);
	int a,b,c,d,sumx=0,sumy=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		visx[a]=visx[c]=1,visy[b]=visy[d]=1;
	}
	for(int i=1;i<=h;i++) sumx+=!visx[i];
	for(int i=1;i<=w;i++) sumy+=!visy[i];
	f[0][0]=g[0][0]=1;
	for(int i=1;i<=h;i++)
		for(int j=0;j*2<=sumx;j++) // 边界要注意，不是 w
			f[i][j]=(f[i-1][j]+((j && i>=2 && !visx[i] && !visx[i-1])?f[i-2][j-1]:0))%mod;
	for(int i=1;i<=w;i++)
		for(int j=0;j*2<=sumy;j++)
			g[i][j]=(g[i-1][j]+((j && i>=2 && !visy[i] && !visy[i-1])?g[i-2][j-1]:0))%mod;
	ll ans=0;
	for(int i=0;i*2<=sumx;i++)
		for(int j=0;j*2<=sumy;j++)
			ans=(ans+f[h][i]*g[w][j]%mod*A(sumx-2*i,j)%mod*A(sumy-2*j,i))%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Rainbow_qwq (赞：4)

- [CF1237F Balanced Domino Placements](https://www.luogu.com.cn/problem/CF1237F)

---

可以考虑简化问题，考虑 $1\times n$ 的一行中，有一些不能放，放 $a$ 个一格骨牌， $b$ 个两格骨牌的方案数。

dp ， 设 $f(i,j)$ 表示前 $i$ 个格子放 $j$ 个两格的方案数。

那如果 $i,i-1$ 都能放， $f(i,j)=f(i-1,j)+f(i-2,j-1)$ ；

否则 $f(i,j)=f(i-1,j)$ 。

最后放 $a$ 个一格骨牌， $b$ 个两格骨牌的方案数 $=f(n,b)\times C_{cnt-2j}^{i}$ ，$cnt$ 表示一行有多少个可以放的格子。

画图会发现，一些行，一些列是不能放的，可以看做上面的简化版问题，所以我们对每一行，每一列都求一下上面的 dp 值，放进 $f,g$ 两个数组里。

放一个横放的骨牌相当于占掉一行两列，放一个竖放的骨牌相当于占掉一列两行。

枚举 $i$ 个横放，$j$ 个竖放，答案为 $\sum f(n,j)g(m,i)C_{cntx-2i}^{j}C_{cnty-2i}^{j}\times i!j!$

其中 $i!j!$ 是因为要行列两两匹配。

code↓ 代码中的变量略微有不同。
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define mod 998244353
inline int qpow(int a,int b=mod-2){
	int res=1;
	for(;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;
	return res;
}

#define maxn 4005
int n,m,k,res;
int fac[maxn],inv[maxn];
void prework(int n)
{
	fac[0]=1;
	For(i,1,n)fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n]);
	Rep(i,n-1,0)inv[i]=qpow(fac[i])%mod;
}
inline int C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void add(int&a,int b){
	a+=b;if(a>mod)a%=mod;
}

int cx,cy;
bool vx[maxn],vy[maxn];
int f[maxn][maxn],g[maxn][maxn];

signed main()
{
	n=read(),m=read(),k=read();
	int mx=max(n,m);
	prework(mx);
	For(i,1,k){
		int a=read(),b=read(),c=read(),d=read();
		vx[a]=vx[c]=1,vy[b]=vy[d]=1;
	}
	For(i,1,n)cx+=vx[i];
	For(i,1,m)cy+=vy[i];
	For(i,0,n)f[i][0]=1;
	For(i,2,n)
		For(j,1,mx){
			f[i][j]=f[i-1][j];
			if(!vx[i]&&!vx[i-1])add(f[i][j],f[i-2][j-1]);
		}
	For(i,0,m)g[i][0]=1;
	For(i,2,m)
		For(j,1,mx){
			g[i][j]=g[i-1][j];
			if(!vy[i]&&!vy[i-1])add(g[i][j],g[i-2][j-1]);
		}
	For(i,0,mx)//横 
		For(j,0,mx)//竖 
			if(i*2+j<=n-cx && i+j*2<=m-cy)
				res=(res+
					1ll*f[n][i]*C(n-cx-2*i,j)%mod
						*g[m][j]%mod*C(m-cy-2*j,i)%mod
						*fac[i]%mod*fac[j]%mod
				)%mod;
	cout<<res; 
    return 0;
}
```

---

## 作者：Kelin (赞：3)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102636886)
给你一个$n\times m$的棋盘，上面已经放了$k$个的骨牌（$1\times2$）

对于一个骨牌的每个格子，不能有其他骨牌的格子和它在同一列，同一行

你可以在剩下的格子里放骨牌，也可以不放

问这个棋盘有多少种放骨牌的方案，对$998244353$取模

$1\le n,m\le3600,0\le k\le2400$

---

## 题解
假设我们放了$d_x$个横向的骨牌，$d_y$个纵向的骨牌

如果某一行已经被占了，将其标记为$1$，否则为$0$，列也是一样

设$R$表示至少有$d_x+2d_y$行$0$且有$d_y$对相邻的$0$的方案数，$C$表示至少有$2d_x+d_y$列$0$且有$d_x$对相邻的$0$的方案数

因为$d_x$行放了横向的骨牌，且每行的骨牌有$d_x$个位置可以选择（纵向同理）

那么$Ans=R\times C\times d_x!\times d_y!$

考虑怎么求$R$，记$f(i,j)$表示前$i$行放了$j(0\le j\le\lfloor\frac i2\rfloor )$个纵向骨牌的方案数，那么有

$f(i,j)=1,j=0$

$f(i,j)=f(i-1,j)$  第$i,i-1$行有一行被占了

$f(i,j)=f(i-1,j)+f(i-2,j-1)$ 第$i,i-1$行均未被占


如果有总共有$h$行$0$，那么$R=f(h,d_y){h-2d_y\choose d_x}$

$C$可以按照同样的方式计算（设为$g(i,j)$。$f$和$g$的$dp$可以用滚动数组优化）

设$n'$为没被占的行数，$m'$为没被占的列数，则

$Ans=\sum_{d_x}\sum_{d_y}f(n',d_y)g(m',d_x){n'-2d_y\choose d_x}{m'-2d_x\choose d_y}d_x!d_y!$

$\ \ \ \ \ \ \ \ =\sum_{d_x}\sum_{d_y}f(n',d_y)g(m',d_x)P^{d_x}_{n'-2d_y}P^{d_y}_{m'-2d_x}$

其中$0\le d_x+2d_y\le n',0\le 2d_x+d_y\le m'$

时间复杂度$O(nm)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
	char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
	while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
const int N=4000+5,Mod=998244353;
typedef int arr[N];
int n,m,k,ans;arr fac,ifac;
inline int Plus(int a,int b){return a+b-(a+b>Mod?Mod:0);}
inline int Mul(int a,int b){return (long long)a*b%Mod;}
inline int P(int n,int m){return Mul(fac[n],ifac[n-m]);}
inline int fpm(int a,int b){
	int x=1;
	for(;b;a=Mul(a,a),b>>=1)
		if(b&1)x=Mul(x,a);
	return x;
}
inline void GetFact(int S){
	fac[0]=1;
	fp(i,1,S)fac[i]=Mul(fac[i-1],i);
	ifac[S]=fpm(fac[S],Mod-2);
	fd(i,S,1)ifac[i-1]=Mul(ifac[i],i);
}
vector<int>dp(const vector<bool>&u){
	int n=u.size()-1;
	vector<int>f1(n/2+1),f2(n/2+1),f3;
	f2[0]=1;
	fp(i,1,n){
		f3=f2;
		if(!u[i]&&!u[i-1])
			fp(j,1,i/2)f3[j]=Plus(f3[j],f1[j-1]);
		f1=f2;f2=f3;
	}
	return f2;
}
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	sd(n),sd(m),sd(k);
	vector<bool>ux(n+1),uy(m+1);
	fp(i,1,2*k){
		int x,y;
		sd(x),sd(y);
		ux[x]=uy[y]=1;
	}
	fp(i,1,n)if(ux[i])--n;
	fp(i,1,m)if(uy[i])--m;
	GetFact(max(n,m)+1);
	vector<int>f=dp(ux);
	vector<int>g=dp(uy);
	fp(dy,0,(int)f.size()-1)
		for(int dx=0;dx<(int)g.size()&&dx+2*dy<=n&&2*dx+dy<=m;++dx)
			ans=Plus(ans,Mul(Mul(f[dy],g[dx]),Mul(P(n-(dy<<1),dx),P(m-(dx<<1),dy))));
	printf("%d",ans);
return 0;
}
```

---

## 作者：Reunite (赞：2)

不错的组合计数题。

## 一
---

首先需要发现一个性质：横向和竖向摆放的牌互不干扰。感觉其他题解里说的不多，我简单说明一下。

行和列互不干扰的原因是，只要摆了一块骨牌，就会造成两行一列（或一行两列）格无法放置，而这里的行列是没有区别的，反正给定的 $k$ 个骨牌所限定的也摆不了。所以行与行之间，列与列之间无本质区别，这启示我们先不考虑平面内进行计数，而是行列分开分别计数。

首先根据给定的 $k$ 个骨牌限定好不能摆放的行和列，这样就和给定的骨牌无关了，我们只关心哪些行和列是可以摆放的。和其他题解类似地，我们设 $f_{i,j}$ 为前 $i$ 行，摆放了 $j$ 个**竖向**的骨牌的方案，$g_{i,j}$ 为前 $i$ 列，摆放了 $j$ 个**横向**的骨牌的方案。注意这里我们仅仅对于这一整行或一整列是否摆放骨牌进行计算方案。换而言之，我们在分别做 $f,g$ 的时候，只是把二维平面当做一维的轴来看的。

因为我们这样设计的状态，能够把行和列之间的互相影响暂时抛开，否则无法计数。会发现我们算出这两个数组后，行和列的相互影响是只与选择放骨牌的数量有关的，与具体怎样摆放没有一点关系。

所以计算答案就简单了吧，记一下全空的行和列的数量分别为 $nn,mm$，则：

$$ans=\sum_{i=0}^{\frac{nn}{2}}\sum_{j=0}^{\frac{mm}{2}} f_{n,i}\cdot g_{m,j} \binom{mm-2j}{i} \binom{nn-2i}{j}i!j! $$

除法为整除。

上式的意义是简单的，即我们钦定横向和竖向摆放的骨牌数量，后面的组合数和阶乘就是各自把骨牌分配给某一行某一列的方案数了。

## 二
---

复杂度 $O(nm)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mod 998244353
using namespace std;

int n,m,k;
bool mp1[3605];
bool mp2[3605];
ll inv[3605];
ll fac[3605];
ll infac[3605];
int f[3605][3605];
int g[3605][3605];

inline ll C(int a,int b){return a<b||b<0?0:fac[a]*infac[b]%mod*infac[a-b]%mod;}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		mp1[a]=mp1[c]=1;
		mp2[b]=mp2[d]=1;
	}
	inv[1]=fac[0]=fac[1]=infac[0]=infac[1]=1;
	int nn=0,mm=0;
	for(int i=2;i<=max(n,m);i++){
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		fac[i]=fac[i-1]*i%mod;
		infac[i]=infac[i-1]*inv[i]%mod;
	}
	f[0][0]=g[0][0]=1;
	for(int i=1;i<=n;i++){
		nn+=!mp1[i];
		for(int j=0;j*2<=i;j++){
			f[i][j]=f[i-1][j];
			if(i>=2&&!mp1[i]&&!mp1[i-1]) (f[i][j]+=f[i-2][j-1])%=mod;
		}
	}
	for(int i=1;i<=m;i++){
		mm+=!mp2[i];
		for(int j=0;j*2<=i;j++){
			g[i][j]=g[i-1][j];
			if(i>=2&&!mp2[i]&&!mp2[i-1]) (g[i][j]+=g[i-2][j-1])%=mod;
		}
	}
	ll ans=0;
	for(int i=0;i*2<=nn;i++){
		for(int j=0;j*2<=mm;j++)
			(ans+=1ll*f[n][i]*g[m][j]%mod*C(mm-2*j,i)%mod*C(nn-2*i,j)%mod*fac[i]%mod*fac[j]%mod)%=mod;
	}
	printf("%lld\n",ans);

	return 0;
}

```

---

## 作者：TonyYin (赞：1)

## 题意

给你一个 $n\times m$ 的棋盘，上面已经放了 $k$ 个的骨牌，每个骨牌是 $1\times 2$ 的矩形。

对于每个骨牌，不能有其他骨牌和它在同一行同一列。

现在要在剩下的格子里放若干个骨牌（允许不放）。

求当前棋盘放骨牌方案数，对 $998244353$ 取模。

$1\leq n, m\leq 3600, 0\leq k\leq 2400$.

## 分析

最终加到棋盘上的骨牌，**分为横放和竖放两种**。

- 横放：形如 $(i, j)(i, j+1)$​，占用两行，一列。
- 竖放：形如 $(i, j)(i+1, j)$​，占用一行，两列。

考虑**枚举这选择两种骨牌的数量**，设选择了 $x$​ 个骨牌横放，$y$​ 个骨牌竖放。

那么问题转化为：先**在所有空余的行中，选择 $x+2\times y$ 行，且这其中有 $y$​ 对行相邻**，之后再**从所有空余的列中，选择 $y+2\times x$ 列，其中有 $x$ 对列相邻。**

由于这两个问题独立，且处理方法类似，所以对行和列分别考虑。

## 分析 - 子问题

先来考虑行的问题。

对于可以任意选取的 $x$​​ 行（无需考虑必须相邻），可以**直接用组合数求解**。

具体来说，预处理出棋盘剩余行数 $rest_x$​ 之后，这部分的方案数 $\operatorname{Ans}_1=C_{rest_x -2\times y}^{x}$.

对于需要特殊考虑的 $2\times y$ 行，用计数 DP 处理。

**设 $\operatorname{dp}_{i, j}$​ 表示前 $i$​ 行选 $j$​​ 对的方案数**，那么这部分的方案数 $\operatorname{Ans}_2=\operatorname{dp}_{n,y}$​​.

考虑如何转移。

如果当前行和前一行都是空的，则：
$$
\operatorname{dp}_{i, j}=\operatorname{dp}_{i-1, j}+\operatorname{dp}_{i-2, j-1}
$$
否则，无法选取 $(i-1, i)$ 这对行，转移方程为：
$$
\operatorname{dp}_{i, j}=\operatorname{dp}_{i-1, j}
$$
这样，选取 $x+2\times y$ **行的方案数即为**：$A=\operatorname{Ans}_1\times \operatorname{Ans}_2$.

## 合并答案

目前，求出了选取行的方案数为 $A$​，同理可求出选取列的方案数为 $B$.

但**选取 $x$​​​ 个横放，$y$​​​ 个竖放的骨牌的方案数 $\operatorname{Ans}_{x, y}\neq A\times B$​​​.**

这是因为：确定一个骨牌的位置需要一行两列/一列两行，**行列要两两匹配**，这个方案数是 $\operatorname{fac}_x\times \operatorname{fac}_y$​. （ $\operatorname{fac}$​ 代表阶乘） 

因此，**$x, y$ 对应的方案数 $\operatorname{Ans}_{x, y}=AB\operatorname{fac}_x\operatorname{fac}_y$​​​​.**

题目所求的答案为：
$$
\operatorname{Sum}=\sum_x\sum_y{\operatorname{Ans}_{x, y}}
$$

## 复杂度

先预处理行和列的 $\operatorname{dp}$​ 数组​，时间复杂度 $\mathcal{O}(nm)$.

之后枚举 $x, y$，时间复杂度同样 $\mathcal{O}(nm)$.

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 4000, mod = 998244353;
int n, m, p;
bool visr[MAXN], visc[MAXN];
int dpr[MAXN][MAXN], dpc[MAXN][MAXN];
int rstr, rstc;
int power(int x, int k) {
	int ret = 1;
	while(k) {
		if(k & 1) ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}
int fac[MAXN], inv[MAXN];
void init() {
	fac[0] = 1;
	for(int i = 1; i <= max(n, m); i++) {
		fac[i] = fac[i - 1] * i % mod;
	}
	inv[max(n, m)] = power(fac[max(n, m)], mod - 2);
	for(int i = max(n, m) - 1; i >= 0; i--) {
		inv[i] = inv[i + 1] * (i + 1) % mod;
	}
}
int C(int a, int b) {
	return fac[a] * inv[b] % mod * inv[a - b] % mod;
}
signed main() {
	scanf("%lld%lld%lld", &n, &m, &p); init();
	for(int i = 1; i <= p; i++) {
		int r1, c1, r2, c2;
		scanf("%lld%lld%lld%lld", &r1, &c1, &r2, &c2);
		visr[r1] = visr[r2] = true;
		visc[c1] = visc[c2] = true;
	}
	for(int i = 1; i <= n; i++) rstr += (!visr[i]);
	for(int i = 1; i <= m; i++) rstc += (!visc[i]);
	for(int i = 0; i <= n; i++) dpr[i][0] = 1;
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j <= n / 2; j++) {
			dpr[i][j] = dpr[i - 1][j];
			if(!visr[i] && !visr[i - 1]) {
				dpr[i][j] = (dpr[i][j] + dpr[i - 2][j - 1]) % mod;
			}
		}
	}
	for(int i = 0; i <= m; i++) dpc[i][0] = 1;
	for(int i = 2; i <= m; i++) {
		for(int j = 1; j <= m / 2; j++) {
			dpc[i][j] = dpc[i - 1][j];
			if(!visc[i] && !visc[i - 1]) {
				dpc[i][j] = (dpc[i][j] + dpc[i - 2][j - 1]) % mod;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= n/2; i++) {//竖着放的
		for(int j = 0; j <= m/2; j++) {//横着放的
			if(i * 2 + j > rstr || i + j * 2 > rstc) continue;
			ans += dpr[n][i] * dpc[m][j] % mod * C(rstr - 2 * i, j) % mod * C(rstc - 2 * j, i) % mod * fac[i] % mod * fac[j] % mod;
			ans %= mod;
		}
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：Mashu77 (赞：0)

题意：给你一个 
$n
×
m$
 的棋盘，上面已经放了 
$k$
 个 
$1
×
2$
 的骨牌。

对于一个骨牌的每个格子，不能有其他骨牌的格子与它在同一行、同一列。

你可以在剩下的格子里放骨牌。

问这个棋盘有多少种放骨牌的方案。对 
$998244353$
 取模。

$1
≤
n
,
m
≤
3600
,
0
≤
k
≤
2400$

题解：对于两个同种骨牌（不妨设占 
$1$
 行 
$2$
 列），交换它们的 
$x$
 坐标，结果仍成立。这种性质启发我们将行列分开分析。

设有 
$i$
 个 
$1
×
2$
 骨牌，$j$
 个 
$2
×
1$
 骨牌。则答案为 
$f
(
i
,
j
)
×
g
(
j
,
i
)
×
i
!
×
j
!$，其中 
$f
(
i
,
j
)$
 表示只考虑行的限制，放 
$i$
 个 
$1
×
1$，$j$
 个 
$2
×
1$
 的方案。$g$
 同理。

求 
$f$。发现再加一维限制，$f
(
k
,
i
,
j
)$ 表示前 
$k$
 行，$i$
 个 
$1$，$j$
 个 
$2$，即可轻松转移。但复杂度 
$O
(
n^
3
)$。因为 
$i$
 只占 
$1$，不难想到只算 
$j$，最后用组合数算答案。
$f
(
i
,
j
)$
 表示前 
$i$
 行，$j$
 个 
$2$。则上面的 
$f
(
i
,
j
)$
 为 
$f(n,j) \times \binom{cn-2j}{i}$，其中 
$c
n$
 表示有多少行可以放。于是实现 
$O
(
n^
2
)$。

---

## 作者：violin_wyl (赞：0)

# [Balanced Domino Placements](https://codeforces.com/contest/1237/problem/F)

## 解析：

### 题目大意：

给你一个 $n\times m$ 的棋盘（$1\le n,m\le3600$），上面已经放了 $k$ （$0\le k\le2400$）个的骨牌（$1\times2$）对于一个骨牌的每个格子，不能有其他骨牌的格子和它在同一列，同一行。

你可以在剩下的格子里放骨牌，也可以不放，问这个棋盘有多少种放骨牌的方案，对 $998244353$ 取模。

--------------------------

### 思路：

可以发现，横着的骨牌占 1 行 2 列，纵骨牌占 2 行 1 列。设最后选 $a$ 个横向的骨牌，$b$ 个纵向的，那么 $2a+b\leq m,a+2b\leq n$，是一种合法方案的充要条件。

先考虑 $n\times 1$ 的情况，可以发现这种情况下横向骨牌等价于一个 $1\times 1$ 的格子，设 $f_{i,j}$ 表示前 $i$ 行放 $j$ 个纵向骨牌的方案数，那么有转移
$$
f_{i,j}=f_{i-1,j}+(f_{i-2,j-1}\times [tx_i \& tx_{i-1}])
$$
其中 $[tx_i \& tx_{i-1}]$ 表示前两行是否已经有骨牌，这个可以预处理已经存在的 $k$ 个骨牌。那么 $a$ 个横向骨牌 $(1\times 1)$ 的格子 $b$ 个纵向的方案数应该是 $f_{n,b}\times \binom{sn-2b}{a}$，$sn$ 表示去掉不能选的行之后的行数，$2b$ 是纵向骨牌占的格子个数。

$g_{i,j}$ 就是 $1\times m$ 时的方案数，转移等价于 $f_{i,j}$ 不做解释。

考虑怎么统计答案。先给出式子：$ans=\sum_{i=0}^n\sum_{j=0}^mf_{n,i}\times \binom{sn-2i}{j}\times f_{m,j}\times \binom{sm-2j}{i}\times i!\times j!$。其中 $i,j$ 是枚举横向纵向放的骨牌个数。

这里解释一下，以 $i$ 为例：我们在 $n\times 1$ 的时候不能在一列放 $i$ 个骨牌 $(f_{n,i})$，但是如果有 $i$ 列可以放，一列一个，那么就能放下 $(\binom{sm-2j}{i})$。若对于 $i$ 列的所有纵向骨牌我从上到下给一个编号，那么最后方案数等价于全排列，所以这部分方案数为 $f_{n,i}\times\binom{sm-2j}{i}\times  i!$。

读者可以自行画图结合理解。

时间复杂度 $\mathcal O(n^2)$。



---

