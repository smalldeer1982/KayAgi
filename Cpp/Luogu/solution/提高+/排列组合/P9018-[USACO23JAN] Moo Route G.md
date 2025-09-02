# [USACO23JAN] Moo Route G

## 题目描述

现在有一条数轴，$t$ 表示当前时刻。在 $t=0$ 时 Bessie 恰好处在 $x=0$ 的位置。

接下来，每秒钟 Bessie 会向左或者向右移动一个单位距离，我们保证 Bessie 是在 $0-N$ 的位置之间移动并最终停在 $x=0$ 的位置。同时，我们有一个 $A_0,A_1,A_2\ldots A_{N-1}$ 的数列，分别表示 Bessie 经过 $0.5,1.5,2.5\ldots (N-1).5$ 这些点的次数。我们可以用一个由 $\text{L}$ 和 $\text{R}$ 组成的序列来表示 Bessie 的路径，我们称 Bessie 改变了一次方向为在序列中的相邻两个字符不同。现在我们不知道具体的移动序列是什么，但我们知道 Bessie 采用了让她改变方向次数最少的走法。现在请问 Bessie 的路径有多少种不同的可能情况？（我们称两条路径不同当且仅当这条路径对应序列中的某一位不同）

## 说明/提示

$N\le10^5,\max(A_i)\le10^6$。

对于测试点 $2-4$，满足 $N\le2,\max(A_i)\le10^3$。

对于测试点 $5-7$，满足 $N\le2$。

对于测试点 $8-11$，满足 $\max(A_i)\le10^3$。

## 样例 #1

### 输入

```
2
4 6```

### 输出

```
2```

# 题解

## 作者：Bugupop (赞：13)

## 【大体思路】

数形结合+组合数。

## 【详解】

### Part 1. 发散思路

