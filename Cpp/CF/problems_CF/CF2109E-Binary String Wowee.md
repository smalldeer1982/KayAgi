---
title: "Binary String Wowee"
layout: "post"
diff: 提高+/省选-
pid: CF2109E
tag: ['动态规划 DP']
---

# Binary String Wowee

## 题目描述

Mouf 觉得主题太无聊了，所以他决定这道题不使用任何主题。

给定一个长度为 $n$ 的二进制$^{\text{∗}}$字符串 $s$。你需要精确执行 $k$ 次以下操作：
- 选择一个下标 $i$（$1 \le i \le n$）满足 $s_i = \mathtt{0}$；
- 然后翻转$^{\text{†}}$所有 $s_j$（$1 \le j \le i$）。

你需要计算执行所有 $k$ 次操作的可能方式数量。

由于答案可能非常大，请输出其对 $998\,244\,353$ 取模的结果。

如果在任何步骤中选择的下标不同，则认为两个操作序列是不同的。

$^{\text{∗}}$ 二进制字符串是指仅由字符 $\mathtt{0}$ 和 $\mathtt{1}$ 组成的字符串。

$^{\text{†}}$ 翻转二进制字符是指将其从 $\mathtt{0}$ 变为 $\mathtt{1}$ 或反之。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 100$）。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \le k \le n \le 500$）——分别表示二进制字符串 $s$ 的长度和需要执行操作的次数。

第二行包含一个长度为 $n$ 的二进制字符串 $s$，仅由字符 $\mathtt{0}$ 和 $\mathtt{1}$ 组成。

保证所有测试用例的 $n$ 之和不超过 $500$。

## 输出格式

对于每个测试用例，输出一个整数——表示精确执行 $k$ 次操作的可能方式数量，对 $998\,244\,353$ 取模的结果。


## 说明/提示

**第一个测试用例解释：**
所有可能的操作序列如下：
1. $\mathtt{\color{red}{0}10} \xrightarrow{i = 1} \mathtt{110}$
2. $\mathtt{\color{red}{010}} \xrightarrow{i = 3} \mathtt{101}$

**第二个测试用例解释：**
所有可能的操作序列如下：
1. $\mathtt{\color{red}{0}00} \xrightarrow{i = 1} \mathtt{\color{red}{1}00} \xrightarrow{i = 2} \mathtt{010}$
2. $\mathtt{\color{red}{0}00} \xrightarrow{i = 1} \mathtt{\color{red}{1}00} \xrightarrow{i = 3} \mathtt{011}$
3. $\mathtt{\color{red}{00}0} \xrightarrow{i = 2} \mathtt{\color{red}{11}0} \xrightarrow{i = 3} \mathtt{001}$

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3 1
010
3 2
000
5 4
01001
8 8
11001100
20 20
10010110101101010110
```

### 输出

```
2
3
10
27286
915530405
```

