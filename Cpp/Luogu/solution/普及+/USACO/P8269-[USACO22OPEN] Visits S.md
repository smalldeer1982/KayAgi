# [USACO22OPEN] Visits S

## 题目描述

Bessie 的 $N$（$2\le N\le 10^5$）个奶牛伙伴（编号为 $1\cdots N$）每一个都拥有自己的农场。对于每个 $1\le i\le N$，伙伴 i 想要访问伙伴 $a_i$（$a_i\neq i$）。

给定 $1\ldots N$ 的一个排列 $(p_1,p_2,\ldots, p_N)$，访问按以下方式发生。

对于 $1$ 到 $N$ 的每一个 $i$：

- 如果伙伴 $a_{p_i}$ 已经离开了她的农场，则伙伴 $p_i$ 仍然留在她的农场。
- 否则，伙伴 $p_i$ 离开她的农场去访问伙伴 $a_{p_i}$ 的农场。这次访问会产生快乐的哞叫 $v_{p_i}$ 次（$0\le v_{p_i}\le 10^9$）。


对于所有可能的排列 $p$，计算所有访问结束后可能得到的最大哞叫次数。

## 说明/提示

【样例解释】


如果 $p=(1,4,3,2)$，则

- 伙伴 $1$ 访问伙伴 $2$ 的农场，产生 $10$ 次哞叫。
- 伙伴 $4$ 看到伙伴 $1$ 已经离开了农场，所以无事发生。
- 伙伴 $3$ 访问伙伴 $4$ 的农场，又产生 $30$ 次哞叫。
- 伙伴 $2$ 看到伙伴 $3$ 已经离开了农场，所以无事发生。

这样总计得到了 $10+30=40$ 次哞叫。

另一方面，如果 $p=(2,3,4,1)$，则

- 伙伴 $2$ 访问伙伴 $3$ 的农场，产生 $20$ 次哞叫。
- 伙伴 $3$ 访问伙伴 $4$ 的农场，产生 $30$ 次哞叫。
- 伙伴 $4$ 访问伙伴 $1$ 的农场，产生 $40$ 次哞叫。
- 伙伴 $1$ 看到伙伴 $2$ 已经离开了农场，所以无事发生。

这样总计得到了 $20+30+40=90$ 次哞叫。可以证明这是所有可能的排列 $p$ 中访问结束后得到的最大可能的哞叫次数。

## 样例 #1

### 输入

```
4
2 10
3 20
4 30
1 40```

### 输出

```
90```

# 题解

## 作者：YBaggio (赞：18)

## 题意
一共有 $n$ 头奶牛，每一头奶牛都有自己想拜访的奶牛，用 $a_i$ 表示牛 $i$ 想拜访的牛。对于每一头牛 $i$，如果它想拜访的牛在家，就会离开家并拜访它，还会增加 $v_i$ 的欢乐值，最后求欢乐值的最大值。
## 思路
我们可以将这个问题看作一个一个图，且每一个节点的出度都是 $1$。 我们可以发现除了每个环中会有一个奶牛无法获得高兴值，其他的奶牛都可以获得高兴值。

我们可以用拓扑排序来找到所有不在环上的奶牛，将答案加上他们的高兴值。接下用 dfs 找出每个环。对于每个环中的无法获得高兴值的奶牛，我们肯定选高兴值最小的。找到每个环的奶牛的非小值并加上它们。

最后在贴上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 1e18+10
#define int long long
const int maxn=100010;
int n,a[maxn],v[maxn],rd[maxn],ans,minn=inf;
bool vis[maxn];
queue<int>q;
void topo(){
    for(int i=1;i<=n;i++){
        if(!rd[i])q.push(i);
    }
    while(!q.empty()){
        int x=q.front();q.pop();
        ans+=v[x];rd[a[x]]--;
        vis[x]=1;
        if(!rd[a[x]])q.push(a[x]);
    }
    return;
}
void dfs(int x){
    vis[x]=1;
    minn=min(minn,v[x]);
    if(vis[a[x]])return;
    dfs(a[x]);
    return;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&a[i],&v[i]);
        rd[a[i]]++;
    }
    topo();
    for(int i=1;i<=n;i++){
        if(!vis[i])ans+=v[i];
    }
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        minn=inf;dfs(i);
        ans-=minn;
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：enucai (赞：10)

