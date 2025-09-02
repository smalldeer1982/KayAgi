# [JOI Open 2018] 猫或狗 / Cats or Dogs

## 题目背景

**特别提醒，由于洛谷交互机制的特殊性，你不能在程序中引用 `catdog.h`，只需要实现要求的几个函数即可。**

## 题目描述

你的儿子 JOI 君喜欢养宠物。在你家的花园里有 $N$​ 个小屋可供饲养宠物，这 $N$ 个房子从 $1$ 到 $N$ 编号。有 $N-1$ 条双向路径双向连接这 $N$ 个小屋，并且对于任意两个小屋，都可以通过某些路径在它们之间移动。每个小屋最多可以住一只宠物。

JOI 君想要养猫和狗，但是他很担心宠物们可能会经常打架。对于每个小屋的如下状态：住了一只猫，住了一只狗，没有住宠物，他都按如下方式定义了花园的**危险级别**：

- 对于每只猫和每只狗，为了不让他们通过未阻塞的道路相遇，需要阻塞的最小路径数。

在定义危险级别后，JOI 君开始指定后 $Q$ 天使用花园的计划。初始时，所有小屋里都没有宠物。第 $i$ 天的计划是如下内容中的一个：

- 在目前没有宠物的小屋 $v$​​ 中养一只猫。
- 在目前没有宠物的小屋 $v$ 中养一只狗。
- 将小屋 $v$ 中的宠物送给邻居，这意味着在小屋 $v$​ 中就没有宠物了。

你作为家长，有责任检查你的儿子的计划是否危险。更确切地说，你需要求出这 $Q$ 天每天进行完计划后，这个花园的危险级别。

---

**为了在线地回答询问，本题采用交互的方式进行评测。**

你需要实现四个函数 `initialize`，`cat`，`dog` 和 `neighbor`。

最初，函数 `initialize` 被调用。这个函数的作用是接受花园的信息。

- `initialize(N, A, B)`
  - $N$：花园中小屋的数量。
  - $A, B$：长度为 $N-1$ 的数组。意味着对于 $0\le i\le N-2$，在小屋 $A_i$ 和小屋 $B_i$ 之间存在一条路径。保证对于任意两个不同的小屋，沿某些路径可以在它们之间移动。

然后，对于这 $Q$ 天的计划，按时间顺序会调用如下函数：

- `cat(v)`：调用此函数，在目前没有宠物的小屋 $v$ 中养一只猫。
- `dog(v)`：调用此函数，在目前没有宠物的小屋 $v$ 中养一只狗。
- `neighbor(v)`：调用此函数，让小屋 $v$ 中的宠物离开。

这些函数应返回在这个计划执行后花园的危险值。

目前不支持对 Java 和 Pascal 语言提交的测评。



## 说明/提示

**【样例】**

考虑有 $5$ 个小屋和 $4$ 条路径的情况。这四条路径连接小屋 $1$ 和小屋 $2$，小屋 $2$ 和小屋 $3$，小屋 $2$ 和小屋 $4$，小屋 $4$ 和小屋 $5$。

1. 假设他首先在小屋 $3$ 养了一只猫，在小屋 $5$ 养了一只狗。通过阻塞小屋 $2$ 和小屋 $4$ 之间的道路，他可以避免猫和狗相遇。因此，此时的危险等级是 $1$。
2. 假设他之后在小屋 $2$​ 养了一直新猫，在小屋 $1$​ 养了一只新狗。通过阻塞小屋 $2$​ 和小屋 $4$​ 之间的道路与小屋 $1$​ 和小屋 $2$​ 之间的道路，他可以避免猫和狗相遇。因此，此时的危险等级是 $2$。
3. 假设他最后将小屋 $2$ 的猫给了邻居。他只需要阻塞小屋 $2$ 和小屋 $3$ 之间的道路。因此，此时的危险等级是 $1$。



**【数据范围】**

本题有三个子任务。每个子任务的分值与附加限制如下表所示：

