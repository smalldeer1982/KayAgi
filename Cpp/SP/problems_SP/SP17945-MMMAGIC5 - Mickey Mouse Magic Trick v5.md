---
title: "MMMAGIC5 - Mickey Mouse Magic Trick v5"
layout: "post"
diff: 难度0
pid: SP17945
tag: []
---

# MMMAGIC5 - Mickey Mouse Magic Trick v5

## 题目描述

在这个问题中，我们的常量值为 $n=124$ 和 $k=5$。你的任务是分别帮助米奇和唐老鸭解决牌的问题。

输入的第一行是两个整数 $M$ 和 $D$，表示米奇需要帮助的测试用例有 $M$ 个，唐老鸭需要帮助的测试用例有 $D$ 个，并且 $M + D < 10^6$。

接下来的 $M$ 行中，每行都有 $k$ 个在 $[1, n]$ 范围内的不同整数，表示给到米奇的牌。这些整数已经按升序排列。

在随后的 $D$ 行中，每行包含 $k-1$ 个在 $[1, n]$ 范围内的不同整数，表示桌面上留给唐老鸭的牌，顺序与实际展示一致，从左到右。

## 输出格式

对于每个米奇的问题，请输出一行，内容包含 $k-1$ 个整数，表示米奇应该留下的那些牌的数值，并从左至右按顺序排列。

对于每个唐老鸭的问题，请输出一行，内容为一个整数，表示隐藏的那张牌的数值。如果你的策略使得某种情况下无法识别这些牌，输出任意一个其余的数值即可。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
```

### 输出

```
1


3 0\n1 2 3 4 5\n2 4 6 40 80&nbsp;\n4 7 8 72 123
\n4 3 2 1\n4 6 80 2\n4 7 123 8



&nbsp;



Input 2
Output 2


0 3\n4 3 2 1\n4 6 80 2\n4 7 123 8
\n5\n40\n72



Explanation
The example above don't show any concrete strategy. It just shows, that strategy must be coherent (when Mickey for given set of cards 1 2 3 4 5 leave on the table 4 3 2 1, then Donald for given cards 4 3 2 1 should answer with the number 5).
Generally You can implement Your own strategy satisfying the conditions below:

for Mickey's query "a1 a2 ... ak" You should reply "b1 b2 ... bk-1", such that {b1, b2, ..., bk-1} is subset of {a1, a2, ..., ak}
for Donald's query "b1 b2 ... bk-1" reply the number c, such that {b1, b2, ..., bk-1, c} = {a1, a2, ..., ak}

&nbsp;
Note
The problem appeared in MWPZ 2007 contest in Poland, with different story (in original problem there was Polish characters Jacek and Placek). The main page of contest is http://mwpz.poznan.pl
```

