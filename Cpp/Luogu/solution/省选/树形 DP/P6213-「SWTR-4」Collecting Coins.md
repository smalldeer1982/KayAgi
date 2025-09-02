# 「SWTR-4」Collecting Coins

## 题目背景

小 A 喜欢 Collecting Coins。他还有个好朋友叫做小 c。

小 c 在外出游玩的时候被困在了一个迷宫里面，小 A 得知消息后，立刻放下了自己手中正在打的树套树套树套树，出发去营救她。

## 题目描述

经过一番勘察，小 A 发现小 c 被困的迷宫由 $n$ 个房间组成，这些房间用 $n-1$ 扇门连接，**形成了一颗树**。小 c 被困在 $d$ 号房间。

小 A 还发现每扇门上都写有一个数字 $v$，经过该扇门就会获得 $v$ 个金币，但每扇门上的金币只能获得一次。

由于把小 c 困在迷宫里的坏人早已知道小 A 会来救她，所以他们在每个房间里都布下了陷阱，使得第 $i$ 个房间最多可以进入 $k_i$ 次，否则小 A 也会被困在迷宫里。Luckily，小 c 在向小 A 求救的时候，已经将这个陷阱告诉了他。

小 A 在进入迷宫的时候可以任选初始房间 $r$（进入迷宫算一次进入房间 $r$）。**小 A 可以离开迷宫，当且仅当他在房间 $r$。**

如果小 A 进入了 $d$ 号房间，我们就认为他成功地救下了小 c。在救下小 c 后，小 A 还可以带着她继续在迷宫中行动。

虽然小 A 并不是一个非常贪财的人，但还是想知道：在**成功救下小 c** 且离开迷宫的前提下，他最多能获得多少金币。

## 说明/提示

【样例 $1$ 说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/zwtjgksh.png)

一种最优的走法为：$2\to 4\to 2$，共可获得 $5$ 金币。

【样例 $2$ 说明】

如上图，小 A 只能空降到 $4$ 号房间，然后再离开迷宫，共可获得 $0$ 金币。

【样例 $4$ 说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/fmd43hzq.png)

一种最优的走法为：$3\to 9\to 10\to 8\to 10\to 12\to 6\to 12\to 10\to 9\to 3$，共可获得 $100+59+65+9+30=263$ 金币。

【数据范围与约定】

**本题使用捆绑测试。**

Subtask 编号 | $n\leq$ | 特殊性质 | 分值 |
:-: | :-: | :-: | :-: |
$1$ | $12$ | $k_i=1$ | $3$ |
$2$ | $12$ | $k_i\leq 3$ | $12$ |
$3$ | $10^3$ | 迷宫为一条链 | $9$ |
$4$ | $10^3$ | 无 | $16$ |
$5$ | $10^5$ | 迷宫为一条链 | $9$ |
$6$ | $10^5$ | 迷宫为一个菊花图 | $16$ |
$7$ | $10^5$ | 无 | $35$ |

对于 $100\%$ 的数据，$1\leq d,k_i\leq n\leq 10^5$，$1\leq v_i\leq 10^4$。

【Source】

