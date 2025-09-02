# Encryption (hard)

## 题目描述

Heidi is now just one code away from breaking the encryption of the Death Star plans. The screen that should be presenting her with the description of the next code looks almost like the previous one, though who would have thought that the evil Empire engineers would fill this small screen with several million digits! It is just ridiculous to think that anyone would read them all...

Heidi is once again given a sequence $ A $ and two integers $ k $ and $ p $ . She needs to find out what the encryption key $ S $ is.

Let $ X $ be a sequence of integers, and $ p $ a positive integer. We define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given integers $ k $ and $ p $ . Her goal is to split $ A $ into $ k $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- No two parts overlap.
- The total sum $ S $ of the scores of those parts is minimized (not maximized!).

Output the sum $ S $ , which is the encryption code.

## 说明/提示

In the first example, if the input sequence is split as $ (3) $ , $ (4,7) $ , $ (2) $ , the total score would be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C3/d85b82846e8d0ea943e5dbc022fe9af7d9ee19d2.png). It is easy to see that this score is the smallest possible.

In the second example, one possible way to obtain score $ 13 $ is to make the following split: $ (16,3) $ , $ (24) $ , $ (13) $ , $ (9,8) $ , $ (7,5,12,12) $ .

## 样例 #1

### 输入

```
4 3 10
3 4 7 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
10 5 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
13
```

# 题解

## 作者：MyukiyoMekya (赞：25)

神仙题。

我们先不考虑优化 $\mathcal O(nkp)$ 那个做法，考虑优化 $\mathcal O(n^2k)$ 那个暴力 dp。

$f_{i,j}$ 表示前 $i$ 个数分为 $j$ 段的最小和，枚举转移点 $k$ ：$f_{i,j}=\min\{f_{k,j-1}+(s_i-s_k\mod p)\}$，其中 $s_n=\sum_{i=1}^na_i$。

这时候要注意到一个性质，$f_{i,j}\equiv s_i \pmod p $。

那么对于 $f_{i,j}$ 的两个转移点 $x,y(x\ne y,x,y <i)$  ，设 $w_x=(s_i-s_x \bmod p),w_y = (s_i-s_y\bmod p)$

那么就是要在这两个里面选最小的：$f_{x,j-1}+w_x,f_{y,j-1}+w_y$，

有 $f_{x,j-1}+w_x\equiv f_{y,j-1}+w_y \pmod p$

假设 $f_{x,j-1}<f_{y,j-1}$ ，由于 $w_x,w_y<p$，所以说无论如何 $f_{x,j-1}+w_x$ 也不可能比 $f_{y,j-1}+w_y$ 大。

$f_{x,j-1}=f_{y,j-1}$ 的时候那么 $w_x$ 一定和 $w_y$ 相同。

那么对于每个 $j$ 记一下最小的 $f_{k,j}$ 的位置 $k$ 即可，从这个 $k$ 转移过来一定是最优的。时间复杂度 $\mathcal O(nk)$

