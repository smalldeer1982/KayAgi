# [ABC394B] cat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_b

给定 $N$ 个由小写字母组成的字符串 $S_1, S_2, \ldots, S_N$，其中所有字符串的长度互不相同。

请将这些字符串按长度升序排列，并按此顺序拼接后输出结果字符串。

## 说明/提示

### 约束条件

- $2 \leq N \leq 50$
- $N$ 为整数
- $S_i$ 是长度介于 $1$ 到 $50$ 之间的由小写字母组成的字符串
- 当 $i \neq j$ 时，$S_i$ 和 $S_j$ 的长度不同

### 样例解释 1

将（`tc`, `oder`, `a`）按字符串长度升序排列后得到（`a`, `tc`, `oder`）。将这些字符串按顺序拼接后得到字符串 `atcoder`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
tc
oder
a```

### 输出

```
atcoder```

## 样例 #2

### 输入

```
4
cat
enate
on
c```

### 输出

```
concatenate```