## Preface

**基环树**好题。

## Analysis

对于所有 $i$，在图上连一条 $i\to a_i$ 的有向边。由于每头奶牛只有一条出边，不难发现这是一个有向的**基环森林**。

对于一棵基环树，每个不在环上的点必然可以做出贡献，只要将她们按照在所属子树中的 $dep$ 值**从大到小**加入排列即可（这样必然能让每头奶牛都走到她们喜欢的奶牛的农场中，即 **先让她来，我再走**）。

在环上的点必然有一个无法走到自己喜欢的奶牛的农场中，并且一定能做到**只让一头牛**这样。因此只要在环上找一个**贡献最小**的奶牛即可。

时间复杂度 $O(n)$。

## Code

**Talk is cheap, show me the code.**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define N 100010
int n,a[N],val[N],vis[N],vis2[N];
vector<int> e[N];
void dfs(int u){
	vis[u]=1;
	for(int v:e[u]) if(!vis[v]) dfs(v);
}
signed main(){
	cin>>n;
	For(i,1,n){
		cin>>a[i]>>val[i];
		e[a[i]].push_back(i);
	}
	int ans=0;
	For(i,1,n) ans+=val[i];
	For(i,1,n) if(!vis[i]){
		int u=i,mn=1e10;
		while(!vis2[u]) vis2[u]=1,u=a[u];
		int v=u;
		do mn=min(mn,val[v]),v=a[v]; while(v!=u);
		ans-=mn;
		dfs(u);
	}
	cout<<ans<<endl;
}
```

---

## 作者：tzyt (赞：5)

update： 2022/4/17 更正了博客地址

[题目连接](https://www.luogu.com.cn/problem/P8269)

[博客中观看体验更佳](https://ttzytt.com/2022/04/P8269/)
# 1：题意简述
有 $N$ 个奶牛，奶牛 $i(1 \le N)$ 想访问奶牛 $a_i (a_i \ne i)$。如果 $a_i$ 已经离开去访问别的奶牛了，则 $i$ 不能成功访问 $a_i$，否则，这次成功访问可以增加 $v_i$ 次哞叫。 现在让你找出可能的最大哞叫次数。

# 2：分析
理解题目后，我们可以首先分析下样例，试试看找一些有用的信息。
![](https://cdn.luogu.com.cn/upload/image_hosting/45pac1tr.png)
为了方便分析样例，我们可以把样例用图的形式展示，图中有向边连接的两个节点就是一头牛和这头牛希望访问的牛 （$i$ 和 $a_i$)。而边权是这次访问能产生的哞叫次数。

通过这张图，我们可以发现，不管以什么样的顺序访问，最多都只能成功的访问三次，最后的一次访问一定会遇到之前已经遇到过的牛，所以选择 $2 \rarr 3$，$3 \rarr 4$ 和 $4 \rarr 1$ 可以达到最大的哞叫次数，也就是 $20 + 30 + 40 = 90$ 次。

再仔细思考这个样例，可以发现不能同时选四条边的本质原因是这样会在图中产生一个环。如果图中有环，并且必须要经过环上的每一条边，那么我们必然会访问到之前访问过的节点。

而如果我们能从原来的图中选出一些边，建出一个没有环的图，那么就一定能找出一种访问顺序，使得我们在遍历所有节点时不会重复访问节点。在不构成环的前提下，我们还需要尽量选择边权大的边，这样就能满足题目的要求——产生最多的哞叫次数。

没有环的，权值最大的图？好像跟最小（大）生成树很相似。

分析到这里，我们就比较容易想到使用最小（大）生成树算法了。通过这类算法，我们可以在图中找出权值最大的树。不过，这还是跟这道题不完全一样。我们还需要解决下面这个问题。

- 最小（大）生成树的算法只能用于无向图中，而我们当前的图是有向图，所以我们可以直接把最小（大）生成树算法用在这道题里吗

（这部分如果理解了可以直接看代码)，代码就是个标准的 kruskal

换一种说法解释这个问题就是：从有向图转换来的无向图是否和原图等价？

![](https://cdn.luogu.com.cn/upload/image_hosting/tcj0rl6u.png)

比如上图这样的情况，不管使用什么访问顺序，三条边我们都是可以选的。但是转换成了无向图之后，就只能选择两条边了（选三条边会产生环）。

在题目中，每一奶牛只有一个想访问的奶牛，也就是说图中的每个节点出度都是 $1$，在这样的条件下，上图中的情况就是不可能出现的（上图中节点 $1$ 的出度为 $2$），并且转换出来的无向图和原图也是等价的。

那为什么只有入度大于 $1$ 时才会导致转换之后的无向图不等价于原来的有向图呢？

我们知道如果有 $n$ 个节点，要把这 $n$ 个节点包含在环中的最少边数是 $n$ 个。并且这 $n$ 个节点里面的每个节点的出度和入度都等于 $1$ 。就和样例中的一样。

一个边可以产生一个出度和一个入度。所以这个环里总共有 $2n$ 个度。如果我们允许一些节点的出度大于 $1$，那么有一些节点的入度可能是 $0$ 了（度的和一定为 $20$，那出度增加了入度就一定会减少），这样一来，入度为 $0$ 时没有别的节点能到达这个节点，自然就不能产生环。

但是如果把直接转换成无向图，出度和入度的总和还是 $2n$，每个节点的度也是 $2$，所以能构成环。

这样一来，在转换时就会产生问题了。

# 3：代码
这里我才用的是 Kruskal 来求的最大生成树，相较于这题的思维，代码还是比较简单的，只要把最小生成树中的排序改一下。

如果不熟悉最小生成树的算法，可以参考[模板题](https://www.luogu.com.cn/problem/P3366)里的题解

需要注意的是权值和可能会超过 `int` 的范围，需要开 `long long`。
```cpp
/*Date: 22 - 03-26 15 28
PROBLEM_NUM: USACO MAR Problem 1. Visits*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
#define ll long long
struct E
{
    int from, to, val;
} e[MAXN];
int n;
int fa[MAXN];
int find_fa(int cur)
{
    if (cur == fa[cur])
        return cur;
    return fa[cur] = find_fa(fa[cur]);
}
void merge(int a, int b)
{
    int af = find_fa(a), bf = find_fa(b);
    fa[af] = bf;
}
//并查集操作

ll ans;

int main()
{
    scanf("%d", &n);
    iota(fa + 1, fa + 1 + n, 1);//最开始 fa[i] = i
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &e[i].to, &e[i].val);
        e[i].from = i;
    }
    sort(e + 1, e + 1 + n, [](E a, E b)
         { return a.val > b.val; });//权值大的放前面
    int used_edge = 0;
    for (int i = 1; i <= n; i++)//kruskal
    {
        if (find_fa(e[i].from) != find_fa(e[i].to))
        {
            used_edge++;
            ans += e[i].val;
            merge(e[i].from, e[i].to);
            if (used_edge == n - 1)
            {
                break;
            }
        }
    }
    printf("%lld\n", ans);
    system("pause");
}
```
最后希望这篇题解能帮到你。如果有看不懂的，或者是发现题解有问题，欢迎通过评论区和私信联系我。

---

## 作者：Mars_Dingdang (赞：4)

洛谷上为什么没有题解 /yiw，那我就来用绿题难度的方法做这道黄题吧。同步发表于 [博客园](https://www.cnblogs.com/Mars-LG/p/P8269.html)。

## 题目大意
Bessie 的 $N$（$2\le N\le 10^5$）个奶牛伙伴（编号为 $1\cdots N$）每一个都拥有自己的农场。对于每个 $1\le i\le N$，伙伴 $i$ 想要访问伙伴 $a_i$（$a_i\neq i$）。

给定 $1\ldots N$ 的一个排列 $(p_1,p_2,\ldots, p_N)$，访问按以下方式发生。

对于 $1$ 到 $N$ 的每一个 $i$：

- 如果伙伴 $a_{p_i}$ 已经离开了她的农场，则伙伴 $p_i$ 仍然留在她的农场。
- 否则，伙伴 $p_i$ 离开她的农场去访问伙伴 $a_{p_i}$ 的农场。这次访问会产生快乐的哞叫 $v_{p_i}$ 次（$0\le v_{p_i}\le 10^9$）。

对于所有可能的排列 $p$，计算所有访问结束后可能得到的最大哞叫次数。

## 大体思路
首先，我们将所有 $(i,a_i)$ 连上有向边。这样，共有 $n$ 个节点 $n$ 条边，形成的是一个内向树的森林。

我们单独考虑每一棵内向树，这个内向树上必然有且仅有一个简单环，其余每个节点的出度为 $1$。

我们对非成环的节点按照拓扑序，让当前一个入读为 $0$ 的节点 $u$ 取到 $a_u$，并获得 $v_u$ 的收益。可以证明，通过这样的方式能够使得所有非成环节点的 $v_u$ 都被收集到。

对于成环的节点，这相当于一个大小 $>1$ 的强连通分量。所以，我们可以使用 $\text{Tarjan}$ 算法求出这个强连通分量 $\mathbf{SCC}$。假设环上节点 $x$ 最先去访问 $a_x$，则 $a_y=x$ 的环上节点 $y$ 无法访问到 $x$，也就是说有且仅有 $v_y$ 无法收集到。那么，我们根据贪心，只需要让 $y$ 是所有环上节点中点权最小的即可。

注意原图可能是一个森林，因此需要多次 $\text{Tarjan}$，分别减去每个环上点权的最小值。

综上，假设有 $c$ 个环，答案为 $\sum v_u-\sum_{i\in [1,c]}\min\{v_u\ |\ u\in \mathbf {SCC}_i\}$，时间复杂度 $O(n)$。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
const ll inf = 1e9 + 7;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
ll n, val[maxn], mi[maxn], sz[maxn];
ll hd[maxn], ver[maxn], nxt[maxn], tot, timer, dfn[maxn], low[maxn];
inline void add(ll u, ll v) {
	ver[++tot] = v; nxt[tot] = hd[u]; hd[u] = tot;
}
ll scc[maxn], cnt, stk[maxn], top;
inline void tarjan(ll u) {
	dfn[u] = low[u] = ++timer;
	stk[++top] = u;
	for(int i = hd[u]; i; i = nxt[i]) {
		int v = ver[i];
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(!scc[v]) 
			low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		mi[++cnt] = inf;
		while(1) {
			int v = stk[top --];
			scc[v] = cnt;
			sz[cnt] ++; 
			mi[cnt] = min(mi[cnt], val[v]);
			if(u == v) break;
		}
	}
}
int main () {
	ll sum = 0;
	read(n);
	rep(i, 1, n) {
		ll u; 
		read(u); read(val[i]);
		add(i, u);
		sum += val[i];
	}
	rep(i, 1, n)
		if(!dfn[i]) tarjan(i);
	rep(i, 1, cnt) 
		if(sz[i] > 1) sum -= mi[i];
	writeln(sum);	
	return 0;
}
```

---

## 作者：junxis (赞：3)

# 0.吐槽
这次大概又进不了 Au 了，这次银组真就难得离谱……

又是图论又是数据结构的，出题组色盲了？

# 1.分析

我们考虑将问题转化为图论的模型。

$$\mathcal{V}=\{i|1 \leq i \leq N\}$$

$$\mathcal{E}=\{i \in \mathcal{V}|(i,a_i,v_i) \}$$

$$\mathcal{G}=(\mathcal{V},\mathcal{E})$$

我们考察 $\mathcal{G}$ 中的一个环 $\mathcal{R}$ 。

假设我们从环的第 $i$ 个点开始模拟，且环内有点 $j$ 满足 $a_j=i$ ：

+ $i$ 拜访 $a_i$，获得权值 $v_i$ 。
+ $a_i$ 拜访 $a_{a_i}$，获得权值 $v_{a_i}$ 。

	$\dots\dots$
+ $j$ 无法拜访 $i$ ，循环结束。

此时， $\mathcal{R}$ 对答案的贡献：

$$c(\mathcal{R})=\sum\limits_{i \in \mathcal{R}}(v_i)-v_j$$

为了使答案最优，由于环之间互不影响，我们可以贪心地推导出：

$$c_{\max}(\mathcal{R})= \sum\limits_{i \in \mathcal{R}}(v_i)-\min\limits_{i \in \mathcal{R}}(v_i)$$

自然地：

$$Ans=\sum\limits_{\mathcal{R} \in \mathcal{G}}(c_{\max}(\mathcal{R}))$$

此时，我们发现这个式子的难点在求出环。

由于 $\mathcal{G}$ 所有点的出度均为 $1$，故 $\mathcal{G}$ 为基环森林。

感性理解：对于这棵基环树，根据第二个式子，每找到一个环就把他去一条边，这样会使基环森林**直接退化成森林**。

而对于这个森林，答案就是所有边权之和，所以这个式子就是求最大权值森林。

我们利用 `kruskal` 算法解决即可。

~~优美无比~~

# 2.代码

```cpp
#include<bits/stdc++.h>
#define ll long long
const int N=2e5+5;
int n;
struct edge{
	int u,v,w;
}e[N];
inline bool cmp(edge x,edge y)
{
	return x.w>y.w;
}
int fa[N];
int find(int x)
{
	while(x!=fa[x])x=fa[x]=fa[fa[x]];
	return x;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		e[i].u=i;
		scanf("%d%d",&e[i].v,&e[i].w);
	}
	/*以下是Kruskal板子，但注意，此时求的是森林，并不强制要求 边数==n-1 而是 边数<=n-1 */
	std::sort(e+1,e+1+n,cmp);//与MST反过来排序 
	int tot=0;
	ll ans=0;//不开long long * * * 
	for(int i=1;i<=n;i++)fa[i]=i;//并查集初始化 
	for(int i=1;i<=n;i++)
	{
		int x=find(e[i].u),y=find(e[i].v);
		if(x==y)continue;
		fa[x]=y;
		tot++;
		ans+=e[i].w;
		if(tot==n-1)
		{
			printf("%lld",ans);
			return 0;
		}
	}
	printf("%lld",ans);
	return 0;
}

