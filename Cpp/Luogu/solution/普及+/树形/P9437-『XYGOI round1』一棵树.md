# 『XYGOI round1』一棵树

## 题目背景

java 今天带了一棵树到出题组，然后被不讲理的 MX 占为己有了。

## 题目描述

于是 MX 有一棵 $n$ 个节点的树，每个点上有一个数字 $a_i$。

定义一条路径 $(x,y)$ 的权值 $w(x,y)$ 为，从 $x$ 走到 $y$ 的最短路径上，所有节点上的数字顺次写下后得到的数。如，顺次经过写有数字 $3,21,0,5$ 的四个节点，那么这个路径的权值为 $32105$。

MX 想知道这棵树所有路径的权值之和，即 $\sum\limits_{x=1}^n\sum\limits_{y=1}^nw(x,y)$ 为多少。

答案可能很大，对 $998244353$ 取模。

## 说明/提示

### 样例解释

样例一解释：$1+12+123+2+21+23+3+32+321=538$。

样例二解释：$5+521+5210+21+215+210+0+021+0215=6418$。

### 数据范围  
**本题采用捆绑测试。**  

记 $V=\max\{a_i\}+1$。

|Subtask|分值|$n\le$|$V\le $|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|0|5|$1000$|$10$||
|1|15|$8000$|$10^9$||
|2|15|$10^6$|$10^9$|$p_i=i$|
|3|15|$10^6$|$10^9$|$p_i=1$|
|4|50|$10^6$|$10^9$||

对于 $100\%$ 的数据，$1\le n\le 10^6$，$0\le a_i<10^9$。

## 样例 #1

### 输入

```
3
1 2 3
1 2```

### 输出

```
538```

## 样例 #2

### 输入

```
3
5 21 0
1 2```

### 输出

```
6418```

## 样例 #3

### 输入

```
4
1 2 3 4
1 2 2
```

### 输出

```
1900```

## 样例 #4

### 输入

```
6
10 23 16 3 125 1
1 1 1 1 1
```

### 输出

```
7680868```

# 题解

## 作者：NaN_HQJ2007_NaN (赞：9)

换根 DP。

本蒟蒻最初没想到换根，把自己写自闭了...

定义 $f_u$ 为子树 $u$ 中的每个结点走到 $u$ 的贡献和，$l_u$ 为大于 $a_u$ 的最小的 $10$ 的幂次方数，$sum_u$ 为 $\sum\limits_{v\in son(u)}{f_v}$。

转移方程为：$f_u=l_u\cdot\sum\limits_{v\in son(u)}{f_v}+siz_u\cdot a_u$。

再定义 $g_u$ 为除去子树 $u$ 其他的所有点到 $fa_u$ 的贡献和。

转移方程为：$g_v=(g_u+sum_u-f_v)\cdot l_u+(n-siz_v)\cdot a_u$。

然后答案加上 $(g_v+sum_v)\cdot l_v+n\cdot a_v$。

