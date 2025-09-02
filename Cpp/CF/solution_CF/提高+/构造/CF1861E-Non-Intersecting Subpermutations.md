# Non-Intersecting Subpermutations

## 题目描述

# 不相交子排列


给定两个整数 $n$ 和 $k$。

对于长度为 $n$ 的数组，我们定义它的成本为可以选择的此数组的最大连续子数组数量，以便：

- 每个元素最多属于一个子数组；
- 每个子数组的长度恰好为 $k$；
- 每个子数组恰好包含从 $1$ 到 $k$ 的每个整数。

例如，如果 $n=10$，$k=3$，且该数组为$[1,2,1,3,2,3,2,3,1,3]$，则其成本为 $2$，因为，例如，我们可以选择从第 $2$ 个元素到第 $4$ 个元素和从第 $7$ 个元素到第 $9$ 个元素的子数组，并且我们可以证明无法选择超过 $2$ 个子数组。

计算由整数 $1$ 到 $k$ 组成、长度为 $n$ 的所有数组的成本总和，并将其对 $998244353$ 取模后打印出来。

## 样例 #1

### 输入

```
10 3```

### 输出

```
71712```

## 样例 #2

### 输入

```
2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
1337 42```

### 输出

```
524933698```

# 题解

## 作者：Zwb0106 (赞：16)

