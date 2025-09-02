# DISQUERY - Distance Query

## 题目描述

 [English](/problems/DISQUERY/en/) [Vietnamese](/problems/DISQUERY/vn/)The traffic network in a country consists of N cities (labeled with integers from 1 to N) and N-1 roads connecting the cities. There is a unique path between each pair of different cities, and we know the exact length of each road.

Write a program that will, for each of the K given pairs of cities, find the length of the shortest and the length of the longest road on the path between the two cities.

### Input

The first line of input contains an integer N, 2

The length of each road will be a positive integer less than or equal to 1 000 000.   
 The next line contains an integer K, 1

### Output

Each of the K lines of output should contain two integers – the lengths from the task description for the corresponding pair of the cities.


## 样例 #1

### 输入

```
5
2 3 100
4 3 200
1 5 150
1 3 50
3
2 4
3 5
1 2
```

### 输出

```
100 200
50 150
50 100
```

## 样例 #2

### 输入

```
7
3 6 4
1 7 1
1 3 2
1 2 6
2 5 4
2 4 4
5
6 4
7 6
1 2
1 3
3 5
```

### 输出

```
2 6
1 4
6 6
2 2
2 6
```

# 题解

## 作者：Bitter_Tea (赞：5)

题目大意:

给有$n$个节点的树, 树上边有边权. 再给定$q$组询问, 每次询问两个点路径上的最小值和最大值.$n,q<=10^5$。

我采用的是最简单的**树上倍增**求$Lca$。

我们设$f(x,k)$表示$x$向上跳$2^k$条边到达的节点。那么$f(x,0)$就是$x$的父亲节点。


首先我们预处理出每个节点的深度$dep$，和每个节点的父亲节点。

代码如下:
```cpp
void dfs(int x,int fa,int deep)
{
	dep[x]=deep;
	for(int i=fir[x];i;i=e[i].nxt)
	{
		int p=e[i].to;
		if(p==fa) continue;
		dfs(p,x,deep+1);
		f[p][0]=x;
	}
}
```


我们用类似于状态转移的式子求节点$x$的其他祖先:

$f(x,k)=f(f(x,k-1))(k-1)$

此式子的意思是~~爸爸的爸爸是爷爷~~,$x$节点向上跳$2^{k-1}$条边，再向上跳$2^{k-1}$条边就到$f(x,k)$了。

代码如下:
```cpp
void dp()
{
	for(int i=1;i<=D;i++)//先枚举跳的次方步
	for(int j=1;j<=n;j++)//再枚举节点
	f[j][i]=f[ f[j][i-1] ][i-1];
	
}
```

以上部分是预处理

然后我们便可以对每次询问实现$O(logn)$的回答:

对于节点$a,b$，我们不妨设$dep_a>=dep_b$

用二进制的思想先把$a,b$跳至同一深度，$a$尝试跳$2^i$步，
如果深度比$dep_b$小，我们不跳，反之则令$a=f(a,i)$，直至到达同一深度，此时如果节点$a$和节点$b$是同一个点，那么$Lca$就是$b$

我们让$a,b$一起向上跳，尝试跳$2^i$步，如果发现$f(a,i)==f(b,i)$，那么我们不跳，因为我们不确保是否正好是$Lca$，反之令$a=f(a,i),b=f(b,i)$。

那么最后$a,b$就差一步就会跳到同一节点，此时的$f(a,0)$就是$Lca$。

代码如下:

```cpp
int lca(int a,int b)
{
	if(dep[a]<dep[b]) swap(a,b);
	int x=dep[a]-dep[b];
	for(int i=D;i>=0;i--)//a跳
	if(x&(1<<i)) a=f[a][i];
	if(a==b) return a;
	for(int i=D;i>=0;i--)//a,b一起跳
	{
		if(f[a][i]==f[b][i]) continue;
		b=f[b][i];a=f[a][i];
	}
	return f[a][0];
}
```

然后此题就很简单了:

我们只需要在预处理的同时记录出节点$x$向上跳$2^k$条边过程中最大的边$d_{max}(x,k)$和最小边$d_{min}(x,k)$。

在转移过程中同时进行转移，再在求$Lca$的过程中顺便求出即可

