# Tree or not Tree

## 题目描述

给定一个无向连通图 $G$，包含 $n$ 个顶点和 $n$ 条边。$G$ 中没有自环或重边。每条边有两种状态：开（on）和关（off）。初始时所有边都处于关闭状态。

你还会得到 $m$ 个查询，每个查询为 $(v,u)$ ——将图 $G$ 中从顶点 $v$ 到顶点 $u$ 的最短路径上的所有边的状态取反。如果存在多条最短路径，则选择字典序最小的那一条。更正式地说，设从顶点 $v$ 到顶点 $u$ 的所有最短路径为顶点序列 $v,v_{1},v_{2},...,u$，在这些序列中选择字典序最小的那一条。

每次查询后，你需要输出仅考虑当前已打开的边时，图 $G$ 的连通分量个数。

## 说明/提示

我们来看第一个样例。我们将在图片中用蓝色高亮表示已打开的边。

- 在执行任何操作前，图中没有任何边被打开，因此初始时有 5 个连通分量。
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/6d848190f5d9993cf6ddd5c1e2cd0e57d9ae6288.png)
- 执行查询 $v=5,u=4$ 后，仅考虑已打开的边，图中有 3 个连通分量。
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/2f3ad3d35eecb878e654ed5cd572ed4f02ecf9ff.png)
- 执行查询 $v=1,u=5$ 后，仅考虑已打开的边，图中有 3 个连通分量。
  
   ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF117E/31e75e1c5e9c21b4cec0bc2e71e38cbba47e290d.png)

