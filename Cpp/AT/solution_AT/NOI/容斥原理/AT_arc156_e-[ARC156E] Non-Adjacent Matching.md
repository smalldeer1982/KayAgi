# [ARC156E] Non-Adjacent Matching

## 题目描述

给定一个长度为 $N$ 的整数序列，每个元素的取值范围为 $0$ 到 $M$，且所有元素的总和不超过 $K$。请你求出满足条件的**好数列**的个数，并将答案对 $998244353$ 取模。

这里，长度为 $N$ 的数列 $X=(X_1,X_2,\ldots,X_N)$ 被称为好数列，当且仅当存在一个满足以下所有条件的图 $G$：

- $G$ 是一个有 $N$ 个顶点（编号为 $1$ 到 $N$）的图，且不包含自环（允许有重边）。
- 对于每个 $i\ (1\leq i \leq N)$，顶点 $i$ 的度数为 $X_i$。
- 对于每个 $i\ (1\leq i \leq N)$，不存在连接顶点 $i$ 和顶点 $i+1$ 的边。这里，顶点 $N+1$ 视为顶点 $1$。

## 说明/提示

### 限制

- $4 \leq N \leq 3000$
- $0 \leq M \leq 3000$
- $0 \leq K \leq NM$
- 输入的所有数均为整数

### 样例解释 1

满足条件的好数列有以下 $3$ 个：

- $(0,0,0,0)$
- $(0,1,0,1)$
- $(1,0,1,0)$

### 样例解释 3

