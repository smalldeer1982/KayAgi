# [AGC037D] Sorting a Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc037/tasks/agc037_d

$ N $ 行 $ M $ 列のマス目があります。 このマス目には $ 1 $ から $ NM $ までの整数がそれぞれ $ 1 $ つずつ書かれています。 上から $ i $ 行目、左から $ j $ 列目にあるマスに書かれている数は $ A_{ij} $ です。

あなたはこのマス目を以下の手順に従って並べ替える必要があります。

1. まず $ N $ 個の行それぞれに対して、その行に書かれている数を好きに並べ替える。
2. 次に $ M $ 個の列それぞれに対して、その列に書かれている数を好きに並べ替える。
3. 最後に $ N $ 個の行それぞれに対して、その行に書かれている数を好きに並べ替える。

最終的に上から $ i $ 行目、左から $ j $ 行目にあるマスに書かれている数が $ M\times\ (i-1)+j $ となるようにしたいです。 そのような並べ替え方を一つ構成してください。与えられた制約の下で、常に条件をみたすように並べ替えられることができることは保証されています。

## 说明/提示

### 制約

- $ 1\ ≦\ N,M\ ≦\ 100 $
- $ 1\ ≦\ A_{ij}\ ≦\ NM $
- $ A_{ij} $ は相異なる

## 样例 #1

### 输入

```
3 2
2 6
4 3
1 5```

### 输出

```
2 6 
4 3 
5 1 
2 1 
4 3 
5 6```

## 样例 #2

### 输入

```
3 4
1 4 7 10
2 5 8 11
3 6 9 12```

### 输出

```
1 4 7 10 
5 8 11 2 
9 12 3 6 
1 4 3 2 
5 8 7 6 
9 12 11 10```

# 题解

## 作者：YksKuusiTAlv (赞：14)

## [AGC037D](https://atcoder.jp/contests/agc037/tasks/agc037_d)

### 基本转化

从 $D$ 变成 $C$ ， 发现只需要保证每行中是它这一行 $D$ 中元素的排列即可。

从 $C$ 变成 $B$ ， 发现 $B$ 需要 在 $C$ 中是同一行的元素要通过列上的交换变到一行上，也就是保证 $C$ 中同一行的元素不能在相同的列上。

### sol1 (爆标)

问题转化成了，给定一个 $n\times m$ 的矩阵 $\rm A$ ， 再给定 $n$ 个形如以下的限制：指定 $m$ 个元素，要求他们不能在同一列上。

保证每个元素被指定一次，要求任意排列每一行满足限制。

继续观察性质，发现我们想要泛化问题，可以把初始给定的矩阵和操作也转化成限制，也就是初始矩阵给定的每一行元素不能在同一列上。

这样，问题就只剩下了 $2\times n$ 个限制，需要给每个元素染上 $m$ 种颜色中的一种，使得每个限制的集合内颜色不同。

别忘了我们转化的过程中，限制并不一般，具有任意一个元素出现且仅出现在两个限制内，且存在 $n$ 个无交的限制的并集是全集，并且这 $n$ 个限制的补集也满足无交且并是全集。

既然可以分成两个是全集的集合，考虑建一张二分图出来，左右两部分分别是 $n$ 个并集是全集的无交限制。

每个元素出现且仅出现在两个限制内，就把他们连一条边。

问题变成了给定一个左右分别有 $n$ 个点的二分图，每个点有 $m$ 条边，要求给每条边染 $1 \sim m$ 的色，使得每个点连出的边中恰好包含 $m$ 种颜色。