受 [P1641](https://www.luogu.com.cn/problem/P1641) 的启发，这道题在一开始模拟样例的时候就尝试用数形结合的方法来体现过程。将原本在数轴上的路径抻开，变成折线放到平面直角坐标系中，就会直观多了。以及，$A_i$ 表示的实际上就是经过 $[i - 1 , i]$ 这一段的次数，对应到图上就是从下往上数第 $i$ 层线段的数量，以下都会用这种方式来描述。

![例图1](https://cdn.luogu.com.cn/upload/image_hosting/xdta6b6u.png)

比如这张图，一行一行横向来看，从下往上数第一层之间的红色线段的数量 $4$ 就代表经过点 $0.5$ 的次数；第二层之间的红色线段数量 $6$ 代表经过点 $1.5$ 的次数。

因为最终又回到了 $x = 0$ 的位置，路径一定是有来有回，所以我们不妨将一来一回两段线段合成一个向上的尖，对于尖进行顺序排列，这样就一定不会出现走不回 $0$ 的情况了。将 $A_i \div 2$，就变成了尖的个数。

题目对于路径有一个限制，那就是要求转头次数最少，对应到图上就是折角要尽可能少，照着样例再画一画就能发现，存在比上图转头 $7$ 次更少的路径，比如：

![例图2](https://cdn.luogu.com.cn/upload/image_hosting/wbwvn9ku.png)

这种方案共转头了 $5$ 次，是样例形成的一种转头次数最少的方案。经过摸索，能发现：如果把两层之间的关系看做是在下面的尖中插入上面的尖的话，转头次数少的图都有一个特点，那就是下面的尖里都尽量不空。

第一张图下面那一层的两个尖中，左边那个尖中间是空的，右边那个尖里一共插入了 $3$ 个上层的尖。

第二张图下面那一层的两个尖中，左边那个尖中间插入了 $1$ 个尖，右边那个尖中间插入了 $2$ 个尖。

这是上层尖比下层尖多的情况，如果下面的尖比较多，那么一定有下面的尖是空的，这时候就要在底下一层选出跟上面一层尖的数量相同的尖，一一对应地放，这样就尽可能使转头次数少了。

说到这，感觉很容易就能把这个问题跟另一个问题联系起来了：这不就是在 $n$ 个篮子里放 $m$ 个苹果的求组合数问题吗！

不过先别急，这只是 $N = 2$ 的情况，我们还要把它拓展到 $N > 2$ 的通解。

接着苹果篮子的问题来说，我们可以把 $N = 2$ 的情况看成是把苹果放到篮子里，如果 $N = 3$，实际上是在上面的问题外面又套了一层这个问题，可以把它类比成把盛了苹果的 $m$ 个篮子放进 $p$ 个箱子里，实际上还是一个苹果篮子问题。不管苹果是以怎样的方式放进了篮子，最终都是有 $m$ 个篮子要放进箱子，跟苹果放置的方案没有关系，可以分步计算，也就是一个乘法原理。

回到原题，对于任意一层的尖，放置的时候只跟它下面的那层有关系，其它层对它产生不了影响。这样也就把 $N = 2$ 的情况普及到了$N > 2$ 的所有情况，那就是计算每相邻两层放置的方案后再相乘就可以了。

OK，思路就到这，接着是一些方案数计算方法，已经明白的可以跳过了！

### Part 2. 计算方法

设上层有 $x$ 个尖，下层有 $y$ 个尖，一共有下面四种情况：

1. $x = 1$：在下层 $y$ 个尖中挑出 $1$ 个放尖，方案数为 $C_y^1$。

2. $y = 1$：将上层所有尖都放到下层唯一这一个尖中，方案数为 $1$。

3.  $x \ge y$：要使下面 $y$ 个尖中间都不空，就是将上层 $x$ 个尖分成 $y$ 个非空段，方法是插板法，把 $x$ 个元素中间插上 $y-1$ 个板，方案数为 $C_{x-1}^{y-1}$。

4.  $x<y$：在下层 $y$ 个尖中挑出 $x$ 个放尖，方案数为 $C_y^x$。

按照上面的情况进行判断，然后将结果累乘起来就可以了。

## 【代码】

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int p = 1e9 + 7;
int n;
ll ans, jc[N], a[N];
ll ksm(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) {
			ret = (ret % p * a % p) % p;
		}
		a = (a * a) % p;
		b >>= 1;
	}
	return ret % p;
}
ll C(int a, int b) {
	return jc[a] * ksm((jc[a - b] % p * jc[b] % p) % p, p - 2) % p;
}
int main() {
	scanf("%d", &n);
	ans = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		a[i] /= 2;
	}
	jc[1] = 1;
	for (int i = 2; i <= 1000000; i++) {
		jc[i] = (jc[i - 1] % p * i % p) % p;
	}
	for (int i = 1; i < n; i++) {
		if (a[i + 1] == a[i] || a[i] == 1) {
			continue;
		}
		if (a[i + 1] == 1) {
			ans = (ans % p * a[i] % p) % p;
			continue;
		}
		if (a[i + 1] >= a[i]) {
			ans = (ans % p * C(a[i + 1] - 1, a[i] - 1) % p) % p;
		} else {
			ans = (ans % p * C(a[i], a[i + 1]) % p) % p;
		}
	}
	printf("%lld", ans % p);
	return 0;
}
```


---

## 作者：MCRS_lizi (赞：11)

代码简单的思维题，USACO 常见风格了。

[题目意思](https://www.luogu.com.cn/paste/raz6msxe)

## 题目分析
我们会发现这题直接入手很难找到突破口，所以我们考虑换个角度从 $N=2$ 的特殊情况先入手。不难发现，$\forall i,A_i\bmod 2=0$，因为每个位置出去肯定要回来，所以，我们把每个 $A_i$ 都变成原来的一半，再进行接下来的考虑。

很显然 $N=2$ 时无非就两种情况：$A_1>A_2$ 和 $A_1\le A_2$，我们不妨进行一下分类讨论。

当 $A_1>A_2$ 时，要想让转弯次数更少，通过贪心可以得知是 $0\rightarrow 2 \rightarrow 0$ 这条路线走 $A_2$ 次且 $0\rightarrow 1 \rightarrow 0$ 走 $A_1-A_2$ 次。其他任何的路径都会带来额外的转弯次数，会严格劣于最优解。这样我们就只用考虑这几次的顺序即可，也就是在总共 $A_1$ 次路径中选择 $A_2$ 次，结果为 $C_{A_1}^{A_2}$。

接下来当 $A_1\le A_2$ 时会相对复杂一些，需要在 $1,2$ 两个点之间来回走把多余的次数抵消。由于每次出去必定会对 $A_1,A_2$ 都产生贡献，所以每对 $A_1$ 产生一次贡献之后都会对 $A_2$ 产生若干次（至少一次）贡献。所以我们可以考虑插隔板，把一共 $A_2$ 个物品分成 $A_1$ 份，也就是 $C_{A_2-1}^{A_1-1}$。

考虑完特殊情况，接下来要拓展到一般情况。我们知道 $A_i$ 可以代表一共有 $A_i$ 次是在向右走的情况下走到了 $i$ 点。这个时候到了 $i$ 点，如果向左走了回去则对接下来不产生影响，否则就和上面 $N=2$ 的情况一样。所以我们可以局部性的讨论每个点的情况，这样我们只用在意它左右两边的点的情况，因为这具有相对的独立性。

综上所述，最终的答案为 $\prod_{i=1}^{N-1} \begin{cases}
C_{A_i}^{A_{i+1}}(A_i>A_{i+1})\\C_{A_{i+1}-1}^{A_i-1}(A_i\le A_{i+1})
\end{cases}$。

由于取模数为质数，可以轻松地使用逆元解决这个问题。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7,N=1000000;
int n,a[1000010],inv[1000010],rev[1000010],ans=1;
inline int power(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
		{
			res=res*x%mod;
		}
		y>>=1;
		x=x*x%mod;
	}
	return res;
}
inline int c(int x,int y)
{
	return inv[y]*rev[x]%mod*rev[y-x]%mod;
}
inline void init()
{
	inv[0]=1;
	for(int i=1;i<=N;i++)
	{
		inv[i]=inv[i-1]*i%mod;
	}
	rev[N]=power(inv[N],mod-2);
	for(int i=N-1;i>=0;i--)
	{
		rev[i]=rev[i+1]*(i+1)%mod;
	}
}
signed main()
{
	init();
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i]/=2;
		if(i>=2)
		{
			if(a[i-1]>a[i])
			{
				ans=ans*c(a[i],a[i-1])%mod;
			}
			else
			{
				ans=ans*c(a[i-1]-1,a[i]-1)%mod;
			}
		}
	}
	cout<<ans;
 	return 0;
}
```


