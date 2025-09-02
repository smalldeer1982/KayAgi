---
title: "Appropriate Team"
layout: "post"
diff: 省选/NOI-
pid: CF1016G
tag: ['状态合并', '素数判断,质数,筛法', '概率论']
---

# Appropriate Team

## 题目描述

Since next season are coming, you'd like to form a team from two or three participants. There are $ n $ candidates, the $ i $ -th candidate has rank $ a_i $ . But you have weird requirements for your teammates: if you have rank $ v $ and have chosen the $ i $ -th and $ j $ -th candidate, then $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ must be met.

You are very experienced, so you can change your rank to any non-negative integer but $ X $ and $ Y $ are tied with your birthdate, so they are fixed.

Now you want to know, how many are there pairs $ (i, j) $ such that there exists an integer $ v $ meeting the following constraints: $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ . It's possible that $ i = j $ and you form a team of two.

 $ GCD $ is the greatest common divisor of two number, $ LCM $ — the least common multiple.

## 输入格式

First line contains three integers $ n $ , $ X $ and $ Y $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le X \le Y \le 10^{18} $ ) — the number of candidates and corresponding constants.

Second line contains $ n $ space separated integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^{18} $ ) — ranks of candidates.

## 输出格式

Print the only integer — the number of pairs $ (i, j) $ such that there exists an integer $ v $ meeting the following constraints: $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ . It's possible that $ i = j $ .

## 说明/提示

In the first example next pairs are valid: $ a_j = 1 $ and $ a_i = [2, 4, 6, 8, 10, 12] $ or $ a_j = 2 $ and $ a_i = [2, 4, 6, 8, 10, 12] $ . The $ v $ in both cases can be equal to $ 2 $ .

In the second example next pairs are valid:

- $ a_j = 1 $ and $ a_i = [1, 5, 7, 11] $ ;
- $ a_j = 2 $ and $ a_i = [1, 5, 7, 11, 10, 8, 4, 2] $ ;
- $ a_j = 3 $ and $ a_i = [1, 3, 5, 7, 9, 11] $ ;
- $ a_j = 6 $ and $ a_i = [1, 3, 5, 7, 9, 11, 12, 10, 8, 6, 4, 2] $ .

## 样例 #1

### 输入

```
12 2 2
1 2 3 4 5 6 7 8 9 10 11 12

```

### 输出

```
12

```

## 样例 #2

### 输入

```
12 1 6
1 3 5 7 9 11 12 10 8 6 4 2

```

### 输出

```
30

```



---

---
title: "Count Leaves"
layout: "post"
diff: 省选/NOI-
pid: CF2020F
tag: ['动态规划 DP', '素数判断,质数,筛法']
---

# Count Leaves

## 题目描述

有正整数 $n$ 和 $d$。我们按如下规则建一棵 $T_{n,d}$ 的约数树：

- 树的根节点上的数为 $n$。这是树的第 $0$ 层。
- 对于第 $i$ 层（$i=0,1,...,d-1$）的每个结点，执行如下操作：若当前节点上的数为 $x$，则 $x$ 的所有可能的不同约数为其儿子节点上的数。这些儿子节点位于第 $i+1$ 层。
- 第 $d$ 层上的点为叶子节点。

例如，$T_{6,2}$（$n=6,d=2$ 的约数树）如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2020F/fe3509981f0e7cfbf5fabd59d7e6e5b6182b6f65.png)

定义 $f(n,d)$ 为 $T(n,d)$ 的叶子节点数。

给定 $n,k,d$ ，计算 $\sum\limits_{i=1}^nf(i^k,d)$ 模 $10^9+7$ 后的答案。

注：在这个问题中，我们说 $y$ 为 $x$ 的约数当且仅当 $y\geq1$ 且存在整数 $z$ 使得 $x=y\cdot z$。

## 输入格式

每个测试有多组测试数据。第一行 $t\ (1\leq t\leq10^4)$ 为测试数据数。

每个测试数据包含一行三个数 $n,k,d\ (1\leq n\leq 10^9,1\leq k,d\leq 10^5)$。

保证所有测试数据中 $n$ 的和不超过 $10^9$。

## 输出格式

