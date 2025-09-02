# [ONTAK2015] Związek Harcerstwa Bajtockiego

## 题目描述

给定一棵 $n$ 个点的无根树，相邻的点之间的距离为 $1$，一开始你位于 $m$ 点。之后你将依次收到 $k$ 个指令，每个指令包含两个整数 $d$ 和 $t$，你需要沿着最短路在 $t$ 步之内（包含 $t$ 步）走到 $d$ 点，如果不能走到，则停在最后到达的那个点。请在每个指令之后输出你所在的位置。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq m \leq n \leq 10^6$，$1 \leq k \leq 10^6$，$1 \leq x, y, d \leq n$，$0 \leq t \leq 10^9$。

## 样例 #1

### 输入

```
3 1 2
1 2
2 3
3 4
1 1```

### 输出

```
3 2```

# 题解

## 作者：Zvelig1205 (赞：15)

# 树剖求树上节点的 k 级祖先

[题目传送门](https://www.luogu.com.cn/problem/P8025)

## 闲话

~~我发现我有一个没 A 的蓝树剖~~

当树剖题做得比较多之后，简单的树剖还真能一眼出思路。

## 变量声明

- `now`：现在所处的节点位置。
- `to`：要到达的节点位置。
- `reach`：不能到达 `to` 时最后到达的节点。
- `lca`：`now` 和 `to` 的最近公共祖先。
- `step`：能走的步数。
- `dis1`：`now` 到 `lca` 的距离。
- `dis2`：`to` 到 `lca` 的距离。

## 思路

蒟蒻分类比较多（太菜，不会将情况合并）。

### 一、能到达

直接输出 `to` 并更新 `now`。

```cpp
if(step>=dis1+dis2)wr(now=to),putchar(' ');
```

### 二、不能到达

蒟蒻怕错，将不能到达的情况又分成了两类：

- 向下跳

- 向上跳

1. 向下跳

此时，从上向下跳 `step` 步就相当于从下向上跳 `dis2-step` 步。

```cpp
else if(lca==now)
{
	now=tiao(to,dis2-step);
	wr(now),putchar(' ');
}
```

2. 向上跳

还是为了防止出错，我又双叒叕分类了。

① 正巧跳到 `lca`：

直接输出 `lca` 并更新 `now`。

```cpp
else if(dis1==step)wr(now=lca),putchar(' ');
```

② 在经过 `lca` 前不能走了：

`now` 向上跳 `dis1` 步。

```cpp
else if(dis1>step)
{
	now=tiao(now,step);
	wr(now);putchar(' ');
}
```

③ 经过 `lca` 后停下：

总路程为 `dis1+dis2`，走过了 `step`，剩下了 `dis1+dis2-step` 步。`to` 向上跳 `dis1+dis2-step` 步。

```cpp
else
{
	now=tiao(to,dis2-(step-dis1));
	wr(now);putchar(' ');
}
```

### 三、跳

思路中全是跳跳跳，那么到底怎么跳？

这题是什么？

对，树剖！

跳重链呗。

每次跳到重链的顶点的父节点，直到距离不够。

此时，当前节点和目标节点在一条重链上。

然后呢？

暴力跳？

~~树退化成链能让你当场去世~~

树剖有个美妙的性质，重链的时间戳是连续的。

而且深度也是连续的。

那么就有以下等式的推导：

$$\begin{array}{c}
dep_{now}-dep_{to}=dfn_{now}-dfn_{to}\\
-dep_{now}+dep_{to}+dfn_{now}=dfn_{to}\\
k=dep_{to}-dep_{now}\\
dfn_{to}=dfn_{now}-k\\
to=rnk[dfn_{to}]
\end{array}$$

所以代码就是这样：

```cpp
int tiao(int x,int k)
{
	while(1)
	{
		if(dep[x]-dep[top[x]]+1>k)break;
		k-=dep[x]-dep[top[x]]+1;
		x=fa[top[x]];
	}
	return rnk[dfn[x]-k];
}
```

全代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int re()
{
	int s=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		s=s*10+ch-48,ch=getchar();
	return s*f;
}
void wr(int s)
{
	if(s<0)putchar('-'),s=-s;
	if(s>9)wr(s/10);
	putchar(s%10+48);
}
const int inf=1e6+7;
int n,m;
int fir[inf],nex[inf<<1],poi[inf<<1],cnt;
void ins(int x,int y)
{
	nex[++cnt]=fir[x];
	poi[cnt]=y;
	fir[x]=cnt;
}
int fa[inf],dep[inf],siz[inf],son[inf];
void dfs1(int now,int from)
{
	siz[now]=1;fa[now]=from;
	dep[now]=dep[from]+1;
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(p==from)continue;
		dfs1(p,now);
		siz[now]+=siz[p];
		if(siz[son[now]]<siz[p])
			son[now]=p;
	}
}
int top[inf],dfn[inf],rnk[inf],sum;
void dfs2(int now,int topn)
{
	top[now]=topn;
	dfn[now]=++sum;rnk[sum]=now;
	if(son[now]==0)return;
	dfs2(son[now],topn);
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(p==fa[now]||p==son[now])
			continue;
		dfs2(p,p);
	}
}
int lca_(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int now;
int tiao(int x,int k)
{
	while(1)
	{
		if(dep[x]-dep[top[x]]+1>k)break;
		k-=dep[x]-dep[top[x]]+1;
		x=fa[top[x]];
	}
	return rnk[dfn[x]-k];
}
int main()
{
	n=re();now=re();m=re();
	for(int i=1;i<n;i++)
	{
		int u=re(),v=re();
		ins(u,v),ins(v,u);
	}
	dfs1(1,1);dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		int to=re(),step=re();
		int lca=lca_(now,to);
		int dis1=dep[now]-dep[lca],dis2=dep[to]-dep[lca];
		if(step>=dis1+dis2)wr(now=to),putchar(' ');
		else if(lca==now)
		{
			now=tiao(to,dis2-step);
			wr(now),putchar(' ');
		}
		else if(dis1==step)wr(now=lca),putchar(' ');
		else if(dis1>step)
		{
			now=tiao(now,step);
			wr(now);putchar(' ');
		}
		else
		{
			now=tiao(to,dis2-(step-dis1));
			wr(now);putchar(' ');
		}
	}
    return 0;
}