请将答案对 $998244353$ 取模后输出。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
10 0 0```

### 输出

```
1```

## 样例 #3

### 输入

```
314 159 26535```

### 输出

```
248950743```

# 题解

## 作者：_SeeleVollerei_ (赞：6)

当允许有 $(i,i+1)$ 的边时，满足题目要求有充要条件 $S=\sum x_i$ 为偶数且不存在某个 $x_i>\frac{S}{2}$。

考虑在这个基础上去调整，将 $(i,i+1)$ 的边找个没有公共点的边去重新选边。那么充要条件为 $S=\sum x_i$ 为偶数且不存在某个 $x_i+x_{i+1}>\frac{S}{2}$。考虑对这个东西计数。

直接数是很麻烦的，但是如果去容斥的话，容易发现由于 $>\frac{S}{2}$，所以需要考虑的情况只有两种，一种是存在 $x_i+x_{i-1}>\frac{S}{2}$，一种是在满足前面一个条件的同时满足 $x_{i-1}+x_i>\frac{S}{2}$。设前面的情况的方案数为 $B$，后面的方案数为 $C$，总的方案数为 $A$，那么答案就是 $A-B+C$。

考虑逐个计算。

对于总方案数，相当于求 $n$ 个 $[0,m]$ 的数凑出来的和 $\le k$ 且为偶数的情况。我选择从生成函数的角度去考虑。

每个数的 GF 是 $1+x+x^2+...+x^m=\frac{1-x^{m+1}}{1-x}$，那么 $n$ 个数乘起来就是 $(\frac{1-x^{m+1}}{1-x})^n$。把分子分母拆开，令 $F(x)=(1-x^{m+1})^n,G(x)=\frac{1}{(1-x)^n}$。那么所求为 $F(x)G(x)$ 的 $\le k $ 的偶数次项的系数。

对于 $F(x)$ 考虑二项式定理展开。

$$F(x)=\sum_{i=0}^n(-1)^i\binom{n}{i}x^{(m+1)i}$$

而 $G(x)$ 是一个很经典的式子，也可以组合意义理解为 $n$ 个没有限制的值凑出来一个和的方案数。

$$G(x)=\sum_{i}\binom{i+n-1}{n-1}x^i$$

枚举 $F(x)$ 的每一项，乘上 $G(x)$ 的一个前缀和即可。复杂度 $O(k)$。

然后还要去除 $x_i>\frac{S}{2}$ 的情况。但是因为 $x_i\le m$ 所以 $S< 2m$，所以不妨直接枚举 $x$ 和 $S$，剩下的部分插板即可，贡献是 $n\times\binom{S-x+n-2}{n-2}$。复杂度 $O(m^2)$。

为了方便，我们可以实现一个函数 $Calc(n,S)$ 表示用 $n$ 个 $[0,m]$ 的数凑出和**恰好**为 $s$ 的方案数。计算方法依然是 $F(x)G(x)$，因为 $F(x)$ 每 $m+1$ 位才有值，所以这个复杂度是 $O(\frac{S}{m})$。

对于 $B$，不妨设 $x_1+x_2>\frac{S}{2}$。因为 $x_1,x_2\le m$，所以有 $S< 4m$。我们考虑枚举 $S$ 和 $S_1=x_1+x_2$。然后考虑把 $x_2$ 用 $S_1-x_1$ 表示，列出与 $x_1$ 有关的不等式。

$$0\le x_1,S_1-x_1\le \min(m,\frac{S}{2})$$

$$S_1-\max(m,\frac{S}{2})\le x_1\le\min(m,\frac{S}{2})$$

有了范围，直接算出 $x_1$ 的情况数即可。复杂度 $O(m^2)$。

然后对于其他数乘上一个 $Calc(n-2,S-S_1)$ 即可。因为 $S<4m$，所以调用该函数的复杂度可以视作常数忽略不计。

对于 $C$，不妨设 $x_1+x_2,x_2+x_3>\frac{S}{2}$。同理有 $S<4m$。枚举 $S$ 和 $S_1=x_1+x_2+x_3$。

接着我们考虑如果我们再去枚举一个 $x_2$ 的话相关的不等式会变成什么样子，尽管直接枚举是 $O(m^3)$ 的。我们将 $x_3$ 用 $S_1-x_2-x_1$ 表示，列出关于 $x_1$ 的不等式。

$$\frac{S}{2}-x_2+1\le x_1,S_1-x_2-x_1\le\min(S_1-x_2,\frac{S}{2},m)$$

化简。

$$\max(\frac{S}{2}+1,S_1-\frac{S}{2},S_1-m)-x_2\le x_1\le \min(\frac{S}{2},m,S_1-\frac{S}{2}-1)$$

容易发现右端点是一个常数，而左端点随着 $x_2$ 增加而减少，那么 $x_1$ 的可选方案数就构成一个公差为 1 的等差数列。直接求和即可。

复杂度 $O(m^2)$。然后同理调用 $Calc(n-3,S-S_1)$ 去计算其他数的方案数。复杂度同理，忽略不计。

值得一提的是算完 $B$ 和 $C$ 都要 $\times n$，原因显然。

https://atcoder.jp/contests/arc156/submissions/39080070

---

## 作者：xcyle (赞：4)

### 充要条件

容易发现，序列 $(X_1,...,X_N)$ 是好的，当且仅当：

- 记 $S=X_1+...+X_N$，$S$ 是偶数，且 $\forall 1\le i\le N,X_i+X_{i\mod N+1}\le \frac{S}{2}$。

对最后一个条件容斥，答案等于：无限制的方案数，减去存在一个位置不满足，再加上两个位置不满足。注意后者两个位置一定相邻。

### 无限制的方案数

记 $f(x)=\frac{1-x^{M+1}}{1-x}$，这个序列的生成函数就是 $f(x)^N$。所求为这个多项式不超过 $K$ 的偶数次系数之和。

不妨设 $K$ 为偶数，那么所求等于 $[x^K]\frac{f(x)^N}{1-x^2}$。

$f(x)^N$ 的上下次数都较高，不如先求出 $g(x)=\frac{(1-x^{M+1})^N}{1-x^2}$，然后就可以快速求出 $[x^K]g(x)(1-x)^{-N}$ 了。

### 存在一个位置不满足的方案数

不妨设不满足的位置是 $1$。

枚举 $T=X_3+...+X_N$，对 $X_1,X_2$ 的限制只和 $X_1+X_2$ 有关。

注意到 $T<2M$，可以在 $O(M^2)$ 的时间内求出 $f(x)^{N-2}$ 的前 $2M$ 项，也就是 $X_3...X_N$ 的填法。

枚举 $X_1+X_2,T$ 计算，复杂度 $O(M^2)$。

### 两个位置不满足的方案数

不妨设不满足的位置是 $1,2$。

枚举 $X_2,T$，
所求为 $\sum\limits_{0\le X_2\le M,T}[x^T]f(x)^{N-3}h(X_2+T,X_2-T)$。

其中 $h(a,b)=\sum\limits_{0\le X_1,X_3\le M,2|X_1+X_3+a}[X_1+X_3\le K-a\land |X_1-X_3|< b]$。可以前缀和预处理。

总时间复杂度 $O((N+M)M)$。

---

## 作者：Tony2 (赞：3)

8 月重做 2 月的题。

首先考虑判定。首先序列需要满足和为奇数。如果 $\exists i:2(a_i+a_{i+1})>\sum_{i=1}^n a_i$，那么序列非法。充分性显然，将这两个位置看作整体之后无法不出现自环；必要性考虑归纳，每次都存在连边方案使下一次也满足条件。

第一部分，算出和为奇数的序列的个数。序列需要满足每个值的范围是 $[0,m]$，这个限制可以差分成 $[0,\inf)-[m+1,\inf)$，对于所有的值就进行容斥。

第二部分，算出钦定两个相邻位置和大于其它位置的个数。因为两个位置的和 $\le 2m$，所以可以直接背包解决。加上前缀和优化背包部分就是 $O(nm)$ 的。

第三部分，注意到第二部分会算重，因为可能有多对不合法的对。注意到不可能有两对不相交的对，所以它们共享一个中点。对于暴力可以考虑枚举中点左侧、中点、中点右侧的值，可以去掉枚举中点的值进行优化，此时中点的可能值是一段区间。

答案是第一部分减第二部分加第三部分。为了方便，我们一般把第二部分和第三部分的初始不合法对的位置固定并共用一个 dp。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3005, NN = 1e7 + 5, lim = 1e7, mod = 998244353;
int qpow(int x, int y){
	int res = 1;
	while (y){
		if (y & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return res;
}
int fac[NN], ifac[NN];
int C(int n, int m){
	return 1ll * fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}
int n, m, k;
int S[NN][2];
int ans1, ans2, ans3;
int f[N][N * 2][2];//考虑到第 i 个人，还剩多少可用度数 
int g[N * 2][2];
void solve(int s){
	for (int i = s; i < n; i++){
		int sum[2] = {0, 0};
		for (int j = m * 2; j >= 0; j--){
			swap(sum[0], sum[1]);
			sum[0] = (sum[0] + f[i][j][0]) % mod;
			sum[1] = (sum[1] + f[i][j][1]) % mod;
			if (j + m < m * 2){
				sum[((m + 1) & 1)] = (sum[((m + 1) & 1)] - f[i][j + m + 1][0]) % mod;
				sum[((m + 1) & 1) ^ 1] = (sum[((m + 1) & 1) ^ 1] - f[i][j + m + 1][1]) % mod;
			}
			f[i + 1][j][0] = sum[0];
			f[i + 1][j][1] = sum[1];
		}
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	fac[0] = 1;
	for (int i = 1; i <= lim; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[lim] = qpow(fac[lim], mod - 2);
	for (int i = lim - 1; i >= 0; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	cin >> n >> m >> k;
	
	for (int i = 0; i <= k; i++){
		int x = C(i + n - 1, n - 1);
		S[i][0] = (S[i - 1][0] + (i & 1 ? 0 : x)) % mod;
		S[i][1] = (S[i - 1][1] + (i & 1 ? x : 0)) % mod;
	}
	for (int i = 0; i <= n && i * (m + 1) <= k; i++)
		ans1 = (ans1 + (i & 1 ? -1ll : 1ll) * C(n, i) * S[k - i * (m + 1)][(i * (m + 1)) & 1]) % mod;
	
	memset(f, 0, sizeof(f));
	for (int a = 0; a <= m; a++)
		for (int b = 0; b <= m; b++)
			if (a + b <= k && a + b > 0)
				f[2][min(k - a - b, a + b - 1)][(a + b) & 1]++;
	solve(2);
	for (int i = 0; i <= m * 2; i++)
		ans2 = (ans2 + f[n][i][0]) % mod;
	
	memset(f, 0, sizeof(f));
	for (int a = 0; a <= m; a++)
		for (int c = 0; c <= m; c++){
			int bl = abs(a - c) + 1, br = min(k - a - c, m);
			if (!(0 <= bl && bl <= br)) continue;
			int mid = (abs(a - c) + 1 + k - a - c) / 2;
			if (bl <= mid){
				int l = bl, r = min(mid, br);
				g[l - abs(a - c) - 1][(a + l + c) & 1]++;
				g[r - abs(a - c)][(a + (r + 1) + c) & 1]--;
			}
			if (mid < br){
				int l = max(mid + 1, bl), r = br;
				g[k - a - r - c][(a + r + c) & 1]++;
				g[k - a - l - c + 1][(a + (l - 1) + c) & 1]--;
			}
		}
	for (int i = 0; i <= m * 2; i++){
		f[3][i][0] = g[i][0];
		f[3][i][1] = g[i][1];
		g[i + 1][1] += g[i][0];
		g[i + 1][0] += g[i][1];
	}
	solve(3);
	for (int i = 0; i <= m * 2; i++)
		ans3 = (ans3 + f[n][i][0]) % mod;
	
	cout << ((ans1 - 1ll * (ans2 - ans3) * n % mod) % mod + mod) % mod;
	return 0;
}
```

