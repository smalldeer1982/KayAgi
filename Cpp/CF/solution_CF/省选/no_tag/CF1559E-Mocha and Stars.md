# Mocha and Stars

## 题目描述

Mocha wants to be an astrologer. There are $ n $ stars which can be seen in Zhijiang, and the brightness of the $ i $ -th star is $ a_i $ .

Mocha considers that these $ n $ stars form a constellation, and she uses $ (a_1,a_2,\ldots,a_n) $ to show its state. A state is called mathematical if all of the following three conditions are satisfied:

- For all $ i $ ( $ 1\le i\le n $ ), $ a_i $ is an integer in the range $ [l_i, r_i] $ .
- $ \sum \limits _{i=1} ^ n a_i \le m $ .
- $ \gcd(a_1,a_2,\ldots,a_n)=1 $ .

Here, $ \gcd(a_1,a_2,\ldots,a_n) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ a_1,a_2,\ldots,a_n $ .

Mocha is wondering how many different mathematical states of this constellation exist. Because the answer may be large, you must find it modulo $ 998\,244\,353 $ .

Two states $ (a_1,a_2,\ldots,a_n) $ and $ (b_1,b_2,\ldots,b_n) $ are considered different if there exists $ i $ ( $ 1\le i\le n $ ) such that $ a_i \ne b_i $ .

## 说明/提示

In the first example, there are $ 4 $ different mathematical states of this constellation:

- $ a_1=1 $ , $ a_2=1 $ .
- $ a_1=1 $ , $ a_2=2 $ .
- $ a_1=2 $ , $ a_2=1 $ .
- $ a_1=3 $ , $ a_2=1 $ .

## 样例 #1

### 输入

```
2 4
1 3
1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
5 10
1 10
1 10
1 10
1 10
1 10```

### 输出

```
251```

## 样例 #3

### 输入

```
5 100
1 94
1 96
1 91
4 96
6 97```

### 输出

```
47464146```

# 题解

## 作者：HoshizoraZ (赞：13)

如果只看前两个条件，那么这是一个比较显然的背包问题。

令 $f_{i,j}$ 表示前 $n$ 个数 $a_i$ 总和为 $j$ 的方案数。

那么对于每个 $a_i=l_i \sim r_i$ 均有 

$$f_{i,j}=\sum_{k=l_i}^{r_i} f_{i-1,j-k}$$

当然直接上背包复杂度是 $\mathcal{O}(nm^2)$ 级别的，我们需要把每一个 $i$ 的所有 $f_{i,j}$ 记录一个前缀和。记

$$s_{i,j}=\sum_{k=0}^{j}f_{i,k}$$

**且当 $j<0$ 时 $s_{i,j}=0$。**

那么有可以一次性转移的方程：

$$f_{i,j}=s_{i-1,j-l_i}-s_{i-1,j-r_i-1}$$

时间复杂度降为了 $\mathcal{O}(nm)$。

---------

之后就是最后一个条件：$\gcd(a_1,a_2,...,a_n)=1$。

这可以让人联想到许多数论题目的常见解决办法，比如莫比乌斯反演或者容斥，这里讲讲容斥做法。

设 

$$F(x)=\sum_{a_1=l_1}^{r_1}\sum_{a_2=l_2}^{r_2}...\sum_{a_n=l_n}^{r_n}[\gcd(a_1,a_2,...,a_n)=x]\left[\sum_{i}a_i \le m\right]$$

显然我们最后要求 $F(1)$。

观察到这个式子仍比较麻烦，但是条件转化成 $[x \mid \gcd(a_1,a_2,...,a_n)]$ 的话问题就会好做点。

于是再定义 $G(x)=\sum\limits_{d=1}^{\lfloor\frac{m}{x}\rfloor}F(dx)$，相当于

$$G(x)=\sum_{a_1=l_1}^{r_1}\sum_{a_2=l_2}^{r_2}...\sum_{a_n=l_n}^{r_n}[x \mid \gcd(a_1,a_2,...,a_n)]\left[\sum_{i}a_i \le m\right]$$

然后 $[x \mid \gcd(a_1,a_2,...,a_n)]$ 这个条件就等价于**限制了每个 $a_i$ 都是 $x$ 的倍数**。

那我们在枚举 $a_i$ 的时候直接**强制它是 $x$ 的倍数**，就消去 $\gcd=1$ 的条件，可以直接上背包了。

---------

之后还没完，我们要算的是 $F(1)$，但只求出了 $G(x)$。

观察一下 $G(x)$ 的定义式

$$G(x)=\sum_{d=1}^{\lfloor\frac{m}{x}\rfloor}F(dx)$$

移个项：

$$F(x)=G(x)-\sum_{d=2}^{\lfloor\frac{m}{x}\rfloor}F(dx)$$

那么我们从 $m$ 到 $1$ 倒序枚举 $x$，$G(x)$ 用背包求，且所有的 $F(x)$ 都可以求出来。

在枚举 $x$ 和 $x$ 的倍数这一步骤，时间复杂度为调和级数级别的，大约为 $\mathcal{O}(m \ln m)$。

因此均摊到每个 $x$ 的时间复杂度为 $\mathcal{O}(\ln m)$

对于每个 $G(x)$，我们可以用背包求。枚举 $x$ 的倍数也不怎么方便，所以我们可以将**上下界以及 $m$ 都除掉 $x$**，这样就可以使得 $a_i$ 连续，且减小背包容量，优化时间复杂度。

对于每个 $G(x)$，背包容量可以降为 $\lfloor\frac{m}{x}\rfloor$。

上文说了，$\sum\limits_{i=1}^m\frac{m}{x}=\mathcal{O}(m \ln m)$。

因此该做法总复杂度为 $\mathcal{O}(nm \ln m)$。

说一下写代码时的注意点：

