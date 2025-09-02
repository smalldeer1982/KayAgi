# フクロモモンガ  (Sugar Glider)

## 题目描述

有 $ n $ 棵树，第 $ i $ 棵树高 $ h_i $ 米，一只小鼠初始位于 $ 1 $ 号树 $ X $ 高度。现有 $ m $ 条航线，表示从 $ u_i $ 号树飞到 $ v_i $ 号树需要 $ t_i $ 秒（是双向边！），飞行过程中它离地面的高度会每秒下降 $ 1 $ 米，小鼠必须保证飞到 $ v_i $ 号树时不会高于树，也不会低于地面，它可以通过在 $ u_i $ 号树上以一米每秒的速度向上（向下）奔波完成！现在它需要到 $ n $ 号树的最高处，请你求出最短时间，不能到达输出 $ -1 $ 。  $ n,m\le 10^5~;~h_i,X,t_i\le 10^9 $ 


接下来 $N$ 行中，第 $i(1\le i\le N)$ 行有一个整数 $H_{i}$，表示树木$i$的高度是 $H_{i}$ 米。

接下来 $M$ 行中，第 $j(1\le j\le M)$ 行有三个以空格分开的整数 $A_{j},B_{j},T_{j}$ $(1\le A_{j}, B_{j}\le N,$ $A_{j}\ne B_{j})$，表示小鼠能花 $T_{j}$ 秒的时间从 $A_{j}$ 飞到 $B_{j}$ 或从 $B_{j}$ 飞到 $A_{j}$。  

对于任意 $1\le j < k\le M$，满足 $(A_{j},B_{j})\neq (A_{k},B_{k})$ 且 $(A_{j},B_{j})\neq (B_{k},A_{k})$。

## 说明/提示

下列是其中一种最优解：

1. 沿着树木 $1$ 向上爬 $50$ 米。
1. 从树木 $1$ 飞到树木 $2$。
1. 从树木 $2$ 飞到树木 $4$。
1. 从树木 $4$ 飞到树木 $5$。
1. 沿着树木 $5$ 向上爬 $10$ 米。

### 输入样例 2
```plain
2 1 0
1
1
1 2 100
```

### 输出样例 2
```plain
-1
```

### 样例解释 2

小鼠无法从树木 $1$ 飞到树木 $2$。

### 输入样例 3
```plain
4 3 30
50
10
20
50
1 2 10
2 3 10
3 4 10
```

### 输出样例 3
```plain
100
```

全部的输入数据满足：

- $2\le N\le 100000$
- $1\le M\le 300000$
- $1\le H_{i}\le 10^{9}(1\le i\le N)$
- $1\le T_{j}\le 10^{9}(1\le j\le M)$
- $0\le X\le H_{1}$

#### 子任务 1（25 分）

满足以下条件：

- $N\le 1000$
- $M\le 3000$
- $H_{i}\le 100(1\le i\le N)$
- $T_{j}\le 100(1\le j\le M)$

#### 子任务 2（25 分）

满足 $X=0$。

#### 子任务 3（50 分）

没有额外限制。

## 样例 #1

### 输入

```
5 5 0
50
100
25
30
10
1 2 10
2 5 50
2 4 20
4 3 1
5 4 20```

### 输出

```
110```

## 样例 #2

### 输入

```
2 1 0
1
1
1 2 100```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 3 30
50
10
20
50
1 2 10
2 3 10
3 4 10```

### 输出

```
100```

# 题解

## 作者：WAAutoMaton (赞：2)

[先宣传一下博客（逃](https://waautomaton.tk/2018/08/12/loj-2759-%E9%A2%98%E8%A7%A3/)

#### 题解

&emsp;&emsp;首先有一个结论：一定存在一个最优解使得对于任意可在X时间内到达的点，从起点到这个点的路程中不向上爬；对于大于X时间的部分，一定不向下爬。  
&emsp;&emsp;所以我们只需要知道到某一个点的最短时间，即可确定到这个点时飞天鼠在树上的高度，这个高度是唯一的（在满足上面的结论的情况下），并且这个状态有一个优秀的性质——若s到t的最短路经过了k，则其中s到k的路径一定是s到k的最短路径。又因为整个过程“边权”都是非负的，所以我们可以用dijkstra算法求出最短路（即最优解）。若使用stl的优先队列总复杂度$O((n+m)logm)$  
&emsp;&emsp;注意到这里我们的实际“边权”依赖于端点的最短路的值，因此边权实际上是在做dij时动态计算的。  

#### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

template <size_t _I_Buffer_Size = 1 << 23, size_t _O_Buffer_Size = 1 << 23>
struct IO_Tp
{
    //这是读入优化板子，为了阅读体验此部分内容省略。
};
 IO_Tp<> IO;
const int maxn = 100000;
const int maxm = 300000;
struct Edge
{
    int to, next, w;
} e[2 * maxm + 10];
int head[maxn + 10];
void addEdge(int a, int b, int w)
{
    static int c = 0;
    e[++c] = (Edge){ b, head[a], w };
    head[a] = c;
	e[++c]=(Edge){a,head[b],w};
	head[b]=c;
}
int a[maxn + 10];
int n, m, beg;
struct Data
{
    int p;
    LL dis;
    Data(int p, LL dis)
        : p(p)
        , dis(dis)
    {
    }
};
bool operator<(const Data &a, const Data &b)
{
    return a.dis > b.dis;
}
LL dis[maxn + 10];
const LL inf = LLONG_MAX / 10;
void dijkstra(int s, int t)
{
    priority_queue<Data> q;
    fill(dis + 1, dis + 1 + n, inf);
    q.push(Data(s, 0));
    dis[s] = 0;
    while (!q.empty()) {
        Data now = q.top();
        q.pop();
        if (now.dis != dis[now.p])
            continue;
        int u = now.p;
        for (int i = head[u]; i != 0; i = e[i].next) {
            LL ndis;
            int v = e[i].to;
			if (a[u]<e[i].w) continue;
            if (dis[u] < beg) {
                LL h = beg - dis[u];
                if (h - e[i].w > a[v]) {
                    ndis = beg - a[v];
                } else if (h - e[i].w >= 0) {
                    ndis = dis[u] + e[i].w;
                } else {
                    ndis = dis[u] + e[i].w + (e[i].w - h);
                }
            } else {
                ndis = dis[u] + 2 * e[i].w;
            }
            if (ndis < dis[v]) {
                dis[v] = ndis;
                q.push(Data(v, ndis));
            }
        }
    }
}
int main()
{
    iopen();
    IO >> n >> m >> beg;
    for (int i = 1; i <= n; ++i) {
        IO >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        int a, b, w;
        IO >> a >> b >> w;
        addEdge(a, b, w);
    }
    dijkstra(1, n);
    if (dis[n] == inf) {
        puts("-1");
    } else {
        LL d = dis[n];
        LL ans;
        if (d < beg) {
            LL h = beg - d;
            ans = d + (a[n] - h);
        } else {
            ans = d + a[n];
        }
        IO << ans << '\n';
    }
    return 0;
}


```

---

