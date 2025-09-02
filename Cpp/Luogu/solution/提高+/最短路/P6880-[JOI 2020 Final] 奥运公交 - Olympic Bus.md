# [JOI 2020 Final] 奥运公交 / Olympic Bus

## 题目描述

给定一个 $N$ 点 $M$ 边的有向图，每条边从 $U_i$ 指向 $V_i$，经过这条边的代价为 $C_i$。

点编号为 $1$ 到 $N$。

我们可以翻转一条边，即让他从 $U_i$ 指向 $V_i$ 变为从 $V_i$ 指向 $U_i$，这时会有 $D_i$ 的代价产生。

你要从点 $1$ 到点 $N$，再从点 $N$ 回到点 $1$，你想知道，通过翻转一条边，或者不翻转，能得到的最小代价和为多少？

## 说明/提示

### 样例 1 解释

最优解为翻转第二条边，总代价为：

- 翻转的代价 $1$。
- 从点 $1$ 到点 $N$ 再返回的最短路径 $1 \to 2 \to 4 \to 3 \to 1$，代价为 $4+2+1+2=9$。

### 样例 4 解释

不一定需要翻转某条边。

### 样例 5 解释

从点 $4$ 到点 $3$ 的边有两条。

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$M \le 1000$。
- Subtask 2（11 pts）：$M$ 为偶数，且 $U_{2i}=U_{2i-1}$，$V_{2i}=V_{2i-1}$，$C_{2i}=C_{2i-1}$。
- Subtask 3（21 pts）：$C_i=0$。
- Subtask 4（63 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $2 \le N \le 200$。
- $1 \le M \le 5 \times 10^4$。
- $1 \le U_i \le N$。
- $1 \le V_i \le N$。
- $U_i \ne V_i$。
- $0 \le C_i \le 10^6$。
- $0 \le D_i \le 10^9$。

### 说明

