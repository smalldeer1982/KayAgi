# [COTS 2024] 奇偶矩阵 Tablica

## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D1T2。$\texttt{1s,1G}。$

## 题目描述

考虑只包含 $0$ 和 $1$ 的 $N\times M$ 矩阵 $A$。

我们称满足以下条件的矩阵是好的：

- $\forall 1\le i\le N$，$\displaystyle \sum_{j=1}^M A_{i,j}\in \{1,2\}$；
- $\forall 1\le j\le M$，$\displaystyle \sum_{i=1}^N A_{i,j}\in \{1,2\}$。

求出 $N$ 行 $M$ 列的好的矩阵的数量，对 $(10^9+7)$ 取模。



## 说明/提示


#### 样例解释

样例 $1$ 解释如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/xufx7ad6.png)

#### 数据范围

对于 $100\%$ 的数据，$1\le N,M\le 3\, 000$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $10$  | $N, M \leq 6$   |
| $2$  | $18$  | $N, M \leq 50$  |
| $3$  | $31$  | $N, M \leq 200$ |
| $4$  | $41$  | 无额外约束 |



## 样例 #1

### 输入

```
2 2```

### 输出

```
7```

## 样例 #2

### 输入

```
3 3```

### 输出

```
102```

## 样例 #3

### 输入

```
15 20```

### 输出

```
415131258```

# 题解

## 作者：yyyyxh (赞：24)

萌萌计数签到题！还是有有趣且直接的做法的。题解区现有做法有点麻烦了！

考虑枚举 $N$ 行中有 $a$ 行和为 $1$，$b$ 行和为 $2$；$M$ 列中有 $c$ 列和为 $1$，$d$ 列和为 $2$。

容易发现这个枚举量是 $O(\min(N,M))$ 级别的，因为我们有 $a+b=N,c+d=M,a+2b=c+2d$。

我们考虑把每一列的 $1$ 和 $2$ 的和分配到行上去，可以看作这样一个过程：有 $M$ 种颜色的小球，其中 $c$ 种颜色各有一个小球，$d$ 种颜色各有两个小球。然后你需要把这些小球划分成 $N$ 个大小不超过 $2$ 的非空集合序列，满足同一个集合的球颜色互不相同。（即集合有标号，但同一个集合内的球无标号）

那首先我们考虑把这 $c+2d$ 个球排成一个序列有多少种可能，容易发现是多重集组合数 $\frac{(c+2d)!}{2^d}$。然后我们把这个序列按顺序分配给每个集合。此时可能会出现两个问题：

+ 分配出了如 $\{1,1\}$  这样两个相同元素的集合。

+ $\{1,2\}$ 和 $\{2,1\}$ 两种分配方式应该算作同一种方案。

考虑容斥掉第一种情况后第二种方案数直接乘上 $2^{-b}$ 就可以了。

那么我们钦定有 $t$ 个集合一定被分配到了相等的数，式子就是：

$$
\sum_{a+b=N,c+d=M,a+2b=c+2d} 
{N\choose b}{M\choose d}\sum_{t=0}^{\min(b,d)} (-1)^t{b\choose t}{d\choose t}t! \frac{(c+2d-2t)!}{2^{b+d-t}}
$$

复杂度 $O(\min(N,M)^2)$，做完了。

---

## 作者：qnqfff (赞：6)

模拟赛考了，写了一整场，寄了，赛后半小时过，泵。

### 思路

考虑处理最后一行，发现填的位置对答案没有影响，考虑填一个填两个分开考虑。

1.填一个：

钦定填左下角，那么先不考虑填的那一列，就变成了一个 $(n-1)\cdot(m-1)$ 的子问题，递归处理，对于填的那一列，最多再填一个，发现任就是一个子问题，也可以递归。

2.填两个：

钦定填左下角的两个，不考虑那两列是一个 $(n-1)\cdot(m-2)$ 的子问题，对于那两列继续分讨。

2.1两列只填一个：

发现是情况1，递归处理。

2.2两列填两个：

