# [HBCPC2024] Colorful Tree

## 题目描述

给你一棵有 $n$ 个节点的树，节点编号从 $1$ 到 $n$，并且有 $n-1$ 条边。每个节点都有一个颜色。起初，所有节点的颜色都是白色。

我们将进行 $q$ 次操作。在每次操作中，会给出两个顶点 $u$ 和 $v$，然后我们将沿着从 $u$ 到 $v$ 的简单路径上的所有节点（包括 $u$ 和 $v$）染成黑色。注意，树中的简单路径定义为路径上的任意顶点都不会被重复经过。

在每次操作之后，你需要确定树中最长的简单路径，其路径上的所有节点的颜色相同。路径的长度定义为路径上的节点数目。

## 样例 #1

### 输入

```
1
8 6
1 2
1 3
2 4
4 5
2 6
4 8
3 7
4 8
7 7
4 5
2 2
4 6
5 1```

### 输出

```
5
4
4
3
4
4```

# 题解

## 作者：xiezheyuan (赞：4)

## 简要题意

你需要维护一个 $n$ 个点的树，初始时所有点都是白色。有 $m$ 次操作，每次操作给定一条树上简单路径，你需要将路径上所有点染成黑色。

你需要求出最长的同色路径（注意路径上所有点都必须同色，路径长度定义为这条路径上**点**的数量，包含端点）。

$T$ 组数据。$1\leq \sum n,\sum m\leq 2\times10^5$。

## 思路

本来以为是路径端点颜色相同，我还以为是经典题目，写完后测了样例发现不对，这才发现题目要求是路径上所有点的颜色……不过这道题也不难。

首先我们先分开求最长黑色路径和最长白色路径，先求最长黑色路径。一种经典的错误思路是维护黑色 / 白色点集，直接维护点集直径。由于黑色 / 白色点**不一定**构成一个连通块，所以求出来的直径中间可能会夹杂其他颜色的点。

顺着这个思路想，我们可以就维护同色连通块，然后维护这个连通块的直径。维护连通块的首选是并查集。我们可以将直径信息存在并查集的根节点上。但是染色可能会出现一条链染多次的情况。

由于我没有想到这玩意也可以并查集，所以我用到了一个比较劣的方法，我们维护一个点第一个被染成黑色的时刻，显然这个可以离线后倒序枚举询问转换为树上染颜色，可以用重链剖分配合颜色段均摊简单维护。

然后我们按照第一个被染成黑色的时刻顺序依次考虑每一个点，先暴力枚举这个点直接相邻的其他点，如果这个点同样也是黑色点，且还没有和这个点合并为一个连通块，那么我们就可以直接合并，合并并查集的同时也要合并直径信息，在更新直径信息的时候更新当前时刻最大直径。注意这样得到的答案需要做一遍前缀最大值才是真的答案（因为答案显然单调，且可能会有其他连通块未被统计）。

对于最长白色路径，如果按照时间顺序做就是删点，比较难做，我们离线倒着做，就变成了加点，和上面做法几乎一样，就不提了。

至于直径合并，这是经典 trick，两个点集的直径端点，一共四个，我们选出两个点，使得这两个点构成的路径长度最大，这个最长路径就是两个点集的并的直径。

最后将两种答案取 $\max$ 即可，时间复杂度单组数据 $O(n\log n+m\log^2 n)$。瓶颈在重链剖分配合颜色段均摊。

## 代码

5.04 KB 大常数代码，建议不要学。

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 2e5 + 5;

