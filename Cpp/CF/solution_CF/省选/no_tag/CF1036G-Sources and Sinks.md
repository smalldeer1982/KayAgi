# Sources and Sinks

## 题目描述

## 题意翻译

给出一张 DAG（$1\leq n, m\leq 10^6$，其中 $n$ 为结点数，$m$ 为边数）

称无入边的结点为 “源点”；无出边的结点为 “汇点”。我们还保证这张 DAG 的源点数量与汇点数量相等，且均不超过 $20$ 个

现在我们对这张 DAG 重复以下操作：

1. 选择**任意**一对源点与汇点 $s, t$
2. 添加一条（有向）边 $(t, s)$；如果仍还有源点与汇点，就再回到操作 $1$。可以发现该次操作将会导致 $s$ 不再是一个源点，$t$ 不再是一个汇点；并且该次操作还有可能添加一个**自环**

现在问，无论操作中的具体选择如何，该图在所有操作结束后，是否**总是**成为**一个**强联通分量（即任意一对结点间都可以相互到达）

## 样例 #1

### 输入

```
3 1
1 2
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 3
1 2
1 3
2 3
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4 4
1 2
1 3
4 2
4 3
```

### 输出

```
YES
```

# 题解

## 作者：Piwry (赞：3)

话说社论中貌似有多项式时间的做法...（Orz）

详见 [此处](https://codeforces.com/blog/entry/61727) 下面的 `dragonslayerintraining` 的评论（[code](https://codeforces.com/contest/1036/submission/67053099)）

## 解析

设 $S$ 为一些源结点 $s$ 的集合，设 $f(S)$ 为所有能被 $S$ 中某一个元素到达的汇结点 $t$ 的集合，设源结点/汇结点的总数 $C$

我们有结论：

1. 若对于所有可能的 $S$ 满足 $|S|\not =C$（注意这和 $|f(S)|\not =C$ 不等价）且 $|S|\not=0$，有 $|S|\geq |f(S)|$，那么答案是 `NO`
2. 若不满足 $1.$，那么答案就是 `YES`

先证明 $1.$。由于 $|S|\geq |f(S)|$，只需考虑将 $f(S)$ 均与 $S$ 内汇结点配对，那么 $f(S)$ 内的汇结点就永远无法到达其它不属于 $f(S)$ 的汇结点了

接着证明 $2.$。我们考虑用归纳法证明：

1. 初始时，对于任意汇结点 $t$ 它显然可以到达自己
2. 设 $T_t$ 是 $t$ 可以到达的汇结点的集合，设 $h(T_t)$ 表示 $T_t$ 所有元素与源结点配对后，配对的源结点可以到达的汇结点的集合（设 $T_t$ 配对的源结点集合为 $S_{T_t}$ 应有 $|S_{T_t}|=|T_t|$，这里即指 $f(S_{T_t})$），且发现 $h(T_t)$ 也是可以被 $t$ 到达的。此时要么 $|T_t|=C$，那么整张图就可以被 $t$ 到达；否则就有 $|h(T_t)|$ 至少为 $|T_t|+1$，这样归纳下去，$t$ 最后一定能到达整张图

证明每个汇点最后能到达整张图后，显然整张图就成为了一个强联通分量

于是枚举 $S$ 检查其 $f(S)$ 即可，复杂度 $O(2^{20}+n+m)$（最坏）

关于具体实现时如何处理出每个源结点可以到达的汇结点，可以考虑状压汇结点，然后从每个源结点 dfs，dp 处理出每个结点能到达的汇结点集合。由于原图不存在环，因此 dfs 时一定不会出现访问 dfs 树的父亲的情况

## CODE

```cpp
#include <cstdio>

/*------------------------------Map------------------------------*/

const int MAXN =1e6+50;

int first[MAXN], tote;
bool vis[MAXN];
struct edge{
	int net, to;
}e[MAXN];

inline void addedge(const int &u, const int &v){
	++tote;
	e[tote].net =first[u], first[u] =tote, e[tote].to =v;
}

/*------------------------------Dfs------------------------------*/

int in[MAXN], out[MAXN];
int reach[MAXN];
int id[MAXN];
int s[20], t[20], tots, tott;

void dfs(const int &u){
	vis[u] =1;
	for(int l =first[u]; l; l =e[l].net){
			dfs(e[l].to);
			reach[u] |=reach[e[l].to];
		}
	if(out[u] == 0)
		reach[u] =(1<<id[u]);
}

bool NO =0;

void dfs_check(const int &i, const int &cnts, const int &reach_nw){
	if(i == tots){
		if(cnts != 0 && cnts != tots && cnts >= __builtin_popcount(reach_nw))
			NO =1;
	}
	else{
		dfs_check(i+1, cnts, reach_nw);
		dfs_check(i+1, cnts+1, reach_nw|reach[s[i]]);
	}
}

/*------------------------------main------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

int main(){
	int n =read(), m =read();
	for(int i =0; i < m; ++i){
		int u =read(), v =read();
		addedge(u, v);
		++in[v], ++out[u];
	}
	for(int i =1; i <= n; ++i){
		if(in[i] == 0)
			s[tots++] =i, id[i] =tots-1;
		if(out[i] == 0)
			t[tott++] =i, id[i] =tott-1;
	}
	for(int i =1; i <= n; ++i)
		if(in[i] == 0)
			dfs(i);
	dfs_check(0, 0, 0);
	if(NO)
		puts("NO");
	else
		puts("YES");
}
```

---

## 作者：Alex_Wei (赞：2)

### *[CF1036G Sources and Sinks](https://www.luogu.com.cn/problem/CF1036G)

设源点数量为 $k$，称一组源汇匹配方案不合法，当且仅当按题目操作后图不是强连通分量。题目要求检查任意匹配方案是否均合法，那目标一定是找出一组不合法的匹配。

若图不是强连通分量，则存在点 $x$ 使得它不可达图上某点 $y$。又因为 $x$ 可达某个汇点，$y$ 被某个源点可达，所以一种源汇匹配的方案不合法当且仅当存在某个汇点不可达图上某个源点。

考虑汇点 $x$ 可达的源点 $y$。设当前可达源点集为 $S$，汇点集为 $T$，初始 $S = \varnothing$，$T = \{x\}$。考虑图的遍历过程，就是先令 $S \gets S\cup g(T)$，然后令 $T\gets T\cup f(S)$，其中 $g(T)$ 是 $T$ 中每个汇点匹配的源点集合，$f(S)$ 是 $S$ 中每个源点可达的汇点集合的并。因为对于 $T'\subseteq T$，有 $g(T')\subseteq g(T)$，因此令 $S\gets g(T)$ 也是正确的。

