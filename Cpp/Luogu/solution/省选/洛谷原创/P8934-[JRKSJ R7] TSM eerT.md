# [JRKSJ R7] TSM eerT

## 题目描述

对于一个 $n$ 个结点的带边权的树 $T$，定义 $dis(x,y)$ 为 $T$ 中 $x\to y$ 路径上的边权和。再定义一个 $n$ 个结点的无向完全图 $p(T)=G$，其中 $\forall x,y\in [1,n]$，$G$ 中边 $(x,y)$ 的边权为 $dis(x,y)$。

定义 $f(T)$ 为 $p(T)$ 的最大生成树。特别的，若 $p(T)$ 的最大生成树不唯一，请立刻判断出并报告。

给定树 $T_0$ 和整数 $k$，求 $f^k(T_0)$。其定义将在下文给出。

## 说明/提示

### 定义

$f^k(T)$ 的定义为：
$$f^k(T)=\begin{cases}T&k=0\\f(f^{k-1}(T))&k>0\end{cases}$$

### 样例 $1$ 解释


![](https://cdn.luogu.com.cn/upload/image_hosting/fpcq3bmt.png)

分别是 $T_0,f(T_0),f^2(T_0),f^3(T_0)$。

以计算 $f(T_0)$ 的过程为例，生成的 $p(T_0)=G$ 为

![](https://cdn.luogu.com.cn/upload/image_hosting/3st5aet7.png)

最大生成树上的边为 $(1,3),(2,3)$。

### 数据规模

本题采用捆绑测试。
| $\text{Subtask}$ | $n\le$ |  $k\le$ | $\text{Score}$ | 
| :----------: | :----------: | :----------: | :----------: | 
| $1$ | $10^3$ | $1$ | $10$ | 
| $2$ | $10^5$ | $1$ |$20$ |
| $3$ | $10^6$ | $1$ |$30$ |
| $4$ | $10^6$ | $10^7$ |$40$ |

对于 $100\%$ 的数据，$2\le n\le 10^6$，$1\le k\le 10^7$，$1\le f_i<i$，$1\le v_i\le10^9$。

### 特殊评分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i$，您需要答对所有 $j\in[1,i]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。

## 样例 #1

### 输入

```
3 3
1 1
2 2```

### 输出

```
13```

## 样例 #2

### 输入

```
10 2
1 7
1 2
1 5
4 5
2 1
3 9
2 9
4 4
9 4```

### 输出

```
736```

## 样例 #3

### 输入

```
4 1
1 1
2 1
3 1```

### 输出

```
-1```

# 题解

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8934)
## 题意
对于一个 $n$ 个结点的带边权的树 $T$，定义 $\text{dis}(x,y)$ 为 $T$ 中 $x\to y$ 路径上的边权和。再定义一个 $n$ 个结点的无向完全图 $p(T)=G$，其中 $\forall x,y\in [1,n]$，$G$ 中边 $(x,y)$ 的边权为 $\text{dis}(x,y)$。

定义 $f(T)$ 为 $p(T)$ 的最大生成树。特别的，若 $p(T)$ 的最大生成树不唯一，请立刻判断出并报告。

给定树 $T_0$ 和整数 $k$，求 $f^k(T_0)$。**边权为正整数。**

若 $\exists x\in[0,k-1]$ 使得 $p(f^x(T_0))$ 的最大生成树不唯一，输出 $-1$。否则，输出 $f^k(T_0)$ 的所有边权和对 $2^{32}$ 取模的结果。

$n\le 10^6$，$1\le k\le 10^7$。
## 思路
来补个严谨证明。

考虑 $k=1$ 的部分分。

使用 $\operatorname{Boruvka}$ 算法。我们对每个点找到距离它最远的点并与其连边。很显然，经过一次 $\operatorname{Boruvka}$ 算法，所有的点已经连通。原因是树上每个点距离最远的点为直径两端点之一，而直径两端点互相连接。

假设答案不是 $-1$，我们就已经得到了 $f(T_0)$ 了。来判断答案是不是 $-1$，共有以下情况：

- 直径不唯一

我们先证明，不会存在两条互不相交的直径。

反证，考虑存在下面的树，满足 $3\to 4$，$6\to 7$ 为两条直径。

![](https://cdn.luogu.com.cn/upload/image_hosting/zvdnb714.png?x-oss-process=image)

不妨令 $x=x_1+x_2>0$，$a>b>0$，$c\ge d>0$。

显然，$a+b\ge a+x+c$，$c+d\ge a+x+c$，所以 $b\ge c+x$，$d\ge a+x$。所以 $b>c\ge d>a$，矛盾。当 $a=b$ 时也易证矛盾。

所以，树不存在两条互不相交的直径。我们还可以证明如果有多条直径，则对于每一条直径，必然有一条其他直径与它在一个端点相交。

于是我们可以找出一条直径 $x\to y$，算出所有的 $\operatorname{dis}(i,x)$ 和 $\operatorname{dis}(i,y)$，如果有 $\operatorname{dis}(i,x)=\operatorname{dis}(x,y)$ 或 $\operatorname{dis}(i,y)=\text{dis}(x,y)$（$i\ne x,i\ne y$）则直径不唯一。

直径不唯一时答案也不一定为 $-1$。当所有直径有同一个端点（具体为上述两种情况仅满足一个），设为 $x$，并且所有点到 $x$ 距离都大于到另一个端点的距离，并且 $k=1$ 的时候，答案不为 $-1$，其余情况都为 $-1$。

考虑找出一条直径，枚举转折点 $i$，找出 $i$ 子树内 $dis(i,k)$ 最大的两个 $k$，则直径为 $\max(\text{dis}(i,k_1)+\text{dis}(i,k_2))$，树形 $\text{dp}$ 即可。

- 直径唯一

则此类情况下，答案为 $-1$ 当且仅当有一个点 $i$ 到直径两端距离相等。

接下来考虑 $k>1$ 的情况。

依然考虑以上算法，考虑一次操作后树为两个点分别挂着一堆点（分别将两个点集记为 $S_x,S_y$）。令 $S_x$ 中与 $x$ 相连边最长的点为 $m_x$，$m_y$ 同理。考虑由于 $x\to y$ 的边权为此时树中的最大边权，此时树的直径为 $m_x\to m_y$，则 $S_x$ 中的点经历这次操作都会连到 $m_y$，且边权为原来的加上 $v_{x\to y}+v_{y\to m_y}$，$S_y$ 中的点同理。新树中 $v_{m_x\to m_y}$ 等于旧树中 $v_{x\to y}+v_{x\to m_x}+v_{y\to m_y}$。

考虑边权的增长是指数级的，我们不能直接维护，必须在模 $2^{32}$ 意义下维护相对顺序。考虑拿两个队列 $q_1,q_2$ 维护 $S_x,S_y$ 中 $v_{x\to p}$ 的相对顺序。考虑一次操作后先得出 $q_1,q_2$ 并进行排序。考虑一次操作，我们会取出两边的最大值并将其置为零，将其余的整体加上一个正数，并将 $x$ 加入队列。考虑维护整体加的 $tag$，由于 $x$ 原先是最小值 $0$，我们将 $-tag$ 加入最后即可。

再考虑判 $-1$：

- 直径不唯一

即 $S_x$ 或 $S_y$ 中前两大值相等。不能直接判断，因为我们的边权是在模 $2^{32}$ 下考虑的。但是我们考虑一次操作后只会取 $k-1$ 次，我们只需要在一次操作后的 $S_x$ 和 $S_y$ 中判断 $i\in[1,\min(n,k-1)]$ 中是否 $q_{o,i}=q_{o,i+1}$ 即可，需要注意，当 $S_x$ 与 $S_y$ 有一个空的时候不应判断这种情况，因为此时直径不唯一但有同一端点。

或者你加个哈希也可以。

这个情况是答案必然为 $-1$ 的。

- 直径唯一

不可能有任何一个点到新直径两端距离相等，因为旧直径是旧的树中边权最大的。

综上，我们做到了 $O(n\log n+k)$ 的复杂度。瓶颈是排序。

代码细节比较多，就贴上来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned 
namespace IO{//by cyffff
	
}
const int N=1e6+10;
int n,k,head[N],cnt;
struct Edge{
	int to,nxt,w;
}a[N<<1];
inline void add(int u,int v,int w){
	cnt++;
	a[cnt].to=v;
	a[cnt].nxt=head[u];
	a[cnt].w=w;
	head[u]=cnt;
}
int s,t;
ll mx,dep[N][2],dis;
inline void dfs(int x,int fa,int tp){
	if(!fa) dep[x][tp]=0;
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa) continue;
		dep[t][tp]=dep[x][tp]+a[i].w;
		dfs(t,x,tp);
	}
}
vector<ll>s1,s2;
queue<ui>d1,d2;
ui tag1,tag2,di,ans;
/*
7 1
1 1
2 2
1 4
2 4
4 4
5 4
*/
int main(){
//	freopen("16.in","r",stdin);
	n=read(),k=read();
	for(int i=2;i<=n;i++){
		int f=i-read(),w=read();
		add(f,i,w),add(i,f,w);
	}
	dfs(1,0,0);
	for(int i=1;i<=n;i++)
		if(dep[i][0]>mx) mx=dep[i][0],s=i;
	dfs(s,0,0);
	for(int i=1;i<=n;i++)
		if(dep[i][0]>dis) dis=dep[i][0],t=i;
	dfs(t,0,1);
	bool fl1=0,fl2=0;
	for(int i=1;i<=n;i++){
		if(i==s||i==t) continue;
		if(dep[i][0]==dep[t][0]) fl1=1;
		if(dep[i][1]==dep[s][1]) fl2=1;
	}
	if(fl1&&fl2) return puts("-1"),0;
	if((fl1||fl2)&&k>1) return puts("-1"),0;
	if(fl1){
		for(int i=1;i<=n;i++){
			if(i==s||i==t) continue;
			if(dep[i][0]<dep[i][1]) return puts("-1"),0;
		}
	}
	if(fl2){
		for(int i=1;i<=n;i++){
			if(i==s||i==t) continue;
			if(dep[i][0]>dep[i][1]) return puts("-1"),0;
		}
	}
	for(int i=1;i<=n;i++){
		if(i==s||i==t) continue;
		if(dep[i][0]==dep[i][1]) return puts("-1"),0;
		if(dep[i][0]>dep[i][1]) s1.push_back(dep[i][0]);
		else s2.push_back(dep[i][1]);
	}
	sort(s1.begin(),s1.end(),greater<ll>());
	sort(s2.begin(),s2.end(),greater<ll>());
	if(s1.size()&&s2.size()){
    	for(int i=0;i+1<s1.size()&&i<min(n,k-1);i++)
    		if(s1[i]==s1[i+1]) return puts("-1"),0;
    	for(int i=0;i+1<s2.size()&&i<min(n,k-1);i++)
    		if(s2[i]==s2[i+1]) return puts("-1"),0;
	}
	for(auto x:s1) d1.push((ui)x);//,printf("%d ",x);puts("");
	for(auto x:s2) d2.push((ui)x);//,printf("%d ",x);puts("");
	di=dis;
	for(int i=2;i<=k;i++){
		ui x=0,y=0;
		bool fl1=0,fl2=0;
		if(!d1.empty()) x=d1.front()+tag1,d1.pop(),fl1=1;
		if(!d2.empty()) y=d2.front()+tag2,d2.pop(),fl2=1;
		if(fl1) d1.push(-tag1),tag1+=y+di;
		if(fl2) d2.push(-tag2),tag2+=x+di;
		di+=x+y;
//		printf("%d %d %d %d %d\n",x,y,tag1,tag2,di);
	}
	while(!d1.empty()) ans+=d1.front()+tag1,d1.pop();
	while(!d2.empty()) ans+=d2.front()+tag2,d2.pop();
	ans+=di;
	write(ans);
	flush();
}
```

---

## 作者：_shy (赞：1)

## [P8934 [JRKSJ R7] TSM eerT](https://www.luogu.com.cn/problem/P8934)
### 思路
1. **树的直径**一定是 $f(T_0)$ 上的权值最大边，思考 $f(T_0)$ 上的其他边的权值与这条直径的关系。构建一个简单的树（其中 $0\to 1\to2\to3\to4$ 是直径）。

![在这里插入图片描述](https://img-blog.csdnimg.cn/85944bd4bac44e009b8d3a98a53577ff.png#pic_center)

我们求点 $7$ 到其他点的最远距离。首先，类似于 $7\to6\to1\to5$ 的路径的长度**一定不大于** $7\to6\to1\to0$ 这条路径的长度，因为 $1\to0$ 的长度一定不小于  $1\to5$ 的长度。同理可得，类似于 $7\to6\to1\to2\to8\to9$ 的路径的长度**一定不大于** $7\to6\to1\to2\to3\to4$ 这条路径的长度。由于点 $7$ 的任意性，可知以任意一点（除直径端点外）为起点，**最远路径的终点一定是两个直径端点中的某一个**，路径长度等于其到直径上的距离加上，直径上的那点到两端点距离的较大值。于是我们可以得到 $f(T_0)$ 的结构了：直径的端点分别挂着一堆非端点，类似于下图的结构（$1$、$2$ 为原直径端点，其他点为非端点）。

![在这里插入图片描述](https://img-blog.csdnimg.cn/2319caaddf094144b3b14de632169a9c.png#pic_center)

2. 思考 $f(T_0)$ 不唯一的原因。首先，**直径可能不唯一**，从上文的 $1\to0$ 的长度一定不小于  $1\to5$ 的长度可推得。我们可以用 $maxl$ 记录直径上的某一点向外延伸的最大距离，若 $maxl$ 等于这一点到两端点距离中的任意一个，则令 $flag$ 为 $1$。但是直径不唯一**不一定**使得 $f(T_0)$ 不唯一：当**存在一个直径端点下没有挂点**时，直径不唯一并不会导致 $f(T_0)$ 不唯一。也就是说，$flag=1$ 且两个端点下面都挂着点的时候，$f(T_0)$ 不唯一。其次，**树的直径上可能存在到两个端点距离相等的点**，判断一下即可。
3. 思考 $f^{2}(T_0)$ 的构造，以如下图作为 $f(T_0)$。

![在这里插入图片描述](https://img-blog.csdnimg.cn/2319caaddf094144b3b14de632169a9c.png#pic_center)

点 $1$ 与点 $2$ 之间的距离即原直径记为 $fm$。假设点 $3$ 是左边挂着的三个点中到点 $2$ 的边权最大（记此边权为 $lm$）的点，点 $7$ 是右边挂着的两个点中到点 $1$ 的边权最大(记此边权为 $rm$)的点。于是左边挂着的点（除点 $3$ 外），其最远距离更新为**边权加 $fm$ 加 $rm$**，其中的最大值是 $f^2(T_0)$ 中的 $lm$；右边挂着的点（除点 $7$ 外），其最远距离更新为**边权加 $fm$ 加 $lm$**，其中的最大值是 $f^2(T_0)$ 中的 $rm$。点 $3$ 到点 $7$ 的距离更新为 $fm+rm+lm$，是 $f^2(T_0)$ 中的 $fm$。点 $2$ 到其他点的最远距离更新为 $fm+rm$，点 $1$ 到其他点的最远距离更新为 $fm+lm$，分别进入“左堆”和“右堆”，各自作为其中的**最小值**。这时，点 $3$ 与点 $7$ 成为了新的直径端点，故他们分别从“左堆”和“右堆”出来。故我们需要用**双端队列**分别模拟存储存储两边的那一堆点，即左堆和右堆，并将其中的点按大到小的方式排序。但是更新的时候不能逐个加值，我们需要**维护加法懒标记**。
4. 思考 $f^2(T_0)$ 不唯一的原因。**直径不唯一仍有可能**，但**直径上不可能存在到两边的距离相等的点**。于是我们只需要判断第一种情况，即左（或右）边的一堆点达到 $lm$ 或 $rm$ 的点不唯一，且两个直径端点都挂着点。
5. 易得，$f^n(T_0),n\geq1$ 的结构与 $f(T_0)$ 的构造类似，故重复上述操作 $3$ 与 $4$ 即可。
6. 时间复杂度为 $\mathcal O(n\log n + k)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;
const unsigned long long MOD = 4294967296;
int n, k;
int head[maxn], cnt;
struct edge 
{
	int v, w, next;
} e[maxn << 1];
void add (int u, int v, int w) 
{
	e[++ cnt] = (edge) {v, w, head[u]};
	head[u] = cnt;
}
unsigned long long tree_d, dis[maxn], maxl;
int last_point, start_point, f[maxn]; 
void dfs (int u, int fa, int tp) 
{
	if (tp == 1) f[u] = fa;
	if (dis[u] > tree_d) tree_d = dis[u], last_point = u;
	for (int i = head[u]; i; i = e[i].next) 
	{
		int v = e[i].v, w = e[i].w;
		if (v == fa) continue;
		dis[v] = (dis[u] + 1ll * w); 
		dfs (v, u, tp);
	}
}
deque <unsigned long long> qu[2];
bool vis[maxn];
unsigned long long q[maxn], qi[maxn], lm, rm, fm, tag[2];
int p, pi;
bool cmp (unsigned long long a, unsigned long long b) {return a > b;} 
void dfsi (int u, int fa, unsigned long long d, int tp) 
{
	if (tp == 1) q[++ p] = d;
	else qi[++ pi] = d;
	if (maxl < d) maxl = d;
	for (int i = head[u]; i; i = e[i].next) 
	{
		int v = e[i].v, w = e[i].w;
		if (vis[v] || v == fa) continue;
		dfsi (v, u, (d + 1ll * w), tp);
	}
} 
int main ()
{
	scanf ("%d %d", &n, &k);
	for (int i = 2; i <= n; i++) 
	{
		int v, w;
		scanf ("%d %d", &v, &w); v = i - v;
		add (i, v, w), add (v, i, w);
	}
	dfs (1, 0, 0);
	start_point = last_point;
	memset (dis, 0, sizeof (dis));
	tree_d = last_point = 0;
	dfs (start_point, 0, 1);
	int cur_point = last_point, flagi = 0;
	while (cur_point != 0) 
		vis[cur_point] = 1, cur_point = f[cur_point]; 
	fm = tree_d;
	cur_point = f[last_point];
	while (cur_point != start_point) 
	{
		int flag = dis[cur_point] > tree_d - dis[cur_point] ? 1 : 0;
		unsigned long long cur_d = max (dis[cur_point], tree_d - dis[cur_point]);
		if (dis[cur_point] == tree_d - dis[cur_point]) printf ("-1"), exit (0);
		maxl = 0, dfsi (cur_point, f[cur_point], cur_d, flag);
		if (maxl == dis[cur_point] + cur_d || maxl == tree_d - dis[cur_point] + cur_d)
			flagi = 1;
		cur_point = f[cur_point];
	}
	if (flagi && p != 0 && pi != 0) printf ("-1"), exit (0);
	sort (q + 1, q + p + 1, cmp), sort (qi + 1, qi + pi + 1, cmp);
	for (int i = 1; i <= p; i++) qu[0].push_back (q[i]);
	for (int i = 1; i <= pi; i++) qu[1].push_back (qi[i]);
	bool pd = qu[0].empty (), pdi = qu[1].empty ();
	for (int i = 1; i < k; i++) 
	{
		lm = pd ? 0 : tag[0] + qu[0].front (), 
		rm = pdi ? 0 : tag[1] + qu[1].front ();
		if (!pd) qu[0].pop_front (), qu[0].push_back (-tag[0]);
		if (!pdi) qu[1].pop_front (), qu[1].push_back (-tag[1]);
		if (p != 0 && pi != 0 && (lm == qu[0].front () + tag[0] || rm == qu[1].front () + tag[1]))
			printf ("-1"), exit (0);
		tag[0] += rm + fm, tag[1] += lm + fm, fm += lm + rm;
	}
	unsigned long long ans = 0ll;
	for (int i = 0; i <= 1; i++) 
		while (!qu[i].empty ()) 
			ans += qu[i].front () + tag[i], qu[i].pop_front ();
	printf ("%u", (ans + fm) % MOD); 
	return 0;
}


```

---