```cpp
// This code wrote by chtholly_micromaker(Myukiyomekya)
#include <bits/stdc++.h>
template <class t>inline bool ckmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
const int MaxN=5e5+50;
int f[MaxN][105],a[MaxN],g[2][105],n,K,p;
inline int fix(int x){return (x%p+p)%p;}
signed main(void)
{
	std::scanf("%d%d%d",&n,&K,&p);
	for(int i=1;i<=n;++i)std::scanf("%d",&a[i]),(a[i]+=a[i-1])%=p;
	std::memset(f,0x3f,sizeof(f));
	f[0][0]=0,g[0][0]=0;
	for(int i=1;i<=n;++i)
	{
		int fp=(i&1)^1;
		for(int j=1;j<=K;++j)
			ckmin(f[i][j],f[g[fp][j-1]][j-1]+fix(a[i]-a[g[fp][j-1]]));
		for(int j=0;j<=K;++j)
		{
			g[i&1][j]=g[fp][j];
			if(f[i][j]<f[g[i&1][j]][j])g[i&1][j]=i;
		}
	}
	std::printf("%d\n",f[n][K]);
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：6)

# 题目大意

有一个包含 $n$ 个正整数的数列，将这个数列分成 $m$ 个非空段，每段的价值为这段的所有数总和 $\bmod~p$，你需要使 $k$ 段价值总和最小，请求出这个最小值。

# 题目分析

先有 $\mathcal{O(n^2m)}$ 做法：

令 $dp[i][j]$ 表示前 $i$ 个数分 $j$ 组的最小值。

有 $dp[i][j]=\min\{dp[k][j-1]+(sum[i]-sum[k])\bmod p\}$。

-----

考虑怎么优化，注意到我们 $dp[i][j]$ 的最小值的求解是从 $\min\{dp[k][j-1]\}$ 里来的，但是单纯记录最小值还不行，我们还要记录位置（$sum[k]$），然后就做完了。

正确性证明：

首先 $sum$ 数组一定严格单调递增，因为 $\forall i\in [1,n],a[i]\in[1,10^6]$。其次我们可以发现 $dp[i][j]\equiv sum[i](\bmod p)$，因为 $(a+b)\bmod p=a\bmod p+b\bmod p$。

所以找到两个 $x,y$，我们要做的其实就是求出 $dp[x][j-1],dp[y][j-1]$ 的最小值，设 $w[x]=(sum[i]-sum[x])\bmod p,w[y]=(sum[i]-sum[y])\bmod p$。

又因为 $dp[i][j]\equiv dp[i][j](\bmod p)$，

故 $dp[x][j-1]+w[x]\equiv dp[y][j-1]+w[y](\bmod p)$。

不妨设 $dp[x][j-1]\lt dp[y][j-1]$，因为 $w[x],w[y]\lt p$，所以 $dp[x][j-1]+w[x]\lt dp[y][j-1]+w[y]$。

所以我们有了思路：对于每个 $j$，记录最小的 $dp[k][j]$ 的位置 $k$，转移时就能 $\mathcal{O(1)}$ 转移了。

总时间复杂度 $\mathcal{O(nm)}$。

# 代码

```cpp
// Problem: CF958C3 Encryption (hard)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF958C3
// Memory Limit: 500 MB
// Time Limit: 2200 ms
// Date:2022-05-21 16:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 5e5 + 5,M = 105;
struct Rem {
	int Max,pos;
} ;
int a[N],sum[N],dp[N][M],g[2][M];
//dp[i][j]:前 i 个数分成 j 组的最小和
int n,m,p;
int main(void) {
	n = read(),m = read(),p = read();
	for (register int i = 1;i <= n; ++ i) {
		a[i] = read();
		sum[i] = (sum[i - 1] + a[i]) % p;
	}
	mst(dp,0x3f);
	dp[0][0] = 0;
	// for (register int i = 1;i <= n; ++ i) dp[i][1] = sum[i];
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = 1;j <= m; ++ j) {
			dp[i][j] = std::min(dp[i][j],dp[g[i & 1 ^ 1][j - 1]][j - 1] + ((sum[i] - sum[g[i & 1 ^ 1][j - 1]]) % p + p) % p);
		}
		for (register int j = 0;j <= m; ++ j) {
			g[i & 1][j] = g[i & 1 ^ 1][j];
			if (dp[i][j] < dp[g[i & 1][j]][j]) {
				g[i & 1][j] = i;
			}
		}
	}
	printf("%d\n",dp[n][m]);
	
	return 0;
}
```

---

## 作者：墨染琉璃殇 (赞：4)

蒟蒻的第二篇题解。

本蒟蒻之前交了下C2的题解，然后又来交C3了…

### 思路如下：
和上一道题（[CF958C2](https://www.luogu.com.cn/problem/CF958C2)）类似，考虑到普通的dp难以通过本题，所以必须从本题的性质入手。

设A数组的前缀和对p取模的值为 $pre$，经过分析，发现当 $n>=k*p$ 时，答案只能为  $pre[n]$ 或 $pre[n]+p$ 。因为必有一个x满足 $pre[y]=x$ 的 $y$ 超过  $k$ 个。

然后发现答案为 $pre[n]$  当且仅当 $pre$ 的以 $n$ 为结尾的**最长不下降子序列** $>=k$ 。于是当 $n>=k*p$ 时，我们只需要求**最长不下降子序列**即可，用数据结构优化即可做到 $O(nlogn)$ ，这里我用的是**树状数组**优化，其他也行。

当 $n<k*p$ 时， $n<10000$ ，可以用上题的做法就能通过。

然后就这样了......

$AC$ $Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,p;
int dp[111][555555],cur[111],a[555555],ld[111],sum[555555],dpp[555555],bit[1111],sz;
void update(int x,int p)
{
	while(x<=sz)
	{
		bit[x]=max(bit[x],p);
		x+=x&(-x);
	}
}
int query(int x)
{
	int res=0;
	while(x>=1)
	{
		res=max(res,bit[x]);
		x-=x&(-x);
	}
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for (int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		a[i]%=p;
	}
	if (k*p>=n)
	{
		for (int i=0;i<=k;i++) 
		{
			for (int j=0;j<=n;j++) 
			dp[i][j]=1e9;
		}
		dp[0][0]=0;
		for (int i=1;i<=k;i++)
		{
			for (int j=0;j<p;j++) cur[j]=1e9;
			for (int j=1;j<=n;j++)
			{
				for (int h=0;h<p;h++) ld[(h+a[j])%p]=cur[h];
				for (int h=0;h<p;h++) cur[h]=ld[h];
				cur[a[j]]=min(cur[a[j]],dp[i-1][j-1]);
				for (int h=0;h<p;h++) dp[i][j]=min(dp[i][j],cur[h]+h);
			}
		}
		cout<<dp[k][n]<<endl;
	}
	else
	{
		for (int i=1;i<=n;i++) sum[i]=(sum[i-1]+a[i])%p;
		sz=1;
		while(sz<p) sz*=2;
		for (int i=1;i<=n;i++)
		{
			dpp[i]=query(sum[i]+1)+1;
			update(sum[i]+1,dpp[i]);
		}
		if (dpp[n]>=k) cout<<sum[n]<<endl;
		else cout<<sum[n]+p<<endl;
	}
	return 0;
}
```

