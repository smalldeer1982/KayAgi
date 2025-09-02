# Santa's Gift

## 题目描述

圣诞老人拥有每种口味 $m$ 的无限糖果。给定一棵包含 $n$ 个顶点的有根树，根节点为顶点 $1$。每个顶点恰好包含一颗糖果，第 $i$ 个顶点的糖果口味为 $f_i$。  

有时圣诞老人担心口味 $k$ 的糖果可能融化。他会随机选择一个顶点 $x$，并将 $x$ 的子树交给面包师进行替换。在替换过程中，所有口味 $k$ 的糖果会被替换为同口味的新糖果，其他口味的糖果保持不变。替换完成后，树会恢复原状。  

替换一颗口味 $k$ 糖果的实际成本为 $c_k$（每个 $k$ 给定）。面包师为简化计算保持固定收费价格 $C$。每次子树进行替换时，无论子树大小或口味如何，面包师都收取 $C$ 的费用。  

假设对于给定口味 $k$，圣诞老人选择替换顶点的概率在所有顶点中均匀分布。你需要计算口味 $k$ 替换成本计算误差的期望值。误差定义如下：  

$$ E(k) = (\text{实际成本} - \text{面包师收取价格})^2 $$  

注意实际成本等于单颗口味 $k$ 糖果替换成本乘以子树中该口味糖果数量。  

此外，圣诞老人可能希望用口袋中的糖果替换顶点 $x$ 处的糖果。你需要处理两种操作：  
- 将顶点 $x$ 的糖果口味改为 $w$  
- 计算给定口味 $k$ 替换成本误差的期望值  

## 说明/提示

对于第一个询问，当选择顶点 $1$、$2$ 或 $3$ 时，口味 $1$ 的替换误差分别为 $66^2$、$66^2$ 和 $(-7)^2$。由于选择概率均等，期望值为 $\frac{66^2 + 66^2 + (-7)^2}{3}$。  

类似地，第二个询问的期望值为 $\frac{41^2 + (-7)^2 + (-7)^2}{3}$。  

第三个询问后，顶点 $2$ 的口味从 $1$ 变为 $3$。  

第四个询问的期望值为 $\frac{(-7)^2 + (-7)^2 + (-7)^2}{3}$。  

第五个询问的期望值为 $\frac{89^2 + 41^2 + (-7)^2}{3}$。  

翻译由 DeepSeek R1 完成  

## 样例 #1

### 输入

```
3 5 5 7
3 1 4
1 1
73 1 48 85 89
2 1
2 3
1 2 3
2 1
2 3
```

### 输出

```
2920.333333333333
593.000000000000
49.000000000000
3217.000000000000
```

# 题解

## 作者：Alex_Wei (赞：6)

