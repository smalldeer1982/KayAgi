# [ARC083E] Bichrome Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc083/tasks/arc083_c

$ N $ 頂点からなる木があります。頂点 $ 1 $ は木の根であり、頂点 $ i $ ($ 2\ ≦\ i\ ≦\ N $) の親は頂点 $ P_i $ です。

すぬけ君は、この木の各頂点に白または黒の色と非負整数の重みを割り当てることにしました。

すぬけ君にはお気に入りの数列 $ X_1,\ X_2,\ ...,\ X_N $ があります。そこで、色および重みの割り当てが、すべての $ v $ について以下の条件を満たすようにしたいと考えました。

- 頂点 $ v $ を根とする部分木に含まれる頂点のうち、頂点 $ v $ と同じ色であるものの重みの和は $ X_v $ である。

ここで、頂点 $ v $ を根とする部分木とは、頂点 $ v $ およびそのすべての子孫からなる木を指すものとします。

このような色および重みの割り当てが可能かどうか判定してください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 1,000 $
- $ 1\ ≦\ P_i\ ≦\ i\ -\ 1 $
- $ 0\ ≦\ X_i\ ≦\ 5,000 $

### Sample Explanation 1

たとえば、以下のような色と重みの割り当ては条件を満たします。 - 頂点 $ 1 $ の色を白、重みを $ 2 $ とする。 - 頂点 $ 2 $ の色を黒、重みを $ 3 $ とする。 - 頂点 $ 3 $ の色を白、重みを $ 2 $ とする。 他にも条件を満たす割り当て方は存在します。

### Sample Explanation 2

頂点 $ 2 $ と頂点 $ 3 $ に同じ色を割り当てる場合、頂点 $ 2 $ に非負の重みを割り当てることができません。 頂点 $ 2 $ と頂点 $ 3 $ に異なる色を割り当てる場合、頂点 $ 1 $ にどちらの色を割り当てても、非負の重みを割り当てることができません。 よって、条件を満たす色および重みの割り当て方は存在しません。

## 样例 #1

### 输入

```
3
1 1
4 3 2```

### 输出

```
POSSIBLE```

## 样例 #2

### 输入

```
3
1 2
1 2 3```

### 输出

```
IMPOSSIBLE```

## 样例 #3

### 输入

```
8
1 1 1 3 4 5 5
4 1 6 2 2 1 3 3```

### 输出

```
POSSIBLE```

## 样例 #4

### 输入

```
1

0```

### 输出

```
POSSIBLE```

# 题解

## 作者：ix35 (赞：11)

#### **题目分析：（贪心+树形DP）**

首先要明确的是三件事：

1. 当某一个子树中染色方案和权值方案都确定以后，对于其祖先结点的子树造成的影响仅仅是两种颜色的权值和，而不关心其具体方案，因为对于它的父结点来说，这个子树是一个整体。
2. 显然将一个子树中所有结点黑白倒置，仍然满足要求；因此我们在处理上一条中提到的权值和时不必关心具体是哪种颜色的权值和。也就是说，不必知道到底是“黑色”还是“白色”的权值和，而只要知道是“两种不同颜色”的权值和。
3. 基于上面一条，我们在处理某一个子树时，可以假设它的根节点染黑色。因为如果根节点染白色，只需将这个子树上所有结点黑白倒置即可转换成黑色。同时，根节点的每一个子节点所对应子树中两种颜色当然也是可以交换的。

这就是我们分析的基础了。刚看到题目中给的条件可能还不太有头绪，即使有了上面的几条基本“规则”也难以继续做下去，所以我们还需要一个能够具体执行的染色和赋权法则。

**贪心策略：（假设将某个子树的根节点染成黑色）则这颗子树中黑色结点的权值和应当恰好等于$V_ x$，而白色结点的权值和应尽量小。**

证明：黑色结点权值和等于$V_x$应该没有什么问题，根据上面的黑白倒置理论，黑色或白色权和等于$V_x$是等价的。

- 白色结点的权值和尽量小也很容易理解：因为假如存在一种白色结点权值和更大的情况能够使整颗树满足要求，则我们一定可以给予这个子树根节点的父节点一个权值使得以父节点为根的更大的子树也满足要求，此时对于白色结点权值和小的情况，我们只要增大父节点的权值，就一定能够达到相同的效果。反之，如果权和较小是满足条件，则当权值增大时，有可能会超出父节点的$V$值，从而不能给它的父节点分配一个非负整数权值。

