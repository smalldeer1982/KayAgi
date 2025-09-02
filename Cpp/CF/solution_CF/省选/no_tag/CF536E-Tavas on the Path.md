# Tavas on the Path

## 题目描述

Tavas lives in Tavaspolis. Tavaspolis has $ n $ cities numbered from $ 1 $ to $ n $ connected by $ n-1 $ bidirectional roads. There exists a path between any two cities. Also each road has a length.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF536E/d3484f8e760e70be37b15d454f75fce51db0bf40.png)Tavas' favorite strings are binary strings (they contain only 0 and 1). For any binary string like $ s=s_{1}s_{2}...\ s_{k} $ , $ T(s) $ is its $ Goodness $ . $ T(s) $ can be calculated as follows:

Consider there are exactly $ m $ blocks of $ 1 $ s in this string (a block of $ 1 $ s in $ s $ is a maximal consecutive substring of $ s $ that only contains $ 1 $ ) with lengths $ x_{1},x_{2},...,x_{m} $ .

Define ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF536E/355506c834e033a7323a71320e8c5f755ccad647.png) where $ f $ is a given sequence (if $ m=0 $ , then $ T(s)=0 $ ).

Tavas loves queries. He asks you to answer $ q $ queries. In each query he gives you numbers $ v,u,l $ and you should print following number:

Consider the roads on the path from city $ v $ to city $ u $ : $ e_{1},e_{2},...,e_{x} $ .

Build the binary string $ b $ of length $ x $ such that: $ b_{i}=1 $ if and only if $ l<=w(e_{i}) $ where $ w(e) $ is the length of road $ e $ .

You should print $ T(b) $ for this query.

## 样例 #1

### 输入

```
2 3
10
1 2 3
1 2 2
1 2 3
1 2 4
```

### 输出

```
10
10
0
```

## 样例 #2

### 输入

```
6 6
-5 0 0 2 10
1 2 1
2 3 2
3 4 5
4 5 1
5 6 5
1 6 1
1 6 2
1 6 5
3 6 5
4 6 4
1 4 2
```

### 输出

```
10
-5
-10
-10
-5
0
```

# 题解

## 作者：Eibon (赞：4)

模拟赛的题，赛时想到一种奇妙（~~baoli~~）的想法。

借鉴倍增的思想，考虑倍增维护每个点向上的最大值与最小值。

查询的时候，每个点连续向上跳一段最小值小于等于 $l$ 的段,并把这一段的贡献加上，然后跳过一段最大值小于 $l$ 的一段，直至跳到 lca。