namespace odt{
    struct node{
        int l,r;
        mutable int v;
        node(int L, int R, int V){l = L, r = R, v = V;}
        bool operator<(const node &x) const {return l < x.l;}
    };
    set<node> tree;
    auto split(int pos){
        auto it = tree.lower_bound(node(pos, 0, 0));
        if(it != tree.end() && it -> l == pos) return it;
        it--;
        int l = it -> l, r = it -> r, v = it -> v;
        tree.erase(it);
        tree.insert(node(l, pos - 1, v));
        return tree.insert(node(pos, r, v)).first;
    }
    void assign(int l, int r, int v){
        auto R = split(r + 1), L = split(l);
        tree.erase(L, R);
        tree.insert(node(l, r, v));
    }
    int query(int l, int r){
        auto R = split(r + 1), L = split(l);
        for(auto it = L;it != R;it++){
            return it -> v;
        }
    }
}

struct edge{
    int nxt, to;
} g[N << 1];
int head[N], ec;

void add(int u, int v){
    g[++ec].nxt = head[u];
    g[ec].to = v;
    head[u] = ec;
}

int dep[N], siz[N], father[N], son[N], top[N], seg[N], rev[N];

void dfs1(int u,int fa){
    siz[u] = 1;father[u] = fa;
    dep[u] = dep[fa] + 1;
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u,int fa){
    if(son[u]){
        top[son[u]] = top[u];
        seg[son[u]] = (++seg[0]);
        rev[seg[0]] = son[u];
        dfs2(son[u], u);
    }
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa || son[u] == v) continue;
        top[v] = v;
        seg[v] = (++seg[0]);
        rev[seg[0]] = v;
        dfs2(v, u);
    }
}