翻译自 [第 19 回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [D オリンピックバス](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t4.pdf)。

## 样例 #1

### 输入

```
4 5
1 2 4 4
1 3 2 1
4 3 1 2
4 1 6 1
2 4 2 5```

### 输出

```
10```

## 样例 #2

### 输入

```
4 10
1 2 4 4
1 2 4 4
1 3 2 1
1 3 2 1
4 3 1 2
4 3 1 2
4 1 6 1
4 1 6 1
2 4 2 5
2 4 2 5```

### 输出

```
10```

## 样例 #3

### 输入

```
4 4
1 2 0 4
1 3 0 1
4 3 0 2
4 1 0 1```

### 输出

```
2```

## 样例 #4

### 输入

```
4 5
1 2 4 4
1 3 2 4
4 3 1 5
4 1 6 1
2 4 2 5```

### 输出

```
12```

## 样例 #5

### 输入

```
4 5
2 1 4 4
1 3 2 1
4 3 1 2
4 3 6 1
2 4 2 5```

### 输出

```
-1```

# 题解

## 作者：dingcx (赞：27)

这里给出一篇更为通俗易懂的题解，算是对其它题解的补充说明吧。

## 思路

如果暴力枚举翻转每条边，每个进行一遍 ```dijkstra```，复杂度 $O(n^2m)$，需要优化。

本题的优化方法是减少 ```dij``` 的使用次数。因为许多边的翻转其实不影响最短路的长度，此时就不需要再调用 ```dij``` 求一边长度了，可以节省时间。

那么边可以分为两类，一种边翻转后对最短路长度产生影响，称为“关键边”，否则不产生影响就不是关键边。

对于每个关键边，需要修改一下边并重新调用 ```dij``` 计算最短路，因为 ```dij``` 是 $n^2$ 的，所以关键边的个数需要限制到 $O(n)$ 级别；对于非关键边，因为有 $m$ 条，需要在 $O(n)$ 内求出路径长度，当然~~这道题比较神奇~~，可以 $O(1)$ 就求出。

考虑如何处理非关键边，这里直接上结论：选择翻转边 $(u,v)$ 的最终代价为 $D+\min(dis(1,n),dis(1,v)+C+dis(u,n))+\min(dis(n,1),dis(n,v)+C+dis(u,1))$。（$dis(u,v)$ 就是 $u \to v$ 的最短距离）

下面说明为什么这个结论是对的。（这里也是其它题解可能讲的不是很清楚的地方，当然这里确实不好说，因为关键边和非关键边是~~相互依存相互促进的~~，接下来这一大段话也会顺便讲掉如何处理关键边。）

首先需要给出关键边的定义（上面的那个不是定义，只是一个大概的理解）：在 $1\to i,i \to n,n \to i,i \to 1 (1 \le i \le n)$ 的其中一个的最短路径上的边。

容易发现，从一个定点出发（或一个定点结束）到其它每个点的最短路径构成一棵树（如果有两条长度相同的就随便选一条），这样关键路径的条数就是上面这 $4$ 棵最短路径树上的边，是 $O(n)$ 级别，满足要求。

有了定义，再回头看那个式子，这里就只看 $1 \to n$ 了，因为 $n \to 1$ 也同理。翻转边 $(u,v)$ 后 $1 \to n$ 代价是 $\min(dis(1,n),dis(1,v)+C+dis(u,n))$。

证明这个是对的，其实就需要两步：为什么能取到，为什么是最小的。式子中的 $dis(1,n)$ 就是选择不经过 $(u,v)$ 的翻转边，（这里可能有人会问，为什么不经过这条边还要翻转，原因是可能去的时候不经过，回来的时候就需要经过了。）因为 $(u,v)$ 不是关键边，所以 $dis(1,n)$ 不会改变，可以直接用；式子中的 $dis(1,v)+C+dis(u,n)$ 就是选择经过 $(u,v)$ 的翻转边，因为不是关键边，翻转 $(u,v)$ 不会改变 $1$ 到任何点、任何点到 $n$ 的最短路径长度，所以 $dis(1,v),dis(u,n)$ 不会改变，然后因为要经过这条边，所以一定是先最短路径走到 $v$，再用这条边到 $u$，然后走最短路径到 $n$。以上两种情况（走与不走翻转边）包含了所有情况，而它们各自是自己情况的最小，所以它们的较小值就是最终的最小值。

有了这样的结论，只需要先预处理出 $dis(1,i),dis(i,n),dis(n,i),dis(i,1)$，便可以 $O(1)$ 计算翻转非关键边的答案。

至此，我们分当前翻转的边是不是关键边两种情况进行了处理，这道题也就大功告成了，总复杂度 $O(n^3+m)$。

### 写法的技巧和细节

这道题的代码并不好写，~~不然我也不至于调 2h~~，于是在这里总结了一些写法上的小技巧和容易出错的细节。

```dij``` 不要用优先队列优化，那样是 $m \log n$，不如暴力的 $n^2$。同时别用邻接表，用邻接矩阵，方便翻转边。

关键边的求法：把每个点**最终**的 $dis$ 是从哪条边转移过来的记录一下，这些边就是关键边。

如何求 $dis(i,n),dis(i,1)$：建立反图，就可以以 $n,1$ 为起点求了。不过因为这道题是邻接矩阵，方便操作，也可以在 ```dij``` 中做手脚，详细可以看下面的代码。

如何处理重边：邻接矩阵是显示不出来重边的，所以在求邻接矩阵时，需要保留边权最小的边，不过这还没完，因为边权最小的边可能被翻转掉，所以还需要记录边权第二小的边，这样可以在边权最小的边翻转后暂时顶替它的位置。但处理重边需要注意，边权大的边只能在邻接矩阵中被忽略，但也需要被存起来，因为这条边的 $D$ 可能很小，把这条边翻转得到的答案可能更优，也就是说在翻转边的时候这条边也需要被考虑进来。

以上细节可能不全，那下面的代码和注释应该能解决你的所有疑惑。

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=210,MAXM=5e4+10;
int n,m,from[MAXN]; //from[i] 表示最终的 dis[i] 是从哪条边转移来的
ll c[MAXN][MAXN],c2[MAXN][MAXN]; //邻接矩阵的最小值和次小值
ll dist[4][MAXN],tdis[MAXN]; //dist[0,1,2,3] 分别是 1->i,i->n,n->i,i->1 的最短距离
bool vis[MAXN],key[MAXN][MAXN],used[MAXN][MAXN]; //key 记录关键边
struct Edge{
	int u,v;ll C,D;
}e[MAXM];
int read(){
	int num=0,sign=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	return num*sign;
}
void dij(int st,ll *dis,int op){ //op=0 是正图，op=1 是反图，op=2 表示翻转一条边的正图
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=n;i++) dis[i]=2e18;
	dis[st]=0;
	while(1){
		int u=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&dis[u]>dis[i]) u=i;
		if(!u) break;
		vis[u]=1;
		for(int i=1;i<=n;i++){
			ll w=(op==1)?c[i][u]:c[u][i]; //处理正图和反图
			if(!vis[i]&&dis[u]+w<dis[i]){
				dis[i]=dis[u]+w;
				if(op<2) from[i]=u; //记录当前转移来的边，但这未必是最终的
			}
		}
	}
	if(op<2) for(int i=1;i<=n;i++) key[from[i]][i]=1; //记录关键边
}
int main(){
	n=read(),m=read();
	memset(c,0x3f,sizeof(c)),memset(c2,0x3f,sizeof(c2));
	for(int i=1;i<=n;i++) c[i][i]=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),C=read(),D=read();
		e[i].u=u,e[i].v=v,e[i].C=C,e[i].D=D;
		if(c[u][v]>C) c2[u][v]=c[u][v],c[u][v]=C; //更新邻接矩阵最大值和次大值
		else if(c2[u][v]>C) c2[u][v]=C; //更新次大值
	}
	dij(n,dist[1],1),dij(1,dist[3],1); //预处理 4 个最短路
	dij(1,dist[0],0),dij(n,dist[2],0);
	ll ans=dist[0][n]+dist[2][1]; //不翻转边
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v;ll C=e[i].C,D=e[i].D;
		if(key[u][v]&&C==c[u][v]&&!used[u][v]){ //是关键边
			ll tmpu=c[u][v],tmpv=c[v][u];
			c[v][u]=min(c[v][u],C); //翻转边 (u,v)
			c[u][v]=(c[u][v]==C)?c2[u][v]:c[u][v]; //如果最小边被翻转，次小边顶替
			ll sum=D;
			dij(1,tdis,2);sum+=tdis[n]; //重算距离
			dij(n,tdis,2);sum+=tdis[1];
			ans=min(ans,sum); //更新答案
			c[u][v]=tmpu,c[v][u]=tmpv; //回溯
			used[u][v]=1;
		}
		else ans=min(ans,(ll)D+
			min(dist[0][n],dist[0][v]+C+dist[1][u])+
			min(dist[2][1],dist[2][v]+C+dist[3][u])); //套公式
	}
	printf("%lld\n",(ans>=1e18)?-1:ans);
	return 0; //华丽结束
}
```
不要忘记点赞~

---

## 作者：xtx1092515503 (赞：23)

因为 $m$ 在可以枚举的范围内，我们考虑枚举 $m$，计算每次翻转完该边后新的 $1\rightarrow n$ 和 $n\rightarrow1$ 的最短路。

以求出翻转后 $1\rightarrow n$ 的最短路为例。设我们当前枚举了某条边 $(u,v,w)$。明显，如果该边不在以 $1$ 为根的最短路径DAG上。则任意一条从 $1$ 出发的最短路径都不可能经过它，故此时可以直接用 $1\rightarrow n$ 作为最短路。当然，我们也不能忽略翻转后的边，故其应该与 $(1\rightarrow v)+w+(u\rightarrow n)$ 取 $\min$。

那么如果该点在最短路径DAG上呢？明显此时就有路径经过它了。但是，我们此时可以直接翻转边后暴力跑Dijkstra——因为，最短路径DAG是可以被缩点的，在缩点过程中被缩掉的边就算被删去，也可以找到另外的路径去替代它。当然，你是没有必要再去写个缩点的——直接对DAG求出任意一棵生成树即可。则此时就出现一棵最短路径树，其边数是 $O(n)$ 的。我们对每条最短路径树上的边都跑一遍 Dijkstra，总复杂度是 $O(n^3)$ 的。（因为本图是稠密图，故直接上 $O(n^2)$ 的无堆优化Dijkstra即可）

可以初始使用Dijkstra预处理出来所有的 $1\rightarrow x,n\rightarrow x,x\rightarrow1,x\rightarrow n$ 来达到 $O(1)$ 计算翻转后边的贡献。

则总复杂度 $O(m+n^3)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=0x0f0f0f0f0f0f0f0f;
int n,m,g[210][210],h[210][210],f[210][210];
bool vis[210];
void Dijkstra(int S,int *dis,int *fa){
	for(int i=0;i<=n;i++)dis[i]=inf,vis[i]=false;
	dis[S]=0;
	while(true){
		int x=0;
		for(int i=1;i<=n;i++)if(!vis[i]&&dis[i]<dis[x])x=i;
		if(!x)break;
		vis[x]=true;
		for(int y=1;y<=n;y++)if(dis[y]>dis[x]+g[x][y])dis[y]=dis[x]+g[x][y],fa[y]=x;
	}
//	for(int i=1;i<=n;i++)printf("%d ",dis[i]);puts("");
}
int dis1[210],fa1[210],sid1[210],af1[210],disn[210],fan[210],sidn[210],afn[210],dist[210],fat[210];
int u[51000],v[51000],c[51000],d[51000];
int res=inf;
signed main(){
	scanf("%lld%lld",&n,&m),memset(g,inf,sizeof(g)),memset(f,inf,sizeof(f));
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld%lld",&u[i],&v[i],&c[i],&d[i]);
		if(g[u[i]][v[i]]>=c[i])f[u[i]][v[i]]=g[u[i]][v[i]],g[u[i]][v[i]]=c[i];
		else f[u[i]][v[i]]=min(f[u[i]][v[i]],c[i]);
	}
//	for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)printf("%d ",g[i][j]);puts("");}
//	for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)printf("%d ",f[i][j]);puts("");}
	Dijkstra(1,dis1,fa1),Dijkstra(n,disn,fan);
	res=min(res,dis1[n]+disn[1]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)h[i][j]=g[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=h[j][i];
	Dijkstra(1,sid1,af1),Dijkstra(n,sidn,afn);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=h[i][j];
	memcpy(h,g,sizeof(g));
	for(int i=1;i<=m;i++){
		int tmpa=g[u[i]][v[i]],tmpb=g[v[i]][u[i]];
		g[u[i]][v[i]]=f[u[i]][v[i]];
		g[v[i]][u[i]]=min(g[v[i]][u[i]],c[i]);
		
		int p=0;
		if(fa1[v[i]]!=u[i]||dis1[u[i]]+c[i]!=dis1[v[i]])p=min(dis1[n],dis1[v[i]]+c[i]+sidn[u[i]]);
		else Dijkstra(1,dist,fat),p=dist[n];
		int q=0;
		if(fan[v[i]]!=u[i]||disn[u[i]]+c[i]!=disn[v[i]])q=min(disn[1],disn[v[i]]+c[i]+sid1[u[i]]);
		else Dijkstra(n,dist,fat),q=dist[1];
		
		g[u[i]][v[i]]=tmpa;
		g[v[i]][u[i]]=tmpb;
		res=min(res,p+q+d[i]);
	}
	printf("%lld\n",res==inf?-1:res);
	return 0;
}
```



