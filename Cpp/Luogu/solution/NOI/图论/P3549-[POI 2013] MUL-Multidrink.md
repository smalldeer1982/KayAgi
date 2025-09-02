# [POI 2013] MUL-Multidrink

## 题目背景

**本题翻译为 AI 生成。**

## 题目描述

Byteasar 住在 Byteburg，一座以每个街角都有牛奶吧而闻名的城市。某天，Byteasar 想出了一个“牛奶多饮计划”：他希望每个牛奶吧只去喝一次。理想情况下，他希望设计一条路线，使得每次前往下一个牛奶吧时，其距离上一个牛奶吧不会超过两个街区（即：路口）。

Byteburg 的路口从 $1$ 到 $N$ 编号，所有街道都是双向通行的。在每对路口之间，存在唯一的一条直接路径，即不会重复经过任何路口的路径。Byteasar 将从编号为 $1$ 的路口出发，并在编号为 $N$ 的路口结束。你的任务是找出一条满足 Byteasar 要求的任意路线（如果存在的话）。

## 样例 #1

### 输入

```
12
1 7
7 8
7 11
7 2
2 4
4 10
2 5
5 9
2 6
3 6
3 12
```

### 输出

```
1
11
8
7
4
10
2
9
5
6
3
12
```

# 题解

## 作者：A_zjzj (赞：20)

其他题解都是大码量的直接构造，来一发 dp 的题解。

思路很明确，直接 dp，然后输出路径即可。

考虑先把 $1\to n$ 的路径找出来，记为 $a_i(1\le i\le m)$。

那么肯定存在一种路径依次经过这些点的子树，然后遍历完 $a_i$ 的子树后再遍历 $a_{i+1}$ 的子树。

这样的话，每个 $a_i$ 的子树就各自独立了，所以分别对每个子树进行求解。

#### 遍历子树

由于每次最多只能跳 $2$ 步，所以如果要遍历 $u$ 的子树内的所有点，那么只有以下几种情况：

- 先到 $u$，然后从 $u$ 跳出去（当且仅当 $u$ 为叶子节点时可以）；

- 先到 $u$，然后从 $u$ 的某个儿子跳出去；

- 先到 $u$ 的某个儿子，然后从 $u$ 的某个儿子跳出去；

- 先到 $u$ 的某个儿子，然后从 $u$ 跳出去。

观察这些情况，发现第二种和第四种本质上是一样的，无非就是遍历顺序正反而已，先合并为一种。

于是，设 $f_{u,i=0/1/2}$ 分别为上述的第 $i+1$ 中情况是否可行。

考虑如何转移：

$f_{u,0}=[u\ is\ \texttt{leaf}];$

$f_{u,1}$ 至多可以先跳到一个非叶子的儿子遍历，最后停在这个儿子，接着跳到其他的叶子的儿子。

即 $f_{u,1}=\operatorname{and}_{v\in son(u)}f_{v,0}/f_{v,1}$，其中只能有一个 $f_{v,1}$。

所以转移就是：

```cpp
f[u][1]=1;
int t1=0;
for(int v:A[u])if(v^fa&&!vis[v]){
	dfs(v,u);
	if(!f[v][0])
		if(!f[v][1])f[u][1]=0;
		else if(++t1>1)f[u][1]=0;
}
```

$f_{u,2}$ 的话就是要有两个儿子可以先到 $v$，再从 $v$ 的儿子跳出或先到 $v$ 的儿子再从 $v$ 跳出（两个儿子的遍历顺序决定了是属于第二种还是第四种，先遍历到的选择第二种，后遍历到的选择第四种）。

转移如下：

```cpp
f[u][2]=1;
int t2=0;
for(int v:A[u])if(v^fa&&!vis[v]){
	dfs(v,u);
	if(!f[v][0])
		if(!f[v][1])f[u][2]=0;
		else if(++t2>2)f[u][2]=0;
}
```

这样 $f$ 就可以 $O(n)$ 完成转移了。

#### 遍历 $1\to n$ 的链

设 $g_{i,0/1}$ 表示 $a_i$ 的子树遍历完之后，在 $u$ 或 $u$ 的某个儿子，是否可行。

这样就很简单了，枚举 $a_i$ 和 $a_{i+1}$ 的状态，选择合适的 $f_{a_{i+1}}$ 进行转移即可。

转移见代码，其实并不难，复杂度也是 $O(n)$。

### 总结

至此，我们已经完成了 $f,g$ 的转移，判断有解无解，然后按照转移的方式输出 dp 的路径即可。

具体实现见代码，总复杂度：$O(n)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;const int N=5e5+10;
int n,m,top,a[N],stk[N],vis[N],f[N][3],g[N][2];vector<int>ans,A[N];
void add(int u,int v){A[u].push_back(v);A[v].push_back(u);}
void find(int u,int fa=0){
	stk[++top]=u;if(u==n)copy(stk+1,stk+1+top,a+1),m=top;
	for(int v:A[u])if(v^fa)find(v,u);stk[top--]=0;
}
void dfs(int u,int fa=0){
	f[u][0]=f[u][1]=f[u][2]=1;
	int t=0,t1=0,t2=0;
	for(int v:A[u])if(v^fa&&!vis[v]){//f 的转移
		t++;dfs(v,u);
		if(!f[v][0])if(!f[v][1])f[u][1]=0;else if(++t1>1)f[u][1]=0;
		if(!f[v][0])if(!f[v][1])f[u][2]=0;else if(++t2>2)f[u][2]=0;
	}
	if(t)f[u][0]=0;else f[u][1]=f[u][2]=0;//特判叶子节点
}
void findf(int u,int i,int fa=0){
	if(!i){
		ans.push_back(u);//叶子节点
	}
	else if(i==1){//u 开始,v 结束
		ans.push_back(u);//因为是 u 开始,所以直接把 u 扔进去就好了
		for(int v:A[u])if(v^fa&&!vis[v]){//先遍历非叶子
			if(!f[v][0])findf(v,3,u);
		}
		for(int v:A[u])if(v^fa&&!vis[v]){//再遍历叶子
			if(f[v][0])findf(v,0,u);
		}
	}
	else if(i==2){//v 开始,v' 结束
		int t=0;
		for(int v:A[u])if(v^fa&&!vis[v]){
			if(!f[v][0])t++;
		}
		if(t==1)return findf(u,1,fa);//必须要找到两个不同的 v 和 v',否则就是第 2 种情况
		t=0;
		for(int v:A[u])if(v^fa&&!vis[v]){
			if(!f[v][0]){
				if(!t)findf(v,1,u),ans.push_back(u),t++;
				else findf(v,3,u);
				//第一个 v 先到 v,再到儿子
				//第二个 v' 先到儿子，再到 v'
			}
		}
		for(int v:A[u])if(v^fa&&!vis[v]){
			if(f[v][0])findf(v,0,u);//最后遍历叶子节点
		}
	}else{//与情况 2 类似,倒着做就好了
		for(int v:A[u])if(v^fa&&!vis[v]){
			if(f[v][0])findf(v,0,u);
		}
		for(int v:A[u])if(v^fa&&!vis[v]){
			if(!f[v][0])findf(v,1,u);
		}
		ans.push_back(u);
	}
}
void findg(int i,int j){//g 的路径输出
	if(i==1){
		findf(i,j);
		return;
	}
	int u=a[i];
	if(j==0){//直接照搬转移的方程即可
		if(g[i-1][0]&f[u][0])return findg(i-1,0),findf(u,0);
		if(g[i-1][0]&f[u][1])return findg(i-1,0),findf(u,3);
		findg(i-1,1);findf(u,0);
	}else{
		if(g[i-1][0]&f[u][1])return findg(i-1,0),findf(u,1);
		if(g[i-1][0]&f[u][2])return findg(i-1,0),findf(u,2);
		findg(i-1,1);findf(u,1);
	}
}
int main(){
	scanf("%d",&n);for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),add(u,v);
	find(1);for(int i=1;i<=m;i++)vis[a[i]]=1;for(int i=1;i<=m;i++)dfs(a[i]);
	g[1][0]=f[1][0];g[1][1]=f[1][1];//g 的初始化
	for(int i=2,u;u=a[i],i<=m;i++){//g 的转移
		g[i][0]|=g[i-1][0]&(f[u][0]|f[u][1]);
		g[i][0]|=g[i-1][1]&f[u][0];
		g[i][1]|=g[i-1][0]&(f[u][1]|f[u][2]);
		g[i][1]|=g[i-1][1]&f[u][1];
	}
	if(!g[m][0])return puts("BRAK"),0;//注意最后要落在 n，所以 g[m][1] 没有用
	findg(m,0);
	for(int x:ans)printf("%d\n",x);
	return 0;
}

