# [USACO18OPEN] Disruption P

## 题目描述

Farmer John 自豪于他所经营的交通发达的农场。这个农场由 $N$ 块牧场（$2 \leq N \leq 50,000$）组成，$N-1$ 条双向道路将它们连接起来，每条道路的长度均为 $1$ 单位。Farmer John 注意到，从任何一块牧场到另一块牧场，都能通过一组合适的道路到达。

尽管 FJ 的农场现在是连通的，他担心如果有一条道路被阻断会发生什么，因为这会将农场分为两个不相交的牧场集合，奶牛们只能在每个集合内移动而不能在集合间移动。于是 FJ 又建造了 $M$ 条额外的双向道路（$1 \leq M \leq 50,000$），每条道路的长度都是一个至多为 $10^9$ 的正整数。奶牛们仍然可以使用原有的道路进行移动，除非其中的某些被阻断。

如果某条原有的道路被阻断，农场就会被分为两块不相交的区域，那么 FJ 会从他的额外修建的道路中选择一条能够重建这两块区域连通性的道路，取代原来的那条，从而使奶牛们又可以从任何一块牧场去往另一块牧场。

对于农场上每一条原有的道路，帮助 FJ 选出最短的替代道路。

## 说明/提示

供题：Brian Dean

## 样例 #1

### 输入

```
6 3
1 2
1 3
4 1
4 5
6 5
2 3 7
3 6 8
6 4 5```

### 输出

```
7
7
8
5
5```

# 题解

## 作者：ASSWECAN (赞：35)

