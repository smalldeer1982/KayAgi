# [ARC181E] Min and Max at the edge

## 题目描述

对于一个编号的无向图，如果存在一棵满足以下条件的生成树 $T$，则称该图为**好图**。对于 $2$ 个顶点 $u,v\ (u < v)$ 之间的边，记为边 $(u,v)$。

- 对于图中的每一条边 $(u,v)\ (u < v)$，在 $T$ 上连接顶点 $u,v$ 的唯一简单路径上，路径经过的所有顶点编号的最小值和最大值分别为 $u,v$。

给定一个包含 $N$ 个顶点、顶点编号为 $1$ 到 $N$ 的简单连通无向图 $G$。图 $G$ 有 $M$ 条边，第 $i$ 条边连接顶点 $A_i,B_i\ (A_i < B_i)$。

对于每个 $i=1,2,\dots,M$，请判断从 $G$ 中删除第 $i$ 条边后得到的图是否为**好图**。

## 说明/提示

## 限制条件

- $2 \leq N \leq 2 \times 10^5$
- $N-1 \leq M \leq 2 \times 10^5$
- $1 \leq A_i < B_i \leq N$
- 输入的所有值均为整数
- 给定的图为简单连通无向图

## 样例解释 1

以删除边 $(4,6)$ 为例，考虑由边 $(1,3),(2,5),(3,4),(3,5),(5,6)$ 构成的生成树。例如对于边 $(3,6)$，连接顶点 $3,6$ 的简单路径为 $3,5,6$，路径上的顶点编号的最小值和最大值分别为 $3,6$，满足条件。对其他边也同理，可以验证该生成树满足条件，因此答案为 `Yes`。  
另一方面，若删除边 $(1,5)$，考虑同样的生成树。对于边 $(4,6)$，连接顶点 $4,6$ 的简单路径为 $4,3,5,6$，路径上的顶点编号的最小值和最大值分别为 $3,6$，不满足条件。对于其他生成树也可以证明不满足条件，因此答案为 `No`。

## 样例解释 2

