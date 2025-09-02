# [USACO19JAN] Exercise Route P

## 题目背景

USACO 19 年一月月赛铂金组第二题。

## 题目描述

奶牛 Bessie 意识到为了保持好的体形她需要更多地进行锻炼。她需要你帮助她选择在农场里每天用来晨跑的路线。 农场由 $n$ 块草地组成，方便起见编号为 $1\sim n$，由 $m$ 条双向的小路连接。作为一种遵循规律的生物，奶牛们倾向于使用其中特定的 $n−1$ 条小路作为她们日常在草地之间移动的路线——她们管这些叫“常规的”小路。从每块草地出发都可以仅通过常规的小路到达所有其他草地。

为了使她的晨跑更加有趣，Bessie 觉得她应该选择一条包含一些非常规的小路的路线。然而，使用常规的小路能够使她感到舒适，所以她不是很想在她的路线中使用过多非常规的小路。经过一些思考，她认为一条好的路线应当形成一个简单环（能够不经过任何草地超过一次的情况下回到起点），其中包含恰好两条非常规的小路。

请帮助 Bessie 计算她可以使用的好的路线的数量。两条路线被认为是相同的，如果它们包含的小路的集合相等。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 2 \times 10^5$，$1 \leq m \leq 2 \times 10^5$，$m \geq n - 1$，$1 \leq a_i, b_i \leq n$。

## 样例 #1

### 输入

```
5 8
1 2
1 3
1 4
1 5
2 3
3 4
4 5
5 2```

### 输出

```
4```

# 题解

## 作者：joe19025 (赞：15)

## Solution

### 前记

第一次想的时候猜了各种玄学结论，但也没想明白，后来看了官方解法也没太懂，后来仔细推敲后才想明白。

### 结论

首先我们发现普通边构成一棵树。2条非普通边加树边能形成环，条件如下。

两条非普通边连接树上两点，能成环当且仅当，一对点在树上的路径与另一对点在树上的路径有重合。画个图解释+粗糙证明一下。

![图解](https://i.loli.net/2019/02/24/5c724fab85694.png)

### 转化

问题变为求有多少个这样的树上路径之间相互重合。

### 拆路径

把路径拆成两部分，

1. $u->lca(u,v)$
2. $v->lca(u,v)$

这样就变成两条直上直下的路径了，也就好记数了。

### 计数

我们想在一个序列上，我们如何计算重叠序列的个数。为了避免算重复，我们就计算分别每一条线段，与自己重叠且开始在自己之后的，加起来即可。就是（开始在线段右端点前的）-（开始在线段左端点前的）。

对于树上问题同样可以这样做。我们把每一条边和它向下对应的点绑定在一起。同样用类似的方法，我们计算

（开始在$u/v$的）-（开始在$lca(u,v)$的）。因为从一个点向上有且只有一条路径，所以所有和它重叠的路径，起点都在lca和它本身之间。 

### 去重

1. 如果一个路径与两边的路径分别都相交，那它就会被计算两次。我们需要减掉重复的。方法就是用map，我们记录topx，topy（top就是属于祖先向下的哪一支），如果两个相同，就证明他们是两侧相交。要减去。对于一对(topx,topy),我们要减去$(出现次数)*(出现次数-1)/2$

2. 如果两条直上直下的路径他们开始在同一个点，这一对就会被算两次，相当于$n * n$次，但其实只有

   $n * (n-1)/2$次，所以要减去多余的。

### 复杂度O(nlogn)

Lca，top都是log复杂度。

## Code

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>
#define MAXN 200005
using namespace std;

vector<int>G[MAXN];
int n,m,cnt;
int a[MAXN],b[MAXN];
int fa[MAXN][20],dep[MAXN];

void dfs(int u,int father,int depth)
{
    fa[u][0]=father;dep[u]=depth;
    for(int i=1;(1<<i)<=depth;i++)
    {
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==father)continue;
        dfs(v,u,depth+1);
    }
}

int lca(int u,int v)
{
    if(dep[u]<dep[v])swap(u,v);
    for(int i=18;i>=0;i--)
    {
        if(dep[fa[u][i]]>=dep[v])
        {
            u=fa[u][i];
        }
    }
    if(u==v)return u;
    for(int i=18;i>=0;i--)
    {
        if(fa[u][i]!=fa[v][i])
        {
            u=fa[u][i];
            v=fa[v][i];
        }
    }
    return fa[u][0];
}

int GetTop(int u,int anc)
{
    if(u==anc)return -1;
    for(int i=18;i>=0;i--)
    {
        if(dep[fa[u][i]]>dep[anc])
            u=fa[u][i];
    }
    return u;
}

map<pair<int,int>,int>Q;
int sum[MAXN],siz[MAXN];
long long ans=0;

