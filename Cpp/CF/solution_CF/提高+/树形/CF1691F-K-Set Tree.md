# K-Set Tree

## 题目描述

You are given a tree $ G $ with $ n $ vertices and an integer $ k $ . The vertices of the tree are numbered from $ 1 $ to $ n $ .

For a vertex $ r $ and a subset $ S $ of vertices of $ G $ , such that $ |S| = k $ , we define $ f(r, S) $ as the size of the smallest rooted subtree containing all vertices in $ S $ when the tree is rooted at $ r $ . A set of vertices $ T $ is called a rooted subtree, if all the vertices in $ T $ are connected, and for each vertex in $ T $ , all its descendants belong to $ T $ .

You need to calculate the sum of $ f(r, S) $ over all possible distinct combinations of vertices $ r $ and subsets $ S $ , where $ |S| = k $ . Formally, compute the following: $ $$$\sum_{r \in V} \sum_{S \subseteq V, |S| = k} f(r, S), $ $  where  $ V $  is the set of vertices in  $ G $ .</p><p>Output the answer modulo  $ 10^9 + 7$$$.

## 说明/提示

The tree in the second example is given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1691F/e82a7a29dc0a63112d5ed3b2013f71742d57079e.png)We have $ 21 $ subsets of size $ 2 $ in the given tree. Hence, $ $$$S \in \left\{\{1, 2\}, \{1, 3\}, \{1, 4\}, \{1, 5\}, \{1, 6\}, \{1, 7\}, \{2, 3\}, \{2, 4\}, \{2, 5\}, \{2, 6\}, \{2, 7\}, \{3, 4\}, \{3, 5\}, \{3, 6\}, \{3, 7\}, \{4, 5\}, \{4, 6\}, \{4, 7\}, \{5, 6\}, \{5, 7\}, \{6, 7\} \right\}. $ $  And since we have  $ 7 $  vertices,  $ 1 \\le r \\le 7 $ . We need to find the sum of  $ f(r, S) $  over all possible pairs of  $ r $  and  $ S $ . </p><p>Below we have listed the value of  $ f(r, S) $  for some combinations of  $ r $  and  $ S $ .</p><ul> <li>  $ r = 1 $ ,  $ S = \\{3, 7\\} $ . The value of  $ f(r, S) $  is  $ 5 $  and the corresponding subtree is  $ \\{2, 3, 4, 6, 7\\} $ . </li><li>  $ r = 1 $ ,  $ S = \\{5, 4\\} $ . The value of  $ f(r, S) $  is  $ 7 $  and the corresponding subtree is  $ \\{1, 2, 3, 4, 5, 6, 7\\} $ . </li><li>  $ r = 1 $ ,  $ S = \\{4, 6\\} $ . The value of  $ f(r, S) $  is  $ 3 $  and the corresponding subtree is  $ \\{4, 6, 7\\}$$$.

## 样例 #1

### 输入

```
3 2
1 2
1 3```

### 输出

```
25```

## 样例 #2

### 输入

```
7 2
1 2
2 3
2 4
1 5
4 6
4 7```

### 输出

```
849```

# 题解

## 作者：dead_X (赞：6)

## 思路
首先考虑根选好了怎么做，显然就直接枚举 $\text{LCA}$ 即可，直接列出式子。

$$
\sum sz_i\left(\binom{sz_i}{k}-\sum_{j\in \text{}son(i)}\binom{sz_j}{k}\right)
$$

也就是说一个点的贡献是 $(sz_i-sz_{fa_i})\binom{sz_i}{k}$。

然后直接换根 dp，dfs 一遍就做完了。

具体实现将 $fa_i$ 分三类枚举：

- 没有 $fa_i$，就是 $n\binom{n}{k}$。
  
- $fa_i$ 在 $i$ 子树里，记录子树里每个根对应的 $sz_j$ 总和。
  
- $fa_i$ 就是以 $1$ 为根的树上 $i$ 的父亲，记录每个根对应的 $sz_{fa_i}$ 的总和。

