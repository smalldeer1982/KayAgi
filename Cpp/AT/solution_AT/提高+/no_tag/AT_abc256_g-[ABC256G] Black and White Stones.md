# [ABC256G] Black and White Stones

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc256/tasks/abc256_g

一辺の長さが整数 $ D $ の正 $ N $ 角形があります。

頂点から始めて、周上に距離 $ 1 $ ごとに黒い石か白い石を置きます。これにより、$ N $ 角形の各辺上に $ D+1 $ 個、全体で $ ND $ 個の石が置かれます。

石の置き方のうち、各辺上にある白い石の個数が等しくなるようなものは何通りありますか？ $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 10^{12} $
- $ 1\ \leq\ D\ \leq\ 10^4 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

下図の $ 10 $ 通りがあります。 !\[図\](https://img.atcoder.jp/abc256/ba2bebe9d374f281e2b44e36231abae2.png)

### Sample Explanation 2

$ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
3 2```

### 输出

```
10```

## 样例 #2

### 输入

```
299792458 3141```

### 输出

```
138897974```

# 题解

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc256_g)

## 思路

先考虑一个暴力 $\rm DP$，设 $f_{i,j,0/1,0/1}$ 表示前 $i$ 条边，每条边上有 $j$ 个白点，第一条边的最左边的顶点的颜色是 $0/1$，第 $i$ 条边的最右边的顶点的颜色是 $0/1$。

为了方便起见，下文中提到的 $d$ 均为输入的 $d$ 加上 $1$ 之后的结果。

简单地写一个转移，以 $f_{i,j,0,0}$ 为例：

$$f_{i,j,0,0}=f_{i-1,j,0,1} \times \binom{d-2}{j-1}+f_{i-1,j,0,0} \times \binom{d-2}{j-2}$$

最后的合并答案是简单的，枚举最后一条边两个端点的状态即可。

其余状态的转移类似，不再赘述，不难发现第二维和第三维都是不变的，所以我们可以枚举第二维和第三维，然后把状态简化到 $f_{i,0/1}$，表示前 $i$ 条边，第 $i$ 条边的最右边的顶点的颜色是 $0/1$。

现在的转移如下：

$$f_{i,0}=f_{i-1,1} \times \binom{d-2}{j-1}+f_{i-1,0} \times \binom{d-2}{j-2}$$

发现两个组合数是不变的，不妨分别设为 $A$ 和 $B$，则 $f_{i,0}=f_{i-1,1} \times A+f_{i-1,0} \times B$。

类似的，我们不妨设 $f_{i,1}$ 的两个组合数为 $C$ 和 $D$，则 $f_{i,1}=f_{i-1,1} \times C+f_{i-1,0} \times D$。

很容易把它写成矩阵的形式：

$$
\begin{bmatrix}
A & B \\
C & D
\end{bmatrix}

\times

\begin{bmatrix}

f_{i-1,1} \\

f_{i-1,0}

\end{bmatrix}

=

\begin{bmatrix}

f_{i,1} \\

f_{i,0}

\end{bmatrix}
$$

然后矩阵快速幂就好了，时间复杂度 $\mathcal O(d \log n)$

## 代码

[Link](https://atcoder.jp/contests/abc256/submissions/39787125)

---

## 作者：Super_Cube (赞：1)

# Solution

设 $dp_{i,0/1}$ 表示第 $i$ 条边的末尾点是白色/黑色的方案数。注意到 $d$ 范围不大，考虑枚举每条边的白点个数为 $j$，转移为：

$$
dp_{i,0}=dp_{i-1,0}\binom{d-1}{j-2}+dp_{i-1,1}\binom{d-1}{j-1}
\\
dp_{i,1}=dp_{i-1,0}\binom{d-1}{j-1}+dp_{i-1,1}\binom{d-1}{j}
$$

除去开头点与末尾点还剩下 $d-1$ 个点，它们的颜色方案数取决于每条边白点总个数和开头点与末尾点的白色个数。

由于图形成环状，这时候初始化成了麻烦事。钦定第一个点为黑色，即 $dp_{0,1}=1$，这种情况答案为 $dp_{n,1}$。钦定第一个点为白色的情况同理。最终的总方案就是两者相加。

注意到转移式异常简洁且系数是定值，改写其为矩阵形式。

$$
\begin{bmatrix}
dp_{i-1,0}&dp_{i-1,1}
\end{bmatrix}
\times
\begin{bmatrix}
\displaystyle\binom{d-1}{j-2}&\displaystyle\binom{d-1}{j-1}\\
\displaystyle\binom{d-1}{j-1}&\displaystyle\binom{d-1}{j}
\end{bmatrix}
=
\begin{bmatrix}
dp_{i,0}&dp_{i,1}
\end{bmatrix}
$$

矩阵快速幂优化即可。

时间复杂度：$O(d\log n)$。

---

## 作者：y3kkc (赞：1)

## 反思  
很显然的计数 dp 题。  
赛时没有打暴力，虽然知道大概要把 $n$ 转化为对数，但一股脑地想正解就没想出来。  
所以遇到计数 dp 题以后暴力一定要先打。   
## 分析
那就让我们从暴力入手。  
由于是暴力，~~所以我们想怎么来就怎么来~~但并不是我们想怎么来就怎来。  
首先，由与对每个点进行决策比较困难，我们可以从边入手。  
于是乎我们不得不设一个 $i$，代表当前处理到了第 $i$ 条边。  
白石子的数量不确定，不方便，我们可以枚举 $j$ 表示每条边有 $j$ 个白石子。  
处于顶点的石子比较难处理，也设入状态中，可以用 0/1 表示当前两边端点的颜色。  
于是设 $dp_{i,j,0/1,0/1}$ 为处理了前 $i$ 条边，第 1 条边左端点颜色为 0/1，第 $i$ 条边右端点为 0/1 的数量。  
观察到 $j$ 是一个不变，我们可以在最外层循环枚举 $j$。  
从而把 $j$ 去掉变为 $dp_{i,0/1,0/1}$。  
当我们从 $i-1$ 转移到 $i$ 时，显然我们可以从 $i-1$ 的状态得到第 $i$ 条边的左端情况（第 $i-1$ 条边的右端点即为第 $i$ 条边的左端点），同时获取到第 $i$ 条边的右端点情况。  
于是我们可以进行少补，进而求出补全 $j$ 个的方案数。  
至此，我们就可以敲出暴力了。  
让我们整理一手。  
组合数由于都以 $d-1$ 为底，这里就用 $c_i$ 简化代替 $C_{d-1}^i$。  
边界：$dp_{0,0,0}=1$，$dp_{0,1,1}=1$  
状态转移方程：
$$dp_{i,0,0} = dp_{i-1,0,0} \times c_{j-2} + dp_{i-1,0,1} \times c_{j-1}$$
$$dp_{i,0,1} = dp_{i-1,0,0} \times c_{j-1} + dp_{i-1,0,1} \times c_j$$
$$dp_{i,1,0} = dp_{i-1,1,0} \times c_{j-2} + dp_{i-1,1,1} \times c_{j-1}$$
$$dp_{i,1,1} = dp_{i-1,1,0} \times c_{j-1} + dp_{i-1,1,1} \times c_j$$  
答案贡献：$dp_{n,0,0}$，$dp_{n,1,1}$  
观察到 $j$ 不变时各组合数也会不变。   
即转移的系数不变。  
所以这是什么？**矩阵快速幂啊！**  
于是，我们设状态矩阵为： 
$$\begin{bmatrix}
  dp_{i,0,0}&dp_{i,0,1} \\
  dp_{i,1,0}&dp_{i,1,1}
\end{bmatrix}$$  
再构造矩阵：
$$\begin{bmatrix}
  c_{j-2}&c_{j-1} \\
  c_{j-1}&c_j
\end{bmatrix}$$  
利用矩阵快速幂进行求解。  
时间复杂度 $O(d\log(n))$。  
~~矩阵太小了，就当他是个常数吧。~~
## 代码  
```cpp  
#include <cstdio>
#include <cstring>
#define int long long
namespace Faster {
//char buf[1 << 23], *p1 = buf, *p2 = buf;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
    int num = 0, sgn = 1;
    char ch = getchar();
    for (; ch < 48 || ch > 57; ch = getchar())
        if (ch == '-')
            sgn = -1;
    for (; ch >= 48 && ch <= 57; ch = getchar()) num = (num << 3) + (num << 1) + (ch & 15);
    return sgn * num;
}
inline void write(int num) {
    static int sta[39], top = 0;
    if (num < 0)
        putchar('-'), num *= -1;
    do
        sta[++top] = num % 10, num /= 10;
    while (num);
    while (top) putchar(sta[top--] | 48);
    return;
}
} using namespace Faster;
const int mod = 998244353;
const int N = 1e4 + 9;
int n, d, ans;
int fac[N], fm[N];
int dp[N][2][2];
struct mat {
	int a[2][2];
	mat() {
		memset(a, 0, sizeof a);
	}
	int* operator[](int x) { return a[x]; }
	inline mat operator*(mat b) {
		mat c;
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) c[i][j] = (a[i][0] * b[0][j] % mod + a[i][1] * b[1][j] % mod) % mod;
		return c;
	}
	inline friend mat operator^(mat bas, int b) {
		--b;
		mat res = bas;
		for (; b; b >>= 1) {
			if (b & 1) res = res * bas;
			bas = bas * bas;
		}
		return res;
	}
};
inline int kpow(int a, int b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}
void init() {
	fac[0] = fm[0] = 1;
	for (int i = 1; i <= 10000; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		fm[i] = kpow(fac[i], mod - 2);
	}
	return;
}
inline int C(int n, int m) {
	if (n < 0 || m < 0 || n < m)
		return 0;
	return fac[n] * fm[m] % mod * fm[n - m] % mod;
}

