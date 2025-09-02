# [SNOI2013] Quare

## 题目描述

4.20 四川芦山地震发生后，抗震救灾委员会接到一个紧急任务，四川省给该委员会发了一份地图，这份地图给出了该省一些城市的情况：任两个城市是用一条或多条公路连接起来的，也可以没有公路连接，但是每个城市都可以直接或间接地到达另外的城市，注意这些公路是可以双向行驶的。由于最近余震、暴雨造成泥石流倾泻，使得车辆在这些公路上行驶很不安全，于是四川省决定尽快对部分公路进行抢修，以保障救援车辆行车安全。
    
该省对所有的公路情况都进行了勘察，分析估计了抢修某段公路所需要花费的时间，并记录在地图中。现在该省希望抗震救灾委员会能找到一个方案，该方案决定出哪些公路需要抢修，使得抢修后的公路仍能保证任意两个城市之间都能直接或间接地相连，同时为了安全起见，即使某一条抢修的公路被泥石流阻断了，任意两城市仍能保持这个性质。由于时间紧迫，抗震救灾委员会还需保证找到的这个方案总抢修时间最短。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 3$，$1 \leq n \leq 12$，$1 \leq m \leq 40$，$1\le c\le 5\times 10^4$。

## 样例 #1

### 输入

```
2
4 6
1 2 1
1 3 2
1 3 3
2 4 2
3 4 1
2 3 1
2 1
1 2 3
```

### 输出

```
6
impossible
```

# 题解

## 作者：ix35 (赞：28)

作为一道求包含所有点的最小权边双连通子图的状压 DP 题，做法与其强连通分量版本 https://codeforces.ml/gym/102759/problem/C 是近乎一样的。

首先我们需要了解 **耳分解**。

这里这样定义耳（不知道是否标准）：对于（强）连通图 $G$，耳是一条路径 $a_1\to \ldots\to a_m$，满足 $a_1,\ldots,a_{m-1}$ 两两不同且 $a_2,\ldots,a_m$ 两两不同（也就是说是一条简单路径或简单圈），并且 $a_2,\ldots,a_{m-1}$ 的度数都为 $2$，并且删除这上面所有边后不影响 $a_2,\ldots,a_{m-1}$ 以外点的（强）连通性。

定义一张图是可耳分解的，当且仅当可以每次从中删去一个耳，并且最终所有边都被删除。

我们有如下定理：

**一张有向图是可耳分解的，当且仅当它强连通。**

**一张无向图是可耳分解的，当且仅当它边双联通。**

上一条定理是用来做那道 open cup 题的，而下一条则是做本题的。

于是我们有一个 naive 算法，倒做耳分解，往一个空图中不断加耳。

令 $f(S)$ 表示包含集合 $S$ 中所有点的最小权双连通分量，枚举与 $S$ 不交的点集 $T$，将 $T$ 连成耳后两端与 $S$ 中的某两个点连接即可，时间复杂度为 $O(3^n\times \operatorname{poly}(n))$。

但是 naive 算法还是 naive 算法，就算能过这题也过不了那个有向图版本，我们进行一个优化。

上面将耳看做了一个整体，但我们不妨将耳逐步加入，具体地，令 $f(S,i,j)$ 表示当前考虑了 $S$ 中的点，但是 $S$ 中最后加入的一个耳还是不完整的，耳伸出去部分的一个端点是 $i$，最终需要与 $j$ 连接上，此时已经加入的所有边的最小权值和。

那么转移只要每次枚举耳上 $i$ 的后继即可。

时间复杂度为 $O(2^n\times \operatorname{poly}(n))$，注意实现细节。

