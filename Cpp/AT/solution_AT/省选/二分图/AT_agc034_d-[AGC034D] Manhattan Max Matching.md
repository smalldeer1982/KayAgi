# [AGC034D] Manhattan Max Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_d

すぬけくんは、二次元平面上に赤いボールと青いボールを置いて遊んでいます。

すぬけくんはまず、赤いボールを置く操作を $ N $ 回行いました。 $ i $ 回目の操作では、座標 $ (RX_i,RY_i) $ に $ RC_i $ 個の赤いボールを置きました。 すぬけくんは次に、青いボールを置く操作を $ N $ 回行いました。 $ i $ 回目の操作では、座標 $ (BX_i,BY_i) $ に $ BC_i $ 個の青いボールを置きました。 ここで、すぬけくんが置いた赤いボールの個数の総和と青いボールの個数の総和は等しいです。 つまり、$ \sum_{i=1}^{N}\ RC_i\ =\ \sum_{i=1}^{N}\ BC_i $ です。 以後、この値を $ S $ とおきます。

すぬけくんはこれから、赤いボールと青いボールのペアを $ S $ 個作ろうとしています。 どのボールも、ちょうど $ 1 $ つのペアに属するようにします。 ここで、座標 $ (rx,ry) $ にある赤いボールと座標 $ (bx,by) $ にある青いボールのペアのスコアを、 $ |rx-bx|\ +\ |ry-by| $ と定義します。

すぬけくんは、ペアのスコアの総和を最大化したいです。 すぬけくんのために、ペアのスコアの総和の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 0\ \leq\ RX_i,RY_i,BX_i,BY_i\ \leq\ 10^9 $
- $ 1\ \leq\ RC_i,BC_i\ \leq\ 10 $
- $ \sum_{i=1}^{N}\ RC_i\ =\ \sum_{i=1}^{N}\ BC_i $
- 入力される値はすべて整数である。

### Sample Explanation 1

座標 $ (0,0) $ に置いてある赤いボールと座標 $ (2,2) $ に置いてある青いボールをペアにすると、 そのスコアは $ |0-2|\ +\ |0-2|=4 $ です。 また、座標 $ (3,2) $ に置いてある赤いボールと座標 $ (5,0) $ に置いてある青いボールをペアにすると、 そのスコアは $ |3-5|\ +\ |2-0|=4 $ です。 この $ 2 $ つのペアを作ると、スコアの総和は $ 8 $ になり、これが最大です。

### Sample Explanation 2

同じ座標に複数回操作を行うこともあります。

## 样例 #1

### 输入

```
2
0 0 1
3 2 1
2 2 1
5 0 1```

### 输出

```
8```

## 样例 #2

### 输入

```
3
0 0 1
2 2 1
0 0 2
1 1 1
1 1 1
3 3 2```

### 输出

```
16```

## 样例 #3

### 输入

```
10
582463373 690528069 8
621230322 318051944 4
356524296 974059503 6
372751381 111542460 9
392867214 581476334 6
606955458 513028121 5
882201596 791660614 9
250465517 91918758 3
618624774 406956634 6
426294747 736401096 5
974896051 888765942 5
726682138 336960821 3
715144179 82444709 6
599055841 501257806 6
390484433 962747856 4
912334580 219343832 8
570458984 648862300 6
638017635 572157978 10
435958984 585073520 7
445612658 234265014 6```

### 输出

```
45152033546```

# 题解

## 作者：justin_cao (赞：14)

首先显然可以想到暴力建出二分图之后跑费用流，但是边数有$O(n^2)$条，比较爆炸，考虑优化。

可以发现，曼哈顿距离有一个非常好的性质，就是把绝对值拆开，一共有四种情况，这四种情况的最大值一定是这个曼哈顿距离的值。

具体地说，就是：
$$
|x_1-x_2|+|y_1-y_2|=max\{ 
x_1-x_2+y_1-y_2,
x_1-x_2-y_1+y_2,
-x_1+x_2+y_1-y_2,
-x_1+x_2-y_1+y_2
\}
$$
那么可以将两个点独立地来看，也就是：
$$
|x_1-x_2|+|y_1-y_2|=max\{
(x_1+y_1)+(-x_2-y_2),
(x_1-y_1)+(-x_2+y_2),
(-x_1+y_1)+(x_2-y_2),
(-x_1-y_1)+(x_2+y_2)
\}
$$
那么既然可以拆开来看的话，就可以不用两两连边了，在左右两排点中间开$4$个新点，然后从左边到它，从它到左边分别连上$4$种边（记得按顺序），然后直接跑费用流即可，边数被降到$O(n)$级别、

