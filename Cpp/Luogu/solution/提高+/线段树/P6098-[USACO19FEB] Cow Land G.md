# [USACO19FEB] Cow Land G

## 题目背景

Cow Land 是一个特殊的奶牛游乐园，奶牛们可以在那里漫步，吃美味的草，并参观不同的景点（尤其过山车特别受欢迎）。

## 题目描述

Cow Land 总共有 $ N $ 个不同的景点（ $ 2 \leq N \leq 10^5 $ ）。 一共有 $ n-1 $ 条道路连接任意两个景点，这意味着任意两个景点间只有一条简单路径。

每个景点 $ i $ 都有一个享受值 $ e_i $ ，这个值可能会改变。因为一些景点在早上更有吸引力，而其他景点在下午则更能吸引游客。

从景点 $ i $ 到景点 $ j $ 的奶牛们可以欣赏从景点 $ i $ 到景点 $ j $ 的路上的所有景观。这条路线的享受值为景点 $ i $ 到景点 $ j $ 的路上的所有景点（包括景点 $ i $ 和景点 $ j $ ）的享受值按位进行异或运算的结果。

请帮助奶牛确定他们前往 Cow Land 旅行时计划的路线的享受值。

## 说明/提示

子任务：对于 $ 50\% $ 的数据，没有修改操作。

## 样例 #1

### 输入

```
5 5
1 2 4 8 16
1 2
1 3
3 4
3 5
2 1 5
1 1 16
2 3 5
2 1 5
2 1 3
```

### 输出

```
21
20
4
20
```

# 题解

## 作者：LeavingZzz (赞：12)

# Solution For P6098  
$By\text{ }ShadderLeave$  
这道题目是一道点权树链剖分叠线段树的题目，码量相对不高，适合入门练手。  
比起最最朴素（维护点权和/最大值）的树链剖分来说，略略有一点点变化，就是需要维护的操作有些奇怪是[异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)，但是没什么影响，有的盆友担心异或不能用线段树维护，~~不要害怕，维护异或的最好方法是面对异或~~，因为异或可以看做是每一个数变成了 $31(int)$ 个 $01$ 然后排成一张表，对于每一位只用关心有奇数个还是偶数个 $1$ 就行了（翻译：**异或运算满足交换律与结合律**）  
那么这道题就变成板子题目了，线段树的节点表示其代表区间内所有节点的异或值，刚刚已经说过满足交换律和结合律，所以回答询问的时候直接按照一般的树链剖分方法来就行。  
换句话说 将一条路径根据划分的轻重链来分成几个区间，然后使用线段树维护区间异或值，由于满足结合律所以先计算**一个个的区间异或值最后异或在一起的结果 和 要求的路径异或值相等**，所以线段树的维护是正确的。  
（别打着打着迷路了，**运算符都是异或**）  
那么....上代码？  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100007;
int N,Q,ix;
struct E{
	int u,v;
}e[maxn<<1];
int first[maxn],nt[maxn<<1],ES;
int TREE[maxn<<2];
int depth[maxn],sz[maxn],top[maxn],A[maxn];
//A数组是点权
int son[maxn],id[maxn],anti[maxn],fa[maxn];
//id是节点->线段树编号的映射 anti是线段树编号->节点的映射(反向映射)
inline void addE(int u,int v)
{
	e[++ES]=(E){u,v};
	nt[ES]=first[u];
	first[u]=ES;
	e[ES+N]=(E){v,u};
	nt[ES+N]=first[v];
	first[v]=ES+N;
	return ;
}
inline int Re()
{
	char c;
	int re,f=1;
	while((c=getchar())>'9'||c<'0')
	if(c=='-') f=-1;
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re*f;
}
inline void DFS(int u)
{
	sz[u]=1;
	int v;
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v!=fa[u])
		{
			depth[v]=depth[u]+1;
			fa[v]=u;
			DFS(v);
			sz[u]+=sz[v];
			if(sz[v]>sz[son[u]]) son[u]=v;
		}
	}
	return ;
}
inline void dfs(int u,int tp)
{
	top[u]=tp;
	id[u]=++ix;anti[ix]=u;
	if(son[u]) dfs(son[u],tp);
	int v;
	for(int i=first[u];i;i=nt[i])
	{
		v=e[i].v;
		if(v!=fa[u]&&v!=son[u])
			dfs(v,v);
	}
	return ;
}
#define mid (L+R>>1)//习惯加上括号因为位运算优先级低谁也不知道会发生什么qwq
inline void Build(int L,int R,int i)
{
	if(L==R)
	{
		TREE[i]=A[anti[L]];
		return ;
	}
	Build(L,mid,i<<1);
	Build(mid+1,R,i<<1|1);
	TREE[i]=TREE[i<<1]^TREE[i<<1|1];
	return ;
}
inline void Update(int L,int R,int x,int i,int k)
{
	if(L==R)//单点修改 [L,R]是当前区间
	{
		TREE[i]=k;
		return ;
	}
	if(x<=mid) Update(L,mid,x,i<<1,k);
	else Update(mid+1,R,x,i<<1|1,k);//单点修改非此即彼直接else即可
	TREE[i]=TREE[i<<1]^TREE[i<<1|1];//使用异或运算符更新
	return ;
}
inline int QwQ(int L,int R,int l,int r,int i)
{//[L,R]是当前区间，[l,r]是待查区间
	if(l<=L&&R<=r)
		return TREE[i];
	int ans=0;//切记初始化为0
	if(l<=mid) ans^=QwQ(L,mid,l,r,i<<1);//全部是异或
	if(r>mid) ans^=QwQ(mid+1,R,l,r,i<<1|1);
	return ans;
}
inline int Query_Path(int x,int y)
{
	int ans=0;//切记初始化为0
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		ans^=QwQ(1,N,id[top[x]],id[x],1);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	ans^=QwQ(1,N,id[x],id[y],1);
	return ans;
}
int main()
{
	N=Re();Q=Re();
	int u,v,s;
	for(int i=1;i<=N;i++)
		A[i]=Re();
	for(int i=1;i<N;i++)
	{
		u=Re();v=Re();
		addE(u,v);
	}
	DFS(1);dfs(1,1);
	Build(1,N,1);
	for(int i=1;i<=Q;i++)
	{
		s=Re();u=Re();v=Re();
		if(s==1)
			 Update(1,N,id[u],1,v);
		else printf("%d\n",Query_Path(u,v));
	}
	return 0;
}
```
这是较为简单的一道树链剖分题目，没有懒惰标记，也没有大的变形，大家在熟练掌握点权树链剖分之后可以开始了解维护边权树链剖分以及一些在原有的算法上巧妙变形的题目。[边权树链剖分板子](https://www.luogu.com.cn/blog/ShadderLeave/solution-p3038)，另外因为有些树链剖分题目实在太毒瘤，窝建立了一个题单来巩固代码熟练程度，[欢迎大家来van](https://www.luogu.com.cn/training/1654#problems)。  
谢谢管理大大审核^_^

---

## 作者：DPair (赞：5)

为什么题解里面全都是树链剖分啊。。。为什么树链剖分的题目一定要用树链剖分来做呢？

提供一种 **DFS序** 的写法，在此我把这道题当作 **DFS序** 板子题详细讲一下。

### 注意：以下内容仅代表个人理解，若有错误请各位一定要及时指正，多谢！

# 【DFS序】（会的可以跳过这一部分）
## 【前置知识】
- DFS（都叫**DFS序**了肯定要会DFS啊）
- 线段树（与DFS序配套使用）
- LCA (仅限于本题，当然很多类似的题目也都用得上)

## 【是什么】
首先我们要了解 **DFS序** 是什么。

顾名思义， **DFS序** 就是 **对一棵树DFS后形成的一个序列**。

大概由这样两个数组构成：（以下称呼受 $tarjan$ 算法影响严重，正式称呼本人不太清楚，知道的大佬可以在评论里说一声）：

- $dfn[i]$ 表示第 $i$ 个节点是 **第几个** 入搜索栈的。
- $low[i]$ 表示第 $i$ 个节点出搜索栈时，最晚入搜索栈的节点的 $dfn$ 值，即此时的 $dfn$ 最大值。

这么说可能有些难懂，我们换一种说法：
- $dfn[i]$ 表示第 $i$ 个节点是 **第几个** 被搜到的。
- $low[i]$ 表示第 $i$ 个节点出搜索栈时，**有多少个** 节点已经被搜过了（其实还是 $dfn$ 最大值）。

这样似乎什么也看不出来，那我们分析一下这两个数组的性质。

## 【性质】
首先，在树上**DFS**先天有一个十分优美的性质：搜完一个节点 $root$ 后，一定会先搜完以它为根的子树中的所有节点 $node$，然后它再出搜索栈。即 $low[root] \geq dfn[node]$ 。

然后还有一个很废话的性质，搜索到一个节点之前，其父亲节点一定被搜索过，即 $dfn[father] < dfn[son]$ ，那么反过来说，一个节点 $root$ 为根的子树中的所有节点 $node$ 都满足：$dfn[root] \leq dfn[node]$ （一个节点本身也在它为根的子树中）。

于是我们发现了一个神奇的东西：

对于一个节点 $root$ ，它子树中所有节点的 $dfn$ 都满足 $dfn\in[dfn[root],low[root]]$

而且我们能进一步发现，**同一棵子树上的节点的** $dfn$ **值一定是连续的！** （毕竟是连着搜索到的）

于是我们成功把树上问题（子树问题）转化为了区间问题。然后就可以用线段树来维护子树问题了。

## 【维护】
不难发现DFS序的局限性：只能进行子树的维护（当然可能也有其他高科技的方法使得DFS序可以解决其他问题，但我不会，这里就不讲了）。

那我们就认真考虑对子树操作的维护了：

### 【对应关系】
由于我们使用线段树来维护子树问题，那我们就得知道线段树与子树上信息的对应关系。

这里我们设线段树维护的序列为 $a$ ，那么我们的对应关系很显然应该是这样：

对于节点 $i$，设 $val[i]$ 表示它的权值，那么线段树上就有 $a[dfn[i]] = val[i]$ 。

用 $dfn$ 值来进行对应更利于我们利用DFS序的性质进行维护。因为此时，以 $root$ 为根的子树就很好表示了：

$a$ 上的区间 $[dfn[root],low[root]]$ 表示以 $root$ 为根的子树。

### 【区间修改】
修改以 $root$ 为根的子树此时等同于修改 $a$ 上的区间 $[dfn[root],low[root]]$   ，即 $modify(dfs[root],low[root])$

### 【区间求值】
同理，$query(dfs[root],low[root)$ 。

# 【本题】
## 【思路】
使用DFS序维护子树信息。

有人可能会问了：“诶？这道题不是问我们路径信息吗？和子树有什么关系？”

别急，我们先对问题进行一下转化。

首先，众所周知有根树上的一条路径的权值和可以用 $LCA$ 和**前缀和**来完成。

其大体思路（以本题为情境，下同）就是记录每一个点到根节点的权值的异或和，对于每两个点 $u, v$ ，用类似前缀和的思想求出 $u, v$ 到它们的 $LCA$ 的异或和，最后再把这两个值异或一下并异或上 $LCA$ 的权值就是 $u$ 到 $v$ 路径上所有点的异或和。（异或上 $LCA$ 的值是由于本题记录的是点权， $u,v$ 到其 $LCA$ 的路径上都不包含 $LCA$ 的点权，所以最后要异或上） 。

所以对于每个点 $i$ ，我们要维护这个点到根节点的异或和 $val[i]$ 。

于是单点查询就可以了。

下面考虑修改。

我们发现，修改一个点上的数，这个点为根的子树中的所有节点的异或和都会发生改变，由于一个点从 $e[i]$ 变为了 $v$ ，相当于异或值异或上了 $e[i]~xor~v$ （一个数异或其本身刚好为 $0$ ，相当与原先该子树中所有点都**异或过** $e[i]$ ，现在消除该影响并改为**异或过** $v$），然后 $e[i]=v$ 即可。

最后稍微讲一下实现上的细节，查询 $u,v$ 路径上的异或和时，由于一个点到其 $LCA$ 的路径上的异或和刚好为 $val[u/v]~xor~val[LCA]$ ，所以最终答案为：

$$
val[u]~xor~val[v]~xor~val[LCA]~xor~val[LCA]~xor~e[LCA]
$$

$$
=val[u]~xor~val[v]~xor~e[LCA]
$$

可以少一次询问。

## 【代码】
（注意：这里代码中的 $val$ 数组实际上是题面中的 $e$ ，不用 $e$ 的原因是建图的时候用过了。）

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
//以上是无关紧要的快读什么的
int dfn[100005], low[100005], tot, val[100005];//dfs序
int n, Q;
int head[100005], nxt[200005], e[200005], cnt;//链式前向星

inline void add(int u, int v){
    nxt[++ cnt] = head[u];
    head[u] = cnt;
    e[cnt] = v;
}
//以下是线段树，与普通线段树没有任何区别
#define LSON rt << 1, l, mid
#define RSON rt << 1 | 1, mid + 1, r

int num[400005], lazy[400005];
inline void pushup(int rt){num[rt] = num[rt << 1] ^ num[rt << 1 | 1];}
inline void update(int rt, int l, int r, int w){
    if((r - l + 1) & 1) num[rt] ^= w;
    lazy[rt] ^= w;
}
inline void pushdown(int rt, int l, int r){
    if(lazy[rt]){
        int mid = (l + r) >> 1;
        update(LSON, lazy[rt]);
        update(RSON, lazy[rt]);
        lazy[rt] = 0;
    }
}
void modify(int rt, int l, int r, int x, int y, int w){
    if(x <= l && r <= y) return update(rt, l, r, w);
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid) modify(LSON, x, y, w);
    if(y > mid) modify(RSON, x, y, w);
    pushup(rt);
}
int query(int rt, int l, int r, int x){
    if(x == l && l == r) return num[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid) return query(LSON, x);
    else return query(RSON, x);
}

int fa[100005][21], dep[100005];

void build(int x, int pre){//建树+倍增LCA初始化
    dfn[x] = ++ tot;
    for (register int i = head[x];i;i = nxt[i]){
        if(pre == e[i]) continue;
        dep[e[i]] = dep[x] + 1;
        fa[e[i]][0] = x;
        for (register int j = 1;j <= 20;j ++) fa[e[i]][j] = fa[fa[e[i]][j - 1]][j - 1];
        build(e[i], x);
    }
    low[x] = tot;
}

inline int LCA(int x, int y){//倍增求LCA
    if(dep[x] < dep[y]) swap(x, y);
    for (register int i = 20;i >= 0;i --){
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if(dep[x] == dep[y]) break;
    }
    if(x == y) return x;
    for (register int i = 20;i >= 0;i --){
        if(fa[x][i] ^ fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    read(n);read(Q);
    for (register int i = 1;i <= n;i ++) read(val[i]);
    for (register int i = 1;i < n;i ++){
        int u, v;read(u);read(v);
        add(u, v);add(v, u);
    }
    dep[1] = 1;
    build(1, 0);
    for (register int i = 1;i <= n;i ++) modify(1, 1, n, dfn[i], low[i], val[i]);
    while(Q --){
        int opt, x, y;read(opt);read(x);read(y);
        if(opt == 1){//修改
            int tmp = val[x] ^ y;
            val[x] = y;
            modify(1, 1, n, dfn[x], low[x], tmp);
        }
        else{//询问
            int lca = LCA(x, y);
            int tmp1 = query(1, 1, n, dfn[x]);
            int tmp2 = query(1, 1, n, dfn[y]);
            fprint(tmp1 ^ tmp2 ^ val[lca], 10);
        }
    }
}
```

