# Best Edge Weight

## 题目描述

You are given a connected weighted graph with $ n $ vertices and $ m $ edges. The graph doesn't contain loops nor multiple edges. Consider some edge with id $ i $ . Let's determine for this edge the maximum integer weight we can give to it so that it is contained in all minimum spanning trees of the graph if we don't change the other weights.

You are to determine this maximum weight described above for each edge. You should calculate the answer for each edge independently, it means there can't be two edges with changed weights at the same time.

## 样例 #1

### 输入

```
4 4
1 2 2
2 3 2
3 4 2
4 1 3
```

### 输出

```
2 2 2 1 ```

## 样例 #2

### 输入

```
4 3
1 2 2
2 3 2
3 4 2
```

### 输出

```
-1 -1 -1 ```

# 题解

## 作者：lnzwz (赞：11)

题意：

给定一个点数为 n，边数为 m，权值不超过 $10^9$ 的带权连通图，没有自环与重边。 现在要求对于每一条边求出，这条边的边权最大为多少时，它还能出现在所有可能的最小生成树上，如果对于任意边权都出现，则输出 $-1$。

这里写一个用倍增的$O(nlogn)$做法。

先求出一个最小生成树。

1、若x到y在树上，那么对于任意一条非树边$e(a,b)$，若满足a到b的树上路径经过$e(x,y)$，

那么，根据最小生成树的性质，添加$e(a,b)$后生成的环上的最大边必须是唯一的$e(a,b)$。

因此，$e(x,y)$的权值应当等于所有满足条件的$e(a,b)$的最小权值减1。

2、若x到y不在树上，那么，根据最小生成树的性质，添加$e(x,y)$后生成的环上的最大边如果不是$e(x,y)$，它就能出现。

因此，$e(x,y)$的权值应当等于x到y路径上的最大值减1。

2可以使用倍增，$O(nlogn)$。

对于1，我们可以把非树边从小到大排序，再依次做链上覆盖，保证每条树边只被其第一次覆盖。

可以把被覆盖的连续边存成一个集合，用并查集维护。

具体来说，并查集的根节点代表此点向上第一个未被覆盖的点（包括自身）。

在这个点被覆盖后，把它与它的父节点的集合合并。

每个点只会被考虑一次，所以复杂度是对的。

总时间复杂度：$O(nlogn)$，很好写。

代码：
```cpp
#include <stdio.h> 
#include <stdlib.h> 
struct SBi {
	int x,	y,	z;
	SBi() {}
	SBi(int X, int Y, int Z) {
		x = X; y = Y; z = Z;
	}
};
SBi bi[200010],px[200010];
int cmp(const void * a, const void * b) {
	return ((SBi * ) a) ->z - ((SBi * ) b) ->z;
}
int fu[200010],fr[200010],ne[400010],v[400010],w[400010],bs = 0;
int getv(int x) {
	if (fu[x] == x) return x;
	fu[x] = getv(fu[x]);
	return fu[x];
}
void addb(int a, int b, int c) {
	v[bs] = b;
	w[bs] = c;
	ne[bs] = fr[a];
	fr[a] = bs++;
}
void kru(int n, int m) {
	for (int i = 1; i <= n; i++) {
		fu[i] = i;
		fr[i] = -1;
	}
	qsort(bi, m, sizeof(SBi), cmp);
	for (int i = 0; i < m; i++) {
		int x = getv(bi[i].x),y = getv(bi[i].y);
		if (x == y) continue;
		fu[x] = y;
		addb(bi[i].x, bi[i].y, bi[i].z);
		addb(bi[i].y, bi[i].x, bi[i].z);
	}
}
int fa[200010],sd[200010],fb[200010],fg[200010];
void dfs1(int u, int f) {
	fa[u] = f;sd[u] = sd[f] + 1;
	for (int i = fr[u]; i != -1; i = ne[i]) {
		if (v[i] != f) {
			fb[v[i]] = w[i];
			dfs1(v[i], u);
		}
	}
}
int x[200010],y[200010],z[200010],bz[18][200010],zd[18][200010];
void yucl(int n) {
	for (int i = 1; i <= n; i++) {
		bz[0][i] = fa[i];
		zd[0][i] = fb[i];
	}
	for (int i = 1; i <= 17; i++) {
		for (int x = 1; x <= n; x++) {
			bz[i][x] = bz[i - 1][bz[i - 1][x]];
			zd[i][x] = zd[i - 1][bz[i - 1][x]];
			if (zd[i - 1][x] > zd[i][x]) zd[i][x] = zd[i - 1][x];
		}
	}
}
int getlca(int a, int b) {
	if (sd[a] < sd[b]) {
		int t = a;
		a = b;b = t;
	}
	for (int i = 17; i >= 0; i--) {
		if (sd[bz[i][a]] >= sd[b]) a = bz[i][a];
	}
	if (a == b) return a;
	int rt;
	for (int i = 17; i >= 0; i--) {
		if (bz[i][a] == bz[i][b]) rt = bz[i][a];
		else {
			a = bz[i][a];
			b = bz[i][b];
		}
	}
	return rt;
}
int getmax(int a, int b) {
	int lc = getlca(a, b),ma = -1;
	for (int i = 17; i >= 0; i--) {
		if (sd[bz[i][a]] >= sd[lc]) {
			if (zd[i][a] > ma) ma = zd[i][a];
			a = bz[i][a];
		}
	}
	for (int i = 17; i >= 0; i--) {
		if (sd[bz[i][b]] >= sd[lc]) {
			if (zd[i][b] > ma) ma = zd[i][b];
			b = bz[i][b];
		}
	}
	return ma;
}
void fugai(int a, int b, int c) {
	while (sd[a = getv(a)] > sd[b]) {
		fg[a] = c;
		fu[a] = getv(fa[a]);
	}
}
int main() {
	int n,m,k = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
		bi[i] = SBi(x[i], y[i], z[i]);
	}
	kru(n, m);dfs1(1, 0);yucl(n);
	for (int i = 1; i <= n; i++) fu[i] = i;
	for (int i = 0; i < m; i++) {
		int a = x[i],b = y[i];
		if (fa[a] != b && fa[b] != a) bi[k++] = SBi(a, b, z[i]);
	}
	qsort(bi, k, sizeof(SBi), cmp);
	for (int i = 0; i < k; i++) {
		int a = bi[i].x,b = bi[i].y,c = bi[i].z;
		int lc = getlca(a, b);
		fugai(a, lc, c);fugai(b, lc, c);
	}
	for (int i = 0; i < m; i++) {
		int a = x[i],b = y[i];
		if (fa[b] == a) {
			a = y[i];
			b = x[i];
		}
		if (fa[a] != b) printf("%d ", getmax(a, b) - 1);
		else printf("%d ", fg[a] - 1);
	}
	return 0;
}
```

---

## 作者：zsq147258369 (赞：5)

~~CF 上唯一一道有 LCT tag 的题。~~

题目要求每条边的权值最大值使得其必定出现在最小生成树上。

那么可以先模拟一遍 Kruskal，可以看到有一条边，端点为 $x,y$，如果：

1. $x,y$ 已经在一个连通块内，那么只有它的边权小于 $x-y$ 路径上某一条边才能加入。

2. $x,y$ 不在一个连通块内，那么直接加入生成树即可。

对于 1，也就是非树边，很明显它的答案是 $x-y$ 路径上边权最大值 -1。可以用 LCT 维护，当然你也可以先把 MST 建出来，然后树剖或倍增。

非树边处理了，那么树边呢？

对于一条非树边，其连接了 $x,y$，边权为 $w$，那么 $x-y$ 路径上所有的边权应都小于 $w$，防止这条非树边~~上位~~替换它。

那么可以树剖，用线段树查询一个区间 min。

我用的是一种类似差分的做法。

还是这条连接了 $x,y$ 的非树边，求出它们的 $lca$，然后搞 $n$ 个优先队列，把 $w-1$ 和 $lca$ 插入 $q_x$ 和 $q_y$ 中，跑一边 dfs，合并每个点的儿子的优先队列，顺便把 $lca$ 在该点下方的踢出（记得用启发式，不然会 T 爆）。那么处理完后的队首即为答案。

最后还要注意下队列是否为空。

~~常数巨大，成功名列最劣解。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+500;

int v[N],a[N],ch[N][2],rev[N],f[N],ans[N],dep[N],head[N],cnt,top,fa[N][20],opt[N][3];

struct node
{
	int u,v,w,id,nxt;
	
	friend bool operator<(node a,node b)
	{
		return a.w<b.w;
	}
}edge[N],e[N<<1];

#define ls ch[x][0]
#define rs ch[x][1]

int isroot(int x){return ch[f[x]][0]==x|ch[f[x]][1]==x;}
void up(int x){v[x]=max(max(v[ls],v[rs]),a[x]);}
void reversal(int x){swap(ls,rs);rev[x]^=1;}
void down(int x){if(!rev[x])return;reversal(ls),reversal(rs);rev[x]=0;}
void rotate(int x)
{
	int y=f[x],z=f[y],k=(ch[y][1]==x),w=(ch[z][1]==y),an=ch[x][k^1];
	if(isroot(y))ch[z][w]=x;ch[x][k^1]=y;ch[y][k]=an;
	if(an)f[an]=y;f[y]=x,f[x]=z;
	up(y);up(x);
}

int st[N];

void splay(int x)
{
	int y=x,z=0;
	st[++z]=x;
	while(isroot(y))st[++z]=y=f[y];
	while(z)down(st[z--]);
	while(isroot(x))
	{
		y=f[x],z=f[y];
		if(isroot(y))rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
		rotate(x);
	}
	up(x);
}

void access(int x){for(int y=0;x;x=f[y=x])splay(x),rs=y,up(x);}
void make_root(int x){access(x);splay(x);reversal(x);}
int find_root(int x){access(x);splay(x);while(ls)down(x),x=ls;splay(x);return x;}
void split(int x,int y){make_root(x);access(y);splay(y);}
void link(int x,int y){make_root(x);if(find_root(y)!=x)f[x]=y;}
void cut(int x,int y){make_root(x);if(find_root(y)==x&&f[y]==x&&!ch[y][0])f[y]=rs=0,up(x);}

int n,m;

char cch,B0[1<<15],*S=B0,*T=B0;
#define getc() (S==T&&(T=(S=B0)+fread(B0,1,1<<15,stdin),S==T)?0:*S++)
int aa;int read(){
	while(cch=getc(),cch<'0'||cch>'9');aa=cch-'0';
	while(cch=getc(),cch>='0'&&cch<='9')aa=((aa<<3)+(aa<<1))+cch-'0';return aa;
}

void add(int u,int v)
{
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}

void dfs(int x,int ff)
{
	fa[x][0]=ff;dep[x]=dep[ff]+1;
	for(int i=1;i<=19;i++)
	{
		if(!fa[fa[x][i-1]][i-1])break;
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff)continue;
		dfs(v,x);
	}
}

int LCA(int x,int y)
{
	if(dep[y]>dep[x])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[x]-(1<<i)>=dep[y])x=fa[x][i];
	if(y==x)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

struct priority
{
	int v,p;
	
	friend bool operator<(priority a,priority b)
	{
		return a.v>b.v;
	}
};

priority_queue<priority>q[N];

void dfs2(int x)
{
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[x][0])continue;
		dfs2(v);
		if(q[v].size()>q[x].size())swap(q[v],q[x]);
		while(!q[v].empty())
		{
			if(dep[q[v].top().p]<=dep[x])q[x].push(q[v].top());
			q[v].pop();
		}
	}
	while(q[x].size()&&dep[q[x].top().p]>dep[x])q[x].pop();
	if(x>n&&q[x].size())ans[x-n]=q[x].top().v;
}