**但是需要注意的是，曼哈顿距离这个性质不适用于最小值**。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 1010
#define inf 1000000007
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,p1,p2,p3,p4,s,t;
int head[maxn*2],nxt[maxn*20],to[maxn*20],c[maxn*20],v[maxn*20],tot=1;
void add(int x,int y,int z,int u)
{
    ++tot;
    nxt[tot]=head[x];
    head[x]=tot;
    to[tot]=y;
    c[tot]=z;
    v[tot]=u;
}
void addx(int x,int y,int z,int u)
{
    add(x,y,z,u);
    add(y,x,0,-u);
}
ll ans;
ll dis[maxn*2];
int pre[maxn*2],pre_num[maxn*2],vis[maxn*2];
queue<int>q;
int spfa()
{
    for(int i=1;i<=t;i++)  dis[i]=-1e16;
    q.push(s);dis[s]=0;vis[s]=1;
    while(q.size())
    {
        int now=q.front();q.pop();vis[now]=0;
        for(int i=head[now];i;i=nxt[i])
        {
            if(dis[to[i]]<dis[now]+v[i]&&c[i])
            {
                dis[to[i]]=dis[now]+v[i];
                pre[to[i]]=now;
                pre_num[to[i]]=i;
                if(!vis[to[i]])  q.push(to[i]),vis[to[i]]=1;
            }
        }
    }
    if(dis[t]==-1e16)  return 0;
    int di=inf;
    for(int i=t;i!=s;i=pre[i])  di=min(di,c[pre_num[i]]);
    for(int i=t;i!=s;i=pre[i])  c[pre_num[i]]-=di,c[pre_num[i]^1]+=di;
    ans+=dis[t]*di;
    return di;
}
int main()
{
    n=read();p1=2*n+1;p2=p1+1;p3=p2+1;p4=p3+1;s=p4+1;t=s+1;
    for(int i=1;i<=n;i++)
    {
        int x=read(),y=read(),z=read();
        addx(s,i,z,0);
        addx(i,p1,inf,x+y);
        addx(i,p2,inf,x-y);
        addx(i,p3,inf,-x+y);
        addx(i,p4,inf,-x-y);
    }
    for(int i=1;i<=n;i++)
    {
        int x=read(),y=read(),z=read();
        addx(i+n,t,z,0);
        addx(p1,i+n,inf,-x-y);
        addx(p2,i+n,inf,-x+y);
        addx(p3,i+n,inf,x-y);
        addx(p4,i+n,inf,x+y);
    }
    while(spfa()){};
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Aleph1022 (赞：6)

注意到最大 Manhattan 距离可以直接拆符号，从 $4$ 种可能的符号中取 $\max$。

对每个红点建点 $R_1, \dots, R_N$，对每个蓝点建点 $B_1, \dots, B_N$，对每一种符号建点 $F_1, F_2, F_3, F_4$。

 - 对于 $i = 1,\dots,N$，连边 $(S, R_i, RC_i, \infty), (B_i, T, BC_i, \infty)$。

 - 对于 $i = 1,\dots,N$，连边 $(R_i, F_1, \infty, RX_i+RY_i), (F_1, B_i, \infty, -BX_i-BY_i)$。

 - 对于 $i = 1,\dots,N$，连边 $(R_i, F_2, \infty, RX_i-RY_i), (F_2, B_i, \infty, -BX_i+BY_i)$。

 - 对于 $i = 1,\dots,N$，连边 $(R_i, F_3, \infty, -RX_i+RY_i), (F_3, B_i, \infty, BX_i-BY_i)$。

 - 对于 $i = 1,\dots,N$，连边 $(R_i, F_4, \infty, -RX_i-RY_i), (F_4, B_i, \infty, BX_i+BY_i)$。

以 $S, F_{1, 2, 3, 4}, T$ 为关键点，讨论两两之间（不经过其他关键点）的最短路：

 - $S \to F_j$：为一个未匹配的红点选择第 $j$ 种符号。

 - $F_j \to T$：为一个未匹配的蓝点选择第 $j$ 种符号。

 - $F_j \to F_k$：将一个选择第 $j$ 种符号的红点改成选择第 $k$ 种符号，或将一个选择第 $k$ 种符号的蓝点改成选择第 $j$ 种符号。

可以用 $20$ 个堆维护，增广时可以直接在关键点之间做 Bellman-Ford。时间复杂度是大常数 $O(N \log N)$。

---

## 作者：OldDriverTree (赞：4)

这是一篇模拟费用流做法的题解。

# Solution

首先考虑如何建图，一个暴力的做法是对于每个红球 $x$，连一条 $S$ 到 $x$ 的边，容量为球的个数，费用为 $0$，对于每个蓝球 $y$，连一条 $x$ 到 $T$ 的边，容量为球的个数，费用为 $0$，对于每对 $(x,y)$，连一条 $x$ 到 $y$ 的边，容量为 $+\infty$，费用为两个点的曼哈顿距离，然后直接跑最大费用最大流。

然后这样有 $O(n)$ 个点，$O(n^2)$ 条边，显然是爆炸的。

[提交记录](https://atcoder.jp/contests/agc034/submissions/62706534)。

然后考虑优化建图，众所周知，$\vert x\vert=\max(x,-x)$，所以我们可以把两个点的曼哈顿距离拆成四个只与 $x$ 有关和只与 $y$ 有关的和的最大值，因此我们考虑新建四个点，表示四种情况，令这四个点分别为 $A,B,C,D$。然后新后的建图方式就为 $S$ 向 $x$ 连边，容量为球的个数，费用为 $0$，$x$ 分别向 $A,B,C,D$ 连边，费用分别为四种情况的值，$A,B,C,D$ 分别向 $y$ 连边，费用也为四种情况的值，但是注意要和 $A,B,C,D$ 向 $x$ 连边的费用符号相反，$y$ 再向 $T$ 连边，容量为球的个数，费用为 $0$。

此时就只有 $O(n)$ 个点和 $O(n)$ 条边，已经能过了。

[提交记录](https://atcoder.jp/contests/agc034/submissions/62680955)。

但是还可以进一步优化，考虑模拟 $\text{EK}$ 算法的过程，每次增广一条最短路，我们令 $S,T,A,B,C,D$ 为关键点，然后不难发现 $S$ 到 $T$ 的最短路上每次是从一个关键点到 $x$ 或 $y$ 再到另一个关键点。

因此我们考虑对于每对关键点 $(p,q)$ 之间都开一个堆维护对于所有可行的非关键点，$p$ 到这个非关键点再到 $q$ 的路径长度和，这样需要开 $20$ 个堆，然后每次增广一条最短路就在 $6$ 个关键点间求一下最长路，并更新经过的球和以及对应的堆。

令 $m$ 为球的总数，则时间复杂度为 $O(m\log n)$，虽然常数比较大，但是能抢到洛谷上的最优解。

[提交记录](https://atcoder.jp/contests/agc034/submissions/62706205)。

还有一道思路类似的题是 [CF730I](https://www.luogu.com.cn/problem/CF730I)。

---

## 作者：NOI_Winner (赞：2)

前置知识：费用流。

本题应该不难看出是一个费用流模型，但用常规的建模方法会发现边数达到了 $10^6$ 量级，因此需考虑优化建图。

由于是曼哈顿距离，我们可以考虑将两点间的距离转化为两点到另一点距离的差。设 $A(0,0),B(10^9,0),C(0,10^9),D(10^9,10^9)$，假设有 $X,Y$ 两点，$d(N,M)$ 表示 $N,M$ 两点的曼哈顿距离，则 $d(X,Y)=\max(d(A,X)-d(A,Y),d(B,X)-d(B,Y),d(C,X)-d(C,Y),d(D,X)-d(D,Y))$，可以通过这个结论优化建图。

建立源点与汇点，由源点向每一组红球连边，容量为该位置红球个数，费用为 $0$。由每一组蓝球向汇点连边，容量为该位置蓝球个数，费用为 $0$。建立四个中间节点，分别对应 $A,B,C,D$ 四个点。由每一组红球向这四个点分别连一条容量为 $+\infty$，费用为两点曼哈顿距离的边，由这四个点向每一组蓝球连一条容量为 $+\infty$，费用为两点曼哈顿距离的**相反数**的边。建完图后跑最大费用最大流就行了。

代码示例：
```cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

using ll = long long;
constexpr int maxn = 1000, inf = 0x3f3f3f3f, maxv = 1000000000;
constexpr ll inf2 = 0xcfcfcfcfcfcfcfcf;
int head[3 * maxn + 5], vert[20 * maxn + 5], nxt[20 * maxn + 5], edge[20 * maxn + 5], cost[20 * maxn + 5], tot = 1;
int now[3 * maxn + 5];
bool v[3 * maxn + 5];
ll d[3 * maxn + 5], ans;

inline void add_edge(int x, int y, int z, int c)
{
	vert[++tot] = y;
	edge[tot] = z;
	cost[tot] = c;
	nxt[tot] = head[x];
	head[x] = tot;
}

inline void add(int x, int y, int z, int c)
{ add_edge(x, y, z, c); add_edge(y, x, 0, -c); }

bool spfa()
{
	queue<int> q; q.push(0);
	memset(d, 0xcf, sizeof(d));
	d[0] = 0; now[0] = head[0];
	
	while (q.size())
	{
		int x = q.front(); q.pop(); v[x] = false;
		for (int i = head[x]; i; i = nxt[i])
		{
			int y = vert[i], z = edge[i], c = cost[i];
			if (z && d[x] + c > d[y])
			{
				d[y] = d[x] + c; now[y] = head[y];
				if (!v[y])
				{ v[y] = true; q.push(y); }
			}
		}
	}
	return inf2 != d[1];
}

int dinic(int x, int flow)
{
	if (1 == x || !flow)
		return flow;
	
	int rest = flow; v[x] = true;
	for (int& i = now[x]; i && rest; i = nxt[i])
	{
		int y = vert[i], z = edge[i], c = cost[i];
		if (z && !v[y] && d[x] + c == d[y])
		{
			int k = dinic(y, min(z, rest));
			if (!k) continue;
			edge[i] -= k; edge[i ^ 1] += k;
			rest -= k; ans += 1ll * k * c;
		}
	}
	v[x] = false;
	return flow - rest;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x, y, c; cin >> x >> y >> c;
		add(0, i + 5, c, 0);
		add(i + 5, 2, c, x + y);
		add(i + 5, 3, c, maxv - x + y);
		add(i + 5, 4, c, x + maxv - y);
		add(i + 5, 5, c, 2 * maxv - x - y);
	}
	for (int i = 1; i <= n; i++)
	{
		int x, y, c; cin >> x >> y >> c;
		add(n + i + 5, 1, c, 0);
		add(2, n + i + 5, c, -x - y);
		add(3, n + i + 5, c, x - maxv - y);
		add(4, n + i + 5, c, y - maxv - x);
		add(5, n + i + 5, c, x + y - 2 * maxv);
	}
	
	int maxflow = 0, flow;
	while (spfa())
		while ((flow = dinic(0, inf)))
			maxflow += flow;
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：Acoipp (赞：2)

## 分析

显然一种暴力就是连接 $O(n^2)$ 条边，但是因为最大费用最大流时间耗费过多，每次都要遍历所有的边，导致时间爆炸，所以考虑优化。

曼哈顿距离有一个很好的性质，对于点 $i,j$ 的曼哈顿距离我们有四种可能，这四种可能如果代入值去计算，最大的那个恰好就是真实的那个。

这四种可能分别是：

$$
x_i-x_j+y_i-y_j,x_i-x_j+y_j-y_i,x_j-x_i+y_i-y_j,x_j-x_i+y_j-y_i 
$$

如果我们将 $i=(5,2),j=(4,6)$ 代入计算，答案分别是 $-3,5,-5,3$。

恰好 $5$ 就是真实的 $i,j$ 之间的曼哈顿距离。

联系到费用流，因为最大费用最大流会自动选择权值较大的那条边，所以我们如果四条边都连接，那么他会自动选择正确的那条，所以我们可以直接建图。

大概就是建立四个虚点，代表上面的四种情况，然后红球向这四个虚点连边，这四个虚点向蓝球连边，边权是上面四个式子拆出来之后对应的红球的权值和蓝球的权值。然后红球蓝球和源点、汇点之间的边按照暴力的方式连即可。（流量就不用说了，很显然）


最后跑最大费用最大流即可，点数 $O(n)$，边数也降到了 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long 
#define N 200005 
using namespace std;
ll n,m,i,j,k,K,s,t,inf,x,y,z,dis[N],ne[N],la[N],to[N],val[N],w[N],vis[N],viss[N],tot=1,ans1,ans2,temp;
ll id1[N],id2[N],id3,id4,id5,id6,rx[N],ry[N],rc[N],bx[N],by[N],bc[N];
queue<ll> q;
inline void merge(ll x,ll y,ll z,ll c){
	tot++,ne[tot] = la[x],la[x] = tot,to[tot] = y,val[tot] = z,w[tot] = c;
	tot++,ne[tot] = la[y],la[y] = tot,to[tot] = x,val[tot] = 0,w[tot] = -c;
}
bool spfa(){
	for(ll i=0;i<inf;i++) dis[i]=-2e18;
	q.push(s);
	dis[s]=0;
	while(q.size()){
		ll tmp = q.front();
		q.pop();
		vis[tmp] = 0;
		for(ll i=la[tmp];i;i=ne[i]){
			if(val[i]>0&&dis[to[i]]<dis[tmp]+w[i]){
				dis[to[i]] = dis[tmp]+w[i];
				if(!vis[to[i]]) vis[to[i]]=1,q.push(to[i]);
			}
		}
	}
	return dis[t]>=-1e18;
}
ll dfs(ll x,ll step){
	if(x==t) return step;
	viss[x] = 1;
	ll used = 0;
	for(ll i=la[x];i;i=ne[i]){
		if(dis[x]+w[i]==dis[to[i]]&&val[i]>0&&!viss[to[i]]){
			ll temp = dfs(to[i],min(val[i],step-used));
			val[i] -= temp,val[i^1] += temp,used += temp;
			if(used==step) return used;
		}
	}
	return used;
}
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	ios::sync_with_stdio(false);
	s=0,t=1,inf=2;
	id3=inf++,id4=inf++,id5=inf++,id6=inf++;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>rx[i]>>ry[i]>>rc[i],id1[i]=inf++,merge(s,id1[i],rc[i],0);
		merge(id1[i],id3,1e18,rx[i]+ry[i]);
		merge(id1[i],id4,1e18,rx[i]-ry[i]);
		merge(id1[i],id5,1e18,-rx[i]-ry[i]);
		merge(id1[i],id6,1e18,-rx[i]+ry[i]);
	}
	for(i=1;i<=n;i++){
		cin>>bx[i]>>by[i]>>bc[i],id2[i]=inf++,merge(id2[i],t,bc[i],0);
		merge(id3,id2[i],1e18,-bx[i]-by[i]);
		merge(id4,id2[i],1e18,-bx[i]+by[i]);
		merge(id5,id2[i],1e18,bx[i]+by[i]);
		merge(id6,id2[i],1e18,bx[i]-by[i]);
	}
	while(spfa()){
		for(i=0;i<inf;i++) viss[i]=0;
		temp=dfs(s,1e18);
		ans1+=temp,ans2+=temp*dis[t];
	}
	cout<<ans2<<endl;
	return 0;
}
/*
Input:
3 4 2
0 1 1
1 2 1
2 3 100
0 3 1

Output:
3
*/
```

---

## 作者：pomelo_nene (赞：2)

显然红球只能匹配蓝球，所以说这是一个二分图带权匹配以及有流量限制（其实也可以拆开其实一样，反正只有 $10$），考虑费用流。

因为 $n \leq 10^3$ 支撑不了 $O(n^2)$ 级别的边数。所以说考虑优化。

思考一下一般的二分图带权匹配，我们的优化是加一个中转点。原因是我们不需要知道到底谁连的是谁，只需要对应的加上贡献即可。

再返回来看这个题，显然我们不能凭借一个中转点就解决这个问题，因为可能你选的两个点所加上的贡献不是这个东西。考虑一下曼哈顿距离的性质。

曼哈顿距离定义：给定两个点 $A,B$，两点间的曼哈顿距离 $dis(A,B)$ 为：

$$
dis(A,B) = |x_A - x_B| + |y_A - y_B|
$$

考虑将这个绝对值函数拆开（请自行移项），得到：

$$
dis(A,B)=
\begin{cases}
(x_A+y_A) - (x_B+y_B),x_A \geq x_B ∧ y_A \geq y_B\\
(-x_A+y_A) - (-x_B+y_B),x_A \leq x_B ∧ y_A \geq y_B\\
(x_A-y_A) - (x_B-y_B),x_A \geq x_B ∧ y_A \leq y_B\\
(-x_A-y_A) - (-x_B-y_B),x_A \leq x_B ∧ y_A \leq y_B\\
\end{cases}
$$

可以发现，每一种情况里面的括号里面的形式都跟另外一个括号内的形式类似，并且只跟一个点有关，就可以更方便地加边并且使得上面的问题解决。于是新开 $4$ 个点，分别对应上面的情况，对应连边即可。具体可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,cnt=1,s,t,to[3000005],val[3000005],siz[2021],nxt[3000005],cst[3000005],ntw[2021],lid[2021],pre[2021],dis[2021];
bool vis[2021];
void addEdge(LL u,LL v,LL w,LL x)
{
	++cnt;
	to[cnt]=v;
	val[cnt]=w;
	cst[cnt]=x;
	nxt[cnt]=siz[u];
	siz[u]=cnt;
	swap(u,v);
	w=0,x=-x;
	++cnt;
	to[cnt]=v;
	val[cnt]=w;
	cst[cnt]=x;
	nxt[cnt]=siz[u];
	siz[u]=cnt;
}
bool bfs(LL p)
{
	memset(dis,63,sizeof dis);
	queue<LL> Q;
	Q.push(p);
	ntw[p]=2e8;
	dis[p]=0;
	while(!Q.empty())
	{
		LL now=Q.front();
		Q.pop();
		vis[now]=false;
		for(LL i=siz[now];i;i=nxt[i])
		{
			if(val[i] && cst[i]+dis[now]<dis[to[i]])
			{
				dis[to[i]]=cst[i]+dis[now];
				if(!vis[to[i]])	Q.push(to[i]),vis[to[i]]=true;
				ntw[to[i]]=min(val[i],ntw[now]);
				lid[to[i]]=i;
				pre[to[i]]=now;
			}
		}
	}
	return dis[0]!=dis[t];
}
struct Ball{
	LL x,y,c;
	Ball(LL X=0,LL Y=0,LL C=0){x=X,y=Y,c=C;}
}a[1005],b[1005];
LL Abs(LL x){return x>0?x:-x;}
LL dist_mht(Ball x,Ball y){return Abs(x.x-y.x)+Abs(x.y-y.y);}
LL ts[5];
LL vec1[]={0,1,-1,1,-1},vec2[]={0,1,1,-1,-1};
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)
	{
		LL x,y,c;
		scanf("%lld %lld %lld",&x,&y,&c);
		a[i]=Ball(x,y,c);
	}
	for(LL i=1;i<=n;++i)
	{
		LL x,y,c;
		scanf("%lld %lld %lld",&x,&y,&c);
		b[i]=Ball(x,y,c);
	}
	s=2*n+1,t=s+1;
	ts[1]=t+1;
	ts[2]=ts[1]+1;
	ts[3]=ts[2]+1;
	ts[4]=ts[3]+1;
	for(LL i=1;i<=n;++i)
	{
		addEdge(s,i,a[i].c,0);
		addEdge(i+n,t,b[i].c,0);
		for(LL j=1;j<=4;++j)
		{
			LL vl=a[i].x*vec1[j]+a[i].y*vec2[j];
			addEdge(i,ts[j],1e7,-vl);
		}
		for(LL j=1;j<=4;++j)
		{
			LL vl=b[i].x*vec1[j]+b[i].y*vec2[j];
			addEdge(ts[j],i+n,1e7,vl);
		}
	}
	LL cost=0;
	while(bfs(s))
	{
		cost+=ntw[t]*dis[t];
		int now=t;
		while(now!=s)
		{
			val[lid[now]]-=ntw[t];
			val[lid[now]^1]+=ntw[t];
			now=pre[now];
		}
	}
	printf("%lld",-cost);
	return 0;
}
```

---

## 作者：strcmp (赞：1)

显然有一个完全没有脑子的费用流模型。

$s \to r_i$ 容量为 $rc_i$ 费用为 $0$，$b_i \to t$ 容量为 $bc_i$ 费用为 $0$。

然后 $r_i \to b_j$ 容量为 $+\infty$ 费用为它们之间的曼哈顿距离。

最大费用最大流即可。

费用流复杂度众所周知是 $\Theta(nmf)$ 的，在二分图上，流量是 $\sum rc_i$。也就是说复杂度是 $\Theta(n^4)$ 还带个 $10$ 的常数。

如果使用 Primal-Dual 算法并且最短路使用朴素 dijkstra，那么时间复杂度 $\Theta(n^3)$，但是 $10$ 的常数消不去，大概也通过不了。除非进行一些极其恐怖的卡常。

直接考虑拆曼哈顿距离。

$|x_a - x_b| + |y_a - y_b| = \max \{ x_a - x_b + y_a - y_b,\,x_b - x_a + y_a - y_b,\, x_a - x_b + y_b - y_a,\,x_b - x_a + y_b - y_a\}$。

比如我们想连一个 $x_a - x_b + y_a - y_b$，可以拆成 $x_a + y_a - x_b - y_b$，于是 $a$ 向一个特殊点连容量为 $+\infty$ 费用为 $x_a + y_a$ 的边，特殊点向所有右侧点连容量为 $+\infty$ 费用为 $-x_b - y_b$ 的边。

这样为什么不影响答案？因为我们跑的是最大费用最大流，最短路一定是找最大费用，也就是说一定会走四种点中费用最大的那一个。

建立四个特殊点，于是额外边数就是 $8n$。

直接跑费用流。如果直接套用 spfa 的时间复杂度分析，得时间复杂度 $\Theta(n^3)$，理论上卡满带个 $80$ 的常数，但是由于距离是曼哈顿距离，而且这图结构固定，spfa 是远远跑不满的。

当然可以使用 Primal-Dual 算法，时间复杂度 $\Theta(n^3 + n^2\log n)$，但此时那个理论上 $80$ 的常数在右边，可以接受。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pq = priority_queue<int>;
using ld = double;
constexpr int maxn = 2e5 + 10, bs = 19260817, mod = 22309287;
constexpr ll inf = 1e12;
struct edge { int fr, to, nxt; ll w, c; } nd[maxn << 1]; int h[maxn], cnt = 0;
inline void add(int u, int v, ll w, ll c) { nd[cnt].nxt = h[u], nd[cnt].fr = u, nd[cnt].to = v, nd[cnt].w = w, nd[cnt].c = c, h[u] = cnt++; }
inline void addE(int u, int v, ll w, ll c) { add(u, v, w, c), add(v, u, 0, -c); }
int s, t, q[maxn], hd = 1, tl = 0, inq[maxn], pre[maxn], n; ll sum = 0, ct = 0, a[maxn], b[maxn], c[maxn], d[maxn], dis[maxn], p1 = 0, p2 = 0;
int spfa() {
	memset(dis, 0x3f, (t + 1) * sizeof(ll));
	hd = 1, tl = 0; q[++tl] = s; dis[s] = 0;
	while (hd <= tl) {
		int u = q[hd++]; inq[u] = 0;
		for (int i = h[u]; ~i; i = nd[i].nxt) {
			int v = nd[i].to;
			if (dis[v] > dis[u] + nd[i].c && nd[i].w) {
				if (!inq[v]) q[++tl] = v, inq[v] = 1;
				pre[v] = i, dis[v] = dis[u] + nd[i].c;
			}
		}
	}
	if (dis[t] > inf) return 0;
	else return 1;
}
int mcmf() {
	if (!spfa()) return 0; int u = t; ll v = inf;
	while (u != s) v = min(v, nd[pre[u]].w), u = nd[pre[u]].fr; u = t; sum += v;
	while (u != s) nd[pre[u]].w -= v, nd[pre[u] ^ 1].w += v, ct += nd[pre[u]].c * v, u = nd[pre[u]].fr;
	return 1;
}
int rc[maxn], rx[maxn], ry[maxn], bc[maxn], bx[maxn], by[maxn];
int main() {
	memset(h, -1, sizeof(h));
	scanf("%d", &n); s = n * 2 + 5, t = n * 2 + 6; int u1 = s - 4, u2 = s - 3, u3 = s - 2, u4 = s - 1;
	rep(i, 1, n) scanf("%d%d%d", &rx[i], &ry[i], &rc[i]), addE(s, i, rc[i], 0);
	rep(i, 1, n) scanf("%d%d%d", &bx[i], &by[i], &bc[i]), addE(i + n, t, bc[i], 0);
	rep(i, 1, n) {
		addE(i, u1, inf, -rx[i] - ry[i]), addE(u1, i + n, inf, bx[i] + by[i]);
		addE(i, u2, inf, -rx[i] + ry[i]), addE(u2, i + n, inf, bx[i] - by[i]);
		addE(i, u3, inf, rx[i] - ry[i]), addE(u3, i + n, inf, -bx[i] + by[i]);
		addE(i, u4, inf, rx[i] + ry[i]), addE(u4, i + n, inf, -bx[i] - by[i]);
	}
	while (mcmf());
	printf("%lld\n", -ct);
    return 0;
}
```

---

## 作者：xht (赞：1)

## [Manhattan Max Matching](https://atcoder.jp/contests/agc034/tasks/agc034_d)

### 题意

- 在平面上有 $n$ 个位置有红点，$n$ 个位置上有蓝点，其中 $(rx_i,ry_i)$ 上有 $rc_i$ 个红点，$(bx_i,by_i)$ 上有 $bc_i$ 个蓝点，红蓝点总个数相同。
- 现在要将红蓝点一一匹配，两点匹配的价值为其曼哈顿距离，要求最大价值和。
- $n \le 10^3$，$rc_i,bc_i \le 10$。

### 题解

首先显然可以直接建图跑费用流，但边数为 $\mathcal O(n^2)$ 无法接受。

考虑曼哈顿距离有性质：

$$
\begin{aligned}
|x_1-x_2|+|y_1-y_2|
&=\max( 
x_1-x_2+y_1-y_2,
x_1-x_2-y_1+y_2,
-x_1+x_2+y_1-y_2,
-x_1+x_2-y_1+y_2
)\\\\
&=\max(
(x_1+y_1)+(-x_2-y_2),
(x_1-y_1)+(-x_2+y_2),
(-x_1+y_1)+(x_2-y_2),
(-x_1-y_1)+(x_2+y_2)
)\\\\
\end{aligned}
$$

于是只需要建四个点对应每种情况，边数 $\mathcal O(n)$，可以直接跑费用流。

### 代码

```cpp
namespace Dinic {
	const int N = 1e5 + 7, M = 2e6 + 7;
	const ll inf = 1e18;
	int n, S, T;
	int h[N], hi[N], e[M], t[M], tot;
	ll d[N], f[M], c[M], mxf, ans;
	bool v[N];

	inline void add(int x, int y, ll z, ll w, bool o = 1) {
		e[++tot] = y, f[tot] = z, c[tot] = w, t[tot] = h[x], h[x] = tot;
		if (o) add(y, x, 0, -w, 0);
	}

	inline bool bfs() {
		for (int i = 1; i <= n; i++) d[i] = inf, v[i] = 0;
		queue<int> q;
		q.push(S), d[S] = 0, v[S] = 1;
		while (q.size()) {
			int x = q.front();
			q.pop(), v[x] = 0;
			for (int i = h[x]; i; i = t[i]) {
				int y = e[i];
				ll z = f[i], w = c[i];
				if (d[y] <= d[x] + w || !z) continue;
				d[y] = d[x] + w;
				if (!v[y]) q.push(y), v[y] = 1;
			}
		}
		return d[T] != inf;
	}

	ll dfs(int x, ll now = inf) {
		if (x == T) return now;
		v[x] = 1;
		ll rst = now;
		for (int &i = hi[x]; i; i = t[i]) {
			int y = e[i];
			ll z = f[i], w = c[i];
			if (v[y] || d[y] != d[x] + w || !z) continue;
			ll k = dfs(y, min(z, rst));
			if (!k) d[y] = inf;
			else ans += k * w, f[i] -= k, f[i^1] += k, rst -= k;
			if (!rst) break;
		}
		v[x] = 0;
		return now - rst;
	}

	inline void main() {
		while (bfs()) {
			for (int i = 1; i <= n; i++) hi[i] = h[i];
			ll now;
			while ((now = dfs(S))) mxf += now;
		}
	}

	inline void init(int _n, int _S, int _T) {
		n = _n, S = _S, T = _T, tot = 1, mxf = 0, ans = 0;
		for (int i = 1; i <= n; i++) h[i] = 0; 
	}
}
using Dinic::add;
using Dinic::inf;

int main() {
	int n;
	rd(n);
	int p1 = n << 1 | 1, p2 = p1 + 1, p3 = p2 + 1, p4 = p3 + 1;
	int S = p4 + 1, T = S + 1;
	Dinic::init(T, S, T);
	for (int i = 1, x, y, c; i <= n; i++)
		rd(x, y, c),
		add(S, i, c, 0),
		add(i, p1, inf, x + y),
		add(i, p2, inf, x - y),
		add(i, p3, inf, -x + y),
		add(i, p4, inf, -x - y);
	for (int i = 1, x, y, c; i <= n; i++)
		rd(x, y, c),
		add(i + n, T, c, 0),
		add(p1, i + n, inf, -x - y),
		add(p2, i + n, inf, -x + y),
		add(p3, i + n, inf, x - y),
		add(p4, i + n, inf, x + y);
	Dinic::main();
	print(-Dinic::ans);
	return 0;
}
```

---

## 作者：1saunoya (赞：1)

## 题意
有 $N$ 个点上面有若干个蓝球，有 $N$ 个点上面有若干个红球。

保证蓝球和红球的数量一样。

每个蓝球和红球匹配的价值是曼哈顿距离，求最大的匹配价值。

$N \leq 10^3$

## 题解
很经典的拆符号。

$\texttt{distance(i,j)} = \max\{x_i-x_j+y_i-y_j,x_j-x_i+y_i-y_j,x_i-x_j+y_j-y_i,x_j-x_i+y_j-y_i\}$

发现 $x_i$ 和 $x_j$ 异号，所以我们就可以直接枚举一个状态 $h$，如果 $i$ 选了 $h$ 这个状态，那么 $j$ 需要选 $h_i \oplus 3$ 这个状态（就是符号位取反），这容易发现和最小费用最大流是一样的，只是用最小费用最大流会跑出一个负数（也就是每次选的都是 $-\texttt{distance(i,j)}$），所以我们最后要输出 最小费用 $\times (-1)$。

还比较好写。

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i < y; i++)
#define all(v) begin(v), end(v)
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
istream &operator>> (istream &in, vector<T> &v) {
 for (auto &x : v) {
  in >> x;
 }
 return in;
}
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
namespace Flow {
#define int long long
int S, T;
void Set(int _S, int _T) { S = _S, T = _T; }
struct Edge_t {
	int v, nxt, w, cost;
	Edge_t(int V = 0, int Nxt = 0, int W = 0, int Cost = 0) {
		v = V, nxt = Nxt, w = W, cost = Cost;
	}
};
std::vector<Edge_t> e(2);
std::vector<int> head;
void add(int u, int v, int w, int cost) {
	if (u >= (int)head.size()) {
		head.resize(u + 127);
	}
	e.emplace_back(v, head[u], w, cost);
	head[u] = (int)e.size() - 1;
}
void addedge(int u, int v, int w, int cost) {
	add(u, v, w, cost);
	add(v, u, 0, -cost);
}
constexpr long long inf = 1e18;
std::queue<int> q;
std::vector<int> dep;
std::vector<int> cur;
std::vector<bool> inq;
bool bfs() {
	dep.assign(head.size(), inf);
	inq.assign(head.size(), false);
	cur = head;
	q.emplace(S), dep[S] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop(); inq[u] = false;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (e[i].w && dep[v] > dep[u] + e[i].cost) {
				dep[v] = dep[u] + e[i].cost;
				if (!inq[v]) {
					inq[v] = true;
					q.emplace(v);
				}
			}
		}
	}
	return dep[T] < inf;
}
int dfs(int u, int flow) {
	if (!flow) {
		return 0;
	} else if (u == T) {
		return flow;
	} else {
		inq[u] = true;
		int f = 0;
		for (int &i = cur[u], rf; i; i = e[i].nxt) {
			int v = e[i].v;
			if (!inq[v] && dep[v] == dep[u] + e[i].cost && (rf = dfs(v, std::min(flow, e[i].w)))) {
				flow -= rf, f += rf;
				e[i].w -= rf, e[i ^ 1].w += rf;
				if (flow == 0) {
					return f;
				}
			}
		}
		return f;
	}
}
std::pair<int, int> dinic() {
	int ans = 0, res = 0;
	while (bfs()) {
		int tmp = dfs(S, inf);
		ans += tmp;
		res += dep[T] * tmp;
	}
	return std::make_pair(ans, res);
}
#undef int
}
using namespace Flow;
int main() {
 cin.tie(nullptr)->sync_with_stdio(false);
 int n;
 cin >> n;
 int tot=0;
 int s=++tot;
 int t=++tot;
 vector<int>p(4);
 for(auto&x:p)x=++tot; 
 Set(s,t);
 rep(i,0,n){
  int x,y,k;
  cin>>x>>y>>k;
  ++tot;
  addedge(s,tot,k,0);
  rep(h,0,4){
   int xx=(h&1)?x:-x;
   int yy=(h&2)?y:-y;
   addedge(tot,p[h],inf,xx+yy);
  }
 }
 rep(i,0,n){
  int x,y,k;
  cin>>x>>y>>k;
  ++tot;
  addedge(tot,t,k,0);
  rep(h,0,4){
   int xx=(h&1)?-x:x;
   int yy=(h&2)?-y:y;
   addedge(p[h],tot,inf,xx+yy);
  }
 }
 cout<<-dinic().second<<"\n";
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

考场的一道题，没注意到 $O(n ^ 2)$ 建图会挂所以以为是一道水题就直接莽过去了，考后开始后悔……      

$O(n ^ 2)$ 建图很水，就不说了，尽管网络流时间复杂度很玄学，但是~~艹~~ $1e6$ 的边数据不得不说还是很困难……      

所以考虑曼哈顿距离的性质，记得之前巨佬 $CLJ$ 还给我讲过这玩意儿可以拿来拆 $max$ 自己还没去想……      

我们首先观察式子 $|x_1 - x_2| + |y_1 - y_2|$ 。     

根据绝对值性质，如果我们误把其中一项算成负数，那么整体值就会变小，所以说我们只要分类讨论一下几种情况然后取 $max$ 即可：     

- $|x_1 - x_2| + |y_1 - y_2| = max(x_1 - x_2 + y_1 - y_2 ,x_2 - x_1 + y_1 - y_2,x_1 - x_2 + y_2 - y_1,x_2 - x_1 + y_2 - y_1)$      

开四个点表示这四种连边，$x_1,y_1$ 项和 $x_2,y_2$ 项分别放在四个点的左右两边，这样变的个数就被优化到了 $8n$ 条，而根据费用流性质，我们肯定会选取最长的一条边，即自动执行 $max$ 操作。      

接着跑最大费用流。     

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define int long long
const int Len = 1e4 + 5,Inf = 1e18;
bool vis[Len];
int n,m,cnt = 1,head[Len],dis[Len],pre[Len],aug[Len],mincost,maxflow,p[15],s,t;
struct node
{
	int next,to,flow,w;
}edge[Len << 1];
void add(int from,int to,int flow,int w)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].flow = flow;
	edge[cnt].w = -w;
	head[from] = cnt;	
}
bool SPFA()
{
	queue<int> q;
	memset(aug , 0 , sizeof aug);
	memset(vis , 0 , sizeof vis);
	for(int i = 1 ; i <= t ; i ++) dis[i] = Inf;
	dis[s] = 0 , vis[s] = 1 , aug[s] = Inf;
	q.push(s);
	while(!q.empty())
	{
		int p = q.front() ; q.pop();
		vis[p] = 0;
		for(int e = head[p] ; e ; e = edge[e].next)
		{
			int to = edge[e].to;
			if(dis[to] > dis[p] + edge[e].w && edge[e].flow)
			{
				dis[to] = dis[p] + edge[e].w;
				pre[to] = e;
				aug[to] = min(aug[p] , edge[e].flow);
				if(!vis[to]) q.push(to) , vis[to] ^= 1;
			} 
		}
	}
	if(dis[t] == Inf) return 0; 
	return 1;
}
void E_K()
{
	mincost = maxflow = 0;
	while(SPFA())
	{
		int x = t , E;
		maxflow += aug[t];
		mincost += aug[t] * dis[t];
		while(x != s)
		{
			E = pre[x];
			edge[E].flow -= aug[t];
			edge[E ^ 1].flow += aug[t];
			x = edge[E ^ 1].to;	
		}	
	}
}
signed main()
{
	scanf("%lld",&n);
	p[1] = (n << 1) + 1;for(int i = 2 ; i <= 4 ; i ++) p[i] = p[i - 1] + 1;
	s = p[4] + 1 , t = s + 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x,y,z;
		scanf("%lld %lld %lld",&x,&y,&z);
		add(s , i , z , 0) , add(i , s , 0 , 0);
		add(i , p[1] , Inf , x + y) , add(p[1] , i , 0 , -(x + y));
		add(i , p[2] , Inf , x - y) , add(p[2] , i , 0 , -(x - y));
		add(i , p[3] , Inf , -x + y) , add(p[3] , i , 0 , x - y);
		add(i , p[4] , Inf , -x - y) , add(p[4] , i , 0 , x + y);
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		int x,y,z;scanf("%lld %lld %lld",&x,&y,&z);
		add(i + n , t , z , 0) , add(t , i + n , 0 , 0);
		add(p[1] , i + n , Inf , -x - y) , add(i + n , p[1] , 0 , x + y);
		add(p[2] , i + n , Inf , y - x) , add(i + n , p[2] , 0 , x - y);
		add(p[3] , i + n , Inf , x - y) , add(i + n , p[3] , 0 , y - x);
		add(p[4] , i + n , Inf , x + y) , add(i + n , p[4] , 0 , -x - y);
	}
	E_K();
	printf("%lld\n",-mincost);
	return 0;
}
```


---

## 作者：zifanwang (赞：0)

首先有个显然的费用流做法，可以直接把任意两异色点连边然后求匹配，但是边数太多无法通过。

考虑一个经典的转化：对于两点 $(x_1,y_1),(x_2,y_2)$ 之间的曼哈顿距离有 $|x_1-x_2|+|y_1-y_2|=\max\{x_1+y_1-x_2-y_2,-x_1+y_1+x_2-y_2,x_1-y_1-x_2+y_2,-x_1-y_1+x_2+y_2\}$。于是可以建四个点 $A,B,C,D$，表示四种正负情况，建立如下费用流模型（$(a,b,c,d)$ 表示一条流量为 $c$，费用为 $d$，$a\to b$ 的边）：

- 对于所有 $1\le i\le n$，$(S,i,RC_i,0)$。
- 对于所有 $1\le i\le n$，$(n+i,T,BC_i,0)$。
- 对于所有 $1\le i\le n$，$(i,A,\infty,RX_i+RY_i)$。
- 对于所有 $1\le i\le n$，$(i,B,\infty,RX_i-RY_i)$。
- 对于所有 $1\le i\le n$，$(i,C,\infty,-RX_i+RY_i)$。
- 对于所有 $1\le i\le n$，$(i,D,\infty,-RX_i-RY_i)$。
- 对于所有 $1\le i\le n$，$(A,i+n,\infty,-BX_i-BY_i)$。
- 对于所有 $1\le i\le n$，$(B,i+n,\infty,-BX_i+BY_i)$。
- 对于所有 $1\le i\le n$，$(C,i+n,\infty,BX_i-BY_i)$。
- 对于所有 $1\le i\le n$，$(D,i+n,\infty,BX_i+BY_i)$。

边数降到了 $\mathcal O(n)$，直接费用流做即可。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 5003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,m,s,t,tot=1,vr[100003],ed[100003],c[100003],nx[100003],now[mxn],hd[mxn];
ll ans,cost,d[mxn];
queue<int>q;
bool b[mxn];
const ll INF=1e18;
inline void add(int x,int y,int z,int cs){
	vr[++tot]=y,ed[tot]=z,c[tot]=cs,nx[tot]=hd[x],hd[x]=tot;
	vr[++tot]=x,ed[tot]=0,c[tot]=-cs,nx[tot]=hd[y],hd[y]=tot;
}
bool spfa(){
	memset(d,0xcf,sizeof(d));
	memcpy(now,hd,sizeof(hd));
	d[s]=0,b[s]=1,q.push(s);
	while(q.size()){
		int x=q.front();q.pop();b[x]=0;
		for(int i=hd[x],y;i;i=nx[i])if(ed[i]&&d[y=vr[i]]<d[x]+c[i]){
			d[y]=d[x]+c[i];
			if(!b[y])b[y]=1,q.push(y);
		}
	}
	return d[t]>-INF;
}
ll dfs(int x,int t,ll flow){
	if(x==t)return flow;
	b[x]=1;
	ll ans=0;
	for(int &i=now[x],y;i&&ans<flow;i=nx[i])if(ed[i]&&!b[y=vr[i]]&&d[y]==d[x]+c[i]){
		ll num=dfs(y,t,min(flow-ans,(ll)ed[i]));
		if(num){
			ans+=num,cost+=num*c[i];
			ed[i]-=num,ed[i^1]+=num; 
		}
	}
	b[x]=0;
	return ans;
}
signed main(){
	scanf("%d",&n);
	s=0,t=n*2+1;
	for(int i=1,x,y,c;i<=n;++i){
		scanf("%d%d%d",&x,&y,&c);
		add(s,i,c,0);
		add(i,t+1,c,x+y);
		add(i,t+2,c,x-y);
		add(i,t+3,c,-x+y);
		add(i,t+4,c,-x-y);
	}
	for(int i=1,x,y,c;i<=n;++i){
		scanf("%d%d%d",&x,&y,&c);
		add(n+i,t,c,0);
		add(t+1,n+i,c,-x-y);
		add(t+2,n+i,c,-x+y);
		add(t+3,n+i,c,x-y);
		add(t+4,n+i,c,x+y);
	}
	while(spfa()){
		ll x;
		while((x=dfs(s,t,INF)))ans+=x;
	}
	printf("%lld",cost);
    return 0;
}
```

