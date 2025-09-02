# [ARC156F] Make Same Set

## 题目描述

给定长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N),B=(B_1,B_2,\dots,B_N),C=(C_1,C_2,\dots,C_N)$。

请你求出一个满足以下条件的整数集合：

- 该集合可以通过对空集合，依次按 $i=1,2,\dots,N$ 的顺序，每次选择 $A_i$ 或 $B_i$ 加入集合，最终得到。
- 该集合也可以通过对空集合，依次按 $i=1,2,\dots,N$ 的顺序，每次选择 $A_i$ 或 $C_i$ 加入集合，最终得到。
- 在满足上述两个条件的所有集合中，元素个数最大。

## 说明/提示

## 限制

- $1\leq N\leq 5000$
- $1\leq A_i,B_i,C_i\leq 10000$
- 输入的所有值均为整数

## 样例解释 1

集合 $\lbrace 1,2,4\rbrace$ 满足以下条件：
- 关于第 1 个条件，可以通过依次向空集合加入 $B_1,A_2,B_3$ 得到。
- 关于第 2 个条件，可以通过依次向空集合加入 $A_1,C_2,C_3$ 得到。
显然，满足条件的集合元素个数不会超过 $N=3$，因此该集合也满足第 3 个条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1 1
2 3 4
5 4 2```

### 输出

```
3
4 1 2```

## 样例 #2

### 输入

```
15
1 1 15 11 13 7 7 1 6 1 5 7 4 9 8
11 30 1 18 16 15 19 17 3 27 22 7 21 29 9
24 14 23 17 18 16 9 12 10 5 26 29 20 19 11```

### 输出

```
12
7 9 11 17 19 1 15 4 5 6 29 13```

# 题解

## 作者：Schi2oid (赞：10)

### 题意简述

给三个长度为 $N$ 的序列 $A,B,C$，现在要求你找到一个最大的集合，使得以下两种方式都可以将其构造出来：

- 对于所有 $i$，将 $A_i$ 或 $B_i$ 加入集合。
- 对于所有 $i$，将 $A_i$ 或 $C_i$ 加入集合。

$N\le 5000,A_i,B_i,C_i\le10000$。

### 思路分析

将上述约束弱化，我们将两种方式改为：

- 对于所有 $i$，将 $A_i$ 或 $B_i$ 加入集合或什么都不做。
- 对于所有 $i$，将 $A_i$ 或 $C_i$ 加入集合或什么都不做。

那么，对于这个约束，我们有一个显然的网络流解法：

![](https://s1.ax1x.com/2023/05/17/p9WBjOO.png)

我们称上图中第一排点为 $AB$ 点，第 $i$ 个表示我们需要在 $A_i$ 和 $B_i$；称上图中最后一排点为 $AC$ 点，第 $i$ 个点表示我们需要在 $A_i$ 和 $C_i$；第二排点和第三排点分别表示 $AB$ 和 $AC$ 点选择的值，称其为中间点。我们对于 $AB$ 点和 $AC$ 点连向与它们挨着的那一排中的 $A_i,B_i$ 或是 $A_i,C_i$ 连边。其他连边如上图所示，所有连边的流量都为 $1$。那么，对于这个网络，我们跑最大流，就可以找到一组解。

那么考虑这个最大流跑出来的结果有可能有什么问题。考虑对于一个 $AB$ 点或一个 $AC$ 点，若与它相连的中间点都没有流经过，那么我们实际上就是在这一次选择时什么都没做，那么我们就不知道这个点应该选择哪一个。我们定义这样的点为**待定点**。如下图，红色的反边表示这条路径被流过了，那么标记为方形的点就是**待定点**，这是因为它们连向的中间点都不在红色路径上。

![](https://s1.ax1x.com/2023/05/17/p9WBxmD.png)

现在，我们考虑一条怎样的增广路才会导致图中产生新的**待定点**。这意味着，存在与这个点相连的中间点从被流经变成了没有被流经。也就是说，我们在这条增广路图中一定能够找到一段路径，它从一个 $AC$ 点出发，接下来经过两个中间点，然后抵达某个 $AB$ 点。只有这种情况才会将某一段路径从被流经过改为没有被流经过。由于与这个点相连的点都没有被流经，那么这个点本身也一定没有被流经，即其与 $S$ 或 $T$ 之间的连边是可选的。这时，我们可以直接让这个点连接 $S$ 或 $T$ 点，再连向中间点，之后的路径不变。此时增广路长度一定会变短。

如下图所示，如果我们选择红色的增广路，那么它就会产生下图中标记为菱形的新的**待定点**。发现一条 $\text{A3orC3}\rightarrow 3 \rightarrow 3 \rightarrow \text{A3orB3}$ 的路径，这条路径状态的变更使得这个菱形点变成了一个**待定点**。这时，我们可以直接对这条增广路调整为右图中的蓝色增广路，这样，增广路长度变小，同时让这个菱形结点不再成为新的**待定点**。

这说明，如果对于一条增广路，其会造成某个点变成新的**待定点**，那么一定存在另外一条增广路比它更短。换句话来说，**如果对最短的增广路进行增广，则一定不会产生新的待定点**。

![](https://s1.ax1x.com/2023/05/17/p9WBz0e.png)

得到这一结论，我们只需要构造一张图，使得其上不存在任何的**待定点**，然后跑一遍最大流即可，显然我们可以在最开始直接钦定我们每一次选择都是 $A_i$。由于每一个 $AB$ 点一定会与一个代表 $A_i$ 的中间相连，而所有 $A_i$ 都被流经，所以图上不存在任何**待定点**。

至此本题完结，复杂度 $O(N\sqrt N)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e18;
int a[5005],b[5005],c[5005];
int n,m=10000,S=0,T;
int AB(int x){return x;}
int AC(int x){return x+n+2*m;}
int ABv(int x){return x+n;}
int ACv(int x){return x+n+m;}
int nxt[200005],head[200005],to[200005],val[200005];
int cnt=1;
int visa[200005],visv[200005];
int cur[200005];
void build(int u,int v,int w){
	to[++cnt]=v;
	val[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
	to[++cnt]=u;
	val[cnt]=w^1;
	nxt[cnt]=head[v];
	head[v]=cnt;
}
int dep[200005];
queue<int>q;
bool bfs(){
	memcpy(cur,head,sizeof head);
	q.push(S);
	for(int i=0;i<=2*n+2*m+1;i++) dep[i]=-1;
	dep[S]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int eg=head[u];eg;eg=nxt[eg]){
			int v=to[eg];
			if(!val[eg]||dep[v]!=-1) continue;
			q.push(v);
			dep[v]=dep[u]+1;
		}
	}
	return dep[T]!=-1;
}
int dfs(int x,int in){
	if(x==T) return in;
	int out=0;
	for(int ed=cur[x];ed;ed=nxt[ed]){
		cur[x]=ed;
		if(!val[ed]||dep[to[ed]]!=dep[x]+1) continue;
		int tmp=dfs(to[ed],min(val[ed],in-out));
		val[ed]-=tmp;
		val[ed^1]+=tmp;
		out+=tmp;
		if(out==in) break;
	}
	return out;
}
int dinic(){
	int ret=0;
	while(bfs()){
		ret+=dfs(S,INF);
	}
	return ret;
}
int ans[200005];
signed main(){
	cin>>n;
	T=2*n+2*m+1;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(!visv[a[i]]){
			visv[a[i]]=1;
			visa[i]=1;
		}
	}
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	for(int i=1;i<=n;i++){
		build(S,AB(i),visa[i]?0:1);
		build(AB(i),ABv(a[i]),visa[i]?0:1);
		build(AB(i),ABv(b[i]),1);
		build(ACv(a[i]),AC(i),visa[i]?0:1);
		build(ACv(c[i]),AC(i),1);
		build(AC(i),T,visa[i]?0:1);
	}
	for(int i=1;i<=m;i++) build(ABv(i),ACv(i),visv[i]?0:1);
	dinic();
	for(int i=1;i<=n;i++){
		int node=AB(i);
		if(val[head[node]]) ans[a[i]]=1;
		else ans[b[i]]=1;
	}
	int anscnt=0;
	for(int i=1;i<=m;i++) if(ans[i]) anscnt++;
	printf("%lld\n",anscnt);
	for(int i=1;i<=m;i++) if(ans[i]) printf("%lld ",i);
	puts("");
	return 0;
}
```