这个问题是 Vizing 定理的经典形式，直接套用其构造性证明方法，即可做到 $O(n\times nm)=O(n^3)$ ， [code](https://atcoder.jp/contests/agc037/submissions/32528777)

### sol2 (标算)

还有另外一种转化的方式，考虑先把 $D$ 中同一行的元素染上一种色。

那么就是给定一个 $n \times m$ 的矩阵 $\rm A$，每个元素被染上了一种颜色，保证一共有 $n$ 种颜色且每种出现 $m$ 个。

要求排列每一行，使得每列包含恰好 $n$ 种颜色。

每行建立一个节点，每个颜色建立一个节点，每行向包含的每个颜色连包含次数条边。

这个二分图的一个完美匹配对应了一列的方案，只需要跑 $m$ 次就可以得到 $\rm B$ 矩阵。

问题是怎么证明这个图一定扛得住 $m$ 个完美匹配。

还剩 $k$ 列没选择的时候，这张图是一张 k-正则 二分图，根据 Hall 定理的推论，一定存在完美匹配。

> 一个无向图，每个点度数都是 $k$ ，则称这个图为 k-正则图。

>假设存在一个集合 $S$, $|N(S)|<|S|$, 由于 $|S|$ 向 $|N(S)|$ 连了 $|S|\times k$ 条边，所以 $N(S)$ 至少有 $|S|\times k$ 条边，但是 $N(S)$ 只有 $N(S)\times k$ 条边，与假设矛盾，故推论成立。


### summary

我们惊奇的发现，虽然从两种完全不同的角度思考，但是建出来的图竟然是完全一样的！

~~也就是你们不跑 $m$ 次最大流而是直接跑 Vizing 定理也可以爆标哦~~~。

同时，也可以这么去理解 sol1，在这个图上找一个完美匹配，然后把他们都染上一种染色，第 $i$ 次染第 $i$ 种染色，因为是完美匹配，所以每个点在这种颜色都有且仅有一条边覆盖它，一定能保证每个点恰好包含 $n$ 种颜色。

---

## 作者：nueryim (赞：12)

## 题解：AT_agc037_d [AGC037D] Sorting a Grid

### 题意

题面很省流了，这里强调一点，本题 $B$、$C$ 只要合法就行，因为可能有很多方案（显然）。

### 分析

看到这种构造方案的首先想到**暴搜**和**网络流**，这里 $n\leq 100$ 暴搜的复杂度“爆”了，将思路往网络流上靠一靠。

---

注意到初始 $A$、目标 $D$ 都为已知，因此就可以依靠这种**定**的关系建图。如果我们想知道方案，对于每个元素我们就要知道其在 $B$ 或 $C$ 中的**行号、列号和值**。

考虑 $A$ 和 $B$ 的关系：我们发现，$A$ 和 $B$ 每一**整行**的元素一定是相同的（不考虑顺序），因此在图中可以使用**相同的节点**表示 $A$ 和 $B$ 的**行号**（$C$ 和 $D$ 同理）。

考虑 $B$ 和 $C$ 的关系：我们发现，$B$ 和 $C$ 每一**整列**的元素一定是相同的，因此在图中可以使用**相同的节点**表示 $B$ 和 $C$（当前列）的**值**，至于为什么要表示**值**而不是**列号**，往下读就知道了。

综上，参照第一个样例，我们可以建出大概这样一副图：

![](https://cdn.luogu.com.cn/upload/image_hosting/74qo6tuw.png)

左边 $3$ 个点表示 $A$ 和 $B$ 的行号，右边 $3$ 个点表示 $C$ 和 $D$ 的行号，中间 $6$ 个点则表示 $B$ 和 $C$ 的值。

---

因为 $A$ 到 $B$ 每行的元素相同，所以从 $A$ 每行的行号向 $B$ 每行（也就是 $A$ 每行）的值连容量为 $1$ 的边，表示 $B$ 当前行可以存在 $A$ 当前行的值。

因为 $C$ 到 $D$ 每行的元素也相同，所以 $D$ 当前行的行号应从 $C$ 当前行的所有值连容量为 $1$ 的边，表示 $C$ 当前行可以存在 $D$ 当前行的值。

连完后图大概长这样：（边的容量都是一）

![](https://cdn.luogu.com.cn/upload/image_hosting/azbt3zjr.png)

---

我们现在倒回来看看连完后的图代表着什么，例如一条路径：$1\sim 6\sim3$ 就表示 $B$ 中第一行值为 $6$ 的元素在 $C$ 中的第三行（**值为 $6$ 的元素在 $B$ 中第一行，在 $C$ 中第三行**）；路径：$3\sim 5\sim 3$ 表示 $B$ 中第三行值为 $5$ 的元素在 $C$ 中还是第三行。

一组（$3$条且没有公用节点）路径如：$1\sim 6\sim 3$、$2\sim 3\sim 2$、$3\sim 1\sim 1$ 就表示 $B$、$C$ 的这一列的元素为 $6$、$3$、$1$。图中可以分出两组路径，刚好就对应了矩阵的两列。

现在我们只需要知道如何给路径分组就能通过代入以上两个结论确定 $B$ 和 $C$ 的具体元素了。

---

那么如何分组呢？

我们发现如果给原图加上**源点**和**汇点**，那么一组恰好对应一个完美匹配，如图：（边的容量均为一）

![](https://cdn.luogu.com.cn/upload/image_hosting/si3ih2yc.png)

那么剩下的就简单了，跑 $m$ 次最大流，每次统计方案即可。

### 代码

有几个细节强调一下：

- 每次跑完最大流要将直接连着源点和汇点的边的容量重置
- 统计答案时要将统计进答案的边加上标记

其他的就看代码吧：

~~~cpp
//AT_agc037_d (AC)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define int long long

int read()
{
    int res = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (; isdigit(ch); ch = getchar())
        res = (res << 3) + (res << 1) + (ch ^ 48);
    return res * f;
}

const int INF = 0x3f3f3f3f;
const int N = 1005; //开大点保险...

int n, m, a[N][N];

int pos(int num, int x) //左边的点num为1， 中间为0， 右边为2
{
    if (num == 1)
        return n * m + x;
    if (num == 2)
        return n * m + n + x;
    return x;
}

int s, t, tot = 1, tota, totb, head[N * N + N * 2], cur[N * N + N * 2];
bool vis[N * N * 4];

struct edge
{
    int to, nxt, flow;
} e[N * N * 4];

void add(int u, int v, int flow)
{
    e[++ tot] = (edge) {v, head[u], flow};
    head[u] = tot;
}

void build()
{
    for (int i = 2; i <= tota; i += 2)
        e[i].flow = 1, e[i ^ 1].flow = 0;
    for (int i = totb; i <= tot; i += 2)
        e[i ^ 1].flow = 1, e[i].flow = 0;
}

int dep[N * N + N * 2];

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue <int> q;
    dep[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u], v, f; i; i = e[i].nxt)
        {
            if (vis[i] || vis[i ^ 1])
                continue;
            v = e[i].to, f = e[i].flow;
            if (f && dep[v] == 0)
            {
                dep[v] = dep[u] + 1;
                q.push(v);
                
            }
        }
    }
    return dep[t];
}

int dfs(int u, int flow)
{
    if (u == t || flow == 0)
        return flow;
    int res = 0, tmp;
    for (int &i = cur[u], v, f; i; i = e[i].nxt)
    {
        if (vis[i] || vis[i ^ 1])
            continue;
        v = e[i].to, f = e[i].flow;
        if (dep[v] == dep[u] + 1 && (tmp = dfs(v, min(flow - res, f))))
        {
            res += tmp;
            e[i].flow -= tmp;
            e[i ^ 1].flow += tmp;
            if (res == flow)
                return res;
        }
    }
    return res;
}

int dinic()
{
    int res = 0, tmp;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (tmp = dfs(s, INF))
            res += tmp;
    }
    return res;
}

