# [GCJ 2016 #1B] Technobabble

## 题目描述

每年，你的教授都会在她的门上贴出一张空白的报名表，用于一个极具声望的科学研究会议。如果有学生想在会议上做报告，他们需要选择一个尚未被写在表上的“两词话题”，并把它写到表上。截止日期过后，教授会让她的一位研究生将这些话题随机排序，以避免对先报名或后报名的学生产生偏见。然后，她会把这些话题提交给你审核。

由于会议上的点心非常美味，有些学生会试图“造假”混进会议。他们会选择表上已有话题中的某个首词，以及另一个话题的末词，将这两个词拼接（首词在前，末词在后）来创造一个新的“话题”（只要它还不在表上）。由于你的教授思想开放，这种策略有时真的能成功！

这些造假者毫无原创性，无法自己想出新的首词或末词；他们只能用表上已经出现过的词。此外，他们不会把某个已作为首词出现的词用作自己的末词（除非该词也已经作为末词出现过），反之亦然。

你拿到了一份包含所有 $\mathbf{N}$ 个已提交话题的列表，顺序随机；你并不知道它们在表上的实际书写顺序。请你计算，最多有多少个话题可能是造假的？


## 说明/提示

在样例第 1 组中，一种可能的顺序是：
```
QUAIL BEHAVIOR（真实）
HYDROCARBON COMBUSTION（真实）
QUAIL COMBUSTION（造假）
```

无论如何安排顺序，都不可能让超过一个话题为造假。

在样例第 2 组中，所有话题都必须是真实的。无论它们被写入表格的顺序如何，都无法在某一步用已有的词拼出一个新话题且不与已有话题重复。

在样例第 3 组中，任何话题都不能为造假。例如，如果 `INTERGALACTIC PLANETARY` 是第一个且唯一写在表上的话题，造假者只能用 `INTERGALACTIC` 作为新话题的首词，`PLANETARY` 作为新话题的末词……但唯一能拼出的组合就是 `INTERGALACTIC PLANETARY`，而它已在表上，不能再用。因此 `PLANETARY INTERGALACTIC` 也必须是真实话题。

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- 每个词的长度 $1 \leqslant \text{length} \leqslant 20$。
- 每组数据中无重复话题。

**小数据集（14 分，测试集 1 - 可见）**

- $1 \leqslant \mathbf{N} \leqslant 16$。

**大数据集（30 分，测试集 2 - 隐藏）**

- $1 \leqslant \mathbf{N} \leqslant 1000$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
3
3
HYDROCARBON COMBUSTION
QUAIL BEHAVIOR
QUAIL COMBUSTION
3
CODE JAM
SPACE JAM
PEARL JAM
2
INTERGALACTIC PLANETARY
PLANETARY INTERGALACTIC```

### 输出

```
Case #1: 1
Case #2: 0
Case #3: 0```

