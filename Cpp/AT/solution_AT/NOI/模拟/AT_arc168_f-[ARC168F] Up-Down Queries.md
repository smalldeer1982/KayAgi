# [ARC168F] Up-Down Queries

## 题目描述

给定一个长度为 $N$ 的整数序列 $x=(x_1,x_2,\cdots,x_N)$，其中每个元素满足 $0 \leq x_i \leq M$，定义 $f(x)$ 如下：

- 准备一个长度为 $M$ 的整数序列 $y=(y_1,y_2,\cdots,y_M)$。初始时，$y$ 的所有元素均为 $0$。然后，依次对每个 $i=1,2,\cdots,N$，按顺序进行如下操作：
  - 对于每个整数 $j$（$1 \leq j \leq x_i$），将 $y_j$ 的值替换为 $\max(y_j-1,0)$。
  - 对于每个整数 $j$（$x_i < j \leq M$），将 $y_j$ 的值替换为 $y_j+1$。
- 所有操作结束后，$y$ 的所有元素之和即为 $f(x)$ 的值。

现给定一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\cdots,A_N)$，其中每个元素满足 $0 \leq A_i \leq M$。请处理 $Q$ 个查询。

- 第 $i$ 个查询：给定整数 $X_i,Y_i$，将 $A_{X_i}$ 的值替换为 $Y_i$，然后输出 $f(A)$ 的值。

## 说明/提示

### 数据范围

- $1 \leq N, M, Q \leq 250000$
- $0 \leq A_i \leq M$
- $1 \leq X_i \leq N$
- $0 \leq Y_i \leq M$
- 输入的所有值均为整数。

### 样例解释 1

首先考虑第 $1$ 个查询。将 $A_1$ 的值替换为 $4$，此时 $A=(4,2,3)$。然后，$f(A)$ 的值按如下方式计算：

- 准备 $y=(0,0,0,0)$。
- 对 $A_1=4$ 进行操作后，$y=(0,0,0,0)$。
- 对 $A_2=2$ 进行操作后，$y=(0,0,1,1)$。
- 对 $A_3=3$ 进行操作后，$y=(0,0,0,2)$。
- $y$ 的元素之和 $=2$，即为 $f(A)$ 的值。

接着考虑第 $2$ 个查询。将 $A_3$ 的值替换为 $0$，此时 $A=(4,2,0)$。然后，$f(A)$ 的值按如下方式计算：