---

## 作者：dbxxx (赞：19)

[可以在我的博客中查看，谢谢支持。](https://www.cnblogs.com/crab-in-the-northeast/p/luogu-p6880.html)

两条前置知识：

-  在图 $G$ 上构造根为 $x$ 的最短路树 $T$，我们删除任意一条不在 $T$ 上的边 $e$，$x$ 到任意一个节点 $u$ 的距离 $d(x, u)$ 均不会发生变化。
-  有向图上 $d(i, x)$ 的求法，其中 $x$ 为定点。实际上就是构造 $G$ 的反图，在反图上跑 $x$ 为源点的 dijkstra 即可。

这个题我的第一反应是分层图，把原图分为两层然后两层之间用反边单向导通。也就是[这个题](https://www.luogu.com.cn/problem/P3119)。

但是这样可以被 hack，看下面这个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/7tcl39xq.png)

唯一一种可行的走法是：翻转 $4 \to 3$ 这条边，然后 $1 \to 2 \to 3 \to 4 \to 5 \to 6 \to 9 \to 8 \to 3 \to 4 \to 7 \to 1$。

可以看到 $3 \to 4$ 我们走了两次，分层图不能很好的处理一条道路被翻转然后被走两次（注意到我上面给的另一道题，那个题本身就不允许在一条道路上反走两次，但这个题可以）。

思考发现好像怎么改分层图的模型也不能处理这个问题。先扔在一边。

注意到原题的一个条件：$n \le 200$。也就是这个图是稠密的？不过还有一个更强的性质，**某棵最短路树最多只有可能有 $199$ 条边**，剩余的边我们都可以利用前置知识第一条加速计算。

实际上翻转一条边 $e$ 可以看做删除 $e$ 然后再添加它的反边 $e'$。

令 $e$ 代表 $(u, v, w)$，$e'$ 代表 $(v, u, w)$。再设**删除 $e$ 前** $s, t$ 两点最短距离 $d(s, t)$（也就是原图上 dijkstra 的结果）；**删除 $e$ 后增加 $e'$ 前** $s, t$ 两点最短距离为 $f(s, t)$；**删除 $e$ 再增加 $e'$ 后** $1$ 到 $n$ 的最短路变为 $D$，$n$ 到 $1$ 的最短路变为 $X$。

那么有：$D = \min(f(1, n), f(1, v) + w +  f(u, n))$，$X = \min(f(n, 1), f(n, v) + w + f(u, 1))$。

证明：$\min$ 中前半部分为不走 $e'$ 的最短路，后半部分为必走 $e'$ 的最短路，合并即可。

现在问题变成：怎么好好利用最短路树性质快速求解 $f(s, t)$？事实上我们只关心四种 $f$：$s = 1$ 或 $s = n$ 或 $t = 1$ 或 $t = n$。

我们令 $T_1$ 为原图上根为 $1$ 的最短路树；$T_n$ 为原图上根为 $n$ 的最短路树；$Y_1$ 为反图上根为 $1$ 的最短路树；$Y_n$ 为反图上根为 $n$ 的最短路树。下面的“重新求解”意为，在原图 $G$ 删除 $e$ 形成的新图 $G'$ 上，重新跑 dijkstra 求最短路（其实只要在 $G$ 上 dijkstra，枚举边时忽略 $e$ 即可）。

- $e \in T_1$ 时，$f(1, t)$ 需要重新求解；否则 $f(1, t) = d(1, t)$；
- $e \in T_n$ 时，$f(n, t)$ 需要重新求解；否则 $f(n, t) = d(n, t)$；
- $e \in Y_1$ 时，$f(s, 1)$ 需要重新求解；否则 $f(s, 1) = d(s, 1)$；
- $e \in Y_n$ 时，$f(s, n)$ 需要重新求解；否则 $f(s, n) = d(s, n)$。

由于一棵最短路树上边数最多只有 $199$，因此上述算法中最多会跑 $199 \times 4$ 次 dijkstra，可过。

最后枚举 $e$，求最小的 $D + X + k$ 即可，这里 $k$ 是原题中的 $D_i$：把 $e$ 翻转的代价。

---

一些细节：

- 稠密图，dijkstra 不加堆优化（不如不加）。
- 注意到这个题中有重边，而且 $u \to v$ 中的所有重边并不能简单地只保留最短的那条边 $ed$，因为翻转 $ed$ 之后 $u \to v$ 还可以从另一条边走，因此这个题不要用邻接矩阵（如果硬用的话需要存 $u \to v$ 的最短边和次短边，会引入接下来写码中很多容易错的细节）。
- 注意不能通过一条边的两个端点确定这个边是 $e$，因为有重边。
- 善用结构体，把图封装起来。

时间复杂度 $\mathcal{O}(w \times n^3)$，其中 $w$ 是一个不超过 $4$ 的常数。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-11 22:33:15 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-12 03:10:21
 */
#include <bits/stdc++.h>
#define int long long
inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

typedef std :: pair <int, int> pii;

const int maxn = 205;
const int maxm = (int)5e4 + 5;
int fru[maxm], tov[maxm], wei[maxm], ext[maxm];

int n;

struct graph {
    graph() {
        std :: memset(ont, false, sizeof(ont));
        std :: memset(pre, 0, sizeof(pre));
    }

    int s;
    std :: vector <pii> G[maxn];
    
    inline void add_edge(int u, int v, int id) {
        G[u].emplace_back(v, id);
    }

    int d[maxn], dis[maxn], pre[maxn];
    bool ont[maxm], vis[maxn];

    inline void dijkstra(int ban) {
        std :: memset(dis, 0x3f, sizeof(dis));
        std :: memset(vis, false, sizeof(vis));
        dis[s] = 0;
        for (int i = 1; i <= n; ++i) {
            int u = n + 1;
            for (int j = 1; j <= n; ++j)
                if (!vis[j] && dis[j] < dis[u])
                    u = j;
            if (u == n + 1)
                break ;
            vis[u] = true;
            
            for (pii e : G[u]) {
                int v = e.first, id = e.second, w = wei[id];
                if (id == ban)
                    continue;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    if (ban)
                        continue;
                    ont[pre[v]] = false;
                    pre[v] = id;
                    ont[pre[v]] = true;
                }
            }
        }

        if (!ban)
            std :: copy(dis + 1, dis + 1 + n, d + 1);
    }

    inline int get(int x, int id) { // 删除 id 后 s 到 x 的距离
        if (!ont[id])
            return d[x];
        
        dijkstra(id);
        
        return dis[x];
    }
} G1, Gn, R1, Rn;