---

## 作者：phil071128 (赞：0)

> 有 $2n$ 朵花，其中 $n$ 朵红花，$n$ 朵蓝花，你要将他们配对，每一对的价值为 $|l_i-l_j|+|w_i-w_j|$，求最大价值和。$n\le 5000$。

匹配问题考虑费用流，直接暴力建图边数为 $O(n^2)$，Dinic 会被卡。

注意到价值的是两个差的绝对值之和的形式，如果将 $(l,w)$ 看做二维平面上一个点，那么相当于两点间**曼哈顿距离**。

因为 $|a-b|=\max (a-b,b-a)$，那么曼哈顿距离等价于一下四个值中最大值：

- $l_i-l_j+w_i-w_j$；
- $l_i-l_j+w_j-w_i$；
- $l_j-l_i+w_i-w_j$；
- $l_j-l_i+w_j-w_i$；

因为最终要求的就是最大值，而**错解不优**，所以问题可以等价于每组匹配中选择一种，求最大价值。

好处即是将价值独立，因此缩减了边数。

具体的，建立四个虚拟点，每个花连向这四个点，流量为一，费用为独立后的价值，再跑费用流，可以通过本题。


```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=2e5+500,inf=1e15+7;
int tot=1,ed,st;
struct edge{
	int to,nxt,w,fl;
}e[N];
int vis[N],dis[N],inq[N],head[N];
bool spfa() {
	queue<int>q;
	q.push(st);
	for(int i=1;i<=ed+10;i++) dis[i]=-inf,vis[i]=inq[i]=0;
	dis[st]=0;inq[st]=1; 
	while(!q.empty()) {
		int x=q.front();q.pop();inq[x]=0;
		for(int i=head[x];i;i=e[i].nxt) {
			int y=e[i].to,w=e[i].w;
			if(dis[y]<dis[x]+w&&e[i].fl) {
				dis[y]=dis[x]+w;
				if(!inq[y]) q.push(y),inq[y]=1;
			}
		}
	}
	return dis[ed]>-inf+100;
}
int ans=0;
int dfs(int x,int sum) {
	if(sum==0||x==ed) return sum; 
	int res=0;
	vis[x]=1;
	for(int i=head[x];i&&sum;i=e[i].nxt) {
		int y=e[i].to,w=e[i].w;
		if(dis[y]!=dis[x]+w||e[i].fl==0||vis[y]) continue;
		int tmp=dfs(y,min(sum,e[i].fl));
		e[i].fl-=tmp,e[i^1].fl+=tmp;
		ans+=tmp*e[i].w;
		sum-=tmp,res+=tmp;
	}
	return res;
}
void add(int u,int v,int fl,int w) {
	e[++tot].to=v;e[tot].nxt=head[u];
	head[u]=tot;e[tot].fl=fl,e[tot].w=w;
}
void ad(int u,int v,int fl,int w) {
	add(u,v,fl,w);
	add(v,u,0,-w);
}
pii red[N],blu[N];
signed main(){
	//fil();
	int n=read();
	st=n*2+1,ed=n*2+2;
	int _1=n*2+3,_2=n*2+4,_3=n*2+5,_4=n*2+6;
	for(int i=1;i<=n;i++) {
		int x=read(),y=read(),sum=read();
		ad(st,i,sum,0);
		ad(i,_1,inf,x+y);
		ad(i,_2,inf,x-y);
		ad(i,_3,inf,-x+y);
		ad(i,_4,inf,-x-y);
	}
	int r=n;
	for(int i=1;i<=n;i++) {
		int x=read(),y=read(),sum=read();
		ad(i+r,ed,sum,0);
		ad(_1,i+r,inf,-x-y);
		ad(_2,i+r,inf,-x+y);
		ad(_3,i+r,inf,x-y);
		ad(_4,i+r,inf,x+y);
	}
	while(spfa()) {
		dfs(st,inf);
	}
	cout<<ans<<"\n";
	return 0;
}


```

