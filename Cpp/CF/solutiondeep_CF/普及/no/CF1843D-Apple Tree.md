# 题目信息

# Apple Tree

## 题目描述

Timofey has an apple tree growing in his garden; it is a rooted tree of $ n $ vertices with the root in vertex $ 1 $ (the vertices are numbered from $ 1 $ to $ n $ ). A tree is a connected graph without loops and multiple edges.

This tree is very unusual — it grows with its root upwards. However, it's quite normal for programmer's trees.

The apple tree is quite young, so only two apples will grow on it. Apples will grow in certain vertices (these vertices may be the same). After the apples grow, Timofey starts shaking the apple tree until the apples fall. Each time Timofey shakes the apple tree, the following happens to each of the apples:

Let the apple now be at vertex $ u $ .

- If a vertex $ u $ has a child, the apple moves to it (if there are several such vertices, the apple can move to any of them).
- Otherwise, the apple falls from the tree.

It can be shown that after a finite time, both apples will fall from the tree.

Timofey has $ q $ assumptions in which vertices apples can grow. He assumes that apples can grow in vertices $ x $ and $ y $ , and wants to know the number of pairs of vertices ( $ a $ , $ b $ ) from which apples can fall from the tree, where $ a $ — the vertex from which an apple from vertex $ x $ will fall, $ b $ — the vertex from which an apple from vertex $ y $ will fall. Help him do this.

## 说明/提示

In the first example:

- For the first assumption, there are two possible pairs of vertices from which apples can fall from the tree: $ (4, 4), (5, 4) $ .
- For the second assumption there are also two pairs: $ (5, 4), (5, 5) $ .
- For the third assumption there is only one pair: $ (4, 4) $ .
- For the fourth assumption, there are $ 4 $ pairs: $ (4, 4), (4, 5), (5, 4), (5, 5) $ .

 ![](https://espresso.codeforces.com/7c6d16e8362e76df883e925d30296fb28360d590.png) Tree from the first example.For the second example, there are $ 4 $ of possible pairs of vertices from which apples can fall: $ (2, 3), (2, 2), (3, 2), (3, 3) $ . For the second assumption, there is only one possible pair: $ (2, 3) $ . For the third assumption, there are two pairs: $ (3, 2), (3, 3) $ .

## 样例 #1

### 输入

```
2
5
1 2
3 4
5 3
3 2
4
3 4
5 1
4 4
1 3
3
1 2
1 3
3
1 1
2 3
3 1```

### 输出

```
2
2
1
4
4
1
2```

## 样例 #2

### 输入

```
2
5
5 1
1 2
2 3
4 3
2
5 5
5 1
5
3 2
5 3
2 1
4 2
3
4 3
2 1
4 2```

### 输出

```
1
2
1
4
2```

# AI分析结果

### 题目重写
Timofey在他的花园里种了一棵苹果树；它是一棵有 $n$ 个顶点的有根树，根在顶点 $1$（顶点的编号从 $1$ 到 $n$）。给出的图没有重边与自环。

这棵苹果树相当年轻，所以只有两个苹果会在上面生长。苹果会在某些顶点上生长（这些顶点可能是相同的）。苹果长出来后，Timofey开始摇晃苹果树，直到苹果掉下来。每次Timofey摇动苹果树时，每个苹果都会发生以下情况：

设苹果现在在顶点 $u$。如果顶点 $u$ 有一个子节点，苹果就会移动到它那里（如果有几个这样的顶点，苹果可以移动到其中任何一个）。否则，苹果会从树上掉下来。

Timofey有 $q$ 个假设，苹果可以在哪些顶点生长。他假设苹果可以在顶点 $x$ 和 $y$ 中生长，并想知道苹果可以从树上掉下来的顶点对 $(a,b)$ 的数量、其中 $a$ 为顶点 $x$ 的苹果会落下的顶点，$b$ 为顶点 $y$ 的苹果会落下的顶点。帮助他做到这一点。

### 算法分类
深度优先搜索 DFS、树形 DP

### 题解分析与结论
题解的核心思路是通过深度优先搜索（DFS）来计算每个节点的子树中叶子节点的数量，然后根据乘法原理，将两个节点的叶子节点数量相乘得到结果。所有题解都采用了这一思路，但在实现细节和代码优化上有所不同。

### 所选高分题解
#### 1. 作者：Dream__Sky (4星)
**关键亮点**：
- 使用DFS遍历树，计算每个节点的子树中叶子节点的数量。
- 通过度数组判断叶子节点，避免了额外的判断逻辑。
- 代码简洁明了，易于理解。

**核心代码**：
```cpp
int dfs(int x, int f) {
    if (du[x] == 1 && x != 1) { a[x] = 1; return a[x]; }
    for (int i = 0; i < v[x].size(); i++) {
        if (v[x][i] == f) continue;
        a[x] += dfs(v[x][i], x);
    }
    return a[x];
}
```

#### 2. 作者：Coffee_zzz (4星)
**关键亮点**：
- 使用DFS计算每个节点的子树中叶子节点的数量。
- 强调了`long long`的使用，避免了溢出问题。
- 代码结构清晰，注释详细。

**核心代码**：
```cpp
void dfs(int u, int f) {
    int v;
    if (deg[u] == 1 && f != 0) {
        val[u] = 1;
        return;
    }
    for (int i = head[u]; i; i = nxt[i]) {
        v = to[i];
        if (v == f) continue;
        dfs(v, u);
        val[u] = val[u] + val[v];
    }
}
```

#### 3. 作者：Wf_yjqd (4星)
**关键亮点**：
- 使用DFS计算每个节点的子树中叶子节点的数量。
- 通过快读优化输入，提高了代码效率。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
void dfs(int x, int fa) {
    for (int i = head[x]; i; i = e[i].ne) {
        if (e[i].to == fa) continue;
        dfs(e[i].to, x);
        f[x] += f[e[i].to];
    }
    if (!f[x]) f[x] = 1;
}
```

### 最优关键思路
通过DFS遍历树，计算每个节点的子树中叶子节点的数量，然后根据乘法原理，将两个节点的叶子节点数量相乘得到结果。注意使用`long long`避免溢出。

### 拓展思路
类似的问题可以通过DFS或BFS遍历树，计算子树的性质，如叶子节点数量、子树大小等。这类问题通常涉及到树的基本性质和遍历算法。

### 推荐题目
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014)
3. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

---
处理用时：28.05秒