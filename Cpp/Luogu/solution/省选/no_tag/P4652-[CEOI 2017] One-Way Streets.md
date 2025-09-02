# [CEOI 2017] One-Way Streets

## 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图，现在想要把这张图定向。

有 $p$ 个限制条件，每个条件形如 $(x_i,y_i)$，表示在新的有向图当中，$x_i$ 要能够沿着一些边走到 $y_i$​​。

现在请你求出，每条边的方向是否能够唯一确定。同时请给出这些能够唯一确定的边的方向。

数据保证有解。

## 说明/提示

对于所有测试点，有 $1\le n,m,p\le 100\ 000;1\le a_i,b_i,x_i,y_i\le n$。

## 样例 #1

### 输入

```
5 6
1 2
1 2
4 3
2 3
1 3
5 1
2
4 5
1 3```

### 输出

```
BBRBBL```

# 题解

## 作者：Twilight_star (赞：13)

[题目传送门](https://www.luogu.com.cn/problem/P4652)
## 前置知识
1. 边双连通分量

2. 缩点

## 题意

给定一张 $n$ 个点 $m$ 条边的无向图，现在想要把这张图定向。

有 $p$ 个限制条件，每个条件形如 $(x_i,y_i)$，表示在新的有向图当中，$x_i$ 要能够沿着一些边走到 $y_i$​​。

现在请你求出，每条边的方向是否能够唯一确定。同时请给出这些能够唯一确定的边的方向。

数据保证有解。


-    若第 $i$ 条边必须得要是 $a_i$​​ 指向 $b_i$ 的，那么这个字符串的第 $i$ 个字符应当为 ``R``；

-    若第 $i$ 条边必须得要是 $b_i$​​ 指向 $a_i$​​ 的，那么这个字符串的第 $i$ 个字符应当为 ``L``；

-    否则，若第 $i$ 条边的方向无法唯一确定，那么这个字符串的第 $i$ 个字符应当为 ``B``。

## 整体思路

我们能确定一条边的方向，当且仅当至少一组 $ x_i $ 到 $ y_i $ 
必须经过这条边。那实际上也就是这条边是一条“割边”，也就是说删去这条边，左右两端的联通块之间没有任何边相连。

所以我们要去找**割边**。


但换句话讲，也就是找到一个个**边双连通分量**，每个边双连通分量内部的边都是不定的，因为这个联通分量内部的点之间互相可以到达且路径不止一条，就算删去了某条边，也依然可以从另一条路径到达。

（不会边双连通分量的同学请左转，[P8436 【模板】边双连通分量](https://www.luogu.com.cn/problem/P8436)）

但找到每个边双连通分量后该如何确定中间的“割边”的方向呢？

我们可以暴力去遍历每一个限制条件，但这样会超时。

那我们再想一想会发现，每个边双连通分量内部的边都不确定方向，就不用考虑了（反正输出``B``就完了）。我们只用考虑剩下的“割边”。

所以我们可以把每个边双连通分量用缩点缩起来，这样点与点之间的边就是原图上的“割边”了。

（不会缩点的同学请右转，[P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)）

我们知道一棵树的每条边都是“割边”，因为任意删去一条边都会导致这棵树**不再联通**，所以我们缩完点后的图就可以近似的看成一棵树，只不过它有可能不联通，所以准确来说，是一个森林（很多棵树）。

而树上问题就要比图上问题方便得多了，因为两点之间的路径是唯一的。

不过话说回来，我们要快速确定新图中每条边的方向。
可以想到用树上差分。但可能跟“树上点差分”和“树上边差分”这样的“用来求和的差分”有所不同，我们只用统计每条边的方向。

不妨假设当这个点的差分值为**正整数**时，这个点通向他父亲的边是向根节点的。

当这个点的差分值为**负整数**时，这个点通向他父亲的边是向叶子节点的。

而当这个点的差分值为零时，这个点通向他父亲的边就是不定向的。

那我们只用知道这个点的差分值是正还是负。

所以当限制条件为 $ x_i $ 和 $ y_i $ 时，设数组 $ cha $ 
为差分数组，我们就将 $ cha[x_i] $ 加一，将 $ cha[y_i] $ 减一。

差分加减完成后别忘了从根节点开始递归，统计差分值。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,M=400005;
int n,m,q,head[M],head2[M],cnt2,cnt=1;//用链式前向星存图  
//cnt初始化为1的好处：编号为i^1的边就是编号i的边的反向边 
int dfn[N],low[N],idx;//求边双连通分量的数组 
int col[N],tmp;//每个点属于的边双连通分量的编号，以及边双连通分量的个数 
int cha[N],d[N];//差分数组，新图上节点的深度 
bool b[M];//判断是否为割边 
struct tree//新图 
{
    int v,nxt;
}e[M];
struct node//原图 
{
    int v,nxt,u;
}a[M];
void add(int u,int v)//原图链式前向星存图 
{
    a[++cnt].v=v;
    a[cnt].u=u;//这里存一下边的起点方便后面用 
    a[cnt].nxt=head[u];
    head[u]=cnt;
}
void add2(int u,int v)//新图链式前向星存图 
{
    e[++cnt2].v=v;
    e[cnt2].nxt=head2[u];
    head2[u]=cnt2;
}
int read()//快读 
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
//这里求边双连通分量的方法是把所有割边“删去”，再搜一遍剩下的图 
void tarjan(int u)//求割边 
{
    dfn[u]=low[u]=++idx;
    for(int i=head[u];i!=0;i=a[i].nxt)
    {
        int v=a[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]) b[i]=b[i^1]=1;//标记割边 
        }
        else low[u]=min(low[u],dfn[v]);
    }
}
void dfs1(int u,int num)//当前搜索到第几个点以及当前边双连通分量的编号 
{
    col[u]=num;//编号 
    for(int i=head[u];i!=0;i=a[i].nxt) 
    {
        if(!col[a[i].v]&&b[i]==0) dfs1(a[i].v,num);//如果这条边不是割边就可以访问 
    }
}
void dfs(int u,int fa)//统计差分数组 
{
    d[u]=d[fa]+1;//更新深度 
    for(int i=head2[u];i!=0;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v!=fa) 
        {
            dfs(v,u);
            cha[u]+=cha[v];//统计差分数组 
        }
    }
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        add(u,v),add(v,u);//加边 
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);//求割边，（原图不一定联通） 
    for(int i=1;i<=n;i++) if(!col[i]) tmp++,dfs1(i,tmp);//求边双连通分量 
    for(int i=2;i<=cnt;i++)
    {
        if(col[a[i].u]!=col[a[i].v]) add2(col[a[i].u],col[a[i].v]);//缩点+加新边 
    }
    q=read();
    while(q--)
    {
        int u=read(),v=read();
        cha[col[u]]++,cha[col[v]]--;//差分 
    }
    for(int i=1;i<=tmp;i++)if(!d[i])dfs(i,0);//统计差分数组，（新图也不一定联通） 
    for(int i=2;i<=cnt;i+=2)//两个两个地加，过滤掉反向边 
    {
        if(col[a[i].u]==col[a[i].v]) //如果是在同一个边双连通分量里 
        {
            printf("B");//那么边的方向就不确定 
            continue;
        }
        if(d[col[a[i].u]]>d[col[a[i].v]])//如果这条边的起点所在的边双连通分量更深，那么这条边的差分值就在起点 
        {
            if(cha[col[a[i].u]]>0) printf("R");//说明这条边是指向根节点，也就指向这条边的终点
            else if(cha[col[a[i].u]]==0) printf("B");//如果没有一个限制条件经过这条边，就输出B 
            else printf("L");//反之 
        }
        else
        {
            if(cha[col[a[i].v]]>0) printf("L");//说明这条边是指向根节点，也就指向这条边的起点（起点深度更小） 
            else if(cha[col[a[i].v]]==0) printf("B");//同上 
            else printf("R");//反之  （这里不要写成L了） 
        }
    }
    return 0;
}

