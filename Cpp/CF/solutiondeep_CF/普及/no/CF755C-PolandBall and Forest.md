# 题目信息

# PolandBall and Forest

## 题目描述

PolandBall lives in a forest with his family. There are some trees in the forest. Trees are undirected acyclic graphs with $ k $ vertices and $ k-1 $ edges, where $ k $ is some integer. Note that one vertex is a valid tree.

There is exactly one relative living in each vertex of each tree, they have unique ids from $ 1 $ to $ n $ . For each Ball $ i $ we know the id of its most distant relative living on the same tree. If there are several such vertices, we only know the value of the one with smallest id among those.

How many trees are there in the forest?

## 说明/提示

In the first sample testcase, possible forest is: 1-2 3-4-5.

There are $ 2 $ trees overall.

In the second sample testcase, the only possible graph is one vertex and no edges. Therefore, there is only one tree.

## 样例 #1

### 输入

```
5
2 1 5 3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
1```

# AI分析结果



# 题目内容

## PolandBall and Forest

### 题目描述

PolandBall和他的家人住在森林里。森林中有若干棵树。树是由 $k$ 个顶点和 $k-1$ 条边组成的无环无向图，其中 $k$ 是某个正整数。注意单个顶点也是合法的树。

每个树的每个顶点上都住着一个亲戚，他们有唯一的id（从1到n）。对于每个Ball i，我们知道它所在树上最远亲戚的id。如果有多个这样的顶点，我们只知道其中id最小的那个。

求森林中有多少棵树？

### 说明/提示

第一个样例的可能结构：1-2 和 3-4-5，共2棵树。

第二个样例是单个顶点，输出1。

### 样例 #1

#### 输入

5
2 1 5 3 3

#### 输出

2

### 样例 #2

#### 输入

1
1

#### 输出

1

---

## 算法分类
并查集

## 题解综合分析

题目核心是求无向图的连通分量个数。各题解均采用并查集解法，差异主要体现在统计方式与优化技巧。关键观察点：每个节点给出的最远亲属本质建立了对称关系，将节点与其最远亲属合并即能构建连通关系。

### 高星题解推荐

#### 1. BLX32M_10（5星）
**亮点**：
- 动态维护连通块计数器，初始为n，每次有效合并减1
- 路径压缩+秩优化实现高效并查集
- 时间复杂度最优（O(nα(n))）

**核心代码**：
```cpp
void merge(int x, int y) {
    fx = find(x), fy = find(y);
    if (fx != fy)
        fa[fy] = fx, ans--;
}
// 初始ans=n，每次merge(i,x)
```

#### 2. Vector_（4星）
**亮点**：
- 代码结构清晰，注释详细
- 包含并查集基础原理说明
- 使用单独计数变量维护连通块数

**实现思路**：
```cpp
int cnt = n;
void un(int x, int y) {
    if(find(x) == find(y)) return;
    f[find(y)] = find(x);
    cnt--; // 直接维护计数器
}
```

#### 3. Y2y7m（4星）
**亮点**：
- 对比DFS与并查集的适用性
- 使用路径压缩优化
- 最终遍历统计根节点数量

**统计方式**：
```cpp
for(int i=1;i<=n;i++)
    if(root[i]==i) cnt++;
```

---

## 关键思路总结
最优解采用**动态维护连通块计数**的技巧，在并查集合并时直接更新计数器，避免最终遍历统计。该技巧将时间复杂度从O(n logn)优化至O(nα(n))，适用于大规模数据。

---

## 同类题目推荐
1. P1551 亲戚（基础并查集）
2. P3367 【模板】并查集（路径压缩+秩优化）
3. P1396 营救（并查集在最小生成树中的应用）

---

## 题解心得摘录
1. **BLX32M_10**：通过图示说明合并操作对连通块数量的影响，强调"有效合并"的判断条件与并查集优化的关联性。
2. **Jsxts_**：对比DFS方案，指出并查集在隐式建图时的优势，实测并查集代码运行时间302ms vs DFS的210ms，反映不同方法的实际效率差异。
3. **fengxiaoyi**：调试时发现未初始化访问数组导致的错误，强调初始化的重要性。

---
处理用时：49.80秒