在随机的数据下跑的飞快，然后在 CF 被卡成 $O(n^{2}\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int T=1,n,m,tot,lst,sum,op1,op2;
int a[maxn],head[maxn],fa[maxn][22],mn[maxn][22],dep[maxn],pre[maxn],mx[maxn][22];
struct edge
{
	int to,nxt,w;
};
edge e[maxn<<1];
void add(int u,int v,int w)
{
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
void dfs(int u,int pa,int W)
{
	mn[u][0]=W;
	mx[u][0]=W;
	fa[u][0]=pa;
	dep[u]=dep[pa]+1;
	for(int i=1;i<=20;i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		mn[u][i]=min(mn[u][i-1],mn[fa[u][i-1]][i-1]);
		mx[u][i]=max(mx[u][i-1],mx[fa[u][i-1]][i-1]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==pa){
			continue;
		}
		int w=e[i].w;
		dfs(v,u,w);
	}
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	int d=dep[u]-dep[v];
	for(int i=0;i<=20;i++){
		if(d&1){
			u=fa[u][i];
		}
		d>>=1;
	}
	if(u==v){
		return u;
	}
	for(int i=20;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}
void jump(int u,int l,int W,int op)
{
	int len=0;
	for(int i=20;i>=0;i--){
		if(mn[u][i]>=W&&dep[fa[u][i]]>dep[l]){
			len+=pre[i];
			u=fa[u][i];
		}
	}
	if(fa[u][0]==l){
		if(mn[u][0]>=W){
			len++;
			if(op==1){
				op1=1;
			}
			else{
				op2=1;
			}
		}
		lst=len;
	}
	else{
		sum+=a[len];
		for(int i=20;i>=0;i--){
			if(mx[u][i]<W&&dep[fa[u][i]]>dep[l]){
				u=fa[u][i];//cout<<u<<endl;
			}
		}
		jump(u,l,W,op);
	}
}
void solve()
{
	scanf("%lld%lld",&n,&m);
	pre[0]=1;
	for(int i=1;i<=20;i++){
		pre[i]=pre[i-1]*2;
	}
	for(int i=1;i<n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0,0);
//	cout<<mn[6][0]<<" "<<mn[6][2]<<endl;
	while(m--){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		int l=LCA(u,v);
		lst=sum=op1=op2=0;
		if(u!=l)jump(u,l,w,1);
		int num1=lst;
		int ans=sum;
		lst=sum=0;
		if(v!=l)jump(v,l,w,2);
		int num2=lst;//cout<<lst<<endl;
		ans+=sum;
//		cout<<sum<<endl;
		if(op1&&op2){
			ans+=a[num1+num2];
		}
		else{
			ans+=a[num1]+a[num2];
		}
		printf("%lld\n",ans);
	}
}
signed main()
{
//	freopen("Tavas_on_the_Path.in","r",stdin);
//	freopen("Tavas_on_the_Path.out","w",stdout);
//	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
/*
6 1
-5 0 0 2 10
1 2 1
2 3 2
3 4 5
4 5 1
5 6 5
1 6 2
*/
```
考虑正解，将所有询问离线下来按照 $l$ 从大到小排序。

同时将边权保存并离线下来，也按照 $l$ 从大到小排序。

然后类似于单指针移动，$O(n)$ 将边权大于等于 $l$ 的节点所对应线段树内叶子结点进行更改。

查询时不同于正常的树剖，从 $u$ 向上与从 $v$ 向上的节点拼接的链顺序是相反的，需要特殊处理。

线段树维护 $sum$，$lx$，$rx$ 和 $len$，分别表示答案，从左端开始的最长全 $1$ 序列，从右端开始的最长全 $1$ 序列，线段树用于维护全 $1$ 序列。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int T=1,n,m,tot,cnt;
int head[maxn],a[maxn],sz[maxn],dep[maxn],fa[maxn];
int dfn[maxn],rk[maxn],son[maxn],tp[maxn],output[maxn];
struct Edge
{
	int u,v,w;
	bool operator < (const Edge &x) const
	{
		return w>x.w;
	}
};
Edge E[maxn];
struct node
{
	int u,v,w,id;
	bool operator < (const node &x) const
	{
		return w>x.w;
	}
};
node q[maxn];
struct edge
{
	int to,nxt,w;
};
edge e[maxn<<1];
void add(int u,int v,int w)
{
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
void dfs1(int u,int pa)
{
	sz[u]=1;
	fa[u]=pa;
	dep[u]=dep[pa]+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==pa){
			continue;
		}
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[son[u]]<sz[v]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int top_fa)
{
	dfn[u]=++cnt;
	rk[cnt]=u;
	tp[u]=top_fa;
	if(son[u]){
		dfs2(son[u],top_fa);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u]){
			continue;
		}
		dfs2(v,v);
	}
}
struct Tree
{
	int sum,lx,rx,len;
};
Tree tree[maxn<<2];
void pushup(Tree &res,Tree res1,Tree res2)
{
	res.len=res1.len+res2.len;
	res.lx=res1.lx+(res1.lx==res1.len?res2.lx:0);
	res.rx=res2.rx+(res2.rx==res2.len?res1.rx:0);
	res.sum=res1.sum+res2.sum-a[res1.rx]-a[res2.lx]+a[res1.rx+res2.lx];
}
void build(int root,int l,int r)
{
	if(l==r){
		tree[root]={0,0,0,1};
		return;
	}
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	pushup(tree[root],tree[root<<1],tree[root<<1|1]);
}
void update(int root,int l,int r,int x)
{
	if(l==r){
		tree[root]={a[1],1,1,1};
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		update(root<<1,l,mid,x);
	}
	else{
		update(root<<1|1,mid+1,r,x);
	}
	pushup(tree[root],tree[root<<1],tree[root<<1|1]);
}
Tree query(int root,int l,int r,int L,int R)
{
	if(L<=l&&r<=R){
		return tree[root];
	}
	int mid=(l+r)>>1;
	Tree res={0,0,0,0};
	Tree res1=res,res2=res;
	if(L<=mid){
		res1=query(root<<1,l,mid,L,R);
	}
	if(R>mid){
		res2=query(root<<1|1,mid+1,r,L,R);
	}
	pushup(res,res1,res2);
	return res;
}
Tree R(Tree u){
    swap(u.lx,u.rx);
    return u;
}
Tree uv_query(int u,int v){
    Tree res={0,0,0,0};
	Tree res1=res,res2=res;
    while(tp[u]!=tp[v]){
        if(dep[tp[u]]<dep[tp[v]]){
            pushup(res2,query(1,1,n,dfn[tp[v]],dfn[v]),res2);
            v=fa[tp[v]];
        }
        else{
            pushup(res1,res1,R(query(1,1,n,dfn[tp[u]],dfn[u])));
            u=fa[tp[u]];
        }
    }
    if(dep[u]<dep[v]){
    	pushup(res,res1,query(1,1,n,dfn[u]+1,dfn[v]));
    }
    else{
    	pushup(res,res1,R(query(1,1,n,dfn[v]+1,dfn[u])));
    }
	pushup(res,res,res2);
	return res;
}
void solve()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
		E[i]={u,v,w};
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		q[i]={u,v,w,i};
	}
	sort(E+1,E+n);
	sort(q+1,q+m+1);
	int pos=1;
	for(int i=1;i<=m;i++){
		while(pos<n&&E[pos].w>=q[i].w){
			int u=E[pos].u,v=E[pos].v;
			if(fa[u]==v){
				swap(u,v);
			}
			update(1,1,n,dfn[v]);
			pos++;
		}
		int u=q[i].u,v=q[i].v;
		output[q[i].id]=uv_query(u,v).sum;
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",output[i]);
	}
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：xiezheyuan (赞：3)

## 简要题意

给出一个 $n$ 个点的树，边有边权。

定义一个序列 $a$ 的权值为 $f_{|a|}$。

有 $m$ 次询问，每次询问给出一个三元组 $(u,v,l)$。求路径上的每条边的边权中，$\leq l$ 的边权的连续段权值和。


$1 \leq n,m \leq 10^5$

## 思路

和 [CF696E](https://www.luogu.com.cn/problem/CF696E) 一样，这又是一道毒瘤树剖题。

大致思路和大家的差不多。

我们离线处理每一个询问。将询问和边排序之后，用类似二维偏序（或扫描线）的思想，每次更新边的权值，就可以转换树上路径中成连续全 $1$ 段的权值和。

这是可以使用线段树 + 树剖维护的。时间复杂度 $O(n\log^{2}n)$。


## 实现

对于一道 \*3100 的题目，我觉得这道题的特点就是：难调！

不信大家可以欣赏以下我的提交记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/uwdy070b.png)

所以我们重点来讲以下实现。

### 线段树

首先是如何合并左右区间的答案。

我们维护四个东西：

- $\text{ans}$ 顾名思义，就是这个区间的答案。下面的公式中记作 $A$。
- $\text{pre}$ 表示这个区间的前缀全 $1$ 子串长度。下面的公式中记作 $P$。
- $\text{suf}$ 表示这个区间的后缀全 $1$ 子串长度。下面的公式中记作 $S$。
- $\text{len}$ 表示这个区间的长度。下面的公式中记作 $L$。

然后考虑每一个量的转移。

首先是 $\text{len}$，这个最简单（公式中 $i$ 表示当前节点，$l$ 表示左子结点，$r$ 表示右子结点）：

$$
L_i = L_l + L_r
$$

然后是 $\text{pre}$，我们分两种情况讨论：

- 大多数情况下，就是左子树的前缀。
- 如果左子树恰好是一个全 $1$ 序列，则需要将右子树前缀加上。

所以有：

$$
P_i = P_l + [P_l = L_l]\times P_r
$$

类似的，$\text{suf}$ 也可以推出来：

$$
S_i = S_r + [S_r = L_r]\times S_l
$$

最后是 $\text{ans}$，$\text{ans}$ 的贡献分成两个部分：

- 原来的左区间和右区间的答案和。
- 左区间的后缀和右区间的前缀被拼成一个完整的。

按照上面的思路，可以写成：

$$
A_i = A_l + A_r - (f_{S_l} + f_{P_r}) + f_{S_l+P_r}
$$

然后只需要维护单点修改和区间查询即可。

### 树链剖分

首先我们注意到前面的 $\text{merge}$ 函数不具备交换律（换句话说就是答案具有顺序性），这就是我们写代码难调的罪魁祸首。

我们跳链时，分成两个部分，一个是 $u\to \text{LCA}(u,v)$，一个是 $v\to\text{LCA}(u,v)$。我们分别记作 $\text{ans1,ans2}$。

然后考虑几个时刻：

- 在两个节点跳重链的时候，如果 $u$ 重链顶端深度**小于** $v$，则此时我们转为跳 $v$，此时为了方便计算，交换 $\text{ans1,ans2}$。$\text{query}$ 返回的答案是 $\text{top}(u)\to u$ 的，也就是说深度从小到大给出的。也就是说如果我们需要维护这个性质，必须把新的加在旧的前面。也就是 `ans1 = merge(now, ans1)`。
- 在一个点已经到达 $\text{LCA}(u,v)$ 时。如果 $u$ 的深度**小于** $v$ 的深度，我们转为跳 $v$，交换 $\text{ans1,ans2}$。合并顺序与之前相同（注意此时交换 $\text{u,v}$ 的时机与交换 $\text{ans1,ans2}$ 不同）。
- 合并 $\text{ans1,ans2}$。注意到 $\text{ans1,ans2}$ 都是深度从小到大的，所以我们需要翻转其中一个，比如说 $\text{ans2}$（翻转只需要交换 $\text{pre}$ 和 $\text{suf}$，其他不会变）。此时 $\text{ans2}$ 深度从大到小。
- 树上路径中深度满足先变小，再变大，再变小。所以最后结果为 `merge(ans2,ans1)`。

一个小细节，如何设置变量初始值？我们可以记录一个 $\text{nsol}$ 状态位来实现。

### Generator

如果大家需要对拍，我可以提供一个简单的数据生成器供参考：

```python
from cyaron import *

s = ""

n = 100
m = 100
rg = (-1000, 1000)

p = [str(randint(*rg)) for i in range(n - 1)]

s += "{} {}\n".format(n, m)
s += " ".join(p) + "\n"
tree = Graph.tree(n, weight_limit = rg)
s += tree.to_str() + "\n"
for i in range(m):
    s += "{} {} {}\n".format(randint(1, n), randint(1, n), randint(*rg))
with open("1.in", "w") as f:
    f.write(s)

```

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i<<1)
#define rs (i<<1|1)
#define mid ((l+r)>>1)
#ifndef LOCAL
#define LOCAL 0
#endif
#define debug(fmt,...) if(LOCAL) do{fprintf(stderr,fmt,##__VA_ARGS__);fprintf(stderr,"\n");}while(0)
#define dbgpt do{debug("Hello! I am at line %d.", __LINE__);}while(0)
#define error(expr,fmt,...) do{if((expr)){debug(fmt,##__VA_ARGS__);exit(0);}}while(0)
using namespace std;
 
const int N = 1e5+5;
 
struct edge{
    int nxt,to;
} g[N*2];
int head[N],ec;
 
void add(int u,int v){
    g[++ec].nxt=head[u];
    g[ec].to=v;
    head[u]=ec;
}
 
int father[N],son[N],siz[N],dep[N];
 
void dfs1(int u,int fa){
    dep[u] = dep[fa] + 1;
    father[u] = fa;siz[u] = 1;
    for(int i = head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
 
int top[N],seg[N];
 
void dfs2(int u,int fa){
    if(son[u]){
        top[son[u]] = top[u];
        seg[son[u]] = ++seg[0];
        dfs2(son[u], u);
    }
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa || v == son[u]) continue;
        top[v] = v;
        seg[v] = ++seg[0];
        dfs2(v, u);
    }
}
struct node{
    int ans,pre,suf,len,nsol;
} t[N<<2];
int f[N];
 
node merge(node x, node y){
    node ret;
    if(x.nsol) return y;
    if(y.nsol) return x;
    ret.pre = (x.pre == x.len) ? (x.pre + y.pre) : x.pre;
    ret.suf = (y.suf == y.len) ? (x.suf + y.suf) : y.suf;
    ret.len = x.len + y.len;
    ret.ans = x.ans + y.ans + f[x.suf + y.pre] - f[x.suf] - f[y.pre];
    ret.nsol = false;
    return ret;
}
 
void build(int i,int l,int r){
    if(l == r) {
        t[i].pre = t[i].suf = 1;
        t[i].ans = f[1];
        t[i].len = 1;
        return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}
 
void update(int p,int v,int i,int l,int r){
    if(l == r){
        t[i].pre = t[i].suf = (v == 1);
        t[i].ans = (v == 1) ? f[1] : 0;
        return;
    }
    if(p <= mid) update(p, v, ls, l, mid);
    else update(p, v, rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}
 
node query(int ql,int qr,int i,int l,int r){
    assert(ql <= qr);
    if(ql <= l && r <= qr) return t[i];
    if(ql <= mid && qr > mid) return merge(query(ql, qr, ls, l, mid), query(ql, qr, rs, mid + 1, r));
    if(ql <= mid) return query(ql, qr, ls, l, mid);
    return query(ql, qr, rs, mid + 1, r);
}
 
int QueryPath(int u,int v){
    node ans1, ans2;
    ans1.nsol = ans2.nsol = true;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v), swap(ans1, ans2);
        node now = query(seg[top[u]], seg[u], 1, 1, seg[0]);
        ans1 = merge(now, ans1);
        u = father[top[u]];
    }
    if(u != v){
        if(dep[u] > dep[v]) swap(u, v);
        else swap(ans1, ans2);
        node now = query(seg[u] + 1, seg[v], 1, 1, seg[0]);
        ans1 = merge(now, ans1);
    }
    swap(ans2.pre, ans2.suf);
    node ans = merge(ans2, ans1);
    if(ans.nsol) return 0;
    return ans.ans;
}
 
int n,m;
 
struct Queries{
    int l,r,p,id;
    bool operator < (const Queries &Q) const{
        return p < Q.p;
    }
} qs[N];
 
struct edge2{
    int u,v,w;
    bool operator<(const edge2 &x) const {
        return w < x.w;
    }
} g2[N];
 
int tt = 1;
int ans[N];
 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<n;i++) cin>>f[i];
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        add(u, v);
        add(v, u);
        g2[i] = {u, v, w};
    }
    dfs1(1, 0);
    seg[1] = top[1] = seg[0] = 1;
    dfs2(1, 0);
    build(1, 1, seg[0]);
    for(int i=1;i<=m;i++){
        cin>>qs[i].l>>qs[i].r>>qs[i].p;
        qs[i].id = i;
    }
    sort(qs+1, qs+m+1);
    sort(g2+1, g2+n);
    for(int i=1;i<=m;i++){
        while(tt < n && g2[tt].w < qs[i].p){
            // dbgpt;
            auto ele = g2[tt++];
            if(dep[ele.u] > dep[ele.v]) swap(ele.u, ele.v);
            update(seg[ele.v], 0, 1, 1, seg[0]);
        }
        ans[qs[i].id] = QueryPath(qs[i].l, qs[i].r);
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：Alex_Eon (赞：2)

#### [$\color{red}博客内食用效果更佳（点我）$](https://www.luogu.com.cn/blog/Ksy/solution-cf536e)
### 题外话
模拟赛里的题，考场上写错了没被卡掉，树剖忘记维护子树大小，写题解警示自己。
### 主体思路：重链剖分+线段树
### 复杂度：$O(q\log^2{n})$
### 完整思路
先把边权下放为点权，然后考虑固定 $l$ 的情况，假设点权已被设为 $0/1$，维护以下信息：
- $las$：区间最左侧连续 $1$ 的个数。
- $ras$：区间最右侧连续 $1$ 的个数。
- $as$：区间内部贡献（不包括左右两侧的 $1$）。
- $al$：区间是否全为 $1$。

合并时只需要加入中间拼接的贡献，注意合并时左右区间有一个全为 $1$ 的情况（或都全为 $1$）。（这种维护方式并不是最优的，需要注意一些细节，更巧妙的维护可以参考其他题解。）

然后考虑不固定 $l$ 我们的做法，常见的套路，将询问离线，按照 $l$ 从大到小排序，这样修改时只会出现从 $0$ 修改成 $1$ 的情况，简单单点修改即可，每个点只会被修改一次，复杂度合理。

具体地，我把所有边扔到优先队列里，每次取队首尝试加入，直到队首边权小于当前 $l$。

### 代码实现需要注意的地方：

- 细节很多，初值、合并细节等都需要注意。
- 树剖求答案时最后合并两条链时需要将其中一条翻转。
- 树剖不要写假，不要像我一样没维护子树大小。

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define UN unsigned
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
using namespace std;
//--------------------//
//IO
inline int rd()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
//--------------------//
const int N=2e5+5;

int n,m;
int f[N];
struct Que
{
    int x,y,l,id;
}q[N];
bool cmp(Que x,Que y){return x.l>y.l;}
int ans[N];
//--------------------//
const int TN=8e5+5;
struct Seg_Tree_Node
{
    int las,ras,as;
    bool al;
    Seg_Tree_Node(){las=ras=as=0,al=false;}
    Seg_Tree_Node(int a,int b,int c,bool d){las=a,ras=b,as=c,al=d;}
};
//bool pri;
struct Seg_Tree
{
    Seg_Tree_Node t[TN];
    Seg_Tree_Node merge(Seg_Tree_Node x,Seg_Tree_Node y)//合并信息
    {
        if(x.las==-1)
            return y;
        if(y.las==-1)
            return x;
        Seg_Tree_Node res(0,0,x.as+y.as,false);
        res.al=(x.al&y.al);
        if(res.al)
        {
            res.ras=res.las=x.las+y.ras;
            return res;
        }
        if(x.al)
            res.las=x.las+y.las,res.ras=y.ras;
        else if(y.al)
            res.las=x.las,res.ras=y.ras+x.ras;
        else
            res.las=x.las,res.ras=y.ras,res.as+=f[x.ras+y.las];
        return res;
    }
    void change(int rt,int L,int R,int pos)
    {
        if(L==R)
        {
            t[rt].as=0,t[rt].las=t[rt].ras=1,t[rt].al=true;
            return;
        }
        int mid=L+R>>1;
        if(pos<=mid)
            change(ls(rt),L,mid,pos);
        else
            change(rs(rt),mid+1,R,pos);
        t[rt]=merge(t[ls(rt)],t[rs(rt)]);
        return;
    }
    Seg_Tree_Node query(int rt,int L,int R,int l,int r)
    {
        if(L>=l&&R<=r)
            return t[rt];
        int mid=L+R>>1;
        if(r<=mid)
            return query(ls(rt),L,mid,l,r);
        if(l>mid)
            return query(rs(rt),mid+1,R,l,r);
        return merge(query(ls(rt),L,mid,l,r),query(rs(rt),mid+1,R,l,r));
    }
}T;
//--------------------//
const int M=5e5+5;
struct Edge
{
    int to,w,nex;
}edge[M];
int tot,head[N];
void add(int from,int to,int w)
{
    edge[++tot]={to,w,head[from]};
    head[from]=tot;
    return;
}
struct Poi
{
    int fa,faw,dep,siz,hson;
    int top,dfn;
}p[N];
int dcnt,rk[N];
void DFS1(int now,int fa,int w)
{
    p[now].fa=fa,p[now].faw=w,p[now].dep=p[fa].dep+1,p[now].siz=1;
    for(int to,w,i=head[now];i;i=edge[i].nex)
    {
        to=edge[i].to,w=edge[i].w;
        if(to==fa)
            continue;
        DFS1(to,now,w);
        p[now].siz+=p[to].siz;
        if(!p[now].hson||p[to].siz>p[p[now].hson].siz)
            p[now].hson=to;
    }
    return;
}
void DFS2(int now,int top)
{
    p[now].top=top,p[now].dfn=++dcnt,rk[dcnt]=now;
    if(p[now].hson)
        DFS2(p[now].hson,top);
    for(int to,i=head[now];i;i=edge[i].nex)
    {
        to=edge[i].to;
        if(to==p[now].fa||to==p[now].hson)
            continue;
        DFS2(to,to);
    }
    return;
}
priority_queue<pair<int,int>>pq;
void init()//将边加入优先队列
{
    for(int i=1;i<=n;i++)
        pq.push({p[i].faw,p[i].dfn});
    return;
}
int query(int x,int y,int tl)
{
    while(pq.top().first>=tl&&!pq.empty())
    {
        T.change(1,1,n,pq.top().second);
        pq.pop();
    }
    Seg_Tree_Node temx,temy,tem;
    temx.las=-1,temy.las=-1;//初值设置，在 merge 函数中有特判
    int ttcntt=0;
    while(p[x].top!=p[y].top)
    {
        ttcntt++;
        if(p[p[x].top].dep<p[p[y].top].dep)
            swap(x,y),swap(temx,temy);
        tem=T.query(1,1,n,p[p[x].top].dfn,p[x].dfn);
        temx=T.merge(tem,temx);
        x=p[p[x].top].fa;
    }
    if(x!=y)//特判相等情况
    {
        if(p[x].dep<p[y].dep)
            swap(x,y),swap(temx,temy);
        tem=T.query(1,1,n,p[y].dfn+1,p[x].dfn);//边权下放所以不包括顶点
        temx=T.merge(tem,temx);
    }
    swap(temx.las,temx.ras);//区间翻转
    temx=T.merge(temx,temy);
    return temx.as+f[temx.las]+(temx.al?0:f[temx.ras]);
}
//--------------------//
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
        f[i]=rd();
    for(int from,to,w,i=1;i<n;i++)
        from=rd(),to=rd(),w=rd(),add(from,to,w),add(to,from,w);
    p[0].dep=-1;
    DFS1(1,0,0);
    DFS2(1,1);
    init();
    for(int i=1;i<=m;i++)
        q[i].x=rd(),q[i].y=rd(),q[i].l=rd(),q[i].id=i;
    sort(q+1,q+m+1,cmp);//离线排序
    for(int i=1;i<=m;i++)
        ans[q[i].id]=query(q[i].x,q[i].y,q[i].l);
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：uniqueharry (赞：1)

题意略。

首先我们可以考虑如果树的边权直接给出的就是 $0/1$，这个问题是否可做。

可以。用线段树维护 $\text{sum, pre, suf, num}$，分别表示区间答案，区间前缀 $1$ 的个数，区间后缀 $1$ 的个数，区间 $1$ 的个数。再套一个树剖就可以维护树上路径。

但现在这个 $0/1$ 并不是一开始给出的，而是根据每次询问的 $l$ 和边权的关系来确定的。但这个问题也很好处理，将询问离线，以 $l$ 为关键字从小到大排序。一开始树上的所有边都是 $1$，随着 $l$ 的变大一些边从 $1$ 变成 $0$，而且再也不会变成 $1$。所以每条边最多只会被修改一次，保证了复杂度的正确。

流程综述：将询问排序。每次找出满足 $w \ge l_{i - 1} \land w < l_i$ 的边并在线段树上修改它们的值，回答询问。

时间复杂度 $O(n \log^2 n)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lc(u) (u << 1)
#define rc(u) (u << 1 | 1)
using namespace std;
const int N = 1e5 + 5;
int n, Q, f[N];
int tot;
struct Edge{
	int id, w;
	bool operator < (const Edge &k) const {
		return w < k.w;
	}
}a[N];
struct query{
	int u, v, l, id;
	bool operator < (const query &k) const {
		return l < k.l;
	}
}q[N];
int head[N], cnt;
struct edge{
	int nxt, to, w, id;
}e[N << 1];
void add(int u, int v, int w, int id){
	e[++cnt].nxt = head[u], e[cnt].to = v, e[cnt].w = w, e[cnt].id = id, head[u] = cnt;
}
int fa[N][19], dep[N], sz[N], son[N], dot[N];
void dfs(int u){
	for(int i = 1; i <= 17; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	sz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].to, id = e[i].id;
		if(v == fa[u][0]) continue;
		fa[v][0] = u, dep[v] = dep[u] + 1, dot[id] = v;
		dfs(v);
		sz[u] += sz[v];
		if(sz[v] > sz[son[u]]) son[u] = v;
	}
}
int dfn[N], pdfn, top[N];
void dfs2(int u, int t){
	dfn[u] = ++pdfn, top[u] = t;
	if(son[u]) dfs2(son[u], t);
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].to;
		if(top[v]) continue;
		dfs2(v, v);
	}
}
int lca(int u, int v){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]][0];
	}
	return dep[u] < dep[v] ? u : v;
}
int jump(int u, int d){
	for(int i = 17; i >= 0; i--) if(dep[fa[u][i]] >= d) u = fa[u][i];
	return u;
}
struct node{
	int sum, pre, suf, num, len;
	node(){
		sum = pre = suf = num = len = 0;
	}
	node(int a, int b, int c, int d, int e){
		sum = a, pre = b, suf = c, num = d, len = e;
	}
}t[N << 2];
node merge(node x, node y){
	node z;
	z.sum = x.sum + y.sum - f[x.suf] - f[y.pre] + f[x.suf + y.pre];
	if(x.num == x.len) z.pre = x.num + y.pre;
	else z.pre = x.pre;
	if(y.num == y.len) z.suf = y.num + x.suf;
	else z.suf = y.suf;
	z.num = x.num + y.num, z.len = x.len + y.len;
	return z;
}
void pushup(int u){
	t[u] = merge(t[lc(u)], t[rc(u)]);
}
void build(int u, int l, int r){
	if(l == r){
		t[u].sum = f[1], t[u].pre = t[u].suf = t[u].num = t[u].len = 1; return;
	}
	int mid = (l + r) >> 1;
	build(lc(u), l, mid), build(rc(u), mid + 1, r);
	pushup(u);
}
void modify(int u, int l, int r, int x){
	if(l == r){
		t[u].sum = t[u].pre = t[u].suf = t[u].num = 0, t[u].len = 1; return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(lc(u), l, mid, x);
	else modify(rc(u), mid + 1, r, x);
	pushup(u);
}
node query(int u, int l, int r, int x, int y){
	if(x > y) return node(0, 0, 0, 0, 0);
	if(l >= x && r <= y) return t[u];
	int mid = (l + r) >> 1;
	if(y <= mid) return query(lc(u), l, mid, x, y);
	if(x > mid) return query(rc(u), mid + 1, r, x, y);
	return merge(query(lc(u), l, mid, x, y), query(rc(u), mid + 1, r, x, y)); 
}
node ask(int u, int v, int op){
	if(dep[u] < dep[v]) swap(u, v);
	int x = lca(u, v);
	if(x == v){
		node res;
		while(top[u] != top[v]){
			if(dep[top[u]] < dep[top[v]]) swap(u, v);
			res = merge(query(1, 2, n, dfn[top[u]], dfn[u]), res);
			u = fa[top[u]][0];
		}
		if(dep[u] < dep[v]) swap(u, v);
		res = merge(query(1, 2, n, dfn[v] + op, dfn[u]), res);
		return res;
	}
	node tl = ask(u, x, 1), tr = ask(jump(v, dep[x] + 1), v, 0);
	swap(tl.pre, tl.suf);
	return merge(tl, tr);
}
int ans[N];
int main(){
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++) scanf("%d", &f[i]);
	for(int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w, i), add(v, u, w, i), a[++tot] = {i, w};
	dep[1] = 1, dfs(1), dfs2(1, 1), build(1, 2, n);
	for(int i = 1; i <= Q; i++) scanf("%d%d%d", &q[i].u, &q[i].v, &q[i].l), q[i].id = i;
	sort(a + 1, a + tot + 1), sort(q + 1, q + Q + 1);
	int last = 0;
	for(int i = 1; i <= Q; i++){
		int l = last + 1, r = tot, mid;
		bool flag = false;
		while(l < r){
			mid = (l + r + 1) >> 1;
			if(a[mid].w < q[i].l) flag = true, l = mid;
			else r = mid - 1;
		}
		if(a[l].w < q[i].l) flag = true;
		if(flag){
			for(int j = last + 1; j <= l; j++) modify(1, 2, n, dfn[dot[a[j].id]]);
			last = l;
		}
		ans[q[i].id] = ask(q[i].u, q[i].v, 1).sum;
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

小清新树剖题。

显然不好直接做，离线下来对 $l$ 扫描线。

时刻保证 $\forall x_i\ge l,s_i=1$，然后每条边的 $s_i$ 只会变化一次。

发现维护的是一个颜色段信息，考虑树剖套线段树。

线段树每个节点上维护前缀 $1$ 的个数，后缀 $1$ 的个数，$1$ 的个数和答案。

注意 push up 时左孩子的后缀 $1$ 和右孩子的前缀 $1$ 形成新段。
```cpp
#include <cstdio>
#include <algorithm>
#define G int m = p->s + p->t >> 1
using namespace std;
struct E
{
    int v, w, t;
} e[200050];
struct S
{
    int u, v, l, i;
} k[100050];
pair<int, int> g[100050];
int n, m, c, p, F[100050], K[100050], z[100050], d[100050],
    f[100050], s[100050], t[100050], b[100050], h[100050];
bool C(S a, S b) { return a.l < b.l; }
void A(int u, int v, int w)
{
    e[++c] = {v, w, h[u]};
    h[u] = c;
}
void X(int u)
{
    s[u] = 1;
    for (int i = h[u], v; i; i = e[i].t)
        if (!d[v = e[i].v])
        {
            f[v] = u;
            d[v] = d[u] + 1;
            g[v] = {e[i].w, v};
            X(v);
            s[u] += s[v];
            if (s[v] > s[z[u]])
                z[u] = v;
        }
}
void Y(int u, int g)
{
    t[u] = g;
    b[u] = ++p;
    if (z[u])
        Y(z[u], g);
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != z[u] && v != f[u])
            Y(v, v);
}
struct T
{
    T *l, *r;
    int s, t, q, x, y, v;
    T(int s, int t) : s(s), t(t) {}
    void u()
    {
        v = l->v + r->v;
        x = l->v == l->t - l->s + 1 ? l->v + r->x : l->x;
        y = r->v == r->t - r->s + 1 ? r->v + l->y : r->y;
        q = l->q + r->q - F[l->y] - F[r->x] + F[l->y + r->x];
    }
} * r;
T *U(T *x, T *y)
{
    if (!x)
        return y;
    if (!y)
        return x;
    T *p = new T(x->s, y->t);
    p->l = x;
    p->r = y;
    p->u();
    return p;
}
void B(int s, int t, T *&p)
{
    p = new T(s, t);
    if (s == t)
        return void(p->q = F[p->x = p->y = p->v = 1]);
    G;
    B(s, m, p->l);
    B(m + 1, t, p->r);
    p->u();
}
void M(int l, T *p)
{
    if (p->s == p->t)
        return void(p->q = p->x = p->y = p->v = 0);
    G;
    if (l <= m)
        M(l, p->l);
    else
        M(l, p->r);
    p->u();
}
T *Q(int l, int r, T *p)
{
    if (l <= p->s && p->t <= r)
        return p;
    G;
    if (l <= m && r > m)
        return U(Q(l, r, p->l), Q(l, r, p->r));
    if (l <= m)
        return Q(l, r, p->l);
    if (r > m)
        return Q(l, r, p->r);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
        scanf("%d", F + i);
    for (int i = 1, u, v, w; i < n; ++i)
        scanf("%d%d%d", &u, &v, &w), A(u, v, w), A(v, u, w);
    X(d[1] = 1);
    Y(1, 1);
    B(1, n, r);
    sort(g + 2, g + n + 1);
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d", &k[i].u, &k[i].v, &k[i].l), k[i].i = i;
    sort(k, k + m, C);
    for (int i = 0, j = 1, u, v; i < m; ++i)
    {
        while (j < n && g[j + 1].first < k[i].l)
            M(b[g[++j].second], r);
        u = k[i].u;
        v = k[i].v;
        T *p = 0, *q = 0;
        while (t[u] != t[v])
        {
            if (d[t[u]] > d[t[v]])
                p = U(Q(b[t[u]], b[u], r), p), u = f[t[u]];
            else
                q = U(Q(b[t[v]], b[v], r), q), v = f[t[v]];
        }
        if (u != v)
        {
            if (d[u] > d[v])
                p = U(Q(b[v] + 1, b[u], r), p);
            else
                q = U(Q(b[u] + 1, b[v], r), q);
        }
        if (p)
            p = new T(*p), swap(p->x, p->y);
        K[k[i].i] = U(p, q)->q;
    }
    for (int i = 0; i < m; ++i)
        printf("%d\n", K[i]);
    return 0;
}
```


---

## 作者：Dtw_ (赞：0)

# 0.前言
好题好题。大力树剖。

/bx/bx @FiraCode @KSCD_
# 1.题意
[Luogu-CF536E](https://www.luogu.com.cn/problem/CF536E)
# 2.Solution
首先，我们考虑如何把他变成 $01$ 串。

先边转点。

然后考虑将询问离线，倒着删点，这样我们就可以直接在树上维护信息了。

考虑我们要维护连续的 $01$，我们记录 $lmx$ 表示最左边连续的 $1$ 的个数，$rmx$ 同理，$mx$ 表示这个段的答案。

然后我们每次 `push_up` 的时候这样更新：

```cpp
void push_up(Node &a, Node b, Node c)
{
	a.sz = b.sz + c.sz;
	a.lmx = b.lmx + c.lmx * (b.lmx == b.sz);
	a.rmx = c.rmx + b.rmx * (c.rmx == c.sz);
	a.mx = b.mx + c.mx - f[b.rmx] - f[c.lmx] + f[b.rmx + c.lmx];
}
```
比较套路。$lmx,rmx$ 和小白逛公园差不多，然后他的贡献就是儿子的贡献加上他新的贡献然后减掉原来的贡献。

然后就是考虑查询，我们在树剖跳左边的时候要注意，因为他要求的是 $u\to v$ 拼成一个 $01$ 串，而我们线段树上维护的都是从根到儿子这个方向的，也就是说 $u\to lca$ 的时候他线段树上的 $01$ 串应该反过来，所以我们需要将 $lmx$ 和 $rmx$ 互换，然后在合并。

还有一个坑点就是最终 $x$ 和 $y$ 可能跳动同一个点上，此时我们的边转点就不行了，所以特判一下，然后在拼上。

# Code

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define fi first
#define se second
 
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
 
const int N = 1e5 + 10;
 
int n, m, a[N], f[N], dfn[N], rnk[N], top[N], son[N], sz[N], ff[N], dep[N], cnt, res[N];
 
vector<int> G[N];
 
void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	sz[u] = 1;
	son[u] = -1;
	ff[u] = fa;
	for (auto v : G[u])
	{	
		if (v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
		if (son[u] == -1 || sz[son[u]] < sz[v]) son[u] = v;
	}
}
 
void dfs_(int u, int t)
{
	dfn[u] = ++cnt;
	rnk[cnt] = u;
	top[u] = t;
	if (son[u] == -1) return;
	dfs_(son[u], t);
	for (auto v : G[u])
	{
		if (v == ff[u] || v == son[u]) continue;
		dfs_(v, v);
	}
}
 
struct Node
{
	int lmx, mx, rmx;
	int sz;	
} tr[N << 2];
 
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define mid (l + r) / 2
 
void push_up(Node &a, Node b, Node c)
{
	a.sz = b.sz + c.sz;
	a.lmx = b.lmx + c.lmx * (b.lmx == b.sz);
	a.rmx = c.rmx + b.rmx * (c.rmx == c.sz);
	a.mx = b.mx + c.mx - f[b.rmx] - f[c.lmx] + f[b.rmx + c.lmx];
}
 
void build(int rt, int l, int r)
{
	tr[rt].sz = r - l + 1;
	if (l == r) return tr[rt] = {1, f[1], 1, 1}, void();
	build(lson, l, mid);
	build(rson, mid + 1, r);
	push_up(tr[rt], tr[lson], tr[rson]);
}
 
void update(int rt, int l, int r, int p)
{
	if (l == r) return tr[rt] = {0, 0, 0, 1}, void();
	if (p <= mid) update(lson, l, mid, p);
	else update(rson, mid + 1, r, p);
	push_up(tr[rt], tr[lson], tr[rson]);
}
 
Node query(int rt, int l, int r, int sp, int ep)
{
	if (sp <= l && r <= ep) return tr[rt];
	Node res;
	bool f = 0;
	if (sp <= mid) res = query(lson, l, mid, sp, ep), f = 1;
	if (ep > mid)
	{
		if (f) push_up(res, res, query(rson, mid + 1, r, sp, ep));
		else res = query(rson, mid + 1, r, sp, ep);
	}
	return res;
}
 
struct qry { int u, v, k, id; } q[N], e[N];
 
Node swp(Node a)
{
	swap(a.lmx, a.rmx);
	return a;
}
 
int qrypath(int x, int y)
{
	Node res = {0, 0, 0, 0};
	Node a = res, b = res;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]]) push_up(b, query(1, 1, n, dfn[top[y]], dfn[y]), b), y = ff[top[y]];
		else push_up(a, a, swp(query(1, 1, n, dfn[top[x]], dfn[x]))), x = ff[top[x]];
	}
	if (x == y) res = a;
	else if (dep[x] < dep[y]) push_up(res, a, query(1, 1, n, dfn[x] + 1, dfn[y]));
	else push_up(res, a, swp(query(1, 1, n, dfn[y] + 1, dfn[x])));
	push_up(res, res, b);
	return res.mx;
}
 
int main()
{
	fst
	cin >> n >> m;
	for (int i = 1; i < n; i++) cin >> f[i];
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		e[i] = {u, v, w};
		G[u].push_back(v), G[v].push_back(u);
	}
	for (int i = 1; i <= m; i++) cin >> q[i].u >> q[i].v >> q[i].k, q[i].id = i;
	sort (q + 1, q + m + 1, [] (qry x, qry y) { return x.k < y.k; });
	sort (e + 1, e + n, [] (qry x, qry y) { return x.k < y.k; });
	dfs(1, 0);
	dfs_(1, 1);
	build(1, 1, n);
	for (int i = 1; i < n; i++) if (dep[e[i].u] < dep[e[i].v]) swap(e[i].u, e[i].v);
	for (int i = 1, j = 1; i <= m; i++)
	{
		while (j < n && e[j].k < q[i].k) update(1, 1, n, dfn[e[j++].u]);
		res[q[i].id] = qrypath(q[i].u, q[i].v);
	}
	for (int i = 1; i <= m; i++) cout << res[i] << "\n";
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

多细节的树链剖分题（其实还好，我就交了五次）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vw0iguy6.png)

先将询问离线保存下来，按 $l$ 排序，一点一点地将树上的边权变成 $1$。

然后就是线段树维护答案了，每个节点维护一个区间左边的最长的全一长度、右边的最长的全一长度、中间（不碰边界）的代价和区间长度。

合并区间是简单的，判一下是否全部都是一即可。

注意一下，计算 $u$ 到 $lca$ 的答案时，不能将 $lca$ 上的数算进去，还有记得反转 $u$ 到 $lca$ 的区间答案再与 $v$ 到 $lca$ 的答案拼接起来。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,f[N],ans[N];
int dfn[N],son[N],dep[N],top[N],siz[N],fat[N],cnt=0;
struct node{
	int v,w;
};
vector<node>g[N];
struct edge{
	int u,v,w;
}e[N];
struct line{
	int u,v,l,id;
}q[N];
bool cmp(line x,line y){
	return x.l>y.l;
}
bool tmp(edge x,edge y){
	return x.w>y.w;
}
struct seg{
	int lmax,rmax,num,len;
}tree[N<<2];
void dfs1(int u,int fa){
	siz[u]=1;fat[u]=fa;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v;
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
void dfs2(int u,int topx){
	top[u]=topx;
	dfn[u]=++cnt;
	if(!son[u])return;
	dfs2(son[u],topx);
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v;
		if(v==fat[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void build(int rt,int l,int r){
	tree[rt].len=r-l+1;
	if(l==r)return;
	int mid=l+r>>1;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
}
seg pushup(seg x,seg y){
	if(x.len==0)return y;
	if(y.len==0)return x;
	if(x.rmax==x.len&&y.lmax==y.len)return {x.len+y.len,x.len+y.len,0,x.len+y.len};
	if(x.rmax==x.len)return {x.len+y.lmax,y.rmax,y.num,x.len+y.len};
	if(y.lmax==y.len)return {x.lmax,x.rmax+y.len,x.num,x.len+y.len};
	return {x.lmax,y.rmax,f[x.rmax+y.lmax]+x.num+y.num,x.len+y.len};
}
void update(int rt,int l,int r,int x){
	if(l==r){
		tree[rt].lmax=tree[rt].rmax=tree[rt].len=1;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)update(rt*2,l,mid,x);
	else update(rt*2+1,mid+1,r,x);
	tree[rt]=pushup(tree[rt*2],tree[rt*2+1]);
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
seg query(int rt,int l,int r,int x,int y){
	if(x>y)return {0,0,0,0};
	if(x<=l&&r<=y)return tree[rt];
	int mid=l+r>>1;
	seg res={0,0,0,0};
	if(x<=mid)res=pushup(res,query(rt*2,l,mid,x,y));
	if(y>mid)res=pushup(res,query(rt*2+1,mid+1,r,x,y));
	return res;
}
seg ask(int x,int y){
	seg res={0,0,0,0};
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res=pushup(query(1,1,n,dfn[top[x]],dfn[x]),res);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	res=pushup(query(1,1,n,dfn[x]+1,dfn[y]),res);
	return res;
}
int calc(seg cnt){
	if(cnt.lmax==cnt.len)return f[cnt.len];
	return f[cnt.lmax]+f[cnt.rmax]+cnt.num;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d",&f[i]);
	}
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		g[e[i].u].push_back({e[i].v,e[i].w});
		g[e[i].v].push_back({e[i].u,e[i].w});
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&q[i].u,&q[i].v,&q[i].l);
		q[i].id=i;
	}
	dfs1(1,0);
	dfs2(1,1);
	sort(q+1,q+1+m,cmp);
	sort(e+1,e+n,tmp);
	build(1,1,n);
	for(int i=1,j=1;i<=m;i++){
		while(j<n&&e[j].w>=q[i].l){
			if(fat[e[j].u]==e[j].v)swap(e[j].u,e[j].v);
			update(1,1,n,dfn[e[j].v]);
			j++;
		}
		if(q[i].u==q[i].v){
			ans[q[i].id]=0;
			continue;
		}
		int l=lca(q[i].u,q[i].v);
		if(l==q[i].u||l==q[i].v){
			seg cnt=ask(q[i].u,q[i].v);
			ans[q[i].id]=calc(cnt);
		}else{
			seg x=ask(q[i].u,l),y=ask(q[i].v,l);
			swap(x.lmax,x.rmax);
			seg cnt=pushup(x,y);
			ans[q[i].id]=calc(cnt);
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}

```

---

## 作者：happybob (赞：0)

考虑 $l$ 固定时怎么做，每条边的边权是 $0$ 或者 $1$，求路径上每个极长连续 $1$ 的段长作为下标的 $f$ 的和。

树剖维护，问题转化成序列问题，只需要维护线段树，每个区间维护对应答案以及左侧连续 $1$ 长度和右侧连续 $1$ 长度，合并时容易更新答案。

现在 $l$ 不固定，考虑离线扫描线，将这个做法套上一个单点修改就好了。

口胡的，没代码。

---

## 作者：rainygame (赞：0)

> 我的解题过程：思路五分钟，调试五小时。感觉这道题思路没有 \*3100，CF 评那么高纯粹的因为实现和调试难度较大。

以下的变量均为翻译中的变量。

我们可以先把问题从树上搬下来，考虑如果是一个序列怎么做？

先假设 $s$ 是给定的，那么维护的时候只需要维护 $f_{p_i}$ 的总和、左右颜色以及从左右分别开始的一段同 $s_i$ 段的长度即可，合并方式参考代码。这种线段树的维护思路和[小白逛公园](https://www.luogu.com.cn/problem/P4513)很像，如果不会的话建议先学习。

再考虑一个更难的问题：$s_i$ 由 $x_i$ 的大小决定，且每次给定的阈值 $l$ 不一定相同。如果直接用线段树维护是很困难的。所以我们要考虑离线，我们可以按 $l$ 升序排序，一开始线段树的 $s_i$ 均为 $1$，当枚举到某个 $l$ 时，把小于 $l$ 的均单点修改为 $0$。每个结点最多只会被修改一次，所以复杂度为 $O((n+m) \log n)$。

接下来我们将它用树链剖分搬回到树上，但是这个貌似和普通的树链剖分不同。

- 普通的树链剖分都是维护点权，这个要维护边权。

	针对这个问题有一种要做“边点互化”的 trick，具体地，由于一个点连接到它父亲的边是唯一的，所以我们考虑将边权下放到对应儿子的点权，**注意修改和查询的边界**。
    
- 普通的树链剖分不需要区间合并，只需要统计每个区间后再运算即可，但本题需要合并区间。

	我们可以先把查询的端点 $u,v$ 的 LCA $L$ 求出来，然后先统计 $u \rightarrow L$ 的答案，再统计 $L \rightarrow v$ 的答案，**这里区间合并的顺序不能错**。
    
复杂度显然是 $O((n+m) \log^2 n)$ 的。
    
至此，这道 CF 评分为 \*3100 就被我们切掉了：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 100001

int n, m, u, v, w, cnt, ind;
int f[MAXN], id[MAXN], at[MAXN], a[MAXN], ans[MAXN];
int dep[MAXN], son[MAXN], siz[MAXN], fa[MAXN], top[MAXN];

struct Edge{
	int v, w;
};
vector<Edge> e[MAXN];

struct Edge2{
    int u, v, w;
}egs[MAXN];
bool cmp(Edge2 a, Edge2 b){
    return a.w > b.w;
}

struct Que{
    int ind, u, v, l;
}que[MAXN];

bool cmp2(Que a, Que b){
    return a.l > b.l;
}

void dfs1(int x, int f){
	fa[x] = f;
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	for (auto i: e[x]){
		int v(i.v);
		if (v != f){
			at[v] = i.w;
			dfs1(v, x);
			siz[x] += siz[v];
			if (siz[son[x]] < siz[v]) son[x] = v;
		}
	}
}

void dfs2(int x, int tp){
	top[x] = tp;
	id[x] = ++cnt;
    a[cnt] = at[x];
	if (!son[x]) return;
	dfs2(son[x], tp);
	for (auto i: e[x]){
		int v(i.v);
		if (v != fa[x] && v != son[x]) dfs2(v, v);
	}
}

int LCA(int u, int v){
    while (top[u] ^ top[v]){
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) return v;
    return u;
}

struct Node{
    int l, r;
    int lc, rc, sum, len;
    int lsz, rsz;
    Node(){
        lc = rc = -1;
        sum = lsz = rsz = len = 0;
    }
    void print(){cout << sum << ' ' << lsz << ' ' << rsz << ' ' << lc << ' ' << rc << '\n';}
};

void merge(Node a, Node b, Node &c){
    c.len = a.len + b.len;
    c.lc = (a.lc ^ -1 ? a.lc : b.lc);
    c.rc = (b.rc ^ -1 ? b.rc : a.rc);
    c.lsz = ((a.lsz == a.len && a.lc == b.lc) || a.lc == -1 ? a.len+b.lsz : a.lsz);
    // cout << a.lc << ' ' << b.lc << ' ' << c.lc << '\n';
    c.rsz = ((b.rsz == b.len && a.rc == b.rc) || b.rc == -1 ? b.len+a.rsz : b.rsz);
    c.sum = a.sum+b.sum;
    if (a.rc == 1 && b.lc == 1){
        c.sum -= f[a.rsz] + f[b.lsz];
        c.sum += f[a.rsz + b.lsz];
    }
}

struct Seg{
    Node tree[MAXN<<2];
#define push_up(p) merge(tree[p<<1], tree[p<<1|1], tree[p])

    void build(int l, int r, int p){
        tree[p].l = l;
        tree[p].r = r;
        if (l == r){
            tree[p].lsz = tree[p].rsz = tree[p].len = 1;
            tree[p].lc = tree[p].rc = 0;
            return;
        }

        int mid((l+r)>>1);
        build(l, mid, p<<1);
        build(mid+1, r, p<<1|1);
        push_up(p);
    }

    void modify(int p, int x){
        if (tree[p].l == tree[p].r){
            tree[p].lc = tree[p].rc = 1;
            tree[p].sum = f[1];
            return;
        }

        int mid((tree[p].l+tree[p].r)>>1);
        if (x <= mid) modify(p<<1, x);
        else modify(p<<1|1, x);
        push_up(p);
        // cout << p << ' ' << tree[p].l << ' ' << tree[p].r << '\n';
        // tree[p].print();
    }

    Node query(int L, int R, int p){
        // if (L == 2 && R == 4) cout << p << '\n';
        if (tree[p].l >= L && tree[p].r <= R) return tree[p];
        int mid((tree[p].l+tree[p].r)>>1);
        Node res;
        if (L <= mid) merge(res, query(L, R, p<<1), res);
        // if (L == 2 && R == 4){
        //     cout << p << ' ' << tree[p].l << ' ' << tree[p].r << ' ' << res.lsz << '\n';
        //     if (p == 6) cout << query(L, R, p<<1).lc << '\n';
        // }
        if (R > mid) merge(res, query(L, R, p<<1|1), res);
        return res;
    }

    Node query(int l, int r){
        Node tmp(query(l, r, 1));
        swap(tmp.lsz, tmp.rsz);
        swap(tmp.lc, tmp.rc);
        return tmp;
    }
}tr;

int query(){
    int lca(LCA(u, v));
    Node res, res2;
    while (top[u] ^ top[lca]){
        merge(res, tr.query(id[top[u]], id[u]), res);
        u = fa[top[u]];
    }
    if (u ^ lca) merge(res, tr.query(id[lca]+1, id[u]), res);
    while (top[v] ^ top[lca]){
        merge(tr.query(id[top[v]], id[v], 1), res2, res2);
        v = fa[top[v]];
    }
    // cout << id[lca]+1 << ' ' << id[v] << '\n';
    if (v ^ lca) merge(tr.query(id[lca]+1, id[v], 1), res2, res2);
    // res2.print();
    merge(res, res2, res);
    return res.sum;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i(1); i<n; ++i) cin >> f[i];
    for (int i(1); i<n; ++i){
    	cin >> u >> v >> w;
    	e[u].push_back({v, w});
    	e[v].push_back({u, w});
        egs[i] = {u, v, w};
	}
	dfs1(1, 0);
	dfs2(1, 1);
    tr.build(1, n, 1);

    for (int i(1); i<=m; ++i){
        cin >> que[i].u >> que[i].v >> que[i].l;
        que[i].ind = i;
    }
    sort(egs+1, egs+n, cmp);
    sort(que+1, que+m+1, cmp2);

    for (int i(1); i<=m; ++i){
        while (ind < n-1 && egs[ind+1].w >= que[i].l){
            ++ind;
            u = egs[ind].u;
            v = egs[ind].v;
            if (dep[v] > dep[u]) swap(u, v);
            // cout << "ad:" << u << '\n';
            tr.modify(1, id[u]);
        }
        // cout << que[i].ind << ' ' << que[i].u << ' ' << que[i].v << ' ' << que[i].l << '\n';
        // tr.tree[12].print();
        u = que[i].u;
        v = que[i].v;
        ans[que[i].ind] = query();
    }
    for (int i(1); i<=m; ++i) cout << ans[i] << '\n';

    return 0;
}
```

这应该是我第一次独立写出来 \*3100 的题吧，纪念一下。

---

## 作者：max0810 (赞：0)

一道小清新树剖题。。。

感觉这道题和[P2486 [SDOI2011] 染色](https://www.luogu.com.cn/problem/P2486)比较像，都是求颜色段。

## 题意简述

给定一棵 $n$ 个节点的树，每条边有边权。

有 $m$ 个询问，形式为 $(u,v,l)$，求 $u$ 到 $v$ 的路径，假设长度为 $p$，第 $i$ 条边权值为 $x_i$，构造一个长度为 $p$ 的 $01$ 串 $s$，如果 $x_i\ge l$，那么 $s_i=1$，否则 $s_i=0$。

对于得到的串 $s$，假设它有 $k$ 段连续的 1，第 $i$ 段长度为 $p_i$，那么要你输出所有 $f_{p_i}$ 的和，其中 $f$ 数组一开始就给出。

## 题解

我们设初始所有边为 $0$。首先把询问离线，按 $l$ 从大到小排序，然后每到一个询问，就把所有大于等于这个询问的 $l$ 的边设为 $1$，然后询问从 $u$ 到 $v$ 的答案。因为排了一遍序，所以每条边至多一次被设为 $1$。

接着考虑如何处理询问，如果这是一个序列的话，我们可以用线段树来维护。

具体来说，每个节点设四个变量 $x,l,r,b$，分别表示这个区间的答案，左边 $1$ 的个数，右边 $1$ 的个数，整个区间是否全为 $1$。根据以上定义，我们可以写出两个区间合并的代码：

```cpp
struct node
{
    int x,l,r;bool b;
    friend node operator +(node x,node y)
    {return {x.x+y.x-f[x.r]-f[y.l]+f[x.r+y.l],x.l+x.b*y.l,y.r+y.b*x.r,x.b&&y.b};}
}t[N << 2];
```
考虑把序列问题转化为树上问题，在代码中加一个树剖即可。

但是要注意的是，这个合并是不满足交换律的，所以不能像一般树剖一样做。比如在求 $x-y$ 这条路径的答案时，我们应该记两个变量 $ans1$ 和 $ans2$，表示 $x$ 向上跳的答案，和 $y$ 向上跳的答案。当 `swap(x,y)` 时，同时也要 `swap(ans1,ans2)`。最后合并的时候，因为 $ans1$ 和 $ans2$ 表示的是 $x$ 和 $y$ **向上**跳的答案，不能直接加，需要先 `swap(x.l,x.r)`，再返回 $ans1+ans2$。

另外，因为这道题是将边权下放到点权，所以要注意路径不包括 LCA，求答案时需要特判一下。

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ls x<<1
#define rs x<<1|1
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
#define ll long long
using namespace std;
const int N = 1e5+5;
int ans[N],f[N],hd[N],cnt,n,m;
struct ques{int u,v,w,id;}a[N],q[N];
bool cmp(ques x,ques y){return x.w > y.w;}
struct edge{int to,nex;}e[N << 1];
void add(int u,int v)
{e[++cnt] = {v,hd[u]};hd[u] = cnt;}
int fa[N],siz[N],d[N],son[N],top[N],rk[N],id[N],tim;
struct node
{
    int x,l,r;bool b;
    friend node operator +(node x,node y)
    {return {x.x+y.x-f[x.r]-f[y.l]+f[x.r+y.l],x.l+x.b*y.l,y.r+y.b*x.r,x.b&&y.b};}
}t[N << 2];
void modify(int x,int l,int r,int i)
{
    if(l == r){t[x] = {f[1],1,1,1};return ;}
    int mid = l+r>>1;
    i <= mid?modify(lson,i):modify(rson,i);
    t[x] = t[ls]+t[rs];
}
node query(int x,int l,int r,int L,int R)
{
    if(L <= l&&r <= R)return t[x];
    int mid = l+r>>1;node ans = {0,0,0,1};
    if(L <= mid)ans = query(lson,L,R);
    if(mid < R)ans = ans+query(rson,L,R);
    return ans;
}
void dfs1(int u,int f)
{
    fa[u] = f;d[u] = d[f]+1;siz[u] = 1;
    for(int i = hd[u],v;i;i = e[i].nex)
    {
        if((v = e[i].to) == f)continue;
        dfs1(v,u);siz[u] += siz[v];
        if(siz[son[u]] < siz[v])son[u] = v;
    }
}
void dfs2(int u,int tp)
{
	id[u] = ++tim;rk[tim] = u;top[u] = tp;
	if(son[u])dfs2(son[u],tp);
	for(int i = hd[u],v;i;i = e[i].nex)
		if((v = e[i].to) != fa[u]&&v != son[u])dfs2(v,v);
}
node queryRange(int x,int y)
{
    node ans1 = {0,0,0,1},ans2 = {0,0,0,1};
    while(top[x] != top[y])
    {
        if(d[top[x]] < d[top[y]])swap(x,y),swap(ans1,ans2);
        ans1 = query(1,1,n,id[top[x]],id[x])+ans1;
        x = fa[top[x]];
    }
    if(d[x] > d[y])swap(x,y),swap(ans1,ans2);
    if(id[x] != id[y])ans2 = query(1,1,n,id[x]+1,id[y])+ans2;
    return swap(ans1.l,ans1.r),ans1+ans2;
}
inline int rd()
{
    char c;int f = 1;
    while(!isdigit(c = getchar()))if(c=='-')f = -1;
    int x = c-'0';
    while(isdigit(c = getchar()))x = x*10+(c^48);
    return x*f;
}
int main()
{
    n = rd();m = rd();
    for(int i = 1;i < n;i++)f[i] = rd();
    for(int i = 1;i < n;i++)
    {
        int u = rd(),v = rd(),w = rd();
        a[i] = {u,v,w,0};add(u,v);add(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    for(int i = 1;i <= n;i++)
        if(d[a[i].u] > d[a[i].v])swap(a[i].u,a[i].v);
    for(int i = 1;i <= m;i++)q[i] = {rd(),rd(),rd(),i};
    sort(a+1,a+n+1,cmp);sort(q+1,q+m+1,cmp);
    for(int i = 1,j = 1;i <= m;i++)
    {
        for(;j < n&&a[j].w >= q[i].w;j++)
            modify(1,1,n,id[a[j].v]);
        ans[q[i].id] = queryRange(q[i].u,q[i].v).x;
    }
    for(int i = 1;i <= m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Luciylove (赞：0)

小清新 *3100。

点边转化，转化为挂在深度大的儿子上。

考虑离线扫描线，然后可以转化为路径上数 0/1 段。然后线段树维护前缀 $1$ 的长度、后缀的 $1$ 的长度、这一个区间的贡献。

实现建议使用重载运算符。

然后就是计算两端拼起来就好了再减去之前的贡献。

可以利用类似 CF484E 的方法，可持久化线段树做到强制在线。

有一些需要注意的细节。比如说要注意从 $x \to y$ 这条路径上 $x \to LCA$ 的这一段，要翻转所维护的东西。


代码比较可读。

[代码。](https://codeforces.com/contest/536/submission/229815298)



---

## 作者：World_Creater (赞：0)

非常无脑的树剖题。

考虑直接给定 $0/1$ 边权怎么做，直接树剖套线段树，线段树上每个节点维护区间前后缀 $1$ 的个数和当前答案，合并信息的什么都是简单的。

有了题目中的限制怎么做，直接将所有询问全部离线下来，然后连着边权一起按大小排序，用类似扫描线的思想实时更新当扫到每个询问时，当前边权的 $0/1$ 状况。

然后就做完了，时间复杂度 $\mathcal{O}(q\log ^2n)$。

如果题目要求强制在线的话，把扫描线线段树的过程换成可持久化线段树是一样的，除了空间变成 $\mathcal{O}(n\log n)$。

难度 $3100$，有至少 $2000$ 都在码代码的难度上。

[码](https://codeforces.com/contest/536/submission/212520543)。

---

## 作者：Daidly (赞：0)

分析询问的性质：给出 $(u,v,l)$，$u\to v$ 路径上边权 $w_i\ge l$ 记为 $1$，否则记为 $0$，求连续 $1$ 段的权值之和。

首先将边权下放到点权。

发现不好差分优化 $u,v$，那我们从 $l$ 下手。由于 $l$ 标记的是一段后缀，这是可以扫的。离线询问，将 $w_i$ 和 $l$ 都递减排序，扫描 $l$ 这一维度，每次只需要将 $w_i\ge l$ 的 $w_i$ 在树上的权值从 $0$ 修改为 $1$，然后树剖线段树维护维护链权值即可。

细节可见代码（如果 WA 很大可能是树剖向上跳写错了）。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e5+5;
int n,m,head[N],cnt,f[N];
int fa[N],dfn[N],cnt1,dep[N],top[N],hson[N],siz[N],w[N];
struct G{
	int next,to,w;
}e[N<<1];

void add(int from,int to,int w){
	e[++cnt]=(G){head[from],to,w};
	head[from]=cnt;
} 

struct SGT{
	struct node{
		int val,pre,suf,len;
	}t[N<<2];
	
	node R(node x){
		swap(x.pre,x.suf);
		return x;
	}
	
	node push_up(node ls,node rs){
		node ans;
		ans.val=ls.val+rs.val-f[ls.suf]-f[rs.pre]+f[ls.suf+rs.pre];
		ans.pre=ls.pre+(ls.pre==ls.len?rs.pre:0);
		ans.suf=rs.suf+(rs.suf==rs.len?ls.suf:0);
		ans.len=ls.len+rs.len;
		return ans;
	}
	
	void build(int l,int r,int p){
		if(l==r){t[p].len=1;return;}
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		t[p]=push_up(t[p<<1],t[p<<1|1]);
	}
	
	void modify(int l,int r,int pos,int p){
		if(l==r){
			t[p].val=f[1],t[p].pre=t[p].suf=1;return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)modify(l,mid,pos,p<<1);
		else modify(mid+1,r,pos,p<<1|1);
		t[p]=push_up(t[p<<1],t[p<<1|1]);
	}
	
	node qry(int l,int r,int lq,int rq,int p){
		if(lq>rq||lq>r||rq<l)return (node){0,0,0,0};
		if(lq<=l&&r<=rq)return t[p];
		int mid=(l+r)>>1;node ans=(node){0,0,0,0};
		if(lq<=mid)ans=push_up(ans,qry(l,mid,lq,rq,p<<1));
		if(mid<rq)ans=push_up(ans,qry(mid+1,r,lq,rq,p<<1|1));
		return ans;
	}
}T;

struct HLD{
	void dfs1(int x){
		siz[x]=1,dep[x]=dep[fa[x]]+1;
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(y==fa[x])continue;
			fa[y]=x,w[y]=e[i].w,dfs1(y),siz[x]+=siz[y];
			if(siz[y]>siz[hson[x]])hson[x]=y;
		}
	}
	
	void dfs2(int x,int topx){
		top[x]=topx,dfn[x]=++cnt1;
		if(!hson[x])return;
		dfs2(hson[x],topx);
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(y==fa[x]||y==hson[x])continue;
			dfs2(y,y);
		}
	}
	
	int qry(int x,int y){
		SGT::node ansx=(SGT::node){0,0,0,0},ansy=(SGT::node){0,0,0,0};
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]){
				ansy=T.push_up(T.qry(1,n,dfn[top[y]],dfn[y],1),ansy);
				y=fa[top[y]];
			}else{
				ansx=T.push_up(ansx,T.R(T.qry(1,n,dfn[top[x]],dfn[x],1)));
				x=fa[top[x]];
			}
		}
		if(dep[x]>dep[y])return T.push_up(T.push_up(ansx,T.R(T.qry(1,n,dfn[y]+1,dfn[x],1))),ansy).val;
		return T.push_up(T.push_up(ansx,T.qry(1,n,dfn[x]+1,dfn[y],1)),ansy).val;
	}
}L;

struct NODE{
	int val,x;
	bool operator<(const NODE &P)const{return val>P.val;}
}p[N];
struct Q{
	int u,v,l,id;
	bool operator<(const Q &P)const{return l>P.l;}
}que[N];
int ans[N],num;

int main(){
	n=read(),m=read();
	for(int i=1;i<n;++i)f[i]=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	L.dfs1(1),L.dfs2(1,1),T.build(1,n,1);
	for(int i=2;i<=n;++i)p[i-1]=(NODE){w[i],i};
	sort(p+1,p+n);
	for(int i=1;i<=m;++i)que[i].u=read(),que[i].v=read(),que[i].l=read(),que[i].id=i;
	sort(que+1,que+m+1);
	for(int i=1,t=1;i<=m;++i){
		while(t<n&&p[t].val>=que[i].l){
			T.modify(1,n,dfn[p[t].x],1);++t;
		}
		ans[que[i].id]=L.qry(que[i].u,que[i].v);
	}
	for(int i=1;i<=m;++i)print(ans[i]),puts("");
	return 0;
}
```

---