```
### 闲话 
（我居然有朝一日能抢到最优解！！！）（2023.10.4）
![](https://cdn.luogu.com.cn/upload/image_hosting/jn6v6a12.png)

---

## 作者：Coros_Trusds (赞：6)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16286912.html)

巧妙的一道题！！！

# 题目大意

给定一张 $n$ 个点 $m$ 条边的无向图，现在想要把这张图定向。

有 $p$ 个限制条件，每个条件形如 $(x_i,y_i)$，表示在新的有向图当中，$x_i$ 要能够沿着一些边走到 $y_i$。

现在请你求出，每条边的方向是否能够唯一确定。同时请给出这些能够唯一确定的边的方向。

数据保证有解。

# 题目分析

什么情况下能够对一条边定向呢？首先，这条边一定不存在于一个连通分量中（如果在连通分量中就不能唯一确定方向了）；其次，这条边一定是路径 $x_i\to y_i$ 上的必经边。

于是我们对整个图 $G$ 进行边双连通分量缩点得到新图 $G'$，**$G'$ 一定是森林**。$G$ 中 $x_i\to y_i$ 上的必经边也就是 $G'$ 中 $col[x_i]\to col[y_i]$ 上的必经边。

然后就是重点了：怎样才能判断一条必经边的方向呢？

树上差分可以解决问题，但普通的边差分修改方式是 $tong[u]+1,tong[v]+1,tong[\operatorname{lca(u,v)}]-1,tong[\operatorname{fa(lca(u,v))}]-1$，可在这里绝对是行不通的。我们需要将树上差分改改。

上图：

![](https://s2.ax1x.com/2019/10/29/K227c9.png)

假设有一个限制条件为 $x_i=8,y_i=6$。那么我们看看 $8\to 6$ 这条路径。首先 $8\to 1$ 这一段都是从子节点连向父节点的边，而 $1\to 6$ 这一段都是从父节点连向子节点的边。

既然如此，如果设 $f=\operatorname{lca}(x_i,y_i)$，则可以分为两段：$x_i\to f,f\to y_i$。所以我们将树上差分改为 $tong[x_i]+1,tong[y_i]-1$ 就没事了。最后计算时采用递归的方式，一个点的权值就是其儿子节点的权值的和。

如果一个点点权为负数，说明该点与父节点的边是从父节点到子节点方向的；如果一个点点权为正数，说明该点与父节点的边是从子节点到父节点方向的；如果点权为 $0$，说明无法确定。解释上面已经说过。注意，现在我们不关心 $tong$ 数组具体的值了，只关注其正负情况。

于是对森林中的每一棵树都进行 $\rm dfs$ 统计答案，然后就没了。

-----

无论如何，这道题一定需要知道：

> 如果一个点点权为负数，说明该点与父节点的边是从父节点到子节点方向的；如果一个点点权为正数，说明该点与父节点的边是从子节点到父节点方向的；如果点权为 $0$，说明无法确定。解释上面已经说过。注意，现在我们不关心 $tong$ 数组具体的值了，只关注其正负情况。

# 代码

```cpp
//2022/5/18
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <stack>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 1e5 + 5;
struct Graph {
	struct Node {
		int v,id,nxt;
		//id:边在输入中的编号
	} gra[N << 1];
	int head[N];
	int idx = 1;
	inline void add(int u,int v,int way) {
		gra[++ idx] = (Node){v,way,head[u]},head[u] = idx;
	}
} g1,g2;
int dfn[N],low[N],col[N],tong[N];
char res[N];
bool in_stack[N],vis[N];
std::stack<int>st;
int n,m,k,num,cnt;
inline void tarjan(int now,int pre) {
	low[now] = dfn[now] = ++ num,in_stack[now] = true;
	st.push(now);
	for (register int i = g1.head[now];i;i = g1.gra[i].nxt) {
		if (i != (pre ^ 1)) {
			int v = g1.gra[i].v;
			if (!dfn[v]) {
				tarjan(v,i);
				low[now] = std::min(low[now],low[v]);
			} else {
				low[now] = std::min(low[now],dfn[v]);
			}
		}
	}
	if (dfn[now] == low[now]) {
		cnt ++;
		int u;
		do {
			u = st.top();st.pop();
			in_stack[u] = false,col[u] = cnt;
		} while (u != now);
	}
}
inline int Abs(int x) {
	return x > 0 ? x : -x;
}
//id:now <-> fa(now) 的编号
//way = 1:now <- fa(now)
//way = -1:now -> fa(now)
inline void dfs(int now,int id,int way) {
	vis[now] = true;
	for (register int i = g2.head[now];i;i = g2.gra[i].nxt) {
		int v = g2.gra[i].v;
		if (!vis[v]) {
			if (g2.gra[i].id > 0) {
				dfs(v,Abs(g2.gra[i].id),1);
			} else {
				dfs(v,Abs(g2.gra[i].id),-1);
			}
			tong[now] += tong[v];
		}
	}
	if (tong[now] != 0) {
		if (tong[now] * way > 0) {
			res[id] = 'L';
		} else {
			res[id] = 'R';
		}
	}
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read(),m = read();
	for (register int i = 1;i <= m; ++ i) {
		int u = read(),v = read();
		//u -> v 是正数
		//v -> u 是负数
		g1.add(u,v,i),g1.add(v,u,-i);
	}
	for (register int i = 1;i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i,-1);
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		for (register int j = g1.head[i];j;j = g1.gra[j].nxt) {
			int v = g1.gra[j].v;
			if (col[i] != col[v]) {
				g2.add(col[i],col[v],g1.gra[j].id);
			}
		}
	}
	k = read();
	while (k --) {
		int u = read(),v = read();
		tong[col[u]] ++,tong[col[v]] --;
	}
	for (register int i = 1;i <= m; ++ i) res[i] = 'B';
	for (register int i = 1;i <= n; ++ i) {
		if (!vis[i]) {
			dfs(i,0,0);
		}
	}
	printf("%s\n",res + 1);

	return 0;
}
```

---

## 作者：ZZXB (赞：6)

可以得到一个的结论:在同一个双联通分量中的点之间的边方向无法确定。

所以可以缩点，然后得到一个森林。

对于要求的方向，多定义一个$a$数组，对于起点$x$，$a[x]++$,终点$y$，$a[y]--$（听说这个操作叫树上差分）。

每一点走向父节点的边方向可以记住$a$来判断。

$a<0$则应由父节点走向子节点

$a>0$则应由子节点走向父节点

$a=0$则无法判断方向。

贴上鬼畜的代码

```c
#include<cstdio>
#include<string>
#include<cstring>
#define R_ register
inline int read() {
	int ret=0,f=1,ch=getchar();
	for (; !isdigit(ch); ch=getchar()) if (ch=='-') f=-f;
	for (; isdigit(ch); ch=getchar()) ret=ret*10+ch-48;
	return ret*f;
}
const int maxn=2e5+5;
struct edge {int son,nxt,id,s;} E[maxn],T[maxn];
int top,tar,cnt,sta[maxn],dfn[maxn],low[maxn],bel[maxn];
int N,M,P,tot=1,lnk[maxn],hed[maxn],Ans[maxn],vis[maxn],a[maxn];
inline void add_edge(int y,int x,int id) {
	E[++tot].son=y,E[tot].nxt=lnk[x],lnk[x]=tot,E[tot].id=id,E[tot].s=+1;
	E[++tot].son=x,E[tot].nxt=lnk[y],lnk[y]=tot,E[tot].id=id,E[tot].s=-1;
}
inline void Add_edge(int x,int y,int id,int s) {
	T[++tot].son=y,T[tot].nxt=hed[x],hed[x]=tot,T[tot].id=id,T[tot].s=s;
}
void tarjan(int x,int pre=0) {
	dfn[x]=low[x]=++cnt,sta[++top]=x;
	for (R_ int k=lnk[x],v; v=E[k].son,k; k=E[k].nxt) if (k^pre)
		if (!dfn[v]) {
			tarjan(v,k^1),low[x]=std::min(low[x],low[v]);
			if (low[v]>dfn[x]) {
				for (++tar; sta[top]^v; ) bel[sta[top]]=tar,--top;
				bel[sta[top]]=tar,--top;
			}
		} else low[x]=std::min(low[x],dfn[v]);
}
void dfs(int x,int fa,int id,int s) {
	for (R_ int k=hed[x],v; v=T[k].son,k; k=T[k].nxt) if (!vis[v])
		vis[v]=1,dfs(v,x,T[k].id,T[k].s),a[x]+=a[v];
	if (a[x]) Ans[id]=(a[x]*s<0?1:2);
}
int main() {
	R_ int i,k,x,y;
	for (N=read(),M=read(),i=1; i<=M; ++i) add_edge(read(),read(),i);
	for (i=1; i<=N; ++i) if (!dfn[i]) tarjan(i);
	if (top) for (++tar; top; --top) bel[sta[top]]=tar;
	for (tot=i=1; x=bel[i],i<=N; ++i)
		for (k=lnk[i]; y=bel[E[k].son],k; k=E[k].nxt)
			if (x^y) Add_edge(x,y,E[k].id,E[k].s);
	for (P=read(),i=1; i<=P; ++i) ++a[bel[read()]],--a[bel[read()]];
	for (i=1; i<=tar; ++i) if (!vis[i]) vis[i]=1,dfs(i,0,0,0);
	for (i=1; i<=M; ++i) putchar(!Ans[i]?'B':(Ans[i]==1?'R':'L'));
	return 0;
}
```
~~最后吐槽一句，为什么这题是黑题？~~

~~再吐槽一句，为什么时限是3秒？总时限吗？~~

---

## 作者：AbsMatt (赞：4)

赛时难得很快就看出来了，结果狂调 1h 后爆 $0$，依旧写篇题解以作纪念
### [题目传送器](https://www.luogu.com.cn/problem/P4652)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-p4652)

## 题意
给一个无向图定向，再给定 $p$ 对形如 $(x_i,y_i)$ 限制，需要保证 $x_i$ 能到达 $y_i$，保证有解，求每条边的方向或是无法确定。

## 做法
给无向图定向并求 $p$ 对能到达的关系明显是与连通性相关的问题。考虑建一棵生成树后将每一条边分为树边和非树边。考虑每一条非树边对答案的影响。

### 步骤一
设非树边为 $(u,v)$，则可以由树边从 $u$ 走到 $lca(u,v)$，也可以由树边从 $v$ 走到 $lca(u,v)$，也可以由当前边从 $u$ 走到 $v$，故此时形成了一个环。显然，这条环上的边的方向都是无法确定的，即输出 ``B``。因为可以从 $u$ 先往 $lca(u,v)$ 走，也能从 $u$ 先往 $v$ 走。

### 步骤二
接着思考如何给边定固定向，设当前要求能从 $x$ 到达 $y$，且不存在步骤一的情况。依旧显然，只能通过从 $x$ 走到 $lca(x,y)$，再从 $lca(x,y)$ 走到 $y$。故 $x$ 到 $lca(x,y)$ 的边的方向都是指向深度小的点，$lca(x,y)$ 到 $y$ 的边的方向都是指向深度大的点。

### 步骤三
除去以上步骤依旧无法确定的边就不受条件的限制，则答案为 ``B``。

## 实现
可以先暴力地从 $u$ 将 跳到 $lca$ 进行修改，时间复杂度为 $O(n \times m + n \times p)$。图不保证联通，记得每棵树都要处理。

### [Code](https://loj.ac/s/2010369)

## 优化
将树上的路径的答案覆盖成一个值明显可以使用重链剖分，将 $(u,v)$ 的答案下放到节点 $v$（将边的修改变成点的修改），当然赛时作为 Joker 的我没想出来可以用 $O(n)$ 的树上差分，这里推荐一篇[树上差分的题解](https://www.luogu.com.cn/blog/cyz2010/solution-p4652)并 $\text{Orz \color{black}c\color{red}yz2010}$。时间复杂度为 $O(n \times \log_2^2n)$，瓶颈在树链剖分，需要轻微卡常，细节有点多。

### [Code](https://loj.ac/s/2006773)

---

## 作者：free_fall (赞：4)

给定一张无向图，以及一些路径，要求给这张无向图定向之后满足这些路径要求。

先考虑这个问题的简化版，如果每两个点之间的路径是唯一的，即这是一颗树，该如何处理？

这个问题非常简单，因为 $a_i$ 到 $b_i$ 的路径上经过的边是唯一确定的，所以我们只需将 $a_i$ 到 $b_i$ 的唯一路径上的所有边都指向 $b_i$ 即可。最后没有被定向的边就是无法唯一确定的。

而原题中给定的是一张无向图，与树不同的地方就在于 $a_i$ 到 $b_i$ 的路径不是唯一的，所以我们无法确定一些边的方向。重点：我们无法确认一条边的方向，因为 $a_i$ 到 $b_i$ 可能不经过它，也就是说**我们只能确定 $a_i$ 到 $b_i$ 的路径中必定经过的边，这些边就是图中的“桥”**，（仔细思考一下“桥”的定义）。

这样一来问题就变得简单了，我们用 tarjan 边双缩点，得到了一片森林，森林中每一棵树上的每一条边都是“桥”，这样一来，问题就变成了刚才提到的树上的版本。注意，如果两个点在同一个边双中，说明它们之间没有任何“桥”，直接不作处理。

又因为路径的数量特别多，我们无法暴力处理，于是考虑使用树上差分（树上差分是真的方便）。对于一个节点我们用 $d_i$ 记录它与它父亲之间的边的状态，0 为无法唯一确定，1 为指向父亲，-1 为指向它自己。我们只需将 $d_{a_i}$ 加一，$d_{b_i}$ 减一即可，这里甚至不需要做 LCA，因为这两个点的影响会在 LCA 抵消（1+(-1)=0 嘛）。

具体实现见代码，时间复杂度为 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,p,u[N],v[N],d[N],dfn[N],low[N],cnt_dfn;
int st[N],top,fa[N],tot,dep[N];//fa[i] 记录的其实是 i 在哪个边双中（实在不知道要起什么名字了）
vector<int> e[N];
struct kk{
	int to,id;
};
vector<kk> edge[N];
void tarjan(int now,int las){
	dfn[now]=low[now]=++cnt_dfn;
	st[++top]=now;
	for(int i=0;i<edge[now].size();i++){
		int to=edge[now][i].to,id=edge[now][i].id;
		if(id==las)continue;
		if(!dfn[to]){
			tarjan(to,id);
			low[now]=min(low[now],low[to]);
		}
		else low[now]=min(low[now],dfn[to]);
	}
	if(dfn[now]==low[now]){
		tot++;
		while(st[top]!=now)fa[st[top--]]=tot;
		fa[st[top--]]=tot;
	}
	return;
}
void dfs(int now,int las){
	dep[now]=dep[las]+1;
	for(int i=0;i<e[now].size();i++){
		int to=e[now][i];
		if(to==las)continue;
		dfs(to,now);
		d[now]+=d[to];
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u[i],&v[i]);
		edge[u[i]].push_back({v[i],i});
		edge[v[i]].push_back({u[i],i});
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])tarjan(i,0);
	}
	for(int i=1;i<=m;i++){
		int uu=fa[u[i]],vv=fa[v[i]];
		if(uu==vv)continue;
		e[uu].push_back(vv);
		e[vv].push_back(uu);
	}
	scanf("%d",&p);
	while(p--){
		int u,v;
		scanf("%d%d",&u,&v);
		d[fa[u]]++,d[fa[v]]--;
	}
	for(int i=1;i<=tot;i++){
		if(!dep[i])dfs(i,0);
	}
	for(int i=1;i<=m;i++){
		int uu=fa[u[i]],vv=fa[v[i]];
		if(uu==vv){
			printf("B");
			continue;
		}
		if(dep[uu]>dep[vv]){
			if(d[uu]>0)printf("R");
			if(d[uu]<0)printf("L");
			if(d[uu]==0)printf("B");
		}
		if(dep[vv]>dep[uu]){
			if(d[vv]>0)printf("L");
			if(d[vv]<0)printf("R");
			if(d[vv]==0)printf("B");
		}
	}
	return 0;
}
```
不是很会写题解，希望讲明白了 QwQ。