---

## 作者：翼德天尊 (赞：5)

**这是一道非常裸的树剖题了。**

[$\color{red}\text{重链剖分好文推荐}$](https://www.cnblogs.com/ivanovcraft/p/9019090.html)

## Part 1 简述题意

有一棵点权树，要求你建立一种数据结构来维护树上两点之间的权值异或值，支持单点修改。

通过**树上两点之间的点权异或值**，我们可以考虑采用树剖的方式。具体一点，可以采用重链剖分。~~毕竟人家更简单~~

## Part 2 步骤阐述

**重链剖分基础步骤：**

1. 输入数据，建边。

2. 两次 $\text{dfs}$ 建立重链剖分信息。

3. 维护操作。

**而这道题的步骤当然与这个差不多啦！**

### 但是，切记：

在重链剖分的过程中，我们的点权有两个序，一个是输入顺序，一个是建立剖分信息时的 $\text{dfs}$ 序。而为了让根节点到它的重儿子之间在维护时可以直接区间维护，所以我们在建立数据结构维护树剖的时候**下标一定要用 $\text{dfs}$ 序**，而在**由输入顺序转入数据结构计算的时候一定要将输入序转换为 $\text{dfs}$ 序**，这样才能在树剖过程中区间处理！！！切记！！~~每次做重链剖分题的时候都会错几次~~

## Part 3 AC code

```cpp
#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;
#define N 100005 
int n,q,in[N],tot,head[N],rk[N];
struct node{
	int to,next;
	node (int to=0,int next=0):to(to),next(next){}
}bian[N<<1];//每一条边
struct node1{
	int fa,zson,w,top,size,d,id;
}e[N];//树剖的每一个节点
struct node2{
	int l,r,sum;
}t[N<<2];//线段树的每一个节点
int read(){//快读
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		c=getchar();
		if (c=='-') f=-1;
	}
	while (c>='0'&&c<='9'){	
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar(); 
	} 
	return w*f;
}
void adde(int u,int v){//加边
	bian[++tot]=node(v,head[u]);
	head[u]=tot;
}
void dfs1(int u){
	e[u].d=e[e[u].fa].d+1,e[u].size=1;
	for (int i=head[u];i;i=bian[i].next){
		int v=bian[i].to;
		if (v!=e[u].fa){
			e[v].fa=u;
			dfs1(v);
			e[u].size+=e[v].size;
			if (e[v].size>e[e[u].zson].size)
				e[u].zson=v;
		}
	}
}
void dfs2(int u,int tp){
	e[u].top=tp,e[u].id=++tot,rk[tot]=u;
	if (e[u].zson) dfs2(e[u].zson,tp);
	for (int i=head[u];i;i=bian[i].next){
		int v=bian[i].to;
		if (v!=e[u].fa&&v!=e[u].zson) dfs2(v,v);
	}
}
void update(int i){
	t[i].sum=t[i<<1].sum^t[i<<1|1].sum;
} 
void build(int i,int l,int r){
	t[i].l=l,t[i].r=r;
	if (l==r){
		t[i].sum=in[rk[l]];
		return;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	update(i);
}
void change(int i,int dis,int k){
	if (t[i].l==t[i].r){
		t[i].sum=k;
		return;
	}
	if (t[i<<1].r>=dis) change(i<<1,dis,k);
	else change(i<<1|1,dis,k);
	update(i);
}
int query(int i,int l,int r){
	if (t[i].l>=l&&t[i].r<=r) return t[i].sum;
	int ans=0;
	if (t[i<<1].r>=l) ans^=query(i<<1,l,r);
	if (t[i<<1|1].l<=r) ans^=query(i<<1|1,l,r);
	return ans; 
}
int query_(int x,int y){
	int ans=0;
	while (e[x].top!=e[y].top){
		if (e[e[x].top].d<e[e[y].top].d) swap(x,y);
		ans^=query(1,e[e[x].top].id,e[x].id);
		x=e[e[x].top].fa;
	}
	if (e[x].id>e[y].id) swap(x,y);
	ans^=query(1,e[x].id,e[y].id);
	return ans;
}
int main(){
	n=read(),q=read();
	for (int i=1;i<=n;i++) in[i]=read();
	for (int i=1;i<n;i++){
		int u=read(),v=read();
		adde(u,v),adde(v,u);
	}
	dfs1(1),tot=0,dfs2(1,1);
	build(1,1,n);//建树
	while (q--){//处理询问
		int op=read(),l=read(),r=read();
		if (op==1) change(1,e[l].id,r); 
		else printf("%d\n",query_(l,r)); 
	}
	return 0;
} 
```

完结撒花！对了，再次提醒，一定要**转序**哦QwQ！



---

## 作者：IntrepidStrayer (赞：4)

## 题意
给定一颗树，支持单点修改、树上路径异或和查询。

## 题解

这是一道[重链剖分](https://www.luogu.com.cn/problem/P3384)的裸题。

**重链剖分**是将每个节点的**子树大小最大**的儿子节点作为**重儿子**，其余作为轻儿子。

父节点与其重儿子的连边称为**重边**。

然后将整棵树重新编号，把整棵树拆成许多**重链**（由重边相连得到的链）和 **轻链**（由非重边相连得到的链）。

重新编号之后，使用**树状数组**或**线段树**维护即可。如果不了解重链剖分，不妨看看[这篇博客](https://www.cnblogs.com/zwfymqz/p/8094500.html)。

本题需要支持单点修改、树上路径异或和查询，可以使用线段树维护。

复杂度$\mathcal{O}(q\log ^2n)$

注意异或操作在C++中表示为```^```

## 代码
```cpp
#include <cstdio>
#include <cstring>

using namespace std;

#define in __inline__
typedef long long ll;
in ll max(ll x, ll y){return x > y ? x : y;}
in ll min(ll x, ll y){return x < y ? x : y;}
in void swap(ll &x, ll &y){x ^= y ^= x ^= y;}
#define rei register int
#define FOR(i, l, r) for(rei i = l; i <= r; ++i)
#define FOL(i, r, l) for(rei i = r; i >= l; --i)
char inputbuf[1 << 23], *p1 = inputbuf, *p2 = inputbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = inputbuf) + fread(inputbuf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
in ll read() {
	ll res = 0; char ch = getchar(); bool f = true;
	for(; ch < '0' || ch > '9'; ch = getchar())
		if(ch == '-') f = false;
	for(; ch >= '0' && ch <= '9'; ch = getchar())
		res = res * 10 + (ch ^ 48);
	return f ? res : -res;
}
const int N = 1e5 + 15;

int a[N], v[N], sum[N << 2], fr[N << 1], to[N << 1], nxt[N << 1], head[N], cnt;
int dep[N], id[N], top[N], fa[N], siz[N], son[N], tot, n, x, y;
/*
dep[i]：节点i的深度
id[i]：重新编号后节点i的编号
top[i]：包括节点i的重链顶端
siz[i]：以i为根的子树大小
son[i]：节点i的重儿子
fa[i]：节点i的父亲
v[i]：重新编号后编号为i的节点的值
*/

in void add(int x, int y) {to[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;}
in void upd(int k) {sum[k] = sum[k << 1] ^ sum[k << 1 | 1];}

void dfs1(int u, int f) {//处理各种信息，包括深度、父节点、子树大小、重儿子
	int v; fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
	for(rei i = head[u]; i; i = nxt[i]) if((v = to[i]) ^ f) {
		dfs1(v, u); siz[u] += siz[v]; if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
void dfs2(int u, int tf) {//重新编号
	id[u] = ++tot, v[tot] = a[u]; top[u] = tf;
	if(!son[u]) return; dfs2(son[u], tf);
	for(rei i = head[u]; i; i = nxt[i]) if(!id[to[i]]) dfs2(to[i], to[i]);
}

void bd(int k, int l, int r) {
	if(l == r) {sum[k] = v[l]; return;}
	int m = l + r >> 1;
	bd(k << 1, l, m); bd(k << 1 | 1, m + 1, r); upd(k);
}
void cg(int k, int l, int r) {
	if(l == r) {sum[k] = y; return;}
	int m = l + r >> 1;
	id[x] <= m ? cg(k << 1, l, m) : cg(k << 1 | 1, m + 1, r); upd(k);
}
int qr(int k, int l, int r, int x, int y) {
	if(x <= l && r <= y) return sum[k];
	int m = l + r >> 1, res = 0;
	if(x <= m) res ^= qr(k << 1, l, m, x, y);
	if(m < y) res ^= qr(k << 1 | 1, m + 1, r, x, y);
	return res;
}
int query(int x, int y, int res = 0) {//树上路径查询
	for(; top[x] ^ top[y]; y = fa[top[y]]) {
		if(dep[top[x]] > dep[top[y]]) x ^= y ^= x ^= y;
		res ^= qr(1, 1, n, id[top[y]], id[y]);
	}
	if(id[x] > id[y]) x ^= y ^= x ^= y;
	return (res ^= qr(1, 1, n, id[x], id[y]));
}

signed main() {
	int q, opt;
	n = read(); q = read();
	FOR(i, 1, n) a[i] = read();
	FOR(i, 1, n - 1) x = read(), y = read(), add(x, y), add(y, x);
	dfs1(1, 0);
	dfs2(1, 1);
	bd(1, 1, n);
	for(; q; --q) {
		opt = read(), x = read(), y = read();
		if(opt == 1) cg(1, 1, n);
		else printf("%d\n", query(x, y));
	}
	return 0;
}
```

---

## 作者：sycqwq (赞：2)

__做法__

这是一道树链剖分模板题，要注意的就是是异或不是求和

在c++中异或的符号是```^```

然后写线段树的时候有两个操作：区间查询异或+单点修改

如果树链剖分不会的可以看我的这片[文章](https://s-y-c.top/2020/03/04/%E6%B5%85%E8%B0%88%E6%A0%91%E9%93%BE%E5%89%96%E5%88%86/)

注释也来自于这一片文章

__代码：__

```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
const int maxn=100005; 
int son[maxn],fa[maxn],n,tot,cnt,id[maxn],a[maxn],b[maxn],siz[maxn],top[maxn],lazy[maxn<<2],dep[maxn],head[maxn<<1],sum[maxn<<2];
struct nofe{
    int u,v,next;
}e[maxn<<1];
void add(int u,int v)
{
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
int dfs1(int now,int f,int d)//now是现在的节点，f是now的父亲节点，d是现在的深度
{
    dep[now]=d;
    fa[now]=f;
    siz[now]=1;//大小初始为1，也就是本身
    int ma=-1;//ma为现在儿子中最大的siz
    for(int i=head[now];i;i=e[i].next)//链式前向星存边
    {
        if(e[i].v==f)//这样就是标记过了，因为是无向边
            continue;
        siz[now]+=dfs1(e[i].v,now,d+1);//自己的大小=自己所有儿子的大小
        if(siz[e[i].v]>ma)//这里是找重儿子
            ma=siz[e[i].v],son[now]=e[i].v;
    }
    return siz[now];
}
void dfs2(int now,int t)//t为现在的链头
{
    id[now]=++tot;//编号
    a[tot]=b[now];
    top[now]=t;//链头
    if(!son[now])//这是个叶子节点，就不需要继续执行了
        return;
    dfs2(son[now],t);//优先标记重儿子
    for(int i=head[now];i;i=e[i].next)//遍历每一个儿子
    {
    	if(e[i].v==fa[now]||e[i].v==son[now])//这就代表处理过了，跳过
    		continue;
            dfs2(e[i].v,e[i].v);//每个轻儿子，是单独的一条链
    }
}
void build(int l,int r,int rt)//建树
{
    if(l==r)
    {
        sum[rt]=a[l];
        return;
    }
    int mid=l+r>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    sum[rt]=sum[rt<<1]^sum[rt<<1|1];
    
}
void update(int l,int r,int rt,int i,int k)//单点修改
{
    if(l==r)
    {
        sum[rt]=k; 
	    return;
    }
    int mid=l+r>>1;
    if(i<=mid)
    update(l,mid,rt<<1,i,k);
    else 
    update(mid+1,r,rt<<1|1,i,k);
    sum[rt]=sum[rt<<1]^sum[rt<<1|1];
}
int query(int l,int r,int rt,int i,int j)//区间查询异或
{
    if(i<=l&&r<=j)
    {
        return sum[rt];
    }
    int ans=0,mid=l+r>>1;
    if(i<=mid)
        ans^=query(l,mid,rt<<1,i,j);
    
    if(mid<j)
        ans^=query(mid+1,r,rt<<1|1,i,j);
    return ans;     
}
int treesum(int u,int v)
{
    int s=0;
    int tu=top[u];
	int tv=top[v];
	while(tu!=tv){
		if(dep[tu]<dep[tv]){
			swap(tu,tv);
			swap(u,v);
		}
		s^=query(1,n,1,id[tu],id[u]);
                u=fa[tu];
		tu=top[u];
	}
	if(dep[u]>dep[v])swap(u,v);
	s^=query(1,n,1,id[u],id[v]);
    return s;
}
int main(){
    int q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>b[i];
    for(int i=1;i<=n-1;i++)
    {
        int x,y;
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=q;i++)
    {
        int c,x,y;
        cin>>c>>x>>y;
        if(c==1)
        {
            update(1,n,1,id[x],y);
        }
        if(c==2)
            cout<<treesum(x,y)<<endl;
    }
    return 0;
}
```

---

## 作者：白鲟 (赞：2)

## 前言
如果显示有问题就到本蒟蒻的[博客](https://www.luogu.com.cn/blog/bzlz-zdx/solution-p6098)来看看吧。  

学树剖这么久一直没专门为它写一篇博客，这篇就权当学习笔记啦。

## 题意简述
维护树上两种操作：两点路径间异或和查询与单点修改。

## 题目分析
如果学过轻重链剖分，很容易发现这是一道模板题，只需要把模板的路径求和改为异或和，也就是只需要把加号改成异或符号。  

如果没学过，就请往下看吧。  

轻重链剖分主要用于解决树上的单点、路径或子树修改与查询的问题。它的思想是将树剖分成链，从而将树上问题转化为序列问题，这样便可以用维护区间操作的数据结构或算法来维护这些操作了，    

如何进行剖分呢？轻重链剖分是根据子树的大小来剖分的。每个结点与它的子结点中子树结点数目最大的一个结点（称为重儿子）在一条链上，而其他子结点则是以它们为父结点重新建立一条链。~~我不会证明的是~~可以证明的是，这样剖分出来，每个结点到根结点的路径上最多有 $\log n$ 条链。  

那么如何对链进行标记呢？答案是记录每一个结点所在链的顶端结点。之后，为每个结点附加一个编号，每条链的编号是连续的；同时，每棵子树上的编号也是连续的。这样，对于链或子树，我们均可以根据编号将其视为一段区间，对这段区间运用树状数组和线段树等数据结构进行维护。  

对于路径查询，我们不断地统计较深的结点所在的链的贡献并将其跳到其所在链的顶端的父结点（意即换成深度更小的下一条链），直到两点在同一条链上，再统计这两点之间的部分的贡献。路径修改类似。对于子树修改或查询，只需要根据子树的大小计算出子树所占区间的尾部，进行一次修改或查询即可。  

可以发现，在以上的操作中，需要用到子树的大小、深度和父结点三个数据。这可以通过一遍 dfs 进行处理。对于每个点所在的链的顶端和编号，可以通过第二遍 dfs 进行处理。编号可以通过时间戳来解决。由于每条链的编号应该连续，进行搜索时应先搜索重儿子。  

由于通常情况下轻重链剖分需要使用树状数组或线段树进行维护，且每次维护最多进入 $\operatorname O(\log n)$ 条链，每次操作时间复杂度为 $\operatorname{O}( \log^2 n)$。  

对于这道题，由于异或运算具有结合律，故可以使用树状数组或线段树进行维护。由于只需要单点修改区间查询，使用树状数组是一个不错的选择。

## 代码
手写 `swap` 一定要加 `&` 符号啊！！！（大雾。
```cpp
#include<cstdio>
using namespace std;
int n,q,x,y,dir,tot,e[100001],head[100001],suc[200001],go[200001],sum[100001],
	tag,depth[100001],son[100001],father[100001],size[100001],top[100001],no[100001];
inline void swap(int &x,int &y)
{
	x^=y^=x^=y;
	return;
}
inline void add_edge(int x,int y)
{
	suc[++tot]=head[x];
	go[tot]=y;
	head[x]=tot;
	return;
}
inline int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int value)
{
	while(x<=n)
	{
		sum[x]^=value;
		x+=lowbit(x);
	}
	return;
}
int query(int x)
{
	int res=0;
	while(x)
	{
		res^=sum[x];
		x-=lowbit(x);
	}
	return res;
}
void dfs1(int x)
{
	size[x]=1;
	for(int i=head[x];i;i=suc[i])
		if(go[i]!=father[x])
		{
			depth[go[i]]=depth[x]+1;
			father[go[i]]=x;
			dfs1(go[i]);
			size[x]+=size[go[i]];
			if(size[son[x]]<size[go[i]])
				son[x]=go[i];
		}
	return;
}
void dfs2(int x,int loc)
{
	top[x]=loc;
	no[x]=++tag;
	if(!son[x])
		return;
	dfs2(son[x],loc);
	for(int i=head[x];i;i=suc[i])
		if(go[i]!=father[x]&&go[i]!=son[x])
			dfs2(go[i],go[i]);
	return;
}
int query(int x,int y)
{
	int res=0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]]<depth[top[y]])
			swap(x,y);
		res^=query(no[x])^query(no[top[x]]-1);
		x=father[top[x]];
	}
	if(depth[x]>depth[y])
		swap(x,y);
	return res^query(no[y])^query(no[x]-1);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)
		scanf("%d",&e[i]);
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1);
	dfs2(1,1);
	for(int i=1;i<=n;++i)
		add(no[i],e[i]);
	while(q--)
	{
		scanf("%d%d%d",&dir,&x,&y);
		if(dir==1)
		{
			add(no[x],y^e[x]);
			e[x]=y;
		}
		else printf("%d\n",query(x,y));
	}
	return 0;
}
```

---

## 作者：genshy (赞：1)


# 题目大意

单点修改，区间亦或。


很多同学担心可能线段树无法维护区间亦或，但实际上他可以支持很多操作

例如区间开方，区间最大值，区间众数等等。

# 解法

先对原来的树进行树剖，预处理出每一条重链和轻链，然后线段树维护区间亦或。

修改是对经过的每一条链修改，转化为区间修改，查询同理。

# 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int N = 1e5+10;
#define LL long long
int n , m , opt , x , y ,tot , num;
int dfn[N] , size[N] , top[N] , head[N] ;
int fa[N] , a[N] , w[N] ,dep[N] , son[N]; 
struct bian{int to , net ;}e[N*2];
void add_(int x,int y)
{
	tot++;
	e[tot].to = y;
	e[tot].net = head[x];
	head[x] = tot;
}
void get_tree(int x)//树剖常规操作
{
	dep[x] = dep[fa[x]] + 1;
	size[x] = 1;
	for(int i = head[x]; i; i = e[i].net)
	{
		int to = e[i].to;
		if(to == fa[x]) continue;
		fa[to] = x;
		get_tree(to);
		size[x] += size[to];
		if(size[to] > size[son[x]]) son[x] = to;
	}
}
void dfs(int x , int topp)
{
	top[x] = topp;
	dfn[x] = ++num ; w[dfn[x]] = a[x];
	if(son[x]) dfs(son[x] , topp);
	for(int i = head[x]; i; i = e[i].net)
	{
		int to = e[i].to;
		if(to == fa[x] || to == son[x]) continue;
		dfs(to , to);
	}
}
struct tree{//封装线段树
	struct node{
		int lc , rc ;
		LL sum;
	}tr[N<<2];
	#define l(o) tr[o].lc
	#define r(o) tr[o].rc
	#define sum(o) tr[o].sum
	void up(int o)
	{
		sum(o) = sum(o*2) ^ sum(o*2+1);
	}
	void build(int o , int L , int R)
	{
		l(o) = L , r(o) = R;
		if(L == R)
		{
 			sum(o) = w[L]; return ;
		}
		int mid = (L + R) / 2;
		build(o*2, L , mid);
		build(o*2+1 , mid+1 , R);
		up(o);
	}
	void chenge(int o , int L , int R , int val)
	{
		if(L <= l(o) && R >= r(o))
		{
			sum(o) = val; return ;
		}
		int mid = (l(o) + r(o) ) / 2;
		if(L <= mid) chenge(o*2 , L , R , val);
		if(R > mid) chenge(o*2+1 , L , R , val);
		up(o);
	}
	LL ask(int o , int L , int R)
	{
		LL ans = 0;
		if(L <= l(o) && R >= r(o))
		{
			return sum(o);
		}
		int mid = (l(o) + r(o)) / 2;
		if(L <= mid) ans = ans ^ ask(o*2 , L ,R);
		if(R > mid) ans = ans ^ ask(o*2+1 , L , R);
		return ans;
	}
}tree;
LL query(int x , int y)//转化为区间问题
{
	LL ans = 0;
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]]) swap(x , y);
		ans = ans ^ tree.ask(1 , dfn[top[x]] , dfn[x]);//线段树维护区间亦或
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x , y);
	ans = ans ^ tree.ask(1 , dfn[x] , dfn[y]);//最后处理两个点在同一条重链上的情况
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	for(int i = 1; i <= n-1; i++)
	{
		scanf("%d%d" , &x,&y);
		add_(x,y); add_(y,x);
	}
	get_tree(1);//处理出重儿子
	dfs(1 , 1);//找每条链的链端
	tree.build(1 , 1 , n);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1)tree.chenge(1 , dfn[x] , dfn[x] , y);
	        if(opt==2)printf("%lld\n",query(x,y));
	}
	return 0;
}
```

本人码风过丑，勿喷。。。。

---

## 作者：HoshiuZ (赞：1)

~~学树剖的第二天~~。

给定一棵 $n$ 个点的树，每个点有点权。

有两种操作：单点修改与询问路径上点的权值的异或值。

### 思路
显然树剖板子。

单点修改不解释。

询问路径上点的权值的异或值，由于异或满足结合律，直接每段的异或值异或起来就好了。

### 代码
```cpp
#include<bits/stdc++.h>
#define N 100010