复杂度 $O(n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,mod=998244353;
ll n,a[N],f[N],g[N],siz[N],sum[N],ans;
vector<int>adj[N];
ll get(ll x){
	if(x==0)return 10;
	ll res=1;
	while(x){res*=10;x/=10;}
	return res;
}
void dfs(int u,int lst){
	siz[u]=1;
	ll t=get(a[u]);f[u]=a[u];
	for(int i=0;i<adj[u].size();++i){
		int v=adj[u][i];if(v==lst)continue;
		dfs(v,u);siz[u]+=siz[v];f[u]=(f[u]+f[v]*t+siz[v]*a[u])%mod;sum[u]=(sum[u]+f[v])%mod;
	}
}
void dfs2(int u,int lst){
	ll tu=get(a[u]);
	for(int i=0;i<adj[u].size();++i){
		ll v=adj[u][i],tv=get(a[v]);if(v==lst)continue;
		g[v]=(g[u]+(sum[u]-f[v]+mod)%mod)%mod*tu+(n-siz[v])*a[u];g[v]%=mod;
		ans=(ans+(g[v]+sum[v])*tv+n*a[v])%mod;
		dfs2(v,u);
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;for(int i=1;i<=n;++i)cin>>a[i];
	for(int u=2;u<=n;++u){
		int v;cin>>v;
		adj[u].push_back(v);adj[v].push_back(u);
	}
	dfs(1,0);ans+=f[1];dfs2(1,0);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：xs_siqi (赞：9)

赛时解出了。思路好想，维护细节较多的换根 dp。这道题考验了对换根 dp 模型基本掌握。
 
## 正文：本题如何运用换根 dp

换根 dp 其实是有模板的。

我总结了一下，一般情况的换根 dp 就是的过程通常是两遍 dfs，并在写题的过程中思考以下问题：

- 两次 dfs 前先维护两次 dfs 需要的信息

- 第一遍维护第二次换根过程中需要维护的信息，以及以任意一个点为根（通常为了方便取 $1$ 号节点为根）如何得到原始 $f$ 值（即其原始方程）

- 第二遍换根的转移方程

- 两遍 dfs 后输出的值

我们尝试使用这个模板来解决这个问题。

### 这题为什么是换根 dp？

此题题意可以转化为：随意确定一个点为根节点，然后计算其他节点到根节点的长度和。于是可以用换根 dp 解决。

### dfs 前：两遍 dfs 前维护什么？

首先观察边权是如何得出的：两个节点**点权按顺序**拼起来。如何将两数拼起来？令后一个节点为 $x$，那么它的位数便是它对 $10$ 取对数。所以我们得出第一个需要维护的就是一个数对 $10$ **取对数**的值（当然，你也可以不维护，直接用系统自带函数一步得出也可以）。

回到“如何拼起来”的问题，令原有数为 $x$，要拼的数为 $y$，拼起来的代价**是 $x\times 10^{num(y)}+y$。** $num$ 函数是该数的位数。举个例子，将 $5$ 与 $6$ 拼起来，$6$ 的位数是 $1$，所以是 $5\times 10+6=56$。由此可见，我们**还需维护 $10$ 的次方倍。** 由数据范围可知，我们只需要维护到 $10^9$ 即可。

总结：维护 $10$ 的次方倍与各个数位数。

### 第一遍 dfs：维护什么？原始方程是什么？

首先我们明晰这样一点：每个点到根节点的总长度，可以转化为每条边的边权乘由几个点走过这条边。即计算贡献。

这样转化有什么妙处？可以向父亲转移状态了。

我们看到我们转化后，需要记录有几个点经过一条边，显然就是这个点是多少点的祖先，也就是这个点的 $size$。于是我们得出第一次 dfs 需要维护每个点的 $size$ 信息。

然后考虑原始转移方程。令 $f_u$ 为 $u$ 节点的所有孩子到 $u$ 节点的总路径长度之和，那我们可以得到以下方程：

$f_u=f_v\times 10^{num(u)}+p_u\times size_v$

解释一下这个方程：$u$ 是 $v$ 的父节点，$p_u$ 指的是 $u$ 节点的权值，$p_u\times size_v$ 表示有 $size_v$ 个数经过这条边。

总结：维护 $size$ 信息，并使用上述方程求得其他点（包括根节点，此题中点到自己本身也有距离）到根节点的距离之和。

### 第二次 dfs：如何运用维护的信息？方程是什么？

![](https://cdn.luogu.com.cn/upload/image_hosting/b7stz842.png)

如何列方程？我们从最简单的情况入手。如图是 $1$ 节点向 $2$ 节点下移的过程。

- 首先考虑节点 $2$ 的子树部分。我们发现我们需要节点 $4$ 的 $f$ 值作为换根后的总值。这个值在第一次 dfs 已经求过了，直接调用 $f_4$ 即可。

- 然后考虑节点 $2$ 的非其子树部分。有人可能认为可以直接调用 $f_3$ 的值，这是不可行的。请注意，**树不一定是二叉树**，假如是**菊花图**的情况，可以把这个解法卡到 $n^2$。

- 于是很自然能想到这个思路：将根节点的 $f$ 值减去 $2$ 好点的 $f$ 值。如图（图中算式有误，请手动在 $10\times f_1$乘号后加一个左括号，第一行最右边加上右括号），考虑最简单的情况，令 $f_2$ 为一位数，$f_1$ 也为一位数，那么除了 $f_2$ 以外的 $f$ 值显然是 $f_1-10\times f_2$。

两边 $f$ 值问题已经解决。现在我们解决换根对于边的**贡献问题。**

- 首先，$1$ 节点下所有节点**及它自己**少了红边。所以应为 $size_2\times p_u$。

- 其次，除了 $2$ 节点子树**以外所有节点**都多了红边，所以应为 $p_v\times (size_{rt}-size_v)$。

那么整个方程过程就结束了。然后总结以下就是这个方程：

$f_v=f_v+10^{num(v)}\times(f_u-f_v\times 10^{num(u)}-p_u\times size_v)+(p_u\times (size_{rt}-size_v))$。

### 两次 dfs 后：答案是什么？

$f$ 值表示每个节点以下的点（包括自身）到其距离。那么显然就是 $f$ 数组中所有元素的和。

### 需要注意的细节

考虑到本题数据较大，所以要时时注意**取模**操作。还有例如刚刚的部分换根方程的处理：

$(f_u-f_v\times 10^{num(u)}-p_u\times size_v)$

若时时取模，这个地方可能会变成负数。所以我们可以**直接加**模数，**不影响**取模后结果，即变成：

$(f_u+mod\times 5-f_v\times 10^{num(u)}-p_u\times size_v)$

取模后结果是**一致**的。

附代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int maxn=2e6+5;
const int mod=998244353;
int n,p[maxn],wei[maxn],ship[15],ans,f[maxn];
int fir[maxn],nxt[maxn],son[maxn],tot,q,siz[maxn];
inline void add(int x,int y){son[++tot]=y;nxt[tot]=fir[x];fir[x]=tot;}
inline void dfs1(int u,int fa){
	siz[u]=1;f[u]=p[u];//点到其本身也有距离
	for(int i=fir[u];i;i=nxt[i]){
		int v=son[i];
		if(v==fa)continue;
		dfs1(v,u);
		siz[u]+=siz[v];//维护size
		f[u]+=f[v]*ship[wei[u]]%mod+p[u]*siz[v]%mod,f[u]%=mod;}}
inline void dfs2(int u,int fa){
	for(int i=fir[u];i;i=nxt[i]){
		int v=son[i];
		if(v==fa)continue;
		f[v]=f[v]+(ship[wei[v]]%mod*((f[u]+mod*5)-f[v]*ship[wei[u]]%mod-p[u]*siz[v]%mod)%mod+(p[v]*(siz[1]-siz[v]))%mod)%mod;//只是刚刚推出来的方程多加了几个%mod
		f[v]%=mod;
		ans+=f[v],ans%=mod;
		dfs2(v,u);}}
signed main(){
	scanf("%lld",&n);
	ship[0]=1;
	for(int i=1;i<=13;i++)ship[i]=ship[i-1]*10,ship[i]%=mod;//shi p，10的几次方，不是ship小船
	for(int num,i=1;i<=n;i++){
		scanf("%lld",&p[i]);num=p[i];
		if(num==0)wei[i]=1;//wei就是位数
		else while(num)num/=10,wei[i]++;}
	for(int x,i=1;i<n;i++)scanf("%lld",&x),add(i+1,x),add(x,i+1);
	dfs1(1,0);dfs2(1,0);
	printf("%lld\n",(ans+f[1])%mod);//因为我的dfs过程只求除了f1以外的总和
	return 0;} 
```


## 后文：本题对换根 dp 的启示

本题只是在边权形式上进行了创新，增加细节，换根 dp 过程**本质是不变的。**

所以只要熟练掌握换根dp的常见技巧过程，以及提高细节处理能力，相信换根 dp 就是常规题了。

---

## 作者：Register_int (赞：6)

拆贡献，计算出 $a_i$ 分别在哪一位出现，乘上 $10$ 的幂累加。给每个点添加权值 $b_i$ 表示 $10^{a_i\text{的位数}}$。以每个点为根拆路径即可做到 $O(n^2)$。

考虑优化。设根为 $1$，$t_u$ 表示对于 $u$ 子树中的每个节点，以 $u$ 为开头它为结尾 $a_u$ 造成的贡献之和。容易得到有转移式：

$$t_u=1+\sum_{v\in \text{son}(u)}t_v\times b_v$$

之后考虑计算以 $u$ 为根时 $t_u$ 的值，设它为 $f_u$。我们需要加上另一棵子树的贡献，即从父亲 $fa_u$ 中去掉 $u$ 的贡献。可以得到转移式：

$$f_u=t_u+(f_{fa_u}-t_u\times b_u)\times b_{fa_u}$$

然而这只是结尾为 $u$ 的情况，我们还要计算经过 $u$ 且结尾不为 $u$ 的情况下，$a_u$ 造成的贡献。设其为 $g_u$，枚举起点在哪棵子树内或在 $u$ 子树外，则有：

$$g_u=(n-size_u)\times t_u+\sum_{v\in \text{son}(u)}size_v\times(f_u-t_v\times b_v)$$

答案即为 $\sum^n_{i=1}a_i\times(f_i+g_i)$，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int mod = 998244353;

struct node {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int s[MAXN];

ll a[MAXN], b[MAXN], f[MAXN], g[MAXN], t[MAXN];

// f: up, g: down

void dfs1(int u, int p) {
	f[u] = s[u] = 1;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v; if (v == p) continue;
		dfs1(v, u), s[u] += s[v];
		f[u] = (f[u] + b[v] * f[v] % mod) % mod;
	}
	t[u] = f[u];
}

int n; ll ans;

void dfs2(int u, int p) {
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v; if (v == p) continue;
		g[u] = (g[u] + s[v] * (f[u] - b[v] * f[v] % mod + mod) % mod) % mod;
		f[v] = (f[v] + b[u] * (f[u] - b[v] * f[v] % mod + mod) % mod) % mod, dfs2(v, u);
	}
	g[u] = (g[u] + (n - s[u]) * t[u] % mod) % mod;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		scanf("%lld", &a[i]), b[i] = 1;
		if (!a[i]) b[i] = 10;
		else for (x = a[i]; x; x /= 10, b[i] = b[i] * 10 % mod);
	}
	for (int i = 2, u; i <= n; i++) scanf("%d", &u), add(u, i), add(i, u);
	dfs1(1, 0), dfs2(1, 0);
	for (int i = 1; i <= n; i++) ans = (ans + a[i] * (f[i] + g[i]) % mod) % mod;
	printf("%lld", ans);
}
```

---

## 作者：huangrenheluogu (赞：5)

# P9437 换根dp

赛时第一次作出 C 题，感觉真的很好（虽然就是一道绿）。

树上的题，很容易发现是换根数形 dp 即可。

## 前置：逆元

$ax\equiv1\pmod p$，在本题中 $p$ 为素数，根据 [费马小定理](https://baike.baidu.com/item/%E8%B4%B9%E9%A9%AC%E5%B0%8F%E5%AE%9A%E7%90%86/4776158)，$x=a^{p-2}$。

然后除以 $a$ 就可以是乘上 $x(=a^{p-2})$，化除为乘。

## 正文
首先，处理出 $10$ 的幂，还有它的逆元，用于后面的运算。

可以先在 $1$ 点进行一遍暴力，求出**到 $1$ 点的路径的总和**。在走得时候，记录每一位对上面的贡献（就是总和+上一位的贡献，就是我代码中的 $f$）。不清楚的话，我们说换根的时候再讲。

接下来考虑换根。

![](https://cdn.luogu.com.cn/upload/image_hosting/gruook87.png)

从 $x$ 换到 $y$。（本来指向 $x$，现在指向 $y$，并且统计答案）

分成两类讨论。

- 在 $x$ 左边的贡献（包含 $x$）

  目标：加上 $a_y$。

1. 乘上 $10^z$，其中 $z$ 为 $a_y$ 的位数。

2. 加上 $y$。

- 在 $y$ 右边的贡献（包含 $y$）

  目标：去掉 $a_x$。

1. 减掉 $a_x$。

2. 除以 $10^z$，其中 $z$ 为 $a_x$ 的位数。**注意这里是乘上逆元。**

好了，现在考虑前面维护的东西。

肯定维护了贡献，由于 $y$ 是 $x$ 的儿子，我们可以很简单地维护 $y$ 的东西。我是维护了 $y$ 的子树（含 $y$）对 $fa_y$ 的贡献。

我的解法是：

```cpp
f[son[i]] = (tem * base[coun[x]] + a[x] * sz[son[i]]) % mod;
```

其中 $base_i$ 是处理的 $10$ 的幂次，$coun_i$ 是 $a_i$ 的位数，$tem$ 是 $son_i$ 返回的总和。

所以我们在换根的时候，就可以轻松求出上面两个讨论的总贡献了。

（$tot$ 是上一次的答案）

- $x$ 及其左边的贡献：
```cpp
tem = tot - f[son[i]];
```
解释一下求 $f_{son_i}$ 的时候为什么要不加上 $a_x$，因为这里的贡献是需要加上 $a_x$，而 $tot$ 里时有 $x$ 到 $x$ 自己的贡献，所以不用加。

然后我们处理总贡献的时候，这一部分就应该是：

```cpp
//tem2用来统计答案
tem2 += tem * base[coun[son[i]]] % mod/*第一步*/ + (n - sz[son[i]]) * a[son[i]] % mod/*第二步*/;
```

- $son_i$ 及其右边的贡献：

```cpp
f[son[i]]
```

然后进行计算。

```cpp
tem2 = f[son[i]] - (sz[son[i]]) * a[x];//去掉a[x]
tem2 = (tem2 % mod + mod) % mod;
tem2 = tem2 * ni[coun[x]] % mod;//除掉a[x]的位数
```

最后放上完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5, mod = 998244353;
int n, a[N], x, fir[N], nxt[N << 1], son[N << 1], base[11], fa[N], sz[N], ans, f[N], coun[N], tot, ni[N];
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void dfs(int x, int ff){
	fa[x] = ff, sz[x] = 1;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		sz[x] += sz[son[i]];
	}
}
inline int ksm(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod, y >>= 1; 
	}
	return res;
}
inline int calc(int x){
	int cnt = 0;
	while(x){
		cnt++;
		x /= 10;
	}
	return cnt ? cnt : cnt + 1;
}
inline int dfs2(int x){
	int res = 0, tem;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == fa[x]) continue ;
		tem = dfs2(son[i]);
		res += tem * base[coun[x]] % mod + a[x] * sz[son[i]];
		f[son[i]] = (tem * base[coun[x]] + a[x] * sz[son[i]]) % mod;
		res %= mod;
	}
	res += a[x];
	return res % mod;
}
inline void dp(int x, int tot){
	if(x != 1) ans += tot;
	int tem, tem2;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == fa[x]) continue; 
		tem = tot - f[son[i]];
		tem2 = f[son[i]] - (sz[son[i]]) * a[x];
		tem2 = (tem2 % mod + mod) % mod;
		tem2 = tem2 * ni[coun[x]] % mod;
		tem2 += tem * base[coun[son[i]]] % mod + (n - sz[son[i]]) * a[son[i]] % mod;
		tem2 = (tem2 % mod + mod) % mod;
		dp(son[i], tem2);
	}
}
signed main(){
	base[0] = 1;
	for(int i = 1; i <= 9; i++) base[i] = base[i - 1] * 10 % mod ;
	for(int i = 0; i <= 9; i++) ni[i] = ksm(base[i], mod - 2);
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), coun[i] = calc(a[i]);
	for(int i = 1; i < n; i++){
		scanf("%lld", &x);
		add(x, i + 1), add(i + 1, x);
	}
	dfs(1, 0);
	ans = dfs2(1);
	dp(1, ans);
	printf("%lld", ans % mod);
	return 0;
}
```

---

## 作者：Scorilon (赞：4)

首先这是一道很明显的换根 dp。

首先注意到要拼接数，所以我们可以先处理出 $num_i=10^{x}$，使得 $10^x > a_i > 10^{x-1}$，这样方便我们后面算贡献。

我们以这棵树为例子来推状态转移方程。

![](https://cdn.luogu.com.cn/upload/image_hosting/9vgrxy91.png)

先假设 $dp_u$ 表示以 $1$ 为根时，从 $u$ 的子树的点到 $u$ 的权值和。

那么 

$$dp_u=\sum_{v \in son_u} dp_v \times num_u+a_u \times siz_v$$

首先 $dp_v \times num_u$ 是把前面已经拼好的数扩大 $num_u$ 倍，然后 $a_u \times siz_v$ 是 $a_u$ 一共对包含它本身在内的子树节点数的贡献。

我们求出了以 $1$ 为根时的贡献值后，设 $f_u$ 表示以 $u$ 为根时的值。

那么我们可以分为两部分考虑：

1. 属于 $u$ 的子树的部分，那么这一部分很明显直接加上就可以，也就是 $dp_u$，例如上图我们已经求出了以 $1$ 为根时的值，然后我们要从节点 $1$ 转移到节点 $2$，那么属于节点 $2$ 的子树部分的贡献就是 $dp_2$。

2. 不属于 $u$ 的子树的部分，我们可以先利用 $f_{fa}-sum$ 求出 $fa$ 的子树中除去 $u$ 的贡献的值，其中 $sum$ 表示节点 $u$ 对它的父节点即 $fa$ 的贡献，根据我们上面的方程逆推回来可得 $sum=dp_u \times num_{fa} + a_{fa} \times siz_u$，然后再根据这个值来计算对 $u$ 的贡献，那么还是带入上面的方程可得对 $u$ 的贡献为 $(f_{fa}-sum) \times num_{u} + a_u \times (siz_1 - siz_{u})$.

因此状态转移方程为

$$f_u=dp_u+num_u \times (f_{fa}-(dp_u \times num_{fa}+a_{fa} \times siz_{u})) + a_u \times (siz_1-siz_u)$$

最后的答案就是 

$$\sum_{i=1}^{n} f_i$$

```cpp
#include <cstdio>