```


# 3.后记

这道题到这里就结束了，银组考这么难是不是不太合适？

不愧为巨佬 Benq 出的题啊，把我吊打四个小时。

这个结论很恶心啊，我是怎么想出来的？

**样例。**

---

## 作者：starrylasky (赞：2)

[博客食用更佳](https://www.cnblogs.com/hhhsky001/articles/16391548.html)

## 题面描述

对于第 $i$ 数，如果 $p_i$ 在他之前，那就产生 $v_i$ 的贡献。求这个贡献值最大。

## Solution

我们可以将此问题转化为用所有的贡献值-所有排列中最小的贡献值。

那么一个显然的思路，考虑在 $v$ 在 $u$ 前会产生贡献时连一条 $u \to v$  的有向边。

* 当且仅当形成环时，一定会产生贡献，题上说取最小，故我们在这个环上找到最小的不满值，累加入答案。

* 当未形成环时，总有一种方式不会产生贡献。

因为每一个数出度入度只有 $1$ ，所以一个数只可能在一个环上。所以我们在深搜时，每个点只需要搜一次，所以时间复杂度为 $O(n)$ 。

~~在2022-06-19 21:36:16时到达最优解~~

## Code

```cpp
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define re register
//#define int long long
#define fep(i,l,r) for(re int i=l;i<=r;++i)
#define For(i,u) for(re int i=head[u];i;i=e[i].nxt)
#define feb(i,r,l) for(re int i=r;i>=l;--i)
#define LL long long
using namespace std;
 
