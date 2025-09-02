# [AGC006F] Blackout

## 题目描述

我们有一个 $N$ 行 $N$ 列的矩阵。第 $i$ 行第 $j$ 列的格子表示为 $(i,j)$。

开始时，有 $M$ 个格子是黑色，其他格子都是白色。特别地，开始时格子 $(a_{1},b_{1}),(a_{2},b_{2}),\cdots, (a_{M},b_{M})$ 是黑色。

スヌケ君会按照以下的规则尽可能多的将白色格子涂成黑色：

- 对于整数 $1\le x,y,z\le N$，如果 $(x,y)$ 和 $(y,z)$ 都是黑色，那么就把 $(z,x)$ 涂黑。

请计算出当再也没有白色格子能被涂黑时，黑色格子的个数。

## 说明/提示

- $1\le N \le 10^{5}$
- $1\le M \le 10^{5}$
- $1\le a_{i},b_{i} \le N$
- 各黑格坐标互不相同

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
1 1
1 2```

### 输出

```
4```

## 样例 #3

### 输入

```
4 3
1 2
1 3
4 4```

### 输出

```
3```

# 题解

## 作者：Ebola (赞：30)

2024.07.21 update. 更新了本题结论的证明。

---

### 题意

你有一个 $N\times N$ 的网格，一开始有 $M$ 个格子是黑色的。

如果格子 $(x,y)$ 和 $(y,z)$ 都是黑色的，那你可以把 $(z,x)$ 也给涂黑

问最多能有多少个黑格子

### 题解

问题转化一下：你有一个 $N$ 个点的有向图，一开始连了 $M$ 条边，假如存在边 $x\to y$ 和 $y\to z$，那么你可以连边 $z\to x$。这样就可做多了。

我们考虑对原图进行三染色。假设某一个点是红，他连向的所有点就是蓝；蓝连向的所有点都是绿；绿连向的所有点又是红。

假如我们对某个弱连通块染色失败，那么这个弱连通块会被操作成一个完全图（见下方证明），那么这种染色失败的弱连通块对答案的贡献就是 $n\times n$（$n$ 表示弱连通块内点的数量）

假如染色成功，但是只存在一种或两种颜色，那么这个弱连通块分成了两层，并且只存在上层指向下层的边。这种情况下根本无法进行操作，所以对答案的贡献就是弱连通块的初始边数

假如染色成功，并且三种颜色都存在，那么在若干次操作之后，任意一个红点都会有直接连向所有蓝点的出边，类似的，蓝连向绿，绿连向红。这种情况称为 “全连接”（见下方证明）。所以这种情况对答案的贡献就是 $cnt_r\times cnt_b+cnt_b\times cnt_g+cnt_g\times cnt_r$，
其中 $cnt_x$ 表示颜色为 $x$ 的点在弱连通块里有多少个，$r,g,b$ 是颜色缩写

就这样直接做就行了，代码实现非常简单，$ans$记得要开 `long long`

```cpp
#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

const int N=200010;
struct Edge{int to,capa,next;} e[N];
int h[N],sum=0,n,m;
bool vis[N];
int cmt,cnt,col[N],c[3];
bool falun;

inline int color(const int &x)
{
	if(x>=3) return x-3;
	if(x<0) return x+3;
	return x;
}

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	c[col[u]]++;vis[u]=1;cnt++;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		cmt+=(e[tmp].capa==1);
		int v=e[tmp].to;
		if(!vis[v]) col[v]=color(col[u]+e[tmp].capa),dfs(v);
		else if(col[v]!=color(col[u]+e[tmp].capa)) falun=0;
	}
}