using namespace std;

inline int read() {
	int x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return w*x;
}

int n,q,e[N],head[N],fa[N],tot=0,depth[N],size[N],son[N],top[N],id[N],rk[N],cnt=0;
struct graph{
	int v,next;
}edge[N<<1];
class SegmentTree{
  private:
  	int data[N<<2];
  	#define d(x) data[x]
  	#define ls (p<<1)
  	#define rs (ls|1)
  	#define mid (l+r>>1)
    inline void update(int p) {
    	d(p)=d(ls)^d(rs);
    }
  public:
  	void build(int p,int l,int r) {
  		if(l==r) {
  			d(p)=e[rk[l]];
  			return ;
  		}
  		build(ls,l,mid);
  		build(rs,mid+1,r);
  		update(p);
  	}
  	void change(int p,int l,int r,int x,int y) {
  		if(l==r) {
  			d(p)=y;
  			return ;
  		}
  		if(x<=mid) change(ls,l,mid,x,y);
  		else change(rs,mid+1,r,x,y);
  		update(p);
  	}
  	int ask(int p,int l,int r,int L,int R) {
  		if(l>R||r<L) return 0;
  		if(l>=L&&r<=R) return d(p);
  		return ask(ls,l,mid,L,R)^ask(rs,mid+1,r,L,R);
  	}
}T;

