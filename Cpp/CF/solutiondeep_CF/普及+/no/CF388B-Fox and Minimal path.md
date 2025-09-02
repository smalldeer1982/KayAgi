# 题目信息

# Fox and Minimal path

## 题目描述

Fox Ciel wants to write a task for a programming contest. The task is: "You are given a simple undirected graph with $ n $ vertexes. Each its edge has unit length. You should calculate the number of shortest paths between vertex 1 and vertex 2."

Same with some writers, she wants to make an example with some certain output: for example, her birthday or the number of her boyfriend. Can you help her to make a test case with answer equal exactly to $ k $ ?

## 说明/提示

In first example, there are 2 shortest paths: 1-3-2 and 1-4-2.

In second example, there are 9 shortest paths: 1-3-6-2, 1-3-7-2, 1-3-8-2, 1-4-6-2, 1-4-7-2, 1-4-8-2, 1-5-6-2, 1-5-7-2, 1-5-8-2.

## 样例 #1

### 输入

```
2```

### 输出

```
4
NNYY
NNYY
YYNN
YYNN```

## 样例 #2

### 输入

```
9```

### 输出

```
8
NNYYYNNN
NNNNNYYY
YNNNNYYY
YNNNNYYY
YNNNNYYY
NYYYYNNN
NYYYYNNN
NYYYYNNN```

## 样例 #3

### 输入

```
1```

### 输出

```
2
NY
YN```

# AI分析结果

### 题目内容
# Fox and Minimal path

## 题目描述

Fox Ciel想要为一场编程竞赛编写一道题目。题目是：“给定一个具有$n$个顶点的简单无向图。其每条边的长度为1。你需要计算顶点1和顶点2之间的最短路径数量。”

和一些出题者一样，她想用某个特定的输出制作一个示例：例如，她的生日或者她男朋友的电话号码。你能帮助她制作一个测试用例，使其答案恰好等于$k$吗？

## 说明/提示

在第一个示例中，有2条最短路径：1 - 3 - 2和1 - 4 - 2。

在第二个示例中，有9条最短路径：1 - 3 - 6 - 2，1 - 3 - 7 - 2，1 - 3 - 8 - 2，1 - 4 - 6 - 2，1 - 4 - 7 - 2，1 - 4 - 8 - 2，1 - 5 - 6 - 2，1 - 5 - 7 - 2，1 - 5 - 8 - 2。

## 样例 #1

### 输入

```
2
```

### 输出

```
4
NNYY
NNYY
YYNN
YYNN
```

## 样例 #2

### 输入

```
9
```

### 输出

```
8
NNYYYNNN
NNNNNYYY
YNNNNYYY
YNNNNYYY
YNNNNYYY
NYYYYNNN
NYYYYNNN
NYYYYNNN
```

## 样例 #3

### 输入

```
1
```

### 输出

```
2
NY
YN
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过对$k$进行二进制拆分，利用二进制的特性来构造满足从顶点1到顶点2有$k$条最短路径的图。主要难点在于如何构造出$2^m$种走法的子图，并将这些子图拼接起来，同时保证最短路长度相同且点数满足要求。不同题解在具体构造方式和优化程度上有所差异。有的题解构造出的图点数为$O(\log^2k)$，在处理较大的$k$时可能会超出点数限制；而有的题解通过将补齐的链合并等方式优化到了$O(\log k)$的点数，提高了效率。

### 所选的题解
- **作者：XiangyuHu (5星)**
    - **关键亮点**：思路清晰，先给出$k = 2^m$情况的构造，再通过二进制拆分拼接子图解决一般情况，且考虑到题目对点数更苛刻要求时的优化构造，代码简洁明了。
    - **重点代码及核心思想**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
bool G[1010][1010];
void addEdge(int u, int v) {
    G[u][v] = G[v][u] = 1;
}
int main() {
    scanf("%d", &k);
    int used = 6;
    for (int i = 2, tmp = 2; tmp <= k; i++, tmp <<= 1) {
        addEdge(i * 3 + 1, i * 3 - 1); // 建 2^(i - 1) 的方案数的点
        addEdge(i * 3 + 1, i * 3 - 2);
        addEdge(i * 3 + 2, i * 3 - 1);
        addEdge(i * 3 + 2, i * 3 - 2);
        addEdge(i * 3, i * 3 + 3); // 建额外链的点、边
        if (k & tmp) {
            addEdge(i * 3 + 3, i * 3 + 2); // 建从 2^(i - 1) 汇方案数的边
        }
        used = i * 3 + 3;
    }
    addEdge(3, 4); addEdge(3, 5); // 建开始的两条边
    if (k & 1) {
        addEdge(5, 6); // 特殊处理之前没有处理的情况
    }
    addEdge(1, 3); // 连从 1 到 3 的边
    addEdge(2, used); // 将路径数转移到 2
    printf("%d\n", used);
    for (int i = 1; i <= used; i++) {
        for (int j = 1; j <= used; j++) {
            printf(G[i][j]? "Y" : "N");
        }
        printf("\n");
    }
    return 0;
}
```
核心思想是通过循环构建每个$2^{i - 1}$方案数的点及连接边，根据$k$的二进制位决定是否连接到额外链上，最后输出图的点数和邻接矩阵。
- **作者：Imiya (4星)**
    - **关键亮点**：通过逐步优化构造图的方式，从最初点数较多的构造，到通过合并补层数的点等操作，将点数优化到$3\times\lfloor\log k\rfloor + 2$，有效减少点数，且配图辅助理解，思路较清晰。
    - **重点代码及核心思想**：