```
### 谢谢您的阅读，有问题请指出


---

## 作者：Tsawke (赞：14)

# [LG-P3549 [POI2013]MUL-Multidrink](https://www.luogu.com.cn/problem/P3549) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P3549-Solution)

（建议您从上方链接进入我的个人网站查看此 Blog，在 Luogu 中图片会被墙掉，部分 Markdown 也会失效）

## 题面

~~一道论文题~~。

给定一棵有 $ n $ 个节点的树，令起点为 $ 1 $，终点为 $ n $，每步可以走的距离为 $ 1 $ 或 $ 2 $，要求不重复地遍历 $ n $ 个节点。

如果无解输出 `BARK`，否则输出 $ n $ 行，表示遍历的路径，存在 SPJ。

$ 1 \le n \le 5 \times 10^5 $。

## 输入格式

> $ n $
>
> Describe the tree($ n - 1 $ lines in total).

## 图例

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_10_04_2.png)

## Solution

本题大多数内容均参考自论文《Hamiltonian paths in the square of a tree》。

作者：Jakub Radoszewski and Wojciech Rytter。

原文链接：[Hamiltonian paths in the square of a tree](http://monkey-hyx.tech/Data/File/content/Hamiltonian%20paths%20in%20the%20square%20of%20a%20tree.pdf)

首先我们引入一个定义：caterpillar（毛毛虫），原文定义为 a single path with several leafs connected to it. 简而言之就是其为一棵树，一棵树为 caterpillar 当且仅当去掉其所有叶子节点后剩下的仅为一条单链，如图即为一个 caterpillar。

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_10_04_3.png)

对于其更多的性质及求法，可以去做一下 [LG-P3174 [HAOI2009] 毛毛虫](https://www.luogu.com.cn/problem/P3174)，但与本题关联不大，就不再赘述。

现在我们引入下一个定义，对于图 $ G = (V, E) $，我们定义 $ G $ 的 $ k $ 次幂，记作 $ G^k $，为一个基于（或者说完全覆盖，原文为 cover）点集 $ V $ 的图，对于 $ \forall u, v \in V $，$ u, v $ 之间有边相连当且仅当在 $ G $ 中 $ u, v $ 之间的路径长度不大于 $ k $。我们称 $ G^2 $ 为 the square of $ G $，称 $ G^3 $ 为 the cube of  $ G $。

然后我们再引入一个定义：2-connected graph（2-连通图），这个定义类似点双，对于具有割点的图我们定义其为 1-connected graph，则同理 2-connected graph 只得就是至少需要去掉两个顶点才能使图的连通分支增加。

现在我们再引入几个定理：

Lemma 1：对于树 $ T $，图 $ T^2 $ 包含哈密尔顿回路当且仅当 $ T $ 为一个 caterpillar。

Lemma 2：对于树 $ T $，图 $ T^2 $ 包含哈密尔顿路径当且仅当 $ T $ 为一个 horsetail。

证明：咕咕咕。

然后我们继续进行定义。

定义 $ P $ 为 $ G $ 的 k-path 当且仅当 $ P $ 为 $ G^k $ 中的一条路径，同理我们定义 k-cycle。

额外地，我们分别定义 $ G $ 的 kH-path 和 kH-cycle 为 $ G^k $ 中的哈密尔顿路径和哈密尔顿回路。

若 $ G^k $ 包含一个 kH-cycle，我们称 $ G $ 为 k-Hamiltonian（这玩意我也不知道怎么译），同理包含 kH-path 称为 k-traceable。

然后对于 caterpillar，我们额外定义其为 non-trivial 当且仅当其至少含有 $ 1 $ 条边。

我们称 caterpillar 的主链，也就是去掉叶子结点剩下的链，为 spine。

下面开始正文：

我们考虑将原图中 $ 1 $ 到 $ n $ 的路径抽离出来，作为其主干，然后将主干上每个点及其每个子树作为一个新的部分，这里有一个性质，对于这些非主干的部分，有一个性质：若其非 caterpillar，则一定无解，这个东西自己画一下找找性质就会发现很显然，~~当然严谨的证明我不会~~。

然后这里我们对于每个主干上的点划分为两类：

1. Type A：有不超过 $ 1 $ 个 non-trivial caterpillar。
2. Type B：有且仅有 $ 2 $ 个 non-trivial caterpillar。

不难发现，对于 Type A 的节点，若从主干上的节点进入，最后一步一定刚好走到下一个主干节点上，对于 Type B 的节点，在进入时必须直接进入到其任意子树中，否则无解，对于后面的无解判断我们主要也就靠这个性质。

这里有一个性质：若一个点有超过两个的 non-trivial caterpillar 则一定无解，这个依然，自己画一下会发现无论上一步刚好走到这个点还是直接走到某一个子树上，最终都是无解的，路径一定会断在某个子树中，~~同样严谨的证明我不会~~。

然后我们额外地定义一个点为 free 当且仅当其为单点，即没有任何子树的主干节点。

如下图例：

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_10_04_4.png)

下一个性质：每个 Type B 的节点前后都必须有至少一个 free 节点，否则无解。显然 free 点是可以将进入下一个主干节点和进入下一个主干节点的某一个子节点相互转换的，而 Type A 不能进行这样的转换，两棵 Type B 之间又需要有这样的转换。

对于满足以上所有性质的主干，我们称其为 $ (u, v) $ -horsetail，同时称这整棵树为 horsetail。

现在我们对上面的性质做一个总结：

1. 每一个主干节点都为 Type A 或 Type B。
2. 在任意两个 Type B 之间都至少有一个 free。
3. 在 Type B 之前至少有一个 free。
4. 在 Type B 之后至少有一个 free。
5. 至少有一个 free。

显然对于上面的四个图例中，(a)(b) 为 horsetail，有解，(c)(d) 非 horsetail，无解。

而对于我们本题的图 $ G $，我们也就需要先判断其是否为 horsetail，如果不是则无解，如果是那么说明 $ G^2 $，也就是按照本题要求构成的图，一定存在一条哈密顿路径，即 Lemma 2。

现在我们对 Lemma 1 进行进一步的阐释：

Lemma 1：任意一个在 caterpillar 上的 2H-cycle 都一定有以下的顺序：我们定义 caterpillar 的 spine 长度为 $ l $，令 spine 为 $ v_1, v_2, \cdots, v_l $，spine 上的叶子为 $ P_1, P_2, \cdots, P_l $，这里我们定义 $ P_i $ 表示一个任意的 $ v_i $ 的叶子的排列。
$$
\begin{aligned}
	&v_1, P_2, v_3, \cdots, v_{l - 1}, P_l, v_l, P_{l - 1}, \cdots, P_3, v_2, P_1 \quad 2 \mid l \\
	&v_1, P_2, v_3, \cdots, P_{l - 1}, v_l, P_l, v_{l - 1}, \cdots, P_3, v_2, P_1 \quad 2 \nmid l
\end{aligned}
$$
![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_10_05_1.png)

如此图中，显然 $ 1, 2, 3, \cdots, 8, 1 $ 和 $ 1, 2, 3, \cdots, 10, 1 $ 分别为两图的一种 2H-cycle。

所以当我们想要对 horsetail 上的 caterpillar 找到 2H-path 的时候，只需要取 2H-cycle 中的一部分，或者说断开 2H-cycle 中的一条边，如 $ 2, 3, 4, \cdots, 8, 1 $ 这种顺序。

然后再次回到本题，或者说回到 Lemma 2：

对于一个 2H-path $ S $，当树 $ T $ 上的节点被按照分别遍历每个主干节点的每个子树的顺序遍历时，同时我们定义每个主干节点 $ u_i $ 所在子树节点集合为 $ layer(u_i) $，满足每个 $ layer(u_i) $ 都按照特定顺序遍历，我们称树 $ T $ 为 layered，此时我们便可以根据每个主干节点的路径将 $ S $ 分成 $ S_1, S_2, S_3, \cdots $。我们定义一个路径 $ S $ 的起点和终点分别为 $ first(S) $ 和 $ last(S) $，定义主干节点为 main，主干节点直接连接的非主干节点为 secondary，则显然对于每个 $ i $，$ first(S_i) $ 和 $ last(S_i) $ 均为 main 或 secondary。

对于我们的算法我们首先需要实现一些辅助函数：（为了便于理解，部分函数名与原论文中有微调）

`vector < int > BuildCaterpillar(int mp, int S, int T)`：

对于从 $ S $ 开始 $ T $ 结束的，挂在 horsetail 的主干上的 $ 1 $ 或 $ 2 $ 条 caterpillar 生成 2H-path，这里我们首先需要对这一部分构建一个新的图，将 caterpillar 上所有叶子指向 spine，同时我们需要维护每条 caterpillar 的主干，具体通过代码中的 `void BuildSpine(int fa, int p)` 实现，我们称 caterpillar 所在的 horsetail 上的主干节点为 $ mp $，那么当 $ mp $ 为 type B 的时候，也就是 non-trivial 的 caterpillar 有两条的时候，我们便可以将前面一条 caterpillar 反过来与其首尾相接，当成同一条 caterpillar，这样最终我们对于形成的 caterpillar 进行如 Lemma 1 地生成 2H-cycle，然后断开其中 $ S \rightarrow T $ 的边（或 $ T \rightarrow S $）即可，同时需要注意如果起始点是在非 non-trivial 的 secondary 节点上，那么我们就需要先遍历其叶子节点，然后最后再遍历其 spine，对于遍历 $ mp $ 的叶子节点，我们通过 `void extend(int mp, int unreach1 = -1, int unreach2 = -1)` 实现，具体可以看一下代码。

`int FindAnySecondaryNode(int p)`：找到 horsetail 中主干为 $ p $ 的任意一个 secondary 节点。

`int FindAnySecondaryNode_PreferablyLeaf(int p)`：找到 horsetail 中主干为 $ p $ 的任意一个 secondary 节点，且优先找非 non-trivial 的叶子节点。

`int FindAnotherSecondaryNode(int p, int lst)`：找到 horsetail 中主干为 $ p $ 的非 $ lst $ 的另一个 secondary 节点。

然后对于具体的实现，首先我们需要检查一下其是否为无解，也就是前面的检查是否为 horsetail，具体由 `void Check(void)` 实现。

然后我们算法的核心就是找到 horsetail 的那一条 2H-path，通过 `vector < int > Get2HPathHorsetail(void)` 实现，大概的思路就是先对第一个节点进行讨论，显然起点一定为 $ 1 $，如果其为 free 节点那么终点也为 $ 1 $，否则一定为其的某一个 secondary 节点，然后构造此 2H-path，对于后面的每个点，如果是 free 节点那么起点终点均为主干点 $ mp $，否则如果上次的终点不是主干节点，这次的起点一定为 $ mp $，终点为优先找非 non-trivial 节点的任意一个 secondary 节点，如果上次的终点是主干节点，那么这次的起点一定为优先找非 non-trivial 节点的 secondary 节点，对于终点，如果该节点是 type B，那么终点也需要为 secondary 节点，找到另外的一个 secondary 节点即可，否则终点为 $ mp $ 即可。

大致的思路就是这样，码量大概 `7.5KiB`，随后的复杂度是 linear 的，也就是 $ O(n) $ 的。

同时这里提供一个原论文中的对于最后的 `Get2HPathHorsetail(void)` 的实现，可以选择性地看一下。

![Oops! The image is blocked! Please visit my own website to observe the image! 图片被墙了，请通过文章头的跳转链接访问！](http://monkey-hyx.tech/Images/Blog/2022_10_09_1.png)

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

/******************************
abbr
mp => mainp
subt => subtree
fa => father
fst => first
lst => last
******************************/

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define EXIT puts("BRAK"), exit(0)
#define MAXN 510000

template<typename T = int>
inline T read(void);

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[(MAXN << 1) + MAXN];
ROPNEW(ed);
Edge* head[MAXN];

int N;
int mainLen(0);
int fa[MAXN], deg[MAXN];
int mainp[MAXN];
int non_trivial[MAXN];
bool isMainp[MAXN], isFree[MAXN];

void dfs(int p = 1){
    for(auto i = head[p]; i; i = i->nxt)
        if(SON != fa[p])
            fa[SON] = p,
            dfs(SON);
}
void InitMainp(void){
    int cur = N;
    do{
        mainp[++mainLen] = cur;
        isMainp[cur] = true;
        cur = fa[cur];
    }while(cur != 1);
    mainp[++mainLen] = 1;
    isMainp[1] = true;
    reverse(mainp + 1, mainp + mainLen + 1);
}
bool isCaterpillar(int fa, int p){
    int cnt(0);
    for(auto i = head[p]; i; i = i->nxt){
        if(SON == fa || deg[SON] == 1)continue;
        if(!isCaterpillar(p, SON))return false;
        if(cnt++)return false;
    }return true;
}
void Check(void){
    for(int p = 1; p <= mainLen; ++p){
        int mp = mainp[p];
        isFree[mp] = true;
        for(auto i = head[mp]; i; i = i->nxt){
            if(isMainp[SON])continue;
            isFree[mp] = false;
            if(deg[SON] == 1)continue;
            ++non_trivial[mp];
            if(non_trivial[mp] > 2)EXIT;
            if(!isCaterpillar(mp, SON))EXIT;
        }
    }
    int curFree(0);
    bool end_with_B(true);
    bool exist_free(false);
    for(int p = 1; p <= mainLen; ++p){
        int mp = mainp[p];
        if(isFree[mp]){++curFree; exist_free = true; end_with_B = false; continue;}
        if(non_trivial[mp] == 2){
            if(!curFree)EXIT;
            curFree = 0;
            end_with_B = true;
        }
    }
    if(end_with_B || !exist_free)EXIT;
}
int FindAnySecondaryNode(int p){
    for(auto i = head[p]; i; i = i->nxt)
        if(!isMainp[SON])return SON;
    return -1;
}
int FindAnySecondaryNode_PreferablyLeaf(int p){
    for(auto i = head[p]; i; i = i->nxt)
        if(!isMainp[SON] && deg[SON] == 1)return SON;
    return FindAnySecondaryNode(p);
}
int FindAnotherSecondaryNode(int p, int lst){
    for(auto i = head[p]; i; i = i->nxt)
        if(!isMainp[SON] && SON != lst)return SON;
    return -1;
}
namespace Caterpillar{
    vector < int > route;
    Edge* head[MAXN];
    vector < int > spine;
    enum type{spineNode = 1, leafNode};
    int ffa[MAXN];
    void add(int s, int t){
        head[s] = new Edge{head[s], t};
        ffa[t] = s;
    }
    void BuildSpine(int fa, int p){
        spine.push_back(p);
        for(auto i = ::head[p]; i; i = i->nxt){
            if(SON == fa)continue;
            if(::deg[SON] == 1)add(p, SON);
            else BuildSpine(p, SON);
        }
    }
    void extend(int mp, int unreach1 = -1, int unreach2 = -1){
        for(auto i = head[mp]; i; i = i->nxt){
            if(SON == unreach1 || SON == unreach2)continue;
            route.push_back(SON);
        }
    }
    vector < int > BuildCaterpillar(int mp, int S, int T){
        route.clear();
        spine.clear();
        route.push_back(S);
        if(S == T)return route;
        spine.push_back(mp);
        bool exist_caterpillar(false);
        for(auto i = ::head[mp]; i; i = i->nxt){
            if(isMainp[SON])continue;
            if(deg[SON] == 1)add(mp, SON);
            else{
                if(!exist_caterpillar)exist_caterpillar = true;
                else reverse(spine.begin(), spine.end());
                BuildSpine(mp, SON);
            }
        }
        vector < pair < int, type >/*spine_node_pos, spine or leaf*/ > temp;
        vector < pair < int, type >/*spine_node_pos, spine or leaf*/ > unextended;
        for(int i = 0; i < (int)spine.size(); ++i)
            temp.push_back({spine.at(i), !(i & 1) ? spineNode : leafNode});
        for(int i = (int)spine.size() - 1; i >= 0; --i)
            temp.push_back({spine.at(i), (i & 1) ? spineNode : leafNode});
        for(auto it = temp.begin(); it < temp.end(); ++it)
            if(it->second == spineNode || head[it->first])unextended.push_back(*it);
        #define LEFT(x) (x == 0 ? (int)unextended.size() - 1 : x - 1)
        #define RIGHT(x) (x == (int)unextended.size() - 1 ? 0 : x + 1)
        auto Beg = deg[S] == 1 ? make_pair(ffa[S], leafNode) : make_pair(S, spineNode);
        auto End = deg[T] == 1 ? make_pair(ffa[T], leafNode) : make_pair(T, spineNode);
        int begPos = -1; while(unextended.at(++begPos) != Beg);
        if(Beg.second == leafNode)extend(Beg.first, S, T);
        if(unextended.at(LEFT(begPos)) == End)
            for(int j = RIGHT(begPos); unextended.at(j) != End; j = RIGHT(j))
                unextended.at(j).second == spineNode
                    ? route.push_back(unextended.at(j).first)
                    : extend(unextended.at(j).first);
        else
            for(int j = LEFT(begPos); unextended.at(j) != End; j = LEFT(j))
                unextended.at(j).second == spineNode
                    ? route.push_back(unextended.at(j).first)
                    : extend(unextended.at(j).first);
        if(End.second == leafNode && Beg != End)extend(End.first, S, T);
        route.push_back(T);
        return route;
    }
}
vector < int > Get2HPathHorsetail(void){
    vector < int > ret;
    int fst = mainp[1];
    int lst = isFree[mainp[1]]
        ? mainp[1]
        : FindAnySecondaryNode(mainp[1]);
    auto tmp = Caterpillar::BuildCaterpillar(mainp[1], fst, lst);
    ret.insert(ret.end(), tmp.begin(), tmp.end());
    for(int i = 2; i <= mainLen; ++i){
        int w = mainp[i];
        if(isFree[w])fst = lst = w;
        else if(!isMainp[lst])
            fst = w,
            lst = FindAnySecondaryNode_PreferablyLeaf(w);
        else
            fst = FindAnySecondaryNode_PreferablyLeaf(w),
            lst = non_trivial[w] == 2
                ? FindAnotherSecondaryNode(w, fst)
                : w;
        auto cp = Caterpillar::BuildCaterpillar(w, fst, lst);
        ret.insert(ret.end(), cp.begin(), cp.end());
    }
    return ret;
}
int main(){
    N = read();
    for(int i = 1; i <= N - 1; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
        ++deg[s], ++deg[t];
    }
    dfs();
    InitMainp();
    Check();
    auto ans = Get2HPathHorsetail();
    for(auto i : ans)printf("%d\n", i);
    return 0;
}
template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## 写在后面

就是这道不怎么友好的题，我做的时候网上几乎没有题解，只能找到几篇说的很简略的题解，然后没办法只能去自己翻英文论文，然后一个一个查词，在我快要写完这道题的时候，才突然发现 Luogu 上多出来了两篇题解。。

然后就是调这道题，一共交了 $ 70+ $ 次才过了这道题，自己写完之后怎么改都是 $ 70 $ pts，Luogu 上下不了数据，hydro 等没有 SPJ，没办法只能开始把每一部分的代码对着大佬的代码改，最后几乎把整篇代码都重构了一遍才找到错误，只是调代码就调了一天半，不过至少最后还是过了。

## UPD

update-2022_10_09 初稿

update-2022_10_10 修复一些错误

---

## 作者：ღꦿ࿐ (赞：11)

# P3549 MUL-Multidrink 解题报告

[P3549](https://www.luogu.com.cn/problem/P3549)

[在博客查看](https://www.cnblogs.com/Dreamerkk/p/17229249.html)

### $\text{0.前言}$

模拟赛场切留念。

值得一想值得一分析但是不值得一写的题。

这种复杂的题的题解还是要一步一步慢慢来，不能太跳跃也不能瞎扯些深奥的定义。

---

### $\text{1.一些说明}$

将树以 $1$ 为根。

“平凡儿子” 指 是叶子的儿子。

“非平凡儿子” 指的是 不是叶子的儿子。


“跳跃” 指从一个儿子跳到它的兄弟。

本文为方便读者理解~~也方便笔者制作~~，插入了部分手绘图片，笔者字丑还请见谅（也别在意我用的草稿纸是啥）。

如有笔误或逻辑错误欢迎指出。

---

### $\text{2.初步分析}$

距离小于等于 $2$ 就是跳儿子，父亲，兄弟，儿子的儿子和父亲的父亲。

首先题目要求了终点为 $n$，又因为一步最多跳的距离是 $2$，可以发现走进 $n$ 的子树后再走出来就无法回到 $n$ 了，简单证明：

假设一个节点 $u$，其儿子中 $n$ 所在子树为 $v$，那么如果想要离开再进入这个子树，一定会经过 $u$，$v$ 之一，即从 $v$ 跳跃到其它儿子，或者从子树内的一个点跳到 $u$ 再进入，所以进去出来后就回不去了。

所以对于一个点的所有儿子，我们一定先遍历其它子树并回来，**最后一个**进入 $n$ 所在的子树。

---

### $\text{3.寻找思路}$


和树相关的构造我们一般先考虑链，菊花图之类的特殊的树，我们先来观察一些较为特殊的树：

见下图：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/mu3skjog.png)

菊花图点两两可以连通，所以随便走即可。

链直接走好像就行？

但是 $n$ 不一定在链的另一端，所以可能需要跳过 $n$，走完下面再回来（如图）。

可以发现如果 $n$ 有一些儿子，那么我们必须要走到 $n$ 的父亲，并且其它点已经遍历了，然后下降到 $n$ 的儿子，遍历完后回到 $n$。


---

于是我们现在要处理的一个很关键的行为就是：“遍历某个点的整棵子树，并且回来”，具体地：是回到这个点的一个儿子，因为这样才能跳出这个子树。

于是我们定义操作 $\text {go(u)}$ 遍历 $u$ 的子树并回到 $u$ 的某个儿子的过程。

经过一些分析可以发现，当 $u$ 的 **非平凡儿子** 的个数大于一的时候，$\text {go(u)}$ **不可能实现**，简述：

考虑这样一棵树：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/apu8jhp5.png)

可以发现无论如何都不能实现上述操作，因为进入某个非平凡子树一定会经过它的顶点，而离开也必须要从同一个点离开，所以不行，类似地，这个非平凡儿子也一定只能有不超过一个非平凡儿子。

那么现在 $u$ 有且仅有一个 **非平凡儿子**，我们考虑如何构造。（没有非平凡儿子的情况是简单的）

下面给出我观察的另一个结构：（下图左侧）

![图3](https://cdn.luogu.com.cn/upload/image_hosting/icnelkoy.png)

因为有前面的限制，每个点最多有一个非平凡儿子，那么整个树的结构无非就是上图左下的那样，所以我们考虑递归地构造。

（其实大概就是讨论一下非平凡儿子和叶子的访问顺序。）

假设目前在点 $\text{go(u)}$，$u$ 的非平凡儿子是 $s$，$s$ 的非平凡儿子是 $t$（如上图），那么有如下遍历方式：

先下降到 $s$ 的平凡儿子（若没有则直接下降到 $t$），在其之间跳跃后跳到 $t$，递归执行 $\text{go(t)}$，此时在 $t$ 的一个儿子，则一定可以跳到 $s$，然后再在那些平凡的叶子之间跳跃即可，上面图中清晰地画出了路径。

这样构造原因是我们想要让 $s$ 是在回来时被访问，这样可以访问 $u$ 的其它平凡儿子，访问 $t$ 并递归后需要直接回到 $s$，所以我们直接遍历 $s$ 的非平凡儿子再去 $t$。

---

### $\text{4.回归原问题}$

现在重新回到原问题，加入我们目前在一个节点 $u$ 上，且 $n$ 在 $u$ 的子树 $t$ 中，遍历所有点并走到 $n$ 的过程，我们称之为 $\text{solve(u)}$。

那么类似上面 $\text{go(x)}$ 中的证明，我们可以发现，$u$ 除了 $t$ 之外，最多只能有一棵非平凡子树，否则是无法遍历并去到 $t$ 的，那么我们令这个非平凡儿子为 $s$（没有非平凡儿子的情况是简单的），同理，这个非平凡儿子只能有一个非平凡儿子（否则我们像上面说的那样无法遍历它），然后这个非平凡儿子是 $p$，如下图。

![图4](https://cdn.luogu.com.cn/upload/image_hosting/m2027w5w.png)

（无非就是讨论下叶子和非平凡儿子的遍历先后顺序）

构造方式（路径在上图中清晰地画出了）：

先下降到 $s$ 的一个平凡儿子并在其之间跳跃访问完，再访问 $s$ 的非平凡儿子 $p$（若没有则直接访问平凡儿子后返回），并对其执行 $\text{go(p)}$，结束后在 $p$ 的某个儿子（若没有则直接返回），可以跳到 $s$，然后再跳到 $u$ 的其它平凡儿子并在之间跳跃，最后访问 $t$，递归执行 $\text{solve(t)}$。

---

### $\text{5.特殊情况}$

（观察样例发现）


当一个点 $u$ 有且仅有一个儿子 $t$，且终点在里面的情况，我们不一定非要访问 $t$，之所以前面我们需要访问 $t$，是因为其它儿子无法跳到 $t$ 的子树里，而且 $t$ 必须要被最后访问，所以就只能跳跃到 $t$ 了。

点 $u$ 有且仅有儿子 $t$ 的时候，可以直接跳到 $t$ 的某个子树后再回到 $t$，并执行 $\text{solve(t)}$ 的操作，举例如图：

![图5](https://cdn.luogu.com.cn/upload/image_hosting/f2jjb17s.png)

$t$ 本身有两个除 $n$ 所在子树外的非平凡子树，如果直接 $\text{solve(t)}$ 是无解的，但是如果我在 $u$ 位置的就直接下降到 $t$ 的某个非平凡儿子，再回到 $t$，就能构造出一条合法的路径。

其实这个操作的本质就是“如果目前这个点有且仅有终点所在子树这一个儿子，我可以提前处理掉这个儿子的（除终点所在子树之外的） **一个非平凡儿子** 和 **所有平凡儿子**”，这样可能使得本身有 $2$ 个（除终点所在子树之外的）非平凡儿子的子树变得只有一个非平凡儿子，可以继续。 当然也可以使得一个只有一个非平凡儿子的点变得只有终点所在子树这一个儿子，可以继续传递下去这个性质。

可以发现少一个非平凡子树和一些平凡子树一定是不劣的，所以直接提前处理掉对应子树，并打好标记删除掉就行了。

---

### $\text{6.代码实现}$

以下是所用到两个构造的 简述：

$\text{go(u)}$

&#8195;若 $u$ 有不少于两个非平凡儿子则非法。

&#8195;若 $u$ 没有非平凡儿子则直接遍历。

&#8195;若 $u$ 有一个非平凡儿子 $s$，则先下降到 $s$ 的平凡儿子（若没有则直接下降   到 $t$），在其之间跳跃后跳到 $t$，递归执行 $\text{go(t)}$。

回到 $s$，在那些 $u$ 平凡的叶子之间跳跃。


$\text{solve(u)}$ 

如果 $u$ 有目前剩余的唯一儿子 $t$。

&#8195; $t=n$，跳到儿子并遍历，若有超过一个非平凡儿子则非法。

&#8195; $t\neq n$，那么处理掉 $t$ 的一个非平凡儿子 $p$，执行 $\text{go(p)}$ 后执行 $\text{solve(t)}$（如果没有则直接执行）。

$u$ 有别的非平凡儿子 $s$，执行上面 $\text{4}$ 中提到的

先下降到 $s$ 的一个平凡儿子并在其之间跳跃访问完，再访问 $s$ 的非平凡儿子 $p$（若没有则直接访问平凡儿子后返回），并对其执行 $\text{go(p)}$，结束后在 $p$ 的某个儿子（若没有则直接返回），可以跳到 $s$，然后再跳到 $u$ 的其它平凡儿子并在之间跳跃，最后访问 $t$，递归执行 $\text{solve(t)}$。


如果 $n$ 有其它没有被消去的兄弟导致它只能被从兄弟跳跃过来，那么如果它有儿子就无法被访问了，无解。

---

贴坨[屎](https://www.luogu.com.cn/paste/uz0lom7o)在这里。感觉没什么参考价值。

















---

## 作者：crashed (赞：2)

# 题目

[点这里](https://www.luogu.com.cn/problem/P3549)看题目。

给定一棵包含 $n$ 个结点的树。

构造一个 $1\sim n$ 的排列 $p_1,p_2,\dots,p_n$，满足：

1. $p_1=1,p_n=n$。

2. 对于任意的 $1\le k<n$，$p_k$ 和 $p_{k+1}$ 之间的**距离不超过 $2$**。

如果不存在，输出 `BRAK`。如果存在，输出任意一组解。

所有数据满足 $2\le n\le 5\times 10^5$。

# 分析

首先可以手玩一下“树形为链，且 $1$ 为一端”——过程和结果都比较简单。从 $1$ 一路走到 $n$ 的父亲，之后的交错跳即可。

可以感知到，“距离”限制还是比较紧的。拿这样的经验，分析一下**一般树上的起手策略**。设 $v$ 为 $n$ 所在子树，那么：

1. 如果 $v$ 是唯一的儿子，那么可以直接**跳到 $v$ 子树**。

2. 如果除了 $v$ 以外其它儿子都是叶子，那么可以先跳叶子，最后**跳到 $v$ 结点**。

3. 否则，可以发现 $v$ 以外最多只能有一个儿子不是叶子，我们记那个儿子为 $w$。可以发现，最终我们必须回到 $w$，那么这个过程类似于**链上行走**，于是可以构造：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/y7fo5vhm.png)

   也就是，先跳到 $w$ 的一个儿子，经过 $w$ 子树之后到达 $w$，然后从 $w$ **跳到 $v$ 结点**。

这些考虑起来都比较简单，但一定要分清楚：**情况 1 和情况 2，3 是本质不同的**。前者是从 $v$ 的父亲出发（第一类），而后者是从 $v$ 出发（第二类）。第二类可以遍历完的情况时第一类的**真子集**。从 $1$ 出发就属于第二类，因此我们已经分析完了第二类的走法了。

----------

在此之前，我们先来解决 $w$ 的问题（第三类）。考虑一个类似于第二类的情况：我们需要从 $s$ 出发，遍历完 $s$ 子树后**回到 $s$ 的一个儿子上**。那么：

1. 如果 $s$ 的所有儿子都是叶子，略。

2. 如果 $s$ 有儿子不是叶子，则这样的儿子**至多只有一个**，有多个就无法回到 $s$ 的儿子之中了。

   设非叶子儿子为 $w$，构造策略基本同第二类 3.：先走到 $w$ 的一个儿子，遍历完之后回到 $w$，然后从 $w$ 开始遍历完所有叶子。

为了 2. 我们需要再构造一个“第四类”问题吗？显然过于复杂。我们注意到**路径具有天然的对称性**。也就是说，如果我们将第三类输出的路径反过来，恰好就是“从 $s$ 的一个儿子出发，遍历完子树后回到 $s$ 的路径”！只需要快速地处理“反序”即可，后面再来讨论。

----------

相应地，第二类 3. 也可以直接用第三类问题的解法解决，于是我们额外讨论一下第一类。

贪心地想，从 $s$ 出发，如果 $n$ 在 $v$ 的子树内，我们就应该**尽量让 $v$ 也可以面对“第一类”的情况**。此外，结合样例我们可以得到一点提示。设 $c$ 为“非叶子儿子或包含 $n$ 的儿子总个数”，则有：

1. 如果 $c=1$，则先遍历叶子儿子，而后经过 $s$，最后进入 $v$ 的子树，变成第一类子问题。

2. 如果 $c=2$，设另外的非叶子儿子为 $w$，则：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/0ko1dunn.png)

   应当先遍历叶子，再到达 $w$，遍历完其子树后到达 $w$ 的一个儿子，而后到达 $s$，最后进入 $v$ 的子树，变成第一类子问题。

3. 如果 $c=3$，设另外两个非叶子儿子为 $w,x$，则：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/dy9mxmo6.png)

   应当先遍历叶子，再到达 $x$，遍历完其子树后到达 $x$ 的一个儿子，而后到达 $s$，再到达 $w$ 的一个儿子，遍历完 $w$ 后到达 $w$，最后到达 $v$ 结点，变成第二类子问题。

----------

最后需要处理一下“倒序”的问题。

在代码实现中，事实上将“倒序”**单独写成一个函数**可以得到更简单的逻辑。不过，由于子树大小确定，所以我们可以提前知道某个子树最终会占据的区间。而方向也可以在进入子树前得知，因此另一种方法就是**改变填写位置和方向模拟倒序**。两种都可以线性处理。

最终我们可以 $O(n)$ 得到结果。

# 代码

```cpp
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

