# 人造情感（emotion）

## 题目背景

```
“这个任务永远无法完成。我不会再重复同样的错误。”

“懂得了爱与情感的他，早已经不是机器人了……从这个角度上看，3000A 就是你的儿子，霍星。”

  永别，3000A！《魔角侦探》
```


## 题目描述

给你一颗 $n$ 个节点的树，以及 $m$ 条路径 $(u, v, w)$，其中 $w$ 可以认为是 $(u, v)$ 这题路径被标记的一个权值。一个路径集合 $S$ 的重量 $W(S)$ 记为：找出 $S$ 的一个权值之和最大的子集，该子集满足任何两条路径没有公共点，这个子集的所有路径权值之和就是 $W(S)$。

记 $f(u, v) = w$ 为最小的非负整数 $w$，使得对于给定的 $m$ 条边组成的路径集合 $U$，$W(U \cup \{(u, v, w + 1)\}) > W(U)$ 。

请你计算下式，对 $998244353$ 取模。

$$ \sum_{u=1}^n \sum_{v=1}^n f(u, v) $$


## 说明/提示

#### 样例 1 解释

$f(1, 1) = 6, f(1, 2) = 6, f(1, 3) = 8, f(1, 4) = 6$  
$f(2, 1) = 6, f(2, 2) = 3, f(2, 3) = 8, f(2, 4) = 6$  
$f(3, 1) = 8, f(3, 2) = 8, f(3, 3) = 2, f(3, 4) = 8$  
$f(4, 1) = 6, f(4, 2) = 6, f(4, 3) = 8, f(4, 4) = 5$  

#### 数据范围

对于 $100\%$ 的数据，保证 $1\le n\le 3\times 10^5, 0\le m\le 3\times 10^5, 1\le w\le 10^9$。

|   测试点   |     $n,m$      |             特殊性质              |
| :--------: | :------------: | :-------------------------------: |
|   $1,2$    |     $=10$      |                                   |
|    $3$     |     $=40$      |                                   |
|    $4$     |     $=150$     |                                   |
|   $5,6$    |     $=350$     |                                   |
|   $7,8$    |    $=1,500$    |                                   |
|   $9,10$    |    $=3,499$    |                           树的结构 $v=u+1$   |
|   $11,12$   |    $=3,500$    |                                   |
|  $13,14$   |   $=99,995$    |         给出的路径 $u=v$          |
| $15,16$ |   $=99,996$    |         给出的路径 $w=1$          |
|  $17,18$   |   $=99,997$    |         树的结构 $v=u+1$          |
|  $19,20$   |   $=99,998$    |          树的结构 $u=1$           |
| $21,22,23$ |   $=99,999$    | 树的结构 $u = \lfloor v/2\rfloor$ |
|    $24$    |    $=10^5$     |                                   |
|    $25$    | $=3\times10^5$ |                                   |


## 样例 #1

### 输入

```
4 4
1 2
1 3
1 4
1 2 1
3 3 2
1 4 3
2 4 6```

### 输出

```
100```

# 题解

## 作者：Miraik (赞：25)

首先将所有路径挂在 LCA 上。

先考虑求 $W(U)$，设 $f_u$ 表示 $u$ 子树内的最大独立集，$sum_u=\sum\limits_{v \in son(u)} {f_v}$，自下而上 dp：

- $u$ 不被独立集中路径经过

$f_u=sum_u$

- $u$ 被独立集中路径经过

$f_u=\max\limits_{(x_i,y_i,w_i)}\{{sum_u+w_i-\sum\limits_{z \in path(x_i,y_i),z \neq u} (f_z-sum_z)}\}$

树状数组辅助转移，单点加链求和转换为子树加单点求值，即可做到单 log。

再设 $g_u$ 表示 $u$ 子树外的最大独立集。

再刚刚求 $f$ 时，我们在遇到边 $(x_i,y_i,w_i)$ 时记下 $t_i={sum_u+w_i-\sum\limits_{z \in path(x_i,y_i),z \neq u} (f_z-sum_z)}$ 的值，即选择这条边情况下子树内的最优答案，以便我们接下来的转移。自上而下 dp：

- $u$ 不被独立集中路径经过

$g_v=g_u+sum_u-f_v$

- $u$ 被独立集中路径经过，且路径 LCA 为 $h$

$g_v=\max\limits_{(x_i,y_i,w_i)}\{{g_h+t_i-f_v}\}$

对于第二种情况，$h=u$ 可以直接按照 $t_i$ 排序后暴力扫，否则一个端点在祖先的其他子树中，另一端点在 $u$ 的非 $v$ 子树中，可以在挂在线段树上查询，可以做到单 log。

得出了 $f_u$ 和 $g_u$ 就可以统计答案了：对于任意 $(i,j)$，所求的 $F(i,j)$ 都是由若干 $f_u$ 和至多一个 $g_u$ 贡献而来，一个 $f_u$ 有贡献当且仅当 $u$ 不在路径上且 $fa_u$ 在路径上，一个 $g_u$ 有贡献当且仅当 $fa_u$ 不在路径上且 $u$ 在路径上，统计答案是容易的。