对于每个测试数据，输出一行一个整数，表示 $\sum\limits_{i=1}^nf(i^k,d)\ mod\ 10^9+7$ 后的结果。 
### 样例解释
在第一个测试样例中，$n=6,k=1,d=1$。因此，我们要算出 $T_{1,1},T_{2,1},T_{3,1},T_{4,1},T_{5,1},T_{6,1}$ 的叶子数的和。
- $T_{1,1}$ 只有一个叶子，该叶子上的数为 $1$。
- $T_{2,1}$ 有两个叶子，叶子上的数为 $1,2$。
- $T_{3,1}$ 有两个叶子，叶子上的数为 $1,3$。
- $T_{4,1}$ 有三个叶子，叶子上的数为 $1,2,4$。
- $T_{5,1}$ 有两个叶子，叶子上的数为 $1,5$。
- $T_{6,1}$ 有四个叶子，叶子上的数为 $1,2,3,6$。

叶子的总数为 $1+2+2+3+2+4=14$。

在第二个测试样例中，$n=1,k=3,d=3$，所以我们要求出 $T_{1^3,3}$ 的叶子数。因为 $1^3=1$，所以这棵树只有一片叶子，答案为 $1$。

## 样例 #1

### 输入

```
3
6 1 1
1 3 3
10 1 2
```

### 输出

```
14
1
53
```



---

---
title: "Segmentation Folds"
layout: "post"
diff: 省选/NOI-
pid: CF2041F
tag: ['二分', '素数判断,质数,筛法', '双指针 two-pointer']
---

# Segmentation Folds

## 题目描述

Peter 喜欢折线段玩。有一条线段位于数轴上的区间 $[\ell, r]$。现如今正是折叠线段的好时机，Peter 决定小心翼翼地对这条线段进行折叠。每次操作中，他可以选择以下两种方式之一（在可能的情况下）：

1. 操作 $\tt{LTR}$：他从左向右折线段，使得左端点 $\ell$ 与某个点 $x$ 重合（$\ell < x \le r$），并且 $\ell + x$ 是质数。当他选择此操作时，总是选取最大的 $x$ 值。折叠后，线段所在的区间变为 $[\frac{1}{2}(\ell + x), r]$。
   
2. 操作 $\tt{RTL}$：他从右向左折线段，使得右端点 $r$ 与某个点 $x$ 重合（$\ell \le x < r$），并且 $r + x$ 是质数。当他选择此操作时，总是选取最小的 $x$ 值。折叠后，线段所在的区间变为 $[\ell, \frac{1}{2}(r + x)]$。

一个折叠序列是指这两种操作的组合。Peter 想要通过多次折叠，使线段的长度尽可能短，且无法再缩短。区间的长度自然定义为 $r - \ell$。考虑以下例子：假设我们折叠一段初始为 $[1, 30]$ 的线段。有三种折叠方式能使最终区间长度最短，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041F/be032bc113ac39f401b84d34f2c5f31947b110d1.png)

请你帮助 Peter 确定有多少种不同的折叠序列可以使线段达到最短长度。结果需要对 $998244353$ 取模。

注：一个大于 $1$ 的整数 $p$ 是质数，当且仅当不存在整数 $a, b > 1$ 使得 $p = ab$。

## 输入格式

第一行包含一个整数 $t$，表示测试用例的数量。接下来的 $t$ 行中，每行包含两个整数 $\ell$ 和 $r$。

- $1 \le t \le 10$
- $1 \le \ell < r \le 10^{12}$
- $r - \ell \le 10^5$

## 输出格式

