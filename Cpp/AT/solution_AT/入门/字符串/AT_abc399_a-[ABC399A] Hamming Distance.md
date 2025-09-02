# [ABC399A] Hamming Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc399/tasks/abc399_a

给定正整数 $N$ 以及由小写英文字母组成的长度为 $N$ 的字符串 $S$ 和 $T$。

请计算 $S$ 和 $T$ 的汉明距离。即，求满足以下条件的整数 $i$（$1 \leq i \leq N$）的个数：$S$ 的第 $i$ 个字符与 $T$ 的第 $i$ 个字符不同。


## 说明/提示

### 约束条件

- $1 \leq N \leq 100$
- $N$ 是整数。
- $S$ 和 $T$ 均为由小写英文字母组成的长度为 $N$ 的字符串。

### 样例解释 1

$S$ 和 $T$ 的第 2、5 个字符不同，其余字符相同。因此答案为 2。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
abcarc
agcahc```

### 输出

```
2```

## 样例 #2

### 输入

```
7
atcoder
contest```

### 输出

```
7```

## 样例 #3

### 输入

```
8
chokudai
chokudai```

### 输出

```
0```

## 样例 #4

### 输入

```
10
vexknuampx
vzxikuamlx```

### 输出

```
4```

