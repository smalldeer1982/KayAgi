# [ARC078F] Mole and Abandoned Mine

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc078/tasks/arc078_d

モグラは $ 1 $ から $ N $ の番号がついた $ N $ 個の頂点と $ M $ 本の辺からなる単純連結無向グラフで表されるような廃坑に住むことにしました。 $ i $ 番目の辺は頂点 $ a_i $ と $ b_i $ をつないでおり、取り除くために $ c_i $ 円かかります。

モグラはいくつかの辺を取り除いて、頂点 $ 1 $ から頂点 $ N $ へ同じ頂点を $ 2 $ 回以上訪れないように移動する経路がただ $ 1 $ 通りのみ存在するようにしたいです。これを達成するために必要な資金の最小値を求めなさい。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 15 $
- $ N-1\ \leq\ M\ \leq\ N(N-1)/2 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- $ 1\ \leq\ c_i\ \leq\ 10^{6} $
- 与えられるグラフに多重辺や自己ループは存在しない
- 与えられるグラフは連結

### Sample Explanation 1

以下の図において、赤い破線で表されている辺は取り除かれた辺です。以下の図のように $ 2 $ つの辺を取り除くことで $ 200 $ 円で達成することが可能です。 !\[45c15676bb602ca3b762561fc014ecd0.png\](https://atcoder.jp/img/arc078/45c15676bb602ca3b762561fc014ecd0.png)

### Sample Explanation 2

はじめから、頂点 $ 1 $ から頂点 $ N $ へのパスが $ 1 $ 通りしかないこともあります。

## 样例 #1

### 输入

```
4 6
1 2 100
3 1 100
2 4 100
4 3 100
1 4 100
3 2 100```

### 输出

```
200```

## 样例 #2

### 输入

```
2 1
1 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
15 22
8 13 33418
14 15 55849
7 10 15207
4 6 64328
6 9 86902
15 7 46978
8 14 53526
1 2 8720
14 12 37748
8 3 61543
6 5 32425
4 11 20932
3 12 55123
8 2 45333
9 12 77796
3 9 71922
12 15 70793
2 4 25485
11 6 1436
2 7 81563
7 11 97843
3 1 40491```

### 输出

```
133677```

# 题解

## 作者：Ciyang (赞：8)

#### 好像还没有题解, 打算发一篇, 本题难度称不上黑题, 正解状压, 是练习的好题。
### 分析
题意描述太模糊了, 我再描述一遍, 我一开始因为没看样例就理解错了.  
本题给出N点M边的无向图, 然后要割掉其中一些边, 使从1到N只有一条不经过重复顶点的边.
#### 重点是这条路径不需要经过所有点.
看数据范围, 只可能是状压或者暴力搜索, 然而难度说明只能是状压了.   
很容易想到, 求删边边权最少, 相当于求留下的边边权最大.   

然后我没有想到具体怎么求, 搜到了一个[大佬的题解](https://www.cnblogs.com/lcxer/p/10719030.html), 最终的图还有一个重要性质:
#### 每个点最多只与保留下来的那条路径上的一个点有边相连 
所以我们先预处理出所有的联通块中的边权和.  
然后进行DP, 二维数组, 第一维为处理了哪些点, 第二维为到达哪个点(当前终点).   
有两种转移, 一种是新处理一个点, 一种是将一个联通块与当前终点相连.

我从这道题还学习了一个新的二进制性质.枚举一个数二进制下的所有子集:

```
int num = 59; // 某个数
for(int i= num; i; i= (i - 1) & num) {
	// i 为 num 的一个二进制子集
}
```
比如(0101)的子集为(0101),(0100),(0001),(0000).   
### 代码
```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int n, m, nn, edge[16][16], tmpx, tmpy, tmpz, sums;
int blocks[1 << 16], len, f[1 << 16][16];
int main() {
	cin >> n >> m;
	nn= 1 << n;
	for(int i= 1; i <= m; i++) {
		cin >> tmpx >> tmpy >> tmpz;
		sums+= edge[tmpx][tmpy]= edge[tmpy][tmpx]= tmpz;
	}
	for(int i= 0; i < nn; i++) {
		for(int j= 1; j <= n; j++) {
			if(!(i & (1 << (j - 1))) && !(blocks[i | (1 << (j - 1))])) {
				blocks[i | (1 << (j - 1))]= blocks[i];
				for(int k= 1; k <= n; k++)
					if((i & (1 << (k - 1)))) blocks[i | (1 << (j - 1))]+= edge[j][k];
			}
		}
	}
	memset(f, -1, sizeof(f));
	f[1][1]= 0;
	for(int i= 0; i < nn; i++) {
		for(int j= 1; j <= n; j++) {
			if(f[i][j] != -1 && (i & (1 << (j - 1)))) {
				for(int k= 1; k <= n; k++)
					if(!(i & (1 << (k - 1))) && edge[j][k]) f[i | (1 << (k - 1))][k]= max(f[i | (1 << (k - 1))][k], f[i][j] + edge[j][k]);
				tmpx= ((nn - 1) ^ i) | (1 << (j - 1));
				for(int k= tmpx; k; k= (k - 1) & tmpx)
					if(k & (1 << (j - 1))) f[i | k][j]= max(f[i | k][j], f[i][j] + blocks[k]);
			}
		}
	}
	cout << sums - f[nn - 1][n] << endl;
	return 0;
}
```


---

## 作者：C　C　A (赞：8)

$$\huge\rm [ARC078D]Mole~and~Abandoned~Mine$$

$$\large\text{——}~The~~Solution~~Written~~by~~CCA~\text{——}$$

---

$$\LARGE\mathcal{Description}$$

$\quad$给定一张 $n(n\leqslant 15)$ 个点 $m$ 条边的无向带权连通图，要求删除一些边，使得从 $1$ 号点到 $n$ 号点仅存在一条简单路径，求删除边的边权和的最小值 。

---

$$\LARGE\mathcal{Solution}$$

$\quad$因为从 $1$ 号点到 $n$ 号点存在且仅存在一条简单路径，所以删完边后的图一定是由一条从 $1$ 到 $n$ 的链，和若干个两两之间没有连边，且与链之间仅有一条边的连通块组成 。

$\quad$令 $f_{i,S}$ 表示集合 $S$ 中的所有点与 $i$ 之间的边权和，$g_S$ 表示两个端点都在 $S$ 内的边权和 。

$\quad$设 $dp_{i,S}$ 表示 $S$ 中的点均已与 $1$ 号点连通，当前链的末尾为 $i$ 的总边权最大值 。

$\quad$考虑到任意一个状态 $\{i,S\}$ 均有两种转移方式，即在 $i$ 后增加一个点 $j$ 并加上 $E_{i,j}$ 的贡献 ，或者在 $i$ 上挂一个连通块 $T$ 并加上 $(f_{i,T}+g_T)$ 的贡献 。

$\quad$于是状态转移方程即为 $:$

$$\begin{cases}dp_{j,S\cup j}=Max\{dp_{i,S}+E_{i,j}\}\\\\dp_{i,S\cup T}=Max\{dp_{i,S}+f_{i,T}+g_{T}\}\end{cases}$$

$\quad$其中，$T$ 为 $S$ 补集的子集，枚举一个集合 $P$ 的子集 $Q$ 的方式如下 $:$

```cpp
    for (int Q = P; Q; Q = (Q - 1) & P);
```

$\quad$这样可以在 $\mathcal{O}(3^{|P|})$ 的总时间复杂度内不重不漏地 $(\varnothing$ 除外$)$ 枚举 $P$ 的所有子集 。

$\quad$至此，本题解决，时间复杂度为 $\mathcal{O}(3^n)$ 。

---

$$\LARGE\mathcal{Code}$$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 15 + 2, K = 1 << 15;

int n, m, k, u, v, w, E[N][N], sum;
int f[N][K], g[K], dp[N][K];

int main () {

	memset(E, 128, sizeof(E)), memset(dp, 128, sizeof(dp));

	scanf("%d%d", &n, &m), k = 1 << n;
	for(int i = 1; i <= m; i++)
		scanf("%d%d%d", &u, &v, &w), E[u][v] = E[v][u] = w, sum += w;

	for(int S = 0; S < k; S++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(S & (1 << (j - 1))) f[i][S] += max(0, E[i][j]);

	for(int S = 0; S < k; S++)
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				if((S & (1 << (i - 1))) && (S & (1 << (j - 1)))) g[S] += max(0, E[i][j]);

	dp[1][1] = 0;
	for(int S = 0; S < k; S++)
		for(int i = 1; i <= n; i++) if(dp[i][S] >= 0) {
			for(int j = 1; j <= n; j++)
				if(!(S & (1 << (j - 1))) && E[i][j] > 0)
					dp[j][S | (1 << (j - 1))] = max(dp[j][S | (1 << (j - 1))], dp[i][S] + E[i][j]);
			for(int T = ((k - 1) ^ S); T; T = ((T - 1) & ((k - 1) ^ S)))
				dp[i][S | T] = max(dp[i][S | T], dp[i][S] + f[i][T] + g[T]);
		}

	printf("%d", sum - dp[n][k - 1]);

	return 0;
}
```


---

## 作者：chenxia25 (赞：5)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/AT2657) & [AtCoder题目页面传送门](https://atcoder.jp/contests/arc078/tasks/arc078_d)

> 给定一个无向连通带权图$G=(V,E),|V|=n,|E|=m$（节点从$0$开始编号），要删掉一些边使得节点$0$到$n-1$有且只有$1$条简单路径，求最小的删掉的边的权值和。

> $n\in[2,15],m\in\left[n-1,\dfrac{n(n-1)}2\right]$，$G$中没有重边或自环。

这个问题显然可以转化为：求最大的删过边之后的图的边权和，再用原图的边权和减去它。

考率删过边之后的图$G'(V,E')$的样子。$0\to n-1$只有$1$条简单路径，设它为$pa\left(pa_1=0,pa_s=n-1,\forall i\in[1,s),(pa_i,pa_{i+1},len)\in E'\right)$。若$\exists i\in[1,s],\exists j\in[i+1,s]$，$pa_i\to pa_j$有不止$1$条简单路径，那么显然可以先走$0\to pa_i$，然后分别走$pa_i\to pa_j$的多条路径，最后走$pa_j\to n-1$，构造出多条$0\to n-1$路径，不符合题意。可以得到$\forall i\in[1,s],\forall j\in[i+1,s]$，$pa_i\to pa_j$只有$1$条简单路径。所以$G'$应该是这样的：$pa$中每个点下面挂着几坨连通的点，各个点挂的点集没有交集（如果有交集，那么这$2$个$pa$中的点之间的简单路径就会不止$1$条）。

最优情况下，$G'$一定是连通的。理由：若$G'$不连通，由于$G'$合法，$0,n-1$一定在一个连通分量内。那么可以在除了$0,n-1$所在连通分量的其他连通分量之间恢复若干被删除的边使得它们连通（由于原图$G$连通，一定可行）。此时$G'$还剩$2$个连通分量，设它们分别为$A,B$，其中$0,n-1\in A$。由于原图$G$连通，一定可以找到一组点$(a,b)$使得$a\in A,b\in B,(a,b,len)\in E$，将$(a,b,len)$恢复，这样$B$就成为了挂在$pa$中点下新的一坨点或某坨旧点的一份子。如此，可以在$G'$上恢复若干被删除的边，使得它更优且合法。所以最优情况下，$G'$一定是连通的。

接下来，利用任意$2$坨点都没有交集这个性质，就可以状压DP了。设$dp_{i,j}(0\in i)$表示$pa$中$0\to j$这条链包括它们下面挂的那些坨点所构成的点集为bitmask$i$时，$\left\{(x,y,len)\mid x,y\in i,(x,y,len)\in E\right\}$中可以留下的边的最大权值和。显然，目标为$\sum\limits_{(x,y,len)\in E}len-dp_{V,n-1}$，边界为$dp_{i,0}=\sum\limits_{x,y\in i,(x,y,len)\in E}len$。转移时，枚举$j$下挂的点集，这个点集和$\{j\}$的并集中显然应该所有的边都留下，再枚举$pa$中$j$的前一个点，这个点到$j$的边也应该留下。于是状态转移方程就出来了：
$$dp_{i,j}=\max_{k\subseteq i-\{0,j\}}\left\{\sum_{x,y\in k\cup\{j\},(x,y,len)\in E}len+\max_{o\in i-k-\{j\},(o,j,len)\in E}\left\{len+dp_{i-k-\{j\},o}\right\}\right\}$$
这里面有个子集枚举，所以直接按照这个方程转移是$\mathrm O\left(3^nn^3\right)$的，过不去。显然，可以预处理出$sum_i=\sum\limits_{x,y\in i,(x,y,len)\in E}len$，复杂度降到了$\mathrm O\left(3^nn^2\right)$，但还是过不去。接下来要处理$\max\limits_{o\in i-k-\{j\},(o,j,len)\in E}\left\{len+dp_{i-k-\{j\},o}\right\}$，不难发现这个式子仅关于$i-k-\{j\}$和$j$，而不同的二元组$(i-k-\{j\},j)$只有$\mathrm O(2^nn)$个，这个式子却被计算了$\mathrm O(3^nn)$次。于是我们可以避免重复计算，记录$tmp_{i,j}=\max\limits_{k\in i,(k,j,len)\in E}\left\{len+dp_{i,k}\right\}$，在每次完成一个$dp_{i,j}$的计算时，更新所有与它相关的$tmp$的值，即令$\forall k\notin i((j,k,len)\in E),tmp_{i,k}=\max(tmp_{i,k},len+dp_{i,j})$。这样，在状态转移方程中遇到这个式子时，直接调用$tmp$即可。

放一下最终的状态转移方程：
$$dp_{i,j}=\max_{k\subseteq i-\{0,j\}}\left\{sum_{k\cup\{j\}}+tmp_{i-k-\{j\},j}\right\}$$

时间复杂度$\mathrm O\left(3^nn+2^nn^2\right)=\mathrm O(3^nn)$。

最后上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=15;
int n,m;
int tb[N][N];//邻接矩阵 
int sum[1<<N]; 
int tmp[1<<N][N],dp[1<<N][N];
void prt_bitmsk(int x){ 
	for(int i=0;i<n;i++)cout<<!!(x&1<<i);
}
int main(){
	cin>>n>>m;
	int tot=0;
	while(m--){
		int x,y,z;
		cin>>x>>y>>z;
		x--;y--;
		tb[x][y]=tb[y][x]=z;
		tot+=z;
	}
	for(int i=0;i<1<<n;i++){//预处理sum 
		for(int j=0;j<n;j++)if(i&1<<j)for(int k=j+1;k<n;k++)if(i&1<<k)
			sum[i]+=tb[j][k];
//		printf("sum[");prt_bitmsk(i);printf("]=%d\n",sum[i]);
	}
	for(int i=0;i<1<<n;i++)for(int j=0;j<n;j++)dp[i][j]=tmp[i][j]=-inf;//初始化 
	for(int i=0;i<1<<n;i++)if(i&1)for(int j=0;j<n;j++)if(i&1<<j){//DP 
		if(j)//非边界 
			for(int k=i^1<<j^1;;k=k-1&(i^1<<j^1)){//枚举j下面挂的点集k 
				dp[i][j]=max(dp[i][j],sum[k|1<<j]+tmp[i^k^1<<j][j]);//状态转移方程 
				if(!k)break;
			}
		else//边界 
			dp[i][j]=sum[i];
//		printf("dp[");prt_bitmsk(i);printf("][%d]=%d\n",j,dp[i][j]);
		for(int k=0;k<n;k++)if(!(i&1<<k))//更新与dp[i][j]有关的所有tmp[i][k] 
			if(tb[j][k])
				tmp[i][k]=max(tmp[i][k],dp[i][j]+tb[j][k]);
	}
	cout<<tot-dp[(1<<n)-1][n-1];//目标 
	return 0;
}
```

---

## 作者：CHU2 (赞：4)

玄学做法。

最终的图可以看成是原图的一棵生成树 + 一些非树边，看起来不错的样子，所以考虑求留下的最大价值

考虑可以留下哪些非树边：设一条非树边的两个端点为$\texttt{u,v}$，则$\texttt{u->v}$路径上的点和$\texttt{1->n}$路径上的点的公共点数量要$<2$（否则就可以走“回头路”，从而多走一条路径）

上面可以用$\texttt{n+1}$次dfs搞定

于是我们就只用确定生成树，一般的想法都是把生成树确定为最大生成树，然而这不一定对，怎么搞呢？

你看这个$\texttt{n,m}$都那么小，可以把最大生成树得出的结果定为$\texttt{ans}$的初值 ，然后**随机很多生成树** 调整它。

生成一棵生成树就是把边集打乱，然后用krusal合并一下。

就……过了？

```cpp
#include <bits/stdc++.h>
#define N 20
#define ll long long
#define lson l,mid,o<<1
#define rson mid+1,r,o<<1|1
#define Ls(o) t[o].ls
#define Rs(o) t[o].rs
#define For(i,x,y) for(int i=(x);i<=(y);++i)
#define Rof(i,x,y) for(int i=(x);i>=(y);--i)
#define Edge(x) for(int i=head[x];i;i=e[i].nxt)
#define mcpy(x,y) memcpy(x,y,sizeof(x))
#define mset(x,y) memset(x,y,sizeof(x))
using namespace std;
int ans=1e9,t,n,m,fa[N],a[N][N],_;
vector<int> g[N];
bool vis[N],use[N*N],p[N][N];
struct ed{ int u,v,w; }e[N*N],tmp[N*N];
void dfs(int x,int f){
	fa[x]=f;
	for(auto to:g[x]) if(to!=f) dfs(to,x);
}
bool cmp(const ed &x,const ed &y){ return x.w>y.w; }
void dfs2(int rt,int x,int f,int cnt){
	if(cnt<=1 && ~a[x][rt] && !p[x][rt] && !(vis[x] && vis[rt]) && f!=rt) _+=a[x][rt];
	for(auto to:g[x]) if(to!=f) dfs2(rt,to,x,cnt+vis[to]);
}
int find(int x){ return x==fa[x]?x:fa[x]=find(fa[x]); }
int solve(){
	int tot=0;_=0;
	For(i,1,n) fa[i]=i,vis[i]=0;
	For(i,1,n) For(j,1,n) p[i][j]=0;
	For(i,1,m) use[i]=0;
	For(i,1,m){
		int u=find(tmp[i].u),v=find(tmp[i].v);
		if(u==v) continue;
		if(u>v) swap(u,v);fa[v]=u;
		tot+=tmp[i].w,use[i]=1,p[tmp[i].u][tmp[i].v]=p[tmp[i].v][tmp[i].u]=1;
	}
	For(i,1,n) g[i].clear();
	For(i,1,m) if(use[i]) g[tmp[i].u].push_back(tmp[i].v),g[tmp[i].v].push_back(tmp[i].u);
	For(i,1,n) fa[i]=0;
	dfs(1,0);
	for(int i=n;i;i=fa[i]) vis[i]=1;
	For(i,1,n) dfs2(i,i,0,vis[i]);
	tot+=_/2;
	return tot;
}
void Rand(){
	random_shuffle(tmp+1,tmp+m+1);
	ans=max(ans,solve());	
}
int main(){
	int qwq=0,u,v,w;
	srand(20000000);srand(rand());srand(rand());
	scanf("%d%d",&n,&m);
	mset(a,-1);
	For(i,1,m){
		scanf("%d%d%d",&u,&v,&w);
		e[i]=(ed){u,v,w},qwq+=w,a[u][v]=a[v][u]=w;
		tmp[i]=e[i],g[u].push_back(v),g[v].push_back(u);
	}
	sort(e+1,e+m+1,cmp);
	For(i,1,m) tmp[i]=e[i];
	ans=solve();
	For(i,1,500500) Rand();
	printf("%d\n",qwq-ans);
}
```





---

## 作者：Cx114514 (赞：3)

先转化一下题意，题目要求删掉的边权和最小，也就是要剩下的边权和最大。再考虑最终剩下的图长什么样：一条 $1$ 到 $n$ 的路径，上面的每个点上可能挂着一个连通块（重点理解一下）。

因为 $n\le 15$，所以不妨设 $f_{S,i}$ 表示在 $i$ 这个状态下（对于每个点，出现记为 $1$，未出现记为 $0$，组成的二进制数记为 $S$），路径的结尾为 $i$ 的边权和最大值。我们枚举当前点上挂的连通块情况，即可完成转移。


令 $g_{i,j}$ 表示从点 $i$ 到点 $j$ 的直接路径距离。对于 $f_{S,i}$，令集合 $T=\left \{ x\in S\mid x\ne i \right \} $，则有转移如下：

$f_{S,i}= \mathop{\max}\limits_{V\subseteq T,j\in V}  \left \{ f_{V,j}+g_{i,j}+ \mathop{\sum}\limits_{k\le l,\left ( k,l \right ) \in S,\left ( k,l \right )\notin V}g_{k,l}\right \} $。

其中枚举子集的复杂度为 $O\left ( 3^{n} \right ) $，故总复杂度为 $O\left ( 3^{n}n^{2} \right ) $。

下面是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, ans, G[25][25], sum[100005], f[100005][25];

int main()
{
	cin >> n >> m;
	while (m--)
	{
		int u, v, w;
		cin >> u >> v >> w;
		ans += w;
		G[u][v] = G[v][u] = w;
	}
	for (int i = 1; i < (1 << n); i++)
		for (int j = 1; j <= n; j++)
			for (int k = j + 1; k <= n; k++)
				if ((i & (1 << (j - 1))) && (i & (1 << (k - 1)))) sum[i] += G[j][k];
	for (int i = 0; i < (1 << n); i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = -1145141919;
	for (int i = 1; i < (1 << n); i++)
		if (i & 1) f[i][1] = sum[i];
	for (int i = 1; i < (1 << n); i++)
		for (int j = 1; j <= n; j++)
			if ((1 << (j - 1)) & i)
				for (int S = i - (1 << (j - 1)); S; S = (S - 1) & (i - (1 << (j - 1))))
					for (int k = 1; k <= n; k++)
						if ((1 << (k - 1)) & S && G[k][j]) f[i][j] = max(f[i][j], f[S][k] + G[k][j] + sum[i - S]);
	cout << ans - f[(1 << n) - 1][n] << endl;
    return 0;
}

```

---

## 作者：lalaouye (赞：2)

这是一道容易想假的题（个人认为）。

首先有一个转化，我们发现直接删边不好做，我们考虑如果已经知道这条唯一路径该怎么做。我们画完图后发现，保留的图一定会是路径中的点挂着若干个路径以外的点，并且这些点可以任意互相连边，路径中不同点挂着的点集一定不能互相连边。
但是直接枚举这条路径会超时，这时候我们发现，除了这条路径以外的点的连边情况并不受路径内的连边顺序所影响，比如说 ``1->2->3->4`` 和 ``1->3->2->4``，他们即使顺序不同，但是对答案不会产生影响，**因为我们实质上关系的是这条路径上的点集，而不是这条路径**。这时就很容易想到 dp 了，处理顺序也是容易的，我们设 $f_{S,i}$ 表示当前已经处理完 $1$ 到 $i$ 路径上 $S$ 内的点的最大边权和，然后我们转移时需枚举一个点集 $T$ 和新的唯一路径末尾 $j$，$j\in T$，意思是 $j$ 挂着的点集为 $T$，为了方便处理让 $j$ 也属于这个集合。那么状态转移方程式为：

$$f_{S\cup T,j}\leftarrow f_{S,i}+Gat_T+e_{i,j}$$ 

其中 $Gat$ 表示一个集合内部连边产生的贡献，可以预处理，$e$ 为边权。

一定要注意 dp 的初始化。

代码（我想代码应该不难写）：

```cpp
auto main () -> int
{
    n = rd (), m = rd ();
    rep (i, 1, m) { int u = rd (), v = rd (), w = rd (); e[u][v] = e[v][u] = w; ret += w; }
    int maG = (1 << n) - 1; rep (S, 1, maG)
    { ve.clear (); rep (j, 0, n - 1) if (S >> j & 1) ve.eb (j + 1);
        for (auto u : ve) for (auto v : ve) { Gat[S] += e[u][v]; } Gat[S] >>= 1; 
    }  rep (S, 1, maG) rep (i, 1, n) f[S][i] = -1e12;
    rep (S, 1, maG) if (S & 1) f[S][1] = Gat[S]; rep (S, 1, maG - 1)
    { if (! (S & 1)) continue; if (S >> (n - 1)) continue; int Ga = maG ^ S;
        rep (i, 0, n - 1)
        { if (! (S >> i & 1)) continue;
            for (int T = Ga; T; T = (T - 1) & Ga)
                rep (j, 0, n - 1) if (T >> j & 1)
                        if (e[i + 1][j + 1])
                            f[S | T][j + 1] = max (f[S | T][j + 1], f[S][i + 1] + Gat[T] + e[i + 1][j + 1]);
        }
    } printf ("%lld\n", ret - f[(1 << n) - 1][n]);
}
```


---

## 作者：roger_yrj (赞：1)

## [ARC078F] Mole and Abandoned Mine

### 前言

看了前两篇题解，一篇时间复杂度不对，一篇排版太乱根本不可读，于是我打算写一篇更好的题解。

### 题意

$n$ 个点 $m$ 条边的简单带权无向连通图，要求割掉若干条边，使 $1$ 到 $n$ 只有 $1$ 条路径，问割掉的边权和最小是多少。

### 题解

发现割边很难判断是否只有一条路径，所以尝试将题意转为保留边权和最大的边集。

通过观察发现，最优解一定把这张图分成若干个连通块，然后用一条路径串起来，类似下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/aiwdaa3u.png)

我们可以 $O(2^nn^2)$ 预处理出每个连通块的边权和：设 $W_S=\sum\limits_{i\in S,j\in S}e_{i,j}$

看到 $n\le15$，考虑状压 DP。

设 $f_{S,i}$ 表示已经连了 $S$ 中的点，路径走到 $i$ 的最大边权和，考虑如何转移。

我们用刷表法实现转移：

$$f_{S|T,j}=\max\limits_{T\cap S=\emptyset,j\in T}\left\{f_{S,i}+e_{i,j}+W_T\right\}$$

时间复杂度 $O(3^nn^2+2^nn^2)$，无法通过。（常数小可能过？）

我们可以用一个类似前缀和优化的东西。设 $g_{S,j}=\max\limits_{i\in S}\left\{f_{S,i}+e_{i,j}\right\}$，那么原式变为 $f_{S|T,j}=\max\limits_{T\cap S=\emptyset,j\in T}\left\{g_{S,j}+W_T\right\}$。

$g$ 可以 $O(3^nn)$ 处理出来，转移优化至 $O(3^nn)$。

于是总的时间复杂度优化到 $O(3^nn+2^nn^2)$，足以通过本题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20,NN=40010;
int n,m,f[NN][N],g[NN][N],W[NN],e[N][N],sum;
int main(){
	cin>>n>>m;
	memset(e,-1,sizeof(e));
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		e[u][v]=e[v][u]=w;
		sum+=w; 
	}
	for(int S=0;S<(1<<n);S++){//预处理连通块 
		for(int i=1;i<=n;i++){
			if(((1<<i)&(S<<1))==0)continue;
			for(int j=i+1;j<=n;j++){
				if(((1<<j)&(S<<1))==0)continue;
				if(~e[i][j])W[S]+=e[i][j];
			}
		}
	}
	memset(f,-0x3f,sizeof(f));
	memset(g,-0x3f,sizeof(g));
	for(int S=1;S<(1<<n);S++)if(S&1)f[S][1]=W[S];
	for(int S=1;S<(1<<n);S++){
		for(int i=1;i<=n;i++){//求 g 
			if(((1<<i)&(S<<1))==0)continue;
			for(int j=1;j<=n;j++){
				if((1<<j)&(S<<1))continue;
				if(~e[i][j])g[S][j]=max(g[S][j],f[S][i]+e[i][j]);
			}
		}
		for(int SS=(1<<n)-1-S;SS;SS=(SS-1)&((1<<n)-1-S)){//刷表法求 f 
			for(int j=1;j<=n;j++){
				if(((1<<j)&(SS<<1))==0)continue;
				if(!S&&j!=1)continue;
				f[S|SS][j]=max(f[S|SS][j],g[S][j]+W[SS]);
			}
		}
	}
	cout<<sum-f[(1<<n)-1][n];
}
```

---

## 作者：BLX32M_10 (赞：1)

## 题意

有一张 $n$ 个点 $m$ 条边的带边权的无向图。去掉一些边使得点 $1$ 和 $n$ 之间只存在一条简单路径。求去掉的边的权值和的最小值。

## 题解

学校请了一个大佬讲 DP 题，~~然后在大家的集思广益下整出了一个随机化做法。~~

不难发现满足题意的图应该是一条 $1$ 到 $n$ 的链上挂着一些连通图，而这些连通图之间没有边相连。

因此只要找出一条 $1$ 到 $n$ 之间的路径，以及其他节点挂在哪个 $1$ 到 $n$ 的路径上的点之后，我们就可以用 $\mathcal O\left(n+m\right)$ 的时间复杂度求出该方案的答案。

不难发现生成树就可以解决。但是使用 Kruscal 需要边权按照一种顺序排序，而 Prim 又在这里不好用。

此时注意到 $n \leq 15$，时限 3s（实际远远不到 3s），因此我们完全可以考虑随机化边权顺序。

对于统计答案，我们先在生成树上搜出来整条 $1$ 到 $n$ 的链的边权之和，然后再在链上的点搜出挂在这个点上的所有点，用并查集维护，最后再遍历一下所有的边，只要边的两个端点挂在同一个点上就把答案加上边权。当然，最终的答案是边权总和减去上述答案。


但这样乱搞正确性并不低。主要原因是我们使用生成树的作用仅仅是确定 $1$ 到 $n$ 的路径和其他节点挂在哪个点上。所以这种做法并不需要生成一棵很确定的树才能让答案正确。

于是我们卡时就能过了。但是实际上根本不用卡得很死，亲测 0.8s 可过。

AC 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb emplace_back
#define mkp make_pair
using namespace std;
int n, m;
mt19937_64 rng(time(0));
vector <pair <int, int> > ed[20];
int G[20][20];
vector <int> tr[20];
struct edge
{
	int u, v, w;
} a[505];
int fa[20], sum, cur, ans;
inline int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void mg(int x, int y)
{
	fa[find(x)] = find(y);
}
inline void init()
{
	for (int i = 1; i <= n; i++)
		fa[i] = i;
}
inline void dfst(int u, int fa)
{
	mg(u, fa);
	for (int v : tr[u])
		if (v != fa)
			dfst(v, u);
}
inline bool dfsc(int u, int fa)
{
	if (u == n)
	{
        for (int vv : tr[u])
            if (vv != fa)
                dfst(vv, u);
		return 1;
	}
	for (int v : tr[u])
	{
		if (v == fa)
			continue;
		if (dfsc(v, u))
		{
			cur += G[u][v];
			for (int vv : tr[u])
				if (vv != fa && vv != v)
					dfst(vv, u);
			return 1;
		}
	}
	return 0;
}
inline int gen_tree()
{
	init();
	for (int i = 1; i <= n; i++)
		tr[i].clear();
	for (int i = 1; i <= m; i++)
	{
		if (find(a[i].u) != find(a[i].v))
		{
			tr[a[i].u].emplace_back(a[i].v);
			tr[a[i].v].emplace_back(a[i].u);
			mg(a[i].u, a[i].v);
		}
	}
	init();
	cur = 0;
	dfsc(1, 0);
	int cc = 0;
	for (int u = 1; u <= n; u++)
	{
		for (auto &p : ed[u])
		{
			int &v = p.first;
			if (find(u) == find(v))
				cc += p.second;
		}
	}
	return cur + cc / 2;
}
inline void shf()
{
	srand(rng());
	for (int i = 1; i <= m; i++)
	{
		swap(a[i], a[rng() % m + 1]);
	}
}
signed main()
{
	scanf("%lld %lld", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%lld %lld %lld", &u, &v, &w);
		G[u][v] = G[v][u] = w;
		a[i] = (edge){u, v, w};
		ed[u].pb(mkp(v, w));
		ed[v].pb(mkp(u, w));
		sum += w;
	}
	ans = sum - gen_tree();
	while (1)
	{
		if (clock() > 0.8 * CLOCKS_PER_SEC)
			break;
		shf();
		ans = min(ans, sum - gen_tree());
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：LCat90 (赞：1)

又是一道自己做出来的题，终于可以自己做出 ARCD 啦！

首先转化成算最终图上的最大边权。

挖掘性质，发现这个图首先有**一条从 $1$ 到 $n$ 的链**。不仅如此，注意到题目中说到路径点不重复，自然地想到**对于链上面每个点 $x$ 都扩展出去一个子图**（可能为空），并且这些点只能自己内部连边或者和 $x$ 连边，否则一定不满足只有 1 条路径的限制。

这样我们就得到了路径的大致样子，然后就是设计 dp。$f(S,i)$ 表示当前走了的点集为 $S$，当前在链上走到了 $i$ 点。

转移分为 2 种。第一种是加入链上的一条边。第二种是在 $i$ 点上接一个子图，这里直接枚举子集转移即可。

一个子图内的边权和可以和输入一起 $O(m2^n)$ 预处理，总时间 $O(n3^n+m2^n)$。

```cpp
#include <bits/stdc++.h>
#define raed read
#define cacl calc
//#define int long long
#define pb push_back
#define pii pair <int, int>
#define fi first 
#define se second
#define vc vector <int>


using namespace std;

const int N = 18, M = 1 << 16, inf = 0x3f3f3f3f; int read();

int n, m, sum;
int dp[M][N]; // maxn
int a[M], val[N][N];

bool ck(int x, int y) {
	return x & (1 <<y - 1);
}
void ckmax(int &x, int y) { x = max(x, y); }

void solve() {
	cin >> n >>m; int maxn = 0;
	for(int i = 1;i <= m; ++i) {
		int x = read(), y = read(), w = read();
		sum += w; val[x][y] = val[y][x] = w;
		for(int j = 1;j < (1 << n); ++j)
			if(ck(j, x) and ck(j, y)) a[j] += w;
	}
	memset(dp, 0xf3, sizeof dp);
	dp[1][1] = 0; 
	for(int i = 1;i < 1 << n; ++i) {
		for(int j = 1;j <= n; ++j)
			if(ck(i, j) and dp[i][j] != inf) {
				int S = i ^ ((1 << n) - 1);
				for(int k = 1;k <= n; ++k)
					if(!ck(i, k) and val[j][k]) ckmax(dp[i | (1 << k - 1)][k], dp[i][j] + val[j][k]);
				for(int k = S;k;k = (k - 1) & S) 
					ckmax(dp[i | k][j], dp[i][j] + a[k | (1 << j - 1)]);			
			}
	}
//	for(int i = 1;i < 1 << n; ++i) 
//		for(int j = 1;j <= n; ++j) 
//			if(ck(i, j)) cout << i << " " << j << " " << dp[i][j] << "\n";
//	cerr << sum <<" ";
	cout << sum - dp[(1 << n) - 1][n];
}

signed main() {
	int T = 1;
	while(T--) solve();
	return 0;
}

/*
难道不是直接把当前路径是什么样的搞出来吗
哦不对你可以 1->n 是一条边，然后 2~n-1 全部选完
或者说也可以路径上一个点借出去一个环 
这个形式怎么 jb 刻画；
首先枚举 S，计算 1 -> n 的路径是 S 的最大路径，转移显然
然后在这个答案的基础上，每个点都接出去一个小的联通块，保证这些联通块没有交
这个暴力怎么优化？
考虑边走边 dp；
dp(S, i) 其中 i 表示当前 1 -> i 的结尾点，S 表示挡墙走到的点集
转移：
1. (S, i) -> (S + j, j)
2. (S, i) -> (S + clr, i) 
转移一共是 3^n 次方，每次 *n
*/

int read() {
	int s = 0, f = 1; char ch = getchar();
	while(ch < '0' or ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * f;	
}
```

---

## 作者：hh弟中弟 (赞：0)

很经典的状压套路，首先有一步转化是求保留的最大边权值，然后考虑答案的形态一定是若干个边双连起来，起点是 $1$，终点是 $n$，有一个重要的性质就是一个边双内的边可以随便加，且每个边双内的点集不交，所以可以根据这个来状压 DP，设 $f_{i,S}$ 表示路径从 $1$ 到 $i$，已经处理完的点集为 $S$ 的最大权值，转移形如 $f_{i,S}=f_{j,T}+W_{S-T}+e_{j,i}$，其中 $W_{S}$ 表示点集 $S$ 中随意加边的最大值，直接转移复杂度是 $3^nn^2$ 的，AT 神机可以通过。\
发现这个转移有很多状态的重复枚举，不妨处理一个 $g_{j,S}$ 表示 $\max{f_{i,S}+e_{i,j}}$，这个可以 $2^nn^2$ 来处理，这样就能快速转移了，时间复杂度 $\mathcal{O}(3^nn+2^nn^2)$。\
[record](https://atcoder.jp/contests/arc078/submissions/61672949)

---

