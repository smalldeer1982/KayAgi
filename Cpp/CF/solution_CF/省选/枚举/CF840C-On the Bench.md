# On the Bench

## 题目描述

A year ago on the bench in public park Leha found an array of $ n $ numbers. Leha believes that permutation $ p $ is right if for all $ 1<=i&lt;n $ condition, that $ a_{pi}·a_{pi+1} $ is not perfect square, holds. Leha wants to find number of right permutations modulo $ 10^{9}+7 $ .

## 说明/提示

For first example:

 $ [1,2,4] $ — right permutation, because $ 2 $ and $ 8 $ are not perfect squares.

 $ [1,4,2] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [2,1,4] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [2,4,1] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [4,1,2] $ — wrong permutation, because $ 4 $ is square of $ 2 $ .

 $ [4,2,1] $ — right permutation, because $ 8 $ and $ 2 $ are not perfect squares.

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
5 2 4 2 4 1 1
```

### 输出

```
144
```

# 题解

## 作者：SatsukiQAQ (赞：33)

upd：2020.9.3 修正了一些错误，重构了代码

看到各位dalao的题解都有组合数学，那么本蒟蒻就来发一篇纯dp的题解吧

首先我们考虑两个数 $ a ,b $ 我们设 $ a = n ^ 2 \times p , b = m ^ 2 \times q $ ( $n, m$ 为整数，$p, q$ 为素数或几个不同素数的积),此时不难发现: $a \times b$ 为完全平方数，当且仅当 $p = q$。因此，我们将序列中的每个数的质因子除去(即将上面的 $a, b$ 变为 $p, q$ )，就可以将原问题转化为：给你一个序列，求有多少种排列使得相邻两个数两两不同。

现在我们考虑将数一个个地放回原序列，则有下面三种情况:

1.放入的数与左右两边相邻的其中一个数相同（另一个不相同）

2.放入的数与左右两边相邻的两个数相同

3.放入的数与左右两边相邻的数都不相同，但左右相邻的数相同

4.放入的数与左右两边相邻的数不相同，并且左右相邻的数也不相同

于是设 $dp[i][j][k]$ 表示 枚举到第 $i$ 个数，有 $j$ 个相同的相邻的位置，$k$ 个与当前数字相同的相邻的位置 的方案数

那么我们会发现，第一种情况与第二种情况对于答案的贡献是一样的，因此将原数组排序后，就可以如下这么转移（ $x$ 表示第 $i+1$ 个数插入前有多少个与 $a[i]$ 相同的数）

对于1,2两种情况，有 $dp[i][j][k] \times (x+x-k+1) -> dp[i+1][j+1][k+1]$

对于3，有 $dp[i][j][k] \times (j-k+1) -> dp[i+1][j-1][k]$

对于4，有 $dp[i][j][k] \times ((i+1)-(x+x-k)-(j-k)) -> dp[i+1][j][k]$

 $dp[n][0][0]$ 即为答案 复杂度为 $ O(n^3) $

可以发现，$dp[i+1][][]$ 只与 $dp[i][][]$ 有关，因此上滚动数组。

代码:

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e2 + 10, mod = 1e9 + 7;
int n, same, a[MAXN];
long long dp[2][MAXN][MAXN];
void div(int &x)
{
	for(int i = 2; i * i <= x; ++ i)
		while(!(x % (i * i)))
			x /= (i * i);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i) scanf("%d", &a[i]), div(a[i]);
	sort(a + 1, a + 1 + n);
	dp[0][0][0] = 1;
	int now(0);
	for(int i = 1; i <= n; ++ i)
	{
		if(a[i] != a[i - 1])
		{
			for(int j = 0; j <= i; ++ j)
				for(int k = 1; k <= same; ++ k)
				{
					(dp[now ^ 1][j][0] += (dp[now ^ 1][j][k] % mod)) %= mod;
					dp[now ^ 1][j][k] = 0;
				}
			same = 0;
		}
		for(int j = 0; j <= i; ++ j)
			for(int k = 0; k <= min(same, j); ++ k)
			{
				if(j && k) (dp[now][j][k] += (dp[now ^ 1][j - 1][k - 1] * (2 * same - k + 1) % mod)) %= mod;
				(dp[now][j][k] += (dp[now ^ 1][j + 1][k] * (j + 1 - k) % mod)) %= mod;
				(dp[now][j][k] += (dp[now ^ 1][j][k] * (i - (2 * same - k) - (j - k)) % mod)) %= mod;
			}
		now ^= 1;
		++same;
		memset(dp[now], 0, sizeof(dp[now]));
	}
	printf("%lld\n", dp[now ^ 1][0][0]);
	return 0;
} 
```

---

## 作者：Kewth (赞：28)

复杂度更优秀的做法。

把一个数的平方因子都去掉，那么两个数的乘积为完全平方数当且仅当两个数相等，问题转换为给定一个序列，求这个序列没有相邻元素相同的排列数。

考虑容斥，设 $f_i$ 表示有至少 $i$ 对相等的数相邻的方案数，
那么答案就是 $\sum_{i=0}^n f_i (-1)^{n - i}$ 。

求 $f_i$ 就是钦定 $i$ 对数，把它们绑在一起看作整体求绑定的方案数再乘个绑定后的排列数 $(n - i)!$ 。

而值不同数之间是不会绑定的，也就是说不同的值之间互不影响，绑定方案数可以乘法原理。

那么对于值为 $x$ 的数求出 $g_{x,i}$ 表示在这些数中绑定 $i$ 对数的方案数，总的绑定方案数就是就是所有 $g_x$ 的卷积合并。

可惜模数 $10^9+7$ ，暴力卷积即可，复杂度 $O(n^2)$ ，理论上可以分治优化卷积做到 $O(nlog^2n)$ 。

参考实现：

（我的实现中 $O(n\sqrt{V})$ 暴力找的完全平方数）

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 5050, mod = 1000000007;
int a[maxn];
int b[maxn], bp;
ll f[maxn], g[maxn], h[maxn];
ll fac[maxn], ifac[maxn];

ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = read;
	int max = int(sqrt(1000000000));
	for(int i = 1; i <= n; i ++) {
		a[i] = read;
		for(int x = max; x; x --)
			if(!(a[i] % (x * x))) {
				a[i] /= x * x;
				break;
			}
	}

	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++)
		if(a[i] != a[i - 1])
			b[++ bp] = 1;
		else
			++ b[bp];

	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for(int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	int lim = 0;
	f[0] = 1;

	for(int i = 1; i <= bp; i ++) {
		ll coe = 1;
		for(int j = b[i]; j; j --) {
			g[b[i] - j] = coe * ifac[b[i] - j] % mod;
			(coe *= j * (j - 1)) %= mod;
		}
		for(int j = 0; j <= lim + b[i]; j ++)
			h[j] = 0;
		for(int j = 0; j <= lim; j ++)
			for(int k = 0; k < b[i]; k ++)
				(h[j + k] += f[j] * g[k]) %= mod;
		lim += b[i] - 1;
		for(int j = 0; j <= lim; j ++)
			f[j] = h[j];
	}

	for(int j = 0; j <= lim; j ++)
		(f[j] *= fac[n - j]) %= mod;

	ll ans = 0;
	for(int j = 0; j <= lim; j ++)
		ans += j & 1 ? - f[j] : f[j];
	ans %= mod;
	if(ans < 0) ans += mod;

	printf("%lld\n", ans);
}
```

---

## 作者：Soulist (赞：18)

$2600$分的 dp 题，还是相当难的= =

$\rm Sol:$

令$d(x)=[\sqrt{x}\in Z]$

假设$d(a\times b)=1$，$d(a\times c)=1$，则应当有：$d(a^2\times b\times c)=1$，又因为$d(a\times a)=1$，所以$d(b\times c)=1$。

换而言之构成完全平方数的性质具有传递性，也就是说假定把能相互构成完全平方数的数放到了一个集合内，则其**内部无论怎么摆都会构成**完全平方数，反之，**这个集合内的数无论和其之外的数怎么摆都必然不会构成完全平方数。**

于是可以先把这些集合缩起来，我们的问题变成，给定$m$个集合，每个集合内有$k$个元素（注意题面被修改了，所有元素均视为不同的），且有：$\sum sz=n$，求有多少种方案排列这$n$个元素满足任意两个相同集合的元素不相邻。

注意到放置的方案可以逐个考虑，即先考虑其他的集合再考虑本集合。

考虑前 $i-1$ 个集合的放置对于当且考虑的集合的影响，不难发现，前 $i-1$ 个集合的放置实际上是对于可使用的空位的影响

我们不妨假设前 $i-1$ 个集合放置后紧密地 **贴在一起**

这样考虑当前集合，其放置入前$i-1$个集合的方法便只有两种：

$1.$直接在两端生成

$2.$在前$i-1$个集合所构成的序列中插入

考虑 dp ，令$dp_{i,j}$表示前 $i-1$ 个集合，有 $j$ 个位置满足不合法(即，有 $j$ 个位置满足其和其前面的数属于同一个集合)的方案数，考虑如何放置当前集合内的 $t$ 个点，由于他们对于外界没有贡献，所以我们可以假定

先将他们分成 $k$ 个连续的段落，则此时至少会有 $t-k$ 个位置满足不合法，然后将这 $k$ 个连续段落插入进去。

将 $t$ 个有区别数分成 $k$ 个连续段落的方案数应当为将 $t-1$ 个数分成 $k$ 个连续段落的方案数 $\times (t-1+k)$（即将最后一个点插入到先前的集合的某个元素之前），或者第 $i$ 个数单独成为一个集合，但是成立的这个集合可以摆在这 $j-1$ 个集合中任意一个集合的前/后，所以我们得到转移（貌似和斯特林数很像= =）

$$g_{i,j}=g_{i-1,j}\times (i-1+j)+g_{i-1,j-1}\times j$$

预处理出系数之后，我们可以得到假定将这$k$个位置插入原来的序列，假定前 $i-1$ 个集合所构成的序列长度为$m$，则我们的问题是将这$k$个连续的段落丢入这$m$个数当中，可以认为是放置入$m+1$个挡板中，不过其中有$j$个位置，满足其和前面的位置乘起来会变成完全平方数，所以假定我们放置入了这$j$个位置中的$l$个位置（即可以认为破坏了$l$个位置）

由于这样分挡板本身对于答案的影响是导致增加了$t-k$个不合法的位置，同时其又破坏了$l$个不合法的位置，所以我们可以得到，这样放置后原来序列中不合法的位置的数量$j\to j+(t-k)-l$

于是有：

$$dp_{i,j+(t-k)-l}=\sum dp_{i,j}\times g_{t,k}\times \dbinom{j}{l}\times \dbinom{sum+1-j}{k-l}$$

好了接下来我们应该来谈谈他的复杂度了，首先状态数是毫无疑问的$O(n^2)$

然而转移的复杂度却不止如此，你可以看到，我们枚举了$4$个量$i,j,k,l$

其中$i$和$j$的枚举复杂度为$O(\text{集合数量})$和$O(n)$，然而$k$的枚举总量为集合大小即：$\sum k=n$，且$l$的枚举复杂度为$O(n)$，所以我们可以得到总体复杂度为$O(n\times n\times \sum k)=O(n^3)$

置于边界，应当为$dp_{0,0}=1$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ; 
const int N = 300 + 5 ; 
int n, m, a[N], num[N], g[N][N], dp[N][N], C[N][N] ; 
void inc( int &x, int y ) {
	x += y, x %= P ; 
}
signed main()
{
	n = gi() ; int x, sum = 0 ;
	rep( i, 1, n ) {
		x = gi() ; int type = 0 ;
		rep( j, 1, m ) {
			int u = a[j] * x, v = sqrt(u) ; 
			if( 1ll * v * v == u ) { ++ num[j], type = 1 ; break ; }
		}
		if( !type ) a[++ m] = x, num[m] = 1 ; 
	}  g[0][0] = dp[0][0] = 1 ; 
	rep( i, 0, n ) rep( j, 0, i ) C[i][j] = ( j == 0 ) ? 1 : ( C[i - 1][j - 1] + C[i - 1][j] ) % P ; 
	rep( i, 1, n ) rep( j, 1, i ) 
	g[i][j] = ( g[i - 1][j] * ( i + j - 1 ) % P + ( j * g[i - 1][j - 1] ) % P ) % P ; 
	rep( i, 1, m ) {
		rep( j, 0, sum ) rep( k, 1, num[i] ) rep( l, 0, j )
		inc( dp[i][j + (num[i] - k) - l], ( ( ( dp[i - 1][j] * g[num[i]][k] ) % P * C[j][l] ) % P * C[sum + 1 - j][k - l] ) % P ) ;
		sum += num[i] ; 
	}
	printf("%lld\n", dp[m][0] ) ;
	return 0 ;
} 
```

