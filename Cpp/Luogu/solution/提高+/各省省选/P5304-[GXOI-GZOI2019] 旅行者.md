# [GXOI/GZOI2019] 旅行者

## 题目描述

J 国有 $n$ 座城市，这些城市之间通过 $m$ 条单向道路相连，已知每条道路的长度。

一次，居住在 J 国的 Rainbow 邀请 Vani 来作客。不过，作为一名资深的旅行者，Vani 只对 J 国的 $k$ 座历史悠久、自然风景独特的城市感兴趣。  
为了提升旅行的体验，Vani 想要知道他感兴趣的城市之间「两两最短路」的最小值（即在他感兴趣的城市中，最近的一对的最短距离）。

也许下面的剧情你已经猜到了—— Vani 这几天还要忙着去其他地方游山玩水，就请你帮他解决这个问题吧。

## 说明/提示

### 样例解释
对于第一组数据，$1$ 到 $3$ 最短路为 $5$；$1$ 到 $6$ 最短路为 $7$；$3,6$ 无法到达，所以最近的两点为 $1,3$，最近的距离为 $5$。

对于第二组数据，$1$ 到 $2$ 最短路为 $6$；$5$ 到 $3$ 最短路为 $6$；其余的点均无法互相达，所以最近的两点为 $1,2$ 和 $5,3$，最近的距离为 $6$。

### 数据范围

$2 \le k \le n$，$1 \le x,y \le n$，$1 \le z \le 2 \times 10^9$，$T \leq 5$。

|测试点编号|$n$ 的规模|$m$ 的规模|约定|
|:-:|:-:|:-:|:-:|
|$1$|$\le 1,000$|$\le 5,000$|无|
|$2$|$\le 1,000$|$\le 5,000$|无|
|$3$|$\le 100,000$|$\le 500,000$|保证数据为有向无环图|
|$4$|$\le 100,000$|$\le 500,000$|保证数据为有向无环图|
|$5$|$\le 100,000$|$\le 500,000$|保证数据为有向无环图|
|$6$|$\le 100,000$|$\le 500,000$|无|
|$7$|$\le 100,000$|$\le 500,000$|无|
|$8$|$\le 100,000$|$\le 500,000$|无|
|$9$|$\le 100,000$|$\le 500,000$|无|
|$10$|$\le 100,000$|$\le 500,000$|无|

