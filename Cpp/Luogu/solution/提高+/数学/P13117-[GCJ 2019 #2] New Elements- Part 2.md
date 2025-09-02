# [GCJ 2019 #2] New Elements: Part 2

## 题目描述

**本题的前两段（不包括本段）与“New Elements: Part 1”完全相同。除此之外，两题可以独立解决；你无需阅读或解决其中一题才能理解或解决另一题。**

Muriel 正在探索两种她命名为 Codium 和 Jamarium 的新元素。她尚未能将它们分离出来，但她希望通过间接方法研究它们的一些重要性质，比如它们的原子量。由于 Muriel 只研究 Codium 的单一同位素和 Jamarium 的单一同位素，它们的原子量都是严格正整数。

Muriel 成功合成了 $\mathbf{N}$ 种不同的分子，每种分子都包含至少一个 Codium 原子和至少一个 Jamarium 原子，且不含其他元素。对于每种分子，她都知道其中每种元素的原子数。分子的分子量等于其所含所有原子的原子量之和。

作为第一步，Muriel 按照分子量严格递增的顺序对这些分子进行了排序。现在她想找出 Codium 和 Jamarium 的原子量的所有可能整数取值对，使其与分子的排序一致。由于她知道可能存在多个满足条件的取值对，她希望找到 Codium 原子量最小的那一组。如果有多组 Codium 原子量相同，则选择 Jamarium 原子量最小的那一组。

## 说明/提示

**样例解释**

在样例 1 中，最后两个分子的区别在于多了一个元素的原子。由于多一个 Codium 的分子整体更重，可以推断 Codium 的原子量大于 Jamarium。取 Codium 和 Jamarium 的原子量分别为 2 和 1 时，分子的分子量分别为 $1 \times 2 + 1 \times 1 = 3$，$1 \times 2 + 2 \times 1 = 4$，$2 \times 2 + 1 \times 1 = 5$，满足严格递增的顺序。由于 Codium 更重，2 是 Codium 的最小原子量，1 是 Jamarium 的最小原子量。

设样例 2 中分子的分子量依次为 $a$、$b$、$c$ 和 $d$。根据原子数，有 $d = 2 \times a$ 且 $c = 2 \times b$。由 $a < b$ 可得 $d = 2 \times a < 2 \times b = c$，这意味着不存在一组原子量能使分子的分子量严格递增。

在样例 3 中，分子的原子总数恰好严格递增。因此，令两种元素的原子量都为 1，可以使分子的分子量严格递增。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{N} \leq 10$。
- 对所有 $i \neq j$，$(\mathbf{C_i}, \mathbf{J_i}) \neq (\mathbf{C_j}, \mathbf{J_j})$（所有分子都不同）。

**测试点 1（10 分，可见）**

- 对所有 $i$，$1 \leq \mathbf{C_i} \leq 100$。
- 对所有 $i$，$1 \leq \mathbf{J_i} \leq 100$。

**测试点 2（16 分，隐藏）**

- 对所有 $i$，$1 \leq \mathbf{C_i} \leq 10^9$。
- 对所有 $i$，$1 \leq \mathbf{J_i} \leq 10^9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
1 1
1 2
2 1
4
1 2
2 1
4 2
2 4
3
1 2
1 3
2 3```

### 输出

```
Case #1: 2 1
Case #2: IMPOSSIBLE
Case #3: 1 1```

