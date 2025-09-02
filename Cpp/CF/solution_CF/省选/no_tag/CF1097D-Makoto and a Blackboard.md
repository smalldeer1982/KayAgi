# Makoto and a Blackboard

## 题目描述

Makoto 有一块大黑板，上面写着一个正整数 $n$。他将恰好进行 $k$ 次如下操作：

假设当前黑板上的数字为 $v$。他会随机选择 $v$ 的一个约数（可能是 $1$ 或 $v$ 本身），并用这个约数替换 $v$。由于 Makoto 使用他著名的随机数生成器（RNG），且总是以 $58$ 作为种子，因此每个约数被选中的概率是相等的。

现在他想知道，经过 $k$ 步操作后，黑板上数字的期望值是多少。

可以证明，这个值可以表示为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是互质的整数，且 $Q \not\equiv 0 \pmod{10^9+7}$。请输出 $P \cdot Q^{-1} \bmod 10^9+7$ 的值。

## 说明/提示

在第一个样例中，经过一步操作后，黑板上的数字可能为 $1$、$2$、$3$ 或 $6$，每种情况出现的概率相等。因此答案为 $\frac{1+2+3+6}{4}=3$。

在第二个样例中，答案等于 $1 \cdot \frac{9}{16}+2 \cdot \frac{3}{16}+3 \cdot \frac{3}{16}+6 \cdot \frac{1}{16}=\frac{15}{8}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 2
```

### 输出

```
875000008
```

## 样例 #3

### 输入

```
60 5
```

### 输出

```
237178099
```

# 题解

## 作者：NaCly_Fish (赞：17)

[题目链接](https://www.luogu.com.cn/problem/CF1097D)

本题解已全面更新。

****
首先有一个重要观察：答案关于 $n$ 是积性的。原因很简单，设 $a_k(n)$ 为答案，就有一个显然的递归关系
$$a_k(n)=\frac{1}{\sigma_0(n)}\sum_{d|n}a_{k-1}(d)$$
其中 $\sigma_0(n)$ 表示 $n$ 的约数个数。根据积性函数的基本性质，两个积性函数的 Dirichlet 卷积（这里就是 Dirichlet 前缀和）仍然是积性的；两个积性函数对应点值相乘，也是积性的。

所以只要 $a_{k-1}(n)$ 是积性的，$a_k(n)$ 就是积性的。显然 $a_0(n)=n$ 是积性函数，故答案是积性的。

利用这个性质，就只要对 $n$ 做质因数分解，对每个质数幂求出答案然后相乘即可。也就是说，我们只用考虑算 $a_k(p^m)$，其中 $p$ 为质数。

此时直接用原本的递归关系来计算，复杂度就大大降低了，足以通过本题。
****
但是这样的 DP 还是太朴素，不符合我鱼鱼之风格，一定要想办法优化一下。  
下文中，我们都考虑**只对一个固定的** $p$ 来求答案。所以为了方便设 $f_{i,j}=a_i(p^j)$，在 $f$ 中不写出 $p$。

在质数幂上，原本的递归关系就变为（有边界值 $f_{0,j}=p^j$）：
$$f_{i,j}=\frac{1}{j+1}\sum_{k=0}^jf_{i-1,k}$$
这个递推式比较特别，第 $i$ 行的信息可以只从第 $i-1$ 行推过来，这是解迭代列可以做的问题。我们设
$$F_i(x)=\sum_{j=0}^\infty f_{i,j}x^j$$
递推式就可以写为（对等式两边分别提取 $x^j$ 项系数，对应的就是原式的等式两边）
$$(xF_i(x))'=\frac{F_{i-1}(x)}{1-x}$$
这样似乎不太好看，可以设 $G_i(x)=xF_i(x)$，就改写为
$$(1-x)xG_i'(x)=G_{i-1}(x)$$
但这样还是不便于处理，就要考虑**基变换换元**了。具体来说，我们希望找到合适的 $u$（也是一个关于 $x$ 的式子），满足 $H_i(u)=G_i(x)$，同时有
$$u \frac{\text d H_i(u)}{\text d u}=H_{i-1}(u)$$
根据链式法则：
$$  \frac{\text dG_i(x)}{\text dx}= \frac{\text dH_i(u)}{\text d u}  \frac{\text du}{\text dx}$$
在等式两边同乘 $(1-x)x$，左边就是 $G_{i-1}(x)$，同时也是 $H_{i-1}(u)$。这样就得到
$$H_{i-1}(u)=u \frac{\text dH_i(u)}{\text du}=x(1-x)\frac{\text dH_i(u)}{\text d u}  \frac{\text du}{\text dx}$$
化简一下，就得到关于 $u$ 的微分方程：
$$u=x(1-x) \frac{\text du}{\text dx}$$
解得 $u=x/(1-x)$。根据前面的边界条件可知 $F_0(x)=(1-px)^{-1}$，也就可以解出
$$H_0(u)=\frac{u}{1-(p-1)u}=\sum_{i\geq 0}(p-1)^iu^{i+1}$$
关于 $uH_i'(u)=H_{i-1}(u)$ 这个性质，将等式两边同时提取 $u^i$ 系数就会发现，每次迭代就是在 $u^i$ 系数上除以 $i$ 而已。这样就可以轻易地写出 $H_k(u)$：
$$H_k(u)=\sum_{i\geq 0}\frac{(p-1)^i}{(i+1)^k}u^{i+1}$$
接下来的工作就很简单了，再把 $H_k(u)$ 变回 $F_k(x)$ 即可：
$$\begin{aligned}f_{k,m}&=[x^m]\frac 1xH_k\left( \frac{x}{1-x}\right) \\ &= \sum_{i\geq 0} \frac{(p-1)^i}{(i+1)^k} [x^{m+1}] \left( \frac{x}{1-x}\right)^i \\ &= \sum_{i=0}^m \binom mi \frac{(p-1)^i}{(i+1)^k}\end{aligned}$$
直接计算即可，$(i+1)^{-k}$ 可以先用线性筛求幂，然后再线性求逆元，单次时间复杂度为 $\Theta(m+\pi(m) \log k)$，其中 $\pi(m)$ 表示不超过 $m$ 的质数个数。
***
最后我们来分析一下总时间复杂度，首先有一个分解质因数的复杂度，一般为 $\sqrt n$ 或 $\sqrt[4]{n}$。  
然后是算 $f_{k,m}$ 的时间复杂度，由于 $m$ 之和有一个显然的上界 $\log_2 n$，且质因数多于一个时，$\pi(m)$ 之和总会减少。也就是说，这部分的时间复杂度不会超过 $\mathcal O(\log_2 n +\pi(\log_2 n)\log k)$。

这里用的是朴素分解质因数，总时间复杂可以写为 
$$\mathcal O\left(\sqrt n+ \frac{ \log k}{\log \log n}\log n\right)$$

```cpp
#include<cstdio>
#define N 10003
#define ll long long
#define p 1000000007
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int fac[N],ifac[N];