const int MAXN = 5e5 + 5;

template<typename _T>
inline void Read( _T &x ) {
    x = 0; char s = getchar(); bool f = false;
    while( s < '0' || '9' < s ) { f = s == '-', s = getchar(); }
    while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
    if( f ) x = -x;
}

template<typename _T>
inline void Write( _T x ) {
    if( x < 0 ) putchar( '-' ), x = -x;
    if( 9 < x ) Write( x / 10 );
    putchar( x % 10 + '0' );
}

struct Edge {
    int to, nxt;
} Graph[MAXN << 1];

std :: vector<int> son[MAXN];

int ans[MAXN], tot;
int siz[MAXN]; bool imp[MAXN];

int head[MAXN], cnt = 1;

int N;

#define Dead {\
    puts( "BRAK" );\
    exit( 0 );\
}

inline void AddEdge( const int &from, const int &to ) {
    Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
    head[from] = cnt;
}

void Init( const int &u, const int &fa ) {
    siz[u] = 1, imp[u] = u == N;
    for( int i = head[u], v ; i ; i = Graph[i].nxt )
        if( ( v = Graph[i].to ) ^ fa ) {
            Init( v, u );
            siz[u] += siz[v];
            imp[u] |= imp[v];
            son[u].push_back( v );
        }
    std :: sort( son[u].begin(), son[u].end(),
        [] ( const int &a, const int &b ) -> bool {
            if( imp[b] ) return true;
            if( imp[a] ) return false;
            return siz[a] < siz[b];
        } );
}