$Thanks$



~~思路来自老师的讲解......~~

---

## 作者：Purslane (赞：3)

# Solution

简单 $\rm DP$ 题。

设 $dp_{u,i}$ 为前 $u$ 个数分为 $i$ 段的最少代价。

注意到转移的时候，假设我们要从 $dp_{u,i}$ 转移到 $dp_{v,i+1}$ 的时候，答案为 $dp_{u,i} + | pre_v - pre_{u}|$。

注意到 $pre_v$ 是确定的，因此我们只需要记录 $pre_u$ 相同时 $dp_{u,i}$ 的最小值，额还是 $O(npk)$ 的。不过拆绝对值之后可以树状数组优化，$O(nk \log p)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500000+10,MAXK=100+10;
int n,k,p,a[MAXN],dp[MAXN][MAXK],pre[MAXK][MAXK],suf[MAXK][MAXK];
void update(int pos,int v,int id,int op) {
	if(op==0) {pos++;while(pos<=p+1) pre[id][pos]=min(pre[id][pos],v),pos+=pos&-pos;return ;}
	else {pos=p+1-pos;while(pos<=p+1) suf[id][pos]=min(suf[id][pos],v),pos+=pos&-pos;return ;}
}
int query(int pos,int id,int op) {
	int mx=0x3f3f3f3f;
	if(op==0) {pos++;while(pos) mx=min(mx,pre[id][pos]),pos-=pos&-pos;return mx;}
	else {pos=p+1-pos;while(pos) mx=min(mx,suf[id][pos]),pos-=pos&-pos;return mx;}
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k>>p;
	ffor(i,1,n) cin>>a[i],a[i]=(a[i]+a[i-1])%p;
	memset(dp,0x3f,sizeof(dp)),memset(pre,0x3f,sizeof(pre)),memset(suf,0x3f,sizeof(suf));
	update(0,0,0,0),update(0,0,0,1);
	ffor(i,1,n) {
		ffor(j,1,k) dp[i][j]=min(query(a[i],j-1,0)+a[i],query(a[i]+1,j-1,1)+a[i]+p);
		ffor(j,1,k) update(a[i],dp[i][j]-a[i],j,0),update(a[i],dp[i][j]-a[i],j,1);
	}
	cout<<dp[n][k];
	return 0;
}
```

---

## 作者：TernaryTree (赞：3)

首先有一个朴素的 dp，$f_{i,j}$ 表示 $[1,i]$ 被分成 $j$ 段的最小价值和。则

$$f_{i,j}=\min_{k=1}^{i-1}f_{k,j-1}+(s_i-s_k)\bmod p$$

$s$ 表示 $a$ 的前缀和。

我们考虑两个决策点 $k_1$ 和 $k_2$。

决策点 $k_1$ 值为：$v_{k_1}=f_{k_1,j-1}+(s_i-s_{k_1})\bmod p$。

决策点 $k_2$ 值为：$v_{k_2}=f_{k_2,j-1}+(s_i-s_{k_2})\bmod p$。

大眼观察法。注意到两者模 $p$ 同余。证明：

> 显然有 $f_{k,j}\equiv s_k$。这是因为 $f_{k,j}$ 一定是 $a_{[1,k]}$ 切成若干段模 $p$ 的和，这与 $s_k$ 是模意义下相等的。

移项即证毕。

我们不妨设 $f_{k_1,j-1}<f_{k_2,j-1}$。若 $v_{k_1}>v_{k_2}$，则 $v_{k_1}=v_{k_2}+xp$，得到 $(s_i-s_{k_1})\bmod p> xp$，这显然是矛盾的。故此时必有 $v_{k_1}\le v_{k_2}$，$k_1$ 是一个更好的决策点。也就是说，当 $f_{k_0,j-1}$ 为 $\{f_{k,j-1}\mid 1\le k\lt i\}$ 的最小值，就有 $f_{i,j}=v_{k_0}$。

使用一个 $g_{i,j}$ 表示最优决策即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5 + 10;
const int maxk = 1e2 + 10;;

int n, k, p;
int a[maxn], s[maxn];
int f[maxn][maxk];
int g[maxn][maxk];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> p;
	for (int i = 1; i <= n; i++) cin >> a[i], s[i] = (s[i - 1] + a[i]) % p;
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for (int j = 1; j <= k; j++) {
		g[0][j] = 0;
		for (int i = 1; i <= n; i++) {
			if (f[i][j - 1] < f[g[i - 1][j]][j - 1]) g[i][j] = i;
			else g[i][j] = g[i - 1][j];
		}
		for (int i = j; i <= n; i++) {
			int k = g[i - 1][j];
			f[i][j] = f[k][j - 1] + (s[i] - s[k] + p) % p;
		}
	}
	cout << f[n][k];
	return 0;
}
```