---

## 作者：CYZZ (赞：3)

## [P4652](https://www.luogu.com.cn/problem/P4652)
赛时口胡出了只需要树上差分的 $\mathcal{O(n)}$ 做法，可是没时间打，只能说**多练**。
### 思路
首先~~猜出~~，一个边**可能被定向**当且仅当这个边是一个**割边**（别的题解有证明）。

如果一条边不会是割边，当且仅当这个边**在环上**。这样，我们先建出 dfs 树，对于每条**非树边**，把这条边唯一对应的环标记上，树上差分和树剖皆可。

求出了所有割边，考虑什么时候一条割边 $e$ 会被定向。发现当且仅当有一个限制 $(p_i,q_i)$，满足 $p_i$ 和 $q_i$ **恰好分处** $e$ 被割开形成的两个边双里。这样，再次使用树上差分，把 $p_i\rightarrow q_i$ 的路径标记上，表示这条路径上的割边被定向左/右。

注意：这里的树上差分可以不带 log，只需要把两个断点的 $sum$ 值一个加一，一个减一即可，想想为什么。

有两个坑点：一个是图有重边，一个是图不保证联通。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
int n,m;
int tot=1,head[N];
struct Edge{int next,to;}e[N<<1];
void add_edge(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int bk[N],sum[N],is[N],bk2[N];char ans[N];
int dfn[N],idx;
void dfs1(int u,int from)
{
    bk[u]=1;dfn[u]=++idx;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(i==(from^1)) continue;
        if(bk[v])
        {
            if(dfn[v]<dfn[u]) sum[u]++,sum[v]--,is[i/2]=1;ans[i/2]='B';
            continue;
        }
        dfs1(v,i);
    }
}
int bk1[N];
void dfs2(int u,int from)
{
    bk1[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;  
        if(i==(from^1)||is[i/2]) continue;
        dfs2(v,i);sum[u]+=sum[v];
        if(sum[v]) ans[i/2]='B';
    }
}
void dfs3(int u,int from)
{
    bk1[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(i==(from^1)||is[i/2]) continue;
        dfs3(v,i);sum[u]+=sum[v];
        if(ans[i/2]=='B') continue;
        if(sum[v]<0) ans[i/2]=i&1?'R':'L';
        else if(sum[v]>0) ans[i/2]=i&1?'L':'R';
        else ans[i/2]='B';
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    for(int i=1;i<=m;i++) ans[i]=' ';
    for(int i=1;i<=n;i++) if(!bk[i]) dfs1(i,0);
    for(int i=1;i<=n;i++) if(!bk1[i]) dfs2(i,0);
    memset(sum,0,sizeof sum);
    memset(bk1,0,sizeof bk1);
    int k;scanf("%d",&k);
    while(k--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        sum[x]--;sum[y]++;
    }
    for(int i=1;i<=n;i++) if(!bk1[i]) dfs3(i,0);
    for(int i=1;i<=m;i++) if(ans[i]==' ') ans[i]='B';
    for(int i=1;i<=m;i++) cout << ans[i];
}
```
点个赞再走吧，同时推荐码农选手 [Absmatt的题解](https://www.luogu.com.cn/blog/yaohaoyou/solution-p4652)。

---

## 作者：under_the_time (赞：2)

## 题意

> 给定一张无向图和若干个形如 $(x,y)$ 的限制，表示 $x$ 和 $y$ 连通。
>
> 需要求出每条边是否能被确定方向，如果能确定方向则求出它的方向。
>
> 数据保证有解。

## 解法

首先观察到无向图中的边双连通分量中的边无法被定向。路径中经过一个边双的部分，一定可以像下图一样以另一个方向绕过这个边双。

![](https://cdn.luogu.com.cn/upload/image_hosting/4i4qrczd.png)

- 蓝、绿色的路径是两条不同的从 $x$ 到 $y$ 的路径，显然在经过中间的“环”时每条边的走向是相反的，故每条边无法定向。

所以我们考虑把所有的边双缩成一个点，每一个边双中的边都标记为无法定向。这样原来的无向图就变成了一棵树，否则由于是无向图，一定还存在边双连通分量，可以进一步缩成点。建议画一张图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/0cwkvzla.png)

- 假设原图缩完边双后是图（一），那么点 $1,2,4$ 仍可以构成一个边双，将它们缩成一个点后的图（二）即是一棵树的结构。

我们就把图上问题转化为了树上问题。对于每个限制 $(x,y)$，如果 $x,y$ 不在同一边双内，由于树上两点的简单路径唯一，我们只需要将 $x$ 和 $y$ 对应的边双之间的路径进行标记即可。

## 实现

缩点过程可以使用 `Tarjan`。计算每条边的方向时，树链剖分显然可行，但我们也可以采用树上差分。对于每个限制 $(x,y)$（$x,y$ 都是边双的编号且 $x\ne y$），设差分数组为 $d$，则让 $d_x+1\to d_x,d_y-1\to d_y$，最后用 `dfs` 将每个结点的儿子的差分值累加至父亲的差分值里。对于每个点 $x$，如果 $d_x>0$，则说明是该点指向它的父亲；如果 $d_x<0$，则说明是它的父亲指向该点；否则就无法定向。可以手模几组样例看看这个差分法的原理。

时间复杂度：`Tarjan` $O(n)$，`dfs` 统计答案 $O(n)$，总时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 5;
vector<int> mp[maxn];
vector<pair<int,int> > e[maxn];
void addEdge(int u,int v,bool op,int id = 0) {
    if (op) {
        mp[u].push_back(v);
        return ;
    }
    e[u].push_back({v,id}); 
}
int dfn[maxn],low[maxn],st[maxn],b[maxn]; 
int top,tot,clo,U[maxn],V[maxn]; bool vis[maxn];
void tj(int u,int fa) {
    dfn[u] = low[u] = ++ clo;
    vis[st[++ top] = u] = true;
    for (auto V : e[u]) {
        int v = V.first;
        if (V.second == fa) continue;
        if (!dfn[v]) { tj(v,V.second); low[u] = min(low[u],low[v]); }
        else if (vis[v]) low[u] = min(low[u],dfn[v]);
    }
    if (dfn[u] == low[u]) {
        b[u] = ++ tot, vis[u] = false;
        while (top > 0 && st[top] != u) 
            b[st[top]] = tot, vis[st[top --]] = false;
        top --;
    }
}
int m;
void build() {
    int u,v;
    for (int i = 1;i <= m;i ++) {
        u = b[U[i]], v = b[V[i]];
        if (u == v) continue;
        addEdge(u,v,true);
        addEdge(v,u,true);
    }
}
int ans[maxn],dep[maxn];
void dfs(int u,int fa) {
    dep[u] = dep[fa] + 1; // 顺便计算一下深度，方便后面统计答案
    for (auto v : mp[u]) {
        if (v == fa) continue;
        dfs(v,u); ans[u] += ans[v];
    }
}
int n,p;
int get(int x) { return x > 0 ? 0 : (x == 0 ? 1 : 2); }
int main() {
    scanf("%d%d",&n,&m);
    for (int i = 1,u,v;i <= m;i ++) {
        scanf("%d%d",&u,&v);
        U[i] = u, V[i] = v;
        addEdge(u,v,false,i); 
        addEdge(v,u,false,i);
    }
    for (int i = 1;i <= n;i ++) 
        if (!dfn[i]) tj(i,0);
    build(); scanf("%d",&p);
    for (int i = 1,u,v;i <= p;i ++) {
        scanf("%d%d",&u,&v);
        ans[b[u]] ++; ans[b[v]] --;
    }
    for (int i = 1;i <= tot;i ++) 
        if (!dep[i]) dfs(i,0);
    
    for (int i = 1;i <= m;i ++) {
        int u = b[U[i]], v = b[V[i]];
        if (u == v) putchar('B'); // 在同一个边双内，无法定向
        else if (dep[u] > dep[v]) // u 的深度 > v，说明 v 是 u 的父亲
            printf("%c","RBL"[get(ans[u])]);
        else printf("%c","LBR"[get(ans[v])]); // 反之，u 是 v 的父亲
    }
    return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：2)

[P4652 [CEOI2017] One-Way Streets](https://www.luogu.com.cn/problem/P4652)

基础图论。

题目中是关于无向图边方向的问题，而边双有一个优秀的性质：边双内的任意两点间至少有两条不经过同样的边的路径，因此对于边双内的边无论有没有题目中 $x$ 能走到 $y$ 的限制，它的方向都是不能确定的，因此首先边双缩点把问题转化为树上问题。

对于限制条件，从 $x$ 到 $y$ 的树上路径是唯一的，所以把这些边的方向确定即可。

由于每条边覆盖一次之后就没用了，所以可以使用并查集维护，每次把 $x$ 到 $y$ 路径上的点合并成一个集合，这样总复杂度是 $\mathcal O(n\log n)$ 的，使用按秩合并可以做到 $\mathcal O(n\alpha(n))$。

```cpp
int n,m,q,cnt=1,tot,num,upi[100001],dep[100001],fa[100001],up[100001],chose[100001],c[100001],id[200001],head[100001],dfn[100001],low[100001],to[200001],nex[200001];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
stack<int> st;
pii a[100001];
void tarjan(int k,int from)
{
	st.e(k),low[k]=dfn[k]=++tot;
	for(int i=head[k];i;i=nex[i])
	{
		if(i==(from^1))continue;
		if(!dfn[to[i]])tarjan(to[i],i),low[k]=min(low[k],low[to[i]]);
		else low[k]=min(low[k],dfn[to[i]]);
	}
	if(dfn[k]==low[k])
	{
		int y;++num;
		do c[y=st.top()]=num,st.pop();while(y!=k);
	}
}
void dfs(int k,int fat)
{
	up[k]=fat,dep[k]=dep[fat]+1,fa[k]=k;
	for(int i=head[k];i;i=nex[i])
	{
		if(to[i]==fat){upi[k]=id[i];continue;}
		dfs(to[i],k);
	}
}
inline void mian()
{
	read(n,m);int x,y;
	for(int i=1;i<=m;++i)read(a[i].fi,a[i].se),add(a[i].fi,a[i].se),add(a[i].se,a[i].fi);
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i,0);
	memset(head,0,sizeof(head)),cnt=1;
	for(int i=1;i<=m;++i)if(c[a[i].fi]!=c[a[i].se])add(c[a[i].fi],c[a[i].se]),add(c[a[i].se],c[a[i].fi]),id[cnt^1]=i,id[cnt]=-i;
	for(int i=1;i<=num;++i)if(!fa[i])dfs(i,0);
	read(q);
	while(q--)
	{
		read(x,y),x=c[x],y=c[y];
		while(1)
		{
			x=find(x),y=find(y);
			if(x==y)break;
			if(dep[x]>dep[y])
			{
				if(upi[x]>0)chose[upi[x]]=1;else chose[-upi[x]]=-1;
				fa[x]=up[x];
			}
			else
			{
				if(upi[y]>0)chose[upi[y]]=-1;else chose[-upi[y]]=1;
				fa[y]=up[y];
			}
		}
	}
	for(int i=1;i<=m;++i)if(chose[i]==1)putchar('R');else if(chose[i]==-1)putchar('L');else putchar('B');
}