## 代码
```cpp
// Problem: F. K-Set Tree
// Contest: Codeforces - CodeCraft-22 and Codeforces Round #795 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1691/F
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//回家？我没有家可以回，我没有退路。
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
vector<int> e[200003];
int fac[200003],ifac[200003],sz[200003],ssz[200003];
int n=read(),k=read(),ans;
int C(int n)
{
	if(n<k) return 0;
	return fac[n]*ifac[k]%p*ifac[n-k]%p;
}
void dfs(int x,int fa=0)
{
	sz[x]=1;
	for(int y:e[x]) if(y!=fa)
		dfs(y,x),sz[x]+=sz[y];
	return ;
}
void calc(int x,int fa=0)
{
	int fsz=(n+(n-sz[x])*sz[x])%p;
	ssz[x]=n;
	for(int y:e[x]) if(y!=fa)
		fsz=(fsz+sz[y]*(n-sz[y]))%p;
	for(int y:e[x]) if(y!=fa)
		ans=(ans+(p+sz[y]*(n-sz[y])%p-(fsz+p-sz[y]*(n-sz[y])%p)%p)*C(sz[y]))%p,
		calc(y,x),ssz[x]=(ssz[x]+sz[y]*(n-sz[y]))%p,
		ans=(ans+(p+(n-sz[y])*sz[y]%p-ssz[y])*C(n-sz[y]))%p;
	return ;
}
signed main()
{
	fac[0]=ifac[0]=1;
	for(int i=1; i<=n; ++i) fac[i]=fac[i-1]*i%p;
	ifac[n]=qp(fac[n],p-2);
	for(int i=n-1; i>=1; --i) ifac[i]=ifac[i+1]*(i+1)%p;
	for(int i=1,u,v; i<n; ++i)
		u=read(),v=read(),e[u].push_back(v),e[v].push_back(u);
	ans=n*n%p*C(n)%p,dfs(1),calc(1),printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lingfunny (赞：5)

## CF1691F [link](https://codeforces.com/contest/1691/problem/F)

~~[Rd795 题解](https://280800.blog.luogu.org/codecraft-22-and-codeforces-round-795-div-2-post)滞销，帮帮我（误~~

不难想到换根 dp，然后我们可以写出如下式子：
$$
f_u=\left(\dbinom{\mathrm{sz}_u}{k}-\sum_{v}\dbinom{\mathrm{sz}_v}{k}\right)\mathrm{sz}_u+\sum_{v}f_v
$$
具体含义就是：考虑这 $k$ 个点，什么时候 $\operatorname{lca}$ 为 $u$。

减法原理，考虑什么时候不为 $u$，当且仅当这 $k$ 个点来自于同一颗子树。减去$\sum\limits_{v}\dbinom{\mathrm{sz}_v}{k}$ 即可。

最后把子树答案合并上去即可。

观察这个式子，可以拆出「只和 $v$ 有关」、「只和 $u$ 有关」、「和 $u,v$ 都有关」三种。为了好换根，我们需要让和 $v$ 有关的都比较好统计。于是考虑重定义 $f_u$ 和 $g_u$。$f_u$ 表示所有儿子的答案，$g_u$ 表示 $\sum\limits_{v}\dbinom{\mathrm{sz}_v}{k}$。

此时子树 $u$ 的答案应该是：
$$
\mathrm{ans}_u=\left(\dbinom{\mathrm{sz}_u}{k}-g_u\right)\mathrm{sz}_u+f_u
$$
此时换根只需要修改 $g$ 和 $f$ 即可，减减加加上面提到的组合数，相信大家都会。

没什么注意事项，没有细节，很好写。

## 码

```cpp
// Problem: F. K-Set Tree
// From: Codeforces - CodeCraft-22 and Codeforces Round #795 (Div. 2)
// URL: https://codeforces.com/contest/1691/problem/F
// Time: 2022-05-31 22:35
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e5+10, mod = 1e9+7;
int jc[mxn], ijc[mxn], n, f[mxn], g[mxn], k, sz[mxn], ans;
// f: 子树 ans 和
// g: 子树 (sz, k) 和
// ans[u]: (C(S-1, k-1) + C(S-1, k) - g[u]) * S + f[u]
vector <int> G[mxn];

