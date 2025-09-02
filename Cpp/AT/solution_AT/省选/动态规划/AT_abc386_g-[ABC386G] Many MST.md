# [ABC386G] Many MST

## 题目描述

给定两个正整数 $N$ 和 $M$。我们考虑一个有 $N$ 个顶点的完全图，顶点编号从 $1$ 到 $N$。在这个图中，每条边的权重是从 $1$ 到 $M$ 的整数。对于这种图，共存在 $M^{N(N-1)/2}$ 种不同的可能性。对于每种可能的图，我们要计算出它的最小生成树中所有边的权重之和。最后，我们需要计算这些权重和的总和，并输出该总和对 $998244353$ 取模的结果。

## 说明/提示

- $2 \leq N \leq 500$
- $1 \leq M \leq 500$
- 所有输入值均为整数

### 示例解释

如果一个三顶点的完全图，其边的权重是 $1$ 或 $2$，有 $8$ 种可能的图。每个图的最小生成树中的边权重和为 $2, 2, 2, 3, 2, 3, 3, 4$，因此答案是 $21$，即 $2 + 2 + 2 + 3 + 2 + 3 + 3 + 4 = 21$。

![](https://img.atcoder.jp/abc386/f22490c7e125872d186e7dbb13165ebc.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 2```

### 输出

```
21```

## 样例 #2

### 输入

```
2 100```

### 输出

```
5050```

## 样例 #3

### 输入

```
20 24```

### 输出

```
707081320```

# 题解

## 作者：emmoy (赞：14)

~~公式恐惧症慎入~~。

题目要求边权在 $1\sim M$ 之间，我们转化一下，变成 $0\sim M-1$ 之间，最后再将答案加上 $(N-1)\times M^{N(N-1)\over2}$ 就行了。

对于一个图 $G$，设 $G_k
$ 是由 $G$ 中边权**小于** $k$ 的边组成的图，而 $c(G_k)$ 是 $G_k$ 中连通块的个数，那么其最小生成树的边权和为 $\sum_{k=1}^{M} (c(G_k)-1)$。

为什么？

如果一条边权为 $v$ 边在最小生成树内，那么只有枚举的 $k$ 在 $v+1\sim M$ 的时候才会有这条边，换句话说，也就是才会让联通块数减一。

那么，在这之前，$k$ 从 $1\sim v$ 共 $v$ 次枚举时联通块数会多一，总共就正好加上了 $v$。

减一是因为最小生成树的点数比边数多 $1$。

原式又可化简为 $-M+\sum_{k=1}^{M} c(G_k)$。

设 $S$ 是所有 $M^{N(N+1)\over2}$ 个完全图的集合，$C(G_k)$ 是 $G_k$ 的连通块的集合，那么总答案为：

$$
\begin{aligned}
&(N-1)\times M^{N(N-1)\over2}+\sum_{G\in S}\left(-M+\sum_{k=1}^{M}c(G_k)\right)\\
=&(N-1)\times M^{N(N-1)\over2}-M\times M^{N(N-1)\over2}+\sum_{k=1}^{M}\sum_{G\in S}c(G_k)\\
=&(N-1-M)\times M^{N(N-1)\over2}+\sum_{k=1}^{M}\sum_{G\in S}\sum_{H\in C(G_k)}1
\end{aligned}
$$

到这里应该都挺好理解的。

下面，我们将推导如何为每个 $k$ 求出 $\sum_{G\in S}\sum_{H\in C(G_k)}1$。

对于一个 $H$，我们设它有 $V$ 个点与 $L$ 条边，那么有 $H\in C(G_k)$ 的图 $G\in S$ 的 $H$ 的数量有如下数量个。

$$
(M-k)^{{V(V-1)\over2}-L}\times k^L\times (M-k)^{V(N-V)}\times M^{(N-V)(N-V-1)\over2}
$$

我们考虑 $G$ 中每条边的情况来得出这个式子。

对于两个端点都在 $H$ 中的边，由于只能有 $L$ 条边显示出来，即有 $L$ 条边的权值为 $0\sim k-1$，共 $k$ 种取值，于是一共有 $k^L$ 种情况，剩下共 ${V(V-1)\over2}-L$ 条边由于都没显现出来，于是取值范围从 $k\sim M-1$，共 $M-k$ 种取值，于是有 $(M-k)^{{V(V-1)\over2}-L}$ 种情况。

对于只有一个端点在 $H$ 中的边，由于这种边如果显现，那么 $H$ 就和 $H$ 外的点连接了，与定义不符，于是这种边取值范围从 $k\sim M-1$，共 $M-k$ 种取值，于是有 $(M-k)^{V(N-V)}$ 种情况。

对于两个端点都不在 $H$ 中的边，由于与 $H$ 无关，所以就可以随便选，有 $M^{(N-V)(N-V-1)\over2}$ 种取值。

全部乘起来即可。

---

我们发现后两项只与 $V$ 有关，于是可以设 $f(s)$ 表示有 $s$ 个节点的所有联通块 $H$ 的 $(M-k)^{{s(s-1)\over2}-L}\times k^L$ 的总和。

我们发现我们可以枚举 $s$。

由于我们要在 $N$ 个点中选 $s$ 个点组成联通块，于是要乘上 $\binom{N}{s}$。

根据乘法分配律，原式就可化为：

$$
(N-1-M)\times M^{N(N-1)\over2}+\sum_{k=1}^{M}\sum_{s=1}^N\binom N s f(s)\times (M-k)^{s(N-s)}\times M^{(N-s)(N-s-1)\over2}
$$

现在我们的问题是如何快速求出 $f(s)$。

考虑容斥，于是可以用总方案数减去不构成联通块的方案数。

不构成联通块的方案数就是有小联通块独立出来，这和上面的式子很像。

于是我们直接 copy 过来。

$$
f(s)=M^{s(s-1)\over2}-\sum_{i=1}^{s-1}\binom s i f(i)\times (M-k)^{i(s-i)}\times M^{(s-i)(s-i-1)\over2}
$$

于是我们开心的打了代码，发现样例没过。

为什么？

我们发现，由于你连通块外的边乱选，就有可能也组成连通块，于是 $\binom s i$ 的时候会算重。

考虑如何去重。

我们可以钦定一个点一定在所选连通块内，那么无论其他如何组，都因为没有钦定的点而选不到。

于是就相当于 $\binom{s-1}{i-1}$。

原式即为：

$$
f(s)=M^{s(s-1)\over2}-\sum_{i=1}^{s-1}\binom {s-1} {i-1} f(i)\times (M-k)^{i(s-i)}\times M^{(s-i)(s-i-1)\over2}
$$

时间复杂度 $\mathcal{O}(n^2m)$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
const int mod=998244353;
int n,m,ans;
int f[N];
int c[N][N],pp[N][N*N];
//c是杨辉三角预处理组合数，pp是预处理幂
signed main()
{
	cin>>n>>m;
	for(int i=0;i<=500;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
		pp[i][0]=1;
		for(int j=1;j<=500*500;j++) pp[i][j]=pp[i][j-1]*i%mod;
	}
	ans=(n-1-m)*pp[m][n*(n-1)/2]%mod;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			f[j]=pp[m][j*(j-1)/2];
			for(int k=1;k<j;k++) f[j]=(f[j]-f[k]*c[j-1][k-1]%mod*pp[m-i][k*(j-k)]%mod*pp[m][(j-k)*(j-k-1)/2]%mod+mod)%mod;
			ans=(ans+c[n][j]*f[j]%mod*pp[m-i][j*(n-j)]%mod*pp[m][(n-j)*(n-j-1)/2]%mod)%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：5)

计数 dp 练手题。

进入此题之前首先考虑一个问题：假设有一个序列 $a_{[1,n]}$，设另一个序列 $b_{[1,n]}$ 满足 $\forall 1\le i\le n,b_i=\sum\limits_{j=i}^n a_j$，也即 $\ge i$ 的所有下标对应 $a$ 值的和。那么 $\sum\limits_{i=1}^n ia_i$ 该如何用 $b$ 表示？

答案是 $\sum\limits_{i=1}^n b_i$，手搓一下即可。这是计数/概率 dp 常用的拆贡献套路。

回到这道题目，我们把问题改为在边权完全不相关随机时，MST 权值的期望，也即最终答案的 $\frac{1}{m^{\frac{1}{2}n(n-1)}}$。我们假设序列 $c_{[1,m]}$ 满足 $\forall 1\le i\le m,c_i$ 表示边权为 $i$ 的边出现在 MST 中的数量期望，那么 MST 权值期望即为 $\sum\limits_{i=1}^m ic_i$。我们求出序列 $d_{[1,m]}$，使得 $\forall 1\le i\le m,d_i=\sum\limits_{j=i}^m c_j$，也表示 MST 中边权 $\ge j$ 的边期望有几条。那么最终期望为 $\sum\limits_{i=1}^m d_i$。

扯那么多是干什么呢？对于 $1\le i\le m$ 的整数 $i$，由于 MST 肯定包含 $n-1$ 条边（废话），那么不难发现，如果我们模拟 MST 按照边权从小到大加入边，那么 $d_i+1$ 即为加入边权 $<i$ 的边后，剩余**联通块**数量的期望。这样就把原先的问题转化成了一个非常板的子问题：

> 一个大小为 $n$ 的图，每两个不同的点之间有 $p$ 的概率连边（互相独立），求最后图的联通块数量。

记 $f_i$ 表示一个大小为 $i$ 的图（记其点集为 $\{1,2,\dots,i\}$）经过上述方式连边后联通的概率。

考虑作减法。钦定 $1$ 号点所在的联通块点集为 $S\not=\{1,2,\dots,i\}$，那么此事件发生的概率为 $S$ 中的点与其他点均没有边相连的概率乘 $S$ 中的点互相联通的概率，即 $(1-p)^{|S|(i-|S|)}f_{|S|}$。我们要排除所有这样的事件的概率，故 $f_i=1-\sum\limits_{\{1\}\sube S\sub \{1,2,\dots,i\}}(1-p)^{|S|(i-|S|)}f_{|S|}=1-\sum\limits_{j=1}^{i-1}\binom{i-1}{j-1}(1-p)^{j(i-j)}f_j$。然后预处理 $t\in [0,\frac{1}{2}n(n-1)]$ 中所有的 $(1-p)^t$ 再 dp 即可。

上述问题的答案就是：枚举 $S\sube \{1,2,\dots,n\}$，$S$ 中的点与其他点都不联通且 $S$ 自身联通的概率求和，也即 $\sum\limits_{S\sube\{1,2,\dots,n\}}(1-p)^{|S|(n-|S|)}f_{|S|}=\sum\limits_{i=1}^n \binom{n}{i}(1-p)^{i(n-i)}f_i$。当 $p=\frac{t-1}{m}$ 时，上式即为 $d_{t}+1$。MST 权值**之和**即为 $m^{\frac{1}{2}n(n-1)}\sum\limits_{i=1}^m d_i$。时间复杂度 $O(n^2m)$，完全可以通过此题。

如果公式有误欢迎指正！下面是代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,C[505][505],P[505][505],ni[505],dp[505],dp2[505],gsm[125005],ans;
const int modp=998244353;

signed main(){
	cin>>n>>m;ni[1]=1;
	for(int i=2;i<=500;i++)ni[i]=(modp-modp/i)*ni[modp%i]%modp;
	for(int i=0;i<=n;i++){
		C[i][0]=P[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%modp;
			P[i][j]=P[i-1][j-1]*i%modp;
		}
	}
	for(int i=0;i<m;i++){
		gsm[0]=1;
		for(int j=1;j<=n*n/2;j++){
			gsm[j]=gsm[j-1]*(m-i)%modp*ni[m]%modp;
		}
		for(int j=1;j<=n;j++){
			dp2[j]=1;
			for(int k=1;k<j;k++){
				dp2[j]=(dp2[j]+modp-C[j-1][k]*gsm[k*(j-k)]%modp*dp2[j-k]%modp)%modp;
			}
			ans=(ans+C[n][j]*dp2[j]%modp*gsm[j*(n-j)])%modp;
		}
		ans=(ans+modp-1)%modp;
	}
	for(int i=1;i<=n*(n-1)/2;i++)ans=ans*m%modp;
	cout<<ans;
	return 0;
}
```

---

## 作者：_determination_ (赞：4)

好题。

“所有最小生成树的边权和”这个东西显然是难处理的。

考虑这样的东西：

> 图 $G$ 的最小生成树边权和为：
>
> $$f(G)=(\sum_{k=1}^{M}c(G,k))-M+N-1$$
>
> 其中 $c(G,k)$ 表示 $G$ 中保留边权 $\leq k$ 的边的连通块的数量。
>
> 证明显然，一定有 $c(G,k)-1$ 条边的权值 $>k$。

$U$ 代表所有 $n$ 个点，完全图的集合。

$$ans=\sum_{G\in U}f(G)$$

$$=\sum_{G\in U}(\sum_{i=1}^{M}c(G,i)-M+N-1)$$
$$=(N-1-M)M^{\frac{N(N-1)}{2}}+\sum_{i=1}^{M}\sum_{G\in U}c(G,i)$$

枚举连通块（边集不一样是不同的），统计该连通块 $g_k$ 的出现次数。

下面令一个图 $g$ 的点数为 $n(g)$，边数为 $m(g)$。

如果这个连通块有 $n$ 个点 $m$ 条边，那么他的贡献是：

$$k^m(M-k)^{n(N-n)}(M-k)^{C_{n}^{2}-m}M^{C_{N-n}^{2}}$$

第一项是这 $m$ 条边的边权是 $[1,k]$ 任意取的。

第二项是该连通块连向外部的边的边权是 $[k+1,M]$ 的。

第三项是连通块内部（除了那 $m$ 条）的边的边权是 $[k+1,M]$ 的。

第四项是外部之间连边是任意边权的。

枚举连通块大小：

$$\sum_{G\in U}c(G,k)$$
$$\sum_{n=1}^{N}C_{N}^{n}(M-k)^{n(N-n)}M^{C_{N-n}^{2}}\sum_{n(g)=n}k^{m(g)}(M-k)^{C_{n}^{2}-m(g)}$$
$$\sum_{n=1}^{N}C_{N}^{n}(M-k)^{n(N-n)}M^{C_{N-n}^{2}}g_k(n)$$

其中 $g_k(n)$ 表示点数为 $n$，每条边有 $k$ 种情况出现，$M-k$ 种情况不出现的连通图数量。

这个就是一个很典的容斥。

$$g_k(n)=M^{C_{n(n-1)}^{2}}-\sum_{i=1}^{n-1}g_k(i)C_{n-1}^{i-1}(M-k)^{i(n-i)}M^{C_{n-i}^{2}}$$

> 总方案数为随便赋权的方案数减去会导致不连通的方案数。
>
> 考虑枚举 $1$ 所在连通块的大小，那么转移是很好理解的。

$$ans=(\sum_{k=1}^{M}\sum_{n=1}^{N}C_{N}^{n}(M-k)^{n(N-n)}M^{C_{N-n}^{2}}g_k(n))+(N-1-M)M^{C_{N}^{2}}$$

---

## 作者：CarroT1212 (赞：3)

应该比较套路的计数，反正我觉得挺难的。基本算复读一下官方题解了，写详细点。

首先你需要知道一个非常诡异的 trick。

> + 给定 $n$ 个点的无向有边权图 $G$，求其 MST 的边权和 $f(G)$。
>
> 令边权区间为 $[1,k]$，$G_x$ 为仅保留 $G$ 中边权 $\le x$ 的边得到的无向无权图，$c(G)$ 为图 $G$ 的连通分量数，那么 MST 边权和为：
>
> $$f(G)=\left(\sum\limits_{i=1}^k c(G_i)\right)-k+n-1$$
>
> > 证明起来比较显然，考虑 Kruskal 过程中每次连接两个连通块的边贡献了几次。$-k$ 是对每个 $i$ 扣掉一个连通块，$+n-1$ 是 MST 中每条边被少算了一次。

这个 trick 的好处在于，你成功地把边权对本题的影响降低了一些，并且求解的东西变成了也许更好处理的连通块数。

于是令所有可能的带权无向完全图集为 $U$，大小 $M^{\frac{N(N-1)}{2}}$。所求答案瞬间变为：

$$\begin{aligned}
\sum\limits_{G\in U}f(G)&=\sum\limits_{G\in U}\left(\left(\sum\limits_{i=1}^M c(G_i)\right)+N-M-1\right)\\
&=(N-M-1)\cdot M^{\frac{N(N-1)}{2}}+\sum\limits_{i=1}^M\sum\limits_{G\in U} c(G_i)\end{aligned}$$

问题变成后面那个东西。再枚举 $i$，对所有相同的 $i$ 统一计算，所以现在问题是对每一个 $k$ 求 $\sum\limits_{G\in U} c(G_k)$。

考虑每一个可能的连通分量 $H_k$ 的贡献（边集不同也视为不同），即它出现在了多少个 $G_k$ 内（$G_k$：把每一种可能的 $G$ 砍掉边权大于 $k$ 的边得到的图，可能重复）。因为我们对所有可能的 $G$ 计数，那么这里的 $G_k$ 可以理解成，**$G_k$ 是一张 $N$ 个点的无向无权图，它的每一条边有 $k$ 种方案出现，$(M-k)$ 种方案不出现**。

这个对连通分量而言就比较好计数了。设 $H_k$ 中的点数为 $V(H_k)$，边数为 $m(H_k)$。那么有 $H_k$ 被计算的次数：

$$h(H_k)=k^{m(H_k)}\cdot (M-k)^{\binom{V(H_k)}{2}-m(H_k)}\cdot (M-k)^{V(H_k)(N-V(H_k))}\cdot M^{\binom{N-V(H_k)}{2}}$$

> 第一项为本来被钦定在 $H_k$ 里的边，第二项为两端属于 $H_k$ 但边本身不属于的，第三项为连接 $H_k$ 与外部的，第四项为完全在外部的。结合定义不难理解底数指数。

式子有了，现在我们需要求 $\sum\limits_{H_k} h(H_k)$。枚举 $V(H_k)$，有：

$$\begin{aligned}

\sum\limits_{G\in U} c(G_k)&=\sum\limits_{H_k} h(H_k)\\

&=\sum\limits_{s=1}^n \binom{N}{s}\cdot \sum\limits_{V(H_k)=s,H_k}k^{m(H_k)}\cdot (M-k)^{\frac{s(s-1)}{2}-m(H_k)}\cdot (M-k)^{s(N-s)}\cdot M^{\binom{N-s}{2}}\\

&=\sum\limits_{s=1}^n \binom{N}{s}\cdot (M-k)^{s(N-s)}\cdot M^{\binom{N-s}{2}}\cdot
\left(\sum\limits_{V(H_k)=s,H_k}k^{m(H_k)}\cdot (M-k)^{\binom{s}{2}-m(H_k)}\right)\\

&=\sum\limits_{s=1}^n \binom{N}{s}\cdot (M-k)^{s(N-s)}\cdot M^{\binom{N-s}{2}}\cdot g_k(s)

\end{aligned}$$

其中由式子实际意义，设 $g_k(s)$ 为点数为 $s$，每条边有 $k$ 种方案出现，$(M-k)$ 种方案不出现，这样的**连通**图的数量。

这里确实是个[图计数经典套路](https://www.luogu.com.cn/problem/P4841)了。有转移：

$$g_k(s)=M^{\frac{s(s-1)}{2}}-\sum\limits_{i=1}^{s-1}\binom{s-1}{i-1}\cdot g_k(i)\cdot (M-k)^{i(s-i)}\cdot M^{\frac{(s-i)(s-i-1)}{2}}$$

> 先求 $s$ 个点的不要求连通的图数量，再把不连通的丢掉。那么枚举某一个固定点所在的连通块大小，把它和外部强制分隔开即可。

把几步式子一层层套上去就可以得到最终答案了。预处理幂次方后复杂度是 $O(N^2M)$ 的。

```cpp
const ll J=1e18,N=507,P=998244353;
ll qp(ll x,ll y=P-2) { return y?(y&1?x:1)*qp(x*x%P,y>>1)%P:1; }
ll fac[N],fnv[N];
struct init { init() {
	fac[0]=1; for (ll i=1;i<N;i++) fac[i]=fac[i-1]*i%P;
	fnv[N-1]=qp(fac[N-1]); for (ll i=N-1;i;i--) fnv[i-1]=fnv[i]*i%P;
} } A;
ll C(ll x,ll y) { return x<0||y<0||x<y?0:fac[x]*fnv[y]%P*fnv[x-y]%P; }
ll n,m,ans,g[N],pw[N][N*N];
ll C2(ll x) { return x*(x-1)/2; }
void mian() {
	for (ll i=0;i<N;i++) {
		pw[i][0]=1;
		for (ll j=1;j<N*N;j++) pw[i][j]=pw[i][j-1]*i%P;
	}
	scanf("%lld%lld",&n,&m);
	for (ll k=1;k<=m;k++) {
		for (ll i=1;i<=n;i++) {
			g[i]=pw[m][C2(i)];
			for (ll j=1;j<i;j++) (g[i]+=P-C(i-1,j-1)*g[j]%P*pw[m-k][j*(i-j)]%P*pw[m][C2(i-j)]%P)%=P;
			(ans+=C(n,i)*g[i]%P*pw[m-k][i*(n-i)]%P*pw[m][C2(n-i)])%=P;
		}
	}
	cout<<(ans+(n-m-1+P)*pw[m][C2(n)])%P;
}
```

（没错预处理全部的幂次方是开得下的）

有 EGF+NTT 做法。

---

## 作者：zhenjianuo2025 (赞：3)

图计数容斥经典例题。

从小到大加入每种边权。

设 $g_{k,i}$ 表示 $i$ 个点的有标号图加入前 $k$ 种权的边构成连通图的方案数，$f_{k,i}$ 表示对应 MST 的边权和。


设 $G_{k,i}$ 表示 $i$ 个点的有标号图加入前 $k$ 种权的边不要求连通的方案数，类似地设 $F_{k,i}$ 表示对应 MST 的边权和。

它们的转移是：
$$
G_{k,i}=\sum_{j=1}^iG_{k,i-j}g_{k-1,j}\binom{i-1}{j-1}(k-i+1)^{j(i-j)}
$$
$$
F_{k,i}=\sum_{j=1}^i\left(F_{k,i-j}g_{k-1,j}+f_{k-1,j}G_{k,i-j}+kG_{k,i-j}g_{k-1,j}\right)\binom{i-1}{j-1}(k-i+1)^{j(i-j)}
$$

上面两式的含义为枚举在去掉所有权值为 $k$ 的边的新图上 $i$ 所在的连通块大小。

再容斥掉加上所有权值为 $k$ 的边的新图不连通的方案，枚举 $i$ 所在的连通块大小，就得到了转移：

$$
g_{k,i}=G_{k,i}-\sum_{j=1}^{i-1}G_{k,i-j}g_{k,j}\binom{i-1}{j-1}(k-i)^{j(i-j)}
$$
$$
f_{k,i}=F_{k,i}-\sum_{j=1}^{i-1}\left(F_{k,i-j}g_{k,j}+f_{k,j}G_{k,i-j}+kG_{k,i-j}g_{k,j}\right)\binom{i-1}{j-1}(k-i)^{j(i-j)}
$$


答案是 $f_{m,n}$。不使用任何多项式手段，那么复杂度 $O(n^2m)$。

---

## 作者：是青白呀 (赞：3)

各种套路的叠加。

模拟最小生成树的过程，每次加入某一个权值的边。考虑利用差分拆贡献，将权值为 $i$ 的边的贡献 $i$ 拆成 $1\sim i$ 每个位置各 $1$，也即计算 $d_i$ 表示权值大于等于 $i$ 的边的个数，最小生成树边权则为 $\sum_{i=1}^m d_i$。假设加入了 $\le i$ 的边后，还有 $x$ 个连通块，则说明有 $x-1$ 条边的权值 $>i$，此处产生了 $x-1$ 的贡献。

于是出现 $O(m)$ 个问题，形如加入权值小于等于 $i$ 的边后，每种完全图的连通块个数和是多少，则 $d$ 用算出来的个数减去 $m^{\frac{n(n-1)}{2}}$ 即可。

考虑如何求个数和？首先假设当前枚举到的边权为 $x$。对于连通块问题，不妨枚举编号最小的点所在的连通块大小进行 dp。设 $f_i$ 表示 $i$ 个点的完全图在此限制下的连通块个数和，$g_i$ 表示 $i$ 个点的连通完全图个数。对于 $f$，枚举第一个点所在的连通块大小，并将其去掉：
$$
f_n=m^{n(n-1)/2}+\sum_{i=1}^n\binom{n-1}{i-1}g_if_{n-i}(m-x)^{i(n-i)}
$$
也即两个部分内部的方案，以及两个部分之间边的方案。注意到要求不连通，故两个部分之间的边权必须大于 $x$。

对于 $g$，可以容斥，用总方案数减去有多个连通块的方案数，于是仍然可以枚举一个连通块，剩下的部分任意连，有：
$$
g_{n}=m^{n(n-1)/2}-\sum_{i=1}^{n-1}\binom{n-1}{i-1}g_i\times m^{(n-i)(n-i-1)/2}\times (m-x)^{i(n-i)}
$$
递推预处理两个幂次即可做到 $O(n^2)$ 求一个权值的答案。总复杂度做到 $O(n^2m)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=505,M=2e6+5,mo=998244353,inf=(ll)1e18+7;
const double PI=acos(-1);
void read(int &a){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    a=x*w;
}
int n,m;
int quick_power(int base,int x){
    int res=1;
    while(x){
        if(x&1)res*=base,res%=mo;
        base*=base,base%=mo;
        x>>=1;
    }
    return res;
}
int tot,f[N],g[N],c[N][N],pwm[N*N],pwn[N*N];
int calc(int x){
    rep(i,0,n)
        f[i]=g[i]=0;
    g[0]=pwn[0]=1;
    f[0]=0;
    rep(i,1,n*n)
        pwn[i]=pwn[i-1]*(m-x)%mo;
    rep(i,1,n){
        g[i]=f[i]=pwm[i*(i-1)/2];
        rep(j,1,i-1){
            int res=c[i-1][j-1]*g[j]%mo*pwm[(i-j)*(i-j-1)/2]%mo*pwn[j*(i-j)]%mo;
            g[i]+=mo-res;
        }
        g[i]%=mo;
        rep(j,1,i){
            int res=c[i-1][j-1]*g[j]%mo*f[i-j]%mo*pwn[j*(i-j)]%mo;
            f[i]+=res;
        }
        f[i]%=mo;
    }
    return f[n];
}
signed main(){
    read(n),read(m);
    tot=quick_power(m,n*(n-1)/2);
    pwm[0]=1;
    rep(i,1,n*n)
        pwm[i]=pwm[i-1]*m%mo;
    c[0][0]=1;
    rep(i,1,n){
        c[i][0]=1;
        rep(j,1,i)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
    }
    int ans=tot*(n-1)%mo;
    rep(i,1,m)
        ans+=calc(i)+mo-tot,ans%=mo;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

计算对于所有 $n$ 个点的无向完全图（边权位于 $[1,m]\cap\mathbb{Z}$）的最小生成树边权和之和。答案对 $998,244,353$ 取模。

$1\leq m\leq 500,2\leq n\leq 500$。

## 思路

先将边权从 $[1,n]$ 改为 $[0,n)$，这样方便后面拆贡献。下面记 $h(x)=\binom{x}{2}$。

最小生成树这个东西很难和计数揉在一起，尝试从最小生成树的本质思考。

仿照 Kruskal 算法，我们按照边权从小到大排序，然后尝试加入到最小生成树中。这里将排序改为桶排序，也就是枚举边权，我们称枚举到边权为 $x$ 称为轮次 $x$。

在轮次 $x$，我们添加了多少条边？应当是这一轮最后的连通块数，减去上一轮最后的连通块数。记 $G_k$ 表示轮次 $k-1$ 已经考虑过的所有边构成的图，$\tau(G)$ 表示图 $G$ 的连通块集合。

那么这个图的最小生成树边权和应该是：

$$
\begin{aligned}
&\sum_{k=0}^{m}k(\tau(G_k)-\tau(G_{k+1}))\\
&=\sum_{k=0}^{m}k\tau(G_k)-\sum_{k=0}^{m}k\tau(G_{k+1})\\
&=\sum_{k=0}^{m}k\tau(G_k)-\sum_{k=1}^{m+1} (k-1)\tau(G_k)\\
&=-m\tau(G_{m+1})+\sum_{k=1}^{m} \tau(G_k)\\
&=-m+\sum_{k=1}^{m}\tau(G_k)
\end{aligned}
$$

这个形式看起来好处理一些，代入，则我们要求的是：

$$
\begin{aligned}
&(n-1)\cdot m^{h(n)}+\sum_{G}\sum_{k=1}^{m} |\tau(G_k)|-m\\
&=(n-1)\cdot m^{h(n)}-m\cdot m^{h(n)}+\sum_{G}\sum_{k=1}^{m} |\tau(G_k)|\\
&=(n-1-m)\cdot m^{h(n)}+\sum_G\sum_{k=1}^{m}\sum_{H\in\tau(G_k)} 1\\
&=(n-m-1)\cdot m^{h(n)}+\sum_{k=1}^{m}\sum_{H}\sum_{G,H\in \tau(G_k)} 1
\end{aligned}
$$

现在考虑如何计算 $\sum_{G,H\in \tau(G_k)} 1$，假设 $H$ 中有 $N$ 个点，$M$ 条边。

则有四部分的贡献：

- 对于 $H$ 中的边，边权需要位于 $[0,k)$，贡献为 $k^M$。
- 对于 $H$ 的导出子图中的非 $H$ 中的边，边权需要位于 $[k,m)$（因为它们不在 $G_k$ 中），贡献为 $(m-k)^{h(N)-M}$。
- 对于 $H$ 的点集中的点连向其他点的边，边权需要位于 $[k,m)$（因为它们出现在 $G_k$ 中，连通块可以更大），贡献为 $(m-k)^{N(n-N)}$。
- 对于端点不为 $H$ 的点集的边，边权没有任何限制（因为它们属于其他连通块），贡献为 $m^{h(n-N)}$。

于是得到：

$$
\sum_{G,H\in \tau(G_k)} 1=k^M\cdot (m-k)^{h(N)-M}\cdot (m-k)^{N(n-N)}\cdot m^{h(n-N)}
$$

于是现在的目标是求：

$$
\begin{aligned}
&\sum_{H}k^M\cdot (m-k)^{h(N)-M}\cdot (m-k)^{N(n-N)}\cdot m^{h(n-N)}\\
&=\sum_{N=1}^{n}(m-k)^{N(n-N)}\cdot m^{h(n-N)}\cdot\binom{n}{N}\cdot\sum_{H=(N,M)}k^M\cdot (m-k)^{h(N)-M}
\end{aligned}
$$

其中添加的 $\binom{n}{N}$ 表示选出 $N$ 个点当连通块中的点。

枚举 $N$ 后只需要求出 $\sum_{H=(N,M)}k^M\cdot (m-k)^{h(N)-M}$ 即可。

我们考察这个和式的意义，有多少个 $N$ 点的无向连通简单图，其中有 $k$ 种方案选择一条边，有 $m-k$ 种方案反选一条边。这是一个[很经典的问题](https://www.luogu.com.cn/problem/P10982)的变式。

考虑设 $f(N)$ 表示上述和式的值，根据我们提出的意义，枚举点 $1$ 所在的连通块大小，可以得到：

$$
m^{h(N)}=\sum_{i=1}^{N}\binom{N-1}{i-1}f(i)\cdot m^{h(N-i)}(m-k)^{i(N-i)}
$$

拉出一个 $f(N)$ 项，得到：

$$
f(N)=m^{h(N)}-\sum_{i=1}^{N-1}\binom{N-1}{i-1}f(i)\cdot m^{h(N-i)}(m-k)^{i(N-i)}
$$

直接 dp 可以做到 $O(n^2)$。

故我们可以以 $O(n^2m\log n)$ 的时间复杂度完成本题。可以预处理 $m^x,(m-k)^x$ 做到 $O(n^2m)$。

[Submission](https://atcoder.jp/contests/abc386/submissions/64013380)。

---

## 作者：littlebug (赞：2)

不会数数题。不会数数题。不会数数题。不会数数题。不会数数题。不会数数题。不会数数题。不会数数题。不会数数题。不会数数题。

## Solution

### Part 1

一个 trick：对于任意一个图 $G$，设 $G_k$ 为该图中所有 $< k$ 的边组成的图，$c(G_k)$ 为这个图的联通块数量，边权区间为 $[0,w_{\max}]$，则图 $G$ 的 MST 边权和等于 $\sum \limits _{k=1} ^{w_{\max} + 1} (c(G_k) - 1) = - (w_{\max} + 1) + \sum \limits _{k=1} ^{w_{\max} + 1} c(G_k)$。

证明：考虑在 MST 中一条边权为 $w$ 的边的贡献，这条边在 $G_k$ 中当且仅当 $k > w$，这时对连通块数是没有影响的；但是当 $k \le w$ 时，这条边就会断开，连通块数量 $+1$，此时 $k$ 的取值范围为 $[1,w]$，正好有 $w$ 个，于是就可以转化了。$-1$ 是因为要扣掉 $G_k$ 原有的那个连通块。

这个 trick 有一个良好的性质，就是不用去处理 MST 了，而是转为连通块的计数。

### Part 2

既然 Part 1 里说边权区间为 $[0,w_{\max}]$，那么我们不妨把题目的边权区间转化为 $[0,m-1]$，最后再加上一个 $m^{\frac {n(n-1)} 2} \times (n-1)$。

设 $ans$ 为答案，$S$ 为所有 $m^{\frac {n(n-1)} 2}$ 个图组成的集合，则可以列出式子：

$$
\begin{aligned}
ans & = m^{\frac {n(n-1)} 2} \times (n-1) + \sum _{G \in S} \left( - m + \sum _{k = 1} ^m c(G_k) \right) \\
& = m^{\frac {n(n-1)} 2} \times (n-1) - m^{\frac {n(n-1)} 2} \times m + \sum _{G \in S} \sum _{k = 1} ^m c(G_k) \\
& = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{G \in S} \sum _{k = 1} ^m c(G_k)
\end{aligned}
$$

但是这么还是不好做，于是可以不考虑图 $G_k$ 是长什么样的，直接对**每个连通块**进行计数，设 $G_k'$ 为 $G_k$ 的所有连通块集合：

$$
\begin{aligned}
ans & = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{G \in S} \sum _{k = 1} ^m c(G_k) \\
& = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{G \in S} \sum _{k = 1} ^m \sum _{H \in G_k'} 1 \\
& = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{k = 1} ^m \sum _{G \in S} \sum _{H \in G_k'} 1
\end{aligned}
$$

### Part 3

第一个 $\sum$ 可以直接枚举，考虑如何计算 $\sum \limits _{G \in S} \sum \limits _{H \in G_k'} 1$。

因为最后求的是 $H$ 的数量，于是可以从这里入手，设 $H$ 有 $V$ 个点，$E$ 条边，则需要考虑下面几种边：

- 一条边的两个顶点都在 $H$ 中。
  - 如果该边也在 $H$ 中，那么因为限制了一条边出现的条件是其边权 $< k$，于是边权的取值范围为 $[0,k-1]$，共 $k$ 种情况；因为 $H$ 中共有 $E$ 条边，于是答案乘上 $k^E$。
  - 如果该边不在 $H$ 中，那么因为这条边不在 $H$ 中，于是其边权一定 $\ge k$，取值范围即为 $[k,m-1]$，共有 $m-k$ 中情况；显然这种边共有 $\frac {V(V-1)} 2 - E$ 条，于是答案乘上 $(m-k)^{\frac {V(V-1)} 2 - E}$。
- 一条边只有一个顶点在 $H$ 中，另一个顶点不在 $H$ 中。同上，这种边的边权取值范围也为 $[k,m-1]$；因为每个在 $H$ 中的点都可以和每个不在 $H$ 中的点连一条边，于是共有 $V(n-V)$ 条，答案乘上 $(m-k)^{V(n-V)}$。
- 一条边的两个顶点都不在 $H$ 中。随便取即可，答案乘上 $m^{\frac {(n-V)(n-V-1)} 2}$。

于是可以得到：

$$
\sum _{G \in S} \sum _{H \in G_k'} 1 = k^E \times (m-k)^{\frac {V(V-1)} 2 - E} \times (m-k)^{V(n-V)} \times m^{\frac {(n-V)(n-V-1)} 2}
$$

所以可以枚举 $V$（即下面式子中的 $i$）和 $E$，再算上从 $n$ 个点里面选 $i$ 个共有 $\binom n i$ 个，答案转化为：

$$
\begin{aligned}
ans & = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{k = 1} ^m \sum _{i=1} ^n \sum _{E = 0} ^{i(i-1)} \binom n i \times k^E \times (m-k)^{\frac {i(i-1)} 2 - E} \times (m-k)^{i(n-i)} \times m^{\frac {(n-i)(n-i-1)} 2} \\
& = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{k = 1} ^m \sum _{i=1} ^n \binom n i \times(m-k)^{i(n-i)} \times m^{\frac {(n-i)(n-i-1)} 2} \sum _{E = 0} ^{i(i-1)} k^E \times (m-k)^{\frac {i(i-1)} 2 - E}
\end{aligned}
$$

### Part 4

观察这个式子，我们发现它是 $O(n^3m)$ 的，枚举 $E$ 消耗的时间复杂度达到了 $O(n^2)$，不可以接受，需要把这个优化掉。注意到，式子中只有后两项与 $E$ 有关，即 $k^E \times (m-k)^{\frac {i(i-1)} 2 - E}$，所以考虑快速计算这个东西。

设 $f_i$ 为有 $i$ 个点的 $H$ 的 $\sum \limits _{E = 0} ^{i(i-1)} k^E \times (m-k)^{\frac {i(i-1)} 2 - E}$，则：

$$
ans = m^{\frac {n(n-1)} 2} \times (n-1-m) + \sum _{k = 1} ^m \sum _{i=1} ^n \binom n i \times (m-k)^{i(n-i)} \times m^{\frac {(n-i)(n-i-1)} 2} \times f_i
$$

可以在 $O(nm)$ 内计算出。那么如何在大约 $O(n)$ 的时间复杂度内递推出 $f_i$ 呢？

容斥！

其实是个比较典的 trick 了，即在点数为 $i$，一条边有 $k$ 种可能出现，$m-k$ 种可能不出现，所形成的连通图的数量。

也就是用总方案数减去非连通块的方案数。显然总方案数为 $m^{\frac {i(i-1)} 2}$，即所能构成的不同图的个数；非连通块即出现 $> 1$ 个连通块，于是可以枚举连通块大小，**固定点 $\bm 1$ 在连通块内**，其它点与连通块分隔开，然后随便选即可，和上面算 $H$ 的数量的方法有些类似。

$$
f_i = m^{\frac {i(i-1)} 2} - \sum _{j=1} ^{i-1} \binom {i-1} {j-1} \times (m-k)^{j(i-j)} \times m^{\frac {(i-j)(i-j-1)} 2} \times f_j
$$

为什么要固定点 $1$ 呢？因为不这样的话就会导致算重，毕竟连通块外的点随便选也可能构成连通块，这样就算重了。而固定了点 $1$ 之后，算的就是 $1$ 所在的连通块的方案数了，不考虑 $1$ 不在内的连通块的情况，于是就不会算重了。

求 $f_i$ 需要 $O(n)$，加上前面求 $ans$ 总复杂度 $O(n^2m)$，终于做完了。

然后就被 $0^0 = 1$ 硬控了 30min（~~这是本题解最重要的一句话~~）。

[突发奇想想把所有式子放到一块看看](https://www.luogu.com.cn/paste/xnnc3oxp)，视觉效果挺不错的。

## Code

```cpp
namespace math
{
    int inv[V],fac[V],finv[V];
    il void init_inv(int n) {inv[0]=inv[1]=finv[0]=finv[1]=fac[0]=fac[1]=1; rep(i,2,n) inv[i]=(mod-mod/i)*inv[mod%i]%mod,finv[i]=inv[i]; rep(i,2,n) fac[i]=fac[i-1]*i%mod,finv[i]=finv[i-1]*finv[i]%mod;}
    il void init_inv() {init_inv(V-1);}
    template <typename T> il T fact(T n) {T ans=1; rep(i,1,n) (ans*=i)%=mod; return ans;}
    template <typename T> il T A(T n,T m) {!finv[0] && (init_inv(),1); return n<m ? 0 : fac[n]*finv[n-m]%mod;}
    template <typename T> il T C(T n,T m) {!finv[0] && (init_inv(),1); return n<m ? 0 : fac[n]*finv[m]%mod*finv[n-m]%mod;}
    template <typename T> il T fpow(T a,T b) {if(a==-1) return b&1?-1:1; if(b<0) return 0; T ans=1; while(b){if(b&1) ans=ans*a%mod; b>>=1,a=a*a%mod;} return ans;}
    template <typename T> il void exgcd(T a,T b,T &x,T &y) {if(!(a%b)) x=0,y=1; else exgcd(b,a%b,y,x),y-=a/b*x;}
    template <typename T> il T ginv(T a) {if(inv[0]) return inv[a]; int x,k; exgcd((int)a,mod,x,k); return (x%mod+mod)%mod;}
}
using namespace math;

int n,m,pw[MAXN][MAXN*MAXN],f[MAXN];

signed main()
{
    rep(i,0,501)
    {
        pw[i][0]=1;
        rep(j,1,501*501) pw[i][j]=pw[i][j-1]*i%mod;
    }

    read(n,m);

    int ans=0;
    ans+=(n-1-m)*pw[m][n*(n-1)/2]%mod;

    rep(k,1,m)
    {
        rep(i,1,n)
        {
            f[i]=pw[m][i*(i-1)/2];
            rep(j,1,i-1) f[i]-=C(i-1,j-1)*f[j]%mod*pw[m-k][j*(i-j)]%mod*pw[m][(i-j)*(i-j-1)/2]%mod;
            f[i]%=mod;
        }

        rep(i,1,n) ans+=C(n,i)*f[i]%mod*pw[m-k][i*(n-i)]%mod*pw[m][(n-i)*(n-i-1)/2]%mod;
        ans%=mod;
    }

    write((ans%mod+mod)%mod);

    return 0;
}
```

华风夏韵，洛水天依！

---

## 作者：不知名用户 (赞：2)

题意：求所有 $n$ 个点，边权 $\in[1,m]$ 的完全图最小生成树的边权和。

首先考虑到一个~~我考虑不到~~很典的套路：考虑把一种边权贡献到前缀或后缀，即考虑保留边权 $\ge i$ 或 $\le i$ 的边然后算贡献。由此不难发现对于图 $G$，最小生成树边权和为 $\sum\limits_{i=0}^{m-1}(c(G_i)-1)$，。$G_i$ 表示只保留 $\le i$ 的边的图，$c(G)$ 表示图 $G$ 的极大连通块数。证明：考虑 Kruskal，当做完边权 $\le i$ 的边时有 $c$ 个极大连通块，就需要 $c-1$ 条 $>i$ 的边连接，每条边会被一个前缀统计进去。

先把 $c(G_i)-1$ 的 $-1$ 提出来，对于一张图是 $-m$，所以总共少计算了 $m\cdot m^{n(n-1)/2}$，最后加上，乘号后面的表示图的个数。考虑列出答案式，并先枚举 $i$，以下所有求和式 $G$ 均表示：$\sum\limits_{G}\sum\limits_{i=0}^{m-1}c(G_i)=\sum\limits_{i=0}^{m-1}\sum\limits_{G}c(G_i)$。

把 $c(G_i)$ 摊到每个连通块上，同时考虑先枚举极大连通块（用 $B$ 表示）再枚举图：$\sum\limits_{i=0}^{m-1}\sum\limits_{G}\sum\limits_{B}[OK(G_i,B)]=\sum\limits_{i=0}^{m-1}\sum\limits_{B}\sum\limits_{G}[OK(G_i,B)]$。

$OK(G,B)$ 表示 $B$ 是否为 $G$ 中的极大连通块。考虑怎么样的 $G,B$ 是合法的，不难发现等价于 $B$ 连通且 $B,G/B$ 之间没边。

考虑怎么计算 $\sum\limits_{G}[OK(G_i,B)]$。分三类边计算：$B$ 内部边，$B,G/B$ 之间的边，$G/B$ 之间的边。发现前者不好直接计算，后两者可以直接指数求出，故考虑 DP：$f_j$ 表示对于所有 $G$，$G_i$ 的子连通块，有多少个大小为 $j$。假设 $B$ 大小为 $j$，那么 $\sum\limits_{G}[OK(G_i,B)]=f_j\cdot(m-i)^{j(n-j)}\cdot m^{(n-j)(n-j-1)/2}$。考虑把枚举 $B$ 变成枚举 $B$ 的大小，答案式为 $\sum\limits_{i=0}^{m-1}\sum\limits_{j=1}^nC_n^j\cdot f_j\cdot(m-i)^{j(n-j)}\cdot m^{(n-j)(n-j-1)/2}$。

只用考虑怎么 DP 就可以了！所有满足方案的正难则反，若不连通，枚举 $1$ 号点所在的连通块大小（一定要钦定一个点！），计算数量类似刚才计算 $\sum\limits_{G}[OK(G_i,B)]$ 的方法分三类边，故 $f_j=m^{j(j-1)/2}-\sum\limits_{k=1}^{j-1}f_k\cdot C_{j-1}^{k-1}\cdot(m-i)^{k(j-k)}\cdot m^{(j-k)(j-k-1)/2}$。

做完了！！！别忘了加上开始多加的 $m\cdot m^{n(n-1)/2}$。代码很短，但是背后有三个很典的套路和一些简单的交换求和顺序的推导：考虑 $\le i$ 的边、贡献摊到连通块、DP 正难则反并钦定一个点。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 510, mod = 998244353;
int f[N], C[N][N], pw[N*N], p[N*N];

signed main()
{
	int n, m, i, j, k, ans = 0;
	scanf("%lld%lld", &n, &m);
	for(i=0;i<=n;i++) C[i][0] = 1;
	for(i=1;i<=n;i++) for(j=1;j<=i;j++) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
	for(i=p[0]=1;i<=n*n;i++) p[i] = p[i-1] * m % mod;
	for(i=0;i<m;i++)
	{
		for(j=pw[0]=1;j<=n*n;j++) pw[j] = pw[j-1] * (m - i) % mod;
		for(j=1;j<=n;j++)
		{
			f[j] = p[j*(j-1)/2];
			for(k=1;k<j;k++)
				f[j] = (f[j] - f[k] * C[j-1][k-1] % mod * pw[k*(j-k)] % mod * p[(j-k)*(j-k-1)/2] % mod) % mod;
			ans = (ans + C[n][j] * f[j] % mod * pw[j*(n-j)] % mod * p[(n-j)*(n-j-1)/2] % mod) % mod;
		}
	}
	int pp = 1;
	for(i=1;i<=n*(n-1)/2;i++) pp = pp * m % mod;
	ans = (ans - pp * m % mod) % mod;
	ans = (ans % mod + mod) % mod;
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：ReTF (赞：2)

考虑立即放弃直接刻画 MST，将贡献拆到每条边上：

对于每个 $i\in [1,M]$，计算 MST 上权值 $\ge i$ 的边数量 $K_i$，则 MST 的边权和为 $\sum K_i$。

由 Kruskal 算法流程，注意到不管 MST 的边集如何变化，只要每条边的权值均不变，则 $K_i$ 唯一确定。

进一步地，假设图中加入权值 $<i$ 的边时会形成 $j$ 个连通块，则始终有 $j=K_i+1$。因为一定会有 $K_i=j-1$ 条权值 $\ge i$ 的边将这些连通块完全连通。

这个贡献可以转化成算图中加入权值 $<i$ 的边时的连通块数量 $-1$。

继续将贡献拆到每个连通块上，枚举 $i$ 和每个连通块 $C$，现在要算使用权值 $<i$ 的边将 $C$ 连通的方案数。

设 $f_C$ 为使用权值 $<i$ 的边将 $C$ 连通的方案数，$g_C$ 为给 $C$ 的生成子图边赋权的方案数。首先有 $g_C=\displaystyle m^\binom{|C|}{2}$。

考虑容斥，用总方案减去不合法的方案数。枚举包含 $C$ 中最小元素的极大连通块 $S\neq C$ 并减去相应方案数。则有：

$$f_C=\sum_{S\subsetneq C,\min\{C\}\in S}f_S\times g_{C-S}\times (m-i+1)^{|S|\times |C-S|}$$

注意到我们只关心集合的大小而非具体元素，上述式子可以简化：

设 $F_c$ 为使用权值 $<i$ 的边将大小为 $c$ 的任意集合 $C$ 连通的方案数，$G_c$ 为给大小为 $c$ 的任意集合 $C$ 的生成子图边赋权的方案数。首先有 $G_c=\displaystyle m^\binom{c}{2}$。

套用上述容斥：

$$F_c=\sum_{1\le s<c}F_s\times \dbinom{c-1}{s-1}\times G_{c-s}\times (m-i+1)^{s\times (c-s)}$$

计算答案：

$$A_i=\left(\sum_{j=1}^nF_j\times \dbinom{n}{j}\times (m-i+1)^{j\times (n-j)}\times m^{\binom{n-j}{2}}\right)-G_n$$

最终的答案是 $\sum A_i$。

---

## 作者：_Cheems (赞：1)

题意：为完全图的每条边赋值 $[1,m]$，求所有情况下 MST 权值之和。

不妨认为权值为 $[0,m)$，最后再加回去即可。

无从下手，需要做一步转化：考虑 kruskal 的过程，依次将权值为 $0\dots m-1$ 的边加入。不妨记 $G_k$ 为将 $<k$ 的边全部加入后得到的图，$c(G_k)$ 为 $G_k$ 的连通分量集合。那么 $n-|c(G_k)|$ 等于 MST 上权值 $< k$ 的边数量，所以有： 

$$\sum\limits_{e\in MST} w=\sum\limits_{e\in MST}m-1-\sum\limits_{i=1}^{m-1}[w<i] =\sum\limits_{k=1}^{m} |c(G_k)|-m$$

对于 $-m$，总的贡献是 $-m^{\frac {n(n-1)}2+1}$。而 $|c(G_k)|$ 等价于求满足条件的连通分量数量，枚举 $k$，枚举连通分量 $T$，记 $V,E$ 为 $T$ 的点数和边数，那么使它在 $k$ 时产生贡献的赋值方案数为：

$$k^{E}m^{\frac {(n-V)(n-V-1)}2}(m-k)^{\frac {V(V-1)}2-E}(m-k)^{V(n-V)}$$

含义是：内部边 $< k$，外部边随意，对于连接内外部或在内部但不在连通分量内的边，取值 $\ge k$。

不妨枚举 $V=s$，那么 $k$ 的总贡献就是：

$$\sum\limits_{s=1}^{n}\sum\limits_{|T|=s} k^{E}m^{\frac {(n-s)(n-s-1)}2}(m-k)^{\frac {s(s-1)}2-E}(m-k)^{s(n-s)}$$

提取公因式：

$$\sum\limits_{s=1}^{n}m^{\frac {(n-s)(n-s-1)}2}(m-k)^{s(n-s)}\sum\limits_{|T|=s} k^{E}(m-k)^{\frac {s(s-1)}2-E}$$

并不关心点的编号，所以记 $f(s)$ 为连通分量大小为 $s$ 时，后面那串式子的值，代入：

$$\sum\limits_{s=1}^{n}m^{\frac {(n-s)(n-s-1)}2}(m-k)^{s(n-s)}{{n}\choose{s}}f(s)$$

求出 $f$ 即可。对于连通分量一类的计数问题，可以借鉴 [ABC213G](https://www.luogu.com.cn/problem/AT_abc213_g) 的做法，即总价值减去不连通情况的价值。先看看总价值 $W$：

$$W=\sum\limits_{E=0}^{\frac {s(s-1)}2} k^E(m-k)^{\frac {s(s-1)}2 -E}=(m-k)^{\frac {s(s-1)}2}(1+\frac {k}{m-k})^{\frac {s(s-1)}2}=m^{\frac {s(s-1)}2}$$

然后是不连通的价值 $W_2$。不连通可以看做：$1$ 所在连通分量、其它点随意组合（这个刚刚解决了）。单独计算两部分的价值都是容易的，将其乘起来后，发现只需修正 $(m-k)^{\frac{s(s-1)}2}$ 这部分即可：

$$W_2=\sum\limits_{i=1}^{s-1} {{s-1}\choose {i-1}}f_im^{\frac{(s-i)(s-i-1)}2}(m-k)^{i(s-i)}$$

最后 $f_s=W-W_2$。

完结撒花，复杂度 $O(n^2m)$。

#### 代码
注意常数优化。


```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

#define ADD(a, b) a = (a + b) % mod
const int N = 5e2 + 5, mod = 998244353;
int n, m, ans, f[N], jc[N], jcinv[N];
int qstp[N][N * N], C[N][N];

inline void solve(int k){
	for(int s = 1; s <= n; ++s){
		f[s] = qstp[m][s * (s - 1) / 2];
		for(int i = 1; i < s; ++i)
			ADD(f[s], 1ll * (mod - 1) * f[i] % mod * C[s - 1][i - 1] % mod * qstp[m][(s - i) * (s - i - 1) / 2] % mod * qstp[m - k][i * (s - i)] % mod);
		ans = (ans + 1ll * qstp[m][(n - s) * (n - s - 1) / 2] * qstp[m - k][s * (n - s)] % mod * C[n][s] % mod * f[s] % mod) % mod;
	}
}
signed main(){
	for(int i = 0; i < N; ++i){
		qstp[i][0] = 1, C[i][0] = C[i][i] = 1;
		for(int j = 1; j < N * N; ++j) qstp[i][j] = 1ll * qstp[i][j - 1] * i % mod; 
		for(int j = 1; j < i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	cin >> n >> m;
	ans = (1ll * (n - 1) * qstp[m][n * (n - 1) / 2] % mod + 1ll * (mod - 1) * qstp[m][n * (n - 1) / 2 + 1] % mod) % mod;
	for(int i = 1; i <= m; ++i) solve(i);
	cout << ans; 
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

直接容斥就行了。

考虑边权为 $w$ 的边对 MST 边权和的贡献。如果加入这条边之前，有 $c_1$ 个联通块；加入这条边之后，有 $c_2$ 个联通块，则这条边会加入 $c1-c_2$ 条，因此答案乘上 $w(c_2-c_1)$。

所以我们只需要求出：对于所有染色方案，只保留 $\le w$ 的边，形成的联通块的个数总和。

对于一类图计数问题，考虑先计算**图联通时的答案**，然后将联通块**拼接起来**。

首先算出：大小为 $n$ 的联通块（保留 $\le w$ 的边）有多少种染色方案。设为 $mul_{n,w}$。我们先**将所有边任意染色**，然后**删去图不联通的情况**（也就是**枚举编号最小的点所在联通块**），代码如下（`pw[i][j]` 指的是 $i^j$）

```cpp
ffor(i,1,n) ffor(w,1,m) {
  mul[i][w]=pw[m][i*(i-1)/2];
  ffor(t,1,i-1) mul[i][w]=(mul[i][w]-pw[m][t*(t-1)/2]*C[i-1][t]%MOD*mul[i-t][w]%MOD*pw[m-w][t*(i-t)])%MOD;
}
```

然后计算出：$res_{i,w}$ 为 $i$ 个点的图，所有染色方案中只保留边权 $\le w$ 的边形成的联通块的个数和。需要计算辅助数组 $cnt_{i,w}$ 为方案数（其实很没有必要）。同样枚举编号最小点所在联通块，大概长这样：

```cpp
ffor(w,1,m) {
  res[0][w]=0,cnt[0][w]=1;
  ffor(i,1,n) {
    ffor(t,1,i) res[i][w]=(res[i][w]+C[i-1][t-1]*mul[t][w]%MOD*pw[m-w][t*(i-t)]%MOD*res[i-t][w])%MOD,cnt[i][w]=(cnt[i][w]+C[i-1][t-1]*mul[t][w]%MOD*pw[m-w][t*(i-t)]%MOD*cnt[i-t][w])%MOD;
    res[i][w]=(res[i][w]+cnt[i][w])%MOD;
  }
}
```

复杂度 $O(n^2m)$。

---

## 作者：lbmzxhb (赞：0)

[此题中文翻译](https://vjudge.net/problem/AtCoder-abc386_g#author=GPT_zh)

考虑先求出一张图中的 MST 权值的期望值，最后再乘上 $m^{\frac{n(n-1)}{2}}$ 即为答案。

注意到求图 $G$ 的 MST 的权值和有如下式子：

$$f(G)=\sum_{i=1}^m(c(G,i)-1)$$

其中 $c(G,i)$ 表示 $G$ 中仅连接所有权值 $<i$ 的边后的联通块数。

证明考虑 Kurskal 求 MST 的过程，权值为 $w$ 的边只有在权值 $<w$ 的边连接后加入，每次贡献值为 $1$，总贡献恰好为 $w$。最后 $-1$ 是因为边数为连通块数 $-1$。

同理，求 MST 权值和的期望为如下式子：

$$E[G]=\sum_{i=1}^m(E[c(G,i)]-1)=\sum_{i=1}^mE[c(G,i)]-m$$

令 $F(p)$ 为每条边有 $p$ 的概率连接的连通块期望个数，则

$$E[G]=\sum_{i=1}^mF(\frac{i-1}{m})-m$$

问题变成了求 $F(p)$ 的值。

令 $g_{p,i}$ 为图中点数为 $i$，边连接概率为 $p$ 时图连通概率，$f_{p,i}$ 为对应的连通块期望个数。

则有以下转移式：

$$g_{p,i}=1-\sum_{j=1}^{i-1}{i-1\choose j-1}g_{p,j}(1-p)^{j(i-j)}$$
$$f_{p,i}=g_{p,i}+\sum_{j=1}^{i-1}{i-1\choose j-1}g_{p,j}(1-p)^{j(i-j)}(f_{p,i-j}+1)$$

对于第一个式子，枚举与 $1$ 连通的点的个数 $j$，则有 $i-1\choose j-1$ 种选点方案，$j$ 个点连通概率为 $g_{p,j}$，且这 $j$ 个点不与其他点连通的概率为 $(1-p)^{j(i-j)}$，最后算出所有不连通的概率后可算出 $g_{p,i}$。

对于第二个式子，枚举方法与第一个一样，但最后要乘上连通块的期望个数 $f_{p,i-j}+1$，且最后还要加上整张图连通的期望 $g_{p,i}$。

最后 $F(p)$ 的答案为 $f_{p,n}$。

求一次 $F(p)$ 并预处理幂的时间复杂度为 $O(n^2)$，则总时间复杂度 $O(n^2m)$。

[代码](https://atcoder.jp/contests/abc386/submissions/61257883)。

---

