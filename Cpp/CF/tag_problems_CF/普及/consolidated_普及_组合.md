---
title: "Beautiful Sequence"
layout: "post"
diff: 普及/提高-
pid: CF2069C
tag: ['数学', '组合数学', '前缀和']
---

# Beautiful Sequence

## 题目描述

我们称一个整数序列为美丽的（beautiful），当且仅当满足以下条件：
- 序列长度至少为 $3$；
- 对于除第一个元素外的每个元素，其左侧存在一个比它小的元素；
- 对于除最后一个元素外的每个元素，其右侧存在一个比它大的元素；

例如，$[1, 4, 2, 4, 7]$ 和 $[1, 2, 4, 8]$ 是美丽的，但 $[1, 2]$、$[2, 2, 4]$ 和 $[1, 3, 5, 3]$ 不是。

注意：子序列是指通过删除原序列中某些元素（不改变剩余元素的顺序）得到的新序列。

给定一个大小为 $n$ 的整数数组 $a$，其中每个元素均为 $1$ 到 $3$ 之间的整数。你的任务是计算数组 $a$ 中美丽子序列的数量。由于答案可能很大，请将其对 $998244353$ 取模后输出。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 3$）。

输入额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——数组 $a$ 中美丽子序列的数量对 $998244353$ 取模后的结果。

## 说明/提示

在示例的第一个测试用例中，以下子序列是美丽的：
- $[a_3, a_4, a_7]$；
- $[a_3, a_5, a_7]$；
- $[a_3, a_4, a_5, a_7]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
7
3 2 1 2 2 1 3
4
3 1 2 2
3
1 2 3
9
1 2 3 2 1 3 2 2 3
```

### 输出

```
3
0
1
22
```



---

---
title: "Kyoya and Colored Balls"
layout: "post"
diff: 普及/提高-
pid: CF553A
tag: ['排列组合']
---

# Kyoya and Colored Balls

## 题目描述

Kyoya Ootori has a bag with $ n $ colored balls that are colored with $ k $ different colors. The colors are labeled from $ 1 $ to $ k $ . Balls of the same color are indistinguishable. He draws balls from the bag one by one until the bag is empty. He noticed that he drew the last ball of color $ i $ before drawing the last ball of color $ i+1 $ for all $ i $ from $ 1 $ to $ k-1 $ . Now he wonders how many different ways this can happen.

## 输入格式

The first line of input will have one integer $ k $ ( $ 1<=k<=1000 $ ) the number of colors.

Then, $ k $ lines will follow. The $ i $ -th line will contain $ c_{i} $ , the number of balls of the $ i $ -th color ( $ 1<=c_{i}<=1000 $ ).

The total number of balls doesn't exceed 1000.

## 输出格式

A single integer, the number of ways that Kyoya can draw the balls from the bag as described in the statement, modulo $ 1000000007 $ .

## 说明/提示

In the first sample, we have 2 balls of color 1, 2 balls of color 2, and 1 ball of color 3. The three ways for Kyoya are:

`<br></br>1 2 1 2 3<br></br>1 1 2 2 3<br></br>2 1 1 2 3<br></br>`

## 样例 #1

### 输入

```
3
2
2
1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1
2
3
4

```

### 输出

```
1680

```



---

