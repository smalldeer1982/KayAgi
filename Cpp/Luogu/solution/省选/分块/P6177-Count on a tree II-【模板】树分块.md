# Count on a tree II/【模板】树分块

## 题目背景

原 bzoj2589。

## 题目描述

给定一个 $n$ 个节点的树，每个节点上有一个整数，$i$ 号点的整数为 $val_i$。

有 $m$ 次询问，每次给出 $u',v$，您需要将其解密得到 $u,v$，并查询 $u$ 到 $v$ 的路径上有多少个不同的整数。

解密方式：$u=u' \operatorname{xor} lastans$。

$lastans$ 为上一次询问的答案，若无询问则为 $0$。

## 说明/提示

对于 $100\%$ 的数据，$1\le u,v\le n\le 4\times 10^4$，$1\le m\le 10^5$，$0\le u',val_i<2^{31}$。

## 样例 #1

### 输入

```
8 2
105 2 9 3 8 5 7 7 
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
3 8```

### 输出

```
4
4```

# 题解

## 作者：mrsrz (赞：46)

[可能更好的体验](https://mrsrz.github.io/2020/03/06/lg6177/)

这里需要用到一种简单的树分块技巧。简单来说就是树上撒点。

我们设一个阈值 $S$，并考虑在树上选择不超过 $\frac n S$ 个点作为关键点，满足每个关键点到离它最近的祖先关键点的距离不超过 $S$。

在树上随机选择 $\frac n S$ 个点，期望距离是正确的。

这里给出一个确定性算法，能够**严格保证保证**每个关键点到离它最近的祖先关键点的距离不超过 $S$。

具体地，我们每次选择一个深度最大的非关键点，然后若它的 $1\sim S$ 级祖先都不是关键点，则我们把它的 $S$ 级祖先标记为关键点。由标记过程可知距离不超过 $S$，并且每标记一个关键点，至少有 $S$ 个点不会被标记，所以关键点数量也是正确的。

接下来，我们考虑一条到根路径上的所有关键点 $x_1,x_2,x_3,\ldots,x_k$，我们用 `bitset` 维护它们两两间出现的颜色。处理的时候，可以用递推的方式，即 $b_{x_i,x_j}=b_{x_i,x_{j-1}}\ \mathrm{or}\ b_{x_{j-1},x_j}$。于是我们只需要用 $O(S)$ 的时间求出相邻两个关键点的 `bitset`，再处理出两两之间的即可。由于这样的点对最多只有 $\frac{n^2}{S^2}$ 对，所以预处理的复杂度为 $O(\frac{n^2}S+\frac{n^3}{w S^2})$。

接下来考虑求解答案。令 $t=\mathrm{LCA}(u,v)$。我们分别求出 $u,v$ 的祖先中离 $u,v$ 最近的关键点 $u_0,v_0$， 以及离 $t$ 最近且在 $t$ 子树中的关键点 $u_1,v_1$。那么一条路径被我们拆成了以下几个部分：$u\sim u_0$，$v\sim v_0$，$u_1\sim t$，$v_1\sim t$，$u_0\sim u_1$，$v_0\sim v_1$。对于前面 $4$ 种，我们直接暴力跳，时间复杂度 $O(S)$。而对于后面两种，我们已经预处理它们的 `bitset`，所以直接取并集即可。时间复杂度 $O(\frac n w)$。当然有可能出现 $u\sim t$，$v\sim t$ 之间没有关键点的情况，此时直接跳到 $t$ 即可。

最后求颜色个数，就调用 `b.count()` 即可，时间复杂度 $O(\frac n w)$。

时间复杂度 $O(\frac{n^2}S+\frac{n^3}{w S^2}+\frac{nm}{w}+mS)$。一般地，我们取 $S=\sqrt n$，得到时间复杂度 $O((n+m)\sqrt n+\frac{n^2+nm}w)$。

空间复杂度 $O(\frac{n^3}{S^2})$，一般地，我们取 $S=\sqrt n$，得到空间复杂度 $O(n^2)$，由于是 `bitset`，所以有较小的空间常数。

然后可以发现，当 $S$ 线性增长时，时间常数是线性增长的，而内存是平方级别下降的，所以我们可以通过调整块大小的方式来**卡空间**。

在 $S$ 取 $1000$ 时仅用了 $11.39\texttt{MB}$，已经是大多数其他做法的约 $\frac 1 {10}$，再继续卡没有意义，而且会增加耗时。[评测记录]( https://www.luogu.com.cn/record/31379387 )

## Code：

```cpp
#include<cstdio>
#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
const int N=40002;
bitset<N>bt[42][42],nw;
vector<int>vec;
int n,m,B,a[N],fa[N],dep[N],mxd[N],FF[N],sz[N],tp[N],son[N];
int id[N],cnt,head[N],tot,ans,sta[N],top,gg[N];
struct edge{
	int to,nxt;
}e[N<<1];
void dfs(int now){
	sz[now]=1,son[now]=0;
	mxd[now]=dep[now];
	for(int i=head[now];i;i=e[i].nxt)if(!dep[e[i].to]){
		dep[e[i].to]=dep[now]+1,fa[e[i].to]=now;
		dfs(e[i].to),sz[now]+=sz[e[i].to];
		if(mxd[e[i].to]>mxd[now])mxd[now]=mxd[e[i].to];
		if(!son[now]||sz[son[now]]<sz[e[i].to])son[now]=e[i].to;
	}
	if(mxd[now]-dep[now]>=1000)id[now]=++tot,mxd[now]=dep[now];
}
void dfs2(int now){
	for(int i=head[now];i;i=e[i].nxt)
	if(dep[e[i].to]>dep[now]){
		if(id[e[i].to]){
			int ip=id[sta[top]],in=id[e[i].to];
			for(int x=e[i].to;x!=sta[top];x=fa[x])bt[ip][in].set(a[x]);
			nw=bt[ip][in];
			for(int i=1;i<top;++i){
				bitset<N>&bs=bt[id[sta[i]]][in];bs=bt[id[sta[i]]][ip];bs|=nw;
			}
			FF[e[i].to]=sta[top],gg[e[i].to]=gg[sta[top]]+1;
			sta[++top]=e[i].to;
		}
		dfs2(e[i].to);
		if(id[e[i].to])--top;
	}
}
void dfs3(int now){
	if(son[now])tp[son[now]]=tp[now],dfs3(son[now]);
	for(int i=head[now];i;i=e[i].nxt)if(e[i].to!=son[now]&&dep[e[i].to]>dep[now])
	dfs3(tp[e[i].to]=e[i].to);
}
inline int LCA(int x,int y){
	while(tp[x]!=tp[y])if(dep[tp[x]]>dep[tp[y]])x=fa[tp[x]];else y=fa[tp[y]];
	return dep[x]<dep[y]?x:y;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",a+i),vec.push_back(a[i]);
	sort(vec.begin(),vec.end()),vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(int i=1;i<=n;++i)a[i]=lower_bound(vec.begin(),vec.end(),a[i])-vec.begin();
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[++cnt]=(edge){v,head[u]},head[u]=cnt;
		e[++cnt]=(edge){u,head[v]},head[v]=cnt;
	}
	dfs(dep[1]=1);
	if(!id[1])id[1]=++tot;
	sta[top=1]=gg[1]=1,dfs2(1),dfs3(1);
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v),u^=ans,nw.reset();
		int l=LCA(u,v);
		while(u!=l&&!id[u])nw.set(a[u]),u=fa[u];
		while(v!=l&&!id[v])nw.set(a[v]),v=fa[v];
		if(u!=l){
			int pre=u;
			while(dep[FF[pre]]>=dep[l])pre=FF[pre];
			if(pre!=u)nw|=bt[id[pre]][id[u]];
			while(pre!=l)nw.set(a[pre]),pre=fa[pre];
		}
		if(v!=l){
			int pre=v;
			while(dep[FF[pre]]>=dep[l])pre=FF[pre];
			if(pre!=v)nw|=bt[id[pre]][id[v]];
			while(pre!=l)nw.set(a[pre]),pre=fa[pre];
		}
		nw.set(a[l]);
		printf("%d\n",ans=nw.count());
	}
	return 0;
}
```



---

## 作者：Aestas16 (赞：28)

提供一种不用树分块的做法。

考虑使用 bitset，对值域建 bitset，显然答案就是 bitset 中 $1$ 的数量。

那么现在的问题就是怎么把一条路径上的 bitset 并起来，可以使用轻重链剖分维护，询问时在把经过的若干条重链上的 bitset 并起来即可。

现在只要求出一条重链上某区间内的 bitset，变成了序列上的问题，对序列分块，预处理出每一块中所有 bitset 的并，询问时散块暴力将数插入 bitset 内，整块直接并上预处理出的信息。时间复杂度 $\Theta(m \log n \cdot \sqrt{n} \cdot \dfrac{n}{w})$，显然无法通过本题。

发现这么做的瓶颈在于对整块的合并，最坏有 $\sqrt{n}$ 个整块要合并，每次合并复杂度是 $\Theta(\dfrac{n}{w})$ 的，合起来就是 $\Theta(\sqrt{n} \cdot \dfrac{n}{w})$ 的。

考虑优化这一部分，由于没有修改，并且**或运算**是可重复贡献的，故可以使用 ST 表加速合并整块的过程，这一部分时间复杂度由 $\Theta(\sqrt{n} \cdot \dfrac{n}{w})$ 变为 $\Theta(\dfrac{n}{w})$。总时间复杂度变为 $\Theta(m \log n \cdot \dfrac{n}{w})$，乍一看好像还是过不去，但是这东西跑不满，而且常数小，因此可以通过本题。甚至跑到了[最优解](https://www.luogu.com.cn/record/list?pid=P6177&orderBy=1&status=&page=1)。

代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

template <class T> void fr(T &a, bool f = 0, char ch = getchar()) {
    for (a = 0; ch < '0' || ch > '9'; ch = getchar()) ch == '-' ? f = 1 : 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) a = a * 10 + (ch - '0');
    a = f ? -a : a;
}
template <class T, class... Y> void fr(T &t, Y &... a) { fr(t), fr(a...); }
int fr() { int a; return fr(a), a; }

const int N = 4e4;

int n, m, up, etot, bsz, lg2[N + 10], bid[N + 10], w[N + 10], arr[N + 10], a[N + 10], hd[N + 10];
struct Edge { int to, nxt; } e[(N << 1) + 10];

inline void adde(register int x, register int y) { e[++etot] = {y, hd[x]}, hd[x] = etot; }

struct Bitset {
    unsigned long long A[626];
    inline Bitset operator|(Bitset b) const {
        Bitset c;
        for (register int i = 0; i <= up; i++) c.A[i] = A[i] | b.A[i];
        return c;
    }
    inline void reset() { for (register int i = 0; i <= up; i++) A[i] = 0; }
    inline void set(register int x) { A[x >> 6] |= 1ull << (x & 63); }
    inline int count() {
        register int ret = 0;
        for (register int i = 0; i <= up; i++) ret += __builtin_popcountll(A[i]);
        return ret;
    }
} ansor, f[9][201];

void work(register int l, register int r) {
    if (bid[l] == bid[r]) {
        for (register int i = l; i <= r; i++) ansor.set(a[i]);
        return;
    }
    for (register int i = l; bid[i] == bid[l]; i++) ansor.set(a[i]);
    for (register int i = r; bid[i] == bid[r]; i--) ansor.set(a[i]);
    if (bid[l] + 1 < bid[r]) {
        register int t = lg2[bid[r] - bid[l] - 1];
        ansor = ansor | f[t][bid[l] + 1] | f[t][bid[r] - (1 << t)];
    }
}

namespace TreeLink {
    int timer, dfn[N + 10], sz[N + 10], fa[N + 10], dep[N + 10], ltop[N + 10], ch[N + 10];
    void dfs1(register int u, register int p) {
        sz[u] = 1, fa[u] = p, dep[u] = dep[p] + 1;
        for (register int i = hd[u]; i; i = e[i].nxt) {
            register int v = e[i].to;
            if (v == p) continue;
            dfs1(v, u), sz[u] += sz[v];
            if (sz[v] > sz[ch[u]]) ch[u] = v;
        }
    }
    void dfs2(register int u, register int p) {
        ltop[u] = p, dfn[u] = ++timer, a[dfn[u]] = w[u], bid[dfn[u]] = (dfn[u] - 1) / bsz + 1, f[0][bid[dfn[u]]].set(w[u]);
        if (ch[u] == 0) return;
        dfs2(ch[u], p);
        for (register int i = hd[u]; i; i = e[i].nxt) {
            register int v = e[i].to;
            if (v == fa[u] || v == ch[u]) continue;
            dfs2(v, v);
        }
    }
    void query(register int u, register int v) {
        ansor.reset();
        while (ltop[u] != ltop[v]) {
            if (dep[ltop[u]] < dep[ltop[v]]) swap(u, v);
            work(dfn[ltop[u]], dfn[u]), u = fa[ltop[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        work(dfn[u], dfn[v]);
    }
} // namespace TreeLink
using namespace TreeLink;

struct OI {
    int RP, score;
} FJOI2022;

signed main() {
    FJOI2022.RP++, FJOI2022.score++;
    fr(n, m), bsz = sqrt(n), up = n >> 6;
    for (register int i = 1; i <= n; i++) fr(w[i]), arr[i] = w[i];
    sort(arr + 1, arr + 1 + n), arr[0] = unique(arr + 1, arr + 1 + n) - arr - 1;
    for (register int i = 1; i <= n; i++) w[i] = lower_bound(arr + 1, arr + 1 + arr[0], w[i]) - arr;
    for (register int i = 1, x, y; i < n; i++) fr(x, y), adde(x, y), adde(y, x);
    dfs1(1, 0), dfs2(1, 1);
    for (register int i = 2; i <= bid[n]; i++) lg2[i] = lg2[i >> 1] + 1;
    for (register int j = 1; j <= lg2[bid[n]]; j++) {
        auto *x = f[j], *y = f[j - 1]; 
        for (register int i = 1; i + (1 << j) - 1 <= bid[n]; i++) x[i] = y[i] | y[i + (1 << (j - 1))];
    }
    for (register int i = 1, x, y, lstans = 0; i <= m; i++) fr(x, y), x ^= lstans, query(x, y), printf("%d\n", lstans = ansor.count());
    return 0;
}
```

---

## 作者：critnos (赞：18)

upd：

![](https://cdn.luogu.com.cn/upload/image_hosting/sj832ktt.png)

top cluster 树分块由于其复杂性和常数较大的原因，使用起来比较麻烦。

这里给出一种平凡的简易树分块。

设块长为 $B$。考虑如下构造：

* 初始存在点集包含整棵树。 
* 取出点集中子树大小 $size$ 最大的点 $x$。
* 若 $size_x > B$，则删除点集中被包含在 $x$ 的子树中且距离 $x$ 不超过 $B$ 的点。显然，这里标记 $\Omega (B)$ 个点。然后将 $x$ 加入另一点集 $S$。
* 若 $size_x \le B$ 或点集为空，终止该过程。

显然，上面得到 $O(\dfrac n B)$ 个点。

最终的树分块结构即为点集 $S$ 的虚树 $T$ 上的点。称 $T$ 中的点为关键点。

显然有以下性质：

* 每个点最深的为关键点的祖先距离其距离为 $O(B)$。
* 每个关键点到其最深的为关键点的祖先距离之和 $O(n)$（虚树链不相交）。

### 链上数颜色

预处理两两关键点之间的答案，$O(\dfrac {n^2} B)$。

考虑 $x,y$ 最深的为关键点的祖先 $x',y'$，路径拆成 $x \to x' \to y'\to y$。

枚举 $x\to x',y'\to y$ 上的点，求其在 $x'\to y'$ 上的出现次数即可。

考虑虚树的特性，$z=lca(x',y')$ 也为关键点。利用树上前缀和相减即可。$O(nB)$。

取 $B=\Theta(\sqrt n)$，时间复杂度为 $O(n\sqrt n)$。

### 链上逆序对

为了使题目更加简洁，令边带权而并非点带权。

和序列上完全一致。令 $B=\Theta (\sqrt n)$

除了前缀和变成了树上的之外，没有任何区别。

---

## 作者：yijan (赞：14)

### Count on a Tree II

推荐到 Luogu 博客或者到 [这里](https://www.yijan.co/old60/) 阅读

以前写的用可持久化分块维护。。既难写而且常数还大。。最后在 Luogu 还是开了读优挂才跑过去的。。感觉题解区的 Bitset 维护比我这个不知道高到哪里去了。。

考虑随机在这个树上打 $\sqrt n$ 个点作为关键点，然后每个点向上跳找到第一个关键点的期望长度是 $ \sqrt n $ 的。当然，也有没那么玄学的打点方法，用深度是 $\sqrt n$ 倍数并且向下最深深度大于等于根号的点来打，这样打出来点的个数是 $\sqrt n$ 的并且明显从每个点向上的长度也是 $\sqrt n$ 的。

然后我们先预处理出关键点间两两的答案，做法是从每个关键点跑一次 DFS 。

然后考虑一次询问，对于一次询问我们需要查询这两个点到关键点的路径上有没有什么颜色是不存在于关键点的路径上的。也就是说我们需要维护根到每个节点的某个颜色的数量。直接主席树维护得带 $ \log $ 不优秀，可以考虑用根号平衡，修改 $O(\sqrt n)$ 查询 $O(1)$ ，套个可持久化就好了。

还需要用 ST 表 $ O(1) $ 维护 LCA。这样做复杂度就是在线的 $O(m\sqrt n)$ 了（虽然常数有点大）。空间是 $n\sqrt n$ 的。

代码写的很丑。。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
using namespace std;
#define MAXN 40006
#define B 206
#define swap( a , b ) ( (a) ^= (b) , (b) ^= (a) , (a) ^= (b) )
int n , m , blo , sz , bl;
int c[MAXN] , C[MAXN];
int head[MAXN] , to[MAXN << 1] , nex[MAXN << 1] , ecn;
void ade( int u , int v ) {
    to[++ ecn] = v , nex[ecn] = head[u] , head[u] = ecn;
}
int ps[B] , im[MAXN] , pre[B][B] , cid , ee;
int w[MAXN] , an;
void dfs( int u , int fa ) {
    if( !w[c[u]] ) ++ an;
    ++ w[c[u]];
    if( im[u] ) pre[cid][im[u]] = an;
    for( int i = head[u] ; i ; i = nex[i] ) {
        int v = to[i];
        if( v == fa ) continue;
        dfs( v , u );
    }
    -- w[c[u]];
    if( !w[c[u]] ) -- an;
}

int kk[MAXN << 2][B] , idx = 0 , rt[MAXN];
void build( ) {
    idx = rt[0] = 1;
    for( int i = 1 ; ( i - 1 ) * bl < sz ; ++ i ) kk[1][i] = i + 1 , ++ idx;
}
void add( int rt , int old , int x ) {
    memcpy( kk[rt] , kk[old] , sizeof kk[old] );
    ++ idx;
    memcpy( kk[idx] , kk[kk[rt][( x - 1 ) / bl + 1]] , sizeof kk[1] );
    kk[rt][( x - 1 ) / bl + 1] = idx;
    ++ kk[idx][( x - 1 ) % bl + 1];
}
int que( int rt , int x ) {
    int t = kk[rt][( x - 1 ) / bl + 1];
    return kk[t][( x - 1 ) % bl + 1];
}

int dfn[MAXN << 1] , dep[MAXN << 1] , pos[MAXN << 1] , en = 0 , d[MAXN] , par[MAXN];
int dfs1( int u , int fa ) {
    dfn[++en] = u , pos[u] = en , dep[en] = d[u] , par[u] = fa;
    rt[u] = ++ idx;
    add( rt[u] , rt[fa] , c[u] );
    int re = 0;
    for( int i = head[u] ; i ; i = nex[i] ) {
        int v = to[i];
        if( v == fa ) continue;
        d[v] = d[u] + 1;
        re = max( re , dfs1( v , u ) );
        dfn[++ en] = u , dep[en] = d[u];
    }
    if( re - d[u] >= blo && d[u] % blo == 0 ) ps[++ ee] = u , im[u] = ee;
    return re ? re : d[u];
}
int lg[MAXN << 1];
int st[MAXN << 1][17];
void ST() {
    for( int i = 1 ; i <= en ; ++ i ) lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    for( int i = 1 ; i <= en ; ++ i ) st[i][0] = i;
    for( int i = 1 ; ( 1 << i ) <= en ; ++ i )
        for (int j = 1; j + (1 << i) - 1 <= en; j++)
            st[j][i] = dep[st[j][i - 1]] < dep[st[j + (1 << (i - 1))][i - 1]] ? st[j][i - 1] : st[j + (1 << (i - 1))][i - 1];
}
int lca( int l , int r ) {
    l = pos[l] , r = pos[r];
    if( l > r ) swap( l , r );
    int k = lg[r - l + 1] - 1;
    return dep[st[l][k]] <= dep[st[r-(1<<k)+1][k]] ? dfn[st[l][k]] : dfn[st[r-(1<<k)+1][k]];
}
int col[MAXN] , cn , l;
int jump( int u ) {
    if( im[u] ) return im[u];
    col[++ cn] = c[u];
    if( u == l ) return -1;
    return jump( par[u] );
}
int rejjump( int u ) {
    if( im[u] ) return im[u];
    col[++ cn] = c[u];
    return rejjump( par[u] );
}
int oc[MAXN];
int main() {
//    freopen("10.in","r",stdin);
//    freopen("ot","w",stdout);
    cin >> n >> m;
    blo = sqrt( n );
    for( int i = 1 ; i <= n ; ++ i ) scanf("%d",&c[i]) , C[i] = c[i];
    sort( C + 1 , C + 1 + n ); sz = unique( C + 1 , C + 1 + n ) - C - 1;
    bl = sqrt( sz );
    for( int i = 1 ; i <= n ; ++ i ) c[i] = lower_bound( C + 1 , C + 1 + sz , c[i] ) - C;
    for( int i = 1 , u , v ; i < n ; ++ i ) {
        scanf("%d%d",&u,&v);
        ade( u , v ) , ade( v , u );
    }
    build( );
    dfs1( 1 , 0 );
//    cout << que( rt[3] , 3 ) << endl;
    ST( );
    for( int i = 1 ; i <= blo ; ++ i ) {
        int p = ps[i]; cid = i;
        dfs( p , p );
    }
    int u , v , psu , psv , flg = 0 , re , last = 0 , t , pr;
    while( m-- ) {
        scanf("%d%d",&u,&v);
        u ^= last;
//        cout << u << ' ' << v << endl;
        l = lca( u , v );
        cn = re = 0;
        psu = jump( u ) , psv = jump( v );
        if( psu == psv ) {
            oc[c[l]] = 1 , ++ re;
            for( int i = 1 ; i <= cn ; ++ i ) if( !oc[col[i]] ) oc[col[i]] = 1 , ++ re;
            for( int i = 1 ; i <= cn ; ++ i ) oc[col[i]] = 0;
            oc[c[l]] = 0;
        } else if( ~psu && ~psv ) {
            re = pre[psu][psv];
            for( int i = 1 ; i <= cn ; ++ i ) if( !oc[col[i]] ) {
                    oc[col[i]] = 1;
                    if( que( rt[ps[psu]] , col[i] ) + que( rt[ps[psv]] , col[i] ) - que( rt[par[l]] , col[i] ) * 2 == 0 )
                        ++ re;
                }
            for( int i = 1 ; i <= cn ; ++ i ) oc[col[i]] = 0;
        } else { 
            if( ~psu ) swap( u , v ) , swap( psu , psv );
            pr = l; t = cn;
            while( !im[pr] ) {
                pr = par[pr];
                if( !oc[c[pr]] ) {
                    oc[c[pr]] = 1;
                    if (que(rt[ps[psv]], c[pr]) - que(rt[par[l]], c[pr]) == 0)
                        --re;
                    col[++ cn] = c[pr];
                }
            }
            re += pre[im[pr]][psv];
            for( int i = t + 1 ; i <= cn ; ++ i ) oc[col[i]] = 0;
            cn = t;
            for( int i = 1 ; i <= cn ; ++ i ) if( !oc[col[i]] ) {
                    oc[col[i]] = 1;
                    if( que( rt[ps[psv]] , col[i] ) - que( rt[par[l]] , col[i] ) == 0 )
                        ++ re;
                }
            for( int i = 1 ; i <= cn ; ++ i ) oc[col[i]] = 0;
        }
        printf("%d\n",last = re);
    }
}

```





---

## 作者：lzqy_ (赞：11)

没有 Top Cluster 树分块的题解，这里补一发。

# 定义

- 树簇：树中的一个联通块，满足其与外界相邻的节点**不超过** $2$ 个。

- 界点：树簇与外界相邻的节点。这里钦定深度较浅的是上界点，深度较深的是下界点（上下界点一定是祖孙关系）。

- 收缩树：考虑将树划分成若干个树簇，满足任意一条边**在且仅在一个树簇中**，任意一个点**至少在一个树簇中**。将每个树簇看成一个点后形成的新的树为收缩树。

- 簇路径：树簇中上界点到下界点之间的路径。

考虑将原树划分成 $O(\sqrt n)$ 个大小为 $O(\sqrt n)$ 的树簇，这样对于树上路径问题，就可以像序列问题一样整块整体处理，零散块暴力处理了。

注意，整块整体处理的是**簇路径而不是整个树簇**。

# 实现

考虑对原树进行DFS，标记上下界点。

节点 $x$ 为上界点当且仅当：

- $x$ 为根。

- $x$ 子树中未被划分的节点个数 $\ge \sqrt n$。

- $x$ 子树中有超过一个界点（否则违背树簇定义）。

对于上界点 $x$，还需要将其子树划分为若干个树簇。考虑将 $x$ 每一个子节点的子树划分到一个树簇中去，那么该过程就非常简单了，即子节点 $y$ 被划分到新的树簇当且仅当：

- $y$ 为 $x$ 的最后一个子节点。

- $x$ 在 $y$ 前的子树中未被划分的节点个数 $\ge \sqrt n$。

- $x$ 在 $y$ 前的子树中有超过一个未被划分的界点。

这个过程略显粗糙，但树簇大小的浮动是在常数级别的，可以接受。

-----

具体实现的时候，只需要在每个上界点打个 tag，然后下传标记即可。

注意，由于上界点一定属于多个树簇，所以一般把上界点 $x$ 归到深度较浅的树簇中（$x$ 在深度较浅的树簇中是下界点），并新建一个上下界点都为 $1$ 的根树簇方便处理。

划分树簇且建收缩树的过程如下：

```cpp
il void Merge(int x,int y,int i,int ed){
	L[++N]=x,R[N]=y;
	for(;i^ed;i=e1[i].to) 
		if(e1[i].v^fa1[x]) tag[e1[i].v]=N;//标记tag
}
void init1_dfs(int fa,int x){
	int cnt=0;
	fa1[x]=fa,dep1[x]=dep1[fa]+1,res[x]=1;
	for(int i=head1[x];i;i=e1[i].to)
		if(e1[i].v^fa){
			init1_dfs(x,e1[i].v),res[x]+=res[e1[i].v];
			if(Clu[e1[i].v]) cnt++,Clu[x]=Clu[e1[i].v];
		}
	if(cnt>1||res[x]>=B||x==1){
    //若满足三个条件之一,标记上界点,并划分子树
		Clu[x]=x,res[x]=0;
		int sum=1,id=0,li=head1[x];
		for(int i=head1[x];i;i=e1[i].to)
			if(e1[i].v^fa){
				if(sum+res[e1[i].v]>B||(id&&Clu[e1[i].v]))
					Merge(x,id,li,i),sum=0,id=0,li=i;
					//划分出新树簇,并更新子树大小,和下界点编号
				if(Clu[e1[i].v]) id=Clu[e1[i].v];
				sum+=res[e1[i].v];
			}
		Merge(x,id,li,0);//最后一部分也要划分成新树簇
	}
}
void down_dfs(int fa,int x,int c=N){
	bl[x]=c;bool fl=0;
	for(int i=head1[x];i;i=e1[i].to)
		if(e1[i].v^fa) fl=1,down_dfs(x,e1[i].v,tag[e1[i].v]?tag[e1[i].v]:c);
	if(!fl&&!R[c]) R[c]=x;
    //如果该树簇没有下界点,就随便选择一个叶节点作下界点
	if(fa1[x]&&!Vis[bl[x]]&&(bl[x]^bl[fa1[x]])){
		Vis[bl[x]]=1;//Vis数组保证 bl[x] 与其父节点不重复连边
		addedge2(bl[x],bl[fa1[x]]);
		addedge2(bl[fa1[x]],bl[x]);
	}
}
void init2_dfs(int fa,int x){
	fa2[x]=fa,dep2[x]=dep2[fa]+1;
	for(int i=head2[x];i;i=e2[i].to)
		if(e2[i].v^fa) init2_dfs(x,e2[i].v);
}
.....
int main(){
	.....
	init1_dfs(0,1),L[++N]=1,R[N]=1,bl[1]=N;
	down_dfs(0,1),init2_dfs(0,N);
	return 0;
}
```

# 本题做法

考虑对于本题树分块的做法（以下称树簇为块）。

对于任意两个块 $u,v$ 维护 $\{u\rightarrow v\}$ 路径上所有块簇路径所含颜色的bitset，对于一组询问 $x,y$，先暴力跑出 $x,y$ 所在块的颜色的bitset，然后再或上两点路径的bitset即可（实际实现可能有些不同）。

对于零散块部分，显然时间复杂度是 $O(\sqrt n)$，对于整块部分，只需要进行一次合并，所以时间复杂度是 $O(\frac{n}{w})$。对于预处理部分，分别以每个块为 $u$ 遍历大小为 $O(\sqrt n)$划分树，时间复杂度 $O(\sqrt n \frac{n}{w})$，由于有 $O(\sqrt n)$ 个块，所以预处理总时间复杂度为 $O(\frac{n^2}{w})$。
。

所以该算法的时间复杂度为 $O(\frac{n^2}{w}+n\sqrt n)$。显然在极限数据下后一部分复杂度小于前一部分，所以可以通过调大块长来优化空间（因为要存两两块之间的bitset，所以空间是 $O(\frac{B^2}{w})$）。

完整代码如下：

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define il inline
using namespace std;
const int w=(1<<16)-1;
const int maxn=40010;
const int maxqn=310;
const ull S=18446744073709551615ull;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
struct Hsh{
	int id,x;
	bool operator <(Hsh a)const{return x<a.x;}
}b[maxn];
int nn,pc[1<<16];


//////////bitset
struct Bitset{
	ull a[maxn/64+2];
	il Bitset operator |(Bitset x)const{for(int i=0;i<=nn;i++) x.a[i]|=a[i];return x;}
	il int Count(int cnt=0)const{
		for(int i=0;i<=nn;i++)
			cnt+=pc[a[i]&w]+pc[(a[i]>>16)&w]+pc[(a[i]>>32)&w]+pc[(a[i]>>48)&w];
		return cnt;
	}
}col[maxqn],data[maxqn][maxqn];
il void Add(Bitset &x,int i){x.a[i-1>>6]|=(1ull<<(i-1&63));}
il void clear(Bitset &x){for(int i=0;i<=nn;i++)x.a[i]=0;}
/////////////


struct edge{
	int v,to;
}e1[maxn<<1],e2[maxqn<<1];
int head1[maxn],head2[maxqn];
int ecnt1=1,ecnt2=1;
il void addedge1(int u,int v){
	e1[++ecnt1].v=v,e1[ecnt1].to=head1[u],head1[u]=ecnt1;
}
il void addedge2(int u,int v){
	e2[++ecnt2].v=v,e2[ecnt2].to=head2[u],head2[u]=ecnt2;
}
int a[maxn],n,m,B,N;
int fa1[maxn],dep1[maxn];
int res[maxn],tag[maxn],Clu[maxn];

bool Vis[maxqn];
int fa2[maxqn],dep2[maxqn];
int L[maxqn],R[maxqn];
int bl[maxn];

///////////划分树簇
il void Merge(int x,int y,int i,int ed){
	L[++N]=x,R[N]=y;
	for(;i^ed;i=e1[i].to) 
		if(e1[i].v^fa1[x]) tag[e1[i].v]=N;
}
void init1_dfs(int fa,int x){
	int cnt=0;
	fa1[x]=fa,dep1[x]=dep1[fa]+1,res[x]=1;
	for(int i=head1[x];i;i=e1[i].to)
		if(e1[i].v^fa){
			init1_dfs(x,e1[i].v),res[x]+=res[e1[i].v];
			if(Clu[e1[i].v]) cnt++,Clu[x]=Clu[e1[i].v];
		}
	if(cnt>1||res[x]>=B||x==1){
		Clu[x]=x,res[x]=0;
		int sum=1,id=0,li=head1[x];
		for(int i=head1[x];i;i=e1[i].to)
			if(e1[i].v^fa){
				if(sum+res[e1[i].v]>B||(id&&Clu[e1[i].v]))
					Merge(x,id,li,i),sum=0,id=0,li=i;
				if(Clu[e1[i].v]) id=Clu[e1[i].v];
				sum+=res[e1[i].v];
			}
		Merge(x,id,li,0);
	}
}
void down_dfs(int fa,int x,int c=N){
	bl[x]=c;bool fl=0;
	for(int i=head1[x];i;i=e1[i].to)
		if(e1[i].v^fa) fl=1,down_dfs(x,e1[i].v,tag[e1[i].v]?tag[e1[i].v]:c);
	if(!fl&&!R[c]) R[c]=x;
	if(fa1[x]&&!Vis[bl[x]]&&(bl[x]^bl[fa1[x]])){
		Vis[bl[x]]=1;
		addedge2(bl[x],bl[fa1[x]]);
		addedge2(bl[fa1[x]],bl[x]);
	}
}
void init2_dfs(int fa,int x){
	fa2[x]=fa,dep2[x]=dep2[fa]+1;
	for(int i=head2[x];i;i=e2[i].to)
		if(e2[i].v^fa) init2_dfs(x,e2[i].v);
}
////////////


//////预处理两两块之间的bitset
void initd_dfs(int rt,int fa,int x,Bitset t){
	t=t|col[x],data[rt][x]=t;
	for(int i=head2[x];i;i=e2[i].to)
		if(e2[i].v^fa) initd_dfs(rt,x,e2[i].v,t);
}
//////////

///////零散块内的暴力
il Bitset Query(int x,int y){
	Bitset ans;clear(ans);
	if(dep1[x]<dep1[y]) swap(x,y);
	while(dep1[x]>dep1[y]) Add(ans,a[x]),x=fa1[x];
	while(x^y){
		Add(ans,a[x]),x=fa1[x];
		Add(ans,a[y]),y=fa1[y];
	}Add(ans,a[x]);
	return ans;
}
////////////


il int Solve(int x,int y){
	Bitset ans;clear(ans);
	int u=bl[x],v=bl[y];
	if(dep2[u]<dep2[v]) swap(u,v),swap(x,y);
	if(u==v) return Query(x,y).Count();
	ans=Query(x,L[u]),u=fa2[u];
	int uu=u;
	while(dep2[uu]-1>dep2[v]) uu=fa2[uu];
	if(dep2[uu]-1==dep2[v])ans=ans|data[u][uu],u=fa2[uu];
	if(u^v){
		ans=ans|Query(y,L[v]),v=fa2[v];
		if(dep2[u]>dep2[v]) ans=ans|col[u],u=fa2[u];
	}
	else return (ans|Query(R[v],y)).Count();
	if(u==v) return ans.Count(); 
	int u_=u,v_=v;
	//注意,lca(u,v) 对应的块实际上是没有走过簇路径的
    //所以需要分别或上 u,v 两侧路径的bitset
    while(fa2[u_]^fa2[v_]) u_=fa2[u_],v_=fa2[v_];
	return (ans|data[u][u_]|data[v][v_]).Count();
}
int main(){
	n=read(),m=read(),B=1000;
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=Hsh{i,a[i]};
	}
	sort(b+1,b+1+n);int val=0;
	b[0].x=-1;
	for(int i=1;i<=n;i++){
		if(b[i].x^b[i-1].x) val++;
		a[b[i].id]=val;
	}nn=val/64;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		addedge1(x,y),addedge1(y,x);
	}
	for(int i=1;i<(1<<16);i++) pc[i]=pc[i>>1]+(i&1);
	init1_dfs(0,1),L[++N]=1,R[N]=1,bl[1]=N;
	down_dfs(0,1),init2_dfs(0,N);
	for(int i=1;i<=N;i++){
		int x=R[i];Add(col[i],a[x]);
		while(x^L[i]) x=fa1[x],Add(col[i],a[x]);
        //处理每个块簇路径对应的bitset
	}Bitset t;clear(t);
	for(int i=1;i<=N;i++)
		initd_dfs(i,0,i,t);
	int x,y,lans=0;
	while(m--){
		x=read()^lans,y=read();
		printf("%d\n",lans=Solve(x,y));
	}
	return 0;
}
```

# Top Cluster 树分块的优劣

- 首先，该算法比起一般树分块算法来说，拥有严格的 $O(n\sqrt n)$ 时间复杂度，其次，每个块只有两个端点的特性，使得任意在序列上能维护的信息都能以相同的时间复杂度在树上维护。

- 但是这个玩意…………真的超级难写啊！而且常数也是真的大qwq


---

## 作者：orz_z (赞：8)

给你一棵 $n$ 个节点且带点权的树，$m$ 个询问，每次查询链颜色数。

强制在线。

$1\leq n \leq 4\times 10^4,1\leq m\leq 10^5$。

#### sol

首先如果不强制在线，用树上莫队即可。

但多了个强制在线，容易想到是预处理题。

查询链颜色数，比较好的一种方法是使用 `bitset`，对值域建 `bitset`，答案就是 `bitset` 中 $1$ 的数量。

 那么现在的问题就是怎么把一条路径上的 `bitset` 并起来。

记得离散化。

**法一**

考虑树分块。

考虑用一种简单的树分块技巧——树上撒点。

简单来说就是先设一个阈值 $S$，在树上选择不超过 $\frac{n}{S}$ 个点作为关键点，满足每个关键点到离它最近的祖先关键点的距离不超过 $S$。

具体地，每次选择当前深度最大的一个非关键点，若它的 $1 \sim S$ 级祖先都不是关键点，则把它的 $S$ 级祖先标记为关键点。

由于上述方法中每标记一个关键点，至少有 $S$ 个点不会被标记，所以关键点的数量是正确的。

仔细思考，容易发现每个关键点到离它最近的祖先关键点的距离不超过 $S$ 这个条件也满足。

撒完关键点，再记录两关键点间的 `bitset`，先用 $\mathcal O(S)$ 的时间求出相邻两关键点的 `bitset`，再处理出两两之间的即可，预处理总时间复杂度为 $\mathcal O(\frac{n^2}{S}+\frac{n^3}{wS^2})$。

然后考虑询问，此时询问的路径就被拆成了两个散块和一个整块，散块暴力，整块 `bitset` 取交集即可，总时间复杂度为 $\mathcal O(mS+\frac{nm}{w})$。

取 $S=\sqrt n$，则总时间复杂度为 $\mathcal O((n+m)\sqrt n+\frac{n^2+nm}{w})$，可过。

$\text{1.88s /  20.14MB /  4.15KB C++14 (GCC 9) O2}$。

```cpp
#include <cstdio>
#include <bitset>
#include <algorithm>

#define re register

namespace Fread
{
    const int SIZE = 1 << 23;
    char buf[SIZE], *S, *T;
    inline char getchar()
    {
        if (S == T)
        {
            T = (S = buf) + fread(buf, 1, SIZE, stdin);
            if (S == T)
                return '\n';
        }
        return *S++;
    }
}
namespace Fwrite
{
    const int SIZE = 1 << 23;
    char buf[SIZE], *S = buf, *T = buf + SIZE;
    inline void flush()
    {
        fwrite(buf, 1, S - buf, stdout);
        S = buf;
    }
    inline void putchar(char c)
    {
        *S++ = c;
        if (S == T)
            flush();
    }
    struct NTR
    {
        ~NTR()
        {
            flush();
        }
    } ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

inline int read()
{
	re int x = 0, f = 1;
	re char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

inline void write(re int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

inline void swap(re int &x, re int &y)
{
	x ^= y ^= x ^= y;
}

const int _ = 4e4 + 7;

std::bitset<_> bt[42][42], nw;

int n, m, B, arr[_], a[_], fa[_], dep[_], mxd[_], FF[_], siz[_], tp[_], hson[_];

int id[_], cnt, head[_], tot, ans, sta[_], top, gg[_];

struct edge
{
	int to, nxt;
} e[_ << 1];

void dfs1(re int now, re int D)
{
	siz[now] = 1;
	dep[now] = D;
	mxd[now] = dep[now];
	for (re int i = head[now]; i; i = e[i].nxt)
	{
		re int v = e[i].to;
		if (!dep[v])
		{
			fa[v] = now;
			dfs1(v, D + 1);
			siz[now] += siz[v];
			if (mxd[v] > mxd[now])
				mxd[now] = mxd[v];
			if (siz[hson[now]] < siz[v])
				hson[now] = v;
		}
	}
	if (mxd[now] - dep[now] >= 1000)
		id[now] = ++tot, mxd[now] = dep[now];
}

void dfs2(re int now)
{
	for (re int i = head[now]; i; i = e[i].nxt)
	{
		re int v = e[i].to;
		if (dep[v] > dep[now])
		{
			if (id[v])
			{
				int ip = id[sta[top]], in = id[v];
				for (int x = v; x != sta[top]; x = fa[x])
					bt[ip][in].set(a[x]);
				nw = bt[ip][in];
				for (int i = 1; i < top; ++i)
				{
					std::bitset<_> &bs = bt[id[sta[i]]][in];
					bs = bt[id[sta[i]]][ip];
					bs |= nw;
				}
				FF[v] = sta[top], gg[v] = gg[sta[top]] + 1;
				sta[++top] = v;
			}
			dfs2(v);
			if (id[v])
				--top;
		}
	}
}

void dfs3(re int now, re int tf)
{
	tp[now] = tf;
	if (hson[now])
		dfs3(hson[now], tf);
	for (re int i = head[now]; i; i = e[i].nxt)
	{
		re int v = e[i].to;
		if (!tp[v])
			dfs3(v, v);
	}
}

inline int LCA(re int x, re int y)
{
	while (tp[x] != tp[y])
	{
		if (dep[tp[x]] < dep[tp[y]])
			swap(x, y);
		x = fa[tp[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

signed main()
{
	n = read(), m = read();
	for (re int i = 1; i <= n; ++i)
		arr[i] = a[i] = read();
	std::sort(arr + 1, arr + 1 + n);
	arr[0] = std::unique(arr + 1, arr + 1 + n) - arr - 1;
	for (re int i = 1; i <= n; ++i)
		a[i] = std::lower_bound(arr + 1, arr + 1 + arr[0], a[i]) - arr;
	for (re int i = 1, u, v; i < n; ++i)
	{
		u = read(), v = read();
		e[++cnt] = (edge){v, head[u]}, head[u] = cnt;
		e[++cnt] = (edge){u, head[v]}, head[v] = cnt;
	}
	dfs1(1, 1);
	if (!id[1])
		id[1] = ++tot;
	sta[top = 1] = gg[1] = 1;
	dfs2(1);
	dfs3(1, 1);
	while (m--)
	{
		int u = read() ^ ans, v = read();
		nw.reset();
		int l = LCA(u, v);
		while (u != l && !id[u])
			nw.set(a[u]), u = fa[u];
		while (v != l && !id[v])
			nw.set(a[v]), v = fa[v];
		if (u != l)
		{
			int pre = u;
			while (dep[FF[pre]] >= dep[l])
				pre = FF[pre];
			if (pre != u)
				nw |= bt[id[pre]][id[u]];
			while (pre != l)
				nw.set(a[pre]), pre = fa[pre];
		}
		if (v != l)
		{
			int pre = v;
			while (dep[FF[pre]] >= dep[l])
				pre = FF[pre];
			if (pre != v)
				nw |= bt[id[pre]][id[v]];
			while (pre != l)
				nw.set(a[pre]), pre = fa[pre];
		}
		nw.set(a[l]);
		write(ans = nw.count()), putchar('\n');
	}
	return 0;
}
```

**法二**

考虑轻重链剖分，询问时将路径上的若干条重链的 `bitset` 并起来即可。

由于重链上的点的 `dfn` 序是连续的，序列分块即可。

每次询问，跳重链分块计算这条重链的贡献即可。

时间复杂度为 $\mathcal O(\frac{n^2}{w}+m\log n(\sqrt{n}+\frac{n}{w}))$。

$\text{1.05s /  18.14MB /  3.47KB C++14 (GCC 9) O2}$。

```cpp
#include <cstdio>
#include <bitset>
#include <algorithm>

#define re register

namespace Fread
{
	const int SIZE = 1 << 23;
	char buf[SIZE], *S, *T;
	inline char getchar()
	{
		if (S == T)
		{
			T = (S = buf) + fread(buf, 1, SIZE, stdin);
			if (S == T)
				return '\n';
		}
		return *S++;
	}
}
namespace Fwrite
{
	const int SIZE = 1 << 23;
	char buf[SIZE], *S = buf, *T = buf + SIZE;
	inline void flush()
	{
		fwrite(buf, 1, S - buf, stdout);
		S = buf;
	}
	inline void putchar(char c)
	{
		*S++ = c;
		if (S == T)
			flush();
	}
	struct NTR
	{
		~NTR()
		{
			flush();
		}
	} ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

inline int read()
{
	re int x = 0, f = 1;
	re char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 4e4 + 7, W = 4e4 + 7, B = 1e3;

std::bitset<W> f[42][42], nw;

int n, m, cnt_node, ans, tot, a[_], arr[_], fa[_], dep[_], siz[_], hson[_], top[_], dfn[_], b[_], bel[_], L[_], R[_], head[_], to[_ << 1], nxt[_ << 1];

inline void swap(re int &x, re int &y)
{
	x ^= y ^= x ^= y;
}

inline void add(re int u, re int v)
{
	to[++tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
}

void dfs1(re int u, re int D)
{
	dep[u] = D, siz[u] = 1;
	for (re int i = head[u]; i; i = nxt[i])
	{
		re int v = to[i];
		if (siz[v])
			continue;
		fa[v] = u;
		dfs1(v, D + 1);
		siz[u] += siz[v];
		if (siz[hson[u]] < siz[v])
			hson[u] = v;
	}
}

void dfs2(re int u, re int tf)
{
	top[u] = tf, dfn[u] = ++cnt_node, a[cnt_node] = b[u];
	if (!hson[u])
		return;
	dfs2(hson[u], tf);
	for (re int i = head[u]; i; i = nxt[i])
	{
		re int v = to[i];
		if (top[v])
			continue;
		dfs2(v, v);
	}
}

inline void pre()
{
	for (re int i = 1; i <= n; ++i)
	{
		bel[i] = (i - 1) / B + 1;
		f[bel[i]][bel[i]].set(a[i]);
	}
	for (re int i = 1; i <= bel[n]; ++i)
		L[i] = R[i - 1] + 1, R[i] = i * B;
	R[bel[n]] = n;
	for (re int i = 1; i < bel[n]; ++i)
		for (re int j = i + 1; j <= bel[n]; ++j)
			f[i][j] = f[i][j - 1] | f[j][j];
}

inline void Query_on_block(re int l, re int r)
{
	if (bel[l] == bel[r])
	{
		for (re int i = l; i <= r; ++i)
			nw.set(a[i]);
		return;
	}
	nw |= f[bel[l] + 1][bel[r] - 1];
	for (re int i = l; i <= R[bel[l]]; ++i)
		nw.set(a[i]);
	for (re int i = L[bel[r]]; i <= r; ++i)
		nw.set(a[i]);
}

inline void Query_on_tree(re int u, re int v)
{
	while (top[u] != top[v])
	{
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		Query_on_block(dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	Query_on_block(dfn[u], dfn[v]);
}

signed main()
{
	n = read(), m = read();
	for (re int i = 1; i <= n; ++i)
		arr[i] = b[i] = read();
	std::sort(arr + 1, arr + 1 + n);
	arr[0] = std::unique(arr + 1, arr + 1 + n) - arr - 1;
	for (re int i = 1; i <= n; ++i)
		b[i] = std::lower_bound(arr + 1, arr + 1 + arr[0], b[i]) - arr;
	re int u, v;
	for (re int i = 1; i < n; ++i)
	{
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs1(1, 1), dfs2(1, 1);
	pre();
	while (m--)
	{
		nw.reset();
		u = read() ^ ans, v = read();
		Query_on_tree(u, v);
		write(ans = nw.count()), putchar('\n');
	}
}
```





---

## 作者：tzc_wk (赞：7)

upd on 2022.2.23：修了个 typo。

[洛谷题面传送门](https://www.luogu.com.cn/problem/P6177)

~~好家伙，在做这道题之前我甚至不知道有个东西叫树分块~~

树分块，说白了就是像对序列分块一样设一个阈值 $B$，然后在树上随机撒 $\dfrac{n}{B}$ 个关键点，满足任意一个点到距离其最近的关键点距离不超过 $\mathcal O(B)$ 级别，这样我们就可以预处理关键点两两之间的信息，然后询问两个点路径上的信息时直接将预处理的信息拿出来使用，再额外加上两个端点到距离它们最近的关键点之间的路径的贡献即可算出答案，复杂度 $\mathcal O(B^2+qB+\dfrac{n^2}{B})$，一般 $B$ 取 $\sqrt{n}$

当然这个“随机撒点”也并不用什么高超的玄学技巧，甚至不用随机（）。一个很显然的想法是将深度 $\bmod B=0$ 设为关键点，但稍微懂点脑子即可构造出反例：一条长度为 $B$ 的链下面挂 $n-B$ 个叶子。因此考虑对上面的过程做点手脚，我们记 $dis_i$ 为 $i$ 到距离它最**远**的叶子节点的距离，那么我们将深度 $\bmod B=0$ 且 $dis_i\ge B$ 的点 $i$ 设为关键节点即可，容易证明在这种构造方法下关键点个数是严格 $\dfrac{n}{B}$ 级别的，读者自证不难，复杂度也就得到了保证。

接下来考虑怎样求出答案，我们首先预处理出每堆关键节点路径上颜色的情况，用 `bitset` 维护，该操作显然可以以 $\mathcal O(\dfrac{n^2}{B})$ 的及 $\mathcal O(\dfrac{n^3}{B^2\omega})$ 空间复杂度完成。那么对于一组询问 $x,y$，记 $x$ **祖先**中离其最近的关键点为 $fx$，$fy$ 的定义类似，$l=\text{LCA}(x,y)$，分三种情况：

- $fx,fy$ 的深度均 $<l$ 的深度，根据关键点的生成方式可知任意一条自上而下的长度为 $2B$（注意，这里不是 $B$，因为对于叶子节点而言，其祖先中离其最近的关键节点与其的距离可能达到 $2B$）的链上必有一个关键节点，因此 $x$ 到 $l$ 的距离必定小于 $2B$，$y$ 同理，对于这种情况暴力跳父亲不会出问题
- $fx,fy$ 中恰有一个深度 $<l$ 的深度，那我们不妨设 $fy$ 深度 $<l$ 的深度，那么我们就找出 $x\to l$ 这条链上离 $l$ 最近的关键点 $z$，具体方法是，我们倍增找出 $x$ 的 $dep_x-dep_l-2B$ 级祖先，然后暴力向上跳，每遇到一个关键点就将 $z$ 设为关键节点，那么我们根据预处理的值找到 $z$ 与 $fx$ 之间的答案，然后加上 $x\to fx,z\to l,y\to l$ 这三段的答案即可
- $fx,fy$ 深度均 $\ge l$ 的深度，那么我们直接找出 $fx,fy$ 之间的答案，然后加上 $x\to fx,y\to fy$ 的答案即可。

时间复杂度 $\mathcal O(\dfrac{n^2}{B}+qB+\dfrac{n^3}{B^2\omega})=\mathcal O(n\sqrt{n}+\dfrac{n^2}{\omega})$，常数略有点大，但实际跑起来不算慢（

```cpp
const int MAXN=4e4;
const int LOG_N=16;
const int BLK=200;
int n,qu,a[MAXN+5],key[MAXN+5],uni[MAXN+5],num=0;
int hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int id[MAXN+5],pcnt=0,blk,buc[MAXN+5];
int dis[MAXN+5],dep[MAXN+5],fa[MAXN+5][LOG_N+2];
bitset<MAXN+5> col[21000],vis;
void dfs0(int x,int f){
	fa[x][0]=f;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;dep[y]=dep[x]+1;
		dfs0(y,x);chkmax(dis[x],dis[y]+1);
	} if(dep[x]%blk==0&&dis[x]>=blk) id[x]=++pcnt;
}
int qwq[BLK+5][BLK+5],cc=0;
void dfs(int x,int f,int rt){
	buc[a[x]]++;if(buc[a[x]]==1) vis.set(a[x]);
	if(id[x]) col[qwq[id[rt]][id[x]]]=vis;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		dfs(y,x,rt);
	} buc[a[x]]--;if(!buc[a[x]]) vis.reset(a[x]);
}
int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=LOG_N;~i;i--) if(dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=LOG_N;~i;i--) if(fa[x][i]^fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int jump(int x){
	while(x){
		if(id[x]) return x;
		x=fa[x][0];
	} return 0;
}
int get_kanc(int x,int k){
	for(int i=LOG_N;~i;i--) if(k>>i&1) x=fa[x][i];
	return x;
}
int main(){
//	freopen("C:\\Users\\汤\\Downloads\\P6177_1.in","r",stdin);
//	cout<<sizeof(col)<<endl;
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),key[i]=a[i];
	key[0]=-1;sort(key+1,key+n+1);
	for(int i=1;i<=n;i++) if(key[i]^key[i-1]) uni[++num]=key[i];
	for(int i=1;i<=n;i++) a[i]=lower_bound(uni+1,uni+num+1,a[i])-uni;
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	blk=(int)sqrt(n);dfs0(1,0);dep[0]=-1;
	for(int i=1;i<=pcnt;i++) for(int j=1;j<=i;j++) qwq[i][j]=qwq[j][i]=++cc;
	for(int i=1;i<=n;i++) if(id[i]) memset(buc,0,sizeof(buc)),dfs(i,0,i);
	for(int i=1;i<=LOG_N;i++) for(int j=1;j<=n;j++)
		fa[j][i]=fa[fa[j][i-1]][i-1];
	int pre=0;
	while(qu--){
		int x,y;scanf("%d%d",&x,&y);x^=pre;vis.reset();
		int l=getlca(x,y),fx=jump(x),fy=jump(y);
		if(dep[fx]<dep[l]&&dep[fy]<dep[l]){
			while(x!=l) vis.set(a[x]),x=fa[x][0];
			while(y!=l) vis.set(a[y]),y=fa[y][0];
			vis.set(a[l]);
			printf("%d\n",pre=vis.count());
		} else if(dep[fx]>=dep[l]&&dep[fy]>=dep[l]){
			vis=col[qwq[id[fx]][id[fy]]];
			while(x!=fx) vis.set(a[x]),x=fa[x][0];
			while(y!=fy) vis.set(a[y]),y=fa[y][0];
			printf("%d\n",pre=vis.count());
		} else{
			if(dep[fy]>=dep[l]) swap(x,y),swap(fx,fy);
			assert(dep[fy]<dep[l]);
			int z=get_kanc(x,max(dep[x]-dep[l]-(blk<<1|1),0));
			int near=-1;
			while(z!=l){
				if(id[z]) near=z;
				z=fa[z][0];
			} if(id[l]) near=l;
			assert(~near);
			if(fx!=near) vis=col[qwq[id[fx]][id[near]]];
			while(x!=fx) vis.set(a[x]),x=fa[x][0];
			while(near!=l) vis.set(a[near]),near=fa[near][0];
			while(y!=l) vis.set(a[y]),y=fa[y][0];
			vis.set(a[l]);
			printf("%d\n",pre=vis.count());
		}
	}
	return 0;
}
```



---

## 作者：clamee (赞：7)

想学习树分块的话可以先看我的 blog [link](https://www.luogu.com.cn/blog/55201/shu-fen-kuai-xue-xi-bi-ji)。 

按我的那篇博客的法三分块以后的每个询问被拆成了两个零散块和一个整块，我们记两个零散块所构成的集合分别为 $A$ 和 $B$，整块构成的集合为 $C$，那么答案就为 $|A\cup B\cup C||A|+|B|+|C|-|A\cap B|-|B\cap C|-|A\cap C|+|A\cap B\cap C|$。

然后发现 $|A|,|B|,|A\cap B|,|A\cap B\cap C|$ 可以在处理零散块的时候直接计算，剩下的 $|B\cap C|,|A\cap C|,|B\cap C|$ 可以 $O(n\sqrt{n})$ 预处理。

方法是从每个块的深度最浅的点 dfs 一遍就行了。

此外 $|A\cap B\cap C|$ 的维护方式是在 $A\cap B$ 中找点判断与 $C$ 是否有交，具体的判断方法见代码。

复杂度 $O((n+q)\sqrt{n})$。
```
#include<bits/stdc++.h>
using namespace std;

#define il inline
#define rg register

il int read()
{
	int re=0,k=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')k=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){re=re*10+ch-48;ch=getchar();}
	return re*k;
}

il void write(int x)
{
	if(x<0)return putchar('-'),write(-x),void();
	if(x<10)return putchar(x+48),void();
	return write(x/10),write(x%10),void();
}

const int BB=351;

int h[100005],l[100005],head[100005],tot,d[100005],fa[100005],top[100005],n,a[100005],sz[100005],son[100005],f[405][100005],p[405],ls,t[100005],c[100005],g[100005];
int fs[2000005],tt;
bool vis[100005];
int vis2[100005],vis1[100005];
struct ss{
    int node,nxt;
}e[100005];
void add(int u,int v)
{
    e[++tot].nxt=head[u];
    e[tot].node=v;
    head[u]=tot;
}
void dfs(int x,int ffa,int dp)
{
	fa[x]=ffa;
	d[x]=dp;
	sz[x]=1;
	
	int maxsz=-1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int k=e[i].node;
		if(k==ffa)continue;
		if(!vis[k])
			g[k]=g[x];
		else g[k]=k;
		dfs(k,x,dp+1);
		sz[x]+=sz[k];
		if(maxsz<sz[k])maxsz=sz[k],son[x]=k;
	}
}
void ddfs(int x,int tt)
{
	top[x]=tt;
	l[x]=h[a[x]];//预处理头顶第一个和它相同的点的
	if(!son[x])return;
	h[a[x]]=x;
	ddfs(son[x],tt);
	for(int i=head[x];i;i=e[i].nxt)
	{
		int k=e[i].node;
		if(fa[x]==k||son[x]==k)continue;
		ddfs(k,k);
	}
	h[a[x]]=l[x];
}
int lca(int x,int y)//树剖LCA
{
	while(top[x]!=top[y])
	{
		if(d[top[x]]<d[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(d[x]>d[y])swap(x,y);
	return x;
}

void dp(int x,int fa,int *ff,int *s,int ls,int ans)//从每个点开始进行预处理
{
	if(!x)return;
	s[++ls]=a[x];
	if(t[a[x]]&&!vis2[a[x]])ans++;
	vis2[s[ls]]++;
	if(vis[x])//预处理 C
	{
		for(int i=1;i<=ls;i++)
		{
			if(!t[s[i]])tt++;
			t[s[i]]++,vis2[s[i]]--;
		}
		ff[x]=tt;
	}
	else ff[x]=ans;//预处理 A 交 B
	for(rg int i=head[x];i;i=e[i].nxt)
	{
		if(e[i].node==fa)continue;
		if(vis[x])
		{	
			dp(e[i].node,x,ff,s+ls,0,0);
		}
		else
		{
			dp(e[i].node,x,ff,s,ls,ans);
		}
	}
	if(vis[x])
	{
		for(int i=1;i<=ls;i++)
		{
			t[s[i]]--;vis2[s[i]]++;
			if(!t[s[i]])tt--;
		}
	}
	vis2[s[ls]]--;
}
int sol(int u,int v,int typ)
{
	int lans=0;
   	int x=u,y=v,LCA=lca(u,v);
   	while(x!=LCA){if(!vis1[a[x]])lans++;vis1[a[x]]=1;x=fa[x];}
   	while(y!=LCA){if(!typ||y!=v){if(!vis1[a[y]])lans++;vis1[a[y]]=1;}y=fa[y];}
	if(!vis1[a[LCA]]&&(!typ||LCA!=v))lans++;
   	while(u!=LCA){vis1[a[u]]=0;u=fa[u];}
   	while(v!=LCA){vis1[a[v]]=0;v=fa[v];}
   	return lans;
}

int b[100005],cnt,q;

int main()
{
	freopen("2.in","r",stdin);
	freopen("2.out","w",stdout);
    n=read();q=read();
   	for(rg int i=1;i<=n;i++)
   	{
   		b[++cnt]=a[i]=read();
   		c[i]=i;
   	}
   	for(rg int i=1,u,v;i<n;i++)
   	{
   		u=read();v=read();
   		add(u,v);add(v,u);
   	}
   	srand(time(0));
   	sort(b+1,b+cnt+1);
   	cnt=unique(b+1,b+cnt+1)-b-1;
   	random_shuffle(c+2,c+n+1);
   	for(rg int i=1;i<=n;i++)
   	{
   		if(i<=BB)p[i]=c[i],vis[c[i]]=1;
   		a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
   	}
	g[1]=1;
   	dfs(1,0,1);
   	ddfs(1,1);
   	for(rg int i=1;i<=BB;i++)
   	{
   		dp(p[i],0,f[i],fs,0,0);
   	}
   	int lans=0;
	memset(vis1,0,sizeof(vis1));
	memset(vis2,0,sizeof(vis2));
   	for(rg int i=1,u,v;i<=q;i++)
   	{
   		u=read()^lans;v=read();
   		if(g[u]==g[v])//零散块
   		{
   			lans=0;
   			int x=u,y=v,LCA=lca(u,v);
   			while(x!=LCA){if(!vis1[a[x]])lans++;vis1[a[x]]=1;x=fa[x];}
   			while(y!=LCA){if(!vis1[a[y]])lans++;vis1[a[y]]=1;y=fa[y];}
			if(!vis1[a[LCA]])lans++;
   			while(u!=LCA){vis1[a[u]]=0;u=fa[u];}
   			while(v!=LCA){vis1[a[v]]=0;v=fa[v];}
   			write(lans);puts("");continue;
   		}
		int LCA=lca(u,v);
   		if(d[g[u]]<d[LCA]||d[g[v]]<d[LCA])//两个块之间是直系亲属关系
   		{
   			if(d[g[u]]<d[LCA])swap(u,v);
   			int x=u,y=v,z=u,A=0,B=0,C=0,AB=0,BC=0,AC=0,ABC=0,xx=u,yy=v,ty;
   			while(!vis[x]&&x!=LCA)
   			{
				if(!vis1[a[x]])
					A++;
				vis1[a[x]]=x;
				x=fa[x];
			}
   			while(!vis[y]&&y!=LCA)
   			{
   				if(!vis2[a[y]])
   				{
   					B++;
   					if(vis1[a[y]])
   					{
   						AB++;
   					}
   				}
   				vis2[a[y]]=y;y=fa[y];
   			}
   			while(d[g[fa[g[z]]]]>d[LCA])z=fa[g[z]];
   			ty=z=g[z];
   			z=fa[z];
   			int zz=z;
   			while(!vis[z]&&z!=LCA)
   			{
   				if(!vis2[a[z]])
   				{
   					B++;
   					if(vis1[a[z]])
   					{
   						AB++;
   					}
   				}
   				vis2[a[z]]=z;z=fa[z];
   			}
   			if(!vis2[a[LCA]])
   			{
   				B++;
   				if(vis1[a[LCA]])AB++;
   			}
			vis2[a[LCA]]=LCA;
 	  		while(!vis[yy]&&yy!=LCA)
 	  		{
 	  			if(vis2[a[yy]]&&vis1[a[yy]])
 	  			{
 	  				if((d[l[vis1[a[yy]]]]>=d[ty]&&d[l[vis1[a[yy]]]]<=d[x]))
 	  					ABC++;
 	  			}
 	  			vis2[a[yy]]=0;yy=fa[yy];
 	  		}
 	  		while(!vis[zz]&&zz!=LCA)
 	  		{
 	  			if(vis2[a[zz]]&&vis1[a[zz]])
 	  			{
 	  				if((d[l[vis1[a[zz]]]]>=d[ty]&&d[l[vis1[a[zz]]]]<=d[x]))
 	  					ABC++;
 	  			}
 	  			vis2[a[zz]]=0;zz=fa[zz];
 	  		}
			if(vis2[a[LCA]])
   			{
   				if(vis1[a[LCA]])
					if((d[l[vis1[a[LCA]]]]>=d[ty]&&d[l[vis1[a[LCA]]]]<=d[x]))
 	  					ABC++;
   			}
			vis2[a[LCA]]=0;
 	  		while(!vis[xx]&&xx!=LCA){vis1[a[xx]]=0;xx=fa[xx];}
 	  		for(rg int j=1;j<=BB;j++)
 	  			if(p[j]==x){x=j;break;}
 	  		for(rg int j=1;j<=BB;j++)
 	  			if(p[j]==ty){ty=j;break;}
   			C=f[x][p[ty]];
   			if(!vis[v])BC=f[x][v];
   			if(!vis[u])AC=f[ty][u];
   			lans=A+B+C-AB-BC-AC+ABC;
   			write(lans);puts("");continue;
   		}
        //两块之间不是直系亲属关系
   		int x=u,y=v,A=0,B=0,C=0,AB=0,BC=0,AC=0,ABC=0,xx=u,yy=v;
   		while(!vis[x]&&x!=LCA)
   		{
   			if(!vis1[a[x]])
   				A++;
   			vis1[a[x]]=x;
   			x=fa[x];
   		}
   		while(!vis[y]&&y!=LCA)
   		{
   			if(!vis2[a[y]])
   			{
   				B++;
   				if(vis1[a[y]])
   				{
   					AB++;
   				}
   			}
   			vis2[a[y]]=y;y=fa[y];
   		}
   		while(!vis[yy]&&yy!=LCA)
   		{
   			if(vis2[a[yy]]&&vis1[a[yy]])
   			{
   				if(((d[l[vis1[a[yy]]]]>=d[LCA])&&(d[l[vis1[a[yy]]]]<=d[x]))||((d[l[vis2[a[yy]]]]>=d[LCA])&&(d[l[vis2[a[yy]]]]<=d[y])))
   					ABC++;
   			}
   			vis2[a[yy]]=0;yy=fa[yy];
   		}
   		while(!vis[xx]&&xx!=LCA){vis1[a[xx]]=0;xx=fa[xx];}
   		for(rg int j=1;j<=BB;j++)
   			if(p[j]==x){x=j;break;}
   		for(rg int j=1;j<=BB;j++)
   			if(p[j]==y){y=j;break;}
   		C=f[x][p[y]];
   		if(!vis[v])BC=f[x][v];
   		if(!vis[u])AC=f[y][u];
   		lans=A+B+C-AB-BC-AC+ABC;
   		write(lans);puts("");
   	}
}
```


---

## 作者：0xyz (赞：5)

写了一点神奇的东西，具体来说是 @critnos 的代码实现。

这题确实有可以跑得飞快的平方除以 $\omega$ 算法，以及跑得更快的平方 $\log$ 除以 $\omega$ 算法。但是既然是树分块模板题，那么我就写了个常数超大的树分块。

### 1. 寻找关键点

我们随机出 $\frac{\sqrt n}{2}$ 个点，建立出它们的虚树。这样一来，我们可以做到每个点向上跳直到跳到关键点上所需要跳的次数是期望 $O(\sqrt n)$，关键点个数是 $O(\sqrt n)$，并且对于每两个关键点，它们的最近公共祖先也是关键点。由于我们要所有点向上跳都有关键点，所以我们可以在一开始钦定节点 $1$ 为关键点，后面处理的时候以 $1$ 号节点为根。

### 2. 具体做法

我们在找出 $O(\sqrt n)$ 个关键点之后，首先要记录关键点之间的答案。我们可以开一个记录颜色的桶，以每一个关键点为根都跑一次深搜，像莫队转移一样记录搜索到每个点时它到当前的根节点的路径上有多少种不同的颜色。这样总的时间复杂度是 $O(n\sqrt n)$ 的。

接下来，我们以 $1$ 为根开始深搜，预处理出每个点的祖先（不算它自己）中，离它最近的关键点是哪一个。同时，我们可以用记录颜色的桶记录下来从 $1$ 号节点到每一个关键点的路径上，每种颜色出现了几次。时间复杂度 $O(n\sqrt n)$。

然后处理完了这些，我们可以开始查询。查询主要就是暴力计算散点，对于 $O(\sqrt n)$ 的散点，分别查询它们在中间的整块上出现了几次。这可以用树上前缀和来维护。

具体来说，每次查询，我们对于还原后的 $x,y$，求出它们的祖先（包括他们自己）中最近的关键点 $fx,fy$，以及 $fx,fy$ 的最近公共祖先 $lc$。然后开始分类讨论：

1. $lc\ne fx\land lc\ne fy$。此时我们直接暴力跳 $x\to fx,y\to fy$，再加上 $fx$ 与 $fy$ 之间预处理好的答案就好了。时间复杂度 $O(\sqrt n)$。

2. $fx=fy\land lc\ne fx$。因为我们知道 $x\to fx$ 的距离和 $y\to fy$ 的距离都是 $O(\sqrt n)$ 的，所以我们直到 $x\to y$ 的距离就是 $O(\sqrt n)$ 的。直接暴力分别跳 $x\to lca(x,y),y\to lca(x,y)$ 就好了。时间复杂度 $O(\sqrt n)$。

3. 其他情况。此时我们一定有 $fx=lc$ 与 $fy=lc$ 恰有一个满足，由于 $x,y$ 对称，我们不妨假设 $fx=lc$。那么我们可以从 $fy$ 开始，不断往上跳最近的关键点直到再跳一次关键点的深度就会小于等于 $x$ 的深度。假设这个关键点是 $ty$，那么答案就是 $x\to lca(x,ty)$ 的散点，$ty\to lca(x,ty)$ 的散点和 $y\to fy$ 的散点，再加上 $fy\to ty$ 的整块。时间复杂度 $O(\sqrt n)$。

在跳的时候，为了保证每种颜色只被算一次，我们可以维护一个桶记录我们已经算过了哪些颜色。为了避免复杂度退化，我们清空桶的时候再重复以上的跳法就好了。

### 3. 代码

主要长度在于有很多重复内容并且很好理解的分类讨论。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _=1e5+5,o=210;
int n,cnt,v,k,c,m,t,a[_],b[_],f[18][_],lg[_],p[_],q[_];
int dep[_],dfn[_],tot,nr[_],fa[_],h[_],s[o][_],pa[o][o];
vector<int>e[_];
int get(int x,int y){
	return dep[x]<dep[y]?x:y;
}
void dfs(int x,int fat){
	f[0][dfn[x]=++cnt]=x;
	dep[x]=dep[fa[x]=fat]+1;
	for(auto y:e[x])
		if(y!=fat)dfs(y,x);
}
void pas(int x,int fat,int rt){
	if(!h[a[x]]++)tot++;
	if(p[x])pa[rt][p[x]]=tot;
	for(auto y:e[x])
		if(y!=fat)pas(y,x,rt);
	if(!--h[a[x]])tot--;
}
void pre(int x,int nea){
	nr[x]=nea;h[a[x]]++;
	if(p[x])
		for(int i=1;i<=v;i++)s[p[x]][i]=h[i];
	for(auto y:e[x])
		if(y!=fa[x])pre(y,p[x]?x:nea);
	h[a[x]]--;
}
int lca(int x,int y){
    if(x==y)return x;
	if(dfn[x]>dfn[y])swap(x,y);
	int ln=lg[dfn[y]-dfn[x]];
	return fa[get(f[ln][dfn[x]+1],f[ln][dfn[y]-(1<<ln)+1])];
}
int main(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;c=k=sqrt(n)/2;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);v=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+v+1,a[i])-b;
	for(int i=1,x,y;i<n;i++)cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
	dfs(1,0);
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=16;i++)
		for(int j=1;j<=n-(1<<i-1);j++)f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	p[q[1]=1]=p[0]=1;
	for(int i=2;i<=k;i++){
		while(p[q[i]])q[i]=rand()%(n-1)+1;
		p[q[i]]=1;
	}
	sort(q+1,q+k+1,[&](int x,int y){return dfn[x]<dfn[y];});
	for(int i=1;i<k;i++)q[++c]=lca(q[i],q[i+1]);
	sort(q+1,q+c+1);c=unique(q+1,q+c+1)-q-1;
	for(int i=1;i<=c;i++)p[q[i]]=i;
	for(int i=1;i<=c;i++)pas(q[i],0,i);
	pre(1,0);
	for(int x,y,lc,fx,fy,ty,ans,la=0;m;m--){
		cin>>x>>y;x^=la;
		fx=p[x]?x:nr[x];fy=p[y]?y:nr[y];
		lc=lca(fx,fy);ans=0;
		if(lc!=fx&&lc!=fy){
			for(int i=x;i!=fx;i=fa[i])
				if(!h[a[i]]){
					ans+=s[p[fx]][a[i]]+s[p[fy]][a[i]]+(a[i]==a[lc])==2*s[p[lc]][a[i]];
					h[a[i]]=1;
				}
			for(int i=y;i!=fy;i=fa[i])
				if(!h[a[i]]){
					ans+=s[p[fx]][a[i]]+s[p[fy]][a[i]]+(a[i]==a[lc])==2*s[p[lc]][a[i]];
					h[a[i]]=1;
				}
			for(int i=x;i!=fx;i=fa[i])h[a[i]]=0;
			for(int i=y;i!=fy;i=fa[i])h[a[i]]=0;
			cout<<(la=ans+pa[p[fx]][p[fy]])<<'\n';
		}else if(fx==fy){
			lc=lca(x,y);
			for(int i=x;i!=fa[lc];i=fa[i])
				if(!h[a[i]])ans++,h[a[i]]=1;
			for(int i=y;i!=lc;i=fa[i])
				if(!h[a[i]])ans++,h[a[i]]=1;
			for(int i=x;i!=fa[lc];i=fa[i])h[a[i]]=0;
			for(int i=y;i!=lc;i=fa[i])h[a[i]]=0;
			cout<<(la=ans)<<'\n';
		}else{
        
			if(fy==lc)swap(x,y),swap(fx,fy);ty=fy;
			while(dep[nr[ty]]>dep[x])ty=nr[ty];
			lc=lca(x,y);
			for(int i=x;i!=fa[lc];i=fa[i])
				if(!h[a[i]]){
					ans+=s[p[fy]][a[i]]+(a[i]==a[ty])==s[p[ty]][a[i]];
					h[a[i]]=1;
				}
			for(int i=ty;i!=lc;i=fa[i])
				if(!h[a[i]]){
					ans+=s[p[fy]][a[i]]+(a[i]==a[ty])==s[p[ty]][a[i]];
					h[a[i]]=1;
				}
			for(int i=y;i!=fy;i=fa[i])
				if(!h[a[i]]){
					ans+=s[p[fy]][a[i]]+(a[i]==a[ty])==s[p[ty]][a[i]];
					h[a[i]]=1;
				}
			for(int i=x;i!=fa[lc];i=fa[i])h[a[i]]=0;
			for(int i=ty;i!=lc;i=fa[i])h[a[i]]=0;
			for(int i=y;i!=fy;i=fa[i])h[a[i]]=0;
			cout<<(la=ans+pa[p[fy]][p[ty]])<<'\n';
		}
	}
	return 0;
}
```

空间复杂度 $O(n\sqrt n)$，时间复杂度 $O((n+m)\sqrt n)$。

---

## 作者：EnofTaiPeople (赞：5)

相信大家都会 $\text{Top cluster}$ 分解吧，其实任何的树分块都可以通过随机撒点解决，如果强行需要形成簇的话还需要建一棵虚树。

但本题并不需要形成簇，所以只要随机选取 $\sqrt n$ 个节点作为关键点，然后处理任意两点之间路径上所有点颜色 `bitset`，查询时只需要将路径上最左和最右的关键点取出，边块暴力即可。

虽然这样的空间复杂度十分的劣质，但还是足以通过。

空间复杂度 $O(\dfrac{n^2}w)$，时间 $O(\dfrac{n^2+nq}w)$，由于撒的点不多，并且随机不够严格，所以常数较大：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e4+4;
using bt=bitset<N>;
bt tb[205][205],nw;
#define tp(x) (t[f[x]][1]==x)
#define in(x) (t[f[x]][0]==x||tp(x))
#define ls t[x][0]
#define rs t[x][1]
int v[N],n,q,mp[N],m,ct[N],ans;
int p[N],dfn[N],dlt,rt,cl[N];
vector<int>lk[N];
namespace lct{
    int f[N],t[N][2],sm[N];
    bt rv;
    void pp(int x){
        sm[x]=sm[ls]|sm[rs]|cl[x];
    }void rev(int x){
        swap(ls,rs),rv[x]=!rv[x];
    }void pd(int x){
        if(rv[x]){
            if(ls)rev(ls);
            if(rs)rev(rs);rv[x]=0;
        }
    }void ppd(int x){
        if(in(x))ppd(f[x]);pd(x);
    }
    void rot(int x){
        int y=f[x],k=tp(x),w=t[x][!k];
        // cerr<<x<<" "<<y<<" "<<w<<endl;
        // cerr<<f[x]<<" "<<f[y]<<endl;
        t[f[w]=t[x][!k]=y][k]=w;
        if(in(y))t[f[y]][tp(y)]=x;
        f[x]=f[y],f[y]=x,pp(y);
        assert(x!=f[x]&&y!=f[y]);
    }
    void splay(int x){
        ppd(x);for(int z=f[x];in(x);rot(x),z=f[x])
            if(in(z))rot(tp(x)^tp(z)?x:z);pp(x);
    }
    int acs(int x){
        int y,z;
        for(y=0;x;x=f[y=x])
            splay(x),rs=y,pp(x);
        return y;
    }
    int getl(int x){
        while(1){assert(x);
            pd(x);
            if(sm[ls])x=ls;
            else if(cl[x])break;
            else x=rs;
        }splay(x);
        return x;
    }
    int getr(int x){
        while(1){assert(x);
            pd(x);
            if(sm[rs])x=rs;
            else if(cl[x])break;
            else x=ls;
        }splay(x);return x;
    }
    void dfs(int x){
        // printf("dfs:%d\n",x);
        nw[::v[x]]=1;
        if(ls)dfs(ls);
        if(rs)dfs(rs);
    }
    int solve(int x,int y){
        acs(x),splay(x),rev(x);
        // cerr<<"lrs:"<<ls<<" "<<rs<<endl;
        acs(y),splay(x);
        nw.reset();
        if(sm[x]){
            int l=getl(x);
            if(t[l][0])dfs(t[l][0]);
            int r=getr(l);
            // printf("l:%d r:%d\n",l,r);
            if(t[r][1])dfs(t[r][1]);
            nw|=tb[cl[l]][cl[r]];
        }else dfs(x);
        return nw.count();
    }
}
void dfs(int x,int rp){
    dfn[x]=++dlt;
    for(int y:lk[x])
        if(y!=rp)
            dfs(y,x),lct::f[y]=x/*,cerr<<"set:"<<x<<" "<<y<<endl*/;
}
void dfs2(int x,int rp){
    ++ct[v[x]],nw[v[x]]=1;
    if(cl[x])tb[rt][cl[x]]=nw;
    for(int y:lk[x])
        if(y!=rp)dfs2(y,x);
    if(!--ct[v[x]])nw[v[x]]=0;
}
int main(){
    ios::sync_with_stdio(false);
    mt19937_64 rg(random_device{}());
    cin>>n>>q;
    int i,x,y;
    for(x=1;x<=n;++x)cin>>v[x],mp[x]=v[x];
    for(i=1;i<n;++i){
        cin>>x>>y;
        lk[x].push_back(y);
        lk[y].push_back(x);
    }sort(mp+1,mp+n+1),dfs(1,0);
    m=unique(mp+1,mp+n+1)-mp;
    for(x=1;x<=n;++x)
        v[x]=lower_bound(mp+1,mp+m,v[x])-mp,p[x]=x;
    shuffle(p+1,p+n+1,rg),m=1+sqrt(1+n);
    if(m>n)m=n;
    for(i=1;i<=m;++i)cl[p[i]]=i;
    for(rt=1;rt<=m;++rt)dfs2(p[rt],0);
    // for(x=1;x<=m;++x)printf("%d%c",p[x]," \n"[x==m]);
    // m=0;
    while(q--){
        cin>>x>>y,x^=ans;
        ans=lct::solve(x,y);
        printf("%d\n",ans);
    }return 0;
}
```

---

## 作者：Jr_Zlw (赞：2)

## 点分治 + bitset + 乱搞

模板题当然是要乱搞的啦，这边提供一种使用点分治，bitset  的乱搞方法。

考虑需要在线查询，所以建出点分树。

设当前查询点为  $(u,v)$  ，其在点分树上的  LCA  为  $rt$  ，即在一次点分治中以  $rt$  为分治重心找到处在不同子树内的  $u,v$。此时只需要将  $(u,rt),(v,rt)$  的答案合并一下就可以了。这个答案可以用  bitset  预处理。

这样做时间复杂度是  $O(\frac{(m+n\log n)n}{w})$，问题不大。

然而空间是  $O(\frac{n^2\log n}{w})$  的，很遗憾无法通过。

这个时候借用一下正解撒点的套路，如果我们只记录某些点的答案，中间暴力往  bitset  中加入答案就好了。

这边我直接按深度每隔  $8$  个点打一次答案，这样查询的时候也就只需要向上跳  $8$  次答案就能找到了。

时空复杂度是玄学的，因为很有可能某个深度的点非常多，也许再随机一点会更好。不过即使不开  O2  这样也能过。

```
#include<bits/stdc++.h>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
#define drep(a,b,c) for(int c(a);c>=(b);--c)
#define grep(b,c) for(int c(head[b]);c;c=nxt[c])
using namespace std;
inline int read()
{
	int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
}
inline void print(int x){if(x>9)print(x/10);putchar(x%10+'0');}
const int N=4e4+10,INF=0x3f3f3f3f;int head[N],des[N<<1],nxt[N<<1],cgt;
inline void ins(int x,int y)
{
	nxt[++cgt]=head[x];des[head[x]=cgt]=y;
	nxt[++cgt]=head[y];des[head[y]=cgt]=x;
}
typedef unsigned long long uLL;
struct Bitset
{
	uLL a[625];inline void operator |= (const Bitset &b){for(int i=0;i<625;++i)a[i]|=b.a[i];}
	inline int count(){int ans=0;for(int i=0;i<625;++i)ans+=__builtin_popcountll(a[i]);return ans;}
	inline void ins(int x){a[x>>6]|=1ull<<(x&63);}
	inline void del(int x){a[x>>6]^=1ull<<(x&63);}
	inline bool operator [] (int x){return a[x>>6]>>(x&63)&1;}
	inline void clear(){memset(a,0,sizeof(a));}
};
unordered_map<int,int> Fa[N];
unordered_map<int,Bitset> s[N];int n,c[N],P[N],p;
inline int bnd(int x){int l(1),r(p),m;while(l<=r)P[m=(l+r)>>1]<=x?l=m+1:r=m-1;return l-1;}
int Mn,Rt,Sz,siz[N],fa[N],dep[N];
inline void getRt(int u,int fa=0)
{
	siz[u]=1;int mx=0;
	grep(u,i)if(!dep[des[i]]&&des[i]!=fa)
	{
		int v=des[i];getRt(v,u);
		siz[u]+=siz[v];mx=max(mx,siz[v]);
	}
	mx=max(mx,Sz-siz[u]); mx<Mn?Mn=mx,Rt=u:0;
}
inline void getSz(int u,int fa=0){siz[u]=1;grep(u,i)if(!dep[des[i]]&&des[i]!=fa)getSz(des[i],u),siz[u]+=siz[des[i]];}
Bitset A;int RT;
inline void dfs(int u,int fa=0,int dd=1)
{
	grep(u,i)if(des[i]!=fa&&!dep[des[i]])
	{
		bool flag=0;int v=des[i];
		if(!A[c[v]])flag=true,A.ins(c[v]);
		if(dd%8==0)
		{
			s[RT][v]=A;
			Fa[RT][v]=u|(1<<30);
		}
		else Fa[Rt][v]=u;
		dfs(v,u,dd+1);
		if(flag)A.del(c[v]);
	}
}
inline void Cnt(int u){s[u][u].ins(c[u]);A=s[u][u];Fa[u][u]=1<<30;RT=u;dfs(u);}
inline void Solve(int u)
{
	Cnt(u);grep(u,i)if(!dep[des[i]])
	{
		int v=des[i];getSz(v);Mn=INF;Sz=siz[v];getRt(v);
		fa[Rt]=u;dep[Rt]=dep[u]+1;Solve(Rt);
	}
}
inline int LCA(int u,int v){while(u!=v){dep[u]<dep[v]?v=fa[v]:u=fa[u];}return u;}
Bitset ans;
inline int qry(int u,int v)
{
	int lc=LCA(u,v);ans.clear();
	while(true){int tmp=Fa[lc][u];if(tmp>>30&1){ans|=s[lc][u];break;}ans.ins(c[u]);u=tmp;}
	while(true){int tmp=Fa[lc][v];if(tmp>>30&1){ans|=s[lc][v];break;}ans.ins(c[v]);v=tmp;}
	return ans.count();
}
int main()
{
	n=read();int Q=read();rep(1,n,i)P[i]=c[i]=read();
	sort(P+1,P+n+1);p=unique(P+1,P+n+1)-P-1;rep(1,n,i)c[i]=bnd(c[i])-1;
	rep(2,n,i)ins(read(),read());Sz=n;Mn=INF;getRt(1);dep[Rt]=1;Solve(Rt);
	int lst=0;while(Q--){int u=lst^read(),v=read();print(lst=qry(u,v));putchar('\n');}
	return 0;
}
```

---

## 作者：eggegg185 (赞：2)

~~首先感谢一个叫 zzctommy 的夶奆佬让我明白树分块~~

~~蒟蒻第一篇题解，求过 qwq~~

我们知道树分块是一种在树上分块的算法（废话），我们使用一种叫“树上撒点”的方法来完成这道题（其实我只会这种）。

首先，在树上撒一些点。我们把这些点叫做关键点。我们需要维护关键点之间的信息，查询一条链时零散点直接暴力求，中间关键点连成的链的信息我们只需要调用之前我们维护好的值就可以了（是不是有分块内味了 $XD$ ）。

为了让我们能够顺利地搞暴力，我们要保证每个点离最近的关键点的距离不超过一个值，也就是每个关键点之间的距离必须不超过一个值（我们把它称作 $S$ )。显然，鉴于我们的查询操作，关键点是越多越好。所以，如果对于一个点，如果他的 $1$ 到 $S$ 级祖先都不是关键点，这个时候就把他设为关键点。但是，如果真这样用的话时间复杂度显然是 $O(nS)$ ，有很大的优化空间。这个时候，我们可以逆向思维一下，如果一个节点的底下没有关键点儿子的最长路径的长度大于等于 $S$ ，那这个点早晚会成为关键点。这个时候我们就可以利用这个性质来把复杂度降为 $O(n)$ 。

好的，我们可以看这个题了，题意：

- 给你一个 $n$ 个节点的树
- 询问两点之间的路径上有多少不同数字

给出每个点的数字，求两点路径上有多少个不同数字（为了表达方便，提前将每个点的数字定义为每个点的颜色）。

首先我们肯定要撒点啊（废话），按照上面的方法把一些关键点“撒”在树上。然后，我们说了要维护关键点之间的信息，也就是关键点之间出现了什么颜色，这里我们离散化之后用 `bitset` 维护。对于相邻的关键点我们没有什么好办法来处理这个 `bitset` ,直接暴力求。但是如果不相邻的关键点我们可以利用或运算来递推求出来，也就是 $bitset_{i,j} = bitset_{i,j-1} | bitset_{j-1,j}$ 。

设 $lca = LCA(x,y)$ ，那么对于两个点的路径，可以先分为 $x-lca$ ， $y-lca$ 。这样，路径就转化为了两条链，我们按照上面的方法弄，也就是先找在 $x$ 父亲方向的最近关键点，把他称作 $x_1$ ，再求在 $lca$ 在 $x$ 方向的最近关键点，称做 $x_2$ 。这样，我们就可以把这条链分成 $x-x_1$ ， $x_1-x_2$ ， $x_2-lca$ 。对于 $x-x_1$ 和 $x_2-lca$ ，我们直接暴力求答案，毕竟复杂度不超过 $O(s)$ 。对于 $x_1-x_2$ 这样的关键点之间的路径，我们之前预处理了它的 `bitset` ，直接拿出来求就是了。这样，把这些求出来的值求并集，就可以得到我们的答案了！下面是代码（本人喜欢用 codeblocks ，所以用的是蹩脚的英文注释，请见谅 qwq ）：

$Code:$

```cpp
#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;
int head[100001],col[100001],deep[100001],maxdeep[100001],largeson[100001],to[100001],nxt[100001],cnt = 0,siz[100001];
bitset<40100> colors[100][100];
bool isbig[100001];
int bigs[100001],bigcnt = 0;
int father[100001];
int bigpa[100001];
//int nearestBigChild[100001];
int top[100001]; //heavy line top
int id[100001]; // big point's id
int lshcol[100001],lshcnt; //color after LI SAN HUA ed.
int n,m;

const int S = 1000;

void add(int a,int b) {
    cnt++;
    to[cnt] = b;
    nxt[cnt] = head[a];
    head[a] = cnt;
}
void dfsBig(int now,int pa) { //Find Big
    deep[now] = deep[pa]+1;
    siz[now] = 1;
    father[now] = pa;
    maxdeep[now] = deep[now];
    for(int i = head[now]; i; i = nxt[i]) {
        if(to[i] != pa) {
            dfsBig(to[i],now);
            siz[now] += siz[to[i]];
            maxdeep[now] = max(maxdeep[now],maxdeep[to[i]]);
            if(!largeson[now] || siz[largeson[now]] < siz[to[i]]) {
                largeson[now] = to[i]; //LCA!
            }
        }
        if(now == 1 || maxdeep[now]-deep[now] > S) {
            isbig[now] = true;
            id[now] = ++bigcnt;
            maxdeep[now] = deep[now]; //Big Points Has Parents!
        }
        // if down S don't have big, it becomes a big.
        // we know that the root is big.
    }
}

void dfsPouFen(int now,int tt) { // thats why we get large sons. for LCA.
    top[now] = tt;
    if(largeson[now]) dfsPouFen(largeson[now],tt);
    for(int i = head[now]; i; i = nxt[i]) {
        if(to[i] != father[now] && to[i] != largeson[now]) {
            dfsPouFen(to[i],to[i]);
        }
    }
}

void dfsBitSet(int now,int pa,int lastbig) {
    if(isbig[now]) {
        bigpa[now] = lastbig;
        colors[id[now]][id[now]].set(lshcol[now]);
        for(int k = now; k != father[lastbig]; k = father[k]) {
            colors[id[now]][id[lastbig]].set(lshcol[k]);
        }
        for(int k = bigpa[lastbig]; k; k = bigpa[k]) {
            colors[id[now]][id[k]] = colors[id[now]][id[lastbig]];
            colors[id[now]][id[k]] |= colors[id[lastbig]][id[k]];
        }
    }
    // for now to last big, we BAO LI
    // we use bit set and or to calculate the bit set.
    for(int i = head[now]; i; i = nxt[i]) {
        if(to[i] == pa) continue;
        dfsBitSet(to[i],now,isbig[now]?now:lastbig);
    }
}

int lca(int u,int v) {
    while(top[u] != top[v]) {
        if(deep[top[u]] < deep[top[v]]) swap(u,v);
        u = top[u];
        u = father[u];
    }
    return (deep[u]>deep[v])?v:u;
}

int query(int u,int v) {
    bitset<40100> opop;
    int homo = lca(u,v);
    opop.set(lshcol[homo]);
    for(; !isbig[u] && u != homo; u = father[u]) {
        opop.set(lshcol[u]);
        //cout << u << endl;
    }
    for(; !isbig[v] && v != homo; v = father[v]) {
        opop.set(lshcol[v]);
    }
    if(u != homo) {
        int u2;
        for(u2 = u; bigpa[u2] && deep[bigpa[u2]] > deep[homo]; u2 = bigpa[u2]);
        opop |= colors[id[u]][id[u2]];
        for(int i = u2; i != homo; i = father[i]) {
            opop.set(lshcol[i]);
        }
    }
    if(v != homo) {
        int v2;
        for(v2 = v; bigpa[v2] && deep[bigpa[v2]] > deep[homo]; v2 = bigpa[v2]);
        opop |= colors[id[v]][id[v2]];
        for(int i = v2; i != homo; i = father[i]) {
            opop.set(lshcol[i]);
        }
    }
    return opop.count();
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> col[i];
        lshcol[i] = col[i];
    }
    for(int i = 1; i < n; i++) {
        int o,p;
        cin >> o >> p;
        add(o,p);
        add(p,o);
    }
    sort(col+1,col+1+n);
    lshcnt = unique(col+1,col+1+n)-col-1;
    for(int i = 1; i <= n; i++) {
        lshcol[i] = lower_bound(col+1,col+1+lshcnt,lshcol[i])-col;
    }
    dfsBig(1,0);
    dfsPouFen(1,1);
    dfsBitSet(1,0,0);
    int lastans = 0;
    while(m--) {
        int u1,v;
        cin >> u1 >> v;
        int u = u1^lastans;
        lastans = query(u,v);
        cout << lastans << endl;
    }
    return 0;
}
```

最后感谢大家观看！ XD

---