注意到 $|S| = g(|T|) = |T|$，而整个过程需要在 $|S|$ 变为 $k$ 之前停止。如果 $f(S)\subseteq T$，那么 $|T|$ 不再增加，$T$ 保持不变，无论再进行多少次操作 $T$ 仍保持不变。因此，若存在 $S\neq U$（$U$ 是源点全集，要求 $|S| < k$）满足 $|S| \geq |f(S)|$，那么构造匹配使得 $g(f(S))\subseteq S$（因为 $|S| \geq |f(S)|$ 所以这是容易的），则 $f(S)$ 的任意汇点均只可达 $S$ 的子集，存在不合法汇点。

否则，对于任意 $S\neq U$ 均有 $|S| < |f(S)|$，则无论怎么匹配，从任意汇点出发，$S$ 总会变成源点全集 $U$。

至此得到结论：答案为 `NO` 当且仅当存在 $S\neq U$ 满足 $|S| \geq |f(S)|$，拓扑排序后状压 DP 求 $f$ 即可。时间复杂度 $\mathcal{O}(2 ^ k + n + m)$。[代码](https://codeforces.com/contest/1036/submission/214688018)。

构造二分图：若源点 $x\rightsquigarrow y$，则从左部点 $x$ 向右部点 $y$ 连边。左部点的权值为 $1$，右部点的权值为 $-1$，问题转化为判定该二分图是否存在非平凡的权值不小于 $0$ 的闭合子图，平凡指所有左部点或没有左部点被选中。这样就是 [ARC161F](https://www.luogu.com.cn/problem/AT_arc161_f) 了。时间复杂度 $\mathcal{O}(k ^ {2.5} + n + \frac {mk} w)$，其中 $\frac {mk} w$ 是求每个源点可达哪些汇点的复杂度。

---

## 作者：Terac (赞：1)

提供本题一种切入点。

除了源汇点其它点是不重要的，把每个源点能到达的汇点预处理出来，变成一张二分图，设 $k$ 为源汇点个数，$k\le 20$。

这个数据范围猜测可能跟 hall 定理有关系，我猜它这个二分图有完美匹配时就是 `YES`，但是好像 $n=1$ 都不对。

还是往 hall 定理想。若存在某些非空源点集合 $S$，它们可达汇点集合 $T$，若 $|T|\ne k$ 且 $|S|\ge|T|$ 时，答案必定为 `NO`，因为只要 $S$ 中每个点都匹配 $T$，那对于 $t\in T$，其通过 $S$，无法到达 $T$ 外的汇点，当然 $|T|=k$ 时除外。

现在证明反之答案为 `YES`。记 $f(T)$ 为汇点集合 $T$ 匹配的源点集合 $S$ 可达的汇点集合，由上面的结论 $|f(T)|>|S|=|T|$，所以可达的源点和汇点集合只会不断变大，直到 $f(T)=k$，所有的源点和汇点都可达，符合限制。

发现这个结论和 hall 定理只有在能否取等上有不同，尝试理解这和二分图匹配的存在性问题的关系，感性理解下可以感知到是相等时源点集合不能向外拓展，所以必须多一个汇点来拓展源点集合。

时间复杂度 $O(n+m+2^k)$。

---