typedef long long ll;

const ll N=1e6+5;
const ll mod=998244353;

ll mo(ll x) {//取模，注意负数 
	return (x%mod+mod)%mod;
}

struct edge {
	ll v,nxt;
}G[N<<1];
ll h[N],idx;

void add(ll u,ll v) {
	G[++idx].v=v;
	G[idx].nxt=h[u];
	h[u]=idx;
}

ll n,a[N];
ll siz[N],num[N];
ll dp[N],f[N];

void dfs1(ll x,ll fa) {
	siz[x]=1,dp[x]=a[x];
	for(ll i=h[x];i;i=G[i].nxt) {
		ll v=G[i].v;
		if(v==fa) continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		dp[x]=mo(dp[x]+mo(mo(dp[v]*num[x])+mo(siz[v]*a[x])));
	}
}

void dfs2(ll x,ll fa) {
	if(x!=1) {
		ll t1=mo(f[fa]-mo(mo(dp[x]*num[fa])+mo(a[fa]*siz[x])));
		f[x]=mo(mo(mo((siz[1]-siz[x])*a[x])+mo(t1*num[x]))+dp[x]);
	}
	for(ll i=h[x];i;i=G[i].nxt) {
		ll v=G[i].v;
		if(v==fa) continue;
		dfs2(v,x);
	}
}