main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>edge[i].u>>edge[i].v>>edge[i].w,edge[i].id=i,ans[i]=-1;
	sort(edge+1,edge+1+m);
	for(int i=1;i<=m;i++)
	{
		int x=edge[i].u,y=edge[i].v;a[edge[i].id+n]=edge[i].w;
		if(find_root(x)==find_root(y))
		{
			split(x,y);
			ans[edge[i].id]=v[y]-1;
			opt[++top][0]=x;opt[top][1]=y;opt[top][2]=edge[i].w-1;
		}
		else
		{
			link(x,edge[i].id+n);
			link(y,edge[i].id+n);
			add(x,edge[i].id+n);add(edge[i].id+n,x);
			add(y,edge[i].id+n);add(edge[i].id+n,y);
		}
	}
	dfs(1,0);
	for(int i=1;i<=top;i++)
	{
		int x=opt[i][0],y=opt[i][1],lca=LCA(x,y);
		if(x!=lca)q[x].push((priority){opt[i][2],lca});
		if(y!=lca)q[y].push((priority){opt[i][2],lca});
	}
	dfs2(1);
	for(int i=1;i<=m;i++)cout<<ans[i]<<' ';
}
```

~~写的可能有些臭？~~

---

## 作者：lzyqwq (赞：4)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17775070.html)**

**[洛谷](https://www.luogu.com.cn/problem/CF827D) [CF](https://codeforces.com/problemset/problem/827/D)**

> - 给出一张 $n$ 个点 $m$ 条边的无向带权图，对于每一条边，求出它的边权最大修改为多少时，它仍然在图的所有最小生成树上。
>
>- 每条边的询问相互独立，即修改一条边时，其它边的权值不是修改后的权值而是这条边输入的权值。
>
> - $n,m\le 2\times 10^5$。

约定：记 $(u,v,w)$ 为 $u,v$ 两点之间边权为 $w$ 的连边。

考虑先求出原图的一棵最小生成树，并对其重链剖分。分两种情况考虑。

- 对于最小生成树上的边，若增大它的权值，它会被某些非树边代替，所以它的最大权值必须**小于**能代替它的最小的非树边的权值。因此维护一个 $mn$ 数组，$mn_i$ 表示能覆盖第 $i$ 条边的最小非树边边权。考虑对于每一条非树边 $(u,v,w)$，所有最小生成树上 $u,v$ 路径上的边的 $mn$ 值，都要对 $w$ 取 $\min$，使用线段树维护。第 $i$ 条边的答案即为 $mn_i-1$。若找不到边替换它则无解。

- 对于不是最小生成树上的边 $(u,v,w)$，若将其加入，则形成了一个包含 $u,v$ 两点最小生成树上路径的环，那么需要在 $u,v$ 两点最小生成树上的路径删去一条边，那么肯定是删去最大的那条边（设其权值为 $mx$），则这条非树边的答案为 $mx-1$。

对每条重链单独建线段树，对于一次路径操作，只有 $\mathcal{O}(1)$ 条链是不完整的，需要拆成 $\mathcal{O}(\log n)$ 个区间；剩下 $\mathcal{O}(\log n)$ 条链都是完整的，操作的时候只会访问到根节点，时间复杂度为 $\mathcal{O}(1)$。

综上，时间复杂度为 $\mathcal{O}(m\log n)$，空间复杂度为 $\mathcal{O}(n+m)$，常数略大。

**[评测记录（含代码）](https://codeforces.com/contest/827/submission/228760412)**

---

## 作者：sunzh (赞：4)

~~谨以此题解纪念写过的最长的codeforces的代码~~

### 题目翻译：

给定一个点数为$n$，边数为$m$，权值不超过$10^9$的带权连通图，没有自环与重边。 现在要求对于每一条边求出，这条边的边权最大为多少时，它还能出现在所有可能的最小生成树上，如果对于任意边权都出现，则输出 $-1$。 
$2 \le n \le 2 \times 10^5,,n - 1 \le m \le 2 \times 10^5 $

### 题解


------------
我们先用kurskal/prim求出原图的MST

我们把MST上的边和不在MST上的边分开考虑

1. 对于不在MST上的边，要成为MST上的边，边权必须比它的两个端点在树上的路径上最长的那条边小，这样才能代替那条边成为MST上的边。

我们如果把边权下放成点权，这里就成了一个树上路径取max操作

2. 对于MST上的边，他如果被代替，那么它dep大的端点的子树内一定有一条边权比它小的边连向它的子树外。  那么对于一条非树边$(u,v)$ 每一个$u->lca,v->lca$两段路径上的点$p$,边$(p,fa[p])$就有可能被用这条边代替。同样的我们可以树上路径取min，最后单点查询

要实现这两个操作，比较容易想到树剖，复杂度$O(nlog_2^2n)$~~（在CF神机上跑2e5毫无压力）~~

但LCT同样可以实现这些操作，复杂度$O(nlog_2n)$~~但是常数巨大~~


我在实现的时候用了树剖+kruskal的做法，如果追求更优复杂度的话请自行用LCT代替树剖

~~代码又臭又长，如有不适请见谅~~
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#define PII pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') { if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9') { x=(x<<3)+(x<<1)+(c^48); c=getchar();}
	return f==1?x:-x;
}
inline void print(int x){
	if(x<0) x=~x+1,putchar('-');
	if(x>=10) print(x/10);
	putchar((x%10)|48);
}
int n,m;
int ans[200010];
PII edg[200010];
int len[200010];
bool tre[200010];
namespace tree{
	vector<PII>vec[200010];
	int maxn[800010],ano[800010],tag[800010];
	int siz[200010],son[200010],fa[200010],dfn[200010],top[200010],val[200010],dep[200010];
	int id;
	void add(int u,int v,int w){
		vec[u].pb(mp(v,w));vec[v].pb(mp(u,w));
	}
	void pushup(int p){
		maxn[p]=max(maxn[p<<1],maxn[p<<1|1]);
		ano[p]=min(ano[p<<1],ano[p<<1|1]);
	}
	void pushdown(int p){
		if(tag[p]!=-1){
			if(tag[p]<ano[p<<1]){
				ano[p<<1]=tag[p];
			}
			if(tag[p]<ano[p<<1|1]){
				ano[p<<1|1]=tag[p];
			}
			tag[p<<1]=(tag[p<<1]==-1?tag[p]:min(tag[p<<1],tag[p]));
			tag[p<<1|1]=(tag[p<<1|1]==-1?tag[p]:min(tag[p<<1|1],tag[p]));
			tag[p]=-1;
		}
	}
	void update(int p,int l,int r,int L,int R,int k){
		if(l>=L&&r<=R){
			if(k<ano[p]){
				ano[p]=k;
			}tag[p]=(tag[p]==-1?k:min(tag[p],k));
			return ;
		}
		pushdown(p);
		int mid=l+r>>1;
		if(L<=mid) update(p<<1,l,mid,L,R,k);
		if(R>mid) update(p<<1|1,mid+1,r,L,R,k);
		pushup(p);
	}
	int qano(int p,int l,int r,int L,int R){
		if(l>=L&&r<=R){
			return ano[p];
		}
		pushdown(p);
		pushup(p);
		int mid=l+r>>1;
		int res=0x3f3f3f3f;
		if(L<=mid) res=min(res,qano(p<<1,l,mid,L,R));
		if(R>mid) res=min(res,qano(p<<1|1,mid+1,r,L,R));
		return res;
	}
	void build(int p,int l,int r){
		tag[p]=-1;
		if(l==r){
			maxn[p]=val[l];ano[p]=0x3f3f3f3f;return ;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(l>=L&&r<=R) return maxn[p];
		int mid=l+r>>1;
		int res=0;
		if(L<=mid) res=max(res,query(p<<1,l,mid,L,R));
		if(R>mid) res=max(res,query(p<<1|1,mid+1,r,L,R));
		return res;
	}
	int Query(int u,int v){
		int res=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			res=max(res,query(1,1,id,dfn[top[u]],dfn[u]));
			u=fa[top[u]];
		}
		if(u==v) return res;
		if(dep[u]>dep[v]) swap(u,v);
		res=max(res,query(1,1,id,dfn[u]+1,dfn[v]));
		return res;
	}
	void dfs1(int x,int f){ 
		fa[x]=f,dep[x]=dep[f]+1,siz[x]=1;
		for(auto i:vec[x]){
			int v=i.fi;
			if(v==f) continue ;
			dfs1(v,x);
			siz[x]+=siz[v];
			if(siz[v]>siz[son[x]]) son[x]=v;
		}
	}
	void dfs2(int x,int topf,int va){
		dfn[x]=++id;val[id]=va;top[x]=topf;
		if(!son[x]) return ;
		for(auto i:vec[x]){
			int v=i.fi;
			if(v==son[x]){
				dfs2(v,topf,i.se);
			}
		}
		for(auto i:vec[x]){
			int v=i.fi;
			if(v==fa[x]||v==son[x]) continue ;
			dfs2(v,v,i.se);
		}
	}
	void UPD(int x,int y,int k){
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			update(1,1,id,dfn[top[x]],dfn[x],k);
			x=fa[top[x]];
		}
		if(x==y) return ;
		if(dep[x]>dep[y]) swap(x,y);
		update(1,1,id,dfn[x]+1,dfn[y],k);
	}
	int another(int x,int y){
		if(dep[x]<dep[y]) swap(x,y);
		return qano(1,1,id,dfn[x],dfn[x]);
	}
	void solve(){
		memset(ano,0x3f,sizeof(ano));
		dfs1(1,0);
		dfs2(1,1,0);
		build(1,1,id);
	}
}
namespace MST{
	int cnt;
	int fa[200010];
	struct edge{
		int u,v,w,id;
	}e[200010];
	void add(int u,int v,int w,int id){
		e[++cnt]=edge{u,v,w,id};
	}
	bool cmp(edge x,edge y){
		return x.w<y.w;
	}
	int find(int x){
		if(fa[x]==x) return x;
		return fa[x]=find(fa[x]);
	}
	void kruskal(){
		int t=1;
		for(int i=1;i<=m;++i){
			int fx=find(e[i].u);
			int fy=find(e[i].v);
			if(fx==fy){
				continue ;
			}
			++t;tree::add(e[i].u,e[i].v,e[i].w);tre[e[i].id]=1;
			fa[fx]=fy;if(t==n) break ;
		}
	}
	void solve(){
		for(int i=1;i<=n;++i) fa[i]=i;
		sort(e+1,e+m+1,cmp);
		kruskal();
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		edg[i].fi=u,edg[i].se=v,len[i]=w;
		MST::add(u,v,w,i);
	}
	MST::solve();
	tree::solve();
	for(int i=1;i<=m;++i){
		if(!tre[i]){
			tree::UPD(edg[i].fi,edg[i].se,len[i]);
		}
	}
	for(int i=1;i<=m;++i){
		if(ans[i]==-1) continue ;
		if(tre[i]){
			ans[i]=tree::another(edg[i].fi,edg[i].se)-1;
			if(ans[i]>0x3f3f3f15) ans[i]=-1;continue ;
		}
		int maxn=tree::Query(edg[i].fi,edg[i].se);
		ans[i]=maxn-1;
	}
	for(int i=1;i<=m;++i) print(ans[i]),putchar(' ');
	return 0;
}
```


---

## 作者：Hoks (赞：3)

## 前言
重剖题单里的，刚好我的[总结文章](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)里把这题当做了练习题，就写篇题解吧。

## 题意分析
有关题意的话，洛谷上的翻译已经写的很详细易懂了。

接着考虑怎么处理。

首先我们优先考虑造出来一颗 MST，那么一条边就有两种可能性：

1. 在 MST 上。

2. 不在 MST 上。

考虑分开考虑这两种情况，对于第一种而言：

- 若增大它的权值，它会被某些非树边代替，所以它的最大权值必须**小于能代替它的最小的非树边的权值**。

- 所以我们可以考虑对着每条非树边，考虑用他来更新树边的能被替换的最小权值。

- 这一步直接用线段树维护即可。

接着是第二种情况：

- 如果把这条边放进树中，必然会形成一个环，这个时候树就变成了基环树。

- 因为生成的是 MST，所以我们要去掉环上边权最大的一条边。

- 但我们又要保证去掉的这条边不能是非树边。

