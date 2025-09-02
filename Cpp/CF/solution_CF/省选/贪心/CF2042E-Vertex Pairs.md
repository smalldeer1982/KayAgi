# Vertex Pairs

## 题目描述

给定一个由$ 2n $个顶点组成的树。回想一下，树是一个没有环的连通无向图。每个顶点上都写了一个从$ 1 $到$ n $的整数。从$ 1 $到$ n $的每个值都恰好写在两个不同的顶点上。每个顶点也有成本-顶点$ i $成本$ 2^i $。

你需要选择树的一个顶点子集，如下所示：

- 子集是连通的；也就是说，从子集中的每个顶点，只通过子集中的顶点可达子集中的每个其他顶点；
- 从$ 1 $到$ n $的每个值都至少写在子集中的一个顶点上。

在所有这样的子集中，您需要找到其中顶点的总代价最小的子集。注意，您不需要最小化子集中的顶点数量。

## 样例 #1

### 输入

```
3
1 1 3 2 3 2
4 2
1 6
6 2
6 3
2 5```

### 输出

```
3
2 4 5```

## 样例 #2

### 输入

```
3
2 3 1 3 2 1
6 4
2 4
5 2
3 6
3 1```

### 输出

```
4
1 3 4 6```

## 样例 #3

### 输入

```
6
5 2 3 4 6 4 2 5 6 1 1 3
10 8
2 10
12 7
4 10
5 9
6 2
1 9
3 4
12 6
11 5
4 5```

### 输出

```
6
2 3 4 5 8 10```

# 题解

## 作者：hard_plan (赞：8)

赛时想出来了，~~赛后~~一遍过。好吧，被卡了，原因是写挂了，后面改过了。