```

---

## 作者：creation_hy (赞：2)

水题，显然一个环内任意两点都有至少两条路径，所有边方向都不定，于是可以缩点，然后就变成树上问题了。

发现方向是给定的，于是 $x\to lca$ 的边只能向上，$lca\to y$ 的边只能向下。变成维护路径修改，甚至不用树剖，直接树上差分就行了，开两个数组分别记向上和向下的修改的差分值。

注意是无向图，要用割边。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, q, head[N], to[N], nxt[N], val[N], etot;
int dfn[N], low[N], cnt, cut[N], id[N], sz[N], tot;
char ans[N];
inline void link(int u, int v, int w)
{
    to[etot] = v;
    val[etot] = w;
    nxt[etot] = head[u];
    head[u] = etot++;
}
inline void tarjan(int x, int fa)
{
    dfn[x] = low[x] = ++cnt;
    for (int i = head[x]; ~i; i = nxt[i])
        if (!dfn[to[i]])
        {
            tarjan(to[i], x);
            low[x] = min(low[x], low[to[i]]);
            if (low[to[i]] > dfn[x])
                cut[i] = cut[i ^ 1] = 1;
        }
        else if (to[i] != fa)
            low[x] = min(low[x], dfn[to[i]]);
}
inline void dye(int x, int k)
{
    id[x] = k;
    for (int i = head[x]; ~i; i = nxt[i])
        if (!cut[i] && !id[to[i]])
            dye(to[i], k);
}
struct Tree
{
    int head[N], to[N], nxt[N], val[N], etot;
    int g[N][20], dep[N], s1[N], s2[N];
    inline Tree() { memset(head, -1, sizeof(head)); }
    inline void link(int u, int v, int w)
    {
        to[etot] = v;
        val[etot] = w;
        nxt[etot] = head[u];
        head[u] = etot++;
    }
    inline void dfs(int x, int fa)
    {
        dep[x] = dep[g[x][0] = fa] + 1;
        for (int i = 1; i <= 18; i++)
            g[x][i] = g[g[x][i - 1]][i - 1];
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa)
                dfs(to[i], x);
    }
    inline int LCA(int x, int y)
    {
        if (dep[x] < dep[y])
            swap(x, y);
        for (int i = 18; ~i; i--)
            if (dep[g[x][i]] >= dep[y])
                x = g[x][i];
        if (x == y)
            return x;
        for (int i = 18; ~i; i--)
            if (g[x][i] != g[y][i])
                x = g[x][i], y = g[y][i];
        return g[x][0];
    }
    inline void solve(int x, int fa)
    {
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] != fa)
                solve(to[i], x), s1[x] += s1[to[i]], s2[x] += s2[to[i]];
        for (int i = head[x]; ~i; i = nxt[i])
            if (to[i] == fa)
                ans[(val[i] - 1) % m + 1] = s1[x] && val[i] <= m || s2[x] && val[i] > m ? 'R' : (!s1[x] && !s2[x] ? 'B' : 'L');
    }
} G;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, link(u, v, i), link(v, u, i + m);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i, 0);
    for (int i = 1; i <= n; i++)
        if (!id[i])
            dye(i, ++tot);
    for (int x = 1; x <= n; x++)
        for (int i = head[x]; ~i; i = nxt[i])
            if (id[x] != id[to[i]])
                G.link(id[x], id[to[i]], val[i]);
            else
                ans[(val[i] - 1) % m + 1] = 'B';
    for (int i = 1; i <= tot; i++)
        if (!G.g[i][0])
            G.dfs(i, 0);
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y, x = id[x], y = id[y];
        int lca = G.LCA(x, y);
        G.s1[x]++, G.s2[y]++, G.s1[lca]--, G.s2[lca]--;
    }
    for (int i = 1; i <= tot; i++)
        if (!G.g[i][0])
            G.solve(i, 0);
    for (int i = 1; i <= m; i++)
        cout << ans[i];
    cout << '\n';
    return 0;
}
```

---

## 作者：Mr_罗 (赞：1)

介绍一个自然的思路。

首先注意到一个环上的边都不能确定方向，因为无论是顺时针定向 $\circlearrowright$ 还是逆时针定向 $\circlearrowleft$ 都不影响连通性。

无向图中若干环交织在一起构成的结构即为边双，因此把原图所有边双缩点后剩下那些树边才是可能填 `LR` 的边。