const int N = 1e5+5,mod = 1e9+7;
int n,to[N],c[N],s[N],top,pos[N]; bool vis[N],belong[N]; LL ans;
 
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5; 

namespace quick {
#define tp template<typename Type>
	namespace in {
		inline char getc() {
			static char buf[1<<21],*p1=buf,*p2=buf;
			return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
		}
		inline int read(char *s) {
			*s=getc();
			while(isspace(*s)) {*s=getc();if(*s==EOF) return 0;}
			while(!isspace(*s)&&*s!=EOF) {s++;*s=getc();}
			*s='\0'; return 1;
		}
		tp inline int read(Type &x) {
			x=0;bool k=false;char c=getc();
			while(!isdigit(c)) {k|=(c=='-');c=getc();if(c==EOF) return 0;}
			while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getc();}
			x*=(k?-1:1); return 1;
		}
		template <typename Type,typename... Args>
		inline int read(Type &&t,Args &&...args) {
			return read(t)+read(args...);
		}
	}
	using in::read;
	namespace out {
		char buf[1<<21];int p1=-1;const int p2=(1<<21)-1;
		inline void flush() {
			fwrite(buf,1,p1+1,stdout);
			p1=-1;
		}
		inline void putc(const char &c) {
			if(p1==p2) flush();
			buf[++p1]=c;
		}
		inline void write(char *s) {
			while(*s!='\0') putc(*s),s++;
		}
		inline void write(const char *s) {
			while(*s!='\0') putc(*s),s++;
		}
		tp inline void write(Type x) {
			static char buf[30];int p=-1;
			if(x<0) {putc('-');x=-x;}
			if(x==0) putc('0');
			else for(;x;x/=10) buf[++p]=x%10+48;
			for(;p!=-1;p--) putc(buf[p]);
		}
		inline void write(const char &c) {putc(c);}
		template <typename Type,typename... Args>
		inline void write(const Type &t,const Args &...args) {
			write(t);write(args...);
		}
	}
	using out::write;
	using out::flush;