signed main() {
	init();
	n = read(), d = read();
	for (int j = 0; j <= d + 1; ++j) {
		mat res;
		res[0][0] = 1, res[0][1] = 0;
		res[1][0] = 0, res[1][1] = 1;
		mat bas;
		bas[0][0] = C(d - 1, j - 2), bas[0][1] = C(d - 1, j - 1);
		bas[1][0] = C(d - 1, j - 1), bas[1][1] = C(d - 1, j);
		res = res * (bas ^ n);
		ans = (ans + res[0][0] + res[1][1]) % mod;
	}	
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：djh0314 (赞：1)

[洛谷](https://www.luogu.com.cn/problem/AT_abc256_g)。

## 题意

有一个 $n$ 边形，每条边上有 $d+1$ 个石子，相邻两边公用一个石子。石子有白色或者黑色。问一共有多少种方案使得所有边上的白色石子数量相同。对 998244353 取模。

$n\le 10^{12}$，$d\le 10^4$。

## 分析

首先对于环形的题目，我们可以想到一个重要技巧：**拆环成链**。我们将 $n$ 边形切换成 $n$ 条相连的边。              

很显然，我们第一个需要满足的条件即是我们的首石子与末石子颜色需要相同，其次为每条边的白色石子个数相同。

对于我们的第二个条件，我们可以枚举我们每条边的白色石子个数。

我们设计一个状态：$f_{i,0/1,0/1}$，表示在取了第 $i$ 条边后，首石子的颜色为 0/1，末石子的颜色为 0/1，（0 为黑色）。

那么我们对这个状态进行转移，令枚举的白色石子的数量为 $x$：           
$f_{i,0,0}=f_{i-1,0,1}\times C_{d-1}^{x-1}+f_{i-1,0,0}\times C_{d-1}^{x}$，      
$f_{i,0,1}=f_{i-1,0,1}\times C_{d-1}^{x-2}+f_{i-1,0,0}\times C_{d-1}^{x-1}$，        
$f_{i,1,0}=f_{i-1,1,0}\times C_{d-1}^{x}+f_{i-1,1,1}\times C_{d-1}^{x-1}$，          
$f_{i,1,1}=f_{i-1,1,0}\times C_{d-1}^{x-1}+f_{i-1,1,1}\times C_{d-1}^{x-2}$。

由此，我们就可以写出我们的暴力：
~~~cpp
dp[0][0][0]=dp[0][1][1]=1;
for(int i=1; i<=n; i++) {
	dp[i][0][0]=(dp[i-1][0][1]*C(d-1,x-1)%mod+dp[i-1][0][0]*C(d-1,x)  %mod)%mod;
	dp[i][0][1]=(dp[i-1][0][1]*C(d-1,x-2)%mod+dp[i-1][0][0]*C(d-1,x-1)%mod)%mod;
	dp[i][1][0]=(dp[i-1][1][0]*C(d-1,x)  %mod+dp[i-1][1][1]*C(d-1,x-1)%mod)%mod;
	dp[i][1][1]=(dp[i-1][1][0]*C(d-1,x-1)%mod+dp[i-1][1][1]*C(d-1,x-2)%mod)%mod;
}
ans=(ans+dp[n][0][0]+dp[n][1][1])%mod);
~~~

时间复杂度：$O(n)$。

## 正解

我们可以发现，我们对于枚举的这个数量下，我们转移的几个参数都是相同的。

也就是说，我们每添加一条边的转移都是相同的，再加上我们的 $n\le 10^{14}$，这让我们想到，我们是否可以使用矩阵快速幂来解决。

~~~cpp
inline int solve(int X) {
	init(X);//预处理ans与bas
	int cnt=n;
	while(cnt) {
		if(cnt&1) ans=ans*bas;
		bas=bas*bas;
		cnt>>=1;
	}
	return (ans.a[1][1]+ans.a[1][4])%MOD;
}
~~~

对于我们的排列组合的处理，我们可以以 $O(d)$ 的复杂度预处理，或者预处理阶乘与其逆元。

整体的复杂度为：$O(\log n)$。

### 总结一下，我们此题运用了 DP，与矩阵的快速幂的优化。

---

## 作者：AC_love (赞：0)

考虑 $n$ 没这么大的时候怎么做。

设 $f(i, 0 / 1)$ 表示第 $i$ 条边末尾是白色 / 黑色的方案数，考虑转移。

转移成环，有点麻烦，不妨钦定第一个点是黑的，此时答案为 $f(n, 1)$，则最终答案其实是 $f(n, 1) \times 2$。

转移，枚举每条边上有 $j$ 个白点，则有：

$$f(i, 0) = f(i - 1, 0) \times {d - 1\choose j - 2} + f(i - 1, 1) \times {d - 1\choose j - 1}$$

$$f(i, 1) = f(i - 1, 0) \times {d - 1\choose j - 1} + f(i - 1, 1) \times {d - 1\choose j}$$

可以做到 $O(dn)$。但本题 $n \le 10^{12}$，考虑优化。

不难发现，转移过程可以用矩阵快速幂优化：

$$\begin{bmatrix} f(i - 1, 0) & f(i - 1, 1) \end{bmatrix} \times \begin{bmatrix} {d - 1\choose j - 2} & {d - 1\choose j - 1} \\ {d - 1\choose j - 1} & {d - 1\choose j} \end{bmatrix} = \begin{bmatrix} f(i, 0) & f(i, 1) \end{bmatrix}$$

由此可以做到 $O(d \log n)$ 的复杂度。

[code](https://atcoder.jp/contests/abc256/submissions/59637133)

---

## 作者：Shxt_Plus (赞：0)

### 分析
发现是计数题，首先想到 DP，但是这里是一个环，所以想到破环为链，但是发现最后一条链的最后一个石子需要和第一条链的第一个石子相同，所以考虑枚举第一条链的第一个石子是什么颜色的。

然后发现每条链都要有相同的白石子数，又发现 $d \leq 10^4$，所以很容易想到枚举每条链上有几个白石子。

那么我们就可以开始做了，用 $f_{j,0/1}$ 来表示第 $j$ 条链最后一个是白/黑石子。

转移方程也很好推，相当于在这条链上的除了首尾的两个石子的 $d-1$ 个石子中选 $x$ 个出来当白石子，方案也就是 $C_i^x$（$x$ 是这条链除了首尾石子应有的白石子数)。

也就是:

$$f_{i,0} = f_{i-1,0}\times C_{d-1}^{i-2}+f_{i-1,1}\times C_{d-1}^{i-1}$$

$$f_{i,1} = f_{i-1,0}\times C_{d-1}^{i-1}+f_{i-1,1}\times C_{d-1}^{i}$$

$i$ 是每条边要有的白石子数。

但是复杂度是 $O(nd)$ 的，但是发现是线性递推，用矩阵快速幂优化就行了。

时间复杂度 $O(d\log n)$。

### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,l;
struct jz
{
	int m[5][5];
	int r,c;
};
jz mul(jz a,jz b)
{
	jz c;
	c.r=a.r;
	c.c=b.c;
	for(int i=1;i<=c.r;i++)
	{
		for(int j=1;j<=c.c;j++)c.m[i][j]=0;
	}
	for(int i=1;i<=a.r;i++)
	{
		for(int j=1;j<=a.c;j++)
		{
			for(int k=1;k<=b.c;k++)
			{
				c.m[i][j]+=a.m[i][k]*b.m[j][k]%mod;c.m[i][j]%=mod;
			}
			
		}
	}
	return c;
}
jz po(jz x,int n)
{
	jz tmp;
	tmp.r=x.r;
	tmp.c=x.c;
	for(int i=1;i<=tmp.r;i++)
	{
		for(int j=1;j<=tmp.c;j++)tmp.m[i][j]=0;
	}
	for(int i=1;i<=tmp.r;i++)tmp.m[i][i]=1;
	while(n>0)
	{
		if(n&1)tmp=mul(x,tmp);
		x=mul(x,x);
		n>>=1;
	}
	return tmp;
}
int jc[10005],inv[10005],jc1[10005];
int C(int n,int m)
{
	if(m<0 || m>n)return 0;
	return jc[n]*jc1[m]%mod*jc1[n-m]%mod;
}
int ans;
signed main()
{
	cin>>n>>l;
	jc[0]=jc[1]=jc1[0]=jc1[1]=inv[1]=1;
	for(int i=2;i<=l+1;i++)
	{
		jc[i]=jc[i-1]*i%mod;
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
		jc1[i]=jc1[i-1]*inv[i]%mod;
	}
	
	for(int i=1;i<=l+1;i++)
	{
		jz b;
		b.r=2;
		b.c=2;
		b.m[1][1]=C(l-1,i-2);
		b.m[2][1]=C(l-1,i-1);
		b.m[1][2]=C(l-1,i-1);
		b.m[2][2]=C(l-1,i);
		b=po(b,n-1);
		jz f;
		f.r=1;
		f.c=2;
		f.m[1][1]=1;
		f.m[1][2]=0;
		f=mul(f,b);
		ans+=f.m[1][1]*C(l-1,i-2)%mod;
		ans+=f.m[1][2]*C(l-1,i-1)%mod;
		ans%=mod;
		f.m[1][1]=0;
		f.m[1][2]=1;
		f=mul(f,b);
		ans+=f.m[1][1]*C(l-1,i-1)%mod;
		ans+=f.m[1][2]*C(l-1,i)%mod;
		ans%=mod;
	}
	ans++;
	ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：yqr123YQR (赞：0)

### 题意
有一正 $n$ 边形，每条边上有 $d + 1$ 个点（端点会被两条线段同时包含），问有多少种黑白染色方案，使得每条边上白点的数量相等，答案对 $998244353$ 取模。
### 分析
由于 $d$ 比较小，而且每条边上的白点数量也是一个相对独立的量，可以直接枚举。设当前枚举至 $x$。

显然，对于一条边，端点及每条边其内部的点（即非端点的点）对其他边是没有影响的。又因为上条边对当前边的影响仅仅取决于其右端点，所以我们只需记录每种状态中，当前边的编号及右端点颜色即可。内部的点对方案的影响可以直接求：若剩余需要考虑的白点的个数为 $c$，则方案数应乘上 $\binom{d-1}c$。

则设 $f_{i,0/1}$ 表示“考虑前 $i$ 条边，当前边的右端点染为白 / 黑色的方案数”。有转移：
$$
\left\{\begin{matrix}
f_{i,0}=\binom{d-1}{x-2}f_{i-1,0}+\binom{d-1}{x-1}f_{i-1,1}\\\\
f_{i,1}=\binom{d-1}{x-1}f_{i-1,0}+\binom{d-1}xf_{i-1,1}
\end{matrix}\right.
$$
此时可以发现，$n$ 达到了 $10^{12}$，而状态又很小，想到 **矩阵快速幂**。将上式化为矩阵形式：
$$
\left[\begin{matrix}f_{i-1,0}&f_{i-1,1}\end{matrix}\right]
\times
\left[\begin{matrix}
\binom{d-1}{x-2}&\binom{d-1}{x-1}\\\\
\binom{d-1}{x-1}&\binom{d-1}x
\end{matrix}\right]
=\left[\begin{matrix}f_{i,0}&f_{i,1}\end{matrix}\right]
$$
为了不算重，钦定第一个端点为白色，则初始矩阵为 $[\begin{matrix}f_{1,0}=\binom{d-1}{x-2}&f_{1,1}=\binom{d-1}{x-1}\end{matrix}]$。累加 $f_{n,0}$ 即可。

时间复杂度：$O(d\log n)$。
### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
#include<memory.h>
typedef long long ll;
typedef unsigned long long ull;
const int maxd = 10000, mod = 998244353;
ll n, ans, fac[maxd + 5], rfac[maxd + 5];
int d;
void init()
{
	fac[0] = fac[1] = rfac[0] = rfac[1] = 1;
	for(int i = 2; i < d; i++) fac[i] = fac[i - 1] * i % mod, rfac[i] = (mod - mod / i) * rfac[mod % i] % mod;
	for(int i = 2; i < d; i++) rfac[i] = rfac[i - 1] * rfac[i] % mod;
}
ll C(int k) {return k < 0 || k > d - 1? 0: fac[d - 1] * rfac[k] % mod * rfac[d - 1 - k] % mod;}//C_{d-1}^k
struct matrix {
	int x, y;
	ll c[3][3];
	void init(int a, int b)
	{
		x = a, y = b;
		memset(c, 0, sizeof c);
	}
	friend matrix operator * (matrix a, matrix b) {
		matrix ret;
		ret.init(a.x, b.y);
		for(int i = 1; i <= a.x; i++)
			for(int j = 1; j <= a.y; j++)
				for(int k = 1; k <= b.y; k++)
					ret.c[i][k] = (ret.c[i][k] + a.c[i][j] * b.c[j][k] % mod) % mod;
		return ret;
	}
	friend matrix operator ^ (matrix a, ll b)
	{
		matrix ret = a;
		b--;
		while(b)
		{
			if(b & 1) ret = ret * a;
			a = a * a;
			b >>= 1;
		}
		return ret;
	}
}st, step;
int main()
{
//	freopen("stone.in", "r", stdin);
//	freopen("stone.out", "w", stdout);
	scanf("%lld%d", &n, &d);
	init();
	st.init(1, 2), step.init(2, 2);
	for(int i = 1; i <= d + 1; i++)
	{
		st.c[1][1] = C(i - 2), st.c[1][2] = C(i - 1);
		step.c[1][1] = C(i - 2), step.c[1][2] = step.c[2][1] = C(i - 1), step.c[2][2] = C(i);
		ll t = (st * (step ^ (n - 1))).c[1][1];
//		printf("%d:%lld\n", i, t);
		ans += t;
		if(ans >= mod) ans -= mod;
	}
	printf("%lld\n", (ans << 1) % mod);
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc256_g%20[ABC256G]%20Black%20and%20White%20Stones)

# 思路

容易看出来是个 DP 题，但是你发现 DP 的起点是不好确定的，于是假定第一条边的起点是黑色。然后你发现设为白色的贡献与黑色是相同的，于是直接令第一条边的起点是黑色，最后答案乘以 $2$ 即可。

然后就可以愉快的 DP 了。

首先枚举每条边白色点的数量 $k$，定义 $dp_{i,0/1}$ 表示确定了前 $i$ 条边，且第 $i$ 条边的终点为 黑色/白色。转移就比较显然了，递推起点为 $dp_{0,0} = 1$：

$$
\left\{\begin{matrix}
dp_{i,0} = dp_{i - 1,0} \times \binom{d - 1}{k} + dp_{i - 1,1} \times \binom{d - 1}{k - 1}\\
dp_{i,1} = dp_{i - 1,0} \times \binom{d - 1}{k - 1} + dp_{i - 1,1} \times \binom{d - 1}{k - 2}
\end{matrix}\right.
$$

但是这样转移的复杂度高达 $\Theta(nd)$，但是仔细观察发现这个式子与矩阵乘法类似。

令 $c_1 = \binom{d - 1}{k},c_2 = \binom{d - 1}{k - 1},c_3 = \binom{d - 1}{k - 2}$。

于是考虑维护 $\begin{bmatrix} dp_{i,0} & dp_{i,1} \end{bmatrix}$ 这个矩阵，它将转移为 $\begin{bmatrix} dp_{i,0} \times c_1 + dp_{i,1} \times c_2 & dp_{i,0} \times c_2 + dp_{i,1} \times c_3 \end{bmatrix}$。

容易构造出转移矩阵：

$$
\begin{bmatrix}
c_1 & c_2\\
c_2 & c_3
\end{bmatrix}
$$

直接矩阵快速幂优化即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Add(a,b) (((a) % mod + (b) % mod) % mod)
#define Mul(a,b) (((a) % mod) * ((b) % mod) % mod)

using namespace std;

const int N = 1e7 + 10,M = 1e4 + 10,mod = 998244353;
int n,d,ans;
int fac[M],inv[M];

struct mat{
	int n,m;
	int mt[5][5];
	
	mat(int a,int b){
		n = a;
		m = b;
		memset(mt,0,sizeof(mt));
	}

    mat friend operator *(const mat &a,const mat &b){
        mat t(a.m,b.m);
        for (re int i = 1;i <= a.n;i++){
            for (re int j = 1;j <= b.m;j++){
                for (re int k = 1;k <= a.m;k++) t.mt[i][j] = Add(t.mt[i][j],Mul(a.mt[i][k],b.mt[k][j]));
            }
        }
        return t;
    }
}base(2,2),dp(1,2);

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline int qmival(int a,int b){
    int res = 1;
    while (b){
        if (b & 1) res = Mul(res,a);
        a = Mul(a,a); b >>= 1;
    }
    return res;
}

inline mat qmi(mat a,int b){
	mat c(a.n,a.n);
	for (re int i = 1;i <= c.n;i++) c.mt[i][i] = 1;
	while (b){
		if (b & 1) c = c * a;
		a = a * a;
		b >>= 1;
	}
	return c;
}

inline void init(){
    fac[0] = 1;
    for (re int i = 1;i <= d;i++) fac[i] = Mul(fac[i - 1],i);
    inv[d] = qmival(fac[d],mod - 2);
    for (re int i = d - 1;~i;i--) inv[i] = Mul(inv[i + 1],i + 1);
}

inline int C(int n,int m){
    if (n < m || m < 0) return 0;
    return Mul(fac[n],Mul(inv[n - m],inv[m]));
}

inline int f(int k){
    int c1 = C(d - 1,k),c2 = C(d - 1,k - 1),c3 = C(d - 1,k - 2);
    dp.mt[1][1] = 1;
    base.mt[1][1] = c1; base.mt[1][2] = c2; base.mt[2][1] = c2; base.mt[2][2] = c3;
    mat ans = dp * qmi(base,n);
    return Mul(ans.mt[1][1],2);
}

signed main(){
    n = read(),d = read(); init();
    for (re int i = 0;i <= d;i++) ans = Add(ans,f(i));
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc256_g)

人生的第一场 ABC，现在回来补一下。

又是数数题，考虑把环拆成链后 dp。注意到拆成链后首尾应当是同一颜色，因此在状态中将它们都记录下来。

设 $f_{i,0/1,0/1}$ 表示前 $i$ 条边，第 $1$ 条边的开头为黑/白色，第 $i$ 条边的结尾为黑/白色，每条边的白色石子数量相同的方案数。

因为 $d$ 不大，所以可以考虑直接枚举每条边上几个白石子，每次重新 dp 一遍。记当前枚举的白石子数为 $x$，转移很显然：

$$
\begin{aligned}
f_{i,0,0}&=f_{i-1,0,0}\times\binom{d-1}{x}+f_{i-1,0,1}\times\binom{d-1}{x-1}\\
f_{i,0,1}&=f_{i-1,0,0}\times\binom{d-1}{x-1}+f_{i-1,0,1}\times\binom{d-1}{x-2}\\
f_{i,1,0}&=f_{i-1,1,0}\times\binom{d-1}{x}+f_{i-1,1,1}\times\binom{d-1}{x-1}\\
f_{i,1,1}&=f_{i-1,1,0}\times\binom{d-1}{x-1}+f_{i-1,1,1}\times\binom{d-1}{x-2}
\end{aligned}
$$
直接做复杂度是 $O(nd)$ 的，考虑优化。

不难发现转移的系数和 $i$ 无关，加上这个 $n$ 的范围很容易让人想到矩阵乘法：
$$
\begin{bmatrix}f_{i,0,0}&f_{i,0,1}\\f_{i,1,0}&f_{i,1,1}\end{bmatrix}
\times
\begin{bmatrix}\binom{d-1}{x}&\binom{d-1}{x-1}\\\binom{d-1}{x-1}&\binom{d-1}{x-2}\end{bmatrix}
$$
时间复杂度 $O(d\log n)$，做完了，矩阵乘法带 $8$ 倍常数。

[提交记录](https://atcoder.jp/contests/abc256/submissions/45500793)

---

## 作者：未来姚班zyl (赞：0)

## 题目大意
给定一个 $n$ 边形，每条边上需放 $d+1$ 块石子（黑或白），相邻边共用顶点。求每条边上黑色石子数量都两两相同的方案数。

## 题目分析

边和边之间的影响是非常小的，所以不难想到 dp。

枚举每条边的黑色石子数量，然后从一条边开始绕一圈，计算是否选择了顶点的方案数。瓶颈在于第一条边和最后一条边的交点很难容斥。干脆直接钦定这个交点染黑或者不染黑，复杂度 $O(nd)$。

显然，转移过程中系数是固定的，可以直接矩阵快速幂，复杂度 $O(d\log n)$。

```cpp
 #include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned int 
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e4+5,M=1e6+5,inf=2147000000;
const double eps=1e-6;
const ll mod=998244353,llf=1e18;
using namespace std;
ll n,d,ans;
ll mul[N],inv[N];
inline ll qp(ll a,ll b){
	if(!b)return 1;
	ll c=qp(a,b>>1);
	c=c*c%mod;
	if(b&1)c=c*a%mod;
	return c;
}
inline void prep(){
	inv[0]=mul[0]=1;
	rep(i,1,d)mul[i]=mul[i-1]*i%mod;
	inv[d]=qp(mul[d],mod-2);
	per(i,d-1,1)inv[i]=inv[i+1]*(i+1)%mod;	
}
inline ll c(int x,int y){
	if(x<y||y<0||x<0)return 0;
	return mul[x]*inv[y]%mod*inv[x-y]%mod;
}
struct mac{
	int a[2][2];
	mac(){
		memset(a,0,sizeof(a));
	}
	mac friend operator*(mac a,mac b){
		mac c;
		rep(i,0,1)rep(j,0,1)rep(k,0,1)(c.a[i][j]+=1LL*a.a[i][k]*b.a[k][j]%mod)%=mod;
		return c;
	}
};
inline mac mp(mac a,ll b){
	if(b==1)return a;
	mac c=mp(a,b>>1);
	c=c*c;
	if(b&1)c=c*a;
	return c;
}
ll dp[M][2];
int main(){
	cin >>n>>d;
	prep();
	rep(i,0,d+1){
		mac s,k;
		k.a[0][0]=c(d-1,i),k.a[0][1]=k.a[1][0]=c(d-1,i-1),k.a[1][1]=c(d-1,i-2);
		k=mp(k,n-1);
		s.a[0][0]=c(d-1,i-1),s.a[1][0]=c(d-1,i-2);
		s=k*s;
		(ans+=s.a[1][0])%=mod;
		s.a[0][0]=c(d-1,i),s.a[1][0]=c(d-1,i-1);
		s=k*s;
		(ans+=s.a[0][0])%=mod;
	}
	cout <<ans;
	return 0;
}
```


---

## 作者：zhouyuhang (赞：0)

确实是不错的好题，至少能把我这种弱智给区分掉。

注意到 $D$ 不大，$N$ 巨大。那你考虑枚举每一条边有几个白石子。不妨设枚举到了 $d$ 个。

然后是最妙的：考虑一个 dp。也就是说 $dp_{{i},{c_1},{c_2}}$ 表示第一个点（就是最开始那角）的颜色 $c_1$ 开始，到了第 $i$ 条边，这条边最后一个点（也就是这条边的角上）的颜色为 $c_2$。显然绕一圈回来刚好那个角重合了，因此这俩玩意儿颜色得一样，答案就是 $dp_{n,0,0}+dp_{n,1,1}$。

考虑如何转移。你发现本质上只跟你在这条边剩几个位置能填（实际上一定是 $D-1$），以及还需要几个白石子有关。这时枚举 $d$ 的好处就出来了：你可以直接确定从 $dp_{i,c_1,c_2}\to dp_{i,c_1,c_2'}$ 的过程中还有几个白石子需要填（实际上就是 $d-[c_2=0]-[c_2'=0]$）。这样一来系数就是从 $D-1$ 里选 $d-[c_2=0]-[c_2'=0]$ 个。然后你发现它是一个标准的矩阵加速形式。然后就做完了。

复杂度 $O(D\log N)$。还是很好写的。

---