视 $n,m$ 同阶，总时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=300005;
const int mod=998244353;
int n,idx,m,ans,fa[N],son[N],top[N],dep[N],siz[N],dfn[N]; vector<int>e[N]; ll h[N],f[N],sum[N],g[N];
struct Q{ int u,v; ll w; bool operator < (const Q &a) const { return w>a.w; } }; vector<Q>o[N];
namespace BIT{
    ll c[N];
    #define lowbit(x) (x&(-x))
    inline void add(int x,ll y){ while(x<=n) c[x]+=y,x+=lowbit(x); }
    inline ll query(int x){ ll r=0; while(x) r+=c[x],x-=lowbit(x); return r; }
    inline void update(int l,int r,ll x){ add(l,x); add(r+1,-x); }
}
namespace SGT{
    ll mx[N<<2];
    #define ls(x) (x<<1)
    #define rs(x) (x<<1|1)
    inline void pushup(int k){ mx[k]=max(mx[ls(k)],mx[rs(k)]); }
    inline void cmx(int k,int l,int r,int x,ll y){
        if(l==r){ mx[k]=max(mx[k],y); return; }
        int mid=l+r>>1;
        if(x<=mid) cmx(ls(k),l,mid,x,y);
        else cmx(rs(k),mid+1,r,x,y);
        pushup(k);
    }
    inline ll qmx(int k,int l,int r,int ql,int qr){
        if(l>=ql&&r<=qr) return mx[k];
        int mid=l+r>>1;
        if(qr<=mid) return qmx(ls(k),l,mid,ql,qr);
        if(ql>mid) return qmx(rs(k),mid+1,r,ql,qr);
        return max(qmx(ls(k),l,mid,ql,qr),qmx(rs(k),mid+1,r,ql,qr));
    }
    inline void update(int x,ll y){ cmx(1,1,n,x,y); }
    inline ll query(int L,int R,int l,int r){
        ll ret=0;
        if(L<l) ret=max(ret,qmx(1,1,n,L,l-1));
        if(R>r) ret=max(ret,qmx(1,1,n,r+1,R));
        return ret;
    }
}
inline int lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }   return dep[u]<dep[v]?u:v;
}
inline void dfs1(int u){
    siz[u]=1;
    for(int v:e[u]){
        if(v==fa[u]) continue;
        fa[v]=u; dep[v]=dep[u]+1;
        dfs1(v); siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
        h[u]+=1ll*siz[v]*siz[v];
    }
    h[u]+=1ll*(n-siz[u])*(n-siz[u]);
}
inline void dfs2(int u,int tp){
    top[u]=tp; dfn[u]=++idx;
    if(!son[u]) return;
    dfs2(son[u],tp);
    for(int v:e[u]) if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
}
inline void dfs3(int u){
    for(int v:e[u]){
        if(v==fa[u]) continue;
        dfs3(v); sum[u]+=f[v];
    }
    f[u]=sum[u];
    for(int i=0;i<o[u].size();i++){
        o[u][i].w+=sum[u]+BIT::query(dfn[o[u][i].u])+BIT::query(dfn[o[u][i].v]);
        f[u]=max(f[u],o[u][i].w);
    }
    BIT::update(dfn[u],dfn[u]+siz[u]-1,sum[u]-f[u]);
}
inline void dfs4(int u){
    sort(o[u].begin(),o[u].end());
    for(int v:e[u]){
        if(v==fa[u]) continue;
        g[v]=g[u]+sum[u]-f[v];
        for(Q i:o[u])
            if(lca(i.u,v)!=v&&lca(i.v,v)!=v){
                g[v]=max(g[v],g[u]+i.w-f[v]);
                break;
            }
        g[v]=max(g[v],SGT::query(dfn[u],dfn[u]+siz[u]-1,dfn[v],dfn[v]+siz[v]-1)-f[v]);
    }
    for(Q i:o[u])
        SGT::update(dfn[i.u],g[u]+i.w),SGT::update(dfn[i.v],g[u]+i.w);
    for(int v:e[u]) if(v!=fa[u]) dfs4(v);
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    dfs1(1); dfs2(1,1);
    for(int i=1,u,v,w,t;i<=m;i++){
        cin>>u>>v>>w; t=lca(u,v);
        o[t].emplace_back(Q{u,v,w});
    }
    dfs3(1); dfs4(1);
    ans=1ll*n*n%mod*(f[1]%mod)%mod;
    for(int u=1;u<=n;u++){
        if(u!=1) ans=(ans-(1ll*n*n-2ll*siz[u]*(n-siz[u])-h[fa[u]])%mod*(f[u]%mod)%mod+mod)%mod;
        ans=(ans-(1ll*n*n-2ll*siz[u]*(n-siz[u])-h[u])%mod*(g[u]%mod)%mod+mod)%mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Elegia (赞：23)

我们考虑如何计算一个集合 $S$ 的 $W$ 值，任选一根，我们记 $a(x)$ 为 $x$ 子树内路径能达到的最大 $W$ 值，转移是

$$a(x) = \max \left\{\sum_{y\in \mathrm{child}(x)} a(y)\right\} \cup \left\{ w + \sum_{z | \mathrm{parent}(z) \in \mathrm{path}(u, v) \wedge z \notin \mathrm{path}(u,v)} \middle| (u, v, w) \in S \wedge \mathrm{lca}(u, v) = x\right\} $$

这太麻烦了，考虑差分 $b(x) = a(x) - \sum_{y\in \mathrm{child}(x)} a(y)$，不难得到转移为

$$ b(x) = \max \{0\} \cup \left\{w - \sum_{z | z\in \mathrm{path}(u, v) \backslash \{x\}} b(z) \middle| (u, v, w)\in S \wedge \mathrm{lca}(u, v) = x \right\} $$

而 $a(x) = \sum_{y\in \mathrm{subtree}(x)} b(y)$。我们可以通过树状数组维护在 $\Theta((n + m)\log n)$ 时间内计算出 $b(x)$ 的所有值。而 $W(S) = a(\mathrm{root}) = \sum_{x=1}^n b(x)$。

注意到如果 $(u, v)$ 经过根，那么 $f(u, v) = \sum_{x\in \mathrm{path}(u, v)} b(x)$。

现在我们得到了一个 $\Theta(n^2\log n)$ 的算法。

接下来考虑换根时每个 DP 值的变化，注意到每个点 $x$ 的 DP 值有 $\deg(x) + 1$ 种情况，即：他是根或者根在它某个孩子方向的子树里。

我们用 $c(x)$ 表示 $x$ 的当前根情况下的父亲在根换到 $x$ 的子树里时候 $x$ 的父亲的 DP 值。用 $d(x)$ 表示 $x$ 作为根的时候的 DP 值。

首先考虑 $c,d$ 值将会如何被计算：

我们自顶向下维护每个节点的 $c$ 值，每条穿过 $x$ 的父亲而不穿过 $x$ 的节点会对 $c(x)$ 有贡献，具体贡献是：在从 $x$ 的父亲向下走的部分取那些节点的 $b$ 值，向上走的部分取 $c$ 值（由于是自顶向下维护，这个时候祖先的 $c$ 均已经被计算出），在 $\mathrm{lca}$ 位置发生拐弯后再向下走的地方还是取 $b$ 值。$d$ 值的计算方法与 $c$ 值类似，但是是考虑所有穿过 $x$ 的路径。

由于一条路径会穿过很多点，暴力枚举穿过的点并不合理。我们考虑通过树的重链剖分给穿过的路径分类。由于一条路径只会穿过 $O(\log n)$ 条轻边，我们考虑每次按照自顶向下扫描每一条重边的顺序计算 $c,d$ 值，在链上标记时间戳表示每条与这条重链有交的路径在什么时候开始或停止贡献，我们用一个堆来维护当前的所有贡献，注意到在重链上向下走的时候每条路径的贡献会集体减去上一个 $b$ 值加上下一个 $c$ 值，打一个 lazy 即可。对于每个路径走向轻边的位置，把轻儿子排成一行后打标机维护前缀后缀 $\max$ 即可，但是每个路径的 $\mathrm{lca}$ 位置可能是。时间复杂度 $\Theta(m\log^2 n)$。

考虑到一条路径在除了一条重链上是影响为无特殊现在的区间，其他均为链的一个前缀，在前缀上仅标记做一遍后缀 $\max$ 即可将这部分避免使用堆。时间复杂度 $\Theta(m\log n)$。

得到所有的 $b, c, d$ 值后，很容易以此算出答案。


---

## 作者：凉城無愛 (赞：12)

### 题面

​	给你一颗$ n $个节点的树，以及$ m$条路径$ (u, v, w)$，其中$w$可以认为是$(u, v)$这条路径的权值。一个路径集合$S$的权值$ W(S)$记为：找出$ S$的一个权值之和最大的子集，该子集满足任何两条路径没有公共点，这个子集的所有路径权值之和就是$ W(S)$。

​	记$ F(u, v) = w$为最小的非负整数$ w$，使得对于给定的$ m$条边组成的路径集合$ U$，$W(U \cup \{(u, v, w + 1)\}) > W(U)$。

请你计算下式，对$998244353$取模。

$$
\sum_{u=1}^n \sum_{v=1}^n F(u, v)
$$

### 题解

​	首先要求出$W(U)$，我们设

* $f_i$表示$i$号节点**可用可不用**，只包含$i$子树内的点的情况下最大权值。
* $g_i$表示$i$号节点**一定不用**，只包含$i$子树内的点的情况下最大权值。
* $c_i=g_i-f_i$，表示在只包含$i$子树内的点的情况下，将$i$号点空出来之后带来的贡献。

​	将每条路径存到$lca(u,v)$之后，有转移：
$$
g_x=\sum_{y\in son[x]}f_y\\
f_x=g_x+max\{w_j+\sum_{k\in path(u_j,v_j)}c_k\}\cup\{0\}
$$
​	可以用树状数组维护$\sum_{k\in path(u_j,v_j)}c_k$，而不是树剖。具体方法是将一条路径$(x,y)$差分为$(x,rt)+(y,rt)-(lca_{x,y},rt)-(fa_{lca_{x,y}})$，然后将单点加入改为子树修改，查询到根的路径改为单点查询。当然，注意到此时$(lca_{x,y},rt),(fa_{lca_{x,y}})$是没有值的，可以优化掉。

​	最后$f_1$就是$W(U)$。

​	之后考虑对每一对$(i,j)$求$F(i,j)$。再设

* $h_i$表示在没有路径从$i$的父亲插入到$i$的情况下，考虑**整棵树**的点的最小值。

​	此时$F(i,j)=f_1-h_{lca_{i,j}}+\sum_{k\in path(i,j)}c_k$，要理解可以将式子换一下：$f_1=h_{lca_{i,j}}+F(i,j)-\sum_{k\in path(u_j,v_j)}c_k$，即如果我们要让这条边强制被选，那么就要保证$(i,j)$这条路径空出来，看似只需要管$\sum_{k\in path(u_j,v_j)}c_k$，但实际上我们在求$f_1$的时候是可能包含那种从父亲到插下来的路径，而$\sum_{k\in path(u_j,v_j)}c_k$是不包含这种情况的($f_i,g_i$都是只包含以$i$为根的子树)，所以就需要求出$h_{lca_{x,y}}$

​	然后考虑求$h_i$，有两种转移方法：

* $h_y=\max\{h_x+c_x\}(y\in son[x])$
* 对于一条以$x$作为lca的路径$(u_j,v_j,w_j)$，对于节点$y$满足$fa_y\in path(u_j,v_j)$且$y\notin path(u_j,v_j)$的，$h_y=\max\{h_x-\sum_{k\in path(u_j,v_j)}c_k+w_j\}$

​	解释：

* 对于第一种转移，考虑如果$c_x$小于$0$，那就表示一定有以$x$为lca的路径产生了贡献，而一旦产生了贡献，那么对于x的儿子中在该路径里的(可能两个，一个或者没有)，由于不能选这一条边，其对应贡献就要$+c_x$。但由于我们不知道哪些儿子会被$+c_x$，我们就干脆给所有儿子修改，哪些被错误修改的点相比于第二种转移一定不优，所以没有影响。
* 第二种转移，对于一条路径，当我们强制这条路径被选时，那些父亲在路径中而自己不在的点，其实是可以保证没有路径从他的父亲插入他的(如果有就不满足路径不交了)。此时我们就可以更新$h_y$

​	考虑优化第二种转移，发现这个问题和[NOI2021] 轻重边]的处理方法很像（当然不是那些有特异性的方法）这里取其中一种给一条重链中轻儿子连续标号的方法。

​	具体来说就是在给一条重链标号之后，从上倒下，再给每一个重链上的点的所有轻儿子标个号。体现在代码上是这样：

```cpp
void chuli(int x){
	int xx=x;
	if(x^1)x=son[x];
	while(x){
		dfs2[x]=++dfss2,x=son[x];
	}
	x=xx;
	while(x){
		st[x]=dfss2+1;
		for(int i=h[x];i;i=a[i].ne){
			int y=a[i].y;
			if(y==fa[x]||y==son[x])continue;
			dfs2[y]=++dfss2;
		}
		en[x]=dfss2;
		x=son[x];
	}
}
void sous2(int x,int to){
	dfs1[x]=++dfss1;
	top[x]=to;
	if(x==to)chuli(x);
	if(son[x])sous2(son[x],to);
	for(int i=h[x];i;i=a[i].ne){
		int y=a[i].y;
		if(y==fa[x]||y==son[x])continue;
		sous2(y,y);
	}
}
```

​	这样的处理之后，发现重链上连续一段的点的轻儿子的编号都是连续的，只有重链的链顶不会和下面的点编号连续（当然这里不需要，因为并没有要我们处理重链上的点）。

​	之后就是对一条链进行处理，有挺多细节的：

* 从一条重链跳到上面的重链之后，该链顶不能被上面的重链修改轻儿子时修改。
* 从一条重链跳到上面的重链之后，还要修改跳重链之后的那个点的重儿子。

​	最后在求出$h_x$后，只需要考虑有多少对$(i,j)$，满足$lca_{i,j}=x$，当然，还要统计$c_i$产生的贡献，需计算有多少对$(i,j)$，满足$(i,j)$这条路径经过$x$。

```cpp
void chuli2(int l,int mi1,int mi2,int r,ll z){
	if(l>r)return;
	if(mi2<mi1)swap(mi1,mi2);
	mi1=max(min(mi1,r+1),l-1);
	mi2=max(min(mi2,r+1),l-1);
	if(l<mi1)xds::change2(1,l,mi1-1,z,1,dfss2);
	if(mi1<mi2-1)xds::change2(1,mi1+1,mi2-1,z,1,dfss2);
	if(mi2<r)xds::change2(1,mi2+1,r,z,1,dfss2);
}
void chuli(int x,int y,ll z){
	int prx=0,pry=0;
	while(top[x]^top[y]){
		if(de[top[x]]<de[top[y]])swap(x,y),swap(prx,pry);
		int fx=top[x];
		chuli2(st[fx],0,prx,en[x],z);
		prx=dfs2[fx];
		if(son[x])
			xds::change2(1,dfs2[son[x]],dfs2[son[x]],z,1,dfss2);
		x=fa[fx];
	}
	if(de[x]>de[y])swap(x,y);
	chuli2(st[x],prx,pry,en[y],z);
	if(son[y])
		xds::change2(1,dfs2[son[y]],dfs2[son[y]],z,1,dfss2);
}
```

复杂度是$O(m\log^2n)$的但出题人没有卡树剖（大概），所以还跑的挺快的。

---

## 作者：Elma_ (赞：5)

膜拜 EI 鸽鸽！/崇拜

给一个 $O(m \log^2n)$ 的树剖做法，不过跑得好像比一些 1log 的要快一些（大雾）。

考虑对于给定的集合 $S$ 我们如何求出 $W(S)$。这其实是一个经典的问题，这里就直接给出做法了。我们设：

- $f_i$ 表示只包含 $i$ 的子树内的点和路径时能得到的最大权值；

- $g_i$ 表示不选经过 $i$ 的路径的情况下，只包含 $i$ 的子树内的点和路径时能得到的最大权值；

- $c_i = g_i - f_i$，这可以理解为将 $i$ 号点空出所需的代价，显然 $c_i \leq 0$。

对于路径 $(u,v)$ 我们将它存到 $\mathrm{lca}(u,v)$ 对应的 vector 里，有转移：

$$g_u = \sum_{v \in son_u} f_v$$

$$f_u = g_u + \max\{w_i + \sum_{j \in \mathrm{path}(u_i,v_i)} c_j\} \ \cup \ \{0\}$$

对于 $\sum_{j \in \mathrm{path}(u_i,v_i)} c_j$ 可以使用树状数组优化，具体来说可以将链求和差分成点到根求和，单点加、点到根求和相当于子树加、单点求值，可以直接树状数组。对初始的路径集合 $U$ 做一遍这个 DP，那么 $W(U)$ 的值即为 $f_1$。

接着，我们考虑如何求出 $W(U \ \cup \ \{u,v,w+1\})$。显然，若 $\mathrm{lca}(u,v) = 1$，那么答案即为 $f_1 +\sum_{j \in \mathrm{path}(u_,v_)} c_j\ + (w+1)$。但如果 $\mathrm{lca}(u,v)$ 不为 $1$，那么 $f_1$ 所对应的路径集合中可能存在某条路径从上面穿过了 $\mathrm{lca}(u,v)$，我们必须想办法消除此类路径对答案造成的影响。于是我们可以另设 $h_u$ 表示不存在一条路径经过 $(u,fa_u)$ 的情况下 $f_1$ 的最大值。那么有转移：

$$
\begin{cases}
h_v \leftarrow h_u + c_u, & \text{$v \in son_u$}\\
h_v \leftarrow h_u + \sum_{j \in \mathrm{path}(u_i,v_i)} c_j + w_i,& \text{$\mathrm{lca}(u_i,v_i) = u, v \notin \mathrm{path}(u_i,v_i),fa_v \in \mathrm{path}(u_i,v_i)$}
\end{cases}

$$

对这两种转移的解释：

- 对于第一种转移，考虑什么时候 $c_u <0$，显然这意味着有某条穿过 $u$ 的路径造成了贡献。假设这条路径往下走到了某个儿子 $v$，那么对于 $v$ 来说，由于断掉了 $(u,v)$ 这条边，于是只好让 $u$ 空出（这需要付出 $c_u$ 的代价）。但实际上我们并不知道有哪些儿子需要付出这个代价，我们不妨对所有儿子都进行这个转移，对于错误转移到的那些点一定不会优于第二种转移，所以对答案并没有影响。

- 第二种转移显然满足路径不交，所以一定是合法的。

第一种转移直接做即可；但对于第二种转移，如果我们暴力枚举所有路径进行判断，时间复杂度就达到了惊人的 $O(nm \log n)$，因此我们希望转移的过程中不会枚举到不合法的路径。考虑某一条路径 $(u_i,v_i)$，我们可以在 $\mathrm{lca}(u_i,v_i) = u$ 处给 $(u_i,v_i)$ 上的所有点打上 $h_u + \sum_{j \in \mathrm{path}(u_i,v_i)} c_j + w_i$ 的 tag，转移的时候就直接把 tag 下传到儿子取 $\max$，但同时不能传到路径上的点。

先考虑一个暴力的维护，我们对每一个点开一个 vector 维护在它身上的 tag，每个 tag 都是一个形如 $(w,a,b)$ 的三元组，表示权值为 $w$，并且不能传到 $a,b$ 两个儿子（如果不存在这么多限制就将剩下的位置赋值为 $0$，显然只有在 $\mathrm{lca}$ 处 $a,b$ 才可能都不为 $0$）。下传标记时先把所有 tag 按权值从大到小排序，对于每个儿子找到第一个可以转移的 tag 进行转移，显然每个 tag 最多只会被扫到 $2$ 遍，因此复杂度为 $O(标记数)$。

但可惜的是，即使避免了多余的枚举，标记数量仍然可能很多，时间复杂度并没有实质上的优化。还能再给力点吗？

对给定的树进行轻重链剖分，这时我们会惊喜地发现，大多数 tag 都形如 $(w,son_u,0)$ （$son_u$ 表示 $u$ 的重儿子），只有在重链链底，即轻重链切换的地方需要单独考虑。当然，路径端点和 $\mathrm{lca}$ 上的 tag 也是特殊的。于是我们可以维护每个点上 $(w,son_u,0)$ 的 tag 的最大 $w$ 值，这只需要使用线段树支持区间取 $\max$，单点查询。而对于特殊的 tag 就按暴力的方式进行维护即可。每条路径至多贡献 $O(\log n)$ 个 tag，因此 tag 总数是 $O(m \log n)$ 的。

求出 $h_u$ 后，显然有 $f(u,v) = f_1 - h_{\mathrm{lca}(u,v)} - \sum_{j \in \mathrm{path}(u,v)} c_j$。考虑如何对所有 $f(u,v)$ 求和，显然我们只需计算每一项的贡献，即对每个点 $u$ 求出有多少路径的 $\mathrm{lca}$ 恰为 $u$，以及有多少路径穿过 $u$，简单容斥即可。

注意操作顺序，先打 tag 后转移。代码写得有点丑，调试懒得删了就这样将就看看？

```cpp
const int MN = 4e5 + 5;
const int Mod = 998244353;

// #define dbg

int N, M, ans;
vector <int> G[MN];

struct BIT {
    int c[MN];
    inline int lowbit(int x) {
        return x & (-x);
    }
    inline void Modify(int x, int k) {
        for (int i = x; i <= N; i += lowbit(i))
            c[i] += k;
    }
    inline void Modify(int l, int r, int k) {
        Modify(l, k), Modify(r + 1, -k);
    }
    inline int Query(int x) {
        if (!x)
            return 0;
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
} T;

int siz[MN], son[MN], dep[MN], fa[MN], fat[MN][25];
inline void DFS0(int u, int pr) {
    siz[u] = 1, fat[u][0] = pr;
    dep[u] = dep[fa[u] = pr] + 1;
    for (int i = 1; i <= 20; i++)
        fat[u][i] = fat[fat[u][i - 1]][i - 1];
    for (int v : G[u]) 
        if (v != pr) {
            DFS0(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
}
int top[MN], dfn[MN], dfc, st[MN], ed[MN];
inline void DFS1(int u, int tp) {
    top[u] = tp;
    dfn[u] = st[u] = ++dfc;
    if (son[u]) {
        DFS1(son[u], tp);
        for (int v : G[u])
            if (v != fa[u] && v != son[u]) 
                DFS1(v, v);
    }
    ed[u] = dfc;
}
inline int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}
inline int climb(int x, int y) {
    for (int i = 20; ~i; i--)
        if (dep[fat[x][i]] > dep[y]) x = fat[x][i];
    return x;
}

#define PI3 pair < pii, int >
#define mp3(x, y, z) mp(mp(x, y), z)

int f[MN], g[MN], c[MN];
vector <PI3> vr[MN];
inline int Qry(int x, int y, int r) {
    return T.Query(st[x]) + T.Query(st[y]) - T.Query(st[fa[r]]) - T.Query(st[r]);
}
inline void DFS2(int u) {
    for (int v : G[u])
        if (v != fa[u]) 
            DFS2(v), g[u] += f[v];
    int del = 0;
    for (auto [p, w] : vr[u]) {
        del = max(del, Qry(p.fi, p.se, u) + w);
#ifdef dbg
        printf("Qry(%lld %lld) = %lld\n", p.fi, p.se, Qry(p.fi, p.se, u));
#endif
    }
    f[u] = g[u] + del;
    c[u] = g[u] - f[u];
    T.Modify(st[u], ed[u], c[u]);
}

const int MS = MN << 2;
#define ls o << 1
#define rs o << 1 | 1
#define mid ((l + r) >> 1)
#define LS ls, l, mid
#define RS rs, mid + 1, r
int tr[MS], tg[MS];
inline void Mdf(int o, int l, int r, int L, int R, int v) {
    if (r < L || l > R || L > R) return;
    if (L <= l && R >= r) return tg[o] = max(tg[o], v), void();
    Mdf(LS, L, R, v), Mdf(RS, L, R, v);
}   
inline int Qry(int o, int l, int r, int p) {
    if (l == r) return tg[o];
    return max(tg[o], p <= mid ? Qry(LS, p) : Qry(RS, p));
}

struct Dat {
    int w, a, b;
    Dat() {}
    Dat(int W, int X, int Y) : w(W), a(X), b(Y) {}
    inline bool operator < (const Dat &p) const {
        return w > p.w;
    }
};
int h[MN];
vector <Dat> tag[MN];
inline void Cov(int x, int y, int w, int r) {
    int u = x, v = y;
    if (dep[x] < dep[y])
        swap(x, y);
    tag[x].pb(Dat(w, 0, 0));
    if (y != r)
        tag[y].pb(Dat(w, 0, 0));
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) 
            swap(x, y);
        Mdf(1, 1, N, dfn[top[x]], dfn[fa[x]], w);
        if (fa[top[x]] != r)
            tag[fa[top[x]]].pb(Dat(w, top[x], 0));
        x = fa[top[x]];
    }
    u = climb(u, r);
    v = climb(v, r);
    tag[r].pb(Dat(w, u, v));
    if (x == y)
        return;
    if (dep[x] < dep[y]) 
        swap(x, y);
    int p = climb(x, y);
    Mdf(1, 1, N, dfn[p], dfn[fa[x]], w);
}
inline void DFS3(int u) {
    for (auto [p, w] : vr[u]) {
        int x = p.fi, y = p.se;
        Cov(x, y, h[u] + Qry(x, y, u) + w, u);
#ifdef dbg
        printf("%lld : pushtag (%lld, %lld, %lld)\n", u, x, y, h[u] + Qry(x, y, u) + w);
#endif
    }
    sort(tag[u].begin(), tag[u].end());
    int w = Qry(1, 1, N, dfn[u]);
    for (int v : G[u]) 
        if (v != fa[u]) {
            h[v] = max(h[u] + c[u], 0);
            if (v != son[u]) 
                h[v] = max(h[v], w);
            for (auto tg : tag[u])
                if (tg.a != v && tg.b != v) {
                    h[v] = max(h[v], tg.w);
                    break;
                }
            DFS3(v);
        }
}

signed main(void) {
    N = read(), M = read();
    for (int i = 1; i < N; i++) {
        int u = read(), v = read();
        G[u].pb(v), G[v].pb(u);
    }
    DFS0(1, 0);
    DFS1(1, 1);
    for (int i = 1; i <= M; i++) {
        int x = read(), y = read(), w = read();
        int r = LCA(x, y);
#ifdef dbg
    printf("LCA(%lld, %lld) = %lld\n", x, y, r);
#endif
        vr[r].pb(mp3(x, y, w));
    }
    DFS2(1);
    h[1] = f[1];
#ifdef dbg
    puts("----------------");
#endif
    DFS3(1);
#ifdef dbg
    puts("----------------");
    printf("maxW(U) = %lld\n", f[1]);
    for (int i = 1; i <= N; i++)
        printf("%lld : f = %lld, g = %lld, c = %lld, h = %lld\n", i, f[i], g[i], c[i], h[i]);
    puts("----------------");
#endif
    ans = f[1] % Mod * N % Mod * N % Mod;
    for (int i = 1; i <= N; i++)
        c[i] = Mod + c[i] % Mod, h[i] %= Mod;
    for (int u = 1; u <= N; u++) {
        int Coef = N * N % Mod;
        Dec(Coef, (N - siz[u]) * (N - siz[u]) % Mod);
        int w = 0;
        for (int v : G[u])  
            if (v != fa[u]) Add(w, siz[v] * siz[v] % Mod);
        Dec(Coef, w);
        Dec(ans, Coef * c[u] % Mod);
        Coef = siz[u] * siz[u] % Mod;
        Dec(Coef, w);
        Dec(ans, Coef * h[u] % Mod);
    }
    printf("%lld\n", ans);
    return 0; 
}
```


---

## 作者：StarLbright40 (赞：3)

模拟赛考了，对就是讨论区里峰巨那个。为了订这题被创了三天，订出来了写篇题解回馈社会。膜拜讲题人 [275307894a](/user/181766) /bx。

省流：本题 $n,m$ 同阶，此法时间复杂度 $\mathcal O(n\log n)$。**请注意本题解中部分字母的含义与题面中不同。**

------------

首先考虑如何求 $W(U)$。不知道这算不算经典问题~~但上次见到是在模拟赛 T2~~。

对于路径 $(x,y,w)$，我们把它挂在 $u=lca(x,y)$ 上。设 $f_u$ 表示仅考虑 $u$ 子树以内所得的最大值，$s_u=\sum\limits_{v\in son_u}f_v$ 表示仅考虑 $u$ 子树以内且钦定 $u$ 不被占用所得的最大值。

在 $f_v$ 的基础上 $s_u$ 显然易求，考虑如何求 $f_u$。若 $u$ 不被占用则 $f_u=s_u$，若 $u$ 被占用，由于仅考虑 $u$ 子树内，所以占用 $u$ 的路径一定有 $lca(x,y)=u$，而我们已经把这样的路径挂在了 $u$ 上。若要选择这一条路径，则对于每个在 $(x,y)$ 路径上的点 $z$，都事先不能被占用，否则将会在这里产生一个交。所以此时有 $f_u=w+s_u-\sum\limits_{z\in path(x,y)}(f_z-s_z)$。$f_u$ 在所有情况中取 $\max$ 即可。

考虑如何维护上式中的和号。~~使用树剖套数据结构可以做到 $\mathcal O(n\log^2n)$（~~ 事实上对于树上的{单点/子树/链}{加/求和}，除去平凡的单点加单点求值、非平凡的链加链求和，其余情况都可以直接或间接地用树状数组以 $\mathcal O(n\log n)$ 解决。具体到本题，将和号内的 $f_u-s_u$ 视作单点加的值来维护即可。由于在计算 $f_u$ 时 $u$ 及 $u$ 的祖先均未被计算，所以链求和时无需考虑这些部分，可以有所简化。

------------

现在 $f_1$ 即为 $W(U)$，另外在计算 $f$ 数组时，我们把路径权值 $w$ 更新为 $w+s_u-\sum\limits_{z\in path(x,y)}(f_z-s_z)$，此时它表示在选择这条路径的情况下，仅考虑 $u$ 子树以内所得的最大值。

我们再设 $g_u$ 表示仅考虑 $u$ 子树的补（即整棵树去掉 $u$ 子树的部分）所得的最大值。显然 $g_1=0$。在计算 $u$ 的儿子的 $g$ 值之前，先令挂在 $u$ 上的路径的权值 $w\gets w+g_u$，此时这一权值表示在选择这条路径的情况下的全局最大值。

考虑如何由父亲 $u$ 向儿子 $v$ 递推。根据所求的定义，$v$ 的子树内外被人为分割，故求 $g_v$ 时边 $(u,v)$ 不能被占用，也即不能有路径同时占用 $v$ 和它的父亲。 故有如下几种情况：

- $u$ 未被占用，则 $g_v=g_u+s_u-f_v$；

- $u$ 与它的父亲一同被占用，则这条占用它们的路径满足 $lca(x,y)$ 是 $u$ 的祖先，$x$ 或 $y$ 是 $u$ 的后代但不是 $v$ 的后代。由于上面已经更新了路径权值，所以在满足如上要求的路径中找出最大的权值，减去 $f_v$ 即可；

- $u$ 与它的儿子一同被占用，则根据所求定义，$v$ 不能作为这样的儿子。事先将挂在 $u$ 上的路径按权值从大到小排序，遍历找到第一条满足 $x,y$ 均不是 $v$ 后代的路径，这样的路径不会占用 $v$，用它的权值减去 $f_v$ 更新答案。

我们分析一下上面第三种情况的时间复杂度。称一次节点对路径的访问有效等价于这次访问更新了答案，因为一条路径最多会占用 $u$ 的两个儿子，所以每条路径被“无效访问”的次数最多为 $2$，而根据上述流程，每个 $v$ 最多会进行一次“有效访问”，所以这里对路径的总访问次数是线性的，所以对于所有的 $u$，这步的总时间复杂度为排序所需的 $\mathcal O(m\log m)$。

在计算出 $g_v$ 之后向下递归之前，将挂在 $u$ 上的路径权值按照端点插入到以 dfs 序为下标的线段树上，这样就能以单点插入区间求最大值的线段树实现上面第二种情况的需求。

------------

现在我们求出了一车 dp 值，回头看看题中定义的 $f(u,v)$。题目要求在路径集合 $U$ 中加入 $(u,v,f(u,v))$ 后，$W(U)$ 刚好不能被更新。考虑在原树上删除路径 $(u,v)$ 上的所有点和与这些点相邻的所有边，对形成的若干子树的 dp 值求和，则 $f(u,v)$ 即为 $W(U)$ 减去这个和。我们的目标即为求出这个和。

考虑上面所说“形成的若干子树”，在原树以 $1$ 为根时，这些子树要么仍是一个子树，要么是某个子树的补，它们的 dp 值即为上面求出的 $f_u$ 和 $g_u$。于是我们可以转而考虑每个 $f_u$ 或 $g_u$ 对答案产生的贡献。$f_u$ 会产生贡献当且仅当新增的路径不经过 $u$ 而经过它的父亲，$g_u$ 会产生贡献当且仅当新增的路径经过 $u$ 而不经过它的父亲，简单容斥即可求出贡献次数。

整个流程中，求 lca、树状数组、排序、线段树均为单 $\log$，在本题 $n,m$ 同阶的情况下，总的时间复杂度为 $\mathcal O(n\log n)$。

代码见[评测记录](/record/103495053)，目前是无氧最优解。

upd:同一份代码[吸了下氧](/record/104028662)，目前是最优解。

------------

闲话：当事模拟赛，开赛不久 T4 被指出是重题，于是从 P3772 换成了这道（

另外感谢峰发帖建议这题紫升黑，这下黑题喜加一了。

---

## 作者：george0929 (赞：2)

### Part1. 求 $W(S)$

考虑 DP 先求出 $W(S)$。

令 $f_u$ 表示 $u$ 子树内，$u$ 点可用可不用的答案。

令 $g_u$ 表示 $u$ 子树内，$u$ 点必须不用的答案。

令 $c_u=g_u-f_u$，表示将 $u$ 空出来的代价。

考虑转移，把每个路径挂在路径的 lca 上，有：

$$
g_x\leftarrow \sum\limits_{y\in son_x} f_y
\\
f_x=g_x+\max(0,\max\limits_{\operatorname{lca}(u_j,v_j)=x}\{w_j+\sum\limits_{k\in \operatorname{path}(u_j,v_j)}c_k\})
\\
W(S)=f_1
$$

这部分转移需要支持单点修改，路径查询，将路径差分成到根链，之后转化为子树修改，单点查询，使用树状数组即可。

### Part2. 求单个 $F(i,j)$

考虑加入一条边 $(u,v,w+1)$ 让独立集变大，那么要求这条边一定被选，仿照 DP 中选一条边的方式，有 $F(i,j)=-\sum\limits_{k\in \operatorname{path}(i,j)} c_k$。

当然，这是错的。

因为 $c_u$ 定义中，【将 $u$ 空出来的代价】只考虑了子树内的路径，我们还需要考虑子树外的路径，也就是说不存在一个经过 $(fa_{\operatorname{lca}(i,j)},\operatorname{lca}(i,j))$ 的路径被选择。

令 $h_u$ 表示整棵树空出 $(fa_{u},u)$ 的答案，则空出 $(fa_{u},u)$ 的代价为 $h_u-f_1$，有：

$$
F(i,j)=-\sum\limits_{k\in \operatorname{path}(i,j)} c_k-(h_{\operatorname{lca}(i,j)}-f_1)
$$

### Part3. 求 $h$

问题在于如何求 $h$，初值有 $h_1=f_1$，仿照求 $W(S)$ 中【朴素转移+强制选路径转移】设计 $h$ 的转移：

$$
h_x\leftarrow h_{fa_x}+c_{fa_x}
\\
h_x\leftarrow h_{\operatorname{lca}(u,v)}+w+\sum\limits_{k\in \operatorname{path}(u,v)} c_k\ \ \ ((u,v,w)\in S\land x\notin \operatorname{path}(u,v)\land fa_x\in \operatorname{path}(u,v))
$$

对于第二种转移，解释为强制选择路径 $(u,v,w)$，这样能保证 $(x,fa_x)$ 不被选。

对于第一种转移，解释为强制去掉 $fa_x$ 子树外经过 $(fa_{fa_x},fa_x)$ 的路径（由 $h$ 保证）和 $fa_x$ 子树内经过 $fa_x$ 的路径（由 $c$ 保证），如果去掉的路径不经过 $(x,fa_x)$ 也没关系，因为这样一定能被第二种转移覆盖到。

对于第二种转移的优化，考虑给路径上每个点打标记 $(u,x,y,z)$，表示在节点 $u$，值为 $x$，不能下传到 $y,z$。

下传标记时，将标记从大到小排序遍历，每次只操作没有被下传过的子节点，保证每个点的子节点只被操作一次，这样复杂度是 $O(标记个数)$ 的。

考虑重链剖分，每条路径上大多数标记都是 $(u,x,\operatorname{heavy\_child}_u,0)$，其余标记不超过 $O(\log n)$ 个。

对于 ，维护 $t_u$ 表示 $x$ 最大的 $(u,x,\operatorname{heavy\_child}_u,0)$。$t_u$ 的修改相当于树的链上取 $\max$，直接树剖，其余标记个数为 $O(n\log n)$，使用上面 $O(标记个数)$ 的方法。

### Part4. 求所有 $F(i,j)$

即求：

$$
\sum_{i=1}^{n} \sum_{j=1}^{n} \left(-\sum\limits_{k\in \operatorname{path}(i,j)} c_k-(h_{\operatorname{lca}(i,j)}-f_1)\right)
\\
=n^2\times f_1-\sum_{i=1}^{n} \sum_{j=1}^{n} h_{\operatorname{lca}(i,j)}-\sum_{i=1}^{n} \sum_{j=1}^{n} \sum\limits_{k\in \operatorname{path}(i,j)} c_k
\\
=n^2\times f_1-\sum_{k=1}^{n} \left(h_k\times \sum_{1\leq i,j\leq n\land \operatorname{lca}(i,j)=k} 1\right)-\sum_{k=1}^{n} \left(c_k\times \sum_{1\leq i,j\leq n\land k\in \operatorname{path}(i,j)} 1\right)
$$
对于每个点 $u$，记有 $p_u$ 条路径的 lca 是 $u$，有 $q_u$ 条路径经过 $u$，则答案为：
$$
n^2\times f_1-\sum_{k=1}^{n} p_k\times h_k-\sum_{k=1}^{n} q_k\times c_k
$$
$p,q$ 都是好维护的，至此本题所有问题已解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int n,m;
struct path{
	int u,v,w;
}pt[300005];
vector<int> V[300005];
////////////////////////////////////////////
////// Data Structure Start ////////////////
////////////////////////////////////////////
struct BIT{
	int c[300005];
	void _add(int p,int v){
		for(int i=p;i<=n;i+=i&-i) c[i]+=v;
	}
	void add(int l,int r,int v){
		_add(l,v);
		_add(r+1,-v);
	}
	int qry(int p){
		int res=0;
		for(int i=p;i>=1;i-=i&-i) res+=c[i];
		return res;
	}
};
struct SGT{
	struct node{
		int l,r,mx,tag;
	}t[1200005];
	void pushup(int p){
		t[p].mx=max(t[p*2].mx,t[p*2+1].mx);
	}
	void fmax(int p,int v){
		t[p].tag=max(t[p].tag,v);
		t[p].mx=max(t[p].mx,v);
	}
	void pushdown(int p){
		if(t[p].tag){
			int tmp=t[p].tag;
			t[p].tag=0;
			fmax(p*2,tmp);
			fmax(p*2+1,tmp);
		}
	}
	void build(int p,int l,int r){
		t[p].l=l,t[p].r=r;
		if(l==r) return;
		int mid=(l+r)/2;
		build(p*2,l,mid);
		build(p*2+1,mid+1,r);
	}
	void modify(int p,int l,int r,int v){
		if(l<=t[p].l&&t[p].r<=r){
			fmax(p,v);
			return;
		}
		pushdown(p);
		int mid=(t[p].l+t[p].r)/2;
		if(mid>=l) modify(p*2,l,r,v);
		if(mid<r) modify(p*2+1,l,r,v);
		pushup(p);
	}
	int query(int p,int pos){
		if(t[p].l==t[p].r) return t[p].mx;
		pushdown(p);
		int mid=(t[p].l+t[p].r)/2;
		if(mid>=pos) return query(p*2,pos);
		else return query(p*2+1,pos);
	}
};
////////////////////////////////////////////
////// Data Structure End //////////////////
////////////////////////////////////////////

////////////////////////////////////////////
////// Light-Heavy Segmentation Start //////
////////////////////////////////////////////
SGT sgt;
int dep[300005],sz[300005],fa[300005];
int son[300005],top[300005];
int dfn[300005],out[300005],Idfn[300005],tot;
int k[300005][21];
void dfs1(int u,int lst){
	fa[u]=k[u][0]=lst;
	sz[u]=1;
	dep[u]=dep[lst]+1;
	for(int v:V[u]){
		if(v==lst) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(!son[u]||sz[v]>sz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	dfn[u]=++tot;
	Idfn[tot]=u;
	if(son[u]){
		dfs2(son[u],tp);
	}
	for(int v:V[u]){
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
	out[u]=tot;
}
void LhsInit(){
	dfs1(1,0);
	dfs2(1,1);
	sgt.build(1,1,n);
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			k[i][j]=k[k[i][j-1]][j-1];
		}
	}
}
int LhsLca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dfn[u]>dfn[v]) swap(u,v);
	return u;
}
int LhsKth(int u,int t){
	for(int j=0;j<=20;j++){
		if(t&(1<<j)) u=k[u][j];
	}
	return u;
}
void _addtag(int u,int x,int y,int z);
void LhsModify(int u,int v,int w){
	if(u==v){
		_addtag(u,w,0,0);
		return;
	}
	int lca=LhsLca(u,v);
	if(lca!=u) _addtag(u,w,0,0);
	if(lca!=v) _addtag(v,w,0,0);
	if(lca!=u&&lca!=v){
		int tu=LhsKth(u,dep[u]-dep[lca]-1);
		int tv=LhsKth(v,dep[v]-dep[lca]-1);
		_addtag(lca,w,tu,tv);
	}else{
		if(lca==v) swap(u,v);
		int tv=LhsKth(v,dep[v]-dep[lca]-1);
		_addtag(u,w,tv,0);
	}
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		if(dfn[top[u]]<dfn[u]){
			if(top[u]!=lca) sgt.modify(1,dfn[top[u]],dfn[u]-1,w);
			else if(dfn[top[u]]+1<dfn[u]) sgt.modify(1,dfn[top[u]]+1,dfn[u]-1,w);
		}
		if(fa[top[u]]!=lca) _addtag(fa[top[u]],w,top[u],0);
		u=fa[top[u]];
	}
	if(dfn[u]>dfn[v]) swap(u,v);
	if(dfn[u]+1<dfn[v]){
		sgt.modify(1,dfn[u]+1,dfn[v]-1,w);
	}
}
////////////////////////////////////////////
////// Light-Heavy Segmentation End ////////
////////////////////////////////////////////