void init(int n){
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for(int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
}

inline int binom(int n,int m){
    if(n<m) return 0;
    return (ll)fac[n]*ifac[m]%p*ifac[n-m]%p;
}

inline int solve(int n,int m,int q){
    int res = 0,tmp = 1;
    for(int i=0;i<=m;++i){
        res = (res+(ll)binom(m,i)*tmp%p*power(i+1,p-n-1))%p;
        tmp = (ll)tmp*(q-1)%p;
    }
    return res;
}

ll n;
int k,ans = 1;

int main(){
    scanf("%lld%d",&n,&k);
    init(233);
    for(ll i=2;i*i<=n;++i){
        if(n%i!=0) continue;
        int cnt = 0;
        while(n%i==0) n /= i,++cnt;
        ans = (ll)ans*solve(k,cnt,i%p)%p;
    }
    if(n>1) ans = (ll)ans*solve(k,1,n%p)%p;
    printf("%d",ans);
    return 0; 
}

```

---

## 作者：_Life_ (赞：6)

感觉题目很清爽啊，写篇题解。

### 题意
给定 $n,k$，一共会进行 $k$ 次操作，每次操作会把 $n$ 等概率的变成 $n$ 的某个因数。

求操作 $k$ 次后 $n$ 的期望，答案对 $10^9+7$ 取模。

$1 \le n \le 10^{15},1 \le k \le 10^4$

### 题解

看到因数，就想着把 $n$ 唯一分解下。

$n=\prod p_i^{k_i}$

$n$ 的因数个数为 $\prod k_i+1$

看到唯一分解，就想着如果是**积性**的就好了。

我们用 $E(n,k)$ 表示对 $n$ 操作 $k$ 次后的期望。

取两个数 $a,b$ 满足 $\gcd(a,b)=1$。

$$a=\prod p_i^{k_i}$$

$$b=\prod q_j^{l_j}$$

$$ E(a,k)=\dfrac{1}{\prod k_i+1} \cdot \sum_{x_1=0}^{k_1} \sum_{x_2=0}^{k_2}\cdots \sum_{x_i=0}^{k_i} E(p_1^{x_1}p_2^{x_2}\cdots p_i^{x_i},k-1) $$

$$ E(b,k)=\dfrac{1}{\prod l_j+1} \cdot \sum_{y_1=0}^{l_1} \sum_{y_2=0}^{l_2}\cdots \sum_{y_j=0}^{l_j} E(q_1^{y_1}q_2^{y_2}\cdots q_j^{y_j},k-1) $$

$$ E(a\cdot b,k)=\dfrac{1}{\prod k_i+1 \prod l_j+1} \cdot \sum_{x_1=0}^{k_1} \sum_{x_2=0}^{k_2}\cdots \sum_{x_i=0}^{k_i}\sum_{y_1=0}^{l_1} \sum_{y_2=0}^{l_2}\cdots \sum_{y_j=0}^{l_j} E(p_1^{x_1}p_2^{x_2}\cdots p_i^{x_i}q_1^{y_1}q_2^{y_2}\cdots q_j^{y_j},k-1)=E(a,k)\cdot E(b,k)$$


于是就可以把 $n$ 拆成质因子的幂次方了，不难发现质因子数量是 $\log n$ 级别的。

$$E(p_i^{k_i},k)=\dfrac{1}{k_i+1} \sum_{j=0}^{k_i}E(p_i^j,k-1)$$

对于质因子的幂次方，可以记忆化处理，全部乘起来就是答案。

总时间复杂度 $O(\sqrt n +k\log^2 n)$

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define per(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
inline void chkmax(int &a,int b){a=max(a,b);}
inline void chkmin(int &a,int b){a=min(a,b);}
typedef pair<int,int> pii;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*f;
}
inline void read(int &x){x=read();}
inline void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
inline void write(int x,char c){write(x),putchar(c);}
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		b>>=1,a=a*a%mod;
	}
	return ans;
}
int inv(int x){return qpow(x,mod-2);}
int n,k,f[64][10005];
int g(int ki,int k,int pi)
{
	if(f[ki][k]!=-1)return f[ki][k];
	if(k==0)return f[ki][k]=qpow(pi,ki);
	if(ki==0)return f[ki][k]=1;
	int ans=0;
	rep(i,0,ki)
		ans=(ans+g(i,k-1,pi))%mod;
	ans=ans*inv(ki+1)%mod;
	return f[ki][k]=ans;
}
signed main()
{
	read(n),read(k);
	int ans=1;
	for(int i=2;i*i<=n;i++)
	{
		int tot=0;
		while(n%i==0)
			n/=i,tot++;
		if(tot)
		{
			memset(f,-1,sizeof(f));
			ans=ans*g(tot,k,i)%mod;
		}
	}
	if(n!=1)
	{
		memset(f,-1,sizeof(f));
		ans=ans*g(1,k,n)%mod;
	}
	write(ans);
}
```

---

## 作者：lylyl (赞：6)

看着大家都没有详细解释为什么是积性函数,蒟蒻一直没懂~~蒟蒻果然是蒟蒻~~.于是就来发篇题解.

首先看着道题直接搞并不是很好搞.

于是我们初步的有一个思路:先将$n$分解质因数成
$$
N=\Pi_{i=1}^{k} p_i^{x_i}
$$


的形式,然后再对于每一个$p^x$计算答案,再将答案合并.

**我们先来解决如何合并的问题.**

对于一次操作,我们可以将其理解为对于每一个质因子的次数$x_i$,将其替换为区间$[0,x_i]$中的任意一个数,记为$x'$.

所以$N$操作一次后应变为
$$
N'=\Pi _{i=1}^{k} p_i^{x'_i}
$$
概率显然为$\Pi_{i=1}^{k}\frac1{x_i+1}$.