- 所以我们只需要查询这条边的两端点路径上的最大边权即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=200010,INF=0x3f3f3f3f3f3f3f3f;
struct edge{int v,nxt,w;}e[N<<1];
struct node{int x,y,w,id;}g[N];
int n,m,tot,cnt,yl;
int dfn[N],top[N],head[N],id[N],f[N],ans[N],lz[N<<2];
int fa[N],dep[N],si[N],son[N],a[N],t[N<<2],tt[N<<2];
bool mp[N];
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),a(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') a=-1;fc=getchar();}
    while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
    return x*a;
}
inline void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline void add(int u,int v,int w){e[++tot].v=v,e[tot].nxt=head[u],head[u]=tot,e[tot].w=w;}
inline bool cmp(node x,node y){return x.w<y.w;}
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void dfs1(int u,int ff)
{
	dep[u]=dep[ff]+1,fa[u]=ff,si[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff) continue;
		dfs1(v,u);si[u]+=si[v];a[v]=e[i].w;
		if(si[v]>si[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	top[u]=topf,dfn[u]=++cnt,id[cnt]=a[u];
	if(son[u]) dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline void pushup(int p){t[p]=max(t[ls],t[rs]);}
inline void pushdown(int p)
{
	if(lz[p]!=INF)
	{
		lz[ls]=min(lz[ls],lz[p]),lz[rs]=min(lz[rs],lz[p]);
		tt[ls]=min(tt[ls],lz[p]),tt[rs]=min(tt[rs],lz[p]);
		lz[p]=INF;
	}
}
inline void build(int p,int l,int r)
{ 
	if(l==r) return void(t[p]=id[l]);
	build(ls,l,mid),build(rs,mid+1,r),pushup(p);
}
inline int query(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return t[p];
	int res=0;if(mid>=s) res=query(ls,l,mid,s,e);
	if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
	return res;
}
inline void modify(int p,int l,int r,int s,int e,int k)
{
	if(l>=s&&r<=e) return void(lz[p]=min(lz[p],k)),void(tt[p]=min(tt[p],k));
	pushdown(p);
	if(mid>=s) modify(ls,l,mid,s,e,k);
	if(mid<e) modify(rs,mid+1,r,s,e,k);
	tt[p]=min(tt[ls],tt[rs]);
}
inline int qry(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return tt[p];pushdown(p);
	int res=0;if(mid>=s) res=qry(ls,l,mid,s,e);
	if(mid<e) res=max(res,qry(rs,mid+1,r,s,e));
	return res;
}
inline void modify(int i)
{
	int x=g[i].x,y=g[i].y,w=g[i].w;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(1,1,cnt,dfn[top[x]],dfn[x],w);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	modify(1,1,n,dfn[x]+1,dfn[y],w);
}
inline int query(int i)
{
	int x=g[i].x,y=g[i].y,res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(query(1,1,cnt,dfn[top[x]],dfn[x]),res);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return max(res,query(1,1,n,dfn[x]+1,dfn[y]));
}
signed main()
{
	n=read(),m=read();memset(tt,0x3f,sizeof tt);memset(lz,0x3f,sizeof lz);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1,u,v,w;i<=m;i++) u=g[i].x=read(),v=g[i].y=read(),w=g[i].w=read(),g[i].id=i;
	sort(g+1,g+1+m,cmp);
	for(int i=1,u,v,w;i<=m;i++)
	{
		u=g[i].x,v=g[i].y,w=g[i].w; 
		if(find(u)==find(v)) continue;
		yl++;add(u,v,w),add(v,u,w);f[find(u)]=find(v);
		mp[i]=1;if(yl==n-1) break;
	}
	dfs1(1,0),dfs2(1,1),build(1,1,cnt);
	for(int i=1;i<=m;i++) if(!mp[i]) ans[g[i].id]=query(i)-1,modify(i);
	for(int i=1,x;i<=m;i++) if(mp[i]) x=max(dfn[g[i].x],dfn[g[i].y]),ans[g[i].id]=qry(1,1,cnt,x,x)-1;
	for(int i=1;i<=m;i++) 
		if(ans[i]==INF-1) print(-1),putchar(' ');
		else print(ans[i]),putchar(' ');
	return 0;
}
/*
10 21
5 6 88
6 3 74
1 5 7
1 6 27
8 1 50
4 1 24
10 6 37
9 7 39
5 7 63
2 7 98
3 4 28
9 2 5
2 4 96
9 6 67
9 10 47
10 4 64
2 5 70
6 8 89
3 5 54
6 7 18
1 7 26
*/
/*
25 27 53 25 88 53 46 46 25 38 53 69 38 38 38 36 38 49 27 26 26
*/
```


---

## 作者：木xx木大 (赞：2)

[CF827D Best Edge Weight](https://www.luogu.com.cn/problem/CF827D) 

orz给我讲这题的 zyt 学长。本篇题解很大程度上参考了[他的博客](https://www.cnblogs.com/zyt1253679098/p/9852648.html)

* 首先随便求出一棵最小生成树，把树边和非树边分开处理。

* 对于非树边 $(u,v)$ ，它必定成为树边的充要条件是它的权值小于树上 $u$ 到 $v$ 之间的路径上的某条边 $e$ 。因此，非树边的答案就是它两端点之间树上路径上最大边的权值减 1（如果相等则两条边都可以选，不符合“必定成为树边”）。

* 对于树边 $(u,v)$ ，如果有一条非树边 $(a,b)$ ，树上 $a$ 和 $b$ 的路径要经过 $(u,v)$ ，那么只有当任意这样的 $(a,b)$ 的权值都大于 $(u,v)$ 时，$(u,v)$ 才必定不会被别的边替换下来，也就是必定成为树边。因此，树边的答案就是所有上述 $(a,b)$ 中权值最小的边的权值减1。

* 那么，对于非树边 $(u,v,w)$ ，我们要查询 $(u,v)$ 间路径上的最大边权，并且需要用 $w$ 来更新这段路径上所有树边的答案（即把这些边的答案与 $w$ 取最小值）。

* 可以用树剖+线段树维护，但这里主要介绍**倍增写法**。代码短，还少个 log 。

* 区间查最大就按普通的倍增写法更新、查询即可。区间取最小是这个算法最精妙之处。考虑用 $mi[a][i]$ 表示所有一端是 $a$ 及其子树，另一端是 $fa[a][i]$ 及其祖先的非树边的最小权值。$mi[a ][0]$ 就是 $a$ 和 $a$ 的父亲之间的边的答案。 

* 因为 $mi[a][i]$ 只会变小不会变大，且全部非树边考虑完后才会查询。我们可以全部修改尽可能大的区间，最后再一起从大区间向小区间倒推。用 $mi[a][i]$ 更新 $mi[a][i−1]$ 和 $mi [fa[a][i−1]][i−1]$ （覆盖了大区间的非树边一定会覆盖该区间的子区间）。这个操作类似于线段树的pushdown。

我的代码有点长大概是因为写的太松散了QAQ

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
struct EDG{
	int fro,to,id;
	ll w;
	bool ist; 
}ed[N];
struct edg{
	int to,nxt,id;
	ll w;
}e[N<<1];
bool cmp(EDG a,EDG b)
{
	return a.w<b.w;
}
int fath[N],fa[N][25],mi[N][25],mx[N][25],dep[N],pre[N],ans[N];
int cnt,head[N],n,m;
int find(int x)
{
	return x==fath[x]? x:fath[x]=find(fath[x]);
}
void add(int u,int v,int w,int id)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].w=w;
	e[cnt].id=id;
}
void dfs(int u)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa[u][0])continue;
		dep[v]=dep[u]+1;
		pre[v]=e[i].id;
		mx[v][0]=e[i].w;
		fa[v][0]=u;
		dfs(v);
	}
}
int querymx(int u,int v)
{
	int s=0;
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=20;i>=0;i--)
	{
		if(d&(1<<i))
		{
			s=max(s,mx[u][i]);
			u=fa[u][i];
		}
	}
	if(u==v)return s;
	for(int i=20;i>=0;i--)
	{
		if(fa[u][i]!=fa[v][i])
		{
			s=max(s,max(mx[u][i],mx[v][i]));
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	s=max(s,max(mx[u][0],mx[v][0]));
	return s;
}
void changemi(int u,int v,int w)
{
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=20;i>=0;i--)
	{
		if(d&(1<<i))
		{
			mi[u][i]=min(mi[u][i],w);
			u=fa[u][i];
		}
	}
	if(u==v)return;
	for(int i=20;i>=0;i--)
	{
		if(fa[u][i]!=fa[v][i])
		{
			mi[u][i]=min(mi[u][i],w);
			mi[v][i]=min(mi[v][i],w);
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	mi[u][0]=min(mi[u][0],w),mi[v][0]=min(mi[v][0],w);
}
int main() 
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&ed[i].fro,&ed[i].to,&ed[i].w);
		ed[i].id=i;
	}
	for(int i=1;i<=n;i++)
		fath[i]=i;
	sort(ed+1,ed+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		int fu=find(ed[i].fro);
		int fv=find(ed[i].to);
		if(fu!=fv)
		{
			fath[fu]=fv;
			add(ed[i].fro,ed[i].to,ed[i].w,ed[i].id);
			add(ed[i].to,ed[i].fro,ed[i].w,ed[i].id);
			ed[i].ist=1;
		}
	}
	dfs(1);
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
			mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
		}
	memset(mi,0x3f,sizeof(mi)); 
	for(int i=1;i<=m;i++)
		if(!ed[i].ist)
		{
			ans[ed[i].id]=querymx(ed[i].fro,ed[i].to)-1;
			changemi(ed[i].fro,ed[i].to,ed[i].w);
		}
	for(int j=20;j;j--)
		for(int i=1;i<=n;i++)
		{
			mi[i][j-1]=min(mi[i][j-1],mi[i][j]);
			mi[fa[i][j-1]][j-1]=min(mi[fa[i][j-1]][j-1],mi[i][j]);
		}
	for(int i=2;i<=n;i++)
		ans[pre[i]]=mi[i][0]-1;
	for(int i=1;i<=m;i++)
		if(ans[i]<0x3f3f3f3f-1)
			printf("%d ",ans[i]);
			else printf("-1 ");
	return 0;
}
```

---

## 作者：ruik (赞：1)

### 题意
给你一个没有自环与重边的带权连通图，要你求每一条边权值最高为多少才一定能在最小生成树。
### 思路
**step1** 对连通图求最小生成树，并分别记录下在与没在最小生成树上的边。

**step2** 对在最小生成树上的边进行 dfs 建树操作。

**step3** 做好所有准备工作后便可以开始记录答案了。我们对于在最小生成树上的边与不在树上的边我们需要分别记录。对于不在最小生成树上的边，它的答案为它们两边的节点于树上的路径中最权值大的边减一。而在树上的边，从小到大枚举不在树上的边，使它们依次修改它们之间路径上的边的答案，答案为所枚举到的边的权值减一。
### code

```cpp
#include<bits/stdc++.h> 
 
using namespace std; 
//#define DEBUG 1 
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}
 
  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }
 
  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }
 
  template <class T>
  T read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp * (ch - '0');
    if (sign) x = -x;
         return x;
  }
 
  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc());
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }
 
  void read(char &c) { for (c = gc(); blank(c); c = gc()); }
 
  void push(const char &c) {
#if DEBUG 
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }
 
  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-'); 
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }
 
  template <class T>
  void write(T x, char lastChar) {
    write(x), push(lastChar);
  }
} io;
 
const int N=2e5+10,M=2e5+10; 
 
int n,m,x,y,z; 
int fat[N],fa[N],f[N][20],dep[N],mx[N][20],lg[N],ccc; 
int fa_len[N],sfa[N],zx[N]; 
int ans[N],tot,cnt; 
bool mark[N]; 
 
struct edge{int x,y,z,id;}a[N],b[N],c[N],ya[N]; 
 
bool _cmp1(edge a,edge b){return a.z <b.z;} 
 
int getfa(int x){return x==fat[x]?x:fat[x]=getfa(fat[x]);} 
void mix(int x,int y){fat[x]=y;} 
 
vector<int>now_g[M]; 
vector<int>g[M]; 
vector<int>_long[M]; 
 
void build(int x){ 
	mark[x]=true; 
	mx[x][0]=lg[fa_len[x]]; 
	f[x][0]=sfa[x]; 
	for(int i=1;i<=19;i++)f[x][i]=f[f[x][i-1]][i-1],mx[x][i]=max(mx[f[x][i-1]][i-1],mx[x][i-1]); 
	for(int i=0;i<now_g[x].size();i++){ 
		if(mark[now_g[x][i]])continue; 
		g[x].push_back(now_g[x][i]); 
		sfa[now_g[x][i]]=x; 
		dep[now_g[x][i]]=dep[x]+1; 
		fa_len[now_g[x][i]]=_long[x][i]; 
		build(now_g[x][i]); 
	} 
} 
 
int LCA_or_ST(int x,int y,bool wa){ 
	int ans=0; 
	if(dep[x]<dep[y])swap(x,y); 
	for(int i=19;i>=0;i--) 
		if(dep[f[x][i]]>=dep[y])ans=max(ans,mx[x][i]),x=f[x][i]; 
	if(x==y)return wa?ans:x; 
	for(int i=19;i>=0;i--) 
		if(f[x][i]!=f[y][i]){ 
			ans=max(ans,max(mx[x][i],mx[y][i])); 
			x=f[x][i]; 
			y=f[y][i]; 
		} 
	return wa?max(ans,max(mx[x][0],mx[y][0])):f[x][0]; 
} 
int getans(int x,int lca,int d){
	if(dep[x]<=dep[lca])return x;
	if(ans[fa_len[x]]==-1)ans[fa_len[x]]=d;
	return sfa[x]=getans(sfa[x],lca,d);
}
int main(){ 
	memset(ans,-1,sizeof(ans));
	dep[1]=1; 
	io.read(n),io.read(m);
	for(int i=1;i<=n;i++)fat[i]=sfa[i]=i; 
	for(int i=1;i<=m;i++){ 
		io.read(x),io.read(y),io.read(z);
		ya[i]=a[i]=(edge){x,y,z,i}; 
	} 
	sort(a+1,a+m+1,_cmp1); 
	for(int i=1;i<=m;i++){ 
    	lg[a[i].id]=a[i].z;
		x=getfa(a[i].x),y=getfa(a[i].y); 
		if(x!=y){ 
			c[++tot]=a[i]; 
			mix(x,y); 
			now_g[a[i].x].push_back(a[i].y); 
			now_g[a[i].y].push_back(a[i].x); 
			_long[a[i].x].push_back(a[i].id); 
			_long[a[i].y].push_back(a[i].id); 
		} 
		else b[++cnt]=a[i]; 
	}
	build(1);
	for(int i=1;i<=cnt;i++){
		x=b[i].x ,y=b[i].y ,z=b[i].z ; 
		int s=LCA_or_ST(x,y,0); 
		getans(x,s,z-1);
		getans(y,s,z-1);
		ans[b[i].id ]=LCA_or_ST(b[i].x ,b[i].y ,1)-1; 
	}
	for(int i=1;i<=m;i++){
		io.write(ans[i],' ');
	}
	return 0; 
}
```

---

## 作者：_RainCappuccino_ (赞：1)

> $\texttt{TAG}$：最小生成树，树上倍增。


分类讨论，现在求出的任意一个最小生成树为 $G\{V,E\}$。

对于 $e \in E$，即树边，有两种情况：

- 无论何值都必定在最小生成树上，不难发现，一定是割边，或者用非另一种情况去判断。
- 否则，最大值为 $(\min\limits _{e'(u,v) \notin E,e \in u \leftrightsquigarrow v}w_{e'}) - 1$，原因：在这棵 MST 的基础上，删去一条边，再加上一条边，一定只能替换新加边 $(u, v)$ 的两个顶点在原树上 $u \leftrightsquigarrow v$ 的唯一路径上的边，不然不能满足树的联通性。

对于 $e(u,v) \notin E$，即非树边，答案只能为 $(\max\limits _{e' \in E,e' \in u \leftrightsquigarrow v}w_{e'}) - 1$。原因同树边的第二种情况。

对于树边的情况 2，转化一下，设对于树边 $(x, y)$ 最后的答案是 $f_i$，就是对于所有非树边 $(u, v)$，对 $u\leftrightsquigarrow v$ 上的边，$f_i \gets \min(f_i, w_{(u,v)})$，直接暴力树剖是 $n \log^2 n$ 的，我们剋癌的 NKOJ 肯定跑不过去。发现这个操作是先修改完毕再查询，可以考虑倍增处理再下放，如果没有被任意一个非树边覆盖过，那么就是情况 1。

对于树边，就是简单的树上倍增求 $\max$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
const int N = 2e5 + 10;
const int M = 2e5 + 10;
const int inf = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> pi;
int n, m;
struct edge {
	int u, v, w, id;
	bool operator < (edge x) const {
		return w < x.w;
	}
} e[M];
vector<edge> g[N], g2[N];
struct dsu {
	int f[N];
	void init () {
		for (int i = 1; i <= n; i ++) f[i] = i;
	}
	int find (int x) {
		return f[x] = (f[x] == x ? x : find(f[x]));
	}
} d;
int son[N], dep[N], fath[N], dfn[N], top[N], siz[N], tmp, to[N], val[N];
int bel[M];
int fa[N][40], k;
void dfs1 (int u, int _fa) {
	siz[u] = 1, fath[u] = _fa, dep[u] = dep[_fa] + 1;
	fa[u][0] = _fa;
	for (int i = 1; ; i ++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		if (!fa[u][i]) {
			k = max(k, i - 1);
			break;
		}
	}
	for (auto e : g[u]) {
		int v = e.v;
		if (v == _fa) continue;
		val[v] = e.w, bel[e.id] = v;
		dfs1 (v, u);
		if (siz[v] > siz[son[u]]) son[u] = v;
		siz[u] += siz[v];
	}
}
int mi[N][40];
void modify (int u, int v, int val) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = k; i >= 0; i --) {
		if (dep[fa[u][i]] >= dep[v]) {
			mi[u][i] = val;
			u = fa[u][i];
		}
	}
	if (u == v) return;
	for (int i = k; i >= 0; i --) {
		if (fa[u][i] != fa[v][i]) {
			mi[u][i] = mi[v][i] = val;
			u = fa[u][i], v = fa[v][i];
		}
	}
	mi[u][0] = mi[v][0] = val;
}
void pushdown () {
	for (int i = k; i >= 1; i --) {
		for (int j = 1; j <= n; j ++) {
			if (!mi[j][i]) continue;
			mi[j][i - 1] = min(mi[j][i - 1], mi[j][i]);
			mi[fa[j][i - 1]][i - 1] = min(mi[fa[j][i - 1]][i - 1], mi[j][i]);
		}
	}
}
void dfs2 (int u, int tp) {
	top[u] = tp, dfn[u] = ++ tmp, to[tmp] = u;
	if (son[u]) dfs2(son[u], tp);
	for (auto e : g[u]) {
		if (e.v == fath[u] || e.v == son[u]) continue;
		dfs2 (e.v, e.v);
	}
}
int log_2[N];
struct tree {
	int ma[N][40];
	void build() {
		for (int i = 1; i <= n; i ++) ma[i][0] = val[to[i]];
		for (int k = 1; (1 << k) <= n; k ++) {
			for (int i = 1; i + (1 << k) - 1 <= n; i ++) {
				ma[i][k] = max(ma[i][k - 1], ma[i + (1 << k - 1)][k - 1]);
			}
		}
	}
	int getmax (int ql, int qr) {
		int len = log_2[qr - ql + 1];
		return max (ma[ql][len], ma[qr - (1 << len) + 1][len]);
	}
} t;
int getmax (int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = max(t.getmax(dfn[top[u]], dfn[u]), res);
		u = fath[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	if (u == v) return res;
	res = max(res, t.getmax(dfn[v] + 1, dfn[u]));
	return res;
}
int befu[M], befv[M];
bool mark[M], mk[M];
#ifdef ONLINE_JUDGE
char buf[1 << 23] , * p1 = buf , * p2 = buf , obuf[1 << 23] , * O = obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
	int x = 0 , f = 1;char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1;ch = getchar(); }
	while (isdigit(ch)) x = x * 10 + (ch ^ 48) , ch = getchar();
	return x * f;
}
signed main() {
//	freopen("in.txt", "r", stdin);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	n = read(), m = read();
	for (int i = 1; i <= n; i ++) d.f[i] = i, log_2[i] = log2(i);
	for (int i = 1; i <= m; i ++) e[i].u = read(), e[i].v = read(), e[i].w = read(), e[i].id = i, befu[i] = e[i].u, befv[i] = e[i].v;
	sort (e + 1, e + 1 + m);
	for (int i = 1; i <= m; i ++) {
		int u = e[i].u, v = e[i].v;
		if (d.find(u) != d.find(v)) {
			d.f[d.find(u)] = d.find(v);
			mk[e[i].id] = 1;
			g[u].push_back({u, v, e[i].w, e[i].id});
			g[v].push_back({v, u, e[i].w, e[i].id});
		}
		g2[u].push_back({u, v, e[i].w, e[i].id});
		g2[v].push_back({v, u, e[i].w, e[i].id});
	}
	dfs1 (1, 0);
	dfs2 (1, 1);
	for (int i = 1; i <= n; i ++)
		for (int j = 0; j <= k; j ++) mi[i][j] = inf;
	t.build();
	for (int i = m; i >= 1; i --) {
		if (!mk[e[i].id]) modify(e[i].u, e[i].v, e[i].w);
	}
	pushdown();
	for (int id = 1; id <= m; id ++) {
		if (mk[id]) {
			int u = bel[id];
			int v = mi[u][0];
			if (v == inf) cout << -1 << ' ';
			else cout << v - 1 << ' ';
		} else {
			cout << getmax(befu[id], befv[id]) - 1 << ' ';
		}
	}
	return 0;
}
```

---

## 作者：bsdsdb (赞：1)

LCT 维护树链信息入门好题。当然也可以用树剖做，但是复杂度多一个 $\log$.

题意：给定一个简单带边权无向图，问每条边边权至多为多少（可能是无穷大）才能出现在每个最小生成树中。

先随便搞一个 MST 进行分析。

为方便表述，记 $x\leftrightarrow y$ 为这棵 MST 上 $x$ 到 $y$ 的路径。

对于连接 $x$ 和 $y$ 的非树边，如果他想要替换掉一个 $x\leftrightarrow y$  上的树边，就需要他的权值变得小于这条树边。因为题目问的是“最大变成多少”，所以我们肯定选 $x\leftrightarrow y$ 上边权最大的，边权 $-1$ 就是答案。

对于连接 $x$ 和 $y$ 的树边，对他的限制是他的边权小于所有「断开 $x$ 和 $y$ 后，连接『森林的两个连通分量』的所有非树边」的边权，也即小于这些边权的最小值。

寻找这些限制了他的边是不好做的。我们换个角度考虑问题，对每个非树边 $(u,v)$ 处理他限制了哪些树边。显然是 $u\leftrightarrow v$ 上的所有边。所以我们要对 $u\leftrightarrow v$ 上的所有边打个 tag. 

也就是说，把每条边都搞成一个单独的点（注：这是常用的处理手法，建议小本本记下来）后，我们现在要维护一个数据结构：

- 查询一条链上所有点的点权（注意：与 tag 不同）的最大值；
- 给一条链上所有点打 tag；
- 查询一个点被打的所有 tag 的最小值。

树剖 $\mathcal O(m\log^2 n)$，LCT $\mathcal O(m\log n)$. 

LCT 代码：

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(chrono::high_resolution_clock().now().time_since_epoch().count());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 4e5 + 5, EDGE = 2e5, NODE = 0;

struct LCTNode {
	ll l = 0, r = 0, p = 0, rev = 0, val = ~inf, telim = inf, ntemx = ~inf, tel_tag = inf;
};
struct LCT {
	LCTNode node[MAXN];
	void lock() {
		node[0] = LCTNode();
	}
	void pushup(ll x) {
		lock();
		node[x].ntemx = max({node[x].val, node[node[x].l].ntemx, node[node[x].r].ntemx});
		lock();
	}
	void pushdown(ll x) {
		if (node[x].rev) {
			swap(node[x].l, node[x].r);
		}
		node[node[x].l].rev ^= node[x].rev;
		node[node[x].r].rev ^= node[x].rev;
		node[x].rev = 0;
		node[x].telim = min(node[x].tel_tag, node[x].telim);
		node[node[x].l].tel_tag = min(node[x].tel_tag, node[node[x].l].tel_tag);
		node[node[x].r].tel_tag = min(node[x].tel_tag, node[node[x].r].tel_tag);
		node[x].tel_tag = inf;
		lock();
	}
	bool isroot(ll x) {
		lock();
		return x && node[node[x].p].l != x && node[node[x].p].r != x;
	}
	bool isl(ll x) {
		return x && !isroot(x) && node[node[x].p].l == x;
	}
	void upd(ll x) {
		if (!isroot(x)) {
			upd(node[x].p);
		}
		pushdown(x);
	}
	void rotate(ll x) {
		if (!x || isroot(x)) {
			return;
		}
		ll p = node[x].p, g = node[p].p;
		if (!isroot(p)) {
			if (isl(p)) {
				node[g].l = x;
			} else {
				node[g].r = x;
			}
		}
		if (isl(x)) {
			node[p].l = node[x].r;
			node[node[x].r].p = p;
			node[x].r = p;
			node[p].p = x;
		} else {
			node[p].r = node[x].l;
			node[node[x].l].p = p;
			node[x].l = p;
			node[p].p = x;
		}
		lock();
		node[x].p = g;
		pushup(p), pushup(x), pushup(g);
	}
	void splay(ll x) {
		if (!x) {
			return;
		}
		upd(x);
		while (!isroot(x) && !isroot(node[x].p)) {
			ll p = node[x].p;
			if (isl(x) == isl(p)) {
				rotate(p);
			} else {
				rotate(x);
			}
			rotate(x);
		}
		if (!isroot(x)) {
			rotate(x);
		}
	}
	void access(ll x) {
		if (!x) {
			return;
		}
		for (ll s = 0; x; s = x, x = node[x].p) {
			splay(s), splay(x);
			node[x].r = s, node[s].p = x;
			lock();
			pushup(x);
		}
	}
	void makeroot(ll x) {
		if (!x) {
			return;
		}
		access(x);
		splay(x);
		node[x].rev ^= 1;
		pushdown(x);
	}
	void split(ll x, ll y) {
		makeroot(x), access(y), splay(y);
	}
	ll find(ll x) {
		access(x), splay(x);
		while (node[x].l) {
			x = node[x].l;
		}
		return x;
	}
	void link(ll x, ll y) {
		makeroot(x), splay(x);
		node[x].p = y;
		pushup(x), pushup(y);
	}
	bool addedge(ll x, ll y, ll eid, ll v) {
		if (find(x) == find(y)) {
			return 0;
		}
		node[eid].val = node[eid].ntemx = v;
		link(x, eid), link(eid, y);
		return 1;
	}
	void addlim(ll x, ll y, ll v) {
		split(x, y);
		pushdown(y);
		node[y].tel_tag = v;
		pushdown(y);
	}
	ll qry_te(ll x) {
		split(x, x);
		return node[x].telim > 1e14 ? -1 : node[x].telim - 1;
	}
	ll qry_nte(ll x, ll y) {
		split(x, y);
		return node[y].ntemx - 1;
	}
} lct;

struct Edge {
	ll u, v, val, id;
};

ll n, m;
Edge e[MAXN];
bool mst[MAXN];

int main() {
	read(n), read(m);
	for (ll i = 1; i <= m; ++i) {
		read(e[i].u), read(e[i].v), read(e[i].val);
		e[i].id = i;
	}
	sort(e + 1, e + m + 1, [](Edge x, Edge y)->bool {
		return mkp(x.val, x.id) < mkp(y.val, y.id);
	});
	for (ll i = 1; i <= m; ++i) {
		if (lct.addedge(e[i].u, e[i].v, e[i].id + EDGE, e[i].val)) {
			mst[e[i].id] = 1;
		} else {
			mst[e[i].id] = 0;
		}
		cerr << e[i].id << ' ' << mst[e[i].id] << endl;
	}
	for (ll i = 1; i <= m; ++i) {
		if (!mst[e[i].id]) {
			lct.addlim(e[i].u, e[i].v, e[i].val);
		}
	}
	static ll ans[MAXN];
	for (ll i = 1; i <= m; ++i) {
		if (mst[e[i].id]) {
			ans[e[i].id] = lct.qry_te(e[i].id + EDGE);
		} else {
			ans[e[i].id] = lct.qry_nte(e[i].u, e[i].v);
		}
	}
	for (ll i = 1; i <= m; ++i) {
		write(ans[i]), space();
	}
	enter();
	return 0;
}
;             ;;;;;;;;;;;         ;
;                      ;         ; ;
;                    ;          ;   ;
;                   ;          ;     ;
;                 ;           ;;;;;;;;;
;               ;            ;         ;
;              ;            ;           ;
;;;;;;;;;;;   ;;;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;

  ;  ;  ;;; ;;;  ;   ;   ;  ;;  ;;  ;;; 
; ; ; ;  ;  ; ; ; ; ; ; ; ; ;;  ; ; ; ;  ;   ;
;;; ; ;  ;  ; ;   ; ; ;   ; ;;  ; ; ; ;  ;   ;
;;; ; ;  ;  ;;   ;  ; ;  ;  ;;  ;;  ;;  ;;; ;;;
;;; ; ;  ;  ;   ;   ; ; ;   ;;; ;;  ;    ;   ;
; ; ; ;  ;  ;   ; ; ; ; ; ;  ;  ; ; ;    ;   ;
;    ;  ;;; ;   ;;;  ;  ;;;  ;  ; ; ;
```

---

## 作者：Stinger (赞：1)

提供蒟蒻的一个 $\log$ 树剖做法。

先跑一遍 kruskal，求出一颗 MST，把树显式地建出来，然后分别讨论树边和非树边。

对于非树边 $(u,v)$，如果要使它一定在 MST 上，那么它只要取代任意一条树边即可。所以它的边权严格小于树上 $u,v$ 两点之间的路径的边权最大值，可以倍增。

对于树边$(x,y)$，它不能被任何一条非树边取代，而一条非树边 $(u,v)$ 取代它的情况和上文类似，即 $(x,y)$ 在 $u$ 到 $v$ 的路径上，且这条非树边的长度小于等于树边的长度。

所以对于每条长度为 $z$ 的非树边 $(x,y)$，$x$ 到 $y$ 的路径上所有树边边权都必须严格小于 $z$。这里可以方便的树剖+线段树维护。

时间复杂度 $O(n\log^2 n)$。

---

事实上，树剖可以做到 $O(n\log n)$，只不过我们不能用线段树维护，需要改成 st 表。

观察上面的线段树，发现只需要支持将区间内大于 $x$ 的数全部改为 $x$，以及单点查询，且修改全部在查询之前。所以我们可以搞个 st 表，修改完后不是从下往上递推而是从上往下，那么修改和查询都是 $O(1)$ 的，从上往下递推是 $O(n\log n)$ 的，总时间复杂度降为 $O(n\log n)$。

线段树代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

const int INF = 0x3fffffff;
inline int min(const int x, const int y) {return x < y ? x : y;}
inline int max(const int x, const int y) {return x > y ? x : y;}
struct Line {
	int u, v, w, id;
	inline bool operator < (const Line a) const {return w < a.w;}
} edge[200005];
struct Edge {
	int to, nxt, w;
} e[400005];
int n, m, f[200005], top[200005], dfn[200005],cnt, tot, fa[200005][20], Ans[200005];
int sze[200005], son[200005], dep[200005], head[200005], dist[200005][20];
bool mark[200005];
inline void AddEdge(int u, int v, int w) {
	e[++ tot].to = v, e[tot].nxt = head[u], e[tot].w = w, head[u] = tot;
}
int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}
void merge(int u, int v, int w) {
	int fx = find(u), fy = find(v);
	AddEdge(u, v, w), AddEdge(v, u, w);
	f[fx] = fy;
}