其实这题也可以不用树剖，先把新加的道路按照代价从小到大排个序，这样每次往上走的时候原来访问过的就可以直接跳过了（因为答案不会变得更优），这样直接就可以用类似并查集的方法就行了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int ans[50010];
int n,m;
int par[50010][17];
int dep[50010];
int po[50010];
int to[50010];
vector<pair<int,int> >G[50010];
pair<int,pair<int,int> >roads[50010];
int getto(int x)
{
	if(to[x]==x)return x;
	return to[x]=getto(to[x]);
}
void dfs(int x,int p)
{
	for(int i=0;i<G[x].size();i++)
	{
		int y=G[x][i].first,id=G[x][i].second;
		if(y==p)continue;
		po[id]=y;
		par[y][0]=x;
		dep[y]=dep[x]+1;
		dfs(y,x);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=16;i>=0;i--)if(dep[par[x][i]]>=dep[y])x=par[x][i];
	if(x==y)return x;
	for(int i=16;i>=0;i--)if(par[x][i]!=par[y][i])x=par[x][i],y=par[y][i];
	return par[x][0];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(make_pair(y,i));
		G[y].push_back(make_pair(x,i)); 
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		roads[i]=make_pair(z,make_pair(x,y));
	}
	dep[0]=-1;
	dfs(1,0);
	for(int i=1;i<=16;i++)
	{
		for(int j=1;j<=n;j++)par[j][i]=par[par[j][i-1]][i-1];
	}
	for(int i=1;i<=n;i++)to[i]=i;
	for(int i=1;i<=n;i++)ans[i]=-1;
	sort(roads+1,roads+m+1);
	for(int i=1;i<=m;i++)
	{
		int v=roads[i].first;
		int x=roads[i].second.first,y=roads[i].second.second;
		int xy=lca(x,y);
		for(x=getto(x);dep[x]>dep[xy];x=getto(par[x][0]))
		{
			ans[x]=v;
			to[x]=par[x][0];
		}
		for(y=getto(y);dep[y]>dep[xy];y=getto(par[y][0]))
		{
			ans[y]=v;
			to[y]=par[y][0];
		}
	}
	for(int i=1;i<n;i++)printf("%d\n",ans[po[i]]);
	return 0;
}
```

---

## 作者：Su_Zipei (赞：12)

这种题是一种比较套路的题目，考虑正向去思考，发现不是很好搞，因为删除每条边之后都要去子树里边寻找可以替代的边，所以正难则反，考虑$m$条边中每条边的贡献。

画一下图即可发现，对于一条连接$<x,y>$的边，它能够更新从$x,y$到$lca$之间的所有边，对边操作不是很好搞所以又用到一个套路，将父边下放到子节点上，然后就有了一个$nlog^2n$的树剖线段树写法，对于这道题来说足够了，但是这样真的是最优的吗？

显然应该不是的，我们发现这样其实会有很多无用的更新，对于每条边来说有用的更新只有一次，就是能够更新到它的权值最小的边，所以我们完全可以按照边的权值进行排序，然后用并查集维护下一次更新的点，所以时间复杂度就是$O(n\times(\text{并查集}))$

```cpp
/*
6 3
1 2
1 3
4 1
4 5
6 5
2 3 7
3 6 8
6 4 5
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e4+10;
struct Edge{
	int to,nxt;
}e[N<<1];
int h[N],idx=1;
void Ins(int a,int b){
	e[++idx].to=b;e[idx].nxt=h[a];h[a]=idx;
}
int f[N];
int find(int x){
	return f[x]==x?x:(f[x]=find(f[x]));
}
struct Node{
	int x,y,w;
	Node(){}
	Node(int a,int b,int c){
		x=a;y=b;w=c;
	}
	bool operator < (const Node&A)const{
		return w<A.w;
	}
}a[N];
int fa[N],dep[N],son[N],len[N],tp[N],edg[N<<1],ans[N];
void dfs1(int u){
	len[u]=1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u])continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		edg[i]=edg[i^1]=v;
		dfs1(v);
		len[u]=max(len[u],len[v]+1);
		if(len[v]>len[son[u]])son[u]=v;
	}
}
void dfs2(int u,int t){
	tp[u]=t;
	if(son[u])dfs2(son[u],t);
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int lca(int x,int y){
	while(tp[x]^tp[y]){
		if(dep[tp[x]]>dep[tp[y]])x=fa[tp[x]];
		else y=fa[tp[y]];
	}
	return dep[x]>dep[y]?y:x;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		Ins(x,y);Ins(y,x);
	}
	dfs1(1);
	dfs2(1,1);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	sort(a+1,a+m+1);
	for(int i=1;i<=n;i++)
		f[i]=i;
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<=m;i++){
		int x=find(a[i].x),y=find(a[i].y);
		int now=dep[lca(a[i].x,a[i].y)];
		while(dep[x]>now){
			ans[x]=a[i].w;
			f[x]=find(fa[x]);
			x=find(x);
		}
		while(dep[y]>now){
			ans[y]=a[i].w;
			f[y]=find(fa[y]);
			y=find(y);
		}
	}
	for(int i=2;i<=idx;i+=2)
		printf("%d\n",ans[edg[i]]);
	return 0;
}

```


---

## 作者：MeowScore (赞：11)

看到是紫题有点害怕，结果想了想发现是板子。

本题解采用树剖套线段树。

题意是给出一棵树和一些带边权的额外边，要求依次回答去掉每一条树边后，若选取一条额外边使得树仍联通，选取边的边权最小是多少。无解输出 `-1`。

我们发现，每次加入一条额外边，假设两端点分别为 `x` 和 `y`，那么**这条边会和原来树上 `x` 和 `y` 之间的链构成一个环**。这个环上任何一条树边被断，断开的两个连通块一定可以通过我们刚加的这条额外边保持联通。而且如果一条树边不在这个环上，那么断了这条树边，这条额外边也无法使树保持联通。这个显然吧。

因此我们可以边转点。在点的时间戳上建立线段树，线段树每片叶子维护“删掉这个点所代表的边后，使树联通需要的最短边的边权”。区间信息都不用合并，因为是单点查询。

这样我们每次读入一条两端点分别为 `x` 和 `y` ，权值为 `k` 的额外边，常规树剖写法，在树上以 `x` 和 `y` 为端点的链上进行和 `k` 取 `min`。


查询的时候先得到这条边对应的点，然后单点查询即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=100010,INF=1000000100;
int n,m;
int head[N],nex[N*2],to[N*2],cnt;
void add(int x,int y){
	cnt++;
	nex[cnt]=head[x];
	to[cnt]=y;
	head[x]=cnt;
}
int fa[N],dep[N],tp[N],sz[N],son[N],tot,dfn[N];
void dfs1(int x,int f){
	fa[x]=f;
	dep[x]=dep[f]+1;
	sz[x]=1;
	int maxn=-1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)
			continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>maxn){
			maxn=sz[y];
			son[x]=y;
		}
	}
}
void dfs2(int x,int top){
	tp[x]=top;
	tot++;
	dfn[x]=tot;
	if(son[x])
		dfs2(son[x],top);
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])
			continue;
		dfs2(y,y);
	}
}
struct ST{
	int minn;
	int tag;
}st[N*4];
struct Edge{
	int x;
	int y;
}g[N];
int res;
inline int min(int x,int y){
	if(x<y)
		return x;
	return y;
}
void push_down(int root,int l,int r){
	int k=st[root].tag;
	st[root].tag=INF;
	st[root*2].minn=min(st[root*2].minn,k);
	st[root*2+1].minn=min(st[root*2+1].minn,k);
	st[root*2].tag=min(st[root*2].tag,k);
	st[root*2+1].tag=min(st[root*2+1].tag,k);
}
void change(int root,int l,int r,int x,int y,int k){
	if(l>=x&&r<=y){
		st[root].minn=min(st[root].minn,k);
		st[root].tag=min(st[root].tag,k);
		return;
	}
	if(l!=r&&st[root].tag!=INF)
		push_down(root,l,r);
	int mid=(l+r)/2;
	if(mid>=x)
		change(root*2,l,mid,x,y,k);
	if(mid+1<=y)
		change(root*2+1,mid+1,r,x,y,k);
}
void ask(int root,int l,int r,int x){
	if(l==r){
		res=st[root].minn;
		return;
	}
	if(l!=r&&st[root].tag!=INF)
		push_down(root,l,r);
	int mid=(l+r)/2;
	if(mid>=x)
		ask(root*2,l,mid,x);
	if(mid+1<=x)
		ask(root*2+1,mid+1,r,x);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		g[i].x=x;
		g[i].y=y;
		add(x,y);
		add(y,x);
	}
	dfs1(1,1);
	dfs2(1,1);
	for(int i=1;i<=n*4;i++)
		st[i].minn=st[i].tag=INF;
	for(int i=1;i<=m;i++){
		int x,y,k;
		cin>>x>>y>>k;
		while(tp[x]!=tp[y]){
			if(dep[tp[x]]<dep[tp[y]])
				swap(x,y);
			change(1,1,n,dfn[tp[x]],dfn[x],k);
			x=fa[tp[x]];
		}
		if(x!=y){
			if(dep[x]>dep[y])
				swap(x,y);
			change(1,1,n,dfn[x]+1,dfn[y],k);
		}
	}
	for(int i=1;i<n;i++){
		res=INF;
		ask(1,1,n,max(dfn[g[i].x],dfn[g[i].y]));
		if(res==INF)
			printf("-1\n");
		else
			printf("%d\n",res);
	}
	return 0;
}

 
```

---

## 作者：wenjing233 (赞：8)

既然没有有图的题解，那我就过来补个图加思路了
### 画图
假设我们有一颗树
![](https://i.loli.net/2019/03/06/5c7f0e0adb762.png)
现在多了一条额外道路
![](https://i.loli.net/2019/03/06/5c7f0e497d85c.png)
则当且仅当额外道路所连的两个点不在一个联通块内时，这条边才有贡献，我们将能够将这两个点分开的边标记出来
![](https://i.loli.net/2019/03/06/5c7f0d7dd41c9.png)
发现这些边构成的路径就是两点之间的最短简单路径，直接用树剖维护区间极值即可
（不要问我前两张图为什么那么怪，因为我是由结果改出过程（简称懒））
### 证明
两点不在同一个联通快内，即两点之间不存在简单路径，因为这是一棵树，所以两点之间的简单路径是唯一的，只有切断简单路径才能使两个点不在一个联通块内，证毕
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=50009;
int head[N],to[N<<1],nt[N<<1];
struct gzw
{
    int st,ed,val;
}way[N];
int n,m,bh,totid;
int top[N],siz[N],mxson[N],fa[N],dep[N],id[N];
int u[N],v[N];
int val[N<<4],tag[N<<4];
bool rnk(gzw a,gzw b)
{
    return a.val>b.val;	
}
void add(int u,int v)
{
    bh++;
    nt[bh]=head[u];
    head[u]=bh;
    to[bh]=v;
}
void dfs1(int now,int fath,int depth)
{
    fa[now]=fath;
    dep[now]=depth;
    siz[now]=1;
    for(int i=head[now],mx=0;i;i=nt[i])
    {
        if(to[i]!=fath)
        {
            dfs1(to[i],now,depth+1);
            siz[now]+=siz[to[i]];
            if(siz[to[i]]>mx) mx=siz[to[i]],mxson[now]=to[i];	
        }
    }
}
void dfs2(int now,int tp)
{
    id[now]=++totid;
    top[now]=tp;
    if(mxson[now])
    {
        dfs2(mxson[now],tp);
    }
    for(int i=head[now];i;i=nt[i])
    {
        if(to[i]!=fa[now]&&to[i]!=mxson[now])
        {
            //cout<<now<<" "<<to[i]<<endl;
            dfs2(to[i],to[i]);
        }
    }
}
void upd (int &x,int k)
{
    x=(x==-1?k:min(x,k));	
}
void pushdown(int now)
{
    if(tag[now]!=-1)
    {
        upd(val[now],tag[now]);
        upd(tag[now<<1],tag[now]);
        upd(tag[now<<1|1],tag[now]);
        tag[now]=-1;
    }
}
int query(int now,int l,int r,int pos)
{
    //cout<<l<<" "<<r<<" "<<pos<<endl;
    pushdown(now);
    if(l==pos&&r==pos)
    {
        return val[now];
    }
    int mid=(l+r)>>1;
    if(mid>=pos) query(now<<1,l,mid,pos);
    else query(now<<1|1,mid+1,r,pos);
}
void change(int now,int l,int r,int ql,int qr,int k)
{
    pushdown(now);
    if(ql<=l&&qr>=r)
    {
        //cout<<now<<" "<<ql<<" "<<qr<<" "<<l<<" "<<r<<" 666"<<endl;
        upd(val[now],k);
        upd(tag[now<<1],k);
        upd(tag[now<<1|1],k);
        return;
    }
    int mid=(l+r)>>1;
    if(mid>=qr) change(now<<1,l,mid,ql,qr,k);
    else if(mid<ql) change(now<<1|1,mid+1,r,ql,qr,k);
    else change(now<<1,l,mid,ql,qr,k),change(now<<1|1,mid+1,r,ql,qr,k);
    return;
}
void C(int x,int y,int k)
{
    int tx=top[x],ty=top[y];
    while(tx!=ty)
    {
        if(dep[tx]<dep[ty]) swap(x,y),swap(tx,ty);
        //cout<<id[tx]<<" "<<id[x]<<" "<<k<<" 233"<<endl;
        change(1,1,n,id[tx],id[x],k);
        x=fa[tx],tx=top[x];
    }
    if(x!=y) 
    {
        if(id[x]>id[y]) swap(x,y);
        //cout<<id[x]+1<<" "<<id[y]<<" "<<k<<" 233"<<endl;
        change(1,1,n,id[x]+1,id[y],k);//???
    }
}
void bl(int now,int l,int r)
{
    pushdown(now);
    //cout<<now<<" "<<l<<" "<<r<<" "<<val[now]<<endl;
    if(l>=r) return;	
    bl(now<<1,l,(l+r)>>1);
    bl(now<<1|1,((l+r)>>1)+1,r);
}
int main() 
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<n;i++)
    {
    	scanf("%d %d",&u[i],&v[i]);
    	add(u[i],v[i]);
    	add(v[i],u[i]);
    }
    for(int i=1;i<=m;i++)
    {
    	scanf("%d %d %d",&way[i].st,&way[i].ed,&way[i].val);	
    }
    sort(way+1,way+m+1,rnk);
    dfs1(1,0,1);
    dfs2(1,1);
    
    memset(val,-1,sizeof(val));
    memset(tag,-1,sizeof(tag));
    for(int i=1;i<=m;i++)
    {
    	C(way[i].st,way[i].ed,way[i].val);	
    	//bl(1,1,n);
    	//cout<<endl;
    }
    for(int i=1,ls;i<n;i++)
    {
    	//cout<<(dep[u[i]]>dep[v[i]]?id[u[i]]:id[v[i]])<<" "<<666<<endl;
        ls=query(1,1,n,dep[u[i]]>dep[v[i]]?id[u[i]]:id[v[i]]);
    	printf("%d\n",ls);
    }
}
/*

*/
```

---

## 作者：JK_LOVER (赞：3)

### 题意：给你 $n$ 个节点的树，再给你 $m$ 条边，求换上这条边后，在保证连通性时，可以删去哪些边。最后问每条边可以改变的值中最小的值。

#### 先画图分析(手玩样例)：

#### 这是加边之后的树的样子(红边是新加的)

![](https://cdn.luogu.com.cn/upload/image_hosting/mtadw03w.png)

#### 这是边可以选择的最小值
![](https://cdn.luogu.com.cn/upload/image_hosting/pvl90ozf.png)
#### 其实可以很好发现：

- 加上一条边之后，可以删去的边是与这条新加的边构成的环中的边。
- 原树的形态不变，当一条边在被多条边构成的环中时，可以选择的最小值是新加边的最小值
- 树上对边赋值，已经明示了答案 -> 树(重)链剖分

如果用线段树维护的树链剖分时间复杂度为 $O(nlog^2n)$
这时候其实您已经可以 $AC$ 了。

### 但是使用LCT可以做到 $O(nlogn)$

通过动态维护路径，一次询问做到 $O(logn)$

然而还有一个问题LCT只能维护点值，这时候我们可将边拆成两端点中间的一个新点

#### 话说LCT的码量比起树链剖分友好多了，若不知道LCT的这里有一个很好的[博客](https://www.cnblogs.com/flashhu/p/8324551.html)

代码就比较简单了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 551000
#define inf 0x3f3f3f3f
int c[N][2],ad[N],f[N],v[N],to[N],from[N];
int n,m;
bool r[N];
void pushr(int x){swap(c[x][0],c[x][1]);r[x]^=1;}
void pusha(int x,int k){v[x] = min(k,v[x]);ad[x] = min(k,ad[x]);}
bool isroot(int x){return c[f[x]][1] == x||c[f[x]][0] == x;}
void pushdown(int x)
{
	if(ad[x]!=inf){pusha(c[x][1],ad[x]);pusha(c[x][0],ad[x]);ad[x] = inf;}
	if(r[x])
	{
		if(c[x][1]) pushr(c[x][1]);
		if(c[x][0]) pushr(c[x][0]);
		r[x] = 0;
	}
}
void rotate(int x)
{
	int y = f[x],z = f[y],k = c[y][1] == x,w = c[x][1^k];
	if(isroot(y)) c[z][c[z][1] == y] = x;
	c[x][1^k] = y;
	c[y][k] = w;
	if(w)f[w] = y;
	f[y] = x;
	f[x] = z;
}
void push(int x)
{
	if(isroot(x)) push(f[x]);
	pushdown(x);
}
void splay(int x)
{
	int y = x,z = 0;
	push(x);
	while(isroot(x))
	{
		y = f[x];z = f[y];
		if(isroot(y))
		{
			rotate((c[y][1] == x)^(c[z][1] == y)?x:y);
		}
		rotate(x);
	}
}
void access(int x){
	for(int y = 0;x;x = f[y = x])
	splay(x),c[x][1] = y;
}
void makeroot(int x){access(x);splay(x);pushr(x);}
void split(int x,int y){makeroot(x);access(y);splay(y);}
void link(int x,int y){makeroot(x);f[x] = y;}
struct E{
	int a,b,w;
}e;

int main()
{
	memset(ad,inf,sizeof(ad));
	memset(v,inf,sizeof(v));
	cin>>n>>m;
	for(int i = 1;i < n;i++){
	int a,b;
	cin>>a>>b;
	to[i] = a;
	from[i] = b;
	link(i+n,a);
	link(i+n,b);
	}
	for(int i = 1;i <= m;i++)
	{
		cin>>e.a>>e.b>>e.w;
		split(e.a,e.b);
		pusha(e.b,e.w);
	}
	for(int i = 1;i < n;i++)
	{
		split(to[i],from[i]);
		if(v[i+n]==inf)cout<<"-1"<<endl;
		else cout<<v[i+n]<<endl;
	}
}
```


