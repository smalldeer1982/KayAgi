# [集训队互测 2024] Classical Counting Problem

## 题目描述

给定一棵 $n$ 个节点的无根树，你可以做如下操作若干次：

- 选择当前树上编号最大或最小的点，删去它和以它为一个端点的所有边，保留任意一个连通块作为操作后的树。

令 $\min$ 为树上所有节点编号的最小值，$\max$ 为树上所有节点编号的最大值，$size$ 为树上的节点个数，则一棵树的权值为 $\min \cdot \max \cdot size$。求所有能通过上述操作得到的非空的树的权值和，对 $2^{32}$ 取模。

## 说明/提示

### 子任务

| 子任务编号 | 特殊性质 | 分值 |
| :---: | :---: | :---: |
| 1 | $n \leq 10$ | 5 |
| 2 | $n \leq 20$ | 10 |
| 3 | $n \leq 100$ | 10 |
| 4 | $n \leq 2000$ | 15 |
| 5 | $n \leq 3 \times 10^4$ | 15 |
| 6 | 给定的树中，每个节点的度数 $\leq 2$ | 20 |
| 7 | 无 | 25 |


## 样例 #1

### 输入

```
6
3
1 2
2 3
3
1 3
2 3
7
2 1
3 1
4 1
5 1
6 5
7 6
6
2 1
3 1
4 1
5 4
6 1
9
2 1
3 2
4 3
5 1
6 4
7 5
8 2
9 3
9
2 1
3 2
4 3
5 4
6 5
7 2
8 3
9 5```

### 输出

```
39
35
528
221
1145
1919```

# 题解

## 作者：_Ad_Astra_ (赞：3)

比较考验基本功的题，需要一步步慢慢转化。

---

首先考虑刻画合法连通块具有哪些性质。注意到合法性只跟块内的最小值 $mn$ 和最大值 $mx$ 有关。由于删除过程不好直接考虑，所以转化为倒着加点。

显然，每次加入的点必须不在 $[mn,mx]$ 范围内。也就是说我们得到了必要条件：与连通块相邻的点必须 $\lt mn$ 或 $\gt mx$。我们发现这个条件也是充分的。具体地，在满足条件的情况下，与当前的连通块相邻的任何一个点 $v$ 都能被加入（不妨设 $v \lt mn$），这时候值域更新为 $[v,mx]$。同时我们以 $v$ 为中心往外扩展，把包含 $v$ 的值域在 $[v,mx]$ 的整个连通块都加入，我们发现这样操作后构成的新连通块仍然满足条件，因此可以一直这样扩展下去，直到成为原树。