inline int mul() { return 1; }
template <typename... A>
int mul(int x, A... a) { return (LL)x*mul(a...)%mod; }
inline int qpow(int x, int y) {
	int res = 1;
	for(; y; x = mul(x, x), y >>= 1) if(y&1) res = mul(res, x);
	return res;
}
inline int C(int n, int m) {
	if(m > n) return 0;
	return mul(jc[n], ijc[m], ijc[n-m]);
}
void add(int &x) { x = x; }
template <typename... A>
void add(int &x, int y, A... a) { x += (x + y) >= mod ? y - mod : y; add(x, a...); }
inline int calc(int S, int F, int G) { return (mul((C(S, k) - G + mod)%mod, S) + F) % mod; }
void dfs(int u, int fa) {
	sz[u] = 1;
	for(int v: G[u]) if(v != fa) {
		dfs(v, u), sz[u] += sz[v];
		add(f[u], calc(sz[v], f[v], g[v]));
		add(g[u], C(sz[v], k));
	}
}
void dfs2(int u, int fa) {
	if(fa) {
		int F = f[fa], G = g[fa];
		add(F, mod - calc(sz[u], f[u], g[u])), add(G, mod - C(sz[u], k));
		add(f[u], calc(n - sz[u], F, G));
		add(g[u], C(n - sz[u], k));
	}
	add(ans, calc(n, f[u], g[u]));
	for(int v: G[u]) if(v != fa) dfs2(v, u);
}

signed main() {
	scanf("%d%d", &n, &k);
	jc[0] = 1; for(int i = 1; i <= n; ++i) jc[i] = mul(jc[i-1], i);
	ijc[n] = qpow(jc[n], mod-2); for(int i = n - 1; ~i; --i) ijc[i] = mul(ijc[i+1], i+1);
	for(int i = 1, u, v; i < n; ++i) scanf("%d%d", &u, &v), G[u].emplace_back(v), G[v].emplace_back(u);
	dfs(1, 0); dfs2(1, 0);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Tachibana_Kimika (赞：2)

如果枚举每个大小为 $k$ 的集合的话，总共枚举量的数量级就是 $n!$ 之类的东西，很明显是不可接受的。

所以我们考虑枚举子树，考虑到子树只会有 $n$ 种，然后我们先考虑根为 $1$ 的情况。

对于一个子树 $u$，在这个子树中大小为 $k$ 的点集有 $\tbinom{siz_u}{k}$ 个，去掉最小覆盖不是 $u$ 的 $\sum_{v\in son_u}\tbinom{siz_v}{k}$，再乘上 $siz_u$ 就可以了。

对于根不为 $1$ 的情况，因为每次根从一个点 $u$ 换到相邻的点 $v$ 只会有这两个点的 $siz$ 发生变化，我们可以预处理 $sum_u=\sum_{v\in son_u}\tbinom{siz_v}{k}$，然后每次换根暴力计算新的 $siz_u,siz_v,sum_u,sum_v$ 和答案五个即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int p=1e9+7;
struct node{
	int to,nxt;
}edge[N*2]; int head[N],cnt;
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void adde(int u,int v){
	add(u,v); add(v,u);
}

int qpow(int a,int index){
	int ans=1;
	while(index){
		if(index&1) ans=ans*a%p;
		a=a*a%p; index>>=1;
	}
	return ans;
}

int fac[N],ifac[N];
void init(int n){
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%p;
	ifac[n]=qpow(fac[n],p-2);
	for(int i=n-1;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%p;
}

int C(int n,int m){//预处理组合数
	if(n<0||m<0||n<m) return 0;
	return fac[n]*ifac[n-m]%p*ifac[m]%p;
	
}
int n,k; 
int _minus(int a,int b){
	return ((a-b)%p+p)%p;
}

int siz[N],sum[N],ans=0; int tot=0;
void dfs(int u,int f){//第一次遍历树求根为1的答案
	siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==f) continue;
		dfs(v,u); siz[u]+=siz[v];
		sum[u]=(sum[u]+C(siz[v],k))%p;
	}
	ans=(ans+siz[u]*(((C(siz[u],k)-sum[u])%p+p)%p)%p)%p;
}