对于每个测试用例，输出一行，表示能将给定线段折叠到最短长度的折叠序列数量，结果对 $998244353$ 取模。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1 30
16 18
142857 240135
```

### 输出

```
3
1
63
```



---

---
title: "Rotatable Number"
layout: "post"
diff: 省选/NOI-
pid: CF303D
tag: ['素数判断,质数,筛法', '进制']
---

# Rotatable Number

## 题目描述

Bike is a smart boy who loves math very much. He invented a number called "Rotatable Number" inspired by $ 142857 $ .

As you can see, $ 142857 $ is a magic number because any of its rotatings can be got by multiplying that number by $ 1,2,...,6 $ (numbers from one to number's length). Rotating a number means putting its last several digit into first. For example, by rotating number $ 12345 $ you can obtain any numbers: $ 12345,51234,45123,34512,23451 $ . It's worth mentioning that leading-zeroes are allowed. So both $ 4500123 $ and $ 0123450 $ can be obtained by rotating $ 0012345 $ . You can see why $ 142857 $ satisfies the condition. All of the $ 6 $ equations are under base $ 10 $ .

- $ 142857·1=142857 $ ;
- $ 142857·2=285714 $ ;
- $ 142857·3=428571 $ ;
- $ 142857·4=571428 $ ;
- $ 142857·5=714285 $ ;
- $ 142857·6=857142 $ .

Now, Bike has a problem. He extends "Rotatable Number" under any base $ b $ . As is mentioned above, $ 142857 $ is a "Rotatable Number" under base $ 10 $ . Another example is $ 0011 $ under base 2. All of the $ 4 $ equations are under base $ 2 $ .

- $ 0011·1=0011 $ ;
- $ 0011·10=0110 $ ;
- $ 0011·11=1001 $ ;
- $ 0011·100=1100 $ .

So, he wants to find the largest $ b $ $ (1&lt;b&lt;x) $ so that there is a positive "Rotatable Number" (leading-zeroes allowed) of length $ n $ under base $ b $ .

Note that any time you multiply a rotatable number by numbers from 1 to its length you should get a rotating of that number.

## 输入格式

The only line contains two space-separated integers $ n,x $ $ (1<=n<=5·10^{6},2<=x<=10^{9}) $ .

## 输出格式

Print a single integer — the largest $ b $ you found. If no such $ b $ exists, print -1 instead.

## 样例 #1

### 输入

```
6 11

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 8

```

### 输出

```
-1

```



---

---
title: "Jzzhu and Apples"
layout: "post"
diff: 省选/NOI-
pid: CF449C
tag: ['枚举', '素数判断,质数,筛法', '栈']
---

# Jzzhu and Apples

## 题目描述

Jzzhu has picked $ n $ apples from his big apple tree. All the apples are numbered from $ 1 $ to $ n $ . Now he wants to sell them to an apple store.

Jzzhu will pack his apples into groups and then sell them. Each group must contain two apples, and the greatest common divisor of numbers of the apples in each group must be greater than 1. Of course, each apple can be part of at most one group.

Jzzhu wonders how to get the maximum possible number of groups. Can you help him?

## 输入格式

A single integer $ n $ $ (1<=n<=10^{5}) $ , the number of the apples.

## 输出格式

The first line must contain a single integer $ m $ , representing the maximum number of groups he can get. Each of the next $ m $ lines must contain two integers — the numbers of apples in the current group.

If there are several optimal answers you can print any of them.

## 样例 #1

### 输入

```
6

```

### 输出

```
2
6 3
2 4

```

## 样例 #2

### 输入

```
9

```

### 输出

```
3
9 3
2 4
6 8

```

## 样例 #3

### 输入

```
2

```

### 输出

```
0

```



---

---
title: "Prime Gift"
layout: "post"
diff: 省选/NOI-
pid: CF912E
tag: ['搜索', '二分', '素数判断,质数,筛法']
---

# Prime Gift

## 题目描述

Opposite to Grisha's nice behavior, Oleg, though he has an entire year at his disposal, didn't manage to learn how to solve number theory problems in the past year. That's why instead of Ded Moroz he was visited by his teammate Andrew, who solemnly presented him with a set of $ n $ distinct prime numbers alongside with a simple task: Oleg is to find the $ k $ -th smallest integer, such that all its prime divisors are in this set.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=16 $ ).

The next line lists $ n $ distinct prime numbers $ p_{1},p_{2},...,p_{n} $ ( $ 2<=p_{i}<=100 $ ) in ascending order.

The last line gives a single integer $ k $ ( $ 1<=k $ ). It is guaranteed that the $ k $ -th smallest integer such that all its prime divisors are in this set does not exceed $ 10^{18} $ .

## 输出格式

Print a single line featuring the $ k $ -th smallest integer. It's guaranteed that the answer doesn't exceed $ 10^{18} $ .

## 说明/提示

The list of numbers with all prime divisors inside $ {2,3,5} $ begins as follows:

 $ (1,2,3,4,5,6,8,...) $

The seventh number in this list ( $ 1 $ -indexed) is eight.

## 样例 #1

### 输入

```
3
2 3 5
7

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5
3 7 11 13 31
17

```

### 输出

```
93

```



---

