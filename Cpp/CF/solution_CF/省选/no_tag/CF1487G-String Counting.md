# String Counting

## 题目描述

You have $ c_1 $ letters 'a', $ c_2 $ letters 'b', ..., $ c_{26} $ letters 'z'. You want to build a beautiful string of length $ n $ from them (obviously, you cannot use the $ i $ -th letter more than $ c_i $ times). Each $ c_i $ is greater than $ \frac{n}{3} $ .

A string is called beautiful if there are no palindromic contiguous substrings of odd length greater than $ 1 $ in it. For example, the string "abacaba" is not beautiful, it has several palindromic substrings of odd length greater than $ 1 $ (for example, "aca"). Another example: the string "abcaa" is beautiful.

Calculate the number of different strings you can build, and print the answer modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2```

### 输出

```
422500```

## 样例 #2

### 输入

```
3
2 2 2 2 2 2 3 3 3 2 2 2 2 2 2 3 3 3 2 2 3 2 2 3 2 2```

### 输出

```
16900```

## 样例 #3

### 输入

```
400
348 322 247 158 209 134 151 267 268 176 214 379 372 291 388 135 147 304 169 149 193 351 380 368 181 340```

### 输出

```
287489790```

# 题解

## 作者：SunsetSamsara (赞：4)

## 题意

有 $26$ 个不同的字符，第 $i$ 个字符有 $c_i$ 个（$\frac{n}{3} < c_i \leq n$）。用这些字符，构造出一个长度为 $n$ 的字符串（每个字符在字符串中出现的个数不超过 $c_i$），使得这个字符串上不存在长度为奇数且大于 $1$ 的回文串。求出方案数对 $998244353$ 取模的结果。

## 分析

发现 $\frac{n}{3} < c_i \leq n$ 这个条件很有趣，因为这样的话如果一开始不管 $c_i$ 随便填也就最多只有 $2$ 个字符超过限制。

于是令不考虑限制的方案数为 $A$，超过至少 $1$ 种字符 $c_i$ 限制的方案数为 $B$，超过至少 $2$ 种字符 $c_i$ 限制的方案数为 $C$，然后用一遍容斥，就可以得到答案为 $A - B + C$。

接下来因为字符串上没有长度为奇数且长度大于 $1$ 的回文串，所以间隔为 $2$ 的字符不能相同。这个限制可以转化为：将字符串按下标奇偶性分为两个序列，序列中相邻两个数不能相等。

不考虑限制的方案数显然是 $A = 26^2\times 26^{n - 2}$。

至于至少一种超出限制的情况，可以使用 $\text{dp}$。既然有一种超出限制，就用 $f_{i, j, k}$ 表示在第 $i$ 位之内超出限制的字符有 $j$ 个并且上个字母是不是超出限制的字母 ($k = 1$ 表示是，$k = 0$ 表示否）的方案数。那么就有：

$$
\begin{aligned}
&f_{1, 1, 1} = 1,f_{1, 0, 0} = 25\\
&f_{i, j, 1} =\begin{cases}f_{i - 1, j - 1, 0}&i\neq\frac{n}{2} + 1\\f_{i - 1, j - 1, 0} + f_{i - 1,j - 1, 0}&i=\frac{n}{2}+1\end{cases}\\
&f_{i, j, 0} =\begin{cases}24f_{i - 1, j, 0}+25f_{i - 1, j, 1}&i\neq\frac{n}{2} + 1\\25f_{i - 1, j, 0}+25f_{i - 1, j, 1}&i=\frac{n}{2}+1\end{cases}
\end{aligned}
$$

最终的 $B = \sum\limits_{i=1}^{26}\sum\limits_{j=c_i+1}^{n}(f_{n,j,0} + f_{n, j, 1})$

至少两种超出限制的情况，也可以使用 $\text{dp}$。既然有两种超出限制，就用 $g_{i, j, k, l}$ 表示在第 $i$ 位之内超出限制的字符有 $j$ 个和 $k$ 个并且上个字母是不是超出限制的字母 ($l = 2$ 表示是第二种，$l = 1$ 表示是第一种，$l = 0$ 表示否）的方案数。 类似地,$C = \sum\limits_{i=1}^{26}\sum\limits_{j=i+1}^{26}\sum\limits_{x=c_i+1}^n\sum\limits_{y=c_j+1}^n(g_{n,x,y,0} + g_{n,x,y,1} + g_{n,x,y,2})$

最终的答案就是 $A - B + C$。

## 代码

```cpp
#include <stdio.h>
#define lld long long
inline lld min(const lld &x, const lld &y) { return x < y ? x : y; }
inline lld max(const lld &x, const lld &y) { return x < y ? y : x; }
const lld mod = 998244353;
const int N = 410;
int n;
int c[N];
int f[N][N][2], g[N][N][N][3];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 26; ++ i) scanf("%d", c + i);
	lld A = 26 * 26, B = 0, C = 0;
	for (int i = 2; i < n; ++ i) A = 25ll * A % mod; // 如上所述 
	
	f[1][1][1] = 1, f[1][0][0] = 25; // f的初始条件 
	for (int i = 2; i <= n; ++ i)
		for (int j = 0; j <= n; ++ j)
			if (i != n / 2 + 1) {
				if (j) f[i][j][1] = f[i - 1][j - 1][0];
				f[i][j][0] = (24ll * f[i - 1][j][0] % mod + 25ll * f[i - 1][j][1] % mod) % mod;
			} else {
				if (j) f[i][j][1] = (f[i - 1][j - 1][0] + f[i - 1][j - 1][1]) % mod;
				f[i][j][0] = (25ll * f[i - 1][j][0] % mod + 25ll * f[i - 1][j][1] % mod) % mod;
			}
	for (int i = 1; i <= 26; ++ i)
		for (int j = c[i] + 1; j <= n; ++ j)
			B = (B + f[n][j][0] + f[n][j][1]) % mod;
	
	g[1][1][0][1] = 1;
	g[1][0][1][2] = 1;
	g[1][0][0][0] = 24;
	for (int i = 2; i <= n; ++ i)
		for (int j = 0; j <= n; ++ j)
			for (int k = 0; k <= n; ++ k)
				if (i != n / 2 + 1) {
					if (j) g[i][j][k][1] = (0ll + g[i - 1][j - 1][k][0] + g[i - 1][j - 1][k][2]) % mod;
					if (k) g[i][j][k][2] = (0ll + g[i - 1][j][k - 1][0] + g[i - 1][j][k - 1][1]) % mod;
					g[i][j][k][0] = (23ll * g[i - 1][j][k][0] % mod
								   + 24ll * g[i - 1][j][k][1] % mod
								   + 24ll * g[i - 1][j][k][2] % mod) % mod;
				} else {
					if (j) g[i][j][k][1] = (0ll + g[i - 1][j - 1][k][0] + g[i - 1][j - 1][k][2] + g[i - 1][j - 1][k][1]) % mod;
					if (k) g[i][j][k][2] = (0ll + g[i - 1][j][k - 1][0] + g[i - 1][j][k - 1][1] + g[i - 1][j][k - 1][2]) % mod;
					g[i][j][k][0] = (24ll * g[i - 1][j][k][0] % mod
								   + 24ll * g[i - 1][j][k][1] % mod
								   + 24ll * g[i - 1][j][k][2] % mod) % mod;
				}
	C = 0;
	for (int i = 1; i <= 26; ++ i)
		for (int j = i + 1; j <= 26; ++ j)
			for (int x = c[i] + 1; x <= n; ++ x)
				for (int y = c[j] + 1; y <= n; ++ y)
					C = (C + g[n][x][y][0] + g[n][x][y][1] + g[n][x][y][2]) % mod;
	printf("%lld\n", ((A - B + C) % mod + mod) % mod);
}
```

---

## 作者：7KByte (赞：4)

EDU 最后一题还是值得思考的。

考虑没有 $c$ 的限制，我们可以设计 $\texttt{DP}$ ，其中 $f[i][u][v]$ 表示前 $i$ 位，最后两位为 $u$ 和 $v$ 的方案数，枚举一下 $i,u,v$ 和 最后一位 $k\ (k\ne u)$ 转移即可。

这里也给一份代码 $\rm O(26^3 N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 405
#define P 998244353
using namespace std;
int f[N][27][27];
int main(){
	int n;scanf("%d",&n);
	rep(i,0,25)rep(j,0,25)f[2][i][j]=1;
	rep(i,3,n)rep(x,0,25)rep(y,0,25)rep(z,0,25)if(x!=z)f[i][x][y]=(f[i][x][y]+f[i-1][y][z])%P;
	int ans=0;rep(i,0,25)rep(j,0,25)ans=(ans+f[n][i][j])%P;
	printf("%d\n",ans);return 0;
}
```