int main() {
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		num[i]=10;
		while(num[i]<=a[i]) num[i]*=10;
	}
	for(ll i=2;i<=n;i++) {
		ll x;
		scanf("%lld",&x);
		add(x,i);add(i,x);
	}
	dfs1(1,0);
	f[1]=dp[1];
	dfs2(1,0);
	ll ans=0;
	for(ll i=1;i<=n;i++) ans=mo(ans+f[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：2018ljw (赞：2)

~~不出预料的板子 rush。~~

出题人的点分最大点耗时约 1.6s。

**为了方便表示，在本篇题解中，$|x|$ 表示数字 $x$ 的长度（字符个数），所有路径均为简单路径。**

考虑统计每个点的贡献，不妨钦定我们当前统计贡献的点为根。

对于一条过根节点的路径 $x\to root\to y$，显然 $x\to root$ 的部分不会对根产生贡献，因此只需要处理出 $root\to y$ 的影响。  
枚举终点所在子树，我们希望能快速求出所有 $root\to y$ 的 $10^{k}$ 之和。

设 $dp_{x}$ 表示考虑以 $x$ 为起点，终点在 $x$ 子树内的所有路径，$x$ 产生的 $10^k$ 贡献之和，易得 $dp_{x}=1+\sum 10^{|a_y|}dp_{y}$。换句话说，若记 $sum_x$ 表示 $x$ 到根的数字长度之和，则 $dp_x=\sum\limits_{y\in subtree_x}10^{sum_y-sum_x}$。

枚举根节点的子节点 $y$，可得以 $y$ 子树内点为终点时，根节点的贡献。因此以其它点为终点时，根节点贡献和为 $a_{rt}\times\sum\limits_{y\in son_{rt}}10^{|a_y|}\times dp_y\times(n-size_y)$，单独加上路径以根节点为终点的情况即可。

不难发现两项都很好换根，因此直接换根即可。

复杂度 $O(n)$。

各部分分的 std 和一些其他做法可以在[这里](https://www.luogu.com.cn/paste/2dvjdnl0)看。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
const int mod=998244353;
using namespace std;
int n,a[1000001],len[1000001];
long long dp[1000001],sz[1000001],pw[10];
int hed[1000001],net[2000001],ver[2000001],tot;
void add(int x,int y){
	ver[++tot]=y;
	net[tot]=hed[x];
	hed[x]=tot;
}
void dfs0(int x,int fr){
	sz[x]=1;dp[x]=1;
	int i;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(y==fr)continue;
		dfs0(y,x);
		sz[x]+=sz[y];
		dp[x]+=dp[y]*pw[len[y]]%mod;
	}
	dp[x]%=mod;
}
long long res;
void dfs1(int x,int fr){
	int i;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		res+=dp[y]*(n-sz[y])%mod*a[x]%mod*pw[len[y]]%mod;
		res%=mod;
	}res+=1ll*a[x]*n;res%=mod;
	long long sd=dp[x];
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(y==fr)continue;
		dp[x]+=mod-dp[y]*pw[len[y]]%mod;
		dp[x]%=mod;
		sz[x]=n-sz[y];
		sz[y]=n;
		dp[y]+=dp[x]*pw[len[x]]%mod;
		dp[y]%=mod;
		dfs1(y,x);
		dp[x]=sd;
	}
}
int ws(int x){
	if(!x)return 1;
	int res=0;
	while(x)res++,x/=10;
	return res;
}
int main(){
	int i,j;
	pw[0]=1;for(i=1;i<=9;i++)pw[i]=pw[i-1]*10%mod;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		len[i]=ws(a[i]);
	}
	for(i=2;i<=n;i++){
		int x;
		scanf("%d",&x);
		add(x,i);
		add(i,x);
	}
	dfs0(1,0);
	dfs1(1,0);
	printf("%lld",res);
}
```
## 后记

这题本来有一些加强版。


![](https://cdn.luogu.com.cn/upload/image_hosting/0pcfs97n.png)

~~所以加强版就只能留着祸害学弟了。~~

---

## 作者：lyas145 (赞：1)

题目在[这里](https://www.luogu.com.cn/problem/P9437)。

一不小心[抢了一个最优解](https://www.luogu.com.cn/record/list?pid=P9437&orderBy=1&status=&page=1)，不过以后应该会有更快的。

# 解题思路

其实对我这种脑袋不灵光的人，最重要的是怎么看出来这题是一道换根 dp 题。

一眼看上去，直觉告诉我 dp 并不可行，但是直觉叕叕叕错了。~~早知道就不听直觉的了。~~

求 $\sum\limits_{x=1}^n\sum\limits_{y=1}^n w(x,y)$ 这个东西，其实也相当于 $\sum\limits_{x=1}^n\sum\limits_{y=1}^n w(y,x)$。我们以节点 $x$ 为起点或终点，求出 $\sum\limits_{y=1}^n w(x,y)$ 或 $\sum\limits_{y=1}^n w(y,x)$，再把这些东西加起来就是答案了，这像啥？换根 dp。

出题人在特殊性质方面搞得挺好。

$p_i=i$ 说明数据中树会是一条链；$p_i=1$ 说明数据中树会是一颗菊花。

平常做有关树的题其实也该思考一下树是一条链或菊花等特殊树的情况。

对于特殊的树，我们在这题主要研究菊花。

## 菊花的情况

$\sum\limits_{i=2}^n(w(1,i)+w(i,1))+\sum\limits_{i=1}^n w(i,i)$ 怎么求我就不说了，这 $\mathcal{O}(n)$ 就直接求出来了。

设 $u,v$ 为菊花上的两个节点且 $u\ne v,u\ne 1,v\ne 1$。

设 $a_i$ 的长度为 $len_i$。

我们把 $u$ 定死为起点，试着求出 $\sum\limits_{v=2,v\ne u}^n w(u,v)$，也就是   
$\sum\limits_{v=2,v\ne u}^n(a_u\times 10^{len_1+len_v}+a_1\times 10^{len_v}+a_v)\\
=(n-2)\times a_u\times 10^{len_1+len_v}+(n-2)\times a_1\times 10^{len_v}+\sum\limits_{v=2,v\ne u}^n a_v$。

可以发现：由于 $len_v$ 我们并不确定，所以我们也无法确定 $(n-2)\times a_u$ 和 $a_1$ 具体需要乘上 $10$ 的几次方，除非 $\mathcal{O}(n)$ 挨个扫一遍，但这就和暴力没啥区别了。

我们把 $u$ 定死为终点，试着求出 $\sum\limits_{v=2,v\ne u}^n w(v,u)$，也就是   
$\sum\limits_{v=2,v\ne u}^n(a_v\times 10^{len_1+len_u}+a_1\times 10^{len_u}+a_u)\\
=\sum\limits_{v=2,v\ne u}^n a_v\times 10^{len_1+len_u}+(n-2)\times a_1\times 10^{len_u}+(n-2)\times a_u$。

可以发现：上面有些东西是可以提前预处理出来的。

设 $S=\sum\limits_{i=1}^n a_i$，那么上式可变成 $(S-a_1-a_u)\times 10^{len_1+len_u}+(n-2)\times a_1\times 10^{len_u}+(n-2)\times a_u$，再预处理一下 $10^x$ 就可以 $\mathcal{O}(n)$ 的做了。

这个很简单，代码就不放了。~~主要是懒得写。~~

## 一般情况

上面把节点 $u$ 定死为终点的做法为我们搞出正解带来了希望。

为了方便讲述，令 $tree(u)$ 表示以 $u$ 为根节点的子树中所有节点（包括 $u$）的集合，$siz_u$ 表示以 $u$ 为根节点的子树的大小（也就是节点数量，当然也包括 $u$）。

设 $g_u=\sum\limits_{i\in tree(u)} w(i,u)$。

转移方程为：

$$g_u=a_u+\sum\limits_{v\in son(u)}(siz_v\times a_u+10^{len_u}\times g_v)$$

应该很好理解。$g_v=\sum\limits_{x\in tree(v)} w(x,v)$，我们需要在所有 $w(x,v)$（一共 $siz_v$ 个）后面接上一个 $a_u$ 才能变成 $w(x,u)$，所以是加上 $\sum\limits_{v\in son(u)}(siz_v\times a_u+10^{len_u}\times g_v)$。别忘了加上 $a_u$！

然后是换根。

设 $f_u=\sum\limits_{i=1}^n w(i,u)$。

我们先以 $1$ 为根，则 $f_1=g_1$。

那么转移方程为（$v\in son(u)$）：

$$f_v=(f_u-(siz_v\times a_u+10^{len_u}\times g_v))\times 10^{len_v}+(n-siz_v)\times a_v+g_v$$

对于节点 $x$（$x\notin tree(v)$），要在 $w(x,u)$ 后接上一个 $a_v$，于是就得加上 $(f_u-(siz_v\times a_u+10^{len_u}\times g_v))\times 10^{len_v}+(n-siz_v)\times a_v$；对于节点 $y$（$y\in tree(u)$），就是 $\sum\limits_{y\in tree(v)} w(y,v)$ 也就是 $g_v$。

最终答案就是 $ans=(\sum\limits_{i=1}^n f_i)\bmod 998244353$。

注意随时取模，不要直接抄上面的方程。

# 码儿

```cpp
#include<bits/stdc++.h>
#define qwq return
using namespace std;
typedef long long ll;
const int N=1e6+5,M=N<<1,P=998244353;
int n,mx,ans;
int f[N],g[N];
int a[N],len[N],p[N*9],siz[N];
int h[N],e[M],ne[M],idx=1;
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while (!isdigit(c)) {f=(c=='-'?-1:1);c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	qwq x*f;
}
void add(int a,int b) {
	e[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
void _dfs(int u,int fa) {
	siz[u]=1;
	g[u]=a[u];
	for (int i=h[u];i;i=ne[i]) {
		int v=e[i];
		if (v==fa) {continue;}
		_dfs(v,u);
		siz[u]+=siz[v];
		g[u]=(g[u]+(1ll*siz[v]*a[u]%P+1ll*p[len[u]]*g[v]%P)%P)%P;
	}
}
void dfs(int u,int fa) {
	ans=(ans+f[u])%P;
	for (int i=h[u];i;i=ne[i]) {
		int v=e[i];
		if (v==fa) {continue;}
		ll t=(f[u]-(1ll*siz[v]*a[u]%P+1ll*p[len[u]]*g[v]%P)%P+P)%P;
		f[v]=((1ll*t*p[len[v]]%P+1ll*(n-siz[v])*a[v]%P)%P+g[v])%P;
		dfs(v,u);
	}
}
int main() {
	n=read();
	for (int i=1;i<=n;i++) {
		a[i]=read();
		len[i]=1;
		for (int x=a[i];x>9;x/=10) {len[i]++;}
		mx=max(mx,len[i]);
	}
	p[0]=1;
	for (int i=1;i<=mx;i++) {p[i]=10ll*p[i-1]%P;}
	for (int i=1;i<n;i++) {
		int a=read(),b=i+1;
		add(a,b);
		add(b,a);
	}
	_dfs(1,0);
	f[1]=g[1];
	dfs(1,0);
	printf("%d\n",ans);
	qwq 0;
}
```

A 了这题之后可以去做一下[这题](https://www.luogu.com.cn/problem/P10974)，看出来是换根 dp 题很重要，并且这题细节挺多。

Thanks for reading！

---

## 作者：樱雪喵 (赞：1)

## Description

给定一棵树，每个点上有权值 $a_i$。定义路径 $(x,y)$ 的权值为 $w(x,y)=\overline{a_x...a_y}$。  
求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n w(i,j)$。

$1\le n\le 10^5, 0\le a_i\le 10^9$。

## Solution

### sub 0/1
暴力。时间复杂度 $O(n^2)$。

### sub 2 
设 $f_i$ 表示 $\sum\limits_{j=1}^i w(j,i)$，$len_i$ 表示 $a_i$ 的位数。  
那么 $f_i=f_{i-1}\times 10^{len_i}+a_i\times i$。则对于所有 $i<j$，路径权值和为 $\sum\limits_{i=1}^n f_i$。  
注意 $w(i,j)\neq w(j,i)$，反方向再做一遍即可。


### sub 3
路径长度最多为 $3$，其中长度为 $1$ 或 $2$ 都可以简单地求出。  
考虑长度为 $3$ 的路径，形如 $x\rightarrow 1 \rightarrow y(x\neq 1,y\neq 1)$，该路径的权值为 $a_x \times 10^{len_1+len_y}+ a_1\times 10^{len_y}+ a_y$。  
所有以 $y$ 为终点的路径权值和为 $10^{len_1+len_y}\times \sum a_x+(n-2) a_1\times 10^{len_y}+(n-2)a_y$。枚举终点，时间复杂度 $O(n)$。

### sub 4
树形 dp。设 $f_u$ 表示以子树 $u$ 内所有点为起点，终点为 $u$ 的权值和。  
类似于 sub 2，得到转移 $f_u=(\sum\limits_{v\in son_u} f_v)\times 10^{len_u} + a_u\times siz_u$。  
直接 dp 的时间复杂度为 $O(n^2)$。  
观察到 $siz_u$ 和 $f_u$ 都是容易换根的，不用枚举根节点。复杂度 $O(n)$。  

tips. 注意当 $a_i=0$ 时，$len_i=1$。


---

## 作者：Svemit (赞：1)

赛时一眼换根 dp，然后调调调了大概 1h+。

[题目传送门](https://www.luogu.com.cn/problem/P9437)

[更好的阅读体验](https://www.cnblogs.com/Svemit/p/17607282.html)

### 什么是换根 dp

在大多数树形 dp 中，我们只考虑对根的贡献，而一部分题目需要算出对所有点的贡献，一个比较显然的做法是对每个点都跑一次树形 dp，但是大大增加了时间复杂度，是我们不能接受的。

树形 dp 中的换根 dp 问题又被称为二次扫描，通常不会指定根结点，并且根结点的变化会对一些值，例如子结点深度和、点权和等产生影响。

换根 dp 的常用套路钦定某一个点为根，然后从根开始进行两次 dfs，第一次记录自己子树内中的节点对自己的贡献，第二次记录不属于自己子树中的点对自己的贡献。

### Solution
不妨钦定 1 为根。

考虑令 $f_u = \sum\limits_{v \in subtree(u)} w(v, u)$，$g_u = (\sum\limits_{v \notin subtree(u)} w(v, u)) + w_u$。为什么要加上 $w_u$？是为了方便转移（~~不加好像也不是很麻烦~~）。

首先我们要实现一个位数的函数。

```cpp
LL mylog(LL v) {
	if(v == 0) return 10;
	int res = 0;
	while(v) res ++, v /= 10;
	return pow(10, res);
} 
```

#### 计算 $f$ 数组

考虑从儿子 $v$ 转移到 $u$，显然为 $f_v \times mylog(w_u) + siz_v  \times w_u$。

得到 $f_u = (\sum\limits_{v \in subtree(u)} f_v) \times mylog(w_u) + w_u \times siz_u$。

```cpp
void dfs1(int u, int fa) {
	siz[u] = 1;
	for(auto v : e[u])
		if(v != fa)	{
			dfs1(v, u);
			siz[u] += siz[v];
			f[u] = (f[u] + f[v]) % mod;
		}
	f[u] = (f[u] * mylog(w[u]) % mod + w[u] * siz[u] % mod) % mod;
}
```

#### 计算 $g$ 数组
如何计算子树外的点对自己的贡献呢？

不妨先想想从根节点转移到第二层节点。

$1$ 转移到 $u$。

先算出除 $subtree(u)$ 外的点对 $1$ 的贡献，显然为 $f_1$ 减去 $u$ 对 $1$ 的贡献 $f_u \times mylog(w_1) + siz_u \times w_1$。

再考虑 $u$ 对儿子 $v$ 的贡献，为 $f_u + g_u$ 减去 $v$ 对 $u$ 的贡献，再把这些继续用计算 $f$ 的方法转移到 $v$ 上去。
```cpp
void dfs2(int u, int fa) {
	for(auto v : e[u])
		if(v != fa)	{
			g[v] = ((f[u] + g[u] - val(v, u) - w[u]) % mod * mylog(w[v]) % mod + (siz[1] - siz[v] + 1) % mod * w[v] % mod) % mod;
			dfs2(v, u);
		}
}
```

AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5, INF = 0x3f3f3f3f;
const LL mod = 998244353;
int n, m;
LL w[N];
vector<int> e[N];
LL f[N], g[N], siz[N];
LL mylog(LL v) {
	if(v == 0) return 10;
	int res = 0;
	while(v) res ++, v /= 10;
	return pow(10, res);
} 
LL val(int u, int v) {
	return (f[u] * mylog(w[v]) + siz[u] * w[v]) % mod;
}
void dfs1(int u, int fa) {
	siz[u] = 1;
	for(auto v : e[u])
		if(v != fa)	{
			dfs1(v, u);
			siz[u] += siz[v];
			f[u] = (f[u] + f[v]) % mod;
		}
	f[u] = (f[u] * mylog(w[u]) % mod + w[u] * siz[u] % mod) % mod;
}
void dfs2(int u, int fa) {
	for(auto v : e[u])
		if(v != fa)	{
			g[v] = ((f[u] + g[u] - val(v, u) - w[u]) % mod * mylog(w[v]) % mod + (siz[1] - siz[v] + 1) % mod * w[v] % mod) % mod;
			dfs2(v, u);
		}
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> w[i];
    for(int i = 2; i <= n; i ++) {
    	int p;
    	cin >> p;
    	e[p].push_back(i), e[i].push_back(p);
  	}
  	dfs1(1, 0);
  	g[1] = w[1];
  	dfs2(1, 0);
  	LL res = 0;
  	for(int i = 1; i <= n; i ++)
  		res = (res + f[i] + g[i] - w[i]) % mod;
  	cout << res << '\n';
    return 0;
}
```

---

## 作者：Usada_Pekora (赞：1)

简单 dp。

不妨设 $f_i$ 表示 $i$ 的子树里所有点走到 $i$ 的答案。

我们令 $\operatorname{join}(x,y)$ 表示把 $x,y$ 连起来后的值。

于是 $f_u=\sum\limits_{(u,v)\in E}\operatorname{join}(f_v,a_u)$，也就是从 $u$ 的所有儿子 $v$ 统计的所有答案再往上走一步到 $u$。

现在已经有了一个 $O(n^2)$ 的暴力，那就是把每个点作为根都这样 DP 一次。

考虑换根。

令 $h_u$ 表示以 $u$ 为根时的答案，我们先以 $1$ 为根做一次上面的 DP，那么 $h_1=f_1$。

想一下换根要处理哪些东西：原有的子树的贡献，以及把 $v$ 原来子树之外的点变成它的子树的贡献。

原有子树的贡献就是 $f_v$，这个不说了。

子树之外的点走到 $v$ 的贡献，就是 $\operatorname{join}(h_u-\operatorname{join}(f_v,a_u),a_v)$，即：除了 $v$ 子树里所有点先走到 $u$，然后再走到 $v$。

那么便做完了，$\operatorname{join}$ 需要先处理每个数的位数。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, mod = 998244353;
int n, a[N], siz[N], f[N], h[N], lg[N], powt[18], ans;
vector<int> g[N];
inline int mod_add(int x, int y) {
	return (x += y) >= mod ? (x - mod) : (x);
}
inline void dfs1(int u, int rt) {
	f[u] = a[u], siz[u] = 1;
	for (int v : g[u]) {
		if (v != rt) {
			dfs1(v, u);
			siz[u] += siz[v];
			f[u] = mod_add(f[u], mod_add(1ll * powt[lg[u]] * f[v] % mod, 1ll * siz[v] * a[u] % mod));
		}
	}
}
inline void dfs2(int u, int rt) {
	ans = mod_add(ans, h[u]);
	for (int v : g[u]) {
		if (v != rt) {
			int up = mod_add(1ll * mod_add(h[u], mod - mod_add(1ll * f[v] * powt[lg[u]] % mod, 1ll * a[u] * siz[v] % mod)) * powt[lg[v]] % mod, 1ll * (n - siz[v]) * a[v] % mod);
			int dwn = f[v];
			h[v] = mod_add(up, dwn);
			dfs2(v, u);
		}
	}
}
inline int read(int &x) {
	char ch = getchar(), res = 0;
	while (!isdigit(ch))
		ch = getchar();
	while (isdigit(ch))
		res++, x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return res;
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	read(n);
	for (int i = 1; i <= n; i++)
		lg[i] = read(a[i]);
	powt[0] = 1;
	for (int i = 1; i < 18; i++)
		powt[i] = 10ll * powt[i - 1] % mod;
	for (int i = 2; i <= n; i++) {
		int u = 0;
		read(u);
		g[i].emplace_back(u), g[u].emplace_back(i);
	}
	dfs1(1, 0);
	h[1] = f[1];
	dfs2(1, 0);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：CuCl4Loliko (赞：1)

## 题意

定义路径权值 $w(x,y)$ 为从 $x$ 节点到 $y$ 节点路径上的数字首位相连得到的数字，给出一棵树，求树上任意两个节点间的路径权值之和。

## 暴力

直接枚举路径的两个端点，暴力走两者之间的路径，统计答案。~~期望得分 0pts~~。

## 正解

考虑换一种方式统计路径权值和。

如果一个节点 $u$ 在经过之前，前面已经走了 $x$ 位数字，那么这个节点会对答案产生 $a_u \times 10^x$ 的贡献。可以在树上一边 DP，一边计算每个节点对答案的贡献。

定义 $x$ 为节点 $u$ 的权值的位数，$cnt_u$ 为 $10^x$。
 
下面进行分类讨论。

#### 一、路径起点位于子树内

定义 $f_u$ 为以节点 $u$ 子树内所有节点出发经过数字位数的贡献之和，即子树内所有上文提到的 $10^x$ 之和。

对于 $u$ 节点的一个儿子 $v$，因为从子树内出发的每条路径都有子树外节点数个终点，即 $n - size_v$，那么显然其对 $u$ 节点的贡献为

$$ a_u \cdot f_v \cdot cnt_v \cdot (n - size_v) $$

$f$ 数组的转移为

$$ f_u = \sum_{v \in u} f_v \cdot cnt_v $$

最后还需要计算以节点 $u$ 自身为起点的贡献为

$$ a_u \cdot (n - size_u - 1) $$

#### 二、路径起点位于子树外

类似于上一种情况，定义 $g_u$ 为以节点 $u$ 子树外所有节点出发经过数字位数的贡献之和。

相似的，这些路径对节点 $u$ 的贡献为

$$ (g_u + 1) \cdot a_u \cdot size_u $$

加一是因为存在以 $u$ 自身为起点，终点在子树内的情况。

$g$ 数组的转移是通过当前的子树减去儿子的子树来转移到儿子

$$ g_v = g_u + f_u - f_v \cdot cnt_v $$

上述操作通过换根 DP 进行求解。

因为以 $u$ 为起点且 $u$ 为终点的情况计算了两次，所以最后将所有贡献求和再减去所有节点的权值和才是答案，答案很大，能取模的地方都要取模。总时间复杂度为 $O(n)$。

## 代码

赛时写的代码，有点丑。。。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5,MOD=998244353;
struct egde{
	int to,nxt;
}e[maxn<<1];
int head[maxn],_;
void adde(int u,int v)
{
	e[++_].nxt=head[u];
	e[_].to=v;
	head[u]=_;
}

int fa[maxn],siz[maxn],w[maxn],a[maxn],cnt[maxn];
int n,ans;

int wei(int x)
{
	if(x==0) return 10;
	int res=1;
	while(x)
	{
		res*=10;
		x/=10;
	}
	return res%MOD;
}

void dfs1(int u,int f)
{
	fa[u]=f;
	w[u]=siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		ans=(ans+w[v]*cnt[v]%MOD*a[u]%MOD*(n-siz[v])%MOD)%MOD;
		w[u]=(w[u]+w[v]*cnt[v]%MOD)%MOD;
	}
	ans=(ans+a[u]*(n-siz[u]+1)%MOD)%MOD;
	return;
}

void dfs2(int u,int c)
{
	ans=(ans+(c+1)*a[u]%MOD*siz[u]%MOD)%MOD;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[u]) continue;
		int t=(w[u]-w[v]*cnt[v]%MOD+MOD)%MOD;
		t=(t+c)%MOD*cnt[u]%MOD;
		dfs2(v,t);
	}
	return;
}