[Sweet Round 04](https://www.luogu.com.cn/contest/26414)$\ \ $E

idea & std：[Alex_Wei](https://www.luogu.com.cn/user/123294)，验题：[chenxia25](https://www.luogu.com.cn/user/138400)

## 样例 #1

### 输入

```
6 4
1 2 3
2 3 4
2 4 5
3 5 2
3 6 3
1 2 1 1 2 2
```

### 输出

```
5```

## 样例 #2

### 输入

```
6 4
1 2 3
2 3 4
2 4 5
3 5 2
3 6 3
1 1 1 1 1 1
```

### 输出

```
0```

## 样例 #3

### 输入

```
6 4
1 2 3
2 3 4
2 4 5
3 5 2
3 6 3
2 2 2 2 2 2
```

### 输出

```
12```

## 样例 #4

### 输入

```
12 6
1 4 33
2 11 51
3 9 100
4 8 7
5 9 35
6 12 30
7 11 58
8 10 65
9 10 59
10 12 9
11 12 72
2 2 2 3 2 1 2 1 2 3 2 2
```

### 输出

```
263```

# 题解

## 作者：z7z_Eta (赞：9)

> preface.

#### 做法使用了树形dp一次dfs, 对 *BeyondHeaven* 的题解做了一定的简析与补充

----

> 提取题意.

* 选择一个$d$的**联通子树**(连通块), 并且选择一个点作入口. $d$ 是小 c 所在的结点.
* 入口 $r$ 满足 $deg_r \le k_r-1$ ; 其他点 $v$ 满足 $deg_v \le k_v$ .
* 求所有联通子树内的边权值和的最大价值.

官方题解的做法是令 $r$ 做根, 用换根dp解决问题

然而比赛时发现了一种更通用的做法, 直接将入口 $r$ 作为**新的一维**

* 我们以$d$为根, 状态记做$f[u][0/1]$
* 其中$f[u][0]$表示$u$子树中没有选择$r$的最大价值, $f[u][1]$则表示$u$子树中已选$r$

这样就保证了$d$在联通块内, 并且$r$被选到

于是, 题目变成了提高组dp

> 转移方程.

$f[u][0] = \text{前}k[u]-1\text{大的}\{f[v][0]+val_{(u,v)}\}$

$f[u][1] = \begin{cases} 1.\text{前}k[u]-2\text{大的}\{f[v][0]+val_{(u,v)}\}\\ 2.\max_{x} \{ f[x][1]+val_{(u,x)}+\text{除}x\text{之外前}k[u]-2\text{大的}\{f[v][0]+val_{(u,v)}\}\} \end{cases} $

($2.$) 转移$2.$本质是枚举了$x$中出现了入口$r$

注意当$k[u]=1$时, $f[u][1] = -\inf$, 因为没有可选的儿子

因为$d$是根, $k[d]$需要先$+1$

所求即为$f[d][1]$

> else.

由于排序, 复杂度 $O(n \log n)$

在 *BeyondHeaven* 的题解中, $f[u][1]$的转移没有考虑$k[u]-1$之外的, 所以有些瑕疵

## code:

```
// Etavioxy
#define il inline
#define ll long long
#define rep(i,s,t) for(register int i=(s);i<=(t);i++)
#define rev_rep(i,s,t) for(register int i=(s);i>=(t);i--)
#define each(i,u) for(int i=head[u];i;i=bow[i].nxt)
#define pt(x) putchar(x)
using namespace std;
il int ci(){
	register char ch;int f=1;
	while(!isdigit(ch=getchar()))f=ch=='-'?-1:1;
	register int x=ch^'0';
	while(isdigit(ch=getchar()))x=(x*10)+(ch^'0');
	return f*x;
}

enum{N=100023};

struct Edge{ int nxt,to,val; } bow[N*2];
int head[N],tot_e;
il void add(int x,int y,int z){
	tot_e++;
	bow[tot_e<<1]=(Edge){head[x],y,z};
	bow[tot_e<<1|1]=(Edge){head[y],x,z};
	head[y]=(head[x]=tot_e<<1)|1;
}

int k[N];
int val[N],f[N][2];
bool cmp1(int x,int y){
	return f[x][0]+val[x] > f[y][0]+val[y];
}
void dfs(int u,int fa){
	if( k[u]==0 ){
		f[u][1] = -1e9;
		f[u][0] = 0;
		return ;
	}
	f[u][1] = f[u][0] = 0;
	vector<int>vec;
	each(i,u){
		int v = bow[i].to;
		if( v==fa ) continue;
		dfs(v,u);
		val[v] = bow[i].val;
		vec.push_back(v);
	}
	sort(vec.begin(),vec.end(),cmp1);
	bool flag=0;
	if( k[u]>(int)vec.size() ){ flag = 1; k[u] = vec.size(); }
	rep(i,0,k[u]-1) f[u][0] += f[vec[i]][0]+val[vec[i]];
	if( flag ) return f[u][1] = f[u][0], void();
	int kth = vec[k[u]-1];
	f[u][1] = f[u][0] - f[kth][0] - val[kth];
	rep(i,0,(int)vec.size()-1){
		if( i<=k[u]-1 ) f[u][1] = max(f[u][1],f[vec[i]][1]+f[u][0]-f[vec[i]][0]);
		else f[u][1] = max(f[u][1],f[vec[i]][1]+val[vec[i]]+f[u][0]-f[kth][0]-val[kth]);
	}
//	printf("LINE : %d u %d f %d %d\n",__LINE__,u,f[u][0],f[u][1]);
}

int main(){
	int n = ci(), d = ci();
	rep(i,1,n-1){
		int x = ci(), y = ci();
		add(x,y,ci());
	}
	rep(i,1,n) k[i] = ci()-1;
	k[d]++;
	dfs(d,0);
	printf("%d\n",f[d][1]);
	return 0;
}
```

这道题超优美的

~~但是Eta太蠢了太蠢了太蠢了~~

---

## 作者：Alex_Wei (赞：7)

$$\mathsf{Preface}$$

[题面传送门](https://www.luogu.com.cn/problem/P6213)

本题灵感来源：曾经的某次 CF 的错解。

---

$$\mathsf{Solution}$$

Subtask $1$：$k_i=1$。每个房间只能进入 $1$ 次，显然输出 $0$。

Subtask $2$：$k_i\leq 3$。爆搜即可。

**送分结束。**

Subtask $3$：一条链，$n\leq 10^3$。乱搞，挖掘性质，略。

---

Subtask $4$：$n\leq 10^3$，显然爆搜的方法行不通。

前置知识：树形 DP。**不会树形 DP 就别往下看了。**

我们知道，小 A 的路径肯定是一棵树的形态，下文我们简称为**路径树**。下图即样例 $5$ 的路径树，路径在样例解释中已给出。

除了**出发点 $3$**，我们称**其余在路径上的节点 $9,10,8,12,6$ **为**路径节点。**

![](https://cdn.luogu.com.cn/upload/image_hosting/u8aibsns.png)

我们假设 $l_i$ 为点 $i$ 在**路径树**上的度数。这样有一个显然的性质：出发点满足 $l_i<k_i$，路径节点满足 $l_i\leq k_i$。

- 如果把所有边看成有向边，那么除了一开始进入房间，走向每个节点都会使该节点的度数 $+1$，感性理解一下即可。

1. 我们定义**到达点** $i$ 为 **在度数限制下**能到达 $d$ 的点，即路径 $i\to d$ 上所有点 $j$ 曼度 $k_j\ge2$（除了 $k_d$ 可以为 $1$）。例如 $10$ 就是一个到达点，而 $4$ 不是（$k_8=1<2$）。可以通过一遍 DFS $O(n)$ 求出一个点是不是到达点。当然，在 $n\leq 10^3$ 的限制下，你也可以 $O(n^2)$ 求。
    
2. 我们定义**到达边** $u\to v$ 为 **除去度数限制**，从 $v$ 不经过 $v\to u$ 能到达 $d$ 的边。例如 $11\to 12$ 就是一个到达边，而 $12\to 10$ 不是。可以通过一遍 DFS $O(n)$ 给所有到达边打上标记。当然，在 $n\leq 10^3$ 的限制下，你也可以 $O(n^2)$ 求。

3. 这样就可以愉快地开始树形 DP 了。因为题目没有指定根的位置（任选初始房间），所以要把每个**到达点**都当成根试一遍，求出最大值。

   我们设 $f_i$ 为以 $i$ 为根的子树选出的路径树的最大值。我们把边按照：到达边优先，都不是到达边按照 $f_x+v(i,x)$ 从大到小排序。选出前 $k_i-1$ 个儿子，$f_i\gets f_i+f_x+v(i,x)$。
     
   - 如果 $i$ 为根，那么本来就应该选 $k_i-1$ 个儿子。
   
   - 如果 $i$ 不为根，那么因为其父节点选择 $i$ 的时候仍要花去 $1$ 度数，所以也应选 $k_i-1$ 个儿子。

定义：

```cpp
const int N=1e5+5;//其实应该是1e3+5
struct edge{int to,val,pa;};
vector <edge> e[N];
int n,d,k[N],a[N];
```

求到达边的代码，$O(n)$：

```cpp
void path(int id,int f){
	for(int i=0;i<e[id].size();i++){
		edge &p=e[id][i];
		if(p.to!=f)p.pa=0,path(p.to,id);
	}
}
......
path(d,0);
```

求到达点的代码，$O(n)$：

```cpp
void avail(int id,int f){
	a[id]=1;
	for(int i=0;i<e[id].size();i++){
		int to=e[id][i].to;
		if(to!=f&&(id==d||k[id]>=2))avail(to,id);
	}
}
......
avail(d,0);
```

排序规则：

```cpp
int dp[N];
bool cmp(edge x,edge y){
	if(x.pa)return 1; if(y.pa)return 0;
	return dp[x.to]+x.val>dp[y.to]+y.val;
}
```
部分 DP 代码，$O(n\log n)$：

```cpp
void dfs1(int id,int f){
	for(int i=0;i<e[id].size();i++){
		int to=e[id][i].to;
		if(to!=f)dfs1(to,id);
	}
	sort(e[id].begin(),e[id].end(),cmp);
	int deg=k[id]-1;
	for(int i=0;i<e[id].size();i++){
		if(!deg)break;
		edge p=e[id][i];
		int to=p.to; int v=dp[to]+p.val;
		if(to==f)continue;
		deg--;
		dp[id]+=v;
	}
}
```
   
每次 DP 结束后更新答案，一次 DP 时间复杂度 $O(n\log n)$，总时间复杂度 $O(n^2\log n)$。

---

Subtask $5$：一条链，$n\leq 10^5$。挖掘性质，略。

Subtask $6$：一条菊花，$n\leq 10^5$。挖掘性质，略。

---

Subtask $7$：$n\leq 10^5$。显然，挖掘性质不再管用了。~~所以略也不管用了。~~ 省略如何求出到达边及到达点。

前置知识：二次扫描与换根法，简称换根 DP。**不会换根 DP 就别往下看了。**

题目没有给出根的位置，显然是换根 DP 的一大特征。~~如果会换根 DP 还想不到的话，AFO 罢，孩子。~~

方便起见，我们假定 $1$ 为树根（其实 $[1,n]$ 中的任意一个整数都可以）。

1. 第一遍 DP：

   定义 $nxt_i$ 为 按照前文给出的排序规则排序，$i$ 的第 $k_i$ 个儿子的权值，权值即 $f_x+v(x,i)$，如果没有则为 $0$。在 DP 时同 $f_i$ 一起求出。
   
2. 第二遍 DP：

   定义 $g_i$ 为以 $i$ 为树根的答案，显然 $g_1=f_1$。定义 $S_i$ 为计算 $g_i$ 时选择的节点编号，显然 $|S_i|<k_i$，且在求 $f_1$ 时可以求出 $S_1$。现在我们考虑如何转移出别的 $g_i$。
   
   情况 $1$：$i\in S_{y}$，其中 $y$ 为 $i$ 的父亲。此时 $f_y=g_y+nxt_y-f_i-v(y,i)$。想想看，计算 $g_y$ 已经选出了 $|S_y|$ 个儿子，现在其中的一个儿子成了 $y$ 的父亲，那么就应该去掉 $i$ 对 $y$ 的贡献，选第 $|S_y|+1$ 个儿子。
   
   情况 $2$：$i\notin S_y$，显然 $f_y=g_y$，原因不再赘述，请读者自行思考。

   用 set 维护 $S$ 数组即可，时间复杂度 $O(n\log n)$。

答案即为 $\max_{i\in V}g_i$，其中 $V$ 为到达点集合。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,sign=0; char s=getchar();
	while(!isdigit(s))sign|=s=='-',s=getchar();
	while(isdigit(s))x=(x<<1)+(x<<3)+(s-'0'),s=getchar();
	return sign?-x:x;
}
const int N=1e5+5;
struct edge {int to,val,pa;};
vector <edge> e[N];
int n,d,k[N],a[N];
void path(int id,int fa){
	for(int i=0;i<e[id].size();i++){
		edge &p=e[id][i];
		if(p.to!=fa)p.pa=0,path(p.to,id);
	}
}
void avail(int id,int fa){
	a[id]=1;
	for(int i=0;i<e[id].size();i++){
		int to=e[id][i].to;
		if(to!=fa&&(id==d||k[id]>=2))avail(to,id);
	}
}
int f[N],g[N],nxt[N];
set <int> S[N];
bool cmp(edge x,edge y){
	if(x.pa)return 1; if(y.pa)return 0;
	return f[x.to]+x.val>f[y.to]+y.val;
}
void dfs1(int id,int fa){
	for(int i=0;i<e[id].size();i++){
		int to=e[id][i].to;
		if(to!=fa)dfs1(to,id);
	}
	sort(e[id].begin(),e[id].end(),cmp);
	int deg=k[id]-1;
	for(int i=0;i<e[id].size();i++){
		edge p=e[id][i];
		int to=p.to; int v=f[to]+p.val;
		if(to==fa)continue;
		if(--deg==-1){nxt[id]=v; break;}
		f[id]+=v;
		if(id==1)S[id].insert(to);
	}
}
void dfs2(int id,int fa,int val){
	if(id!=1){
		if(S[fa].count(id))f[fa]=g[fa]+nxt[fa]-f[id]-val;
		else f[fa]=g[fa];
		sort(e[id].begin(),e[id].end(),cmp);
		int deg=k[id]-1;
		for(int i=0;i<e[id].size();i++){
			edge p=e[id][i];
			int to=p.to; int v=f[to]+p.val;
			if(--deg==-1){nxt[id]=v; break;}
			g[id]+=v,S[id].insert(to);
		}
	}
	for(int i=0;i<e[id].size();i++){
		edge p=e[id][i];
		if(p.to!=fa)dfs2(p.to,id,p.val);
	}
}
int main(){
	n=read(),d=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		e[u].push_back({v,w,1}),e[v].push_back({u,w,1});
	}
	for(int i=1;i<=n;i++)k[i]=read();
	path(d,0),avail(d,0);
	dfs1(1,0),g[1]=f[1],dfs2(1,0,0);
	int ans=0;
	for(int i=1;i<=n;i++)if(a[i])ans=max(ans,g[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

$$\mathsf{Conclusion}$$

因为某次 CodeForces 一个简单题想复杂了而得到的 idea，应该是一道难度适中的换根 DP。**希望大家能通过本题对换根 DP 的理解更深一步。**

~~没有根的树形 DP 不是好换根 DP。~~

- Upd on 2020.3.13：比赛的时候一些神仙只用了 $1$ 次 DFS 的树形 DP。代码，常数都碾压正解，也没有正解这么麻烦，orz！

码字不易，点个赞呗 qwq。另外，发现错误记得私信我哈，bye ~

---

## 作者：BeyondHeaven (赞：6)


给一个一次Dfs的做法

我们记一个连通块的根为这个连通块中深度最小的节点。

题目相当于，求一个边权和最大的包含$d$的连通块，使得对这个连通块中的一个特定点的$k$值$-1$后，满足每个点$x$的度数不超过$k[x]$。($-1$相当于把这个节点作为起始点)

首先把$d$作为树根，然后令$k[d]\leftarrow k[d]+1$。(只是为了方便计算)

对一个节点$u$，设$f[u]$表示满足每个点$v$的度数不超过$k[v]$且$u$的度数不超过$k[u]-1$的包含$u$的连通块的最大边权和，$g[u]$表示满足对这个连通块中的一个特定点的$k$值$-1$后满足每个点$v$的度数不超过$k[v]$且$u$的度数不超过$k[u]-1$的包含$u$的连通块的最大边权和。

递推式为：

$f[u]=\{$前$k[u]-1$大的$f[v]$之和$|v\in \operatorname{son}(u)\}$

$g[u]=\max(f[u]-\min\{f[v]-g[v]|v\in \operatorname{son}(u)\},\{$前$k[u]-2$大的$f[v]$之和$|v\in \operatorname{son}(u)\})$

所求即为$g[d]$，注意当$k[u]=1$时$g[u]$不存在。

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define MaxN 100123
struct Edge{int v,w,next;}edge[MaxN<<1];
int head[MaxN],num_edge;
inline void add_edge(int u,int v,int w)
{
	edge[++num_edge].v=v;
	edge[num_edge].w=w;
	edge[num_edge].next=head[u];
	head[u]=num_edge;
}
int n,d;
int k[MaxN];
inline void Init()
{
	scanf("%d%d",&n,&d);
	for(int i=1,u,v,w;i<n;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(int i=1;i<=n;++i)
	scanf("%d",k+i);
	++k[d];
}
int path[MaxN];
int f[MaxN],g[MaxN];
inline void Dfs(int u,int fa,int val)
{
	path[u]=val;
	if(k[u]==1){f[u]=0;g[u]=-0x3f3f3f3f;return;}
	std::vector<int>sons;
	for(int i=head[u];i;i=edge[i].next)
	if(edge[i].v!=fa)
	{
		Dfs(edge[i].v,u,edge[i].w);
		sons.push_back(edge[i].v);
	}
	auto cmp=[](int a,int b){return f[a]+path[a]>f[b]+path[b];};
	std::sort(sons.begin(),sons.end(),cmp);
	for(int i=0;i<k[u]-1&&i<sons.size();++i)
	f[u]+=f[sons[i]]+path[sons[i]];
	if(k[u]-1>sons.size())g[u]=f[u];
	else
	{
		int dec=f[sons[k[u]-2]]+path[sons[k[u]-2]];
		for(int i=0;i<k[u]-1;++i)
		dec=std::min(dec,f[sons[i]]-g[sons[i]]);
		g[u]=f[u]-dec;
	}
}
int main()
{
	Init();
	Dfs(d,0,0);
	printf("%d\n",g[d]);
	return 0;
}
```



---

## 作者：Night_sea_64 (赞：4)

### 一个结论

先抛开题目。对于一棵有根树，如果我们需要走到它的所有点并且回到根。要使进入每个点的次数最小，那么我们从它的父亲结点进来，就一口气把它的子树都走完，然后再回到它的父亲结点。

按照上面的方法，进入一个点所需要的最少次数就**取决于它的度数**。因为我们从一个点连向的每一条边都要进入它，不管是从它的父亲结点进来还是从它的子结点回来。

---

### 本题做法

我们把上面的结论放到这道题。在这道题中，初始房间 $r$ 就是根。如果一个点不是根，进入它所需要的最少次数就是它的度数。如果该结点是根，进入它所需要的最少次数就是它的度数 $+1$（因为题目中进入迷宫算进入一次房间 $r$）。

由此可得，除了根结点比较特殊，其它的点的进入次数**与遍历的顺序无关**。那么现在我们的任务就只用 dp 选择原树的一部分给小 A 走，再找一个能当初始房间的结点当根就好了。

但是还没完，这题还有一个条件：必须经过房间 $d$。略加思考我们就可以直接把 $d$ 钦定为 **dp 过程**的根（不是初始房间）。这样的好处就是，如果一个子结点选了，它的父亲结点也必须选；如果一个父亲结点没选，它的子结点也必须不选。

好了，现在我们就只剩下初始房间的问题了。因为初始房间不一定是 $d$（样例 $1$ 就能说明这一点），所以我们必须在选出来的部分中找能当初始房间的点。

考虑到一点就是，初始房间的限制次数**不能用完**。因为进入整棵树算作进入一次初始房间，而在正常算的过程中因为还不知道它是初始房间，所以这一次不会算进去。

一个点作为初始房间，只用满足上面一个条件即可。那我们在 dp 过程中，dp 数组一定会开一维表示当前是那个点。但是因为还有初始房间的问题，所以在我的方法中，只有一维很难解决。我的做法就是**再开一维**，表示当前点及其子树中，**有没有能当作初始房间的点被选出**（我是用 $1$ 表示有，$0$ 表示不一定有而不是绝对没有）。数组大小变为原来的 $2$ 倍。

显然这样设计状态之后，答案为 $f_{d,1}$。假设 $k$ 为第二维的值，考虑如何转移。

#### 1：$k=0$

比较简单。用 $now$ 表示还剩下的限制次数（下同）。因为上面的结论所以最多只能再去 $now$ 个子结点。我们取所有子结点 $k=0$ 的答案中前 $now$ 大的（不够就全取，下同）加一起就好了。

#### 2：$k=1$ 且当前点可以当作初始房间

跟上面类似，因为初始房间要留出来一次，所以最多只能再去 $now-1$ 个子结点。也是取子结点 $k=0$ 的答案。

#### 3：$k=1$ 且当前点不一定可以当作初始房间

这个比较麻烦。因为当前点的子结点中，至少取一个的 $k=1$。而其它的子结点 $k$ 可以为 $0$。这时我们先取 $now$ 个 $k=0$ 的，再枚举一个子结点的 $k=1$。如果该子结点的 $k=0$ 的答案刚刚被取了，就换掉它。否则贪心地换掉 $k=0$ 中最小的答案。

上述过程中需要对子结点 $k=0$ 的答案进行排序。

最后一个小问题就是初值。$k=0$ 的情况初值设为 $0$ 就好了。但是 $k=1$ 的情况初值要设为 $-\inf$，因为如果一个点的 $k=1$ 没有办法做到，正常转移到别的点的时候会正常地从 $0$ 开始加，所以是错的。

整个算法复杂度 $O(n\log n)$。

---

### 参考代码

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,d,a[100010],f[100010][2];
//第一维表示现在的点号
//第二维表示有没有选出一个位置，进入次数 < 限制次数
//0 表示有可能有也可能没有，1 表示有
//记录的是选当前点并且满足第二维的条件的情况下，金币最大值
struct node{int x,y;}b[100010];
bool cmp(const node &x,const node &y){
    return x.x>y.x;
}
struct edge{int x,w;};
vector<edge>v[100010];
void dfs(int x,int last)
{
    for(auto e:v[x])
        if(e.x!=last)
            dfs(e.x,x);
    int now=a[x]-(x!=d),cur=0;
    if(now)
    {
        //第二维为 0
        for(auto e:v[x])
            if(e.x!=last)
                b[++cur]={f[e.x][0]+e.w,f[e.x][1]+e.w};
        sort(b+1,b+cur+1,cmp);
        for(int i=1;i<=min(cur,now);i++)
            f[x][0]+=b[i].x;

        //第二维为 1 并且当前点选出的子节点满足进入次数 < 限制次数
        cur=0;
        int sum1=0,sum2=0;
        for(auto e:v[x])
            if(e.x!=last)
                b[++cur]={f[e.x][0]+e.w,f[e.x][1]+e.w};
        sort(b+1,b+cur+1,cmp);
        for(int i=1;i<=min(cur,now);i++)
            sum1=max(sum1,sum1+b[i].x);
        int maxn=-9e18;
        for(int i=1;i<=cur;i++)
            if(i<=now)maxn=max(maxn,b[i].y-b[i].x);
            else maxn=max(maxn,b[i].y-b[now].x);
        sum1+=maxn;

        //第二维为 1 并且当前点满足进入次数 < 限制次数
        cur=0;
        for(auto e:v[x])
            if(e.x!=last)
                b[++cur]={f[e.x][0]+e.w,f[e.x][1]+e.w};
        sort(b+1,b+cur+1,cmp);
        for(int i=1;i<=min(cur,now-1);i++)
            sum2=max(sum2,sum2+b[i].x);
        f[x][1]+=max(sum1,sum2);
    }
    else f[x][1]=-2e9;
}
signed main()
{
    cin>>n>>d;
    for(int i=1;i<n;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        v[x].push_back({y,w});
        v[y].push_back({x,w});
    }
    for(int i=1;i<=n;i++)cin>>a[i];
    dfs(d,0);
    cout<<f[d][1]<<endl;
    return 0;
}
```

看不懂的话可以私信我。如果我写的有错误也欢迎指出。

---

## 作者：Scarlet_Hypoc (赞：3)

将限制分开考虑。

假设不管到达次数 $k_i$ 和要救小 c 两个条件，只管收集金币，那么不难得到一个简单的dp：设 $f_x$ 表示 $x$ 子树内能收集到的最多的金币，转移为 $f_x=\sum_{y\in son}f_y+w$，$w$ 是边上的金币数。

加上到达次数这个限制，由于这个点要么从父亲那走过来，要么作为起点，无论如何到达次数都要减一，那么每次取前 $a_x-1$ 大的儿子即可，按 $f_y+w$ 进行排序。

然后进行简单的换根dp，每次将父亲那棵子树也考虑进这 $a_x-1$ 个里面就好了。

最后加上救小 c 的限制，这个限制其实就是转移时强制某棵子树一定要选。

这就做完了，但看起来转移时需要讨论很多东西。

不妨第一次dp从小 c 所在的位置开始做，那么第二次dp（即换根部分）时，强制选的那棵子树就是父亲，只需要选出儿子中的前 $a_x-2$ 大即可，这样可以简单地实现。

代码如下：
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 200010
#define pb push_back

int n,rt,a[maxn],ans=0;
struct edge{int y,z,next;}e[maxn<<1];
int first[maxn],len=0;
void buildroad(int x,int y,int z){e[++len]=(edge){y,z,first[x]};first[x]=len;}
int f[maxn];
struct par{int x,val;};
vector<par> s[maxn];
bool cmp(par x,par y){return x.val>y.val;}
void dfs1(int x,int fa){
	for(int i=first[x];i;i=e[i].next){
		int y=e[i].y;if(y==fa)continue;
		dfs1(y,x);s[x].pb((par){y,f[y]+e[i].z});
	}
	sort(s[x].begin(),s[x].end(),cmp);
	for(int i=0;i<min((int)s[x].size(),a[x]-1);i++)f[x]+=s[x][i].val;
}
bool v[maxn];
void dfs2(int x,int fa,int fa_val){
	if(x!=rt&&a[x]==1)return;
	f[x]=fa_val;int lim=a[x]-2;if(!fa)lim++;
	for(int i=0;i<min((int)s[x].size(),lim);i++)v[s[x][i].x]=true,f[x]+=s[x][i].val;
	ans=max(ans,f[x]);
	int p=0;if(s[x].size()>lim)p=s[x][lim].val;
	for(int i=first[x];i;i=e[i].next){
		int y=e[i].y;if(y==fa)continue;
		if(v[y])dfs2(y,x,f[x]-f[y]-e[i].z+p+e[i].z);
		else dfs2(y,x,f[x]+e[i].z);
	}
}

int main()
{
	scanf("%d %d",&n,&rt);
	for(int i=1,x,y,z;i<n;i++){
		scanf("%d %d %d",&x,&y,&z);
		buildroad(x,y,z);buildroad(y,x,z);
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs1(rt,0);ans=max(ans,f[rt]);
	dfs2(rt,0,0);
	printf("%d",ans);
}
```

---

## 作者：Supor__Shoep (赞：0)

挺明显的换根 DP。。

### 0x01

先考虑一下起点为 $d$ 的答案该怎么算。

我们发现可以钦定 $d$ 为树根，设 $dp_i$ 表示以 $i$ 为根的子树中，以 $i$ 为起点最多可以获得的代价。由于有了进入节点的次数限制，我们肯定不能直接加和。不难发现这个限制其实就和点的度数有关，于是我们直接选择 $i$ 的儿子中，$dp$ 值最大的 $k_i-1$ 个就行了，排序即可。

### 0x02

我们尝试根据起点为 $d$ 时的求法拓展到其余节点。

这里就是换根 DP 了。我们记 $f_i$ 表示以 $i$ 为起点，且 $i$ 只会往父亲节点移动的最大代价。考虑用 $f_{fa}$ 去更新 $f_i$。如果我们只能向 $fa$ 移动，那么 $fa$ 肯定已经走过了一次，又因为我们的 $fa$ 也在往上走，所以初始时 $fa$ 走了两次。也就是我们选择 $i$ 的兄弟节点中 $dp$ 值最大的 $k_{fa}-2$ 个节点，将它们的 $dp$ 值加起来，最后再加上 $f_{fa}$，就可以得到 $dp_i$。

可能有人要问了——为什么 $fa$ 非要往上走呢？为什么不可以用 $i$ 的兄弟节点中 $dp$ 值最大的 $k_{fa}-1$ 个呢？？

因为我们必须要走到 $d$ 节点至少一次，并且我们是以 $d$ 为根进行 DP 的，那么 $fa$ 肯定就要往上走一次。也正是如此，我们在统计 $d$ 的儿子的时候，才应该像上面这样转移，因为 $fa$ 就是 $d$，没有必要往其它地方走了。

### 0x03

求出了 $f_i$ 之后，我们就可以统计答案了。

我们枚举起点 $s$。首先要到达 $d$ 至少一次，我们就加上一个 $f_s$，然后再考虑将 $k_s$ 给跑满，所以我们还要加上 $s$ 的儿子中 $dp$ 值最大的 $k_s-2$ 个的和。

比较最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int head[MAXN],nxt[MAXN<<1],to[MAXN<<1],val[MAXN<<1],tot;
void add(int x,int y,int z)
{
	to[++tot]=y;
	val[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
int n,d;
int a[MAXN],in[MAXN];
int dp[MAXN],f[MAXN];
int stk[MAXN],cnt;
bool cmp(int x,int y){ return dp[x]<dp[y]; }
void dfs_first(int x,int fa)
{
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		dfs_first(to[i],x);
	}
	int tot=0;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		dp[to[i]]+=val[i],stk[++tot]=to[i];
	}
	sort(stk+1,stk+tot+1,cmp);
	for(int i=max(1,tot-a[x]+2);i<=tot;i++)	dp[x]+=dp[stk[i]];
}
int maxx;
void dfs(int x,int fa)
{
	if(a[x]==1)	return;
	cnt=0;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		stk[++cnt]=to[i];
	}
	sort(stk+1,stk+cnt+1,cmp);
	int now=0;
	for(int i=cnt-a[x]+3;i<=cnt;i++)	now+=dp[stk[i]];
	maxx=max(maxx,f[x]+now);
	for(int i=cnt-a[x]+3;i<=cnt;i++)	f[stk[i]]=f[x]+now-dp[stk[i]]+dp[stk[max(1,cnt-a[x]+3)-1]];
	for(int i=1;i<=cnt-a[x]+2;i++)	f[stk[i]]=f[x]+now;
	for(int i=head[x];i;i=nxt[i])
	{
		if(to[i]==fa)	continue;
		f[to[i]]+=val[i];
		dfs(to[i],x);
	}
}
int main()
{
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>d;
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z),add(y,x,z);
		in[x]++,in[y]++;
	}
	for(int i=1;i<=n;i++)	cin>>a[i],a[i]=min(a[i],in[i]+1);
	for(int i=head[d];i;i=nxt[i])	dfs_first(to[i],d);
	cnt=0;
	for(int i=head[d];i;i=nxt[i])	stk[++cnt]=to[i],dp[to[i]]+=val[i];
	sort(stk+1,stk+cnt+1,cmp);
	for(int i=max(1,cnt-a[d]+2);i<=cnt;i++)	maxx+=dp[stk[i]];
	for(int i=max(1,cnt-a[d]+2);i<=cnt;i++)	f[stk[i]]=maxx-dp[stk[i]]+dp[stk[max(1,cnt-a[d]+2)-1]];
	for(int i=1;i<=cnt-a[d]+1;i++)	f[stk[i]]=maxx;
	for(int i=head[d];i;i=nxt[i])	f[to[i]]+=val[i],dfs(to[i],d);
	cout<<maxx;
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

这个，$O(n)$ 的树形 dp 应该非常显然。

但是有几个限制条件：

- 每次进入的次数不能超过 $k_i$。

其实这里出题人很良心，因为进入迷宫也算进入一次。这样每一个点就有一个“父节点”了。根的父节点可以认为是虚拟原点。

所以，每个节点最多只能和 $k_i-1$ 个儿子算贡献。

- 需要成功救下小 c，即必须走到 $d$。

如果不考虑这个条件，就是换根的时候每个点儿子算前 $k_i-1$ 的贡献就好了。

如果必须走到 $d$，看着不是很好办，因为我们需要知道 $d$ 在当前节点 $x$ 的什么方位，然后必须统计那个方位的贡献。

但是，我们可以转换思路，让 $d$ 成为父节点转移过来的点。

因为父节点对于一个节点来说是比较特殊的，而且只有一个，所以可以强制加入父节点的贡献。

先看一下第一次 dfs 的过程。

简要地说，就是得到儿子的贡献，然后排序，在儿子节点里出来之后显然不会走回去了，这个贪心应该没问题。

```cpp
inline bool cmp(node x, node y){
	return x.x > y.x;
}
inline void dfs(int x, int ff = 0){
	fa[x] = ff;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		vec[x].pb((node){f[son[i]] + w[i], son[i]});
	}
	sort(vec[x].begin(), vec[x].end(), cmp);
	for(int i = 0; i < vec[x].size(); i++) id[vec[x][i].id] = i;
	for(int i = 0; i < vec[x].size() && i < k[x] - 1; i++) f[x] += vec[x][i].x, now[x] = i + 1;
//	printf("x & f[x] : %lld %lld\n", x, f[x]);
}
```

这里，用 $now_x$ 记录一个节点用了几个儿子，可以方便换根。

下面是换根，感觉可以算重点。

换根的参数我记了两个，点 $x$ 和父节点的贡献 $wfa$。

首先，对于每一个不是 $d$ 的节点 $x$，我们应该用 $wfa$ 更新 $f_x$。

- 如果只能进入一次，那么显然不能满足我们的要求，直接 return（这一部分是特判）。

- 如果儿子已经达到了 $k_x-1$ 个，那么显然要删掉一个代价最小的，注意我们 $now_x$ 记录用了几个儿子，也要减 $1$。

- 加上父节点贡献。

```cpp
if(x != d){
//	printf("%lld %lld %lld\n", x, vec[x].size(), k[x] - 1);
	if(k[x] == 1) return ;
	if(now[x] == k[x] - 1) f[x] -= vec[x][--now[x]].x;
	f[x] += wfa;
}
```

下面是父节点在更改的时候需要变化一下 $f_x$，因为在父节点变成 $son$ 的儿子的过程中，可能父节点中的一部分贡献是 $son$ 的，那么要减掉，同时尽可能多地加上贡献。

我们在 `dfs` 函数中记录了一个 `id`，用的就是存储一个儿子在父节点中排名第几。

所以，我们在转移之前要这么干，下面是伪代码：

```
如果儿子计算了贡献:
	去掉贡献。
    	如果可以增加贡献：
        	增加贡献。
```

注意，增加贡献的时候，也要判断增加的贡献是不是下面这个儿子的。

返回的时候记得减掉。

```cpp
for(int i = fir[x]; i ; i = nxt[i]){
	if(son[i] == fa[x]) continue ;
	if(id[son[i]] < now[x]){
		f[x] -= vec[x][id[son[i]]].x;
		if(now[x] < vec[x].size() && now[x] != id[son[i]]) f[x] += vec[x][now[x]].x;
		if(now[x] + 1 < vec[x].size() && now[x] == id[son[i]]) f[x] += vec[x][now[x] + 1].x;
	}
	dfs2(son[i], f[x] + w[i]);
	if(id[son[i]] < now[x]){
		f[x] += vec[x][id[son[i]]].x;
		if(now[x] < vec[x].size() && now[x] != id[son[i]]) f[x] -= vec[x][now[x]].x;
		if(now[x] + 1 < vec[x].size() && now[x] == id[son[i]]) f[x] -= vec[x][now[x] + 1].x;
	}
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
int n, d, ans, x, y, z, fir[N], nxt[N << 1], son[N << 1], w[N << 1], tot, k[N], f[N], tem, fa[N], id[N], now[N];
struct node{
	int x, id;
};
vector<node>vec[N];
inline void add(int x, int y, int z){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
	w[tot] = z;
}
inline bool cmp(node x, node y){
	return x.x > y.x;
}
inline void dfs(int x, int ff = 0){
	fa[x] = ff;
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		vec[x].pb((node){f[son[i]] + w[i], son[i]});
	}
	sort(vec[x].begin(), vec[x].end(), cmp);
	for(int i = 0; i < vec[x].size(); i++) id[vec[x][i].id] = i;
	for(int i = 0; i < vec[x].size() && i < k[x] - 1; i++) f[x] += vec[x][i].x, now[x] = i + 1;
//	printf("x & f[x] : %lld %lld\n", x, f[x]);
}
inline void dfs2(int x, int wfa = 0){
//	printf("x = %lld  ; wfa = %lld\n", x, wfa);
	if(x != d){
//		printf("%lld %lld %lld\n", x, vec[x].size(), k[x] - 1);
		if(k[x] == 1) return ;
		if(now[x] == k[x] - 1) f[x] -= vec[x][--now[x]].x;
		f[x] += wfa;
	}
	ans = max(ans, f[x]);
//	printf("%lld %lld\n", x, f[x]);
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == fa[x]) continue ;
		if(id[son[i]] < now[x]){
			f[x] -= vec[x][id[son[i]]].x;
			if(now[x] < vec[x].size() && now[x] != id[son[i]]) f[x] += vec[x][now[x]].x;
			if(now[x] + 1 < vec[x].size() && now[x] == id[son[i]]) f[x] += vec[x][now[x] + 1].x;
		}
		dfs2(son[i], f[x] + w[i]);
		if(id[son[i]] < now[x]){
			f[x] += vec[x][id[son[i]]].x;
			if(now[x] < vec[x].size() && now[x] != id[son[i]]) f[x] -= vec[x][now[x]].x;
			if(now[x] + 1 < vec[x].size() && now[x] == id[son[i]]) f[x] -= vec[x][now[x] + 1].x;
		}
	}
}
signed main(){
	scanf("%lld%lld", &n, &d);
	for(int i = 1; i < n; i++){
		scanf("%lld%lld%lld", &x, &y, &z);
		add(x, y, z), add(y, x, z);
	}
	for(int i = 1; i <= n; i++) scanf("%lld", &k[i]);
	dfs(d);
	dfs2(d);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Skicyer (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P6213)

# 想法
第一眼应该就是树形 DP 了。然后想一下方程。

首先从 $d$ 点开始 DP 应该是没有问题的。

因为一定要经过 $d$ 点，所以在 DP 时强制加入 $fa$ 的贡献。这样就满足要求了。

## 方程
再思考一下，发现第一次扫描是将 $son$ 中挑最优的走。

$$val_{fa}=\sum^{k_{fa}} val_{son}$$

换根时加入 $fa$ 的贡献就好了。
此时要讨论 $val_{fa}$ 的改变。

$mx$ 为没被选的最大值，$mn$ 为被选的最小值。

如果 $fa$ 选了满了。
这个用 $mx$ 判断。

$$val_{fa}=val_{fa}-val_{son}-w_i$$

如果没有且选了 $son$。

$$val_{fa}=val_{fa}-val_{son}-w_i+mx_{fa}$$



如果 $son$ 选满了。

$$val_{son}=val_{son}-mn_{son}+val_{fa}$$

如果 $son$ 没选满

$$val_{son}=val_{son}+val_{fa}$$

```cpp
//mx为没被选的最大值 mn为被选的最小值
//d 为题面的 k
void dfs2(int x,int fa){
	int tmp=val[x];
	for(int i=fst[x];i;i=nxt[i]){
		int to=e[i];
		if(to==fa) continue;
		if(d[to]==1) continue;
		val[x]=tmp;
		if(d[x]>=sz[x]){
			val[x]=tmp-val[to]-w[i];
			//son全选了
		}
		else {	
			if(val[to]+w[i]>mx[x]&&d[x]>1) {
				val[x]=tmp-val[to]-w[i]+mx[x];
				//to被选了 去掉
			}
		}
		if(d[to]>sz[to]){
			val[to]=val[to]+val[x]+w[i];
		}
		else {
			val[to]=val[to]-mn[to]+val[x]+w[i];
			mx[to]=mn[to];
		}
		//换根
		ans=max(ans,val[to]);
		sz[to]++;
		dfs2(to,x);
		sz[to]--;
	}
}
```
## 总结
换根 DP 应该是不难的，但这道题细节很多，我 $val$ 忘回溯挂了好久。

其他的就比较像模板了，但是判断是否被选的那一部分比较不一样。而且 $sz$ 也要更新。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int mx[maxn],mn[maxn];
int fst[maxn<<1],e[maxn<<1],nxt[maxn<<1],cnt,w[maxn<<1];
priority_queue<int> q[maxn],chk;
int val[maxn],sz[maxn],d[maxn];
int ans=0;
void add(int x,int y,int val){
	nxt[++cnt]=fst[x];
	fst[x]=cnt;
	e[cnt]=y;
	w[cnt]=val;
}
void dfs(int x,int fa){
	sz[x]=1;
	for(int i=fst[x];i;i=nxt[i]){
		int to=e[i];
		if(to==fa) continue;
		sz[x]++;
		dfs(to,x);
		q[x].push(val[to]+w[i]);
	}
	for(int i=1;i<d[x]&&q[x].size();i++){
		val[x]+=q[x].top(); 
		mn[x]=q[x].top();
		q[x].pop();
	}
	if(q[x].size()) {
		mx[x]=q[x].top();
	}
}
void dfs2(int x,int fa){
	int tmp=val[x];
	for(int i=fst[x];i;i=nxt[i]){
		int to=e[i];
		if(to==fa) continue;
		if(d[to]==1) continue;
		val[x]=tmp;
		if(d[x]>=sz[x]){
			val[x]=tmp-val[to]-w[i];
		}
		else {	
			if(val[to]+w[i]>mx[x]&&d[x]>1) {
				val[x]=tmp-val[to]-w[i]+mx[x];
			}
		}
		if(d[to]>sz[to]){
			val[to]=val[to]+val[x]+w[i];
		}
		else {
			val[to]=val[to]-mn[to]+val[x]+w[i];
			mx[to]=mn[to];
		}
		ans=max(ans,val[to]);
		sz[to]++;
		dfs2(to,x);
		sz[to]--;
	}
}
int n,D;
signed main(){
	scanf("%d%d",&n,&D);
	for(int i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
	}
	dfs(D,0);
	ans=val[D];
	dfs2(D,0);
	printf("%d\n",ans);
	return 0;
}
```


---