![](https://cdn.luogu.com.cn/upload/image_hosting/89f081c5.png)

例如上图 $4-2-5$ 就是一个合法连通块，依次加入 $1$、$3-6$、$7$ 可以扩展成原树，对应的删除操作就是依次删除 $7$、$6$ 和 $1$。

---

  回到原问题。由于我们刚才刻画的条件唯一的限制与 $mn$ 和 $mx$ 有关，因此我们先考虑固定这两个值计算贡献。显然这两个点 $mn \leftrightarrow mx$ 路径上的所有点必须被包含。如果之间有不在 $[mn,mx]$ 的点则肯定不合法。否则的话考虑我们刚才得出的条件，我们发现可以类似地进行扩展，把所有相邻的值域内的点扩展入连通块，直到形成一个极大连通块为止。也就是说，$[mn,mx]$ 能确定的最后的连通块形态是唯一的。

这时候容易实现 $O(n^3)$ 暴力。同时不难想到优化，固定 $mn$ 并从小到大枚举 $mx$，用并查集等维护连通块即可做到约 $O(n^2)$。

---

考虑优化。直接枚举 $mn$ 或 $mx$ 任何一个都难以直接计算。联想到 $mn$ 到 $mx$ 的路径必选这一条件，可以想到使用点分治来处理路径信息。

但是答案乘上 $size$ 还是难以维护。联想到经典套路：可以把 $size$ 拆开，多加入一维 $v$，三元组 $(mn,mx,v)$ 表示 $v$ 能够在 $mn$ 和 $mx$ 确定的连通块内，即求所有三元组 $mn \times mx$ 的和。

现在的条件要好刻画多了。发现 $v$ 只需要满足到 $mn \leftrightarrow mx$ 路径上经过的所有点都在 $[mn,mx]$ 之间，就一定能被扩展到。

回到点分治过程。我们现在确定了一个分治中心 $rt$ 作为 $mn$、$mx$ 和 $v$ 的 $\text{lca}$，重新描述一下我们的限制：首先 $mn \leftrightarrow mx$ 路径上的点都要在 $[mn,mx]$ 之间，其次 $v$ 到这条路径经过的点也要在 $[mn,mx]$ 之间。注意到这两段能被 $mn \to rt$、$mx \to rt$ 与 $v \to rt$ 三段恰好覆盖。所以只需要转而考虑这三段即可。

所有限制现在都跟每个点到 $rt$ 路径上的点有关了。更进一步地，对于每个点 $u$ 计算 $l_u$ 和 $r_u$ 表示 $u \to rt$ 路径上的点的最小值和最大值。我们的限制可以被重新表述为：

$$
\begin{cases}
r_{mn} \le mx \\

l_{mx} \ge mn \\

mn \le l_v \le r_v \le mx\\
\end{cases}
$$

---

现在问题简化为：给定若干 $(u,l_u,r_u)$ 三元组，求满足上述不等式的 $(mn,mx,v)$ 的 $mn \times mx$ 之和。考虑枚举 $mx$，即按照所有点的 $r_x$ 排序后扫描线。

开一颗线段树，维护 $mn$ 在每个区间内时的答案 $s$。同时每个区间还要维护区间内已经被加入（即 $r_{mn} \le mx$）的 $mn$ 的和 $val$，以及区间内每个 $mn$ 对应的恰好满足 $l_v=mn$ 的 $v$ 的数量 $c$，作为辅助。

每次加入一个点，有三种情况：

+ $u$ 作为 $v$。这时候 $u$ 应在扫描线到 $r_u$ 处被加入。加入时产生贡献为让 $\le l_u$ 的 $mn$ 答案加上已经被加进来的 $mn$ 的和，即对于 $[1,l_u]$ 执行 $s \leftarrow s+val$，同时 $l_u$ 处合法 $v$ 数量增加，即在 $l_u$ 处执行 $c \leftarrow c+1$。

+ $u$ 作为 $mn$。需满足 $l_u=u$。这时候 $u$ 应在扫描线到 $r_u$ 处被加入。加入时这个点第一次合法，因此对于 $u$ 点处执行 $val \leftarrow u$。同时 $u$ 作为 $mn$ 能对答案产生的贡献也要计算，与它能产生的贡献的 $v$ 有 $\sum\limits_{i=u}^nc_i$ 个（可以线段树区间查询求出，记作 $C$），故在 $u$ 点处执行 $s \leftarrow C \times u$。

+ $u$ 作为 $mx$。需满足 $r_u=u$。这时候 $u$ 应在扫描线恰好到 $u$ 处时进行查询。即求 $[l_u,u]$ 区间内所有 $s$ 的和，乘上 $u$ 并加入答案。

总结一下，我们要用线段树维护三个数组 $s$、$val$ 与 $c$，支持单点修改、区间 $s \leftarrow s+val$ 与区间求和三种操作。

这样已经基本解决了。注意当 $v$ 跟 $mn$ 和 $mx$ 均在同一子树内时贡献会算重，对每棵子树再跑一遍扫描线算出贡献减掉即可。

---

每层分治总共需要对 $O(n)$ 个点跑扫描线，每一层的复杂度为 $O(n \log n)$。总的时间复杂度为 $O(n \log^2 n)$，可以通过。

代码虽然稍长但并不难写，细节与边界情况也不是很多。

以下是本人实现，代码较丑，人傻常数大，仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int,int>
#define fir first
#define sec second
#define chmin(a,b) a=min(a,b)
#define chmax(a,b) a=max(a,b)
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
constexpr int mod=(1LL<<32)-1;

int ans;

int n,sz[100010],vis[100010],mx[100010],l[100010],r[100010],msz;
vector<int>g[100010];
vector<int>tmp;
void dfs1(int u,int f){sz[u]=1;for(auto v:g[u])if(v!=f&&!vis[v])dfs1(v,u),sz[u]+=sz[v];}
void dfs2(int u,int f,int &rt){mx[u]=msz-sz[u];for(auto v:g[u]){if(v!=f&&!vis[v])dfs2(v,u,rt),chmax(mx[u],sz[v]);}if(mx[u]<=mx[rt])rt=u;}
 
void dfs3(int u,int f)
{
	l[u]=min(l[f],u),r[u]=max(r[f],u),tmp.pb(u);
	for(auto v:g[u])if(!vis[v]&&v!=f)dfs3(v,u);
}

/*
--------------------- 
*/

struct tnode
{
	int l,r,s,v,c,tag;
	tnode(){}
	tnode(int _l,int _r,int _s,int _v,int _c,int _tag)
	{l=_l,r=_r,s=_s,v=_v,c=_c,tag=_tag;}
	//s: 区间内所有 mn 对答案的贡献
	//v: 区间内所有合法的 mn 的和
	//c: 区间内合法 v 的数量 
}t[400010];
#define ls rt<<1
#define rs rt<<1|1
void pushup(int rt)
{
	t[rt].s=(t[ls].s+t[rs].s)&mod;
	t[rt].v=(t[ls].v+t[rs].v)&mod;
	t[rt].c=(t[ls].c+t[rs].c)&mod;
}
void change(int rt,int tag){(t[rt].s+=t[rt].v*tag)&=mod,(t[rt].tag+=tag)&=mod;}
void pushdown(int rt){if(t[rt].tag)change(ls,t[rt].tag),change(rs,t[rt].tag),t[rt].tag=0;}
void build(int rt,int l,int r)
{
	t[rt]={l,r,0,0,0,0};
	if(l==r)return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void update(int rt,int x,int v,int op)
{
	if(t[rt].l==t[rt].r)
	{
		if(op==0)(t[rt].s+=v)&=mod;
		else if(op==1)(t[rt].v+=v)&=mod;
		else (t[rt].c+=v)&=mod;
		return;
	}
	pushdown(rt);
	if(x<=t[ls].r)update(ls,x,v,op);
	else update(rs,x,v,op);
	pushup(rt);
}
void add(int rt,int l,int r,int v)
{
	if(l<=t[rt].l&&r>=t[rt].r){change(rt,v);return;}
	pushdown(rt);
	if(l<=t[ls].r)add(ls,l,r,v);
	if(r>=t[rs].l)add(rs,l,r,v);
	pushup(rt);
}
int query(int rt,int l,int r,int op)
{
	if(l<=t[rt].l&&r>=t[rt].r)return op?(op==1?t[rt].v:t[rt].c):t[rt].s;
	pushdown(rt);
	int ans=0;
	if(l<=t[ls].r)ans+=query(ls,l,r,op);
	if(r>=t[rs].l)ans+=query(rs,l,r,op);
	return ans&mod;
}

/*
--------------------- 
*/

int m,b[300010];
vector<int>q[300010];
int calc()
{
	int ans=0;
	m=0;
	for(auto u:tmp)b[++m]=u,b[++m]=l[u],b[++m]=r[u];
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	build(1,1,m);
	for(int i=1;i<=m;i++)q[i].clear();
	for(auto u:tmp)
	{
		int p=lower_bound(b+1,b+m+1,u)-b;
		q[p].pb(u);
		int rp=lower_bound(b+1,b+m+1,r[u])-b;
		q[rp].pb(-u);
	}
	for(int i=1;i<=m;i++)
	{
		sort(q[i].begin(),q[i].end());
		for(auto u:q[i])
		{
			
			if(u<0)
			{
				u=-u;
				int p=lower_bound(b+1,b+m+1,u)-b;
				int lp=lower_bound(b+1,b+m+1,l[u])-b;
				
				//u 为 v 
				add(1,1,lp,1);
				update(1,lp,1,2);
				
				//u 为 mn 
				if(u==l[u])
				{
					int q=query(1,p,p,1);
					update(1,p,u,1);
					int t=query(1,p,m,2);
					update(1,p,(u*t)&mod,0);
				}
			}
			else if(u==r[u])
			{
				//u 为 mx 
				int p=lower_bound(b+1,b+m+1,u)-b;
				int lp=lower_bound(b+1,b+m+1,l[u])-b;
				(ans+=query(1,1,lp,0)*u)&=mod;
			}
		}
	}
	return ans;
}

void dfs(int u)
{
	dfs1(u,0);
	msz=sz[u],mx[0]=inf;
	int rt=0;
	dfs2(u,0,rt);
	
	l[rt]=r[rt]=rt;
	vector<int>tr; 
	tr.pb(rt);
	int pans=0;
	for(auto v:g[rt])if(!vis[v])
	{
		tmp.clear();
		if(!vis[v])dfs3(v,rt);
		int q=calc();
		(pans+=mod+1-q)&=mod;
		for(auto x:tmp)tr.pb(x);
	}
	tmp=tr;
	int q=calc();
	pans+=q;
	(ans+=pans)&=mod;
	
	vis[rt]=1;
	for(auto v:g[rt])if(!vis[v])dfs(v);
}
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)g[i].clear(),vis[i]=0;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].pb(v);
		g[v].pb(u);
	}
	ans=0;
	dfs(1);
	cout<<ans<<endl;
	return;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
} 
```

---

## 作者：yishanyi (赞：1)

##  [[Luogu P12480]](https://luogu.com.cn/problem/P12480)/[[QOJ9533]](https://qoj.ac/problem/9533) Classical Counting Problem

### pro.

$n$ 个点的无根树，每次可以做以下操作若干次：

- 选择当前树上编号最大或最小的点 $u$，删去 $u$ 及其连边，保留任意一个连通块作为操作后的树。

令 $min$ 为树上所有节点编号的最小值，$max$ 为树上所有节点编号的最大值，$size$ 为树上的节点个数，则一棵树的权值为 $min\cdot max\cdot size$。

求所有能通过操作得到的非空树的权值和。

$n\le1e5$。$\mathrm{3s,1024MB}$。

### sol.

读完题后发现没有明显的多项式做法，考虑寻找性质。

~~不很~~容易发现：一对合法的 $(min,max)$ 可以确定唯一的一棵树。

证明：一对点 $(u,v)$ 能作为一棵合法树的 $(min,max)$ 当且仅当 $u$ 到 $v$ 的路径上的所有点都在 $[u,v]$ 区间内，然后在这条路径上不断加入在 $[u,v]$ 区间内且与当前联通块联通的点，即可得到 $(u,v)$ 对应的树 $T$，显然树 $T$ 的形态与加点顺序无关，故每个合法 $(u,v)$ 对应唯一的一棵树。而对于一棵树 $T$ ，设其最小值和最大值分别为 $(u,v)$，由于只对最大值或最小值操作，故再进行操作显然不对应 $(u,v)$ 。故合法 $(min,max)$ 与合法的树一一对应。

于是可以枚举 $min,max$ ，然后加入 $[min,max]$ 区间内的点，判断是否联通并统计答案。暴力实现 $\mathcal{O}(n^3)$ ，固定 $min$ 或 $max$ 再依次加入点，用并查集维护连通性，即可实现 $\mathcal{O}(n^2)$ 。

考虑优化。注意到一对合法 $(min, max)$ 的判断用到了路径信息，于是想到点分治。对于一个分治中心，记录每个点到其路径上的最大值 $max_u$ 和最小值 $min_u$，则对于 $u=min_u\land v=max_v\land min_v\ge u\land max_u\le v$ 的 $(u,v)$ 即为合法对。如果没有 $size$ 可以二维数点维护，难点在于怎么处理 $size$ 这一项。

**Trick**：对于难处理的有限制联通块大小，可以考虑拆贡献，即维护有多少个 $x$ 能满足这样的限制。

于是可以转化为在每个分治中心下统计有多少个 $(l,r,x)$ 可以在同一个联通块里，对答案的贡献即为 $l\cdot r$。

显然合法 $l,r$ 的限制依然成立，而 $x$ 需要满足的限制应该为 $min_x\ge l\land max_x\le r$。

即一对合法 $(l,r,x)$ 应满足：

$$
\begin{cases}
min_l=l
\\
max_r=r
\\
min_l\le min_x
\\
min_l\le min_r
\\
max_x\le max_r
\\
max_l\le max_r
\end{cases}
$$

观察到关键限制都是 $min$ 或 $max$ 之间的偏序关系，于是不妨设每个点的坐标为 $(min_x,max_x)$ ，发现合法三元组在二维平面上应满足：![](https://cdn.luogu.com.cn/upload/image_hosting/xd8xhfv7.png)

考虑对 $max$ 一维扫描线，线段树维护另一维。

于是当扫到某个 $r$ 时，能与 $r$ 匹配的 $(l,x)$ 一定已经加入了线段树。

而对于某个 $r$ ，能与它产生贡献的 $l$ 一定在 $min_r$ 左侧。设 $l$ 能与 $cnt_l$ 个 $x$ 匹配，则答案为 $l\cdot cnt_l\cdot r$ 。

所以线段树需要维护区间 $\sum l\cdot cnt_l$ 。

我们设一段区间内可以作为 $l$ 的点的编号和为标准和 $std$，要求的 $\sum l\cdot cnt_l$ 为结果和 $sum$ 。

则插入一个 $l$ 时，$min_l=l$ 处的标准和要增加 $l$ ，能与该点匹配的 $cnt$ 不变，结果和要增加 $l\cdot cnt_l$；插入一个 $x$ 时，对于 $min_x$ 左侧的区间，标准和不变，能与区间中每处匹配的 $cnt$ 增加 $1$，结果和要增加一个区间对应的标准和。

于是我们线段树中维护 $std,cnt,sum,add$，分别为区间标准和，能与这段区间匹配的 $x$ 数量，区间结果和，（懒标记）区间加了多少次标准和，支持 $std$ 的单点加，$cnt$ 的区间加，$sum$ 的区间修改（$cnt$ 及所谓区间加的定义其实并不严格，因为一段区间每个位置能匹配的 $x$ 的数量不尽相同，但由于 $cnt$ 只在单点修改 $l$ 时由于需要补上之前加入的 $x$ 的贡献才使用，而一个单点能匹配的 $x$ 的数量是一定的，即 $cnt$ 只需要下传，所以 $cnt$ 才可以简单当作区间加处理~~定义是不知道该怎么描述~~）。

复杂度分析可以考虑点分治最坏情况下的形式就是一条链，形态类似线段树，相当于对线段树上每个点开一棵线段树，即树套树，故复杂度 $\mathcal{O}(n\log^2n)$ 。

一些实现细节：

- 由于 $(l,r,x)$ 可以任意相等，所以可以作为 $l,r$ 的也可以作为 $x$ 。因此在同一高度的点的操作顺序应该是先插入 $l$ ，再插入 $x$ ，最后查询 $r$ 。

- 子树去重时不能更新 $min$ 和 $max$ ，仍然要保留原分治中心下的 $min$ 和 $max$ 数值，否则起到的不是去重效果。

- 对于每个分治中心需要离散化，不能直接扫描线 $[1,~n]$ ，否则复杂度会退化至 $\mathcal{O}(n^2\log^2n)$ 。

### cod.

```cpp
#include <bits/stdc++.h>

