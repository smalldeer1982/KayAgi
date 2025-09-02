# [GCJ Farewell Round #3] Game Sort: Part 2

## 题目描述

注意：问题 **Game Sort: Part 1** 和 **Game Sort: Part 2** 的题目描述主要部分相同，仅最后一段不同。这两个问题可以独立解决。

**Amir** 和 **Badari** 正在玩一个排序游戏。游戏开始时，一位公正的裁判会选择一个字符串 $\mathbf{S}$ 和一个整数 $\mathbf{P}$。然后，**Amir** 需要将 $\mathbf{S}$ 分割成恰好 $\mathbf{P}$ 个连续的非空部分（子字符串）。例如，如果选中的字符串是 $\mathbf{S} = \text{CODEJAM}$ 且 $\mathbf{P} = 3$，**Amir** 可以将其分割为 $[\text{COD}, \text{EJA}, \text{M}]$ 或 $[\text{CO}, \text{D}, \text{EJAM}]$，但不能分割为 $[\text{COD}, \text{EJAM}]$、$[\text{COD}, \text{JA}, \text{M}]$、$[\text{EJA}, \text{COD}, \text{M}]$ 或 $[\text{CODE}, \text{EJA}, \text{M}]$。

接着，**Badari** 必须重新排列每个部分的字母，使得这些部分按字典序非递减顺序排列。如果她能成功，则她获胜；否则，**Amir** 获胜。

给定初始字符串和分割数量，你能帮助 **Amir** 通过选择一种 **Badari** 无法获胜的分割方式来赢得游戏吗？如果不可能，请说明无法实现。

## 说明/提示

**样例解释**

在样例 #1 中，**Badari** 无法将 $\text{DEJAM}$ 重新排列为字典序大于 $\text{O}$ 的字符串，因此 **Amir** 确保了胜利。

在样例 #2 中，$\text{AAA}$ 的字典序必然小于任何包含超过 3 个字母的字符串的重排结果，因此 **Amir** 也获胜。

在样例 #3 中，所有可能的分割方式都会使得部分列表已经按字典序排列，因此 **Amir** 无法获胜。

**限制**

- $1 \leq \mathbf{T} \leq 100$。
- $\mathbf{S}$ 的每个字符均为大写字母 A 到 Z。

**测试集 1（8 分，可见评测结果）**

- $2 \leq \mathbf{P} \leq 3$。
- $\mathbf{P} \leq \mathbf{S} \text{ 的长度} \leq 100$。

**测试集 2（20 分，隐藏评测结果）**

- $2 \leq \mathbf{P} \leq 100$。
- $\mathbf{P} \leq \mathbf{S} \text{ 的长度} \leq 10^5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
3 CODEJAM
2 ABABABABAAAA
3 AABBCDEEFGHIJJKLMNOPQRRSTUVWXYZZ```

### 输出

```
Case #1: POSSIBLE
C O DEJAM
Case #2: POSSIBLE
ABABABABA AAA
Case #3: IMPOSSIBLE```