void dfs2(int u,int father,int cur)
{
    siz[u]=cur;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==father)continue;
        dfs2(v,u,cur+sum[v]);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0,1);
    for(int i=n;i<=m;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
        int anc=lca(a[i],b[i]);
        int topx=GetTop(a[i],anc);
        int topy=GetTop(b[i],anc);
        if(topx!=-1)
        {
            sum[topx]++;
            ans-=sum[topx];
        }
        if(topy!=-1)
        {
            sum[topy]++;
            ans-=sum[topy];
        }
        if(topx!=-1 && topy!=-1)
        {
            if(topx>topy)swap(topx,topy);
            ans-=Q[make_pair(topx,topy)];
            Q[make_pair(topx,topy)]++;
        }
    }
    dfs2(1,1,0);
    for(int i=n;i<=m;i++)
    {
        ans+=siz[a[i]]+siz[b[i]]-2*siz[lca(a[i],b[i])];
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：ETHANK (赞：11)

**题目大意：**

给定 $n$ 个点 $m$ 条边，其中 $n-1$ 条边为普通边，这些普通边构成了一棵树，剩下的边为特殊边。问图中有多少简单环恰包含两条特殊边。

数据范围：$1\le n\le 2\times10^5,1\le m\le 2\times 10^5,m\ge n-1,1\le a_i,b_i\le n$ .

> 知识储备：LCA

> 题目难度：省选/USACO Platinum

**解析：**

不难发现，简单环的形式是两条特殊边加上若干树上边。如果设这两条特殊边为  $(u_1,v_1),(u_2,v_2)$ ，当且仅当树上路径 $[u_1,v_1],[u_2,v_2]$ 有边重合时才能构造出简单环。

下面思考如何对重合的树上路径进行计数。先考虑一条链上的情况，即序列上计算重合区间的数量。可以扫一遍序列，对于当前区间 $[l_i,r_i]$ ，计算其他区间的左端点被该区间包含的数量即可。

树上路径也是类似的，我们将 $[u,v]$ 拆分为 $[u,L],[v,L]$ ，其中 $L$ 为 $u,v$ 的 LCA 。这样每个 $[u,v]$ 就被拆分为了两个链上的情况，类似处理序列的方法就可以计数。

然而这可能带来一定重复：

- $[u_i,v_i],[u_j,v_j]$ 在两条链上都有交：

考虑 $[u,L],[v,L]$ 链上 $L$ 的儿子 topx, topy ，那么两条链都有交等价于 $i,j$ 的 topx, topy 相同。用 map 存有相同 topx, topy 的 $[u,v]$ 数量 $k$ ，答案减去 $\binom{k}{2}$ 即可。

- 某条链上的起始点相同：

若这个起始点有 $k$ 条链，那么会算 $k^2$ 次，我们希望算 $\binom k2$ 次，减去算多的即可。

时间复杂度：$O(n\log n)$ .

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define ll long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=2e5+5;
int n,m,fa[N][20],Log[N],dep[N];
int a[N],b[N],L[N],siz[N],sum[N];
ll ans;
vector <int> G[N];
void dfs(int u,int f){
    dep[u]=dep[f]+1,fa[u][0]=f;
    for(int x:G[u])if(x!=f)dfs(x,u);
}
int lca(int x,int y) {
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y]){
	    x=fa[x][Log[dep[x]-dep[y]]];
	}
    if(x==y)return x;
    per(i,18,0){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int Top(int x,int anc){
    if(x==anc)return -1;
    per(i,18,0){
        if(dep[fa[x][i]]>dep[anc])x=fa[x][i];
    }
    return x;
}
map <pii,int> mp;
void dfs2(int u,int f,int now){
    siz[u]=now;
    for(int v:G[u])if(v!=f){
        dfs2(v,u,now+sum[v]);
    }
}
void init(){
    Log[0]=-1;
    rep(i,1,n)Log[i]=Log[i>>1]+1;
    rep(i,1,18){
        rep(j,1,n)fa[j][i]=fa[fa[j][i-1]][i-1];
    }
}
int main(){
    //freopen("disrupt.in","r",stdin);
    //freopen("disrupt.out","w",stdout);
    n=read(),m=read();
    rep(i,1,n-1){
        int u=read(),v=read();
        G[u].pb(v),G[v].pb(u);
    }
    dfs(1,0);
    init();
    rep(i,n,m){
        a[i]=read(),b[i]=read();
        L[i]=lca(a[i],b[i]);
    }
    rep(i,n,m){
        int topx=Top(a[i],L[i]),topy=Top(b[i],L[i]);
        if(topx!=-1){
            sum[topx]++;
            ans-=sum[topx];
        }
        if(topy!=-1){
            sum[topy]++;
            ans-=sum[topy];
        }
        if(topx!=-1&&topy!=-1){
            if(topx>topy)swap(topx,topy);
            ans-=mp[{topx,topy}];
            mp[{topx,topy}]++;
        }
        //cout<<i<<" "<<topx<<" "<<topy<<" "<<ans<<endl;
    }
    dfs2(1,0,0);
    rep(i,n,m){
        ans+=siz[a[i]]+siz[b[i]]-2*siz[L[i]];
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：PhantasmDragon (赞：7)


什么时候,两条非常规边可以在树上组成一个简单环?
假设这条两边分别为 $(u_1,v_1),(u_2,v_2)$ ,经过~~简单~~研究发现,在树上以 $u_1,v_1$ 为起止点的路径与以 $u_2,v_2$ 为起止点的路径有公共边的时候,即有边交,那么就可以组成一个简单环.

那么原题题意就变成了给你一些树上的路径,求这些路径之间有多少对有边交.

首先,树上的路径是从 $u$ -> $lca$ -> $v$ 这种形式的. 这并不利于我们研究.所以我们可以吧每条路径拆成两个: $u$ -> $lca$ 与 $v$ -> $lca$,这样就方便研究. 虽然这样会有一些重复计算,但是重复计算的部分很好剔除. 

不难发现只有当两条路径的 $lca$ 相同, 且两条路径与 $lca$ 相连的两条边是一样的,这时才会重复计算.

就是这个样子:
![enter image description here](https://leanote.com/api/file/getImage?fileId=5c7aaa23ab64410dee00783f)
红色,蓝色两条路径被拆分后,两个部分分别都会有交,所以答案就多了1.
一种方法就是对于每条路径都记录一下这两条与 $lca$ 相连的边,放在一个 $map$ 里就行了.

 具体的计数方法,可以先考虑一个一维空间,也就是直线上的一些线段 $[L_i,R_i]$ 相交计数.
 
为了防止重复,对于一个线段 $x$ ,我们只数与它相交,且 $L_i > L_x$ 的线段 $i$.

这样就有一个简单做法. 对于每个线段 $x$, 在 $L_x$ 时把答案减去满足 $L_i < L_x$ 的 $i$ 的个数,在 $R_x$ 时把答案加上满足 $L_i<R_x$ 的 $i$ 的个数. 这样对于每个线段我们都算出了与它相交,且 $L_i > L_x$ 的线段 $i$ 的个数.

实现方法类似差分, 在每个 $L_i$ 位置 +1, 做一次前缀和, $sum[R_x]-sum[L_x-1]$ 就是 线段 $x$ 的答案.

注意当有 $L$ 相等的情况时,会重复计算,需要减去多算的.

那么,我们在树上做的事情也是完全一样的.
为了方便,我们把连接 $x$ 与它父亲的边的权值放在 $x$ 上.
对于一条拆分后的"简单"路径 $(u,v)[dep_u < dep _v]$, 给这条路径上最浅的边 $(u,u_{son})$ 的权值+1,(放在 $w[u_{son}]$上) 然后做一次树上的前缀和, 那么这条路径的答案就是 $sum[v]-sum[u]$.

可以这样理解: 一个拆分后的路径的最浅边相当于一维模型中的 $L_x$ , 最深边相当于 $R_x$, 那么 $L_x-1$ 即为路径中最浅边上面的边, 即连接最高点 $u$ 与其父亲的边.

注意一下最浅边重合的情况, 即 $L$ 相等的情况, 处理方式和一维无差别.

----------
贴上代码:
```
#include<cstdio>
#include<cstdlib>
#include<map>
#include<algorithm>
#define maxn 400005
#define ll long long
using namespace std;
int pre[maxn],to[maxn],las[maxn],mk[maxn],sum[maxn],inc;
int fa[maxn][22],dep[maxn],st[maxn],en[maxn],lca[maxn],n,m;
ll ans=0;
void ins(int a,int b){pre[++inc]=las[a],las[a]=inc,to[inc]=b;}
void GetFa(int x,int f)
{
    dep[x]=dep[f]+1,fa[x][0]=f;
    for(int i=1;i<=21;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=las[x],y=to[i];i;i=pre[i],y=to[i])
        if(y!=f) GetFa(y,x);
}
void dfs(int x,int f,int now)
{
    sum[x]=(now+=mk[x]);
    for(int i=las[x],y=to[i];i;i=pre[i],y=to[i])
        if(y!=f) dfs(y,x,now);
}
int LCA(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    int delta=dep[x]-dep[y];
    for(int i=21;i>=0;i--)
        if((delta>>i)&1) x=fa[x][i];
    if(x==y) return x;
    for(int i=21;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int Close(int x,int anc)
{
    if(x==anc) return -1;
    for(int i=21;i>=0;i--)
        if(fa[x][i]&&dep[fa[x][i]]>dep[anc]) x=fa[x][i];
    return x;
}
map<pair<int,int>,int> mp;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<n;i++)
        scanf("%d%d",&u,&v),ins(v,u),ins(u,v);
    GetFa(1,0);
    for(int i=n;i<=m;i++)
    {
        scanf("%d%d",&st[i],&en[i]);
        lca[i]=LCA(st[i],en[i]);
        int ux=Close(st[i],lca[i]);
        int uy=Close(en[i],lca[i]);
        if(ux!=-1) ans-=(++mk[ux]);
        if(uy!=-1) ans-=(++mk[uy]);
        if(ux!=-1&&uy!=-1)
        {
            if(ux>uy) swap(ux,uy);
            ans-=(mp[make_pair(ux,uy)]++);
        }
    }
    dfs(1,0,0);
    for(int i=n;i<=m;i++)
        ans+=sum[st[i]]+sum[en[i]]-2*sum[lca[i]];
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：feecle6418 (赞：6)

题意就是算非树边覆盖的树边有交的对数。

可以枚举一条边，树上差分求出它被几条非树边覆盖，设为 $c$，则这条边带来了 $\binom c2$ 的答案。可惜这样会算重。

注意到问题在于，两条链的交是一条链，这条链上的所有边都会算一次，但一共只该被算一次。

用改进的点 - 边容斥，算 边的答案 - 两条边的答案即可。两条边的答案除了 LCA 那里都可以树上差分，LCA 处可以用个 map 统计。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pr;
int n, m, cnt, h[200005], p[200005][20], d[200005], c2[200005], c1[200005];
long long ans = 0;
map<pr, int> mp;
struct Edge {
	int to, next;
} e[400005];
void Add_Edge(int x, int y) {
	e[++cnt].to = y;
	e[cnt].next = h[x];
	h[x] = cnt;
}
void DFS(int x, int fa) {
	p[x][0] = fa, d[x] = d[fa] + 1;
	for (int i = h[x]; i; i = e[i].next) {
		int y = e[i].to;
		if (y == fa) continue;
		DFS(y, x);
	}
}
void MakeST() {
	for (int j = 1; j <= 18; j++) {
		for (int i = 1; i <= n; i++) p[i][j] = p[p[i][j - 1]][j - 1];
	}
}
int LCA(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	for (int i = 18; i >= 0; i--)
		if (d[p[x][i]] >= d[y]) x = p[x][i];
	if (x == y) return x;
	for (int i = 18; i >= 0; i--)
		if (p[x][i] ^ p[y][i]) x = p[x][i], y = p[y][i];
	return p[x][0];
}
int Getson(int x, int lca) {
	if (x == lca) return 0;
	for (int i = 18; i >= 0; i--)
		if (d[p[x][i]] > d[lca]) x = p[x][i];
	return x;
}
void DFS2(int x) {
	for (int i = h[x]; i; i = e[i].next) {
		int y = e[i].to;
		if (y != p[x][0]) DFS2(y), c1[x] += c1[y], c2[x] += c2[y];
	}
	ans -= 1ll * c1[x] * (c1[x] - 1) / 2;
	ans += 1ll * c2[x] * (c2[x] - 1) / 2;
	// cout << x << ' ' << c1[x] << ' ' << c2[x] << '\n';
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), Add_Edge(x, y), Add_Edge(y, x);
	DFS(1, 0);
	MakeST();
	for (int i = 1, x, y; i <= m - n + 1; i++) {
		scanf("%d%d", &x, &y);
		int lca = LCA(x, y);
		// c1[x]++, c1[y]++;
		// c1[lca]--;
		// c1[p[lca][0]]--;
		c2[x]++, c2[y]++;
		c2[lca] -= 2;
		if (x != lca && y != lca) {
			c1[x]++;
			c1[y]++;
			int u = Getson(x, lca), v = Getson(y, lca);
			c1[u]--;
			c1[v]--;
			if (u > v) swap(u, v);
			mp[pr(u, v)]++;
		} else {
			if (d[x] > d[y]) swap(x, y);
			if (p[y][0] == x) continue;
			c1[y]++;
			c1[Getson(y, lca)]--;
		}
	}
	DFS2(1);
	for (auto [x, y] : mp) ans -= 1ll * y * (y - 1) / 2;
	printf("%lld\n", ans);
}
```

---

## 作者：Prean (赞：4)

这个去重给写麻了。。。。。。

显然对于两条非树边，其只能组成最多一条回路。构造方式是将两条非树边在树上的路径中重复的部分去掉，再加上两条非树边即可。

于是考虑如何统计重合的路径。

考虑将一条链拆成两条从祖先到孙子的链。统计这些链相交的情况。

可以注意到只有一个情况会算重：LCA 相同，且对于两组链而言，左边部分的链和右边部分的链均有重合。

即 $u,v$ 的祖先中深度大于 $LCA(u,v)$ 中最深的一对祖先，若两条链的这玩意儿相同会被算重。

直接求出这两个祖先然后丢到 map 里面就行了。

考虑一堆祖先到孙子的链如何统计重合情况。

对深度开一个桶，对于 $u$，树状数组上有值的位置表示有 $CB[x]$ 条链满足，深的那个节点与 $u$ 的 LCA 的深度为 $x$，且浅的那个节点是 $u$ 的祖先。

做起来很简单，只需要回溯之后将这个深度的桶的值移动到父亲即可。由于需要查询区间和所以使用树状数组

但是注意到，如果存在 $(u1,v1),(u2,v2)$ （二元组中后者为前者的祖先）满足 $v2$ 是 $v1$ 的祖先且 $v1$ 是 $u2$ 的祖先会被算两遍，需要去掉这种情况。

这种情况再对深度开一个桶，仍然使用树状数组维护即可。

复杂度 $O(n\log n)$。
```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#include<map>
const int M=2e5+5;
int n,m,ege,dfc,s[M],a[M],b[M],L[M],R[M],h[M],u[M],v[M];int f[M],d[M],siz[M],top[M],son[M];long long ans;
std::map<long long,int>CB;std::vector<int>q[M];int BIT[M],V[M];
struct Edge{
	int v,nx;
}e[M<<1];
inline void Add(const int&u,const int&v){
	e[++ege]=(Edge){v,h[u]};h[u]=ege;
	e[++ege]=(Edge){u,h[v]};h[v]=ege;
}
inline void DFS1(const int&u){
	siz[u]=1;d[u]=d[f[u]]+1;
	for(int v,E=h[u];E;E=e[E].nx)if((v=e[E].v)^f[u])f[v]=u,DFS1(v),siz[u]+=siz[v],siz[v]>siz[son[u]]&&(son[u]=v);
}
inline void DFS2(const int&u,const int&tp){
	top[u]=tp;L[u]=++dfc;if(!son[u])return void(R[u]=dfc);DFS2(son[u],tp);
	for(int E=h[u];E;E=e[E].nx)if(e[E].v^f[u]&&e[E].v^son[u])DFS2(e[E].v,e[E].v);R[u]=dfc;
}
inline int LCA(int u,int v){
	while(top[u]^top[v])d[top[u]]>d[top[v]]?u=f[top[u]]:v=f[top[v]];return d[u]>d[v]?v:u;
}
inline int Find(int u,const int&v){
	while(top[u]^top[v]){
		if(f[top[u]]==v)return top[u];u=f[top[u]];
	}
	return son[v];
}
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline void Mdf(int x,const int&V){
	if(!x)return;::V[x]+=V;while(x<=n)BIT[x]+=V,x+=x&-x;
}
inline int Qry(int x){
	int ans(0);while(x>=1)ans+=BIT[x],x-=x&-x;return ans;
}
inline void DFSX(const int&u){
	Mdf(d[u],b[u]);for(int v,E=h[u];E;E=e[E].nx)if((v=e[E].v)^f[u])DFSX(v);
	for(int&x:q[u])ans+=Qry(d[u])-Qry(x)-1;Mdf(d[u]-1,a[u]);Mdf(d[u]-1,V[d[u]]);Mdf(d[u],-V[d[u]]);
}
inline void DFSY(const int&u){
	Mdf(d[u],b[u]);for(int v,E=h[u];E;E=e[E].nx)if((v=e[E].v)^f[u])DFSY(v);
	for(int&x:q[u])ans-=Qry(d[u])-Qry(x)-1;Mdf(d[u],-b[u]);
}
inline void swap(int&a,int&b){
	int c=a;a=b;b=c;
}
signed main(){
	n=read();m=read()-n+1;for(int u,v,i=1;i<n;++i)u=read(),v=read(),Add(u,v);
	for(int i=1;i<=m;++i)u[i]=read(),v[i]=read();DFS1(1);DFS2(1,1);
	for(int i=1;i<=m;++i){
		const int&lca=LCA(u[i],v[i]);if(L[u[i]]<L[v[i]])swap(u[i],v[i]);
		if(L[v[i]]<=L[u[i]]&&R[u[i]]<=R[v[i]]){
			--a[Find(u[i],v[i])];++b[u[i]];q[u[i]].push_back(d[v[i]]);++s[u[i]];continue;
		}
		const int&x=Find(u[i],lca),&y=Find(v[i],lca);ans-=CB[(n+1ll)*x+y];++CB[(n+1ll)*x+y];++CB[(n+1ll)*y+x];
		--a[x];--a[y];++b[u[i]];++b[v[i]];q[u[i]].push_back(d[lca]);q[v[i]].push_back(d[lca]);++s[u[i]];++s[v[i]];
	}
	DFSX(1);DFSY(1);for(int i=1;i<=n;++i)ans+=s[i]*(s[i]-1ll)/2;printf("%lld",ans);
}
```

---

## 作者：ywy_c_asm (赞：2)

这题似乎做法很多啊……

~~手玩可知~~我们要求有多少对边相交的被非树边覆盖的路径，可以转化为对每条路径求有多少路径和他不相交，然后我们开始大力讨论——

![](https://cdn.luogu.com.cn/upload/pic/56554.png)

其中A是当前的边，B是要统计的边，我们令$f[i]$为LCA在i子树的路径的个数，对于情况6直接上$f[i]$，对于情况1和情况2我们可以使用换根dp，设$g[i]$为i到根的一条链上，不在i子树且与这条链无边交的路径数，这个从上到下转移，但是这个要算一棵子树到另一棵子树之间有多少路径，这个我们求出dfs序然后二维数点，这个用主席树来做，求出$g$之后就能算了。对于情况3我们用树状数组在端点的子树上进行区间加，在LCA上统计。情况4和情况5比较特殊，他涉及到到根的这条链的细枝末节之间的路径，我们用$h[i]$进行统计，在换根dp的时候把其他儿子与子树外的部分二维数点统计一下就行了。注意特判直上直下的路径。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	typedef struct _b {
	    int dest;
	    int nxt;
	} bian;
	bian memchi[500001];
	int gn = 1, heads[200001];
	inline void add(int s, int t) {
	    memchi[gn].dest = t;
	    memchi[gn].nxt = heads[s];
	    heads[s] = gn;
	    gn++;
	}
	int lef[5000001], rgh[5000001], data[5000001], gseg = 1, root[200001], dfn[200001], c[300001], gdfn = 1;
	int query(int rl, int rr, int l, int r, int tree1, int tree2) {
	    if (rl == l && rr == r)
	        return (data[tree2] - data[tree1]);
	    int mid = (l + r) >> 1;
	    if (rl > mid)
	        return (query(rl, rr, mid + 1, r, rgh[tree1], rgh[tree2]));
	    if (rr <= mid)
	        return (query(rl, rr, l, mid, lef[tree1], lef[tree2]));
	    return (query(rl, mid, l, mid, lef[tree1], lef[tree2]) +
	            query(mid + 1, rr, mid + 1, r, rgh[tree1], rgh[tree2]));
	}
	int insert(int l, int r, int tree, int pt) {
	    int me = gseg;
	    gseg++;
	    data[me] = data[tree] + 1;
	    if (l == r)
	        return (me);
	    int mid = (l + r) >> 1;
	    if (pt <= mid)
	        lef[me] = insert(l, mid, lef[tree], pt), rgh[me] = rgh[tree];
	    else
	        lef[me] = lef[tree], rgh[me] = insert(mid + 1, r, rgh[tree], pt);
	    return (me);
	}
	int fan[200001];
	vector<int> vec[200001];
	int size[200001];
	inline int Ewsd(int l1, int r1, int l2, int r2) {
	    if (l1 > r1 || l2 > r2)
	        return (0);
	    if (l1 < l2)
	        swap(l1, l2), swap(r1, r2);
	    return (query(l1, r1, 1, gdfn - 1, root[l2 - 1], root[r2]));
	}
	int deep[200001], ance[200001][19], lg[200001];
	void dfs(int pt, int baba) {
	    size[pt] = 1;
	    dfn[pt] = gdfn;
	    fan[gdfn] = pt;
	    gdfn++;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        ance[memchi[i].dest][0] = pt;
	        deep[memchi[i].dest] = deep[pt] + 1;
	        dfs(memchi[i].dest, pt);
	        size[pt] += size[memchi[i].dest];
	    }
	}
	inline int lca(int a, int b) {
	    if (deep[a] > deep[b])
	        swap(a, b);
	    for (register int i = lg[deep[b]]; i >= 0; i--) {
	        if (deep[ance[b][i]] >= deep[a])
	            b = ance[b][i];
	    }
	    if (a == b)
	        return (a);
	    for (register int i = lg[deep[a]]; i >= 0; i--) {
	        if (ance[a][i] != ance[b][i])
	            a = ance[a][i], b = ance[b][i];
	    }
	    return (ance[a][0]);
	}
	int f[200001], g[200001], ss[400001], ts[400001], ls[200001], c1[200011], dh[200001];
	void efs(int pt, int baba) {
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        efs(memchi[i].dest, pt);
	        f[pt] += f[memchi[i].dest];
	    }
	}
	int dg[200001];
	void ffs(int pt, int baba) {
	    int sig = 0;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        dg[memchi[i].dest] +=
	            Ewsd(1, dfn[pt] - 1, dfn[memchi[i].dest], dfn[memchi[i].dest] + size[memchi[i].dest] - 1);
	        dg[memchi[i].dest] += Ewsd(dfn[memchi[i].dest], dfn[memchi[i].dest] + size[memchi[i].dest] - 1,
	                                   dfn[pt] + size[pt], gdfn - 1);
	        sig += dg[memchi[i].dest];
	    }
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        dh[memchi[i].dest] = dh[pt] + sig - dg[memchi[i].dest];
	        g[memchi[i].dest] = g[pt] + f[pt] - f[memchi[i].dest];
	        g[memchi[i].dest] -= Ewsd(dfn[pt], dfn[memchi[i].dest] - 1, dfn[memchi[i].dest],
	                                  dfn[memchi[i].dest] + size[memchi[i].dest] - 1);
	        g[memchi[i].dest] -= Ewsd(dfn[memchi[i].dest], dfn[memchi[i].dest] + size[memchi[i].dest] - 1,
	                                  dfn[memchi[i].dest] + size[memchi[i].dest], dfn[pt] + size[pt] - 1);
	    }
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        ffs(memchi[i].dest, pt);
	    }
	}
	inline int chget(int pt, int yeye) {
	    for (register int i = lg[deep[pt]]; i >= 0; i--)
	        if (deep[ance[pt][i]] > deep[yeye])
	            pt = ance[pt][i];
	    return (pt);
	}
	void ywymain() {
	    deep[0] = -1;
	    int n = get(), m = get();
	    lg[0] = -1;
	    for (register int i = 1; i < n; i++) {
	        int s = get(), t = get();
	        add(s, t);
	        add(t, s);
	        lg[i] = lg[i - 1];
	        if (i == (i & -i))
	            lg[i]++;
	    }
	    dfs(1, 0);
	    for (register int i = 1; i <= lg[n - 1]; i++) {
	        for (register int j = 1; j <= n; j++) ance[j][i] = ance[ance[j][i - 1]][i - 1];
	    }
	    int all = 0;
	    for (register int i = n; i <= m; i++) {
	        int s = get(), t = get();
	        if (s == t)
	            continue;
	        int l = lca(s, t);
	        if (dfn[s] > dfn[t])
	            swap(s, t);
	        ss[i] = s;
	        ts[i] = t;
	        ls[i] = l;
	        all++;
	        vec[dfn[s]].push_back(dfn[t]);
	        if (s != l) {
	            for (register int j = dfn[s]; j <= n; j += (j & -j)) c1[j]++;
	            for (register int j = dfn[s] + size[s]; j <= n; j += (j & -j)) c1[j]--;
	        }
	        for (register int j = dfn[t]; j <= n; j += (j & -j)) c1[j]++;
	        for (register int j = dfn[t] + size[t]; j <= n; j += (j & -j)) c1[j]--;
	        f[l]++;
	    }
	    for (register int i = 1; i <= n; i++) {
	        root[i] = root[i - 1];
	        for (register int j = 0; j < vec[i].size(); j++) {
	            root[i] = insert(1, n, root[i], vec[i][j]);
	        }
	    }
	    efs(1, 0);
	    ffs(1, 0);
	    ll ans = 0;
	    for (register int i = n; i <= m; i++) {
	        if (!ss[i])
	            continue;
	        int tot = 0;
	        for (register int j = dfn[ls[i]]; j > 0; j -= (j & -j)) tot += c1[j];
	        tot++;
	        if (ss[i] == ls[i]) {
	            tot += g[ts[i]];
	            tot += f[ts[i]];
	            tot += dh[chget(ts[i], ss[i])];
	        } else {
	            int ds = chget(ss[i], ls[i]), dt = chget(ts[i], ls[i]);
	            tot += (g[ts[i]] - g[dt]);
	            tot += (g[ss[i]] - (g[ds] - g[ls[i]]));
	            tot += f[ls[i]];
	            tot -= f[ds];
	            tot -= f[dt];
	            tot += Ewsd(dfn[ds], dfn[ds] + size[ds] - 1, dfn[dt], dfn[dt] + size[dt] - 1);
	            tot -= Ewsd(dfn[ls[i]], dfn[ds] - 1, dfn[ds], dfn[ds] + size[ds] - 1);
	            tot -= Ewsd(dfn[ds], dfn[ds] + size[ds] - 1, dfn[ds] + size[ds], dfn[ls[i]] + size[ls[i]] - 1);
	            tot -= Ewsd(dfn[ls[i]], dfn[dt] - 1, dfn[dt], dfn[dt] + size[dt] - 1);
	            tot -= Ewsd(dfn[dt], dfn[dt] + size[dt] - 1, dfn[dt] + size[dt], dfn[ls[i]] + size[ls[i]] - 1);
	            tot += dh[ds];
	            tot -= dg[dt];
	            tot += f[ss[i]];
	            tot += f[ts[i]];
	        }
	        ans += (all - tot);
	    }
	    cout << ans / 2 << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：asuldb (赞：2)

[题目](https://www.luogu.org/problemnew/show/P5203)

这题的数据有点水，暴力合并$set$好像过了

分析一下这个题的性质，发现我们一条非树边就会形成一个环，而我们要求选择两个非树边，就会形成两个环，要求不走重复的点，就是说我们需要走一个大环，且必须经过这两个小环

显然需要这两个小环有至少一条公共边

发现问题转化成了求**有多少对路径，这对路径有公共边**

应该可以用数据结构来维护大力讨论的，当然树上差分的正解思路也非常妙

~~于是我们写个暴力吧！~~

对于这道题我第一想法是启发式合并$set$，我们可以利用如同树上差分那样的方式，对于一条路径$(u,v)$，我们在$u,v$处打上一个标记，在$lca(u,v)$再打上一个删除标记，每次合并$set$的时候，往$set$里插入的所有标记都表明**这个标记代表的路径经过了这条边**，这样这条路径就可以和原来$set$里的标记任意组合了，就可以统计答案了

但是会和正解树上差分遇到一样的问题，就是如果两条路径的公共边形成的不是一条链，这对路径我们会计算两次

这里采用和正解一样的方法就好了，就是利用一个$map$来找到这样的路径有多少对

到这里复杂度还非常正常，是有点大的$O(nlog^2n)$，但是我们又发现我们好像没有什么办法去利用删除标记

如果每次合并前都要扫一遍删除集合的话，复杂度显然就不对了，菊花树随便卡掉

于是我们启发式删除，看看维护删除集合小还是待合并集合小，那个小就遍历哪一个

还是过不去怎么办，那就把$set$换成unordered_set，信仰一下就可以了

代码

```cpp
#include<tr1/unordered_set>
#include<tr1/unordered_map>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 200005
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define set_it unordered_set<int>::iterator
# define getchar() (S==T&&(T=(S=BB)+fread(BB,1,1<<15,stdin),S==T)?EOF:*S++)
using namespace std::tr1;
char BB[1 << 18],*S=BB,*T=BB; 
inline int read() {
    int x=0;char c=getchar();while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
struct E{int v,nxt;}e[maxn<<1];
int head[maxn],deep[maxn],sum[maxn],fa[maxn],top[maxn],son[maxn],f[maxn][19],st[maxn];
int n,m,num,cnt,md,t;
int rt[maxn];
LL ans;
unordered_set<int> s[maxn],del[maxn];
unordered_map<LL,int> ma;
inline void add(int x,int y) {e[++num].v=y;e[num].nxt=head[x];head[x]=num;}
void dfs1(int x) {
    sum[x]=1;int maxx=-1;
    for(re int i=head[x];i;i=e[i].nxt) {
        if(deep[e[i].v]) continue;
        deep[e[i].v]=deep[x]+1;fa[e[i].v]=x;f[e[i].v][0]=x;
        for(re int j=1;j<=18;j++) f[e[i].v][j]=f[f[e[i].v][j-1]][j-1];
        dfs1(e[i].v);
        sum[x]+=sum[e[i].v];
        if(sum[e[i].v]>maxx) maxx=sum[e[i].v],son[x]=e[i].v;
    }
}
void dfs2(int x,int topf) {
    top[x]=topf;
    if(!son[x]) return;
    dfs2(son[x],topf);
    for(re int i=head[x];i;i=e[i].nxt) {
        if(top[e[i].v]) continue;
        dfs2(e[i].v,e[i].v);
    }
}
inline int LCA(int x,int y) {
    while(top[x]!=top[y]) {
        if(deep[top[x]]<deep[top[y]]) std::swap(x,y);
        x=fa[top[x]];
    }
    if(deep[x]<deep[y]) return x;return y;
}
inline void D(int a,int c) {
    if(del[c].size()<s[a].size()) {
    	for(set_it it=del[c].begin();it!=del[c].end();++it) {
        	int x=*it;
        	s[a].erase(x);
    	}
    	return;
    }
    t=0;
    for(set_it it=s[a].begin();it!=s[a].end();++it) 
        if(del[c].find(*it)!=del[c].end()) st[++t]=*it;
    while(t) s[a].erase(st[t--]);
}
inline void merge(int a,int b,int c) {
    int now=s[a].size();
    for(set_it it=s[b].begin();it!=s[b].end();++it) {
        int x=*it;
        if(del[c].find(x)!=del[c].end()) continue;
        ans+=now;s[a].insert(x);
    }
}
inline int jump(int x,int y) {
    for (re int i=18;i>=0;--i) if(deep[x]-(1<<i)>deep[y]) x=f[x][i];
	return x;
}
void dfs(int x) {
	D(rt[x],x);
    for(re int i=head[x];i;i=e[i].nxt) {
        if(deep[e[i].v]<deep[x]) continue;
        dfs(e[i].v);
        if(s[rt[e[i].v]].size()<=s[rt[x]].size()) {
            if(x!=1) merge(rt[x],rt[e[i].v],x);
        }
        else {
            D(rt[e[i].v],x);
            if(x!=1) merge(rt[e[i].v],rt[x],x),rt[x]=rt[e[i].v];
        }
    }
}
int main() {
    n=read(),m=read();int x,y,z;
    for(re int i=1;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
    deep[1]=1,dfs1(1),dfs2(1,1);
    for(re int i=1;i<=n;i++) rt[i]=i;
    for(re int i=n;i<=m;i++) {
        x=read(),y=read();z=LCA(x,y);
        if(x==y) continue;
        if(deep[x]<deep[y]) std::swap(x,y);
        ans+=s[x].size();
        if(z!=y) ans+=s[y].size();
        s[x].insert(i);
        if(z!=y) s[y].insert(i);
        del[z].insert(i);
        if(x==z||y==z) continue;
        int xx=jump(x,z),yy=jump(y,z);
        if(xx>yy) std::swap(xx,yy);
        ans-=ma[(LL)xx*(LL)n+yy];ma[(LL)xx*(LL)n+yy]++;
    }
    dfs(1);
    printf("%lld\n",ans);
}
```


---

## 作者：2021cyq (赞：1)

不难发现一个结论：如果两条非树边的边它们路径之间有交集，则可以计入答案。

那么问题变成了计数问题。

考虑在一条链上怎么做：

有左右端点 $l,r$，对于每一个 $l$ 找其他 $l_1$ 使得 $l\leq l_1 \leq r$。

那么前缀和一下即可 。

现在再考虑一下树上怎么做。

我们可以把 $x\to y$ 拆成 $x\to LCA(x,y)\to y$。

于是转化为两条链的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/632ycheb.png)

如上图

我们发现实际答案是 $3$，但是如果不去重我们发现实际答案是 $18$，这是为什么呢？

我们发现左边三个点每个的贡献都是 $3$，所以左边三个点的贡献和是 $9$。

为什么？

应为它们的 $l$ 是相同的，所以互相都算了一次。

所以第一种去重是对于 $l$ 相同的链，设 $x$ 为 $l$ 相同的链的个数，答案要减去 $\frac{x\times (x+1)}{2}$。

那么我们按照这种去重方式，发现答案从 $18$ 变成了 $6$ ($18-\frac{3\times4}{2}-\frac{3\times4}{2}$，即为左边右边都减去了 $l$ 相同的情况)。

但是还是不对，因为它们是包含关系左右算的是同样的情况，所以对这种情况也要去重。

如果直接在 $LCA$ 记录非树边的$LCA$的数量是错的，因为 $LCA$ 可能有多个子树，但两个不同子树的非树边不会对答案产生贡献。

所以直接记录有多少条非树边的 $topx,topy$ (即为上图的 $x$ 和 $y$ )是相等的，那么答案就要减去 $\frac{sum_{topx,topy}\times (sum_{topx,topy})}{2}$。

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+5;
int head[N],nex[N],to[N],tot;
int fa[N][20],deep[N];
int xxx[N],yyy[N],n,m;
ll sum[N],ans;
map<pair<int,int>,int>s;
void add(int x,int y)
{
	tot++;
	nex[tot]=head[x];
	head[x]=tot;
	to[tot]=y;
}
int LCA(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	for(int i=18;i>=0;i--)
		if(deep[fa[x][i]]>=deep[y])
			x=fa[x][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int top(int x,int y)
{
	if(x==y)return 0;
	for(int i=18;i>=0;i--)
		if(deep[fa[x][i]]>deep[y])
			x=fa[x][i];
	sum[x]++;
	return x;
}
void dfs(int x)
{
	for(int i=head[x];i;i=nex[i])
	{
		int y=to[i];
		if(y!=fa[x][0])
		{
			fa[y][0]=x;
			deep[y]=deep[x]+1;
			dfs(y);
		}
	}
}
void dfs1(int x)
{
	for(int i=head[x];i;i=nex[i])
	{
		int y=to[i];
		if(y!=fa[x][0])
		{
			sum[y]+=sum[x];
			dfs1(y);
		}
	}
}
int main()
{
	freopen("exercise.in","r",stdin);
	freopen("exercise.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&xxx[i],&yyy[i]);
		if(i<n)
		{
			add(xxx[i],yyy[i]);
			add(yyy[i],xxx[i]);
		}
	}
	deep[1]=1;
	dfs(1);
	for(int i=1;i<=19;i++)
		for(int j=1;j<=n;j++)
			fa[j][i]=fa[fa[j][i-1]][i-1];
	for(int i=n;i<=m;i++)
	{
		int x=xxx[i],y=yyy[i];
		int lca=LCA(x,y);
		int topx=top(x,lca),topy=top(y,lca);
		if(topx>topy)swap(topx,topy);
		if(topx&&topy)
		{
			ll noww=s[make_pair(topx,topy)];
			s[make_pair(topx,topy)]++;
			ans=ans+noww*(noww-1)/2-noww*(noww+1)/2;
		}
	}
	for(int i=1;i<=n;i++)ans=ans-sum[i]*(sum[i]+1)/2;
	dfs1(1);
	for(int i=n;i<=m;i++)
	{
		int lca=LCA(xxx[i],yyy[i]);
		ans=ans+sum[xxx[i]]+sum[yyy[i]]-2*sum[lca];
	}
	printf("%lld",ans);
}
```

---

## 作者：devout (赞：1)

考虑两条非树边可以选当且仅当他们在树上的路径有交

考虑把一条路径拆成直上直下的两条

现在的问题是计算这样的路径之间有几个交集

为了保证不算重，我们对于每条路径只统计起始点在他下面且和他有交集的

对于这种情况我们只需要把 $x$ 跳到 $lca$ 的儿子 $topx$ 在这里打上标记，最后统计一下前缀和计算答案就可以

但是对于 $(x,lca)$ 和 $(y,lca)$ 都有交集的部分，我们会算重

所以开一个 map 记录二元组 $(topx,topy)$ 的个数，每次减掉即可

对于两条起点相同并且有公共部分的链，我们会算两次，这种也直接利用标记数组减掉就可以了

$\mathcal O(n\log n)$

```cpp
int n,m;
int head[N],cnt;
int st[N][20],dep[N];
int cf[N];
int X[N<<1],Y[N<<1],tot;
map<PII,int> var;
ll ans;

struct Edge{
	int to,next;	
}e[N<<1];

void add(int x,int y){
	e[++cnt]=(Edge){y,head[x]},head[x]=cnt;	
}

int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y); 
	_Rep(i,19,0)if(dep[st[x][i]]>=dep[y])x=st[x][i];
	if(x==y)return x;
	_Rep(i,19,0)if(st[x][i]!=st[y][i])x=st[x][i],y=st[y][i];
	return st[x][0];
}

void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;
	st[u][0]=fa;
	Rep(i,1,19)st[u][i]=st[st[u][i-1]][i-1];
	RepG(i,u){
		int v=e[i].to;
		if(v==fa)continue;
		dfs1(v,u);	
	}
}