void dfs2(int u,int f){//换根
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==f) continue;
		
		int tmp=ans;
		ans=_minus(ans,siz[u]*(((C(siz[u],k)-sum[u])%p+p)%p)%p);
		ans=_minus(ans,siz[v]*(((C(siz[v],k)-sum[v])%p+p)%p)%p);//去掉uv对答案的贡献
		int tsumu=sum[u],tsumv=sum[v];//先存下这四个值
		int tsizu=siz[u],tsizv=siz[v];
		sum[u]=_minus(sum[u],C(siz[v],k));//更新这四个值，注意一下更新顺序
		siz[u]-=siz[v];
		siz[v]+=siz[u];
		sum[v]=(sum[v]+C(siz[u],k))%p;
		ans=(ans+siz[u]*(((C(siz[u],k)-sum[u])%p+p)%p)%p)%p;//重新加上uv对答案的贡献
		ans=(ans+siz[v]*(((C(siz[v],k)-sum[v])%p+p)%p)%p)%p;
		tot=(tot+ans)%p;
		dfs2(v,u);
		
		ans=tmp;//直接回退
		sum[u]=tsumu; sum[v]=tsumv;
		siz[u]=tsizu; siz[v]=tsizv;
	}
}

inline void fake_main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		adde(u,v);
	}
	dfs(1,0); tot+=ans;
	dfs2(1,0);
	cout<<tot<<"\n";
}