void add(int u,int v) {
	edge[++tot].v=v;
	edge[tot].next=head[u];
	head[u]=tot;
}

void dfs_first(int u) {
	depth[u]=depth[fa[u]]+1;
	size[u]=1;
	for(int i=head[u];i;i=edge[i].next) {
		int v=edge[i].v;
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs_first(v);
		size[u]+=size[v];
		if(size[v]>size[son[u]]) son[u]=v;
	}
}

void dfs_second(int u,int t) {
	if(!u) return ;
	top[u]=t;
	id[u]=++cnt;
	rk[cnt]=u;
	dfs_second(son[u],t);
	for(int i=head[u];i;i=edge[i].next) {
		int v=edge[i].v;
		if(v!=fa[u]&&v!=son[u]) dfs_second(v,v);
	}
}

void init() {
	dfs_first(1);
	dfs_second(1,1);
	T.build(1,1,n);
}

int ask(int x,int y) {
	int ans=0;
	while(top[x]!=top[y]) {
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		ans^=T.ask(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(id[x]>id[y]) swap(x,y);
	ans^=T.ask(1,1,n,id[x],id[y]);
	return ans;
}
		
int main() {
	n=read(),q=read();
	for(int i=1;i<=n;i++) e[i]=read();
	for(int i=1;i<n;i++) {
		int u,v;
		u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	
	init();
	for(int i=1;i<=q;i++) {
		int ins,x,y;
		ins=read(),x=read(),y=read();
		switch(ins) {
			case 1:T.change(1,1,n,id[x],y);break;
			case 2:printf("%d\n",ask(x,y));break;
		}
	}
	
	return 0;
}
```

---

## 作者：K2sen (赞：1)

## 题目大意
1 i v，表示将 e_ie i修改为 vv 。

2 i j，表示询问从景点 i到景点 j的路线的享受值为多少。
## solution
树链剖分+线段树（单线修改+区间异或）

注意^的优先级比=小

要写成这样

>tree[rt].sum = (tree[lson].sum ^ tree[rson].sum);

## code
```cpp
/*
	Auther:_Destiny
	time:2020.5.4
*/
#include <bits/stdc++.h>
#define ll long long
#define N 100010
#define M 1010

using namespace std;
int n, m;
int pre[N], w[N], dep[N], top[N], siz[N], fath[N], son[N], dfn[N];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

namespace Seg {
	#define lson rt << 1
	#define rson rt << 1 | 1
	struct node {
		int sum;
	}tree[N << 2];
	void push_up(int rt) {
		tree[rt].sum = (tree[lson].sum ^ tree[rson].sum);
	}
	void build(int rt, int l, int r) {
		if (l == r) {
			tree[rt].sum = w[pre[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		push_up(rt);
	}
	void update(int rt, int c, int l, int r, int pow) {
		if (l == r) {
			tree[rt].sum = c;
			return;
		}
		int mid = (l + r) >> 1;
		if (pow <= mid) update(lson, c, l, mid, pow);
		else update(rson, c, mid + 1, r, pow);
		push_up(rt);
	}
	int query(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) return tree[rt].sum;
		int mid = (l + r) >> 1, ans = 0;
		if (L <= mid) ans ^= query(lson, l, mid, L, R);
		if (R > mid) ans ^= query(rson, mid + 1, r, L, R);
		return ans;
	}
}

namespace Cut {
	int head[N << 1], add_edge, cnt;
	struct node {
		int next, to;
	}edge[N << 1];
	void add(int from, int to) {
		edge[++add_edge].next = head[from];
		edge[add_edge].to = to;
		head[from] = add_edge;
	}
	void dfs(int x, int fa) {
		fath[x] = fa, dep[x] = dep[fa] + 1, siz[x] = 1;
		for (int i = head[x]; i; i = edge[i].next) {
			int to = edge[i].to;
			if (to == fa) continue;
			dfs(to, x), siz[x] += siz[to];
			if (siz[son[x]] < siz[to]) son[x] = to;
		}
	}
	void dfs2(int x, int tp) {
		dfn[x] = ++cnt, pre[cnt] = x, top[x] = tp;
		if (son[x]) dfs2(son[x], tp);
		for (int i = head[x]; i; i = edge[i].next) {
			int to = edge[i].to;
			if (to == fath[x] || to == son[x]) continue;
			dfs2(to, to);
		}
	}
	int ask(int x, int y) {
		int ans = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			ans ^= Seg::query(1, 1, n, dfn[top[x]], dfn[x]);
			x = fath[top[x]];
		}
		if (dfn[x] > dfn[y]) swap(x, y);
		ans ^= Seg::query(1, 1, n, dfn[x], dfn[y]);
		return ans;
	}
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) 
		w[i] = read();
	for (int i = 1, x, y; i <= n - 1; i++) {
		x = read(), y = read();
		Cut::add(x, y), Cut::add(y, x);
	}
	Cut::dfs(1, 1), Cut::dfs2(1, 1), Seg::build(1, 1, n);
	for (int i = 1, opt, x, y; i <= m; i++) {
		opt = read();
		if (opt == 1) {
			x = read(), y = read();
			Seg::update(1, y, 1, n, dfn[x]);
		}
		if (opt == 2) {
			x = read(), y = read();
			printf("%d\n", Cut::ask(x, y));
		}
	}
	return 0;
}
```

---

## 作者：yu__xuan (赞：1)

水篇题解，不然咕值掉没了。/kk

### 题目
[P6098 【[USACO19FEB]Cow Land G】](https://www.luogu.com.cn/problem/P6098)

### 思路
树链剖分。需要用到的操作有单点修改和区间查询。

0.单点修改
```cpp
void update(int x,int k,int now) {//就是线段树的单点修改。
	if(tree[now].l==tree[now].r) {//找到了要改的点
		tree[now].w=k;return;
	}
	int mid=(tree[now].l+tree[now].r)>>1;
	if(x<=mid) update(x,k,lson);//要改的点在当前区间的左边
	else update(x,k,rson);//在右边
	tree[now].w=(tree[lson].w^tree[rson].w);//合并一下小区间的到大区间的值。
}
```

0.区间查询
```cpp
int ask(int x,int y) {//用于将一条路径分成好几个在线段树上连续的链。
	int ans=0;
	while(top[x]!=top[y]) {//当两点不在同一条链上时
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);//先跳链顶深度大的点。
		ans^=Seg::query(dfn[top[x]],dfn[x],1);//答案异或上这条链的值。
		x=fa[top[x]];//跳到这条链的链顶的父亲
	}
	if(dep[x]>dep[y]) std::swap(x,y);//两个点在一条链上处理一下这条链。
	ans^=Seg::query(dfn[x],dfn[y],1);
	return ans;
}
int query(int x,int y,int now) {//线段树区间查询
	if(tree[now].l>=x&&tree[now].r<=y) return tree[now].w;
	int mid=(tree[now].l+tree[now].r)>>1,ans=0;
	if(x<=mid) ans^=query(x,y,lson);
	if(y>mid) ans^=query(x,y,rson);
	return ans;
}
```
### Code
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define MAXN 100001

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int n,q,dfn[MAXN],pre[MAXN],w[MAXN],size[MAXN];

namespace Seg {
	#define lson now<<1
	#define rson now<<1|1
	struct Node {
		int l,r,w;
	}tree[MAXN<<2];
	void build(int l,int r,int now) {
		tree[now].l=l,tree[now].r=r;
		if(tree[now].l==tree[now].r) {
			tree[now].w=w[pre[l]];return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		build(l,mid,lson),build(mid+1,r,rson);
		tree[now].w=(tree[lson].w^tree[rson].w);
	}
	void update(int x,int k,int now) {
		if(tree[now].l==tree[now].r) {
			tree[now].w=k;return;
		}
		int mid=(tree[now].l+tree[now].r)>>1;
		if(x<=mid) update(x,k,lson);
		else update(x,k,rson);
		tree[now].w=(tree[lson].w^tree[rson].w);
	}
	int query(int x,int y,int now) {
		if(tree[now].l>=x&&tree[now].r<=y) return tree[now].w;
		int mid=(tree[now].l+tree[now].r)>>1,ans=0;
		if(x<=mid) ans^=query(x,y,lson);
		if(y>mid) ans^=query(x,y,rson);
		return ans;
	}
}

namespace Cut {
	int cnt,pthn,head[MAXN],dep[MAXN];
	int top[MAXN],son[MAXN],fa[MAXN];
	struct Edge {
		int next,to;
	}pth[MAXN<<1];
	void add(int from,int to) {
		pth[++pthn].to=to,pth[pthn].next=head[from];
		head[from]=pthn;
	}
	void dfs1(int u,int father) {
		dep[u]=dep[father]+1,fa[u]=father,size[u]=1;
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=father) {
				dfs1(x,u),size[u]+=size[x];
				if(size[son[u]]<size[x]) son[u]=x;
			}
		}
	}
	void dfs2(int u,int tp) {
		top[u]=tp,dfn[u]=++cnt,pre[cnt]=u;
		if(son[u]) dfs2(son[u],tp);
		for(int i=head[u];i;i=pth[i].next) {
			int x=pth[i].to;
			if(x!=fa[u]&&x!=son[u]) dfs2(x,x);
		}
	}
	int ask(int x,int y) {
		int ans=0;
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			ans^=Seg::query(dfn[top[x]],dfn[x],1);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) std::swap(x,y);
		ans^=Seg::query(dfn[x],dfn[y],1);
		return ans;
	}
}

int main() {
	read(n);read(q);
	for(int i=1;i<=n;++i) read(w[i]);
	for(int i=1,u,v;i<n;++i) {
		read(u),read(v);
		Cut::add(u,v),Cut::add(v,u);
	}
	Cut::dfs1(1,1),Cut::dfs2(1,1),Seg::build(1,n,1);
	for(int i=1,opt,x,y;i<=q;++i) {
		read(opt),read(x),read(y);
		if(opt==1) Seg::update(dfn[x],y,1);
		else printf("%d\n",Cut::ask(x,y));
	}
	return 0;
}
```

---

## 作者：Martin_MHT (赞：1)

不用树剖，但是码的丑，勉强看看

这道题朴素的一个想法是维护每个点岛根节点的路径上的所有点的异或的结果，设其为$dis[i]$，修改的时候暴力维护$dis$，查询的时候只需知道$dis[u]$, $dis[v]$和$e[lca(u,v)]$。

考虑优化，发现一个点的$e$值有更改，影响到的是整个子树的$dis$。  
那么我们就需要一个数据结构，维护单点查询，子树修改（雾）

考虑把一棵树拉成一个序列，有一个简单的结论是一棵子树里面的点的$dfs$序是连续的，就可以根据$dfs$序开一棵线段树，维护区间修改，单点查询，下标为每个点的$dfs$序。

时间复杂度$O(nlogn)$，也许比树剖快。

```cpp
#include <cstdio>
#define N 100010
#define fo(i, a, b) for(int i = (a); i <= (b); ++i)
#define fd(i, a, b) for(int i = (a); i >= (b); --i)
struct Edge
{
	int v, x;
}edge[N << 1];
int n, q, d, len, t[N], dep[N], f[N][20], a[N], e[N], head[N], dfn[N], siz[N];
void add(int u, int v)
{
	edge[++len] = (Edge){v, head[u]};
	head[u] = len;
}
int tree[N << 2], tag[N << 2];
inline int ck(int l, int r){return (r - l + 1) & 1;}
inline int ls(int t){return t << 1;}
inline int rs(int t){return t << 1 | 1;}
void pushdown(int t, int l, int r)
{
	int lt = ls(t), rt = rs(t);
	tag[lt] ^= tag[t], tag[rt] ^= tag[t];
	int mid = (l + r) >> 1;
	tree[lt] ^= (ck(l, mid) * tag[t]);
	tree[rt] ^= (ck(mid + 1, r) * tag[t]);
	tag[t] = 0;
}
void pushup(int t){tree[t] = tree[ls(t)] ^ tree[rs(t)];}
void update(int t, int l, int r, int fl, int fr, int val)
{
	if(fl <= l && r <= fr)
	{
		tree[t] ^= (ck(l, r) * val); tag[t] ^= val;
		return ;
	}
	pushdown(t, l, r);
	int mid = (l + r) >> 1;
	if(fl <= mid)	update(ls(t), l, mid, fl, fr, val);
	if(fr > mid)	update(rs(t), mid + 1, r, fl, fr, val);
	pushup(t);
}
int query(int t, int l, int r, int w)
{
	if(l == r)	return tree[t];
	pushdown(t, l, r);
	int mid = (l + r) >> 1;
	if(w <= mid)	return query(ls(t), l, mid, w);
	else	return query(rs(t), mid + 1, r, w);
}
void dfs(int u, int fat)
{
	siz[u] = 1;
	dfn[u] = ++d;
	a[u] ^= a[fat];
	dep[u] = dep[fat] + 1;
	f[u][0] = fat;
	fo(i, 1, 19)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = head[u]; i; i = edge[i].x)
	{
		int v = edge[i].v;
		if(v == fat)	continue ;
		dfs(v, u);
		siz[u] += siz[v];
	}
}
void build(int t, int l, int r)
{
	if(l == r)
	{
		tree[t] = e[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls(t), l, mid); build(rs(t), mid + 1, r);
	pushup(t);
}
int lca(int u, int v)
{
	if(dep[u] < dep[v]){int t = u; u = v; v = t;}
	fd(i, 19, 0)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(u == v)	return u;
	fd(i, 19, 0)
		if(f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}
int main()
{
	freopen("cowland.in", "r", stdin);
	freopen("cowland.out", "w", stdout);
	scanf("%d %d", &n, &q);
	int u, v;
	fo(i, 1, n)	scanf("%d", &a[i]), t[i] = a[i];
	fo(i, 2, n)
	{
		scanf("%d %d", &u, &v);
		add(u, v); add(v, u);
	}
	dfs(1, 0);
	fo(i, 1, n)	e[dfn[i]] = a[i];
	build(1, 1, n);
	fo(i, 1, n)	e[dfn[i]] = t[i];
	fo(i, 1, q)
	{
		int tp;
		scanf("%d", &tp);
		if(tp == 1)
		{
			scanf("%d", &u);
			update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, e[dfn[u]]);
			scanf("%d", &e[dfn[u]]);
			update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, e[dfn[u]]);
		}
		else
		{
			scanf("%d %d", &u, &v);
			int fkw = lca(u, v);
			u = query(1, 1, n, dfn[u]);
			v = query(1, 1, n, dfn[v]);
			printf("%d\n", u ^ v ^ e[dfn[fkw]]);
		}
	}
	return 0;
}
```


别问我为什么变量名叫fkw，问就是某游某池沉了

---

## 作者：Samuel_YHL (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6098)  
# 题意
给你一个有$N$个节点的树， 其中每个点$i$都有一个值$ei$，现在给出$M$个操作，要求你完成这些操作

一共有两种操作:  
$\qquad$	第一种：$1$ $x$ $y$ 表示将第$i$个点的值改为$y$  
$\qquad$   第二种：$2$ $x$ $y$ 表示询问第$x$个点到第$y$个点的路径上所有点的异或值  
# 思路
看到区间查询和单点修改，很容易就可以想到线段树或树状数组，并且是在一棵树的查询和修改，正解显然就是树链剖分。

但是这里有一个比较奇怪的东西，就是区间查询的不是和，而是异或值。有的人可能会以为不能用线段树维护，但其实是可以的！  

因为异或值是满足交换律和结合律的  
也就是说

$a$ $xor$ $b$ = $b$ $xor$ $a$ 并且  $a\; xor\; \left(b\; xor\; c\right)$ = $\left(a\; xor\; b\right)\; xor\; c$  

感性证明一下：  

有10010、11001、01100三个数，要求他们的异或值，那么最终的答案上的每一位只跟原来每一位上有奇数个1还是偶数个1相关，很显然每一位上的1的奇偶性是不会变的，所以无论怎么交换位置，答案也不会变，也就是满足交换律和结合律。

那么接下来就好办了，只需要把线段树维护的值改成异或值就OK了，剩下的就是裸的树剖了
# 代码
~~又到了大家喜闻乐见的放代码环节~~
```
#include <cstdio>
#include <algorithm>
#define maxn 100010
using namespace std;
struct EDGE
{
	int to, next;
}edge[maxn << 1];
int t[maxn << 2];
int n, m;
int head[maxn], cxk, cnt, ans;
int a[maxn], w[maxn], son[maxn], dep[maxn], f[maxn], id[maxn], top[maxn], size[maxn];
void add(int u, int v)
{
	edge[++cxk].next = head[u];
	edge[cxk].to = v;
	head[u] = cxk;
	return;
}
void build(int wz, int l, int r)
{
	if (l == r)
	{
		t[wz] = w[l];
		return;
	}
	int mid = (l + r) /2;
	build(wz * 2, l, mid);
	build(wz * 2 + 1, mid + 1, r);
	t[wz] = t[wz * 2] ^ t[wz * 2 + 1];
	return;
}
void update(int wz, int l, int r, int x, int kkk)
{
	if (l == x && r == x)
	{
		t[wz] = kkk;
		return;
	}
	int mid = (l + r) / 2;
	if (mid + 1 <= x)
		update(wz * 2 + 1, mid + 1, r, x, kkk);
	else
		update(wz * 2, l, mid, x, kkk);
	t[wz] = t[wz * 2] ^ t[wz * 2 + 1];
	return;
}
void sum(int wz, int l, int r, int x, int y)
{
	if (l >= x && r <= y)
	{
		ans ^= t[wz];
		return;
	}
	int mid = (l + r) / 2;
	if (mid + 1 <= y)
		sum(wz * 2 + 1, mid + 1, r, x, y);
	if (mid >= x)
		sum(wz * 2, l, mid, x, y);
	return;
}
void query(int x, int y)
{
	ans = 0;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		sum(1, 1, n, id[top[x]], id[x]);
		x = f[top[x]];
	}
	if (dep[x] > dep[y])
		swap(x, y);
	sum(1, 1, n, id[x], id[y]);
	return;
}
void dfs1(int u, int fa)
{
	int mx = -1, d = 0;
	dep[u] = dep[fa] + 1;
	f[u] = fa;
	size[u] = 1;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == fa)
			continue;
		dfs1(v, u);
		size[u] += size[v];
		if (size[v] > mx)
		{
			mx = size[v];
			d = v;
		}
	}
	son[u] = d;
	return;
}
void dfs2(int u, int tf)
{
	top[u] = tf;
	id[u] = ++cnt;
	w[cnt] = a[u];
	if (son[u] == 0)
		return;
	dfs2(son[u], tf);
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == f[u] || v == son[u])
			continue;
		dfs2(v, v);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			update(1, 1, n, id[x], y);
		else
		{
			query(x, y);
			printf("%d\n", ans);
		}
	}
	return 0;
}

```
## 最后的话
这是本蒟蒻第二次写的题解，可能会有很多不足的地方，不喜勿喷。  
如果我有什么说错了，可以在评论区说出来或者私信我也可以。  
最后放上一个[树剖的教学](https://www.cnblogs.com/chinhhh/p/7965433.html)，我就是在这里学会的，不会树剖的小盆友可以参考一下

---

## 作者：pocafup (赞：1)

~~震惊,蒟蒻学树剖第二天就打题解~~

所以说,理解之后树剖这种东西其实难度真心不大.至少这种模板题都可以秒切的

这里推荐一个博客: [树剖详解](https://www.cnblogs.com/chinhhh/p/7965433.html)
蒟蒻就是在这个博客上学到的

如果想看我自己写的总结,请点 [我的博客](https://www.cnblogs.com/DannyXu/p/12372291.html)
这个链接(~~虽然这个是写给自己看的,理解难度应该不小~~)

树剖的方法在博客上都有了,在这里不细讲,专注讲一下这题的实现:

$dfs$ 请使用博客上的方法,这题需要做的只是照搬

首先,我们可以发现,这题跟普通的树剖基本上一样.唯一的区别就是他要使用 $xor$ .那么,我们发现, $xor$ 的操作其实跟加减没有任何区别.于是,我们只需要将加减法换成 $xor$, 这题的操作就实现了

1.update
update跟正常的线段树update没有区别,而且他不需要lazy,因为他只需要update一个点.所以我们仍然是二分查找,找到就二分,然后他的父亲就更新为左儿子 $xor$ 右儿子.
我们还可以观察到,如果更新右儿子,那么左儿子就不用更新了.因此,这个更新速度是恒定的 $O(logn)$

```cpp
void update(int way, int l, int r, int q, int val){
  if (q<l || q>r) return;//不在范围内(其实用处不大)
  if (l==r && r==q) {seg[way]=val;return;}//刚好是这个数就更新
  if (l==r) return;//否则不更新
  int mid = (l+r)/2;
  if (q<=mid)update(way*2,l,mid,q,val);//在左儿子的区间
  if (q>mid)update(way*2+1,mid+1,r,q,val);//在右儿子的区间
  seg[way]  =seg[way*2]^seg[way*2+1];//用儿子更新父亲
}
```

2.query

这题的难点来了:怎么拿路径

我们可以发现,取两点之间的路径相当于分别取两点到他俩 $lca$ 的值.

再观察,我们发现,在取 $lca$ 途中答案可以直接更新,因为去lca的路径只有一条,所以,我们每次query的时候先将答案设成0,每次网上跳区间的时候答案就是 $ans^区间$

```cpp
int query_up(int way, int l, int r, int qlow, int qhigh){
  if (qlow<= l && r<=qhigh) return seg[way];//完全包围
  if (l>qhigh || r<qlow) return 0;//不在范围

  int mid = (l+r)/2;
  return (query_up(way*2,l,mid,qlow,qhigh) ^ query_up(way*2+1,mid+1,r,qlow,qhigh));//左儿子^右儿子
}
int query(int x, int y){
  int ans = 0;//设答案为0
  while(top[x]!=top[y]){//如果不在同一条链
    if (dep[top[x]]<dep[top[y]]) swap(x,y);//谁高谁低
    ans ^= query_up(1,1,n,id[top[x]],id[x]);//更新答案
    x = fat[top[x]];//跳到上面那条链
  }
  if (dep[x]>dep[y]) swap(x,y);
  ans ^= query_up(1,1,n,id[x],id[y]);//找本链的值
  return ans;
}
```

完整代码:
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
const int MAXN = 1e5+5;
int res = 0;
int n,m,r,p,dep[MAXN],fat[MAXN],son[MAXN],sz[MAXN],num[MAXN],id[MAXN],top[MAXN],wt[MAXN],cnt=0,head[MAXN],tot = 0;
int seg[MAXN*4],lazy[MAXN*4];
vector<int> adj[MAXN];
void dfs1(int pos, int f, int depth){
  dep[pos] = depth;
  fat[pos] = f;
  sz[pos] = 1;
  int maxi = -1;
  for (int v : adj[pos]){
    if (v == f) continue;
    dfs1(v,pos,depth+1);
    sz[pos]+=sz[v];
    if (maxi<sz[v]) {maxi = sz[v];son[pos] = v;}
  }
}
bool vis[MAXN];
void dfs2(int pos, int top_pos){
  id[pos] = ++cnt;
  wt[cnt] = num[pos];
  top[pos] = top_pos;
  if (!son[pos]) return;
  dfs2(son[pos],top_pos);
  for (int v : adj[pos]){
    if (v==fat[pos] || v==son[pos])  continue;
    dfs2(v,v);
  }
}//树剖的基础dfs
void make_tree(int way, int l, int r){
  if (l==r) {seg[way] = wt[l];return;}
  int mid = (l+r)/2;
  make_tree(way*2,l,mid);
  make_tree(way*2+1,mid+1,r);
  seg[way] = seg[way*2] ^seg[way*2+1] ;
}//建树
void update(int way, int l, int r, int q, int val){
  if (q<l || q>r) return;
  if (l==r && r==q) {seg[way]=val;return;}
  if (l==r) return;
  int mid = (l+r)/2;
  if (q<=mid)update(way*2,l,mid,q,val);
  if (q>mid)update(way*2+1,mid+1,r,q,val);
  seg[way]  =seg[way*2]^seg[way*2+1];
}//更新
int query_up(int way, int l, int r, int qlow, int qhigh){
  if (qlow<= l && r<=qhigh) return seg[way];
  if (l>qhigh || r<qlow) return 0;

  int mid = (l+r)/2;
  return (query_up(way*2,l,mid,qlow,qhigh) ^ query_up(way*2+1,mid+1,r,qlow,qhigh));
}//求区间
int query(int x, int y){
  int ans = 0;
  while(top[x]!=top[y]){
    if (dep[top[x]]<dep[top[y]]) swap(x,y);
    ans ^= query_up(1,1,n,id[top[x]],id[x]);
    x = fat[top[x]];
  }
  if (dep[x]>dep[y]) swap(x,y);
  ans ^= query_up(1,1,n,id[x],id[y]);
  return ans;
}//求链
int main(){
  cin >> n >> m;
  for (int i=1;i<=n;i++) cin >> num[i];
  for (int i=0;i<n-1;i++){
    int a,b; cin >> a  >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs1(1,0,1);
  dfs2(1,1);
  make_tree(1,1,n);
  //初始化
  for (int i=0;i<m;i++){
    int ind,a,b; cin >> ind >> a >> b;
    if (ind==1){
      update(1,1,n,id[a],b);
    }else{
      cout << query(a,b) << endl;
    }//操作
  }
}
```
复杂度 $O(nlog^2n)$ 可以过

做完建议去做P3384,本蒟蒻就是做了那题才恍然大悟的


---

## 作者：MuYC (赞：0)

#### 前言

比较常见的树链剖分题。

前置知识：线段树 + 树链剖分

这类维护区间位运算的题目往往采用：拆位线段树维护。

#### 思路

笔者默认做题者会树链剖分，这里就简单讲讲拆位线段树。

考虑到区间异或和，影响答案的只有区间内的数二进制下的某几位是否为$1$，于是我们很自然的将问题分解为：

+ 区间内的所有数中，二进制下第 $i$ 位为 $1$ 的数一共有多少个？

知道了这个我们就很容易得到最后的答案了。

很显然的一点，假设区间内第 $i$ 为 $1$ 的数一共有奇数个，那么这一位是可以贡献给最终答案的，答案就加上 $1 << i$ 。如果是偶数它的贡献会被异或消除为 $0$ ，对最终答案没有影响。

+ 修改操作

我们实际上只需要单点修改某个位置上的线段树值即可。

于是就直接清空线段树上这个点的所有值，按照给出的数来进行按位分解后统计即可。

#### 具体做法：

线段树中存储区间 $[L,R]$ 中第 $i$ 位为 $1$ 的数的个数，记作 $cnt[i]$

然后对于每一次查询，我们就开一个全局数组（用一次就得清空一次），按照线段树的传统做法，对于完全被包含的就将线段树中的值加入到这个数组中。传统线段树即可。

对于每次修改，找到 $pos$(修改的点) ，然后将当前点的对应的线段树的$cnt$ 数组清空，然后将给定的值转为二进制，暴力统计第 $i$ 位是否为 $1$ 即可。

代码实现可以看下面的 "$Code$" 部分，有注释。

时间复杂度：O($nlog^2n * 32$)(其实是跑不满的，效率还蛮高的)

#### $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int start[MAXN],n,tot = 0,Q,now = 0;
int dep[MAXN],siz[MAXN],son[MAXN],fa[MAXN];
int dfn[MAXN],dfn_id[MAXN],tp[MAXN],val[MAXN],Ans[35];//Ans就是上文提到的全局数组

struct Edge {
    int to,next;
} edge[MAXN * 2];

struct SegmentTree {
    int l,r;
    int cnt[33];
} T[MAXN * 4];

inline int read()
{
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

void add(int from,int to)
{
    tot ++;
    edge[tot].to = to;
    edge[tot].next = start[from];
    start[from] = tot;
    return ;
}

int DFS1(int x,int from)//树链剖分DFS1
{
    siz[x] = 1 , dep[x] = dep[from] + 1;
    son[x] = 0 , fa[x] = from;
    for(int i = start[x] ; i ; i = edge[i].next)
    {
        int to = edge[i].to;
        if(to == from) continue;
        int v = DFS1(to,x);
        if(v > siz[son[x]]) son[x] = to;
        siz[x] += v;
    }
    return siz[x];
}

void DFS2(int x,int top)//树链剖分DFS2
{
    tp[x] = top , dfn[x] = ++now , dfn_id[now] = x;
    if(son[x]) DFS2(son[x],top);
    for(int i = start[x] ; i ; i = edge[i].next)
    {
        int to = edge[i].to;
        if(to == fa[x] || to == son[x]) continue;
        DFS2(to, to);
    }
    return ;
}

void build(int x,int l,int r)
{
    T[x].l = l , T[x].r = r;
    if(l == r)
    {
        int D = val[dfn_id[l]],len = 0;
        while(D)//进行二进制分解
        {
            T[x].cnt[++len] += (D & 1);
            D >>= 1;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    build(x << 1 , l , mid);
    build(x << 1 | 1 , mid + 1 , r);
    for(int i = 1 ; i <= 32 ; i ++)//直接暴力的将两个儿子的值给获取掉
        T[x].cnt[i] = T[x << 1].cnt[i] + T[x << 1 | 1].cnt[i];
    return ;
}

void change(int x,int pos,int k)
{
    if(T[x].l == dfn[pos] && T[x].r == dfn[pos])
    {
        int D = val[pos],len = 0;
        while(D)//常数优化，因为直接全部清空太浪费了，有些本来就没被访问
        {
            T[x].cnt[++len] -= (D & 1);
            D >>= 1;
        }
        D = k;
        len = 0;
        while(D)
        {
            T[x].cnt[++len] += (D & 1);
            D >>= 1;
        }
        val[pos] = k;//上面的常数优化需要知道当前点的被修改前的值为多少，所以要保存
        return ;
    }
    int mid = (T[x].l + T[x].r) >> 1;
    if(dfn[pos] <= mid) change(x << 1 , pos , k);
    else change(x << 1 | 1 , pos , k);
    for(int i = 1 ; i <= 32 ; i ++)
        T[x].cnt[i] = T[x << 1].cnt[i] + T[x << 1 | 1].cnt[i];
    return ;
}

void Get(int x,int l,int r)
{
    if(T[x].l >= l && T[x].r <= r)
    {
        for(int i = 1 ; i <= 32 ; i ++) 
        Ans[i] += T[x].cnt[i];//上文提到的将线段树中的值暴力加入答案中
        return ;
    }
    int mid = (T[x].l + T[x].r) >> 1;
    if(l <= mid) Get(x << 1 , l , r);
    if(r  > mid) Get(x << 1 | 1 , l , r);
    return ;
}

void GetAns(int x,int y)//树链剖分模板
{
    while(tp[x] != tp[y])
    {
        if(dep[tp[x]] < dep[tp[y]]) swap(x,y);
        Get(1 , dfn[tp[x]] , dfn[x]);
        x = fa[tp[x]];
    }
    if(dfn[x] < dfn[y]) Get( 1 , dfn[x] , dfn[y]);
    else Get(1 , dfn[y] , dfn[x]);
    return ;
}

int main()
{
    n = read() , Q = read();
    for(int i = 1 ; i <= n ; i ++) val[i] = read();
    for(int i = 1 ; i <= n - 1 ; i ++)
    {
        int u = read() , v = read();
        add(u,v); add(v,u);
    }
    DFS1(1,0);
    DFS2(1,1);
    build(1 , 1 , n);
    while(Q -- )
    {
        int op = read() , l = read() , r = read();
        if(op == 1) change( 1 , l , r);
        else 
        {
            memset(Ans,0,sizeof(Ans));//每次用都要清空
            GetAns( l , r );
            int sum = 0;
            for(int j = 1 ; j <= 32 ; j ++)
            if(Ans[j] & 1) sum += (1 << (j - 1));//是奇数的话就对答案有贡献
            //注意这里要减一，因为分解的时候第1位相当于2的0次方
            printf("%d\n",sum);
        }
    }
    return 0;
}
```

---

## 作者：StupidSeven (赞：0)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/P6098)
 
## Analysis
树链剖分板子+线段树单点修改+区间异或

## Solution
树剖板子和单点修改就不了讲，区间异或其实就是在每次更新和查询时取异或值，也是个板子，具体见代码

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define M 5000010
#define int long long
inline int read(){
	int s=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){s=s*10+c-48;c=getchar();}
	return s*f;
}
struct node{
	int u,v;
}Edge[M];
struct SegTree{
	int lson,rson,x;
}tree[M<<2];
int n,m,u,v,opt,cnt,tot,head[M];
int siz[M],son[M],fat[M],dep[M],top[M],idx[M],rk[M],value[M];
void addEdge(int u,int v){
	Edge[++cnt]=(node){head[u],v};
	head[u]=cnt;
	return;
}
void dfs1(int u,int dad){
	siz[u]=1;fat[u]=dad;
	dep[u]=dep[dad]+1;
	for(int i=head[u];i;i=Edge[i].u){
		int v=Edge[i].v;
		if(v==dad) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}
	return;
}
void dfs2(int u,int dad){
	top[u]=dad;
	idx[u]=++tot;
	rk[tot]=u;
	if(!son[u]) return;
	dfs2(son[u],dad);
	for(int i=head[u];i;i=Edge[i].u){
		int v=Edge[i].v;
		if(v!=son[u]&&v!=fat[u])
			dfs2(v,v);
	}
	return;
}
void UpDate(int index){
	tree[index].x=tree[index<<1].x^tree[index<<1|1].x;
	return;
}
void BuildTree(int index,int lson,int rson){
	tree[index]=(SegTree){lson,rson};
	if(lson==rson){
		tree[index].x=value[rk[lson]];
		return;
	}
	int mid=(lson+rson)>>1;
	BuildTree(index<<1,lson,mid);
	BuildTree(index<<1|1,mid+1,rson);
	UpDate(index);
	return;
}
void Change(int index,int lson,int rson,int x,int k){
	if(lson==rson){
		tree[index].x=k;
		return;
	}
	int mid=(lson+rson)>>1;
	if(x<=mid) Change(index<<1,lson,mid,x,k);
	else Change(index<<1|1,mid+1,rson,x,k);
	UpDate(index);
	return;
}
int Query(int index,int lson,int rson){
	if(lson<=tree[index].lson&&tree[index].rson<=rson)
		return tree[index].x;
	int mid=(tree[index].lson+tree[index].rson)>>1,ans=0;
	if(lson<=mid) ans^=Query(index<<1,lson,rson);
	if(rson>mid) ans^=Query(index<<1|1,lson,rson);
	return ans;
}
int TreeQuery(int u,int v){
	int ans=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans^=Query(1,idx[top[u]],idx[u]);
		u=fat[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans^=Query(1,idx[u],idx[v]);
	return ans;
}
signed main(void){
	n=read();m=read();
	for(int i=1;i<=n;i++) value[i]=read();
	for(int i=1;i<n;i++){
		u=read();v=read();
		addEdge(u,v);
		addEdge(v,u);
	}
	dfs1(1,0);dfs2(1,1);
	BuildTree(1,1,n);
	while(m--){
		opt=read();u=read();v=read();
		if(opt==1) Change(1,1,n,idx[u],v);
		else printf("%lld\n",TreeQuery(u,v));
	}
	return 0;
}
```


---

## 作者：ztasd (赞：0)

看到各位大佬们已经把其他的东西讲的很明白了，我这个 juruo 就讲一讲最基本的树链剖分吧。

## 0.树剖是什么？~~能吃吗？~~

~~不能吃~~

树剖是树链剖分的简称，我们一般说的树剖其实指**重链剖分**。当然，还有一种长链剖分~~我不会~~，但是据说不常用。

树链剖分能够把树剖分成许多链，这样就可以用维护区间的方式维护一棵树。

## 1.怎么剖分

先引入一些概念：

1. **重儿子**：一棵树最大的子树叫重儿子。例如这棵树中3就是1的重儿子：![](https://cdn.luogu.com.cn/upload/image_hosting/wvcn1s57.png)很明显，一棵树的重儿子是唯一的。什么？有多棵子树的大小相同？那就随便选一个呗。
2. **轻儿子**：除了重儿子都是轻儿子。~~废话~~
3. **重边**：连接父亲和重儿子的边就是重边。
4. **轻边**：除了重边都是轻边。
5. **重链**：许多重边连起来就叫重链。例如：![](https://cdn.luogu.com.cn/upload/image_hosting/sa0fpyz9.png)

这棵树里节点 $\{1,3,5,6\}$ 可以构成一颗重链。~~很显然~~  ，**每个重链的起点一定是一个轻儿子。每个节点都属于且仅属于一条重链。**<-很重要，一定要记住！

然后就开始剖分了。

具体的剖分过程，就是维护一些数组：
* $deep[i]$ 代表节点 $i$ 的深度。
* $top[i]$ 代表节点 $i$ 所属重链的链顶。（也就是重链里深度最小的那个节点）
* $size[i]$ 代表以 $i$ 为根的子树的大小。
* $son[i]$ 代表节点 $i$ 的唯一一个重儿子是谁。
* $f[i]$ 代表节点 $i$ 的父亲是谁。
* $dfn[i]$ 代表节点 $i$ 的”遍历顺序“。

剖分时要跑两个dfs。~~经典操作~~

第一个dfs要维护 $size$ 、$son$ 、$f$、$deep$ 这几个数组。

提示：树要用无向图存！

```cpp
void dfs1(int u,int fa/*记录当前节点父亲是谁*/){
    size[u]=1;//因为自己也是子树的一部分
    f[u]=fa;
    deep[u]=deep[fa]+1;//很明显，当前深度=父亲深度+1
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];//遍历每个出边
        if(v!=fa){//如果当前出边终点是儿子而不是父亲
            dfs1(v,u);//搜
            size[u]+=size[v];//加上儿子大小
            if(size[v]>size[son[u]]){//找到最大的儿子作为重儿子
                son[u]=v;
            }
        }
    }
}
```
然后我们已经知道了每个节点的重儿子，现在应该把它们连起来成为一条重链了：
```cpp
void dfs2(int u,int tp/*当前链顶*/){
    top[u]=tp;
    dfn[u]=++step;
    if(son[u]){//如果没有重儿子，那么一个儿子也没有
        dfs2(son[u],tp);//优先遍历重儿子，为什么之后再说
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i];
            if(son[u]!=v&&f[u]!=v){//遍历轻儿子
                dfs2(v,v);//轻儿子一定是一条重链的链顶
            }
        }
    }
}
```
**如果优先遍历重儿子，那么重链的$dfn$一定是连续的。**例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/3w1daj6g.png)

因为重链的$dfn$是连续的，而每个点都属于一条重链，所以可以用线段树维护区间的方式维护点权，这样就不用暴力的一个个查，一个个改了。

一些常见的用法：
```cpp
query(1,1,n,dfn[top[u]],dfn[u])//查询u到链顶的点权和
modify(1,1,n,dfn[top[u]],dfn[u],3)//把u到链顶的点权都加3
```

具体到题目上，可以发现甚至连懒惰标记都不需要，没有区间修改的操作。

那么，怎么计算从一个点到另外一个点路径上的点权和？
```cpp
int query_ans(int u,int v){
    int ret=0;
    while(top[u]!=top[v]){
        if(deep[top[u]]<deep[top[v]]){//注意，一定要比较链顶深度！坑了我好几次
            swap(u,v);
        }
        ret^=query(1,1,n,dfn[top[u]],dfn[u]);//这道题要求异或
        u=f[top[u]];
    }//就是当uv不在同一条链上时，让链顶深度小的往上跳
    if(deep[u]>deep[v]){
        swap(u,v);
    }
    ret^=query(1,1,n,dfn[u],dfn[v]);//当在同一条链上时，把它们之间的点加起来
    return ret;
}
```

知道了这些操作，这题就非常好写了。就是直接把板子套上去嘛！

AC Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
int n,q,e[MAXN];
vector<int> g[MAXN];
int dfn[MAXN],step,top[MAXN],size[MAXN],son[MAXN],f[MAXN],deep[MAXN];
void dfs1(int u,int fa){
    size[u]=1;
    f[u]=fa;
    deep[u]=deep[fa]+1;
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(v!=fa){
            dfs1(v,u);
            size[u]+=size[v];
            if(size[v]>size[son[u]]){
                son[u]=v;
            }
        }
    }
}
void dfs2(int u,int tp){
    top[u]=tp;
    dfn[u]=++step;
    if(son[u]){
        dfs2(son[u],tp);
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i];
            if(son[u]!=v&&f[u]!=v){
                dfs2(v,v);
            }
        }
    }
}
int tree[MAXN*4];
void push_up(int rt){
    tree[rt]=tree[rt*2]^tree[rt*2+1];
}
void modify(int rt,int l,int r,int x,int k){
    if(l==r){
        tree[rt]=k;
    }else{
        int mid=(l+r)/2;
        if(x<=mid){
            modify(rt*2,l,mid,x,k);
        }else{
            modify(rt*2+1,mid+1,r,x,k);
        }
        push_up(rt);
    }
}
int query(int rt,int l,int r,int L,int R){
    if(L>R){return 0;}
    if(L<=l&&R>=r){
        return tree[rt];
    }else{
        int mid=(l+r)/2,ret=0;
        if(L<=mid){
            ret^=query(rt*2,l,mid,L,R);
        }
        if(R>mid){
            ret^=query(rt*2+1,mid+1,r,L,R);
        }
        return ret;
    }
}
int query_ans(int u,int v){
    int ret=0;
    while(top[u]!=top[v]){
        if(deep[top[u]]<deep[top[v]]){
            swap(u,v);
        }
        ret^=query(1,1,n,dfn[top[u]],dfn[u]);
        u=f[top[u]];
    }
    if(deep[u]>deep[v]){
        swap(u,v);
    }
    ret^=query(1,1,n,dfn[u],dfn[v]);
    return ret;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",e+i);
    }
    for(int i=1;i<=n-1;i++){
        int u,v,w;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        modify(1,1,n,dfn[i],e[i]);
    }
    for(int i=1;i<=q;i++){
        int op;
        scanf("%d",&op);
        if(op==1){
            int x,k;
            scanf("%d%d",&x,&k);
            modify(1,1,n,dfn[x],k);
        }else{
            int u,v;
            scanf("%d%d",&u,&v);
            printf("%d\n",query_ans(u,v));
        }
    }
    return 0;
}
```

完结撒花~

---

## 作者：Unordered_OIer (赞：0)

# P6098 题解
```
              重链剖分裸题
```
## 题意概述
一棵树，动态维护每个结点的权值，查找一条路径的异或和，没有更多了~
## 解答
简简简简化问题：  
如果只有一条链，**没**有修改？  
$$\huge{前缀和！}$$

简简简化问题：
如果只有一条链，**有**修改？
$$\huge{线段树！}$$
##### ~~还不会线段树的自己去敲板子吧~~

简简化问题：
如果是一棵树，**没**有修改？
$$\huge{倍增+LCA！}$$

那么，如果**是一棵树，又有修改呢？**
$$\huge{线段树+倍增+LCA！}$$
即为  
$$\huge{重链剖分！}$$

![](https://ss3.bdstatic.com/70cFv8Sh_Q1YnxGkpoWK1HF6hhy/it/u=2266815608,1859947537&fm=26&gp=0.jpg)
$$\huge{重链剖分是个啥？？？}$$

### 以下为重链剖分基础
父亲结点的所有儿子中子树结点数目最多（$size$最大）的一个结点叫做重儿子，边叫做重边；其余的是轻儿子，边叫做轻边。重边组成重链。  

定理：任意一个点到根的路径上，不超过$\log n$条轻边，也不超过$\log n$条重链  

**显然：重链是不会分叉的！**  
**重链是一段一段的**  
建树的时候按照重链必须连续的原则来建树  
维护重链==维护区间→线段树维护  

这里唯一不同的是，这是$\color{red}{\large异或}$

$So\ what?$

于是代码军来了  
变量含义什么的应该很清楚了(看变量名)
```cpp
#include<bits/stdc++.h>
using namespace sstd;
const int SZ_N=100000;
int st[4*SZ_N];
void stUpdate(int idx,int l,int r,int i,int v){
	if(l==r)st[idx]=v;
	else{
		int m=(l+r)/2;
		if(i<=m)stUpdate(2*idx,l,m,i,v);
		else stUpdate(2*idx+1,m+1,r,i,v);
		st[idx]=st[2*idx]^st[2*idx+1];
	}
}
void stUpdate(int i,int v){
	stUpdate(1,0,SZ_N-1,i,v);
}
int stQuery(int idx,int l,int r,int lhs,int rhs){
	if(l>=lhs&&r<=rhs)return st[idx];
	int ret=0;
	int m=(l+r)/2;
	if(m>=lhs)ret^=stQuery(2*idx,l,m,lhs,rhs);
	if(m+1<=rhs)ret^=stQuery(2*idx+1,m+1,r,lhs,rhs);
	return ret;
}
int stQuery(int l,int r){
	return stQuery(1,0,SZ_N-1,l,r);
}
const int SZ_D=17;
int lca[SZ_N][SZ_D];
int depth[SZ_N];
int getLCA(int a,int b){
	if(depth[a]<depth[b])swap(a,b);
	for(int d=SZ_D-1;d>=0;d--)
		if(depth[a]-(1<<d)>=depth[b])
			a=lca[a][d];
	for(int d=SZ_D-1;d>=0;d--)
		if(lca[a][d]!=lca[b][d]){
			a=lca[a][d];
			b=lca[b][d];
		}
	if(a!=b)a=lca[a][0],b=lca[b][0];
	return a;
}
void initLCA(){
	for(int d=1;d<SZ_D;d++)
		for(int i=0;i<SZ_N;i++)
			lca[i][d]=lca[lca[i][d-1]][d-1];
}
vector<int> edges[SZ_N];
int treesz[SZ_N];
int vtxtoSt[SZ_N];
int tpch[SZ_N];
int vals[SZ_N];
void dfsForHLD(int curr,int topPtr,int par,int& itnSt_idx){
	vtxtoSt[curr]=itnSt_idx++;
	stUpdate(vtxtoSt[curr],vals[curr]);
	tpch[curr]=topPtr;
	int lgstchl=-1;
	int lgstsz=-1;
	for(int out:edges[curr]){
		if(out==par)continue;
		if(treesz[out]>lgstsz){
			lgstsz=treesz[out];
			lgstchl=out;
		}
	}
	if(lgstchl<0)return;
	dfsForHLD(lgstchl,topPtr,curr,itnSt_idx);
	for(int out:edges[curr]){
		if(out==par||out==lgstchl)continue;
		dfsForHLD(out,out,curr,itnSt_idx);
	}
}
void dfsForSize(int curr,int par){
	treesz[curr]++;
	for(int out:edges[curr]){
		if(out==par)continue;
		depth[out]=depth[curr]+1;
		lca[out][0]=curr;
		dfsForSize(out,curr);
		treesz[curr]+=treesz[out];
	}
}
void initHLD(){
	dfsForSize(0,-1);
	initLCA();
	int itnSt_idx=0;
	dfsForHLD(0,0,-1,itnSt_idx);
}
int pathQuery(int chl,int par){
	int ret=0;
	while(chl!=par){
		if(tpch[chl]==chl){
			//轻边
			ret^=vals[chl];
			chl=lca[chl][0];
		}
		else if(depth[tpch[chl]]>depth[par]){
			ret^=stQuery(vtxtoSt[tpch[chl]],vtxtoSt[chl]);
			chl=lca[tpch[chl]][0];
		}
		else{
			ret^=stQuery(vtxtoSt[par]+1,vtxtoSt[chl]);
			break;
		}
	}
	return ret;
}
int query(int a,int b){
	int r=getLCA(a,b);
	return pathQuery(a,r)^pathQuery(b,r)^vals[r];
}
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;i++)cin>>vals[i];
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	initHLD();
	while(q--){
		int t;
		cin>>t;
		if(t==1){
			int i,v;
			cin>>i>>v;
			vals[--i]=v;
			stUpdate(vtxtoSt[i],v);
		}else{
			int a,b;
			cin>>a>>b;
			cout<<query(a-1,b-1)<<"\n";
		}
	}
	return 0;
}
```
如果```for(int out:edge[curr])```不知道什么意思的，你可以这样写：
```cpp
for(int i=0;i<edge[curr].size();i++)
{
    int out=edge[curr][i];
    ...
}
```
注意，两种写法是等价的，但是最开始贴的那种写法有可能无法本地编译通过。

---

