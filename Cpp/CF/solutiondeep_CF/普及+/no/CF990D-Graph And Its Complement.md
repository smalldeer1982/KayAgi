# 题目信息

# Graph And Its Complement

## 题目描述

Given three numbers $ n, a, b $ . You need to find an adjacency matrix of such an undirected graph that the number of components in it is equal to $ a $ , and the number of components in its complement is $ b $ . The matrix must be symmetric, and all digits on the main diagonal must be zeroes.

In an undirected graph loops (edges from a vertex to itself) are not allowed. It can be at most one edge between a pair of vertices.

The adjacency matrix of an undirected graph is a square matrix of size $ n $ consisting only of "0" and "1", where $ n $ is the number of vertices of the graph and the $ i $ -th row and the $ i $ -th column correspond to the $ i $ -th vertex of the graph. The cell $ (i,j) $ of the adjacency matrix contains $ 1 $ if and only if the $ i $ -th and $ j $ -th vertices in the graph are connected by an edge.

A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting this pair of vertices, but adding any other vertex to $ X $ violates this rule.

The complement or inverse of a graph $ G $ is a graph $ H $ on the same vertices such that two distinct vertices of $ H $ are adjacent if and only if they are not adjacent in $ G $ .

## 样例 #1

### 输入

```
3 1 2
```

### 输出

```
YES
001
001
110
```

## 样例 #2

### 输入

```
3 3 3
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 图及其补图

## 题目描述
给定三个数 $n$, $a$, $b$ 。你需要找到一个无向图的邻接矩阵，使得该图的连通分量数量等于 $a$ ，其补图的连通分量数量等于 $b$ 。该矩阵必须是对称的，并且主对角线上的所有数字都必须为零。

在无向图中，不允许存在自环（从一个顶点到其自身的边）。一对顶点之间最多只能有一条边。

无向图的邻接矩阵是一个大小为 $n$ 的方阵，仅由 “0” 和 “1” 组成，其中 $n$ 是图的顶点数，第 $i$ 行和第 $i$ 列对应图的第 $i$ 个顶点。当且仅当图中的第 $i$ 个和第 $j$ 个顶点通过一条边相连时，邻接矩阵的单元格 $(i, j)$ 包含 $1$ 。

连通分量是一组顶点 $X$ ，使得对于该组中的任意两个顶点，图中至少存在一条连接这对顶点的路径，但向 $X$ 中添加任何其他顶点都会违反此规则。

图 $G$ 的补图或逆图是一个在相同顶点上的图 $H$ ，使得 $H$ 中两个不同的顶点相邻当且仅当它们在 $G$ 中不相邻。

## 样例 #1
### 输入
```
3 1 2
```
### 输出
```
YES
001
001
110
```

## 样例 #2
### 输入
```
3 3 3
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这三道题解思路相近，均通过分类讨论来解决问题。核心在于利用图和其补图的性质，根据不同的 $a$、$b$ 取值构造出满足条件的图。难点在于理解图与补图连通分量个数的关系，并据此进行合理构造。

### 所选的题解
- **作者：zmxqs (5星)**
    - **关键亮点**：对图和补图连通分量关系分析全面，不仅指出不同情况是否有解，还给出具体构造方法，代码实现简洁高效，常数小。
    - **个人心得**：强调了输入输出优化，建议使用 `putchar` 而非 `scanf`，且不要使用未开启 `ios` 的 `cin/cout`。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, b;
int main() {
    scanf("%d%d%d", &n, &a, &b);
    if (a > 1 && b > 1) {
        printf("NO\n");
        return 0;
    }
    if (a == 1 && b == 1) {
        if (n == 2 || n == 3) {
            printf("NO\n");
            return 0;
        }
        else {
            printf("YES\n");
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (i == j + 1 || i + 1 == j) {
                        putchar('1');
                    }
                    else {
                        putchar('0');
                    }
                }
                putchar('\n');
            }
            return 0;
        }
    }
    else if (a > 1) {
        printf("YES\n");
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i >= a && j >= a && (i == j + 1 || i + 1 == j)) {
                    putchar('1');
                }
                else {
                    putchar('0');
                }
            }
            putchar('\n');
        }
    }
    else if (b > 1) {
        printf("YES\n");
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j) {
                    putchar('0');
                }
                else if (i >= b && j >= b && (i == j + 1 || i + 1 == j)) {
                    putchar('0');
                }
                else {
                    putchar('1');
                }
            }
            putchar('\n');
        }
    }
    return 0;
}
```
核心实现思想：根据不同的 $a$、$b$ 取值情况，分别构造邻接矩阵。若 $a>1$ 且 $b>1$ 输出 `NO`；若 $a = 1$ 且 $b = 1$ 且 $n\neq2,3$ 构造一条链；若 $a>1$ 让前 $a - 1$ 个点独立，$a$ 到 $n$ 个点组成一条链；若 $b>1$ 则先按 $a>1$ 构造，再取反边。

- **作者：lmy_2011 (4星)**
    - **关键亮点**：思路清晰，简洁地阐述了根据 $a$、$b$ 不同取值分类构造图的方法，将 $a$ 为 $1$ 的情况转化为 $b$ 为 $1$ 的情况处理。
```cpp
// 未提供完整代码，思路为：
// b为1的情况，将图分成a块，前a - 1块都只有一个节点，最后1块包含剩下节点
// a为1的情况，把它当作b为1的情况，再将输出反过来
// a与b均为1的情况，n为2或3时输出NO，否则输出YES
```
核心实现思想：根据 $a$、$b$ 取值分类构造图，$b = 1$ 时按特定方式分块；$a = 1$ 时转化为 $b = 1$ 情况并取反输出；$a = b = 1$ 时特殊判断 $n$ 的值。

- **作者：ttq012 (4星)**
    - **关键亮点**：简洁明了地进行分类讨论，每种情况给出了具体构造方式，明确指出时间复杂度。
```cpp
// 未提供完整代码，思路为：
// 若a>1且b>1则无解
// 若a = 1且b = 1，n∈{2,3}无解，否则构造i→i + 1这样一条链
// 若a>1且b = 1，令a = 1且b>1讨论，构造让前b - 1个点全都不连边，b到n个点中任意两个点都相互连边
```
核心实现思想：对不同的 $a$、$b$ 取值情况分别处理，判断是否有解并给出构造方法。

### 最优关键思路或技巧
通过对图和补图连通分量个数关系的深入分析进行分类讨论，利用特定的点连接方式（如链、独立点集等）构造满足条件的图，同时注意输入输出优化以提高效率。

### 同类型题或类似算法套路拓展
此类题目通常围绕图的性质和构造展开，关键在于掌握图和补图的基本概念与性质，通过分类讨论，依据给定条件合理构造图的结构。

### 洛谷推荐题目
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及图的连通性和点的分配问题，与本题类似，需根据条件构造图结构。
- [P1129 驾车旅行](https://www.luogu.com.cn/problem/P1129)：结合图论与模拟，通过分析图中节点关系解决实际问题，锻炼对图结构的理解与应用。
- [P1999 高维正方体](https://www.luogu.com.cn/problem/P1999)：从简单图形构造拓展到高维图形，考验对图形构造和规律探索的能力，与本题构造图的思想类似。 

---
处理用时：62.12秒