#undef tp
}
using namespace quick;

inline void dfs(int u)
{
	if(vis[u])
	{
		int minn=1e9;
		fep(i,pos[u],top) minn=min(minn,c[s[i]]),belong[s[i]]=true;;
		ans+=minn; return ;
	}
	if(belong[u])
	{
		fep(i,1,top) belong[s[i]]=true; return ;//一定要有这句，否则保证不了时间复杂度的线性
	}
	vis[u]=true; s[++top]=u; pos[u]=top;
	dfs(to[u]);
	vis[u]=false; --top;
}
 
signed main()
{
	read(n); LL sum=0;
	fep(i,1,n) read(to[i],c[i]),sum+=c[i];
	fep(i,1,n) if(!belong[i]) dfs(i);
	write(sum-ans);
	return flush(),0;
}
```


---

## 作者：Sparkle_ZH (赞：2)

**题意简述**
+ 有 $n$ 只奶牛，第 $i$ 只奶牛希望拜访第 $a_i$ 只奶牛。
+ 给定一个 $1$ . . . $N$ 的排列 $(p_1, p_2, ..., p_n)$，对于从 $1$ 到 $n$ 的每一个 $i$：
  + 如果奶牛 $a_{p_i}$ 已经离开了她的农场，那么奶牛 $p_i$ 仍然留在她的农场。
  + 否则，奶牛 $p_i$ 就会离开她的农场去拜访第 $a_{p_i}$ 只奶牛，并产生 $v_{p_i}$ 次快乐的哞叫。
+ 给出序列 $a_n$ 与 $v_n$，对于所有可能的排列 $p$，计算可能得到的快乐哞叫的次数的最大值。
+ $2 \leq n \leq 10^5$，$0 \leq v_i \leq 10^9$。

**解题思路**

十分有趣的图论题。

我们建立一个 $n$ 条边 $n$ 个点的有向图，第 $i$ 条边从 $i$ 连向 $a_i$。注意到图不一定连通。

首先考虑对于 $a_i \neq a_j$ 的部分分如何解决。这种情况下，每个连通块都形成一个简简单单的环。

容易发现最优情况下，应当是先由一头起始奶牛 $i$ 拜访 $a_i$，然后 $a_i$ 拜访 $a_{a_i}$，然后 $a_{a_i}$ 拜访 $a_{a_{a_i}}$，以此类推。

![图片 1](https://cdn.luogu.com.cn/upload/image_hosting/hvq8p1gs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以这种情况下，每个连通块的答案就是 $v_i$ 的和减去这个连通块内 $v_i$ 的最小值。

那么对于非特殊情况，我们如何解决呢？先随意画出一张可能的有向图观察一下吧。

![图片 2](https://cdn.luogu.com.cn/upload/image_hosting/nc9fmrds.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们发现每一个连通块内有且仅有一个环，那么我们就可以把点分成两类：
+ 如果这个点不在环上，我们先让它进行拜访，它一定能对答案产生贡献。（见下图）
+ 如果这个点在环上，那么我们用部分分的思路推导，也一定有且仅有一个环上的点无法产生贡献。

![图片 3](https://cdn.luogu.com.cn/upload/image_hosting/ecj9zsd8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

问题也就迎刃而解了。我们对于每个连通块，统计所有 $v_i$ 的和，再减去**环上**的点的 $v_i$ 的最小值，就是答案。

**代码**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = (x<<3) + (x<<1) + ch - '0', ch = getchar();
    return x;
}

const int L = 1e5 + 5;
int n, ans, minn, a[L], v[L], f[L], in[L];
vector<int> vec, son[L];
bool vis[L];

void get_point(int x) { // 获取每一个连通块中的点
    vis[x] = true, vec.push_back(x);
    for (int i = 0; i < son[x].size(); i++)
	if (!vis[son[x][i]]) get_point(son[x][i]);
    if (!vis[a[x]]) get_point(a[x]);
}

void get_circle(int x) { // dfs 找环，同时直接更新最小值
    f[x]++;
    if (f[x] == 2) minn = min(minn, v[x]);
    if (f[a[x]] != 2) get_circle(a[x]);
}

signed main() {
    n = read();
    for (int i = 1; i <= n; i++)
	a[i] = read(), v[i] = read(), son[a[i]].push_back(i), in[a[i]]++;
		
    for (int i = 1; i <= n; i++) {
	if (vis[i]) continue;
	minn = L*L;
	get_point(i);
	get_circle(i);
	for (int j = 0; j < vec.size(); j++)
    	    ans += v[vec[j]];
	ans -= minn;
	vec.clear();
    }
	
    printf("%lld", ans);
	
    return 0;
}
```