```cpp
#include<iostream>
using namespace std;
const int N = 1000;
int k, a[N], b[N], c[N], t = 2, h = 30;
bool g[N][N];
int main() {
    cin >> k;
    if (k == 1) {
        printf("2\nNY\nYN");
        return 0;
    }
    for (;!((1 << h) & k); h--); //求图的层数
    for (int i = 1; i <= h; i++)a[i] = ++t; //按优先从上到下，其次从右到左的顺序对每个点编号
    for (int i = 1; i <= h; i++)b[i] = ++t;
    for (int i = 1; i <= h; i++)c[i] = ++t;
    g[a[1]][1] = g[1][a[1]] = true; //对1,2点连别
    g[b[1]][1] = g[1][b[1]] = true;
    if (k & 1)g[c[1]][1] = g[1][c[1]] = true;
    g[a[h]][2] = g[2][a[h]] = true;
    g[b[h]][2] = g[2][b[h]] = true;
    g[c[h]][2] = g[2][c[h]] = true;
    for (int i = 1; i < h; i++) {
        g[a[i]][a[i + 1]] = g[b[i]][b[i + 1]] = g[c[i]][c[i + 1]] = true; //每一列从上到下连边
        g[a[i + 1]][a[i]] = g[b[i + 1]][b[i]] = g[c[i + 1]][c[i]] = true;
        g[a[i]][b[i + 1]] = g[b[i]][a[i + 1]] = true; //右边两列交叉连别
        g[b[i + 1]][a[i]] = g[a[i + 1]][b[i]] = true;
        if (k & (1 << i))g[c[i + 1]][a[i]] = g[a[i]][c[i + 1]] = g[c[i + 1]][b[i]] = g[b[i]][c[i + 1]] = true; //上文中的合并
    }
    cout << t << endl;
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= t; j++)printf("%c", g[i][j]? 'Y' : 'N');
        putchar('\n');
    }
    return 0;
}
```
核心思想是先确定图的层数，然后对每层的点进行编号，通过对$k$的二进制位判断来连接不同层的点，实现满足条件的图的构造，最后输出图的点数和邻接矩阵。
- **作者：hexu2010 (4星)**
    - **关键亮点**：解析过程详细，通过建层连边构造出距离源点为$2^i$条最短路的节点，再建链拉边将这些节点连接起来，思路清晰，代码实现逻辑明确。
    - **重点代码及核心思想**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; w *= (ch == '-')? -1 : 1, ch = getchar());
    for (; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
    return s * w;
}
const int MAXN = 1005;
bool G[MAXN][MAXN];
void add(int u, int v) {
    G[u][v] = G[v][u] = 1;
}
signed main() {
    int k = read(), s = log2(k);
    add(1, 3), add(1, 4);
    for (int i = 1; i <= s; i++) {
        add(i * 2 + 1, i * 2 + 3);
        add(i * 2 + 1, i * 2 + 4);
        add(i * 2 + 2, i * 2 + 3);
        add(i * 2 + 2, i * 2 + 4);
    }
    for (int i = 1; i <= s; i++) {
        add(2 * s + 4 + i, 2 * s + i + 5);
    }
    add(3 * s + 4, 2);
    for (int i = 0; i <= s; i++) {
        if ((k & (1 << i)) == 0) continue;
        if (i == s) add(2 * i + 4, 2);
        else add(2 * i + 4, 2 * s + i + 5);
    }
    cout << 3 * s + 4 << endl;
    for (int i = 1; i <= 3 * s + 4; i++) {
        for (int j = 1; j <= 3 * s + 4; j++) {
            cout << (G[i][j]? "Y" : "N");
        }
        puts("");
    }
    return 0;
}
```
核心思想是先通过循环构建每层节点间的边，再构建链上的边，根据$k$的二进制位决定从特定节点到链上对应节点的连接，最后输出图的点数和邻接矩阵。

### 最优关键思路或技巧
1. **二进制拆分**：将$k$进行二进制拆分，通过构造从顶点1到某些节点有$2^i$条最短路的子图，再根据二进制位拼接这些子图，实现从顶点1到顶点2有$k$条最短路的图的构造。
2. **优化点数**：通过将用于补齐最短路长度的链合并等方式，减少图的点数，从$O(\log^2k)$优化到$O(\log k)$，使构造的图能满足题目对点数的限制。

### 可拓展之处
同类型题通常围绕图的构造，要求满足特定的路径数量、距离等条件。类似算法套路是利用数的进制特性（如二进制、十进制等）来构造子结构，再组合成满足要求的图。例如，可能会要求构造图满足特定的最长路径数量、不同顶点对之间的特定路径关系等。

### 洛谷相似题目
1. **P1331 海战**：通过构造特定的图结构来模拟海战场景，判断船只分布是否符合要求，涉及图的构造与条件判断。
2. **P1469 找筷子**：利用异或运算（与二进制相关）的特性来解决问题，与本题利用二进制特性构造图有相似的思维方式。
3. **P2676 超级书架**：通过构造合适的数据结构和算法来满足书籍选择的特定条件，与本题构造图满足特定路径数量条件类似，都需要根据题目要求设计合适的解决方案。 

---
处理用时：114.81秒