---

## 作者：psoet (赞：4)

> 有三个序列 $A_{1\sim n},B_{1\sim n},C_{1\sim n}$，找到一个最大的集合 $S$，使得它可以由如下两种方式生成：枚举 $i$，将 $A_i/B_i$ 加入 $S$；枚举 $i$，将 $A_i/C_i$ 加入 $S$。$(n\leq 5000)$

直觉告诉我们答案就是先按第一种方式生成一个集合，再按第二种方式生成一个集合，两个集合交的大小的最大值。写个暴力可以发现是对的。

假设这个结论成立，那么答案是好求的。建一个三部图，左边表示第一种方式，右边表示第二种方式，中间为每种元素（有 1 的容量），跑最大流即可。

---

下面考虑证明结论的正确性，也就是构造方案。

假设当前第一种方式生成的集合是 $S$，第二种方式生成的集合是 $T$。我们要在保持 $|S\cap T|$ 不变的情况下把对称差调整到 0。

假设存在某个 $i$，$S_i\notin T$。如果切换 $S_i$ 的状态后 $S_i^\prime \in T$ 我们直接切换（显然 $|S\cap T|$ 不变）。$T_i\notin S$ 同理。切换一次后对称差减小。

否则如果对称差依然大于 0，一定存在 $A_i,B_i\notin T$ 或 $A_i,C_i\notin S$。

