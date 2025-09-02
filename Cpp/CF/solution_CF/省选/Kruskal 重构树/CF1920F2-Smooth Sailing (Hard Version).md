# Smooth Sailing (Hard Version)

## 题目描述

本题的两个版本唯一的区别在于 $q$ 的约束条件。只有当两个版本都被解决时，你才能进行 hack。

Thomas 正在环绕一个被海洋包围的岛屿航行。海洋和岛屿可以用一个有 $n$ 行 $m$ 列的网格表示。行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $m$。位于第 $r$ 行第 $c$ 列的格子可以表示为 $(r, c)$。下面是一个有效网格的示例。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/516df36ca6ac022124866d4043411e04ed0cf48c.png) 有效网格示例

网格中有三种类型的格子：岛屿、海洋和海底火山。用 '\#' 表示岛屿格子，'.' 表示海洋格子，'v' 表示海底火山格子。保证至少有一个岛屿格子和至少有一个海底火山格子。保证所有岛屿格子构成一个连通块 $^{\dagger}$，所有海洋格子和海底火山格子构成一个连通块。此外，保证网格的边界（即第 $1$ 行、第 $n$ 行、第 $1$ 列和第 $m$ 列）上没有岛屿格子。

定义从格子 $(x, y)$ 出发的环岛航行为一条满足以下条件的路径：

- 路径的起点和终点都是 $(x, y)$。
- 如果 Thomas 当前在格子 $(i, j)$，他可以移动到 $(i+1, j)$、$(i-1, j)$、$(i, j-1)$、$(i, j+1)$，只要目标格子是海洋格子或海底火山格子且仍在网格内。注意，在一次环岛航行中允许多次经过同一个格子。
- 路径必须环绕岛屿并完全包围它。某条路径 $p$ 完全包围岛屿，指的是如果不经过路径 $p$ 上的格子，仅通过相邻（包括对角线相邻）的格子移动，则无法从任意岛屿格子到达网格边界。下图中，从 $(2, 2)$ 出发，经过 $(1, 3)$，再以另一条路返回 $(2, 2)$ 的路径并未完全包围岛屿，因此不算作一次环岛航行。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/587237f643ee9a450f570eb64a27b00d982a357b.png) 未完全包围岛屿的路径示例

一次环岛航行的安全性定义为：路径上某个格子到最近海底火山的曼哈顿距离 $^{\ddagger}$ 的最小值（注意岛屿格子的存在不影响该距离）。

你有 $q$ 次询问。每次询问为 $(x, y)$，你需要求出从 $(x, y)$ 出发的环岛航行的最大安全性。保证 $(x, y)$ 是海洋格子或海底火山格子。

$^{\dagger}$ 一组格子构成一个连通块，指的是从该组任意一个格子出发，只通过该组内的格子且每次移动到有公共边的相邻格子，可以到达该组内的任意一个格子。

$^{\ddagger}$ 格子 $(r_1, c_1)$ 和 $(r_2, c_2)$ 的曼哈顿距离为 $|r_1 - r_2| + |c_1 - c_2|$。

## 说明/提示

对于第一个示例，下图展示了从 $(1, 1)$ 出发的最优环岛航行。该环岛航行的安全性为 $3$，因为路径上某个格子到最近海底火山的曼哈顿距离的最小值为 $3$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1920F2/b0d58ba7a9650556e586a3235109c2b13f201dd2.png) 最优环岛航行示例

对于第四个示例，注意在一次环岛航行中允许多次经过同一个格子。例如，从 $(7, 6)$ 出发的环岛航行就必须多次经过同一个格子。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9 9 3
.........
.........
....###..
...v#....
..###....
...##...v
...##....
.........
v........
1 1
9 1
5 7```

### 输出

```
3
0
3```

## 样例 #2

### 输入

```
3 3 5
..v
.#.
...
1 2
1 3
2 3
2 1
3 2```

### 输出

```
0
0
0
0
0```

## 样例 #3

### 输入

```
14 13 5
.............
.............
.............
...vvvvvvv...
...v.....v...
...v.###.v...
...v.#.#.v...
...v..v..v...
...v..v..v...
....v...v....
.....vvv.....
.............
.............
.............
1 1
7 7
5 6
4 10
13 6```

### 输出

```
3
0
1
0
2```

## 样例 #4

### 输入

```
10 11 4
...........
..#######..
..#..#..#..
..#.....#..
..#..v..#..
..#.###.#..
..#.#.#.#..
..#...#.#..
..#####.#..
...........
7 6
3 7
6 8
1 1```

### 输出

```
1
2
3
4```

# 题解

## 作者：cjZYZtcl (赞：11)

首先考虑 F1 的做法。

有一个对询问的转化是记 $dis_{x, y}$ 表示离 $(x, y)$ 点的最近的 `v` 到 $(x, y)$ 的曼哈顿距离。

记一条路径的权值为路径上所有点的 $dis$ 的最小值。

则询问相当于查询包围所有 `#` 的路径的权值最大值。

考虑一条如下图的连接 `#` 与地图边缘的横线（或竖线）：（图是原题题面的图，加粗线即为所述的线）

