# [PA 2010] Riddle

## 题目描述

$n$ 个点 $m$ 条边的无向图被分成 $k$ 个部分。每个部分包含一些点。

请选择一些关键点，使得每个部分**恰**有一个关键点，且每条边**至少**有一个端点是关键点。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1\le k,w\le n\le 10^6$，$\sum w=n$，$1\le a,b\le n$，$0\le m\le 10^6$。

## 样例 #1

### 输入

```
6 5 2
1 2
3 1
1 4
5 2
6 2
3 3 4 2
3 1 6 5```

### 输出

```
TAK```

# 题解

## 作者：阴阳八卦 (赞：74)

蒟蒻第一次写题解，多多包涵。感觉前面的大佬写得有点迷糊，~~对，就是我太菜了~~，蒟蒻来表达下自己的想法

对于本题而言，每个点有两种状态：选或不选。

同时题目又给出限制条件：点集内**只能**选一个点，一条边上**至少**选一个点

~~这也太明显了吧~~

所以就是在点集内，若选择某个点则另外的点不能选；一条边上，若不选某个点，则另一个点必选。此时已经很显然了，2-SAT建边跑强连通分量判断是否矛盾，完事

~~2-SAT板子过了才做这题的吧~~[板子](https://www.luogu.com.cn/problem/P4782)

但是如果直接暴力建边就会有这样的问题：[记录](www.luogu.com.cn/record/36357719)

**总有大数据会MLE或TLE！**

而其根本原因就在与点集内的建边:
```
for(int i=1;i<=k;i++)
{
	scanf("%d",&t);
	for(int j=1;j<=t;j++)scanf("%d",&a[j]);
	for(int j=1;j<=t;j++)
	{
		for(int l=1;l<=t;l++)
     		if(l==j)continue;
		else add((a[j]-1)*2,(a[l]-1)*2+1);
	}
}
```
~~快乐超限~~

$N^2$的算法让人难以接受，时间空间过大，为解决这个问题必须优化点集内建边算法

![ ](https://cdn.luogu.com.cn/upload/image_hosting/n65rzuip.png)

这是我们原来的建图方式，朴素但是有效~~好歹92分~~

如何优化呢？关键就在于缩小$N^2$的计算量，而要完成这一步，关键是减少建边的数量（或者说优化建边的方式）

2-SAT里变量两种状态的点是关键，不可能直接在这$2N$个点之上优化。自然而然得，我们应当新建若干点作为媒介使新图拥有原来的性质，而这$2N$个点的地位等价（感觉一下？），自然应当新建$2N$个点一一对应（连边）

为保持原来点的性质不变，出点继续出，入点继续入

![ ](https://cdn.luogu.com.cn/upload/image_hosting/p50ab9od.png)

然后自然而然得，我们可以转移边

![ ](https://cdn.luogu.com.cn/upload/image_hosting/fc1gq9sk.png)

对于这幅图，我们容易发现~~没错非常容易~~，9-16，10-16，11-16这三条边可以变成9-10，10-11，11-16这样的三条边，而同时9-10还可以用于9-15，10-15到9-10，10-15的转换。所以经过这样的转化，我们能得到这张图

![](https://cdn.luogu.com.cn/upload/image_hosting/47j9yl2j.png)

但是这张图存在致命的错误：出现了1-9-14-13-2，1-9-10-13-2之类的错误线路，为了调整这种线路，我们将9-14调整为9-4，10-13调整为3-13（保持9-10，14-13之类的由有利边仍然存在），类似操作后，有了这张图

![ ](https://cdn.luogu.com.cn/upload/image_hosting/jr0snomu.png)

此时图形已经符合原图的所有性质，但是为了便于进行循环操作，我们对其微调(也就4条边），得到这张图（也就是程序得到的图）

![](https://cdn.luogu.com.cn/upload/image_hosting/ypkhxjf2.png)

附上点集内代码，可以结合图片食用
```
int cntt=2*n;
for(int j=1;j<=k;j++)
{
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&a[i]);
		pre[a[i]][0]=++cntt;//新建点
		pre[a[i]][1]=++cntt;//新建点
		add((a[i]-1)*2,pre[a[i]][0]);
		add(pre[a[i]][1],(a[i]-1)*2+1);
	}
	for(int i=2;i<=t;i++)
	{
		int d1=a[i-1],d2=a[i];
		add(pre[d1][0],pre[d2][0]);
		add(pre[d2][1],pre[d1][1]);
		add(pre[d1][0],(d2-1)*2+1);
		add((d2-1)*2,pre[d1][1]);
	}
}
```
最后附上AC代码
```
#include<bits/stdc++.h>
//(i-1)*2    (i-1)*2+1   
using namespace std;
const int N=2*1e6+10,M=2*1e7;
int dfn[2*N],low[2*N],fa[2*N],vis[2*N],st[2*N],head[2*N],a[N];
int to[2*M],Next[2*M],pre[N][2];
int cnt,p,cntk;
void add(int x,int y)
{
	to[cnt]=y;
	Next[cnt]=head[x];
	head[x]=cnt++;
}
void tar(int x)
{
	dfn[x]=low[x]=++cntk;
	vis[x]=1;
	st[++p]=x;
	for(int i=head[x];i!=-1;i=Next[i])
	{
		if(!dfn[to[i]])
		{
			tar(to[i]);
			low[x]=min(low[x],low[to[i]]);
		}
		else if(vis[to[i]])low[x]=min(low[x],dfn[to[i]]);
	}
	int cur;
	if(low[x]==dfn[x])
	{
		do{
			cur=st[p];
			p--;
			vis[cur]=0;
			fa[cur]=x;
		}while(cur!=x);
	}
}
void init()
{
	memset(head,-1,sizeof(head));
	cnt=0;
	cntk=0;
	p=0;
}
int main()
{
	init();
	int n,m,k,x,y,t;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add((x-1)*2+1,(y-1)*2);
		add((y-1)*2+1,(x-1)*2);
	}
	int cntt=2*n;
	for(int j=1;j<=k;j++)
	{
		scanf("%d",&t);
		for(int i=1;i<=t;i++)
		{
			scanf("%d",&a[i]);
			pre[a[i]][0]=++cntt;
			pre[a[i]][1]=++cntt;
			add((a[i]-1)*2,pre[a[i]][0]);//xuan ze lianchu
			add(pre[a[i]][1],(a[i]-1)*2+1);//lian dao bu xuan
		}
		for(int i=2;i<=t;i++)
		{
			int d1=a[i-1],d2=a[i];
			add(pre[d1][0],pre[d2][0]);
			add(pre[d2][1],pre[d1][1]);
			add(pre[d1][0],(d2-1)*2+1);
			add((d2-1)*2,pre[d1][1]);
		}
	}
	cntk=0;
	for(int i=0;i<=cntt;i++)
	if(!dfn[i])tar(i);
	bool flag=1;
	for(int i=1;i<=n&&flag;i++)
	if(fa[(i-1)*2]==fa[(i-1)*2+1])flag=0;
	if(flag) printf("TAK");
	else printf("NIE");
	return 0;
}
```

---

## 作者：lhm_ (赞：41)

首先不难看出对于本题的点与点之间的限制关系，我们可以考虑用$2-SAT$来解决，通过从状态$x$向状态$y$连一条有向边表示若状态$x$存在，那么状态$y$必须存在。

接下来的处理中，$x$表示点$x$被选为关键点，$x^\prime$表示点$x$没有选为关键点，$x \longrightarrow y$表示两个状态之间连一条有向边。

对于每条边至少有一个端点是关键点这一限制，若边两端为$x$和$y$，那么直接进行$x^\prime \longrightarrow y\ ,\ y^\prime \longrightarrow x$即可。

处理使得每个部分恰有一个关键点这一限制时，发现要进行像一个点向该部分中除它以外的所有点连边的操作，这样的话，边数会达到$n^2$级别，这是不可以接受的，所以要考虑优化建图。

对于每个点，我们这里在其所在的部分中考虑，每个点用$a_i$来表示，再对其新增一个状态$pre_i$，表示在该部分中前$i$个点是否有点被选为关键点。

连边时我们可以进行以下的操作：

$a_i \longrightarrow pre_{a_i}\ ,\ pre_{a_i}^\prime \longrightarrow a_i^\prime$

$pre_{a_{i-1}} \longrightarrow pre_{a_i}\ ,\ pre_{a_i}^\prime \longrightarrow pre_{a_{i-1}}^\prime\ $

$\ pre_{a_{i-1}} \longrightarrow a_i^\prime\ ,\ a_i \longrightarrow pre_{a_{i-1}}^\prime$

通过这样的前缀优化建图，就不用再连那么多边了，同时题目的限制条件也都可以满足。

具体实现细节看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define p1(x) x
#define p0(x) x+n
#define pre1(x) x+2*n
#define pre0(x) x+3*n
#define maxn 8000010
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,k,dfn_cnt,co_cnt,top;
int dfn[maxn],low[maxn],co[maxn],st[maxn],a[maxn];
bool vis[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++dfn_cnt;
    st[++top]=x,vis[x]=true;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);
        else if(vis[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x])
    {
        co_cnt++;
        int now;
        do
        {
            now=st[top--];
            vis[now]=false;
            co[now]=co_cnt;
        }while(now!=x);
    }
}
bool check()
{
    for(int i=1;i<=4*n;++i)
        if(!dfn[i])
            tarjan(i);
    for(int i=1;i<=n;++i)
        if(co[p1(i)]==co[p0(i)]||co[pre1(i)]==co[pre0(i)])
            return false;
    return true;
}
int main()
{
    read(n),read(m),read(k);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        read(x),read(y);
        add(p0(x),p1(y)),add(p0(y),p1(x));
    }
    for(int i=1;i<=k;++i)
    {
        int w;
        read(w);
        for(int j=1;j<=w;++j)
            read(a[j]),add(p1(a[j]),pre1(a[j])),add(pre0(a[j]),p0(a[j]));
        for(int j=2;j<=w;++j)
        {
            add(pre1(a[j-1]),pre1(a[j])),add(pre0(a[j]),pre0(a[j-1]));
            add(pre1(a[j-1]),p0(a[j])),add(p1(a[j]),pre0(a[j-1]));
        }
    }
    if(check()) puts("TAK");
    else puts("NIE");
    return 0;
}
```

---

## 作者：yaorz (赞：26)

### 暴力思路

首先可以看出，对于每个点，有是关键点与不是关键点两种状态。并且有如下两条相互限制：

- 一个点是关键点，则该点所属部分中其余点都不能是关键点
- 一个点不是关键点，则与其相连的其他点，都必须是关键点

由此，可以看出这可以用 **2-SAT** 来解决

但是如果按照上述思路，直接暴力建边是会挂掉的。对于每一个部分，都需要连 $n^2$ 条边。显然时空复杂度都无法承受。

![暴力](https://cdn.luogu.com.cn/upload/image_hosting/2pmjalzn.png)

### 建边优化

第二条限制和第一条限制相互独立，不需要管，只需要修改第一条限制。我们希望可以只建 $O(n)$ 级别数量的边。

考虑优化思路，第一条限制的本质，是在每一个部分中，把每一个点的 “真状态” 连向其余所有点的 “假状态”。并且只要保证连通即可。而连向其余所有点，可以看做连向这个点之前的前缀 和 这个点之后的后缀。
![缀](https://cdn.luogu.com.cn/upload/image_hosting/d68tnyn4.png)

如上图，点 $3$ 就是连向了其对应点 $7$ ，之前的所有点和之后的所有点。也就是 **前缀** 和 **后缀**。

所以可以用常见的 **前后缀** 建边来优化。

我们先建立若干个辅助点，让每一个辅助点都和最终点相连。然后，按照从前往后的顺序连接辅助点。这样，只需要连一条边，就得到了一个点的 **后缀**。
![后缀](https://cdn.luogu.com.cn/upload/image_hosting/0m1nioxg.png)

（如上图，点 $2$ 一条边就连到了 $2$ 之后的所有对应点）

反之，如果按照从后往前的顺序连接辅助点，就得到了前缀。必须要建两排辅助点。

最终建的图如下：
![hahah](https://cdn.luogu.com.cn/upload/image_hosting/1658qirp.png)

代码中，这几行分别编号为 $1\to n$、$2n+1\to 3n$、$3n+1\to 4n$、$n+1\to 2n$

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
struct Edge{
	int to, last;
}edge[N * 12];
int head[N << 2], tot, low[N << 2], dfn[N << 2];
int vis[N << 2], st[N << 2], top, sze, num;
int p[N];
int belng[N << 2], n, m, k, a, b;
void add(int u, int v) {
	edge[++tot] = (Edge){v, head[u]};
	head[u] = tot;
}
void tarjan(int u) {
	low[u] = dfn[u] = ++num;
	vis[u] = 1;
	st[++top] = u;
	for(int i = head[u]; i; i = edge[i].last) {
		int v = edge[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u]) {
		++sze;
		while(st[top] != u) {
			belng[st[top]] = sze;
			vis[st[top]] = 0;
			top--;
		}
		belng[st[top]] = sze;
		vis[st[top]] = 0;
		top--;
	}
}
int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &a, &b);
		add(a + n, b);
		add(b + n, a);
	}
	for(int i = 1; i <= k; i++) {
		int w;
		scanf("%d", &w);
		for(int j = 1; j <= w; j++) {
			scanf("%d", &p[j]);
			add(p[j] + 2 * n, p[j] + n);
			add(p[j] + 3 * n, p[j] + n);
		}
		for(int j = 1; j < w; j++) {
			add(p[j + 1] + 2 * n, p[j] + 2 * n);
			add(p[j] + 3 * n, p[j + 1] + 3 * n);
			add(p[j], p[j + 1] + 3 * n);
			add(p[j + 1], p[j] + 2 * n);
		}
	}
	for(int i = 1; i <= 2 * n; i++) {
		if(!dfn[i]) {
			tarjan(i);
		}
	}
	for(int i = 1; i <= n; i++) {
		if(belng[i] == belng[i + n]) {
			printf("NIE\n");
			return 0;
		}
	}
	printf("TAK\n");
	return 0;
}
```


---

## 作者：Brilliance_Z (赞：17)

[本题 P6378](https://www.luogu.com.cn/problem/P6378) 思路极其巧妙：2-SAT + 前缀优化建图。

### 2-SAT

不会2-SAT出门左传 [洛谷日报](https://www.luogu.com.cn/blog/85514/post-2-sat-xue-xi-bi-ji)。

每个节点只有 $2$ 种可能的取值 + 存在性问题 $\rightarrow$ 2-SAT。

每条边至少有一个端点是关键点：$\neg u\rightarrow v,\neg v\rightarrow u$。

每个点集恰有一个关键点：

这一部分比较难处理。因为看上去好像是多 SAT 问题。

但是我们可以把它转化为 2-SAT 问题 ~~（因为 $O(N)$ 的时间复杂度只能用 2-SAT 解决了……）~~ 。最直接的想法就是：对于点集 $(a,b,c)$，$a\rightarrow \neg b,a\rightarrow \neg c,b\rightarrow \neg a,b\rightarrow \neg c,c\rightarrow \neg a,c\rightarrow \neg b$。

这样做好像有一个问题：可能这个点集 2-SAT 会求出一个点都不选的方案。但是题目要求每个点集恰有一个关键点。

但是仔细想想会发现：在本题中恰有一个关键点的方案包含一个点都不选的方案，因为如果 2-SAT 求出该点集一个点都不选的方案，我不妨在该点集中任意选出 $1$ 个点，因为每条边是至少选出一个点而不是恰好，所以最终结果仍然是满足 2-SAT 关系的。

然后就 MLE 了……

瓶颈在于点集的 2-SAT 建边是 $O(N^2)$ 的。

~~本题数据范围显示要求 $O(N)$，所以我们往前缀优化建图方向想。~~ 把点集中的每个点拿出来排成 $1$ 个序列 $s$，设 $\neg s$ 表示点集 $\{\neg a\}$ 的序列。

```plain
a b c ¬a ¬b ¬c
```

发现排成上面这样还是不易看出如何用前缀优化建图。把 $\neg s$ 放在 $s$ 一前一后：

```plain
¬a ¬b ¬c a b c ¬a ¬b ¬c
```

看出来了！对于一个点 $a$，从 $a$ 向 $\neg s$ 中 $a$ 的前缀（不含 $a$）连边，从 $a$ 向 $\neg s$ 中 $a$ 的后缀（不含 $a$）连边。

### 前缀优化建图

事实上，前缀优化建图适用于从序列上区间 $[l_1,r_1]$（可能是 $1$ 个点）的补集上的所有节点向区间 $[l_2,r_2]$（可能是 $1$ 个点）的补集上的所有节点连长度为 $w$ 的边。前面我们谈到的点集的 2-SAT 建边，恰好符合上面的适用条件。

$opre/ipre/osuf/isuf[u]$ 代表点 $u$ 的前缀/后缀所有点的出点/入点。

1. 预处理：从 $opre[i-1]$ 和 $i$ 向 $opre[i]$ 连一条权值为 $0$ 的边；从 $ipre[i]$ 向 $ipre[i-1]$ 和 $i$ 连一条权值为 $0$ 的边；从 $i$ 和 $osuf[i+1]$ 向 $osuf[i]$ 连一条权值为 $0$ 的边；从 $isuf[i]$ 向 $i$ 和 $isuf[i+1]$ 连一条权值为 $0$ 的边。**注意 $i=1$ 或 $i=n$ 时的边界问题。**
2. 对于序列上区间 $[l_1,r_1]$ 的补集上的所有节点向区间 $[l_2,r_2]$ 的补集上的所有节点连长度为 $w$ 的边，建立 $1$ 个虚点，从 $opre[l_1-1]$ 和 $osuf[r_1+1]$ 向虚点连边，从虚点向 $ipre[l_2-1]$ 和 $isuf[r_2+1]$ 连边，在出点和入点中选一个建边为权值 $wor$，另一个建边为权值 $0$。**注意 $i=1$ 或 $i=n$ 时的边界问题。**
3. 对于点向点连边、点和补集之间的建边的情况就不要糊涂了。

预处理时间复杂度：$O(N)$。空间复杂度：$O(N)$。

建 $1$ 条边的时间复杂度：$O(1)$。空间复杂度：$O(1)$。

对于本题而言，配合 2-SAT 时建边不需要权值；点集的 2-SAT 建边只需要用到前缀/后缀的入点，而不需要出点。

最终我们得到了极其优秀的 $O(N)$ 算法！

```cpp
//i：不选点i；i+n：选点i
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10,EN=N*2+N*2,EM=N*2+N*(2*2+2);
int n,m,k;
int h[EN],e[EM],ne[EM],idx;
int part[N];
int vidx;
int pre[N],suf[N];
int dfn[EN],low[EN],num;
int belong[EN],scc;
int st[EN],top;
bool in_st[EN];

void add(int u,int v)
{
    e[++idx]=v,ne[idx]=h[u],h[u]=idx;
    return ;
}

void tarjan(int u)
{
    dfn[u]=low[u]=++num;
    st[++top]=u,in_st[u]=true;
    for(int i=h[u];i!=0;i=ne[i])
    {
        int v=e[i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in_st[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        scc++;
        int z;
        do
        {
            z=st[top--];
            belong[z]=scc;
            in_st[z]=false;
        }while(z!=u);
    }
    return ;
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v+n),add(v,u+n);
    }
    vidx=2*n;
    for(int i=1;i<=k;i++)
    {
        int w;
        scanf("%d",&w);
        for(int i=1;i<=w;i++) scanf("%d",&part[i]);
        pre[part[1]]=part[1];
        for(int i=2;i<=w;i++)
        {
            pre[part[i]]=++vidx;
            add(pre[part[i]],pre[part[i-1]]),add(pre[part[i]],part[i]);
        }
        suf[part[w]]=part[w];
        for(int i=w-1;i>=2;i--)
        {
            suf[part[i]]=++vidx;
            add(suf[part[i]],suf[part[i+1]]),add(suf[part[i]],part[i]);
        }
        for(int i=1;i<=w;i++)
        {
            if(i!=1) add(part[i]+n,pre[part[i-1]]);
            if(i!=w) add(part[i]+n,suf[part[i+1]]);
        }
    }
    for(int i=1;i<=vidx;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
        if(belong[i]==belong[i+n])
        {
            puts("NIE");
            return 0;
        }
    puts("TAK");
    return 0;
}
```

---

## 作者：wwlw (赞：7)

[Link](https://www.luogu.com.cn/problem/P6378)

-----------------

### 题目描述

$n$ 个点 $m$ 条边的无向图被分成 $k$ 个部分。每个部分包含一些点。

请选择一些关键点，使得每个部分**恰**有一个关键点，且每条边**至少**有一个端点是关键点。

### 解法

有一些限制条件，问你是否有合法方案，容易想到 2-SAT 。

思考如何建立新图，一共有两种限制：对于原图的每条边来说，它连接的两个点至少有一个点被选；对于一组相关联的点来说，他们之中只有一个被选择。可以看到对于每个点，它的状态只有选与不选这两种。

那么容易想到把每个点都拆成两个点，一个表示选（记为 $u_1$），另一个表示不选（记为 $u_2$）。对于第一种限制，若原图中一条边连接了 $u$ 和 $v$ 两个点，那么连接 $u_2\to v_1$ 和 $v_2\to u_1$，因为若 $u$ 不选必选 $v$ ，后者同理。对于第二种限制，连接所有 $u_1\to v_2$，其中 $v$ 为除 $u$ 外同一个部分的其它所有点，表示选了 $u$ ，那么这个部分的其它点都不能选。

最后按套路跑一遍 $tarjan$ 。

### 优化

可以看出，如果所有点都被划分在一个部分，即一个部分有 $n$ 个点，那么总边数一定是 $O(n^2)$ 的。

如果按最后分组时读入节点的顺序来看的话，那么我们其实是把一个点向一段连续的区间连边，容易想到线段树优化建边。然而非常毒瘤的是数据为 $1e6$ ，那么线段树常数稍一大就会挂掉。

还可以怎么优化？

再次回到题目，我们漏掉了一个重要的条件：在一组之内，每次区间的左端点或者右端点都是固定的！

也就是说每次我们连接的其实是一个前缀和后缀，于是想到了前缀后缀优化。

![](https://cdn.luogu.com.cn/upload/image_hosting/jfjemo4a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，节点 $u$ 只需要连接一个节点实际上就连接了整个前缀，后缀同理。而对于每个节点都只需要连接前缀后缀两个节点，故空间复杂度为 $O(n)$。至此可以很好地通过此题。

```cpp
#include<stdio.h>
#define lid id<<1
#define rid id<<1|1
using namespace std;
#define N 5000007

template<class T>
inline void read(T &x){
    T flag=1;x=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    x*=flag;
}

struct E{
	int next,to;
}e[N<<1];
int n,m,K,cnt,len[N],a[N],dfn[N],c[N],low[N],tim=0,sta[N],top=0,scc_num=0,head[N];
bool vis[N];

inline void add(int id,int to){
	e[++cnt]=(E){head[id],to};
	head[id]=cnt;
}

inline int min(int x,int y){return x<y? x:y;}
inline void tarjan(int u){
	dfn[u]=low[u]=++tim;
	sta[top++]=u;vis[u]=true;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		int y;
		scc_num++;
		do{
			y=sta[--top];
			vis[y]=false;
			c[y]=scc_num;
		}while(u!=y);
	}
}

inline bool check(){
	for(int i=1;i<=(n<<2);++i)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;++i)
		if(c[a[i]]==c[a[i]+n]) return false;
	return true;
}

int main(){
//	freopen("sample2.in","r",stdin);
	read(n),read(m),read(K);
	for(int i=1;i<=m;i++){
		int u,v;
		read(u),read(v);
		add(u+n,v),add(v+n,u);
	}
	int ret=0;
	for(int i=1;i<=K;i++){
		read(len[i]);
		for(int j=1;j<=len[i];j++){
			int pos=ret+j;
			read(a[pos]);
			if(j!=1){
				add(a[pos]+2*n,a[pos-1]+2*n);
				add(a[pos],a[pos-1]+2*n);
			}
			add(a[pos]+2*n,a[pos]+n);
		}
		ret+=len[i];
	}
	ret=0;
	for(int i=1;i<=K;i++){
		for(int j=1;j<=len[i];j++){
			int pos=ret+j;
			if(j!=len[i]){
				add(a[pos]+3*n,a[pos+1]+3*n);
				add(a[pos],a[pos+1]+3*n);
			}
			add(a[pos]+3*n,a[pos]+n);
		}
		ret+=len[i];
	}
	printf("%s",check()? "TAK":"NIE");
}

/*
5 4 1
1 2
1 3
3 4
4 5
5 2 3 1 5 4
*/
```


---

## 作者：huangzirui (赞：6)

本题的关键之处在于解决 2-SAT 中 "若干个点只能选择一个" 的问题。

考虑某个点向除它之外的点连边，那么需要连 $n^2$ 条边，不够优秀。

考虑一个点 $x$ 向点 $[1,x-1] \bigcup [x+1,n]$ 连边，显然可以前缀和优化。

设点 $f_i$ 是点 $[1,i]$ 是否被选择的状态，点 $g_i$ 是点 $[i,n]$ 是否被选择的状态，直接连就行，需要连 $O(n)$ 条边。

当然，使用线段树/倍增优化也行，需要连 $O(n\log n)$ 条边。

---

## 作者：UperFicial (赞：5)

~~补了一个巨坑，2021 夏令营的历史遗留产物~~。

考虑转化成 $\text{2-sat}$ 模型，每个点有两种情况，关键点或不是关键点。我们令 $x$ 表示 $x$ 是关键点，$x'$ 则不是关键点。

对于原图的一条边 $(u,v)$，则可以抽象成【两个条件至少满足一个】这一条件限制，连边 $u'\to v,v'\to u$。

那么，【每一个部分都有一个关键点】这一条件限制应该怎样满足呢？

最暴力的想法是，枚举每一个点，然后暴力向它所在的部分的除自己以外所有的点连边，复杂度 $\Theta(n^2)$。考虑优化。

考虑新建虚拟节点加快建边速度，$i$ 要连向 $[1,i-1]$ 和 $[i+1,n]$ 这两个区间，可以分开考虑。

对于区间 $[i+1,n]$，假设说 $i+1$ 号节点已经连上了 $[i+2,n]$，那么我们只需连一条 $i\to i+1$ 的有向边即可，边的关系是传递的。

但 $i+1$ 管辖的范围只是 $[i+2,n]$，所以特别的，我们再连一条 $i\to i'+1$ 的边即可。反过来也是一样，这便是【前后缀和优化建图】的经典 $\texttt{trick}$。

很可惜，这是个假做法。我们连了 $i\to i+1$，但是又连了 $i+1\to i'$，可以得到 $i\to i'$，这不就相当于连了所有的点吗（害怕）。

那么怎么办呢？

我们可以对于每一个 $i$ 新建一个克隆节点 $pre_i$，每一个 $i'$ 新建一个克隆 $suf_{i'}$ 即可，我们连 $i\to pre_i$，$suf_{i'}\to i'$，直接把 $pre$ 和 $suf$ 当成节点来连边，这就是对的了！

代码就不放了，写的都一样/qd

AC 记录：[$\textbf{QwQ}$](https://www.luogu.com.cn/record/69906382)

---

## 作者：最後 (赞：4)

有一说一这题确实难
## 普通边
用常规的2-SAT问题角度即可
```
add(point1+n,point2);
add(point2+n,point1);
```
## 子图
难点所在
对n方级别的建图,时间无法接受

有神奇的建图方法来减少边的数量

**本文中所有的point指选择该点为关键点,point+n为不选该点为关键点,point+2*n表示由point点衍生而来的同样表示选择point点为关键点的点,point+3*n表示由point+n衍生而来的同样表示不选point点为关键点的点**

图是找[阴阳八卦](https://www.luogu.com.cn/user/198835)借的
![](https://cdn.luogu.com.cn/upload/image_hosting/fl06983i.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
1. 显然的,两个衍生而来的点需具备衍生前的同等性质,因此有
```
add(point,point+2*n);
add(point+3*n,point+n);
```
![](https://cdn.luogu.com.cn/upload/image_hosting/pp8cb8mq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

**接下来就是最重要的构图**

因为由n-1个点向第n点连边,同时由n-2个点向第n-1点连边,n-3个点向第n-2点连边
这部分的边数有没有想办法减少呢?

联想到在跑强连通分量的时候我们只需要一条路径就能让两个点身处同一强连通分量中,而不一定需要其直连.

所以对上面那些冗杂的边,我们可以

**想象一条主道路分出子道路**

![](https://cdn.luogu.com.cn/upload/image_hosting/a5fv3q3g.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这就是裂点的目的,保证了存在一条主道路.

这样的构造同时保证了一定的对称性,即构图时只跟前一个点与当前点有关

接下来的连边结合上述论述就显得自然了


2. 将point1+2n点与point2+2n点连边
3. 将point2+3n点与point1+3n点连边
4. 将point1+2n点与point2+n点连边
5. 将point2点与point1+3n点连边

 _合理性?_
 
 当点数较多时,原本向其他所有点直连的边转变为通过一定路径到达且由于是有向图,错位的连边(表现在point1+2n点与point2+n点连边,point2点与point1+3n点连边)保证了不会多出原本不存在的路径.
 
 与普通边的互斥也不存在矛盾

附上AC

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e6+10;
const int N=1e7+10;
int n,m,k,len,p,last,now;
int head1[N],next1[N],to1[N];
int head2[N],next2[N],to2[N];
int visit[maxn],q[maxn],f[maxn];
void add(int a,int b)
{
	len++;
	next1[len]=head1[a];
	head1[a]=len;
	to1[len]=b;
	next2[len]=head2[b];
	head2[b]=len;
	to2[len]=a;
}
void dfs1(int num)
{
	visit[num]=1;
	for(int i=head2[num];i;i=next2[i])
	if(!visit[to2[i]])dfs1(to2[i]);
	q[++len]=num;
}
void dfs2(int num)
{
	visit[num]=0;
	f[num]=len;
	for(int i=head1[num];i;i=next1[i])
	if(visit[to1[i]])dfs2(to1[i]);
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a+n,b);
		add(b+n,a);
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&p,&last);
		add(last,last+2*n);
		add(last+3*n,last+n);
		for(int j=2;j<=p;j++)
		{
			scanf("%d",&now);
			add(now,now+2*n);
			add(now+3*n,now+n);
			add(last+2*n,now+2*n);
			add(last+2*n,now+n);
			add(now,last+3*n);
			add(now+3*n,last+3*n);
        	last=now;
		}
	}
	len=0;
	for(int i=1;i<=4*n;i++)
	if(!visit[i])dfs1(i);
	len=0;
	for(int i=4*n;i>=1;i--)
	if(visit[q[i]])len++,dfs2(q[i]);
	bool flag=false;
	for(int i=1;i<=n;i++)
	if(f[i]==f[n+i])
	{
		flag=true;
		break;
	}
	if(flag)cout<<"NIE"<<endl;
	else cout<<"TAK"<<endl;
	return 0;
}
```


---

## 作者：Hadtsti (赞：3)

### 题意简述
给出一张 $n(1\le n\le 10^6)$ 个点 $m(1\le m\le 10^6)$ 条边的无向图。现在对 $n$ 个点黑白染色，满足每条边连接的两点至少有一个是黑点；同时题目将这 $n$ 个点恰好分为 $k(1\le k\le n)$ 部分，要求每部分有且只有一个黑点。求是否有满足条件的染色方案。
### 题目分析

很明显是 2-SAT 问题。如一般 2-SAT 题相同，我们设 $x_0$ 为 $x$ 点是白色的状态，$x_1$ 为 $x$ 点是黑色的状态。

那么我们对每条边 $(x,y)$，如果 $x$ 是白点，那么 $y$ 一定是黑点。所以我们从 $x_0$ 向 $y_1$ 连边；同理从 $y_0$ 向 $x_1$ 连边。

对于每“部分”点内的条件转化，首先可以发现每个“部分”至少一个黑点这一条件是无用的。因为若该部分内有至少两个点之间有连边，那么就至少有一个黑点；否则任意两个点之间都没有连边，随便找一个点定为黑点就行。而每个“部分”内只有至多一个黑点一条件，直接处理是将“部分”中每个点 $x$ 对“部分”中其他所有点 $y$，从 $x_1$ 向 $y_0$ 连边。这样做边数是 $O(n^2)$ 级别的，空间、时间都会炸。

事实上，对于这种类似于对一个图中某点集内的点互相之间连边的操作，可以考虑前缀优化建图的方式解决。例如本题，以 $\{1,2,3,5,9\}$ 这一“部分”点中 $3_1$ 点向其他点连边为例，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p6vho5be.png)

这样对一个点暴力建边的复杂度为 $O(n)$。注意到这些边的终点实际上是这一“部分”中首尾两段点，又考虑到 tarjan 算法本质上只需要维护两点之间的可达性。那么对“部分”中的开头一段，我们就可以采用“前缀”的方式维护可达性。具体来说，对每个 $x$ 点多建立一个 $x_2$ 点，然后从 $x_2$ 向 $x_0$ 连边，接着对每“部分”中的所有点，将 $x_2$ 连成一条链。如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8mmqexrs.png)

然后我们发现只需要从 $3_1$ 向 $2_2$ 连一条边就可以实现从 $3_1$ 到 $1_0$ 与 $2_0$ 连边的效果：

![](https://cdn.luogu.com.cn/upload/image_hosting/yoif03yv.png)

对“部分”中结尾一段，也可以类似地采用后缀方式优化。

这样，我们就可以在 $4\times n$ 个点和至多 $8\times n$ 条边的图上跑 tarjan 解决问题即可。时间复杂度仍是 $O(n+m)$。

### 代码实现

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,k,w,x,y; 
int tot,hd[4000010],v[8000010],nt[8000010];
int cnt,dfn[4000010],low[4000010],stk[4000010]/*栈*/,top,num,c[4000010]/*点所在 SCC 编号*/;
bool ins[4000010];//是否入栈 
//用下标为 x 的点代表 x_0，x+n 代表 x_1，x+2*n 代表 x_2，x+3*n 代表 x_3 
void rd(int &x)
{
	x=0;
	char c=getchar();
	for(;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())
		x=(x<<3)+(x<<1)+c-'0';
}//10^6 的数据，用个快读 
void add(int x,int y)
{
	v[++tot]=y;
	nt[tot]=hd[x];
	hd[x]=tot;
}//建边 
void tarjan(int x)//tarjan 求 SCC 
{
	dfn[x]=low[x]=++cnt;
	stk[++top]=x;
	ins[x]=1;
	for(int i=hd[x];i;i=nt[i])
	{
		int y=v[i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x])
	{
		int y;
		num++;
		do
		{
			y=stk[top--];
			ins[y]=0;
			c[y]=num;
		}while(y!=x);
	}
}
int main()
{
	rd(n),rd(m),rd(k);
	for(int i=1;i<=m;i++)
	{
		rd(x),rd(y);
		add(x,y+n); 
		add(y,x+n);
	}
	for(int i=1;i<=k;i++)
	{
		rd(w);
		y=0;//上一个点 
		for(int j=1;j<=w;j++)
		{
			rd(x);
			add(x+2*n,x);
			add(x+3*n,x);
			if(y)
			{
				add(x+n,y+2*n);
				add(y+n,x+3*n);
				add(x+2*n,y+2*n);
				add(y+3*n,x+3*n);
			}
			y=x;
		}
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
		if(c[i]==c[i+n])//如果 i_0 和 i_1 在同一个 SCC 里面，推出矛盾！ 
		{
			printf("NIE");
			return 0;
		}
	printf("TAK");
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：2)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16311181.html)

# 题目大意

$n$ 个点 $m$ 条边的无向图被分成 $k$ 个部分。每个部分包含一些点。

请选择一些关键点，使得每个部分**恰**有一个关键点，且每条边**至少**有一个端点是关键点。

# 题目分析

明显是 $\verb!2-SAT!$ 题。基础的 $\verb!2-SAT!$ 只是可以去模板题学一下，只要会 $\verb!tarjan!$ 应该就没问题。

首先会给定 $m$ 条边，对于一条边 $(u,v)$，因为每一条边至少一个端点是关键点，将每个点拆分成两个表示状态的点 $u,u'$，我们就可以连边 $u'\to v$ 和 $v'\to u$。$u'$ 表示不选点 $u$，$u$ 表示选点 $u$。

（建图算法一）

对于另一个条件：一个部分只能选一个点。我们这样想：既然只能选一个点，那么就不能选其它点，所以 $x$ 连向其它点 $v'$ 就好了，因为 $v'$ 就代表不选其他点 $v$ 的状态。

这样子单次复杂度是 $\mathcal{O(n)}$ 的，所以我们需要优化建图。

-----

引入正题——前后缀和优化建图。

按照算法一连出的图是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/n65rzuip.png)

我们发现连的边太多了，每新加一个点就会再连 $3$ 条边，我们要找到一种连边总数更少的建图方式。

引入“前后缀和优化建图”——

我们连边可以优化一下，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fc1gq9sk.png)

显然 $9\to 15$ 等价于 $9\to 10\to 15$，而类似的，我们会发现只要将第二层和第三层每一层的每个节点之间都互相连边就可以了，然后再稍稍优化下得到：

![](https://cdn.luogu.com.cn/upload/image_hosting/ascjjxrm.png)

这样，如果我们要新加一个点，那么直接连这个点在“前缀层”中的前一个点，以及这个点在“后缀层”中的后一个点，然后惊喜的发现满足条件了。

然后代码就简单了，连边部分代码：

```cpp
for (register int i = 1;i <= m; ++ i) {
	int u = read(),v = read();
	//u,v 至少有一个关键点 
	add(u + n,v),add(v + n,u);
}
//2 * n + 1 ~ 3 * n 存前缀
//3 * n + 1 ~ 4 * n 存后缀
while (k --) {
	int t = read();
	for (register int i = 1;i <= t; ++ i) {
		a[i] = read();
		add(a[i],a[i] + 2 * n),add(a[i] + 3 * n,a[i] + n);
	}
	for (register int i = 2;i <= t; ++ i) {
		add(a[i - 1] + 2 * n,a[i] + 2 * n),add(a[i - 1] + 2 * n,a[i] + n);
		add(a[i] + 3 * n,a[i - 1] + 3 * n),add(a[i],a[i - 1] + 3 * n);
	}
}
``` 

# 代码

主要代码已经给出，其它都是板子。

完整代码见博客。

---

## 作者：Zimse (赞：2)

如果没有 $k$ 个部分这个限制的话,就是一个 2-SAT 的板子题。

但是如果有 $k$ 个部分的限制呢?

一种建边思路是每一组的所有点两两之间建边，但是这样最多有 $n^2$ 条边 , 无法通过本题。

这种情况有一种经典的优化建边方法。

$a_i$ 表示选第 $i$ 个点为关键点 , $a_i'$ 表示不选。

对于边 $(u,v)$ , 建边 $(a_u',a_v),(a_v',a_u)$。

对于每一组的点 $p_i$ 表示这一组前 $i$ 个点有关键点 , $p_i'$ 表示没有。

然后建一些边:

对于每一组 , 考虑到这一组的第 $i$ 个数 $s_i$。

如果这一组第 $i$ 个之前已经存在关键点 , 那么 $i$ 不能是关键点:$(p_{i-1},a_{s_i}')$。

如果这一组第 $i-1$ 个之前已经存在关键点 , 那么 $i$ 之前有关键点:$(p_{i-1},p_i)$。

如果这一组第 $i$ 个之前不存在关键点 , 那么 $i-1$ 之前没有关键点:$(p_i',p_{i-1}')$。

如果这一组第 $i$ 个是关键点 , 那么 $i$ 及之前有关键点:$(a_{s_i},p_i)$。

如果这一组第 $i$ 个是关键点 , 那么 $i-1$ 及之前没有关键点:$(a_i,p_{i-1}')$。

如果这一组第 $i$ 个之前不存在关键点 , 那么 $i$ 不是关键点:$(p_i',a_{s_i}')$。

注意 $p_i$ 的下标顺着 $n$ 向后扩展到 $2n$ , 这样建 $6$ 倍边就可以啦。

模拟赛遇到这个题 , 因为用的 vector 被卡常了 , 边还是比较多 , 最好用链表来存边。

------------
Code

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define ll long long
#define ull unsigned long long

using namespace std; 

int read(){int qrx=0,qry=1;char qrc=getchar();
while(qrc<'0'||qrc>'9'){if(qrc=='-')qry=-1;qrc=getchar();}
while(qrc>='0'&&qrc<='9')qrx=qrx*10+qrc-'0',qrc=getchar();
return qrx*qry;}

const int N=8e6+7,Mod=998244353,INF=0x3f3f3f3f;
int n,m,dfn[N],low[N],vis[N],tot,st[N],cnt,cl[N],cn,k,S;
int hd[N],nxt[N],to[N],ec;

void add(int u,int v){
	nxt[++ec]=hd[u];
	hd[u]=ec,to[ec]=v;
	return;
}

void tarjan(int u){
	dfn[u]=low[u]=++tot,st[++cnt]=u,vis[u]=1;
	for(int i=hd[u];i!=0;i=nxt[i]){
		int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])low[u]=min(low[u],dfn[v]);
	}
	
	if(dfn[u]==low[u]){
		cl[u]=++cn,vis[u]=0;
		while(st[cnt]!=u)cl[st[cnt]]=cn,vis[st[cnt--]]=0;
		--cnt;
	}
	return;
}

int main(){
	n=read(),m=read(),k=read();
	for(int i=1,u,v;i<=m;i++){
		u=read(),v=read();
		if(u==v)continue;
		add(u,v+(n<<1)),add(v,u+(n<<1));
	}
	
	int now=0;
	for(int i=1;i<=k;i++){
		int w=read();
		for(int j=1;j<=w;j++){
			S=read();
			add(S+(n<<1),now+j+n*3),add(now+j+n,S);
			if(j>1){
				add(now+j-1+n*3,now+j+n*3),add(now+j-1+n*3,S);
				add(now+j+n,now+j-1+n),add(S+(n<<1),now+j-1+n);
			}
		}
		now+=w;
	}
	
	n*=4;
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	n/=4;
	
	for(int i=1;i<=n;i++)if(cl[i]==cl[i+(n<<1)])return !printf("NIE\n");
	printf("TAK\n");
	return 0;
}
```


---

## 作者：Stinger (赞：1)

非常腻害（？）的一个科技，前缀优化建图。

首先看到"每条边**至少**有一个端点是关键点"珂以想到 2-SAT，对于每个点建立两个点 $x_1,x_2$ 分别表示 $x$ 不是关键点和是关键点。

对于每条原图中的边 $x\rightarrow y$，在 2-SAT 的图中连 $x_1\rightarrow y_2,y1\rightarrow x_2$ 这两条边。

但是每个部分只能有一个关键点，为了满足这个需求我们需要对于每个在这个部分 $i$ 里的 $x$ 点，从 $x_2$ 向 $i$ 部分其它所有点 $y$ 的 $y_1$ 连边。你当然可以线段树优化建图，但是太慢了~~还很可能会被卡（雾~~

所以前缀优化建图到底是什么东西？我们定义前缀为 $x$ 节点所在的部分，按照题目中的输入顺序中，在 $x$ 前面输入的部分（**包含 $x$ 本身**）。比如对于样例，$4$ 的前缀就是 $3,4$。

对于每个点再建立两个点 $x_3,x_4$ 分别表示前缀没有关键点和有关键点，那么如果 $x$ 本身就是关键点，前缀肯定有关键点，所以连一条 $x_2\rightarrow x_4$ 的边。

同理，如果前缀都没有关键点，$x$ 本身肯定也不是关键点，所以从 $x_3$ 向 $x_1$ 连边。

接下来考虑 $x$ 以及输入顺序中在 $i$ 前一个输入的点 $y$（$x$ 和 $y$ 是一个部分的点）。

- 如果 $y$ 的前缀有关键点，则 $x$ 前缀也有关键点，连边 $y_4\rightarrow x_4$。
- 如果 $x$ 前缀没有关键点，则 $y$ 前缀可定没有关键点，连边 $x_3\rightarrow y_3$。
- 如果 $y$ 前缀已经有了关键点，那么 $x$ 就不能是关键点了，连边 $y_4\rightarrow x_1$。
- 如果 $x$ 是关键点，$y$ 前缀肯定不能有关键点，连边 $x_2\rightarrow y_3$。

补充一下，其实在上面的连边过程中有些边我们没有连，比如 $x$ 是关键点，$y$ 肯定不是关键点。但如果 $x$ 是关键点，$y$ 的前缀都没有关键点，$y$ 怎么可能是关键点？图中也有 $x_3\rightarrow y_3\rightarrow y_1$ 的边。

虽然点数有 $4$ 的常数，边数有 $8$ 的常数，~~但随便怎么样还是把线段树这些常数和复杂度都上天的东西吊着打（~~

```cpp
/*
x_1 编号是 x
x_2 编号是 x+n 
x_3 编号是 x+3*n
x_4 编号是 x+2*n 
*/
#include <cstdio>
#include <cstring>
#define gc (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 65536, stdin), p1 == p2) ? EOF : *p1 ++)
const int N = 8000005, M = 10000005;
inline int min(const int x, const int y) {return x < y ? x : y;}

char buf[65536], *p1, *p2;
inline int read() {
	char ch;
	int x = 0;
	while ((ch = gc) < 48);
	do x = x * 10 + ch - 48; while ((ch = gc) >= 48);
	return x;
}

int n, m, k;
struct TwoSAT {
	struct Edge {
		int to, nxt;
	} e[M];
	int head[N], s[N], dfn[N], low[N], col[N], tot, top, cnt, scc;
	bool Instack[N];
	inline void AddEdge(const int u, const int v) {
		e[++ tot].to = v, e[tot].nxt = head[u], head[u] = tot;
	}
	void Tarjan(int u) {
		dfn[u] = low[u] = ++ cnt, s[++ top] = u, Instack[u] = true;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
			else if (Instack[v]) low[u] = min(low[u], dfn[v]);
		}
		if (dfn[u] == low[u]) {
			++ scc;
			do
				col[s[top]] = scc, Instack[s[top]] = false;
			while (s[top --] != u);
		}
	}
	bool solve() {
		for (int i = 1; i <= 4 * n; ++ i)
			if (!dfn[i]) Tarjan(i);
		for (int i = 1; i <= n; ++ i)
			if (col[i] == col[i + n] || col[i + 2 * n] == col[i + 3 * n])
				return false;
		return true;
	}
} solver;

int main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= m; ++ i) {
		int u = read(), v = read();
		solver.AddEdge(u, v + n);
		solver.AddEdge(v, u + n);
	}
	for (int i = 1; i <= n; ++ i) {
		solver.AddEdge(i + n, i + 2 * n);
		solver.AddEdge(i + 3 * n, i);
	}
	for (int i = 1; i <= k; ++ i) {
		int T, pre, x;
		T = read(), pre = read();
		while (-- T) {
			x = read();
			solver.AddEdge(pre + 2 * n, x + 2 * n);
			solver.AddEdge(x + 3 * n, pre + 3 * n);
			solver.AddEdge(pre + 2 * n, x);
			solver.AddEdge(x + n, pre + 3 * n);
			pre = x;
		}
	}
	puts(solver.solve() ? "TAK" : "NIE");
	return 0;
}
```



---

## 作者：Aisaka_Taiga (赞：0)

## 2-SAT

暴力思路：

设 $i$ 表示当前点为 $1$，$i + n$ 表示当前点为 $0$。

题目中说**每条边至少有一个端点是关键点**，所以对于一条边 $(u,v)$ 可以确定以下的关系：

* 若 $u$ 为 $0$，则 $v$ 必定为 $1$，连边：$u + n \to v$。

* 若 $v$ 为 $0$，则 $u$ 必定为 $1$，连边：$v + n \to u$。

对于 $k$ 个部分，若其中一个点是 $1$，那么其他点必须是 $0$。

但是最坏情况下这个过程是 $O(n^2)$ 的，而且空间也会炸。

考虑优化一下建图过程：

设当前点集需要这样连边：

![](https://cdn.luogu.com.cn/upload/image_hosting/l1s21qyd.png)

再开 $2n$ 个点，按照以下的方式连边：

![](https://cdn.luogu.com.cn/upload/image_hosting/8aj1iw2r.png)

可以发现，每一个点对应的上面多了两个点，而且向其中一个连边后，对于向后的 $n$ 个点，会把后面的点都给与 $2$ 相连，对于向前的 $n$ 个点，会把前面的点使得 $2$ 能够到达。

就像下面这样，同样达到了一开始的图的效果。

![](https://cdn.luogu.com.cn/upload/image_hosting/hyzg5yrn.png)

也就是说，我们总共多加了 $2n$ 个点和 $4n$ 条边，就能让对于 $k$ 个部分的建边数降到了 $2n$，加上之前的对于边的 $2n$ 条边，总共对于点开 $4n$，边开 $8n$ 即可通过此题。

code：

```cpp

/*
 * @Author: Aisaka_Taiga
 * @Date: 2023-09-28 14:25:43
 * @LastEditTime: 2023-09-28 14:41:46
 * @LastEditors: Aisaka_Taiga
 * @FilePath: \Desktop\P6378.cpp
 * The heart is higher than the sky, and life is thinner than paper.
 */
#include <bits/stdc++.h>

#define int long long
#define N 4000100

using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
    while(c <= '9' && c >= '0') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * f;
}

int n, m, k, cnt, head[N], dfn[N], low[N], stk[N], top, sd[N], vis[N], scc, tim, a[N], ff;
struct node{int u, v, next;}e[N << 1];

inline void add(int u, int v){e[++ cnt] = (node){u, v, head[u]}; head[u] = cnt;}

inline void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ top] = u;
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        int y; scc ++;
        while(1)
        {
            y = stk[top --];
            sd[y] = scc;
            vis[y] = 0;
            if(u == y) break;
        }
    }
    return ;
}

signed main()
{
    n = read(); m = read(); k = read();
    for(int i = 1; i <= m; i ++)
    {//i+n是0,i是1
        int u = read(), v = read();
        add(u + n, v);
        add(v + n, u);
    }
    for(int i = 1; i <= k; i ++)
    {
        int up = read(), cc = 0;
        for(int j = 1; j <= up; j ++) a[j] = read();
        for(int j = 1; j <= up; j ++)
        {
            add(a[j] + 3 * n, a[j] + n);
            add(a[j] + 2 * n, a[j] + n);
            if(j != 1) add(a[j] + 3 * n, a[j - 1] + 3 * n);
            if(j != up) add(a[j] + 2 * n, a[j + 1] + 2 * n);
        }
        for(int j = 1; j <= up; j ++)
        {
            if(j != 1) add(a[j], a[j - 1] + 3 * n);
            if(j != up) add(a[j], a[j + 1] + 2 * n);
        }
    }
    for(int i = 1; i <= 2 * n; i ++)
        if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i ++)
        if(sd[i] == sd[i + n]) ff = 1;
    if(ff) cout << "NIE" << endl;
    else cout << "TAK" << endl;
    return 0;
}
```

---

## 作者：Butterfly_qwq (赞：0)

思路很巧妙的一道题。

每条边至少有一个端点是关键点就是经典的 2-SAT 问题，不会 2-SAT 出门左转[这里](https://www.luogu.com.cn/problem/P4782)。

那我们考虑一下每个部分恰有一个关键点怎么做。

解法一如下。

这是一个 w-SAT 问题（$w$ 的含义见输入格式）。

一个很经典的 NPC 问题，即只能使用暴力解决的问题（当然 $w\le2$ 是能做的）。

复杂度不被允许。

解法2如下：

将 w-SAT 转化成 2-SAT。

一个选了就说明其他的不能选，那么对于每一个点的选点和所有和他同处一个集合（不包含自己）的不选点连边即可。

先不考虑时间复杂度，空间复杂度就是 $O(n^2)$。

解法3如下。

我们建 $4$ 层点而不是像经典问题一样建 $2$ 层。

为了方便我们只考虑一个集合的问题。

前两层和经典问题一样分别表示第 $i$ 个选和第 $i$ 个不选。

后两层分别表示前 $i$ 个选和前 $i$ 个不选。

那么就可以得到如下建图：

1. 第 $i$ 个选就说明前 $i$ 个选。
2. 前 $i$ 个不选就说明第 $i$ 个不选。
3. 前 $i$ 个点选就说明第 $i+1$ 个点不选。
4. 第 $i$ 个点选就说明前 $i-1$ 个点不选。
5. 前 $i$ 个点选就说明前 $i+1$ 个点选。
6. 前 $i$ 个点不选就说明前 $i-1$ 个点不选。

AC Code:

```
/*
Author:FeS2_qwq
Start Coding:2023.8.15 16:02
Finish Debugging:2023.8.15 18:18
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int sccno[N*4],low[N*4],dfn[N*4],head[N*4],idx,cnt,sccnum,si[N*4];
stack<int> s;
struct edge
{
	int to,next;
}e[N*10];
void add(int u,int v)
{
	e[++cnt]={v,head[u]};
	head[u]=cnt;
}
void tarjan(int u)
{
	dfn[u]=low[u]=++idx;
	s.push(u);
	si[u]=1;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(si[v])low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		sccnum++;
		int v=-1;
		while(v!=u)
		{
			v=s.top();
			s.pop();
			si[v]=0;
			sccno[v]=sccnum;
		}
	}
}
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		add(a+n,b);
		add(b+n,a);
	}
	while(k--)
	{
		int w,lst=-1;
		cin>>w;
		while(w--)
		{
			int u;
			cin>>u;
			add(u,u+2*n);
			add(u+3*n,u+n);
			if(lst!=-1)
			{ 
				add(lst+2*n,u+2*n);
				add(u+3*n,lst+3*n);
				add(lst+2*n,u+n);
				add(u,lst+3*n);
			} 
			lst=u;
		}
	}
	for(int i=1;i<=(n<<2);i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
	{
		if(sccno[i]==sccno[i+n]||sccno[i+2*n]==sccno[i+3*n])
		{
			cout<<"NIE";
			return 0;
		}
	}
	cout<<"TAK";
	return 0;
}
```

---