> Q：为何边双中每条边都不能确定方向？
>
> A：先把边双定向成强连通分量（任取一棵 dfs 树，将树边都从父到子定向，非树边都从后代到祖先定向，容易证明正确性），再把所有边反向后仍然强连通（强连通图的反图仍然强连通，证明考虑原来 $u\to v$ 的路径现在给 $v\to u$ 用）。

现在考虑树上怎么做。一条路径 $s\to t$ 需要被定向，拆分成 $s\to\operatorname{lca}(s,t)\to t$ 两端。$s$ 向上走到 LCA 的过程表示这条路径定向为子向父，LCA 走下去定向为父到子。用 0/1 分别表示两种方向，树剖搞一下就好了。

时间复杂度 $\mathcal O(n\log^2n)$。虽然不太优，但是稍加更改就可以过 [CF555E](/problem/CF555E)（多写一个查询区间和就好了），这是 [CF555E 的 AC 记录](https://codeforces.com/contest/555/submission/295332550)。

本题代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ul unsigned ll
#define LL __int128_t
#define db double
#define DB long db
#define pii pair<int, int>
#define fi first
#define se second
#define mkpr make_pair
#define vi vector<int>
#define vii vector<pii>
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define bit(x) (1 << (x))
#define bin(s, x) ((s) >> (x) & 1)
#define mem(a, x) memset(a, x, sizeof(a))
#define req(i, l, r) for (int i(l), i##End(r); i < i##End; i = -~i)
#define qer(i, r, l) for (int i(r), i##End(l); i > i##End; i = ~-i)
#define rep(i, l, r) for (int i(l), i##End(r); i <= i##End; i = -~i)
#define per(i, r, l) for (int i(r), i##End(l); i >= i##End; i = ~-i)

#ifdef JYR
#define errs(x) fputs(x, stderr)
#define errm(x, ...) fprintf(stderr, x, ##__VA_ARGS__)
#else
#define errs(x) 0
#define errm(x, ...) 0
#endif

template<typename T, typename U> void chkmx(T &_a, U _b) { if (_a < _b) _a = _b; }
template<typename T, typename U> void chkmn(T &_a, U _b) { if (_a > _b) _a = _b; }

bool Mbe;

// #define MC

#define N 200005
#define mod 998244353
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f

int n, m, q;
vii G[N], H[N];
pii e[N];
int dfn[N], low[N], tot;
int stk[N], top;
int bl[N], tt;
int fa[N], de[N], sz[N], sn[N];
int tp[N], df[N], nf[N], te[N];
int ans[N];

pii add(pii a, pii b) { return mkpr(a.fi + b.fi, a.se + b.se); }

struct SegTree {
    #define lc (i << 1)
    #define rc (lc | 1)

    pii su[N << 2]; // 0: v <- u dn | 1: v -> u up
    int tg[N << 2];

    void psu(int i) { su[i] = add(su[lc], su[rc]); }

    void chg(int i, int k, int l, int r) {
        if (!k) su[i] = mkpr(r - l + 1, 0);
        else su[i] = mkpr(0, r - l + 1);
        tg[i] = k;
    }

    void psd(int i, int l, int d, int r) {
        if (int &k = tg[i]; k != -1) {
            chg(lc, k, l, d);
            chg(rc, k, d + 1, r);
            k = -1;
        }
    }

    void bld(int i = 1, int l = 1, int r = tt) {
        su[i] = mkpr(0, 0), tg[i] = -1;
        if (l == r) return;
        int d = (l + r) >> 1;
        bld(lc, l, d), bld(rc, d + 1, r);
    }

    void mdf(int L, int R, int k, int i = 1, int l = 1, int r = tt) {
        if (L <= l && r <= R) return chg(i, k, l, r);
        int d = (l + r) >> 1; psd(i, l, d, r);
        if (L <= d) mdf(L, R, k, lc, l, d);
        if (d < R) mdf(L, R, k, rc, d + 1, r);
        return psu(i);
    }

    void slv(int i = 1, int l = 1, int r = tt) {
        if (l == r) {
            assert(!su[i].fi || !su[i].se);
            ans[te[nf[l]]] = (su[i].fi ? 0 : (su[i].se ? 1 : -1));
            return;
        }
        int d = (l + r) >> 1; psd(i, l, d, r);
        slv(lc, l, d), slv(rc, d + 1, r);
    }
} T;

void tarjan(int u, int fe) {
    dfn[u] = low[u] = ++tot, stk[++top] = u;
    for (auto [v, i] : G[u]) {
        if (!dfn[v]) tarjan(v, i), chkmn(low[u], low[v]);
        else if (i != fe) chkmn(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v; tt++;
        do {
            v = stk[top--];
            bl[v] = tt;
        } while (v != u);
    }
}

void dfs1(int u, int ft) {
    de[u] = de[fa[u] = ft] + (sz[u] = 1);
    for (auto [v, i] : H[u]) if (v != ft) {
        dfs1(v, u), te[v] = i, sz[u] += sz[v];
        if (sz[sn[u]] < sz[v]) sn[u] = v;
    }
}

void dfs2(int u, int ft) {
    tp[u] = ft, nf[df[u] = ++tot] = u;
    if (!sn[u]) return;
    dfs2(sn[u], ft);
    for (auto [v, i] : H[u]) if (v != fa[u] && v != sn[u]) dfs2(v, v);
}

void mslv() {
    scanf("%d%d", &n, &m);
    rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[i] = mkpr(u, v);
        G[u].eb(v, i), G[v].eb(u, i);
    }
    rep(i, 1, n) if (!dfn[i]) tarjan(i, 0);
    rep(u, 1, n) for (auto [v, i] : G[u])
        if (bl[u] != bl[v]) H[bl[u]].eb(bl[v], i);
    tot = 0;
    rep(i, 1, tt) if (!sz[i]) dfs1(i, 0), dfs2(i, i);
    T.bld();
    scanf("%d", &q);
    while (q--) {
        int u, v, U, V, w;
        scanf("%d%d", &u, &v);
        U = u = bl[u], V = v = bl[v];
        while (tp[u] != tp[v]) {
            if (de[tp[u]] < de[tp[v]]) swap(u, v);
            u = fa[tp[u]];
        }
        w = (de[u] < de[v] ? u : v);
        u = U, v = V;
        while (tp[u] != tp[w]) T.mdf(df[tp[u]], df[u], 1), u = fa[tp[u]];
        if (u != w) T.mdf(df[w] + 1, df[u], 1);
        while (tp[v] != tp[w]) T.mdf(df[tp[v]], df[v], 0), v = fa[tp[v]];
        if (v != w) T.mdf(df[w] + 1, df[v], 0);
    }
    mem(ans, -1), T.slv();
    rep(i, 1, m) {
        if (ans[i] == -1) putchar('B');
        else putchar((de[bl[e[i].fi]] < de[bl[e[i].se]]) ^ ans[i] ? 'R' : 'L');
    }
    puts("");
}

void sprw() {}

void mprw() {}

bool Med;

int main() {
    #ifdef JYR
    freopen("Test.in", "r", stdin);
    freopen("Test.out", "w", stdout);
    #endif
    mprw();
    #ifdef MC
    int _; scanf("%d", &_);
    while (_--) sprw(), mslv();
    #else
    mslv();
    #endif
    errm("%.3lfMB %.0lfms\n", abs(&Med - &Mbe) / 1048576., clock() * 1000. / CLOCKS_PER_SEC);
    return 0;
}
```

---

## 作者：lyxeason (赞：1)

### 题解
可以发现，题目中可以定向的边一定是一个点对 $x_i$ 到 $y_i$ 路径上的必经边，那么题目就转化成给定 $p$ 个点对，求每个点对之间的必经边。

无向图的必经边可以由边双连通分量求出。可以把原图每个边双连通分量缩点成一棵树，树边都是割边。由必经边的定义可知必经边一定是割边。

那么一个点对 $x_i$ 到 $y_i$ 路径上的必经边就是从 $x_i$ 所在的边双连通分量到$y_i$ 所在的边双连通分量的路径上所经过的边。

可以用树上差分的思想来完成这一操作。设点 $i$ 所在的边双连通分量为 $c_i$，并增加一个用来计算答案的点权数组 $a_i$。那么对于一个点对 $x_i$ 到 $y_i$，令 $a_{c_{x_i}}$ 加一，$a_{c_{y_i}}$ 减一。

计算时，从底向上递归，每个点的点权等于自身的权值加上所有子节点的点权。最后如果一个点点权为负则这个点与其父节点的连边方向为从父节点向这个点。如果为正则方向相反。否则如果为 $0$ 则无法确定方向。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lveyvm5k.png)

设 $\operatorname{lca}(x_i,y_i)=p$，可以发现，令 $a_{c_{x_i}}$ 加一，$a_{c_{y_i}}$ 减一后，在递归时，$x_i$ 到 $p$ 路径上的点的点权会加一，$y_i$ 到 $p$ 的路径上的点的点权会减一，而 $p$ 及以上的节点既有 $x_i$ 的加一，又有 $y_i$ 的减一，恰好抵消。这样就实现了 $x_i$ 到 $y_i$ 的路径上的边的标记。

------------
### 代码
###### 代码里有注释

```cpp


#include <cstdio>
#include <cstring>

using namespace std;

struct Graph { //因为缩点需要再开一个图，所以最好把图放在结构体里，方便用
    int h[100009];
    int nxt[200009];
    int to[200009];
    int id[200009];
    int idx;
    inline void Init () {
        idx = 0;
        memset(h, -1, sizeof(h));
    }
    inline void Add (int a, int b, int ii) {
        nxt[idx] = h[a], to[idx] = b, id[idx] = ii, h[a] = idx++;
    }
};

int N;
int M;
int P;
Graph A;
int timestamp;
int dfn[100009];
int low[100009];
int stk[100009];
int tt;
int dcc_cnt;
int cid[100009];
Graph dcc;
int mark[100009];
bool st[100009];
char res[100009];

inline int Min (int a, int b) {
    return a < b ? a : b;
}

void Tarjan (int x, int p) { //Tarjan求边双连通分量
    int v;

    dfn[x] = low[x] = ++timestamp;
    stk[++tt] = x;
    for (int e = A.h[x]; ~e; e = A.nxt[e]) {
        v = A.to[e];
        if (!dfn[v]) {
            Tarjan(v, e);
            low[x] = Min(low[x], low[v]);
        }
        else if (e != (p ^ 1))
            low[x] = Min(low[x], dfn[v]);
    }
    if (dfn[x] == low[x]) {
        dcc_cnt++;
        do {
            v = stk[tt--];
            cid[v] = dcc_cnt;
        } while (v != x);
    }
}

inline int Abs (int x) {
    return x > 0 ? x : -x;
}

void Dfs (int x, int id, int s) { //x表示当前点，id表示从x向x的父节点的边的编号，s表示输入中这条边是从x向父节点(x=-1)还是从父节点向x(x=1)
    int v;

    st[x] = true;
    for (int e = dcc.h[x]; ~e; e = dcc.nxt[e]) {
        v = dcc.to[e];
        if (!st[v]) Dfs(v, Abs(dcc.id[e]), dcc.id[e] > 0 ? 1 : -1), mark[x] += mark[v]; //求点权
    }
    if (mark[x]) res[id] = mark[x] * s < 0 ? 'R' : 'L';
}

int main () {
    int a;
    int b;
    int v;

    A.Init(), dcc.Init();
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d%d", &a, &b);
        A.Add(a, b, i), A.Add(b, a, -i);
    }
    for (int i = 1; i <= N; i++)
        if (!cid[i]) Tarjan(i, 0);
    for (int i = 1; i <= N; i++) {
        for (int e = A.h[i]; ~e; e = A.nxt[e]) {
            v = A.to[e];
            if (cid[i] != cid[v]) dcc.Add(cid[i], cid[v], A.id[e]);
        }
    }
    scanf("%d", &P);
    while (P--) {
        scanf("%d%d", &a, &b);
        mark[cid[a]]++, mark[cid[b]]--; //标记
    }
    for (int i = 1; i <= M; i++) res[i] = 'B'; //注意这里要初始化
    for (int i = 1; i <= N; i++)
        if (!st[i]) Dfs(i, 0, 0);
    printf("%s\n", res + 1);
    return 0;
}
```

---

## 作者：_Anchor (赞：1)

# 前言

介绍一种无需缩点而直接使用 dfs 树的办法，跑得也比较快。

# 题目

[P4652 [CEOI2017]One-Way Streets](https://www.luogu.com.cn/problem/P4652)

![](https://img2020.cnblogs.com/blog/2013965/202109/2013965-20210912220236844-1215430328.png)

# 分析

首先我们可以直接跑出 dfs 树，然后考虑所有的返祖边：

考虑差分来做，因为这时一定会构成环，而环上的边无论朝向哪，环上的点都是可以互相到达的，也就是说，环上点的朝向是无所谓的，也就是都是 $\text{B}$ 类边，我们直接树上差分打 $\text{B}$ 类标记即可。

然后考虑题目的限制，我们直接根据限制给出的条件也一样对 dfs 树上打差分标记，分别是“朝上”和“朝下”标记（注意这里是对一条边的儿子处打标记，同时不是 $\text{L}$ 和 $\text{R}$ 标记而是“朝向标记”）

然后我们再对整个树 dfs 一遍确认树边的方向：

如果已经有了 $\text{B}$ 类标记，那么直接把这条边变成 $\text{B}$ 即可。

对于剩下的情况：

如果有朝上或者朝下的标记，那么就要根据当前边的方向来决定到底是 $\text{L}$ 还是 $\text{R}$ 。

如果什么标记都没有，说明这条边也可以随便标方向，直接标上 $\text{B}$ 即可。

这个做法的复杂度瓶颈在于求 LCA ，也是可以优化到线性的。

这里使用树剖求 LCA ，复杂度 $O(n\log n)$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x){
	x=0;bool f=false;char ch=getchar();
	while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
#define ll long long
#define ull unsigned long long
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define dep(i,y,x) for(int i=(y);i>=(x);i--)
const int N=2e5+5,M=2e5+5,MOD=1e9+7;
int n,m,k;
int head[N],to[N<<1],nex[N<<1],from[N],idx,fre[N],dir[N<<1];
bool vis[N],vis1[N],visi[N<<1];
inline void add(int u,int v,int w){nex[++idx]=head[u];from[idx]=u;to[idx]=v;head[u]=idx;dir[idx]=w;return ;}
int dep[N],fa[N],siz[N],son[N],top[N],tag[N][3];
char Edge[N];
void dfs1(int x,int f){
	dep[x]=dep[f]+1,fa[x]=f,siz[x]=1;
	for(register int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(siz[y]) continue;fre[y]=i;visi[i]=visi[i+(dir[i]==0?1:-1)]=true;
		dfs1(y,x);siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
	return ;
}
void dfs2(int x){
	if(x==son[fa[x]]) top[x]=top[fa[x]];
	else top[x]=x;
	if(son[x]) dfs2(son[x]);
	for(register int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(!top[y]) dfs2(y);
	}
	return ;
}
inline int QueryLca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
inline bool IsTreeEdge(int id){return (fa[to[id]]==from[id])||(to[id]==fa[from[id]]);}
void dfs(int x){
	vis1[x]=true;
	for(register int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(vis1[y]) continue;
		dfs(y);
		tag[x][0]+=tag[y][0],tag[x][1]+=tag[y][1],tag[x][2]+=tag[y][2];
	}
	if(tag[x][0]) Edge[fre[x]]='B';
	else if(tag[x][1]) Edge[fre[x]]=dir[fre[x]]?'R':'L';
	else if(tag[x][2]) Edge[fre[x]]=dir[fre[x]]?'L':'R';
	else Edge[fre[x]]='B';
	return ;
}
signed main(){
	read(n),read(m);
	for(register int i=1,u,v;i<=m;i++) read(u),read(v),add(u,v,0),add(v,u,1);
	for(register int i=1;i<=n;i++) if(!siz[i]) fre[i]=idx+1,dfs1(i,0),dfs2(i);
	for(register int i=1,lca;i<=idx;i++) if(!visi[i]) lca=QueryLca(from[i],to[i]),tag[from[i]][0]++,tag[to[i]][0]++,tag[lca][0]-=2,Edge[i]=(dir[i]?'B':'P');
	read(k);
	for(register int i=1,u,v,lca;i<=k;i++){
		read(u),read(v);lca=QueryLca(u,v);
		tag[u][1]++,tag[v][2]++,tag[lca][1]--,tag[lca][2]--;
	}
	for(register int i=1;i<=n;i++) if(!vis1[i]) dfs(i);
	for(register int i=1;i<=idx;i++) if(Edge[i]=='B'||Edge[i]=='L'||Edge[i]=='R') putchar(Edge[i]);
	return 0;
}
/*
*/
```


