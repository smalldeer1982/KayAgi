# [ABC284A] Sequence of Strings

## 题目描述

给定 $N$ 个字符串 $S_1,S_2,\ldots,S_N$，按照这个顺序给出。

请按照 $S_N,S_{N-1},\ldots,S_1$ 的顺序输出这些字符串。

## 说明/提示

### 限制条件

- $1\leq N\leq 10$
- $N$ 是整数
- $S_i$ 是由英文字母大小写和数字组成的字符串，长度在 $1$ 到 $10$ 之间

### 样例解释 1

$N=3$，$S_1=$ `Takahashi`，$S_2=$ `Aoki`，$S_3=$ `Snuke`。因此，按照 `Snuke`、`Aoki`、`Takahashi` 的顺序输出。

### 样例解释 2

给定的字符串中也可能包含数字。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
Takahashi
Aoki
Snuke```

### 输出

```
Snuke
Aoki
Takahashi```

## 样例 #2

### 输入

```
4
2023
Year
New
Happy```

### 输出

```
Happy
New
Year
2023```

