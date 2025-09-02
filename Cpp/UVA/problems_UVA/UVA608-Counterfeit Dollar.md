---
title: "Counterfeit Dollar"
layout: "post"
diff: 普及/提高-
pid: UVA608
tag: []
---

# Counterfeit Dollar

## 题目描述

有 $12$ 枚硬币 $\texttt A \sim \texttt L$，其中有 $1$ 枚是假币。

假币和真币**重量不同**，但不知道假币比真币重还是轻。

现在用一架天平秤 $3$ 次，告诉你结果：

1. $\texttt{up}$：右边高；
2. $\texttt{down}$：右边低；
3. $\texttt{even}$：平衡。

保证天平左右硬币个数**总是相等**。

## 输入格式

**本题在单测试点内有多组测试数据。**

第一行一个正整数 $n$ 表示测试数据组数。

## 输出格式

共 $n$ 行，每一行输出哪一枚是假币，并说明它比真币轻还是重。

- 若轻输出 `XXX is the counterfeit coin and it is light.`
- 若重输出 `XXX is the counterfeit coin and it is heavy.`

## 样例 #1

### 输入

```
1
ABCD EFGH even
ABCI EFJK up
ABIJ EFGH even
```

### 输出

```
K is the counterfeit coin and it is light.
```