---

## 作者：rubbishZZZ (赞：1)

## ARC156E Non-Adjacent Matching



#### 题意：

- 给定 $n,m,K$，称一个序列 $X_1,X_2,\cdots,X_n$ 是合法的，当且仅当存在一个 $n$ 个点的无向图，满足第 $i$ 个点的度数是 $X_i$，第 $i$ 个点不连向 $i+1$，且 $X_i\leq m,\sum\limits_{i=1}^nX_i\leq K$。求有多少个合法的序列，对 $998244353$ 取模。
- $4\leq n\leq 3000,0\leq m\leq 3000,0\leq k\leq nm$。



#### 解法：

- 困难的部分是他形成了一个不存在 $(i,i+1)$无向图，考虑转化这个限制。

  设 $k=\sum\limits_{i=1}^n X_i$，则 $2\mid k$ 是合法的必要条件。

  我们发现对于不相交的 $(i,i+1),(x,y)$，一定存在一种交换方式使得不存在相邻的边。

  那么不合法当且仅当无论怎么交换都存在 $(i,i+1)$，进一步发现 $2(X_i+X_{i+1})\gt k$。

  小结一下：合法当且仅当 $\forall i,2(X_i+X_{i+1})\leq k$，$X_i\leq m$，$2\mid k$。

  那么考虑容斥，钦定多少个 $i$ 满足 $2(X_i+X_{i+1})>k$。易发现不超过两个，且如果有两个当且仅当时相邻的两项，否则 $2(X_i+X_{i+1})+2(X_j+X_{j+1})>2k\Rightarrow X_i+X_{i+1}+X_j+X_{j+1}>k$，不满足 $k$ 的定义。

  1. 不钦定 $2(X_i+X_{i+1})>k$。

     即选 $n$ 个 $\leq m$ 的数使和为 $k$。

     再容斥一下，考虑有多少个 $X_i\gt m$。

     把式子列出来：$\sum\limits_{i=0}^k[2\mid i]\sum\limits_{j=0}^{\min(n,\frac{i}{m+1})}(-1)^j\dbinom{n}{j}\dbinom{i-j(m+1)+n-1}{n-1}\\=\sum\limits_{j=0}^{\min(n,\frac{k}{m+1})}(-1)^j\dbinom{n}{j}\sum\limits_{i=j(m+1)}^{k}[2\mid i]\dbinom{i-j(m+1)+n-1}{n-1}$。

     发现等式右侧的第二个求和中 $-j(m+1)+n-1,n-1$ 都是定值，$i-j(m+1)$ 构成了从 $0$ 开始的一个前缀，可分别预处理 $2\mid i,2\nmid i$ 时 $\dbinom{i+n-1}{n-1}$ 的前缀和，复杂度是 $O(nm)$。

  2. 钦定 $p$ 使得 $2(X_p,X_{p+1})\gt k$。发现 $p$ 具体的位置不重要，只需求出 $p$ 的一种情况再乘 $n$ 即可。

     枚举 $X_p+X_{p+1},k-X_p-X_{p+1}$，分别是 $x,y$，可能会疑惑后 $k$ 的值域不会很大吗？但是若 $2(X_p+X_{p+1})>k$，则 $k\leq 4m-1$。因此枚举的复杂度是 $O(m^2)$。

     接下来分别记数，首先要求 $2x\gt y,x+y\leq k,2\mid (x+y)$。

     - 对于 $X_p+X_{p+1}$，即要求 $\sum\limits_{i=0}^m\sum\limits_{j=0}^m[i+j=x]$，可以快速预处理。

     - 对于 $y$，及要求有多少中方法，选 $n-2$ 个数，每个数 $\in[0,m]$，和为 $y$。

       这部分可以用一个背包，设 $f_{i,j}$ 表示 $i$ 个 $[0,m]$ 的数，和为 $j$ 的方案数。

       转移可以前缀和优化，复杂度 $O(nm)$。

  3. 钦定 $p$ 使得 $2(X_{p-1}+X_p)\gt k,2(X_p+X_{p+1})\gt k$。同样是考虑一个 $p$ 然后乘 $n$。

     要考仔细虑枚举的东西，我们大概只能枚举两个，其余的预处理。

     $X_{p-1},X_{p+1}$ 是相对对称的，$k-X_{p-1}-X_{p}-X_{p+1}$ 几乎是一定要枚举的。

     而 $X_{p-1}$ 和 $X_{p+1}$ 都和 $X_p$ 分别有关系，不能一起枚举，因此枚举 $X_{p},k-X_{p-1}-X_p-X_{p+1}$，分别为 $x,y$。

     接下来分别记数：

     - 对于 $X_{p}$，系数为 $1$。

     - 对于 $y$，直接调用 $f_{n-3,y}$。

     - 然后我们就要求 $X_{p-1}=i,X_{p+1}=j$ 满足一些条件：

       - $2\mid(i+j+x+y)$
       - $i+x\gt y+j$
       - $j+x\gt y+i$
       - $i,j\in[0,m]$
       - $i+j+x+y\leq k$

       第二条和第三条合成一下：$|i-j|\gt y-x$。

       设 $val_{o,s,t}$ 表示奇偶性为 $o,x=s,y=t$ 时的系数。

       我们可以枚举 $i,j$，然后相当于在 $val_{(i+j)\bmod 2}$ 的表中矩形加。

       可以打标机，再做一次前缀和，预处理出 $val$，预处理和求解的复杂度均为 $O(m^2)$。