void DFS2( const int &u, const int &fa, int cur, const int &dir ) {
    // 根本不需要关心到 u 的距离！
    // 如果最开始就是从 u 出发的，那么最后必须到 u 的一个儿子
    // 把整个路径反过来就可以得到从一个儿子出发的路径！

    ans[cur += dir] = u;
    int n = son[u].size(), sml = 0, lrg; 
    rep( i, 0, n - 1 )
        sml += siz[son[u][i]] == 1;
    lrg = n - sml;
    if( lrg >= 2 ) Dead
    if( lrg ) {
        DFS2( son[u][n - 1], u, cur + dir * ( siz[son[u][n - 1]] + 1 ), - dir );
        cur += dir * siz[son[u][n - 1]];
    }
    rep( i, 0, sml - 1 ) ans[cur += dir] = son[u][i];
}

void DFS1( const int &u, const int &fa, const int &d, int cur, const int dir ) {
    // d = 0: 从 u 出发
    // d = 1: 从 u 的父亲出发
    // 注意这里的目标是到达 N，而不是回到 u 附近，所以需要记录 d

    int n = son[u].size(), sml = 0, lrg;
    rep( i, 0, n - 1 )
        sml += siz[son[u][i]] == 1 && ! imp[son[u][i]];
    lrg = n - sml;
    if( u == N ) {
        if( d == 0 && siz[u] > 1 ) Dead
        DFS2( u, fa, cur + dir * ( siz[u] + 1 ), - dir );
    } else if( d == 1 ) {
        if( lrg > 3 ) Dead
        rep( i, 0, sml - 1 ) 
            ans[cur += dir] = son[u][i];
        if( lrg == 3 ) {
            DFS2( son[u][n - 3], u, cur, dir );
            cur += dir * siz[son[u][n - 3]], ans[cur += dir] = u;
            DFS2( son[u][n - 2], u, cur + dir * ( siz[son[u][n - 2]] + 1 ), - dir );
            cur += dir * siz[son[u][n - 2]];
            DFS1( son[u][n - 1], u, 0, cur, dir );
        } else {
            if( lrg == 2 ) {
                DFS2( son[u][n - 2], u, cur, dir );
                cur += dir * siz[son[u][n - 2]];
            }
            ans[cur += dir] = u;
            DFS1( son[u][n - 1], u, 1, cur, dir );
        }
    } else {
        if( lrg > 2 ) Dead
        ans[cur += dir] = u;
        if( lrg == 2 ) {
            DFS2( son[u][n - 2], u, cur + dir * ( siz[son[u][n - 2]] + 1 ), - dir );
            cur += dir * siz[son[u][n - 2]];
        }
        rep( i, 0, sml - 1 ) ans[cur += dir] = son[u][i];
        DFS1( son[u][n - 1], u, n == 1, cur, dir );
    }
}