int lca(int x, int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = father[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

void UpdateTree(int x,int y,int z){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        odt::assign(seg[top[x]], seg[x], z);
        x = father[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    odt::assign(seg[x], seg[y], z);
}

int dis(int x, int y){
    int b = lca(x, y);
    int a = dep[x] + dep[y] - 2 * dep[b] + 1;
    return a;
}

int fa[N];

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int n, m;
struct option{
    int x, y;
} opt[N];
bool col[N];
int black[N], white[N];

struct diameter{
    int x, y;
} d[N];

diameter operator+(const diameter& x, const diameter& y){
    auto _ = [&](int x, int y){
        return make_pair(dis(x, y), make_pair(x, y));
    };
    vector<pair<int,pair<int,int> > > bkt = {
        _(x.x, x.y), _(y.x, y.y),
        _(x.x, y.x), _(x.y, y.y),
        _(x.x, y.y), _(x.y, y.x)
    };
    auto ret = *max_element(bkt.begin(), bkt.end());
    return {ret.second.first, ret.second.second};
}

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) fa[i] = i;
    for(int i=1;i<n;i++){
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    seg[0] = seg[1] = 1;
    top[1] = rev[1] = 1;
    dfs1(1, 0);dfs2(1, 0);
    odt::tree.clear();
    odt::tree.insert(odt::node(1, n, m + 1));
    for(int i=1;i<=m;i++){
        cin >> opt[i].x >> opt[i].y;
    }
    for(int i=m;i>=1;i--) UpdateTree(opt[i].x, opt[i].y, i);
    vector<pair<int,int> > vp;
    for(int i=1;i<=n;i++){
        int tim = odt::query(seg[i], seg[i]);
        vp.push_back({tim, i});
    }
    sort(vp.begin(), vp.end());
    for(auto& [tim, u] : vp){
        if(tim > m) continue;
        col[u] = 1;
        d[u] = {u, u};
        for(int i=head[u];i;i=g[i].nxt){
            int v = g[i].to;
            if(!col[v]) continue;
            if(find(u) != find(v)){
                d[find(u)] = d[find(u)] + d[find(v)];
                black[tim] = max(black[tim], dis(d[find(u)].x, d[find(u)].y));
                fa[find(v)] = find(u);
            }
        }
    }
    for(int i=1;i<=m;i++) black[i] = max(black[i], black[i - 1]);
    reverse(vp.begin(), vp.end());
    for(int i=1;i<=n;i++) fa[i] = i, col[i] = 0;
    for(auto& [tim, u] : vp){
        col[u] = 1;
        d[u] = {u, u};
        for(int i=head[u];i;i=g[i].nxt){
            int v = g[i].to;
            if(!col[v]) continue;
            if(find(u) != find(v)){
                d[find(u)] = d[find(u)] + d[find(v)];
                white[tim - 1] = max(white[tim - 1], dis(d[find(u)].x, d[find(u)].y));
                fa[find(v)] = find(u);
            }
        }
    }
    for(int i=m-1;i;i--) white[i] = max(white[i], white[i + 1]);
    for(int i=1;i<=m;i++) cout << max(black[i], white[i]) << '\n';
}

void clear(){
    for(int i=1;i<=n;i++){
        head[i] = dep[i] = siz[i] = father[i] = son[i] = top[i] = seg[i] = rev[i] = 0;
    }
    for(int i=1;i<=m;i++){
        white[i] = black[i] = col[i] = 0;
    }
    ec = 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) solve(), clear();
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：luogu_gza (赞：3)

首先，问题等价于求黑色和白色的直径。

我们维护每一个点变黑的时刻（等价于链 checkmin，可以用树剖加线段树解决，倒着做就是链覆盖），那么问题就等价于加点动态维护直径。

我们有性质：有点集 $A$ 与 $B$，设其直径分别为 $(a,b)$ 和 $(c,d)$，则其合并后的直径 $(s,t)$ 满足 $s,t \in \{a,b,c,d\}$。

我们只要判六次距离就能合并两个点集的直径，考虑每一次加边等价于连接连通块，用并查集维护一下即可。

白色的怎么办呢？时光倒流，等价于白色动态加点，再做一遍就好了。

[code](https://www.luogu.com.cn/record/172003675)。

要代码找我。

---

## 作者：lzyqwq (赞：1)

赛时没切被 @[irris](https://www.luogu.com.cn/user/419487) 老师锐评了。

![](https://cdn.luogu.com.cn/upload/image_hosting/k4axx8es.png?x-oss-process=image/resize,m_lfit,h_2170,w_2225)

**[题目传送门](https://www.luogu.com.cn/problem/P10866)**

> - 给出 $n$ 个点的树，初始所有点都为白色。有 $q$ 次操作，每次给出两个点 $u,v$，将 $u,v$ 路径上的所有点变成黑色。每次操作后，您都要输出当前树中最长的由相同颜色的点构成的链的长度。
> - $T$ 组数据。$T\le 100$，$\sum n,\sum q\le 2\times 10^5$。

默认 $\mathcal{O}(n)=\mathcal{O}(q)$。

考虑分别求解黑 / 白连通块的直径。以黑的为例。维护每个时刻的黑色连通块，考虑 $i$ 时刻有哪些点会加进来。

记 $a_x$ 表示第一次覆盖点 $x$ 的操作。若 $x$ 始终为白色，则 $a_x=q+1$。那么对于第 $i$ 次操作，相当于将路径上的点的 $a$ 值全部取 $\min$。所有操作之后需要支持单点查询。

为了方便，将 $a$ 数组的下标映射到 $\text{dfn}$ 序上。

显然可以直接重剖 + 线段树维护，但是考虑优雅一点的做法。注意到每次操作覆盖的值是递增的，因此只需要修改路径上未被修改的点。这样一来每个点至多修改一次。

记 $p_i=1/0$ 表示 $i$ 这个点是否被修改，那我们需要支持的是，单点 $0$ 变 $1$，求单点后继 $0$（下标 $\ge$ 这个位置的下标最小的 $0$ 的位置）。这个可以并查集维护，将后继 $0$ 相同的下标看成一个连通块，在连通块的根上记录这一块的后继 $0$，每次 $0$ 变 $1$ 就是合并相邻的连通块。

对于一个 $\text{dfn}$ 区间的修改，就利用并查集遍历区间中的 $0$，然后在 $a$ 数组上单点修改并将这个连通块与右边合并。

那么这部分的时间复杂度是 $\mathcal{O}(n\alpha(n)\log n)$。因为一次操作中 $\mathcal{O}(\log n)$ 条重链都需要进行一次并查集 `find` 操作。

求出 $a_x$ 后，考虑按时间顺序加入点。

考虑加入点后对于当前黑色连通块有什么影响，显然 $x$ 会与它邻域的点所在的连通块合并。再用一个并查集维护树上黑色连通块，将连通块内部的直径记录在根上。同时记录全局直径。

合并两个连通块时，删去原来直径的贡献，加入新直径的贡献，但由于新直径肯定比原来的大，因此全局直径直接和它取 $\max$ 即可。

现在考虑如何合并两个点集并计算新直径。根据经典结论，新直径的端点一定在原来的直径端点中。证明的话考虑如果不这样一定可以找到一条更长的链。单点构成的连通块的直径显然就是它自己，这在合并前先处理好。

那么我们只需要支持查询树上两点距离即可。分别计算到 $\text{LCA}$ 的距离即可。使用 [DFS 序求 LCA](https://www.luogu.com.cn/article/pu52m9ue) 即可做到 $\mathcal{O}(n\log n)-\mathcal{O}(1)$。代码中给的是这种实现，然而发现根本没必要，瓶颈不在于这里，直接重剖 LCA 也可以而且空间更优。。。

这样黑色连通块直径已经求解完了。但是我们发现如果这样做白色连通块的话，每次的操作会删除一些白点，不好维护。考虑倒序操作，从 $q$ 次操作做完的树开始倒推，则一个点 $x$ 变为白色的时间为 $a_x-1$，类似维护即可。

这题就做完了。时间复杂度为 $\mathcal{O}(n\alpha(n)\log n)$，空间复杂度为 $\mathcal{O}(n\log n)$。然后，多测注意清到 $q+1$！！！

**[AC Link](https://www.luogu.com.cn/record/172111259)**

**[AC Code](https://www.luogu.com.cn/paste/ot6mo8x0)**

目前是你谷最优解。

---

## 作者：Diaоsi (赞：1)

[Colorful Tree](https://www.luogu.com.cn/problem/P10866)

又是这个经典 trick。

先维护染色的过程，由于总的变化次数是 $\mathcal{O}(n)$，所以我们可以暴力维护染色的过程。

考虑先用并查集维护黑色的连通块，在每个集合中记录深度最低的点。染色时模仿求 $\mathrm{lca}$ 的过程不断向上合并，合并完直接跳到当前连通块的最高点。

这样我们就可以对每个点求出这个点变黑的时刻，然后遍历整个时间轴，不断往森林中加点并维护直径。

维护直径的 trick 很经典，具体地说于两个点集 $S$ 和 $T$，其直径端点分别为 $(x,y)$ 和 $(u,v)$，合并两个点集后新的直径的两端点一定出自这四个节点中的两个，共 $\dbinom{4}{2}=6$ 种情况，可以 $\mathcal{O}(1)$ 判断。

这样我们就可以求出黑色部分的答案，白色部分的答案只需要把这个过程倒过来就可以了。

时间复杂度 $\mathcal{O}(n\log n)$。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,m,ans[N],tag[N],col[N],cnt[N],fa[N],sz[N];
int d[N],in[N],out[N],lg[N<<1],st[N<<1][20],ts;
vector<int> h[N],v[N];
struct rec{
	int l,r,len;
}res[N];
void add(int x,int y){
	h[x].push_back(y);
}
void dfs(int x,int fa){
	d[x]=d[fa]+1;
	in[x]=++ts;st[ts][0]=x;
	for(int y:h[x]){
		if(y==fa)continue;
		dfs(y,x);
	}
	out[x]=++ts;
	if(fa)st[ts][0]=fa;
	else st[ts][0]=0;
}
void init(){
	for(int j=1;(1<<j)<=ts;j++)
		for(int i=1;i+(1<<j)-1<=ts;i++){
			int x=st[i][j-1],y=st[i+(1<<(j-1))][j-1];
			st[i][j]=(d[x]<d[y])?x:y;
		}
}
int lca(int x,int y){
	int l=in[x],r=in[y];
	if(l>r)swap(l,r);int ln=lg[r-l+1];
	return d[st[l][ln]]<d[st[r-(1<<ln)+1][ln]]?st[l][ln]:st[r-(1<<ln)+1][ln];
}
int dist(int x,int y){
	return d[x]+d[y]-2*d[lca(x,y)];
}
int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
void merge(int u,int v,int op){
	int x=get(u),y=get(v);
	if(x==y)return;
	if(op&&sz[x]>sz[y])swap(x,y);
	fa[x]=y;sz[y]+=sz[x];
}
void merge(int u,int v){
	int x=get(u),y=get(v);
	int l,r,len=0;
	if(x==y)return;
	int l1=res[x].l,r1=res[x].r;
	int l2=res[y].l,r2=res[y].r;
	int d1=res[x].len,d2=res[y].len;
	int d3=dist(l1,l2),d4=dist(r1,r2);
	int d5=dist(l1,r2),d6=dist(l2,r1);
	if(len<=d1)len=d1,l=l1,r=r1;
	if(len<=d2)len=d2,l=l2,r=r2;
	if(len<=d3)len=d3,l=l1,r=l2;
	if(len<=d4)len=d4,l=r1,r=r2;
	if(len<=d5)len=d5,l=l1,r=r2;
	if(len<=d6)len=d6,l=l2,r=r1;
	merge(x,y,1);
	res[get(x)]=(rec){l,r,len};
}
void solve(){
	ts=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		fa[i]=i,sz[i]=1;
		h[i].clear();
		tag[i]=m+1;
		col[i]=0;
	}
	for(int i=0;i<=m+1;i++)
		cnt[i]=ans[i]=0,v[i].clear();
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	init();
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d",&x,&y);
		z=lca(x,y);
		while(d[x]>=d[z]){
			if(x==get(x))merge(x,st[out[x]][0],0);
			tag[x]=min(tag[x],i);
			x=get(x);
		}
		while(d[y]>=d[z]){
			if(y==get(y))merge(y,st[out[y]][0],0);
			tag[y]=min(tag[y],i);
			y=get(y);
		}
	}
	for(int i=1;i<=n;i++)
		v[tag[i]].push_back(i);
	for(int i=1;i<=n;i++){
		fa[i]=i,sz[i]=1;
		res[i]=(rec){i,i,0};
	}
	for(int i=1;i<=m+1;i++){
		ans[i]=ans[i-1];
		for(int x:v[i]){
			col[x]=1;
			for(int y:h[x]){
				if(col[x]!=col[y])continue;
				merge(x,y);
			}
			ans[i]=max(ans[i],res[get(x)].len);
		}
	}
	for(int i=1;i<=n;i++){
		fa[i]=i,sz[i]=1;
		res[i]=(rec){i,i,0};
	}
	for(int i=m+1;i>=1;i--){
		cnt[i-1]=cnt[i];
		for(int x:v[i]){
			col[x]=0;
			for(int y:h[x]){
				if(col[x]!=col[y])continue;
				merge(x,y);
			}
			cnt[i-1]=max(cnt[i-1],res[get(x)].len);
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",max(ans[i],cnt[i])+1);
}
int main(){
	for(int i=2;i<N<<1;i++)lg[i]=lg[i>>1]+1;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：数据结构，树链剖分，离线，线段树，并查集，直径

[传送门：https://www.luogu.com.cn/problem/P10866](https://www.luogu.com.cn/problem/P10866)

## 题意

给定一颗 $n$ 个顶点的树，一开始全部都是白色节点。需要进行 $q$ 次操作，每次给定树上一条链的两个端点，将这条链上的所有点全部染成黑色。每次操作后所有黑色点和树上连接两个黑色点的边、所有白色点和树上连接两个白色点的边构成了一个森林，求这个森林的直径。

## 分析思路

CSP-S 模拟赛考了这题。前期的思维都对了，就差并查集维护直径的 trick。确实是学到了。

首先对于这棵树，我们可以预处理出每个点第一次被染成黑色的时间。具体来说，我们使用树链剖分，给每个点维护第一次被染成黑色的时间作为点权，初始全部为 $\inf$。每次操作等价于区间取 $\min$，懒标记线段树即可。

预处理完所有店之后，考虑按照时间离线。我们维护一个黑色森林的直径，初始大家都没有连边（那些白色点作为直径为 $1$ 的黑色树，不影响答案）。对于每个点被加入之后，我们检查它的所有连边是不是能放到黑色森林上。于是问题转化为：进行一些连边，动态维护直径。

这时候我们需要用到一个经典结论：给定两个点集 $S, T$，其中 $S$ 的一条直径的两个端点是 $(x, y)$， $T$ 的一条直径的两个端点是 $(u, v)$，则最后直径的两个端点一定在 $\{x, y, u, v\}$ 中四选二产生。所以我们可以用并查集维护动态维护黑森林的直径。

对于白点，我们只要倒着做一遍即可。时间复杂度 $O\left(n \log^2 n\right)$，主要来自树链剖分 + 线段树。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
const int inf = (int)1e9;
struct SegmentTree {
    struct Node {
        int l, r, mn, lazy;
        inline int mid(void) {
            return (l + r) >> 1;
        }
        inline void set_min(int val) {
            mn = min(mn, val), lazy = min(lazy, val);
        }
    } tr[N << 2];
    inline int ls(int p) { return p << 1; }
    inline int rs(int p) { return p << 1 | 1; }
    inline void build(int p, int l, int r) {
        tr[p] = {l, r, inf, inf};
        if (l != r) {
            const int m = (l + r) >> 1;
            build(ls(p), l, m), build(rs(p), m + 1, r);
        }
    }
    inline void maintain(int p) {
        tr[p].mn = min(tr[ls(p)].mn, tr[rs(p)].mn);
    }
    inline void pushdown(int p) {
        if (tr[p].lazy != inf) {
            tr[ls(p)].set_min(tr[p].lazy);
            tr[rs(p)].set_min(tr[p].lazy);
            tr[p].lazy = inf;
        }
    }
    inline void set_min(int p, int l, int r, int v) {
        if (l <= tr[p].l && tr[p].r <= r) {
            return tr[p].set_min(v);
        }
        pushdown(p);
        if (l <= tr[p].mid()) set_min(ls(p), l, r, v);
        if (r > tr[p].mid()) set_min(rs(p), l, r, v);
        maintain(p);
    }
    inline int query(int p, int l, int r) {
        if (l <= tr[p].l && tr[p].r <= r) {
            return tr[p].mn;
        }
        pushdown(p);
        int m = tr[p].mid(), ans = inf;
        if (l <= m) ans = min(ans, query(ls(p), l, r));
        if (r > m) ans = min(ans, query(rs(p), l, r));
        return ans;
    }
} tr;
struct Node {
    int fa, dep, siz, hson, top, id;
    inline void assign(int t, int x) {
        top = t, id = x;
    }
} T[N];
vector<int> G[N];
int t, n, m, u, v, cnt, ans[N], rnk[N], f[N][20];
inline void dfs1(int x, int fa) {
    f[x][0] = fa, T[x] = {fa, T[fa].dep + 1, 1};
    for (int i = 1; (1 << i) <= T[x].dep; i++) {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (auto y : G[x]) {
        if (y == fa) continue;
        dfs1(y, x), T[x].siz += T[y].siz;
        if (T[T[x].hson].siz < T[y].siz) {
            T[x].hson = y;
        }
    }
}
inline void dfs2(int x, int t) {
    T[x].assign(t, ++cnt), rnk[cnt] = x;
    if (T[x].hson) dfs2(T[x].hson, t);
    for (auto y : G[x]) {
        if (y != T[x].fa && y != T[x].hson) dfs2(y, y);
    }
}
inline void Modify(int u, int v, int w) {
    int fu = T[u].top, fv = T[v].top;
    while (fu != fv) {
        if (T[fu].dep >= T[fv].dep) {
            tr.set_min(1, T[fu].id, T[u].id, w);
            u = T[fu].fa, fu = T[u].top;
        } else {
            tr.set_min(1, T[fv].id, T[v].id, w);
            v = T[fv].fa, fv = T[v].top;
        }
    }
    tr.set_min(1, min(T[u].id, T[v].id), max(T[u].id, T[v].id), w);
}
inline int LCA(int u, int v) {
    if (T[u].dep < T[v].dep) swap(u, v);
    while (T[u].dep > T[v].dep) {
        u = f[u][__lg(T[u].dep - T[v].dep)];
    }
    if (u == v) return u;
    for (int k = __lg(T[u].dep); k >= 0; k--) {
        if (f[u][k] != f[v][k]) {
            u = f[u][k], v = f[v][k];
        }
    }
    return f[u][0];
}
inline int dis(int u, int v) {
    return T[u].dep + T[v].dep - 2 * T[LCA(u, v)].dep + 1;
}
struct DiameterDSU {
    int diameter;
    std::vector<int> fa, siz, l, r;
    DiameterDSU(int n) : diameter(1), fa(n + 1), siz(n + 1, 1), l(n + 1), r(n + 1) {
        std::iota(fa.begin(), fa.end(), 0);
        std::iota(l.begin(), l.end(), 0);
        std::iota(r.begin(), r.end(), 0);
    }
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline bool same(int x, int y) {
        return find(x) == find(y);
    }
    // true if x and y were not in the same set, false otherwise.
    inline bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (siz[fx] < siz[fy]) swap(fx, fy);
        std::vector<int> choice = {l[fx], r[fx], l[fy], r[fy]};
        int u = 0, v = 0, ans = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                const int d = dis(choice[i], choice[j]);
                if (d > ans) ans = d, u = choice[i], v = choice[j];
            }
        }
        l[fx] = u, r[fx] = v, diameter = max(diameter, ans);
        fa[fy] = fx, siz[fx] += siz[fy], siz[fy] = 0;
        return true;
    }
};
inline void solve(void) {
    cin >> n >> m, tr.build(1, 1, n), cnt = 0;
    for (int i = 1; i <= n; i++) {
        G[i].clear(), ans[i] = 0;
        memset(f[i], 0x00, sizeof(f[i]));
    }
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    for (int i = 1; i <= m; i++) {
        cin >> u >> v, Modify(u, v, i);
    }
    vector<int> t(n + 1);
    deque<pair<int, int>> Q1, Q2;
    for (int i = 1; i <= n; i++) {
        t[i] = tr.query(1, T[i].id, T[i].id);
        Q1.push_back({t[i], i});
        Q2.push_back({t[i], i});
    }
    DiameterDSU D1(n), D2(n);
    std::sort(Q1.begin(), Q1.end());
    std::sort(Q2.begin(), Q2.end(), greater<>());
    for (int i = 1; i <= m; i++) {
        while (!Q1.empty() && Q1[0].first <= i) {
            auto fr = Q1[0];
            for (auto v : G[fr.second]) {
                if (t[v] <= i) D1.merge(v, fr.second);
            }
            Q1.pop_front();
        }
        ans[i] = D1.diameter;
    }
    for (int i = m; i >= 1; i--) {
        while (!Q2.empty() && Q2[0].first > i) {
            auto fr = Q2[0];
            for (auto v : G[fr.second]) {
                if (t[v] > i) D2.merge(v, fr.second);
            }
            Q2.pop_front();
        }
        ans[i] = max(ans[i], D2.diameter);
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