这就是我们染色和赋权的具体方案了。下面就要考虑具体如何实现的问题。

采用树形DP的递归实现。我们用$f[i]$表示以$i$为根的子树中白色结点的最小权值和。我们进行一次DFS，假设某结点$x$的所有子结点的$dp$值已经算出，并假设这个结点染黑色，那么对于每个子树$i$来说有两种决策：

1. 将这个子树的根节点染黑，则整棵树的黑权和增加$V_i$，整棵树的白权和增加$ f[i]$；
2. 将这个子树的根节点染白（黑白倒置），则整棵树的黑权和增加$f[i]$，白权和增加$V_i$。

同时考虑到这个节点自身染黑，而且权值可以是任意一个非负整数，所以只要每个子树统计完后黑权和不超过$V_x$即可（少的可以直接通过根节点加），所以我们要求的实际上就是：在黑权和不超过$V_x$的情况下，使白权和最小。这其实是类似于01背包的问题，题目中给出的最大$V_x$不大，因此可以使用背包问题的方法求解，这里只是每两个物品中必须选一个的背包，要求可行的最大值（因为黑权和最大代表白权和最小）。

下面代码中用$f[i]$指树形dp中的数组，$dp[i]$代表背包中的dp数组。

算法时间复杂度为$O(\sum \limits_{i=1}^nV_i)=O(NV)$。

------