目前这份代码是本题最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m,x,y,z,d[20][20][2],dp[1<<12][14][14][2],f[1<<12];
int main () {
	scanf("%d",&t);
	for (int ii=1;ii<=t;ii++) {
		memset(d,0x2f,sizeof(d));
		memset(dp,0x2f,sizeof(dp));
		memset(f,0x2f,sizeof(f));
		scanf("%d%d",&n,&m);
		for (int i=1;i<=m;i++) {
			scanf("%d%d%d",&x,&y,&z);
			x--,y--;
			if (z<d[x][y][0]) {d[x][y][1]=d[x][y][0],d[x][y][0]=z;}
			else if (z<d[x][y][1]) {d[x][y][1]=z;}
			swap(x,y);
			if (z<d[x][y][0]) {d[x][y][1]=d[x][y][0],d[x][y][0]=z;}
			else if (z<d[x][y][1]) {d[x][y][1]=z;}
		}
		for (int i=0;i<n;i++) {f[1<<i]=0;}
		for (int i=1;i<(1<<n);i++) {
			for (int j=0;j<n;j++) {
				if (!(i&(1<<j))) {continue;}
				for (int k=0;k<n;k++) {
					if (!(i&(1<<k))) {continue;}
					f[i]=min(f[i],dp[i][j][k][1]+d[j][k][0]);
				}
			}
			if (f[i]<0x2f2f2f2f) {
				for (int j=0;j<n;j++) {
					if (i&(1<<j)) {continue;}
					for (int k=0;k<n;k++) {
						if (!(i&(1<<k))) {continue;}
						f[i|(1<<j)]=min(f[i|(1<<j)],f[i]+d[j][k][0]+d[j][k][1]);
					}
				}
				for (int j=0;j<n;j++) {
					if (!(i&(1<<j))) {continue;}
					for (int k=0;k<n;k++) {
						if (!(i&(1<<k))) {continue;}
						for (int l=0;l<n;l++) {
							if (i&(1<<l)) {continue;}
							dp[i|(1<<l)][l][k][0]=min(dp[i|(1<<l)][l][k][0],f[i]+d[j][l][0]);
							if (j!=k) {f[i|(1<<l)]=min(f[i|(1<<l)],f[i]+d[j][l][0]+d[k][l][0]);}
						}
					}
				}
			}
			for (int j=0;j<n;j++) {
				if (!(i&(1<<j))) {continue;}
				for (int k=0;k<n;k++) {
					if (!(i&(1<<k))) {continue;}
					if (min(dp[i][j][k][0],dp[i][j][k][1])==0x2f2f2f2f) {continue;}
					for (int l=0;l<n;l++) {
						if (i&(1<<l)) {continue;}
						dp[i|(1<<l)][l][k][1]=min(dp[i|(1<<l)][l][k][1],
						min(dp[i][j][k][0],dp[i][j][k][1])+d[j][l][0]);
					}
				}
			}
		}
		if (f[(1<<n)-1]==0x2f2f2f2f) {printf("impossible\n");}
		else {printf("%d\n",f[(1<<n)-1]);}
	}
	return 0;
}
```


---

## 作者：juju527 (赞：17)

### 前置知识
**耳分解**

感觉耳分解的定义 ix35 讲得很清楚了，~~来复读一下~~。

定义（强）连通图中的**耳**为一条路径 $a,(a_1,a_2,\cdots,a_m)$，满足其为一条简单路径或一个简单环，删除该路径上的所有边后不影响除 $a_2,a_3,\cdots,a_{m-1}$ 之外点的（强）连通性。

不加证明的给出下述两个定理：

1. 一张有向图是可耳分解的，当且仅当它强连通。

2. 一张无向图是可耳分解的，当且仅当它边双联通。

### $\texttt{Solution}$
原题即求包含所有点的最小权边双连通子图。

存在一个先把耳 DP 出来，再枚举子集合并的 $O(3^n\text{poly}(n))$ 的做法，这里不予展开。

重点来讲 $O(2^nn^3)$ 的做法。

设计这样一个 DP 状态：$f_S$ 表示将集合 $S$ 连成边双联通图的最小代价，我们试图增量加入耳，设计一个辅助 DP $g_{S,x,y}$ 表示考虑了集合 $S$，正在处理一个耳，该耳的路径已经走到点 $x$，目标走到点 $y$。

转移较为复杂：
1. 对于耳，形如 $x\to y\to x$ 的情况需要特殊处理（走 $(x,y)$ 的最短边和次短边），我们直接转移 $f$。
	```cpp
	for(int x=0;x<n;x++){
	    if((s>>x)&1)continue;
	    for(int y=0;y<n;y++){
	        if(!((s>>y)&1))continue;
	        if(e[x][y].se==inf)continue;
	        chkmn(f[s|(1<<x)],f[s]+e[x][y].fi+e[x][y].se);
	    }
	}

	```
2. 开始转移一个耳，枚举起点 $z$ 和终点 $y$，满足 $z,y\in S$，枚举走出的第一步 $x$，满足 $x\not\in S$。
   
   特别的，$z,y$ 相同的情况下由于我们不能让转移在 $x$ 下一步直接回到 $z$，（这个情况已在 Case 1 中考虑），我们对 $S$ 加入 $x$ 以规避这样的转移（迎合转移 3）。
   ```cpp
   for(int x=0;x<n;x++){
       if((s>>x)&1)continue;
       for(int y=0;y<n;y++){
           if(!((s>>y)&1))continue;
           for(int z=0;z<n;z++){
               if(!((s>>z)&1))continue;
               if(e[z][x].fi==inf)continue;
               if(y!=z)chkmn(g[s][x][y],f[s]+e[z][x].fi);
               else chkmn(g[s|(1<<x)][x][y],f[s]+e[z][x].fi);
           }
       }
   }

   ```
3. 转移 $g_{S,x,y}$，枚举其下一步 $z$，满足 $y\in S,z\not\in S$，我们希望只有 $x\not\in S$ 的 $g_{S,x,y}$ 转移回 $f$，所以除耳的第一步，其它时候我们均保持 $g_{S,x,y}$ 中有 $x\not\in S$。
   
   故转移 2 中将 $S$ 加入 $x$ 可以避免一步回到 $z$。
   ```cpp
   for(int x=0;x<n;x++){
       for(int y=0;y<n;y++){
           if(!((s>>y)&1)||x==y)continue;
           if(g[s][x][y]==inf)continue;
           for(int z=0;z<n;z++){
               if(((s>>z)&1)||x==z)continue;
               if(e[x][z].fi==inf)continue;
               chkmn(g[s|(1<<x)][z][y],g[s][x][y]+e[x][z].fi);
           }
       }
   }

   ```
4. 结束一个耳，从 $g_{S,x,y}$ 转移到 $f_{S+x}$  中。
   ```cpp
   for(int x=0;x<n;x++){
       if((s>>x)&1)continue;
       for(int y=0;y<n;y++){
           if(!((s>>y)&1))continue;
           chkmn(f[s|(1<<x)],g[s][x][y]+e[x][y].fi);
       }
   }

   ```

复杂度显然为 $O(2^nn^3)$。

关键代码已经全部给出，不放完整代码了。

---

## 作者：UltiMadow (赞：10)

神仙状压dp题（

题意即为求边权和最小的边双子图

发现这个 $n$ 很小，很适合状压点集

于是我们设 $f_s$ 为 $s$ 集合的点构成点双的最小代价

考虑将一个新的集合 $t$ 加入 $s$ 所带来的最小代价

有一个结论，这个最小代价必然是把 $t$ 中的点连成一条链然后把链的两端点接入 $s$

但是还有个特例，即 $t$ 中只有一个点，这时我们只需要加入 $t\to s$ 的最小边和次小边即可

设 $e_{i,j,0/1}$ 表示 $i\to j$ 的边权最小/次小值，$g_{s,i,0/1}$ 表示点 $i$ 连入 $s$ 的边的边权最小/次小值，$h_{s,i,j}$ 表示 $s$ 中的点连成一条链，链端点为 $i,j$ 的最小权值和

发现 $g$ 可以直接计算，$h_{s,i,j}=\min_{k\not =i}\{h_{s-k,k,j}+e_{i,k,0}\}$

于是 $f$ 就可以转移了

$f_{s}=\min_{t\subset s}\{f_{s-t}+h_{s,i,j}+g_{s-t,i,0}+g_{s-t,j,0}\}$，也可以只转移进一个点 $f_s=\min_{t\in s}\{f_{s-t}+g_{s-t,t,0}+g_{s-t,t,1}\}$

计算 $g$ 是 $\mathcal O(2^nn^2)$ 的，计算 $h$ 是 $\mathcal O(2^nn^3)$ 的，计算 $f$ 是 $\mathcal O(3^nn^2)$，所以总复杂度 $\mathcal O(2^nn^3+3^nn^2)$

有个细节就是如果把 $f,g,h$ 的初始值全部设成 `0x3f3f3f3f` 由于 $f$ 转移有四个数相加，所以可能会爆 `int`（开 `long long` 也没用），所以初始值要小于 `INT_MAX/4`

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 100
using namespace std;
const int inf=(0x7f7f7f7f)/5;
int T,n,m;
int e[MAXN][MAXN][2],h[1<<12][15][15];
int f[1<<12],g[1<<12][15][2];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				e[i][j][0]=e[i][j][1]=inf;
		for(int i=0;i<(1<<n);i++)f[i]=inf;
		for(int i=0;i<(1<<n);i++)
			for(int j=1;j<=n;j++)g[i][j][0]=g[i][j][1]=inf;
		for(int i=0;i<(1<<n);i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)h[i][j][k]=inf;
		for(int i=1;i<=m;i++){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			if(w<e[u][v][0])e[u][v][1]=e[u][v][0],e[u][v][0]=w;
			else if(w<e[u][v][1])e[u][v][1]=w;
			e[v][u][0]=e[u][v][0];e[v][u][1]=e[u][v][1];
		}
		for(int i=1;i<=n;i++)
			for(int s=0;s<(1<<n);s++){
				if(s&(1<<(i-1)))continue;
				for(int j=1;j<=n;j++)
					if(s&(1<<(j-1))){
						if(e[i][j][0]<g[s][i][0])g[s][i][1]=g[s][i][0],g[s][i][0]=e[i][j][0];
						else if(e[i][j][0]<g[s][i][1])g[s][i][1]=e[i][j][0];
						if(e[i][j][1]<g[s][i][0])g[s][i][1]=g[s][i][0],g[s][i][0]=e[i][j][1];
						else if(e[i][j][1]<g[s][i][1])g[s][i][1]=e[i][j][1];
					}
			}
		for(int i=1;i<=n;i++)h[1<<(i-1)][i][i]=0;
		for(int s=0;s<(1<<n);s++)
			for(int i=1;i<=n;i++){
				if(!(s&(1<<(i-1))))continue;
				for(int j=1;j<=n;j++){
					if(!(s&(1<<(j-1))))continue;
					if(i==j)continue;
					for(int k=1;k<=n;k++)
						if(k!=i&&(s&(1<<(k-1))))
							h[s][i][j]=min(h[s][i][j],h[s^(1<<(i-1))][k][j]+e[i][k][0]);
				}
			}
		f[0]=0;
		for(int i=1;i<=n;i++)f[1<<(i-1)]=0;
		for(int s=1;s<(1<<n);s++){
			for(int i=1;i<=n;i++)
				if(s&(1<<(i-1))){
					int ns=1<<(i-1);
					if(!(s^ns))break;
					f[s]=min(f[s],f[s^ns]+h[ns][i][i]+g[s^ns][i][0]+g[s^ns][i][1]);
				}
			for(int t=(s-1)&s;t;t=(t-1)&s)
				for(int i=1;i<=n;i++)
					if(t&(1<<(i-1)))
						for(int j=1;j<=n;j++)
							if(i!=j&&(t&(1<<(j-1))))
								f[s]=min(f[s],f[s^t]+h[t][i][j]+g[s^t][i][0]+g[s^t][j][0]);
		}
		if(f[(1<<n)-1]>=inf)puts("impossible");
		else printf("%d\n",f[(1<<n)-1]);
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：6)

**P5776**

如果你不知道耳分解，你可能会在做此题时吃大亏。

可能不完全严谨，建议看 ix35 论文原文。

对于任意一个是边双的原图，我们认为从一个初始子图为简单环的 $G_0$ 开始，对于 $G_i \rightarrow G_{i + 1}$，从边集的补集里选一个当且仅当路径端点在 $G_i$ 中的路径并入 $G_i$ 中得到 $G_{i + 1}$，最后可以得到原图。

对于这个路径就是耳，注意路径端点是可重复的，并且一条边在这个过程中只会被加入一次。

这个可以证明充要性。简单讲一下，必要性是因为任意每次拓展加入的都在原图上组成了一个简单环，所以肯定一直是边双；

充分性可以考虑构造一棵 $1$ 为根的 dfs 树，初始随便钦定一个和 $1$ 相连的非树边 $(1,x)$，将两点树上路径和该边构造初始简单环 $G_0$，在 $G_i$ 的点集 $V'$ 未满秩时每次找到一个 dfs 树上父亲在 $G_i$ 且自己不在 $G_i$ 中的点 $p$（在未满秩前显然存在这样的点），然后子树内随便找一个返祖边，设其连向 $p$ 的祖先 $u$ 以及 $p$ 的子孙 $v$，那么 $u$ 先走返祖边到 $v$ 然后走到 $p$ 的父亲去就是一个耳；如果 $V'$ 满秩了就每次把所有没加进的边扔进去就行了。

可以发现这样任意时刻，$G_i$ 中的点都是一个和 $1$ 联通的连通块。自然是对的。

这只是为了解决这道题而做的前置知识，如果你没看懂建议去看一下 ix35 原文，很好理解的。

------------------------------------------------------

回到这道题，那么我们可以状压 dp 模拟耳分解。维护 $f(S)$ 表示 $S$ 中的节点构成边双的最小花费，由于是最小花费我们可以不记录边集的选择情况，因为状压 dp 的过程肯定能算到所有可能出现的分解情况，重新算一条边一定不优。

一个比较显然的转移是维护一下 $E(T,x,y)$ 表示点集为 $T$，且 $x,y \in T$，从 $x$ 走到 $y$ 经过 $T$ 中所有点的最小边权和。

转移的时候枚举子集，令 $f(S) \leftarrow f(S/T) + \min_{x,y \in T} E(T,x,y) + \min_{a,b\in S/T} e_{a,x} + e_{b,y}$ 即可模拟一次加耳的过程。

当然你也可以直接枚举一个 $E(T \cup \{a,b\},a,b)$ 来算，毛姑姑下来可能是 $O(3 ^ n \times n ^ 2)$，剪点枝肯定跑的很快。

更快的理论复杂度做法是我们套路化的不一次加完一个耳，设 $dp(S,x,y)$ 表示 $S$ 中有一部分点正在进行加耳的步骤，并且当前已经加到了 $x$，而加耳的过程在末端点是 $y$ 时会结束时的最小边权和，再去转移原本的 $f(S)$。

发现你肯定能做到 $O(2 ^ n \times Poly(n))$ 了，不过你发现有很多 corner：

- 存在直接向外伸出一个点后回来的情况，直接暴力枚举解决；

- 由于 $dp(S,x,y)$ 只能记录两个节点，转移可能会出现从原本在 $G_i$ 的一个节点 $x$ 走到 $y$ 去经过同一条边走回来的情况，所以要多设一维，即 $dp(S,x,y,1/0)$ 新增一个维表示当前加耳的过程中，$x$ 是/不是当前耳按照枚举顺序下的第二个节点。

- 然后就直接让 $dp(S,x,y,1)$ 才能向 $f$ 数组更新，其它转移照常即可。发现这时候也会少算“从 $G_i$ 走出去找到一个点然后又走回一个在 $G_i$ 中但不同于出发点”的情况，照样枚举算就好了。

时间复杂度 $O(2 ^ n \times n ^ 3)$，自己的代码 corner 判的不好于是无耻地贺了 ix35 的代码。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = (1 << 12) + 5 , Inf = 0x3f3f3f3f;
int n,m,w[25][25][2],dp[Len][16][16][2],f[Len];
inline void solve()
{
	memset(w , 0x3f , sizeof w);
	memset(dp , 0x3f , sizeof dp);
	memset(f , 0x3f , sizeof f);
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y,ww;scanf("%d %d %d",&x,&y,&ww);x -- , y --;
		if(w[x][y][0] > ww){w[x][y][1] = w[x][y][0];w[x][y][0] = ww;}
		else w[x][y][1] = min(w[x][y][1] , ww);
		swap(x , y);
		if(w[x][y][0] > ww){w[x][y][1] = w[x][y][0];w[x][y][0] = ww;}
		else w[x][y][1] = min(w[x][y][1] , ww);
	}
	for(int i = 0 ; i < n ; i ++) f[1 << i] = 0;
	for(int i = 1 ; i < (1 << n) ; i ++)
	{
		//printf("%d %d\n",i,f[i]);
		for(int j = 0 ; j < n ; j ++)
		{
			if(!((i >> j) & 1)) continue;
			for(int k = 0 ; k < n ; k ++) 
			{
				if(!((i >> k) & 1)) continue;
				f[i] = min(f[i] , dp[i][j][k][1] + w[j][k][0]);
			}
		}
		if(f[i] < Inf)
		{
			//case 1:直接伸出去一个点后回来，枚举 S 内端点和伸出去的点 
			for(int j = 0 ; j < n ; j ++)
			{
				if(!((i >> j) & 1)) continue;
				for(int k = 0 ; k < n ; k ++)
				{
					if((i >> k) & 1) continue;
					f[i | (1 << k)] = min(f[i | (1 << k)] , f[i] + w[j][k][0] + w[j][k][1]);	
				}	
			}
			//case2:伸出去一个带中转点的环，依次枚举这三个点，顺便 
			for(int j = 0 ; j < n ; j ++)//1,2,4,3 这个环没有枚到。 
			{
				if(!((i >> j) & 1)) continue;
				for(int k = 0 ; k < n ; k ++)
				{
					if((i >> k) & 1) continue;
					for(int l = 0 ; l < n ; l ++)
					{
						if(!((i >> l) & 1)) continue;
						dp[i | (1 << k)][k][l][0] = min(dp[i | (1 << k)][k][l][0] , f[i] + w[j][k][0]);
						//if((i | (1 << k)) == 11 && l == 0 && k == 3) printf("!!!%d\n",dp[i | (1 << k)][k][l][0]);
						if(j != l) f[i | (1 << k)] = min(f[i | (1 << k)] , f[i] + w[j][k][0] + w[k][l][0]);
					}
				}
			}
		}
			//case3:暴力转移
			for(int j = 0 ; j < n ; j ++)
			{
				if(!((i >> j) & 1)) continue;
				for(int k = 0 ; k < n ; k ++)//枚举的耳的另一个端点 
				{
					if(!((i >> k) & 1)) continue;
					if(min(dp[i][j][k][0] , dp[i][j][k][1]) == Inf) continue;
					for(int l = 0 ; l < n ; l ++)
					{
						if((i >> l) & 1) continue;
						dp[i | (1 << l)][l][k][1] = min(dp[i | (1 << l)][l][k][1] , 
						min(dp[i][j][k][0] , dp[i][j][k][1]) + w[j][l][0]);
					}
				}
			}			
		
	}
	if(f[(1 << n) - 1] == Inf) puts("impossible");
	else printf("%d\n",f[(1 << n) - 1]);
}
signed main()
{
	int T;scanf("%d",&T);while(T --) solve();
	return 0;
}
```