- 前缀和数组的初始值为 $0$。
- 注意方式背包时下标变负数的情况。
- 做除法的时候，注意**下界 $\frac{l_i}{x}$ 要上取整。**
- 取模要取干净。

这道题就这么做完了。具体细节可以看代码：

```cpp
#include <bits/stdc++.h>
#define N 100010
#define MOD 998244353
#define reg register
typedef long long ll;
using namespace std;
 
int n, m, l[N], r[N], dp[N], las[N], ss[N], ans, sss, slas[N];
 
inline int F(int x, int y){		// 上取整
	return x / y + (x % y != 0);
}
 
int main(){
 
	cin >> n >> m;
	for(reg int i = 1; i <= n; i++) cin >> l[i] >> r[i];
	for(reg int d = m; d >= 1; d--){
		for(reg int j = 0; j <= m / d; j++)
			dp[j] = 0, las[j] = 0, slas[j] = 0;
		las[0] = slas[0] = 1;
		for(reg int j = 1; j <= m / d; j++)
			slas[j] = (slas[j - 1] + las[j]);
		for(reg int j = 1; j <= n; j++){
			for(reg int L = m / d; L >= F(l[j], d); L--){
				if(L - r[j] / d > 0) dp[L] = (slas[L - F(l[j], d)] - slas[L - r[j] / d - 1] + MOD) % MOD;
				else dp[L] = slas[L - F(l[j], d)];
			}
			for(reg int j = 0; j <= m / d; j++)
				las[j] = dp[j], dp[j] = 0;
			slas[0] = las[0];
			for(reg int j = 1; j <= m / d; j++)
				slas[j] = (slas[j - 1] + las[j]) % MOD;
		}
		for(reg int j = 0; j <= m / d; j++)
			ss[d] = (ss[d] + las[j]) % MOD;
		for(reg int j = d + d; j <= m; j += d)
			ss[d] = (ss[d] - ss[j] + MOD) % MOD;
	}
	printf("%d\n", ss[1]);
 
	return 0;
}
```

---

## 作者：Qiaoqia (赞：12)

> 求出满足以下条件的整数数组 $a$ 个数
> - 长度为 $n$
> - 和不超过 $m$
> - 最大公约数是 $1$
> - $a_i \in [l_i, r_i]$

如果没有 $\gcd$ 的限制那么就是一个简单背包，容易想到用前缀和优化，时间复杂度就变成了 $nm$。 

主要的问题还是出在这个 $\gcd$ 如何处理，容易想到要用容斥做，可是我却不知道应该怎样去容斥，在分解质因数的思路上花费了很多的时间，但是遗憾的是这是一条死路。  
主要是没有想到一个容斥的小 trick。

在处理 $\gcd$ 为 $x$ 的问题时，可以倒着枚举一个 $i$，设 $ans_i$ 是 $\gcd$ 恰好为 $i$ 的方案数，$f_i$ 为 $\gcd$ 是 $i$ 的倍数的方案数。

那么就可以用 $ans_g = f_g - \sum_{g|i} ans_i$ 来求解。


用这个方法结合原来的背包，先用背包求出 $f$，然后再进行下面的容斥就可以了。 
具体地，设 $f_{i, j}$ 是前 $i$ 个和不超过 $j\times g$ 的方案数，$f_{i, j} = \sum f_{i-1, k}$， $k$ 是枚举之前的和能到这里的，$l$ 和 $r$ 都要除以 $g$ 处理，然后前缀和优化即可。初始化是 $f_{0, i} = 1$，因为是前缀和，每次叠了个 $1$，实际上只有 $f_{0, 0} = 1$ 目标状态是 $f_{n, m/g}$。

但是赛场上我还是遇到了一个小问题改变了我思考的方向，在考虑容斥之前考虑求总数的时候觉得这个复杂度是 $nm^2$ 的无法通过，所以放弃了这个方向的思考，转而去想着分解出来的质数出不出现的问题。  
实际上这个复杂度根本就是 $O(nm \ln m)$ 的，因为除以了 $g$ 之后复杂度变成了调和级数。


```cpp
#include <iostream>
#include <algorithm>
#define int long long
const int N = 55, M = 100005, P = 998244353;
int n, m, l[N], r[N], f[N][M], ans[M];
signed main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> l[i] >> r[i];
	for (int g = m/n; g >= 1; g--) {
		for (int i = 0; i <= n; i++)	
			for (int j = 0; j <= m/g+1; j++) f[i][j] = 0;
		for (int j = 0; j <= m/g+1; j++) f[0][j] = 1;
		for (int i = 1; i <= n; i++) {
			int L = (l[i]+g-1)/g, R = r[i]/g;
			for (int a = L; a <= m/g+1; a++) {
				int cl = std::max(a-R, 0ll), cr = a-L;
				if (cl > cr) f[i][a] = 0;
				else f[i][a] = (f[i-1][cr] - (cl ? f[i-1][cl-1] : 0) + P) % P;
				if (a > 0) f[i][a] = (f[i][a] + f[i][a-1]) % P;
			}
		}
		ans[g] = f[n][m/g];
		for (int i = 2*g; i <= m; i += g) ans[g] = (ans[g] - ans[i] + P) % P;
	}
	std::cout << ans[1];
}
```


---

## 作者：Demoe (赞：7)

### [题目传送门](https://www.luogu.com.cn/problem/CF1559E)

## $\text{Description}$

- 给定 $n$, $m$ 求满足以下条件的数列数量：
- $a_i\in [l_i,r_i](1\le i\le n)$，
- $\sum_{i=1}^na_i\le m$，
- $\gcd(a_1,a_2,...,a_n)=1$，
- 答案对 $998244353$ 取模。

## $\text{Solution}$

~~咋回事啊，前面才出了 You，咋现在又出一道类似的题啊。~~

考虑原式求什么。