void dfs1(int u) {
	sze[u] = 1, dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < 20; ++ i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		dist[u][i] = max(dist[u][i - 1], dist[fa[u][i - 1]][i - 1]);
	}
	for (int i = head[u]; i; i = e[i].nxt)
		if (e[i].to != fa[u][0]) {
			int v = e[i].to;
			fa[v][0] = u, dist[v][0] = e[i].w, dfs1(v), sze[u] += sze[v];
			if (sze[v] > sze[son[u]]) son[u] = v;
		}
}
void dfs2(int u) {
	dfn[u] = ++ cnt;
	if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
	for (int i = head[u]; i; i = e[i].nxt)
		if (e[i].to != fa[u][0] && e[i].to != son[u])
			top[e[i].to] = e[i].to, dfs2(e[i].to);
}

struct Node {
	int l, r, v, Lazy;
} tree[800005];
void make_tree(int O, int L, int R) {
	tree[O].l = L, tree[O].r = R, tree[O].v = INF, tree[O].Lazy = INF;
	if (L != R) {
		make_tree(O << 1, L, L + R >> 1);
		make_tree(O << 1 | 1, (L + R >> 1) + 1, R);
	}
}
inline void pushdown(int O) {
	if (tree[O].Lazy == INF) return;
	tree[O << 1].v = min(tree[O << 1].v, tree[O].Lazy);
	tree[O << 1].Lazy = min(tree[O << 1].Lazy, tree[O].Lazy);
	tree[O << 1 | 1].v = min(tree[O << 1 | 1].v, tree[O].Lazy);
	tree[O << 1 | 1].Lazy = min(tree[O << 1 | 1].Lazy, tree[O].Lazy);
	tree[O].Lazy = INF;
}
void update(int O, int L, int R, int v) {
	if (L <= tree[O].l && tree[O].r <= R) {
		tree[O].v = min(tree[O].v, v), tree[O].Lazy = min(tree[O].Lazy, v);
		return;
	}
	int mid = tree[O].l + tree[O].r >> 1;
	pushdown(O);
	if (L <= mid) update(O << 1, L, R, v);
	if (mid < R) update(O << 1 | 1, L, R, v);
	tree[O].v = min(tree[O << 1].v, tree[O << 1 | 1].v);
}
int query(int O, int p) {
	if (tree[O].l == tree[O].r) return tree[O].v;
	int mid = tree[O].l + tree[O].r >> 1;
	pushdown(O);
	return p <= mid ? query(O << 1, p) : query(O << 1 | 1, p);
}
void change(int u, int v, int d) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
		update(1, dfn[top[u]], dfn[u], d);
		u = fa[top[u]][0];
	}
	if (dep[u] > dep[v]) u ^= v ^= u ^= v;
	if (dfn[u] < dfn[v]) update(1, dfn[u] + 1, dfn[v], d);
}
int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
		u = fa[top[u]][0];
	}
	return dep[u] < dep[v] ? u : v;
}
int ask(int u, int v) {
	int p = LCA(u, v), t1 = dep[u] - dep[p], t2 = dep[v] - dep[p], ans = 0;
	for (int i = 19; i >= 0; -- i)
		if (t1 & 1 << i) ans = max(ans, dist[u][i]), u = fa[u][i];
	for (int i = 19; i >= 0; -- i)
		if (t2 & 1 << i) ans = max(ans, dist[v][i]), v = fa[v][i];
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	make_tree(1, 1, n);
	for (int i = 1; i <= n; ++ i) f[i] = i;
	for (int i = 1; i <= m; ++ i)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w), edge[i].id = i;
	std::sort(edge + 1, edge + m + 1);
	for (int i = 1, cnt = 0; cnt < n - 1; ++ i)
		if (find(edge[i].u) != find(edge[i].v))
			merge(edge[i].u, edge[i].v, edge[i].w), mark[i] = true, ++ cnt;
	dfs1(1), top[1] = 1, dfs2(1);
	for (int i = 1; i <= m; ++ i)
		if (!mark[i]) change(edge[i].u, edge[i].v, edge[i].w);
	for (int i = 1; i <= m; ++ i)
		if (mark[i]) {
			int ans = query(1, max(dfn[edge[i].u], dfn[edge[i].v]));
			Ans[edge[i].id] = (ans < INF ? ans - 1 : -1);
		} else {
			int ans = ask(edge[i].u, edge[i].v);
			Ans[edge[i].id] = ans - 1;
		}
	for (int i = 1; i <= m; ++ i) printf("%d ", Ans[i]);
	return 0;
}
```

st 表代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

const int INF = 0x3fffffff;
inline int min(const int x, const int y) {return x < y ? x : y;}
inline int max(const int x, const int y) {return x > y ? x : y;}
struct Line {
	int u, v, w, id;
	inline bool operator < (const Line a) const {return w < a.w;}
} edge[200005];
struct Edge {
	int to, nxt, w;
} e[400005];
int n, m, f[200005], top[200005], dfn[200005],cnt, tot, fa[200005][20], Ans[200005];
int sze[200005], son[200005], dep[200005], head[200005], dist[200005][20];
bool mark[200005];
inline void AddEdge(int u, int v, int w) {
	e[++ tot].to = v, e[tot].nxt = head[u], e[tot].w = w, head[u] = tot;
}
int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}
void merge(int u, int v, int w) {
	int fx = find(u), fy = find(v);
	AddEdge(u, v, w), AddEdge(v, u, w);
	f[fx] = fy;
}

void dfs1(int u) {
	sze[u] = 1, dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < 20; ++ i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		dist[u][i] = max(dist[u][i - 1], dist[fa[u][i - 1]][i - 1]);
	}
	for (int i = head[u]; i; i = e[i].nxt)
		if (e[i].to != fa[u][0]) {
			int v = e[i].to;
			fa[v][0] = u, dist[v][0] = e[i].w, dfs1(v), sze[u] += sze[v];
			if (sze[v] > sze[son[u]]) son[u] = v;
		}
}
void dfs2(int u) {
	dfn[u] = ++ cnt;
	if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
	for (int i = head[u]; i; i = e[i].nxt)
		if (e[i].to != fa[u][0] && e[i].to != son[u])
			top[e[i].to] = e[i].to, dfs2(e[i].to);
}

int st[20][500005], Log[500005];
void update(int l, int r, int d) {
	int k = Log[r - l + 1];
	st[k][l] = min(st[k][l], d);
	st[k][r - (1 << k) + 1] = min(st[k][r - (1 << k) + 1], d);
}
void change(int u, int v, int d) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
		update(dfn[top[u]], dfn[u], d);
		u = fa[top[u]][0];
	}
	if (dep[u] > dep[v]) u ^= v ^= u ^= v;
	if (dfn[u] < dfn[v]) update(dfn[u] + 1, dfn[v], d);
}
int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) u ^= v ^= u ^= v;
		u = fa[top[u]][0];
	}
	return dep[u] < dep[v] ? u : v;
}
int ask(int u, int v) {
	int p = LCA(u, v), t1 = dep[u] - dep[p], t2 = dep[v] - dep[p], ans = 0;
	for (int i = 19; i >= 0; -- i)
		if (t1 & 1 << i) ans = max(ans, dist[u][i]), u = fa[u][i];
	for (int i = 19; i >= 0; -- i)
		if (t2 & 1 << i) ans = max(ans, dist[v][i]), v = fa[v][i];
	return ans;
}

int main() {
	for (int i = 0; i <= 19; ++ i)
	for (int j = 1; j <= 500000; ++ j) st[i][j] = INF;
	scanf("%d%d", &n, &m);
	f[1] = 1;
	for (int i = 2; i <= n; ++ i) f[i] = i, Log[i] = Log[i >> 1] + 1;
	for (int i = 1; i <= m; ++ i)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w), edge[i].id = i;
	std::sort(edge + 1, edge + m + 1);
	for (int i = 1, cnt = 0; cnt < n - 1; ++ i)
		if (find(edge[i].u) != find(edge[i].v))
			merge(edge[i].u, edge[i].v, edge[i].w), mark[i] = true, ++ cnt;
	dfs1(1), top[1] = 1, dfs2(1);
	for (int i = 1; i <= m; ++ i)
		if (!mark[i]) change(edge[i].u, edge[i].v, edge[i].w);
	for (int i = 19; i; -- i)
		for (int j = 1; j + (1 << i) - 1 <= n; ++ j) {
			st[i - 1][j] = min(st[i - 1][j], st[i][j]);
			st[i - 1][j + (1 << i - 1)] = min(st[i - 1][j + (1 << i - 1)], st[i][j]);
		}
	for (int i = 1; i <= m; ++ i)
		if (mark[i]) {
			int ans = st[0][max(dfn[edge[i].u], dfn[edge[i].v])];
			Ans[edge[i].id] = (ans < INF ? ans - 1 : -1);
		} else Ans[edge[i].id] = ask(edge[i].u, edge[i].v) - 1;
	for (int i = 1; i <= m; ++ i) printf("%d ", Ans[i]);
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：1)

首先$kruskal$跑出最小生成树

对图中每条边进行讨论（设这条边连接的两个点为$u,v$）

 - 非树边，要使这条边成为树边，把这条边的权值最大改为$u->v$路径上边权最大值-1即可
 - 树边，最大边权使得这条边依然是树边，最大能达到所有连接的点的路径经过这条边的非树边的边权最小值-1

如何做？非树边和树边分别做一下

需要维护路径最值，路径修改最值。转化成裸树剖了。。。

$20W$的范围两只$log$问题不大。码量较大，调半天。。。

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 200010
#define inf 0x3f3f3f3f
#define ls rt << 1
#define rs rt << 1 | 1
using namespace std;
struct Edge{
	int to, next, len, id;
}edge[maxn << 1];
struct Line{
	int x, y, z, flag, id;
}line[maxn << 1];
struct Seg{
	int l, r, Max, Min, tag;
}seg[maxn << 2];
int n, m, num, head[maxn], fa[maxn], f[maxn], d[maxn], size[maxn], son[maxn], id[maxn], Index;
int pre[maxn], prelen[maxn], wt[maxn], top[maxn], ans[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y, int z, int id){ edge[++num] = (Edge){ y, head[x], z, id }; head[x] = num; }
bool cmp(Line x, Line y){ return x.z < y.z; }
int get(int k){ return k == f[k] ? k : f[k] = get(f[k]); }

void kruskal(){
	for (int i = 1; i <= n; ++i) f[i] = i;
	for (int i = 1; i <= m; ++i){
		int s1 = get(line[i].x), s2 = get(line[i].y);
		if (s1 != s2){
			f[s1] = s2, line[i].flag = 1;
			addedge(line[i].x, line[i].y, line[i].z, line[i].id);
			addedge(line[i].y, line[i].x, line[i].z, line[i].id);
		}
	}
}

void dfs(int u){
	size[u] = 1, son[u] = -1;
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v != fa[u]){
			d[v] = d[u] + 1, fa[v] = u, pre[v] = edge[i].id, prelen[v] = edge[i].len;
			dfs(v);
			size[u] += size[v];
			if (son[u] == -1 || son[u] != -1 && size[son[u]] < size[v]) son[u] = v;
		}
	}
}

void dfs(int u, int x){
	wt[id[u] = ++Index] = prelen[u], top[u] = x;
	if (son[u] == -1) return;
	dfs(son[u], x);
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v != fa[u] && v != son[u]) dfs(v, v);
	}
}

void updmax(int &x, int y){ if (x < y) x = y; }
void updmin(int &x, int y){ if (x > y) x = y; }

void pushup(int rt){
	seg[rt].Max = max(seg[ls].Max, seg[rs].Max);
	seg[rt].Min = min(seg[ls].Min, seg[rs].Min);
}

void pushdown(int rt){
	updmin(seg[ls].Min, seg[rt].tag);
	updmin(seg[ls].tag, seg[rt].tag);
	updmin(seg[rs].Min, seg[rt].tag);
	updmin(seg[rs].tag, seg[rt].tag);
	seg[rt].tag = inf;
}

void build(int rt, int l, int r){
	seg[rt].Min = seg[rt].tag = inf;
	seg[rt].l = l, seg[rt].r = r;
	if (l == r){ seg[rt].Max = wt[l]; return; }
	int mid = (l + r) >> 1;
	build(ls, l, mid); build(rs, mid + 1, r);
	pushup(rt);
}

void update(int rt, int l, int r, int k){
	if (seg[rt].l > r || seg[rt].r < l) return;
	if (seg[rt].l >= l && seg[rt].r <= r){
		updmin(seg[rt].Min, k);
		updmin(seg[rt].tag, k);
		return;
	}
	pushdown(rt);
	update(ls, l, r, k); update(rs, l, r, k);
	pushup(rt);
}

int querymax(int rt, int l, int r){
	if (seg[rt].l > r || seg[rt].r < l) return 0;
	if (seg[rt].l >= l && seg[rt].r <= r) return seg[rt].Max;
	pushdown(rt);
	return max(querymax(ls, l, r), querymax(rs, l, r));
}

int querymin(int rt, int pos){
	if (seg[rt].l == seg[rt].r) return seg[rt].Min;
	pushdown(rt);
	if (seg[ls].r >= pos) return querymin(ls, pos); else
	return querymin(rs, pos);
}

int qrymax(int u, int v){
	int sum = 0;
	while (top[u] != top[v]){
		if (d[top[u]] < d[top[v]]) swap(u, v);
		updmax(sum, querymax(1, id[top[u]], id[u]));
		u = fa[top[u]];
	}
	if (d[u] > d[v]) swap(u, v);
	return max(sum, querymax(1, id[u] + 1, id[v]));
}

void updatemin(int u, int v, int k){
	while (top[u] != top[v]){
		if (d[top[u]] < d[top[v]]) swap(u, v);
		update(1, id[top[u]], id[u], k);
		u = fa[top[u]];
	}
	if (d[u] > d[v]) swap(u, v);
	update(1, id[u] + 1, id[v], k);
}

int main(){
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) line[i].x = read(), line[i].y = read(), line[i].z = read(), line[i].id = i;
	sort(line + 1, line + 1 + m, cmp);
	kruskal();
	dfs(1); dfs(1, 1);
	build(1, 1, n);
	for (int i = 1; i <= m; ++i)
		if (!line[i].flag){
			ans[line[i].id] = qrymax(line[i].x, line[i].y) - 1;
			updatemin(line[i].x, line[i].y, line[i].z);
		}
	for (int i = 2; i <= n; ++i) ans[pre[i]] = querymin(1, id[i]) - 1;
	for (int i = 1; i <= m; ++i) printf("%d ", ans[i] < inf - 1 ? ans[i] : -1);
	return 0;
}
```


