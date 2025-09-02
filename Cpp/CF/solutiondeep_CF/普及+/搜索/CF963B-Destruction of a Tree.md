# 题目信息

# Destruction of a Tree

## 题目描述

You are given a tree (a graph with $ n $ vertices and $ n-1 $ edges in which it's possible to reach any vertex from any other vertex using only its edges).

A vertex can be destroyed if this vertex has even degree. If you destroy a vertex, all edges connected to it are also deleted.

Destroy all vertices in the given tree or determine that it is impossible.

## 说明/提示

In the first example at first you have to remove the vertex with index 1 (after that, the edges (1, 2) and (1, 4) are removed), then the vertex with index 2 (and edges (2, 3) and (2, 5) are removed). After that there are no edges in the tree, so you can remove remaining vertices in any order.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF963B/9b84e98fe96447b82c6a8ccba7a9e4a5189ce14b.png)

## 样例 #1

### 输入

```
5
0 1 2 1 2
```

### 输出

```
YES
1
2
3
5
4
```

## 样例 #2

### 输入

```
4
0 1 2 3
```

### 输出

```
NO
```

# AI分析结果



### 题目内容重写

# 树的销毁

## 题目描述

给定一棵包含 $n$ 个顶点的树（无环连通图）。当一个顶点的度数为偶数时，可以删除该顶点及其相连的所有边。要求判断能否按此规则删除所有顶点，若能则输出删除顺序。

## 说明/提示

样例1中，先删除度为2的顶点1，导致其相邻边被删除。此时顶点2的度数变为2（边2-3和2-5），继续删除顶点2，最终剩余无边的顶点可任意顺序删除。

## 样例 #1

### 输入
```
5
0 1 2 1 2
```

### 输出
```
YES
1
2
3
5
4
```

---

### 综合题解分析

#### 核心结论
1. **奇偶性判断**：当 $n$ 为偶数时直接无解（边数 $n-1$ 为奇数，每次删除偶数边，最终必剩奇数边）。
2. **递归子树处理**：从叶子向根遍历，优先删除偶数度的最深层节点（DFS序或后序遍历），保证父节点删除后不影响子树。
3. **状态转移方程**：用异或运算维护子树删除逻辑（如 `f[u] = (⊕f[son]) ⊕ 1`）。

---

### 精选题解（评分≥4星）

#### 1. [作者：7KByte] ⭐⭐⭐⭐⭐
**关键亮点**  
- **异或状态压缩**：用 $f[u]$ 表示是否保留父边，通过异或运算快速判断子树奇偶性。
- **线性时间复杂度**：仅需两次 DFS，无复杂数据结构。
- **代码简洁性**：核心逻辑仅 20 行，递归输出顺序清晰。

**核心代码片段**  
```cpp
void dfs(int x,int fa){
    for(int i=h[x];i;i=e[i].nxt)
        if(e[i].to!=fa) dfs(e[i].to,x),f[x]^=f[e[i].to];
    f[x]^=1;
}
void calc(int x,int fa){
    for(int i=h[x];i;i=e[i].nxt)
        if(e[i].to!=fa&&f[e[i].to]) calc(e[i].to,x);
    printf("%d\n",x);
    for(int i=h[x];i;i=e[i].nxt)
        if(e[i].to!=fa&&!f[e[i].to]) calc(e[i].to,x);
}
```

---

#### 2. [作者：妹子啦] ⭐⭐⭐⭐
**关键亮点**  
- **DFS序贪心**：用栈实现后序遍历，确保优先删除最深层节点。
- **度数动态更新**：删除节点后实时更新相邻节点度数，避免重复计算。
- **边界处理完善**：单独处理度数为0的叶节点。

**核心代码片段**  
```cpp
void dfs1(int x,int f){ // 生成DFS序栈
    sta.push(x);
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        if(v != f) dfs1(v,x);
    }
}
void dfs2(int x){ // 按顺序删除偶数度节点
    ans[++num] = x;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        deg[v]--;
        if(!(deg[v] & 1)) dfs2(v);
    }
}
```

---

#### 3. [作者：_鱼非仙_] ⭐⭐⭐⭐
**关键亮点**  
- **树形DP设计**：定义状态 $f(u)$ 表示父节点删除顺序需求。
- **拓扑序构造**：通过有向边建立删除依赖关系，保证输出顺序合法。
- **数学严谨性**：证明异或运算的合法性（奇偶性守恒）。

**核心公式**  
$$f(u) = \left( \bigoplus_{v \in \text{son}(u)} f(v) \right) \oplus 1$$

---

### 关键思路总结
1. **奇偶剪枝**：优先判断 $n$ 的奇偶性，$n$ 为偶直接返回 `NO`。
2. **后序优先删除**：通过 DFS 后序遍历或栈结构，保证深层节点先被处理。
3. **状态异或运算**：用异或维护子树删除逻辑，避免复杂计数。

---

### 拓展练习（洛谷题号）
1. **P1352 没有上司的舞会**（树形DP基础）  
2. **P3379 最近公共祖先**（DFS遍历与树结构处理）  
3. **P1040 加分二叉树**（树形结构与递归优化）

---
处理用时：63.23秒