signed main()
{
	int tt=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),tt=(tt+a[i])%MOD;
	for(int i=1;i<=n;i++)
		cnt[i]=wei(a[i]);
	for(int i=1;i<n;i++)
	{
		int v;
		cin>>v;
		adde(i+1,v);
		adde(v,i+1);
	}
	dfs1(1,0);
	dfs2(1,0);
	cout<<(ans-tt+MOD)%MOD<<endl;
	return 0;
}
```

---

## 作者：一只小咕咕 (赞：0)

[也许更好的阅读体验](https://www.cnblogs.com/yzxgg/p/18317716)

明显的换根 dp，感觉是道不错的换根 dp 练习题。
### 题意
一棵 $n$ 个节点的树，点带权，定义 $w(x,y)=\overline {a_x\dots a_y}$ 。

求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}w(i,j)\bmod 998244353$。
### 思路

我们不妨先求出 $i=1$ 时的 $\sum w(i,j)$，再求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}w(i,j)$。

设 $f_u$ 为其子树每个点走到 $x$ 的总贡献，定义 $\operatorname{get}(a_u)$ 为 $a_u$ 的位数，不难得出转移方程：
$$
f_u=\sum\limits_{v\in son} f_v \times \operatorname{get}(a_u)+size_u\times a_x
$$
这样我们就可以求出 $i=1$ 时的 $\sum w(i,j)$。朴素的，我们可以直接求 $n$ 次得到最终的答案，但是这样 $\mathcal{O(n^2)}$ 的复杂度是不能接受的。

从 $i=1$ 推到整棵树，考虑换根 dp，发现这几个条件都很好换根转移。

具体的，我们设 $g_u$ 为整棵树走到 $u$ 的贡献。考虑一个节点，假设我们已经得知了其父节点的 $g$，并且也得知了其子树内点的贡献，所以剩余需要求出子树外的答案。

子树外节点到其父节点的贡献和为其父节点的 $g$ 减去此节点及其子树对父节点的贡献，而子树外节点到其本身的贡献都比父节点多个本身，所以需要再乘一个 $10^{\mid a_x \mid}$。形式化的：

$$
g_u=(g_{fa}-(f_u\times \operatorname{get}(a_{fa})+size_x\times a_{fa}))\times \operatorname{get}(a_{fa})+(n-size_u)\times a_u+f_u
$$

答案即为 $\sum g$，复杂度 $\mathcal{O(n)}$，注意开 `long long` 和一步一模防止爆炸。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+5;
const int mod=998244353;
inline int read();
int n,a[N],cnt,head[N];
int f[N],size[N],g[N],ans;
struct E{
	int to,next,w;
}edge[N<<1];
void add(int u,int v)
{
	edge[++cnt].next=head[u];
	edge[cnt].to=v;
	head[u]=cnt;
}
int get(int x)
{
	if(x==0) return 10;
	int cnt=0;
	while(x>=1)
	{
		x/=10;
		cnt++;
	}
	return pow(10,cnt);
}
void dfs0(int x,int fa)
{
	size[x]=1;
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fa) continue;
		dfs0(to,x);
		f[x]=(f[x]+f[to]*get(a[x]))%mod;
		size[x]+=size[to];
	}
	f[x]=(f[x]+size[x]*a[x])%mod;
}
void dfs(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		int to=edge[i].to;
		if(to==fa) continue;
		g[to]=(((g[x]-(f[to]*get(a[x])%mod+a[x]*size[to])%mod)*get(a[to]))%mod+((n-size[to])*a[to])%mod+f[to])%mod;
		dfs(to,x);
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read(); 
	}
	for(int i=1;i<n;i++)
	{
		int x;
		x=read();
		add(x,i+1);
		add(i+1,x);
	}
	dfs0(1,0);
	g[1]=f[1];
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		ans=(ans+g[i])%mod; 
	}
	printf("%lld",ans);
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		x=(x<<1)+(x<<3)+(ch&15);
		ch=getchar();
	}
    return x*f;
}
```