本题还可以模拟费用流，思路来自 Larunatrecy：

我们考虑模拟上述费用流的过程，注意到其实关键的点只有源点汇点以及中间的四个点（记为 $S,T,V_{1,2,3,4}$），并且每次增广路一定是如下形态：

- 对于 $S\to {V_{k}}$，为某个未选择的红花选择一种方式 $k$。
- 对于 $V_{k}\to T$，为某个未选择的蓝花选择一种方式 $k$。
- 对于 $V_{i}\to V_{j}$，将某个选择了第 $i$ 种方式的红花/蓝花改为选用第 $j$ 种方式。

并且因为一次增广时不会经过重复的边，我们只需要知道上述的三种路径中代价的最大值即可，可以开 $4+4+12=20$ 个堆维护这些代价，然后对这六个点的图跑 SPFA，求出最短路后更新每个堆里的数即可。

复杂度是 $\Theta(n\log n)$，常数很大。

---

## 作者：Filberte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc034_d)

## 思路

考虑费用流建图：

- 从源点向每个红点连一条容量为 $rc_i$，费用为 $0$ 的边。
- 从每个蓝点向汇点连一条容量为 $bc_i$，费用为 $0$ 的边。
- 每个红点像每个蓝点连一条容量为正无穷，费用为两点间曼哈顿距离的边。

