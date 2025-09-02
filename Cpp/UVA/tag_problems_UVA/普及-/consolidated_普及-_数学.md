---
title: "The 3n + 1 problem"
layout: "post"
diff: 普及-
pid: UVA100
tag: ['模拟', '数学', '递归']
---

# The 3n + 1 problem

## 题目描述

考虑下面的程序：

1. 输入 $n$

2. 输出 $n$

3. 如果 $n=1$ 退出程序

4. 如果 $n$ 是奇数，$n \rightarrow 3 n + 1$

5. 如果 $n$ 是偶数 $n\rightarrow \dfrac n 2$

6. 回到第 $2$ 步 

若输入 $22$，会得出下面的数列： `22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1`。

我们推测，对于任何输入的正整数 $n$，程序最终都会输出 $1$（$n\le 10^6$ 时，保证推论正确）。 给定 $n$，可以计算这个程序输出的所有数字的数量（包括最后的 $1$）。我们把输出的数字总数称为这个 $n$ 的周期长度。对于上面的例子，周期长度为 $16$。 

对于输入的每对 $(i,j)$，计算 $[i,j]$ 内所有数字区间长度的最大值。

## 输入格式

输入几对整数 $(i,j)$，保证 $0<i,j\le 10^4$。对于每对 $(i,j)$，你需要计算 $[i,j]$ 内最大区间长度。数据保证 $32$ 位整数在计算过程中不溢出。

## 输出格式

对于每对 $(i,j)$，先输出 $i,j$，再输出 $[i,j]$ 范围内最大周期长度，每个数字中间一个空格，然后换行。

## 样例 #1

### 输入

```
1 10
100 200
201 210
900 1000
```

### 输出

```
1 10 20
100 200 125
201 210 89
900 1000 174
```



---

---
title: "Triangle Counting"
layout: "post"
diff: 普及-
pid: UVA11401
tag: ['数学']
---

# Triangle Counting

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2396

[PDF](https://uva.onlinejudge.org/external/114/p11401.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11401/5eaa7dd447e7d2ae45ba394b0c6ba6a37f3cba8d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11401/b0bc4155f968ef494f664a8d35457b9fca2b3cab.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11401/310d1f61107c2c5ef7e67a82bb796695a1fe073a.png)

## 说明/提示

给定$n$条边，长度分别为$1,2,3,...,n$。用其中三条边构成一个三角形，有多少种不同的方案？注意，一条边只能使用一次。

**输入格式**

每行输入包含一个数字$n(3 \leq n \leq 10^6)$，含义如上所示。
结束标志为$n <3$。

**输出格式**

对于每组数据，输出如前所述的方案数。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
5
8
0
```

### 输出

```
3
22
```



---

---
title: "Square Numbers"
layout: "post"
diff: 普及-
pid: UVA11461
tag: ['数学', '数论']
---

# Square Numbers

## 题目描述

平方数是指平方根也是整数的整数。例如，$1$、$4$、$81$ 都是平方数。给定两个数字 $a$ 和 $b$，你需要找出在 $a$ 和 $b$ 之间（包含 $a$ 和 $b$）有多少个平方数。

## 输入格式

输入文件最多包含 $201$ 行输入。每行包含两个整数 $a$ 和 $b$（$0 < a \le b \le 10 ^ 5$)。输入由包含两个零的行终止，该行不应被处理。

## 输出格式

对于输入的每一行，输出一行。该行包含一个整数，表示在 $a$ 和 $b$ 之间（包含 $a$ 和 $b$）有多少个平方数。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1 4
1 10
0 0
```

### 输出

```
2
3
```



---