---

## 作者：sdyzpf (赞：5)

## 题意
给你一张有重边、无自环的无向正权图，求出它边权和最小的边双连通生成子图的边权和。

## 思路简述

感觉截至 $2025/4/24$ 的题解对状压部分的讲解不够详细，所以专门开一篇题解讲状压部分。

关于耳分解的定义，网络上能搜集到多种版本，下文中使用“将一张图不断删去耳(包括所有边和除两端外的所有点)，使得最后仅剩环 $G_0$”这一版本进行转移。

考虑思考其逆过程，分为两部分，找到 $G_0$，然后添加耳。

令 $f_{msk}$ 为原图点集为 $msk$ 导出子图的边权和最小的边双连通生成子图的边权和；$e_{i,j}$ 为连接 $i,j$ 两点的最小边；$dp_{msk,i,j}$ 为考虑 $msk$ 中的点，当前存在一个未构建完成的耳（即一条链，链的一端在已经边双连通的部分上），除链外所有点边双连通，链不在边双连通部分上的端点为 $i$，且最终链会接到 $j$ 上的最小边权和。

我们会有以下几种转移（注意转移顺序，$1$ 必须在 $2,3$ 前）：

1. $f_{msk}=\min (f_{msk},dp_{msk,i,j}+e_{i,j})$，即将链（此处断句）接到 $j$ 上，完成耳的构建。
2. $dp_{msk,i,j}=\min(dp_{msk,i,j},f_{msk})$，即开始构造一个两端分别为 $i,j$ 的耳。
3. $dp_{msk|(1<<v),v,j}=\min(dp_{msk|(1<<v),v,j},dp_{msk,u,j}+e_{u,v})$，即对链进行扩张。