int main()
{
	int u,v;
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		u=read();v=read();
		add_edge(u,v,1);
		add_edge(v,u,-1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		memset(c,0,sizeof(c));
		cmt=cnt=0;falun=1;
		dfs(i);
		if(!falun) ans+=1ll*cnt*cnt;
		else if(c[0]&&c[1]&&c[2]) ans+=1ll*c[0]*c[1]+1ll*c[1]*c[2]+1ll*c[2]*c[0];
		else ans+=cmt;
	}
	printf("%lld\n",ans);
	return 0;
}
```

### 证明路线

先依次证明以下四条性质。

**性质1：** 完全图具有 “感染性”。即：在一个完全图的基础上
连接任意一个点，这个点都会和原图的所有点形成双向边、以及一个自环，
从而成为更大的完全图。
所以只要一个弱连通块存在完全子图，那么它就会演化为完全图

**性质2：** 四元环会演化出二元完全子图，所以会被感染为完全图。

**性质3：** 五元环会演化出二元完全子图，所以会被感染为完全图。

**性质4：** 设 $n\;(n\geq 7\; \text{且不是}\; 3 \; \text{的倍数})$ 元环中，点的编号为 $1,...,n$；首先可以生成 $3\to 1,\; 1\to (n-1)$ 两条边，这两条边又可以引出 $(n-1)\to 3$，此时 $3,4,...,(n-1)$ 构成一个 $(n-3)$ 元环。由归纳法得到：该 $n$ 元环会演化出四元环或五元环。因此由前三条性质，它最终演化为完全图。

借助前四个性质，可以说明：染色失败时，最终会变成一个完全图。（因为染色失败必然包含一个长度不能被 $3$ 整除的环）

**性质5：** 三元链可以变成三元环。

**性质6：** 对于成功染色且有三种颜色的情况，
如果两条三元环 $r_1\to g_1\to b_1\to r_1$ 与 $r_2\to g_2\to b_2\to r_2$ 之间存在初始连接，
那么它们会演化为全连接。

借助性质 5、性质 6，可以说明：对于成功染色且有三种颜色的情况，最终整个弱连通块会演变成三层全连接。（每一对三元环只要存在初始连接，就会演化成全连接，而弱连通块里三元环都是直接或间接相连的，所以最终全部演化为全连接）

---

## 作者：sry_ (赞：12)

#### AGC006F Balckout

##### 题意

给定一个 $n\cdot n$ 的网格图，有些格子为黑。如果 $(x,y),(y,z)$ 均为黑，则 $(z,x)$ 也为黑，求最终黑色点的个数。

$1\leq n,m\leq 10^5$

##### 题解

该题解主要证明其他博客上很显然的结论。。。

很容易想到若存在 $(x,y)$ 则建图 $x\rightarrow y$ 。

考虑一个弱联通图的情况，而整图的情况可以看成弱联通图的乘积。

由于操作可以分为 $y$ ，指向 $y$ 的与被 $y$ 指的，有三种情况，考虑对该图三染色，即若有 $x\rightarrow y$  那么 $col_y=col_x+1\bmod 3$ ，注意图是若联通。

那么会发生一下三种情况之一。

- 不存在三染色，即存在一条边满足 $col_y\neq col_x+1\bmod 3$
- 存在三染色，但仅用一/两种颜色
- 存在三染色，且三种颜色均用了

先考虑情况 $2$ 和 $3$ ，最后考虑情况 $1$ 。

**情况二**

结论：黑色点的个数等于原先边的个数。

若图只能用 $1/2$ 种颜色那么肯定不会存在 $x\rightarrow y,y\rightarrow z$ 的边，那么不会产生新的边，即不会有新的黑点产生。

**情况三**

结论：我们设 $c_{0/1/2}$ 分别表示 $col=0/1/2$ 的个数，那么黑点个数为 $c_0c_1+c_1c_2+c_2c_0$ ，即集合按照 $0/1/2$ 顺序连边。

如果图能被三染色那么肯定存在一条链 $u\rightarrow v\rightarrow w$ 满足 $col_u=0,col_v=1,col_w=2$ 。

显然这三个点肯定满足上述结论。

考虑归纳构造，若当前图 $G$ 满足构造，新加入一条边 $u\rightarrow p$ 。（由于 $u,v,w$ 等价故我们仅用考虑 $u$ 的情况）

定义 $\{0/1/2\}$ 表示 $col=0/1/2$ 点的集合。

由于 $\{2\}\rightarrow u,u\rightarrow p$  ，那么 $p\rightarrow\{2\}$ 。

由于 $p\rightarrow \{2\},\{2\}\rightarrow \{0\}$ ，那么 $\{0\}\rightarrow p$ 。

可以发现无法存在其余边的出现，得证。

如果 $p\rightarrow u$ 类似，这里不在阐述。

**情况一**

结论：黑点个数为所在弱联通块点的个数的平方。

先去考虑一个子问题，由于三染色过程形成的是一个 $dfs$ 树，而若存在矛盾仅能为返祖边，那么我们肯定能将其若联通块进行三染色并且会附赠一些矛盾的边。

若先不考虑矛盾的边那么依据情况三我们已经得到一个 $\{0\}\rightarrow \{1\},\{1\}\rightarrow \{2\},\{2\}\rightarrow \{0\}$ 的边集。

**解决当前问题的小结论**

结论：若在一个三染色图上加入一个矛盾边那么肯定能让一个集合 $\{x\},x\in\{0,1,2\}$ 满足 $\{x\}\rightarrow \{x\}$ 。

证明这个也很简单，我们继续沿用情况三的 $u,v,w$ ，证明也和情况三的类似。

- 若存在 $u_1\rightarrow u_2 $ ，根据 $u_2\rightarrow \{1\}$ 可得 $\{1\}\rightarrow u_1$ ，又由于 $u_1\rightarrow \{1\}$ ，那么 $\{1\}\rightarrow \{1\}$ 。

- 若存在 $u\rightarrow w$ ，由于 $w\rightarrow u$ 可得 $u\rightarrow u$ 。可以归纳到上述证明。

得证。

继续考虑情况 $1$ 的证明，根据当前的小结论可以得到该图存在一个 $\{x\}\rightarrow \{x\}$ 的边，不妨将其设为 $\{0\}\rightarrow \{0\}$ 。

由于 $\{0\}\rightarrow\{0\},\{0\}\rightarrow \{1\}$ 可得 $\{1\}\rightarrow \{0\}$ 。

由于 $\{1\}\rightarrow \{0\},\{0\}\rightarrow \{1\}$ 可得 $\{1\}\rightarrow \{1\}$  。

由于 $\{1\}\rightarrow \{1\},\{1\}\rightarrow \{2\}$ 可得 $\{2\}\rightarrow \{1\}$ 。

同理可得 $\{1\}\rightarrow \{2\},\{2\}\rightarrow \{2\}$ 。

由于任意两点均可以直接到达，图为完全图，那么黑点个数显然为弱联通块个数的平方。

得证。



---

## 作者：zzw4257 (赞：10)

~~最近作业的F终于又有一个会做了~~

>给定一个初始有向图，你可以执行若干次操作:当$(x,y),(y,z)$($x,y$不全相等)存在且$(z,x)$不存在时你可以把$(z,x)$加入边集

简单画一些图，你会发现结果有三种

- 一条边都加不了
- 加满到完全图
- 加了一些边

以一条长度为7的链为例，易发现点可以分为$\{1,4,7\},\{2,5\},\{3,6\}$三组组内无连边，相邻顺时针(且让我这样说吧)间存在连边

但当你破坏这个美妙的性质跨组在$7,1$间连边或者加个自环后就会迭代到完全图

稍微拓展一下会发现可以 **$3$染色** 的图有与链一样的性质

具体的，我们定义一个有向弱连通图可以 **$3$染色** 当且仅当原图可以划分成三个点集$A,B,C$,只存在$A\to B,B\to C,C\to A$的连边

这个东西可以简单的用遍历每条边两次的$dfs$实现判定，并统计点集大小

然后我们再考虑一下剩下的情况，就只有染色出矛盾和只能染出两种颜色的可能

你可能会说二阶含双边菊花图是个反例包含了两种情况，因此我们规定染色出矛盾是更优先的判定标准

故形式化写下结论,对原图任意弱联通分量$G(V,E)$有

- 可 **$3$染色**:$ans=AB+BC+CA$
- 染色出矛盾（优先）:$ans=(A+B+C)^2$
- 只能染出两种颜色:原边数

```cpp
#include<bits/stdc++.h>
#define N 100001
using namespace std;
typedef long long ll;
int n,m,col[N],vis[N],flag;
ll ans;
vector<int>v[3];
struct Edge{int v,to;};
vector<Edge>g[N];
inline void dfs(int x){
	int y;vis[x]=1;v[col[x]].push_back(x);
	for(auto t:g[x])if(!vis[y=t.to])col[y]=(col[x]+t.v)%3,dfs(y);
	else if(col[y]^((col[x]+t.v)%3))flag=1;
}
int main(void){
	int i,j,x,y,res;scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i)scanf("%d%d",&x,&y),g[x].push_back({1,y}),g[y].push_back({2,x});
	for(i=1;i<=n;++i)if(!vis[i]){
		for(j=0;j<3;++j)v[j].clear();
		flag=0;dfs(i);res=0;
		if(flag)ans+=(0ll+v[0].size()+v[1].size()+v[2].size())*(0ll+v[0].size()+v[1].size()+v[2].size());
		else if(v[0].size()*v[1].size()*v[2].size())ans+=1ll*v[0].size()*v[1].size()+1ll*v[1].size()*v[2].size()+1ll*v[2].size()*v[0].size();
		else{for(j=0;j<3;++j)for(int x:v[j])res+=g[x].size();ans+=res>>1;}
	}printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Cocoly1990 (赞：7)