先把 $\gcd$ 条件删掉，即为经典 dp 问题，可以 $O(nm)$ 解决。

我们令 $f(a_1,a_2,...,a_n)$ 为当前数列是否满足前两个条件。

答案即为 $\sum\limits_{a_1=l_1}^{r_1}\sum\limits_{a_2=l_2}^{r_2}...\sum\limits_{a_n=l_n}^{r_n}f(a_1,a_2,...,a_n)[\gcd(a_1,a_2,...,a_n)=1]$。

典型的莫反形式。

$\begin{aligned}ans & = \sum\limits_{a_1=l_1}^{r_1}\sum\limits_{a_2=l_2}^{r_2}...\sum\limits_{a_n=l_n}^{r_n}f(a_1,a_2,...,a_n)[\gcd(a_1,a_2,...,a_n)=1] \\ & = \sum\limits_{a_1=l_1}^{r_1}\sum\limits_{a_2=l_2}^{r_2}...\sum\limits_{a_n=l_n}^{r_n}f(a_1,a_2,...,a_n)\sum\limits_{d\mid \gcd(a_1,a_2,...,a_n)}\mu(d)\\ &= \sum\limits_{a_1=l_1}^{r_1}\sum\limits_{a_2=l_2}^{r_2}...\sum\limits_{a_n=l_n}^{r_n}f(a_1,a_2,...,a_n)\sum\limits_{d\mid a_1 \& d\mid a_2 \& ... \& d\mid a_n}\mu(d) \\&= \sum\limits_{d=1}^m\mu(d) \sum\limits_{a_1=\left\lceil \frac{l_1}{d}\right \rceil}^{\left\lfloor \frac{r_1}{d}\right\rfloor}\sum\limits_{a_2\left\lceil \frac{l_2}{d}\right \rceil}^{\left\lfloor \frac{r_2}{d}\right\rfloor}...\sum\limits_{a_n=\left\lceil \frac{l_n}{d}\right \rceil}^{\left\lfloor \frac{r_n}{d}\right\rfloor}f(a_1,a_2,...,a_n)\end{aligned}$

后面那个就是删掉 $\gcd$ 条件的题目，可以 $O(\dfrac{nm}{d})$ 完成。

由调和级数可知，时间复杂度 $O(nm\ln m)$，注意到 $\mu(i)=0$ 时可以不用 dp 能够加速。（事实上如果你 $\mu(i)=0$ 也跑 dp 的话可能 pretest 就 Tle 了。）

~~显然比 D2 简单啊。~~

## $\text{Code}$

```cpp
const int N=1e5+5,mod=998244353;
int n,m,mu[N],l[N],r[N],L[N],R[N],ans,prime[N],cnt,dp[N],f[N];
bool tag[N];

inline void pre(){
	mu[1]=tag[1]=1;
	for(re i=2;i<N;++i){
		if(!tag[i]) prime[++cnt]=i,mu[i]=-1;
		for(re j=1;j<=cnt&&prime[j]*i<N;++j){
			tag[i*prime[j]]=1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]]=-mu[i];
		}
	}
}

// ---------- Mobius ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);rd(m);pre();
	for(re i=1;i<=n;++i) rd(L[i]),rd(R[i]);
	for(re d=1;d<=m;++d)
		if(mu[d]){
			for(re i=1;i<=n;++i) l[i]=(L[i]+d-1)/d,r[i]=R[i]/d;
			int sum=m/d;
			for(re i=0;i<=sum;++i) dp[i]=1;
			for(re i=1;i<=n;++i){
				for(re j=1;j<=sum;++j) f[j]=0;
				for(re j=l[i];j<=sum;++j){
					f[j]=dp[j-l[i]];
					if(j-r[i]-1>=0) f[j]=(f[j]-dp[j-r[i]-1]+mod)%mod;
				}
				dp[0]=0;
				for(re j=1;j<=sum;++j) dp[j]=(dp[j-1]+f[j])%mod;
			}
			ans=(ans+dp[sum]*mu[d])%mod;ans=(ans+mod)%mod;
		}
	wr(ans);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：Leasier (赞：5)

前置芝士：[莫比乌斯反演](https://oi-wiki.org/math/number-theory/mobius/)

~~讲个笑话：赛时我因为去搞 D2 而在最后五秒码完这道题却发现过不了样例，第二天调了三分钟就 AC 了。~~

原式 $= \displaystyle\sum_{a_1 = l_1}^{r_1} \sum_{a_2 = l_2}^{r_2} \cdots \sum_{a_n = l_n}^{r_n} [\sum_{i = 1}^n a_i \leq m \operatorname{and} \gcd(a_1, a_2, \cdots, a_n) = 1]$

$ = \displaystyle\sum_{d = 1}^m \mu(d) \sum_{a_1 = l_1, d\ |\ a_1}^{r_1} \sum_{a_2 = l_2, d\ |\ a_2}^{r_2} \cdots \sum_{a_n = l_n, d\ |\ a_n}^{r_n} [\sum_{i = 1}^n a_i \leq m]$

$ = \displaystyle\sum_{d = 1}^m \mu(d) \sum_{a_1 = \lceil \frac{l_1}{d} \rceil}^{\lfloor \frac{r_1}{d} \rfloor} \sum_{a_2 = \lceil \frac{l_2}{d} \rceil}^{\lfloor \frac{r_2}{d} \rfloor} \cdots \sum_{a_n = \lceil \frac{l_n}{d} \rceil}^{\lfloor \frac{r_n}{d} \rfloor} [\sum_{i = 1}^n a_i \leq \lfloor \frac{m}{d} \rfloor]$

后半部分直接用前缀和优化 dp 维护即可。dp 部分时间复杂度为 $O(\frac{nm}{d})$，于是整体时间复杂度为 $O(nm \ln m)$。

代码：
```cpp
#include <stdio.h>