---

## 作者：luoguhandongheng (赞：5)

（2024NOV7th，Exhausting Thursday）

有意思（~~我做不出来的~~）的组合题。

可以先做银组的减弱版 [P9015](https://www.luogu.com.cn/problem/P9015)。

### 心路历程

（个人记录，可以跳过）一开始想将 $A$ 序列拆分为多个递增序列。每个递增序列的方案数是好计算的，但在拼接的时候出了一些问题。情况复杂特别多，分讨到一半又发现复杂度好像假了，然后就做不下去了。

### 正解

实际上完全可以把条件进一步加强，不考虑递增序列，直接考虑 $N=2$ 时的情况。

1. $A_0>A_1$ 时，一种最优路径如下图。

​![](https://cdn.luogu.com.cn/upload/image_hosting/2q8v1yv2.png)可以发现，$0\to 2$ 的红色路径形成了 $A_1 \over 2$ 个红色条状物，$0\to1$ 的蓝色路径形成了 ${A_0 - A_1} \over 2$ 个蓝色条状物。（读者可以对照上图数一数）他们之间可以随意互换位置。总共有 $A_0 \over 2$ 个条状物，选其中 $A_1 \over 2$ 个放红色。故共有 $C_{A_0 \over 2}^{A_1 \over 2}$ 种方案。

2. $A_0 \le A_1$ 时，一种最优路径如下图。

​![](https://cdn.luogu.com.cn/upload/image_hosting/66hllktz.png)​

黑色的为路径。这次可以随意移动的方块为这些红色条状物与蓝色条状物。$0 \to 2$ 的红色条状物有 $\frac{A_0}2-1$ 个，$1 \to 2$ 的蓝色条状物有 $\frac{A_1-A_0}{2}$ 个。共有 $\frac{A_1}{2}-1$ 个位置，选其中 ${A_0 \over 2}-1$ 放红色条状物。共有 $C_{\frac{A_1}{2}-1}^{{A_0 \over 2}-1}$ 种方案。

接下来考虑 $N \ge 3$ 时。我们发现对于前三个数，一条 $0 \to 2$ 的路径直接拼上一条 $1 \to 3$ 的路径就形成了一条 $0 \to 3$ 的路径。下图直观地说明了这一事实。

​![](https://cdn.luogu.com.cn/upload/image_hosting/oykths2u.png)​

​![](https://cdn.luogu.com.cn/upload/image_hosting/wk24gdcc.png)​

那么 $0 \to 3$ 的路径数量显然就等于 $0 \to 2 $ 的数量乘上 $1 \to 3$ 的数量。而 $i \to i+2$ 这样相邻两个路径数量的计算方法与 $N \le 2$ 时没有区别，将 $A_i$ 看成 $A_0$，$A_{i+1}$ 看成 $A_1$ 即可。

注意这里不可以两个两个拼，即不能将 $0 \to 4 $ 拆成 $0 \to 2$ 和 $2 \to 4$ 两段数量相乘。这是因为当 $A_1 \ne A_2$ 时，两条路径经过 $2$ 的次数都不同，肯定无法拼在一块。

这样一直拼下去即可。最终答案为

$$
\prod_{i=1}^{n-1} \begin{cases}C_{A_{i-1} \over 2}^{A_{i} \over 2}  & A_{i-1} > A_i\\ C_{\frac{A_i}{2}-1}^{{A_{i-1} \over 2}-1} & A_{i-1} \le A_i\end{cases}
$$

组合数的计算预处理阶乘并用费马小定理算逆元即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5,mod=1e9+7,D=1e6+5;
int qp(int a,int b){
    ll res=1;
    for(;b;b>>=1,a=(1ll*a*a)%mod){
        if(b&1)
            res=(res*a)%mod;
    }
    return res;
}
int a[N],inv[D],fac[D],n;
void init(){
    inv[1]=inv[0]=1,fac[1]=1;
    for(int i=2;i<D;++i){
        fac[i]=(1ll*fac[i-1]*i)%mod;
        inv[i]=qp(fac[i],mod-2);
    }
}
int C(int n,int m){
    if(m==0) return 1;
    return (1ll*(1ll*fac[n]*inv[m])%mod*inv[n-m])%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    init();
    int ans=1;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(i>=2){
            int b0=a[i-1]>>1,b1=a[i]>>1;
            ans=(1ll*ans*(b0>=b1 ? C(b0,b1):C(b1-1,b0-1)))%mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：hjyowl (赞：4)

### 思路

容易发现 $a_i$ 一定是偶数，所以说我们用对 $a_i$ 除以 $2$ 来获得他非返回的时经过的。

优先观察 $n=2$ 的部分分。

如果 $a_1 > a_2$，那么显然会在两个之间先跑很多次，再在 $1$ 那反复跑。

反过来，$a_1 \le a_2$，那么会跑很多次到 $2$ 那里继续跑。

两个情况可以参考下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/310sfja7.png)

所以说，对于 $n=2$，如果 $a_1 > a_2$，答案就是在 $a_1$ 中选 $a_2$ 个，所以答案是 $C_{a_1}^{a_2}$。

对于 $a_1 \le a_2$，答案就把 $a_2$ 分成 $a_1$ 段，答案为 $C_{a_2-1}^{a_1-1}$。

接下来我们把他拓展到所有情况，可以发现 $a_i$ 和 $a_{i+1}$ 之间的贡献是可以当作 $n=2$，$a_1=a_i$，$a_2=a_{i+1}$ 的样子来算。

最后用乘法原理把每一对 $a_i$ 和 $a_{i+1}$ 的贡献相乘就可以了。

由于 $p$ 是素数，可以直接用逆元求解组合数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010, mod = 1e9 + 7;
long long fact[N];
long long infact[N];
long long a[N];
long long qmi(long long a, long long k)
{
    long long res = 1;
    while (k)
    {
        if (k & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        k >>= 1;
    }
    return res;
}
long long C(long long a, long long b)
{
    if (a < b || b < 0)
    {
        return 0;
    }
    return (fact[a] * infact[b] % mod) * infact[a - b] % mod;
}
long long inv(long long x)
{
    return qmi(x, mod - 2);
}
long long solve(long long a, long long b)
{
    if (a > b)
    {
        return C(a, b);
    }
    else
    {
        return C(b - 1, a - 1);
    }
}
int main()
{
    long long n;
    cin >> n;
    for (long long i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i] /= 2;
    }
    fact[0] = infact[0] = 1;
    for (long long i = 1; i < N; i++)
    {
        fact[i] = fact[i - 1] * i % mod;
        infact[i] = inv(fact[i]);
    }
    long long res = 1;
    for (long long i = 1; i < n; i++)
    {
        res = (res * solve(a[i], a[i + 1])) % mod;
    }
    cout << res;
    return 0;
}
```

---

## 作者：Creeper_l (赞：2)

首先有一些性质。因为保证有解，所以 $a_i$ 一定都是 $2$ 的倍数（必须一来一回）。并且总的步数应该为 $\sum a_i$。

先考虑 $n \le 2$ 的情况，这时我们可以分情况讨论。因为每一条线段都会被来回走两次，所以我们可以先把每一个数都除以 $2$。

1. 若 $a =b$，则最优情况一定是形如 $RRLLRRLL\dots$ 的，否则转向次数一定更多。

2. 若 $a<b$，我们假设先按上述情况的方式走完，那么右边线段应该还需要再被走 $b-a$ 次。考虑这 $b-a$ 次在什么时候走最优，会发现如果选择走到中间点的时候再走一次 $RL$ 是最优的。所以我们每一次走到中间点都可以选择走一次 $RL$。最先总共有 $a$ 个中间点，每走一次 $RL$ 还会多产生一个中间点，所以总方案数是 $\frac{\prod_{i=a}^{b-1}i}{(b-a)!}$。

3. 若 $a > b$，那么左边线段应该还需要再被走 $a-b$ 次。则会发现如果走到最左边的时候再多走一次 $RL$ 是最优的。最先总共有 $(b+1)$ 个左边点，每一次走 $RL$ 还会多产生一个，所以总方案数是 $\frac{\prod_{i=(b+1)}^{a}i}{(a-b)!}$。

现在考虑把 $n$ 扩展到 $10^5$。这时我们会发现，如果我们从左往右考虑的话，那么 $a_{i+1}$ 的选择只和 $a_i$ 有关系，和 $a_{i-1}$ 没有关系。所以我们可以从左往右依次将序列拆分为 $[a_1,a_2],[a_2,a_3]$ 这样长度为 $2$ 的段，对于每一段都可以按照 $n=2$ 的情况单独算，最终答案即为它们相乘。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7; 
const int MAXN = 2e6 + 10;
int n,a,b,fac[MAXN],inv[MAXN],invfac[MAXN],p[MAXN],ans = 1;
inline int P(int l,int r){return (fac[r] * invfac[l - 1]) % mod;}
signed main()
{
	inv[0] = fac[0] = invfac[0] = 1;
	inv[1] = fac[1] = invfac[1] = 1;
	for(int i = 2;i <= 2000000;i++)
	{
		inv[i] = (inv[mod % i] * (mod - mod / i)) % mod;
		fac[i] = (fac[i - 1] * i) % mod;
		invfac[i] = (invfac[i - 1] * inv[i]) % mod;
	} 
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++) scanf("%lld",&p[i]);
	for(int i = 2;i <= n;i++)
	{
		a = p[i - 1],b = p[i];
		int tmp;
		if(a % 2 == 1 || b % 2 == 1) tmp = 0;
		else if(a == b) tmp = 1;
		else if(b > a) tmp = (P(a / 2,a / 2 + (b - a) / 2 - 1) * invfac[(b - a) / 2]) % mod;
		else if(a > b) tmp = (P(b / 2 + 1,b / 2 + (a - b) / 2) * invfac[(a - b) / 2]) % mod;
		ans = (ans * tmp) % mod;
	} 
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：slzx2022YuYihan (赞：2)

# Solution

这是一道非常有意思的数学题，推了我将近一个小时，最后因为阶乘和逆元数组开小了惨炸三十五分。

我们可以画一个图（这里上传一个当时我的大巴草稿），请读者感性理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/4yj4ca9i.png)

我们发现，$a$ 数组中的数肯定都是偶数。不妨令 $b_i=a_i\div 2$。要使拐弯次数最少，我们就把上一段的箭头平移过来。如果 $b_i>b_{i-1}$，可以在其中插入 $b_i-b_{i-1}$ 组来回箭头，问题就转化成了：把 $b_i-b_{i-1}$ 个相同的小球放入 $b_{i-1}$ 个不同的盒子，其中盒子可以为空。利用隔板法，方案数为 $C_{b_i-b_{i-1}+b_{i-1}-1}^{b_{i-1}-1}=C_{b_i-1}^{b_{i-1}-1}$。否则，方案数为 $C_{b_{i-1}}^{b_i}$。统计时全部相乘即可，注意单独拎出 1 的情况。组合数用老套路求，时间复杂度 $O(\max{b_i} \log MOD)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T& x){
    x = 0; T w = 1; char ch = getchar();
    while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x *= w;
}
template<typename T>inline void write(T x){
    if (x < 0)	putchar('-'), x = ~(x - 1);
    if (x > 9)	write(x / 10);
    putchar(x % 10 ^ 48);
}

const int N = 1e5 + 5;

const int M = 5e5 + 5;

const ll mo = 1e9 + 7;

inline ll qpow(ll a, ll b){
    ll res = 1;
    while (b){
        if (b & 1)  res = res * a % mo;
        a = a * a % mo, b >>= 1;
    }
    return res;
}
ll jc[M], inv[M];
inline ll C(ll a, ll b){
    return jc[a] * inv[a - b] % mo * inv[b] % mo;
}

ll n, a[N], ma;

ll ans;

int main(){
    //ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i]), ma = max(ma, a[i]);
    jc[0] = inv[0] = 1;
    for (int i = 1; i <= (ma >> 1); ++i)
        jc[i] = jc[i - 1] * i % mo, inv[i] = qpow(jc[i], mo - 2);
    ans = 1;
    for (int i = 2; i <= n; ++i)
        if (a[i] > a[i - 1])
            ans = ans * C((a[i] >> 1) - 1, (a[i - 1] >> 1) - 1) % mo;
        else
            ans = ans * C((a[i - 1] >> 1), (a[i] >> 1)) % mo;
    write(ans), putchar('\n');

    return 0;
}
```

---

## 作者：EZ_XHX (赞：2)

首先我们假设已经得到一组合法方案，把它两两拆开，一定不可能比两两的局部最优劣。

如果说要劣，我们找到劣的那一组，劣就一定意味着出现了中间不必要的迂回。

也就是说假如我现在找到劣的那一组为 $[x-1,x+1]$ 我在 $x$ 这里把迂回删掉，改成没有迂回的。

这样做对于其他的来说并没有影响，因为两侧的接口还是一样的，但是中间少了一个迂回，自然也不可能的最优的。

为什么没有影响，因为任意两个方案一定可以拼凑在一起形成一一映射。我改动也可以进行拼凑。

因为还有更优的方案就是把迂回删掉。

很显然，我们同时也无法再比局部最优更优了。

如果更优，局部最优为什么不能换成这个呢？

主要还是要自己画图去理解。

然后因为每个不同，我们可以很方便地去用乘法原理进行统计。

---

## 作者：cqbzlym (赞：1)

[更好的阅读体验！](https://xsc062.netlify.app/20250219/#usaco23jan-moo-route-g)

希望大家不要和我一样忽略了重要条件：终点也是 $0$。这意味着每个点都会被左右成对地经过，那么不妨令 $A_i\gets \frac 2{A_i}$。

观察到给了 $N=2$ 的一档分，考虑该情况。

1. 若 $A_1> A_2$：

   此时最优策略为：

   ```plain{data-line="1,2,5,6,9,10"}
   |--------->
   <---------|
   |--------->
   <---------|
   |--------->
   <---------|
   |---->
   <----|
   |---->
   <----|
   ===========
   0    1    2
   ```

   只要不拆开一组，箭头排列顺序任意。显然方案数为 ${A_1}\choose {A_2}$。
1. Otherwise：

    此时最优策略为：

   ```plain{data-line="4,5,7,8"}
   |---------->
         <----|
         |---->
         <----|
         |---->
    <---------|
    |--------->
    <---------|
    ===========
    0    1    2
   ```

   相似地，只要不拆开一组，箭头排列顺序任意，可以注意到除了第一个，每个长 `|--->` 的前面一定是一个长 `<---|`，那么问题转化为选择 $A_1-1$ 个短 `<---|` 拉长，方案数为 ${A_2-1}\choose{A_1-1}$。

进一步，考虑 $N=3$ 的情况。若已知子问题 $0\to1\to2$ 的方案和子问题 $1\to2\to3$ 的方案，可以直接乘起来合并。为什么呢？

二者经过 $2$ 的次数相等；在子问题 $0\to1\to2$ 中，$1\to2$ 的下一步一定是 $2\to 1$；我们把该过程替换为子问题 $1\to 2\to 3$ 中对应的一段 $1\to2\to\cdots\to2\to1$ 的路径即可。

那么两两合并起来，可以得到最终答案为 $\prod\limits_{i=1}^{n-1}\begin{cases}{\binom{A_i}{A_{i+1}}}&A_i>A_{i+1}\\{\binom{A_{i+1}-1}{A_i-1}}&\text{otherwise}\end{cases}$。
```cpp
#include <bits/stdc++.h>
const int lim = 5e5;
const int mod = 1e9 + 7;
int main() {
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
#else
    std::freopen(".in", "r", stdin);
    std::freopen(".out", "w", stdout);
#endif
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i], a[i] /= 2;
    std::vector<long long> inv(lim + 1), fac(lim + 1);
    auto qkp = [&](long long x, int y) {
        long long res = 1ll;
        for (; y; (x *= x) %= mod, y >>= 1)
            if (y & 1)
                (res *= x) %= mod;
        return res;
    };
    inv[0] = fac[0] = 1ll;
    for (int i = 1; i <= lim; ++i)
        fac[i] = fac[i - 1] * i % mod;
    inv[lim] = qkp(fac[lim], mod - 2);
    for (int i = lim - 1; i; --i)
        inv[i] = inv[i + 1] * (i + 1) % mod;
    auto C = [&](int n, int m) {
        return fac[n] * inv[n - m] % mod * inv[m] % mod;
    };
    long long res = 1ll;
    for (int i = 1; i < n; ++i)
        if (a[i] > a[i + 1])
            (res *= C(a[i], a[i + 1])) %= mod;
        else
            (res *= C(a[i + 1] - 1, a[i] - 1)) %= mod;
    std::cout << res << '\n';
    return 0;
}
```

---

## 作者：小木虫 (赞：0)

### Preface  
非常玄妙的组合数学思维题，需要善用部分分思维，本蒟蒻赛时读错题做到最后。  
### Problem  
给你一个从 0 到 $n$ 的数轴，一头奶牛会在上面走路，每次可以向左或向右移动一格，对于每个 $i$ 给定从 $i$ 到 $i+1$ 与从 $i+1$ 到 $i$ 的次数和 $a_i$，开始奶牛在点 0，最后需要回到点 0，问你转向次数最小的方案数一共有多少。

$n\leq 10^5$，$\sum a_i\leq10^6$。  

### Solution  
首先发现从 0 出发，回到 0，根据这个条件，我们可知任何一次从 $i$ 到 $i+1$，肯定会有一次对应的从 $i+1$ 到 $i$。这意味着对于任何 $i$，$a_i\bmod 2=0$。  

然后让我们先研究一下部分分，即 $n\leq 2$ 的情况。  
发现题目要求转向次数最少，这个条件十分可疑，于是我们先对于 $n\leq 2$ 的情况先手玩一下，做个分讨。   
由于接下来的操作并非单向移动而是往返，我们先将 $a$ 全部除以 2，然后做接下来的操作。

对于 $a_1\geq a_2$：  
我们肯定要做 $a_1$ 次的 $(0,1)$ 往返，在这个过程中需要带上 $a_2$ 次 $(1,2)$ 往返。  
然后我们发现我们可以做 $a_2$ 次 $(0,2)$ 往返，$a_1-a_2$ 次 $(0,1)$ 往返。  
容易发现，这个操作使得 $a_1-a_2$ 次的从向左变成向右的转向被合并了，达到了下限，其它都不优。  
那么这样的操作的总个数即为 $ \binom{a_1}{a_2}$。  

对于 $a_1\leq a_2$：  
同理，我们需要做 $a_1$ 次的 $(0,2)$ 往返，在其中做 $a_2-a_1$ 次的 $(1,2)$ 往返，同理也是最优的。  
应用插板法，操作总个数为 $\binom{a_2-1}{a_1-1}$。  

然后让我们扩展到 $n\leq 10^5$。  
我们将这 $n$ 个数的情况拆成 $n-1$ 个 2 个数的情况，可以发现他们是可以首尾相接的。  
  
对于子任务 $(a_i,a_{i+1})$，我们会经过 $a_{i+1}$ 对应边 $a_{i+1}$ 次，然后这样就跟下一个子任务 $(a_{i+1},a_{i+2})$ 相接上了，这样可以保证总体转向次数最小，换句话说就是第几次经过目前子任务的最后边后就相当于第几次通过下一子任务的第一条边，这样就把每一次到右端点之后向左转的转向与下一个子任务合并了，并且也把下一个子任务到达左端点后向左转的转向和这个子任务合并了。

那么这样的话答案就是所有子任务答案的乘积。

然后代码就很简单了：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int M=1e6;
const int mod=1e9+7;
int n,a[N],f[N],inv[N];int x,y;
void exgcd(int a,int b){
  	if(!b){x=1,y=0;return;}
  	exgcd(b,a%b);int t=x;
  	x=y,y=t-a/b*y;
}
int C(int x,int y){
	if(x==y||y==0)return 1;
	return (f[x]*inv[y]%mod*inv[x-y]%mod)%mod;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
	f[0]=1;
	for(int i=1;i<=M;i++){
		f[i]=f[i-1]*i;f[i]%=mod;
		exgcd(f[i],mod);
		inv[i]=(x%mod+mod)%mod;
	}
	cin>>n;int res=1;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]/=2;
	for(int i=2;i<=n;i++){
		if(a[i-1]>=a[i]){
			res*=C(a[i-1],a[i]);res%=mod;
		}else{
			res*=C(a[i]-1,a[i-1]-1);res%=mod;
		}
	}cout<<res;
	return 0;
}
```


---