观察一下给定的条件，$\frac{n}{3}\le c_i$的条件很奇怪，手盘一下发现最多只会有两种字符超出限制，因为如果有三个超过则总和已经 $>n$ 了。

这样我们可以容斥一下，先用前一份代码求出所有满足条件的串的数量，再减去一种字符超出限制的串的数量，最后加上两种字符超出限制的串的数量。

我们可以设计方程 $f[i][p][q][u][v][x][y]$ 表示前 $i$ 位，第 $p$种字符使用了 $u$ 次，第 $q$ 种字符使用了 $v$ 次，最后两位为 $x,y\in\{0,1,2\}$，分别表示为 $p$ 字符，为$ q$ 字符或为其余的 $24$ 种字符之一。

肉眼可见无论 $p,q$ 是什么都一样，所以这两个维度去掉。

然后枚举一下当前位 $z$ 转移。如果 $z=2$ 则有 $24$ 种选择，否则只有 $1$ 种选择，注意如果$z=2\  \rm and \ x=z$，则只有 $23$ 种选择。

转移一下得到$f[i][u][v][x][y]$。

注意超出的部分$u,v$是$>c_k$ 的一段，所以我们求出二维后缀和：

$$g[i][j]=\sum\limits_{u=i}^{n}\sum\limits_{v=j}^{n}\sum\limits_{x,y\in\{0,1,2\}}f[n][u][v][x][y]$$ 

