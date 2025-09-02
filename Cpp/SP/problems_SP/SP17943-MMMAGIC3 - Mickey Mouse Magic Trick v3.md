---
title: "MMMAGIC3 - Mickey Mouse Magic Trick v3"
layout: "post"
diff: 难度0
pid: SP17943
tag: []
---

# MMMAGIC3 - Mickey Mouse Magic Trick v3

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP17943/3aa7e179bc80b62279b4f3556a92771923f8e562.png)

米奇和唐老鸭在玩一种魔术卡片游戏。你的任务是为他们提供帮助。具体情况如下：

## 输入格式

同一行中的所有整数由单个空格隔开。（输出格式同样如此）

在这个问题中，有两个常量 $n=8$ 和 $k=3$。其他题目中使用的常量可能不同：[MMMAGIC4](../../problems/MMMAGIC4/)、[MMMAGIC5](../../problems/MMMAGIC5/)、[MMMAGIC6](../../problems/MMMAGIC6/)。

输入的第一行包含两个整数 $M$ 和 $D$，表示米奇需帮助的测试用例数量为 $M$，唐老鸭需帮助的测试用例数量为 $D$。（注意：$M+D < 200$）

接下来的 $M$ 行，每行有 $k$ 个从 $[1, n]$ 范围中选出的不同整数，代表给米奇的卡片上的数字。这些数字的顺序是随机的。

接下来的 $D$ 行，每行有 $k-1$ 个从 $[1, n]$ 范围中选出的不同整数，表示桌面上留给唐老鸭的卡片上的数字。它们的顺序是从左到右。

## 输出格式

对于每个米奇的请求，输出一行，包含 $k-1$ 个整数，代表米奇需要留在桌面上的卡片值，顺序为从左到右。

对于每个唐老鸭的请求，输出一行，包含一个整数，代表隐藏卡片的值。如果无法确定隐藏的卡片，则可以输出任意一个剩余的卡片值。

## 说明/提示

- $n = 8, \ k = 3$
- $M + D < 200$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
```

### 输出

```
1


3 0\n1 2 3\n4 6 2\n8 7 4
\n2 1\n4 6\n4 7



&nbsp;



Input 2
Output 2


0 3\n2 1\n4 6\n4 7
\n3\n2\n8



Explanation
The example above don't show any concrete strategy. It just shows, that strategy must be coherent (when Mickey for given set of cards 1 2 3 leave on the table 2 1, then Donald for given cards 2 1 should answer with the number 3).
Generally You can implement Your own strategy satisfying the conditions below:

for Mickey's query "a1 a2 ... ak" You should reply "b1 b2 ... bk-1", such that {b1, b2, ..., bk-1} is subset of {a1, a2, ..., ak}
for Donald's query "b1 b2 ... bk-1" reply the number c, such that {b1, b2, ..., bk-1, c} = {a1, a2, ..., ak}

&nbsp;
Note
The similar problem appeared in MWPZ 2007 contest in Poland, with different story (in original problem there was Polish characters Bolek and Lolek). The main page of contest is http://mwpz.poznan.pl
```