2024-12-18 管理员注：[在测试点五中可能存在自环](https://www.luogu.com.cn/discuss/1022672)。

## 样例 #1

### 输入

```
2
6 7 3
1 5 3
2 3 5
1 4 3
5 3 2
4 6 5
4 3 7
5 6 4
1 3 6
7 7 4
5 3 10
6 2 7
1 2 6
5 4 2
4 3 4
1 7 3
7 2 4
1 2 5 3```

### 输出

```
5
6
```

# 题解

## 作者：xht (赞：115)

题目地址：[P5304 [GXOI/GZOI2019]旅行者](https://www.luogu.org/problemnew/show/P5304)

这里是官方题解

> 一个图 $n$ 点 $m$ 条边，里面有 $k$ 个特殊点，问这 $k$ 个点之间两两最短路的最小值是多少？
> $n \leq 10^5, m \leq 5 * 10 ^5$

假设我们把特殊点分成 $A,B$ 两个集合，新建 $s$ 连 $A$ 集合的所有点，边权 $0$ ，新建 $t$ 连接 $B$ 集合里的所有点，边权 $0$ ，那么 $s$ 到 $t$ 的最短路就是 $A,B$ 集合点之间的最短路的最小值。

那么对于 $k$ 个特殊点，我们枚举二进制里的第 $i$ 位，把二进制第 $i$ 位是 $0$ 的点放在 $A$ ， $1$ 的点放在 $B$ ，用以上方法跑一个最短路。

然后跑 $log\ n$ 次最短路之后，所有最短路的最小值就是最终答案。

原理是，假设 $k$ 个特殊点里最近的是 $x$ 和 $y$ ，那么 $x$ 和 $y$ 一定有一个二进制位不一样，那么他们肯定在那次分组的时候被放进了不同的集合，从而肯定被算进了最后的答案之中最短路。
```cpp
#include <bits/stdc++.h>

const int MAXN = 100010, MAXM = 700010;

struct Edge {
	int y, z;
	Edge *next;
}*a[MAXN], POOL[MAXM], *ptr, *back[MAXN];

void AddEdge(int x, int y, int z) {
	Edge *tmp = ptr++;
	tmp->y = y;
	tmp->z = z;
	tmp->next = a[x];
	a[x] = tmp;
}

int n, nodes[MAXN], k, s, t;
long long dis[MAXN];

long long dijkstra() {
	memset(dis, 0x3f, sizeof(dis));
	dis[s] = 0;
	std::priority_queue<std::pair<long long, int> > Q;
	Q.push(std::make_pair(0, s));
	for (int i = 1; i < n + 2; i++) {
		while (!Q.empty() && dis[Q.top().second] != -Q.top().first) Q.pop();
		if (Q.empty()) break;
		int now = Q.top().second;
		Q.pop();
		for (Edge *p = a[now]; p; p = p->next)
			if (dis[p->y] > dis[now] + p->z)
				Q.push(std::make_pair(-(dis[p->y] = dis[now] + p->z), p->y));
	}
	return dis[t];
}

int main(int argc, char* argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		ptr = POOL;
		memset(a, 0, sizeof a);
		int m;
		scanf("%d%d%d", &n, &m, &k);
		while (m--) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			AddEdge(x, y, z);
		}
		for (int i = 1; i <= k; i++) scanf("%d", nodes + i);

		long long Ans = ~0ull>>1;
		s = n + 1, t = n + 2;
		for (int i = 0; (1 << i) <= k; i++) {
			Edge *backup = ptr;
			memcpy(back, a, (sizeof a[0]) * (n + 3));
			for (int j = 1; j <= k; j++) if (j & (1 << i)) {
					AddEdge(s, nodes[j], 0);
				} else {
					AddEdge(nodes[j], t, 0);
				}
			Ans = std::min(Ans, dijkstra());
			ptr = backup;
			memcpy(a, back, (sizeof a[0]) * (n + 3));
			for (int j = 1; j <= k; j++) if (j & (1 << i)) {
					AddEdge(nodes[j], t, 0);
				} else {
					AddEdge(s, nodes[j], 0);
				}
			Ans = std::min(Ans, dijkstra());
			ptr = backup;
			memcpy(a, back, (sizeof a[0]) * (n + 3));
		}
		printf("%lld\n", Ans);
	}
	return 0;
}
```

---

## 作者：人殇物已非 (赞：77)

## 暴力碾标算，$n^2$过百万！

本毒瘤又一次深刻讨论了一下，当我们在考场上真的不知道正解怎么打时，**如何拿暴力得到尽可能多的分数。**~~**（AC）**~~~~**（最优解第一个）**~~

由于是暴力，所以，根本没有任何的奇异算法在里面。

什么两遍$dijkstra$染色......这是什么，我怎么完全不知道，你们怎么什么都会啊$orz$。
### 朴素：
我们可以在读完题就马上得出我们的最朴素的暴力，对于$k$个感兴趣的点，每个点都跑一遍$dijkstra$求最短路，再$n^2$枚举找到最近的点对即为答案。**复杂度$O(T*n^2logn)$，期望得分$20pts$。**

### 优化：

但是我们在稍稍思考之后就会发现，这样好蠢呀！题目要求的是两两点对之间最短的那一对，**那么我们找到每个 **“感兴趣”的点** 离自己最近的不就可以了**，干嘛要管那些虽然也 **“感兴趣”**，但是离自己很远的点。

#### 所以，得到我们对暴力的优化，对每个点只松弛到**找到另一个也“感兴趣”的点**。

之后直接$return$，再往下的松弛操作不可能比当前答案更优秀。

而这里我们正好善用了$dijkstra$的优美的性质，$dijkstra$算法的堆优化每次取的是堆顶元素，这个元素的$dis[u]$是当前队列里最小的，所以$dis[u]$小的点一定会先被拿出来用而先出队，并且只会进队一次。

所以一旦**第一个**也感兴趣的点出队，那个点的$dis[u]$已经确定，并且是所有感兴趣的点中，离当前起点**最近**的。

### 复杂度分析：

#### 那么这个复杂度是多少呢？玄学。

这个复杂度我们可以很清晰的看到，在每遍$dijkstra$的复杂度是$Ω(1)$的，即为最优情况下找到第一个点就可以$return$。**~~（脸要有多白）~~** 此时每次的**运算复杂度居然小于了读入复杂度.....** 所以总复杂度是$Ω(T*m)$，$m$是因为读入......

而每遍$dijkstra$的最坏复杂度又是是$O(nlogn)$的，那么**理论上的最坏情况下**，复杂度是和暴力一样的，$O(T*n^2logn)$，但是我们考虑到以下一些**数据的局限性：**

- 每遍访问到第 $n-k$ 个点的时候，即：把所有的不感兴趣的点都访问过了。此时一定能找到一个感兴趣的点。而这种情况才是真的**最坏情况**。

- 假如我们构建出对于一个点，按照上面的情况让它需要把所有的不感兴趣的点都访问一遍，那么对于当前点确实是一个 $(n-k)*log(n-k)$的复杂度。但是我们会发现对于其他的点去再跑$dijkstra$的时候**很难**再跑到这个最坏复杂度。

所以实际理论最坏复杂度是$O(T*(n-k)*log(n-k)*k)$的，当由基本不等式：$n-k==k$ 时取到最大值为$O(T*n^2/4*log(n/2))$，此时确实是过不了的了。

—————————————————————————————————————

但是这个数据确实很难构造，出题人就算构造也不可能造10组。于是我们期望得分$80pts$+.

而实际上$AC$而且跑的飞快，把 $cin$ 换成快读之后就直接成了最优解第一个，而且比第二名还快了近1倍。。。。

#### （如果是省选原数据的话，大佬们放过我吧不要来$hack$了）

贴一个没有快读的
### $code:$
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+9,maxm=5e5+9;
struct edge{
    int to,next,w;
}e[maxm];
int cnt,last[maxn];
inline void add(int u,int v,int w){
    cnt++;
    e[cnt].to=v;
    e[cnt].next=last[u];
    last[u]=cnt;
    e[cnt].w=w;
}
long long dis[maxn];
struct node{
    int u;long long d;
    bool operator < (const node &rhs) const{
        return d>rhs.d;
    }
};
priority_queue<node> q;
bitset<maxn> vis,fl;
int n,m,k;
long long dij(int st){
    while(!q.empty()) q.pop();
    vis.reset();
    memset(dis,0x3f,sizeof(dis));
    q.push((node){st,0});dis[st]=0;
    while(!q.empty()){
        node fi=q.top();q.pop();
        int u=fi.u;if(fl[u]&&u!=st) return dis[u];
        if(!vis[u]){
            vis[u]=1;
            for(int i=last[u];i;i=e[i].next){
                int v=e[i].to,w=e[i].w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    q.push((node){v,dis[v]});
                }
            }
        }
    }
    return 0x3f3f3f3f3f3f3f3f;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        cnt=0;memset(last,0,sizeof(last));
        fl.reset();
        cin>>n>>m>>k;
        for(int i=1,u,v,w;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);add(u,v,w);
        }
        for(int i=1,u;i<=k;i++){scanf("%d",&u);fl[u]=1;}
        long long ans=0x3f3f3f3f3f3f3f3f;
        for(int i=1;i<=n;i++){
            if(fl[i]) ans=min(dij(i),ans);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

和我同机房的小伙伴根据这个思路比我先打了代码，犯了无数$ZZ$错误并且依然$AC$了。

### 他居然，多组数据 不！清 ！空 ！

研究了一下他的代码之后发现，他数组比数据范围多开大了好几倍，所以并没有发生什么具体的$RE$和$WA$错误....

#### 由此我们提出第二个口号！！

## 数组开的大，不清也不怕！！

---

## 作者：s_r_f (赞：71)

~~我也很好奇大家的复杂度为什么多了一个$log$。。。~~

一句话题意:有向图$G$中$|V| = n$,$|E| = m$,给定一个特殊点点集$S,|S| = k(p_1,p_2, ...,p_k)$

求$min(dis(p_i,p_j)) (i ≠ j)$.

首先有一个很暴力的$O(Tnlognlogk)$的方法~~这也就是出题人开$5000ms$的原因~~:

$i ≠ j$ 当且仅当$i$和$j$至少有一位二进制位不同。

枚举不同的二进制位,每次把$k$个点分成$S_0,S_1$两个集合跑$Dijsktra$

求$log_2k$次最短路并取$min$.

然而这题确实有$O(Tnlogn)$的做法。

首先,我们求出$f[i],g[i]$为$i$到某个关键点/某个关键点到$i$的最短距离。 

写成式子就是

$f[i] = min(dis_{min}(i,p_j))$

$g[i] = min(dis_{min}(p_j,i))$

注意$dis_{min}(i,p_j)$和$dis_{min}(p_j,i)$并不是同一个东西,因为**这是一张有向图。**

同时我们求出$From[i],To[i]$表示$f[i],g[i]$中 $dis_{min}(i,p_j)$和$dis_{min}(p_j,i)$对应的$p_j$

即$f[i]$的最短路走到了拿里,$g[i]$的最短路是从哪里来的。

上述内容只要做两次$Dijsktra$,一次在$G$上，一次在$G$的反图上。

复杂度$O(nlogn)$

考虑枚举一条边$(u,v,w),$

如果$From[u] ≠ To[v],$那么就用$g[u] + f[v] + w$来更新答案。

再枚举点$u,$

如果$From[u] ≠ To[u],$那么就用$g[u] + f[u]$来更新答案。

做完了。

这样做为什么是对的呢？

引用一下某神犇的解释：

"不难证明，对于源点 $i$，由 $i$ 拓展的点 $j$ 以及与 $j$ 相邻且不由$i$ 拓展的点 $k$， 如果 $i$ 的最优路径从 $j$ 走到了 $k$，那么走到拓展 $k$ 的源点是最优的。因此这个做法是正确的。"

对于一条最短的路径$x -> y$,假设其路径上没有边$(u,v)$满足$From[u] ≠ x,To[v] ≠ y$ 

很显然的一点就是$f[v] <= dis_{min}(v,y)$且$g[u] <= dis_{min}(x,u)$

如果此时$From[v] ≠ To[u],$那么存在比$x->y$不劣的解被更新了，对$ans$没有影响。

如果$From[v]$和$To[u]$都$≠x,y$，那么如果它们相等，

令$z = From[v]$,说明$dis_{min}(z,v) + w + dis_{min}(u,x)$也可以更新$ans$,

且$dis_{min}(x,u) >= dis_{min}(z,u), dis_{min}(v,y) >= dis_{min}(v,z)$

如果存在$>1$个这样的点$z$,那么一定有路径$z_1->z_2$比$x ->y$不劣且被更新到，对$ans$没有影响。

如果只存在一个这样的$z$,就回到了上面一种情况，要么$x->y$只有一条边(显然不可能) ，要么就一定有$(u,v)$满足$From[v] ≠ To[u].$

再讨论$From[v] = To[u] = x/y$的情况。

由于路径长为正整数，所以如果$From[v] = To[u] = x/y$,

那么找到它在$x->y$中的前/后的任意一条边，一定有$From[v] ≠ To[u].$

证毕。

那么代码实现也就很简单了。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
inline LL read(){
    LL x = 0,f = 1; char c = getchar();
    while (c != EOF && !isdigit(c)) {if (c == '-') f = -1;c = getchar();}
    while (isdigit(c)) {x = x * 10 + c - '0';c = getchar();}
    return x * f;
}
inline void write(LL x){
    if (x < 0) putchar('-'),x = -x;
    if (x > 9) write(x/10); putchar(x%10+'0');
}
inline void writeln(LL x){ write(x),putchar('\n'); }

const int N = 100005,M = 500005;
int Fr[M<<2],To[M<<2],Ne[M<<2],Dis[M<<2],He1[N],He2[N],_k;
inline void add(int *He,int x,int y,int z){
	++_k,Fr[_k] = x,To[_k] = y,Dis[_k] = z,Ne[_k] = He[x],He[x] = _k;
}

int T,n,m,k,p[N];

const LL INF = 1ll<<60;

int f1[N],f2[N];
LL dis1[N],dis2[N];

struct Node{
	int x; LL d;
	Node (int xx = 0,LL dd = 0){ x = xx,d = dd; }
	inline bool operator < (Node x) const{ return d > x.d; }
}t;

priority_queue<Node>Heap;



void Dij_1(){ //dis1 : p[i] -> x
	int i;
	while (!Heap.empty()) Heap.pop();
	for (i = 1; i <= n; ++i) dis1[i] = INF,f1[i] = -1;
	for (i = 1; i <= k; ++i) dis1[p[i]] = 0,f1[p[i]] = p[i],Heap.push(Node(p[i],0));
	int p,x;
	while (!Heap.empty()){
		t = Heap.top(); Heap.pop();
		if (t.d == dis1[t.x])
		for (p = He1[t.x]; p ; p = Ne[p]) if (dis1[To[p]] > dis1[t.x] + Dis[p]){
			dis1[To[p]] = dis1[t.x] + Dis[p];
			f1[To[p]] = f1[t.x];
			Heap.push(Node(To[p],dis1[To[p]]));
		}
	}
}

void Dij_2(){ //dis2 : x -> p[i]
	int i;
	for (i = 1; i <= n; ++i) dis2[i] = INF,f2[i] = -1;
	for (i = 1; i <= k; ++i) dis2[p[i]] = 0,f2[p[i]] = p[i],Heap.push(Node(p[i],0));
	int p,x;
	while (!Heap.empty()){
		t = Heap.top(); Heap.pop();
		if (t.d == dis2[t.x])
		for (p = He2[t.x]; p ; p = Ne[p]) if (dis2[To[p]] > dis2[t.x] + Dis[p]){
			dis2[To[p]] = dis2[t.x] + Dis[p];
			f2[To[p]] = f2[t.x];
			Heap.push(Node(To[p],dis2[To[p]]));
		}
	}
}

LL ans;
int main(){
	int i,u,v,w;
	T = read();
	while (T--){
		_k = 0;
		memset(He1,0,sizeof(He1));
		memset(He2,0,sizeof(He2));
		
		n = read(),m = read(),k = read();
		while (m--){ u = read(),v = read(),w = read(); if (u^v) add(He1,u,v,w),add(He2,v,u,w); }
		for (i = 1; i <= k; ++i) p[i] = read();
		Dij_1();
		Dij_2();
		ans = INF;
		for (i = 1; i <= n; ++i) if (f1[i] ^ f2[i]) ans = min(ans,dis1[i] + dis2[i]);
		for (i = 1; i <= _k; i += 2) if (f1[Fr[i]]^f2[To[i]])
			ans = min(ans,dis1[Fr[i]] + dis2[To[i]] + Dis[i]);
		writeln(ans);
	}
    return 0;
}
```

---

## 作者：Owen_codeisking (赞：45)

为什么出题人开了 $5000ms$？

正反跑两遍 $Dijkstra$ 染个色取个 $min$ 就好了啊。

时间复杂度：$O(Tn\log n)$

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100000+10;
const int maxm=500000+10;
const ll inf=0x3f3f3f3f3f3f3f3f;	
int n,m,k,a[maxn],X[maxm],Y[maxm],W[maxm],col[2][maxn],head[maxn],tot;
ll dis[2][maxn],ans;bool vis[maxn],iscity[maxn];

struct Edge
{
	int to,next,val;
}e[maxm];

struct node
{
	ll dis;int id;
	node(ll _dis=0,int _id=0):dis(_dis),id(_id){}
};
inline bool operator < (const node &a,const node &b)
{
	return a.dis>b.dis;
}

inline int read()
{
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

inline void addedge(int x,int y,int w)
{
	e[++tot].to=y;
	e[tot].val=w;
	e[tot].next=head[x];
	head[x]=tot;
}

inline void Dijkstra(ll *dis,int *col)
{
	for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
	priority_queue<node> pq;
	for(int i=1;i<=k;i++) dis[a[i]]=0,col[a[i]]=a[i],pq.push(node(0,a[i]));
	while(!pq.empty())
	{
		int u=pq.top().id;pq.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].val)
			{
				dis[v]=dis[u]+e[i].val;
				col[v]=col[u];
				pq.push(node(dis[v],v));
			}
		}
	}
}

inline void solve()
{
	n=read(),m=read(),k=read();
	int x,y,w;
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),w=read();
		if(x!=y) addedge(x,y,w);
		X[i]=x;Y[i]=y;W[i]=w;
	}
	for(int i=1;i<=k;i++) a[i]=read(),iscity[a[i]]=1;
	Dijkstra(dis[0],col[0]);
	for(int i=1;i<=n;i++) head[i]=0;
	tot=0;
	for(int i=1;i<=m;i++)
		if(X[i]!=Y[i]) addedge(Y[i],X[i],W[i]);
	Dijkstra(dis[1],col[1]);
	ans=inf;
	for(int i=1;i<=m;i++)
	{
		x=X[i];y=Y[i];w=W[i];
		if(col[0][x]&&col[1][y]&&col[0][x]!=col[1][y]) ans=min(ans,dis[0][x]+dis[1][y]+w);
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++) head[i]=iscity[i]=0;
	tot=0;
}

int main()
{
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：VenusM1nT (赞：15)

Dijkstra。

这道题目简直是弟弟级别的……

考虑每条边 $(u,v,w)$ 的贡献，我们可以处理出城市中离 $u$ 最近的距离为 $dis_1$，离 $v$ 最近的距离为 $dis_2$，那么这条边的权值就是 $dis_1+dis_2+w$，然后找到最短的一条就行了。

同时，我们还要记录这个城市的编号，如果两个城市相同，那么相当于走了一个环回到其本身了，不能计入答案。

正反跑两边 Dijkstra，分别染色。染色也就是在跑 Dijkstra 的过程中记录离这个点最近的城市，具体可以见代码。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 500005
#define reg register
#define inl inline
#define ll long long
using namespace std;
int cnt,fst[MAXN],to[MAXM],nxt[MAXM],w[MAXM];
int n,m,k,col[2][MAXN],a[MAXN],fr[MAXM],tx[MAXM],ww[MAXM];
ll dis[2][MAXM];
struct Node
{
	int u;
	ll dis;
	bool operator < (const Node &x) const
	{
		return x.dis<dis;
	}
};
priority_queue <Node> q;
template <typename T> inl void Read(reg T &x)
{
	x=0;
	reg int fu=1;
	reg char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
	x*=fu;
}
inl void AddEdge(reg int u,reg int v,reg int c)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
	w[cnt]=c;
}
inl void Dijkstra(reg int id)
{
	memset(dis[id],60,sizeof(dis[id]));
	memset(col[id],0,sizeof(col[id]));
	for(reg int i=1;i<=k;i++)
	{
		dis[id][a[i]]=0;
		col[id][a[i]]=a[i];
		q.push((Node){a[i],0});
	}
	while(!q.empty())
	{
		reg Node now=q.top();
		q.pop();
		reg int u=now.u;
		reg ll d=now.dis;
		if(d!=dis[id][u]) continue;
		for(reg int i=fst[u];i;i=nxt[i])
		{
			reg int v=to[i];
			if(dis[id][v]>dis[id][u]+w[i])
			{
				dis[id][v]=dis[id][u]+w[i];
				col[id][v]=col[id][u];
				q.push((Node){v,dis[id][v]});
			}
		}
	}
}
int main()
{
	int Time;
	Read(Time);
	while(Time--)
	{
		cnt=0;
		memset(fst,0,sizeof(fst));
		Read(n);
		Read(m);
		Read(k);
		for(reg int i=1;i<=m;i++)
		{
			int x,y,z;
			Read(x);
			Read(y);
			Read(z);
			fr[i]=x;
			tx[i]=y;
			ww[i]=z;
			if(x^y) AddEdge(x,y,z);
		}
		for(reg int i=1;i<=k;i++) Read(a[i]);
		Dijkstra(0);
		cnt=0;
		memset(fst,0,sizeof(fst));
		for(reg int i=1;i<=m;i++) if(fr[i]^tx[i]) AddEdge(tx[i],fr[i],ww[i]);
		Dijkstra(1);
		reg ll ans=1e18;
		for(reg int i=1;i<=m;i++)
		{
			reg int u=fr[i],v=tx[i],c=ww[i];
			if(col[0][u] && col[1][v] && col[0][u]!=col[1][v]) ans=min(ans,dis[0][u]+dis[1][v]+c);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：徐致远 (赞：14)

[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/06/03/%E3%80%8CGXOI%20GZOI2019%E3%80%8D%E6%97%85%E8%A1%8C%E8%80%85-Solution/)

### 题解

对于这题，一开始能比较容易地想到一个乱搞的做法：

将$k$个关键点随机分成两半，建立超级源点向其中一半的所有点建边权为$0$的边，再从另一半向超级汇点建边权为$0$的边。

然后用Dijkstra求出源点到汇点的最短路，取每次求解出最短路的最小值为答案。

这样一次求出最优解的概率为$\frac{1}{4}$。

但是如果我们重复以上操作20次，那么求出最优解的概率为$1-(\frac{3}{4})^{20}\approx99.7\%$。

这样AC的概率其实已近非常高了，如果能优化常数然后增大重复次数，那么AC的概率还可以进一步提高。

其实如果想到了上面乱搞的做法，离正解也很近了。

我们可以根据关键点编号在二进制中第$i$位上的数字来对这$k$个关键点进行分组，为$0$的分在一组，为$1$的分在另一组。然后按照上面的方式建图求最短路。

假设最优解中的起点为$u$，终点为$v$，那么它们编号在二进制中至少有一位不同，所以它们必定会在某一次分组中被分在了不同的组，从而求解出了答案。

时间复杂度$O(nlog^2n )$。

注意由于图是有向的，所以每枚举到二进制中的一位时应进行两次分组。

### 代码

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn=100005,maxm=500005;const LL inf=0x3F3F3F3F3F3F3F3FLL;
int T,n,m,k,V[maxn];LL ans,dist[maxn];
inline char nc()
{
	static const int S=131072;static char buf[S],*L,*R;
	return L==R&&(R=(L=buf)+fread(buf,1,S,stdin),L==R)?EOF:*L++;
}
inline int read()
{
	int ret=0,f=1;char ch=nc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=nc();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=nc();}
	return ret*f;
}
struct Graph
{
	int tot,lnk[maxn],son[maxm],nxt[maxm],w[maxm];
	inline void Clear(){tot=0;memset(lnk,0,sizeof(lnk));}
	inline void add_e(int x,int y,int z){tot++;son[tot]=y;w[tot]=z;nxt[tot]=lnk[x];lnk[x]=tot;}
}G1,G2;
struct Node
{
	int id;LL dis;
	bool operator < (const Node& b)const{return dis>b.dis;}
};
inline void Dijkstra()
{
	memset(dist,63,sizeof(dist));
	priority_queue<Node> que;
	que.push((Node){n+1,0});
	dist[n+1]=0;
	while(!que.empty())
	{
		Node QH=que.top();que.pop();
		if(QH.id==n+2&&QH.dis<ans) ans=QH.dis;
		if(QH.dis>dist[QH.id]) continue;
		dist[QH.id]=QH.dis;
		for(int i=G2.lnk[QH.id];i;i=G2.nxt[i])
			if(QH.dis+G2.w[i]<dist[G2.son[i]])
				que.push((Node){G2.son[i],QH.dis+G2.w[i]});
	}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();m=read();k=read();G1.Clear();G2.Clear();ans=inf;
		for(int i=1;i<=m;i++)
		{
			int a=read(),b=read(),c=read();
			G1.add_e(a,b,c);G2.add_e(a,b,c);
		}
		for(int i=1;i<=k;i++) V[i]=read();
		for(int i=0;(1<<i)<=n;i++)
		{
			G2.tot=G1.tot;
			memcpy(G2.lnk,G1.lnk,(n+3)*sizeof(int));
			for(int j=1;j<=k;j++)
			{
				if(V[j]&(1<<i)) G2.add_e(n+1,V[j],0);
				else G2.add_e(V[j],n+2,0);
			}
			Dijkstra();
			G2.tot=G1.tot;
			memcpy(G2.lnk,G1.lnk,(n+3)*sizeof(int));
			for(int j=1;j<=k;j++)
			{
				if(V[j]&(1<<i)) G2.add_e(V[j],n+2,0);
				else G2.add_e(n+1,V[j],0);
			}
			Dijkstra();
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：_louhc (赞：11)

## 思路

窝又来提供一种~~玄学~~神奇的做法 染色、倍增什么的都没有，，，  
思路十分简单，对于每个点x，记录两个dis，即离x最近的两个关键点的距离。
当然，这两个关键点不能一样，所以也要顺便记录一下是从哪个关键点走过来的。
然后把所有关键点push进优先队列，上一个Dijkstra模板来求出最小的两条路径就OK了。
最后对所有关键点的第二近的距离求min输出，就可以了。

上面可能说的不是很清楚，看代码把qwq

## 代码

```cpp
#include<bits/stdc++.h>
#define u32 unsigned
#define i64 long long
#define u64 unsigned long long
#define f80 long double
#define rgt register
#define getchar() ( p1 == p2 && ( p2 = bf + fread( bf, 1, 1 << 21, stdin ), p1 = bf ) == p2 ? EOF : *p1++ )
using namespace std;
#define MAXN 100005
#define MAXM 500005

char bf[1 << 21], *p1, *p2;
template<typename T>
inline void read( rgt T &x ){ x = 0; rgt char t, flg(0);
	for ( t = getchar(); !isdigit(t); t = getchar() ) flg = t == '-';
	for ( ; isdigit(t); t = getchar() ) x = x * 10 + ( t & 15 ); x = flg ? -x : x;
}

clock_t __t_bg, __t_ed;
struct node{
	i64 v; int w; node(){} node( i64 x, int y ):v(x), w(y){}
	bool operator < ( const node &t )const{ return v > t.v; }
};
#define pi pair<node, int>
int N, M, K, T, itr[MAXN]; node dis[MAXN][2]; char vis[MAXN];
int hd[MAXN], nxt[MAXM], to[MAXM], val[MAXM], tot;
inline void add( int x, int y, int z ){ nxt[++tot] = hd[x], hd[x] = tot, to[tot] = y, val[tot] = z; }

priority_queue<pi> Q;

signed main(){
	__t_bg = clock();
	read(T);
	while( T-- ){
		read(N), read(M), read(K), memset( hd, 0, sizeof hd ), tot = 0;
		for ( rgt int i = 1, x, y, z; i <= M; ++i )
			read(x), read(y), read(z), add(x,y,z);
		memset( dis, 0x7f, sizeof dis ), memset( vis, 0, sizeof vis );
		for ( rgt int i = 1; i <= K; ++i ) read(itr[i]), Q.push(make_pair(dis[itr[i]][0] = node(0, itr[i]), itr[i]));//所有关键点入队列
		while( !Q.empty() ){
			rgt int u(Q.top().second), w(Q.top().first.w);//u表示当前到哪个点，w表示从哪个关键点过来，t表示当前走的长度
			rgt i64 t(Q.top().first.v); Q.pop();
			if ( vis[u] >= 2 ) continue;
			++vis[u];
			for ( rgt int i = hd[u], v; i; i = nxt[i] ){
				v = to[i];
				if ( w != dis[v][0].w ){//注意判断一些情况
					if ( dis[v][0].v > t + val[i] ) dis[v][1] = dis[v][0], dis[v][0] = node( t + val[i], w ), Q.push(make_pair(dis[v][0], v));
					else if ( dis[v][1].v > t + val[i] ) dis[v][1] = node( t + val[i], w ), Q.push(make_pair(dis[v][1], v));
				} else if ( dis[v][0].v > t + val[i] ) dis[v][0].v = t + val[i], Q.push(make_pair(dis[v][0], v));
			}
		} rgt i64 ans(LONG_LONG_MAX);
		for ( rgt int i = 1; i <= K; ++i ) ans = min( ans, dis[itr[i]][1].v );
		printf( "%lld\n", ans );
	}
	__t_ed = clock(), fprintf( stderr, "time: %.5lfs\n", double( __t_ed - __t_bg ) / CLOCKS_PER_SEC );
	return 0;
}
```

---

## 作者：MLEAutoMaton (赞：7)

## 传送门
[Loj](https://loj.ac/problem/3087)

## Solution
考虑两个关键点对之间一定不会经过另一个关键点,那么就跑两边$dijkstra$然后枚举边就行了.
具体实现见代码.

## 代码实现
```cpp
/*
  mail: mleautomaton@foxmail.com
  author: MLEAutoMaton
  This Code is made by MLEAutoMaton
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define ll long long
#define re register
#define int ll
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi()
{
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=200010,M=1000010;
struct node
{
	int to,nxt,w,id;
}e[M];
struct edge{int u,v,w;}ed[M<<1];
int front[N],cnt=1,a[N],bl[N][2],n,m,k,vis[N];
ll dis[N][2];
void Add(int u,int v,int w){e[++cnt]=(node){v,front[u],w,0};front[u]=cnt;e[++cnt]=(node){u,front[v],w,1};front[v]=cnt;}
typedef pair<ll,int> pii;
priority_queue<pii,vector<pii>,greater<pii> >q;
#define mp make_pair
void solve()
{
	ll ans=1e18+10;
	for(int i=1;i<=n;i++)dis[i][0]=1e18,vis[i]=0;
	for(int i=1;i<=k;i++)dis[a[i]][0]=0,bl[a[i]][0]=a[i],q.push(mp(0,a[i]));
	while(!q.empty())
	{
		pii now=q.top();q.pop();int u=now.second;
		if(vis[u])continue;vis[u]=1;
		for(int i=front[u];i;i=e[i].nxt)
		{
			if(e[i].id)continue;
			int v=e[i].to;
			if(dis[v][0]>dis[u][0]+e[i].w)
			{
				dis[v][0]=dis[u][0]+e[i].w;
				q.push(mp(dis[v][0],v));
				bl[v][0]=bl[u][0];
			}
		}
	}
	for(int i=1;i<=n;i++)dis[i][1]=1e18,vis[i]=0;
	for(int i=1;i<=k;i++)dis[a[i]][1]=0,bl[a[i]][1]=a[i],q.push(mp(0,a[i]));
	while(!q.empty())
	{
		pii now=q.top();q.pop();int u=now.second;
		if(vis[u])continue;vis[u]=1;
		for(int i=front[u];i;i=e[i].nxt)
		{
			if(!e[i].id)continue;
			int v=e[i].to;
			if(dis[v][1]>dis[u][1]+e[i].w)
			{
				dis[v][1]=dis[u][1]+e[i].w;
				q.push(mp(dis[v][1],v));
				bl[v][1]=bl[u][1];
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		int u=ed[i].u,v=ed[i].v;
		if(bl[u][0]==bl[v][1])continue;
		ans=min(ans,ed[i].w+dis[u][0]+dis[v][1]);
	}
	printf("%lld\n",ans);
}
signed main()
{
	freopen("tourist.in","r",stdin);
	freopen("tourist.out","w",stdout);
	int T=gi();
	while(T--)
	{
		n=gi();m=gi();k=gi();
		for(int i=1;i<=m;i++){int x=gi(),y=gi(),z=gi();Add(x,y,z);ed[i]=(edge){x,y,z};}
		for(int i=1;i<=k;i++)a[i]=gi();
		solve();
		for(int i=1;i<=n;i++)front[i]=0;cnt=1;
	}
	return 0;
}
```

---

## 作者：TopCarry (赞：6)

#### 这里提供一种 分治/倍增 的解法。
&emsp;&emsp;首先我们可以想到一个$fake$的做法：直接建超级源汇然后跑最短路。这样只能拿到有向无环图的$30pts$，因为你没有办法处理“自己到自己”这种情况。

&emsp;&emsp;然后我们很容易搞出一个$O(N^2)$的算法，就是枚举每个点然后跑一遍$Dijkstra$就可以了。

&emsp;&emsp;我们考虑一下这个算法的瓶颈是什么？显然不是求最短路，而是枚举。
最后的答案肯定是点集中一个点$ansS$到$ansT$的最短路径，我们只要保证在枚举的时候，存在一个时刻，超级源点$S$连在$ansS$上并且$ansT$连在超级源点$T$上，而且这个枚举的复杂度可以接受就好了。

&emsp;&emsp;我们思考一下能否在枚举的时候每次“倍增（分治）”。

&emsp;&emsp;假设a数组为题目中给的点集，为了方便理解，我这里用线段树来解释，假设我们已经建好了a数组的线段树，第一次我们把a数组中，下标<=mid的都连到S，其余连到T：
![](https://cdn.luogu.com.cn/upload/pic/57247.png )

&emsp;&emsp;跑一边$Dijkstra$，然后把S和T反过来，S连右，T连左，再跑一遍$Dijkstra$。

&emsp;&emsp;那么凡是$ansS$在$a[1]-a[mid]/a[mid+1]-a[r]$中，且$ansT$在$a[mid+1]-a[r]/a[1]-a[mid]$的情况都被我们一次统计了，剩下的就是$ansT$和$ansS$都在同一个线段里的情况了，那么我们第二次这么做：
![](https://cdn.luogu.com.cn/upload/pic/57254.png)

&emsp;&emsp;这样分治下去，只要$logn$次枚举就可以统计出答案，每次$nlogn$那么总复杂度就是$O(Tnlog^2n)$的，在$O2$（反正省选也有）下最慢的点在$2s$左右。

&emsp;&emsp;为什么这么做不会漏掉答案呢？

&emsp;&emsp;一句话:任意两个叶子在线段树上都有唯一的$LCA$，那么他们一定会在我们“分别连”这个$LCA$左右儿子的时候被枚举到。

&emsp;&emsp;实际上这颗线段树根本不用建出来（似乎建出来连边可以优化到$O(n)$），直接暴力连边复杂度也是对的。代码实现的时候$BFS$分治并不好写，所以我写的是从叶子迭代上去，类似于倍增的方式(长得好像$FFT$...)。

&emsp;&emsp;最优解是$Dijkstra$染色($O(Tnlogn)$)，但是我保证并不是每个人都会这东西，标算好像是拆二进制枚举，感觉虽然会好写一些，但是脑洞真的很大，像我这种人考试的时候肯定想不到，而这个类似于线段树的思路是比较$native$的，很容易想到，所以才有了这一篇题解，希望对大家有所帮助。

## Code:
```cpp
#include<cstdio>
#include<cmath>
#include<queue>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
static char buf[100000],*pa,*pd;
#define gc pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++
inline int read(){
	register int x(0),f(1);register char c(gc);
	while(c>'9'||c<'0')f=c=='-'?-1:1,c=gc;
	while(c>='0'&&c<='9')x=x*10+c-48,c=gc;
	return f*x;
}
const int N=110000,M=510000;
struct edge{
	int to,next;
	ll w;
}e[M];
int head[150000],tot;
void add(int x,int y,ll z){
	e[++tot].next=head[x];e[tot].to=y;head[x]=tot;e[tot].w=z;
}
int t,n,m,K,a[N];
const int S=0,T=N-1;
ll dis[N],ans;
#define re(a) memset((a),0,sizeof((a)))
void clear(){
	re(a);re(head);tot=0;
}
struct node{
	int u;
	ll udis;
};
bool operator < (node x,node y){
	return x.udis>y.udis;
}
priority_queue<node> q;
ll DJ(){
	memset(dis,127,sizeof(dis));
	dis[S]=0;
	q.push((node){S,0});
	register int i;
	while(!q.empty()){
		int u=q.top().u;ll udis=q.top().udis;q.pop();
		if(udis!=dis[u])continue;
		for(i=head[u];i;i=e[i].next)
			if(dis[u]+e[i].w<dis[e[i].to]){
				dis[e[i].to]=dis[u]+e[i].w;
				q.push((node){e[i].to,dis[e[i].to]});
			}
	} 
	return dis[T];
}
int past[150000];
void work(){
	register int i,j,l,r,mid;
	ans=(ll)pow(2,63)-10;
	memcpy(past,head,sizeof(past));
	for(mid=1;mid<=K;mid<<=1){
		for(l=0,r=mid<<1;l<=K;l+=r){
			for(j=l+1;j<=l+mid;j++)if(j<=K)add(S,a[j],0);
			for(j=l+mid+1;j<=l+r;j++)if(j<=K)add(a[j],T,0);
		}
		ans=min(ans,DJ());
		tot-=K;
		memcpy(head,past,sizeof(head));
		for(l=0,r=mid<<1;l<=K;l+=r){
			for(j=l+1;j<=l+mid;j++)if(j<=K)add(a[j],T,0);
			for(j=l+mid+1;j<=l+r;j++)if(j<=K)add(S,a[j],0);
		}
		ans=min(ans,DJ());
		tot-=K;
		memcpy(head,past,sizeof(head));
	}
	cout<<ans<<'\n';
}
int main(){
	t=read();
	register int i,x,y,z;
	while(t--){
		n=read();m=read();K=read();
		for(i=1;i<=m;i++){
			x=read();y=read();z=read();add(x,y,z);
		}
		for(i=1;i<=K;i++){
			a[i]=read();
		}
		work();
		clear();
	}
	return 0;
}
```



---

## 作者：star_magic_young (赞：5)


~~所以这个$5s$是SMG~~

暴力是枚举每一个点跑最短路,然后有一个很~~拿衣服~~幼稚的想法,就是把所有给出的关键点当出发点,都丢到队列里,求最短路的时候如果当前点$x$某个相邻的点$y$是关键点,就用$dis_x+$边权$w_i$更新答案.感觉这个复杂度是正确的,然后跑一下样例也对

~~交上去就可以获得70'的好成绩~~

这个方法会有一种特殊情况无法处理,就是这条路径的起点和终点都是同一点,因为图中可能有环.那么我们更新答案就不能用起点是$y$的路径更新答案,于是考虑同时记录从某个出发点到一个点的最短路以及是从哪个出发点转移过来的,同时求次短路,要求最短路的起点和次短路起点不一样,那么在更新答案时,如果最短路起点不等于终点就用最短路更新,否则用次短路

```cpp
// luogu-judger-enable-o2
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<set>
#define LL long long
#define db double

using namespace std;
const int N=100000+10,M=500000+10;
int rd()
{
    int x=0,w=1;char ch=0;
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
int to[M],nt[M],hd[N],tot;
LL w[M];
void add(int x,int y,int z){++tot,to[tot]=y,nt[tot]=hd[x],w[tot]=z,hd[x]=tot;}
bool v[N];
struct nn
{
    LL d;
    int y;
    void clr(){d=1ll<<50,y=0;}
    bool operator < (const nn &bb) const {return d<bb.d;}
}d1[N],d2[N];
struct node
{
    int x;
    nn d1,d2;
    bool operator < (const node &bb) const {return bb.d1.d!=d1.d?bb.d1<d1:bb.d2<d2;}
};
priority_queue<node> q;
int n,m,kk;

int main()
{
    int T=rd();
    while(T--)
    {
        memset(hd,0,sizeof(hd)),tot=0;
        n=rd(),m=rd(),kk=rd();
        for(int i=1;i<=m;++i)
        {
            int x=rd(),y=rd(),z=rd();
            if(x==y) continue;
            add(x,y,z);
        }
        memset(v,0,sizeof(v));
        for(int i=1;i<=n;++i) d1[i].clr(),d2[i].clr();
        LL ans=1ll<<50;
        while(kk--)
        {
            int x=rd();
            d1[x]=(nn){0,x},v[x]=1,q.push((node){x,d1[x],d2[x]});
        }
        while(!q.empty())
        {
            int x=q.top().x;
            nn dd1=q.top().d1,dd2=q.top().d2;
            q.pop();
            if(d1[x]<dd1||d2[x]<dd2) continue;
            for(int i=hd[x];i;i=nt[i])
            {
                int y=to[i];
                if(v[y])
                {
                    if(dd1.y!=y) ans=min(ans,dd1.d+w[i]);
                    else ans=min(ans,dd2.d+w[i]);
                }
                else
                {
                    nn n1=d1[y],n2=d2[y];
                    if(n1.d>dd2.d+w[i])
                    {
                        if(n1.y!=n2.y) n2=n1;
                        n1=(nn){dd2.d+w[i],dd2.y};
                    }
                    else if(n2.d>dd2.d+w[i]&&n1.y!=dd2.y) n2=(nn){dd2.d+w[i],dd2.y};
                    if(n1.d>dd1.d+w[i])
                    {
                        if(n1.y!=n2.y) n2=n1;
                        n1=(nn){dd1.d+w[i],dd1.y};
                    }
                    else if(n2.d>dd1.d+w[i]&&n1.y!=dd1.y) n2=(nn){dd1.d+w[i],dd1.y};
                    if(n1<d1[y]||n2<d2[y]) q.push((node){y,d1[y]=n1,d2[y]=n2});
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Jμdge (赞：3)

这么**简单**的题，Venus 都讲不清楚，太强了！


# noteskey

两次多源最短路跑跑（正图一遍反图一遍）然后枚举边？

怎么 Venus 就一句话 AC 了呢

总之就是

>正图上从 k 个关键点出发跑 $dijkstra$  ，记某个点离最近的关键点距离为 $dis[0][i]$ 

>反图上也从 k 个关键点出发跑 $dijkstra$ ，距离记为 $dis[1][i]$ 

>枚举正图中的边 $u->v:  w $ ， 用 $dis[0][u]+dis[1][v]+w $更新答案


# watch out

精度问题...如果出事的话就查查有没有什么 long long 写成 int 吧




# code

```cpp
//by Judge
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define go(G,u) for(Rg int i=G.head[u],v=G.e[i].to;i;v=G.e[i=G.e[i].nxt].to)
#define P pair<ll,int>
#define ll long long
#define se second
#define fi first
using namespace std;
const int M=1e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmin(T& a,T b){return a>b?a=b,1:0;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,m,k,id[2][M],a[M]; ll dis[2][M]; priority_queue<P> q;
struct Gr{ int pat,head[M]; struct Edge{int to,val,nxt;}e[M*5];
	inline void clear(Rg int n){ pat=0,memset(head,0,(n+2)<<2); }
	inline void add(int u,int v,int w){ e[++pat]={v,w,head[u]},head[u]=pat; }
}G[2];
inline void dijkstra(int p){ memset(dis[p],60,(n+2)<<3),memset(id[p],0,(n+2)<<2);
	fp(i,1,k) dis[p][a[i]]=0,id[p][a[i]]=a[i],q.push(P(0,a[i]));
	while(!q.empty()){ Rg int u=q.top().se; Rg ll d=-q.top().fi; q.pop();
		if(d==dis[p][u]) go(G[p],u) if(cmin(dis[p][v],d+G[p].e[i].val))
			id[p][v]=id[p][u],q.push(P(-dis[p][v],v));
	}
}
int main(){
	fp(T,1,read()){ n=read(),m=read(),k=read();
		G[0].clear(n),G[1].clear(n); Rg int x,y,z;
		fp(i,1,m){ x=read(),y=read(),z=read();
			if(x^y) G[0].add(x,y,z),G[1].add(y,x,z);
		} fp(i,1,k) a[i]=read();
		dijkstra(0),dijkstra(1); ll ans=1e18;
		fp(u,1,n) go(G[0],u){ Rg int w=G[0].e[i].val;
			if(id[0][u]&&id[1][v]&&id[0][u]^id[1][v])
				cmin(ans,dis[0][u]+dis[1][v]+w);
		} printf("%lld\n",ans);
	} return 0;
}
```


---

## 作者：Alear (赞：2)

爆搜

参加同步测试时写的大暴力搜索，没想到居然在5s的时间里水过了，成了我唯一A的一道题（应该是整场考试最水的题了吧）

把所有感兴趣的城市都用结构体保存起来
```cpp
struct length{
	int d,u,from;
}len;
```
存的是每一条路径的长度，当前点，源点

直接丢到堆里面去，每次取出长度最短的路径，如果当前的点是感兴趣的城市，且起点不为当前点，这时搜到的距离就是答案。否则对每一个子节点进行拓展，直接丢到堆里面去。

贴代码，慢的一匹，最慢一个点跑了4s多，复杂度O（玄学）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100010
#define M 500010
int read(){
	int c,nx=0;
	do{
		c=getchar()-'0';
	}while(c<0 or c>9);
	nx=getchar()-'0';
	while(nx>=0 and nx<=9){
		c=c*10+nx;
		nx=getchar()-'0';
	}
	return c;
}
int a[N];
int now,head[N],next[M],ver[M],edge[M];
inline void addEdge(int u,int v,int e){
	now++;
	next[now]=head[u];
	ver[now]=v;
	head[u]=now;
	edge[now]=e;
}
struct length{
	int d,u,from;
}len;
bool operator<(length x,length y){
	return x.d>y.d;
}
int n,m,k;
int dist[N];
bool is[N];
priority_queue<length>q;
int main(){
	int u,v,e,d,from;
	int t=read();
	len.d=len.from=len.u=0;
	for(int h=1;h<=t;h++){
		now=0;
		len.d=len.from=len.u=0;
		memset(head,0,sizeof(head));
		memset(next,0,sizeof(next));
		memset(is,0,sizeof(is));
		while(q.size())
			q.pop();
		memset(dist,0x3f,sizeof(dist));
		n=read();
		m=read();
		k=read();
		for(int i=1;i<=m;i++){
			u=read();
			v=read();
			e=read();
			if(u!=v){
				addEdge(u,v,e);
			}
		}
		for(int i=1;i<=k;i++){
			len.u=len.from=a[i]=read();
			is[a[i]]=1;
			q.push(len);
		}
		while(q.size()){
			u=q.top().u;
			d=q.top().d;
			len.from=from=q.top().from;
			q.pop();
			if(is[u] and u!=from){
				printf("%d\n",d);
				break;
			}
			for(int i=head[u];i;i=next[i]){
				len.u=ver[i];
				len.d=d+edge[i];
				q.push(len);
			}
		}
		
	}
	
}
```


---

## 作者：hl666 (赞：2)

有趣的题目，又好想又好码，可谓是省选题中的一股清流

考虑如果我们枚举一个点作为起点，然后暴力求出到其它点的最短路，那么可以暴力解决问题

但是我们稍微转化一下问题，同时把**一些点的集合**作为起点，跑出到其它剩下所有点的最短路，取出其中最小的一条，就相当于同时做了多次猜测

具体实现也非常简单，直接建个超级起点$st$和终点$tar$，如果这个关键点$x$位于起点集合那么连一条$st\to x,val=0$的边，在终点集合就连一条$x\to tar,val=0$的边

最后$st\to tar$的最短路即为答案，看起来十分简单

但是我们细细一想发现这个方法好像很优秀，如果最后答案是$x\to y$，那么如果$x$被分到起点集合里而$y$被分到终点集合里那么这个算法就直接跑出了答案！

根据上面的分析我们很容易得到一个**随机化**的做法，我们每次给所有关键点随机分配到两边然后跑最短路，这样正确率就是$\frac{1}{4}$

由于跑一次的复杂度是$O(n\log n)$（用DJ），因此5s的时限我们稳妥的跑$20$次左右，这样错误的概率就是：

$$(\frac{1}{4})^{20}\approx 0.0031712\approx\frac{1}{315}$$

足以通过此题，而且最大点在Luogu上仅用时2100+ms，因此跑更大的$30,40$次都不成问题（如果比赛的时候还是求稳为主，后面全T了就很尴尬）

随机化CODE

```cpp
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<queue>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
const int N=1e5+5,M=5e6+5;
const long long INF=1e18;
struct edge
{
    int to,nxt,v;
}e[N+M]; int n,t,thead[N],head[N],a[N],cnt,tcnt,m,k,x,y,z,st,tar; long long dis[N];
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        char Fin[S],*A,*B;
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        #undef tc
}F;
class SSSP
{
    private:
        struct data
        {
            int id; long long val;
            friend inline bool operator < (const data& A,const data& B)
            {
                return A.val>B.val;
            }
        }; priority_queue <data> hp; bool vis[N];
    public:
        #define to e[i].to
        inline void Dijkstra(void)
        {
            RI i; for (i=st;i<=tar;++i) dis[i]=INF,vis[i]=0; dis[st]=0;
            hp.push((data){st,0}); while (!hp.empty())
            {
                int now=hp.top().id; hp.pop(); if (vis[now]) continue;
                vis[now]=1; for (i=head[now];i;i=e[i].nxt)
                if (dis[to]>dis[now]+e[i].v) hp.push((data){to,dis[to]=dis[now]+e[i].v});
            }
        }
        #undef to
}G;
inline void taddedge(CI x,CI y,CI z)
{
    e[++tcnt]=(edge){y,thead[x],z}; thead[x]=tcnt;
}
inline void addedge(CI x,CI y,CI z)
{
    e[++cnt]=(edge){y,head[x],z}; head[x]=cnt;
}
inline long long solve(long long ret=INF)
{
    RI i,j; for (F.read(n),F.read(m),F.read(k),i=1;i<=m;++i)
    F.read(x),F.read(y),F.read(z),taddedge(x,y,z);
    for (tar=n+1,i=1;i<=k;++i) F.read(a[i]);
    for (i=1;i<=20;++i)
    {
        for (cnt=tcnt,j=st;j<=tar;++j) head[j]=thead[j];
        for (j=1;j<=k;++j) if (rand()&1) addedge(st,a[j],0);
        else addedge(a[j],tar,0); if (G.Dijkstra(),dis[tar]<ret) ret=dis[tar];
    }
    return ret;
}
inline void clear(void)
{
    for (RI i=st;i<=tar;++i) thead[i]=0; tcnt=0;
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    for (srand(20030909),F.read(t);t;--t) printf("%lld\n",solve()),clear(); return 0;
}
```

------

好吧接下来讲一下正确做法，大致建模和上面一样，就是分配点集的时候稍作修改，枚举$n$范围内的每一个二进制位，如果这个点编号这一位上为$1$就放在起点一边，反之

正确性证明也很好理解，假设答案为$x\to y$，那么$x\ne y$，因此$x,y$必然有至少一位在二进制下不同，故至少有一次被分在了两侧，结论成立

这样就可以以$O(n\log^2 n)$的复杂度通过此题了，注意答案为有向点对，因此要枚举两边

二进制分组CODE

```cpp
#include<cstdio>
#include<cctype>
#include<queue>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
const int N=1e5+5,M=5e6+5;
const long long INF=1e18;
struct edge
{
    int to,nxt,v;
}e[N+M]; int n,t,thead[N],head[N],a[N],cnt,tcnt,m,k,x,y,z,st,tar; long long dis[N];
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        char Fin[S],*A,*B;
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        #undef tc
}F;
class SSSP
{
    private:
        struct data
        {
            int id; long long val;
            friend inline bool operator < (const data& A,const data& B)
            {
                return A.val>B.val;
            }
        }; priority_queue <data> hp; bool vis[N];
    public:
        #define to e[i].to
        inline void Dijkstra(void)
        {
            RI i; for (i=st;i<=tar;++i) dis[i]=INF,vis[i]=0; dis[st]=0;
            hp.push((data){st,0}); while (!hp.empty())
            {
                int now=hp.top().id; hp.pop(); if (vis[now]) continue;
                vis[now]=1; for (i=head[now];i;i=e[i].nxt)
                if (dis[to]>dis[now]+e[i].v) hp.push((data){to,dis[to]=dis[now]+e[i].v});
            }
        }
        #undef to
}G;
inline void taddedge(CI x,CI y,CI z)
{
    e[++tcnt]=(edge){y,thead[x],z}; thead[x]=tcnt;
}
inline void addedge(CI x,CI y,CI z)
{
    e[++cnt]=(edge){y,head[x],z}; head[x]=cnt;
}
inline long long solve(long long ret=INF)
{
    RI i,j; for (F.read(n),F.read(m),F.read(k),i=1;i<=m;++i)
    F.read(x),F.read(y),F.read(z),taddedge(x,y,z);
    for (tar=n+1,i=1;i<=k;++i) F.read(a[i]);
    for (i=1;i<=(n<<1);i<<=1)
    {
        for (cnt=tcnt,j=st;j<=tar;++j) head[j]=thead[j];
        for (j=1;j<=k;++j) if (a[j]&i) addedge(st,a[j],0);
        else addedge(a[j],tar,0); if (G.Dijkstra(),dis[tar]<ret) ret=dis[tar];
    }
    for (i=1;i<=(n<<1);i<<=1)
    {
        for (cnt=tcnt,j=st;j<=tar;++j) head[j]=thead[j];
        for (j=1;j<=k;++j) if (a[j]&i) addedge(a[j],tar,0);
        else addedge(st,a[j],0); if (G.Dijkstra(),dis[tar]<ret) ret=dis[tar];
    }
    return ret;
}
inline void clear(void)
{
    for (RI i=st;i<=tar;++i) thead[i]=0; tcnt=0;
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    for (F.read(t);t;--t) printf("%lld\n",solve()),clear(); return 0;
}
```



---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5304)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;最最暴力的方法，枚举一个点作为起点，跑$Dijkstra$，然后取最小值。时间是$O(Tkm\log_2m)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑优化。实际上，我们根本不需要知道到底是哪一个点跟哪一个点组成了最短距离。这启发我们对点进行分组，一组为起点，一组为终点，然后用$Dijkstra$的伪多源汇版本跑出来两组点之间的最短距离。对于每次得到的最短距离，我们再取$\min$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑分组。对于一对点$u,v$，由于$u\not =v$，所以在二进制中，$u$必然有一位和$v$不同。所以我们枚举二进制位，每一次将该位为$0$的作为起点，为$1$的作为终点，跑一次；然后起终点互换再跑一次；最后再枚举下一位。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;正确性也已经说明了，答案的一对点必有一位二进制不同，所以一定会被枚举到。时间是$O(Tm\log_2m\log_2n)$  
# 代码
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

//#define int LL

const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e5 + 5, MAXM = 5e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
   	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct edge
{
	int to, nxt; LL w;
}Graph[MAXM];

struct node
{
	int u; LL dis;
	node(){} node( const int U, const LL Dis ) { u = U, dis = Dis; }
	bool operator < ( const node & other ) const { return ! ( dis < other.dis ); }
};

priority_queue<node> q;

LL dist[MAXN];
int seq[MAXN];
int head[MAXN];
LL ans;
int N, M, K, cnt;
bool visited[MAXN], sta[MAXN], fin[MAXN];

void addEdge( const int from, const int to, const int w )
{
	Graph[++ cnt].w = w, Graph[cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

LL Dijkstra()
{
	while( ! q.empty() ) q.pop();
	for( int i = 1 ; i <= N ; i ++ ) dist[i] = INF, visited[i] = false;
	for( int i = 1 ; i <= N ; i ++ ) if( sta[i] ) q.push( node( i, dist[i] = 0 ) );
	node h; int u, v; LL w;
	while( ! q.empty() )
	{
		h = q.top(), q.pop();
		if( fin[u = h.u] ) return h.dis;
		if( visited[u] ) continue; visited[u] = true;
		for( int i = head[u] ; i ; i = Graph[i].nxt )
		{
			v = Graph[i].to, w = Graph[i].w;
			if( ! visited[v] && dist[v] > dist[u] + w/* && dist[u] + w < ans*/ ) 
				q.push( node( v, dist[v] = dist[u] + w ) );
		}
	}
	return INF;
}

