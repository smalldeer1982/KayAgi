# [CERC2015] Juice Junctions

## 题目描述

你被雇佣升级一个旧果汁加工厂的橙汁运输系统。系统有管道和节点构成。每条管道都是双向的，且每条管道的流量都是 $1$ 升每秒。管道可能连接节点，每个节点最多可以连接 $3$ 条管道。节点的流量是无限的。节点用整数 $1$ 到 $n$ 来表示。在升级系统之前，你需要对现有系统进行分析。对于两个不同节点 $s$ 和 $t$，$s-t$ 的流量被定义为：当 $s$ 为源点，$t$ 为汇点，从 $s$ 能流向 $t$ 的最大流量。

以下面的第一组样例数据为例，$1-6$ 的流量为 $3$，$1-2$ 的流量为 $2$。

计算每一对满足 $a<b$ 的节点 $a-b$ 的流量的和。

## 样例 #1

### 输入

```
6 8
1 3
2 3
4 1
5 6
2 6
5 1
6 4
5 3```

### 输出

```
36```

# 题解

## 作者：zsc2003 (赞：8)

看到有大佬用最小割树做的,蒟蒻并不会

这里借助老师的思想写一个不用网络流的做法

由于最大流=最小割,所以最大流一定回$\leq 3$

那么分类讨论一下

使用并查集维护一下

一、若两个点在不同的集合,那么最大流就是0

二、若两个点同一个集合内

使用tarjan缩点一下

1、若两个点不在同一个联通分量内,则易证这两个点的最大流为1

2、若两个点在同一个联通分量内

①若两个点是三联通的,则最大流为3

②否则为2

按照以上方式分类即可

判断两个点是三联通的方式:

若这两个点是三联通的,则整张图中删除任意一条边后进行tarjan缩点,这两个点仍在同一个联通分量内。

所以删除m条边这两个点所在的连通分量的编号是相同的

使用哈希即可方便的判断是否完全相同,这样求出总和即可


```cpp

#include<iostream>
#include<cstdio>
#include<cstring>
#define ll unsigned long long
using namespace std;
inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=3010,M=4510;
const ll p=19491001;
int n,m;
struct edge
{
	int to,next;
}mem[M<<1];
int head[N],cnt=1;
inline void add(int u,int v)
{
	mem[++cnt].next=head[u];
	mem[cnt].to=v;
	head[u]=cnt;
}
int fa[N],f1,f2;
inline int getfa(int x)
{
	if(fa[x]!=x)fa[x]=getfa(fa[x]);
	return fa[x];
}
int dfn[N],low[N],ti;
int st[N],top;
int dcc[N],co;
bool vis[M<<1];
ll d[N];
void tarjan(int u,int no)
{
	low[u]=dfn[u]=++ti;
	st[++top]=u;
	for(int i=head[u];i>0;i=mem[i].next)
	{
		if(vis[i])continue;
		if((i==no)||((i^1)==no))continue;
		int to=mem[i].to;
		if(!dfn[to])
		{
			vis[i]=vis[i^1]=1;
			tarjan(to,no);
			vis[i]=vis[i^1]=0;
			low[u]=min(low[u],low[to]);
		}
		else
			low[u]=min(low[u],dfn[to]);
	}
	if(low[u]==dfn[u])
	{
		dcc[u]=++co;
		while(st[top]!=u)
			dcc[st[top--]]=co;
		top--;
	}
}
inline void work()
{
	for(int i=1;i<=n;i++)
		d[i]=1ll;
	for(int no=1;no<=m+1;no++)
	{
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		ti=0,co=0,top=0;
		for(int i=1;i<=n;i++)
			if(!dfn[i])
				tarjan(i,no<<1);
		for(int i=1;i<=n;i++)
			d[i]=d[i]*p+(ll)dcc[i];
	}
}
inline int calc(int u,int v)
{
	f1=getfa(u),f2=getfa(v);
	if(f1!=f2)//不在一个集合内最大流为0 
		return 0;
	if(dcc[u]!=dcc[v])//不在一个dcc内最大流为1
		return 1;
	if(d[u]==d[v])//用hash判断每次的dcc是否完全相同 
		return 3;/*如果删掉任意一条边,u,v仍在同一个dcc内
	则u,v在同一个三联通分量内,即最大流为3*/
	return 2;//否则最大流为2	
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		fa[i]=i;
	int u,v;
	for(int i=1;i<=m;i++)
	{
		u=read(),v=read();
		add(u,v),add(v,u);
		f1=getfa(u),f2=getfa(v);
		if(f1!=f2)fa[f1]=f2;
	}
	work();
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans+=calc(i,j);
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Rainbow_qwq (赞：4)

[P4214 【[CERC2015]Juice Junctions】
](https://www.luogu.com.cn/problem/P4214)

# 思路

一眼最小割树？不行， $n\le3000$ ，肯定要 TLE 。

发掘一下题目性质：

> 每个节点最多可以连接 $3$ 条管道

所以，任意两点间最大流一定 $\le 3$ ！

那就可以分类讨论，先把求最大流转成求最小割。

1. 最小割为 $0$

那这两个点 $u,v$ 就不在一个联通块里。直接用并查集判断即可。

2. 最小割为 $1$

割掉 $1$ 条边，两个点就分开了，这让我们想到了什么呢？

$\text{Tarjan}$ 求割边（桥）与边双连通分量！

（不会 Tarjan 求边双连通分量可以去搜索学习

一遍 $\text{Tarjan}$ 求出每个点所在的边双连通分量，如果两个点不在一个边双连通分量里，答案为 $1$ 。

求边双连通分量的代码：
```cpp
int dfn[maxn],low[maxn],frm[maxn],idx;
int bel[maxn],scc;
stack<int>s;
//frm[i] 表示 i 从哪条边过来
void dfs(int u)
{
	dfn[u]=low[u]=++idx;
	s.push(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(frm[u]^1)||vis[i])continue;
		if(!dfn[v]){
			frm[v]=i;dfs(v);
			low[u]=min(low[u],low[v]);
		}else low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]!=low[u])return;
	scc++;int v;
    // frm[u] 为割边
	do{
		v=s.top();s.pop();
		bel[v]=scc;
	}while(u!=v);
}
inline void tarjan()
{
	scc=idx=0;
	For(i,1,n)dfn[i]=low[i]=frm[i]=bel[i]=0;
	For(i,1,n)if(!dfn[i])dfs(i);
}
```

3. 最小割为 $2$

有点复杂。

要割掉 $2$ 条边才能割断，看到 $0\le m\le 4500$ ，可以想到：

**我们可以暴力割掉每一条边，再像最小割为 $1$ 时一样求边双连通分量** ，就可以啦！

如果 2 个点在有一种割掉一条边情况下，属于不同边双连通分量了，答案就为 $2$ 。

割掉每一条边，每个点会有 $m$ 个值，这时可以使用 Hash ，就能 $O(1)$ 判断了。

设 $H_i$ 为 $i$ 的哈希值，那加入割了一条边后，属于 $bel_i$ 这个边双连通分量，那就 $H_i=H_i \times base+bel_j$ ， $H_i$ 用 `unsigned long long` 存， `base` 随便设一个数。

如果 2 个点的 Hash 值不同，那割掉某一条边后，再割一次就可以了，答案为 $2$ 。

核心代码： ~~取了 `base = 19491001`~~
```cpp
for(int i=2;i<=tot;i+=2)
{
	vis[i]=vis[i^1]=1;//标记为不能走
	tarjan();
	For(j,1,n)H[j]=H[j]*19491001+bel[j];
	vis[i]=vis[i^1]=0;
}
```

4. 最小割为 $3$

显然，不属于以上情况，就是 $3$ 。

$m$ 遍 Tarjan + $n^2$ 次 $O(1)$ 判断，复杂度： $O(m(n+m)+n^2)$

完整代码：
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define maxn 3005
int n,m,res;
struct edge{
	int to,nxt;
}e[maxn<<3];
int tot,head[maxn];
bool vis[maxn<<3];
inline void adde(int u,int v){
	e[++tot]=(edge){v,head[u]};
	head[u]=tot;
}

int fa[maxn];
int getf(int x){return fa[x]==x?x:fa[x]=getf(fa[x]);}

int dfn[maxn],low[maxn],frm[maxn],idx;
int bel[maxn],scc;
stack<int>s;
void dfs(int u)
{
	dfn[u]=low[u]=++idx;
	s.push(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(frm[u]^1)||vis[i])continue;
		if(!dfn[v]){
			frm[v]=i;dfs(v);
			low[u]=min(low[u],low[v]);
		}else low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]!=low[u])return;
	scc++;int v;
	do{
		v=s.top();s.pop();
		bel[v]=scc;
	}while(u!=v);
}
inline void tarjan()
{
	scc=idx=0;
	For(i,1,n)dfn[i]=low[i]=frm[i]=bel[i]=0;
	For(i,1,n)if(!dfn[i])dfs(i);
}

unsigned long long H[maxn];
signed main()
{
	tot=1,n=read(),m=read();
	For(i,1,n)fa[i]=i;
	For(i,1,m){
		int u=read(),v=read();
		adde(u,v);adde(v,u);
		fa[getf(u)]=getf(v);
	}
	for(int i=2;i<=tot;i+=2)
	{
		vis[i]=vis[i^1]=1;
		tarjan();
		For(j,1,n)H[j]=H[j]*19491001+bel[j];
		vis[i]=vis[i^1]=0;
	}
	tarjan();
	For(i,1,n)
		For(j,i+1,n){
			if(getf(i)!=getf(j));
			else if(bel[i]!=bel[j])res++;
			else if(H[i]!=H[j])res+=2;
			else res+=3;
		}
	cout<<res;
    return 0;
}
```