| 子任务编号 | 分值 |         $N$          |         $Q$          |
| :--------: | :--: | :------------------: | :------------------: |
|    $1$     | $8$  |    $1\le N\le 15$    |   $1\le Q\le 100$    |
|    $2$     | $30$ |  $1\le N\le 1\ 000$  |  $1\le Q\le 1\ 000$  |
|    $3$     | $62$ | $1\le N\le 100\ 000$ | $1\le Q\le 100\ 000$ |



## 样例 #1

### 输入

```
3
1 2
2 3
4
1 1
1 3
2 2
3 2
```

### 输出

```
0
0
2
0```

## 样例 #2

### 输入

```
5
1 2
2 3
2 4
4 5
5
1 3
2 5
1 2
2 1
3 2```

### 输出

```
0
1
1
2
1```

# 题解

## 作者：CaoXian (赞：4)

这道题的交互只是为了强制在线而已，算不上真正意义上的交互题。

动态 dp 板板题。

---

题意简述：

给定一棵树，刚开始每个点都没有被染色，每次操作可以将一个未染色结点染为红色或蓝色，或是将一个已染色的结点变为无色。每次操作后需要求出：在树上最少删去多少条边可以使得每一个联通块内不会同时出现红色和蓝色的结点。

先考虑暴力：

每次修改完后在树上跑一遍树形 dp。令 $dp_{i, 0/1/2}$ 表示在以编号为 $i$ 的结点为根结点的子树中，根节点所属联通块的颜色为无色、红色、蓝色的情况下，最少需要删多少条边可以使得当前子树满足条件。

转移方程很容易写出来：

$$
\begin{matrix}
dp_{u, 0} =
\begin{cases}
\sum\limits_{v\in son_{u}}\min(dp_{v, 0}, dp_{v, 1} + 1, dp_{v, 2} + 1)&color_{u} = 0\\
\infty&color_{u} \not= 0
\end{cases}\\\\
dp_{u, 1} =
\begin{cases}
\sum\limits_{v\in son_{u}}\min(dp_{v, 0}, dp_{v, 1}, dp_{v, 2} + 1)&color_{u} = 1\\
\infty&color_{u} \not= 1
\end{cases}\\\\
dp_{u, 2} =
\begin{cases}
\sum\limits_{v\in son_{u}}\min(dp_{v, 0}, dp_{v, 1} + 1, dp_{v, 2})&color_{u} = 2\\
\infty&color_{u} \not= 2
\end{cases}\\
\end{matrix}
$$

上面的式子中 $son_{u}$ 表示结点 $u$ 的子结点集合，$color_{u}$ 表示结点 $u$ 的颜色，$0$ 表示无色，$1$ 表示红色，$2$ 表示蓝色，若某个 $dp_{u, 0/1/2}$ 为 $\infty$ 则表示这种状态不可能出现。

观察这个式子，其实可以做出一些小优化，比如 $dp_{u, 0}$ 的转移一定不是最优的，可以合并到另外两个转移中。

重新定义 $dp_{u, 0/1}$ 表示在以编号为 $i$ 的结点为根结点的子树中，根节点所属联通块的颜色**没有蓝色**或**没有红色**的情况下，最少需要删多少条边可以使得当前子树满足条件。

转移方程就会简化为：

$$
\begin{matrix}
dp_{u, 0} =
\begin{cases}
\sum\limits_{v\in son_{u}}\min(dp_{v, 0}, dp_{v, 1} + 1)&color_{u} \not= 2\\
\infty&color_{u} = 2
\end{cases}\\\\
dp_{u, 1} =
\begin{cases}
\sum\limits_{v\in son_{u}}\min(dp_{v, 0} + 1, dp_{v, 1})&color_{u} \not= 1\\
\infty&color_{u} = 1
\end{cases}
\end{matrix}
$$

这一点常数优化在正解里非常重要，因为这样做的的话单次广义矩阵乘法就可以从 $27$ 次运算降到 $8$ 次运算，大约优化了 $3$ 倍的常数。

上面的做法时间复杂度是 $\mathcal{O}(QN)$ 的，无法通过。