---

## 作者：Elma_ (赞：1)

教练模拟赛的 T3，赛时无人 AC。

首先我们注意到，在一个 E-DCC 内，因为任意两个点之间都至少有两条边不相交的路径，因此 E-DCC 内的所有边方向都不定。于是我们可以用并查集缩点求 E-DCC，因为原图不保证联通，所以缩完点之后得到的新图是一个森林。

然后考虑 $p$ 条 $u \to v$ 的限制：

- 如果 $u,v$ 在同一个 E-DCC 内，那么可以直接忽略这条限制；
- 如果 $u,v$ 不在同一个 E-DCC 内，设 $u$ 所在的 E-DCC 为 $x$，$v$ 所在的 E-DCC 为 $y$，那么对于 $x\to y$ 在新图中树上的路径，我们可以同时维护一个上行标记和一个下行标记，最后再 dfs 一遍求出答案。

具体如何维护这两个标记呢？我们可以在新图中树上倍增搞出 $x,y$ 的 LCA，设这个点为 $q$，那么一条 $x \to y$ 的路径实际上可以被拆成一条 $x \to q$ 的上行路径和一条 $q \to y$ 的下行路径，用差分分别给这两条路径打上上行标记和下行标记即可。

然后要注意的是最后 dfs 的时候一条 $u \to v$ 的路径应该根据 $v$ 上的标记定向而不是 $u$ 上的标记定向。建图的时候有一个小 trick，对于每一条边把正边（为了方便，默认 $a_i \to b_i$ 为正边）的编号标为正数，反边的编号标为负数，如果反边定了某一个方向，那么正边就定和反边相反的方向。

代码比较简洁，但是因为本人太菜所以调了八千万年。顺带一提，这题难度绝对不到黑。