​	总复杂度 $O(m(n+m)+k)$，很牛。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}

const int N=3005,mod=998244353;
int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
void Fplus(int&x,int y){x=fplus(x,y);}
void Fminus(int&x,int y){x=fminus(x,y);}
int fpow(int x,int k=mod-2){
	int res=1;
	for(;k;k>>=1){
		if(k&1)res=(ll)res*x%mod;
		x=(ll)x*x%mod;
	}
	return res;
}
int fac[N*N],ifac[N*N],n,m,k,ans,f[N][N*2],g[N][N*2],A,B,C;
int pre[N*N],val[2][N*4][N];
int Comb(int x,int y){return (ll)fac[x]*ifac[y]%mod*ifac[x-y]%mod;}

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	n=read(),m=read(),k=read()/2*2;
	fac[0]=1;
	rep(i,1,k+n)fac[i]=(ll)fac[i-1]*i%mod;
	ifac[k+n]=fpow(fac[k+n]);
	per(i,k+n,1)ifac[i-1]=(ll)ifac[i]*i%mod;
	rep(i,0,k){
		pre[i]=fplus((i-2>=0?pre[i-2]:0),Comb(i+n-1,n-1));
	}
	rep(i,0,min(n,k/(m+1))){
		((i&1)?Fminus:Fplus)(A,(ll)Comb(n,i)*pre[k-(m+1)*i]%mod);
	}
	f[0][0]=1;
	int lim=min(m+m-1,k);
	rep(i,0,lim)g[0][i]=1;
	rep(i,1,n){
		rep(j,0,lim){
			f[i][j]=fminus(g[i-1][j],j>m?g[i-1][j-m-1]:0);
			g[i][j]=fplus(f[i][j],j?g[i][j-1]:0);
		}
	}
	rep(i,1,m+m)rep(j,0,min(i-1,k-i))if(!((i^j)&1)){
		Fplus(B,(ll)min(i+1,m+m-i+1)*f[n-2][j]%mod);
	}
	lim=min(k,4*m-1);
	rep(i,0,m)rep(j,0,m)if(i+j<=lim){
		int o=((i^j)&1);
		val[o][1][abs(i-j)+1]++;
		val[o][lim-i-j+1][abs(i-j)+1]--;
	}
	rep(o,0,1)rep(i,1,lim)rep(j,1,m){
		val[o][i][j]+=val[o][i-1][j]+val[o][i][j-1]-val[o][i-1][j-1];
	}
	rep(t,1,m)rep(s,0,min(t-1,lim-t)){
		Fplus(C,(ll)val[(s^t)&1][s+t][t-s]*f[n-3][s]%mod);
	}
	B=(ll)n*B%mod,C=(ll)n*C%mod;
	printf("%d\n",fplus(fminus(A,B),C));
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# ARC156E 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_arc156_e)

