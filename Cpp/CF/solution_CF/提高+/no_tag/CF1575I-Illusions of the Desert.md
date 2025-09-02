# Illusions of the Desert

## 题目描述

Chanek Jones is back, helping his long-lost relative Indiana Jones, to find a secret treasure in a maze buried below a desert full of illusions.

The map of the labyrinth forms a tree with $ n $ rooms numbered from $ 1 $ to $ n $ and $ n - 1 $ tunnels connecting them such that it is possible to travel between each pair of rooms through several tunnels.

The $ i $ -th room ( $ 1 \leq i \leq n $ ) has $ a_i $ illusion rate. To go from the $ x $ -th room to the $ y $ -th room, there must exist a tunnel between $ x $ and $ y $ , and it takes $ \max(|a_x + a_y|, |a_x - a_y|) $ energy. $ |z| $ denotes the absolute value of $ z $ .

To prevent grave robbers, the maze can change the illusion rate of any room in it. Chanek and Indiana would ask $ q $ queries.

There are two types of queries to be done:

- $ 1\ u\ c $ — The illusion rate of the $ x $ -th room is changed to $ c $ ( $ 1 \leq u \leq n $ , $ 0 \leq |c| \leq 10^9 $ ).
- $ 2\ u\ v $ — Chanek and Indiana ask you the minimum sum of energy needed to take the secret treasure at room $ v $ if they are initially at room $ u $ ( $ 1 \leq u, v \leq n $ ).

Help them, so you can get a portion of the treasure!

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1575I/43e878f27686fc876e301e4ea8c8c9f60c7772de.png)In the first query, their movement from the $ 1 $ -st to the $ 2 $ -nd room is as follows.

- $ 1 \rightarrow 5 $ — takes $ \max(|10 + 4|, |10 - 4|) = 14 $ energy.
- $ 5 \rightarrow 6 $ — takes $ \max(|4 + (-6)|, |4 - (-6)|) = 10 $ energy.
- $ 6 \rightarrow 2 $ — takes $ \max(|-6 + (-9)|, |-6 - (-9)|) = 15 $ energy.

 In total, it takes $ 39 $ energy.In the second query, the illusion rate of the $ 1 $ -st room changes from $ 10 $ to $ -3 $ .

In the third query, their movement from the $ 1 $ -st to the $ 2 $ -nd room is as follows.

- $ 1 \rightarrow 5 $ — takes $ \max(|-3 + 4|, |-3 - 4|) = 7 $ energy.
- $ 5 \rightarrow 6 $ — takes $ \max(|4 + (-6)|, |4 - (-6)|) = 10 $ energy.
- $ 6 \rightarrow 2 $ — takes $ \max(|-6 + (-9)|, |-6 - (-9)|) = 15 $ energy.

Now, it takes $ 32 $ energy.

## 样例 #1

### 输入

```
6 4
10 -9 2 -1 4 -6
1 5
5 4
5 6
6 2
6 3
2 1 2
1 1 -3
2 1 2
2 3 3```

### 输出

```
39
32
0```

# 题解

## 作者：幻影星坚强 (赞：4)

我们不知道 $\max(|x|+|y|,|x|-|y|)=|x|+|y|$，我们也不会奇怪技巧，但是我们发现这题有两个操作，所以我们考虑操作分块。