![](https://cdn.luogu.com.cn/upload/image_hosting/5tekn8lk.png)

则有对于一个任意位置的点，只有经过该线奇数次后回到自身才是一条合法的路径（即包围所有 `#` 的路径）。

证明挺显然的，考虑经过该线奇数次后的点一定和起始点在线的不同侧，所以要不经过线而回到起始点就需要绕过所有 `#`，即包围了所有 `#`。

那么 F1 做法就呼之欲出了：

考虑对每个点拆成两个点 $(x, y, 0)$ 与 $(x, y, 1)$，表示经过线偶数/奇数次时到达该点的状态，则存在合法路径当且仅当 $(x, y, 0)$ 和 $(x, y, 1)$ 联通。

对每个询问，按 $dis$ 从大到小加入所有能走的点（即不为 `#` 的点），每加入一种 $dis$，判断询问点的 $(x, y, 0)$ 与 $(x, y, 1)$ 联通情况，如果联通了则说明答案即当前图中最小的 $dis$，这个可以并查集维护，时间复杂度 $O(nmq \log{(nm)})$。

然后考虑 F2 的做法。

#### 做法1

注意到对每个询问依次加入所有点会浪费很多时间，考虑将操作合并。

将询问离线后整体二分，则二分状态 $(l, r, L, R)$ 表示已加入 $dis$ 在 $(R, maxdis]$ 中的点（$maxdis$ 即 $dis$ 的最大值）时所有未联通的点在 $[l, r]$ 范围内。

记 $Mid = \lfloor \frac{L + R}{2} \rfloor$，则将 $dis$ 在 $(Mid, R]$ 中的所有点加入图中，对每个要处理的询问 check 后递归处理即可。

注意这里并查集的修改需要撤销，所以不能用路径压缩，总时间复杂度 $O((q + nm) \log^2{(nm)})$。

[AC Submission](https://codeforces.com/contest/1920/submission/241624674)

#### 做法2

考虑询问的本质是查询使 $(x, y, 0)$ 与 $(x, y, 1)$ 能联通的路径权值最大值。

发现对于原做法建图时将图的边权设为两端两点的 $dis$ 的最小值后可以 Kruskal 重构树解决。

所以建出图之后跑一遍最大生成树建出 Kruskal 重构树，那么询问就是查询 $(x, y, 0)$ 与 $(x, y, 1)$ 在 Kruskal 重构树上的 LCA 对应边的权值，倍增维护即可。

时间复杂度 $O((q + nm) \log{(nm)})$，但不知道为啥实测没有整体二分跑的快。

[AC Submission](https://codeforces.com/contest/1920/submission/241625224)

---

## 作者：Wuyanru (赞：10)

哎，人类智慧题，从来没有见过这样的题，写篇题解纪念之。

[题目链接](https://www.luogu.com.cn/problem/CF1920F2)。

## 题意

现在有一个大小为 $n\times m$ 的网格，格子有三种，海水、火山与岛屿。

定义一个格子的权值，为到所有火山的曼哈顿距离的最小值。

现在有 $q$ 次询问，每一次给定格子 $(x,y)$，你现在需要从 $(x,y)$ 这个格子出发，每一次走到相邻的非岛屿的四连通格子内，包围整个岛屿，并回到格子 $(x,y)$（可以经过相同格子）。

对于每一组询问，你的路径的权值，是所有经过格子的权值的最小值，你需要输出路径权值的最大值。

其中，包围的定义是，不存在一条从岛屿出发的八连通的路径，可以不经过你走到的格子，到达网格边界。

$3\le n,m\le n\times m\le 3\times 10^5$。

$q\le 3\times 10^5$。

## 题解

既然要求路径的权值，不妨先把每一个格子的权值求出来。

这一步是简单的，可以使用多源 bfs 在 $O(nm)$ 的复杂度内求出。

考虑什么样的路径是合法的。

考虑从岛屿的边界为起点，引一条只经过格子边界（不经过岛屿边界），且终点在网格边界的简单折线（例如下图黑色折线）。

可以发现，任意一个**可能作为答案的**方案合法，当且仅当穿过了这条线奇数次（例如下图白线）。

![](https://cdn.luogu.com.cn/upload/image_hosting/nw3rbisw.png)

一个粗略的证明：

以上图黑色折线为例，可以发现，折线的一端在岛屿边界，而另一端在网格边界，这样整张图就从一个环形的结构，被黑线分成了一个链式的结构。

再来考虑任何一条合法路径（例如白线），我们先给它选一个方向（顺时针或逆时针，这里以顺时针举例）。

我们再给黑色折线的**每一侧**定一个方向，例如上下。

这个时候来观察白线与黑色折线的所有交点。

可以发现，白线被分成了若干段（废话，白线若没有经过黑线一定不合法）。

由于我们给白线定了方向，又给黑线定了上下侧的区别。

那么每一段白线都可以划分为以下四种类型之一：上侧到上侧、上侧到下侧、下侧到上侧、下侧到下侧。

例如，白线中最长的一段就是从下侧到上侧，特殊的，这个例子中整个白线中并没有出现上侧到下侧。

回到证明中，假设白线被黑线分了 $n$ 段，那么就会有 $n$ 个交点，上侧与下侧在所有线段类型中便会各出现 $n$ 次。

这时，如果 $n$ 是奇数，那就必然会出现上侧到下侧和下侧到上侧中的至少一种。

这时候证明就很简单了，因为白线连成了环状，所以只要出现上述两种情况中的一种，岛屿就一定被“包围”。

现在我们就证明了，穿过黑线奇数次的方案，一定是合法的。

那么穿过黑线偶数次的方案呢？它们一定不合法吗？

答案是，这些方案可能合法，但没有必要管他们。

来看这两种情况，红线都穿过黑线偶数次，但它们都是合法方案（加粗点为起点）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ct8r7p5e.png)

容易发现，如果这种情况合法，那么上侧到下侧、下侧到上侧出现次数和必然 $\ge2$，那么整个路径就必然有自相交的部分。

既然有相交的部分，我们就可以化简。

![](https://cdn.luogu.com.cn/upload/image_hosting/luidwjt0.png)

只保留绿色部分，答案一定不劣，并且经过格子数量变少。

一直化简下去，红线一定能变为只穿过黑线奇数次，并且答案不劣于原来的方案。

所以经过黑线奇数次的答案要么不合法，要么没必要统计。

那么如何取黑线呢？可以参照第一张图，从岛屿边缘直接引一条普通线段即可（那条黄线）。

现在我们知道了什么情况是合法的，考虑如何计算答案。

那么现在的问题就是，对于每一组询问的点 $(x,y)$，我们需要找一条路径，使得它穿过了黑线奇数次，并回到 $(x,y)$，需要最大化这条路径的权值。

首先想暴力怎么做（首先设 $p_{i,j}$ 表示格子 $(i,j)$ 的权值）。

我们可以令 $dis_{x',y',0},dis_{x',y',1}$ 分别表示，现在在点 $(x',y')$，经过了黑线奇数次还是偶数次，最大权值是多少。

那么答案就是 $dis_{x,y,1}$。

我们可以令初始情况为 $dis_{x,y,0}=p_{x,y}$，然后跑一个最短路即可。

这样单组的复杂度是 $O(nm\log nm)$ 的，可以通过 F1。

这个时候我们可以发现一些有趣的事情，例如对于所有询问来说，我们建的图都长得一样。

我们还可以改变一下求的东西，不难发现 $dis_{x,y,1}$ 表示的其实是，找出一条起点为 $(x,y,0)$ 且终点为 $(x,y,1)$ 的路径，使它路径上点的权值最小值最大。

这不是我们重构树能干的事吗？

所以我们只需要一开始把最大生成树的重构树建出来（一条边 $(u,v)$ 边权的定义是 $\min(p_u,p_v)$）。

之后对于所有的询问 $(x,y)$，我们只需要查出点 $(x,y,0)$ 与 $(x,y,1)$ 的 LCA 即可。

时间复杂度是 $O((nm+q)\log nm)$，其实 $\log$ 完全可以消掉，但是加上也能过。

## 代码

[代码挂这里](https://www.luogu.com.cn/paste/gj7odg8t)。

感谢观看！

---

## 作者：未来姚班zyl (赞：9)

- Solve F1 first.
- 模拟赛中学到的一般性的做法

我们**去除**题目中的特殊性质：**岛屿构成一个四联通块**，即岛屿可以在除了边界上的任何位置，问题变为是否存在岛屿能到达边界，这题还能够完成吗？

一些简单的约定：
- 设 $N=nm$。
- 称一个点被 ban 了当且仅当它在被选择的路径上。
- 赋予这个网格图上的点 $(x,y)$ 新标号 $(x-1)\bmod m+y$（目的单纯是转为我们日常习惯的一维数组与表达）。本文形如“点 $(x,y)$”表示网格图中对应的点的坐标，形如点 $x$ 表示重标号后为 $x$ 的点。

本题解将给出一个 $O(N\log^2 N)$ 的解决方案。

在去掉特殊性质后，如果要判断岛屿能否到达边界，就无法使用现有题解的特殊方法。不过我们可以用一张无向图 $G$ 来刻画这个问题：

- 对于网格上没有被 ban 的点 $x$ 与点 $y$，如果两点八联通，则连边 $x\leftrightarrow y$。
- 建立超级源点 $S$，对于边界上的点 $x$，连边 $x\leftrightarrow S$。
- 建立超级汇点 $T$，对于 $s_{x,y}=\text{\#}$，即岛屿，连边 $(x,y)\leftrightarrow T$。
- 则存在岛屿能到达边界当且仅当 $S$ 和 $T$ 连通。

这样我们用一个点数和边数都是 $O(N)$，且每个点的度数为 $O(1)$ 的图将问题转换为连通性。

然后是和现有题解一样的思路，我们要最大化路径权值的最小值，可以使用 Kruskal 重构树。

我们从树的角度切入，处理一次查询点 $(x,y)$ 的答案，可以二分点 $(x,y)$ 在 Kruskal 重构树上的祖先 $anc$，然后可以选入路径的点的集合就是 **$anc$ 的子树**，这个观察非常厉害！我们的做法变为：

- 二分 $(x,y)$ 在 Kruskal 重构树上的祖先 $anc$，每次判断：如果将 $anc$ 的子树里的点全部从 $G$ 中移除，$S$ 和 $T$ 是否依旧连通。

对于子树问题，我们可以把 Kruskal 重构树用 dfn 序转为区间！设非岛屿点的数量为 $M$，现在问题变为有序列 $a_{1\sim M}$，多次查询区间 $[l,r]$，若从 $G$ 中删除 $a_l\sim a_r$ 的点，$S$ 与 $T$ 是否连通。

我们尝试对于每个位置 $l$，求出最小的 $r$ 使得如果删除 $a_l\sim a_r$ 中的点， $S$ 和 $T$ 不连通，设其为 $f_l$。

显然 $f_l$ 可以双指针，不过我们的操作为加边、删边、维护连通性，非常 ~~LCT~~ 困难。

但是我们可以利用 $f_l$ 的单调性进行**整体二分**。并使用**可撤销并查集**维护连通性。

这样的做法要求我们的加入和撤销要有很清晰的顺序，否则复杂度和正确性难以保证，这里呕象将很详细的教大家怎么用整体二分解决这个问题。

我们把删除 $[l,r]$ 看作保留 $a_1\sim a_{l-1}$ 与 $a_{r+1}\sim a_M$ 中的点，即保留一段前缀和一段后缀，这样操作就只有加点（同时加入这个点带来的边），求出 $g_l$ 表示如果保留前 $l$ 个点，最大的 $r$ 使得保留 $a_{r+1}\sim a_M$ 中的点，$S$ 和 $T$ 仍然连通。

接下来，用 `solve(l,r,L,R)` 表示当前要处理 $g_l\sim g_r$，它们的取值范围是 $[L,R]$，我们二分答案 $mid=\lfloor\frac{L+R+1}{2}\rfloor$。

我们的想法是保证当 `solve(l,r,L,R)` 开始时，$a_1\sim a_{l-1}$ 和 $a_{R+1}\sim a_M$ 已经被加入；结束时，撤销到开始时的状态。我们用图文来解释这个过程（横线中用红色表示当前最新的操作，黑色/红色表示对应点当前被加入，竖线表示当前处理的区间）：

- 初始，`solve(l,r,L,R)`：

![](https://cdn.luogu.com.cn/upload/image_hosting/1o8jkbcs.png)

- 第一步：加入 $a_{mid}\sim a_R$：

![](https://cdn.luogu.com.cn/upload/image_hosting/nlufas63.png)

- 第二步：从左到右加点，找到 $S$ 和 $T$ 连通的第一个位置 $pos$：

![](https://cdn.luogu.com.cn/upload/image_hosting/ee2b60mq.png)

这时候我们发现，对于 $i\in[pos,r]$，$g_i\ge mid$，对于 $i\in [l,pos-1]$，$g_i<mid$。

- 第三步，撤销第二步中的操作，为向左递归铺垫。这样我们回到了第一步中的图。
- 第四步，向左递归，即 `solve(l,pos-1,L,mid-1)`。

![](https://cdn.luogu.com.cn/upload/image_hosting/vpiu5rs3.png)

- 第五步，向左递归结束，在左区间造成的所有操作被撤销，再次回到第一次的图。
- 第六步，撤销第一步的操作，为向右递归做铺垫，回到初始的图。
- 第七步，加入 $[l,pos-1]$ 中的点，为向右递归做铺垫。

![](https://cdn.luogu.com.cn/upload/image_hosting/wbafp7h6.png)

- 第八步，向右递归，即 `solve(pos,r,mid,R)`。

![](https://cdn.luogu.com.cn/upload/image_hosting/3g4h0vtv.png)

- 第九步，向右递归结束，操作被撤销，回到第七步中的图。
- 第十步，撤销第七步中的操作，回到初始状态，我们的目标达成！

容易发现，虽然每次 solve 考虑的区间是 $[l,R]$，但是每次 solve 的复杂度为 $O((r-l+1+R-L+1)\log N)$，这两部分在每层的总和都是 $O(n)$ 的，所以复杂度足以保障。

这样我们就可以在 $O(N\log^2 N)$ 的时间求出所有的 $g_l$，从而得到所有的 $f_l$。最终我们可以在 kruskal 重构树上倍增代替二分，check 是 $O(1)$ 的，所以查询是 $O(q\log N)$。总复杂度为 $O(N\log^2 N)$。

有一点点边界情况，比如如果 $a_1\sim a_l$ 保留时 $S$ 和 $T$ 已经连通，就令 $g_l=M+1$。这个只需要在初始时令 $R=M+1$ 就行，还有很多细节可以自己研究。


```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=1e5+5,M=3e5+5,inf=(1LL<<30)-1,dx[8]={1,0,-1,0,1,1,-1,-1},dy[8]={0,1,0,-1,1,-1,1,-1};
int n,m,q,val[M],fa[M][20],G[M],tp,S,T,h[M],to[M],nxt[M],cnt,f[M],sz[M],dfn[M],Id[M],siz[M],Time,rt;
int id(int x,int y){return (x-1)*m+y;}
string s[N];
vector<int>a[N];
vector<bool>v[N];
bool che(int X,int Y){return X&&Y&&X<=n&&Y<=m;}
void bfs(){
	queue<Pi>q;
	repn(i)repm(j)a[i][j]=inf;
	repn(i)repm(j)if(s[i][j]=='v')a[i][j]=0,q.push({i,j});
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;q.pop();
		val[id(x,y)]=a[x][y];
		rep(i,0,3){
			int X=x+dx[i],Y=y+dy[i];
			if(!che(X,Y))continue;
			if(a[X][Y]==inf)a[X][Y]=a[x][y]+1,q.push({X,Y});
		}
	}
}
int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}
int find(int x){return f[x]==x?x:find(f[x]);}
void add_(int a,int b){to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;}
struct edge{int x,y,w;}g[M<<1];
bool cmp(edge a,edge b){return a.w>b.w;}
void dfs(int x,int Fa){
	Id[dfn[x]=++Time]=x,siz[x]=1,fa[x][0]=Fa;
	rep(i,1,18)fa[x][i]=fa[fa[x][i-1]][i-1];
	e(x)dfs(y,x),siz[x]+=siz[y];
}
struct op{
	int x,y;
}st[M];
void Undo(int t){while(tp>t)sz[st[tp].y]-=sz[st[tp].x],f[st[tp].x]=st[tp].x,tp--;}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(sz[x]>sz[y])swap(x,y);
	if(x!=y)f[x]=y,sz[y]+=sz[x],st[++tp]={x,y};
}
bool F[M];
void Insert(int ID){
	if(!ID)return;
	int x=(ID-1)/m+1,y=(ID-1)%m+1;
	v[x][y]=1;
	rep(i,0,7){
		int X=x+dx[i],Y=y+dy[i];
		if(che(X,Y)&&v[X][Y])merge(id(x,y),id(X,Y));
	}
	if(x==1||y==1||x==n||y==m)merge(id(x,y),S);
	if(s[x][y]=='#')merge(id(x,y),T);
}
void Refuse(int ID){
	if(!ID)return;
	int x=(ID-1)/m+1,y=(ID-1)%m+1;
	v[x][y]=0;
}
void solve(int l,int r,int Ll,int Rr){
	if(l>r||Ll>Rr)return;
	if(Ll==Rr){
		rep(i,l,r)G[i]=Ll;
		return;
	}
	int Mid=Ll+Rr+1>>1,TiM=tp,Tim,pos=l-1;
	rep(i,Mid,Rr)Insert(Id[i]);
	Tim=tp;
	if(find(S)!=find(T)){
		rep(i,l,r+1){
			pos=i;
			if(i==r+1)break;
			Insert(Id[i]);
			if(find(S)==find(T))break;		
		}
	}
	rep(i,l,min(pos,r))Refuse(Id[i]);
	Undo(Tim),solve(l,pos-1,Ll,Mid-1);
	rep(i,Mid,Rr)Refuse(Id[i]);
	Undo(TiM),pos=max(pos,l);
	rep(i,l,pos-1)Insert(Id[i]);
	solve(pos,r,Mid,Rr);
	rep(i,l,pos-1)Refuse(Id[i]);
	Undo(TiM);
}
void SolveG(){
	rep(i,1,n*m+2)f[i]=i,sz[i]=1;
	S=n*m+1,T=S+1;
	rep(i,1,Time)G[i]=0;
	repn(x)repm(y)if(s[x][y]=='#')Insert(id(x,y));
	tp=0;
	solve(1,Time-1,1,Time+1);
	rep(i,1,Time-1)G[i]=max(G[i],i+1),F[i+1]=G[i]<=i+siz[Id[i+1]];
	F[1]=1;
}
void Main(){
	n=read(),m=read(),q=read();
	rep(i,0,n+1)a[i].resize(m+2),v[i].resize(m+2);
	repn(i)cin>>s[i],s[i]=' '+s[i];
	bfs();
	int ct=0;
	repn(x)repm(y)if(s[x][y]!='#'){
		rep(i,0,1){
			int X=x+dx[i],Y=y+dy[i];
			if(!che(X,Y)||s[X][Y]=='#')continue;
			g[++ct]={id(x,y),id(X,Y),min(val[id(x,y)],val[id(X,Y)])};
		}
	}
	rep(i,1,n*m)f[i]=i;
	sort(g+1,g+ct+1,cmp);
	rep(i,1,ct){
		int x=g[i].x,y=g[i].y;
		x=Find(x),y=Find(y);
		if(x==y)continue;
		if(val[x]>=val[y])f[x]=y,add_(y,x),rt=y;
		else f[y]=x,add_(x,y),rt=x;
	}
	dfs(rt,0),SolveG(),F[0]=1;
	while(q--){
		int x=read(),y=read(),Nw=id(x,y);
		if(F[dfn[Nw]]){
			cout <<val[Nw]<<'\n';
			continue;
		}
		per(i,18,0)if(!F[dfn[fa[Nw][i]]])Nw=fa[Nw][i];
		cout <<val[fa[Nw][0]]<<'\n';
	}
	repn(x)repm(y)v[x][y]=0,h[id(x,y)]=0,Id[id(x,y)]=0;
	rep(x,1,n*m)rep(y,0,18)fa[x][y]=0;
	cnt=Time=rt=0;
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：EuphoricStar (赞：8)

首先需要知道的一个 trick：判断一个点是否在一个闭合回路内部，从这个点向任意方向引一条射线，若不考虑相切，那么和回路的交点为奇数时这个点在回路内部，否则在外部。

那么这题要判断一个回路是否包含全部的 island，可以找到任意一个 island 向右引一条射线。

给每个点增加一个状态 $(x, y, 0/1)$ 表示当前走到 $(x, y)$，穿过了偶数或奇数次射线。那么一次询问的本质是找到一条 $(x, y, 0) \to (x, y, 1)$ 的一条经过点权最小值最大的路径（可以多源 bfs 求出任意一点 $(i, j)$ 到最近的 `v` 的距离 $d_{i, j}$，$(x, y, 0/1)$ 的点权就是 $d_{x, y}$）。

上面那个问题显然给每条 $(u, v)$ 赋权 $\min(val_u, val_v)$，就可以建 Kruskal 重构树查 LCA 解决。

建图就对于一个 $(x, y)$，如果它在射线上就视为 $(x, y) \to (x + 1, y)$ 和射线新增了一个交点。

时间复杂度 $O((nm + q) \log nm)$。

[code](https://codeforces.com/contest/1920/submission/241537796)

---

## 作者：Z1qqurat (赞：2)

离线启发式合并做法 $\checkmark$

考虑快速判断一个点是否在一条闭合回路内的方法，这其实类似于判断一个点是否在一个多边形内，从该点连出一条射线，如果该射线与回路不相切，那么如果射线与回路有奇数个交点则该点在回路内，否则在回路外。

由于所有岛屿形成一个四连通块，所以如果一条闭合回路没有经过岛屿点且包含了一个岛屿点，那么它肯定包含了所有岛屿。于是我们只需要考虑一个岛屿点 $(sx,sy)$，考虑从它的上边向右连出一条射线，设状态 $(x,y,0/1)$ 表示目前回路到了 $(x,y)$，与这条射线一共有偶数/奇数个交点，那么只有纵向的边会产生新的交点，比如 $x=sx,y>sy$ 时 $(x,y)\to (x+1,y)$ 就会产生一个新的交点，所以 $(x,y,0)\to(x+1,y,1),(x,y,1)\to(x+1,y,0)$。于是我们相当于就要求 $(x,y,0)\to(x,y,1)$ 路径上的离火山最近距离的最大值。类似于 F1，设 $dis_{x,y}$ 表示 $(x,y)$ 离火山的最近距离，那么如果 $(x,y,t)\to(x',y',t')$，边权设为 $\min(dis_{x,y},dis_{x',y'})$，那么相当于直接求 $(x,y,0)\to(x+1,y,1),(x,y,1)\to(x+1,y,0)$ 路径上的最小边权最大值。

这可以用 Kruskal 重构树解决，但是我觉得不够优美还浪费空间。想到之前打 zr 见过的一个套路，把询问 $i:(x,y)$ 离线下来，对每个点开一个询问 set，$i$ 存进 $x,y$ 的 set 里面，然后求最大生成树的同时做启发式合并，比如现在要合并 $fu,fv$，连的边权为 $w$，那么所有 $x\in qu_{fu},y\in qu_{fv}$ 的询问 $(x,y)$ 的答案都可以设为 $w$，所以可以更新一些询问的答案，然后合并 $qu_{fu},qu_{fv}$，还未处理的询问就并进去。这样复杂度 $\mathcal{O}(nm\cdot\alpha(nm)\log nm)$，跑得还算快，但是比 Kruskal 重构树的在线做法好写多了，至少不需要构出一个具体的生成树/重构树。

[Submission.](https://codeforces.com/contest/1920/submission/245970987)

---

## 作者：huangrenheluogu (赞：2)

参考文章：

- [Codeforces Editoral](https://codeforces.com/blog/entry/122560)

- [cjZYZtcl(188286) 的题解](https://www.luogu.com.cn/blog/188286/solution-cf1920f2)

可以看看 F1 中我的题解，发现和本题正解不是很一样，所以导致我根本想不到 F2 怎么做的。

同时，因为我 F1 是用 vector 写的，所以从 $0$ 开始标号，但是最后输入 $x,y$ 的时候忘记减 $1$ 了，调试好久警示后人。在题解中，我仍然是从 $(1,1)$ 开始标号，看代码的时候注意一下。

怎么判定一条回路是包围中间的岛屿的？

CF 上提供了一个新奇的方法，将岛屿的边缘任意一点向任意一个方向引一条射线，显然，这一条道路需要经过这条射箭奇数次。

下图来源：[Codeforces Editoral](https://codeforces.com/blog/entry/122560)

![](https://cdn.luogu.com.cn/upload/image_hosting/vkiy1xib.png)

我们从 $(3,7)$ 向右侧引射线，以穿过 $(3,8)$ 和 $(2,8)$ 中间的连线或者 $(3,8)$ 和 $(4,8)$ 中间的连线的次数统计。比如，图中所示的箭头就是一次“经过射线”，因为它出了一次 $(3,8)$。

可以定义两个点，$(x,y,1/0)$ 表示这个点经过了奇数/偶数次。

考虑建边。

注意，这里我们应该由 $(x,y)$ 向 $(x+1,y)$ 或者 $(x,y+1)$ 建边。否则会因为双向边卡空间，并且需要同时判断 $(x,y)$ 和 $(nx,ny)$ 是否在引出的射线上，其中 $(nx,ny)$ 是引出边连接的另一个节点。

判定条件就是让 $(x,y,0)$ 和 $(x,y,1)$ 连接起来的最小长度的边的长度。

这让我们想到了 Kruskal 重构树。

剩下的就是 Kruskal 重构树的模板了。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 3e5 + 5, inf = 1e9;
int n, m, qq, nx, ny, l, r, mid, dis, z, d, X, Y, _x, _y, tot, fa[N << 2][25], fax, fay, a[N], idx, w[N << 2], f[N << 1], lg[N << 2], dep[N << 2], x, y, _lca;
int Fa[N << 2], fir[N << 2], son[N << 2], nxt[N << 2], total;
int dx[8] = {0, 1, 0, -1, 1, -1, -1, 1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
char c;
struct node{
	int x, y;
};
vector<node>isla;
queue<node>q;
struct dots{
	int x, y, ans;
};
deque<dots>Q;
struct edge{
    int x, y, dis;
}e[N << 4], tmp;
inline int calc(int x, int y, int k = 0){
    return x * m + y + 1 + k * n * m;
}
inline bool cmp(edge x, edge y){
    return x.dis > y.dis;
}
inline int getfa(int x){
    if(Fa[x] == x) return x;
    return Fa[x] = getfa(Fa[x]);
}
inline void dfs(int x, int ff = 0){
    dep[x] = dep[ff] + 1;
    fa[x][0] = ff;
    for(int i = 1; i <= lg[dep[x]]; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(int i = fir[x]; i ; i = nxt[i]){
        if(son[i] == ff) continue ;
        dfs(son[i], x);
    }
}
inline int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	for(int i = lg[dep[y]]; ~i; i--){
		if(dep[fa[y][i]] >= dep[x]) y = fa[y][i];
	}
	if(x == y) return x;
	for(int i = lg[dep[x]]; ~i; i--){
		if(fa[x][i] != fa[y][i]){
			x = fa[x][i], y = fa[y][i];
		}
	}
	return fa[x][0];
}
inline void add(int x, int y){
	nxt[++total] = fir[x];
	fir[x] = total;
	son[total] = y;
}
int main(){
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &qq);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			c = getchar();
			f[calc(i, j)] = inf;
			while(c != '.' && c != 'v' && c != '#') c = getchar();
			if(c == '.') a[calc(i, j)] = 0;
			if(c == 'v'){
                a[calc(i, j)] = 1;
				q.push((node){i, j});
				f[calc(i, j)] = 0;
			}
			if(c == '#'){
			    a[calc(i, j)] = 2;
				isla.pb((node){i, j});
				_x = i, _y = j;
			}
		}
	}
	while(!q.empty()){
		X = q.front().x;
		Y = q.front().y;
		q.pop();
		for(int k = 0; k < 4; k++){
			nx = X + dx[k], ny = Y + dy[k];
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue ;
			if(f[calc(nx, ny)] <= f[calc(X, Y)] + 1) continue ;
			f[calc(nx, ny)] = f[calc(X, Y)] + 1;
			q.push((node){nx, ny});
		}
	}
	/*
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			printf("%d ", f[calc(i, j)]);
		}
		puts("");
	}
	*/
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) Fa[calc(i, j)] = calc(i, j), Fa[calc(i, j, 1)] = calc(i, j, 1);
	}
	for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(a[calc(i, j)] == 2) continue ;
            w[calc(i, j)] = f[calc(i, j)];
            w[calc(i, j, 1)] = f[calc(i, j)];
            for(int ch : {1}){
                nx = i + ch, ny = j;
                if(nx < 0 || nx >= n) continue ;
                if(a[calc(nx, ny)] == 2) continue ;
                if(i == _x && j > _y){
                	tmp.dis = min(f[calc(nx, ny)], f[calc(i, j)]), tmp.x = calc(i, j, 0), tmp.y = calc(nx, ny, 1);
	                e[++tot] = tmp;
	                tmp.x = calc(i, j, 1), tmp.y = calc(nx, ny, 0);
	                e[++tot] = tmp;
				}
				else{
					tmp.dis = min(f[calc(nx, ny)], f[calc(i, j)]), tmp.x = calc(i, j, 1), tmp.y = calc(nx, ny, 1);
	                e[++tot] = tmp;
	                tmp.x = calc(i, j, 0), tmp.y = calc(nx, ny, 0);
	                e[++tot] = tmp;
				}
            }
            for(int ch : {1}){
                nx = i, ny = j + ch;
                if(ny < 0 || ny >= m) continue ;
                if(a[calc(nx, ny)] == 2) continue ;
                tmp.dis = min(f[calc(nx, ny)], f[calc(i, j)]), tmp.x = calc(i, j, 0), tmp.y = calc(nx, ny, 0);
                e[++tot] = tmp;
                tmp.x = calc(i, j, 1), tmp.y = calc(nx, ny, 1);
                e[++tot] = tmp;
            }
        }
	}
	sort(e + 1, e + tot + 1, cmp);
	idx = n * m * 2;
	//for(int i = 1; i <= tot; i++) printf("%d %d : %d\n", e[i].x, e[i].y, e[i].dis);
	for(int i = 1; i <= tot; i++){
        fax = getfa(e[i].x);
        fay = getfa(e[i].y);
        if(fax == fay) continue ;
        idx++;
        Fa[idx] = idx;
        Fa[fax] = idx;
        Fa[fay] = idx;
        w[idx] = e[i].dis;
        add(idx, fax), add(idx, fay);
	}
	for(int i = 2; i <= idx; i++) lg[i] = lg[i >> 1] + 1;
	dfs(idx);
	while(qq--){
		scanf("%d%d", &x, &y);
		x--, y--;
		_lca = lca(calc(x, y), calc(x, y, 1));
		printf("%d\n", min(w[_lca], f[calc(x, y)]));
	}
	return 0;
}

```

---

## 作者：Msents (赞：0)

介绍一种很唐很构式正确性也难搞的做法，本质上是 F1 做法硬套 F2，看个乐子就好。

考虑 F1 的做法，我们可以二分答案。具体地，设目前二分值为 $k$，每次检查将距离火山的长度小于 $k$ 的点设成不可达，再求当前询问的点能到达哪些地方，最后求从岛屿出发，是否能不通过询问点到达的地方而到达边界，就行了。

现考虑 F2。之前的做法对于相同的 $k$，每个询问做了很多相同的事，考虑绑在一起处理，也就是整体二分。容易发现在一个联通块里的询问点在这次检查里要么全部通过，要么全都不通过。那么现在的任务就是快速求每个连通块的合法性。

我的做法是从岛屿开始扩展，看能到哪些询问点不可达的地方。无法扩展之后，看与其相邻的询问点可达的连通块是否与其它还没有到达的地方。如果有，那么这个联通块里的询问点肯定是合法的，将连通块里的询问点标记，并将新的到达的地方加入队列里。如果没有，那这个联通块里的都是不合法的。
如此进行下去，直到到达所有的地方。

复杂度 $O(nm\log{nm})$，但是我写的交 CF TLE了，校内 OJ WA 了一个点。

伪算：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxQ=300000;
int n,m,q;
vector<vector<char> >a;
vector<vector<bool> >vst,vis,vit;
vector<vector<vector<int> > >qf;
struct Point{
	Point(){}
	Point(int x,int y,int k):x(x),y(y),k(k){}
	int x,y,k;
}que[MaxQ+1];
int ans[MaxQ+1];
bool IsInMap(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
void MultBinary(int ql,int qr,int l,int r){
static const int
	dx[]={0,1,0,-1},
	dy[]={1,0,-1,0},
	fx[]={-1,0,1,1,1,0,-1,-1},
	fy[]={-1,-1,-1,0,1,1,1,0};
	if(ql>qr)return;
	if(l==r){
		for(int i=ql;i<=qr;i++)ans[que[i].k]=l;
		return;
	}
	int mid=(l+r+1)/2;
	queue<Point>q1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='v')
				q1.emplace(i,j,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			vst[i][j]=false;
	while(!q1.empty()){
		int x=q1.front().x,y=q1.front().y,k=q1.front().k;
		q1.pop();
		if(vst[x][y]||k>=mid)continue;
		vst[x][y]=true;
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(!IsInMap(nx,ny))continue;
			q1.emplace(nx,ny,k+1);
		}
	}
	for(int i=ql;i<=qr;i++)qf[que[i].x][que[i].y].emplace_back(que[i].k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='#')
				q1.emplace(i,j,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			vis[i][j]=false;
	vector<Point>tol,tor;
	while(1){
		vector<Point>out;
		bool flag=true;
		while(!q1.empty()){
			int x=q1.front().x,y=q1.front().y;
			q1.pop();
			if(vis[x][y])continue;
			vis[x][y]=true;
			if(x==1||x==n||y==1||y==m){
				flag=false;
				break;
			}
			for(int i=0;i<8;i++){
				int nx=x+fx[i],ny=y+fy[i];
				if(!IsInMap(nx,ny))continue;
				if(a[nx][ny]=='.'&&(!vst[nx][ny])){
					out.emplace_back(nx,ny,0);
					continue;
				}
				q1.emplace(nx,ny,0);
			}
		}
		if(!flag)break;
		for(auto&p:out){
			if(vis[p.x][p.y])continue;
			q1.emplace(p.x,p.y,0);
			flag=true;
			vector<Point>nw,que;
			while(!q1.empty()){
				int x=q1.front().x,y=q1.front().y;
				q1.pop();
				if(vis[x][y])continue;
				while(qf[x][y].size()){
					que.emplace_back(x,y,qf[x][y].back());
					qf[x][y].pop_back();
				}
				if(x==1||x==n||y==1||y==m)flag=false;
				if(vst[x][y]){
					nw.emplace_back(x,y,0);
					continue;
				}
				vis[x][y]=true;
				for(int i=0;i<4;i++){
					int nx=x+dx[i],ny=y+dy[i];
					if(!IsInMap(nx,ny))continue;
					q1.emplace(nx,ny,0);
				}
			}
			if(nw.size()){
				for(auto&p:nw)q1.emplace(p);
				for(auto&p:que){
					if(vst[p.x][p.y]){
						tor.push_back(p);
					}else{
						tol.push_back(p);
					}
				}
				break;
			}else{
				for(auto&p:que)tol.push_back(p);
			}
			if(!flag)break;
		}
		if(!flag)break;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			while(qf[i][j].size()){
				tor.emplace_back(i,j,qf[i][j].back());
				qf[i][j].pop_back();
			}
		}
	}
	for(int i=0;i<tol.size();i++)que[ql+i]=tol[i];
	for(int i=0;i<tor.size();i++)que[ql+tol.size()+i]=tor[i];
	MultBinary(ql,ql+tol.size()-1,mid,r);
	MultBinary(ql+tol.size(),qr,l,mid-1);
}
void Solve(){
	cin>>n>>m>>q;
	a=vector<vector<char> >(n+1,vector<char>(m+1));
	vst=vis=vit=vector<vector<bool> >(n+1,vector<bool>(m+1));
	qf=vector<vector<vector<int> > >(n+1,vector<vector<int> >(m+1));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=q;i++)cin>>que[i].x>>que[i].y,que[i].k=i;
	MultBinary(1,q,0,n+m);
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	Solve();
	return 0;
}

```

---