---

## 作者：Z_M__ (赞：2)

先考虑一下 $O(n^2k)$ 的 DP ，设 $f[i][j]$ 为到第 $i$ 位，分 $j$ 段的最小价值, 那么转移很简单，
 
 为 $f[i][l + 1] = \min (f[i][l + 1], f[j][l] + (a[i] - a[j]) \%p $, 其中 $a[i]$ 表示 $1-i$ 的前缀和。
代码如下：
```cpp
for (int i = 1; i <= n; i++)
	for (int j = 1; j < i; j++)
		for (int l = 1; l < i; l++)
			f[i][l + 1] = min (f[i][l + 1], f[j][l] + (a[i] - a[j]) % p);
```

 上面的 DP 肯定会超时，考虑优化一下上面的 DP。我们发现在更新 $f[i][l + 1]$ 时，其实就是在找 $1$ 到 $(i-1)$ 中分成 $l$ 段的最小值, 那我们可以将【前 $i-1$ 个数分成 $l$ 段的最小值】存下来，没必要每次都 $O(n)$ 向前找一遍, 这样时间复杂度为 $O(nk)$。
 
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5 + 10;
int n, k, p, a[MAXN], f[MAXN][111], g[111], id[111], tg[111], tid[111]; 
// g数组就是存储分成 l 段的最小值，id存储最小值所在的位置，tg、tid见下面的代码
signed main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n >> k >> p;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] += a[i - 1];
	}
	memset (g, 0x3f, sizeof (g));
	for (int i = 1; i <= n; i++)
	{
		f[i][1] = (a[i]) % p;
		for (int j = 1; j <= k; j++)
			tg[j] = g[j], tid[j] = id[j]; // tg和tid用来临时存储这一轮的最小值
		if (g[1] > f[i][1])
		{
			tg[1] = f[i][1]; // 不能直接改g数组，不然后面可能出现，f[i][l + 1] = f[i][l] + (a[i] - a[i]) % p，这不符合题意（每段都要为非空段）
			tid[1] = i;
		}
		for (int j = 1; j < min (i, k + 1); j++)
		{
			f[i][j + 1] = g[j] + (a[i] - a[id[j]]) % p;
			if (f[i][j + 1] < g[j + 1])
			{
				tg[j + 1] = f[i][j + 1];
				tid[j + 1] = i;
			}
		}
		for (int j = 1; j <= k; j++)
			g[j] = tg[j], id[j] = tid[j]; // 将修改后的最小值赋给g
	}
	cout << f[n][k] << endl;
	return 0;
}
 ```

---

## 作者：2huk (赞：1)

显然 DP。设 $f(i, j)$ 表示考虑前 $i$ 个数，划分成 $j$ 段的答案。

令 $s_i = (a_1+a_2+\dots + a_i) \bmod p$。转移 $f(k,j-1) + (s_i-s_k) \bmod p \to f(i, j)$。

注意到 $s_i - s_k = \begin{cases} s_i - s_k & s_i \ge s_k \\ s_i - s_k + p & s_i < s_k \end{cases}$。于是可以把 DP 式子重写：

$$
\begin{aligned}
f(i,j)&=\min_{k=0}^{i-1} f(k,j-1) + (s_i-s_k) \bmod p \\ &=
s_i + \min_{k=0}^{i-1} f(k,j-1) - s_k + [s_i \ge s_k]p
\end{aligned}
$$

开两个树状数组。第一个维护所有满足 $s_k \le s_i$ 的 $f(i,j-1)-s_k$ 的最小值，第二个维护所有满足 $s_k \ge s_i+1$ 的 $f(i,j-1)-s_k$ 的最小值。转移就可以优化到 $\log p$ 了。

复杂度 $\mathcal O(nm\log p)$。需要卡常，比如把 `int` 换成 `short`。

```cpp
// Problem: 
//     Encryption (hard)
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF958C3
// Memory Limit: 500 MB
// Time Limit: 2200 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #define tests
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, m, p;
int a[N];
short f[N][110];

