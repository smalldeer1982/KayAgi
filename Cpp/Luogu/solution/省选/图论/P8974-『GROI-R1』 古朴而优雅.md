# 『GROI-R1』 古朴而优雅

## 题目背景


会馆内忽地安静了下来。

「敝姓言，名杉。」

他的声音沉稳而凝重，略带沙哑，却不失力度，极具穿透力。每个字都重重地打在耳畔，渗进头脑里，让人想不认真听都难。

「这所学院的院长。」

## 题目描述

杉虽然年事已高，但是还是保持与时俱进。他学习了深度优先遍历算法，觉得这种新潮的东西在一所古朴而优雅的学院里会很受欢迎。所以，他找到了在走廊里晃荡的寒，向他提出了一个问题：

「我们知道，对一棵树进行深度优先遍历可以用下面的伪代码很好地解决。」

$$
\begin{array}{l}
\text{DFS-TREE}(u)\\
\begin{array}{ll}
1 & p\gets p+1\\
2 & t_p\gets u\\
3 & vis_u\gets 1\\
4 & \textbf{for }\text{each edge }(u,v)\in E \\
5 & \qquad \textbf{if }vis_v=0\\
6 & \qquad \qquad \text{DFS-TREE}(v)\\
7 & p\gets p+1\\
8 & t_p\gets u\\
\end{array}
\end{array}
$$

起初，所有变量或数组的值均为 $0$。

「我们把调用 $\text{DFS-TREE}(1)$ 在遍历过程中得到的数组 $t$ 称为这棵树的**遍历顺序**。」

「你看这段代码的第 $4$ 行，这句话**遍历每一条边的顺序是不固定的**。」

寒素来最讨厌不确定的东西，可是碍于院长的颜面，还是继续听下去。

「你能数出这段代码**会生成多少种不同的遍历顺序**吗？」

寒发现他曾经做过这个题，很快地报出了解法。本以为就结束了，可是杉继续说：

「如果我**在树上增加一条边**，你还会做吗？」

寒发现他的那点水平完全不够了，于是他去请教玘。玘却认为这道题目依然很简单，他告诉了寒这道题的做法。可是寒找不到杉了。

这个世界到底怎么了呢？

## 说明/提示

**样例解释**

对于第一次询问可以得到如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ojeiswc8.png)

能得到的遍历顺序有：

- $\{1,2,3,3,2,4,4,1\}$
- $\{1,4,4,2,3,3,2,1\}$
- $\{1,3,2,2,3,4,4,1\}$
- $\{1,4,4,3,2,2,3,1\}$

对于第二次询问可以得到如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6dut5s4r.png)

能得到的遍历顺序有：

- $\{1,2,2,3,3,4,4,1\}$
- $\{1,2,2,4,4,3,3,1\}$
- $\{1,3,3,2,2,4,4,1\}$
- $\{1,3,3,4,4,2,2,1\}$
- $\{1,4,4,2,2,3,3,1\}$
- $\{1,4,4,3,3,2,2,1\}$

**数据范围**

**本题采用捆绑测试。**

| 测试点编号 | 数据范围 | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{Subtask1}$ | $n,q\le8$ |  | $5$ |
| $\text{Subtask2}$ | $n,q\le20$ |  | $10$ |
| $\text{Subtask3}$ | $n,q\le500$ |  | $10$ |
| $\text{Subtask4}$ | $n,q\le3000$ |  | $15$ |
| $\text{Subtask5}$ | $n,q\le2\times10^5$ | $\text{A}$ | $15$ |
| $\text{Subtask6}$ | $n,q\le2\times10^5$ | $\text{B}$ | $10$ |
| $\text{Subtask7}$ | $n,q\le2\times10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证每一次询问的边 $(x,y)\in E$。

特殊性质 $\text{B}$：保证树退化成一条链。

对于 $100\%$ 的数据保证 $1\le n,q\le2\times10^5$，$1\le u,v,x,y\le n$，$x\ne y$。