int main() {
    Read( N );
    rep( i, 1, N - 1 ) {
        int u, v; Read( u ), Read( v );
        AddEdge( u, v ), AddEdge( v, u );
    }
    Init( 1, 0 );
    DFS1( 1, 0, 0, 0, 1 );
    rep( i, 1, N ) 
        Write( ans[i] ), putchar( '\n' );
    return 0;
}
```

---

## 作者：OtoriEmu (赞：1)

难度全在实现啊！

首先把 $1 \to n$ 这条链抽出来，形成一个层式的结构。

然后每层构造就好了，采用 Sudden Death 判断是否无解。

从一层跳到下一层的方法有从当前层的儿子跳到下一层，当前层跳到下一层，当前层跳到下一层的儿子。需要实现两个构造函数 $F(u)$ 表示对于以 $u$ 为根的子树，以 $u$ 的儿子为起点，$u$ 为终点遍历掉整棵子树；$G(u)$ 表示对于以 $u$ 为根的子树，以 $u$ 为起点，$u$ 的儿子为终点遍历掉整棵子树。两者需要互相调用。

具体的讲解放在代码注释。因为这题难度全在判断，不结合代码很麻烦，所以原谅一下啦！

同时给上[完整代码](https://www.luogu.com.cn/paste/lwwmzh2b)。

```cpp
int n,fa[500005],siz[500005];
bool vis[500005];
vector<int> Ans,G[500005];
void initdfs(int u,int f)
{
	fa[u]=f,siz[u]=1;
	for(auto v:G[u])	if(v^f)	initdfs(v,u),siz[u]+=siz[v];
}
inline void brak(int id=0){puts("BRAK");exit(id=0);}
void pF(int,int);
void pG(int,int);
void pF(int u,int f) // 从 u 的儿子跳起，然后留在 u
{
	vector<int> Pans;
	int pson=0; // 这两个东西的定义参见 dfs(int,int,bool)
	for(auto v:G[u])
	{
		if(v==f)	continue;
		if(siz[v]==1)	Pans.push_back(v);
		else	++pson;
	}
	if(pson>1)	brak(1); // 跳完一个子树会占用 u，这样就上不来了
	for(auto p:Pans)	Ans.push_back(p); // 从大小为 1 的子树跳起
	for(auto v:G[u])	if(v!=f && siz[v]!=1)	pG(v,u); // 然后以儿子为起点，儿子的儿子为终点，最后跳到 u
	Ans.push_back(u); // 跳到 u
}
void pG(int u,int f) // 从 u 跳起，然后留在 u 的儿子
{
	Ans.push_back(u); // 从 u 跳起
	vector<int> Pans;
	int pson=0; // 这两个东西的定义参见 dfs(int,int,bool)
	for(auto v:G[u])
	{
		if(v==f)	continue;
		if(siz[v]==1)	Pans.push_back(v);
		else	++pson;
	}
	if(pson>1)	brak(2); // 跳完两个子树会占用 u 的另一个儿子，这样就上不来了
	for(auto v:G[u])	if(v!=f && siz[v]!=1)	pF(v,u); // 以 u 儿子的儿子为起点，u 的儿子为终点，最后留下来
	for(auto p:Pans)	Ans.push_back(p); // 当然要处理掉大小为 1 的子树，注意这里的处理顺序和 pG(int,int) 不一样
}
void dfs(int u,int f,bool cris) // 当前点，父亲点，是否在 u 上（cris=true 时在 u 上，否则在 f 上）
{
	assert(vis[u]);
	if(u==n) // 特判已经到终点
	{
		if(siz[u]==1) // 如果说 u 没有儿子，那就很好，直接走掉
		{
			Ans.push_back(u);
			return ;
		}
		if(cris)	brak(3); // 否则我们已经在 u 上了，很不好，就去世了
		pF(u,f); // 然后以 u 的儿子为起点，u 为终点构造
		return ;
	}
	if(cris)	Ans.push_back(u); // 一开始就在 u 上
	vector<int> Pans; // 大小为 1 的子树
	int pson=0; // 大小不为 1 的子树的个数
	for(auto v:G[u])
	{
		if(v==f)	continue;
		if(vis[v])	continue;
		if(siz[v]==1)	Pans.push_back(v);
		else	++pson;
	}
	bool ncir=true; // 下一层是留在下一层的父亲结点 (u) 还是下一层的结点
	if(cris) // 如果在 u 上——
	{
		if(pson>1)	brak(4); // 并且有大于一个大小不为 1 的子树，应该去世，可以画图理解
		if(pson==0 && Pans.empty())	ncir=false; // 并且没有儿子，处理下一层的时候停留在 u
		else
		{
			for(auto v:G[u])
			{
				if(v==f)	continue;
				if(vis[v] || siz[v]==1)	continue;
				pF(v,u); // 以 v 的儿子为起点，v 为终点构造子树
			}
		}
		for(auto p:Pans)	Ans.push_back(p); // 最后处理掉大小为 1 的子树，然后跟着从这个点直接跳到下一层的点
	}
	else // 否则在 f 上——
	{
		if(pson>2)	brak(5); // 并且有超过两个大小不为 1 的子树，应该去世，画图吧
		else if(pson==0) // 并且没有大小不为 1 的子树
		{
			for(auto p:Pans)	Ans.push_back(p); // 处理掉大小为 1 的子树
			Ans.push_back(u); // 然后跳到 u
			ncir=false; // 下一层留在 u
		}
		else if(pson==1) // 并且有一个大小不为 1 的子树
		{
			for(auto p:Pans)	Ans.push_back(p); // 先处理掉大小为 1 的子树
			for(auto v:G[u])
			{
				if(v==f)	continue;
				if(vis[v] || siz[v]==1)	continue;
				pG(v,u); // 然后以 v 为起点，v 的儿子为终点
			}
			Ans.push_back(u); // 跳到 u 结束
			ncir=false; // 下一层留在 u
		}
		else // 并且有两个大小不为 1 的子树
		{
			bool c=false; // 可以证明的是我们在处理两个子树的过程中一定会跳到 u，不然无法完成构造，下一层也自然不会留在 u
			for(auto v:G[u])
			{
				if(v==f)	continue;
				if(vis[v] || siz[v]==1)	continue;
				if(c)	Ans.push_back(u); // 见下
				if(!c)	pG(v,u); // 先处理第一棵子树，此时是从 f 跳到 v，以 v 为起点构造，停留在 v 的一个儿子，最后跳到 u
				else	pF(v,u); // 然后从 u 跳到另一个 v 的儿子，最后在 v 结束，然后跳到下一层的点
				c=true;
			}
			for(auto p:Pans)	Ans.push_back(p); // 注意在跳到下一层之前要处理掉大小为 1 的子树
		}
	}
	for(auto v:G[u])	if(vis[v] && v!=f)	dfs(v,u,ncir); // 处理下一层吧
}
int main(){
	n=read();
	if(n==1)	return puts("1")&0;
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	initdfs(1,0);
	{
	int p=n;
	while(p)	vis[p]=true,p=fa[p];
	} // 抽出 1 -> n 这条链，打上标记
	dfs(1,0,true); // 构造
	for(auto p:Ans)	write(p),puts("");
	return 0;
}
```

---

## 作者：Leasier (赞：1)

考虑抓出 $1 \sim n$ 的路径，我们将所求路径分成两部分：

- 不在路径上的子树：我们需要遍历一遍后离开。
- 在路径上的子树：我们需要依次走完路径两边的子树，再依次向下最终走到 $n$ 子树。

考虑 dp。设 $f_{u, i}$ 表示是否可以遍历完 $u$ 子树后离开，其中 $i = 0$ 表示进入时位于 $u$，$i = 1$ 表示进入时位于 $u$ 的一个儿子。

初值：对于所有叶子 $u$，有 $f_{u, 0} = \operatorname{true}$。

转移需要进行一些讨论。下面设非叶子儿子个数为 $size$。手画一下可以发现 $size > 1$ 时都是 $\operatorname{false}$。

1. $size = 0$

此时我们只需要跳着遍历所有叶子，则 $f_{u, 0} = f_{u, 1} = \operatorname{true}$。

2. $size = 1$

设唯一的非叶子儿子为 $v$。

对于 $f_{u, 0}$，我们有两种选择：

- 跳到 $v$ 的一个儿子并遍历 $v$ 子树，最后遍历所有叶子即可。此时的条件为 $f_{v, 1}$。
- 先遍历所有叶子，然后跳到 $v$ 并遍历其子树。此时的条件为 $f_{v, 0} \operatorname{and} [cnt_{leaf} > 0]$。

对于 $f_{u, 1}$，我们只有一种选择：

- 跳到 $v$ 并遍历 $v$ 子树，然后回到 $u$ 并遍历所有叶子儿子。

类似地，设 $g_{u, i}$ 表示是否可以遍历完 $u$ 子树并进入 $1 \to n$ 路径上的下一个点 $nxt_i$，其中 $i = 0$ 表示进入时位于 $u$，$i = 1$ 表示进入时位于 $u$ 的一个儿子。

初值：$g_{n, 0} = [n \text{ is a leaf}]$，$g_{n, 1} = f_{n, 1}$。

转移还需要进行一些讨论。下面设非叶子儿子个数为 $size$。手画一下可以发现 $size > 2$ 时都是 $\operatorname{false}$——这里与 $f$ 不同的原因是有一个子树你必须不回来。

注意下面的 $cnt_{leaf}$ 不包括 $nxt_u$——当然也只有可能是 $n$。

1. $size = 0$

对于 $g_{u, 0}$，我们有两种选择：

- 先遍历所有叶子，然后跳到 $nxt_u$ 并接下去遍历。此时的条件为 $g_{nxt_u, 0}$。
- 直接跳到 $nxt_u$ 的一个儿子并继续遍历。此时的条件为 $g_{nxt_u, 1} \operatorname{and} [cnt_{leaf} = 0]$。

对于 $g_{u, 1}$，我们有两种选择：

- 先遍历所有叶子，然后跳回 $u$，再跳到 $nxt_u$ 并接下去遍历。此时的条件为 $g_{nxt_u, 0}$。
- 先遍历所有叶子，然后跳回 $u$，再跳到 $nxt_u$ 的一个儿子并接下去遍历。此时的条件为 $g_{nxt_u, 1} \operatorname{and} [cnt_{leaf} > 0]$。

2. $size = 1$

设唯一的非叶子儿子为 $v$。

对于 $g_{u, 0}$，我们只有一种选择：

- 先遍历 $v$，然后跳回 $u$ 并遍历所有叶子，然后跳到 $nxt_u$ 并接下去遍历。此时的条件为 $g_{nxt_u, 0} \operatorname{and} f_{v, 1}$。

对于 $g_{u, 1}$，我们有四种选择：

- 先遍历所有叶子，然后遍历 $v$，接下来跳到 $n$，最后跳到 $nxt_u$ 并接下去遍历。此时的条件为 $g_{nxt_u, 0} \operatorname{and} f_{v, 0}$。
- 然后跳到 $v$ 的一个儿子来遍历 $v$，接下来经过至少一个叶子来跳到 $n$，最后跳到 $nxt_u$ 并接下去遍历。此时的条件为 $g_{nxt_u, 0} \operatorname{and} f_{v, 1} \operatorname{and} [cnt_{leaf} > 0]$。
- 先遍历所有叶子，然后遍历 $v$，接下来跳到 $n$，最后跳到 $nxt_u$ 的一个儿子并接下去遍历。此时的条件为 $g_{nxt_u, 1} \operatorname{and} f_{v, 0}$。
- 然后跳到 $v$ 的一个儿子来遍历 $v$，接下来经过至少一个叶子来跳到 $n$，最后跳到 $nxt_u$ 的一个儿子并接下去遍历。此时的条件为 $g_{nxt_u, 1} \operatorname{and} f_{v, 1} \operatorname{and} [cnt_{leaf} > 0]$。

3. $size = 2$

设两个非叶子儿子为 $v_1, v_2$。

此时 $g_{u, 0}$ 一定不行，考虑 $g_{u, 1}$。

对于 $g_{u, 1}$，我们有两种选择：

- 首先遍历所有叶子，然后跳到 $v_1$，接下来跳回 $u$，再跳到 $v_2$ 的某个儿子，最后跳到 $nxt_u$ 并接下去遍历。此时的条件为 $g_{nxt_u, 0} \operatorname{and} f_{v_1, 0} \operatorname{and} f_{v_2, 1}$。
- 在上一种选择的基础上 $\operatorname{swap}(v_1, v_2)$。

dp 后先拿 $g_{1, 0}$ 判断是否有解，然后模拟上述转移意义输出方案即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <vector>
#include <cstdio>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int head[2000007], fa[2000007], son_cnt[2000007], nxt[2000007], ans[2000007];
bool dp1[2000007][7], dp2[2000007][7];
Edge edge[4000007];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father){
	fa[u] = father;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			son_cnt[u]++;
			dfs1(x, u);
		}
	}
}

void dfs2(int u){
	if (son_cnt[u] == 0){
		dp1[u][0] = true;
		return;
	}
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u]) dfs2(x);
	}
	int size;
	vector<int> son;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u] && son_cnt[x] != 0) son.push_back(x);
	}
	size = son.size();
	if (size == 0){
		dp1[u][0] = dp1[u][1] = true;
	} else if (size == 1){
		dp1[u][0] = dp1[son[0]][1] || (dp1[son[0]][0] && son_cnt[u] > 1);
		dp1[u][1] = dp1[son[0]][0];
	}
}

void dfs3(int u){
	if (nxt[u] == 0){
		if (son_cnt[u] == 0){
			dp2[u][0] = true;
		} else {
			dp2[u][1] = dp1[u][1];
		}
		return;
	}
	int size;
	vector<int> son;
	dfs3(nxt[u]);
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u] && x != nxt[u] && son_cnt[x] != 0) son.push_back(x);
	}
	size = son.size();
	if (size == 0){
		dp2[u][0] = dp2[nxt[u]][0] || (dp2[nxt[u]][1] && son_cnt[u] == 1);
		dp2[u][1] = dp2[nxt[u]][0] || (dp2[nxt[u]][1] && son_cnt[u] > 1);
	} else if (size == 1){
		dp2[u][0] = dp2[nxt[u]][0] && dp1[son[0]][1];
		dp2[u][1] = (dp2[nxt[u]][0] || dp2[nxt[u]][1]) && (dp1[son[0]][0] || (dp1[son[0]][1] && son_cnt[u] > 2));
	} else if (size == 2){
		dp2[u][1] = dp2[nxt[u]][0] && ((dp1[son[0]][0] && dp1[son[1]][1]) || (dp1[son[0]][1] && dp1[son[1]][0]));
	}
}

void write(int n){
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

inline void leaf1(int u){
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u] && son_cnt[x] == 0){
			write(x);
			putchar('\n');
		}
	}
}

void dfs4(int u, int op){
	int size;
	vector<int> son;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u] && son_cnt[x] != 0) son.push_back(x);
	}
	size = son.size();
	if (op == 0){
		write(u);
		putchar('\n');
		if (size == 0){
			leaf1(u);
		} else if (dp1[son[0]][1]){
			dfs4(son[0], 1);
			leaf1(u);
		} else {
			leaf1(u);
			dfs4(son[0], 0);
		}
	} else {
		leaf1(u);
		if (size > 0) dfs4(son[0], 0);
		write(u);
		putchar('\n');
	}
}

inline void leaf2(int u){
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u] && x != nxt[u] && son_cnt[x] == 0){
			write(x);
			putchar('\n');
		}
	}
}

void dfs5(int u, int op){
	if (nxt[u] == 0){
		if (op == 0){
			write(u);
			putchar('\n');
		} else {
			dfs4(u, 1);
		}
		return;
	}
	int size;
	vector<int> son;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != fa[u] && x != nxt[u] && son_cnt[x] != 0) son.push_back(x);
	}
	size = son.size();
	if (op == 0){
		write(u);
		putchar('\n');
		if (size == 0){
			if (dp2[nxt[u]][0]){
				leaf2(u);
				dfs5(nxt[u], 0);
			} else {
				dfs5(nxt[u], 1);
			}
		} else {
			dfs4(son[0], 1);
			leaf2(u);
			dfs5(nxt[u], 0);
		}
	} else {
		if (size == 0){
			leaf2(u);
			write(u);
			putchar('\n');
			if (dp2[nxt[u]][0]){
				dfs5(nxt[u], 0);
			} else {
				dfs5(nxt[u], 1);
			}
		} else if (size == 1){
			leaf2(u);
			if (dp1[son[0]][0]){
				dfs4(son[0], 0);
				write(u);
				putchar('\n');
			} else {
				write(u);
				putchar('\n');
				dfs4(son[0], 1);
			}
			if (dp2[nxt[u]][0]){
				dfs5(nxt[u], 0);
			} else {
				dfs5(nxt[u], 1);
			}
		} else {
			leaf2(u);
			if (dp1[son[0]][0] && dp1[son[1]][1]){
				dfs4(son[0], 0);
				write(u);
				putchar('\n');
				dfs4(son[1], 1);
			} else {
				dfs4(son[1], 0);
				write(u);
				putchar('\n');
				dfs4(son[0], 1);
			}
			dfs5(nxt[u], 0);
		}
	}
}

int main(){
	int n = read();
	for (int i = 1; i < n; i++){
		int u = read(), v = read();
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs1(1, 0);
	for (int i = n; i != 1; i = fa[i]){
		nxt[fa[i]] = i;
	}
	dfs2(1);
	dfs3(1);
	if (!dp2[1][0]){
		printf("BRAK");
	} else {
		dfs5(1, 0);
	}
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

一种思维要求不高的超级池沼做法。

首先，显然不存在一条路径，跳进一棵子树 $u$ 再跳出之后，再跳进子树 $u$。

对于这种问题，一种笨笨的思考方式是从一种基本情况出发，bfs 式地找到其它需要处理的情况并解决之。

我们下文令“满足情况 $x$”指代“存在满足情况 $x$ 要求的路径”。

设我们现在要求考虑点 $u$，分以下几种情况：

### 情况 $1:$ 要求一条路径从 $u$ 开始，遍历整棵子树之后在 $n$ 号节点停下。（钦定 $n$ 一定在 $u$ 子树内）

首先如果 $u$ 是 $n$ 号节点本身的话，除非其没有儿子，否则一定无解。

排除掉这种情况后，我们可以发现 $u$ 一定在某个儿子 $s$ 的子树内。因此路径要求在遍历完其它子树之后，一次性遍历完 $s$。

此时 $u$ 下一步的儿子 $v$ 要么是一个可以从儿子（$u$ 孙子）出发，遍历完整棵子树后回到 $v$ 的点（$2$ 情况），此时接下来的路径是沿着若干个叶子结点跳到 $s$，要么直接从叶子结点开始跳。然后要求从 $s$ 开始，遍历整棵子树之后在 $n$ 号节点停止（$1$ 情况）。

除此之外，如果 $u$ 的儿子只有 $s$，则下一步也可以直接跳到 $s$ 的其中一个儿子，此时要求 $s$ 为一个存在一条从 $s$ 的其中一个儿子开始的路径，遍历完 $s$ 的整棵子树之后在 $n$ 结束。（$4$ 情况）

### 情况 $2:$ 要求一条路径从 $u$ 的其中一个儿子出发，遍历完整个子树后由 $u$ 结束。

相对简单的一种。由于能够返回 $u$ 的上一个节点要么是儿子，要么是孙子。而 $u$ 的一个儿子 $v$ 能够从自己开始，遍历完子树后切换到另外一个儿子当且仅当 $v$ 为叶子。于是发现合法路径必然是以下形式：

若干个叶子节点 $\rightarrow$ 一个存在一条路径，使得从 $p$ 出发，能够遍历完所有子树，并结束于 $p$ 的一个儿子 $q$ 的儿子 $p$（情况 $3$） $\rightarrow$ $u$。（前两部分可以去掉一个。）

### 情况 $3:$ 要求一条路径从 $u$ 出发，遍历完整个子树后由 $u$ 的其中一个儿子 $v$ 结束。

与上一个一样简单。由于 $u$ 的下一个节点要么是儿子，要么是孙子。而对于一个儿子 $v$，如果以其父亲作为遍历路径的前驱，则其能够在遍历完子树后能够切换到其兄弟，要么满足情况 $2$（$v$ 子树内遍历到的第一个节点为 $v$ 的儿子），要么是叶子（第一个节点为 $v$）。于是发现合法路径必然是以下形式：

一个满足情况 $2$ 的儿子 $\rightarrow$ 一堆叶儿子 $\rightarrow$ 根。

### 情况 $4:$ 要求一条路径从 $u$ 的其中一个儿子 $v$ 出发，遍历完 $u$ 的整个子树之后于 $n$ 结束。

最麻烦的一种。

我们先判掉两类情况：

$1.u=n$

此时问题转化为了情况 $2$。

$2.v$ 为 $u$ 唯一的儿子。

首先如果 $v=n$ 无解。

此时有两种方案：

要么 $v$ 走到 $u$，然后走到 $v$ 的其中一个儿子。此时要求 $v$ 满足存在一条路径，满足从 $v$ 的其中一个儿子出发，遍历 $v$ 子树内除了 $v$ 之外的所有节点，并且在 $n$ 结束。（情况 $5$）

要么 $v$ 先走到它的一个孙子（第一步走到儿子的方案可以转化为第一种方案，此时不劣），然后遍历完子树内除了 $v$ 之外的所有节点并于 $n$ 结束，并且要求其中有 $v$ 儿子之间的跳跃（把 $x$ 跳跃到 $y$ 转化成 $x$ 先跳跃到 $u$，然后 $u$ 跳到 $y$）。（情况 $6$）

现在两类情况判掉了。显然我们的目的地 $s$ 为子树内包含 $n$ 的唯一儿子。我们现在有两种方案可供选择：

要么经过若干个叶子节点之后，走到一个满足情况 $3$ 的一个儿子，经由它跳到根，然后跳到 $s$ 的儿子节点并完成接下来的路程。（要求 $s$ 满足情况 $4$）（前两者可以缺一个）。

要么由一个满足情况 $3$ 的儿子出发，走到根，然后走到一个满足情况 $2$ 的儿子，然后经过若干个叶子后直接走到 $s$。此时要求 $s$ 满足情况 $1$。（前三者可以缺 $1$ 至 $2$ 个）。

### 情况 $5:$ 要求 $u$ 满足存在一条路径，满足从 $u$ 的其中一个儿子出发，遍历 $u$ 子树内除了 $u$ 之外的所有节点，并且在 $n$ 结束。

首先如果 $u=n$ 铁定无解。

设子树内有 $n$ 的那个 $u$ 的儿子为 $s$，则合法路径一定为经过一堆叶儿子（可以没有）之后来到 $s$ ，完成接下来的路程。此时要求 $s$ 满足情况 $1$。

### 情况 $6:$ 要求 $u$ 满足存在一条路径，满足从 $u$ 的其中一个孙子出发，遍历 $u$ 子树内除了 $u$ 之外的所有节点，并且在 $n$ 结束。并且至少有一次 $u$ 的儿子之间的跳跃。

首先如果 $u$ 的儿子数量 $\le 1$ 无解。

显然你得先从 $u$ 的孙子回到其对应的 $u$ 的儿子。因此起始节点必须满足情况 $2$。

与上一种情况类似，中途的节点一定是一堆叶子（可以没有）。

目的地 $s$ 也需要满足情况 $1$。


```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=5e5;