> *[CF960H Santa's Gift](https://www.luogu.com.cn/problem/CF960H) *3100*

将贡献式展开，得到 $\dfrac{b_x ^ 2\sum S_i ^ 2 + 2b_xC \sum S_i} n + C ^ 2$。因此只需对每个颜色维护每个点的子树内含有该颜色的节点个数的和与平方和。因为只有单点修改颜色，对应修改一条链上所有点关于某个颜色的 $S_i$，所以容易树剖 + 动态开点线段树维护，注意 `push_down` 时新开节点。时空复杂度线性对数平方。

想必来写这道题目的同学应该会区间加区间平方和罢。$\sum (x_i + v) ^ 2 = \sum x_i ^ 2 + v\sum x_i + Lv ^ 2$，其中 $L$ 是区间长度。

代码很简单。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5, K = N * 360;
long long sq[K], val[K], C;
int n, m, q, node, fa[N], a[N], b[N];
int R[N], ls[K], rs[K], laz[K];
void tag(int l, int r, int &x, long long v) {
	if(!x) x = ++node;
	sq[x] += 2 * val[x] * v + (r - l + 1) * v * v;
	val[x] += (r - l + 1) * v;
	laz[x] += v;
}
void down(int l, int r, int x) {
	if(laz[x]) {
		int m = l + r >> 1;
		tag(l, m, ls[x], laz[x]);
		tag(m + 1, r, rs[x], laz[x]);
		laz[x] = 0;
	}
}
void modify(int l, int r, int ql, int qr, int &x, int v) {
	if(!x) x = ++node;
	if(ql <= l && r <= qr) return tag(l, r, x, v), void();
	int m = l + r >> 1;
	down(l, r, x);
	if(ql <= m) modify(l, m, ql, qr, ls[x], v);
	if(m < qr) modify(m + 1, r, ql, qr, rs[x], v);
	val[x] = val[ls[x]] + val[rs[x]];
	sq[x] = sq[ls[x]] + sq[rs[x]];
}
vector <int> e[N];
int dn, dfn[N], sz[N], dep[N], son[N], top[N];
void dfs1(int id) {
	sz[id] = 1, dep[id] = dep[fa[id]] + 1;
	for(int it : e[id]) {
		dfs1(it), sz[id] += sz[it];
		if(sz[it] > sz[son[id]]) son[id] = it;
	}
}
void dfs2(int id, int t) {
	top[id] = t, dfn[id] = ++dn;
	if(son[id]) dfs2(son[id], t);
	for(int it : e[id]) if(it != son[id]) dfs2(it, it);
}
void add(int x, int c, int v) {while(x) modify(1, n, dfn[top[x]], dfn[x], R[c], v), x = fa[top[x]];}
int main() {
	cin >> n >> m >> q >> C;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 2; i <= n; i++) cin >> fa[i], e[fa[i]].push_back(i);
	for(int i = 1; i <= m; i++) cin >> b[i];
	dfs1(1), dfs2(1, 1);
	for(int i = 1; i <= n; i++) add(i, a[i], 1);
	for(int i = 1; i <= q; i++) {
		int op, x, y;
		cin >> op >> x;
		if(op == 1) cin >> y, add(x, a[x], -1), add(x, a[x] = y, 1);
		else printf("%.10lf\n", (double)(b[x] * b[x] * sq[R[x]] - 2 * b[x] * C * val[R[x]]) / n + C * C);
	}
	return 0;
}
```

---

## 作者：sgl654321 (赞：3)

### 闲话
生日浅破一手 150 紫，权且当做生日礼物吧。

又是一道带颜色限制的树剖题。
### 题目大意
- 有 $m$ 种颜色，每个颜色 $j$ 有一个权值 $b_j$。并给定一个常数 $C$。
- 给定一棵 $n$ 个节点的树，节点 $i$ 上面的颜色是 $f_i$。
- 有 $q$ 次操作，每次操作是如下的两种之一：
	1. `1 x y` 表示把节点 $x$ 的颜色变成 $y$。
   2. `2 y` 表示让你输出：
   	$$\dfrac{\sum_{i=1}^{n} (S_{i,y}\times b_y-C)^2}{n}$$
   其中 $S_{i,y}$ 表示的是节点 $i$ 的子树中，节点颜色为 $y$  的个数。
   
## 解题思路
### 化简所求代数式
$$\begin{aligned} &\dfrac{\sum_{i=1}^n (S_{i,y}\times b_y-C)^2}{n}\\
&= \dfrac{\sum_{i=1}^n(S_{i,y}^2\times b_y^2-2\times S_{i,y}\times b_y\times C+C^2)}{n}\\
&=\dfrac{b_y^2\times \sum_{i=1}^{n}S_{i,y}^2 -2Cb_y\times \sum_{i=1}^n{S_{i,y}}}{n}+C^2\\
\end{aligned} $$

我们发现，这个式子其实只有两项是非常数项：一是 $\sum_{i=1}^nS_{i,y}^2$，二是 $\sum_{i=1}^nS_{i,y}$。即对于每一个颜色 $y$，求出所有子树中 $y$ 颜色的个数，维护他们的**线性和**与**平方和**。

### 考虑使用算法与数据结构
我们除了询问操作还有一个修改操作，是把一个节点 $x$ 的颜色改为 $y$。我们设这个节点本来的颜色是 $y'$。

肯定只有 $y',y$ 两种颜色收到了影响，那么有哪些节点收到了影响呢？显然是 $x$ 即其所有直系祖先。

具体地，
1. 把所有 $S_{i,y'}$ 减去 $1$，其中 $i$ 是 $x$ 及其直系祖先。
2. 把所有 $S_{i,y}$ 减去 $1$，其中 $i$ 是 $x$ 及其直系祖先。

那么这就是一个显然的树链上的修改了。来做这题的人应该都知道这个要用**树链剖分**吧。

考虑树链剖分转化成序列问题，那么操作就变成了区间修改，区间平方和，区间和三种。区间上的问题，我们再使用线段树。如果有不会维护平方和的（额，应该没有吧）可以看看这个题：[P5142 区间方差](https://www.luogu.com.cn/problem/P5142)。随便讲一下，如果我们把一个区间全部加上了 $k$，那么由于 $\sum (x_i+k)^2=\sum x_i^2+\color{red}{2k\sum  x_i+nk^2}$，所以我们只需要加上红色部分即可。

### 考虑弱化问题
如果颜色个数 $m$ 很小，那么显然我们可以直接开 $m$ 棵线段树，对 $m$ 中颜色分别进行维护即可。空间复杂度卡满，直接变成 $O(mn\log n)$。

现在的颜色种类很多，我们应当怎么办呢？

### 考虑原问题
虽然颜色种类 $m$ 很大，但是我们发现这 $m$ 种颜色总共的点数是恒定的，即 $n$。如果我们直接开 $m$ 棵线段树，线段树中很大一部分空间都会被浪费掉。

因此我们需要使用一种更加高级的线段树：**动态开点线段树**。

即，我们并不固定地开每一种颜色的线段树，只有我们修改到了这个位置，我们才新建一个节点。

例如，我们要修改 $[3,5](n=5)$ 这个区间，当前这个线段树为空。那么我们只需要新建 $[1,5],[1,3],[3,3],[4,5]$ 这四个节点就行了。

由于有 $m$ 棵线段树，所以我们要知道每一棵线段树的根节点编号，同时还要记录下每一个节点的左右儿子是谁。

### 完整思路
1. 输入树的形态和原来每个节点的颜色。通过树链剖分，用动态开点线段树把 $S_{j,a_i}$（$j$ 是 $i$ 的直系祖先和 $j$ 本身）链上加 $1$。
2. 对于操作 $1$，设 $x$ 的原来颜色为 $y'$，把 $S_{j,y'}$ 链上减去 $1$，$S_{j,y}$ 链上加 $1$。
3. 对于操作 $2$，线性和与平方和就是 $t_{root_x}$ 的。然后直接套那个挺长的期望公式即可。

### 细节部分
1. 不少题解都没有提到动态开点线段树的空间上限要开到多少。这里简单讨论一下。

对于原来的颜色，我们会把根节点到所有的节点的所有的链进行链上修改。根据树剖的基本结论，这个东西会被剖成 $O(\log n)$ 根连续的重链。根据线段树的基本结论，对于一个区间进行修改，会涉及到 $O(\log n)$ 个节点。因此原来的颜色修改就会修改掉 $O(n\log^2 n)$ 个节点。

对于操作 $1$ 的修改，我们会进行两次链上修改，一次链上减 $1$，一次链上加 $1$。链上减 $1$ 的情况我们肯定已经新开过了，不用新开。因此我们会修改掉 $O(\log^2n)$ 个节点。

考虑最坏情况，最多会新建 $O((n+q)\log^2n)$ 个节点。开到这个级别就可以了。然而树剖根本卡不满，所以开 $200n$ 就差不多了。

2. 在 `pushdown` 函数中，如果没有儿子节点我们也要进行新建节点。
3. 递归函数我们一定要记得开局部变量，记录当前节点是什么。不然等你递归建完左子树和右子树，你的当前节点就已经面目全非了。
4. 仔细仔细再仔细，不要打错式子了。

### 参考代码
我们树剖题目是这样的，代码非常长。并且众所周知，我图论写的比较抽象，因此有用者链接[自取](https://www.luogu.com.cn/paste/9bkh78du)。


---

## 作者：Leap_Frog (赞：3)

### P.S.
锻炼码力的好题  
看基本没代码可读的题解就来篇  

### Description.
略

### Solution.
首先询问一个颜色这种题可以对每个颜色分别维护。  
反正笔者第一想法就是对每个颜色建立虚树。  
但是发现虚树上无法删除，比较复杂，而且虚树维护信息也比较困难。  
转念一想，发现其实虚树上根本不需要删除，因为总复杂度是 $O(n+q)$ 的。  

拆一下式子，变成了下式。  
$$
\begin{aligned}
&=\frac1n\sum_{i=1}^n(S_ib_x-C)^2\\
&=\frac1n\sum_{i=1}^nS_i^2b_x^2+C^2-2CS_ib_x\\
&=\frac{b_x^2}n\sum_{i=1}^nS_i^2-\frac{2Cb_x}{n}\sum_{i=1}^nS_i+C^2\\
\end{aligned}
$$

所以我们需要求出 $S_i^2$ 和和 $S_i$ 和。  
可以直接维护 $S_i$。  
每次修改颜色相当于对一个点到根的路径 $+1$ 或 $-1$。  
然后相当于一个区间加。  

但是这样空间肯定爆炸，考虑动态开点。  
虽然是区间加，就相当于只有一个 tag 的区间定义为结束节点。  
然后时空复杂度都是 $O(n\log ^2n)$，$5\times 10^4$ 随便过。  

### Coding.
```cpp
//Coded by Kamiyama_Shiki on 2021.11.10 {{{
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=50005;int n,m,Q,cl[N];ll b[N],C;
struct node
{
	ll _0,_1,_2;
	node(ll w=-1,ll a=-1,ll b=-1)
	{
		if(~a) _0=w,_1=a,_2=b;
		else if(~w) _0=1,_1=w,_2=w*w;
		else _0=_1=_2=0;
	}
	inline node operator+(node a) {return node(_0+a._0,_1+a._1,_2+a._2);}
	inline node operator+(ll b) {return node(_0,_1+b*_0,_2+2*b*_1+_0*b*b);}
};
struct segm{int ls,rs;ll tg;char ed;node vl;}T[N*205];int tt,rt[N];
inline void pushup(int x) {T[x].vl=T[T[x].ls].vl+T[T[x].rs].vl;}
inline void newnd(int &x,node c) {T[x=++tt]=(segm){0,0,0,1,c};}
inline void allc(int x,ll w) {T[x].vl=T[x].vl+w,T[x].tg+=w;}
inline void pushdw(int x)
{
	if(T[x].ed)
	{
		ll lnr=T[x].vl._0>>1,lnl=T[x].vl._0-lnr;T[x].ed=0;
		newnd(T[x].ls,node(lnl,0,0)),newnd(T[x].rs,node(lnr,0,0));
	}
	if(T[x].tg) allc(T[x].ls,T[x].tg),allc(T[x].rs,T[x].tg),T[x].tg=0;
}
inline void modif(int x,int l,int r,int dl,int dr,int dc)
{
	if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return allc(x,dc);else pushdw(x);
	modif(T[x].ls,l,(l+r)>>1,dl,dr,dc),modif(T[x].rs,((l+r)>>1)+1,r,dl,dr,dc),pushup(x);
}
struct edge{int to,nxt;}e[N];int et,head[N];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
int dep[N],f[N],sz[N],sn[N],dfn[N],nfd[N],dt,tp[N];
inline void dfs0(int x,int fa)
{
	dep[x]=dep[f[x]=fa]+1,sz[x]=1,sn[x]=0;
	for(int i=head[x];i;i=e[i].nxt)
	{
		dfs0(e[i].to,x),sz[x]+=sz[e[i].to];
		if(sz[e[i].to]>sz[sn[x]]) sn[x]=e[i].to;
	}
}
inline void dfs1(int x,int top)
{
	dfn[x]=++dt,nfd[dt]=x,tp[x]=top;if(sn[x]) dfs1(sn[x],top);else return;
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=sn[x]) dfs1(e[i].to,e[i].to);
}
inline void chang(int id,int x,int dc)
{
	for(;tp[x]!=1;x=f[tp[x]]) modif(rt[id],1,n,dfn[tp[x]],dfn[x],dc);
	modif(rt[id],1,n,1,dfn[x],dc);
}
inline void debug(int x,int l,int r)
{
	printf("[ %d %d ] : %lld %lld %lld\n",l,r,T[x].vl._0,T[x].vl._1,T[x].vl._2);
	if(l==r) return;else pushdw(x),debug(T[x].ls,l,(l+r)>>1),debug(T[x].rs,((l+r)>>1)+1,r);
}
int main()
{
	read(n,m,Q,C);for(int i=1;i<=n;i++) read(cl[i]);
	for(int i=2,f;i<=n;i++) read(f),adde(f,i);
	for(int i=1;i<=m;i++) read(b[i]),newnd(rt[i],(node){n,0,0});
	dfs0(1,0),dfs1(1,1);for(int i=1;i<=n;i++) chang(cl[i],i,1);
	for(int fg,x,y;Q--;)
	{
		read(fg,x);if(fg&1) {read(y),chang(cl[x],x,-1),chang(cl[x]=y,x,1);continue;}
		node w=T[rt[x]].vl;printf("%.8lf\n",1.0*w._2*b[x]*b[x]/n-2.0*C*b[x]/n*w._1+C*C);
	}return 0;
}
```

---

## 作者：Coffee_zzz (赞：2)

形式化题面（为了避免 $c$ 和 $C$ 混淆，原题面中的 $c$ 在此处用 $b$ 表示）：

给定一个常数 $C$ 和一棵包含 $n$ 个结点的有根树，根为 $1$ 号结点，结点 $2\sim n$ 的父亲为结点 $p_2\sim p_n$。有 $m$ 种颜色，结点 $u$ 的颜色为 $f_u$，颜色 $i$ 的权值为 $b_i$。

现有 $q$ 次操作：

  - $1\ x\ w$：将 $f_x$ 的值修改为 $w$。

  - $2\ k$：从树中等概率选取一个点 $u$，求 $(S_{u,k}\times b_k-C)^2$ 的期望，其中 $S_{u,k}$ 表示以 $u$ 为根的子树中颜色为 $k$ 的节点数。

如果答案的绝对误差或相对误差不超过 $10^{−6}$ ，则认为答案正确。

---

首先推一下我们要求的式子：
$$
\begin{aligned}
&\dfrac 1 n\sum_{u=1}^n\;(S_{u,k} \times b_k-C)^2\\
=\ &\dfrac 1 n \sum_{u=1}^n \left({S_{u,k}}^2\times {b_k}^2-2 \times S_{u,k} \times b_k \times C+C^2\right)\\
=\ &\dfrac {{b_k}^2} n \sum_{u=1}^n {S_{u,k}}^2-\dfrac {2\times b_k\times C} n \sum_{u=1}^n S_{u,k}+C^2
\end{aligned}
$$

容易发现，其实我们只需要维护 $\sum\limits_{u=1}^n {S_{u,k}}^2$ 和 $\sum\limits_{u=1}^n S_{u,k}$ 即可。

由于每次对点 $u$ 进行修改操作时，只会影响点 $u$ 的祖先的两种颜色的答案，所以可以直接在树剖后用动态开点线段树暴力修改。

其中 $\sum\limits_{u=1}^n {S_{u,k}}^2$ 可以利用 $(S_{u,k}+v)^2={S_{u,k}}^2+2\times v\times S_{u,k}+v^2$ 快速维护。

时间复杂度 $\mathcal O(n \log^2 n)$。

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

模拟赛最后 45min 码出了 180 行的 *3100 数据结构题，纪念

先假设下面的 $/n$ 不存在，考虑简化 $\sum(S_ib_x-C)^2$。

$$\sum_{i=1}^n(S_ib_x-C)^2$$
$$\sum_{i=1}^nS_i^2b_x^2-2S_ib_xC+C^2$$
$$nC^2-2b_xC\sum_{i=1}^nS_i+b_x^2\sum_{i=1}^nS_i^2$$

于是我们只需要对每一个元素颜色的 $\sum S_i$ 和 $\sum S_i^2$。

变某一个节点的颜色可以看做为把这个到根路径上对对应颜色所有 $S_i$ 加 1 或者减 1。$\sum S_i^2$ 可以维护变的时候的差。现在问题退化成对所有颜色维护一个支持到根路径节点值之和，到根路径节点值全部加减1的一个结构。

~~不知道出题人怎么想到淀粉质~~

这个直接看起来是树剖，但是对每一个颜色开一个完全的树剖结构显然不行（内存炸），所以用动态开点线段树。

这里只需要注意 $\sum S_i^2$ 是怎么变了。当时在一个节点 $u$ 所有 $S_i$ 加 1，差是

$$\sum_{i\in Link}2S_i+1=|Link|+2\sum_{i\in Link}^nS_i$$

$|Link|$ 就是节点 $u$ 的深度，dfs 出来。减 1 的时候并不是一整个取负，而是

$$\sum_{i\in Link}-2S_i+1=|Link|-2\sum_{i\in Link}^nS_i$$

这样更新就可以了。

赛时代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;
/*
static char buf[450 << 20];
size_t idx = sizeof buf;
void* operator new(size_t s) {
	assert(s < idx);
	return (void*)&buf[idx -= s];
}
void operator delete(void*) {}

template<class T> struct ptr {
	unsigned ind;
	ptr(T* p = 0) : ind(p ? unsigned((char*)p - buf) : 0) {
		assert(ind < sizeof buf);
	}
	T& operator*() const { return *(T*)(buf + ind); }
	T* operator->() const { return &**this; }
	T& operator[](int a) const { return (&**this)[a]; }
	explicit operator bool() const { return ind; }
};
*/
namespace sst {
    class SST {
    public:
    	ll sum;
    	SST* ch[2];
    	SST() : sum(0) {
    		ch[0] = nullptr;
    		ch[1] = nullptr;
    	}
    	void inc(int val, int diff, int dep=16) {
    		sum += diff;
    		if (!dep) return;
    		bool cv = val & (1 << (dep - 1));
    		if (!ch[cv]) ch[cv] = new SST;
    		ch[cv]->inc(val, diff, dep-1);
    	}
    };
    
    inline ll psum(SST* root, int val) {
    	int dep = 16; ll ans = 0;
    	while(dep && root) {
    		bool cv = val & (1 << (--dep));
    		if (cv && root->ch[0]) ans += root->ch[0]->sum;
    		root = root->ch[cv];
    	}
    	return ans + (root ? root->sum : 0);
    }
}

class IaIs {
public:
    sst::SST* di, *idi;
    IaIs() { using namespace sst; di = new SST(); idi = new SST(); }
    void ia(int r, int dt) { di->inc(r, dt); idi->inc(r, r*dt); }
    void ia(int l, int r, int dt) { ia(r+1, -dt); ia(l, dt); }
    ll is(int r) { using namespace sst; return (r+1) * psum(di, r) - psum(idi, r); }
    ll is(int l, int r) { return is(r) - is(l-1); }
};

IaIs colors[50004];
vector<int> elist[50004];

int size[50004], heavy[50004];
int hp[50004], par[50004], dep[50004];

void dfsSize(int u=1, int f=-1) {
    if(f == -1) dep[u] = 1;
    else dep[u] = dep[f] + 1;
    size[u] = 1, heavy[u] = -1; par[u] = f;
    for(int& v:elist[u]) if(v != f) {
        dfsSize(v, u);
        size[u] += size[v];
        if(heavy[u] == -1 || size[heavy[u]] < size[v]) heavy[u] = v;
    }
}

int clock = 1;
int toDfs[50004];

ll askLink(int L, int R, int color) {
    return colors[color].is(toDfs[L], toDfs[R]);
}

void addLink(int L, int R, int dt, int color) {
    return colors[color].ia(toDfs[L], toDfs[R], dt);
}

void dfsHeav(int u=1, int f=-1) {
    if(f == -1) hp[u] = u;
    toDfs[u] = clock++;
    if(heavy[u] != -1) {
        hp[heavy[u]] = hp[u];
        dfsHeav(heavy[u], u);
    }
    for(int& v:elist[u]) if(v != f && v != heavy[u]) {
        hp[v] = v;
        dfsHeav(v, u);
    }
}

ll askToRoot(int u, int color) {
    ll ans = 0;
    while(u != -1) {
        ans += askLink(hp[u], u, color);
        u = par[hp[u]];
    }
    return ans;
}

void addToRoot(int u, int dt, int color) {
    while(u != -1) {
        addLink(hp[u], u, dt, color);
        u = par[hp[u]];
    }
}

int type[50004];
int ck[50004];
ll sumT[50004], sumT2[50004];

void make(int i, int dt) {
    sumT[type[i]] += dt * dep[i];
    sumT2[type[i]] += dt * (2 * askToRoot(i, type[i])) + dep[i];
    addToRoot(i, dt, type[i]);
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, q, c; cin >> n >> m >> q >> c;
    rep1(i, n) cin >> type[i];
    iter(i, 2, n+1) {
        int f; cin >> f;
        elist[f].pb(i);
        elist[i].pb(f);
    }
    rep1(i, m) cin >> ck[i];
    dfsSize();
    dfsHeav();
    rep1(i, n) {
        make(i, 1);
    }
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int x, w; cin >> x >> w;
            make(x, -1);
            type[x] = w;
            make(x, 1);
        } else {
            int k; cin >> k;
            ll ans = 1ll * n * c * c;
            ans += 1ll * ck[k] * ck[k] * sumT2[k];
            ans -= 2 * ck[k] * c * sumT[k];
            long double v = ans;
            v /= n;
            cout << fixed << setprecision(20) << v << endl;
        }
    }
}

```

