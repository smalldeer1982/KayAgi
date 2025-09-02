# Groceries in Meteor Town

## 题目描述

Mihai lives in a town where meteor storms are a common problem. It's annoying, because Mihai has to buy groceries sometimes, and getting hit by meteors isn't fun. Therefore, we ask you to find the most dangerous way to buy groceries so that we can trick him to go there.

The town has $ n $ buildings numbered from $ 1 $ to $ n $ . Some buildings have roads between them, and there is exactly $ 1 $ simple path from any building to any other building. Each road has a certain meteor danger level. The buildings all have grocery stores, but Mihai only cares about the open ones, of course. Initially, all the grocery stores are closed.

You are given $ q $ queries of three types:

1. Given the integers $ l $ and $ r $ , the buildings numbered from $ l $ to $ r $ open their grocery stores (nothing happens to buildings in the range that already have an open grocery store).
2. Given the integers $ l $ and $ r $ , the buildings numbered from $ l $ to $ r $ close their grocery stores (nothing happens to buildings in the range that didn't have an open grocery store).
3. Given the integer $ x $ , find the maximum meteor danger level on the simple path from $ x $ to any open grocery store, or $ -1 $ if there is no edge on any simple path to an open store.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1628E/0800df34ef5a0b5bca352d9e8d746a52ec67cd12.png)

This is an illustration of the town given in the sample input.

In the first query, there are no open stores, so obviously there are no edges on the simple path from $ 1 $ to any open store, so the answer is $ -1 $ .

After the second and third queries, the set of open stores is $ \{1\} $ . The simple path from $ 1 $ to $ 1 $ has no edges, so the answer for the $ 3 $ rd query is $ -1 $ .

After the fourth query, there are no open stores.

After the fifth and sixth queries, the set of open stores is $ \{5, 6\} $ . In the sixth query, there are two paths from $ x_j = 4 $ to some open grocery store: $ 4 $ to $ 5 $ and $ 4 $ to $ 6 $ . The biggest meteor danger is found on the edge from $ 4 $ to $ 6 $ , so the answer for the $ 6 $ th query is $ 4 $ . This path is marked with red in the illustration.

After the rest of the queries, the set of open stores is $ \{5\} $ . In the eighth query, the only path from $ x_j = 4 $ to an open store is from $ 4 $ to $ 5 $ , and the maximum weight on that path is $ 3 $ . This path is marked with green in the illustration.

In the ninth query, the only path from $ x_j = 1 $ to an open store is from $ 1 $ to $ 5 $ , and the maximum weight on that path is $ 5 $ . This path is marked with blue in the illustration.

## 样例 #1

### 输入

```
6 9
1 3 1
2 3 2
4 5 3
4 6 4
3 4 5
3 1
1 1 1
3 1
2 1 1
1 5 6
3 4
2 6 6
3 4
3 1```

### 输出

```
-1
-1
4
3
5```

# 题解

## 作者：MatrixCascade (赞：27)

很早之前就口胡了的题，教练布置了所以写一下。

首先看到到两个点之间的简单路径中经过的最长的边，就去想是否可以用 Kruskal 重构树转化成两个点的 lca 的权值。

于是查询操作就转化成了重构树上， $x$ 点与所有白点的 lca 的权值。

