---
title: "MMMAGIC6 - Mickey Mouse Magic Trick v6"
layout: "post"
diff: 难度0
pid: SP17946
tag: []
---

# MMMAGIC6 - Mickey Mouse Magic Trick v6

## 题目描述

给定如下情景代码：![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP17946/f7d4e975f3b49722b032f17dd0b87a76b7882723.png)

## 输入格式

在这道题中，两个常量为 $n=725$ 和 $k=6$。同一行的整数由单个空格分隔，输出也遵循同样的格式。

输入的第一行包含两个整数 $M$ 和 $D$，其中 $M$ 是米奇需要帮助的测试用例数目，$D$ 是唐老鸭需要帮助的测试用例数目，并且满足 $M+D < 10^6$。

接下来的 $M$ 行，每行有 $k$ 个从 $1$ 到 $n$ 范围内的不同整数，这些数值表示给米奇的卡片上的数，按升序排列。

接下来的 $D$ 行，每行有 $k-1$ 个从 $1$ 到 $n$ 范围内的不同整数，这些数值表示唐老鸭桌面上的卡片数，且顺序与桌面上相同，从左至右。

## 输出格式

对于每一个米奇的查询，输出一行，包含 $k-1$ 个整数，这些是米奇需要留在桌面上的卡片数值，以从左至右的顺序输出。

对于每一个唐老鸭的查询，输出一行，包含一个整数，表示隐藏卡片的数值；如果你的策略无法确定这个数值，可以输出剩余数值中的任意一个。

**数据范围与提示：**

- $M + D < 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
```

### 输出

```
1


3 0\n1 2 3 4 5 6\n2 4 6 100 200 500\n4 7 8 111 222 666
\n5 4 3 2 1\n6 500 4 100 200\n4 111 7 8 222



 



Input 2
Output 2


0 3\n5 4 3 2 1\n6 500 4 100 200\n4 111 7 8 222
\n6\n2\n666



Explanation
The example above don't show any concrete strategy. It just shows, that strategy must be coherent (when Mickey for given set of cards 1 2 3 4 5 6 leave on the table 5 4 3 2 1, then Donald for given cards 5 4 3 2 1 should answer with the number 6).
Generally You can implement Your own strategy satisfying the conditions below:

for Mickey's query "a1 a2 ... ak" You should reply "b1 b2 ... bk-1", such that {b1, b2, ..., bk-1} is subset of {a1, a2, ..., ak}
for Donald's query "b1 b2 ... bk-1" reply the number c, such that {b1, b2, ..., bk-1, c} = {a1, a2, ..., ak}

 
Note
The similar problems appeared in MWPZ 2007 contest in Poland, with different story (in original problems there was Polish characters Bolek, Lolek and Jacek, Placek). The main page of contest is http://mwpz.poznan.pl
```