我们 $B$ 个操作分一块，每次查询都将块内的修改的节点所造成影响的那些边改变的边权算出来，不难发现改变的边条数是 $O(B)$ 的，单次查询根据求 $lca$ 以及求链上较上面端点的儿子的方式不同有 $O(B\log n)$ 与 $O(B)$ 两种复杂度，每次预处理都重新求一遍每个节点到根的路径和。复杂度为 $O(n\sqrt{n\log n})$ 或 $O(n\sqrt{n})$，这里给出 $O(n\sqrt{n\log n})$ 的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int block = 300;
struct bian
{
	int from, to;
}eg[N << 1];
int front[N], num;
void add(int x, int y)
{
	eg[++ num].to = y;
	eg[num].from = front[x];
	front[x] = num;
}
int n, q;
int a[N];
struct QUE
{
	int op, x, y;
}que[N];
int siz[N], son[N], dep[N], top[N], fa[N], dfn[N];
void dfs1(int o, int from)
{
	dep[o] = dep[from] + 1;
	fa[o] = from;
	siz[o] = 1;
	for (int i = front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(to == from)continue;
		dfs1(to, o);
		siz[o] += siz[to];
		if(siz[to] > siz[son[o]])son[o] = to;
	}
}
void dfs2(int o, int tp)
{
	dfn[o] = ++ num;
	top[o] = tp;
	if(son[o]) dfs2(son[o], tp);
	for (int i = front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(to == son[o] || to == fa[o])continue;
		dfs2(to, to);
	}
}
int vis[N], now[N], tot;
long long Dep[N];
void dfs3(int o, int from)
{
	vis[o] = 0;
	for (int i = front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(to == from)continue;
		Dep[to] = Dep[o] + max(abs(a[o] - a[to]), abs(a[o] + a[to]));
		dfs3(to, o);
	}
}
int LCA(int x, int y)
{
	while(top[x] != top[y])
	{
		if(dep[top[x]] < dep[top[y]])
		swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y])
	swap(x, y);
	return y;
}
int jump(int x, int y)
{
	while(top[x] != top[y])
	{
		x = top[x];
		if(fa[x] == y)
		return x;
		x = fa[x];
	}
	return son[y];
}
bool check(int x, int y){return dfn[x] <= dfn[y] && dfn[y] < dfn[x] + siz[x];}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i)
	cin >> a[i];
	for (int i = 1; i < n; ++ i)
	{
		int x, y;
		cin >> x >> y;
		add(x, y);
		add(y, x);
	}
	num = 0;
	dfs1(1, 0);
	dfs2(1, 1);
	for (int i = 1; i <= q; ++ i) cin >> que[i].op >> que[i].x >> que[i].y;
	for (int l = 1; l <= q; l += block)
	{
		int r = min(q, l + block - 1);
		dfs3(1, 0);
		tot = 0;
		for (int i = l; i <= r; ++ i)
		vis[que[i].x] = 1;
		for (int i = 1; i <= n; ++ i)
		if(vis[i])
		now[++ tot] = i;
		for (int i = l; i <= r; ++ i)
		{
			if(que[i].op == 1) a[que[i].x] = que[i].y;
			else
			{
				int x = que[i].x, y = que[i].y;
				int lca = LCA(que[i].x, que[i].y);
				long long ans = Dep[que[i].x] + Dep[que[i].y] - Dep[lca] * 2;
				for (int i = 1; i <= tot; ++ i)
				{
					int o = now[i];
					if(check(lca, o) && check(o, x))
					{
						if(o != x)
						{
							int tt = jump(x, o);
							ans += - (Dep[tt] - Dep[o]) + max(abs(a[o] - a[tt]), abs(a[o] + a[tt]));
						}
						if(o != lca)
						{
							int tt = fa[o];
							if(vis[tt] == 0)
							ans += - (Dep[o] - Dep[tt]) + max(abs(a[o] - a[tt]), abs(a[o] + a[tt]));
						}
					}
					if(check(lca, o) && check(o, y))
					{
						if(o != y)
						{
							int tt = jump(y, o);
							ans += - (Dep[tt] - Dep[o]) + max(abs(a[o] - a[tt]), abs(a[o] + a[tt]));
						}
						if(o != lca)
						{
							int tt = fa[o];
							if(vis[tt] == 0)
							ans += - (Dep[o] - Dep[tt]) + max(abs(a[o] - a[tt]), abs(a[o] + a[tt]));
						}
					}
				}
				cout << ans << "\n";
			}
		}
	}
}
```



---

## 作者：wcyQwQ (赞：2)


[题目传送门](https://www.luogu.com.cn/problem/CF1575I)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/11/01/CF1575I%20Illusions%20of%20the%20Desert/)

## 前言

这个菜狗不知道 $\max(|a_x-a_y|,|a_x+a_y|) = |a_x|+|a_y|$，所以写了一个题解中都没有的巨大难写的线段树做法。

### 前置芝士

树链剖分，线段树。


## 分析

用树链剖分转化为区间问题之后，我们就把问题转化为了求这样一个式子
$$
\sum_{i=l + 1}^r \max(|a_i-a_{i-1}|,|a_i+a_{i-1}|)
$$
并且支持单点修改。

考虑线段树，我们维护 $3$ 个值 $la, ra, sum$，分别表示当前区间的左端点，右端点和答案。依照定义可以这样从子节点转移给父节点。

```c++
inline void pushup(int p)
{
    t[p].la = t[p << 1].la;
    t[p].ra = t[p << 1 | 1].ra;
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum + max(abs(t[p << 1].ra - t[p << 1 | 1].la), abs(t[p << 1].ra + t[p << 1 | 1].la));
}
```

然后查询的时候就把左右区间的答案全部合并起来，树上查询也如法炮制，那么我们就用一种巨大难写的线段树通过了本题。

## 代码

```c++
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int N = 2e5 + 10;
int a[N], b[N];
int h[N], e[N], ne[N], idx;
int fa[N], dep[N], son[N], sz[N], top[N], dfn[N], tt;
struct node
{
    int l, r, la, ra;
    ll sum;
    node() {l = r = la = ra = sum = 0;}
} t[N << 2];

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void dfs1(int u, int p)
{
    fa[u] = p, dep[u] = dep[p] + 1, sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == p) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