**题目大意**

> 给定 $n$ 个点 $1\sim n$，定义一张图是好的需要满足：
>
> - $(1,2),(2,3),\dots,(n,1)$ 之间没有边。
> - 每个点度数 $\le m$。
> - 所有点度数和 $\le k$。
>
> 求有多少 $x_1\sim x_n$ 可以作为一张好图的度数序列。
>
> 数据范围：$n,m\le 3000,k\le nm$。

**思路分析**

记 $S=\sum_{i=1}^n x_i$，一组序列合法当且仅当：

- $2\mid S,S\le k$。
- $\forall i\in [1,n]$ 满足 $x_i+x_{i+1}\le S/2$。
- $\forall i\in[1,n]$ 满足 $x_i\in[0,m]$。

可以验证这就是合法的充要条件，构造每次取一个 $x_i+x_{i+1}=S/2$ 的点和任意一个其他的点连起来即可。

然后考虑对这样的序列计数。

我们容斥枚举 $x_i+x_{i+1}>S/2$ 的位置数，容易证明不满足的位置 $\le 2$ 个。

先考虑没有钦定位置的情况，直接容斥得到方案数为：
$$
\sum_{S=0}^k[2\mid S]\sum_{i=0}^n(-1)^i\binom ni\binom{S+n-1-(m+1)i}{n-1}
$$
对于 $S\in[0,k]$，最后一个式子是若干组合数的前缀和，对上指标奇偶性分类即可。

