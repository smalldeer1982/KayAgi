# 矩阵解压 Matrix Decompressing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2023

[PDF](https://uva.onlinejudge.org/external/110/p11082.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/4bfbadba5826e7df25fe35bb6c563f54e80f8b54.png)

## 样例 #1

### 输入

```
2
3 4
10 31 58
10 20 37 58
3 4
10 31 58
10 20 37 58```

### 输出

```
Matrix 1
1 6 1 2
1 2 2 16
8 2 14 3
Matrix 2
1 1 1 7
1 1 7 12
8 8 9 2```

# 题解

## 作者：_liet (赞：8)

下面是紫书P374给出的解法：

这里我们首先根据题中给出的数据计算每一行和每一列的数字和 $RowSum[i], ColSum[i]$，然后建立行与列的二分图，每一行与每一列分别相连，容量为 $19$，然后让源点 $s$ 与每一行相连，容量为 $RowSum[i] - C$；每一列与汇点 $t$ 相连，容量为 $ColSum[i] - R$。建完图之后跑一遍最大流，当从 $s$ 出发的边和汇聚到 $t$ 的边都是满载时，从第 $i$ 行到第 $j$ 列的边的流量 $+ 1$ 就是 $matrix[i][j]$ 的值。

---------

上述方法的正确性，我是这么理解的：

$s$ 到每一行的边的流量相当于每一行的数字和，每一列到 $t$ 的边的流量相当于每一列的数字和，所以只有当这些边都满载时才能满足数据给出的条件；

第 $i$ 行到第 $j$ 列的流量代表的是第 $i$ 行的第 $j$ 个位置给 $ColSum[j]$ 贡献的数量，也就是 $matrix[i][j]$ 的值；

另外因为 $matrix[i][j]\in[1, 20]$，所以为了防止算出的边的流量为 $0$，所以事先将矩阵中的每个数 $- 1$，然后最后输出的时候再加回来。

-----

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#define INF 999999999
#define MAXN 30
#define MAXVERTEX 100
using namespace std;
typedef long long ll;

struct Edge {
    int from, to, cap, flow;

    Edge(int u = 0, int v = 0, int c = 0, int f = 0):
        from(u), to(v), cap(c), flow(f) {}
};

int edges;
vector<Edge> edge;
vector<int> g[MAXVERTEX];
int a[MAXVERTEX], p[MAXVERTEX];

void init(int n) {
    for (int i = 0; i < n; i++)
        g[i].clear();
    edge.clear();
}

void add(int from, int to, int cap) {
    edge.push_back(Edge(from, to, cap, 0));
    edge.push_back(Edge(to, from, 0, 0));
    edges = edge.size();
    g[from].push_back(edges - 2);
    g[to].push_back(edges - 1);
}

// 求最大流常规操作
int maxflow(int s, int t) {
    int flow = 0;
    while (true) {
        memset(a, 0, sizeof(a));
        queue<int> q;
        q.push(s);
        a[s] = INF;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < g[x].size(); i++) {
                Edge& e = edge[g[x][i]];
                if (!a[e.to] && e.cap > e.flow) {
                    p[e.to] = g[x][i];
                    a[e.to] = min(a[x], e.cap - e.flow);
                    q.push(e.to);
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) break;
        for (int u = t; u != s; u = edge[p[u]].from) {
            edge[p[u]].flow += a[t];
            edge[p[u]^1].flow -= a[t];
        }
        flow += a[t];
    }
    return flow;
}

int row[MAXN], col[MAXN];
int r, c;

// 输入数据
void input() {
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; i++) {
        scanf("%d", &row[i]);
    }
    for (int i = 0; i < c; i++) {
        scanf("%d", &col[i]);
    }

    // 把 row 和 col 设定成单独该行和该列的和
    for (int i = r - 1; i > 0; i--) {
        row[i] -= row[i - 1];
    }
    for (int i = c - 1; i > 0; i--) {
        col[i] -= col[i - 1];
    }
}