int cnt, ans1[N][N], ans2[N][N];

void stats()
{
    cnt ++;
    for (int u = 1; u <= n; u ++)
        for (int i = head[pos(1, u)]; i; i = e[i].nxt)
            if (!vis[i] && e[i].to < pos(1, u) && e[i].flow == 0)
            {
                vis[i] = vis[i ^ 1] = 1;
                ans1[u][cnt] = e[i].to;
                break;
            }
    for (int u = 1; u <= n; u ++)
        for (int i = head[pos(2, u)]; i; i = e[i].nxt)
            if (!vis[i] && e[i].to < pos(2, u) && e[i].flow == 1)
            {
                vis[i] = vis[i ^ 1] = 1;
                ans2[u][cnt] = e[i].to;
                break;
            }
}

signed main()
{
    n = read(), m = read();
    s = n * m + n * 2 + 1, t = s + 1;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            a[i][j] = read();

    for (int i = 1; i <= n; i ++)
        add(s, pos(1, i), 1), add(pos(1, i), s, 0);
    tota = tot;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            add(pos(1, i), a[i][j], 1), add(a[i][j], pos(1, i), 0);
    for (int i = 1; i <= n; i ++)
        for (int j = (i - 1) * m + 1; j <= i * m; j ++)
            add(j, pos(2, i), 1), add(pos(2, i), j, 0);
    totb = tot;
    for (int i = 1; i <= n; i ++)
        add(pos(2, i), t, 1), add(t, pos(2, i), 0);

    for (int i = 1; i <= m; i ++)
    {
        build(); //重置源点和汇点的边的容量
        dinic(); //跑最大流
        stats(); //统计
    }

    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1; j <= m; j ++)
            printf("%lld ", ans1[i][j]);
        printf("\n");
    }
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1; j <= m; j ++)
            printf("%lld ", ans2[i][j]);
        printf("\n");
    }

    return 0;
}
~~~

---

## 作者：Kinandra (赞：8)

标签: 二分图匹配

#### Part 1

考虑用 $D$ 向前还原成 $C$ . 显然只要每个元素在 $C$ 指在其所处的行 $C$ 就是合法的.

考虑 $C$ 还原 $B$ , 我们将同一行的元素染成一种颜色(方便起见记 $col_x=\lfloor \frac{x-1}m\rfloor+1)$ ), 显然 $B$ 的每一列恰好包含每种颜色的元素恰好一个, 并且这样的 $B$ 可以很容易地得到一个合法的 $C$ .

那么问题就转化为给定一个矩阵 $A$ , 每个元素有一个颜色且每个颜色恰好出现 $m$ 个, 要求任意排列每一行地元素后使得每一列恰好包含每一种颜色.

#### Part 2

我们可以想到一个二分图匹配的算法, 为每一行建立一个节点, 为每一种颜色建立一个节点, 行节点向行包含的颜色连边. 这个二分图的一个**完美匹配**等价于矩阵 $B$ 一列的方案, 那么我们只要做 $m$ 次二分图匹配并取出 $m$ 次完美匹配就可以构造一个合法的 $B$ 了.

那么问题就是我们任意取完美匹配是否能保证之后一定能取出完美匹配. 答案是肯定的: 考虑还剩 $k$ 列方案未决定, 此时每个行节点和颜色节点的**度数**都恰好为 $k$ , 我们假设此时不存在完美匹配, 根据 Hall 定理, 必然有一个行节点的集合 $S$ , 使得 $S$ 连向的所有颜色节点的集合 $T$ 满足 $|S|>|T|$ . 又知 $S,T$ 间的边数为 $k|S|$ , 则 $T$ 中必然存在一个点的度数大于 $k$ , 矛盾.

时间复杂度 $\mathcal O(nm^2\sqrt n)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, m;
int col(int x) { return (x - 1) / m + 1; }
int a[202][202], b[202][202];
vector<int> c[202][202];
void pop(int x, int i, int j) { b[i][j] = c[i][x].back(), c[i][x].pop_back(); }

struct Flow {
    int s, t;
    int hd[1003], nx[100005], to[100005], c[100005], cnt;
    void add(int f, int t, int cap) {
        nx[++cnt] = hd[f], hd[f] = cnt, to[cnt] = t, c[cnt] = cap;
    }
    void fadd(int f, int t) { add(f, t, 1), add(t, f, 0); }
    void init() { t = (s = (n << 1) + 1) + 1, cnt = 1; }

    queue<int> q;
    int dep[1003];
    bool bfs() {
        for (int i = 1; i <= t; ++i) dep[i] = 0;
        dep[s] = 1, q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = hd[u], v; i; i = nx[i])
                if (!dep[v = to[i]] && c[i] > 0) dep[v] = dep[u] + 1, q.push(v);
        }
        return dep[t];
    }

    int iter[1003];
    int dfs(int u, int dist) {
        if (u == t) return dist;
        for (int &i = iter[u], v; i; i = nx[i]) {
            if (c[i] < 1 || dep[v = to[i]] != dep[u] + 1) continue;
            int d = dfs(v, min(dist, c[i]));
            if (d) return c[i] -= d, c[i ^ 1] += d, d;
        }
        return 0;
    }

    void Dinic() {
        while (bfs()) {
            for (int i = 1; i <= t; ++i) iter[i] = hd[i];
            while (dfs(s, 1000)) void();
        }
    }
    void work(int id) {
        for (int i = 1; i <= n; ++i) fadd(s, i), fadd(i + n, t);
        Dinic();
        for (int i = n + 1; i <= n + n; ++i)
            for (int j = hd[i]; j; j = nx[j])
                if (c[j]) c[j] = 0, pop(i - n, to[j], id);
    }
} flow;
void ins(int i, int x) { c[i][col(x)].push_back(x), flow.fadd(i, n + col(x)); }

