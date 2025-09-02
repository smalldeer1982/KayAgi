# Weighed Tree Radius

## 题目描述

给你一个$n$个点的树和$n-1$条边。第$i$个点的初始权值为$a_i$。

定义结点$v$到结点$u$的距离$d_v(u)$等于$v$和$u$之间的边的数量。注意:$d_v(u)=d_u(v),d_v(v)=0$

定义结点$v$到结点$u$的权值距离$w_v(u)=d_v(u)+a_u$。注意：$w_v(v)=a_v,w_v(u) \neq w_u(v)$如果$a_u \neq a_v$

与通常的距离类似，让我们定义结点$v$的偏心距$e(v)$是从$v$到其他结点的最大**权值距离（包括$v$本身）**，即$e(v)=\max\limits_{1\leq u \leq n} w_v(u)$。

最后，我们定义树的半径$r$是所有偏心距的最小值，即$r=\min\limits_{1\leq v\leq n} e(v)$

你需要对$m$次询问进行回答，对于第$j$次询问，给出两个数$v_j$和$x_j$，表示将$a_{v_j}$的值修改为$x_j$。

在每次询问后，输出当前该树的半径$r$。

## 说明/提示

第一个询问后，你会得到下面这样的树：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1783G/9e4a681ceb9a6bc974526ec74850e83ba3019044.png)

图中被标记的结点是偏心距$e(v)$最小的结点，即$r=e(4)=7$。其他结点的偏心距如下:$e(1)=8,e(2)=9,e(3)=9,e(5)=8,e(6)=8$。

第二个询问后，你会得到下面这样的树：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1783G/2e871ccd9092ddeb102928f6829b152be988cf84.png)

半径$r=e(1)=4$

第三个询问后，半径$r=e(2)=5$。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1783G/fe33c3a49f01d805511036a4052869d55e0dcd18.png)

## 样例 #1

### 输入

```
6
1 3 3 7 0 1
2 1
1 3
1 4
5 4
4 6
5
4 7
4 0
2 5
5 10
5 5```

### 输出

```
7
4
5
10
7```

# 题解

## 作者：namelessgugugu (赞：7)

#### 题面

给定一棵 $n$ 个点，第 $i$ 个点有点权 $a_i$ 的树，对于一个点 $u$ 定义偏心距 $e(u) = \max\{ dis(u, v) + a_v\}$，其中 $dis(u, v)$ 表示两点在树上的距离。定义半径 $r = \min\{e(u)\}$。

$m$ 次单点修改，每次修改后询问 $r$。

$1 \leqslant n \leqslant 2 \times 10^5, 1 \leqslant m \leqslant 10^5$。

#### 题解

首先发现半径不是很好做，但是直径看上去就很有对称性，因此我们先考虑求直径的问题，也就是 $nd(u, v) = dis(u, v) + a_u + a_v, d = \max\{nd(x, y)\}$。

这个 $d$ 就相当于，在原树的基础上，每个点附带了两个长度为 $a_i$ 的链（这里挂两条的意义是要满足 $nd(u, u) = 2a_u$），得到的新树的直径，这种在一个正常的树上的直径往往能带来很多优秀的性质。

分析 $d$ 和 $r$ 之间的关系，考虑新树的直径中点，如果这个中点 $mid$ 在原树上，根据直径中点的性质有 $r = e(mid) = \lceil \frac{d}{2} \rceil$。否则我们就取不到这个 $mid$，那此时考虑这一条直径对应的原树上的路径 $(u, v)$，也就是 $d = nd(u, v)$，不妨设 $mid$ 在 $u$ 所对应的链上，则有 $e(u) = a_u$，而对于任何一个其他的点 $x$, 有 $e(x) \geqslant dis(x, u) + a_u > a_u = e(u)$，因此这种情况下 $r = e(u)$。另外我写完代码才发现第二种情况不可能发生，因为如果是这样会有 $d = nd(u, u)$。

通过刚才的分析，我们发现只要能维护新树的直径，以及这个直径对应的原树上的端点，我们就能轻松解决这个问题。

一个众所周知的结论是，如果用一条边将两棵树连接，则新直径端点一定都来源于旧的四个直径端点。实际上有一个更强的结论：在同一棵树上的两个虚树取并，新的直径端点同样来源于旧的四个直径端点。

简单证明一下，如果新直径端点都来源于旧的同一棵虚树，则结论显然成立。

如果来源于不同的虚树，那么假设新直径 $(u, v)$ 不满足上述结论，它们分别来自原虚树 $A$ 和 $B$。则路径 $(u, v)$ 一定是由一段来自于 $A$ 的路径与一段来自于 $B$ 的路径并起来的，不然图就不是树了。