$Code$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=1e5+5,D=17;
struct D{int nxt,to,w;}e[N*2];
int fir[N],tot,dep[N];
int f[N][18],d_max[N][18],d_min[N][18];
int n,Q;
void add(int x,int y,int z)
{
	e[++tot].nxt=fir[x];
	e[tot].to=y;
	e[tot].w=z;
	fir[x]=tot;
}
void dfs(int x,int fa,int deep)
{
	dep[x]=deep;
	for(int i=fir[x];i;i=e[i].nxt)
	{
		int p=e[i].to;
		if(p==fa) continue;
		dfs(p,x,deep+1);
		f[p][0]=x;
		d_max[p][0]=e[i].w;
		d_min[p][0]=e[i].w;
	}
}
void dp()
{
	for(int i=1;i<=D;i++)
	for(int j=1;j<=n;j++)
	{
		f[j][i]=f[ f[j][i-1] ][i-1];
		d_max[j][i]=max(d_max[j][i-1],d_max[ f[j][i-1] ][i-1]);
		d_min[j][i]=min(d_min[j][i-1],d_min[ f[j][i-1] ][i-1]);
	}
}
int lca(int a,int b,int z)
{
	int dmax=0,dmin=2147483647;
	if(dep[a]<dep[b]) swap(a,b);
	int x=dep[a]-dep[b];
	for(int i=D;i>=0;i--)
	if(x&(1<<i))
	{
		dmax=max(d_max[a][i],dmax);
		dmin=min(d_min[a][i],dmin);
		a=f[a][i];
	}
	if(a==b)
	{
		if(z==1) return dmax;
		if(z==2) return dmin;
	}
	for(int i=D;i>=0;i--)
	{
		if(f[a][i]==f[b][i]) continue;
		dmax=max(max(d_max[a][i],d_max[b][i]),dmax);
		dmin=min(min(d_min[a][i],d_min[b][i]),dmin);
		b=f[b][i];a=f[a][i];
	}
	dmax=max(max(d_max[a][0],d_max[b][0]),dmax);
	dmin=min(min(d_min[a][0],d_min[b][0]),dmin);
	if(z==1) return dmax;
	return dmin;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	dfs(1,0,1);dp();
	scanf("%d",&Q);
	while(Q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d %d\n",lca(x,y,2),lca(x,y,1));
	}
	return 0;
}
```
~~码字不易，留下你的赞可好~~







---

## 作者：Sooke (赞：3)

### 解题思路

这道题有比较多的做法，树链剖分 $+$ 线段树，$LCT$ 等都能做，但前者有两个 $\log$，后者常数较大，因此这里给出一个 $\log$ 跑得飞快的树链剖分 $+ ST$ 表的做法。

首先，**化边权为点权**，这个只需要从任意结点开始 $dfs$ 一遍，把边权转到**所连的子结点**就行了。

之后，维护**固定**树上的路径，树链剖分当然绰绰有余，现在问题是如何求一条重链上权值最小值和最大值。因为没有修改，显然这是 $ST$ 表的特长，用类似线段树的方法，在以时间戳为下标的 $ST$ 表中搞。

接下来就是两个模板结合的事儿了，注意细节。

### 代码实现

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

inline int read() {
    char c = getchar(); int n = 0; bool f = false;
    while (c < '0' || c > '9') { if (c == '-') { f = true; } c = getchar(); }
    while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
    return f ? -n : n;
}

const int maxN = 200005, maxE = maxN << 1, maxLog = 23;

int n, m, t, logN, fth[maxN], dep[maxN], siz[maxN], son[maxN], val[maxN], dfn[maxN], top[maxN], min[maxLog][maxN], max[maxLog][maxN], g[maxN];

struct List {
    int len, fst[maxN], nxt[maxE], v[maxE], w[maxE];
    
    List() { memset(fst, -1, sizeof(fst)); }
    inline void insert(int u, int vv, int ww) { v[len] = vv, w[len] = ww, nxt[len] = fst[u], fst[u] = len++; }
    inline void connect(int u, int vv, int ww) { insert(u, vv, ww), insert(vv, u, ww); }
} ls;

void dfs1(int u, int fa) {
    fth[u] = fa; dep[u] = dep[fa] + 1; siz[u] = 1;
    for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) {
        int v = ls.v[i], w = ls.w[i];
        if (v != fa) {
            val[v] = w; dfs1(v, u); siz[u] += siz[v];
            if (siz[son[u]] < siz[v]) { son[u] = v; }
        }
    }
}
void dfs2(int u, int p) {
    top[u] = p; dfn[u] = ++t; min[0][t] = max[0][t] = val[u];
    if (son[u]) { dfs2(son[u], p); }
    for (int i = ls.fst[u]; ~i; i = ls.nxt[i]) {
        int v = ls.v[i];
        if (v != fth[u] && v != son[u]) { dfs2(v, v); }   
    }
}

void buildST() {
    for (int i = 1; i <= logN; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) { min[i][j] = std::min(min[i - 1][j], min[i - 1][j + (1 << i - 1)]); max[i][j] = std::max(max[i - 1][j], max[i - 1][j + (1 << i - 1)]); }
    }
}
inline void queryST(int l, int r, int &resMin, int &resMax) {
    if (l > r) { return; } int logLen = g[r - l + 1];
    resMin = std::min(resMin, std::min(min[logLen][l], min[logLen][r - (1 << logLen) + 1]));
    resMax = std::max(resMax, std::max(max[logLen][l], max[logLen][r - (1 << logLen) + 1]));
}

inline void query(int u, int v) {
    int ansMin = 1e9, ansMax = -1e9;
    while (top[u] != top[v]) {
        if (dep[top[u]] >= dep[top[v]]) { queryST(dfn[top[u]], dfn[u], ansMin, ansMax); u = fth[top[u]]; }
        else { queryST(dfn[top[v]], dfn[v], ansMin, ansMax); v = fth[top[v]]; }
    }
    if (dep[u] < dep[v]) { queryST(dfn[u] + 1, dfn[v], ansMin, ansMax); } else { queryST(dfn[v] + 1, dfn[u], ansMin, ansMax); }
    printf("%d %d\n", ansMin, ansMax);
}

int main() {
    n = read(); while (1 << logN + 1 <= n) { logN++; }
    for (int i = 1; i <= n; i++) { g[i] = log(i) / log(2.0); }
    for (int i = 2; i <= n; i++) { int u = read(), v = read(); ls.connect(u, v, read()); }
    dfs1(1, 0); dfs2(1, 1); buildST();
    for (m = read(); m; m--) { query(read(), read()); }
    return 0;
}
```