int main() {
    n = read(), m = read(), flow.init();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) a[i][j] = read(), ins(i, a[i][j]);
    for (int i = 1; i <= m; ++i) flow.work(i);
    for (int i = 1; i <= n; ++i, puts(""))
        for (int j = 1; j <= m; ++j)
            printf("%d ", a[col(b[i][j])][j] = b[i][j]);
    for (int i = 1; i <= n; ++i, puts(""))
        for (int j = 1; j <= m; ++j) printf("%d ", a[i][j]);
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：幻影星坚强 (赞：6)

一年前我还在普转提时期的模拟赛的题，那时啥都不会，只有一堆普及知识，真佩服当时的自己能做（乱搞）出这道题，现在肯定做不出了，~~时代在退步。~~ 现在发现这是原题，于是来写个题解。

首先对于 $A$ 到 $B$ 的过程，我们要让 $D$ 每一行的数都处在不同列上，于是我们采用类似冒泡排序的贪心乱搞做法，假如某一列存在两个及以上 $D$ 同一行的数，那么就要将这些在同一行的数某一个移出去，于是我们便贪心的将这些数都与同行的下一列的数交换，但进行一次这样的操作显然不对，于是我们多进行几次交换，然后我将上界设为 $n\times m$ 。发现没有错误，正确性暂时不能证明，先留个坑。

对于 $B$ 到 $C$ 的过程，因为我们已经保证了 $D$ 每一行的数都处在不同列上，所以我们只要把他们搬到对应的行上就行了。

对于 $C$ 到 $D$ 的过程，因为我们保证 $C$ 的每一行都是对应这一行行 $D$ 里的数，所以显然可以换出来。

于是我们便用普及组的做法过了这道题，时间复杂度 $O(n^2m^2)$ ，~~正确性不能保证。~~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m;
int a[110][110], b[110][110], c[110][110], ori[110][110];//ori代表B的某一列有多少个D的某一行的数
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++ i)
	{
		for(int j = 1; j <= m; ++ j)
		{
			scanf("%d", &a[i][j]);
			++ ori[j][(a[i][j] - 1) / m + 1];
			b[i][j] = a[i][j];
		}
	}
	for(int timer = 0; timer < n * m; ++ timer)
	for(int i = 1; i < m; ++ i)
	{
		for(int j = 1; j <= n; ++ j)
		{
			if(ori[i][(b[j][i] - 1) / m + 1] > 1)//大于1，将它和同行的下一列交换
			{
				-- ori[i][(b[j][i] - 1) / m + 1];
				++ ori[i][(b[j][i + 1] - 1) / m + 1];
				++ ori[i + 1][(b[j][i] - 1) / m + 1];
				-- ori[i + 1][(b[j][i + 1] - 1) / m + 1];
				swap(b[j][i], b[j][i + 1]);
			}
		}
	}
	for(int i = 1; i <= n; ++ i)
	{
		for(int j = 1; j <= m ; ++ j)
		{
			c[i][j] = b[i][j];
		}
	}
	for(int timer = 0; timer < n; ++ timer)
	for(int i = 1; i <= n; ++ i)
	{
		for(int j = 1; j <= m ; ++ j)
		{
			int gu = c[i][j];
			swap(c[i][j], c[(gu - 1) / m + 1][j]);//换到对应行
		}
	}
	for(int i = 1; i <= n; ++ i)
	{
		for(int j = 1; j <= m; ++ j)
		{
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}
	for(int i = 1; i <= n; ++ i)
	{
		for(int j = 1; j <= m; ++ j)
		{
			printf("%d ", c[i][j]);
		}
		if(i != n)
		printf("\n");
	}
	return 0;
}