[**原题链接**](https://codeforces.com/contest/1861/problem/E)

------------
给一个简单易懂的容斥做法。

------------
## 思路

对每个序列都计算合法段的个数比较困难，可以考虑计算以每个 $i$ 为结尾的合法段的贡献，求和即答案。

设 $f_i$ 表示只考虑前 $i$ 个位置，以 $i$ 为结尾的合法段的贡献次数。因为重叠不会有贡献，因此对于一个已确定的序列，计算答案一定是贪心选尽可能靠前的段。如果不考虑重叠不计的限制，$f_i$ 就是 $k! \times k^{i-k}$。

现在减去不合法的，这种情况等价于存在一个 $[i-k+1,i)$ 中的 $j$，使得 $j$ 为结尾的段合法且被计算贡献，这个方案数就是 $f_j \times (i-j)!$。乘 $(i-j)!$ 是由于 $[i-k+1,i]$ 这个段中 $1$ 到 $k$ 各出现一次，而 $[i-k+1,j]$ 中的数已经被以 $j$ 为结尾的段确定了，剩下 $i-j$ 个数任意指定次序。

因此，有 $f_i = k! \times k^{i-k} - \sum\limits_{i-k+1\le j<i} f_j \times (i-j)!$，后面的 $n-i$ 个数随便选，因此答案是 $\sum\limits_{i=k}^{n} f_i \times k^{n-i}$。

这个做法有 $O(nk)$ 的时间复杂度和 $O(n)$ 的空间复杂度。

------------
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define gc getchar
#define pc putchar
#define fs first
#define sc second
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define lowbit(x) (x&(-x))
using namespace std;

ll read()
{
	ll x=0,f=1;
	char ch=gc();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=gc();
	return x*f;
}
void print(ll x)
{
	if(x<0)pc('-'),x=-x;
	if(x>9)print(x/10);
	pc(x%10+48);
}

const int N=4005;
const ll mod=998244353;
int n,k;
ll fac[N],f[N];

ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
void init()
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%mod;
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read(),k=read(),init();
	
	for(int i=k;i<=n;i++)
	{
		f[i]=fac[k]*qpow(k,i-k);
		for(int j=i-k+1;j<i;j++)
			f[i]-=f[j]*fac[i-j]%mod;
		f[i]=(f[i]%mod+mod)%mod;
	}
	
	ll ans=0;
	for(int i=k;i<=n;i++)
		ans=(ans+f[i]*qpow(k,n-i))%mod;
	print(ans);
	
	return 0;
}
```

---

## 作者：y_kx_b (赞：9)

9.2 11:13 >> 18:53

参考了官方题解。

每个序列的 cost 怎么计算？贪心扫一遍，记录当前一个最长后缀，每次扫到一个新元素时单调队列似的弹出前面的元素，等到长度等于 $k$ 的时候 $cost\gets cost + 1$ 并且清空后缀（每个元素只能用一遍）。[btf code](https://codeforces.com/contest/1861/submission/221515115)（请忽略那一长串缺省源，下同）。

那么考虑 dp：$dp_{i,x,c}$ 表示前 $i$ 个位置，当前最大后缀长度为 $x$，序列 cost 为 $c$ 的序列数。那么有两种转移：

1. 第 $i+1$ 个位置上的元素与之前都不同。显然这个元素有 $k-x$ 个选法，$\begin{cases}dp_{i+1,x+1,c}\gets(k-x)\ dp_{i,x,c}, x+1\not=k\\dp_{i+1,0,c+1}\gets(k-x)\ dp_{i,x,c}, x+1=k\end{cases}$。
2. 第 $i+1$ 个位置上的元素与后缀里的第 $j$ 个元素（从右往左数）一样。这时显然 $dp_{i+1,j, c}$ 与 $dp_{i,x,c}$ 一一对应（新序列在原序列加入一个唯一确定元素的基础上踢掉了原来的右数第 $j$ 个位置（含本身）往左的所有元素，新后缀长度变为 $j$），直接 $dp_{i+1, j, c} \gets dp_{i, x, c}, \text{for}\ j\in[1, x]$。

这样[直接做](https://codeforces.com/contest/1861/submission/221547771)是 $O(n^2k)$ 的（第二维范围是 $[0, k)$，第三维是 $[0, \left\lfloor\frac nk\right\rfloor]$，所以总状态是 $O(n^2)$ 的；第二类转移是 $O(k)$ 的）。考虑把转移方程写成填表法。

1. $\begin{cases}dp_{i,x,c}\gets(k-x+1)\ dp_{i-1,x-1,c}, x\not=0\\dp_{i,x,c}\gets dp_{i-1,k-1,c-1}, x=0\land c\not=0\end{cases}$。
2. $dp_{i,x,c} \gets \sum\limits_{j=x}^{k-1} dp_{i-1,j,c},\text{if }x>0$。

发现第二个转移可以前缀和（其实是后缀和）优化到 $O(1)$，那么这道题[做完了](https://codeforces.com/contest/1861/submission/221552150)（不过不知道为什么时间很危险，可能是我实现太烂了？）。时间复杂度 $O(n^2)$。

但是其实我们状态的第三维是不需要的。我们考虑每次转移到 $x=k$ 时，不去把第三维 $+1$，而是计算这个 $1$ 会给答案带来多少贡献。也就是说，有 $k^{n-i}$ 个序列是以这个序列为前缀的，再加上这个序列有 $dp_{i, 0}$ 个，所以对答案贡献是 $dp_{i, 0} \times k^{n-i}$ 的。那么我们成功把时间复杂度优化到了 $O(nk)$，完结撒花！

[O(nk) code](https://codeforces.com/contest/1861/submission/221555995)。

---

## 作者：Xy_top (赞：6)

少有的 我不看题解 能做出来的 2E 的 DP 题。

这题的状态设计很奇怪，所以我将说出我想到这个状态的全过程。

首先，我读错了题，没看到 ``each element belongs to at most one subarray``，那么这就是一道计数题了，枚举长度为 $k$ 的排列的位置，然后其他乱填即可。

虽然这个做法是错的，但却给了我很大的启发。

紧接着我想到了 dp，设 $f_x$ 为从第 $x$ 个位置向后所有数列的 $cost$ 之和。两种转移如下：

$f_x=k\times f_{x+1}$，即这一位乱填。

$f_x=k!\times f_{x+k}$，即在后面填一个长度为 $k$ 的排列。

$x> n$ 时，$f_x=1$。

然后你会发现答案大了很多，原因是乱填包含的排列的情况。

这时就需要换个状态了，我发现状态太少了不足以不重不漏的计算答案。

设 $f_{i,j}$ 为从 $n$ 到 $1$ 倒着扫（我也不知道我为啥要想倒着扫），$i$ 以及向后的都是已经考虑过的，$i+j-1$ 后面的都是一个个长度为 $k$ 的排列。且 $a_{i\cdots i+j-1}$ 是有希望在考虑完 $i$ 前面成为排列的，并且 $j$ 要是最大的，满足这个条件所有的序列的 $cost$ 之和。

其实说白了有希望就是 $a_{i\cdots i+j-1}$ 没有相同的元素并且这个长度要最大。

答案也很简单，就是 $\sum\limits_{i=1}^k f_{1,i}$ 了。

下面考虑转移，这里我才用的是贡献转移。

到了 $f_{i,j}$，我们考虑它能对哪些 $f_{i-1}$ 做贡献。

- 如果 $j=k$ 了，那么前一个可以乱填，当前这里已经达成了长度为 $k$ 的排列了，所以加到 $f_{i-1,1}$ 上，可以填 $1\cdots k$ 中任意的元素，所以 $f_{i-1,1} \to f_{i-1,1}+ k \times f_{i,j}$。

以下的两种转移是填后面 $j$ 个没出现过的数字的情况：

- 如果 $j=k-1$ 了，再一个可以选择把剩下的那个没有出现过的填了，这样就成为了一个排列了，这是新加入的答案。但有多少个这种排列呢？显然不是 $f_{i,j}$。此时发现还需要一种状态 $g_{i,j}$，大体意思和 $f$ 差不多，不过它存储的是满足这个条件的序列个数，那么显然了，$f_{i-1,k}\to f_{i-1,k}+f_{i,j}+g_{i,j}$。

- 如果 $j\leq k-2$ 时，填一个没出现过的是不会出现排列的，所以仅需要把当前的加到填完的状态上就行。填完后是  $f_{i-1,j+1}$，当前这个位置有 $j$ 个都被填了，还剩 $k-j$ 个，总共的方案就是 $f_{i,j}\times (k-j)$，所以 $f_{i-1,j+1}\to f_{i-1,j+1}+f_{i,j}\times (k-j)$。

最后这种转移是填一个之前出现过的把这个排列毁掉：

然而这个时候填哪个之前出现的也是个问题，如果就填上一个填的，那么转移后的 $j$（即最长希望连续序列长度）就是 $1$ 了，如果填 $i+1$ 位置填的，长度就将会是 $2$ 了。

此时，还要枚举一个 $l$ 代表填上几个填的。如果填了前 $l$ 个填过的数字，那么转移后的 $j$ 就是 $l$。（有点难于理解，多次阅读可能会好一点，我这里给张图）


![](https://cdn.luogu.com.cn/upload/image_hosting/qmmfrfhv.png)

如果填了 A，那么转移后的 $j$（即最长希望连续序列长度）为 $1$，这个 A 是上一个填的。

填 B，转移后的 $j$ 就是 $2$，B 是上两个填的。

以此类推...

那么可以写出这一部分的伪代码：

```cpp
For (l, 1, j) {//这里枚举到 j 是因为最多填上 j 的填的，再往后的都是已经构成排列的了
	f[i - 1][l] += f[i][j];
}
```

然后这就是 $n\times k^2$ 的，我给个代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, k, ans;
const int mod = 998244353;
int f[4005][4005], g[4005][4005];
void Add (int &x, int y) {x = (x + y) % mod;}
void solve () {
	cin >> n >> k;
	g[n][1] = k;
	foR (i, n, 2) {
		For (j, 1, k) {
			if (j == k) Add (g[i - 1][1], k * g[i][j]);
			else {
				Add (g[i - 1][j + 1], (k - j) * g[i][j]);
				For (l, 1, j) Add (g[i - 1][l], g[i][j]);
			}
		}
	}
	foR (i, n, 2) {
		For (j, 1, k) {
			if (j == k) Add (f[i - 1][1], k * f[i][j]);
			else {
				if (j + 1 == k) Add (f[i - 1][j + 1], f[i][j] + g[i - 1][k]);
				else Add (f[i - 1][j + 1], (k - j) * f[i][j]);
				For (l, 1, j) Add (f[i - 1][l], f[i][j]);
			}
		}
	}
	int ans = 0;
	For (i, 1, k) ans += f[1][i], ans %= mod;
	cout << ans;
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

典中典的差分优化 DP，但是这里有个灵异事件，我直接把 $f_{i-1}$ 当成差分数组搞就 WA 了，但是 $k\geq n-1$ 时不会，我只能新开一个差分数组了，AC 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, k, ans;
const int mod = 998244353;
int f[4005][4005], g[4005][4005], d[4005];
void Add (int &x, int y) {x = (x + y) % mod;}
void solve () {
	cin >> n >> k;
	g[n][1] = k;
	foR (i, n, 2) {
		For (j, 1, k) d[j] = 0;
		For (j, 1, k) {
			if (j == k) Add (g[i - 1][1], k * g[i][j]);
			else {
				Add (g[i - 1][j + 1], (k - j) * g[i][j]);
				d[1] += g[i][j];
				d[j + 1] -= g[i][j];
				d[1] = (d[1] % mod + mod) % mod;
				d[j + 1] = (d[j + 1] % mod + mod) % mod;
			}
		}
		For (i, 1, k) d[i] += d[i - 1], d[i] %= mod;
		For (j, 1, k) g[i - 1][j] = (g[i - 1][j] + d[j]) % mod;
	}
	foR (i, n, 2) {
		For (j, 1, k) d[j] = 0;
		For (j, 1, k) {
			if (j == k) Add (f[i - 1][1], k * f[i][j]);
			else {
				if (j + 1 == k) Add (f[i - 1][j + 1], f[i][j] + g[i - 1][k]);
				else Add (f[i - 1][j + 1], (k - j) * f[i][j]);
				d[1] += f[i][j];
				d[j + 1] -= f[i][j];
				d[1] = (d[1] % mod + mod) % mod;
				d[j + 1] = (d[j + 1] % mod + mod) % mod;
			}
		}
		For (i, 1, k) d[i] += d[i - 1], d[i] %= mod;
		For (j, 1, k) f[i - 1][j] = (f[i - 1][j] + d[j]) % mod;
	}
	int ans = 0;
	For (i, 1, k) ans += f[1][i], ans %= mod;
	cout << ans;
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：BreakPlus (赞：3)

至于为什么会写一篇 *2300 的题解，是希望把这题钉在自己的耻辱柱上。笔者在做此题时坚持直觉，一意孤行，虽然想出了与众不同的解法，但是耗费大量时间，得不偿失，警钟敲烂。

----

+ 首先处理本题需要计数的东西。考虑什么时候可以取到尽量多的区间。一个很显然的贪心是：找到最靠前的区间并选取它。如果选取靠右的，那么剩下的区间更短，不优。

+ 然后我们可以考虑一段位于 $[i-k+1,i]$ 的区间什么时候可以给答案贡献。为此我们需要先知道上一个区间的位置，记为 $[j-k+1,j]$。依据上述的贪心做法，在 $[j+1,i-1]$ 之间不能选出一个刚好含有 $1\sim k$ 的区间。

+ 我们使用这样一个技巧。记 $d(i)$ 表示 $i$ 个数的序列，满足条件的区间仅出现在序列的末尾的序列数。不难发现我们针对这个东西很难计数。

+ 而若求出了 $g(i)$ 表示 $i$ 个数的序列中没有满足条件的区间，可以得到一个柿子：$d(i) = kg(i-1) - g(i)$。也就是，满足 $1 \sim i-1$ 不含满足条件的区间的方案数减去 $1 \sim i$ 不含满足条件的区间的方案数，它等于满足条件的区间出现在末尾的方案数。

+ 对于 $g(i)$ 我们不难容斥得到。

+ 考虑对最初我们想求的东西。令 $h(i)$ 表示以 $i$ 结尾的一个满足条件的区间能对答案有多少的贡献（不考虑 $i+1 \sim n$ 的元素，因为它们是任意的）。

+ $h(i) = \sum \limits_{j=0}^{i-1}h(j)d(i-j)$

+ 然后这题就做完了。

```cpp
void solve(){
	n=read(), k=read();
	f[0][0]=1;
	pw[0]=1;
	for(ll i=1;i<=n;i++) pw[i]=pw[i-1]*k%mod;
	for(ll i=k;i<=n;i++){
		for(ll j=0;j<i;j++){
			_Add(f[i][0], f[j][1] * Fac(minn(k, i-j)) % mod * pw[maxx(i-j-k, 0)] % mod);
			_Add(f[i][1], f[j][0] * Fac(minn(k, i-j)) % mod * pw[maxx(i-j-k, 0)] % mod);
		}
	}
	g[0]=1;
	for(ll i=1;i<=n;i++){
		g[i]=qpow(k,i);
		for(ll j=1;j<=i;j++){
			_Add(g[i], f[j][0] * pw[i-j] % mod);
			_Minus(g[i], f[j][1] * pw[i-j] % mod);
		}
	}
	h[0]=1;
	ll ans=0;
	for(ll i=k;i<=n;i++){
		for(ll j=0;j<=i-k;j++){
			_Add(h[i], h[j] * ((g[i-j-1] * k - g[i-j] + mod) % mod) % mod);
		}
		_Add(ans, h[i]*qpow(k, n-i)%mod);
	}
	printf("%d\n", ans);
}
```

---

## 作者：OccDreamer (赞：3)

### 简要题意

一个长度为 $n$ 的元素在 $[1,k]$ 的整数序列 $a$ 的价值定义如下。

- 初始 $i=1$，如果 $a_{i\sim i+k-1}$ 包含了 $1 \sim k$ 的所有整数，则价值加 $1$，然后令 $i=i+k$。如果没有包含 $1\sim k$ 的所有整数则 $i=i+1$，直到 $i \geq n-k+2$ 时结束。

对于给定的 $k$，求所有长度为 $n$ 的序列的价值和。

### 做法

我们称一个位置 $x$ 是匹配的，当且仅当在序列中选出的段中包含 $[x-k+1,x]$。

考虑设计 dp。

设 $f_i$ 表示长度为 $i$ 的序列，只存在一个匹配位置，且这个位置为 $i$ 的方案数。

设 $F_i$ 表示长度为 $i$ 的序列，不存在匹配位置的方案数。

设 $g_i$ 表示长度为 $i$ 的序列，有一个匹配位置为 $i$ 的方案数。

设 $dp_i$ 表示长度为 $i$ 的序列，有一个匹配位置为 $i$ 的所有序列的价值和。

不难发现最后的答案就是 $\sum F_{n-i}dp_i$。

转移如下。

$$
f_i=k!k^{i-k}-\sum_{j=k}^{i-1} f_j k^{\max\{0,i-k-j\}}(\min\{k,i-j\})!
$$

考虑用总方案数减去不合法的方案乘上系数就可以得到上述式子。

$$
F_i=k^i-\sum_{j=1}^i f_j k^{i-j}
$$

依然是考虑用总方案数减去不合法方案数。

$$
g_i=\sum_{j=0}^{i-k} g_jf_{i-j}
$$

$$
dp_i=\sum_{j=0}^{i-k} (g_j+dp_j)f_{i-j}
$$

然后就可以在 $O(n^2)$ 时间内求出答案了。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 4004;
const int mod = 998244353;

int n, k, res, p[MAXN];
int f[MAXN], fac[MAXN], ifac[MAXN], dp[MAXN], g[MAXN], F[MAXN];

ll powc[MAXN];

int main(){
	cin >> n >> k; powc[0]=1; fac[0]=1;
	for(int i=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=n;++i) powc[i]=powc[i-1]*k%mod;
	ll p=1; for(int i=1;i<=k;++i) p=p*i%mod; f[k]=p;
	for(int i=0;i<k;++i) F[i]=powc[i]; F[k]=(powc[k]-f[k]+mod)%mod;
	for(int i=k+1;i<=n;++i){
		f[i]=p*powc[i-k]%mod; int t=i-k+1;
		for(int j=k;j<i;++j){
			if(t<=j) (f[i]-=1ll*f[j]*fac[k-(j-t+1)]%mod-mod)%=mod;
			else (f[i]-=1ll*f[j]*powc[t-j-1]%mod*p%mod-mod)%=mod;
		}
		F[i]=powc[i];
		for(int j=1;j<=i;++j) (F[i]-=1ll*f[j]*powc[i-j]%mod-mod)%=mod;
	}
	dp[0]=0, g[0]=1; ll sum=0;
	for(int i=k;i<=n;++i){
		for(int j=i-k;j>=0;--j){
			(g[i]+=1ll*g[j]*f[i-j]%mod)%=mod;
			(dp[i]+=1ll*(g[j]+dp[j])*f[i-j]%mod)%=mod;
		}
		sum+=1ll*dp[i]*F[n-i]%mod; sum%=mod;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：RockyYue (赞：3)

**注：参考第一篇题解，记录自己理解**
### 题意

一个序列的价值被定义为其中最多的长度为 $k$ 的包含所有 $\{1,2,3,...,k\}$ 的不交子段的个数。

求所有长度为 $n$ 的每一位为 $1$ 到 $k$ 的所有序列的价值之和。

其中 $1\le n,k\le 4000$

### 解法

设一个匹配为一个符合条件的子段。

对于长度为 $i$ 的一段序列，设：

$dp_i$ 为其中一个匹配以 $i$ 结束的所有序列价值和。

$F_i$ 为不存在任何匹配的方案数。

则易得答案：$\sum_{i=0}^n{dp_iF_{n-i}}$，其中 $i$ 为最后一个匹配的结束位置。

为什么要这样设计状态呢？因为对于以匹配结尾的序列明显是更为好求的，我们只需要考虑上一个匹配的结束位置即可。

为了求解这两个数组，我们再引入两个数组。

$f_i$ 为存在且仅存在一个匹配且以i结束的方案数。

$g_i$ 为其中一个匹配以i结束的方案数。

接下来考虑递推求解四个数组。

$f_i=k!k^{i-k}-\sum_{j=k}^{i-1}f_jk^{\max\{i-k-j,0\}}(\min\{i-j,k\})!$

其中 $k!$ 表示最后的 $k$ 个位置构成一个匹配的方案数，$k^{i-k}$ 表示前面 $i-k$ 个位置随便排的数量，后面减去的部分是前 $i-k$ 个中有匹配的方案数。其中 $j$ 表示前 $i-k$ 个中最后一个匹配的结束位置。$i-k-j$ 表示 $[j+1,i]$ 这一段除了最后一个匹配的部分，可以随便选。最后的阶乘则是最后一个匹配，当 $i-j<k$ 时，因为 $j$ 结束的也是一个匹配，前面的部分必然各不相同，则后面选上剩余的那些数排列即可。

$F_i=k^i-\sum_{j=k}^i{f_jk^{i-j}}$

其中 $j$ 表示枚举的第一个匹配的结束位置。

$g_i=\sum_{j=k}^{i-k}{g_jf_{i-j}}+f_i$

其中 $j$ 表示枚举的上一个匹配的结束位置，最后注意可能没有上一个匹配，要加上 $f_i$。

$dp_i=\sum_{j=k}^{i-k}{(g_j+dp_j)f_{i-j}}+f_i$

这里 $j$ 表示上一个匹配的结束位置，$g_j+dp_j$ 表示这些序列继续写到$i$的价值和，$dp_j$ 表示截至到 $j$ 的价值，$g_j$ 相当于对每个序列的价值 $+1$。$\times f_{i-j}$ 表示对于后面部分每一种排列方式都会产生上述价值。最后不要忘记加上只有这一个匹配的 $f_i$。

---

## 作者：Z_X_D_ (赞：2)

## 思路
- 显然是 DP，考虑子任务问题，可以想到把长度 $n$ 分成前后两段，然后转移统计答案，但是前后两端衔接时中间可能会产生一个额外的子数组，因此还需要记录后缀最长不重的长度。
- 用 $f_{i,j}$ 表示到第 $i$ 位且后 $j$ 位互不相同的序列的个数，统计所有 $f_{i,0}$ 为答案（正确性下面会讲），参照上面的思路，我们可能需要对所有的前缀统计答案，但是这样复杂度是 $O(n^2k^2)$，不太可行。
- 可以发现上面的转移不仅会 TLE 还会重复统计多次导致答案错误，所以 $f_i$ 的所有状态可以只由 $f_{i-1}$ 的状态转移过来，这样的话复杂度是 $O(nk)$ 的。

具体地，$f_{i,j}$ 可以由 $f_{i-1,x}(j\le x<k)$ 和 $f_{i-1,j-1}$ 转移而来，前者能对当前产生 $\Sigma_{x=j}^{k}{f_{i-1,x}}$ 的贡献（当前为填上前面倒数第 $x-j+1$ 个数），后者能对当前产生 $f_{i-1,j-1}\times (k-j)$ 的贡献（填上与之前不重复的数）。

关于对 $f_{i,0}$ 统计答案，$j=0$ 表示当前后缀 $k$ 个数恰好是子数组，后面随便填，因此会对答案产生 $f_{i,0}\times k^{n-i}$ 的贡献。

关于统计答案的正确性，对于每个 $j=0$ 序列，序列中其他子数组都在之前被统计过了，后边的子数组到后面会统计，所以也不会少算。

然后就可以愉快 DP 了。
## $Code$
```cpp
#include<bits/stdc++.h>
#define int long long
#define M 998244353
#define N 4010
#define otto auto//帅otto
using namespace std;
int f[N][N];
int qp(int b,int n)
{
	int ans=1;
	while(n)
	{
		if(n&1)
			ans=ans*b%M;
		b=b*b%M;
		n>>=1;
	}
	return ans;
}
int ans;
signed main()
{
	int n,k,nw,i,j;
	scanf("%lld%lld",&n,&k);
	f[0][0]=1;
	for(i=1;i<=n;i++)
	{
		nw=0;
		for(j=k-1;j>=1;j--)
		{
			nw=(nw+f[i-1][j])%M;
			f[i][j]=nw;
		}
		for(j=0;j<k;j++)
			f[i][(j+1)%k]=(f[i][(j+1)%k]+f[i-1][j]*(k-j))%M;
		ans=(ans+f[i][0]*qp(k,n-i)%M)%M;
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：Leasier (赞：2)

vp 时花了 1h 解决本题，被 30min 速切的 [goujingyu](https://www.luogu.com.cn/user/266966) 嘲讽了 /kk

------------

- **将序列与最大 cost 的划分方式一一对应，对这种划分方式 dp。**

考虑如何求出一个序列的最大 cost：

- 贪心地，我们从 $1$ 到 $n$ 枚举 $i$，设当前子序列为 $a'$，初始为空。
- 若 $a_i \notin a'$，我们直接将 $a_i$ 加入 $a'$；否则，我们从 $a'$ 开头开始逐项删除直到 $a_i \notin a'$，再将其加入。
- 若此时 $|a'| = k$，我们将 $a'$ 加入所拆分出的子段，再将 $a'$ 清空。

遂考虑把 $a'$ 的相关信息压进状态 dp。设 $dp_{i, j, x}$ 表示讨论到 $i$，$|a'| = j$，此时总 cost 为 $x$ 的方案数。

初值：$dp_{0, 0, 0} = 1$。

转移需要讨论三种情况：

- $j < k - 1$，新加入的 $a_{i + 1} \notin a'$：此时令 $dp_{i + 1, j + 1, x} \leftarrow dp_{i, j, x}(k - j)$。
- $j = k - 1$，新加入的 $a_{i + 1} \notin a'$：此时令 $dp_{i + 1, 0, x + 1} \leftarrow dp_{i, j, x}$。
- 新加入的 $a_{i + 1} \in a'$：考虑枚举我们删完并加入当前数后 $|a'| = y \in [1, j]$，此时令 $dp_{i + 1, y, x} \leftarrow dp_{i, j, x}$。

前缀和优化即可。时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;
int dp[2][4007][4007], sum[4007][4007];

int main(){
	int n, k, up, lst, ans = 0;
	scanf("%d %d", &n, &k);
	dp[0][0][0] = 1;
	for (int i = 0; i < n; i++){
		int cur = i & 1, nxt = cur ^ 1;
		up = i / k;
		for (int j = 0; j < k; j++){
			for (int x = 0; x <= up; x++){
				dp[nxt][j][x] = 0;
			}
		}
		for (int j = k - 1; j >= 1; j--){
			for (int x = up; x >= 0; x--){
				sum[j][x] = (sum[j + 1][x] + dp[cur][j][x]) % mod;
			}
		}
		for (int j = 0; j < k; j++){
			for (int x = 0; x <= up; x++){
				dp[nxt][j][x] = (dp[nxt][j][x] + sum[j][x]) % mod;
				if (j < k - 1){
					dp[nxt][j + 1][x] = (dp[nxt][j + 1][x] + 1ll * dp[cur][j][x] * (k - j) % mod) % mod;
				} else {
					dp[nxt][0][x + 1] = (dp[nxt][0][x + 1] + dp[cur][j][x]) % mod;
				}
			}
		}
	}
	lst = n & 1;
	up = n / k;
	for (int i = 0; i < k; i++){
		for (int j = 0; j <= up; j++){
			ans = (ans + 1ll * dp[lst][i][j] * j % mod) % mod;
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

爆标做法。目前范围：$n \le 10^9, k \le 10^5$。

前置知识：$\Theta(\mathsf M(n) \log k)$ 线性递推。

## 题意简述
设 $p = 119 \times 2^{23} + 1$，$[n] = \{1, 2, \dots, n\}$。

给定正整数 $n, k$。对于长度为 $n$ 的数列 $a$，我们定义 $f(a)$ 为：最大的 $m$，使得存在 $m$ 个子区间 $S_1, \dots, S_m \subseteq [n]\ (S_i = [l_i, r_i] \cap \mathbb Z)$，它们两两不交，$|S_i| = k$，且 $\{a_x \mid x \in S_i\} = [k]$。

对于 $k^n$ 个值域为 $[k]$ 长度为 $n$ 的序列 $a$，求 $f(a)$ 的总和。

## 解法 1（原题）
本部分能解决 $n, k \le 5 \times 10^3$ 的问题。

我们定义对于数列 $a$，**合适**的最优方案为贪心地取的最优方案。具体地，顺向枚举 $i = 1, \dots, n-k+1$，如果 $i$ 不属于上个区间 $I$ 且 $\{a_i, \dots, a_{i+k-1}\} = [k]$，则加入一个新区间 $I' = [i, i+k-1] \cap \mathbb Z$。容易证明合适的最优方案一定是最优方案，以及一个数列的合适的最优方案唯一。我们现在转为对合适的最优方案的讨论。

如果我们没有 $S_i$ 两两不交的限制，则考虑某个 $T$ 在全部的 $k^n$ 个序列的全部的 $S_i$ 中的总出现次数，考虑到 $T = [l, r] \cap \mathbb Z$，则 $(a_{1}, \dots, a_{r})$ 是 $[k]$ 的排列，共有 $k!$ 个方案，而 $T^\complement$ 的元素则是自由的，所以共有 $k^{n-k}$ 个方案，所以是 $k^{n-k} \cdot k!$。

我们现在只考虑前 $i$ 个数，让后面的数自由地在 $[k]$ 取。我们定义，$f(i)$ 等于有多少个数列，使得 $[i-k+1, i]$ 是合适的最优方案之一，则答案为
$$
\sum_{i=k}^n f(i).
$$

根据我们上面的讨论，如果没有两两无交的性质，$f(i) = k^{n-k} \cdot k!$。所以我们只需找到因有交，$[i-k+1,i]$ 不能选上合适的最优方案的方案数。现在考虑：合适的最优方案里有 $[j-k+1,j]$，且 $j \in [i-k+1,i-1]$。这样，这个数列一定在 $f(j)$ 的数列中，但是由于 $f(j)$ 只需考虑前 $j$ 项，所以 $f(j)$ 数列并不一定满足条件。

我们现在需要新增的限制是：
$$
\{a_\ell \mid \ell \in [j+1,i]\} = \{a_\ell \mid \ell \in [j-k+1,i-k]\}.
$$
这是因为两边均是 $[k] \setminus \{a_\ell \mid \ell \in [i-k+1,j]\}$。左右两边大小一定是 $i-j$，并且右侧集合对于 $f(j)$ 而言是确定的，所以满足限制的 $a_\ell$ 子段共有 $(i-j)!$ 个，而在 $f(j)$ 中我们视它为 $k^{i-j}$ 个，所以 $[j-k+1,j]$ 比 $[i-k+1,i]$ 更合适的数列共有
$$
\dfrac{(i-j)!}{k^{i-j}} f(j)
$$
个。因此我们有
$$
f(i) = k! \cdot k^{n-k} - \sum_{j=i-k+1}^{i-1} \dfrac{(i-j)!}{k^{i-j}} f(j).
$$
直接实现即可。

## 解法 2
注意到后面是一个卷积形式，所以考虑求生成函数。但是 $n$ 限制了 $f(i)$ 只会有 $n-k$ 项，这是不利于生成函数的表达的。我们进行换元：
$$
g(i) = \dfrac{f(i)}{k^{n-i}},
$$
这样原来的表达式变成了
$$
g(i) = k! \cdot k^{i-k} - \sum_{j=1}^{k-1} g(i-j) \cdot j!.
$$
我们希望对这个东西做生成函数优化。

将两边乘以 $X^i$ 并对 $i \ge k$ 求和，有
$$
G(X) = \sum_{i \ge k} g(i) X^i = A(X) - B(X),
$$
其中
$$
A(X) = \sum_{i \ge k} k! k^{i-k} X^i = k! X^k \sum_{i \ge 0} (kX)^i = \dfrac{k!X^k}{1-kX},
$$
而
$$
\begin{aligned}
B(X) &= \sum_{i \ge k} \sum_{j = 1}^{k - 1} X^i g(i-j) \cdot j! \\
&= \sum_{j=1}^{k-1} j! \sum_{i \ge k} X^i g(i-j) \\
&= \sum_{j=1}^{k-1} j! X^j G(X).
\end{aligned}
$$
整理得
$$
G(X) \cdot \left( \sum_{j=0}^{k-1} j!X^j \right) = \dfrac{k!X^k}{1-kX}.
$$
因此
$$
G(X) = \dfrac{k!X^{k}}{(1-kX) \cdot (\sum_{j=0}^{k-1} j!X^j)}.
$$
实现多项式求逆做法，或者进一步：

注意到答案为
$$
\sum_{i=k}^n g(i) k^{n-i},
$$
这又是一个卷积形式，所以它是
$$
[X^n] \dfrac{G(X)}{1-kX},
$$
这就变成了一个次数较少的分式的远处系数值问题，我们可以做到时间复杂度 $\Theta(k \log k \log n)$（Bostan–森算法）。

```cpp
using namespace std;
using namespace atcoder;

using Z = modint998244353;

#define mlt convolution

using P = vector<Z>;
using i64 = int64_t;

Z BostanMori(P f, P g, i64 x) {
    for (;; x >>= 1) {
        if (x == 0) return f[0] / g[0];
        P negG;
        for (int i = 0; i < g.size(); ++i) negG.push_back(i & 1 ? -g[i] : g[i]);
        f = mlt(f, negG), g = mlt(g, negG);
        int i;
        for (i = 0; i < g.size(); i += 2) g[i / 2] = g[i];
        g.resize(i >> 1);
        for (i = x & 1; i < f.size(); i += 2) f[i / 2] = f[i];
        f.resize(i >> 1);
    }
}

vector<Z> get_fact(int n) {
    vector<Z> f(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i;
    return f;
}

int main() {
    int n, k;
    cin >> n >> k;
    P f(k + 1);
    auto fact = get_fact(k);
    f.back() = fact[k];
    P g0(fact.begin(), fact.begin() + k), g1 = {1, -k};
    auto g = mlt(mlt(g1, g1), g0);
    auto ans = BostanMori(f, g, n);
    cout << ans.val() << '\n';
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

神题。

首先注意到，当以 $i$ 结尾的 $j$ 个数互不相同时，以 $i-1$ 结尾的 $j-1$ 个数一定也互不相同。

我们令 $f_{i,j}$，表示前 $i$ 个数，$[i-j+1,j]$ 互不相同的方案数，每段子数组我们在结尾处计算贡献，即 $f_{i,0}$。

当新加入一个与前面的数都不相同的数时，$f_{i,j}=f_{i-1,j-1}\times (k-j+1)$。否则 $f_{i,j}=\sum \limits_{j^{\prime}=j}^{k-1} f_{i,j^{\prime}}$。

答案为 $\sum f_{i,0}\times k^{n-i}$。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4005;
const int Mod=998244353;
int n,k,ans;
int f[N][N];
int qpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%Mod) if(b&1) ans=1ll*ans*a%Mod;
    return ans;
}
int main(){
    scanf("%d%d",&n,&k);
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=k-1;j>=1;j--) sum=(sum+f[i-1][j])%Mod,f[i][j]=(f[i][j]+sum)%Mod;
        for(int j=1;j<=k;j++) f[i][j]=(f[i][j]+1ll*f[i-1][j-1]*(k-j+1)%Mod)%Mod;
        f[i][0]=f[i][k];
        ans=(ans+1ll*f[i][0]*qpow(k,n-i)%Mod)%Mod;
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：xxzx (赞：1)

[在我的博客查看](https://xxzx.moe/2023/09/17/cf1861e/)

提供一种小清新容斥做法。

考虑计算每一个连续子数组的贡献。
如果每个元素可以属于多个连续子数组，那么显然，每个连续子数组的贡献都是 $1$。而题目要求每个元素最多属于一个子数组，当多个子数组相交的时候会算重，因此容斥。

设 $f_{i,j}$ 表示有 $i$ 个子数组相交，它们的并长度为 $j$ 的方案数。每次枚举下一段子数组与前面的所有子数组交为空集的长度 $l$，可以列出如下转移：

$$
f_{i,j}=\sum\limits_{l=1}^{\min(k-1,j-k)}f_{i-1,j-l}\times l!
$$

则答案为

$$
\sum\limits_{i}\sum\limits_{j}(-1)^{i+1}\times (n-j+1)\times f_{i,j}\times k^{n-j}
$$

我们发现在转移 $f_{i,j}$ 的过程中 $i$ 并没有什么用，只在计算答案的时候贡献 $i+1$ 个 $-1$ 的容斥系数，我们直接把容斥系数代入转移，重设 $f_i$ 表示若干子数组的并长度为 $i$ 的（带上容斥系数的）方案数。转移如下：

$$
f_{i}=\sum\limits_{l=1}^{\min(k-1,i-k)}-1\times f_{i-l}\times l!
$$

时间复杂度 $O(n^2)$，代码很好写。
### Code
核心代码：
```cpp
void solve() {
	cin>>n>>k;
	for(int i=0;i<=n;i++) f[i]=0;
	f[k]=fac[k];
	for(int i=k;i<=n;i++)
		for(int j=1;i+j<=n&&j<k;j++)
			f[i+j]=(f[i+j]-f[i]*fac[j]%Mod+Mod)%Mod;
	ll ans=0;
	for(int i=k;i<=n;i++) ans=(ans+(n-i+1)*f[i]%Mod*Pow(k,n-i))%Mod;
	cout<<ans<<endl;
}
```
[完整代码](https://codeforc.es/contest/1861/submission/221327813)

---

## 作者：huangrenheluogu (赞：0)

VP 的时候花在 B 的时间太多了（想不到吧），同时 C 还 WA 了，浪费了很多时间，所以这个 E 是在赛后十分钟写完的。

考虑贪心，显然一个数在前面匹配到是更优的，这样后面有更多的数去产生一组 $1\sim k$ 的排列。

那么，状态就显然了，$g_{i,j}$ 表示前 $i$ 个数，目前这一组里 $k$ 个数里选择了 $j$ 个的合法方案数。（这里不用 $f$ 的原因是本来用 $f$ 统计答案的，后来直接中途算掉了）。

我用的是中途算贡献，显然上一个 $0$ 个数，这一次就会变成 $1$ 个，所以 $0$ 个是不会滞留的。所以答案就是 $\sum\limits^{n}_{i=1}g_{i,0}$。

转移方程讨论一下。

$j=0$ 的时候，从上一次的 $k-1$ 转移，下面讨论 $j\ne 0$ 的情况。

由于对于一组，比如 $k=5$，目前是 $\{1,5,3\}$，这个就是最后的，没有重复数字的集合，我们下文简称为“集合”。那么如果我们加入 $3$，$j$ 就会变成 $1$，提示我们倒序枚举，然后直接累加贡献。

接下来对于一个数，比如增加一个，发现上面的集合里，我们有 $\{2,4\}$ 两种插入方案，所以 $g_{i,j}$ 对 $g_{i+1,j+1}$ 的答案贡献是 $(k-j)$。

还有就是 $g_{i,j+1},g_{i,j+2},g_{i,j+3}\dots,g_{i,k-1}$，这个我们已经用后缀和 $sum$ 统计好了，每一个都对 $g_{i+1,j+1}$ 有 $1$ 倍的贡献。想想看，我们只有一种数才可能让集合变成我们想要的大小，比如 $\{1,5,3\}$ 中，想要集合大小变成 $2$，只能加入 $5$，然后集合就是 $3,5$。

[code](https://codeforces.com/contest/1861/submission/237890328)

---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17316432.html)，第 $18$ 题。

为了后面写 **dp** 方便记原题中的 $k$ 为 $K$。

这种计计题有个套路：先考虑判断数组的价值（有时候是判断合法性），然后压进状态 **dp**。

---
大概判断思路是：能取排列就取排列。易证这样是最优的。

我们从小到大加入数组中的元素，令辅助**动态**数组为 $a$，大小为 $|a|$，初始为空。设答案的计数器为 $cnt$。

考虑当前加入的数为 $x$，
- 若 $x\not\in a$，之前 $|a|=K-1$，此时 $cnt\gets cnt+1$；
- 若 $x\not\in a$，之前 $|a|<K-1$，往 $a$ 中的末尾加入元素 $x$，更新数组大小。
- 若 $x\in a$，设它在 $a$ 中的位置为 $p$。则我们把 $1\sim p$ 的数全部从 $a$ 中删去，往 $a$ 中的末尾加入元素 $x$，更新数组大小。

最终的计数器为数组的价值，**注意到数组 $a$ 始终没有两个相同元素**。

---

这时候就好 **dp** 了，记 $f_{i,j,k}$ 表示填了数组中的前 $i$ 个数，$|a|=j$，数组价值 $cost=k$ 的方案数。

注意到 $0\le j\le K,0\le cost\le \dfrac{n}{K}$，于是状态数是 $O(n^2)$ 的。

按照上面三种情况转移：

$
f_{i,j,k}\gets (K-(j-1))\times f_{i-1,j-1,k}(j<K)\\
f_{i,0,k}\gets f_{i-1,K-1,k-1}\\
f_{i,j,k}=\sum\limits_{t\ge j} f_{i-1,t,k}(j>0)
$

第三种情况的 $t$ 是枚举**之前**的 $|a|$，显然 $|a|$ 不会变大，而 $j>0$ 是因为 $|a|$ 不会减少到 $0$，所以 $0$ 位置不可被转移。

---
设 $n,k$ 同阶，此时复杂度 $O(n^3)$，后缀和优化一下，复杂度 $O(n^2)$。**空间问题**可以把第一维压成 $0/1$，实现精细（这里的代码）可以直接把第一位压掉，直接开 $n^2$ 数组即可。

代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=4005,mod=998244353;
int n,K,L,f[N][N],g[N][N],h[N],ans;
inline int md(int x){return x>=mod?x-mod:x;}
int main()
{
	scanf("%d%d",&n,&K);L=n/K;f[0][0]=g[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int k=0;k<=L;k++) h[k]=f[K-1][k];
		for(int j=K-1;j>=1;j--) for(int k=0;k<=L;k++) f[j][k]=1ll*f[j-1][k]*(K-j+1)%mod;
		for(int k=1;k<=L;k++) f[0][k]=h[k-1];f[0][0]=0;
		for(int j=1;j<K;j++) for(int k=0;k<=L;k++) f[j][k]=md(f[j][k]+g[j][k]);
		for(int j=K-1;j>=0;j--) for(int k=0;k<=L;k++) g[j][k]=md(g[j+1][k]+f[j][k]);
	}
	for(int k=0;k<=L;k++) ans=(ans+1ll*k*g[0][k])%mod;
	return printf("%d",ans),0;
}
```

---

## 作者：ningago (赞：0)

对于一个固定的数列求权值，肯定是从前往后，能取排列就取。

对于一个长度为 $n$ 的数列，考虑往前填一些数。

- 要么填一个排列，转化到 $n-K$ 的子问题；
- 要么填一个数 $x$，那么我们的要求是：$x$ 不能和后面 $n-1$ 个填的数，组成排列。

那么可以设计 DP 状态：$dp_{i,j}$ 表示序列长度为 $i$，序列前面有 $j$ 个互不相同的数，要求填的数不能与前面这些数组成排列，的权值和（$0\leq j<K$），$cnt_{i,j}$ 表示方案数。

转移：

- $dp_{i,j}\leftarrow \sum_{k=1}^j dp_{i-1,k}$，表示填了一个之前 $j$ 个数里已经存在的数。
- $dp_{i,j}\leftarrow dp_{i-1,j+1}\times (K-j)$，表示填了一个新的数。
- $dp_{i,j}\leftarrow dp_{i-K,0}\times val(K,j)+cnt_{i-K,0}\times 1$，表示填一个排列。

$cnt_{i,j}$ 的递推类似，前缀和优化即可，现在的问题是求 $val(K,j)$ 表示 $K$ 个数的排列，满足下面条件的方案数：

- $\{a_K\}\ne\{1\}$；
- $\{a_{K-1},a_K\}\ne\{1,2\}$；
- $\{a_{K-2},a_{K-1},a_K\}\ne\{1,2,3\}$；
- $\cdots$
- $\{a_{K-j+1},\cdots,a_{K-1},a_K\}\ne\{1,2,\cdots, j\}$；

考虑用总方案数减去不合法的，具体地，减去的分别是：

- 后 $1$ 位满足第一条限制的方案数；
- 后 $2$ 位满足第二条限制，但不满足第一条限制的方案数；
- 后 $3$ 位满足第三条限制，但不满足前两条限制的方案数；
- $\cdots$

这样可以写成递推式：

$val(K,j)=K!-\sum_{i=1}^j val(i,i-1)\cdot (K-i)!$

这样不难发现有用的 $val$ 只有 $O(n)$ 种，直接转移即可。

$val$ 可能有组合意义直接算？我不会啊 QAQ。

复杂度 $O(nK)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <vector>
#include <queue>
#include <numeric>

char ST;
// #define int long long
#define ll long long
#define inf 0x3f3f3f3f
// #define inf 0x3f3f3f3f3f3f3f3f
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int readstr(char *str)
{
	int len = 0;
	char c = getchar();
	for(; !isalpha(c) && !isdigit(c) && c != '.' && c != '*' && c != '#' && c != '-' && c != '+'; c = getchar());
	for(;  isalpha(c) ||  isdigit(c) || c == '.' || c == '*' || c == '#' || c == '-' || c == '+'; c = getchar()) str[++len] = c;
	return len;
}

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second

void ckmax(int &x, int y) { x = x > y ? x : y; }
void ckmin(int &x, int y) { x = x < y ? x : y; }
#define mod 998244353
// #define mod 1000000007
void plus_(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b)
{
	int res = 1;
	for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(res, a);
	return res;
}

#define N 4010
int n, K, fac[N], invf[N];
struct node
{
	int cnt, sum;
	void operator += (node B)
	{
		plus_(sum, B.sum);
		plus_(cnt, B.cnt);
	}
	node operator * (int x)
	{
		node res;
		res.sum = 1ll * sum * x % mod;
		res.cnt = 1ll * cnt * x % mod;
		return res;
	}
	node operator + (int x)
	{
		node res;
		res.cnt = cnt;
		res.sum = (sum + cnt) % mod;
		return res;
	}
	node operator + (node B)
	{
		return (node){(cnt + B.cnt) % mod, (sum + B.sum) % mod}; 
	}
} dp[N][N], sum[N][N];

int val[N][N];
int prefac[N];

node SUM(int i, int j);

int VAL(int i, int j)
{
	if(!j) return fac[i];
	if(val[i][j]) return val[i][j];
	if(j == 1) return val[i][j] = (fac[i] - fac[i - 1] + mod) % mod;
	int res = fac[i];
	for(int k = 1; k <= j; k++)
		plus_(res, mod - 1ll * VAL(k, k - 1) * fac[i - k] % mod);
	return val[i][j] = res;
}

node DP(int i, int j)
{
	if(j == K) return (node){0, 0};
	if(i == 0) return (node){1, 0};
	if(~dp[i][j].cnt) return dp[i][j];
	node res = (node){0, 0};
	res += SUM(i - 1, j);
	res += DP(i - 1, j + 1) * (K - j);
	if(i >= K)
		res += (DP(i - K, 0) + 1) * VAL(K, j);
	return dp[i][j] = res;
}

node SUM(int i, int j)
{
	if(!j) return (node){0, 0};
	if(~sum[i][j].cnt) return sum[i][j];
	sum[i][j] = DP(i, j) + SUM(i, j - 1);
	return sum[i][j];
}

void solve()
{
	int T = 4000;
	for(int i = fac[0] = 1; i <= T; i++) fac[i] = 1ll * fac[i - 1] * i % mod, prefac[i] = (prefac[i - 1] + fac[i]) % mod;
	n = read(), K = read();
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			dp[i][j].cnt = sum[i][j].cnt = -1;
	int ans = DP(n, 0).sum;
	printf("%d\n", ans);
}

char ED;
signed main()
{
	solve();
	return 0;
}
```

---