---

## 作者：zjc23 (赞：3)

errr,这是我们今天一道考试题。

考场做法：树链剖分

那么问题来了，普通的树剖只只支持维护点权，而这题是边权

怎么办呢？

我们假定树的根为一

对于每条边，把他的边权给到、它连接的两点中深度更深的点就可以了

为什么这样是对的呢

errr，因为给深度浅的会有冲突

这样的话根1是没有点权的

所以只需要从2到n建树就可以了

统计答案的时候只需要不计算两点LCA的点权就可以了

下面是代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define INF 1e9

const int N = 100005;

int to[N<<1],head[N],nex[N<<1],ce;
int val[N<<1];
int dfn[N],top[N],fa[N],vall[N],dep[N];
int siz[N],son[N],a[N];
int n,m,num;

void add(int u,int v,int w){
	to[++ce] = v;nex[ce] = head[u],head[u] = ce;val[ce] = w;
}

void dfs(int x){//找重儿子
	siz[x] = 1;
	for(int i=head[x];i;i=nex[i]){
		int y = to[i];
		if(siz[y])continue;
		fa[y] = x;
		vall[y] = val[i];
		dep[y] = dep[x]+1;
		dfs(y);
		siz[x] += siz[y];
		if(!son[x] || siz[son[x]] < siz[y])son[x] = y;
	}
}

void dfss(int x,int Top){//搞时间戳
	dfn[x] = ++num;a[num] = x;
	top[x] = Top;
	if(!son[x])return;
	dfss(son[x],Top);
	for(int i=head[x];i;i=nex[i]){
		int y = to[i];
		if(y == fa[x] || y == son[x])continue;
		dfss(y,y);
	}
}

struct Node{
	int maxx,minn;
}v[N<<2];

void pushup(int rt){
	v[rt].maxx = max(v[rt<<1].maxx,v[rt<<1|1].maxx);
	v[rt].minn = min(v[rt<<1].minn,v[rt<<1|1].minn);
}

void plant(int l,int r,int rt){//建树
	if(l == r){
		v[rt].maxx = v[rt].minn = vall[a[l]];
		return;
	}
	int mid = (l+r)>>1;
	plant(l,mid,rt<<1);
	plant(mid+1,r,rt<<1|1);
	pushup(rt);
}

Node search(int L,int R,int l,int r,int rt){//找区间最大最小值
	if(L <= l && r <= R)
		return v[rt];

	int mid = (l+r)>>1;
	Node ans;ans.maxx = 0,ans.minn = INF;
	if(R <= mid)ans = search(L,R,l,mid,rt<<1);
	else if(L > mid)ans = search(L,R,mid+1,r,rt<<1|1);
	else {
		Node LL = search(L,R,l,mid,rt<<1);
		Node RR = search(L,R,mid+1,r,rt<<1|1);
		ans.minn = min(ans.minn,min(LL.minn,RR.minn));
		ans.maxx = max(ans.maxx,max(LL.maxx,RR.maxx));
	}
	return ans;
}

Node get(int x,int y){//找x到y路径上的最大最小值
	Node res;
	res.maxx = 0,res.minn = INF;
	while(top[x] != top[y]){
		if(dep[top[x]] > dep[top[y]])swap(x,y);
		Node err = search(dfn[top[y]],dfn[y],2,n,1);
		res.maxx = max(res.maxx,err.maxx);
		res.minn = min(res.minn,err.minn);
		y = fa[top[y]];
	}
	if(x == y)return res;
	if(dep[x] > dep[y])swap(x,y);
	Node err = search(dfn[x]+1,dfn[y],2,n,1);//统计dfn[x]+1到dfn[y]的就可以了
	res.maxx = max(res.maxx,err.maxx);
	res.minn = min(res.minn,err.minn);
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	dep[1] = 1;
	dfs(1);
	dfss(1,1);
	plant(2,n,1);
	scanf("%d",&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		Node zz_plays_ass = get(x,y);
		printf("%d %d\n",zz_plays_ass.minn,zz_plays_ass.maxx);
	}
	return 0;
}