这也可以看成$k$个$p_i$的操作一次的概率之积.

~~显然~~这个可以推广.

$$
\therefore ans[N]=\Pi_{i=1}^{k}ans[p_i]
$$

于是答案就是个积性函数了.

**我们再来看看如何计算每一个$p_i$的答案.**

设$dp[s][j]$表示当前已经操作了$j$次,操作后的数为$p_i^s$的概率.

显然有状态转移方程$dp[s][j]=\sum_{l=s}^{x_i}\frac{dp[l][j-1]}{l+1}$,初始状态为$dp[x_i][0]=1$.

$\therefore ans_i=\sum_{j=0}^{x_i}dp[k][j]*p^j$

最终的答案即为$\Pi_{i=1}^{k}ans_i$.

*如果您像我一样无聊的话,您可以用滚动数据省去一维.*

```cpp
#include<bits/stdc++.h>
#define il inline
#define rg register
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const int O = 1e6 + 10, K = 1e4 + 10;
template<class TT>
il TT read() {
	TT o = 0, fl = 1; char ch = getchar();
	while (!isdigit(ch) && ch != '-') ch = getchar();
	if (ch == '-') fl = -1, ch = getchar();
	while (isdigit(ch)) o = o * 10 + ch - '0', ch = getchar();
	return fl * o;
}
ll n, ans = 1ll, res, dp[51], inv[51], val;
int k, tot, cnt;
il void solve () {
	res = 0; memset(dp, 0, sizeof dp); dp[cnt] = 1;
	for (int i = 1; i <= k; ++i)
		for (int j = 0; j <= cnt; ++j) {
			(dp[j] *= inv[j + 1]) %= mod;
			for (int k = j + 1; k <= cnt; ++k)
				(dp[j] += dp[k] * inv[k + 1] % mod) %= mod;
		}
	ll bin = 1, tmp = val % mod;
	for (int i = 0; i <= cnt; ++i, (bin *= tmp) %= mod)
		(res += dp[i] * bin % mod) %= mod;
	(ans *= res) %= mod;
}
int main() {
	n = read<ll>(), k = read<int>();
	inv[0] = inv[1] = 1;
	for (int i = 2; i < 51; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (ll i = 2ll; i * i <= n; ++i)
		if (n % i == 0){
			val = i;
			while (n % i == 0) n /= i, ++cnt;
			solve();
		}
	if (n ^ 1) val = n, cnt = 1, solve();
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Nemlit (赞：5)

我们考虑对于一个$N$，他如果变成了他的约数$x$，那又会变成一个子问题

我们定义$F(n, k)$为n操作k次的期望个数

那么我们有$F(n, k) =\sum_{x|n} F(x, k - 1) * \frac{1}{d}$（其中d为n的约数个数）

因为$N$的约数个数肯定在$\sqrt N$以内现在我们就有了一个$O(\sqrt N K)$的暴力了

前面的$\sqrt N$肯定是不能省略了，我们可不可以对$K$下手呢？

我们考虑$N$是质数，那么答案为$\frac{N + 2^k - 1}{2^k}$

再考虑一波$N = p^x$其中p是质数，那么我们考虑用上述$DP求解$

设$dp[i][j] $为第i此操作后，为$p^j$的概率

$dp[i][j] = \sum_{l = j}^x dp[i - 1][l] * \frac{1}{j}$

最后的答案为$\sum_{j = 1}^{x} dp[k][j] * p^j$

我们发现每一个$p_i^{j}$互不影响，这又是一个积性函数

$sum[i][j] * sum[i][k] = sum[i][j * k](gcd(j, k) == 1)$

证明的话我们一样回归定义，假设变成$p_1^j * p_2^0$的概率为x，$p_1^0 *p_2^k$的概率为y，那么$p_1^j*p_2^k$的概率一定为$x*y$

于是我们只需要对$N$分解质因数后再套一个$\prod$即可

这样的复杂度是$\sqrt N + K * log^3N=10^9$

但是由于$log$不一定为2，所以这个复杂度是可以过这道题的
# $Code:$
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
#define il inline
#define re register
#define int long long
#define mod 1000000007
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define mem(k, p) memset(k, p, sizeof(k))
#define maxn 1000005
int n, m, prim[maxn], tot, dis[maxn], dp[10005][50], ans, inv[100], Ans = 1;
il void get(int x) {
	for(re int i = 2; i * i <= x; ++ i) {
		if(x % i == 0) prim[++ tot] = i;
		while(x % i == 0) x /= i, ++ dis[tot];
	}
	if(x != 1) prim[++ tot] = x, ++ dis[tot];
}
il int qpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = r * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return r;
}
signed main() {
	n = read(), m = read();
	get(n);
	rep(i, 1, 60) inv[i] = qpow(i, mod - 2);
	rep(T, 1, tot) {
		mem(dp, 0), dp[0][dis[T]] = 1, ans = 0;
		rep(i, 1, m) {
			rep(j, 0, dis[T]) {
				rep(k, j, dis[T]) dp[i][j] = (dp[i - 1][k] * inv[k + 1] % mod + dp[i][j]) % mod;
			}
		}
		rep(i, 0, dis[T]) ans = (ans + dp[m][i] * qpow(prim[T] % mod, i) % mod) % mod;
		Ans = ans * Ans % mod;
	}
	printf("%lld", Ans);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：5)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10230547.html)

## Description

给定一个数 $n$，对它进行 $k$ 次操作，每次将当前的数改为自己的因数，包括 $1$ 和自己。写出变成所有因数的概率是相等的。求 $k$ 次以后 $n$ 期望会变成多少

## Input

一行两个整数 $n,k$

## Output

一行一个整数代表答案

## Hint

$1~\leq~n~\leq~10^{15}~,~1~\leq~k~\leq~10^4$

## Solution

#### Hello 2019！

我们考虑整个数字变化的树形图：

以 $n~=~6~,~k~=~2$ 为例：

![qwq](https://cdn.luogu.com.cn/upload/pic/48194.png)

（恕我直言，这图是真的丑）

然后我们将这张图改一下，要求每个非叶节点都有 $4$ 个孩子，如果孩子数不足，就让他们平分这四个。于是新的变化图如下：

![qwq](https://cdn.luogu.com.cn/upload/pic/48195.png)

（恕我直言，这图更丑了）

我们发现这张图上所有叶节点出现的概率都是等可能的，并且他们包含了所有的情况，所以求出这些数字的和再除以节点数就是期望值。

接着考虑由于一个数字的所有质因数都是独立的，同时每个质因子都可以画出类似的转移图，依据唯一分解定理，我们可以将质因子拆开，对于每个质因子求出他们期望变成多少，然后乘起来即为总期望。这里的质因子包括了质数 $p$ 和它的指数 $c$。

接着考虑我们对质因子DP。一次对 $p^c$ 的操作相当于将其变成 $p^0,p^1,p^2,\dots p^c$ 中的任意一个。于是我们可以将一次操作转化成将指数 $c$ 变成 $[1,c]$ 中任意一个数。我们规定任何一个节点都有 $d(n)$ 个孩子， $d(n)$ 为 $n$ 的因数个数。则对于一个数值为 $x$ 的节点，她有 $\frac{1}{x + 1}$ 的概率变成 $y~(0~\leq~y~\leq~x)$，那么它会占据 $x$ 的 $\frac{d(n)}{x + 1}$ 个孩子。

例如，对于 $2^2$ 进行 $2$ 次变化的指数图如下

![qwq](https://cdn.luogu.com.cn/upload/pic/48204.png)

我们认为粉色的位置每个数占据了 $\frac{1}{2}$ 个儿子

于是我们考虑当我们进行了 $i$ 次变化，第 $w$ 个质因子在树形图上的第 $i$ 层指数数值为 $j$ 的节点个数，则显然有

 $$f_{w,i,j}~=~\sum_{h = j}^{c_w}~f_{w,i - 1,h}~\times~\frac{d(n)}{h + 1}$$

其中 $c_j$ 为 $n$ 的唯一分解式中对应项的指数。

于是我们枚举 $n$ 的因数，求出他们出现的次数与他们值的乘积，除以最下面一层的节点个数即为答案

$$\begin{aligned}ans~& =~\frac{1}{d^k(n)}~\sum_{x \mid n}~Times_d~\times~x\\&=\frac{1}{d^k(n)}~\sum_{x \mid n}~d~\prod_{i = 1}^{d(n)}~f_{i,k,h}\end{aligned}$$

其中 $h$ 为 $d$ 唯一分解式对应项的指数。

我们发现在 DP时，第 $k$ 层每个位置都被乘了 $d^k(n)$，于是可以和式子中的 $\frac{1}{d^k(n)}$ 约掉，式子变为

 $$f_{w,i,j}~=~\sum_{h = j}^{c_w}~f_{w,i - 1,h}~\times~\frac{1}{h + 1}$$

$$\begin{aligned}ans~& =~\sum_{x \mid n}~Times_d~\times~x\\&=~\sum_{x \mid n}~d~\prod_{i = 1}^{d(n)}~f_{i,k,h}\end{aligned}$$

看起来舒服多了。

考虑复杂度：我们枚举了 $k$ 层，每层枚举了 $n$ 的质因数个数次，这里的质因数不包括指数，但是包括重复的，例如 $p^2$ 算作两个质因数。由于一个数 $n$ 的质因数为 $O(\log n)$，所以总状态复杂度为 $O(k \log n)$。在转移时，我们枚举的上界是 $O(\log n)$，所以总复杂度为 $O(k~\log^2 n)$。发现转移的位置事实上转移了一个加权后缀和，于是我们再开一个数组维护这个后缀和即可做到 $O(k \log n)$。

注意到这样会爆空间，但是发现对于每个DP状态我们只需要第 $k$ 层的情况，并且第一维互不影响，于是我们可以把第一维省掉，每次DP完一个质因子用另一个数组记录第 $k$ 层的答案，即可做到空间复杂度 $O(\log^2 n~+~k~\log n)$。（其实动态开DP数组可以做到空间复杂度 $O(k~\log n)$，但是没啥意义）

最后统计答案时直接爆搜因数即可。

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long ll;

namespace IPT {
    const int L = 1000000;
    char buf[L], *front=buf, *end=buf;
    char GetChar() {
	    if (front == end) {
		    end = buf + fread(front = buf, 1, L, stdin);
		    if (front == end) return -1;
		}
	    return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
    rg char ch = IPT::GetChar(), lst = ' ';
    while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
    while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
    if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
    rg char ch = IPT::GetChar(), lst = ' ';
    while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
    while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
    if (ch == '.') {
	    ch = IPT::GetChar();
	    double base = 1;
	    while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
    if (lst == '-') x = -x;
}

namespace OPT {
    char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
    if (x < 0) {x = -x, putchar('-');}
    rg int top=0;
    do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
    while (top) putchar(OPT::buf[top--]);
    if (pt) putchar(aft);
}

const int maxt = 60;
const int maxm = 10010;
const int MOD = 1000000007;

ll n, kk, ans;
ll frog[maxm][maxt], inv[maxt], gorf[maxt][maxt], sum[maxm][maxt];
std::vector<ll> d;
int cnt;
int c[maxt];

void Get_Inv(ci, ci);
void dfs(ci, ci);
int mpow(cl x, int);

signed main() {
    freopen("1.in", "r", stdin);
    qr(n); qr(kk);
    Get_Inv(59, MOD);
    ll dn = n;d.push_back(0);
    for (ll i = 2; (i * i) <= n; ++i) if(!(dn % i)) {
	    d.push_back(i); ++cnt;
	    while (!(dn % i)) {dn /= i; ++c[cnt];}
	}
    if (dn != 1) {++cnt; d.push_back(dn); c[cnt] = 1;}
    for (rg int j = 1; j <= cnt; ++j) {
	    frog[0][c[j]] = sum[0][c[j]] = inv[c[j] + 1];
	    for (rg int i = 0; i < c[j]; ++i) frog[0][i] = 0, sum[0][i] = sum[0][c[j]];
	    for (rg int i = 1; i <= kk; ++i) {
		    rg int di = i - 1;
		    sum[i][c[j] + 1] = 0;
		    for (rg int k = c[j]; ~k; --k) {
			    frog[i][k] = sum[di][k];
			    sum[i][k] = (sum[i][k + 1] + frog[i][k] * inv[k + 1] % MOD) % MOD;
			}
		}
	    for (rg int k = 0; k <= c[j]; ++k) gorf[j][k] = frog[kk][k];
	}
    dfs(1, 1);
    qw((ans + MOD) % MOD, '\n', true);
    return 0;
}

void Get_Inv(ci x, ci p) {
    inv[1] = 1;
    for (rg int i = 2; i <= x; ++i) inv[i] = - p / i * inv[p % i] % MOD;
}

void dfs(ci cur, ci v) {
    if (cur > cnt) {ans = (ans + v) % MOD; return;}
    for (int i = 0; i <= c[cur]; ++i) dfs(cur + 1, 1ll * gorf[cur][i] * v % MOD * mpow(d[cur], i) % MOD);
}

int mpow(cl x, int y) {
    ll _ret = 1, _temp = x % MOD;
    while (y) {
	    if (y & 1) _ret = _ret * _temp % MOD;
	    _temp = _temp * _temp % MOD;
	    y >>= 1;
	}
	return _ret;
}
```



