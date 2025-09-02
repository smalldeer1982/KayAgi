# 题目信息

# [USACO07MAR] Ranking the Cows G

## 题目描述

Each of Farmer John's N cows (1 ≤ N ≤ 1,000) produces milk at a different positive rate, and FJ would like to order his cows according to these rates from the fastest milk producer to the slowest.

FJ has already compared the milk output rate for M (1 ≤ M ≤ 10,000) pairs of cows. He wants to make a list of C additional pairs of cows such that, if he now compares those C pairs, he will definitely be able to deduce the correct ordering of all N cows. Please help him determine the minimum value of C for which such a list is possible.

FJ想按照奶牛产奶的能力给她们排序。现在已知有N头奶牛（1 ≤ N ≤ 1,000）。FJ通过比较，已经知道了M（1 ≤ M ≤ 10,000）对相对关系。每一对关系表示为“X Y”，意指X的产奶能力强于Y。现在FJ想要知道，他至少还要调查多少对关系才能完成整个排序。


## 说明/提示

From the information in the 5 test results, Farmer John knows that since cow 2 > cow 1 > cow 5 and cow 2 > cow 3 > cow 4, cow 2 has the highest rank. However, he needs to know whether cow 1 > cow 3 to determine the cow with the second highest rank. Also, he will need one more question to determine the ordering between cow 4 and cow 5. After that, he will need to know if cow 5 > cow 3 if cow 1 has higher rank than cow 3. He will have to ask three questions in order to be sure he has the rankings: "Is cow 1 > cow 3?  Is cow 4 > cow 5? Is cow 5 > cow 3?"


## 样例 #1

### 输入

```
5 5
2 1
1 5
2 3
1 4
3 4```

### 输出

```
3```

# AI分析结果



**算法分类**: 图论（传递闭包）

---

### 综合分析与结论
本题核心是计算有向图的传递闭包，统计已知关系后求出剩余需确定的关系对。关键难点在于高效处理大规模节点（N=1000）的传递闭包计算，需采用 bitset 优化或拓扑排序策略。

---

### 精选题解与亮点

#### 1. panyf 的题解（5星）
- **关键亮点**：提供四种传递闭包实现方法，对比清晰。其中 bitset 优化的 Floyd 版本代码简洁，复杂度 $O(n^3/w)$，实测高效。
- **核心代码**：
  ```cpp
  for(int k=1; k<=n; ++k)
      for(int i=1; i<=n; ++i)
          if(b[i][k]) 
              b[i] |= b[k];
  ```
  利用 bitset 的位运算特性，批量更新可达性。

#### 2. zhzh2001 的题解（5星）
- **关键亮点**：从组合数学角度分析问题，明确传递闭包的作用，对比 Floyd 与拓扑排序的适用场景。代码兼顾可读性与效率。
- **核心思路**：拓扑排序后按逆序合并可达集合，复杂度 $O(nm/w)$，适合稀疏图。

#### 3. Mine_King 的题解（4星）
- **关键亮点**：详细解释拓扑排序与 bitset 的结合原理，给出完整注释代码，适合萌新理解。
- **个人心得**：强调传递闭包的链式结构特性，直观说明问题本质。

---

### 最优思路总结
**核心技巧**：使用 bitset 优化的 Floyd 算法，将可达性判断转化为位运算，大幅降低时间复杂度。具体步骤：
1. 初始化邻接矩阵。
2. 三重循环中，若 `i` 可达 `k`，则将 `i` 的可达集合与 `k` 的可达集合合并。
3. 统计所有已知关系，总对数减去已知数即为答案。

---

### 相似题目推荐
1. [P1613 跑路](https://www.luogu.com.cn/problem/P1613)（利用传递闭包优化路径计算）
2. [P4308 [CTSC2011] 幸福路径](https://www.luogu.com.cn/problem/P4308)（动态规划结合传递闭包）
3. [P2419 [USACO08JAN]Cow Contest S](https://www.luogu.com.cn/problem/P2419)（传递闭包确定排名可能性）

---
处理用时：41.93秒