---

## 作者：Raymondzll (赞：3)

## P4214 Juice Junctions

### 前言

### 注：与最高赞题解的区别是不用缩点。

看到题解区有一篇说道：

>应该没有人不会最小割树吧。

>我觉得能找到这题的应该都会最小割树。

显然，我被开除人籍了。

最令人气愤的是，这标签里，竟然没有点双！

无意义内容不多说了，希望管理能给过。

### 解题思路

题目中有一个重要条件：每个节点最多连接 $3$ 条管道。

这就意味着，每个点对的贡献无非 $0,1,2$ 或 $3$。

$0$ 就意味着，这两个点不连通（无向图）。

$1$ 稍微复杂一点，它的意思是，两点间没有两条**没有公共部分的**路径。

这里给出两种理解方式：这两点的路径必然经过割边，或者这两点不在一个边双连通分量里。

后者应该更方便程序实现吧。

$2$ 和 $3$ 怎么判断呢？

~~[P6658 边三连通分量](https://www.luogu.com.cn/problem/P6658)~~

这道题赤裸裸的平方级别算法好吧，你给我整一个黑题干什么。

实际上换个角度考虑，边三连通分量也就意味着**无论你删去哪一条边，这两（多）个点都属于一个边双连通分量**。

哦，我们知道了，预处理一下每条边删去后每个点属于哪个边双连通分量，如果两个点在某条边删去之后所属的边双连通分量不一致，那么他们的答案就不是 $3$。

乍一看这个算法好像要 $O(mn+n^2m)$。

这时候就需要点小 trick 了，对每个点在每条边删去后的所属边双情况进行哈希。

时间复杂度大约 $O(mn+n^2)$。

总结：先预处理每个点的哈希值（意义见上），再预处理原图每个点所属的连通块和边双连通分量，最后 $n^2$ 枚举点对判断。

### 代码部分

```cpp
#include <bits/stdc++.h>
using namespace std;
void file(string str){
	freopen((str+".in").c_str(),"r",stdin);
	freopen((str+".out").c_str(),"w",stdout);
}
int n,m;
int v[9010],nxt[9010],tot=1,head[3010];//链式前向星
bool vis[3010];
int dfn[3010],low[3010],idx;//tarjan必备
int mark[9010];//是不是割边
int col[3010],bcc;//所属边双
int has[3010];//hash
int fade;//删去的边的编号
void addedge(int a,int b){v[++tot]=b;nxt[tot]=head[a];head[a]=tot;}
void tarjan(int u,int fa){
	vis[u]=1;dfn[u]=low[u]=++idx;
	for(int i=head[u];i;i=nxt[i]){
		if(i==fade||i==(fade^1))continue;//删掉了就不能走
		int ch=v[i];
		if(!vis[ch]){
			tarjan(ch,u);
			low[u]=min(low[u],low[ch]);
			if(low[ch]>dfn[u])mark[i]=mark[i^1]=1;//两条都标记
		}else if(ch!=fa) low[u]=min(low[u],dfn[ch]);
	}
}
void dfs(int u){
	col[u]=bcc;
	for(int i=head[u];i;i=nxt[i]){
		int ch=v[i];
		if(i!=fade&&i!=(fade^1)&&col[ch]==0&&mark[i]!=1)dfs(ch);//这里也要记得删掉了的不能走
	}
}
int colh[3010],cc;//这里是判连通性的，为了和边双的变量做出区别，在最后加了个字母h
void dfsh(int u){
	colh[u]=cc;
	for(int i=head[u];i;i=nxt[i]){
		int ch=v[i];
		if(!colh[ch])dfsh(ch);
	}
}
long long final;
void clear(){//不清空col害死人
	memset(vis,0,sizeof(vis));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(col,0,sizeof(col));
	memset(mark,0,sizeof(mark));
	bcc=idx=0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){int a,b;scanf("%d%d",&a,&b);addedge(a,b);addedge(b,a);}
	for(int i=1;i<=m;i++){
		fade=i*2;clear();
		for(int j=1;j<=n;j++){if(!vis[j])tarjan(j,0);}
		for(int j=1;j<=n;j++){if(!col[j]){bcc++;dfs(j);}}
		for(int j=1;j<=n;j++)has[j]=(1ll*has[j]*131+col[j])%1000000007;
	}
	fade=0;clear();
	for(int i=1;i<=n;i++){if(!vis[i])tarjan(i,0);}
	for(int i=1;i<=n;i++){if(!col[i]){bcc++;dfs(i);}}
	for(int i=1;i<=n;i++){if(!colh[i]){cc++;dfsh(i);}}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(colh[i]!=colh[j])final+=0;
			else if(col[i]!=col[j])final+=1;
			else if(has[i]!=has[j])final+=2;
			else final+=3;
		}
	}
	printf("%lld",final);
	return 0;
}
```

---

## 作者：__FL__ (赞：2)

最小割树模板。
## 最小割树
我们先简单介绍一下最小割树的思想。

最小割树满足这样的一种性质：对于一张流量图的最小割树，**这张图上任意两点的最小割，等于最小割树上对应两点的最小割**。

这类题目一般伴有多组询问，如果我们已经得到了最小割树，就可以根据树的良好性质，$O(N^2)$ 累加得到答案。

那么我们怎么得到最小割树呢？

过程是这样的：对于一张流量图，我们任取两个点 $s,t$，然后求 $s,t$ 之间的最小割 $c$。显然这时两个点不再连通，并且整个图被分为两部分，一部分与 $s$ 连通，另一部分不与 $s$ 连通。我们在树中（注意不是流量图）连一条 $(s,t)$ 的权为 $c$ 的双向边，然后将与 $s$ 连通的一部分点在 $s$ 那头递归建立最小割子树，另一部分点在 $t$ 那头建立最小割子树。这里运用的是分治思想。

尤其需要注意的是，每次求最小割时，都应在**流量图原图**上跑最大流。

于是我们得到了一棵最小割树。

这个思路的证明比较复杂，但是如果你将树的性质和“最小割要在原图上跑”这个问题联合起来想一想，应该能隐约想到它是正确的。至于其他可以自行查阅证明。

这道题提到了一个性质：每个节点最多可以连接 $3$ 条管道，这意味着这道题可以用 Tarjan 等算法解决。这里不再赘述。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 6005,M = 30005,inf = 1e9;
int n,m,u,v,head[N],nxt[M],to[M],w[M],init_w[M],cnt=-1,s,t,d[N],a[N],tmp[N],f[N>>1][N>>1],sum;
queue<int>q;
vector<pair<int,int>>vec[N];
inline void add(int u,int v,int c) {nxt[++cnt] = head[u],head[u] = cnt,to[cnt] = v,w[cnt] = c;}
inline void Add(int u,int v,int c) {add(u,v,c); add(v,u,c);}
inline void Acc(int u,int v,int c) {vec[u].push_back({v,c}); vec[v].push_back({u,c});}
bool bfs()
{
	while (!q.empty()) q.pop();
	q.push(s);
	memset(d,0,sizeof d);
	d[s] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; ~i; i = nxt[i])
		{
			int v = to[i];
			if (w[i] && !d[v])
			{
				d[v] = d[u]+1;
				if (v == t) return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
int dfs(int u,int limit)
{
	if (u == t) return limit;
	int flow = 0;
	for (int i = head[u]; ~i; i = nxt[i])
	{
		int v = to[i];
		if (w[i] && d[v] == d[u]+1)
		{
			int p = dfs(v,min(w[i],limit-flow));
			if (!p) d[v] = 0;
			flow += p;
			w[i] -= p;
			w[i^1] += p;
			if (flow == limit) return flow;
		}
	}
	return flow;
}
int Dinic()
{
	int ans = 0;
	while (bfs())
		ans += dfs(s,inf);
	return ans;
}
void build(int l,int r)
{
	if (l >= r) return;
	for (int i = 0; i <= cnt; i++)
		w[i] = init_w[i];
	s = a[l],t = a[r];
	int c = Dinic();
	Acc(s,t,c);
	int f = l-1,g = r+1;
	for (int i = l; i <= r; i++)
		if (d[a[i]]) tmp[++f] = a[i];
		else tmp[--g] = a[i];
	for (int i = l; i <= r; i++)
		a[i] = tmp[i];
	build(l,f);
	build(g,r);
}
void init(int u,int mmin,int root,int fa)
{
	f[root][u] = mmin;
	for (pair<int,int>i: vec[u])
		if (i.first != fa)
			init(i.first,min(mmin,i.second),root,u);
}
int main()
{
	memset(head,-1,sizeof head);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		Add(u,v,1);
		Add(v,u,1);
	}
	for (int i = 0; i <= cnt; i++)
		init_w[i] = w[i];
	for (int i = 1; i <= n; i++)
		a[i] = i;
	build(1,n);
	for (int i = 1; i <= n; i++)
		init(i,inf,i,i);
	for (int i = 1; i <= n; i++)
		for (int j = i+1; j <= n; j++)
			sum += f[i][j];
	cout << sum/2;
	return 0;
}
```

---

## 作者：JiaY19 (赞：2)

[$\text{可能更好的阅读体验}$](https://www.cnblogs.com/mfeitveer/p/15944941.html)

最小割树板子题。

一开始我用通常我写的 $\text{Isap}$ 去试了试，只有 $\text{65pts}$。

后面尝试使用 $\text{Dinic}$，居然就有了 $\text{100pts}$，跑了 $14s$。

最后题解区说可以用 $\text{EK}$ 跑，我试了一下，居然只跑了 $\text{6s}$。

好吧，$\text{EK}$ 的崛起了属于是。

可为啥 $\text{Isap}$ 比 $\text{Dinic}$ 慢呢，令人极度疑惑。

### 思路

应该没有人不会最小割树吧。

我觉得能找到这题的应该都会最小割树。

所以这里我可以对这道题网络流做法的迷惑的复杂度，做一些感性理解。

由于 $\text{EK}$ 是单次不断寻找可行边，然后我们即可发现，本题中每个点的度数小于等于三，即到汇点的可行边只有三条，而又限制了每条边的流量严格为一。

故其网络流的最大复杂度应该为 $O(3n)$ ，就相当于 $O(n)$ 了。

故总复杂度应为 $O(n^2)$

而 $\text{dinic}$ 需要不断的使用 $\text{dfs}$ 寻找，自然多了很多其他的情况，所以更劣一些。

给 $\text{EK}$ 的代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3010;
const int M = 20000;
const int inf = 1e9 + 7;

int T , n , m , s , t , q , cnt , maxflow;
int id[N] , que[N] , vis[N] , tmp[N] , head[N];

struct edge
{
	int to , nxt , val , sum;
}e[M];

struct Pre
{
	int v , edge;
}pre[N];

inline int read()
{
	int asd = 0 , qwe = 1; char zxc;
	while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
	while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
	return asd * qwe;
}

inline void add(int x , int y , int z)
{
	e[++cnt] = {y , head[x] , z , z} , head[x] = cnt;
	e[++cnt] = {x , head[y] , 0 , 0} , head[y] = cnt;
}

inline int bfs()
{
	queue<int> q; 
	memset(que , 0 , sizeof que);
	memset(pre , -1 , sizeof pre);
	q.push(s) , que[s] = 1;
	while(q.empty() == 0)
	{
		int x = q.front(); q.pop();
		for(int i = head[x];i;i = e[i].nxt)
			if(que[e[i].to] == 0 && e[i].val)
			{
				que[e[i].to] = 1;
				pre[e[i].to] = (Pre){x , i};
				if(e[i].to == t) return 1;
				q.push(e[i].to);
			}
 	}
 	return 0;
}

inline void init()
{
	for(int i = 0;i <= cnt;i++) e[i].val = e[i].sum;
}

inline int EK(int ss , int ts)
{
	s = ss , t = ts , maxflow = 0 , init();
	while(bfs())
	{
		int minn = inf;
		for(int i = t;i != s;i = pre[i].v) minn = min(minn , e[pre[i].edge].val);
		for(int i = t;i != s;i = pre[i].v) e[pre[i].edge].val -= minn;
		maxflow += minn;
	}
	return maxflow;
}

struct GHT
{
	edge tr[M];
	int tot , hed[N] , ans[N][N];
	
	inline void add_tree(int x , int y , int z)
	{
		tr[++tot] = {y , hed[x] , z} , hed[x] = tot;
		tr[++tot] = {x , hed[y] , z} , hed[y] = tot;
	}
	
	inline void find(int now)
	{
		vis[now] = 1;
		for(int i = head[now];i;i = e[i].nxt)
			if(vis[e[i].to] == 0 && e[i].val) find(e[i].to);
	}
	
	inline void build(int l ,int r)
	{
		if(l >= r) return;
		int x = id[l] , y = id[l + 1] , sum = EK(x , y);
		int ls = l , rs = r;
		memset(vis , 0 , sizeof vis) , find(x);
		add_tree(x , y , sum);
		for(int i = l;i <= r;i++)
			tmp[(vis[id[i]] ? ls++ : rs--)] = id[i];
		for(int i = l;i <= r;i++) id[i] = tmp[i];
		build(l , ls - 1) , build(rs + 1 , r);
	}
	
	inline void get(int now , int fa , int dis , int gen)
	{
		ans[gen][now] = dis;
		for(int i = hed[now];i;i = tr[i].nxt)
			if(tr[i].to != fa) get(tr[i].to , now , min(dis , tr[i].val) , gen);
	}
	
	inline void solve()
	{
		for(int i = 1;i <= n;i++) id[i] = i;
		build(1 , n);
		for(int i = 1;i <= n;i++) get(i , 0 , inf , i);
	}
	
	inline int ask()
	{
		int res = 0;
		for(int i = 1;i <= n;i++)
			for(int j = i + 1;j <= n;j++) res += ans[i][j];
		return res;
	}
}tree;

int main()
{
	n = read() , m = read() , cnt = 1;
	for(int i = 1;i <= m;i++)
	{
		int x = read() , y = read();
		add(x , y , 1) , add(y , x , 1);
	}
	tree.solve();
	cout << tree.ask();
	return 0;
} 
```



---

## 作者：Tari (赞：2)

最小割树+并查集。

我们知道，$u,v$ 两点的最小割的值即为最小割树中 $u,v$ 路径上的最小边权；我们可以将最小割树上的边 $(u,v,w)$ 按边权从大到小排序，加入树中，同时用并查集维护 $u,v$ 所在连通块的 $size$ ，那么每条边的贡献即为 $w\times size_{fa[u]} \times size_{fa[v]}$。

**（但是这个方法没用用到度数小于等于3的特点，可能不够优秀）**

感谢 bztMinamoto 告诉我这题卡dinic放ek ~~（迷惑）~~ 

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#define R register int
using namespace std;
namespace Luitaryi {
inline int g() { R x=0,f=1;
	register char s; while(!isdigit(s=getchar())) f=s=='-'?-1:f;
	do x=x*10+(s^48); while(isdigit(s=getchar())); return x*f;
} const int N=3010,M=9010,Inf=0x3f3f3f3f;
int n,m,S,T,ans,tim;
int vr[M],nxt[M],fir[N],w[M],l[M],d[N],s[N],t[N],fa[N],sz[N],cnt=1;
inline void add(int u,int v,int ww) {
	vr[++cnt]=v,nxt[cnt]=fir[u],fir[u]=cnt,l[cnt]=ww;
	vr[++cnt]=u,nxt[cnt]=fir[v],fir[v]=cnt,l[cnt]=ww;
}
queue<int> q;
inline bool bfs() {
	memset(d,0,sizeof d);
	d[S]=1,q.push(S);
	while(q.size()) { R u=q.front(); q.pop();
		for(R i=fir[u],v;i;i=nxt[i]) 
			if(w[i]&&!d[v=vr[i]]) d[v]=i,q.push(v);
	} return d[T];
}
inline int ek() {
	R ret=0; memcpy(w,l,cnt+1<<2);
	while(bfs()) {
		++ret;
		for(R i=T;i!=S;i=vr[d[i]^1])
			--w[d[i]],++w[d[i]^1];
	} return ret;
}
struct node {
	int u,v,w;
	inline bool operator < (const node &that) const
		{return w>that.w;}	
}e[N];
inline void build(int l,int r) { 
	if(l>=r) return ; 
	S=s[l],T=s[l+1];
	R p=l-1,q=r+1,w=ek();
	for(R i=l;i<=r;++i) 
		d[s[i]]?t[++p]=s[i]:t[--q]=s[i];
	e[++tim]=(node){S,T,w};
	for(R i=l;i<=r;++i) s[i]=t[i]; 
	build(l,p),build(q,r);
}
inline int getf(int x) {return x==fa[x]?x:fa[x]=getf(fa[x]);}
inline void merge(int i) {
	R u=getf(e[i].u),v=getf(e[i].v); 
	fa[u]=v;
	ans+=e[i].w*sz[u]*sz[v];
	sz[v]+=sz[u];
}
inline void main() {
	n=g(),m=g();
	for(R i=1,u,v;i<=m;++i) 
		u=g(),v=g(),add(u,v,1);
	for(R i=1;i<=n;++i) s[i]=i;
	build(1,n); for(R i=1;i<=n;++i) fa[i]=i,sz[i]=1;
	sort(e+1,e+n); for(R i=1;i<n;++i) merge(i);
	printf("%d\n",ans);
}
} signed main() {Luitaryi::main(); return 0;}
```

---

## 作者：bztMinamoto (赞：2)

打广告：[这里](https://www.cnblogs.com/bztMinamoto/p/9571156.html)

首先最大流等于最小割，那么可以转化为最小割树来做（不知道什么是最小割树的可以看看这题->[这里](https://www.cnblogs.com/bztMinamoto/p/9570614.html)）

具体的做法似乎是$hash[i][j]$表示最小割为$i$时点$j$是否与$S$连通

然后据Claris大爷说这题卡dinic，只能用EK

顺便吐槽一句，Claris大爷的代码真的不能看……
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define inf 0x3f3f3f3f3
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=3005;
int ver[N<<2],Next[N<<2],edge[N<<2],head[N],tot=1;
inline void add(int u,int v,int e){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
	ver[++tot]=u,Next[tot]=head[v],head[v]=tot,edge[tot]=e;
}
int dep[N],q[N],n,m,S,T,ans;
bool bfs(){
	int l=0,r=1;memset(dep+1,-1,sizeof(int)*n);dep[q[0]=S]=0;
	while(l<r){
		int u=q[l++];
		for(int i=head[u];i;i=Next[i])
		if(dep[ver[i]]<0&&edge[i])
		dep[ver[i]]=i,q[r++]=ver[i];
	}
	return ~dep[T];
}
int id[N],tmp[N];
unsigned Pow=1,Hash[4][N];
void solve(int L,int R){
	if(L==R) return;
	for(int i=2;i<=tot;i+=2)
	edge[i]=edge[i^1]=1;
	S=id[L],T=id[R];int flow=0,j;
	while(bfs()){
		++flow;
		for(int i=T;i!=S;i=ver[j^1]) --edge[j=dep[i]],++edge[j^1];
	}
	Pow*=233;
	for(int i=1;i<=n;++i)
	if(~dep[i]) Hash[flow][i]+=Pow;
	int l=L,r=R;
	for(int i=L;i<=R;++i)
	if(~dep[id[i]]) tmp[l++]=id[i];
	else tmp[r--]=id[i];
	memcpy(id+L,tmp+L,sizeof(int)*(R-L+1));
	solve(L,l-1),solve(r+1,R);
}
int main(){
	//freopen("testdata.in","r",stdin);
	n=read(),m=read();
	for(int i=1,u,v;i<=m;++i)
	u=read(),v=read(),add(u,v,1);
	for(int i=1;i<=n;++i) id[i]=i;
	solve(1,n);
	for(int i=1;i<=n;++i)
	for(int j=i+1;j<=n;++j)
	for(int k=0;k<=3;++k)
	if(Hash[k][i]!=Hash[k][j]) {ans+=k;break;}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Charlie_ljk (赞：1)

- [推一下自己的最小割树学习笔记](https://www.cnblogs.com/Charlieljk/p/18729786)。

# 最小割树

最小割树就是通过分治建出一棵树，树上两点的最小割就等于原图上的最小割，树上两点路径唯一，其最小割就等于路径上边权的最小值。

建树时，任意选择两点最为 $s,t$ 跑最小割，求得 $ans_{s,t}$，并将其分为两个集合 $S,T$，对于 $x\in S,y\in T$，有 $ans_{x,y}=ans_{y,x}=\min(ans_{s,t},ans_{x,s},ans_{t,y})$。

之后对于这两部分再分别跑最小割，重复上述步骤，就能在理论（网络流的复杂度跑不满） $O(n^3m)$ 的复杂度内建出一棵最小割树。

# 答案处理

因为树有很多性质，最小割本身也有很多性质，所以绝不用对于每个询问都遍历一遍树这么粗鲁的做法。

## 建树

建树就是对于每一层分治将 $s,t$ 连上边权为 $ans_{s,t}$ 的边即可，$ans_{s,t}$ 为本次最小割跑出的答案。

因为原图两点的最小割就等于树上两点路径上边权的最小值，根据这点就可以有很多种处理方式了，具体有树上倍、lca 等多种求法，但是本题 $Q$ 与 $n^2$ 同级，就不如以每个点为根遍历一遍树，复杂度 $O(n^2)$。

## 不建树

根据上面的式子，对于 $x\in S,y\in T$，有 $ans_{x,y}=ans_{y,x}=\min(ans_{s,t},ans_{x,s},ans_{t,y})$。

所以可以在分治的同时处理出答案，不需要把树建出来。

# 一些细节

- 每一次跑最小割前要将所有边恢复初始状态。
- 本题为无向图，要所以可以不用对于每一个边再建一条流量为 $0$ 的反边了，建双向边即可。
- 注意分治时每层的 $s,t$ 不同，根据需要保存本层的 $s,t$。

# 代码如下

采用不建树的方法，跑的还是比较快的，但是空间上会劣一点：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
using namespace std;
const int N=3010,M=9010,inf=0x3f3f3f3f;
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
inline bool blank(const char x) {return !(x^32)||!(x^10)||!(x^13)||!(x^9);}
template<typename Tp> inline void read(Tp &x) {x=0; register bool z=true; register char a=gc(); for(;!isdigit(a);a=gc()) if(a=='-') z=false; for(;isdigit(a);a=gc()) x=(x<<1)+(x<<3)+(a^48); x=(z?x:~x+1);}
inline void read(double &x) {x=0.0; register bool z=true; register double y=0.1; register char a=gc(); for(;!isdigit(a);a=gc()) if(a=='-') z=false; for(;isdigit(a);a=gc()) x=x*10+(a^48); if(a!='.') return x=z?x:-x,void(); for(a=gc();isdigit(a);a=gc(),y/=10) x+=y*(a^48); x=(z?x:-x);}
inline void read(char &x) {for(x=gc();blank(x)&&(x^-1);x=gc());}
inline void read(char *x) {register char a=gc(); for(;blank(a)&&(a^-1);a=gc()); for(;!blank(a)&&(a^-1);a=gc()) *x++=a; *x=0;}
inline void read(string &x) {x=""; register char a=gc(); for(;blank(a)&&(a^-1);a=gc()); for(;!blank(a)&&(a^-1);a=gc()) x+=a;}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y) {read(x),read(y...);}
template<typename Tp> inline void write(Tp x) {if(!x) return pc(48),void(); if(x<0) pc('-'),x=~x+1; register int len=0; register char tmp[64]; for(;x;x/=10) tmp[++len]=x%10+48; while(len) pc(tmp[len--]);}
inline void write(const double x) {register int a=6; register double b=x,c=b; if(b<0) pc('-'),b=-b,c=-c; register double y=5*powl(10,-a-1); b+=y,c+=y; register int len=0; register char tmp[64]; if(b<1) pc(48); else for(;b>=1;b/=10) tmp[++len]=floor(b)-floor(b/10)*10+48; while(len) pc(tmp[len--]); pc('.'); for(c*=10;a;a--,c*=10) pc(floor(c)-floor(c/10)*10+48);}
inline void write(const pair<int,double>x) {register int a=x.first; if(a<7) {register double b=x.second,c=b; if(b<0) pc('-'),b=-b,c=-c; register double y=5*powl(10,-a-1); b+=y,c+=y; register int len=0; register char tmp[64]; if(b<1) pc(48); else for(;b>=1;b/=10) tmp[++len]=floor(b)-floor(b/10)*10+48; while(len) pc(tmp[len--]); a&&(pc('.')); for(c*=10;a;a--,c*=10) pc(floor(c)-floor(c/10)*10+48);} else cout<<fixed<<setprecision(a)<<x.second;}
inline void write(const char x) {pc(x);}
inline void write(const bool x) {pc(x?49:48);}
inline void write(char *x) {fputs(x,stdout);}
inline void write(const char *x) {fputs(x,stdout);}
inline void write(const string &x) {fputs(x.c_str(),stdout);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y) {write(x),write(y...);}
int n,m,s,t,ans,cs[N],ct[N],dep[N],node[N],f[N][N];
int tot=1,now[N],head[N],nxt[M],to[M],w[M];
inline void add(int x,int y)
{
	nxt[++tot]=head[x],to[head[x]=tot]=y,w[tot]=1;
	nxt[++tot]=head[y],to[head[y]=tot]=x,w[tot]=1;
}
inline bool bfs()
{
	queue<int>q; memset(dep,0,sizeof(dep));
	for(memcpy(now,head,sizeof(now)),q.push(s),dep[s]=1;!q.empty();)
	{
		int x=q.front(); q.pop();
		for(int i=head[x],y;y=to[i];i=nxt[i]) if(w[i]&&!dep[y])
		{dep[y]=dep[x]+1,q.push(y); if(y==t) return true;}
	} return false;
}
inline int dfs(int x,int sum)
{
	if(x==t||!sum) return sum; int sur,res=0;
	for(int &i=now[x],y;y=to[i];i=nxt[i]) if(w[i]&&dep[y]==dep[x]+1)
	{
		if(!(sur=dfs(y,min(sum,w[i])))) {dep[y]=-1; continue;}
		w[i]-=sur,w[i^1]+=sur,res+=sur; if(!(sum-=sur)) break;
	} return res;
}
inline void build(int l,int r)
{
	if(l>=r) return ; s=node[l],t=node[r]; int res=0,ns=0,nt=0;
	for(int i=2;i<tot;i+=2) w[i]=w[i^1]=w[i]+w[i^1]>>1;
	while(bfs()) res+=dfs(s,inf); f[s][t]=f[t][s]=res;
	for(int i=l,x;i<=r;i++) dep[x=node[i]]?cs[++ns]=x:ct[++nt]=x;
	for(int i=1;i<=ns;i++) node[l+i-1]=cs[i];
	for(int i=1;i<=nt;i++) node[l+ns+i-1]=ct[i];
	int os=s,ot=t; build(l,l+ns-1),build(l+ns,r); 
	for(int i=1,j,x,y;i<=ns;i++) for(x=node[l+i-1],j=1;j<=nt;j++)
		y=node[l+ns+j-1],f[x][y]=f[y][x]=min({f[x][os],f[ot][y],res});
}
signed main()
{
	read(n,m),memset(f,0x3f,sizeof(f)); for(int i=1;i<=n;i++) node[i]=i; 
	for(int x,y;m--;) read(x,y),add(x,y); build(1,n);
	for(int i=1,j;i<=n;i++) for(j=i+1;j<=n;j++) ans+=f[i][j]; write(ans);
}
```

---

## 作者：yanwh1 (赞：1)

之前在打网络流题目时并不会最小割树，学完后来打篇正解。
# 形式化题目
给一张无向图，要求你计算出图中任意两点 $a,b (a<b)$ 的最大流之和。
# 思路
## 思路一：我会网络流！
网络流大家应该都会吧，如果暴力地用网络流一个个去查的话，将会喜提 30pts。
## 思路二：我会最小割树！
相信大家都会打最小割树吧（不会的出门左转去打一下 [P4897 【模板】最小割树（Gomory-Hu Tree）](https://www.luogu.com.cn/problem/P4897)）。

这里简单讲解一下，最小割树就是将一张图改为树，图上每两个点的最小割就是树上两个点的最小割。

于是我们将在图上做网络流变成了在树上做网络流，复杂度骤减。于是我们还是喜提 30pts。
## 思路三：我会最小割树加优化！
我们每次只搜两个点的网络流就要搜索整棵树，实在是太浪费了，于是我们转换为每一次查询会查出所有小于该点的点最小割之和，于是最终复杂度为 $O(n \times m)$。
# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}inline void write(long long x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=3005,M=4505,inf=INT_MAX;
int head[M],to[M<<1],nxt[M<<1],w[M<<1],cnt=1,n,m,s,t;
inline void add(int u,int v,int vl){nxt[++cnt]=head[u],to[cnt]=v,w[cnt]=vl,head[u]=cnt;}
int dis[N],now[N],rs[N],rs1[N],rs2[N];
queue<pair<int,int>>qe;
struct edge{int v,w;};
vector<edge>qwe[N];
inline int bfs(){
	for(rint i=1;i<=n;i++)dis[i]=inf;
	queue<int>q;q.push(s),dis[s]=0,now[s]=head[s];
	while(!q.empty()){
		int u=q.front();q.pop();
		for(rint i=head[u];i;i=nxt[i]){
			int v=to[i],vl=w[i];
			if(vl&&dis[v]==inf){
				q.push(v);
				dis[v]=dis[u]+1;
				now[v]=head[v];
				if(v==t)return 1;
			}
		}
	}return 0;
}inline int dfs(int u=s,int mn=inf){
	if(u==t||!mn)return mn;
	int k,res=0;
	for(rint i=now[u];i;i=nxt[i]){
		now[u]=i;int v=to[i],vl=w[i];
		if(vl&&dis[v]==dis[u]+1){
			k=dfs(v,min(vl,mn));
			if(!k)dis[v]=inf;
			w[i]-=k,w[i^1]+=k;
			qe.push(make_pair(i,k));
			res+=k,mn-=k;
			if(!mn)break;
		}
	}return res;
}inline int dinic(int u,int v){
	s=u,t=v;int ans=0;
	while(bfs())ans+=dfs();
	while(!qe.empty()){
		pair<int,int> res=qe.front();qe.pop();
		w[res.first]+=res.second;
		w[res.first^1]-=res.second;
	}return ans;
}inline void build(int l,int r){
	int m1=0,m2=0;
	if(l==r)return;
	int ans=dinic(rs[l],rs[l+1]);
	qwe[rs[l]].push_back({rs[l+1],ans});
	qwe[rs[l+1]].push_back({rs[l],ans});
	for(rint i=l;i<=r;i++){
		if(dis[rs[i]]!=inf)rs1[++m1]=rs[i];
		else rs2[++m2]=rs[i];
	}for(rint i=1;i<=m1;i++)rs[i+l-1]=rs1[i];
	for(rint i=1;i<=m2;i++)rs[i+l+m1-1]=rs2[i];
	build(l,l+m1-1),build(l+m1,r);
}inline int query(int u,int f,int mx,int mn){
	int sum=0;
	for(rint i=0;i<qwe[u].size();i++){
		int v=qwe[u][i].v,w=qwe[u][i].w;
		if(f==v)continue;
		if(v<mx)sum+=min(mn,w);
		sum+=query(v,u,mx,min(mn,w));
	}return sum;
}
signed main(){
	n=read(),m=read();
	for(rint i=1;i<=n;i++)rs[i]=i;
	for(rint i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v,1),add(v,u,1);
	}build(1,n);int ans=0;
	for(rint i=2;i<=n;i++)
		ans+=query(i,0,i,inf);
	write(ans);
	return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

本文同时作为我的最小割树笔记，很抱歉笔者由于实力不够，并不能给出一个自然的想到最小割树的推导方式，而是通过介绍过程—证明正确性的方式给出最小割树的构建方式。

在这里评价一下最小割树：遇强则强，速度不详/kx。

# Part 2：正文

## 最小割树的定义

对于一张图 $G$，我们定义一颗有边权树 $T$ 为图 $G$ 的最小割树当且仅当其满足对于**任意**一对点对 $(u,v)$，其在 $T$ 上的简单路径上**边权最小值**为其在 $G$ 上的最小割。

## 最小割树的构造

最小割树以递归的方式构造。下文中，我们设当前的处理到的点集为 $V$，初始时，$V$ 为 $1$ 到 $n$ 中的全部点。

在每一步中，我们将在 $V$ 中任意选择两个不同的点 $(u,v)$，以 $u$ 为源点，$v$ 为汇点，求出其在 $G$ 中两点之间的最小割 $cut(u,v)$。然后我们在树 $T$ 中 $(u,v)$ 间连接一条边权为 $cut$ 的边，并将能从起点 $u$ 通过在残量网络上**未被割掉**的边到达的点划分到 $V_s$ 中，其余的划分到 $V_t$ 中，并递归构建 $V_s,V_t$。边界条件为 $|V|=1$。

容易发现，这样做连接出的一定是一颗树，证明可以考虑从边界倒序构建。

## 最小割树的证明

现在的问题转为，如何证明按上文中的方式构建的 $T$ 满足最小割树的性质。

> Lemma1：在一步划分中，设当前选中的的两个点为 $u,v$，对于任意两个点 $u'\in V_s,v'\in V_t$，一定有 $cut(u,v)\ge cut(u',v')$。

证明是容易的。若 $cut(u,v)<cut(u',v')$，则此时 $u'$ 和 $v'$ 一定没有被完全割断。这违反了 $V_s$ 和 $V_t$ 之间的点不能通过在残量网络上未被割掉的边到达的性质。

> Lemma2：对于任意三个点 $u,v,w$，有 $cut(u,v)\ge \min(cut(u,w),cut(w,v))$。

更加容易证明。利用最小割等于最大流这一性质，我们发现从 $u$ 到 $v$ 的最大流一定有一种流法是 $u\rightarrow w\rightarrow v$， 也就是说  $cut(u,v)\ge \min(cut(u,w),cut(w,v))$。

> Lemma3：对于任意 $n$ 个点 $p_1,p_2,\cdots,p_n$，有 $cut(p_1,p_n)\ge \min\limits_{i=1}^{n-1}cut(p_i,p_i+1)$。

本质上是对 Lemma2 的多次使用。

现在我们可以开始证明了。设 $u,v$ 为树上任意不同两点，$u',v'$ 为树上 $u,v$ 简单路径上的边权最小值的边的两端点，且 $u,v$ 间有边相连。首先使用 Lemma3，我们有 $cut(u,v)\ge cut(u',v')$。而根据 Lemma1 和最小割树的构建方式，我们知道做完最小割后一定有 $cut(u,v)\leq cut(u',v')$，故 $cut(u,v)=cut(u',v')$。

## 最小割树的时间复杂度

考虑每一条边都需要跑一次网络流，边有 $n-1$ 条，那么复杂度应当是 $O(n^3m)$，但这只是理论上界，由于网络流大部分跑不满，而且随机选点使得难以定向构造一张图卡掉，故这个东西跑的速度一般很快。

同时这个题也做完了，最小割树建出来后从每个点 bfs 求出最小割即可，时间复杂度 $O(n^3m)$。

尽管这个复杂度不怎么对，但是实测最慢点只有 1.5s。

# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=3e3+7,M=2e4+7;
struct Dinic{
	struct edge{int to,nxt;int dis;}e[M<<1];
	int head[N],cur[N],dis[N],cnt,s,t;
	Dinic(){memset(head,-1,sizeof(head));cnt=0;}
	void add(int u,int v,int w){
		// Debug("%d %d %d\n",u,v,w);
		e[cnt].to=v;e[cnt].dis=w,e[cnt].nxt=head[u],head[u]=cnt++;
		e[cnt].to=u;e[cnt].dis=0,e[cnt].nxt=head[v],head[v]=cnt++;
	}
	bool bfs(){
		memset(dis,-1,sizeof(dis));dis[s]=0;
		queue<int>q;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u],v;~i;i=e[i].nxt)
				if(!(~dis[v=e[i].to])&&e[i].dis)dis[v]=dis[u]+1,q.push(v);
		}return dis[t]!=-1;
	}
	int dfs(int u,int flow){
		if(u==t)return flow;
		int delta=flow;
		for(int i=cur[u],v;~i;i=e[i].nxt){
			cur[u]=e[i].nxt;v=e[i].to;
			if(dis[v]==dis[u]+1&&e[i].dis>0){
				int f=dfs(v,min(e[i].dis,delta));
				if(!f){dis[v]=-1;continue;}
				e[i].dis-=f,e[i^1].dis+=f,delta-=f;
				if(!delta)break;
			}
		}return flow-delta;
	}
	int dinic(){
		int ans=0;
		while(bfs()){
			memcpy(cur,head,sizeof(head));
			ans+=dfs(s,1e9);
		}return ans;
	}
}G;