对于一开始找 $G_0$ 环的部分，我们也可以使用相似的转移，甚至将两部分共用一个数组进行。

但我们发现上述转移过程实际上是存在问题的，对于一个二元环，两点间的最小边会被重复经过。解决方案是预处理两点间的最小边和次小边，特判二元环。此外，在转移 $1$ 中，我们需保证不会构建出二元环。我的处理方案是给 $dp$ 数组增设 $0/1$ 维，表示当前的链能否停止扩张，与 $j$ 相接。题解区中还给出了其他处理手段，然而本人看不懂。

至此本题解决完毕。

## code

``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,e[12][12][2],f[(1<<12)+5],dp[(1<<12)+5][12][12][2];
inline bool isin(int msk,int p){return (msk>>p)&1;}
inline void solve(){
    memset(e,0x1f,sizeof(e));
    memset(f,0x1f,sizeof(f));
    memset(dp,0x1f,sizeof(dp));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        if(e[u][v][0]>w) e[u][v][1]=e[u][v][0],e[u][v][0]=w;
        else if(e[u][v][1]>w) e[u][v][1]=w;
        swap(u,v);
        if(e[u][v][0]>w) e[u][v][1]=e[u][v][0],e[u][v][0]=w;
        else if(e[u][v][1]>w) e[u][v][1]=w;
    }
    //找G0环部分
    for(int s=0;s<n;s++)
        for(int t=0;t<n;t++)//特判二元环
            if(s!=t) f[(1<<s)|(1<<t)]=min(f[(1<<s)|(1<<t)],e[s][t][0]+e[s][t][1]);
    for(int s=0;s<n;s++)//枚举G0环的起点(起点即终点)
        for(int k=0;k<n;k++)//走一步
            dp[(1<<s)|(1<<k)][k][s][1]=e[s][k][0];
    //加耳部分
    for(int msk=1;msk<(1<<n);msk++){
        //特判二元环
        for(int s=0;s<n;s++)
            for(int t=0;t<n;t++)
                if(isin(msk,s)&&!isin(msk,t))
                    f[msk|(1<<t)]=min(f[msk|(1<<t)],f[msk]+e[s][t][0]+e[s][t][1]);
        //完成当前的耳/G0环
        for(int s=0;s<n;s++)
            for(int t=0;t<n;t++)
                f[msk]=min(f[msk],dp[msk][s][t][0]+e[s][t][0]);//通过 0/1 维无视二元环
        //枚举耳的起点和终点,新开一个耳
        for(int s=0;s<n;s++)
            for(int t=0;t<n;t++)
                if(isin(msk,s)&&isin(msk,t))
                    dp[msk][s][t][s==t]=min(dp[msk][s][t][s==t],f[msk]);//起点终点相等要注意排除二元环
        //在扩张当前的链/G0环
        for(int s=0;s<n;s++)
            for(int t=0;t<n;t++)
                for(int k=0;k<n;k++)//我们要从 s 走到 k
                    for(int op:{0,1})
                        if(isin(msk,s)&&isin(msk,t)&&!isin(msk,k)){
                            int nop=op&(s==t);
                            dp[msk|(1<<k)][k][t][nop]=min(dp[msk|(1<<k)][k][t][nop],dp[msk][s][t][op]+e[s][k][0]);
                        }
    }
    if(f[(1<<n)-1]<1e9) cout<<f[(1<<n)-1]<<'\n';
    else cout<<"impossible\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：zzzyyyyhhhhh (赞：2)