最后 $Ans=g[0][0]-\sum\limits_{i=1}^{26}g[c_i+1][0]+\sum\limits_{i=1}^{26}\sum\limits_{j=i+1}^{26}g[c_i+1][c_j+1]$。

这样会被卡空间，注意把第一个维度用滚动数组优化。

这样还会被卡常，搞不好还会$\texttt{TLE}$翻车。

观察一下$u,v$的上界为$\left\lfloor\frac{n}{2}\right\rfloor+1$，可以优化$4$倍常数。

显然，只有形如 $\texttt{AABBAABB}...$的串能卡到这个上界。

时间复杂度$\rm O(N^3)$，空间复杂度 $\rm O(N^2)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 405
#define P 998244353
using namespace std;
int n,c[26],f[2][205][205][3][3],g[N][N];
signed main(){
	scanf("%d",&n);
	rep(i,0,25)scanf("%d",&c[i]);
	rep(i,0,2)rep(j,0,2)f[0][(i==1)+(j==1)][(i==2)+(j==2)][i][j]=(i?1:24)*(j?1:24);
	rep(i,3,n){
		int cur=i&1;
		memset(f[cur],0,sizeof(f[cur]));
		rep(u,0,n/2+1)rep(v,0,n/2+2)rep(x,0,2)rep(y,0,2)rep(z,0,2){
			if(x==z&&x)continue;
			if(x==z)f[cur][u][v][y][z]=(f[cur][u][v][y][z]+1LL*f[cur^1][u][v][x][y]*23%P)%P;
			else f[cur][u+(z==1)][v+(z==2)][y][z]=(f[cur][u+(z==1)][v+(z==2)][y][z]+1LL*f[cur^1][u][v][x][y]*(z?1:24)%P)%P;
		}
	}
	pre(i,n/2+1,0)pre(j,n/2+1,0){
		g[i][j]=(g[i+1][j]+g[i][j+1]-g[i+1][j+1])%P;
		rep(x,0,2)rep(y,0,2)g[i][j]=(g[i][j]+f[n&1][i][j][x][y])%P;
	}
	int ans=g[0][0];
	//cout<<ans<<endl;
	rep(i,0,25)ans=(ans-g[c[i]+1][0])%P;
	rep(i,0,25)rep(j,i+1,25)if(i^j)ans=(ans+g[c[i]+1][c[j]+1])%P;
	printf("%d\n",(ans+P)%P);
	return 0;
} 