int n,m,Q;
vector<tuple<int,int,int>>edge;
vector<pair<int,int>>g[N];
vector<int>S;
int ans[N];
set<int>res;

void solve(vector<int>&pnt){
	// for(auto u:pnt)Debug("%d ",u);Debug("\n");
	if((int)pnt.size()==1)return;
	G.s=pnt.back(),G.t=pnt.front();
	G.cnt=0;
	memset(G.head,-1,sizeof(G.head));
	for(auto [u,v,w]:edge)G.add(u,v,w),G.add(v,u,w);
	auto w=G.dinic();
	g[G.s].eb(G.t,w),g[G.t].eb(G.s,w);
	vector<int>l,r;
	for(auto x:pnt)
		if(G.dis[x]!=-1)l.eb(x);
		else r.eb(x);
	solve(l),solve(r);
}

void bfs(int s){
	memset(ans,0x3f,sizeof(ans));
	queue<int>q;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto [v,w]:g[u])if(ans[v]==ans[N-1])ans[v]=min(ans[u],w),q.push(v);
	}
}


int main(){
	read(n,m);
	for(int i=1,u,v;i<=m;i++)read(u,v),edge.eb(make_tuple(u,v,1));
	for(int i=0;i<=n;i++)S.emplace_back(i);
	solve(S);
	int all=0;
	for(int u=1;u<=n;u++){bfs(u);for(int i=u+1;i<=n;i++)if(u!=i)all+=ans[i];}
	printf("%d\n",all);
	return 0;
}
```

---

## 作者：Exber (赞：1)

## 做法

最小割树。

不知道为什么大家都说最小割树不能过……反正我用 `dinic` 构造的最小割树过了。~~虽然是最劣解 /kk~~

不知道最小割树的可以去看这篇[学习笔记](https://www.luogu.com.cn/blog/251130/zui-xiao-ge-shu-ght-xue-xi-bi-ji) awa。

首先这道题要求多次最大流，因为最大流 $=$ 最小割，所以我们可以用最小割树来处理。不过注意由于边是双向的，求最小割时会割掉正反两条边，所以答案要除以 `2`。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define S 100005
#define MS 10005

int n,m,q,s,t;
int ineu[S],inev[S],inew[S];
int esum,to[S],c[S],nxt[S],h[MS];
int dep[MS],cur[MS];
int esum2,to2[S],c2[S],nxt2[S],h2[MS];
int nd[MS],tot1,tmp1[MS],tot2,tmp2[MS];
int depp[MS],up[MS][30],minn[MS][30];

inline void init()
{
    esum=1;
    memset(h,0,sizeof(h));
}

inline void add(int x,int y,int w)
{
    to[++esum]=y;
    c[esum]=w;
    nxt[esum]=h[x];
    h[x]=esum;
}

inline void add2(int x,int y,int w)
{
    to2[++esum2]=y;
    c2[esum2]=w;
    nxt2[esum2]=h2[x];
    h2[x]=esum2;
}

inline bool bfs()
{
    memset(dep,0,sizeof(dep));
    queue<int> q;
    q.push(s);
    dep[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=h[u];i;i=nxt[i])
        {
            int v=to[i];
            if(c[i]>0&&dep[v]==0)
            {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>0;
}

int dfs(int u,int w)
{
    if(u==t)
    {
        return w;
    }
    int sum=0;
    for(int &i=cur[u];i;i=nxt[i])
    {
        int v=to[i];
        if(c[i]>0&&dep[v]==dep[u]+1)
        {
            int re=dfs(v,min(w,c[i]));
            c[i]-=re;
            c[i^1]+=re;
            w-=re;
            sum+=re;
            if(w==0)
            {
                break;
            }
        }
    }
    return sum;
}

inline int dinic()
{
    int ans=0;
    while(bfs())
    {
        for(int i=1;i<=n;i++)
        {
            cur[i]=h[i];
        }
        ans+=dfs(s,1e8);
    }
    return ans;
}

inline int slove(int x,int y)
{
    init();
    s=x;
    t=y;
    for(int i=1;i<=m;i++)
    {
        add(ineu[i],inev[i],inew[i]);
        add(inev[i],ineu[i],0);
        add(inev[i],ineu[i],inew[i]);
        add(ineu[i],inev[i],0);
    }
    return dinic();
}

void built(int l,int r)
{
    if(l==r)
    {
        return; 
    }
    int nans=slove(nd[l],nd[r]);
    add2(nd[l],nd[r],nans);
    add2(nd[r],nd[l],nans);
    tot1=0;
    tot2=0;
    for(int i=l;i<=r;i++)
    {
        if(dep[nd[i]]>0)
        {
            tmp1[++tot1]=nd[i];
        }
        else
        {
            tmp2[++tot2]=nd[i];
        }
    }
    for(int i=1;i<=tot1;i++)
    {
        nd[l+i-1]=tmp1[i];
    }
    for(int i=1;i<=tot2;i++)
    {
        nd[l+tot1-1+i]=tmp2[i];
    }
    int l1=l,r1=l+tot1-1;
    int l2=l+tot1,r2=r;
    built(l1,r1);
    built(l2,r2);
}

void initque(int u,int fa,int val)
{
    depp[u]=depp[fa]+1;
    up[u][0]=fa;
    minn[u][0]=val;
    for(int i=1;i<=25;i++)
    {
        up[u][i]=up[up[u][i-1]][i-1];
        if(up[u][i]!=0)
        {
            minn[u][i]=min(minn[u][i-1],minn[up[u][i-1]][i-1]);
        }
    }
    for(int i=h2[u];i;i=nxt2[i])
    {
        int v=to2[i];
        if(v==fa)
        {
            continue;
        }
        initque(v,u,c2[i]);
    }
}

inline int quemin(int x,int y)
{
    if(depp[x]<depp[y])
    {
        int t=x;
        x=y;
        y=t;
    }
    int res=1e8;
    for(int i=25;i>=0;i--)
    {
        if(depp[up[x][i]]>=depp[y])
        {
            res=min(res,minn[x][i]);
            x=up[x][i]; 
        }
    }
    if(x==y)
    {
        return res;
    }
    for(int i=25;i>=0;i--)
    {
        if(up[x][i]!=up[y][i])
        {
            res=min(res,min(minn[x][i],minn[y][i]));
            x=up[x][i];
            y=up[y][i];
        }
    }
    res=min(res,min(minn[x][0],minn[y][0]));
    return res;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&ineu[i],&inev[i]);
		inew[i]=1;
		ineu[m+i]=ineu[i];
		inev[m+i]=inev[i];
		inew[m+i]=inew[i];
    }
    m*=2;
    for(int i=1;i<=n;i++)
    {
        nd[i]=i;
    }
    built(1,n);
    initque(1,0,0);
    long long res=0;
    for(int i=2;i<=n;i++)
    {
    	for(int j=1;j<i;j++)
    	{
    		res+=quemin(i,j);
		}
	}
	printf("%lld\n",res/2);
    return 0;
}
```