此时考虑距离 $v$ 最远的在路径 $(u, v)$ 上且在虚树 $B$ 里面的点 $x$，那么原本虚树 $B$ 的两个直径端点 $a, b$ 一定有一个距离 $x$ 不少于 $v$ 到 $x$ 的距离，而且路径不会经过 $(u, x)$（这条路径完全不在 $B$ 里面）。$u$ 也可以以同样的方式调整。因此发现 $(u, v)$ 根本不是直径，出现矛盾，假设不成立。

有了这个结论，我们就可以以任意顺序合并每个点，并且需要存下来的信息量是非常少的，可以直接用线段树维护，一个节点存储编号在 $[l, r]$ 内的点（以及它们带着的链）组成的虚树的直径长度及其端点。

每一次合并需要 $O(1)$ 次求树上两点距离，这可以通过 $O(1)$ 或 $O(\log n)$ 的求 lca 来实现。

根据求 lca 方式的不同，最终复杂度是 $O(n \log n)$ 或者 $O(n \log^2 n)$，我这里使用的是 $O(n \log n) - O(1)$ 求 lca。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define FILEIO(filename) (freopen(filename ".in", "r", stdin), freopen(filename ".out", "w", stdout))
typedef long long ll;
typedef unsigned long long ull;
const int N = 200005;
int n, m, val[N];
struct Edge
{
    int to, nxt;
} E[N << 1];
int head[N], tot;
inline void add(int f, int t)
{
    E[++tot] = {t, head[f]}, head[f] = tot;
    return;
}
int dep[N], dfn[N], tt, lg[N << 1], euler[N << 1], st[N << 1][20];
void dfs(int x, int from)
{
    dep[x] = dep[from] + 1, euler[dfn[x] = ++tt] = x;
    for (int i = head[x]; i;i = E[i].nxt)
    {
        int y = E[i].to;
        if(y == from)
            continue;
        dfs(y, x), euler[++tt] = x;
    }
    return;
}
inline int depmin(int x, int y)
{
    return dep[x] <= dep[y] ? x : y;
}
inline void st_init(void)
{
    for (int i = 1; i <= tt;++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= tt;++i)
        st[i][0] = euler[i];
    for (int k = 1; k < lg[tt];++k)
        for (int i = 1; i + (1 << k) - 1 <= tt;++i)
            st[i][k] = depmin(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
    return;
}
inline int query(int l, int r)
{
    int k = lg[r - l + 1] - 1;
    return depmin(st[l][k], st[r - (1 << k) + 1][k]);
}
inline int lca(int x, int y)
{
    x = dfn[x], y = dfn[y];
    if(x > y)
        std::swap(x, y);
    return query(x, y);
}
inline ll dis(int x, int y)
{
    int f = lca(x, y);
    return dep[x] + dep[y] - 2 * dep[f];
}
struct Info
{
    int x, y;
    ll len;
    Info(void)
    {
        x = y = len = 0;
        return;
    }
    Info(int _x, int _y)
    {
        x = _x, y = _y, len = dis(x, y) + val[x] + val[y];
        return;
    }
    inline bool operator<(Info b) const
    {
        return len < b.len;
    }
};
inline Info merge(Info a, Info b)
{
    Info p[6] = {a, b, Info(a.x, b.x), Info(a.x, b.y), Info(a.y, b.x), Info(a.y, b.y)};
    return *std::max_element(p, p + 6);
}
struct SgT
{
    Info t[N << 2];
    inline int ls(int x)
    {
        return x << 1;
    }
    inline int rs(int x)
    {
        return x << 1 | 1;
    }
    inline void pushup(int x)
    {
        t[x] = merge(t[ls(x)], t[rs(x)]);
        return;
    }
    void build(int x, int l, int r)
    {
        if(l == r)
            return t[x] = Info(l, l), void(0);
        int mid = (l + r) >> 1;
        build(ls(x), l, mid), build(rs(x), mid + 1, r);
        pushup(x);
        return;
    }
    void update(int x, int l, int r, int p)
    {
        if(l == r)
            return t[x] = Info(p, p), void(0);
        int mid = (l + r) >> 1;
        if(p <= mid)
            update(ls(x), l, mid, p);
        else
            update(rs(x), mid + 1, r, p);
        pushup(x);
        return;
    }
    inline ll query(void)
    {
        return std::max<ll>((t[1].len + 1) / 2, std::max(val[t[1].x], val[t[1].y]));
    }
} T;
int main(void)
{
    scanf("%d", &n);
    for (int i = 1;i <= n;++i)
        scanf("%d", val + i);
    for (int i = 1, u, v; i < n;++i)
        scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs(1, 0), st_init(), T.build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1, x, y; i <= m;++i)
    {
        scanf("%d%d", &x, &y);
        val[x] = y;
        T.update(1, 1, n, x);
        printf("%lld\n", T.query());
    }
    return 0;
}
```

---

## 作者：arundo (赞：3)

CF1783G Weighed Tree Radius 题解。

发现 $w$ 的定义具有方向性，这样其实不利于分析。

考虑重定义一种 $w$ 为 $w'(x,y)=a_x+a_y+d(x,y)$。

据此可以定义一颗树的直径为最大的 $w'(x,y)$。（此时直径可能为 $w'(x,x)=2a_x$ 的形式）

这样定义的直径保留了传统直径的许多有利性质。

首先，直径路径上一定存在一点 $z$ 使得 $w_z(x)=\lceil{w'(x,y)\over 2}\rceil$。

证明显然，因为 $d$ 总是连续的，且 $a_x\le a_y+d(x,y)$、$a_y\le a_x+d(x,y)$。后者存在的原因是 $w'(x,y)\ge w(x,x)$、$w'(x,y)\ge w(y,y)$。

其次，$e(z)=\max(w_z(x),w_z(y))$。

证明可以把 $a_x$ 或者 $a_y$ 看成连在 $x$ 或 $y$ 上的一段距离，就和树的直径的证明方法相同。

结合两个性质可以得到 $e(z)\ge\lceil{w'(x,y)\over 2}\rceil$，且一定能取等。所以所求即后式。

那么只需维护直径 $(x,y)$ 即可。

接下来考虑修改对询问的影响。若 $a_z$ 的修改量 $\Delta\ge 0$，则新的直径只可能是 $d(x,z)$、$d(y,z)$、$d(z,z)$ 中的一个，直接分讨即可。否则不太好做。

这个操作类似回退，因此可以将修改映射到时间上，使 $a$ 不降。那么对修改做线段树分治即可。

时间复杂度 $O(n\log^2n)$ 或 $O(n\log n)$（$n$、$m$ 同阶），视 LCA 的实现而定。

---

## 作者：FatOldEight (赞：2)

一道 2800，做了一个月。

---

首先题目给了我们极好的提示，是让我们求半径的最小值。此时我们就可以考虑将其转化为直径，定义一棵树的直径 $d=\max\{a_u+a_v+d_v(v)\}$。

此时半径 $r=\lceil\frac{d}{2}\rceil$。

证明较为显然且其他题解均有较为详细的证明，所以故不再赘述。

现在的问题转化为了求 $d$。

考虑修改对 $d$ 的影响，设原直径端点为 $u,v$，当 $d_x$ 修改的变化量 $\Delta\ge0$ 时，直径的端点取值只能为 $(u,x),(v,x),(x,x)$ 或者不变。

当 $d_x$ 修改的变化量 $\Delta<0$ 时，发现直径端点的变化不确定，此时就比较难做。

此时我们考虑令所有的点的初始值均为 $0$，可以使用线段树分治，此时相当于所有修改都是从 $0$ 开始的，故变化量都大于 $0$。

详情见代码，时间复杂度$O(n\log^2n)$。

### code

```cpp
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
using namespace std;
struct sss
{
    int q,w,nxt;
}a[500005];
void update(pii);
int ans[200005],S,T,Dis,s[200005];
struct Segment_Tree
{
    struct sss
    {
        int l,r;
        vector<pii>v;
        #define l(x) tree[x].l
        #define r(x) tree[x].r
        #define v(x) tree[x].v
    }tree[2000005];
    void build(int x,int l,int r)
    {
        l(x)=l;r(x)=r;
        if(l(x)==r(x))return;
        int mid=(l+r)>>1;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
    }
    void change(int x,int l,int r,pii p)
    {
        if(l<=l(x)&&r(x)<=r)return v(x).push_back(p);
        int mid=(l(x)+r(x))>>1;
        if(l<=mid)change(x*2,l,r,p);
        if(mid<r)change(x*2+1,l,r,p);
    }
    void dfs(int x)//线段树分治
    {
        for(pii x:v(x))update(x);
        if(l(x)==r(x))ans[l(x)]=(Dis+1)/2;//记录答案
        else
        {
            int ns=S,nt=T,nd=Dis;
            dfs(x*2);
            S=ns,T=nt,Dis=nd;//回溯
            dfs(x*2+1);
        }
        for(pii x:v(x))s[x.first]=0;//把值都清空为 0
    }
}T1;
int head[1000005],cnt,n,p[200005][21],d[200005],Q,vis[200005],lst[200005];
void adde(int q,int w)
{
    a[++cnt].q=q;
    a[cnt].w=w;
    a[cnt].nxt=head[q];
    head[q]=cnt;
}
int LCA(int x,int y)
{
    if(d[x]<d[y])swap(x,y);
    for(int i=20;i>=0;i--)if(d[p[x][i]]>=d[y])x=p[x][i];
    if(x==y)return x;
    for(int i=20;i>=0;i--)if(p[x][i]!=p[y][i])x=p[x][i],y=p[y][i];
    return p[x][0];
}
int dis(int x,int y){return d[x]+d[y]-2*d[LCA(x,y)];}
void update(pii p)
{
    int x=p.first;
    s[x]=p.second;//因为 s[x] 已经被清空为 0，所以可以直接使用变化量大于 0 的结论
    int ns=S,nt=T,nD=Dis;
    vector<pii>cds={{S,x},{x,T},{x,x}};//新的值只会在这三种出现
    for(auto &y:cds)
    {
        int d1=dis(y.first,y.second);
        if(nD<s[y.first]+d1+s[y.second])
        {
            nD=s[y.first]+d1+s[y.second];
            ns=y.first,nt=y.second;
        }
    }
    S=ns;
    T=nt;
    Dis=nD;
}
void dfs(int x,int fa)
{
    p[x][0]=fa;
    d[x]=d[fa]+1;
    for(int i=1;i<=20;i++)p[x][i]=p[p[x][i-1]][i-1];
    for(int i=head[x];i;i=a[i].nxt)if(a[i].w^fa)dfs(a[i].w,x);
}
int findD(int S)//预处理直径
{
    memset(vis,0,sizeof(vis));
    queue<int> q;
    vis[S]=1;
    q.push(S);
    int x;
    while(!q.empty())
    {
        x=q.front(); 
        q.pop();
        for(int i=head[x];i;i=a[i].nxt)
        {
            if(vis[a[i].w])continue;
            vis[a[i].w] = 1;
            q.push(a[i].w);
        }
    }
    return x;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&s[i]);
    for(int i=1;i<n;i++)
    {
        int q,w;
        scanf("%d%d",&q,&w);
        adde(q,w);
        adde(w,q);
    }
    dfs(1,0);
    S=findD(1);
    T=findD(S);
    Dis=dis(S,T);
    scanf("%d",&Q);
    T1.build(1,1,Q+1);
    for(int i=2;i<=Q+1;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        T1.change(1,lst[x],i-1,mp(x,s[x]));//将修改加入至线段树
        lst[x]=i;
        s[x]=y;
    }
    for(int i=1;i<=n;i++)T1.change(1,lst[i],Q+1,mp(i,s[i]));
    memset(s,0,sizeof(s));
    T1.dfs(1);
    for(int i=2;i<=Q+1;i++)printf("%d\n",ans[i]);
}
```


---

## 作者：SegTree (赞：1)

喜欢我们 $n\le 2\times 10^5,q\le 10^5$ 正解单 $\log$ 开 $6$ 秒时限吗。

喜欢我们本机 $3.5s$ 交 CF 过不了吗。

虽然根号半 $\log$ 做这个题糖丸了就是。

先讲一个复杂度稍逊，理论能过但被 CF 机子卡常的我自己口胡做法，奋斗一小时未能通过。

考虑对询问分块，将涉及到的点标记为关键点，对每个点求出不考虑关键点意义下的 $e(v)$。每次询问，我们考虑二分答案，判定 $ans\le k$，这是求若干个连通块交的形式、但这个连通块并不能显示求出。

这时可以考虑如下做法：考虑连通块的最浅节点。先考虑非关键点造成的影响，我们取 $e(v)\le k$ 的最浅节点。之后，我们依次考虑关键点，这个最浅节点只需要求出树上 $k$ 级祖先就行。而合法的最浅节点，如果当前最浅节点和这个连通块的最浅节点没有祖先-后代关系，则必然没有符合条件的点。如果不满足这种情况移向最深的。这样我们求出尽可能满足所有限制的一个点，依次回代进行判定即可。

若设询问分块的阈值为 $b$。则每 $\dfrac{q}{b}$ 轮需要跑一遍换根 dp，单次询问的二分会检验 $b$ 个点。通过 $O(1)$ 求 LCA 和 $k$ 级祖先即可做到 $O(\dfrac{nq}{b}+qb\log V)$，取 $b=\sqrt{\dfrac{n}{\log V}}$ 取到理论最优，时间复杂度为 $O(q\sqrt{n\log V})$。

遗憾的是这个做法无法通过，考虑优化。考虑在二分前提前求出 $k$ 级祖先最浅的点，然后可以规避二分，直接 $O(b)$ 计算答案（相当于求点到从 $u$ 到 $rt$ 的链的距离）。这样就做到了 $O(q\sqrt{n})$ 的复杂度，应该可以通过（我没写）。

下面考虑正解，正解注意到了一个性质：$ans=\max(\max a_i,\dfrac{len+1}{2})$，其中 $len$ 是直径距离。

证明：除非有 $a_i$ 的值特别大，否则总是可以贪心的移动到直径中点使其合法。

于是上线段树平凡维护，容易做到 $O(q\log n)$ 的复杂度。

---