```

~~不过这道题写倍增LCA更简单~~

祝各位NOIp2018rp++!

---

## 作者：Holy_Push (赞：3)

虽然本题我第一反应也是树剖，但人家没有修改何必用到树剖和LCT呢~~~ 而且边权不好处理对吧

（当然是更好打的倍增了）

我们倍增找LCA的时候，是设fa[i][j]表示点i向上2^j的父亲，同理，我们可以设MAX[i][j]表示点i向上2^j条边的边权最大值，MIN[i][j]表示点i向上2^j条边的边权最小值，然后查询的时候倍增向上跳就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=998244353,N=100002,LOG=20;

int n,maxdeep,fa[N][LOG],MAX[N][LOG],MIN[N][LOG],w;
int edge[N<<1],nxt[N<<1],first[N<<1],dist[N<<1],deep[N];

void read(int &x)
{
	x=0;char s=getchar();
	while (!isdigit(s)) s=getchar();
	while (isdigit(s)) {x=(x<<1)+(x<<3)+s-'0';s=getchar();}
}

void write(int x)
{
	int len=0,a[20];
	while (x) {a[++len]=x%10;x/=10;}
	if (!len) a[++len]=0;
	for (int i=len;i;i--) putchar(a[i]+48);
}

void add(int x,int y,int z)
{
	edge[++w]=y,nxt[w]=first[x],first[x]=w;dist[w]=z;
}

void dfs(int x,int fat)
{
	fa[x][0]=fat;
	for (int i=first[x];i;i=nxt[i])
		if (edge[i]!=fat) 
		{
			deep[edge[i]]=deep[x]+1;
			dfs(edge[i],x);
			MAX[edge[i]][0]=MIN[edge[i]][0]=dist[i];
		}
}

void LCA(int x,int y)
{
	if (x==y) {puts("0 0");return;}
	if (deep[x]<deep[y]) swap(x,y);
	int Max=-INF,Min=INF;
	for (int i=maxdeep;i>=0;i--)
		if (deep[fa[x][i]]>=deep[y])
		{
			Max=max(Max,MAX[x][i]);Min=min(Min,MIN[x][i]);
			x=fa[x][i];
		}
	if (x==y) {write(Min),putchar(' '),write(Max),putchar('\n');return;}
	for (int i=maxdeep;i>=0;i--)
		if (fa[x][i]!=fa[y][i])
		{
			Max=max(Max,MAX[x][i]);Min=min(Min,MIN[x][i]);
			Max=max(Max,MAX[y][i]);Min=min(Min,MIN[y][i]);
			x=fa[x][i];y=fa[y][i];
		}
	Max=max(Max,MAX[x][0]);Min=min(Min,MIN[x][0]);
	Max=max(Max,MAX[y][0]);Min=min(Min,MIN[y][0]);
	write(Min),putchar(' '),write(Max),putchar('\n');
}

int main()
{
	read(n);
	for (int i=1;i<n;i++)
	{
		int u,v,z;
		read(u),read(v),read(z);
		add(u,v,z);add(v,u,z);
	}
	deep[1]=1;dfs(1,0);MIN[1][0]=INF;
	for (int i=1;i<=n;i++)
	{
		bool flag=true;
		for (int j=1;j<=n;j++)
		{
			fa[j][i]=fa[fa[j][i-1]][i-1];
			MAX[j][i]=max(MAX[j][i-1],MAX[fa[j][i-1]][i-1]);
			MIN[j][i]=min(MIN[j][i-1],MIN[fa[j][i-1]][i-1]);
			if (fa[j][i]) flag=false;
				else MIN[j][i]=INF;
		}
		if (flag) {maxdeep=i;break;}
	}
	int Q;read(Q);
	for (Q;Q;--Q)
	{
		int u,v;
		read(u);read(v);
		LCA(u,v);
	}
}
```


---

## 作者：JK_LOVER (赞：2)

## 题意
在树上求出一条路径的最大值和最小值。
## 分析
像树上的简单路径问题一般考虑树链剖分和 $LCT$ 。但是如果树链剖分再加个线段树时间复杂度为 $O(n\log n \times \log n)$ 。但是常数比 $LCT$ 小。这里考虑 $LCT$ 的 $O(n\log n)$ 做法。

