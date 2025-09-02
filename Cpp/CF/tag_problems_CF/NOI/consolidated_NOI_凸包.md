---
title: "Algoland and Berland"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1070M
tag: ['凸包']
---

# Algoland and Berland

## 题目描述

很久以前，Algoland和Berland是一个国家，但那个时代早已过去。现在它们是两个国家，但他们的城市散布在一个共同的领土上。

所有城市都表示为一个平面直角坐标系的一个点。Algoland由 $a$ 个城市组成，编号从 $1$ 到 $a$。Algoland第 $i$ 个城市的坐标为 $(xa_i,ya_i)$ 。同样的，Berland由 $b$ 个城市组成，编号从 $1$ 到 $b$。Berland第 $j$ 个城市的坐标是 $(xb_j,yb_j)$ 。保证两个国家的 $a+b$ 个城市里没有三个城市在一条直线上。

作为联合两国的第一步，Berland决定修建几条双向的高速公路。每条高速公路将是一条线段，从Berland的一个城市开始，到Algoland的一个城市结束。除了高速公路的起点或终点，高速公路不能在任何一点上相互交叉。此外，高速公路必须连接所有 $a+b$ 个城市。这意味着人们可以通过高速公路从任何一个城市到达任何其他的城市。请注意，所有的高速公路都是双向的，这意味着人们可以在每条高速公路上双向行驶。

每一个Berland城市的市长都分配了一个预算来建造从这个城市出发的高速公路。因此，你会得到数 $r_1,r_2,\dots,r_b$ ，其中 $r_j$ 是要从第 $j$ 个Berland城市开始的高速公路的数量。市长们分配的预算是非常紧张的，只有建设所有高速公路必要的代价。也就是 $r_1+r_2+\dots+r_b=a+b-1$ 。

请你帮助Berland建设高速公路，有以下几个要求：

- 每条高速公路都是一条连接Berland城市和Algoland城市的线段。
- 没有任何两条高速公路有交点，除了交点是两条公路的起点或终点。
- 高速公路必须连接所有 $a+b$ 个城市。
- 有 $r_j$ 条高速公路从第 $j$ 个Berland城市开始。

## 输入格式

本题有多组测试数据。

第一行输入一个整数 $t$ $(1\le t\le3000)$ ，代表有 $t$ 组测试数据。

每个测试数据的第一行有两个整数，分别为 $a$ 和 $b$ 。

第二行有 $b$ 个整数，第 $i$ 个整数表示 $r_i$ $(1\le r_i\le a)$ 。

接下来的 $a$ 行，每行两个整数 $xa_i,ya_i$ 。

再接下来的 $b$ 行，每行两个整数 $xb_i,yb_i$ 。

具体意义见上文描述。

## 输出格式

对于每个测试数据，第一行输出`YES`或`NO`，代表能否满足要求。

如果能满足要求，输出 $a+b-1$ 行，每行有两个整数 $j$ 和 $i$，表示从第 $j$ 个Berland城市往第 $i$ 个Algoland城市建设一条高速公路。如果有多组方法，请输出其中的一个

## 样例 #1

### 输入

```
2
2 3
1 1 2
0 0
1 1
1 2
3 2
4 0
1 1
1
0 0
0 1

```

### 输出

```
YES
2 2
1 2
3 2
3 1
YES
1 1

```



---

---
title: "Yandex Cuneiform (Hard Version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2046F2
tag: ['动态规划 DP', '动态规划优化', '凸包']
---

# Yandex Cuneiform (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, there is no restriction on the number of question marks. You can hack only if you solved all versions of this problem.

For a long time, no one could decipher Sumerian cuneiform. However, it has finally succumbed to pressure! Today, you have the chance to decipher Yandex cuneiform.

Yandex cuneiform is defined by the following rules:

1. An empty string is a Yandex cuneiform.
2. If you insert exactly one copy of each of the three letters 'Y', 'D', and 'X' into a Yandex cuneiform in such a way that no two adjacent letters become equal after the operation, you obtain a Yandex cuneiform.
3. If a string can't be obtained using the above rules, it is not a Yandex cuneiform.

You are given a template. A template is a string consisting of the characters 'Y', 'D', 'X', and '?'.

You need to check whether there exists a way to replace each question mark with 'Y', 'D', or 'X' to obtain a Yandex cuneiform, and if it exists, output any of the matching options, as well as a sequence of insertion operations to obtain the resulting cuneiform.

In this version of the problem, the number of question marks in the template can be arbitrary.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

Each test case consists of a single line containing a template of length $ n $ ( $ 3 \leq n < 2 \cdot 10^5 $ , $ n \bmod 3 = 0 $ ), consisting only of characters 'Y', 'D', 'X', and '?'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing 'NO' if it is not possible to obtain a cuneiform from the given template.

Otherwise, output 'YES' on the first line, and on the second line, any obtainable cuneiform. After that, you need to output the sequence of operations that leads to the cuneiform you printed.

A sequence of operations is described by $ \frac{n}{3} $ triples of pairs. A pair has the form c p, where $ c $ is one of the letters 'Y', 'D', or 'X', and $ p $ is the position at which the letter $ c $ should be inserted. The insertion position is the number of letters to skip from the beginning of the string for the insertion. For example, after inserting the character 'D' into the string "YDX" with $ p=3 $ , the result is "YDXD", and with $ p=0 $ , it is "DYDX". Note that the index cannot exceed the current length of the string.

The operations are applied from top to bottom, left to right. After inserting each triple to the string, there should be no two adjacent identical characters.

## 说明/提示

In the second example, the string is transformed like this: $ "" \to \mathtt{YDX} \to \mathtt{YDXDYX} $ .

## 样例 #1

### 输入

```
4
???
Y??D?X
???
D??DXYXYX
```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO
```



---