---

## 作者：wptt (赞：1)

题目复杂不可读，固抄了一个形式化题意。

给定一个 $n$ 个节点的有根树，有 $m$ 中颜色，第 $i$ 个点的颜色为 $f_i$，颜色 $i$ 的权值为 $c_i$。

有两种操作：

1. 将 $f_x\gets y$。
2. 从树中等概率的选择一个节点 $i$，求解 $(S_i\times c_x-C)^2$ 的期望，其中 $S_i$ 表示以 $i$ 为根的子树中 $x$ 颜色的数量。

显然 $\dfrac{1}{n}\sum\limits_{i=1}^n (S_i\times c_x-C)^2$ 这个东西是很难直接维护的，那么拆开得到：

$$\begin{aligned}
\dfrac{1}{n}\sum\limits_{i=1}^n (S_i\times c_x-C)^2&=\dfrac{1}{n}\left( \sum\limits_{i=1}^n (S_i\times c_x)^2-2C\times c_x\times S_i+C^2 \right)\\
&=C^2+\dfrac{{c_{x}}^2}{n}\sum\limits_{i=1}^n {S_i}^2-\dfrac{2C\times c_{x}}{n}\sum\limits S_{i}
\end{aligned}
$$

所以现在就只需要维护 $\sum\limits_{i=1}^n {S_{i}}^2$ 和 $\sum\limits_{i=1}^n S_{i}$ 就可以了。