在此网络上跑最大费用最大流，得到的最大费用即为所求的答案。但是这样建图一共有 $O(n^2)$ 条边，无法通过此题，考虑优化建图。曼哈顿距离有一个很好的性质：$|x_1 - x_2| + |y_1 - y_2|$ 的值是以下 $4$ 个值的最大值：

- $(x_1 + y_1) + (-x_2 - y_2)$
- $(x_1 - y_1) + (-x_2+y_2)$
- $(-x_1+y_1) + (x_2 - y_2)$
- $(-x_1-y_1) + (x_2 + y_2)$

所以可以建立 $4$ 个中转点，每个点向这 $4$ 个点分别连接 $4$ 条边，边权都是正无穷，费用是对应的权值。这样通过流量限制可以保证每个点的匹配量不会超过限制量，而最大费用保证了计算任意两点匹配时所带来的贡献是这两个点的曼哈顿距离，至此，我们成功将边的数量降低到 $O(n)$ 级别，就可以通过这个题目了。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2050;
const int M = 2e4 + 100;
const int inf = 2e9;
struct E{
    int to, nxt, w, c;  
}e[M];int h[N], idx = 1;
void add(int u, int v, int w, int c){
    e[++idx] = {v, h[u], w, c};h[u] = idx;
    e[++idx] = {u, h[v], 0, -c};h[v] = idx;
}
int n;
const int s = 0, t = N - 1, n1 = N - 2, n2 = N - 3, n3 = N - 4, n4 = N - 5;
int rx[N], ry[N], rc[N], bx[N], by[N], bc[N];