---

## 作者：ETHANK (赞：2)

**题目大意：**

给一棵 $N$ 个点的树和 $M$ 条特殊边，特殊边有边权。希望求出去掉树上任意一条边后，加一条特殊边使图连通的最小代价。

数据范围：$2\le N\le 5\times 10^4,M\le 5\times10^4$ .

> 知识储备：并查集，倍增LCA

> 题目难度：省选/USACO Platinum

**解析：**

*（这道题稍为自然的想法是考虑特殊边能给哪些边的答案带来贡献，并用树剖+线段树维护最小值，这种做法的复杂度是 $O(N\log^2 N)$ 的，可以通过本题。 这里给出一个更为精妙的离线做法。）*

对特殊边按边权升序排序。考虑特殊边 $(u,v)$ 能成为哪些树上边的答案。去掉一条边加上 $(u,v)$ 后原图仍为树，不难发现去掉的这条边必须在 $[u,v]$ 的树上路径上。其次，当这条树边的答案已经确定后，不需要再考虑这条边断开的情况，于是可以用并查集合并两个端点。

实现比较简单，预处理倍增 LCA ，从小到大遍历特殊边，对树上边更新答案即可。

时间复杂度：$O(M\alpha(n))$ .

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
int n,m,fa[N][20],Log[N],pos[N],dep[N];
int dsu[N],ans[N];
int find(int x){return x==dsu[x]?x:dsu[x]=find(dsu[x]);}
struct Edge{
    int u,v,w;
    bool operator <(const Edge a)const{
        return w<a.w;
    }
}e[N];
vector <pii> G[N];
void dfs(int u,int f){
    dep[u]=dep[f]+1,fa[u][0]=f;
    for(auto x:G[u]){
        if(x.fi==f)continue;
        pos[x.se]=x.fi;
        dfs(x.fi,u);
    }
}
int lca(int x,int y) {
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y]){
	    x=fa[x][Log[dep[x]-dep[y]]];
	}
    if(x==y)return x;
    for(int i=Log[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
void init(){
    Log[0]=-1;
    rep(i,1,n){
        Log[i]=Log[i>>1]+1;
        ans[i]=-1;
        dsu[i]=i;
    }
    rep(i,1,16){
        rep(j,1,n)fa[j][i]=fa[fa[j][i-1]][i-1];
    }
    sort(e+1,e+m+1);
}
int main(){
    //freopen("disrupt.in","r",stdin);
    //freopen("disrupt.out","w",stdout);
    n=read(),m=read();
    rep(i,1,n-1){
        int u=read(),v=read();
        G[u].pb({v,i}),G[v].pb({u,i});
    }
    dfs(1,0);
    rep(i,1,m){
        e[i]={read(),read(),read()};
    }
    init();
    rep(i,1,m){
        int u=e[i].u,v=e[i].v,w=e[i].w;
        int L=lca(u,v);
        for(u=find(u);dep[u]>dep[L];u=find(fa[u][0])){
            ans[u]=w,dsu[u]=fa[u][0];
        }
        for(v=find(v);dep[v]>dep[L];v=find(fa[v][0])){
            ans[v]=w,dsu[v]=fa[v][0];
        }
    }
    rep(i,1,n-1)printf("%d\n",ans[pos[i]]);
    return 0;
}
```



---

## 作者：Bruteforces (赞：2)

除了传统的树剖+线段树做法以外，这里再提供一种树剖+珂朵莉树的做法。（珂朵莉真是太可爱辣）

我们把所有额外的边按照边权从大到小排序，然后对于每一条边，我们强行将这条边连接的两点路径上，除了LCA以外的所有点的答案修改为这条边的边权。嗯，区间推平，珂朵莉树基本操作，而且只有这一个操作。

这种做法的时间复杂度应该是 $O(nlog^2n)$ 的，和树剖+线段树一样。不过实际运行速度貌似不尽人意（本蒟蒻线段树做法638ms,珂朵莉树1345ms）可能是set常数太大了？

以下是代码：
```
#include <bits/stdc++.h>
#define LL long long
#define PII pair<int,int>
#define IT set<node>::iterator
using namespace std;

const int N=1e5+50;
int n,m,to[N<<1],ne[N<<1],head[N],cnt=0;
PII Edge[N];
int fa[N],dep[N],siz[N],wson[N],dfn[N],id[N],tot=0,top[N];

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	for(; !isdigit(ch); ch=getchar())if(ch=='-')f=-1;
	for(; isdigit(ch); ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}

namespace Prework {  //建树，树剖
	inline void Addedge(int x,int y) {
		to[++cnt]=y;ne[cnt]=head[x];head[x]=cnt;
	}
	void DFS_first(int x,int f) {
		fa[x]=f;dep[x]=dep[f]+1;siz[x]=1;
		for(int i=head[x]; i; i=ne[i])if(to[i]!=f) {
			DFS_first(to[i],x);
			siz[x]+=siz[to[i]];
			if(siz[to[i]]>siz[wson[x]])wson[x]=to[i];
		}
	}
	void DFS_second(int x,int tp) {
		dfn[x]=++tot;id[tot]=x;top[x]=tp;
		if(wson[x])DFS_second(wson[x],tp);
		for(int i=head[x]; i; i=ne[i])if(to[i]!=fa[x] && to[i]!=wson[x]) {
			DFS_second(to[i],to[i]);
		}
	}
	void Solve() {
		n=read(),m=read();
		for(int i=1; i<n; ++i) {
			Edge[i].first=read(),Edge[i].second=read();
			Addedge(Edge[i].first,Edge[i].second);
			Addedge(Edge[i].second,Edge[i].first);
		}
		DFS_first(1,0);DFS_second(1,1);
	}
}
namespace Mian{
	struct MoreEdge{
		int x,y,w;
		bool operator < (const MoreEdge &x)const {
			return w>x.w;
		}
	}E[N];
	struct node{
		int L,R;
		mutable int v;
		node(int _L,int _R=-1,int _v=0) : L(_L),R(_R),v(_v){}
		bool operator < (const node &x)const {
			return L<x.L;
		}
	};
	set<node> Chtholly;
	int Ans[N];
    //珂朵莉树基本操作
	IT split(int x){
		IT it=Chtholly.lower_bound(node(x));
		if(it!=Chtholly.end() && it->L==x)return it;
		--it;
		int L=it->L,R=it->R,v=it->v;
		Chtholly.erase(it);Chtholly.insert(node(L,x-1,v));
		return Chtholly.insert(node(x,R,v)).first;
	}
	void assign(int L,int R,int v) {
		IT Right=split(R+1),Left=split(L);
		Chtholly.erase(Left,Right);
		Chtholly.insert(node(L,R,v));
	}
	void Cover(int T) {
		int x=E[T].x,y=E[T].y,w=E[T].w;
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]])swap(x,y);
			assign(dfn[top[x]],dfn[x],w);
			x=fa[top[x]];
		}
		if(dep[x]>dep[y])swap(x,y);
		if(x!=y)assign(dfn[x]+1,dfn[y],w);
	}
	void Solve() {
		Chtholly.insert(node(1,n,-1));
		for(int i=1; i<=m; ++i) {
			E[i].x=read(),E[i].y=read(),E[i].w=read();
		}
		sort(E+1,E+m+1);
		for(int i=1;i<=m;++i)Cover(i);
		for(IT it=Chtholly.begin();it!=Chtholly.end();++it){
			for(int i=it->L;i<=it->R;++i)Ans[id[i]]=it->v;
		}
		for(int i=1;i<n;++i){
			int x=(dep[Edge[i].first]<dep[Edge[i].second]?Edge[i].second:Edge[i].first);
			printf("%d\n",Ans[x]);
		}	
	}
}