- 因为这道题是考虑边权的最大最小，所以还需要拆边成点。
- 边和点的考虑是不同的，可以参见代码。
- $U$ 是这条路径的边的集合。
$$
ans_{max} = \max(ans_{max},val[i]) (i \in U)
$$
$$
ans_{min} = \max(ans_{min},val[i]) (i \in U)
$$
$LCT$ 的码量是比树链剖分小得多的。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 410000;
int c[N][2],f[N],n,m,mi[N],mx[N],val[N];
bool r[N];
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
inline void write(int x)
{
	if(x>9)write(x/10);
    putchar(x%10+'0');
}

void pushr(int x)
{
	swap(c[x][1],c[x][0]);
	r[x] ^= 1;
}
void pushdown(int x)
{
	if(r[x])
	{
		if(c[x][1]) pushr(c[x][1]);
		if(c[x][0]) pushr(c[x][0]);
		r[x] = 0;
	}		
}
void pushup(int x)
{
	if(x > n)
	mx[x] = mi[x] = val[x];
	else 
	mx[x] = 0,mi[x] = 0x3f3f3f3f;
	if(c[x][1]) {mx[x] = max(mx[x],mx[c[x][1]]) ; mi[x] = min(mi[x],mi[c[x][1]]);}
	if(c[x][0]) {mx[x] = max(mx[x],mx[c[x][0]]) ; mi[x] = min(mi[x],mi[c[x][0]]);}
}
bool nroot(int x)
{
	return c[f[x]][0] == x || c[f[x]][1] == x; 
}
void rotate(int x)
{
	int y = f[x],z = f[y],k = c[y][1] == x,w = c[x][!k];
	if(nroot(y)) c[z][c[z][1] == y] = x;
	c[x][!k] = y;c[y][k] = w;
	f[w] = y;f[y] = x;f[x] = z;
	pushup(y);
}
void push(int x)
{
	if(nroot(x)) push(f[x]);
	pushdown(x);
}
void splay(int x)
{
	push(x);
	while(nroot(x))
	{
		int y = f[x],z = f[y];
		if(nroot(y))
		{
			rotate(((c[y][1]==x)^(c[z][1]==y))?x:y);
		}
		rotate(x);
		pushup(x);
	}
}
void access(int x)
{
	for(int y = 0;x;x = f[y=x])
	splay(x),c[x][1] = y,pushup(x);
}
void makeroot(int x)
{
	access(x);splay(x);pushr(x);
}
void link(int x,int y)
{
	makeroot(x);
	f[x] = y;
}
int main()
{
	n = read();
	for(int i = 1;i < n;i++)
	{
		int a = read(),b = read(),c = read();
		link(a,i+n);
		link(b,i+n);
		val[i+n] = c;
	}
	m = read();
	for(int i = 1;i <= m;i++)
	{
		int a = read(),b = read();
		makeroot(a);
		access(b);
		splay(b);
		write(mi[b]);printf(" ");
		write(mx[b]);printf("\n");	
	}
}
```


[欢迎来踩](https://www.luogu.com.cn/blog/xzc/solution-sp3978)


---

## 作者：andysk (赞：2)

[Link](https://www.luogu.org/problem/SP3978)

[Blog阅读效果更佳](https://tony102.xyz/index.php/2019/10/23/sp3978-disquery-distance-query/)

题意不说了，翻译已经是简明题意了。

很容易想到要求一个LCA，这里可以用到两种方法来解决。

可以使用树剖求LCA，但是考虑到树剖是可以处理点权的，在这里我们要转化成边权。所以不是很好处理。

那就是倍增了，稍微想一下就可想到在倍增的同时记两个数组```Min[][] Max[][]```, 在倍增的同时处理出到当前节点的最小边和最大边。

思路大概是这样，具体实现也很板子，见代码



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 100000 + 5;

int n, Q, num, t;
int head[SIZE], depth[SIZE], dis[SIZE], f[SIZE][21], Min[SIZE][21], Max[SIZE][21];

struct node {
    int to, v, Next;
} edge[SIZE << 1];

inline int read()
{
    char ch = getchar();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
    return x * f;
}

inline void Addedge(int x, int y, int z)
{
    edge[++num].to = y;
    edge[num].v = z;
    edge[num].Next = head[x];
    head[x] = num;
}

inline void DFS(int u, int fa)
{
    f[u][0] = fa;
    for (int i = head[u]; i; i = edge[i].Next) {
        int v = edge[i].to;
        if (v != fa) {
            Min[v][0] = Max[v][0] = edge[i].v; //　赋初值
            depth[v] = depth[u] + 1;
            DFS(v, u);
        }
    }
}

inline void init()
{
    for (int k = 1; k <= 20; k++)
        for (int i = 1; i <= n; i++) {
            if (f[f[i][k - 1]][k - 1] && f[i][k - 1]) {
                f[i][k] = f[f[i][k - 1]][k - 1];
                Min[i][k] = std::min(Min[i][k - 1], Min[f[i][k - 1]][k - 1]);
                Max[i][k] = std::max(Max[i][k - 1], Max[f[i][k - 1]][k - 1]);　// 预处理倍增数组的时候同时处理Min Max两个数组
            }
        }
}
    
inline void LCA(int u, int v)
{
    int ans_min = 2e9, ans_max = -2e9;
    if (depth[u] > depth[v]) std::swap(u, v);
    for (int i = 20; i >= 0; i--) {
        if (depth[u] <= depth[f[v][i]]) {
            ans_min = std::min(ans_min, Min[v][i]), ans_max = std::max(ans_max, Max[v][i]);　//　跳的时候记最大最小值，一定要注意先记再跳
            v = f[v][i];
        }
    }
    if (u == v) {
        printf("%d %d\n", ans_min, ans_max);
        return;
    }
    for (int i = 20; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            ans_min = std::min(ans_min, std::min(Min[u][i], Min[v][i])), ans_max = std::max(ans_max, std::max(Max[u][i], Max[v][i]));
            u = f[u][i], v = f[v][i];
        }
    }
    ans_min = std::min(ans_min, std::min(Min[u][0], Min[v][0]));
    ans_max = std::max(ans_max, std::max(Max[u][0], Max[v][0])); // 跟第０层比较
    printf("%d %d\n", ans_min, ans_max);
}

int main()
{
    int u, v, d;
    n = read();
    for (int i = 1; i < n; i++) {
        u = read(), v = read(), d = read();
        Addedge(u, v, d);
        Addedge(v, u, d);
    }
    depth[1] = 1;
    DFS(1, 0);
    Min[1][0] = 2e9;
    init();
     Q = read();
     while (Q--) {
         u = read(), v = read();
         LCA(u, v);
     }
    return 0;
}
```




