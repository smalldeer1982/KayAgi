# [GCJ 2018 #1B] Mysterious Road Signs

## 题目描述

Signfield 镇位于一条完全笔直且无限延伸的东西向公路上。在这条公路上，依次排列着 $\mathbf{S}$ 个神秘的路标，每个路标的两面都写有数字。第 $i$ 个路标（从西到东编号）位于 Signfield 东侧 $\mathbf{D}_{\mathbf{i}}$ 公里处，其西侧写有数字 $\mathbf{A}_{\mathbf{i}}$，东侧写有数字 $\mathbf{B}_{\mathbf{i}}$。

Signfield 的居民都不知道这些路标想表达什么。你认为，路标西侧的数字是给向东行驶的司机看的，代表到某个特定目的地的距离。同理，你认为路标东侧的数字是给向西行驶的司机看的，也代表到某个特定目的地的距离。不过，你怀疑并不是所有路标都与这个理论一致。

为了验证你的理论，你希望找到满足以下规则的有效路标集合：

- 该集合是所有路标序列的一个连续子序列（整个序列也算作连续子序列）。
- 存在两个位置 $\mathrm{M}$ 和 $\mathrm{N}$（均为 Signfield 东侧的公里数，$\mathrm{M}$ 和 $\mathrm{N}$ 不一定为正数，也不一定不同），使得对于该集合中的每一个路标，至少满足下列条件之一：
    - $\mathbf{D}_{\mathbf{i}}+\mathbf{A}_{\mathbf{i}}=\mathrm{M}$。
    - $\mathbf{D}_{\mathbf{i}}-\mathbf{B}_{\mathbf{i}}=\mathrm{N}$。

请你求出满足上述条件的有效集合中，包含路标数量的最大值，以及有多少个不同的有效集合达到该最大值。

## 说明/提示

**样例解释**

在样例 1 中，只有一个路标。如果我们只选择这个路标作为集合，有很多可能的 $\mathrm{M}$ 和 $\mathrm{N}$ 组合都是可行的，例如：

- $\mathrm{M}=2$，$\mathrm{N}=0$
- $\mathrm{M}=1$，$\mathrm{N}=0$（注意每个路标只需满足其中一个条件；$\mathrm{M}$ 和 $\mathrm{N}$ 可以与某些路标或 Signfield 重合）
- $\mathrm{M}=2$，$\mathrm{N}=-12345$（$\mathrm{N}$ 可以在 Signfield 西侧）
- $\mathrm{M}=0$，$\mathrm{N}=0$（$\mathrm{M}$ 和 $\mathrm{N}$ 不一定不同）
- $\mathrm{M}=2$，$\mathrm{N}=3$（$\mathrm{N}$ 可以在 $\mathrm{M}$ 东侧）

因此，只包含该路标的集合是有效的。该长度的集合只有一个，所以答案是 1 1。

在样例 2 中，注意第 1、2、4、5 个路标在 $\mathrm{M}=9$ 和 $\mathrm{N}=-1$ 时是成立的，但它们不是连续子序列（第 3 个路标的背面数字不能当作正面用）。实际上，没有包含 4 个路标的有效集合。有两个不同的包含 3 个路标的有效集合。注意，虽然第二个集合有两组不同的 $\mathrm{M}/\mathrm{N}$ 组合可以使其成立，但该集合只计数一次：

- 第 1、2、3 个路标，$\mathrm{M}=9$，$\mathrm{N}=7$
- 第 3、4、5 个路标，$\mathrm{M}=18$，$\mathrm{N}=-1$ 或 $\mathrm{M}=22$，$\mathrm{N}=7$

在样例 3 中，整个序列是一个有效集合，$\mathrm{M}=4$，$\mathrm{N}=2$。

**数据范围**

- $1 \leqslant \mathbf{T} \leqslant 60$。
- $1 \leqslant \mathbf{D}_{\mathbf{i}} \leqslant 10^{6}$，对所有 $i$。
- $\mathbf{D}_{\mathbf{i}}<\mathbf{D}_{\mathbf{j}}$，对所有 $i<j$。
- $1 \leqslant \mathbf{A}_{\mathbf{i}} \leqslant 10^{6}$，对所有 $i$。
- $1 \leqslant \mathbf{B}_{\mathbf{i}} \leqslant 10^{6}$，对所有 $i$。

**测试点 1（10 分，公开）**

- 所有测试用例 $1 \leqslant \mathbf{S} \leqslant 100$。

**测试点 2（20 分，隐藏）**

- 除 3 个测试用例外，所有测试用例 $1 \leqslant \mathbf{S} \leqslant 100$。
- 有 3 个测试用例 $\mathbf{S}=10^{5}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1
1 1 1
5
2 7 12
6 3 11
8 10 1
11 11 12
13 9 14
5
1 3 3
2 2 2
3 1 1
4 2 2
5 3 3```

### 输出

```
Case #1: 1 1
Case #2: 3 2
Case #3: 5 1```

