---
title: "LUCIFER - LUCIFER Number"
layout: "post"
diff: 难度0
pid: SP10968
tag: []
---

# LUCIFER - LUCIFER Number

## 题目描述

Lucifer 是唯一一个在电脑游戏中击败过 RA-ONE 的人。RA-ONE 因此想要复仇，而 G-ONE 则保护着 Lucifer。

这种 G-ONE 和 RA-ONE 的纠葛严重扰乱了 Lucifer 的生活。他迫切希望击败 RA-ONE。通过调查，他发现只有扔出与 Lucifer 数字数量相等的武器才能击败 RA-ONE。

Lucifer 数字具有与 [RA-ONE 数字](https://www.spoj.com/problems/RAONE/) 和 [G-ONE 数字](https://www.spoj.com/problems/GONE/) 一些相似的特性。

如果一个数字中，偶数位上的数字之和与奇数位上的数字之和的差是一个质数，那么这个数字就是一个 Lucifer 数。例如，20314210 就是一个 Lucifer 数：

奇数位上的数字是：0, 2, 1, 0

偶数位上的数字是：1, 4, 3, 2

计算差值： (1 + 4 + 3 + 2) - (0 + 2 + 1 + 0) = 10 - 3 = 7，结果是一个质数。

Lucifer 有一个满是武器的仓库可供挑选，他想知道在给定的范围内有多少个这样的 Lucifer 数字，以决定要准备多少武器打败 RA-ONE。

你能帮他计算吗？

## 输入格式

第一行包含一个整数 $t$，表示测试用例的数量。

接下来的每一行包含两个整数 $a$ 和 $b$，表示一个闭区间。

## 输出格式

对于每个测试用例，输出一行，表示在区间 $[a, b]$ 中的 Lucifer 数的数量。

## 说明/提示

$$1 \le t \le 100$$
$$1 \le a \le b \le 10^5$$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n5\n200 250\n150 200\n100 150\n50 100\n0 50\n\n&nbsp;
```

### 输出

```
\n2\n16\n3\n18\n6\n\n\nNOTE: t will be less than 100\nfrom and to will be between 0 and 10^9 inclusive
```