如果改变了点 $x$，那么其原本到根路径上 $S_{i}$ 所有的 $x$ 都要减 $1$。

$$\begin{aligned}
(S_{i}-1)^2={S_{i}}^2-2\times S_{i}+1
\end{aligned}$$

但是因为直接开 $m$ 棵线段树的空间复杂度为 $O(nm)$，所以需要动态开点做到 $O(m\log n)$。

时间复杂度为 $O(n\max\{f_{i}\}+q\log n)$。

---

## 作者：Hadtsti (赞：1)

### 题意简述

注：原题翻译有点小锅，题目中的 $b$ 和 $c$ 应该是一个东西。本文暂且写作 $c$。

给出一棵 $n(2\le n\le 5\times 10^4)$ 个节点的有根树，根为 $1$。点 $2\sim n$ 的父亲为 $p_2\sim p_n$。有 $m(1\le m\le 5\times 10^4)$ 种颜色。点 $i$ 的颜色为 $f_i(1\le f_i\le m)$，颜色 $i$ 的权值为 $c_i(1\le c_i\le 100)$。

有两种操作共 $q(1\le q\times 5\times 10^4)$ 次：

- $\texttt{1 }x\text{ }y$，将 $f_x\leftarrow y$。

- $\texttt{2 }x$，从树中等概率选取一个点 $i$，得到 $(S_ic_x-C)^2$ 的价值。求期望价值。其中 $S_i$ 表示以 $i$ 为根的子树中颜色为 $x$ 的节点数。$C$ 是给定的常数。