---

## 作者：船酱魔王 (赞：0)

# P9437 『XYGOI round1』一棵树 题解

## 题意回顾

一棵 $ n $ 个结点的树，点带权，从 $ x $ 到 $ y $ 的唯一最短路径上所有权值数字前后相连组成的数记为 $ w(x,y) $，你需要求出 $ \sum_{x=1}^{n}{\sum_{y=1}^{n}{w(x,y)}} $ 对 $ 998244353 $ 取模的值。

$ n \le 10^6 $，$ a_i < 10^{9} $

## 分析

首先，我们把答案拆分成对于每个结点 $ y $ 求出 $ \sum_{x=1}^{n}{w(x,y)} $ 的值 $ ans_y $，再求 $ \sum_{y=1}^{n}{ans_y} $。

我们定义一个点 $ y $ 的子树（含本身）对其造成的答案贡献为 $ dn_y $，大于这个数的最小 $ 10 $ 的整次方数值记为 $ wei_y $，子树大小记为 $ sz_y $，显然有：

$$ dn_{y}=\sum_{x \in son}{dn_{x}} \times wei_{y}+sz_{y} \times a_y $$

我们**从下而上**的求出 $ dn_{y} $。

考虑一个结点的答案，分成子树内和子树外两部分，子树内已经求出，我们需要求出子树外答案。子树外的所有点到他的权值都比到他的父结点多一个他本身，而子树外的结点到父结点的权值由父结点的答案减去他对父结点的贡献即可，形式化地讲，即为：