---

## 作者：ouuan (赞：3)

这里是复杂度为 $O(\sqrt n+k\log n)$ 的做法，很多人都是 $O(\sqrt n+k\log^2 n)$ 的。

先考虑 $n=p^{\alpha}$ 怎么做。 令 $f_{i,j}$ 表示已经操作了 $i$ 次，剩下的数为 $p^j$ 的概率。

那么，$f_{i,j}=\sum\limits_{t=j}^\alpha\frac{f_{i-1,t}}{t+1}$，因为对于每个 $f_{i-1,t}$ 都有 $\frac1{t+1}$ 的概率转移到 $f_{i,j}(0\le j\le t)$ 。

观察这个式子，可以发现，$f_{i,j}=f_{i,j+1}+\frac{f_{i-1,j}}{j+1}$，于是可以 $O(\alpha k)$ 计算出 $f_{k,0..\alpha}$，答案就是 $\sum\limits_{j=0}^\alpha f_{k,j}\times p^j$。

如何扩展到任意的 $n$ 呢？可以发现，对于每个质因数，每次操作减去多少个该质因数是概率独立的，所以可以分开计算然后乘起来。

使用滚动数组可以将空间复杂度优化至 $O(\log n)$（质因数个数）。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N=100010;
const int M=1000000007;

