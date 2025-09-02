---
title: "MMMAGIC4 - Mickey Mouse Magic Trick v4"
layout: "post"
diff: 难度0
pid: SP17944
tag: []
---

# MMMAGIC4 - Mickey Mouse Magic Trick v4

## 题目描述

在这道题中，我们使用固定的值 $n=27$ 和 $k=4$。还有其他问题涉及不同的值：[MMMAGIC3](../../problems/MMMAGIC3/)、[MMMAGIC5](../../problems/MMMAGIC5/)、[MMMAGIC6](../../problems/MMMAGIC6/)。

### 输入格式

输入的第一行包含两个整数 $M$ 和 $D$，分别代表米奇和唐老鸭需要帮助的测试用例数目，其中 $M+D < 40000$。

接下来的 $M$ 行，每行给出 $k$ 个从 $1$ 到 $n$ 之间不重复的整数，表示米奇收到的卡片上的数值。这些数值是随机排列的。

接下来的 $D$ 行，每行给出 $k-1$ 个从 $1$ 到 $n$ 之间不重复的整数，表示唐老鸭桌上剩余卡片的数值。这些数值按照桌面上的顺序排列，从左到右。

### 输出格式

对每一个米奇的查询，输出一行，包括 $k-1$ 个整数，表示米奇需要放在桌上的卡片数值，从左到右排列。

对每一个唐老鸭的查询，输出一行，包含一个整数，表示隐藏卡片的数值。如果根据策略无法得出唯一结果，可输出任意一个剩余的数值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
```

### 输出

```
1


3 0\n1 2 3 4\n4 13 6 2\n8 20 7 4
\n3 2 1\n13 4 6\n4 20 7



&nbsp;



Input 2
Output 2


0 3\n3 2 1\n13 4 6\n4 20 7
\n4\n2\n8



Explanation
The example above don't show any concrete strategy. It just shows, that strategy must be coherent (when Mickey for given set of cards 1 2 3 4 leave on the table 3 2 1, then Donald for given cards 3 2 1 should answer with the number 4).
Generally You can implement Your own strategy satisfying the conditions below:

for Mickey's query "a1 a2 ... ak" You should reply "b1 b2 ... bk-1", such that {b1, b2, ..., bk-1} is subset of {a1, a2, ..., ak}
for Donald's query "b1 b2 ... bk-1" reply the number c, such that {b1, b2, ..., bk-1, c} = {a1, a2, ..., ak}

&nbsp;
Note
The similar problems appeared in MWPZ 2007 contest in Poland, with different story (in original problems there was Polish characters Bolek, Lolek and Jacek, Placek). The main page of contest is http://mwpz.poznan.pl
```