---

## 作者：Genius_Z (赞：1)

[$\Large \color{blue}{Bl}\color{orange}{og}$](http://geiz-revive.github.io/)

题意是要求出一条边的边权为多大时，能出现在所有的最小生成树中，因此我们先随便造一棵最小生成树，进行分类讨论。

- 对于非树边，它的答案是它链接的这两个点在最小生成树上的链的最大值再-1，这样它才能替换掉树边。
- 对于树边，它的答案是能够让它所链接的两个点联通的非树边的最小值再减一，否则它会被替换掉。

之后可以发现，我们需要的只不过是一个能查询链上最大值、链上取最小值的一个数据结构，因此树剖$\Theta(nlog^2_n)$，LCT$\Theta(nlog_n)$

$\large Code:$

```cpp
#pragma region revive
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#define inl inline
#define re register int
#define fa(x) t[x].fa
#define son(x,y) t[x].child[y]
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define ll long long
const int inf = 0x3f3f3f3f;
#define lowbit(x) ((x) & (-x))
using namespace std;
#ifndef _DEBUG
#define getchar() (*(IOB.in.p++))
#define putchar(c) (*(IOB.out.p++)=(c))
#define io_eof() (IOB.in.p>=IOB.in.pend)
struct IOBUF { struct { char buff[1 << 26], *p, *pend; }in; struct { char buff[1 << 26], *p; }out; IOBUF() { in.p = in.buff; out.p = out.buff; in.pend = in.buff + fread(in.buff, 1, 1 << 26, stdin); }~IOBUF() { fwrite(out.buff, 1, out.p - out.buff, stdout); } }IOB;
#endif
template<typename IO>
inl void write(IO x) {
	if (x == 0) return (void)putchar('0');
	if (x < 0)putchar('-'), x = -x;
	static char buf[30];
	char* p = buf;
	while (x) {
		*(p++) = x % 10 + '0';
		x /= 10;
	}
	while (p > buf)putchar(*(--p));
}
inl void writestr(const char *s) { while (*s != 0)putchar(*(s++)); }
template<typename IO>inl void writeln(IO x) { write(x), putchar('\n'); }
template<typename IO>inl void writesp(IO x) { write(x), putchar(' '); }
inl int readstr(char *s) {
	char *begin = s, c = getchar();
	while (c < 33 || c>127) {
		c = getchar();
	}
	while (c >= 33 && c <= 127) {
		*(s++) = c;
		c = getchar();
	}
	*s = 0;
	return s - begin;
}
template<typename IO>
inl IO read() {
	IO x = 0;
	register bool w = 0;
	register char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') w = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return w ? -x : x;
}
#pragma endregion
int fa[1000001], ans[1000001];
bool vis[1000001];
struct node {
	int child[2], fa, w, max, tag;
	bool filp;
}t[1000001];
inl void maintain(int x) {
	t[x].max = max({ t[ls(x)].max, t[rs(x)].max, t[x].w });
}
inl bool poi(int x) { return rs(fa(x)) == x; }
inl bool nroot(int x) { return ls(fa(x)) == x || rs(fa(x)) == x; }
inl void reverse(int x) { swap(ls(x), rs(x)), t[x].filp ^= 1; }
inl void change(int x, int w) { ans[x] = min(ans[x], w), t[x].tag = min(t[x].tag, w); }
inl void rotate(int x) {
	re f = fa(x), gf = fa(f), fs = poi(x), gfs = poi(f), s = t[x].child[fs ^ 1];
	if (nroot(f))t[gf].child[gfs] = x;
	t[x].child[fs ^ 1] = f, t[f].child[fs] = s;
	if (s)fa(s) = f;
	fa(f) = x, fa(x) = gf, maintain(f);
}
inl void pushdown(int x) {
	if (t[x].filp) {
		if (ls(x))reverse(ls(x));
		if (rs(x))reverse(rs(x));
		t[x].filp = 0;
	}
	if (t[x].tag != inf) {
		if (ls(x))change(ls(x), t[x].tag);
		if (rs(x))change(rs(x), t[x].tag);
		t[x].tag = inf;
	}
}
inl void push(int x) {
	if (nroot(x))push(fa(x));
	pushdown(x);
}
inl void splay(int x) {
	push(x);
	while (nroot(x)) {
		if (nroot(fa(x)))poi(x) == poi(fa(x)) ? rotate(fa(x)) : rotate(x);
		rotate(x);
	}
	maintain(x);
}
inl void access(int x) {
	for (re i = 0; x; x = fa(i = x)) splay(x), rs(x) = i, maintain(x);
}
inl void makeroot(int x) {
	access(x), splay(x), reverse(x);
}
inl void split(int x, int y) {
	makeroot(y), access(x), splay(x);
}
inl void link(int x, int y) {
	split(x, y), fa(y) = x;
}
struct edge {
	int u, v, w, id;
	bool operator <(const edge &fff)const {
		return w < fff.w;
	}
}e[1000001];
inl int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
signed main() {
	re n = read<int>(), m = read<int>(), u, v, w = n + m, now;
	for (re i = 1; i <= w; i++)t[i].tag = ans[i] = inf;
	for (re i = 1; i <= m; i++) u = read<int>(), v = read<int>(), w = read<int>(), e[i] = edge{ u,v,w }, e[i].id = i;
	sort(e + 1, e + 1 + m);
	for (re i = 1; i <= m; i++) {
		u = e[i].u, v = e[i].v, w = e[i].w, now = e[i].id + n;
		if (find(u) != find(v)) {
			fa[find(v)] = u;
			t[now].w = t[now].max = w;
			link(u, now), link(v, now), vis[now] = 1;
		}
		else {
			split(u, v);
			ans[now] = t[u].max - 1;
			change(u, w);
		}
	}
	for (re i = n + 1, k = n + m; i <= k; i++) {
		if (vis[i]) {
			access(i), splay(i), writesp(ans[i] == inf ? -1 : ans[i] - 1);
		}
		else {
			writesp(ans[i]);
		}
	}
}
```



---

## 作者：WJiannan (赞：1)

> 给定一个点数为 $n$，边数为 $m$，权值不超过 $10^9$ 的带权连通图，没有自环与重边。
> 现在要求对于每一条边求出，这条边的边权最大为多少时，它还能出现在所有可能的最小生成树上，如果对于任意边权都出现，则输出 $-1$。
> ($2 \le n \le 2 \times 10^5, n-1 \le m \le 2 \times 10^5$)

由于偷懒，我只写了 $O(n\log^2 n)$ 的做法。

分 $2$ 种情况考虑：

 - **一条边 $e(u,v)$ 不在任意的最小生成树上**：
	 -  则一定要使 $w_e$ 小于最小生成树的上 $u$ 到 $v$ 的路径上的最大权值。
	 - 证明：考虑 $\mathrm{Kruskal}$ 的计算过程，先将边按照边权排序，如果 $w_e$ 要在最小生成树上，那么只需要令其在 $u,v$ 各自所在联通块被连接在一起前，加入 $e(u,v)$ 即可，所以只要使 $w_e$ 小于最小生成树的上 $u$ 到 $v$ 的路径上的最大权值。 
 - **一条边 $e(u,v)$ 在其中一个最小生成树上**：
	 - 则其权值等于不在最小生成树上的边 $e'(u',v')$，且 $u',v'$ 的路径经过边 $e(u,v)$ 的权值 $w_{e'} - 1$；
	 - 证明：由前一个证明可知，$e(u,v)$ 在最小生成树，只需要满足 $e'(u',v')$ 的权值都比它大即可。
	