---

## 作者：lgswdn_SA (赞：17)

总结了一下三种做法。个人觉得这是一道很好的题目，能够明白三种不同的解法对理解这种 DP 和容斥应该也有帮助（吧）。【new：添加了理论 $O(n\log^2n)$ 的做法，但是因为 sb 模数没有 implement】。

首先考虑相乘等于平方相当于两个数除去平方因子后相同。所以我们把所有数都除去平方因子，然后问的相当于是序列有多少排排列满足相邻两项不等。为了更方便地 DP，我们对修改后的序列排序。接下来就是三种解法（代码用命名空间合成了一份，所以你会发现代码出奇的长，只是因为里面实际上把三种解法全写在里面了）。

**$O(n^3)$ 做法**

考虑用插入的DP。$f(i,j,k)$ 表示目前已经插入了前 $i$ 个数，且目前有 $j$ 个相邻位置的数相同，有 $k$ 个位置满足与当前转移的数字相同的数相邻。转移先设 $s_i$ 表示 $i$ 之前有 $s_i$ 个数与第 $i$ 个数相等。考虑三种情况。

1. 插入后自己与相邻的数相同（$j$ 变大）。

   此时对 $f(i,j,k)$ 的贡献为 $(2_s{i}-k+1)\times f(i-1,j-1,k-1)$。

2. 插入后没有任何变化（$j$ 不变）。

   此时对 $f(i,j,k)$ 的贡献为 $(i-2s_{i+1}+2k-j)\times f(i-1,j,k)$。

3. 插入后两个相同的数不相邻了（$j$ 变小）。

   此时对 $f(i,j,k)$ 的贡献为 $(j-k+1)\times f(i-1,j+1,k)$。

上面转移问题其实很大，因为如果 $a_i\neq a_{i+1}$，那么在计算 $i-1$ 对 $i$ 的贡献的时候，需要有把所有 $k>0$ 的 $f(i-1,j,k)$ 清空并将贡献记到 $f(i-1,j,0)$ 中，这样才能保证不会有问题。至于空间我们滚动一下。

**另一种 $O(n^3)$ 做法**

我们发现这个序列是可以被分成块的，满足每一块内数字相同。于是我们考虑每次插入好多个数而不止一个数。设第 $i$ 块有 $s_i$ 个相同的数。设 $f(i,j)$ 表示目前插入了前 $i$ 块，并且有 $j$ 个位置相邻的数相同。

对于如何转移，我们考虑先枚举把第 $i$ 块拆分成 $k$ 个小块（这种方案数设其为 $g_{s_i,k}$，比较好弄，之后再说）。首先其内部会产生 $s_i-k$ 对相邻的相同的数。然后我们考虑枚举有多少个小块插入到了满足左右两边数值一样（即在插入前位置相邻且数值相同），设为 $p$，则对位置相邻且数值相同的对数的贡献为 $-p$。

设 $q$ 为第 $i$ 块前插入了多少个数（即块的大小总和），于是乎一共有 $q+1$ 个空位可以插。
$$
f(i,j+s_i-k-p) \leftarrow \sum_{k} \binom{j}{p}\binom{q+1-j}{k-p}g(s_i,k)f(i-1,j)
$$
我们看看 $g$ 的转移。注意到块内的数是有顺序而言的。
$$
g(i,j)\leftarrow (i-1+j)\times g(i-1,j)+j\times g(i-1,j-1)
$$
关于初值，有 $g(0,0)=f(0,0)=1$。

时间复杂度亦是 $O(\sum s_in^2)=O(n^3)$。

**比较仙的 $O(n^2)$**

考虑容斥。首先我们转化为无标号的计数（最后乘上 $\sum s_i!$ 就能转化成有标号的）。对于一个不合法方案，我们观察每一个数值，设其能被分为 $b_i$ 个连续段。我们容斥 $b$，设 $\sum b=r$。
$$
\sum (-1)^{r} \frac{(n-r)!\prod\binom{s_i-1}{b_i}}{\prod (s_i-b_i)!}
$$
其中 $(n-r)!$ 为所有可能性，然后要除掉那些已经在一个连续段内的数的排列情况。然后分子的那个 $\prod$ 是对连续段做插板法。考虑用 DP 求出这个值（类似背包计数）。$f(i,j)$ 表示前 $i$ 个数值，目前 $r=j$ 的 $\sum (-1)^r \frac{\prod ...}{\prod ...}$。显然我们不需要把 $(n-r)!$ 这一项包括在 DP 的计算中，因为它可以在计算答案的时候算。

于是我们有转移:
$$
f(i,j)=\sum_{k} f(i-1,j-k)\times \frac{\binom{s_i-1}{k}}{(s_i-k)!}
$$
转移看上去非常卷积。但是我多项式很拉。所以就不管他了。

初值 $f(0,0)=1$。注意到我们还要转化成有标号计数，所以实际答案 $ans=(\prod s_i!) \times \sum f_{cnt,i}(n-i)!$。时间复杂度为 $O(\sum s_in)=O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=309,mod=1e9+7;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

void pls(int &x,int y) {x+=y; x=(x>=mod?x-mod:x);}

int n,a[N],s[N],fac[N],inv[N],ifac[N];