然后考虑钦定一个位置的情况：

枚举这两个位置的和 $t$，暴力枚举这两个位置的所有分配，那么剩余位置的和 $<t$ 且 $\le k-t$。

dp 预处理求出 $n-2$ 个 $[0,m]$ 中变量凑出 $<t$ 的方案总和，容易发现 $t\le 2m$，因此前缀和优化 dp，时间复杂度为 $\mathcal O(nm)$。

由于还要钦定具体位置，所以最后答案记得 $\times n$。

对于钦定两个位置的情况，容易发现这两个位置一定相邻。

设对应的三个元素分别为 $x,t,y$，剩余部分的和为 $s$，那么所有限制为:
$$
\begin{cases}
x+t<y+s\\
t+y<s+x\\
x+s+t+y\le k\\
2\mid x+s+t+y
\end{cases}
\implies 
\begin{cases}
|y-x|<t-s\\
y+x\le k-t-s\\
y+x\equiv t-s \pmod 2
\end{cases}
$$
可以对所有 $(x,y)$ 二维前缀和出数量，枚举 $s,t$ 即可，对于剩下 $n-3$ 个元素的方案同样用 dp 出来的结果即可。

这一部分的答案也要记得 $\times n$。

时间复杂度 $\mathcal O(k+nm)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3005,MAXV=1e7+5,MOD=998244353;
void add(ll &x,ll y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
void sub(ll &x,ll y) { x=(x>=y)?x-y:x+MOD-y; }
ll fac[MAXV],ifac[MAXV];
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b=b>>1) if(b&1) ret=ret*a%p;
	return ret;
}
ll binom(int n,int m) {
	if(n<0||m<0||m>n) return 0;
	return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;
}
ll bs[MAXV][2],dp[MAXN][MAXN<<1],sum[MAXN<<1];
int cnt[MAXN][MAXN<<1][2];
signed main() {
	fac[0]=1;
	for(int i=1;i<MAXV;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[MAXV-1]=ksm(fac[MAXV-1]);
	for(int i=MAXV-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	ll ans0=0,ans1=0,ans2=0;
	for(int i=0;i<=k;++i) {
		if(i) bs[i][0]=bs[i-1][0],bs[i][1]=bs[i-1][1];
		add(bs[i][i&1],binom(i+n-1,n-1));
	}
	for(int i=0,t=0;i<=n&&t<=k;++i,t+=m+1) {
		ans0=(ans0+(i&1?-1:1)*binom(n,i)*bs[k-t][t&1])%MOD;
	}
	if(ans0<0) ans0+=MOD;
	dp[0][0]=1;
	for(int i=1;i<=n;++i) {
		ll s=0;
		for(int j=0;j<=2*m;++j) {
			add(s,dp[i-1][j]),dp[i][j]=s;
			if(j>=m) sub(s,dp[i-1][j-m]);
		}
	}
	for(int t=1;t<=2*m&&t<=k;++t) {
		ll co=0,tmp=0;
		for(int x=0;x<=m;++x) if(0<=t-x&&t-x<=m) ++co;
		for(int s=t&1;s<t&&s+t<=k;s+=2) tmp+=dp[n-2][s];
		ans1=(ans1+tmp*co)%MOD;
	}
	for(int x=0;x<=m;++x) for(int y=0;y<=m;++y) ++cnt[abs(x-y)][x+y][(x+y)%2];
	for(int i=0;i<=m;++i) for(int j=0;j<=2*m;++j) for(int r:{0,1}) {
		if(i) cnt[i][j][r]+=cnt[i-1][j][r];
		if(j) cnt[i][j][r]+=cnt[i][j-1][r];
		if(i&&j) cnt[i][j][r]-=cnt[i-1][j-1][r];
	}
	for(int t=0;t<=m;++t) for(int s=0;s<t&&s+t<=k;++s) {
		//|y-x|<t-s, y+x<k-t-s, y+x%2==(t-s)%2
		ans2=(ans2+cnt[t-s-1][min(2*m,k-t-s)][(t-s)%2]*dp[n-3][s])%MOD;
	}
	printf("%lld\n",(ans0+n*(ans2+MOD-ans1))%MOD);
	return 0;
}
```

---

## 作者：Feyn (赞：0)

[更多的 ARC 题目](https://www.cnblogs.com/Feyn/p/16977678.html)

我应该学会数数。

首先考虑什么样的数列是合法的。首先和是偶数。如果没有相邻点不能相连的限制的话有一个限制是说不能有一个点的度数找过一半（不然一定出现自环），考虑这个限制之后相当于不存在相邻点的度数之和严格超过一半。充分性和必要性很好证明，接下来考虑如何计数。

直接做不好做，考虑容斥，发现这道题里需要容斥的情况异常的少，只有一对相邻点度数超标、相邻两对点度数分别超标的情况，不存在更多的情况是因为如果两对不相交的相邻点都不合法，那么总度数不久超标了。于是思考如何对上面两种情况计数，只需要枚举超标的那一对点的度数和是什么并计算方案、枚举那三个点大概的度数是什么并计算方案即可，计算方案等价于希望让一些取值在 $[0,x]$ 中的数和为 $t$ 并求方案数，这个问题是经典的，做好记忆化的话稍微分析一下就能发现复杂度大概是 $O(nm+k)$。

似乎没什么了，细节有点多，需要对当前要求的东西有清晰的认知不然很容易出问题，但都很好理解，我也不知道为什么我卡了很一会。也可以参照代码加深理解。

```cpp
#include<bits/stdc++.h>
// #define Feyn
#define int long long
using namespace std;
const int N=10000010;
const int mod=998244353;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int num,lim,sum;

int p[N],q[N],inv[N];
void initC(){
    p[0]=p[1]=q[0]=q[1]=inv[0]=inv[1]=1;
    for(int i=2;i<N;i++){
        p[i]=p[i-1]*i%mod;
        inv[i]=inv[mod%i]*(mod-mod/i)%mod;
        q[i]=q[i-1]*inv[i]%mod;
    }
}
inline int ask(int s1,int s2){
    if(s1<0||s2<0||s1<s2)return 0;
    return p[s1]*q[s1-s2]%mod*q[s2]%mod;
}
inline void add(int &s1,int s2){
    s1=(s1+s2)%mod;
}

namespace feyn{
    int n,preSum[N][2],rec[2][N];
    void init(){
        memset(preSum,0,sizeof(preSum));
        memset(rec,-1,sizeof(rec));
        for(int x=0;x<=sum;x++){
            if(x)preSum[x][0]=preSum[x-1][0],preSum[x][1]=preSum[x-1][1];
            add(preSum[x][x&1],ask(x+n-1,n-1));
        }
    }
    int work(int val,bool want){
        if(val<0)return 0;
        if(rec[want][val]>=0)return rec[want][val];
        int ans=0;
        for(int i=0;i<=n&&i*(lim+1)<=val;i++){
            int now=(i%2?-1:1)*ask(n,i);
            add(ans,now*preSum[val-i*(lim+1)][want^(i*(lim+1)&1)]);
        }
        return rec[want][val]=(ans%mod+mod)%mod;
    }
}

int cnt[N];

signed main(){
	
	#ifdef Feyn
	freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    read(num);read(lim);read(sum);
    initC();int ans=0;
    feyn::n=num;feyn::init();
    ans+=feyn::work(sum,0);

    feyn::n=num-2;feyn::init();
    for(int s=0;s<=lim*2&&s<=sum;s++){
        int preNum=min(lim,s)-max(0ll,s-lim)+1;
        add(ans,-feyn::work(min(sum-s,s-1),s&1)*preNum%mod*num);
    }
    feyn::n=num-3;feyn::init();
    for(int mn=0;mn<=lim*2;mn++){
        for(int mx=0;mx<=lim;mx++){
            if(mn+mx>sum)continue;
            int preNum=min(mx,min(lim,mn))-max(0ll,mn-lim)+1;
            if(preNum<=0)continue;
            preNum*=2;
            if(mn-mx>=0&&mn-mx<=lim)--preNum;
            add(ans,preNum*feyn::work(min(sum-mn-mx,mn-mx-1),mx+mn&1)%mod*num);
        }
    }
    printf("%lld\n",(ans%mod+mod)%mod);

    return 0;
}
```

---