ll dis[N];
bool inq[N];
int eid[N], mf[N];
bool spfa(){
    memset(dis, -0x3f, sizeof(dis));
    memset(mf, 0, sizeof(mf));
    queue<int> q;q.push(s);
    dis[s] = 0, inq[s] = 1, mf[s] = inf;
    while(!q.empty()){
        int u = q.front();q.pop();
        inq[u] = 0;
        for(int i = h[u];i;i = e[i].nxt) if(e[i].w){
            int v = e[i].to, c = e[i].c;
            if(dis[u] + c > dis[v]){
                dis[v] = dis[u] + c;
                mf[v] = min(mf[u], e[i].w);
                eid[v] = i;
                if(!inq[v]){
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }   
    }
    return mf[t] > 0;
}
ll EK(){
    ll sum = 0;
    while(spfa()){
        int u = t;
        while(u != s){
            int i = eid[u];
            e[i].w -= mf[t];
            e[i ^ 1].w += mf[t]; 
            u = e[i ^ 1].to;
        }
        sum += mf[t] * dis[t];
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i++){  
        cin >> rx[i] >> ry[i] >> rc[i];
        add(i, n1, rc[i], rx[i] + ry[i]);
        add(i, n2, rc[i], rx[i] - ry[i]);
        add(i, n3, rc[i], -rx[i] + ry[i]);
        add(i, n4, rc[i], -rx[i] - ry[i]);
        add(s, i, rc[i], 0);
    }
    for(int i = 1;i <= n;i++){  
        cin >> bx[i] >> by[i] >> bc[i];
        add(i + n, t, bc[i], 0);
        add(n1, i + n, bc[i], -bx[i] - by[i]);
        add(n2, i + n, bc[i], -bx[i] + by[i]);
        add(n3, i + n, bc[i], bx[i] - by[i]);
        add(n4, i + n, bc[i], +bx[i] + by[i]);
    }
    cout << EK() << endl;
    return 0;
}
```

---

## 作者：关怀他人 (赞：0)

### AGC 034D
#### Solution
不难想到费用流，但是若直接建图，则边数会达到$\mathcal O(n^2)$，不可通过。

注意到$|x_i−x_j|+|y_i−y_j|=max(x_i+y_i−x_j−y_j,x_i−xj-y_i+y_j,-x_i+x_j+y_i−y_j,-x_i+x_j−y_i+y_j)$

那么我们可以建四个中间点分别代表上面四种情况，每个点向这四个中间点连边，容量为$1$，这样边数就降到$\mathcal O(n)$了，由于是最大费用，所以保证了这样做的正确性。

最后跑个最大费用最大流即可。
#### Code
```cpp
int S,T,tot,n;
int p[5];

struct MinCostMaxFlow{
    int len;
    int head[MAXN],in[MAXN],id[MAXN],pre[MAXN]; ll dis[MAXN];
    queue<int> q;

    MinCostMaxFlow() {len = 1; memset(head,-1,sizeof(head));}

    struct Edge{
        int to,next,flow,cost;
    } e[MAXN << 1];
    
    void add_edge(int u,int v,int flow,int cost){
        e[++len] = (Edge){v,head[u],flow,cost};
        head[u] = len;
        e[++len] = (Edge){u,head[v],0,-cost};
        head[v] = len;
    }

    bool spfa(){
        for(int i = 1;i <= tot;i++) dis[i] = llINF, id[i] = pre[i] = in[i] = 0;
        in[S] = 1; q.push(S); dis[S] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop(); in[u] = 0;
            for(int i = head[u];i != -1;i = e[i].next){
                int v = e[i].to;
                if(e[i].flow && dis[v] > dis[u] + e[i].cost){
                    dis[v] = dis[u] + e[i].cost;
                    pre[v] = u; id[v] = i;
                    if(!in[v]) in[v] = 1, q.push(v);
                }
            }
        }
        return dis[T] != llINF;
    }

    ll EK(){
        ll minCost = 0;
        while(spfa()){
            int mi = INF;
            for(int i = T;i != S;i = pre[i]) checkMin(mi,e[id[i]].flow);
            for(int i = T;i != S;i = pre[i]) e[id[i]].flow -= mi, e[id[i] ^ 1].flow += mi;
            minCost += (ll)mi * dis[T];
        }
        return minCost;
    }
} mcmf;

int main(){
    scanf("%d",&n); tot = (n << 1);
    for(int i = 1;i <= 4;i++) p[i] = ++tot;
    S = ++tot; T = ++tot;
    for(int i = 1,x,y,c;i <= n;i++){
        scanf("%d%d%d",&x,&y,&c);
        mcmf.add_edge(S,i,c,0);
        mcmf.add_edge(i,p[1],INF,-x - y);
        mcmf.add_edge(i,p[2],INF,-x + y);
        mcmf.add_edge(i,p[3],INF,x - y);
        mcmf.add_edge(i,p[4],INF,x + y);
    }
    for(int i = 1,x,y,c;i <= n;i++){
        scanf("%d%d%d",&x,&y,&c);
        mcmf.add_edge(i + n,T,c,0);
        mcmf.add_edge(p[1],i + n,INF,x + y);
        mcmf.add_edge(p[2],i + n,INF,x - y);
        mcmf.add_edge(p[3],i + n,INF,-x + y);
        mcmf.add_edge(p[4],i + n,INF,-x - y);
    }
    printf("%lld\n",-mcmf.EK());
    return 0;
}
```

---