int main() {
	Prework::Solve();
	Mian::Solve();
	return 0;
}
```

---

## 作者：feicheng (赞：2)

## [$\text{Description}$](https://www.luogu.com.cn/problem/P4374)



给定一颗有 $n$ 个点的树，另给出 $m$ 条有边权的边。求断掉一条边后能使原树联通的最小边权。

## [$\text{Solution}$](https://www.luogu.com.cn/paste/jokul7s8)



非常有意思的一道树剖题目，我们可以画图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/j9oqhatv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

接着我们思考断掉一条边，寻找最小的能使图联通的边（这里建议手模一下），我们会发现：

**只有当被断掉的边连接的两个点在额外边连接的两点的路径上（也就是形成环）时，这条额外边才有贡献**。

举个例子：当断掉 $1-2$ 这条边时，为了保证 $1-2$ 之间联通，我们可以选择边权为 $3$ 的红边，而当断掉 $1-3$ 之间的边时，我们可以选择边权为 $3$ 的红边，也可以选择边权为 $5  $ 的红边（因为 $1-3$ 之间的边和他们都形成了环），而当断掉 $2-5$ 之间的边时，由于没有红边和他们形成环，所以就无解了。

所以这实际上就是一个树剖模板：区间修改求最小 + 区间查询最小值。

时间复杂度：$\Theta(n\log^2n)$（树剖复杂度）

代码在链接里。

---

## 作者：ueettttuj (赞：1)

[题目](https://www.luogu.org/problem/P4374)

[强行安利我的博客](https://www.luogu.org/blog/ueettttujzzr/p4374-usaco18opendisruption)

此题树剖可写。对于每一条新加的边，它与原边构成了一个环，环上的边都可以用该新边替代。设新加的边为$(x,y,z)$，则用树剖维护点$x\sim y$的路径(路径是唯一的)，路径上的每一条边都可以被新边替代。故对于每一条边维护一个可以替代此边的新边的权值最小值$z$，对于每次询问都返回这个最小值即可。

注意：
- 此题是边权。

- $lazy,minn$要取最小值(详见代码)

- $lazy,minn$初始化赋无穷大

贴代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 1000000000000
long long n,m,head[50010],tot,cnt;
struct node{
	long long nex,to;
};
node edge[100010];
struct data2{
	long long xx,yy;
};
data2 edge2[100010];
struct data{
	long long fa,size,son,id,deep,top;
};
data tree[50010];
struct node2{
	long long minn,lazy;
};
node2 tree2[200010];
void add(long long x,long long y){
	edge[++tot].to=y;
	edge[tot].nex=head[x];
	head[x]=tot;
}
void pushup(long long rt){
	tree2[rt].minn=min(tree2[rt*2].minn,tree2[rt*2+1].minn);
}
void pushdown(long long rt){
	tree2[rt*2].lazy=min(tree2[rt*2].lazy,tree2[rt].lazy);
	tree2[rt*2+1].lazy=min(tree2[rt*2+1].lazy,tree2[rt].lazy);//注意取最小值 
	tree2[rt*2].minn=min(tree2[rt*2].minn,tree2[rt].lazy);
	tree2[rt*2+1].minn=min(tree2[rt*2+1].minn,tree2[rt].lazy);
	tree2[rt].lazy=maxn;
}
void changed(long long rt,long long l,long long r,long long x,long long y,long long z){ //线段树维护区间 
	if(x<=l && y>=r){
		tree2[rt].lazy=min(tree2[rt].lazy,z);
		tree2[rt].minn=min(tree2[rt].minn,z); //注意要取最小值 
		return ;
	}
	pushdown(rt);
	long long mid=(l+r)/2;
	if(x<=mid) changed(rt*2,l,mid,x,y,z);
	if(y>mid) changed(rt*2+1,mid+1,r,x,y,z);
	pushup(rt);
}
long long ask(long long rt,long long l,long long r,long long x,long long y){
	if(x<=l && y>=r){
		return tree2[rt].minn;
	}
	pushdown(rt);
	long long mid=(l+r)/2;
	long long anss=maxn;
	if(x<=mid) anss=min(anss,ask(rt*2,l,mid,x,y));
	if(y>mid) anss=min(anss,ask(rt*2+1,mid+1,r,x,y));
	return anss;
}
void dfs1(long long rt,long long father,long long depp){ //树剖操作 
	tree[rt].fa=father;
	tree[rt].deep=depp;
	tree[rt].size=1;
	long long maxson=-1;
	for(long long i=head[rt];i;i=edge[i].nex){
		long long y;
		y=edge[i].to;
		if(y==father) continue ;
		dfs1(y,rt,depp+1);
		tree[rt].size+=tree[y].size;
		if(maxson<tree[y].size){
			maxson=tree[y].size;
			tree[rt].son=y;
		}
	}
}
void dfs2(long long rt,long long topp){
	tree[rt].top=topp;
	tree[rt].id=++cnt;
	if(tree[rt].son==0) return ;
	dfs2(tree[rt].son,topp);
	for(long long i=head[rt];i;i=edge[i].nex){
		long long y;
		y=edge[i].to;
		if(y==tree[rt].fa || y==tree[rt].son) continue ;
		dfs2(y,y);
	}
}
void update(long long x,long long y,long long z){//更新操作 
	while(tree[x].top!=tree[y].top){
		if(tree[tree[x].top].deep<tree[tree[y].top].deep) swap(x,y);
		changed(1,1,n,tree[tree[x].top].id,tree[x].id,z);
		x=tree[tree[x].top].fa;
	}
	if(tree[x].id>tree[y].id) swap(x,y);
	changed(1,1,n,tree[x].id+1,tree[y].id,z);
}
long long updateask(long long x,long long y){  //查询 
	long long anss=maxn;
	while(tree[x].top!=tree[y].top){
		if(tree[tree[x].top].deep<tree[tree[y].top].deep) swap(x,y);
		anss=min(anss,ask(1,1,n,tree[tree[x].top].id,tree[x].id));
		x=tree[tree[x].top].fa;
	}
	if(tree[x].id>tree[y].id) swap(x,y);
	anss=min(anss,ask(1,1,n,tree[x].id+1,tree[y].id));
	return anss;
}
int main(){
	scanf("%lld %lld",&n,&m);
	tot=1;
	for(long long i=1;i<=4*n;i++){
		tree2[i].minn=maxn;
		tree2[i].lazy=maxn;
	}
	long long b,c;
	for(long long i=1;i<n;i++){
		scanf("%lld %lld",&b,&c);
		add(b,c);
		add(c,b);
		edge2[i].xx=b;
		edge2[i].yy=c;  //记下询问 
	}
	dfs1(1,-1,1);
	dfs2(1,-1);
	long long d;
	for(long long i=1;i<=m;i++){
		scanf("%lld %lld %lld",&b,&c,&d);
		update(b,c,d);      //更新可以替代此边的新边边权最小值 
	}
	for(long long i=1;i<n;i++){ //枚举询问 
		long long kk;
		kk=updateask(edge2[i].xx,edge2[i].yy);
		if(kk!=maxn) printf("%lld\n",kk);
		else printf("-1\n");
	}
	return 0;
}
```



---

## 作者：寒鸽儿 (赞：1)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-p4374)  
### 使用树链剖分模板即可解决本题。
模型构造：  
对于一条新增的路,由于原图是一棵树,因而增加路后成一个简单环。这条路就可以替代环上的任意一条原有路径,换言之,环上原有的路径可以被替代。  
因而本问题涉及到在树上的两点的简单路径上的统计(最小值)操作,考虑套用树剖模板解题。  
细节分析:  
1.本题是对边的统计，很容易想到树剖边转点,即把每一条边映射到它所连的深度较大的那个点(就是孩子结点对应从它的父亲结点伸向它的边)。  
2.本题是按照所给边的先后顺序输出,它与我们结点对应边的关系可以在第一次dfs(建树)时统计,具体见代码dfs1中的idn数组的维护。  
3.本题实际上只要维护单点最小值即可,我的代码线段树有点写多了。

给出AC代码(总用时1352ms,O2 776ms巨慢)
```cpp
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 50010;
const int inf = 0x3f3f3f3f;

int n, idn[maxn], ids[maxn];

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline void swap(int &x, int &y) {
	int t = x; x = y; y = t;
}

#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,2000000,stdin), p1==p2)?EOF:*p1++)
char buf[2000000], *p1 = buf, *p2 = buf;
inline void read(int &x) {
    x = 0;
    char ch = gc();
    while(ch < '0' || ch > '9') ch = gc();
    while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = gc();
}

struct edge{
    int to, nex, id;
}e[maxn<<1];
int head[maxn], tot = 0;
inline void addedge(int u, int v, int _id) {
    e[tot] = (edge){v, head[u], _id}; head[u] = tot++;
    e[tot] = (edge){u, head[v], _id}; head[v] = tot++;
}

int fa[maxn], d[maxn], son[maxn], size[maxn], top[maxn], dfn[maxn], rk[maxn], dfs_clock = 1;
void dfs1(int pre, int cur) {
    fa[cur] = pre; d[cur] = d[pre]+1; size[cur] = 1;
    for(int i = head[cur]; i != -1; i = e[i].nex)
        if(e[i].to != pre) {
            dfs1(cur, e[i].to);
            size[cur] += size[e[i].to];
            if(size[e[i].to] > size[son[cur]]) son[cur] = e[i].to;
			idn[e[i].to] = e[i].id;
        }
}

void dfs2(int tp, int cur) {
    rk[dfs_clock] = cur; top[cur] = tp; dfn[cur] = dfs_clock++;
    if(!son[cur]) return;
    dfs2(tp, son[cur]);
    for(int i = head[cur]; i != -1; i = e[i].nex)
        if(!dfn[e[i].to])
            dfs2(e[i].to, e[i].to);
}

struct seg{
    int l, r, dat, laz;
}t[maxn<<4];

inline void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r; t[p].dat = t[p].laz = inf;
    if(l == r) return;
    int mid = (l+r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid+1, r);
}

inline void pushdown(int p) {
	t[p<<1].dat = min(t[p<<1].dat, t[p].laz);
	t[p<<1|1].dat = min(t[p<<1|1].dat, t[p].laz);
	t[p<<1].laz = min(t[p<<1].laz, t[p].laz);
	t[p<<1|1].laz = min(t[p<<1|1].laz, t[p].laz);
	t[p].laz = inf;
}

inline void change(int p, int l, int r, int v) {
	if(l <= t[p].l && t[p].r <= r) {
		t[p].dat = min(t[p].dat, v);
		t[p].laz = min(t[p].laz, v);
		return;
	}
	if(t[p].laz != inf) pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if(l <= mid) change(p<<1, l, r, v);
	if(r > mid) change(p<<1|1, l, r, v);
	t[p].dat = min(t[p<<1].dat, t[p<<1|1].dat);
}

inline int query(int p, int l, int r) {
	if(l <= t[p].l && t[p].r <= r)
		return t[p].dat;
	if(t[p].laz != inf) pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1, res = inf;
	if(l <= mid) res = min(res, query(p<<1, l, r));
	if(r > mid) res = min(res, query(p<<1|1, l, r));
	return res;
}

inline void cg(int x, int y, int v) {
	while(top[x] != top[y]) {
		if(d[top[x]] < d[top[y]]) swap(x, y);
		change(1, dfn[top[x]], dfn[x], v);
		x = fa[top[x]];
	}
	if(d[x] < d[y]) swap(x, y);
	change(1, dfn[y]+1, dfn[x], v);
}

int main() {
    int m, u, v, w;
    read(n); read(m);
    memset(head, -1, sizeof(head));
    for(int i = 1; i < n; i++) {
        read(u); read(v);
        addedge(u, v, i);
    }
    dfs1(0, 1);
    dfs2(1, 1);
    build(1, 1, n);
    while(m--) {
		read(u); read(v); read(w);
		if(u == v) continue;
		cg(u, v, w);
    }
	for(int i = 2; i <= n; i++) ids[idn[i]] = i;
	for(int i = 1; i < n; i++) {
		int t = query(1, dfn[ids[i]], dfn[ids[i]]);
		printf("%d\n", t==inf ? -1 : t);
	}
    return 0;
}
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  

---

## 作者：Styx (赞：1)

线段树合并  
结果模拟赛的时候没判-1萎掉了  
问题可以抽象成在一条边连接的两个点里较深的点的子树里找一条边，连接该点的父亲，且这条边边权最小

显然可以把边权离散化一下，然后树上差分，这都是线段树合并的小trick  
接着就可以随便线段树合并了

# 注意要判-1！！！！

代码如下：

```cpp
#include<bits/stdc++.h>
#define lson tr[now].l
#define rson tr[now].r
#define mp make_pair
#define pii pair<int,int>
using namespace std;