vector<int> nxt[maxn+5];
int rootn[maxn+5];//情况1
int sonfa[maxn+5];//情况2
int fason[maxn+5];//情况3
int sonbegn[maxn+5];//情况4
int sononlyn[maxn+5];//情况5
int haven[maxn+5];//n 在不在子树内
int fa[maxn+5];
int isleaf[maxn+5];//是否为叶子节点
int gsonbegn[maxn+5];//情况6
int n;

bool Rootn(int now);
bool Sonfa(int now);
bool Fason(int now);
bool Sonbegn(int now);
bool Sononlyn(int now);
bool Gsonbegn(int now);
//六种情况的合法性判断
void ROOTN(int now);
void SONFA(int now);
void FASON(int now);
void SONBEGN(int now);
void SONONLYN(int now);
void GSONBEGN(int now);
//六种情况的方案构造

void dfs(int now){
	int cnt=0;
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		cnt++;
		fa[i]=now;
		dfs(i);
	}
	if(cnt){
		isleaf[now]=0;
	}
	else{
		isleaf[now]=1;
	}
}

bool Rootn(int now){
	int sonrtsum=0,gu=0,endson=0;
	if(rootn[now]!=-1){
		goto label;
	}
	rootn[now]=0;
	if(now==n){
		if(isleaf[now]){
			rootn[now]=1;
		}
		else{
			rootn[now]=0;
		}
		goto label;
	}
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		if(haven[i]){
			endson=i;
			continue;
		}
		if(isleaf[i]){
			gu++;
			continue;
		}
		if(Sonfa(i)){
			sonrtsum++;
			if(sonrtsum>=2){
				//cout<<"GRETER 2\n";
				goto label;
			}
		}
		else//cout<<"OTHER\n";
			goto label;
	}
	if(Rootn(endson)||((gu+sonrtsum==0&&Sonbegn(endson)))){
		rootn[now]=1;
	}
	label:
	return rootn[now];
}

