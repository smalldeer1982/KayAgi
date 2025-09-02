# [JOI 2021 Final] 机器人 / Robot

## 题目描述

给定一个 $N$ 点无向图，这 $N$ 个点编号为 $1 \sim N$，由 $M$ 条边连接，这 $M$ 条边编号为 $1 \sim M$，分别连接点 $A_i$ 与点 $B_i$。这 $M$ 条边染上了颜色，第 $i$ 条边的颜色为 $C_i$，保证 $C_i \in [1,M]$ 但不保证 $C_i$ 互不相等。

你很智能，如果我说一种颜色 $L$，满足下面这些要求的话：

- 存在一条边的颜色为 $L$ 且一个端点为你现在在的点。
- 不存在大于等于两条边满足颜色为 $L$ 且一个端点为你现在在的点。

你就会移动到这条边走向对面的端点，否则你就会原地不动。

你现在在点 $1$ 处，我要你移动到点 $N$ 处，我可以告诉你一些颜色你按照这些颜色走。但这个图有可能不满足能从 $1$ 走向 $N$ 这个条件，因此我要改变一些边的颜色。改变第 $i$ 条边的颜色使其变为另一个在区间 $[1,M]$ 里的数需要的代价为 $P_i$，我想问，至少需要多少代价才能让你成功移动到点 $N$？

## 说明/提示

#### 样例 1 解释

我可以进行如下操作：

- 将第 $4$ 条边的颜色改为 $4$，代价 $1$。
- 将第 $6$ 条边的颜色改为 $2$，代价 $2$。

总代价 $3$，然后我如下使唤你：

- 我说“颜色 $2$！”你从点 $1$ 移动到点 $2$。
- 我说“颜色 $4$！”你从点 $2$ 移动到点 $4$。

#### 样例 2 解释

很遗憾，即使如此智能的你也到达不了第 $N$ 个点。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（34 pts）：$N \le 1000$，$M \le 2000$。
- Subtask 2（24 pts）：$P_i=1$。
- Subtask 3（42 pts）：无特殊限制。

对于 $100\%$ 的数据，$2 \le N \le 10^5$，$1 \le M \le 2 \times 10^5$，$1 \le A_i<B_i \le N$，$1 \le C_i \le M$，$1 \le P_i \le 10^9$，保证图无重边。

#### 说明

翻译自 [The 20th Japanese Olympiad in Informatics Final Round D ロボット的英文翻译 Robot](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t4-en.pdf)。

## 样例 #1

### 输入

```
4 6
1 4 4 4
3 4 1 3
1 3 4 4
2 4 3 1
2 3 3 2
1 2 4 2```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2
1 4 1 2
3 5 1 4```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 7
2 3 7 1
1 4 5 1
4 5 3 1
3 4 7 1
2 4 3 1
3 5 6 1
1 2 5 1```

### 输出

```
1```

# 题解

## 作者：遮云壑 (赞：9)