int qpow(int x,int y);

ll n;
int k,p[60][2],tot,q=1,ans=1,f[60],inv[60];

int main()
{
    int i,j,temp,sum;
    
    cin>>n>>k;
    
    for (i=1;i<60;++i) //预处理逆元
    {
        inv[i]=qpow(i,M-2);
    }
    
    for (i=2;1ll*i*i<=n;++i) //分解质因数
    {
        if (n%i==0)
        {
            p[++tot][0]=i;
            while (n%i==0)
            {
                ++p[tot][1];
                n/=i;
            }
        }
    }
    
    if (n>1)
    {
        p[++tot][0]=n%M;
        p[tot][1]=1;
    }
    
    for (;tot;--tot) //对每个质因数分别dp
    {
        memset(f,0,sizeof(f));
        f[p[tot][1]]=1;
        for (i=1;i<=k;++i)
        {
            for (j=p[tot][1];j>=0;--j)
            {
                f[j]=(f[j+1]+(ll)f[j]*inv[j+1])%M;
            }
        }
        sum=0;
        temp=1;
        for (j=0;j<=p[tot][1];++j) //乘起来
        {
            sum=(sum+(ll)temp*f[j])%M;
            temp=(ll)temp*p[tot][0]%M;
        }
        ans=(ll)ans*sum%M;
    }
    
    cout<<ans;
    
    return 0;
}