感谢 @[Akuto_urusu](https://www.luogu.com.cn/user/312342) 提出可以优化的地方。

## 题意

给定一棵有 $2\times n$ 个节点的树，每个节点都有颜色，颜色在 $[1,n]$ 之间，保证每个颜色出现 $2$ 次。选第 $i$ 个点的代价是 $2^i$。

现在，你需要选出一个集合。你需要使得这个集合内的点互相能通过该集合内的点到达，并且每种颜色都至少在该集合中出现一次。代价为集合内所有点的代价之和。

你需要找出代价最小的集合并给出方案。

## 思路

先考虑这个代价最小的集合的大致求法。

有一个经典技巧，从大到小考虑，如果我们选了 $i$，代价为 $2^i$，而如果我们不选 $i$，对于 $j\in[1,i-1]$，无论我们是否选 $j$，这个代价最多也是 $\sum_{j=1}^{i-1}2^j=2^i-1$，比 $2^i$ 小。

所以按节点编号从大到小考虑，如果能不取该节点就不取（换种说法，也就是删去），否则就取。

那么什么情况下该节点可以不取呢？

根据题目给出的定义，如果删去它后有一个连通块里包含所有颜色就可以不取。

所以我们需要判断一个连通块内是否包含所有颜色。

但是，这个问题有点难解决，至少我不会。

因为删掉节点 $u$ 后，剩下的部分有两种，一种是以 $u$ 的儿子为根的子树，一种是整棵树删去 $u$ 子树后剩下的部分。两种一起处理太困难了。

![](https://cdn.luogu.com.cn/upload/image_hosting/awfrtd67.png)

那么再想想，我们如何做使得只用处理一种，也就是说，另一种一定被取或被删呢？。

记 $col_i$ 为 $i$ 节点的颜色。

假设我们已经找到了一个必取（不可删）的节点 $v$，并让该连通块变成以 $v$ 为根的树。（至于为什么是连通块而不是整个图，后面会说）

那么这样我们再考虑删点时，惊奇地发现——因为树根 $v$ 是不能删的，所以删去的只能是子树部分。那么删去点 $u$ 就相当于删去了以 $u$ 为根的这棵子树！

（图为示意图，隐去了节点颜色等信息）
![](https://cdn.luogu.com.cn/upload/image_hosting/6k8lpcm9.png)

然后如何判断一个节点是否能删呢？

如果直接去搜索删完后剩下的部分是否有所有颜色太慢了，所以考虑把所有不能删的节点全部标记，没被标记的就可以删。

如果节点 $i,j$ 满足 $col_i=col_j(i\neq j)$，那么 $i,j$ 的所有公共祖先都不能删，因为如果删了，$col_i$ 这种颜色就不存在于这个连通块中了。所以将 $i,j$ 的所有公共祖先标记一下不能删。

但是有一些颜色初始时在这个连通块中就只有一个节点了，那么这个节点的所有祖先都不能删。

（节点黑色圆圈内为编号，圆圈外为节点的颜色）

![](https://cdn.luogu.com.cn/upload/image_hosting/p287fmb6.png)

处理完后，从大到小遍历所有还没被删的点，如果没被标记就把它删掉。但是删掉该子树后，有些颜色的出现次数变成 $1$ 了，此时仅存的那个该颜色的点的祖先都不能取。所以暴力遍历要删的子树的所有节点，对于另一个同颜色的点，对其所有祖先进行标记。

按照从大到小的顺序一直进行下去，直到所有节点被删或被标记。

那么这个标记的维护，会有路径上的更改与单点查询，考虑用树链剖分实现。因为有 $n$ 种颜色，每种颜色需要对路径标记一次，时间复杂度为 $O(n\log ^2n)$。而每个节点最多被删一次，每一次删需要一次路径标记，时间复杂度为 $O(n\log^2n)$。到这里时间复杂度 $O(n\log ^2n)$。

---

现在找到一个必取点后的事情已经被我们解决了，但是如何去找一个必取点呢？

实际上，只用判断编号为 $2n$ 的这个点是否能删就行了。

- 如果可以删，那么删完后存在唯一的节点 $v$ 满足 $col_v=col_{2n}(v\neq 2n)$，而又要保证包含所有颜色，所以必须取 $v$。将 $v$ 所在的连通块留下，将其他连通块删去，这也是为什么上文说的是连通块了。

- 如果不能删，那么 $2n$ 这个点就必取，上文说的连通块在此情况下其实就是整个图。

那么如何判断编号为 $2n$ 的点是否能删呢？

我们再来看看刚才那个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/awfrtd67.png)

根据刚才说的，剩下的连通块分为两种，太麻烦了，所以初始建树时，我们钦定 $2n$ 为树的根，这样只用讨论以 $2n$ 的儿子为根的子树是否合法就行了。

记录 $sum_u$ 为以 $u$ 为根的子树内颜色种数。然后判断是否有 $sum_v=n,v\in son_{2n}$。

预处理 $sum$ 数组，对于节点 $i,j$，满足 $col_i=col_j(i\neq j)$，将所有 $i,j$ 的祖先的 $sum$ 值加 $1$。这里可以用树上差分统计，将 $sum_i$ 加 $1$，$sum_j$ 加 $1$，$sum_{\operatorname{lca(i,j)}}$ 减 $1$。


处理完后，遍历一遍树统计差分数组，然后最近公共祖先用树剖实现（因为上面已经用了树剖）。这里时间复杂度 $O(n\log n)$。

那么到此这道题就做完了。

所以整个做法就是：判断一下编号为 $2n$ 的点是否能删，如果能删，将与它颜色相同的另一个点定为新树根；否则定它为新树根。然后用树链剖分处理每个点是否能删，能删则删，删后再更新标记。最后把没被删的点输出。

时间复杂度 $O(n\log ^2n)$，常数小，跑得挺快的。因为是树剖，所以码量可能有点大。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Os")
const int N=1e6+5;
int head[N],cnt,n;//建图 
int top[N],id[N],sz[N],son[N],d[N],f[N],cnta;
//树剖数组，top链顶，id[u]为u在序列中的下表，son重儿子，d深度，f为父亲 
int col[N];//每个点颜色 
int pos1[N],pos2[N];
//pos1[i],pos2[i]为颜色为i的两个点的编号 
int sum[N];
//原树内以u为根的子树内的颜色个数
int root;
//新树根节点 
bool del[N];//该点是否删去
vector<int> ans;//存答案 
struct edge
{
	int v,nxt;
}a[N<<1];//链式前向星建图 
void add(int u,int v) 
{
	a[++cnt].v=v;
	a[cnt].nxt=head[u];
	head[u]=cnt;
}
struct seg
{
	bool assign,val;//区间赋值，单点查询线段树
	//assign为lazy标记，val为值 
}s[N<<2];
int read()//快读 
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void pushdown(int rt)//下传 
{
	if(s[rt].assign)
	{
		s[rt<<1].assign|=1;
		s[rt<<1|1].assign|=1;
		s[rt<<1].val|=1;
		s[rt<<1|1].val|=1;
		s[rt].assign=0;
	}
}
void update(int l,int r,int rt,int L,int R)
{//区间加 
	if(L<=l&&R>=r)
	{
		s[rt].val|=1;
		s[rt].assign|=1;
		return;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(L<=mid) update(l,mid,rt<<1,L,R);
	if(R>mid) update(mid+1,r,rt<<1|1,L,R);
}
int query(int l,int r,int rt,int pos)
{//单点查询 
	if(l==r) return s[rt].val;
	int mid=(l+r)>>1;
	pushdown(rt);
	if(pos<=mid) return query(l,mid,rt<<1,pos);
	return query(mid+1,r,rt<<1|1,pos);
}
void dfs(int u,int fa)
{//预处理深度，子树大小，重儿子 
	d[u]=d[fa]+1,sz[u]=1,f[u]=fa;
	for(int i=head[u];i!=0;i=a[i].nxt)
	{
		int v=a[i].v;
		if(v==fa||del[v]) continue;
		dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t)
{//预处理链顶，在序列中的下标 
	top[u]=t,id[u]=++cnta;
	if(!son[u]) return;
	dfs2(son[u],t);
	for(int i=head[u];i!=0;i=a[i].nxt)
	{
		int v=a[i].v;
		if(v==f[u]||v==son[u]||del[v]) continue;
		dfs2(v,v); 
	}
}
int lca(int u,int v)
{//树剖求LCA 
	while(top[u]!=top[v])
	{
		if(d[top[u]]>d[top[v]]) swap(u,v);
		v=f[top[v]];
	}
	if(d[u]>d[v]) swap(u,v);
	return u;
}
void path_update(int u,int v)
{//树剖对路径进行赋值 
	while(top[u]!=top[v])
	{
		if(d[top[u]]>d[top[v]]) swap(u,v);
		update(1,n,1,id[top[v]],id[v]);
		v=f[top[v]];
	}
	if(d[u]>d[v]) swap(u,v);
	update(1,n,1,id[u],id[v]);
}
void get_sum(int u,int fa)//统计差分数组 
{
	for(int i=head[u];i!=0;i=a[i].nxt)
	{
		int v=a[i].v;
		if(v==fa) continue;
		get_sum(v,u);
		sum[u]+=sum[v];
	}
}
void assign(int u,int fa,int end)//在原树上删点 
{//删去原树除去 以end为根的子树 的所有点 
	del[u]=1;
	for(int i=head[u];i!=0;i=a[i].nxt)
	{
		int v=a[i].v;
		if(v==end||v==fa) continue;
		assign(v,u,end);
	}
}
bool check(int u)//判断是否删掉2n这个点 
{
	for(int i=head[u];i!=0;i=a[i].nxt)
	{
		int v=a[i].v;
		if(v==f[u]) continue;
		if(sz[v]>=n/2)
		{//判断其儿子的子树是否合法 
			if(sum[v]==n/2) 
			{
				assign(n,0,v);//删点 
				return true;
			}
			return false;
		}
	}
	return false;
}
void modify(int u,int fa)//新树上删点 
{
	int pos=0;
	if(pos1[col[u]]==u) pos=pos2[col[u]];
	else pos=pos1[col[u]];
	path_update(root,pos);//更新另一个点 
	del[u]=1;
	for(int i=head[u];i!=0;i=a[i].nxt)
	{
		int v=a[i].v;
		if(v==fa||del[v]) continue;
		modify(v,u);
	}
}
int main()
{
	n=read()*2;
	for(int i=1;i<=n;i++) 
	{
		col[i]=read();
		if(pos1[col[i]]) pos2[col[i]]=i;
		else pos1[col[i]]=i;
	}
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(n,0);//以2n这个点为根 
	dfs2(n,0);
	for(int i=1;i<=n;i++)
	{
		int l=lca(pos1[i],pos2[i]);
		sum[pos1[i]]++,sum[pos2[i]]++,sum[l]--;
	}
	get_sum(n,0);
	if(check(n))//如果可以删2n这个点 
	{
		if(pos1[col[n]]==n) root=pos2[col[n]];
		else root=pos1[col[n]];
		cnta=0;
		memset(son,0,sizeof(son));
		dfs(root,0);//以root为根重构一下树 
		dfs2(root,0);
	}
	else root=n;//树根没变，可以不用重构 
	for(int i=1,l;i<=n;i++)
	{
		if(del[pos1[i]]) l=pos2[i];//如果只有一个该颜色的点未删，则它的祖先都不能删 
		else if(del[pos2[i]]) l=pos1[i];
		else l=lca(pos1[i],pos2[i]);//如果有两个同颜色的节点未被删，则它们的公共祖先都不能删 
		//更新哪些节点不能删 
		path_update(root,l);
	}
	for(int u=n;u>=1;u--)
	{
		if(del[u]) continue;//已经被删过 
		if(!query(1,n,1,id[u])) modify(u,f[u]);//如果能删 
		else ans.push_back(u);
	}
	printf("%d\n",ans.size());
	for(int i=ans.size()-1;i>=0;i--) printf("%d ",ans[i]);
	return 0;
}
```

（制作不易，若有错误请指出，如果对您有帮助，可以点个赞么，谢谢！）

---

## 作者：喵仔牛奶 (赞：7)

# Solution

由于有 $n$ 种颜色，我们可以发现，选择的方案里至少包含一个重心。我们新建一个没有颜色的点 $r$，然后断开两个重心之间的边（如果有的两个重心的话），让 $r$ 向重心连边，可以发现这样的话 $r$ 必选。

比较经典的刻画：必选一个点情况下的联通块是以这个点为根的树扣掉若干子树。

观察哪些点不能被扣掉：令颜色为 $x$ 的点是 $s_{x,0},s_{x,1}$，可以发现 $\text{LCA}(s_{x_0},s_{x,1})$ 及其祖先不能被扣，不然没有 $x$ 了。这些点之外都可以扣。

接下来我们找到编号最大的能扣的点，把它扣掉。这之后，对于它和它子树内的 $x$，另一个和 $x$ 颜色相同的点 $y$ 和 $y$ 的祖先不能被扣。一直这样扣就做完了。

具体做法：从大到小枚举点的编号，能扣就扣。扣掉的话递归进入子树，找出对应的 $y$，向上跳父亲，跳到打过“不能扣”标记的就停止。如果递归到之前被扣掉的点就停止向下递归。

可以发现一个点会被打上至多一次“不能扣”标记，会被 dfs 访问至多一次。故这些总复杂度 $\mathcal{O}(n)$。

总复杂度 $\mathcal{O}(n\log n)$，瓶颈在于求 LCA，当然可以线性。

# Code

```cpp
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
    int n, x, y, mx, rt, ct, a[N], sz[N], dfn[N], fa[N], id[N], vs[N], del[N], st[20][N]; 
	vector<int> ce, s[N], G[N];
	void dfs1(int u, int fa) { // 求重心
		int x = 0; sz[u] = 1;
		for (int v : G[u])
			if (v != fa) dfs1(v, u), sz[u] += sz[v], x = max(x, sz[v]);
		x = max(x, n - sz[u]);
		if (x < mx) mx = x, ce.clear();
		if (x == mx) ce.pb(u);
	}
	void dfs2(int u) { // 预处理 LCA
		dfn[u] = ++ ct, id[ct] = u, st[0][ct] = dfn[fa[u]];
		for (int v : G[u])
			if (v != fa[u]) fa[v] = u, dfs2(v);
	}
	int lca(int u, int v) {
		if (u == v) return u;
		if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
		int d = __lg(v - u ++);
		return id[min(st[d][u], st[d][v - (1 << d) + 1])];
	}
	void upd(int x) { // x 及其祖先打上标记
		while (x != rt && !vs[x]) vs[x] = 1, x = fa[x];
	}
	void dfs3(int u) { // 递归 x 子树
		if (del[u]) return;
		del[u] = 1, upd(s[a[u]][u == s[a[u]][0]]);
		for (int v : G[u])
			if (v != fa[u]) dfs3(v);
	}
	int main() {
		cin >> n, n *= 2;
		REP(i, 1, n) cin >> a[i], s[a[i]].pb(i);
		REP(i, 2, n) cin >> x >> y, G[x].pb(y), G[y].pb(x);
		mx = 1e9, dfs1(1, 0), rt = n + 1;
		for (int x : ce) G[rt].pb(x), G[x].pb(rt);
		if (SZ(ce) == 2) { // 断开两重心之间的边
			int x = ce[0], y = ce[1];
			sort(ALL(G[x])), sort(ALL(G[y]));
			G[x].erase(lower_bound(ALL(G[x]), y));
			G[y].erase(lower_bound(ALL(G[y]), x));
		}
		dfs2(rt);
		REP(i, 1, __lg(n + 1)) REP(j, 1, n + 1)
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		REP(i, 1, n / 2)
			upd(lca(s[i][0], s[i][1]));
		DEP(i, n, 1)
			if (!vs[i]) dfs3(i);
		ct = 0;
		REP(i, 1, n) ct += !del[i];
		cout << ct << '\n';
		REP(i, 1, n)
			if (!del[i]) cout << i << ' ';
		cout << '\n';
 		return 0;
	}
}

---

## 作者：hegm (赞：5)

假如我们钦定了某一个节点一定作为答案，那么该如何操作。

考虑以确定的节点为根，那么最终答案一定是一个包括根的点集。

我们从 $2n\sim 1$ 挨个考虑，每次对于节点 $i$，检查是否存在一种方案，满足不选这个节点，并且之前删除节点也不选的情况下是否有一个合法方案。

对于一个节点，如果不选它，那么显然，他子树内所有节点都无法继续和根节点联通。

考虑如何 `check` 是否依然存在合法解。

1. 其子树内不能有两个同种颜色的节点。

2. 其子树内不能存在一个节点，其另一半已经被删除。

两者都满足即可，$1$ 可以通过对每对颜色求 $\text{lca}$ 然后令其到根节点路径上的所有节点都无法被删除。

$2$ 则是在每次删除的时候，暴力删除每个节点，然后令其另一个同颜色的节点到根路径上的所有节点无法被删除。

由于每个节点都只会被删一次，因此复杂度可以接受。

问题在于如何找到一定在答案内的节点。

其实也很简单，随便找一堆颜色点，两者各为根跑两边即可。

复杂度 $O(n\log n)$。

---

## 作者：ZM____ML (赞：3)

钦定根妙完了。

因为原题给出了一个无根树，如果我们在此基础上考虑不选择一个点，则需要对其的所有子树进行递归，这个做起来是十分复杂的。所以我们考虑钦定一个点为根，表示根这个点一定在我所选的集合内。因为同一种颜色的两个点至少选择一个，所以将两个点分别钦定为根跑一遍即可。

因为删除第 $i$ 个点的代价为 $2^i$，所以我们考虑贪心，按照编号从大往小进行考虑，贪心的可以不选当前第 $i$ 个点就不选，显然这一定是最优的。

那么对于一个节点，如果删除了它相当于删除了它的所有子树，那么我们考虑如何判断那些点不能被删除。

1. 任意一对同色点的 $\text{lca}$ 到根路径上的所有点是不能被删除的。

2. 当一个点被删除，则另一个同色点到根路径上的所有点是不能被删除的。

第一种情况可以提前找到所有同色点 $\text{lca}$ 预处理，第二种情况可以直接打标记暴力删除。

因为每个点只会被删除一次，所以复杂度是正确的。

复杂度 $O(n \log n)$。

---

## 作者：Forgive_Me (赞：1)

## CF2042E Vertex Pairs

### 题面：

给定一个由 $2n$ 个顶点组成的树（编号 $1\sim 2n$）。  
每个顶点上都被染上 $[1,n]$ 中的一个颜色。  
且树上每个颜色的点都恰好有两个。  
每个顶点有代价——编号为 $i$ 的顶点代价为 $2^i$。

你需要选择树的一个点集，满足：  
1.  点集是连通的；  
2.  该点集的颜色集合要包含 $[1,n]$ 里的所有颜色。

求总代价最小的点集。  
注意，不需要最小化点集中的顶点数量。

$n\leq 2\times 10^5$。

---

### Solution：

文章较长，是我结合了自己的认识和其他题解的做法总结的，请耐心阅读，欢迎指出问题和修改意见。


---

写在前面：一般这种求树上连通块的题，都有两种方法。

要么是钦定一个根（连通块内必选点）去做，这样只需要找子树；  
要么硬做，用类似换根的方法，麻烦一点但比较通，讨论会恶心一点。

---

考虑当这是一棵有根树，且根必选，要确定其他必选点：

对于所有颜色我们都有两个点存在。  
并且，在这两个点当中我们至少选一个点。

起初我想的是，分讨两个点的位置关系，然后发现最后结论是一样的。  
即：这两个点的 lca 为必选点。证明显然。  
则有，从这两个点的 lca 到根的路径上的所有点必选。

这样我们就找到了所有必选点。  
注意：此处的“必选点”我们不考虑代价，只考虑能否构造合法答案点集。  
也就是说，一个合法连通块必须包含上述“必选点”。

考虑选择剩下的点。挖掘一下性质。  
它和前面的必选点有什么区别？

这里我给出一个认识：  
> 在前面“必选点”的基础上，剩下的点的选择约束关系只存在于剩下的点的点集中。

那我们就可以对剩下的点贪心的去做。  
怎么贪心？  
（从小到大能选就选显然是假的！）  
只需从大往小遍历，能不选就不选，充分利用了 $2^i$ 的性质。  
（不就是二进制从高位枚举吗！）

但我们每钦定一个点选或不选**都会影响其他点的选择状态**：

1.  若钦定 $x$ 不选，则 $x$ 及其子树内的点都必不选。  
2.  若钦定 $x$ 选，则 $x$ 到根的路径上的点都必选。

发现如果我们朴素的处理，会出现一种情况：  
在前面我钦定了一些点不选，导致后面遍历到的点都被打上了“必不选”标记，有些权值的点没有被选到，非法。  
（这里“朴素的处理”指，我们在贪心的过程中，每次钦定一个点不选，只改变该点及其子树或到根的链上的选择状态。反例很好得到。）

**而我们在扫的过程中不会主动选择，只会被动选择。**

即我们只会钦定某点不选，而我们对于某点“选”的钦定，实际上是这个“不选”的钦定所导致的。

**换言之，我们每一个“不选”的钦定，都会迫使我们做出一个“选”的钦定。**

形象一点，就是在钦定 $x$ 点不选时，为了点集中还有该颜色的点，我们要找到与它颜色相同的点 $y$ ，并钦定 $y$ 必选，再分别进行链和子树的标记。

注意，这里有一个细节容易忽略：  
还是那个例子。设我们钦定 $x$ 不选，与它同色的点为 $y$ 。此时我们会把 $x$ 的子树全部钦定为“不选”，把 $y$ 到根的链全部钦定为“选”。

这就结束了吗？不是的。

刚才提到，每一个“不选”的钦定，都会迫使我们做出一个“选”的钦定。  
**即对于 $x$ 子树内的每一个点，我们在钦定其不选后，都要找到它所对应的同色点，并钦定为“选”。**  
这个过程可以递归解决。

正确性：  
正是因为我们是编号从大往小扫，选 $y$ 的代价才是小于选 $x$ 的代价的。  
所以我们才只需考虑**个体代价**，忽略**有关链或子树的代价**。

（解释：因为我们站在代价贪心的基础上来扫，就不用担心我们不选这个点，导致选择的同色点（及其到根的链上）有代价更大的点被我们钦定为必选。）

---


现在问题就在于：如何找到一个必选点当根？

1.  二分找到最大必选点。（常数最大的一集）（我最初的写法）  
注意，如果你是这样做的，那么有些点就被删去了，如果该权值只剩下一个点了呢？


2.  树的重心。  
证明：选出的点集大小大于等于 $n$。   
（这个我认为不太好想也没细想，看了题解里面有这种）

3.  对同权值两个点做两遍，选更优的。  
这个做法还挺优的，我自带大常数的代码也只跑了一秒多。  
要注意一点：例如我钦定的是权值为 $1$ 的第一个点做根，我无需也不可强制权值为 $1$ 的第二个点不选（这个应该是很好理解的）。

---

世界线收束，整理一下过程：

1.  找出最大必选点，将其作为根。

2.  建新树，标记必选点。

3.  对剩下的点，代价从大往小扫，贪心选点，更改选择状态。

---

时间复杂度分析：

（以下 $n$ 与 $2n$ 混用致歉）

找根-> 最劣也是单 $\log$。

跳 lca -> $O(n\log n)$ 也可 $O(n)$。

标记：每个点最多被标记一次（必选/必不选）-> $O(n)$。

总： $O(n\log n)$ 级别……？


---

总结：我认为这题有几个点非常好玩，也比较经典。

1.  $2^i$ 在贪心策略的利用。

2.  树上连通块问题“钦定根”的做法。（当然，这道题似乎不钦定根也可以做？）

3.  对于点的认识：“必选点”，钦定“选/不选”的点。
---

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=400010;
vector<int> v[N],col[N];
int n,cnt,RT;
int c[N],d[N],up[N][21],mk[N],ans[2][N];
//mk[]:0/1/2->未确定选择状态/必选/必不选 
void dfs(int x,int fa)
{
	mk[x]=0;
    for(auto y:v[x])
    {
        if(y==fa) continue;
        d[y]=d[x]+1;
        up[y][0]=x;
        dfs(y,x);
    }
}
inline int lca(int x,int y)
{
    if(d[x]<d[y]) swap(x,y);
    int now=d[x]-d[y];
    while(now>0)
    {
        int k=log2(now);
        x=up[x][k];
        now-=(1<<k);
    }
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(up[x][i]!=up[y][i]) x=up[x][i],y=up[y][i];
    return up[x][0];
}
inline void des(int i,int fa)//钦定不选，递归标记 
{
	mk[i]=2;
	int now=col[c[i]][0];
    if(now==i) now=col[c[i]][1];
    while(!mk[now]) 
    {
    	mk[now]=1;
    	now=up[now][0];
	}
    for(auto y:v[i])
        if(y!=fa&&mk[y]!=2) des(y,i);
}
void solve(int res[])
{
    dfs(RT,0);
    for(int j=1;j<=19;j++)
        for(int i=1;i<=2*n;i++) 
            up[i][j]=up[up[i][j-1]][j-1];
    mk[RT]=1;
    for(int i=1;i<=n;i++)
    {
        int x=col[i][0],y=col[i][1];
        int now=lca(x,y);
		while(mk[now]==0) mk[now]=1,now=up[now][0];
    }
    for(int i=2*n;i>=1;i--)
    {
    	if(mk[i]==2) continue;
    	else if(mk[i]==1) res[i]=1;
		else des(i,up[i][0]);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=2*n;i++) 
    {
        cin>>c[i];
        col[c[i]].push_back(i);
    }
    for(int i=1;i<2*n;i++)
    {
        int x,y;
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
        
    }
    RT=col[1][0];solve(ans[0]);
    RT=col[1][1];solve(ans[1]);
    //分别钦定为根做两遍 
    int op=0;
	for(int i=2*n;i>=1;i--)
    {
        if(ans[0][i]!=ans[1][i])
        {
            if(ans[0][i]==0) op=0;
            else op=1;
            break;
        }
    }
    int cnt=0;
    for(int i=1;i<=2*n;i++) if(ans[op][i]) cnt++;
    cout<<cnt<<'\n';
    for(int i=1;i<=2*n;i++) if(ans[op][i]) cout<<i<<" ";
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定一个 $2n$ 个点的树，点有点权，点权位于 $[1,n]$ 且对于每一个 $x\in[1,n]$，都恰好存在两个点点权为 $x$，选择点 $i$ 的代价为 $2^i$。

你需要选择一个连通块，使得选择的点覆盖了所有点权且代价总和最小，输出选取的方案。

$1\leq n\leq 2\times 10^5$。

## 思路

看到题目，唯一的切入点应该就是覆盖了所有点权了，那么自然得到对于两个同点权的点 $x,y$，至少有一个在答案中。不过好像没什么用？不不不，盲生，你发现了华点。

不妨钦定一个点必须在答案中，那么不妨以这个点为根，则我们不选择一个点，则它的子树的所有点都无法选择，这是一个关键性质。

看到代价的形式，不难想到从大到小枚举点去做经典按位贪心，如果这个点可以不出现在答案中，那么不出现在答案中一定最优。

现在的问题是如何判断一个点必须出现在答案中，那么要么这个点的子树中存在两个同点权点，要么存在一个点，使得与其同点权的点无法选择。

对于第一种情况，只需要预先标记同点权的点 $x,y$ 的 LCA 到根的路径均必须选择即可。

对于第二种情况，我们在决定不选择一个点时，暴力向下 dfs，找到这个点的同色点，它到根的路径均必须选择。注意需要保证每个点只会向下 dfs 一次。

然后需要考虑我们用什么数据结构来维护，由于若一个点必须选择，则其祖先均必须选择，所以可以直接暴力更改就好了，无需重链剖分。

时间复杂度 $O(n\log n)$ 可以通过本题，将 LCA 算法换成 $O(1)$ RMQ 可以做到 $O(n)$。

## 代码

感觉这个做法题解区已经有一片了，但好像大家都没有放代码，那我就补充一下我的实现吧。

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 4e5 + 5;
int n, a[N], rt;
vector<int> b[N], g[N];

int father[N], dep[N], siz[N], son[N], top[N], dfn[N], rev[N];

void dfs1(int u, int fa){
    dep[u] = dep[fa] + 1, father[u] = fa, siz[u] = 1;
    for(int v : g[u]){
        if(v == fa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fa){
    dfn[u] = ++dfn[0], rev[dfn[u]] = u;
    if(son[u]) top[son[u]] = top[u], dfs2(son[u], u);
    for(int v : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v, dfs2(v, u);
    }
}

bool val[N];

void update(int x){
    for(;x&&!val[x];x=father[x]) val[x] = true;
}

bool ret[2][N], removed[N];

int lca(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = father[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

void solve(bool ret[]){
    top[rt] = rt, dfn[0] = father[rt] = 0;
    dfs1(rt, 0), dfs2(rt, 0);
    for(int i=1;i<=(n>>1);i++) update(lca(b[i][0], b[i][1]));
    update(rt);
    for(int i=n;i;i--){
        if(val[i]) ret[i] = true;
        else{
            int j = dfn[i];
            for(;j<=dfn[i]+siz[i]-1;j++){
                if(removed[j]){
                    j = j + siz[rev[j]] - 1;
                    continue;
                }
                removed[j] = true;
                int t = a[rev[j]];
                update(rev[j] == b[t][0] ? b[t][1] : b[t][0]);
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n; n <<= 1;
    for(int i=1;i<=n;i++) cin >> a[i], b[a[i]].push_back(i);
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    rt = b[1][0], solve(ret[0]);
    fill(son + 1, son + n + 1, 0);
    fill(val + 1, val + n + 1, false);
    fill(removed + 1, removed + n + 1, false);
    rt = b[1][1], solve(ret[1]);
    bool result = 0;
    for(int i=n;i;i--){
        if(ret[0][i] != ret[1][i]){
            result = ret[0][i] ? 1 : 0;
            break;
        }
    }
    cout << count(ret[result] + 1, ret[result] + n + 1, 1) << '\n';
    for(int i=1;i<=n;i++){
        if(ret[result][i]) cout << i << ' ';
    }
    cout << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Otomachi_Una_ (赞：1)

水题解/se

因为你要选至少 $n$ 个点，所以重心一定会被选上。我们以重心为根。

然后考虑每个点维护一个 $ban$ 数组表示这个点是不是强制被选上。

那么，对权值相同的两个点 $p,q$，$lca(p,q)$ 到 $rt$ 的路径上所有点都是必选的。跳父亲打个标记就行。

然后从大到小扫描。如果这个点被打上了标记就加入集合。否则就删掉，同时将子树中，所有点的另一个对偶点的所有祖先打上 $ban$ 标记。

时间复杂度：$\mathcal O(n)$。

---

## 作者：spdarkle (赞：0)

根据边权的特殊性，容易想到经典贪心，也就是我们按编号从大到小加入点，如果不加入这个点仍然存在合法方案，那么就删去这个点，否则这个点必选。

这样构造出的方案权值一定最小。

考虑这个过程，一个暴力的想法是将这个点删除，然后看当前已经有的必选点组成的连通块（这个点不能够割开这个连通块）能否仍然合法。

这当然很劣，但是可以发现 **这个点不能位于当前包含所有必选点的最小连通块内**，也就是删掉这个点不能导致必选点不连通。

这启发我们想办法快速判断一个点能否删除，发现有如下条件：

1. 这个点到必选点连通块上没有点已经确认删除。
2. 以必选点连通块为根方向，这个点的子树内不存在某个颜色出现两次，或者不存在某个颜色，其中这个颜色有个点已经确认删除。
3. 这个点删掉后不会导致必选点不连通。

发现这个后，其实就比较容易了。首先我们找到一个必选点，令其为根，接着对每一对同色点求最近公共祖先，这个最近公共祖先到根的链必选。

接着我们就可以从大到小枚举点进行判断了，如果这个点可删，那么将**其与其子树**全部删除。

删除一个点时，需要将其同色点到根的路径全部标记为必选。

这些操作可以用并查集维护，但事实上这里是笔者脑抽了，暴力合就是对的。

现在还有一个问题是如何找到一个必选点，可以二分最大的必选点，然后看删掉比二分值大的点后有没有连通块合法即可。

---

## 作者：yhylivedream (赞：0)

给一个不用四毛子的 $O(n)$ 做法。

钦定根的做法别的题解已经很详细了，就不阐述一遍。

发现瓶颈在于如何判断有是否有两个颜色相同的点在某一子树内。

很容易想到给两个颜色相同的点的 LCA 打上 tag，在统一上传，复杂度为 $O(n\log n)$。

由于一个子树在 DFS 序上是一段连续的区间，可以将颜色相同的点在 DFS 序上当做一段区间 $[l_i,r_i]$，这样问题就变成了判断一段区间是否完全包含任意给定区间，对于每个点记录离它最近的给定区间的左端点，直接前缀 max 即可。

代码不给了，很容易实现。

---

## 作者：居然有个高手 (赞：0)

笨方法做题。

考虑如何找出最大的需要保留的点，发现我们可以二分点权值 $x$，删掉比 $x$ 大的点后看是否存在一个连通块具有所有颜色。这样我们就在 $O(n\log n)$ 时间内找到了一个答案的必须点。

接下来我们先视为保留 $[1,x]$ 的所有点，然后再进行删点。将 $x$ 视为根，则我们后面要删掉点 $u$ 时需要满足删完 $u$ 后照样拥有所有颜色。这样的点 $u$ 必然不满足子树内有一个唯一颜色或有一个颜色的两个点。倒推可得我们从每个颜色的两个点的 lca 向上标记，这些点都是不可删除的；而对于唯一颜色点直接从他本身向上标记。标记只有 $O(n)$ 个，复杂度是显然正确的。

时间复杂度：$O(n\log n)$。但是由于前面那个二分的过程，常数很大，需要一定卡常。。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e5+5;
char buf[1<<21], *p1, *p2;
#define GC p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF : *p1++
inline int read() {
	int x = 0; char ch = GC;
	while(ch > '9' || ch < '0') ch = GC;
	while(ch >= '0' && ch <= '9') x = (x<<1) + (x<<3) + (ch^48), ch = GC;
	return x;
}
bool qwqa;
int n,a[N],head[N],etot,vis[N],ok,c[N],rt,fa[N],b[N][3],ans[N],cnt,dfn[N],f[20][N<<1],num,d[N];
struct edge{
    int nxt,to;
}e[N<<1];
inline void add(int a,int b){
    e[++etot]={head[a],b};head[a]=etot;
}
inline void dfs1(int x,int w){
    if(!c[a[x]])ok++;
    c[a[x]]=1;vis[x]=1;
    for(int i = head[x],y;i;i=e[i].nxt){
        y=e[i].to;
        if(!vis[y]&&y<w)dfs1(y,w);
    }
}
inline void dfs2(int x,int w){
    c[a[x]]=0;
    vis[x]=2;
    for(int i = head[x],y;i;i=e[i].nxt){
        y=e[i].to;
        if(vis[y]==1&&y<w)dfs2(y,w);
    }
}
inline bool check(int x){
    for(int i = 1;i<=2*n;i++)vis[i]=0;
    for(int i = 1;i<=2*n;i++){
        if(!vis[i]&&i<x){
            ok=0;
            dfs1(i,x);dfs2(i,x);
            if(ok==n)return 1;
        }
    }
    return 0;
}
inline void dfs(int x,int fa){
    c[a[x]]++;vis[x]=0;
    b[a[x]][c[a[x]]]=x;
    ::fa[x]=fa;
    dfn[x]=++num;f[0][num]=x;
    for(int i = head[x],y;i;i=e[i].nxt){
        y=e[i].to;
        if(y!=fa&&y<=rt)d[y]=d[x]+1,dfs(y,x),f[0][++num]=x;
    }
}
inline void dfs3(int x){
    vis[x]=2;
    int now = b[a[x]][1];
    if(now==x)now=b[a[x]][2];
    while(!vis[now]){
        vis[now]=1;
        now=fa[now];
    }
    for(int i = head[x],y;i;i=e[i].nxt){
        y=e[i].to;
        if(y!=fa[x]&&y<=rt)dfs3(y);
    }
}
inline int lca(int x,int y){
    x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    int k = __lg(y-x+1);
    if(d[f[k][x]]<d[f[k][y-(1<<k)+1]])return f[k][x];
    return f[k][y-(1<<k)+1];
}
bool qwqb;
int main(){
    // cerr<<(&qwqa-&qwqb)/1024/1024;
    n=read();
    for(int i = 1;i<=2*n;i++)a[i]=read();
    for(int i = 1,x,y;i<2*n;i++)x=read(),y=read(),add(x,y),add(y,x);
    int l=n+1,r=2*n,mid,qwq=0;
    while(l<=r){
        qwq++;
        mid=l+r>>1;
        if(check(mid))r=mid-1;
        else l=mid+1;
    }
    // if(n==2e5)return 0;
    rt=r;
    for(int i = 1;i<=2*n;i++)vis[i]=2;
    d[rt]=1;dfs(rt,0);
    for(int j = 1;j<=__lg(num);j++){
        for(int i = 1;i+(1<<j)-1<=num;i++){
            if(d[f[j-1][i]]<d[f[j-1][i+(1<<j-1)]])f[j][i]=f[j-1][i];
            else f[j][i]=f[j-1][i+(1<<j-1)];
        }
    }
    vis[rt]=1;
    for(int i = 1;i<=n;i++){
        if(c[i]==1){
            int now = b[i][1];
            while(!vis[now]){
                vis[now]=1;
                now=fa[now];
            }
        }
        else{
            int now=lca(b[i][1],b[i][2]);
            while(!vis[now]){
                vis[now]=1;
                now=fa[now];
            }
        }
    }
    ans[++cnt]=rt;
    for(int i = rt-1;i>=1;i--){
        if(vis[i]==2)continue;
        if(vis[i]){
            ans[++cnt]=i;
            continue;
        }
        dfs3(i);
    }
    printf("%d\n",cnt);
    for(int i = cnt;i>=1;i--)printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

没想到可以钦定一个必定包含的点为根，写了一个比较丑的做法。

点 $i$ 的权值是 $2^{i}$，于是考虑按位确定答案，当确定了不要的点集合为 $S$ 时，原图被分割为若干给连通块，当 $S$ 非空时，原图被分割为至少 $2$ 个连通块，注意到合法连通块至少有 $n$ 个点，所以在被分割出的若干连通块至多只有一个连通块的子连通块可以成为答案，如果子连通块合法这个连通块本身也合法，因此可以考虑动态的维护出当前求出的合法连通块再在分割时 check 当前连通块被分割出的最大连通块是否合法以决定要不要把当前点加入 $S$。

问题变为如何维护一个连通块是否合法？

对于某种只剩下一个点的颜色，这个连通块必须要包含这种颜色，注意到被分割出的连通块是一个子树或者子树补与当前连通块的交，因此可以用 dfs 序加树状数组维护出连通块内的只剩下一个点的颜色数，对于剩下两个点的颜色数，假若被分割出的连通块中只包含两个点中的一个点，那么注意到这个被分割出的连通块与分割点出边的边集交一定被两个同色点之间的路径经过，差分后还是可以 dfs 序加树状数组维护一个链加边查，至于被分割出的连通块包含一种颜色的两个点的情况可以用连通块大小与前面求出的信息容斥下得到，连通块大小的求法与连通块内只剩下一个点的颜色数的求法相似。

至此可以快速判断连通块合法，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+114;
int tr[maxn][2];//所有存活点 所有存活单点
int List[maxn];//双点之间的边加 一条边被认为是 (i,fa_i)
int fa[maxn];
vector<int> E[maxn];
int n;
vector<int> ans;
int L[maxn],R[maxn],dfncnt,node[maxn];
int X[maxn],Y[maxn];
int dep[maxn];
int a[maxn];
int top[maxn],sz[maxn],son[maxn];
set<int> S;//存活点的 dfn 序
void dfs1(int u){
    L[u]=++dfncnt;
    node[dfncnt]=u;
    sz[u]=1;
    for(int v:E[u]){
        if(v!=fa[u]){
            fa[v]=u;
            dep[v]=dep[u]+1;
            dfs1(v);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]) son[u]=v;
        }
    }
    R[u]=dfncnt;
}
void dfs2(int u,int tp){
    top[u]=tp;
    if(son[u]!=0) dfs2(son[u],tp);
    for(int v:E[u]){
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}
int LCA(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    return v;
}
void addpoint(int u,int c,int ty){
    while(u<=2*n) tr[u][ty]+=c,u+=(u&(-u));
}
int askseq(int l,int r,int ty){
    int res=0;
    while(r>0) res+=tr[r][ty],r-=(r&(-r));
    l--;
    while(l>0) res-=tr[l][ty],l-=(l&(-l));
    return res;
}
void addlist(int u,int c){
    u=L[u];
    while(u<=2*n) List[u]+=c,u+=(u&(-u));
}
int asklist(int u){
    int res=0;
    int l=L[u],r=R[u];
    while(r>0) res+=List[r],r-=(r&(-r));
    l--;
    while(l>0) res-=List[l],l-=(l&(-l));
    return res;
}
void del(int u){
    //删掉点 u
    addpoint(L[u],-1,0);
    addlist(X[a[u]],-1);
    addlist(Y[a[u]],-1);
    addlist(LCA(X[a[u]],Y[a[u]]),2);
    S.erase(L[u]);
    if(u==X[a[u]]) addpoint(L[Y[a[u]]],1,1);
    else addpoint(L[X[a[u]]],1,1);
}
void delet(int u,int ty){
    //ty=0 删掉 u 子树内的点
    //ty=1 删掉 u 子树外的点
    vector<int> vec;
    if(ty==0){
        for(auto it=S.lower_bound(L[u]);(*it)<=R[u]&&it!=S.end();it++){
            vec.push_back((*it));
        }
    }else{
        for(auto it=S.begin();(*it)<L[u]&&it!=S.end();it++){
            vec.push_back((*it));
        }
        for(auto it=S.upper_bound(R[u]);it!=S.end();it++){
            vec.push_back((*it));
        }
    }
    for(int x:vec) del(node[x]);
}
bool check(int u,int v){
    //check u->v 后抵达的连通块是否合法
    if(fa[v]==u){
        int sum=askseq(L[v],R[v],0);
        int sum0=askseq(L[v],R[v],1);
        int sum1=asklist(v);
        return ((sum-sum0-sum1)/2+sum0+sum1)==n;
    }else{
        int sum=askseq(1,L[u]-1,0)+askseq(R[u]+1,2*n,0);
        int sum0=askseq(1,L[u]-1,1)+askseq(R[u]+1,2*n,1);
        int sum1=asklist(u);
        return ((sum-sum0-sum1)/2+sum0+sum1)==n;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=2*n;i++) S.insert(i);
    for(int i=1;i<=2*n;i++){
        cin>>a[i];
        if(X[a[i]]==0) X[a[i]]=i;
        else Y[a[i]]=i;
    }
    for(int i=1;i<2*n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;i++) addlist(X[i],1),addlist(Y[i],1),addlist(LCA(X[i],Y[i]),-2);
    for(int i=1;i<=2*n;i++) addpoint(i,1,0);
    for(int u=2*n;u>=1;u--){
        if(S.find(L[u])!=S.end()){
            //不保留
            int mid=0;
            for(int v:E[u]){
                if(S.find(L[v])!=S.end()){
                    if(check(u,v)==true) mid=v;
                }
            }
            if(mid==0){
                ans.push_back(u);
            }else{
                for(int v:E[u]){
                    if(v==mid) continue;
                    if(S.find(L[v])!=S.end()){
                        if(v==fa[u]) delet(u,1);
                        else delet(v,0);
                    }
                }
                del(u);
            }
        }
    }
    cout<<ans.size()<<'\n';
    reverse(ans.begin(),ans.end());
    for(int x:ans) cout<<x<<' ';
    return 0;
}
```

---