```

## 广告

[树剖相关知识](https://www.cnblogs.com/adm-1223/p/15875076.html)

[My blog](https://www.cnblogs.com/adm-1223/)

---

## 作者：bruhify (赞：6)

## Problem:

- 给定一棵无权树和一个起点 $m$，操作 $k$ 次，每次要求在简单路径上走最多 $t$ 步到新的点 $d$，如果走不到则在走 $t$ 步后停下，求每次操作后的点的编号。

- 数据范围：$1 \leq n,k \leq 10^6$, $0 \leq t \leq 10^9$。

## Editorial:

设当前操作的起点为 $u$，在 $t$ 步内走到的终点为 $v$。

考虑将每一次操作的简单路径 $(u,d)$ 拆为两条，设 $u$ 和 $d$ 的最近公共祖先为 $p$， 那么将 $(u,d)$ 拆为 $(u,p)$ 和 $(p,d)$。如果 $u$ 到 $d$ 的距离 $\leq t$，则可以在 $t$ 步内走到，此时 $v=d$，输出 $d$ 即可；
否则，需要判断 $v$ 所在的路径部分。

设 $u$ 到 $d$ 的距离 $= x$，$u$ 到 $p$ 的距离 $= y$。

若 $y \geq t$，则 $v$ 在 $(u,p)$ 上，这次操作走过的边均为从儿子到父亲的边，而且走了 $t$ 次，那么 $v$ 为 $u$ 的 $t$ 级祖先。

若 $y \leq t$，则 $v$ 在 $(p,d)$ 上。如果按照上面的思路考虑，除去 $(u,p)$ 上的 $y$ 条边后，剩下的 $t-y$ 条边是从父亲到儿子的边，不好记录。

正难则反，我们考虑 $t$ 步内在 $(u,d)$ 上没有走到的边，这样的边有 $x-t$ 条，而且组成了从 $v$ 到 $d$ 的简单路径，那么 $v$ 为 $d$ 的 $x-t$ 级祖先。

至此，我们已经成功地把原问题转化为了维护树上最近公共祖先和 $k$ 级祖先问题，使用树链剖分维护即可。（倍增表常数过大，会在第 $4$ 个测试点上被卡掉 qnq）

时间复杂度：$\mathcal {O(n \log n + k \log n)}$

空间复杂度：$\mathcal {O(n)}$

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,u,k;

int h[1000005],e[2000005],ne[2000005],idx;

void add(int a,int b) {
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}

int depth[1000005];

int sub[1000005];
int heavy[1000005];
int fa[1000005];

void dfs1(int u) {
	sub[u]=1;
	for(int i=h[u];i!=-1;i=ne[i]) {
		int v=e[i];
		if(depth[v]==0) {
			depth[v]=depth[u]+1;
			fa[v]=u;
			dfs1(v);
			sub[u]+=sub[v];
			if(heavy[u]==0 || sub[heavy[u]]<sub[v]) {
				heavy[u]=v;
			}
		}
	}
}

int dfn[1000005],top[1000005];
int rk[1000005];
int timestamp;

void dfs2(int u,int topu) {
	dfn[u]=++timestamp;
	rk[dfn[u]]=u;
	top[u]=topu;
	if(heavy[u]==0) {
		return;
	}
	dfs2(heavy[u],topu);
	for(int i=h[u];i!=-1;i=ne[i]) {
		int v=e[i];
		if(depth[v]==depth[u]+1 && v!=heavy[u]) {
			dfs2(v,v);
		}
	}
}

int lca(int u,int v) {//最近公共祖先
	while(top[u]!=top[v]) {
		if(depth[top[u]]<depth[top[v]]) {
			swap(u,v);
		}
		u=fa[top[u]];
	}
	if(depth[u]>depth[v]) {
		swap(u,v);
	}
	return u;
}

int kthA(int u,int d) {//k级祖先
	d=depth[u]-d;
	while(depth[top[u]]>d) {
		u=fa[top[u]];
	}
	return rk[dfn[u]-(depth[u]-d)];
}

int read() {
	int s=0;
	char ch=getchar();
	while(ch<'0' || ch>'9') {
		ch=getchar();
	}
	while(ch>='0' && ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s;
}

int main() {
	n=read(),u=read(),k=read();
	memset(h,-1,sizeof(int)*(n+1));
	for(int i=1;i<=n-1;i++) {
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	depth[1]=1;
	dfs1(1);
	dfs2(1,1);//树链剖分预处理
	for(int i=1;i<=k;i++) {
		int d=read(),t=read();
		int p=lca(u,d);
		if(depth[u]+depth[d]-(depth[p]<<1)<=t) {//u到d的距离小于等于t
			printf("%d ",u=d);
			continue;
		}
		if(t>=depth[u]-depth[p]) {//u到p的距离小于等于t
			t=(depth[u]+depth[d]-(depth[p]<<1))-t;
			u=kthA(d,t);
		}else {//u到p的距离大于t
			u=kthA(u,t);
		}
		printf("%d ",u);
	}
	return 0;
}
```


