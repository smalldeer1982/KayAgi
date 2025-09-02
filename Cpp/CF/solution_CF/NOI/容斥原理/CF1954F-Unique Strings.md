# Unique Strings

## 题目描述

我们称两个字符串 $a$ 和 $b$ 是相等的，如果可以通过循环移位字符串 $a$ 得到字符串 $b$。例如，字符串 0100110 和 1100100 是相等的，而 1010 和 1100 则不相等。

给定一个长度为 $n$ 的二进制字符串 $s$，其前 $c$ 个字符为 1，后 $n-c$ 个字符为 0。

每次操作，你可以将一个 0 替换为 1。

请计算在不超过 $k$ 次操作内，最多可以得到多少个不同的字符串（不同指的是循环同构意义下的不同字符串）。由于答案可能很大，请输出答案对 $10^9+7$ 取模后的结果。

## 说明/提示

在第一个测试用例中，唯一可能的字符串是 1。

在第二个测试用例中，可能的字符串有：100、110 和 111。字符串 101 与 110 是循环等价的，因此不计入。

在第三个测试用例中，可能的字符串有：10000、11000、10100。字符串 10010 与 10100 循环等价，10001 与 11000 循环等价。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1 0```

### 输出

```
1```

## 样例 #2

### 输入

```
3 1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
5 1 1```

### 输出

```
3```

## 样例 #4

### 输入

```
6 2 2```

### 输出

```
7```

## 样例 #5

### 输入

```
24 3 11```

### 输出

```
498062```

# 题解

## 作者：bsdsdb (赞：6)

题意：有 $n$ 长度的 01 串，前 $c$ 个字符为 $1$，其余为 $0$。你可以将不超过 $k$ 个 $0$ 改成 $1$，求能得到的循环意义下不同的 01 串个数。

显然是 Burnside 引理。对于样例 $(n,c,k)=(5,1,1)$，「开头为 $1$，一共至多两个 $1$，转 $1,2,3,4$ 下不动」的 01 串个数为 $0$，转 $5$ 下不动的为 $5$。算出来是 $\frac55=1$，与样例输出不符。这中间出的问题在于违反了 Burnside $\forall g\in G,x\in X:g(x)\in X$ 的要求。刚刚我们设 $X$ 表示所有「开头为 $1$，一共至多两个 $1$，长度为 $5$」的 01 串，但是 $10100$ 转一下就会变成 $01010$，就不在 $X$ 里面了。所以我们考虑扩展 $X$，将其定义为「长度为 $n$，$1$ 的个数在 $[c,c+k]$ 中，且存在连着的 $c$ 个 $1$」的 01 串。此时 $X$ 在 $G$ 中置换意义下不同个数与原题所求相同。

为了减少麻烦，在 $n=c+k$ 时令 $k\gets k-1$，最终答案加上 $1$。设转 $x$ 下的不动点个数为 $f(x)$。下文的「段」指从 $[1,x]$ 到 $[n-x+1,n]$ 共 $\frac nx$ 个内部染色不受限的区间。在 $c\ge x$ 的时候要全部涂上 $1$，又因为 $c+k<n$ 所以不可能。对于 $c<x$，在初始的 $k$ 次机会中要先拿出 $c\left(\frac nx-1\right)$ 次把每一段的头 $c$ 个字符染成 $1$，拿不出来说明 $f(x)=0$。否则，易得每一段只能至多染 $k':=\left\lfloor\frac{k-c\left(\frac nx-1\right)}{\frac nx}\right\rfloor$ 个（拿出去头 $c$ 个后，一段要染一个，$\frac nx$ 段就要染 $\frac nx$ 个）。经过这些转化，$f(x)$ 变成了「长度为 $x$，$1$ 的个数在 $[c,c+k']$ 内，串成一圈后存在连续 $c$ 个 $1$」的 01 串个数。

考虑其反面，「长度为 $x$，$1$ 的个数在 $[c,c+k']$ 内，串成一圈后没有连续 $c$ 个 $1$」的 01 串个数，记他为 $g(x)$。易得 $f(x)=\sum_{i=c}^{c+k}\binom xi-g(x)$。我们先假装他没有串成一圈，是一个链，那么就可以 dp：设 $\gdef\dp{\mathrm{dp}}\dp_{i,j}$ 为「长度为 $i$，第 $i$ 位是 $0$，一共有 $j$ 个 $1$，不存在连续 $c$ 个 $1$」的 01 串个数。那么有：$\dp_{0,0}=1,\dp_{i,j}=\sum_{k=0}^{c-1}\dp_{i-1-k,j-k}$，前缀和优化即可。对于串成一圈的情况，设前面有极大的连续 $y$ 个 $1$，后面有 $z$ 个，满足 $y+z<c$，那么此时情况数为 $\sum_{j=c-y-z}^{c+k-y-z}\dp_{x-y-z-1,j}$。发现他只和 $y+z$ 有关，所以可以改成「前后面极大连续 $1$ 个数总和为 $y$」的情况数，他等于 $(y+1)\sum_{j=c-y}^{c+k-y}\dp_{x-y-1,j}$。那么 $g(x)=\sum_{y=0}^{c-1}(y+1)\sum_{j=c-y}^{c+k-y}\dp_{x-y-1,j},f(x)=\sum_{i=c}^{c+k}\binom xi-g(x),\gdef\ans{\mathrm{ans}}\ans=\frac1n(f\ast\varphi)(n)$。复杂度 $\Omicron(d(n)n(n+\log p))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


const ll MAXN = 3005, mod = 1e9 + 7;

ll n, c, K, ad, phi[MAXN], fac[MAXN], dp[MAXN][MAXN], prv[MAXN][MAXN];

void init(ll N = 3000) {
	phi[1] = 1;
	for (ll i = 2; i <= N; ++i) {
		phi[i] = i;
		ll x = i;
		for (ll j = 2; j <= x; ++j) {
			if (x % j == 0) phi[i] = phi[i] / j * (j - 1);
			while (x % j == 0) x /= j;
		}
	}
	fac[0] = fac[1] = 1;
	for (ll i = 2; i <= N; ++i) fac[i] = fac[i - 1] * i % mod;
}

ll qpow(ll x, ll y) {
	if (!y) return 1;
	if (y & 1) return x * qpow(x, y ^ 1) % mod;
	return qpow(x * x % mod, y >> 1);
}
ll inv(ll x) {return qpow(x, mod - 2);}
ll binom(ll x, ll y) {return fac[x] * inv(fac[y]) % mod * inv(fac[x - y]) % mod;}

ll f(ll x) {
	if (c >= x) return 0;
	if ((K - (n / x - 1) * c) < 0) return 0;
	ll ret = 0, k = (K - (n / x - 1) * c) / (n / x);
	for (ll i = c; i <= c + k; ++i) (ret += binom(x, i)) %= mod;
	ll g[MAXN] = {};
	for (ll i = 0; i < c; ++i) for (ll j = c; j <= c + k; ++j) (g[i] += dp[x - i - 1][j - i]) %= mod;
	for (ll i = 0; i < c; ++i) (ret -= g[i] * (i + 1) % mod - mod) %= mod;
	return ret;
}

int main() {
	init();
	cin >> n >> c >> K;
	if (c == n) cout << 1 << endl, exit(0);
	if (c + K == n) ad = 1, --K;
	dp[0][0] = prv[0][0] = 1;
	for (ll i = 1; i <= n + 1; ++i) {
		for (ll j = 0; j < i; ++j) {
			if (i == j + 1) {
				if (j >= c) dp[i][j] = 0;
				else dp[i][j] = 1;
			} else if (!j) {
				dp[i][j] = 1;
			} else {
				dp[i][j] = (prv[i - 1][i - 1 - j] - prv[max(i - c - 1, ll(0))][i - 1 - j] + mod) % mod;
			}			
			prv[i][i - j] = (prv[i - 1][i - j] + dp[i][j]) % mod;
		}
	}
	ll ans = 0;
	for (ll i = 1; i * i <= n; ++i) {
		if (n % i) continue;
		(ans += phi[n / i] * f(i) % mod) %= mod;
		if (i * i != n) (ans += phi[i] * f(n / i) % mod) %= mod;
	}
	(ans *= inv(n)) %= mod;
	cout << ans + ad << endl;
	return 0;
}
```