```cpp
#include <cmath>
#include <queue>
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

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;

inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int n, m, q, fat[maxn];
inline int find(int x) {
	return fat[x] == x ? x : fat[x] = find(fat[x]);
}

struct node {
	int nxt, to, col;
}edge[maxn << 1];
int head[maxn], tot = 1, top, dfn[maxn], low[maxn];
int tim, sta[maxn];
inline void addedge(int u, int v, int col) {
	edge[++tot] = (node){head[u], v, col}, head[u] = tot;
}
inline void tarjan(int u, int fath) {
	dfn[u] = low[u] = ++tim;
	sta[++top] = u;
	for (int i = head[u];i;i = edge[i].nxt) {
		int v = edge[i].to;
		if ((i ^ 1) == fath) continue;
		if (!dfn[v]) {
			tarjan(v, i), low[u] = min(low[u], low[v]); 
		} else low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		do {
			int x = find(u), y = find(sta[top]);
			if (x != y) fat[x] = y; 
		} while (sta[top--] != u);
	}
}

struct node2 {
	int nxt, to, col;
}edge2[maxn << 1];
int tot2, head2[maxn], dep[maxn], fa[maxn][25];
inline void addedge2(int u, int v, int col) {
	edge2[++tot2] = (node2){head2[u], v, col}, head2[u] = tot2;
} 
inline void dfs(int u) {
	for (int i = 0;fa[u][i];i++)
		fa[u][i + 1] = fa[fa[u][i]][i];
	for (int i = head2[u];i;i = edge2[i].nxt) {
		int v = edge2[i].to;
		if (v == fa[u][0]) continue;
		dep[v] = dep[u] + 1, fa[v][0] = u;
		dfs(v);
	}
}
inline int getlca(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 20;i >= 0;i--)
		if(dep[u] <= dep[v] - (1 << i)) v = fa[v][i];
	if(u == v) return u;
	for(int i = 20;i >= 0;i--)
		if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

char ans[maxn];
int up[maxn], down[maxn], vis[maxn];
inline void solve(int u) {
	vis[u] = 1;
	for (int i = head2[u];i;i = edge2[i].nxt) {
		int v = edge2[i].to;
		if (v == fa[u][0]) continue;
		solve(v), up[u] += up[v], down[u] += down[v];
		int col = edge2[i].col;
		if (up[v]) ans[abs(col)] = (col > 0 ? 'L' : 'R');
		if (down[v]) ans[abs(col)] = (col > 0 ? 'R' : 'L');
	}
}

inline void init() {
	tot = 1; tot2 = top = 0;
	memset(edge, 0, sizeof(edge));
	memset(edge2, 0, sizeof(edge2));
	memset(head, 0, sizeof(head));
	memset(head2, 0, sizeof(head2));
	memset(vis, 0, sizeof(vis));
	memset(up, 0, sizeof(up));
	memset(down, 0, sizeof(down));
	memset(fa, 0, sizeof(fa));
}

int main(void) {
	while (~scanf("%d %d", &n, &m)) { init();
		for (int i = 1;i <= n;i++) fat[i] = i;
		for (int i = 1;i <= m;i++) {
			int u = read(), v = read(); ans[i] = 'B';
			addedge(u, v, i), addedge(v, u, -i);
		}
		for (int i = 1;i <= n;i++) if (!dfn[i]) tarjan(i, 0);
		for (int i = 1;i <= n;i++) {
			for (int j = head[i];j;j = edge[j].nxt) {
				int u = find(i), v = find(edge[j].to);
				if (u != v) addedge2(u, v, edge[j].col);
			}
		}
		for (int i = 1;i <= n;i++) if (!dep[i]) dep[i] = 1, dfs(i);
		q = read();
		for (int i = 1;i <= q;i++) {
			int u = read(), v = read();
			if ((u = find(u)) == (v = find(v))) continue;
			int lca = getlca(u, v); 
			up[u]++, up[lca]--, down[v]++, down[lca]--;
		}
		for (int i = 1;i <= n;i++) if (!vis[i]) solve(i);
		puts(ans + 1);
	}
	return 0;
}
```


---

## 作者：_anll_ (赞：0)

## 大体思路
一个很显然的结论：如果形成了一个边双联通，那么在这里面的所有边都可以取任意方向。证明也很简单：在一个边双里，$a,b,c$ 相互连边，要使他们相互可达可以是 $a\rightarrow b$，$b\rightarrow c$，$c\rightarrow a$，当然也可以反过来，$a\leftarrow b$，$b \leftarrow c$，$c \leftarrow a$。于是你发现对于一条边而言方向是没有硬性要求的。

于是自然而然地想到了将边双联通分量缩成一个点，缩完后就会变成一棵树。我们考虑一对 $(x,y)$ 会将哪些树边确定。令 $lca$ 表示 $x$ 和 $y$ 的最近公共祖先，则 $x$ 到 $lca$ 的路径上的所有边都被确定从下往上，$y$ 到 $lca$ 的路径上的所有边都被确定从上往下。

容易想到树上差分。化边权为点权，定义 $up[i]$ 为 $i$ 到 $fas[i]$ 的那条边向上的权值，每轮操作显然是 $up[x]+1$，$up[lca]-1$。$down$ 数组同理可得。最后跑 dfs 统计即可。

需要注意本题不保证原图联通。

## 代码演示
```cpp
#include<map>
#include<cstring>
#include<iostream>
#define endl '\n'
using namespace std;
const int N=1e5+5;
struct Edge{
	int l,nxt;
}edges[N<<1];
int n,m,q,tt=1,head[N];
int tot,dfn[N],low[N];
int top,stk[N],instk[N];
int cnt,edcc[N],edcs[N];
int fas[N],dep[N],siz[N],son[N],topp[N];
int up[N],down[N],vu[N],vv[N];
char ans[N];
pair<int,int> po[N];
map<pair<int,int>,int> mo; 
void add_edge(int f,int l){
	edges[++tt]={l,head[f]};
	head[f]=tt;
}
void tarjan(int x,int las){
	dfn[x]=low[x]=++tot;
	stk[++top]=x;instk[x]=1;
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;
		if(!low[l]){
			tarjan(l,i);
			low[x]=min(low[x],low[l]);
		}
		if(instk[l]&&(i^las)!=1)
			low[x]=min(low[x],dfn[l]);
	}
	if(low[x]==dfn[x]){
		int y;cnt++;
		do{
			y=stk[top--];instk[y]=0;
			edcc[y]=cnt,edcs[cnt]++;
		}while(y!=x);
	}
}
void dfs1(int x,int fa){
	fas[x]=fa,dep[x]=dep[fa]+1,siz[x]=vv[x]=1;
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;if(l==fa) continue;
		dfs1(l,x);siz[x]+=siz[l];
		if(siz[l]>siz[son[x]]) son[x]=l;
	}
}
void dfs2(int x,int tot){
	topp[x]=tot;
	if(!son[x]) return;dfs2(son[x],tot);
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;
		if(l!=fas[x]&&l!=son[x]) dfs2(l,l);
	}
}
int LCA(int x,int y){
	while(topp[x]!=topp[y]){
		if(dep[topp[x]]<dep[topp[y]]) swap(x,y);
		x=fas[topp[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int dfsu(int x,int fa){
	vu[x]=1;int an=0;
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;
		if(l!=fa) an+=dfsu(l,x);
	}
	an+=up[x];
	if(an){
		int a=mo[{x,fas[x]}];
		a>0?ans[a]='R':ans[-a]='L';
	}
	return an;
}
int dfsd(int x,int fa){
	vu[x]=1;int an=0;
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;
		if(l!=fas[x]) an+=dfsd(l,x);
	}
	an+=down[x];
	if(an){
		int a=mo[{fas[x],x}];
		a>0?ans[a]='R':ans[-a]='L';
	}
	return an;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;int f,l;
	for(int i=1;i<=m;i++){
		cin>>f>>l;po[i]={f,l};
		add_edge(f,l);add_edge(l,f);
	}
	for(int i=1;i<=n;i++) if(!low[i]) tarjan(i,0);
	memset(edges,0,sizeof(edges));
	memset(head,0,sizeof(head));tt=1;
	for(int i=1;i<=m;i++){
		f=po[i].first,l=po[i].second;
		if(edcc[f]!=edcc[l]){
			add_edge(edcc[f],edcc[l]);
			add_edge(edcc[l],edcc[f]);
			mo[{edcc[f],edcc[l]}]=i;
			mo[{edcc[l],edcc[f]}]=-i;
		}
		else ans[i]='B';
	}
	for(int i=1;i<=m;i++) if(!vv[i]) dfs1(i,0),dfs2(i,i);
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>f>>l;f=edcc[f],l=edcc[l];
		int lca=LCA(f,l);
		up[f]++,up[lca]--;
		down[l]++,down[lca]--;
	}
	for(int i=1;i<=cnt;i++) if(!vu[i]) dfsu(i,0),dfsd(i,0);
	for(int i=1;i<=m;i++){
		if(!ans[i]) ans[i]='B';
		cout<<ans[i];
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P4652)

------------
# 思路：
首先任意环上的边一定不是必经边，答案为 ```B```。我们随便搞一颗原图的 ```dfs``` 树，那么非树边，和每条飞树边覆盖的树上的链都是 ```B```。在树上打链覆盖的标记即可。

然后是对于每个 $x$ 到 $y$ 有路的限制，我们直接在 $x$ 至 $lca$ 打向上走的标记，$lca$ 至 $y$ 打向下走的标记，最后判断一下就好了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
struct Edge{
    int x,y;
}Es[N],queB[N];
int n,m,Q,tmplen,tagB[N],tagL[N],tagR[N],ans[N],fa_id[N],fir[N],nxt[N],son[N],id[N],tot,dep[N],anc[N][20];
bool in_t[N],vis_e[N],vis[N],is_rt[N];
void add(int x,int y,int z){
    son[++tot]=y; 
	id[tot]=z; 
	nxt[tot]=fir[x]; 
	fir[x]=tot;
}
void dfs1(int x){
    vis[x]=true;
    for(int j=fir[x];j;j=nxt[j]){
		if(!vis_e[id[j]]){
	        vis_e[id[j]]=true;
	        if(!vis[son[j]]){
				fa_id[son[j]]=id[j];
				in_t[id[j]]=true;
				dfs1(son[j]); 
			}else{
	            ans[id[j]]='B';
	            queB[++tmplen].x=x;
				queB[tmplen].y=son[j];
	        }
	    }
	}
}
void dfs_info(int x,int pre){
    anc[x][0]=pre; 
	for(int i=1;i<=18;i++){
		anc[x][i]=anc[anc[x][i-1]][i-1];
	}
    for(int j=fir[x];j;j=nxt[j]){
		if(in_t[id[j]]&&son[j]!=pre){
			dep[son[j]]=dep[x]+1;
			dfs_info(son[j],x);
		}
	}
}
int LCA(int x,int y){
    if(dep[x]<dep[y]){
		swap(x,y);
	}
    for(int i=18;i>=0;i--){
		if(dep[anc[x][i]]>=dep[y]){
			x=anc[x][i];
		}
	}
    if(x==y){
		return x;
	}
    for(int i=18;i>=0;i--){
		if(anc[x][i]!=anc[y][i]){
			x=anc[x][i];
			y=anc[y][i];
		}
	}
    return anc[x][0];
}
void dfs(int x,int pre){
    for(int j=fir[x];j;j=nxt[j]){
		if(in_t[id[j]]&&son[j]!=pre){
			dfs(son[j],x); 
			tagB[x]+=tagB[son[j]]; 
			tagL[x]+=tagL[son[j]]; 
			tagR[x]+=tagR[son[j]];
		}
	}
    if(tagB[x]){
		ans[fa_id[x]]='B';
	}else if(tagR[x]){
		ans[fa_id[x]]=Es[fa_id[x]].x==x?'R':'L';
	}else if(tagL[x]){
		ans[fa_id[x]]=Es[fa_id[x]].y==x?'R':'L';
	}else{
		ans[fa_id[x]]='B';
	}
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>Es[i].x>>Es[i].y;
        add(Es[i].x,Es[i].y,i); 
		add(Es[i].y,Es[i].x,i);
    }
    for(int i=1;i<=n;i++){
		if(!vis[i]){
			is_rt[i]=true;
			dfs1(i);
			dfs_info(i,i);
		}
	}
    for(int i=1;i<=tmplen;i++){
		tagB[queB[i].x]++;
		tagB[queB[i].y]++;
		tagB[LCA(queB[i].x,queB[i].y)]-=2;
	}
    cin>>Q;
    for(int i=1,x,y,_lca;i<=Q;i++){
        cin>>x>>y; 
		_lca=LCA(x,y);
        tagR[x]++; 
		tagR[_lca]--;
        tagL[y]++; 
		tagL[_lca]--;
    }
    for(int i=1;i<=n;i++){
		if(is_rt[i]){
			dfs(i,i);
		}
	}
    for(int i=1;i<=m;i++){
		putchar(ans[i]);
	}
    return 0;
}
```
完结撒花~