#define file(name, suf) ""#name"."#suf""
#define input(name) freopen(file(name, in), "r", stdin)
#define output(name) freopen(file(name, out), "w", stdout)
#define map(type, x) static_cast<type>(x)

typedef unsigned int uint;

constexpr int N = 1e5 + 10;
int n, siz[N], son_siz[N], id[N], min[N], max[N];
std::vector<int> e[N], node;
bool arr[N];
uint ans;
struct Seg_Tree {
    struct Node { uint sum, std, cnt, add, clr; } t[N << 2];

#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)

    void up(int u) {
        t[u].sum = t[ls].sum + t[rs].sum;
        t[u].std = t[ls].std + t[rs].std;
    }

    void build(int u, int l, int r) {
        t[u] = {0, 0, 0, 0, false};
        if (l == r) return;
        build(ls, l, mid), build(rs, mid + 1, r);
    }

    void add(int u, uint x) { t[u].sum += t[u].std * x, t[u].cnt += x, t[u].add += x; }

    void down(int u) {
        if (t[u].add) add(ls, t[u].add), add(rs, t[u].add), t[u].add = 0;
    }

    void insert(int u, int l, int r, int k, uint x) {
        if (l == r) return t[u].std += x, t[u].sum += t[u].cnt * x, void();
        down(u);
        if (k <= mid) insert(ls, l, mid, k, x);
        else insert(rs, mid + 1, r, k, x);
        up(u);
    }