不妨设 $A_i,B_i\notin T$。此时一定有 $T_i = C_i$，我们令 $S_i = T_i = A_i$。不难证明 $|S\cap T|$ 不会减小，对称差不会增大，且满足 $S_i = T_i = A_i$ 的下标数量增加。

于是总共只会调整 $O(n)$ 轮。复杂度 $O(n^2)$。

---

网上题解说由于 Dinic 的神秘性质按某些方式建图后可以不用调整。不是很懂。

---

## 作者：yizhiming (赞：4)

全网都找不到带代码的中文题解。。。

[$Link$](https://www.luogu.com.cn/problem/AT_arc156_f)

## 题目大意

给定三个长为 $n$ 的序列 $A,B,C$，求大小最大的集合 $S$，满足：

- 初始一个空集，枚举 $[1,n]$，每次将 $A_i$ 或 $B_i$ 加入集合。

- 初始一个空集，枚举 $[1,n]$，每次将 $A_i$ 或 $C_i$ 加入集合。

通过上述两种方式都能构造出来的集合为 $S$。

$1\leq n \leq 5000,1\leq a_i,b_i,c_i \leq 10000$。

## 题目分析

不难发现可以将题意转换成匹配问题，考虑每个权值是否能够同时匹配两种情况，其中对于所有出现过的 $A_i$ 一定能够匹配，所以我们先把这一部分处理出来，所以现在剩下的只有出现多次的 $A_i$ 以及剩余的 $B_i,C_i$。

先把问题弱化，改成每次选择对应的两个权值或者不选，容易证明不选等价于统计 $A_i$ 的贡献，而 $A_i$ 的贡献在之前已经统计过了，所以上面的贡献加上这一步就是答案。

考虑将 $i$ 和权值都拆点，$i$ 表示选择 $A_i,B_i$ 时的情况，$i+n$ 表示选择 $A_i,C_i$ 的情况，源点向第一种连，汇点向第二种连，考虑中间的连边，不难想到权值每种只会贡献一次，所以 $i,i+n$ 分别向对应的权值连边，因为贡献只有一次，所以权值也要拆点，由入点向出点连一条流量为 $1$ 的边即可。

按照上述连法，我们就能完成弱化的情况。

然而是这样吗？（查阅资料）仔细想想后你会发现，若对于一个点 $i$，其对应的匹配点 $a_i,b_i$ 若没有流量，就会导致当前节点无法选择，从而导致这种情况不合法而舍掉，所以我们只能证明上界，却不能证明能否达到上界，怎么办呢？

自己多次手模后发现直接跑 dinic 是没有问题的，为什么呢？因为可以证明每次跑最短的增广路，则不会出现上述的无法选择的节点，考虑证明。

假设当前我们增广一条路，使得 $i$ 成为了无法选择的节点，那么这条路径的形式一定经过了和汇点直接相连的节点，然后往后回流，经过了 $i$ 对应的 $A_i/B_i$ 节点，但是这个回流的过程一定是 $S\rightarrow \dots \rightarrow j+n \rightarrow \dots \rightarrow i$，其中还需要经过 $A_i/B_i$ 的权值，但是根据无法选择的定义，我们可以从 $i$ 经过对应权值往 $j$ 走，以这种方式代替原本的增广路，这条增广路一定会比原本增广路要短，因为原本增广路需要通过其它节点走到 $j$，所以我们每次走最短的增广路，就不会出现无法选择的节点。

所以 dinic 可以很好地适用这种情况，首先先强制将 $A_i$ 第一次出现满流，然后再残余网络上跑最大流即可。

## Code

建边用异或是因为边权只有 $0/1$ 这样子可以方便地建反向边（不是网络流本身返流的反向边），看别人提交记录时学到的，这样可以不用分大讨。

查询集合时，只需要考虑哪些权值入点和出点之间没有流量即可。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 5e4+5;
struct aa{
	int nxt,to,val;
}edge[N*2];
int head[N],tote=1;
void add(int u,int v,int w){
	edge[++tote].nxt = head[u];edge[tote].to = v;head[u] = tote;edge[tote].val = w;
	edge[++tote].nxt = head[v];edge[tote].to = u;head[v] = tote;edge[tote].val = w^1;
}
int a[N],b[N],c[N],n,V = 1e4,S,T;
int ans,inf = 1e9;
int dep[N];
queue<int>q;
bool bfs(){
	memset(dep,0,sizeof(dep));
	q.push(S);
	dep[S] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int now = edge[i].to;
			if(!dep[now]&&edge[i].val){
				dep[now] = dep[u]+1;
				q.push(now);
			}
		}
	}
	return dep[T];
}
int dfs(int u,int f){
	if(u==T){
		return f;
	}
	int used = 0;
	for(int i=head[u];i&&f;i=edge[i].nxt){
		int now = edge[i].to;
		if(dep[now]==dep[u]+1&&edge[i].val){
			int w = dfs(now,min(f,edge[i].val));
			f-=w;used+=w;
			edge[i].val-=w;edge[i^1].val+=w;
		}
	} 
	if(!used){
		dep[u] = 0;
	}
	return used;
}
void dinic(){
	while(bfs()){
		ans+=dfs(S,inf);
	}
}
bool vis[N];
int main(){
	n = read();
	for(int i=1;i<=n;i++){
		a[i] = read();
	}
	for(int i=1;i<=n;i++){
		b[i] = read();
	}
	for(int i=1;i<=n;i++){
		c[i] = read();
	}
	S = 0;T = 2*n+2*V+1;
	for(int i=1;i<=n;i++){
		int x = 1;
		if(!vis[a[i]]){
			vis[a[i]] = 1;
			x = 0;
			ans++;
		}
		add(S,i,x);
		add(i+n,T,x);
		add(i,2*n+a[i],x);
		add(i,2*n+b[i],1);
		add(2*n+a[i]+V,i+n,x);
		add(2*n+c[i]+V,i+n,1);
	}
	for(int i=1;i<=V;i++){
		add(2*n+V+i,2*n+i,vis[i]);
	}
	dinic();
	cout<<ans<<"\n";
	for(int i=1;i<=V;i++){
		int u = 2*n+i;
		for(int j=head[u];j;j=edge[j].nxt){
			int now = edge[j].to;
			if(now==u+V&&!edge[j].val){
				cout<<i<<" ";
			}
		}
	}
	return 0;
}

