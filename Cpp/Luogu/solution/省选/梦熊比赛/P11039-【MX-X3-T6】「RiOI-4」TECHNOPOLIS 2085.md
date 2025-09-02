# 【MX-X3-T6】「RiOI-4」TECHNOPOLIS 2085

## 题目背景

原题链接：<https://oier.team/problems/X3G>。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/931ql7zi.png)

（图片来自 phigros 曲绘，侵删。）

啊～啊～啊咦～啊咦～哦→啊↑啊↓啊～嗯～哎哎↑哎哦哎嗯～哦啊~爱↖爱↑爱↗爱↑爱↑啊～啊～啊咦～啊咦～啊→啊↑啊↓啊～嗯嗯↓嗯↓滴嘚滴嘚唔↑～～嘟←嘟↖️嘟↑嘟↗️嘟→嘟↘️嘟↓

你说得对，但是这里是梦熊周赛题，不是出题人用来发电的地方，所以你需要做一道图论题。

## 题目描述

约定 $\operatorname{lca}_G(u,v)$ 表示编号为 $u,v$ 的结点在有标号有根树 $G$ 上的最近共同祖先。给定一棵根编号为 $1$，大小为 $n$ ，结点编号为 $1\sim n$ 的有根树 $T$ 与一个大小为 $m$ 的点集 $S$。你需要求出有多少个**不同的**大小为 $n$ 的结点编号为 $1\sim n$ 的有根树 $T'$，满足对于任意 $u,v\in S$，有 $\operatorname{lca}_T(u,v)=\operatorname{lca}_{T'}(u,v)$。

答案对 $998\,244\,353$ 取模。

我们称两颗大小为 $n$ 的有标号有根树是**不同的**，当且仅当以下二者至少一个成立：

- 它们的根节点不同。
- 存在一条边，在一棵树中未出现，而在另一棵树中出现。

## 说明/提示

**【样例解释 #1】**

只有与 $T$ 完全相同的树满足要求。

**【样例解释 #2】**

对于样例 2，满足要求的树的所有 $8$ 种 $p$ 数组如下（根的 $p_i$ 为 $0$）：

$\{0,1,1,2,1\},\{0,1,1,2,2\},\{0,1,1,2,3\},\{0,1,1,2,4\},$  
$\{0,1,1,5,2\},\{0,5,1,2,1\},\{0,1,5,2,1\},\{5,1,1,2,0\}$。

**【数据范围】**

**本题开启捆绑测试。**

|子任务|分数|$n\le$|$m\le$|
|:-:|:-:|:-:|:-:|
|$1$|$7$|$10$|$10$|
|$2$|$18$|$200$|$200$|
|$3$|$22$|$10^5$|$10^5$|
|$4$|$17$|$10^6$|$10$|
|$5$|$36$|$10^6$|$10^6$|

对于 $100\%$ 的数据，$2\le m\le n\le 10^6$，保证输入的 $p$ 对应了一棵有标号有根树，$S$ 描述了一个结点组成的集合。

## 样例 #1

### 输入

```
5 3
1 1 2 2
3 4 5
```

### 输出

```
1```

## 样例 #2

### 输入

```
5 3
1 1 2 2
2 3 4```

### 输出

```
8```

## 样例 #3

### 输入

```
20 10
20 8 7 16 3 15 1 10 17 3 13 15 1 17 1 14 14 8 4
3 7 10 19 15 13 4 6 18 5```

### 输出

```
553508927```

# 题解

## 作者：11400F (赞：4)

## TECHNOPOLIS 2085 题解

~~我是中二吃，看到题目和背景那啪的一下就点进来了。~~

---

要使在新的树 $T^{\prime}$ 上一些关键点的 LCA 和原树相同，很容易就会想到虚树，也就是说，对于关键点集 $S$，$T$ 和 $T^{\prime}$ 的虚树是相同的。

那么我们首先就可以把这棵虚树给建好（设这棵虚树有 $k$ 个点）。然后将剩下的点插到虚树里，造出来一棵新树。

我们这里假设新树树根为虚树的根。

具体地说，把剩下的点插到原来的虚树中，就只有两种情况：要么把点加到虚树边上；要么不在虚树边上加点，等把加在虚树边上的点加完了之后再把这棵虚树上的点和这些散点连边使它们连通。