### 题目分析

一个比较裸的树剖，甚至只有路径修改单点查询。

先分析操作 $2$。这一询问实际上是求 $\displaystyle \frac{1}{n}\sum_{i=1}^n(S_ic_x-C)^2$。直接维护不太可行，因此我们对它进行一下转换，把不同次数的项分解开来维护（类似于[方差](https://www.luogu.com.cn/problem/P1471)这个题）：

$\ \ \ \ \displaystyle\frac{1}{n}\sum_{i=1}^n(S_ic_x-C)^2$

$\displaystyle=\frac{1}{n}\sum_{i=1}^n(S_i^2c_x^2-2S_ic_xC+C^2)$

$\displaystyle=\frac{1}{n}\sum_{i=1}^nS_i^2c_x^2-\frac{1}{n}\sum_{i=1}^n2S_ic_xC+C^2$

$\displaystyle=\frac{c_x^2}{n}\sum_{i=1}^nS_i^2-\frac{2c_xC}{n}\sum_{i=1}^nS_i+C^2$

$c_x$ 和 $C$ 都是固定常数，也就是说我们只用维护 $\displaystyle\sum_{i=1}^nS_i^2$ 和 $\displaystyle\sum_{i=1}^nS_i$ 就可以，这两个量的合并都十分直观（还是类似[方差](https://www.luogu.com.cn/problem/P1471)这个题）。

再看操作 $1$。这一修改实质上只涉及到从 $x$ 到根的路径上的结点，就是典型的路径修改。只需要把这条路径上旧颜色的 $S$ 减 $1$，新颜色的 $S$ 加 $1$ 即可。

注意到颜色数不多，很容易想到重链剖分后直接维护 $m$ 棵线段树。但是构造完整的线段树结构肯定会 MLE（空间复杂度 $O(nm)$），所以考虑动态开点。空间复杂度降到 $O(m \log^2 n)$，此题空间限制最大能开到 $O(1.6\times 10^7)$，已经足够了。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,op,x,y,f[50010],b[50010],a[50010],nd,num[50010];
int tot,hd[50010],nt[50010],v[50010];
int cnt,d[50010],top[50010],fa[50010],dfn[50010],son[50010],size[50010];
long long C;
struct node
{
	int ls,rs;//左右子结点编号。 
	long long sqsum,sum,tag;//平方和、和、懒标记。 
}tr[16000010];//线段树结点结构体 
void rd(int &x)
{
	x=0;
	char c=getchar();
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
}//快读 
void rd(long long &x)
{
	x=0ll;
	char c=getchar();
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())
		x=(x<<3ll)+(x<<1ll)+c-'0';
}//快读
void add(int x,int y)
{
	v[++tot]=y;
	nt[tot]=hd[x];
	hd[x]=tot;
}//建边 
void dfs1(int x)
{
	size[x]=1;
	d[x]=d[fa[x]]+1;
	for(int i=hd[x];i;i=nt[i])
	{
		int y=v[i];
		dfs1(y);
		size[x]+=size[y];
		if(size[y]>size[son[x]])
			son[x]=y;
	}
}//第一遍 DFS，计算出结点深度 d、子树大小 size 并找到重儿子 son。 
void dfs2(int x,int tp)
{
	top[x]=tp;
	dfn[x]=++cnt;
	if(!son[x])
		return;
	dfs2(son[x],tp);
	for(int i=hd[x];i;i=nt[i])
	{
		int y=v[i];
		if(y!=son[x])
			dfs2(y,y);
	}
}//第二遍 DFS，计算出重链顶 top、遍历顺序 dfn。 
void pushup(int p)
{
	tr[p].sqsum=tr[tr[p].ls].sqsum+tr[tr[p].rs].sqsum;//平方和更新 
	tr[p].sum=tr[tr[p].ls].sum+tr[tr[p].rs].sum;//和更新 
}//用子结点更新父结点。 
void addtag(int &p,long long val,int len)
{
	if(!p)
		p=++nd;//原来没有就新建。 
	tr[p].sqsum+=2ll*tr[p].sum*val+1ll*len*val*val;//平方和更新 
	tr[p].sum+=1ll*len*val;//和更新 
	tr[p].tag+=val;//标记更新 
}//打标记。 
void pushdown(int &p,int len)
{
	if(tr[p].tag)
	{
		addtag(tr[p].ls,tr[p].tag,(len+1)/2);//左儿子 
		addtag(tr[p].rs,tr[p].tag,len/2);//右儿子 
		tr[p].tag=0;//清空标记 
	}
}//下传懒标记。 
void change(int ql,int qr,int &p,int l,int r,long long val) //ql:当前结点左端点，qr:当前结点右端点，p:当前结点，l:询问左端点，r:询问右端点，val:更新的值。 
{
	if(!p)
		p=++nd;//原来没有就新建。 
	if(ql>=l&&qr<=r)//全包含直接修改。 
	{
		addtag(p,val,qr-ql+1);
		return;
	}
	pushdown(p,qr-ql+1); 
	int mid=ql+qr>>1;
	if(mid>=l)
		change(ql,mid,tr[p].ls,l,r,val);//左子结点 
	if(mid<r)
		change(mid+1,qr,tr[p].rs,l,r,val);
	pushup(p);
}//线段树区间修改。 
void change_to_root(int x,int col,long long val)//从 x 修改到根。 
{
	while(top[x]!=1)
	{
		change(1,n,num[col],dfn[top[x]],dfn[x],val);
		x=fa[top[x]];//一条重链一条重链地改 
	}
	change(1,n,num[col],1,dfn[x],val);
}
int main()
{
	rd(n),rd(m),rd(q),rd(C);
	for(int i=1;i<=n;i++)
		rd(a[i]);
	for(int i=2;i<=n;i++)
		rd(fa[i]),add(fa[i],i);
	for(int i=1;i<=m;i++)
		rd(b[i]);
	dfs1(1);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		change_to_root(i,a[i],1);//初始化 
	while(q--)
	{
		rd(op),rd(x);
		if(op==1)
		{
			rd(y);
			change_to_root(x,a[x],-1);//把原来颜色的删掉 1 
			a[x]=y;
			change_to_root(x,a[x],1);//新颜色加上 1
		}			
		else
			printf("%.10lf\n",(double)(b[x]*b[x]*tr[num[x]].sqsum-2*b[x]*C*tr[num[x]].sum)/n+C*C);
	}
	return 0;
}
```


---

## 作者：lzyqwq (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17518977.html)**

**[洛谷](https://www.luogu.com.cn/problem/CF960H "洛谷")**

**[CF](https://codeforces.com/contest/960/problem/H "CF")**

**注：为了避免混淆，修改了部分变量的名称**。

> - 给出 $n$ 个点的有根树，$m$ 种颜色，点 $i$ 有颜色 $a_i$，颜色 $i$ 有权值 $b_i$。维护两种操作，共 $q$ 次：
>    - $\texttt{1 }x\text{ }y$，将 $a_x\leftarrow y$。
>   
>    - $\texttt{2 }x$，从树中等概率选取一个点 $i$，得到 $(S_i\times b_x-C)^2$ 的价值。求期望价值。其中 $S_i$ 表示以 $i$ 为根的子树中颜色为 $x$ 的节点数。$C$ 是给定的常数。
> - $n,m\le 5\times 10^4$。

先写出答案的表达式：

$$\begin{aligned}\dfrac{\sum_{i=1}^n(S_i\times b_x-C)^2}{n}&=\dfrac{\sum_{i=1}^n(b_x^2S_i^2-2b_xCS_i+C^2)}{n}\\&=\dfrac{b_x^2\sum_{i=1}^n S_i^2-2b_xC\sum_{i=1}^nS_i+nC^2}{n}\end{aligned}$$

考虑维护每种颜色的 $S_i$，套路树剖再动态开点线段树。操作 $\texttt{1}$ 相当于对颜色 $a_x$ 将根到 $x$ 路径上的 $S_i$ 减 $1$，对于颜色 $y$ 将这些 $S_i$ 加 $1$。这个修改区间含根节点很友好，不需要正常跳链，直接从 $x$ 跳到根就好了。

线段树的节点要维护平方和以及和，简单讲一下平方和的维护：

$$\begin{aligned}\sum\limits_{i=l}^r(x_i+v)^2&=\sum\limits_{i=l}^r(x_i^2+2vx_i+v^2)\\&=\sum\limits_{i=l}^rx_i^2+2v\sum\limits_{i=l}^rx_i+(r-l+1)v^2\end{aligned}$$

就是在**原来平方和**的基础上加上 $2v$ 倍的**原来的和**，再加上 $(r-l+1)v^2$。由于是动态开点线段树不方便 pushdown，所以写了标记永久化。

对于 $\texttt{2}$ 操作，查询区间也很友好，直接用那种颜色线段树的根的信息就可以了。

时空复杂度均为 $\mathcal{O}(m\log^2n)$，可以接受。

**[评测记录](https://codeforces.com/contest/960/submission/211670722 "评测记录")**

```cpp
//指针预警/cf。
#include<bits/stdc++.h>
#define ls x->lc
#define rs x->rc
#define int long long
using namespace std;
const int N=5e4+5;
int n,m,q,c,a[N],b[N],f[N],sz[N],d[N],t[N],h[N],dfn[N],cnt;
vector<int>g[N];
struct node{
	int sum,sq,add;
	node*lc,*rc;
	node(){
		sum=sq=add=0;
		lc=rc=NULL;
	}
}*rt[N];
void dfs1(int u){
	sz[u]=1;
	for(int v:g[u]){
		d[v]=d[u]+1;
		dfs1(v);
		sz[u]+=sz[v];
	}
}
void dfs2(int u){
	for(int v:g[u]){
		if((sz[v]<<1ll)>sz[u]){
			t[h[u]=v]=t[u];
		}else{
			t[v]=v;
		}
		dfs2(v);
	}
}
void dfs3(int u){
	dfn[u]=++cnt;
	if(h[u]){
		dfs3(h[u]);
	}
	for(int v:g[u]){
		if(v^h[u]){
			dfs3(v);
		}
	}
}
void modify(node*&x,int l,int r,int ql,int qr,int k){
	if(x==NULL){
		x=new node;
	}
	if(ql<=l&&r<=qr){
		x->add+=k;
		x->sq+=2*k*x->sum+(r-l+1)*k*k;
		x->sum+=(r-l+1)*k; 
	}else{
		int mid=(l+r)>>1ll;
		if(ql<=mid){
			modify(ls,l,mid,ql,qr,k);
		}
		if(qr>mid){
			modify(rs,mid+1,r,ql,qr,k);
		}
		x->sum=x->sq=0;
		if(ls!=NULL){
			x->sum+=ls->sum;
			x->sq+=ls->sq;
		}
		if(rs!=NULL){
			x->sum+=rs->sum;
			x->sq+=rs->sq;
		}
		x->sq+=2*x->add*x->sum+(r-l+1)*x->add*x->add;
		x->sum+=(r-l+1)*x->add;
	}
}
void chain(int k,int x,int v){
	while(x){
		modify(rt[k],1,n,dfn[t[x]],dfn[x],v);
		x=f[t[x]];
	}
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>n>>m>>q>>c;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=2;i<=n;++i){
		cin>>f[i];
		g[f[i]].emplace_back(i);
	}
	for(int i=1;i<=m;++i){
        rt[i]=NULL;
		cin>>b[i];
	}
	dfs1(1);
	dfs2(t[1]=1);
	dfs3(1);
	for(int i=1;i<=n;++i){
		chain(a[i],i,1);
	}
	for(int op,x,y;q--;){
		cin>>op>>x;
		if(op&1ll){
			cin>>y;
			chain(a[x],x,-1);
			chain(a[x]=y,x,1);
		}else{
			if(rt[x]==NULL){//无这种颜色。
				cout<<c*c<<'\n';
			}else{
				cout<<fixed<<setprecision(12)<<(1.0*b[x]*b[x]*rt[x]->sq-1.0*2*b[x]*c*rt[x]->sum+n*c*c)/n<<'\n';
			}
		}
	}
}