```

照着我自己理解写的，官方题解和网上的实在不太好懂，有问题还请指出。

---

## 作者：JWRuixi (赞：3)

~~哇，金牌题！~~

### 题意

给定序列 $\{a_n\},\{b_n\},\{c_n\}$，找到一个符合如下条件的**不可重集** $S$：

1. 它可以通过将 $\forall i \in [1, n]$，$a_i$ 或 $b_i$ 加入集合生成；
2. 它可以通过将 $\forall i \in [1, n]$，$a_i$ 或 $c_i$ 加入集合生成；
3. 它是所有满足该条件的集合中大小最大的。

输出一个合法的集合 $S$。

### 分析

先考虑一个弱化版的生成方式：

- 对于 $\forall i \in [1, n]$，将 $a_i$ 或 $b/c_i$ 或空加入集合。

这时候如何求 $S$ 的最大大小呢？考虑使用网络流：

1. 源点向所有 $a/b$ 的决策点连边，所有 $a/c$ 决策点向汇点连边。
2. 将每个值拆点；对于 $\forall i \in [1, n]$，左部点 $i$ 向 $a_i,b_i$ 连边，$a^\prime_i,c^\prime_i$ 向右部点 $i$ 连边（流量均为 $1$）。

显然此时的最大流即为弱化问题的答案，容易构造一组合法的解，这显然是原问题的一个上界。

思考为什么同样的做法不能应用到原问题：若存在一个点 $i$ 满足 $a_i$ 和 $b_i$ 对应的权值点均无流量，则无法构造出一种合法方案（下称这种决策点为**空节点**）。

我们考虑分析这个网络与空节点的关系，结论：**在 Dinic 增广的过程中，不会出现新的空节点**。

证明：若出现新的空节点，设其为 $u$，则意味着在增广的过程中，选择了一条增广路退回了 $S \to u \to v_u$ 的流量（$v_u$ 为 $u$ 选择的权值点），也就是说可以将过程拆分成：$S \to \dots \to S \to \dots \to T$；在 Dinic 增广的过程中，因为进行了分层优化，所以显然会走最短的一条增广路，而前半段显然不符合这一性质，所以这种情况是不会出现的。

有了这个性质，我们相当于将问题转化成：找到一个**残余网络**，满足没有空节点，在它上面进行 Dinic 增广。

显然 $a_1,a_2,\dots,a_n$ 是一个合法的点集，只需要每个点都向 $a$ 增广就能构造出一个合法的残余网络。

总时间复杂度 $\mathcal O(n\sqrt n)$。

### Code

提交记录：<https://atcoder.jp/contests/arc156/submissions/43221939>。



---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc156_f)

**题目大意**

> 给定 $a_1\sim a_n,b_1\sim b_n,c_1\sim c_n$。
>
> 对于每个 $i$ 把 $a_i/b_i$ 加入 $S$，$a_i/c_i$ 加入 $T$，求最大的 $|S|$ 使得 $S=T$ 并输出方案。
>
> 数据范围：$n\le 5000$。

**思路分析**

先考虑可以不加入 $a_i/b_i$ 和 $a_i/c_i$ 的情况，这相当于类似三分图匹配的模型，建网络流即可解决。

不妨猜测这个问题的答案就是最终问题的答案。

显然答案不可能更大，我们只要保证 $|S\cap T|$ 不变，然后使得 $S,T$ 对称差变成 $0$。

我们考虑调整法：

- 如果 $a_i\in S,a_i\not\in T,b_i\in T$（$b_i\in S$ 也同理），直接令 $b_i$ 加入 $S$，显然 $a_i\not\in S\cap T$，那么此时对称差变小，是一种合法的调整。
- 否则对于任意 $a_i\not\in T\iff b_i\not\in T$，显然 $c_i\in T$，此时令 $a_i$ 同时加入 $S,T$。
  - 如果 $c_i\in S$，那么 $S\cap T$ 不变，下一次操作可以调整掉 $c_i$ 使得对称差变小。
  - 否则 $S\cap T$ 变大，对称差变小。

那么我们只要 $\mathcal O(n)$ 次调整即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5005,V=1e4;
namespace F {
const int MAXV=3e4+5,MAXE=2e5+5,inf=1e9;
int hd[MAXV],dep[MAXV],cur[MAXV],ec=1,S,T;
struct Edge { int v,f,e; }	G[MAXE];
void add(int u,int v,int f) { G[++ec]={v,f,hd[u]},hd[u]=ec; }
int link(int u,int v,int f) { return add(v,u,0),add(u,v,f),ec; }
bool bfs() {
	memset(dep,-1,sizeof(dep));
	memcpy(cur,hd,sizeof(cur));
	queue <int> Q; Q.push(S),dep[S]=0;
	while(Q.size()) {
		int u=Q.front(); Q.pop();
		for(int i=hd[u];i;i=G[i].e) if(G[i].f) {
			int v=G[i].v;
			if(dep[v]==-1) dep[v]=dep[u]+1,Q.push(v);
		}
	}
	return ~dep[T];
}
int dfs(int u,int f) {
	if(u==T) return f;
	int r=f;
	for(int i=cur[u];i&&r;i=G[i].e) {
		int v=G[cur[u]=i].v;
		if(dep[v]==dep[u]+1&&G[i].f) {
			int g=dfs(v,min(r,G[i].f));
			if(!g) dep[v]=-1;
			G[i].f-=g,G[i^1].f+=g,r-=g;
		}
	}
	return f-r;
}
int dinic() { 
	int f=0;
	while(bfs()) f+=dfs(S,inf);
	return f;
}
}
using F::link;
int n,a[MAXN],b[MAXN],c[MAXN],el[MAXN],er[MAXN];
int f[MAXN],g[MAXN],p[MAXN],q[MAXN],S[V+5],T[V+5];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n;++i) scanf("%d",&c[i]);
	int s=F::S=2*n+2*V+1,t=F::T=2*n+2*V+2;
	for(int i=1;i<=n;++i) {
		int vl=2*V+i,vr=vl+n;
		link(s,vl,1),link(vl,a[i],1),el[i]=link(vl,b[i],1);
		link(vr,t,1),link(a[i]+V,vr,1),er[i]=link(c[i]+V,vr,1);
	}
	for(int i=1;i<=V;++i) link(i,i+V,1);
	F::dinic();
	for(int i=1;i<=n;++i) {
		f[i]=(F::G[el[i]].f?a[i]:b[i]),++S[f[i]];
		g[i]=(F::G[er[i]].f?a[i]:c[i]),++T[g[i]];
		p[i]=a[i]^b[i]^f[i],q[i]=a[i]^c[i]^g[i];
	}
	auto check=[&]() {
		for(int i=1;i<=n;++i) if(!T[f[i]]||!S[g[i]]) return false;
		return true;
	};
	while(!check()) {
		for(int i=1;i<=n;++i) if(!T[f[i]]&&T[p[i]]) {
			--S[f[i]],++S[p[i]],swap(f[i],p[i]); goto ed;
		}
		for(int i=1;i<=n;++i) if(!S[g[i]]&&S[q[i]]) {
			--T[g[i]],++T[q[i]],swap(g[i],q[i]); goto ed;
		}
		for(int i=1;i<=n;++i) if(!T[f[i]]) {
			--S[f[i]],--T[g[i]];
			f[i]=g[i]=a[i],p[i]=b[i],q[i]=c[i];
			++S[f[i]],++T[g[i]];
			goto ed;
		}
		for(int i=1;i<=n;++i) if(!S[g[i]]) {
			--S[f[i]],--T[g[i]];
			f[i]=g[i]=a[i],p[i]=b[i],q[i]=c[i];
			++S[f[i]],++T[g[i]];
			goto ed;
		}
		ed:;
	}
	set <int> Q(f+1,f+n+1);
	printf("%d\n",(int)Q.size());
	for(int it:Q) printf("%d ",it); puts("");
	return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

这个题拷打我网络流水平拷打的我汗流浃背了。

# Part 2：正文

我们先考虑这样一个弱化问题，第一种操作中，我们每次可以选 $a_i$，选 $b_i$ 或不选，第二种操作中我们可以选 $a_i$，选 $c_i$ 或不选。问最大集合大小。用这种方式生成的集合大小和原问题能生成的显然相等。这个问题的答案显然是上界，下界可以考虑钦定一个位置不做操作，对那个位置对位的另一个操作做讨论得到在这个位置两种操作全选 $a_i$ 不劣。

对于这个问题，我们有网络流做法。考虑建三排点，第一排第三排均有 $n$ 个点，分别代表每个位置的操作，源向第一排连边，第三排向汇连边。第二排代表每一个数。第一排中的每个点 $i$ 向第二排中的 $a_i,b_i$ 连边，第二排中的 $a_i,c_i$ 向第三排中的 $i$ 连边。为了限制每个数在集合里只出现一次，我们要把第二排再拆一次点，中间连边限制流量为 $1$。对这个图跑最大流即可得到上面问题的答案。

但是有一个很糟糕的问题是，在构造方案上，这个做法和原问题有差别。原问题没有不选操作，这意味着在原问题的方案中，第一排点的出边和第三排点的入边所代表的数中，至少应有一个存在于构造出的集合。而我们的网络流得到的方案不能保证这一点。我们考虑怎么修复这个问题。

我们称在第一排和第三排的点中，对应操作的两个数均不在构造的集合中的点为不合法点，反之为合法点。有一个惊人的结论是，我们注意到，在最大流单次增广的过程中，如果每次增广长度最短的路径，一定不会让一个本来合法的点变为不合法。证明是容易的，我们考虑什么样的增广路会导致合法点变成不合法。记 $A_i,B_i,B'_i,C_i$ 为四排点中的第 $i$ 个，$S$ 为源，$T$ 为汇。那么一条路径一定是经过了一条 $B_i'\rightarrow B_i$ 的边。即路径形如 $S\rightsquigarrow B'_i\rightarrow B_i\rightarrow A_j\rightarrow B_k\rightsquigarrow T$。但根据不合法点的定义，$S\rightarrow A_j$ 这条边的当前流量为 $0$，所以 $S\rightarrow A_j\rightarrow B_k\rightsquigarrow T$ 这条路径是一个更短的合法增广路。

因此我们如果有一个初始状态不存在不合法点，我们对这个初始方案做最大流增广后得到残量网络就是一个不存在不合法点的残量网络。对着这个残量网络构造方案即可。最后的问题是初始状态的选择。不难发现，我们只需要初始让每个操作均选 $a_i$ 即可（即手动增广所有形如 $S\rightarrow A_i\rightarrow B_{a_i}\rightarrow B'_{a_i}\rightarrow C_j\rightarrow T$ 的路径）。

代码使用了 `atcoder/maxflow`，其增广方式为每次增广最短路径。

# Part 3：代码

```cpp
#include<bits/stdc++.h>
#include<atcoder/maxflow>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

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