- 准备 $y=(0,0,0,0)$。
- 对 $A_1=4$ 进行操作后，$y=(0,0,0,0)$。
- 对 $A_2=2$ 进行操作后，$y=(0,0,1,1)$。
- 对 $A_3=0$ 进行操作后，$y=(1,1,2,2)$。
- $y$ 的元素之和 $=6$，即为 $f(A)$ 的值。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 4 2
1 2 3
1 4
3 0```

### 输出

```
2
6```

## 样例 #2

### 输入

```
7 2 9
2 0 2 2 0 1 0
1 1
3 0
4 0
4 1
6 1
3 2
2 0
3 2
2 0```

### 输出

```
4
7
11
9
9
6
6
6
6```

## 样例 #3

### 输入

```
20 200000 10
39664 143179 193565 153887 16141 91985 51452 155409 116777 190060 87620 64458 106481 51272 9108 100995 139248 18243 181424 6182
4 196305
13 59753
8 96194
6 57037
19 125781
16 142779
15 13967
10 17772
16 84763
12 17283```

### 输出

```
1145670
1234421
1352851
1352851
1464137
1380569
1380569
1608611
1724643
1736769```

# 题解

## 作者：qiuzx (赞：10)

## 题意

有一个长度为 $m$ 的初始全 $0$ 的序列 $a_i$，依次进行 $n$ 次操作。每次给定 $x_i$，将所有 $1\le j\le x_i$ 的 $a_j$ 变成 $\max(0,a_j-1)$，将所有 $x_i<j\le m$ 的 $a_j$ 变成 $a_j+1$。给定初始的操作序列，有 $q$ 次单点修改 $x_i$，每次修改后回答在序列 $a_i$ 上依次执行这些操作，最终所有 $a_i$ 的和是多少。$n,m,q\le 2.5\times 10^5$。

## 思路

记 $a_0=0$，则容易发现整个操作的过程中，$a_i$ 一定单调不降。这启发我们维护 $a_i$ 的差分数组，具体地，我们维护一个可重集 $S$，其中一个元素 $i$ 出现了 $d$ 次表示 $a_{i+1}=a_i+d$。那么我们现在将操作抽象成可重集上的操作。可以发现一次操作相当于先对 $x_i<j\le m$ 的 $a_j$ 加上 $2$，再对全局做 $a_i=\max(0,a_i-1)$ 的操作。前者相当于在 $S$ 中插入两个 $x_i$，后者相当于删掉 $S$ 中最小的元素。由于只需要知道最后 $S$ 中所有元素的和，即可通过一些简单的计算得到最终需要的答案，所以我们就将问题转化为了这个可重集上的问题。

这个问题仍然不太好处理，因为一次修改可能会对后面 $S$ 的操作产生很大的影响。但这类删除最小值的问题可以考虑建立费用流模型。具体来说，建 $n$ 个点分别代表每次操作，从 $i$ 向 $i+1$ 连边权无穷，费用为 $0$ 的边。从源点向 $i$ 连边权为 $2$，费用为 $x_i$ 的边，表示到达 $i$ 时会加入两个 $x_i$。从 $i$ 向汇点连边权为 $1$，费用为 $0$ 的边，表示在 $i$ 处会删除一个点。

这样一个模型为什么和原问题等价呢？可以从一种类似模拟费用流的角度分析这个费用流，从左往右依次扫每个操作，先将能加的流量全部假定加进来，最后没流出去的就扔掉，流出去的作为最终的答案。则在每一个点上，先加入两个 $x_i$，然后会扔掉一个点。由于每个点都能向右延伸到最右侧，所以每次删除最小值这样的贪心一定是正确的。那么解决这个费用流问题就有这样的一种贪心方法。不难发现这样的贪心就对应了可重集问题中的操作，而最终的流量就是所有被删除的点之和，只需要用所有点的权值和减去这个值，即可得到我们需要的答案。那么我们只需要能够求这个费用流模型的最小费用最大流即可。

这个费用流模型形式非常简单，它的主干是一条链，所以考虑直接用数据结构维护每条边的流量来处理修改边权的操作。假设求得了当前的最优解，然后修改了 $s\to x$ 的边权，那么不进行任何操作一定仍然是一组合法解，下面我们只需要通过调整流来让解变得更优。由于当前已经满流且流量平衡被满足，所以若考虑最原始的增广费用流的方法，我们只能够增广一些环。由于 $i\to t$ 这些边都流满了，且不会修改这些边，所以增广的环一定形如 $s\to i\to j\to s$，注意和朴素费用流方法一样，这里也可以用到反向边，即可以 $j<i$。显然，只有在增广负环的情况下才会更优，所以一定有 $i=x$ 或 $j=x$。因为若不满足这两点，则这个环与我们修改的边没有关系，那么在修改之前进行增广一定更优，与原来是最优解矛盾。

这样我们就得到了一个暴力的做法，枚举每个 $y$，考察 $s\to x\to y\to s$ 能否增广，若可以则增广并更新答案。下面考虑如何优化。首先需要观察到在处理一次修改的时候，不会同时增广 $s\to x$ 和 $x\to s$，因为若同时增广这两条边，那么把它们拼一起就是和 $x$ 无关的环了。这意味着一次修改我们增广的次数至多是 $2$，那么我们只需要能够快速求出每次增广哪个环最优即可。不妨以 $s\to x\to y\to s$ 为例。若 $y>x$，则只要 $s\to x$ 和 $y\to s$ 有流量就能够增广，那么我们只需要求所有这样的 $y$ 中权值最小的一个即可。若 $y<x$，则除了满足上面的条件以外，还需要额外满足当前 $y\to x$ 这条链上所有边流量均不为 $0$。注意到满足这个条件的 $y$ 形如一段区间，所以也变成求区间权值最小值的问题。

具体地，使用一棵线段树维护每条链上边的流量，则一次增广相当于区间加，而需要支持线段树二分找到第一个/最后一个为 $0$ 的位置。然后使用两棵线段树分别维护所有有流量的正向边和反向边的权值的最大/最小值，在增广时可能会导致一条边被流满，此时将它变为正/负无穷即可，就是一个单点修改，区间查询的线段树。这样就做完了，复杂度 $O(n\log n)$。一个小细节是初始为了保证满流，不需要先跑一遍费用流，而是可以将所有边权值看作 $0$，则此时一个显然的合法解是流 $n$ 次 $s\to i\to t$，费用为 $0$。所以以这个为初始状态，将初始的 $x_i$ 看作修改即可方便地处理这个细节。

[代码](https://atcoder.jp/contests/arc168/submissions/47815130)

---

## 作者：Hanghang (赞：5)

纪念一下第一次补完 ARC 的所有题。

本题解介绍 $O(n\log^2n)$ 做法，需要卡常才能过。

感谢 @Rainbow_qwq 大佬的耐心讲解，拜谢拜谢拜谢。

首先注意到每次操作是前后缀修改，自然想到维护差分数组。

假设当前操作到了 $a_i$，那么差分数组的 $a_i$ 这位加 $2$，然后差分数组全局最小的值大于 $0$ 的地方减 $1$。

注意到我们其实只有维护每次有哪些位置与 $0$ 取了最大值，也就是差分数组减一的位置和其更小的位置。

其他的贡献是简单的，也就是 $\displaystyle\sum_{i=1}^{n} m-2 \times a_i$。

那我也就可以维护一个小根堆，每次插入两个 $a_x$，删除掉小根堆的堆顶并加入答案。

注意到这是个类似贪心的问题，自然想到建图转模拟费用流。

源点向每个点 $i$ 连一条边，流量为 $2$，成本为 $a_i$，$i$ 向 $i+1$ 连一条边，流量为无穷大，成本为 $0$，每个点 $i$ 向汇点连边，流量为 $1$，成本为 $0$。

其实这就是 [P9168 \[省选联考 2023\] 人员调度 ](https://www.luogu.com.cn/problem/P9168) 的链的部分分，大概的做法为：

把 $1$ 看成根，维护每个点的子树还能加多少次。

如果加入一个点之后，这个点到根的每个点都还能加点，那么直接加即可。

否则找到最大的点它不能再加点了，那么就找到里面的最大值，

如果能当前代价小于最大值，那么就直接替换。

修改边权的操作看为先把这个边给删了，然后再加入一个新边，注意到删除不太能做，用线段树分治变插销即可。

代码很丑，将就看看把：

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e6+3,M=(1<<18);
int n,m,Q,tot,la[N],lb[N];
ll res,ans[N];
struct Nod{int x,y;}a[N];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
inline void write(ll X)
{
	int s[20],o=0;
	while(X){s[++o]=X%10;X/=10;}
	if(!o)s[++o]=0;
	while(o)putchar(s[o--]+'0');
	putchar('\n');
}
#define ls (p<<1)
#define rs (p<<1|1)
#define mi ((l+r)>>1)
struct Sgt2
{
	int tr[N],tag[N];
	void Build(int p,int l,int r)
	{
		if(l==r){tr[p]=n-l+1;return;}
		Build(ls,l,mi);Build(rs,mi+1,r);tr[p]=tr[rs];
	}
	void Upd(int R,int p,int l,int r,int d)
	{
		if(r<=R){tr[p]+=d;tag[p]+=d;return;}
		Upd(R,ls,l,mi,d);
		if(R>mi)Upd(R,rs,mi+1,r,d);
		tr[p]=min(tr[ls],tr[rs])+tag[p];
	}
	inline int Ask(int p,int l,int r,int w)
	{
		while(l<r)
		{
			w+=tag[p];
			tr[rs]+w==0?(l=mi+1,p=rs):(r=mi,p=ls);
		}
		return l;
	}
	int Find(int R,int p,int l,int r,int w)
	{
		if(r<=R)return tr[p]+w==0?Ask(p,l,r,w):-1;
		w+=tag[p];
		if(R<=mi)return Find(R,ls,l,mi,w);
		int x=Find(R,rs,mi+1,r,w);
		return x==-1?Find(R,ls,l,mi,w):x;
	}
}T2;
struct Sgt3
{
	int num[N];
	struct cmp
	{
		inline bool operator ()(const int &x,const int &y){return a[x].y!=a[y].y?a[x].y<a[y].y:x<y;}
	};
	struct PQ
	{
		priority_queue<int,vector<int>,cmp> q1,q2;
		inline void Insert(int x){q1.push(x);}
		inline void Erase(int x){q2.push(x);}
		inline int Top()
		{
			while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();
			return q1.empty()?0:q1.top();
		}
	}pq[N];
	inline int Cmp(int x,int y){return a[x].y>a[y].y?x:y;}
	inline void Upd(int p,int u){for(num[p+=M]=u,p>>=1;p;p>>=1)num[p]=Cmp(num[ls],num[rs]);}
	inline int Ask(int l)
	{
		int s=0,r=n;
	    for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
		{
		    if(~l&1)s=Cmp(s,num[l^1]);
		    if(r&1)s=Cmp(s,num[r^1]);
	    }
	    return s;
	}
	inline void Add(int id){int z=a[id].x;pq[z].Insert(id);Upd(z,pq[z].Top());}
	inline void Del(int id){int z=a[id].x;pq[z].Erase(id);Upd(z,pq[z].Top());}
}T3;
struct Sgt1
{
	vector<int>now[N];
	vector<Nod>cur[N];
	inline void Addnew(int id){res+=a[id].y;T3.Add(id);T2.Upd(a[id].x,1,1,n,-1);}
	inline void Delnew(int id){res-=a[id].y;T3.Del(id);T2.Upd(a[id].x,1,1,n,1);}
	inline Nod Add(int id)
	{
		int x=T2.Find(a[id].x,1,1,n,0);
		if(x==-1){Addnew(id);return {id,-1};}
		int mx=T3.Ask(x);
		if(a[id].y>=a[mx].y)return {-1,-1};
		Addnew(id);Delnew(mx);return {id,mx}; 
	}
	inline void Del(Nod t)
	{
		if(t.x!=-1)Delnew(t.x);
		if(t.y!=-1)Addnew(t.y);
	}
	void Upd(int L,int R,int p,int l,int r,int u)
	{
		if(L<=l&&r<=R){now[p].push_back(u);return;}
		if(L<=mi)Upd(L,R,ls,l,mi,u);
		if(R>mi)Upd(L,R,rs,mi+1,r,u);
	}
	void Ans(int p,int l,int r)
	{
		for(int x:now[p])cur[p].push_back(Add(x)),cur[p].push_back(Add(x));
		if(l==r)ans[l]+=res;
		else Ans(ls,l,mi),Ans(rs,mi+1,r);
		for(int i=(int)cur[p].size()-1;i>=0;i--)Del(cur[p][i]); 
	}
}T1; 
int main()
{
	n=read();m=read();Q=read();T2.Build(1,1,n);
	for(int i=1,y;i<=n;i++)y=read(),a[++tot]={i,y},lb[i]=tot,ans[0]+=m-2*y;
	for(int i=1,x,y;i<=Q;i++)
	{
	    x=read();y=read();T1.Upd(la[x],i-1,1,0,Q,lb[x]);ans[i]=ans[i-1];ans[i]-=m-2*a[lb[x]].y;
		a[++tot]={x,y};lb[x]=tot;la[x]=i;ans[i]+=m-2*y;
	}
	for(int i=1;i<=n;i++)T1.Upd(la[i],Q,1,0,Q,lb[i]);
	T1.Ans(1,0,Q);
	for(int i=1;i<=Q;i++)write(ans[i]);
}
```