$$ ans_{y}=(ans_{fa_y}-(dn_y \times wei_{fa_y}+sz_y \times a_{fa_y})) \times wei_y + (sz_1 - sz_y) \times a_y + dn_y $$

注意 ```long long``` 和取模。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int n;
int a[N];
int wei[N];
int sz[N];
long long dn[N];
long long ans[N];
vector<int> g[N];
void pre_dfs(int u, int fath) {
	for(int i = 0; i < g[u].size(); i++) {
		if(g[u][i] == fath) {
			continue;
		}
		pre_dfs(g[u][i], u);
		dn[u] += dn[g[u][i]];
		sz[u] += sz[g[u][i]];
	}
	sz[u]++;
	dn[u] %= mod;
	dn[u] = dn[u] * wei[u] + (long long)sz[u] * a[u];
	dn[u] %= mod;
}
void dfs(int u, int fath) {
	if(u != 1) {
		long long t1 = ans[fath] - (dn[u] * wei[fath] % mod + sz[u] * a[fath] % mod);
		t1 = (t1 % mod + mod) % mod;
		long long t2 = t1 * wei[u] % mod + (sz[1] - sz[u]) * a[u] % mod;
		t2 = (t2 % mod + mod) % mod;
		ans[u] = ((t2 + dn[u]) % mod + mod) % mod;
	}
	for(int i = 0; i < g[u].size(); i++) {
		if(g[u][i] == fath) {
			continue;
		}
		dfs(g[u][i], u);
	}
}
signed main() {
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		wei[i] = 10;
		while(wei[i] <= a[i]) {
			wei[i] *= 10;
		}
	}
	int x, y;
	for(int i = 2; i <= n; i++) {
		scanf("%lld", &x);
		g[i].push_back(x);
		g[x].push_back(i);
	}
	pre_dfs(1, 0);
	ans[1] = dn[1];
	dfs(1, 0);
	long long sum = 0;
	for(int i = 1; i <= n; i++) {
		sum = (sum + ans[i]) % mod;
	}
	cout << sum << endl;
	return 0;
}
```

---