---

## 作者：Lgx_Q (赞：3)

没用 Burnside 过了这题。

原题相当于求有多少个环状 $01$ 串，使得 $1$ 的个数在 $[c,c+k]$ 之间，且至少有一段长度 $\ge c$ 的 $1$ 连续段。

考虑计算总答案，然后去掉重复的贡献。

这里我们以 $0$ 为开头对字符串计数，全 $1$ 串可以特判。

枚举 $0$ 的个数 $i$，即可断环为链，通过容斥 + dp 可以求出至少一段长度 $\ge c$ 的 $1$ 连续段的方案数。

但是会算重。在一个方案中，我们可以以 $i$ 个 $0$ 中任意一个 $0$ 为开头，因此结果除以 $i$ 即可。

但是发现这样仍然是错误的。具体的，可能存在两个 $0$ 作为开头后，形成的字符串仍然相同，但是我们没法重复计算这个的贡献。

更进一步地观察，对于一个 $01$ 串，找出他的最小整周期 $p$，我们只关心把单个周期内 $0$ 作为开头，这样能保证形成的串不同，即关心单个周期内 $0$ 的个数。

于是考虑枚举最小周期 $p$，以及枚举单个周期内 $0$ 的个数。单个周期内的总方案数是容易求的，但不一定保证最小周期一定是 $p$。

