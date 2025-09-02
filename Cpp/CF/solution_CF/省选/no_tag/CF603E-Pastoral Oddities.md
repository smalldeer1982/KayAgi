# Pastoral Oddities

## 题目描述

In the land of Bovinia there are $ n $ pastures, but no paths connecting the pastures. Of course, this is a terrible situation, so Kevin Sun is planning to rectify it by constructing $ m $ undirected paths connecting pairs of distinct pastures. To make transportation more efficient, he also plans to pave some of these new paths.

Kevin is very particular about certain aspects of path-paving. Since he loves odd numbers, he wants each pasture to have an odd number of paved paths connected to it. Thus we call a paving sunny if each pasture is incident to an odd number of paved paths. He also enjoys short paths more than long paths, so he would like the longest paved path to be as short as possible. After adding each path, Kevin wants to know if a sunny paving exists for the paths of Bovinia, and if at least one does, the minimum possible length of the longest path in such a paving. Note that "longest path" here means maximum-weight edge.

## 说明/提示

For the first sample, these are the paths that Kevin should pave after building the $ i $ -th path:

1. No set of paths works.
2. Paths 1 (length $ 4 $ ) and 2 (length $ 8 $ ).
3. Paths 1 (length $ 4 $ ) and 2 (length $ 8 $ ).
4. Paths 3 (length $ 2 $ ) and 4 (length $ 3 $ ).

In the second sample, there never exists a paving that makes Kevin happy.

## 样例 #1

### 输入

```
4 4
1 3 4
2 4 8
1 2 2
3 4 3
```

### 输出

```
-1
8
8
3
```

## 样例 #2

### 输入

```
3 2
1 2 3
2 3 4
```

### 输出

```
-1
-1
```

## 样例 #3

### 输入

```
4 10
2 1 987
3 2 829
4 1 768
4 2 608
3 4 593
3 2 488
4 2 334
2 1 204
1 3 114
1 4 39
```

### 输出

```
-1
-1
829
829
768
768
768
488
334
204
```

# 题解

## 作者：Saliеri (赞：54)

来一篇写得清楚一点的线段树分治。

___

首先我们考虑这个题目的限制 ，`每个点的度数都是奇数` ，的本质是什么。

手玩几个图，珂以发现一个很强的结论：

这个限制等价于 “这个图中只存在大小为**偶数**的连通块”。

证明：

- 必要性：假设存在奇数大小的连通块，由于每个点的度数都为奇数，所有所有度数之和也为奇数。然而每一条边都对总度数贡献且只贡献了 **2**，所以**总度数必然是偶数**。这就与假设矛盾。所以只有必然只存在偶数大小的连通块。

- 充分性：对于每一个偶数大小的连通块，随便拿出它的一颗生成树，从底向上跑一遍这个算法：

	- 如果这个节点儿子连上来的边数为偶数，就连上他与父亲的边，反之则不然。
  
  我们发现，这样的构造可以满足除了根的所有节点的限制。
  
  然而因为这个连通块内除根外其他节点的数量是奇数，而这些点的度数都是奇数，而包括根的总度数是偶数，所以根的度数自然也是奇数。

证明完结论后，就可以开始考虑 `最小化边集中的最大边权` 的这个限制了。

很明显，这个条件一看就很有**最小瓶颈生成树**的感觉，而最小瓶颈生成树的解决方式应该人人皆知。Kruskal，即按权值从小到大加边直到满足条件为止。

~~这个题应该不会有人因为在这里想到 Prim 然后掉进粪坑吧~~

到这里我们就可以得到这个问题的静态版本的解法：

- **把边按权值排序**，用并查集时刻维护一下奇连通块的数目就行了。

接下来我们考虑怎么把这个算法扩展到动态加边。

不难想到的是，这个算法想要支持动态加边且保证复杂度基本是胡扯。

因为在排序后的边集的中间加边就可能会导致整张图的形态从那里开始变化，从而影响答案，而这个影响我们是无法快速算出的。

但如果我们仔细考虑一下加边的过程，发现：一条边如果进入时就没有进入最优边集，那么就再也不会进入；一条边一旦被淘汰，就再也不会回来。

说明：每一条边有一个影响范围，只有这个范围内这条边才会被纳入最优边集中。

**影响范围 & 时间轴 -> 线段树分治。**

接下来就考虑怎么求出每条边的影响区间。

考虑在线段树分治的过程中，每访问到一个叶子，我们都必然需要后移 Kruskal 的指针，将新的合法的边纳入答案直到合法为止。那么这个时间点就是这条边的影响范围的结束位置，而我们又知道每一条边的出现时间，于是事情就好起来了。



注意：分治时应当**从右到左**递归，因为我们是要依次对每一个时间点求出答案，然后通过答案计算被最优边集包含的边影响区间。如果从左到右的话，得不到每一条边的影响区间的结束位置。

但是我们发现这是一个边分治边 cover 的处理过程，直接线段树分治起来可能会有点小问题，因为这个时间点上 cover 上的边不知道什么时候撤回掉。

这也很简单啊，只 cover 到当前时间减一就可以了，这个点上 cover 上的边在这个点直接撤回就完事了。

这个算法的原理也很好理解：

我们每次在叶子节点找答案，祖先节点上 cover 上的时间戳必然合法，在这个点上 cover 上的边也会因为判断而只加起始时间在当前时间点之前的边。

原本我们的时间复杂度因为每一次暴力加边而变得不可接受。

而通过计算决策的影响范围与将这些范围线段树分治，就减少了大量的重复计算。

总的复杂度还是经典的 $O(m \log m \log n)$。

___

代码区：