对于长度相等的两个数列 $k$，字典序比较方式如下：若存在某个 $i$（$1 \leq i \leq k$），使得 $x_{i} < y_{i}$，且对于所有 $j$（$1 \leq j < i$）都有 $x_{j} = y_{j}$，则序列 $x$ 的字典序小于序列 $y$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2
2 1
4 3
2 4
2 5
4 1
5 4
1 5
```

### 输出

```
3
3
```

## 样例 #2

### 输入

```
6 2
4 6
4 3
1 2
6 5
1 5
1 4
2 5
2 6
```

### 输出

```
4
3
```

# 题解

## 作者：Hadtsti (赞：4)

### 题意简述

给出一个 $n$ 个点的基环树，初始 $n$ 条边的边权都是 $0$。$m$ 次操作，每次指定两个点 $u$ 和 $v$，把从 $u$ 到 $v$ 的字典序最小的路径上的所有边的边权取反。每次操作输出当前由边权为 $1$ 的边连接的极大连通块数量。

### 题目分析

非常不错的“清新”树剖题。

我们先想一想如果是一棵树的话该怎么处理。这很明显是一个裸的树剖：两次 dfs 后再拿线段树维护，用每个线段树结点维护重链上的 $1$ 边数量 $cnt$，取反时直接把数量改为长度 $r-l+1$ 减掉原来的数量 $cnt$ 即可。考虑每次把 $0$ 边改成 $1$ 边时，$1$ 边连接的极大连通块数量会 $-1$（新的 $1$ 边把原来不连通的两个极大连通块连接起来了）；相反，把 $1$ 边改成 $0$ 边时，极大连通块数量会 $+1$（把原来连通的一个极大连通块分成了两个）。那么让初始答案为 $n$（都是 $0$ 边），每次操作在线段树修改时顺带统计一下 $1$ 边变化量以更新答案就好了，实现也非常简单直观。

回到原题。我们发现每次操作改变的路径可以分成三段：非环上的一段、环上的一段以及非环上的另外一段。考虑把环缩成一个点。如样例 $1$ 的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ym2ao9t7.png)

那么非环上的修改就可以连起来变成一条路径，这样的修改就是上文说的树的情况。而剩下环上的部分则可以看作链，另开一棵线段树维护就好了。每次修改的要么是连续的 $1$ 段，要么首尾相接则是开头和结尾各 $1$ 段。至于环上修改的区间首尾，就是离原始两个端点最近的环上点。具体实现细节看代码。

另外需要注意的是如果环上全都是 $1$ 边答案要 $+1$。因为此时环上最后变成 $1$ 的那条边贡献无效（这条边即使不变成 $1$ 整个环同样连通）。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,y,lx,ly,ans;
int tot,hd[100010],nt[400010],v[400010],deg[400010]/*度*/;//建图有关 
int d[100010],size[100010],fa[100010],son[100010];//树剖一轮 dfs 有关：深度、子树大小、父结点、重儿子 
int top[100010],dfn[100010],cnt;//树剖二轮 dfs 有关：重链顶、dfs 序号 
queue<int>que;//拓扑排序用的队列 
bool vis[100010];//如果拓扑排序时出队
int num,cyc_rk[100010]/*环上点序号*/,id[100010]/*环上点序号对应的原点编号*/,rt_id[100010]/*离每个点最近的环上点*/; 
struct node
{
	int l,r,cnt;//左右端点和 1 边数量 
	bool tag;//懒标记：是否取反 
};//线段树结点 
struct Segment_Tree
{
	node tr[400010];//线段树 4 倍空间 
	void pushup(int p)
	{
		tr[p].cnt=tr[p<<1].cnt+tr[p<<1|1].cnt;//左右子结点更新父结点 
	}
	void addtag(int p)
	{
		tr[p].tag=!tr[p].tag;//标记取反 
		tr[p].cnt=tr[p].r-tr[p].l+1-tr[p].cnt;//答案更新
	}
	void pushdown(int p)
	{
		if(tr[p].tag)
		{
			addtag(p<<1);//下传到左子结点 
			addtag(p<<1|1);//下传到右子节点 
			tr[p].tag=0;//清空标记 
		}
	}
	void build(int p,int l,int r)
	{
		tr[p].l=l,tr[p].r=r;
		tr[p].tag=0,tr[p].cnt=0;
		if(l==r)
			return;
		int mid=l+r>>1;
		build(p<<1,l,mid);//建左子结点 
		build(p<<1|1,mid+1,r);//建右子节点 
	}
	void change(int p,int l,int r)
	{
		if(l>r)
			return;//区间为空就不改了。 
		if(tr[p].l>=l&&tr[p].r<=r)
		{
			ans-=tr[p].r-tr[p].l+1-2*tr[p].cnt;//1 边增多了 tr[p].r-tr[p].l+1-2*tr[p].cnt 条，那么答案就减少这么多条。 
			addtag(p);//更新结点 
			return;
		}
		pushdown(p);//下传懒标记 
		int mid=tr[p].l+tr[p].r>>1; 
		if(l<=mid)
			change(p<<1,l,r);//改左结点 
		if(r>mid)
			change(p<<1|1,l,r);//改右结点 
		pushup(p);//更新结点 
	}
}tree/*缩点后的树*/,cyc/*环*/;
void add(int x,int y)
{
	deg[y]++;
	v[++tot]=y;
	nt[tot]=hd[x];
	hd[x]=tot;
}//加边 
void dfs_cyc(int x)//深搜一遍环 
{
	cyc_rk[x]=++num;//记录序号 
	id[num]=x; 
	for(int i=hd[x];i;i=nt[i])
	{
		int y=v[i];
		if(!vis[y]&&y!=id[1]&&y!=id[cyc_rk[x]-1])//如果在环上，也不是刚刚搜到的那个或者重绕了一圈就搜下去 
		{
			dfs_cyc(y); 
			break;
		}
	}
}
void dfs1(int x,int tp)//tp：离 x 最近的环上点 
{
	size[x]=1;
	d[x]=d[fa[x]]+1;//更新深度 
	rt_id[x]=cyc_rk[tp];//离 x 最近的环上点 
	for(int i=hd[x];i;i=nt[i])
	{
		int y=v[i];
		if(vis[y]&&y!=fa[x])
		{
			fa[y]=x;//更新父亲 
			dfs1(y,tp);
			size[x]+=size[y];//更新子树大小 
			if(size[y]>size[son[x]])
				son[x]=y;//更新重儿子 
		}
	}
}
void dfs2(int x,int tp)
{
	if(cyc_rk[x])//在环上就不搜了 
		return;
	top[x]=tp;//更新重链顶 
	dfn[x]=++cnt;
	if(!son[x])//搜到叶子了 
		return;
	dfs2(son[x],tp);//重儿子的重链顶不变 
	for(int i=hd[x];i;i=nt[i])
	{
		int y=v[i];
		if(y!=fa[x]&&y!=son[x])
			dfs2(y,y);//非重儿子的重链顶是它本身 
	}
}
void change_range(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(d[top[x]]<d[top[y]])
			swap(x,y);
		tree.change(1,dfn[top[x]],dfn[x]);//更新一条重链 
		x=fa[top[x]];
	}
	if(d[x]>d[y])
		swap(x,y);
	tree.change(1,dfn[x]+1,dfn[y]);//边权不更新 LCA，dfn[x]+1 
}
int main()
{
	scanf("%d%d",&n,&q);
	ans=n;//初始答案是 n 
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x,&y),add(x,y),add(y,x);
	for(int i=1;i<=n;i++)
		if(deg[i]==1)
			que.push(i);//叶子节点入队 
	while(!que.empty())
	{
		int x=que.front();
		vis[x]=1;
		que.pop();
		for(int i=hd[x];i;i=nt[i])
		{
			int y=v[i];
			if(!vis[y])
			{
				deg[y]--;//断边 
				if(deg[y]==1)
					que.push(y);//如果成叶子了就入队 
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])//在环里 
		{
			dfs_cyc(i);//搜环 
			break;
		}
	for(int i=1;i<=n;i++)
		if(cyc_rk[i])
			dfs1(i,i);//树剖第一次 dfs 
	d[n+1]=1;//环缩成 n+1 号点 
	for(int i=1;i<=n;i++)
		if(cyc_rk[i])
		{
			if(size[son[i]]>size[son[n+1]])
				son[n+1]=son[i];
			for(int j=hd[i];j;j=nt[j])
			{
				int y=v[j];
				if(vis[y])
					fa[y]=n+1,add(y,n+1),add(n+1,y);
			}
		}//把环上所有点连接的非环上点都连到 n+1 点上 
	dfs2(n+1,n+1);//第二次 dfs
	tree.build(1,1,cnt+1);//树上点建线段树 
	cyc.build(1,1,n-cnt+1);//环上点建线段树 
	while(q--)
	{
		scanf("%d%d",&x,&y);
		change_range(vis[x]?x:n+1,vis[y]?y:n+1);//更新树上点（如果在环上就改 n+1） 
		x=rt_id[x],y=rt_id[y];
		lx=x,ly=y;
		if(x>y)
			swap(x,y);
		if(2*(y-x)<n-cnt+1)//环上路径长度小于环长度一半，直接改两端点中间那一段 
			cyc.change(1,x,y-1);
		else if(2*(y-x)>n-cnt+1)//环上路径长度大于环长度一半，改开头到小编号端点和大编号端点到结尾两段 
			cyc.change(1,1,x-1),cyc.change(1,y,n-cnt+1);
		else//环上路径长度正好等于环长度一半，分类讨论 
		{
			if(id[lx==1?n-cnt+1:lx-1]<id[lx==n-cnt+1?1:lx+1])//从 x 向小编号走字典序更小 
			{
				if(lx>ly) 
					cyc.change(1,ly,lx-1);
				else
					cyc.change(1,1,lx-1),cyc.change(1,ly,n-cnt+1);	
			} 	
			else//否则向大编号走 
			{
				if(lx>ly)
					cyc.change(1,1,ly-1),cyc.change(1,lx,n-cnt+1);	
				else
					cyc.change(1,lx,ly-1);
			}
		}
		printf("%d\n",cyc.tr[1].cnt==n-cnt+1?ans+1:ans);//如果环上都是 1 边，那么答案 +1 
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：3)

### [CF117E Tree or not Tree](https://www.luogu.com.cn/problem/CF117E)

处理基环树：通过拓扑排序剥叶子的方式找到环，从环上任意一点开始 DFS 得到环上每个点的顺序。

将答案设为 $n$。依次加入每条黑色的边，如果两侧不连通则答案减 $1$。如果两侧连通，那么加入这条边后形成环。当且仅当环上的所有边均为黑色才可能发生一次这种情况。

因此答案为 $n$ 减去黑色边数量，且若整个环均为黑色，则答案再加 $1$。

问题转化为维护每条边的颜色。

修改 $(u, v)$ 时，对于树边的部分，用树链剖分 + 线段树维护。对于环边的部分，若 $u, v$ 属于不同子树，设 $u', v'$ 分别为它们的根。如果 $u', v'$ 的距离等于环长一半，需要比较 $u'$ 的前驱和后继求出路径经过了哪一半。路径和环相交的部分是一段区间，区间里面所有边的编号要么是一段区间，要么是一段前驱并上一段后继，都可以用线段树维护。

时间复杂度 $\mathcal{O}((n + q\log n)\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

bool Mbe;
constexpr int N = 1e5 + 5;

int n, q, vis[N];
int k, bel[N], pos[N];
vector<int> e[N], cyc;

int fa[N], dep[N], sz[N], son[N];
int dn, dfn[N], top[N];
void dfs1(int id, int ff) {
  fa[id] = ff;
  bel[id] = bel[ff];
  dep[id] = dep[ff] + 1;
  sz[id] = 1;
  for(int it : e[id]) {
    if(vis[it] || it == ff) continue;
    dfs1(it, id);
    sz[id] += sz[it];
    if(sz[it] > sz[son[id]]) son[id] = it;
  }
}
void dfs2(int id, int tp) {
  dfn[id] = ++dn, top[id] = tp;
  if(son[id]) dfs2(son[id], tp);
  for(int it : e[id]) {
    if(vis[it] || it == fa[id] || it == son[id]) continue;
    dfs2(it, it);
  }
}

void getcycle() {
  vector<int> deg(n + 2, 0);
  queue<int> q;
  for(int i = 1; i <= n; i++) {
    deg[i] = e[i].size(), vis[i] = 1;
    if(deg[i] == 1) q.push(i);
  }
  while(!q.empty()) {
    int t = q.front();
    q.pop(), vis[t] = 0;
    for(int it : e[t]) if(vis[it] && --deg[it] == 1) q.push(it);
  }
  for(int i = 1; i <= n; i++) 
    if(vis[i]) {
      int cur = i, lst = -1;
      do {
        pos[cur] = cyc.size();
        bel[cur] = cur;
        dfs1(cur, cur), dfs2(cur, cur);
        cyc.push_back(cur);
        int nw = -1;
        for(int it : e[cur]) if(vis[it] && it != lst) nw = it;
        lst = cur, cur = nw;
      } while(cur != i);
      k = cyc.size();
      break;
    }
}

struct Segtree {
  int val[N << 2], len[N << 2], laz[N << 2];
  void build(int l, int r, int x) {
    len[x] = r - l + 1;
    if(l == r) return;
    int m = l + r >> 1;
    build(l, m, x << 1);
    build(m + 1, r, x << 1 | 1);
  }
  void tag(int x) {
    laz[x] ^= 1;
    val[x] = len[x] - val[x];
  }
  void down(int x) {
    if(laz[x]) {
      tag(x << 1);
      tag(x << 1 | 1);
      laz[x] = 0;
    }
  }
  void push(int x) {
    val[x] = val[x << 1] + val[x << 1 | 1];
  }
  void modify(int l, int r, int ql, int qr, int x) {
    if(ql > qr) return;
    if(ql <= l && r <= qr) return tag(x);
    int m = l + r >> 1;
    down(x);
    if(ql <= m) modify(l, m, ql, qr, x << 1);
    if(m < qr) modify(m + 1, r, ql, qr, x << 1 | 1);
    push(x);
  }
} t1, t2;

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> q;
  for(int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  getcycle();
  t1.build(1, dn, 1);
  t2.build(0, k - 1, 1);
  
  for(int i = 1; i <= q; i++) {
    int u, v;
    cin >> u >> v;
    if(bel[u] == bel[v]) {
      while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        t1.modify(1, dn, dfn[top[u]], dfn[u], 1);
        u = fa[top[u]];
      }
      if(dep[u] > dep[v]) swap(u, v);
      t1.modify(1, dn, dfn[u] + 1, dfn[v], 1);
    }
    else {
      while(top[u] != bel[u]) {
        t1.modify(1, dn, dfn[top[u]], dfn[u], 1);
        u = fa[top[u]];
      }
      while(top[v] != bel[v]) {
        t1.modify(1, dn, dfn[top[v]], dfn[v], 1);
        v = fa[top[v]];
      }
      t1.modify(1, dn, dfn[bel[u]] + 1, dfn[u], 1);
      t1.modify(1, dn, dfn[bel[v]] + 1, dfn[v], 1);
      u = pos[bel[u]];
      v = pos[bel[v]];

      if(abs(v - u) * 2 != k) {
        if(u > v) swap(u, v);
        if((v - u) * 2 < k) {
          t2.modify(0, k - 1, u, v - 1, 1);
        }
        else {
          t2.modify(0, k - 1, v, k - 1, 1);
          t2.modify(0, k - 1, 0, u - 1, 1);
        }
      }
      else {
        int pr = cyc[u ? u - 1 : k - 1];
        int su = cyc[u + 1 < k ? u + 1 : 0];
        if(pr < su) {
          if(u < v) {
            t2.modify(0, k - 1, v, k - 1, 1);
            t2.modify(0, k - 1, 0, u - 1, 1);
          }
          else {
            t2.modify(0, k - 1, v, u - 1, 1);
          }
        }
        else {
          if(u < v) {
            t2.modify(0, k - 1, u, v - 1, 1);
          }
          else {
            t2.modify(0, k - 1, u, k - 1, 1);
            t2.modify(0, k - 1, 0, v - 1, 1);
          }
        }
      }
    }
    int ans = n - t1.val[1] - t2.val[1];
    if(t2.val[1] == k) ans++;
    cout << ans << "\n";
  }
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：Hoks (赞：3)

## 前言
重剖题单里的，刚好我的[总结文章](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)里把这题当做了练习题，就写篇题解吧。

## 题意分析
有关题意的话，洛谷上的翻译已经写的很详细易懂了。

首先我们考虑下题目中的基环树要是变成树该怎么处理。

用每个线段树维护重链上的 $1$ 边数量。

如果取反就直接把数量改为长度减掉原来的数量即可。

接着考虑翻转时存在两种情况：

1. 将 $0$ 改为 $1$ 时，$1$ 边连接的极大连通块数量会 $-1$。

2. 将 $1$ 边改成 $0$ 边时，极大连通块数量会 $+1$。

那么让初始答案为 $n$，每次操作在线段树修改时顺带统计一下 $1$ 边变化量以更新答案就好了。

那面对基环树呢？

考虑转化为树，把环缩点之后就成了一颗树。

缩点很简单，直接拓扑排序打标机即可。

剩下的环上的点考虑再开一颗线段树维护，就可以顺利完成此题了。

## 代码

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define midt ((t[p].l+t[p].r)>>1)
#define midc ((c[p].l+c[p].r)>>1)
#define ls (p<<1)
#define rs (p<<1|1)
#define int long long
using namespace std;
const int N=100010,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
struct edge
{int v,nxt;}e[N<<2];
struct node
{int l,r,s,lz;}t[N<<2],c[N<<2];
int n,q,tot,cnt,num,ans;
int head[N],rt[N],rk[N],in[N],vis[N],id[N];
int son[N],fa[N],si[N],dep[N],dfn[N],top[N];
queue<int>qu;
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
void add(int u,int v){e[++tot].v=v,e[tot].nxt=head[u],head[u]=tot;}
void dfs(int u)
{
	rk[u]=++num;id[num]=u; 
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;//cout<<u<<" "<<v<<endl;
		if(!vis[v]&&v!=id[1]&&v!=id[rk[u]-1]){dfs(v);break;}
	}
}
void dfs1(int u,int topf)
{
	si[u]=1;dep[u]=dep[fa[u]]+1;rt[u]=rk[topf];
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;//cout<<vis[v]<<" "<<v<<endl;//cout<<u<<" "<<v<<endl;
		if(v==fa[u]||!vis[v]) continue;
		fa[v]=u;dfs1(v,topf);si[u]+=si[v];
		if(si[v]>si[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int topf)
{
	if(rk[u]) return;
	top[u]=topf;dfn[u]=++cnt;
	if(son[u]) dfs2(son[u],topf);
	else return;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
void tag1(int p){t[p].lz^=1;t[p].s=t[p].r-t[p].l+1-t[p].s;}
void pushdown1(int p){if(t[p].lz) tag1(ls),tag1(rs),t[p].lz=0;}
void tag2(int p){c[p].lz^=1;c[p].s=c[p].r-c[p].l+1-c[p].s;}
void pushdown2(int p){if(c[p].lz) tag2(ls),tag2(rs),c[p].lz=0;}
void build1(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;t[p].s=t[p].lz=0;
	if(l==r) return;
	build1(ls,l,mid);build1(rs,mid+1,r);
}
void build2(int p,int l,int r)
{
	c[p].l=l,c[p].r=r,c[p].s=c[p].lz=0;
	if(l==r) return;
	build2(ls,l,mid);build2(rs,mid+1,r);
}
void modify1(int p,int l,int r)
{
	if(l>r) return;
	if(t[p].l>=l&&t[p].r<=r){ans-=t[p].r-t[p].l+1-2*t[p].s;tag1(p);return;}
	pushdown1(p);if(midt>=l) modify1(ls,l,r);if(midt<r) modify1(rs,l,r);
	t[p].s=t[ls].s+t[rs].s;
}
void modify2(int p,int l,int r)
{
	if(l>r) return;
	if(c[p].l>=l&&c[p].r<=r){ans-=c[p].r-c[p].l+1-2*c[p].s;tag2(p);return;}
	pushdown2(p);if(midc>=l) modify2(ls,l,r);if(midc<r) modify2(rs,l,r);
	c[p].s=c[ls].s+c[rs].s;
}
void modify(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify1(1,dfn[top[x]],dfn[x]);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);modify1(1,dfn[x]+1,dfn[y]);
}
signed main()
{
	ans=n=read(),q=read();
	for(int i=1,u,v;i<=n;i++) u=read(),v=read(),add(u,v),add(v,u),in[u]++,in[v]++;
	for(int i=1;i<=n;i++) if(in[i]==1) qu.push(i);
	while(!qu.empty())
	{
		int u=qu.front();qu.pop();vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			if(!vis[v])
			{
				in[v]--;
				if(in[v]==1) qu.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++) if(!vis[i]){dfs(i);break;}
	for(int i=1;i<=n;i++) if(rk[i]) dfs1(i,i);
	n++;dep[n]=1;
	for(int i=1;i<n;i++)
		if(rk[i])
		{
			if(si[son[i]]>si[son[n]]) son[n]=son[i];
			for(int j=head[i];j;j=e[j].nxt)
			{
				int v=e[j].v;
				if(vis[v]) fa[v]=n,add(v,n),add(n,v);
			}
		}
	dfs2(n,n);build1(1,1,cnt+1);build2(1,1,n-cnt);
	for(int i=1,x,y,lx,ly;i<=q;i++)
	{
		x=read(),y=read();modify(vis[x]?x:n,vis[y]?y:n);
		x=rt[x],y=rt[y];lx=x,ly=y;if(x>y) swap(x,y);
		if(2*(y-x)<n-cnt) modify2(1,x,y-1);
		else if(2*(y-x)>n-cnt) modify2(1,1,x-1),modify2(1,y,n-cnt);
		else
			if(id[lx==1?n-cnt:lx-1]<id[lx==n-cnt?1:lx+1])
				if(lx>ly) modify2(1,ly,lx-1);
				else modify2(1,1,lx-1),modify2(1,ly,n-cnt);
			else
				if(lx>ly) modify2(1,1,ly-1),modify2(1,lx,n-cnt);	
				else modify2(1,lx,ly-1);
		print(c[1].s==n-cnt?ans+1:ans);puts("");
	}
	return 0;
}
/*
10 10
3 4
2 8
5 6
1 9
2 1
10 2
3 8
2 7
2 3
7 5
5 10
5 4
4 9
6 3
8 7
5 6
6 4
3 5
6 9
8 1
*/
/*
7
7
7
3
3
4
3
2
5
5
*/
```