void pre() {
	inv[0]=inv[1]=fac[0]=ifac[0]=1;
	rep(i,1,n) fac[i]=fac[i-1]*i%mod;
	rep(i,2,n) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	rep(i,1,n) ifac[i]=ifac[i-1]*inv[i]%mod;
}
int C(int x,int y) {
	if(x<0||y<0||x<y) return 0;
	else return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

namespace Solution_1 { //第一种O(n^3)做法 
	int s[N],f[2][N][N];
	void solve() {
		int d=0;
		rep(i,1,n) {
			if(a[i]==a[i-1]) s[i]=s[i-1]+1;
			else s[i]=0;
		}
		f[0][0][0]=1;
		rep(i,1,n) {
			if(a[i]!=a[i-1]) {
				rep(j,0,i) rep(k,1,s[i-1])
					pls(f[d^1][j][0],f[d^1][j][k]), f[d^1][j][k]=0;
			}
			rep(j,0,i) {
				int upk=min(s[i],j);
				rep(k,0,upk) {
					if(j&&k) pls(f[d][j][k],f[d^1][j-1][k-1]*(2*s[i]-k+1)%mod);
					pls(f[d][j][k],f[d^1][j][k]*(i-2*s[i]+2*k-j)%mod);
					pls(f[d][j][k],f[d^1][j+1][k]*(j-k+1)%mod);
				}
			}
			memset(f[d^1],0,sizeof(f[d^1]));
			if(i!=n) d^=1;
		}
		printf("%lld\n",f[d][0][0]);
	}
}

namespace Solution_2 { //第二种o(n^3)做法 
	int cnt,s[N],g[N][N],f[N][N];
	void calc_g() {
		g[0][0]=1;
		rep(i,1,n) rep(j,1,i) g[i][j]=((i+j-1)*g[i-1][j]+j*g[i-1][j-1])%mod;
	}
	void calc_f() {
		int q=0;
		f[0][0]=1;
		rep(i,1,cnt) {
			rep(j,0,q) rep(k,1,s[i]) rep(p,0,j) {
				pls(f[i][j+s[i]-k-p],C(j,p)*C(q+1-j,k-p)%mod*g[s[i]][k]%mod*f[i-1][j]%mod);
			}
			q+=s[i];
		}
	}
	void solve() {
		rep(i,1,n) {
			if(a[i]!=a[i-1]) {
				s[++cnt]=1;
			} else {
				s[cnt]++;
			}
		}
		calc_g();
		calc_f();
		printf("%lld\n",f[cnt][0]);
	}
}

namespace Solution_3 { //第三种O(n^2)做法 
	int cnt,s[N],f[N][N];
	void solve() {
		rep(i,1,n) {
			if(a[i]!=a[i-1]) {
				s[++cnt]=1;
			} else {
				s[cnt]++;
			}
		}
		int mxr=0;
		f[0][0]=1;
		rep(i,1,cnt) {
			mxr+=s[i]-1;
			rep(j,0,mxr) {
				int upk=min(s[i],j);
				rep(k,0,upk) 
					pls(f[i][j],f[i-1][j-k]*C(s[i]-1,k)%mod*ifac[s[i]-k]%mod);
			}
		}
		int ans=0;
		rep(i,0,mxr) pls(ans,f[cnt][i]*fac[n-i]%mod*(i%2==0?1:mod-1)%mod);
		rep(i,1,cnt) ans=ans*fac[s[i]]%mod;
		printf("%lld\n",ans);
	} 
}

signed main() {
	n=read();
	rep(i,1,n) {
		a[i]=read();
		for(int j=2;j*j<=a[i];j++)
			while(a[i]%(j*j)==0) a[i]/=j*j;
	}
	sort(a+1,a+n+1);
	pre();
	Solution_3::solve(); //all solutions can pass
	return 0;
}
```

**New: $O(n\log^2n)$**（理论方法）

考虑优化 DP 的计算。我们设第 $i$ 行的 DP 用幂级数表示为 $F_i$，然后设 

$$
G_i=\sum_{k=0}^{s_i} \frac{\binom{s_i-1}{k}}{(s_i-k)!}x^k
$$
，那么有
$$
F_i=F_{i-1}\times G_{i}
$$

所以我们求的目标 $F_{cnt}=\prod G_i$。一个非常重要的东西是，我们发现 $\sum s_i=n$，也就意味着我们可以通过分治 NTT 的方法做到 $O(n\log^2 n)$。

（你会发现这只不过是 [集训队作业2019] 青春猪头少年不会梦到兔女郎学姐 的弱化一万次的版本）

最后你发现模数是 $10^9+7$ 然后作者不想写三模NTT。

---

## 作者：yijan (赞：9)

### CF840C On the bench

为了可能更好的阅读体验，建议到 luogu 博客或者 [这里](https://www.yijan.co/cf840c-on-the-bench/) 阅读

我们考虑当 $a_ia_j,a_ja_k$ 均为完全平方数的时候，$a_ia_ka_j^2$ 也一定是一个完全平方数，于是 $a_ia_k$ 也是完全平方数了。也就是说我们可以把所有数划分成很多类，每一类里面任意两个数乘起来都是完全平方，并且不同类的数乘起来一定不是完全平方。

如果把 “同一类” 这个问题看成 “同一种颜色”，现在问题就在于给定很多个数，每个数有自己的颜色，求排列数量满足不存在相邻的相同颜色的数。

这是个经典的容斥问题，可以考虑枚举不满足这个条件的相邻的数的数量。具体来说，我们分别处理一下每一种颜色。假设当前颜色的数个数为 $a_i$ ，把相邻的颜色相同的缩到一起，枚举一下缩到一起后的数的个数，容斥系数为 $(-1)^k$ 其中 $k$ 为缩到一起（也就是不满足条件）的个数，那么缩后形成的方案数量乘上容斥系数以及算上排列去重就是：
$$
(-1)^{j} {a_i - 1 \choose j - 1} \frac 1 {(a_i-j)!}
$$
现在问题就是我们要从每个颜色中选择一部分出来，把这个系数乘在一起，最后乘上 $k!$ ，就是缩成这么多个的总共的数量乘上容斥系数，加起来即可。

但是这样做了之后我们是将所有颜色视作相同的，但是在这个题还得给颜色分配标号，因此还得乘上所有颜色的阶乘的乘积。

这个东西可以通过分治 FFT / NTT 做到 $O(n\log n)$ ，但是既然出题人只给了 $n \le 300$ 就暴力 dp 就好了。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 316
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
#define P 1000000007
typedef long long ll;
int n;
int A[MAXN];

int Pow( int x , int a ) {
    int ret = 1;
    while( a ) {
        if( a & 1 ) ret = 1ll * ret * x % P;
        x = 1ll * x * x % P , a >>= 1;
    }
    return ret;
}

bool chk( ll x ) {
    ll qwq = sqrt( x );
    return ( qwq * qwq == x );
}

int f[MAXN] , a[MAXN] , m;
int dp[MAXN][MAXN] , td[MAXN][MAXN] , J[MAXN] , iJ[MAXN];

int C( int a , int b ) {
    return a < b ? 0 : J[a] * 1ll * iJ[b] % P * iJ[a - b] % P;
}

void solve() {
    cin >> n;
    int flg;
    rep( i , 1 , n ) {
        scanf("%d",A + i);
        flg = 0;
        rep( j , 1 , i - 1 ) if( chk( 1ll * A[i] * A[j] ) ) {
            ++ a[f[j]] , flg = 1; break;
        }
        if( !flg ) f[i] = ++ m , a[m] = 1;
    }
    J[0] = iJ[0] = 1;
    rep( i , 1 , n ) J[i] = J[i - 1] * 1ll * i % P , iJ[i] = Pow( J[i] , P - 2 );
    int s = 0;
    dp[0][0] = 1;
    rep( i , 1 , m ) {
        rep( j , 0 , s ) {
            rep( t , 0 , a[i] - 1 ) {
                dp[i][j + a[i] - t] += 1ll * dp[i - 1][j] * ( ( t & 1 ) ? P - 1 : 1 ) % P * C( a[i] - 1 , t ) % P * iJ[a[i] - t] % P;
                dp[i][j + a[i] - t] %= P;
            }
        }
        s += a[i];
    }
    int res = 0;
    rep( i , 1 , n ) res = ( res + 1ll * J[i] * dp[m][i] % P ) % P;
    rep( i , 1 , m ) res = 1ll * res * J[a[i]] % P;
    cout << res << endl;
}

signed main() {
//    freopen("in1.in","r",stdin);
//    freopen("fuckout","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：liangzihao (赞：9)

如果$a*b$为完全平方数，$a*c$为完全平方数，那么$b*c$也为完全平方数。

证明：对于任意一个数$x$，质因数分解后如果每一个质数的指数都是偶数($0$也算偶数)，那么这个数就是完全平方数。根据每一个质数指数的奇偶性，我们可以写出一个二进制数，记为$bit_x$。而两数相乘，其质数的指数相加，对于奇偶性就是异或。因为，$bit_a\ xor\ bit_b=0$，$bit_a\ xor\ bit_c=0$，所以$bit_b=bit_c$，即$bit_b\ xor\ bit_c=0$。因此，$b*c$也是完全平方数。

所以我们可以把两两可以组成完全平方数的数分成$cnt$组，每组大小为$num_i$。
我们设$f[i][j]$为前$i$组，有$j$个冲突点(即相邻两个数积为完全平方数)的方案数。因为可以随意调换，所以第$i$组有$num_i!$个方案。我们再枚举$k$，表示把第$i$个组分成$k$块，即放$k-1$个挡板，方案数为$\binom{k-1}{num_i-1}$，这样会产生$num_i-k$个不合法位置。

设$sum$为前$i-1$个组数的个数，这$k$个块可以放入$sum+1$个位置上，而其中$j$个位置是不合法位置，枚举有$l$个不非法位置中间插入了当前组的块，这样就会减少$l$个不合法位置，也使用了$l$个块。在$j$个位置中选择$l$个位置，方案数为$\binom{l}{j}$。在剩下的$sum+1-j$个位置中选择剩下的$k-l$个块，方案数为$\binom{k-l}{sum+1-j}$。

所以，总转移方程式为：
$$f[i][j-l+num_i-k]=\sum{num_i!}*\binom{k-1}{num_i-1}*\binom{l}{j}*\binom{k-l}{sum+1-j}$$

因为$\sum_{i=1}^{cnt}num_i=n$，所以，总复杂度为$O(n^3)$。式子有点多，有错误请指出。

代码：
```
#include <iostream>
#include <cstdio>
#include <cmath>
#define LL long long

const LL maxn=307;
const LL mod=1e9+7;

using namespace std;

LL num[maxn],a[maxn];
LL f[maxn][maxn];
LL n,cnt,x,sum;
LL jc[maxn],njc[maxn];

LL power(LL x,LL y)
{
    if (y==1) return x;
    LL c=power(x,y/2);
    c=(c*c)%mod;
    if (y%2) c=(c*x)%mod;
    return c;
}

LL C(LL x,LL y)
{
    if ((x<0) || (y<0) || (y>x)) return 0;
    if ((x==0) || (y==x))  return 1;
    return jc[x]*njc[y]%mod*njc[x-y]%mod;
}

int main()
{
    scanf("%lld",&n);
    for (LL i=1;i<=n;i++)
    {
        scanf("%lld",&x);
        LL flag=0;
        for (LL j=1;j<=cnt;j++)
        {
            LL c=trunc(sqrt(x*a[j]));
            if (c*c==x*a[j])
            {
                flag=1;
                num[j]++;
                break;
            }
        }
        if (!flag) num[++cnt]=1,a[cnt]=x;
    }
    jc[0]=jc[1]=1;
    njc[0]=njc[1]=1;
    for (LL i=2;i<=n;i++)
    {
        jc[i]=(LL)(jc[i-1]*i)%mod;
        njc[i]=power(jc[i],mod-2);
    }	
    f[0][0]=1;
    for (LL i=1;i<=cnt;i++)
    {
        for (LL j=0;j<=sum;j++)
        {
            for (LL k=1;k<=num[i];k++)
            {
                for (LL l=0;l<=j;l++)
                {
                    LL d=j-l+num[i]-k;
                    if ((d>=0) && (d<n))
                    {
                        f[i][d]=(f[i][d]+jc[num[i]]*C(num[i]-1,k-1)%mod*C(j,l)%mod*C(sum+1-j,k-l)%mod*f[i-1][j]%mod)%mod;
                    }
                }
            }
        }
        sum+=num[i];
    }
    printf("%I64d\n",f[cnt][0]);
} 
```

---

## 作者：pengyule (赞：8)

~~题解区朴素 dp 算法者仅二，而其言多模糊。余屡读而不解其转移方程，气急，用自己的方法一遍 A，喟然叹曰，还是我的方法好。~~

排列计数 dp 通常考虑插入 dp。如，最终序列中 $[1,X,X,3,X,5,X]$，如果我们当前只考虑了 $1,3,5$，那么眼前的排列长这样：$[1,3,5]$，而插入一个 $X$ 就是扒开一个夹缝（也可能是首尾）插进去：$[1,X,3,5]$。

----

第一个观察是两数之和为平方，这是一个让人乍一看难以处理的说法。考虑换说法。手推小数据或分析。得知等价于两数各自消去平方因子后相等。

---

接下来便可以 dp 了。我们面对的问题是，现在有 $n$ 个带有颜色的球，所有球视作各不相同，不能使相邻球颜色相同（下文称为一对冲突），求排列方案数。设 $f(i,j,k)$ 表示考虑了 $i$ 个球，$j$ 个冲突，$k$ 个**会产生冲突的夹缝**（**针对于当前颜色而言**）。  
注释：（1）夹缝：两数之间或首或尾。（2）针对于当前颜色而言：插入一个当前颜色（第 $i$ 个球的颜色）的球会和相邻的球产生冲突。

**由于 $k$ 是相对于颜色的，因此如果 $i-1$ 与 $i$ 不是同一种颜色的，那就压根不在同一个频率上考虑问题，很不好。所以我们考虑把同色的球放在一起考虑，在两色交接的地方（此时 $k$ 会归零）继承一下之前的 dp 数据。**

----

这一部分来解决粗体字谈到的问题。  
$$
f(i-1,j,0)\gets \sum_k f(i-1,j,k)
$$
这里 $i-1$ 跟 $i$ 的颜色是不同的，所以现在我们从相对 $i-1$ 的颜色而言转变为相对 $i$ 的颜色而言，而不论之前的 $k$ 如何，我们现在（还没有放入任何 $i$ 的颜色的求时）的 $k$ 一定是 $0$。  
这里是在为马上到来的颜色段的 dp 做准备，还没有真正开始 dp。

---

现在我们可以正式开始这一颜色段的 dp 了。现在我们的 $i-1$ 的 dp 数组也是相对于我们的颜色而言了，所以可以无所顾忌地分类讨论转移了。

有能力的同学看完状态就知道怎么转移了。这里只提一下要点：
- 放了 $i-1$ 个球的时候，总共有 $i$ 个夹缝。
- 有 $j$ 个夹缝是两侧颜色相等的。
- 如果记 $x$ 为考虑到 $i-1$ 时有多少个当前颜色的球，那么有 $2x-k'$ 对当前颜色的冲突。$k'$ 是 $i-1$ 的 dp 数组的第三维。
- 所有夹缝只有 $3$ 类：被 $k$ 算的、两侧相同且不是当前颜色的、两侧不同且都不是当前颜色的。

1° 产生冲突  
$$
f(i,j,k)\gets f(i-1,j-1,k-1)\cdot (k-1)
$$
2° 化解冲突
$$
f(i,j,k)\gets f(i-1,j+1,k-2)\cdot (j-2x+k-1)
$$
3° 无关
$$
f(i,j,k)\gets f(i-1,j,k-2)\cdot (i-j+2x-2k+4)
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/4x26d7pl.png)

---

现在我们可以开始写代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=305,mod=1e9+7;
inline void add(int &x,int y){(x+=y)>=mod&&(x-=mod);}
int n,a[N],f[N][N][N];
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=sqrt(a[i])+0.1;j>1;j--)if(a[i]%(j*j)==0){a[i]/=j*j;break;}
	}
	sort(a+1,a+n+1);
	f[0][0][0]=1;
	for(int i=1,x=0;i<=n;i++){
		if(i>1&&a[i]!=a[i-1]){
			for(int j=0;j<=n;j++)for(int k=1;k<=n;k++)
				add(f[i-1][j][0],f[i-1][j][k]),f[i-1][j][k]=0;
			x=0;
		}
		for(int j=0;j<=n;j++)
			for(int k=1;k<=n;k++){
				if(j)add(f[i][j][k],f[i-1][j-1][k-1]*(k-1ll)%mod);
				if(k>=2){
					if(j-2*x+k-1>=0)add(f[i][j][k],f[i-1][j+1][k-2]*(j-2*x+k-1ll)%mod);
					if(i-j+2*x-2*k+4>=0)add(f[i][j][k],f[i-1][j][k-2]*(i-j+2*x-2*k+4ll)%mod);
				}
			}
		x++;
	}
	int ans=0;
	for(int k=0;k<=n;k++)add(ans,f[n][0][k]);
	cout<<ans;
}
```

----

现在我们可以提交了。  
通过了。

---

## 作者：Pengzt (赞：5)

[CF840C](https://www.luogu.com.cn/problem/CF840C)

考虑什么时候 $a_i\times a_j$ 为一个平方数。先将其分解质因数，去掉不影响的平方因子，得到新数组 $b$。当且仅当 $b_i=b_j$ 时有 $a_i\times a_j$ 为平方数。

然后题目就变成了求所有满足最后相邻数不相等的方案数。直接是不好做的，考虑容斥。

令 $f_{i,j}$ 表示前 $i$ 个值中，恰好有 $j$ 个相等的相邻数。

令第 $i$ 个值出现的次数为 $c_i$，则有 $f_{i,j}=\sum f_{i-1,j-k}\times\dbinom{c_i}{k}\times\dfrac{(c_i-1)!}{(c_i-k-1)!}$。后面的系数是指在 $c_i$ 个数中选 $k$ 个段的方案数。

最后的答案显然就是：$\sum\limits_{i=0}^{n-1}(-1)^i(n-i)!f_{num,i}$。

时间复杂度：$\mathcal{O}(n^3)$。

[评测记录](https://www.luogu.com.cn/record/126068715)。

---

## 作者：joke3579 (赞：3)

这里提供 $O(n\log^2 n)$ 做法的讲解与实现。

首先讲解 $O(n^2)$ 容斥 dp 的部分。

为方便，设 $s_i$ 为除去平方因子后第 $i$ 大的数出现了多少次。  
为方便，首先进行无标号计数，最后乘入 $\prod (s_i!)$ 即可。

于是问题转化成了有颜色无标号小球排列计数，需要相邻小球颜色不同。这就比较的典。   
我们考虑一个容斥。首先设有 $b$ 段长度大于 $1$ 的相同颜色段，然后我们把这些段缩成一个小球。设第 $i$ 种颜色被缩成的小球数是 $t_i$（$\sum t_i = b$），则有
$$ans = \sum_{b}(-1)^{b}  \frac{(n-b)!\prod_{i}\binom{s_i-1}{t_i}}{\prod_{i}(s_i - t_i)!}$$

$(n-b)!$ 是当前缩完后的序列的总可能性，然后我们得除去那些已经在一个连续段内的排列情况。这是分子。分母考虑对连续段做一下插板法使得计数的序列都满足不会再缩起来的情况。

先不考虑 $(n-b)!$，最后得到答案时乘进去就行。套路地设 $f_{i,j}$ 为前 $i$ 个数值，$b=j$ 时的答案。定义 $n < m$ 时 $\binom{n}{m} =0$，$n < 0$ 时 $n! = 0$，我们有转移
$$f_{i,j} = \sum_{k=0}^j f_{i-1,j-k} \times \frac{\binom{s_i-1}{k}}{(s_i - k)!}$$

乘入阶乘即可得到答案。

然后考虑构造两个生成函数进行统一转移。构造生成函数 $F_k$ 与 $G_k$ 满足
$$F_k(x) = \sum_{i=0}f_{k,i} x^i$$
$$G_k(x) = \sum_{i=0}^{s_k} \frac{\binom{s_k-1}{i}}{(s_k - i)!}x^i$$
则我们能发现 $F_k = F_{k-1} \times G_k$。而  $F_0 = 1$。
则答案即为
$$\sum_{i=0}^{n-b}(-1)^{i}\times (n-i)! \times \left([x^i]\prod_{i=1}^bG_i\right)$$

后面那个东西保证了度数加和是 $n$，所以可以启发式合并。我们开一个按照多项式度数排序的小根堆，每次取度数最小的多项式卷起来。

总时间复杂度 $O(n \log^2 n)$。注意这题需要任意模数，因此常数较大。

code：

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (register int(i) = (a); (i) <= (b); ++(i))
#define pre(i, a, b) for (register int(i) = (a); (i) >= (b); --(i))
using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
int n, tmp, a[N], s[N], jc[N], inv[N];

#define fp(i, a, b) for (int i = (a), i##_ = (b) + 1; i < i##_; ++i)
#define fd(i, a, b) for (int i = (a), i##_ = (b) - 1; i > i##_; --i)
using ll = int64_t;
using db = double;
struct cp {
    db x, y;
    cp(db real = 0, db imag = 0) : x(real), y(imag){};
    cp operator+(cp b) const { return {x + b.x, y + b.y}; }
    cp operator-(cp b) const { return {x - b.x, y - b.y}; }
    cp operator*(cp b) const { return {x * b.x - y * b.y, x * b.y + y * b.x}; }
};
using vcp = vector<cp>;
using Poly = vector<int>;
namespace FFT {
    const db pi = acos(-1);
    vcp Omega(int L) {
        vcp w(L); w[1] = 1;
        for (int i = 2; i < L; i <<= 1) {
            auto w0 = w.begin() + i / 2, w1 = w.begin() + i;
            cp wn(cos(pi / i), sin(pi / i));
            for (int j = 0; j < i; j += 2)
                w1[j] = w0[j >> 1], w1[j + 1] = w1[j] * wn;
        }
        return w;
    }
    auto W = Omega(1 << 21);
    void DIF(cp *a, int n) {
        cp x, y;
        for (int k = n >> 1; k; k >>= 1)
            for (int i = 0; i < n; i += k << 1)
                for (int j = 0; j < k; ++j)
                    x = a[i + j], y = a[i + j + k],
                    a[i + j + k] = (x - y) *  W[k + j], a[i + j] = x + y;
    }
    void IDIT(cp *a, int n) {
        cp x, y;
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0; i < n; i += k << 1)
                for (int j = 0; j < k; ++j)
                    x = a[i + j], y = a[i + j + k] * W[k + j],
                    a[i + j + k] = x - y, a[i + j] = x + y;
        const db Inv = 1. / n;
        fp(i, 0, n - 1) a[i].x *= Inv, a[i].y *= Inv;
        reverse(a + 1, a + n);
    }
}
namespace MTT{
    Poly conv(const Poly &a, const Poly &b, const int&P) {
        int n = a.size(), m = b.size(), o = n + m - 1, l = 1 << (__lg(o - 1) + 1);
        vcp A(l), B(l), c0(l), c1(l);
        for (int i = 0; i < n; i++) A[i] = cp(a[i] & 0x7fff, a[i] >> 15);
        for (int i = 0; i < m; i++) B[i] = cp(b[i] & 0x7fff, b[i] >> 15);
        FFT::DIF(A.data(), l), FFT::DIF(B.data(), l);
        for (int k = 1, i = 0, j; k < l; k <<= 1)
            for (; i < k * 2; i++) {
                j = i ^ k - 1;
                c0[i] = cp(A[i].x + A[j].x, A[i].y - A[j].y) * B[i] * 0.5;
                c1[i] = cp(A[i].y + A[j].y, -A[i].x + A[j].x) * B[i] * 0.5;
            }
        FFT::IDIT(c0.data(), l), FFT::IDIT(c1.data(), l);
        Poly res(o);
        for (int i = 0; i < o; i++) {
            ll c00 = c0[i].x + 0.5, c01 = c0[i].y + 0.5, c10 = c1[i].x + 0.5, c11 = c1[i].y + 0.5;
            res[i] = (c00 + ((c01 + c10) % P << 15) + (c11 % P << 30)) % P;
        }
        return res;
    }
}
namespace Polynomial {
    void DFT(vcp &a) { FFT::DIF(a.data(), a.size()); }
    void IDFT(vcp &a) { FFT::IDIT(a.data(), a.size()); }
    int norm(int n) { return 1 << (__lg(n - 1) + 1); }
    
    vcp &dot(vcp &a, vcp &b) { fp(i, 0, a.size() - 1) a[i] = a[i] * b[i]; return a; }
    Poly operator*(Poly &a, Poly &b) {
        int n = a.size() + b.size() - 1;
        vcp c(norm(n));
        fp(i, 0, a.size() - 1) c[i].x = a[i];
        fp(i, 0, b.size() - 1) c[i].y = b[i];
        DFT(c), dot(c, c), IDFT(c), a.resize(n);
        fp(i, 0, n - 1) a[i] = int(c[i].y * .5 + .5);
        return a;
    }
}
using namespace Polynomial;

Poly F[N];

int qp(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    } return ret;
}

struct pip {
    int id, deg;
    pip(int _i, int _d) : id(_i), deg(_d) {}
    bool operator < (const pip & b) const {
        return deg > b.deg;
    }
} ; priority_queue <pip> que;

int prime[1000005], cnt;
bool vis[1000005];
void sieve(int bnd) {
    rep(i,2,bnd) {
        if (!vis[i]) prime[++cnt] = i;
        rep(j,1,cnt) {
            if (i * prime[j] > bnd) break;
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int C(int n, int m) { if (n < m) return 0; return 1ll * jc[n] * inv[m] % mod * inv[n-m] % mod; }

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n; rep(i,1,n) cin >> a[i], tmp = max(tmp, a[i]);

    sieve(sqrt(tmp) + 10); 
    rep(i,1,cnt) prime[i] = prime[i] * prime[i];
    rep(i,1,n) rep(j,1,cnt) while (a[i] % prime[j] == 0) a[i] /= prime[j];
    sort(a+1, a+1+n);
    tmp = 0; cnt = 0;
    
    jc[0] = inv[0] = 1;
    rep(i,1,n) jc[i] = 1ll * jc[i-1] * i % mod;
    inv[n] = qp(jc[n], mod - 2);
    pre(i,n-1,1) inv[i] = 1ll * inv[i+1] * (i+1) % mod;

    rep(i,1,n) if (a[i] != a[i-1]) ++ s[++cnt]; else ++ s[cnt];
    rep(k,1,cnt) {
        F[k].resize(s[k]+1);
        que.emplace(k, s[k]+1);
        rep(i,0,s[k]) F[k][i] = 1ll * C(s[k] - 1, i) * inv[s[k] - i] % mod;
    } 

    tmp = n - cnt;

    while (que.size() > 1) {
        int x1 = que.top().id; que.pop();
        int x2 = que.top().id; que.pop();
        F[x1] = MTT :: conv(F[x1], F[x2], mod);
        que.emplace(x1, F[x1].size());
        F[x2].clear(); F[x2].shrink_to_fit();
    }

    int ans = 0, ptr = que.top().id; 
    rep(i,0,tmp) 
        if (i & 1) ans = (ans + 1ll * (mod - 1) * jc[n - i] % mod * F[ptr][i]) % mod;
        else ans = (ans + 1ll * jc[n - i] % mod * F[ptr][i]) % mod;
    rep(i,1,cnt) ans = 1ll * ans * jc[s[i]] % mod;
    cout << ans << endl;
}
```

---

## 作者：pomelo_nene (赞：2)

显然的，我们需要化掉平方因子。现在如果两个数相乘会是一个完全平方数，那么这两个数一定相等。

现在就完美的转化了题目：给定一个数列，有多少种排法能够使数列中的相邻的两个数不相同？

现在就是一个非常平凡的 dp（并且可以作为一个模型！）。定义 $dp_{i,j}$ 为前 $i$ 种数，有 $j$ 对相邻的数相邻的排法数量。

首先计算下每种数出现的次数 $sz_i$，令 $\displaystyle sum_i = \sum_{j=1}^i sz_j$。考虑计算，枚举将第 $i$ 种数分成 $k$ 个相邻的部分并选 $l$ 个部分对这个 $j$ 造成贡献。有 dp 方程：

$$dp_{i,j-l+sz_i-k}=dp_{i,j} \times \binom{sz_i-1}{k-1} \times \binom{j}{l} \times \binom{sum_i+1-j}{k-l}$$

可以考虑用各种算组合贡献的方法证明这个方程式是正确的。

然后不知道为什么我的代码会诡异的 WA 掉，需要多加上一个并查集才能 A 掉？

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
struct UnionFindSet{
	int fa[305];
	void makeSet(LL upper){for(LL i=0;i<=upper;++i)	fa[i]=i;}
	LL findSet(LL x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	void unionSet(LL x,LL y)
	{
		LL xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return ;
		fa[xx]=yy;
	}
}ufs;
LL n,a[305],dp[305][305],f[305],C[305][305],fac[305],sizen[305],sum[305],aprc[305];
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)	scanf("%lld",&a[i]);
	ufs.makeSet(301);
	for(LL i=1;i<=n;++i)
	{
		for(LL j=i+1;j<=n;++j)
		{
			LL p=a[i]*a[j];
			LL s=(LL)sqrt(p);
			if(s*s==p)	ufs.unionSet(i,j);
		}
	}
	LL tot=0;
	for(LL i=1;i<=n;++i)	++aprc[ufs.findSet(i)];
	for(LL i=1;i<=n;++i)	if(aprc[i])	sizen[++tot]=aprc[i],sum[tot]=sum[tot-1]+sizen[tot];
	dp[0][0]=fac[0]=C[0][0]=1;
	for(LL i=1;i<=300;++i)	for(LL j=0;j<=i;++j)	C[i][j]=(C[i-1][j]+(j==0?0:C[i-1][j-1]))%MOD;
	for(LL i=1;i<=n;++i)	fac[i]=fac[i-1]*i%MOD;
	for(LL i=0;i<tot;++i)
	{
		for(LL j=0;j<=n;++j)
		{
			for(LL k=1;k<=sizen[i+1];++k)
			{
				for(LL l=0;l<=min(j,k);++l)
				{
					dp[i+1][j-l+sizen[i+1]-k]+=dp[i][j]*C[sizen[i+1]-1][k-1]%MOD*C[j][l]%MOD*C[sum[i]+1-j][k-l]%MOD;
					dp[i+1][j-l+sizen[i+1]-k]%=MOD;
				}
			}
		}
	}
	for(LL i=1;i<=tot;++i)	dp[tot][0]*=fac[sizen[i]],dp[tot][0]%=MOD;
	printf("%lld",dp[tot][0]);
	return 0;
}
```

---

## 作者：BINYU (赞：2)

## 题意

给定 $n$ 个数，你可以任意排列，求最终任意相邻两个数的乘积不为完全平方数的方案数。

## 思路

容易想到对于一个数，我们把它除以一个它能整除的完全平方数后，将不影响答案。所以，我们尽可能地去把一个数除以它能整除的完全平方数，最终问题变为：求最终任意相邻两个数不相等的方案数。

考虑 DP。

首先离散化，记 $m$ 表示离散化后数的种类数，$cnt_i$ 表示数 $i$ 的出现次数，$dp_{i,j}$ 表示现在填到第 $i$ 个数，还有 $j$ 组不合法的位置的方案数，显然，答案为 $dp_{m,0}$，初始状态为 $dp_{1,cnt_1 - 1} = cnt_1!$。

对于每一次填数，我们可以把之前不合法的位置中间添上当前的数，使其合法，也可能会让当前种类的数相邻，增加不合法的位置。

记当前的数的种类为 $i$，之前的不合法的位置为 $j$，已经填了的数的总数为 $Cnt$ 减少的不合法位置数为 $k1$，把当前的数划分成 $k2$ 个集合（集合内的数相邻），则当前状态为 $dp_{i,j - k1 + cnt_i - k2}$。

粗略一看，我们要计算的方案数包括集合的划分，选择位置，集合内的定序，集合间的定序和四个方面。

### 集合的划分

在数的位置确定的前提下，使用插板法，划分集合的方案数为 $C_{cnt_i-1}^{k2-1}$。

### 选择位置

我们采用捆绑法和插空法，把一个集合看成一个整体，对于不合法的位置，选择的方案数为 $C_{j}^{k1}$，对于合法的位置，选择的方案数为 $C_{Cnt + 1 - j}^{k2 - k1}$。

### 集合内的定序+集合间的定序

发现前两个操作后，在一方案中所有数的位置都是确定的，确定这两个顺序可以归结为确定数的顺序，总方案数为 $cnt_i!$。

把上面的部分串起来，可以得到：

$$dp_{i + 1,j - k1 + cnt_{i+1} - k2} \gets dp_{i,j}\times C_{cnt_{i+1}-1}^{k2-1}\times C_{j}^{k1}\times C_{Cnt + 1 - j}^{k2 - k1}\times cnt_{i+1}!$$

然后枚举 $i$、$j$、$k1$、$k2$ 就完了。

时间复杂度看似是 $O(n^4)$，实际上第三、四层的枚举最大值直到 $cnt_i$，总的枚举次数为 $n$，所以实际的复杂度为 $O(n^3)$，常数也非常小。

---

## 作者：OIerAlbedo (赞：1)


## Introduction

一道`*2500 `的数数题，有一道双倍经验[P4448](https://www.luogu.com.cn/problem/P4448)，举报 $ \text{AHOI} $ 抄袭 $ \text{CF} $。

## Solution

如果 $ a_i $ 是形如 $ \prod_{i=1}^{n}{b_i}^{p_i} $，其中 $ b_i $ 是质数，那么如果 $ p_i\ge 2 $，那么 $ p_i $ 可以减 $ 2 $，因为他不会影响最终结果，然后问题就转换成了一个经典题型，求有多少个排列满足 $ a_{pi}\not=a_{p_{i-1}} $，用 $ \text{DP} $ 解决。

我们可以利用隔板法的思想，假设 $ f[i][j] $ 表示截止到前 $ i $ 个不同的数，有 $ j $ 个不合法的空位，最终答案为 $ f[len][0] $，其中 $ len $ 为不同的数的个数。

然后我们可以发现，新加进来 $ fre $ 个相同的数，前面总共有 $ sum $ 个数，那么总共有 $ sum+1 $ 个空位，我们需要知道的有：

$ lst1 $ 表示前面不合法的空位的数量。

$ now $ 表示当前这 $ fre $ 个数会抵消多少个不合法的空位。

$ add $ 表示当前这 $ fre $ 个数会增加几个不合法的空位。

现在我们还要考虑的是如果增加了 $ add $ 个不合法的空位会对这新加进来的 $ fre $ 的数产生什么影响，我们假设会分成 $ x $ 段，那么 $ \sum_{i=1}^x len[x]-1=add $，就是 $ fre-x=add $，就是 $ x=fre-add $,就是如果我们要增加 $ add $ 个空位势必要分成 $ fre-add $ 段，而我们发现如果枚举有多少个空位不好做，我们考虑枚举分成几段。

那么有如下转移：
$$
f[i][lst1-now+fre-x]+=f[i-1][lst]\times C(fre-1,fre-x)\times C(lst1,now)\times C(sum+1-lst1,x-now)
$$
理论上会 $ \text{T} $，但实际不知道，待我写完再说。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;
long long len,MOD,lsh[1001010],fac[1001010],sum,dif,lst1,x,c[1010][1010],up,fre[100101],f[1010][1010],a[100100],n,i,j,now,ans;
int main() {
    ios::sync_with_stdio(0);cin.tie();cout.tie();
    cin>>n;MOD=1e9+7;
    for (i=1;i<=n;i++) 
         {
         	cin>>a[i];
         	for (j=2,up=sqrt(a[i]);j<=up;j++)
         	     while (a[i] % (j*j)==0) 
         	          a[i]/=(j*j);
         	lsh[i]=a[i];
		 }
	c[0][0]=1;fac[0]=1;
	for (i=1;i<=500;i++)
	    {
	    	c[i][0]=1;c[i][i]=1;
	    	for (j=1;j<i;j++)
	    	   c[i][j]=(c[i-1][j-1]+c[i-1][j]) % MOD;
	    	fac[i]=fac[i-1]*i % MOD;
		}
	sort(lsh+1,lsh+n+1);len=unique(lsh+1,lsh+n+1)-lsh-1;
	for (i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh,fre[a[i]]++;
	f[1][fre[1]-1]=1;sum=fre[1];
	for (i=1,dif=1;i<=len;i++) dif=dif*fac[fre[i]] % MOD;
	for (i=2;i<=len;sum+=fre[i],i++)
	   for (lst1=0;lst1<=sum+1;lst1++)
	        if (f[i-1][lst1]!=0)
	            for (x=1;x<=fre[i];x++)
	                for (now=0;now<=min(lst1,x);now++)
	                    { 
	                    f[i][lst1-now+fre[i]-x]+=f[i-1][lst1]*c[fre[i]-1][fre[i]-x] % MOD*c[lst1][now] % MOD*c[sum+1-lst1][x-now] % MOD;
	                    f[i][lst1-now+fre[i]-x]%=MOD;
						}
    cout<<f[len][0]*dif % MOD<<endl;
	return 0;
}

```



---

## 作者：tzc_wk (赞：1)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/840/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF840C)

这是一道 *2500 的 D1C，可个人认为难度堪比某些 *2700 *2800。

~~不过嘛，*2500 终究还是 *2500，还是被我自己想出来了~~

~~双倍经验 P4448 [AHOI2018初中组]球球的排列 哦~~

~~u1s1 其实一年以前做过 P4448，不过好像直到我 AC 这道题之后才发现这俩题一模一样，并且似乎这次用的方法和上次还不太一样~~

~~跑题了跑题了~~

首先有个性质：$\forall a,b,c\in\mathbb{N}^+$ 若 $ab,bc$ 均为完全平方数，$ac$ 也是完全平方数，因为假设 $ab=x^2,bc=y^2$，则 $ac=\dfrac{a^2b^2c^2}{ab·bc}=(\dfrac{abc}{xy})^2$，也就是说 $ac$ 是一个有理数的平方，而又显然 $ac\in\mathbb{N}^+$，故 $ac$ 为完全平方数。

考虑 $\forall i,j\in[1,n],i\ne j$，若 $a_ia_j$ 为完全平方数，就在 $i,j$ 之间连一条边，那么根据之前的推论，若 $(i,j),(j,k)$ 之间均存在边，那么 $(i,k)$ 间也存在边，也就是说得到的图是**一个个团的并集**。

考虑将同一个团中的点染上同一个颜色，于是原题等价于给出 $k$ 种颜色，第 $i$ 种颜色的球有 $c_i$ 个（每种颜色的球互不相同），其中 $\sum\limits_{i=1}^kc_i=n$，求将这 $n$ 个球排成一行，其中相邻两个球颜色不同的方案数。

考虑 $dp$，$dp_{i,j}$ 表示将前 $i$ 种颜色的球排成一行，其中有 $j$ 个相邻位置颜色相同的方案数。

考虑从 $dp_i$ 转移到 $dp_{i+1}$，我们枚举第 $i+1$ 种颜色分成了多少组，设为 $x$，再枚举这 $x$ 组中有多少组摆在了原本颜色相同的两球之间，设为 $y$，那么这样一来会少掉 $y$ 个颜色相同的相邻位置，但同时由于 $i+1$ 种颜色分为了 $x$ 组，又会多出 $c_{i+1}-x$ 对颜色相同的相邻位置。算下这样划分的方案数，设 $s_{i,j}$ 表示将 $i$ 个不同的球划分成 $j$ 组，组内有序但组与组之间无序的方案数，那么将第 $i+1$ 种颜色的球划分为 $x$ 组的方案数为 $s_{c_{i+1},x}$，从 $x$ 组中选出 $y$ 组的方案数为 $\dbinom{x}{y}$，这 $y$ 组进一步“消灭”颜色相同的位置的方案数为 $k^{\underline{y}}$，将剩余的 $x-y$ 组填入剩余的 $(\sum\limits_{t=1}^ic_t)+1$ 个空隙中的方案数为 $((\sum\limits_{t=1}^ic_t)+1)^{\underline{x-y}}$，故我们有状态转移方程式 $dp_{i,j}\times s_{c_{i+1},x}\times \dbinom{x}{y}\times k^{\underline{y}}\times ((\sum\limits_{t=1}^ic_t)+1)^{\underline{x-y}}\rightarrow dp_{i+1}{j-y+c_{i+1}-x}$。最终答案即为 $dp_{k,0}$。

最后考虑怎样求 $s_{i,j}$，考虑最后一个球的摆法，若它单独成一组，则 $dp_{i,j}\leftarrow dp_{i-1,j-1}$，若它与前面的求合并为一组，则它有 $i-1+j$ 个空隙可以插入，$dp_{i,j}\leftarrow dp_{i-1,j}\times(i+1-j)$。

算下时间复杂度，乍一看四重循环，$n^4$，但实际上 $\sum\limits_{i=1}^kc_i=n$，故复杂度是 $n^3$ 的，可以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=300;
const int MOD=1e9+7;
int n,a[MAXN+5],f[MAXN+5];
bool issqr(ll x){int _sqrt=sqrt(x);return (1ll*_sqrt*_sqrt==x);}
int find(int x){return (!f[x])?x:f[x]=find(f[x]);}
void merge(int x,int y){x=find(x);y=find(y);if(x^y) f[x]=y;}
int siz[MAXN+5],b[MAXN+5],bn=0,s[MAXN+5][MAXN+5];
int dp[MAXN+5][MAXN+5],fac[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	for(int i=1;i<=n;i++) ifac[i]=1ll*ifac[i]*ifac[i-1]%MOD;
	s[0][0]=1;
	for(int i=1;i<=n;i++) for(int j=1;j<=i;j++){
		s[i][j]=(s[i-1][j-1]+1ll*(i-1+j)*s[i-1][j])%MOD;
	}
}
int binom(int x,int y){
	if(x<0||y<0||x<y) return 0;
	return 1ll*fac[x]*ifac[x-y]%MOD*ifac[y]%MOD;
}
int main(){
	scanf("%d",&n);init_fac(n+1);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(issqr(1ll*a[i]*a[j]))
		merge(i,j);
	for(int i=1;i<=n;i++) siz[find(i)]++;
	for(int i=1;i<=n;i++) if(find(i)==i) b[++bn]=siz[i];
//	for(int i=1;i<=bn;i++) printf("%d\n",b[i]);
	dp[0][0]=1;int sum=0;
	for(int i=0;i<bn;i++){
		for(int j=0;j<=sum-i;j++){
			for(int k=1;k<=b[i+1];k++){
				int ways=s[b[i+1]][k];
				for(int l=0;l<=min(j,k);l++){
					int ways2=1ll*binom(k,l)*fac[l]%MOD*binom(j,l)%MOD;
					ways2=1ll*ways2*binom(sum+1-j,k-l)%MOD*fac[k-l]%MOD;
					ways2=1ll*ways2*ways%MOD;ways2=1ll*dp[i][j]*ways2%MOD;
//					printf("%d %d %d %d %d\n",i,j,k,l,ways2);
					dp[i+1][j-l+b[i+1]-k]=(dp[i+1][j-l+b[i+1]-k]+ways2)%MOD;
				}
			}
		}
		sum+=b[i+1];
	}
//	for(int i=1;i<=bn;i++) for(int j=0;j<=n;j++) printf("%d %d %d\n",i,j,dp[i][j]);
	printf("%d\n",dp[bn][0]);
	return 0;
}
```

事实上本题还有更优秀的做法

~~下面就是我没想到的部分了~~

我们考虑将每种颜色定义一个 $b_i$ 表示将这种颜色的球强制分为 $b_i$ 组并要求同一组的球必须绑在一起。

考虑对于固定的 $b_1,b_2,\dots,b_k$ 怎样计算这样填的方案数，首先对于每种颜色，将其分为 $b_i$ 组的方案数为 $c_i!\dbinom{c_i-1}{b_i-1}\times$，其次将这捆绑后的 $B=\sum\limits_{i=1}^kb_i$ 组排列起来的方案数为 $\dfrac{B!}{\prod\limits_{i=1}^kb_i!}$，故总方案数为 $\prod\limits_{i=1}^k(c_i!\dbinom{c_i-1}{b_i-1})·\dfrac{B!}{\prod\limits_{i=1}^kb_i!}=B!\prod\limits_{i=1}^kc_i!·\prod\limits_{i=1}^k\dbinom{c_i-1}{b_i-1}\dfrac{1}{b_i!}$，我们考虑枚举 $B$，那显然前两项都是常数，只需考虑第二个 $\prod$ 中的东西就行了。

还是考虑 $dp$，$dp_{i,j}$ 表示考虑到前 $i$ 个球，它们的 $b_i$ 加起来等于 $j$ 的 $\prod\limits_{i=1}^k\dbinom{c_i-1}{b_i-1}\dfrac{1}{b_i!}$ 的和。

转移就枚举 $b_i=l$，那么显然有 $dp_{i,j}=\sum dp_{i-1,j-l}\dbinom{c_i-1}{l-1}\dfrac{1}{l!}$。

那么最终 $\sum\limits_{i=1}^k=B$ 的答案即为 $dp_{k,B}$。

但是这样计算有个问题就是会重复计算，比方说排列方式为 `1 1 2 2`，那么它在 $dp_{2,3},dp_{2,4}$ 中都会被计算，不过这个问题很容易解决，直接容斥原理一下就行了，故最终答案为 $\sum\limits_{i=k}^ndp_{k,B}\times(-1)^{n-i}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=300;
const int MOD=1e9+7;
int n,a[MAXN+5],f[MAXN+5];
bool issqr(ll x){int _sqrt=sqrt(x);return (1ll*_sqrt*_sqrt==x);}
int find(int x){return (!f[x])?x:f[x]=find(f[x]);}
void merge(int x,int y){x=find(x);y=find(y);if(x^y) f[x]=y;}
int siz[MAXN+5],b[MAXN+5],bn=0;
int dp[MAXN+5][MAXN+5],fac[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	for(int i=1;i<=n;i++) ifac[i]=1ll*ifac[i]*ifac[i-1]%MOD;
}
int binom(int x,int y){
	if(x<0||y<0||x<y) return 0;
	return 1ll*fac[x]*ifac[x-y]%MOD*ifac[y]%MOD;
}
int main(){
	scanf("%d",&n);init_fac(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(issqr(1ll*a[i]*a[j]))
		merge(i,j);
	for(int i=1;i<=n;i++) siz[find(i)]++;
	for(int i=1;i<=n;i++) if(find(i)==i) b[++bn]=siz[i];
	dp[0][0]=1;
	for(int i=1;i<=bn;i++) for(int j=1;j<=n;j++) for(int k=1;k<=min(j,b[i]);k++){
		dp[i][j]=(dp[i][j]+1ll*dp[i-1][j-k]*binom(b[i]-1,k-1)%MOD*ifac[k]%MOD)%MOD;
	} int ans=0,mul=1;for(int i=1;i<=bn;i++) mul=1ll*mul*fac[b[i]]%MOD;
	for(int i=bn;i<=n;i++){
		if((n-i)&1) ans=(ans-1ll*dp[bn][i]*fac[i]%MOD*mul%MOD+MOD)%MOD;
		else ans=(ans+1ll*dp[bn][i]*fac[i]%MOD*mul%MOD)%MOD;
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：NaN_HQJ2007_NaN (赞：0)

[更好的阅读体验](https://www.luogu.com.cn/blog/leleleeee/ti-xie-cf840c-on-the-bench)

这是一篇简洁易懂的良心题解，提供了多种做法。

对于两个数 $x,y$，定义 $x=n^2 \cdot tx,y=m^2 \cdot ty$。如果 $x\cdot y$ 为平方数，则说明 $tx=ty$。所以我们可以将每个数除去其平方因子，比较相邻两数是否相等即可。

## F1：

定义 $f_{i,j,k}$ 为插入 $i$ 个数、有 $j$ 对相邻相等的数、有 $k$ 对相邻且与 $a_i$ 相等的数。

定义 $s_i$ 为在插入第 $i$ 个数之前有多少个数与 $a_i$ 相等。

转移分三种情况讨论：

1. $a_i$ 插入后与等于 $a_i$ 的数相邻：

$$f_{i,j,k}=f_{i-1,j-1,k-1}\times (2\cdot s_i-k+1)$$

2. $a_i$ 插入后相邻的两个数相等：

$$f_{i,j,k}=f_{i-1,j+1,k}\times (j-k+1)$$

3. $a_i$ 插入后没发生任何变化：

$$f_{i,j,k}=f_{i-1,j,k}\times(i-2\cdot s_i+2\cdot k-j)$$

实现时可以把 $a$ 数组排序，如果 $a_i \neq a_{i-1}$，则将 $f_{i-1,j,k}$ 全部加到 $f_{i-1,j,0}$ 上，并清 $0$。

可以把第一维滚掉。复杂度 $O(n^3)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300+5,mod=1e9+7;
ll n,a[N],f[2][N][N];
void fen(ll &x){
  for(ll i=2;i*i<=x;++i){
    while(x%(i*i)==0){
      x/=i*i;
    }
  }
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;for(int i=1;i<=n;++i){cin>>a[i];fen(a[i]);}
  sort(a+1,a+n+1);
  int t=0,cnt=0;f[0][0][0]=1;
  for(int i=1;i<=n;++i){
    if(a[i]!=a[i-1]){
      for(int j=0;j<i;++j){
        for(int k=1;k<=min(j,cnt);++k){
          f[t^1][j][0]=(f[t^1][j][0]+f[t^1][j][k])%mod;
          f[t^1][j][k]=0;
        }
      }
      cnt=0;
    }
    for(int j=0;j<i;++j){
      for(int k=0;k<=min(cnt,j);++k){
        ll tmp=0;
        if(j&&k)tmp=f[t^1][j-1][k-1]*(2*cnt-k+1)%mod;
        tmp=(tmp+f[t^1][j][k]*(i-2*cnt+2*k-j)%mod+f[t^1][j+1][k]*(j-k+1)%mod)%mod;
        f[t][j][k]=(f[t][j][k]+tmp)%mod;
      }
    }
    ++cnt;memset(f[t^1],0,sizeof(f[t^1]));t^=1;
  }
  cout<<f[t^1][0][0]<<endl;
  return 0;
}

```

### F2：

考虑将相同的数作为一个整体，切成多块插入。

定义 $f_{i,j}$ 为前 $i$ 组数插入后有 $j$ 对相同相邻数的方案数。

定义 $g_{i,j}$ 为 $i$ 个不同的数分成 $j$ 组的方案数。

定义 $s_i$ 为第 $i$ 组有多少数，$k$ 为将第 $i$ 组数分成几部分插入，$sum_i$ 为 $\sum\limits_{i=1}^{i}s_i$，$p$ 为插入 $k$ 部分后有几对原来相邻相同的数断开了。

$g$ 的转移方程如下：

$$g_{i,j}=(i-1+j)\cdot g_{i-1,j}+j\cdot g_{i-1,j-1}$$

第一项为将 $i$ 放到块中的方案数，第二项为将 $i$ 独立成新的一块的方案数。

$f$ 的转移方程如下：

$$f_{i,j+s_i-k-p}=\sum\limits_{k=0}^{s_i}\sum\limits_{p=0}^{\min(k,j)}\dbinom{j}{p}\cdot\dbinom{sum_{i-1}+1-j}{k-p}\cdot g_{s_i,k}\cdot f_{i-1,j}$$

复杂度 $O(n^2\sum{s_i})$，即 $O(n^3)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300+10,mod=1e9+7;
ll n,m,s[N],sum[N],a[N],f[N][N],g[N][N],c[N][N];
void fen(ll &x){
  for(ll i=2;i*i<=x;++i){
    while(x%(i*i)==0){
      x/=i*i;
    }
  }
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;for(int i=1;i<=n;++i){cin>>a[i];fen(a[i]);}
  sort(a+1,a+n+1);
  for(int i=1;i<=n;++i){
    m+=(a[i]!=a[i-1]);
    ++s[m];
  }
  for(int i=1;i<=m;++i)sum[i]=sum[i-1]+s[i];
  g[0][0]=f[0][0]=c[0][0]=1;
  for(int i=1;i<=n+5;++i){
    c[i][0]=1;
    for(int j=1;j<=i;++j){
      g[i][j]=((i-1+j)*g[i-1][j]%mod+j*g[i-1][j-1]%mod)%mod;
      c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
  }
  for(int i=1;i<=m;++i){
    for(int j=0;j<=max(sum[i-1]-1,0LL);++j){
      for(int k=0;k<=s[i];++k){
        for(int p=0;p<=min(k,j);++p){
          f[i][j+s[i]-k-p]=(f[i][j+s[i]-k-p]+c[j][p]*c[sum[i-1]+1-j][k-p]%mod*g[s[i]][k]%mod*f[i-1][j]%mod)%mod;
        }
      }
    }
  }
  cout<<f[m][0]<<endl;
  return 0;
}

```

### F3：

神仙容斥。

我们同样是考虑将相同数字分为一组，对于每一组再分块。

定义 $s_i$ 为第 $i$ 组元素个数，$b_i$ 为分成几块，$B$ 为 $\sum\limits_{i=1}^{m}b_i$。

那么第 $i$ 组分块排列的方案数为：$s_i!\cdot\dbinom{s_i-1}{b_i-1}$。即全排列后插板分块。

那么答案的计算式如下：

$$ans=\sum\limits_{B=1}^{n}[\sum\limits_{i=1}^{m}b_i=B]\left[(-1)^{n-B}\cdot\frac{B!}{\prod\limits_{i=1}^{m}(b_i!)}\cdot \prod\limits_{i=1}^{m}s_i!\cdot\dbinom{s_i-1}{b_i-1}\right]$$

因为 $n,m,s_i$ 是已知的，我们提到前面整理一下：

$$ans=\left(\prod\limits_{i=1}^{m}s_i\right)\cdot\sum\limits_{B=1}^{n}\left[(-1)^{n-B}\cdot \sum{b}[\sum\limits_{i=1}^{m}b_i=B]\left(\prod\limits_{i=1}^{m}\dbinom{s_i-1}{b_i-1}\cdot\frac{1}{b_i!}\right)\right]$$

容易发现，在 $B$ 确定的情况下，后面那些是可以预处理的。

定义 $f_{i,j}=\sum{b}[\sum\limits_{w=1}^{i}b_w=j]\left(\prod\limits_{w=1}^{i}\dbinom{s_w-1}{b_w-1}\cdot\frac{1}{b_w!}\right)$。

转移可以枚举 $b_i$ 大小，方程如下：

$$f_{i,j}=\sum\limits_{b_i=1}^{\min(j-i+1,s_i)}\left[f_{i-1,j-b_i}\cdot\dbinom{s_i-1}{b_i-1}\cdot\frac{1}{b_i!}\right]$$

所以最终答案为：

$$ans=\left(\prod\limits_{i=1}^{m}s_i\right)\cdot\left[\sum\limits_{B=m}^{n}B!\cdot (-1)^{n-B}\cdot f_{m,B}\right]$$

预处理复杂度 $O(n\sum s_i)$，即 $O(n^2)$。查询复杂度 $O(n)$。

总复杂度 $O(n^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300+5,mod=1e9+7;
ll n,m,a[N],s[N],fac[N],inv[N],f[N][N];
void fen(ll &x){for(ll i=2;i*i<=x;++i)while(x%(i*i)==0)x/=i*i;}
ll C(int x,int y){
  if(y>x||y<0)return 0;
  return fac[x]*inv[x-y]%mod*inv[y]%mod;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;for(int i=1;i<=n;++i){cin>>a[i];fen(a[i]);}
  sort(a+1,a+n+1);
  fac[0]=fac[1]=inv[0]=inv[1]=1;
  for(int i=2;i<=n;++i){
    fac[i]=fac[i-1]*i%mod;
    inv[i]=(mod-mod/i)*inv[mod%i]%mod;
  }
  for(int i=2;i<=n;++i)inv[i]=inv[i-1]*inv[i]%mod;
  for(int i=1;i<=n;++i){
    m+=(a[i]!=a[i-1]);
    ++s[m];
  }
  ll t=1,sum=0,ans=0;
  for(int i=1;i<=m;++i)t=t*fac[s[i]]%mod;
  f[0][0]=1;
  for(int i=1;i<=m;++i){
    sum+=s[i];
    for(int j=1;j<=sum;++j){
      for(int k=1;k<=min((ll)j-i+1,s[i]);++k){
        f[i][j]=(f[i][j]+f[i-1][j-k]*C(s[i]-1,k-1)%mod*inv[k]%mod)%mod;
      }
    }
  }
  for(int i=m;i<=n;++i){
    ll tmp=t*fac[i]%mod*f[m][i]%mod,op=1;
    if((n-i)&1)op=-1;
    ans=(ans+op*tmp+mod)%mod;
  }
  cout<<ans<<endl;
  return 0;
}

```


---

## 作者：ダ月 (赞：0)

### 题目分析：

结论 $1$：

对于对于大于 $1$ 的正整数 $k$ 满足 $k^2|a_i$，$k$ 在题目中没有起到关键作用。

证明：对于 $a_i=k_1^2n$，$a_j=k_2^2m$ ，$a_ia_j=k_1^2k_2^2nm$，因为 $a_ia_j$ 是否是完全平方数由 $nm$ 决定，与 $k_1^2k_2^2$ 无关。

因此，在读入 $a_i$ 的时候，筛掉它所有的 $k$。题目变成了任意两个数不相邻的个数。

结论 $2$：

考虑动态规划，我们看看我们要记录什么。第一个数是前 $i$ 个数；序列中可能会有相同相邻的数字，但也可能因为 $a_i$ 的插入，断开，所以要记录 $j$ 表示当前有 $j$ 个相同相邻的位置；我们在插入式，还要考虑 $a_i$ 左右是否产生新的相邻的位置，所以还要记 $k$ 表示当前有 $k$ 个数字相同相邻。

省流：记 $f_{i,j,k}$ 为前 $i$ 个数，序列中 $j$ 个相同相邻的数，$k$ 个当前数的相同相邻数。

这显然和 $a_i$ 在序列中出现的次数有关。

考虑转移：

- 若当前相邻有相同的数，$f_{i,j,k}$ 加上 $f_{i-1,j-1,k-1}\times(2s_i-k+1)$。

- 若当前加入这个数时断裂了一些相邻的数，那么 $f_{i,j,k}$ 加上 $f_{i-1,j+1,k}\times(j-k+1)$。

- 若无任何变化，那么 $f_{i,j,k}$ 加上 $f_{i-1,j,k}\times(i-2s_{i+1}+2k-j)$。

转移时间复杂度：$O(n^3)$。

结论 $3$：

可以滚掉第一维。

结论 $4$：

当 $a_i$ 与 $a_{i-1}$ 不相同时，第三维要发生变化，我们将第三维步压到 $0$ 里即可。即 $f_{i,j,0}=\sum f_{i,j,k}$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300+10;
#define pd(x) push_back(x)
#define rz(x,y) x.resize(y)
#define all(x) x.begin(),x.end()
#define First(x) (*x.begin())
#define End(x) (*x.end())
#define Avail(x,y) (x.find(y)==x.end())
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}ll readLL(){
		ll x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}void GStr(char *c,bool Ban_Space=true){
		c[0]=0;int p=0;
		while(c[p]!='\n'&&(c[p]!=' '||Ban_Space))c[++p]=getchar();
		c[p]='\0';
	}string Gstr(bool Ban_Space=true,int Pr_Space=1){
		string s;char c=0;
		for(int i=1;i<=Pr_Space;i++)s+=' ';
		while(c!='\n'&&(c!=' '||Ban_Space))c=getchar(),s+=c;s.pop_back();s+='\0';
		return s;
	}
	char readChar(){
		char c=' ';
		while(c==' '&&c=='\n')c=getchar();
		return c;
	}void write(int x){
		if(!x)return;
		write(x/10);
		putchar(x%10+'0');
	}void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
	void Wc(char c){putchar(c);}
	void writell(ll x){
		if(!x)return;
		write(x/10);
		putchar(x%10+'0');
	}void Outputll(ll x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else writell(x);}
	void WLll(ll x){Outputll(x);putchar('\n');}
	void WSll(ll x){Outputll(x);putchar(' ');}
	void Wstr(string s){for(int i=0;i<s.size();i++)Wc(s[i]);}
	void Wstr(char *s){int l=strlen(s);for(int i=0;i<l;i++)Wc(s[i]);}
	#define PS putchar(' ')
	#define Pn putchar('\n');
}
//==============================================================================
int n;
int a[N];
ll f[2][N][N];
int s[N];
const int mod=1e9+7;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=2;j*j<=a[i];j++)
			while(a[i]%(j*j)==0)
				a[i]/=(j*j);
	}sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		s[i]=a[i]==a[i-1]?s[i]=s[i-1]+1:0;
	f[0][0][0]=1;int p=0;
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1])
			for(int j=0;j<=i;j++)
				for(int k=1;k<=s[i-1];k++)
					f[p^1][j][0]=(f[p^1][j][0]+f[p^1][j][k])%mod,
					f[p^1][j][k]=0;
		for(int j=0;j<=i;j++)
			for(int k=0;k<=min(s[i],j);k++){
				f[p][j][k]=(f[p][j][k]+f[p^1][j][k]*(i-s[i]*2+2*k-j)%mod+f[p^1][j+1][k]*(j-k+1)%mod)%mod;
				if(j&&k)f[p][j][k]=(f[p][j][k]+1ll*f[p^1][j-1][k-1]*(2*s[i]-k+1)%mod)%mod;
			}
		memset(f[p^1],0,sizeof(f[p]));
		p^=1;
	}printf("%lld\n",f[p^1][0][0]);
	return 0;
}

```


---

## 作者：Chenaknoip (赞：0)

这道题是一道经典的组合数学问题。

题目意思是：对 $n$ 个数进行排列后，相邻两数的乘积不能是完全平方数。求方案数。

因为两个完全平方数的乘积一定是完全平方数，所以 $a_i$ 的完全平方因子对结果没有影响。所以可以在输入 $a_i$ 后，对每个 $a_i$ 除以 $a_i$ 中的所有完全平方因子，使得 $a_i$ 中不含有任何完全平方因子。

接下来，因为此时所有数不含完全平方因子，所以只有两相同的数相乘才能形成完全平方数。

于是，问题转换为：对 $n$ 个数求排列，要求任意相邻两数不等。考虑动态规划。

设 $dp_{i,j}$ 为前 $i$ 个数的排列中，有 $j$ 组相等的相邻数。显然答案为 $dp_{n,0}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

long long dp[305][502]; 
long long C[502][502]; 
long long A[502]; 
int a[305], p[305];

void init() {
	C[0][0] = 1;
	for (int i = 1; i < 480; i++) {
		C[i][0] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		C[i][i] = 1;
	}
	A[0] = A[1] = 1;
	for (int i = 2; i < 480; i++)
		A[i] = (A[i - 1] * i) % mod;
}
map<int, int> mp;
int main() {
	init();
	int cnt, n = 0;
	scanf("%d", &cnt);
	for (int i = 1; i <= cnt; i++) {
		scanf("%d", &p[i]);
		for (int j = 2; j * j <= p[i]; j++) {
			while (p[i] % (j * j) == 0) p[i] /= (j * j);
		}
		mp[p[i]]++;
	}
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
		a[++n] = (it -> second);
	}
	memset(dp, 0, sizeof(dp));
	dp[1][a[1] - 1] = 1;
	long long sum = a[1];
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < sum; j++) 
			for (int k = 1; k <= a[i]; k++) 
				for (int u = 0; u <= j && u <= k; u++)
					dp[i][j - u + a[i] - 1 - (k - 1)] = (dp[i][j - u + a[i] - k] + (((dp[i - 1][j] * C[j][u]) % mod * C[sum + 1 - j][k - u]) % mod * C[a[i] - 1][k - 1]) % mod) % mod;
		sum += a[i];
	}
	long long ans = dp[n][0];
	for (int i = 1; i <= n; i++)
		ans = (ans * A[a[i]]) % mod;
	cout << ans << endl;
	return 0;
}
```


---