---

## 作者：0xFF (赞：4)

#### 题目大意


------------
给出一棵树，初始点为 $m$ 点，每次给出 $d,t$，询问能否从 $m$ 点走 $t$ 步之内到达 $d$ 点，输出 $m$ 点最终停留的位置。

#### 思路分析


------------
分类讨论

如果两点间简单路径的长度小于 $t$，那么一定可以走到 $d$ 点，直接输出即可。

如果两点间简单路径的长度小于等于 $m$ 点到 $m,d$ 的最近公共祖先的简单路径的长度，输出 $m$ 的 $t$ 级祖先。

如果两点间简单路径的长度大于 $m$ 点到 $m,d$ 的最近公共祖先的简单路径的长度，相当于从 $d$ 点向上走两点间简单路径的长度减去 $t$ 步，即输出 $d$ 点的 `depth[m]+depth[d]-2*depth[LCA(m,d)]-t` 级祖先。

考虑树剖求解。

每次向上跳到链顶与目标点比较，如果所在链的链顶的深度大于目标点的深度，则可以继续跳。

若当前所在的点和目标点处于同一条链上，由于之前树剖中求出了每一个点的 dfs 序，直接向上跳两点的 dfs 序之差步即可，因为一条链上的点的 dfs 序是连续的，所以两点的层数之差即为两点 dfs 序之差。