```

---

## 作者：Sol1 (赞：3)

所有 $c$ 都大于 $\dfrac{n}{3}$，所以超限的最多有两个，故考虑容斥。

DP，保存两个特殊字符的数量，设 $f(i,j,k,0/1/2,0/1/2)$ 为构造长度为 $i$，特殊字符 1 用了 $j$ 个，特殊字符 2 用了 $k$ 个，$i-1$ 位是特殊字符 1/特殊字符 2/普通字符，$i$ 位是特殊字符 1/特殊字符 2/普通字符的方案数。

有：

- $f(1,1,0,0,0)=1$
- $f(1,0,1,0,1)=1$
- $f(1,0,0,0,2)=24$
- $f(2,j,k,l,0)=f(1,j-1,k,0,l)$
- $f(2,j,k,l,1)=f(1,j,k-1,0,l)$
- $f(2,j,k,l,2)=24f(1,j,k,0,l)$
- $f(i,j,k,l,0)=f(i-1,j-1,k,1,l)+f(i-1,j-1,k,2,l)$
- $f(i,j,k,l,1)=f(i-1,j,k-1,0,l)+f(i-1,j,k-1,2,l)$
- $f(i,j,k,l,2)=24f(i-1,j,k,0,l)+24f(i-1,j,k,1,l)+23f(i-1,j,k,2,l)$

设 $s_{j,k}=\sum_{x=j}^n\sum_{y=k}^n\sum_{p=0}^2\sum_{q=0}^2f(n,x,y,p,q)$，则答案就是：

$$s_{0,0}-\sum_{i=1}^{26}s_{c_i+1,0}+\sum_{i=1}^{26}\sum_{j=i+1}^{26}s_{c_i+1,c_j+1}$$

二维后缀和递推 $s$ 是 $O(n^2)$，暴力枚举算答案是 $O(|\Sigma|^2)$，总复杂度 $O(n^3)$，空间复杂度可以通过滚动数组做到 $O(n^2)$，可以通过本题。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const long long mod = 998244353;
int n, c[30];
long long dp[2][405][405][3][3], ans[405][405];

inline void Read() {
	n = qread();
	for (int i = 1;i <= 26;i++) c[i] = qread();
}

inline void Trans(long long &x, long long y) {x = (x + y >= mod ? x + y - mod : x + y);}

inline void Prefix() {
	dp[1][0][0][0][2] = 24;
	dp[1][0][1][0][1] = 1;
	dp[1][1][0][0][0] = 1;
	for (int i = 2;i <= 2;i++) {
		memset(dp[i & 1], 0, sizeof(dp[i & 1]));
		for (int j = 0;j <= n;j++) {
			for (int k = 0;k <= n;k++) {
				if (j) {
					for (int l = 0;l < 3;l++) {
						Trans(dp[i & 1][j][k][l][0], dp[i - 1 & 1][j - 1][k][0][l]);
						Trans(dp[i & 1][j][k][l][0], dp[i - 1 & 1][j - 1][k][1][l]);
						Trans(dp[i & 1][j][k][l][0], dp[i - 1 & 1][j - 1][k][2][l]);
					}
				}
				if (k) {
					for (int l = 0;l < 3;l++) {
						Trans(dp[i & 1][j][k][l][1], dp[i - 1 & 1][j][k - 1][0][l]);
						Trans(dp[i & 1][j][k][l][1], dp[i - 1 & 1][j][k - 1][1][l]);
						Trans(dp[i & 1][j][k][l][1], dp[i - 1 & 1][j][k - 1][2][l]);
					}
				}
				for (int l = 0;l < 3;l++) {
					Trans(dp[i & 1][j][k][l][2], dp[i - 1 & 1][j][k][0][l] * 24 % mod);
					Trans(dp[i & 1][j][k][l][2], dp[i - 1 & 1][j][k][1][l] * 24 % mod);
					Trans(dp[i & 1][j][k][l][2], dp[i - 1 & 1][j][k][2][l] * 24 % mod);
				}
			}
		}
	}
	for (int i = 3;i <= n;i++) {
		memset(dp[i & 1], 0, sizeof(dp[i & 1]));
		for (int j = 0;j <= n;j++) {
			for (int k = 0;k <= n;k++) {
				if (j) {
					for (int l = 0;l < 3;l++) {
						Trans(dp[i & 1][j][k][l][0], dp[i - 1 & 1][j - 1][k][1][l]);
						Trans(dp[i & 1][j][k][l][0], dp[i - 1 & 1][j - 1][k][2][l]);
					}
				}
				if (k) {
					for (int l = 0;l < 3;l++) {
						Trans(dp[i & 1][j][k][l][1], dp[i - 1 & 1][j][k - 1][0][l]);
						Trans(dp[i & 1][j][k][l][1], dp[i - 1 & 1][j][k - 1][2][l]);
					}
				}
				for (int l = 0;l < 3;l++) {
					Trans(dp[i & 1][j][k][l][2], dp[i - 1 & 1][j][k][0][l] * 24 % mod);
					Trans(dp[i & 1][j][k][l][2], dp[i - 1 & 1][j][k][1][l] * 24 % mod);
					Trans(dp[i & 1][j][k][l][2], dp[i - 1 & 1][j][k][2][l] * 23 % mod);
				}
			}
		}
	}
	for (int j = 0;j <= n;j++) {
		for (int k = 0;k <= n;k++) {
			for (int l = 0;l < 3;l++) {
				for (int m = 0;m < 3;m++) Trans(ans[j][k], dp[n & 1][j][k][l][m]);
			}
			//printf("%lld ", ans[j][k]);
		}
		//puts("");
	}
	for (int j = n;j >= 0;j--) {
		for (int k = n;k >= 0;k--) Trans(ans[j][k], (ans[j][k + 1] + ans[j + 1][k] - ans[j + 1][k + 1] + mod) % mod);
	}
}

inline void Solve() {
	long long res = ans[0][0];
	//printf("%lld\n", res);
	for (int i = 1;i <= 26;i++) {
		//printf("%lld ", ans[c[i] + 1][0]);
		res = (res - ans[c[i] + 1][0] + mod) % mod;
	}
	//puts("");
	for (int i = 1;i <= 26;i++) {
		for (int j = i + 1;j <= 26;j++) Trans(res, ans[c[i] + 1][c[j] + 1]);
	}
	printf("%lld", res);
}

int main() {
	Read();
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：q424479543 (赞：0)

前面的思路跟之前的人的题解是一样的，主要就是容斥+dp。我这里前面的思路直接跳过了，主要说一下我自己后面的想法。

### 状态表示

状态 $f[i][u][v][a][b]$ 表示前 $i$ 位，第一种字符用了 $u$ 个，第二种字符用了 $v$ 个，最后两位的字符是 $a$ 和 $b$，其中 $a, b \in \{0, 1, 2\}$。具体含义为：

- $0$ 表示其他 24 种字符；
- $1$ 表示第 1 种字符；
- $2$ 表示第 2 种字符。

### 二元多项式表示

将第 2、3 个状态用二元多项式表示。这样， $[x^u y^v] F_{i, a, b}(x, y)$ 就是原来的 $f[i][u][v][a][b]$，其中 $F_i$ 是一个 $3 \times 3$ 的矩阵，矩阵中的每个元素是一个二元多项式。

### 转移矩阵

新增一个字符后，倒数第三个字符到倒数第一个字符的转移矩阵 $A$ 为：

$$
A = 
\begin{bmatrix}
23 & x & y \\
24 & 0 & y \\
24 & x & 0
\end{bmatrix}
$$

### 递推关系

字符串只有 2 位时：

$$
F_2 = F_2^T = 
\begin{bmatrix}
24 \\
x \\
y
\end{bmatrix}
\begin{bmatrix}
24 & x & y
\end{bmatrix}
$$

对于 $F_{i+1}$ 后两个字符是 $bc$ 的情况，可以由 $F_i$ 后两个字符是 $0b(c)$、$1b(c)$、$2b(c)$ 的情况转移得到：

$$
F_{i+1, b, c} = F_{i, 0, b} A_{0, c} + F_{i, 1, b} A_{1, c} + F_{i, 2, b} A_{2, c}
$$

$$
\qquad\quad = F_{i, b, 0}^T A_{0, c} + F_{i, b, 1}^T A_{1, c} + F_{i, b, 2}^T A_{2, c}
$$

$F_i$ 的递推关系如下：

$$
F_{i+1} = F_i^T A
$$

$$
F_{i+2} = F_{i+1}^T A = A^T F_i A
$$

$$
F_{i+3} = F_{i+2}^T A = A^T F_i^T A^2
$$

得到：

$$
F_n = 
\begin{cases}
A^{\frac{n-2}{2} T} F_2 A^{\frac{n-2}{2}}, & \text{如果} \, n \, \text{是偶数} \\
A^{\frac{n-3}{2} T} F_2^T A^{\frac{n-1}{2}}, & \text{如果} \, n \, \text{是奇数}
\end{cases}
$$

把 $F_2$ 带代入上式：

$$
F_n = A^{\lfloor \frac{n-2}{2} \rfloor T} 
\begin{bmatrix}
24 \\
x \\
y
\end{bmatrix}
\begin{bmatrix}
24 & x & y
\end{bmatrix} 
A^{\lceil \frac{n-2}{2} \rceil}
$$

这里的转置是因为转移时系数由倒数第三个字符和倒数第一个字符决定。如果转移系数由最后两个字符决定，则无需转置。

### 矩阵分解

发现可以把 $F_n$ 分解成左右两个部分，分别是一个 $3 \times 1$ 的列向量和一个 $1 \times 3$ 的行向量相乘。

令 $B_i$ 表示如下的行向量：

$$
B_i = 
\begin{bmatrix}
24 & x & y
\end{bmatrix} A^i 
$$

则有：

$$
F_n = B_{\lfloor \frac{n-2}{2} \rfloor}^T  B_{\lceil \frac{n-2}{2} \rceil}
$$

$$
\sum_{a=0}^{2} \sum_{b=0}^{2} F_{n, a, b} = 
\begin{bmatrix}
1 & 1 & 1
\end{bmatrix} F_n
\begin{bmatrix}
1 \\
1 \\
1
\end{bmatrix}
=  
(B_{\lfloor \frac{n-2}{2} \rfloor} 
\begin{bmatrix}
1 \\
1 \\
1
\end{bmatrix})^T  
(B_{\lceil \frac{n-2}{2} \rceil}
\begin{bmatrix}
1 \\
1 \\
1
\end{bmatrix})
$$

### 复杂度分析

使用矩阵快速幂和可变大小的二维卷积计算 $B_{\lceil \frac{n-2}{2} \rceil}$ 复杂度为 $O(n^2 \log n)$，而固定大小的二维卷积复杂度为 $O(n^2 \log^2 n)$。

另外，可以直接通过 $1 \times 3$ 向量乘以 $3 \times 3$ 矩阵，乘 $\lceil \frac{n-2}{2} \rceil$ 次来计算 $B_{\lceil \frac{n-2}{2} \rceil}$，这样复杂度仍为 $O(n^3)$。不过，由于仅需要计算到 $\frac{n}{2}$，且是 $1 \times 3$ 向量之间的转移，而不是 $3 \times 3$ 矩阵间的转移，常数为原来的 $\frac{1}{24}$。


### 部分代码
```cpp
mint f[2][102][102][3];
constexpr int fftN = 256;
int a[fftN][fftN] , b[fftN][fftN];
void ntt2(int a[][fftN],bool isRev){
    for(int i = 0; i < fftN; ++i)
        poly::ntt::ntt(a[i] , fftN, isRev);
    for(int i = 0; i < fftN; ++i)
        for(int j = i + 1; j < fftN; ++j) 
            swap(a[i][j],a[j][i]);
    for(int i = 0; i < fftN; ++i)
        poly::ntt::ntt(a[i] , fftN, isRev);
} 
void conv2(){
    ntt2(a,0); ntt2(b,0);
    for(int i = 0; i < fftN; ++i)
        for(int j = 0; j < fftN; ++j) 
            a[i][j] *= (mint)b[i][j];
    ntt2(a,1);
}
void solution(){ 
    int n = rd();
    f[0][0][0][0] = (mint)24;
    f[0][1][0][1] = (mint)1;
    f[0][0][1][2] = (mint)1; 
    for(int i = 1; i <= (n-2+1)/2 ; ++i){
        auto &F = f[~i&1] , &G = f[i&1];
        memset(G , 0 , sizeof(G));
        for(int u = 0; u <= i/2+1; ++u)
            for(int v = 0; v <= i/2+1; ++v){
                G[u][v][0] = 23 * F[u][v][0] + 24 * (F[u][v][1] + F[u][v][2]);
                G[u+1][v][1] = F[u][v][0] + F[u][v][2];
                G[u][v+1][2] = F[u][v][0] + F[u][v][1];
            }
    }
    auto &F = f[(n-2)/2&1] , &G = f[(n-2+1)/2&1];
    for(int u = 0; u <= n/4+1; ++u)
        for(int v = 0; v <= n/4+1; ++v)
            a[u][v] = F[u][v][0] + F[u][v][1] + F[u][v][2],
            b[u][v] = G[u][v][0] + G[u][v][1] + G[u][v][2];
    conv2();
    for(int u = n/2+1; u >= 0; --u)
        for(int v = n/2+1; v >= 0; --v)
            a[u][v] = (mint)a[u][v] + a[u+1][v] + a[u][v+1] - a[u+1][v+1];
    int res = a[0][0], C[26];
    for(int i = 0 ; i < 26; ++i){
        C[i] = min(rd<int>(), n/2+1);
        res -= (mint)a[C[i]+1][0];
        for(int j = 0; j < i; ++j)
            res += (mint)a[C[i]+1][C[j]+1];
    }
    print(res);
}
```

---

