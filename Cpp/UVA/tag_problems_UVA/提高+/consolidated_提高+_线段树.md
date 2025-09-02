---
title: "Pick-up Sticks"
layout: "post"
diff: 提高+/省选-
pid: UVA10902
tag: ['线段树', '向量', '线段相交']
---

# Pick-up Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1843

[PDF](https://uva.onlinejudge.org/external/109/p10902.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10902/702970269e727240519ea95b134ce15226100639.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10902/3a664d7003b9287c3232980a0beba3fdabca3e46.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10902/fe0d3e9168cc4cfc10d135dee5ab2e9e30f0953d.png)

## 样例 #1

### 输入

```
5
1 1 4 2
2 3 3 1
1 -2.0 8 4
1 4 8 2
3 3 6 -2.0
3
0 0 1 1
1 0 2 1
2 0 3 1
0
```

### 输出

```
Top sticks: 2, 4, 5.
Top sticks: 1, 2, 3.
```



---

---
title: "Permutation"
layout: "post"
diff: 提高+/省选-
pid: UVA11525
tag: ['线段树', '排列组合', '康托展开']
---

# Permutation

## 题目描述

### 题目大意
对于一个给定的$k$ ，求将自然数$1$ ~$k$ 所有的排列按照字典序从小到大排序后位于第$n$ 的排列。排序从$0$ 开始编号。

由于$n$ 有可能很大，所以现在将给你$k$ 个数，分别为$S_1$ ，$S_2$ ，……，$S_k$ ，规定$n$ 的计算方式为

$$n=\sum_{i=1}^k S_i \times (k-i)!$$

## 输入格式

输入文件包含多组数据。

输入文件的第$1$ 行包含一个数$T$ （$\leq 10$ ），为数据组数。

接下来$T$ 组数据，每组数据的第一行包含$1$ 个数$k$ （$1 \leq k \leq 50000$ ），第二行包含$k$ 个整数，第$i$ 个整数表示$S_i$ （$0 \leq S_i \leq k-i$ ）。

## 输出格式

输出文件包含$T$ 行。

对于输入文件的每组数据，输出一行，包含$k$ 个数，为对应的$1$ ~$n$ 的排列。

## 样例 #1

### 输入

```
4
3
2 1 0
3
1 0 0
4
2 1 1 0
4
1 2 1 0
```

### 输出

```
3 2 1
2 1 3
3 2 4 1
2 4 3 1
```



---

---
title: "Fast Matrix Operations"
layout: "post"
diff: 提高+/省选-
pid: UVA11992
tag: ['线段树', '构造']
---

# Fast Matrix Operations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3143

[PDF](https://uva.onlinejudge.org/external/119/p11992.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/9b4b07db5bbb2af0ec8d2e58971ff9ef667aba18.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/c66d9d68dcf16d53358935e75ad9c88d099a7046.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/97cd09c03cc7c50c54aa53c6a7fd6478eaa7a1cf.png)

## 样例 #1

### 输入

```
4 4 8
1 1 2 4 4 5
3 2 1 4 4
1 1 1 3 4 2
3 1 2 4 4
3 1 1 3 4
2 2 1 4 4 2
3 1 2 4 4
1 1 1 4 3 3
```

### 输出

```
45 0 5
78 5 7
69 2 7
39 2 7
```



---

---
title: "Array Transformer"
layout: "post"
diff: 提高+/省选-
pid: UVA12003
tag: ['线段树', '分块']
---

# Array Transformer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3154

[PDF](https://uva.onlinejudge.org/external/120/p12003.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12003/50f071c57d8ce0e0ecfd82014a1327d7ceae7ed2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12003/b1dade64563b7d3030cff0926fd43a341b640a1f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12003/26bb239ed11d0b47045182bf090b6eb09f4ca774.png)

## 样例 #1

### 输入

```
10 1 11
1
2
3
4
5
6
7
8
9
10
2 8 6 10
```

### 输出

```
1
2
3
4
5
6
7
8
9
6
Explanation: There is only one instruction: L = 2, R = 8, v = 6, p = 10. There are 4 numbers
(2,3,4,5) less than 6, so k = 4. The new number in A[10] is 11 ∗ 4/(8 − 2 + 1) = 44/7 = 6.
```



---

---
title: "优化最大值电路 Minimizing Maximizer"
layout: "post"
diff: 提高+/省选-
pid: UVA1322
tag: ['线段树']
---

# 优化最大值电路 Minimizing Maximizer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4068

[PDF](https://uva.onlinejudge.org/external/13/p1322.pdf)

## 样例 #1

### 输入

```
1
40 6
20 30
1 10
10 20
20 30
15 25
30 40
```

### 输出

```
4
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
title: "Kingdom"
layout: "post"
diff: 提高+/省选-
pid: UVA1455
tag: ['线段树', '并查集']
---

# Kingdom

## 题目描述

平面有n个城市，初始时城市之间没有任何双向道路连接。你的任务是依次执行以下任务：



road A B:在城市A和城市B之间连接一条双向道路，保证这条道路不和其他道路在非端点处相交。



line C：询问一条y=C的水平线和多少个州相交，以及这些州一共包含几个城市。在任意时刻，每一组连接的城市形成一个州。在本指令中，C的小数部分保证为0.5.



例如，在图中，y=4.5穿过两个州，共八个城市；y=6.5穿过一个州，共5个城市。

## 输入格式

输入第一行为数据组T。每组数据第一行为一个整数n(1<=n<=100000)。以下n行每行两个整数x,y（0<=x,y<=1000000）,即各城市坐标。城市编号为0~n-1。下一行为指令总数m(1<=m<=200000)。以下m行每行一条指令，其中A,B为不同的整数，且0<=A,B<n；C是小数部分保证为0.5的实数，且0<C<1000000。不会有两条道路连接一对相同的城市。每组数据至少有一条line指令。

## 输出格式

对于每条line指令，输出y=C穿过的州的数目和这些州包含的城市总数



---