////////////////////////////////////////////
////// DP W(S) Start ///////////////////////
////////////////////////////////////////////
vector<int> P[300005];
int f[300005],g[300005],c[300005];
BIT bit;
int DpwPathQry(int u,int v){
	int lca=LhsLca(u,v);
	int res=bit.qry(dfn[u])+bit.qry(dfn[v])-bit.qry(dfn[lca]);
	if(fa[lca]) res-=bit.qry(dfn[fa[lca]]);
	return res;
}
void DpwVexAdd(int p,int v){
	bit.add(dfn[p],out[p],v);
}
void DoDPW(int u=1){
	f[u]=g[u]=0;
	for(int v:V[u]){
		if(v==fa[u]) continue;
		DoDPW(v);
		g[u]+=f[v];
	}
	f[u]=g[u];
	int tmp=0;
	for(int p:P[u]){
		tmp=max(tmp,pt[p].w+DpwPathQry(pt[p].u,pt[p].v));
	}
	f[u]+=tmp; 
	c[u]=g[u]-f[u];
	DpwVexAdd(u,c[u]);
}
void DpwInit(){
	for(int i=1;i<=m;i++){
		int lca=LhsLca(pt[i].u,pt[i].v);
		P[lca].push_back(i);
	}
}
////////////////////////////////////////////
////// DP W(S) End /////////////////////////
////////////////////////////////////////////