```


---

## 作者：chenxia25 (赞：2)

考虑倒推，从目标矩阵往前推。经过第三步和第二部，某个矩阵能被得到显然当且仅当它的每一列都来自不同行。然后考虑正过来，从原始矩阵经过第一步要能到达上述矩阵，也就是要将每一行重新排列使得每一列都被分配到来自 $n$ 个不同行的元素。于是只要解决这个问题就可以了，到这儿的分析还是很简单的。

下面考虑构造方案。先尝试构造第一列，就是要从每行选一个，选出来的 $n$ 个来自最终位置的不同行。那就是个二分图匹配嘛，没有更好的方法了。那怎么保证最大流跑出来的一组解执行之后，剩下来的 $n\times(m-1)$ 子问题依然有解呢？题面中有一句话「The constraints guarantee that it is always possible to achieve the objective.」很微妙，它是说给定数据一定有解还是任意可能的数据一定有解呢？直接翻译是前者，但是如果满足后者，我们就不用担心上述问题了，随便选一组完美匹配就行了。事实上后者确实是对的，下面给出一个证明。

显然只要每次 $n\times(m-i)$​​ 子问题都能找到一组完美匹配，由数学归纳法可知原命题成立。那看是否有完美匹配考虑霍尔定理：对任意 $\{1\sim n\}$​​​ 的子集，用它内部所有元素作为最终位置所在行定位到当前矩阵中 $s(m-i)$​​ 个位置（其中 $s$​​ 是子集大小），要是这些位置来自不少于 $s$​​ 行就好了。跟据抽屉原理，这是显然的………………事实上，这玩意构出来的二分图满足每个点度数相等，都等于 $m-i$​（重边也算），它专门有个名字叫 $m-i$​​ 阶正则二分图，上述证明说明任意（大于零阶）正则二分图都有完美匹配。

那就跑 $m$ 遍二分图最大流就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=20010;
int n,m,s,t;
vector<pair<int,int> > nei[N+1];
vector<int> rv[N+1];
void ae(int x,int y,int z){
	nei[x].pb(mp(y,z)),nei[y].pb(mp(x,0));
	rv[x].pb(nei[y].size()-1),rv[y].pb(nei[x].size()-1);
}
int dep[N+1];
bool bfs(){
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	queue<int> q;
	q.push(s);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i].X,c=nei[x][i].Y;
			if(c&&!~dep[y])dep[y]=dep[x]+1,q.push(y);
		}
	}
	return ~dep[t];
}
int now[N+1];
int dfs(int x=s,int flw=inf){
	if(x==t||!flw)return flw;
	int res=0,tmp;
	for(int &i=now[x];i<nei[x].size();i++){
		int y=nei[x][i].X,&c=nei[x][i].Y;
		if(dep[y]==dep[x]+1&&(tmp=dfs(y,min(flw,c)))){
			res+=tmp,flw-=tmp;
			c-=tmp,nei[y][rv[x][i]].Y+=tmp;
			if(!flw)break;
		}
	}
	return res;
}
int dinic(){
	int res=0;
	while(bfs()){
		memset(now,0,sizeof(now));
		res+=dfs();
	}
	return res;
}
int a[N/100][N/100];
int chs[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=1;i<=m;i++){
		for(int j=1;j<=2*n+2;j++)nei[j].clear(),rv[j].clear();
		s=2*n+1,t=s+1;
		for(int j=1;j<=n;j++)ae(s,j,1),ae(j+n,t,1);
		for(int j=1;j<=n;j++)for(int k=i;k<=m;k++)ae(j,(a[j][k]+m-1)/m+n,1);
		dinic();
		for(int j=1;j<=n;j++)for(int k=0;k<nei[j].size();k++)if(nei[j][k].X<=2*n&&!nei[j][k].Y)chs[j]=nei[j][k].X-n;
//		for(int j=1;j<=n;j++)cout<<chs[j]<<"!\n";
		for(int j=1;j<=n;j++)for(int k=i;k<=m;k++)if((a[j][k]+m-1)/m==chs[j]){swap(a[j][i],a[j][k]);break;}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cout<<a[i][j]<<" \n"[j==m];
	for(int j=1;j<=m;j++){
		vector<int> v;
		for(int i=1;i<=n;i++)v.pb(a[i][j]);
		sort(v.begin(),v.end());
		for(int i=1;i<=n;i++)a[i][j]=v[i-1];
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cout<<a[i][j]<<" \n"[j==m];
	return 0;
}
```

---

## 作者：Leasier (赞：1)

考虑倒推，我们希望知道合法的 $b, c$ 需要满足什么条件。

$c$ 显然需要满足每行中包含所有应该在这一行中的元素，则我们其实不关心 $a, b$ 中这些元素的具体信息，不妨将一个 $x$ 染上 $\lceil \frac{x}{m} \rceil$ 这种颜色（或者说是它应该在的行号），则：

- $c$ 中每行颜色相同。
- $b$ 中每列包含所有 $n$ 种颜色。

考虑逐列确定，则我们相当于要做一个二分图匹配。那是否随便取一组匹配就一定能保证有解呢？

注意到如果此前每一步都存在完美匹配，则考虑到第 $i$ 行时左右每个点的度数都恰好为 $m - i + 1$，于是一定存在完美匹配，进而不难归纳证明。

按上述方式求出 $b$ 后不难得出对应的 $c$。时间复杂度为 $O(n^2 m^2)$。

代码：
```cpp
#include <iostream>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt, tm = 0;
int a[107][107], head[107], link[107], vis[107];
Edge edge[10007];

inline void init(int n){
	cnt = 0;
	for (register int i = 1; i <= n; i++){
		head[i] = link[i] = 0;
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

bool dfs(int u){
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (vis[x] != tm){
			vis[x] = tm;
			if (link[x] == 0 || dfs(link[x])){
				link[x] = u;
				return true;
			}
		}
	}
	return false;
}

int main(){
	int n, m;
	cin >> n >> m;
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for (register int i = 1; i <= m; i++){
		init(n);
		for (register int j = 1; j <= n; j++){
			for (register int k = i; k <= m; k++){
				add_edge(j, (a[j][k] - 1) / m + 1);
			}
		}
		for (register int j = 1; j <= n; j++){
			tm++;
			dfs(j);
		}
		for (register int j = 1; j <= n; j++){
			for (register int k = i; k <= m; k++){
				if ((a[link[j]][k] - 1) / m + 1 == j){
					swap(a[link[j]][i], a[link[j]][k]);
					break;
				}
			}
		}
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			for (register int k = i; k <= n; k++){
				if ((a[k][j] - 1) / m + 1 == i){
					swap(a[i][j], a[k][j]);
					break;
				}
			}
		}
	}
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：xht (赞：1)

## [Sorting a Grid](https://atcoder.jp/contests/agc037/tasks/agc037_d)

### 题意

- 给定一个 $n \times m$ 的矩阵，每个位置上的数 $\in[1,nm]$，且每个数恰好出现一次。
- 你可以进行三次操作：
  1. 将每一行重排。
  2. 将每一列重排。
  3. 再将每一行重排。
- 要求最终矩阵被还原为有序矩阵。
- $n,m \le 100$。

### 题解

倒着考虑，第三步会将同一行的打乱，因此同一行的顺序不重要，于是可以将每个数的行数看成它们的颜色。

第二步会将同一列的打乱，因此第二步之前每一列应该恰好每种颜色各有一个。

于是问题变成了，在一个矩阵中有 $n$ 种颜色，每种颜色恰好 $m$ 个，要通过重排每一行，实现每一列恰好每种颜色各一个。

考虑二分图匹配模型，左边为 $n$ 行，右边为 $n$ 种颜色，对于每一行的每种颜色连边，

然后找 $m$ 次最大匹配，将第 $i$ 的匹配作为第 $i$ 列。根据 Hall 定理，每次匹配必然是完美匹配。

使用匈牙利算法时间复杂度为 $\mathcal O(n^2m^2)$。

### 代码

```cpp
const int N = 107;
int n, m, a[N][N], b[N][N], f[N], g[N], v[N], p[N];