#### **程序：**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1010;
int n,fa[MAXN],v[MAXN],dp[5*MAXN],f[MAXN];
vector <int> p[1010];
void dfs (int x) {
	for (int ii=0;ii<p[x].size();ii++) {
		dfs(p[x][ii]);
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for (int ii=0;ii<p[x].size();ii++) {
		int k=p[x][ii];
		for (int i=v[x];i>=0;i--) {
			int tmp=0x3f3f3f3f;
			if (i>=v[k]) {
				tmp=min(tmp,dp[i-v[k]]+f[k]);
			}
			if (i>=f[k]) {
				tmp=min(tmp,dp[i-f[k]]+v[k]);
			}
			dp[i]=tmp;
		}
	}
	for (int i=v[x];i>=0;i--) {
		f[x]=min(f[x],dp[i]);
	}
	return;
}
int main () {
	memset(f,0x3f,sizeof(f));
	scanf("%d",&n);
	for (int i=2;i<=n;i++) {
		scanf("%d",&fa[i]);
		p[fa[i]].push_back(i);
	}
	for (int i=1;i<=n;i++) {
		scanf("%d",&v[i]);
	}
	dfs(1);
	if (f[1]<0x3f3f3f3f) {
		printf("POSSIBLE\n");
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
```

---

## 作者：Kinandra (赞：2)

标签:构造

假设有可行的方案, 我们尝试构造出来.

设 $w_u$ 为 $u$ 的权值, $y_u$ 表示 $u$ **子树内与 $u$ 颜色不同的点** 的权值和. 则 $x_u+y_u=\sum_{v\in T_u}w_u$, 其中 $T_u$ 表示 $u$ 的子树的点集.

考虑 $x_u$ 如何从儿子节点 $v$ 转移, 容易得到 $x_u=w_u+\sum_{c_u=c_v}x_v+\sum_{c_u\neq c_v}y_v$, 其中 $c_u$ 表示 $u$ 的颜色. 因为 $w_u$ 是一个任意决定的非负整数, 并且其取值只影响 $x_u$, 不影响 $y_u$, 所以我们可以先确定儿子节点 $v$ 对 $u$ 的贡献是 $x$ 还是 $y$, 最后的调整 $w_u$ 使得方案合法.

发现一个点对于其父亲的影响全部可以用 $x$ 和 $y$ 来体现, 容易体会到 $y$ 越小越优, 所以我们利用拓扑序(或递归)求出每一个点 $y$ 的最小值, 在求的过程中判断是否有解就好了.

具体的, 对于叶子结点, $y=0$; 对于非叶子节点我们可以用背包来求 $y$, 详细可以看代码.

时间复杂度 $\mathcal O(nx)$.

```cpp
#include <bits/stdc++.h>
#define inf 1000000000
using namespace std;
int read();
int n;
queue<int> q;
int fa[1003], deg[1003], x[1003], y[1003];
int f[1003][5003];
void insert(int u) { return --deg[u] ? void() : q.push(u); }

void update(int u, int a, int b) {
    for (int i = x[u]; i >= 0; --i) {
        if (i >= b)
            f[u][i] = min(f[u][i - a] + b, f[u][i - b] + a);
        else if (i < a)
            f[u][i] = inf;
        else
            f[u][i] = f[u][i - a] + b;
    }
}

int main() {
    n = read();
    for (int i = 2; i <= n; ++i) deg[fa[i] = read()]++;
    for (int i = 1; i <= n; ++i) x[i] = read();
    for (int i = 1; i <= n; ++i) deg[i] ? void() : q.push(i);
    while (!q.empty()) {
        int u = q.front(), v = fa[u];
        q.pop(), insert(v);
        if ((y[u] = f[u][x[u]]) >= inf) return puts("IMPOSSIBLE"), 0;
        if (!v) break;
        if (x[u] > y[u]) swap(x[u], y[u]);
        y[u] = min(y[u], inf);
        update(v, x[u], y[u]);
    }
    puts("POSSIBLE");
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

```

---

## 作者：irris (赞：2)

> 贪心 / 背包

因为我们可以任意设置点 $u$ 的权值，因此无论如何贪心让所有值最小是最优的选择。

设 $c_u$ 表示 $u$ 子树内与点 $u$ 异色点的权值和最小值，我们要尽可能最小化 $c_u$。

边界，$c_{\text{leaf}} = 0$。

转移：对于 $u$ 的所有儿子 $v_1\dots v_m$，做大小为 $X_u$ 的分组背包，其中第 $i$ 组包含两个元素 $\langle X_{v_i}, c_{v_i}\rangle\langle c_{v_i}, X_{v_i}\rangle$（分别代表同色和异色），第一维为大小，第二维为权值。统计背包的各项最小值就得到了 $c_u$。

时间复杂度 $\mathcal O(nX)$。

---

## 作者：huangrenheluogu (赞：1)

# ARC083E

AtCoder 中的 [题目](https://atcoder.jp/contests/arc083/tasks/arc083_c)。

对于每个节点，枚举黑白，然后判断即可，复杂度 $O(2^n\times n)$，（暴力）讲完了。

下面进入正文。

记给每个点的权值为 $w_i(w_i\ge 0)$，每个节点的颜色为 $col_i$，$col_i=1$ 表示黑色，$col_i=0$ 表示白色。

发现一个性质：**一个子树内黑白节点可以完全变换，而这是对方案没有影响的。**

就是说，一个子树内，黑的变成白的，白的变成黑的，对于每个节点 $x$，由于 $x$ 和它子树内的节点颜色一起变换，所以仍然满足 $X_i=\sum\limits_{j,col_j=col_i,j\in subtree_i}w_j$，其中，$subtree_x$ 表示 $x$ 的子树节点。

所以，**我们只需要考虑每个节点 $x$ 与 $x$ 颜色不同节点权值总和即可。**

发现一个贪心：下面取得越少越好，发现由于 $w_x$ 是可以任取的，所以另一个的值越少会让父节点更容易满足。如果不足，可以用 $w_x$ 不足；如果同种颜色的可以再塞下一个，那就赚了。

于是，题目转化为背包。

记 $f_{x,j}$ 表示 $x$ 节点和 $x$ 相同颜色总和为 $j$ 的最小值。

转移就是背包，代价不大于 $j$ 的情况下，最小化 $f_{x,j}$。

经典的零一背包问题。

但是注意这里是分 $X_x$ 和 $g_{son_i}$，其中 $g_{son_i}$ 表示 $\min\{f_{son_i,j}\},0\le j\le X_{son_i}$。

代码中，我令 $f_{x,X_x}=g_x$。

如果可行，就是 `POSSIBLE`。

如有一个节点不行，就是 `IMPOSSIBLE`。

下面放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int x, n, a[N], fir[N], nxt[N], son[N], tot, f[N][N * 5], inf = 1e9, tem;
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void dfs(int x){
	for(int i = 0; i <= a[x]; i++) f[x][i] = inf;
	f[x][0] = 0;
	for(int i = fir[x]; i ; i = nxt[i]){
		dfs(son[i]);
		for(int j = a[x]; j >= 0; j--){
			tem = inf;
			if(j >= a[son[i]]) tem = min(tem, f[x][j - a[son[i]]] + f[son[i]][a[son[i]]]);
			if(j >= f[son[i]][a[son[i]]]) tem = min(tem, f[x][j - f[son[i]][a[son[i]]]] + a[son[i]]);
			f[x][j] = tem;
		}
	}
	for(int i = 1; i <= a[x]; i++) f[x][i] = min(f[x][i], f[x][i - 1]);
	if(f[x][a[x]] == inf){
		printf("IMPOSSIBLE");
		exit(0);
	}
}
int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		scanf("%d", &x);
		add(x, i);
	}
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1);
	printf("POSSIBLE");
	return 0;
} 
```

---

## 作者：Sol1 (赞：1)

校内模拟赛考了这道题，结果状态对了方程推错了……

我是 sb 石锤。

首先，这个问题有 $4$ 个维度：

1. $i$ 节点；
1. 子树内白点的权值和 $w_0$；
1. 子树内黑点的权值和 $w_1$；
1. 自己染成黑色还是白色 $c$。

直接利用这个来 DP 应该会有一个 $O(nX^4)$ 的优秀复杂度。

但是我们发现现在这个状态有一维是不需要记的，因为根据题目要求，有 $w_c=X_i$。

于是降到 $3$ 维：

1. $i$ 节点；
1. 自己染成黑色还是白色 $c$。
1. 子树内另外一个颜色的点的权值和 $w_{1-c}$。

利用这个来 DP 会有一个 $O(nX^2)$ 的优秀复杂度。

考虑继续优化，因为上界是 $X$，且权值不能是负的，所以我们猜测可能需要让 $w_{1-c}$ 尽量小。

如何证明？

1. 最优性：如果有一个方案使得 $w_{1-c}$ 不是最小的，那么将这个子树内方案修改为使得 $w_{1-c}$ 最小，并增大颜色为 $1-c$ 的祖先的权值，一定能构造出另外一个方案。
2. 可行性：~~你都 DP 出来了当然可行。~~

所以问题变为一个 $2$ 维的最优化问题：

1. $i$ 节点；
1. 自己染成黑色还是白色 $c$。
1. 最小化子树内另外一个颜色的点的权值和 $w_{1-c}$。

然后就得到状态：设 $f_{i,c}$ 表示 $i$ 节点，自己染成 $c$ 颜色，子树内 $1-c$ 的颜色的权值和最小是多少。

但是这时转移好像没有那么简单。

考虑一个类似于 0/1 背包的转移。

设 $g_{c,i}$ 表示 $c$ 颜色权值和为 $i$ 时，$1-c$ 颜色的权值和最小多少。

考虑加入一个点 $v$ 时的转移。

枚举点 $u$ 和点 $v$ 的颜色。如果是 $0,0$，有转移：

$$g_{0,j}\leftarrow g_{0,j-X_v}+f_{v,0}$$

$0,1$，有转移：

$$g_{0,j}\leftarrow g_{0,j-f_{v,1}}+X_v$$

$1,0$，有转移：

$$g_{1,j}\leftarrow g_{1,j-f_{v,0}}+X_v$$

$1,1$，有转移：

$$g_{1,j}\leftarrow g_{1,j-X_v}+f_{v,1}$$

合并回 $f$ 的时候，就直接枚举 $i$ 节点的权值就行了：

$$f_{i,j}=\min_{k=0}^{X_i}g_{j,k}$$

总时间复杂度为 $O(nX)$，可以通过本题。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[(1 << 21) + 5], *p1 = buf, *p2 = buf;

inline int qread() {
	char c = getchar();
	int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
int n, hd[1005], pnt, x[1005], dp[1005][2], col[1005], siz[1005][2];
Edge e[2005];

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread();
	for (int i = 2;i <= n;i++) {
		int fa = qread();
		AddEdge(fa, i);
	}
	for (int i = 1;i <= n;i++) x[i] = qread();
}

inline void Dfs(int u) {
	if (!~hd[u]) {
		dp[u][0] = dp[u][1] = 0;
		return;
	}
	int f[2][5005], g[2][5005];
	memset(f, 0x3f, sizeof(f));
	f[0][0] = f[1][0] = 0;
	for (int i = hd[u];~i;i = e[i].nxt) {
		Dfs(e[i].to);
		memset(g, 0x3f, sizeof(g));
		for (int j = x[u];j >= 0;j--) {
			if (x[e[i].to] <= j) {
				g[0][j] = min(g[0][j], f[0][j - x[e[i].to]] + dp[e[i].to][0]);
				g[1][j] = min(g[1][j], f[1][j - x[e[i].to]] + dp[e[i].to][1]);
			}
			if (dp[e[i].to][1] <= j) g[0][j] = min(g[0][j], f[0][j - dp[e[i].to][1]] + x[e[i].to]);
			if (dp[e[i].to][0] <= j) g[1][j] = min(g[1][j], f[1][j - dp[e[i].to][0]] + x[e[i].to]);
		}
		memcpy(f, g, sizeof(f));
	}
	dp[u][0] = dp[u][1] = 0x3f3f3f3f;
	//printf("u=%d:\n", u);
	for (int i = 0;i <= x[u];i++) {
		//printf("%d ", f[0][i]);
		dp[u][0] = min(dp[u][0], f[0][i]);
		dp[u][1] = min(dp[u][1], f[1][i]);
	}
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	Dfs(1);
	if (dp[1][0] == 0x3f3f3f3f && dp[1][1] == 0x3f3f3f3f) puts("IMPOSSIBLE");
	else puts("POSSIBLE");
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

小清新题。

一棵子树对外界的影响只关注其黑、白权值之和。考虑 $u$ 子树，令 $u$ 为黑色，那么黑点权值确定，不难发现白点权值应当尽量小，因为本题只需满足点权非负即可，所以白点权值较大的方案一定可以通过将权值移到 $u$ 父亲的方式转化为权值和较小的方案。

那么进行树形 dp，目标是 $u$ 子树黑点权值和为 $X_u$ 且白点权值尽量小，$u$ 权值随意所以令其它黑点权值和 $\le X_u$ 即可。所以有状态 $f_{u,i}$ 表示 $u$ 子树黑点权值为 $i$ 时白点权值和最小是多少。

考虑转移，记 $g$ 为 $f_u$ 的滚动数组，新增 $v$ 子树那么分类讨论 $v$ 的颜色（是否和 $u$ 一样即可）：

1. 均为黑色：$f_{u,i+X_v}\gets g_i+f_{v,X_v}$。
2. 为白色：$f_{u,f_{v,X_v}}\gets g_i+X_v$。

读者可以结合贪心结论和 dp 转移来加深理解，其实本质是一样的：为了使第二种转移中尽量不越界，所以肯定要白点权值尽量小。

最后判断 $f_{1,X_1}$ 是否有值，复杂度 $O(nV)$。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MIN(a, b) a = min(a, b)
const int N = 1e3 + 5, M = 5e3 + 5, inf = 1e7;
int n, pa, a[N], f[N][M], g[M];
vector<int> to[N];

inline void dfs(int u){
	for(int i = 0; i <= a[u]; ++i) f[u][i] = 0;
	for(auto v : to[u]){
		dfs(v);
		for(int i = 0; i <= a[u]; ++i) g[i] = f[u][i], f[u][i] = inf;
 		for(int i = 0; i <= a[u]; ++i){
			if(i + a[v] <= a[u]) MIN(f[u][i + a[v]], g[i] + f[v][a[v]]);
			if(i + f[v][a[v]] <= a[u]) MIN(f[u][i + f[v][a[v]]], g[i] + a[v]);
		}
	}
}
signed main(){
	cin >> n;
	for(int i = 2; i <= n; ++i) scanf("%lld", &pa), to[pa].push_back(i);
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	dfs(1);
	if(f[1][a[1]] < inf) puts("POSSIBLE");
	else puts("IMPOSSIBLE");
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

容易想到的一种转移为 $f_{n,sum,col}$ 表示 $n$ 的子树在颜色为 $col$ 时且大小为 $sum$ 时是否可能。考虑优化。

注意到 $col$ 一维可以省略，因为一个点是黑色还是白色并不重要，重要的是它和子树中的某些点同色还是异色。我们在转移到某个状态的时候，考虑这样一种情况：当前点（称之为 $u$ ）为黑色时 $f$ 为 $1$ 。考虑把 $u$ 的子树的颜色全部翻转，那么 $u$ 为白色的时候情况是一样的， $f$ 也为 $1$ 。反之亦然。故 $col$ 一维没有必要。

下面考虑如何转移。

设 $f_n$ 表示 $n$ 的子树中，可能的同色点权总和有哪些。自下到上遍历这棵树。假设我们遍历到了点 $u$ 。

显然要让 $u$ 的子树中与其同色点的权值之和为 $x_u$ 。那么， $u$ 的儿子们与其同色点的权值之和一定小于等于 $x_u$ （因为树上的点权必须是非负整数）。为了给后面要遍历到的点更多空间，就要让 $u$ 尽量小，也就是让 $u$ 的儿子的子树中同色点的权值之和尽量大。

我们发现，同色点和异色点就像背包中的选和不选。对于点 $u$ ，我们可以选择一部分点与之同色，设它们的权值和为 $j$ ；也可以选择另一部分点与之同色，那么它们的权值和就是 $u$ 的子树大小（不包括 $u$ ）再减去 $j$ 。

为了方便，我们可以假设 $u$ 是黑色的。然后就可以计算 $u$ 子树中的同色节点权值总和（其实就是 $x_i$ ）和异色节点权值总和了（称之为 $w_i$ ）。那么如果 $u$ 的父亲是白色的，那么在考虑父亲节点 ${fa}_u$ 时，与 $u$ 异色的点就被考虑；反之亦然。这样就可以得到关于 $u$ 对父亲节点的贡献的式子，即 $f_{fa_u} \gets \{e+x_i|e\in f_{fa_u}\}\cup\{e+w_i|e\in f_{fa_u}\}$ 。用状态压缩表示集合即可。

代码就很简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,x[1024],w[1024],f[1024],s[1024];
bitset<8192>v[1024];
int main(){
	cin>>n;for(i=2;i<=n;i++)cin>>f[i];
	for(i=1;i<=n;v[i++]=1)cin>>x[i];
	for(i=n;i;i--){
		for(j=x[i];~j&&!v[i][j];j--);
		if(j<0){cout<<"IMPOSSIBLE";return 0;}
		s[f[i]]+=x[i]+(w[i]=s[i]-j);
		v[f[i]]=(v[f[i]]<<x[i])|(v[f[i]]<<w[i]);
	}cout<<"POSSIBLE";
	return 0;
}
```

---

## 作者：Dovish (赞：0)

## 题意
注意到 $x$ 的限制是对子树生效的，所以我们可以把子树看出一个整体而不关注其内部的构造。

如果你先摸了样例，你就会发现，问题的其实是在讨论与 $u$ 相连的点和 $u$ 的相对颜色关系。

我们记 $u$ 子树内和 $u$ 的颜色不一样的点权的最小情况为 $\text{dif}_u$，$c_u$ 为 $u$ 点的颜色（其实不用写出来，只是为了易于表示）。

仔细想一下，要求就是 $\sum_{c_u=c_v} x_v+\sum_{c_u\not=c_v} \text{dif}_v\le x_u$ 并且这时的 $\text{dif}_u$ 为 $\sum_{c_u\not=c_v} x_v+\sum_{c_u=c_v} \text{dif}_v$。

我们把 $x_u$ 看成背包总容积，于是问题变成了一个背包问题，要求每个物品必须选，但是要么把 $x_v$ 做体积， $\text{dif}_v$ 做价值，要么把 $\text{dif}_v$ 做体积， $x_v$ 做价值，要  容量为 $x_u$ 内的最小价值来更新 $\text{dif}_u$。

如果某个背包放不完就是非法方案了。

而这个背包的求法可以借鉴上下界网络流的做法：

1. 我们先把最小的求一次背包使得体积最小。

2. 然后把背包容量和这个东西做差，得到真正的背包容量。

3. 然后你把每一个物品的 $\max({x_u,\text{dif}_u})-\min({x_u,\text{dif}_u})$ 当**体积和价值**，做一次背包。

4. 然后第一次算出来的价值减去这次背包的答案就是 $\text{dif}_u$。

其实就是在满足背包容量的前提下尽可能的把“价值”换成“容量”。

（感谢伟大的 [Sin_Watt](https://www.luogu.com.cn/user/883464) 一下就秒了这个东西。）

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10,inf=1e9,mod=998244353;
int n,x[N],color[N],tf;
vector<int>e[N];
int f[N][N];
int dif[N]; 
void add(int u,int v)
{
	e[u].push_back(v);
}
void dfs(int u,int fa)
{
	int add=0,tag=0,res=0;
	if(!e[u].size())return;
	for(auto v:e[u])
	{
		dfs(v,u);
		add+=min(x[v],dif[v]); 
		res+=max(x[v],dif[v]); 
	}
	int base=x[u]-add;
	if(base<0)
	{
		tf=1;
		return;
	}
	dif[u]=inf;
	for(auto v:e[u])
	{
		for(int j=base;j>=0;j--)
		{
			int t=max(x[v],dif[v])-min(x[v],dif[v]);
			if(j-t>=0)
			f[u][j]=max(f[u][j],f[u][j-t]+t);
		}
	} 
	for(int j=0;j<=base;j++)
	{
		dif[u]=min(dif[u],res-f[u][j]);
		tag=1;
	}
	if(!tag)tf=1;
}
signed main()
{
	cin>>n;
	for(int i=2,fa;i<=n;i++)
	{
		cin>>fa;
		add(fa,i);
	}
	for(int i=1;i<=n;i++)cin>>x[i];
	dfs(1,0);
	if(tf)cout<<"IMPOSSIBLE";
	else cout<<"POSSIBLE";
}
```

---

## 作者：sunzz3183 (赞：0)

# P9663 [ARC083E] Bichrome Tree

## 题意

给定一棵根树，询问是否存在一组权值 $a$ 和黑白染色 $col$，使得

$$x_u=\sum_{v\in tree_u}[col_v=col_u]a_v$$

## 分析

发现**具体**颜色不重要，我们只关心相对颜色，因为将一个子树的黑白反转并不影响内部答案。

可以想到对于一棵树我们可以设 $f_{i,j,k}$ 为 $i$ 为根的子树，和 $i$ 颜色相同的权值为 $j$，不同的为 $k$，这种情况是否可行。

由于 $x_i$ 的限制，$j$ 只能等于它，所以直接设 $f_{i,j}$ 为 $i$ 为根的子树，和 $i$ 颜色相同的权值为 $x_i$，不同的为 $j$，这种情况是否可行。

此时可以直接跑树形背包，但是是 $O(n^3)$ 的，考虑优化：

可以发现，这是一个可行性动态规划，考虑转最优性动态规划。

发现 $j$ 显然**越小**越好，因为当 $j$ 小了的时候 $a_i$ 可以将自己的值变大，而当 $j$ 大了的时候，显然 $a_i$ 不能减小，所以现在状态变成了：

设 $f_{i}$ 为 $i$ 为根的子树，和 $i$ 颜色相同的权值为 $x_i$，不同的最少为 $f_i$。

此时，对于每个点，它的儿子取值就变成了要么是 $x_v$ 要么是 $f_v$，显然这是个背包问题。

设 $g_i$ 为相同的权值为 $i$ 时的最小不同权值，直接 $01$ 背包。

$$f_u=min_{0\leq i\leq x_u}\{g_i\}$$

最后判断是否有解，若 $f_u<\inf$（有符合的取值），则为有解，否则无解。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=1002,inf=0x3f3f3f3f3f3f3f3f;
struct edge{
    int nxt,v;
}ed[N<<1];
int en,first[N];
void add(int u,int v){
    ed[++en]={first[u],v};
    first[u]=en;
}
int n,x[N],f[N],g[N*5],h[N*5];
void dfs(int u,int fa){
    int sum=0;
    for(int i=first[u];i;i=ed[i].nxt)
        if(ed[i].v!=fa)
            dfs(ed[i].v,u),sum+=x[ed[i].v]+f[ed[i].v];
    g[0]=0;
    for(int i=first[u];i;i=ed[i].nxt)
        if(ed[i].v!=fa){
            for(int j=x[u];j>=x[ed[i].v];j--)
                h[j]=min(h[j],g[j-x[ed[i].v]]+f[ed[i].v]);//注意细节，不能直接使用 g 转移，否则就是把 x_v 和 f_v 看作了两个不同的物品
            for(int j=x[u];j>=f[ed[i].v];j--)
                h[j]=min(h[j],g[j-f[ed[i].v]]+x[ed[i].v]);
            for(int j=x[u];j>=0;--j)
                g[j]=h[j],h[j]=inf;
        }
    for(int i=0;i<=x[u];i++)
        f[u]=min(f[u],g[i]),g[i]=inf;
    return;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n=read();
    memset(f,0x3f,sizeof(f));
    memset(h,0x3f,sizeof(h));
    memset(g,0x3f,sizeof(g));
    for(int i=2;i<=n;i++){
        int u=read();
        add(u,i);add(i,u);
    }
    for(int i=1;i<=n;i++)x[i]=read();
    dfs(1,0);
    puts(f[1]<inf?"POSSIBLE":"IMPOSSIBLE");
    return 0;
}
```


---

