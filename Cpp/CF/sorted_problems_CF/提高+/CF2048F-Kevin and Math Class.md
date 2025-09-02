---
title: "Kevin and Math Class"
layout: "post"
diff: 提高+/省选-
pid: CF2048F
tag: ['动态规划 DP', '树形 DP', '笛卡尔树']
---

# Kevin and Math Class

## 题目描述

Kevin 是来自 Eversleeping Town 的一名学生，他正在参加一门数学课，老师正在给他出一些除法练习题。

在黑板上，有两行正整数，每行包含 $n$ 个数字。第一行是 $a_1, a_2, \ldots, a_n$，第二行是 $b_1, b_2, \ldots, b_n$。

对于每个除法练习题，Kevin 可以选择任何一个区间 $[l, r]$，并在 $b_l, b_{l+1}, \ldots, b_r$ 中找到最小的值 $x$。然后他将修改 $l \leq i \leq r$ 范围内的每个 $a_i$，使得每个 $a_i$ 被 $x$ 除后的结果向上取整。

更正式地，他选择两个整数 $1 \leq l \leq r \leq n$，设 $x = \min_{l \leq i \leq r} b_i$，然后将所有 $l \leq i \leq r$ 范围内的 $a_i$ 修改为 $ \lceil \frac{a_i}{x} \rceil$。

Kevin 只有当所有 $a_i$ 都变为 1 时，才能离开教室回家。他非常渴望回家，想知道实现这一目标所需的最小除法练习次数。

## 输入格式

每个测试案例包含多个测试用例。第一行是测试用例的数量 $t$（$1 \le t \le 10^4$）。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示数列 $a$ 和 $b$ 的长度。

接下来的一行是 $n$ 个整数 $a_1, a_2, \ldots, a_n$，表示黑板上的第一行数字。

接下来的一行是 $n$ 个整数 $b_1, b_2, \ldots, b_n$，表示黑板上的第二行数字。

保证所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数 —— 达成目标所需的最小除法练习次数。

## 说明/提示

对于第一个测试用例:  
$[{\color{red}{5,4}}, 2] \xrightarrow[\min(b_1, b_2) = 3] {\text{操作区间}[1, 2]} [{\color{red}{2, 2, 2}}] \xrightarrow[\min(b_1, b_2, b_3) = 2]{\text{操作区间}[1, 3]} [1, 1, 1]$

对于第二个测试用例:  
$[{\color{red}{3, 6, 1}}, 3, 2] \xrightarrow[\min(b_1, b_2, b_3) = 3]{\text{操作区间}[1, 3]} [1, {\color{red}{2, 1, 3}}, 2] \xrightarrow[\min(b_2, b_3, b_4) = 2]{\text{操作区间}[2, 4]} [1, 1, 1, {\color{red}{2, 2}}] \xrightarrow[\min(b_4, b_5) = 2]{\text{操作区间}[4, 5]} [1, 1, 1, 1, 1]$

translation from [Yorg](https://www.luogu.com.cn/user/617130)

## 样例 #1

### 输入

```
3
3
5 4 2
6 3 2
5
3 6 1 3 2
3 5 3 2 2
6
8 3 3 7 5 8
3 2 3 4 2 3
```

### 输出

```
2
3
3
```