inline bool gmi(int &a, int b) {
    return b < a ? a = b, true : false;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

signed main() {
    n = read();
    int m = read();
    
    G1.s = R1.s = 1;
    Gn.s = Rn.s = n;

    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read(), w = read(), ex = read();
        G1.add_edge(u, v, i);
        Gn.add_edge(u, v, i);
        R1.add_edge(v, u, i);
        Rn.add_edge(v, u, i);
        fru[i] = u;
        tov[i] = v;
        wei[i] = w;
        ext[i] = ex;
    }

    G1.dijkstra(0);
    Gn.dijkstra(0);
    R1.dijkstra(0);
    Rn.dijkstra(0);
    
    int ans = G1.d[n] + Gn.d[1];
    
    for (int i = 1; i <= m; ++i) {
        int u = fru[i], v = tov[i], w = wei[i], ex = ext[i];
        gmi(ans, 
            min(G1.get(n, i), G1.get(v, i) + w + Rn.get(u, i)) + 
            min(Gn.get(1, i), Gn.get(v, i) + w + R1.get(u, i)) + ex
        );
    }

    if (ans >= G1.dis[n + 1])
        puts("-1");
    else
        printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Thunder_S (赞：8)

## Solution

首先明确一个性质，翻转的边需要在最短路树上，否则对答案没有贡献。

首先求出 $1$ 到 $i$，$i$ 到 $n$ 的最短路径，并把在最短路树上的边打上标记。

也求出 $n$ 到 $i$，$i$ 到 $1$ 的最短路径，同时打上最短路树的标记。

具体操作可以建正图和反图共 $4$ 个，两个正图，两个反图，正图和反图中各有一个以 $1$ 为起点，一个以 $n$ 为起点，以不同的起点求出对应的最短路。

约定：

1. 以 $1$ 为起点的正图为图 $1$。目的是求出 $1$ 到 $i$ 的最短路。

2. 以 $n$ 为起点的反图为图 $2$。目的是求出 $i$ 到 $n$ 的最短路。

3. 以 $n$ 为起点的正图为图 $3$。目的是求出 $n$ 到 $i$ 的最短路。

4. 以 $1$ 为起点的反图为图 $4$。目的是求出 $i$ 到 $1$ 的最短路。

5. 一条边的起点是 $x$，终点是 $y$，权值是 $v$。

令初始答案为在不翻转边下的 $1$ 到 $n$ 和 $n$ 到 $1$ 的最短路径和。

考虑枚举边，对于 $1$ 到 $n$，如果该边不在图的最短路树上，就返回原值，否则将此边翻转跑最短路。

对于翻转，显然不能找到原边将其翻转。有一种想法是给原边打上标记，加入新的翻转边并在最短路结束后将其删掉。

另一种想法是手动走翻转边。对于一条边，要么走要么不走。不走就是在没有原边的基础上跑最短路，走则是先从 $1$ 走到 $y$，再从 $x$ 走到 $n$，同时补上中间少了的 $v$。

将 $1$ 到 $n$ 和 $n$ 到 $1$ 分开处理，求出两个最短路，判断最短路径和加上修改当前边的权值与答案的大小，更新答案。

最后判断 $-1$，输出答案即可。

## Code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 1e9
#define N 205
#define M 50005
#define ll long long
using namespace std;
int n,m,x[M],y[M];
ll ans,z[M],d[M];
struct gra
{
	int s,tot,cant,last[M];
	ll dis1[N],dis2[N];
	bool bin[M],bj[N];
	struct node
	{
		int to,next,head;
		ll val;
	}a[M];
	void add(int x,int y,ll z)
	{
		a[++tot].to=y;
		a[tot].val=z;
		a[tot].next=a[x].head;
		a[x].head=tot;
	}
	void dij()
	{
		memset(bj,false,sizeof(bj));
		for (int i=1;i<=n+1;++i)
			dis1[i]=inf;
		dis1[s]=0;
		for (int i=1;i<=n;++i)
		{
			int k=n+1;
			for (int j=1;j<=n;++j)
				if (!bj[j]&&dis1[j]<dis1[k]) k=j;
			if (k==n+1) break;
			bj[k]=true;
			for (int j=a[k].head;j;j=a[j].next)
			{
				int u=a[j].to;
				if (!bj[u]&&dis1[u]>dis1[k]+a[j].val) dis1[u]=dis1[k]+a[j].val,last[u]=j;
			}
		}
		for (int i=1;i<=n;++i)
			if (i!=s) bin[last[i]]=true;
	}
	void get()
	{
		memset(bj,false,sizeof(bj));
		for (int i=1;i<=n+1;++i)
			dis2[i]=inf;
		dis2[s]=0;
		for (int i=1;i<=n;++i)
		{
			int k=n+1;
			for (int j=1;j<=n;++j)
				if (!bj[j]&&dis2[j]<dis2[k]) k=j;
			if (k==n+1) break;
			bj[k]=true;
			for (int j=a[k].head;j;j=a[j].next)
			{
				int u=a[j].to;
				if (!bj[u]&&dis2[u]>dis2[k]+a[j].val&&j!=cant) dis2[u]=dis2[k]+a[j].val;
			}
		}
	}
	ll calc(int e,int ss)
	{
		if (!bin[e]) return dis1[ss];
		cant=e;
		get();
		return dis2[ss];
	}
}g[10];
int main()
{
	scanf("%d%d",&n,&m);
	g[1].s=g[4].s=1;
	g[2].s=g[3].s=n;
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d%lld%lld",&x[i],&y[i],&z[i],&d[i]);
		g[1].add(x[i],y[i],z[i]);g[2].add(y[i],x[i],z[i]);
		g[3].add(x[i],y[i],z[i]);g[4].add(y[i],x[i],z[i]);
	}
	for (int i=1;i<=4;++i)
		g[i].dij();
	ans=g[1].dis1[n]+g[3].dis1[1];
	for (int i=1;i<=m;++i)
	{
		ll d1=min(g[1].calc(i,n),g[1].calc(i,y[i])+z[i]+g[2].calc(i,x[i]));
		ll d2=min(g[3].calc(i,1),g[3].calc(i,y[i])+z[i]+g[4].calc(i,x[i]));
		ans=min(ans,d1+d2+d[i]);
	}
	if (ans>=1e9) printf("-1\n");
	else printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：冷笑叹秋萧 (赞：4)

#  [JOI 2020 Final] オリンピックバス
## 题意
题面写得很清楚明白了。
## 题解
看到这道题的第一眼，会很显然地想到每次枚举一条翻转的边跑最短路，但这样的复杂度显然非常的大，只能拿到最低档的 5 分（捆绑数据要是打炸了还一分没有）。
分析一下数据范围，我们发现如果有一种 $O(n^{3})$ 左右的算法就可以不多不少刚刚好跑过。
首先我们明确包括一共有四种从$1\sim n$再从$n\sim 1$的走法：

 1.  $1\sim n$ 和 $n\sim 1$ 都走不用经过翻转的边的最短路。
 2.  $1\sim n$ 走必经过翻转的边 $v\sim u$ 的最短路， $n\sim 1$ 走不用经过翻转的边的最短路。
 3.  $1\sim n$ 走不用经过翻转的边的最短路， $n\sim 1$ 走必经过翻转的边$v\sim u$的最短路。
 4.   $1\sim n$ 和 $n\sim 1$ 都走必经过翻转的边 $v\sim u$ 的最短路。

~~（有点绕口）~~
再想想我们需要在没有任何边翻转的原图中先得到那些东西：

 1.  1 号城市到 $n$ 号个城市的最短路。
 2.  $n$ 号城市到 1 号城市的最短路。
 3. 每个城市到 1 号城市的最短路。
 4. 每个城市到 $n$ 号城市的最短路。

前两个直接在原图跑最短路，后两个建个反图跑最短路即可。

至于为什么要建反图，是因为如果你把某条边翻转了之后，原先有在最短中的边就不存在了，所以不能直接从前两个的结果中赋值过来（还是不懂的可以画图手动模拟一下，很显然是不相同的）。

~~（那你说了那么多，还不是要枚举每条边去翻转？？？）~~ 

对于翻转操作，我们有一个~~奇技淫巧~~好的方法进行处理：因为如果我们没有翻转在 $1\sim n$ 和 $n\sim 1$ 最短路上的边，上述第一中走法中是不会产生贡献的，而在最短路上的边翻转之后，对于我们当前求出的其他走法中也不会更优。

所以我们只需要在跑前两遍最短路时处理出在 $1\sim n$ 和 $n\sim 1$ 最短路上的边，然后枚举这些边，暴力加边跑最短路，做第一种走法，其它的边就直接 $O(1)$ 走后面三种走法，然后判断取最小值即可。

然后我们就可以限制枚举边翻转的复杂度在严格 $O(n)$ 以内了。

实现有~~亿~~一点点细节，但是明确思路之后就不难写。
## CODE

```cpp
#include<cstdio>
#include<string>
#define R register int
#define N 205
#define M 50005
#define ll long long
#define inf 1234567891011
using namespace std;
struct G{ll to,next,id;ll w;}e[M];
int n,m,u[M],v[M],cnt,head[N],nxt[N],last[N];
ll c[M],d[M],ans1,ans2,ans,dist1[N],dist2[N][5];
bool bz[N],flag[M];
ll min(ll a,ll b) {return a<b?a:b;}
void read(int &x)
{
	x=0;ll f=1;char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x*=f;
}
void read1(ll &x)
{
	x=0;ll f=1;char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x*=f;
}
void add(int u,int v,ll w,int id)
{
	e[++cnt].to=v;e[cnt].w=w;e[cnt].id=id;
	e[cnt].next=head[u];head[u]=cnt;
}
void dij1(int s)
{
	for (R i=1;i<=n;++i) dist1[i]=inf,bz[i]=0,nxt[i]=0;
	dist1[s]=0;
	for (R i=1;i<=n;++i)
	{
		ll mn=inf;int k=n+1;
		for (R j=1;j<=n;++j) if (!bz[j] && dist1[j]<mn) mn=dist1[j],k=j;
		if (k==n+1) break;bz[k]=1;
		for (R j=head[k];j;j=e[j].next)
		{
			int v=e[j].to;
			if (dist1[v]>dist1[k]+e[j].w) dist1[v]=dist1[k]+e[j].w,nxt[v]=k,last[v]=j;
		}
	}
}
void dij2(int s,int num)
{
	for (R i=1;i<=n;++i) dist2[i][num]=inf,bz[i]=0;
	dist2[s][num]=0;
	for (R i=1;i<=n;++i)
	{
		ll mn=inf;int k=n+1;
		for (R j=1;j<=n;++j) if (!bz[j] && dist2[j][num]<mn) mn=dist2[j][num],k=j;
		if (k==n+1) break;bz[k]=1;
		for (R j=head[k];j;j=e[j].next)
		{
			int v=e[j].to;
			if (dist2[v][num]>dist2[k][num]+e[j].w) dist2[v][num]=dist2[k][num]+e[j].w;
		}
	}	
}
void build(ll u)
{
	while (u) flag[last[u]]=1,u=nxt[u];
}
int main()
{
	read(n);read(m);
	for (R i=1;i<=m;++i)
	{
		read(u[i]);read(v[i]);read1(c[i]);read1(d[i]);
		add(u[i],v[i],c[i],i);
	}
	dij1(1);ans1=dist1[n];build(n);
	dij1(n);ans2=dist1[1];build(1);ans=ans1+ans2;
	dij2(1,1);dij2(n,2);
	for (R i=1;i<=n;++i) head[i]=0;cnt=0;
	for (R i=1;i<=m;++i) add(v[i],u[i],c[i],i);
	dij2(1,3);dij2(n,4);
	for (R i=1;i<=m;++i)
	{
		if (flag[i]) 
		{
			for (R j=1;j<=n;++j) head[j]=0;cnt=0;
			for (R j=1;j<=m;++j)
				if (j==i) add(v[j],u[j],c[j],j);else add(u[j],v[j],c[j],j);
			dij1(1);ll tot1=dist1[n];dij1(n);ll tot2=dist1[1];ans=min(ans,tot1+d[i]+tot2);
		}
		else
		{
			ans=min(ans,ans1+dist2[v[i]][2]+c[i]+d[i]+dist2[u[i]][3]);
			ans=min(ans,ans2+dist2[v[i]][1]+c[i]+d[i]+dist2[u[i]][4]);
			ans=min(ans,dist2[v[i]][1]+c[i]+d[i]+dist2[u[i]][4]+dist2[v[i]][2]+c[i]+dist2[u[i]][3]);
		}
	}
	if (ans>=inf) printf("-1\n");else printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Time_tears (赞：4)

题意：给你一个有向图，问你能否通过换边从$1$ 到 $n$ ，并使代价最小。

首先：我们肯定是枚举转换的边，然后求转换后的最短路。
但这样的复杂度是 $O(n^2m)$ 的，因为这样会多做很多的无用功。

注意到在最短路树上的边才有可能修改后对最短路有影响，所以我们最多只用跑 $O(n)$ 次最短路，复杂度 $O(n^3)$ 。

最后说一下，因为我们要求 $1$ 到 $n$ 和 $n$ 到 $1$ 的最短路，我们就可以用 4 个最短路， 原点为 $1$ ，正图， 原点为 $1$ ，反图， 原点为 $n$ ，正图，和原点为 $n$ ，反图。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<cstdio>
#include<cstring>
#define N 205
#define M 50005
#define ll long long
using namespace std;
int n,m,x[M],y[M],c[M],d[M];
struct Graph {
	int s,n,B,vis[N],h[N];
	int las[N],pd[M],cnt;
	ll d1[N],d2[N];
	struct node {
		int to,next,value;
	} e[M];
	void Addedge(int x,int y,int z) {
		e[++cnt]=(node) {y,h[x],z},h[x]=cnt;
	}
	void Dijkstra() {
		memset(d1,0x3f,sizeof(ll)*(n+2));
		memset(vis,0,sizeof(int)*(n+1)),d1[s]=0;
		for(int i=1,j,k=n+1,y; i<=n; ++i,k=n+1) {
			for(j=1; j<=n; ++j)if(!vis[j]&&d1[j]<d1[k])k=j;
			if(k==n+1)break;
			for(j=h[k],vis[k]=1; j; j=e[j].next)if(!vis[y=e[j].to]&&d1[y]>d1[k]+e[j].value)d1[y]=d1[k]+e[j].value,las[y]=j;
		}
		for(int i=1; i<=n; ++i)if(i!=s)pd[las[i]]=1;
	}
	void Solve() {
		memset(d2,0x3f,sizeof(ll)*(n+2));
		memset(vis,0,sizeof(int)*(n+1)),d2[s]=0;
		for(int i=1,j,k=n+1,y; i<=n; ++i,k=n+1) {
			for(j=1; j<=n; ++j)if(!vis[j]&&d2[j]<d2[k])k=j;
			if(k==n+1)break;
			for(j=h[k],vis[k]=1; j; j=e[j].next)if(!vis[y=e[j].to]&&B!=j&&d2[y]>d2[k]+e[j].value)d2[y]=d2[k]+e[j].value;
		}
	}
	ll Calc(int x,int y) {
		if(!pd[x])return d1[y];
		return (B!=x?(B=x,Solve()):void()),d2[y];
	}
} G[4];
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
ll min(ll x,ll y) {
	return x<y?x:y;
}
int main() {
	n=read(),m=read(),G[0].s=G[2].s=1,G[1].s=G[3].s=n,G[0].n=G[2].n=G[1].n=G[3].n=n;
	for(int i=1; i<=m; ++i) {
		x[i]=read(),y[i]=read(),c[i]=read(),d[i]=read();
		G[0].Addedge(x[i],y[i],c[i]),G[1].Addedge(y[i],x[i],c[i]);//1->i,i->n
		G[2].Addedge(y[i],x[i],c[i]),G[3].Addedge(x[i],y[i],c[i]);//i->1,n->i
	}
	for(int i=0; i<4; ++i)G[i].Dijkstra();
	ll ans=G[0].d1[n]+G[3].d1[1];
	for(int i=1; i<=m; ++i) {
		ll dn=min(G[0].Calc(i,n),G[0].Calc(i,y[i])+c[i]+G[1].Calc(i,x[i]));
		ll d1=min(G[3].Calc(i,1),G[3].Calc(i,y[i])+c[i]+G[2].Calc(i,x[i]));
		ans=min(ans,d1+dn+d[i]);
	}
	printf("%lld",(ans<1e17)?ans:-1);
	return 0;
}
```


---

## 作者：Zwb0106 (赞：3)

[**原题链接**](https://www.luogu.com.cn/problem/P6880)

------------
## 思路

这里给出一个比其他题解更强的结论：我们需要暴力重跑最短路的边只有 $1$ 到 $n$ 和 $n$ 到 $1$ 最短路上的必经边。

首先说明一点，用暴力松弛的方式实现的 Dijkstra 有 $O(n^2)$ 的时间复杂度，在稠密图上更优。以下记 $dis_{u,v}$ 表示原图上从 $u$ 到 $v$ 的最短路长度。

一个直接的想法是，枚举 $m$ 条边，每次都跑 Dijkstra，时间复杂度 $O(n^2 m)$。注意到很多边并不会使答案更优，尝试减小这个枚举上界。

具体地，若边 $(u,v,c,d)$ 既不是 $1$ 到 $n$ 最短路上的必经边，也不是 $n$ 到 $1$ 最短路上的必经边，那反向之后不会破坏原先的最短路，这是因为存在不覆盖这条边的最短路径，于是直接对原最短路与强制经过这条边的最短路取 $\min$，即 $\min \{ dis_{1,n},dis_{1,v} + c + dis_{u,n} \} + \min \{ dis_{n,1},dis_{n,v} + c + dis_{u,1} \} +d$。

现在考虑最短路上的必经边。

注意到图上从一点到另一点的最短路的必经边集合是所有最短路径的交，而最短路径必然不会经过重复点，因此边数是 $O(n)$ 的，那么必经边的数目也是 $O(n)$ 的，所以暴力重跑最短路即可，这部分的复杂度为 $O(n^3)$。至于找必经边，在做以 $1$ 和 $n$ 为起点的 Dijkstra 时，在成功松弛的点上记录一下前驱边，这些边一定包含了所有必经边（可惜的是，尽管我给出了一个更强的结论，但这并不能优化复杂度，为了代码实现方便，还是把所有前驱边都处理了）。

时间复杂度 $O(n^3+m)$。

------------
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define gc getchar
#define pc putchar
#define fs first
#define sc second
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define lowbit(x) (x&(-x))
using namespace std;

ll read()
{
	ll x=0,f=1;
	char ch=gc();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=gc();
	return x*f;
}
void print(ll x)
{
	if(x<0)pc('-'),x=-x;
	if(x>9)print(x/10);
	pc(x%10+48);
}

const int N=205,M=1e5+5;
const ll INF=1e18;
int n,m,vis[N],ok[M],key[N],col[M];
ll dis[N][N];
struct Edge{
	int u,v,w1,w2;
}E[M];
struct edge{
	int v,w,id;
};
vector<edge>e[N];

void Dijkstra(int s,int op)
{
	for(int i=1;i<=n;i++)
		dis[s][i]=INF,vis[i]=0;
	dis[s][s]=0;
	
	for(int i=1;i<=n;i++)
	{
		int u=0;
		ll mind=INF;
		
		for(int v=1;v<=n;v++)
			if(!vis[v]&&dis[s][v]<mind)
				mind=dis[s][v],u=v;
		
		if(!u)break;
		vis[u]=1;
		
		for(int j=0;j<e[u].size();j++)
		{
			int v=e[u][j].v,w=e[u][j].w,id=e[u][j].id;
			if(!ok[id])continue;
			if(dis[s][u]+w<dis[s][v])
			{
				dis[s][v]=dis[s][u]+w;
				if(!op)key[v]=id;
			}
		}
	}
	
	if(!op)
		for(int i=1;i<=n;i++)
			col[key[i]]=1;
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read(),m=read();
	
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),c=read(),d=read();
		e[u].push_back({v,c,i<<1});
		e[v].push_back({u,c,i<<1|1});
		E[i]={u,v,c,d};
		ok[i<<1]=1;
	}
	
	Dijkstra(1,0),Dijkstra(n,0);
	for(int i=2;i<n;i++)
		Dijkstra(i,1);
	
	ll ans=min(INF,dis[1][n]+dis[n][1]);
	
	for(int i=1;i<=m;i++)
	{
		if(col[i<<1])continue;
		
		int u=E[i].u,v=E[i].v,w1=E[i].w1,w2=E[i].w2;
		
		ll D1=min(dis[1][n],dis[1][v]+w1+dis[u][n]),
		D2=min(dis[n][1],dis[n][v]+w1+dis[u][1]);
		
		ans=min(ans,D1+D2+w2);
	}
	
	for(int i=1;i<=m;i++)
	{
		if(!col[i<<1])continue;
		
		ok[i<<1]=0,ok[i<<1|1]=1;
		
		Dijkstra(1,1),Dijkstra(n,1);
		ans=min(ans,dis[1][n]+dis[n][1]+E[i].w2);
		
		ok[i<<1]=1,ok[i<<1|1]=0;
	}
	
	if(ans<INF)print(ans);
	else print(-1);
	
	return 0;
}
```

---

## 作者：djh0314 (赞：2)

[**洛谷**](https://www.luogu.com.cn/problem/P6880)。

## 题意

应该显然，注意**最多只能翻转一条边**，并且可以不翻转。

## 分析

首先观察数据范围 $2\le N \le 200$，$1\le M \le 5\times 10^4$，可以发现我们的 $N$ 和 $M$ 并不是同级的，因此，在众多的最短路算法中，我们应当选择不加堆优化的 dijkstra 算法，并且使用邻接矩阵，这是 $O(n^2)$ 的时间复杂度，加入使用了堆优化或者使用邻接表，这就会使我们的最短路的时间变大。

接下来就是这道题比较巧妙的地方了，我们都知道 $M\le 1000$ 的暴力怎么打，使用不加堆优化的迪杰，加上枚举翻转的边，时间复杂度是 $O(M\times N^2)$。但是这 $m$ 次最短路并不是都是必须的，首先，假如我们枚举的这条边并不在 $1$ 到 $n$ 或 $n$ 到 $1$ 的最短路当中，那么翻转场此边并不会影响原来的路径的大小，但是我们的最短路可能会因此发生改变，不过只需要用原来 $1$ 到 $v$ 的最短路加上 $u$ 到 $n$ 的最短路加上翻转的边，与原最短路取小值即可。

那么在原最短路径的边呢，没有什么高大上的算法，直接和暴力一样即可。

接下来分析一下时间复杂度，我们的暴力是 $O(n^2)$，不在最短路上的取答案是 $O(1)$，而最短路径上的边数，最多只有 $O(n)$。

注意，这里的最短路径上的边，是指确定的一条路径，这条路径可以用记转移来的结点，也就是最短路径树解决，而不是可能出现在最短路径上的边。

~~~cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e2+5;
const int M = 5e4+5;
const int INF = 0x3f3f3f3f3f3f;
inline int read() {
	int x;
	scanf("%lld",&x);
	return x;
}
int n, m;
struct Edge {
	int u,v,c,d;
} edge[M];

int lj[N][N],g[N][N],mark[N],dis[5][N],fa[5][N],vis[2][N][N];
//dis[0] 1 正  dis[1] n 正  dis[2] 1 反 dis[3] n 反 dis[4] ls

inline void dj(int st,int *dis,int *fa) {
	for(int i=1; i<=n; ++i) dis[0]=dis[i]=INF,mark[i]=fa[i]=0;
	dis[st]=0;
	while(1) {
		int now=0;
		for(int i=1; i<=n; ++i) if(!mark[i]&&dis[i]<dis[now]) now=i;
		if(!now) break;
		mark[now]=1;
		for(int i=1; i<=n; ++i) if(dis[i]>dis[now]+lj[now][i]) dis[i]=dis[now]+lj[now][i],fa[i]=now;
	}
	return ;
}

signed main() {
	n=read(),m=read();
	for(int i=1; i<=m; ++i) edge[i]=<%read(),read(),read(),read()%>;
	memset(lj,0x3f,sizeof lj),memset(g,0x3f,sizeof g);
	for(int i=1; i<=m; ++i) {
		int u=edge[i].u,v=edge[i].v,c=edge[i].c;
		g[u][v]=min(g[u][v],c);
		if(g[u][v]<lj[u][v]) swap(g[u][v],lj[u][v]);
	}
	dj(1,dis[0],fa[0]),dj(n,dis[1],fa[1]);
	for(int i=1; i<=n; ++i) for(int j=i; j<=n; ++j) swap(lj[i][j],lj[j][i]);
	dj(1,dis[2],fa[2]),dj(n,dis[3],fa[3]);
	for(int i=1; i<=n; ++i) for(int j=i; j<=n; ++j) swap(lj[i][j],lj[j][i]);
	int res=dis[0][n]+dis[1][1];
	if(dis[0][n]<INF) for(int now=n; now; now=fa[0][now]) vis[0][fa[0][now]][now]=1;
	if(dis[1][1]<INF) for(int now=1; now; now=fa[1][now]) vis[1][fa[1][now]][now]=1;
	for(int i=1; i<=m; ++i) {
		int u=edge[i].u,v=edge[i].v,c=edge[i].c,d=edge[i].d;
		int len1=lj[u][v],len2=lj[v][u];
		if(lj[u][v]==c) lj[u][v]=g[u][v];
		lj[v][u]=min(lj[v][u],c);
		int tot=d;
		if(vis[0][u][v]) dj(1,dis[4],fa[4]),tot+=dis[4][n];
		else tot+=min(dis[0][n],dis[0][v]+dis[3][u]+c);

		if(vis[1][u][v]) dj(n,dis[4],fa[4]),tot+=dis[4][1];
		else tot+=min(dis[1][1],dis[1][v]+dis[2][u]+c);
		
		res=min(res,tot);
		lj[u][v]=len1,lj[v][u]=len2;
	}
	cout<<(res>=INF?-1:res)<<"\n";
	return 0;
}
~~~
总结起来，这道题利用了最短路的边数小，以及不加堆优化的 dijkstra，这两个平时并不多用的性质，是一道最短路好题。

---

## 作者：伟大的王夫子 (赞：2)

真的是一道十分好的最短路题目。

我们可以枚举每条需要翻转的边 $i$，考虑计算出翻转之后的最短路径。这里以求 $1 \to n$ 的最短路为例，其中 $n \to 1$ 的同理。

我们先看一下第二档部分分。在这一档部分分中，翻转一条边之后，这一条边相当于变成了一条无向边。我们设 $f_i$ 表示 $1 \to i$ 的最短路长度，$g_i$ 为 $i \to n$ 的最短路长度，那么对于边 $(U_i, V_i, W_i)$，答案显然为 $\min(f_n,f_{V_i} +W_i+ g_{U_i})$，其中，后者表示翻转这条边后给答案的贡献。

那么对于一般的情况，我们该如何处理呢？

其实，若 $(U_i, V_i, W_i)$ 不在 $1 \to V_i$ 与 $U_i \to n$ 的最短路上时，我们仍然可以采用上面的求法，如果在上面时，那么我们暴力翻转边求一次最短路即可。

那这个做法的复杂度又要如何保证呢？怎么判断一条边是否在最短路径上？

我们可以对于每个 $x$，记录一下 $f_x$ 是从哪个 $f$ 转移过来的，记为 $fr_x$。那么，只有当 $fr_{V_i} = U_i$ 时，这条边才会在 $1 \to V_i$ 的最短路上出现。

解决了判断的问题，下面证明一下时间复杂度。

容易发现，如果将 $fr_x$ 与 $x$ 连边，那么会构建出原图的最短路径树。而最短路径树的边最多只有 $n - 1$ 条，于是需要暴力翻转重跑的边不超过 $O(n)$。那么总复杂度为 $O(n^3 + m)$。其中求最短路用的是未加堆优化的迪杰斯特拉。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 205, M = 50005;
using ll = long long;
const ll inf = 4557430888798830399;
int n, m, D[M];
struct graph {
	ll f[N], g[N], d[N], an[N][N];
	int fr1[N], fr2[N], m, a[N][N], X[M], Y[M], Z[M], ver[M], edge[M], tot, nxt[M], head[N];
	vector<pair<int, int> > e[N], fe[N];
	bool v[N];
	graph() {
		m = 0;
		memset(an, -1, sizeof an);
		memset(a, 0x3f, sizeof a);
	}
	inline void add1(int x, int y, int z) {
		X[++m] = x, Y[m] = y, Z[m] = z;
		a[x][y] = min(a[x][y], z);
		e[x].push_back(make_pair(y, z));
		fe[y].push_back(make_pair(x, z));
	}
	inline void add2(int x, int y, int z) {
		ver[++tot] = y, edge[tot] = z, nxt[tot] = head[x], head[x] = tot;
	}
	void dij() {
		memset(v, 0, sizeof v);
		memset(f, 0x3f, sizeof f);
		f[1] = 0;
		for (int i = 1; i < n; ++i) {
			int x = -1;
			for (int j = 1; j <= n; ++j)
				if (!v[j] && (x == -1 || f[j] < f[x])) x = j;
			v[x] = 1;
			for (auto v : e[x]) {
				int y = v.first, z = v.second;
				if (f[y] > f[x] + z) {
					f[y] = f[x] + z;
					fr1[y] = x;
				}
			}
		}
		memset(v, 0, sizeof v);
		memset(g, 0x3f, sizeof g);
		g[n] = 0;
		for (int i = 1; i < n; ++i) {
			int x = -1;
			for (int j = 1; j <= n; ++j) 
				if (!v[j] && (x == -1 || g[j] < g[x])) x = j;
			v[x] = 1;
			for (auto v : fe[x]) {
				int y = v.first, z = v.second;
				if (g[y] > g[x] + z) {
					g[y] = g[x] + z;
					fr2[y] = x;
				}
			}
		}
	}
	ll dij(int s, int t) {
		tot = 0;
		for (int i = 1; i <= n; ++i) head[i] = 0;
		for (int i = 1; i <= m; ++i) add2(X[i], Y[i], Z[i]);
		memset(v, 0, sizeof v);
		memset(d, 0x3f, sizeof d);
		d[s] = 0;
		for (int i = 1; i < n; ++i) {
			int x = -1;
			for (int j = 1; j <= n; ++j)
				if (!v[j] && (x == -1 || d[j] < d[x])) x = j;
			v[x] = 1;
			for (int i = head[x]; i; i = nxt[i]) {
				int y = ver[i], z = edge[i];
				d[y] = min(d[y], d[x] + z);
			}
		}
		return d[t];
	} 
	ll work(int id) {
		if (!id) return f[n];
		if ((fr1[Y[id]] == X[id] || fr2[X[id]] == Y[id]) && a[X[id]][Y[id]] == Z[id]) {
			if (an[X[id]][Y[id]] != -1) return an[X[id]][Y[id]];
			else {
				swap(X[id], Y[id]);
				an[Y[id]][X[id]] = dij(1, n);
				swap(X[id], Y[id]);
				return an[X[id]][Y[id]];
			}
		} else return min(f[Y[id]] + g[X[id]] + Z[id], f[n]);
	}
} g1, g2;
int main() {
	cin >> n >> m;
	for (int i = 1, x, y, z; i <= m; ++i) {
		scanf("%d%d%d%d", &x, &y, &z, D + i);
		g1.add1(x, y, z);
		g2.add1(n - x + 1, n - y + 1, z);
	}
	g1.dij(), g2.dij();
	ll ans = inf;
	ans = min(ans, g1.work(0) + g2.work(0));
	for (int i = 1; i <= m; ++i) ans = min(ans, g1.work(i) + g2.work(i) + D[i]);
	cout << (ans == inf ? -1 : ans) << endl;
}
```


