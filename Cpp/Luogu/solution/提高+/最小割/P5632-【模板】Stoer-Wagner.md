# 【模板】Stoer-Wagner

## 题目描述

定义无向图 $G$ 的最小割为：一个去掉后可以使 $G$ 变成两个连通分量，且边权和最小的边集的边权和。

给出一张无向图 $G$，求其最小割。

## 说明/提示

对于前 $20\%$ 的数据， $n\leq 10$。  
对于前 $40\%$ 的数据， $n\leq 100$。  
对于另外 $10\%$ 的数据，保证输入为一棵树。  
对于另外 $10\%$ 的数据，保证输入为一条链。  
对于 $100\%$ 的数据， $n\leq 600,m\leq \frac{n\times (n-1)}{2}$ ，保证 $\sum_{i=1}^{m}w_i \leq10^9$ 。

#### PS：想交 最大流/最小割树 的就省省吧。

## 样例 #1

### 输入

```
4 6
1 2 5
1 3 1
2 4 1
3 4 2
2 3 1
1 4 2
```

### 输出

```
4```

# 题解

## 作者：ix35 (赞：29)

## Stoer-Wagner 全局最小割算法

之前一篇题解没有证明，我来加上一个证明。

参考文章：[全局最小割StoerWagner算法详解 By Oyking](https://www.cnblogs.com/oyking/p/7339153.html)

设原图为 $G=(V,E)$，最小割为 $C\in E$。

算法基本思想：对于无向图上任意两点 $s,t$，割去 $C$ 后，则或者 $s,t$ 处于同一连通块，或者 $s,t$ 处于不同两连通块（显然）。

1. 对于 $s,t$ 处于同一连通块的情况，根据割的定义，割去 $C$ 后至少有一个点 $j$，与 $s$ 不在一个连通块内，则 $j,t$ 也不在一个连通块内，那么 $j$ 与 $s,t$ 都不在一个连通块内，所以凡是 $j$ 与 $s,t$ 之间的边必须全部割去，如果 $(j,s)$ 边被割去，则如果 $(j,t)$ 未被割去，$(j,s)$ 不割是一种更小的割法（与最小割矛盾），因此如果 $(j,s)\in C$，则有 $(j,t)\in C$，所以 $s,t$ 可看作是一个整体，共享所有的边。

那么，处理完一对 $s,t$ 之间的最小割后，就只有它们处于同一连通块的情况了，也就是做完一对以后就合并一对点，如是进行 $n-1$ 次即合并成一个点，算法完成。

2. 下面主要探讨 $s,t$ 不在一联通块时的答案，即 $s,t$ 之间的最小割，注意 $s,t$ 的选择是任意的。

构造过程依赖于一个集合 $A$，一开始，我们令 $A=\varnothing$，然后我们将所有点（合并了的点算一个）按照某种顺序加入 $A$ 中。

加入顺序依赖于权值函数 $w(i)$，我们令 $w(i)$ 表示 $\sum\limits_{j\in A} d(j,i)$，其中 $d(j,i)$ 表示 $j,i$ 之间的边权（因为求最小割，如果没有边可视为不用割，即 $d(j,i)=0$）。

算法流程：每次选择 $w(i)$ 最大的 $i$ 加入 $A$ 中，如是进行 $|V'|$ 次（其中 $|V'|$ 表示当前图的点数）即可确定所有点加入 $A$ 的顺序，定义 $ord(i)$ 表示第 $i$ 个加入 $A$ 的点，令 $t=ord(|V'|)$，则对于任意一点 $s$，$s$ 到 $t$ 的最小割即为 $w(t)$。

下面来证明一下以上算法的正确性（来自最上面的链接）：

若点 $v$ 满足：在割去 $C$ 的图中，存在一个点 $u$，在 $v$ 之前加入 $A$，且 $u$ 和 $v$ 不在一连通块内，则称 $v$ 是 Active 的。

下证对于任意一个 Active 结点 $v$，$C$ 中处在 $v$ 前的部分不小于 $w(v)$。如果此结论成立，则因 $t$ 最后加入 $A$，所以 $C$ 在 $t$ 前部分就是整个 $C$，于是 $C\ge w(t)$，又将 $w(t)$ 割去后 $t$ 与其他点都不连通，所以 $w(t)$ 就是 $t$ 到之前任意一点的最小割。

运用数学归纳法，对于第一个 Active 结点 $v$，结论成立：因为 $v$ 前结点都不是 Active 结点，所以都处在一连通块内，所以 $v$ 与它们都不处在一连通块内，所以想要割去 $v$ 需要断开它和之前所有点的边，即 $w(v)$。

对于 $v$ 之后的第一个 Active 结点 $u$，有 $w(u)$ 是从 $v$ 前结点和 $v$ 到 $u$ 之间结点与 $u$ 的边构成的，对于 $v$ 前面的结点，$w(u)$ 的这一部分不超过 $w(v)$（因为 $v$ 先加入 $A$）。而对于 $v$ 到 $u$ 之间结点，与 $v$ 同样道理地，与 $u$ 边权相加一定要出现在 $C$ 中，两者相加，所以完整的 $w(u)$ 必然大于等于 $C$ 在 $u$ 前部分，归纳可得证。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=610,INF=1e9;
int n,m,x,y,z,s,t,dis[MAXN][MAXN],w[MAXN],dap[MAXN],vis[MAXN],ord[MAXN];
int proc (int x) {
	memset(vis,0,sizeof(vis));
	memset(w,0,sizeof(w));
	w[0]=-1;
	for (int i=1;i<=n-x+1;i++) {
		int mx=0;
		for (int j=1;j<=n;j++) {
			if (!dap[j]&&!vis[j]&&w[j]>w[mx]) {mx=j;}
		}
		vis[mx]=1,ord[i]=mx;
		for (int j=1;j<=n;j++) {
			if (!dap[j]&&!vis[j]) {w[j]+=dis[mx][j];}
		}
	}
	s=ord[n-x],t=ord[n-x+1];
	return w[t];
}
int sw () {
	int res=INF;
	for (int i=1;i<n;i++) {
		res=min(res,proc(i));
		dap[t]=1;
		for (int j=1;j<=n;j++) {
			dis[s][j]+=dis[t][j];
			dis[j][s]+=dis[j][t];
		}
	}
	return res;
}
int main () {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		dis[x][y]+=z,dis[y][x]+=z;
	}
	printf("%d\n",sw());
	return 0;
}
```








---

## 作者：HansLimon (赞：16)

${\color{white}\text{悄咪咪的交一篇题解 qwq}}$

\-\-感谢@saxiy 和@Clever_Jimmy 发现我的口胡错误

## Stoer-Wagner算法
###### 其实记不下来名字的，太绕了 qwq
[原论文传送门 需要科学的力量](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.450.4415&rep=rep1&type=pdf)

最开始看到这道题的时候想的是网络流，但是数据范围....然后噼里啪啦想半天没思路

**这个时候就需要伟大的Sto(~~啥啥啥~~)算法了**

我就不再从割的定义入手了 qwq

### Part 1
考虑我们有如下的图G:

![first](https://s2.ax1x.com/2019/11/14/MNeGcQ.md.png)

很明显，最小割自然是**1**

但如果将**1**换成4，最小割即为**2**了(也就是右上角的那两边)

那么回顾一下我们对于这一问题的思路：找到边集E使得G被分为多个连通块，再比较各个E的边权和，选出最小的

###### 好像有点绕，请再读一遍 qwq
**有没有发现在这一过程中我们并没有理会每一次找E时已经被处理为连通块中的边**

因为这些边并不能对E计算边权和产生影响，这个St啥算法也是这个思路，而且在你搞懂后还会觉得有点像缩点。
### Part 2
对于每一次计算E，我们的做法如下
```cpp
max_wage = -1;//wage表示这个点发出的边权和
for (register int j = 1;j <= n;j ++)
	if (!added[j] && !used[j] && max_wage < wage[j]){
	//added表示当前这个点是否被合并(后文会说到)，used表示进入集合E(或者说已访问)
		next_point = j;
		max_wage = wage[j];
	}
```
解释：因为我们要求最小割，所以尽量把边权值大的放入连通块，因为这样不会对E统计边权和造成影响。

然后对于任何的S、T，只有两种情况：分开或在一起
```cpp
used[next_point] = true;
ans = max_wage;
S = T, T = next_point;
```
接着就是我先前说的有点像缩点的玩意了，将$nextpoint$加入某一个连通块
	
    for (register int j = 1;j <= n;j ++)if (!added[j] && !used[j])wage[j] += map[T][j];
对E这一部分的操作就结束了 qwq
###### 其实感觉没说透彻，恳请大佬们提提修改意见
### Part 3
然后就是一直计算E了嘛 qwq

感觉没啥好讲的，就放码吧
```cpp
int stoer_wagner(){
	register int ans = MAX;
	for (register int i = 1;i < n;i ++){
		ans = min(ans, step());
		if (!ans)return 0;
		added[T] = true;
		for (register int j = 1;j <= n;j ++)
			if (!added[j]){
				map[S][j] += map[T][j];
				map[j][S] += map[j][T];
			}
	}
	return ans;
}
```
应该没啥问题 qwq
### Part 4
最后就是放码时间(写着写着感觉好像忘了啥，到时候~~想起来再补吧~~)

```cpp
#include <cstdio>
#define var_DEBUG(x, y) printf("Passing %s with value %d %d\n", __FUNCTION__, (x), (y));

const int N = 607, M = (N*(N - 1))>>1, MAX = 2e9;
int n, m, /*cnt, */S, T, /*first[N], */wage[N], map[N][N];
bool used[N], added[N];

inline int min(int a, int b){return a < b?a:b;}
int step(){
	register int ans = MAX, next_point = T, max_wage;
	for (register int i = 1;i <= n;i ++)used[i] = false, wage[i] = 0;
	for (register int i = 1;i <= n;i ++){
		max_wage = -1;
		for (register int j = 1;j <= n;j ++)
			if (!added[j] && !used[j] && max_wage < wage[j]){
				next_point = j;
				max_wage = wage[j];
			}
		if (next_point == T)break;
		used[next_point] = true;
		ans = max_wage;
		S = T, T = next_point;
		for (register int j = 1;j <= n;j ++)if (!added[j] && !used[j])wage[j] += map[T][j];
	}
	return ans;
}
int stoer_wagner(){
	register int ans = MAX;
	for (register int i = 1;i < n;i ++){
		ans = min(ans, step());
		if (!ans)return 0;
		added[T] = true;
		for (register int j = 1;j <= n;j ++)
			if (!added[j]){
				map[S][j] += map[T][j];
				map[j][S] += map[j][T];
			}
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for (register int i = 1, x, y, z;i <= m;i ++){
		scanf("%d %d %d", &x, &y, &z);
		map[x][y] += z, map[y][x] += z;
	}
	return !printf("%d", stoer_wagner());
}
```
### Part 5
其实可以不看了，这一部分算我求助qwq

注意到$AC$代码中用的是邻接矩阵了嘛，因为我不知道怎么用链式前向星解决qwq

就是因为在函数stoer_wagner中，最后一部分
```cpp
for (register int j = 1;j <= n;j ++)
	if (!added[j]){
		map[S][j] += map[T][j];
		map[j][S] += map[j][T];
	}
```
就是这个地方不知道怎么办，想开一个临时数组缓存但是S和T是变换的qwq

希望能有大佬优化此代码为链式前向星qwq

---

## 作者：0Io_oI0 (赞：15)

我们先从算法简介讲起……
# 算法简介
Stoer-Wagner 算法在 $1995$ 年由 Stoer 和 Wagner 共同提出，是一种通过递归的方式来解决无向正权图上的全局最小割问题的算法。
# 概念
- 割：对于一个无向图 $G
=
(
V
,
E
)$，令 $C
U
T$ 表示一些边的集合，若从 $G$ 中删去 $C
U
T$ 的所有边，使得 $G$ 不再连通，我们就称 $C
U
T$ 集合是 $G$ 的割。
- 最小割：一个去掉后可以使 $G$ 变成两个连通分量，且边权和最小的边集的边权和。
- $S-T$ 割：使 $S$ 和 $T$ 不连通的割。
# 步骤
1. 在图 $G$ 中确定两点 
$s$，$t$。
2. 求出 $S
−
T$ 最小割。
3. 合并 $s$，$t$
   - 删除 $s$，$t$ 之间的边。
    - 对于 $\frac{G}{\{
s
,
t
\}}$ 中任意一点 $k$，删除 $(
t
,
k
)$。
    - $dist(s,k)=dist(s,k)+
d
i
s
t
(
t
,
k
)$。
4. 若 $|
V
|
 ＞ 
1$，返回 $step$ $1$。
5. 输出最小值。

合并的过程非常像 Prim 求最小生成树的过程。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int ma=605;
const int INF=(1<<29);
int mp[ma][ma],dis[ma],fa[ma],size[ma],n,m;;
bool vis[ma],re[ma];
inline int get(int x){
	if(fa[x]==x)	return x;
	return fa[x]=get(fa[x]);
}
inline void merge(int x,int y){
	int f1=get(x);
	int f2=get(y);
	if(f1!=f2){
		fa[f1]=f2;
		size[f2]+=size[f1];
	}
}
inline int contract(int &s,int &t){
	int minn=INF;//最小割 
	memset(dis,0,sizeof(dis));
	memset(vis,false,sizeof(vis));
	//类似于 Prim 求最小生成树的步骤 
	for(register int i=1;i<=n;i++){
		int maxx=-INF,u=-1;
		for(register int j=1;j<=n;j++){
			if(re[j]==false && vis[j]==false && dis[j]>maxx){
				maxx=dis[j];
				u=j;
			}
		}
		if(u==-1)return minn;
		s=t;
		t=u;
		minn=maxx;
		vis[u]=true;
		for(register int j=1;j<=n;j++)if(re[j]==false && vis[j]==false)dis[j]+=mp[u][j];
	} 
	return minn;
}
inline int Stoer_Wagner(){
	int minn=INF;
	int s,t,ans;
	for(register int i=1;i<=n-1;i++){//循环 n - 1 次
		ans=contract(s,t);
		re[t]=true;
		minn=min(minn,ans);
		if(minn==0)return 0;
		for(register int j=1;j<=n;j++)
			if(re[j]==false){
				mp[j][s]+=mp[j][t];
				mp[s][j]=mp[j][s];
			}
	}  
	return minn;
}
int main(void){
	scanf("%d%d",&n,&m);
	if(m<n-1)puts("0");//很明显将导致不连通
	else{
		for(register int i=1;i<=n;i++){
			fa[i]=i;
			size[i]=1;
		}
		for(register int i=1;i<=m;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			if(get(u)!=get(v))merge(u,v);
			mp[u][v]+=w;
			mp[v][u]+=w;
		}
		if(size[get(1)]!=n)puts("0");//图不连通
		else printf("%d\n",Stoer_Wagner());
	}
	return 0;
}
```

---

## 作者：Lstdo (赞：9)

来个奥妙重重的随机化算法。[原始论文传送门](http://www.columbia.edu/~cs2035/courses/ieor6614.S09/Contraction.pdf)

全局最小割相比一般的源汇最小割，有个重要的特点是：很小。最小割是不会超过最小的点的度数（带权，即这个点相连的边的权之和，后同选一条边。）的，因为把这些边全割了也是原图的一个割。假设最小割是 $c$,那么一定有 $2\sum w_i\geq nc$,也就是最小割和所有权值之和相比很小。

我们不好找最小割的边，但我们知道从权的意义上来看，不是割的边占了大多数（对某一特定的最小割来说）。所以我们可以随机找不是割的边。

## 1 朴素版本

为了讲清楚，先考虑不带权的图。

我们不断随机找边，假设我们足够欧，能把最小割里的边全部剩下，也就是我们随机找了若干条边，这些边能够把原图连成恰好有两个连通块的图，那么最小割就是剩下的边中横跨这两个连通块的。

更具体的，整个流程可以描述成：每次均匀随机找一条边，把这条边的两个点缩成一个点，然后删掉所有自环，直到只剩下两个点，找到的最小割就是这两个最终的点之间的边权之和。

贴个原论文的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/y3vzd6xn.png)

这样做能得到真正的最小割当且仅当最小割的边没被缩掉。严谨地说，对于一个把图分成 $(A,B)$ 的割，它是这个算法的输出当且仅当所有跨过 $A$ 和 $B$ 的边都没有被缩掉。

考虑这样做的正确率。设最小割是 $c$,当图中有 $r$ 个结点时，因为最小度数是 $c,$ 所以图中至少有 $rc/2$ 条边，选中最小割的边的概率不超过 $2/r$,所以正确率是

$$(1-\dfrac 2n)(1-\dfrac 2{n-1})\dots (1-\dfrac 23)$$
$$=\dfrac 2{n(n-1)}$$
$$=\Omega(n^{-2})$$

对于带权的图，把权看作重边即可。当然不能把权拆了，我们可以在选边时以权为比例的概率来选取，这样就有了重边的效果。在缩边的过程中还可以顺便把重边合并了。正确率分析过程是相同的，能得到一样的结果。

## 2 实现

对于随机选边，直接选是 $O(m)$ 的，我们可以用这样一种技巧：先以度数为比例随机选一个顶点，然后在这个点的出边中以权为比例选一条边。容易知道这样选是等效的，而时间优化为了 $O(n)$

对于缩边，我们用邻接矩阵来存图，不需要特别处理重边，也是 $O(n)$ 的。

一共要缩 $O(n)$ 次边，所以得到一个割是 $O(n^2)$,因为 $(1-\dfrac 1{n^2})^{cn^2}=e^{-c},$所以整个算法的复杂度是 $O(cn^4)$.本文中 $c$ 表示一个参数，使得算法错误率随 $c$ 指数级降低。

## 3 优化

这个复杂度是没有太大优势的，瓶颈出在错误率太高，需要重复太多次。降低错误率是很困难的，但我们冷静分析，使正确率变低的部分出在最后几步，最后 $3$ 个结点到 $2$ 个结点的一步居然有整整 $2/3$ 的概率失败，前面的计算全部功亏一篑。我们可以通过某种手段，重复利用前半部分的正确率高的信息，多算几次最后一步。

显然就是分治。但不能从中间分治，原因可以看后面。这里选择化归为规模是 $m=\lceil n/\sqrt2\rceil+1$ 的子问题，也就是先缩边到剩下 $m$ 个结点，这一步不选到最小割的边的概率能类似地得到，是

$$\dfrac{m(m-1)}{n(n-1)}>\dfrac{(n/\sqrt 2+1)(n/\sqrt 2)}{n(n-1)}>\dfrac 12$$

这样我们递归 $2$ 次规模为 $m$ 的子问题，平均来看就有 $1$ 个可以成功得到最小割。

严谨地说，设从下往上第 $k$ 层递归成功概率是 $p_k,p_0$ 是常数，有 $p_{k+1}\geq 1-(1-\dfrac 12 p_{k})^2,$ 最坏情况下 $p_{k+1}=p_k-\dfrac 14 p_k^2.$ 设 $p_k$ 规模是 $k^t,p_{k+1}-p_k=O(k^{t-1}),$ 有 $k^{t-1}\sim k^{2t},t=-1,$ 即 $p_k=\Theta(1/k).$ 原问题的层数是 $\log n$ 级别的，所以该递归算法正确率是 $\Theta(1/\log n)$.如果从中间分治，不能使得 $p_{k+1}$ 和 $p_{k}$ 系数相同，这样 $p_k$ 会以指数的速度趋于 $0.$

一次试验的复杂度是 $T(n)=O(n^2)+2T(n/\sqrt 2)$,根据主定理，复杂度是 $T(n)=O(n^2\log n)$

得到答案需要 $c\log n$ 次试验，复杂度是 $O(cn^2\log^2 n)$

## 4 代码

递归时可以用回退数据结构来记录修改，回溯时撤销即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
const int N=600,M=N*N,MAXN=N+5,MAXM=M+5;
const double SQRT2=sqrt(2);
inline int read()
{
    int ans=0;
    char c=getchar();
    while (!isdigit(c)) c=getchar();
    while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
    return ans;
}
vector<pair<int*,int> > his;
inline int modify(int* p,int x){his.push_back(make_pair(p,*p)),*p=x;return x;}
inline void undo(int rec=0){while ((int)his.size()>rec) *his.back().first=his.back().second,his.pop_back();}
int deg[MAXN],n,m,ans;
int g[MAXN][MAXN],nxt[MAXN];
int idx[MAXN],sum[MAXN],tot;
int random_select()
{
    for (int i=1;i<=tot;i++) sum[i]+=sum[i-1];
    int x=1.0*rand()/RAND_MAX*sum[tot];
    return upper_bound(sum+1,sum+tot+1,x)-sum;
}
void contract(int T)
{
    while (T--)
    {
        tot=0;
        for (int i=nxt[0];i;i=nxt[i]) idx[++tot]=i;
        for (int i=1;i<=tot;i++) sum[i]=deg[idx[i]];
        int u=idx[random_select()];
        tot=0;
        for (int i=nxt[0];i;i=nxt[i]) if (u!=i&&g[u][i]) idx[++tot]=i;
        for (int i=1;i<=tot;i++) sum[i]=g[u][idx[i]];
        int v=idx[random_select()];
        for (int w=nxt[0];w;w=nxt[w])
            if (w!=u&&w!=v)
            {
                modify(&g[u][w],g[u][w]+g[v][w]);
                modify(&g[w][u],g[w][u]+g[w][v]);
            } 
        modify(&deg[u],deg[u]+deg[v]-2*g[u][v]);
        for (int i=0;nxt[i];i=nxt[i]) if (nxt[i]==v) modify(&nxt[i],nxt[v]);
    }
}
int solve(int n)
{
    if (n<=6)
    {
        int ans=0,rec=his.size();
        contract(n-2);
        ans=deg[nxt[0]];              
        undo(rec);
        return ans;
    }
    int res=0x7fffffff,m=n/SQRT2+1;
    for (int T=2;T;T--)
    {
        int rec=his.size();
        contract(n-m);
        res=min(res,solve(m));
        undo(rec);
    }
    return res;
}
int main()
{
    n=read(),m=read();
    for (int i=1;i<=n;i++) nxt[i]=i+1;
    nxt[0]=1,nxt[n]=0;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        u=read(),v=read(),w=read();
        g[u][v]+=w,g[v][u]+=w;
        deg[u]+=w,deg[v]+=w;
    }
    int output=1e9;
    for (int T=100/log(n);T;T--)
        output=min(output,solve(n));      
    cout<<output;
    return 0;
}
```
~~别问我100/log(n)是什么东西，问就是玄学~~

## 5 其他信息

- 如果跑 $O(c\log^2n)$ 次试验，甚至能有较大概率找到所有解。当然 $n$ 要足够大。

- 用邻接表存图可以做到空间 $O(m),$ 但时间没有变，所以没啥用

- 对于稀疏图，一次性算出边权的前缀和，用二分一次性随机找多条边(大概 $m/\log m$)一起缩，可以优化几个 $\log$

---

## 作者：A1443356159 (赞：9)

# Stoer-Wagner

[很好的学习资料](https://basics.sjtu.edu.cn/~dominik/teaching/2016-cs214/presentation-slides/2016-12-06-StoerWagner-BigNews.pdf)。

算法的过程其他题解已经说的很清楚了，主要说说 MinimumCutPhase 的证明。

设在 MinimumCutPhase 过程中加入的序列以 $s,t$ 结尾，规定，$w(S,t)$ =$\sum\limits_{s\in S}E(s,t)$，$A_t$ 表示在 MinimumCutPhase 过程中比 $t$ 先加入的点的集合，$C_t$ 表示 $s,t$ 的最小割，$w(C_t)$ 表示割的大小。

证明在任意时刻 $w(A_t,t)$ =$C_t$。（注：此时不考虑没有加入序列的点）

可以看出，这么割是把 $t$ 这个点单独割了出来，所以，只需要证明，把前面任意一个点与 $t$ 放在割的同一边后答案不会更优秀。

归纳证明，令 $u$ 是与 $t$ 在割的同一边的最后加入序列的那个点，$v$ 是在 $u$ 之后加入序列的那个点。

令 $CC$ 表示 $u$ 与 $t$ 在割的同一边那个割。
$$
w(A_t,t)=w(A_v,t)+w(A_t\backslash A_v,t)
$$
因为 $v$ 比 $t$ 先加入序列，所以
$$
w(A_v,t)\le w(A_v,v)
$$
又因为 $w(A_v,v)=C_v$，所以
$$
w(A_v,t)\le w(A_v,v)\le C_v
$$


因为 $C_v,E(A_t\backslash A_v,t)\in CC$  并且 $C_v \cap E(A_t\backslash A_v,t)=\empty$，所以
$$
w(C_v)+w(A_t\backslash A_v,t)\le CC
$$
联立一下就是，
$$
w(A_v,t)+w(A_t\backslash A_v,t)\le CC\\
w(A_t,t)\le CC
$$

于是证明了把前面任意一个点与 $t$ 放在割的同一边后答案不会更优秀，所以 $C_t=w(A_t,t)$。



---

## 作者：Mine_King (赞：8)

## 问题描述

给你一张有边权的连通无向图 $G = (V, E)$，定义这张图上的一组割 $C \subseteq E$ 满足删去 $E$ 中的边后 $G$ 不连通。求割的边权和的最小值。

## Stoer-Wagner 算法

该算法基于一个基本事实：对于任意两点 $s, t$，一组割要么把它们分到不同的连通块中，要么把它们分到同一连通块中。

该算法的核心思想是每次选出两个点 $s, t$，求出这两个点之间的最小割，然后把这两个点合并起来（点合并，对于连接的边取并集，连向相同的边权值相加）继续做直到只剩一个点。

考虑通过一些特殊的选 $s, t$ 的方法使得这两个点的最小割可以快速求出来。

设当前的图为 $G' = (V', E')$，维护一个点集 $A$，初始时为 $\varnothing$。

定义 $d(u, v)$ 为 $u, v$ 之间边的权值，若没有这条边则 $d(u, v) = 0$。  
对于一个点 $u \notin A$，定义 $w(u) = \sum _ {v \in A} d(u, v)$。

每次选择 $w$ 最大的点 $u$，将其加入 $A$，设最后加入的点为 $t$，倒数第二个加入的点为 $s$，则 $w(t)$ 为 $s, t$ 的最小割的大小。

这个被称为 MinimumCutPhase。

那为啥这个是对的啊？

我们定义一个点 $v$ 在割 $C$ 中是 Active 的当且仅当在 $v$ 前最后一个加入到 $A$ 中的点 $u$ 与 $v$ 在割 $C$ 中不属于同一个连通块。  
定义 $A _ v$ 为 $v$ 刚要加入前的 $A$，$C _ S$ 为 $C$ 在点集 $S$ 中的割的大小。

> 引理：对于任意一个割 $C$ 和任意一个 Active 的点 $u$，$w(u) \le C _ {A _ u \cup \{u\}}$。

考虑归纳证明：对于第一个 Active 的点 $u$，显然 $w(u) = C _ {A _ u \cup \{u\}}$。  
对于一个 Active 的点 $u$ 和其之后第一个 Active 的点 $v$，将 $w(v)$ 的贡献拆开：

$$
w(v) = \sum\limits _ {a \in A _ u} d(v, a) + \sum\limits _ {a \in A _ v \setminus A _ u} d(v, a)
$$

对于前半部分： $\sum _ {a \in A _ u} d(v, a) \le w(u) \le C _ {A _ u \cup \{u\}}$，对于后半部分：$\sum _ {a \in A _ v \setminus A _ u} d(v, a) = C _ {(A _ v \cup \{v\}) \setminus A _ u}$。

所以 $w(v) \le C _ {A _ u \cup \{u\}} + C _ {(A _ v \cup \{v\}) \setminus A _ u} \le C _ {A _ v \cup \{v\}}$，引理得证。

因此对于任意一个将 $s, t$ 分开的割 $C$，$t$ 都是 Active 的，所以 $w(t) \le C$，并且将 $t$ 单独割开是一个合法的割且能取到等号，因此 $w(t)$ 即为割开 $s, t$ 的最小割。

时间复杂度是 $O(|V| ^ 3)$，可以使用斐波那契堆优化到 $O(|V||E| + |V| ^ 2 \log |V|)$，但是常数巨大且写起来麻烦，实用价值偏低，故这里不再展开。

以下是一个 $O(|V| ^ 3)$ 的实现：

```cpp
int n, m, g[605][605], vis1[605], vis2[605];
long long w[605];

long long Stoer_Wagner() {
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i < n; i++) {
		int s = 0, t = 0;
		memset(vis2, 0, sizeof(vis2));
		memset(w, 0, sizeof(w));
		for (int j = 1; j <= n - i + 1; j++) {
			int now = 0;
			for (int k = 1; k <= n; k++)
				if (!vis1[k] && !vis2[k] && w[k] >= w[now]) now = k;
			s = t, t = now;
			vis2[now] = 1;
			for (int k = 1; k <= n; k++) w[k] += g[k][now];
		}
		ans = min(ans, w[t]);
		vis1[t] = 1;
		for (int j = 1; j <= n; j++)
			if (j != s) g[s][j] += g[t][j], g[j][s] += g[j][t];
	}
	return ans;
}
```

参考：<https://www.cnblogs.com/oyking/p/7339153.html>

---

## 作者：Belia (赞：1)

### $\mathcal{Stoer-Wagner}$：

给定一个无向图 $G$，求其最小割（即删除一个边集使得图分成两个连通分量，且删除边的权值和最小）。如果图不连通，输出 $0$。

### 证明过程：

#### 1. 算法目标
全局最小割定义为：
$$
\min_{\emptyset \subsetneq S \subsetneq V} w(S, V\setminus S) = \min_{\emptyset \subsetneq S \subsetneq V} \left( \sum_{\substack{u \in S \\ v \in V\setminus S}} w(u,v) \right)
$$

#### 2. 核心思想
合并操作保持最小割性质：
$$
\text{mincut}(G) = \min \left\{ w(A_{n-1}, \{t\}),\  \text{mincut}(G') \right\}
$$
其中 $G'$ 是合并 $t$ 到 $s$ 后的图。

#### 3. 正确性证明
**(a) 最小割结构**：
$$
\forall \text{最小割 } C,\quad (s,t \text{ 被 } C \text{ 分离}) \lor (s,t \text{ 在 } C \text{ 同侧})
$$

**(b) 合并引理**：
$$
\text{mincut}(G_{merged}) = \min_{C \text{ 不分离 } s,t} w(C)
$$

**(c) 数学归纳**：
$$
\begin{cases}
\text{基例 } (n=2): & \text{mincut} = w(s,t) \\
\text{假设 } (k<n): & \forall |V|<n \text{ 算法正确} \\
\text{归纳 } (n\text{ 节点}): & 
\begin{aligned}
\text{mincut}(G) = \min \Big\{ & \underbrace{w(A_{n-1}, \{t\})}_{\text{$s$-$t$ 割}}, \\
& \underbrace{\text{mincut}(G/\{s,t\})}_{\text{合并后最小割}} \Big\}
\end{aligned}
\end{cases}
$$

#### 4. 关键步骤证明
**(a) 最大邻接序性质**：
设 $A_k = \{v_1,\dots,v_k\}$，加入顺序满足：
$$
v_{k+1} = \arg\max_{v \notin A_k} w(v, A_k)
$$
则前缀割权值为：
$$
w(A_k, V\setminus A_k) = \sum_{i=1}^{k} w(v_i, v_{k+1})
$$

**(b) $s$-$t$ 割最优性**：
对最后两个节点 $s=v_{n-1}, t=v_n$：
$$
\lambda(s,t) = w(A_{n-1}, \{t\}) = \min_{u \in A_{n-1}} \lambda(u,t)
$$

#### 5. 时间复杂度分析
$$
T(n) = \underbrace{O(n)}_{\text{合并次数}} \times \underbrace{O(n^2)}_{\text{单轮操作}} = O(n^3)
$$

#### 6. 空间复杂度
邻接矩阵存储：
$$
S(n) = O\left( \sum_{i=1}^{n} \sum_{j=1}^{n} 1 \right) = O(n^2)
$$

#### 7. 合并操作形式化
合并 $t$ 到 $s$ 的边权更新：
$$
\forall v \notin \{s,t\},\quad 
\begin{cases}
w'(s,v) = w(s,v) + w(t,v) \\
w'(v,s) = w(v,s) + w(v,t)
\end{cases}
$$

#### 算法伪代码
$$
\begin{array}{l}
\hline
\text{STOER-WAGNER}(G=(V,E,w)) \\
\hline
1.\quad \text{mincut} \gets \infty \\
2.\quad \textbf{while } |V| > 1 \textbf{ do} \\
3.\quad \quad A \gets [v_1] \quad \text{// 任意起点} \\
4.\quad \quad \textbf{for } k = 2 \textbf{ to } |V| \\
5.\quad \quad \quad v_k \gets \arg\max_{v \notin A} w(v, A) \\
6.\quad \quad \quad \text{cut}_k \gets w(A, \{v_k\}) \\
7.\quad \quad \textbf{end for} \\
8.\quad \quad s \gets v_{|V|-1}, t \gets v_{|V|} \\
9.\quad \quad \text{mincut} \gets \min(\text{mincut}, \text{cut}_{|V|}) \\
10.\quad \quad G \gets G / \{s,t\} \quad \text{// 合并 $t$ 到 $s$} \\
11.\quad \textbf{end while} \\
12.\quad \textbf{return mincut} \\
\hline
\end{array}
$$

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long//#define ll long long你值得拥有
#define ull unsigned long long//#define ull unsigned long long你值得拥有
using namespace std;
const int maxn=605;
const ull INF=1e18;
ull w,val,now,minc=INF,g[maxn][maxn],del[maxn],d[maxn],vis[maxn];
ll a,b,n,m;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//cincout加速代码
    cin>>n>>m;
    for(ll i=1;i<=n;i++)
    for(ll j=1;j<=n;j++)
    g[i][j]=0;
    while(m--)
    cin>>a>>b>>w,g[a][b]+=w,g[b][a]+=w;
    for(ll i=1;i<=n;i++)
	del[i]=0;
    for(ll it=0,cnt,s,t,st,pre;it<n-1;it++)
    {
        for(ll i=1;i<=n;i++)
		vis[i]=0,d[i]=0;
        cnt=n-it,s=-1,t=-1,st=1,val=0;
        while(del[st])
		st++;
        vis[st]=1,pre=st;
        for(ll k=1;k<=cnt-1;k++)
        {
            now=-1;
            for(ll j=1;j<=n;j++)
            {
                if(del[j]||vis[j])
				continue;
                d[j]+=g[pre][j];
                if(now==-1||d[j]>d[now])
				now=j;
            }
            if(now==-1)
			break;
            vis[now]=1,val=d[now];
            if(k==cnt-1)
			s=pre,t=now;
            pre=now;
        }
        if(val<minc)
		minc=val;
        if(minc==0)
		break;
        for(ll j=1;j<=n;j++)
        {
            if(del[j]||j==t)
			continue;
            g[s][j]+=g[t][j],g[j][s]+=g[t][j];
        }
        del[t]=1;
    }
    if(minc==INF)
	minc=0;
    cout<<minc<<"\n";
    return 0;
}
```
~~轻松搞定~~！