---

## 作者：Reunite (赞：1)

~~不容易啊独立做出来一道 $3100$。~~

## 一
---
首先我们把那个式子拆了，变成 

$$\large \frac{b_x^2\sum{s_i^2}-2Cb_x\sum s_i+nC^2}{n}$$

发现期望是假的，先丢掉常数项，考虑如何维护分子，发现我们要快速维护每一个子树内某中颜色的个数和，与个数平方和，这样正着考虑是不怎么好做的。

考虑一个颜色为 $c$ 的节点 $u$，它只会对它祖先在颜色为 $c$ 这一部分的答案产生贡献。动态想一下的话，就相当于题目变成了对应链加，求全局和，平方和。这是重剖可以维护的。

具体的，我们对每种颜色开一个线段树，因为点总数是少的，直接上动态开点维护即可。注意动态开点线段树推标记的时候对于空的左右儿子也是要推的。（我调了好久才反应过来）。

---

## 二
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

int n,m,q,C,dfs_clock,tot;
int b[50005];
int c[50005];
int fa[50005];
int sz[50005];
int dfn[50005];
int son[50005];
int top[50005];
int dep[50005];
int rt[100005];
ll t[8000005];
ll s[8000005];
int tg[8000005];
int lc[8000005];
int rc[8000005];
vector <int> g[50005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

void dfsfind(int u){
	sz[u]=1;
	dep[u]=dep[fa[u]]+1;
	for(int v:g[u]){
		dfsfind(v);
		sz[u]+=sz[v];
		if(sz[son[u]]<sz[v]) son[u]=v;
	}
	return ;
}

void dfstime(int u,int tp){
	top[u]=tp;
	dfn[u]=++dfs_clock;
	if(son[u]) dfstime(son[u],tp);
	for(int v:g[u]){
		if(son[u]==v) continue;
		dfstime(v,v);
	}
	return ;
}

inline void addtag(int u,int len,int x){
	s[u]+=2ll*x*t[u]+1ll*len*x*x;
	t[u]+=x*len;
	tg[u]+=x;
	return ;
}

inline void pushdown(int u,int l,int r){
	if(!tg[u]) return ;
	int mid=(l+r)>>1;
	if(!lc[u]) lc[u]=++tot;
	if(!rc[u]) rc[u]=++tot;
	addtag(lc[u],mid-l+1,tg[u]);
	addtag(rc[u],r-mid,tg[u]);
	tg[u]=0;
	return ;
}

int updata(int u,int l,int r,int L,int R,int x){
	if(!u) u=++tot;
	if(L<=l&&r<=R){
		addtag(u,r-l+1,x);
		return u;
	}
	pushdown(u,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) lc[u]=updata(lc[u],l,mid,L,R,x);
	if(R>mid) rc[u]=updata(rc[u],mid+1,r,L,R,x);
	t[u]=t[lc[u]]+t[rc[u]];
	s[u]=s[lc[u]]+s[rc[u]];
	return u;
}

inline void change(int u,int v,int x,int s){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		rt[x]=updata(rt[x],1,n,dfn[top[u]],dfn[u],s);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	rt[x]=updata(rt[x],1,n,dfn[v],dfn[u],s);
	return ;
}

int main(){
	in(n),in(m),in(q),in(C);
	for(int i=1;i<=n;i++) in(c[i]);
	for(int i=2;i<=n;i++){
		in(fa[i]);
		g[fa[i]].push_back(i);
	}
	for(int i=1;i<=m;i++) in(b[i]);
	dfsfind(1);
	dfstime(1,1);
	for(int i=1;i<=n;i++) change(i,1,c[i],1);
	int op,x,y;
	while(q--){
		in(op);
		if(op==1){
			in(x),in(y);
			change(x,1,c[x],-1);
			c[x]=y;
			change(x,1,c[x],1);
		}
		else{
			in(x);
			ll ans=1ll*n*C*C+1ll*b[x]*b[x]*s[rt[x]]-2ll*C*b[x]*t[rt[x]];
			printf("%lf\n",ans*1./n);
		}
	}

	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

简单的 *3100 树剖题。

写出答案式子:

$$\frac{\sum (S_{i,x}b_x - C)^2}{n} = \frac{b_x^2\sum S_{i,x}^2 - 2 b_x C \sum S_{i,x}}{n} + C^2$$

然后转换成维护区间修改和维护区间和，平方和的问题了，平方和的式子是 $\sum (x+k)^2 = \sum x^2 + 2k \sum x + len \times k$。

颜色的问题我们直接动态开点线段树，每棵线段树维护一种颜色，线段树上每个点维护树上子树颜色和，那么 1 操作就是对从 $u$ 到根的所有 $k$ 颜色的节点 $+1$，对原来的颜色 $-1$。

注意线段树空间开大一点就好了，复杂度 $O(n\log^2 n)$。

[submission](https://codeforces.com/contest/960/submission/284173252)

---

## 作者：wwwwwza (赞：0)

先拆式子 $\sum\limits_{i=1}^n (S_i\times b_x-C)^2=\sum\limits_{i=1}^n ((S_i\times b_x)^2-2\times S_i\times b_x\times C +C^2)=C^2+\sum\limits_{i=1}^n (S_i\times b_x)^2+2\times C\times \sum\limits_{i=1}^n S_i\times b_x$。

那么问题就转化为求 $S_i\times b_x$ 和其平方和，直接动态开点和树链剖分即可。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,m,q,c,col[N],val[N],opt,x,y,root[N],idx=0;
int dfn[N],son[N],dep[N],top[N],siz[N],fat[N],cnt=0;
vector<int>g[N];
struct seg{
	int lson,rson,num,sum,tag;
}tree[N*50];
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int topx){
	top[u]=topx;
	dfn[u]=++cnt;
	if(!son[u])return;
	dfs2(son[u],topx);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==son[u])continue;
		dfs2(v,v);
	}
} 
void push(int rt,int l,int r,int d){
	tree[rt].sum+=(2*tree[rt].num*d+(r-l+1)*d*d);
	tree[rt].num+=(r-l+1)*d;
	tree[rt].tag+=d;
}
void pushdown(int rt,int l,int r){
	if(tree[rt].tag){
		int mid=l+r>>1;
		if(!tree[rt].lson)tree[rt].lson=++idx;
		if(!tree[rt].rson)tree[rt].rson=++idx;
		push(tree[rt].lson,l,mid,tree[rt].tag);
		push(tree[rt].rson,mid+1,r,tree[rt].tag);
		tree[rt].tag=0;
	}
}
void update(int &rt,int l,int r,int x,int y,int d){
	if(!rt)rt=++idx;
	if(x<=l&&r<=y){
		push(rt,l,r,d);
		return;
	}
	pushdown(rt,l,r);
	int mid=l+r>>1;
	if(x<=mid)update(tree[rt].lson,l,mid,x,y,d);
	if(y>mid)update(tree[rt].rson,mid+1,r,x,y,d);
	tree[rt].num=tree[tree[rt].lson].num+tree[tree[rt].rson].num;
	tree[rt].sum=tree[tree[rt].lson].sum+tree[tree[rt].rson].sum;
} 
void pre(int x,int y,int d,int rt){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		update(root[rt],1,n,dfn[top[x]],dfn[x],d);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	update(root[rt],1,n,dfn[x],dfn[y],d);
}
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&q,&c);
	for(int i=1;i<=n;i++)scanf("%lld",&col[i]);
	for(int i=2;i<=n;i++){
		scanf("%lld",&x);
		fat[i]=x;
		g[x].push_back(i);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=m;i++)scanf("%lld",&val[i]);
	for(int i=1;i<=n;i++){
		pre(1,i,val[col[i]],col[i]);
	}
	while(q--){
		scanf("%lld",&opt);
		if(opt==1){
			scanf("%lld%lld",&x,&y);
			pre(1,x,-val[col[x]],col[x]);
			col[x]=y;
			pre(1,x,val[col[x]],col[x]);
		}else{
			scanf("%lld",&x);
			int ans=tree[root[x]].sum-2*c*tree[root[x]].num+c*c*n;
			double res=ans/(double)n;
			printf("%.8lf\n",res);
		}
	}
	return 0;
}

```

---