再用[这题](https://www.luogu.com.cn/problem/CF1062E)的经典的套路，一个点集的 lca 为这个点集中 $dfn$ 最大点和 $dfn$ 最小点的 lca，这样修改操作就可以直接用线段树去维护区间最大最小 $dfn$ 了。然后就做完了，复杂度 $(n+q)\log n$。

~~严重虚高题~~

---

## 作者：MarchKid_Joe (赞：13)

# [CF1628E Groceries in Meteor Town](https://www.luogu.com.cn/problem/CF1628E)

## 算法

- 线段树区间最值
- 多点最近公共祖先
- Kruskal 重构树-最小生成树

## 题意

其实题意翻译很清楚了。

1. 区间节点 $[l,r]$ 染白色。

2. 区间节点 $[l,r]$ 染黑色。

3. 查询当前点与所有**白点**的简单路径边权最大值，不存在输出 $-1$。

## 思路

### 简单路径边权最大值

对于这种简单路径边权最大值：参照 Kruskal 重构树的性质：原图中两点间所有简单路径最大边权的最小值=Kruskal 重构树上两点 LCA 的权值。

对于树来说，简单路径就一条，所以所有简单路径的最大边权的最小值就是这条简单路径的最大边权。所以我们构建 Kruskal **重构树-最小生成树**通过查询**多点最近公共祖先**维护路径边权**最大值**。

并查集维护建 Kruskal 重构树。

```cpp
namespace KruskalTree//Kruskal 重构树
{
    struct EDGE
    {
        int u, v, w;
        EDGE(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w){}
        friend bool operator<(const EDGE &A, const EDGE &B){return A.w < B.w;}
    };
    EDGE E[N];
    int pcnt;
    int fa[N << 1];
    int val[N << 1];
    void add(int u, int v, int w, int i){E[i] = EDGE(u, v, w);}//加边
    int get(int x){return x != fa[x] ? fa[x] = get(fa[x]) : x;}//并查集
    void build()
    {
        for (int i = 1; i <= (n << 1); i++) fa[i] = i;//并查集初始化
        sort(E + 1, E + n);//边权从小到大排序
        for (int i = 1; i < n; i++)
        {
            int x = get(E[i].u);
            int y = get(E[i].v);
            fa[x] = fa[y] = n + (++pcnt);//因为是树，所以合并前x,y一定不在同一集合，直接合并
            chain::add(n + pcnt, x);//chain 为链式前向星
            chain::add(n + pcnt, y);//chain 为链式前向星
            val[n + pcnt] = E[i].w;//边权变为点权
        }
    }
}
signed main()
{
    for (int i = 1, u, v, w; i < n; i++)
    {
        read(u, v, w);
        KruskalTree::add(u, v, w, i);//加边
    }
    KruskalTree::build();//建树
}
```

### 多点最近公共祖先

如何查询一个**点集**的最近公共祖先？

查询当前点集 dfs 序最小的节点和 dfs 序最大的节点的最近公共祖先就是这个点集所有结点的最近公共祖先。

两点间的最近公共祖先用倍增，树剖就可以了。

其实就是倍增法求最近公共祖先。~~最近公共祖先作为普及的难度，代码应该没什么必要。~~

```cpp
namespace LCA//倍增 LCA，顺便求 dfs 序。
{
    int dfncnt;
    int dfn[N << 1];
    int idfn[N << 1];
    int dep[N << 1];
    int lg[N << 1];
    int f[N << 1][21];
    void dfs(int u, int fa)
    {
        dfn[u] = ++dfncnt;//点对应的 dfs 序。
        idfn[dfncnt] = u;//dfs 序对应的点。
        f[u][0] = fa;
        dep[u] = dep[fa] + 1;//更新深度。
        for (int i = 1; i <= lg[dep[u]]; i++)//更新祖先。
            f[u][i] = f[f[u][i - 1]][i - 1];
        for (int i = head[u]; i; i = e[i].nxt)
            if (!dfn[e[i].v])
                dfs(e[i].v, u);
    }
    int lca(int x, int y)//倍增 LCA。
    {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = lg[dep[x]]; i >= 0; i--)
            if (dep[f[x][i]] >= dep[y])
                x = f[x][i];
        if (x == y)
            return x;
        for (int i = lg[dep[x]]; i >= 0; i--)
        {
            if (f[x][i] != f[y][i])
            {
                x = f[x][i];
                y = f[y][i];
            }
        }
        return f[x][0];
    }
    void initival()
    {
        for (int i = 1; i <= (n << 1); i++)//预处理 log2。
            lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == (i >> 1));
        dfs(n + KruskalTree::pcnt, 0);//最好把最后一个加入的点作为根。
    }
}
struct type// 二元组，存最大值最小值，相当于pair。
{
    int maxn, minn;
    void update(int x){maxn = max(maxn, x), minn = min(minn, x);}
    type(int maxn = -INF, int minn = +INF) : maxn(maxn), minn(minn){}
};
signed main()// opt=3 时的查询操作。
{
    LCA::initival();//初始化。
    /*=====================*/
    ans = -1;
    read(x);
    type Q = query();//查询区间白点最大和最小 dfs 序，用数据结构维护。
    Q.update(dfn[x]);//当前节点也要更新 dfs 序最大值和最小值。
    if (Q.maxn != Q.minn)
    {
        y = lca(idfn[Q.maxn], idfn[Q.minn]);
        if (x != y) ans = val[y];
    }
    write(ans, '\n');
}
```

### 维护区间所有白点最大和最小的 dfs 序

数据结构**线段树**。

1. 维护的变量

    $inf$：最大值为 $-\infty$，最小值为 $+\infty$。

    $all$：区间所有节点最大值和最小值。
    
    $val$：区间所有白点最大值和最小值。
    
    $tag$：懒标记。

2. 建树

    用两个子区间的 $all$ 更新当前区间的 $all$。当前区间的 $val$ 不变，仍然为 $inf$，因为初始时全部为黑点。**此后的所有修改操作，$all$ 均不变**，所以说，$all$ 的作用就是用于快速恢复当前区间的贡献。

3. 更新

    $opt=1$：更新当前区间为白点，将 $val$ 改为 $all$，并给当前区间打上标记 $tag=1$。
    
    $opt=2$：更新当前区间为黑点，将 $val$ 改为 $inf$，并给当前区间打上标记 $tag=2$。

    用两个子区间的 $val$ 更新当前区间的 $val$。

4. 下传懒标记

    $tag=1$：将两个子区间的 $val$ 更新为 $all$，恢复贡献。
    
    $tag=2$：将两个子区间的 $val$ 更新为 $inf$，删除贡献。
    
    最后清空当前区间的 $tag=0$。
    
5. 查询

    直接返回根节点的 $val$ 就是所有白点 dfs 序的最大值和最小值。

```cpp
/*区分注释里的节点（黑+白）和白点 qwq*/
namespace SegmentTree
{
    #define lc(i) i << 1
    #define rc(i) i << 1 | 1
    const int INF = 1 << 30;
    struct type// 二元组，相当于pair。
    {
        int maxn, minn;
        void update(int x){maxn = max(maxn, x), minn = min(minn, x);}
        type(int maxn = -INF, int minn = +INF) : maxn(maxn), minn(minn){}
    };
    struct node
    {
        int l, r, tag;//tag 是当前区间的黑，白性质懒标记：tag=1 白点；tag=2 黑点；tag=0 没有标记。
        type val, all;//all 为当前区间所有节点的最大值和最小值，val 为所有白点的最大值和最小值。
        node(int l = 0, int r = 0, int tag = 0) : l(l), r(r), tag(tag){}
    };
    node tr[N << 4];
    void up(node &i, int tag)
    {
        i.tag = tag;
        if (tag == 1) i.val = i.all;//白点就恢复贡献。
        if (tag == 2) i.val = type(-INF, +INF);//黑点就清除贡献。
    }
    type change(const type &A, const type &B)//最大值和最小值贡献合并。
    {
        return type(max(A.maxn, B.maxn), min(A.minn, B.minn));
    }
    void push_down(int i)//下传标记。
    {
        if (tr[i].tag)
        {
            up(tr[lc(i)], tr[i].tag);
            up(tr[rc(i)], tr[i].tag);
            tr[i].tag = 0;
        }
    }
    void build(int l, int r, int i = 1)//建树。
    {
        tr[i] = node(l, r);
        if (l == r)
            return tr[i].all.update(LCA::dfn[l]);//权值更新为 dfs 序。
        int mid = (l + r) >> 1;
        build(l, mid, lc(i));
        build(mid + 1, r, rc(i));
        tr[i].all = change(tr[lc(i)].all, tr[rc(i)].all);//记得push_up所有节点的贡献，所有节点节点节点。
    }
    void update(int l, int r, int tag, int i = 1)
    {
        if (tr[i].l > r || tr[i].r < l)
            return void();
        if (tr[i].l >= l && tr[i].r <= r)
            return up(tr[i], tag);
        push_down(i);
        update(l, r, tag, lc(i));
        update(l, r, tag, rc(i));
        tr[i].val = change(tr[lc(i)].val, tr[rc(i)].val);//记得push_up所有白点的贡献，所有白点白点白点。
    }
    type query(){return tr[1].val;}//直接返回根节点。
}
signed main()// opt=1|2 时的修改操作。
{
    SegmentTree::build(1, n);//只用建 [1,n]，新加入的点不可能被修改。
    /*=====================*/
    if (opt < 3)
    	update(l, r, opt);
    else
    	query();
}
```

## 流程

- 构建 Kruskal 重构树-**最小**生成树。
- 通过 dfs 对 Kruskal 重构树-最小生成树求所有点 dfs 序。
- 对点 $[1,n]$ 的 dfs 序构建线段树维护区间**白点**最大值和最小值。对于黑白点，打个 $tag$ 就行了。
- 求当前**所有白点和当前节点**的 dfs 序最大的点与 dfs 序最小的点的最近公共祖先，就是当前点与所有白点的最近公共祖先，输出对应的权值即可。

## Code

完整代码 $5\operatorname{KB}$ 太长了，扔大批量代码会显得太臃肿，于是就扔了个链接：若有需要再 click [here](https://www.luogu.com.cn/paste/115fjz3l)。

## 总结

Kruskal 重构树：[My luogu Blog:KruskalTree](https://www.luogu.com.cn/blog/MarchKidJoe/zui-xiao-sheng-cheng-shu)

Kruskal 重构树：[My WordPress Blog:KruskalTree](http://marchkidjoe.mygamesonline.org/minimum_spanning_tree/)

代码量比较大的题，只是考的算法多而已，就像 [CF487E Tourists](https://www.luogu.com.cn/problem/CF487E)。

---

## 作者：寒鸽儿 (赞：9)

#### 题意
给定一个 $n$ 点的带权无向树，初始时点标记为 $0$ ，维护：
操作：  
1. 将标号区间 $[l, r]$ 的点标记置 $1$ 。  
2. 将标号区间 $[l, r]$ 的点标记置 $0$ 。  

询问（ $q$ 次）：  
1. 点 $x$ 到标记为 $1$ 的点的最大瓶颈距离（要求是简单路径，不包括 $x$ ，不存在输出 $-1$ ）。  

$1 \leq n \leq 3 \times 10^5$ ，边权 $1 \leq w_i \leq 10^9$ 。

#### 题解
瓶颈距离啥的会想到 kruskal 重构树。  
最远肯定绕路到 kruskal 重构树权值最大的地方，即所有标记为 $1$ 的点的 lca 与 $x$ 的 lca。要注意特判只有 $x$ 一个标记为 $1$ 的点的情况。  
多点 lca 的结论是 dfs 序最大的点和最小的点求一次 lca，因此需要维护标记为 $1$ 的点集的最大和最小的 dfs 序。用线段树来维护这个值，需要预处理所有线段树结点对应区间的 dfs 序的最大最小值以方便区间修改打 tag 时对结点进行赋值（计算变成了调用预处理的值）。  


#### code
```cpp
struct edge { int u, v, w; } e[maxn];
int par[maxn << 1];
inline int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
int ch[2][maxn << 1], wt[maxn << 1], fa[30][maxn << 1], dfn[maxn << 1], idfn[maxn << 1], dep[maxn << 1], dfs_clock, tot;

void krt_build(int n) {
    sort(e + 1, e + n, [&](edge &x, edge &y) { return x.w < y.w; });
    rep(i,1,n<<1) par[i] = i;
    tot = n;
    rep(i,1,n - 1) {
        int u = find(e[i].u), v = find(e[i].v), w = e[i].w;
        par[u] = par[v] = fa[0][u] = fa[0][v] = ++ tot;
        ch[0][tot] = u, ch[1][tot] = v;
        wt[tot] = w;
    }
}

void dfs(int cur) {
    dfn[cur] = ++ dfs_clock, idfn[dfs_clock] = cur, dep[cur] = dep[fa[0][cur]] + 1;
    rep(i,1,25) fa[i][cur] = fa[i - 1][fa[i - 1][cur]];
    rep(i,0,1) if(ch[i][cur]) dfs(ch[i][cur]);
}

int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    per(i,25,0) if(dep[fa[i][x]] >= dep[y]) x = fa[i][x];
    if(x == y) return x;
    per(i,25,0) if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

struct segTree {
    int mx[maxn << 2], mn[maxn << 2], smx[maxn << 2], smn[maxn << 2], tag[maxn << 2];
    void as(int p, int v) {
        v ? (mx[p] = smx[p], mn[p] = smn[p]) : (mx[p] = 0, mn[p] = inf);
    }
    void spread(int p) {
        register int ls = p << 1, rs = ls | 1;
        as(ls, tag[p]), as(rs, tag[p]), tag[ls] = tag[rs] = tag[p], tag[p] = -1;
    }
    void build(int p, int lp, int rp) {
        tag[p] = -1; mx[p] = 0, mn[p] = inf;
        if(lp == rp) { smx[p] = smn[p] = dfn[lp]; return ; }
        register int mid = (lp + rp) >> 1, ls = p << 1, rs = ls | 1;
        build(ls, lp, mid), build(rs, mid + 1, rp);
        smx[p] = max(smx[ls], smx[rs]), smn[p] = min(smn[ls], smn[rs]);

    }
    void assign(int p, int lp, int rp, int l, int r, int v) {
        if(l <= lp && rp <= r) {
            v ? (mn[p] = smn[p], mx[p] = smx[p]) : (mn[p] = inf, mx[p] = 0);
            tag[p] = v;
            return ;
        }
        register int mid = (lp + rp) >> 1, ls = p << 1, rs = ls | 1;
        if(~tag[p]) spread(p);
        if(l <= mid) assign(ls, lp, mid, l, r, v);
        if(r > mid) assign(rs, mid + 1, rp, l, r, v);
        mx[p] = max(mx[ls], mx[rs]), mn[p] = min(mn[ls], mn[rs]);
    }
    void qry(int &v1, int &v2) { v1 = mn[1], v2 = mx[1]; }
} s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q, u, v, w;
    cin >> n >> q;
    rep(i,1,n-1) {
        cin >> u >> v >> w;
        e[i] = {u, v, w};
    }
    krt_build(n);
    dfs(tot);
    s.build(1, 1, n);
    int t, l, r, x;
    rep(qr,1,q) {
        cin >> t;
        if(t == 1 || t == 2) {
            cin >> l >> r;
            s.assign(1, 1, n, l, r, t == 1 ? 1 : 0);
        } else {
            cin >> x;
            int mn, mx; s.qry(mn, mx);
            if(mn == inf || (mn == dfn[x] && mx == mn)) cout << -1 << endl;
            else cout << wt[lca(idfn[mn], lca(idfn[mx], x))] << endl;
        }
    }
    return 0;
}
```

---

## 作者：hegm (赞：5)

### [传送门](https://www.luogu.com.cn/problem/CF1628E)

这道题需要会区间 $\text{LCA}$。

可以做一下这道题：[Company](https://www.luogu.com.cn/problem/CF1062E)||
[我的题解](https://www.luogu.com.cn/blog/hegm/solution-cf1062e)

考虑建树，由于两点间路径唯一，所以需要查询两点间的最大可能权值，即为两点间的最小瓶颈路，建立最小 $\text{Kruskal}$ 重构树。

因为点权从下到上为升序，所以我们的目的是让给定的 $x$ 点和所有白点的 $\text{LCA}$ 深度最小。

使用上面哪道题的思路，多个数 $\text{LCA}$ 为 $dfn_{max}$ 和 $dfn_{min}$ 的 $\text{LCA}$。

那么 $ans=\max(\text{lca}(x,dfn_{max}) , \text{lca}(x,dfn_{min}))$。（这里的 $dfn_{max,min}$ 是指 $dfn$ 最大最小的白点）。

那么 $3$ 操作解决了。

如何解决 $1,2$ 捏？

建出一颗线段树，存储所有点是黑点，还是白点， $\text{push\_up}$ 的时候统计出所有白点的 $dfn_{min,max}$。

做完了 ![](//啧.tk/cy) 

放下代码


------------


### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define inf 1000000009
#define ls (now<<1)
#define rs (now<<1|1)
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,f[N],cnt,tot,dfn[N],fa[N][20],t[N],dep[N],awa,lx,rx,head[N],val[N],q;
struct edge
{
	int u,v,w;
}e[N];
bool cmp(edge a,edge b){return a.w<b.w;}
int find(int now)
{
	if(now==f[now])return now;
	return f[now]=find(f[now]);
}
struct fig
{
	int from,to,next;
}k[N];
struct tree
{
	int l,r,mx,mn,tag;
	int rx,rn;//全体的dfn 
	bool vis;//0白，1黑 
}tr[N*4];
void add(int from,int to)
{
	k[++tot].from=from;
	k[tot].to=to;
	k[tot].next=head[from];
	head[from]=tot;
}
void dfs(int now,int f)
{
	dfn[now]=++awa;
	t[awa]=now;
	dep[now]=dep[f]+1;
	fa[now][0]=f;
	for(int i=1;i<=19;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
	for(int i=head[now];i;i=k[i].next)dfs(k[i].to,now);
}
void up(int now)
{
	tr[now].vis=1;
	if(!tr[ls].vis&&!tr[rs].vis)
	{
		tr[now].mx=max(tr[ls].mx,tr[rs].mx);
		tr[now].mn=min(tr[ls].mn,tr[rs].mn);
		tr[now].vis=0;
	}
	else if(!tr[ls].vis)
	{
		tr[now].mx=tr[ls].mx;
		tr[now].mn=tr[ls].mn;
		tr[now].vis=0;
	}
	else if(!tr[rs].vis)
	{
		tr[now].mx=tr[rs].mx;
		tr[now].mn=tr[rs].mn;
		tr[now].vis=0;
	}
}
void down(int now)
{
	if(tr[now].tag==-1)return ;
	if(tr[now].tag==1)
	{
		tr[ls].tag=tr[rs].tag=1;
		tr[ls].vis=tr[rs].vis=1;
		tr[ls].mx=tr[rs].mn=0;
		tr[ls].mn=tr[rs].mn=inf;
		tr[now].tag=-1;
	}
	if(tr[now].tag==0)
	{
		tr[ls].vis=tr[rs].vis=0;
		tr[ls].tag=tr[rs].tag=0;
		tr[ls].mx=tr[ls].rx;tr[ls].mn=tr[ls].rn;
		tr[rs].mx=tr[rs].rx;tr[rs].mn=tr[rs].rn; 
		tr[now].tag=-1;
	}
}
void build(int now,int l,int r)
{
	tr[now].l=l;tr[now].r=r;
	tr[now].vis=1;tr[now].tag=-1;tr[now].mn=inf;
	if(l==r)
	{
		tr[now].rn=dfn[l];
		tr[now].rx=dfn[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	tr[now].rx=max(tr[ls].rx,tr[rs].rx);
	tr[now].rn=min(tr[ls].rn,tr[rs].rn);
}
void midy(int now,int cl,int cr,int x)
{
	if(tr[now].l>=cl&&tr[now].r<=cr)
	{
		tr[now].tag=x;
		tr[now].vis=x;
		if(x==1)
		{
			tr[now].mn=inf;
			tr[now].mx=0;
		}
		if(x==0)
		{
			tr[now].mx=tr[now].rx;
			tr[now].mn=tr[now].rn;
		}
		return ; 
	}
	down(now);
	int mid=(tr[now].l+tr[now].r)>>1;
	if(mid>=cl&&tr[ls].tag!=x)midy(ls,cl,cr,x);
	if(mid<cr&&tr[rs].tag!=x)midy(rs,cl,cr,x);
	up(now);
}
void que(int now,int cl,int cr)//记得初始化lx 
{
	if(now==1)lx=inf,rx=0;
	if(tr[now].l>=cl&&tr[now].r<=cr)
	{
		if(!tr[now].vis)
		{
			lx=min(lx,tr[now].mn);
			rx=max(rx,tr[now].mx);
		}
		return ;
	}
	down(now);
	int mid=(tr[now].l+tr[now].r)>>1;
	if(mid>=cl)que(ls,cl,cr);
	if(mid<cr)que(rs,cl,cr);
	up(now);
}
int lca(int a,int b)
{
	if(dep[a]<dep[b])swap(a,b);
	for(int i=19;i>=0;i--)if(dep[fa[a][i]]>=dep[b])a=fa[a][i];
	if(a==b)return val[a];
	for(int i=19;i>=0;i--)if(fa[a][i]!=fa[b][i])a=fa[a][i],b=fa[b][i];
	return val[fa[a][0]]; 
}
signed main()
{
	n=read();q=read();
	for(int i=1;i<n;i++)
	{
		e[i].u=read();
		e[i].v=read();
		e[i].w=read();
	}
	sort(e+1,e+n,cmp);cnt=n;
	for(int i=1;i<=2*n;i++)f[i]=i;
	for(int i=1;i<n;i++)
	{
		int u=find(e[i].u),v=find(e[i].v);
		f[u]=f[v]=++cnt;
		val[cnt]=e[i].w;
		add(cnt,u);add(cnt,v);
	}
	dfs(cnt,0);
	build(1,1,n);
	int op,l,r,x;
	while(q--)
	{
		op=read();
		if(op==3)
		{
			x=read();
			que(1,1,n);
			if(lx==rx&&t[lx]==x)cout<<-1<<"\n";
			else if(rx==0)cout<<-1<<"\n";
			else cout<<max(lca(x,t[rx]),lca(x,t[lx]))<<"\n";
			continue;
		}
		l=read();r=read();
		if(op==1)midy(1,l,r,0);
		else midy(1,l,r,1);
	}
	return 0;
}
```

---

## 作者：Demoe (赞：3)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1628E)

## $\text{Description}$

- 给定一棵树，每个点点权初始为 $0$，有如下操作 $q$ 次。
- 将序号在 $[l,r]$ 中的点点权改为 $0/1$。
- 询问 $x$ 到所有点权为 $1$ 的点的简单路径上最大边权。

## $\text{Solution}$

考虑 Kruskal 重构树性质：

>原图中两个点之间的所有简单路径上最大边权的最小值 = 最小生成树上两个点之间的简单路径上的最大值 = Kruskal 重构树上两点之间的 LCA 的权值。
>——OI WIKI

这是对于一般图而言，这里我们是树，两点之间有且仅有一条简单路径。

那么即树上两点之间简单路径的最大边权 = Kruskal 重构树上两点之间 LCA 权值。

我们所求的即询问给定的点与各个点权为 $1$ 的点在 Kruskal 重构树上 LCA 权值的最大值。

而我们由上面性质，又可得到点 $x$ 的简单路径上最大边权不超过 $val$  的所有点均在 Kruskal 重构树上的某一棵子树内。

那么我们所求就可转化为询问给定的点点与所有点权为 $1$ 的点在 Krus 重构树上的 LCA。

---

考虑如何求多点 LCA。

有结论：多点 LCA 为 DFS 序最小和最大两点的点 LCA。

考虑证明结论。

令 $\text{LCA(a,b)}$ 为 $a$ 和 $b$ 的 LCA。

设 DFS 序最小的点为 $a$，最大的点为 $b$。

对于中间的点 $c$。

$a$ 可能是 $c$ 的祖先，也可能在 $c$ 祖先的在 $c$ 所在子树左边的子树内。

$b$ 可能是 $c$ 的后代，也可能在 $c$ 祖先的在 $c$ 所在子树右边的子树内。

- 若 $a$ 是 $c$ 的祖先。

显然 $\text{LCA(c,b)}$ 和 $\text{LCA(c,a)}$ 都在 $\text{LCA(a,b)}$ 的子树内。

- 若 $a$ 在 $c$  祖先的在 $c$ 所在子树左边的子树内。

	- 若 $b$ 是 $c$ 的后代。
    
    $\text{LCA(c,b)=c}$，$\text{LCA(a,b)=LCA(a,c)}$ 为 $c$ 的祖先。
    
    - 若 $b$ 在 $c$ 祖先的在 $c$ 所在子树右边的子树内。
    
    $\text{LCA(a,b)=LCA(LCA(c,a),LCA(c,b))}$。（实际上 $\text{LCA(c,a)}$ 和 $\text{LCA(c,b)}$ 其中一个为另外一个的祖先或两个相同。）
    
    
    
故结论成立。

---

那么我们只需要动态维护点权为 $1$ 的点中 DFS 序最小的点和最大的点。

可以考虑用线段树维护。

时间复杂度 $O(n+q\log n)$。

~~然而我写的是 $O(n\alpha(n)+q\log n)$ 的因为我 Kruskal 重构树是拷一般图板子的。~~

## $\text{Code}$

```cpp
const int N=6e5+5;
int n,tot,hd[N],Q,f[N<<1][22],dep[N],dfn[N],rk[N],qwq;
struct edge{int t,nxt;}es[N<<1];
int fa[N],siz[N];
inline int found(int x){return fa[x]==x?x:fa[x]=found(fa[x]);}
inline void merge(int x,int y){
	int fx=found(x),fy=found(y);
	if(siz[fx]<siz[fy]) swap(fx,fy);
	fa[fy]=fx;siz[fx]+=siz[fy];siz[fy]=0;
}

int cnte,cnt,val[N<<1];
struct Edge{int u,v,w;}e[N<<1];
struct EDGE{int t,nxt;}E[N<<3];
inline void add(int x,int y,int z){es[++tot]=(edge){y,hd[x]};hd[x]=tot;e[tot]=(Edge){x,y,z};}
inline void Add(int x,int y){E[++cnte]=(EDGE){y,hd[x]};hd[x]=cnte;}
inline bool cmp(Edge x,Edge y){return x.w<y.w;}
inline void kruscal(){
	cnt=n;
	for(re i=1;i<=(n<<1);++i) fa[i]=i,siz[i]=1,hd[i]=0;
	sort(e+1,e+tot+1,cmp);
	for(re i=1;i<=tot;++i)
		if(found(e[i].u)^found(e[i].v)){
			val[++cnt]=e[i].w;
			Add(found(e[i].u),cnt);Add(cnt,found(e[i].u));Add(found(e[i].v),cnt);Add(cnt,found(e[i].v));
			fa[found(e[i].u)]=fa[found(e[i].v)]=cnt;
		}
}

// ---------- Kruskal ---------- //

inline void dfs(int x,int fa){
	f[x][0]=fa;dep[x]=dep[fa]+1;dfn[x]=++qwq;rk[qwq]=x;
	for(re i=hd[x];i;i=E[i].nxt)
		if(E[i].t^fa) dfs(E[i].t,x);
}

inline int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(re i=21;i>=0;--i)
		if(f[x][i]&&dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(re i=21;i>=0;--i)
		if(f[x][i]&&f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

struct SGT{
	#define xl (x<<1)
	#define xr (x<<1|1)
	#define mid ((l+r)>>1)
	const int INF=1e9;
	int mx[N<<2],mn[N<<2],Mx[N<<2],Mn[N<<2],tag[N<<2],fl[N<<2];
	inline void pushup(int x){mx[x]=max(mx[xl],mx[xr]);mn[x]=min(mn[xl],mn[xr]);}
	inline void pushdown(int x){if(fl[x]){tag[xl]=tag[xr]=tag[x];mx[xl]=(tag[xl]?Mx[xl]:0);mn[xl]=(tag[xl]?Mn[xl]:INF);mx[xr]=(tag[xr]?Mx[xr]:0);mn[xr]=(tag[xr]?Mn[xr]:INF);fl[xl]=fl[xr]=1;fl[x]=0;}}
	inline void build(int x,int l,int r){
		mx[x]=tag[x]=0;mn[x]=INF;
		if(l==r){Mx[x]=Mn[x]=dfn[l];return ;}
		build(xl,l,mid);build(xr,mid+1,r);
		Mx[x]=max(Mx[xl],Mx[xr]);Mn[x]=min(Mn[xl],Mn[xr]);
	}
	inline void modify(int x,int l,int r,int L,int R,int k){
		if(L<=l&&r<=R){
			tag[x]=k;fl[x]=1;mx[x]=(k?Mx[x]:0);mn[x]=(k?Mn[x]:INF);
			return ;
		}
		pushdown(x);
		if(mid>=L) modify(xl,l,mid,L,R,k);
		if(mid<R) modify(xr,mid+1,r,L,R,k);
		pushup(x);
	}
}T;

// ---------- SGT ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);rd(Q);
	for(re i=1;i<n;++i){int x,y,z;rd(x);rd(y);rd(z);add(x,y,z);add(y,x,z);}
	kruscal();dfs(cnt,0);
	for(re s=1;s<=21;++s)
		for(re i=1;i<=cnt;++i) f[i][s]=f[f[i][s-1]][s-1];
	T.build(1,1,cnt);
	for(re i=1;i<=Q;++i){
		int op,l,r;rd(op);
		if(op<=2) rd(l),rd(r),T.modify(1,1,cnt,l,r,(op-1)^1);
		else{
			rd(l);int st=T.mn[1],ed=T.mx[1];
			if(st==dfn[l]&&ed==dfn[l]||ed==0) puts("-1");
			else wr(val[LCA(LCA(rk[st],rk[ed]),l)]),puts("");
		}
	}
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：_Ponder_ (赞：2)

[Groceries in Meteor Town](https://www.luogu.com.cn/problem/CF1628E)

### 题目大意

维护一颗带权树，支持以下操作：

- 将 $[l,r]$ 内的点变为白色。

- 将 $[l,r]$ 内的点变为黑色。

- 查询点 $x$ 到任意一个白色节点的简单路径上的最大值。

### 思路分析

~~没事干了把以前的题拿出来写题解。~~

看到『简单路径上的最大值』的字样首先想到 Kruskal 重构树。

我们先把这颗树的 Kruskal 重构树建出来，那么 $x$ 到任意一个白色节点的简单路径上的最大值就等于 $x$ 和所有白色节点的 LCA 的权值。

也就是说，我们只需要支持查询所有的白点的 LCA 就行了。

---

有一个结论：**一堆点的 LCA 等于其中 dfs 序最小的点和 dfs 序最大的点的 LCA。**

证明是容易的：

dfs 序所对应的子树区间只存在包含关系，不存在相交关系。

考虑三个点 $a,b,c$ 的情况，不妨设 $\text{dfn}_a <\text{dfn}_b<\text{dfn}_c$，这三点的 LCA 对应的 dfs 序区间恰好包含 $a,b,c$ 对应的 dfs 序区间，又因为 $b$ 对应的 dfs 序区间位于 $a,c$ 中间，故只要包含了 $a,c$ 对应的区间就一定包含了 $b$。即 $\text{LCA}(a,b,c)=\text{LCA}(a,c)$。

更多点的情况类似。

--- 

那么我们只需要维护所有白色点的 dfs 序最值即最值所在位置就可以求出所有白点的 LCA，这可以用线段树简单实现。

具体的说，我们的线段树需要支持以下操作：

- 查询 dfs 序 最大 / 最小 的白点编号。

- 区间修改点的颜色。

这两个操作是容易做到的。

那么这题就做完了。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N = 600600;
#define inf 0x3f3f3f3f
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)

int n, m, op, in1, in2, in3, cnt, rt;
int val[N], fat[N], siz[N], dep[N], top[N], dfn[N], son[N], fa[N];

struct Edge{
    int u, v, w;
}e[N];

struct STn{
    int minn, minp;
    int maxn, maxp;
    int tag;
};
struct ST{
    STn a[N << 2], b[N << 2];
    STn merge(STn p, STn a, STn b){
        p.minn = min(a.minn, b.minn);
        p.maxn = max(a.maxn, b.maxn);
        p.minp = (p.minn == a.minn ? a.minp : b.minp);
        p.maxp = (p.maxn == a.maxn ? a.maxp : b.maxp);
        return p;
    }
    void build(int p, int l, int r){
        if (l == r) {
            a[p].minn = a[p].maxn = dfn[l];
            a[p].minp = a[p].maxp = l;
            b[p] = a[p];
            return ;
        }
        build(ls, l, mid); build(rs, mid + 1, r);
        a[p] = merge(a[p], a[ls], a[rs]);
        b[p] = a[p];
    }
    void change_t(int p, int k){
        if (k == 0) a[p] = b[p];
        else a[p] = STn{inf, inf, -inf, -inf, 1};
    }
    void push_down(int p){
        if (a[p].tag == -1) return ;
        change_t(ls, a[p].tag);
        change_t(rs, a[p].tag);
        a[p].tag = -1;
    }
    void change(int p, int l, int r, int x, int y, int k){
        if (x <= l && r <= y) return change_t(p, k);
        push_down(p);
        if (x <= mid) change(ls, l, mid, x, y, k);
        if (y > mid) change(rs, mid + 1, r, x, y, k);
        a[p] = merge(a[p], a[ls], a[rs]);
    }
}tree;

vector <int> to[N];

int find(int x){
    return fat[x] == x ? x : fat[x] = find(fat[x]); 
}

void dfs_1(int s, int gr){
    fa[s] = gr; siz[s] = 1;
    dep[s] = dep[gr] + 1;
    for (auto v : to[s]) {
        dfs_1(v, s);
        siz[s] += siz[v];
        if (siz[son[s]] < siz[v]) son[s] = v;
    }
}

void dfs_2(int s, int tp){
    top[s] = tp; dfn[s] = ++ cnt;
    if (!son[s]) return ;
    dfs_2(son[s], tp);
    for (auto v : to[s])    
        if (v != fa[s] && v != son[s]) dfs_2(v, v);
}

int lca(int x, int y){
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

int main(){
    scanf("%d %d", &n, &m); rt = 2 * n - 1;
    for (int i = 1; i <= 2 * n; i ++) fat[i] = i;
    for (int i = 1; i < n; i ++) {
        scanf("%d %d %d", &in1, &in2, &in3);
        e[i] = Edge{in1, in2, in3};
    }
    sort(e + 1, e + n, [](Edge a, Edge b){return a.w < b.w;});
    for (int i = 1; i < n; i ++) {
        to[i + n].push_back(find(e[i].u));
        to[i + n].push_back(find(e[i].v));
        val[i + n] = e[i].w;
        fat[find(e[i].u)] = fat[find(e[i].v)] = find(i + n);
    }
    dfs_1(rt, 0); dfs_2(rt, rt);
    tree.build(1, 1, rt);
    tree.change_t(1, 1);
    while (m --) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &in1, &in2);
            tree.change(1, 1, rt, in1, in2, 0);
        }
        if (op == 2) {
            scanf("%d %d", &in1, &in2);
            tree.change(1, 1, rt, in1, in2, 1);
        }
        if (op == 3) {
            scanf("%d", &in1);
            STn res = tree.a[1];
            if (res.minn == inf) {cout << "-1\n"; continue;}
            int l = lca(res.minp, res.maxp);
            if (in1 == l) {cout << "-1\n"; continue;}
            cout << val[lca(in1, lca(res.minp, res.maxp))] << '\n';
        }
    }
    return 0;
}
```



---

## 作者：Umbrella_Leaf (赞：2)

### 题意

> 给你一棵 $n$ 个点的带权树，初始所有顶点都是白色。有 $q$ 个操作：
>
> - 将 $[l,r]$ 内的点全部染成黑色；
> - 将 $[l,r]$ 内的点全部染成白色；
> - 询问离 $x$ 的瓶颈距离最大的黑色点到 $x$ 的瓶颈距离。
>
> $2\le n,q\le 3\times 10^5$。

### 分析

首先考虑如何处理瓶颈距离，我们可以建一棵类似 Kruskal 重构树的树，每次在原树中选出边权最小的边，建立一个新点权值为此边边权，它的两个儿子是这条边连接的两个连通块。

那么 $(x,y)$ 的瓶颈距离就是 $x$ 和 $y$ 的 LCA 的权值。

然后在 Kruskal 重构树上做一遍 dfs 并求出 dfs 序，那么距离 $x$ 的最大的瓶颈距离就是所有黑色点和 $x$ 的 LCA 的值。

然后就拿线段树维护 LCA 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int x,y,z;
	bool operator <(const edge &b)const{
		return z<b.z;
	}
}e[300005];
int n,q;
int son[600005][2],cnt,val[600005];
int fa[600005];
int pe[600005][25];
int dep[600005];
int tree[2000005],tag[2000005],lca[2000005];
int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
void dfs(int x){
	if(son[x][0]){
		dep[son[x][0]]=dep[x]+1;
		dfs(son[x][0]);
		pe[son[x][0]][0]=x;
	}if(son[x][1]){
		dep[son[x][1]]=dep[x]+1;
		dfs(son[x][1]);
		pe[son[x][1]][0]=x;
	}
}
int LCA(int x,int y){
	if(!x||!y)return x|y;
	int k=20;
	while(dep[x]!=dep[y]&&k>=0){
		if(dep[x]<dep[y])swap(x,y);
		if(dep[pe[x][k]]>=dep[y])x=pe[x][k];
		k--;
	}
	if(x==y)return x;
	k=20;
	while(k>=0){
		if(pe[x][k]!=pe[y][k])x=pe[x][k],y=pe[y][k];
		k--;
	}
	return pe[x][0];
}
void build(int k,int l,int r){
	tag[k]=-1;
	if(l==r){
		lca[k]=l;
		return;
	}
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	lca[k]=LCA(lca[k*2],lca[k*2+1]);
}
void pushdown(int k,int l,int r){
	if(tag[k]>=0){
		if(tag[k]){
			tree[k*2]=lca[k*2];
			tree[k*2+1]=lca[k*2+1];
		}else{
			tree[k*2]=0;
			tree[k*2+1]=0;
		}
		tag[k*2]=tag[k*2+1]=tag[k];
		tag[k]=-1;
	}
}
void update(int k,int l,int r,int x,int y,int z){
	if(l>=x&&r<=y){
		if(z)tree[k]=lca[k];
		else tree[k]=0;
		tag[k]=z;
		return;
	}
	pushdown(k,l,r);
	int mid=l+r>>1;
	if(x<=mid)update(k*2,l,mid,x,y,z);
	if(y>mid)update(k*2+1,mid+1,r,x,y,z);
	tree[k]=LCA(tree[k*2],tree[k*2+1]);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)fa[i]=i,val[i]=-1;
	for(int i=1;i<n;i++)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
	sort(e+1,e+n);
	cnt=n;
	for(int i=1;i<n;i++){
		int x=get(e[i].x),y=get(e[i].y);
		son[++cnt][0]=x,son[cnt][1]=y,val[cnt]=e[i].z;
		fa[x]=fa[y]=fa[cnt]=cnt;
	}
	dep[cnt]=1;
	dfs(cnt);
	for(int j=1;j<=20;j++)for(int i=1;i<=cnt;i++)pe[i][j]=pe[pe[i][j-1]][j-1];
	build(1,1,n);
	while(q--){
		int opt;scanf("%d",&opt);
		if(opt==1){
			int l,r;scanf("%d%d",&l,&r);
			update(1,1,n,l,r,1);
		}else if(opt==2){
			int l,r;scanf("%d%d",&l,&r);
			update(1,1,n,l,r,0);
		}else{
			int x;scanf("%d",&x);
			printf("%d\n",val[LCA(x,tree[1])]);
		}
	}
	return 0;
}
```

---

## 作者：Semorius (赞：1)

### 前置知识
- 线段树
- $\text{Kruskal}$ 重构树
- 点集 $\text{LCA}$

### 思路

看到询问为 $x$ 到所有白色节点的路径上最大可能边权，可以利用 $\text{Kruskal}$ 重构树转化为 $x$ 与所有白色点的 $\text{lca}$ 的权值。

问题在于如何快速求出一个点集的 $\text{lca}$，参考 CF1062E 中的套路，维护点集中 $\text{dfs}$ 序最大以及最小的两个点，求这两个点的 $\text{lca}$ 即为这个点集的 $\text{lca}$。

具体实现先建出 $\text{Kruskal}$ 重构树，然后建线段树维护区间 $\text{dfn}$ 最大最小值。对于修改操作，如果为操作 $1$ 则更新该区间 $\text{dfn}$ 最大值最小值，否则清空该区间。对于询问操作，查询全局 $\text{dfn}$ 最大最小值，与 $x$ 的 $\text{dfn}$ 合并，求 $\text{lca}$ 权值。

时间复杂度 $O(n \log n + q \log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define l(x) x<<1
#define r(x) x<<1|1
const int SIZE = 600005;
const int mod = 998244353;
int n, T, totv;
int head[SIZE], ver[SIZE*2], nxt[SIZE*2], tot;
int dfn[SIZE], id[SIZE], sum[SIZE], iid;
int a[SIZE], fa[SIZE], d[SIZE], f[SIZE][30];

inline int rd(){
	int f = 1, x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}

struct E{
	int x, y, val; 
}e[SIZE];

int get(int x){
	if(x == fa[x]) return x;
	return fa[x] = get(fa[x]);	
}

bool cmp(E x, E y){
	return x.val < y.val;	
}

void add(int x, int y){
	ver[++tot] = y, nxt[tot] = head[x];
	head[x] = tot;	
}

void dfs(int x, int ffa){
	dfn[x] = ++iid; id[dfn[x]] = x; d[x] = d[ffa] + 1; f[x][0] = ffa;
	for(int i = 1; i <= 25; i++) f[x][i] = f[f[x][i-1]][i-1];
	for(int i = head[x]; i; i = nxt[i]){
		int y = ver[i];
		if(y == ffa) continue;
		dfs(y, x);
	}	
}

int LCA(int x, int y){
	if(d[x] < d[y]) swap(x, y);
	for(int i = 25; i >= 0; i--){
		if(d[f[x][i]] >= d[y]) x = f[x][i];
		if(x == y) return x;
	}
	for(int i = 25; i >= 0; i--){
		if(f[x][i] != f[y][i]){
			x = f[x][i], y = f[y][i];
		}
	}
	return f[x][0];
}

struct Tree{
	int l, r;
	int Maxx, Minx;
	int Max, Min;
	int tag;
}t[SIZE<<2];

void pushup(int p){
	t[p].Max = max(t[l(p)].Max, t[r(p)].Max);
	t[p].Min = min(t[l(p)].Min, t[r(p)].Min);
	t[p].Maxx = max(t[l(p)].Maxx, t[r(p)].Maxx);
	t[p].Minx = min(t[l(p)].Minx, t[r(p)].Minx);
}

void pushdown(int p){
	if(t[p].tag != -1){
		if(t[p].tag){
			t[l(p)].Max = t[l(p)].Maxx;
			t[l(p)].Min = t[l(p)].Minx;
			t[r(p)].Max = t[r(p)].Maxx;
			t[r(p)].Min = t[r(p)].Minx;
		}
		else{
			t[l(p)].Max = 0, t[l(p)].Min = (1<<30);
			t[r(p)].Max = 0, t[r(p)].Min = (1<<30);
		}
		t[l(p)].tag = t[p].tag, t[r(p)].tag = t[p].tag;
		t[p].tag = -1;
	}
}

void Build(int p, int l, int r){
	t[p].l = l, t[p].r = r; t[p].tag = -1;
	if(l == r){
		t[p].Max = 0, t[p].Min = (1<<30);
		t[p].Maxx = t[p].Minx = dfn[l];
		return;
	}	
	int mid = (l + r) >> 1;
	Build(l(p), l, mid);
	Build(r(p), mid+1, r);
	pushup(p);
}

void change(int p, int l, int r, int kk){
	if(l <= t[p].l && r >= t[p].r){
		if(kk){
			t[p].Max = t[p].Maxx;
			t[p].Min = t[p].Minx;
		}
		else{
			t[p].Max = 0, t[p].Min = (1<<30);
		}
		t[p].tag = kk;
		return;
	}
	pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if(l <= mid) change(l(p), l, r, kk);
	if(r > mid) change(r(p), l, r, kk);
	pushup(p);
}

int main(){
	n = rd(), T = rd();
	for(int i = 1; i < n; i++){
		e[i].x = rd(), e[i].y = rd(), e[i].val = rd(); fa[i] = i;
	}
	for(int i = n; i <= 2*n; i++) fa[i] = i;
	sort(e+1, e+n, cmp); totv = n;
	for(int i = 1; i < n; i++){
		int x = e[i].x, y = e[i].y, val = e[i].val;
		int xx = get(x), yy = get(y);
		if(xx == yy) continue;
		totv++;
		add(xx, totv); add(totv, xx);
		add(yy, totv); add(totv, yy);
		a[totv] = val;
		fa[xx] = totv;
		fa[yy] = totv;
	}
	dfs(totv, 0);
	Build(1, 1, n);
	while(T--){
		int op = rd();
		if(op == 1){
			int l = rd(), r = rd();
			change(1, l, r, 1);
		}
		else if(op == 2){
			int l = rd(), r = rd();
			change(1, l, r, 0);			
		}
		else{
			int x = rd();
			int Min = t[1].Min, Max = t[1].Max;
			Min = min(Min, dfn[x]);
			Max = max(Max, dfn[x]);
			if(Min == (1<<30)){
				printf("-1\n");
				continue;
			}
			int x1 = id[Max], x2 = id[Min];
			int cc = LCA(x1, x2);
			if(a[cc] == 0) printf("-1\n");
			else printf("%d\n", a[cc]);
		}
	}
	return 0;
}
```


---

## 作者：周子衡 (赞：1)

方便起见，设树上有节点 $u,v$，定义 $\mathrm{maxv}(u,v)$ 表示 $u,v$ 路径上的最大边权（若 $u=v$，不妨设 $\mathrm{maxv}(u,v)=-1$）；设 $S$ 是树上一点集，定义 $\mathrm{maxv}(u,S)=\max_{u,v\in S}\{\mathrm{maxv}(u,v)\}$；对树上某节点 $u$ 和某点集 $S$，定义 $\mathrm{maxv}(u,S)=\max_{v\in S} \{\mathrm{maxv}(u,v)\}$

经典结论：设树上有点集 $S_1,S_2$，$u$ 是 $S_1$ 中任意一节点，$v$ 是 $S_2$ 中任意一节点。那么

$$\mathrm{maxv}(S_1\cup S_2)=\max\{\max\{\mathrm{maxv}(S_1),\mathrm{maxv}(S_2)\},\mathrm{maxv}(u,v)\}$$

这个结论在之前的 CF 题目中也有出过，此处略去详细证明。特别地，取 $S_2$ 为单点集 $\{u\}$，我们就得到了 $\mathrm{maxv}(u,S)$ 的计算方法。

回到原题。考虑用线段树维护开的点集 $S$，线段树上每个节点维护这个区间内所有开的节点组成的连通块中的最大边权，以及任意一个节点（**代表点**）。为了快速处理区间赋值操作，初始化时可以处理一下每个区间的点全开时的答案。合并的时候，大区间的答案对两个小区间的答案，以及小区间代表点间的最大边权取 $\max$。处理询问的时候也类似。

若采用树上倍增的方法 $O(\log n)$ 朴素计算两点间最大边权，总时间复杂度 $O(n\log^2 n)$，会遭到出题人定向针对。考虑优化计算两点间最大边权的复杂度：建立 Kruskal 重构树，则每次相当于计算两点 LCA，可以用 Euler 序做到预处理 $O(n\log n)$、单次查询 $O(1)$ 的复杂度。这样总时间复杂度 $O(n\log n)$。

一份 $O(n\log^2 n)$、在赛时狂 T 不止的代码（怨念.jpg）：

```cpp
#include<cstdio>
#include<vector>

using namespace std;


int fast_read()
{
	char ch='\0';
	while(!(ch>='0'&&ch<='9'))ch=getchar();
	int x=0;while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}

struct e
{
	int to,val;e(int _to=0,int _val=0):to(_to),val(_val){}
};
vector<e> ed[400000];int fa[400000][20],maxval[400000][20],dep[400000];

void dfs_bas(int u,int f=0)
{
	dep[u]=dep[f]+1;
	fa[u][0]=f;for(int i=1;i<20;i++)fa[u][i]=fa[fa[u][i-1]][i-1],maxval[u][i]=max(maxval[u][i-1],maxval[fa[u][i-1]][i-1]);
	for(int i=0;i<ed[u].size();i++)
	{
		int v=ed[u][i].to;if(v==f)continue;maxval[v][0]=ed[u][i].val;dfs_bas(v,u);
	}
}
int query(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);int ans=-1;
	for(int i=18;i>=0;i--)if(dep[fa[x][i]]>=dep[y]){ans=max(ans,maxval[x][i]);x=fa[x][i];}if(x==y)return ans;
	for(int i=18;i>=0;i--)if(fa[x][i]!=fa[y][i]){ans=max(ans,max(maxval[x][i],maxval[y][i]));x=fa[x][i],y=fa[y][i];}
	return max(ans,max(maxval[x][0],maxval[y][0]));
}
/*
int query_anc(int x,int d)
{
	int ans=-1;for(int i=18;i>=0;i--)if(d&(1<<i)){ans=max(ans,maxval[x][i]);x=fa[x][i];}return ans;
}
int query(int x,int y)
{
	int l=LCA(x,y);return max(query_anc(x,dep[x]-dep[l]),query_anc(y,dep[y]-dep[l]));
}*/

struct SegmentTree
{
	struct nd
	{
		int tag,l,r,pos,ans,ans_1;
	}t[2000000];
	void build(int l,int r,int k=1)
	{
		t[k].l=l,t[k].r=r,t[k].tag=-1,t[k].pos=0,t[k].ans=t[k].ans_1=-1;if(l==r)return;
		int mid=(l+r)>>1;build(l,mid,k<<1),build(mid+1,r,k<<1|1);
		t[k].ans_1=max(max(t[k<<1].ans_1,t[k<<1|1].ans_1),query(mid,mid+1));
	}
	void add_tag(int k,int tag)
	{
		if(tag==-1)return;
		t[k].tag=tag;
		if(tag==0){t[k].pos=0,t[k].ans=-1;}
		else{t[k].pos=t[k].l,t[k].ans=t[k].ans_1;}
	}
	void spread(int k)
	{
		add_tag(k<<1,t[k].tag),add_tag(k<<1|1,t[k].tag);t[k].tag=-1;
	}
	void update(int k)
	{
		if(t[k<<1].pos==0&&t[k<<1|1].pos==0){t[k].pos=0,t[k].ans=-1;return;}
		if(t[k<<1].pos==0){t[k].pos=t[k<<1|1].pos,t[k].ans=t[k<<1|1].ans;return;}
		if(t[k<<1|1].pos==0){t[k].pos=t[k<<1].pos,t[k].ans=t[k<<1].ans;return;}
		t[k].pos=t[k<<1].pos,t[k].ans=
		max(max(t[k<<1].ans,t[k<<1|1].ans),query(t[k<<1].pos,t[k<<1|1].pos));
	}
	void modify(int l,int r,int tag,int k=1)
	{
		if(l>t[k].r||r<t[k].l)return;
		if(l<=t[k].l&&t[k].r<=r){add_tag(k,tag);return;}
		spread(k);modify(l,r,tag,k<<1),modify(l,r,tag,k<<1|1);update(k);
	}
}T;

int main()
{
	//freopen("CF1628E.in","r",stdin);
	//freopen("CF1628E.out","w",stdout);
	int n=fast_read();int q=fast_read();
	for(int i=1,u=0,v=0,w=0;i<n;i++)
	{
		u=fast_read();v=fast_read();w=fast_read();
		ed[u].push_back(e(v,w)),ed[v].push_back(e(u,w));
	}
	dfs_bas(1);T.build(1,n);
	while(q--)
	{
		int op=0;op=fast_read();
		if(op==1)
		{
			int l=fast_read();int r=fast_read();T.modify(l,r,1);
		}
		else if(op==2)
		{
			int l=fast_read();int r=fast_read();T.modify(l,r,0);
		}
		else
		{
			int x=fast_read();
			int ans=T.t[1].ans;if(T.t[1].pos)ans=max(ans,query(x,T.t[1].pos));
			printf("%d\n",ans);
		}
	}
}
```

---

## 作者：Alex_Wei (赞：1)

Shitty problem.

题目相当于求 $x$ 以及所有开着的点的虚树上路径最大值。路径最值让我们想到 kruskal 重构树，而若干个点形成的虚树的路径最值就是这些点在 kruskal 重构树上的 LCA 对应的边的权值。

因此，建出重构树，线段树维护区间 LCA 即可。时间复杂度线性对数。启示：**树上路径最值 $\to$ kruskal 重构树**。[代码](https://codeforces.com/contest/1628/submission/143736225)。

---

## 作者：_AyachiNene (赞：0)

# 思路：
首先，求路径上的最大权值，就想到能不能用 Kruskal 重构树来做。显然，在重构树上深度越小的点的权值就越大，所以考虑怎么让一个点集的 lca 深度最小。求一个点集的 lca 有一个套路，一个点集的 lca 就等于 $dfn$ 最大和最小的点的 lca。这个也很好想，因为 $dfn$ 最大和最小的两个点的跨度肯定是最大的，那么它们的 lca 就等于所有点的 lca。因为查询操作要求从 $x$ 点出发的最大值所以答案就是 Kruskal 重构树上点 $x$ 和所有白点的 lca 的权值，再上个数据结构就做完了。

具体细节见代码。
# Code：
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
struct node
{
	int nxt,to,val;
}e[1200005];
int head[600005],cnt_edge;
inline void add_edge(int u,int v)
{
	e[++cnt_edge].to=v;
	e[cnt_edge].nxt=head[u];
	head[u]=cnt_edge;
}
struct node1
{
	int x,y,val;
}edge[600005];
bool cmp(node1 x,node1 y)
{
	return x.val<y.val;
}
int F[600005];
int n,m;
int val[600005],cnt_kt;
int siz[600005],dfn[600005],f[600005],dep[600005],top[600005],son[600005],cnt;
int pos[600005];
int find(int x)
{
	if(F[x]==x)
		return x;
	return F[x]=find(F[x]);
}
void dfs1(int u,int fa)
{
	f[u]=fa;
	dep[u]=dep[fa]+1;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)
			continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
			son[u]=v;
	}
}
void dfs2(int u,int t)
{
	top[u]=t;
	dfn[u]=++cnt;
	pos[cnt]=u;
	if(son[u])
		dfs2(son[u],t);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==f[u]||v==son[u])
			continue;
		dfs2(v,v);
	}
}
inline int lca(int x,int y)   //树链剖分求lca 
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=f[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
//--------------st表----------------
int stmax[600005][21],stmin[600005][21];
int lg[600005]; 
inline void bldst()
{
	for(int i=1;i<=6e5;i++)   //st表维护区间最值 
		lg[i]=log2(i);
	for(int i=1;i<=n;i++)
		stmax[i][0]=stmin[i][0]=dfn[i];
	for(int j=1;j<=20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			stmax[i][j]=max(stmax[i][j-1],stmax[i+(1<<(j-1))][j-1]);
			stmin[i][j]=min(stmin[i][j-1],stmin[i+(1<<(j-1))][j-1]);
		}
}
inline int qstmax(int l,int r)
{
	int k=lg[r-l+1];
	return max(stmax[l][k],stmax[r-(1<<k)+1][k]);
}
inline int qstmin(int l,int r)
{
	int k=lg[r-l+1];
	return min(stmin[l][k],stmin[r-(1<<k)+1][k]);
}
//----------以上为st边-------------- 
//-----------以下为线段树-----------
#define ls (root<<1)
#define rs (root<<1|1)
#define mid ((t[root].l+t[root].r)>>1) 
struct segt
{
	int l,r,maxn,minn,tag;//线段树维护涂黑涂白和区间最值 
}t[600005<<2];
//tag=1:涂黑
//tag=2：涂白 
inline void update(int root)
{
	t[root].maxn=max(t[ls].maxn,t[rs].maxn);
	t[root].minn=min(t[ls].minn,t[rs].minn);
}
inline down(int root)
{
	if(t[root].tag==2)
	{
		t[ls].tag=2;
		t[rs].tag=2;
		t[ls].maxn=qstmax(t[ls].l,t[ls].r); //涂白后这个点的权值就是这段区间的最大最小值 
		t[ls].minn=qstmin(t[ls].l,t[ls].r);
		t[rs].maxn=qstmax(t[rs].l,t[rs].r);
		t[rs].minn=qstmin(t[rs].l,t[rs].r);
		t[root].tag=0;
	}
	else
	{
		t[ls].tag=1;
		t[rs].tag=1;
		t[ls].maxn=t[rs].maxn=-1e9;   //涂黑就把这个点的最大最小值分别赋成inf和-inf 
		t[ls].minn=t[rs].minn=1e9;
		t[root].tag=0;
	}
}
void bld(int l,int r,int root)
{
	t[root].l=l;
	t[root].r=r;
	if(l==r)
	{
		t[root].maxn=-1e9;
		t[root].minn=1e9;
		return;
	}
	bld(l,mid,ls);
	bld(mid+1,r,rs);
	update(root);
}
void add(int x,int y,int root)
{
	if(t[root].l>=x&&t[root].r<=y)
	{
		t[root].tag=2;
		t[root].maxn=qstmax(t[root].l,t[root].r);
		t[root].minn=qstmin(t[root].l,t[root].r);
		return;
	}
	if(t[root].tag)	
		down(root);
	if(x<=mid)
		add(x,y,ls);
	if(y>mid)
		add(x,y,rs);
	update(root);
}
void del(int x,int y,int root)
{
	if(t[root].l>=x&&t[root].r<=y)
	{
		t[root].tag=1;
		t[root].maxn=-1e9;
		t[root].minn=1e9;
		return;
	}
	if(t[root].tag)
		down(root);
	if(x<=mid)
		del(x,y,ls);
	if(y>mid)
		del(x,y,rs);
	update(root);
}
int qmax(int x,int y,int root)
{
	if(t[root].l>=x&&t[root].r<=y)
		return t[root].maxn;
	int res=-1e9;
	if(t[root].tag)
		down(root);
	if(x<=mid)
		res=max(res,qmax(x,y,ls));
	if(y>mid)
		res=max(res,qmax(x,y,rs));
	return res;
}
int qmin(int x,int y,int root)
{
	if(t[root].l>=x&&t[root].r<=y)
		return t[root].minn;
	int res=1e9;
	if(t[root].tag)
		down(root);
	if(x<=mid)
		res=min(res,qmin(x,y,ls));
	if(y>mid)
		res=min(res,qmin(x,y,rs));
	return res;
}
//-------------------------------
int main()
{
	for(int i=1;i<=6e5;i++)
		F[i]=i;
	n=read(),m=read();
	for(int i=1;i<n;i++)
		edge[i].x=read(),edge[i].y=read(),edge[i].val=read();
	sort(edge+1,edge+n,cmp);
	cnt_kt=n;
	for(int i=1;i<n;i++)//Kruskal重构树 
	{
		val[++cnt_kt]=edge[i].val;
		int fx=find(edge[i].x);
		int fy=find(edge[i].y);
		F[fx]=F[fy]=F[cnt_kt]=cnt_kt;
//		cout<<fx<<" "<<fy<<endl;
		add_edge(cnt_kt,fx);
		add_edge(fx,cnt_kt);
		add_edge(cnt_kt,fy);
		add_edge(fy,cnt_kt);
	}
	dfs1(cnt_kt,0);
	dfs2(cnt_kt,cnt_kt);
	bldst();
	bld(1,n,1);
//	for(int i=1;i<=n;i++)
//		cout<<dfn[i]<<" ";
//	cout<<endl;
	while(m--)
	{
		int op,x,y;
		op=read(),x=read();
		if(op==1)
		{
			y=read();
			add(x,y,1);
		}
		else if(op==2)
		{
			y=read();
			del(x,y,1);
		}
		else
		{
			int maxdfn=qmax(1,n,1);
			int mindfn=qmin(1,n,1);
//			cout<<maxdfn<<" "<<mindfn<<endl;
			if(maxdfn==-1e9||mindfn==1e9||(maxdfn==mindfn&&pos[mindfn]==x))//特判没有白点和就只有x一个白点的情况 
			{
				cout<<-1<<endl;
				continue;
			}
//			cout<<pos[maxdfn]<<" "<<pos[mindfn]<<endl;
			int ans=lca(pos[maxdfn],pos[mindfn]);
			ans=lca(ans,x);
			cout<<val[ans]<<endl;
		}
	}
}
```


---

## 作者：happybob (赞：0)

这为啥有 *3100。

考虑询问本质上在干什么。

树上两点之间边权最大值，相当于两点在 Kruskal 重构树（边权从小到大排序）上 LCA 的点权。

设 $l_{i,j}$ 表示重构树上 $i$ 与 $j$ 的 LCA，$val_i$ 表示重构树上 $i$ 的点权。

于是我们要求 $\max \limits_{u \in \text{white} \land u \neq x} val_{l_{u,x}}$。

通过观察可知，这个东西等于所有白点的 LCA 和 $x$ 的 LCA 的点权。

注意到这是个点集 LCA 的问题，只需要把 DFS 序最大和最小的两个点弄出来即可，线段树维护。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int N = 6e5 + 5;

vector<int> G[N];
int val[N];
int n, q;
int nfa[N][21], dep[N];

class Union_Find
{
public:
	int idx;
	int fa[N];
	void Init()
	{
		for (int i = 0; i < N; i++) fa[i] = i;
		idx = n;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : fa[u] = find(fa[u]));
	}
	void merge(int u, int v, int w)
	{
		if ((u = find(u)) == (v = find(v))) return;
		idx++;
		val[idx] = w;
		G[idx].emplace_back(u), G[idx].emplace_back(v);
		fa[u] = fa[v] = idx;
		nfa[u][0] = nfa[v][0] = idx;
	}
}uf;

struct Edge
{
	int u, v, w;

	Edge() = default;

	Edge(int u, int v, int w)
		: u(u), v(v), w(w)
	{
	}

	bool operator==(const Edge& other) const = default;
}p[N];

int dfn[N], idx, rid[N];

void dfs(int u, int f)
{
	dep[u] = dep[f] + 1;
	dfn[u] = ++idx;
	rid[idx] = u;
	for (auto& j : G[u]) dfs(j, u);
}

class SegmentTree
{
public:
	struct Node
	{
		int l, r, maxn, minn;
		int tag;
		int realmax, realmin;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
		tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
		tr[u].realmax = max(tr[u << 1].realmax, tr[u << 1 | 1].realmax);
		tr[u].realmin = min(tr[u << 1].realmin, tr[u << 1 | 1].realmin);
	}
	void pushdown(int u)
	{
		if (tr[u].tag == -1) return;
		if (tr[u].tag)
		{
			tr[u << 1].tag = 1;
			tr[u << 1 | 1].tag = 1;
			tr[u << 1].realmax = 0, tr[u << 1].realmin = N;
			tr[u << 1 | 1].realmax = 0, tr[u << 1 | 1].realmin = N;
		}
		else
		{
			tr[u << 1].tag = 0;
			tr[u << 1 | 1].tag = 0;
			tr[u << 1].realmax = tr[u << 1].maxn, tr[u << 1].realmin = tr[u << 1].minn;
			tr[u << 1 | 1].realmax = tr[u << 1 | 1].maxn, tr[u << 1 | 1].realmin = tr[u << 1 | 1].minn;
		}
		tr[u].tag = -1;
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, dfn[l], dfn[l], -1, 0, N };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int l, int r, int v)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			if (!v)
			{
				tr[u].tag = 0;
				tr[u].realmax = tr[u].maxn, tr[u].realmin = tr[u].minn;
			}
			else
			{
				tr[u].tag = 1;
				tr[u].realmax = 0, tr[u].realmin = N;
			}
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, v);
		if (r > mid) update(u << 1 | 1, l, r, v);
		pushup(u);
	}
	int qmax(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].realmax;
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1, res = 0;
		if (l <= mid) res = qmax(u << 1, l, r);
		if (r > mid) res = max(res, qmax(u << 1 | 1, l, r));
		return res;
	}
	int qmin(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].realmin;
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1, res = N;
		if (l <= mid) res = qmin(u << 1, l, r);
		if (r > mid) res = min(res, qmin(u << 1 | 1, l, r));
		return res;
	}
}sgt;

int LCA(int u, int v)
{
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);
	int k = dep[u] - dep[v], c = 0;
	while (k)
	{
		if (k & 1) u = nfa[u][c];
		c++;
		k >>= 1;
	}
	if (u == v) return u;
	for (int i = 20; i >= 0; i--)
	{
		if (nfa[u][i] != nfa[v][i])
		{
			u = nfa[u][i], v = nfa[v][i];
		}
	}
	return nfa[u][0];
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	uf.Init();
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		p[i] = Edge(u, v, w);
	}
	sort(p + 1, p + n, [&](const Edge& x, const Edge& y) {return x.w < y.w; });
	for (int i = 1; i < n; i++) uf.merge(p[i].u, p[i].v, p[i].w);
	dfs(2 * n - 1, 2 * n - 1);
	sgt.build(1, 1, n);
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 1; j <= 2 * n - 1; j++) nfa[j][i] = nfa[nfa[j][i - 1]][i - 1];
	}
	while (q--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int l, r;
			cin >> l >> r;
			sgt.update(1, l, r, 0);
		}
		else if (op == 2)
		{
			int l, r;
			cin >> l >> r;
			sgt.update(1, l, r, 1);
		}
		else
		{
			int x;
			cin >> x;
			int maxid = sgt.qmax(1, 1, n);
			int minid = sgt.qmin(1, 1, n);
			if (maxid == 0 || minid == N || (maxid == minid && maxid == dfn[x])) cout << "-1\n";
			else
			{
				cout << val[LCA(x, LCA(rid[maxid], rid[minid]))] << "\n";
			}
		}
	}
	return 0;
}
```


---

## 作者：Leasier (赞：0)

前置芝士：[Kruskal 重构树](https://oi-wiki.org/graph/mst/#kruskal-重构树)、[线段树](https://oi-wiki.org/ds/seg/)

看到路径最大值，考虑建出原树的 Kruskal 重构树。

然后从 $x$ 出发到达任意一个白色点的简单路径上经过的边的最大权值就是 $x$ 与当前所有白色点在 Kruskal 重构树上的 LCA 的权值。无解当且仅当没有白色点或白色点只有 $x$ 一个。

于是线段树维护区间 LCA 即可。时间复杂度为 $O(n \log^2 n)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

typedef struct {
	int nxt;
	int start;
	int end;
	int dis;
} Edge;

typedef struct {
	int l;
	int r;
	int tag;
	int full_lca;
	int cur_lca;
} Node;

int cnt = 0;
int root[600007], val[600007], head[600007], depth[600007], fa[600007][27];
Edge edge1[300007], edge2[600007];
Node tree[2400007];

bool operator <(const Edge a, const Edge b){
	return a.dis < b.dis;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		root[i] = i;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void add_edge(int start, int end){
	cnt++;
	edge2[cnt].nxt = head[start];
	head[start] = cnt;
	edge2[cnt].end = end;
}

void dfs(int u){
	int t;
	depth[u] = depth[fa[u][0]] + 1;
	t = log2(depth[u]);
	for (register int i = 1; i <= t; i++){
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (register int i = head[u]; i != 0; i = edge2[i].nxt){
		dfs(edge2[i].end);
	}
}

inline int lca(int u, int v){
	if (u == 0) return v;
	if (v == 0) return u;
	if (depth[u] < depth[v]) swap(u, v);
	while (depth[u] > depth[v]) u = fa[u][(int)log2(depth[u] - depth[v])];
	if (u == v) return u;
	for (register int i = log2(depth[u]); i >= 0; i--){
		if (fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

inline void update1(int x){
	tree[x].full_lca = lca(tree[x * 2].full_lca, tree[x * 2 + 1].full_lca);
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r){
		tree[x].full_lca = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	update1(x);
}

inline void pushdown(int x){
	if (tree[x].tag != 0){
		int ls = x * 2, rs = x * 2 + 1;
		tree[ls].tag = tree[rs].tag = tree[x].tag;
		if (tree[x].tag == 1){
			tree[ls].cur_lca = tree[ls].full_lca;
			tree[rs].cur_lca = tree[rs].full_lca;
		} else {
			tree[ls].cur_lca = tree[rs].cur_lca = 0;
		}
		tree[x].tag = 0;
	}
}

inline void update2(int x){
	tree[x].cur_lca = lca(tree[x * 2].cur_lca, tree[x * 2 + 1].cur_lca);
}

void white(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag = 1;
		tree[x].cur_lca = tree[x].full_lca;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) white(x * 2, l, r);
	if (r > mid) white(x * 2 + 1, l, r);
	update2(x);
}

void black(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag = 2;
		tree[x].cur_lca = 0;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) black(x * 2, l, r);
	if (r > mid) black(x * 2 + 1, l, r);
	update2(x);
}

int main(){
	int n = read(), q = read(), m = n;
	init(n * 2 - 1);
	for (register int i = 1; i < n; i++){
		edge1[i].start = read();
		edge1[i].end = read();
		edge1[i].dis = read();
	}
	sort(edge1 + 1, edge1 + n);
	for (register int i = 1; i < n; i++){
		int u = get_root(edge1[i].start), v = get_root(edge1[i].end);
		m++;
		root[u] = root[v] = fa[u][0] = fa[v][0] = m;
		val[m] = edge1[i].dis;
		add_edge(m, u);
		add_edge(m, v);
	}
	dfs(m);
	build(1, 1, n);
	for (register int i = 1; i <= q; i++){
		int t = read();
		if (t <= 2){
			int l = read(), r = read();
			if (t == 1){
				white(1, l, r);
			} else {
				black(1, l, r);
			}
		} else {
			int x = read();
			if (tree[1].cur_lca == 0 || tree[1].cur_lca == x){
				printf("-1\n");
			} else {
				printf("%d\n", val[lca(x, tree[1].cur_lca)]);
			}
		}
	}
	return 0;
}
```

---