    void add(int u, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) return add(u, 1);
        down(u), add(ls, l, mid, ql, qr), add(rs, mid + 1, r, ql, qr), up(u);
    }

    uint query(int u, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return t[u].sum;
        down(u);
        return query(ls, l, mid, ql, qr) + query(rs, mid + 1, r, ql, qr);
    }
} T;

int get_core(int u, int f, int all) {
    int core = son_siz[u] = (siz[u] = 1) - 1;
    for (const int& v : e[u])
        if (v != f && !arr[v]) {
            int res = get_core(v, u, all);
            siz[u] += siz[v], son_siz[u] = std::max(son_siz[u], siz[v]);
            core = !core || son_siz[res] < son_siz[core] ? res : core;
        }
    son_siz[u] = std::max(son_siz[u], all - siz[u]);
    return !core || son_siz[u] < son_siz[core] ? u : core;
}

void dfs(int u, int f) {
    node.push_back(u), siz[u] = 1, min[u] = std::min(min[f], u), max[u] = std::max(max[f], u);
    for (const int& v : e[u]) if (v != f && !arr[v]) dfs(v, u), siz[u] += siz[v];
}

void reput(int u, int f) {
    node.push_back(u);
    for (const int& v : e[u]) if (v != f && !arr[v]) dfs(v, u);
}