我很乐意解答关于此题解的任何疑惑，欢迎与我交流。

---

## 作者：masterhuang (赞：2)

> 有长为 $N$ 的操作序列 $x = (x_1, x_2, \dots, x_N)$，对 $f(x)$ 定义如下：
>
> 有长为 $M$ 初始全 $0$ 的序列 $y$，对于 $i = 1, 2, \dots, N$ 依次进行如下操作。
>
> - $\forall j\le x_i,y_j\gets \max(y_j-1,0)$
> - $\forall j>x_i,y_j\gets y_j+1$
>
> $f(x)$ 为依次进行所有操作后的 $\sum y_i$。
>
> 现在给出初始的操作序列 $x$，有 $Q$ 次修改操作，将 $x_i$ 修改为 $k$，每次操作后输出当前的 $f(x)$。
>
> $1\le N,M,Q\le 2.5\times 10^5,1\le x_i,k\le M$。

这篇主要讲如何自然转换模拟费用流。

- 可以发现一次操作相当于先对 $x_i < j \le m$ 的 $a_j$ 加上 $2$，再对全局做 $a_i = \max(0, a_i - 1)$ 的操作。

记 $a_0 = 0$，则容易发现整个操作的过程中，$a_i$​ 一定单调不降。

于是差分，令 $d=a_i-a_{i-1}$，则 $ans=\sum d_i(m+1-i)$。