---

## 作者：yangdezuo (赞：1)

## 题目描述
定义无向图 $G$ 的最小割为：一个去掉后可以使 $G$ 变成两个连通分量，且边权和最小的边集的边权和。

给出一张无向图 $G$，求其最小割。
## 这就是简单的图论知识（Stoer–Wagner 算法）
对于任何被激活的点 $v$，$w(A_v, v) \le w(C_v)$。

证明：使用数学归纳法。

对于第一个被激活的点 $v_0$，由定义可知 $w(A_{v_0}, v_0) = w(C_{v_0})$。

对于之后两个被激活的点 $u$, $v$，假设 $\operatorname{pos}(v) < \operatorname{pos}(u)$，则有：

$w(A_u, u) = w(A_v, u) + w(A_u - A_v, u)$

又，已知：

$w(A_v, u) \le w(A_v, v)$ 并且 $w(A_v, v) \le w(C_v)$ 联立可得：

$w(A_u, u) \le w(C_v) + w(A_u - A_v, u)$

由于 $w(A_u - A_v, u)$ 对 $w(C_u)$有贡献而对 $w(C_v)$ 没有贡献，在所有边均为正权的情况下，可导出：

$w(A_u,u) \le w(C_u)$

由归纳法得证。

由于 $\operatorname{pos}(s) < \operatorname{pos}(t)$，并且 $s$, $t$ 不在同一连通块，因此 $t$ 会被激活，由此可以得出 $w(A_t, t) \le w(C_t) = w(C)$。
```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(1,2,3,"Ofast","inline","-fgcse","-fgcse-lm","-fipa-sra","-ftree-pre","-ftree-vrp","-fpeephole2","-ffast-math","-fsched-spec","unroll-loops","-falign-jumps","-falign-loops","-falign-labels","-fdevirtualize","-fcaller-saves","-fcrossjumping","-fthread-jumps","-funroll-loops","-fwhole-program","-freorder-blocks","-fschedule-insns","inline-functions","-ftree-tail-merge","-fschedule-insns2","-fstrict-aliasing","-fstrict-overflow","-falign-functions","-fcse-skip-blocks","-fcse-follow-jumps","-fsched-interblock","-fpartial-inlining","no-stack-protector","-freorder-functions","-findirect-inlining","-fhoist-adjacent-loads","-frerun-cse-after-loop","inline-small-functions","-finline-small-functions","-ftree-switch-conversion","-foptimize-sibling-calls","-fexpensive-optimizations","-funsafe-loop-optimizations","inline-functions-called-once","-fdelete-null-pointer-checks")
//#pragma G++ optimize(1,2,3,"Ofast","inline","-fgcse","-fgcse-lm","-fipa-sra","-ftree-pre","-ftree-vrp","-fpeephole2","-ffast-math","-fsched-spec","unroll-loops","-falign-jumps","-falign-loops","-falign-labels","-fdevirtualize","-fcaller-saves","-fcrossjumping","-fthread-jumps","-funroll-loops","-fwhole-program","-freorder-blocks","-fschedule-insns","inline-functions","-ftree-tail-merge","-fschedule-insns2","-fstrict-aliasing","-fstrict-overflow","-falign-functions","-fcse-skip-blocks","-fcse-follow-jumps","-fsched-interblock","-fpartial-inlining","no-stack-protector","-freorder-functions","-findirect-inlining","-fhoist-adjacent-loads","-frerun-cse-after-loop","inline-small-functions","-finline-small-functions","-ftree-switch-conversion","-foptimize-sibling-calls","-fexpensive-optimizations","-funsafe-loop-optimizations","inline-functions-called-once","-fdelete-null-pointer-checks")       //O3优化
#define int long long
using namespace std;
const int N=601;
const int inf=0x3f3f3f3f;
int fa[N],siz[N],edge[N][N],dist[N],vis[N],bin[N],n, m;//定义
int find(int x){  查找（并查集模板）
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int contract(int &s, int &t){
	memset(dist,0,sizeof(dist));
	memset(vis,false,sizeof(vis));
	int k,mincut,maxc;
	for(int i=1;i<=n;i++){
		k=-1;
		maxc=-1;
		for(int j=1;j<=n;j++) if(!bin[j]&&!vis[j]&&dist[j]>maxc) k=j,maxc=dist[j];
		if(k==-1) return mincut;
		s=t,t=k;
		mincut=maxc;
		vis[k]=true;
		for(int j=1;j<=n;j++) if(!bin[j]&&!vis[j]) dist[j]+=edge[k][j];
	}
	return mincut;
}

int Stoer_Wagner(){  二分
	int mincut,s,t,ans;
	for(int i=1;i<n;i++){
		mincut=inf;
		ans=contract(s,t);
		bin[t]=true;
		if(mincut>ans) mincut=ans;
		if(mincut==0) return 0;
		for(int j=1;j<=n;j++) if(!bin[j]) edge[s][j]=(edge[j][s]+=edge[j][t]);
	}
	return mincut;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0); //优化cin和cout
	cin>>n>>m;
	if(m<n-1){  //特判
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1; //初始化
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		int fu=find(u),fv=find(v);  
		if(fu!=fv){      //并查集模板
			if(siz[fu]>siz[fv]) swap(fu,fv);
			fa[fu]=fv,siz[fv]+=siz[fu];
		}
		edge[u][v]+=w,edge[v][u]+=w;
	}
	int fr=find(1);
	if(siz[fr]!=n){    \\特判
		cout<<0;
		return 0;
	}
	cout<<Stoer_Wagner();  \\最后输出
}
```