bool Sonfa(int now){
	int fason=0;
	if(sonfa[now]!=-1){
		goto label;
	}
	sonfa[now]=0;
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		else if(isleaf[i]){
			continue;
		}
		else if(Fason(i)){
			fason++;
			if(fason==2){
				goto label;
			}
		}
		else{
			goto label;
		}
	}
	sonfa[now]=1;
	label:
	return sonfa[now];
}

bool Fason(int now){
	int sonfa=0;
	if(fason[now]!=-1){
		goto label;
	}
	fason[now]=0;
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		else if(isleaf[i]){
			continue;
		}
		else if(Sonfa(i)){
			sonfa++;
			if(sonfa==2){
				goto label;
			}
		}
		else{
			goto label;
		}
	}
	fason[now]=1;
	label:
	return fason[now];
}


bool Sononlyn(int now){
	if(sononlyn[now]!=-1){
		goto label;
	}
	sononlyn[now]=0;
	if(now==n){
		goto label;
	}
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		else if(haven[i]){
			if(!Rootn(i)){
				goto label;
			}
		}
		else if(isleaf[i]){
			continue;
		}
		else{
			goto label;
		}
	}
	sononlyn[now]=1;
	label:
	return sononlyn[now];
}
//#define debug2
void ROOTN(int now){
	cout<<now<<"\n";
	if(now==n){
		//cout<<now<<"\n";
		return;
	}
	int endson;
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		if(haven[i]){
			endson=i;
		}
		if(!haven[i]&&!isleaf[i]){
			SONFA(i);
		}
	}
	for(auto i:nxt[now]){
		if(i==fa[now]){
			continue;
		}
		if(!haven[i]&&isleaf[i]){
			cout<<i<<"\n";
		}
	}
	if(!Rootn(endson)){
		SONBEGN(endson);
	}
	else{
		ROOTN(endson);
	}
}

void SONFA(int now){
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(isleaf[i]){
				cout<<i<<"\n";
			}
		}
	}
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(fason[i]==1){
				FASON(i);
			}
		}
	}
	cout<<now<<"\n";
}

void FASON(int now){
	cout<<now<<"\n";
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			//cout<<i<<" "<<sonfa[i]<<" "<<isleaf[i]<<"\n";
			if(!isleaf[i]&&sonfa[i]){
				SONFA(i);
			}
		}
	}
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(isleaf[i]){
				cout<<i<<"\n";
			}
		}
	}
}

bool Gsonbegn(int now){
	int cnt=0,cnt2=0;
	int endpos=0;
	if(gsonbegn[now]!=-1){
		goto label;
	}
	gsonbegn[now]=0;
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			cnt++;
			if(haven[i]){
				endpos=i;
				continue;
			}
			if(!isleaf[i]){
				if(Sonfa(i)){
					cnt2++;
					if(cnt2==2){
						goto label;
					}
				}
				else{
					goto label;
				}
			}
		}
	}
	if(cnt2!=1){
		goto label;
	}
	gsonbegn[now]=Rootn(endpos);
	label:return gsonbegn[now];
}

bool Sonbegn(int now){
	int tail=0;
	int ffason[2]={0,0},ssonfa[2]={0,0};
	if(sonbegn[now]!=-1){
		goto label;
	}
	sonbegn[now]=0;
	if(now==n&&isleaf[n]){
		goto label;
	}
	else if(now==n){
		sonbegn[now]=Sonfa(now);
		goto label;
	}
	else{
		int endpos=0;
		int cnt=0;
		for(auto i:nxt[now]){
			if(i!=fa[now]){
				cnt++;
				if(haven[i]){
					endpos=i;
				}
			}
		}
		if(cnt==1){
			sonbegn[now]=Gsonbegn(endpos)|Sononlyn(endpos);
			goto label;
		}
		for(auto i:nxt[now]){
			if(i!=fa[now]){
				if(haven[i]){
					endpos=i;
					continue;
				}
				if(isleaf[i]){
					continue;
				}
				if(tail==2){
					goto label;
				}
				if(Fason(i)||Sonfa(i)){
					ffason[tail]=Fason(i);
					ssonfa[tail]=Sonfa(i);
					tail++;
					continue;
				}
				goto label;
			}
		}
		bool havesonfa=0,havefason=0;
		if(tail==1){
			if(ffason[0]){
				havefason=1;
			}
			else if(ssonfa[0]){
				havesonfa=1;
			}
		}
		else{
			for(int i=0;i<tail;i++){
				havesonfa|=ssonfa[i];
				havefason|=ffason[i];
			}
		}
		sonbegn[now]=Rootn(endpos)|((!havesonfa)&&Sonbegn(endpos));
	}
	label:
	return sonbegn[now];
}

void SONBEGN(int now){
	int cnt=0;
	if(now==n){
		SONFA(now);
		return;
	}
	if(cnt==1){
		int son;
		for(auto i:nxt[now]){
			if(i!=fa[now]){
				son=i;
			}
		}
		if(Sonbegn(son)){
			cout<<son<<"\n"<<now<<"\n";
			SONBEGN(son);
		}
		else{
			GSONBEGN(son);
		}
		return;
	}
	int fason[2]={0,0},sonfa[2]={0,0},value[2]={0,0},tail=0;
	int endson=0;
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(haven[i]){
				endson=i;
			}
			if(!haven[i]&&!isleaf[i]){
				if(::fason[i]){
					fason[tail]=1;
				}
				if(::sonfa[i]){
					sonfa[tail]=1;
				}
				value[tail]=i;
				tail++;
			}
		}
	}
	int fasonv=0,sonfav=0;
	for(int i=0;i<tail;i++){
		if(fason[i]){
			fasonv=value[i];
		}
	}
	for(int i=0;i<tail;i++){
		if(sonfa[i]){
			if(fasonv==value[i]){
				for(int j=0;j<tail;j++){
					if(fason[j]&&j!=i){
						fasonv=value[j];
						sonfav=value[i];
						goto label;
					}
				}
			}
		}
	}
	label:;
	if(rootn[endson]){
		if(fasonv){
			FASON(fasonv);
		}
		cout<<now<<"\n";
		if(sonfav){
			SONFA(sonfav);
		}
		for(auto i:nxt[now]){
			if(i!=fa[now]){
				if(i!=endson&&isleaf[i]){
					cout<<i<<"\n";
				}
			}
		}
		ROOTN(endson);
	}
	else{
		for(auto i:nxt[now]){
			if(i!=fa[now]){
				if(i!=endson&&isleaf[i]){
					cout<<i<<"\n";
				}
			}
		}
		if(fasonv){
			FASON(fasonv);
		}
		cout<<now<<"\n";
		SONBEGN(endson);
	}
}

void SONONLYN(int now){
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(!haven[i]){
				cout<<i<<"\n";
			}
		}
	}
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(haven[i]){
				ROOTN(i);
			}
		}
	}
}