---

## 作者：wxwoo (赞：1)

[$$\color{#0e90d2}\huge{\texttt{my blog}}$$](https://wxwoo.github.io/2019/05/27/solution-sp3978)

******

[原题目链接](https://www.luogu.org/problemnew/show/SP3978)

树上链最值查询

做法很多，LCT，树上倍增，树剖都可以

但由于LCT常数过大，树上倍增比树剖常数大，这里使用树链剖分

边权转点权是树剖常用套路，将边权转成深度较大的点的点权，查询时注意避开两点的LCA的权值

由于不带修改，树剖后用ST表维护，时间复杂度$\mathcal{O}(n\log n)$，比用线段树维护$\mathcal{O}(n\log ^2n)$还少一个log

代码如下

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
template<typename T>inline void read(T &x)
{
	char ch=getchar();
	T f=1;
	x=0;
	while(!('0'<=ch&&ch<='9'))
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=f;
}
const int N=100010,logN=20;
int n,m;
int head[N],nxt[N<<1],to[N<<1],w[N<<1],e;
int fa[N],son[N],dep[N],wt[N],sz[N],id[N],seq[N],top[N],cnt;
int st[N][logN][2],_log[N];
inline void add(int u,int v,int f)
{
	to[++e]=v;
	w[e]=f;
	nxt[e]=head[u];
	head[u]=e;
}
inline void build()
{
	_log[0]=-1;
	for(int i=1;i<=n;++i)
	{
		st[i][0][0]=st[i][0][1]=wt[seq[i]];
		_log[i]=_log[i>>1]+1;
	}
	for(int j=1;j<=logN;++j)
	{
		for(int i=1;i+(1<<j)-1<=n;++i)
		{
			st[i][j][0]=max(st[i][j-1][0],st[i+(1<<j-1)][j-1][0]);
			st[i][j][1]=min(st[i][j-1][1],st[i+(1<<j-1)][j-1][1]);
		}
	}
}
inline int qmax(int x,int y)
{
	int s=_log[y-x+1];
	return max(st[x][s][0],st[y-(1<<s)+1][s][0]);
}
inline int qmin(int x,int y)
{
	int s=_log[y-x+1];
	return min(st[x][s][1],st[y-(1<<s)+1][s][1]);
}
void dfs1(int x,int f,int d)
{
	fa[x]=f;
	dep[x]=d+1;
	sz[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		wt[y]=w[i];
		dfs1(y,x,d+1);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])
			son[x]=y;
	}
}
void dfs2(int x,int t)
{
	id[x]=++cnt;
	top[x]=t;
	seq[cnt]=x;
	if(!son[x])
		return;
	dfs2(son[x],t);
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa[x]||y==son[x])
			continue;
		dfs2(y,y);
	}
}
inline int querymin(int x,int y)
{
	int ans=0x3f3f3f3f;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans=min(ans,qmin(id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(x==y)
		return ans;
	return min(ans,qmin(id[x]+1,id[y]));
}
inline int querymax(int x,int y)
{
	int ans=-0x3f3f3f3f;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans=max(ans,qmax(id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	if(x==y)
		return ans;
	return max(ans,qmax(id[x]+1,id[y]));
}
int main()
{
	read(n);
	int u,v,f;
	for(int i=1;i<n;++i)
	{
		read(u);
		read(v);
		read(f);
		add(u,v,f);
		add(v,u,f);
	}
	dfs1(1,1,1);
	dfs2(1,1);
	build();
	read(m);
	++m;
	while(--m)
	{
		read(u);
		read(v);
		printf("%d %d\n",querymin(u,v),querymax(u,v));
	}
	return 0;
}
```

---

## 作者：hkhkkk (赞：0)

这是一道不错的练习题，可以拿来学习算法。

首先，观察题意，翻译很明确，树上每个点都有一个权值，

我们需要求出树上两点之间权值的最大值和最小值，

看到这里，发现树链剖分可以维护路径权值，

但是这题不用修改，那我们不妨换种方法，用倍增 LCA 求解，

倍增 LCA 是一种倍增思想求解树上最近公共祖先的算法，

从易到难，我们先看看最基础的 LCA 算法，

我们从两个点开始，每次往上走一条边，

把经过的点打个标记，如果走到了被标记的点，

那么这个点就是我们求解的最近公共祖先，

这个算法很好理解，我们再看看进阶，

假设我们随意选一个点作为根开始遍历，那么每个点可以得到一个深度，

利用先前的算法，先将深度深的向上走直至两点深度相同，

再同时把两个点向上走，就可以避免打标记和一些时间的浪费，

继续观察，发现每次只走一条边似乎过于浪费，我们能不能借助倍增的思想呢？

比方说一个点到它的最近公共祖先的距离为 $9$，那一次走 $9$ 条边不是就到了吗。

虽然我们不能这么做，因为这样无论时间还是空间复杂度都过高，

但是我们可以借用二进制拆分思想，将点到最近公共祖先的距离拆成 $2$ 的幂次的和，

举个例子：我们将 $9$ 拆成 $2^3+2^0$，那只要走两次，

第一次向上跳 $8$ 条边，第二次向上走 $1$ 条边即可走到，

![](https://cdn.luogu.com.cn/upload/image_hosting/7nqwngid.png)

由此，我们只需要存储跟每个点的距离为 $2$ 的幂次的祖先节点，

其中定义 $anc[i][j]$ 为距离第 $i$ 个点 $2^j$ 条边的祖先节点，

首先 $anc[i][0]$ 就是父节点，而 $anc[i][j]=anc[anc[i][j-1]][j-1]$，

这样预处理相当于每次跳 $2^{j-1}$ 条边，跳两次就能知道了，

查询的实现是先一个点跳直到两个点深度相同，再一起跳，找到最近公共祖先，

那么预处理的时空复杂度为 O($nlogn$)，单次查询则为 O($logn$)，

这样可以满足我们的需求了，是不是很简单？

但单纯的 LCA 不支持路径查询，我们考虑用 LCA 的方法维护路径最值，

看到 LCA 可以用倍增求祖先节点，那我们是不是也可以用倍增记录路径最值呢？

我们再定义 $mi[i][j]$ 为第 $i$ 个点到 $anc[i][j]$ 之间边的最小权值，

那么 $mi[0][i]$ 就是点 $i$ 和父节点边的权值，通过倍增的思想得到：

$mi[i][j]=min(mi[i][j-1],mi[anc[i][j-1]][j-1])$，

怎么来的呢？就像这样:

![](https://cdn.luogu.com.cn/upload/image_hosting/s417nw3k.png)

同理，记录 $ma$ 数组可以得到最大值，

这样我们只要在 LCA 的过程中"顺便" 记录一下路径的值，问题就得到了解决。

最后，上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,y,z;
int tot,o[100001],to[200001],val[200001],ne[200001];//前向星存图
int anc[100001][20],mi[100001][20],ma[100001][20],d[100001];
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*f;
}
void add(int x,int y,int z){
	to[++tot]=y,val[tot]=z,ne[tot]=o[x],o[x]=tot;
}
void dfs(int x,int fa,int u){
	d[x]=d[fa]+1;
	anc[x][0]=fa;
	mi[x][0]=ma[x][0]=u;
	for(int j=1;j<=log2(n);j++){
		anc[x][j]=anc[anc[x][j-1]][j-1];
		mi[x][j]=min(mi[x][j-1],mi[anc[x][j-1]][j-1]);
		ma[x][j]=max(ma[x][j-1],ma[anc[x][j-1]][j-1]);
   }
	for(int i=o[x];i;i=ne[i])
		if(to[i]!=fa) dfs(to[i],x,val[i]);
} 
int lca(int x,int y){
	int num=(1<<30);
	if(d[x]>d[y]) swap(x,y);
	for(int j=log2(n);j>=0;j--)
		if(d[anc[y][j]]>=d[x]){
			num=min(num,mi[y][j]);
			y=anc[y][j];
		}
	if(x==y) return num;
	for(int j=log2(n);j>=0;j--) 
		if(anc[x][j]!=anc[y][j]){
			num=min(num,min(mi[x][j],mi[y][j]));
			x=anc[x][j];
			y=anc[y][j];
		}
	num=min(num,min(mi[x][0],mi[y][0]));
	return num;
}
int lca2(int x,int y){
	int num=-(1<<30);
	if(d[x]>d[y]) swap(x,y);
	for(int j=log2(n);j>=0;j--)
		if(anc[y][j]&&d[anc[y][j]]>=d[x]){
			num=max(num,ma[y][j]);
			y=anc[y][j];
		}
	if(x==y) return num;
	for(int j=log2(n);j>=0;j--)
		if(anc[x][j]!=anc[y][j]){
			num=max(num,max(ma[x][j],ma[y][j]));
			x=anc[x][j];
			y=anc[y][j];
		}
	num=max(num,max(ma[x][0],ma[y][0]));
	return num;
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
	    x=read(),y=read(),z=read();
		add(x,y,z);
		add(y,x,z); 
	} 
	dfs(1,0,1);
	q=read();
	for(int i=1;i<=q;i++){
	    x=read(),y=read();
		printf("%d %d\n",lca(x,y),lca2(x,y));
	}
    return 0;
}
```


---

## 作者：vocaloid (赞：0)

树链剖分。无脑边权转点权，线段树维护最大最小值，查询时忽略 $\text{LCA}$ 即可。

树链剖分入门见：[树链剖分瞎入门](https://www.luogu.org/blog/Venus/tree-train-split)

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
typedef pair<int,int> pr;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1],w[MAXN<<1];
int n,Q,a[MAXN],maxn[MAXN<<2],minx[MAXN<<2];
int dfn[MAXN],Index,siz[MAXN],son[MAXN],top[MAXN],dep[MAXN],faz[MAXN],rk[MAXN];
void AddEdge(int u,int v,int c)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
void Dfs1(int u)
{
	siz[u]=1;
	son[u]=0;
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz[u]) continue;
		dep[v]=dep[u]+1;
		faz[v]=u;
		a[v]=w[i];
		Dfs1(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v]) son[u]=v;
	}
}
void Dfs2(int u,int rt)
{
	dfn[u]=++Index;
	rk[Index]=u;
	top[u]=rt;
	if(son[u]) Dfs2(son[u],rt);
	for(int i=fst[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==faz[u] || v==son[u]) continue;
		Dfs2(v,v);
	}
}
void PushUp(int rt)
{
	maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
	minx[rt]=min(minx[rt<<1],minx[rt<<1|1]);
}
void BuildSegmentTree(int rt,int l,int r)
{
	if(l==r)
	{
		maxn[rt]=minx[rt]=a[rk[l]];
		return;
	}
	int mid=l+r>>1;
	BuildSegmentTree(rt<<1,l,mid);
	BuildSegmentTree(rt<<1|1,mid+1,r);
	PushUp(rt);
}
int QueryMax(int rt,int l,int r,int tl,int tr)
{
	if(tl<=l && r<=tr) return maxn[rt];
	int mid=l+r>>1,res=-2e9;
	if(tl<=mid) res=max(res,QueryMax(rt<<1,l,mid,tl,tr));
	if(tr>mid) res=max(res,QueryMax(rt<<1|1,mid+1,r,tl,tr));
	return res;
}
int QueryMin(int rt,int l,int r,int tl,int tr)
{
	if(tl<=l && r<=tr) return minx[rt];
	int mid=l+r>>1,res=2e9;
	if(tl<=mid) res=min(res,QueryMin(rt<<1,l,mid,tl,tr));
	if(tr>mid) res=min(res,QueryMin(rt<<1|1,mid+1,r,tl,tr));
	return res;
}
pr QueryOnTree(int u,int v)
{
	int res1=-2e9,res2=2e9;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res1=max(res1,QueryMax(1,1,n,dfn[top[u]],dfn[u]));
		res2=min(res2,QueryMin(1,1,n,dfn[top[u]],dfn[u]));
		u=faz[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res1=max(res1,QueryMax(1,1,n,dfn[u]+1,dfn[v]));
	res2=min(res2,QueryMin(1,1,n,dfn[u]+1,dfn[v]));
	return make_pair(res1,res2);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Dfs1(1);
	Dfs2(1,1);
	BuildSegmentTree(1,1,n);
	scanf("%d",&Q);
	while(Q--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		pr res=QueryOnTree(x,y);
		printf("%d %d\n",res.second,res.first);
	}
	return 0;
}
```

---