struct tree
{
	int sum,l,r;
}tr[5000060];

struct edge
{
	int from,to,w;
}e[100010];

vector<pii> g[100010];
vector<int> op[100010],op2[100010];

int n,m,tmp[100010],cnt,rt[100010],deep[100010],fa[100010][18],cnt2,ans[100010];
int N=100010;

int push_up(int now)
{
	tr[now].sum=tr[lson].sum+tr[rson].sum;
}

int insert(int &now,int l,int r,int pos,int val)
{
	if(!now) now=++cnt2;
	if(l==r)
	{
		tr[now].sum+=val;
		return 0;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	{
		insert(lson,l,mid,pos,val);
	}
	else
	{
		insert(rson,mid+1,r,pos,val);
	}
	push_up(now);
}

int query(int now,int l,int r)
{
	if(l==r) return tr[now].sum==0?-1:l;
	int mid=(l+r)>>1;
	if(tr[lson].sum) return query(lson,l,mid);
	else return query(rson,mid+1,r);
}

int merge(int a,int b,int l,int r)
{
	if(!a) return b;
	if(!b) return a;
	if(l==r)
	{
		tr[a].sum+=tr[b].sum;
		return a;
	}
	int mid=(l+r)>>1;
	tr[a].l=merge(tr[a].l,tr[b].l,l,mid);
	tr[a].r=merge(tr[a].r,tr[b].r,mid+1,r);
	push_up(a);
	return a;
}

void init()
{
	sort(tmp+1,tmp+cnt+1);
	int tot=unique(tmp+1,tmp+cnt+1)-tmp-1;
	for(int i=1;i<=m;i++)
	{
		e[i].w=lower_bound(tmp+1,tmp+cnt+1,e[i].w)-tmp;
	}
}

int dfs(int now,int f,int dep)
{
	deep[now]=dep;
	fa[now][0]=f;
	rt[now]=now;
	++cnt2;
	for(int i=1;i<=17;i++)
	{
		fa[now][i]=fa[fa[now][i-1]][i-1];
	}
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i].first==f) continue;
		dfs(g[now][i].first,now,dep+1);
	}
}

int lca(int x,int y)
{
	if(deep[y]>deep[x]) swap(x,y);
	for(int i=17;i>=0;i--)
	{
		if(deep[fa[x][i]]>=deep[y]) x=fa[x][i];
	}
	if(x==y) return x;
	for(int i=17;i>=0;i--)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}

int solve(int now,int f,int id)
{
	for(int i=0;i<op[now].size();i++)
	{
		insert(rt[now],1,N,op[now][i],1);
	}
	for(int i=0;i<op2[now].size();i++)
	{
		insert(rt[now],1,N,op2[now][i],-2);
	}
	for(int i=0;i<g[now].size();i++)
	{
		if(g[now][i].first==f) continue;
		solve(g[now][i].first,now,g[now][i].second);
		merge(rt[now],rt[g[now][i].first],1,N);
	}
	ans[id]=tmp[query(rt[now],1,N)];
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	int from,to;
	for(int i=1;i<n;i++)
	{
		cin>>from>>to;
		g[from].push_back(mp(to,i));
		g[to].push_back(mp(from,i));
	}
	dfs(1,0,1);
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].from>>e[i].to>>e[i].w;
		tmp[++cnt]=e[i].w;
	}
	init();
	tmp[0]=-1;
	for(int i=1;i<=m;i++)
	{
		int anc=lca(e[i].from,e[i].to);
		op[e[i].from].push_back(e[i].w);
		op[e[i].to].push_back(e[i].w);
		op2[anc].push_back(e[i].w);
	}
	solve(1,0,0);
	for(int i=1;i<n;i++)
	{
		cout<<ans[i]<<endl;
	}
}
```



---

## 作者：Clouder (赞：1)

## Before the Beginning

本文同步发表于[个人博客](https://www.codein.icu/lp4374/)。

## 解法

不难发现，额外的双向道路的两个端点，在树上的简单路径上的边，被割断后，都可以走这条双向道路。  
一个很自然的想法就是使用轻重链剖分加线段树，维护区间最小值，进行区间取 min 更新，复杂度 $O(n \log ^2 n)$.  
但可以通过对双向道路的边权进行排序，转化为染色问题。  
具体地，将双向道路以权值从大到小排序，转化为区间染色，每次染色都能覆盖上次的颜色，那么这个问题就相当经典了。  
同样可以使用线段树区间覆盖来维护染色，但复杂度依然是 $O(n \log ^2 n)$ 的。  
然而，染色问题有着更优的解决方法。有的人称为并查集，或者双向链表、缩点等等。  

[染色例题](https://www.luogu.com.cn/problem/P2391)

核心思想：逆序处理，将覆盖转化为跳过。由于染色的区间连续，因此可以在遇到一段已染色区间时，跳过该段区间，使每个点都只会被染色一次。  
感性理解时间复杂度是 $O(n)$ 的，这里不深入研究了。  

---

Update on 10/21/2020:    
经过一定的思考，发现我原先的代码复杂度应该是假的。    
原先的写法相当于不进行路径压缩的并查集，因为每个点虽然只需要染色一次，但会重复跳到已被染色的点上。具体地，从深向浅染色一条链，每次要求从链顶到链底染色，每次需要从链底跳到链顶，而由于没有路径压缩，相当于暴力跳点，会退化到 $O(n^2)$.  
因此需要对这个并查集进行路径压缩优化。而由于不使用按秩合并，最坏复杂度是 $O(\log n)$ 的。   

这里放一下原先的代码。   
[Old Version](https://www.luogu.com.cn/paste/f1ht6kg5)

---

在本题中，同样可以使用这个办法来进行染色。  
双向道路按权值从小到大排序。  
将简单路径拆成 $\texttt{u} \to \texttt{lca}$ 与 $\texttt{v} \to \texttt{lca}$ 两条，分别进行染色即可。    
并查集维护某个点的祖先中，第一个未被染色的点。    
将边转化为点后，注意 $\texttt{lca}$ 节点代表其通向父亲的边，是不用染色的。    

## 代码

实现中，使用了轻重链剖分求 $\texttt{lca}$，时间复杂度 $O(n\log n)$.  

```cpp
#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
const int maxn = 5e4 + 100;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc()) ;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}

struct node
{
    int to, next,id;
} E[maxn << 1];
int head[maxn], tot;
inline void add(int x, int y, int id) { E[++tot].next = head[x], E[tot].to = y, E[tot].id = id, head[x] = tot; }
struct edge
{
    int u, v, w;
} G[maxn];
bool cmp(const edge& a, const edge& b) { return a.w < b.w; }