bool dfs(int i, int k) {
	for (int j = 1; j <= m; j++)
		if (a[i][j]) {
			int x = (a[i][j] - 1) / m + 1;
			if (v[x] != k) {
				v[x] = k;
				if (!f[x] || dfs(f[x], k))
					return f[x] = i, g[i] = j, 1;
			}
		}
	return 0;
}

int main() {
	rd(n, m);
	for (int i = 1; i <= n; i++)
		rda(a[i], m);
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++)
			dfs(i, (i - 1) * m + (j - 1) + 1);
		for (int i = 1; i <= n; i++)
			b[i][j] = a[i][g[i]], a[i][g[i]] = f[i] = 0;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			print(b[i][j], " \n"[j==m]);
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++)
			p[(b[i][j]-1)/m+1] = b[i][j];
		for (int i = 1; i <= n; i++)
			b[i][j] = p[i];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			print(b[i][j], " \n"[j==m]);
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

可以发现，每一列上数都来自不同行的矩阵都符合 $B$ 矩阵。

现在给每个点按行号染色，即有 $n$ 种颜色各 $m$ 个点，问能否重排每行，使每列颜色互不相同（恰为一组排列）。

可以证明问题一定有解，我们每次从每行取一个元素构成一列，满足颜色互不相同，递归到 $n,m-1$ 的问题。

可以证明总存在这样的取法。假设有 $k$ 种颜色无法一起取到，那么包含这 $k$ 种颜色的行少于 $k$ 个。但一行有 $m$ 个数，$k$ 种颜色共有 $km$ 个点，至少需要 $k$ 行才放得下。反证得证。

一组取法本质是一组 $n$ 个点 $O(nm)$ 条边的完美匹配，上述证明本质是 hall 定理。

最后跑 $m$ 次匈牙利算法得出 $B$，$C$ 容易构造。复杂度 $O(n^2m^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)

const int N = 105;

int n,m,a[N][N],b[N][N],P[N],flg[N];
bool vis[N][N];
vector<int> G[N];

bool dfs(int u,int x){
	if(flg[u] == x) return 0;
	flg[u] = x;
	for(int v : G[u]) if(!P[v] || dfs(P[v],x)) return P[v] = u,1;
	return 0;
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) rep(j,1,m) scanf("%d",a[i] + j);
	rep(j,1,m){
		rep(i,1,n) G[i].clear(),P[i] = flg[i] = 0;
		rep(i,1,n) rep(k,1,m) if(!vis[i][k]) G[(a[i][k] - 1) / m + 1].push_back(i);
		rep(i,1,n) dfs(i,i);
		rep(i,1,n) rep(k,1,m) if(!vis[i][k] && !b[i][j] && (a[i][k] - 1) / m + 1 == P[i]) b[i][j] = a[i][k],vis[i][k] = 1;
	}
	rep(i,1,n) rep(j,1,m) printf("%d%c",b[i][j]," \n"[j == m]);
	rep(i,1,n) rep(j,1,m) a[(b[i][j] - 1) / m + 1][j] = b[i][j];
	rep(i,1,n) rep(j,1,m) printf("%d%c",a[i][j]," \n"[j == m]);
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

需要找出一个策略使得三次操作后的矩阵有序。

发现若在第三次操作后可以使得矩阵变得有序，那么在第三次操作前即第二次操作后每个元素均应当处于正确的行当中。那么我们考虑如何使得元素处于正确的行当中。

发现唯一一次可以更改元素所在行的操作为第二行，但是其只能任意排列一列，也就是所在第二次操作之前矩阵每列的元素应当是所属的行互不相同。

因此我们第一次操作的目的便是为每个元素制定一个合适的列，使得每列中的元素其应属于的行互不相同。

因此我们考虑建出一个二分图：

- 左部点共 $N$ 个点，分别代表初始矩阵的一行；
- 右部点共 $N$ 个点，分别代表最终矩阵的一行；
- 若某个应在第 $y$ 行的元素在初始矩阵的第 $x$ 行，那么建边 $\left(x, y\right)$。

不难发现此图为正则二分图，因此求出该图的最小边染色，颜色相同的边代表的颜色在 $B$ 矩阵的同一列中。

将 $B$ 矩阵的每一列进行排列，使得其每个元素在对应的行出现即可得到 $C$。

复杂度为 $\mathcal{O}(N^2M)$。


---

## 作者：小木虫 (赞：0)

### Preface  
非常好题目，这使我置换环旋转。  
### Problem  
给你一个 $n\times m$ 的网格 $A$，每个格子里有一个 $1$ 到 $n\times m$ 的数，每个数恰好出现一次，现在你可以进行三个操作： 

随意排列 $A$ 的每一行得到网格 $B$。  
随意排列 $B$ 的每一列得到网格 $C$。  
随意排列 $C$ 的每一行得到网格 $D$。  

现在要求 $D$ 的位置 $(i,j)$ 上的数字为 $(i-1)\times m+j$，请你构造合法的 $B$ 与 $C$。  

$n,m\leq 100$。  