void GSONBEGN(int now){
	cout<<now<<"\n";
	int endpos=0;
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(haven[i]){
				endpos=i;
				continue;
			}
			if(!isleaf[i]){
				SONFA(i);
			}
		}
	}
	for(auto i:nxt[now]){
		if(i!=fa[now]){
			if(!haven[i]&&isleaf[i]){
				cout<<i<<"\n";
			}
		}
	}
	cout<<fa[now]<<"\n";
	Rootn(endpos);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		rootn[i]=sonfa[i]=fason[i]=sonbegn[i]=sononlyn[i]=gsonbegn[i]=-1;
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		nxt[u].push_back(v);
		nxt[v].push_back(u);
	}
	dfs(1);
	int now=n;
	while(now){
		haven[now]=1;
		now=fa[now];
	}
	if(Rootn(1)){
		ROOTN(1);
	}
	else{
		cout<<"BRAK";
	}
}
```

---

## 作者：w9095 (赞：0)

[P3549 [POI 2013] MUL-Multidrink](https://www.luogu.com.cn/problem/P3549)

非常 tricky 的一道题，模拟赛拼尽全力无法战胜，写篇题解记录一下。

容易理解的直接构造法。

按原题限制随便跳会破坏很多性质，几乎无法定向构造。考虑最后必须到 $n$，每经过一个点，必须要遍历其所有子树，而从 $1\to n$ 至少会经过之间的路径，路径上的节点可以调整为依次经过，所以考虑把 $1\to n$ 的路径提出来，每次考虑子树内的构造，走完之后再走到路径上下一个节点。

考虑一个点的子树走到下一个点的子树，只会从这个点子树的根或一个儿子走到另一个点子树的根或一个儿子。

考虑从一个点的子树走出来，结合决策包容性，发现能从根节点节点走出来就从根节点走，否则就从根节点的儿子走出来。发现此时已经不存在决策了，对每个点记录能否到自己和自己儿子，按照优先级决策，可以直接构造。

观察每一次的操作，我们发现就是要实现对于每个节点的子树儿子进自己出或自己进儿子出的构造。考虑把这些组合成一个操作。

考虑无解的情况，以某个节点自己进儿子出为例。如果存在两棵大小大于 $1$ 的子树，进入其中一棵子树回来的时候这个节点和对应子树的子节点都已经被访问过，无解。且在任意情况下，无论怎么遍历，无解的依旧无解。

以某个节点自己进儿子出为例。由上述分析有解时每个点只会有一个大小大于 $1$ 的子树，大小为 $1$ 的子树可以在儿子进自己出地访问完这棵子树后顺次访问，自己进儿子出访问显然无解。于是归约为了更小的问题，递归构造。时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	int v,nxt;
}e[4000001];
int n,u,v,h[2000001],fa[2000001],siz[2000001],ans[2000001],st[2000001],tol=0,mx=0,cnt=0,top=0;
bool vis[2000001];
void cstr_sf(int,int);
void cstr_fs(int,int);
void add_edge(int u,int v)
{
	e[++cnt].nxt=h[u];
	e[cnt].v=v;
	h[u]=cnt;
} 

void end()
{
	printf("BRAK\n");
	exit(0);
}

void cstr_sf(int x,int pr)
{
	vector<int>ss,sl;
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=pr&&!vis[e[i].v]&&siz[e[i].v]==1)ss.push_back(e[i].v);
	    else if(e[i].v!=pr&&!vis[e[i].v])sl.push_back(e[i].v);
	if(sl.size()>=2)end();
	for(int i=0;i<ss.size();i++)ans[++tol]=ss[i];
	for(int i=0;i<sl.size();i++)cstr_fs(sl[i],x);
	ans[++tol]=x;
}

void cstr_fs(int x,int pr)
{
	ans[++tol]=x;
	vector<int>ss,sl;
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=pr&&!vis[e[i].v]&&siz[e[i].v]==1)ss.push_back(e[i].v);
	    else if(e[i].v!=pr&&!vis[e[i].v])sl.push_back(e[i].v);
	if(sl.size()>=2)end();
	for(int i=0;i<sl.size();i++)cstr_sf(sl[i],x);
	for(int i=0;i<ss.size();i++)ans[++tol]=ss[i];
}

void dfs(int x,int pr)
{
	siz[x]=1,fa[x]=pr;
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=pr)dfs(e[i].v,x),siz[x]+=siz[e[i].v];
}

bool cstr(int x,int pr,bool flag)
{
	vector<int>ss,sl;
	for(int i=h[x];i;i=e[i].nxt)
	    if(e[i].v!=pr&&!vis[e[i].v]&&siz[e[i].v]==1)ss.push_back(e[i].v);
	    else if(e[i].v!=pr&&!vis[e[i].v])sl.push_back(e[i].v);
	if(x==n)
	   {
	   	if(siz[x]==1)ans[++tol]=x;
	   	else
	   	   {
	   	   	if(!flag)end();
	   	   	cstr_sf(x,pr);
		   }
		return 0;
	   }
	bool tf=0;
	if(ss.empty()&&sl.empty())ans[++tol]=x,tf=1;
	else if(!flag)
	   {
	   	if(sl.size()>=2)end();
	   	ans[++tol]=x,tf=0;
	   	for(int i=0;i<sl.size();i++)cstr_sf(sl[i],x);
	    for(int i=0;i<ss.size();i++)ans[++tol]=ss[i];
	   }
	else
	   {
	   	if(sl.size()==0)
	   	   {
		   for(int i=0;i<ss.size();i++)ans[++tol]=ss[i];
		   ans[++tol]=x,tf=1;
	       }
	   	else if(sl.size()==1)
	   	   {
		   for(int i=0;i<ss.size();i++)ans[++tol]=ss[i];
		   for(int i=0;i<sl.size();i++)cstr_fs(sl[i],x);
		   ans[++tol]=x,tf=1;
	       }
	   	else if(sl.size()==2)
	   	   {
	   	   cstr_fs(sl[0],x),ans[++tol]=x,tf=0,cstr_sf(sl[1],x);
	   	   for(int i=0;i<ss.size();i++)ans[++tol]=ss[i];
		   }
	   	else end();
	   }
	return tf;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)scanf("%d%d",&u,&v),add_edge(u,v),add_edge(v,u);
	dfs(1,0);
	int x=n;
	while(x)vis[x]=1,st[++top]=x,x=fa[x];
	bool tf=0;
	for(int i=top;i>=1;i--)tf=cstr(st[i],0,tf);
	for(int i=1;i<=tol;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

机房大佬说这题思路上没有黑题的压迫感。

不妨拎起 $1\to n$ 的链，链上每个点代表一棵子树。直觉上应该依次将子树遍历完再进行下去，这确实是对的。证明考虑调整法即可，假如我多次遍历该子树，则存在方案一次性遍历完，然后其它的对该子树的遍历就跳过即可。

于是考虑对一棵子树的遍历，同理进入儿子子树就应该遍历完，显然树形 dp，记 $f_{u,0/1/2/3}$ 表示根进根出、根进儿子出、儿子进根出、儿子进儿子出地遍历完该子树是否可行。注意一个性质：$f_{u,1/2}$ 实际上是相反的，也就是说一个成立另一个肯定成立，不妨一起记在 $f_{u,1}$。

转移大力分讨即可：

1. $f_{u,0}$：等价于 $u$ 无儿子。
2. $f_{u,1}$：以儿子进根出为例，发现要么从一个儿子 $v$ 的 $f_{v,1}$ 开始、然后将叶子跳完、最后跳到 $u$；要么全是叶子跳完后再跳到 $u$。也就是等价于 $\sum\limits_{v\in son(u)} f_{v,0} \ge |son(u)|-1$，且剩下的那个必须满足 $f_{v,1}$ 成立。
3. $f_{u,2}$：不难发现，优先跳完叶子不劣，所以先将所有叶子跳完。接着，假如一棵儿子子树不剩，就在跳叶子过程中跳到 $u$ 即可；假如只剩 $1$ 棵 $v$ 子树，先跳 $u$ 再跳 $f_{v,1}$（儿子进根出）的方案即可；假如剩 $2$ 棵子树 $v_1,v_2$，则对 $v_1$ 进行根进儿子出，再跳到 $u$，对 $v_2$ 进行儿子进根出即可。假如剩 $\ge 3$ 棵子树无解。也就是等价于去掉所有叶子后，儿子子树必须满足 $f_{v,1}$ 成立，且儿子子树个数 $\le 2$。

最后，将链上的子树方案合并起来，肯定从左到右一个个地遍历，记 $g_{i,0/1}$ 表示遍历完链上前 $i$ 棵子树、且最终停留在 $i$ 子树根或儿子上是否可行。转移是容易的，留给读者思考。

输出方案按转移进行即可。复杂度 $O(n)$。
#### 代码
依托答辩，难以评价。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 6e5 + 5;
int n, u, v, d[N], dist[N], dn;
bool vis[N], f[N][3], g[N][2]; 
vector<int> to[N], son[N], ans;

inline void init(int u, int from){
	for(auto v : to[u])
		if(v ^ from) init(v, u), vis[u] |= vis[v];
	if(u == n) vis[u] = true;
	if(vis[u]) dist[++dn] = u;
}
inline void dfs(int u){
	vis[u] = true;
	for(auto v : to[u])	
		if(!vis[v]) dfs(v), son[u].push_back(v);
	f[u][0] = son[u].empty();
	
	if(!son[u].empty()){
		f[u][1] = true;
		int cnt = 0;
		for(auto v : son[u])
			if(!f[v][0]){
				if(!f[v][1]) f[u][1] = false;
				else if(++cnt > 1) f[u][1] = false;
			}
	}
	
	if(son[u].size() >= 2){
		f[u][2] = true;
		int cnt = 0;
		for(auto v : son[u])
			if(!f[v][0]){
				if(!f[v][1]) f[u][2] = false;
				else if(++cnt > 2) f[u][2] = false;
			}
	}
}
inline void print(int u, int id){
	//0：叶
	//1：u进v出
	//2: v进u出
	//3：v进v出 
	if(!id) ans.push_back(u);
	if(id == 1){
		ans.push_back(u);
		for(auto v : son[u]) if(!f[v][0]) print(v, 2);
		for(auto v : son[u]) if(f[v][0]) print(v, 0);
	}
	if(id == 2){
		for(auto v : son[u]) if(f[v][0]) print(v, 0);
		for(auto v : son[u]) if(!f[v][0]) print(v, 1);
		ans.push_back(u);
	}
	if(id == 3){
		int fir = 0, sec = 0;
		for(auto v : son[u]) 
			if(!f[v][0]){
				if(!fir) fir = v;
				else sec = v;
			}
		if(!fir){
			for(auto v : son[u])
				if(f[v][0]){
					print(v, 0);
					if(!fir) ans.push_back(u), fir = 1; 
				}
		}
		else{
			for(auto v : son[u]) if(f[v][0]) print(v, 0);
			bool fl = false;
			for(auto v : son[u])
				if(!f[v][0]){
					if(!fl) print(v, 1), ans.push_back(u), fl = true;
					else print(v, 2);
				}
		}
		
	}
}
inline void print2(int i, int id){
	if(i == 1){
		if(!id) print(dist[i], 0);
		else print(dist[i], 1);
		return ;
	}
	if(!id){
		if(g[i - 1][0] && f[dist[i]][0]) print2(i - 1, 0), print(dist[i], 0);
		else if(g[i - 1][0] && f[dist[i]][1]) print2(i - 1, 0), print(dist[i], 2);
		else if(g[i - 1][1] && f[dist[i]][0]) print2(i - 1, 1), print(dist[i], 0);
	}
	else
		if(g[i - 1][0] && f[dist[i]][1]) print2(i - 1, 0), print(dist[i], 1);
		else if(g[i - 1][0] && f[dist[i]][2]) print2(i - 1, 0), print(dist[i], 3);
		else if(g[i - 1][1] && f[dist[i]][1]) print2(i - 1, 1), print(dist[i], 1); 
}
signed main(){
	cin >> n;
	for(int i = 1; i < n; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	init(1, 0);
	reverse(dist + 1, dist + 1 + dn);
	for(int i = 1; i <= dn; ++i) dfs(dist[i]);
	g[1][0] = f[dist[1]][0], g[1][1] = f[dist[1]][1];
	for(int i = 2; i <= dn; ++i){
		g[i][0] = (g[i - 1][0] & (f[dist[i]][0] | f[dist[i]][1])) | (g[i - 1][1] & f[dist[i]][0]);
		g[i][1] = (g[i - 1][0] & (f[dist[i]][1] | f[dist[i]][2])) | (g[i - 1][1] & f[dist[i]][1]);
	}
	if(!g[dn][0]) puts("BRAK"); 
	else{
		print2(dn, 0);
		for(auto i : ans) printf("%d\n", i);
	}
	return 0;
}

```

---

## 作者：tybbs (赞：0)


[题目链接](https://www.luogu.com.cn/problem/P3549 "题目链接")

初步观察题目，发现可以把过程大致理解为跳 $1$ 到 $n$ 的链，中途路过其他点。

可以先把 $1$ 到 $n$ 的链抽出来，再把链上的点的作为树根，得到一条每个结点上都挂了一棵树的结构。

我们初步考虑，应当要让从链走入子树时可以“返回”，所以我们树形 dp ，记 

$f_{u,1}$ 表示子树 $u$ 从 $u$ 进入，可否遍历后返回 $fa_u$；

$f_{u,0}$ 表示子树 $u$ 从 $fa_u$ 进入，可否遍历返回 $u$。

考虑如何进行转移：

先考虑 $f_{u,1}$：

（我们称一个点为“单点”，当且仅当这个点没有儿子,记 $u$ 的儿子构成的集合为 $son(u)$）

1. 如果 $son(u)$ 中没有非单点， $f_{u,1}=1$。 这是显然的，只需从 $u$ 进入，遍历儿子结点即可。

2. 如果 $son(u)$ 中有且仅有一个单点，不妨设为 $k$，则 $f_{u,1}=f_{k,0}$。 若 $f_{k,0}=1$, 从 $u$ 进入子树 $k$ 再返回到 $k$ 遍历其他单点即可。反之，若 $f_{k,0}=0$，一旦进入子树 $k$，就无法返回，可得$f_{u,1}=0$。

3. 如果 $son(u)$ 中有多个非单点，$f_{u,1}=0$。不妨设有非单点 $k1,k2$。因为进入子树 $k1$ 后，只能终结在 $k1$，跳单点只能从 $k2$ 进入 $k2$ 的子树，然后就无发返回了。

$f_{u,0}$ 差不多同理，结论唯一的不同是 “如果 $son(u)$ 中有且仅有一个单点，不妨设为 $k$，则 $f_{u,0}=f_{k,1}$”。


计算完 $f$ 后，我们考虑如何求答案。

我们记 $g_{u,1}$ 表示从一出发可以跳链到达 $u$ （ $u$ 为链上节点），此时 $1-u$ 的所有结点上挂的子树都被访问， $u$ 所在子树亦被遍历，目前位于 $u$ 结点是否可行。

$g_{u,1}$ 表示从一出发可以跳链到达 $u$ （ $u$ 为链上节点），此时 $1-u$ 的所有结点上挂的子树都被访问， $u$ 所在子树**未**被遍历，目前位于 $u$ 结点是否可行。

记 $x$ 为 $u$ 前一个结点。

$g_{u,1}$ 大部分转移显然（$g_{u,1}=g_{x,1} \vee (g_{x,0} \wedge f_{x,1})$），可以看代码。有一种比较特别：$x$ 有两个非单点子节点 $s1,s2$。可以从 $x$ 的前一个结点进入 $s1$ ，遍历完毕回到 $x$, 跳到 $s2$，遍历子节点中的单点，进入 $u$。

$g_{u,0}$ 在 $size(u)=1$ 时转移与 $g_{u,1}$ 相同，$size(u)>1$ 时，$g_{u,1}=g_{x,1} \wedge f_{u,0}$。
最终答案即为 $g_{n,1}$。

找方案其实是简单的，就是正常的 dp 回溯。

代码：实现的不太好，很长。

[代码](https://www.luogu.com.cn/paste/u1pphnkh "代码")

---