---

## 作者：james1BadCreeper (赞：0)

首先一个边双内部内部肯定无法确定（完全可以所有边都反向），我们只需要判断割边。

边双缩点建立出树，一个限制 $u\rightarrow v$ 表示强制钦定这条链上的方向。由于一定有解，因此直接使用树上差分维护，根据在树上较深的那个点的正负确定边的方向即可，具体见代码。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5; 

int n, m, q; 
vector<pair<int, int>> G[N]; 
bool bri[N]; 

int dfn[N], low[N], num, col[N], st[N], tot, cnt; 
void tarjan(int x, int in_edge) {
    dfn[x] = low[x] = ++num; st[++tot] = x; 
    for (auto [y, id] : G[x]) 
        if (!dfn[y]) {
            tarjan(y, id), low[x] = min(low[x], low[y]); 
            if (dfn[x] < low[y]) bri[id] = 1; 
        } else if (id != in_edge) low[x] = min(low[x], dfn[y]); 
    if (dfn[x] == low[x]) {
        int y; ++cnt; 
        do col[y = st[tot--]] = cnt; while (x != y); 
    }
}

vector<int> E[N]; 
bool vis[N]; 
int d[N], dep[N]; 
void dfs(int x, int ff) {
    vis[x] = 1; dep[x] = dep[ff] + 1; 
    for (int y : E[x]) if (y != ff) dfs(y, x), d[x] += d[y]; 
}

int u[N], v[N]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> m; 
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v; ::u[i] = u, ::v[i] = v; 
        G[u].emplace_back(v, i); G[v].emplace_back(u, i); 
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i, 0); 
    for (int u = 1; u <= n; ++u) for (auto [v, id] : G[u]) if (col[u] != col[v])
        E[col[u]].emplace_back(col[v]); 
    
    cin >> q; 
    while (q--) {
        int x, y; cin >> x >> y; // x -> y
        x = col[x]; y = col[y]; 
        if (x != y) ++d[x], --d[y]; 
    }
    
    for (int i = 1; i <= cnt; ++i) if (!vis[i]) dfs(i, 0); 

    for (int i = 1; i <= m; ++i)
        if (!bri[i]) cout << "B"; 
        else {
            if (dep[col[u[i]]] > dep[col[v[i]]]) {
                if (d[col[u[i]]] > 0) cout << "R";
                else if (d[col[u[i]]] == 0) cout << "B"; 
                else cout << "L"; 
            } else {
                if (d[col[v[i]]] > 0) cout << "L"; 
                else if (d[col[v[i]]] == 0) cout << "B"; 
                else cout << "R"; 
            }
        }
    cout << "\n"; 
    return 0;
}
```

---

## 作者：rq_kyz (赞：0)

# 【题解】 P4652 [CEOI2017] One-Way Streets

### 传送门

[P4652 [CEOI2017] One-Way Streets](https://www.luogu.com.cn/problem/P4652)

---

### 题意

有一张 $n$ 个点、$m$ 条边的无向图，有 $p$ 个限制条件 $(x,y)$，表示点 $x$ 可以走到点 $y$，问能否给图中的每条边定向，若可以，则是哪个方向。

---

### 分析

楼上很多大佬都是用的树上差分做法，这里来搞一个并差集做法。

我们发现，限制条件 $(x,y)$ 只会影响桥（割边），对于不是桥的边，一定有一种方案不走这条边，也就是说，不是桥的边一定不定向。

这样我们的思路就比较清晰了，首先通过边双缩点，缩完的图一定是一棵树，保留下来的边一定都是桥。现在我们考虑如何在树上将 $x$ 到 $y$ 的路径上的所有边全部更新方向。

那么接下来应该怎么做呢？暴力更新是 $O(n^2)$，肯定不行。我们注意到，一条边只会被更新一次，如果有很多次更新，那也只有第一次是有效的。所以我们可以使用并差集进行维护。

并差集维护点，如果 $fa-u$ 的这条边已经被更新，则将这两个点放入同一个并差集中，注意这里需要**将 $u$ 的并差集父亲设为 $fa$**，不能反过来。因为这样的话我们就可以通过并差集向上快速跳跃，跃过那些已经更新过的边，从而降低时间复杂度。

另外，~~据说本题还可以用树链剖分~~，奈何作者码力太蒻，就不给大家展示了。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll last[100001];//链式前向星
struct s1{
	ll t,to;
}nxet[200001];
ll cd=0;
void lj(ll x,ll y){
	nxet[cd].t=last[x];
	nxet[cd].to=y;
	last[x]=cd;
	cd++;
}
struct s2{//记录边
	ll x,y;
}b[100001];
ll cnt=0,dfn[100001],low[100001];
stack<ll> sta;
ll sc=0,belong[100001],sz[100001];
vector<ll> scc[100001];
void Tarjan(ll u,ll pre){//Tarjan求边双
	dfn[u]=low[u]=++cnt;
	sta.push(u);
	for(ll j=last[u];~j;j=nxet[j].t){
		ll v=nxet[j].to;
		if(j==(pre^1))
			continue;
		if(!dfn[v]){
			Tarjan(v,j);
			low[u]=min(low[u],low[v]);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		sc++;
		while(1){
			ll x=sta.top();
			sta.pop();
			belong[x]=sc;
			sz[sc]++;
			scc[sc].push_back(x);
			if(x==u)
				break;
		}
	}
}
ll fa[100001],depth[100001];
void dfs(ll u){//dfs求出每个点的father和depth
	depth[u]=depth[fa[u]]+1;
	for(ll j=last[u];~j;j=nxet[j].t){
		ll v=nxet[j].to;
		if(v!=fa[u]){
			fa[v]=u;
			dfs(v);
		}
	}
}
ll bcj[100001];//并差集
void init(ll n){
	for(ll i=1;i<=n;i++)
		bcj[i]=i;
}
ll getfather(ll x){
	if(x==bcj[x])
		return x;
	return bcj[x]=getfather(bcj[x]);
}
ll ans[100001];//记录边的方向，一条边用它下方的点u表示，1表示从u到fa，-1表示从fa到u，0表示还没有更新
void add(ll u,ll v){//修改函数
	u=getfather(u);
	v=getfather(v);
	ll k=1;
	while(u!=v){
		if(depth[u]<depth[v]){
			u^=v^=u^=v;
			k=-k;
		}
		ans[u]=k;
		bcj[u]=getfather(fa[u]);
		u=bcj[u];//向上跳跃
	}
}
int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	memset(last,-1,sizeof(last));
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld",&b[i].x,&b[i].y);
		lj(b[i].x,b[i].y);
		lj(b[i].y,b[i].x);
	}
	for(ll i=1;i<=n;i++)//边双缩点
		if(!dfn[i])
			Tarjan(i,-1);
	memset(last,-1,sizeof(last));//没用的空间回收再利用
	cd=0;
	for(ll i=1;i<=m;i++){
		ll x=b[i].x,y=b[i].y;
		if(belong[x]!=belong[y]){//在新图中建边
			lj(belong[x],belong[y]);
			lj(belong[y],belong[x]);
		}
	}
	for(ll i=1;i<=sc;i++)//dfs遍历树
		if(!depth[i])
			dfs(i);
	init(sc);//并差集初始化
	ll q;
	scanf("%lld",&q);
	while(q--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		add(belong[x],belong[y]);//更新
	}
	for(ll i=1;i<=m;i++){
		ll x=b[i].x,y=b[i].y;
		if(belong[x]==belong[y])//不是桥
			printf("B");
		else if(fa[belong[y]]==belong[x])//是桥，输入方向为从上到下
			printf("%c",!ans[belong[y]]?'B':(ans[belong[y]]<0?'R':'L'));
		else//是桥，输入方向为从下到上
			printf("%c",!ans[belong[x]]?'B':(ans[belong[x]]>0?'R':'L'));
	}
	return 0;
}
```

---