## 样例 #1

### 输入

```
4 2
1 2
1 3
1 4
2 3
1 4```

### 输出

```
4
6```

# 题解

## 作者：TernaryTree (赞：4)

赛时所有结论都推出来了，代码没调出来（

---

## 结论 $1$

考虑一棵树 $(V,E)$，它的遍历方案数为：

$$f(V,E)=\prod_u \text{deg}_u!$$

其中 $\text{deg}_u$ 表示结点 $u$ 的子节点个数。

### 证明：

对于每个点的所有子节点 $S_u=\{v\mid u\to v\}$，其中 $|S_u|=\text{deg}_u$，存在 $\text{deg}_u!$ 种排列方式。

考虑每一次遍历都优先选择当前结点 $u$ 在集合 $S_u$ 中 第一个子结点。则每种排列都对应唯一一种遍历顺序。根据乘法原理，结论得证。

## 结论 $2$

对于任意图，遍历过程中，所有经过的边构成了一棵树。

### 证明：

证明其是一棵树，可分解为：

1. 边集 $E'$ 是连通的

2. 点集 $V$ 的大小为边集大小加一。

对于 $1$，结论显然成立。

对于 $2$，考虑到初始时，点集大小为 $1$（$V'=\{1\}$），边集为空集。每次多遍历一个点，点集与边集同时增加一个元素，故差值不变为 $1$，证毕。

## 结论 $3$

对于一棵基环树，有且仅有一条边没有被遍历到。形式化地，设基环树为 $(V,E)$，并且遍历中经过的所有边为 $E'$，则有 $|E\backslash E'|=1$。

### 证明：

由结论 $2$，有 $|E'|=n-1$。又基环树有 $n$ 条边，得证。

## 结论 $4$

没有被遍历到的这条边一定在环上。

### 证明：

考虑反证。若这条边不在环上，由于基环树除环边外，剩余的每条边都是割边，故若这条边没有遍历到，$E'$ 不连通，矛盾，得证。

## 结论 $5$

若在原树上增加边 $(x,y)$，则环为 $x$ 到 $\operatorname{lca}(x,y)$ 路径与 $y$ 到 $\operatorname{lca}(x,y)$ 路径的交加上边 $(x,y)$。

### 证明：

显然的，若基环树上一条边被去掉，剩余部分仍然连通，则这条边在环上。

考虑 $x$ 到 $\operatorname{lca}(x,y)$ 这条路径上任意一边。若割掉 $(u,v)$，其中 $u$ 是 $v$ 的父亲，则 $u$ 仍然可以通过 $u\to \operatorname{lca}(x,y)\to y\to x\to v$，原图仍然连通。$y$ 到 $\operatorname{lca}(x,y)$ 同理。

## 结论 $6$

若在原树上增加边 $(x,y)$，则没有被遍历到的边属于 $\operatorname{lca}(x,y)$ 在环上的两边。

### 证明：

由于我们假定 $1$ 为根，故遍历过程中一定会进入环。由于环上深度最低的点是 $\operatorname{lca}(x,y)$，所以进入环后，有两条路径选择：顺时针走与逆时针走。由深搜“走到死路才回头”的性质，结论得证。

## 结论 $7$

若在原树上增加边 $(x,y)$，则答案为将没有遍历到的边各个删去，得到的树的答案之和。形式化地，