---

## 作者：RockyYue (赞：0)

只讲过程，不谈证明。

> 结论：
>
> - $G(V,E)$，点集 $A$ 初始为空，定义点集外点 $X$ 到 $A$ 的距离 $dis(X,A)=\sum _{v\in A} d(X,v)$，其中 $d(X,v)$ 为两点**边权**（不连边则为 $0$）。
> - 对 $V$ 中所有点，每次加入 $dis(X,A)$ 最大的点 $X$（$dis$ 随 $A$ 动态变化），则以当前最后加入两个点为源汇的，在以 $A$ 为点集的诱导子图中的最小割，即为最后一个点加入时的 $dis$。

1. 每次对当前图做上述过程，用最后加入的两个点在当前整张图的最小割更新答案。
2. 将这两个点 $s$ 和 $t$ 合并，具体地，删除其中一个点 $s$，并对所有还存在的点 $u$，更新 $w(t,u)\stackrel +\longleftarrow w(s,u)$，其中 $w$ 为两点间双向边权。
3. 重复第一步，直到所有点被合并到一个点，这整个过程是 $O(n^2\log n+nm)$ 的，实现中注意重边边权叠加。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=605;
int n,m,g[N][N],dis[N];
bool inA[N],alive[N];
int cal(int &s,int &t){
	for(int i=1;i<=n;++i)inA[i]=0,dis[i]=0;
	int k,maxd; int lstd=0;
	for(int i=1;i<=n;++i){
		k=maxd=-1;
		for(int j=1;j<=n;++j){
			if(alive[j]&&!inA[j]&&dis[j]>maxd)maxd=dis[j],k=j;
		}
		if(k==-1)return lstd;	// 所有点已经加入
		inA[k]=1;
		s=t,t=k; lstd=maxd;
		for(int j=1;j<=n;++j){
			if(alive[j]&&!inA[j])dis[j]+=g[k][j];
		}
	}
	return maxd;
}
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin>>n>>m;
	while(m--){
		int u,v,w;cin>>u>>v>>w;
		g[u][v]+=w,g[v][u]+=w;
		int x=find(u),y=find(v);
		if(x!=y)fa[x]=y;
	}
	int rt=find(1);
	for(int i=2;i<=n;++i){
		if(find(i)!=rt){cout<<0<<'\n';return 0;}
	}
	int s=0,t=0,res=1e9;
	for(int i=1;i<=n;++i)alive[i]=1;
	for(int i=1;i<n;++i){
		res=min(res,cal(s,t));
		alive[s]=0;
		for(int j=1;j<=n;++j){
			if(alive[j])g[t][j]=(g[j][t]+=g[s][j]);
		}
	}
	cout<<res<<'\n';
	return 0;
}
```

---