#### 代码实现


------------
```cpp
void dfs1(int u,int fath){
	fa[u] = fath , depth[u] = depth[fath] + 1 , siz[u] = 1;
	for(int i=head[u];i;i=edge[i].next){
		int v = edge[i].to;
		if(v == fath) continue;
		dfs1(v,u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]) son[u] = v;
	}
}
void dfs2(int u,int topf){
	top[u] = topf;
	dfn[u] = ++cnt;
	id[cnt] = u;
	if(!son[u]) return;
	dfs2(son[u],topf);
	for(int i=head[u];i;i=edge[i].next){
		int v = edge[i].to;
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v,v);
	}
}
int lca(int x,int y){
	while(top[x] != top[y]){
		if(depth[top[x]] < depth[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	if(depth[x] > depth[y]) swap(x,y);
	return x;
}
int find(int u,int d){
	d = depth[u] - d;
	while(depth[top[u]] > d){
		u = fa[top[u]];
	}
	return id[dfn[u] - (depth[u] - d)];
}

int main(){
	int n = read() , m = read() , k = read();
	for(int i=1;i<=n-1;i++){
		int a = read() , b = read();
		add(a,b); add(b,a);
	}
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=k;i++){
		int d = read() , t = read();
		int pos = lca(m,d);
		int dis = depth[m] + depth[d] - 2 * depth[pos];
		if(dis < t){
			cout<<d<<" ";
			m = d;
			continue;
		}
		else if(depth[m] - depth[pos] <= t){
			t = dis - t;
			d = find(d,t);
		}
		else d = find(m,t);
		printf("%d ",d);
		m = d;
	}
	return 0;
}
```


---

## 作者：蒟蒻中的zzh (赞：2)

## 前言：
其实这道题还是比较简单的...只不过它卡倍增
## 正文部分
### 考场 87 分做法（倍增）

首先我们知道，如果想在树上从 $A$ 点到 $B$ 点，需要先从 $A$ 点走到它们的 lca，再从它们的 lca 走到 $B$ 点。我们还可以利用每个节点的深度表示出 $A$ 到 lca(A,B) 的距离和 lca(A,B) 到 $B$ 的距离。这样，我们只需要求出它们的 lca 就可以知道能否在指定步数内从 $A$ 点到达 $B$ 点。

现在就只需要考虑不能到的情况。首先，我们可以确定我们最后会落在在那一段。我们设 $A$ 到 lca(A,B) 的距离为 $x$，如果 $x < t$，则我们最后会落在 $B$ 和 lca(A,B) 之间；如果 $x > t$，则我们最后会落在 $A$ 和 lca(A,B) 之间；如果 $x = t$，则我们会落在 lca(A,B) 上。

现在我们已经确定了会在哪一段路上了，那么我们就只需要确定在那个点上了。我们这样考虑：如果我们最后落在了 $A$ 和 lca(A,B) 之间，那么我们就从 $A$ 向上跳；如果是落在了 $B$ 和lca(A,B) 之间，我们就从 $B$ 往上跳。这个往上跳的过程我们可以仿照倍增求 lca 中把两个节点跳到同一个深度处的做法，及：
```
if(dep[x]>dep[y]) swap(x,y);
for(int i=0;dep[y]-dep[x]>>i>0;++i) 
	if(dep[y]-dep[x]>>i&1)
		y=fa[y][i];
//lca

int move(int m,int t)
{
	for(int i=0;t>>i>0;++i) 
		if(t>>i&1)
			m=fa[m][i];
	return m;
}
//移动
```
那么恭喜你，如果你这样实现的话，你可以拿到 87 分（有一个点 TLE）。