继续容斥，容易发现这个容斥是莫比乌斯反演的形式，然后这题就做完了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define pir pair<ll,ll>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
using namespace std;
const ll maxn=3010, mod=1e9+7;
ll n,c,k,f[maxn][maxn],C[maxn][maxn],ans,inv[maxn],res[maxn][maxn];
ll pri[maxn],pr,mu[maxn],b[maxn];
int main(){
	scanf("%lld%lld%lld",&n,&c,&k);
	mu[1]=1;
	for(ll i=2;i<=n;i++){
		if(!b[i]){
			pri[++pr]=i, mu[i]=-1;
		}
		for(ll j=1;j<=pr&&i*pri[j]<=n;j++){
			ll t=i*pri[j]; b[t]=1;
			if(i%pri[j]) mu[t]=-mu[i];
			else break;
		}
	}
	inv[1]=1;
	for(ll i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	C[0][0]=1;
	for(ll i=1;i<=n;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	f[1][0]=f[0][0]=1;
	for(ll i=2;i<=n;i++){
		for(ll j=0;j<i;j++){
			f[i][j]=f[i-1][j];
			if(j){
				f[i][j]=(f[i][j]+f[i-1][j-1])%mod;
				if(j>=c) f[i][j]=(f[i][j]-f[i-c-1][j-c]+mod)%mod;
			}
		}
	}
	if(c+k==n) ans=1, --k;
	for(ll i=n;i;i--)
		if(n%i==0){
			for(ll j=0;j<i;j++)
				if((n/i)*j<=c+k&&(n/i)*j>=c){
					res[i][j]=(C[i-1][j]-f[i][j]+mod)%mod;
					for(ll k=2;i*k<=n;k++)
						res[i*k][j*k]=(res[i*k][j*k]+
						mu[k]*res[i][j]+mod)%mod;
				}
		}
	for(ll i=1;i<=n;i++)
		if(n%i==0){
			for(ll j=0;j<i;j++)
				ans=(ans+res[i][j]*inv[i-j])%mod;
		} printf("%lld",ans);
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

很好的计数题。考场上大脑翻滚，并没有想出解决群中运算不封闭的处理方法。

考虑修改一下题目的定义。合法串定义改为“可以通过 $\texttt S$ 的任何一个循环重构把部分 $0$ 改为 $1$得到”，这样在题目所示的置换群下所有串是封闭的。

考虑使用 $\rm Burnside$ 引理，依次计算每个置换的不动点。那么假设要求解一个循环节长度为 $len$ 的字符串。

如果 $len \le c$，那么只有一种可能——整个串全是 $1$。否则，在循环节中有一个**循环长度至少为 $c$ 的 $1$ 连续段**（也就是把这个串当做一个环）。

正难则反，考虑求出任何一个长度为 $1$ 的连续段长度都 $<c$ 的序列种数。注意到对于不同的询问，$c$ 都是恒定的，所以可以通过某种方式预处理。设 $dp_{n,k}$ 为长度为 $n$ 的**线性序列**，里面放了 $k$ 个 $1$ 且没有长度 $\ge c$ 的 $1$ 的连续段的方案数。

$dp_{n,k}$ 可以通过比较平凡的前缀和优化 $\rm DP$ 解决。

当这个环并不全是 $1$ 的时候，考虑枚举跨过 $n$ 到 $1$ 这条边的 $1$ 的连续段的长度。

这样做到 $O(n^2d(n))$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MOD=1e9+7;
int n,c,k,dp[MAXN][MAXN],pre[MAXN][MAXN],C[MAXN][MAXN];
map<int,int> mp;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int solve(int len) {
	if(mp.count(len)) return mp[len];
	int ans=0;
	if(len<=c) return mp[len]=(c+k==n),(c+k==n);
	ffor(i,0,(c+k)/(n/len)) ans=(ans+C[len][i])%MOD;
	ffor(i,0,c-1) {
		int mul=i+1,rst=len-i-2,res=0;
		ffor(j,i,min((c+k)/(n/len),len-2)) res=(res+dp[rst][j-i])%MOD;
		ans=(ans-res*mul)%MOD;
	}
	return mp[len]=ans,ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>c>>k; ffor(i,0,n) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	dp[0][0]=1,pre[0][0]=1;
	ffor(i,1,n) {
		ffor(k,0,i) dp[i][k]=dp[i-1][k];	
		ffor(k,1,i-1) {
			int lst=i-c-1;
			if(lst>=0) dp[i][k]=(dp[i][k]+pre[i-2][i-k-1]-pre[lst][i-k-1])%MOD;
			else dp[i][k]=(pre[i-2][i-k-1]+dp[i][k])%MOD;
		}
		if(i<c) dp[i][i]++;
		ffor(k,0,i) pre[i][i-k]=(pre[i-1][i-k]+dp[i][k])%MOD;
	}
	int ans=0;
	ffor(i,1,n) ans=(ans+solve(__gcd(n,i)))%MOD;
	ans=ans*qpow(n,MOD-2)%MOD;
	cout<<(ans%MOD+MOD)%MOD<<'\n';	
	return 0;
}
```

---

## 作者：spdarkle (赞：2)

[link](https://www.luogu.com.cn/problem/CF1954F)

计数类 *3100 首次独立过纪念版题解。

首先我们考虑一个去重的问题。貌似针对循环同构去重的问题，只能从循环节上入手。

那么我们考虑设 $dp(d)$ 为 最小循环节长度恰好为 $d$ 不同方案数个数，则答案为：

$$\sum_{d=1}^ndp(d)=\sum_{d|n}\frac{dp(d)}{d}$$

这似乎是一条可行的路。但我们发现确定最小循环节长度是一个较为困难的问题，反而确定存在一个长度为 $d$ 的循环节（直接固定，类似于二项式反演的思想）更为容易。

所以不妨有设 $g(d)$ 为存在长度为 $d$ 的循环节的方案数，则容易有 $g(n)=\sum_{d|n}dp(d)$，因此由莫比乌斯反演我们知道 $dp(n)=\sum_{d|n}\mu(\frac{n}{d})g(d)$。

好了现在让我们来想想 $g$ 的求法。

一个困扰我们的问题是原问题摆在了环上，但幸好我们可以将原题意转化为求解有多少个环状二进制串，满足 $cnt_1\in[c,c+k]$，存在一个全是一的连续段长度大于等于 $c$。

如果说去掉环的限制显然是一个很 naive 的 DP 题，而环的限制本质上还是对同构提出了要求。

我们考虑字符串 $S$ 的循环同构串数量，不妨设 $S_i$ 为 $S$ 从 $i$ 位置开始的循环串。则显然有设 $x$ 为 $S$ 的最小循环节长度，有 $S_i=S_{i+x}$，且 $S_1\sim S_x$ 互不相同。

这告诉我们 $g(d)$ 其实也就是只需要考虑填这个串的 $[1,d]$ 位即可，剩下的就是复制的问题了。

好了，现在我们可以考虑怎么去掉个数限制了。

为了方便统计，我们就强行要求 $S[1]=0$ 吧。我们不妨设 $f_{i,j,0/1}$ 为在 $[1,i]$ 中填写 $j$ 个零，且最后一个零是 $i$，当前是否已经填过长度大于等于 $c$ 的一连续段。

则对于 $S_1\sim S_d$ 两两不同的限制就太简单了，这意味着只考虑 $S[1,d]$，将其作为一个循环串，每个位置开头都不一样，这告诉我们如果我们将强制 $S[1]=0$，则对于任意一个使用了 $t$ 个零的合法串，都恰有 $t-1$ 个与它同构，这告诉我们 $\frac{f_{i,j,0/1}}{j}$ 就是填完 $S[1,i]$，然后 $[i+1,d]$ 全部写 $1$，所产生的贡献。

首先我们进行 $O(n^2)$ 的动态规划求出 $f$。

就有 $f_{i,j,t}\to f_{i+x+1,j,t|[x\ge c]}$，初始 $f_{1,1,0}=1$。

这个转移显然可以使用差分进行优化。

接着我们有 $s_{i,j,t}=\sum_{x\le j}\frac{f_{i,x,t}}{x}$。

然后我们就可以考虑着手求出 $g$ 了。

对于 $g_d$，由于它要复制 $\frac{n}{d}$ 次，我们可以求出其能够填写的零的个数的范围 $[l,r]$，同时枚举最后一个零的位置 $i\in[1,d]$，注意到 $[i+1,d]$ 全部写一，利用 $s$ 进行统计即可。

但是我们需要注意到可能会出现类似于统计 $g(6)$，对于串 `011011` 这种答案。

我们发现这个串是应该属于 $dp(3)$。在这里还多除以了一个 $2$，因此这提示我们可能需要更改一下朴素的莫比乌斯容斥系数。

一个很简便的方法是：将所有的 $d$ 直接化为 $n$，也即直接乘上 $\frac{d}{n}$，这样就去除了这种多除的问题。然后最后算答案的时候 $dp(d)$ 再乘上 $\frac{n}{d}$ 即可。

复杂度 $O(n^2+d^2(n)+\sum_{d|n}d)=O(n^2)$

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1954F)

**题目大意**
> 求有多少长度为 $n$ 的 01 串满足 $s_1\sim s_c=1$，且 $\sum_{i=c+1}^n s_i\le k$，循环同构算同一个串。
> 
> 数据范围：$n\le 3000$。

**思路分析**

先把 $k+c=n$ 的情况特判掉（$k\gets k-1$ 且答案 $+1$ 即可）。

显然 Burnside 引理，但题目中给的串关于循环移位不封闭，我们把限制改成：至少有 $c$ 个连续的 1 且总和 $\le k+c$，显然循环同构去重后答案不变。

我们只要对于每个 $d\mid n$ 求出 $f_d$ 表示满足 $s_i=s_{i+d}$，且满足上述条件的串数，答案就是 $\dfrac 1n\sum f_{\gcd(n,i)}$。

如果 $d>c$ 那么一定是全 1 串，因为 $k+c<n$ 所以不行。

否则我们观察每个长度为 $d$ 的循环节，反面考虑求出：写成环后没有长度 $\ge c$ 的连续 1 段，且 1 的总数不超过 $\left\lfloor\dfrac{k+c}{n/d}\right\rfloor$ 的方案数。

断环成链，枚举左右两侧 1 段长度和，中间的方案只要求 $dp_{i,j}$ 表示长度为 $i$ 的序列，总和不超过 $j$ 且没有长度 $\ge c$ 的连续 1 段。

先求总和恰好为 $j$ 的方案数，转移为 $dp_{i,j}=\sum_{p=0}^{c-1} dp_{i-p-1,j-p}$，边界条件为 $dp_{0,0}\sim dp_{c-1,c-1}=0$，前缀和优化即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3005,MOD=1e9+7;
ll C[MAXN][MAXN],f[MAXN],dp[MAXN][MAXN],s[MAXN][MAXN],ans=0;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
signed main() {
	int n,c,k;
	scanf("%d%d%d",&n,&c,&k),k+=c;
	if(c==n) return puts("1"),0;
	if(k==n) --k,ans+=n;
	for(int i=0;i<=n;++i) {
		if(i<c) dp[i][i]=1;
		for(int j=0;j<=i;++j) {
			if(i>0) {
				dp[i][j]+=s[i-1][j];
				if(i>c&&j>=c) dp[i][j]-=s[i-c-1][j-c];
				dp[i][j]=(dp[i][j]%MOD+MOD)%MOD;
			}
			s[i][j]=dp[i][j];
			if(i&&j) s[i][j]=(s[i][j]+s[i-1][j-1])%MOD;
		}
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) {
		dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
	}
	for(int i=0;i<=n;++i) for(int j=C[i][0]=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	for(int d=1;d<=n;++d) if(n%d==0&&c<d&&k>=(n/d)*c) {
		int q=k/(n/d);
		for(int j=0;j<=q;++j) f[d]+=C[d][j];
		for(int j=0;j<=q&&j<c;++j) {
			if(j>=d-2) f[d]-=j+1;
			else f[d]-=dp[d-j-2][q-j]*(j+1);
		}
		f[d]=(f[d]%MOD+MOD)%MOD;
	}
	for(int i=1;i<=n;++i) ans+=f[__gcd(n,i)];
	ans=(ans%MOD+MOD)*ksm(n)%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

好题选讲讲了这道，用了当时用的题解，写得不好就当乐一乐吧。

## 题目大意

你有一个长度为 $n$ 的字符串，它的前 $c$ 个字符是 $1$，其余字符是 $0$。你可以将不超过 $k$ 个 $0$ 改成 $1$，求能够得到的在循环同构意义下本质不同的字符串数量，对 $10^9+7$ 取模。

$1\le c\le n\le 3000,0\le k\le n-c$。

## 题目分析

稍微将答案形式化一下：计算含有不超过 $c+k$ 个 $1$ ，且存在长度至少为 $c$ 的连续段的本质不同字符串个数。

我们称满足 “含有不超过 $c+k$ 个 $1$ ，且存在长度至少为 $c$ 的连续段” 的字符串为好的字符。而 $f_i$ 表示好的字符串中循环右移 $i$ 位后与原串相等的字符串个数。显然这里循环移位是构成置换群的，根据 Burnside 引理，答案可以表示为：

$$ans=\frac{1}{n}\sum\limits_{i=1}^nf_i$$

$ans$ 就是在好的字符串在循环移位的作用下构成的本质不同子串构成的集合大小。

$n$ 即为循环移位下构成的**置换群大小**。

$i$ 表示字符串中循环位移构成的置换群中的一种**置换**。

$f_i$ 则表示在 $i$ 这种置换下保持不变的元素的个数，和上面的定义符合。

长度为 $n$ 的字符串循环右移 $i$ 位后保持不变的充要条件是 $\forall x\in[1,n]，s[x]=s[(x+p-1)\bmod n+1]$，简单的画一画就能发现这等价于 $s$ 存在长度为 $g=\gcd(n,i)$ 的循环节，所以我们可以转而枚举 $n$ 的因数 $g$，方便之后的计数。先整理答案式子：

$$ans=\frac{1}{n}\sum\limits_{g|n}{ct}_gf_g$$

${ct_g}$ 为 $\gcd(i,n)=g$ 的 $i$ 的个数。

现在只需要求出 $f_g$ 的值就可以了。

显然，字符串的前 $g$ 个字符可以确定一个唯一的字符串。一个好的字符串的前缀应满足 $1$ 的个数 $\le \frac{g(c+k)}{n}$，并且有一段长度至少为 $c$ 的 $1$ 连续段（可以跨过首尾）。第二个限制不好处理，我们考虑正难则反：枚举左右边极长的 $1$ 的长度，中间段的方案数可以简单 $dp$ 预处理：设 $dp_{i,j}$ 表示长度为 $i$，$0$ 的个数为 $j$ ，钦定了最后一位为 $0$ 的方案数，前缀和优化即可 $O(1)$ 转移与计算答案。

复杂度 $O(\sum\limits_{g|n}g^2+n^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =3e3+5,M=4e6+5,inf=(1LL<<31)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int dp[N][N],n,c,k,p[N][N],P[N][N];
inline int get(int x,int l,int r){
	l=max(l,0);
	r=min(r,n);
	if(l>r)return 0;
	if(l)return Red(p[x][r],p[x][l-1]);
	return p[x][r];
}
int K[N];
inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int fac[N],iv[N];
inline void prep(){
	fac[0]=1;
	repn(i)fac[i]=mul(fac[i-1],i);
	iv[n]=INV(fac[n]);
	per(i,n-1,0)iv[i]=mul(iv[i+1],i+1);
}
inline int C(int x,int y){
	return (x<0||y<0||x<y)?0:mul(fac[x],mul(iv[y],iv[x-y]));
}
inline int Get(int len,int r){
	if(len<0)return 0; 
	r=max(r,0);
	return P[r][len];
}
inline void Main(){
	n=read(),c=read(),k=read(),prep();
	//dp[i][j]=\sum dp[i-1][j-k] k\in
	rep(i,0,n)p[0][i]=1;
	dp[0][0]=1;
	repn(i)
		repn(j)
			dp[i][j]=get(i-1,j-c,j-1),p[i][j]=Add(p[i][j-1],dp[i][j]);
	repn(i)P[n][i]=dp[n][i];
	per(i,n-1,0)repn(j)P[i][j]=Add(dp[i][j],P[i+1][j]);
	repn(i)K[gcd(i,n)]++;
	int ans=0;
	repn(i)if(K[i]){
		if(i<=c){
			if(c+k==n)add(ans,K[i]);
		}else {
			int m=min((c+k)/(n/i),i),w=0;//最多 m 个
			rep(j,0,m)add(w,C(i,j));
			rep(l,0,c-1)rep(r,0,c-1-l){
				//cout <<i-l-r-1<<' '<<c+k-l-r<<'\n';
				red(w,Get(i-l-r-1,i-1-m));
			}
			add(ans,mul(K[i],w));
		} 
	}
	cout <<mul(ans,INV(n));
}
signed main(){
	int T=1;
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

先考虑如何描述一个合法 01 串。

- $1$ 的出现次数 $\in [c,c+k]$。
- 存在一段连续的 $1$ 长度 $\ge c$。

我们注意到循环置换得到的 01 串在同一个等价类内，考虑 Burnside 引理。令 $x=(a_2,a_3,\dots,a_n,a_1)$，$G$ 为作用在集合 $S=\{x^i\mid 1\le i\le n\}$ 上的置换群，套用式子有

$$ans=\dfrac1n\sum_{g\in G}|X^g|$$

其中 $X^g$ 表示所有经过置换 $g$ 变换后保持不变，同时满足题目条件的 01 串集合。对于 $g=x^i\in G$，其必然存在长度为 $\gcd(n,i)$ 的循环节。令 $len=\gcd(n,i)$。

先不考虑出现次数的限制，首先满足存在一段连续的 $1$ 长度 $\ge c$。若 $len \le c$，则只有可能是全 $1$，此时 $|X^g|=[c+k=n]$；否则考虑 dp，存在转任意，即总数减去任意极长 $1$ 连续段长度 $\le c-1$ 方案数。令 $f_{n,k}$ 表示长为 $n$，填了 $k$ 个 $0$ 的方案数。有

$$f_{i,j}=\sum_{k=0}^{\min(i-j,c-1)}f_{i-k-1,j-1}$$

即钦定最后 $k$ 位为 $1$，倒数第 $k+1$ 位为 $0$。前缀和优化做到 $\Theta(n^2)$，但是因为我们要求的是环，所以一段前缀和一段后缀拼成的子段无法被考虑到。枚举前缀 $1$ 数量和后缀 $1$ 数量，中间一段即可使用 dp 值。

由于 $\gcd(n,i)\mid n$ 所以对所有 $len\mid n$ 跑上述过程即可。复杂度是跑不满的 $\Theta(n^2d(n))$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;
using umap = unordered_map<int, int>;

const int maxn = 3e3 + 10;
const int mod = 1e9 + 7;
const bool multidata = 0;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

int n, c, m, ans;
umap bk;

int power(int a, int b, int p = mod) {
	int t = 1; a %= p;
	while (b) {
		if (b & 1) t = t * a % p;
		a = a * a % p, b >>= 1;
	}
	return t;
}

int f[maxn][maxn], s[maxn][maxn];
int fac[maxn], ifac[maxn], inv[maxn];

void init() {
	fac[0] = 1; rep(i, 1, maxn - 1) fac[i] = fac[i - 1] * i % mod;
	ifac[maxn - 1] = power(fac[maxn - 1], mod - 2); per(i, maxn - 2, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	rep(i, 1, maxn - 1) inv[i] = fac[i - 1] * ifac[i] % mod;
}

int C(int n, int m) {
	if (n < 0 || n < m || m < 0) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int sum(int l, int r, int k) {
	l = max(l, 0ll);
	return (s[r][k] - (l ? s[l - 1][k] : 0) + mod) % mod;
}

int solve(int len) {
	if (len <= c) return n == c + m;
	int tot = 0, ans = 0, cnt = n / len, L = (c + cnt - 1) / cnt, R = (c + m) / cnt;
	if (L > R) return 0;
	rep(i, L, R) (tot += C(len, i)) %= mod;
	int L0 = len - R, R0 = len - L;
	f[0][0] = s[0][0] = 1;
	rep(i, 1, len) {
		f[i][0] = i < c;
		s[i][0] = s[i - 1][0] + f[i][0];
		rep(k, 1, i) {
			f[i][k] = sum(i - min(i - k, c - 1) - 1, i - 1, k - 1);
			s[i][k] = (s[i - 1][k] + f[i][k]) % mod;
		}
	}
	rep(i, 0, len) rep(j, 1, i) (f[i][j] += f[i][j - 1]) %= mod;
	rep(i, 0, c - 1) {
		rep(j, 0, c - 1 - i) {
			if (i + j > R) continue;
			int l = max(L0 - 2, 0ll), r = min(R0 - 2, len - i - j - 2);
			(ans += f[len - i - j - 2][r] - (l ? f[len - i - j - 2][l - 1] : 0) + mod) %= mod;
		}
	}
	return (tot - ans + mod) % mod;
}

void fake_main() {
	init();
	n = read(), c = read(), m = read();
	per(i, sqrt(n), 1) {
		if (n % i == 0) {
			bk[i] = solve(i);
			if (i * i != n) bk[n / i] = solve(n / i);
		}
	}
	rep(i, 1, n) (ans += bk[__gcd(n, i)]) %= mod;
	write(ans * power(n, mod - 2) % mod), pc('\n');
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
/*
21 6 3
*/
```

---