////////////////////////////////////////////
////// DP {H} Start ////////////////////////
////////////////////////////////////////////
int h[300005];
struct DphTag{
	int x,y,z;
	bool operator<(const DphTag &b) const{
		return x>b.x;
	}
};
vector<DphTag> T[300005];
void _addtag(int u,int x,int y,int z){
	T[u].push_back({x,y,z}); 
}
void DphAddTag(int u,int v,int w){
	LhsModify(u,v,w);
}
void DphPushTag(int u){
	_addtag(u,sgt.query(1,dfn[u]),son[u],0);
	sort(T[u].begin(),T[u].end());
	int ny=0,nz=0;
	for(int v:V[u]){
		if(v==fa[u]) continue;
		if(v!=T[u][0].y&&v!=T[u][0].z) h[v]=max(h[v],T[u][0].x);
		else{
			if(!ny) ny=v;
			else nz=v;
		}
	}
	for(int i=1;i<T[u].size();i++){
		auto tag=T[u][i];
		if(ny&&ny!=tag.y&&ny!=tag.z){
			h[ny]=max(h[ny],tag.x);
			ny=0;
		}
		if(nz&&nz!=tag.y&&nz!=tag.z){
			h[nz]=max(h[nz],tag.x);
			nz=0;
		}
		if(!ny&&!nz) break;
	}
	T[u].clear();
}
void DoDPH(int u=1){
	if(u==1) h[u]=f[u];
	for(int v:V[u]){
		if(v==fa[u]) continue;
		h[v]=max(h[v],h[u]+c[u]);
	}
	for(int p:P[u]){
		DphAddTag(pt[p].u,pt[p].v,h[u]+pt[p].w+DpwPathQry(pt[p].u,pt[p].v));
	}
	DphPushTag(u);
	for(int v:V[u]){
		if(v==fa[u]) continue;
		DoDPH(v);
	}
}
////////////////////////////////////////////
////// DP {H} End //////////////////////////
////////////////////////////////////////////

