# [CERC2015] Looping Labyrinth

## 题目描述

一个$n×m$的矩形，其中每格为路或墙，通过将图案平移来获得迷宫。迷宫是一个大小有限的坐标系，其图案在四个方向上重复。

用整数（包括负整数）表示横纵坐标。向下行数增加，向右列数增加，坐标$(0,0)$处称为原点。特别地，图案的左上角在原点，而右下角在坐标$(n-1,m-1)$。

原点是出口，为了从开始逃离迷宫，我们要从不同的起点到达原点，每一步可向上，下，左或右。对于每个起点，确定是否可以逃离迷宫。

## 样例 #1

### 输入

```
6 9 
..#####.. 
..#...#.. 
......#.. 
..#####.. 
..#...... 
..#...#.. 
5 
1 4 
5 4 
1 -5 
5 -5 
-1000000000 0```

### 输出

```
yes 
no 
no 
yes 
yes```

# 题解

## 作者：x义x (赞：32)

[参考资料](https://yhx-12243.github.io/OI-transit/records/lydsy4437%3Blg4356%3Bgym101480L.html)

[更坏的阅读体验](https://xyix.github.io/posts/?&sortby=id&postname=luogu-4356)

> **题目大意.**
>
> 现在有一个无限大小的格子迷宫，它是由一个已知的 $n\times m$ 的图形无限重复得到的。现在有 $T$ 个格子，请你回答每个格子能否到达格子 $(0,0)$。
>
> $n,m\le 100,T\le 2\times10^5$。

对每个格子我们都可以求出它的**"块坐标"**和**"块内坐标"**，即 $(x,y)=(nx_B+x_I,my_B+y_I)$，下面记为 $(x_B,y_B,x_I,y_I)$。

记格子 $u$ 能到达 $v$ 为 $u\rightarrow v$。箭头只是个符号，其实这是个双向关系。

---

每个块的 $(0,0)$ 是否可达显然是十分重要的，下面进行研究。

我们显然有以下结论：

> **引理 1.**
>
> 若 $(x,y,0,0)\rightarrow(0,0,0,0)$，则 $\forall \lambda,(\lambda x,\lambda y,0,0)\rightarrow(0,0,0,0)$。

> **引理 1 - 证明.**
>
> 对于 $\lambda\ge 0$，$(\lambda x,\lambda y,0,0)\rightarrow((\lambda-1)x,(\lambda-1)y,0,0)\rightarrow\ldots$。
>
> $\lambda\le 0$ 亦然。

> **引理 2.**
>
> 若 $(x_1,y_1,0,0)\rightarrow(0,0,0,0)\leftarrow(x_2,y_2,0,0)$，
>
> 则 $\forall\lambda,\mu,(\lambda x_1+\mu x_2,\lambda y_1+\mu y_2,0,0)\rightarrow(0,0,0,0)$。

> **引理 2 - 证明.** 同上。

仔细一想你会发现，你好像构造不出 $(2,0,0,0)$ 能到达，$(1,0,0,0)$ 却到不了的情况。更进一步我们有如下猜想

> **定理 1.**
>
> 若 $(\lambda x_u,\lambda y_u,0,0)\rightarrow(0,0,0,0)$，则 $(x_u,y_u,0,0)\rightarrow(0,0,0,0)$。

> **定理 1 - 证明.**
>
> （鱼大原文假定路径可被一个连续函数表示，我认为这个证法不算太严谨也不够优美，下文是我自己发现的证法。）
>
> 假如我们一顿走位走到了 $(\lambda x_u,\lambda y_u,0,0)$（这条路径称为 $0$ 路径），那么我们把它移动到 $(x_u,y_u,0,0),(2x_u,2y_u,0,0),\ldots$，这些路径称为 $1,2,...$ 路径。
>
> 如果 $0$ 路径和 $1$ 路径之间相交，那么我们就立刻得出了一条 $(0,0,0,0)\rightarrow(x_u,y_u,0,0)$ 的路径。现在我们来证明，它们真的一定会相交。
>
> 如图，所有的 $0$ 路径构成了一条无限长的城墙。
>
> [图片链接](https://xyix.github.io/images/luogu-4356.png)
>
> 这条城墙把平面分成三个部分：**上面**，**下面** 和 **里面**。不难发现 $1$ 路径如果和 $0$ 路径无交，那就必定完全存在于这三部分之一。不难证明它不可能在里面，要在就在上面或下面，不妨设为上面。
>
> 那么 $2$ 路径在 $1$ 路径的上面，$3$ 路径在 $2$ 路径的的上面，……$\lambda$ 路径在 $\lambda-1$ 路径的上面，自然也就在 $0$ 路径的上面。
>
> ——等等！$\lambda$ 路径难道不就是 $0$ 路径自己吗？！一条路径怎么可能在自己的上面呢？这引出了矛盾，原假设不成立。

有了以上知识储备，我们可以发现，可达的 $(*,*,0,0)$ 构成的集合的形态是极度有限的。

- $\{(0,0,0,0)\}$。最简单的形态。
- $\{(u,v,0,0)\},\gcd(u,v)=1$。即找到了一组可达 $(u,v,0,0)$。
- 如果找到了两组 $(u_1,v_1,0,0),(u_2,v_2,0,0)$，那么不难发现任何一个 $(x,y,0,0)$ 都能被表示（具体证明可以见鱼大的博客），即形态为 $\{(x,y,0,0),x,y\in \mathbb Z\}$。

考虑求解这个"块可达性形态"。我们从 $(0,0,0,0)$ 开始 BFS，限制每个块内坐标至多访问一次，若试图访问多次便说明我们找到了一组 $(u,v)$。这样复杂度是 $O(nm)$ 的，还顺利完成了形态求解的任务。

然后又发现这个形态好像只和 BFS 出的集合有关，换句话说：除了那些根本到不了的点，其他所有点的"块可达性形态"是一样的。直接用相同的做法套就完事了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m;
bool H[105][105];

struct node {
    int xB, yB, xI, yI;
};
node calc(int x, int y) {
    node ans;
    ans.xB = x >= 0 ? (x / n) : ((x + 1) / n - 1);
    ans.yB = y >= 0 ? (y / m) : ((y + 1) / m - 1);
    ans.xI = x - ans.xB * n; assert(ans.xI >= 0 && ans.xI < n);
    ans.yI = y - ans.yB * m;
    return ans;
}

int U = 0, V = 0;
void insert(int nU, int nV) {
    if (U == -998244353) return; // case 2
    if (nU == 0 && nV == 0) return; // meaningless
    if (nU < 0) nU = -nU, nV = -nV;
    else if (nU == 0 && nV < 0) nV = -nV;
    int g = __gcd(nU, abs(nV)); nU /= g, nV /= g;
    if (nU == U && nV == V) return;
    if (U || V)  U = V = -998244353; // case 1 -> case 2
    else U = nU, V = nV; // case 0 -> case 1
}

bool vis[105][105];
pair<int, int> pB[105][105];
bool isvalid(node u) {
    if (H[u.xI][u.yI]) return 0;
    if (!vis[u.xI][u.yI]) {
        vis[u.xI][u.yI] = 1;
        pB[u.xI][u.yI] = make_pair(u.xB, u.yB);
        return 1;
    }
    insert(u.xB - pB[u.xI][u.yI].first, u.yB - pB[u.xI][u.yI].second);
    return 0;
}

int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        char c = getchar();
        while (c != '.' && c != '#') c = getchar();
        for (int j = 0; j < m; j++)
            H[i][j] = c == '#', c = getchar();
    }

    queue<pair<int, int> > Q;
    isvalid((node){0, 0, 0, 0}); Q.push(make_pair(0, 0));
    while (!Q.empty()) {
        pair<int, int> u = Q.front(); Q.pop();
        for (int i = 0; i < 4; i++) {
            int vx = u.first + d[i][0], vy = u.second + d[i][1];
            if (isvalid(calc(vx, vy))) Q.push(make_pair(vx, vy));
        }
    }

    int T; scanf("%d", &T);
    while (T--) {
        int x, y; scanf("%d%d", &x, &y);
        node qaq = calc(x, y);
        if (!vis[qaq.xI][qaq.yI]) { printf("no\n"); continue; }
        if (U == 0 && V == 0) {
            if (qaq.xB != pB[qaq.xI][qaq.yI].first || qaq.yB != pB[qaq.xI][qaq.yI].second)
                printf("no\n");
            else printf("yes\n");
            continue;
        }
        if (U == -998244353 && V == -998244353) {
            printf("yes\n"); continue;
        }
        int nU = qaq.xB - pB[qaq.xI][qaq.yI].first,
            nV = qaq.yB - pB[qaq.xI][qaq.yI].second;
        if (nU == 0 && nV == 0) { printf("yes\n"); continue; }
        if (nU < 0) nU = -nU, nV = -nV;
        else if (nU == 0 && nV < 0) nV = -nV;
        int g = __gcd(nU, abs(nV)); nU /= g, nV /= g;
        if (nU == U && nV == V) { printf("yes\n"); continue; }
        printf("no\n");
    }
}
```


---