题意简述
----
有一张 $n\times n$ 的网格，一开始共有 $m$ 个格子被涂成黑色，其它所有格子都是白色的。

如果存在三个正整数 $x, y, z$（$1\le x, y, z\le n$），满足 $\left(x, y\right)$ 和 $\left(y, z\right)$ 都是黑色的，那么就可以将 $\left(z, x\right)$ 涂成黑色。

求最多能使棋盘上有多少个黑色的格子。

思路
-----
以下部分内容来自于教练的讲义，融入了笔者的思考

认真思考，我们可以发现以下性质
如果 $\left(x, y\right)$ $\left(y, z\right)$ 和 $\left(z, x\right)$ 中任两个是黑色的，则第三个是黑色的。

更进一步的是，如果对任意 $x\in X, z\in Z$，都存在 $y_0 \in Y$ 满足 $\left(x, y_0\right)$ 和 $\left(y_0, z\right)$ 同时为黑，那么 $\left(z,x\right)$ 也是黑的。

我们不妨把一个黑色的格子当做两个元素之间产生关联。这种关联是单向的，即 $\left(x, y\right)$ 是黑的不能得出 $\left(y, x\right)$ 也是黑的。

考虑在膜 $3$ 的意义下建图

我们假设有三个**互不相交**的**非空**集合正解 $X, Y, Z$ 他们分别用 $0,1,2$，每个元素必然存在于其中一个点集。