$$\text{ans}=\sum f(V,E')$$

其中

$$f(V,E)=\prod_u \text{deg}_u!$$

### 证明：

没有遍历到的边对答案没有贡献，删去后答案不变。证毕。

## 结论 $8$

在原树上删去一条边再添加一条边使得仍然连通，则最多只有 $4$ 个结点的 $\text{deg}$ 发生了变化，且这四个结点为删去边与添加边的端点。

具体地，若删去一条边 $(u,v)$，则 $\text{deg}_u\gets \text{deg}_u-1$，$\text{deg}_v\gets \text{deg}_v-1$；若添加边 $(x,y)$，则 $\text{deg}_x\gets \text{deg}_x+1$，$\text{deg}_y\gets \text{deg}_y+1$。

### 证明：

删去一条边 $(u,v)$（$u$ 为 $v$ 的父亲）后，显然的 $\text{deg}_u\gets \text{deg}_u-1$（少了一条通向 $v$ 的边）。而对于 $v$，手玩可以发现，其一个子结点成为了它的父亲结点，所以 $\text{deg}_v\gets \text{deg}_v-1$。

加上一条边同理。

## 总结

利用结论 $8$，考虑到我们只关心 $\text{deg}$ 的变化，预处理出阶乘及其逆元，可以在 $\Theta(q\log n)$ 的复杂度内完成问题。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 5e5 + 1;
const int mod = 1e9 + 7;
const int maxd = 20;

typedef pair<int, int> pii;

struct edge {
    int to, next;
};

int n, q;
int head[maxn];
edge e[maxn << 1];
int cnt;

void add_edge(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

int fac[maxn];
int inv[maxn];

int power(int base, int freq, int mod) {
    int ans = 1, tmp = base;
    while (freq) {
        if (freq & 1) ans = ans * tmp % mod;
        freq >>= 1;
        tmp = tmp * tmp % mod;
    }
    return ans;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    inv[maxn - 1] = power(fac[maxn - 1], mod - 2, mod);
    for (int i = maxn - 2; ~i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int fa[maxn][maxd];
int dep[maxn];

void get_dep(int u, int depth, int fat) {
    dep[u] = depth;
    for (int i = head[u]; i; i = e[i].next) {
        if (e[i].to != fat) {
        	get_dep(e[i].to, depth + 1, u);
		}
    }
} 

void get_fa(int cur, int fat) {
    fa[cur][0] = fat;
    for (int i = 1; i <= log2(dep[cur]) + 1; i++) {
        fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
    }
    for (int i = head[cur]; i; i = e[i].next) {
        if (e[i].to != fat) {
        	get_fa(e[i].to, cur);
		}
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v]) {
        u = fa[u][(int) log2(dep[u] - dep[v])];
    }
    if (u == v) return u;
    for (int i = log2(dep[u]); i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int ful = 1;
int deg[maxn];

void dfs(int u, int fa, int &mul) {
    int tot = 0;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        tot++;
        dfs(v, u, mul);
    }
    mul = mul * fac[tot] % mod;
    deg[u] = tot;
}

int getans(int u, int v, int x, int y) {
    int cur = ful * inv[deg[u]] % mod * inv[deg[v]] % mod * inv[deg[x]] % mod * inv[deg[y]] % mod;
    deg[u]--, deg[v]--, deg[x]++, deg[y]++;
    cur = cur * fac[deg[u]] % mod * fac[deg[v]] % mod * fac[deg[x]] % mod * fac[deg[y]] % mod;
    deg[u]++, deg[v]++, deg[x]--, deg[y]--;
    return cur;
}

int firstson(int u, int v) {
    int d = dep[v] - dep[u] - 1;
    for (int i = log2(d + 1); ~i; i--) {
        if (d >> i & 1) v = fa[v][i];
    }
    return v;
}

pii getson(int rt, int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    if (u == rt) {
        return make_pair(v, firstson(u, v));
    }
    return make_pair(firstson(rt, u), firstson(rt, v));
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init();
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    get_dep(1, 0, 0);
    get_fa(1, 0);
    dfs(1, 0, ful);
    while (q--) {
        int x, y;
        cin >> x >> y;
        int z = lca(x, y);
        if (dist(x, y) == 1) {
            cout << ful << endl;
            continue;
        }
        pii ts = getson(z, x, y);
        int xt = ts.first, yt = ts.second;
        int ans1 = getans(z, xt, x, y), ans2 = getans(z, yt, x, y);
        cout << (ans1 + ans2) % mod << endl;
    }
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

闲话：这能评紫？感觉蓝差不多了吧。

---

首先考虑一棵树怎么做。显然我们对第 $i(i>1)$ 个度为 $d_i$ 的节点有 $(d_i-1)!$ 种遍历顺序（根节点 $1$ 为 $d_1!$），所以整体的方案就是 $d_1!\prod\limits_{i=2}^{n}(d_i-1)!$ 种。

然后考虑基环树怎么处理。基环树就是树 + 一条边。简单模拟一下，我们会发现这个基环树遍历完了之后一定恰好是有一条边没遍历到的，因为最后访问的那条边一定是 $u$ 和 $v$ 已经被搜索过就走不了了。

另外这条边肯定在环上，否则搜出来就不连通了。考虑连边 $x,y$，则环一定是 $\text{LCA}(x,y) \rightarrow y \rightarrow x \rightarrow \text{LCA}(x,y)$ 这样，或者反过来。由于深搜会一直搜到死路，所以最后要么是从 $x$ 到 $\text{LCA}(x,y)$ 的最后一步没搜到，要么是从 $y$ 到 $\text{LCA}(x,y)$ 的最后一步没搜到。

所以我们只需要考虑这两种情况对答案带来的影响。

当我们删除一条边 $(x,y)$ 时，会使得 $d_x \rightarrow d_x-1$，$d_y \rightarrow d_y-1$，答案从 $(d_x-1)!(d_y-1)!$ 变成 $(d_x-2)!(d_y-2)!$。$x$ 或 $y$ 为根节点的少减 $1$ 即可，不再赘述。答案变化了 $\dfrac{1}{(d_x-1)(d_y-1)}$ 倍。

当我们添加一条边 $(x,y)$ 时，会使 $d_x \rightarrow d_x+1$，$d_y \rightarrow d_y+1$。同理可以算出答案的变化为 $d_xd_y$ 倍。根节点需要 +1，不再赘述。

那么答案也会相应的扩大 / 缩小一定的倍数。所以我们只需要预处理一开始的答案，以及 $\text{LCA}$ 和逆元，每次在线进行修改，重新计算贡献就可以了。

复杂度 $O((n+q)\log n)$。

---

## 作者：lsj2009 (赞：0)

## Solution

本题解不对部分分做法进行讲解。

我个人认为这题应该是本场比赛中质量最高的一题。其次，它是一道浑身结论的结论题。

首先再解决这个问题前，我们需要先来看看题目中“做过的”那个问题：

> 给定一棵树，计算会生成多少种不同的遍历顺序。

结论 $1$：每一种遍历顺序与树的形态一一对应（这里的形态分每一个节点的左右）。

证明：显然一个数 $u$ 在遍历顺序当中会出现两次，第一次是进入以 $u$ 为根的子树，第二次是完成对整个以 $u$ 为根的子树的遍历。而两者中间那一段区间则表示了以 $u$ 为根的子树的形态。依据数学归纳法，我们从一个叶子节点 $u$ 逐渐向上递归，即可得到整棵树的形态。这里不再赘述。

继续思考，第一眼的想法是树形 dp。我们考虑定义状态 $f_u$ 表示为对于以 $u$ 为根的子树会有多少种可能的遍历顺序。容易发现我们先遍历 $u$ 的每一棵子树都会产生不同的遍历顺序，而对于 $u$ 的每一棵子树内部也会有不同的遍历顺序，所以根据乘法原理可以得到 $f_u=|\text{Son}_u|!\prod\limits_{v\in \text{Son}_u} f_v$。其中 $\text{Son}_u$ 表示 $u$ 的儿子集合。然后我们将整棵树得到的算式展开（或者由整棵树自底向上考虑）即可得到 $f_1=\prod\limits_{u} |\text{Son}_u|!$，这里我们默认 $1$ 号节点为根。接下来，容易发现，除一号节点外，所有节点均有一个父节点，所以可以得到 $|\text{Son}_u|=deg_u-[u\neq 1]$，其中 $deg_u$ 表示为节点 $u$ 的度数。所以可以得到原算式更容易维护的一个版本：$f_1=\prod\limits_{u} (deg_u-[u\neq 1])!$。

此时，我们完成了对于一棵树的解答。但是真正的题目是 $q$ 次询问，每次询问加入一条边（即令原树变成一棵基环树），问其方案总数。

结论 $2$：其中必然有且仅有 $1$ 条边没有遍历过。

证明：设 $R$ 为我们已经经过的点，最开始 $R=\{1\}$，接下来每一次经历过一条边，我们都会从一个点 $u\in R$ 来到一个点 $v\notin R$，然后 $R\gets R+\{v\}$，当 $\{R\}=[1,n]\cap \mathbb{N}$ 时即遍历结束。容易发现每经过一条边 $|R|$ 的大小 $+1$，最终 $|R|=n$，一开始 $|R|=1$，所以说我们经过了 $n-1$ 条边，而一棵基环树有 $n$ 条边，所以我们定然没有经过一条且仅有一条边。

结论 $3$：这条边一定在环上。

证明：显然。因为如果这条边不在环上，一棵基环树定然会裂成两个部分，则我们没一次完成遍历。

结论 $4$：满足条件的边有且仅有两条为与环上深度最低的点相邻的在环上的边。

证明：首先，这个点还有另一个名字叫环上最接近于根的点。如果要完成遍历就必须要进入环，而进入环的的第一步就是需要通过唯一的进入环的边通过点 $u$ 而环上每个点在环内的边只有两条，但是无论从哪一条走，我们都会绕一遍后通过另一条回到点 $u$,而此时点 $u$ 却已经经过，所以那条边定然不能经过。哪怕其中有一个点 $v$ 连向了环以外的点，但因为基环树有且仅有一个环，所以肯定又会完成对以点 $v$ 为根的子树后继续回归，完成对环的遍历。所以，无论选择哪条边进入环，我们总能完成对环上除与进入那条边对应的边以外所有边的遍历。

结论 $5$：若连接边 $(u,v)$，则上述环上深度最低的点位 $lca(u,v)$。

证明：因为有结论为环即为路径 $(u,v)$ 加上边 $(u,v)$，原因为这构成一个环，而基环树上有且仅有一个环，所以该结论为真。然后回到原结论，显然路径 $(u,v)$ 与环 $(u,v)$ 点集相同，而 $lca(u,v)$ 是路径上所有节点的祖先，所以深度最低。

至此，本题所有结论已介绍完毕。我们再回到一棵树的情况下，则我们连上边 $(u,v)$ 再接上上述结论两条边的任意一条，也就得到了两棵树，而且这两棵树的遍历顺序互不相同。

那么我就可以通过此前的公式计算出两种情况的答案但是这样复杂度 $O(nq)$。其实容易发现，度数改变的点有且仅有至多四个点：连上的边的两个点和接上边的两个点。所以我们就可以先预处理出原树答案，然后通过此计算偏差对答案进行更改即可，具体的，将两式作比。

但是更具体的，我们还需要分类讨论：重边与自环，这种情况答案即为原树答案；连边两点为祖先子孙关系，这样断掉的两边有一边为连上的边；还有就是两点不为祖先子孙关系，这种情况最平凡，但也需注意断掉边和连上边的点是否有重合。

详见代码。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define int long long
#define PII pair<int,int>
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
using namespace std;
const int N=1e6+5,M=25,MOD=1e9+7;
int qpow(int a,int b) {
	int res=1,base=a;
	while(b) {
		if(b&1)
			res=res*base%MOD;
		base=base*base%MOD; b>>=1;
	}
	return res;
}
int head[N],deg[N],len;
struct node {
	int to,nxt;
}; node edge[N<<1];
void add_edge(int u,int v) {
	edge[++len]={v,head[u]}; head[u]=len; ++deg[v];
}
int jc[N],f[N][M],d[N],ans=1;
void dfs(int u,int fa) {
	d[u]=d[fa]+1; f[u][0]=fa;
	rep(i,1,20)
		f[u][i]=f[f[u][i-1]][i-1];
	ans=jc[deg[u]-(u!=1)]*ans%MOD;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(v!=fa) {
			dfs(v,u);
		}
	}
}
int getson(int u,int v) {
	per(i,20,0) {
		if(d[f[v][i]]>d[u])
			v=f[v][i];
	}
	return v;
}
int lca(int u,int v) {
	per(i,20,0) {
		if(d[f[v][i]]>=d[u])
			v=f[v][i];
	}
	if(u==v)
		return u;
	per(i,20,0) {
		if(f[u][i]!=f[v][i])
			u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
int solve(int u,int v) {
	if(d[u]>d[v])
		swap(u,v);
	int lc=lca(u,v);
	int su=getson(lc,u),sv=getson(lc,v);
	if(u==lca(u,v)) {
		int t=jc[deg[u]-(u!=1)]*qpow(jc[deg[u]-(u!=1)+1],MOD-2)%MOD;
		t=t*jc[deg[sv]-(sv!=1)-1]%MOD*qpow(jc[deg[sv]-(sv!=1)],MOD-2)%MOD;
		t=(t+jc[deg[u]-(u!=1)]%MOD*qpow(jc[deg[u]-(u!=1)+1],MOD-2)%MOD*jc[deg[v]-(v!=1)]%MOD*qpow(jc[deg[v]-(v!=1)+1],MOD-2)%MOD)%MOD;
		return t%MOD;
	}
	int res=0;
	if(u==su) {
		int t=jc[deg[u]-(u!=1)]*qpow(jc[deg[u]-(u!=1)+1],MOD-2)%MOD;
		u=f[u][0];
		t=t*jc[deg[u]-(u!=1)-1]%MOD*qpow(jc[deg[u]-(u!=1)],MOD-2)%MOD;
		res=(res+t)%MOD;
	} else {
		u=su;
		int t=jc[deg[u]-(u!=1)-1]*qpow(jc[deg[u]-(u!=1)],MOD-2)%MOD;
		u=f[u][0];
		t=t*jc[deg[u]-(u!=1)-1]%MOD*qpow(jc[deg[u]-(u!=1)],MOD-2)%MOD;
		res=(res+t)%MOD;
	}
	if(v==sv) {
		int t=jc[deg[v]-(v!=1)]*qpow(jc[deg[v]-(v!=1)+1],MOD-2)%MOD;
		v=f[v][0];
		t=t*jc[deg[v]-(v!=1)-1]%MOD*qpow(jc[deg[v]-(v!=1)],MOD-2)%MOD;
		res=(res+t)%MOD;
	} else {
		v=sv;
		int t=jc[deg[v]-(v!=1)-1]*qpow(jc[deg[v]-(v!=1)],MOD-2)%MOD;
		v=f[v][0];
		t=t*jc[deg[v]-(v!=1)-1]%MOD*qpow(jc[deg[v]-(v!=1)],MOD-2)%MOD;
		res=(res+t)%MOD;
	}
	return res;
}
signed main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n,q;
	scanf("%lld%lld",&n,&q);
	rep(i,2,n) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	jc[0]=1;
	rep(i,1,n)
		jc[i]=jc[i-1]*i%MOD;
	dfs(1,0);
	while(q--) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		if(u==v||u==f[v][0]||v==f[u][0])
			printf("%lld\n",ans);
		else {
			int upu=jc[deg[u]-(u!=1)+1]%MOD*qpow(jc[deg[u]-(u!=1)],MOD-2)%MOD;
			int upv=jc[deg[v]-(v!=1)+1]%MOD*qpow(jc[deg[v]-(v!=1)],MOD-2)%MOD;
			printf("%lld\n",solve(u,v)%MOD*ans%MOD*upu%MOD*upv%MOD);
		}
	}
	return 0;
}
```

---