void erase(int u) {
    reput(u, 0), std::sort(node.begin(), node.end());
    int all = node.size();
    T.build(1, 1, all);
    for (const int& x : node) id[x] = std::lower_bound(node.begin(), node.end(), x) - node.begin() + 1;
    std::sort(node.begin(), node.end(), [](const int& a, const int& b) { return max[a] < max[b];});
    for (int i = 0, j; i < node.size(); i = j) {
        for (j = i; j < node.size() && max[node[j]] == max[node[i]]; j++) if (min[node[j]] == node[j]) T.insert(1, 1, all, id[node[j]], node[j]);
        for (j = i; j < node.size() && max[node[j]] == max[node[i]]; j++) T.add(1, 1, all, 1, id[min[node[j]]]);
        for (j = i; j < node.size() && max[node[j]] == max[node[i]]; j++) if (max[node[j]] == node[j]) ans -= T.query(1, 1, all, 1, id[min[node[j]]]) * node[j];
    }
}

void sol(int u) {
    arr[u] = true, dfs(u, 0);
    std::sort(node.begin(), node.end());
    int all = node.size();
    T.build(1, 1, all);
    for (const int& x : node) id[x] = std::lower_bound(node.begin(), node.end(), x) - node.begin() + 1;
    std::sort(node.begin(), node.end(), [](const int& a, const int& b) { return max[a] < max[b];});
    for (int i = 0, j; i < node.size(); i = j) {
        for (j = i; j < node.size() && max[node[j]] == max[node[i]]; j++) if (min[node[j]] == node[j]) T.insert(1, 1, all, id[node[j]], node[j]);
        for (j = i; j < node.size() && max[node[j]] == max[node[i]]; j++) T.add(1, 1, all, 1, id[min[node[j]]]);
        for (j = i; j < node.size() && max[node[j]] == max[node[i]]; j++) if (max[node[j]] == node[j]) ans += T.query(1, 1, all, 1, id[min[node[j]]]) * node[j];
    }
    for (const int& v : e[u]) if (!arr[v]) node.clear(), erase(v);
    node.clear();
    for (const int& v : e[u]) if (!arr[v]) sol(get_core(v, 0, siz[v]));
}

void solve() {
    std::cin >> n, max[0] = 0, min[0] = INT_MAX, ans = 0;
    for (int i = 1; i <= n; i++) e[i].clear(), arr[i] = false;
    for (int i = 1, u, v; i < n; i++) std::cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
    sol(get_core(1, 0, n));
    std::cout << ans << "\n";
}

int main() {
    // input(main), output(main);
    int _ = 1;
    std::cin >> _;
    while (_--) solve();
    return 0;
}
```

---