这启发我们每次给可重集加入 $d_i$ 个 $m+1-i$，最终要求 $S$ 集合内所有数的和。

- 考虑 $+2$，相当于 $d_{x_i+1}$ 加 $2$，于是相当于往 $S$ 加入**两个** $m-x_i$​。

- 考虑 $-1$，由于钦定 $a_0$ 始终为 $0$，于是相当于第一个非 $0$ 的 $d_i$ 减 $1$，考虑 $d$ 以及加入的过程，发现相当于**删除集合内最大值！**

于是转化要维护如下问题：

> 初始有空可重集，每次加两个 $m-x_i$，删除集合内最大值，最终求集合内数的和。

考虑经典 **trick**，把删除最大值变成删除任意数，最终求最小可能集合内数的和。

此时就很好建立费用流了（源汇为 $S,T$，括号内前者表示流量，后者表示费用）：

$\forall i,(S\to i;2,m-x_i),(i\to T;1,0),\forall i<j,(i\to j,\infty,0)$

其中 $i\to j$ 的边表示一个数在它加入的时刻后被删除，需要有桥梁连过去。

而这类边显然能拆为 $(i\to i+1,\infty,0)$。

---

然后考虑模拟这个费用流。

显然我们找到一个合法的最大流，然后不断找环增广。

