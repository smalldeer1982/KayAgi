# Shohag Loves Pebae

## 题目描述

# Shohag Loves Pebae


Shohag 有一棵有 $ n $ 个节点的树。

Pebae 有一个整数 $ m $。 她想给每个节点赋一个值--一个从 $ 1 $ 到 $ m $ 的整数。 所以她要求 Shohag 计算出，模数为 $ 998\,244\,353 $ 的赋值中，满足以下条件的赋值个数：

- 对于每一对 $ 1 \le u \lt v \le n $ ，从 $ u $ 到 $ v $ 的唯一简单路径中节点值的 [最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) 不能被路径中的节点数整除。
- 从 $ 1 $ 到 $ n $ 的所有节点值的[最大公约数（GCD）](https://en.wikipedia.org/wiki/Greatest_common_divisor) 是 $ 1 $ 。

但这个问题对 Shohag 来说太难了。因为 Shohag 喜欢 Pebae，所以他必须解决这个问题。请救救 Shohag！

## 说明/提示

样例一中，有效赋值是 $ [1, 1, 1, 1, 1] $ 和 $ [1, 1, 1, 1, 5] $ 。

样例二中，有效赋值是 $ [1, 1] $ , $ [1, 3] $ , $ [1, 5] $ , $ [3, 1] $ , $ [3, 5] $ , $ [5, 1] $ 和 $ [5, 3] $ 。

## 样例 #1

### 输入

```
6 6
1 2
2 3
3 4
4 5
3 6```

### 输出

```
2```

## 样例 #2

### 输入

```
2 5
1 2```

### 输出

```
7```

## 样例 #3

### 输入

```
12 69
3 5
1 4
2 3
4 5
5 6
8 9
7 3
4 8
9 10
1 11
12 1```

### 输出

```
444144548```

# 题解

## 作者：ForgotMe (赞：2)

完全没想到 cf 有一天会出筛法，更没想到自己唐的以为出题人有高明的 $m^{3/4}$ 的做法，所以 $\mathcal{O}(\frac{m}{\ln m})$ 肯定会被卡。实际上在之前确实有出题人拿 $\mathcal{O}(\frac{m}{(\ln m)^2})$ 的 std 放 $10^{10}$，[CTT 2022 Day3 T3](https://www.luogu.com.cn/article/38vaqpk8)。

下面先规定几个记号：

- $\pi(n)：1\sim n$ 中的质数个数。
- $\operatorname{minp}(x)$ 表示 $x$ 的最小质因子。
- $f_{M,lim}$ 表示 $\sum_{i=1}^M [\operatorname{minp}(i)>lim]$。

先来讲讲如何过题。首先题目中的限制条件完全是为了套个皮而已，求出经过点 $i$ 的最长链所含点数，设为 $h_i$，那么每个点的点权 $a_i$ 的限制转化为 $\operatorname{minp}(a_i)> h_i$。然后还有一个 $\gcd =1$ 的限制，这个比较好解决，直接莫比乌斯反演即可。记 $mx=\max_{i=1}^n h_i$，那么答案为

$$
\sum_{d=1}^m \mu(d)[\operatorname{minp}(d)>mx]\prod_{i=1}^n f_{\lfloor\frac{m}{d}\rfloor,h_i}
$$

首先对 $d$ 整除分块，那么本题的难点就来了，合法的 $d$ 已经后面的 $f$ 都含有一个 $\operatorname{minp}$ 的限制，这个东西非常讨厌，似乎并没有什么非常好的解决手段。如果你对 min25 块筛非常熟悉的话，其实这就是块筛过程中的中间值！

设 $dp_{n,p}$ 表示 $1\sim n$ 内满足 $\operatorname{minp}(i)>p$ 或者 $i$ 本身就是质数的 $i$ 的个数，这是经典的 min25 块筛定义。实际上，这个 dp 在几年前就已经出现过了，见 https://www.luogu.com.cn/problem/P7571 。不熟悉的同学可以去学习一下。其转移类似于 min25 筛第一部分的 dp。

考虑如何筛 $\mu(d)[\operatorname{minp}(d)>mx]$ 的前缀和，实际上只需要将上面的 dp 执行到最后一个小于等于 $mx$ 的质数即可，然后将小于等于 $mx$ 的质数对应的贡献减去即可。

同样的对于 $f$ 也可以这么做，把每个 $f$ 当作一次询问离线下来，当 min25 块筛 dp 到其对应的质数限制时把询问拿出来回答就行。可是这里有 $n\sqrt{m}$ 个询问，暴力做肯定就 t 了。

注意到 $h_i$ 有一个很好的性质，那就是 $h_i\in[\frac{mx}{2},mx]$，因为距离一个点最远的点就是直径的两端。

那么对于 $mx\ge 2\sqrt{m}$ 的情况，此时 $h_i\ge \sqrt{m}$，$\ge \sqrt{m}$ 的质数都被 ban 了，那不就是只能选 $>\sqrt{m}$ 的质数吗？同时发现反演已经不必要了，直接把每个点能选的大质数的个数乘起来就是答案，此时 gcd 必然为 $1$，注意要减去同时选相同的大质数的情况。而对于小于 $2\sqrt{m}$ 的情况也很好处理，考虑对 $h_i$ 找到最后一个小于等于 $h_i$ 的质数，然后把询问放入这个桶里，那么可以发现最多有 $\frac{2\sqrt{m}}{\ln m}$ 种不同的询问。算一下复杂度，每个询问要花费 $\mathcal{O}(\sqrt{m})$ 的时间，那么复杂度就是 $\mathcal{O}(\frac{m}{\ln m})$ 吗？其实算少了，还有一个快速幂的复杂度，真正的复杂度是 $\mathcal{O}(\frac{m\log n}{\ln m})$。看上去似乎非常的不靠谱，但是令人吃惊的是，这个玩意过题了，而且跑的还挺快，不需要什么卡常，正常写就能轻松过题。让我们再仔细看看复杂度，实际上那个 $\log n$ 估计大了，因为是 qkpow 的指数之和为 $n$，实际上复杂度或许应该看为 $\mathcal{O}(\dfrac{m\log (\frac{n}{\sqrt{m}})}{\ln m})$。

放个代码：https://www.luogu.com.cn/paste/369f5l4r 。

可以再给力一点吗？可以的！

考虑对于 $mx\le 2m^{\frac{1}{4}}$ 情况，使用块筛，也就是上面的做法，此时的复杂度是 $\mathcal{O}(\frac{m^{\frac{3}{4}}\log n}{\log m})$。

对于 $2m^{\frac{1}{2}}>mx> 2m^{\frac{1}{4}}$，注意到整除分块当 $\frac{m}{d}\le m^{\frac{1}{2}}$ 时，此时 $f_{\frac{m}{d},h_i}=\pi(\frac{m}{d})-\pi(h_i)+1$，可以直接算，而对于 $d\le \sqrt{m}$ 的情况，此时合法的 $d$（$\operatorname{minp}(d)> mx$）只有 $\frac{\sqrt{m}}{\ln m}$ 个（只能取质数），而询问的种数同样只有 $\frac{\sqrt{m}}{\ln m}$ 个，同样的使用块筛解决问题，那么就可以在 $\mathcal{O}(\dfrac{m\log (\frac{n}{\sqrt{m}})}{(\ln m)^2}+\dfrac{m}{\ln m})$ 的复杂度内解决问题。

---

## 作者：Otomachi_Una_ (赞：1)

我们先不管 $\gcd(a_{1\sim n})=1$ 这个限制。

注意到 $u<v$，$node(u\sim v)\nmid lcm(u\sim v)$ 的本质。我们可以仅考虑所有长度为质数的路径。这是因为如果合数长度合法，我们随便拿出一个其的质因子 $p$，总能在 $u\sim v$ 路径上找到 $p$ 的倍数，这也会导致不合法。

我们可以通过简单 dp 对每个点 $x$ 算出包含 $x$ 的最长路径长度 $f_x$。那么对每个 $x$ 的限制其实是相对独立的，即 $a_x$ 不存在小于等于 $f_x$ 的质因子。

我们可以考虑对每个 $i=1\sim n$ 计算 $1\sim m$ 当中有多少个数的最小质因子 $> i$，这样就完成了计算。

即，我们需要计算每个 $i=1\sim n$，$1\sim m$ 当中有多少个数最小质因子恰为 $i$。

我是个菜狗，不会任何筛子。但是我的板子库里面有 $\operatorname{soft-}O(m^{3/4})$ 时间内求出每个 $i$，$\pi(\dfrac mi)$。考虑怎么解。

根据 D2T1 的套路。我们可以把最大的质因子当作一个变量。我们可以直接暴力搜索除了最大质因子之外的因子，然后我们预处理出来了 $\pi(\dfrac mi)$ 可以这个 $O(1)$ 算出有最大质因子的可能性。

我们现在考虑 $\gcd=1$ 这个限制。套路地枚举 $g=\gcd$，并且钦定每个 $a_i$ 都是 $g$ 的倍数。需要注意的是如果 $g$ 最小质因子比 $\max f$ 还要小那么答案就是 $0$。否则答案就是 $m'=\dfrac mg$ 时的答案。

整除分块，我们只有 $O(\sqrt m)$ 个 $m'$ 需要计算。复杂度差不多也是 $O(\operatorname{can pass})$。

考虑怎么计算区间 $[l,r]$ 内，最小质因子 $>K$ 的 $x$，$\mu(x)$ 的和。

同样套用 D2T1 套路，由于 $l-1,r$ 都是形如 $\dfrac{m}{i}$ 的。仍然把最大质因子当作变量即可。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2039G)

**题目大意**

> 给定一棵 $n$ 个点的树，给每个点赋 $[1,m]$ 的权值，使得每条路径的长度都不是点权 $\mathrm{LCM}$ 的因数，且所有点权互质，求方案数。
>
> 数据范围：$n\le 10^6,m\le 10^9$。

**思路分析**

观察题目的限制，实际上就是要求 $u$ 的点权的最小质因子大于 $u$ 的最长路长度。

不妨设最长路长度为 $h_u$，那么方案数就是 $\prod f_{m,h_u}$，其中 $f_{i,j}$ 表示 $[1,i]$ 中最小质因子 $>j$ 的数个数，做一个类似 Min25 筛的过程，只处理到 $p_k\le j$ 的部分即可。

但是这样无法满足点权互质的限制，莫比乌斯反演得到方案数为 $\sum_d\mu(d)\prod f_{m/d,h_u}$。

很显然整除分块，那么我们要算 $\mu(d)$ 的区间和且要求 $d$ 的最小质因子 $>\max h_u$，这也是类似地仿照 Min25 筛的过程解决即可。

然后我们要求出所有 $f_{m/d,h_u}$，此时有 $\mathcal O(n\sqrt m)$ 组询问，直接计算肯定无法通过。

注意到根据直径的性质 $h_u\ge \dfrac 12\max h$，所以当 $\max h\ge 2\sqrt m$ 的时候，所有 $h_u\ge \sqrt m$，那么 $a_u$ 不可能是合数，只可能是 $1$ 或质数，且互质的条件变成不能同时填某个质数，这是容易解决的。

所以我们只要处理 $\max h<2\sqrt m$ 的情况，此时 $h_u\in[\sqrt m,2\sqrt m]$，那么本质不同的询问数不超过质数个数，即 $\pi(\sqrt m)$ 级别。

对于 $h_u$ 相同的元素要用快速幂计算答案，复杂度 $\mathcal O(\sqrt m\pi(\sqrt m)\log n)=\mathcal O\left(\dfrac{m}{\log m}\log n\right)$

时间复杂度 $\mathcal O\left(\dfrac{m\log n}{\log m}\right)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
ll ksm(ll a,ll b) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
vector <int> G[MAXN];
int n,lim[MAXN],dep[MAXN],ot[MAXN];
void dfs1(int u,int fz) {
	for(int v:G[u]) if(v^fz) dfs1(v,u),dep[u]=max(dep[u],dep[v]+1);
}
void dfs2(int u,int fz) {
	int mx=ot[u],smx=0;
	for(int v:G[u]) if(v^fz) {
		if(mx<dep[v]+1) smx=mx,mx=dep[v]+1;
		else smx=max(smx,dep[v]+1);
	}
	lim[u]=mx+smx+1;
	for(int v:G[u]) if(v^fz) ot[v]=(dep[v]+1==mx?smx:mx)+1,dfs2(v,u);
}
int q,up,pr[MAXN],tot,qc[MAXN];
bool isc[MAXN];
ll m,B,vl[MAXN],id1[MAXN],id2[MAXN];
int id(ll x) { return x<=B?id1[x]:id2[m/x]; }
ll g[MAXN],f[MAXN],h[MAXN],dp[MAXN]; //cnt prime, sum mu, minp>?, answer
ll F(ll x) {
	if(x<=pr[up]) return x>=1;
	return f[id(x)]+up+1;
}
signed main() {
	scanf("%d%lld",&n,&m),B=sqrt(m);
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	dfs1(1,0),dfs2(1,0);
	for(int i=2;i<MAXN;++i) {
		if(!isc[i]) pr[++tot]=i;
		for(int j=1;j<=tot&&i*pr[j]<MAXN;++j) {
			isc[i*pr[j]]=true;
			if(i%pr[j]==0) break;
		}
	}
	for(int i=1;i<=n;++i) lim[i]=upper_bound(pr+1,pr+tot+1,lim[i])-pr-1;
	up=*max_element(lim+1,lim+n+1);
	for(ll l=1,r;l<=m;l=r+1) {
		r=m/(m/l),vl[++q]=m/l;
		if(vl[q]<=B) id1[vl[q]]=q;
		else id2[m/vl[q]]=q;
	}
	for(int i=1;i<=q;++i) g[i]=vl[i]-1;
	for(int k=1;k<=tot;++k) {
		for(int i=1;i<=q&&1ll*pr[k]*pr[k]<=vl[i];++i) {
			g[i]-=g[id(vl[i]/pr[k])]-(k-1);
		}
	}
	for(int i=1;i<=q;++i) f[i]=-g[i];
	for(int k=tot;k>up;--k) {
		for(int i=1;i<=q&&1ll*pr[k]*pr[k]<=vl[i];++i) {
			f[i]-=f[id(vl[i]/pr[k])]+k;
		}
	}
	if(pr[up]>2*B) {
		ll ans=1;
		for(int i=1;i<=n;++i) ans=ans*(max(0ll,g[1]-lim[i])+1)%MOD;
		if(up<g[1]) ans=(ans-(g[1]-up))%MOD;
		printf("%lld\n",(ans+MOD)%MOD);
		return 0;
	}
	for(int i=1;i<=n;++i) ++qc[lim[i]];
	for(int i=1;i<=q;++i) h[i]=g[i],dp[i]=1;
	for(int k=tot;k>=1;--k) {
		if(qc[k]) {
			for(int i=1;i<=q&&vl[i]>=pr[k];++i) dp[i]=dp[i]*ksm((h[i]-k+1)%MOD,qc[k])%MOD;
		}
		for(int i=1;i<=q&&1ll*pr[k]*pr[k]<=vl[i];++i) {
			for(ll pw=pr[k];pw*pr[k]<=vl[i];pw=pw*pr[k]) {
				h[i]+=1+h[id(vl[i]/pw)]-k;
			}
		}
	}
	dp[q]=1;
	ll ans=0;
	for(ll l=1,r;l<=m;l=r+1) {
		r=m/(m/l);
		ans=(ans+(F(r)-F(l-1))%MOD*dp[id(m/l)])%MOD;
	}
	printf("%lld\n",(ans+MOD)%MOD);
	return 0;
}
```

---