---

## 作者：junee (赞：0)

# P4214 题解

## 前置知识

边双，哈希。

## 题目分析

非常好的神仙题，使我的脑子旋转。

首先注意到题目条件，**每个节点最多可以连接 3 条管道**，这个条件非常突兀，实际上仔细想一想会发现，这个条件告诉我们最大流 $\le 3$！

考虑把最大流转化为最小割。

思考最小割四种取值什么时候会取到？

1.当两个点不连通时，可知最小割为 0。

2.当最小割为 1 时，即割掉一个边就会断，很容易让我们想到边双里的桥，求一次边双即可。

这里给出一个 dfs 序求边双的代码。

```
void dfs(int u,int from){
	stk[++tt]=u;
	instk[u]=1;
	st[u]=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(i==(from^1)||bre[i])continue;
		if(!st[j]){
			dfs(j,i);
			s[u]+=s[j];
		}
		else if(instk[j])s[u]++,s[j]--;
	}
	instk[u]=0;
	if(!s[u]){
		cnt++;
		int y;
		do{
			y=stk[tt--];
			id[y]=cnt;
		}while(y!=u);
	}
}
```

3.当最小割为 2 时，其实就是多割掉一条边。

发现 $m$ 比较小，考虑暴力割边再求边双，如果割成两个边双则最小割为 2，考虑用哈希 $O(1)$ 判断即可。