---

## 作者：wwwwwza (赞：0)

我们考虑一个最简单的 $O(m\times n^2)$ 的暴力，最短路用 $O(n^2)$ 的 Dijkstra 来求。

但是在每一次翻转路径中，可以发现有些时候求最短路是没有用的，换句话说，如果翻转的路径不是最短路上的路径，其答案是不会发生变化的。

所以，在枚举翻转的路径时，如果该路径时最短路上的路径，则 $O(n)$ 求整个最短路；若不是，则判断过这个翻转的路径会不会比最短路更优。

时间复杂度 $O(n^3)$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e2+5;
const int M=5e4+5;
const int inf=1e12;
int n,m,x[M],y[M],c[M],d[M],dis[N][N],swp=0,ans=0,a=0,b=0,to[N];
bool vis[N],line[2][M];
struct node{
	int v,w,d,id,opt;
};
bool cmp(node p,node q){
	return p.w<q.w;
}
vector<node>g[N];
void dij(int s,int flag,int *dist){
	for(int i=1;i<=n;i++){
		dist[i]=inf;
		vis[i]=0;
	}
	dist[s]=0;
	for(int i=1;i<=n;i++){
		int u=0,minn=inf;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&minn>dist[j]){
				minn=dist[j];
				u=j;
			}
		}
		vis[u]=1;
		for(int j=0;j<g[u].size();j++){
			int v=g[u][j].v,w=g[u][j].w,id=g[u][j].id,opt=g[u][j].opt;
			int pos=(swp==id?1:0);
			if(opt==pos&&!vis[v]&&dist[v]>dist[u]+w){
				dist[v]=dist[u]+w;
				to[v]=id;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(i==s)continue;
		if(flag==0)line[flag][to[i]]=1;
		if(flag==1)line[flag][to[i]]=1;
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld%lld",&x[i],&y[i],&c[i],&d[i]);
		g[x[i]].push_back({y[i],c[i],d[i],i,0});
		g[y[i]].push_back({x[i],c[i],d[i],i,1});
	}
	for(int i=1;i<=n;i++)sort(g[i].begin(),g[i].end(),cmp);
	for(int i=1;i<=n;i++)dij(i,(i==1?0:(i==n?1:2)),dis[i]);
	a=dis[1][n],b=dis[n][1];
	ans=a+b;
	for(int i=1;i<=m;i++){
		int res=d[i];
		swp=i;
		if(line[0][i])dij(1,2,dis[0]),res+=dis[0][n];
		else res+=min(a,dis[1][y[i]]+c[i]+dis[x[i]][n]);
		if(line[1][i])dij(n,2,dis[0]),res+=dis[0][1];
		else res+=min(b,dis[n][y[i]]+c[i]+dis[x[i]][1]);
		ans=min(ans,res);
	}
	if(ans>=inf)printf("-1");
	else printf("%lld",ans);
	return 0;
}