int qpow(int x,int y) //快速幂，用于求逆元
{
    int out=1;
    while (y)
    {
        if (y&1)
        {
            out=(ll)out*x%M;
        }
        x=(ll)x*x%M;
        y>>=1;
    }
    return out;
}
```

---

## 作者：__Hacheylight__ (赞：2)

题意就是给一个数，每次可以把它替换成为它的一个因数，问替换k次后期望的数为多少

一看就不会做，只好先从简单的开始着手

如果一个数为质数，肯定非常好处理，有$\frac{1}{2^k}$种可能为原数，其余都为1

如果一个数的分解质因数形式为$x=p_1^{e_1}$怎么搞？ 

很容易想出$dp$

$dp[i][j]$表示做了$i$次操作，当前指数为$j$的答案

枚举$0<=k<=j,dp[i+1][k]+=dp[i][j]*inv[j+1]$，乘以$inv[j+1]$是因为k有$\frac{1}{j+1}$种可能，$dp[i][j]$只是其中的一种

然后怎么推广到数的形式为$x=p_1^{e_1}*p_2^{e_2}*...*p_k^{e_k}$

**我们发现该函数是积性函数**

然后就分解质因数，对于每个质因数分别$dp$再求积就行了

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define per(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define enter cout << endl
#define siz(x) ((int)x.size())
typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 10010 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const ll MOD = 1000000007 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

#define int long long

ll n, m, ans = 1 ;
ll f[N][65] ; // f[i][j]表示前i次操作，使得值变成了x^j的方案数
ll inv[N] ;

void init() {
	inv[1] = 1 ;
	for (int i = 2; i <= 1000; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD ;
}

ll solve(ll x, ll y) {
	clr(f) ;
	f[0][y] = 1 ;
	for (int i = 0; i < m; i++)
	for (int j = 0; j <= y; j++)
	if (f[i][j]){
		for (int k = 0; k <= j; k++) f[i + 1][k] = (f[i + 1][k] + f[i][j] * inv[j + 1]) % MOD ; // 枚举转移到f[i+1][k]
	}
	ll now = 1, sum = 0 ;
	for (int i = 0; i <= y; i++) {
		sum = (sum + now * f[m][i]) % MOD ;
		now = now * x % MOD ;
	}
	return sum ;
}

signed main(){
	scanf("%lld%lld", &n, &m) ;
	init() ;
	for (ll i = 2; i <= sqrt(n); i++)
	if (n % i == 0){
		ll cnt = 0 ;
		while (n % i == 0) cnt++, n /= i ;
		ans = ans * solve(i, cnt) % MOD ;
//		cout << i << " " << cnt << " " << ans << endl ;
	}
	if (n > 1) ans = ans * solve(n, 1) % MOD ;
	printf("%lld\n", ans) ;
	return 0 ;
}

/*
写代码时请注意：
	1.ll？数组大小，边界？数据范围？
	2.精度？
	3.特判？
	4.至少做一些
思考提醒：
	1.最大值最小->二分？
	2.可以贪心么？不行dp可以么
	3.可以优化么
	4.维护区间用什么数据结构？
	5.统计方案是用dp？模了么？
*/

```

---

## 作者：bsdsdb (赞：1)

题意：有数 $n,k$，一轮操作会让 $n$ 等概率地变成他的某个因数，求 $k$ 轮操作后 $n$ 的期望值 $\bmod(10^9+7)$。$n\le 10^{15},k\le10^{18}$。

记答案为 $\mathbb E_k(n)$，把 $n$ 质因数分解成 $\prod_{i=1}^\beta{p_i}^{\alpha_i}$。容易得出 $\Omicron(d^2(n)k)$ 的 dp：

$$
\mathbb E_j(i)=\frac1{d(i)}\sum_{\ell\mid i}\mathbb E_{j-1}(\ell)
$$

引理 1：$\mathbb E_k$ 是积性函数。

> 证：
>
> $$
> \begin{aligned}
> \mathbb E_k(x)=&\frac1{d(x)}\sum_{t\mid i}\mathbb E_{k-1}(t)\\
> =&\frac1{d(x)}(1\ast\mathbb E_{j-1})\\
> \mathbb E_0=&\mathrm{Id}
> \end{aligned}
> $$
>
> 两个积性函数的 Dirichlet 卷积和对点乘都是积性函数，归纳即可。

所以，所求答案即为

$$
\prod_{i=1}^\beta\mathbb E_k({p_i}^{\alpha_i})
$$

考虑对某个固定的 $i$ 求解 $\mathbb E_k({p_i}^{\alpha_i})$。接下来将省略下标 $\cdot_i$。因为 $p^\alpha$ 的因数集 $\{d:d\mid p^\alpha\}=\{p^\delta:\delta\le\alpha\}$，所以对 $p^\alpha$ 进行操作，相当于把 $\alpha$ 变成一个于 $[0,\alpha]$ 中随机选取的数。设 $\alpha$ 一开始是 $x$，经过 $k$ 次操作后变成 $t$ 的概率为 $P(k,t,\alpha)$（把 $k$ 和 $t$ 提到前面的作用待会就会知道），则：