所以有了上述想法，我们就能自然而然想出一个非常 simple 且 naive 的做法。

只需要任意的求出一个最小生成树，用**树链剖分线段树**维护树上两点间路径的区间查询和区间取 $\min$ 即可，$O(n \log^2 n)$。

复杂度更低的做法（杂谈）：
更多做法尽在 http://blog.csdn.net/Steaunk/article/details/79504451
广告

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#define R register
#define Min(_A, _B) (_A < _B ? _A : _B)
#define Max(_A, _B) (_A > _B ? _A : _B)
template <class TT>  void Swap(R TT &A, R TT &B){ R TT t = A; A = B; B = t; }
int F()
{
	R int x; R char ch;
	while(ch = getchar(), ch < '0'|| ch > '9'); x = ch - '0';
	while(ch = getchar(), ch >= '0' && ch <= '9') x = ch - '0' + x * 10;
	return x;
}
const int Size = 200010, Inf = 2147483647;
int n, m, Point[Size], Next[Size << 1], To[Size << 1], W1[Size << 1], W2[Size << 1], q;
struct Edge{ int u, v, c, Ans; } e[Size], *p[Size];
void Add(R Edge *t)
{
	Next[++q] = Point[t->u]; Point[t->u] = q; To[q] = t->v; W1[q] = t->c, W2[q] = t - e;
	Next[++q] = Point[t->v]; Point[t->v] = q; To[q] = t->u; W1[q] = t->c, W2[q] = t - e;
}
bool cmp(R Edge *i, R Edge *j){ return i->c < j->c; }
int Sum[Size], Most[Size], dfn[Size], dfn_index, Pre[Size], A[Size], Who[Size];
int fa[Size], dep[Size], last[Size];
int Find(R int now){ return last[now] == now ? now : last[now] = Find(last[now]); }
void DFS1(R int u, R int from)
{
	Sum[u] = 1;
	dep[u] = dep[fa[u] = from] + 1;
	for(R int j = Point[u]; j; j = Next[j])
		if(To[j] != from)
		{
			DFS1(To[j], u);
			Sum[u] += Sum[To[j]];
			if(Sum[Most[u]] < Sum[To[j]]) Most[u] = To[j];
		}
}
void DFS2(R int u, R int from, R int Grand, R int j)
{
	A[dfn[u] = ++dfn_index] = W1[j]; Who[u] = W2[j];
	Pre[u] = Grand;
	for(R int j = Point[u]; j; j = Next[j]) if(Most[u] == To[j]) 
		DFS2(Most[u], u, Grand, j);
	for(R int j = Point[u]; j; j = Next[j])
		if(To[j] != from && To[j] != Most[u])
			DFS2(To[j], u, To[j], j);
}
int S0[1 << 19], Lazy[1 << 19], S1[1 << 19];
void Pushdown(R int node)
{
	if(Lazy[node] < Inf)
	{
		Lazy[node << 1] = Min(Lazy[node << 1], Lazy[node]);
		Lazy[node << 1 | 1] = Min(Lazy[node << 1 | 1], Lazy[node]);
		S0[node << 1] = Min(S0[node << 1], Lazy[node]);
		S0[node << 1 | 1] = Min(S0[node << 1 | 1], Lazy[node]);
		Lazy[node] = Inf;
	}
}
void Modify0(R int node, R int begin, R int end, R int l, R int r, R int val)
{
	if(l <= begin && end <= r)
	{
		S0[node] = Min(S0[node], val);
		Lazy[node] = Min(Lazy[node], val);
		return ;
	}
	Pushdown(node);
	R int mid = begin + end >> 1;
	if(l <= mid) Modify0(node << 1, begin, mid, l, r, val);
	if(r > mid) Modify0(node << 1 | 1, mid + 1, end, l, r, val);
}
int Query0(R int node, R int begin, R int end, R int l, R int r)
{
	if(l > r) return S0[node];
	if(l <= begin && end <= r) return S0[node];
	Pushdown(node);
	R int mid = begin + end >> 1, t1 = Inf, t2 = Inf;
	if(l <= mid) t1 = Query0(node << 1, begin, mid, l, r);
	if(r > mid) t2 = Query0(node << 1 | 1, mid + 1, end, l, r);
	return Min(t1, t2);
}
int Query1(R int node, R int begin, R int end, R int l, R int r)
{
	if(l > r) return S1[node];
	if(l <= begin && end <= r) return S1[node];
	R int mid = begin + end >> 1, t1 = 0, t2 = 0;
	if(l <= mid) t1 = Query1(node << 1, begin, mid, l, r);
	if(r > mid) t2 = Query1(node << 1 | 1, mid + 1, end, l, r);
	return Max(t1, t2);
}
void Build1(R int node, R int begin, R int end)
{
	if(begin == end)
	{
		S1[node] = A[begin];
		return ;
	}
	R int mid = begin + end >> 1;
	Build1(node << 1, begin, mid);
	Build1(node << 1 | 1, mid + 1, end);
	S1[node] = Max(S1[node << 1], S1[node << 1 | 1]);
}
void Build0(R int node, R int begin, R int end)
{
	S0[node] = Lazy[node] = Inf;
	if(begin == end) return ;
	R int mid = begin + end >> 1;
	Build0(node << 1, begin, mid);
	Build0(node << 1 | 1, mid + 1, end);
}
void Work(R Edge *i)
{
	R int A = i->u, B = i->v;
	while(Pre[A] != Pre[B])
	{
		if(dep[Pre[A]] < dep[Pre[B]]) Swap(A, B);
		Modify0(1, 1, n, dfn[Pre[A]], dfn[A], i->c);
		R int t = Query1(1, 1, n, dfn[Pre[A]], dfn[A]);
		i->Ans = Max(i->Ans, t);
		A = fa[Pre[A]];
	}
	if(A == B) return ;
	if(dep[A] < dep[B]) Swap(A, B);
	Modify0(1, 1, n, dfn[B] + 1, dfn[A], i->c);
	R int t = Query1(1, 1, n, dfn[B] + 1, dfn[A]);
	i->Ans = Max(i->Ans, t);
}
int main()
{
	scanf("%d %d", &n, &m);
	for(R int i = 1; i <= m; i++) e[i] = (Edge){F(), F(), F(), -1};
	for(R int i = 1; i <= m; i++){ last[i] = i; p[i] = e + i; }
	std::sort(p + 1, p + 1 + m, cmp);
	for(R int i = 1; i <= m; i++)
	{
		R int X = Find(p[i]->u), Y = Find(p[i]->v);
		if(X != Y){ last[X] = Y; Add(p[i]); }
	}
	DFS1(1, 0); DFS2(1, 0, 0, 0);
	Build0(1, 1, n); Build1(1, 1, n);
	for(R int i = 1; i <= n; i++) last[i] = i;
	for(R int i = 1; i <= m; i++)
	{
		R int X = Find(p[i]->u), Y = Find(p[i]->v);
		if(X != Y) last[X] = Y;
		else Work(p[i]);
	}
	for(R int i = 1; i <= n; i++) e[Who[i]].Ans = Query0(1, 1, n, dfn[i], dfn[i]);
	for(R Edge *i = e + 1; i <= e + m; i++)
		if(i->Ans == Inf) printf("-1 ");
		else printf("%d ", i->Ans - 1);
	return 0;
}
```

---

## 作者：LJ26yanxingyu (赞：1)

### 题意
题目说的非常清晰，就是一条边能选入最小生成树时，这条边最大为几，如果无论如何，这条边都必定选入，输出 $-1$。

### 思路
就是建一个最小生成树，一个环上的在树上的边答案为环上未选入树上的最小边减一，未选入树上的边是环上选入树上边的最大值减一，这样就能保证这条边一定入选树上。

这里提供一个简单好写，只用倍增 LCA 和并查集的做法，就是从小到大枚举，然后暴力跳，因为一个环上的在树上的边答案为未选入树上的最小边减一，又是从小到大枚举的，所以每条树上的边只会在第一次跳到时被赋值，我们只用路径压缩一下树上被跳到的边就好了，再建一个图求公共祖先和环上最大值来求未选入树上的边的答案，时间复杂度是 $O(m\log{n})$ 的，可以通过。

### 代码
```cpp
#include<bits/stdc++.h>
#define N 500015
#define M 2000015
 
using namespace std;
 
//#define DEBUG 1  // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}
 
  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  // 调试，可显示字符
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }
  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }
  template <class T>
  void read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp * (ch - '0');
    if (sign) x = -x;
  }
  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc());
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }
  void read(char &c) { for (c = gc(); blank(c); c = gc()); }
  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }
 
  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-');  // 负数输出
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }
  void write_s(string S_tr){
  	string::iterator it=S_tr.begin();
  	while(it!=S_tr.end())push(*it),++it;
  }
 
  template <class T>
  void write(T x, char lastChar) {
    write(x), push(lastChar);
  }
} io;
 
int n,m;
struct node{
	int a1,b1,z,id;
	friend bool operator <(node a11,node a22){
		return a11.z<a22.z;
	}
	bool book;
}p[M];
struct jie{
	int to,net,w,id;
}e[M*2];
 
int hed[N],W=1,yi[M],ans[M];
int fa[N],dep[N],f[N][22],mx[N][22];
bool mark[N];
 
void _add(int a1,int b1,int zh,int id){
	e[W]=(jie){b1,hed[a1],zh,id},hed[a1]=W++;
	return;
}
int get_fa(int x){
	return x==fa[x]?x:fa[x]=get_fa(fa[x]);
}
void _kruscal(){
	int cnt=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int fa1=get_fa(p[i].a1),fa2=get_fa(p[i].b1);
		if(fa1!=fa2){
			fa[fa1]=fa2;
			p[i].book=1;
			cnt++;
			if(cnt==n-1)break;
		}
	}
	return;
}
void _dfs(int x){
	mark[x]=1;
	for(int i=1;i<=18;i++){
		f[x][i]=f[f[x][i-1]][i-1];
		mx[x][i]=max(mx[x][i-1],mx[f[x][i-1]][i-1]);
	}
	int y;
	for(int j=hed[x];j;j=e[j].net){
		y=e[j].to;
		if(!mark[y]){
			dep[y]=dep[x]+1;
			f[y][0]=x;
			yi[y]=e[j].id;
			mx[y][0]=e[j].w;
			_dfs(y);
		}
	}
	return;
}
int get_ans(int x,int lca,int d){
	if(dep[x]<=dep[lca])return x;
	if(ans[yi[x]]==-1)ans[yi[x]]=d;
	return fa[x]=get_ans(fa[x],lca,d);
}
pair<int,int> LCA(int a1,int b1){
	int tmp=0;
	if(dep[a1]>dep[b1])swap(a1,b1);
	int ca=dep[b1]-dep[a1],k=0;
	while(ca){
		if(ca%2==1)tmp=max(tmp,mx[b1][k]),b1=f[b1][k];
		ca/=2,k++;
	}
	if(a1==b1)return make_pair(a1,tmp);
	for(int i=18;i>=0;i--){
		if(f[a1][i]!=f[b1][i]){
			tmp=max(max(mx[a1][i],mx[b1][i]),tmp);
			a1=f[a1][i],b1=f[b1][i];
		}
	}
	tmp=max(tmp,max(mx[a1][0],mx[b1][0]));
	return make_pair(f[a1][0],tmp);
}
 
int main(){
	io.read(n),io.read(m);
	for(int i=1;i<=m;i++){
		io.read(p[i].a1),io.read(p[i].b1),io.read(p[i].z);
		p[i].id=i;
	}
	sort(p+1,p+1+m);
	_kruscal();
	for(int i=1;i<=m;i++){
		if(p[i].book){
			_add(p[i].a1,p[i].b1,p[i].z,p[i].id);
			_add(p[i].b1,p[i].a1,p[i].z,p[i].id);
		}
	}
	dep[1]=1;
	_dfs(1);
	for(int i=1;i<=n;i++){
		fa[i]=f[i][0];
	}
	for(int i=1;i<=m;i++)ans[i]=-1;
	for(int i=1;i<=m;i++){
		if(p[i].book)continue;
		pair<int,int>tmp=LCA(p[i].a1,p[i].b1);
		ans[p[i].id]=tmp.second-1;
		get_ans(p[i].a1,tmp.first,p[i].z-1);
		get_ans(p[i].b1,tmp.first,p[i].z-1);
	}
	int t=1,v;
	while(t<=m){
		io.write(ans[t],' ');
		t++;
	}
	return 0;
}
``````

---

## 作者：baka24 (赞：0)

题解里的感觉都看不太懂，写一下我的做法。

我们先建出最小生成树，分别考虑在树上和不在树上的边。

对于不在树上的边，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/5alxc9zi.png)

我们考虑对于蓝色边，我们需要让它取代一条红色边。如果它出现在了最小生成树上，在红色生成树 $1\sim 4$ 的路径上一定有一条边被蓝色边取代了，而它（被取代的红色边）一定比蓝色边大。

那么我们可以知道，一条不在最小生成树上的边的最大权值即 $u,v$ 路径上最大值减 $1$。

对于在树上的边，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/is3rqcjz.png)

考虑深红色边，对于这条边，可能取代它的即为绿色边。深红色边的最大权值必须小于绿色边的最小值。

观察后我们发现这相当于绿色边向生成树上的边做贡献。我们让所有非树边对于树上 $u,v$ 之间的所有边做贡献。具体的，让 $u,v$ 之间所有边对于 $w$ 取 $\min$。

总结一下，我们需要两个操作：

1. 查询 $x,y$ 路径上的最小值。
2. 让点 $x,y$ 之间所有边对于 $w$ 取 $\min$ 

发现可以树链剖分做，然后就没了。

