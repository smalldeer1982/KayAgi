# [NWRRC 2016] Gangsters in Central City

## 题目描述

长期以来，中央城的水供应一直没有问题。城市的排水系统呈现出一棵根树的形式：中央水库位于树根，房屋位于树叶。水通过沿着树的边缘运行的管道从中央水库流向房屋。每个房屋都能获得水。

突然，黑帮占领了一些房屋。作为市长，你非常担心，并想要赶走这些黑帮。因此，你希望停止向被黑帮占领的房屋供水。为此，你可以堵塞排水系统中的一些管道。如果从水库到某个房屋的路径上至少有一根管道被堵塞，那么该房屋将无法获得水。

你非常害怕这些黑帮，所以你决定堵塞最少数量的管道，以使其看起来像是意外。同时，你关心市民，因此对于选择的堵塞管道数量，你希望最小化没有黑帮且无法获得水的房屋数量。

不幸的是，黑帮可能会在一些房屋中出现和消失。因此，你询问科学家在每次黑帮位置变化后所需的最小堵塞管道数量以及没有黑帮且无法获得水的房屋的最小数量。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 6
1 2 1 3 3 3
+ 4
+ 5
+ 6
+ 7
- 6
- 5
```

### 输出

```
1 0
2 0
2 1
2 0
2 1
2 0
```

# 题解

## 作者：zzzyyyyhhhhh (赞：1)

看到有加边和删边，想到线段树分治。发现第一问的答案一定不会超过根节点的度数（删掉根节点的所有边一定符合条件），因此把根节点删掉，分成几个连通块统计。

第一问比较好做，线段树分治维护有几个连通块内有关键点就可以了。

因为每个连通块最多删一条边，所以第二问可以转化为在每个连通块内选一个深度最大的节点使所有此连通块内的关键点都是它的子孙，这条边就是这个点与父亲相连的边。所有关键点的 lca 满足这个条件，所以维护关键点的 lca 即可，预处理这个点是几个叶子节点的祖先即可。

当然，如果你知道树上多个点的 lca 就是 dfs 序最大的点与 dfs 序最小的点的 lca 这个结论的话可以直接线段树维护第二问，数组记录第一问答案。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
#define int long long
int n,m;
vector<int> a[N];
vector<int> ad[N*4],r;
int lc[22][N];
int lg,f[22][N],dep[N];
int siz[N],ls[N];
int ans[N],now[22],k[N];
inline void dfs(int x,int fa)
{
	f[0][x]=fa;
	if(a[x].empty())siz[x]=1;
	for(auto i:a[x])dep[i]=dep[x]+1,dfs(i,x),siz[x]+=siz[i];
}
inline int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=lg;~i;i--)if(dep[f[i][x]]>=dep[y])x=f[i][x];
	if(x==y)return x;
	for(int i=lg;~i;i--)if(f[i][x]!=f[i][y])x=f[i][x],y=f[i][y];
	return f[0][x];
}
#define mid ((l+r)>>1)
#define ll (x<<1)
#define rr (x<<1|1)
inline void add(int l1,int r1,int l,int r,int x,int val)
{
	if(l>=l1&&r<=r1){ad[x].push_back(val);return;}
	if(l1<=mid)add(l1,r1,l,mid,ll,val);
	if(r1>mid)add(l1,r1,mid+1,r,rr,val);
}
int v[N],cnt[N],pp,ans1[N];
inline void get(int l,int r,int x,int dep)
{
	now[dep]=now[dep-1];
	map<int,int> s,s1;
	for(auto i:ad[x])
	{
		now[dep]-=siz[k[f[lg][i]]];
		if(s1.find(f[lg][i])==s1.end())s1[f[lg][i]]=k[f[lg][i]];
		if(k[f[lg][i]])k[f[lg][i]]=lca(k[f[lg][i]],i);
		else k[f[lg][i]]=i;
		now[dep]+=siz[k[f[lg][i]]];
		s[f[lg][i]]=k[f[lg][i]];
		if(!cnt[f[lg][i]])pp++;
		cnt[f[lg][i]]++;
	}
	if(l==r){ans[l]+=now[dep];ans1[l]=pp;for(auto i:s1)k[f[lg][i.first]]=i.second;for(auto i:ad[x]){cnt[f[lg][i]]--;if(!cnt[f[lg][i]])pp--;}return;}
	get(l,mid,ll,dep+1);
	for(auto i:s)
		k[f[lg][i.first]]=i.second;
	get(mid+1,r,rr,dep+1);
	for(auto i:s1)k[f[lg][i.first]]=i.second;
	for(auto i:ad[x]){cnt[f[lg][i]]--;if(!cnt[f[lg][i]])pp--;}
}
#undef mid
#undef rr
#undef ll
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int x;
	for(int i=2;i<=n;i++)cin>>x,a[x].push_back(i);
	for(auto i:a[1])r.push_back(i);
	for(auto i:r)dfs(i,i);
	lg=__lg(n)+1;
	for(int i=1;i<=lg;i++)
		for(int j=1;j<=n;j++)f[i][j]=f[i-1][f[i-1][j]];
	char c;
	int tmp=0;
	for(int i=1;i<=m;i++)
	{
		cin>>c>>x;
		if(c=='+')ls[x]=i,tmp++;
		else
		{
			add(ls[x],i-1,1,m+1,1,x);
			ls[x]=0;
			tmp--;
		}
		ans[i]=-tmp;
	}
	for(int i=1;i<=n;i++)if(ls[i])add(ls[i],m+1,1,m+1,1,i);
	get(1,m+1,1,1);
	for(int i=1;i<=m;i++)
		cout<<ans1[i]<<' '<<ans[i]<<'\n';
}
```