signed main(){
	init(N-10);
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：_tobi_ (赞：2)

换根 DP 计数题，先考虑 $1$ 为根怎么做。

$\sum_{|S|=k}f(1,S)$ 也即这棵树里选 $k$ 个点，枚举 LCA 为 $x$，对于所有的 $x$ 的方案数 $cnt_x$（也即 $S$ 的方案数）乘上 $siz_x$（最小子树大小）求和。显然 $cnt_x = \binom{siz_x}{k} - \sum\limits_{y \in son(x)}\binom{siz_y}{k}$。

我们将 $cnt_x \times siz_x$ 记为 $g_1[x]$，子树内求和后为 $f_1[x]$。显然 $f_1[x] = g_1[x] + \sum\limits_{y \in son(x)} f_1[y]$。算出来的 $f_1[1]$ 即为以 $1$ 为根的答案。  

接下来进行换根，我们增加几个需要用到的定义：
1. $g[x] = [\binom{n}{k} - \sum\limits_{y \in son(x)}\binom{siz_y}{k} - \binom{n - siz_x}{k}] \times n$，也即我们在以 $1$ 为根的视角下，将 $x$ 子树以外的部分视为 $x$ 父亲为根的子树，这样相当于变成了以 $x$ 为根，它的父亲变成了它的儿子，且 $siz_x' = n$。我们可以通过 $O(1)$ 算出，这里直接列出式子，不再推导：（式子里的 $siz$ 和 $son$ 都是以 $1$ 为根的）
$$g[x] = \left[\frac{g_1[x]}{siz_x} - \binom{siz_x}{k} + \binom{n}{k} - \binom{n - siz_x}{k}\right] \times n$$
2. $g_y'[x] = [\binom{n - siz_y}{k} - \sum\limits_{z \in son(x), z \neq y} \binom{siz_z}{k} - \binom{n - siz_x}{k}] \times (n - siz_y)$，其中 $y \in son(x)$，即在 $g[x]$ 的基础上去掉了 $y$ 子树的部分。也可以 $O(1)$ 算出：
$$g_y'[x] = \left[\frac{g[x]}{n} - \binom{n}{k} + \binom{n - siz_y}{k} + \binom{siz_y}{k}\right] \times (n - siz_y)$$
3. $f_y'[x] = f[x] - g[x] + g_y'[x] - f_1[y]$，其中 $y \in son(x)$，定义类似 $g_y'[x]$。
4. $f[y] = f_1[y] - g_1[y] + g[y] + f_y'[x]$，其中 $y \in son(x)$，定义类似 $g[x]$。

有了上面这些定义，换根的式子就非常简单了：
$$f[y] = f_1[y] - g_1[y] + g[y] + f_y'[x], y \in son(x)$$
也即以 $1$ 为根的 $f_1[y]$ 去掉以 $1$ 为根的 $g_1[y]$，加上以 $y$ 为根的 $g[y]$，再加上以 $y$ 为根时父亲 $x$ 的贡献 $f_y'[x]$。

代码：
```cpp
istream &in = cin;
ostream &out = cout;
#define newl '\n'
using LL = long long;

const int P = 1e9 + 7, N = 2e5 + 5;
LL fac[N], inv[N], invf[N];
LL siz[N], f1[N], g1[N], f[N], g[N];
int head[N], nxt[2 * N], to[2 * N], tot;
int n, t;

void add(int x, int y){
    to[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}

LL qpow(LL x, LL y){
    LL res = 1;
    for(; y; y >>= 1){
        if(y & 1) res = res * x % P;
        x = x * x % P;
    }
    return res;
}

LL comb(int x, int y){
    if(y > x) return 0;
    return fac[x] * invf[y] % P * invf[x - y] % P;
}

void dfs(int x, int fa){
    siz[x] = 1;
    for(int e = head[x]; e; e = nxt[e]){
        int y = to[e];
        if(y == fa) continue;
        dfs(y, x);
        siz[x] += siz[y];
    }
    g1[x] = comb(siz[x], t);
    for(int e = head[x]; e; e = nxt[e]){
        int y = to[e];
        if(y == fa) continue;
        g1[x] = ((g1[x] - comb(siz[y], t)) % P + P) % P;
    }
    g1[x] = g1[x] * siz[x] % P;
    f1[x] = g1[x];
    for(int e = head[x]; e; e = nxt[e]){
        int y = to[e];
        if(y == fa) continue;
        f1[x] = (f1[x] + f1[y]) % P;
    }
}

void dp(int x, int fa){
    for(int e = head[x]; e; e = nxt[e]){
        int y = to[e];
        if(y == fa) continue;
        g[y] = (g1[y] * inv[siz[y]] % P - comb(siz[y], t) + comb(n, t) - comb(n - siz[y], t)) % P * n % P;
        LL gx = (g[x] * inv[n] % P - comb(n, t) + comb(n - siz[y], t) + comb(siz[y], t)) % P * (n - siz[y]) % P;
        LL fx = (f[x] - g[x] + gx - f1[y]) % P;
        f[y] = (f1[y] - g1[y] + g[y] + fx) % P;
        dp(y, x);
    }
}

int main(){
    ios::sync_with_stdio(0), in.tie(0), out.tie(0);
    in >> n >> t;
    for(int i = 1; i < n; i++){
        int x, y; in >> x >> y;
        add(x, y), add(y, x);   
    }
    fac[0] = 1;
    invf[0] = 1;
    for(int i = 1; i <= n; i++){
        fac[i] = fac[i - 1] * i % P;
        invf[i] = qpow(fac[i], P - 2);
        inv[i] = qpow(i, P - 2);
    }
    dfs(1, 0);
    g[1] = g1[1], f[1] = f1[1];
    dp(1, 0);
    LL ans = 0;
    for(int i = 1; i <= n; i++) ans = (ans + f[i]) % P;
    if(ans < 0) ans += P;
    out << ans << newl;
    return 0;
}
```

---

## 作者：candy0014 (赞：1)

> 提供一种不用 dp 的做法，跑得飞快。

>[洛谷传送门](https://www.luogu.com.cn/problem/CF1691F)
>
>[CF 传送门](https://codeforces.com/problemset/problem/1691/F)

# 题意

给定一棵有 $n$ 个点的树及正整数 $k$，定义 $F(u,S) $为以 $u$ 为根时包含集合 $S$ 中所有点的最小子树的大小，求 $\sum_{u=1}^{n}\sum_{|S|=k}F(u,S)$。

# 思路

先考虑对于一个给定的集合 $S$，有没有什么简单的式子可以表示 $\sum_{u=1}^n F(u,S)$。

我们称这样的 $u$ 为关键点：$u\in S$，或者以 $u$ 为根时，至少有两棵子树里有 $\in S$ 的点。显然若 $u$ 为关键点，则 $F(u,S)=n$。如在样例 2 中，若 $S=\{3,7\}$，则点 $3,2,4,7$ 为关键点。

对于关键点之外的点，设它们形成了 $m$ 个连通块，第 $i$ 个连通块大小为 $sz_i$。若 $u$ 在第 $i$ 个连通块中，则 $F(u,S)=n-sz_i$。

考虑所有点的 $F$ 值之和：

- 共有 $n-\sum sz_i$ 个关键点，每个关键点的 $F$ 值为 $n$，共为 $n\times (n-\sum sz_i)=n^2-n\sum sz_i$；
- 第 $i$ 个连通块有 $sz_i$ 个点，每个点的 $F$ 值为 $n-sz_i$，共为 $\sum sz_i\times(n-sz_i)=n\sum sz_i-\sum sz_i^2$；
- 所有点的 $F$ 值之和为 $n^2-n\sum sz_i+n\sum sz_i-\sum sz_i^2=n^2-\sum sz_i^2$。

故问题转化为求每种 $S$ 下的 $\sum sz_i^2$ 之和。发现连通块一共只有 $2(n-1)$ 个（每条树边两侧的连通块），考虑每个连通块的贡献。

先计算以 $u$ 为根的子树作为连通块的次数。对于一种 $S$，这棵子树被作为连通块当且仅当 $fa_u$ 是关键点。记 $SZ_u$ 为以 $1$ 为根时 $u$ 子树的大小。此时有两种情况：

- $fa_u\in S$：此时共有 $\dbinom{n-SZ_u-1}{k-1}$ 种情况；
- $fa_u\not\in S$：此时共有 $\dbinom{n-SZ_u-1}{k}-{\large\sum\limits_{v\in son_{fa_u},v\not=u}}\dbinom{SZ_v}{k}-\dbinom{n-SZ_{fa_u}-1}{k}$ 种情况，即在去掉 $u$ 子树和 $fa_u$ 后的点中取 $k$ 个，然后去掉 $fa_u$ 不是关键点的情况。

以 「全部点去掉 $u$ 子树」作为连通块的次数与上同理。

然后即可算出答案。

注意：可以先预处理出 $p_u={\large\sum\limits_{v\in son_{u}}}\dbinom{SZ_v}{k}$，否则在前一种情况中多次访问父亲的儿子，会被菊花图卡掉。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int N=2e5+5;
ll ksm(ll u,ll v=mod-2){ll tmp=1;u%=mod;while(v) tmp=tmp*((v&1)?u:1)%mod,u=u*u%mod,v>>=1;return tmp;}
ll jie[N],inv[N];
void init(int n=N-3){
	jie[0]=1;
	for(int i=1;i<=n;i++) jie[i]=1ll*jie[i-1]*i%mod;
	inv[n]=ksm(jie[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
ll C(ll u,ll v){
	if(v<0||v>u) return 0;
	return 1ll*jie[u]*inv[v]%mod*inv[u-v]%mod;
}
//---------------------------------------------预处理组合数
int head[N],tot;
struct EDGE{
	int nex,to;
} e[N<<1];
void add(int u,int v){
	e[++tot].nex=head[u],e[tot].to=v;
	head[u]=tot;
}
ll n,k,SZ[N],fa[N],p[N];
ll ans=0;
void dfs(int u,int fat){ //预处理 SZ,p,fa 数组
	SZ[u]=1,fa[u]=fat;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].to;
		if(v==fat) continue;
		dfs(v,u);
		SZ[u]+=SZ[v];
		p[u]=(p[u]+C(SZ[v],k))%mod;
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	init();
	cin>>n>>k;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	ll num;
	for(int u=2;u<=n;u++){
		num=C(n-SZ[u]-1,k-1)+C(n-SZ[u]-1,k)-(p[fa[u]]-C(SZ[u],k))-C(n-SZ[fa[u]],k);
		num%=mod;
		ans=(ans+SZ[u]*SZ[u]%mod*num)%mod; //第一种连通块

		num=C(SZ[u]-1,k-1)+C(SZ[u]-1,k)-p[u];
		num%=mod;
		ans=(ans+(n-SZ[u])*(n-SZ[u])%mod*num)%mod; //第二种连通块
	}
	cout<<(n*n%mod*C(n,k)%mod-ans+mod)%mod<<"\n"; //计算答案
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：1)

我竟然独立做出了 *2500。

考虑一个点 $u$ 作为连通块的根。分为两种情况：$r=u$ 和 $r\neq u$。

第一种情况是好办的，答案就是 $(C_n^k-\sum _{u\to v} C_{size_v}^k)\times n$。

第二种情况，不妨枚举 $r$ 在哪里。那么 $S$ 中的点不能在 $r$ 所在的子树中取，另外的计算方式仍然是一致的。此时方案数也要乘上  $r$ 的选取范围，即该子树的大小。把根节点在每一棵子树里的答案相加即可。

总时间复杂度 $O(n\log p)$。

---

## 作者：OtterZ (赞：0)

# 1.题意
给定一颗树，设 $\operatorname{f}(r,S)$ 为以 $r$ 为根时，以点集 $S$ 的最近公共祖先为根的子树大小，问 $\sum_{r = 1}^n\sum_{|S| = k}\operatorname{f}(r,S)$。
# 2.小结论
指定一棵树，以 $r$ 为根，则 $x$ 为最近公共祖先的情况树为 $(_k^{sz_x}) - \sum_{y \exist son(x)}(_k^{sz_y})$，$x$ 对应贡献为 $((_k^{sz_x}) - \sum_{y \exist son(x)}(_k^{sz_y})) \times sz_x$，即为 $g_{r,x}$。
# 3.初步公式
首先默认一个根 $r$，跑 $t_{r,x} = \sum_{y\exist subtree(x)} g_{r,y} = g_{r,x} + \sum_{z\exist son(x)}t_{r,z}$，然后进行换根推 $dp_x = \sum_{|S| = k}\operatorname{f}(x,S)$。

对于 $dp_x$，有 $t_{x,fa_x} = dp_{fa_x} - t_{fa_x,x} - g_{fa_x,fa_x} + g_{x,fa_x}$，然后有 $dp_x = t_{fa_x,x} - g_{fa_x,x} + g_{x,x} + t_{x,fa_x}$。
# 4.优化
首先 $t_{fa_x,x}= t_{r,x}$，其次用逆元处理 $(_k^{sz_x})$，最后我们再开数组维护 $ \sum_{y \exist son(x)}(_k^{sz_y})$，就可以得到一个 $\operatorname{O}(n)$ 的解法。
# 5.上代码

```cpp
#include<cstdio>
#include<vector>
using namespace std;
int n,k,s[200009],inv[200009],fs[200009],u,v;
const int mod = 1e9 + 7;
void init(){
	s[0] = s[1] = inv[1] = fs[0] = fs[1] = 1;
	for(int i = 2; i <= n; i ++){
		s[i] = 1ll * s[i - 1] * i % mod;
		inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
		fs[i] = 1ll * fs[i - 1] * inv[i] % mod;
	}
}
int c(int x,int y){
	if(y > x)
		return 0;
	else
		return 1ll * s[x] * fs[y] % mod * fs[x - y] % mod;
}
int dp1[200009],dp2[200009],dp3[200009],ans,sz[200009];
vector<int>e[200009];
void srh1(int v,int fa){
	sz[v] = 1;
	for(int i = 0; i < e[v].size(); i ++){
		if(e[v][i] == fa)
			continue;
		srh1(e[v][i],v);
		dp1[v] = (dp1[v] + dp1[e[v][i]]) % mod;
		dp2[v] = (dp2[v] + c(sz[e[v][i]],k)) % mod;
		sz[v] = sz[v] + sz[e[v][i]];
	}
	dp1[v] = (dp1[v] + 1ll * (mod + c(sz[v],k) - dp2[v]) * sz[v] % mod) % mod;
	//printf("%d %d\n",v,dp1[v]);
}
void srh2(int v,int fa){
	if(fa != 0){
		int o = ((long long)dp3[fa] - dp1[v] + 1ll * (c(sz[fa] - sz[v],k) - dp2[fa] + c(sz[v],k)) * (sz[fa] - sz[v]) % mod - 1ll * (c(sz[fa],k) - dp2[fa]) * (sz[fa]) % mod) % mod;
		if(o < 0)
			o += mod;
		dp3[v] = (1ll * dp1[v] - 1ll * (c(sz[v],k) - dp2[v]) * sz[v] % mod + 1ll * (c(sz[fa],k) - dp2[v] - c(sz[fa] - sz[v],k)) * sz[fa] % mod + o) % mod;
		if(dp3[v] < 0)
			dp3[v] += mod;
		dp2[v] = (dp2[v] + c(sz[fa] - sz[v],k)) % mod;
		sz[v] = sz[fa];
		ans = (ans + dp3[v]) % mod;
		//printf(" %d %d %d\n",v,dp3[v],o);
	}
	for(int i = 0; i < e[v].size(); i ++){
		if(e[v][i] == fa)
			continue;
		srh2(e[v][i],v);
	}
}
int main(){
	scanf("%d %d",&n,&k);
	for(int i = 1; i < n; i ++){
		scanf("%d %d",&u,&v);
		e[v].push_back(u);
		e[u].push_back(v);
	}
	init();
	srh1(1,0);
	dp3[1] = dp1[1];
	ans = dp1[1];
	srh2(1,0);
	printf("%d\n",ans);
	return 0;
}
```
+ 时间：$390 \text{ms}$；
+ 空间：$21092 \text{KB}\approx 20 \text{MB}$。

---

