---
title: "PBOARD - Blocks for kids"
layout: "post"
diff: 难度0
pid: SP7250
tag: []
---

# PBOARD - Blocks for kids

## 题目描述

Wango 是一位杰出的数学老师，有两个儿子：大儿子 Kango 和小儿子 Dango，兄弟俩正好出生在同一天，相隔两年。Kango 今年 9 岁，而 Dango 7 岁。他们的生日快到了，Wango 要为他们准备礼物。经过深思熟虑，他决定送每人一块 Pango 板，用它来介绍高等数学的概念。

Pango 板大小为 $n$（$n \geq 0$）时是一个 $2 \times n$ 的矩形，由单元格组成。需要用 Pango 件把这个矩形填满，可以接受任意的铺法。大小为 0 的 Pango 板是存在的，也是唯一的，它被视为空集的一个例子。

有四种类型的 Pango 件可以使用：

1 2 3 4  
== == == ==  
XX X X X  
XX XX X

这四种块的图片如下所示：

![4 types of blocks](http://www.hostpic.org/images/66pic.jpg.jpeg "Blocks for Kids")

Wango 在给 Kango 或 Dango 送出板子之前，必须用这些 Pango 件完全铺满它（每种件的数量没有限制），并且件不能旋转。为了节省开支（经济萧条嘛），Wango 决定只买一块大小为 $N$ 的板子，然后选择一个整数 $k$（$0 \leq k \leq N$），将一块大小为 $k$ 的板子给 Kango，另一块大小为 $(N-k)$ 的板子给 Dango（当然，这两块板子都要铺满）。你需要帮助他计算出他可以把礼物分给儿子的不同方法数。两种方法只有在 Dango 或 Kango 拿到的板子不同的时候，才被认为是不同的。如果两个 Pango 板的铺法从左到右完全相同，那么它们被视为完全相同的板子（注意，这里不允许旋转板子进行比较）。

## 输入格式

输入包含多个测试用例，每个测试用例占一行。
每行给出一个整数 $N$（$0 \leq N \leq 1,000,000,000$），表示 Wango 打算购买的板子的大小。
以一行输入 `-1` 作为结束标志，这行不应处理。
一共最多有 10000 个测试用例。

## 输出格式

对于每个测试用例，输出一种方式的总数量，对 10,007 取模后的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n0\n1\n2\n-1\n\n
```

### 输出

```
\n1\n4\n16\n\nExplanation:\nNumber of different 0-sized Pango boards = 1\nNumber of different 1-sized Pango boards = 2\nNumber of different 2-sized Pango boards = 6\nFor N = 0, he has to give 0-sized boards to both his sons. He can do this in 1*1 = 1 way\nFor N = 1, he has to give 0-sized board to one of his sons, and 1-sized board to the other, for a total of 2*1 +\n1*2 = 4 ways\nFor N = 2, he can give the presents in 6*1 + 2*2 + 1*6 = 16 ways\n
```