![](https://cdn.luogu.com.cn/upload/image_hosting/kv9l2s4z.png)

我们可以假设 $X$ 到 $Y$，$Y$ 到 $Z$ 的距离为$1$.

那么在膜 $3$ 意义下，各集合之间的距离就可以算出，如 $Z$ 到 $X$ 的距离应该为 $1$，因为在膜 $3$ 意义下 $\left(1 + 2\right)=0$

显然对于不同连通块，我们可以分开处理。我们可以分成一下三种情况处理。同样显然的是，**每两点存在联系，就表明存在一个黑块。**

1. 如果一个连通块的点集可以被划分为两个不相交的集合，且**只有**其中一个集合的点向另一个集合连边，**每个集合内部没有连边**，那么这个连通块不能产生新的边。此时仅需统计边数即可，值得注意的是，因为我们建的是**有向图**，所以统计出来的边数除以 $2$ 即可。

2. 如果一个连通块的点集可以被划分为三个不相交的集合 $X,Y,Z$，且 $X$ 中的每个点都与 $Y$ 中的至少一个点连边，其他集合间的关系相同。那么这个连通块的最终状态为 $X$ 中所有点向 $Y$ 中所有点连边，其他两个集合关系相同。最终边数为 $ X \times Y + Y \times Z  + X \times Z $。

3. 如果一个连通块不符合上面说的任意一种情况，如集合内部有连边，**则最终状态为集合内部所有点对之间都有连边（包括自环）**。最终边数为**点数平方**。

具体怎么判断呢，我们可以进行**染色**，对于每个节点，我们用 $col\left[\right]$ 记录下它所在的集合（同上图三个集合），对于任意两个联通点，如果 `col[v] != (col[u] + e[j].w) % 3` 则说明他们不分属两个集合，即集合内有边相连。对于上述 $\texttt{2}$ 仅需判断是否三个集合内都有点即可。

综合时间复杂度 $\mathcal{O}\left(n+m\right)$，可以通过本题，当然了你不吸氧手写队列也并不复杂。
[![WFJqf0.md.png](https://z3.ax1x.com/2021/07/12/WFJqf0.md.png)](https://imgtu.com/i/WFJqf0)
还算过得去/cy

code
---
```cpp
#include<bits/stdc++.h>
#define Maxn 100007
#define ll long long
using namespace std ;
struct Edge 
{
	int to , w , next ;
}e[Maxn << 1] ;

int head[Maxn] , col[Maxn] , cnt[3] , tot , n , m , check , edgecnt ;
ll ans ; 
bool vis[Maxn] ;
queue <int> q ;
void add(int x , int y , int w)
{
	e[++ tot].to = y , e[tot].next = head[x] , head[x] = tot , e[tot].w = w ;
}
void clear(queue<int>& q)
{
    queue<int> empty ;
    swap(empty , q) ;
}
int main()
{
	int u , v ;
	cin >> n >> m ;
	for(int i = 1 ; i <= m ; i ++)
	{
		cin >> u >> v ;
		add(u , v , 1) ;
		add(v , u , 2) ;
	}
	for(int i = 1 ; i <= n ; i ++)
		if(! vis[i])
		{
			check = edgecnt = cnt[0] = cnt[1] = cnt[2] = 0 ;
			clear(q) ; q.push(i) ;
			vis[i] = 1 ;
			while(! q.empty())
			{
				u = q.front() ;
				q.pop() ;
				++ cnt[col[u]] ;
				for(int j = head[u] ; j ; j = e[j].next)
				{
					++ edgecnt ;
					v = e[j].to ;
					if(vis[v])
						if(col[v] != (col[u] + e[j].w) % 3) check = 1 ;
					if(! vis[v])
					{
						vis[v] = 1 ; 
						col[v] = (col[u] + e[j].w) % 3 ;
						q.push(v) ;
					}
				}
			}
			if(check) ans += 1ll * (cnt[0] + cnt[1] + cnt[2]) * (cnt[0] + cnt[1] + cnt[2]) ;
			else if(cnt[0] && cnt[1] && cnt[2]) ans += 1ll * cnt[0] * cnt[1] + 1ll * cnt[1] * cnt[2] + 1ll * cnt[2] * cnt[0] ;
			else ans += edgecnt >> 1 ;
		}
		cout << ans ;
		return 0 ;
}
```



---

## 作者：sky_of_war (赞：2)

> 自闭了...之前做过的题现在又不会了...

同步更新于我的博客：[「AGC 006F」Blackout](https://www.skyofwar.net/2019/05/13/154.html)

把方格$(i,j)$想象为一条边$i \rightarrow j$。
那么对于输入，可以得到一张有向图。

考虑用三种颜色给原图每个联通块染色。
令这三种颜色分别为$0,1,2$，且$0 \rightarrow 1 \rightarrow 2 \rightarrow 0$。

可以发现题目中的染色方法便是这张图上，若某个$0\rightarrow 1$且$1\rightarrow2$，则产生$2\rightarrow 0$的边。
那么在染色后，分为三种情况：

 - 如果染色成功了，那么当前联通块对答案的贡献便是:所有$0$向$1$连边，所有$1$向$2$连边，所有$2$向$1$连边的总边数
 - 如果不成功但是用了每种颜色，画图可知一定是出现了环（包括自环），于是这个联通块可以被连成一个完全图
 - 如果不成功也没有使用每一种颜色，那么这个联通块的贡献就是输入的边

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 5e5 + 10;

int n, m; 
ll to[MAXN << 1], nxt[MAXN << 1], h[MAXN], tot;
ll c[MAXN], w[MAXN << 1];
ll ans, f[4], flag;

inline void _read(int &x)
{
	x = 0;
	char t = getchar();
	while (!isdigit(t)) t = getchar();
	while (isdigit(t))
	{
		x = x * 10 + t - '0';
		t = getchar();
	}
}

inline void ae(const int &u, const int &v, const int &c)
{
	to[++tot] = v;
	nxt[tot] = h[u];
	w[tot] = c;
	h[u] = tot;
}

inline void dfs(int u)
{
	f[c[u]]++;
	for (int i = h[u]; i; i = nxt[i])
	{
		if (w[i] == 1)++f[3];
		if (!(~c[to[i]]))
		{
			c[to[i]] = (c[u] + w[i]) % 3;
			dfs(to[i]);
		}
		else if (c[to[i]] != (c[u] + w[i]) % 3)
			flag = 1;
	}
}

int main()
{
	_read(n), _read(m);
	for (int i = 1, u, v; i <= m; ++i)
	{
		_read(u), _read(v);
		ae(u, v, 1), ae(v, u, 2);
	}
	memset(c, -1, sizeof c);
	for (int i = 1; i <= n; ++i)
		if (!(~c[i]))
		{
			f[c[i] = 0] = f[1] = f[2] = f[3] = flag = 0;
			dfs(i);
			if (flag)
			{
				ll cnt = f[0] + f[1] + f[2];
				ans += cnt * cnt;
				continue;
			}
			if ((!f[0]) || (!f[1]) || (!f[2]))
			{
				ans += f[3];
				continue;
			}
			ans += f[0] * f[1];
			ans += f[1] * f[2];
			ans += f[2] * f[0];
		}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

~~在冬令营听讲座根本听不懂的我跑过来水题解了~~

乍一看题面：哇，这是什么，根本不可做的样子！那个奇奇怪怪的限制好像并不是很好转移的样子！

然后讲座就说了：我们可以将这道题转换成一个图论问题，建出$n$个点，我们把原问题中的每个点$(x,y)$转换为：在新图中，连一条有向边$(x,y)$。如果图中存在边$(x,y),(y,z)$，连边$(z,x)$，求最终得到的图中边的数量。

首先，这个问题肯定是关于弱连通分量（即将所有有向边看作无向边形成的连通块）独立的。

我们发现，在一次操作中，必有点$y$的入度和出度都不为$0$。

我们关于一个出入度都不为$0$的点$y$做分析：

显然，所有被$y$指向的点都会连一条边指向所有指向$y$的节点。

那么我们就可以关于这个$y$点将图分成三层：指向$y$的，$y$本身，被$y$指向的。

我们对于任何一个这样的$y$，都进行分层。

如果层与层之间相互独立（即不同的$y$的分层结果并不冲突），那我们就得到了一张有三部分的图。第一部分是在原图中指向某一个$y$的，第二部分是在原图中的某个$y$，第三部分是在原图中被某个$y$所指向的。

各部分内部没有边，而第一部分所有点连向第二部分所有点，第二部分所有点连向第三部分所有点，第三部分所有点连向第一部分所有点。

稍等，我们原分析中，不是只有“第三部分所有点连向第一部分所有点”吗？另外两条是怎么冒出来的？

我们可以将第一部分看作新的第二部分，第二部分看作新的第三部分，第三部分看作新的第一部分，这样便说明了三部分之间是互相连边的。

那么，这种情况下，这个弱连通分量的贡献就是$t_0*t_1+t_1*t_2+t_2*t_0$，其中$t_0,t_1,t_2$依次表示第一部分、第二部分、第三部分的节点数。

当然还有其它情况，即不同的$y$的分层结果冲突了。这可能意为着各部分内部连了边，可能意味着在某些部分间的边反掉了。

但不管怎么样，最终都会连成一张完全图。

我们可以证明一下：首先，如果多出来这么一条边，那肯定会出现一个二元环（同部分间的边一定可以直接连一条反边，异部分之间的边本来就成环）。

我们把这个二元环部分缩成一个点。则不管是连进来的边还是连出去的边，都可以连一条反边。而一旦反边被连，就又构成二元环，又可以缩进去。直到整个弱连通分量全都缩成一个点。

则如果出现分部冲突的局面，那直接贡献$sz^2$的答案。其中$sz$是弱连通分量大小。

我们可以通过染色解决这个问题。颜色$0$代表第一部分，颜色$0$的点指向的点为颜色$1$；颜色$1$代表第二部分，颜色$1$的点指向的点为颜色$2$；颜色$2$代表第三部分，颜色$2$的点指向的点为颜色$0$……

如果染色冲突，就是$sz^2$的那种情形；否则，就是$t_0*t_1+t_1*t_2+t_2*t_0$的情形。

等等，我们好像忘了一种极端情况！如果不存在这样出入度都不为$0$的点$y$怎么办？

还能怎么办！不存在这样的$y$，就意味着不存在可以连边的地方。答案为这个弱连通分量中边的个数。在染色中的体现，就是不存在某一部分。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,head[100100],cnt,col[100100],tot[3],TE;
typedef long long ll;
ll res;
struct node{
	int to,next,val;
}edge[200100];
void ae(int u,int v){
	edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=1,head[u]=cnt++;
	edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=-1,head[v]=cnt++;
}
bool Dye(int x){
	tot[col[x]]++;
	bool ret=true;
	for(int i=head[x];i!=-1;i=edge[i].next){
		TE+=(edge[i].val==1);
		if(col[edge[i].to]==-1){
			col[edge[i].to]=(col[x]+edge[i].val+3)%3;
			ret&=Dye(edge[i].to);
		}
		else ret&=(col[edge[i].to]==(col[x]+edge[i].val+3)%3);
	}
	return ret;
}
int main(){
	scanf("%d%d",&n,&m),memset(head,-1,sizeof(head)),memset(col,-1,sizeof(col));
	for(int i=1,x,y;i<=m;i++)scanf("%d%d",&x,&y),ae(x,y);
	for(int i=1;i<=n;i++){
		if(col[i]!=-1)continue;
		memset(tot,0,sizeof(tot)),TE=0;
		col[i]=0;
		if(!Dye(i)){res+=1ll*(tot[0]+tot[1]+tot[2])*(tot[0]+tot[1]+tot[2]);continue;}
		if(!tot[0]||!tot[1]||!tot[2]){res+=TE;continue;}
		res+=1ll*tot[0]*tot[1]+1ll*tot[1]*tot[2]+1ll*tot[2]*tot[0];
	}
	printf("%lld\n",res);
	return 0;
} 
```


---

## 作者：ETHANK (赞：0)

题目描述看上去很怪，先找一下等价命题，发现可以看做 $n$ 个点 $m$ 条边的图，且如果 $(u,v),(v,w)$ 有边，$(w,u)$ 也连一条边。再转换一下，对于 $v$ 的所有出边和入边对的节点，出点向入点连一条边。

首先观察到加边只在弱连通分量里进行，我们可以单独考虑每个这样的分量。

- 如果不存在一组 $(u,v),(v,w)$ 的话，图不会变化。
- 如果存在，将一个节点染红，其出点染蓝，入点染绿；入边对绿点或出边对蓝点的所有点染红，这些红点再继续引出新的点染色。染色若成功， $R\to G\to B\to R$ ，三种颜色构成了三元环。不难发现，颜色不同的节点两两之间都会有一条边。让我们更好的描述这个染色过程，实质上为起点为红色，该点连向的所有点染蓝色，蓝色点连向的所有点染绿色。设三色点数量分别为 $R,G,B$ ，那么该连通分量对答案贡献为 $RG+RB+GB$ 。
- 然而，我们忽略了在上述染色过程中失败的可能性，即出现染色的矛盾。不妨设矛盾出现在点 $u$ 且它同时染了红色和蓝色，根据上个染色的性质（红点和蓝点连边）， $u$ 会有自环。而自环又可以推出 $u$ 也能染绿色，进而发现所有点都向 $u$ 连边，而这引出了所有点的染色矛盾，整个图将变成包括自环的完全图。对答案贡献为 $tot^2$ ，其中 $tot$ 为连通分量大小。

时间复杂度： $O(n)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=1e5+5;
int n,m,col[N],flag,tot,etot;
bool vis[N];
ll ans,cnt[3];
struct Edge{int tp,to;};
vector<Edge> G[N];
void dfs(int u){
    ++cnt[col[u]];vis[u]=1;++tot;
    for(auto tmp:G[u]){
        etot+=(tmp.tp==1);
        int v=tmp.to;
        if(!vis[v]){
            col[v]=(col[u]+tmp.tp)%3;dfs(v);
        }else if(col[v]!=(col[u]+tmp.tp)%3)flag=0;
    }
}
int main(){
    n=read(),m=read();
    rep(i,1,m){
        int u=read(),v=read();
        G[u].push_back({1,v});
        G[v].push_back({2,u});
    }
    rep(i,1,n)if(!vis[i]){
        memset(cnt,0,sizeof(cnt));
        flag=1;etot=tot=0;
        dfs(i);
        if(!flag)ans+=1ll*tot*tot;
        else if(cnt[0]&&cnt[1]&&cnt[2]){
            ans+=cnt[0]*cnt[1]+cnt[1]*cnt[2]+cnt[2]*cnt[0];
        }else ans+=etot;
    }
    printf("%lld\n",ans);
    return 0;
}
```





---

## 作者：pufanyi (赞：0)

按照套路，我们应该把行和列看成点，即有$1\sim N$个点，每个格子$(x,y)$可以看成是$x\to y$的一条有向边。如果存在边$(x,y)$与边$(y,z)$，就连边$(z,x)$，询问最终有几条边。

我们将每个弱连通分量分开考虑。

我们考虑什么时候不能加边了，大概是这$2$中情况：

1. 已经是完全图了，边数为$n\times (n - 1)$。
2. 图被划分为$3$个集合（可以是空集）$A,B,C$，$A$的所有点向$B$的所有点连边，$B$的所有点向$C$连边，$C$的所有点向$A$连边，边数为$|A|\times |B| + |B|\times |C| + |C|\times |A|$。

我们发现一个点集如果会到情况$2$，那就到情况$2$，否则就是情况$1$。

于是我们尝试划分集合，将弱连通块中每个点一遍`dfs`染色，如果染色成功，那就是情况$2$，否则就是情况$1$。

---

## 作者：淇淇 (赞：0)

对于这样一个迷之题面大家第一反应大概是神题不可做，然而显然是可以做的，我们对每一个黑色方块(x,y)建立一条有向边，边权记为1,为了方便后续对这张图的遍历、染色工作，我们再建立一条反向的(y,x),不过为了与描述黑色方块的边区分开来，将边权标记为−1.

考虑图中的每一个联通块，我们对其进行三染色操作，基本染色原则为r -> g -> b -> r.

染色完毕后，我们不难发现以下规律：

对于每个无法成功染色的联通块（颜色相互冲突），根据题意，我们都可以构造一张可以含有自环的完全图（注意：根据题意，形如(x,x)的点是可行的）.显然，这样的结构对答案的贡献为n2.

对于每个可以成功染色的联通块，如果三种颜色均包含在内，那么根据题意，该联通块中每一对r -> g， g -> b，b -> r均可以连出一条有向边（暨染成黑色）.若约定用n(r)表示该种颜色的节点在联通块中的数量，这样的结构对答案的贡献可以表示为n(r)∗n(g)+n(g)∗n(b)+n(b)∗n(r).

对于每个可以成功染色的联通块，如果仅有两种或更少的颜色包含在内，那么显然我们无法染出更多的黑块.则这样的结构对答案没有额外贡献.

根据如上三条规律，我们不难写出如下程序。不过具体地，一个小小的细节是由于答案可能过大，我们需要用longlong型变量对答案进行储存。并且，我们要时刻注意int乘法中可能存在的溢出问题，解决方案很简单，在每一个int乘法运算前加上(longlong)即可。

# AC代码！

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;
inline int read(){
    int re = 0,ch = getchar();
    while(!isdigit(ch))ch = getchar();
    while(isdigit(ch))re = (re<<1)+(re<<3)+ch-'0',ch = getchar();
    return re;
}
const int maxn = 200010;
struct edge{
    int v,w,nxt;
}e[maxn];
int h[maxn],cnt;
inline void add(int u,int v,int w){
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = h[u];
    h[u] = cnt;
}
inline int color(int c){
    if(c >= 3)c -= 3;
    if(c < 0)c += 3;
    return c;
}
int col[maxn],cnum[3],nsz,esz;
bool flag = 1,vis[maxn];
void coloring(int u){
    cnum[col[u]]++;nsz++;vis[u] = 1;
    for(int i = h[u];i;i = e[i].nxt){
        int v = e[i].v;
        if(e[i].w == 1)esz++;
        if(!vis[v]) col[v] = color(col[u] + e[i].w),coloring(v);
        else if(col[v] != color(col[u] + e[i].w)) flag = 0;
    }
}
int n,m;
long long ans;
int main(){
    n = read(),m = read();
    int u,v;
    for(int i = 1;i <= m;i++){
        u = read(),v = read();
        add(u,v,1);
        add(v,u,-1);
    }
    for(int i = 1;i <= n;i++){
        if(vis[i])continue;
        memset(cnum,0,sizeof(cnum));
        nsz = 0,esz = 0,flag = 1;
        coloring(i);
        if(!flag) ans += (long long)nsz * nsz;
        else if(cnum[0] && cnum[1] && cnum[2]) 
            ans += (long long)cnum[0] * cnum[1]
             + (long long)cnum[1] * cnum[2] + (long long)cnum[2] * cnum[0];
        else ans += esz;
    }
    printf("%lld",ans);
    return 0;
} 
```
谢谢观看！

---