如果重叠直接就是一整块子问题，直接递归，否则是情况2。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=1e9+7;
using namespace std;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9') p=p*10+c-'0',c=getchar();return p*flg;}
int n,m,dp[3010][3010],f[3010][3010],g[3010][3010];
int dfs(int n,int m);  
int go(int n,int m){
    if(n<=0||m<=0) return 0;if(~f[n][m]) return f[n][m];if(m==1) return f[n][m]=(n<=2?1:0);
    return f[n][m]=(dfs(n-1,m-1)+go(m,n-1))*m%mod;
}
int _go(int n,int m){
    if(n<=0||m<=0) return 0;if(~g[n][m]) return g[n][m];if(m==1) return g[n][m]=(n==2?3:(n==3?2:0));if(m==2) return g[n][m]=((dfs(n-2,m-1)+go(m,n-2))*2%mod*m%mod+dfs(n-2,m-1)*m%mod+(n<=4?(n==2?1:(n==3?3:2)):0)*2%mod)%mod;
    return g[n][m]=((dfs(n-2,m-1)+go(m,n-2))*2%mod*m%mod+dfs(n-2,m-1)*m%mod+(_go(m,n-2)+dfs(n-2,m-2))*m%mod*(m-1)%mod)%mod;
}
int dfs(int n,int m){
	if(n<=0||m<=0) return 0;if(~dp[n][m]) return dp[n][m];if(2*n<m||2*m<n) return dp[n][m]=0;if(n==1||m==1) return dp[n][m]=1;
    return dp[n][m]=((dfs(n-1,m-1)+go(m,n-1))*m%mod+(dfs(n-1,m-2)+_go(m,n-1))*(m*(m-1)/2)%mod)%mod;
}
void solve(){memset(dp,-1,sizeof(dp));memset(f,-1,sizeof(f));memset(g,-1,sizeof(g));cout<<dfs(n,m);}
signed main(){
    n=read();m=read();if(2*n<m){cout<<0;return 0;}if(n==1){cout<<1;return 0;}solve();
    return 0;
}
```

---

## 作者：oMin0 (赞：6)

感谢怪兽老师的指导，我真是唐完了。

## 分析

首先容易想到对行列建二分图，对同行同列的 $1$ 连边，则图与矩阵一一对应，矩阵合法当且仅当没有孤立点，且每个连通块的形态都是环或链。

注意到二分图上环所经过的左右部点数量一定相等，链所经过的左右部点数量至多相差 $1$，所以先考虑算出 $f_{k,i}(k=-1/0/1)$ 表示把 $i$ 个左部点、$i+k$ 个右部点连成一个连通块的方案数。这可以通过枚举左右部点的排列得出简单公式：

$$
\begin{aligned}
&f_{0,i}=(i-1)!\times i!\times\frac{1}{2}+i!\times i!\\
&f_{1,i}=i!\times (i+1)!\times \frac{1}{2}\\
&f_{-1,i}=i!\times (i-1)!\times \frac{1}{2}
\end{aligned}
$$

于是我们可以尝试简单递推。记 $ans_{i,j}$ 表示原问题在 $n=i,m=j$ 时的答案，则枚举第一行所在连通块的形态，可以得到多项式复杂度的做法：

$$ans_{i,j}=\sum\limits_{k,p} ans_{i-p,j-p-k}f_{k,p}C_{i-1,p-1}C_{j,p+k}$$

显然以上做法时间复杂度为 $O(n^3)$，需要优化。

考虑把递推拆成两个部分。注意到 $k=1$ 与 $k=-1$ 的连通块个数的差可以确定，而 $k=0$ 本身就具有 $i=j$ 的良好性质，于是记 $g_i$ 表示仅考虑 $k=0$ 的连通块时的 $ans_{i,i}$，$h_i$ 表示仅考虑 $k=1/-1$ 的连通块时的 $ans_{i,i+m-n}$，则答案即为 $\sum g_ih_{n-i}C_n^iC_m^i$，而 $g_i$ 和 $h_i$ 都可以 $O(n^2)$ 地求出：

- $g_i$ 直接采用 $ans_{i,j}$ 的递推即可，由于状态数除以了 $n$，时间复杂度 $O(n^2)$。

- $h_i$ 需要我换个角度考虑。注意到 $f_{1,i},f_{-1,i}$ 的 EGF 每一项系数都是相等的常数（$F_1(x)=\sum\limits_{i\geq 1}\frac{1}{2}x^i,F_{-1}(x)=\sum\limits_{i\geq 2}\frac{1}{2}x^i$），那么由插板法可知 $[x^p]F_1(x)^{k_1}F_2(x)^{k_2}=\frac{1}{2^{k_1+k_2}}C_{p-k_2-1}^{k_1+k_2-1}$，可以 $O(1)$ 计算。于是 $h_i=i!\times(i+m-n)!\times \sum\limits_{p} [x^i]F_1(x)^pF_{2}(x)^{p-m+n}\times\frac{1}{p!}\times\frac{1}{(p-m+n)!}$ 也可以在 $O(n^2)$ 的时间复杂度下算完（注意连通块无标号，所以式子最后要除两种连通块数量的阶乘）。

那么由此可见总时间复杂度变为 $O(n^2)$，可以通过本题。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define mod 1000000007

int ksm(int x,int k) {int na=1; for(int i=1;i<=k;i<<=1) {if(i&k) na=na*x%mod; x=x*x%mod;} return na;}

int n,m,f[3005],jc[3005],ny[3005],inv[3005],cfv[3005];

void init()
{
	jc[0]=1; for(int i=1;i<=3000;i++) jc[i]=jc[i-1]*i%mod;
	ny[3000]=ksm(jc[3000],mod-2); for(int i=2999;i>=0;i--) ny[i]=ny[i+1]*(i+1)%mod;
	for(int i=1;i<=3000;i++) inv[i]=jc[i-1]*ny[i]%mod;
	cfv[0]=1; for(int i=1;i<=3000;i++) cfv[i]=cfv[i-1]*inv[2]%mod;
}
int C(int x,int y) {if(x==y) return 1; return jc[x]*ny[y]%mod*ny[x-y]%mod;}
int Calc(int x,int y) {return C(x+y-1,y-1);}

int dp1[3005],fg[3005];

signed main()
{
	cin>>n>>m; init(); if(n>m) swap(n,m);
	f[1]=1; 
	for(int i=2;i<=n;i++) f[i]=(i+inv[2])%mod;
	for(int i=0;i<=n;i++)
	{
		int cg=m-n+i,ch=i;
		for(int j=cg+2*ch;j<=n;j++)
		{
			fg[j]=(fg[j]+cfv[cg+ch]*Calc(j-cg-2*ch,cg+ch)%mod*C(cg+ch,cg)%mod*ny[cg+ch]%mod)%mod;
		}
	}
	for(int i=0;i<=n;i++) fg[i]=fg[i]*jc[i]%mod*jc[i+m-n]%mod;
	dp1[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			dp1[i]=(dp1[i]+dp1[i-j]*f[j])%mod;
		}
		dp1[i]=dp1[i]*inv[i]%mod;
	}
	for(int i=0;i<=n;i++) dp1[i]=dp1[i]*jc[i]%mod*jc[i]%mod;
	int ans=0;
	for(int i=0;i<=n;i++)
	{
		ans=(ans+dp1[i]*fg[n-i]%mod*C(n,i)%mod*C(m,i)%mod)%mod;
	}
	cout<<ans<<endl;
}
```