inline void dfs2(int u, int t)
{
    top[u] = t, dfn[u] = ++tt, b[tt] = a[u];
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

inline void pushup(int p)
{
    t[p].la = t[p << 1].la;
    t[p].ra = t[p << 1 | 1].ra;
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum + max(abs(t[p << 1].ra - t[p << 1 | 1].la), abs(t[p << 1].ra + t[p << 1 | 1].la));
}

inline void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r;
    if (l == r)
    {
        t[p].la = t[p].ra = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void modify(int p, int x, int v)
{
    if (t[p].l == t[p].r)
    {
        t[p].la = t[p].ra = v;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if (x <= mid) modify(p << 1, x, v);
    else modify(p << 1 | 1, x, v);
    pushup(p);
}

inline node merge(node l, node r)
{
    node u;
    u.la = l.la, u.ra = r.ra;
    u.sum = l.sum + r.sum + max(abs(l.ra - r.la), abs(l.ra + r.la));
    return u;
}

inline node query(int p, int l, int r)
{
    if (l <= t[p].l && t[p].r <= r) return t[p];
    int mid = (t[p].l + t[p].r) >> 1;
    if (l > mid) return query(p << 1 | 1, l, r);
    if (r <= mid) return query(p << 1, l, r);
    return merge(query(p << 1, l, r), query(p << 1 | 1, l, r));
}

inline ll query_path(int u, int v)
{
    ll res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, dfn[top[u]], dfn[u]).sum;
        res += max(abs(a[top[u]] - a[fa[top[u]]]), abs(a[top[u]] + a[fa[top[u]]]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res += query(1, dfn[u], dfn[v]).sum;
    return res;
}

int main()
{
    memset(h, -1, sizeof h);
    int n = read(), q = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n - 1; i++)
    {
        int a = read(), b = read();
        add(a, b);
        add(b, a);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    while (q--)
    {
        int op = read(), u = read(), v = read();
        if (op == 1) modify(1, dfn[u], v), a[u] = v;
        else printf("%lld\n", query_path(u, v));
    }
    return 0;
}
```





---

## 作者：唐一文 (赞：2)

我是傻逼我不会算 $\max(|x-y|,|x+y|)$ ~~然后我用奇奇怪怪的方法过了这题。~~

~~假设我们不知道~~$\sout{\max(|x-y|,|x+y|)=|x|+|y|}$~~。~~

题意：

一颗 $n$ 个结点的树，点有点权，一条边 $(u,v)$ 的边权为 $\max(|a_u-a_v|,|a_u+a_v|)$，$m$ 次操作，每次修改一个点的点权或查询一条路径上的边权和。

首先可以边权转点权，然后一个很显然的暴力就是查询时树剖，修改时暴力将与之相邻的边权都修改一遍。

这样暴力虽然查询是 $O\left(\log^2n\right)$ 的，但是修改是 $O\left( \deg\times \log n\right)$ 的，会被菊花图之类的卡掉。

那么可以用根号分治来平衡修改和查询的复杂度，定义一个阈值 $B$。

在树剖时将 $\deg$ 大于 $B$ 的点单独拿出来当作一条链的链顶，这样的点不超过 $\dfrac{n}{B}$ 个。

修改时只暴力修改 $\deg\leq B$ 的点，每次修改 $O\left(B\log n\right)$。

然后在查询的时候将链顶和其重儿子的边单独拿出来修改，将链顶和其父亲的边单独拿出来修改，每次查询 $O\left(\dfrac{n}{B}\log n\right)$。

大概是当 $B=\sqrt{n}$ 的时候最优。

~~但是我场上 debug de不出来，把 B 的大小改成 n 交了一发（暴力），想看一下到底是不是根号分治出了问题，结果直接过了。刚刚调出来发现竟然跑不过暴力。~~

[根号分治](https://www.luogu.com.cn/paste/aotyonka)，[~~暴力~~](https://www.luogu.com.cn/paste/erhk3nr6)~~（其实没啥区别就是暴力更快）~~

---

## 作者：Yoimiyamwf (赞：1)

# 题意
给定一棵树，每个节点均有一个点权 $a_i$。对于一条边 $e=(u,v)$，其边权定义为 $w_e=\operatorname{max}(|a_u+a_v|,|a_u-a_v|)$。维护一个数据结构，使其支持单点修改权值和查询路径长两种操作。

# 分析
对于每条边 $e=(u,v)$ 的边权 $w_e$，容易发现 $w_e=\operatorname{max}(|a_u+a_v|,|a_u-a_v|)=|a_u|+|a_v|$，所以我们只需要维护每个区间的点权绝对值之和即可。

对于路径总长，设路径上各点点权分别为 $a_1,a_2,...,a_n$，则 $len=(|a_1|+|a_2|)+(|a_2|+|a_3|)+...+(|a_{n-1}|+|a_n|)=2\times\sum _ {i = 1} ^ n |a_i|-|a_1|-|a_2|$。

于是，本题就可以通过维护点权和来解决，显然树链剖分加线段树可以胜任。

# 代码
```
#include <bits/stdc++.h>
#define in inline
#define rint register int
#define r(a) runtimerror(a)
#define w(a) wronganswer(a)
#define wl(a) wronganswer(a);putchar('\n')
#define ws(a) wronganswer(a);putchar(' ')
using namespace std;
typedef long long ll;
ll a[100010],newn[100010],c;
int n,m,u,v,opt,tot,cnt,head[100010],size[100010],son[100010],dep[100010],fa[100010],nid[100010],top[100010];
template <typename t> void wronganswer(t a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) wronganswer(a/10);
	putchar(a%10^48);
}
template <typename t> in void runtimerror(t &a){
	char ch=getchar();
	t x=1,f=0;
	while(!isdigit(ch)){
		if(ch=='-') x=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		f=(f<<3)+(f<<1)+(ch^48);
		ch=getchar();
	}
	a=x*f;
}
struct Edge{
	int to,nex;
}edge[200010];
in void add_edge(int from,int to){
	edge[++tot]={to,head[from]};
	head[from]=tot;
}
void dfs1(int id,int fat,int dp){
	fa[id]=fat,dep[id]=dp,size[id]=1;
	for(rint i=head[id];i;i=edge[i].nex){
		if(edge[i].to==fat) continue;
		dfs1(edge[i].to,id,dp+1);
		size[id]+=size[edge[i].to];
		if(size[edge[i].to]>size[son[id]]) son[id]=edge[i].to;
	}
}
void dfs2(int id,int t){
	top[id]=t,nid[id]=++cnt,newn[cnt]=abs(a[id]);
	if(!son[id]) return;
	dfs2(son[id],t);
	for(rint i=head[id];i;i=edge[i].nex){
		if(edge[i].to==son[id]||edge[i].to==fa[id]) continue;
		dfs2(edge[i].to,edge[i].to);
	}
}
template <typename t> struct segment_tree{
	struct segment{
		int l,r;
		t sum;
	}s[400010];
	in void pushup(int id){
		s[id].sum=s[id<<1].sum+s[id<<1|1].sum;
	}
	void build(int id,int l,int r){
		if(l==r){
			s[id]={l,r,newn[l]};
			return;
		}
		s[id]={l,r};
		int mid=l+r>>1;
		build(id<<1,l,mid);
		build(id<<1|1,mid+1,r);
		pushup(id);
	}
	void modify(int id,int target,t val){
		if(s[id].l==s[id].r){
			s[id].sum=val;
			return;
		}
		int mid=s[id].l+s[id].r>>1;
		if(mid>=target) modify(id<<1,target,val);
		else modify(id<<1|1,target,val);
		pushup(id);
	}
	t query(int id,int l,int r){
		if(s[id].l>=l&&s[id].r<=r) return s[id].sum;
		int mid=s[id].l+s[id].r>>1;
		t ans=0;
		if(mid>=l) ans+=query(id<<1,l,r);
		if(mid<r) ans+=query(id<<1|1,l,r);
		return ans;
	}
	t query_path(int u,int v){
		t ans=-query(1,nid[u],nid[u])-query(1,nid[v],nid[v]);
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			ans+=2*query(1,nid[top[u]],nid[u]);
			u=fa[top[u]];
		}
		if(dep[u]<dep[v]) swap(u,v);
		ans+=2*query(1,nid[v],nid[u]);
		return ans;
	}
};
segment_tree <ll> t;
int main(){
	r(n),r(m);
	for(rint i=1;i<=n;i++){
		r(a[i]);
	}
	for(rint i=1;i<n;i++){
		r(u),r(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	t.build(1,1,n);
	while(m--){
		r(opt);
		if(opt==1){
			r(u),r(c);
			t.modify(1,nid[u],abs(c));
		}else{
			r(u),r(v);
			wl(t.query_path(u,v));
		}
	}
	return 0;
}
```


---

## 作者：徐天乾 (赞：1)

# 题意
给定一个有 $n$ 个节点的树，一条 $x$ 到 $y$ 的边的权值是 $\max(|a_{x}-a_{y}|,|a_{x}+a_{y}|)$ 。现有 $q$ 个操作，操作分两种：
1. 将 $a_{x}$ 变为 $y$；
2. 问从 $x$ 到 $y$ 最短路径上所有边权之和。

# 前置知识
树链剖分，如果不会的话可以先做
[模板](https://www.luogu.com.cn/problem/P3384)。

# 思路
我们首先需要知道一个重要的等式： $\max(|a_{x}-a_{y}|,|a_{x}+a_{y}|)=|a_{x}|+|a_{y}|$。

证明：不妨令 $a_{x}^2+a_{y}^2=A(A>=0)$，$2\times a_{x} \times a_{y}=B$

易知:           $\max(|a_{x}-a_{y}|,|a_{x}+a_{y}|)=|a_{x}|+|a_{y}|$
$\Rightarrow$   $\max(|a_{x}-a_{y}|,|a_{x}+a_{y}|)^2=(|a_{x}|+|a_{y}|)^2$
$\Rightarrow$   $\max(|a_{x}-a_{y}|^2,|a_{x}+a_{y}|^2)=(|a_{x}|+|a_{y}|)^2$
$\Rightarrow$   $\max(A^2-B,A^2+B)=A^2+|B|$
$\Rightarrow$   $\max(-B,B)=|B|$
 
证毕！

不妨设从 $x$ 到 $y$ 最短路径上的点的点值依次为 $u_{1},u_{2},...,u_{t}$，那么题目所求的 $\max(|u_{1}-u_{2}|,|u_{1}+u_{2}|)+...+\max(|u_{t-1}-u_{t}|,|u_{t-1}+u_{t}|)=2 \times (|u_{1}+...+u_{t}|)-|u_{1}|-|u_{t}|$。
边权之和转变成了点权和，要求一条路径上的点权和，也自然会想到用树链剖分来进行维护，之后这就是一道板子题了。（不过树链剖分我调了1小时......）

# 代码
```cpp
    #include<bits/stdc++.h>
    #define int long long //不开long long见祖宗
    #define M 500500
    using namespace std;
    int i,n,m,x,y,z,rt,cnt,mod,T,a[M],f[M],h[M],u[M],v[M],id[M],add[M],sum[M],top[M],size[M];
    vector<int> A[M]; 
    void build(int l,int r,int num){
    	if (l==r){sum[num]=abs(a[l]);return ;} //维护的值是该点的绝对值
    	int m=(l+r)>>1;
    	build(l,m,num<<1);build(m+1,r,num<<1|1);
    	sum[num]=sum[num<<1]+sum[num<<1|1];
    	return ;
    }
    void pushdown(int num,int l,int r){
    	if (add[num]==0) return ;
    	add[num<<1]+=add[num];  add[num<<1|1]+=add[num];
    	sum[num<<1]+=add[num]*l;  sum[num<<1|1]+=add[num]*r;
    	add[num]=0;return ;
    }
    void update(int L,int R,int c,int l,int r,int num){
    	if (L<=l&&r<=R) {sum[num]+=c*(r-l+1);add[num]+=c;return ;}
    	int m=(l+r)>>1;
    	pushdown(num,m-l+1,r-m);
    	if (L<=m) update(L,R,c,l,m,num<<1);
    	if (R>m) update(L,R,c,m+1,r,num<<1|1);    
    	sum[num]=sum[num<<1]+sum[num<<1|1];
    	return ; 
    }
    int query(int L,int R,int l,int r,int num){
    	if (L<=l&&r<=R) return sum[num];
    	int m=(l+r)>>1,ans=0;
    	pushdown(num,m-l+1,r-m);
    	if (L<=m) ans+=query(L,R,l,m,num<<1);
    	if (R>m) ans+=query(L,R,m+1,r,num<<1|1);
    	return ans;
    }
    void dfs1(int t,int w){
    	int i,maxn=0,len=A[t].size();
    	h[t]=h[w]+1;f[t]=w;size[t]=1;
    	for (i=0;i<len;i++) 
    		if (A[t][i]!=w){
    			dfs1(A[t][i],t); 
    			size[t]+=size[A[t][i]];
    			if (size[A[t][i]]>maxn)
    				maxn=size[A[t][i]],u[t]=A[t][i];
    		}	
    	return ;
    }
    void dfs2(int t,int w){
    	id[t]=++cnt;a[cnt]=v[t];top[t]=w;
    	if (!u[t]) return ;
    	dfs2(u[t],w);int i,len=A[t].size();
    	for (i=0;i<len;i++)
    		if (A[t][i]!=f[t]&&A[t][i]!=u[t])
    			dfs2(A[t][i],A[t][i]); 
    	return ;
    }
    int Query(int x,int y){
        int ans=0;
        while (top[x]!=top[y]){
            if (h[top[x]]<h[top[y]]) swap(x,y);
            ans+=query(id[top[x]],id[x],1,n,1); 
            x=f[top[x]];
        }
        if (h[x]>h[y]) swap(x,y);
        ans+=query(id[x],id[y],1,n,1);
        return ans;
    }
    void Update(int x,int y,int k){
        while (top[x]!=top[y]){
            if(h[top[x]]<h[top[y]]) swap(x,y);
            update(id[top[x]],id[x],k,1,n,1);
            x=f[top[x]];
        }
        if(h[x]>h[y]) swap(x,y);
        update(id[x],id[y],k,1,n,1);
        return ;
    }
    signed main(){
    	scanf("%lld %lld",&n,&m);
    	for (i=1;i<=n;i++) scanf("%lld",&v[i]);
    	for (i=1;i<n;i++){
    		scanf("%lld %lld",&x,&y);
    		A[x].push_back(y);
    		A[y].push_back(x);
    	}
    	dfs1(1,0);dfs2(1,1);build(1,n,1);
    	for (i=1;i<=m;i++){
    		scanf("%lld %lld %lld",&T,&x,&y);
    		if (T==1)  Update(x,x,abs(y)-abs(v[x])),v[x]=y; //修改
    		if (T==2)  printf("%lld\n",Query(x,y)*2-abs(v[x])-abs(v[y]));  //查询
    	}
    	return 0;
    } 
```




---

## 作者：Valhalla_Is_Calling (赞：1)

### $\operatorname{Description.}$
给出一棵树，第 $i$ 个点的点权为 $a_i$，从点 $i$ 走到点 $j$ 的代价是 $\operatorname{max}(|a_i-a_j|,|a_i+a_j|)$，存在修改点权的操作，每次询问查询两点之间的通行代价。

### $\operatorname{Solution.}$
很重要的一个转化是 $\operatorname{max}(|a_i-a_j|,|a_i+a_j|)=|a_i|+|a_j|$，如果觉得自己在考场上看不出来这个的话请移步另一篇题解。

有了这个转化这个就成模板题了，显然从 $i$ 走到 $j$ 经过的所有点除了这俩点之外都有 $2\times |a_k|$ 的贡献，所以树剖维护一下修改和查询即可，每次查询的答案即为路径上的点权和的两倍减去两个端点的点权即可。

---

## 作者：rainygame (赞：1)

不是为啥题解里没有单 $\log$ 做法啊？

假设不知道 $\max\{\lvert x+y\rvert,\lvert x-y\rvert\}=\lvert x\lvert+\lvert y\rvert$。

设 $b_u=\max\{\lvert a_u+a_{fa_u}\lvert,\lvert a_u-a_{fa_u}\lvert\}$，钦定 $b_1=0$。设 $d_u$ 表示 $u\rightarrow 1$ 路径的 $b$ 之和。那么查询可以转化成 $O(1)$ 次查询 $d_x$。

修改 $b$ 就直接修改子树内点的 $d$ 即可，用 BIT 维护每次修改是 $O(\log n)$ 的。但是问题在于修改的不仅包括自己的 $b$，也包括儿子们的 $b$，数量级是 $O(n)$ 的。

考虑阈值分治。设修改时只修改前 $B$ 重的儿子，那么每次修改的时间复杂度是 $O(B\log n)$ 的。询问时先计算所有前 $B$ 重的儿子对答案的贡献。注意到一个点到根的路径上最多只有 $\log_{B+1}n$ 个轻儿子，对于这些轻儿子暴力计算 $b$ 即可。所以时间复杂度为 $O(nB\log n+n\log_{B+1} n)$，取 $B=1$ 最优。时间复杂度为 $O(n\log n)$。

好吧其实就是树剖。[submission](https://codeforces.com/problemset/submission/1575/321009492)

---

## 作者：__DDDDDD__ (赞：0)

# 前言

~~（好像没有 LCT 的题解？不水一发太可惜了）~~

这里提供一种 LCT 做法，供各位大佬参考%%%


# 题目分析

[$Link$](https://www.luogu.com.cn/problem/CF1575I)

给定一棵树，每条边有边权，要求维护以下两种操作：

1. 单点点权修改；

1. 查询路径上的边权和。

不同的是，本题中边权值定义为该边连接两点点权的和、差绝对值的最大值，即对于边 $(u,v)$，该边边权值为 $\max(|a_{u}+a_{v}|,|a_{u}-a_{v}|)$。

但是，~~从其他题解的分析可知~~，原式 $\max(|a_{u}+a_{v}|,|a_{u}-a_{v}|) \Leftrightarrow |a_{u}|+|a_{v}|$。
所以对于一条路径 $x_{1} \to x_{2} \to x_{3} \to ... \to x_{n-1} \to x_{n}$，路径上的边权和为：

 $|a_{x1}| + |a_{x2}|+|a_{x2}|+|a_{x3}|+|a_{x3}|+...+|a_{n-1}|+|a_{n-1}|+|a_{n}|$

$\Rightarrow (|a_{x1}| + |a_{x2}|+|a_{x3}|+...+|a_{n-1}|+|a_{n}|) \times 2-|a_{x1}|-|a_{n}|$

故对于一条路径，路径上的边权和等于**路径上点权绝对值的和的两倍**减去**头尾两点的点权绝对值**。

对应在 LCT 中，即 $split(u,v)$ 后，输出 $sum[v]\times2-val[u]-val[v]$。

详细代码及注释如下：

# 代码+注释

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
inline int read(){				// 快读直接忽略负号，相当于取绝对值 
	re int x=0,f=1;re char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
const int maxn=5e5+10;			// 自信开大数组（bushi） 
int n,m;
struct Link_Cut_Tree{
	int fa[maxn],c[maxn][2];	// 分别存储父节点与子节点 
	bool rev[maxn];				// 翻转懒标记 
	int a[maxn],v[maxn];		// a[]存储单点点权，v[]存储总和 
	inline void spread(int x){
		if(rev[x]){
			rev[c[x][0]]^=1;
			rev[c[x][1]]^=1;
			rev[x]=0;
			swap(c[x][0],c[x][1]);
		}
	}
	inline void update(int x){
		v[x]=v[c[x][0]]+v[c[x][1]]+a[x];
	}
	inline bool isroot(int x){
		return c[fa[x]][0]!=x&&c[fa[x]][1]!=x;
	}
	inline void rotate(int x){
		int y=fa[x],z=fa[y];
		int dir=(c[y][0]==x);
		c[y][dir^1]=c[x][dir];
		fa[c[x][dir]]=y;
		fa[x]=z;
		if(!isroot(y))c[z][c[z][1]==y]=x;
		fa[y]=x;
		c[x][dir]=y;
		update(y);update(x);
	}
	int st[maxn],top;
	inline void splay(int x){
		top=1;
		st[top]=x;
		for(int i=x;!isroot(i);i=fa[i])st[++top]=fa[i];
		while(top)spread(st[top--]);
		while(!isroot(x)){
			int y=fa[x],z=fa[y];
			if(!isroot(y)){
				(c[y][0]==x)^(c[z][0]==y)?rotate(x):rotate(y);
			}
			rotate(x);
		}
	}
	inline void access(int x){
		for(int t=0;x;t=x,x=fa[x]){
			splay(x);c[x][1]=t;update(x);
		}
	}
	inline void makeroot(int x){
		access(x);splay(x);rev[x]^=1;
	}
	inline int findroot(int x){
		access(x);splay(x);spread(x);
		while(c[x][0])x=c[x][0],spread(x);
		splay(x);
		return x;
	}
	inline void split(int x,int y){
		makeroot(x);access(y);splay(y);
	}
	inline void link(int x,int y){
		makeroot(x);
		if(findroot(y)!=x)fa[x]=y;
	}
}lct;
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){	// 点权初始值 
		lct.a[i]=read();
	}
	for(int i=1;i<n;i++){	// 连边 
		int u=read(),v=read();
		lct.link(u,v);
	}
	for(int i=1;i<=m;i++){	// 操作 
		int opt=read();
		if(opt==1){
			int x=read(),v=read();
			lct.splay(x);
			lct.a[x]=v;
		}else{
			int u=read(),v=read();
			lct.split(u,v);
			printf("%lld\n",lct.v[v]*2-lct.a[u]-lct.a[v]);
		}
	}
	return 0;
}
```


---

## 作者：郑朝曦zzx (赞：0)

## 题解

容易想到树链剖分，但是树剖是在点上建立线段树，这个是边权，好像不太好写。

凭借初一数学的经验，我们要拆开绝对值以解决问题。

**先给公式：**

$\max(|x+y|, |x-y|) = |x| + |y|$

**证明：**

楼上大佬用平方证明的，其实我们可以根据初一所学数学知识，对 $x, y$ 的正负性进行分类讨论即可。

- 如果 $x, y$ 中有 $0$ 式子显然成立。

- 若 $0\lt x, y$，化简得：$x + y = x + y$

- 若 $x, y \lt 0$，化简得：$-x-y = -x-y$

- 若 $y \lt 0\lt x$，化简得：$x - y = x - y$

- 若 $x \lt 0\lt y$，化简得：$y - x = y - x$

**问题转化**

有了式子就好办了，**边权就转化成了点权**，对于一条路径，首尾的点权会算一遍，中间会算两遍。然后就是树链剖分板子了。

## 代码
[代码实现](https://codeforces.com/contest/1575/submission/188298805)

---

## 作者：Lamb_Carp (赞：0)

# advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17738287.html)看呢。

# prologue

还是太菜了，这个 154 行的树剖20min才敲完。

# analysis

首先，处理这个给到我们的这个式子。

$$ \max(| a _ u + a _ v |, | a _ u - a _ v |) $$

我们可以分类讨论：

- $a > 0, b > 0$:
  显然 $a + b > a - b$, 所以上式等于 $a + b \Rightarrow | a | + | b | $
- $a > 0, b < 0 \iff a < 0, b > 0$
  这个时候，我们只需要讨论 $a > 0, b < 0$ 的情况就好了。我们将 $b$ 的符号拿出来，$\Rightarrow a - (- | b |) \Rightarrow a + | b | \Rightarrow | a | + | b |$
  
- $a < 0, b < 0$
  操作同上， $ | -(| a | + | b |) | \Rightarrow | a | + | b | $。
  
综上：
$$\max(| a _ u + a _ v |, | a _ u - a _ v |) \iff | a | + | b | $$

对于一条路径的询问，我们把每两个点之间的距离拿出来，不断累加，就可以知道，这一段路径的长度就是下式。（其中 $dis _ {u \to v}$ 表示从 $u$ 到 $v$  的距离， $sum _ {u \to v}$ 表示从 $u$ 到 $v$ 的点值的绝对值之和，$w_u$ 和 $w_v$ 表示这两个点的点权）
$$ dis _ {u \to v} = 2 \cdot sum _ {u \to v} - | w_u | - | w_v | $$

之后就是正常实现一个**树链剖分**和**线段树**即可。

# code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll

const ll N = 1e5 + 10, M = N << 1;

ll n, m;

ll tot, ne[M], e[M], h[N], w[N];

ll son[N], top[N], id[N], cnt, fa[N], dep[N], nw[N], sz[N];

struct node
{
    ll l, r;
    ll dis;
}tr[N << 2];

inline void add(ll a, ll b)
{
    ne[++tot] = h[a], h[a] = tot, e[tot] = b;
}

inline void dfs1(ll u, ll fath, ll depth)
{
    fa[u] = fath, dep[u] = depth, sz[u] = 1;

    for(rl i=h[u]; ~i; i = ne[i])
    {
        ll v = e[i];
        if(v == fath) continue;
        dfs1(v, u, depth + 1);
        sz[u] += sz[v];
        if(sz[son[u]] < sz[v]) son[u] = v;
    }
}

inline void dfs2(ll u, ll t)
{
    id[u] = ++ cnt, nw[cnt] = w[u], top[u] = t;

    if(!son[u]) return ;
    dfs2(son[u], t);

    for(rl i=h[u]; ~i; i = ne[i])
    {
        ll v = e[i];
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

inline void pushup(ll u)
{
    tr[u].dis = abs(tr[u << 1].dis) + abs(tr[u << 1 | 1].dis);
}

inline void build(ll u, ll l, ll r)
{
    tr[u] = {l, r, abs(nw[r])};

    if(l == r) return ;

    ll mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);

    pushup(u);
}

inline void update(ll u, ll l, ll r, ll k)
{
    if(tr[u].l == l && tr[u].l == tr[u].r)
    {
        tr[u].dis = k;
        return ;
    }

    ll mid = tr[u].l + tr[u].r >> 1;
    
    if(l <= mid) update(u << 1, l, r, k);
    if(r > mid) update(u << 1 | 1, l, r, k);

    pushup(u);
}

inline ll query(ll u, ll l, ll r)
{
    ll res = 0;

    if(l <= tr[u].l && r >= tr[u].r) return tr[u].dis;

    ll mid = tr[u].l + tr[u].r >> 1;
    
    if(l <= mid) res += query(u << 1, l, r);
    if(r > mid) res += query(u << 1 | 1, l, r);

    return res;
}

inline void upd_point(ll u, ll k)
{
    update(1, id[u], id[u], k);
}

inline ll query_path(ll u, ll v)
{
    ll res = - query(1, id[u], id[u]) - query(1, id[v], id[v]);

    while(top[u] != top[v])
    {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res += 2 * query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }

    if(dep[u] < dep[v]) swap(u, v);

    res += 2 * query(1, id[v], id[u]);

    return res;
}

int main()
{
    // freopen("1.in", "r", stdin), freopen("1.out", "w", stdout);

    cin >> n >> m;

    memset(h, -1, sizeof h);

    for(rl i=1; i <= n; ++ i) cin >> w[i];

    for(rl i=1; i < n; ++ i)
    {
        ll a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs1(1, -1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    while(m -- )
    {
        ll t, u, v;
        cin >> t >> u >> v;
        if(t == 1) upd_point(u, abs(v));
        else cout << query_path(u, v) << endl;
    }

    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

就是……随便推一些式子，随便写一个[树剖](https://www.luogu.com.cn/problem/solution/P3384)，就随便过了……
## 分析
首先发现此题的式子一看就不是很友好。所以尝试化简。

原式：$max(|a_u + a_v|, |a_u - a_v|)$。

分类讨论：

- 当 $a_u > 0, a_v > 0$ 时，显然有 原式 $= a_u + a_v$；

- 当 $a_u > 0, a_v < 0$ 时，
$|a_u - a_v| = |a_u + |a_v||$，
$|a_u + a_v| = |a_u - |a_v||$。
肉眼可见，第一个式子大于第二个式子。即 原式 $= a_u + |a_v|$；

- 当 $a_u < 0, a_v > 0$ 时，
$|a_u + a_v| = |a_v - |a_u|| = |-(|a_u| - a_v)| = ||a_u| - a_v|$，
$|a_u - a_v| = |-a_v - |a_u|| = |-(|a_u| + a_v)| = ||a_u| + a_v|$，
这样就跟上一种情况差不多，即 原式 $=|a_u| + a_v$；

- 当 $a_u < 0, a_v < 0$ 时，显然有 原式 $=|a_u| + |a_v|$。

注意到在以上分类讨论的结果中，没有被开绝对值的数都是正数，而正数的绝对值等于其自身。故 原式 $= |a_u| + |a_v|$。~~比原式漂亮多了~~。

这样，我们发现询问时的答案与每个点原本的点权无关，只与其原本点权的绝对值有关。所以可以把所有点的点权 $a_i$ 改为 $|a_i|$，而不对答案造成影响。以下所述 $a_i$ 也即为 $|a_i|$。

到这里，我们就将每一条边的边权转换到了其两个端点上。题目所要求的求两点间最短路的距离也可以转换到两点间最短路上所有点的点权上。故我们就可以只维护树上每两点间的点权和即可。考虑树链剖分。每次询问时，设询问的两点为 $u$ 和 $v$，则我们只需要求出 $u$ 和 $v$ 之间最短路上的点权和 $s$，再输出最终答案 $s * 2 - a_u - a_v$ 即可。

至于答案为什么是这个……因为在最短路上的每个点（除了起点和终点）的点权要被算两遍（因为两侧共有两条边），而起点和终点就只用被算一次。

## 代码

```cpp
#include <iostream>
#define int long long
#define abs(x) ((x) > 0 ? (x) : -(x))
using namespace std;
const int N = 1048576; // ???
int head[200005], nxt[200005], to[200005], cnt; // 链式前向星
void add(int u, int v) { to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt; }
int dfn[100005], sz[100005], son[100005], dep[100005], top[100005], f[100005];
int w[N * 4], wt[N * 4], ncnt;
// ----------------- 以下树剖板子 --------------------
void dfs1(int x, int fa, int d) {
    dep[x] = d;
    f[x] = fa;
    sz[x] = 1;
    for (int i = head[x]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            dfs1(v, x, d + 1);
            sz[x] += sz[v];
            if (sz[v] > sz[son[x]]) 
                son[x] = v;
        }
    }
}
void dfs2(int x, int t) {
    dfn[x] = ++ncnt;
    wt[ncnt] = w[x];
    top[x] = t;
    if (!son[x]) 
        return;
    dfs2(son[x], t);
    for (int i = head[x]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (v != son[x] && v != f[x]) 
            dfs2(v, v);
    }
}
// ----------------- 以上树剖板子 --------------------
// ---------------- 以下线段树板子 -------------------
int sm[N * 4];
void Build(int o, int l, int r) {
    if (l == r) {
        sm[o] = wt[l];
        return;
    }
    int mid = l + r >> 1;
    Build(o << 1, l, mid);
    Build(o << 1 | 1, mid + 1, r);
    sm[o] = sm[o << 1] + sm[o << 1 | 1];
}
void Add(int o, int l, int r, int x, int y) {
    if (l == r) {
        sm[o] = y;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) 
        Add(o << 1, l, mid, x, y);
    else 
        Add(o << 1 | 1, mid + 1, r, x, y);
    sm[o] = sm[o << 1] + sm[o << 1 | 1];
}
int Query(int o, int l, int r, int L, int R) {
    if (L <= l && r <= R) 
        return sm[o];
    int mid = l + r >> 1, ret = 0;
    if (L <= mid) 
        ret += Query(o << 1, l, mid, L, R);
    if (R > mid) 
        ret += Query(o << 1 | 1, mid + 1, r, L, R);
    return ret;
}
// ---------------- 以上线段树板子 -------------------
// --------------- 以下继续树剖板子 ------------------
void change(int u, int v) { Add(1, 1, N, dfn[u], v); }
int Query_sum(int u, int v) {
    int ret = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) 
            swap(u, v);
        ret += Query(1, 1, N, dfn[top[u]], dfn[u]);
        u = f[top[u]];
    }
    if (dep[u] > dep[v]) 
        swap(u, v);
    ret += Query(1, 1, N, dfn[u], dfn[v]);
    return ret;
}
// --------------- 以上继续树剖板子 ------------------
signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> w[i], w[i] = abs(w[i]); // 取绝对值
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    Build(1, 1, N);
    while (q--) {
        int op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 1) 
            change(x, abs(y)); // 修改的时候把将要改成的数也取一个绝对值
        else  
            cout << Query_sum(x, y) * 2 // 这甚至是可以编译通过的（
                - Query(1, 1, N, dfn[x], dfn[x]) 
                - Query(1, 1, N, dfn[y], dfn[y]) 
                << "\n";
    }
    return 0;
}
```
## 完结撒花~~
（又轻松水过了一道蓝题捏）

---

## 作者：gesong (赞：0)

题目传送门：[Illusions of the Desert](https://www.luogu.com.cn/problem/CF1575I)。
# 前置知识
1. **[树链剖分](https://oi-wiki.org/graph/hld/)**。 
2. **[线段树](https://oi-wiki.org/ds/seg/)**。

# 思路
首先我们需要知道一个重要的公式：$\max(|a_u+a_v|,|a_u-a_v|)=|a_u|+|a_v|$。

然后我们发现就是求区间和的操作，于是就想到了**树链剖分+线段树**来求解。

由于树链剖分就是模板，但是线段树不一样，所以我们就直接讲线段树。



**维护信息**：

由于这道题只需要路径求和，所以这里只需要一个 sum  记录区间和即可。

**pushup 函数**：

很简单，由于区间和就是左右子区间的区间和的和。

```cpp
inline void pushup(int k){
	t[k].sum=t[lc].sum+t[rc].sum;
}
```
**pushdown 函数**：

没有这一个函数，因为 change 函数是单点修改，因此修改的区间就是线段树的**叶子结点**，不会影响祖宗的值，因此也没有懒标记。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
const int N=1e5+10,M=N*2;
int h[N],e[M],nx[M],w[N];
int dfn[N],nw[N],top[N],d[N],son[N],sz[N],fa[N],idx;
inline void add(int u,int v){
	e[idx]=v,nx[idx]=h[u],h[u]=idx++;
	e[idx]=u,nx[idx]=h[v],h[v]=idx++;
}
void dfs1(int u,int f){
	fa[u]=f,sz[u]=1;
	for (int i=h[u];~i;i=nx[i]){
		int v=e[i];
		if (v==f) continue;
		d[v]=d[u]+1;
		dfs1(v,u);
		sz[u]+=sz[v];
		if (sz[son[u]]<sz[v]) son[u]=v;
	}
}
int cnt;
void dfs2(int u,int t){
	dfn[u]=++cnt,nw[cnt]=w[u],top[u]=t;
	if (!son[u]) return ;
	dfs2(son[u],t);
	for (int i=h[u];~i;i=nx[i]){
		int v=e[i];
		if (v==son[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}
//树链剖分
struct nord{
	int l,r,sum;
}t[N<<2];
#define lc k<<1
#define rc k<<1|1
inline void pushup(int k){
	t[k].sum=t[lc].sum+t[rc].sum;
}
void build(int k,int l,int r){
	t[k].l=l,t[k].r=r;
	if (l==r){
		t[k].sum=nw[l];
		return ;
	}
	int mid=l+r>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(k);
}
void change(int k,int x,int p){
	if (t[k].l==t[k].r){
		t[k].sum=p;
		return ;
	}
	int mid=t[k].l+t[k].r>>1;
	if (x<=mid) change(lc,x,p);
	else change(rc,x,p);
	pushup(k);
}
int ask(int k,int l,int r){
	if (l<=t[k].l&&r>=t[k].r) return t[k].sum;
	int mid=t[k].l+t[k].r>>1,ans=0;
	if (l<=mid) ans+=ask(lc,l,r);
	if (r>mid) ans+=ask(rc,l,r);
	return ans;
}
//线段树
inline int op1(int u,int v){//求路径和
	int ans=0;
	while(top[u]!=top[v]){
		if (d[top[u]]<d[top[v]]) swap(u,v);
		ans+=ask(1,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if (d[u]<d[v]) swap(u,v);
	ans+=ask(1,dfn[v],dfn[u]);
	return ans;
}
main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) h[i]=-1,cin>>w[i],w[i]=abs(w[i]);//一定要 abs
	for (int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);//建树
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	while(m--){
		int op,u,v;
		cin>>op>>u>>v;
		if (op==1){
			v=abs(v);//一定要 abs
			change(1,dfn[u],v);
			w[u]=v;
		}
		else cout <<op1(u,v)*2-w[u]-w[v]<<endl;
	}
    return 0;
}
```


---