//you can skip this part
int dep[maxn], size[maxn], son[maxn], top[maxn], fa[maxn], id[maxn], ANS[maxn];
void dfs1(int u)
{
    size[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa[u]) continue;
        id[v] = E[p].id, fa[v] = u, dep[v] = dep[u] + 1, dfs1(v), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
void dfs2(int u)
{
    if(!son[u]) return;
    top[son[u]] = top[u], dfs2(son[u]);
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa[u] || v == son[u]) continue;
        top[v] = v, dfs2(v);
    }
}
int lca(int x, int y)
{
    for (; top[x] != top[y]; x = fa[top[x]]) if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
//region end

int bel[maxn], up[maxn];
int find(int x) { return x == up[x] ? x : up[x] = find(up[x]); }
void update(int x, int y, int c)  //y is the ancestor of x
{
    //update from x to y (excluding y) with color c
    for (x = find(x); dep[x] > dep[y]; x = find(x)) bel[x] = c, up[x] = fa[x];
    //only set up[x] to fa[x], then leave it to path compression
}
int n, m;
int main()
{
    read(n), read(m);
    for (int i = 1, a, b; i < n; ++i) read(a), read(b), add(a, b, i), add(b, a, i);
    dep[1] = 1, dfs1(1), top[1] = 1, dfs2(1);
    for (int i = 1; i <= m; ++i) read(G[i].u), read(G[i].v), read(G[i].w);
    std::sort(G + 1, G + 1 + m, cmp);
    for (int i = 1; i <= n; ++i) up[i] = i;
    for (int i = 1; i <= m; ++i)
    {
        int l = lca(G[i].u, G[i].v);
        update(G[i].u, l, i), update(G[i].v, l, i);
    }
    for (int i = 2; i <= n; ++i) ANS[id[i]] = bel[i] ? G[bel[i]].w : -1;
    for (int i = 1; i < n; ++i) printf("%d\n", ANS[i]);
    return 0;
}
```

---

## 作者：miserExist (赞：0)

一个小 trick 为一条给的虚边会影响到连接的两个点之间的实边路径

如图： 红色的为给的虚边

![](https://z3.ax1x.com/2021/10/31/IpBYaF.png)

而这条虚边影响的路径就是：

![](https://z3.ax1x.com/2021/10/31/IpBrqK.png)

因为只要这两个点连了另外一条边，他们之间原本的路径上的边即使断开他们也依旧联通。

所以进行的操作就是区间赋值和求区间最小值，可以用树剖来实现。

但是打赋值 tag 的时候，要一次性把这个区间中的每一小段能打 tag 的都打上，即使这一区间的最小值小于你的 tag，因为区间可以覆盖掉它下面大的 tag

如图

![](https://z3.ax1x.com/2021/10/31/IpruXq.png)


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
const int N = 4e5 + 10, inf = 2e9;
int h[N], ne[N], e[N], idx;
int n,m;
int fa[N], sz[N], dep[N], cnt, top[N], son[N], id[N];
struct seg
{
	int l, r;
	int tag, minn;
}tr[N << 1];
struct Edge
{
	int u, v;
}edge[N];
void add(int a, int b)
{
	e[idx] = b;
	ne[idx] = h[a];
	h[a] = idx ++;
}
void dfs1(int u, int fat, int depth)
{
	sz[u] = 1;
	fa[u] = fat;
	dep[u] = depth;
	for(int i = h[u]; ~i; i = ne[i])
	{
		int y = e[i];
		if(y == fat) continue;
		
		dfs1(y,u,depth+ 1);
		sz[u] += sz[y];
		if(sz[son[u]] < sz[y]) son[u] = y;
	}
}
void dfs2(int u, int t)
{
	top[u] = t;
	id[u] = ++ cnt;
	if(!son[u]) return;
	dfs2(son[u], t);
	for(int i = h[u]; ~i; i = ne[i])
	{
		int y = e[i];
		if(y == fa[u] || y == son[u]) continue;
		dfs2(y,y);
	}
}
void pushup(int u)
{
	tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
}
void build(int u, int l, int r)
{
	tr[u].l = l, tr[u].r = r, tr[u].tag = inf, tr[u].minn = inf;
	if(l == r) return;
	int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
void pushdown(int u)
{
	if(tr[u].tag != inf)
	{
		tr[u << 1].tag = min(tr[u].tag, tr[u << 1].tag);
		tr[u << 1 | 1].tag = min(tr[u].tag, tr[u << 1 | 1].tag);
		if(tr[u << 1].minn >= tr[u].tag)
		{
			tr[u << 1].minn = tr[u].tag;
		}
		if(tr[u << 1 | 1].minn >= tr[u].tag)
		{
			tr[u << 1 | 1].minn = tr[u].tag;
		}
		tr[u].tag = inf;
	}
}
void modify(int u, int l, int r, int k)
{
	if(tr[u].l >= l && tr[u].r <= r)
	{
		tr[u].tag = min(k, tr[u].tag);
		if(tr[u].minn >= k)
		{
			tr[u].minn = k;
		}
		return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid) modify(u << 1, l, r, k);
	if(r > mid) modify(u << 1 | 1, l, r, k);
	pushup(u);
}
void pre_modify(int u, int v, int k)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u,v);
		modify(1, id[top[u]], id[u], k);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u,v);
	modify(1, id[u] + 1, id[v], k);
}
int query(int u, int pos)
{
	if(tr[u].l == pos && tr[u].r == pos)
	{
		return tr[u].minn;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(pos <= mid) return query(u << 1, pos);
	else if(pos > mid) return query(u << 1 | 1, pos);
}

signed main()
{
	cin >> n >> m;
	memset(h, -1, sizeof h);
	for(int i = 1; i <= n - 1; i ++)
	{
		int a,b;
		cin >> a >> b;
		add(a,b), add(b,a);
		edge[i].u = a, edge[i].v = b;
	}
	dfs1(1,0,1), dfs2(1,1), build(1,1,n);
	while(m --)
	{
		int l, r, len;
		cin >> l >> r >> len;
		pre_modify(l,r,len);
	}
	
	for(int i = 1; i <= n - 1; i ++)
	{
		int u = edge[i].u, v = edge[i].v;
		int val;
		if(dep[u] < dep[v])
		{
			val = query(1,id[v]);
		}
		else val = query(1, id[u]);
		if(val >= inf) puts("-1");
		else cout << val << endl;
	}
	
	
	return 0;
}

```

---

## 作者：D_F_S (赞：0)

    介绍一种自认为好理解的 DSU on tree 做法。
  
## Solution：
因为题目要求出删去每条边的答案，所以考虑离线处理。
![](https://z3.ax1x.com/2021/10/22/5cRQmQ.png)

（图示黑线为树边，红色为额外边）

如图所示，对于每条边，将其断开，都能将整棵树分成两个部分，一部分为单独的一颗子树。从这颗子树中连出的额外边中边权最小值便是对于这条边的答案。

显而易见，DSU 便可以维护子树中连接的所有额外边，用 DFS序 就能检验一条额外边是否连出子树，最后通过优先队列维护最小值。


**有一点需要注意**，虽然一共有 $m$ 条额外边需要我们维护，但一个点至多在 DSU 中暴力合并 $\log n$ ，因此一条额外边最多会加入优先队列中 $2*\log n$ 次，总的时间复杂度仍为 $O(n\log^{2}n)$。

## Code：
```cpp
#include<bits/stdc++.h>
#define inl inline
#define PA pair<int,int>
#define MP make_pair
using namespace std;
const int maxn=1e5+1;
struct node
{
	int next,to;
}edge[maxn<<1];
struct node1
{
	int next,to,val;
}exedge[maxn<<1];
struct node2
{
	int h,exh,size,son,st,ed,num;     // num : 每个点父亲边的编号 
}a[maxn];
priority_queue<PA,vector<PA>,greater<PA> > q;     // pair 的 first 记录边权， second 记录终点的 DFS 序 
int n,m,cnt,zs,ans[maxn];     // zs : 当前的重儿子编号 
inl int Read()     // 快读 
{
	int s=0; char c;
	while(!isdigit(c=getchar()));
	for(;isdigit(c);c=getchar()) s=s*10+c-'0';
	return s;
}
inl void Write(int x)     // 快输 
{
	short cnt=0,s[10];
	if(x<0) putchar('-'), x=-x;
	do s[++cnt]=x%10; while((x/=10));
	while(cnt--) putchar(s[cnt+1]+'0');
}
inl void Add(int y,int x)     // 新增树边 
{
	edge[++cnt]=(node){a[x].h,y}; a[x].h=cnt;
	edge[++cnt]=(node){a[y].h,x}; a[y].h=cnt;
}
inl void Exadd(int val,int y,int x)     // 新增额外边 
{
	exedge[++cnt]=(node1){a[x].exh,y,val}; a[x].exh=cnt;
	exedge[++cnt]=(node1){a[y].exh,x,val}; a[y].exh=cnt;
}
void DFS(int p,int prt)     // 找重儿子 
{
	a[p].size=1; a[p].st=++cnt;
	for(int i=a[p].h,to;i;i=edge[i].next)
	{
		to=edge[i].to;
		if(to==prt) continue;
		a[to].num=(i+1)>>1;
		DFS(to,p); a[p].size+=a[to].size;
		if(a[to].size>a[a[p].son].size) a[p].son=to;
	}
	a[p].ed=cnt;
}
void Calc(int p,int prt)     // 遍历子树内其他额外边 
{
	for(int i=a[p].exh;i;i=exedge[i].next) q.push(MP(exedge[i].val,a[exedge[i].to].st));
	for(int i=a[p].h;i;i=edge[i].next)
		if((edge[i].to!=prt)&&(edge[i].to!=zs)) Calc(edge[i].to,p);
}
void DSU(int p,int prt,bool flag)     // flag ： 当前子树是否需要清空 
{
	for(int i=a[p].h;i;i=edge[i].next)
		if((edge[i].to!=prt)&&(edge[i].to!=a[p].son)) DSU(edge[i].to,p,true);
	if(a[p].son) DSU(a[p].son,p,false), zs=a[p].son;
	Calc(p,prt); zs=0;
	while((!q.empty())&&q.top().second>=a[p].st&&q.top().second<=a[p].ed) q.pop();     // 排除连接子树内两点的额外边
	     // 如果在重儿子时一条边就连接了两个子树内的点，那么在当前点这条边一定也连接了两个子树内的点
	if(q.empty()) ans[a[p].num]=-1;     // 无解
	else ans[a[p].num]=q.top().first;
	if(flag)      // 清空 
	{
		priority_queue<PA,vector<PA>,greater<PA> > em;
		swap(q,em);     // 一种比 while 循环 pop 更快的清空方式 
	}
}
int main()
{
	n=Read(); m=Read();
	for(int i=1;i<n;++i) Add(Read(),Read());
	while(m--) Exadd(Read(),Read(),Read());
	cnt=0; DFS(1,0); cnt=0; DSU(1,0,0);     // 劳模 cnt …
	for(int i=1;i<n;++i) Write(ans[i]), putchar('\n');
	return 0;
}
```


------------
    p.s.这道题既有类并查集做法，也有树剖做法，所以 DSU on tree 很合理吧~

---

## 作者：yyyyxh (赞：0)

## 前言
看到题解大佬们LCA+并查集、树剖、LCT各种各样的做法，蒟蒻瑟瑟发抖，但似乎没有看到我在模拟赛上的思路，于是来补充一下。
## 思路
本题是让我们去求在一棵树上任意切断一条边，连接断开的两部分的额外边的最小值。

由于树上切断一条边，分成的两部分一定有这条边下的子树，处理子树问题有一种方法：欧拉序列。类似于DFS序，欧拉序列在DFS访问和回溯时各记一次时间戳，则有一个显然的性质：一颗子树的节点在欧拉序列中一定是一段连续的区间（访问完父节点后必先访问完其子节点再回溯），像树剖一样将子树问题转换为区间问题。
[![yZFdC4.png](https://s3.ax1x.com/2021/02/01/yZFdC4.png)](https://imgchr.com/i/yZFdC4)

如此图，欧拉序列为：1 2 3 4 4 5 5 3 2 6 7 7 6 1

其中 3 4 4 5 5 3 对应三的子树。

设一个节点 $i$ 对应的下标为 $l_i$ 和 $r_i$ ($l_i<r_i$)，则该节点在子树 $x$ 中的判定标准为 $l_x \leq l_i \leq r_x$ 或 $l_x \leq r_i \leq r_x$。若一条额外边 $(u,v)$ 在 $x$ 的父亲边切断时被统计，则有 $r_u< l_x \leq r_v \leq r_x$ 或 $l_x \leq l_u \leq r_x < l_v$。开一颗线段树进行统计。

对于第一种边，按递增扫描每一个 $l_x$ ，此时线段树中所有边都有 $r_u<l_x$ （因为不存在两个节点满足 $l_i<l_j<r_i<r_j$） ,因此统计其中 $r_v \in [l_x,r_x]$ 的边的最小值（即查询 $l_x$~$r_x$中记录的边权最小值），然后将这个节点所有的额外边加入线段树中（即在 $r_v$的位置记录 $w_{u,v}$）。

对于第二种边同理递减扫描 $r_x$，具体见代码。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100005,M=200005;
const int INF=1000000007;
int hd[N],nxt[M],to[M],id[M],tot=1;
int shd[N],snxt[M],sto[M],sval[M],stot;
int dfn1[N],dfn2[N];
int s[N],o[N],snum,onum;
int n,m;
int ans[N],num,yxh[N];


//-----线段树------- 
class Segment_Tree{
private:
	#define l(p) t[p].l
	#define r(p) t[p].r
	#define lc(p) (p<<1)
	#define rc(p) ((p<<1)|1)
	struct Segment_Tree_Node{
		int dat,l,r;
	}t[8*N];
public:
	void change(int p,int x,int v){
		if (l(p)==r(p)) {t[p].dat=min(t[p].dat,v); return;}
		int mid=(l(p)+r(p))>>1;
		if (x<=mid) change(lc(p),x,v);
		else change(rc(p),x,v);
		t[p].dat=min(t[lc(p)].dat,t[rc(p)].dat);
	}
	void init(int p,int l,int r){
		l(p)=l; r(p)=r;
		t[p].dat=INF;
		if (l==r) return;
		int mid=(l+r)>>1;
		init(lc(p),l,mid);
		init(rc(p),mid+1,r);
	}
	int ask(int p,int l,int r){
		if (l<=l(p)&&r>=r(p)) return t[p].dat;
		int mid=(l(p)+r(p))>>1;
		int val=INF;
		if (l<=mid) val=min(val,ask(lc(p),l,r));
		if (r>mid) val=min(val,ask(rc(p),l,r));
		return val;
	}
	#undef l
	#undef r
	#undef lc
	#undef rc
	#undef dat
}st,ot;
//-----线段树------- 


inline void add(int u,int v,int w){
	tot++;
	nxt[tot]=hd[u];
	hd[u]=tot;
	to[tot]=v;
	id[tot]=w;
}
inline void sadd(int u,int v,int w){
	stot++;
	snxt[stot]=shd[u];
	shd[u]=stot;
	sto[stot]=v;
	sval[stot]=w;
}
void label(int u,int in_edge){
	dfn1[u]=++num; s[++snum]=u; //访问时记录 
	yxh[u]=id[in_edge];  //注意是要按边输出，记录每个点对应边序号 
	for (int i=hd[u]; i; i=nxt[i]){
		if (i==(in_edge^1)) continue;
		label(to[i],i);
	}
	dfn2[u]=++num; o[++onum]=u; //回溯时记录 
}


int main(){
	scanf("%d%d",&n,&m);
	for (int i=1; i<n; i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v,i);
		add(v,u,i);
	}
	label(1,tot+2);
	for (int i=1; i<=m; i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		sadd(u,v,w);
		sadd(v,u,w);
	}
	for (int i=1; i<n; i++) ans[i]=INF;
	//递增枚举li 
	st.init(1,1,2*n);
	for (int i=1; i<=n; i++){
		int pos=s[i],ld=dfn1[pos],rd=dfn2[pos];
		ans[yxh[pos]]=min(ans[yxh[pos]],st.ask(1,ld,rd));
		for (int j=shd[pos]; j; j=snxt[j]) st.change(1,dfn2[sto[j]],sval[j]); //加入与该节点相连的额外边 
	}
	//递减枚举ri 
	ot.init(1,1,2*n);
	for (int i=n; i; i--){
		int pos=o[i],ld=dfn1[pos],rd=dfn2[pos];
		ans[yxh[pos]]=min(ans[yxh[pos]],ot.ask(1,ld,rd));
		for (int j=shd[pos]; j; j=snxt[j]) ot.change(1,dfn1[sto[j]],sval[j]);
	}
	for (int i=1; i<n; i++) if (ans[i]<INF) printf("%d\n",ans[i]); else puts("-1"); //注意判断无解 
	return 0;
}
```
时效上 $O(n\log_2n)$，写起来相对树剖应该轻松一些，线段树都不用懒标记。

---

## 作者：PanH (赞：0)

虽说是树剖裸题，但是其他的做法还蛮多的。

题解里已经有一个 **线段树合并+树上差分** 的方法，这里给出一个只用 **线段树合并** ，不用 **树上差分** 的方法。

一条边只有一端在子树内，另一端在子树外，才有可能对当前子树的根的向上连边产生贡献，所以合并时若相同位置的值在两个要合并的线段树中都存在，就可以将其赋值 INF ，就省去了差分。

code：
```
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int N=5e4+5,MAXN=2e6+5;
int n,m,ans[N],rt[N],tree[MAXN],ls[MAXN],rs[MAXN],tot;
struct edge{
	int next,to,id;
}e[N<<1];
int head[N],cnt;
void add(int u,int v,int id)
{
	e[++cnt]={head[u],v,id};
	head[u]=cnt;
}
#define mid (l+r>>1)
void ins(int l,int r,int &k,int x,int y)
{
	if(!k) k=++tot;
	if(l==r) return tree[k]=y,void();
	if(x<=mid) ins(l,mid,ls[k],x,y);
	else ins(mid+1,r,rs[k],x,y);
	tree[k]=min(tree[ls[k]],tree[rs[k]]);
}
void merge(int l,int r,int &k1,int k2)
{
	if(!k2) return;
	if(!k1) return k1=k2,void();
	if(l==r) return tree[k1]=INF,void();
	merge(l,mid,ls[k1],ls[k2]);
	merge(mid+1,r,rs[k1],rs[k2]);
	tree[k1]=min(tree[ls[k1]],tree[rs[k1]]);
}
#undef mid
void dfs(int x,int fa)
{
	for(int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y==fa) continue;
		dfs(y,x),ans[e[i].id]=tree[rt[y]];
		merge(1,m,rt[x],rt[y]);
	}
}
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m;
	tree[0]=INF;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,add(u,v,i),add(v,u,i);
	for(int i=1,u,v,w;i<=m;i++)
	{
		cin>>u>>v>>w;
		ins(1,m,rt[u],i,w);
		ins(1,m,rt[v],i,w);
	}
	dfs(1,0);
	for(int i=1;i<n;i++) cout<<(ans[i]==INF?-1:ans[i])<<endl;
}
```


---

## 作者：Genius_Z (赞：0)

[$\huge\color{blue}Bl\color{red}{og}$](http://geiz-revive.github.io/)

[$\large\color{blue} {Describe}$](https://www.luogu.org/problemnew/show/P4374)

蒟蒻回去颓了十天文化课以后回来的第一题。

分析题意可知，这题可以抽象成给链上的每条边赋值，每条边的权值为这个赋的值和原有值的最小值，然后就是板子了，树剖$log^2$，$LCT$ $log$，这里选择用$LCT$，因为要边转点所以常数还是挺大的。

还有就是注意初始化和要判断无解情况，初始化所有权值和标记为$inf$，统计答案时如果一条边的权为$inf$就输出$-1$

$\large{Code}$：

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
struct node {
	int fa, child[2], w, tag;
	bool filp;
}t[1000001];
inl void change(int x, int w) {
	t[x].w = min(t[x].w, w), t[x].tag = min(t[x].tag, w);
}
inl void reverse(int x) {
	swap(ls(x), rs(x)), t[x].filp ^= 1;
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
inl bool nroot(int x) { return ls(fa(x)) == x || rs(fa(x)) == x; }
inl bool poi(int x) { return rs(fa(x)) == x; }
inl void push(int x) {
	if (nroot(x))push(fa(x));
	pushdown(x);
}
inl void rotate(int x) {
	re f = fa(x), gf = fa(f), fs = poi(x), gfs = poi(f), s = t[x].child[fs ^ 1];
	if (nroot(f))t[gf].child[gfs] = x;
	t[f].child[fs] = s, t[x].child[fs ^ 1] = f;
	if (s)fa(s) = f;
	fa(x) = gf, fa(f) = x;
}
inl void splay(int x) {
	push(x);
	while (nroot(x)) {
		if (nroot(fa(x)))poi(x) == poi(fa(x)) ? rotate(fa(x)) : rotate(x);
		rotate(x);
	}
}
inl void access(int x) { for (re i = 0; x; x = fa(i = x)) splay(x), rs(x) = i; }
inl void makeroot(int x) { access(x), splay(x), reverse(x); }
inl void split(int x, int y) { makeroot(y), access(x), splay(x); }
inl void link(int x, int y) { split(x, y), fa(y) = x; }
struct edge {
	int u, v;
}e[1000001];
signed main() {
	re n = read<int>(), m = read<int>(), x, y, w;
	for (re i = 0; i <= n; i++)t[i].w = t[i + n].w = inf;
	for (re i = 1; i < n; i++)x = read<int>(), y = read<int>(), e[i] = edge{ x,y }, link(x, i + n), link(y, i + n);
	while (m--) {
		x = read<int>(), y = read<int>(), w = read<int>();
		split(x, y), change(x, w);
	}
	for (re i = 1; i < n; i++)split(e[i].u, e[i].v), writeln(t[i + n].w == inf ? -1 : t[i + n].w);
}
```



---

## 作者：nihanchu (赞：0)

这个好像完全就是联系树剖的模板题。
很明显额外加的路径可以拿来更新两点间的那些边的最优答案，然后就直接树剖就可以了。
要注意更新的时候两点的公共祖先的想上连的边不能被更新。
唔，适合用来练习树剖。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 8*50009
#define maxx 1000000009
#include<vector>
using namespace std;
int w[maxn],num,cnt,n,m,fa[maxn],size[maxn],dep[maxn],son[maxn],top[maxn];
int f[maxn],head[maxn],fx[maxn];
struct ding{
  int t,nex;
}e[maxn];
void add(int u,int v)
{e[++num].t=v;e[num].nex=head[u];head[u]=num;}
pair<int,int>q[maxn];
void dfs1(int x,int y)
{
  fa[x]=y; size[x]=1;son[x]=0;int now=0;
  for (int i=head[x];i;i=e[i].nex)
  {
  	int to=e[i].t;if (to==y) continue;
  	dep[to]=dep[x]+1;dfs1(to,x);size[x]+=size[to];
  	if (size[to]>now) now=size[to],son[x]=to;
  }
}
void dfs2(int x,int y)
{
  w[x]=++cnt;
  if (son[x]!=0) top[son[x]]=top[x],dfs2(son[x],x);
  for (int i=head[x];i;i=e[i].nex)
  {
  	int to=e[i].t;
  	if ((to==y)||(to==son[x])) continue;
  	top[to]=to;
  	dfs2(to,x);
  }
}
void build(int x,int l,int r)
{
  f[x]=maxx;
  if (l==r) return;
  int mid=(l+r)>>1;
  build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}
void push(int x)
{
  f[x<<1]=min(f[x<<1],f[x]);
  f[x<<1|1]=min(f[x<<1|1],f[x]);
}
void up(int x,int l,int r,int lef,int righ,int val)
{
  if ((l>=lef)&&(r<=righ))
  {
  	f[x]=min(f[x],val); return;
  } 
  int mid=(l+r)>>1;push(x);
  if (lef<=mid)up(x<<1,l,mid,lef,righ,val);
  if (righ>mid)up(x<<1|1,mid+1,r,lef,righ,val);
}
int query(int x,int l,int r,int y)
{
  if ((l==y)&&(r==y)) return f[x];
  push(x);
  int mid=(l+r)>>1;
  if (y<=mid) return query(x<<1,l,mid,y);
  if (y>mid) return query(x<<1|1,mid+1,r,y);
}
void update(int x,int y,int val)
{
  int now,tx=top[x],ty=top[y],ans=0; 
  //if ((x==1)&&(y==4)) cout<<"$"<<tx<<" "<<ty<<endl;
  while (tx!=ty)
  {
  	if (dep[tx]<dep[ty]) swap(x,y),swap(tx,ty);
  	up(1,1,n,w[tx],w[x],val);
  	x=fa[tx]; tx=top[x];
  }
  if (x==y) return;
  if (w[x]>w[y]) swap(x,y);
  up(1,1,n,w[x]+1,w[y],val);
}
inline int read()
{
  int ex=0;char ch;
  ch=getchar();
  while ((ch<'0')||(ch>'9')) ch=getchar();
  while ((ch>='0')&&(ch<='9'))
  {
  	ex=ex*10+ch-'0';
  	ch=getchar();
  }
  return ex;
}
int main()
{
  scanf("%d%d",&n,&m);
  int x,y,r;
  for (int i=1;i<n;i++)
  {
  	x=read();y=read();add(x,y);add(y,x);
  	q[i]=make_pair(x,y);
  }
  top[1]=1;dep[1]=1;
  dfs1(1,1);dfs2(1,1);
  build(1,1,n); 
  for (int i=1;i<=m;i++)
  {
  	x=read();y=read();r=read();
  	//if ((fa[x]==y)||(fa[y]==x)) continue;
  	update(x,y,r);
  }
  int tp;
  for (int i=1;i<n;i++)
  {
   if (dep[q[i].first]>dep[q[i].second]) 
   tp=query(1,1,n,w[q[i].first]);
   else tp=query(1,1,n,w[q[i].second]);
   if (tp!=maxx) printf("%d\n",tp);
   else cout<<"-1"<<endl;
  }
  return 0;
}

```

---

## 作者：Autre (赞：0)

给定一棵树和 $m$ 对元素 $(u_i,v_i,w_i)$，对于每条边求出所有 $u_i,v_i$ 分布在该边两侧的元素中 $w_i$ 的最小值。

不难发现 $u_i,v_i$ 分居某条边两侧，当且仅当这条边在 $u_i$ 到 $v_i$ 的简单路径上。于是我们放弃枚举每条边考虑所有元素的贡献，转而枚举每个元素，更新涉及到的边的答案。

可行的做法有 $O(m\log^2n)$ 的重链剖分，$O(m\log n)$ 的全局平衡二叉树，$O(n\log m)$ 的线段树合并，还有其余题解没提到过的，好写常数又小的可并堆。

考虑对每个点维护出，涉及到这个点的所有元素按照 $w_i$ 构成的小根堆。树上差分，在链的两个端点加边，在链上最浅的点处删边（也即我们需要用两个堆维护实现堆的删除），一个点的堆来源于儿子的贡献（也即我们需要使用可并堆）和在自己处登记的加边、删边。

这里使用左偏树实现可并堆。

```C++
#include<iostream>
#include<cstring>
#include<vector>

const int N = 5e4, T = N*4+1;
std::vector<std::pair<int, int>>g[N];
int ls[T], rs[T], vl[T], h[T], tt;
int w[N*3], nx[N*3], ad[N], dl[N];
int s[N], d[N], fa[N], sn[N], tf[N];
int o[N], ans[N];
void isn(int u, int f) {
    s[u] = 1, sn[u] = -1, fa[u] = f;
    for (auto[v, i] : g[u]) if (v != f) {
        d[v] = d[u] + 1, isn(v, u), s[u] += s[v];
        if (!~sn[u] || s[v] > s[sn[u]]) sn[u] = v;
    }
}
void itf(int u, int f) {
    if (tf[u] = f, ~sn[u]) itf(sn[u], f);
    for (auto[v, i] : g[u])
        if (v != fa[u] && v != sn[u]) itf(v, v);
}
int lca(int u, int v) {
    for (; tf[u]!=tf[v]; u=fa[tf[u]])
        if (d[tf[u]] < d[tf[v]]) std::swap(u, v);
    return d[u] < d[v] ? u : v;
}
int mg(int u, int v) {
    if (!u || !v) return u | v;
    if (vl[u] > vl[v]) std::swap(u, v);
    rs[u] = mg(rs[u], v);
    if (h[ls[u]] < h[rs[u]]) std::swap(ls[u], rs[u]);
    return h[u] = h[rs[u]] + 1, u;
}
std::pair<int, int>dfs(int u, int f) {
    int a = 0, b = 0;
    for (auto[v, i] : g[u]) if (v != f) {
        auto[x, y] = dfs(o[i] = v, u);
        a = mg(a, x), b = mg(b, y);
    }
    for (int i=ad[u]; ~i; i=nx[i])
        vl[++tt] = w[i], a = mg(a, tt);
    for (int i=dl[u]; ~i; i=nx[i])
        vl[++tt] = w[i], b = mg(b, tt),
        vl[++tt] = w[i], b = mg(b, tt);
    while (b && vl[a] == vl[b])
        a = mg(ls[a], rs[a]), b = mg(ls[b], rs[b]);
    return ans[u] = a ? vl[a] : -1, std::make_pair(a, b);
}
int main() {
    int n, m; std::cin >> n >> m;
    memset(ad, -1, n*4), memset(dl, -1, n*4);
    for (int i=1, u, v; i<n; i++) std::cin >> u >> v,
        g[--u].emplace_back(--v, i), g[v].emplace_back(u, i);
    isn(0, 0), itf(0, 0);
    for (int i=0, u, v, x, t; i<m; i++) std::cin >> u >> v >> x,
        nx[i*3] = ad[--u], w[i*3] = x, ad[u] = i*3,
        nx[i*3+1] = ad[--v], w[i*3+1] = x, ad[v] = i*3+1,
        nx[i*3+2] = dl[t=lca(u, v)], w[i*3+2] = x, dl[t] = i*3+2;
    dfs(0, 0);
    for (int i=1; i<n; i++) printf("%d\n", ans[o[i]]);
}
```

---