inline int min(const int a, const int b) {
	return a < b ? a : b;
}

struct Tree1 {
	short tr[110];
	void clear() { memset(tr, 0x3f, sizeof tr); }
	
	void modify(short x, short d) {
		x ++ ;
		for (short i = x; i < 110; i += i & -i) tr[i] = min(tr[i], d);
	}
	
	short query(short x) {
		x ++ ;
		short res = 32767;
		for (short i = x; i; i -= i & -i) res = min(res, tr[i]);
		return res;
	}
}T1;

struct Tree2 {
	short tr[110];
	void clear() { memset(tr, 0x3f, sizeof tr); }
	
	void modify(short x, short d) {
		x = 110 - x;
		for (short i = x; i < 110; i += i & -i) tr[i] = min(tr[i], d);
	}
	
	short query(short x) {
		x = 110 - x;
		short res = 32767;
		for (short i = x; i; i -= i & -i) res = min(res, tr[i]);
		return res;
	}
}T2;

void solve() {
	cin >> n >> m >> p;
	
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		a[i] = (a[i] + a[i - 1]) % p;
		f[i][1] = a[i];
	}
	
	for (short j = 2; j <= m; ++ j ) {
		T1.clear(), T2.clear();
		
		T1.modify(a[0], f[0][j - 1] - a[0]);
		T2.modify(a[0], f[0][j - 1] - a[0]);
		for (int i = 1; i <= n; ++ i ) {
			f[i][j] = i >= j ? a[i] + min(T1.query(a[i]), T2.query(a[i] + 1) + p) : 32767;
			T1.modify(a[i], f[i][j - 1] - a[i]);
			T2.modify(a[i], f[i][j - 1] - a[i]);
		}
	}
	
	cout << f[n][m] << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：Charlie_ljk (赞：1)

先写出 $O(n^2k)$ 的转移方程：

$$f_{i,k}=\min\limits_{j=k-1}^{i-1}\{f_{j,k-1}+(sum_i-sum_j)\bmod p\}$$

发现对于每个 $f_{i,*}$ 其 $\bmod p$ 的值恒等于 $sum_i \bmod p$，那么对于两个转移点 $x,y$，有：

$$f_{x,k-1}+(sum_i-sum_x)\bmod p\equiv f_{y,k-1}+(sum_i-sum_y)\bmod p\pmod p$$

若 $f_{x,k-1}<f_{y,k-1}$，因为 $(sum_i-sum_j)\bmod p<p$，所以一定有 $f_{x,k-1}+(sum_i-sum_x)\bmod p\le f_{y,k-1}+(sum_i-sum_y)\bmod p$。

