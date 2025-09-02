---
title: "[ABC409D] String Rotation"
layout: "post"
diff: 普及/提高-
pid: AT_abc409_d
tag: []
---

# [ABC409D] String Rotation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc409/tasks/abc409_d

给定一个长度为 $N$ 的由小写字母组成的字符串 $S=S_1S_2\dots S_N$。你需要对 $S$ 执行恰好一次以下操作：

- 选择 $S$ 的一个长度至少为 1 的连续子串，将其向左循环移位 1 次。具体来说，选择整数 $1 \leq \ell \leq r \leq N$，将 $S$ 的第 $\ell$ 个字符插入到第 $r$ 个字符的右侧，然后删除 $S$ 的第 $\ell$ 个字符。

请找出所有可能的操作后 $S$ 中字典序最小的字符串。

共有 $T$ 个测试用例，请对每个测试用例给出答案。

## 输入格式

输入通过标准输入给出，格式如下：

> $T$  
> $\mathrm{case}_1$  
> $\mathrm{case}_2$  
> $\vdots$  
> $\mathrm{case}_T$

每个测试用例 $\mathrm{case}_i$（$1 \leq i \leq T$）的格式如下：

> $N$  
> $S$


## 输出格式

输出 $T$ 行。第 $i$ 行（$1 \leq i \leq T$）输出 $\mathrm{case}_i$ 对应的答案。


## 说明/提示

### 约束条件

- $1 \leq T \leq 10^5$
- $1 \leq N \leq 10^5$
- $S$ 是由小写字母组成的长度为 $N$ 的字符串
- $T$ 和 $N$ 为整数
- 单个输入文件中所有测试用例的 $N$ 之和不超过 $10^5$

### 样例解释 1

- 对于第 1 个测试用例，选择第 2 到第 7 个字符进行循环移位，得到 `acodert` 是字典序最小的结果。
- 对于第 2 个测试用例，无论如何操作都只能得到 `x`。
- 对于第 3 个测试用例，选择第 1 到第 2 个字符进行循环移位，得到 `nsuke` 是字典序最小的结果。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
7
atcoder
1
x
5
snuke
```

### 输出

```
acodert
x
nsuke
```