顺便一提，可以不用线段树。最小值用ST表预处理，取 $\max$ 可以差分做（具体实现看代码）。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson (pos<<1)
#define rson (pos<<1|1)
#define pii pair<int,int> 
#define fr first
#define sc second 
#define mk make_pair
#define pb push_back
#define gczakioi true
#define inx int i=h[u],v=(~i)?edge[i].v:0,w=(~i)?edge[i].w:0;~i;i=edge[i].nx,v=(~i)?edge[i].v:0,w=(~i)?edge[i].w:0
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=200010,N=20;
int n,m;
//链式前向星存图
struct Edge{int v,w,nx;}edge[MAXN<<1];int h[MAXN],CNT;void init(){memset(h,-1,sizeof(h));CNT=1;}
void add_side(int u,int v,int w){edge[++CNT]={v,w,h[u]};h[u]=CNT;edge[++CNT]={u,w,h[v]};h[v]=CNT;}
//并查集找出最小生成树
struct side{
	int u,v,w,as,id;bool tr;
	bool operator <(const side&G)const{
		return id<G.id;
	}
}s[MAXN];
bool cmp(side x,side y){return x.w<y.w;}
int ff[MAXN];
int fid(int x){
	if(ff[x]==x)return x;
	return ff[x]=fid(ff[x]);
}
//树链剖分
int a[MAXN],dy[MAXN],dfn[MAXN],cnt,siz[MAXN],son[MAXN],fa[MAXN],top[MAXN],ty,sd[MAXN];
void dfs1(int u,int lst){
	int mx=0;fa[u]=lst;siz[u]=1;
	for(inx)if(v!=lst){
		a[v]=w;sd[v]=sd[u]+1;
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>mx){
			mx=siz[v];son[u]=v;
		}
	}
}
void dfs2(int u,int lst){
	dfn[u]=++cnt;dy[cnt]=u;top[u]=ty;
	if(son[u])dfs2(son[u],u);
	for(inx)if(v!=lst&&v!=son[u]){
		ty=v;
		dfs2(v,u);
	}
}
//ST表
int f[N][MAXN],lg2[MAXN];
void build(){
	for(int i=1;i<=n;i++){
		if(i!=1)lg2[i]=lg2[i>>1]+1;
		f[0][i]=a[dy[i]];
	}
	for(int i=1;1<<i<=n;i++){
		for(int j=1;j+(1<<i-1)<=n;j++){
			f[i][j]=max(f[i-1][j],f[i-1][j+(1<<i-1)]);
		}
	}
}
int query(int l,int r){
	int g=lg2[r-l+1];
	return max(f[g][l],f[g][r-(1<<g)+1]);
}
//差分维护最小值用
vector<int> in[MAXN],de[MAXN];
int as[MAXN];multiset<int>st;
//查询+修改
int qry(int x,int y,int z){
	int res=0;
	while(top[x]!=top[y]){
		if(sd[top[x]]<sd[top[y]])swap(x,y);
		res=max(res,query(dfn[top[x]],dfn[x]));
		in[dfn[top[x]]].pb(z);
		de[dfn[x]+1].pb(z);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])swap(x,y);
	if(x^y){
		res=max(res,query(dfn[x]+1,dfn[y]));
		in[dfn[x]+1].pb(z);
		de[dfn[y]+1].pb(z);
	}
	return res;
}
void slv(){init();
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){ff[i]=i;
		s[i].u=read(),s[i].v=read(),s[i].w=read();
		s[i].id=i;
	}
	sort(s+1,s+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=fid(s[i].u),y=fid(s[i].v);
		if(x!=y){
			ff[x]=y;
			add_side(s[i].u,s[i].v,s[i].w);
			s[i].tr=1;//建树+标记树边
		}
	}
	dfs1(1,1);ty=1;
	dfs2(1,1);
	build();
	for(int i=1;i<=m;i++){
		if(!s[i].tr){
			s[i].as=qry(s[i].u,s[i].v,s[i].w)-1;//统计非树边答案
		}
	}
	for(int i=1;i<=n;i++){//统计树边答案
		for(int j=0;j<de[i].size();j++)st.erase(st.find(de[i][j]));
		for(int j=0;j<in[i].size();j++)st.insert(in[i][j]);
		if(!st.empty())as[i]=*st.begin();
		else as[i]=0;
	}
	for(int i=1;i<=m;i++){
		if(s[i].tr){
			if(sd[s[i].u]>sd[s[i].v])swap(s[i].u,s[i].v);
			s[i].as=as[dfn[s[i].v]]-1;
		}
	}
	sort(s+1,s+m+1);//输出
	for(int i=1;i<=m;i++){
		printf("%d ",s[i].as);
	}
}
signed main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	slv();
    return 0;
} 	
```

---

## 作者：SrsgPrince_ (赞：0)

# CodeForces CF827D Best Edge Weight Solution

题目传送门：[CF827D(Luogu)](https://www.luogu.com.cn/problem/CF827D) 和原题 [CF827D(CodeForces)](http://codeforces.com/problemset/problem/827/D)。

推荐在我的 [博客](https://www.luogu.com.cn/blog/fy123333/CodeForcesCF827DSolution) 中查看。

## 题目分析 Hint

给定一个点数为 $n$，边数为 $m$，权值不超过 $1 \times 10^9$ 的带权连通图，没有自环和重边。对于每一条边求出这条边的边权最大为多少的时候，它还能出现在所有可能的最小生成树上，如果多余任意边权都出现，则输出 $-1$。

数据范围：$2 \leq n \leq 2 \times 10^5, n-1 \leq m \leq 2 \times 10^5$。

根据题意，我们可以先跑一遍最小生成树，然后我们分讨一下树边和非树边。

## 思路 Solution

如果是非树边，即 $u, v$ 在一个连通块里，边权必须比它的两个端点在树上的路径最长的那条边小，那么这时候答案直接就是 $u-v$ 路径上边权最大值 $-1$。对于树边，我们不能让它被替换掉，那么连接 $u, v$ 的非树边，需要这条路径上的边权小于这条非树边的边权，那么答案就是边权最小值 $-1$。这些区间 $\min$ 和 $\max$ 树剖和 LCT 都能实现，树剖的复杂度 $O(n \log^2 n)$，LCT 复杂度 $O(n \log n)$。我使用的是 LCT。

```cpp
const int maxn = 5e5 + 10;
int n, m, cnt, top, a1;
int a[maxn], val[maxn], chd[2][maxn], rev[maxn], fa[maxn], res[maxn], stk[maxn];
int dep[maxn], head[maxn], fath[20][maxn], opt[3][maxn];
struct Node {
    int u, v, w, idx, nxt;
    inline bool operator < (Node b) const {
        return this->w < b.w;
    }
} edg[maxn], ed[maxn << 1];
struct Priority {
    int v, p;
    inline friend bool operator < (Priority a, Priority b) {
        return a.v > b.v;
    }
};
priority_queue<Priority> que[maxn];
inline bool nRoot(int x) {
    return chd[0][fa[x]] == x || chd[1][fa[x]] == x;
}
inline void pushUp(int x) {
    val[x] = max(max(val[chd[0][x]], val[chd[1][x]]), a[x]);
}
inline void reverse(int x) {
    swap(chd[0][x], chd[1][x]);
    rev[x] ^= 1;
}
inline void pushDown(int x) {
    if (!rev[x]) 
        return;
    reverse(chd[0][x]);
    reverse(chd[1][x]);
    rev[x] = 0;
}
inline void rotate(int x) {
    int y = fa[x], z = fa[y], k = (chd[1][y] == x), w = (chd[1][z] == y), ance = chd[!k][x];
	if (nRoot(y))
        chd[w][z] = x;
    chd[!k][x] = y;
    chd[k][y] = ance;
	if(ance)
        fa[ance] = y;
    fa[y] = x;
    fa[x] = z;
	pushUp(y);pushUp(x);
}
inline void splay(int x) {
    int y = x, top = 0;
    stk[++top] = x;
    while (nRoot(y))
        stk[++top] = y = fa[y];
    while (top)
        pushDown(stk[top--]);
    while (nRoot(x)) {
        y = fa[x];
        int z = fa[y];
        if (nRoot(y))
            rotate((chd[1][y] == x) ^ (chd[1][z] == y) ? x : y);
        rotate(x);
    }
    pushUp(x);
}
inline void access(int x) {
    for (int y = 0; x; x = fa[y = x]){
        splay(x);
        chd[1][x] = y;
        pushUp(x);
    }
}
inline void makeRoot(int x) {
    access(x);
    splay(x);
    reverse(x);
}
inline int findRoot(int x) {
    access(x);
    splay(x);
    while (chd[0][x]) {
        pushDown(x);
        x = chd[0][x];
    }
    splay(x);
    return x;
}
inline void split(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
}
inline void link(int x, int y) {
    makeRoot(x);
    if (findRoot(y) != x)
        fa[x] = y;
}
inline void cut(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x && fa[y] == x && !chd[0][y]) {
        fa[y] = chd[1][x] = 0;
        pushUp(x);
    }
}
inline void addEdge(int b, int e) {
    ed[++cnt].u = b;
    ed[cnt].v = e;
    ed[cnt].nxt = head[b];
    head[b] = cnt;
}
inline void dfs(int u, int f) {
    fath[0][u] = f;
    dep[u] = dep[f] + 1;
    for (int i = 1; i <= 19; ++i) {
        if (!fath[i-1][fath[i-1][u]]) 
            break;
        fath[i][u] = fath[i-1][fath[i-1][u]];
    }
    for (int i = head[u]; i; i = ed[i].nxt) {
        int v = ed[i].v;
        if (v == f) continue;
        dfs(v, u);
    }
}
inline int LCA(int x, int y) {
    if (dep[y] > dep[x])
        swap(x, y);
    for (int i = 19; i >= 0; --i)
        if (dep[x] - (1 << i) >= dep[y])
            x = fath[i][x];
    if (y == x)
        return x;
    for (int i = 19; i >= 0; --i)
        if (fath[i][x] != fath[i][y])
            x = fath[i][x], y = fath[i][y];
    return fath[0][x];
}
inline void dfs2(int u) {
    for (int i = head[u]; i; i = ed[i].nxt) {
        int v = ed[i].v;
        if (v == fath[0][u]) 
            continue;
        dfs2(v);
        if (que[v].size() > que[u].size())
            swap(que[v], que[u]);
        while (!que[v].empty()) {
            if (dep[que[v].top().p] <= dep[u])
                que[u].push(que[v].top());
            que[v].pop();
        }
    }
    while (que[u].size() && dep[que[u].top().p] > dep[u])
        que[u].pop();
    if (u > n && que[u].size())
        res[u - n] = que[u].top().v;
}
signed main() {
    quickRead(n, m);
    for (int i = 1; i <= m; ++i){
        quickRead(edg[i].u, edg[i].v, edg[i].w);
        edg[i].idx = i;
        res[i] = -1;
    }
    sort(edg+1, edg+m+1);
    for (int i = 1; i <= m; ++i) {
        int u = edg[i].u, v = edg[i].v;
        a[edg[i].idx + n] = edg[i].w;
        if (findRoot(u) == findRoot(v)) {
            split(u, v);
            res[edg[i].idx] = val[v] - 1;
            opt[0][++top] = u;
            opt[1][top] = v;
            opt[2][top] = edg[i].w - 1;
        } else {
            link(u, edg[i].idx + n);
            link(v, edg[i].idx + n);
            addEdge(u, edg[i].idx + n);
            addEdge(edg[i].idx + n, u);
            addEdge(v, edg[i].idx + n);
            addEdge(edg[i].idx + n, v);
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= top; ++i) {
        int x = opt[0][i], y = opt[1][i], lca = LCA(x, y);
        if (x != lca)
            que[x].push((Priority){opt[2][i], lca});
        if (y != lca)
            que[y].push((Priority){opt[2][i], lca});
    }
    dfs2(1);
    for (int i = 1; i <= m; ++i)
        quickWrite(res[i], ' ');
    return 0;
}
```


---

## 作者：5k_sync_closer (赞：0)

树上倍增+可并堆。

把原图的 MST 建出来，分别考虑非树边和树边的答案。

对于非树边 $(u,v)$，其最大为 $u\to v$ 路径最大值 $-1$ 时，可以替换掉这个最大值，加入 MST。

树上倍增维护路径最大值即可。

对于树边 $(u,v)$，其最大为所有覆盖其的非树边的最小值 $-1$ 时，不会被这些非树边替换，在 MST 中。

即对每条非树边在 MST 上的路径，对这条非树边的权值 check min。

用可并堆维护 check min 操作。

具体地，对每条非树边 $(u,v,w)$，在堆 $q_u$ 和 $q_v$ 中加入 $(w,\operatorname{lca}(u,v))$，

从下往上合并每个点的堆，合并到 $u$ 点时 $q_u$ 包含所有端点在 $u$ 子树内的 check min 操作。

这些操作中，只有 $\operatorname{lca}$ 的深度小于 $u$ 的操作可以影响到 $(u,fa_u)$ 这条边，所以把堆顶上 $\operatorname{lca}$ 深度大于等于 $u$ 的操作弹出，

此时的堆顶即为 $(u,fa_u)$ 这条树边的答案。特别地，堆为空时 $(u,fa_u)$  的答案为 $-1$。

```cpp
#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
struct E
{
    int v, w, t;
} e[400050];
struct S
{
    int u, v, w, i;
} g[200050];
__gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>> q[200050];
int n, m, c, z[200050], r[200050], d[200050], h[200050], f[20][200050], w[20][200050];
bool o[200050];
bool C(S a, S b) { return a.w < b.w; }
bool R(S a, S b) { return a.i < b.i; }
int F(int x) { return x == z[x] ? x : z[x] = F(z[x]); }
void A(int u, int v, int w) { e[++c] = {v, w, h[u]}, h[u] = c; }
void D(int u)
{
    for (int i = h[u], v; i; i = e[i].t)
        if (!d[v = e[i].v])
        {
            w[0][v] = e[i].w;
            d[v] = d[f[0][v] = u] + 1;
            for (int j = 1; f[j - 1][v]; ++j)
                f[j][v] = f[j - 1][f[j - 1][v]], w[j][v] = max(w[j - 1][v], w[j - 1][f[j - 1][v]]);
            D(v);
        }
}
int L(int u, int v)
{
    if (d[u] < d[v])
        swap(u, v);
    while (d[u] > d[v])
        u = f[__lg(d[u] - d[v])][u];
    if (u == v)
        return u;
    for (int k = __lg(d[u]); k >= 0; --k)
        if (f[k][u] != f[k][v])
            u = f[k][u], v = f[k][v];
    return f[0][u];
}
int Q(int u, int v)
{
    int q = 0;
    if (d[u] < d[v])
        swap(u, v);
    while (d[u] > d[v])
        q = max(q, w[__lg(d[u] - d[v])][u]), u = f[__lg(d[u] - d[v])][u];
    if (u == v)
        return q;
    for (int k = __lg(d[u]); k >= 0; --k)
        if (f[k][u] != f[k][v])
            q = max({q, w[k][u], w[k][v]}), u = f[k][u], v = f[k][v];
    return max({q, w[0][u], w[0][v]});
}
void M(int u, int k)
{
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            M(v, u), q[u].join(q[v]);
    while (!q[u].empty() && d[q[u].top().second] >= d[u])
        q[u].pop();
    if (!q[u].empty())
        r[u] = q[u].top().first - 1;
    else
        r[u] = -1;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        z[i] = i;
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w), g[i].i = i;
    sort(g, g + m, C);
    for (int i = 0, u, v, p = 0; i < m; ++i)
        if ((u = F(g[i].u)) != (v = F(g[i].v)))
        {
            z[u] = v;
            o[g[i].i] = 1;
            A(g[i].u, g[i].v, g[i].w);
            A(g[i].v, g[i].u, g[i].w);
            if (++p == n - 1)
                break;
        }
    D(d[1] = 1);
    for (int i = 0, l; i < m; ++i)
        if (!o[g[i].i])
            q[g[i].u].push({g[i].w, l = L(g[i].u, g[i].v)}), q[g[i].v].push({g[i].w, l});
    M(1, 0);
    sort(g, g + m, R);
    for (int i = 0; i < m; ++i)
        if (o[i])
            printf("%d ", r[d[g[i].u] > d[g[i].v] ? g[i].u : g[i].v]);
        else
            printf("%d ", Q(g[i].u, g[i].v) - 1);
    return 0;
}
```


---

## 作者：I_am_Accepted (赞：0)

第一届粉兔杯被粉兔用这道题淘汰~~话说粉兔杯怎么出原题啊~~。

先随便找出一棵生成树，对于树边和非树边分别计算答案。

非树边 $(u,v)$ 的答案为 $u,v$ 在树上路径权值 $\max-1$，这里我使用倍增求。

树边的答案为所有覆盖其的非树边的权值 $\min-1$（没被覆盖过则答案为 $-1$），这里将非树边按边权升序排序，一条链覆盖前面覆盖过的树边是无意义的，所以使用树上并查集维护没有被覆盖过的边即可。

复杂度线性对数。

[代码](https://codeforces.com/contest/827/submission/208043680) 挺短的。

---

## 作者：Echoternity (赞：0)

~~考试考到原题了。~~

考虑把最开始的最小生成树给找到，然后替换边。每一次会添加一条边，然后形成一个环，同样的，对于我们添加的这一条边，能够影响的也只有当前这一个环。

对于树边（从一开始就存在在最小生成树里的边），如果其不是所构成环上的除开其它树边的最小边了，就会被另外一条非树边所代替；对于非树边，如果这条边比环上所有树边的权值都要大了，就不可能成为生成树的边。

所以考虑树剖维护边权，对于树边，在边上赋上权值后让非树边去查询，得到非树边答案，对于非树边，在路径上进行 `checkMin` 操作，然后让树边去查询即可。

``` c++