所以直接记录最优策略即可，复杂度 $O(nk)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=5e5+10;
template<typename Tp> inline void read(Tp&x)
{
    x=0;register bool z=true;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
    for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    x=(z?x:~x+1);
}
void wt(int x){if(x>9)wt(x/10);putchar((x%10)+'0');}
void write(int x){if(x<0)putchar('-'),x=~x+1;wt(x);}
int n,m,p,f[N][2],sum[N],lastx[N],lasty[N];
signed main()
{
    read(n),read(m),read(p);
    for(int i=1,a;i<=n;i++)
        read(a),sum[i]=sum[i-1]+a;
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int j=1;j<=m;j++)
    {
        int minn=f[j-1][(j-1)&1],ans=j-1;
        for(int i=j;i<=n;i++)
        {
            f[i][j&1]=minn+(sum[i]-sum[ans])%p;
            if(f[i][(j-1)&1]<minn) 
            {
                minn=f[i][(j-1)&1];
                ans=i;
            }
        }
    }
    write(f[n][m&1]);
}
```

---

## 作者：Hoks (赞：1)

## 前言
比较有意思的 dp 题，思路类似于 CF958C2。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先考虑下最朴素的思路，设计 $f_{i,j}$ 表示前 $i$ 个数分成 $j$ 段的最小值，并处理出前缀和 $s$。

那么转移直接考虑枚举断点 $k$，方程式即为 
$$f_{i,j}=\min(f_{k,j-1}+(s_i-s_k)\bmod p)$$
这样的复杂度是 $O(n^2k)$ 的，考虑优化。

$n$ 降掉得到 $O(nk)$。

因为每次取模只是相当于减去 $k\times p$，所以 $f_{i,j}\equiv s_i(\bmod p)$。

考虑对于两个断点 $x,k$，根据转移方程式可得：
$$f_{x,j-1}+s_i-s_x\equiv f_{i,j}\equiv f_{k,j-1}+s_i-s_k(\bmod p)$$

又因为 $s_i-s_x,s_i-s_k<p$，所以可以得到：
$$f_{x,j-1}<f_{k,j-1}\Leftrightarrow f_{x,j-1}+(s_i-s_x)\bmod p\le f_{k,j-1}+(s_i-s_k)\bmod p$$

原因也很简单，考虑反证：

若 $f_{x,j-1}<f_{k,j-1}$ 且 $f_{x,j-1}+(s_i-s_x)\bmod p>f_{k,j-1}+(s_i-s_k)\bmod p$

设 $(s_i-s_x)\bmod p=a,(s_i-s_k)\bmod p=b$。

则式子变为 $f_{x,j-1}+a>f_{k,j-1}+b$。

$f_{x,j-1}+a\equiv f_{k,j-1}+b(\bmod p)$。

给这两个式子移项得到：
$$a\equiv f_{k,j-1}-f_{x,j-1}+b(\bmod p)$$
$$a>f_{k,j-1}-f_{x,j-1}+b$$
再令 $t=f_{k,j-1}-f_{x,j-1}$，由题设 $f_{x,j-1}<f_{k,j-1}$ 得 $t>0$。

此时 $a_{min}$ 即为 $t+b+p$，而 $a,b\in[0,p)$。

所以 $a=t+b+p>p$ 显然取不到，也就是命题成立。

考虑用 $g_{i,j}$ 存下 $\min(f_{1\sim i-1,j})$ 的位置，直接用这玩意转移即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10,M=110,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f,lim=20;
int n,k,p,s[N],f[N][M],g[2][M];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='0'&&c<='1'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    n=read(),k=read(),p=read();memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++) s[i]=(s[i-1]+read())%p;f[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++) f[i][j]=f[g[i&1][j-1]][j-1]+((s[i]-s[g[i&1][j-1]])%p+p)%p;
        for(int j=0;j<=k;j++) g[i&1^1][j]=f[i][j]<f[g[i&1][j]][j]?i:g[i&1][j];
    }print(f[n][k]);
    genshin:;flush();return 0;
}
```

---

## 作者：立柱已选162534 (赞：1)

一个无脑解法（确信）

显然有 $O(n^2k)$ 的 dp：

设 $a_i$ 的前缀和为 $s_i$，将前 $i$ 个数分为 $k_0$ 段时的答案为 $f_{i,k_0}$，则有 $f_{i,k_0}=\min\limits_{0\le j<i}((s_i-s_j)\bmod p+f_{j,k_0-1})$

由于带取模的转移比较难优化，并且 $a\bmod b=a-b\times\lfloor\frac{a}{b}\rfloor$，考虑让每段之和除以 $p$ 的值之和最大化，即 $f_{i,k_0}=\max\limits_{0\le j<i}(\lfloor\frac{s_i-s_j}{p}\rfloor+f_{j,k_0-1})$，此时答案为 $s_n-p
\times f_{n,k}$。

然而 $\lfloor\frac{s_i-s_j}{p}\rfloor+f_{j,k_0-1}$ 还是不好优化，于是考虑分离为两个只关于 $i$ 或 $j$ 的式子。

