# COT2 - Count on a tree II

## 题目描述

You are given a tree with **N** nodes. The tree nodes are numbered from **1** to **N**. Each node has an integer weight.

We will ask you to perform the following operation:

- **u v** : ask for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 样例 #1

### 输入

```
8 2
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
7 8```

### 输出

```
4
4```

# 题解

## 作者：eee_hoho (赞：32)

裸的树上莫队

其实和普通莫队上一样的，只不过我们要把树转化为线性结构，这就需要欧拉序，我们从根对这棵树进行$dfs$，点进栈时记一个时间戳$st$，出栈时再记一个时间戳$ed$，画个图理解一下

![fasdfa](https://cdn.luogu.com.cn/upload/pic/63138.png)

这棵树的欧拉序为$(1,2,4,5,5,6,6,7,7,4,2,3,3)$，那么每次询问的节点$u,v$有两种情况

1. $u$在$v$的子树中（$v$在$u$的子树中同理），比如$u=6,v=2$，我们拿出$(st[2],st[6])$这段区间$(2,4,5,5,6)$，$5$出现了两次，因为搜索的时候$5$不属于这条链，所以进去之后就出去了，而出现一次的都在这条链上，就都可以统计

2. $u$和$v$不在同一个子树中，比如$u=5,v=3$，这次拿出$(ed[5],st[3])$这段区间$(5,6,6,7,7,4,2,3)$，要保证$st[u]<st[v]$，出现两次的可以忽略，然而这次只统计了$5,4,2,3$，所以最后再统计上$lca$就好了

- 至于如何忽略掉区间内出现了两次的点，这个很简单，我们多记录一个$use[x]$，表示$x$这个点有没有被加入，每次处理的时候如果$use[x]=0$则需要添加节点；如果$use[x]=1$则需要删除节点，每次处理之后都对$use[x]$异或$1$就可以了

- 而欧拉序可以用树剖来求，$lca$也就求出来了，非常的方便

- 排序的话没有区别，可以普通排序，也可以奇偶性排序

- 因为$st,ed$的大小都是$n$，所以取块的大小时要用$2n$，而不是$n$

- 最后要注意的一点就是这个题权值比较大，需要离散化

**Code**
``` cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#define N 200000
using namespace std;
struct node
{
	int l,r,ll,rr,id,lca;
}q[N+5];
int n,m,a[N+5],st[N+5],ed[N+5],dfn[N+5],f[N+5],num,size[N+5],his[N+5],dep[N+5],son[N+5],top[N+5],c[N+5],tmp,blo,l=1,r,use[N+5],ans[N+5],data[N+5];
vector <int> d[N+5];
void dfs1(int u,int fa)  //树剖第一次深搜
{
	f[u]=fa;st[u]=++num;
	size[u]=1;his[num]=u;
	dep[u]=dep[fa]+1;
	vector <int>::iterator it;
	for (it=d[u].begin();it!=d[u].end();it++)
	{
		int v=(*it);
		if (v==fa)continue;
		dfs1(v,u);
		size[u]+=size[v];
		if (size[v]>size[son[u]])son[u]=v;
	}
	ed[u]=++num;his[num]=u;
}
void dfs2(int u,int to)   //树剖第二次深搜
{
	top[u]=to;
	if (son[u])dfs2(son[u],to);
	vector <int>::iterator it;
	for (it=d[u].begin();it!=d[u].end();it++)
	{
		int v=(*it);
		if (v!=son[u]&&v!=f[u])dfs2(v,v);
	}
}
int Lca(int x,int y)   //树剖求lca
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]])swap(x,y);
		x=f[top[x]];
	}
	if (dep[x]>dep[y])swap(x,y);
	return x;
}
void add(int x)
{
	tmp+=(++c[a[x]]==1);
}
void del(int x)
{
	tmp-=(--c[a[x]]==0);
}
void calc(int x)     //对点进行加入或删除
{
	(!use[x])?add(x):del(x);
	use[x]^=1;
}
int cmp(node x,node y)   //排序
{
	return (x.ll==y.ll)?(x.ll%2==1?x.r<y.r:x.r>y.r):x.l<y.l;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),data[i]=a[i];
    sort(data+1,data+n+1);
    for(int i=1;i<=n;i++)a[i]=lower_bound(data+1,data+n+1,a[i])-data;  //离散化
	int x,y;
	for (int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		d[x].push_back(y);
		d[y].push_back(x);
	}
	dfs1(1,0); 
	dfs2(1,1);
	blo=n*2/sqrt(m*2/3);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		if (st[x]>st[y])swap(x,y);  //保证stx<sty
		q[i].id=i;
		q[i].lca=Lca(x,y);  
		if (q[i].lca==x)    //x,y在以x为根的子树中
		{
			q[i].l=st[x];
			q[i].r=st[y];
			q[i].ll=st[x]/blo;
			q[i].rr=st[y]/blo;
			q[i].lca=0;
		}
		else
		{
			q[i].l=ed[x];
			q[i].r=st[y];
			q[i].ll=ed[x]/blo;
			q[i].rr=st[y]/blo;
		}
	}
	sort(q+1,q+m+1,cmp);
	for (int i=1;i<=m;i++)
	{
		while (l>q[i].l)calc(his[--l]);
		while (r<q[i].r)calc(his[++r]);
		while (l<q[i].l)calc(his[l++]);
		while (r>q[i].r)calc(his[r--]);
		if (q[i].lca)calc(q[i].lca);
		ans[q[i].id]=tmp;
		if (q[i].lca)calc(q[i].lca);
	}
	for (int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：attack (赞：23)

## [更好的阅读体验点这里](https://www.cnblogs.com/zwfymqz/p/9223425.html)

## 简介

树上莫队，顾名思义就是把莫队搬到树上。


题目意思很明确：给定一个$n$个节点的树，每个节点表示一个整数，问$u$到$v$的路径上有多少个不同的整数。

像这种不带修改数颜色的题首先想到的肯定是树套树莫队，那么如何把在序列上的莫队搬到树上呢？

## 算法

### 欧拉序

我们考虑用什么东西可以把树上的问题转化到序列上，dfs序是可以的，但是这道题不行（无法搞lca的贡献）

有一种神奇的东西，叫做欧拉序。

它的核心思想是：当访问到点$i$时，加入序列，然后访问$i$的子树，当访问完时，再把$i$加入序列

煮个栗子，下面这棵树的欧拉序为

$1\ 2\ 3\ 4\ 4\ 5\ 5\ 6\ 6\ 3\ 7\ 7\ 2\ 1$



 

### 树上莫队

有了这个有什么用呢？

我们考虑我们要解决的问题：求$x$到$y$的路径上有多少个不同的整数

 

这里我们设$st[i]$表示访问到$i$时加入欧拉序的时间，$ed[i]$表示回溯经过$i$时加入欧拉序的时间

不妨设$st[x]<st[y]$（也就是先访问$x$，再访问$y$）

分情况讨论 

 

若$lca(x,y) = x$，这时$x,y$在一条链上，那么$st[x]$到$st[y]$这段区间中，有的点出现了两次，有的点没有出现过，这些点都是对答案没有贡献的，我们只需要统计出现过$1$次的点就好

比如当询问为$2,6$时，$(st[2],st[6])=2\ 3\ 4\ 4\ 5\ 5\ 6$，$4,5$这两个点都出现了两次，因此不统计进入答案

若$lca(x,y) \not = x$，此时$x,y$位于不同的子树内，我们只需要按照上面的方法统计$ed[x]$到$st[y]$这段区间内的点。 

比如当询问为$4,7$时，$(ed[4],st[7]) = 4\ 5\ 5\ 6\ 6\ 3\ 7\ $。大家发现了什么？没错！我们没有统计$lca$，因此我们需要特判$lca$

 

然后就没啦，开始愉快的调代码吧

 

## 相关证明

此处纯为作者瞎扯。。。

为什么出现两次的点不统计答案
树上路径的定义为：从$x$到$y$经过节点个数最少的路径。

若一个点$k$出现两次，说明我们可以先访问$k$，进入$k$的子树中，然后出来，再到$y$，很显然不访问$k$是更优的。因此出现两次的点不能统计入答案

为什么当$lca(x,y) \not =x$时需要从$ed[x]$开始遍历
从$st[x]$到$ed[x]$为$x$的子树中的节点，很显然这些节点不能统计进答案

## 代码

注意我们询问的区间长度为$2*N$，所以预处理的时候一定要循环到$2*N$！

 
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
using namespace std;
const int MAXN = 1e5 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, Q;
int belong[MAXN], block;
struct Query {
    int l, r, ID, lca, ans;
    bool operator < (const Query &rhs) const{
        return belong[l] == belong[rhs.l] ? r < rhs.r : belong[l] < belong[rhs.l];
    //    return belong[l] < belong[rhs.l];
    }
}q[MAXN];
vector<int>v[MAXN];
int a[MAXN], date[MAXN];
void Discretization() {
    sort(date + 1, date + N + 1);
    int num = unique(date + 1, date + N + 1) - date - 1;
    for(int i = 1; i <= N; i++) a[i] = lower_bound(date + 1, date + num + 1, a[i]) - date;    
}
int deep[MAXN], top[MAXN], fa[MAXN], siz[MAXN], son[MAXN], st[MAXN], ed[MAXN], pot[MAXN], tot;
void dfs1(int x, int _fa) {
    fa[x] = _fa; siz[x] = 1;
    st[x] = ++ tot; pot[tot] = x; 
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(deep[to]) continue;
        deep[to] = deep[x] + 1;
        dfs1(to, x);
        siz[x] += siz[to];
        if(siz[to] > siz[son[x]]) son[x] = to;
    }
    ed[x] = ++tot; pot[tot] = x;
}
void dfs2(int x, int topfa) {
    top[x] = topfa;
    if(!son[x]) return ;
    dfs2(son[x], topfa);
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(top[to]) continue;
            dfs2(to, to);
    }
}
int GetLca(int x, int y) {
    while(top[x] != top[y]) {
        if(deep[top[x]] < deep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
void DealAsk() {
    for(int i = 1; i <= Q; i++) {
        int x = read(), y = read();
        if(st[x] > st[y]) swap(x, y);
        int _lca = GetLca(x, y);
        q[i].ID = i;
        if(_lca == x) q[i].l = st[x], q[i]. r = st[y];
        else q[i].l = ed[x], q[i].r = st[y], q[i].lca = _lca;
    }
}
int Ans, out[MAXN], used[MAXN], happen[MAXN];
void add(int x) {
    if(++happen[x] == 1) Ans++;
}
void delet(int x) {
    if(--happen[x] == 0) Ans--;
}
void Add(int x) {
    used[x] ? delet(a[x]) : add(a[x]); used[x] ^= 1;
}
void Mo() {
    sort(q + 1, q + Q + 1);
    int l = 1, r = 0, fuck = 0;
    for(int i = 1; i <= Q; i++) {
        while(l < q[i].l) Add(pot[l]), l++, fuck++;
        while(l > q[i].l) l--, Add(pot[l]), fuck++;
        while(r < q[i].r) r++, Add(pot[r]), fuck++;
        while(r > q[i].r) Add(pot[r]), r--, fuck++;
        if(q[i].lca) Add(q[i].lca);
        q[i].ans = Ans;
        if(q[i].lca) Add(q[i].lca);
    }
    for(int i = 1; i <= Q; i++) out[q[i].ID] = q[i].ans;
    for(int i = 1; i <= Q; i++)
        printf("%d\n", out[i]);
}
int main() {
    N = read(); Q = read();
    //block = 1.5 * sqrt(2 * N) + 1;
    //block = pow(N, 0.66666666666);
    block = sqrt(N);
    for(int i = 1; i <= N; i++) a[i] = date[i] = read();
    for(int i = 1; i <= N * 2; i++) belong[i] = i / block + 1;
    Discretization();
    for(int i = 1; i <= N - 1; i++) {
        int x = read(), y = read();
        v[x].push_back(y); v[y].push_back(x);
    }
    deep[1] = 1; dfs1(1, 0);
    dfs2(1, 1);
/*    for(int i = 1; i <= N; i++)    
        for(int j = 1; j <= i - 1; j++)
            printf("%d %d %d\n", i, j, GetLca(i, j));*/
    DealAsk();
    Mo();
    return 0;
}
 ```

---

## 作者：Spasmodic (赞：15)

我直接膜拜ClCN

### 1.前言
[模板题](https://www.luogu.com.cn/problem/SP10707)

前置芝士：欧拉序，莫队

下面进入正题。
### 2.算法（例题：SP10707）
首先我们考虑链上的问题，显然是可以一个莫队解决的.

但是树上显然不可以树链剖分，因为考虑到我们无法把两段链的答案合并。

那怎么办？

其实除了dfn序，还有一个东西，叫**欧拉序**，我们可以尝试把它转化过去。

我们先画一个样例的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kz6prh8l.png)

下面是这个图的欧拉序：
```
1 2 2 3 5 5 6 6 7 7 3 4 8 8 4 1
```

显然可以预计算两个数组：$s_u$表示$u$第一次出现的地方，$t_u$表示$u$最后一次出现的地方。

为了方便起见，我们不妨设$s_u<s_v$，即$u$比$v$先出现。

下面我们考虑如何转化，我们分两种情况考虑：

1. u和v是祖孙关系

如$u=3,v=6$

这种情况下，我们考虑转化为$[s_u,s_v]$

拿$u=3,v=6$举例，我们就可以转化为这样的一个区间：
```
3 5 5 6
```
这里$5$出现了2次，相当于一进一出，就可以转化了。

2. otherwise

如$u=2,v=6$

这种情况下，我们考虑转化为$[t_u,s_v]$

不过这样是不够的，我们还要加上一个LCA。

拿$u=2,v=6$举例，我们就可以转化为这样的一个区间：
```
2 3 5 5 6
```
这里$5$出现了两次可以抵消，而$1$没有出现，我们只要加上$1$就可以了

于是我们就转化为了序列上的问题，可以用莫队解决。

### 3.代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=40005,M=100005;
int n,m,bl,uv,c[N],a[N],tot,hd[N],ans[M];
struct edge{int t,nxt;}es[N<<1];
void add(int u,int v){es[++tot]=(edge){v,hd[u]},hd[u]=tot;}
int e[N<<1],d[N],f[N][20],cnt,s[N],t[N],ccnt[N];
void dfs(int u){
	d[u]=d[f[u][0]]+1,e[++cnt]=u,s[u]=cnt;
	for(int i=1;i<20;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=hd[u],v;i;i=es[i].nxt)if((v=es[i].t)!=f[u][0])f[v][0]=u,dfs(v);
	e[++cnt]=u,t[u]=cnt;
}
int LCA(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=19;i>=0;i--)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
struct query{int l,r,pos,id,x;}q[M];
bool cmp(const query&x,const query&y){return x.pos==y.pos?x.r>y.r:x.pos<y.pos;}
bool vst[N];
void update(int x){
	if(!(vst[x]^=1)&&(--ccnt[c[x]])==0)uv--;
	if(vst[x]&&(ccnt[c[x]]++)==0)uv++;
}
int main(){
	scanf("%d%d",&n,&m),bl=sqrt(m);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]),a[i]=c[i];
	sort(a+1,a+n+1);
	int qaq=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;i++)c[i]=lower_bound(a+1,a+qaq+1,c[i])-a;
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1);
	for(int i=1,u,v,lca;i<=m;i++){
		scanf("%d%d",&u,&v),lca=LCA(u,v),q[i].id=i;
		if(u==lca||v==lca){
			if(s[v]<s[u])swap(u,v);
			q[i].l=s[u],q[i].r=s[v];
		}
		else {
			if(t[v]<s[u])swap(u,v);
			q[i].l=t[u],q[i].r=s[v],q[i].x=lca;
		}
		q[i].pos=q[i].l/bl; 
	}
	sort(q+1,q+m+1,cmp);
	for(int i=1,l=1,r=0;i<=m;i++){
		while(l>q[i].l)update(e[--l]);
		while(r<q[i].r)update(e[++r]);
		while(l<q[i].l)update(e[l++]);
		while(r>q[i].r)update(e[r--]);
		if(q[i].x)update(q[i].x);
		ans[q[i].id]=uv;
		if(q[i].x)update(q[i].x);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：何俞均 (赞：11)

广告：食用[$blog$](https://www.cnblogs.com/heyujun/p/10334356.html)体验更佳

这题在$bzoj$上是一个强制在线的题目，所以莫队在上面是不能过的。

所以我们就用到了另一个东西：树分块

![img](https://i.loli.net/2019/01/29/5c4ffb5ed1747.png)

具体是怎么分块的呢：根据深度，从最深的叶子节点往上分，同一子树内的节点在一个块

比如说上面那张图，

有$7$个点，那么我们每隔$2$的深度就分一块

但是我们又要保证同一子树内的在一块，且要从最深的叶子节点一直往下

所以最后分块的结果：$(1,2)(7,6,3)(4,5)$。

知道怎么分块了，我们在来考虑怎么做。

现在给了你两个将询问的点$u,v(dep[u]>dep[v])$，我们分类讨论一下现在的情况：

>$(1):$这两个点在同一个块内:
直接暴力统计即可
$(2):$这两个点不在同一个块内：
这种情况比较复杂，记一个块的根为$rt[i]$，则它到另外所有点的答案我们可以很轻松地
统计出来，只需要对于每个$rt[i]$暴力统计一遍就可以了。
那么现在我们要考虑的只有$u$到它的块的根$x$路径上是否会对答案产生贡献：
对于这个，我们可以将这个分块可持久化，维护这个点的颜色在它的祖先中出现最深的位置
的深度，那么一个块只需继承上面的块，并将在这个块中颜色的答案更新，因为那个颜色如
果出现在这个位置，那么答案肯定更优。
有了上面的铺垫，那我们只需对$u\rightarrow x$上的点暴力算它的深度是否超过$lca_{u,v}$即可

代码
```cpp
#include <iostream> 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath> 
#include <algorithm> 
using namespace std; 
inline int gi() { 
    register int data = 0, w = 1; 
    register char ch = 0; 
    while (!isdigit(ch) && ch != '-') ch = getchar(); 
    if (ch == '-') w = -1, ch = getchar(); 
    while (isdigit(ch)) data = 10 * data + ch - '0', ch = getchar(); 
    return w * data; 
} 
const int MAX_N = 4e4 + 5; 
struct Graph { int to, next; } e[MAX_N << 1]; int fir[MAX_N], e_cnt; 
void clearGraph() { memset(fir, -1, sizeof(fir)); e_cnt = 0; }  
void Add_Edge(int u, int v) { e[e_cnt] = (Graph){v, fir[u]}; fir[u] = e_cnt++; } 
int N, M, LEN; 
int X[MAX_N], a[MAX_N], b[MAX_N], r[MAX_N]; 
int P[MAX_N][205], A[205][MAX_N];
int fa[MAX_N], dep[MAX_N], q[MAX_N], belong[MAX_N], cur, sz;
int rt[205], tot;
int c[MAX_N], Res; 
struct Block {
    int a[205]; 
    int &operator [] (int x) { return P[a[b[x]]][r[x]]; } 
    void insert(Block rhs, int x, int d) { 
        int blk = b[x], t = r[x]; 
        memcpy(a, rhs.a, sizeof(a)); 
        memcpy(P[++sz], P[a[blk]], sizeof(P[0])); 
        P[sz][t] = d, a[blk] = sz; 
    } 
} s[MAX_N]; 
 
namespace Tree { 
    int top[MAX_N], son[MAX_N], size[MAX_N]; 
    void dfs(int x, int tp) { 
        top[x] = tp; 
        if (son[x]) dfs(son[x], tp); 
        for (int i = fir[x]; ~i; i = e[i].next) {
            int v = e[i].to; if (v == fa[x] || v == son[x]) continue; 
            dfs(v, v); 
        } 
    }
    int LCA(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y); 
            x = fa[top[x]]; 
        } 
        return dep[x] < dep[y] ? x : y; 
    } 
} 
int dfs(int x, int f) { 
    fa[x] = f; 
    s[x].insert(s[f], a[x], dep[x] = dep[f] + 1); 
    Tree::size[x] = 1; 
    q[++cur] = x; int md = dep[x], p = cur; 
    for (int i = fir[x]; ~i; i = e[i].next) {
        int v = e[i].to; if (v == f) continue; 
        md = max(md, dfs(v, x)); Tree::size[x] += Tree::size[v]; 
        if (Tree::size[Tree::son[x]] < Tree::size[v]) Tree::son[x] = v; 
    } 
    if (md - dep[x] >= LEN || p == 1) { 
        rt[++tot] = x; 
        for (int i = p; i <= cur; i++) belong[q[i]] = tot; 
        cur = p - 1;
        return dep[x] - 1; 
    } 
    return md; 
}
void Prepare(int x, int f, int *s) { 
    if (!c[a[x]]++) ++Res; s[x] = Res; 
    for (int i = fir[x]; ~i; i = e[i].next) if (e[i].to != f) Prepare(e[i].to, x, s); 
    if (!--c[a[x]]) --Res; 
} 
int Solve1(int u, int v) { 
    for (cur = Res = 0; u != v; u = fa[u]) {
        if (dep[u] < dep[v]) swap(u, v); 
        if (!c[q[++cur] = a[u]]) c[a[u]] = 1, ++Res; 
    } 
    for (Res += !c[a[u]]; cur; ) c[q[cur--]] = 0;
    return Res; 
} 
int Solve2(int u, int v) {
    if (dep[rt[belong[u]]] < dep[rt[belong[v]]]) swap(u, v); 
    int x = rt[belong[u]], d = dep[Tree::LCA(u, v)]; Res = A[belong[u]][v]; 
    for (cur = 0; u != x; u = fa[u]) { 
        if (!c[a[u]] && s[x][a[u]] < d && s[v][a[u]] < d)
            c[q[++cur] = a[u]] = 1, ++Res; 
    } 
    for (; cur; ) c[q[cur--]] = 0; 
    return Res; 
} 
int main () { 
    clearGraph(); 
    N = gi(), M = gi(); LEN = sqrt(N) - 1; 
    for (int i = 1; i <= N; i++) b[i] = (i - 1) / LEN + 1, r[i] = i % LEN; 
    for (int i = 1; i <= N; i++) a[i] = X[i] = gi(); 
    sort(&X[1], &X[N + 1]); int cnt = unique(&X[1], &X[N + 1]) - X - 1; 
    for (int i = 1; i <= N; i++) a[i] = lower_bound(&X[1], &X[cnt + 1], a[i]) - X; 
    for (int i = 1; i < N; i++) { 
        int u = gi(), v = gi();
        Add_Edge(u, v);
        Add_Edge(v, u); 
    }
    cur = 0; 
    dfs(1, 0); Tree::dfs(1, 1); 
    for (int i = 1; i <= tot; i++) Prepare(rt[i], 0, A[i]); 
     
    for (int ans = 0; M--; ) {
        int u = ans ^ gi(), v = gi(); 
        printf("%d\n", ans = belong[u] == belong[v] ? Solve1(u, v) : Solve2(u, v)); 
    } 
    return 0; 
} 
```

另附莫队代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

inline int gi() {
    register int data = 0, w = 1;
    register char ch = 0;
    while (ch != '-' && (ch > '9' || ch < '0')) ch = getchar();
    if (ch == '-') w = -1 , ch = getchar();
    while (ch >= '0' && ch <= '9') data = data * 10 + (ch ^ 48), ch = getchar();
    return w * data;
}
#define MAX_N 40005
#define MAX_LOG_N 17 
#define MAX_M 100005
struct Graph {
	int to, next; 
} e[MAX_N << 1];
int fir[MAX_N], e_cnt = 0;
void clearGraph() {
	memset(fir, -1, sizeof(fir));
	e_cnt = 0; 
}
void Add_Edge(int u, int v) {
	e[e_cnt].to = v, e[e_cnt].next = fir[u], fir[u] = e_cnt++; 
} 
int N, M, L, len, A[MAX_M]; 
int c[MAX_N], _c[MAX_N]; 
inline int getB(int x) { return x / L + ((x % L) ? 1 : 0); } 
struct Query { 
	int l, r, add, id;
	bool operator < (const Query &rhs) const { 
		if (getB(l) == getB(rhs.l)) return (getB(l) & 1) ? (r < rhs.r) : (r > rhs.r); 
		else return getB(l) < getB(rhs.l); 
	} 
} q[MAX_M]; 
int P[MAX_N << 1], tot = 0, st[MAX_N], ed[MAX_N], f[MAX_N][MAX_LOG_N], dep[MAX_N]; 
void dfs(int x, int fa) { 
	dep[x] = dep[fa] + 1, P[++tot] = x, st[x] = tot; 
	for (int i = 0; i < 16; i++) f[x][i + 1] = f[f[x][i]][i];
	for (int i = fir[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		f[v][0] = x;
		dfs(v, x); 
	}
	P[++tot] = x, ed[x] = tot; 
}
int LCA(int x, int y) { 
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 16; i >= 0; i--) {
		if (dep[f[x][i]] >= dep[y]) x = f[x][i];
		if (x == y) return x; 
	}
	for (int i = 16; i >= 0; i--) 
		if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0]; 
} 
bool used[MAX_N]; 
int cnt[MAX_N], ans; 
void Add(int x) { 
	if (used[x]) {
		cnt[c[x]]--;
		if (cnt[c[x]] == 0) ans--; 
	} else {
		cnt[c[x]]++;
		if (cnt[c[x]] == 1) ans++; 
	}
	used[x] ^= 1; 
} 
int main () {
	clearGraph(); 
	N = gi(), M = gi(); L = sqrt(N); 
	for (int i = 1; i <= N; i++) c[i] = _c[i] = gi(); 
	sort(&_c[1], &_c[N + 1]); 
	int size = unique(&_c[1], &_c[N + 1]) - _c - 1; 
	for (int i = 1; i <= N; i++) c[i] = lower_bound(&_c[1], &_c[size + 1], c[i]) - _c; 
	for (int i = 1; i < N; i++) { 
		int u = gi(), v = gi(); 
		Add_Edge(u, v); 
		Add_Edge(v, u); 
	} 
	dfs(1, 0); 
	for (int i = 1; i <= M; i++) {
		int l = gi(), r = gi(), lca = LCA(l, r);  
		if (st[r] < st[l]) swap(l, r); 
		if (l == lca) q[i] = (Query){st[l], st[r], 0, i}; 
		else q[i] = (Query){ed[l], st[r], lca, i}; 
	} 
	sort(&q[1], &q[M + 1]); 
	int ql = 1, qr = 0;
	for (int i = 1; i <= M; i++) { 
		while (ql < q[i].l) Add(P[ql]), ++ql;
		while (ql > q[i].l) --ql, Add(P[ql]);
		while (qr < q[i].r) ++qr, Add(P[qr]);
		while (qr > q[i].r) Add(P[qr]), --qr;
		if (q[i].add) Add(q[i].add);
		A[q[i].id] = ans;
		if (q[i].add) Add(q[i].add); 
	}
	for (int i = 1; i <= M; i++) printf("%d\n", A[i]); 
	return 0; 
} 
```

---

## 作者：Piwry (赞：4)

#### 怎么可以没有树分块莫队呢？

~~（话说最初我是从鱼鱼那里看到这个东西的）~~

# 1.树上分块（一种）

upd：话说其实有好多种树分块方法...（分出来块的性质都不一样），这里就讲一种最简单的，只保证块的大小（~~以及一些奇奇怪怪的~~...还是看程序吧）的性质。

首先有一个简单的分块方法：考虑在进入函数时将点入栈，并判断栈元素数量是否超过块大小，若超过就（在函数开头或末尾~~或随便哪处~~，最后把剩下的同一弹出就可以）将栈中所有元素弹出并标号。

（$S$ 代表分块大小）

```cpp
/*栈后边界开（stl那样）*/
void dfs(int u, int fa){
	/*...*/
	/*blablabla*/
	/*...*/
   
	stk[top++] =u;
	if(top == S){
		while(top) chunk[stk[--top]] =totk;/*totchunk(?)*/
		++totk;
	}
}
```

但考虑如果在搜索上一个兄弟子树后没有弹出所有元素，分出来的块就有可能在块内不连续：

（同颜色为一块）

![1](https://cdn.luogu.com.cn/upload/image_hosting/tsg5uaul.png)

（考虑更坏的情况，块基础大小为 $9$）

![3](https://cdn.luogu.com.cn/upload/image_hosting/93tebg11.png)

因此我们需要记录当前点入栈时的栈高度，并且只选择弹出栈位置 "不低于" 当前点的点并分为一块（只取儿子或该节点），这样就可以保证块内部的间隔不会那么远，一个块中间**最远间隔一个节点**。

（图中 $S$ 设为 $5$，图像以下面程序为准）

![2](https://cdn.luogu.com.cn/upload/image_hosting/nnmh859t.png)

```cpp
/*栈后边界仍旧开*/
void dfs(int u, int fa){
	/*入栈也可放在结尾，块大小不会影响只是分出来的图像有点小差异（但仍旧可能隔一个点）*/
	stk[top++] =u;
	int bottom =top-1;
	
	/*...*/
	/*blablabla*/
	/*xxx*/{
		/*dfs();*/
		if(top-bottom >= S){
			++totk;
			while(top != bottom) chunk[stk[--top]] =totk;
		/*这个 while会把高度大于等于 bottom的弹出*/
		}
		/*不可放在尾端，不然分块大小会炸（设想每颗子树节点数都小于 S，见下图）*/
		/*顶部更是不可以，否则完全分不了块*/
	}
	/*...*/
	
	/*可以塞一个特判应对 S为 1的情况（没有必要）*/
}
```

（将判断出栈部分放在尾部，块基础大小为 $4$）

![4](https://cdn.luogu.com.cn/upload/image_hosting/6n3kozys.png)

dfs 后再把栈剩下的节点分到另一块即可（这个块的大小范围是 $[1, S-1]$，dfs 结尾入栈的话可能有 $S$）。

```cpp
++totk;
while(top) chunk[stk[--top]] =totk;
```

但块大小为 $1$ 的时候可能会有些小 bug（叶子不会进入函数中间段），~~不过此时数据范围很小不排序也没事，实在不行~~加个特判就可以。

接下来我们考虑下分块的大小是否正确。

对于 dfs 路径上某点，当搜索完上一个子树，准备搜索下一个子树时，最坏有可能剩下 $S-1$ 个子树点或该点在栈中；若这次仍剩下 $S-1$ 个点，就会形成一个 $2S-2$ 大小的块：这是**最坏情况**，因此块的大小是 $S$ 级别的。

# 2.指针移动

对于排序后的两个询问 $(u, v), (u', v')$，若我们要从 $(u, v)$ 转移到 $(u', v')$，如果直接遍历两条链（$u$ - $v$ 和 $u'$ - $v'$）的话明显是暴力的。但我们可以试着将这组操作转化为 $u$ - $u'$ 和 $v$ - $v'$（就类似序列莫队的移动了）：

设 $S_{u, v}$ 表示路径 $u$ - $v$ 上的所有点； $T_{u, v}$ 表示路径 $u$ - $v$ 上不含 $\text{lca}(u, v)$ 的所有点。且设集合 $\text{xor}$ 操作，$A \text{xor} B=A\cup  B-A\cap B$。设根 $rt$。

可以发现：

$$T_{u', v'}$$

$$=T_{u', v'}\text{xor}T_{u, v}\text{xor}T_{u, v}$$

$$=(S_{u', rt}\text{xor}S_{rt, v'})\text{xor}(S_{u, rt}\text{xor}S_{rt, v})\text{xor}T_{u, v}$$

$$=(S_{u', rt}\text{xor}S_{u, rt})\text{xor}(S_{rt, v'}\text{xor}S_{rt, v})\text{xor}T_{u, v}$$

$$=T_{u, u'}\text{xor}T_{v, v'}\text{xor}T_{u, v}$$

（由集合 $\text{xor}$ 的交换，结合律可得）

$T_{u, v}$ 就是当前的状态（还多了一个 lca）。我们接着设操作 `mov(u1, u2)`，表示对路径 $u1$ - $u2$ 上的点（**不包括 lca**）全部做一次 "xor操作"（如果该点已统计就加入答案，否则就从答案删除），最后再额外删去 $\text{lca}(u, v)$ 的贡献并加上 $\text{lca}(u', v')$ 的贡献即可。这样，我们实际上就是在遍历 $u$ - $u'$ 和 $v$ - $v'$的路径（~~就是一般莫队的操作啦~~）。

（[神鱼的这篇题解](https://www.luogu.com.cn/blog/NaCly-Fish-blog/solution-p4074)有图像解释也可以看看）

```cpp
inline void upd(int pos){
	if(vis[pos] ^=1){ if(++cntcol[col[pos]] == 1) ++ANS; }
	else if(--cntcol[col[pos]] == 0) --ANS;
}

inline void mov(int u1, int u2){
	if(dep[u1] < dep[u2]) u1 ^=u2 ^=u1 ^=u2;/*奇怪的 swap写法*/
	while(dep[u1] > dep[u2]) upd(u1), u1 =f[u1];
	while(u1 != u2) upd(u1), upd(u2), u1 =f[u1], u2 =f[u2];
}
```

最后，如果是带修的话只需判断修改的节点**有没有被算进贡献**就行了。

# 3.\*对r指针的排序

对于 `r` 的排序，其实可以直接按块排，可以证明这样不会过多地增大复杂度：

- 如果是（树上）带修莫队，本来对于同块的 `r` 就不是按确切位置而是 `t` 排序的，因此没有影响。

- 如果是（树上）普通莫队，可以发现这样会使对于每个 `l` 块内 `r` 每次的移动距离最坏增长到 $S$，总共 $mS$；同时换 `l` 块时 `r` 的最坏移动距离 `n` 不变。因此总的复杂度为 $O(mS+(mS+\frac {n^2} S))$，仅仅多了一个 $mS$，且还没有括号序做法的二倍常数。

# 4.CODE

有一个需要注意的点：这里一开始设 `u =v =1` ，所表示的意思是**答案已包含 $u$ - $v$ 路径上的贡献**，因此一开始需要加入点 `1` 的贡献。

另外，代码中的 `lca` 是用重链剖分实现的。

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using std::sort;

const int MAXN =4e4+50, MAXN2 =1e5+50;

int S, n, m;

/*------------------------------Map------------------------------*/

int topl[MAXN], f[MAXN], siz[MAXN], dep[MAXN], ws[MAXN];
int first[MAXN];
int stk[MAXN], top, chunk[MAXN], totk;

struct edge{
	int net, to;
}e[MAXN<<1];

void dfs1(int u, int fa){
	stk[top++] =u;
	int bottom =top-1;
	siz[u] =1, f[u] =fa, dep[u] =dep[fa]+1;
	edge E;
	for(int l =first[u]; l; l =E.net){
		E =e[l];
		if(E.to != fa){
			dfs1(E.to, u), siz[u] +=siz[E.to];
			if(!ws[u] || siz[ws[u]] < siz[E.to]) ws[u] =E.to;
			if(top-bottom >= S){
				++totk;
				while(top != bottom) chunk[stk[--top]] =totk;
			}
		}
	}
	/*尾部可以加一个特判应对块大小 1情况*/
}

void dfs2(int u, int fa){
	topl[u] =(ws[fa] == u) ? topl[fa] : u;
	edge E;
	for(int l =first[u]; l; l =E.net){
		E =e[l];
		if(E.to != fa) dfs2(E.to, u);
	}
}

inline int lca(int x, int y){
	if(dep[topl[x]] < dep[topl[y]]) x ^=y ^=x ^=y;
	while(topl[x] != topl[y]){
		x =f[topl[x]];
		if(dep[topl[x]] < dep[topl[y]]) x ^=y ^=x ^=y;
	}
	if(dep[x] < dep[y]) x ^=y ^=x ^=y;
	return y;
}

inline void addedge(int u, int v, int i){
	edge &E =e[i], &E2 =e[n-1+i];
	E.net =first[u], first[u] =i;
	E.to =v;
	E2.net =first[v], first[v] =n-1+i;
	E2.to =u;
}

/*------------------------------莫队------------------------------*/

int col1[MAXN], col[MAXN], cntcol[MAXN];
bool vis[MAXN];

struct query{
	int u, v, cku, ckv, ord;
}q[MAXN2];

int cmp(query a, query b){
	/*我也不知树上的奇偶优化有多大用，看我 yy的图形应该有一点用的吧..*/
	if(a.cku == b.cku) return (a.cku&1) ? a.ckv < b.ckv : a.ckv > b.ckv;
	else return a.cku < b.cku;
}

int ANS;

inline void upd(int pos){
	if(vis[pos] ^=1){ if(++cntcol[col[pos]] == 1) ++ANS; }
	else if(--cntcol[col[pos]] == 0) --ANS;
}

inline void mov(int u1, int u2){
	if(dep[u1] < dep[u2]) u1 ^=u2 ^=u1 ^=u2;
	while(dep[u1] > dep[u2]) upd(u1), u1 =f[u1];
	while(u1 != u2) upd(u1), upd(u2), u1 =f[u1], u2 =f[u2];
}

/*------------------------------Main------------------------------*/

int ans[MAXN2];
int hsh[MAXN];

int cmp2(int x, int y){
	return col1[x] < col1[y];
}

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	n =read(), m =read();
	for(int i =1; i <= n; ++i) col1[i] =read(), hsh[i] =i;
	sort(hsh+1, hsh+1+n, cmp2);
	int ctot =1; col[hsh[1]] =1;
	for(int i =2; i <= n; ++i){
		if(col1[hsh[i]] != col1[hsh[i-1]]) ++ctot;
		col[hsh[i]] =ctot;
	}
	for(int i =1; i <= n-1; ++i) addedge(read(), read(), i);
	for(int i =0; i < m; ++i) q[i].u =read(), q[i].v =read(), q[i].ord =i;
	S =pow(n, 1.0/2);
	dfs1(1, 1), dfs2(1, 1);
	++totk;
	while(top) chunk[stk[--top]] =totk;
	for(int i =0; i < m; ++i) q[i].cku =chunk[q[i].u], q[i].ckv =chunk[q[i].v];
	sort(q, q+m, cmp);
	
	int u =1, v =1;
	upd(1);/*!*/
	for(int i =0; i < m; ++i){
		query nw =q[i];
		int Lca1 =lca(u, v), Lca2 =lca(nw.u, nw.v);
		mov(u, nw.u), u =nw.u;
		mov(v, nw.v), v =nw.v;
		upd(Lca1), upd(Lca2);
		/*这里直接调用 upd，是因为这函数其实就像一个自动判断的是 add还是 del的综合函数*/
		/*序列莫队也可以这样子用*/
		ans[nw.ord] =ANS;
	}
	for(int i =0; i < m; ++i) printf("%d\n", ans[i]);
}
```


---

## 作者：juju527 (赞：3)

前置知识：莫队

[juju的莫队学习笔记](https://juju527.blog.luogu.org/mu-dui)

[更好的阅读体验](https://blog.csdn.net/zty_ju/article/details/105235632)

### 树上莫队

考虑一个神奇的序：欧拉序

就是dfs的时候不仅记录进栈的时间同时记录出栈的时间

![](https://images2018.cnblogs.com/blog/1101696/201806/1101696-20180625111030297-903825718.png)

借用自为风月马前卒大佬blog的图

它跑出来的一个欧拉序是这样的

1 2 3 6 6 4 4 5 5 3 7 7 2 1

每个点第一次出现代表它在此时进栈，第二次出现代表它在此时出栈

我们可以定义st[i]表示i点的进栈时间，ed[i]表示i点的出栈时间

不妨设dep[x]<=dep[y]

考虑路径有两种情况

**LCA(x,y)==x**

此时我们需要的区间就是st[x]到st[y]或ed[y]到ed[x]的全部

同时该区间所有出现了两次的点都不要

我们思考出现两遍的点代表什么

出现两边证明我们遍历了该点的整棵子树并且x在其之前入栈，y在其之后入栈

那么这个点并不在x到y的路径中

而同时因为x是y的祖先，目前y还没退出去，那么y的所有祖先的出栈点应在更后面

而x之上的祖先在st[x]之前入栈，ed[x]之后出诊，故不影响我们的查询

**LCA(x,y)!=x**

我们需要的区间是ed[x]到st[y]，但由于这段区间不会包含LCA(x,y)，我们还要单独加上LCA(x,y)

我们思考从x退栈的过程，它会往祖先走然后去下一个子树

当遍历到y时，我们可以想象到

从x到lca(不包括lca)的点都出栈了，不在x到y路径的点都遍历了两遍，y到lca(不包括lca)的点都还没出栈

而st[lca]在st[x]之前，ed[lca]在ed[y]之后，lca不会出现在ed[x]到st[y]这个区间里



当我们确定了区间后跑普通莫队即可

而这个莫队是只记录出现奇数次的点的贡献的

无论是不出现还是出现两次都是不计算贡献

注意lca的特殊性

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=40005,maxm=100005;
int block;
struct Query{
	int id;
	int x,y,z;
	bool operator <(Query i)const{
		return x/block==i.x/block?y<i.y:x<i.x;
	}
}q[maxm];
struct node{
	int id,data;
	bool operator <(node i)const{
		return data<i.data;
	}
}a[maxn];
struct Edge{
	int to;
	int nxt;
}e[2*maxn];
int cnt;
int head[maxn];
int c[maxn];
int dep[maxn],f[maxn][21];
int tp=0;
int s[2*maxn],st[maxn],ed[maxn];
int tot[maxn];
int ans=0;
int ANS[maxm];
bool vis[maxn];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
void add(int u,int v){
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
	return ;
}
void dfs(int x,int fa){
	s[++tp]=x;
	st[x]=tp;
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<=20;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i!=-1;i=e[i].nxt){
		int tmp=e[i].to;
		if(tmp==fa)continue;
		dfs(tmp,x);
	}
	s[++tp]=x;
	ed[x]=tp;
	return ;
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
void modify(int x){
	vis[s[x]]^=1;
	if(!vis[s[x]]){
		tot[c[s[x]]]--;
		if(tot[c[s[x]]]==0)ans--;
	}
	else{
		tot[c[s[x]]]++;
		if(tot[c[s[x]]]==1)ans++;
	}
	return ;
}
int main(){
	int n,m;
	n=read();m=read();
	block=sqrt(2*n);
	for(int i=1;i<=n;i++){
		a[i].id=i;
		a[i].data=read();
	}
	sort(a+1,a+n+1);
	int w=0;
	for(int i=1;i<=n;i++){
		if(a[i].data>a[i-1].data)w++;
		c[a[i].id]=w;
	}
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		int p=lca(u,v);
		q[i].id=i;q[i].z=0;
		if(p==u||p==v){
			if(st[v]<st[u])swap(u,v);
			q[i].x=st[u];q[i].y=st[v];
		}
		else{
			if(ed[v]<st[u])swap(u,v);
			q[i].x=ed[u];q[i].y=st[v];q[i].z=p;
		}
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		int id=q[i].id,x=q[i].x,y=q[i].y,z=q[i].z;
		while(l<x)modify(l++);
		while(l>x)modify(--l);
		while(r<y)modify(++r);
		while(r>y)modify(r--);
		if(z)modify(st[z]);
		ANS[id]=ans;
		if(z)modify(st[z]);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ANS[i]);
	return 0;
}

```

---

## 作者：yzhang (赞：3)

### [树上莫队](https://www.cnblogs.com/yzhang-rp-inf/p/9991671.html)qaq

### [原题传送门](https://www.luogu.org/problemnew/show/SP10707)

先重链剖分，顺便求出欧拉序

要求出每个询问的区间

分两种情况

设st[i]<st[j]

- st[i]=lca(i,j)

把st[i]~st[j]欧拉序中更新，位置出现次数为1，跟新，出现次数为2，不跟新（进一次，出一次，相当于它不在路径上）

- st[i]!=lca(i,j)

同理，把ed[i]~st[j]处理，注意特判lca(i,j)

#### 注意：得出结果后要还原lca(i,j)

#### 完整代码

```cpp
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define N 40005
#define M 100005
#define getchar nc
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf; 
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++; 
}
inline int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(register int x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[20];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
inline void Swap(register int &a,register int &b)
{
    a^=b^=a^=b;
}
struct edge{
    int to,next;
}e[N<<1];
int head[N],cnt=0;
inline void add(register int u,register int v)
{
    e[++cnt]=(edge){v,head[u]};
    head[u]=cnt;
}
int n,m;
int a[N],date[N];
int dep[N],top[N],siz[N],son[N],fa[N],st[N],ed[N],pot[N<<1],tot=0;
inline void dfs1(register int x,register int f)
{
    fa[x]=f,siz[x]=1,st[x]=++tot;
    pot[tot]=x;
    for(register int i=head[x];i;i=e[i].next)
        if(e[i].to!=f)
        {
            dep[e[i].to]=dep[x]+1;
            dfs1(e[i].to,x);
            siz[x]+=siz[e[i].to];
            if(siz[e[i].to]>siz[son[x]])
                son[x]=e[i].to;
        }
    ed[x]=++tot;
    pot[tot]=x;
}
inline void dfs2(register int x,register int topf)
{
    top[x]=topf;
    if(son[x])
        dfs2(son[x],topf);
    for(register int i=head[x];i;i=e[i].next)
        if(e[i].to!=fa[x]&&e[i].to!=son[x])
            dfs2(e[i].to,e[i].to);
}
inline int Getlca(register int x,register int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            Swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
struct query{
    int l,r,id,lca;
}q[M];
int bel[N<<1],block;
inline bool cmp(register query a,register query b)
{
    return bel[a.l]!=bel[b.l]?a.l<b.l:((bel[a.l]&1)?a.r<b.r:a.r>b.r);
}
int ans[M],p[N],vis[N],res=0;
inline void add(register int x)
{
    res+=!p[x]++;
}
inline void del(register int x)
{
    res-=!--p[x];
}
inline void Add(register int x)
{
    vis[x]?del(a[x]):add(a[x]);
    vis[x]^=1;
}
int main()
{
    n=read(),m=read();
    block=sqrt(n);
    for(register int i=1;i<=n;++i)
        a[i]=date[i]=read();
    for(register int i=1;i<=(n<<1);++i)
        bel[i]=i/block+1;
    sort(date+1,date+1+n);
    int num=unique(date+1,date+1+n)-date-1;
    for(register int i=1;i<=n;++i)
        a[i]=lower_bound(date+1,date+1+num,a[i])-date;
    for(register int i=1;i<n;++i)
    {
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dep[1]=1;
    dfs1(1,0);
    dfs2(1,1);
    for(register int i=1;i<=m;++i)
    {
        int x=read(),y=read();
        if(st[x]>st[y])
            Swap(x,y);
        int lcaa=Getlca(x,y);
        q[i].id=i;
        if(lcaa==x)
            q[i].l=st[x],q[i].r=st[y];
        else
            q[i].l=ed[x],q[i].r=st[y],q[i].lca=lcaa;
    }
    sort(q+1,q+1+m,cmp);
    int l=1,r=0;
    for(register int i=1;i<=m;++i)
    {
        int ll=q[i].l,rr=q[i].r;
        while(l<ll)
            Add(pot[l++]);
        while(l>ll)
            Add(pot[--l]);
        while(r<rr)
            Add(pot[++r]);
        while(r>rr)
            Add(pot[r--]);
        if(q[i].lca)
            Add(q[i].lca);
        ans[q[i].id]=res;
        if(q[i].lca)
            Add(q[i].lca);
    }
    for(register int i=1;i<=m;++i)
        write(ans[i]),puts("");
    return 0;
} 
```




---

## 作者：xgzc (赞：3)

### 题解

这道题目是树上莫队练手题

我们知道莫队是离线的，但是万一强制在线就凉凉了

于是我们就需要一些操作：树分块

看到这个图：

![](https://i.loli.net/2019/02/03/5c56666500ba1.png)

这里有$7$个点，我们每隔$2$深度分块

但是我们要保证分块的连续性，于是分成了$(1,2)(7,6,3)(4,5)$三块

现在给了你两个将询问的点$u,v(dep[u]>dep[v])$，分类讨论：

1. 两个点在同一个块内

   直接暴力

2. 两个点不在同一个块内

   > 这种情况比较复杂，记一个块的根为$rt[i]$，则它到另外所有点的答案我们可以很轻松地
   > 统计出来，只需要对于每个$rt[i]$暴力统计一遍就可以了。
   >
   > 那么现在我们要考虑的只有$u$到它的块的根$x$路径上是否会对答案产生贡献：
   > 对于这个，我们可以将这个分块可持久化，维护这个点的颜色在它的祖先中出现最深的位置
   > 的深度，那么一个块只需继承上面的块，并将在这个块中颜色的答案更新，因为那个颜色如
   > 果出现在这个位置，那么答案肯定更优。
   >
   > 有了上面的铺垫，那我们只需对$u\to x$上的点暴力算它的深度是否超过$\mathrm{LCA}(u, v)$即可

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<cmath>
#include<algorithm>
#define RG register
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define clear(x, y) memset(x, y, sizeof(x))

inline int read()
{
	int data = 0, w = 1; char ch = getchar();
	while(ch != '-' && (!isdigit(ch))) ch = getchar();
	if(ch == '-') w = -1, ch = getchar();
	while(isdigit(ch)) data = data * 10 + (ch ^ 48), ch = getchar();
	return data * w;
}

const int maxn(40010), SQRT(210);
struct edge { int next, to; } e[maxn << 1];
int head[maxn], e_num;
inline void add_edge(int from, int to)
{
	e[++e_num] = (edge) {head[from], to};
	head[from] = e_num;
}

int n, m, Len, a[maxn], b[maxn], _a[maxn], r[maxn];
int P[maxn][SQRT], A[SQRT][maxn], fa[maxn], dep[maxn];
int q[maxn], belong[maxn], top, cnt, SIZE, root[maxn];
int c[maxn], Ans;

struct Block
{
	int a[SQRT]; void insert(const Block&, int, int);
	int &operator [] (const int &x) { return P[a[b[x]]][r[x]]; }
	const int &operator [] (const int &x) const { return P[a[b[x]]][r[x]]; }
} s[maxn];

void Block::insert(const Block &rhs, int x, int d)
{
	int blk = b[x], t = r[x];
	memcpy(a, rhs.a, sizeof(a));
	memcpy(P[++SIZE], P[a[blk]], sizeof(P[0]));
	P[a[blk] = SIZE][t] = d;
}

namespace Tree
{
	int belong[maxn], heavy[maxn], size[maxn];
	void dfs(int x, int chain)
	{
		belong[x] = chain;
		if(!heavy[x]) return;
		dfs(heavy[x], chain);
		for(RG int i = head[x]; i; i = e[i].next)
		{
			int to = e[i].to;
			if(to == fa[x] || to == heavy[x]) continue;
			dfs(to, to);
		}
	}

	int LCA(int x, int y)
	{
		while(belong[x] != belong[y])
		{
			if(x[belong][dep] < y[belong][dep]) std::swap(x, y);
			x = x[belong][fa];
		}
		return dep[x] < dep[y] ? x : y;
	}
}

int dfs(int x, int f)
{
	using Tree::size; using Tree::heavy;
	fa[x] = f, size[x] = 1;
	s[x].insert(s[f], a[x], dep[x] = dep[f] + 1);
	q[++top] = x; int maxd = dep[x], p = top;
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to; if(to == f) continue;
		maxd = std::max(maxd, dfs(to, x)); size[x] += size[to];
		if(size[heavy[x]] < size[to]) heavy[x] = to;
	}

	if(maxd - dep[x] >= Len || p == 1)
	{
		root[++cnt] = x;
		for(RG int i = p; i <= top; i++) belong[q[i]] = cnt;
		top = p - 1; return dep[x] - 1;
	}
	return maxd;
}

void Pre(int x, int f, int *s)
{ 
	if(!c[a[x]]++) ++Ans; s[x] = Ans;
	for(RG int i = head[x]; i; i = e[i].next) if(e[i].to != f)
		Pre(e[i].to, x, s);
	if(!--c[a[x]]) --Ans;
}

int Solve1(int x, int y)
{
	for(top = Ans = 0; x != y; x = fa[x])
	{
		if(dep[x] < dep[y]) std::swap(x, y);
		if(!c[q[++top] = a[x]]) c[a[x]] = 1, ++Ans;
	}
	for(Ans += !c[a[x]]; top;) c[q[top--]] = 0;
	return Ans;
}

int Solve2(int x, int y)
{
	if(dep[root[belong[x]]] < dep[root[belong[y]]]) std::swap(x, y);
	int x1 = root[belong[x]], d = dep[Tree::LCA(x, y)]; Ans = A[belong[x]][y];
	for(top = 0; x != x1; x = fa[x])
		if(!c[a[x]] && s[x1][a[x]] < d && s[y][a[x]] < d)
			c[q[++top] = a[x]] = 1, ++Ans;
	while(top) c[q[top--]] = 0;
	return Ans;
}

int main()
{
	n = read(), m = read(), Len = sqrt(n) - 1;
	for(RG int i = 1; i <= n; i++) b[i] = (i - 1) / Len + 1, r[i] = i % Len;
	for(RG int i = 1; i <= n; i++) a[i] = _a[i] = read();
	std::sort(_a + 1, _a + n + 1);
	int tot = std::unique(_a + 1, _a + n + 1) - _a - 1;
	for(RG int i = 1; i <= n; i++)
		a[i] = std::lower_bound(_a + 1, _a + tot + 1, a[i]) - _a;
	for(RG int i = 1, x, y; i < n; i++) x = read(), y = read(),
		add_edge(x, y), add_edge(y, x);
	top = 0, dfs(1, 0), Tree::dfs(1, 1);
	for(RG int i = 1; i <= cnt; i++) Pre(root[i], 0, A[i]); 
	int ans = 0; while(m--)
	{
		int x = read(), y = read();
		printf("%d\n", ans = (belong[x] == belong[y] ?
					Solve1(x, y) : Solve2(x, y)));
	}
	return 0;
}
```

---

## 作者：殇雪 (赞：2)

我们来讲一下树上莫队。

   前置技能：莫队，括号序列

   我们如果要维护子树的信息的话，只要把树展开成DFS序就好了。

   那么如果是路径呢？

               1

            /   |    \

          2     3     4

                  |

                  5

   我们在进入和退出一个节点时都把这个点扔到序列里，那么我们发现上面这个数的序列为：

        1 2 2 3 5 5 3 4 4 1

   我们记一个点的第一次出现的位置为st[i],第二次为ed[i]

     那么比如我们要找1 到 5 的路径， 我们取 st[1] 到 st[5] 这一段区间，我们发现在 1-5上的点出现了一次，而不在这条路径的点出现了偶数次。

    -> 一条 从 a 连向其子孙 b 的路径，我们可以取 st[a] 到 st[b] 的区间。（st[a]<=st[b]）

    若我们要从2 到 5 呢？

    我们取ed[2]到st[5],我们发现在 2-5上的点出现了一次，而不在这条路径的点出现了偶数次。但是LCA 1却没有出现，那么我们在统计答案的时候把这玩意加上就好了。

    -> 一般的， 一条 由 a  连向 非子孙 非祖宗点 b的路径，我们可以取 ed[a] 到 st[b] 的区间再加上lca 对答案的贡献。（st[a]<=st[b]）
    这道题显然可以这样维护：
    ```
[代码在这里](http://www.cnblogs.com/rrsb/p/8672557.html)

---

## 作者：VTloBong (赞：0)

>我有一莫队，可以过十万。 

# 思路
看到这种询问与区间内某个数出现的次数有关的题，很容易想起莫队。
但此题的询问是在树上，所以我们需要把树转化为线性结构。  
通常把树转化为线性结构要利用dfs序,但dfs序并不适用于莫队。  
好在天无绝人之路，dfs序不可用，但我们还有欧拉序。   
## 1.欧拉序
dfs序为什么不适用于莫队？   
在思考这个问题之前，我们不妨先想一下dfs序是什么。  
dfs序,顾名思义，指每个节点在dfs深度优先遍历中的进栈的时间戳序列。一条树上简单路径在dfs序上被分为几段不相交的区间，因此，dfs序适用于维护的信息可以由区间合并而来的情况。   
而欧拉序，即每个节点在dfs深度优先遍历中的进出栈的时间戳序列。如果把有进有出的点忽略，一条树上简单路径在欧拉序上就成为了一段连续的区间。因此，欧拉序适用于维护的信息可以由区间加减相邻元素而调整的情况。       
**口胡的结论：dfs序适用于维护的信息可以由区间合并而来的情，而欧拉序适用于维护的信息可以由区间加减相邻元素而调整的情况。**（欢迎打脸）
## 2.假树上莫队
我们在点进栈时记一个时间戳st，出栈时再记一个时间戳ed。  
每次询问的节点u,v（不妨设 $st_u<st_v$ ）有两种情况：
1. u是v的祖先，路径在欧拉序上对应的区间为 $[st_u,st_v]$ ;
2. u不是v的祖先，路径在欧拉序上对应的区间为 $[ed_u,st_v]$ ，再加上lca的贡献。  

我们可以树链剖分求lca,顺便在预处理时求出欧拉序。   
开一个数组记录节点i在不在目前区间中，区间调整时，1表示需要删除，0表示需要加入。
# 代码
前方大常数警告  
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
//#define int long long
const int maxn=400005,sqrn=1005;
//离散化：
struct number{
	int data,id;
}lsh[maxn];
bool cmp1(number x,number y){
	return x.data <y.data ;
} 
//树剖：
struct edge{
	int to,next;
}e[maxn<<1];
int head[maxn],dfn[maxn<<1],st[maxn],ed[maxn],fa[maxn],dep[maxn],s[maxn],son[maxn],top[maxn];
inline void add_edge(int u,int v,int id){
	e[id].to=v,e[id].next=head[u],head[u]=id;
}
inline void build(int m){
	int u,v;m<<=1;
	for(register int i=1;i<=m;i+=2)
		scanf("%d%d",&u,&v),add_edge(u,v,i),add_edge(v,u,i+1);
}
inline void dfs1(int x){
	st[x]=++dfn[0],dfn[dfn[0]]=x,dep[x]=dep[fa[x]]+1,s[x]=1,son[x]=0;
	for(register int l=head[x],v;l;l=e[l].next){
		v=e[l].to;
		if(v==fa[x])continue;
		fa[v]=x,dfs1(v),s[x]+=s[v];
		if(s[v]>s[son[x]])son[x]=v;
	}
	ed[x]=++dfn[0],dfn[dfn[0]]=x;
}
inline void dfs2(int x){
	if(son[x])top[son[x]]=top[x],dfs2(son[x]);
	for(register int l=head[x],v;l;l=e[l].next){
		v=e[l].to;
		if(v==fa[x]||v==son[x])continue;
		top[v]=v,dfs2(v);
	}
}
inline int _lca(int u,int v){
	int t;
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]])t=u,u=v,v=t;
		u=fa[top[u]];
	}return dep[u]>dep[v]?v:u;
}
//莫队： 
struct query{
	int l,r,lca,id;
}q[maxn];
int a[maxn],cnt[maxn<<1],ans,ls=1,rs,size,book[maxn],f[200000],n,m;
bool cmp2(query x,query y){
    return (x.l-1)/size==(y.l-1)/size?(((x.l-1)/size)&1?x.r<y.r:x.r>y.r ):(x.l-1)/size<(y.l-1)/size; 
}
inline void add(int k){
	if(!cnt[a[k]])ans++;
	cnt[a[k]]++;
}
inline void del(int k){
	cnt[a[k]]--;
	if(!cnt[a[k]])ans--;
}
inline void change(int k){
	book[k]?del(k):add(k);
	book[k]^=1;
}
main(){
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
		lsh[i].id=i,scanf("%d",&lsh[i].data);
	sort(lsh+1,lsh+n+1,cmp1);
	for(int i=1,num=0;i<=n;i++){
		if(lsh[i].data!=lsh[i-1].data||i==1)num++;
		a[lsh[i].id]=num;
	}for(size=1;size*size<n;size++);
	f[1]=0,dfn[0]=0,top[1]=1,build(n-1),dfs1(1),dfs2(1);
	for(register int i=1,u,v,t;i<=m;++i){
		q[i].id=i,scanf("%d%d",&u,&v),q[i].lca=_lca(u,v);
		if(st[u]>st[v])t=u,u=v,v=t;
		if(q[i].lca==u)q[i].l=st[u],q[i].lca=0;
		else q[i].l=ed[u];
		q[i].r=st[v];
	}sort(q+1,q+m+1,cmp2);
	for(register int i=1;i<=m;++i){
		int nl=q[i].l ,nr=q[i].r ;
		while(rs<nr)rs++,change(dfn[rs]);
		while(ls>nl)ls--,change(dfn[ls]);
		while(ls<nl)change(dfn[ls]),ls++;
		while(rs>nr)change(dfn[rs]),rs--;
		if(q[i].lca)change(q[i].lca);
        f[q[i].id]=ans;
        if(q[i].lca)change(q[i].lca);
	}for(register int i=1;i<=m;++i)printf("%d\n",f[i]);
	return 0;
} 





---