那么，我们如何把这个代码改对呢？

### 正解

上述做法中，我们的结论还是可以使用的，只不过求 lca 和 move 这两个部分慢了一点。于是我们很容想到用常数更小的[树链剖分](https://oi-wiki.org/graph/hld/)。我们只需要把 move 过程从模仿倍增变成在重链上面跳即可。

### 完整代码

倍增：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
int fa[N][22],n,m,dep[N],head[N],t,k;
struct node
{
	int to,next;
}a[N<<1];
void add(int from,int to)
{
	a[++t].to=to;
	a[t].next=head[from];
	head[from]=t;
}
void dfs(int rt,int f)    倍增求 lca 中的 dfs 
{
	dep[rt]=dep[f]+1;
	fa[rt][0]=f;
	for(int i=1;i<=20;++i)
		fa[rt][i]=fa[fa[rt][i-1]][i-1];
	for(int i=head[rt];i!=0;i=a[i].next)
		if(a[i].to!=f)
			dfs(a[i].to,rt);
	return ;
}
int lca(int x,int y)  //倍增求lca
{
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=0;dep[y]-dep[x]>>i>0;++i) 
		if(dep[y]-dep[x]>>i&1)
			y=fa[y][i];
	if(x==y) return x;
	for(int i=20;i>=0;--i) 
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int move(int m,int t)
{
	for(int i=0;t>>i>0;++i) 
		if(t>>i&1)
			m=fa[m][i];
	return m;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=k;++i) 
	{
		int d,t;
		scanf("%d%d",&d,&t);
		int l=lca(m,d);
		if(dep[m]-dep[l]+dep[d]-dep[l]<=t) m=d;   判断最终到底会落在在哪一段上
		else if(dep[m]-dep[l]>t) m=move(m,t);
		else if(dep[m]-dep[l]==t) m=l;
		else if(dep[m]-dep[l]<t) m=move(d,dep[d]-dep[l]-t+dep[m]-dep[l]);
		printf("%d ",m);
	}
	return 0;
}

```

树链剖分：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int N=1000005;
int t,head[N],m,k,n,fa[N],top[N],son[N],rnk[N],dfn[N],dep[N],siz[N],cnt;
struct node
{
	int to,next;
}a[N<<1];
void add(int x,int y)
{
	a[++t].to=y;
	a[t].next=head[x];
	head[x]=t;
}
void dfs1(int rt,int f)
{
	fa[rt]=f;
	dep[rt]=dep[f]+1;
	siz[rt]=1;
	for(int i=head[rt];i!=0;i=a[i].next)
	{
		if(dep[a[i].to]!=0) continue;
		dfs1(a[i].to,rt);
		siz[rt]+=siz[a[i].to];
		if(siz[son[rt]]<siz[a[i].to]) son[rt]=a[i].to;
	}
	return ;
}
void dfs2(int rt,int tp)
{
	top[rt]=tp;
	dfn[rt]=++cnt;
	rnk[cnt]=rt;
	if(son[rt]==0) return ;
	dfs2(son[rt],tp);
	for(int i=head[rt];i!=0;i=a[i].next)
		if(dfn[a[i].to]==0&&a[i].to!=son[rt]) dfs2(a[i].to,a[i].to);
	return ;
}
int lca(int x,int y)   //树链剖分求 lca
{
	while(top[x]!=top[y])
		if(dep[top[x]]<dep[top[y]]) y=fa[top[y]];
		else x=fa[top[x]];
	return dep[x]<dep[y]?x:y;
}
int move(int s,int t)   移动
{
	int x=s;
	while(dep[x]-dep[top[s]]+1<=t)
		s=fa[top[s]];
//	cout<<dfn[s]-(t-dep[x]-dep[s])<<endl;
	return rnk[dfn[s]-(t-(dep[x]-dep[s]))];
}
int main()
{
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(0),std::cout.tie(0);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=k;++i)
	{
		int d,t;
		scanf("%d%d",&d,&t);
		int l=lca(m,d);
		if(dep[m]-dep[l]==t) m=l;     判断落在哪一段
		else if(dep[m]-dep[l]+dep[d]-dep[l]<=t) m=d;
		else if(dep[m]-dep[l]>t) m=move(m,t);
		else m=move(d,dep[d]-dep[l]-(t-(dep[m]-dep[l])));
		printf("%d ",m);
	}
	return 0;
}

```