### Solution  
我们发现这个题目很怪异，冲突的情况是贪心无法处理的，于是我们考虑对这种图进行匹配。  

仔细观察题目，你发现只要构造出网格 $B$，$C$ 就可以直接构造。  
你还发现，$B$ 中每一列不能有两个数字在 $D$ 中在同一行，你考虑染色，把在 $D$ 中在同一行的所有数字染上同一种颜色，那么 $B$ 的每一列都有 $n$ 种颜色。  

现在我们要分配 $A$ 的每一行使得满足上述条件，你发现如果我们目前只考虑一列的方案，那么我们可以对每一行建出一个节点，每一个颜色建出一个节点，每一行向其包含的颜色连包含次数条边，然后我们求出任意一个最大匹配，若该匹配是完全匹配，则这是一种合法方案。  

现在这个题目还有两个疑点，第一个是如果这种构造方式的匹配并不是完全匹配该怎么办？第二个是我们前面列的匹配是对后面列的匹配有后效性的，有没有可能出现前面的一个匹配使得后面本来一个唯一合法的匹配被删掉了？  

这两个疑问可以通过同一个定理来证明，即 Hall 定理。  

首先，根据 Hall 定理，我们有一个二分图的最大匹配为：  

$$n_1-\max_S(|S|-|N(S)|)$$  

其中，$n_1$，$n_2$ 分别为二分图左右部的点数，$S$ 为左部分中任意一个点集，$N(S)$ 为 $S$ 的邻域。  

我们考虑证明对于任何一次匹配，它一定是完全的，这样我们总体就一定有解，也不必担心后效性问题。  

对于第 $k$ 次匹配，每个左部点都有 $n-k+1$ 条出度，每个右部点都有 $n-k+1$ 条入度。  
考虑选择任何一个左部点集 $S$，它有邻域 $N(S)$。  
若 $|S|>|N(S)|$，则 $N(S)$ 应该至少有 $|S|\times (n-k+1)$ 条入度，但其仅有 $|N(S)|\times (n-k+1)$ 条入度，矛盾，故一定有一个完全匹配。  