const int N = 1e5 + 7, M = 50 + 7, mod = 998244353;
int prime[N], mu[N], l[M], r[M], r_[M], sum_[N], sum[N], dp[M][N];
bool p[N];

inline void init(int n){
	int cnt = 0;
	p[0] = p[1] = true;
	mu[1] = 1;
	for (register int i = 2; i <= n; i++){
		if (!p[i]){
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				mu[t] = 0;
				break;
			}
			mu[t] = -mu[i];
		}
	}
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int do_dp(int n, int m){
	int ans = 0;
	for (register int i = 0; i <= m; i++){
		sum_[i] = 1;
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 0; j <= m; j++){
			int t = min(r_[i], j);
			if (i == n) ans = (ans + sum_[t]) % mod;
			sum[j] = sum_[t];
			if (j > 0) sum[j] = (sum[j] + sum[j - 1]) % mod;
		}
		for (register int j = 0; j <= m; j++){
			sum_[j] = sum[j];
		}
	}
	return ans;
}

int main(){
	int n, m, mi, ans = 0;
	scanf("%d %d", &n, &m);
	mi = m + 1;
	init(m);
	for (register int i = 1; i <= n; i++){
		scanf("%d %d", &l[i], &r[i]);
	}
	for (register int i = 1; i <= m; i++){
		int sum = 0, tm = m / i;
		for (register int k = 1; k <= n; k++){
			int tl = (l[k] - 1) / i + 1;
			r_[k] = r[k] / i - tl;
			sum = min(sum + tl, mi);
		}
		if (tm >= sum) ans = ((ans + mu[i] * do_dp(n, tm - sum)) % mod + mod) % mod;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：kradcigam (赞：4)

推广[个人博客](https://www.cnblogs.com/zhaohaikun)，欢迎大家来玩。

题目意思：

> 给定 $n$ 和 $m$，求 $n$ 个数满足以下 $3$ 个条件的方案数（对 $998244353$ 取模）：
>
> 1. $l_i\leq a_i\leq r_i(1\leq i\leq n)$
> 2. $\sum\limits_{i=1}^{n} a_i \leq m$
> 3. $\gcd(a_1,a_2,\cdots,a_n)=1$

考虑对 $\gcd$ 大力容斥，这样就变成了让 $\gcd(a_1,a_2,\cdots,a_n)$ 为某个数的倍数的方案数，因为 $\gcd$ 要为某个数的倍数。所以 $a_i$ 必须为那个数的倍数，我们可以考虑直接除一下。

考虑 $dp$，$f_{i,j}$ 表示前 $i$ 个质数和（除了之后）为 $j$ 的方案数。

求出每个数的合法区间（除来之后的），枚举它，设它为 $k$，转移就是 $f_{i,j}\gets f_{i-1,j-k}$。

最后再提一下，容斥乘的数是 [$\mu$](https://www.cnblogs.com/zhaohaikun/p/13830072.html)。

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define int long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=55,M=1e5+10,MOD=998244353;
int l[N],r[N],ll[N],rr[N],prim[M],cnt,s[M];
bool is[M];
int f[N][M],g[N][M],ans,h[M];
signed main(){
	int n=read(),m=read();
	h[1]=1;
	F(i,2,m){
		if(!is[i]){
			h[i]=-1;
			prim[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*prim[j]<m;j++){
			is[i*prim[j]]=1;
			if(i%prim[j]==0)break;
			h[i*prim[j]]=-h[i];
		}
	}
	F(i,1,n)l[i]=read(),r[i]=read();
	F(_,1,m/n){
		F(i,1,n){
			if(l[i]%_==0)ll[i]=l[i]/_;
			else ll[i]=l[i]/_+1;
			rr[i]=r[i]/_;
		}
		F(i,1,m/_)f[1][i]=0;
		F(i,ll[1],rr[1])f[1][i]=1;
		F(i,2,n){
			F(j,1,m/_)
				s[j]=(s[j-1]+f[i-1][j])%MOD;
			F(j,ll[i],m/_)
				f[i][j]=(s[j-ll[i]]-s[j-min(j-1,rr[i])-1]+MOD)%MOD;
		}
		int s=0;
		F(i,1,m/_)s=(s+f[n][i])%MOD;
		ans=(ans+s*h[_]+MOD)%MOD;
	}cout<<ans;
	return 0;
}
```

- Update：复杂度分析：

	我们把枚举容斥的数设为 $x$，一次 $dp$，和的上限是 $\frac{m}{x}$。所以单次 dp 的复杂度是 $O(n\times\frac{m}{x})$，但 $x$ 会从 $1$ 一直到 $\frac{m}{n}$。
    
    即：
    
    $$
  \begin{aligned}
  &\sum_{x=1}^{\frac{m}{n}} n\times\frac{m}{x}\\
  =&n\times m\sum_{x=1}^{\frac{m}{n}} \frac{1}{x}\\
  =&n\times m\times\log\frac{m}{n}
  \end{aligned}
  $$
    

---

## 作者：constexpr (赞：4)

蒟蒻不会莫反，发一篇dp优化+容斥原理的题解

观察给出的三个条件：
- $\forall i \in [1,n],l_i \leq a_i \leq r_i$
- $\sum^{n}_{i=1}a_i \leq m$
- $\gcd(a_1,a_2,...,a_n)=1$

第三个条件是最棘手的。

故反向考虑求出在满足前两个条件的前提下 $\gcd(a_1,a_2,...,a_n) \neq 1$ 的情况数，再与满足前两个条件的情况数作差就能得到答案。

接下来的问题就是如何快速求出情况数了，先考虑满足前两个条件的情况数。

为了方便，我们将第 $i$ 个数的范围从 $[l_i,r_i]$ 设置为 $[0,r_i-l_i]$ ，同时将 $m$ 减去 $l_i$。

于是就可以转化为如下问题：

>给出不等式 $x_1+x_2+...+x_n \leq m$ 和 $n$ 个限制条件 $x_i \leq b_i$，求不等式的非负整数解组数。$n \leq 50,m \leq 100000$。

显然有一种暴力的背包做法：

设 $dp_{i,j}$ 为前 $i$ 个数确定，和为 $j$ 的情况总数。

假设第 $i+1$ 个数取 $x$，则 $dp_{i+1,j+x} \gets dp_{i+1,j+x}+dp_{i,j}$。

因为每个数可能有多种取值，故进行分组背包即可。

但时间复杂度为 $O(nm^2)$，显然会超时。

此时就要请上我们的第一个主角——dp 优化了！

由于状态数有整整 $5 \times 10^6 $ 个，故需要快速求出 $dp_{i,j}$。

考虑哪些状态对 $dp_{i,j}$ 作出贡献。

不考虑下标为负数的情况，当第 $i$ 个数分别取 $0,1,2,...,r_i-l_i$ 时，对其作出贡献的分别是 $dp_{i-1,j-0},dp_{i-1,j-1},...,dp_{i-1,j-(r_i-l_i)}$。

由于第 $i$ 个数的取值是连续的，故 dp 数组的下标也是连续的。

静态数组求区间和，前缀和维护即可。

设 $s_{i,j}=\sum^j_{k=1}dp_{i,k}$，则转移方程为 :

$dp_{i,j}=s_{i-1,j}-s_{i-1,\max(0,j-(r_i-l_i))}$

时间复杂度 $O(nm)$。

现在还有一个问题：如何求出满足 $\gcd$ 不为 $1$ 的序列个数？

设 $f_i$ 表示 $\gcd$ 为 $i$ 的序列个数，$g_i$ 表示 $\sum^m_{j=1}[i|j]f_i$

考虑用同样的方法快速求出 $g$ 数组。

求 $g_i$ 时，由于所有数的 $\gcd$ 为 $i$ 的倍数，故每个数都是 $i$ 的倍数。

这样，每个数的取值形成了等差数列。进行以下几条操作，即可转化为之前的问题。

- $\forall j \in [1,n],l_j \gets \left\lceil \frac{l_j}{i} \right\rceil,r_j \gets \left\lfloor \frac{r_j}{i} \right\rfloor$
- $m \gets \left\lfloor \frac{m}{i} \right\rfloor$

即可再 $O(nlogn)$ 调和级数复杂度下求出 $g$ 数组。

知道了 $g$ 数组，那么 $f$ 数组的求值也不难了。

通过容斥原理，不难得出 $f_i=g_i-g_{i \times 2}-g_{i \times 3}-...$

也是调和级数的复杂度。

最后的 $f_1$ 即为答案。

代码 ~~（不要在意码风和变量名）~~

```cpp
#include <cstdio>
#include <cstring>
const long long suyanxu=998244353;
int n,m,sumq,l[60],r[60];
long long ans,f[100010],g[100010],sum[100010],mem[100010];
bool tag=true;
inline int min(int x,int y){
	return x<y?x:y;
}
int main(){
	scanf("%d %d",&n,&m);
	sumq=m;
	for(register int i=1;!(i>n);++i)scanf("%d %d",&l[i],&r[i]),sumq-=l[i];
	//first use of dp:ai>m
	f[0]=1;
	for(register int i=1;i<=n;++i){
		for(register int j=0;j<=sumq;++j)g[j]=sum[j]=0;
		for(register int j=1;j<=sumq+1;j++)sum[j]=f[j-1]+sum[j-1],sum[j]%=suyanxu;
		for(register int j=0;j<=sumq;j++)g[j]=(sum[j+1]-sum[j-min(r[i]-l[i],j)]+suyanxu)%suyanxu;
        for(register int j=0;j<=sumq;++j)f[j]=g[j];
	}
	for(register int i=0;!(i>sumq);++i)ans+=f[i],ans%=suyanxu;
	for(register int i=m;i>1;--i){
		sumq=m/i,tag=true;
		for(register int j=1;j<=n;++j)sumq-=(l[j]-1)/i+1;
		for(register int j=1;!(j>sumq);++j)f[j]=0;
		for(register int j=1;j<=n;++j)if((l[j]-1)/i+1>r[j]/i)tag=false;
		if(!tag)continue;
		f[0]=1;
		for(register int k=1;k<=n;++k){
		    for(register int j=0;j<=sumq;++j)g[j]=sum[j]=0;
		    for(register int j=1;j<=sumq+1;j++)sum[j]=f[j-1]+sum[j-1],sum[j]%=suyanxu;
		    for(register int j=0;j<=sumq;j++)g[j]=(sum[j+1]-sum[j-min(r[k]/i-((l[k]-1)/i+1),j)]+suyanxu)%suyanxu;
            for(register int j=0;j<=sumq;++j)f[j]=g[j];
		}
		for(register int j=0;j<=sumq;++j)mem[i]+=f[j],mem[i]%=suyanxu;
		for(register int j=2;i*j<=m;++j)mem[i]+=suyanxu-mem[i*j],mem[i]%=suyanxu;
		ans+=suyanxu-mem[i],ans%=suyanxu;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：do_while_true (赞：3)

莫比乌斯反演的另外一种形式：

如果有：
$$
f(n)=\sum_{n|d}g(d)
$$
则有：
$$
g(n)=\sum_{n|d}\mu(\frac{d}{n})f(d)
$$
这里的 $d$ 通常是小于等于一个界限，也就是题目中所给定的 "$n$"。

特别地，当 $n=1$ 时，$g(1)=\sum \mu(d)f(d)$，也可以理解为容斥系数为 $\mu$ 的容斥。

--- 

对第三个条件进行莫比乌斯反演，得：
$$
ans=\sum_{d=1}^m \mu(d)f(d)
$$
其中 $f(d)$ 为 $\gcd$ 为 $d$ 的倍数时的答案。

对于 $f(d)$，每次可以做一下背包，用前缀和优化易做到 $\mathcal{O}(\frac{nm}{d})$​，总时间复杂度就是 $\mathcal{O}(nm\log nm)$，注意到 $\mu(d)$ 为 $0$ 的时候不用跑背包，所以这个远远跑不满。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#define int long long
#define mp std::make_pair
typedef long long ll;
const ll mod = 998244353;
void cAdd(ll &x, ll y) { x = (x + y >= mod) ? (x + y - mod) : (x + y); }
ll Add(ll x, ll y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
ll Mod(ll x) { return (x+mod)%mod; }
typedef std::pair<int, int> pii; 
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 500010;
int n, m, L[N], R[N], l[N], r[N];
int ct, prime[N], mu[N];
bool vis[N];
void pre() {
	vis[1] = 1; mu[1] = 1;
	for(int i = 2; i <= 500000; ++i) {
		if(!vis[i]) {
			prime[++ct] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= ct && i * prime[j] <= 500000; ++j) {
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0) mu[i * prime[j]] = 0;
			else mu[i * prime[j]] = mu[i] * mu[prime[j]];
			if(i % prime[j] == 0) break;
		}
	}
}
ll f[N], g[N], ans;
signed main() {
	pre();
	read(n); read(m);
	for(int i = 1; i <= n; ++i) read(L[i]), read(R[i]);
	for(int d = 1; d <= m; ++d) {
		if(!mu[d]) continue ;
		for(int i = 1; i <= n; ++i) l[i] = (L[i]+d-1)/d, r[i] = R[i]/d;
		int s = m/d;
		for(int i = 0; i <= s; ++i) g[i] = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= s; ++j) f[j] = 0;
			for(int j = l[i]; j <= s; ++j)
				f[j] = Add(g[j-l[i]], (j>=r[i]+1)?Mod(-g[j-r[i]-1]):0);
			g[0] = 0;
			for(int j = 1; j <= s; ++j)	g[j] = Add(g[j-1], f[j]);
		}
		ans = Add(ans, Mod(mu[d] * g[s] % mod));
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：_lbw_ (赞：3)

题意：

求满足以下条件长度为 $n$ 的序列 $a$ 个数

- $\sum\limits_{i=1}^na_i\leq m$

- $\forall1\leq k\leq n,a_k\in[l_k,r_k]$

- $\gcd(a_1,a_2,\dots,a_n)=1$

题解：

首先有这个 $\gcd$ 不好做，考虑莫比乌斯反演。

设 $T_k$ 表示满足前两个条件并且 $a$ 全为 $k$ 的倍数的方案数。

于是变成求 $1\leq k\leq m,\mu(k)*T_k$。

考虑如何快速求出 $T_k$，因为均为 $k$ 的倍数，先将 $l_i,r_i,m$ 均除以 $k$，就可以把倍数条件去掉。

然后限制就只剩前两问了，发现每个 $a_i$ 都小于 $m/k$，所以若求 $T_k$ 复杂度为 $\mathcal{O}(\frac{nm}{k}\times f(\log\frac{m}{k}))$ 的话，实际复杂度就是 $\mathcal{O}(nmf(\log m)\ln m)$。

接着思考，剩下似乎变成了一个背包问题，每次背包必须是$\mathcal{O}(m)$ 左右，但是直接做枚举 $a_k\in[l_k,r_k]$ 背包是 $\mathcal{O}(m^2)$ 的

但只要在每次背包做完后前缀和一下就可以做到 $\mathcal{O}(m)$ 了

复杂度 $\mathcal{O}(nm\ln m)$

题码：

```cpp
const int maxn = 1e5+5;
ll n,m,l[maxn],r[maxn],p[maxn+10],mu[maxn+10],_l[maxn],_r[maxn],_m,ans;
bool v[maxn+10];ll dp[maxn],sum[maxn];
inline void init(){
    v[1]=mu[1]=1;
    int cnt=0;F(i,2,_m){
        if(!v[i])p[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*p[j]<=_m;++j){
            v[i*p[j]]=1;
            if(i%p[j])mu[i*p[j]]=-mu[i];
            else{mu[i*p[j]]=0;break;}
        }
    }
}
int main(){
	n=read();_m=read();init();
	F(i,1,n)_l[i]=read(),_r[i]=read();
	F(_,1,_m){
		if(!mu[_])continue;
		m=_m/_;F(i,1,n)l[i]=ceil(1.0*_l[i]/_),r[i]=_r[i]/_;
		F(i,1,n)if(l[i]>r[i])goto orz;
		F(j,0,m)sum[j]=1;
		F(i,1,n){
			F(j,0,m)dp[j]=0;F(j,l[i],r[i])dp[j]=sum[j-l[i]];
			F(j,r[i]+1,m)dp[j]=(sum[j-l[i]]-sum[j-r[i]-1]+cht)%cht;
			sum[0]=dp[0];F(j,1,m)sum[j]=(sum[j-1]+dp[j])%cht;
		}
		ans=(ans+mu[_]*sum[m])%cht;orz:;
	}
	cout<<(ans+cht)%cht;
	return 0;
}
```


---

## 作者：5ab_juruo (赞：2)

当时考场上看到 D2，啊不会啊，怎么办啊。然后去看了一眼 announcement：请阅读所有的题面。好，果断开 E，然后就搞出来了。

赛后讨论，人均认为 D2 比 E 难。

## 题解

题意：求满足以下条件的序列 $a$ 的个数：

- 长度为 $n$，每一项都是正整数；
- $l_i\le a_i\le r_i$；
- $\sum a_i\le m$；
- $\gcd\{a_1,a_2,\cdots,a_n\}=1$。

答案对 $998244353$ 取模。

---

注意到前三个条件很好满足，就是一个简单的 DP，而 $\gcd$ 无法直接处理，考虑容斥。

令 $f_i$ 为序列 $a$ 满足 $\gcd\{a_1,a_2,\cdots,a_n\}\ge i$ 时的答案，联系莫比乌斯函数为容斥系数的性质，可以得到答案就是 $\sum \limits_{i=1}^m\mu(i)f_i$。

注意到当 $\gcd\{a_1,a_2,\cdots,a_n\}\ge i$ 的时候，可以 $a_i\leftarrow \dfrac{a_i}{i}$，此时值域满足 $m^\prime=\left\lfloor\dfrac{m}{i}\right\rfloor$，单次 DP 的复杂度就变成 $\mathcal{O}\left(n\left\lfloor\dfrac{m}{i}\right\rfloor\right)$。对于每个 $i$ 都进行一次 DP，整体复杂度即为 $\mathcal{O}(nm\log m)$，可以通过。

赛时写的丑代码，~~莫比乌斯函数线性筛还是贺的~~:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int max_n = 50, max_m = 100000, max_pr = 15000, mod = 998244353;

int l[max_n], r[max_n], vis[max_m+1], prime[max_pr], n, m;
ll pf[max_n+1][max_m+2], dp[max_n+1][max_m+2];

inline int cdiv(int a, int b) { return a / b + ((a%b)? 1:0); }
inline int my_max(int a, int b) { return (a > b)? a:b; }

int mu[max_m];

void Mobius(int n)
{
	mu[1]=1;
	prime[0]=0;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			prime[++prime[0]]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=prime[0]&&i<=n/prime[j];j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
}

ll ans(int f)
{
	pf[0][0] = 0;
	for (int i = 0; i <= m / f; i++)
		pf[0][i+1] = 1;
	
	for (int i = 0, pl, pr; i < n; i++)
	{
		pl = cdiv(l[i], f), pr = r[i] / f;
		for (int j = 0; j <= pl; j++)
			pf[i+1][j] = 0;
		for (int j = pl; j <= m / f; j++)
		{
			dp[i+1][j+1] = (pf[i][j-pl+1] - pf[i][my_max(0, j-pr)] + mod) % mod;
			pf[i+1][j+1] = (pf[i+1][j] + dp[i+1][j+1]) % mod;
			
		//	cerr << "dp[" << i << "][" << j << "] = " << dp[i+1][j+1] << endl;
		}
	}
	
//	cerr << f << " " << n << " " << m / f << " " << dp[n][(m/f)+1] << endl;
	
	return pf[n][(m/f)+1];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	ll anss = 0;
	
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> l[i] >> r[i];
	
	Mobius(m);
	for (int i = 1; i <= m; i++)
		anss = (anss + ans(i) * mu[i]) % mod;
	
	cout << (anss + mod) % mod << endl;
	
	return 0;
}
```

---

## 作者：FjswYuzu (赞：0)

套路地枚举 $\gcd$ 进行莫比乌斯反演。修正 $m$ 至 $m'$ 以及每个数的取值范围 $[l_i',r_i']$。注意到我们现在要处理的是这样一个问题：给定每个整数的取值范围 $[l_i',r_i']$，询问有多少种方案使得所有数的和小于 $m'$。

用多项式考虑。发现对于数 $i$，对于 $j \in [l_i',r_i']$，第 $j$ 项的系数为 $1$。于是这个问题就变得很特殊，对于答案的多项式相乘，新的答案多项式的某一项是之前的多项式的某一段连续的项系数之和。考虑 dp。定义 $dp_i$ 为选的数和为 $i$ 的方案数，注意到上面的东西，我们可以用前缀和优化转移，最后统计答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=998244353;
LL cnt,prime[30005],mu[100005],n,l[55],r[55];
bool vis[100005];
void shai(LL up)
{
	mu[1]=1;
	for(LL i=2;i<=up;++i)
	{
		if(!vis[i])	mu[i]=MOD-1,prime[++cnt]=i;
		for(LL j=1;j<=cnt && prime[j]*i<=up;++j)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)	break;
			mu[i*prime[j]]=MOD-mu[i];
		}
	}
}
LL dp[100005],sum[100005],m;
int main(){
	shai(100000);
	scanf("%lld %lld",&n,&m);
	for(LL i=1;i<=n;++i)	scanf("%lld %lld",&l[i],&r[i]);
	LL ans=0;
	for(LL i=1;i<=m;++i)
	{
		if(!mu[i])	continue;
		LL up=m/i;
		LL st=0;
		for(LL j=1;j<=up;++j)	dp[j]=0;
		for(LL j=1;j<=n;++j)
		{
			LL L=(l[j]+i-1)/i,R=r[j]/i;
			L=max(L,1ll);
			if(L>R)	goto fail;
			if(j==1)
			{
				for(LL k=1;k<=up;k++)	sum[k]=0;
				for(LL k=L;k<=R;k++)	sum[k]=1;
				for(LL k=2;k<=up;k++)	(sum[k]+=sum[k-1])%=MOD;
			}
			else
			{
				for(LL k=1;k<=up;k++)	dp[k]=sum[max(0ll,k-L)]-sum[max(0ll,k-R-1)];
				for(LL k=1;k<=up;k++)	sum[k]=0;
				for(LL k=1;k<=up;k++)	sum[k]=(sum[k-1]+dp[k])%MOD;
			}
		}
		for(LL j=0;j<=up;++j)	(st+=dp[j])%=MOD;
		ans=(ans+mu[i]*st%MOD)%MOD;
		fail:;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：shao0320 (赞：0)

# CF1559E Mocha and Stars

~~考场上过了这个题结果前缀和写挂导致FST~~

考虑枚举最后的 **公因数** 然后进行容斥。

设 $F(i,j,k)$ 表示枚举的公因数为 $i$ ，目前已经考虑了前 $j$ 个数，加起来的总和是 $i\times k$ 的方案数。

由于 $j$ 不大，$k$ 的总和也是一个调和级数，因此可以通过背包+前缀和在 $O(nm\ln m)$ 的时间复杂度内求出 $F$ （实际上我们也只需要对于每个 $i$ 求出 $\sum_{k} F(i,n,k)$ 即可）。

设 $g(i)$ 表示 $\gcd$ 为 $i$ 的方案数，$f(i)$ 表示存在公因数为 $i$ 的方案数，这个显然就是莫比乌斯反演的形式了，那我们只想知道 $f(1)$ ，因此答案就是

$$
\sum_{i=1}^{n} g(i)\mu(i)
$$


---

## 作者：meyi (赞：0)

定义 $\text{fac}(k)$ 为正整数 $k$ 的质因子个数，$\text{dp}(k)$ 表示满足前两条限制，且 $\gcd$ 为 $k$ 的倍数的方案数，利用容斥原理可得答案为 $\sum\limits_{k\text{的每个质因子只出现一次}}(-1)^{\text{fac}(k)}\text{dp}(k)$。

详细说一下 dp 部分，设 $f_{i,j,k}$ 为 $\gcd$ 为 $i$，取到第 $j$ 件物品，总重量为 $k$（显然 $k$ 为 $i$ 的倍数） 的方案数，容易发现这是一个背包问题，那么状态转移方程为 $f_{i,j,k}=\sum\limits_{p=\lceil \frac{l_j}{i}\rceil\times i}^{\lfloor \frac{r_j}{i}\rfloor\times i}f_{i,j-1,k-p}$。

直接枚举 $p$ 显然会 TLE，使用前缀和优化，令 $pre_{i,j,k}=\sum\limits_{p=0}^kf_{i,j,k}$，那么$f_{i,j,k}=pre_{i,j-1,k-\lceil \frac{l_{j-1}}{i}\rceil\times i}-pre_{i,j-1,k-\lfloor \frac{r_{j-1}}{i}\rfloor\times i-1}$。根据定义可得 $\text{dp}(i)=pre_{i,n,m}$。

利用调和级数可以计算出时间复杂度为 $O(nm\ln m)$。$i$ 这一维不用实际开数组，注意清空即可，于是空间复杂度为 $O(nm)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define DEBUG(k...) fprintf(stderr,k)
typedef long long ll;
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,true:false;}
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,true:false;}
const int maxm=61,maxn=1e5+10,mod=998244353;
struct modint{
	int val;
	inline modint(int val_=0):val(val_){}
	inline modint &operator=(int val_){return val=val_,*this;}
	inline modint &operator+=(const modint &k){return val=val+k.val>=mod?val+k.val-mod:val+k.val,*this;}
	inline modint &operator-=(const modint &k){return val=val-k.val<0?val-k.val+mod:val-k.val,*this;}
    inline modint &operator*=(const modint &k){return val=1ll*val*k.val%mod,*this;}
    inline modint &operator^=(int k){
        modint ret=1,tmp=*this;
        for(;k;k>>=1,tmp*=tmp)if(k&1)ret*=tmp;
        return val=ret.val,*this;
    }
    inline modint &operator/=(modint k){return *this*=(k^=mod-2);}
    inline modint &operator+=(int k){return val=val+k>=mod?val+k-mod:val+k,*this;}
    inline modint &operator-=(int k){return val=val<k?val-k+mod:val-k,*this;}
    inline modint &operator*=(int k){return val=1ll*val*k%mod,*this;}
    inline modint &operator/=(int k){return *this*=((modint(k))^=mod-2);}
    template<class T>friend modint operator+(modint a,T b){return a+=b;}
    template<class T>friend modint operator-(modint a,T b){return a-=b;}
    template<class T>friend modint operator*(modint a,T b){return a*=b;}
    template<class T>friend modint operator/(modint a,T b){return a/=b;}
    friend modint operator^(modint a,int b){return a^=b;}
    friend bool operator==(modint a,int b){return a.val==b;}
    friend bool operator!=(modint a,int b){return a.val!=b;}
    inline bool operator!(){return !val;}
    inline modint operator-(){return val?mod-val:0;}
    inline modint &operator++(int){return *this+=1;}
};
using mi=modint;
vector<int>fac[maxn];
mi ans,f[maxm][maxn],pre[maxm][maxn];
inline mi query(int id,int l,int r,int k){
	return pre[id-1][r]-(l>=k?pre[id-1][l-k]:0);
}
int l[maxn],m,n,r[maxn];
bool vis[maxn];
int main(){
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=n;++i)scanf("%d%d",l+i,r+i);
	for(ri i=2;i<=m;++i)
		if(!fac[i].size())
			for(ri j=i;j<=m;j+=i){
				fac[j].push_back(i);
				if((j/i)%i==0)vis[j]=true;
			}
	ri mx=m/n;
	for(ri i=1;i<=mx;++i)
		if(!vis[i]){
			f[0][0]=pre[0][0]=1;
			for(ri j=i;j<=m;j+=i)f[0][j]=0,pre[0][j]=pre[0][j-i]+f[0][j];
			for(ri j=1;j<=n;++j){
				ri ll=((l[j]+i-1)/i)*i,rr=(r[j]/i)*i;
				for(ri k=0;k<ll;k+=i)f[j][k]=pre[j][k]=0;
				for(ri k=ll;k<=m;k+=i){
					f[j][k]=query(j,k-rr,k-ll,i);
					pre[j][k]=pre[j][k-i]+f[j][k];
				}
			}
			if(fac[i].size()&1)ans-=pre[n][(m/i)*i];
			else ans+=pre[n][(m/i)*i];
		}
	printf("%d",ans);
	return 0;
}
```


---