$$
\mathbb E_k(p^\alpha)=\sum_{t=0}^\alpha p^t P(k,t,\alpha)\\
P(k,t,\alpha)=\frac1{\alpha+1}\sum_{\delta=0}^\alpha P(k-1,t,\delta)\\
P(0,t,\alpha)=[t=\alpha]
$$

如果使用递推式，总复杂度为 $\Omicron(k\log^2n)$，理论上已经可以通过 $k\le10^4$ 的原题，但是我被卡常了。所以，我们尝试以更低的复杂度求解 $P(k,t,\alpha)$ 的值。发现 $P(k-1,t,\delta)$ 到 $P(k,t,\alpha)$ 的转移长得像一个线性变换，所以把 $P(k,t,\cdot)$ 视作一个列向量，然后构造矩阵乘法解决问题：

$$
Q_{k,t,\alpha}\coloneqq
\begin{bmatrix}
P(k,t,0)\\
P(k,t,1)\\
\vdots\\
P(k,t,\alpha)
\end{bmatrix}\\
M_\alpha\coloneqq
\begin{bmatrix}
\frac11\\
\frac12&\frac12\\
\vdots&\vdots&\ddots\\
\frac1{\alpha+1}&\frac1{\alpha+1}&\cdots&\frac1{\alpha+1}
\end{bmatrix}\\
Q_{k,t,\alpha}=M_\alpha Q_{k-1,t,\alpha}={M_\alpha}^kQ_{0,t,\alpha}
$$

对于所有的 $\alpha$ 预处理出 ${M_\alpha}^k$，然后对所有可能的 $t$ 乘出 $Q_{k,t,\alpha}$，从而得出 $P(k,t,\alpha)$，总复杂度为 $\Omicron(\sqrt n+\log^4n\log k)$（朴素质因数分解）或 $\Omicron(n^\frac14\log n+\log^4n\log k)$（使用 Pollard-Rho 分解质因数）。

---

## 作者：az__eg (赞：1)

引荐模拟赛，出题人给这道题放第二题。

首先看到 $n\leq 10^{15}$，想到分解因数。

考虑一种过不去的做法。

就是记录下每一个因数，然后 dp 转移，发现过不去，时间复杂度为 $O(n^{\frac{2}{3}}m)$。

发现这个 $m$ 约不掉，考虑优化 $n^{\frac{2}{3}}$。大胆猜个结论，不同质因数互不影响，最后再把这些质因子有几个的概率乘起来，组合一下得到答案。

证明：

我们先将 $n$ 分解为 $\Pi{p_i^{a_i}}$。发现每次变为约束即将每一个 $a_i$ 等概率变成 $0$ 到 $a_i$ 中的任意一个数，最后每一个因数的概率可以表示为第 $i$ 个质因子有 $j$ 的概率。因为每次减少的质因数的概率互相独立，所以可以这么算。

设 $dp_{i,j}$ 表示第 $i$ 种质因子还有 $j$ 个的概率，$num_i$ 表示第 $i$ 种质因子一开始有几个。

然后 dp 的方程式：

$$dp_{i,j} = \sum\limits^{num_i}_{k=j} dp_{i,k}\times \frac{1}{k+1}$$