实现使用了网络流，时间复杂度 $O((nm)^{1.5})$。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=105;
int n,m,a[N][N];
namespace Graph_Match{
    const int N=2e5+10;
    const int inf=1e9;
    int n1,n2,n,m,s,t,u,v;
    int head[N],cur[N],nxt[N],to[N],del[N],f[N],cnt=-1;
    void add(int u,int v,int w){
    	nxt[++cnt]=head[u];
    	head[u]=cnt;
    	to[cnt]=v;
    	f[cnt]=w;
    }int maxflow,dep[N];
    queue <int> Q;
    bool bfs(){
	    Q.push(s);dep[0]=0;
	    for(int i=0;i<=n;i++)cur[i]=head[i];
	    for(int i=1;i<=n;i++)dep[i]=1e9;
	    while(Q.size()){
		    int u=Q.front();Q.pop();
		    for(int i=head[u];i!=-1;i=nxt[i]){
                if(del[i])continue;
		    	int v=to[i];
		    	if(f[i]==0)continue;
		    	if(dep[v]>dep[u]+1){
		    		dep[v]=dep[u]+1;
		    		Q.push(v);
		    	}
		    }
	    }
        return (dep[n]<1e9);
    }
    int dfs(int u,int limit){
	    if(u==n)return limit;int flow=0;
	    for(int &i=cur[u];i!=-1;i=nxt[i]){
            if(del[i])continue;
		    int v=to[i];
		    if(dep[v]!=dep[u]+1)continue;
		    int p=dfs(v,min(limit,f[i]));
		    flow+=p;limit-=p;
		    f[i]-=p;f[i^1]+=p;
		    if(!limit)return flow;
	    }return flow;
    }
    void DINIC(){
	    maxflow=0;
	    while(bfs())
	    	maxflow+=dfs(s,inf);
    }
    int run(){
        maxflow=0;
        n=n1+n2+1;
        s=0;t=n;
        int L=cnt+1;
        for(int i=1;i<=n1;i++)
            add(s,i,1),add(i,s,0);
        for(int i=1;i<=n2;i++)
            add(i+n1,t,1),add(t,i+n1,0);
        int R=cnt;
        DINIC();
        for(int i=L;i<=R;i++)del[i]=1;
        return maxflow;
    }
}
int id[N][N],vis[N][N],b[N][N],c[N][N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    memset(Graph_Match::head,-1,sizeof(Graph_Match::head));
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>a[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            Graph_Match::add(i,(a[i][j]-1)/m+1+n,1);
            id[i][j]=Graph_Match::cnt;
            Graph_Match::add((a[i][j]-1)/m+1+n,i,0);
        }
    }
    Graph_Match::n1=Graph_Match::n2=n;
    for(int k=1;k<=m;k++){
        Graph_Match::run();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j])continue;
                if(Graph_Match::f[id[i][j]]==0){
                    b[i][k]=a[i][j];
                    Graph_Match::del[id[i][j]]=1;
                    Graph_Match::del[id[i][j]+1]=1;
                    vis[i][j]=1;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            c[(b[i][j]-1)/m+1][j]=b[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            cout<<b[i][j]<<" ";
        cout<<"\n";
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            cout<<c[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}
```


---

## 作者：Cry_For_theMoon (赞：0)

[传送门](https://atcoder.jp/contests/agc037/tasks/agc037_d)

题意洛谷上比我解释的更清楚（）

##### 分析：

这种乱七八糟的排序题，容易想到对元素分类染色。

考虑对元素从小到大分为 $n$ 类，形式化地，$a_{i,j}$ 被染上颜色 $\left\lceil \frac{a_{i,j}}{m}  \right\rceil$，那么显然会有 $n$ 种颜色，每种颜色的元素都恰有 $m$ 个。

染完色后，容易发现，在第一轮行操作后，必须满足每一列里每种颜色的元素恰好出现一次。然后就可以很方便地进行列操作。

所以我们只需要考虑如何分配每一行的元素位置，使得分配结束后每种颜色在每列里都恰好出现一次。这个东西看上去就比最开始看到的排序可做多了。

先说一个容易做错的想法（指我一开始写的构造方案），很快我们就会发现其错误之处并且得到正确解法：

考虑我们枚举颜色 $1\rightarrow n$​，每次确定所有颜色为 $i$​ 的元素的位置。那么容易想到二分图匹配：我们把颜色为 $i$ 的 $m$ 个元素作为左部点，把 $m$ 个列作为右部点。对于第 $u$ 个颜色为 $i$ 的元素 $(r,c)$，我们连 $L(u) \rightarrow R(c)$（$L,R$ 代表左、右部）。求出这个图的一个完美匹配，做 $n$ 次这样的操作，即可求出行操作后的矩阵。

看上去这是没问题的，毕竟题目说了”保证一定有解“。然而当我们（其实只有我）交上去的时候会 WA 13 个点，加点调试信息后很快就会发现在某些轮匹配的时候是会出现不存在完美匹配的。

错误的原因很显然，因为完美匹配有多种选择，所以可能当前我们选的匹配方案，会让后面某些时候不能产生完美匹配。也就是说这个解法是有后效性的。

然后发现我们需要解决一个问题：二分图是否能产生完美匹配。这是 Hall 定理所解决的问题。但是我们仍然不能用 Hall 定理改进上面的算法，这是因为，我们发现其实在这个过程中有 $n$ 张二分图，你要判断后面能否合法，就得判断后面若干张二分图是否合法，这是很麻烦的，同时，注意到，这 $n$ 张二分图还不是独立的，对于第 $i$ 张二分图，就算你当前选的方案令第 $i+1 \sim n$ 张二分图都有完美匹配，但是可能此时的第 $i+1$ 张二分图，不管选什么完美匹配，都会令第 $i+2 \sim n$ 张二分图中的某个不存在完美匹配。所以按照颜色构造的方案被我们否决。

考虑此时一个方向是，我们的构造方案要让最后形成的二分图数量尽可能少，如果不能只有一张，那也得让它们独立。考虑从左往右一列一列构造。第 $i$​ 次构造第 $i$​ 列的结果。那显然共有 $m$​ 张二分图，每次构造一列的时候，把行看作左部点，颜色看作右部点，对于一个元素 $(r,c)$​，我们连 $L(r) \rightarrow R(color(r,c))$​。然后依旧取一个最大匹配。

然后考虑说明此时的正确性。首先发现第 $1$ 轮一定不存在最大匹配。然后，假设 $i \ge 2$，容易发现，第 $i$ 轮的二分图和第 $i-1$ 轮相比每个点的度数都少了 $1$. 进一步发现第 $i$​ 轮的时候每个节点的度数都为 $l=m-i+1$，那么一个集合 $S$ 向外共连出 $l|S|$ 条边，如果分配给 $|T|<|S|$ 个右部点，根据鸽巢原理，$T$ 中必定有一个点度数 $\gt l$。矛盾。所以这种构造方法是成立的。

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=210,ADD=110;
int n,m,a[MAXN][MAXN],color[MAXN][MAXN];
int ret1[MAXN][MAXN],ret2[MAXN][MAXN],vis[MAXN*2],match[MAXN*2],tag[MAXN][MAXN];
vector<pi>bucket[MAXN];
struct Edge{
	int u,v;
}edge[MAXN*MAXN*2];
int first[MAXN*2],next[MAXN*MAXN*2],tot;
void clear(){
	tot=0;
	memset(first,0,sizeof first);
	memset(next,0,sizeof next);
	memset(edge,0,sizeof edge);
}
void addedge(int u,int v){
	edge[++tot]=(Edge){u,v};
	next[tot]=first[u];first[u]=tot;
}
int dfs(int u){
	for(int j=first[u];j;j=next[j]){
		int v=edge[j].v;
		if(vis[v])continue;
		vis[v]=1;
		if(!match[v] || dfs(match[v])){
			match[v]=u;
			return true;
		}
	}
	return false;
}
int main(){
	cin>>n>>m;
	rep(i,1,n){
		rep(j,1,m){
			cin>>a[i][j];
			color[i][j]=(a[i][j]+m-1)/m;
			bucket[color[i][j]].pb(mp(i,j));
		}
	}
	//一列一列确定
	rep(i,1,m){
		clear();
		memset(match,0,sizeof match);
		rep(r,1,n){
			rep(c,1,m){
				if(tag[r][c])continue;
				addedge(r,ADD+color[r][c]);
			}
		}
		rep(j,1,n){
			memset(vis,0,sizeof vis);
			dfs(j);
		}
		rep(x,1,n){
			int r=match[x+ADD]; //从第r行里找到一个颜色为x的 
			rep(c,1,m){if(tag[r][c] || color[r][c]!=x)continue;
				ret1[r][i]=a[r][c];
				tag[r][c]=1;
				break;
			}
		}
	} 
	
	rep(i,1,n){
		rep(j,1,m){
			printf("%d ",ret1[i][j]);
		}
		printf("\n");
	}
	rep(r,1,n){
		rep(c,1,m){
			ret2[(ret1[r][c]+m-1)/m][c]=ret1[r][c];
		}
	}
	rep(i,1,n){
		rep(j,1,m){
			printf("%d ",ret2[i][j]);
		}
		printf("\n");
	}
	return 0;
}

```



---