把初始 $x$ 看成从 $0$ 开始修改。

对于修改 $x$，考虑一定是增广包含 $x$ 的环。

$S\to x\to y\to S(\text{or}\ S\to y\to x\to S)$，取决于修改大了还是小了。

其中分讨 $y<x$ 和 $y>x$​。考虑左侧环和右侧环，线段树维护可达点，和区间最值即可。

复杂度 $O(n\log n)$。

[code](https://atcoder.jp/contests/arc168/submissions/66660542)

---

## 作者：qczrz6v4nhp6u (赞：2)

### Solution

一个简单的观察是 $y$ 单调不降。类似 slope trick，我们考虑维护可重集 $S$，满足 $S$ 中有恰好 $y_{i+1}-y_{i}$ 个 $i$，则一次操作相当于加入 $2$ 个 $x_i$ 并删除 $S$ 的最小值。

但是这个形式的问题很难上数据结构。发现难点主要在于我们无法得知每个时刻 $S$ 的最小值，考虑适当放宽限制。

思考后发现我们实际上只需要保证第 $i$ 次操作后 $S$ 内剩余 $i$ 个点且 $S$ 对应的 $\sum y_i$ 最小。发现可以使用费用流刻画：

- $s\to i$ 连一条流量为 $2$，费用为 $m-x_i$ 的边；
- $i\to i-1$ 连一条流量为 $+\infty$，费用为 $0$ 的边；
- $i\to t$ 连一条流量为 $1$，费用为 $0$ 的边。

其中 $s$ 为源点，$t$ 为汇点，答案即为 $s$ 到 $t$ 的最小费用最大流。类似 [[省选联考 2023] 人员调度
](https://www.luogu.com.cn/problem/P9168)，线段树维护反向边并时间分治即可做到 $O(n\log^2 n)$。

但是本题并没有插入删除，考虑更为优秀的做法。

注意到我们实际上相当于先求出一个合法的最大流，再在上面通过若干个环增广费用。合法的最大流是易求的：直接 $s\to i\to t$ 显然为合法的最大流。对于增广环，分 $x_i$ 变大与变小两种情况讨论：

- $x_i$ 变大。此时费用变小，则 $s\to i$ 的边在增广环中应为正向。
- $x_i$ 变小。此时费用变大，则 $s\to i$ 的边在增广环中应为反向。

然后每次修改都线段树增广即可。时间复杂度 $O(n\log n)$。[submission](https://atcoder.jp/contests/arc168/submissions/59131655)。

---

## 作者：EuphoricStar (赞：2)

貌似是第三道问号题？感觉前面这个转化不是人能想到的。。。

考虑维护 $y$ 的差分序列。更进一步地，我们类比 slope trick，维护一个**可重集**，里面有 $y_{i + 1} - y_i$ 个 $i$（为了方便我们让每次操作时 $y_{m + 1}$ 加 $1$）。那么一次操作就相当于，插入两个 $a_i$，删去最小值。

考虑统计答案。如果不考虑 $\max$ 操作就是 $\sum\limits_{i = 1}^n m - 2a_i$。考虑 $\max$ 操作，相当于每次有最小值个数避免了减 $1$。所以答案每次再加上最小值。

于是求 $f(a)$ 可以转化为：从左往右遍历 $a$，往可重集中加入 $2$ 个 $a_i$，把此时可重集的最小值累加进答案，再删除最小值。

考虑倒着操作，转化为从右往左遍历 $a$，往可重集中加入 $2$ 个 $a_i$，删除可重集中的**最大值**。最后可重集中的数的和就是答案。

这样就转化成了一个比较标准的 [P9168 [省选联考 2023] 人员调度](https://www.luogu.com.cn/problem/P9168) 的链的问题了。简单讲一下这个问题的做法。

考虑初始时一个数也没有，然后我们在一些位置加数。加数的同时维护最后还在可重集中的数。

设当前要加的数的位置是 $u$，数值是 $x$。我们找到 $u$ 的祖先即 $[1, u]$ 中最后一个满的位置 $v$（一个点 $v$ 满了指 $v$ 的子树即 $[v, n]$ 中数的个数 $= sz_v = n - v + 1$）。

如果 $v$ 不存在我们放心把这个数加入即可，因为不会造成 pop。

否则，我们找到 $v$ 的子树中的最大值，设其权值为 $w$。

若 $x > w$，那么 $x$ 加入后在 $v$ 位置一定会被 pop，所以不用加入。

否则，因为 $w$ 不会被 pop，所以 $x$ 也不会被 pop。于是我们直接用 $x$ 替换 $w$ 即可。

注意到我们不能删除，考虑线段树分治变删除为撤销即可。

实现时需要一棵线段树维护每个位置的 $sz$ 减去其子树内数的个数，一棵线段树维护子树中所有数的最大值，配合 $n$ 个可重集维护每个点上的数。

时间复杂度 $O(n \log^2 n)$，需要卡常。卡常主要两点，第一棵线段树不要用 pair 维护最小值及其位置，改成线段树上二分；注意到可重集中至多两个元素，所以可以手写。

[卡常前的代码](https://atcoder.jp/contests/arc168/submissions/48877269)，[卡常后的代码](https://atcoder.jp/contests/arc168/submissions/48880842)。

---

## 作者：LinkyChristian (赞：2)

发现数列单调递增，考虑差分。差分后的 $d_i$ 会被贡献 $m-i$ 次，因此我们将 $d_i$ 看做是有 $d_i$ 个值为 $m-i$ 的数，这些数构成一个可重集合，每次操作就是加入两个 $m-x_i$，然后删掉最大的数。最后剩下的所有数的和就是我们要的答案。 

考虑构建费用流。对每个操作我们设一个点 $i$ ，从源点 $s$ 向这 $n$ 个点连容量为 $2$ ，费用为 $m-x_i$ 的边，从 $i$ 向 $i+1$ 连容量为 $INF$ ，费用为 $0$ 的边，从 $i$ 向 $t$ 连容量为 $1$ ，费用为 $0$ 的边。对这个图跑最大费用最大流，得到的就是被删去的数的和，用一开始的和减去跑出来的费用就是答案。

我们考虑先构建一个合法的流然后增广。合法的流很容易构建，直接把 $s\rightarrow i \rightarrow t$ 流满就行。修改一个位置 $p$ 后，显然只有两种可能的增广路径，一种是修改后的值比原先的值小，有可能出现 $s\rightarrow x \rightarrow p \rightarrow s (x<p)$ 与 $s \rightarrow y \rightarrow p  \rightarrow s (p<y)$，另一种是修改后的值比原先的值大，有可能出现 $s\rightarrow p \rightarrow x \rightarrow s (x<p)$ 与 $s\rightarrow p \rightarrow y \rightarrow s (p<y)$。两种增广都最多发生两次。考虑模拟费用流，我们需要维护的有：（$s\rightarrow i$）未满流的区间最大值、有流的区间最小值、区间链上的边的流量最小值。最后一个是因为在链上流反向边的时候需要保证链上的边流量都不为空。一个范围是 $1\sim n$ ，另一个是 $1 \sim n-1$，于是开两棵线段树维护即可。注意特判 $n=1$ 。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500010
#define ls k*2
#define rs k*2+1
#define mid (l+r)/2
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,q,a[N],b[N],f[N],ans;
const int INF=0x3f3f3f3f3f3f3f3fll;
int s[N<<2],tag[N<<2];
pii mn[N<<2],mx[N<<2];
void pushup(int k) {mn[k]=min(mn[ls],mn[rs]),mx[k]=max(mx[ls],mx[rs]);}
void build(int k,int l,int r) {
	if(l==r) return mn[k]={0,l},mx[k]={0,l},void();
	build(ls,l,mid),build(rs,mid+1,r),pushup(k);
}
void pushdown(int k) {
	s[ls]+=tag[k],tag[ls]+=tag[k],s[rs]+=tag[k],tag[rs]+=tag[k],tag[k]=0;
}
void update(int pos,int k=1,int l=1,int r=n) {
	if(l==r) return mn[k]={f[l]>0?a[l]:INF,l},mx[k]={f[l]<2?a[l]:-INF,l},void();
	if(pos<=mid) update(pos,ls,l,mid);
	else update(pos,rs,mid+1,r);
	pushup(k);
}
void modify(int L,int R,int x,int k=1,int l=1,int r=n-1) {
	if(L>R) return ;
	if(L<=l&&r<=R) return s[k]+=x,tag[k]+=x,void();
	pushdown(k);
	if(L<=mid) modify(L,R,x,ls,l,mid);
	if(R>mid) modify(L,R,x,rs,mid+1,r);
	s[k]=min(s[ls],s[rs]);
}
int query(int L,int R,int opt,int k=1,int l=1,int r=n-1) {
	if(L>R) return 0;
	if(l==r) return l;
	pushdown(k);
	int res=0;
	if(!opt) {
		if(L<=mid&&!s[ls]) res=query(L,R,opt,ls,l,mid);
		if(res) return res;
		if(R>mid&&!s[rs]) return query(L,R,opt,rs,mid+1,r);
	} else {
		if(R>mid&&!s[rs]) res=query(L,R,opt,rs,mid+1,r);
		if(res) return res;
		if(L<=mid&&!s[ls]) return query(L,R,opt,ls,l,mid);
	} return 0; 
}
pii qmn(int L,int R,int k=1,int l=1,int r=n) {
	if(L>R) return {INF,0};
	if(L<=l&&r<=R) return mn[k];
	pii res={INF,0};
	if(L<=mid) res=min(res,qmn(L,R,ls,l,mid));
	if(R>mid) res=min(res,qmn(L,R,rs,mid+1,r));
	return res;
}
pii qmx(int L,int R,int k=1,int l=1,int r=n) {
	if(L>R) return {-INF,0};
	if(L<=l&&r<=R) return mx[k];
	pii res={-INF,0};
	if(L<=mid) res=max(res,qmx(L,R,ls,l,mid));
	if(R>mid) res=max(res,qmx(L,R,rs,mid+1,r));
	return res;
}
void zg(int pos,int las) {
//	if(pos==2) printf("!%lld\n",ans);
	if(a[pos]>las) { 
		if(f[pos]==2) return ;
		pii s1=qmn(pos+1,n);
		int t,lim=(t=query(1,pos-1,1))?t:0;
		pii s2=qmn(lim+1,pos-1);
		if(s1.fi>=a[pos]&&s2.fi>=a[pos]) return ;
		if(s1<s2) {
			f[pos]++,f[s1.se]--,ans-=a[pos]-a[s1.se];
			update(pos),update(s1.se),modify(pos,s1.se-1,1);
		} else {
			f[pos]++,f[s2.se]--,ans-=a[pos]-a[s2.se];
			update(pos),update(s2.se),modify(s2.se,pos-1,-1);
		}
	} else {
		if(f[pos]==0) return ;
		pii s1=qmx(1,pos-1);
		int t,lim=(t=query(pos,n,0))?t:n;
		pii s2=qmx(pos+1,lim);
		if(s1.fi<=a[pos]&&s2.fi<=a[pos]) return ;
		if(s1>s2) {
			f[pos]--,f[s1.se]++,ans-=a[s1.se]-a[pos];
			update(pos),update(s1.se),modify(s1.se,pos-1,1);
		} else {
			f[pos]--,f[s2.se]++,ans-=a[s2.se]-a[pos];
			update(pos),update(s2.se),modify(pos,s2.se-1,-1);
		}
	}
}
main() {
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>q;
	for(int i=1; i<=n; i++) cin>>b[i],f[i]=1;
	if(n==1) {
		while(q--) {int x,y; cin>>x>>y; printf("%d\n",m-y);}
		return 0;
	}
	build(1,1,n);
	for(int i=1; i<=n; i++) {
		a[i]=m-b[i],update(i),ans+=(2-f[i])*a[i];
		zg(i,0),zg(i,0);
	}
	while(q--) {
		int x,y,las; cin>>x>>y; las=a[x];
		a[x]=m-y,update(x),ans+=(2-f[x])*(a[x]-las);
		zg(x,las),zg(x,las);
		printf("%lld\n",ans);
	}
} 
```


---