接下来就是动态 dp 的解释了：

我们定义广义矩阵乘法 $A \times B = C$ 满足：

$$
C_{i, j} = \min\limits_{1 \leqslant k \leqslant M}\left\{A_{i, k} + B_{k, j}\right\}
$$

其中 $A$ 矩阵为 $N \times M$ 的矩阵， $B$ 矩阵为 $M \times R$ 的矩阵，$C$ 矩阵为 $N \times R$ 的矩阵。

可以发现这种运算仍然满足结合律。

我们可以把上面的转移方程改成广义矩阵乘法的形式：

$$
\begin{bmatrix}
dp_{u', 0} & dp_{u', 0} + 1\\
dp_{u', 1} + 1 & dp_{u', 1}
\end{bmatrix}

\times

\begin{bmatrix}
dp_{v, 0}\\
dp_{v, 1}
\end{bmatrix}

=

\begin{bmatrix}
dp_{u, 0}\\
dp_{u, 1}
\end{bmatrix}
$$

上面的 $dp_{u', 0/1}$ 是表示还没有转移 $u$ 的子结点 $v$ 之前的 $u$ 的答案。或者可以理解为将 $v$ 从 $u$ 的子结点中去掉后，$u$ 的答案。

每次修改一个结点就相当于把从它到根结点的链上所有的转移矩阵修改了，暴力修改肯定是不行的，可以重链剖分过后做到每次最多修改 $\log N$ 个转移矩阵。

具体的话就是维护每个结点**除开重儿子**的转移矩阵，额外定义 $g_{u, 0/1}$ 表示不考虑重儿子的情况下的答案，跟上面的 $dp_{u', 0/1}$ 差不多。修改的时候把经过的重链末端的结点的转移矩阵更改了就行。

关于动态 dp 的部分不再细讲了，如果不会动态 dp 的话建议先去做[模板题](https://www.luogu.com.cn/problem/P4719)，里面的题解也有详细的解释。

注意每次修改节点颜色状态后，如果结点有颜色，一定要把转移矩阵中不可能出现的那一行全部设为 $\infty$，这样才能避免错误转移。

给出代码实现：

```cpp
// #include "catdog.h"
#include <bits/stdc++.h>
using namespace std;
const int inf = 100000;
int n, m, u, v, add[2], sub[2], color[100005], f[100005][2], _g[100005][2];
int cnt, fa[100005], siz[100005], dep[100005], son[100005], dfn[100005], top[100005], rnk[100005], bot[100005];
vector<int> e[100005];
struct matrix {
	int v[2][2];
	matrix(int val = inf) {
		v[0][0] = val, v[0][1] = inf;
		v[1][0] = inf, v[1][1] = val;
	}
	matrix operator = (const matrix& _) {
		v[0][0] = _.v[0][0], v[0][1] = _.v[0][1];
		v[1][0] = _.v[1][0], v[1][1] = _.v[1][1];
		return *this;
	}
	matrix operator * (const matrix& _) const {
		matrix ret;
		ret.v[0][0] = min(v[0][0] + _.v[0][0], v[0][1] + _.v[1][0]);
		ret.v[0][1] = min(v[0][0] + _.v[0][1], v[0][1] + _.v[1][1]);
		ret.v[1][0] = min(v[1][0] + _.v[0][0], v[1][1] + _.v[1][0]);
		ret.v[1][1] = min(v[1][0] + _.v[0][1], v[1][1] + _.v[1][1]);
		return ret;//循环展开后的广义矩阵乘法
	}
} ans, before, after, g[100005];
struct Segment_Tree {//线段树维护转移矩阵
	matrix val[400005];
	int pos, L, R, l[400005], r[400005];
	#define lc (k << 1)
	#define rc ((k << 1) | 1)
	#define mid ((l[k] + r[k]) >> 1)
	void push_up(int k) {
		val[k] = val[lc] * val[rc];
	}
	void build(int k) {
		if(l[k] == r[k]) {
			val[k] = g[rnk[l[k]]];
			return;
		}
		l[lc] = l[k], r[lc] = mid, l[rc] = mid + 1, r[rc] = r[k];
		build(lc), build(rc);
		push_up(k);
	}
	void change(int k) {
		if(l[k] == r[k]) {
			val[k] = g[rnk[pos]];
			return;
		}
		if(pos <= mid) change(lc);
		else change(rc);
		push_up(k);
	}
	matrix ask(int k) {
		if(L <= l[k] && r[k] <= R) return val[k];
		matrix ret(0);
		if(L <= mid) ret = ret * ask(lc);
		if(R > mid) ret = ret * ask(rc);
		return ret;
	}
	void Change(int Pos) {
		pos = Pos;
		return change(1);
	}
	matrix Ask(int l, int r) {
		L = l, R = r;
		return ask(1);
	}
} tree;
//树链剖分
void dfs1(int now) {
	siz[now] = 1, dep[now] = dep[fa[now]] + 1;
	for(const auto& i : e[now]) {
		if(i != fa[now]) {
			fa[i] = now;
			dfs1(i);
			siz[now] += siz[i];
			if(siz[i] > siz[son[now]]) son[now] = i;
		}
	}
}
void dfs2(int now) {
	++cnt; dfn[now] = cnt, rnk[cnt] = now;
	if(now == son[fa[now]]) top[now] = top[fa[now]];
	else top[now] = now;
	if(son[now]) {
		dfs2(son[now]);
		bot[now] = bot[son[now]];
		f[now][0] += min(f[son[now]][0], f[son[now]][1] + 1);
		f[now][1] += min(f[son[now]][0] + 1, f[son[now]][1]);
	}
	else bot[now] = now;
	for(const auto& i : e[now]) {
		if(i != fa[now] && i != son[now]) {
			dfs2(i);
			f[now][0] += min(f[i][0], f[i][1] + 1);
			f[now][1] += min(f[i][0] + 1, f[i][1]);
			_g[now][0] += min(f[i][0], f[i][1] + 1);
			_g[now][1] += min(f[i][0] + 1, f[i][1]);
		}
	}
	g[now].v[0][0] = _g[now][0], g[now].v[0][1] = _g[now][0] + 1;
	g[now].v[1][0] = _g[now][1] + 1, g[now].v[1][1] = _g[now][1];
}
//修改转移矩阵
void change(int now, int val) {
	g[now].v[0][0] = _g[now][0], g[now].v[0][1] = _g[now][0] + 1;
	g[now].v[1][0] = _g[now][1] + 1, g[now].v[1][1] = _g[now][1];
	color[now] = val;
	if(color[now]) g[now].v[color[now] - 1][0] = g[now].v[color[now] - 1][1] = inf;//把不可能出现的一行设为inf
	while(now) {
		before = tree.Ask(dfn[top[now]], dfn[bot[now]]);
		tree.Change(dfn[now]);
		after = tree.Ask(dfn[top[now]], dfn[bot[now]]);
		now = fa[top[now]];
		add[0] = min(after.v[0][0], after.v[0][1]), sub[0] = min(before.v[0][0], before.v[0][1]);
		add[1] = min(after.v[1][0], after.v[1][1]), sub[1] = min(before.v[1][0], before.v[1][1]);
		_g[now][0] += min(add[0], add[1] + 1) - min(sub[0], sub[1] + 1), _g[now][1] += min(add[0] + 1, add[1]) - min(sub[0] + 1, sub[1]);
		g[now].v[0][0] = _g[now][0], g[now].v[0][1] = _g[now][0] + 1;
		g[now].v[1][0] = _g[now][1] + 1, g[now].v[1][1] = _g[now][1];
		if(color[now]) g[now].v[color[now] - 1][0] = g[now].v[color[now] - 1][1] = inf;//不可能出现的状态
	}
}
//下面就是交互了
void initialize(int N, std::vector<int> A, std::vector<int> B) {
	n = N;
	for(int i = 2; i <= n; ++i) {
		u = A[i - 2], v = B[i - 2];
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(1);
	dfs2(1);
	tree.l[1] = 1, tree.r[1] = n;
	tree.build(1);
}
int cat(int v) {
	change(v, 1);
	ans = tree.Ask(dfn[top[1]], dfn[bot[1]]);
	return min(min(ans.v[0][0], ans.v[0][1]), min(ans.v[1][0], ans.v[1][1]));
}
int dog(int v) {
	change(v, 2);
	ans = tree.Ask(dfn[top[1]], dfn[bot[1]]);
	return min(min(ans.v[0][0], ans.v[0][1]), min(ans.v[1][0], ans.v[1][1]));
}
int neighbor(int v) {
	change(v, 0);
	ans = tree.Ask(dfn[top[1]], dfn[bot[1]]);
	return min(min(ans.v[0][0], ans.v[0][1]), min(ans.v[1][0], ans.v[1][1]));
}
```

---

## 作者：ZLCT (赞：0)

# [JOI Open 2018] 猫或狗
## 题目翻译
~~没有猫狗的舞会~~\
给定一棵树，不断在节点上添加/删除一只猫/狗，每次操作后回答此时若想使得任意一对猫狗不在同一个连通块中至少需要断开几条边。
## solution
动态 dp 当然要用动态树写了。\
如果不会动态 dp 其实也没关系，我觉得会 LCT 你就肯定会动态 dp 了。
### step 1 normal dp
我们先不考虑动态，思考一下一次操作如何计算答案。\
这是一个比较经典的树形 dp，我们可以设 $f_{u,0/1/2}$ 表示点 $u$ 子树最终连通块中 **什么也不剩/只剩下猫/只剩下狗** 所需删除最少的边数。\
但是此时我们会有一种情况不好考虑，若一个点的子树中没有猫/狗，那我们理论上还需要将 $f_{u,1/2}$ 的初始值设为 $\infty$。\
但是我们发现我们可以将状态设为 $f_{u,0/1/2}$ 表示点 $u$ 子树最终连通块中 **什么也不剩/最多只剩下猫/最多只剩下狗** 所需删除最少的边数。\
这样很显然不会影响我们的转移，因为若剩下子树中无猫/狗，则说明 $f_{u,1/2}=f_{u,0}$，则我们可以认为转移时都从 $f_{u,0}$ 转移而来。\
那我们就会有以下转移：
$$
f_{u,0}=\sum\limits_{v\in son_u}\min(f_{v,0},f_{v,1}+1,f_{v,2}+1)
$$
$$
f_{u,1}=\sum\limits_{v\in son_u}\min(f_{v,0},f_{v,1},f_{v,2}+1)
$$
$$
f_{u,2}=\sum\limits_{v\in son_u}\min(f_{v,0},f_{v,1}+1,f_{v,2})
$$
但是注意若点 $u$ 处为猫/狗，则 $f_{u,2/1}$ 应为 $\infty$，因为不可能满足状态定义的条件。\
于是我们就完成了一次答案的计算。\
我们考虑把它放进 LCT 当中。
### step 2 dp onto LCT
显然这个题需要维护子树信息，所以我们需要维护虚儿子的信息。\
你会发现这个题虚儿子的信息十分容易维护。\
由于 LCT 的虚边都是原树的边，所以我们可以按照朴素 dp 的转移进行转移。\
我们设 $fi_{u,0/1/2}$ 表示 $u$ 的虚子树 ***包括点 $u$*** 中的 dp 值，然后不难发现这满足可加性（前面转移都是求和，肯定满足可加性了）。\
那么我们只需要在实变虚时将 $f_{v}$ 的贡献按照上面的转移贡献到 $fi_{fa_v}$ 即可，当然不要忘了虚边实时将贡献减去。
### step 3 chain son
这里的 chain son 代表实儿子，但是实儿子在树上不是真实的儿子，这个如果翻译成 real son 就很逆天。\
这道题难点就在对于实链的处理比较麻烦，因为这道题需要按照深度依次 dp，所以我们不能只和求 $sum,max$ 一样简单地考虑左右实儿子进行 dp。\
那么这时候我们就需要一个可以在 dp 时保留 dp 顺序的东西。
### step 4 matrix with dp
我们知道矩阵是一个好东西，因为它没有交换律，所以我们可以通过左乘右乘来使得其保持运算顺序不变。\
首先根据 LCT 的性质，每个实边连接的树都表示一条原树上的链，所以我们可以保证其深度一定互不相同。\
接下来根据二叉搜索树的性质，每个点的左子树中的节点都比它深度浅，每个点的右子树中的节点都比它深度大，于是我们若将 $f,fi$ 都用矩阵表示出来，分别为 $F,G$，则转移就可以写成：
$$
F_u=F_{lson_u}\otimes G_{u}\otimes F_{rson_u}
$$
其中 $f$ 的矩阵既然为答案矩阵，我们就需要先确定它：
$$
F_u=\begin{bmatrix}f_{u,0} \\ f_{u,1} \\ f_{u,2}\end{bmatrix}
$$
那么根据最开始的转移方程我们可以写出对应 $fi$ 的方程形式
$$
G_u=\begin{bmatrix}fi_{u,0} & fi_{u,0}+1 & fi_{u,0}+1 \\ fi_{u,1} & fi_{u,1} & fi_{u,1}+1 \\ fi_{u,2} & fi_{u,2}+1 & fi_{u,2}\end{bmatrix}
$$
那根据一开始转移时强调的，若点 $u$ 本身有猫/狗，则要把对应的另一项的 $F,G$ 值处理成 $\infty$。\
注意这里因为以后可能会将该点的猫/狗拿掉，所以这里处理 $\infty$ 时要加上一个 $\infty$ 而不是赋值。
## 总结
其实你会发现动态 dp 没有什么高深的东西，如果从 LCT 角度理解，仅仅是通过矩阵来限定转移的顺序，这个点在许多 LCT 的题目中也是一种十分实用的技巧。\
注：若你在 LOJ 上提交，引用 `catdog.h` 时要用 `#include "catdog.h"`
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e8+7;
int read(){
    int res=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
    return f*res;
}
void print(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)print(x/10);
    putchar((x%10)^48);
}
struct matrix{
    int g[3][3];
    void output(){
        cout<<"\n_______________\n";
        for(int i=0;i<3;++i,putchar('\n')){
            for(int j=0;j<3;++j,putchar(' ')){
                cout<<g[i][j];
            }
        }
        cout<<"__________________\n";
    }
    friend matrix operator *(matrix &A,matrix &B){
        matrix res;
        res.g[0][0]=min({A.g[0][0]+B.g[0][0],A.g[0][1]+B.g[1][0],A.g[0][2]+B.g[2][0]});
        res.g[0][1]=min({A.g[0][0]+B.g[0][1],A.g[0][1]+B.g[1][1],A.g[0][2]+B.g[2][1]});
        res.g[0][2]=min({A.g[0][0]+B.g[0][2],A.g[0][1]+B.g[1][2],A.g[0][2]+B.g[2][2]});
        res.g[1][0]=min({A.g[1][0]+B.g[0][0],A.g[1][1]+B.g[1][0],A.g[1][2]+B.g[2][0]});
        res.g[1][1]=min({A.g[1][0]+B.g[0][1],A.g[1][1]+B.g[1][1],A.g[1][2]+B.g[2][1]});
        res.g[1][2]=min({A.g[1][0]+B.g[0][2],A.g[1][1]+B.g[1][2],A.g[1][2]+B.g[2][2]});
        res.g[2][0]=min({A.g[2][0]+B.g[0][0],A.g[2][1]+B.g[1][0],A.g[2][2]+B.g[2][0]});
        res.g[2][1]=min({A.g[2][0]+B.g[0][1],A.g[2][1]+B.g[1][1],A.g[2][2]+B.g[2][1]});
        res.g[2][2]=min({A.g[2][0]+B.g[0][2],A.g[2][1]+B.g[1][2],A.g[2][2]+B.g[2][2]});
        return res;
//        vector<pair<pair<int,int>,pair<int,int> > >vec[3][3];
//        for(int k=0;k<3;++k){
//            for(int i=0;i<3;++i){
//                for(int j=0;j<3;++j){
//                    vec[i][j].push_back({{i,k},{k,j}});
//                }
//            }
//        }
//        for(int i=0;i<3;++i){
//            for(int j=0;j<3;++j){
//                printf("res.g[%d][%d]=min({A.g[%d][%d]+B.g[%d][%d],A.g[%d][%d]+B.g[%d][%d],A.g[%d][%d]+B.g[%d][%d]});\n",i,j,vec[i][j][0].first.first,vec[i][j][0].first.second,vec[i][j][0].second.first,vec[i][j][0].second.second,vec[i][j][1].first.first,vec[i][j][1].first.second,vec[i][j][1].second.first,vec[i][j][1].second.second,vec[i][j][2].first.first,vec[i][j][2].first.second,vec[i][j][2].second.first,vec[i][j][2].second.second);
//            }
//        }
//        return res;
    }
};
const int N=1e5+666;
struct node{
    int son[2],fa;
    matrix f,fi;
}tr[N];
int col[N];
bool notroot(int x){
    return tr[tr[x].fa].son[0]==x||tr[tr[x].fa].son[1]==x;
}
void pushup(int x){
    tr[x].f=tr[x].fi;
    if(tr[x].son[0])tr[x].f=tr[tr[x].son[0]].f*tr[x].f;
    if(tr[x].son[1])tr[x].f=tr[x].f*tr[tr[x].son[1]].f;
}
void rotate(int x){
    int y=tr[x].fa,z=tr[y].fa;
    int k=tr[y].son[1]==x;
    if(notroot(y)){
        tr[z].son[tr[z].son[1]==y]=x;
    }
    tr[x].fa=z;
    tr[y].son[k]=tr[x].son[k^1];
    tr[tr[x].son[k^1]].fa=y;
    tr[x].son[k^1]=y;
    tr[y].fa=x;
    pushup(y);
    pushup(x);
}
void splay(int x){
    while(notroot(x)){
        int y=tr[x].fa,z=tr[y].fa;
        if(notroot(y))rotate((tr[y].son[1]==x)^(tr[z].son[1]==y)?x:y);
        rotate(x);
    }
}
void access(int x){
    for(int y=0;x;x=tr[x].fa){
        splay(x);
        if(y){
            tr[x].fi.g[0][0]-=min({tr[y].f.g[0][0],tr[y].f.g[1][0]+1,tr[y].f.g[2][0]+1});
            tr[x].fi.g[1][1]-=min({tr[y].f.g[0][0],tr[y].f.g[1][0],tr[y].f.g[2][0]+1});
            tr[x].fi.g[2][2]-=min({tr[y].f.g[0][0],tr[y].f.g[1][0]+1,tr[y].f.g[2][0]});
            tr[x].fi.g[0][1]=tr[x].fi.g[0][2]=tr[x].fi.g[0][0]+1;
            tr[x].fi.g[1][0]=tr[x].fi.g[1][1];tr[x].fi.g[1][2]=tr[x].fi.g[1][1]+1;
            tr[x].fi.g[2][0]=tr[x].fi.g[2][2];tr[x].fi.g[2][1]=tr[x].fi.g[2][2]+1;
        }
        if(tr[x].son[1]){
//            cout<<"("<<x<<','<<tr[x].son[1]<<")\n";
//            tr[tr[x].son[1]].f.output();tr[x].fi.output();
            tr[x].fi.g[0][0]+=min({tr[tr[x].son[1]].f.g[0][0],tr[tr[x].son[1]].f.g[1][0]+1,tr[tr[x].son[1]].f.g[2][0]+1});
            tr[x].fi.g[1][1]+=min({tr[tr[x].son[1]].f.g[0][0],tr[tr[x].son[1]].f.g[1][0],tr[tr[x].son[1]].f.g[2][0]+1});
            tr[x].fi.g[2][2]+=min({tr[tr[x].son[1]].f.g[0][0],tr[tr[x].son[1]].f.g[1][0]+1,tr[tr[x].son[1]].f.g[2][0]});
            tr[x].fi.g[0][1]=tr[x].fi.g[0][2]=tr[x].fi.g[0][0]+1;
            tr[x].fi.g[1][0]=tr[x].fi.g[1][1];tr[x].fi.g[1][2]=tr[x].fi.g[1][1]+1;
            tr[x].fi.g[2][0]=tr[x].fi.g[2][2];tr[x].fi.g[2][1]=tr[x].fi.g[2][2]+1;
//            tr[x].fi.output();
        }
        tr[x].son[1]=y;
        pushup(x);
        y=x;
    }
}
vector<int>G[N];
void dfs(int u,int fa){
    tr[u].fi.g[0][1]=tr[u].fi.g[0][2]=tr[u].fi.g[1][2]=tr[u].fi.g[2][1]=1;
    tr[u].f=tr[u].fi;
    for(int v:G[u]){
        if(v==fa)continue;
        tr[v].fa=u;
        dfs(v,u);
    }
}
void initialize(int n,vector<int>A,vector<int>B){
    for(int i=0;i<n-1;++i){
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }
    dfs(1,1);
}
void printlink(int x){
    if(tr[x].son[0])printlink(tr[x].son[0]);
    cout<<x<<' ';
    if(tr[x].son[1])printlink(tr[x].son[1]);
}
void debug(int x){
    cout<<"\n???";printlink(x);cout<<"???\n";
    tr[1].fi.output();tr[2].fi.output();tr[3].fi.output();
}
int cat(int x){
    access(x);
    splay(x);
    col[x]=1;
    tr[x].fi.g[0][0]+=inf;
    tr[x].fi.g[2][2]+=inf;
    tr[x].fi.g[0][1]=tr[x].fi.g[0][2]=tr[x].fi.g[0][0]+1;
    tr[x].fi.g[2][0]=tr[x].fi.g[2][2];tr[x].fi.g[2][1]=tr[x].fi.g[2][2]+1;
    pushup(x);
//    debug(x);
    return min({tr[x].f.g[0][0],tr[x].f.g[1][0],tr[x].f.g[2][0]});
}
int dog(int x){
    access(x);
    splay(x);
    col[x]=2;
    tr[x].fi.g[0][0]+=inf;
    tr[x].fi.g[1][1]+=inf;
    tr[x].fi.g[0][1]=tr[x].fi.g[0][2]=tr[x].fi.g[0][0];
    tr[x].fi.g[1][0]=tr[x].fi.g[1][1];tr[x].fi.g[1][2]=tr[x].fi.g[1][1]+1;
    pushup(x);
//    debug(x);
    return min({tr[x].f.g[0][0],tr[x].f.g[1][0],tr[x].f.g[2][0]});
}
int neighbor(int x){
    access(x);
    splay(x);
    if(col[x]==1){
        tr[x].fi.g[0][0]-=inf;
        tr[x].fi.g[2][2]-=inf;
        tr[x].fi.g[0][1]=tr[x].fi.g[0][2]=tr[x].fi.g[0][0]+1;
        tr[x].fi.g[2][0]=tr[x].fi.g[2][2];tr[x].fi.g[2][1]=tr[x].fi.g[2][2]+1;
    }else{
        tr[x].fi.g[0][0]-=inf;
        tr[x].fi.g[1][1]-=inf;
        tr[x].fi.g[0][1]=tr[x].fi.g[0][2]=tr[x].fi.g[0][0];
        tr[x].fi.g[1][0]=tr[x].fi.g[1][1];tr[x].fi.g[1][2]=tr[x].fi.g[1][1]+1;
    }
    col[x]=0;
    pushup(x);
//    debug(x);
    return min({tr[x].f.g[0][0],tr[x].f.g[1][0],tr[x].f.g[2][0]});
}
```

---