自认为代码写的比较好看……

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
const int maxn = 3e5+5;
int n,m,pos,ans[maxn],odd;
struct Edge{
	int x,y,v,id;
	bool operator <(Edge b){return v<b.v;}
}e[maxn];
struct ch{int x,y,dlt;};
ch st[maxn];
int fa[maxn],siz[maxn],top;
int getfa(int x){return fa[x] == x ? x : getfa(fa[x]);}
std :: vector <Edge> vec[maxn<<2];
void cover(int k,int l,int r,int x,int y,Edge v){
	if(l>y||r<x||x>y)return ;
	if(l>=x&&r<=y)return vec[k].push_back(v),void();
	int mid = l+r>>1;
	cover(k<<1,l,mid,x,y,v),cover(k<<1|1,mid+1,r,x,y,v);
}
void trymerge(int x,int y){
	int fx = getfa(x),fy = getfa(y);
	if(fx != fy){
		if(siz[fx]<siz[fy])fx^=fy^=fx^=fy;
		st[++top] = (ch){fx,fy,0};
		if(siz[fx]%2==1&&siz[fy]%2==1)odd-=2,st[top].dlt+=2;
		siz[fx] += siz[fy],fa[fy] = fx;
	}
}
void getans(int k,int l,int r){
	int pretop = top;
	for(int i=0;i<vec[k].size();++i)trymerge(vec[k][i].x,vec[k][i].y);
	int mid = l+r>>1;
	if(l == r){
		while(1){
			if(odd == 0 || pos == m)break;
			if(e[pos+1].id <= l){
				trymerge(e[pos+1].x,e[pos+1].y);
				cover(1,1,m,e[pos+1].id,l-1,e[pos+1]);
			}
			++pos;
		}
		if(odd == 0)ans[l] = e[pos].v;
		else ans[l] = -1;
	}
	else getans(k<<1|1,mid+1,r),getans(k<<1,l,mid);
	while(top^pretop){
		int x = st[top].x,y = st[top].y,dlt=st[top].dlt;
		siz[x] -= siz[y],fa[y] = y,odd += dlt,--top;
	}
}
int main(){
	scanf("%d %d",&n,&m),odd = n;
	for(int i=1;i<=n;++i)fa[i] = i,siz[i] = 1;
	for(int i=1;i<=m;++i)scanf("%d %d %d",&e[i].x,&e[i].y,&e[i].v),e[i].id = i;
	std::sort(e+1,e+m+1),getans(1,1,m);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：asuldb (赞：25)

[题目](http://codeforces.com/problemset/problem/603/E)

经过大力手玩不难发现存在一个边集使得每个点的度数都是奇数的充要条件是**不存在奇数个点的联通块**。

考虑证明奇数个点的联通块一定不合法。刚开始所有点度数均为偶数，考虑加入一条边$(u,v)$的影响：

- $u,v$度数均为偶数，那么加入$(u,v)$后两点度数均变为奇数，奇度点个数增加$2$。

- $u,v$度数均为奇数，那么加入$(u,v)$后两点度数均变为偶数，奇度点个数减少$2$。

- $u,v$度数一奇一偶，那么加入$(u,v)$之后奇偶性交换，奇度点个数不变。

不难发现加入一条边会令奇度点个数$+2,-2$或不变，于是奇度点个数始终为偶数，不可能存在一个奇数个点的联通块满足条件。

对于偶数个点的联通块，可以直接找出其一棵生成树，之后用一层层删叶子的方法就能构造出一个合法的边集。

现在的我们需要求出一个边集，使得所有联通块均有偶数个点，且最小化最大边集。不难想到一个类似于kruskal的做法，即将所有边从小到大排序，并查集维护联通块的点数，顺次加入每一条边，直到不存在奇数个点的联通块为止。

考虑到加入边的过程中答案是不升的，即加入一条边后答案不可能变大，于是考虑用cdq分治来解决问题。

设当前我们处理的是$[l,r]$内的边，且答案在$[x,y]$中；我们保证，加入时间在$[1,l)$且权值小于$x$的都已经被加入了。尝试求出$ans_{mid}$，这样就能分治到$[l,mid-1,ans_{mid},y]$和$[mid+1,r,x,ans_{mid}]$去处理。

我们先将$[l,mid]$中边权小于$x$的边加入，之后在从小到大加入权值在$[x,y]$之间的边；一旦满足条件就停止，此时最后加入的边的边权就是$ans_{mid}$。

当往下分治的时候，我们需要保证性质继续满足；于是分治左区间的时候需要把权值小于$ans_{mid}$的边中出现时间小于$l$的边加入，分治右区间的时候需要把出现时间小于$mid+1$的边中权值小于$x$的加入。

由于分治完后要撤回新加入的边，于是可以维护一个支持撤回的并查集，时间复杂度是$O(m\log m\log n)$。

代码

```cpp
#include<bits/stdc++.h>
#define re register
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int maxn=1e5+5,maxm=3e5+5;
struct Edge{int u,v,t,w;}e[maxm],E[maxm];
int n,m,ans[maxm],id[maxm];
inline int cmp(const Edge &A,const Edge &B) {return A.w<B.w;}
struct dsu{
	int fa[maxn],sz[maxn],tot,top,st[maxn];
	inline void bud() {
		tot=n;for(re int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	}
	inline int find(int x) {
		while(x!=fa[x])x=fa[x];return x;
	}
	inline void lnk(int x,int y) {
		x=find(x),y=find(y);if(x==y) return;
		if(sz[x]<sz[y]) x^=y,y^=x,x^=y;
		fa[y]=x;tot-=(sz[x]&1),tot-=(sz[y]&1);
		sz[x]+=sz[y];tot+=(sz[x]&1);st[++top]=y;
	}
	inline void back() {
		int y=st[top--],x=fa[y];
		tot-=(sz[x]&1);sz[x]-=sz[y];fa[y]=y;
		tot+=(sz[x]&1);tot+=(sz[y]&1);
	}
}S;
void cdq(int l,int r,int x,int y) {
	if(l>r) return;
	int mid=l+r>>1,pre=S.top;
	for(re int i=l;i<=mid;++i)
		if(id[i]<x) S.lnk(E[i].u,E[i].v);
	for(re int i=x;i<=y;++i) {
		if(e[i].t<=mid) S.lnk(e[i].u,e[i].v); 
		if(!S.tot) {ans[mid]=i;break;}
	}
	while(S.top>pre) S.back();
	if(!ans[mid]) {
		for(re int i=l;i<=mid;++i) 
			if(id[i]<x) S.lnk(E[i].u,E[i].v);
		cdq(mid+1,r,x,y);
		while(S.top>pre) S.back();
		return;	
	}
	for(re int i=l;i<=mid;++i) 
		if(id[i]<x) S.lnk(E[i].u,E[i].v);
	cdq(mid+1,r,x,ans[mid]);
	while(S.top>pre) S.back();
	for(re int i=x;i<ans[mid];++i) 
		if(e[i].t<l) S.lnk(e[i].u,e[i].v);
	cdq(l,mid-1,ans[mid],y);
	while(S.top>pre) S.back();
	
}
int main() {
	n=read(),m=read();S.bud();
	for(re int i=1;i<=m;i++)
		e[i].t=i,e[i].u=read(),e[i].v=read(),e[i].w=read(); 
	for(re int i=1;i<=m;i++)E[i]=e[i];
	std::sort(e+1,e+m+1,cmp);
	for(re int i=1;i<=m;i++)id[e[i].t]=i;cdq(1,m,1,m);
	for(re int i=1;i<=m;++i)if(!ans[i]) puts("-1");else printf("%d\n",e[ans[i]].w);
	return 0;
}
```



---

## 作者：xht (赞：25)

> [CF603E Pastoral Oddities](https://codeforces.com/contest/603/problem/E)

## 题意

- 给定一张 $n$ 个点的无向图，初始没有边。
- 依次加入 $m$ 条带权的边，每次加入后询问是否存在一个边集，满足每个点的度数均为奇数。
- 若存在，则还需要最小化边集中的最大边权。
- $n \le 10^5$，$m \le 3 \times 10^5$。

## 题解

对于一个 $n$ 个点的连通块，存在满足条件的边集的充要条件为 $n$ 是偶数，因为若 $n$ 是奇数，由于每个点的度数都是奇数，因此总度数为奇数，但由于每条边会产生的度数为 $2$，因此矛盾。

那如果 $n$ 为偶数，是否意味着一定存在呢？答案显然是肯定的，我们可以找出来一个生成树，然后从叶子开始，一个点与其父亲的连边保留当且仅当这个点与其所有儿子的连边数为偶数，那么就可以构造出来了。

因此这张图存在满足条件的边集当且仅当每个连通块的点数均为偶数。

我们接下来再考虑，对于一张给定的静态图，如何最小化边集中的最大边权呢？

考虑 kruskal 算法，由于加入边不会使答案变劣，因此用并查集维护每个连通块的点数，直到加入某条边后，满足所有连通块的点数均为偶数，这条边的边权就是答案。

扩展到动态加边，我们采用 LCT 维护每个连通块的最小生成树结构及大小，同时用大根堆维护所有在森林中的边。

每当我们加入一条边后，我们不断地尝试删除当前森林中边权最大的边，直到删除了某条边后出现了奇数大小的连通块，那么这条边的边权就是答案。

由于我们需要知道当前是否存在奇数大小的连通块，这里的 LCT 需要采用维护子树信息的技巧，即额外维护一个虚子树的信息总和，在 $\operatorname{access}$ 和 $\operatorname{link}$ 的时候更新。

显然每条边最多被删掉一次，因此在 $n,m$ 同阶的情况下，总时间复杂度为 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 4e5 + 7, M = 3e5 + 7;
int n, m, x[M], y[M], z[M], v[M], cnt;
pq<pair<int, int>> q;

struct LCT {
	int f[N], ch[N][2], s[N], v[N], a[N], c[N], d[N];
	#define lc ch[p][0]
	#define rc ch[p][1]
	#define get(p) (p == ch[f[p]][1])
	#define rev(p) v[p] ^= 1, swap(ch[p][0], ch[p][1])
	#define isrt(p) (ch[f[p]][0] != p && ch[f[p]][1] != p)
	inline void upd(int p) {
		s[p] = s[ch[p][0]] + s[ch[p][1]] + d[p] + (p <= n);
		int o = a[c[lc]] > a[c[rc]] ? c[lc] : c[rc];
		c[p] = a[o] > a[p] ? o : p;
	}
	inline void spd(int p) {
		if (p && v[p]) {
			if (lc) rev(lc);
			if (rc) rev(rc);
			v[p] = 0;
		}
	}
	inline void rot(int p) {
		int x = f[p], y = f[x], u = get(p), v = get(x), o = isrt(x);
		f[ch[p][u^1]] = x, ch[x][u] = ch[p][u^1];
		f[x] = p, ch[p][u^1] = x, upd(x), upd(p);
		if ((f[p] = y) && !o) ch[y][v] = p;
	}
	void pre(int p) {
		if (!isrt(p)) pre(f[p]);
		spd(p);
	}
	inline void splay(int p) {
		pre(p);
		for (int x = f[p]; x = f[p], !isrt(p); rot(p))
			if (!isrt(x)) rot(get(p) == get(x) ? x : p);
	}
	inline void access(int p) {
		for (int x = 0; p; p = f[x=p])
			splay(p), d[p] += s[rc], d[p] -= s[rc=x], upd(p);
	}
	inline void mkrt(int p) {
		access(p), splay(p), rev(p);
	}
	inline void split(int x, int y) {
		mkrt(x), access(y), splay(y);
	}
	inline int fdrt(int p) {
		access(p), splay(p);
		while (lc) spd(p), p = lc;
		return splay(p), p;
	}
	inline void link(int x, int y) {
		mkrt(x), access(y), splay(y), cnt -= s[x] & 1, cnt -= s[y] & 1;
		d[f[x]=y] += s[x], upd(y), cnt += s[y] & 1;
	}
	inline void cut(int x, int y) {
		split(x, y), cnt -= s[y] & 1;
		f[x] = ch[y][0] = 0, upd(y), cnt += s[x] & 1, cnt += s[y] & 1;
	}
	inline int add(int i) {
		int x = ::x[i], y = ::y[i], z = ::z[i];
		bool ok = 1;
		if (fdrt(x) == fdrt(y)) {
			split(x, y);
			int o = c[y];
			if (a[o] > z) cut(::x[o-n], o), cut(::y[o-n], o), v[o] = 1;
			else ok = 0;
		}
		if (ok) {
			s[i+n] = 1, a[i+n] = z, c[i+n] = i + n;
			link(x, i + n), link(y, i + n), q.push(mp(z, i));
		}
		if (cnt) return -1;
		while (q.size()) {
			int o = q.top().se;
			q.pop();
			if (::v[o]) continue;
			cut(::x[o], o + n), cut(::y[o], o + n);
			if (cnt) {
				link(::x[o], o + n), link(::y[o], o + n);
				return q.push(mp(::z[o], o)), ::z[o];
			}
		}
		return 0;
	}
} lct;

int main() {
	rd(n), rd(m), cnt = n;
	for (int i = 1; i <= n; i++) lct.s[i] = 1, lct.c[i] = i;
	for (int i = 1; i <= m; i++)
		rd(x[i]), rd(y[i]), rd(z[i]), print(lct.add(i));
	return 0;
}
```

---

## 作者：_Anchor (赞：14)

## Preface

这里介绍一种复杂度为 $O(mlognlogm)$ 的**整体二分**做法。

## Problem

[CF603E Pastoral Oddities（整体二分）](https://www.luogu.com.cn/problem/CF603E)

![](https://cdn.luogu.com.cn/upload/image_hosting/q8ervcoj.png)

## Solution

**整体二分+可撤销并查集**

神仙思路。

首先做这个题必须要先手玩样例推出一个重要的性质：当一个图可以满足题目条件当且仅当途中所有连通块的大小都是偶数。

这里就暂不赘述具体的做法了，我们重点在于整体二分。

然后我们发现每次询问的答案可以二分，而且因为我们不断地加边，答案肯定越来越优，也就是说答案单调不升，于是我们可以考虑整体二分。

我们可以这样来二分：$Solve(ql,qr,vl,vr)$ 表示当前我们要处理的询问区间是 $[ql,qr]$ ，且这些询问的答案一定在 $val_vl$ ~ $val_vr$ 之间。（假设事先对于边集以权值为关键字排过序，并用一个数组存了下来）

注意：这里的 $[vl,vr]$ 是下标区间，具体来说是所有边按边权排完序过后的下标区间。

接下来想一下对于每一次分治具体怎么做：

首先，我们在处理到当前区间之前，要先保证：区间 $[1,ql]$ 的所有值 $\leq val_{vl}$ 的边都在我们当前的边集内。

然后我们才可以考虑二分，我们每次二分 $mid=ql+qr>>1$ ，那么我们现在就相当于是在权值为 $val_{vl+1}$ ~ $val_{vr}$ 且编号在 $[ql,qr]$ 中 的区间当中找到一个最小的点 $MID$ 使得这个图满足条件。

那么因为之前我们已经排过序并用一个数组存下来了，所以我们直接不停的从小到大加边直到满足条件或加完所有的边为止，那么我们把这个点记作 $MID$。（ $MID$ 一定是 $[vl,vr]$ 上的。）

然后我们判断当前状态下图是否满足形态，更新一下 $Ans[Q[mid].id]$ 。

那么现在我们就把区间分成了左右两半，要递归的子区间明显是 $Solve(ql,mid-1,MID,vr)$ 和 $Solve(mid+1,qr,vl,MID)$ 。（还是因为答案的单调不上升。）

但是在进入之前我们都要先处理一下边集：

也就是我们先还原我们在当前区间的所有操作（使用可撤销并查集即可），然后在递归左边之前，先把边权在 $val_{vl}$ ~ $val_{MID}$ 当中且边的编号在 $[1,ql]$ 中的边全部加进去。

在递归右边之前，先还原左边的影响，然后把编号在 $[ql,mid]$ 且权值 $\leq val_{vl}$ 的边加入。

然后记得我们这里的“图是否满足条件”的状态是在全局维护的（代码里就是 $Now$ ），维护的是奇数连通块个数。

最后就是并查集要按秩合并（可撤销并查集基操）。

时间复杂度 $O(mlogmlogn)$

## Code

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
const int N=4e5+5;
int n,m,Now,Ans[N];
struct Query{
	int x,y,v,id;
}Q[N],P[N];//其中P是边集按照边权排序得到的结果，Q就是正常边集。 
inline bool Cmp(Query a,Query b){return (a.v==b.v)?(a.id<b.id):(a.v<b.v);}
namespace DSU{//可撤销并查集（按秩合并） 
	int fa[N],siz[N],top;
	struct _Node{int x,y,fa1,fa2,siz1,siz2;}sta[N];
	void PreWork(){
		top=0;
		for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
		return ;
	}
	int Getfa(int x){return x==fa[x]?x:Getfa(fa[x]);}
	void Merge(int x,int y){
		int fx=Getfa(x),fy=Getfa(y);
		if(fx==fy) return ;
		if(siz[fx]>siz[fy]) swap(fx,fy);
		if((siz[fx]&1)&&(siz[fy]&1)) Now-=2;
		sta[++top].x=fx,sta[top].fa1=fx;
		sta[top].y=fy,sta[top].fa2=fy;
		sta[top].siz1=siz[fx],sta[top].siz2=siz[fy];
		fa[fx]=fy,siz[fy]+=siz[fx];
		return ;
	}
	void Return(){
		fa[sta[top].x]=sta[top].fa1,siz[sta[top].x]=sta[top].siz1;
		fa[sta[top].y]=sta[top].fa2,siz[sta[top].y]=sta[top].siz2;
		Now+=((sta[top].siz1&1)&&(sta[top].siz2&1))*2;
		top--;return ;
	}
};
using namespace DSU;
namespace Solve{
	void Solve(int vl,int vr,int ql,int qr){//处理下标在 ql-qr 的答案，且答案一定在区间下标为 vl-vr 当中。 
		if(ql>qr) return ;
		int mid=ql+qr>>1,now=top,NOW=vl,MID; //以 ans[mid] 为基准处理左右区间 
		
		for(int i=ql;i<=mid;i++) if(P[i].v<=vl) Merge(P[i].x,P[i].y); 
		for(int i=vl;i<=vr&&Now;i++,NOW++) if(Q[i].id<=mid) Merge(Q[i].x,Q[i].y);
		MID=max(NOW-1,vl);
		//更新当前 mid 点的答案 
		if(!Now) Ans[P[mid].id]=Q[MID].v;
		else Ans[P[mid].id]=-1;
		while(top>now) Return();
		//左区间 
		for(int i=vl;i<=MID;i++) if(Q[i].id<=ql) Merge(Q[i].x,Q[i].y);
		Solve(MID,vr,ql,mid-1);
		while(top>now) Return();
		//右区间 
		for(int i=ql;i<=mid;i++) if(P[i].v<=vl) Merge(P[i].x,P[i].y);
		Solve(vl,MID,mid+1,qr);
		while(top>now) Return();
		
		return ;
	}
}
namespace Main{
	void main(){
		read(n),read(m);
		for(int i=1,x,y,v;i<=m;i++){
			read(x),read(y),read(v);
			Q[i]=Query{x,y,v,i};
			P[i]=Q[i];
		}
		sort(Q+1,Q+m+1,Cmp);
		for(int i=1;i<=m;i++) P[Q[i].id].v=i;
		Now=n;
		PreWork();
		Solve::Solve(1,m,1,m);
		for(int i=1;i<=m;i++) printf("%d\n",Ans[i]);
		return ;
	}
};
int main(){
	Main::main();
    return 0;
}
```  

---

## 作者：Alex_Wei (赞：10)

- Update on 2022.10.25：修改笔误。

> [CF603E Pastoral Oddities](https://www.luogu.com.cn/problem/CF603E)

考察一张图合法的充要条件。

因为图上所有点度数之和为偶数，所以只要存在奇数大小连通块则不合法。否则，因为一条路径的两个端点度数均为奇数，其余均为偶数，所以将连通块内所有节点任意两两配对得到点数除以 $2$ 条路径，这些路径的对称差即合法方案。因此图合法的充要条件为所有连通块大小为偶数。

至此，存在显然的 LCT 在线维护最小生成树的 $\mathcal{O}(m\log n)$ 做法。

考虑整体二分，令 $solve(l, r, vl, vr)$ 表示已知 $ans_l \sim ans_r$ 在 $[vl, vr]$ 范围内，求 $ans_l\sim ans_r$。接下来有两个方向：

- 对 $[l, r]$ 分治，令 $mid = \frac{l + r} 2$，二分求出 $ans_{mid}$，然后 $solve(l, mid - 1, ans_{mid}, vr)$ 以及 $solve(mid + 1, r, vl, ans_{mid})$。
- 对 $[vl, vr]$ 分治，令 $mid = \frac{vl + vr} 2$，依次加入所有权值 $\leq mid$ 的边直到合法，令第一个合法位置为 $pos$，则 $ans_{pos} \leq mid$，$ans_{pos - 1} > mid$。因此 $solve(l, pos - 1, mid + 1, vr)$ 以及 $solve(pos, r, vl, mid)$。

无论哪种方法，朴素实现均无法接受。注意到在 $solve(l, r, vl, vr)$ 的过程中，编号 $< l$ 且权值 $\leq vl$ 的边一定被考虑，因此尝试保证在 $solve(l, r, vl, vr)$ 调用时，所有 $\leq l$ 且权值 $\leq vl$ 的边已经加入并查集。

因为第一种方法需要二分求 $ans_{mid}$，比第二种方法多出一个 $\log$，故考虑第二种方法。

- 当 $solve(l, pos - 1, mid + 1, vr)$ 时，枚举所有权值在 $vl\sim mid + 1$ 之间的边，若编号 $< l$ 则加入并查集。最后回溯。
- 当 $solve(pos, r, vl, mid)$ 时，枚举所有编号在 $l\sim pos$ 之间的边，若权值 $\leq vl$ 则加入并查集。最后回溯。

- 注意，在按编号顺序加入权值 $\leq mid$ 的边之前，需要先将权值在 $vl\sim mid$ 之间的编号 $< l$ 的边加入并查集。

容易发现，单次 $solve$ 的复杂度和 $r - l$ 与权值在 $vl \sim vr$ 之间的边的数量相关。因为分治两个子树时编号与权值均分裂成两段区间，所以每层分治树的操作次数关于 $m$ 线性，再算上可持久化并查集的复杂度，总时间复杂度 $\mathcal{O}(m\log V\log n)$。对权值离散化可将 $\log V$ 变为 $\log m$。

即使没有 LCT 的理论复杂度优秀，但常数相当小且相当好写，在 CF 和洛谷上均获得最优解（2022.7.9）。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool Mbe;
constexpr int N = 3e5 + 5;
constexpr int inf = 0x3f3f3f3f;
int n, m, odd, stc[N], top;
int fa[N], sz[N], ans[N];
struct edge {
  int u, v, w, id;
  bool operator < (const edge &rhs) {
    return w < rhs.w;
  }
} e[N], g[N];
int find(int x) {return fa[x] == x ? x : find(fa[fa[fa[fa[x]]]]);} // 怎么可撤销并查集又路径压缩了！
void merge(int u, int v) {
  if((u = find(u)) == (v = find(v))) return;
  if(sz[u] < sz[v]) swap(u, v);
  if((sz[u] & 1) && (sz[v] & 1)) odd -= 2;
  sz[u] += sz[v], fa[v] = u, stc[++top] = v;
}
void undo(int lim) {
  while(top > lim) {
    int v = stc[top--], u = fa[v];
    fa[v] = v, sz[u] -= sz[v];
    if((sz[u] & 1) && (sz[v] & 1)) odd += 2;
  }
}
void solve(int l, int r, int vl, int vr) {
  if(l > r || vl > vr) return;
  if(vl == vr) {
    for(int p = l; p <= r; p++) ans[p] = g[vl].w;
    return;
  }
  int mid = vl + vr >> 1, ori = top;
  for(int p = vl; p <= mid; p++) if(g[p].id < l) merge(g[p].u, g[p].v);
  int found = r + 1, ori2 = top;
  for(int p = l; p <= r; p++) {
    if(e[p].w <= g[mid].w) merge(e[p].u, e[p].v);
    if(!odd) {found = p; break;}
  }
  undo(ori2);
  solve(l, found - 1, mid + 1, vr);
  undo(ori); // add this line
  for(int p = l; p < found; p++) if(e[p].w <= g[vl].w) merge(e[p].u, e[p].v); // vl -> g[vl].w
  solve(found, r, vl, mid);
  undo(ori);
}
bool Med;
int main() {
  fprintf(stderr, "%.4lf\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n >> m, odd = n;
  for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
  for(int i = 1; i <= m; i++) {
    cin >> e[i].u >> e[i].v >> e[i].w;
    e[i].id = i, g[i] = e[i];
  }
  sort(g + 1, g + m + 1);
  g[m + 1].w = -1;
  solve(1, m, 1, m + 1);
  for(int i = 1; i <= m; i++) cout << ans[i] << "\n";
  return cerr << "Time: " << clock() << "\n", 0;
}
/*
2022/7/9
start coding at 11:11
finish debugging at 19:18
*/
```

---

## 作者：lzk5627 (赞：6)

来发一发线段树分治的题解

首先对于限制条件进行分析,发现满足条件当且仅当连通块的大小为偶数

证明:

因为一条边导致总度数不会变,所以如果为奇数的话,最终的总度数为奇数,所以肯定连通块大小不为奇数

然后考虑如果是偶数怎么去构造,首先我们对于一个连通块可以随便找出一个生成树,从叶子节点开始考虑,如果当前节点的度数为偶数,那么就加上和父亲的边,这样的话最终就只有根节点的度数不能确定,但是总度数为偶数,就决定了根节点的度数也为偶数

解法:

首先要考虑只有一个询问的情况,就是从小往大加上边,直到所有连通块都是偶数大小位置.

考虑扩展开来,最暴力的想法就是用LCT暴力维护子树的大小,然后每次插入边的时候删除最大的边

从这个想法中,我们可以发现每条边的对答案的贡献是一个区间,我们可以从时间线往前做,所有从小往大加入每条边,直到最终的图满足条件,然后新加入的边的作用范围就是 最开始出现的时间到现在所处的时间

那么我们大概就是做这样一个事情

在线段树上遍历,每到达一个点把这个点上标记的边加到图中,可以用一个支持回退的并查集维护,然后优先遍历右儿子,再去遍历左儿子,遍历完子树之后就删除标记的边

每到达一个叶子节点,可以从小往大加边,直到图满足条件位置,这个可以用一个堆来维护,然后再把新加入的边往线段树上打标记,答案就是加入的边的最大值

感觉比LCT稍微好写一点吧,时间复杂度 O(mlog(m) log(n))

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;
	register char ch=getchar();
	while(ch<'0'||ch>'9')	ch=getchar();
	while(ch>='0'&&ch<='9')	x=x*10+(ch^48),ch=getchar();
	return x;
}
const int N=1e5+5;
const int M=3e5+5;
struct each{
	int x,y,z,t;
	bool operator < (const each k) const {
		return z>k.z;
	}
}a[M],st[N];
vector<each>b[M<<2];
priority_queue<each>que;
int n,m,top,cnt,fa[N],si[N],dep[N],ans[M];
inline int find(int x){
	while(fa[x])	x=fa[x];
	return x;
}
inline void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)	return ;
	cnt-=(si[x]&1)+(si[y]&1);
	if(dep[x]>dep[y])	swap(x,y);
	if(dep[x]==dep[y])	st[top].y=1,++dep[y];
	st[++top].x=x,fa[x]=y,si[y]+=si[x],cnt+=si[y]&1;
}
inline void del(each k){
	int x=k.x,y=fa[x];
	if(k.y)	dep[y]--;
	cnt-=si[y]&1,si[y]-=si[x];
	cnt+=(si[x]&1)+(si[y]&1),fa[x]=0;
}
void add(int l,int r,int x,int y,each z,int rt){
	if(x>y)	return ;
	if(x<=l&&y>=r){
		b[rt].push_back(z);
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid)	add(l,mid,x,y,z,rt<<1);
	if(y>mid)	add(++mid,r,x,y,z,rt<<1|1);
}
void dfs(int l,int r,int rt,int res){
	int tmp=top,si=b[rt].size();
	for(register int i=0;i<si;i++){
		merge(b[rt][i].x,b[rt][i].y);
		res=max(res,b[rt][i].z);
	}

	if(l==r){
		int num=0;
		while(cnt&&!que.empty()){
			each k=que.top();	que.pop();
			if(k.t<=l){
				merge(k.x,k.y),res=max(res,k.z);
				a[++num]=k;
			}
		}
		if(!cnt){
			for(register int i=1;i<=num;i++)
				add(1,m,a[i].t,l-1,a[i],1);
			ans[l]=res;
		}
		else	ans[l]=-1;
	}
	else{
		int mid=(l+r)>>1;
		dfs(mid+1,r,rt<<1|1,res),dfs(l,mid,rt<<1,res);
	}
	while(top!=tmp)	del(st[top--]);
}
int main(){
	n=read(),m=read();
	for(register int i=1;i<=n;i++)	si[i]=1;
	for(register int i=1;i<=m;i++){
		a[i].x=read(),a[i].y=read();
		a[i].z=read(),a[i].t=i,que.push(a[i]);
	}
	cnt=n,dfs(1,m,1,-1);
	for(register int i=1;i<=m;i++)	printf("%d\n",ans[i]);
	return 0;
}

```

---

## 作者：lgswdn_SA (赞：4)

正向推导一波。仅仅代表我的思考路径。可能有些繁琐。

首先考虑静态无权怎么判断合法。对于一棵树，我们从叶子结点开始往上推。叶节点的父边是必选的，然后再往上可以依次确定每个点的父边是否选择。这棵树是合法的当且仅当它的根节点的度数为奇数。

那我们对于一个连通图，取出其任意一棵生成树，跑这个流程。最终如果树是合法的，那么这个图就是合法的（其它边都不选就行了），并且方案是可以直接构造的。如果最终树是非法的，那必然这个树仅存在一个偶度点（根节点）。考虑加入一条非树边或者删除一条树边，发现无论这个边怎么连怎么删，都必然不会改变偶度点个数的奇偶性（要么偶度点个数加二，要么减二，要么不变）。也就是说，如果树是非法的，那么无论你怎么改，那都不可能是合法的。这样说明了一个连通块合法当且仅当偶度点个数为偶数。

更进一步，由于任意一张图的奇度点个数必然为偶数，所以一个连通块合法当且仅当其大小为偶数。**一个图合法当且仅当其所有连通块的大小都为偶数。**

---

对于动态的情况，我们使用一种有趣的分治方法。由于答案是递减的，我们可以我们以时间作为分治的关键字，然后同时也维护值域的答案区间。具体操作大概是：

对于一次分治（时间 $[l,r]$，值域 $[x,y]$）  
1. 把 $[l,r]$ 的时间区间中满足边的边权 $w_i<x$ 的边全部加入并查集
2. 取时间的中点 $mid$。我们把值域在 $[x,y]$ 且时间在 $[l,mid]$ 的边按值域从小到大加入并查集，直到合法。这相当于是使 $mid$ 合法的最小答案 $z$。
3. 由于答案是递减的，所以这个 $z$ 是 $[l,mid]$ 时间段的下界，且是 $[mid+1,r]$ 时间段的上界。分别继续分治两个时间段即可。
4. 在 2, 3（其中包括两次分治结束）后都要回到初始状态（即把这些操作全部都撤回掉）。

也有一种类似的整体二分做法，大概就是分治答案区间，去找最小合法时间，然后类似地递归下去。本质上没什么区别（因为答案和时间都是单调的），就不多赘述了。

复杂度：每一个分治区间的复杂度都是 $(C\times(r-l)+C\times(y-x))\log n$ 的，即一层的复杂度为 $O(m\log n)$，总复杂度 $O(m\log m\log n)$。

分治有不少的细节。需要很注意。  
还有别忘了离散化。这样分治在出现两个权值相同的边时可能会寄，需要在离散化时手动区分一下。

https://codeforces.com/contest/603/submission/167729346

---

## 作者：ღꦿ࿐ (赞：4)

题意翻译的很清楚，不再叙述。

有一个结论就是 “偶数度连通块是有解的充分必要条件” ，很多题解说的都是“调整法”，便于理解，但给出一个具体化的证明，如下：


答案是生森林是显然的，因为环一定可以从集合中删去使得答案更优

首先，奇数大小的连通块的边数为偶数，每条边对总度数的贡献是 2，而总度数等于 奇数 * 奇数 仍然为奇数，故是必要条件。

对于充分性，只要给出一组构造即可。

令 $S(x)$ 表示大小为 2x 的连通块。

对于大小为 0 的连通块 $S(0)$ 空集为解。

对于大小为 2 的连通块 $S(1)$ 有解，直接选择二点之间的边即有解。

对于 $S(x)$ 若 $S(p) (p\in \mathbb{N},p < x)$ 有解，则 $S(x)$ 有解。

，证明如下：

因为该连通块的大小是偶数，所以该连通块一定可以被划分成两个大小为偶数的连通块，或两个大小为奇数的连通块。

若该连通块可以被约化为 $S(x-p) , S(p) (0 < p < x)$  两边都有解。

若该连通块不能被划分成两个偶数大小的连通块，则任意选择一条边，将这条边加入边集，钦定这两个点不再被其他边连接，可以约化成 $S(x - 1 - p) , S(p) (0\leq p \leq x - 1) $ 。 

故 $S(x)$ 若 $S(p) (p\in \mathbb{N},p < x)$ 有解，则 $S(x)$ 有解。

由数学归纳法， $S(0)$ 有解，又因上定理，故偶数大小是成立的充分必要条件。

回到本题，已经解决静态问题了，考虑“加边”怎么处理。

将“加边”离线，然后由于答案是单调不降的，选的边只会越来越大，考虑倒着计算，将边按权值排序，先按顺序加入边直道答案成立（用一个指针从左向右加—），知道该边的起始时间的前一个时刻把这条边删了，继续加入边即可。

但是由于“删边”很难实现，又因为和图的连通性有关，于是考虑用一个[半在线的线段树分治](https://codeforces.com/problemset/problem/576/E)去维护它，记录奇数大小的连通块数，使用可撤销并查集，先遍历右儿子，遍历到叶节点就判断，并向前面区间加边即可。

一个坑点是不能在 $[tim , l]$ 直接连边（ $tim$ 表示这条边的出现时间， $l$ 表示目前分治到的时间点） 因为已经遍历到了这个叶子，可能导致上面的标记没有生效，应在 $[tim , l - 1]$ 连边。

线段树分治部分代码：

```cpp
/*uniset 表示合并 ， disset表示拆分 ，O记录操作以撤回 ， cnt表示目前奇数大小的连通块数*/
/*本人码风、缩进略怪，多多包涵*/
void solve(int x,int l,int r) {
    vector<Pair> O;
    for(int p : ed[x]) {
        int U = find(e[p].u) , V = find(e[p].v) ;
        if(U^V) {
            if(siz[U] < siz[V]) swap(U,V) ; 
            uniset(U,V); O.emplace_back(U,V);
        }
    }
    if(l == r) {
            while (cnt && ptr <= m) {
                if(e[ptr].tim <= l)
                {
                    int U = find(e[ptr].u) , V = find(e[ptr].v) ;
                    if(U^V) {
                        if(siz[U] < siz[V]) swap(U,V) ; 
                        uniset(U,V); O.emplace_back(U,V);
                    }
                    adde(1,1,m,e[ptr].tim,l - 1,ptr); /*坑点就是这里！！！*/
                }
            ptr ++ ;  
        }
        if(!cnt) ans[l] = e[ptr - 1].w; else ans[l] = -1 ;
    }
    else {
        int mid = l + r >> 1;
        solve(x<<1|1,mid+1,r);
        solve(x<<1,l,mid) ;
    }
    reverse(All(O)) ;
    for(auto[U,V]:O) disset(U,V) ;
}

```

[ACcode](https://www.luogu.com.cn/paste/vjpyqxmf) 

(有快读之类的东西，define极多，观感不佳，上方代码为方便阅读进行了缩进修改，删除了部分注释。)

如有笔误、逻辑错误欢迎轻喷。

感谢您的阅读，感谢管理员辛苦审核。

---

## 作者：yangchenxiao (赞：4)

~~来补一个比较正宗一点的整体二分做法吧~~

首先结论是所有连通块点数均为偶数的图是合法的，这一点其他题解已经给出了严谨的证明。   
观察到答案很明显是单调的，因此每次都可以二分实现，由于有多次询问，可以使用整体二分解决。    
加边限制有二，其一时间轴，其一值大小，恰好对应了两维操作、二分值，因此预处理两个边集分别按照时间、值域排序备用。   
~~正宗的整体二分是二分值域的~~    
$\mathop{solve}(lx,rx,l,r)$ 表示操作 $[lx,rx]$ 的答案是 $[l,r]$ 的边，设二分值 $\mathop{mid}=\frac{l+r}{2}$，然后去寻找操作的分界点。   
思想是从左到右一条一条加 $\le \mathop{mid}$ 的边，直到某个位置 $\mathop{pos}$ 使得图变成了合法的，那么此时就可以成功递归到 $(lx,pos-1,mid+1,r)$ 和 $(pos,rx,l,mid)$ 解决了。   
注意在每次枚举之前，都要保证所有 $\le mid$ 且 $<lx$ 的所有边都已经在集合里，那么根据二分的过程，可以手动使得进入函数前就处理好 $<l$ 的部分已经加入，此时再加入 $[l,mid]$ 的边。   
此时可以发现分治深度是 $\log n$ 的，且每层中都只枚举当前层长度的距离，总复杂度还是 $\mathcal{O}(n\log n)$ 的，然后再加上可撤销并查集的复杂度。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
const int maxn=3e5+5;
typedef pair<int,int>pi;
int n,m,ans[maxn],tp;
pi sta[maxn];
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct Edge{
	int x,y,w,id;
}edge[maxn],edge1[maxn];
struct DSU{
	int fa[maxn],siz[maxn],num;
	void init(int n){num=n;for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;}
	int find(int x){return fa[x]==x?x:find(fa[x]);}
	void merge(int x,int y){
		x=find(x),y=find(y);if(x==y)return ;
		if(siz[x]>siz[y])swap(x,y);
		num-=(siz[x]&1),num-=(siz[y]&1);
		fa[x]=y;siz[y]+=siz[x];sta[++tp]=mp(x,y);
		num+=(siz[y]&1);
		return ;
	}
	void undo(int last){
		while(tp>last){
			num-=(siz[sta[tp].se]&1);
			fa[sta[tp].fi]=sta[tp].fi,siz[sta[tp].se]-=siz[sta[tp].fi];
			num+=(siz[sta[tp].fi]&1);num+=(siz[sta[tp].se]&1);
			tp--;
		}
		return ;
	}
}t;
void solve(int lx,int rx,int l,int r){
	if(lx>rx)return ;
	int mid=l+r>>1,last=tp,pos=0;
	for(int i=l;i<=mid;i++)if(edge[i].id<lx)t.merge(edge[i].x,edge[i].y);
	for(int i=lx;i<=rx;i++){
		if(edge1[i].id<=mid)t.merge(edge1[i].x,edge1[i].y);
		if(!t.num){pos=i;break;}
	}
	t.undo(last);
	if(l==r){
		if(!pos)pos=rx+1;
		for(int i=pos;i<=rx;i++)ans[i]=edge[l].w;
		for(int i=lx;i<pos;i++)ans[i]=-1;
		return ;
	}
	if(!pos){
		last=tp;
		for(int i=l;i<=mid;i++)if(edge[i].id<lx)t.merge(edge[i].x,edge[i].y);
		solve(lx,rx,mid+1,r);t.undo(last);return ;
	}
	last=tp;
	for(int i=l;i<=mid;i++)if(edge[i].id<lx)t.merge(edge[i].x,edge[i].y);
	solve(lx,pos-1,mid+1,r);t.undo(last);
	last=tp;
	for(int i=lx;i<pos;i++)if(edge1[i].id<l)t.merge(edge1[i].x,edge1[i].y);
	solve(pos,rx,l,mid);t.undo(last);
	return ;
}
int main(){
	n=read(),m=read();t.init(n);
	for(int i=1;i<=m;i++)edge1[i]=edge[i]={read(),read(),read(),i};
	sort(edge+1,edge+m+1,[](Edge a,Edge b){return a.w<b.w;});
	for(int i=1;i<=m;i++)edge1[edge[i].id].id=i;
	solve(1,m,1,m);for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：_ZSR_ (赞：2)

### [ CF603E Pastoral Oddities](https://www.luogu.com.cn/problem/CF603E)

首先肯定是要想怎么判断存在一个边集使得所有点的度数都为奇数。最后满足条件的图一定是由若干个连通块组成，由于每一个连通块相互独立，因此单独考虑每一个连通块。如果一个连通块的点数为奇数，那么这个连通块的总度数也必然为奇数。如果一个连通块的点数为偶数，那么这个连通块的总度数也必然为偶数。然而每加一条边会使得总度数加二，因此满足条件的图一定是由若干个大小为偶数的连通块组成。

那么必要性我们就证明完了，那么对于大小为偶数的连通块，我们是否都可以构造出一个方案，使得每个点的度数为奇数。随便拿出这个连通块的一个生成树。对于叶节点，显然它们的度数为奇数。考虑叶节点以上的节点。如果某个非叶节点的点的儿子节点连向它的边的数量为偶数，那么保留它和它父亲的边，否则砍掉。那如果是根节点怎么办呢？它又没有父亲。其实，在保证除根节点以外的所有点都满足条件的前提下，根节点自然满足。证明还是用总度数证明。

接下来考虑怎么最小化最大边权。很直接的想法是直接把边权从小到大排序，每次加入一条边后判断是否每个连通块的大小都是偶数。如果是，那么当前加入的这条边就是答案。虽然这是静态的做法，但还是可以给我们不少启示。我们还是要先按边权从小到大排序。常规的线段树分治是预处理每条边出现和删除的时间，然后每次递归左边，再递归右边。既然所有边都加上之后更好做，那么我们考虑先递归右边。第一个遍历到的叶节点必然是 $m$。在 $m$ 我们做一遍静态的做法，这时选出来的所有边在最后都是最优的，那么意味着它们不会被删除，因此它们的删除时间为 $m$。这样我们就可以每次遍历到一个叶节点都做一遍此操作，然后更新新遍历到的边的出现和删除时间。

感觉最后一部分讲得有点抽象，具体看看代码理解吧。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=3e5+10;
int n,m,odd,top,pos;
struct Edge{
    int u,v,w,id;
    bool operator< (const Edge &t) const
    {
        return w<t.w;
    }
}edge[M];
int fa[N],size[N],ans[M];
struct Operation{
    int x,y,add,cut;
}stk[M];
struct Tree{
    int l,r;
    vector<int> appear;
}tr[M<<2];
int find(int x)
{
    return x==fa[x]?x:find(fa[x]);
}
inline void merge(int x,int y)
{
    x=find(x),y=find(y);
    if (x!=y)
    {
        if (size[x]>size[y]) swap(x,y);
        fa[x]=y;
        stk[++top]={x,y,size[x],0};
        if ((size[x]&1)&&(size[y]&1))
        {
            odd-=2;
            stk[top].cut+=2;
        }
        size[y]+=size[x];
    }
}
void build(int p,int inl,int inr)
{
    tr[p]={inl,inr};
    if (inl==inr) return;
    int mid=inl+inr>>1;
    build(p<<1,inl,mid);
    build(p<<1|1,mid+1,inr);
}
void modify(int p,int x,int y,int id)
{
    if (x<=tr[p].l&&tr[p].r<=y)
    {
        tr[p].appear.push_back(id);
        return;
    }
    int mid=tr[p].l+tr[p].r>>1;
    if (x<=mid) modify(p<<1,x,y,id);
    if (y>mid) modify(p<<1|1,x,y,id);
}
void solve(int p)
{
    int lasttop=top;
    for (auto i:tr[p].appear) merge(edge[i].u,edge[i].v);
    if (tr[p].l==tr[p].r)
    {
        while (true)
        {
            if (!odd||pos==m) break;
            if (edge[pos+1].id<=tr[p].l)
            {
                merge(edge[pos+1].u,edge[pos+1].v);
                if (edge[pos+1].id<tr[p].l) modify(1,edge[pos+1].id,tr[p].l-1,pos+1);
            }
            ++pos;
        }
        if (!odd) ans[tr[p].l]=edge[pos].w;
        else ans[tr[p].l]=-1;
    }
    else solve(p<<1|1),solve(p<<1);
    while (top>lasttop)
    {
        fa[stk[top].x]=stk[top].x;
        size[stk[top].y]-=stk[top].add;
        odd+=stk[top].cut;
        --top;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    odd=n;
    for (int i=1;i<=m;++i)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edge[i]={u,v,w,i};
    }
    sort(edge+1,edge+m+1);
    for (int i=1;i<=n;++i) fa[i]=i,size[i]=1;
    build(1,1,m);
    solve(1);
    for (int i=1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：liuzhangfeiabc (赞：2)

题目大意：给定无向图，初始为空，每次加入一条边，求选择若干条边，使得每个点度数均为奇数，且最大权值尽可能小。

首先我们不妨来看一些简化版的问题，比如：如果给定一张图，如何判断是否存在合法的边集？

每个连通块之间显然是独立的，我们分开讨论就好。

一个比较明显的结论是，一个大小为奇数的连通块是无解的。这是因为如果每个点的度数都是奇数，那么它们的度数和也是奇数，然而一个连通块的点度数和是2e一定是偶数。

那么一个大小为偶数的连通块是否一定有解呢？答案是肯定的。只需要对原图求一棵dfs树，然后从叶子开始贪心，每个点根据其连向儿子的度数决定其连向父亲的边是否选即可。

所以，一个图有解当且仅当其每个连通块大小都是偶数。

再把边权的限制加上。假设给定一张图，如何求最大权值尽可能小的合法边集？

这也很简单。像kruskal那样按照边权升序加入边，维护每个连通块的大小，直到所有连通块大小均为偶数即可。

那如何处理动态加边呢？

容易发现加边会使得答案逐渐变小，而我们的上述操作是按照从小到大的顺序枚举答案，这会非常不和谐。

那不妨把操作反过来（时光倒流大法好），变成每次删边求答案。

假设我们已经对一开始的图求好了答案，现在删掉了一条边，这可能使得一个偶数连通块分裂成了两个奇数连通块。此时我们要从上次的位置继续按边权顺序加边，直到图重新变成全偶数连通块为止。

这就是一个经典的加边删边维护连通性的动态图问题。由于每条边的删除时间已知，我们可以用lct维护最大删除时间生成树，同时用简单的维护子树信息的方法维护连通块大小的奇偶性。

（什么你不会lct？出门右转模板区。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar()
#define pc putchar
#define li long long
inline li read(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = (x << 1) + (x << 3) + (c ^ '0'),c = gc;
	return y == '-' ? -x : x;
}
inline void print(li q){
	if(q < 0) pc('-'),q = -q;
	if(q >= 10) print(q / 10);
	pc(q % 10 + '0');
}
int n,m;
int f[400010],l[400010],r[400010],mx[400010];
bool c[400010],sz[400010],zs[400010];
struct edge{
	int u,v,w;
}e[300010];
int ee[300010],ans[300010];
inline bool cmp(int q,int w){
	return e[q].w < e[w].w;
}
inline bool is(int q){
	return l[f[q]] != q && r[f[q]] != q;
}
inline void ud(int q){
	sz[q] = sz[l[q]] ^ sz[r[q]] ^ zs[q];
	mx[q] = max(max(mx[l[q]],mx[r[q]]),q <= n ? 0 : q);
}
inline void rv(int q){
	c[q] ^= 1;swap(l[q],r[q]);
}
inline void ps(int q){
	if(!c[q]) return;
	if(l[q]) rv(l[q]);
	if(r[q]) rv(r[q]);
	c[q] = 0;
}
inline void ro(int q){
	int p = f[q];
	if(l[f[p]] == p) l[f[p]] = q;
	else if(r[f[p]] == p) r[f[p]] = q;
	f[q] = f[p];f[p] = q;
	if(l[p] == q){
		l[p] = r[q];r[q] = p;
		if(l[p]) f[l[p]] = p;
	}
	else{
		r[p] = l[q];l[q] = p;
		if(r[p]) f[r[p]] = p; 
	}
	ud(p);ud(q);
}
inline void gx(int q){
	if(!is(q)) gx(f[q]);
	ps(q);
}
inline void sp(int q){
	gx(q);
	while(!is(q)){
		int p = f[q];
		if(!is(p)){
			if((l[f[p]] == p) ^ (l[p] == q)) ro(q);
			else ro(p);
		}
		ro(q);
	}
}
inline void ac(int q){
	int p = 0;
	while(q){
		sp(q);
		zs[q] ^= sz[r[q]];
		r[q] = p;
		zs[q] ^= sz[r[q]];
		ud(q);
		p = q;
		q = f[q];
	}
}
inline void mk(int q){
	ac(q);sp(q);rv(q);
}
inline void si(int u,int v){
	mk(u);ac(v);sp(v);
}
int main(){
	int i,j,u,v,w;
	n = read();m = read();
	if(n & 1){
		for(i = 1;i <= m;++i) puts("-1");
		return 0;
	}
	for(i = 1;i <= m;++i){
		e[i].u = read();e[i].v = read();e[i].w = read();ee[i] = i;
	}
	sort(ee + 1,ee + m + 1,cmp);
	for(i = 1;i <= n;++i) sz[i] = zs[i] = 1,mx[i] = 0;
	for(i = 1;i <= m;++i) mx[i + n] = i + n;
	int nw = n;
	for(i = m,j = 1;i;--i){
		for(;j <= m && nw;++j){
			if(ee[j] > i) continue;
			w = ee[j] + n;u = e[w - n].u;v = e[w - n].v;
			si(u,v);
			if(f[u]){
				if(mx[v] <= w) continue;
				w = mx[v];u = e[w - n].u;v = e[w - n].v;
				si(u,v);sp(w);l[w] = r[w] = f[u] = f[v] = sz[w] = zs[w] = 0;
				w = ee[j] + n;u = e[w - n].u;v = e[w - n].v;
				mk(u);mk(v);f[u] = f[v] = w;sz[w] = zs[w] = sz[u] ^ sz[v];
			}
			else{
				rv(v);f[u] = f[v] = w;sz[w] = zs[w] = sz[u] ^ sz[v];
				if(sz[u] && sz[v]) nw -= 2;
			}
		}
		if(j > m && nw) ans[i] = -1;
		else{
			ans[i] = e[ee[j - 1]].w;
			w = i + n;u = e[i].u;v = e[i].v;
			si(u,v);sp(w);
			if(!f[v]) continue;
			l[w] = r[w] = f[u] = f[v] = sz[w] = zs[w] = 0;
			if(sz[u] && sz[v]) nw += 2;
		}
	}
	for(i = 1;i <= m;++i) print(ans[i]),pc('\n');
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：2)

（哦我写这个题解的时候luogu好像没法交CF了……不过这个在CF上确实A了……）

首先你一个大致的思路就是，每次暴力把边排序然后依次加入判断是否能够构成一个合法的方案。然后我们要做的就是判定其合法性。

然后~~经过多次手玩~~发现加入一条两端都在同一个连通块的边（也就是非树边）是对合法性没有用的（至于为啥这个我并不能证明……）。然后这样的话你就只需要考虑其生成树或者说是生成森林，那么我们可以从其叶子入手，不妨先确定一个根，然后叶子的度数必须是1他必须选他的父亲边，我们从这里入手，就这样dfs一遍，发现一个点度数为偶数的时候就选上他父亲边，为奇数的时候不用选也不能选父亲边，最后判断根的度数即可，所以不管选哪个根方法都是唯一的。

然后我们接着手玩发现一个更强的结论：**如果存在size为奇数的连通块，就无解。**

这个可以用上面的那个结论归纳证明：如果这个连通块只有1个点，显然无解，如果这个连通块是2个点连起来的显然有解，那么，我现在要合并两个偶连通块，合并完还是偶连通块是有解的。一个奇连通块可以看做在一个偶连通块上加了个叶子，由于偶连通块已经有解但是加了个叶子之后会自底往上改变奇偶性，就无解了，而合并奇连通块相当于合并两个偶连通块再加2个叶子，改变了两次奇偶性相当于没变，所以这结论成立。~~（感觉我好像在口胡啊……）~~

于是我们现在就可以做到$O(m^2logm)$的暴力了，但是这东西好像就是在做一个最小生成树或者叫最小生成森林，如果要动态维护的话，能不能直接用$LCT$呢？

哦然后你写了一个LCT维护最小生成树之后发现连样例1都过不去，因为你暴力的过程是如果加完这条边之后连通块全部都是偶的（显然之后再加边不可能又出来奇的……）就停止加边，这条边就是最小的最大值，所以你最小生成森林上的一些大树边是没有用的。

那么我可以这么干：每次我维护完生成森林之后，我从大到小考虑每条已经加入的边，如果删掉它之后没有产生奇连通块，就删掉，否则停止删边。为啥这个是对的呢？如果你最大的边比答案大的话，那么假如答案的那条边之后加的边连的就都是偶连通块，所以删去一定不会产生奇连通块。

于是我们就在LCT上维护一下子树实际的size，再开个大根堆维护加进来的边，就好了。注意替换树边的时候要删掉已经加进来的一条树边，这个用个懒惰删除堆。

哦对了这里分享一个小细节，比如你要是用结构体存边的话不能只在自定义的$<$运算符里比较大小，如果大小相同的话还要以编号为第二关键字，这样防止这两条已经懒惰删除的边在两个堆中相对大小不一样导致没法及时弹出去就出锅了……这个调了我好久……

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define isroot(_o) (_o!=ch[fa[_o]][0]&&_o!=ch[fa[_o]][1])
#define opp(_o) (_o==ch[fa[_o]][1])
using namespace std;
namespace ywy{
	void print(int num){
		if(num>=10)print(num/10);putchar(num%10+'0');
	}
	int fa[400001],minpos[400001],val[400001],ch[400001][2],size[400001];
	int stk[400001];
	unsigned char bj[400001];
	int sz[400001];
	inline void up(int tree){
		size[tree]=size[ch[tree][0]]+size[ch[tree][1]]+sz[tree];
		minpos[tree]=tree;
		int minn=val[tree];
		if(val[minpos[ch[tree][0]]]>minn)minn=val[minpos[ch[tree][0]]],minpos[tree]=minpos[ch[tree][0]];
		if(val[minpos[ch[tree][1]]]>minn)minn=val[minpos[ch[tree][1]]],minpos[tree]=minpos[ch[tree][1]];
	}
	inline void down(int tree){
		if(bj[tree])bj[tree]=0,swap(ch[tree][0],ch[tree][1]),bj[ch[tree][0]]^=1,bj[ch[tree][1]]^=1;
	}
	inline void xuan(int me){
        int tree=fa[me],cjr=fa[tree];
		down(cjr);down(tree);down(me);
		int op=opp(me),ls=ch[me][op^1];
        ch[me][op^1]=tree;ch[tree][op]=ls;fa[ls]=tree;
		if(!isroot(tree))ch[cjr][opp(tree)]=me;
        fa[tree]=me;fa[me]=cjr;up(tree);up(me);
    }
    inline void splay(int tree){
        if(isroot(tree)){down(tree);return;}
		int sp=0,tmp=tree;
		while(!isroot(tmp))stk[sp]=tmp,sp++,tmp=fa[tmp];
        stk[sp]=tmp;sp++;
		while(sp)sp--,down(stk[sp]);
		while(!isroot(tree)){
            int cjr=fa[tree];
			if(!isroot(cjr))xuan((opp(cjr)==opp(tree))?cjr:tree);
			xuan(tree);
        }
		up(tree);
    }
    inline void access(int tree){
        splay(tree);down(tree);
		sz[tree]+=size[ch[tree][1]];
		ch[tree][1]=0;up(tree);while(fa[tree]){
            int cjr=fa[tree];splay(cjr);down(cjr);
			sz[cjr]-=size[tree];
			sz[cjr]+=size[ch[cjr][1]];
            ch[cjr][1]=tree;
			up(cjr);splay(tree);
        }
		up(tree);
    }
	inline void makeroot(int tree){
		access(tree);
		splay(tree);bj[tree]^=1;
	}
	inline void link(int a,int b){
		makeroot(a);makeroot(b);
		sz[a]+=size[b];fa[b]=a;up(a);
	}
	inline void cut(int a,int b){
		makeroot(a);access(b);
		splay(a);down(a);
		ch[a][1]=fa[b]=0;up(a);
	}
	inline int findroot(int tree){
		access(tree);splay(tree);down(tree);
		while(ch[tree][0])tree=ch[tree][0],down(tree);
		splay(tree);return(tree);
	}
	typedef struct _b{
		int s;int t;int l;
		friend bool operator <(const _b &a,const _b &b){
			return(a.l<b.l);
		}
	}bian;
	bian memchi[300001];
	int gnn=1;
	int ss[400001],ts[400001];
	typedef struct _n{
		int l;int pt;
		friend bool operator <(const _n &a,const _n &b){
			if(a.l==b.l)return(a.pt<b.pt);
			return(a.l<b.l);
		}
		friend bool operator ==(const _n &a,const _n &b){
			return(a.pt==b.pt);
		}
	}node;
	priority_queue<node> que,del;
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	void ywymain(){
		int n=get(),m=get();
		for(register int i=1;i<=n;i++){
			sz[i]=size[i]=1;minpos[i]=i;
		}
		if(n&1){
			for(register int i=1;i<=m;i++)printf("-1\n");return;
		}
		int cnt=n;int gnn=n+1;
		while(m){
			m--;
			int s=get(),t=get(),l=get();
			int aa=findroot(s),ab=findroot(t);
			if(aa!=ab){
				if(size[aa]&1)cnt--;
				if(size[ab]&1)cnt--;
				if((size[ab]+size[aa])&1)cnt++;
				int me=gnn;gnn++;
				node cjr;cjr.pt=me;
				cjr.l=l;que.push(cjr);
				ss[me]=s;ts[me]=t;val[me]=l;
				minpos[me]=me;
				link(me,s);link(me,t);
			}else{
				makeroot(s);access(t);splay(t);
				if(val[minpos[t]]>l){
					int dst=minpos[t];
					node cjr;cjr.pt=dst;cjr.l=val[dst];
					del.push(cjr);
					cut(ss[dst],dst);cut(ts[dst],dst);
					int me=gnn;gnn++;
					ss[me]=s;ts[me]=t;val[me]=l;
					minpos[me]=me;
					link(me,s);link(me,t);
					cjr.pt=me;cjr.l=l;
					que.push(cjr);
				}
			}
			if(cnt){
				printf("-1\n");
			}else{
				while(1){
					while(!que.empty()&&!del.empty()&&que.top()==del.top())que.pop(),del.pop();
					int pt=que.top().pt;
					makeroot(pt);access(ss[pt]);splay(ss[pt]);
					if(sz[ss[pt]]&1)break;
					cut(ss[pt],pt);cut(ts[pt],pt);
					que.pop();
				}
				print(que.top().l);
				putchar('\n');
			}
		}
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF603E)

[CF](https://codeforces.com/problemset/problem/603/E)

### 写在前面

第九道黑题！

Codeforces 上少有的经典数据结构题。

题意已经很精简了，不再赘述。

### 分析

首先，注意到“每个店的度数都是奇数”这个限制条件是很难考虑的，必须转化掉。

考虑加边的奇度数的点的数量变化，加入边 $(u,v)$，则：

+ 当 $u$ 和 $v$ 的度数一奇一偶时，奇度数的点的数量不变。

+ 当 $u$ 和 $v$ 的度数都为偶时，奇度数的点的数量加二。

+ 当 $u$ 和 $v$ 的度数都为奇时，奇度数的点的数量减二。

已知没有变的时候奇度数的点的数量为零，奇度数的点的数量必然为偶数。

所以，当连通块的大小为奇数时，每个点的度数都是奇数，那么总度数也是奇数，矛盾，即连通块的大小只能为偶数。

此时我们应该思考的是，连通块的大小为偶数时就必然成立吗？

可以想到一种构造方法，先抽出一颗生成树，从叶节点开始，如果度数为偶数就连向父亲，否则不连，最后，根的度数也一定是奇数。

所以，我们最终证明了，**每个点的度数均为奇数等价于每个连通块的大小均为偶数**。

既然要让最大边权最小，那就按照边权从小到大排序，同时记录一下其初始位置。

然后进行线段树分治，注意为了边覆盖的时效性，应当从大到小地进行分治。

在叶子结点的时候，对于初始位置小于叶子的加入，覆盖它之后的范围，直到满足条件为止。当然，如果全部加入了仍不满足，根据题意，答案存下 $-1$ 即可。

注意在跳出节点时应撤销加入的边不干扰后续操作。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1;
	x = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
int n,m;
struct Seg
{
	#define M 300010
	#define N 100010
	#define mid (l+r)/2
	#define ls u<<1
	#define rs u<<1|1
	struct node
	{
		int u,v,w,id;
		inline bool friend operator<(const node &X,const node &Y) {return X.w < Y.w;}
	}e[M];
	vector<pii> g[M<<2];
	int ans[M],now;
	Seg() {now = 0;}
	struct union_find
	{
		int f[N],sz[N],sum;
		stack<node> s;
		inline void init()
		{
			F(i,1,n) f[i] = i,sz[i] = 1;
			sum = n;
		}
		inline int find(int u)
		{
			while(u != f[u]) u = f[u];
			return u; 
		}
		inline int merge(int u,int v)
		{
			u = find(u),v = find(v);
			if(u == v) return 0;
			if(sz[u] < sz[v]) swap(u,v);
			if((sz[u]&1)&&(sz[v]&1)) s.push((node){u,v,2,0}),sum -= 2;
			else s.push((node){u,v,0,0});
			sz[u] += sz[v];
			f[v] = u;
			return 1;
		}
		inline void erase(int u,int v,int w)
		{
			sz[u] -= sz[v];
			f[v] = v;
			sum += w;	
		}
		inline void erase(int len)
		{
			if(!len) return;
			while(len--)
			{
				erase(s.top().u,s.top().v,s.top().w);
				s.pop();
			}
		}
	}tree;
	void update(int u,int l,int r,int x,int y,pii p)
	{
		if(x <= l&&r <= y) 
		{
			g[u].push_back(p);
			return;
		}
		if(x <= mid) update(ls,l,mid,x,y,p);
		if(y > mid) update(rs,mid+1,r,x,y,p);
	}
	void solve(int u,int l,int r)
	{
		int cnt = 0;
		for(auto p:g[u]) cnt += tree.merge(p.first,p.second);
		if(l == r)
		{
			while(tree.sum&&now < m)
			{
				++now;
				if(e[now].id <= l)
				{
					cnt += tree.merge(e[now].u,e[now].v);
					if(e[now].id < l) update(1,1,m,e[now].id,l-1,(pii){e[now].u,e[now].v});	
				}	
			}	
			if(tree.sum) ans[l] = -1;
			else ans[l] = e[now].w;
		}
		else
		{
			solve(rs,mid+1,r);
			solve(ls,l,mid);
		}
		tree.erase(cnt);
		return;	
	}
	inline void init()
	{
		read(n),read(m);
		F(i,1,m) read(e[i].u),read(e[i].v),read(e[i].w),e[i].id = i;
		sort(&e[1],&e[m+1]);
		tree.init();
		solve(1,1,m); 
		F(i,1,m) write(ans[i]),putchar('\n');	
	}
}tree;
int main()
{
	tree.init();
	return 0;
}
```


---

## 作者：pldzy (赞：1)

[CF 传送门：CF603E](https://codeforces.com/problemset/problem/603/e)

整体二分 + 可撤销并查集。

（这个方法是个人认为较简单的，除外还有[LCT 维护](https://www.luogu.com.cn/blog/xht37/solution-cf603e)、[线段树分治](https://www.luogu.com.cn/blog/shan-cheng/solution-cf603e)的做法。）

~~考场上苦想正解觉得自己写得出来的我真的太 naive 了~~

## Solution

### Part 1 每个点的度数均为奇数

不妨称度数为奇数的点为奇点，为偶数称偶点。

逐一考虑题目限制条件。显然先从“每个点为奇点”考虑，因为它相对特殊。

先扔出一个很重要的结论：一个连通图内所有点为奇点，等价于该连通图内有偶数个节点。证明如下：

- **必要性**：考场上阿巴出“若某连通图内的每个点都为奇点，则该图中点数必定为奇数”。

	这个性质的证明不难，~~手玩小样例即可~~，形象地说，奇点必定是成双成对出现的，若想要一个偶点变为奇点，必须同时让另一个偶点变为奇点（或者重新构造出一个点）。自己画画图构造一下很容易就能得出。

- **充分性**：对于一个有偶数个节点的连通图，我们可以在它任意一种形态的生成树上构造出“所有点为奇点”的局面。

	具体地，从底向上遍历每一个节点，如果这个节点儿子连上来的边数为偶数，就连上他与父亲的边，反之则不然。对于根节点，因为其子树内其他节点的度数之和为 奇数 x 奇数 = 奇数，而度数总和为偶数，所以根节点的度数也为奇数。
    
结合这个结论和其充分性证明中的构造方式，可以发现：对于一个连通图，只要添上某一条边之后，它的点数变为偶数，那这条边就是这个边集中的最大边权。进一步地，想要把这个图真真切切构造成一个“所有点都为奇点”的情况，需要在图中删边，但是删的边一定不会是这条最大权的边。

由此，明白：既然我们只是要求“最小化边集中的最大边权”，那这个连通图内部如何删边我们其实毫不关心，只需要明白有这个操作，但是代码实现中无需写出，**要想找到“最小化边集中的最大边权”，只需要看在加入哪条边之后总点数变为偶数即可**。直白地说，对合法的边，能加就加。

### Part 2 最小化边集中的最大边权

然后来考虑“最小化边集中的最大边权”这个限制条件。条件反射肯定就想到二分答案的做法，但是本题是动态加边，复杂度不允许每次加边后都来一次二分，故引导我们去考虑整体二分的做法。进一步地，为了保证能够使用整体二分，考虑证明最终答案的单调性。这个通过~~观察样例输出~~简单思考发现答案一定是单调不下降的。

按照整体二分的套路来，函数 `solve(ql, qr, vl, vr)` 表示现在处理在 $[ql,qr]$ 之间的询问，且它们的答案都是边按照权值从小到大排序之后，位于 $[vl,vr]$ 之中的某边的边权。（使用 $e$ 数组按输入顺序存放边，$b$ 数组按权值从小到大存放边。）

按照之前的推论，我们根本不关心连通块内部怎么删边，故要先确保在 $e$ 中编号小于 $ql$、$w$ 中编号小于 $vl$ 的边都先加入。为了继续二分处理询问，设 $mid=\frac{vl+vr}{2}$，我们就需要求出在询问 $[ql,qr]$，中，哪个询问的答案是 $b_{mid}.w$，记此答案为 $Ans$。若求出了 $Ans$，那么接下来要递归的两个函数的分别是 `solve(ql, Ans - 1, mid + 1, vr)` 和 `solve(Ans, qr, vl, mid)`，即分别递归左子区间和右子区间。

### Part 3 加边

再回过头考虑加边细节：

1. 为求解 $Ans$ 加边：我们首先肯定要保证 $e$ 中编号小于 $ql$ 的边且 $w$ 中编号小于 $mid$ 的边都必须得加入，这是根据能加就加的原则。然后再从 $e_{ql}$ 遍历到 $e_{qr}$，依次加入这些边，直到加入某条边之后整个图中没有一个内部点数为奇数的连通块，则这条边就是 $Ans$。
2. 为递归 `solve(ql, Ans - 1, mid + 1, vr)` 加边：显然，为了不妨碍下一个递归函数，我们只需要在递归这个函数之前加入 $e$ 中编号小于 $ql$ 的边且 $w$ 中编号小于 $mid$ 的边。
3. 为递归 `solve(Ans, qr, vl, mid)` 加边：同理，此时要先加入  $e$ 中编号在 $[ql, Ans)$ 的边且其边权小于 $b_{vl}.w$ 的边。

综上，我们可以发现：

1. 我们想维护连通块内的节点数；
2. 每次递归函数中，上述三个加边步骤有所重复（比如第一步的前半部分和第二步）；
3. 我们想尽可能节省空间。

这三条（或者更多）指向了我们维护这些边、连通块所使用的工具：可撤销并查集。

为什么要“可撤销”？发现第一步加边之后，要想执行第二步加边操作，只需要撤销掉第一步后半部分的加边操作即可，无需重新加边（显然，撤销比初始化再重新加边要方便的多）。

嗯，然后这道题就结束了。

简单提一嘴可撤销并查集，它其实就是在并查集的基础上，不路径压缩，然后再开个栈存放每次合并的两个根节点，便于撤销即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(register int i = a; i <= b; ++i)
const int maxn = 3e5 + 5;
int n, m, num;
int fa[maxn], sz[maxn], stk[maxn], tot, ans[maxn];
struct node{
    int u, v, w, id;
}e[maxn], b[maxn];
bool operator <(const node &a, const node &b){
    return a.w < b.w;
}
 
inline int fnd(int x){
    return x == fa[x] ? x : fnd(fa[x]);
}
 
inline void erase(int lmt){
    while(tot > lmt){
        int v = stk[tot--], u = fa[v];
        fa[v] = v, sz[u] -= sz[v];
        if((sz[u] & 1) and (sz[v] & 1)) num += 2; 
    }
}
 
inline void merge(int x, int y){
    x = fnd(x), y = fnd(y);
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);
    if((sz[x] & 1) and (sz[y] & 1)) num -= 2;
    sz[x] += sz[y], fa[y] = x, stk[++tot] = y;
}
 
inline void slv(int ql, int qr, int vl, int vr){
    if(ql > qr or vr < vl) return;
    if(vl == vr){
        rep(i, ql, qr) ans[i] = b[vl].w; return;
    } int mid = vl + vr >> 1, nw = tot;
    rep(i, vl, mid) if(b[i].id < ql) merge(b[i].u, b[i].v);//加入之前的边 
    int Ans = qr + 1, nw2 = tot;
    rep(i, ql, qr){
        if(e[i].w <= b[mid].w) merge(e[i].u, e[i].v);
        if(!num){Ans = i; break;}//找到 ans[mid] 
    } erase(nw2), slv(ql, Ans - 1, mid + 1, vr), erase(nw);//递归左子区间 
    rep(i, ql, Ans - 1) if(e[i].w <= b[vl].w) merge(e[i].u, e[i].v);//添加满足限制的边 
    slv(Ans, qr, vl, mid), erase(nw); //递归右子区间 
} 
 
int main(){
    scanf("%d%d", &n, &m), num = n;
    rep(i, 1, n) sz[i] = 1, fa[i] = i;
    rep(i, 1, m) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w), e[i].id = i, b[i] = e[i];
    sort(b + 1, b + m + 1), b[m + 1].w = -1;
    slv(1, m, 1, m + 1); rep(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
```


------------
感谢阅读。

---

## 作者：juju527 (赞：1)

### $\texttt{Solution}$
这里给出DFS树经典方法对于此题结论的一个证明

随意取点集的一个DFS生成森林，钦定选所有非树边

从叶子开始用父亲边调整节点度数，容易发现除根外所有点均能被调整到奇度

当调整法做完后，我们发现根的度数已经确定，什么时候根的度数为奇数呢？

考虑一条边使得整个图的度数加2，图总度数一定为偶数

显然每个连通块独立，记某个连通块点数为 $n$

除根外点度数和奇偶性为 $n-1$,则当 $n-1$ 为奇数时根节点所选度数一定为奇数

故“存在一个边集，满足每个点的度数均为奇数”等价于“不存在奇数个点的连通块”

进一步发现加入一条边答案一定不劣

这是因为对于两个连通块的合并：奇加奇为偶，偶加偶为偶，奇加偶为奇

分治计算即可

[code](https://www.luogu.com.cn/paste/f4ghnb6o)

---

## 作者：关怀他人 (赞：1)

### CF 603E
#### Solution
首先，存在一个边集使得所有点度数为奇数的充要条件是每个连通块都有偶数个点。

必要性，因为一条边提供的度为$2$，所以一个连通块总度数必然为偶数，显然不可能出现点数为奇数且度数全为奇数的情况。

充分性，考虑对于每个连通块任取一棵生成树，自底往上考虑每个点是否保留到它父亲的边，这样除了根之外每个点的度数都必然为奇数，而由于总度数为奇数，所以根的度数显然也为奇数。

不难发现，如果加入了一条小于答案的边，那么无论如何答案都不会变大，所以可以用一个类似 kruskal 的方法，从小到大加边直到不存在度数为奇数的连通块为止，此时的最后一条边的边权就是答案了，这个过程可以用并查集维护。

而对于每个点都要计算答案，可以考虑整体二分，将权值离散化之后，设$solve(l,r,x,y)$表示考虑$[l,r]$之间的边且答案为$[x,y]$的情况，首先将$[l,mid]$之间所有权值小于$x$的边加入，然后再将权值在$[x,y]$之间且编号小于$mid$的边加入直到不存在度为奇数的点，此时的边权就是$mid$的答案了。

+ 如果一直存在度为奇数的点，那么说明编号在$[l,mid]$中的边答案都为$-1$，然后递归处理$solve(mid+1,r,x,y)$即可。

+ 如果找到了$mid$的答案，那么考虑递归分治。往右递归递归$solve(mid+1,r,x,ans[mid])$时需要将$[l,mid]$中小于$x$的边加入并查集，往左递归$solve(l,mid-1,ans[mid],y)$时需要将$[x,ansmid−1]$中小于$l$的边加入并查集。

由于要支持撤销操作，使用按秩合并的可撤销并查集即可。

由于每条边最多被加入$\mathcal O(\log m)$次，每次加入的复杂度为$\mathcal O(\log n)$，所以复杂度为$\mathcal O(m\log m\log n)$

#### Code
```cpp
int n,m;
int ans[MAXN];

struct Edges{
    int u,v,w,id;
} p[MAXN],q[MAXN];

struct DSU{
    int num,top;
    int fa[MAXN],size[MAXN];
    pii stk[MAXN];

    void init(int n) {num = n; for(int i = 1;i <= n;i++) fa[i] = i, size[i] = 1;}
    int find(int x) {return x == fa[x] ? x : find(fa[x]);}

    void merge(int x,int y){
        x = find(x); y = find(y);
        if(x == y) return;
        if(size[x] < size[y]) swap(x,y);
        num -= (size[x] & 1) + (size[y] & 1);
        fa[y] = x; size[x] += size[y]; num += (size[x] & 1);
        stk[++top] = make_pair(x,y);
    }

    void undo(){
        int x = stk[top].first, y = stk[top].second; top -= 1;
        num -= (size[x] & 1); size[x] -= size[y];
        fa[y] = y; num += (size[x] & 1) + (size[y] & 1); 
    }
} dsu;

void solve(int l,int r,int x,int y){
    if(l > r) return;
    int mid = (l + r) >> 1, lst = dsu.top, ansmid = -1;
    for(int i = l;i <= mid;i++)
        if(q[i].id < x) dsu.merge(q[i].u,q[i].v);
    for(int i = x;i <= y;i++){
        if(p[i].id <= mid) dsu.merge(p[i].u,p[i].v);
        if(dsu.num == 0) {ansmid = i; break;}
    }
    while(dsu.top > lst) dsu.undo();
    if(ansmid == -1){
        for(int i = l;i <= mid;i++) ans[i] = -1;
        for(int i = l;i <= mid;i++)
            if(q[i].id < x) dsu.merge(q[i].u,q[i].v);
        solve(mid + 1,r,x,y); 
        while(dsu.top > lst) dsu.undo(); return; 
    }
    ans[mid] = p[ansmid].w;
    for(int i = l;i <= mid;i++)
        if(q[i].id < x) dsu.merge(q[i].u,q[i].v);
    solve(mid + 1,r,x,ansmid); while(dsu.top > lst) dsu.undo();
    for(int i = x;i <= ansmid;i++)
        if(p[i].id < l) dsu.merge(p[i].u,p[i].v);
    solve(l,mid - 1,ansmid,y); while(dsu.top > lst) dsu.undo();
}

int main(){
    scanf("%d%d",&n,&m); dsu.init(n);
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&q[i].u,&q[i].v,&q[i].w);
        p[i] = q[i]; p[i].id = i;
    }
    sort(p + 1,p + 1 + m,[&](const Edges &x,const Edges &y) {return x.w < y.w;});
    for(int i = 1;i <= m;i++) q[p[i].id].id = i;
    solve(1,m,1,m);
    for(int i = 1;i <= m;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：541forever (赞：0)

我们首先需要观察出一个性质，就是当图中的连通块的点数均为偶数时，一定能选出一个边集使得所有点的度数均为基数。而如果问题是静态的，最小化最大的一条边则让我们想到如 Kruskal 一样从小到大加边，能加就加，一直到所有连通块的点数均为偶数为止。这么做是因为加入一条边不会使点数为奇数的联通块增多，而我们只关心最大的那条边多大。

然后这个东西看上去就不太能支持动态加任意边权的边，因为这会影响到大量边权的边。正难则反，我们可以发现，每条边出现在边集内的时间一定是一个区间，于是不妨利用线段树分治从后往前加边，先将所有边按边权排序，然后再从后往前处理，先将挂在当前节点的 tag 插入，然后再在全局维护一个指针能加边就加边直到在当前节点状态下不再有点数为奇数的连通块或该指针已遍历完所有的边，同时将这些加进去的边在其对应的时间区间打上 tag，并在每个节点处理完时撤销加入的这些边。这样我们可以发现每条边都只被遍历一次并插入线段树一次，时空复杂度十分正确。

[Code](https://codeforces.com/contest/603/submission/211118417)

---

## 作者：orz_z (赞：0)

### CF603E Pastoral Oddities

存在这样满足每个点的度数均为奇数的边集，充分条件是连通块的点数为偶数。 

先考虑必要性，加入一边度数和增加 $2$ 故度数和为偶数，而当满足条件的连通块点数为奇时，度数和必为奇数，矛盾。

证明充分性：对于一个偶数大小的连通块，找出其一棵生成树，从叶子开始根据连向儿子的度数考虑是否添加其到父亲的边，逐步满足，最后除了根之外都满足条件，显然根据奇偶性根也满足条件，故充分性保证。

故用一个按秩合并并查集即可维护连通块是否满足条件。

再考虑边集中的最大边权最小的限制，一棵最小生成树足矣。

在线 `LCT` 维护最小生成树森林，时间复杂度 $\mathcal O(n\log n)$。

但非常难写且常数巨大，考虑离线做法。

观察样例得知，时间升序，答案单调递减；还有“最大值最小”一类的词，考虑二分。

多次询问，考虑整体二分。

具体地，离散化权值，再对权值分治，令其为 $mid$。

添加权值 $\leq mid$ 的边直到合法，根据第一个合法的位置分治。

注意细节，整体二分后面的状态 $(l,r,vl,vr)$ 需要并查集中含有所有编号 $\leq l$ 且权值 $\leq vl$ 的边，考虑维护一个可撤销并查集即可。

时间复杂度 $\mathcal O(m\log m\log n)$。

```cpp
#include<cstdio>
#include<algorithm>

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}

inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 3e5 + 5;

int n, m, cnt, fa[_], sz[_], t, s[_], ans[_];

struct abc {
	int u, v, w, id;
	bool operator < (const abc &t) {
		return w < t.w;
	}
} e[_], b[_];

int find(int x) {
	return fa[x] == x ? x : find(fa[x]);
}

void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (sz[u] < sz[v]) std::swap(u, v);
	if ((sz[u] & 1) && (sz[v] & 1)) cnt -= 2;
	sz[u] += sz[v], fa[v] = u, s[++t] = v;
}

void ers(int lim) {
	while (t > lim) {
		int v = s[t--], u = fa[v];
		fa[v] = v, sz[u] -= sz[v];
		if ((sz[u] & 1) && (sz[v] & 1)) cnt += 2;
	}
}

void solve(int l, int r, int vl, int vr) {
	if (l > r || vl > vr) return;
	if (vl == vr) {
		for (int i = l; i <= r; ++i) ans[i] = b[vl].w;
		return;
	}
	int mid = (vl + vr) >> 1, nw = t;
	for (int i = vl; i <= mid; ++i)
		if (b[i].id < l) merge(b[i].u, b[i].v);
	int Id = r + 1, nw2 = t;
	for (int i = l; i <= r; ++i) {
		if (e[i].w <= b[mid].w) merge(e[i].u, e[i].v);
		if (!cnt) {
			Id = i;
			break;
		}
	}
	ers(nw2);
	solve(l, Id - 1, mid + 1, vr);
	ers(nw);
	for (int i = l; i < Id; ++i)
		if (e[i].w <= b[vl].w) merge(e[i].u, e[i].v);
	solve(Id, r, vl, mid);
	ers(nw);
}

signed main() {
	n = cnt = read(), m = read();
	for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
	for (int i = 1; i <= m; ++i) {
		e[i].u = read(), e[i].v = read(), e[i].w = read();
		e[i].id = i, b[i] = e[i];
	}
	std::sort(b + 1, b + m + 1);
	b[m + 1].w = -1;
	solve(1, m, 1, m + 1);
	for (int i = 1; i <= m; ++i) write(ans[i]), he;
}
```



---