//=========================================================================================================
// Define the global variables here.

bool membg=0;
constexpr int N=5e3+7;
int n,a[N],b[N],c[N],pos[N<<1],vis[N<<1];

bool memed=0;

//=========================================================================================================
// Code here.

void solve(){
	read(n);
	int vlim=0;
	for(int i=1;i<=n;i++)read(a[i]),vlim=max(vlim,a[i]);
	for(int i=1;i<=n;i++)read(b[i]),vlim=max(vlim,b[i]);
	for(int i=1;i<=n;i++)read(c[i]),vlim=max(vlim,c[i]);
	int s=0,t=2*n+2*vlim+1;
	atcoder::mf_graph<int>G(2*n+2*vlim+2);
	for(int i=1;i<=n;i++){
		if(vis[a[i]]){
			G.add_edge(s,i,1);
			G.add_edge(i,n*2+a[i],1);
			G.add_edge(n*2+vlim+a[i],n+i,1);
			G.add_edge(n+i,t,1);
		}
		else{
			vis[a[i]]=1;
			G.add_edge(i,s,1);
			G.add_edge(n*2+a[i],i,1);
			G.add_edge(n+i,n*2+vlim+a[i],1);
			G.add_edge(t,n+i,1);
		}
		G.add_edge(i,n*2+b[i],1);
		G.add_edge(n*2+vlim+c[i],n+i,1);
	}
	for(int i=1;i<=vlim;i++){
		if(vis[i]){
			pos[i]=G.add_edge(n*2+vlim+i,n*2+i,1);
		}else{
			pos[i]=G.add_edge(n*2+i,n*2+vlim+i,1);
		}
	}
	G.flow(s,t);
	
	auto edge=G.edges();
	vector<int>lis;
	for(int i=1;i<=vlim;i++){
		if(vis[i]!=edge[pos[i]].flow)
			lis.eb(i);
	}
	
	printf("%d\n",(int)lis.size());
	for(auto x:lis)printf("%d ",x);
	printf("\n");
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