void dfs2(int u,int fa){
	cf[u]+=cf[fa];
	RepG(i,u){
		int v=e[i].to;
		if(v==fa)continue;
		dfs2(v,u);	
	}
}

int main()
{
	memset(head,-1,sizeof(head));
	read(n),read(m);
	Rep(i,1,n-1){
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	Rep(qwq,n,m){
		int x,y;
		read(x),read(y);
		int tpx=-1,tpy=-1;
		int LCA=lca(x,y);
		if(x!=LCA){
			int xx=x;
			_Rep(i,19,0)if(dep[st[xx][i]]>dep[LCA])xx=st[xx][i];
			tpx=xx;	
		}
		if(y!=LCA){
			int yy=y;
			_Rep(i,19,0)if(dep[st[yy][i]]>dep[LCA])yy=st[yy][i];	
			tpy=yy;
		}
		if(~tpx){
			cf[tpx]++;	
			ans-=cf[tpx];
			X[++tot]=LCA,Y[tot]=x;
		}
		if(~tpy){
			cf[tpy]++;
			ans-=cf[tpy];
			X[++tot]=LCA,Y[tot]=y;
		}
		if(~tpx&&~tpy){
			if(tpx>tpy)swap(tpx,tpy);
			ans-=var[mkp(tpx,tpy)];	
			var[mkp(tpx,tpy)]++;
		}
	}
	dfs2(1,0);
	Rep(i,1,tot)ans+=cf[Y[i]]-cf[X[i]];
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：felixwu (赞：1)

让我们来考虑一下贝茜可以利用的两条非标准路径。
考虑由标准路径组成的树。我们将把非标准跟踪的“路径”看作它在上述树中两个相应节点之间的路径。如果我们正在考虑的两个非标准路径具有边不相交路径，则不可能使用它们创建一个简单的循环。然而，如果它们的路径确实重叠，那么我们可以创建一个简单的循环。
现在我们有另一个问题，我们如何计算路径重叠的非标准路径对?
我们认为这棵树是任意根的。
让非标准的跟踪从节点A开始到节点B通过其最低共同祖先(LCA)
这是一个有点难处理的形状。
如果我们决定将每个非标准路径都拆分为从A来以及从B来，然后计算重叠路径的个数
用这种计数方法，我们可能会数得过多。然而，我们可以很容易地判断一对是否会被高估。我们看到，只有当两条路径都经过相同的LCA且路径中连接到LCA的两条边相同时，才会出现对的计数过多。然后我们就可以找到这样的对的数量，并将其从我们的答案中删除，因为这允许我们忽略过度计数，并使用非常简单的形状的路径。
我们的问题现在更简单了，我们有从某个节点到它的一个祖先节点的路径我们想要计算重叠的对的数量。
一个相似的，更广为人知的问题是这个，但是是以一维线段的形式。
形式[Ai,Bi]表示有一条直线从Ai开始和结束Bi我们可以用下面的方法解决它。在每一段开始的时候，从你的答案中减去在它之前开始的段数，而在每一段结束的时候，加上在这段结束之前开始的段数。(对于在相同位置开始/结束的段对要稍微小心)。在树形图中，我们可以做同样的事情。我们可以使用深度优先搜索的预计算来计算从每个节点的祖先开始的路径数。对于从一个节点出发的每条路径一个祖先B，我们添加(从祖先的路径开始的路径数B)来回答我们的问题。
我们小心地不去数那些在路径上有相同最低边的对。
感谢Dhruv Rohatgi



```cpp

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define MAXN 200000
 
int N,Q;
vector<int> edges[MAXN];
int x[MAXN], y[MAXN], anc[MAXN];
int p[MAXN][20];
int d[MAXN];
 
int numInters[MAXN];
int psInters[MAXN];
map<pair<int,int>, int> MP;
 
void dfs(int i,int par,int depth)
{
	p[i][0] = par;
	d[i] = depth;
	for(int j=0;j<edges[i].size();j++)
		if(edges[i][j]!=par)
			dfs(edges[i][j],i, depth+1);
}
 
void dfsSum(int i, int ps)
{
	psInters[i] = ps;
	for(int j=0;j<edges[i].size();j++)
		if(edges[i][j]!=p[i][0])
			dfsSum(edges[i][j], ps + numInters[edges[i][j]]);
}
 
void precompute()
{
	dfs(0, -1, 0);
	for(int j=1;j<20;j++)
		for(int i=0;i<N;i++)
		{
			if(p[i][j-1]==-1)
				p[i][j] = -1;
			else
				p[i][j] = p[p[i][j-1]][j-1];
		}
}
 
int lca(int a,int b)
{
	for(int j=19;j>=0;j--)
		if(d[p[a][j]] >= d[b])
			a = p[a][j];
	for(int j=19;j>=0;j--)
		if(d[p[b][j]] >= d[a])
			b = p[b][j];
	for(int j=19;j>=0;j--)
		if(p[a][j]!=p[b][j])
			a = p[a][j], b = p[b][j];
	if(a==b) return a;
	return p[a][0];
}
 
int topEdge(int top,int bot)
{
	if(top==bot)
		return -1;
	for(int j=19;j>=0;j--)
		if(d[p[bot][j]] > d[top])
			bot = p[bot][j];
	return bot;
}
 
long long choose2(int m)
{
	return (((long long) m)*(m-1))/2;
}
 
int main()
{
	int M,a,b;
	cin >> N >> M;
	Q = M - (N-1);
	for(int i=0;i<N-1;i++)
	{
		cin >> a >> b;
		a--,b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	precompute();
	long long ans = 0;
	for(int i=0;i<Q;i++)
	{
		cin >> x[i] >> y[i];
		x[i]--,y[i]--;
		anc[i] = lca(x[i],y[i]);
		int topx = topEdge(anc[i], x[i]);
		if(topx != -1)
		{
			ans -= numInters[topx] + 1;
			numInters[topx]++;
		}
		int topy = topEdge(anc[i], y[i]);
		if(topy != -1)
		{
			ans -= numInters[topy] + 1;
			numInters[topy]++;
		}
		if(topx != -1 && topy != -1)
		{
			if(topx>topy) swap(topx,topy);
			ans -= MP[make_pair(topx,topy)];
			MP[make_pair(topx,topy)]++;
		}
	}
	dfsSum(0,0);
	for(int i=0;i<Q;i++)
		ans += psInters[x[i]] + psInters[y[i]] - 2*psInters[anc[i]];
	cout << ans << '\n';
}
```


---

## 作者：West_2_31_1 (赞：0)

通过观察题目可得，两条非树边与树边形成环的充要条件为两点非树边的端点之间的路径有重合部分。

于是题目等价于，给你一大堆路径，问你有边交的路径对数。

于是一个很套路的方法是把 $U \to V$ 的路径断成 $U \to \operatorname{LCA}(U,V)$ 和 $V \to \operatorname{LCA}(U,V)$。

由于我们要统计边交，所以我们钦定每个节点连向其父亲的边的贡献统计到该节点上。

所以实际上 $U \to \operatorname{LCA}(U,V)$ 和 $V \to \operatorname{LCA}(U,V)$ 的边的贡献就是 $\operatorname{LCA}(U,V)$ 的两个连向 $U$ 和 $V$ 的儿子（记为 $Utop$ 和 $Vtop$）的点的贡献。

具体地，假设我们要统计一条数轴上一堆区间的交，其实差分一下，每个区间的贡献直接记为左端点的贡献，再前缀和回去，一个区间覆盖其他区间的数量就是左右端点前缀和的差。

把数轴放在当前节点到树根的链上。

发现有可能算重。

![](https://cdn.luogu.com.cn/upload/image_hosting/6i4jbl65.png)

例如一个 $Utop$ 下挂了多个 $U$，手模发现直接统计的答案为 $cnt^2$，而我们要 $\dbinom{cnt}{2}$。
$$
cnt^2-\dbinom{cnt}{2}=cnt^2-\frac{cnt^2-cnt}{2}=\frac{cnt^2+cnt}{2}=\sum^{cnt}_{i=1}{i}
$$
手动处理每一个 $Utop$ 的贡献多余部分即可（即在加入差分数组之后在 $ans$ 中减掉当前差分数组的值）。

考虑到，若多个树上路径 $U\to V$ 共用一个 $\operatorname{LCA}(U,V)$ 下的一对 $Utop$ 和 $Vtop$。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2mwrnae.png)

此时，$Utop$ 的贡献为 $\dbinom{cnt}{2}$，$Vtop$ 的贡献亦为 $\dbinom{cnt}{2}$，和为 $cnt^2-cnt$。

但实际上，$U\to V$的路径重复对数应该是只有$\dbinom{cnt}{2}$。
$$
cnt^2-cnt-\dbinom{cnt}{2}=cnt^2-cnt-\frac{cnt^2-cnt}{2}=\frac{cnt^2-cnt}{2}=\sum^{cnt}_{i=1}{i-1}
$$
再次手动减去即可。

实现上开个 map 存一下 $Utop$ 和 $Vtop$ 都相同的就可以了（即在加入 map 之前在 $ans$ 中减掉这个 map 的值）。

```cpp
#include<map>
#include<fstream>
#include<iostream>
using namespace std;
int hd[200001],nt[400001],to[400001],cnt=0;
inline void add(int u,int v){
	++cnt,nt[cnt]=hd[u],to[cnt]=v,hd[u]=cnt;
}
int f[200001][18];
int dep[200001];
inline void pre(int x){
	for(int i=1;i<=17;++i){
		f[x][i]=f[f[x][i-1]][i-1];
	}
	for(int i=hd[x];i;i=nt[i])
		if(to[i]^f[x][0]){
			f[to[i]][0]=x;
			dep[to[i]]=dep[x]+1;
			pre(to[i]);
		}
}
int xtop,ytop;
inline int lca(int x,int y){
	if(dep[x]>dep[y]){
		for(int i=17;i>=0;--i){
			if(dep[f[x][i]]>dep[y])x=f[x][i];
		}
		xtop=x;
		x=f[x][0];
	}
	if(x==y)return x;
	for(int i=17;i>=0;--i){
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	}
	xtop=x,ytop=y;
	return f[x][0];
}
int x[200001],y[200001];
int g[200001];
map<pair<int,int>,int>M;
inline void dfs(int x){
	g[x]+=g[f[x][0]];
	for(int i=hd[x];i;i=nt[i])
		if(to[i]^f[x][0]){
			dfs(to[i]);
		}
}
int main(){
	// fstream cin("exercise.in",ios::in),cout("exercise.out",ios::out);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	f[1][0]=1;
	pre(1);
	long long ans=0;
	for(int i=n;i<=m;++i){
		cin>>x[i]>>y[i];
		if(dep[y[i]]>dep[x[i]])swap(x[i],y[i]);
		xtop=ytop=-1;
		int l=lca(x[i],y[i]);
		if(l==y[i]){
			++g[xtop];
			ans-=g[xtop];
		}else{
			++g[xtop];
			ans-=g[xtop];
			++g[ytop];
			ans-=g[ytop];
			if(xtop>ytop)swap(xtop,ytop);
			ans-=M[make_pair(xtop,ytop)]++;
		}
	}
	dfs(1);
	for(int i=n;i<=m;++i){
		int l=lca(x[i],y[i]);
		ans+=g[x[i]]+g[y[i]]-g[l]-g[l];
	}
	cout<<ans<<'\n';
	return 0;
}
```



---