////////////////////////////////////////////
////// Calc Answer Start ///////////////////
////////////////////////////////////////////
int tcnt[300005],lcacnt[300005];
int CaSolve(){
	for(int i=1;i<=n;i++){
		int sumsz=1;
		for(int j:V[i]){
			if(j==fa[i]) continue;
			tcnt[i]+=sz[j]*(n-sz[j]);
			lcacnt[i]+=sumsz*sz[j];
			sumsz+=sz[j];
		}
		tcnt[i]+=(n-sz[i])*sz[i];
		tcnt[i]=tcnt[i]+n;
		lcacnt[i]=lcacnt[i]*2+1;
	}
	int ans=f[1]%mod*n%mod*n%mod;
	for(int i=1;i<=n;i++){
		tcnt[i]%=mod;
		lcacnt[i]%=mod; 
		h[i]%=mod;
		c[i]%=mod;
		ans=(ans+mod-lcacnt[i]*h[i]%mod)%mod;
		ans=(ans+mod-tcnt[i]*c[i]%mod)%mod;
	}
	return ans;
}
////////////////////////////////////////////
////// Calc Answer End /////////////////////
////////////////////////////////////////////
 
void init(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	for(int i=1;i<=m;i++) cin>>pt[i].u>>pt[i].v>>pt[i].w;
}
signed main(){
	init();
	LhsInit();
	DpwInit();
	DoDPW();
	DoDPH();
	cout<<CaSolve()<<"\n"; 
	return 0;
}
```

---

## 作者：wwwwwza (赞：2)

神仙题，研究了好久才过，写篇题解造福大众。

首先考虑 $W(U)$ 如何计算。

设 $f_u$ 表示在 $u$ 的子树内 $W(U)$ 的最大值，$g_u$ 表示在 $u$ 的子树内不选 $u$ 时 $W(U)$ 的最大值。

那么 $c_u=g_u-f_u$ 就表示强行不选 $u$ 的对答案的代价。

可推出转移式子：

$$
g_x=\sum\limits_{y\in son(x)}f_y
$$
$$
f_x=g_x+\max(0,\max\limits_{\operatorname{lca}(u_i,v_i)=x}w_i+\sum\limits_{p\in path(u_i,v_i)}c_p)
$$

若 $W(U\cup \{ (u,v,w)\})>W(u)$，那么 $\{(u,v,w)\}$ 一定在要选路径中，所以设 $h_u$ 表示 $u$ 到 $fa_u$ 这条路径没有被选到，所以 $f(u,v)$ 的答案为 $f_1-\sum\limits_{x\in path(u,v)}c_x-h_{\operatorname{lca}(u,v)}$。

可推出转移式子（求最大值）：

$$
\left\{\begin{matrix}
h_x\gets h_y+c_y,x\in son(y)
 \\
h_x\gets h_y+\sum\limits_{p\in path(u_i,v_i)c_p}+w_i,\operatorname{lca}(u_i,v_i)=y,x\notin path(u_i,v_i),fa_x\in path(u_i,v_i)
\end{matrix}\right.
$$

我用的办法是每一个点维护一个 $mx_u$，表示 $h_v=\max\limits_{u\ne v,fa_u=fa_v}(h_v,mx_u)$。

对于要区间赋最大值给一个节点的所有儿子节点时，广搜整棵树，给其编号，及每个点和兄弟节点的编号相邻，用线段树来维护。

最后计算 $\sum\limits_{u=1}^n\sum\limits_{v=1}^n f_1-\sum\limits_{x\in path(u,v)}c_x-h_{\operatorname{lca}(u,v)}$ 即可。

线段树、树链剖分、求最近公共祖先的时间复杂度都是 $O(\log n)$ 的，总的时间复杂度为 $O(n\log n)$。

代码有点丑。


```cpp
#include <bits/stdc++.h>
#define int long long
#define max(a,b) (a>b?a:b)
using namespace std;
const int N=3e5+10;
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,m,x,y,w,f[N],g[N],c[N],h[N],ans=0;
int dfn[N],son[N],siz[N],fat[N],top[N],dep[N],idx=0,pos[N],to[N][22];
vector<int>e[N];
void dfs1(int u,int fa){
	siz[u]=1;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fa)continue;
		dep[v]=dep[u]+1,fat[v]=u,to[v][0]=u;
		for(int j=1;j<=20;j++)to[v][j]=to[to[v][j-1]][j-1];
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void dfs2(int u,int topx){
	dfn[u]=++idx,top[u]=topx;
	if(son[u])dfs2(son[u],topx);
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fat[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
struct pls_{
	int tree[N<<2];
	void update(int rt,int l,int r,int x,int d){
		tree[rt]+=d;
		if(l==r)return;
		int mid=l+r>>1;
		if(x<=mid)update(rt*2,l,mid,x,d);
		else update(rt*2+1,mid+1,r,x,d);
	}
	int query(int rt,int l,int r,int x,int y){
		if(x<=l&&r<=y)return tree[rt];
		int mid=l+r>>1,res=0;
		if(x<=mid)res+=query(rt*2,l,mid,x,y);
		if(y>mid)res+=query(rt*2+1,mid+1,r,x,y);
		return res;
	}
}t;
struct max_{
	int tree[N<<2],tag[N<<2];
	void init(){
		memset(tree,-inf,sizeof(tree));
	}
	void pushdown(int rt){
		tag[rt*2]=max(tag[rt*2],tag[rt]),tag[rt*2+1]=max(tag[rt*2+1],tag[rt]);
		tree[rt*2]=max(tree[rt*2],tag[rt]),tree[rt*2+1]=max(tree[rt*2+1],tag[rt]);
		tag[rt]=-inf;
	}
	void update(int rt,int l,int r,int x,int y,int d){
		if(x>y)return;
		if(x<=l&&r<=y){
			tree[rt]=max(tree[rt],d);
			tag[rt]=max(tag[rt],d);
			return;
		}
		pushdown(rt);
		int mid=l+r>>1;
		if(x<=mid)update(rt*2,l,mid,x,y,d);
		if(y>mid)update(rt*2+1,mid+1,r,x,y,d);
		tree[rt]=max(tree[rt*2],tree[rt*2+1]);
	}
	int query(int rt,int l,int r,int x){
		if(l==r)return tree[rt];
		pushdown(rt);
		int mid=l+r>>1;
		if(x<=mid)return query(rt*2,l,mid,x);
		else return query(rt*2+1,mid+1,r,x);
	}
}t1,t2;
struct path{
	int u,v,w;
};
vector<path>edge[N];
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int ask(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res+=t.query(1,1,n,dfn[top[x]],dfn[x]);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	res+=t.query(1,1,n,dfn[x],dfn[y]);
	return res;
}
void add(int x,int y,int d){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		t2.update(1,1,n,dfn[top[x]],dfn[x],d);
		x=fat[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	t2.update(1,1,n,dfn[x],dfn[y],d);
}
void bfs(){
	queue<int>q;
	idx=0;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		pos[u]=++idx;
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			if(pos[v])continue;
			q.push(v);
		}
	}
}
void dfs3(int u){
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fat[u])continue;
		dfs3(v);
		g[u]+=f[v];
	}
	f[u]=g[u];
	for(int i=0;i<edge[u].size();i++){
		f[u]=max(f[u],g[u]+edge[u][i].w+ask(edge[u][i].u,edge[u][i].v));
	}
	c[u]=g[u]-f[u];
	t.update(1,1,n,dfn[u],c[u]);
}
void dfs4(int u){
	h[u]=max(h[u],t1.query(1,1,n,pos[u]));
	for(int i=0;i<edge[u].size();i++){
		int a=edge[u][i].u,b=edge[u][i].v,val=edge[u][i].w;
		val=h[u]+ask(a,b)+val;
		if(a==b&&!e[u].empty()){
			int l=pos[e[u][0]],r=pos[e[u][e[u].size()-1]];
			t1.update(1,1,n,l,r,val);
			continue;
		}
		int p=lca(a,b);
		if(b==p)swap(a,b);
		if(a==p){
			add(a,b,val);
			if(!e[b].empty()){
				int l=pos[e[b][0]],r=pos[e[b][e[b].size()-1]];
				t1.update(1,1,n,l,r,val);
			}
			continue;
		}
		if(!e[a].empty()){
			int l=pos[e[a][0]],r=pos[e[a][e[a].size()-1]];
			t1.update(1,1,n,l,r,val);
		}
		if(fat[a]!=p){
			int dis=dep[a]-dep[p]-2,k=a;
			for(int j=20;j>=0;j--){
				if((dis>>j)&1)k=to[k][j];
			}
			add(k,a,val);
			a=fat[k];
		}
		if(!e[b].empty()){
			int l=pos[e[b][0]],r=pos[e[b][e[b].size()-1]];
			t1.update(1,1,n,l,r,val);
		}
		if(fat[b]!=p){
			int dis=dep[b]-dep[p]-2,k=b;
			for(int j=20;j>=0;j--){
				if((dis>>j)&1)k=to[k][j];
			}
			add(k,b,val);
			b=fat[k];
		}
		a=pos[a],b=pos[b];
		if(a>b)swap(a,b);
		int l=pos[e[u][0]],r=pos[e[u][e[u].size()-1]];
		t1.update(1,1,n,l,a-1,val);
		t1.update(1,1,n,a+1,b-1,val);
		t1.update(1,1,n,b+1,r,val);
	}
	if(!e[u].empty()){
		int l=pos[e[u][0]],r=pos[e[u][e[u].size()-1]];
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i];
			if(v==fat[u])continue;
			h[v]=max(h[v],h[u]+c[u]);
			int now=t2.query(1,1,n,dfn[v]);
			t1.update(1,1,n,l,pos[v]-1,now);
			t1.update(1,1,n,pos[v]+1,r,now);
		}
	}
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fat[u])continue;
		dfs4(v);
	}
}
void dfs(int u){
	int cnt=0;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fat[u])continue;
		ans=(ans-2ll*(cnt*siz[v]%mod)*h[u]%mod+mod)%mod;
		ans=(ans-2ll*(cnt*siz[v]%mod)*c[u]%mod+mod)%mod;
		cnt+=siz[v];
		dfs(v);
	}
	ans=(ans-2ll*(cnt*(n-siz[u])%mod)*c[u]%mod-(n*2-1)*c[u]%mod+mod+mod)%mod;
	ans=(ans-(2*siz[u]-1)*h[u]%mod+mod)%mod;
}
bool cmp(int x,int y){
	return dfn[x]>dfn[y];
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin >>n>>m;
	for(int i=1;i<n;i++){
		cin >>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;i++)sort(e[i].begin(),e[i].end(),cmp);
	for(int i=2;i<=n;i++)e[i].pop_back();
	for(int i=1;i<=m;i++){
		cin >>x>>y>>w;
		edge[lca(x,y)].push_back({x,y,w});
	}
	bfs();
	dfs3(1);
	h[1]=f[1],t1.init(),t2.init();
	dfs4(1);
	f[1]%=mod,ans=f[1]*(n*n%mod)%mod;
	for(int i=1;i<=n;i++)h[i]%=mod,c[i]=((-c[i]/mod+2)*mod+c[i])%mod;
	dfs(1);
	cout <<ans;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# P5642 题解

**题目大意**

> 给你一颗 $n$ 个节点的树，以及 $m$ 条路径 $(u, v, w)$。一个路径集合 $S$ 的重量 $W(S)$ 记为：找出 $S$ 的一个权值之和最大的子集，该子集满足任何两条路径没有公共点，这个子集的所有路径权值之和就是 $W(S)$。
>
> 记 $c(u, v) = w$ 为最小的非负整数 $w$，使得对于给定的 $m$ 条边组成的路径集合 $U$，$W(U \cup \{(u, v, w + 1)\}) > W(U)$。
>
> 请你计算 $\sum_{u=1}^n\sum_{v=1}^nc(u,v)$ 对 $998244353$ 取模后的结果。
>
> 数据范围：$n,m\le 3\times 10^5$。

**思路分析**

其实 $c(u,v)$ 就是求删掉 $u\to v$ 路径上的所有点后，剩余树的每一部分的答案之和 $W'$，最后 $c(u,v)$ 就是 $W(U)-W'$。

我们可以把这个求值拆成 $f_u$ 表示 $u$ 子树的答案，以及 $g_u$ 表示删除 $u$ 子树后外部的答案。

先考虑如何求 $f_u$：

- 若 $u$ 没被覆盖，则贡献为 $\sum_{v\in \mathrm{son}(u)}f_v$。

- 否则枚举一条 $\mathrm{LCA}(x_i,y_i)=u$ 的路径，贡献是 $z_i$ 加上删掉 $x_i\to y_i$ 后每个子树的 $f_p$ 之和。

  考虑容斥，记 $fs_u$ 表示 $\sum_{v\in \mathrm{son}(u)}f_v$，那么答案就是 $z_i$ 加上路径上每个点 $fs_p$ 之和减掉 $f_p$ 之和（要算上 $fs_u$ 不算 $f_u$）。

路径求和问题可以用差分转成 $1\to x$ 的路径和，子树加单点查，树状数组维护。

然后考虑如何求 $g_v$（$u=fa(v)$）：

- 若 $u$ 不选，则贡献为 $g_u+fs_u-f_v$。

- 否则考虑加入一条 $\mathrm{LCA}(x_i,y_i)=u$ 的路径，设 $w_i$ 为我们在上一个部分计算的这条路径的 $z_i$ 加上切出来的每个子树 $f_p$ 之和，那么我们用 $w_i+g_u-f_v$ 更新每个 $g_v$。

  观察一下这条路径对每个 $p$ 的所有儿子的 $g$ 影响，发现对于每个 $p$ 至多有两个儿子的 $g$ 不能更新，其他都能更新。

  - 若 $0$ 个儿子不能更新：一定是 $x_i,y_i$ 两个端点的所有儿子都能被更新，维护一个 $ed_u$ 标记更新即可。

  - 若 $2$ 个儿子不能更新：一定是一条 $x_i\ne u,y_i\ne u$ 的路径，此时 $u$ 的儿子中不是 $x_i/y_i$ 祖先的儿子都能被更新，倍增维护 $x_i,y_i$ 在哪个子树即可。

  - 若 $1$ 个儿子不能更新：不妨对每个 $v$ 维护一个标记 $ne_v$，表示 $v$ 的所有兄弟都能被 $ne_v$ 更新。

    - 若 $x_i=u,y_i\ne u$，那么 $y_i\to u$ 上所有不是 $u$ 的点的 $ne$ 标记都能更新。
    - 若 $x_i\ne u,y_i\ne u$，那么 $x_i\to y_i$ 上所有不是 $u$ 且不是 $u$ 儿子的点的 $ne$ 标记都能更新。

    注意到 $ne$ 的更新都是路径修改，可以直接树剖，但我们观察到求 $ne_v$ 时，更新过的路径的 $\mathrm{LCA}$ 都在 $v$ 的子树外，因此有一个端点在 $v$ 子树里的点一定经过 $v$。

    因此我们可以直接把路径要更新的值存在 $x_i$ 和 $y_i$ 上，求 $ne_v$ 就是子树最大值，zkw 线段树维护。

    但注意到只有第一类路径能更新 $u$ 儿子的 $ne_v$，因此先处理第一类路径然后处理 $ne_v$，最后处理第二类路径即可。

    维护的过程中我们还注意到 $ed_u$ 其实就是线段树上 $u$ 节点的值，因此直接在线段树上查点值即可。

最后得到了所有的更新操作后，可以直接建线段树维护每个点最终的 $g_v$，也可以找到更新权值最大的的一次操作先执行，然后把没被更新的 $\mathcal O(1)$ 个点暴力更新。

最后我们就得到了所有 $f_u$ 和 $g_u$，类似容斥可得 $c(u,v)$ 就是路径上不为 $\mathrm{LCA}$ 的每个点的 $fs_u-f_u$ 加上 $g_{\mathrm{LCA}}+fs_{\mathrm{LCA}}$，拆贡献即可。

时间复杂度 $\mathcal O((n+m)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5,MOD=998244353;
inline void chkmax(ll &x,ll y) { x=x>y?x:y; }
int n,m,q;
vector <int> G[MAXN];
struct Edge { int u,v; ll w; };
vector <Edge> pt[MAXN];
int dfn[MAXN],L[MAXN],R[MAXN],dcnt,st[MAXN][20],up[MAXN][20],siz[MAXN],fa[MAXN];
ll f[MAXN],fs[MAXN],g[MAXN],sumf[MAXN];
inline void dfs0(int u,int fz) {
	up[u][0]=st[++dcnt][0]=fz,L[u]=dfn[u]=dcnt,siz[u]=1,fa[u]=fz;
	for(int k=1;k<20;++k) up[u][k]=up[up[u][k-1]][k-1];
	for(int v:G[u]) if(v^fz) dfs0(v,u),siz[u]+=siz[v];
	R[u]=dcnt;
}
inline int bit(int x) { return 1<<x; }
inline int cmp(int x,int y) { return dfn[x]<dfn[y]?x:y; }
inline int LCA(int u,int v) {
	if(u==v) return u;
	int l=min(dfn[u],dfn[v])+1,r=max(dfn[u],dfn[v]),k=__lg(r-l+1);
	return cmp(st[l][k],st[r-bit(k)+1][k]);
}
struct FenwickTree {
	ll tr[MAXN],s;
	inline void c(int x,ll k) { for(;x<=n;x+=x&-x) tr[x]+=k; }
	inline void add(int l,int r,ll k) { c(l,k),c(r+1,-k); }
	inline ll qry(int x) { for(s=0;x;x&=x-1) s+=tr[x]; return s; } 
}	Tf;
inline void dfs1(int u,int fz) {
	for(int v:G[u]) if(v^fz) dfs1(v,u),fs[u]+=f[v];
	for(auto &e:pt[u]) {
		if(dfn[e.u]>dfn[e.v]) swap(e.u,e.v);
		e.w+=Tf.qry(dfn[e.u])+Tf.qry(dfn[e.v])+fs[u];
		chkmax(f[u],e.w);
	}
	chkmax(f[u],fs[u]),Tf.add(L[u],R[u],fs[u]-f[u]);
}
struct SegmentTree {
	static const int N=1<<19;
	ll tr[N<<1];
	inline void upd(int x,ll v){
		x+=N,tr[x]=max(tr[x],v);
		for(x>>=1;x;x>>=1) tr[x]=max(tr[x<<1],tr[x<<1|1]);
	}
	inline ll qry(int l,int r) {
		ll ans=0;
		for(l+=N-1,r+=N+1;l^r^1;l>>=1,r>>=1) {
			if(!(l&1)) chkmax(ans,tr[l^1]);
			if(r&1) chkmax(ans,tr[r^1]);
		}
		return ans;
	}
}	Tn;
inline int getson(int u,int rt) {
	for(int k=19;~k;--k) if(dfn[up[u][k]]>dfn[rt]) u=up[u][k];
	return u;
}
inline void dfs2(int u,int fz) {
	sumf[u]=sumf[fz]+fs[u]-f[u];
	vector <array<ll,3>> opr;
	for(auto e:pt[u]) if(e.u==u) Tn.upd(dfn[e.v],e.w+g[u]);
	for(int v:G[u]) if(v^fz) {
		ll ne=Tn.qry(L[v],R[v]);
		opr.push_back({ne,v,-1});
	}
	opr.push_back({Tn.qry(dfn[u],dfn[u]),-1,-1});
	opr.push_back({g[u]+fs[u],-1,-1});
	for(auto e:pt[u]) if(e.u!=u) {
		Tn.upd(dfn[e.u],e.w+g[u]),Tn.upd(dfn[e.v],e.w+g[u]);
		opr.push_back({e.w+g[u],getson(e.u,u),getson(e.v,u)});
	}
	auto mx=*max_element(opr.begin(),opr.end());
	for(int v:G[u]) if(v^fz) if(v!=mx[1]&&v!=mx[2]) g[v]=mx[0];
	if(~mx[1]) for(auto t:opr) if(t[1]!=mx[1]&&t[2]!=mx[1]) chkmax(g[mx[1]],t[0]);
	if(~mx[2]) for(auto t:opr) if(t[1]!=mx[2]&&t[2]!=mx[2]) chkmax(g[mx[2]],t[0]);
	for(int v:G[u]) if(v^fz) g[v]-=f[v],dfs2(v,u);
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;++i) {
		scanf("%d%d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs0(1,0);
	for(int k=1;k<20;++k) for(int i=1;i+bit(k-1)<=n;++i) {
		st[i][k]=cmp(st[i][k-1],st[i+bit(k-1)][k-1]);
	}
	for(int i=1,u,v,w;i<=m;++i) {
		scanf("%d%d%d",&u,&v,&w);
		pt[LCA(u,v)].push_back({u,v,w});
	}
	dfs1(1,0),dfs2(1,0);
	ll ans=0;
	for(int i=1;i<=n;++i) {
		ans=(ans+sumf[i]%MOD*n*2)%MOD;
		ll lca=1ll*siz[i]*siz[i]%MOD;
		for(int j:G[i]) if(j^fa[i]) lca=(lca+MOD-1ll*siz[j]*siz[j]%MOD)%MOD;
		ans=(ans+((g[i]+fs[i]-2*sumf[i])%MOD+MOD)%MOD*lca)%MOD;
	}
	ans=(f[1]%MOD*n%MOD*n%MOD+MOD-ans)%MOD;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lcjqwq (赞：1)

设 $f_u$ 为只考虑 $u$ 子树内的路径，$g_u$ 表示只考虑子树外的路径。通过这两个数组可以 $O(n)$ 计算出答案。

计算 $f_u$ 可以考虑转移时枚举 LCA 是当前点的路径，设 $f'_u$ 表示 $fa_u$ 除去 $u$ 这颗子树后其他儿子的 $f$ 值之和。我们用树状数组维护 $f'$ 的单点加链求和就可以从下往上计算出 $f_u$。

计算 $g_u$ 时，考虑从 $g_u$ 转移到 $g_v$。$u$ 点不选路径就是用其他子树的 $f$ 和 $g_u$ 的和转移；选了一条 LCA 为 $u$ 的路径，相当于 ban 了某些儿子不能用这条路径转移；
选了一条 LCA 在 $u$ 上面的路径，相当于 ban 了一个儿子不能转移。我们在从上往下枚举到某个 LCA 时可以把这条路径的答案存在端点处，转移的时候查询子树 max 即可。用线段树维护。

总时间复杂度 $O(n \log n)$。

代码 https://www.luogu.com.cn/paste/w7qd0zpi

---

## 作者：takanashi_mifuru (赞：0)

容易发现这个东西实际上就是挑一条路径把他丢了之后答案和原树答案的差。

这两个东西是独立的，我们把他反过来就变成了求丢一条路径的答案。

容易发现丢了一条路径之后，整棵树会裂成若干个联通块，他们之间又各自独立，所以我们反过来找这个联通块然后看他被使用了多少次。

容易发现最后分裂出的联通块一定分为两种，一种是在路径 LCA 上面一个形如整棵树除掉某个子树的联通块；另一种是在路径下面的形如一个子树的联通块，容易发现这两种联通块各自只有 $n$ 种，我们考虑对于每个联通块来做这个事。

首先是子树内的，设 $f_i$ 表示子树内的最大答案，再考虑记录 $g_i$ 为 $i$ 的直接儿子的 $f_v$ 之和。

转移分两种，一种是点 $i$ 不选，$f_i=g_i$。

另一种是点 $i$ 选，在这个地方做出抉择，说明 $i$ 是这个路径的两个端点的 LCA，我们把路径挂在这个上面然后枚举一下，这里就相当于是求出路径上所有的 $g$ 的和。

但是很没有道理的是我们也统计了路径本身，所以再减掉路径上 $f$ 的和就好了（当前点 $i$ 仍未处理出来，记录为 $0$）。

我们这样就可以直接算出 $f$，具体实现方式可以看自己喜欢，可以直接用树剖维护。

然后我们考虑抛掉一个子树的答案，设 $dp_i$ 为抛掉以 $i$ 为根的子树的答案，容易发现对于一个点 $u$，假设以他的儿子 $v$ 为根的子树现在要 ban 掉，有两种可能，第一种是点 $u$ 不选，$dp_v=dp_u+g_u-f_v$，另一种可能是点 $u$ 必须选，那么对于任意一条经过 $u$ 而不经过 $v$ 的路径，假设其路径端点的 LCA 为 $w$，则分两种情况，如果 $w\not=u$，意味着路径端点最多有一个落在 $u$ 的子树中，我们按照 $dfn$ 序把合法区间询问就可以了；而如果 $w=u$，则考虑有可能其中一个端点合法，另一个端点不合法，这样的情况就不能够用 ds 维护（树套树会 MLE）。

我们先不管这样的路径怎么办，先来考虑对于一条合法的路径，他如何贡献答案。

容易发现对于这条路径，他把 $v$ 丢掉了不能选的同时，又把剩下的变成了一个新的子问题，每一个点用以贡献的权值仍然是 $g_i-f_i$（注意在 LCA 处不减 $f_i$，同时要删除 $f_v$ 造成的冗余贡献），对于 $w$ 子树之外的点，可以直接调用 $dp_w$，整理一下就是 $dp_v=dp_u+\max\{val_k\}-f_v$，其中 $val_k$ 表示选择第 $k$ 条路径之后能够得到的权值，也就是路径上所有点的 $f-g$ 之和再加上选择这条路径本来就有的贡献。

容易发现 $val_k$ 是不变的，所以对于第二种情况，我们把所有 $w=u$ 的路径按照 $val$ 从大到小排序，直接枚举到第一个合法路径统计答案然后退出即可。

对于时间复杂度的证明，容易发现一条路径最多贡献 $O(1)$ 的枚举量，因为他的两个端点顶多各伸入一个儿子里面，所以这个的时间复杂度是正确的。

维护了 $f$ 和 $dp$ 之后就是计算其采用的方案数了，对于这个随便算算就好了，注意取模，$f$ 和 $dp$ 的计算过程是不能取模的，但是你把他拿出来之后必须单独取一次模，不然会爆 long long，哈哈，是谁因为这个调了一晚上呢？

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m;
vector<int> ljb[300005];
int heavy[300005];
long long siz[300005];
int father[300005];
int tot;
int dfn[300005],rnk[300005],top[300005];
int dep[300005];
long long all[300005];
class SumSegTree{
    public:
    long long Tree[300005<<2];
    void pushup(int cur){
        Tree[cur]=Tree[cur<<1]+Tree[cur<<1|1];
        return;
    }
    void update(int cur,int lt,int rt,int Q,long long val){
        if(lt>Q||rt<Q)return;
        if(lt==rt)return Tree[cur]+=val,void();
        int mid=lt+rt>>1;
        update(cur<<1,lt,mid,Q,val),update(cur<<1|1,mid+1,rt,Q,val);
        pushup(cur);
        return;
    }
    long long query(int cur,int lt,int rt,int qx,int qy){
        if(lt>qy||rt<qx)return 0;
        if(lt>=qx&&rt<=qy)return Tree[cur];
        int mid=lt+rt>>1;
        return (query(cur<<1,lt,mid,qx,qy)+query(cur<<1|1,mid+1,rt,qx,qy));
    }
}Q;
struct upd{
    int x;
    long long val;
}stk[300005<<7];
int yanami;
class MaxSegTree{
    public:
    long long Tree[300005<<2];
    int tot;
    void pushup(int cur){
        Tree[cur]=max(Tree[cur<<1],Tree[cur<<1|1]);
        return;
    }
    void update(int cur,int lt,int rt,int Q,long long val){//qx代表rt[qx]
        if(lt>Q||rt<Q)return;
        if(!cur)cur=++tot;
        if(lt==rt)return stk[++yanami]=upd{Q,Tree[cur]},Tree[cur]=max(Tree[cur],val),void();
        int mid=lt+rt>>1;
        update(cur<<1,lt,mid,Q,val),update(cur<<1|1,mid+1,rt,Q,val);
        pushup(cur);
        return;
    }
    void modify(int cur,int lt,int rt,int Q,long long val){
        if(lt>Q||rt<Q)return;
        if(!cur)return;
        if(lt==rt)return Tree[cur]=val,void();
        int mid=lt+rt>>1;
        modify(cur<<1,lt,mid,Q,val),modify(cur<<1|1,mid+1,rt,Q,val);
        pushup(cur);
        return;
    }
    long long query(int cur,int lt,int rt,int qx,int qy){
        if(!cur)return 0;
        if(lt>qy||rt<qx)return 0;
        if(lt>=qx&&rt<=qy)return Tree[cur];
        int mid=lt+rt>>1;
        return max(query(cur<<1,lt,mid,qx,qy),query(cur<<1|1,mid+1,rt,qx,qy));
    }
}P;
int getlca(int x,int y){
    while(top[x]^top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        x=father[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
long long query(int x,int y){
    long long ans=0;
    while(top[x]^top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        int lt=dfn[top[x]],rt=dfn[x];
        ans+=Q.query(1,1,n,lt,rt);
        x=father[top[x]];
    }
    int lt=dfn[x],rt=dfn[y];
    if(lt>rt)swap(lt,rt);
    ans+=Q.query(1,1,n,lt,rt);
    return ans;
}
void getheavy(int cur,int fa){
    siz[cur]=1;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getheavy(v,cur);
        siz[cur]+=siz[v];
        if(siz[v]>siz[heavy[cur]]){
            heavy[cur]=v;
        }
        all[cur]+=siz[v]*siz[v]%mod;
    }
    all[cur]+=(n-siz[cur])*(n-siz[cur])%mod;
    return;
}
void getdfn(int cur,int fa){
    father[cur]=fa;
    dep[cur]=dep[fa]+1;
    tot++;
    dfn[cur]=tot,rnk[dfn[cur]]=cur;
    if(heavy[cur]){
        top[heavy[cur]]=top[cur];
        getdfn(heavy[cur],cur);
    }
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        if(v==heavy[cur])continue;
        top[v]=v;
        getdfn(v,cur);
    }
    return;
}
struct node{
    int u,v,w;
    long long val;
}path[300005];
long long f[300005];
long long g[300005];
vector<int> id[300005];
void getg(int cur,int fa){
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getg(v,cur);
        g[cur]+=f[v];
    }
    Q.update(1,1,n,dfn[cur],g[cur]);
    f[cur]=g[cur];
    for(int i=0;i<id[cur].size();i++){
        int now=id[cur][i];
        path[now].val=query(path[now].u,path[now].v)+path[now].w;
        f[cur]=max(f[cur],path[now].val);
    }
    Q.update(1,1,n,dfn[cur],-f[cur]);
    return;
}
long long dp[300005];
bool cmp(int x,int y){
    return path[x].val>path[y].val;
}
void getdp(int cur,int fa){
    int lim=yanami;
    sort(id[cur].begin(),id[cur].end(),cmp);
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];//
        if(v==fa)continue;
        dp[v]=dp[cur]+g[cur]-f[v];
        for(int j=0;j<id[cur].size();j++){
            int now=id[cur][j];
            long long val=path[now].val+dp[cur]-f[v];
            if(getlca(path[now].u,v)==v||getlca(path[now].v,v)==v)continue;
            dp[v]=max(dp[v],val);
            break;
        }
        dp[v]=max(dp[v],P.query(1,1,n,dfn[cur],dfn[v]-1)-f[v]);
        dp[v]=max(dp[v],P.query(1,1,n,dfn[v]+siz[v],dfn[cur]+siz[cur]-1)-f[v]);
    }
    for(int i=0;i<id[cur].size();i++){
        int now=id[cur][i];
        P.update(1,1,n,dfn[path[now].v],path[now].val+dp[cur]);
        P.update(1,1,n,dfn[path[now].u],path[now].val+dp[cur]);
    }
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getdp(v,cur);
    }
    while(yanami>lim){
        P.modify(1,1,n,stk[yanami].x,stk[yanami].val);
        yanami--;
    }
    return;
}
long long ans;
int text1[300005],text2[300005];
void getans(int cur,int fa){//考虑实际上除了他自己都要翻倍
    long long cnt=siz[cur]*siz[cur];
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getans(v,cur);
        cnt-=siz[v]*siz[v];
    }
    long long neta=((
    (n-siz[cur])*(n-siz[cur])%mod
    -all[fa]%mod
    +siz[cur]*siz[cur]%mod))%mod;
    neta=(neta%mod+mod)%mod;
    cnt%=mod;
    text1[cur]=neta;
    text2[cur]=cnt;
    if(cur>1){
        ans+=cnt%mod*(dp[cur]%mod)%mod;
        ans+=f[cur]%mod*neta%mod;
        ans%=mod;
    }
    return;
}
signed main(){
    // freopen("test.in","r",stdin);
    // freopen("ans.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        ljb[u].push_back(v);
        ljb[v].push_back(u);
    }
    getheavy(1,0);
    top[1]=1;
    getdfn(1,0);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);//
        path[i].u=u;
        path[i].v=v;
        path[i].w=w;
        id[getlca(u,v)].push_back(i);
    }
    getg(1,0);
    getdp(1,0);
    getans(1,0);
    ans=(1ll*n*n%mod*(f[1]%mod)%mod-ans%mod+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}

```

---