- 首先讨论把点加到虚树边上的情况：

  假设我们把 $i$ 个点插入到虚树树边上。因为我们要选 $i$ 个点，所以选点的方案数就是 $C_{n-k}^{i}$。然后插到虚树边上。注意到，我们每把一个点插入到某条虚树边上，这条边就会因为中间加了一个点而被被断为 $2$ 条。并且因为最开始这棵虚树是只有 $k-1$ 条边的，所以，插入边的方案数就为 $(k-1)\cdot k\cdot(k+1)\cdots(k+i-2) = \displaystyle\prod_{p=1}^{i}(k-2+p) = \frac{(k+i-2)!}{(k-2)!}$。而因为 $m \ge 2$，所以 $k$ 也一定 $\ge 2$，不用担心越界。

  所以把点加到虚树边上的情况就有 $\displaystyle C_{n-k}^{i} \cdot \frac{(k+i-2)!}{(k-2)!}$ 种。

- 然后讨论把剩下的散点和这棵已经加完了 $i$ 个点的新树连边的情况：

  问题就转化成了：有一棵点数为 $k+i$ 的树，和一堆总数为 $n-k-i$ 的散点。现在需要连接 $n-k-i$ 条边使这些散点和树连通。求连边的方案数。

  在这之前，我们引入由 **Prüfer 序列**引出的一个公式：

  > 现在有一个 $n$ 个点和 $m$ 条边的有标号无向图，其中有 $k$ 个连通块。第 $i$ 个连通块的大小为 $s_i$。我们要连接 $k-1$ 条边使这个图连通。求连边的方案数。
  >
  > 方案数即为：
  > $$
  > n^{k-2} \cdot \displaystyle \prod_{i=1}^{k} s_i
  > $$
  > （具体证明详见 [OI-Wiki](https://oi-wiki.org/graph/prufer/#图连通方案数)，这里不作过多说明。）

  将其带入可得：答案即为 $n^{n-k-i-1}\cdot\displaystyle\prod_{i=1}^{n-k-i+1} s_i = n^{n-k-i-1}(k+i)$。

  这里有一种特殊情况：当 $i=n-k$ 时，那么显然，就是没有点为散点的情况，方案数为 $1$。

  因为情况复杂，我们假设这种情况的答案为 $out_{n, k, i}$（此时新树树根为虚树根，并且原树点 $n$ 个、虚树点 $i$ 个、把 $i$ 个点放到了虚树树边上）。

所以新树树根为虚树根，原树点 $n$ 个、虚树点 $k$ 个的散点答案 $out_{n, k, i}$ 和总答案 $res_{n, k}$ 就为：
$$
out_{n, k, i} = \left\{
\begin{aligned}
&n^{n-k-i-1}(k+i) &(i < n-k)\\
&1 &(i=n-k)
\end{aligned}
\right.


\\
res_{n, k} = \displaystyle \sum_{i=0}^{n-k} C_{n-k}^{i} \cdot \frac{(k+i-2)!}{(k-2)!}\cdot out_{n, k, i}
$$
而如果 $k < n$，就说明有可能有新树树根不为虚树树根的情况，那么我们就可以钦定一个新树根，它的儿子唯一，为原来的虚树树根。一共有 $n-k$ 种钦定方式。每一种钦定方式的答案为 $res_{n, k+1}$，因为新加了一个点到虚树中。所以新树树根不为虚树树根的总方案数为 $(n-k)\cdot res_{n, k+1}$。

所以最终的总答案就为：
$$
res_{n, k} + [k<n] \cdot (n-k)\cdot res_{n, k+1}
$$
Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+6;
const int M = 2e6+6;

struct Edge{
    int to, nxt;
}edge[M];
int h[N], cnt;
void _add(int u, int v) {edge[++cnt] = {v, h[u]}; h[u] = cnt; }
void add(int u, int v) {_add(u, v), _add(v, u);}
int dep[N], dfn[N], dfnidx, anc[N][21], keyp[M];
int lim, m, len;
void dfs(int x, int fa){
    dfn[x] = ++dfnidx;
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    for(int i=1;i<=lim;i++) anc[x][i] = anc[anc[x][i-1]][i-1];
    for(int i=h[x];i;i=edge[i].nxt){
        int v = edge[i].to; if(v == fa) continue;
        dfs(v, x);
    }
}
int getlca(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int sa = dep[x] - dep[y];
    for(int i=lim;i>=0&&sa;i--){
        if(sa&(1<<i)) sa -= (1<<i), x = anc[x][i];
    }
    if(x==y) return x;
    for(int i=lim;i>=0;i--){
        if(anc[x][i]^anc[y][i]) x = anc[x][i], y = anc[y][i];
    }
    return anc[x][0];
}
bool cmp(int x, int y){
    return dfn[x] < dfn[y];
}
void init_imagtree(){
    for(int i=1;i<=m;i++) cin>>keyp[i];
    sort(keyp+1, keyp+1+m, cmp);
    len = m;
    for(int i=1;i<m;i++)
        keyp[++len] = getlca(keyp[i], keyp[i+1]);
    sort(keyp+1, keyp+1+len);
    len = unique(keyp+1, keyp+1+len) - keyp - 1;
}
// 其实上面那一堆都只是用来求最开始的虚树有多少个点。应该有更好的方法。


typedef long long ll;
const ll mod = 998244353;
ll fact[M], invfact[M];

ll ksm(ll bas, ll x){
    ll ans = 1;
    while(x){
        if(x&1) ans = ans * bas % mod;
        bas = bas * bas % mod; x >>= 1;
    }
    return ans;
}

ll C(ll nn, ll mm){
    return fact[nn]*invfact[mm]%mod*invfact[nn-mm]%mod;
}
ll calc(int n, int k){
    ll ans = 0;
    for(int i=0;i<=n-k;i++){
        ans = (ans + 
              C(n-k, i) * fact[k+i-2] % mod * invfact[k-2] % mod * 
              ((i == n-k)? 1: ksm(n, n-k-i-1) * (k+i) % mod) % mod)
              % mod;
    }
    return ans;
}

int n;
void init_fact(){
    fact[0] = invfact[0] = 1;
    for(int i=1;i<=n;i++)
        fact[i] = fact[i-1] * i % mod;
    invfact[n] = ksm(fact[n], mod-2);
    for(int i=n-1;i>=1;i--)
        invfact[i] = invfact[i+1] * (i+1) % mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>m;
    lim = __lg(n) + (__builtin_popcount(n) != 1);
    // cout<<lim<<'\n';
    int u;
    for(int i=2;i<=n;i++){
        cin>>u; add(u, i);
    }
    dfs(1, 0);
    init_imagtree();
    
    init_fact();
    ll ans = 0;
    ans += calc(n, len);
    if(len < n) ans = (ans + (n-len) * calc(n, len+1) % mod) % mod;
    cout<<ans;
    return 0;
}
```

为了一道 2085 学了好多啊 qwq，~~我还要打 2085。~~

---

## 作者：Leasier (赞：2)

~~我不玩音游，这题背景不是我写的。~~

---

转化题意，可知：

- $S$ 中点在**有根树** $T, T'$ 中形成的虚树完全一致。

首先 $O(n)$ 求出虚树大小，下面就用 $m$ 表示了。现在问题转化为：

- 在一棵大小为 $m$ 的**有根树** $B$ 上插入 $n - m$ 个点。
- 每一个新加入的点可以插在边上，也可以挂在其他点之下。
- 对新的**有根树** $T'$ 计数。

不妨先来考虑 $B, T'$ 的根相同的情况。

~~此题最大的难点可能在于：不要到这里就开始考虑 poly。~~

考虑逐个击破：

- 先考虑“插在边上”的情况，枚举有 $i \in [0, n - m]$ 个点插在边上，选出它们的方案数为 $C_{n - m}^i$，插入它们的方案数为 $(m - 1)^{\overline i}$。
- 现在我们还剩 $n - m - i$ 个孤立点，当点数非零，运用 [与 Prüfer 序相关的结论](https://oi-wiki.org/graph/prufer/#%E5%9B%BE%E8%BF%9E%E9%80%9A%E6%96%B9%E6%A1%88%E6%95%B0) 可知方案数为 $(m + i) n^{n - m - i - 1}$。

把上面三项相乘后相加即可。

对于 $B, T'$ 的根不同的情况，在剩下的 $n - m$ 个点里随便挑一个钦定为根，认为它在 $B$ 中在同上计算即可。

答案不难 $O(n)$ 计算，则时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef struct {
	int nxt;
	int end;
} Edge;

const int mod = 998244353;
int m, cnt = 0;
int head[1000007], power[1000007], inv[1000007];
bool mark[1000007], vis[1000007];
Edge edge[1000007];

inline void init(int n, int m){
	power[0] = 1;
	for (register int i = 1; i <= m; i++){
		power[i] = 1ll * power[i - 1] * n % mod;
	}
	inv[0] = inv[1] = 1;
    for (register int i = 2; i <= n; i++){
	    inv[i] = mod - 1ll * (mod / i) * inv[mod % i] % mod;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u){
	vis[u] = mark[u];
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		dfs(x);
		vis[u] |= vis[x];
	}
	if (!mark[u]){
		int cnt = 0;
		for (register int i = head[u]; i != 0; i = edge[i].nxt){
			if (vis[edge[i].end]) cnt++;
		}
		if (cnt >= 2){
			mark[u] = true;
			m++;
		}
	}
}

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

inline int solve(int n, int m){
	int k = n - m, comb = 1, up = 1, ans = 0;
	for (register int i = 0; i <= k; i++){
		int x = 1ll * comb * up % mod;
		if (i < k) x = 1ll * x * power[k - i - 1] % mod * (m + i) % mod;
		add(ans, x);
		comb = 1ll * comb * (k - i) % mod * inv[i + 1] % mod;
		up = 1ll * up * (m + i - 1) % mod;
	}
	return ans;
}

int main(){
	int n = read(), ans;
	m = read();
	for (register int i = 2; i <= n; i++){
		int p = read();
		add_edge(p, i);
	}
	for (register int i = 1; i <= m; i++){
		int u = read();
		mark[u] = true;
	}
	dfs(1);
	init(n, n - m - 1);
	ans = solve(n, m);
	if (m < n) add(ans, 1ll * (n - m) * solve(n, m + 1) % mod);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P11039)

**题目大意**

> 给定 $n$ 个点的有根树，和一个点集 $S$，求有多少有根树满足 $S$ 中任意两点的 $\mathrm{LCA}$ 标号都相同（两棵树根可以不同）。
>
> 数据范围：$n\le 10^6$。

**思路分析**

容易发现题目中的限制等价于 $S$ 的虚树在两棵树中形态不变。

先假定树根等于虚树的根。

求出虚树大小 $m$，那么枚举 $i$ 个点插入在虚树的边中，剩余的 $n-m-i$ 个点可以看成一些散点，要和一个大小为 $m+i$ 的块连成树，可以用 Prufer 序列直接算答案，因此答案为：
$$
\sum_{i=0}^{n-m} \binom{n-m}i(m-1)^{\overline i}(m+i)n^{n-m-i-1}
$$
注意到答案只和 $n,m$ 有关，和树的形态无关，可以简单求出 $m$。

如果树根不是虚树的根，那么相当于将新的根变成虚树根的父亲，即 $m\gets m+1$ 后重算答案即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
ll ksm(ll a,ll b=MOD-2) {
	ll ret=1;
	for(;b;a=a*a%MOD,b>>=1) if(b&1) ret=ret*a%MOD;
	return ret;
}
ll fac[MAXN],ifac[MAXN],pw[MAXN];
ll C(int x,int y) {
	if(x<0||y<0||y>x) return 0;
	return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
ll calc(int n,int m) {
	ll ans=0;
	for(int i=0;i<=n-m;++i) {
		ans=(ans+fac[m+i-2]*ifac[m-2]%MOD*C(n-m,i)%MOD*(i<n-m?((m+i)*pw[n-m-i-1]%MOD):1))%MOD;
	}
	return ans;
}
vector <int> G[MAXN];
int n,m,cnt;
bool f[MAXN];
void dfs(int u) {
	bool ok=f[u];
	for(int v:G[u]) dfs(v),ok|=(f[u]&&f[v]),f[u]|=f[v];
	cnt+=ok;
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=fac[0]=pw[0]=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD,pw[i]=pw[i-1]*n%MOD;
	ifac[n]=ksm(fac[n]);
	for(int i=n;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	for(int i=2,u;i<=n;++i) scanf("%d",&u),G[u].push_back(i);
	for(int i=1,x;i<=m;++i) scanf("%d",&x),f[x]=true;
	dfs(1);
	ll ans=calc(n,cnt);
	if(cnt<n) ans=(ans+(n-cnt)*calc(n,cnt+1))%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：fzitb7912 (赞：1)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/9zpicw3e)。

## 分析

好题。

考虑到 $T'$ 中任意两个关键点的 $\operatorname{LCA}$ 都与 $G$ 相同，不妨先将这些关键点的虚树建出来。记虚树上有 $m$ 个节点，那么问题就转化为：将 $n-m$ 个点插入虚树中，求最终生成树的数量。

现在对 $T'$ 的树根进行分类讨论：

1. $T'$ 的根为虚树的根。
2. $T'$ 的根不为虚树的根。

对于情况 $1$。那 $n-m$ 个点可能会插入当前树上的边，也可能会直接与当前树上的点连接。考虑枚举插到边里面的点的数量，记为 $x$。因为每加一个点会多出来 $1$ 条边，而一开始有 $m-1$ 条边，所以第 $i$ 个点能插在 $m-1+i-1$ 条边中的任意一条里面。所以有方案数为：$C_{n-m}^{x}\times (\prod\limits_{i=m-1}^{m-1+x-1}i)$。

对于剩下的 $n-m-x$ 个点，我们将当前的树 $T'$ 看作 $1$ 个大小为 $m+x$ 的连通块，剩下的点看作 $n-m-x$ 个大小为 $1$ 的连通块。通过 Prüfer 序列，我们可以得到生成树的数量为：$n^{(n-m-x+1)-2}\times (m+x)\times (\prod\limits_{i=2}^{n-m-x+1}1)$。

那么，对于情况 $1$，生成树的数量即为：$\sum\limits_{x=0}^{n-m} C_{n-m}^{x}\times (\prod\limits_{i=m-1}^{m-1+x-1}i)\times n^{(n-m-x+1)-2}\times (m+x)\times (\prod\limits_{i=2}^{n-m-x+1}1)$。这里令当 $x$ 为 $n-m$ 时，后半部分结果为 $1$。

现在看情况 $2$。发现这实际上就相当于在 $n-m$ 个点中选了 $1$ 个点当虚树的新根，然后就变成情况 $1$ 了。

该算法时间复杂度为 $O(n\log n)\sim O(n)$。

## 代码

这里给出暴力二次排序建虚树求 $m$ 的做法，比较慢……

```cpp
il int C(int n,int m){
	if(n<m||m<0||n<0) return 0;
	return _[n]*inv[m]%p*inv[n-m]%p;
}
il bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
il void add(int a,int b){
	ne[++idx]=h[a],e[idx]=b,h[a]=idx;
	return ;
}
il void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	dfn[u]=++cnt,f[u][0]=fa;
	for(re int i=1;i<22;++i) f[u][i]=f[f[u][i-1]][i-1];
	for(re int i=h[u];i;i=ne[i]) dfs(e[i],u);
	return ;
}
il int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(re int i=21;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(re int i=21;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
il void init(){
	_[0]=1;inv[0]=qmi(_[0],p-2,p);
	for(re int i=1;i<N;++i) _[i]=_[i-1]*i%p,inv[i]=qmi(_[i],p-2,p);
	return ;
}
il int work(int n,int m){
	int sum=0;
	for(re int x=0;x<=n-m;++x)
		sum=(sum+C(n-m,x)*_[m-1+x-1]%p*inv[m-1-1]%p*((x==n-m)?1:(qmi(n,n-m-x+1-2,p)*(m+x)%p))%p)%p;
	return sum;
}

il void solve(){
	n=rd,m=rd;
	for(re int i=2;i<=n;++i) add(rd,i);
	dfs(1,0),init();
	for(re int i=1;i<=m;++i) a[i]=rd;
	sort(a+1,a+m+1,cmp);
	b[++len]=a[1];
	for(re int i=2;i<=m;++i) b[++len]=lca(a[i-1],a[i]),b[++len]=a[i];
	sort(b+1,b+len+1),len=unique(b+1,b+len+1)-(b+1);
	m=len;
	ans=(ans+work(n,m))%p;
	if(m+1<=n) ans=(ans+(n-m)*work(n,m+1)%p)%p;
	printf("%lld\n",ans);
    return ;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

大致题意：

给定一颗有根树 $T$ 和一个点集 $S$，求有多少颗有根树 $T'$，使得点集 $S$ 中的任意一对点的最近公共祖先在这两棵树中都相同。

我们考虑我们涉及的点是 $S$ 和他们两两的 LCA，那么先把虚树建出来，假设有 $K$ 个点。

现在假定虚树的根就是我们的 $T'$ 的根。 

那考虑从虚树上加点，要么他在虚树的边上，显然不会影响答案，要么他是这些点的儿子不在边上，也不会影响答案，那么枚举多少个在边上。

假设有 $i$ 个，选出 $i$ 个点，共有 $\binom{n-K}i$ 种，接着插入，共有 $(K-1)^{\overline{i}}$ 种方法。

接着考虑剩下的 $n-K-i$ 个节点，这个相当于和那个 $K+i$
 的大块连 $n-K-i$ 条边使得联通的方案数，这个套 prufer，我们知道有 $(K+i)n^{n-K-i-1}$ 种（边界处有特判）。

最后为：

$$\sum_{i=0}^{n-m}\binom{n-K}i(K-1)^{\overline{i}}(K+i)n^{n-K-i-1}$$

还没完由于我们假定了虚树根，实际上他有可能是别节点为根，共有 $(n-K)$ 个，然后加谁都一样，所以把那个当成根加入到虚树里头，再跑一遍上面的式子即可。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
long long fpow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}long long K=0;
int n,m,fa[26][1000005],b[1000005],cnt,dfn[1000005],dep[1000005];
vector<int>vec[1000005];
bool book[1000005];
void dfs(int u){
	bool ok=book[u];
	for(int i=0;i<vec[u].size();i++){
		int v=vec[u][i];
		dfs(v);
		ok|=(book[u]&&book[v]);
		book[u]|=book[v];
		
	}
	K+=ok;
}
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}

long long fac[2000005];
long long calc(long long K,long long cnt){
	//cnt+K
	//n-K-cnt+1
	if(cnt==n-K)return 1;
	return (K+cnt)*(fpow(n,n-K-cnt-1))%mod;
}
long long calc2(long long n,long long K){
	long long ans=0;
	for(int i=0;i<=n-K;i++){
//		cout<<(fac[n-K]*fpow(fac[i]*fac[n-K-i]%mod,mod-2)%mod)*(fac[K+i-2]*fpow(fac[K-2],mod-2)%mod)%mod<<"\n";
		ans=(ans+(fac[n-K]*fpow(fac[i]*fac[n-K-i]%mod,mod-2)%mod)*(fac[K+i-2]*fpow(fac[K-2],mod-2)%mod)%mod*calc(K,i)%mod)%mod;
//	cout<<ans<<"\n";
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		cin>>fa[0][i];
		vec[fa[0][i]].push_back(i);
	}
	dep[1]=1;
	for(int i=1;i<=m;i++)cin>>b[i],book[b[i]]=1;
	dfs(1);
//	for(int i=2;i<=m;i++){
//		book[b[i]]=1;
//		book[lca(b[i],b[i-1])]=1;
//		//3 5
//	}
//	for(int i=1;i<=n;i++)cout<<book[i]<<" ";
	/*
	3 5
	   1
	 2  3
	4 5
	*/
	
	
//	for(int i=1;i<=n;i++)K+=(book[i]==1);
	fac[0]=1;
	for(int i=1;i<=n*2;i++)fac[i]=fac[i-1]*i%mod;
	long long ans=calc2(n,K);
//	cout<<K<<"\n";
//	cout<<ans<<"\n";
	if(K<n)ans=(ans+(n-K)*calc2(n,K+1)%mod)%mod;
	cout<<ans<<"\n";
}
```

---