## Description
[出门左转](https://www.luogu.com.cn/problem/P7407)

~~教练原话：JOI Final=日本的NOIP？？（大雾）~~
## Solution
#### 大体思路：建虚点+最短路
##### 1. 为什么要建虚点？
  
当你在一个点决策下一步时，决策会有很多种情况，虚点的作用就是让我们考虑到所有的这些情况。

##### 2. 如何建立虚点？**敲黑板敲黑板**

首先考虑会有几种情况

- 该颜色在当前点只有一种，花费为0
- 该颜色在当前点有多种，可以改它自身，也可以该它的其他所有相同颜色的小伙们
- 从一个多颜色的点进来，并且选择这一颜色的点出去，同时出去的时候选择改变其他所有同色边的方案

这样说，十分空洞，看不懂先跳吧，后面还会讲。

**插播一个性质：我们对边改颜色可以做到不对后来产生任何影响。**

原因很显然，一共有 $M$ 种颜色，只要我们想，是可以做到每一条边的颜色各不相同的。

放个图，更好理解。（为了表示颜色，只有手绘了，手残勿喷TAT）

![](https://cdn.luogu.com.cn/upload/image_hosting/14owfnko.png)

蓝色是你现在在的点，红色是几个相同颜色的点，黑色是所谓的虚点。

声明一下，这题虚点连的边都是有向边，因为权值会不同。

1. 建虚点，每一种颜色建一个虚点
2. 当前点向虚点连边（蓝->黑），权值为0
3. 虚点向出去的点连边（黑->红），权值为其他所有同色的边的权值之和
4. 出去的点向虚点连边（红->黑），权值为0

解释：

走2，3两种边，实现了改变其他所有同色边的情况。

走4，3两种边，（4进3出）实现了刚才说的乱七八糟的情况，这里细讲一下。（这非常重要，个人认为这是本题最难的一部分了）

现在我们在一个红点，要进蓝点，并且出来的又是红点，出来的时候选择改变其他所有红边。既然出来的时候改变其他所有的红边，那么进来的那条边肯定也改掉了，可以改成一个进去不需要任何花费的边，出来的时候改变其他红边的权值，所以我们直接以0的花费走到虚点，在以该所有红边的花费走出来，就可以了。

好了，虚点建完了，跑dij吧。

## code
```cpp
#include<bits/stdc++.h>
#define N 1000010
#define int long long
using namespace std;
inline void read(int& x)
{
	x=0;int y=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x=x*y;
}
int n,m;
struct Node{
	int to,nxt,w,col;
}e[N<<1];
int cnt,head[N];
inline void add(int u,int v,int col,int w)
{
	e[++cnt].col=col;e[cnt].nxt=head[u],e[cnt].to=v,e[cnt].w=w;
	head[u]=cnt;
}
int vis[N],num[N],sum[N],rt[N],tot,d[N];
struct node{
	int dis,id;
	bool operator<(const node& x)const{return dis>x.dis;}
	node(){}
	node(int d_,int id_){dis=d_,id=id_;}
};
priority_queue<node> q;
inline void dij()
{
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	q.push(node(d[1],1));
	while(!q.empty())
	{
		int x=q.top().id;q.pop();
		if(vis[x])continue;vis[x]=1;
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to,w=e[i].w;
			if(d[y]>d[x]+w)
			{
				d[y]=d[x]+w;
				q.push(node(d[y],y));
			}
		}
	}
}
signed main(){
//	freopen("robot.in","r",stdin);
//	freopen("robot.out","w",stdout);
	read(n),read(m);
	for(int i=1;i<=m;i++)
	{
		int x,y,z,zz;
		read(x),read(y),read(z),read(zz);
		add(x,y,z,zz),add(y,x,z,zz);
	}
	tot=n;
//-------------------重点分割线--------------------------- 
	//这一段是关于建虚点的 
	for(int x=1;x<=n;x++)
	{
		for(int i=head[x];i;i=e[i].nxt)
		{
			if(!e[i].col)continue;
			sum[e[i].col]+=e[i].w; 
			num[e[i].col]++;
			//sum表示同色点的权值和，num表示该颜色点有几个 
		}
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			if(!e[i].col)continue;
			if(num[e[i].col]==1)e[i].w=0;//仅一个，花费为0 
			else 
			{
				if(!rt[e[i].col])
				//2类边，蓝->黑 
				//rt记录了每一种颜色的虚点编号 
				{
					rt[e[i].col]=++tot;
					add(x,tot,0,0);
				}
				add(rt[e[i].col],e[i].to,0,sum[e[i].col]-e[i].w);
				//3类边，黑->红，权值为sum[e[i].col]-e[i].w 
				add(e[i].to,rt[e[i].col],0,0);
				//4类边，红->黑，权值为0 
			}
		}
		for(int i=head[x];i;i=e[i].nxt) 
		{
			rt[e[i].col]=sum[e[i].col]=num[e[i].col]=0;
		}
		//别忘了清空数组 
		//由于一个点的度数不会太大，所以直接改会比memset快一点 
	}
//-------------------重点分割线--------------------------- 
	dij();
	if(d[n]==0x3f3f3f3f3f3f3f3f)printf("-1\n");
	else printf("%lld\n",d[n]);
	return 0;
}
```


---

## 作者：moongazer (赞：8)

考虑从 $u$ 到 $v$ 的一条颜色为 $c$ 长度为 $w$ 的边，设 $S_{u,c}$ 为以 $u$ 为端点所有颜色为 $c$ 的边的长度之和，要经过该边有两种策略：

1. 将该边改为一种不冲突的颜色，费用 $w$。
2. 将所有相同颜色的其他边改掉，费用 $S_{u,c}-w$。

发现 $u$ 是菊花的中心且每条边的颜色两两不同的情况下 1 策略是不合法的，但是此时 2 策略费用为 $0$ 故可以不考虑。

发现若有 $u\to v$，$v\to x$ 两条边颜色都为 $c$ 在 $u\to v$ 选择 1 策略，$v\to x$ 选择 2 策略那么改变 $u\to v$ 边的颜色的代价会计算两边，考虑减去。

考虑建立虚点 $v_c$ 由 $u$ 向 $v_c$ 连边权为 $0$ 的边，$v_c$ 向 $x$ 连边权为 $S_{v,c}-w$ 的边，发现这样 $u\to v_c\to x$ 就是先 $1$ 策略再 $2$ 策略的代价。

于是跑 Dijkstra 即可。

最多每条边都建一个虚点，故点数是 $\operatorname{O}(n+m)$ 的，边数还是 $\operatorname{O}(m)$ 的，时间复杂度 $\operatorname{O}((n+m)\log m)$。

注意：以下参考代码大量使用 STL 和 C++17 特性，常数巨大且需要注意编译选项（亲测 `std::map` 比 `std::unordered_map` 快）。

```cpp
const int N = 100005;

void addedge(int u, int v, int c, int w);

std::map<int, ll> sum[N], dis[N];
std::map<int, int> len[N], col[N];
std::map<int, std::vector<pii>> mp[N];

int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v, c, w;
    read(u), read(v), read(c), read(w);
    addedge(u, v, c, w), addedge(v, u, c, w);
  }
  std::priority_queue<std::tuple<ll, int, int>> pq;
  auto upd = [&](int v, int c, ll udis) {
    if (!dis[v].count(c) || dis[v][c] > udis) {
      dis[v][c] = udis;
      pq.emplace(-udis, v, c);
    }
  };
  upd(1, 0, 0);
  while (!pq.empty()) {
    auto [d, u, c] = pq.top();
    d = -d;
    pq.pop();
    if (d != dis[u][c]) continue;
    for (auto [v, vc] : mp[u][c]) {
      ll w;
      if (c == vc)
        w = std::min(1ll * len[u][v], sum[u][col[u][v]] - len[u][v]);
      else if (c)
        w = sum[u][c] - len[u][v];
      else
        w = 0;
      upd(v, vc, d + w);
    }
  }
  if (dis[n].count(0))
    write(dis[n][0]), EL;
  else
    puts("-1");
  return 0;
}

void addedge(int u, int v, int c, int w) {
  col[u][v] = c, len[u][v] = w;
  sum[u][c] += w;
  mp[u][0].emplace_back(v, 0);
  mp[u][0].emplace_back(v, c);
  mp[u][c].emplace_back(v, 0);
}
```


---

## 作者：masonpop (赞：2)

很棒的思维题。

首先，如果我们想经过一条边 $(a,b,c,p)$，有两种方式：

① 直接将自己的颜色改为一种未出现的颜色，花费 $p$。

② 把当前与自己同色的边全部改掉，花费 $S_{a,c}-p$。其中 $S_{a,c}$ 表示与 $a$ 相连的所有 $c$ 颜色边改动代价和。

然后如果你直接把这两个东西取 $\min$ 跑最短路然后提交，发现是错的。因为可能有这种情况：先从 $x\to y$ 并选择方案 ①，再从 $y\to z$ 并选择方案 ②。此时发现总代价只有 $S_{y,z}-w$，因为如果 $x\to y$ 的颜色先被修改掉，之后就不用改了。

可以用一个虚点来完成这个操作。对于每个点连边的每个颜色，建立虚点 $T$。然后对于每条边，分别针对对方案 ①，② 像虚点连出两条边，边权分别为 $0,S_{y,z}-w$，且方向相反（前者连向 $T$）。这样就可以用 $O(m)$ 个虚点完成这个操作了。

然后跑最短路即可。[代码](https://www.luogu.com.cn/paste/6yqchw8y)。

---

## 作者：☯☯枫☯☯ (赞：2)

## 题解 [JOI 2021 Final] ロボット

[题目传送门](https://www.luogu.com.cn/problem/P7407)

## Analysis

本题本质上就是一个最短路问题，关键在于考虑改变道路的颜色。我们计算新的花费以重建一张图来跑最短路。

- 仅有一条与当前路口相连的路是要走的颜色，那么直接走过去即可，花费为 $0$。

- 否则分为两种情况，记当前与当前路口相连的颜色为 $c$ 的道路的总花费为 $sum_c$，要去的点为 $y$，花费为 $p_y$。

  1. 将要走的边改为独有的颜色，单次花费为 $p_y$。

  2. 改变与当前路口相连且与要走的路颜色相同的其他道路，单次花费为 $sum_c-p_y$。

为了简便我们可以直接用 `std::map` 记录每种颜色对应的花费 ~~（给了 2s 这不随便乱用）~~，后面不再赘述。

自然地，以上朴素想法引发了一些问题。

### Q1：是否存在一种情况，使得不能将一条边改为独有的颜色？

显然不存在。注意到一共有 $m$ 条边，$m$ 种颜色，那么显然每条边都可以改为独有的颜色。或者考虑菊花图的情况，这时一个点占有的颜色种类最多。但此时无需改变颜色。

### Q2：一条边会不会被重复改变颜色？

不会。一条边走两次显然不是最优解。

### Q3：何时无法到达？

当点 $1$ 与点 $n$ 不连通时。由于原图所有边都是无向边，且不存在无法抵达相邻点的情况，因此只有不连通时才无法到达。

明确以上三个基本问题以后就可以开始做题了。

对于 $\text{subtask 1}$，直接暴力拆点，将每个点拆成 $m$ 个点对应 $m$ 种不同颜色，然后重新计算边权即可。

对于 $\text{subtask 2}$，我们发现无论怎么跑每条边的花费一定是 $1$，因此直接当最短路跑就行了。

对于 $\text{subtask 3}$，我们发现基于原有的边直接跑最短路是有问题的。简单的说，在边权不同时，通过修改一条边抵达另一个点的操作存在“后效性”。

考虑一种最简单的图形。

```cpp
4 3
1 2 1 5
1 3 1 4
3 4 1 1
```

[![IZIs1S.png](https://z3.ax1x.com/2021/11/04/IZIs1S.png)](https://imgtu.com/i/IZIs1S)

我们发现输出是 $5$，而手模发现答案是 $4$，即改变 $1 \leftrightarrow 4$ 这一条边。

[![IZoPnH.png](https://z3.ax1x.com/2021/11/04/IZoPnH.png)](https://imgtu.com/i/IZoPnH)

每次修改边的颜色，会对与目标点相连的边的颜色状态产生影响。且影响的边是和**被改变边原来颜色相同的边**。也就是说，如果我们改变当前边，那么从目标点 $y$ 继续走颜色为 $c$ 的道路，相当于跳过中间点，直接抵达另一个点。

对每个点已拥有的颜色建立虚点，增加每个点对相应虚点的虚边即可。这里同样使用 `std:set` 记录。

因为对每条边至多建两个虚点，加上初始的 $n$ 个点，所以整张图最多有 $n+2\times m$ 个点。每两个通过非虚边连接的点 $x,y$ 及其对应颜色的虚点 $x',y'$ 至多连三条无向边，即 $x \leftrightarrow y$，$x\leftrightarrow y'$，$x'\leftrightarrow y$，因此最多有 $3\times m$ 条边。由于链式前向星连的是单项边，因此要开 $6\times m$ 条边。

最后跑个最短路即可。时间复杂度 $\mathcal{O}((n+m)\times \log(n+m))$。

### Code:

```cpp
#include <bits/stdc++.h>
#define ld double
#define eps (1e-8)
#define ll long long
#define lld long double
#define ull unsigned long long
#define Min(x, y) ((x) > (y) and ((x) = (y)))
#define Max(x, y) ((x) < (y) and ((x) = (y)))
#define Add(x,y) (((x)+=(y))>=mod and ((x)-=mod))
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define PF(i, a, b) for (int i = (a); i >= (b); --i)
#define For(i, x) for (int i = head[(x)]; i; i = net[(i)])
using namespace std;
bool beginning;
inline int read();
const int N=5e5+5,E=N<<3;//赛时防挂，不要在意
int n,m;
int ver[E],net[E],head[N],tot;
ll edge[E];
inline void add(int x,int y,ll z) {
	ver[++tot]=y,net[tot]=head[x],edge[head[x]=tot]=z;
}
struct P {
	int to,c;
	ll p;
	P(int x=0,int y=0,ll z=0) {
		to=x,c=y,p=z;
	}
};
vector<P>f[N];
ll dis[N];
struct Hp {
	int d;
	ll dis;
	bool operator <(const Hp &a)const {
		return dis>a.dis;
	}
};
bool vis[N];
inline void dij() {
	memset(dis,0x3f,sizeof(dis));
	priority_queue<Hp>q;
	dis[1]=0;
	q.push({1,0});
	Hp t;
	while(!q.empty()){
		t=q.top();
		q.pop();
		if(vis[t.d])continue;
		vis[t.d]=1;
		For(i,t.d){
			int &y=ver[i];
			if(dis[y]>dis[t.d]+edge[i]){
				dis[y]=dis[t.d]+edge[i];
				q.push({y,dis[y]});
			}
		}
	}
	printf("%lld\n",dis[n]==dis[0]?-1:dis[n]);
}
map<int,ll>mp,vtl[N];
bool ending;
int main() {
	cerr<<1.0*(&beginning-&ending)/1024/1024<<"MB\n----------\n";
	n=read(),m=read();
	int a,b,c,p;
	F(i,1,m) {
		a=read(),b=read(),c=read(),p=read();
		f[a].emplace_back(P<%b,c,p%>);
		f[b].emplace_back(P<%a,c,p%>);
	}
	int cnt=n;
	F(i,1,n){
		for(P y:f[i])if(!mp[y.c])vtl[i][y.c]=++cnt,mp[y.c]=1;
		for(P y:f[i])mp[y.c]=0;
	}
	mp.clear();
	F(i,1,n) {
		for(P y:f[i])mp[y.c]+=y.p;

		for(P y:f[i]) {
			add(i,y.to,min(y.p,mp[y.c]-y.p));
			add(i,vtl[y.to][y.c],0);
			add(vtl[i][y.c],y.to,mp[y.c]-y.p);
		}

		for(P y:f[i])mp[y.c]=0;
	}
	
	dij();
	return 0;
}
inline int read() {
	int x = 0;
	bool f = 1;
	char c = getchar();
	while (!isdigit(c)) {
		f = c ^ 45;
		c = getchar();
	}
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return f ? x : -x;
}
```

新建的边切记要开 `long long`。

---

## 作者：7KByte (赞：1)

如果当前边已经是唯一的边，那么我们可以直接连一条边权为 $0$ 的有向边。

否则我们可以花费 $P_i$ 的代价将它变成唯一的边，所以我们连一条边权为 $P_i$ 的有向边。

然后跑最短路，得到 $0 $ 分的好成绩（

手算以下发现还有两类情况没有考虑到。

首先 $P_i$ 可以不相等，这意味着我们可以保留当前边，然后花费其它多条边的代价使之成为唯一边可能会更优。

还有一种情况就是例如 $1-2$ ，$2-3$ ，两条边颜色相同，只用任意改动一条边就能使两条边同时成为唯一边。

扩展以下，我们将直接花费 $P_i$ 代价改变一条边的操作为 $\mathbf{A}$ 操作，保留当前边而修改其他所有边的操作为 $\mathbf{B}$ 操作。

那么先进行 $\mathbf{A}$ 操作，再进行 $\mathbf{B}$ 操作，第一次 $\mathcal{A}$ 操作的代价可以省去。

所以对于每条边建立一个虚点，进入这个虚点表示进行一次 $\mathbf{A}$ 操作，离开这个虚点表示进行一次 $\mathbf{B}$ 操作 ，然后进行连边操作。

一共 $N+M$ 个点，$8M$ 条有向边，时间复杂度 $\mathcal{O}((N+M)\log (N+M))$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int n,m,h[N],tot,v[N],idx;long long d[N],c[N<<1];map<int,int>u[N];
struct edge{int to,nxt;long long val;}e[N<<2];
void add(int x,int y,long long z){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;}
struct node{int y,c,p;};vector<node>a[N];
priority_queue<pair<long long,int> >q;
void dij(){
	memset(d,0x3f,sizeof(d));d[1]=0;q.push(make_pair(0,1));
	while(!q.empty()){
		int x=q.top().second;q.pop();v[x]=1;
		for(int i=h[x];i;i=e[i].nxt)if(d[x]+e[i].val<d[e[i].to])
			d[e[i].to]=d[x]+e[i].val,q.push(make_pair(-d[e[i].to],e[i].to));
		while(!q.empty()&&v[q.top().second])q.pop();
	}
}
int main(){
	scanf("%d%d",&n,&m);idx=n;
	rep(i,1,m){
		int x,y,z,w;scanf("%d%d%d%d",&x,&y,&z,&w);
		node cur;cur.y=y;cur.c=z;cur.p=w;
		a[x].push_back(cur);cur.y=x;a[y].push_back(cur);
	}
	rep(x,1,n){
		for(int i=0;i<(int)a[x].size();i++)if(!c[a[x][i].c])u[x][a[x][i].c]=++idx,c[a[x][i].c]=1;
		for(int i=0;i<(int)a[x].size();i++)c[a[x][i].c]=0;
	}
	rep(x,1,n){
		for(int i=0;i<(int)a[x].size();i++)c[a[x][i].c]+=a[x][i].p;
		for(int i=0;i<(int)a[x].size();i++){
			add(x,a[x][i].y,a[x][i].p);
			add(x,a[x][i].y,c[a[x][i].c]-a[x][i].p);
			add(u[x][a[x][i].c],a[x][i].y,c[a[x][i].c]-a[x][i].p);
			add(x,u[a[x][i].y][a[x][i].c],0);
		}
		for(int i=0;i<(int)a[x].size();i++)c[a[x][i].c]=0;
	}
	dij();printf("%lld\n",d[n]==0x3f3f3f3f3f3f3f3fLL?-1LL:d[n]);
	return 0;
} 
```

---

## 作者：lilong (赞：0)

读完题可以发现，由于边数与颜色种类数相等，故想要一条边可以走则一定能将其修改成一种独立的颜色（剩下 $m-1$ 条边最多 $m-1$ 种颜色）。因此在某一节点，想要走一条边，有两种策略：

- 花费 $p$ 的代价修改这条边。
- 花费 $S-p$ 的代价修改与这条边颜色相同的其它边。

但是直接这样建边并不正确。如果现在走了 $a \rightarrow b,b\rightarrow c$ 且两条边颜色相同，第一条采用了策略一，第二条采用了策略二，则第一条边被修改了两次（事实上并不需要）。引入虚点，对于**当前点 $i$ 连接的每种颜色**建立一个虚拟点 $v_c$，并取所有该种颜色的边的另一端点 $u$，执行以下操作：

- 建立 $i\rightarrow v_c$，边权 $0$。
- 建立 $u\rightarrow v_c$，边权 $0$。
- 建立 $v_c\rightarrow u$，边权 $S-p$。

不要忘记建策略一的边（直接在原图上建），建完后跑 Dijkstra 即可。时间复杂度 $O(m\log m)$。


```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#define N 2000010
#define inf 1e18
#define ll long long
using namespace std;
vector<int> G[N];
int n,m,vis[N],id[N],tot,tot0,cnt;
ll sum0,sum[N],node;
int hd[N];
ll dis[N];
struct E{
    int u,v;
	ll w;
	int col,p,nxt;
}e0[N*2],e[N*2];
bool cmp(int x,int y){
    return e0[x].col<e0[y].col;
}
void add(int u,int v,ll w){
    cnt++;
    e[cnt].v=v;
    e[cnt].w=w;
    e[cnt].nxt=hd[u];
    hd[u]=cnt;
}
void dijk(){
    priority_queue<ll,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
    for(int i=2;i<=node;i++)
        dis[i]=inf;
    q.push(make_pair(dis[1],1));
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int i=hd[u];i;i=e[i].nxt){
            int v=e[i].v;
            if(dis[u]+e[i].w<dis[v]){
                dis[v]=dis[u]+e[i].w;
                q.push(make_pair(dis[v],v));
            }
        }
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int u,v,col,p;
    cin>>n>>m;
    node=n;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>col>>p;
        add(u,v,p);
        add(v,u,p);
        tot0++;
        e0[tot0].u=u,e0[tot0].v=v,e0[tot0].col=col,e0[tot0].p=p,e0[tot0].w=inf;
        G[u].push_back(tot0);
        tot0++;
        e0[tot0].u=v,e0[tot0].v=u,e0[tot0].col=col,e0[tot0].p=p,e0[tot0].w=inf;
        G[v].push_back(tot0);
    }
    for(int i=1;i<=n;i++){
        tot=0;
        for(auto j:G[i])id[++tot]=j;
        sort(id+1,id+tot+1,cmp);
        for(int j=1,k;j<=tot;j=k+1){
            k=j;
            while(k<=tot&&e0[id[k]].col==e0[id[j]].col)k++;
            k--;
            sum[e0[id[j]].col]=0;
            for(int l=j;l<=k;l++)
                sum[e0[id[j]].col]+=e0[id[l]].p;
            node++;
            add(i,node,0);
            for(int l=j;l<=k;l++){
                u=e0[id[l]].u,v=e0[id[l]].v;
                if(u==i)swap(u,v);
                add(node,u,sum[e0[id[j]].col]-e0[id[l]].p);
                add(u,node,0);
            }
        }
    }
    dijk();
    if(dis[n]==inf)cout<<-1;
    else cout<<dis[n];
    return 0;
}
```

---

## 作者：_lmh_ (赞：0)

有 $M$ 种可用的颜色，所以每次修改颜色时，一定能找到一种未被使用的颜色（剩余 $M-1$ 条边无法取遍 $M$ 种颜色），因此最优策略下，只要一条边经过了修改，那么之后就可以自由地使用这条边。

可以得出如下结论：一条边能被使用，当且仅当它被修改过或者当前节点相邻的其余所有同色边都被修改过。

首先，两次经过同一个节点是没有意义的（保持所有边的修改情况不变，删掉这个环即可）。同时我们发现，如果我修改了一条边同色的所有相邻边，然后沿着这条边走了一步，之后再走到那些被修改的边相邻的节点也是没有意义的（保持修改状态不变，这一步直接走过去即可）。

因此我们认为，修改即将要走过的边的操作是“好的”，因为这样修改之后可以减小后续操作的代价：下一步如果选择修改所有同色的相邻边，可以少修改一条；修改其余所有边的操作是“不好的”，因为这样操作无法减少后续操作的代价。

所以如果一个“不好的”操作的代价大于“好的”操作，就一定会选择好的操作。进而可以得出，一组同色边当中，只有权重大于一半的边可能会触发“不好的”操作——这样的边至多只有一条。

现在给每条边建立一个虚点 $V'_i$，表示修改了这条边并走过去；每个原来的点 $V_i$ 代表将所有相邻边视为没有修改的情况。

假设存在一条 $(u,v,c,w)$ 的边 $i$，那么从 $V_u,V_v$ 向 $V'_i$ 连边，权值为 $w$；从 $V_i'$ 向 $V_u,V_v$ 连边，权值为 $0$；从 $V_u,V_v$ 向对方连有向边，权值为其余所有相邻同色边的权值之和。

最后一种情况：进行一个好操作之后，进行一个“不好的”操作，因为之前的操作可以少修改一条边。这样从 $V'_i$ 向最大的相邻同色边连向的节点 $V$ 连边，就可以处理这种情况。

最后跑一遍最短路就做完了，总复杂度 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=300007;
ll n,m,dis[N],vis[N],U[N],V[N],col[N],w[N];
map<ll,ll> mp[N],mx1[N],mx2[N];
vector<pair<ll,ll> > to[N];
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<> > pq;
void update(int u,int c,int i){
	if (mx1[u].find(c)==mx1[u].end()){
		mx1[u][c]=i;return;
	}
	if (w[mx1[u][c]]<w[i]){mx2[u][c]=mx1[u][c];mx1[u][c]=i;return;}
	if (mx2[u].find(c)==mx2[u].end()||w[mx2[u][c]]<w[i]) mx2[u][c]=i;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for (int i=1;i<=m;++i){
		cin>>U[i]>>V[i]>>col[i]>>w[i];
		mp[U[i]][col[i]]+=w[i];
		mp[V[i]][col[i]]+=w[i];
		update(U[i],col[i],i);
		update(V[i],col[i],i);
	}
	for (int i=1;i<=m;++i){
		to[U[i]].emplace_back(n+i,w[i]);
		to[V[i]].emplace_back(n+i,w[i]);
		to[n+i].emplace_back(U[i],0);
		to[n+i].emplace_back(V[i],0);
		to[U[i]].emplace_back(V[i],mp[U[i]][col[i]]-w[i]);
		to[V[i]].emplace_back(U[i],mp[V[i]][col[i]]-w[i]);
		int p1=mx1[U[i]][col[i]],p2=mx2[U[i]][col[i]];
		if (i!=p1) to[n+i].emplace_back(U[p1]^V[p1]^U[i],mp[U[i]][col[i]]-w[p1]-w[i]);
		else if (p2) to[n+i].emplace_back(U[p2]^V[p2]^U[i],mp[U[i]][col[i]]-w[p2]-w[i]);
		p1=mx1[V[i]][col[i]],p2=mx2[V[i]][col[i]];
		if (i!=p1) to[n+i].emplace_back(U[p1]^V[p1]^V[i],mp[V[i]][col[i]]-w[p1]-w[i]);
		else if (p2) to[n+i].emplace_back(U[p2]^V[p2]^V[i],mp[V[i]][col[i]]-w[p2]-w[i]);
	}
	memset(dis,0x3f,sizeof(dis));dis[1]=0;
	pq.emplace(0,1);
	while(!pq.empty()){
		int u=pq.top().second;pq.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (auto p:to[u]) if (dis[p.first]>dis[u]+p.second){
//			assert(p.second>=0);
			pq.emplace(dis[p.first]=dis[u]+p.second,p.first);
		}
	}
	cout<<(dis[n]>1e17?-1:dis[n])<<endl;
	return 0;
}
```

---

## 作者：AKPC (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/vsgpbjxj.png)

**题意**

有一张无向图，图上每条边都有各自的颜色，不一定两两不同，也不一定都相同。

每次走到一个节点，你可以给机器人一种颜色，机器人会把这个点所有该颜色的出边全部框选，进行如下判断：

- 如果只有一条，机器人会顺着这条边走到它指向的节点。
- 反之，机器人会原地不动。

在把机器人放到这张图之前，你可以花费一些代价改变一些边的颜色，每条边都有一个代价，改动某条边需要花费这条边的代价。

你需要找到最小的代价，使得机器人可以从 $1$ 节点走到 $n$ 节点。

**思路**

对于目前在一个节点 $u$，你给出了颜色 $c$，那么对于每条 $u\to v$ 的颜色为 $c$ 的边，如果要走这条边，有两种决策：

- 改该边为 $u$ 的所有出边都未出现过的颜色，代价 $P_{u\to v}$。
- 改掉除了该边之外所有 $u$ 出边的同色边的颜色，代价是 $u$ 所有同色出边的 $P$ 之和减去 $P_{u\to v}$。

一种朴素的做法就是把一条边的边权设为上面两种决策中代价最小值然后跑 dijkstra，但是如果出现 $u\to v$，$v\to w$ 这条路径颜色相同，但是没有在 $u$ 节点改变 $u\to v$ 的颜色，那么这两条边在 $v$ 节点都会被计算代价，所以一个节点对两个决策代价取 $\min$ 不保证最优。

如果我们能把两种决策的边都建出来，就可以保证正确性了。但是如果在原图设边权，是不好考虑代价设定的。因此，我们需要一些虚点来辅助。

![](https://cdn.luogu.com.cn/upload/image_hosting/mxljevyt.png)

图中红边都是 $1$ 节点红颜色的**实边**，黑框节点都是**实点**，而红框节点 $x$ 是专门为 $1$ 的红色出边建立的**虚点**，黑边都是虚边。

具体的建图方案是：

- 建立 $1\to x$，边权为 $0$。
- 建立 $x\to 2,3,4$，对于 $x\to y$，其边权为 $\sum_{i=2}^4P_{1\to i}-P_{1\to y}$，这构造了第二种决策的路径。
- 建立 $2,3,4\to x$，边权 $0$，便于 dijkstra 反悔。

跑 dijkstra 即可。

**代码**

[code](/paste/vwjqudaw)。

---

## 作者：Z1qqurat (赞：0)

一雪前耻题。首先发现颜色范围 $\in[1,m]$，也就是说一定能将所有边变成不同的颜色，所以根本不需要考虑具体染成什么颜色，只要图联通就一定会有解。于是我们想，如果走 $(u,v,c,w)$ 这条边，我们要付出多少代价：

* 如果这是 $u$ 开头的唯一一条颜色 $c$ 边，那么走它不需要代价，$u\xrightarrow{0} v$。
* 否则，要么将这条边修改为一条不同颜色的边，要么将 $u$ 开头的其他 $c$ 边全部改成不同颜色，$u\xrightarrow{\min(w,sum_{u,c})} v$，这里 $sum_{u,c}$ 表示从 $u$ 开头的颜色为 $c$ 的边的 $w$ 之和。

你以为这样就结束了？其实还有一种情况，如果从 $x\to y\to z$，$(x,y),(y,z)$ 原色都是 $c$，通过 $w_{x,y}$ 的代价将 $(x,y)$ 修改为了一种不同的颜色，通过 $s_{y,c}-w_{y,z}$ 的代价将 $(y,z)$ 的同色边修改为不同颜色，那么直接叠加两个代价其实是错的，实际上这一共只需要 $s_{y,c}-w_{y,z}$ 的总代价，因为在 $(y,z)$ 之前 $(x,y)$ 已经被修改掉了颜色。于是考虑我们建出一个虚点 $vt$，然后建边 $x\xrightarrow{0} vt, vt\xrightarrow{s_{y,c}-w_{y,z}} z$，这样 $x\to vt\to z$ 的路径就代表了这种情况的代价。

分析一下这种建边下虚边的数量，发现如果我们给一个边颜色全部相同的菊花，那么虚边数量可能达到 $\mathcal{O}(m^2)$，考虑是否出现了重复连接的边：

![](https://pic.imgdb.cn/item/65b8478f871b83018a417b8e.jpg)

发现我们其实并不需要对每一组 $x\to y\to z$ 都连一次，这些边中对于固定的虚点 $vt$ 都是一样的。这样连边就保证虚边数量是 $\mathcal{O}(m)$ 的了。

注意不能直接对每种颜色开一个虚点，只能对于每个中间点 $y$，它的出边颜色 $c$ 开一个新的虚点 $vt$，这样才能保证正确。由于边是双向边，所以虚点数量上界是 $2m$。总体复杂度 $\mathcal{O}(n\log n+m)$，瓶颈在 Dijkstra。

[Submission.](https://atcoder.jp/contests/joi2021ho/submissions/49800597)

---

## 作者：wxzzzz (赞：0)

### 思路

有一个显然但是错误的思路：将一条边 $(x,y)$ 的权值当作 $\displaystyle\min\Big(\sum_{c(x,k)=c(x,y)}p(x,k)-p(x,y),p(x,y)\Big)$，直接跑最短路。

这样会漏掉一种情况：走 $x\to y\to z$，最优方案可能是将所有 $(x,k)\ (c(x,k)=c(x,y),k\ne y)$ 都改成其他颜色，然后以 $0$ 的代价走过 $(x,y),(y,z)$。下图就是例子（$1\to 2\to 5$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/4zh8knr8.png)

考虑建虚点处理上述情况：

1. 对每个点的每一种颜色的出边建一个虚点。对于一条边 $(x,y)$，令 $x$ 的颜色为 $c(x,y)$ 的虚点为 $u$。

1. 连边 $(x,u)$，令 $c(x,u)=0,p(x,u)=0$。（注意，虚点连出的都是有向边，下同）

1. 连边 $(u,y)$，令 $c(u,y)=0,p(u,y)=\displaystyle\sum_{c(x,k)=c(x,y)}p(x,k)-p(x,y)$。

1. 连边 $(y,u)$，令 $c(y,u)=0,p(y,u)=0$。

如下图：（由于软件显示问题，下图中用 $6.,7.$ 代替 $6,7$）

![](https://cdn.luogu.com.cn/upload/image_hosting/j5xvcfah.png)

可以发现，建立虚点后，所有 $x\to y\to z$ 的路径包含了所有可能的最优路径，跑最短路即可。

### 代码

这题的出边需要排序，因此用 vector 存图。

注意千万不能用迭代器遍历出边，因为加边操作会使迭代器失效，从而 RE。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt;
long long s[1000005], dis[1000005];
bitset<1000005> vis;
struct graph {
    int y, c;
    long long p;
};
vector<graph> g[1000005];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
bool cmp(graph x, graph y) {
    return x.c < y.c;
}
void dijkstra() {
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0, q.push({0, 1});

    while (!q.empty()) {
        int x = q.top().second;
        q.pop();

        if (vis[x])
            continue;

        vis[x] = 1;

        for (graph i : g[x]) {
            int y = i.y, c = i.c;
			long long p = i.p;

            if (dis[x] + p < dis[y]) {
                dis[y] = dis[x] + p;
                q.push({dis[y], y});
            }
        }
    }
}
int main() {
    cin >> n >> m;
    cnt = n;

    while (m--) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        g[x].push_back({y, a, b});
        g[y].push_back({x, a, b});
    }

    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end(), cmp);

        for (int j = 0; j < g[i].size(); j++)
            if (g[i][j].c)
                s[g[i][j].c] += g[i][j].p;

        for (int j = 0; j < g[i].size(); j++) {
            int y = g[i][j].y, c = g[i][j].c;
            long long p = g[i][j].p;

            if (!c)
                continue;

            if (!vis[c]) {
                g[i].push_back({++cnt, 0, 0});
                vis[c] = 1;
            }

            g[cnt].push_back({y, 0, s[c] - p});
            g[y].push_back({cnt, 0, 0});
        }

        for (int j = 0; j < g[i].size(); j++)
            if (g[i][j].c)
                s[g[i][j].c] = vis[g[i][j].c] = 0;
    }

    dijkstra();

    if (dis[n] > 1e18)
        cout << "-1";
    else
        cout << dis[n];

    return 0;
}
```

---