---

## 作者：Purslane (赞：0)

# Solution

我严重怀疑随机跳题每道题的概率是不均等的。

考虑目前有多少条边处于“关”的状态。如果原图就是一棵树，那么如果关了 $t$ 条边，必然形成 $t+1$ 个联通块。但是原图是一个基环树，因此如果环上断了一条边，应该减少一个联通块。

我们把所有的边分为环边和树边。树边使用树链剖分。

如果要穿过环，在环上分类讨论即可。代码好长 /ll 不想压进 $\rm 3 \ KB$ 了，感觉没啥意义。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,q,A,B,tot,dep[MAXN],psl[MAXN],rev[MAXN],tfa[MAXN],vis[MAXN]; vector<int> G[MAXN],T[MAXN],cir;
void dfs(int u,int f) {
	vis[u]=1,dep[u]=dep[f]+1,tfa[u]=f;
	for(auto v:G[u]) {
		if(v==f) continue ;
		if(vis[v]) {if(dep[v]<dep[u]) A=v,B=u;}
		else dfs(v,u);
	}
	return ;
}
namespace DS {
	int flp[MAXN<<2],cnt[MAXN<<2];	
	#define lson (k<<1)
	#define rson (k<<1|1)
	#define mid (l+r>>1)
	void modify(int k,int l,int r) {return flp[k]^=1,cnt[k]=r-l+1-cnt[k],void();}
	void push_down(int k,int l,int r) {if(flp[k]) modify(lson,l,mid),modify(rson,mid+1,r);return flp[k]=0,void();}
	void update(int k,int l,int r,int x,int y) {
		if(x>y) return ;
		if(x<=l&&r<=y) return modify(k,l,r),void();push_down(k,l,r);
		if(x<=mid) update(lson,l,mid,x,y);
		if(y>mid) update(rson,mid+1,r,x,y);
		return cnt[k]=cnt[lson]+cnt[rson],void();
	}
	int query(int k,int l,int r,int x,int y) {
		if(x<=l&&r<=y) return cnt[k]; push_down(k,l,r);
		if(y<=mid) return query(lson,l,mid,x,y);
		if(x>mid) return query(rson,mid+1,r,x,y);
		return query(lson,l,mid,x,y)+query(rson,mid+1,r,x,y);
	}
}
namespace TR {
	int dep[MAXN],dfn[MAXN],col[MAXN],sze[MAXN],son[MAXN],top[MAXN],fa[MAXN];	
	void dfs1(int u,int f) {
		sze[u]=1,fa[u]=f,dep[u]=dep[f]+1;
		for(auto v:T[u]) if(v!=f) {
			dfs1(v,u),sze[u]+=sze[v];
			if(sze[v]>sze[son[u]]) son[u]=v;
		}
		return ;
	}
	void dfs2(int u,int anc) {
		col[u]=anc; if(!vis[u]) dfn[u]=++tot;
		if(son[u]&&u!=anc) top[son[u]]=top[u],dfs2(son[u],anc);
		for(auto v:T[u]) if(!top[v]) top[v]=v,dfs2(v,anc);
		return ;
	}
	void chain_update(int u,int v) {
		while(top[u]!=top[v]) if(dep[top[u]]<dep[top[v]]) DS::update(1,1,n,dfn[top[v]],dfn[v]),v=fa[top[v]];	
		else DS::update(1,1,n,dfn[top[u]],dfn[u]),u=fa[top[u]];
		if(u==v) return ;
		if(dfn[u]<dfn[v]) DS::update(1,1,n,dfn[u]+1,dfn[v]);
		else DS::update(1,1,n,dfn[v]+1,dfn[u]);
		return ;
	}
}
void modify(int u,int v) {
	if(TR::col[u]==TR::col[v]) return TR::chain_update(u,v),void();
	TR::chain_update(u,TR::col[u]),TR::chain_update(v,TR::col[v]);
	int dis1,U=TR::col[u],V=TR::col[v];
	if(rev[U]<=rev[V]) dis1=rev[V]-rev[U]; else dis1=rev[V]+cir.size()-rev[U];
	if(dis1<cir.size()-dis1) ;
	else if(dis1>cir.size()-dis1) swap(U,V);
	else {
		int pre=rev[U]+1,nxt=rev[U]-1; if(pre==cir.size()+1) pre=1; if(nxt==0) nxt=cir.size();	
		if(psl[pre]>psl[nxt]) swap(U,V);
	}
	if(rev[U]<=rev[V]) return DS::update(1,1,n,rev[U],rev[V]-1),void();
	return DS::update(1,1,n,rev[U],cir.size()),DS::update(1,1,n,1,rev[V]-1),void();
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;ffor(i,1,n) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(1,0);int tpos=B;while(tpos!=A) cir.push_back(tpos),tpos=tfa[tpos]; cir.push_back(A);
	memset(vis,0,sizeof(vis)); for(auto id:cir) vis[id]=1;
	ffor(u,1,n) for(auto v:G[u]) if(!(vis[u]&&vis[v])) T[u].push_back(v);
	for(auto id:cir) TR::dfn[id]=++tot,rev[id]=tot,psl[tot]=id;
	for(auto id:cir) TR::dfs1(id,0),TR::top[id]=id,TR::dfs2(id,id);
	ffor(i,1,q) {int u,v; cin>>u>>v,modify(u,v),cout<<n-DS::cnt[1]+1-(DS::query(1,1,n,1,cir.size())!=cir.size())<<'\n';}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF117E *2900}$

> - 给定 $n$ 个点的基环树（边无权，无重边自环），每条边有黑白两种颜色。有 $m$ 次操作，每次给定 $u,v$，将 $u \to v$ 的字典序最小的最短路上的边颜色翻转，然后问只保留黑色边后的连通块数量。
> - $1 \le n,m \le 10^5$。

思路非常简单，但是代码【】。

考虑先断开任意一条环边（记作 $p,q$）得到一棵树，每次操作只需要把 $dis(u,v)$ 与 $\min(dis(u,p)+1+dis(q,v),dis(u,q)+1+dis(p,v))$ 比较，如果相等就比较字典序。这里是一些琐碎的分讨，当然你也可以直接上 Misha and LCP on tree 。

然后我们知道如果不考虑环边，有连通块数等于点数减边数。然后对于环边 $p,q$，如果 $p \to q$ 的路径上都是黑边则没有贡献，否则连通块数减 $1$。

树剖实现，时间复杂度 $\mathcal O(q \log^2 n)$。[代码](https://codeforces.com/contest/117/submission/259810308)。

---