---

## 作者：翼德天尊 (赞：2)

首先很容易想到，当目前所在的位置和目标点 $d$ 的树上距离小于 $t$ 时，那么答案肯定是目标点。而树上距离可以通过求 $lca$ 后 $lca$ 和起始点、目标点的深度之差的和得出。

当树上距离大于 $t$ 时，我们可以分类讨论，设起始点与 $lca$ 的距离为 $dis1$，目标点与 $lca$ 的距离为 $dis2$，则：

1. $dis1=t$，此时不必多说，答案就是 $lca$。

2. $dis1>t$，大于 $t$ 就说明无法走到 $lca$ 的位置，那么答案就是起始点向上跳 $t$ 步，即答案为起始点的 $t$ 级祖先。求 $t$ 级祖先显然可以用树链剖分来求。倍增的方式大概也可以（但好像由于常数过大会超时）

3. $dist1<t$，此时终点一定是在 $lca$ 到目标点的一条链上，答案为 $lca$ 向下跳 $t-dis1$ 步的位置。但求儿子显然并不好求，而由于总距离固定，我们完全可以将跳儿子改为跳祖先，即答案为目标点的 $dis1+dis2-t$ 级祖先，同样可以用上述方法来求。

总时间复杂度 $O((n+k)logn)$，即可通过本题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 1000005
int n,now,k,head[N],tot,cnt,rk[N];
struct node{
	int to,next;
	node (int to=0,int next=0)
		:to(to),next(next){}
}b[N<<1];
struct node1{
	int fa,w,zson,top,size,id,d;
}e[N];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
void adde(int u,int v){
	b[++tot]=node(v,head[u]);
	head[u]=tot;
}
void dfs1(int u){
	e[u].d=e[e[u].fa].d+1,e[u].size=1;
	for (int i=head[u];i;i=b[i].next){
		int v=b[i].to;
		if (v!=e[u].fa){
			e[v].fa=u;
			dfs1(v);
			e[u].size+=e[v].size;
			if (e[v].size>=e[e[u].zson].size)
				e[u].zson=v;
		} 
	} 
} 
void dfs2(int u,int tp){
	e[u].top=tp,e[u].id=++cnt,rk[cnt]=u;
	if (e[u].zson) dfs2(e[u].zson,tp);
	for (int i=head[u];i;i=b[i].next){
		int v=b[i].to;
		if (v!=e[u].fa&&v!=e[u].zson)
			dfs2(v,v);
	}
}
void query(int x,int y,int t){
	int to=y;
	while (e[x].top!=e[y].top){
		if (e[e[x].top].d<e[e[y].top].d) swap(x,y);
		x=e[e[x].top].fa;
	}
	if (e[x].id>e[y].id) swap(x,y);//此时x为lca
	int all=e[to].d+e[now].d-e[x].d*2;
	if (all<=t){
		now=to;
		return;
	}
	if (e[now].d-e[x].d==t){//分类讨论
		now=x;
		return;
	}else if (e[now].d-e[x].d>t){
		y=now;
		while (e[y].d-e[e[y].top].d<t) t-=e[y].d-e[e[y].top].d+1,y=e[e[y].top].fa;//跳重链
		now=rk[e[y].id-t];//同重链之中跳
		return;
	}else{
		t=all-t,y=to;
		while (e[y].d-e[e[y].top].d<t) t-=e[y].d-e[e[y].top].d+1,y=e[e[y].top].fa;
		now=rk[e[y].id-t];
		return;
	}
}
int main(){
	n=read(),now=read(),k=read();
	for (int i=1;i<n;i++){
		int u=read(),v=read();
		adde(u,v),adde(v,u);
	}
	dfs1(1),dfs2(1,1);
	while (k--){
		int d=read(),t=read();
		query(now,d,t);
		printf("%d ",now);
	}
	return 0;
}
```


---

## 作者：huayt (赞：0)

前置知识 [树链剖分](https://oi-wiki.org//graph/hld/)（oi-wiki）

# 思路
题目要求树上两点之间的距离，第一个想到的应该是求 LCA（最近公共祖先），然后再算距离。

因为树剖后得到的同一条重链上的 dfs 序都是连续的，所以可以用 dfs 序来求同一条链上任意两点之间的距离。并且树上每个节点编号都对应**唯一**的 dfs 序。利用这点就能求出移动后的位置。

# 重点
对于不同的链，dfs 序并不是连续的，设当前最多走 $k$ 步，当前链的长度为 $L$，如果 $k>L$，则 $k=k-L$，然后跳到下一条链。

重复此过程，直到 $k<L$，设当前节点为 $x$，则终点的 dfs 序为 $dfn[x]\pm k$。
（建议画一棵树模拟此过程方便理解）

代码（核心代码有注释）
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;
const int N=1e6+5;
struct Node{
	int ver,nxt;
}List[N<<1];
int head[N],tot;
int dep[N],siz[N],son[N],fa[N],dfn[N],top[N],rnk[N],cnt;
//rnk数组存原编号
int ans[N];
int n,s,m;

void add(int x,int y){
	List[++tot].ver=y;
	List[tot].nxt=head[x];
	head[x]=tot;
	return;
}//建边

void Dfs1(int x){
	int i;
	siz[x]=1;
	son[x]=-1;
	for(i=head[x];i;i=List[i].nxt){
		int y=List[i].ver;
		if(dep[y]<=dep[x]+1) continue;
		dep[y]=dep[x]+1;
		fa[y]=x;
		Dfs1(y);
		siz[x]+=siz[y];
		if(son[x]==-1||siz[y]>siz[son[x]]) son[x]=y;
	}
	return;
}

void Dfs2(int x,int k){
	int i;
	top[x]=k;
	dfn[x]=++cnt;
	rnk[cnt]=x;
	if(son[x]==-1) return;
	Dfs2(son[x],k);
	for(i=head[x];i;i=List[i].nxt){
		int y=List[i].ver;
		if(y==fa[x]||y==son[x]) continue;
		Dfs2(y,y);
	}
	return;
}//树剖

int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}//求最近公共祖先

void solve(int x,int y){
	//x是终点，s是当前位置
	int pos=lca(x,s),d1=dep[s]-dep[pos],d2=dep[x]-dep[pos];
	if(y>=d1) s=pos,y-=d1;		//特判
	else{		//往上走
		while(top[s]!=top[pos]){	//如果不在同一条链
			int dis=dfn[s]-dfn[top[s]]+1;	//求链长（第一次为s到链顶长度）
			if(y<dis){		//如果到不了下一条链
				s=rnk[dfn[s]-y];	//记录原编号
				return;
			}
			y-=dis;		//减掉当前链长
			s=fa[top[s]];	//跳到下一条链
		}
		s=rnk[dfn[s]-y];
		return;
	}
	if(y>=d2){
		s=x;
		return;
	}else{		//往下走
		vector<pair<int,int> > vec;		
        //因为链只能上跳，用vector储存链的信息
		while(top[x]!=top[pos]){
			int dis=dfn[x]-dfn[top[x]]+1;
			vec.push_back(make_pair(top[x],dis));
			x=fa[top[x]];
		}
		vec.push_back(make_pair(pos,dep[x]-dep[pos]+1));	//注意记录最后一段
		int i;
		for(i=vec.size()-1;i>=0;i--){		//倒着搜每一条链
			int d=vec[i].second;
			if(y<d){
				s=rnk[dfn[vec[i].first]+y];	
				return;
			}
			y-=d;
		}
	}
	return;
}
----------求解----------
int main(){
	int i;
	scanf("%d%d%d",&n,&s,&m);
	for(i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	memset(dep,0x3f,sizeof(dep));
	dep[s]=1;
	Dfs1(s);
	Dfs2(s,s);
	for(i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		solve(x,y);
		ans[i]=s;
	}
	for(i=1;i<=m;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```


---

