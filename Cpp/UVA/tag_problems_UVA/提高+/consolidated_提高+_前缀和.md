---
title: "树林里的树 Trees in a Wood."
layout: "post"
diff: 提高+/省选-
pid: UVA10214
tag: ['莫比乌斯反演', '前缀和', '分块']
---

# 树林里的树 Trees in a Wood.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1155

[PDF](https://uva.onlinejudge.org/external/102/p10214.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10214/50c1f69fedc915b5433ce438aa7604af34fd8f42.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10214/808df44b8756dba5507bc71c957bf48ed7059f7f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10214/0067dbf9991a54b975861cf5bbf94ec6b6db62d0.png)

## 样例 #1

### 输入

```
3 2
0 0
```

### 输出

```
0.7058824
```



---

---
title: "Spreading the Wealth"
layout: "post"
diff: 提高+/省选-
pid: UVA11300
tag: ['递推', '排序', '前缀和']
---

# Spreading the Wealth

## 题目描述

圆桌旁边坐着$n$个人，每个人有一定数量的金币，金币的总数能被$n$整除。每个人可以给他左右相邻的人一些金币，最终使得每个人的金币数量相等。您的任务是求出被转手的金币的数量的最小值。

　

## 输入格式

输入包含多组数据。每组数据第一行为一个整数$n(n<=1000000)$,以下n行每行为一个整数，按逆时针顺序给出每个人拥有的金币数。输入结束标志为文件结束符($EOF$).

　

## 输出格式

对于每组数据，输出被转手的金币的数量的最小值。输入保证这个值在$64$位无符号整数的范围之内。

Translated by @洛谷万岁

## 样例 #1

### 输入

```
3
100
100
100
4
1
2
5
4
```

### 输出

```
0
4
```



---

---
title: "照明系统设计 Lighting System Design"
layout: "post"
diff: 提高+/省选-
pid: UVA11400
tag: ['枚举', '排序', '前缀和']
---

# 照明系统设计 Lighting System Design

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2395

[PDF](https://uva.onlinejudge.org/external/114/p11400.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/c3748d15cb3e3882e349c0c2e200acb240ab8b00.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/8c7751c33d777f27b23c671b600389469282fc9b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/115c28d58e6ba75439c2c7bd1d61178f8efff609.png)

## 样例 #1

### 输入

```
3
100 500 10 20
120 600 8 16
220 400 7 18
0
```

### 输出

```
778
```



---

---
title: "GCD - Extreme (I)"
layout: "post"
diff: 提高+/省选-
pid: UVA11424
tag: ['枚举', '最大公约数 gcd', '前缀和']
---

# GCD - Extreme (I)

## 题目描述

给定   $n$，求
  $$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中   $\gcd(i,j)$ 指的是   $i$ 和   $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数   $n$，如果   $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果，保证可以用  $64$ 位整形变量存储。

## 说明/提示

对于   $100\%$ 的数据，  $1 < n < 2 \times 10^5+1$，最多  $2 \times 10^4$ 组数据。

## 样例 #1

### 输入

```
10
100
20000
0
```

### 输出

```
67
13015
1153104356
```



---

---
title: ""Ray, Pass me the dishes!""
layout: "post"
diff: 提高+/省选-
pid: UVA1400
tag: ['线段树', '分治', '前缀和']
---

# "Ray, Pass me the dishes!"

## 题目描述

给出一个长度为 $n$ 的整数序列 $D$，你的任务是对 $m$ 个询问作出回答。对于询问 $(a,b)$，需要找到两个下标 $x$ 和 $y$，使得 $a\le x\le y\le b$，并且 $D_x+D_{x+1}+...+D_y$ 尽量大。如果有多组满足条件的 $x$ 和 $y$，$x$ 应尽量小。如果还有多解，$y$ 应该尽量小。

## 输入格式

输入包含多组数据。每组数据第一行为两个整数 $n$ 和$m$（$1\le n,m\le 5\times10^5$），即整数序列长度和查询的个数。第二行包含 $n$ 个整数，依次为 $D_1,D_2,...,D_n$ 的值。这些整数的绝对值不超过 $10^9$。以下 $m$ 行每行为一个查询，包含两个整数 $a$ 和 $b$。输入结束标志为文件结束符 `EOF`。

## 输出格式

对于每组数据，输出数据编号`Case xx:` ，然后为每个查询输出一行，包含两个整数 $x$ 和 $y$。



---

---
title: "Guess"
layout: "post"
diff: 提高+/省选-
pid: UVA1423
tag: ['排序', '拓扑排序', '前缀和']
---

# Guess

## 题目描述

给定一个数组： $a_1,a_2,a_3,\dots ,a_n$ 。

我们定义一个符号矩阵 $S_{i,j},i\le j$ ，代表 $a_i+a_{i+1}+\dots +a_j$ 的符号为 $+,-,0$ 三个中的一种。

你需要写一个程序，输入这个 $n\times n$ 的半矩阵，输出原来的数列。如果有多解，输出一组即可。

数据总共有T组。

## 输入格式

第一行输入 $T$ ，代表数据的组数。

接下来共 $T$ 组数据。

对于每一组数据，第一行输入数列的长度 $n$ ，第二行是一个长度为 $\frac{n(n+1)}{2}$ 的字符串，代表这个半矩阵。

## 输出格式

对于每一组数据，输出原来的数列。如果有多解，输出一组即可。

## 说明/提示

$1\le n \le 10$ 

 $-10\le a_i \le 10$ 

Translated by @dblark



---

---
title: "切蛋糕 Cake slicing"
layout: "post"
diff: 提高+/省选-
pid: UVA1629
tag: ['动态规划 DP', '枚举', '前缀和']
---

# 切蛋糕 Cake slicing

## 题目描述

翻译：有一个n行m列(1<=n,m<=20)的网络蛋糕上有k个樱桃。每次可以用一刀沿着网络线把蛋糕切成两块，并且只能够直切不能拐弯。要求最后每一块蛋糕上恰好有一个樱桃，且切割线总长度最小。

## 输出格式

输入输出样例
输入样例:
3 4 3
1 2
2 3
3 2
输出样例:
Case 1: 5



---