---

## 作者：Doubeecat (赞：1)

> G.Gangsters in Central City
> 给出一棵含有 $n$ 个节点的，且 $1$ 为根节点的树，叶子节点都是房屋，让你在一个集合里面进行添加房屋和移除房屋的操作。
> 
> 每一次添加和移除后，你将要回答下面两个问题：
> 
> 1.  最少需要砍多少条边，才能使已选房屋都不能从根节点到达。
> 
> 2.  在第 $1$ 问的条件下，如何砍边使从根节点点开始走不能到达的非已选房屋数目最小，输出最小值。
> 
> $n \leq 10^5$

来补一个另外一个题解中说的神乎其神的 set 做法。

对于第一问，我们有个很简单的思考：我们显然只需要砍掉和根节点直接相关联的边即可满足最小。这个的证明十分显然，因为砍掉这些边显然能影响到的点是最多的。

然后我们来考虑第二问，一个最直接的想法：我们需要求出集合中靠的比较近的点的 LCA ，然后砍断这些 LCA 和父亲的连边。接下来就是两个问题：

1. 哪些点算是集合中靠的比较近的点？
2. 怎么找到多个点的 LCA？

第一个问题我们需要结合第一问来思考，第一问中，我们砍掉的都是直接和根节点关联的边，所以我们把集合中的点按照**所属直接关联根节点的子树**来分类。可能有些抽象，结合代码来理解。

```cpp
void dfs2(int x,int anc) {
    bel[x] = anc;//bel 记录的是这个点属于哪个
    for (int i = 0;i < G[x].size();++i) {
        int y = G[x][i];
        dfs2(y,anc);
    }
}
//in main
for (int i = 1;i < n;++i) {
    int x;cin >> x;G[x].push_back(i+1);
    deg[x]++;
    if (x == 1) lis.push_back(i+1);//找出所有和根节点直接相连的点丢进vector里面
} 
for (int i = 0;i < lis.size();++i) {
    dfs2(lis[i],lis[i]);
}
```

这样我们就把点按照从属的子树分成了几类。