ix35 的耳分解做法太神仙了，所以介绍一个状压 dp 做法。

最后的答案一定是几个强连通分量加上一些重合的边（2 条边都连接 $u,v$ 则这两条边重合）构成，所以如果我们求出 $f_S$ 表示使点集 $S$ 中所有点强连通的最小花费后可以子集枚举在 $O(3^nm)$ 的复杂度内求出答案。所以我们现在只需要求出 $f_S$。

因为边权非负，所以如果少选一条边且不改变连通性的话一定少选最优，所以达到 $f_S$ 的边集所构成的子图一定是一个环或者几个环的并（如果是几个环的并则每两个环最多相交一个点）。我们先求出来所有环的答案，可以枚举环的起点，然后 $O(2^nn)$ 求出 $f_S$。对于环的并的情况再 $O(3^nn)$ 子集枚举求出。

最终复杂度 $O(3^n(n+m)+2^nn)$，远不如耳分解，所以建议去学习 ix35 的耳分解。

最后给出代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 13,MX=1e9+1;
int n,m,f[1<<12],g[1<<12][12];
struct edge{int t,w;};
vector<edge> a[N];
int e[N][N];
signed main()
{
	int tt;
	cin>>tt;
	while(tt--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)a[i].clear();
		memset(f,0x3f,sizeof(f));
		memset(e,0x3f,sizeof(e));
		int x,y,z;
		for(int i=1;i<=m;i++)
		{
			cin>>x>>y>>z;
			a[x].push_back({y,z});
			a[y].push_back({x,z});
			e[x][y]=min(e[x][y],z);
			e[y][x]=min(e[y][x],z);
		}
		for(int i=1;i<=n;i++)e[i][i]=0;
		for(int s=1;s<=n;s++)
		{
			memset(g,0x3f,sizeof(g));
			g[1<<(s-1)][s-1]=0;
			for(int i=1;i<(1<<n);i++)
				for(int j=1;j<=n;j++)
				{
					if(g[i][j-1]>MX)continue;
					for(auto p:a[j])
						if(!(i&(1<<(p.t-1))))
						g[i|(1<<(p.t-1))][p.t-1]=min(g[i|(1<<(p.t-1))][p.t-1],g[i][j-1]+p.w);
					if(__builtin_popcount(i)>2)f[i]=min(f[i],g[i][j-1]+e[s][j]);
				}
		}
		for(int i=1;i<(1<<n);i++)
			for(int j=1;j<=n;j++)
				if(i&(1<<(j-1)))
					for(int p=((1<<n)-1)^i;p;p=(p-1)&(((1<<n)-1)^i))
						f[i|p]=min(f[i|p],f[i]+f[p|(1<<(j-1))]);
		for(int i=0;i<n;i++)g[1<<i][i]=0,f[1<<i]=0;
		for(int i=1;i<(1<<n);i++)
			for(int j=(i-1)&i;j;j=(j-1)&i)
			{
				int st=i^j,mi=1e9,smi=1e9;
				for(int p=1;p<=n;p++)
					if(st&(1<<(p-1)))
						for(auto u:a[p])
							if(j&(1<<(u.t-1)))
							{
								if(u.w<mi)smi=mi,mi=u.w;
								else smi=min(smi,u.w);
							}
				assert((j|st)==i);
				f[i]=min(f[i],f[j]+f[st]+mi+smi);
			}
		if(f[(1<<n)-1]<MX)cout<<f[(1<<n)-1]<<'\n';
		else cout<<"impossible\n";
	}
}
```

---

## 作者：Purslane (赞：2)

# Solution

本题是无向图最小权耳分解板子题。略微记录一些耳分解相关内容。

----------

定义无向图 $G=(V,E)$ 对其导出子图 $G'=(V',E')$ 存在耳，当前仅当可以找到一组顶点 $(x_1,x_2,\dots,x_{t-1},x_t)$，其中 $x_1,x_t \in V$，$\{x_2,x_3,\dots,x_{t-1}\} = V / V'$，且 $\forall 1 \le i \le t-1$，$x_i$ 和 $x_{i+1}$ 有边，且除了 $x_1$ 和 $x_t$ 外这组顶点两两不同。这样的一组顶点称为 **$G$ 对 $G'$ 的耳**，如果 $x_1 \neq x_t$ 称为 **$G$ 对 $G'$ 的开耳。**

> 直观地看，就像 $G'$ 外面挂了一个“耳朵”形成了 $G$。定义并不关注 $V / V'$ 和 $V'$ 之间的连边情况，也就是完全图任何点集是他的一个耳。

对于有向图，也容易定义他的“耳”，只要确定边的方向一定即可。

----------

定义无向图的耳分解为：

取无向图 $G$ 的若干个导出子图 $G_0=(V_0,E_0)$，$G_1 = (V_1,E_1)$，$\dots$，$G_t=(V_t,E_t)$。

其中 $G_t=G$，$V_0 \subset V_1 \subset \cdots \subset V_t$；$G_0$ 存在哈密顿回路（就是能形成一个环），且 $\forall 1 \le i \le t$，$G_i$ 对 $G_{i-1}$ 的耳存在。

这样的耳构成的集合称为无向图的耳分解。

特别的，如果每个耳都是开耳，称为无向图的开耳分解。

同样容易定义有向图的耳分解。

----------

无向图的耳分解实际上刻画了图的双连通性。

$\rm Theorem \ 1$：**无向图存在耳分解当且仅当无向图边双联通**。


$\rm Theorem \ 2$：**无向图存在开耳分解当且仅当无向图点双联通**。


$\rm Theorem \ 3$：**有向图存在耳分解当且仅当有向图强联通**。

定理证明：

必要性证明逆否命题。比较显然：存在割边、割点、多个极大强联通分量，显然就找不到耳

充分性证明考虑构造性证明。以 $\rm Theorem \ 1$ 为例，我们求出原图的一棵 DFS 树。将包含根的任意一个环当做 $G_0$。在 $G$ 扩张为原图之前，必定能找到一个点 $u$ 不在 $G$ 中，它存在返祖边且另一端点在 $G$ 中。那么很容易将这个耳朵挂在原图上。由于不存在割边，这样的 $u$ 一定能找到。

----------

回到本题，我们本质上在求解无向图的最小权耳分解。

考虑使用**状压 DP**，层层增加耳。

设 $dp_{S,i,j}$ 为“将 $S$ 中的点放进耳分解中，目前存在一个不完整的耳并且最后一个节点是 $i$，这只耳最后要连到 $j$ 上”所需的最小代价即可。

复杂度 $O(n^32^n)$。

- Q：为什么要记录 $j$？

- A：否则你无法区分哪些点属于当前耳，哪些点属于之前确定好的耳。

一个小小的细节：耳可能仅含有一对重边，也可能只包含一个外部点，这个特判。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20,MAXM=(1<<12)+10,INF=0x3f3f3f3f3f3f3f3f;
int T,n,m,dp[MAXM][MAXN][MAXN],ans[MAXM];
vector<int> G[MAXN][MAXN];
int calc(int u,int v) {
	if(G[u][v].empty()) return INF;
	return G[u][v][0];
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		ffor(i,1,n) ffor(j,1,n) G[i][j].clear();
		memset(dp,0x3f,sizeof(dp)),memset(ans,0x3f,sizeof(ans));
		ffor(i,1,m) {
			int u,v,w;
			cin>>u>>v>>w;
			G[u][v].push_back(w),G[v][u].push_back(w);
		}
		ffor(u,1,n) ffor(v,1,n) {
			sort(G[u][v].begin(),G[u][v].end());
			if(u<v) {
				if(G[u][v].size()>=2) ans[(1<<u-1)+(1<<v-1)]=G[u][v][0]+G[u][v][1];
				dp[(1<<u-1)+(1<<v-1)][u][v]=dp[(1<<u-1)+(1<<v-1)][v][u]=calc(u,v);
			}
		}
		ffor(s,1,(1<<n)-1) {
			ffor(u,1,n) ffor(v,1,n) if(!(s&(1<<u-1))&&(s&(1<<v-1))) ffor(w,1,n) if(s&(1<<w-1)) dp[s|(1<<u-1)][u][w]=min(dp[s|(1<<u-1)][u][w],ans[s]+calc(u,v));
			ffor(u,1,n) ffor(v,1,n) if((s&(1<<u-1))&&(s&(1<<v-1))&&u!=v) ffor(k,1,n) if(!(s&(1<<k-1))) {
				dp[s|(1<<k-1)][k][v]=min(dp[s|(1<<k-1)][k][v],dp[s][u][v]+calc(k,u));
				if(G[u][k].size()&&G[k][v].size()) ans[s|(1<<k-1)]=min(ans[s|(1<<k-1)],min(ans[s],dp[s][u][v])+calc(k,u)+calc(k,v));
			}
			ffor(u,1,n) ffor(v,1,n) if((s&(1<<u-1))&&!(s&(1<<v-1))) if(G[u][v].size()>=2) ans[s|(1<<v-1)]=min(ans[s|(1<<v-1)],ans[s]+G[u][v][0]+G[u][v][1]);
		}
		if(ans[(1<<n)-1]<INF) cout<<ans[(1<<n)-1]<<'\n';
		else cout<<"impossible\n";
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

题意：给定一张带权无向图，求最小生成边双连通图，$n\le 12$。

题解：

考虑用 ear decomposition 的过程刻画合法条件。我们知道，一张无向图是边双连通图，等价于该图存在 ear decomposition。

因此容易想到状压 dp，以已经被耳覆盖的点集作为状态，每次扩展一个耳进行转移。直接暴力做容易做到 $\mathcal O(3^n\mathrm{poly}(n))$。

每次以一个耳为整体转移显然是不优的，不如考虑分步转移，每次扩展耳的一个点。具体而言，设 $f_{S}$ 为耳分解已经覆盖了 $S$ 中点的最小代价，$g_{S,x,y}$ 为耳分解已经覆盖了 $S$ 中点，目前正在扩展一个新的耳，当前在点 $x$，终点为 $y$ 的最小代价。

转移：

- 扩展一个形如 $x\to y\to x$ 的耳，其中 $x\in S$。这时候我们会取 $(x,y)$ 间的最小和次小边，从 $f_{S}$ 转移到 $f_{S\cup \{x\}}$。

- 开始一个形如 $x\to y\to \dots \to z$ 的耳，其中 $x,z\in S,y\notin S$。这时候应当从 $f_{S}$ 转移到 $g_{S,y,z}$。但是注意，如果 $x=z$，这种情况是错误的（已经被第一条考虑，在这里会算两次最小边），因此这时候应当转移到 $g_{S\cup\{y\},y,z}$，并在分步转移的时候限制转移点不在 $S$ 中。

- 分步转移：设目前状态为 $g_{S,x,y}$，那么我们枚举下一步走到 $z$，转移到 $g_{S\cup \{x\},z,y}$。

- 结束一个耳：从 $g_{S,x,y}$ 转移到 $f_{S\cup\{x\}}$。

最终答案即 $f_{\{1,2,\dots ,n\}}$。

时间复杂度 $\mathcal O(2^nn^3)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll INF=1e6;
ll T,n,m,dp[(1<<13)+9][14][14],f[(1<<13)+9];
ll e[14][14][2];
void solve(){
    n=read(),m=read();
    rep(i,0,n){
        rep(j,0,n)e[i][j][0]=e[i][j][1]=INF;
    }
    rep(i,1,m){
        ll x=read(),y=read(),z=read();
        if(z<e[x][y][0])e[x][y][1]=e[x][y][0],e[x][y][0]=z;
        else e[x][y][1]=min(e[x][y][1],z);
        swap(x,y);
        if(z<e[x][y][0])e[x][y][1]=e[x][y][0],e[x][y][0]=z;
        else e[x][y][1]=min(e[x][y][1],z);
    }
    /*dp[S][i][j] 表示目前已经加入了 S 中的点
    当前扩展的耳，目前走到 i，终点是 j 的最小代价*/
    rep(i,0,(1<<n)){
        rep(j,0,n){
            rep(k,0,n)dp[i][j][k]=INF;
        }
        f[i]=INF;
    }
    rep(i,1,n)f[1<<(i-1)]=0;
    rep(S,0,(1<<n)-1){
        if(f[S]<INF){
            //转移 x->y->x
            rep(x,1,n){
                if(!((S>>(x-1))&1))continue;
                rep(y,1,n){
                    if((S>>(y-1))&1)continue;
                    f[S|(1<<(y-1))]=min(f[S|(1<<(y-1))],f[S]+e[x][y][0]+e[x][y][1]);
                }
            }
            //转移 x->y->....z
            rep(x,1,n){//起点
                if(!((S>>(x-1))&1))continue;
                rep(y,1,n){//第一步
                    if((S>>(y-1))&1)continue;
                    rep(z,1,n){//终点
                        if(!((S>>(z-1))&1))continue;
                        if(x==z)dp[S|(1<<(y-1))][y][z]=min(dp[S|(1<<(y-1))][y][z],f[S]+e[x][y][0]);
                        else dp[S][y][z]=min(dp[S][y][z],f[S]+e[x][y][0]);
                    }
                }
            }
        }
        rep(x,1,n){
            rep(y,1,n){
                if(!((S>>(y-1))&1))continue;
                if(x==y)continue;
                if(dp[S][x][y]>=INF)continue;
                rep(z,1,n){
                    if((S>>(z-1))&1)continue;
                    if(x==z)continue;
                    dp[S|(1<<(x-1))][z][y]=min(dp[S|(1<<(x-1))][z][y],dp[S][x][y]+e[x][z][0]);
                }
            }
        }
        rep(x,1,n){
            if((S>>(x-1))&1)continue;
            rep(y,1,n){
                if(!((S>>(y-1))&1))continue;
                f[S|(1<<(x-1))]=min(f[S|(1<<(x-1))],dp[S][x][y]+e[x][y][0]);
            }
        }
    }
    if(f[(1<<n)-1]<INF)write(f[(1<<n)-1]),putchar('\n');
    else puts("impossible");
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：happybob (赞：1)

考虑生成边双联通子图，只需要从一个开始不断加耳形成。

朴素做法是记 $f_S$ 表示将集合 $S$ 内的点连成边双联通图的最小权值和。转移枚举 $S$ 补集的所有子集转移。这个和枚举子集是一样的，复杂度不少于 $O(3^n)$，无法通过。

考虑优化枚举过程。改变状态。记 $f_{S,i,j}$ 表示当前已经在边双联通图和耳上的点集合为 $S$，现在在耳上拓展到了点 $i$，钦定了耳的终点为 $j$ 的最小值。这样转移只需要枚举耳下一个不在集合内的任一点转移，或者直接连到 $j$ 结束耳。

但写了写发现其实不对，因为我们没有处理过重边的问题。首先重边必然只保留最小的两条，但是转移时并没有处理过一个仅包含两个点的开耳拓展时要选两条边。于是把状态加上一个 $0/1$ 表示目前这个 $i$ 是否是刚刚从耳的第一个点出来，且耳的起点等于终点。转移简单改改就行了。复杂度 $O(2^nn^3)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int N = 13, INF = (int)1e9;

int f[1 << N][N][N][2], w[N][N][2];
int t, n, m;

void chkmin(int& x, int y)
{
	x = min(x, y);
}

inline bool chk(int S, int i)
{
	return (S >> (i - 1)) & 1;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 0; i < (1 << n); i++)
		{
			for (int j = 0; j <= n; j++)
			{
				for (int k = 0; k <= n; k++)
				{
					f[i][j][k][0] = f[i][j][k][1] = (int)1e9;
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++) w[i][j][0] = w[i][j][1] = (int)1e9;
		}
		for (int i = 1; i <= m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			if (::w[u][v][0] > w)
			{
				::w[u][v][1] = ::w[u][v][0];
				::w[u][v][0] = w;
			}
			else if (::w[u][v][1] > w)
			{
				::w[u][v][1] = w;
			}
			if (::w[v][u][0] > w)
			{
				::w[v][u][1] = ::w[v][u][0];
				::w[v][u][0] = w;
			}
			else if (::w[v][u][1] > w)
			{
				::w[v][u][1] = w;
			}
		}
		for (int i = 1; i <= n; i++)
		{
			f[1 << (i - 1)][0][0][0] = 0;
		}
		for (int i = 1; i < (1 << n); i++)
		{
			for (int j = 1; j <= n; j++)
			{
				for (int k = 1; k <= n; k++)
				{
					// case1: 从 0 转移
					// 1.1: x != k
					for (int x = 1; x <= n; x++)
					{
						if (w[j][x][0] != INF && j != k && !chk(i, x))
						{
							chkmin(f[i | (1 << (x - 1))][x][k][0], f[i][j][k][0] + w[j][x][0]);
						}
					}
					// 1.2 trans to k
					if (w[j][k][0] != INF)
					{
						chkmin(f[i][0][0][0], f[i][j][k][0] + w[j][k][0]);
					}
					// case2: 从 1 转移
					// 2.1: x != k
					for (int x = 1; x <= n; x++)
					{
						if (w[j][x][0] != INF && j != k && !chk(i, x))
						{
							chkmin(f[i | (1 << (x - 1))][x][k][0], f[i][j][k][1] + w[j][x][0]);
						}
					}
					// 2.2 x = k
					if (w[j][k][1] != INF)
					{
						chkmin(f[i][0][0][0], f[i][j][k][1] + w[j][k][1]);
					}
				}
			}
			// trans from f[i][0][0][0]
			for (int st = 1; st <= n; st++)
			{
				if (!chk(i, st)) continue;
				for (int ed = 1; ed <= n; ed++)
				{
					if (!chk(i, ed)) continue;
					for (int x = 1; x <= n; x++)
					{
						if (w[st][x][0] != INF && !chk(i, x))
						{
							chkmin(f[i | (1 << (x - 1))][x][ed][st == ed], f[i][0][0][0] + w[st][x][0]);
						}
					}
				}
			}
		}
		if (f[(1 << n) - 1][0][0][0] == INF) cout << "impossible\n";
		else cout << f[(1 << n) - 1][0][0][0] << "\n";
	}
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

求边权最小的点集为原图点集的边双。考虑状压。一个边双可以拆成一个边双加一条链，代价最小即为链两端的点连线加入这个边双。$f_{S}$ 表示点集为 $S$ 的边权最小的边双。

考虑设几个辅助数组。$c_{S,u,v}$ 表示 $S$ 中以 $u,v$ 为端点的链的最小权值和，$g_{S,u,0/1}$ 表示将 $u$ 连到 $S$ 中去的最小/次小代价。$g$ 可以暴力枚举，$c$ 有 $c_{S,u,v}=\min_{k\neq i} h_{S-u,k,v}+w_{u,k}$。
$$
f_{S}=\min_{T\subset S}
\begin{cases}
f_{S-T}+c_{T,u,v}+g_{S-T,u,0}+g_{S-T,v,0} &|T|>1\\
f_{S-T}+g_{S-T,u,0}+g_{S-T,u,1} &|T|=1
\end{cases}
$$
初始值有
$$
\begin{aligned}
f_{\{u\}}=f_{\varnothing}=0\\
c_{\{u\},u,u}=0\\
\end{aligned}
$$

```cpp
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int SS=5009,N=19,inf=0x1f1f1f1f;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int T,n,m,S,w[N][N][2],c[SS][N][N],g[SS][N][2],f[SS];