```

---

## 作者：Adolfo_North (赞：0)

一个比较重要的性质：反转的边要在最短路上才会有贡献。

我们可以先跑一遍最短路，记录下整颗最短路树，然后暴力的对每一条边进行判断，反转。

我们建正反图各两个，分别以 $1$，$n$ 为起点。$n$，$1$ 为终点。然后对每个图跑最短路，记录下最短路树。

若不反转任何一条边，则答案为 $1$ 到 $n$ 再到 $1$ 的最短路。

然后暴力枚举边，第 $i$ 条边，考虑将其反转。反转之后 $1$ 到 $n$ 的最短路即为 $1$ 到 $V_i$ 再从 $U_i$ 走到 $n$ 的最短路。往返分开来算。

有一个需要注意的点是，不可以开全局 `long long` 进行运算，否则只有[ 5 分](https://www.luogu.com.cn/record/157332669)。

讲的比较少，都在代码里。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+7;
const int M=207; 
int n,m;
int u[N],v[N];
long long c[N],d[N],ans;
struct node{
	int frnt;
	long long sum1[M],sum2[M];
	bool fl[M],st[N];
	int lst[N];
	struct Map{
		int to,val,nxt,hed;
	}G[N];
	int cnt=0;
	void add(int u,int v,int w){
		G[++cnt].to=v;
		G[cnt].val=w;
		G[cnt].nxt=G[u].hed;
		G[u].hed=cnt;
	}
	void DJ(){
		memset(fl,0,sizeof fl);
		for(int i=1;i<=n+1;i++) sum1[i]=1e9;
		sum1[frnt]=0;
		for(int i=1;i<=n;i++){
			int u=n+1;
			for(int j=1;j<=n;j++) if(!fl[j]&&sum1[j]<sum1[u]) u=j;
			if(u==n+1) break;
			fl[u]=1;
			for(int j=G[u].hed;j;j=G[j].nxt){
				int v=G[j].to,w=G[j].val;
				if(!fl[v]&&sum1[v]>sum1[u]+w){
					sum1[v]=sum1[u]+w;
					lst[v]=j;//给在最短路树上的点打标记。
				}
			}
		}
		for(int i=1;i<=n;i++) if(i!=frnt) st[lst[i]]=1;//这里是计录下最短路树。
	}
	int swp;
	void DJ2(){
		memset(fl,0,sizeof fl);
		for(int i=1;i<=n+1;i++) sum2[i]=1e9;
		sum2[frnt]=0;
		for(int i=1;i<=n;i++){
			int u=n+1;
			for(int j=1;j<=n;j++) if(!fl[j]&&sum2[j]<sum2[u]) u=j;
			if(u==n+1) break;
			fl[u]=1;
			for(int j=G[u].hed;j;j=G[j].nxt){
				int v=G[j].to,w=G[j].val;
				if(!fl[v]&&sum2[v]>sum2[u]+w&&j!=swp){//这里多了一个判断：即不能为翻转之前的边。
					sum2[v]=sum2[u]+w;
				}
			}
		}
	}
	long long work(int u,int end){
		if(!st[u]) return sum1[end];//不在最短路树上 
		swp=u;
		DJ2();
		return sum2[end];
	}
}g[5];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	g[1].frnt=g[4].frnt=1,g[2].frnt=g[3].frnt=n;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>c[i]>>d[i];
		g[1].add(u[i],v[i],c[i]);//四个图 
		g[2].add(v[i],u[i],c[i]);
		g[3].add(u[i],v[i],c[i]);
		g[4].add(v[i],u[i],c[i]);
	}
	for(int i=1;i<=4;i++) g[i].DJ();//不反转，求最短路 
	ans=g[1].sum1[n]+g[3].sum1[1];//初始答案 
	for(int i=1;i<=m;i++){//将边反转 
		int go=min(g[1].work(i,n),g[1].work(i,v[i])+c[i]+g[2].work(i,u[i]));//去 
		int back=min(g[3].work(i,1),g[3].work(i,v[i])+c[i]+g[4].work(i,u[i]));//来 
		ans=min(ans,go+back+d[i]);
	}
	if(ans>=1e9) ans=-1;
	cout<<ans;
	return 0;
}
```

---