#include<bits/stdc++.h>
#define re register
typedef long long ll;
typedef long double ld;
template<class T>
inline void read(T &x)
{
    x=0;
    char ch=getchar(),t=0;
    while(ch<'0'||ch>'9') t|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(t) x=-x;
}
template<class T,class ...Arc>
inline void read(T &x,Arc &...arc){ read(x),read(arc...); }
template<class T>
inline void write(T x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<>
inline void write(bool x){ putchar(x?'1':'0'); }
template<>
inline void write(char c){ putchar(c); }
template<>
inline void write(char *s){ while(*s!='\0') putchar(*s++); }
template<>
inline void write(const char *s){ while(*s!='\0') putchar(*s++); }
template<class T,class ...Arc>
inline void write(T x,Arc ...arc){ write(x),write(arc...); }
template<class T>
inline bool checkMax(T &x,T y){ return x<y?x=y,1:0; }
template<class T>
inline bool checkMin(T &x,T y){ return x>y?x=y,1:0; }
template<class T>
inline T abs(T x){ return x>0?x:-x; }
const int MAXN=1e6+10;
const ll INF=1ll<<60;
struct Node
{ int x,y,id;ll val; }Ed[MAXN];
struct G
{ int next,to;ll val; }Edge[MAXN<<1];
int Head[MAXN],Total;
bool Vis[MAXN];
int N,M,Cnt,Pos[MAXN];
ll ans[MAXN];
int Rt[MAXN],Dep[MAXN],Fa[MAXN],Dfn[MAXN],Top[MAXN],Son[MAXN],Siz[MAXN];
inline void addEdge(int u,int v,ll w)
{
    Edge[++Total]=(G){Head[u],v,w};Head[u]=Total;
    Edge[++Total]=(G){Head[v],u,w};Head[v]=Total;
}
void dfsTree(int x,int last)
{
    Fa[x]=last,Dep[x]=Dep[last]+1,Siz[x]=1;
    for(int e=Head[x],v;e;e=Edge[e].next)
    {
        if((v=Edge[e].to)==last) continue;
        dfsTree(v,x);
        Siz[x]+=Siz[v];
        if(!Son[x]||Siz[v]>Siz[Son[x]]) Son[x]=v;
    }
}
void dfsChain(int x,int topf)
{
    Top[x]=topf,Dfn[x]=++Cnt;
    if(!Son[x]) return ;
    dfsChain(Son[x],topf);
    for(int e=Head[x],v;e;e=Edge[e].next)
    {
        if((v=Edge[e].to)==Fa[x]||v==Son[x]) continue;
        dfsChain(v,v);
    }
}
inline bool cmp(const Node &x,const Node &y){ return x.val<y.val; }
inline int getRt(int x)
{ return Rt[x]==x?x:Rt[x]=getRt(Rt[x]); }
#define ls (p<<1)
#define rs (p<<1|1)
struct Seg
{
    int l,r;
    ll val,tag,mx,sec;
}Tr[MAXN<<2];
inline void pushUp(int p)
{
    if(Tr[ls].mx==INF&&Tr[rs].mx==INF)
    {
        Tr[p].mx=INF,Tr[p].sec=-INF;
        return ;
    }
    if(checkMax(Tr[p].mx,Tr[ls].mx)) Tr[p].sec=std::max(Tr[ls].sec,Tr[rs].mx);
    if(checkMax(Tr[p].mx,Tr[rs].mx)) Tr[p].sec=std::max(Tr[rs].sec,Tr[ls].mx);
}
inline void pushDown(int p)
{
    if(Tr[p].tag==INF) return ;
    if(checkMin(Tr[ls].mx,Tr[p].tag)) checkMin(Tr[ls].tag,Tr[p].tag);
    if(checkMin(Tr[rs].mx,Tr[p].tag)) checkMin(Tr[rs].tag,Tr[p].tag);
    Tr[p].tag=INF;
    return ;
}
void build(int p,int l,int r)
{
    Tr[p].l=l,Tr[p].r=r,Tr[p].tag=Tr[p].mx=INF;
    Tr[p].sec=-INF;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
}
void modifyX(int p,int x,ll v)
{
    if(Tr[p].l==Tr[p].r) return Tr[p].val+=v,void();
    int mid=(Tr[p].l+Tr[p].r)>>1;
    x<=mid?modifyX(ls,x,v):modifyX(rs,x,v);
    Tr[p].val=std::max(Tr[ls].val,Tr[rs].val);
}
ll queryMax(int p,int l,int r)
{
    if(Tr[p].l==l&&Tr[p].r==r) return Tr[p].val;
    int mid=(Tr[p].l+Tr[p].r)>>1;
    if(r<=mid) return queryMax(ls,l,r);
    else if(l>mid) return queryMax(rs,l,r);
    else return std::max(queryMax(ls,l,mid),queryMax(rs,mid+1,r));
}
void modifyMin(int p,int l,int r,ll v)
{
    if(Tr[p].mx<=v) return ;
    if(l<=Tr[p].l&&Tr[p].r<=r)
        if(Tr[p].sec<=v)
        {
            Tr[p].mx=v,checkMin(Tr[p].tag,v);
            return ;
        }
    pushDown(p);
    int mid=(Tr[p].l+Tr[p].r)>>1;
    if(l<=mid) modifyMin(ls,l,std::min(r,mid),v);
    if(mid<r) modifyMin(rs,std::max(l,mid+1),r,v);
    pushUp(p);
}
ll querySec(int p,int x)
{
    if(Tr[p].l==Tr[p].r) return Tr[p].mx;
    pushDown(p);
    int mid=(Tr[p].l+Tr[p].r)>>1;
    return x<=mid?querySec(ls,x):querySec(rs,x);
}
inline ll Path(int x,int y,ll v)
{
    if(!x||!y) return 0;
    ll res=0;
    while(Top[x]!=Top[y])
    {
        if(Dep[Top[x]]<Dep[Top[y]]) std::swap(x,y);
        checkMax(res,queryMax(1,Dfn[Top[x]],Dfn[x]));
        modifyMin(1,Dfn[Top[x]],Dfn[x],v);
        x=Fa[Top[x]];
    }
    if(Dep[x]>Dep[y]) std::swap(x,y);
    if(x==y) return res;
    checkMax(res,queryMax(1,Dfn[Son[x]],Dfn[y]));
    modifyMin(1,Dfn[Son[x]],Dfn[y],v);
    return res;
}
int main()
{
    // freopen("easy.in","r",stdin);
    // freopen("easy.out","w",stdout);
    read(N,M);
    for(int i=1;i<=M;++i) read(Ed[i].x,Ed[i].y,Ed[i].val),Ed[i].id=i;
    std::sort(Ed+1,Ed+M+1,cmp);
    for(int i=1;i<=N;++i) Rt[i]=i;
    int res=0;
    for(int i=1;i<=M;++i)
    {
        int p=getRt(Ed[i].x),q=getRt(Ed[i].y);
        if(p!=q)
        {
            Rt[q]=p;
            Vis[i]=1;++res;
            addEdge(Ed[i].x,Ed[i].y,Ed[i].val);
        }
        if(res==N-1) break;
    }
    dfsTree(1,0),dfsChain(1,1);
    build(1,1,N);
    for(int i=1;i<=M;++i) if(Vis[i])
    {
        if(Fa[Ed[i].x]==Ed[i].y) modifyX(1,Dfn[Ed[i].x],Ed[i].val),Pos[i]=Ed[i].x;
        else modifyX(1,Dfn[Ed[i].y],Ed[i].val),Pos[i]=Ed[i].y;
    }
    for(int i=1;i<=M;++i) if(!Vis[i]) ans[Ed[i].id]=Path(Ed[i].x,Ed[i].y,Ed[i].val);
    for(int i=1;i<=M;++i) if(Vis[i]) ans[Ed[i].id]=querySec(1,Dfn[Pos[i]]);
    for(int i=1;i<=M;++i) write(std::min(ans[i],(ll)1e9),'\n');
    return 0;
}
/*
 
*/

```
代码过不了，要改一下输出（~~懒得改了~~）。

这个是 $\mathcal O(n\log^2 n)$ 的写法，好像有一支 $\log$ 的，排序后用并查集维护，不太好想。把每个非树边排了序后，那当前非树边所能做贡献的边即是当前其他没有被影响到的树边（显然）。那么说我们就可以用并查集来维护这个东西，$f_i$ 表示 $i$ 这条边上面第一个没有被覆盖的边在哪里，每次修改就只用用并查集跳一下就可以了。由于每一个边只会覆盖 $1$ 次，因此时间复杂度就是 $\mathcal O(m\alpha (m))$ 跑得超快。

---

## 作者：fade_away (赞：0)

我有一个很妙（ cao ）的思路，它有三只 $log$ 。。。

大概是我们把边按照权值排序，然后对于一个询问 $(u,v)$ ，我们可以二分答案 $x$ ，找到最小的 $x$ 满足把边权 $\leq x$ 但不是 $(u,v)$ 的边加入后， $(u,v)$ 之间不成环，答案就是 $x_{min}-1$ 。

一个一个询问做太慢了，于是我们考虑整体二分+并查集维护， ```solve(V,l,r)``` 表示 $V$ 中的询问的答案在 $(l,r)$ 中，维护的时候我们保证 $(1,l-1)$ 的边在并查集里，这样可以保证转移时的修改个数是 $O(r-l+1)+O(V.size())$ 级别的。

剩下的就是如何快速对于一个边的前缀 Mid 去掉 $(u,v)$ 这条边，再判断 $(u,v)$ 是否连通。这个可以用缺一背包的思想，再上一个分治解决。

于是我们得到了一个总时间复杂度为 $O(n\log^3 n)$ 的整体二分套分治套并查集做法。它只用到了答案的二分性，没考虑其他性质。~~因此这个做法思想naive，实现简单，是一个不可多得的好做法！~~

## Code
```cpp
PR stk[MAXN * 20];
vector<int> V;
int f[MAXN], Ans[MAXN], flag[MAXN], c[MAXN], cnt[MAXN], top = 0, n, m;
struct Enode{ int u, v, c, id; } E[MAXN];

int find(int x) { return f[x] == x ? f[x] : find(f[x]); }
void add(int x) {
	int u = find(E[x].u), v = find(E[x].v);
	if (u == v) { stk[++ top] = MP(-1, -1); return; }
	if (cnt[u] > cnt[v]) swap(u, v);
	f[u] = v, cnt[v] += cnt[u], stk[++ top] = MP(u, v);
}
void und() {
	if (stk[top].fi != -1) cnt[stk[top].se] -= cnt[stk[top].fi], f[stk[top].fi] = stk[top].fi;
	-- top;
}
void Solve(vector<int> &V, int l, int r, int t) {
	if (l == r) {
		c[V[l]] = (find(E[V[l]].u) == find(E[V[l]].v));
		return;
	}
	int mid = (l + r) >> 1;

	for (int i = mid + 1; i <= r ; ++ i) if (V[i] <= t) add(V[i]);
	Solve(V, l, mid, t);
	for (int i = mid + 1; i <= r ; ++ i) if (V[i] <= t) und();

	for (int i = l; i <= mid ; ++ i) if (V[i] <= t) add(V[i]);
	Solve(V, mid + 1, r, t);
	for (int i = l; i <= mid ; ++ i) if (V[i] <= t) und();
}
void solve(vector<int> &V, int L, int R) {
	if (!V.size()) return;

	if (L == R) {
		for (auto v : V) Ans[E[v].id] = E[L].c - 1;
		return;
	}

	int Mid = (L + R) >> 1;
	for (int i = L; i <= Mid ; ++ i) 
		if (!flag[i]) add(i);
	Solve(V, 0, (int)V.size() - 1, Mid);
	for (int i = L; i <= Mid ; ++ i) 
		if (!flag[i]) und();

	vector<int> lv, rv;
	lv.clear(), rv.clear();
	for (auto v : V) 
		if (c[v]) lv.PB(v); 
		else rv.PB(v);

	for (auto v : rv) {
		flag[v] = 0;
		if (v < L) add(v); 
	}
	solve(lv, L, Mid);
	for (auto v : rv) {
		flag[v] = 1;
		if (v < L) und();
	}

	for (auto v : lv) {
		flag[v] = 0;
		if (v <= Mid) add(v);
	}
	for (int i = L; i <= Mid + 1 ; ++ i) if (!flag[i]) add(i);
	solve(rv, Mid + 1, R);
	for (int i = L; i <= Mid + 1 ; ++ i) if (!flag[i]) und();
	for (auto v : lv) {
		flag[v] = 1;
		if (v <= Mid) und();
	}
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	read(n), read(m);
	for (int i = 1, u, v, c; i <= m ; ++ i) read(u), read(v), read(c), E[i] = (Enode){u, v, c, i};
	sort(E + 1, E + m + 1, [&](Enode a, Enode b) { return a.c < b.c; });
	for (int i = 1; i <= n ; ++ i) f[i] = i, cnt[i] = 1;
	for (int i = 1; i <= m ; ++ i) flag[i] = 1, V.PB(i);
	solve(V, 1, m + 1);
	for (int i = 1; i <= m ; ++ i) print(Ans[i]), putc(' ');
	return 0;
}
```


---