第二个问题其实是之前刷知乎找到的，这里（[如何在 DAG 中找多个点的 LCA ? - 阮行止的回答 - 知乎](https://www.zhihu.com/question/46440863/answer/165741734)）有非常详细的证明，不再赘述。这里直接丢结论：**树上多个点的LCA，就是DFS序最小的和DFS序最大的这两个点的LCA。**

所以我们对于每个子树内的点维护一个 `set`，每次取出 dfs 序最大点和 dfs 序最小点求出这些点的 LCA。我们可以算出砍掉一条边的代价为 这个点覆盖的叶子数 - 这棵子树里的被封锁节点数。

对于增加操作，我们先对于原来的 LCA 求出这个 LCA 控制的叶子节点数，再对插入点后的 LCA 求出这个 LCA 控制的叶子节点数，两者相减再扣去当前集合内的点数就是答案。

具体请看代码实现。

Code:

```cpp
int bel[N];//这个点属于哪个子树
int rul[N],dfn[N],cnt,deg[N],vis[N],rk[N];//这个点管辖了几个叶子
int n,q;
bool leaf[N];

vector <int> G[N],lis;

set <int> s[N];

void dfs1(int x) {
    dfn[x] = ++cnt;rk[cnt] = x;//求出每个点dfs序以及每个dfs序对应的点
    for (int i = 0;i < G[x].size();++i) {
        int y = G[x][i];
        dfs1(y);
    }
}

int dfs2(int x,int anc) {
    //printf("%d %d\n",x,anc);
    bel[x] = anc;
    if (leaf[x]) {//求出每个点控制了多少个叶子节点
        return rul[x] = 1;
    } 
    for (int i = 0;i < G[x].size();++i) {
        int y = G[x][i];
        rul[x] += dfs2(y,anc);
    }
    return rul[x];
}
//树剖求LCA
int dep[N],top[N],siz[N],fat[N],son[N],ans1,ans2;

void dfs3(int x,int f) {
    siz[x] = 1,fat[x] = f,dep[x] = dep[f] + 1,son[x] = 0;
    for (int i = 0;i < G[x].size();++i) {
        int y = G[x][i];
        dfs3(y,x);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) {
            son[x] = y;
        }
    }
}

void dfs4(int x,int f) {
    if (son[f] == x) top[x] = top[f];
    else top[x] = x;
    if (son[x]) dfs4(son[x],x);
    for (int i = 0;i < G[x].size();++i) {
        if (G[x][i] != son[x]) dfs4(G[x][i],x);
    }
}

int LCA(int x,int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x,y);
        x = fat[top[x]];
    }
    return (dep[x] < dep[y]) ? x : y;
}

signed main() {
	cin >> n >> q;
    for (int i = 1;i < n;++i) {
        int x;cin >> x;G[x].push_back(i+1);
        deg[x]++;
        if (x == 1) lis.push_back(i+1);//先将直接相连的都丢到一个vector里
    } 
    for (int i = 1;i <= n;++i) {
        if (!deg[i]) leaf[i] = 1;//维护所有叶子节点
    }
    for (int i = 0;i < lis.size();++i) {
        dfs2(lis[i],lis[i]);
    }
    dfs1(1),dfs3(1,0),dfs4(1,0);
    int now = 0,las;
    while (q--) {
        char opt;int x;
        cin >> opt >> x;
        //now保存的是集合里一共有几个点。
        if (opt == '+') {
            ++now;las = 0;
            if (s[bel[x]].size()) {
                int laslca = LCA(rk[*s[bel[x]].begin()],rk[*s[bel[x]].rbegin()]);
                //集合中最小和最大点LCA
                las = rul[laslca];
                //LCA控制的点数
            }
            s[bel[x]].insert(dfn[x]);
            int lca = LCA(rk[*s[bel[x]].begin()],rk[*s[bel[x]].rbegin()]);
            if (!vis[bel[x]]) ++ans1;
            //维护第一问
            ++vis[bel[x]];
            ans2 += rul[lca] - las; 
        } else {
            //与上方广义对称
            --now;las = 0;
            int lca = LCA(rk[*s[bel[x]].begin()],rk[*s[bel[x]].rbegin()]);
            s[bel[x]].erase(dfn[x]);
            --vis[bel[x]];
            if (!vis[bel[x]]) --ans1;
            if (s[bel[x]].size()) {
                int laslca = LCA(rk[*s[bel[x]].begin()],rk[*s[bel[x]].rbegin()]);
                las = rul[laslca];
            }
            ans2 -= rul[lca] - las; 
        }
        printf("%d %d\n",ans1,ans2-now);
    }
	return 0;
}
```

---

## 作者：Elma_ (赞：1)

首先发现这棵树的根并没有什么用。

把根去掉后整棵树裂成了若干颗子树，每颗子树中如果有强盗就需要割掉它们的 lca，否则就不需要。要解决的问题其实就是标记/取消一个关键点，然后询问这些点的 lca。

可以先 dfs 一遍求出欧拉序，然后在每颗子树就是询问区间关键点的 lca。这似乎是一个经典问题，可以在线段树的每个节点存下左右子树的 lca，修改和查询都只要在线段树上查即可，合并也比较容易，但是要注意有某一个儿子为空的情况。

每颗子树的非已选房屋数量就是 lca 子树大小减去子树中叶子节点的数量，这个可以提前 dfs 得到。总时间复杂度 $O(q\log^2 n)$。

需要注意细节，具体看代码。似乎有更加神的 set 做法然而我并不会于是就写了这个阴间玩意，模拟赛时差点没调出来（

```cpp
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>	
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}	
 
const int maxn = 5e5 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }
 
struct node {
	int nxt, to;
}edge[maxn << 1];
int n, q, s, tot, tim, sum, ans1, ans2, head[maxn], from[maxn], vis[maxn], val[maxn];
int dep[maxn], siz[maxn], son[maxn], top[maxn], fa[maxn], st[maxn], ed[maxn], leaf[maxn];
 
inline void addedge(int u, int v) {
	edge[++tot] = (node){head[u], v}, head[u] = tot;
}
inline void dfs1(int u, int fath) {
	dep[u] = dep[fath] + 1;
	siz[u] = 1, son[u] = 0, fa[u] = fath;
	leaf[u] = (head[u] == 0);
	for (int i = head[u];i;i = edge[i].nxt) {
		int v = edge[i].to;
		if (v == fath) continue;
		dfs1(v, u);
		siz[u] += siz[v], leaf[u] += leaf[v];
		if (siz[v] > siz[son[u]])
			son[u] = v;
	}
}
inline void dfs2(int u, int fath) {
	st[u] = ++tim;
	if (u == son[fath]) top[u] = top[fath];
	else top[u] = u;
	if (son[u]) dfs2(son[u], u);
	for (int i = head[u];i;i = edge[i].nxt) {
		int v = edge[i].to;
		if (v != son[u] && v != fath) dfs2(v, u);
	}
	ed[u] = tim;
}
inline void dfs3(int u, int anc) {
	from[u] = anc;
	for (int i = head[u];i;i = edge[i].nxt) 
		if (edge[i].to != fa[u]) dfs3(edge[i].to, anc);
}
inline int getlca(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]])
			x = fa[top[x]];
		else y = fa[top[y]];
	}
	return (dep[x] < dep[y]) ? x : y;
}
 
#define ls(x) x << 1
#define rs(x) x << 1 | 1
inline int merge(int x, int y) {
	if (!x || !y) return x + y;
	return getlca(x, y);
}
inline void modify(int x, int l, int r, int to, int k) {
	if (l == r) { val[x] = k;return; }
	int mid = (l + r) >> 1;
	if (to <= mid) modify(ls(x), l, mid, to, k);
	else modify(rs(x), mid + 1, r, to, k);
	val[x] = merge(val[ls(x)], val[rs(x)]);
} 
inline int query(int x, int l, int r, int ql, int qr) {
	if (l >= ql && r <= qr) return val[x];
	int mid = (l + r) >> 1, res = 0;
	if (ql <= mid) res = query(ls(x), l, mid, ql, qr);
	if (qr > mid) res = merge(res, query(rs(x), mid + 1, r, ql, qr));
	return res;   
} 
inline void insert(int x) {
	if (vis[x]) return;
	int l, r, tmp; ++sum, vis[x] = 1, l = st[from[x]], r = ed[from[x]];
	tmp = query(1, 1, n, l, r); if (tmp) ans1--, ans2 -= leaf[tmp];
	modify(1, 1, n, st[x], x);
	tmp = query(1, 1, n, l, r); if (tmp) ans1++, ans2 += leaf[tmp];
}
inline void remove(int x) {
	if (!vis[x]) return;
	int l, r, tmp; --sum, vis[x] = 0, l = st[from[x]], r = ed[from[x]]; 
	tmp = query(1, 1, n, l, r); if (tmp) ans1--, ans2 -= leaf[tmp];
	modify(1, 1, n, st[x], 0);
	tmp = query(1, 1, n, l, r); if (tmp) ans1++, ans2 += leaf[tmp];
}
#undef ls(x)
#undef rs(x)
 
int main(void) { 
	n = read(), q = read();
	for (int i = 2, fath;i <= n;i++)
		fath = read(), addedge(fath, i);
	dfs1(1, 0), dfs2(1, 1);
	for (int i = head[1];i;i = edge[i].nxt) 
		dfs3(edge[i].to, edge[i].to);
	while (q--) {
		char opt; cin >> opt; int x = read(); 
		if (opt == '+') insert(x);
		else remove(x);
		printf("%d %d\n", ans1, ans2 - sum);
	} 
	return 0;  
}
```


---

## 作者：Redshift_Shine (赞：0)

## 闲话

相比于 [P3684](/problem/P3684) 和 [P4901](/problem/P4901)，这道题对不同知识点的缝合更加自然。

[P7037](/problem/P7037)=ST 表/树链剖分/倍增+思维。

本人认为此题的难点在于推出多个点的 LCA 为 DFS 序最小和最大的点的 LCA。

## 解法

注意到，首先不考虑第二个问题，只考虑最少要砍多少条边，易得最优解法一定是砍与根节点相连的边。

那么考虑第二个问题，不难注意到就是要将本来砍与根节点相邻的边改为砍掉根节点直接子节点为根的每棵子树下的深度最大的节点使得该节点是所有被占节点的祖先。

那么考虑如何高效地维护这个信息。

容易发现整棵树被根节点分成了若干个不交的部分。对于这些不交的部分，我们使用 DFS 分别标记它们处在哪一个节点下辖的子树内。

接下来，利用 `set` 存储每个子树内的被占节点**的 DFS 序**，利用 `set` 自动排序的特性进行处理即可。

哈？你问我怎么求 LCA？既然我们都处理了 DFS 序……那当然要转换成 RMQ 问题啦！根据 DFS 序的性质，我们可以发现一个节点的祖先的 DFS 序一定严格小于这个节点的 DFS 序。于是在使用 ST 表 $O(n\log n)$ 预处理后接下来的询问就都是 $O(1)$ 了！

然而，询问完之后还是要丢进 `set` 里操作。

最终总时间复杂度为 $O(n\log n)$，但是常数极大。

## 代码

```c++
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
int n, m, x, eul[20][N << 1], dfn[N], rnk[N], idx1, siz[N], idx2, lg2[N << 1], ps[N], cl[N], ttsz, ttat, res1;
vector<int> road[N];
set<int> st[N];
char ch;
void dfs(int x)
{
    dfn[x] = ++idx1;
    ps[x] = ++idx2;
    eul[0][idx2] = dfn[x];
    rnk[dfn[x]] = x;
    if (!road[x].size())
    {
        siz[x] = 1;
        return;
    }
    for (auto &i : road[x])
    {
        dfs(i);
        siz[x] += siz[i];
        eul[0][++idx2] = dfn[x];
    }
}
void clr(int x, int tcl)
{
    cl[x] = tcl;
    for (auto &i : road[x])
        clr(i, tcl);
}
void init()
{
    for (int i = 2; i <= idx2 + 1; i++)
        lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= lg2[idx2]; i++)
    {
        for (int j = 1; j + (1 << i) - 1 <= idx2 + 1; j++)
        {
            eul[i][j] = min(eul[i - 1][j], eul[i - 1][(j + (1 << (i - 1)))]);
        }
    }
}
int lca(int x, int y)
{
    x = ps[x], y = ps[y];
    if (x > y)
        swap(x, y);
    int tmp = lg2[y - x + 1];
    return rnk[min(eul[tmp][x], eul[tmp][y - (1 << tmp) + 1])];
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &x);
        road[x].emplace_back(i);
    }
    dfs(1);
    init();
    for (auto &i : road[1])
        clr(i, i);
    for (int i = 1; i <= m; i++)
    {
        cin >> ch;
        scanf("%d", &x);
        if (ch == '+')
        {
            res1 += !st[cl[x]].size();
            ttat++;
            if (st[cl[x]].size())
                ttsz -= siz[lca(rnk[*st[cl[x]].begin()], rnk[*st[cl[x]].rbegin()])];
            st[cl[x]].emplace(dfn[x]);
            ttsz += siz[lca(rnk[*st[cl[x]].begin()], rnk[*st[cl[x]].rbegin()])];
            printf("%d %d\n", res1, ttsz - ttat);
            continue;
        }
        ttat--;
        ttsz -= siz[lca(rnk[*st[cl[x]].begin()], rnk[*st[cl[x]].rbegin()])];
        st[cl[x]].erase(dfn[x]);
        if (st[cl[x]].size())
            ttsz += siz[lca(rnk[*st[cl[x]].begin()], rnk[*st[cl[x]].rbegin()])];
        res1 -= !st[cl[x]].size();
        printf("%d %d\n", res1, ttsz - ttat);
    }
}
```

---