int main()
{
	LL ww;
	int T, fr, to;
	read( T );
	while( T -- )
	{
		for( int i = 1 ; i <= N ; i ++ ) head[i] = 0;
		read( N ), read( M ), read( K );
		ans = INF, cnt = 0;
		for( int i = 1 ; i <= M ; i ++ ) read( fr ), read( to ), read( ww ), addEdge( fr, to, ww );
		for( int i = 1 ; i <= K ; i ++ ) read( seq[i] );
		for( int i = 0 ; ( 1 << i ) <= N ; i ++ )
		{
			for( int j = 1 ; j <= N ; j ++ ) sta[j] = fin[j] = false;
			for( int j = 1 ; j <= K ; j ++ ) 
			{
				if( seq[j] & ( 1 << i ) ) sta[seq[j]] = true;
				else fin[seq[j]] = true;
			}
			ans = MIN( ans, Dijkstra() );
			for( int j = 1 ; j <= N ; j ++ ) sta[j] = fin[j] = false;
			for( int j = 1 ; j <= K ; j ++ ) 
			{
				if( seq[j] & ( 1 << i ) ) fin[seq[j]] = true;
				else sta[seq[j]] = true;
			}
			ans = MIN( ans, Dijkstra() );
		}
		write( ans ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：二分之一 (赞：1)

## 90 分

暴力方法

以每个感兴趣的点为起点，跑k遍最短路，取每两个感兴趣的点距离的最小值即可

由上，如果我们把每个点最短路全跑完再比较取值，绝对会TLE

而由dijkstra贪心的特性，我们可以得知，当弹出的点包含在k中且不是起点时，则这个点一定是由起点延伸出的最优情况

故我们只需跑k遍最短路，然后如果堆顶弹出的点包含在k中时，返回该店所对应的dis值就可以了

## 100 AC

当各位用上述方法提交上代码时，发现最后一个点T了，所以我们应该换种方法

简单说一下：

把包含于k中的点看做一个集合

以该集合为起点，正反跑两边dijkstra（spfa没试过）

把每个点都染上色（标记出离该点最近的，包含于k中的点）

(我在这里把正向跑dij的颜色称为cl1，反之称为cl2)

对于每条边，设边两点分别为x,y  正向边为 x->y

如果cl1x和cl2y不一致，则这条边会做出贡献

该边可以得到的选择为 sum=dij1x+dij2y+edge[该边]

最后得出来所有可能的ans的最小值即是答案

————————————————————————————

以下是代码

————————————————————————————

## 90:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 5000001
#define inf 0x3f3f3f3f3f3f3f3f
#define R register
using namespace std;
ll head[MAXN],ver[MAXN],edge[MAXN];
ll Next[MAXN],tot;
ll n,m,k;
bool a[MAXN];
ll s[MAXN];
ll T;
inline void add(ll x,ll y,ll z)
{
	ver[++tot]=y;edge[tot]=z;
	Next[tot]=head[x];head[x]=tot;
	return;
}
ll d[MAXN],vis[MAXN];
inline ll dijkstra(ll st)
{
	priority_queue <pair<ll,ll> > q;
	for(int i=1;i<=n;i++)
	    d[i]=inf,vis[i]=0;
	d[st]=0;
	q.push(make_pair(0,st));
	while(!q.empty())
	{
		ll x=q.top().second;
		q.pop();
		if(x!=st&&a[x]) return d[x];
		if(vis[x]) continue;
		vis[x]=1;
		for(R ll i=head[x];i;i=Next[i])
		{
			ll y=ver[i],z=edge[i];
			if(d[y]>d[x]+z)
			{
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
		} 
	}
}
ll x,y,z;
ll ans;
int main()
{
	scanf("%lld",&T);

	while(T--)
	{
		memset(Next,0,sizeof(Next));
		tot=0;
		scanf("%lld%lld%lld",&n,&m,&k);

		for(ll i=1;i<=n;i++) head[i]=0,a[i]=0;
		for(R ll i=1;i<=m;i++)
		{
			scanf("%lld%lld%lld",&x,&y,&z);

			add(x,y,z);

		}
		for(R ll i=1;i<=k;i++)
		{
			scanf("%lld",&s[i]);

			a[s[i]]=1;
		}
		ans=inf;
		for(R ll i=1;i<=k;i++)
		    ans=min(ans,dijkstra(s[i]));

		printf("%lld\n",ans);
	}
	return 0;
}
```

## AC:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 5000001
#define inf 0x3f3f3f3f
#define R register
using namespace std;
struct ndoe
{
	ll x,y,w;
}a[MAXN];
ll ver[MAXN],edge[MAXN],head[MAXN],Next[MAXN],tot;
inline void add(int x,int y,int z)
{
	ver[++tot]=y;edge[tot]=z;
	Next[tot]=head[x];head[x]=tot;
	return;
}
ll n,m,k,T;
ll d[MAXN][2],col[MAXN][2],vis[MAXN];
ll s[MAXN],pd[MAXN];
inline void dijkstra(ll e)
{
	for(ll i=1;i<=n;i++)
	    d[i][e]=inf,vis[i]=0;
	priority_queue< pair<ll,ll> > q;
	for(ll i=1;i<=k;i++)
	    d[s[i]][e]=0,col[s[i]][e]=s[i],
	    q.push(make_pair(0,s[i]));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(int i=head[x];i;i=Next[i])
		{
			int y=ver[i],z=edge[i];
			if(d[y][e]>d[x][e]+z)
			{
				d[y][e]=d[x][e]+z;
				col[y][e]=col[x][e];
				q.push(make_pair(-d[y][e],y));
			}
		}
	}
	return;
}
inline void clear()
{
	memset(head,0,sizeof(head));
	memset(Next,0,sizeof(Next));
	memset(pd,0,sizeof(pd));
	tot=0;return;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&m,&k);
		clear();
		for(int i=1;i<=m;i++)
		{
			scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].w);
			add(a[i].x,a[i].y,a[i].w);
		}
		for(int i=1;i<=k;i++)
		{
			scanf("%lld",&s[i]);
			pd[s[i]]=1;
		}
		dijkstra(0);
		clear();
		for(int i=1;i<=m;i++)
		    add(a[i].y,a[i].x,a[i].w);
		dijkstra(1);
		ll ans=inf;
		for(int i=1;i<=m;i++)
		{
			ll x=a[i].x,y=a[i].y,w=a[i].w;
			if(!col[x][0]||!col[y][1]) continue;
			if(col[x][0]==col[y][1]) continue;
			ans=min(d[x][0]+d[y][1]+w,ans);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

————————————————————————

PS:

1. 博主语文实在不太好，可能表达上有些问题，有的点也点的不透，抱歉~~QAQ~~

2. ~~如果不算最后的点，90跑的比AC的还快。。。~~

---

## 作者：Rainybunny (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.com.cn/problem/P5304).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本题解法多样, 这里带来一种玄学的方法: **二进制分组**.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们枚举每个二进制位, 按这一位二进制把结点编号分为两组, 一组作为起点, 全部塞入队列, 另一组作为终点, 跑一次$Dijkstra$, 把前者到后者的最短路用于更新答案. 复杂度$O(n\log_2^2n)$.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;正确性也不难证明: 假设答案路径是从$u$到$v$的最短路. 显然$u$和$v$的编号是不同的. 所以一定有一次分组, 使得$u$在起点一组, $v$在终点一组, 就找到了答案.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以, 这题怎么又黑了...  
## 代码
```cpp
#include <queue>
#include <cstdio>
#include <utility>

#define Int register int

using namespace std;

typedef long long int LL;
typedef pair<LL, int> pli;

const LL INF = 1LL << 62;
const int MAXN = 1e5, MAXM = 5e5;
int n, m, k, Cnte, Head[MAXN + 5], Import[MAXN + 5];
bool Mark[MAXN + 5];
LL Dist[MAXN + 5];

struct Edge {
	int To, Cost, _nxt;
	Edge () {}
	Edge ( const int t, const int c, const int n ): To ( t ), Cost ( c ), _nxt ( n ) {}
} Graph[MAXM + 5];

inline int rint () {
	int x = 0; char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () );
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' );
	return x;
}

inline LL Min ( const LL a, const LL b ) { return a < b ? a : b; }

inline int Max ( const int a, const int b ) { return a > b ? a : b; }

inline void Link ( const int f, const int t, const int c ) {
	Graph[++ Cnte] = Edge ( t, c, Head[f] );
	Head[f] = Cnte;
}

inline LL Dijkstra ( const int bit, LL* Dist, const bool r ) {
	LL ret = INF;
	static bool Vis[MAXN + 5];
	static priority_queue<pli, vector<pli>, greater<pli> > Q;
	for ( ; ! Q.empty (); Q.pop () );
	for ( Int i = 1; i <= n; ++ i ) Vis[i] = false, Dist[i] = INF;
	int Cnt = 0;
	for ( Int i = 1; i <= k; ++ i ) {
		if ( ( ( Import[i] >> bit ) & 1 ) == r ) {
			++ Cnt;
			Q.push ( { Dist[Import[i]] = 0, Import[i] } );
		}
	}
	if ( Cnt == k ) return INF;
	while ( ! Q.empty () ) {
		pli p = Q.top (); Q.pop ();
		if ( Vis[p.second] ) continue;
		Vis[p.second] = true;
		for ( Int i = Head[p.second], v; i; i = Graph[i]._nxt ) {
			if ( ! Vis[v = Graph[i].To] && Dist[v] > p.first + Graph[i].Cost ) {
				Q.push ( { Dist[v] = p.first + Graph[i].Cost, v } );
			}
		}
	}
	for ( Int i = 1; i <= k; ++ i ) {
		if ( ( ( Import[i] >> bit ) & 1 ) ^ r ) {
			ret = Min ( ret, Dist[Import[i]] );
		}
	}
	return ret;
}

inline void Work () {
	for ( Int T = rint (); T --; ) {
		int mx = 0;
		n = rint (), m = rint (), k = rint ();
		Cnte = 0;
		LL Ans = INF;
		for ( Int i = 1; i <= n; ++ i ) Head[i] = 0;
		for ( Int i = 1, u, v, w; i <= m; ++ i ) u = rint (), v = rint (), w = rint (), Link ( u, v, w );
		for ( Int i = 1; i <= k; ++ i ) Mark[i] = false;
		for ( Int i = 1; i <= k; ++ i ) mx = Max ( Import[i] = rint (), mx ), Mark[Import[i]] = true;
		for ( int i = 0; 1 << i <= mx; ++ i )
			Ans = Min ( Ans, Dijkstra ( i, Dist, false ) ),
			Ans = Min ( Ans, Dijkstra ( i, Dist, true ) );
		printf ( "%lld\n", Ans );
	}
}

int main () {
//	freopen ( "tourist.in", "r", stdin );
//	freopen ( "tourist.out", "w", stdout );
	Work ();
	return 0;
}
```

---