由于 $f_{j,k_0-1}$ 为整数，先把它塞入取整符号中，得到 $\lfloor\frac{s_i-s_j}{p}+f_{j,k_0-1}\rfloor$。

将 $\frac{s_i-s_j}{p}$ 分开，得到 $\lfloor\frac{s_i}{p}-\frac{s_j}{p}+f_{j,k_0-1}\rfloor$。

显然，只要使 $\frac{s_i}{p}-\frac{s_j}{p}+f_{j,k_0-1}$ 最优，则 $\lfloor\frac{s_i}{p}-\frac{s_j}{p}+f_{j,k_0-1}\rfloor$ 会最优。

于是，可以把取整符号整个提出 $\max$ 外，同时把 $\frac{s_i}{p}$ 也提出去，即 $f_{i,k_0}=\lfloor\frac{s_i}{p}+\max\limits_{0\le j<i}(-\frac{s_j}{p}+f_{j,k_0-1})\rfloor$

运用类似前缀和的方法计算 $\max\limits_{0\le j<i}(-\frac{s_j}{p}+f_{j,k_0})$ 即可，时间复杂度 $O(nk)$。

[代码](https://codeforces.com/contest/958/submission/253568333)

闲话：用了 [typst](typst.app) 之后用回 markdown 与 $\LaTeX$ 之后有亿点不习惯（

---

## 作者：daniEl_lElE (赞：1)

考虑 $dp_{i,j}$ 表示看到第 $i$ 位，选出 $j$ 段的最小价值。

容易发现 $dp_{i,j}\bmod p$ 是固定的，于是修改状态为看到第 $i$ 位，选出 $j$ 段的最小价值除以 $p$ 的值。

考虑转移，记录前缀和 $\mod p$ 的数组为 $b$。对于所有 $b_i\geq b_{i'}$，可以直接从 $dp_{i',j}$ 转移到 $dp_{i,j+1}$。对于所有 $b_i>b_{i'}$，，可以直接从 $dp_{i',j}+1$ 转移到 $dp_{i,j+1}$。用树状数组维护最小值即可。总复杂度 $O(nk\log n)$，跑的飞快。

```cpp
#pragma GCC optimize("Ofast","inline")
#include <bits/stdc++.h>
#define double long double
#define lowbit(i) (i&(-i))
using namespace std;
int a[500005];
struct bit{
	int f[105];
	void change(int pos,int v){
		while(pos<=100){
			f[pos]=min(f[pos],v);
			pos+=lowbit(pos);
		}
	}
	int qry(int pos){
		int ans=1e9;
		while(pos){
			ans=min(ans,f[pos]);
			pos-=lowbit(pos);
		}
		return ans;
	}
}tree[105];
int minv[105];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,k,p; cin>>n>>k>>p;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=(a[i]+a[i-1])%p;
	}
	for(int i=0;i<=n;i++) a[i]++;
	memset(minv,1,sizeof(minv));
	for(int i=0;i<=k;i++) memset(tree[i].f,1,sizeof(tree[i].f));
	tree[0].change(1,0);
	minv[1]=0;
	for(int i=1;i<=n;i++){
		for(int j=k;j>=1;j--){
			int v=min(tree[j-1].qry(a[i]),minv[j-1]+1);
			tree[j].change(a[i],v);
			minv[j]=min(minv[j],v);
			if(i==n&&j==k){
				cout<<v*p+a[i]-1;
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：李至擎 (赞：1)

谁说 $n\le5\times 10^5$，$k\le100$，$p\le100$ 只能 $O(nk)$？我今天就要用 $O(nk\log p)$ 过这个题！

定义 $f_{i,j}$ 表示前 $j$ 个数，分成 $i$ 段的最小价值和，$s_i$ 表示前缀和（对 $p$ 取模），转移就是 $f_{i,j}=\min\limits_{l=1}^{j-1}\left\{f_{i-1,l}+\left(s_j-s_l\right)\bmod p\right\}$。朴素转移是 $O(n^2k)$ 的。

但是我们发现，我们不需要枚举具体从哪个位置转移过来，只要知道那个位置的前缀和对 $p$ 取模的值即可。更具体地，我们在转移的时候维护一个数组 $g$，$g_i$ 表示所有前缀和对 $p$ 取模为 $i$ 的转移中最小的，显然这个可以在转移的同时 $O(1)$ 更新，复杂度就优化到了 $O(nkp)$。

这样肯定还是过不了的，但我们可以利用数据结构再次优化，用树状数组维护 $g$ 数组：对于 $\left(s_j-s_l\right)\bmod p$ 这一项，发现它在 $s_l\le s_j$ 的时候等于 $s_j-s_l$，反之等于 $s_j-s_l+p$。所以我们可以开两个树状数组，分别维护前/后缀 $f_{i-1,l}-s_l$ 的最小值。时间复杂度 $O(nk\log p)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,k,p,f[105][500005],s[500005],c[105],d[105];
inline void addp(int x,int y){for(x++;x<=p;x+=x&-x)c[x]=min(c[x],y);}
inline void adds(int x,int y){for(x=p-x;x<=p;x+=x&-x)d[x]=min(d[x],y);}
inline int askp(int x){int res=inf;for(x++;x;x-=x&-x)res=min(res,c[x]);return res;}
inline int asks(int x){int res=inf;for(x=p-x;x;x-=x&-x)res=min(res,d[x]);return res;}
signed main(){
	n=read(),k=read(),p=read();
	for(int i=1;i<=n;++i)s[i]=(s[i-1]+read())%p,f[1][i]=s[i];
	for(int i=2;i<=k;++i){
		for(int j=0;j<p;++j)c[j+1]=d[p-j]=inf;
		for(int j=1;j<=n;++j)f[i][j]=min(askp(s[j]),asks(s[j]+1)+p)+s[j],addp(s[j],f[i-1][j]-s[j]),adds(s[j],f[i-1][j]-s[j]);
	}
	printf("%d\n",f[k][n]);
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18321977)

# 思路

先考虑 $\Theta(n^2k)$ 的暴力 DP。

定义 $dp_{i,j}$ 表示在前 $i$ 个数中选取 $j$ 个的最小和，转移显然：

$$
dp_{i,j} = \min_{1 \leq k < i}\{dp_{k,j - 1} + s_{k + 1,i} \bmod p\}
$$

注意到一个性质：$dp_{i,j} \equiv s_i \pmod p$。因为前者是前 $i$ 项分为若干段的模 $p$ 下的和，与后者显然在模 $p$ 意义下同余。

对于 $dp_{i,j}$ 的两个转移的位置 $k_1,k_2$，计算出的结果分别是，$dp_{k_1,j - 1} + s_{k_1 + 1,i} \bmod p$ 与 $dp_{k_2,j - 1} + s_{k_2 + 1,i} \bmod p$。并且有：

$$
dp_{k_1,j - 1} + s_{k_1 + 1,i} \bmod p \equiv dp_{k_2,j - 1} + s_{k_2 + 1,i} \bmod p \pmod p
$$

假设 $dp_{k_1,j - 1} < dp_{k_2,j - 1}$，由于 $s_{k_1 + 1,i} \bmod p$ 与 $s_{k_2 + 1,i} \bmod p$ 一定小于 $p$，所以前者一定小于后者。

这样，对于每一个 $j$，记录最小的 $dp_{i,j}$ 即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 5e5 + 10,M = 110;
int n,m,p;
int arr[N],s[N];
int dp[N][M],f[M];

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

#define sum(l,r) ((s[r] - s[l - 1]) % p)

signed main(){
    n = read(),m = read(),p = read();
    for (re int i = 1;i <= n;i++) s[i] = s[i - 1] + (arr[i] = read());
    for (re int i = 1;i <= n;i++){
        for (re int j = 1;j <= min(i,m);j++) dp[i][j] = dp[f[j - 1]][j - 1] + sum(f[j - 1] + 1,i);
        for (re int j = 1;j <= min(i,m);j++){
            if (!f[j] || dp[f[j]][j] > dp[i][j]) f[j] = i;
        }
    }
    printf("%lld",dp[n][m]);
    return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

令 $f_{i,j}$ 表示当前看了前 $i$ 位，选出 $j$ 段的最小的价值除以 $p$ 下取整得到的值。

令 $g_i=(\sum_{j=1}^i a_j)\bmod p$，显然可以 $O(n)$ 转移。

若对于 $i$ 位置存在另一个位置 $j$ 满足 $g_j\le g_i$，那么 $f_{i,k+1}$ 可以由 $f_{j,k}$ 转移过来。若在上述式子的基础上有 $g_j\neq g_i$ 那么 $f_{i,k+1}$ 可以由 $f_{j,k}+1$ 转移过来。

发现更新值的时候值域很小且连续，所以建 $p$ 个权值树状数组维护区间最小值即可。时间复杂度 $O(nk\log n)$，卡卡常能过。

---