---

## 作者：liyixin0514 (赞：4)

# [P10681 [COTS 2024] 奇偶矩阵 Tablica](https://www.luogu.com.cn/problem/P10681)

[可能不一定会更好的阅读体验](https://www.cnblogs.com/wingheart/p/18660665)

## 题意

有一个 $n \times m$ 的 $01$ 矩阵，问有多少种填 $01$ 的方式，满足同一行、列恰好有 $1$ 或 $2$ 个 $1$。

$n,m \le 3000$。

## 思路

首先一个显然的 $O(nm^2)$ 做法：

设 $f_{i,s0,s1}$ 表示考虑到第 $i$ 行，目前有 $s0$ 列有 $0$ 个 $1$，有 $s1$ 列有 $1$ 个 $1$，的方案数。

转移分 $5$ 种，讨论第 $i+1$ 行填几个 $1$，以及在 $s0$ 还是 $s1$ 那里选 $1$。

就是酱子：

```cpp
int w = f[i][s0][s1];
if (s0)
	_add(f[i + 1][s0 - 1][s1 + 1], mul(s0, w)),
	_add(f[i + 1][s0 - 1][s1], mul(w, mul(s0, s1)));
if (s1)
	_add(f[i + 1][s0][s1 - 1], mul(s1, w));
if (s0 >= 2)
	_add(f[i + 1][s0 - 2][s1 + 2], mul(w, 1ll * s0 * (s0 - 1) / 2 % mod));
if (s1 >= 2)
	_add(f[i + 1][s0][s1 - 2], mul(w, 1ll * s1 * (s1 - 1) / 2 % mod));
```

------

好像 DP 状态不好再减了。

所以考虑不要一行行转移了，直接组合计数。

> 学习了 yyyyxh 大佬的题解。

枚举有 $x_1$ 行恰好有 $1$ 个 $1$，那么有 $x_2 = n-x_1$ 恰好有 $2$ 个 $1$。

那么所有列加起来 $1$ 的个数 $y_1+2y_2 = x_1+2x_2$，所以可以直接求出 $y_1,y_2$。

问题就是有 $m$ 种球，其中 $y_1$ 种各有 $1$ 个，$y_2$ 种各有 $2$ 个。有 $n$ 个桶，其中 $x_1$ 个容量为 $1$，$x_2$ 个容量为 $2$。问有多少种放球方式，满足每个桶都放满，且一个桶里不能放两个同一种球。

桶和球的种类都是有编号的，但是编号不影响计数，所以答案乘上组合数 $\binom{n}{x_1} \binom{m}{y_1}$ 即可。

一个错误答案是 $(y_1+2y_2)!$。

有两个难处理的问题：

1. 两个同种球是无序的，容量为 $2$ 的桶里面两个球也是无序的。
2. 一个桶不能放两个同种球。

情况 $1$ 我们就对答案乘上 $\frac{1}{2^{x_2+y_2}}$。

情况 $2$ 考虑容斥。外层只有枚举的 $O(\min(n,m))$ 复杂度，所以放心容斥。

具体地，就是随便放 $-$ 钦定一个容量为 $2$ 的桶放两个一样的球 $+$ 钦定两个容量为 $2$ 的桶放两个一样的球……

钦定的方案数就是除去那几个行和列，剩下随便放的方案数。

即

$$\sum_{k=0}^{\min(x_2,y_2)} \binom{x_2}{k} \binom{y_2}{k} k! (-1)^k \frac{(y_1+2y_2-2k)!}{2^{x_2+y_2-2k}}$$

$k!$ 是计算每个钦定的桶对应什么种类的球。

这对吗？实际上是错的，如果有两个同种球被放在一个桶里的情况，直接算排列只是多算了 $1$ 次，而你以为有 $3$ 次都是多算的。所以当你钦定这两个同种球必须在一个桶里的时候，需要把多减的加回来。就是说容斥要带系数 $2^k$，体现在分母那里变成 $2^{x_2+y_2-k}$。

总的式子就是：

$$\sum_{x_1+x_2=n, y_1+y_2=m, x_1+2x_2=y_1+2y_2} \binom{n}{x_1} \binom{m}{y_1} \sum_{k=0}^{\min(x_2,y_2)} \binom{x_2}{k} \binom{y_2}{k} k! (-1)^k \frac{(y_1+2y_2-2k)!}{2^{x_2+y_2-k}}$$

> $\binom{x_2}{k} \binom{y_2}{k} k! (-1)^k \frac{(y_1+2y_2-2k)!}{2^{x_2+y_2-k}}$ 算出来是小数，很反直觉。大概是容斥容的。

复杂度 $O(\min(n,m)^2)$。

## code

> 好难。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace hesitate {
	constexpr int N=6e3+7,Max=6e3,mod=1e9+7;
	int add(int a,int b) { return a+b>=mod ? a+b-mod : a+b; }
	void _add(int &a,int b) { a=add(a,b); }
	int mul(int a,int b) { return 1ll*a*b%mod; }
	void _mul(int &a,int b) { a=mul(a,b); }
	int ksm(int a,int b=mod-2) {
		int s=1;
		while(b) {
			if(b&1) _mul(s,a);
			_mul(a,a);
			b>>=1;
		}
		return s;
	}
	int fac[N],ifac[N],mi[N],imi[N];
	void init() {
		fac[0]=mi[0]=1;
		rep(i,1,Max) fac[i]=mul(fac[i-1],i);
		rep(i,1,Max) mi[i]=add(mi[i-1],mi[i-1]);
		ifac[Max]=ksm(fac[Max]);
		per(i,Max-1,0) ifac[i]=mul(ifac[i+1],i+1);
		imi[Max]=ksm(mi[Max]);
		per(i,(Max)-1,0) imi[i]=add(imi[i+1],imi[i+1]);
	}
	int c(int n,int m) { return mul(fac[n],mul(ifac[m],ifac[n-m])); }
	int n,m;
	int ans;
	void main() {
		init();
		sf("%d%d",&n,&m);
		rep(x1,0,n) {
			int x2=n-x1,y2=x1+(x2<<1)-m,y1=m-y2;
			if(y2<0 || y1<0) continue;
			int s=0;
			rep(k,0,min(x2,y2)) {
				int sum= (k&1) ? mod-1 : 1;
				_mul(sum,mul(mul(c(x2,k),c(y2,k)),fac[k]));
				_mul(sum,mul(fac[y1+(y2<<1)-(k<<1)],imi[x2+y2-k]));
				_add(s,sum);
			}
			_mul(s,mul(c(n,x1),c(m,y1)));
			_add(ans,s);
		}
		pf("%d\n",ans);
	}
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
	hesitate :: main();
}
```

---

## 作者：CatFromMars (赞：3)

声明：我是一个计数小萌新，这道题我不会做，实在是太菜了。做法来源于巨佬 [yyyxh 的题解](https://www.luogu.com.cn/article/hypndkiz)。他的题解写的非常之好，连我这种小蒟蒻都能看得懂 qwq。但是个人认为里面还是有一点不太明确的地方，这里写一下我的理解，更多是一种补充吧。~~如有雷同，我抄他的。~~

---
每行每列的 1 数量和均为 1/2。注意到如果得到一个合法矩形，我们任意交换两行两列矩形显然仍然合法。所以可以考虑找到特殊的有 2 个 1 的行或者列以此为基准计数。我们设有 $a$ 行有 $2$ 个 1，$b$ 行有 $1$ 个 1，$c$ 列有 $2$ 个 1，$d$ 列有 $1$ 个 1，那么就有 $a + b = n, c + d = m, 2a + b = 2c + d$。显然，已知其中任何一个未知数，都能把剩下三个解出来。

所以考虑枚举 $c$，此时 $a, b, d$ 也就确定了。考虑在此情况下合法的矩形数量。

现在我们对问题进行进一步抽象：假设 1 的位置是 $(2c + d)$ 个二元组 $(x_1, y_1), (x_2, y_2), \dots, (x_{2c + d}, y_{2c+d})$。那么要求构造满足的条件实际上是：

1. $y_1 \sim y_{2c+d}$ 形成的并集大小为 $m$。
2. $y$ 中有 $c$ 个数出现了 $2$ 次。
3. $x_1 \sim x_{2c+d}$ 形成的并集大小为 $n$。
4. $x$ 中有 $a$ 个数出现了 $2$ 次。

因为对 $c$ 进行了枚举，所以可以想到对这样一个问题转化：前两个条件先在 $m$ 列中选择 $c$ 个看成两个列，方案数有 $m\choose c$ 种。类似的，将 $n$ 行中选择 $a$ 个看成两行，方案数有 $n\choose a$ 种。让新的 $(m+c)$ 列按照顺序排开，对行数中的 $(n + a)$ 个行做全排列，从而和上面的列匹配。这样产生的方案数是 $\dfrac{(n+a)!}{2^a} = \dfrac{(2c + d)!}{2^a}$ 个。注意除以 $2^a$ 是因为是可重集的全排列，而大小为 $2$ 的数有 $a$ 个。也就是说答案就是 ${n\choose c}{m\choose a}\frac{(2c+d)!}{2^a}$。

但是这是错误的，错误的原因是因为：
1. 产生了不正确的计数：这样可能会出现 $x_i = x_j, y_i = y_j, i\not= j$ 的情况。如何解决？容易容斥。枚举有 $t$ 个这样的坐标，如果我们忽略一个这样的坐标，那么方案数应当有 ${a\choose t}{c \choose t}\frac{t!{(2c + d - 2t)!}}{2^{a - t}}$。容斥系数为 $(-1)^t$。上面讨论的情况不过是 $t = 0$ 的情况。

2. 产生了重复计数，可能会出现 $(x_1, y_1), (x_2, y_1)$ 和 $(x_2, y_1), (x_1, y_1)$ 被认成两种方案。显然只需要除以 $2^c$ 即可。

综上答案应该为 

$\sum\limits_{a, b, c, d}{n\choose c}{m\choose a}\sum\limits_{t = 0}^{\min\{a, c\}}(-1)^t{a\choose t}{c \choose t}\frac{t!{(2c + d - 2t)!}}{2^{a - t}\times 2^{c}}$。

代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 6000;
const ll Mod = 1e9 + 7;
ll C[N + 10][N + 10], qp2[N + 10], fac[N + 10], qi2[N + 10];
ll qpow(ll n, ll m) {
	ll res = 1;
	while(m) {
		if(m & 1) res = res * n % Mod;
		n = n * n % Mod, m >>= 1;
	}
	return res;
}
void prep() {
	C[0][0] = 1;
	C[1][0] = C[1][1] = 1;
	for(int i = 2; i <= N; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
	}
	
	qi2[0] = fac[0] = qp2[0] = 1;
	for(int i = 1; i <= N; i++) {
		qp2[i] = qp2[i - 1] * 2 % Mod;
		qi2[i] = qpow(qp2[i], Mod - 2); 
		fac[i] = fac[i - 1] * i % Mod;
	}
}
int n, m;
int main() {
	prep();
	cin >> n >> m;	
	
	ll sum = 0, ans = 0;
	for(int c = 0; c <= m; c++) {
		int d = m - c, a = m - n + c, b = 2 * n - c - m;
		if(a < 0 || b < 0) continue;
		
		sum = 0;
		for(int t = 0; t <= min(a, c); t++)
			sum = ((sum +
			(C[a][t] * C[c][t] % Mod) % Mod * fac[t] % Mod *
			((t % 2 == 1) ? (-1) : (1)) % Mod
			* (fac[2 * c + d - 2 * t] * qi2[a + c - t] % Mod) % Mod) % Mod + Mod) % Mod;
		sum = sum * C[n][a] % Mod * C[m][c] % Mod;
//		cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << sum << endl;
		ans = (ans + sum) % Mod;
	}
	cout << ans << endl;
}
```

---

## 作者：Purslane (赞：3)

# Solution

被 Reunite 拉过来看的一道题。

考虑枚举有 $k$ 个行和为 $2$，则有 $n+k-m$ 个列和为 $2$。

考虑一共有 $n+k$ 和盒子与 $n+k$ 个球，分别表示行和列，要把这些球放进盒子里面，显然有 $(n+k)!$ 种方法。

但是显然不能让同一行对应的两个盒子装同一列对应的两个球，因此需要对这一部分容斥，单次容斥复杂度为 $O(n)$。

容斥结束之后，考虑同一行和同一列对应的球与盒子互不区分，因此要乘上 $(\dfrac{1}{2})^{n-m+2k}$。

复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6000+10,MOD=1e9+7,I2=(MOD+1)/2;
int n,m,t=6000,C[MAXN][MAXN],pw[MAXN],pw2[MAXN],frac[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,0,t) {
		C[i][0]=1;
		ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
	}
	pw[0]=1,pw2[0]=1,frac[0]=1;
	ffor(i,1,t) frac[i]=frac[i-1]*i%MOD,pw2[i]=pw2[i-1]*2%MOD,pw[i]=pw[i-1]*I2%MOD;
	int ans=0;
	ffor(i,0,n) {
		int ch=i,cl=n+i-m,mul=0;
		if(cl<0||cl>m) continue ;
		ffor(j,0,min(ch,cl)) {
			int D=1-2*(j%2);
			mul=(mul+D*C[ch][j]*C[cl][j]%MOD*frac[n+i-2*j]%MOD*frac[j]%MOD*pw2[j])%MOD;
		}
		mul=mul*pw[ch+cl]%MOD;
		ans=(ans+mul*C[n][ch]%MOD*C[m][cl]%MOD)%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Re_Star (赞：2)

[题面](https://www.luogu.com.cn/problem/P10681)

[更好的阅读体验](https://www.cnblogs.com/Re-Star/p/18828939)

首先枚举行与列和为 $1$ 或 $2$ 的个数，我们设有 $a$ 行和为 $1$，$b$ 行和为 $2$，$c$ 列和为 $1$，$d$ 列和为 $2$。显然它们满足下列关系：
$$
\begin{aligned} 
\begin{equation}
    \begin{cases}
    a+b=n\\
    c+d=m\\
    a+2b=c+2d\\
    \end{cases}
\end{equation}
\end{aligned}
$$
所以只要有一个量确定了，其他三个也就定下来了。现在考虑对于固定的 $a$，$b$，$c$，$d$，我们可以将问题转化一下。这个问题相当于我们现在有 $m$ 种颜色的小球，其中 $c$ 种颜色有一个，其余 $d$ 种有两个，我们现在需要把它们放入 $n$ 个有标号集合中，其中有 $a$ 个集合放一个球，其余 $b$ 个集合放两个球，同一集合不能放入两个同色球。

接下来我们考虑把这 $m$ 个小球按不同方式排列，对于每种方式我们都钦定前 $a$ 个球每个球单独放入一个集合中，后面的我们将每相邻两个球放入同一个集合，但是这样可能会将两个同色球放入同一集合，所以我们对小球构成的序列还需要有限制，即后面 $2b$ 的位置上每相邻两球颜色不同，也就是有 $b$ 对小球颜色不能相同。这个限制很难描述，所以我们考虑容斥容斥掉了集合内出现同色球的方案。现在这 $b$ 个集合每个集合交换两元素的位置其实一种方案但被统计了 $2$ 次，所以每种方案都被重复统计了 $2^b$ 次，最后还要乘 $2^{-b}$。

最后整理一下上面的每一步，就可以得到式子：
$$
\begin{aligned} 
ans=\sum\limits_{a+b=n,c+d=m,a+2b=c+2d\\}{n\choose a}{m\choose c}\frac{\sum_{t=0}^{min(b,d)}(-1)^t{b\choose t}{d\choose t}t!\frac{(c+2d-2t)!}{2^{d-t}}}{2^b}
\end{aligned}
$$

这个式子看着很长，但其实比较简单，建议自己先理解一下。拆开来讲的话就是，在 $n$ 行中选 $a$ 行和为 $1$，在 $m$ 列中选 $c$ 列和为 $1$。后面要满足 $b$
组连续两个小球不同色，我们枚举有 $t$ 组是同色的，再在 $b$ 组里选 $t$ 组，$d$ 种颜色里选 $t$ 种，这 $t$ 组的顺序可以随意交换，其他 $c+2d-2t$ 个小球位置任意，最后再乘上 $2^{-b}$ 就可以了。

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7,N=3e3+5;
ll fac[N<<1],invq[N<<1],n,m,ans,C[N][N];
ll qp(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) (res*=x)%=mod;
		(x*=x)%=mod,y>>=1;
	}
	return res;
}
inline ll rd()
{
    char c;int f=1;
    while(!isdigit(c=getchar()))if(c=='-') f=-1;
    ll x=(c^48);
    while(isdigit(c=getchar()))x=x*10+(c^48);
    return x*f;
}
inline ll h(int i){return (i&1)?(mod-1):1;}
inline void add(ll &x,ll y){x+=y;if(x>=mod) x-=mod;}
inline ll solve(int a,int b,int c,int d)
{
	ll res=0;
	for(int t=0;t<=d&&t<=b;t++) add(res,h(t)*C[b][t]%mod*C[d][t]%mod*fac[t]%mod*fac[c+2*d-2*t]%mod*invq[d+b-t]%mod);
	return res;
}
int main()
{
	n=rd(),m=rd(),fac[0]=invq[0]=1;ll s=2*max(n,m),i2=qp(2,mod-2);
	for(int i=1;i<=s;i++) fac[i]=fac[i-1]*i%mod,invq[i]=invq[i-1]*i2%mod;
	for(int i=0;i<=max(n,m);i++)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int b=0;b<=n;b++)
	{
		int a=n-b,cnt=b*2+a;
		if(cnt>=m&&cnt<=2*m) add(ans,C[n][b]*C[m][cnt-m]%mod*solve(a,b,2*m-cnt,cnt-m)%mod);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：BreakPlus (赞：1)

感觉这个题虽然简单，但是还是很容易想半天想不出来的。

----

转换一下问题，$A_{i,j}$ 为 $1$ 视为 $i$ 向 $n+j$ 连了一条边，形成一个 $n+m$ 个点的图。

然后这是一个二部图，只会有偶环，没有重边，且每个点的度数为 $1$ 或 $2$。

由经典结论，结合二部图的性质，度数为 $1$ 或 $2$ 的简单图一定由以下四种结构组成：

+ 一个偶环；
+ 一个长度为偶数的链；
+ 一个长度为奇数的链，且编号 $\le n$ 的点多一个；
+ 一个长度为奇数的链，且编号 $> n$ 的点多一个。

对于前两种和后两种分开计数，然后卷起来即可。

具体地，令 $f_i$ 表示有 $i$ 个左部点（编号 $\le n$），$i$ 个右部点（编号 $>n$），由前两种结构组成的图的方案数。容易 dp 预处理出 $f$。

然后枚举 $i$，再枚举第三种结构 $s$，可以推算出第四种结构的数量 $t$。这个系数是容易计算的。

```cpp
ll f[3005], dp[3005][3005], pw[3005]; ll n, m;

void procedure(){
	n=read(), m=read();
	pw[0]=1, pw[1]=iv2;
	for(ll i=2;i<=3000;i++) pw[i]=pw[i-1]*pw[1]%mod;
	f[0]=1;
	for(ll i=1;i<=min(n,m);i++){
		for(ll j=1;j<=i;j++){
			ll coef = perm(i-1,j-1)*perm(i,j)%mod;
			if(j>1) coef=coef*iv2%mod;
			else coef=0;
			(f[i] += f[i-j] * coef) %= mod;

			coef = perm(i-1,j-1)*perm(i,j)%mod*j%mod;
			(f[i] += f[i-j] * coef) %= mod;
		}
	}
	ll ans=0;
	for(ll i=0;i<=min(n,m);i++){
		ll coef = f[i]*binom(n,i)%mod*binom(m,i)%mod;
		ll p=n-i, q=m-i;

		for(ll s=0;s<=p;s++){
			// s-t = p-q
			ll t=s-p+q;
			if(t>q || t<0) continue;
			ll r=p-s, ok;

			if(!r && !s && !t) ok = 1;
			else ok = binom(p,s)*binom(q,t)%mod*binom(r-1,s+t-1)%mod*fac[r]%mod*fac[r]%mod*pw[s+t]%mod;
			ans=(ans+ok*coef)%mod;
		}
	}
	printf("%lld\n", ans);
}
```

---

## 作者：吾爱CC (赞：1)

萌萌题。

考虑行向列连边，相当于规定左边有 $n$ 个点，右边有 $m$ 个点，求满足无重边，且每个点度数在 $[1,2]$ 的方案数。

枚举左边有 $j$ 个二度点，相当于将 $n+j$ 个球分到 $m$ 个盒子里，每个盒子里有 $1/2$ 个球。设 $g_{n,m}$ 为总共 $n$ 个球放到 $m$ 个盒子里的方案数，有 
$$g_{n,m}=n\times g_{n-1,m-1}+\frac{n(n-1)}{2}\times g_{n-2,m-1}$$

那么贡献为 $\frac{g_{n+j,m}}{2^j}$，因为同一左部点代表的球本质相同。

但是这样算可能有重边，考虑枚举重边个数 $i$，那么答案为:

$$\sum_{i=0}^n\binom{n}{i}\binom{m}{i}i!(-1)^i\sum_{j=0}^{n-i}\frac{1}{2^{j+i}}\binom{n-i}{j}g_{n-i+j,m}$$

复杂度 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read(){
    char ch=getchar();
    while(!isdigit(ch) && ch!='-') ch=getchar();
    int x=0,ff=1; if(ch=='-') ff=-1,ch=getchar();
    while(isdigit(ch)) x=(x<<3) + (x<<1) + (ch^48),ch=getchar();
    return x*ff;
}
const int N=3e3+5,P=1e9+7,inv2=(P+1)/2;
int n,m,g[N*2][N],C[N][N],pw[N],pw2[N];
inline int F(int n,int m){ int s=0;
    for(int i=0;i<=n;i++) s=(s+1ll*C[n][i]*pw2[i]%P*g[n+i][m])%P;
    return s;
}
int main(){
    pw[0]=pw2[0]=1; for(int i=1;i<N;i++) pw[i]=1ll*pw[i-1]*i%P,pw2[i]=1ll*pw2[i-1]*inv2%P;
    for(int i=0;i<N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
    }
    n=read(); m=read(); g[0][0]=1; int ans=0;
    for(int i=1;i<=2*n;i++)
        for(int j=1;j<=m;j++){
            int &s=g[i][j]; s=1ll*g[i-1][j-1]*i%P;
            if(i>1) s=(s+1ll*g[i-2][j-1]*(i*(i-1)/2))%P;
        }
    for(int i=0;i<=n && i<=m;i++) ans=(ans+1ll*C[n][i]*C[m][i]%P*pw[i]%P*pw2[i]%P*((i&1)?-1:1)*F(n-i,m-i))%P;
    ans=(ans%P+P)%P; printf("%d\n",ans);
    return 0;
}
```

---

## 作者：binbin_200811 (赞：1)

# [P10681 COTS/CETS 2024 奇偶矩阵 Tablica](https://www.luogu.com.cn/problem/P10681)

来自 [qnqfff](https://www.luogu.com.cn/user/304534) 大佬的梦幻 dp。

## 约定

二元组 $(n,m)$ 表示一个 $n$ 行 $m$ 列的矩形。

不添加说明的子问题，限制与题面一致。

## 思路

先考虑放最后一行，发现你填的位置经过变换后可以得到其他的结果，也就是说只要乘上变换的方案数就可以任选位置放。

那么考虑填一个还是两个。

1.填一个

填在左下角，不考虑填的那一列（填的列不再填）变成了 $(n-1,m-1)$ 的子问题；考虑那一列，变成了一个 $(m,n-1)$ 其中有一行填一个的子问题。

2.填两个

填在左下角两个：

* 2.1 不考虑填的列，是一个 $(n-1,m-2)$ 的子问题。
* 2.2 考虑填的两列，是一个 $(m,n-1)$ 其中两行有一行（不填状况已经考虑，这里必填一个可以更多）必填一个的子问题。

3.一行填一个

填左下角，是一个 $(n-1,m-1)$ 的子问题和 $(m,n-1)$ 其中一行填一个的子问题（该行填完后对于其他列来说又只能填一个）。

4.两行必填一个（有一行可填可不填）

* 4.1 同一列填一个 $(n-2,m-1)$ 的子问题和 $(m,n-2)$ 其中一行填一个的子问题。
* 4.2 同一列填两个 $(n-2,m-1)$ 的子问题。
* 4.3 任选两列列填两个 $(n-2,m-2)$ 的子问题和 $(m,n-2)$ 其中两行必填一个的子问题。 

在大力分讨之后，发现所有情况都可以分为子问题，而子问题合并的系数也易于得出，具体系数参考代码或读者自行思考。

使用记忆化搜索实现，较为容易。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const ll mod=1e9+7;
// const ll mod=1211221111;
const int maxn=3005;

int n,m;

ll dp[maxn][maxn],f[maxn][maxn],g[maxn][maxn];

inline ll dfs(int n,int m);
int go(int n,int m){//求 (n,m) 中某一行必填一个的方案数
    if(n<=0||m<=0) return 0;
    if(~f[n][m]) return f[n][m];
    if(m==1)
    {
        if(n<=2) return f[n][m]=1;
        return f[n][m]=0;
    }
    return f[n][m]=(dfs(n-1,m-1)+go(m,n-1))*m%mod;
}
inline ll _go(int n,int m)//求 (n,m) 中某两行有一行必填一个的方案数
{
    if(n<=0||m<=0) return 0;
    if(~g[n][m]) return g[n][m];
    if(m==1)
    {
        if(n==2) return g[n][m]=3;
        else if(n==3) return g[n][m]=2;
        return g[n][m]=0;
    }
    if(m==2)
    {
        g[n][m]=((dfs(n-2,m-1)+go(m,n-2))*2%mod*m%mod/*同一列填一个*/+dfs(n-2,m-1)*m%mod)%mod;/*同一列填一个*/
        if(n<=4)//直接算两列的贡献
        {
            if(n==2) g[n][m]+=2;
            else if(n==3) g[n][m]+=6;
            else g[n][m]+=4;
        }
        return g[n][m]=0;
    }
    return g[n][m]=(((dfs(n-2,m-1)+go(m,n-2))*2%mod*m%mod/*同一列填一个*/+dfs(n-2,m-1)*m%mod/*同一列填两个*/)+(_go(m,n-2)+dfs(n-2,m-2))*m%mod*(m-1)%mod/*任选两列列填两个（有序）*/)%mod;
}
inline ll dfs(int n,int m)//求子问题(n,m)的方案数
{
    if(n<=0||m<=0) return 0;
    if(~dp[n][m]) return dp[n][m];
    if(2*n<m||2*m<n) return dp[n][m]=0;
    if(n==1||m==1) return dp[n][m]=1;
    return dp[n][m]=((dfs(n-1,m-1)+go(m,n-1))*m%mod/*填一个*/+(dfs(n-1,m-2)+_go(m,n-1))*(m*(m-1)/2)%mod/*填两个*/)%mod;
}
inline void solve()
{
    memset(dp,-1,sizeof(dp));memset(f,-1,sizeof(f));memset(g,-1,sizeof(g));
    printf("%lld",dfs(n,m));
}

int main()
{
    scanf("%d%d",&n,&m);
    if(2*n<m) printf("0"),exit(0);
    if(n==1) printf("1"),exit(0);
    solve();
}
```

---

