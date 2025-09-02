# [CERC 2022] Differences

## 题目描述

我们有一个包含 $N$ 个字符串 $S_i$ 的列表。所有字符串长度均为 $M$，且只包含字符 A、B、C 和 D。我们定义两个字符串 $X$ 和 $Y$ 之间的距离为它们在所有下标 $j$ 处字符不同的个数（即 $X_j \neq Y_j$ 的下标数量）。已知在这些字符串中，恰好有一个特殊字符串，它与其他所有字符串的距离均为 $K$。注意，可能存在其他字符串对之间的距离也为 $K$。我们在寻找这个特殊字符串时遇到了困难，请你编写程序帮助我们找到它。

## 说明/提示

### 输入限制

- $2 \leq N, M \leq 10^5$
- $1 \leq K \leq M$
- $NM \leq 2 \cdot 10^7$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 10 2
DCDDDCCADA
ACADDCCADA
DBADDCCBDC
DBADDCCADA
ABADDCCADC```

### 输出

```
4```

## 样例 #2

### 输入

```
4 6 5
AABAAA
BAABBB
ABAAAA
ABBAAB```

### 输出

```
2```