4.当最小割为 3 怎么判断？非前面三种不就是这种情况。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
typedef unsigned long long ULL;
const int N=1e4+10,base=13331;
int h[N],e[N*2],ne[N*2],idx;
int n,m; 
int fa[N];
ULL hsh[N];
int st[N],bre[N],s[N],instk[N],stk[N],id[N],tt,cnt;
int ans=0;
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)fa[x]=y;
}
void dfs(int u,int from){
	stk[++tt]=u;
	instk[u]=1;
	st[u]=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(i==(from^1)||bre[i])continue;
		if(!st[j]){
			dfs(j,i);
			s[u]+=s[j];
		}
		else if(instk[j])s[u]++,s[j]--;
	}
	instk[u]=0;
	if(!s[u]){
		cnt++;
		int y;
		do{
			y=stk[tt--];
			id[y]=cnt;
		}while(y!=u);
	}
}
void clear(){
	cnt=tt=0;
	for(int i=1;i<=n;i++)st[i]=s[i]=instk[i]=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i,h[i]=-1;
	while(m--){
		int a,b;
		cin>>a>>b;
		add(a,b),add(b,a);
		merge(a,b);
	}
	for(int i=0;i<idx;i+=2){
		bre[i]=bre[i^1]=1;
		clear();
		for(int j=1;j<=n;j++)
			if(!st[j])dfs(j,-1);
		for(int j=1;j<=n;j++)hsh[j]=hsh[j]*base+id[j];
		bre[i]=bre[i^1]=0;
	}
	clear();
	for(int i=1;i<=n;i++){
		if(!st[i])dfs(i,-1);
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(find(i)!=find(j))continue;
			if(id[i]!=id[j])ans++;
			else if(hsh[i]!=hsh[j])ans+=2;
			else ans+=3;
		}
	}
	cout<<ans;
	return 0;
}
```

---