void cal_g() {
	rep(s,0,S) {
		rep(u,1,n) {
			if(s&(1<<u-1)) continue;
			rep(i,1,n) if(u!=i&&(s&(1<<i-1))) {
				if(w[u][i][0]<g[s][u][1]) g[s][u][1]=w[u][i][0];
				if(g[s][u][1]<g[s][u][0]) swap(g[s][u][1],g[s][u][0]);
				if(w[u][i][1]<g[s][u][1]) g[s][u][1]=w[u][i][1];
			}
		}
	}
}

void cal_c() {
	rep(i,1,n) c[1<<i-1][i][i]=0;
	rep(s,0,S) {
		int cnt=0; rep(i,1,n) if(s&(1<<i-1)) cnt++; if(cnt<=1) continue;
		rep(u,1,n) if(s&(1<<u-1)) {
			rep(v,1,n) if(s&(1<<v-1)) {
				rep(k,1,n) if(k!=u&&(s&(1<<k-1))) {
					c[s][u][v]=min(c[s][u][v],c[s-(1<<u-1)][k][v]+w[u][k][0]);
				}
			}
		}
	}
}

void cal_f() {
	f[0]=0;
	rep(s,1,S) {
		int cnt=0; rep(i,1,n) if(s&(1<<i-1)) cnt++;
		if(cnt==1) {f[s]=0; continue;}
		for(int t=s;t;t=(t-1)&s) {
			int pc=0; rep(i,1,n) if(t&(1<<i-1)) pc++;
			if(pc==1) {
				int u;
				rep(i,1,n) if(t&(1<<i-1)) u=i;
				f[s]=min(f[s],f[s-t]+g[s-t][u][0]+g[s-t][u][1]);
			} else {
				rep(u,1,n) if(t&(1<<u-1)) rep(v,1,n) if(t&(1<<v-1)) {
					f[s]=min(f[s],f[s-t]+c[t][u][v]+g[s-t][u][0]+g[s-t][v][0]);
				}
			}
		}
	}
}

int main() {
	T=read();
	while(T--) {
		memset(w,0x1f,sizeof(w)), memset(c,0x1f,sizeof(c)), memset(g,0x1f,sizeof(g)), memset(f,0x1f,sizeof(f));
		n=read(), m=read(), S=(1<<n)-1;
		rep(i,1,m) {
			int u=read(), v=read(), ww=read();
			if(ww<w[u][v][1]) w[u][v][1]=ww;
			if(w[u][v][1]<w[u][v][0]) swap(w[u][v][0],w[u][v][1]);
			w[v][u][0]=w[u][v][0], w[v][u][1]=w[u][v][1];
		}
		cal_g();
		cal_c();
		cal_f();
		if(f[S]==inf) puts("impossible");
		else printf("%d\n",f[S]);
	}
	return 0;
}
```

---