然后还可以前缀和小优化一下，最终复杂度 $O(m\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=1e9+7;
int n,m;
int ksm(int a,int b)
{
	a%=MOD;
	int rt=1;
	while(b!=0)
	{
		if(b%2==1)
		{
			rt*=a;
			rt%=MOD;
		}
		a*=a;
		a%=MOD;
		b>>=1;
	}
	return rt;
}
int prime[100001];
int cnt;
int ans;
int num[100001];
int dp[61][64];
int inv[100001];
void init()
{
	int i,j;
	for(i=0;i<=100000;i++)
	{
		inv[i]=ksm(i,MOD-2);
	}
}
void dfs(int dep,int cal,int cal2)//统计因数，n的三次方根，不会炸
{
	if(dep==cnt+1)
	{
		ans+=cal*cal2%MOD;
		ans%=MOD;
		return;
	}
	int i,j;
	int dq=cal;
	for(i=0;i<=num[dep];i++)
	{
		if(i>0)
		dq*=prime[dep];
		dfs(dep+1,dq%MOD,cal2*dp[dep][i]%MOD);
	}
}
signed main()
{
	init();
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	int i,j,k,l;
	i=2;
	while(i*i<=n)
	{
		if(n%i==0)
		{
			prime[++cnt]=i;
			while(n%i==0)
			{
				n/=i;
				num[cnt]++;
			}
		}
		i+=1;
	}
	if(n>1)
	{
		prime[++cnt]=n;
		num[cnt]=1;
	}
	for(i=1;i<=cnt;i++)
	{
		dp[i][num[i]]=1;
		for(j=1;j<=m;j++)
		{
			int sum=0;
			for(k=num[i];k>=0;k--)
			{
				sum+=dp[i][k]*inv[k+1];//前缀和转移
				sum%=MOD;
				dp[i][k]=sum;
				dp[i][k]%=MOD;
			}
		}
	}
	dfs(1,1,1);
	cout<<ans;
}
```


---

## 作者：chihik (赞：1)

令 $f_{n,k}$ 为 数 $n$ 进行 $k$ 次操作后的期望值，由题得：

$$f_{k,n}=
\begin{cases}
n &k=0\\
\displaystyle \frac{1}{d(n)}\sum_{d|n}f_{k-1,d} & k \not= 0 \\
\end{cases}$$

显然是一个积性函数，考虑质数取值

$$f_{k,p^w}=\frac{1}{w+1} \sum_{i=0}^w f_{k-1,p^i}$$

质因数分解后求值即可，复杂度 $\mathcal O (\sqrt n+k\log n)$

```cpp
#include <cstdio>
#define LL long long

const int MAXL = 100 , Mod = 1e9 + 7;
int Add( int x , int y ) { x += y; return x >= Mod ? x - Mod : x; }
int Sub( int x , int y ) { x -= y; return x < 0 ? x + Mod : x; }
int Mul( int x , int y ) { return 1ll * x * y % Mod; }
int Qkpow( int x , int po ) { int p = 1; for( ; po ; po >>= 1 , x = Mul( x , x ) ) if( po & 1 ) p = Mul( p , x ); return p; }
int Inv( int x ) { return Qkpow( x , Mod - 2 ); }
int iv[ MAXL + 5 ];
void Init( ) {
	iv[ 1 ] = 1;
	for( int i = 2 ; i <= MAXL ; i ++ ) iv[ i ] = Mul( iv[ Mod % i ] , Mod - Mod / i );
}

int g[ 2 ][ MAXL + 5 ];
int f( LL n , int w , int k ) {
	n %= Mod;
	for( int i = 0 , p = 1 ; i <= w ; i ++ , p = Mul( p , n ) ) g[ 0 ][ i ] = p;
	for( int i = 1 ; i <= k ; i ++ ) {
		for( int j = 0 , Sum = 0 ; j <= w ; j ++ ) {
			Sum = Add( Sum , g[ ( i - 1 ) & 1 ][ j ] );
			g[ i & 1 ][ j ] = Mul( iv[ j + 1 ] , Sum );
		}
	}
	return g[ k & 1 ][ w ];	
}

LL n; int k;
int main( ) {
	Init();
	scanf("%lld %d",&n,&k);

	int Ans = 1;
	for( LL i = 2 ; i * i <= n ; i ++ )
		if( n % i == 0 ) {
			int w = 0;
			for( ; n % i == 0 ; n /= i ) w ++;
			Ans = Mul( Ans , f( i , w , k ) );
		}
	if( n > 1 ) Ans = Mul( Ans , f( n , 1 , k ) );
	printf("%d\n", Ans );
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [CF1097D](https://codeforces.com/contest/1097/problem/D)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1097D)

---

## 思路

我们可以发现，$n$ 的不同质因子之间不会互相干扰。

我们令 $d_k(n)$ 表示 $n$ 进行 $k$ 次操作后的期望，那么若 $n = \prod p_i^{q_i}$（质因数分解），有 $d_k(n) = \prod d_k(p_i^{q_i})$。

那么接下来就讨论 $d_k(p^q)$ 如何求值。

若 $q=0$，显然 $d_k(p^q) = 1$。若 $k = 0$，有 $d_k(p^q) = p^q$。

对于 $kq\not=0$ 的情况，每一次操作相当于从 $p^0, p^1, \cdots, p^q$ 中选一个作为结果，所以容易推出 $d_k(p^q) = \frac{1}{q + 1}\sum_{i=0}^qd_{k-1}(p^i)$。

## 实现

注意到，$k \le 10^4$，而 $n$ 有最多不会超过 $14$ 个质因子（$2\times3\times\dots\times43\gt10^5$），并且每个质因子的次数不会超过 $\log n \lt 55$。这就意味着对于一个质因子，$d$ 的不同情况有 $k\log n \lt 5.5\times 10^5$ 种，乘上 $14 \lt 10^7$，加个记忆化搜索就可以过了。

最终复杂度：$O(\sqrt{n}+k\log n)$，有约 $14$ 倍的常数。

## 注意事项

由于 $n$ 很大，需要开 `long long`，在枚举质因子时也要开。~~我一开始没开结果调了半天。~~

## 核心代码

```cpp
ll d[55][MAXK];

inline ll dp(ll b, int p, int t) // b(ase) 是质因数，p(ower) 是指数，t 是操作数（不与全局变量 k 重名）
{
    if (d[p][t]) // 记搜优化
    {
        return d[p][t];
    }
    if (p == 0)
    {
        return d[p][t] = 1;
    }
    if (t == 0)
    {
        return d[p][t] = pow(b, p, MOD);
    }
    ll res = 0;
    for (int i = 0; i <= p; i++)
    {
        res = (res + dp(b, i, t - 1)) % MOD;
    }
    return d[p][t] = res * inv(p + 1, MOD) % MOD; // 记得乘逆元
}
```


---

## 作者：氧少Kevin (赞：0)

## CF1097D - Makoto and a Blackboard
- https://codeforces.com/problemset/problem/1097/D
- 质因数分解、积性函数、概率期望
- 紫、*2200
## 题意
- 你手里有一个数字，每次操作可以把这个数字等概率变成这个数字的某个约数（因数）
- 给出 $n(1\leq n \leq 10^{15})$ 和 $K(1\leq K\leq 10^4)$，分别代表手里的数字的初始值，和操作的次数
- 问 $K$ 次操作后，手里数字的期望

## 思路
### 超时做法
- 令 $dp[i][j]$ 为操作了 $i$ 次，当前因数为 $j$ 的概率（用 map 实现 DP 数组）
- 转移：$dp[i][j]\rightarrow dp[i+1][p]\ \ ,i<K,p|j$

### 正确思路
- 手里的数字可以按质因子考虑，也就是说，可以写成 $p_1^{x_1}\times p_2^{x_2}\times \dots \times p_k^{x_k}$ 的形式
- 每次操作相当于将每个 $x_1,x_2,\dots x_k$ 随机降低某个值（可以是 $0$）
- 那么，分别算出上式中 $p_1^{x_1}, p_2^{x_2}, \dots ,$ 和 $p_k^{x_k}$ 在操作 $K$ 次后的大小的期望，乘在一起，就是答案


---