---

## 作者：xixike (赞：1)

[更好的阅读体验](https://xixike.github.io/USACO2022.3%20Silver/)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/P8269)

## Solution

手玩一遍样例，找找最优决策，不难发现一个环中最优情况瞎只有一个点不能选。

并且题目给出的关系是一个基环树森林。

所以先求一下总和， 然后 $\text{Tarjan}$ 找每一个环上的最小值，用总和减去即可。

另外要判一下环的大小大于等于 2 时才能减（一个点时显然是可以加上的）。

## Code
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define ll long long

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 1e6 + 10;
int n, m;
ll sum;
int a[N], v[N];
vector <int> g[N];
int dfn[N], low[N], tim;
int stk[N], top;
bool vis[N];

inline int tarjan(int x){
    dfn[x] = low[x] = ++tim;
    stk[++top] = x, vis[x] = 1;
    for(auto y : g[x]){
        if(!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
        else if(vis[y]) low[x] = min(low[x], dfn[y]);
    }
    int siz = 0, mins = 1e9;
    if(low[x] == dfn[x]){
        int k;
        do{
            k = stk[top--];
            vis[k] = 0, siz++, mins = min(mins, v[k]);
        }while(x != k);
    }
    return mins * (siz > 1 ? 1 : 0);
}

signed main(){
    n = read();
    for(int i = 1; i <= n; ++i){
        a[i] = read(), v[i] = read(), sum += v[i];
        g[a[i]].pb(i);
    }
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) sum -= tarjan(i);
    write(sum), puts("");
    return 0;
}
```

---

## 作者：小木虫 (赞：1)

### Problem
原题面：
有 $n$ 头奶牛，每头奶牛要去探亲（只探一只），探完亲后留在那个奶牛的家里。如果奶牛到达一头奶牛家后发现它不在家，就会失望地走掉。否则会发出 $v_i$ 声快乐的叫声。现在要你找到这些奶牛的最佳行动顺序使得叫声数量最大。
  
简化题意：给定一个 $n$ 点 $n$ 边有向图，将图中所有环断开后剩下的边权最大。
### Solution
发现题目对于每个点只有一条出边，很容易让人想到树。于是我们将这条边的连接点看为该点的父亲。有 $n$ 条边所以这是一个或多个基环树。拓扑排序后将每棵基环树唯一的环找到其中最小值就好了。  
code:  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;int a[N];int v[N];
bool vis[N];int deg[N];
queue <int> Q;
long long ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&v[i]);
		deg[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(!deg[i])Q.push(i);
	}
	while(!Q.empty()){
		int u=Q.front();Q.pop();vis[u]=true;
		int to=a[u];
		deg[to]--;ans+=v[u];
		if(!deg[to]){
			Q.push(to);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int MIN=1e9+10;
			int u=i;long long sum=0;
			while(!vis[u]){
				sum+=v[u];MIN=min(MIN,v[u]);vis[u]=true;u=a[u];
			}
			ans+=sum-MIN;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

既然每头牛都要去另一头牛那里，我们就可以用一个图来表示这些情况。

那么，$N$ 个点 $N$ 条边是什么图呢？

因为 $N$ 个点 $N-1$ 条边是一棵树，那么树加一条边就是传说中的**基环树**。

所谓基环树，就是树上有了一个环（普通的树是双向边，在哪里加一条边都有环）。

不过，这个图不一定联通，我们就只能称其为**基环树森林**。

我们把它分成两个部分：主干部分（环）和分支部分（环外面的枝杈）。

因为每头牛只会想去一个地方，所以这个有向图的分支部分都是从外面连向环上的点。我们如果想要求出最大边权和，分支部分肯定是可以通过拓扑排序的方式全都得到，然后连到环上。

因为环是一个环，因此他必须会有一条边的边权无法获得。为了让我们的答案尽量大，肯定选边权最小的那一条不获得。

在实际计算过程中，在从一个节点访问时遇到一个访问过的节点时，会有两种情况：

1. 遇到了自己访问的路上的节点，说明这条路上有环，而且这个节点一定是环上的点
2. 遇到了别的路上的节点，就不用继续访问了

遇到有环的话，我们就从这个环上的点往回找，直到再找到他，这个过程中就可以找最小边权了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],v[100005],vis[100005];//vis为0表示没访问过，为1表示是现在路上的，为2表示是其他路上的
long long tot,ans;
int mn(int u){//在路上取最小边权
	int res=v[u];
	for(int i=a[u];i!=u;i=a[i]) res=min(res,v[i]);
	return res;
}
void end(int x){//把所有自己路上的都改成“别的路上的”，说明遍历结束
	while(vis[x]==1) vis[x]=2,x=a[x];
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>v[i];tot+=v[i];//计算总边权和
	}
	int x;
	for(int i=1;i<=n;i++){
		if(!vis[i]){//没有访问过
			x=i;
			while(!vis[x]){//一直往前找
				vis[x]=1;
				x=a[x];
			}
			if(vis[x]==1) ans+=mn(x);//ans表示要减去的所有边权
			end(i);//遍历结束
		}
	}
	cout<<tot-ans<<endl;//总的减去不能获得的，就是答案
	return 0;
}
```

---