删除某条边后，图也有可能变为非连通图。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 9
1 3
1 5
2 5
2 6
3 4
3 5
3 6
4 6
5 6```

### 输出

```
No
No
No
No
Yes
No
No
Yes
Yes```

## 样例 #2

### 输入

```
5 4
1 2
2 3
3 4
4 5```

### 输出

```
No
No
No
No```

## 样例 #3

### 输入

```
15 20
12 13
7 8
5 7
8 10
9 12
4 5
11 12
2 4
6 8
4 14
1 2
14 15
2 9
3 8
2 15
10 11
13 14
8 9
7 14
5 13```

### 输出

```
No
No
No
Yes
Yes
No
Yes
No
No
No
No
No
No
No
No
Yes
No
No
No
No```

# 题解

## 作者：WrongAnswer_90 (赞：6)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18348887)

### [[ARC181E] Min and Max at the edge](https://www.luogu.com.cn/problem/AT_arc181_e)

场上没人过的神题。（大概是搬运的官方题解）

先考虑如何 chk 一个图是否存在好生成树。观察好生成树的限制，发现其对于非树边的限制是在生成树上连接两点的路径有关。而 Kruskal 的证明就是对于每条非树边，其边权大于所有其路径上的树边，两者很像。

但是题目中的限制是点的限制，转到边上的想法是给点赋点权 $X_i$，然后 $(u,v)$ 的边权为 $|X_u-X_v|$。考虑把 $X$ 设成一个递增的序列，比如 $X_i=10^i$，这样边权一定互不相同。 

对于一棵好的生成树，设 $S(u,v)$ 表示 $u,v$ 之间的树上路径，则对于点 $i$ 要求 $\forall i\in S(u,v),X_u\leq X_i\leq X_v$。而对于边 $(x,y)$，$X_u\leq X_x,X_y\leq X_v$。设其根据上述定义的边权是 $w(x,y)=|X_x-X_y|$，则 $\forall (x,y)\in S(u,v),w(x,y)<w(u,v)$。这就证明了好的生成树一定是新图中的最小生成树。

因为可以构造出边权互不相同的情况，所以这也证明了好的生成树也是唯一的。跑出来这个图的最小生成树之后，检查每条非树边，如果都满足限制则该图是好的。

但是题目有多次询问，而且这个最小生成树也不是那么好求。不难发现其实图中定义的边权只需要满足 $\forall i<j<k,w(i,j)<w(i,k)$ 并且 $\forall i<j<k,w(i,k)>w(j,k)$ ，即满足区间包含单调性即可。

所以可以把边 $w(u,v)$ 赋为 $v\times(n+1)-u$，这样得到的生成树一定满足对于任意非树边 $(u,v)$，其路径上的最大值就是 $v$。原因是非树边 $(u,v)$ 路径上的边权应当都小于 $w(u,v)$，所以如果存在大于 $v$ 的点则一定不合法。而且因为是 $-u$，所以合并两个连通块的时候，一边选择的较小的点会尽可能的大，这也满足路径上的最小值尽量是 $u$。

但是这样还是需要 chk 路径上点的最小值是否满足条件。可以再反着做一遍，$w(u,v)=(n-u+1)\times(n+1)-(n-v+1)$，同理得这样求出来的东西的最小值一定合法，最大值尽量合法。因为已经证明了好的生成树唯一，所以判一下两棵树是否相同即可。

这样就将问题转化成了比较好的形式：删边求最小生成树，可以看成是找一条非树边 $(x,y)$ 满足 $x\in \text{subtree}(i),y\notin \text{subtree(i)},w(x,y)$ 最小。转成 dfn 序之后可以看成是两个 3-side 矩形查最小值，可以扫描线线段树维护，复杂度是 $\mathcal O(n\log n)$。

```cpp
int n,m,fa[200010];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
set<int> st;
inline void update(int id)
{
	auto it=st.find(id);
	if(it==st.end())st.insert(id);
	else st.erase(it);
}
int flag=1;
struct Node
{
	int x,y,z,t;
	Node(int X=0,int Y=0,int Z=0,int T=0){x=X,y=Y,z=Z,t=T;}
};
inline bool cmp1(Node x,Node y){return x.z<y.z;}
struct MST
{
	int cnt,head[200010],to[400010],nex[400010];
	int tot,siz[200010],dfn[200010];
	pii ans[200010];
	bool ins[200010];
	Node a[200010];
	vector<tup> L[200010],R[200010];
	vector<pair<int,pii>> ve[200010];
	inline pii get(pii x,pii y){return x.fi<y.fi?x:y;}
	struct{int l,r;pii v;}t[400010];
	#define ls(x) (t[x].l+t[x].r)
	#define rs(x) (ls(x)^1)
	void build(int p,int l,int r)
	{
		t[p]={l,r,mp(INF,0)};
		if(l==r)return; 
		int mid=l+((r-l)>>1);
		build(ls(p),l,mid),build(rs(p),mid+1,r);
	}
	void change(int p,int x,pii y)
	{
		t[p].v=get(t[p].v,y);
		if(t[p].l==t[p].r)return;
		change(ls(p)^(x>t[ls(p)].r),x,y);
	}
	pii ask(int p,int l,int r)
	{
		if(l<=t[p].l&&r>=t[p].r)return t[p].v;
		pii v=mp(INF,0);
		if(l<=t[ls(p)].r)v=get(v,ask(ls(p),l,r));
		if(r>t[ls(p)].r)v=get(v,ask(rs(p),l,r));
		return v;
	}
	inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
	void dfs(int x,int Fa=0)
	{
		dfn[x]=++tot,siz[x]=1;
		for(int i=head[x];i;i=nex[i])if(to[i]!=Fa)
		dfs(to[i],x),siz[x]+=siz[to[i]];
	}
	inline void solve()
	{
		int x,y;
		for(int i=1;i<=n;++i)fa[i]=i;
		sort(a+1,a+1+m,cmp1);
		for(int i=1;i<=m;++i)
		{
			x=find(a[i].x),y=find(a[i].y),ans[i]=mp(INF,0ll);
			if(x==y)continue;
			ins[a[i].t]=1,update(a[i].t),fa[x]=y;
			add(a[i].x,a[i].y),add(a[i].y,a[i].x);
		}
		for(int i=2;i<=n;++i)flag&=find(i-1)==find(i);
		dfs(1),build(1,1,n);
		for(int i=1;i<=m;++i)
		{
			if(!ins[a[i].t])continue;
			x=dfn[a[i].x]<dfn[a[i].y]?a[i].y:a[i].x;
			L[dfn[x]-1].eb(tup(dfn[x],dfn[x]+siz[x]-1,a[i].t));
			R[dfn[x]+siz[x]].eb(tup(dfn[x],dfn[x]+siz[x]-1,a[i].t));
		}
		for(int i=1;i<=m;++i)if(!ins[a[i].t])
		ve[min(dfn[a[i].x],dfn[a[i].y])].eb(mp(max(dfn[a[i].x],dfn[a[i].y]),mp(a[i].z,a[i].t)));
		for(int i=1;i<=n;++i)
		{
			for(auto [x,y]:ve[i])change(1,x,y);
			for(auto [x,y,z]:L[i])ans[z]=get(ans[z],ask(1,x,y));
			ve[i].clear();
		}
		build(1,1,n);
		for(int i=1;i<=m;++i)if(!ins[a[i].t])
		ve[max(dfn[a[i].x],dfn[a[i].y])].eb(mp(min(dfn[a[i].x],dfn[a[i].y]),mp(a[i].z,a[i].t)));
		for(int i=n;i>=1;--i)
		{
			for(auto [x,y]:ve[i])change(1,x,y);
			for(auto [x,y,z]:R[i])ans[z]=get(ans[z],ask(1,x,y));
			ve[i].clear();
		}
	}
}t[2];
inline void mian()
{
	read(n,m);int x,y;
	for(int i=1;i<=m;++i)
	{
		read(x,y);
		if(x>y)swap(x,y);
		t[0].a[i]=Node(x,y,y*inf-x,i);
		t[1].a[i]=Node(x,y,(n-x+1)*inf-(n-y+1),i);
	}
	t[0].solve(),t[1].solve();
	if(!flag){for(int i=1;i<=m;++i)puts("No");return;}
	for(int i=1;i<=m;++i)
	{
		int fl=1;
		if(t[0].ins[i])fl&=t[0].ans[i].se!=0,update(i),update(t[0].ans[i].se);
		if(t[1].ins[i])fl&=t[1].ans[i].se!=0,update(i),update(t[1].ans[i].se);
		if(st.empty()&&fl)puts("Yes");else puts("No");
		if(t[0].ins[i])update(i),update(t[0].ans[i].se);
		if(t[1].ins[i])update(i),update(t[1].ans[i].se);
	}
}
```

---

## 作者：SegTree (赞：3)

比较厉害的题。

首先考虑如何 check 是否存在生成树。

考虑一些比较自然的想法，比方说按 $v$ 升序排序。那么对于非树边的限制，它一定满足编号最大的是 $v$，否则就不是最小生成树了，可以把这条非树边换成树边。也就是说按照 $v(n+1)-u$ 排序。为了尽可能满足 $u$ 的限制，应该在 $v$ 等值时按 $u$ 升序排序，然后暴力 check $u$ 的限制是否被满足，但是这么做太麻烦了。

于是把上面那一步换成按 $u$ 降序排序，相同时按 $v$ 降序排序，此时 $u$ 的限制一定被满足，且会尽可能满足 $v$ 的限制。因此，我们可以直接 check 这两颗生成树选择的边集是否一致。

问题变成：

给你两张图，边集一样但边权不一样。询问将每条边删除后最小生成树选择的边集是否一致。

给每条边随机一个权值，先求最小生成树的随机权值和，然后对于树边算一下一端在里边 $dfn_x\in [dfn_u,dfn_u+siz_u)$ 一端在外面的边 $dfn_y\notin [dfn_u,dfn_u+siz_u)$ 边权最小的边对应的随机权值。

这是经典问题，离线后使用一颗线段树不难解决。

视 $n,m$ 同阶，复杂度 $O(n\log n)$。

---

## 作者：qiuzx (赞：1)

称一棵生成树是好的当且仅当它是将某个图判定为好图时所用的那棵生成树。

首先考虑如何判断一个图是否是好的。既然是生成树，那么容易想到通过最小生成树进行刻画，所以我们试图对边进行赋权（假定边权互不相同），使得每个好的生成树一定是以这种方式赋权所得到的最小生成树。如果有这样一种赋权方式，那么直接求出最小生成树之后可以就很容易 check 图是否是好的了。

注意到最小生成树的关键性质就是对于每条非树边 $(u,v)$，在树上 $u\to v$ 路径上的任意一条边 $(u',v')$ 均满足 $w_{u',v'}<w_{u,v}$。而我们现在希望对于所有不是最小生成树的生成树都一定不是好的，因此假定这棵生成树上有某条非树边 $(u,v)$，则一定存在一条原图上的边 $(u',v')$，使得 $w_{u',v'}<w_{u,v}$ 且在这棵生成树上 $u'\to v'$ 的路径上必须经过 $u$ 和 $v$。如果能够让 $(u',v')$ 不合法，那么我们的目标就达成了。而只需要 $w_{x,y}$ 赋值为与 $|x-y|,\max(x,y),\min(x,y)$ 等相关的权值，基本上都可以验证此时 $(u',v')$ 一定不合法。例如令 $w_{x,y}=|x-y|$（再加上某个 tie breaker），则不妨设 $u'<v',u<v$。那么由于 $w_{u',v'}<w_{u,v}$，一定有 $v-u>v'-u'$，即有 $v>v'$ 或 $u<u'$，显然原图不是好的。

但如果想要处理原问题，任取一种这样的赋值方式是不够的，因为我们不能在删除一条边之后重新做一次最后的 check。上述的赋值方式可以保证算出的最小生成树是这棵生成树是好的生成树的一个必要条件，但并不充分。不过很明显不可能存在某种最小生成树是一个充要条件，所以我们希望在必要条件的基础上做得好一些，例如找到某个生成树满足之前的所有要求，同时对于任意图，每条边 $(u,v)(u<v)$ 在这棵生成树的路径上所有点中最大的一个都一定小于 $v$。

可以发现以在上述几种较为简单的赋值方式中，基于 $\max(x,y)$ 赋值的方式是可行的。例如令 $w_{x,y}=By-x$，其中 $x<y$，$B$ 为一个足够大的常数（$>n$ 即可，这是为了保证权值互不相同）。此时首先需要验证对于任意 $(u,v),(u',v')(u<v,u'<v')$，若 $u,v$ 在 $u'\to v'$ 的路径上且 $w_{u,v}>w_{u',v'}$，则 $v>v'$ 或 $u<u'$。由于 $w_{u,v}>w_{u',v'}$，所以 $Bv-u>Bv'-u'$，即 $v>v'$ 或 $u<u'$。另一方面，还需要证明对于每条边 $(u,v)(u<v)$ 和每条在最小生成树上 $u\to v$ 路径上的边 $(u',v')(u'<v')$，都有 $v'\le v$。由于 $w_{u',v'}<w_{u,v}$，所以 $Bv'-u'<Bv-u$，即 $v'\le v$。

因此我们证明了，若令图中每条边 $(x,y)(x<y)$ 的权值为 $By-x$，则这张图的最小生成树必定是一个好的生成树，且这个最小生成树满足让这个图是好图的合法条件的一半。那么自然可以对称地想，发现如果令权值为 $B(n-x)-(n-y)$，这样得到的最小生成树同样是一个好的生成树，且满足合法条件的另一半（即对于任意一条边 $(u,v)(u<v)$，树上 $u\to v$ 路径上的所有点均 $>u$）。将这两半拼在一起就是原图合法的充分条件。从而原图是好的，当且仅当这两种方式求出的最小生成树是一样的。

现在回到原题，先求出按照这两种方式的最小生成树，然后需要对每条边，求出将它删除后两棵生成树的变化。对于非树边显然没有变化。对于树边，相当于要找出跨越它的非树边中最小的一个，可以枚举非树边转化为树上路径取 $\min$，单点查询，可以使用树剖线段树维护，复杂度 $O(n\log^2n)$。最后只需要判定两棵生成树的边集是否相等即可，由于对于每条边对边集的修改量是 $O(1)$ 的，所以可以使用 XOR hashing 维护。

[代码](https://atcoder.jp/contests/arc181/submissions/56464022)

---