// 连边
void link() {
    // 把行与列相连，行的节点是从 0 到 r，列的节点是 r 到 r + c
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            add(i, j + r, 19);
        }
    }

    // 把 s = r + c 与行相连
    for (int i = 0; i < r; i++) {
        add(r + c, i, row[i] - c);
    }

    // 把列与 t = r + c + 1 相连
    for (int i = 0; i < c; i++) {
        add(i + r, r + c + 1, col[i] - r);
    }
}

int main() {
    int t;

    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        // 两个 cases 之间需要输出空行
        if (i != 1) printf("\n");

        input();
        init(r + c + 2);
        link();

        maxflow(r + c, r + c + 1);
        printf("Matrix %d\n", i);
        // 输出边的流量 + 1 就是答案
        for (int j = 1; j <= r * c; j++) {
            printf("%d%c", edge[(j - 1) * 2].flow + 1, j % c == 0 ? '\n' : ' ');
        }
    }

    return 0;
}
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

因该是还有什么神奇的解法，不然 $20$ 的数值上限确实不算大。

考虑使用网络流求解。当我们将 $A_{i,j}$ 设为 $v$ 的时候，可以理解为从 $RowSum(i)=\sum_{j=1}^mA_{i,j}$ 中分配了 $v$ 到 $ColumnSum(j)=\sum_{i=1}^nA_{i,j}$ 中。

也就是说我们实际上就是将每一行的“流量”分配到每一列上。显然有解的前提下这些流量会全部从行流向列。

所以我们从原点向行建边，上限就是这一行的和，随后从列向汇点建边，下限就是这一列的和。有解的情况下，网络流一定能给我们构造出来一组解。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node { int p, v, nt; }e[40005]; int h[2005], cne;
inline void ins(int l, int r, int v) {
	e[++cne].nt = h[l]; e[cne].p = r; e[cne].v = v; h[l] = cne;
	e[++cne].nt = h[r]; e[cne].p = l; e[cne].v = 0; h[r] = cne;
}
int qp, n, m, k, s, t, d[2005], tp, th[2005], ans[25][25]; queue<int>q;
inline bool bfs() {
	memset(d, 0, sizeof d);
	d[s] = 1; q.emplace(s);
	while (q.size()) {
		tp = q.front(); q.pop();
		for (int i = h[tp], sp; i; i = e[i].nt)
			if (!d[sp = e[i].p] && e[i].v)
				d[sp] = d[tp] + 1, q.emplace(sp);
	}
	return d[t];
}
inline int dfs(int p, int fs) {
	if (p == t || !fs) return fs; int ret = 0;
	for (int& i = th[p], sp, v; i; i = e[i].nt)
		if (d[sp = e[i].p] == d[p] + 1 && (v = dfs(sp, min(fs - ret, e[i].v)))) {
			ret += v; e[i].v -= v; e[i ^ 1].v += v;
			if (ret == fs) return ret;
		}
	return ret;
}
signed main() {
	ios::sync_with_stdio(0); cin >> qp;
	for (int c = 1; c <= qp; ++c) {
		memset(h, 0, sizeof h); cne = 1;
		cin >> n >> m; s = n + m + 1, t = s + 1;
		for (int i = 1, a = 0, b; i <= n; ++i)
			cin >> b, b -= a, a += b, ins(s, i, b - m);
		for (int i = 1, a = 0, b; i <= m; ++i)
			cin >> b, b -= a, a += b, ins(i + n, t, b - n);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				ins(i, j + n, 19);
		while (bfs())
			memcpy(th, h, sizeof h),
			dfs(s, 1e8);
		cout << "Matrix " << c << endl;
		for (int i = 1; i <= n; i++)
			for (int j = h[i]; j; j = e[j].nt)
				if (e[j].p > n && e[j].p <= n + m)
					ans[i][e[j].p - n] = e[j].v;
		for (int i = 1; i <= n; ++i, cout << endl)
			for (int j = 1; j <= m; ++j)
				cout << 20 - ans[i][j] << " ";
	}
}
```

---

