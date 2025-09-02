

---

---
title: "Sumsets"
layout: "post"
diff: 提高+/省选-
pid: UVA10125
tag: ['二分', '枚举', '排序']
---

# Sumsets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1066

[PDF](https://uva.onlinejudge.org/external/101/p10125.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/29d92f1d32bdaefa1d311d7a2aa7e97895e4a322.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/ce194eb546afa406872932e0bd6f9dd4ca894f2d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/bf773b60567946315edebe60d7e76099b6dc0d8e.png)

## 样例 #1

### 输入

```
5
2
3
5
7
12
5
2
16
64
256
1024
0
```

### 输出

```
12
no solution
```



---

---
title: "Machine Schedule"
layout: "post"
diff: 提高+/省选-
pid: UVA1194
tag: ['二分图']
---

# Machine Schedule

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3635

[PDF](https://uva.onlinejudge.org/external/11/p1194.pdf)

## 样例 #1

### 输入

```

5 5 10
0 1 1
1 1 2
2 1 3
3 1 4
4 2 1
5 2 2
6 2 3
7 2 4
8 3 3
9 4 3
0
```

### 输出

```
3
```



---

---
title: "Airport 机场"
layout: "post"
diff: 提高+/省选-
pid: UVA1450
tag: ['二分', '其它技巧']
---

# Airport 机场

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4196

[PDF](https://uva.onlinejudge.org/external/14/p1450.pdf)

## 样例 #1

### 输入

```
3
1
1 1
3
3 2
0 3
2 0
6
0 1
1 1
1 2
1 1
1 1
6 0

```

### 输出

```
0
3
5
```



---



---

# 题号列表

- UVA10125 - Sumsets
- UVA1194 - Machine Schedule
- UVA1450 - Airport 机场


---

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

# 题号列表

- UVA10214 - 树林里的树 Trees in a Wood.
- UVA12003 - Array Transformer


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

# 题号列表

- UVA1400 - "Ray, Pass me the dishes!"


---

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



---

# 题号列表

- UVA10214 - 树林里的树 Trees in a Wood.
- UVA11300 - Spreading the Wealth
- UVA11400 - 照明系统设计 Lighting System Design
- UVA11424 - GCD - Extreme (I)
- UVA1400 - "Ray, Pass me the dishes!"
- UVA1423 - Guess
- UVA1629 - 切蛋糕 Cake slicing


---

---
title: "Raising the Roof"
layout: "post"
diff: 提高+/省选-
pid: UVA1065
tag: ['剪枝']
---

# Raising the Roof

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3506

[PDF](https://uva.onlinejudge.org/external/10/p1065.pdf)



---

---
title: "旋转游戏 The Rotation Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1343
tag: ['剪枝', '启发式迭代加深搜索 IDA*', '构造']
---

# 旋转游戏 The Rotation Game

## 题目描述

　　如图 $1$ 所示，有一个 “#” 形的棋盘，上面有 $1,2,3$ 三种数字各 $8$ 个。给定 $8$ 种操作，分别为图中的 $\text{A}\sim \text{H}$。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 $8$ 的序列循环移动 $1$ 个单位。例如下图最左边的 “#” 形棋盘执行操作 $\text{A}$ 时，会变为图中间的 “#” 形棋盘，再执行操作 $\text{C}$ 后会变为图中最右边的 “#” 形棋盘。
![](https://cdn.luogu.org/upload/pic/40731.png)
$$\text{图 1}$$
　　现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 $8$ 个格子里的数字相同。

## 输入格式

　　输入包括不超过 $30$ 组测试数据。每个测试数据只包括一行，包含 $24$ 个整数，每相邻两个整数之间用 $1$ 个空格隔开，表示这个 “#” 形棋盘的初始状态。（这些整数的排列顺序是从上至下，同一行的从左至右。例如 $\text{1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3}$ 表示图 $1$ 最左边的状态。）每两组测试数据之间没有换行符。输入文件以一行 $0$ 结束。

## 输出格式

　　对于每组测试数据，输出两行。第一行用字符 $\text{A}\sim \text{H}$ 输出操作的方法，**每两个操作字符之间没有空格分开**，如果不需要任何步数，输出 `No moves needed`。第二行输出最终状态中最中间的 $8$ 个格子里的数字。如果有多组解，输出操作次数最少的一组解；如果仍有多组解，输出字典序最小的一组。任意相邻两组测试数据的输出之间不需输出换行符。



---

---
title: "Sudoku Extension"
layout: "post"
diff: 提高+/省选-
pid: UVA1461
tag: ['模拟', '搜索', '剪枝']
---

# Sudoku Extension

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4207

[PDF](https://uva.onlinejudge.org/external/14/p1461.pdf)



---

---
title: "Addition Chains"
layout: "post"
diff: 提高+/省选-
pid: UVA529
tag: ['搜索', '枚举', '剪枝', '搜索']
---

# Addition Chains

## 题目描述

一个与 $n$ 有关的整数加成序列 $<a_0,a_1,a_2,...,a_m>$ 满足以下四个条件：  
 $1.a_0=1$   
 $2.a_m=n$   
 $3.a_0<a_1<a_2<...<a_{m-1}<a_m$   
 $4.$ 对于每一个 $k(1≤k≤m)$ 都存在有两个整数 $i$ 和 $j(0≤i,j≤k-1,i$ 和 $j$ 可以相等 $)$ ，使得 $a_k=a_i+a_j$   
你的任务是：给定一个整数 $n$ ,找出符合上述四个条件的长度最小的整数加成序列。如果有多个满足要求的答案，只需要输出任意一个解即可。  
举个例子，序列 $<1,2,3,5>$ 和 $<1,2,4,5>$ 均为 $n=5$ 时的解。

## 输入格式

输入包含多组数据。每组数据仅一行包含一个整数 $n(1≤n≤10000)$ 。在最后一组数据之后是一个 $0$ 。

## 输出格式

对于每组数据，输出一行所求的整数加成序列，每个整数之间以空格隔开。

感谢@Iowa_BattleShip 提供的翻译

## 样例 #1

### 输入

```
5
7
12
15
77
0
```

### 输出

```
1 2 4 5
1 2 4 6 7
1 2 4 8 12
1 2 4 5 10 15
1 2 4 8 9 17 34 68 77
```



---



---

# 题号列表

- UVA1065 - Raising the Roof
- UVA1343 - 旋转游戏 The Rotation Game
- UVA1461 - Sudoku Extension
- UVA529 - Addition Chains


---

---
title: "城市里的间谍 A Spy in the Metro"
layout: "post"
diff: 提高+/省选-
pid: UVA1025
tag: ['动态规划 DP', '枚举']
---

# 城市里的间谍 A Spy in the Metro

## 题目描述

#### 题目大意

某城市地铁是一条直线，有 $n$（$2\leq	 n\leq	 50$）个车站，从左到右编号 $1\ldots n$。有 $M_1$ 辆列车从第 $1$ 站开始往右开，还有 $M_2$ 辆列车从第 $n$ 站开始往左开。列车在相邻站台间所需的运行时间是固定的，因为所有列车的运行速度是相同的。在时刻 $0$，Mario 从第 $1$ 站出发，目的在时刻 $T$（$0\leq T\leq 200$）会见车站 $n$ 的一个间谍。在车站等车时容易被抓，所以她决定尽量躲在开动的火车上，让在车站等待的时间尽量短。列车靠站停车时间忽略不计，且 Mario 身手敏捷，即使两辆方向不同的列车在同一时间靠站，Mario 也能完成换乘。

## 输入格式

输入文件包含多组数据。

每一组数据包含以下 $7$ 行：

第一行是一个正整数 $n$，表示有 $n$ 个车站。

第二行是为 $T$，表示 Mario 在时刻 $T$ 会见车站 $n$ 的间谍。

第三行有 $n-1$ 个整数 $t_1,t_2,\ldots,t_{n-1}$，其中 $t_i$ 表示地铁从车站 $i$ 到 $i+1$ 的行驶时间。


第四行为 $M_1$，及从第一站出发向右开的列车数目。

第五行包含 $M_1$ 个正整数 $a_1,a_2,\ldots,a_{M_1}$，即每个列车出发的时间。

第六行为 $M_2$ ，即从第 $n$ 站出发向左开的列车数目。

第七行包含 $M_2$ 个正整数 $b_1,b_2,\ldots,b_{M_2}$，即每个列车出发的时间。

输入文件以一行 $0$ 结尾。

## 输出格式

有若干行，每行先输出 ```Case Number XXX : ```（XXX为情况编号，从 $1$ 开始），再输出最少等待时间或 ```impossible```（无解）。

## 样例 #1

### 输入

```
4
55
5 10 15
4
0 5 10 20
4
0 5 10 15
4
18
1 2 3
5
0 3 6 10 12
6
0 3 5 7 12 15
2
30
20
1
20
7
1 3 5 7 11 13 17
0

```

### 输出

```
Case Number 1: 5
Case Number 2: 0
Case Number 3: impossible

```



---

---
title: "Optimal Binary Search Tree"
layout: "post"
diff: 提高+/省选-
pid: UVA10304
tag: ['动态规划 DP', '区间 DP']
---

# Optimal Binary Search Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1245

[PDF](https://uva.onlinejudge.org/external/103/p10304.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/8240dddbc7a394a9919bfe12ea1df0e5a38b12ed.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/5b63358ad156699ebafb2a0a0b6d27baf4fd1d2b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10304/79b21d984f95af03e88a2fb005e341d755d171c2.png)

## 样例 #1

### 输入

```
1 5
3 10 10 10
3 5 10 20
```

### 输出

```
0
20
20
```



---

---
title: "Ferry Loading II"
layout: "post"
diff: 提高+/省选-
pid: UVA10440
tag: ['动态规划 DP', '贪心']
---

# Ferry Loading II

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1381

[PDF](https://uva.onlinejudge.org/external/104/p10440.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/62f4e72b9730523fdb77b04f21f28f29a3eff81d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/0bb9d3b2914964e55e2370002ec531eaa0ab40b4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/4a97c3e41ba3630f0efc866c67bde50939a5e9db.png)

## 样例 #1

### 输入

```
2
2 10 10
0
10
20
30
40
50
60
70
80
90
2 10 3
10
30
40
```

### 输出

```
100 5
50 2
```



---

---
title: "Multi-peg Towers of Hanoi"
layout: "post"
diff: 提高+/省选-
pid: UVA10444
tag: ['动态规划 DP', '高精度', '递推']
---

# Multi-peg Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1385

[PDF](https://uva.onlinejudge.org/external/104/p10444.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/b08ae043c16349a4e020bb344c82bd8559661c15.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/9918d07219dee733e043308fe7408963612853cc.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/28c5f29618658abb670593f72b8636cd5eadedfe.png)

## 样例 #1

### 输入

```
3 4
4 4
10 4
10 5
0 0
```

### 输出

```
Case 1: 5
Case 2: 9
Case 3: 49
Case 4: 31
```



---

---
title: "校长的烦恼 Headmaster's Headache"
layout: "post"
diff: 提高+/省选-
pid: UVA10817
tag: ['动态规划 DP', '状态合并', '进制']
---

# 校长的烦恼 Headmaster's Headache

## 题目描述

斯普林菲尔德（春之田野？？？）学院的校长正在考虑为某些科目招聘新老师 现在有一批申请岗位的老师 每个老师能教一个或多个科目 校长想要选择一些申请者以保证每个科目都至少有两名老师能教 同时总共花的钱要最小

## 输入格式

输入由多组测试组成，它们的格式如下： 第一行包含三个给定的整数S，M和N， S (<=8)是科目的总数 M(<=20)是在职教师数，N(<=100)是应聘者的数量

接下来M行每行描述一个在职教师 首先给出雇佣他的花费C (10000<=C<=50000) ,接下来是他能教的科目列表 科目用1—S的整数表示 你必须保证继续聘用他们

之后N行，以同样格式给出应聘者的信息

输入以一个空测试S=0结束，你不应当处理它 （这句有些别扭，不过懂意思就好）

## 输出格式

对于每组测试，输出符合条件的最小花费
翻译贡献者UID：60885

## 样例 #1

### 输入

```
2 2 2
10000 1
20000 2
30000 1 2
40000 1 2
0 0 0
```

### 输出

```
60000
```



---

---
title: "放置街灯 Placing Lampposts"
layout: "post"
diff: 提高+/省选-
pid: UVA10859
tag: ['动态规划 DP']
---

# 放置街灯 Placing Lampposts

## 题目描述

# 题面描述

给定一个 $n$ 个点 $m$ 条边的无向无环图，在尽量少的节点上放灯，使得所有边都与灯相邻（被灯照亮）。

在灯的总数最小的前提下，被两盏灯同时照亮的边数应该尽可能大。

## 输入格式

第一行输入 $T$ ,为数据组数。

每组数据第一行输入 $n,m$，分别为该组数据中图的点数和边数。

以下 $m$ 行，输入各边的两端点 $u,v$。

## 输出格式

输出共 $T$ 行。

对每组数据，一行输出三个数，最小灯数、被两盏灯同时照亮的边数、只被一盏灯照亮的边数。

## 样例 #1

### 输入

```
2
4 3
0 1
1 2
2 3
5 4
0 1
0 2
0 3
0 4
```

### 输出

```
2 1 2
1 0 4
```



---

---
title: "Game of Sum"
layout: "post"
diff: 提高+/省选-
pid: UVA10891
tag: ['动态规划 DP']
---

# Game of Sum

## 题目描述

有一个长度为 $n$ 的整数序列，两个游戏者 $A$ 和 $B$ 轮流取数，$A$ 先取。每次玩家只能从左端或者右端取任意数量的数，但不能两边都取。所有数都被取走视为游戏结束，然后统计每个人取走的数之和，作为各自的得分。两个人采取的策略都是让自己得分尽可能高，并且两个人都很机智，求 $A$ 得分 - $B$ 得分后的结果。

## 输入格式

输入包含多组数据，每组数据第一行为正整数 $n(1\leq n\leq 100)$ ，第二行为给定的整数序列，输入结束标志是 $n=0$ 。

## 输出格式

对于每组数据，输出 $A$ 和 $B$ 都采取最优策略下，$A$ 的得分$-B$ 的得分。


感谢 @额冻豆腐  提供的翻译

## 样例 #1

### 输入

```
4
4 -10 -20 7
4
1 2 3 4
0
```

### 输出

```
7
10
```



---

---
title: "Tiling Dominoes"
layout: "post"
diff: 提高+/省选-
pid: UVA11270
tag: ['动态规划 DP', '进制', '插头 DP']
---

# Tiling Dominoes

## 题目描述

题目大意

给定一个m×n的矩形网格，用1×2多米诺骨牌完全平铺。 请注意，即使一个平铺的旋转与另一个平铺相匹配，它们仍算作不同的平铺。 下面显示了一个平铺示例。

## 输入格式

输入包括多组数据。每组数据占一行，包含两个整数m，n（n×m≤100）。输入结束标志为文件结束符（EOF）。

## 输出格式

对于每组数据输出一行，输出总数。

## 样例 #1

### 输入

```
2 10
4 10
8 8
```

### 输出

```
89
18061
12988816
```



---

---
title: "完美的服务 Perfect Service"
layout: "post"
diff: 提高+/省选-
pid: UVA1218
tag: ['动态规划 DP', '递归', '枚举']
---

# 完美的服务 Perfect Service

## 题目描述

一个网络中有 $N$ 个节点，由 $N-1$ 条边连通，每个节点是服务器或者客户端。如果节点 $u$ 是客户端，就意味着 $u$ 所连接的所有点中有且仅有一台服务器。求最少要多少台服务器才能满足要求。

## 输入格式

输入包含多组测试数据。对于每组数据，第一行是一个整数 $N(\le10000)$。

接下来 $N-1$ 行，每行两个整数 $a_i,b_i$，表示 $a_i,b_i$ 有一条双向连通的边。

除最后一组输入以外，每组数据以 $0$ 结尾，最后一组数据以 $-1$ 结尾。

## 输出格式

对于每组输入，仅输出一行，表示所需要的最小服务器台数。

翻译贡献者：An_Account.



---

---
title: "20个问题 Twenty Questions"
layout: "post"
diff: 提高+/省选-
pid: UVA1252
tag: ['动态规划 DP', '标签464']
---

# 20个问题 Twenty Questions

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3693

[PDF](https://uva.onlinejudge.org/external/12/p1252.pdf)



---

---
title: "Dance Dance Revolution"
layout: "post"
diff: 提高+/省选-
pid: UVA1291
tag: ['动态规划 DP']
---

# Dance Dance Revolution

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=4037

[PDF](https://uva.onlinejudge.org/external/12/p1291.pdf)



---

---
title: "Jump"
layout: "post"
diff: 提高+/省选-
pid: UVA1452
tag: ['动态规划 DP']
---

# Jump

## 题目背景

扩展约瑟夫环问题。

## 题目描述

[problemUrl]: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4198

编号为 $1,2,...n$ 的人围坐在圆桌周围。从 $1$ 号开始报数，报到 $k$ 的人出列，他的下一个人又重新从 $1$ 开始报数，数到 $k$ 的人又出列；依次下去，直到圆桌上所有人都出列。给定 $n$ 与 $k$，求最后出列的三个人的编号。

例如 $n=10,k=2$，出列顺序为 `2，4，6，8，10，3，7，1，9，5`。那么答案为 `1 9 5`。

## 输入格式

第一行为数据组数 $T$。接下来 $T$ 行，每行包含两个数字 $n,k$ 。



## 输出格式

对每一组数据，输出一行，分别是倒数第三，倒数第二，倒数第一的序号，每个序号用空格隔开。

## 说明/提示

$5≤n≤5\times 10^5,2≤k≤5\times 10^5$ 。

## 样例 #1

### 输入

```
1
10 2
```

### 输出

```
1 9 5
```



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

---
title: "纸牌游戏 Double Patience"
layout: "post"
diff: 提高+/省选-
pid: UVA1637
tag: ['动态规划 DP', '搜索', '概率论']
---

# 纸牌游戏 Double Patience

## 题目描述

Double  Patience是一种单人游戏，使用标准的36张牌组。这些牌在洗牌后放在一张桌子上，叠成9叠，每叠4张，面朝上。



牌放下后，玩家转身。每一次，他可以从任意两个牌堆中取出同一等级的顶级牌，然后将它们移除。如果有几种可能性，玩家可以选择任何一种。如果所有的牌都从桌上移除，玩家将赢得游戏，如果一些牌仍然在桌上，并且没有有效的移动，玩家将失败。



乔治喜欢这种游戏。但当有几种可能时，他不知道要选择哪一张。乔治不想多想，所以在这种情况下，他只需从可能的情况中选择一对随机的，并删除它。乔治选择每种情况的可能性相同。



例如，如果最上面的牌是Ks、Kh、Kd、9h、8s、8d、7c、7d和6h，他会删除任何一对在(KS, KH)、(KS, KD)、(KH, KD)、 (8S, 8D)和 (7C, 7D)中的任何一对。删除（Ks,Kh）、（Ks,Kd）、（Kh,Kd）、（8s,8d）和（7c,7d）的概率都为1/5。



请算出在游戏开始时，根据桌上的牌，找出如果乔治按照描述行事，他赢得游戏的可能性是多少。

## 输入格式

输入文件包含几个测试用例，每个测试用例由九行组成。每行包含四张牌的描述，它们在游戏开始时形成一堆，从下一张牌到上一张牌。



每张卡片有两个字符：一个用于等级，一个用于花色。等级用“6”表示6，“7”表示7，“8”表示8，“9”表示9，“T”表示10，“J”表示杰克，“Q”表示女王，“K”表示国王，“A”表示王牌。花色用“S”代表黑桃，C代表梅花，D代表钻石，H代表红桃。例如，“KS”表示黑桃王。



每个卡片描述之间用一个空格隔开。

## 输出格式

对于每个测试用例，输出一行实数-如果乔治随机玩游戏，他赢得游戏的概率。您的答案必须精确到小数点后6位

## 样例输入，输出略



---

---
title: "巴比伦塔 The Tower of Babylon"
layout: "post"
diff: 提高+/省选-
pid: UVA437
tag: ['动态规划 DP', '搜索', '递推', '排序']
---

# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 输入格式

输入会包含至少一组数据，每组数据的第一行是一个整数 $n(n\le30)$，表示方块的种类数。 这组数据接下来的 $n$ 行，每行有三个整数，表示 $xi,yi,zi$。输入数据会以 $0$ 结束。

## 输出格式

对于每组数据，输出一行，其中包含组号（从 $1$ 开始）和塔最高的高度。按以下格式：``Case i: maximum height = __``。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342
```



---



---

# 题号列表

- UVA1025 - 城市里的间谍 A Spy in the Metro
- UVA10304 - Optimal Binary Search Tree
- UVA10440 - Ferry Loading II
- UVA10444 - Multi-peg Towers of Hanoi
- UVA10817 - 校长的烦恼 Headmaster's Headache
- UVA10859 - 放置街灯 Placing Lampposts
- UVA10891 - Game of Sum
- UVA11270 - Tiling Dominoes
- UVA1218 - 完美的服务 Perfect Service
- UVA1252 - 20个问题 Twenty Questions
- UVA1291 - Dance Dance Revolution
- UVA1452 - Jump
- UVA1629 - 切蛋糕 Cake slicing
- UVA1637 - 纸牌游戏 Double Patience
- UVA437 - 巴比伦塔 The Tower of Babylon


---

---
title: "Almost Union-Find"
layout: "post"
diff: 提高+/省选-
pid: UVA11987
tag: ['并查集', '平衡树', '哈希 hashing']
---

# Almost Union-Find

## 题目描述

有 $n$ 个集合，$m$ 次操作。规定第 $i$ 个集合里初始只有 $i$。有三种操作：

1. 输入两个元素 $p$ 和 $q$，若 $p$ 和 $q$ 不在一个集合中，合并两个元素的集合。
2. 输入两个元素 $p$ 和 $q$，若 $p$ 和 $q$ 不在一个集合中，把 $p$ 添加到 $q$ 所在的集合。
3. 输入一个元素 $p$，查询 $p$ 所在集合的元素个数和所有元素之和。

## 输入格式

有几组数据。

每组数据第一行输入 $n$ 和 $m$ 两个整数。

每组数据以下 $m$ 行，每行第一个数 $k$ 代表选择哪一个命令，若 $k$ 是 $1$ 或 $2$ 命令，则再输入两个整数 $p$ 和 $q$。若 $k$ 是 $3$，则输入一个整数 $p$。

输入文件结束符（EOF）结束输入。

## 输出格式

输出行数为每组数据 $3$ 号命令的总数。

每一行输出两个整数 $a$ 和 $b$，即元素个数和元素和。

## 说明/提示

$1 \leq  n,m\leq 10 ^ 5$，$1 \leq  p,q\leq n$。

## 样例 #1

### 输入

```
5 7
1 1 2
2 3 4
1 3 5
3 4
2 4 1
3 4
3 3
```

### 输出

```
3 12
3 7
2 8
```



---



---

# 题号列表

- UVA11987 - Almost Union-Find


---

---
title: "多少块土地 How Many Pieces of Land ?"
layout: "post"
diff: 提高+/省选-
pid: UVA10213
tag: ['图论', '高精度']
---

# 多少块土地 How Many Pieces of Land ?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1154

[PDF](https://uva.onlinejudge.org/external/102/p10213.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10213/82410c5d60b6479b7a08f094e449cc42577c84fa.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10213/12cbe469542e974964720e963806931c43bb097f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10213/36cbbf8a0535026ec0f15834fa670c7e8256bd64.png)

## 样例 #1

### 输入

```
4
1
2
3
4
```

### 输出

```
1
2
4
8
```



---

---
title: "Falling Leaves"
layout: "post"
diff: 提高+/省选-
pid: UVA1525
tag: ['字符串', '搜索', '平衡树', '图论建模']
---

# Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4300

[PDF](https://uva.onlinejudge.org/external/15/p1525.pdf)



---

---
title: "Abbott的复仇 Abbott's Revenge"
layout: "post"
diff: 提高+/省选-
pid: UVA816
tag: ['广度优先搜索 BFS', '图论建模', '最短路']
---

# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/4939e773b1884a681cdc9dbd1fe1251df58b072b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/9ff2bb3a862e6ca3e356ecb98a558f994c9d7f5d.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz
```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
```



---



---

# 题号列表

- UVA10213 - 多少块土地 How Many Pieces of Land ?
- UVA1525 - Falling Leaves
- UVA816 - Abbott的复仇 Abbott's Revenge


---

---
title: "Treblecross"
layout: "post"
diff: 提高+/省选-
pid: UVA10561
tag: ['字符串', '搜索']
---

# Treblecross

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1502

[PDF](https://uva.onlinejudge.org/external/105/p10561.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/31bc60cd2679d5a858bab6338b6a91a761cb246d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/f3a035fa62c3266f7235864450f9f70c79fb3298.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/9aa18e2eb8be86e1d3e3cb2e789c20ffbc1a2cbf.png)

## 样例 #1

### 输入

```
4
.....
X.....X..X.............X....X..X
.X.X...X
...............................................
```

### 输出

```
WINNING
3
LOSING
WINNING
3
WINNING
1 12 15 17 20 24 28 31 33 36 47
```



---

---
title: "Hyper Prefix Sets"
layout: "post"
diff: 提高+/省选-
pid: UVA11488
tag: ['字符串']
---

# Hyper Prefix Sets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2483

[PDF](https://uva.onlinejudge.org/external/114/p11488.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/b054540c80bd466e35ea7b5ef13a250519cecff4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/fc8e7263656e721ab7ea67390fda22bec8d391d1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/144ebe3d0def2038245a39df7775b227fb650280.png)

## 样例 #1

### 输入

```
4
4
0000
0001
10101
010
2
01010010101010101010
11010010101010101010
3
010101010101000010001010
010101010101000010001000
010101010101000010001010
5
01010101010100001010010010100101
01010101010100001010011010101010
00001010101010110101
0001010101011010101
00010101010101001
```

### 输出

```
6
20
66
44
```



---

---
title: "生成排列 Generating Permutations"
layout: "post"
diff: 提高+/省选-
pid: UVA11925
tag: ['字符串', '构造']
---

# 生成排列 Generating Permutations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3076

[PDF](https://uva.onlinejudge.org/external/119/p11925.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/4ae01d3bad0e00d10dd54ea1a36732d8994153c9.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/39a915f8fa7c330f6d88d2084592f1cdbcc50f29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/b09493d267f3d2d325027cbace89abb524055c4a.png)

## 样例 #1

### 输入

```
3 2 1 3
3 2 3 1
4 4 2 3 1
0
```

### 输出

```
1
2
12122
```



---

---
title: "Bribing FIPA"
layout: "post"
diff: 提高+/省选-
pid: UVA1222
tag: ['字符串', '离散化', '背包 DP']
---

# Bribing FIPA

## 题目描述

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。

## 输入格式

多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。


多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。

## 输出格式

对于每组输入数据，输出一行表示答案。
```
UVA1222

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。


对于每组输入数据，输出一行表示答案。
样例输入：
3 2
Aland 10
Boland 20 Aland
Coland 15
#

样例输出：
20



---

---
title: "Jurassic Remains"
layout: "post"
diff: 提高+/省选-
pid: UVA1326
tag: ['字符串', '搜索', '枚举']
---

# Jurassic Remains

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4072

[PDF](https://uva.onlinejudge.org/external/13/p1326.pdf)



---

---
title: "Falling Leaves"
layout: "post"
diff: 提高+/省选-
pid: UVA1525
tag: ['字符串', '搜索', '平衡树', '图论建模']
---

# Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4300

[PDF](https://uva.onlinejudge.org/external/15/p1525.pdf)



---



---

# 题号列表

- UVA10561 - Treblecross
- UVA11488 - Hyper Prefix Sets
- UVA11925 - 生成排列 Generating Permutations
- UVA1222 - Bribing FIPA
- UVA1326 - Jurassic Remains
- UVA1525 - Falling Leaves


---

---
title: "Intervals"
layout: "post"
diff: 提高+/省选-
pid: UVA1723
tag: ['差分约束', '差分']
---

# Intervals

## 题目描述

有 $n$ 个区间，在区间 $[a_i,b_i]$ 中至少取任意互不相同的 $c_i$ 个整数。求在满足 $n$ 个区间的情况下，至少要取多少个正整数。

## 输入格式

**本题有多组数据**。

第一行的一个整数 $T$ 表示数据个数，后面有一行空行。

对于每组数据：

第一行包含一个整数 $n(1\leq n\leq 50000)$ 表示区间数。

以下 $n$ 行描述区间。

输入的第 $i+1$ 行包含三个整数 $a_i,b_i,c_i$，由空格分开。其中 $0\leq a_i\leq b_i\leq 50000，1\leq c_i\leq b_i-a_i+1$。

## 输出格式

对于每组数据，输出一个对于 $n$ 个区间 $[a_i,b_i]$ 
至少取 $c_i$ 个不同整数的数的总个数。

**在除了最后一组数据后输出空行。**

### 样例

input：

```
1

5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1
```

output：

```
6
```


### 样例解释

可以取 $3,4,5,8,9,10$，为符合条件且取数个数最少的一组解。

感谢@[LittleDino](https://www.luogu.com.cn/user/60563) 提供的翻译。



---



---

# 题号列表

- UVA1723 - Intervals


---

---
title: "Almost Union-Find"
layout: "post"
diff: 提高+/省选-
pid: UVA11987
tag: ['并查集', '平衡树', '哈希 hashing']
---

# Almost Union-Find

## 题目描述

有 $n$ 个集合，$m$ 次操作。规定第 $i$ 个集合里初始只有 $i$。有三种操作：

1. 输入两个元素 $p$ 和 $q$，若 $p$ 和 $q$ 不在一个集合中，合并两个元素的集合。
2. 输入两个元素 $p$ 和 $q$，若 $p$ 和 $q$ 不在一个集合中，把 $p$ 添加到 $q$ 所在的集合。
3. 输入一个元素 $p$，查询 $p$ 所在集合的元素个数和所有元素之和。

## 输入格式

有几组数据。

每组数据第一行输入 $n$ 和 $m$ 两个整数。

每组数据以下 $m$ 行，每行第一个数 $k$ 代表选择哪一个命令，若 $k$ 是 $1$ 或 $2$ 命令，则再输入两个整数 $p$ 和 $q$。若 $k$ 是 $3$，则输入一个整数 $p$。

输入文件结束符（EOF）结束输入。

## 输出格式

输出行数为每组数据 $3$ 号命令的总数。

每一行输出两个整数 $a$ 和 $b$，即元素个数和元素和。

## 说明/提示

$1 \leq  n,m\leq 10 ^ 5$，$1 \leq  p,q\leq n$。

## 样例 #1

### 输入

```
5 7
1 1 2
2 3 4
1 3 5
3 4
2 4 1
3 4
3 3
```

### 输出

```
3 12
3 7
2 8
```



---

---
title: "苗条的生成树 Slim Span"
layout: "post"
diff: 提高+/省选-
pid: UVA1395
tag: ['并查集', '排序', '生成树']
---

# 苗条的生成树 Slim Span

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4141

[PDF](https://uva.onlinejudge.org/external/13/p1395.pdf)



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



---

# 题号列表

- UVA11987 - Almost Union-Find
- UVA1395 - 苗条的生成树 Slim Span
- UVA1455 - Kingdom


---

---
title: "理想路径 Ideal Path"
layout: "post"
diff: 提高+/省选-
pid: UVA1599
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 输入格式

输入共$m+1$行：

第一行$2$个空格整数：$n$和$m$。

以后$m$行，每行空格隔开的$3$个整数$a_i,b_i,c_i$，表示在$a_i,b_i$之间有一条颜色为$c_i$的道路。

## 输出格式

输出共两行：

第一行$1$个正整数$k$，表示$1$到$n$至少需要经过$k$条边。

第二行包含$k$个空格隔开的正整数，表示从$1$到$n$依次经过的边的**颜色**。

## 输入输出样例：
### 输入样例：
```
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
```
### 输出样例：
```
2
1 3
```
### 输入输出样例解释：
路径依次如下：

$1\rightarrow3$，颜色为$1$（最后输入的那条）；

$3\rightarrow4$，颜色为$3$。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译



---

---
title: "Solitaire"
layout: "post"
diff: 提高+/省选-
pid: UVA1724
tag: ['搜索', '广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# Solitaire

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=859&page=show_problem&problem=4862

[PDF](https://uva.onlinejudge.org/external/17/p1724.pdf)

## 样例 #1

### 输入

```
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



---

---
title: "Abbott的复仇 Abbott's Revenge"
layout: "post"
diff: 提高+/省选-
pid: UVA816
tag: ['广度优先搜索 BFS', '图论建模', '最短路']
---

# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/4939e773b1884a681cdc9dbd1fe1251df58b072b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/9ff2bb3a862e6ca3e356ecb98a558f994c9d7f5d.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz
```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
```



---



---

# 题号列表

- UVA1599 - 理想路径 Ideal Path
- UVA1724 - Solitaire
- UVA816 - Abbott的复仇 Abbott's Revenge


---

---
title: "Sumsets"
layout: "post"
diff: 提高+/省选-
pid: UVA10125
tag: ['二分', '枚举', '排序']
---

# Sumsets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1066

[PDF](https://uva.onlinejudge.org/external/101/p10125.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/29d92f1d32bdaefa1d311d7a2aa7e97895e4a322.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/ce194eb546afa406872932e0bd6f9dd4ca894f2d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/bf773b60567946315edebe60d7e76099b6dc0d8e.png)

## 样例 #1

### 输入

```
5
2
3
5
7
12
5
2
16
64
256
1024
0
```

### 输出

```
12
no solution
```



---

---
title: "Piotr's Ants"
layout: "post"
diff: 提高+/省选-
pid: UVA10881
tag: ['排序']
---

# Piotr's Ants

## 题目描述

一根长度为$L$厘米的木棍上有$n$只蚂蚁，每只蚂蚁要么向左爬，要么向右爬，速度为$1$厘米/秒。当两只蚂蚁相遇时，它们同时掉头（时间忽略不计）。给出每只蚂蚁的初始位置和朝向，请计算$T$秒后每只蚂蚁的位置。

　

## 输入格式

输入第一行为测试数据组数$N$，接下来一共$N$组数据，每组数据的第一行为$3$个整数$L,T,n(0<=n<=10000)$,以下$n$行每行描述了一只蚂蚁的初始位置。其中，整数$x$为它距离木棍左端的距离(单位：厘米).字母表示初始朝向($L$表示朝左，$R$表示向右)

  　

## 输出格式

对于每组数据，输出$n$行，按输入顺序给出每只蚂蚁的位置和朝向($Turning$ 表示正在碰撞)，在第$T$秒之前已经掉下的蚂蚁(正好爬到木棍边缘的不算)输出Fell off.

Translated by @洛谷万岁

## 样例 #1

### 输入

```
2
10 1 4
1 R
5 R
3 L
10 R
10 2 3
4 R
5 L
8 R
```

### 输出

```
Case #1:
2 Turning
6 R
2 Turning
Fell off

Case #2:
3 L
6 R
10 R
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
title: "Following Orders"
layout: "post"
diff: 提高+/省选-
pid: UVA124
tag: ['搜索', '深度优先搜索 DFS', '拓扑排序']
---

# Following Orders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=60

[PDF](https://uva.onlinejudge.org/external/1/p124.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/a4a2f6fd96f29dbbab122912895a18a100222b62.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/54c2361014489729658ffc3ced224b7aa260b8c2.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/d3b6edfcc40cb2874efe9a2a99da24fc2905e6df.png)

## 样例 #1

### 输入

```
a b f g
a b b f
v w x y z
v y x v z v w v
```

### 输出

```
abfg
abgf
agbf
gabf
wxzvy
wzxvy
xwzvy
xzwvy
zwxvy
zxwvy
```



---

---
title: "Wall"
layout: "post"
diff: 提高+/省选-
pid: UVA1303
tag: ['排序', '概率论', '凸包']
---

# Wall

## 题目描述

给定一些点，求出最短的包围所有点的轮廓且满足任意点到轮廓的距离不小于给定的$L$。

## 输入格式

第一行一个正整数$T$，代表数据组数。



接下来$T$组数据，对于每组数据，第一行为两个整数$n,L,(3\le n\le 1000,1\le L\le 1000)$，分别代表点的个数和点距离轮廓的最小距离。接下来$n$行，每行两个整数$X_i,Y_i(-10000\le X_i,Y_i\le 10000)$，表示点的坐标。

## 输出格式

输出共$2T$行，对于每组数据，**四舍五入至整数位**输出答案，并空一行。同时，最后一组数据后仅有一个空行。



例如：这是当$T=2$时，两组数据均为样例的答案，`----`表空行。

```

1628

----

1628

----

```



---

---
title: "苗条的生成树 Slim Span"
layout: "post"
diff: 提高+/省选-
pid: UVA1395
tag: ['并查集', '排序', '生成树']
---

# 苗条的生成树 Slim Span

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4141

[PDF](https://uva.onlinejudge.org/external/13/p1395.pdf)



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
title: "巴比伦塔 The Tower of Babylon"
layout: "post"
diff: 提高+/省选-
pid: UVA437
tag: ['动态规划 DP', '搜索', '递推', '排序']
---

# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 输入格式

输入会包含至少一组数据，每组数据的第一行是一个整数 $n(n\le30)$，表示方块的种类数。 这组数据接下来的 $n$ 行，每行有三个整数，表示 $xi,yi,zi$。输入数据会以 $0$ 结束。

## 输出格式

对于每组数据，输出一行，其中包含组号（从 $1$ 开始）和塔最高的高度。按以下格式：``Case i: maximum height = __``。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342
```



---



---

# 题号列表

- UVA10125 - Sumsets
- UVA10881 - Piotr's Ants
- UVA11300 - Spreading the Wealth
- UVA11400 - 照明系统设计 Lighting System Design
- UVA124 - Following Orders
- UVA1303 - Wall
- UVA1395 - 苗条的生成树 Slim Span
- UVA1423 - Guess
- UVA437 - 巴比伦塔 The Tower of Babylon


---

---
title: "Crossing Streets"
layout: "post"
diff: 提高+/省选-
pid: UVA1043
tag: ['搜索', '离散化']
---

# Crossing Streets

## 题目描述

Peter 要从家到学校，他想要规划穿过马路条数最少的路线。

给定 $n$ 条马路的起始点与终点坐标（马路一定与坐标轴平行），以及 Peter 家和大学所在位置坐标。求 Peter 从家到大学的任意路径下最少穿过多少条马路。特别地，Peter 不能穿过马路之间的交点。

## 输入格式

题目含有多组数据。

对于每组数据：

第一行，输入一个整数 $n$，代表马路条数。

接下来 $n$ 行，每行四个数 $x_1,y_1,x_2,y_2$，代表一条马路起点与终点坐标。

接下来一行四个数，$x_h,y_h,x_u,y_u$，代表 Peter 家的坐标与大学的坐标。

当输入的 $n$ 为 $0$ 时，结束程序。

## 输出格式

对于每组数据，输出 $2$ 行，格式如下：
```
City [i]
Peter has to cross [x] streets
```
其中 `i` 代表是第几组数据，`x` 代表答案（不包含 `[]`）。

## 说明/提示

$1\le n\le 500$，所有输入的坐标绝对值不大于 $2\times 10^9$。

Translated by HYdroKomide.

## 样例 #1

### 输入

```
8
6 0 24 0
24 0 24 4
24 4 6 4
6 4 6 0
12 1 26 1
26 1 26 6
26 6 12 6
12 6 12 1
0 1 17 3
1
10 10 20 10
1 1 30 30
0
```

### 输出

```
City 1
Peter has to cross 2 streets
City 2
Peter has to cross 0 streets
```



---

---
title: "Treblecross"
layout: "post"
diff: 提高+/省选-
pid: UVA10561
tag: ['字符串', '搜索']
---

# Treblecross

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1502

[PDF](https://uva.onlinejudge.org/external/105/p10561.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/31bc60cd2679d5a858bab6338b6a91a761cb246d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/f3a035fa62c3266f7235864450f9f70c79fb3298.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/9aa18e2eb8be86e1d3e3cb2e789c20ffbc1a2cbf.png)

## 样例 #1

### 输入

```
4
.....
X.....X..X.............X....X..X
.X.X...X
...............................................
```

### 输出

```
WINNING
3
LOSING
WINNING
3
WINNING
1 12 15 17 20 24 28 31 33 36 47
```



---

---
title: "The Largest Clique"
layout: "post"
diff: 提高+/省选-
pid: UVA11324
tag: ['搜索', '记忆化搜索', '强连通分量']
---

# The Largest Clique

## 题目描述

给你一张有向图 $G$，求一个结点数最大的结点集，使得该结点集中的任意两个结点 $u$ 和 $v$ 满足：要么 $u$ 可以达 $v$，要么 $v$ 可以达 $u$ （$u,v$ 相互可达也行）。

## 输入格式

第一行，输入一个整数，代表测试数据组数 $T$，每组数据的格式如下。

第一行为结点数 $n$ 和边数 $m$，结点编号 $1 \sim n$。

以下 $m$ 行每行两个整数 $u$ 和 $v$ ，表示一条有向边 $u \to v$。

## 输出格式

对于每组数据，输出最大结点集的结点数。

## 样例 #1

### 输入

```
1
5 5
1 2
2 3
3 1
4 1
5 2
```

### 输出

```
4
```



---

---
title: "Following Orders"
layout: "post"
diff: 提高+/省选-
pid: UVA124
tag: ['搜索', '深度优先搜索 DFS', '拓扑排序']
---

# Following Orders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=60

[PDF](https://uva.onlinejudge.org/external/1/p124.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/a4a2f6fd96f29dbbab122912895a18a100222b62.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/54c2361014489729658ffc3ced224b7aa260b8c2.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/d3b6edfcc40cb2874efe9a2a99da24fc2905e6df.png)

## 样例 #1

### 输入

```
a b f g
a b b f
v w x y z
v y x v z v w v
```

### 输出

```
abfg
abgf
agbf
gabf
wxzvy
wzxvy
xwzvy
xzwvy
zwxvy
zxwvy
```



---

---
title: "Jurassic Remains"
layout: "post"
diff: 提高+/省选-
pid: UVA1326
tag: ['字符串', '搜索', '枚举']
---

# Jurassic Remains

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4072

[PDF](https://uva.onlinejudge.org/external/13/p1326.pdf)



---

---
title: "旋转游戏 The Rotation Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1343
tag: ['剪枝', '启发式迭代加深搜索 IDA*', '构造']
---

# 旋转游戏 The Rotation Game

## 题目描述

　　如图 $1$ 所示，有一个 “#” 形的棋盘，上面有 $1,2,3$ 三种数字各 $8$ 个。给定 $8$ 种操作，分别为图中的 $\text{A}\sim \text{H}$。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 $8$ 的序列循环移动 $1$ 个单位。例如下图最左边的 “#” 形棋盘执行操作 $\text{A}$ 时，会变为图中间的 “#” 形棋盘，再执行操作 $\text{C}$ 后会变为图中最右边的 “#” 形棋盘。
![](https://cdn.luogu.org/upload/pic/40731.png)
$$\text{图 1}$$
　　现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 $8$ 个格子里的数字相同。

## 输入格式

　　输入包括不超过 $30$ 组测试数据。每个测试数据只包括一行，包含 $24$ 个整数，每相邻两个整数之间用 $1$ 个空格隔开，表示这个 “#” 形棋盘的初始状态。（这些整数的排列顺序是从上至下，同一行的从左至右。例如 $\text{1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3}$ 表示图 $1$ 最左边的状态。）每两组测试数据之间没有换行符。输入文件以一行 $0$ 结束。

## 输出格式

　　对于每组测试数据，输出两行。第一行用字符 $\text{A}\sim \text{H}$ 输出操作的方法，**每两个操作字符之间没有空格分开**，如果不需要任何步数，输出 `No moves needed`。第二行输出最终状态中最中间的 $8$ 个格子里的数字。如果有多组解，输出操作次数最少的一组解；如果仍有多组解，输出字典序最小的一组。任意相邻两组测试数据的输出之间不需输出换行符。



---

---
title: "Sudoku Extension"
layout: "post"
diff: 提高+/省选-
pid: UVA1461
tag: ['模拟', '搜索', '剪枝']
---

# Sudoku Extension

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4207

[PDF](https://uva.onlinejudge.org/external/14/p1461.pdf)



---

---
title: "Falling Leaves"
layout: "post"
diff: 提高+/省选-
pid: UVA1525
tag: ['字符串', '搜索', '平衡树', '图论建模']
---

# Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4300

[PDF](https://uva.onlinejudge.org/external/15/p1525.pdf)



---

---
title: "理想路径 Ideal Path"
layout: "post"
diff: 提高+/省选-
pid: UVA1599
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 输入格式

输入共$m+1$行：

第一行$2$个空格整数：$n$和$m$。

以后$m$行，每行空格隔开的$3$个整数$a_i,b_i,c_i$，表示在$a_i,b_i$之间有一条颜色为$c_i$的道路。

## 输出格式

输出共两行：

第一行$1$个正整数$k$，表示$1$到$n$至少需要经过$k$条边。

第二行包含$k$个空格隔开的正整数，表示从$1$到$n$依次经过的边的**颜色**。

## 输入输出样例：
### 输入样例：
```
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
```
### 输出样例：
```
2
1 3
```
### 输入输出样例解释：
路径依次如下：

$1\rightarrow3$，颜色为$1$（最后输入的那条）；

$3\rightarrow4$，颜色为$3$。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译



---

---
title: "纸牌游戏 Double Patience"
layout: "post"
diff: 提高+/省选-
pid: UVA1637
tag: ['动态规划 DP', '搜索', '概率论']
---

# 纸牌游戏 Double Patience

## 题目描述

Double  Patience是一种单人游戏，使用标准的36张牌组。这些牌在洗牌后放在一张桌子上，叠成9叠，每叠4张，面朝上。



牌放下后，玩家转身。每一次，他可以从任意两个牌堆中取出同一等级的顶级牌，然后将它们移除。如果有几种可能性，玩家可以选择任何一种。如果所有的牌都从桌上移除，玩家将赢得游戏，如果一些牌仍然在桌上，并且没有有效的移动，玩家将失败。



乔治喜欢这种游戏。但当有几种可能时，他不知道要选择哪一张。乔治不想多想，所以在这种情况下，他只需从可能的情况中选择一对随机的，并删除它。乔治选择每种情况的可能性相同。



例如，如果最上面的牌是Ks、Kh、Kd、9h、8s、8d、7c、7d和6h，他会删除任何一对在(KS, KH)、(KS, KD)、(KH, KD)、 (8S, 8D)和 (7C, 7D)中的任何一对。删除（Ks,Kh）、（Ks,Kd）、（Kh,Kd）、（8s,8d）和（7c,7d）的概率都为1/5。



请算出在游戏开始时，根据桌上的牌，找出如果乔治按照描述行事，他赢得游戏的可能性是多少。

## 输入格式

输入文件包含几个测试用例，每个测试用例由九行组成。每行包含四张牌的描述，它们在游戏开始时形成一堆，从下一张牌到上一张牌。



每张卡片有两个字符：一个用于等级，一个用于花色。等级用“6”表示6，“7”表示7，“8”表示8，“9”表示9，“T”表示10，“J”表示杰克，“Q”表示女王，“K”表示国王，“A”表示王牌。花色用“S”代表黑桃，C代表梅花，D代表钻石，H代表红桃。例如，“KS”表示黑桃王。



每个卡片描述之间用一个空格隔开。

## 输出格式

对于每个测试用例，输出一行实数-如果乔治随机玩游戏，他赢得游戏的概率。您的答案必须精确到小数点后6位

## 样例输入，输出略



---

---
title: "Solitaire"
layout: "post"
diff: 提高+/省选-
pid: UVA1724
tag: ['搜索', '广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# Solitaire

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=859&page=show_problem&problem=4862

[PDF](https://uva.onlinejudge.org/external/17/p1724.pdf)

## 样例 #1

### 输入

```
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



---

---
title: "Optimal Array Multiplication Sequence"
layout: "post"
diff: 提高+/省选-
pid: UVA348
tag: ['搜索', '记忆化搜索']
---

# Optimal Array Multiplication Sequence

## 题目描述

对于三个矩阵$A,B,C$，若$C=AB$，则C的计算方式为$C_{i,j}=\sum_k A_{i,k} \times B_{k,j}$。



可见若要计算两个大小分别为$a \times b$和$b \times c$的矩阵的乘积，需要$a \times b \times c$次计算；

对于两个矩阵$A,B$，不满足$A \times B = B \times A$；对于三个矩阵$A,B,C$，满足$(A \times B) \times C = A \times (B \times C)$。



给定$n$个矩阵$A1,A2, \dots ,An$的行列数，现在要算出这些矩阵的积，问如何安排运算顺序可使运算次数最少。



本题包含多组数据。

## 输入格式

对于每组数据，首先输入一个正整数$n(0 \le n \le 10)$，然后每行输入两个正整数，表示每个矩阵的行数和列数。

## 输出格式

首先输出“$Case\ k:\ $”，其中$k$为当前数据的组别编号。然后输出最优计算顺序，其中乘号用“x”代表，且前后都要输出一个空格。每一次乘法的外面都要套一对小括号。



例如第一组数据的最优解为先计算$A2 \times A3$，再计算$A1 \times (A2 \times A3)$，则要输出“(A1 x (A2 x A3))”。

## 样例 #1

### 输入

```
3
1 5
5 20
20 1
3
5 10
10 20
20 35
6
30 35
35 15
15 5
5 10
10 20
20 25
0
```

### 输出

```
Case 1: (A1 x (A2 x A3))
Case 2: ((A1 x A2) x A3)
Case 3: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))
```



---

---
title: "巴比伦塔 The Tower of Babylon"
layout: "post"
diff: 提高+/省选-
pid: UVA437
tag: ['动态规划 DP', '搜索', '递推', '排序']
---

# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 输入格式

输入会包含至少一组数据，每组数据的第一行是一个整数 $n(n\le30)$，表示方块的种类数。 这组数据接下来的 $n$ 行，每行有三个整数，表示 $xi,yi,zi$。输入数据会以 $0$ 结束。

## 输出格式

对于每组数据，输出一行，其中包含组号（从 $1$ 开始）和塔最高的高度。按以下格式：``Case i: maximum height = __``。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342
```



---

---
title: "Addition Chains"
layout: "post"
diff: 提高+/省选-
pid: UVA529
tag: ['搜索', '枚举', '剪枝', '搜索']
---

# Addition Chains

## 题目描述

一个与 $n$ 有关的整数加成序列 $<a_0,a_1,a_2,...,a_m>$ 满足以下四个条件：  
 $1.a_0=1$   
 $2.a_m=n$   
 $3.a_0<a_1<a_2<...<a_{m-1}<a_m$   
 $4.$ 对于每一个 $k(1≤k≤m)$ 都存在有两个整数 $i$ 和 $j(0≤i,j≤k-1,i$ 和 $j$ 可以相等 $)$ ，使得 $a_k=a_i+a_j$   
你的任务是：给定一个整数 $n$ ,找出符合上述四个条件的长度最小的整数加成序列。如果有多个满足要求的答案，只需要输出任意一个解即可。  
举个例子，序列 $<1,2,3,5>$ 和 $<1,2,4,5>$ 均为 $n=5$ 时的解。

## 输入格式

输入包含多组数据。每组数据仅一行包含一个整数 $n(1≤n≤10000)$ 。在最后一组数据之后是一个 $0$ 。

## 输出格式

对于每组数据，输出一行所求的整数加成序列，每个整数之间以空格隔开。

感谢@Iowa_BattleShip 提供的翻译

## 样例 #1

### 输入

```
5
7
12
15
77
0
```

### 输出

```
1 2 4 5
1 2 4 6 7
1 2 4 8 12
1 2 4 5 10 15
1 2 4 8 9 17 34 68 77
```



---

---
title: "Triangle War"
layout: "post"
diff: 提高+/省选-
pid: UVA751
tag: ['搜索', '状态合并', '博弈树']
---

# Triangle War

## 题目描述

## 题面翻译

给出10个点，共有18条边，每次A,B两个人轮流加入一条边。A先加。

如果形成一个三角形，则三角形归他所有，**而且还必须再走一步**。最后三角形多的人胜。

现在已经给出一部分已经完成的步数，由于两位玩家都是**最聪明的**，他们都会走**为自己带来最大优势**的步数。你需要判断谁会赢得游戏。

## 输入格式

每个测试点包含多组数据。输入的第一行包括一个整数  $t$  ，表示数据组数。

对于每一组数据：
第一行为一个正整数  $m$  ，表示已经完成的步数。 （6 <=  $m$  <= 18)

接下来的  $m$  行描述了按顺序 A , B 两人完成的步数，按照  $i$   $j$  的形式，表示i，j 已经被填上。

## 输出格式

对于每一组测试数据输出一行，先输出游戏的序号 `Game x`: ，如果 A 获胜，输出 `A wins.` ，否则输出 `B wins.` 。

## 输入输出样例
略

感谢@Kato_Megumi  提供的翻译

## 样例 #1

### 输入

```
4
6
2 4
4 5
5 9
3 6
2 5
3 5
7
2 4
4 5
5 9
3 6
2 5
3 5
7 8
6
1 2
2 3
1 3
2 4
2 5
4 5
10
1 2
2 5
3 6
5 8
4 7
6 10
2 4
4 5
4 8
7 8
```

### 输出

```
Game 1: B wins.
Game 2: A wins.
Game 3: A wins.
Game 4: B wins.
```



---

---
title: "Abbott的复仇 Abbott's Revenge"
layout: "post"
diff: 提高+/省选-
pid: UVA816
tag: ['广度优先搜索 BFS', '图论建模', '最短路']
---

# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/4939e773b1884a681cdc9dbd1fe1251df58b072b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/9ff2bb3a862e6ca3e356ecb98a558f994c9d7f5d.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz
```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
```



---



---

# 题号列表

- UVA1043 - Crossing Streets
- UVA10561 - Treblecross
- UVA11324 - The Largest Clique
- UVA124 - Following Orders
- UVA1326 - Jurassic Remains
- UVA1343 - 旋转游戏 The Rotation Game
- UVA1461 - Sudoku Extension
- UVA1525 - Falling Leaves
- UVA1599 - 理想路径 Ideal Path
- UVA1637 - 纸牌游戏 Double Patience
- UVA1724 - Solitaire
- UVA348 - Optimal Array Multiplication Sequence
- UVA437 - 巴比伦塔 The Tower of Babylon
- UVA529 - Addition Chains
- UVA751 - Triangle War
- UVA816 - Abbott的复仇 Abbott's Revenge


---

---
title: "Duathlon"
layout: "post"
diff: 提高+/省选-
pid: UVA10385
tag: ['数学', '枚举', '期望']
---

# Duathlon

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1326

[PDF](https://uva.onlinejudge.org/external/103/p10385.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/945f9e56a0937fda8776dab247e1ddf0a30143a8.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/8608111801d57b83b5e8d0bc4afb09d09224171f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/e62cac0caf13a720d5cb52a53fd1a0ac7809bb47.png)

## 样例 #1

### 输入

```
100
3
10.0 40.0
20.0 30.0
15.0 35.0
100
3
10.0 40.0
20.0 30.0
15.0 25.0
```

### 输出

```
The cheater can win by 612 seconds with r = 14.29km and k = 85.71km.
The cheater cannot win.
```



---

---
title: "Hackers' Crackdown"
layout: "post"
diff: 提高+/省选-
pid: UVA11825
tag: ['数学', '状态合并', '进制']
---

# Hackers' Crackdown

## 题目描述

假如你是一个黑客，侵入了一个有着 $n$ 台计算机（编号为$0,1,2,3....n-1$）的网络。一共有 $n$ 种服务，每台计算机都运行着所有服务。对于每台计算机，你都可以选择一项服务，终止这台计算机和所有与它相邻计算机的该项服务（如果其中一些服务已经停止，那他们继续保持停止状态）。你的目标是让尽量多的服务完全瘫痪(即：没有任何计算及运行着该服务)

## 输入格式

输入包含多组数据，每组数据的第一行为整数 $n(1\leq n\leq 16)$ : 以下 $n$ 行每行描述一台计算机相邻的计算机，其中第一个数 $m$ 为相邻计算机个数，接下来的 $m$ 个整数为这些计算机的编号。输入结束标志 $n=0$。

## 输出格式

对于每组数据，输出完全瘫痪的服务的数量。

## 样例 #1

### 输入

```
3
2 1 2
2 0 2
2 0 1
4
1 1
1 0
1 3
1 2
0
```

### 输出

```
Case 1: 3
Case 2: 2
```



---

---
title: "K Smallest Sums"
layout: "post"
diff: 提高+/省选-
pid: UVA11997
tag: ['数学', '最短路', '队列']
---

# K Smallest Sums

## 题目描述

有一个 $k \times k$ 的矩阵，在每行任取一个位置，把这些位置的元素相加的到一个值，求前 $k$ 小的值。

## 输入格式

多组数据。

每组第一行是整数 $k$。

第 $2$ 到 $k+1$ 行中的第 $i+1$ 行有 $k$ 个整数，第 $j$ 个表示 $a_{i,j}$。

## 输出格式

每行 $k$ 个整数，表示答案。

## 说明/提示

对于 $100\%$ 的数据，$2 \leq k \leq 750$。

## 样例 #1

### 输入

```
3
1 8 5
9 2 5
10 7 6
2
1 1
1 2
```

### 输出

```
9 10 12
2 2
```



---

---
title: "Garland"
layout: "post"
diff: 提高+/省选-
pid: UVA1555
tag: ['数学', '枚举']
---

# Garland

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4330

[PDF](https://uva.onlinejudge.org/external/15/p1555.pdf)



---

---
title: "勤劳的蜜蜂 Bee Breeding"
layout: "post"
diff: 提高+/省选-
pid: UVA808
tag: ['数学', '递推']
---

# 勤劳的蜜蜂 Bee Breeding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=749

[PDF](https://uva.onlinejudge.org/external/8/p808.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/9bab4a64afdd472dc2664e3eff03743e904c3d4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/ece86ec0d7a73280a4d4325cfcfeda323b9b3cd5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/0f05e34c6915f5c4d3fc623283f0f02d6594ce4c.png)

## 样例 #1

### 输入

```
19 30
0 0
```

### 输出

```
The distance between cells 19 and 30 is 5.
```



---



---

# 题号列表

- UVA10385 - Duathlon
- UVA11825 - Hackers' Crackdown
- UVA11997 - K Smallest Sums
- UVA1555 - Garland
- UVA808 - 勤劳的蜜蜂 Bee Breeding


---

---
title: "Airport Express"
layout: "post"
diff: 提高+/省选-
pid: UVA11374
tag: ['枚举', '最短路']
---

# Airport Express

## 题目描述

在$Iokh$市中，机场快线是市民从市内去机场的首选交通工具。机场快线分为经济线和商业线两种，线路、速度和价钱都不同。你有一张商业线车票，可以坐一站商业线，而其他时候只能乘坐经济线。假设换乘时间忽略不计，你的任务是找一条去机场最快的线路。

## 输入格式

输入包含多组数据。每组数据第一行为$3$个整数$N, S$和$E(2 \leq N \leq 500, 1 \leq S, E \leq 100)$，即机场快线中的车站总数，起点和终点（即机场所在站）编号。下一行包含一个整数$M(1 \leq M \leq 1000)$，即经济线的路段条数。以下$M$行每行3个整数$X, Y, Z(1 \leq X, Y \leq N, 1 \leq Z \leq 100)$，表示可以乘坐经济线在车站$X$和车站$Y$之间往返，其中单程需要$Z$分钟。下一行为商业线的路段条数$K(1 \leq K \leq 1000)$，以下$K$行是这些路段的描述，格式同经济线。所有路段都是双向的，但有可能必须使用商业车票才能到达机场。保证最优解唯一。

## 输出格式

对于每组数据，输出$3$行。第一行按访问顺序给出经过的各个车站（包括起点和终点），第二行是换乘商业线的车站编号（如果没有商业线车票，输出`Ticket Not Used`），第三行是总时间。

**注意**：输出时，每两组数据之间要加一个空行。并且不会过滤行末空格。

Translated by @andyli

## 样例 #1

### 输入

```
4 1 4
4
1 2 2
1 3 3
2 4 4
3 4 5
1
2 4 3
```

### 输出

```
1 2 4
2
5
```



---

---
title: "K Smallest Sums"
layout: "post"
diff: 提高+/省选-
pid: UVA11997
tag: ['数学', '最短路', '队列']
---

# K Smallest Sums

## 题目描述

有一个 $k \times k$ 的矩阵，在每行任取一个位置，把这些位置的元素相加的到一个值，求前 $k$ 小的值。

## 输入格式

多组数据。

每组第一行是整数 $k$。

第 $2$ 到 $k+1$ 行中的第 $i+1$ 行有 $k$ 个整数，第 $j$ 个表示 $a_{i,j}$。

## 输出格式

每行 $k$ 个整数，表示答案。

## 说明/提示

对于 $100\%$ 的数据，$2 \leq k \leq 750$。

## 样例 #1

### 输入

```
3
1 8 5
9 2 5
10 7 6
2
1 1
1 2
```

### 输出

```
9 10 12
2 2
```



---

---
title: "理想路径 Ideal Path"
layout: "post"
diff: 提高+/省选-
pid: UVA1599
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 输入格式

输入共$m+1$行：

第一行$2$个空格整数：$n$和$m$。

以后$m$行，每行空格隔开的$3$个整数$a_i,b_i,c_i$，表示在$a_i,b_i$之间有一条颜色为$c_i$的道路。

## 输出格式

输出共两行：

第一行$1$个正整数$k$，表示$1$到$n$至少需要经过$k$条边。

第二行包含$k$个空格隔开的正整数，表示从$1$到$n$依次经过的边的**颜色**。

## 输入输出样例：
### 输入样例：
```
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
```
### 输出样例：
```
2
1 3
```
### 输入输出样例解释：
路径依次如下：

$1\rightarrow3$，颜色为$1$（最后输入的那条）；

$3\rightarrow4$，颜色为$3$。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译



---

---
title: "Abbott的复仇 Abbott's Revenge"
layout: "post"
diff: 提高+/省选-
pid: UVA816
tag: ['广度优先搜索 BFS', '图论建模', '最短路']
---

# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/4939e773b1884a681cdc9dbd1fe1251df58b072b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/9ff2bb3a862e6ca3e356ecb98a558f994c9d7f5d.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz
```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
```



---



---

# 题号列表

- UVA11374 - Airport Express
- UVA11997 - K Smallest Sums
- UVA1599 - 理想路径 Ideal Path
- UVA816 - Abbott的复仇 Abbott's Revenge


---

---
title: "The Last Non-zero Digit."
layout: "post"
diff: 提高+/省选-
pid: UVA10212
tag: ['枚举', '概率论', '构造']
---

# The Last Non-zero Digit.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1153

[PDF](https://uva.onlinejudge.org/external/102/p10212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/4e8f810bc4e7a305f60b05b1e511704f8aa33548.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/0894c564af5b074b1fa71eba4f22eddd87c8094a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/f87ef3743b89683c4cc1e3cc87091658d956339f.png)

## 样例 #1

### 输入

```
10 10
10 5
25 6
```

### 输出

```
8
4
2
```



---

---
title: "古代象形符号 Ancient Messages"
layout: "post"
diff: 提高+/省选-
pid: UVA1103
tag: ['连通块', '进制', '构造']
---

# 古代象形符号 Ancient Messages

## 题目描述

为了理解早期文明，考古学家经常研究用古代语言编写的文本。在3000多年前的埃及使用的一种语言是基于称为象形文字的字符。如图显示了六个象形文字及其名称，在这个题目中，您需要编写一个程序来识别这六个字。

![]("C:\Users\白文礼\Desktop\4_1.png")

输入INPUT：
```

## 输入格式

输入由几个测试用例组成，每个测试用例描述一个包含一个或多个的图像。 象形文字选自图所示的那些。图像以一系列水平扫描线的形式给出，这些水平扫描线由黑色像素（由1表示）和白色像素（由0表示）组成。在输入数据中，每个扫描线以十六进制表示法编码。 例如，序列将表示八个像素10011100（一个黑色像素，后面是两个白色像素，依此类推） 十六进制表示法为9c。 在十六进制中仅使用数字和小写字母a到f编码。每个测试用例的第一行包含两个整数，H和W。H（0＜H≤200）是 图像中的扫描行数。 W（0＜W≤50）是每行中十六进制字符的数量 。 接下来的H行包含图像的十六进制字符，从上到下。
输入图像符合以下规则：
图像仅包含图1中所示的象形文字。
每个图像至少包含一个有效的象形文字。
图像中的每个黑色像素都是有效象形文字的一部分。
每个象形文字由一组连邻的黑色像素组成，即每个黑色像素至少和一个位于其顶部，底部，左侧或右侧的其他黑色像素相临。
象形文字间不相连，一个象形文字中不包含其他象形文字。
对角线顶点接触的两个黑色像素必然具有共同的相邻的黑色像素。
象形文字可能会扭曲，但其在拓扑结构上一定等同于图1中的一个符号。 （两个图形的拓扑结构等同是说一个图形通过扭曲拖拽可以成为另一个图形，但是不能撕裂。） 
在输入所有测试用例之后换行并输入两个零，表示结束。

输入样例
100 25 
0000000000000000000000000 
0000000000000000000000000 
...(50 lines omitted)... 
00001fe0000000000007c0000 
00003fe0000000000007c0000 
...(44 lines omitted)... 
0000000000000000000000000 
0000000000000000000000000
150 38 
00000000000000000000000000000000000000
00000000000000000000000000000000000000 
...(75 lines omitted)... 
0000000003fffffffffffffffff00000000000 
0000000003fffffffffffffffff00000000000 
...(69 lines omitted)... 
00000000000000000000000000000000000000
00000000000000000000000000000000000000 
0 0
```

输出OUTPUT：

```

## 输出格式

对于每个测试用例，输出其测试用例编号，后跟一个字符串，字符串包含的每一个字符都代表一个图像中的象形文字，具体对应关系如下：
Ankh：A
Wedjat：J
Djed：D 
Scarab：S
Was：W
Akhet：K

输出样例
Case 1: AKW
Case 2: AAAAA
```



---

---
title: "生成排列 Generating Permutations"
layout: "post"
diff: 提高+/省选-
pid: UVA11925
tag: ['字符串', '构造']
---

# 生成排列 Generating Permutations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3076

[PDF](https://uva.onlinejudge.org/external/119/p11925.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/4ae01d3bad0e00d10dd54ea1a36732d8994153c9.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/39a915f8fa7c330f6d88d2084592f1cdbcc50f29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/b09493d267f3d2d325027cbace89abb524055c4a.png)

## 样例 #1

### 输入

```
3 2 1 3
3 2 3 1
4 4 2 3 1
0
```

### 输出

```
1
2
12122
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
title: "旋转游戏 The Rotation Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1343
tag: ['剪枝', '启发式迭代加深搜索 IDA*', '构造']
---

# 旋转游戏 The Rotation Game

## 题目描述

　　如图 $1$ 所示，有一个 “#” 形的棋盘，上面有 $1,2,3$ 三种数字各 $8$ 个。给定 $8$ 种操作，分别为图中的 $\text{A}\sim \text{H}$。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 $8$ 的序列循环移动 $1$ 个单位。例如下图最左边的 “#” 形棋盘执行操作 $\text{A}$ 时，会变为图中间的 “#” 形棋盘，再执行操作 $\text{C}$ 后会变为图中最右边的 “#” 形棋盘。
![](https://cdn.luogu.org/upload/pic/40731.png)
$$\text{图 1}$$
　　现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 $8$ 个格子里的数字相同。

## 输入格式

　　输入包括不超过 $30$ 组测试数据。每个测试数据只包括一行，包含 $24$ 个整数，每相邻两个整数之间用 $1$ 个空格隔开，表示这个 “#” 形棋盘的初始状态。（这些整数的排列顺序是从上至下，同一行的从左至右。例如 $\text{1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3}$ 表示图 $1$ 最左边的状态。）每两组测试数据之间没有换行符。输入文件以一行 $0$ 结束。

## 输出格式

　　对于每组测试数据，输出两行。第一行用字符 $\text{A}\sim \text{H}$ 输出操作的方法，**每两个操作字符之间没有空格分开**，如果不需要任何步数，输出 `No moves needed`。第二行输出最终状态中最中间的 $8$ 个格子里的数字。如果有多组解，输出操作次数最少的一组解；如果仍有多组解，输出字典序最小的一组。任意相邻两组测试数据的输出之间不需输出换行符。



---



---

# 题号列表

- UVA10212 - The Last Non-zero Digit.
- UVA1103 - 古代象形符号 Ancient Messages
- UVA11925 - 生成排列 Generating Permutations
- UVA11992 - Fast Matrix Operations
- UVA1343 - 旋转游戏 The Rotation Game


---

---
title: "Sumsets"
layout: "post"
diff: 提高+/省选-
pid: UVA10125
tag: ['二分', '枚举', '排序']
---

# Sumsets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1066

[PDF](https://uva.onlinejudge.org/external/101/p10125.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/29d92f1d32bdaefa1d311d7a2aa7e97895e4a322.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/ce194eb546afa406872932e0bd6f9dd4ca894f2d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10125/bf773b60567946315edebe60d7e76099b6dc0d8e.png)

## 样例 #1

### 输入

```
5
2
3
5
7
12
5
2
16
64
256
1024
0
```

### 输出

```
12
no solution
```



---

---
title: "The Last Non-zero Digit."
layout: "post"
diff: 提高+/省选-
pid: UVA10212
tag: ['枚举', '概率论', '构造']
---

# The Last Non-zero Digit.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1153

[PDF](https://uva.onlinejudge.org/external/102/p10212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/4e8f810bc4e7a305f60b05b1e511704f8aa33548.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/0894c564af5b074b1fa71eba4f22eddd87c8094a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/f87ef3743b89683c4cc1e3cc87091658d956339f.png)

## 样例 #1

### 输入

```
10 10
10 5
25 6
```

### 输出

```
8
4
2
```



---

---
title: "城市里的间谍 A Spy in the Metro"
layout: "post"
diff: 提高+/省选-
pid: UVA1025
tag: ['动态规划 DP', '枚举']
---

# 城市里的间谍 A Spy in the Metro

## 题目描述

#### 题目大意

某城市地铁是一条直线，有 $n$（$2\leq	 n\leq	 50$）个车站，从左到右编号 $1\ldots n$。有 $M_1$ 辆列车从第 $1$ 站开始往右开，还有 $M_2$ 辆列车从第 $n$ 站开始往左开。列车在相邻站台间所需的运行时间是固定的，因为所有列车的运行速度是相同的。在时刻 $0$，Mario 从第 $1$ 站出发，目的在时刻 $T$（$0\leq T\leq 200$）会见车站 $n$ 的一个间谍。在车站等车时容易被抓，所以她决定尽量躲在开动的火车上，让在车站等待的时间尽量短。列车靠站停车时间忽略不计，且 Mario 身手敏捷，即使两辆方向不同的列车在同一时间靠站，Mario 也能完成换乘。

## 输入格式

输入文件包含多组数据。

每一组数据包含以下 $7$ 行：

第一行是一个正整数 $n$，表示有 $n$ 个车站。

第二行是为 $T$，表示 Mario 在时刻 $T$ 会见车站 $n$ 的间谍。

第三行有 $n-1$ 个整数 $t_1,t_2,\ldots,t_{n-1}$，其中 $t_i$ 表示地铁从车站 $i$ 到 $i+1$ 的行驶时间。


第四行为 $M_1$，及从第一站出发向右开的列车数目。

第五行包含 $M_1$ 个正整数 $a_1,a_2,\ldots,a_{M_1}$，即每个列车出发的时间。

第六行为 $M_2$ ，即从第 $n$ 站出发向左开的列车数目。

第七行包含 $M_2$ 个正整数 $b_1,b_2,\ldots,b_{M_2}$，即每个列车出发的时间。

输入文件以一行 $0$ 结尾。

## 输出格式

有若干行，每行先输出 ```Case Number XXX : ```（XXX为情况编号，从 $1$ 开始），再输出最少等待时间或 ```impossible```（无解）。

## 样例 #1

### 输入

```
4
55
5 10 15
4
0 5 10 20
4
0 5 10 15
4
18
1 2 3
5
0 3 6 10 12
6
0 3 5 7 12 15
2
30
20
1
20
7
1 3 5 7 11 13 17
0

```

### 输出

```
Case Number 1: 5
Case Number 2: 0
Case Number 3: impossible

```



---

---
title: "Duathlon"
layout: "post"
diff: 提高+/省选-
pid: UVA10385
tag: ['数学', '枚举', '期望']
---

# Duathlon

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1326

[PDF](https://uva.onlinejudge.org/external/103/p10385.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/945f9e56a0937fda8776dab247e1ddf0a30143a8.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/8608111801d57b83b5e8d0bc4afb09d09224171f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10385/e62cac0caf13a720d5cb52a53fd1a0ac7809bb47.png)

## 样例 #1

### 输入

```
100
3
10.0 40.0
20.0 30.0
15.0 35.0
100
3
10.0 40.0
20.0 30.0
15.0 25.0
```

### 输出

```
The cheater can win by 612 seconds with r = 14.29km and k = 85.71km.
The cheater cannot win.
```



---

---
title: "最小公倍数的最小和 Minimum Sum LCM"
layout: "post"
diff: 提高+/省选-
pid: UVA10791
tag: ['递归', '枚举', '素数判断,质数,筛法']
---

# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/7a5e01d2fc4bd5a007ecd456a07165372a1da9fa.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/eb4e5ec11ec7e64f907d2a65a0fcc8faf715a7db.png)

## 样例 #1

### 输入

```
12
10
5
0
```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6
```



---

---
title: "Nuts for nuts.."
layout: "post"
diff: 提高+/省选-
pid: UVA10944
tag: ['枚举', '进制']
---

# Nuts for nuts..

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1885

[PDF](https://uva.onlinejudge.org/external/109/p10944.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/eab44d58cb45ad772b3f67192aa37528e61e5fe1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/a1c24b72a850b0c3c74a01bb376efca80cd04044.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/aa27c38474cbf5db18725d954fc07f00ee41663b.png)

## 样例 #1

### 输入

```
5 5
L....
#....
#....
.....
#....
5 5
L....
#....
#....
.....
#....
```

### 输出

```
8
8
```



---

---
title: "H-半素数 Semi-prime H-numbers"
layout: "post"
diff: 提高+/省选-
pid: UVA11105
tag: ['枚举', '素数判断,质数,筛法', '中国剩余定理 CRT']
---

# H-半素数 Semi-prime H-numbers

## 题目描述

# 【问题描述】

形如$4n+1$的数被称为“H数”，乘法在“H数”组成的集合内是封闭的。在这个集合中只能被1和本身整除的数叫做“H-素数”（不包括1），其余的数被称为“H-合数”。一个“H-合成数”是一个能且只能分解成两个“H-素数”乘积的“H-合数”（可能有多种分解方案）。比如$441=21*21=9*49$,所以$441$是“H-合成数”。$125=5*5*5$,所以125不是“H-合成数”。

求$0$~$h$范围内“H-合成数”的个数。

## 输入格式

输入若干行，每行一个小于等于$1000001$的整数$h$，一个$0$表示结束。

## 输出格式

对于每一行输入，输出两个数，第一个表示当前的$h$，第二个表示答案。

## 样例 #1

### 输入

```
21
85
789
0
```

### 输出

```
21 0
85 5
789 62
```



---

---
title: "Airport Express"
layout: "post"
diff: 提高+/省选-
pid: UVA11374
tag: ['枚举', '最短路']
---

# Airport Express

## 题目描述

在$Iokh$市中，机场快线是市民从市内去机场的首选交通工具。机场快线分为经济线和商业线两种，线路、速度和价钱都不同。你有一张商业线车票，可以坐一站商业线，而其他时候只能乘坐经济线。假设换乘时间忽略不计，你的任务是找一条去机场最快的线路。

## 输入格式

输入包含多组数据。每组数据第一行为$3$个整数$N, S$和$E(2 \leq N \leq 500, 1 \leq S, E \leq 100)$，即机场快线中的车站总数，起点和终点（即机场所在站）编号。下一行包含一个整数$M(1 \leq M \leq 1000)$，即经济线的路段条数。以下$M$行每行3个整数$X, Y, Z(1 \leq X, Y \leq N, 1 \leq Z \leq 100)$，表示可以乘坐经济线在车站$X$和车站$Y$之间往返，其中单程需要$Z$分钟。下一行为商业线的路段条数$K(1 \leq K \leq 1000)$，以下$K$行是这些路段的描述，格式同经济线。所有路段都是双向的，但有可能必须使用商业车票才能到达机场。保证最优解唯一。

## 输出格式

对于每组数据，输出$3$行。第一行按访问顺序给出经过的各个车站（包括起点和终点），第二行是换乘商业线的车站编号（如果没有商业线车票，输出`Ticket Not Used`），第三行是总时间。

**注意**：输出时，每两组数据之间要加一个空行。并且不会过滤行末空格。

Translated by @andyli

## 样例 #1

### 输入

```
4 1 4
4
1 2 2
1 3 3
2 4 4
3 4 5
1
2 4 3
```

### 输出

```
1 2 4
2
5
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
title: "拿行李（极限版） GCD - Extreme (II)"
layout: "post"
diff: 提高+/省选-
pid: UVA11426
tag: ['枚举', '最大公约数 gcd']
---

# 拿行李（极限版） GCD - Extreme (II)

## 题目描述

得定 $n$，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 4\times 10^6+1$。

## 样例 #1

### 输入

```
10
100
200000
0
```

### 输出

```
67
13015
143295493160
```



---

---
title: "Even Parity"
layout: "post"
diff: 提高+/省选-
pid: UVA11464
tag: ['递推', '枚举', '进制', '概率论']
---

# Even Parity

## 题目描述

给你一个 $n \times n$ 的 $01$ 矩阵（每个元素非 $0$ 即 $1$），你的任务是把尽量少的 $0$ 变成 $1$，使得原矩阵便为偶数矩阵（矩阵中每个元素的上、下、左、右的元素（如果存在的话）之和均为偶数）。

## 输入格式

输入的第一行为数据组数 $T$（$T \le 30$）。每组数据：第一行为正整数 $n$（$1 \le n \le 15$）；接下来的 $n$ 行每行包含 $n$ 个非 $0$ 即 $1$ 的整数，相邻整数间用一个空格隔开。

## 输出格式

对于每组数据，输出被改变的元素的最小个数。如果无解，输出 $-1$。

## 样例 #1

### 输入

```
3
3
0 0 0
0 0 0
0 0 0
3
0 0 0
1 0 0
0 0 0
3
1 1 1
1 1 1
0 0 0
```

### 输出

```
Case 1: 0
Case 2: 3
Case 3: -1
```



---

---
title: "Determine the Shape"
layout: "post"
diff: 提高+/省选-
pid: UVA11800
tag: ['计算几何', '枚举']
---

# Determine the Shape

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2900

[PDF](https://uva.onlinejudge.org/external/118/p11800.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11800/a432d36e486b05289dc5e158f596f11b15abc707.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11800/275f97e3f03222dd0db7ad500dbb1f7e159be822.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11800/2473f64d4c076d0d9495d2530cec78b2dc2c1dee.png)

## 样例 #1

### 输入

```
6
0 0
2 0
2 2
0 2
0 0
3 0
3 2
0 2
0 0
8 4
5 0
3 4
0 0
2 0
3 2
1 2
0 0
5 0
4 3
1 3
0 0
5 0
4 3
1 4
```

### 输出

```
Case 1: Square
Case 2: Rectangle
Case 3: Rhombus
Case 4: Parallelogram
Case 5: Trapezium
Case 6: Ordinary Quadrilateral
```



---

---
title: "完美的服务 Perfect Service"
layout: "post"
diff: 提高+/省选-
pid: UVA1218
tag: ['动态规划 DP', '递归', '枚举']
---

# 完美的服务 Perfect Service

## 题目描述

一个网络中有 $N$ 个节点，由 $N-1$ 条边连通，每个节点是服务器或者客户端。如果节点 $u$ 是客户端，就意味着 $u$ 所连接的所有点中有且仅有一台服务器。求最少要多少台服务器才能满足要求。

## 输入格式

输入包含多组测试数据。对于每组数据，第一行是一个整数 $N(\le10000)$。

接下来 $N-1$ 行，每行两个整数 $a_i,b_i$，表示 $a_i,b_i$ 有一条双向连通的边。

除最后一组输入以外，每组数据以 $0$ 结尾，最后一组数据以 $-1$ 结尾。

## 输出格式

对于每组输入，仅输出一行，表示所需要的最小服务器台数。

翻译贡献者：An_Account.



---

---
title: "Jurassic Remains"
layout: "post"
diff: 提高+/省选-
pid: UVA1326
tag: ['字符串', '搜索', '枚举']
---

# Jurassic Remains

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4072

[PDF](https://uva.onlinejudge.org/external/13/p1326.pdf)



---

---
title: "Garland"
layout: "post"
diff: 提高+/省选-
pid: UVA1555
tag: ['数学', '枚举']
---

# Garland

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4330

[PDF](https://uva.onlinejudge.org/external/15/p1555.pdf)



---

---
title: "感觉不错 Feel Good"
layout: "post"
diff: 提高+/省选-
pid: UVA1619
tag: ['枚举', '栈']
---

# 感觉不错 Feel Good

## 题目背景

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4494

[PDF](https://uva.onlinejudge.org/external/16/p1619.pdf)

## 题目描述

给出正整数 $n$ 和一个长度为 $n$ 的数列 $a$，要求找出一个子区间 $[l,r]$，使这个子区间的数字和乘上子区间中的最小值最大。

形式化的，要求找出 $[l,r]$ 使得：
$$
\left(\sum \limits_{i=l}^{r}a_i\right)\times\min\limits_{i=l}^{r}a_i
$$
最大。输出这个最大值与区间的两个端点。

在答案相等的情况下最小化区间长度，最小化长度的情况下最小化左端点序号。


## 输入格式

本题有多组数据。

每组数据的第一行是一个整数 $n$；
第二行是 $n$ 个非负整数 $a_i$。

两组数据之间用一个空行隔开。

## 输出格式

对于每组数据，第一行输出最大值，第二行输出区间左、右端点。

两组数据间用 **一个空行** 隔开。

**本题不忽略文末回车。**

## 说明/提示

$1 \leq n \leq 10^5, 0 \leq a_i \leq 10^6$。

## 样例 #1

### 输入

```
6
3 1 6 4 5 2
```

### 输出

```
60
3 5
```



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

---
title: "Intersecting Lines"
layout: "post"
diff: 提高+/省选-
pid: UVA378
tag: ['枚举', '向量', '叉积']
---

# Intersecting Lines

## 题目描述

以$(x_1,y_1),(x_2,y_2),(x_3,y_3),(x_4,y_4)$的形式给出两条直线，问过$(x_1,y_1),(x_2,y_2)$的直线和过$(x_3,y_3),(x_4,y_4)$的直线的位置关系。其中$(x_1,y_1)\ne(x_2,y_2),(x_3,y_3)\ne(x_4,y_4)$。

## 输入格式

第一行为数据组数$N$，接下来$N$行，每行$8$个整数，分别依次代表上述$4$个点的坐标。$-1000\le x,y\le 1000$。

## 输出格式

输出共$N+2$行。在第一行输出$\tt INTERSECTING\ LINES\ OUTPUT$，对于第$i+1$行，输出第$i$组数据的答案。

* 如果两直线相交，输出$\mathtt{POINT}\ x\ y$，其中$(x,y)$是交点坐标，保留$2$位小数。
* 如果两直线重合，输出$\tt LINE$。
* 如果两直线平行且不重合，输出$\tt NONE$。

在第$N+2$行输出一行$\tt END\ OF\ OUTPUT$。（详见样例）

## 样例 #1

### 输入

```
5
0 0 4 4 0 4 4 0
5 0 7 6 1 0 2 3
5 0 7 6 3 -6 4 -3
2 0 2 27 1 5 18 5
0 3 4 0 1 2 2 5
```

### 输出

```
INTERSECTING LINES OUTPUT
POINT 2.00 2.00
NONE
LINE
POINT 2.00 5.00
POINT 1.07 2.20
END OF OUTPUT
```



---

---
title: "Addition Chains"
layout: "post"
diff: 提高+/省选-
pid: UVA529
tag: ['搜索', '枚举', '剪枝', '搜索']
---

# Addition Chains

## 题目描述

一个与 $n$ 有关的整数加成序列 $<a_0,a_1,a_2,...,a_m>$ 满足以下四个条件：  
 $1.a_0=1$   
 $2.a_m=n$   
 $3.a_0<a_1<a_2<...<a_{m-1}<a_m$   
 $4.$ 对于每一个 $k(1≤k≤m)$ 都存在有两个整数 $i$ 和 $j(0≤i,j≤k-1,i$ 和 $j$ 可以相等 $)$ ，使得 $a_k=a_i+a_j$   
你的任务是：给定一个整数 $n$ ,找出符合上述四个条件的长度最小的整数加成序列。如果有多个满足要求的答案，只需要输出任意一个解即可。  
举个例子，序列 $<1,2,3,5>$ 和 $<1,2,4,5>$ 均为 $n=5$ 时的解。

## 输入格式

输入包含多组数据。每组数据仅一行包含一个整数 $n(1≤n≤10000)$ 。在最后一组数据之后是一个 $0$ 。

## 输出格式

对于每组数据，输出一行所求的整数加成序列，每个整数之间以空格隔开。

感谢@Iowa_BattleShip 提供的翻译

## 样例 #1

### 输入

```
5
7
12
15
77
0
```

### 输出

```
1 2 4 5
1 2 4 6 7
1 2 4 8 12
1 2 4 5 10 15
1 2 4 8 9 17 34 68 77
```



---

---
title: "Biorhythms"
layout: "post"
diff: 提高+/省选-
pid: UVA756
tag: ['枚举', '中国剩余定理 CRT']
---

# Biorhythms

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=697

[PDF](https://uva.onlinejudge.org/external/7/p756.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA756/329b737b4282ecf0453655ef99a6ed722e0b36b8.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA756/81cd6f8d5dfe0c72bece093ba441fb7e6c18241c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA756/a5871e0729ee76f328863bd6062e300eea9930c1.png)

## 样例 #1

### 输入

```
0 0 0 0
0 0 0 100
5 20 34 325
4 5 6 7
283 102 23 320
203 301 203 40
-1 -1 -1 -1
```

### 输出

```
Case 1: the next triple peak occurs in 21252 days.
Case 2: the next triple peak occurs in 21152 days.
Case 3: the next triple peak occurs in 19575 days.
Case 4: the next triple peak occurs in 16994 days.
Case 5: the next triple peak occurs in 8910 days.
Case 6: the next triple peak occurs in 10789 days.
```



---



---

# 题号列表

- UVA10125 - Sumsets
- UVA10212 - The Last Non-zero Digit.
- UVA1025 - 城市里的间谍 A Spy in the Metro
- UVA10385 - Duathlon
- UVA10791 - 最小公倍数的最小和 Minimum Sum LCM
- UVA10944 - Nuts for nuts..
- UVA11105 - H-半素数 Semi-prime H-numbers
- UVA11374 - Airport Express
- UVA11400 - 照明系统设计 Lighting System Design
- UVA11424 - GCD - Extreme (I)
- UVA11426 - 拿行李（极限版） GCD - Extreme (II)
- UVA11464 - Even Parity
- UVA11800 - Determine the Shape
- UVA1218 - 完美的服务 Perfect Service
- UVA1326 - Jurassic Remains
- UVA1555 - Garland
- UVA1619 - 感觉不错 Feel Good
- UVA1629 - 切蛋糕 Cake slicing
- UVA378 - Intersecting Lines
- UVA529 - Addition Chains
- UVA756 - Biorhythms


---

---
title: "感觉不错 Feel Good"
layout: "post"
diff: 提高+/省选-
pid: UVA1619
tag: ['枚举', '栈']
---

# 感觉不错 Feel Good

## 题目背景

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4494

[PDF](https://uva.onlinejudge.org/external/16/p1619.pdf)

## 题目描述

给出正整数 $n$ 和一个长度为 $n$ 的数列 $a$，要求找出一个子区间 $[l,r]$，使这个子区间的数字和乘上子区间中的最小值最大。

形式化的，要求找出 $[l,r]$ 使得：
$$
\left(\sum \limits_{i=l}^{r}a_i\right)\times\min\limits_{i=l}^{r}a_i
$$
最大。输出这个最大值与区间的两个端点。

在答案相等的情况下最小化区间长度，最小化长度的情况下最小化左端点序号。


## 输入格式

本题有多组数据。

每组数据的第一行是一个整数 $n$；
第二行是 $n$ 个非负整数 $a_i$。

两组数据之间用一个空行隔开。

## 输出格式

对于每组数据，第一行输出最大值，第二行输出区间左、右端点。

两组数据间用 **一个空行** 隔开。

**本题不忽略文末回车。**

## 说明/提示

$1 \leq n \leq 10^5, 0 \leq a_i \leq 10^6$。

## 样例 #1

### 输入

```
6
3 1 6 4 5 2
```

### 输出

```
60
3 5
```



---



---

# 题号列表

- UVA1619 - 感觉不错 Feel Good


---

---
title: "Movie collection"
layout: "post"
diff: 提高+/省选-
pid: UVA1513
tag: ['树状数组']
---

# Movie collection

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4259

[PDF](https://uva.onlinejudge.org/external/15/p1513.pdf)



---



---

# 题号列表

- UVA1513 - Movie collection


---

---
title: "The Last Non-zero Digit."
layout: "post"
diff: 提高+/省选-
pid: UVA10212
tag: ['枚举', '概率论', '构造']
---

# The Last Non-zero Digit.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1153

[PDF](https://uva.onlinejudge.org/external/102/p10212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/4e8f810bc4e7a305f60b05b1e511704f8aa33548.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/0894c564af5b074b1fa71eba4f22eddd87c8094a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/f87ef3743b89683c4cc1e3cc87091658d956339f.png)

## 样例 #1

### 输入

```
10 10
10 5
25 6
```

### 输出

```
8
4
2
```



---

---
title: "Even Parity"
layout: "post"
diff: 提高+/省选-
pid: UVA11464
tag: ['递推', '枚举', '进制', '概率论']
---

# Even Parity

## 题目描述

给你一个 $n \times n$ 的 $01$ 矩阵（每个元素非 $0$ 即 $1$），你的任务是把尽量少的 $0$ 变成 $1$，使得原矩阵便为偶数矩阵（矩阵中每个元素的上、下、左、右的元素（如果存在的话）之和均为偶数）。

## 输入格式

输入的第一行为数据组数 $T$（$T \le 30$）。每组数据：第一行为正整数 $n$（$1 \le n \le 15$）；接下来的 $n$ 行每行包含 $n$ 个非 $0$ 即 $1$ 的整数，相邻整数间用一个空格隔开。

## 输出格式

对于每组数据，输出被改变的元素的最小个数。如果无解，输出 $-1$。

## 样例 #1

### 输入

```
3
3
0 0 0
0 0 0
0 0 0
3
0 0 0
1 0 0
0 0 0
3
1 1 1
1 1 1
0 0 0
```

### 输出

```
Case 1: 0
Case 2: 3
Case 3: -1
```



---

---
title: "Cheerleaders"
layout: "post"
diff: 提高+/省选-
pid: UVA11806
tag: ['状态合并', '容斥原理', '概率论']
---

# Cheerleaders

## 题目描述

你有一个 $n\times m$ 的网格图，现在你要将 $k$ 个人放在网格中，满足以下条件：
- 网格图的四个边都至少有一个人；
- 每个格子上不能有两个人；
- 每个人必须都有位置。

求放的方案数，答案对 $10^6+7$ 取模。

注意：四个角的人可以同时算作在两个边上。

## 输入格式

第一行一个整数 $T$ 表示数据组数。

对于每组数据：一行三个整数 $n,m,k$，如题意所示。

## 输出格式

每组数据一行一个整数。见样例。

## 说明/提示

数据范围：$T\le 50,2\le n,m\le 20,k\le 500$。

## 样例 #1

### 输入

```
2
2 2 1
2 3 2
```

### 输出

```
Case 1: 0
Case 2: 2
```



---

---
title: "Wall"
layout: "post"
diff: 提高+/省选-
pid: UVA1303
tag: ['排序', '概率论', '凸包']
---

# Wall

## 题目描述

给定一些点，求出最短的包围所有点的轮廓且满足任意点到轮廓的距离不小于给定的$L$。

## 输入格式

第一行一个正整数$T$，代表数据组数。



接下来$T$组数据，对于每组数据，第一行为两个整数$n,L,(3\le n\le 1000,1\le L\le 1000)$，分别代表点的个数和点距离轮廓的最小距离。接下来$n$行，每行两个整数$X_i,Y_i(-10000\le X_i,Y_i\le 10000)$，表示点的坐标。

## 输出格式

输出共$2T$行，对于每组数据，**四舍五入至整数位**输出答案，并空一行。同时，最后一组数据后仅有一个空行。



例如：这是当$T=2$时，两组数据均为样例的答案，`----`表空行。

```

1628

----

1628

----

```



---

---
title: "纸牌游戏 Double Patience"
layout: "post"
diff: 提高+/省选-
pid: UVA1637
tag: ['动态规划 DP', '搜索', '概率论']
---

# 纸牌游戏 Double Patience

## 题目描述

Double  Patience是一种单人游戏，使用标准的36张牌组。这些牌在洗牌后放在一张桌子上，叠成9叠，每叠4张，面朝上。



牌放下后，玩家转身。每一次，他可以从任意两个牌堆中取出同一等级的顶级牌，然后将它们移除。如果有几种可能性，玩家可以选择任何一种。如果所有的牌都从桌上移除，玩家将赢得游戏，如果一些牌仍然在桌上，并且没有有效的移动，玩家将失败。



乔治喜欢这种游戏。但当有几种可能时，他不知道要选择哪一张。乔治不想多想，所以在这种情况下，他只需从可能的情况中选择一对随机的，并删除它。乔治选择每种情况的可能性相同。



例如，如果最上面的牌是Ks、Kh、Kd、9h、8s、8d、7c、7d和6h，他会删除任何一对在(KS, KH)、(KS, KD)、(KH, KD)、 (8S, 8D)和 (7C, 7D)中的任何一对。删除（Ks,Kh）、（Ks,Kd）、（Kh,Kd）、（8s,8d）和（7c,7d）的概率都为1/5。



请算出在游戏开始时，根据桌上的牌，找出如果乔治按照描述行事，他赢得游戏的可能性是多少。

## 输入格式

输入文件包含几个测试用例，每个测试用例由九行组成。每行包含四张牌的描述，它们在游戏开始时形成一堆，从下一张牌到上一张牌。



每张卡片有两个字符：一个用于等级，一个用于花色。等级用“6”表示6，“7”表示7，“8”表示8，“9”表示9，“T”表示10，“J”表示杰克，“Q”表示女王，“K”表示国王，“A”表示王牌。花色用“S”代表黑桃，C代表梅花，D代表钻石，H代表红桃。例如，“KS”表示黑桃王。



每个卡片描述之间用一个空格隔开。

## 输出格式

对于每个测试用例，输出一行实数-如果乔治随机玩游戏，他赢得游戏的概率。您的答案必须精确到小数点后6位

## 样例输入，输出略



---



---

# 题号列表

- UVA10212 - The Last Non-zero Digit.
- UVA11464 - Even Parity
- UVA11806 - Cheerleaders
- UVA1303 - Wall
- UVA1637 - 纸牌游戏 Double Patience


---

---
title: "Pebble Solitaire"
layout: "post"
diff: 提高+/省选-
pid: UVA10651
tag: ['模拟', '状态合并', '进制']
---

# Pebble Solitaire

## 题目描述

[原PDF](https://uva.onlinejudge.org/external/106/p10651.pdf)

Pebble Solitaire是一款有趣的游戏。你会得到一个上面有一排小洞的板，这些洞最初只有一个没有被鹅卵石占据。 游戏的目的是从棋盘上移除尽可能多的鹅卵石。如果满足以下条件，你就可以进行移动：如果存在三个相邻的、能连成一条直线的洞（不妨称它们为A，B和C），中间为B，其中A是空的，但B和C上均有一个石子。那么你可以把C上的石子移到A上，并拿走B中的石子。 你可以继续移动石子，直到无法再移动为止。

在这个问题中，我们来看一个简单的游戏变体，即一个沿着一条线放置十二个小洞的板。 每次游戏开始时，有一些洞上被放有石子。你的任务是使尽可能少的鹅卵石留在棋盘上。

![pr](https://cdn.luogu.org/upload/pic/23786.png)

在 a) 中有两种可能的移动，分别是8->6和7->9。

b) 为 a) 选择第二种移动方式的结果，此时又有两种移动方式，分别是5->7或者6->4。

c) 作为 b) 做出第一种选择的结果，此时再没有其它的移动方式了。

## 输入格式

输入的第一行为一个n，接下来有n行分别为不同的n个游戏。 每个游戏包括一行输入，正好有十二个字符，按顺序描述板的十二个空腔。每一个字符都是'-'或'o'（英语字母表中的第十五个小写字符）。‘-’（负号）表示空洞，而“o”表示洞里面有一块鹅卵石。正如你在样本中发现的那样，输入可能是不能再移动的。

## 输出格式

对于输入中的n个游戏中的每一个，输出在那一个游戏中板上能够在移动中留下的最小数量的鹅卵石。

## 输入输出样例

##### 输入样例#1：
```cpp
5
---oo-------
-o--o-oo----
-o----ooo---
oooooooooooo
oooooooooo-o
##### 输出样例#1：
```cpp
1
2
3
12
1

感谢@Ezios 提供的翻译

## 样例 #1

### 输入

```
5
---oo-------
-o--o-oo----
-o----ooo---
oooooooooooo
oooooooooo-o
```

### 输出

```
1
2
3
12
1
```



---

---
title: "Sudoku Extension"
layout: "post"
diff: 提高+/省选-
pid: UVA1461
tag: ['模拟', '搜索', '剪枝']
---

# Sudoku Extension

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4207

[PDF](https://uva.onlinejudge.org/external/14/p1461.pdf)



---

---
title: "圈图的匹配 Edge Case"
layout: "post"
diff: 提高+/省选-
pid: UVA1646
tag: ['模拟', '高精度', '斐波那契数列']
---

# 圈图的匹配 Edge Case

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4521

[PDF](https://uva.onlinejudge.org/external/16/p1646.pdf)



---



---

# 题号列表

- UVA10651 - Pebble Solitaire
- UVA1461 - Sudoku Extension
- UVA1646 - 圈图的匹配 Edge Case


---

---
title: "Following Orders"
layout: "post"
diff: 提高+/省选-
pid: UVA124
tag: ['搜索', '深度优先搜索 DFS', '拓扑排序']
---

# Following Orders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=60

[PDF](https://uva.onlinejudge.org/external/1/p124.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/a4a2f6fd96f29dbbab122912895a18a100222b62.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/54c2361014489729658ffc3ced224b7aa260b8c2.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA124/d3b6edfcc40cb2874efe9a2a99da24fc2905e6df.png)

## 样例 #1

### 输入

```
a b f g
a b b f
v w x y z
v y x v z v w v
```

### 输出

```
abfg
abgf
agbf
gabf
wxzvy
wzxvy
xwzvy
xzwvy
zwxvy
zxwvy
```



---



---

# 题号列表

- UVA124 - Following Orders


---

---
title: "苗条的生成树 Slim Span"
layout: "post"
diff: 提高+/省选-
pid: UVA1395
tag: ['并查集', '排序', '生成树']
---

# 苗条的生成树 Slim Span

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4141

[PDF](https://uva.onlinejudge.org/external/13/p1395.pdf)



---



---

# 题号列表

- UVA1395 - 苗条的生成树 Slim Span


---

---
title: "Crossing Streets"
layout: "post"
diff: 提高+/省选-
pid: UVA1043
tag: ['搜索', '离散化']
---

# Crossing Streets

## 题目描述

Peter 要从家到学校，他想要规划穿过马路条数最少的路线。

给定 $n$ 条马路的起始点与终点坐标（马路一定与坐标轴平行），以及 Peter 家和大学所在位置坐标。求 Peter 从家到大学的任意路径下最少穿过多少条马路。特别地，Peter 不能穿过马路之间的交点。

## 输入格式

题目含有多组数据。

对于每组数据：

第一行，输入一个整数 $n$，代表马路条数。

接下来 $n$ 行，每行四个数 $x_1,y_1,x_2,y_2$，代表一条马路起点与终点坐标。

接下来一行四个数，$x_h,y_h,x_u,y_u$，代表 Peter 家的坐标与大学的坐标。

当输入的 $n$ 为 $0$ 时，结束程序。

## 输出格式

对于每组数据，输出 $2$ 行，格式如下：
```
City [i]
Peter has to cross [x] streets
```
其中 `i` 代表是第几组数据，`x` 代表答案（不包含 `[]`）。

## 说明/提示

$1\le n\le 500$，所有输入的坐标绝对值不大于 $2\times 10^9$。

Translated by HYdroKomide.

## 样例 #1

### 输入

```
8
6 0 24 0
24 0 24 4
24 4 6 4
6 4 6 0
12 1 26 1
26 1 26 6
26 6 12 6
12 6 12 1
0 1 17 3
1
10 10 20 10
1 1 30 30
0
```

### 输出

```
City 1
Peter has to cross 2 streets
City 2
Peter has to cross 0 streets
```



---

---
title: "Bribing FIPA"
layout: "post"
diff: 提高+/省选-
pid: UVA1222
tag: ['字符串', '离散化', '背包 DP']
---

# Bribing FIPA

## 题目描述

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。

## 输入格式

多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。


多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。

## 输出格式

对于每组输入数据，输出一行表示答案。
```
UVA1222

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。


对于每组输入数据，输出一行表示答案。
样例输入：
3 2
Aland 10
Boland 20 Aland
Coland 15
#

样例输出：
20



---



---

# 题号列表

- UVA1043 - Crossing Streets
- UVA1222 - Bribing FIPA


---

---
title: "最小公倍数的最小和 Minimum Sum LCM"
layout: "post"
diff: 提高+/省选-
pid: UVA10791
tag: ['递归', '枚举', '素数判断,质数,筛法']
---

# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/7a5e01d2fc4bd5a007ecd456a07165372a1da9fa.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/eb4e5ec11ec7e64f907d2a65a0fcc8faf715a7db.png)

## 样例 #1

### 输入

```
12
10
5
0
```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6
```



---

---
title: "H-半素数 Semi-prime H-numbers"
layout: "post"
diff: 提高+/省选-
pid: UVA11105
tag: ['枚举', '素数判断,质数,筛法', '中国剩余定理 CRT']
---

# H-半素数 Semi-prime H-numbers

## 题目描述

# 【问题描述】

形如$4n+1$的数被称为“H数”，乘法在“H数”组成的集合内是封闭的。在这个集合中只能被1和本身整除的数叫做“H-素数”（不包括1），其余的数被称为“H-合数”。一个“H-合成数”是一个能且只能分解成两个“H-素数”乘积的“H-合数”（可能有多种分解方案）。比如$441=21*21=9*49$,所以$441$是“H-合成数”。$125=5*5*5$,所以125不是“H-合成数”。

求$0$~$h$范围内“H-合成数”的个数。

## 输入格式

输入若干行，每行一个小于等于$1000001$的整数$h$，一个$0$表示结束。

## 输出格式

对于每一行输入，输出两个数，第一个表示当前的$h$，第二个表示答案。

## 样例 #1

### 输入

```
21
85
789
0
```

### 输出

```
21 0
85 5
789 62
```



---

---
title: "GCD Guessing Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1521
tag: ['贪心', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCD Guessing Game

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4267

[PDF](https://uva.onlinejudge.org/external/15/p1521.pdf)


## 输入格式

**本题在单测试点内有多组测试数据，请读入到 EOF。**

给定 $n (2 \leq n \leq 10^4)$，玩一个猜数游戏。目标为 $p (p \in [1, n])$。

每一次可以猜一个数 $x$，会告诉你 $\gcd(x, p)$。

求在 **最坏** 情况下，至少需要猜几次 **保证** 猜出 $p$。

## 输出格式

对于每一组数据，输出答案并换行。

## 说明/提示

Translated by @[longgod](/user/39675), retranslated by @[Carroty_cat](/user/912750).

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```



---



---

# 题号列表

- UVA10791 - 最小公倍数的最小和 Minimum Sum LCM
- UVA11105 - H-半素数 Semi-prime H-numbers
- UVA1521 - GCD Guessing Game


---

---
title: "最小公倍数的最小和 Minimum Sum LCM"
layout: "post"
diff: 提高+/省选-
pid: UVA10791
tag: ['递归', '枚举', '素数判断,质数,筛法']
---

# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/7a5e01d2fc4bd5a007ecd456a07165372a1da9fa.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/eb4e5ec11ec7e64f907d2a65a0fcc8faf715a7db.png)

## 样例 #1

### 输入

```
12
10
5
0
```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6
```



---

---
title: "H-半素数 Semi-prime H-numbers"
layout: "post"
diff: 提高+/省选-
pid: UVA11105
tag: ['枚举', '素数判断,质数,筛法', '中国剩余定理 CRT']
---

# H-半素数 Semi-prime H-numbers

## 题目描述

# 【问题描述】

形如$4n+1$的数被称为“H数”，乘法在“H数”组成的集合内是封闭的。在这个集合中只能被1和本身整除的数叫做“H-素数”（不包括1），其余的数被称为“H-合数”。一个“H-合成数”是一个能且只能分解成两个“H-素数”乘积的“H-合数”（可能有多种分解方案）。比如$441=21*21=9*49$,所以$441$是“H-合成数”。$125=5*5*5$,所以125不是“H-合成数”。

求$0$~$h$范围内“H-合成数”的个数。

## 输入格式

输入若干行，每行一个小于等于$1000001$的整数$h$，一个$0$表示结束。

## 输出格式

对于每一行输入，输出两个数，第一个表示当前的$h$，第二个表示答案。

## 样例 #1

### 输入

```
21
85
789
0
```

### 输出

```
21 0
85 5
789 62
```



---

---
title: "GCD Guessing Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1521
tag: ['贪心', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCD Guessing Game

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4267

[PDF](https://uva.onlinejudge.org/external/15/p1521.pdf)


## 输入格式

**本题在单测试点内有多组测试数据，请读入到 EOF。**

给定 $n (2 \leq n \leq 10^4)$，玩一个猜数游戏。目标为 $p (p \in [1, n])$。

每一次可以猜一个数 $x$，会告诉你 $\gcd(x, p)$。

求在 **最坏** 情况下，至少需要猜几次 **保证** 猜出 $p$。

## 输出格式

对于每一组数据，输出答案并换行。

## 说明/提示

Translated by @[longgod](/user/39675), retranslated by @[Carroty_cat](/user/912750).

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```



---



---

# 题号列表

- UVA10791 - 最小公倍数的最小和 Minimum Sum LCM
- UVA11105 - H-半素数 Semi-prime H-numbers
- UVA1521 - GCD Guessing Game


---

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



---

# 题号列表

- UVA10902 - Pick-up Sticks
- UVA11525 - Permutation
- UVA11992 - Fast Matrix Operations
- UVA12003 - Array Transformer
- UVA1322 - 优化最大值电路 Minimizing Maximizer
- UVA1400 - "Ray, Pass me the dishes!"
- UVA1455 - Kingdom


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

# 题号列表

- UVA11525 - Permutation


---

---
title: "Bribing FIPA"
layout: "post"
diff: 提高+/省选-
pid: UVA1222
tag: ['字符串', '离散化', '背包 DP']
---

# Bribing FIPA

## 题目描述

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。

## 输入格式

多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。


多组输入数据，每组的第一行为两个整数$N$、$M(1 \leq N \leq 200 , 0 \leq M \leq N)$，接下来的$N$行描述一个国家，每行依次为一个字符串表示国家的名称、一个数字描述需要的钻石数量、若干个字符串表示该国家直接的附属国。总输入以一行一个‘#’号表示结束。

## 输出格式

对于每组输入数据，输出一行表示答案。
```
UVA1222

题意：

在$FIPA$即将有一场投票来决定下一届$IPWC$的举办地，而某个国家的代表想通过赠送钻石争取其他国家的投票。他已经知道了争取到每一个国家的选票各需要的钻石的数量，但是因为有一些贫弱的国家会与其直接或间接附属于的大国投相同国家的票，所以他不需要给每一个国家钻石以争取选票。

比如，$C$国家附属于$B$国家，而$B$国家附属于$A$国家，则在向A国家赠送礼物后，可以获得$ABC$三国的选票。已知不存在一个国家附属于多个国家，且附属关系之间不存在环，试求在$N$个国家中获得至少$M$个国家的选票最少需要花费的钻石数量。


对于每组输入数据，输出一行表示答案。
样例输入：
3 2
Aland 10
Boland 20 Aland
Coland 15
#

样例输出：
20



---



---

# 题号列表

- UVA1222 - Bribing FIPA


---

---
title: "最小公倍数的最小和 Minimum Sum LCM"
layout: "post"
diff: 提高+/省选-
pid: UVA10791
tag: ['递归', '枚举', '素数判断,质数,筛法']
---

# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/7a5e01d2fc4bd5a007ecd456a07165372a1da9fa.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/eb4e5ec11ec7e64f907d2a65a0fcc8faf715a7db.png)

## 样例 #1

### 输入

```
12
10
5
0
```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6
```



---

---
title: "H-半素数 Semi-prime H-numbers"
layout: "post"
diff: 提高+/省选-
pid: UVA11105
tag: ['枚举', '素数判断,质数,筛法', '中国剩余定理 CRT']
---

# H-半素数 Semi-prime H-numbers

## 题目描述

# 【问题描述】

形如$4n+1$的数被称为“H数”，乘法在“H数”组成的集合内是封闭的。在这个集合中只能被1和本身整除的数叫做“H-素数”（不包括1），其余的数被称为“H-合数”。一个“H-合成数”是一个能且只能分解成两个“H-素数”乘积的“H-合数”（可能有多种分解方案）。比如$441=21*21=9*49$,所以$441$是“H-合成数”。$125=5*5*5$,所以125不是“H-合成数”。

求$0$~$h$范围内“H-合成数”的个数。

## 输入格式

输入若干行，每行一个小于等于$1000001$的整数$h$，一个$0$表示结束。

## 输出格式

对于每一行输入，输出两个数，第一个表示当前的$h$，第二个表示答案。

## 样例 #1

### 输入

```
21
85
789
0
```

### 输出

```
21 0
85 5
789 62
```



---

---
title: "GCD Guessing Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1521
tag: ['贪心', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCD Guessing Game

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4267

[PDF](https://uva.onlinejudge.org/external/15/p1521.pdf)


## 输入格式

**本题在单测试点内有多组测试数据，请读入到 EOF。**

给定 $n (2 \leq n \leq 10^4)$，玩一个猜数游戏。目标为 $p (p \in [1, n])$。

每一次可以猜一个数 $x$，会告诉你 $\gcd(x, p)$。

求在 **最坏** 情况下，至少需要猜几次 **保证** 猜出 $p$。

## 输出格式

对于每一组数据，输出答案并换行。

## 说明/提示

Translated by @[longgod](/user/39675), retranslated by @[Carroty_cat](/user/912750).

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```



---



---

# 题号列表

- UVA10791 - 最小公倍数的最小和 Minimum Sum LCM
- UVA11105 - H-半素数 Semi-prime H-numbers
- UVA1521 - GCD Guessing Game


---

---
title: "Ferry Loading II"
layout: "post"
diff: 提高+/省选-
pid: UVA10440
tag: ['动态规划 DP', '贪心']
---

# Ferry Loading II

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1381

[PDF](https://uva.onlinejudge.org/external/104/p10440.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/62f4e72b9730523fdb77b04f21f28f29a3eff81d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/0bb9d3b2914964e55e2370002ec531eaa0ab40b4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/4a97c3e41ba3630f0efc866c67bde50939a5e9db.png)

## 样例 #1

### 输入

```
2
2 10 10
0
10
20
30
40
50
60
70
80
90
2 10 3
10
30
40
```

### 输出

```
100 5
50 2
```



---

---
title: "GCD Guessing Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1521
tag: ['贪心', '素数判断,质数,筛法', '最大公约数 gcd']
---

# GCD Guessing Game

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4267

[PDF](https://uva.onlinejudge.org/external/15/p1521.pdf)


## 输入格式

**本题在单测试点内有多组测试数据，请读入到 EOF。**

给定 $n (2 \leq n \leq 10^4)$，玩一个猜数游戏。目标为 $p (p \in [1, n])$。

每一次可以猜一个数 $x$，会告诉你 $\gcd(x, p)$。

求在 **最坏** 情况下，至少需要猜几次 **保证** 猜出 $p$。

## 输出格式

对于每一组数据，输出答案并换行。

## 说明/提示

Translated by @[longgod](/user/39675), retranslated by @[Carroty_cat](/user/912750).

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```



---



---

# 题号列表

- UVA10440 - Ferry Loading II
- UVA1521 - GCD Guessing Game


---

---
title: "Pebble Solitaire"
layout: "post"
diff: 提高+/省选-
pid: UVA10651
tag: ['模拟', '状态合并', '进制']
---

# Pebble Solitaire

## 题目描述

[原PDF](https://uva.onlinejudge.org/external/106/p10651.pdf)

Pebble Solitaire是一款有趣的游戏。你会得到一个上面有一排小洞的板，这些洞最初只有一个没有被鹅卵石占据。 游戏的目的是从棋盘上移除尽可能多的鹅卵石。如果满足以下条件，你就可以进行移动：如果存在三个相邻的、能连成一条直线的洞（不妨称它们为A，B和C），中间为B，其中A是空的，但B和C上均有一个石子。那么你可以把C上的石子移到A上，并拿走B中的石子。 你可以继续移动石子，直到无法再移动为止。

在这个问题中，我们来看一个简单的游戏变体，即一个沿着一条线放置十二个小洞的板。 每次游戏开始时，有一些洞上被放有石子。你的任务是使尽可能少的鹅卵石留在棋盘上。

![pr](https://cdn.luogu.org/upload/pic/23786.png)

在 a) 中有两种可能的移动，分别是8->6和7->9。

b) 为 a) 选择第二种移动方式的结果，此时又有两种移动方式，分别是5->7或者6->4。

c) 作为 b) 做出第一种选择的结果，此时再没有其它的移动方式了。

## 输入格式

输入的第一行为一个n，接下来有n行分别为不同的n个游戏。 每个游戏包括一行输入，正好有十二个字符，按顺序描述板的十二个空腔。每一个字符都是'-'或'o'（英语字母表中的第十五个小写字符）。‘-’（负号）表示空洞，而“o”表示洞里面有一块鹅卵石。正如你在样本中发现的那样，输入可能是不能再移动的。

## 输出格式

对于输入中的n个游戏中的每一个，输出在那一个游戏中板上能够在移动中留下的最小数量的鹅卵石。

## 输入输出样例

##### 输入样例#1：
```cpp
5
---oo-------
-o--o-oo----
-o----ooo---
oooooooooooo
oooooooooo-o
##### 输出样例#1：
```cpp
1
2
3
12
1

感谢@Ezios 提供的翻译

## 样例 #1

### 输入

```
5
---oo-------
-o--o-oo----
-o----ooo---
oooooooooooo
oooooooooo-o
```

### 输出

```
1
2
3
12
1
```



---

---
title: "校长的烦恼 Headmaster's Headache"
layout: "post"
diff: 提高+/省选-
pid: UVA10817
tag: ['动态规划 DP', '状态合并', '进制']
---

# 校长的烦恼 Headmaster's Headache

## 题目描述

斯普林菲尔德（春之田野？？？）学院的校长正在考虑为某些科目招聘新老师 现在有一批申请岗位的老师 每个老师能教一个或多个科目 校长想要选择一些申请者以保证每个科目都至少有两名老师能教 同时总共花的钱要最小

## 输入格式

输入由多组测试组成，它们的格式如下： 第一行包含三个给定的整数S，M和N， S (<=8)是科目的总数 M(<=20)是在职教师数，N(<=100)是应聘者的数量

接下来M行每行描述一个在职教师 首先给出雇佣他的花费C (10000<=C<=50000) ,接下来是他能教的科目列表 科目用1—S的整数表示 你必须保证继续聘用他们

之后N行，以同样格式给出应聘者的信息

输入以一个空测试S=0结束，你不应当处理它 （这句有些别扭，不过懂意思就好）

## 输出格式

对于每组测试，输出符合条件的最小花费
翻译贡献者UID：60885

## 样例 #1

### 输入

```
2 2 2
10000 1
20000 2
30000 1 2
40000 1 2
0 0 0
```

### 输出

```
60000
```



---

---
title: "Nuts for nuts.."
layout: "post"
diff: 提高+/省选-
pid: UVA10944
tag: ['枚举', '进制']
---

# Nuts for nuts..

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1885

[PDF](https://uva.onlinejudge.org/external/109/p10944.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/eab44d58cb45ad772b3f67192aa37528e61e5fe1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/a1c24b72a850b0c3c74a01bb376efca80cd04044.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10944/aa27c38474cbf5db18725d954fc07f00ee41663b.png)

## 样例 #1

### 输入

```
5 5
L....
#....
#....
.....
#....
5 5
L....
#....
#....
.....
#....
```

### 输出

```
8
8
```



---

---
title: "古代象形符号 Ancient Messages"
layout: "post"
diff: 提高+/省选-
pid: UVA1103
tag: ['连通块', '进制', '构造']
---

# 古代象形符号 Ancient Messages

## 题目描述

为了理解早期文明，考古学家经常研究用古代语言编写的文本。在3000多年前的埃及使用的一种语言是基于称为象形文字的字符。如图显示了六个象形文字及其名称，在这个题目中，您需要编写一个程序来识别这六个字。

![]("C:\Users\白文礼\Desktop\4_1.png")

输入INPUT：
```

## 输入格式

输入由几个测试用例组成，每个测试用例描述一个包含一个或多个的图像。 象形文字选自图所示的那些。图像以一系列水平扫描线的形式给出，这些水平扫描线由黑色像素（由1表示）和白色像素（由0表示）组成。在输入数据中，每个扫描线以十六进制表示法编码。 例如，序列将表示八个像素10011100（一个黑色像素，后面是两个白色像素，依此类推） 十六进制表示法为9c。 在十六进制中仅使用数字和小写字母a到f编码。每个测试用例的第一行包含两个整数，H和W。H（0＜H≤200）是 图像中的扫描行数。 W（0＜W≤50）是每行中十六进制字符的数量 。 接下来的H行包含图像的十六进制字符，从上到下。
输入图像符合以下规则：
图像仅包含图1中所示的象形文字。
每个图像至少包含一个有效的象形文字。
图像中的每个黑色像素都是有效象形文字的一部分。
每个象形文字由一组连邻的黑色像素组成，即每个黑色像素至少和一个位于其顶部，底部，左侧或右侧的其他黑色像素相临。
象形文字间不相连，一个象形文字中不包含其他象形文字。
对角线顶点接触的两个黑色像素必然具有共同的相邻的黑色像素。
象形文字可能会扭曲，但其在拓扑结构上一定等同于图1中的一个符号。 （两个图形的拓扑结构等同是说一个图形通过扭曲拖拽可以成为另一个图形，但是不能撕裂。） 
在输入所有测试用例之后换行并输入两个零，表示结束。

输入样例
100 25 
0000000000000000000000000 
0000000000000000000000000 
...(50 lines omitted)... 
00001fe0000000000007c0000 
00003fe0000000000007c0000 
...(44 lines omitted)... 
0000000000000000000000000 
0000000000000000000000000
150 38 
00000000000000000000000000000000000000
00000000000000000000000000000000000000 
...(75 lines omitted)... 
0000000003fffffffffffffffff00000000000 
0000000003fffffffffffffffff00000000000 
...(69 lines omitted)... 
00000000000000000000000000000000000000
00000000000000000000000000000000000000 
0 0
```

输出OUTPUT：

```

## 输出格式

对于每个测试用例，输出其测试用例编号，后跟一个字符串，字符串包含的每一个字符都代表一个图像中的象形文字，具体对应关系如下：
Ankh：A
Wedjat：J
Djed：D 
Scarab：S
Was：W
Akhet：K

输出样例
Case 1: AKW
Case 2: AAAAA
```



---

---
title: "Tiling Dominoes"
layout: "post"
diff: 提高+/省选-
pid: UVA11270
tag: ['动态规划 DP', '进制', '插头 DP']
---

# Tiling Dominoes

## 题目描述

题目大意

给定一个m×n的矩形网格，用1×2多米诺骨牌完全平铺。 请注意，即使一个平铺的旋转与另一个平铺相匹配，它们仍算作不同的平铺。 下面显示了一个平铺示例。

## 输入格式

输入包括多组数据。每组数据占一行，包含两个整数m，n（n×m≤100）。输入结束标志为文件结束符（EOF）。

## 输出格式

对于每组数据输出一行，输出总数。

## 样例 #1

### 输入

```
2 10
4 10
8 8
```

### 输出

```
89
18061
12988816
```



---

---
title: "Even Parity"
layout: "post"
diff: 提高+/省选-
pid: UVA11464
tag: ['递推', '枚举', '进制', '概率论']
---

# Even Parity

## 题目描述

给你一个 $n \times n$ 的 $01$ 矩阵（每个元素非 $0$ 即 $1$），你的任务是把尽量少的 $0$ 变成 $1$，使得原矩阵便为偶数矩阵（矩阵中每个元素的上、下、左、右的元素（如果存在的话）之和均为偶数）。

## 输入格式

输入的第一行为数据组数 $T$（$T \le 30$）。每组数据：第一行为正整数 $n$（$1 \le n \le 15$）；接下来的 $n$ 行每行包含 $n$ 个非 $0$ 即 $1$ 的整数，相邻整数间用一个空格隔开。

## 输出格式

对于每组数据，输出被改变的元素的最小个数。如果无解，输出 $-1$。

## 样例 #1

### 输入

```
3
3
0 0 0
0 0 0
0 0 0
3
0 0 0
1 0 0
0 0 0
3
1 1 1
1 1 1
0 0 0
```

### 输出

```
Case 1: 0
Case 2: 3
Case 3: -1
```



---

---
title: "Hackers' Crackdown"
layout: "post"
diff: 提高+/省选-
pid: UVA11825
tag: ['数学', '状态合并', '进制']
---

# Hackers' Crackdown

## 题目描述

假如你是一个黑客，侵入了一个有着 $n$ 台计算机（编号为$0,1,2,3....n-1$）的网络。一共有 $n$ 种服务，每台计算机都运行着所有服务。对于每台计算机，你都可以选择一项服务，终止这台计算机和所有与它相邻计算机的该项服务（如果其中一些服务已经停止，那他们继续保持停止状态）。你的目标是让尽量多的服务完全瘫痪(即：没有任何计算及运行着该服务)

## 输入格式

输入包含多组数据，每组数据的第一行为整数 $n(1\leq n\leq 16)$ : 以下 $n$ 行每行描述一台计算机相邻的计算机，其中第一个数 $m$ 为相邻计算机个数，接下来的 $m$ 个整数为这些计算机的编号。输入结束标志 $n=0$。

## 输出格式

对于每组数据，输出完全瘫痪的服务的数量。

## 样例 #1

### 输入

```
3
2 1 2
2 0 2
2 0 1
4
1 1
1 0
1 3
1 2
0
```

### 输出

```
Case 1: 3
Case 2: 2
```



---



---

# 题号列表

- UVA10651 - Pebble Solitaire
- UVA10817 - 校长的烦恼 Headmaster's Headache
- UVA10944 - Nuts for nuts..
- UVA1103 - 古代象形符号 Ancient Messages
- UVA11270 - Tiling Dominoes
- UVA11464 - Even Parity
- UVA11825 - Hackers' Crackdown


---

---
title: "最小公倍数的最小和 Minimum Sum LCM"
layout: "post"
diff: 提高+/省选-
pid: UVA10791
tag: ['递归', '枚举', '素数判断,质数,筛法']
---

# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/7a5e01d2fc4bd5a007ecd456a07165372a1da9fa.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/eb4e5ec11ec7e64f907d2a65a0fcc8faf715a7db.png)

## 样例 #1

### 输入

```
12
10
5
0
```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6
```



---

---
title: "完美的服务 Perfect Service"
layout: "post"
diff: 提高+/省选-
pid: UVA1218
tag: ['动态规划 DP', '递归', '枚举']
---

# 完美的服务 Perfect Service

## 题目描述

一个网络中有 $N$ 个节点，由 $N-1$ 条边连通，每个节点是服务器或者客户端。如果节点 $u$ 是客户端，就意味着 $u$ 所连接的所有点中有且仅有一台服务器。求最少要多少台服务器才能满足要求。

## 输入格式

输入包含多组测试数据。对于每组数据，第一行是一个整数 $N(\le10000)$。

接下来 $N-1$ 行，每行两个整数 $a_i,b_i$，表示 $a_i,b_i$ 有一条双向连通的边。

除最后一组输入以外，每组数据以 $0$ 结尾，最后一组数据以 $-1$ 结尾。

## 输出格式

对于每组输入，仅输出一行，表示所需要的最小服务器台数。

翻译贡献者：An_Account.



---



---

# 题号列表

- UVA10791 - 最小公倍数的最小和 Minimum Sum LCM
- UVA1218 - 完美的服务 Perfect Service


---

---
title: "Multi-peg Towers of Hanoi"
layout: "post"
diff: 提高+/省选-
pid: UVA10444
tag: ['动态规划 DP', '高精度', '递推']
---

# Multi-peg Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1385

[PDF](https://uva.onlinejudge.org/external/104/p10444.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/b08ae043c16349a4e020bb344c82bd8559661c15.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/9918d07219dee733e043308fe7408963612853cc.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/28c5f29618658abb670593f72b8636cd5eadedfe.png)

## 样例 #1

### 输入

```
3 4
4 4
10 4
10 5
0 0
```

### 输出

```
Case 1: 5
Case 2: 9
Case 3: 49
Case 4: 31
```



---

---
title: "Tribles"
layout: "post"
diff: 提高+/省选-
pid: UVA11021
tag: ['递推', '期望', '线性递推']
---

# Tribles

## 题目描述

# Tribles

## 题面翻译

### 题目大意

一开始有 $k$ 只生物，这种生物只能活一天，死的时候有 $p_i$ 的概率生成 $i$ 只这种生物（也只能活一天），询问 $m$ 天内所有生物都死的概率（包括 $m$ 天前死亡的情况）


[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1962

[PDF](https://uva.onlinejudge.org/external/110/p11021.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/dc00578efa81b6aad117bc54386f7e892627c921.png)

## 输入格式

第一行输入一个整数 $T$，表示数据总数

每一组先输入三个整数 $n(1<=n<=1000),k(0<=k<=1000),m(0<=m<=1000)$

接下来 $n$ 行，每行一个实数，分别为 $p_0$ 到 $p_{n-1}$


![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/08abc60eb45dcabca841e2417b496cd3ae2dca35.png)

## 输出格式

对于每一组数据，先输出"Case #x: "（请注意冒号后有一个**空格**）
再输出答案，精度要求在 1e-6 以内（即保留小数点后七位）

感谢@xMinh 提供翻译


![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/77ab0f01844658d722f6868f9a488841f59db741.png)

## 样例 #1

### 样例输入 #1

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5
```

### 样例输出 #1

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062
```

## 样例 #1

### 输入

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5
```

### 输出

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062
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
title: "Even Parity"
layout: "post"
diff: 提高+/省选-
pid: UVA11464
tag: ['递推', '枚举', '进制', '概率论']
---

# Even Parity

## 题目描述

给你一个 $n \times n$ 的 $01$ 矩阵（每个元素非 $0$ 即 $1$），你的任务是把尽量少的 $0$ 变成 $1$，使得原矩阵便为偶数矩阵（矩阵中每个元素的上、下、左、右的元素（如果存在的话）之和均为偶数）。

## 输入格式

输入的第一行为数据组数 $T$（$T \le 30$）。每组数据：第一行为正整数 $n$（$1 \le n \le 15$）；接下来的 $n$ 行每行包含 $n$ 个非 $0$ 即 $1$ 的整数，相邻整数间用一个空格隔开。

## 输出格式

对于每组数据，输出被改变的元素的最小个数。如果无解，输出 $-1$。

## 样例 #1

### 输入

```
3
3
0 0 0
0 0 0
0 0 0
3
0 0 0
1 0 0
0 0 0
3
1 1 1
1 1 1
0 0 0
```

### 输出

```
Case 1: 0
Case 2: 3
Case 3: -1
```



---

---
title: "阿里巴巴 Alibaba"
layout: "post"
diff: 提高+/省选-
pid: UVA1632
tag: ['递推']
---

# 阿里巴巴 Alibaba

## 题目描述

## 题面描述
在**一条直线**的同一个方向上有  $n$ 件珠宝，已知每件珠宝的位置，并且第  $i$ 件珠宝在  $t_i$ 时刻就毁灭，问能否将所有的珠宝收集起来？搜集不耗时，移动需要耗时。

## 输入格式

第一行一个整数  $n$（ $n\le10000$）。  
接下来  $n$ 行，每行两个整数，分别为  $a_i$ 和  $t_i$ ，表示从起点走到此处的时间和珠宝消失的时间。

## 输出格式

如果可以收集所有珠宝，则输出最短的时间（不需要回到起点）否则输出`No solution`



---

---
title: "巴比伦塔 The Tower of Babylon"
layout: "post"
diff: 提高+/省选-
pid: UVA437
tag: ['动态规划 DP', '搜索', '递推', '排序']
---

# 巴比伦塔 The Tower of Babylon

## 题目描述

你可能已经听说过巴比伦塔的传说。现在这个传说的许多细节已经被遗忘。所以本着本场比赛的教育性质，我们现在会告诉你整个传说：

巴比伦人有 $n$ 种长方形方块，每种有无限个，第 $i$ 种方块的三边边长是 $xi,yi,zi$。对于每一个方块，你可以任意选择一面作为底，这样高就随着确定了。举个例子，同一种方块，可能其中一个是竖着放的，一个是侧着放的，一个是横着放的。

他们想要用堆方块的方式建尽可能高的塔。问题是，只有一个方块的底的两条边严格小于另一个方块的底的两条边，这个方块才能堆在另一个上面。这意味着，一个方块甚至不能堆在一个底的尺寸与它一样的方块的上面。

你的任务是编写一个程序，计算出这个塔可以建出的最高的高度。

## 输入格式

输入会包含至少一组数据，每组数据的第一行是一个整数 $n(n\le30)$，表示方块的种类数。 这组数据接下来的 $n$ 行，每行有三个整数，表示 $xi,yi,zi$。输入数据会以 $0$ 结束。

## 输出格式

对于每组数据，输出一行，其中包含组号（从 $1$ 开始）和塔最高的高度。按以下格式：``Case i: maximum height = __``。

## 样例 #1

### 输入

```
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
```

### 输出

```
Case 1: maximum height = 40
Case 2: maximum height = 21
Case 3: maximum height = 28
Case 4: maximum height = 342
```



---

---
title: "勤劳的蜜蜂 Bee Breeding"
layout: "post"
diff: 提高+/省选-
pid: UVA808
tag: ['数学', '递推']
---

# 勤劳的蜜蜂 Bee Breeding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=749

[PDF](https://uva.onlinejudge.org/external/8/p808.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/9bab4a64afdd472dc2664e3eff03743e904c3d4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/ece86ec0d7a73280a4d4325cfcfeda323b9b3cd5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/0f05e34c6915f5c4d3fc623283f0f02d6594ce4c.png)

## 样例 #1

### 输入

```
19 30
0 0
```

### 输出

```
The distance between cells 19 and 30 is 5.
```



---



---

# 题号列表

- UVA10444 - Multi-peg Towers of Hanoi
- UVA11021 - Tribles
- UVA11300 - Spreading the Wealth
- UVA11464 - Even Parity
- UVA1632 - 阿里巴巴 Alibaba
- UVA437 - 巴比伦塔 The Tower of Babylon
- UVA808 - 勤劳的蜜蜂 Bee Breeding


---

---
title: "K Smallest Sums"
layout: "post"
diff: 提高+/省选-
pid: UVA11997
tag: ['数学', '最短路', '队列']
---

# K Smallest Sums

## 题目描述

有一个 $k \times k$ 的矩阵，在每行任取一个位置，把这些位置的元素相加的到一个值，求前 $k$ 小的值。

## 输入格式

多组数据。

每组第一行是整数 $k$。

第 $2$ 到 $k+1$ 行中的第 $i+1$ 行有 $k$ 个整数，第 $j$ 个表示 $a_{i,j}$。

## 输出格式

每行 $k$ 个整数，表示答案。

## 说明/提示

对于 $100\%$ 的数据，$2 \leq k \leq 750$。

## 样例 #1

### 输入

```
3
1 8 5
9 2 5
10 7 6
2
1 1
1 2
```

### 输出

```
9 10 12
2 2
```



---

---
title: "理想路径 Ideal Path"
layout: "post"
diff: 提高+/省选-
pid: UVA1599
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 输入格式

输入共$m+1$行：

第一行$2$个空格整数：$n$和$m$。

以后$m$行，每行空格隔开的$3$个整数$a_i,b_i,c_i$，表示在$a_i,b_i$之间有一条颜色为$c_i$的道路。

## 输出格式

输出共两行：

第一行$1$个正整数$k$，表示$1$到$n$至少需要经过$k$条边。

第二行包含$k$个空格隔开的正整数，表示从$1$到$n$依次经过的边的**颜色**。

## 输入输出样例：
### 输入样例：
```
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
```
### 输出样例：
```
2
1 3
```
### 输入输出样例解释：
路径依次如下：

$1\rightarrow3$，颜色为$1$（最后输入的那条）；

$3\rightarrow4$，颜色为$3$。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译



---



---

# 题号列表

- UVA11997 - K Smallest Sums
- UVA1599 - 理想路径 Ideal Path


---

---
title: "多少块土地 How Many Pieces of Land ?"
layout: "post"
diff: 提高+/省选-
pid: UVA10213
tag: ['图论', '高精度']
---

# 多少块土地 How Many Pieces of Land ?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1154

[PDF](https://uva.onlinejudge.org/external/102/p10213.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10213/82410c5d60b6479b7a08f094e449cc42577c84fa.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10213/12cbe469542e974964720e963806931c43bb097f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10213/36cbbf8a0535026ec0f15834fa670c7e8256bd64.png)

## 样例 #1

### 输入

```
4
1
2
3
4
```

### 输出

```
1
2
4
8
```



---

---
title: "Multi-peg Towers of Hanoi"
layout: "post"
diff: 提高+/省选-
pid: UVA10444
tag: ['动态规划 DP', '高精度', '递推']
---

# Multi-peg Towers of Hanoi

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1385

[PDF](https://uva.onlinejudge.org/external/104/p10444.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/b08ae043c16349a4e020bb344c82bd8559661c15.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/9918d07219dee733e043308fe7408963612853cc.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10444/28c5f29618658abb670593f72b8636cd5eadedfe.png)

## 样例 #1

### 输入

```
3 4
4 4
10 4
10 5
0 0
```

### 输出

```
Case 1: 5
Case 2: 9
Case 3: 49
Case 4: 31
```



---

---
title: "圈图的匹配 Edge Case"
layout: "post"
diff: 提高+/省选-
pid: UVA1646
tag: ['模拟', '高精度', '斐波那契数列']
---

# 圈图的匹配 Edge Case

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4521

[PDF](https://uva.onlinejudge.org/external/16/p1646.pdf)



---



---

# 题号列表

- UVA10213 - 多少块土地 How Many Pieces of Land ?
- UVA10444 - Multi-peg Towers of Hanoi
- UVA1646 - 圈图的匹配 Edge Case


---

---
title: "Bicoloring"
layout: "post"
diff: 普及/提高-
pid: UVA10004
tag: ['二分图']
---

# Bicoloring

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=945

[PDF](https://uva.onlinejudge.org/external/100/p10004.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10004/09f718cb383e213e651b85dfd47bb80608f88609.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10004/4d777247a97ad6fb46850227245dfe0ccb1ff2c9.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10004/e4ee823a4583ec36f33f5632f6b2aeb9ca4671f1.png)

## 样例 #1

### 输入

```
3
3
0 1
1 2
2 0
3
2
0 1
1 2
9
8
0 1
0 2
0 3
0 4
0 5
0 6
0 7
0 8
0
```

### 输出

```
NOT BICOLORABLE.
BICOLORABLE.
BICOLORABLE.
```



---

---
title: "Crossed Ladders"
layout: "post"
diff: 普及/提高-
pid: UVA10566
tag: ['数学', '二分']
---

# Crossed Ladders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1507

[PDF](https://uva.onlinejudge.org/external/105/p10566.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/04bd930627e82cc986e14b41bdaa0b69d1b37635.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/3754046125e48d80d182db37d7cf4ad07235fd79.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/4551903c4aac4c95f56b92a3629e8f0e97337487.png)

## 样例 #1

### 输入

```
30 40 10
12.619429 8.163332 3
10 10 3
10 10 1
```

### 输出

```
26.033
7.000
8.000
9.798
```



---

---
title: "Winterim Backpacking Trip"
layout: "post"
diff: 普及/提高-
pid: UVA907
tag: ['二分']
---

# Winterim Backpacking Trip

## 题目描述

你在进行一次远足。你现在已知路上有 $N$ 个营地，你这次远足将耗时 $K$ 个夜晚和每两个营地之间的距离。

你的每个夜晚必须在一个营地度过且你不可以走回头路。也就是说，你白天必须得走到某一个营地。

现在你需要求出：你走的最多的那天走了多远？

## 输入格式

第一行，输入两个整数，分别为营地数量 $N$ 和你将度过的夜晚数量 $K$ 。

接下来 $N+1$ 行，每行一个整数，表示两个营地之间的距离。

## 输出格式

输出一行一个整数，表示远足中你走的最多的那天走的距离。

## 说明/提示

$N$ 小于等于 $600$ , $K$ 小于等于 $300$ 。

## 样例 #1

### 输入

```
4 3
7
2
6
4
5
```

### 输出

```
8
```



---



---

# 题号列表

- UVA10004 - Bicoloring
- UVA10566 - Crossed Ladders
- UVA907 - Winterim Backpacking Trip


---

---
title: "Maximum Sum"
layout: "post"
diff: 普及/提高-
pid: UVA108
tag: ['贪心', '枚举', '前缀和']
---

# Maximum Sum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=44

[PDF](https://uva.onlinejudge.org/external/1/p108.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/9bad502ba34d25d0111329e7b191a1e73f37eafb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/396f13d4868ef41457d1488f0abfd926a952de29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/68309ab00fee7fe7c208d797f30252388b43c04b.png)

## 样例 #1

### 输入

```
4
0 -2 -7 0 
9 2 -6 2
-4 1 -4 1 
-1 8 0 -2
```

### 输出

```
15
```



---

---
title: "连续素数之和 Sum of Consecutive Prime Numbers"
layout: "post"
diff: 普及/提高-
pid: UVA1210
tag: ['素数判断,质数,筛法', '前缀和']
---

# 连续素数之和 Sum of Consecutive Prime Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3651

[PDF](https://uva.onlinejudge.org/external/12/p1210.pdf)



---



---

# 题号列表

- UVA108 - Maximum Sum
- UVA1210 - 连续素数之和 Sum of Consecutive Prime Numbers


---

---
title: "带宽 Bandwidth"
layout: "post"
diff: 普及/提高-
pid: UVA140
tag: ['枚举', '剪枝']
---

# 带宽 Bandwidth

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=76

[PDF](https://uva.onlinejudge.org/external/1/p140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/c28a82a576401d68954e54e49ebe92f369cda3c9.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/b1e8ffcfe78f638ef691e846732af5db87cfed53.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/a04c7e0220dc363f6a9b2b8414dfbfd573ebaa94.png)

## 样例 #1

### 输入

```
A:FB;B:GC;D:GC;F:AGH;E:HD
#
```

### 输出

```
A B C F G D H E -&gt; 3
```



---



---

# 题号列表

- UVA140 - 带宽 Bandwidth


---

---
title: "唯一的雪花 Unique Snowflakes"
layout: "post"
diff: 普及/提高-
pid: UVA11572
tag: ['枚举', '哈希 hashing', '双指针 two-pointer']
---

# 唯一的雪花 Unique Snowflakes

## 题目描述

企业家 Emily 有一个很酷的主意：把雪花包起来卖。她发明了一台机器，这台机器可以捕捉飘落的雪花，并把它们一片一片打包进一个包裹里。一旦这个包裹满了，它就会被封上送去发售。

Emily 的公司的口号是“把独特打包起来”，为了实现这一诺言，一个包裹里不能有两片一样的雪花。不幸的是，这并不容易做到，因为实际上通过机器的雪花中有很多是相同的。Emily 想知道这样一个不包含两片一样的雪花的包裹最大能有多大，她可以在任何时候启动机器，但是一旦机器启动了，直到包裹被封上为止，所有通过机器的雪花都必须被打包进这个包裹里，当然，包裹可以在任何时候被封上。

## 输入格式

第一行是测试数据组数 $T$，对于每一组数据，第一行是通过机器的雪花总数 $n$（$n \le {10}^6$），下面 $n$ 行每行一个在 $[0, {10}^9]$ 内的整数，标记了这片雪花，当两片雪花标记相同时，这两片雪花是一样的。

## 输出格式

对于每一组数据，输出最大包裹的大小。

## 样例 #1

### 输入

```
1
5
1
2
3
2
1
```

### 输出

```
3
```



---



---

# 题号列表

- UVA11572 - 唯一的雪花 Unique Snowflakes


---

---
title: "Dominos 2"
layout: "post"
diff: 普及/提高-
pid: UVA11518
tag: ['搜索', '图论']
---

# Dominos 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2513

[PDF](https://uva.onlinejudge.org/external/115/p11518.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/7f28ab761227ecc0796512e3a227ad6b7d28229e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/358c7d33d629af402b53bf37fed925488939a6c1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/66db10874dbf273f4e15346e2df8aeb00eddd6c8.png)

## 样例 #1

### 输入

```
1
3 2 1
1 2
2 3
2
```

### 输出

```
2
```



---



---

# 题号列表

- UVA11518 - Dominos 2


---

---
title: "Generating Fast"
layout: "post"
diff: 普及/提高-
pid: UVA10098
tag: ['字符串', '置换']
---

# Generating Fast

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=1039

[PDF](https://uva.onlinejudge.org/external/100/p10098.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10098/f90ae2e6e97ea26dff771e444046ad7a5afbfd41.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10098/0957311e3dd3d7af39f6eb9c8bd1e5fe9d887dd1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10098/2eec7cf1f33dbaf3cccbe2fafc1d57c0b13a3a08.png)

## 样例 #1

### 输入

```
3
ab
abc
bca
```

### 输出

```
ab
ba

abc
acb
bac
bca
cab
cba

abc
acb
bac
bca
cab
cba
```



---

---
title: "Ecological Bin Packing"
layout: "post"
diff: 普及/提高-
pid: UVA102
tag: ['字符串', '枚举', '深度优先搜索 DFS']
---

# Ecological Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

[PDF](https://uva.onlinejudge.org/external/1/p102.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ef84892469f793327bfb4a3ea04e4237b1761a6d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ae3b90e524e6ffd7e27eab05a64abfd8be7111ef.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/249702f9f5f1e91446cb32d9b3ad6a7eca7264f5.png)

## 样例 #1

### 输入

```
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10
```

### 输出

```
BCG 30
CBG 50
```



---

---
title: "最长的滑雪路径 Longest Run on a Snowboard"
layout: "post"
diff: 普及/提高-
pid: UVA10285
tag: ['字符串', '搜索', '记忆化搜索']
---

# 最长的滑雪路径 Longest Run on a Snowboard

## 题目描述

$ben$喜欢滑雪。（以下简叙）在一个$R*C(R,C\leq100)$的整数矩阵上找一条高度严格递减的最长路。起点任意，但每次只能沿着上下左右$4$个方向之一走一格，并且不能走出矩阵外。如图所示，最长路是按照高度$25,24,23,...,2,1$这样走，长度为$25$。矩阵中的数均为$0$~$100$.

## 输入格式

有多组数据。

第一行为一个整数$N$，表示数据组数。
对于每组数据，第一行包括一个字符串和两个整数$R,C$，为此滑雪者的姓名和矩阵的长宽。

## 输出格式

对于每组数据，输出一行，格式为：
``name: answer``

$name$为当前数据的滑雪者姓名，$answer$为你的答案。

## 样例 #1

### 输入

```
2
Feldberg 10 5
56 14 51 58 88
26 94 24 39 41
24 16 8 51 51
76 72 77 43 10
38 50 59 84 81
5 23 37 71 77
96 10 93 53 82
94 15 96 69 9
74 0 62 38 96
37 54 55 82 38
Spiral 5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
```

### 输出

```
Feldberg: 7
Spiral: 25
```



---

---
title: "复合词 Compound Words"
layout: "post"
diff: 普及/提高-
pid: UVA10391
tag: ['字符串']
---

# 复合词 Compound Words

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1332

[PDF](https://uva.onlinejudge.org/external/103/p10391.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10391/c08e8f7cb6ab0d8672dfe8d32dd1d605dbe69332.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10391/ec41c801b6c4829e139f94fcb9387752bd4f1d50.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10391/229bba2a86ce98680bf997a6a7d7de2f40571d54.png)

## 样例 #1

### 输入

```
a
alien
born
less
lien
never
nevertheless
new
newborn
the
zebra
```

### 输出

```
alien
newborn
```



---

---
title: "安迪的第一个字典 Andy's First Dictionary"
layout: "post"
diff: 普及/提高-
pid: UVA10815
tag: ['模拟', '字符串', '排序']
---

# 安迪的第一个字典 Andy's First Dictionary

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1756

[PDF](https://uva.onlinejudge.org/external/108/p10815.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/4f5c1d24c1c6cb6c76b70bd32c63daec8b95b2f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/03acce165b96154650f2620dd40e5c6d60bd1a9f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/a4a74f8b6cd346abca8f4ccf0d50b25e34c0aba2.png)

## 样例 #1

### 输入

```
Adventures in Disneyland
Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."
So they went home.
```

### 输出

```
a
adventures
blondes
came
disneyland
fork
going
home
in
left
read
road
sign
so
the
they
to
two
went
were
when
```



---

---
title: "Chinese Mahjong"
layout: "post"
diff: 普及/提高-
pid: UVA11210
tag: ['模拟', '字符串', '搜索', '枚举']
---

# Chinese Mahjong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2151

[PDF](https://uva.onlinejudge.org/external/112/p11210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/00db9c6ee014cb07d2ff71e0aff3d224225bbbd1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/1402d96f2257d9e8bce6c1fccdee577f9b27804e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/0cc0c231da6a95552468965d5df9b75080e2ca2a.png)

## 样例 #1

### 输入

```
1S 1S 2S 2S 2S 3S 3S 3S 7S 8S 9S FA FA
1S 2S 3S 4S 5S 6S 7S 8S 9S 1T 3T 5T 7T
0
```

### 输出

```
Case 1: 1S 4S FA
Case 2: Not ready
```



---

---
title: "Phone List"
layout: "post"
diff: 普及/提高-
pid: UVA11362
tag: ['字符串', '字典树 Trie']
---

# Phone List

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=25&page=show_problem&problem=2347

[PDF](https://uva.onlinejudge.org/external/113/p11362.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/86a9ad22547794c86c707c6301a3959ca76cfd43.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/d5bf45fcc4bdcc7e676e655a36dda7a794b189af.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11362/da40d07a03794e91297b87d8a38934cf0ee2e2e4.png)

## 样例 #1

### 输入

```
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346
```

### 输出

```
NO
YES
```



---

---
title: "The Errant Physicist"
layout: "post"
diff: 普及/提高-
pid: UVA126
tag: ['模拟', '字符串']
---

# The Errant Physicist

## 题目描述

著名物理学家阿尔弗雷德·E·纽曼正在研究涉及多项式乘法的问题。例如，他可能需要计算
$$
(-x^8y+9x^3-1+y) \cdot (x^5y+1+x^3)
$$
得到答案
$$
-x^{13}y^2-x^{11}y+8x^8y+9x^6-x^5y+x^5y^2+8x^3+x^3y-1+y
$$
不幸的是，这些问题太微不足道了，以至于这位伟人的思绪总是游离在工作之外，他得到了错误的答案。因此，他设计的几枚核弹头过早引爆，摧毁了五个主要城市和几片雨林。
你要写一个程序来执行这样的乘法并拯救世界。

## 输入格式

输入数据文件有若干个测试数据，每个测试数据有两行，每行包含的字符不超过 $80$ 个。输入文件的最后一行包含一个`#`作为其第一个字符。

每行输入都包含一个多项式，该多项式没有空格，也没有任何显式的求幂运算符。指数是正的非零无符号整数。系数也是整数，但也可以是负数。指数和系数的大小都小于或等于 $100$。每个项最多包含一个 $x$ 因子和一个 $y$ 因子。

## 输出格式

您的程序必须将输入中的每对多项式相乘，并在一对上打印每个乘积行，第一行包含所有指数，相对于其余行适当定位信息，在下面的行中。

1. 输出行中的项必须按 $x$ 的幂次降序排列，对于给定的幂次按照 $y$ 的幂次升序排序。

2. 可以被化简的单项式必须化简。例如，$40x^2y^3-38x^2y^3$ 被替换为 $2x^2y^3$。

3. 不得显示系数为零的单项式。

4. 除常数项为 $1$ 的情况外，系数 $1$ 被省略。

5. 省略指数 $1$。

6. 省略 $x^0$ 和 $y^0$ 的因子。

7. 二进制正负（即输出中连接项的正负）前后都有一个空格。

8. 如果第一项的系数为负，则在第一列中以一元减号开头，中间没有空格。否则，系数本身从第一个输出开始列。

9. 可以假设输出长度最多为 $80$ 个字符。

10. 每对输出行之间不应有空白行。

11. 一对行的长度应该相同——为了实现这一点，尾随空格应该出现在较短行的最后一个非空白字符之后。

## 样例 #1

### 输入

```
-yx8+9x3-1+y
x5y+1+x3
1
1
#
```

### 输出

```
13 2 11
8
6 5
5 2
3 3
-x y - x y + 8x y + 9x - x y + x y + 8x + x y - 1 + y
1
```



---

---
title: "Software CRC"
layout: "post"
diff: 普及/提高-
pid: UVA128
tag: ['字符串', '递推', '进制']
---

# Software CRC

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=64

[PDF](https://uva.onlinejudge.org/external/1/p128.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/2ed0a2961b881ebefab6464e3345553e002df0c8.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/bfbdaaa48bb848a17ac2a5ab1bcae82f4ecb4334.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/48234fb6a73fd634750ac85257ec7843b5e06d8d.png)

## 样例 #1

### 输入

```
this is a test
A
#
```

### 输出

```
77 FD
00 00
0C 86
```



---

---
title: "ID Codes"
layout: "post"
diff: 普及/提高-
pid: UVA146
tag: ['字符串', '排序']
---

# ID Codes

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=82

[PDF](https://uva.onlinejudge.org/external/1/p146.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/0a26c57498e3107538df966221b8da23281e007c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/3e254f4c8a187037e7d61d92007343a3eebe415c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/c93af7b124b8d27efecfc989ed2cb65fbb7f4644.png)

## 样例 #1

### 输入

```
abaacb
cbbaa
#
```

### 输出

```
ababac
No Successor
```



---

---
title: "反片语 Ananagrams"
layout: "post"
diff: 普及/提高-
pid: UVA156
tag: ['字符串', '排序', '概率论']
---

# 反片语 Ananagrams

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=92

[PDF](https://uva.onlinejudge.org/external/1/p156.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/dc6cdcbb36579acf2629ae204167ab408bdaa20f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/ec895ca45b112623bf0e495312ef5805c9c5a222.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/46b34b0a4275c645ab84982aea6e74168eb7cdb4.png)

## 样例 #1

### 输入

```
ladder came tape soon leader acme RIDE lone Dreis peat
ScAlE orb eye Rides dealer NotE derail LaCeS drIed
noel dire Disk mace Rob dries
#
```

### 输出

```
Disk
NotE
derail
drIed
eye
ladder
soon
```



---

---
title: "数据库 Database"
layout: "post"
diff: 普及/提高-
pid: UVA1592
tag: ['字符串', '枚举', '进制']
---

# 数据库 Database

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4467

[PDF](https://uva.onlinejudge.org/external/15/p1592.pdf)



---

---
title: "决斗 Headshot"
layout: "post"
diff: 普及/提高-
pid: UVA1636
tag: ['字符串', '条件概率']
---

# 决斗 Headshot

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4511

[PDF](https://uva.onlinejudge.org/external/16/p1636.pdf)



---

---
title: "信息解码 Message Decoding"
layout: "post"
diff: 普及/提高-
pid: UVA213
tag: ['模拟', '字符串', '进制']
---

# 信息解码 Message Decoding

## 题目描述

考虑下面的01串序列：
```
0，00，01，10，000，001，010，011，100，101，110，0000，0001，···，1101，1110，00000，···
```
首先是长度为1的串，然后是长度为2的串，依此类推。如果看成二进制，相同长度的后一个串等于前一个串加1。注意上述序列中不存在全为1的串。你的任务是是编写一个解码程序。

## 输出格式

感谢@hedwig 提供的翻译

## 样例 #1

### 输入

```
TNM AEIOU 
0010101100011 
1010001001110110011 
11000 
$#**\ 
0100000101101100011100101000
```

### 输出

```
TAN ME 
##*\$
```



---

---
title: "谜题 Puzzle"
layout: "post"
diff: 普及/提高-
pid: UVA227
tag: ['模拟', '字符串', '枚举']
---

# 谜题 Puzzle

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=163

[PDF](https://uva.onlinejudge.org/external/2/p227.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/952149a2874e339bbc22a79a1cd1d063e89e1421.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/e230761e1328196764fb5b28ac3d84ef407e0b7e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/30096ab22228859e28141b62fe1f49b2628b66bb.png)

## 样例 #1

### 输入

```
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAAAABBRRRLL0
Z
```

### 输出

```
Puzzle #1:
T R G S J
X O K L I
M D V B N
W P   A E
U Q H C F

Puzzle #2:
  A B C D
F G H I E
K L M N J
P Q R S O
T U V W X

Puzzle #3:
This puzzle has no final configuration.
```



---

---
title: "Integer Inquiry"
layout: "post"
diff: 普及/提高-
pid: UVA424
tag: ['字符串', '高精度']
---

# Integer Inquiry

## 题目描述

BIT 的新超级计算机的第一批用户之一是 Chip Diller。他将他对 $3$ 的幂的探索扩展到了从 $0$ 到 $333$ 的范围，并研究了这些数字的各种和。

“这台超级计算机真棒，”Chip 说。“我只希望 Timothy 能在这里看到这些结果。”

（Chip 搬到了一个新公寓，一旦第三街 Lemon Sky 公寓三楼有空房，他就搬了进去。）

## 输入格式

输入最多包含 $100$ 行文本，每行包含一个非常大的整数。每个非常大的整数的长度不超过 $100$ 个字符，并且只包含数字（不会有负数）。

最后一行输入将仅包含一个单独的零。

## 输出格式

你的程序应该输出输入中给出的非常大的整数之和。

---

Translated by User 735713.

## 样例 #1

### 输入

```
123456789012345678901234567890
123456789012345678901234567890
123456789012345678901234567890
0
```

### 输出

```
370370367037037036703703703670
```



---

---
title: "矩阵链乘 Matrix Chain Multiplication"
layout: "post"
diff: 普及/提高-
pid: UVA442
tag: ['字符串', '栈', '构造']
---

# 矩阵链乘 Matrix Chain Multiplication

## 题目描述

## 矩阵链乘


​  假设你必须评估一种表达形如 A*B*C*D*E，其中 A,B,C,D,E是矩阵。既然矩阵乘法是关联的，那么乘法的顺序是任意的。然而，链乘的元素数量必须由你选择的赋值顺序决定。

​  例如，A，B，C分别是 50 * 10 ，10 * 20 和 20 * 5 的矩阵。现在有两种方案计算 A * B * C ,即（A * B) * C 和 A*(B * C)。  
   第一个要进行15000次基本乘法，而第二个只进行3500次。

​  你的任务就是写出一个程序判定以给定的方式相乘需要多少次基本乘法计算。

## 输入格式

​  输入包含两个部分：矩阵和表达式。 
   输入文件的第一行包含了一个整数 n(1  $\leq$  n  $\leq$  26), 代表矩阵的个数。接下来的n行每一行都包含了一个大写字母，说明矩阵的名称，以及两个整数，说明行与列的个数。  
   第二个部分严格遵守以下的语法：

SecondPart = Line {  Line  } <EOF>
Line       = Expression <CR>
Expression = Matrix | "(" Expression Expression ")"
Matrix     = "A" | "B" | "C" | ... | "X" | "Y" | "Z"

## 输出格式

​  对于每一个表达式，如果乘法无法进行就输出 " error "。否则就输出一行包含计算所需的乘法次数。 

感谢@onceagain 提供翻译

## 样例 #1

### 输入

```
9
A 50 10
B 10 20
C 20 5
D 30 35
E 35 15
F 15 5
G 5 10
H 10 20
I 20 25
A
B
C
(AA)
(AB)
(AC)
(A(BC))
((AB)C)
(((((DE)F)G)H)I)
(D(E(F(G(HI)))))
((D(EF))((GH)I))
```

### 输出

```
0
0
0
error
10000
error
3500
15000
40500
47500
15125
```



---



---

# 题号列表

- UVA10098 - Generating Fast
- UVA102 - Ecological Bin Packing
- UVA10285 - 最长的滑雪路径 Longest Run on a Snowboard
- UVA10391 - 复合词 Compound Words
- UVA10815 - 安迪的第一个字典 Andy's First Dictionary
- UVA11210 - Chinese Mahjong
- UVA11362 - Phone List
- UVA126 - The Errant Physicist
- UVA128 - Software CRC
- UVA146 - ID Codes
- UVA156 - 反片语 Ananagrams
- UVA1592 - 数据库 Database
- UVA1636 - 决斗 Headshot
- UVA213 - 信息解码 Message Decoding
- UVA227 - 谜题 Puzzle
- UVA424 - Integer Inquiry
- UVA442 - 矩阵链乘 Matrix Chain Multiplication


---

---
title: "Arctic Network"
layout: "post"
diff: 普及/提高-
pid: UVA10369
tag: ['并查集', '生成树']
---

# Arctic Network

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1310

[PDF](https://uva.onlinejudge.org/external/103/p10369.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/b3c41b35e81b308ad9ef5826dfa39b5f526836c1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/1fed2f028e09206e67a50d94d47eca7ea0360586.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/08973cd15c06ad71bc58f70cc9dd85f12476e242.png)

## 样例 #1

### 输入

```
1
2 4
0 100
0 300
0 600
150 750
```

### 输出

```
212.13
```



---

---
title: "Ubiquitous Religions"
layout: "post"
diff: 普及/提高-
pid: UVA10583
tag: ['并查集']
---

# Ubiquitous Religions

## 题目描述

### 题目简述

有一个 $n$ 个点，$m$ 条边的无向图，求这个图有多少个连通块。

## 输入格式

**本题多组数据**。

每组数据的第一行为 $n$ 和 $m$。

接下来 $m$ 行，每一行两个值 $x,y$，描述一条由 $x$ 到 $y$ 的无向边。

输入的结束为 $0\ 0$。

## 输出格式

对于每一组数据，输出一行 `Case i: ans`，其中 $i$ 表示目前是第 $i$ 组数据，$ans$ 表示第 $i$ 组数据的图的连通块个数。

## 说明/提示

$0<n\le 5\times 10^4$，$0\le m\le \frac{n\times (n-1)}{2}$。

## 样例 #1

### 输入

```
10 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
10 4
2 3
4 5
4 8
5 8
0 0
```

### 输出

```
Case 1: 1
Case 2: 7
```



---

---
title: "Friends"
layout: "post"
diff: 普及/提高-
pid: UVA10608
tag: ['并查集']
---

# Friends

## 题目描述

某个小镇里有 $N$ 个位公民，其中有些人是朋友关系。

在这个小镇里，“我的朋友的朋友是我的朋友”是一条不变的真理，即如果 $A$ 和 $B$ 是朋友，$B$ 和 $C$ 是朋友，那么 $A$ 和 $C$ 也是朋友。

由于镇里的朋友太多，形成了几个朋友团（在任何一个朋友团里的人都是朋友，而任意两个不相同朋友团的人不是朋友）。你想知道镇里最大的朋友团里有多少位公民。

## 输入格式

**本题有多组数据。**

第一行一个正整数 $T$，代表数据组数，保证为 `int` 范围。

接下来对于每一组数据：

第一行两个数 $N$ 和 $M$，$N$ 代表公民数，$M$ 代表朋友的对数。

接下来 $M$ 行，每行两个整数 $A$ 和 $B$，代表居民 $A$ 和居民 $B$ 是朋友。保证 $A$ 和 $B$ 均小于 $N$ 且不相等，但可能会出现重复的数据。

## 输出格式

对于每组数据，输出一行一个整数，代表镇里最大的朋友团里的公民数量。

## 说明/提示

$1 \leq N \leq 3 \times 10^4$，$0 \leq M \leq 5 \times 10^5$。

## 样例 #1

### 输入

```
2
3 2
1 2
2 3
10 12
1 2
3 1
3 4
5 4
3 5
4 6
5 2
2 1
7 1
1 2
9 10
8 9
```

### 输出

```
3
7
```



---

---
title: "Virtual Friends"
layout: "post"
diff: 普及/提高-
pid: UVA11503
tag: ['并查集']
---

# Virtual Friends

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2498

[PDF](https://uva.onlinejudge.org/external/115/p11503.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11503/22196a0b85da544cbb9282738f8363a33f28edf0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11503/5479c9917ca9cf83bc83862301aa2ef7e5bbb237.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11503/58fa3ef5d9c7e6c8d8b6764d58b1bace8a90d1ac.png)

## 样例 #1

### 输入

```
1
3
Fred Barney
Barney Betty
Betty Wilma
```

### 输出

```
2
3
4
```



---

---
title: "The Suspects"
layout: "post"
diff: 普及/提高-
pid: UVA1197
tag: ['并查集']
---

# The Suspects

## 题目描述

在一所大学里有 $n$ 个学生（这些学生的编号为 $0\sim  n-1$）。这些学生由于兴趣爱好等原因组成了 $m$ 个群体。

由于非典（$\mathrm{SARS}$）流行，该大学的学生会需要排除可能的非典患者。

由于非典传染性强，学生会的成员假定：如果一个群体中有一个人是非典患者，那么这个群体中的所有人都是非典患者。

现在已知编号为 $0$ 的学生为非典患者。请你找出这些学生中非典患者的人数。

## 输入格式

输入数据由多组数据组成。

每组数据包括$m+1$行：

第$1$行有两个由空格隔开的非负整数$n$和$m$，其意义如题目所述。

第$2\sim m+1$行表示每个群体的人员信息，每行的第一个数字$k$表示该群体的人数，其后有$k$个用空格隔开的非负整数，表示这个群体的各个成员的编号。

当$n=m=0$时，表示输入结束，不需要处理之后的数据。

## 输出格式

对于每组输入数据，输出一个整数，表示这组数据中非典患者的数量。每组数据的输出以换行符结尾。

## 输入输出样例

### 样例输入：
```
100 4
2 1 2
5 10 13 11 12 14
2 0 1
2 99 2
200 2
1 5
5 1 2 3 4 5
1 0
0 0
```

### 样例输出：
```
4
1
1
```



---



---

# 题号列表

- UVA10369 - Arctic Network
- UVA10583 - Ubiquitous Religions
- UVA10608 - Friends
- UVA11503 - Virtual Friends
- UVA1197 - The Suspects


---

---
title: "Commandos"
layout: "post"
diff: 普及/提高-
pid: UVA11463
tag: ['广度优先搜索 BFS', '最短路']
---

# Commandos

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2458

[PDF](https://uva.onlinejudge.org/external/114/p11463.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6db49602a4d25da560ee412c34699e1614bef1f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6dd5f0f8ad77e22ca50b6445d392ed09627aa84c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/f01cfb1355e55dd1b4f293845dd5f685541a310d.png)

## 样例 #1

### 输入

```
2
4
3
0 1
2 1
1 3
0 3
2
1
0 1
1 0
```

### 输出

```
Case 1: 4
Case 2: 1
```



---

---
title: "骑士的移动 Knight Moves"
layout: "post"
diff: 普及/提高-
pid: UVA439
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# 骑士的移动 Knight Moves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=380

[PDF](https://uva.onlinejudge.org/external/4/p439.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/49281f2a839995de267463a506fc7b04652bcf4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/f986ca9c080d4c2fa5952f61f878eaafe27fdf4b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/e3265edbb46489790ff00e32193564840a6de7fe.png)

## 样例 #1

### 输入

```
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
```

### 输出

```
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.
```



---

---
title: "Dungeon Master"
layout: "post"
diff: 普及/提高-
pid: UVA532
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# Dungeon Master

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=473

[PDF](https://uva.onlinejudge.org/external/5/p532.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/f5204064f9aec4c41d412eb29fbc006dac1f717c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/bc032dafb23822eecdf0192d86ea58ddcaa98ec5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/30d36b3bfe984f90284eb870b4006708e8229767.png)

## 样例 #1

### 输入

```
3 4 5
S....
.###.
.##..
###.#
#####
#####
##.##
##...
#####
#####
#.###
####E
1 3 3
S##
#E#
###
0 0 0
```

### 输出

```
Escaped in 11 minute(s).
Trapped!
```



---



---

# 题号列表

- UVA11463 - Commandos
- UVA439 - 骑士的移动 Knight Moves
- UVA532 - Dungeon Master


---

---
title: "Shoemaker's Problem"
layout: "post"
diff: 普及/提高-
pid: UVA10026
tag: ['贪心', '排序']
---

# Shoemaker's Problem

## 题目描述

有 $n$ 个任务，每个任务从接手开始每分钟罚款 $S_i$ 元，直到完成任务为止。然而每个任务需要花 $T_i$ 的时间去完成。你只能把一件任务完成才能去做下一件事情，问如何安排任务处理顺序，使得总罚款最小。注意，每个任务在第 $0$ 时刻就全部交给了你。

## 输入格式

第一行一个整数 $T$，表示多组测试数据数量。

对于每组数据，一个整数 $n$ 表示任务数量，接下来 $n$ 行每行两个整数 $T_i$ 和 $S_i$。

## 输出格式

每个多组数据，输出对应的安排顺序，若存在多种方案，请输出字典序最小的一个。

**注意相邻两个多组测试点中间需要隔一个空行**

## 样例 #1

### 输入

```
1
4
3 4
1 1000
2 2
5 5
```

### 输出

```
2 1 3 4
```



---

---
title: "给任务排序 Ordering Tasks"
layout: "post"
diff: 普及/提高-
pid: UVA10305
tag: ['排序', '拓扑排序']
---

# 给任务排序 Ordering Tasks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1246

[PDF](https://uva.onlinejudge.org/external/103/p10305.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10305/62db82e05a53c8fcb4628f932e511aa228649ae7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10305/f94e7802ecac0d2a2ffcf48a4e2568b6608cf4c2.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10305/f488d842d5a4387004559040947dd79465dbd850.png)

## 样例 #1

### 输入

```
5 4
1 2
2 3
1 3
1 5
0 0
```

### 输出

```
1 4 2 5 3
```



---

---
title: "Ultra-QuickSort"
layout: "post"
diff: 普及/提高-
pid: UVA10810
tag: ['树状数组', '排序']
---

# Ultra-QuickSort

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1751

[PDF](https://uva.onlinejudge.org/external/108/p10810.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/751b373c4650fd9cb6ed8962c612343e8c3faf34.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/bbac08e36c21bfb711cef255cbd33a4aba31f921.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/07aa3a0e09920ab537e7e75fdd2f783aadf38833.png)

## 样例 #1

### 输入

```
5
9
1
0
5
4
3
1
2
3
0
```

### 输出

```
6
0
```



---

---
title: "安迪的第一个字典 Andy's First Dictionary"
layout: "post"
diff: 普及/提高-
pid: UVA10815
tag: ['模拟', '字符串', '排序']
---

# 安迪的第一个字典 Andy's First Dictionary

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1756

[PDF](https://uva.onlinejudge.org/external/108/p10815.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/4f5c1d24c1c6cb6c76b70bd32c63daec8b95b2f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/03acce165b96154650f2620dd40e5c6d60bd1a9f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/a4a74f8b6cd346abca8f4ccf0d50b25e34c0aba2.png)

## 样例 #1

### 输入

```
Adventures in Disneyland
Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."
So they went home.
```

### 输出

```
a
adventures
blondes
came
disneyland
fork
going
home
in
left
read
road
sign
so
the
they
to
two
went
were
when
```



---

---
title: "Radar Installation"
layout: "post"
diff: 普及/提高-
pid: UVA1193
tag: ['贪心', '排序', '优先队列']
---

# Radar Installation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3634

[PDF](https://uva.onlinejudge.org/external/11/p1193.pdf)

## 样例 #1

### 输入

```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---

---
title: "ID Codes"
layout: "post"
diff: 普及/提高-
pid: UVA146
tag: ['字符串', '排序']
---

# ID Codes

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=82

[PDF](https://uva.onlinejudge.org/external/1/p146.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/0a26c57498e3107538df966221b8da23281e007c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/3e254f4c8a187037e7d61d92007343a3eebe415c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA146/c93af7b124b8d27efecfc989ed2cb65fbb7f4644.png)

## 样例 #1

### 输入

```
abaacb
cbbaa
#
```

### 输出

```
ababac
No Successor
```



---

---
title: "反片语 Ananagrams"
layout: "post"
diff: 普及/提高-
pid: UVA156
tag: ['字符串', '排序', '概率论']
---

# 反片语 Ananagrams

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=92

[PDF](https://uva.onlinejudge.org/external/1/p156.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/dc6cdcbb36579acf2629ae204167ab408bdaa20f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/ec895ca45b112623bf0e495312ef5805c9c5a222.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/46b34b0a4275c645ab84982aea6e74168eb7cdb4.png)

## 样例 #1

### 输入

```
ladder came tape soon leader acme RIDE lone Dreis peat
ScAlE orb eye Rides dealer NotE derail LaCeS drIed
noel dire Disk mace Rob dries
#
```

### 输出

```
Disk
NotE
derail
drIed
eye
ladder
soon
```



---

---
title: "图书管理系统 Borrowers"
layout: "post"
diff: 普及/提高-
pid: UVA230
tag: ['排序']
---

# 图书管理系统 Borrowers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=166

[PDF](https://uva.onlinejudge.org/external/2/p230.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA230/080bb4c03724a95130bfbcbf99ca56637343b6dc.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA230/09a2dbdba94471eaf8b74e77ff5188cc2fa76b1a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA230/eea5cbbfe48805b94128530790d4e152ce9ed9a8.png)

## 样例 #1

### 输入

```
"The Canterbury Tales" by Chaucer, G.
"Algorithms" by Sedgewick, R.
"The C Programming Language" by Kernighan, B. and Ritchie, D.
END
BORROW "Algorithms"
BORROW "The C Programming Language"
RETURN "Algorithms"
RETURN "The C Programming Language"
SHELVE
END
```

### 输出

```
Put "The C Programming Language" after "The Canterbury Tales"
Put "Algorithms" after "The C Programming Language"
END
```



---

---
title: "Bridge Hands"
layout: "post"
diff: 普及/提高-
pid: UVA555
tag: ['模拟', '排序']
---

# Bridge Hands

## 题目描述

一副扑克牌，除去大小王后还有 $52$ 张。

我们定义扑克牌的大小比较为：

如果花色不同，则梅花 $<$ 方块 $<$ 黑桃 $<$ 红桃。

此处，我们将梅花写作 $\text{C}$，方块写作 $\text{D}$，黑桃写作 $\text{S}$，红桃写作 $\text{H}$。

如果花色相同，则 $2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < \text{J} < \text{Q} < \text{K} < \text{A}$。

此处我们将 $10$ 写作 $\text{T}$，$\text{J}$、$\text{Q}$、$\text{K}$、$\text{A}$保持原来的写法。

一张牌由其花色和牌点组成，即，红桃 $10$ 被我们表示成 $\text{HT}$，黑桃 $4$ 被我们表示成 $\text{S4}$，以此类推。

注意，以上有涉及到字母的均为大写字母。

现在有一种四个人的游戏是用一副去掉大小王后的扑克牌玩的。四个人分别被表示成南，西，北，东。每一轮都有一个庄家，发牌时从庄家的顺时针方向下一位选手开始发牌，然后按顺时针发牌直至牌被发光，此时每个人手里的牌数相同，为 $13$ 张。

此处默认：南的顺时针方向一位是西，西的顺时针方向一位是北，北的顺时针方向一位是东，东的顺时针方向一位是南。南、西、北、东分别用 $\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 来表示。

现在给定牌堆和庄家，请求出每位玩家的手牌**排序后**的结果。排序方法参照上部。

## 输入格式

**本题多测。**

对于每组数据，第一行一个字符 $c$，代表庄家。$c$ 只能是$\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 或 $#$。当输入到 $#$ 时结束程序。

接下来**两行两个**字符串，代表牌堆。注意，每**两个字符**代表一张牌。上面一行的牌堆会比下面一行的牌堆先被发出。

## 输出格式

对于每组数据，按照 $\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 的顺序输出，一行一位选手。对于每一行输出形如 `c: a[1] a[2] a[3] a[4] a[5] a[6] a[7] a[8] a[9] a[10] a[11] a[12] a[13]`，其中 $c$ 代表选手，$a_i$ 代表该选手**排序后的**第 $i$ 张牌。

## 样例 #1

### 输入

```
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#
```

### 输出

```
S: C3 C5 C7 CT CJ D9 DT DJ S3 SK H2 H9 HT
W: C2 C4 CK D4 D5 D6 DQ DA S4 S8 ST SJ H8
N: C6 C8 C9 CA D8 S9 SA H4 H5 H6 H7 HJ HA
E: CQ D2 D3 D7 DK S2 S5 S6 S7 SQ H3 HQ HK
```



---



---

# 题号列表

- UVA10026 - Shoemaker's Problem
- UVA10305 - 给任务排序 Ordering Tasks
- UVA10810 - Ultra-QuickSort
- UVA10815 - 安迪的第一个字典 Andy's First Dictionary
- UVA1193 - Radar Installation
- UVA146 - ID Codes
- UVA156 - 反片语 Ananagrams
- UVA230 - 图书管理系统 Borrowers
- UVA555 - Bridge Hands


---

---
title: "Ecological Bin Packing"
layout: "post"
diff: 普及/提高-
pid: UVA102
tag: ['字符串', '枚举', '深度优先搜索 DFS']
---

# Ecological Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

[PDF](https://uva.onlinejudge.org/external/1/p102.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ef84892469f793327bfb4a3ea04e4237b1761a6d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ae3b90e524e6ffd7e27eab05a64abfd8be7111ef.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/249702f9f5f1e91446cb32d9b3ad6a7eca7264f5.png)

## 样例 #1

### 输入

```
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10
```

### 输出

```
BCG 30
CBG 50
```



---

---
title: "最长的滑雪路径 Longest Run on a Snowboard"
layout: "post"
diff: 普及/提高-
pid: UVA10285
tag: ['字符串', '搜索', '记忆化搜索']
---

# 最长的滑雪路径 Longest Run on a Snowboard

## 题目描述

$ben$喜欢滑雪。（以下简叙）在一个$R*C(R,C\leq100)$的整数矩阵上找一条高度严格递减的最长路。起点任意，但每次只能沿着上下左右$4$个方向之一走一格，并且不能走出矩阵外。如图所示，最长路是按照高度$25,24,23,...,2,1$这样走，长度为$25$。矩阵中的数均为$0$~$100$.

## 输入格式

有多组数据。

第一行为一个整数$N$，表示数据组数。
对于每组数据，第一行包括一个字符串和两个整数$R,C$，为此滑雪者的姓名和矩阵的长宽。

## 输出格式

对于每组数据，输出一行，格式为：
``name: answer``

$name$为当前数据的滑雪者姓名，$answer$为你的答案。

## 样例 #1

### 输入

```
2
Feldberg 10 5
56 14 51 58 88
26 94 24 39 41
24 16 8 51 51
76 72 77 43 10
38 50 59 84 81
5 23 37 71 77
96 10 93 53 82
94 15 96 69 9
74 0 62 38 96
37 54 55 82 38
Spiral 5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
```

### 输出

```
Feldberg: 7
Spiral: 25
```



---

---
title: "Square"
layout: "post"
diff: 普及/提高-
pid: UVA10364
tag: ['深度优先搜索 DFS']
---

# Square

## 题目描述

给定 $N$ 根木棍，每根木棍的长度为 $x$ 。

尝试用所有的木棍围成一个正方形。

## 输入格式

第一行输入一个整数 $T$，代表 $T$ 组数据。

接下来 $T$ 行，每行开头输入一个整数 $N$，即有 $N$ 根木棍，接着输入 $N$ 个整数代表每根木棍的长度。

## 输出格式

$T$ 行，每行输出一个字符串，若能围成正方形，输出 ``yes``，否则输出 ``no``。

## 样例 #1

### 输入

```
3
4 1 1 1 1
5 10 20 30 40 50
8 1 7 2 6 4 4 3 5
```

### 输出

```
yes
no
yes
```



---

---
title: "Chinese Mahjong"
layout: "post"
diff: 普及/提高-
pid: UVA11210
tag: ['模拟', '字符串', '搜索', '枚举']
---

# Chinese Mahjong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2151

[PDF](https://uva.onlinejudge.org/external/112/p11210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/00db9c6ee014cb07d2ff71e0aff3d224225bbbd1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/1402d96f2257d9e8bce6c1fccdee577f9b27804e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/0cc0c231da6a95552468965d5df9b75080e2ca2a.png)

## 样例 #1

### 输入

```
1S 1S 2S 2S 2S 3S 3S 3S 7S 8S 9S FA FA
1S 2S 3S 4S 5S 6S 7S 8S 9S 1T 3T 5T 7T
0
```

### 输出

```
Case 1: 1S 4S FA
Case 2: Not ready
```



---

---
title: "Commandos"
layout: "post"
diff: 普及/提高-
pid: UVA11463
tag: ['广度优先搜索 BFS', '最短路']
---

# Commandos

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2458

[PDF](https://uva.onlinejudge.org/external/114/p11463.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6db49602a4d25da560ee412c34699e1614bef1f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6dd5f0f8ad77e22ca50b6445d392ed09627aa84c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/f01cfb1355e55dd1b4f293845dd5f685541a310d.png)

## 样例 #1

### 输入

```
2
4
3
0 1
2 1
1 3
0 3
2
1
0 1
1 0
```

### 输出

```
Case 1: 4
Case 2: 1
```



---

---
title: "Dominos 2"
layout: "post"
diff: 普及/提高-
pid: UVA11518
tag: ['搜索', '图论']
---

# Dominos 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2513

[PDF](https://uva.onlinejudge.org/external/115/p11518.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/7f28ab761227ecc0796512e3a227ad6b7d28229e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/358c7d33d629af402b53bf37fed925488939a6c1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/66db10874dbf273f4e15346e2df8aeb00eddd6c8.png)

## 样例 #1

### 输入

```
1
3 2 1
1 2
2 3
2
```

### 输出

```
2
```



---

---
title: "困难的串 Krypton Factor"
layout: "post"
diff: 普及/提高-
pid: UVA129
tag: ['搜索', '递归']
---

# 困难的串 Krypton Factor

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=65

[PDF](https://uva.onlinejudge.org/external/1/p129.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/acf4a8193efdffb3da55bab10c0c0b1353f2dc09.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/b923e93bcc47c02bfb54e49f8ec2dafc214ee3e7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/2bee9ae1cb76c0f477ce304cd2c16b191025d687.png)

## 样例 #1

### 输入

```
7 3
30 3
0 0
```

### 输出

```
ABAC ABA
7
ABAC ABCA CBAB CABA CABC ACBA CABA
28
```



---

---
title: "骑士的移动 Knight Moves"
layout: "post"
diff: 普及/提高-
pid: UVA439
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# 骑士的移动 Knight Moves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=380

[PDF](https://uva.onlinejudge.org/external/4/p439.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/49281f2a839995de267463a506fc7b04652bcf4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/f986ca9c080d4c2fa5952f61f878eaafe27fdf4b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/e3265edbb46489790ff00e32193564840a6de7fe.png)

## 样例 #1

### 输入

```
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
```

### 输出

```
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.
```



---

---
title: "素数环 Prime Ring Problem"
layout: "post"
diff: 普及/提高-
pid: UVA524
tag: ['搜索', '深度优先搜索 DFS', '素数判断,质数,筛法']
---

# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/564d6b149cca77cbaf1583cf2a35822a0f78251c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/3944acd7f0b0909cb25a01cbb113e5507c6e3a72.png)

## 样例 #1

### 输入

```
6
8
```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2
```



---

---
title: "Dungeon Master"
layout: "post"
diff: 普及/提高-
pid: UVA532
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# Dungeon Master

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=473

[PDF](https://uva.onlinejudge.org/external/5/p532.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/f5204064f9aec4c41d412eb29fbc006dac1f717c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/bc032dafb23822eecdf0192d86ea58ddcaa98ec5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/30d36b3bfe984f90284eb870b4006708e8229767.png)

## 样例 #1

### 输入

```
3 4 5
S....
.###.
.##..
###.#
#####
#####
##.##
##...
#####
#####
#.###
####E
1 3 3
S##
#E#
###
0 0 0
```

### 输出

```
Escaped in 11 minute(s).
Trapped!
```



---

---
title: "Goldbach's Conjecture"
layout: "post"
diff: 普及/提高-
pid: UVA543
tag: ['搜索', '枚举', '素数判断,质数,筛法']
---

# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 输入格式

输入包含多组数据。

每组数据占一行，包含一个偶数 $n(n \le 10^6)$。 读入以 $0$ 结束。

## 输出格式

对于每组数据，输出形如 `n = a + b`，其中 $a,b$ 是奇质数。若有多组满足条件的 $a,b$，输出 $b−a$ 最大的一组。

若无解，输出 `Goldbach's conjecture is wrong.`。

## 样例 #1

### 输入

```
8
20
42
0
```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37
```



---



---

# 题号列表

- UVA102 - Ecological Bin Packing
- UVA10285 - 最长的滑雪路径 Longest Run on a Snowboard
- UVA10364 - Square
- UVA11210 - Chinese Mahjong
- UVA11463 - Commandos
- UVA11518 - Dominos 2
- UVA129 - 困难的串 Krypton Factor
- UVA439 - 骑士的移动 Knight Moves
- UVA524 - 素数环 Prime Ring Problem
- UVA532 - Dungeon Master
- UVA543 - Goldbach's Conjecture


---

---
title: "Irreducable Basic Fractions"
layout: "post"
diff: 普及/提高-
pid: UVA10179
tag: ['数学', '数论']
---

# Irreducable Basic Fractions

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1120

[PDF](https://uva.onlinejudge.org/external/101/p10179.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10179/9620a43ff9b7f7c199916d89f9baccfbc26a1bcb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10179/15c5758bb9140db2ef3dc73765681e52125bf8c7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10179/dab1354a409dc125c75d183100f42a2c53cbec80.png)

## 样例 #1

### 输入

```
12
123456
7654321
0
```

### 输出

```
4
41088
7251444
```



---

---
title: "选择与除法 Choose and divide"
layout: "post"
diff: 普及/提高-
pid: UVA10375
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/8ff851cc9926c4165c7c6485311457578bf77f44.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/1dd11724e900842b1855cb026891122b11c4b9c5.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998
```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960
```



---

---
title: "Crossed Ladders"
layout: "post"
diff: 普及/提高-
pid: UVA10566
tag: ['数学', '二分']
---

# Crossed Ladders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1507

[PDF](https://uva.onlinejudge.org/external/105/p10566.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/04bd930627e82cc986e14b41bdaa0b69d1b37635.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/3754046125e48d80d182db37d7cf4ad07235fd79.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/4551903c4aac4c95f56b92a3629e8f0e97337487.png)

## 样例 #1

### 输入

```
30 40 10
12.619429 8.163332 3
10 10 3
10 10 1
```

### 输出

```
26.033
7.000
8.000
9.798
```



---

---
title: "Triangle Fun"
layout: "post"
diff: 普及/提高-
pid: UVA11437
tag: ['数学', '计算几何']
---

# Triangle Fun

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2432

[PDF](https://uva.onlinejudge.org/external/114/p11437.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11437/f4b807f28b80b04a563e92fb3605213be81cada3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11437/1b689792e470ad9074a7872233a8a5108ef92cb4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11437/831bc9d4b2e1f5cb1b048fcf3e80a525cedda978.png)

## 样例 #1

### 输入

```
2
3994.707 9251.677 4152.916 7157.810 5156.835 2551.972
6903.233 3540.932 5171.382 3708.015 213.959 2519.852
```

### 输出

```
98099
206144
```



---

---
title: "Big Number"
layout: "post"
diff: 普及/提高-
pid: UVA1185
tag: ['数学', '高精度']
---

# Big Number

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3626

[PDF](https://uva.onlinejudge.org/external/11/p1185.pdf)



---

---
title: "Hats"
layout: "post"
diff: 普及/提高-
pid: UVA12024
tag: ['数学', '组合数学']
---

# Hats

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3175

[PDF](https://uva.onlinejudge.org/external/120/p12024.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/25a75cc3aa1181e89f3439302a46c65776fbdd03.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/6e06f4c8abc36d2c27721c4c1a100d96fdc1440a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/5795feaddca228bb541652bdb5a4f2bf8601a4e5.png)

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
1/2
2/6
9/24
```



---

---
title: "Roman Roulette"
layout: "post"
diff: 普及/提高-
pid: UVA130
tag: ['模拟', '数学']
---

# Roman Roulette

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=66

[PDF](https://uva.onlinejudge.org/external/1/p130.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/caee382d0a44b73c133d86736efebb87c565fd81.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/2fd7d5a7becb6e3c9198792129aea585cf60d396.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/7119a2af354945bcc0ae14333eecfa0ba1f0c8b0.png)

## 样例 #1

### 输入

```
5 2
1 5
0 0
```

### 输出

```
3
1
```



---



---

# 题号列表

- UVA10179 - Irreducable Basic Fractions
- UVA10375 - 选择与除法 Choose and divide
- UVA10566 - Crossed Ladders
- UVA11437 - Triangle Fun
- UVA1185 - Big Number
- UVA12024 - Hats
- UVA130 - Roman Roulette


---

---
title: "噪音恐惧症 Audiophobia"
layout: "post"
diff: 普及/提高-
pid: UVA10048
tag: ['最短路']
---

# 噪音恐惧症 Audiophobia

## 题目描述

**题意描述**


有一张有$C$个路口，$S$条街道的无向图，每条街道都一个噪音值。

请问从$c_1$走到$c_2$，经过的路径上最大噪音的最小值是多少。

## 输入格式

输入包含多组数据，每组数据第一行包含三个整数$C(\leq 100),S(\leq1,000),Q(\leq 10,000)$，分别表示路口数、街道数、询问数。

接下来$S$行，每行$3$个整数$c_1,c_2,d(c_1≠c_2)$，分别表示一条街道连接的两个路口编号，以及这条街道噪音的分贝值。

接下来$Q$行，每行给定两个路口编号$c_1,c_2(c_1 ≠ c_2)$，请你输出这两个路口之间路径的最大分贝值的最小值。如果$c_1$不能到达$c_2$，输出"no path"。

输入以$C=S=Q=0$结束。

## 输出格式

每组数据前输出一行数据组数的编号。（见样例）

对于每个询问，输出一行。

每两组数据之间输出一个空行。

## 样例 #1

### 输入

```
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
1 7
2 6
6 2
7 6 3
1 2 50
1 3 60
2 4 120
3 6 50
4 6 80
5 7 40
7 5
1 7
2 4
0 0 0
```

### 输出

```
Case #1
80
60
60

Case #2
40
no path
80
```



---

---
title: "Commandos"
layout: "post"
diff: 普及/提高-
pid: UVA11463
tag: ['广度优先搜索 BFS', '最短路']
---

# Commandos

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2458

[PDF](https://uva.onlinejudge.org/external/114/p11463.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6db49602a4d25da560ee412c34699e1614bef1f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6dd5f0f8ad77e22ca50b6445d392ed09627aa84c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/f01cfb1355e55dd1b4f293845dd5f685541a310d.png)

## 样例 #1

### 输入

```
2
4
3
0 1
2 1
1 3
0 3
2
1
0 1
1 0
```

### 输出

```
Case 1: 4
Case 2: 1
```



---

---
title: "Domino Effect"
layout: "post"
diff: 普及/提高-
pid: UVA318
tag: ['优先队列', '最短路']
---

# Domino Effect

## 题目描述

@[lin_toto](/space/show?uid=256)

题目名字：多米诺骨牌效应

您是否知道多米诺骨牌除了玩之外还可以用来做其他事情？拿一些多米诺骨牌，然后将它们排成一排，并在它们之间只留一小段距离。如果你做得对，你可以推倒第一张多米诺骨牌并使所有其他的多米诺骨牌依次倒下（这就是“多米诺骨牌效应”的由来）。

数量太少的多米诺骨牌有点毫无意义，所以有些人在八十年代初就走向了相反的极端。他们使用数以百万计的不同颜色和材料的多米诺骨牌，用倒下的精美多米诺骨牌组成的图案填满整个大厅，来创造（短命的）艺术品。在这些过程中，通常不只有一排多米诺骨牌同时倒下。你可以发现，时间是一个重要的影响因素。 

现在你的任务是编写一个程序，给定由多米诺骨牌组成的系统，计算最后一个多米诺骨牌在何时何地倒下。该系统由几个简单的关键多米诺骨牌和其之间的多米诺骨牌连接而成。当一个关键的多米诺骨牌倒下时，连接到该关键多米诺骨牌的所有多米诺骨牌都开始倒下（除了那些已经倒下的多米诺骨牌）。当倒下的多米诺骨牌到达尚未倒下的其他关键多米诺骨牌时，这些关键多米诺骨牌也会倒下并且引起与它们相连的多米诺骨牌开始倒下。多米诺骨牌行可能会从任何一端开始倒下。甚至有可能同一多米诺骨牌行从两端开始倒下，在这种情况下，该行倒下的最后一张多米诺骨牌位于其行两端的关键多米诺骨牌之间。您可以假设行中的多米诺骨牌以均匀的速度倒下。

## 输入格式

输入文件包含几个多米诺骨牌系统的描述。每个描述的第一行包含两个整数：关键多米诺骨牌的数量n（1 <= n <500）和它们之间的行数m。关键的多米诺骨牌从1到n编号。在任何一对关键多米诺骨牌之间至多有一行并且多米诺骨牌图是连通的，即至少有一种方法可以通过多米诺骨牌行从一个关键多米诺骨牌到达任何其他多米诺骨牌。 

以下m行每行包含三个整数a，b和l，表示在关键的多米诺骨牌a和b之间有一行，从一端到另一端需要l秒。 

每个系统都是通过翻推倒编号为1的多米诺骨牌来启动的。 

文件以一组空的多米诺骨牌系统（n = m = 0）结束，你不应该处理此组数据。

## 输出格式

对于每组数据，输出一行说明数据的编号（'System ＃1'，'System ＃2'等）。然后输出一行，其中包含最后一张多米诺骨牌落下的时间，精确到小数点后一位数，以及最后一张多米诺骨牌倒下的位置，这个位置为某个关键多米诺骨牌或两个关键多米诺骨牌之间（在这种情况下 ，按升序输出两个关键多米诺骨牌编号）。按照输出示例的格式输出。输入保证只有一个解决方案。**在每组数据后输出一个空行。**

## 样例 #1

### 输入

```
2 1
1 2 27
3 3
1 2 5
1 3 5
2 3 5
0 0
```

### 输出

```
System #1
The last domino falls after 27.0 seconds, at key domino 2.
System #2
The last domino falls after 7.5 seconds, between key dominoes 2 and 3.
```



---



---

# 题号列表

- UVA10048 - 噪音恐惧症 Audiophobia
- UVA11463 - Commandos
- UVA318 - Domino Effect


---

---
title: "矩阵链乘 Matrix Chain Multiplication"
layout: "post"
diff: 普及/提高-
pid: UVA442
tag: ['字符串', '栈', '构造']
---

# 矩阵链乘 Matrix Chain Multiplication

## 题目描述

## 矩阵链乘


​  假设你必须评估一种表达形如 A*B*C*D*E，其中 A,B,C,D,E是矩阵。既然矩阵乘法是关联的，那么乘法的顺序是任意的。然而，链乘的元素数量必须由你选择的赋值顺序决定。

​  例如，A，B，C分别是 50 * 10 ，10 * 20 和 20 * 5 的矩阵。现在有两种方案计算 A * B * C ,即（A * B) * C 和 A*(B * C)。  
   第一个要进行15000次基本乘法，而第二个只进行3500次。

​  你的任务就是写出一个程序判定以给定的方式相乘需要多少次基本乘法计算。

## 输入格式

​  输入包含两个部分：矩阵和表达式。 
   输入文件的第一行包含了一个整数 n(1  $\leq$  n  $\leq$  26), 代表矩阵的个数。接下来的n行每一行都包含了一个大写字母，说明矩阵的名称，以及两个整数，说明行与列的个数。  
   第二个部分严格遵守以下的语法：

SecondPart = Line {  Line  } <EOF>
Line       = Expression <CR>
Expression = Matrix | "(" Expression Expression ")"
Matrix     = "A" | "B" | "C" | ... | "X" | "Y" | "Z"

## 输出格式

​  对于每一个表达式，如果乘法无法进行就输出 " error "。否则就输出一行包含计算所需的乘法次数。 

感谢@onceagain 提供翻译

## 样例 #1

### 输入

```
9
A 50 10
B 10 20
C 20 5
D 30 35
E 35 15
F 15 5
G 5 10
H 10 20
I 20 25
A
B
C
(AA)
(AB)
(AC)
(A(BC))
((AB)C)
(((((DE)F)G)H)I)
(D(E(F(G(HI)))))
((D(EF))((GH)I))
```

### 输出

```
0
0
0
error
10000
error
3500
15000
40500
47500
15125
```



---



---

# 题号列表

- UVA442 - 矩阵链乘 Matrix Chain Multiplication


---

---
title: "Prime Distance"
layout: "post"
diff: 普及/提高-
pid: UVA10140
tag: ['枚举', '素数判断,质数,筛法']
---

# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/9848cf59ee0ece9e1a0dfd40a08e689a1c5c6604.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/6760a091328104551b134bb6b39accf505df0484.png)

## 样例 #1

### 输入

```
2 17
14 17
```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.
```



---

---
title: "Ecological Bin Packing"
layout: "post"
diff: 普及/提高-
pid: UVA102
tag: ['字符串', '枚举', '深度优先搜索 DFS']
---

# Ecological Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

[PDF](https://uva.onlinejudge.org/external/1/p102.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ef84892469f793327bfb4a3ea04e4237b1761a6d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ae3b90e524e6ffd7e27eab05a64abfd8be7111ef.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/249702f9f5f1e91446cb32d9b3ad6a7eca7264f5.png)

## 样例 #1

### 输入

```
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10
```

### 输出

```
BCG 30
CBG 50
```



---

---
title: "Image Is Everything"
layout: "post"
diff: 普及/提高-
pid: UVA1030
tag: ['枚举']
---

# Image Is Everything

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3471

[PDF](https://uva.onlinejudge.org/external/10/p1030.pdf)



---

---
title: "Maximum Sum"
layout: "post"
diff: 普及/提高-
pid: UVA108
tag: ['贪心', '枚举', '前缀和']
---

# Maximum Sum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=44

[PDF](https://uva.onlinejudge.org/external/1/p108.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/9bad502ba34d25d0111329e7b191a1e73f37eafb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/396f13d4868ef41457d1488f0abfd926a952de29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/68309ab00fee7fe7c208d797f30252388b43c04b.png)

## 样例 #1

### 输入

```
4
0 -2 -7 0 
9 2 -6 2
-4 1 -4 1 
-1 8 0 -2
```

### 输出

```
15
```



---

---
title: "The primary problem"
layout: "post"
diff: 普及/提高-
pid: UVA10948
tag: ['枚举', '素数判断,质数,筛法']
---

# The primary problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1889

[PDF](https://uva.onlinejudge.org/external/109/p10948.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/e8db1ede82953ce1670162c4cb5dde5e02f35076.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/2b712e379782764e7b714ebada6c5d4d4ea8dfab.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/8ef2ba1bb7ff9690621ef3bff83005d37e831f21.png)

## 样例 #1

### 输入

```
4
5
6
7
9
10
11
0
```

### 输出

```
4:
2+2
5:
2+3
6:
3+3
7:
2+5
9:
2+7
10:
3+7
11:
NO WAY!
```



---

---
title: "Open Credit System"
layout: "post"
diff: 普及/提高-
pid: UVA11078
tag: ['枚举', '优先队列']
---

# Open Credit System

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2019

[PDF](https://uva.onlinejudge.org/external/110/p11078.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/25cd6848e8285209c3495ee0e4d8dbf426b85add.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/026441a9548841bf934643d0c612606f5cd27fd5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/94f6757afbd3bba1db2ec9c49cc54dadb565959d.png)

## 样例 #1

### 输入

```
3
2
100
20
4
4
3
2
1
4
1
2
3
4
```

### 输出

```
80
3
-1
```



---

---
title: "环形跑道 Just Finish it up"
layout: "post"
diff: 普及/提高-
pid: UVA11093
tag: ['枚举']
---

# 环形跑道 Just Finish it up

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2034

[PDF](https://uva.onlinejudge.org/external/110/p11093.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11093/4a8ff08dc895659b141306f5ab2159a69456d4a3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11093/e958c95d281e08201c0afd3278469819665a9540.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11093/876afde51b47b7b3fd322b45859776296cfef750.png)

## 样例 #1

### 输入

```
2
5
1 1 1 1 1
1 1 2 1 1
7
1 1 1 10 1 1 1
2 2 2 2 2 2 2
```

### 输出

```
Case 1: Not possible
Case 2: Possible from station 4
```



---

---
title: "Chinese Mahjong"
layout: "post"
diff: 普及/提高-
pid: UVA11210
tag: ['模拟', '字符串', '搜索', '枚举']
---

# Chinese Mahjong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2151

[PDF](https://uva.onlinejudge.org/external/112/p11210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/00db9c6ee014cb07d2ff71e0aff3d224225bbbd1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/1402d96f2257d9e8bce6c1fccdee577f9b27804e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/0cc0c231da6a95552468965d5df9b75080e2ca2a.png)

## 样例 #1

### 输入

```
1S 1S 2S 2S 2S 3S 3S 3S 7S 8S 9S FA FA
1S 2S 3S 4S 5S 6S 7S 8S 9S 1T 3T 5T 7T
0
```

### 输出

```
Case 1: 1S 4S FA
Case 2: Not ready
```



---

---
title: "唯一的雪花 Unique Snowflakes"
layout: "post"
diff: 普及/提高-
pid: UVA11572
tag: ['枚举', '哈希 hashing', '双指针 two-pointer']
---

# 唯一的雪花 Unique Snowflakes

## 题目描述

企业家 Emily 有一个很酷的主意：把雪花包起来卖。她发明了一台机器，这台机器可以捕捉飘落的雪花，并把它们一片一片打包进一个包裹里。一旦这个包裹满了，它就会被封上送去发售。

Emily 的公司的口号是“把独特打包起来”，为了实现这一诺言，一个包裹里不能有两片一样的雪花。不幸的是，这并不容易做到，因为实际上通过机器的雪花中有很多是相同的。Emily 想知道这样一个不包含两片一样的雪花的包裹最大能有多大，她可以在任何时候启动机器，但是一旦机器启动了，直到包裹被封上为止，所有通过机器的雪花都必须被打包进这个包裹里，当然，包裹可以在任何时候被封上。

## 输入格式

第一行是测试数据组数 $T$，对于每一组数据，第一行是通过机器的雪花总数 $n$（$n \le {10}^6$），下面 $n$ 行每行一个在 $[0, {10}^9]$ 内的整数，标记了这片雪花，当两片雪花标记相同时，这两片雪花是一样的。

## 输出格式

对于每一组数据，输出最大包裹的大小。

## 样例 #1

### 输入

```
1
5
1
2
3
2
1
```

### 输出

```
3
```



---

---
title: "带宽 Bandwidth"
layout: "post"
diff: 普及/提高-
pid: UVA140
tag: ['枚举', '剪枝']
---

# 带宽 Bandwidth

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=76

[PDF](https://uva.onlinejudge.org/external/1/p140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/c28a82a576401d68954e54e49ebe92f369cda3c9.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/b1e8ffcfe78f638ef691e846732af5db87cfed53.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/a04c7e0220dc363f6a9b2b8414dfbfd573ebaa94.png)

## 样例 #1

### 输入

```
A:FB;B:GC;D:GC;F:AGH;E:HD
#
```

### 输出

```
A B C F G D H E -&gt; 3
```



---

---
title: "Power Crisis"
layout: "post"
diff: 普及/提高-
pid: UVA151
tag: ['模拟', '枚举', '队列']
---

# Power Crisis

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=87

[PDF](https://uva.onlinejudge.org/external/1/p151.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/2b7fc9e4df48b383902b9f5285f0316b5f437407.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/e69ea5e0da52f9c6b45414318b78dab4f5faf403.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/47bd9da34308490bfea1a9eb4e0baa05fdd433d1.png)

## 样例 #1

### 输入

```
17
0
```

### 输出

```
7
```



---

---
title: "数据库 Database"
layout: "post"
diff: 普及/提高-
pid: UVA1592
tag: ['字符串', '枚举', '进制']
---

# 数据库 Database

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4467

[PDF](https://uva.onlinejudge.org/external/15/p1592.pdf)



---

---
title: "谜题 Puzzle"
layout: "post"
diff: 普及/提高-
pid: UVA227
tag: ['模拟', '字符串', '枚举']
---

# 谜题 Puzzle

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=163

[PDF](https://uva.onlinejudge.org/external/2/p227.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/952149a2874e339bbc22a79a1cd1d063e89e1421.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/e230761e1328196764fb5b28ac3d84ef407e0b7e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/30096ab22228859e28141b62fe1f49b2628b66bb.png)

## 样例 #1

### 输入

```
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAAAABBRRRLL0
Z
```

### 输出

```
Puzzle #1:
T R G S J
X O K L I
M D V B N
W P   A E
U Q H C F

Puzzle #2:
  A B C D
F G H I E
K L M N J
P Q R S O
T U V W X

Puzzle #3:
This puzzle has no final configuration.
```



---

---
title: "Goldbach's Conjecture"
layout: "post"
diff: 普及/提高-
pid: UVA543
tag: ['搜索', '枚举', '素数判断,质数,筛法']
---

# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 输入格式

输入包含多组数据。

每组数据占一行，包含一个偶数 $n(n \le 10^6)$。 读入以 $0$ 结束。

## 输出格式

对于每组数据，输出形如 `n = a + b`，其中 $a,b$ 是奇质数。若有多组满足条件的 $a,b$，输出 $b−a$ 最大的一组。

若无解，输出 `Goldbach's conjecture is wrong.`。

## 样例 #1

### 输入

```
8
20
42
0
```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37
```



---



---

# 题号列表

- UVA10140 - Prime Distance
- UVA102 - Ecological Bin Packing
- UVA1030 - Image Is Everything
- UVA108 - Maximum Sum
- UVA10948 - The primary problem
- UVA11078 - Open Credit System
- UVA11093 - 环形跑道 Just Finish it up
- UVA11210 - Chinese Mahjong
- UVA11572 - 唯一的雪花 Unique Snowflakes
- UVA140 - 带宽 Bandwidth
- UVA151 - Power Crisis
- UVA1592 - 数据库 Database
- UVA227 - 谜题 Puzzle
- UVA543 - Goldbach's Conjecture


---

---
title: "The Blocks Problem"
layout: "post"
diff: 普及/提高-
pid: UVA101
tag: ['模拟', '递归', '栈']
---

# The Blocks Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=37

[PDF](https://uva.onlinejudge.org/external/1/p101.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/4657c698576c8c299dbbf5655d7dbe63bf148978.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/0a0a9b4a15235d9e81d83d5d31ee89ce48870fed.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/ca24bcd0ff3af9dc6c1fcefd73c87532e9e05bd4.png)

## 样例 #1

### 输入

```
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit
```

### 输出

```
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:
```



---

---
title: "I Can Guess the Data Structure!"
layout: "post"
diff: 普及/提高-
pid: UVA11995
tag: ['模拟', '栈', '队列']
---

# I Can Guess the Data Structure!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3146

[PDF](https://uva.onlinejudge.org/external/119/p11995.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/55cb8a2c5cf1532ff4a8dff640c7538c0998c78c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/85c08a1b2399e94d2f430010d18cb8c7c42d2ddd.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/ca430d6d3039e2b5f45d99cd031ba66a1656ade0.png)

## 样例 #1

### 输入

```
6
1 1
1 2
1 3
2 1
2 2
2 3
6
1 1
1 2
1 3
2 3
2 2
2 1
2
1 1
2 2
4
1 2
1 1
2 1
2 2
7
1 2
1 5
1 1
1 3
2 5
1 4
2 4
```

### 输出

```
queue
not sure
impossible
stack
priority queue
```



---

---
title: "矩阵链乘 Matrix Chain Multiplication"
layout: "post"
diff: 普及/提高-
pid: UVA442
tag: ['字符串', '栈', '构造']
---

# 矩阵链乘 Matrix Chain Multiplication

## 题目描述

## 矩阵链乘


​  假设你必须评估一种表达形如 A*B*C*D*E，其中 A,B,C,D,E是矩阵。既然矩阵乘法是关联的，那么乘法的顺序是任意的。然而，链乘的元素数量必须由你选择的赋值顺序决定。

​  例如，A，B，C分别是 50 * 10 ，10 * 20 和 20 * 5 的矩阵。现在有两种方案计算 A * B * C ,即（A * B) * C 和 A*(B * C)。  
   第一个要进行15000次基本乘法，而第二个只进行3500次。

​  你的任务就是写出一个程序判定以给定的方式相乘需要多少次基本乘法计算。

## 输入格式

​  输入包含两个部分：矩阵和表达式。 
   输入文件的第一行包含了一个整数 n(1  $\leq$  n  $\leq$  26), 代表矩阵的个数。接下来的n行每一行都包含了一个大写字母，说明矩阵的名称，以及两个整数，说明行与列的个数。  
   第二个部分严格遵守以下的语法：

SecondPart = Line {  Line  } <EOF>
Line       = Expression <CR>
Expression = Matrix | "(" Expression Expression ")"
Matrix     = "A" | "B" | "C" | ... | "X" | "Y" | "Z"

## 输出格式

​  对于每一个表达式，如果乘法无法进行就输出 " error "。否则就输出一行包含计算所需的乘法次数。 

感谢@onceagain 提供翻译

## 样例 #1

### 输入

```
9
A 50 10
B 10 20
C 20 5
D 30 35
E 35 15
F 15 5
G 5 10
H 10 20
I 20 25
A
B
C
(AA)
(AB)
(AC)
(A(BC))
((AB)C)
(((((DE)F)G)H)I)
(D(E(F(G(HI)))))
((D(EF))((GH)I))
```

### 输出

```
0
0
0
error
10000
error
3500
15000
40500
47500
15125
```



---



---

# 题号列表

- UVA101 - The Blocks Problem
- UVA11995 - I Can Guess the Data Structure!
- UVA442 - 矩阵链乘 Matrix Chain Multiplication


---

---
title: "Strategic game"
layout: "post"
diff: 普及/提高-
pid: UVA1292
tag: ['树形 DP']
---

# Strategic game

## 题目描述

### 题目翻译

给定一棵 $n$ 个节点的树。你需要让这棵树上的每条边都被看守。当一条边的端点上至少有一个士兵时，我们就说这条边被看守。求出看守这棵树最少用的士兵数量。

## 输入格式

**本题有不定组数的多组数据。**

对于每组数据，第一行为正数 $n$，描述树的大小。

请注意节点编号从 $0$ 开始，

接下来 $n$ 行中，每行可能为：

- $u_i:(k_i)$ $v_1$ $v_2$ $\cdots$ $v_{k_i}$

`u_i:(k_i) v_1 v_2 ... v_{k_i}`

表示点 $u_i$ 的儿子有 $k_i$ 个，编号依次为 $v_1,v_2,\cdots,v_{k_i}$；

也可能为

- $u_i:(0)$

`u_i:(0)`

表示点 $u_i$ 没有儿子。

## 输出格式

对于每组数据，输出一行一个整数，即答案。

## 样例 #1

### 输入

```
4
0:(1) 1
1:(2) 2 3
2:(0)
3:(0)
5
3:(3) 1 4 2
1:(1) 0
2:(0)
0:(0)
4:(0)

```

### 输出

```
1
2

```



---



---

# 题号列表

- UVA1292 - Strategic game


---

---
title: "Ultra-QuickSort"
layout: "post"
diff: 普及/提高-
pid: UVA10810
tag: ['树状数组', '排序']
---

# Ultra-QuickSort

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1751

[PDF](https://uva.onlinejudge.org/external/108/p10810.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/751b373c4650fd9cb6ed8962c612343e8c3faf34.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/bbac08e36c21bfb711cef255cbd33a4aba31f921.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/07aa3a0e09920ab537e7e75fdd2f783aadf38833.png)

## 样例 #1

### 输入

```
5
9
1
0
5
4
3
1
2
3
0
```

### 输出

```
6
0
```



---



---

# 题号列表

- UVA10810 - Ultra-QuickSort


---

---
title: "选择与除法 Choose and divide"
layout: "post"
diff: 普及/提高-
pid: UVA10375
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/8ff851cc9926c4165c7c6485311457578bf77f44.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/1dd11724e900842b1855cb026891122b11c4b9c5.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998
```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960
```



---

---
title: "反片语 Ananagrams"
layout: "post"
diff: 普及/提高-
pid: UVA156
tag: ['字符串', '排序', '概率论']
---

# 反片语 Ananagrams

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=92

[PDF](https://uva.onlinejudge.org/external/1/p156.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/dc6cdcbb36579acf2629ae204167ab408bdaa20f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/ec895ca45b112623bf0e495312ef5805c9c5a222.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA156/46b34b0a4275c645ab84982aea6e74168eb7cdb4.png)

## 样例 #1

### 输入

```
ladder came tape soon leader acme RIDE lone Dreis peat
ScAlE orb eye Rides dealer NotE derail LaCeS drIed
noel dire Disk mace Rob dries
#
```

### 输出

```
Disk
NotE
derail
drIed
eye
ladder
soon
```



---

---
title: "下落的树叶 The Falling Leaves"
layout: "post"
diff: 普及/提高-
pid: UVA699
tag: ['递归', '树的遍历', '概率论']
---

# 下落的树叶 The Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=640

[PDF](https://uva.onlinejudge.org/external/6/p699.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/735ce6ad24a18ffc8b70b3a6c28998f5211a95ce.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/3915803c372316917ebc2dfce3b293040c414d6d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/08403ba4d2bc8dd6492bc2a54f8c6fa4f6769708.png)

## 样例 #1

### 输入

```
5 7 -1 6 -1 -1 3 -1 -1
8 2 9 -1 -1 6 5 -1 -1 12 -1
-1 3 7 -1 -1 -1
-1
```

### 输出

```
Case 1:
7 11 3
Case 2:
9 7 21 15
```



---



---

# 题号列表

- UVA10375 - 选择与除法 Choose and divide
- UVA156 - 反片语 Ananagrams
- UVA699 - 下落的树叶 The Falling Leaves


---

---
title: "The Blocks Problem"
layout: "post"
diff: 普及/提高-
pid: UVA101
tag: ['模拟', '递归', '栈']
---

# The Blocks Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=37

[PDF](https://uva.onlinejudge.org/external/1/p101.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/4657c698576c8c299dbbf5655d7dbe63bf148978.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/0a0a9b4a15235d9e81d83d5d31ee89ce48870fed.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/ca24bcd0ff3af9dc6c1fcefd73c87532e9e05bd4.png)

## 样例 #1

### 输入

```
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit
```

### 输出

```
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:
```



---

---
title: "安迪的第一个字典 Andy's First Dictionary"
layout: "post"
diff: 普及/提高-
pid: UVA10815
tag: ['模拟', '字符串', '排序']
---

# 安迪的第一个字典 Andy's First Dictionary

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1756

[PDF](https://uva.onlinejudge.org/external/108/p10815.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/4f5c1d24c1c6cb6c76b70bd32c63daec8b95b2f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/03acce165b96154650f2620dd40e5c6d60bd1a9f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10815/a4a74f8b6cd346abca8f4ccf0d50b25e34c0aba2.png)

## 样例 #1

### 输入

```
Adventures in Disneyland
Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."
So they went home.
```

### 输出

```
a
adventures
blondes
came
disneyland
fork
going
home
in
left
read
road
sign
so
the
they
to
two
went
were
when
```



---

---
title: "全部相加 Add All"
layout: "post"
diff: 普及/提高-
pid: UVA10954
tag: ['模拟', '优先队列', '队列']
---

# 全部相加 Add All

## 题目描述

## 题意翻译
给你 $n$ 个数，求将这 $n$ 个数合并成一个数的成本（成本即为此次相加之和）的最小值。

## 输入格式

本题多测，每组数据的第一行为 $n$，然后一行 $n$ 个整数，表示需要合并的数据。当 $n=0$ 时，表示输入结束。

## 输出格式

一行一个整数，表示成本的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^3$，$1 \leq a_i \leq 10^{5}$。

## 样例 #1

### 输入

```
3
1 2 3
4
1 2 3 4
0
```

### 输出

```
9
19
```



---

---
title: "Chinese Mahjong"
layout: "post"
diff: 普及/提高-
pid: UVA11210
tag: ['模拟', '字符串', '搜索', '枚举']
---

# Chinese Mahjong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2151

[PDF](https://uva.onlinejudge.org/external/112/p11210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/00db9c6ee014cb07d2ff71e0aff3d224225bbbd1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/1402d96f2257d9e8bce6c1fccdee577f9b27804e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11210/0cc0c231da6a95552468965d5df9b75080e2ca2a.png)

## 样例 #1

### 输入

```
1S 1S 2S 2S 2S 3S 3S 3S 7S 8S 9S FA FA
1S 2S 3S 4S 5S 6S 7S 8S 9S 1T 3T 5T 7T
0
```

### 输出

```
Case 1: 1S 4S FA
Case 2: Not ready
```



---

---
title: "I Can Guess the Data Structure!"
layout: "post"
diff: 普及/提高-
pid: UVA11995
tag: ['模拟', '栈', '队列']
---

# I Can Guess the Data Structure!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3146

[PDF](https://uva.onlinejudge.org/external/119/p11995.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/55cb8a2c5cf1532ff4a8dff640c7538c0998c78c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/85c08a1b2399e94d2f430010d18cb8c7c42d2ddd.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/ca430d6d3039e2b5f45d99cd031ba66a1656ade0.png)

## 样例 #1

### 输入

```
6
1 1
1 2
1 3
2 1
2 2
2 3
6
1 1
1 2
1 3
2 3
2 2
2 1
2
1 1
2 2
4
1 2
1 1
2 1
2 2
7
1 2
1 5
1 1
1 3
2 5
1 4
2 4
```

### 输出

```
queue
not sure
impossible
stack
priority queue
```



---

---
title: "The Errant Physicist"
layout: "post"
diff: 普及/提高-
pid: UVA126
tag: ['模拟', '字符串']
---

# The Errant Physicist

## 题目描述

著名物理学家阿尔弗雷德·E·纽曼正在研究涉及多项式乘法的问题。例如，他可能需要计算
$$
(-x^8y+9x^3-1+y) \cdot (x^5y+1+x^3)
$$
得到答案
$$
-x^{13}y^2-x^{11}y+8x^8y+9x^6-x^5y+x^5y^2+8x^3+x^3y-1+y
$$
不幸的是，这些问题太微不足道了，以至于这位伟人的思绪总是游离在工作之外，他得到了错误的答案。因此，他设计的几枚核弹头过早引爆，摧毁了五个主要城市和几片雨林。
你要写一个程序来执行这样的乘法并拯救世界。

## 输入格式

输入数据文件有若干个测试数据，每个测试数据有两行，每行包含的字符不超过 $80$ 个。输入文件的最后一行包含一个`#`作为其第一个字符。

每行输入都包含一个多项式，该多项式没有空格，也没有任何显式的求幂运算符。指数是正的非零无符号整数。系数也是整数，但也可以是负数。指数和系数的大小都小于或等于 $100$。每个项最多包含一个 $x$ 因子和一个 $y$ 因子。

## 输出格式

您的程序必须将输入中的每对多项式相乘，并在一对上打印每个乘积行，第一行包含所有指数，相对于其余行适当定位信息，在下面的行中。

1. 输出行中的项必须按 $x$ 的幂次降序排列，对于给定的幂次按照 $y$ 的幂次升序排序。

2. 可以被化简的单项式必须化简。例如，$40x^2y^3-38x^2y^3$ 被替换为 $2x^2y^3$。

3. 不得显示系数为零的单项式。

4. 除常数项为 $1$ 的情况外，系数 $1$ 被省略。

5. 省略指数 $1$。

6. 省略 $x^0$ 和 $y^0$ 的因子。

7. 二进制正负（即输出中连接项的正负）前后都有一个空格。

8. 如果第一项的系数为负，则在第一列中以一元减号开头，中间没有空格。否则，系数本身从第一个输出开始列。

9. 可以假设输出长度最多为 $80$ 个字符。

10. 每对输出行之间不应有空白行。

11. 一对行的长度应该相同——为了实现这一点，尾随空格应该出现在较短行的最后一个非空白字符之后。

## 样例 #1

### 输入

```
-yx8+9x3-1+y
x5y+1+x3
1
1
#
```

### 输出

```
13 2 11
8
6 5
5 2
3 3
-x y - x y + 8x y + 9x - x y + x y + 8x + x y - 1 + y
1
```



---

---
title: "Roman Roulette"
layout: "post"
diff: 普及/提高-
pid: UVA130
tag: ['模拟', '数学']
---

# Roman Roulette

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=66

[PDF](https://uva.onlinejudge.org/external/1/p130.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/caee382d0a44b73c133d86736efebb87c565fd81.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/2fd7d5a7becb6e3c9198792129aea585cf60d396.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA130/7119a2af354945bcc0ae14333eecfa0ba1f0c8b0.png)

## 样例 #1

### 输入

```
5 2
1 5
0 0
```

### 输出

```
3
1
```



---

---
title: "Power Crisis"
layout: "post"
diff: 普及/提高-
pid: UVA151
tag: ['模拟', '枚举', '队列']
---

# Power Crisis

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=87

[PDF](https://uva.onlinejudge.org/external/1/p151.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/2b7fc9e4df48b383902b9f5285f0316b5f437407.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/e69ea5e0da52f9c6b45414318b78dab4f5faf403.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/47bd9da34308490bfea1a9eb4e0baa05fdd433d1.png)

## 样例 #1

### 输入

```
17
0
```

### 输出

```
7
```



---

---
title: "信息解码 Message Decoding"
layout: "post"
diff: 普及/提高-
pid: UVA213
tag: ['模拟', '字符串', '进制']
---

# 信息解码 Message Decoding

## 题目描述

考虑下面的01串序列：
```
0，00，01，10，000，001，010，011，100，101，110，0000，0001，···，1101，1110，00000，···
```
首先是长度为1的串，然后是长度为2的串，依此类推。如果看成二进制，相同长度的后一个串等于前一个串加1。注意上述序列中不存在全为1的串。你的任务是是编写一个解码程序。

## 输出格式

感谢@hedwig 提供的翻译

## 样例 #1

### 输入

```
TNM AEIOU 
0010101100011 
1010001001110110011 
11000 
$#**\ 
0100000101101100011100101000
```

### 输出

```
TAN ME 
##*\$
```



---

---
title: "谜题 Puzzle"
layout: "post"
diff: 普及/提高-
pid: UVA227
tag: ['模拟', '字符串', '枚举']
---

# 谜题 Puzzle

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=163

[PDF](https://uva.onlinejudge.org/external/2/p227.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/952149a2874e339bbc22a79a1cd1d063e89e1421.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/e230761e1328196764fb5b28ac3d84ef407e0b7e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/30096ab22228859e28141b62fe1f49b2628b66bb.png)

## 样例 #1

### 输入

```
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAAAABBRRRLL0
Z
```

### 输出

```
Puzzle #1:
T R G S J
X O K L I
M D V B N
W P   A E
U Q H C F

Puzzle #2:
  A B C D
F G H I E
K L M N J
P Q R S O
T U V W X

Puzzle #3:
This puzzle has no final configuration.
```



---

---
title: "DNA Translation"
layout: "post"
diff: 普及/提高-
pid: UVA385
tag: ['模拟']
---

# DNA Translation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=321

[PDF](https://uva.onlinejudge.org/external/3/p385.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA385/e93f18e2850196cc7c32643963e208aa23d116a5.png)

## 样例 #1

### 输入

```
ATACTCGTAATTCACTCC
CACCTGTACACAGAGGTAACTTAG
TTAATACGACATAATTAT
GCCTTGATATGGAGAACTCATTAGATA
AAGTGTATGTTGAATTATATAAAACGGGCATGA
ATGATGATGGCTTGA
*
```

### 输出

```
Ser-Ile-Lys
Cys-Leu-His
Ser-Tyr
*** No translatable DNA found ***
Leu-Asn-Tyr-Ile-Lys-Arg-Ala
Met-Met-Ala
```



---

---
title: "团体队列 Team Queue"
layout: "post"
diff: 普及/提高-
pid: UVA540
tag: ['模拟', '队列']
---

# 团体队列 Team Queue

## 题目描述

有 $t$ 个团队的人正在排长队。每有一个新来的人时，他会从队首开始向后搜寻，如果发现有队友正在排队，他就会插队到他队友的身后；如果没有发现任何一个队友排队，他就只好站在长队的队尾。

输入每个团队中所有队员的编号，要求支持如下 $3$ 种指令：

`ENQUEUE x`：编号为 $x$ 的人进入长队。

`DEQUEUE`：长队的队首出队。

`STOP`：停止模拟。

对于每个 `DEQUEUE` 指令，输出出队的人的编号。

## 输入格式

有多种测试数据，每组的数据的第一行为一个整数 $t$ （$1 \le t \le 1000$），表示有 $t$ 个团队。随后 $t$ 行描述每一个团队，即每一个团队有一个表示该团队人数的整数 $n$ （可能多达 $1000$ 个）和 $n$ 个整数编号（范围为 $0$ ~ $999999$）。

随后是指令列表（可能多达 $200000$ 条指令），有如题所示 $3$ 种不同的指令。

## 输出格式

对应每组测试数据，首先输出一行 `Scenario #k`，其中 $k$ 表示第几次测试；然后每一个 `DEQUEUE` 指令打印出队的人的编号（单独占一行）。

在每一组测试时局之后打印一空行，即使这组测试数据是最后一组。

## 样例 #1

### 输入

```
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
2
5 259001 259002 259003 259004 259005
6 260001 260002 260003 260004 260005 260006
ENQUEUE 259001
ENQUEUE 260001
ENQUEUE 259002
ENQUEUE 259003
ENQUEUE 259004
ENQUEUE 259005
DEQUEUE
DEQUEUE
ENQUEUE 260002
ENQUEUE 260003
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0
```

### 输出

```
Scenario #1
101
102
103
201
202
203

Scenario #2
259001
259002
259003
259004
259005
260001
```



---

---
title: "Bridge Hands"
layout: "post"
diff: 普及/提高-
pid: UVA555
tag: ['模拟', '排序']
---

# Bridge Hands

## 题目描述

一副扑克牌，除去大小王后还有 $52$ 张。

我们定义扑克牌的大小比较为：

如果花色不同，则梅花 $<$ 方块 $<$ 黑桃 $<$ 红桃。

此处，我们将梅花写作 $\text{C}$，方块写作 $\text{D}$，黑桃写作 $\text{S}$，红桃写作 $\text{H}$。

如果花色相同，则 $2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < \text{J} < \text{Q} < \text{K} < \text{A}$。

此处我们将 $10$ 写作 $\text{T}$，$\text{J}$、$\text{Q}$、$\text{K}$、$\text{A}$保持原来的写法。

一张牌由其花色和牌点组成，即，红桃 $10$ 被我们表示成 $\text{HT}$，黑桃 $4$ 被我们表示成 $\text{S4}$，以此类推。

注意，以上有涉及到字母的均为大写字母。

现在有一种四个人的游戏是用一副去掉大小王后的扑克牌玩的。四个人分别被表示成南，西，北，东。每一轮都有一个庄家，发牌时从庄家的顺时针方向下一位选手开始发牌，然后按顺时针发牌直至牌被发光，此时每个人手里的牌数相同，为 $13$ 张。

此处默认：南的顺时针方向一位是西，西的顺时针方向一位是北，北的顺时针方向一位是东，东的顺时针方向一位是南。南、西、北、东分别用 $\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 来表示。

现在给定牌堆和庄家，请求出每位玩家的手牌**排序后**的结果。排序方法参照上部。

## 输入格式

**本题多测。**

对于每组数据，第一行一个字符 $c$，代表庄家。$c$ 只能是$\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 或 $#$。当输入到 $#$ 时结束程序。

接下来**两行两个**字符串，代表牌堆。注意，每**两个字符**代表一张牌。上面一行的牌堆会比下面一行的牌堆先被发出。

## 输出格式

对于每组数据，按照 $\text{S}$、$\text{W}$、$\text{N}$、$\text{E}$ 的顺序输出，一行一位选手。对于每一行输出形如 `c: a[1] a[2] a[3] a[4] a[5] a[6] a[7] a[8] a[9] a[10] a[11] a[12] a[13]`，其中 $c$ 代表选手，$a_i$ 代表该选手**排序后的**第 $i$ 张牌。

## 样例 #1

### 输入

```
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#
```

### 输出

```
S: C3 C5 C7 CT CJ D9 DT DJ S3 SK H2 H9 HT
W: C2 C4 CK D4 D5 D6 DQ DA S4 S8 ST SJ H8
N: C6 C8 C9 CA D8 S9 SA H4 H5 H6 H7 HJ HA
E: CQ D2 D3 D7 DK S2 S5 S6 S7 SQ H3 HQ HK
```



---



---

# 题号列表

- UVA101 - The Blocks Problem
- UVA10815 - 安迪的第一个字典 Andy's First Dictionary
- UVA10954 - 全部相加 Add All
- UVA11210 - Chinese Mahjong
- UVA11995 - I Can Guess the Data Structure!
- UVA126 - The Errant Physicist
- UVA130 - Roman Roulette
- UVA151 - Power Crisis
- UVA213 - 信息解码 Message Decoding
- UVA227 - 谜题 Puzzle
- UVA385 - DNA Translation
- UVA540 - 团体队列 Team Queue
- UVA555 - Bridge Hands


---

---
title: "Ecological Bin Packing"
layout: "post"
diff: 普及/提高-
pid: UVA102
tag: ['字符串', '枚举', '深度优先搜索 DFS']
---

# Ecological Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=38

[PDF](https://uva.onlinejudge.org/external/1/p102.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ef84892469f793327bfb4a3ea04e4237b1761a6d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/ae3b90e524e6ffd7e27eab05a64abfd8be7111ef.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA102/249702f9f5f1e91446cb32d9b3ad6a7eca7264f5.png)

## 样例 #1

### 输入

```
1 2 3 4 5 6 7 8 9
5 10 5 20 10 5 10 20 10
```

### 输出

```
BCG 30
CBG 50
```



---

---
title: "Square"
layout: "post"
diff: 普及/提高-
pid: UVA10364
tag: ['深度优先搜索 DFS']
---

# Square

## 题目描述

给定 $N$ 根木棍，每根木棍的长度为 $x$ 。

尝试用所有的木棍围成一个正方形。

## 输入格式

第一行输入一个整数 $T$，代表 $T$ 组数据。

接下来 $T$ 行，每行开头输入一个整数 $N$，即有 $N$ 根木棍，接着输入 $N$ 个整数代表每根木棍的长度。

## 输出格式

$T$ 行，每行输出一个字符串，若能围成正方形，输出 ``yes``，否则输出 ``no``。

## 样例 #1

### 输入

```
3
4 1 1 1 1
5 10 20 30 40 50
8 1 7 2 6 4 4 3 5
```

### 输出

```
yes
no
yes
```



---

---
title: "素数环 Prime Ring Problem"
layout: "post"
diff: 普及/提高-
pid: UVA524
tag: ['搜索', '深度优先搜索 DFS', '素数判断,质数,筛法']
---

# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/564d6b149cca77cbaf1583cf2a35822a0f78251c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/3944acd7f0b0909cb25a01cbb113e5507c6e3a72.png)

## 样例 #1

### 输入

```
6
8
```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2
```



---



---

# 题号列表

- UVA102 - Ecological Bin Packing
- UVA10364 - Square
- UVA524 - 素数环 Prime Ring Problem


---

---
title: "Arctic Network"
layout: "post"
diff: 普及/提高-
pid: UVA10369
tag: ['并查集', '生成树']
---

# Arctic Network

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1310

[PDF](https://uva.onlinejudge.org/external/103/p10369.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/b3c41b35e81b308ad9ef5826dfa39b5f526836c1.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/1fed2f028e09206e67a50d94d47eca7ea0360586.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/08973cd15c06ad71bc58f70cc9dd85f12476e242.png)

## 样例 #1

### 输入

```
1
2 4
0 100
0 300
0 600
150 750
```

### 输出

```
212.13
```



---

---
title: "Dark roads"
layout: "post"
diff: 普及/提高-
pid: UVA11631
tag: ['生成树']
---

# Dark roads

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2678

[PDF](https://uva.onlinejudge.org/external/116/p11631.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11631/3b6d8ed066db76a33df958a6c0c60e1de6f08826.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11631/7734ca5ac043999aba0dd88070cb0666c4ceb068.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11631/1ed1cc0f3f59d366bbd1502cdf64865f590a4679.png)

## 样例 #1

### 输入

```
7 11
0 1 7
0 3 5
1 2 8
1 3 9
1 4 7
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11
0 0
```

### 输出

```
51
```



---



---

# 题号列表

- UVA10369 - Arctic Network
- UVA11631 - Dark roads


---

---
title: "Prime Distance"
layout: "post"
diff: 普及/提高-
pid: UVA10140
tag: ['枚举', '素数判断,质数,筛法']
---

# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/9848cf59ee0ece9e1a0dfd40a08e689a1c5c6604.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/6760a091328104551b134bb6b39accf505df0484.png)

## 样例 #1

### 输入

```
2 17
14 17
```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.
```



---

---
title: "Simply Emirp"
layout: "post"
diff: 普及/提高-
pid: UVA10235
tag: ['数论', '素数判断,质数,筛法']
---

# Simply Emirp

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1176

[PDF](https://uva.onlinejudge.org/external/102/p10235.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b3b8ea0ca3590b5800fc5123b088be54c52be882.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/47f9f19dfa96cceb92ba90ea3da8b9b3f734d82c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b48c8f0251bdbc8438a102dbda43364ddd5ec586.png)

## 样例 #1

### 输入

```
17
18
19
179
199
```

### 输出

```
17 is emirp.
18 is not prime.
19 is prime.
179 is emirp.
199 is emirp.
```



---

---
title: "选择与除法 Choose and divide"
layout: "post"
diff: 普及/提高-
pid: UVA10375
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/8ff851cc9926c4165c7c6485311457578bf77f44.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/1dd11724e900842b1855cb026891122b11c4b9c5.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998
```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960
```



---

---
title: "The primary problem"
layout: "post"
diff: 普及/提高-
pid: UVA10948
tag: ['枚举', '素数判断,质数,筛法']
---

# The primary problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1889

[PDF](https://uva.onlinejudge.org/external/109/p10948.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/e8db1ede82953ce1670162c4cb5dde5e02f35076.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/2b712e379782764e7b714ebada6c5d4d4ea8dfab.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/8ef2ba1bb7ff9690621ef3bff83005d37e831f21.png)

## 样例 #1

### 输入

```
4
5
6
7
9
10
11
0
```

### 输出

```
4:
2+2
5:
2+3
6:
3+3
7:
2+5
9:
2+7
10:
3+7
11:
NO WAY!
```



---

---
title: "连续素数之和 Sum of Consecutive Prime Numbers"
layout: "post"
diff: 普及/提高-
pid: UVA1210
tag: ['素数判断,质数,筛法', '前缀和']
---

# 连续素数之和 Sum of Consecutive Prime Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3651

[PDF](https://uva.onlinejudge.org/external/12/p1210.pdf)



---

---
title: "素数间隔 Prime Gap"
layout: "post"
diff: 普及/提高-
pid: UVA1644
tag: ['素数判断,质数,筛法']
---

# 素数间隔 Prime Gap

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4519

[PDF](https://uva.onlinejudge.org/external/16/p1644.pdf)



---

---
title: "素数环 Prime Ring Problem"
layout: "post"
diff: 普及/提高-
pid: UVA524
tag: ['搜索', '深度优先搜索 DFS', '素数判断,质数,筛法']
---

# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/564d6b149cca77cbaf1583cf2a35822a0f78251c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/3944acd7f0b0909cb25a01cbb113e5507c6e3a72.png)

## 样例 #1

### 输入

```
6
8
```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2
```



---

---
title: "Goldbach's Conjecture"
layout: "post"
diff: 普及/提高-
pid: UVA543
tag: ['搜索', '枚举', '素数判断,质数,筛法']
---

# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 输入格式

输入包含多组数据。

每组数据占一行，包含一个偶数 $n(n \le 10^6)$。 读入以 $0$ 结束。

## 输出格式

对于每组数据，输出形如 `n = a + b`，其中 $a,b$ 是奇质数。若有多组满足条件的 $a,b$，输出 $b−a$ 最大的一组。

若无解，输出 `Goldbach's conjecture is wrong.`。

## 样例 #1

### 输入

```
8
20
42
0
```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37
```



---



---

# 题号列表

- UVA10140 - Prime Distance
- UVA10235 - Simply Emirp
- UVA10375 - 选择与除法 Choose and divide
- UVA10948 - The primary problem
- UVA1210 - 连续素数之和 Sum of Consecutive Prime Numbers
- UVA1644 - 素数间隔 Prime Gap
- UVA524 - 素数环 Prime Ring Problem
- UVA543 - Goldbach's Conjecture


---

---
title: "Prime Distance"
layout: "post"
diff: 普及/提高-
pid: UVA10140
tag: ['枚举', '素数判断,质数,筛法']
---

# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/9848cf59ee0ece9e1a0dfd40a08e689a1c5c6604.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/6760a091328104551b134bb6b39accf505df0484.png)

## 样例 #1

### 输入

```
2 17
14 17
```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.
```



---

---
title: "Simply Emirp"
layout: "post"
diff: 普及/提高-
pid: UVA10235
tag: ['数论', '素数判断,质数,筛法']
---

# Simply Emirp

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1176

[PDF](https://uva.onlinejudge.org/external/102/p10235.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b3b8ea0ca3590b5800fc5123b088be54c52be882.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/47f9f19dfa96cceb92ba90ea3da8b9b3f734d82c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b48c8f0251bdbc8438a102dbda43364ddd5ec586.png)

## 样例 #1

### 输入

```
17
18
19
179
199
```

### 输出

```
17 is emirp.
18 is not prime.
19 is prime.
179 is emirp.
199 is emirp.
```



---

---
title: "选择与除法 Choose and divide"
layout: "post"
diff: 普及/提高-
pid: UVA10375
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/8ff851cc9926c4165c7c6485311457578bf77f44.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/1dd11724e900842b1855cb026891122b11c4b9c5.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998
```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960
```



---

---
title: "The primary problem"
layout: "post"
diff: 普及/提高-
pid: UVA10948
tag: ['枚举', '素数判断,质数,筛法']
---

# The primary problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1889

[PDF](https://uva.onlinejudge.org/external/109/p10948.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/e8db1ede82953ce1670162c4cb5dde5e02f35076.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/2b712e379782764e7b714ebada6c5d4d4ea8dfab.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/8ef2ba1bb7ff9690621ef3bff83005d37e831f21.png)

## 样例 #1

### 输入

```
4
5
6
7
9
10
11
0
```

### 输出

```
4:
2+2
5:
2+3
6:
3+3
7:
2+5
9:
2+7
10:
3+7
11:
NO WAY!
```



---

---
title: "连续素数之和 Sum of Consecutive Prime Numbers"
layout: "post"
diff: 普及/提高-
pid: UVA1210
tag: ['素数判断,质数,筛法', '前缀和']
---

# 连续素数之和 Sum of Consecutive Prime Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3651

[PDF](https://uva.onlinejudge.org/external/12/p1210.pdf)



---

---
title: "素数间隔 Prime Gap"
layout: "post"
diff: 普及/提高-
pid: UVA1644
tag: ['素数判断,质数,筛法']
---

# 素数间隔 Prime Gap

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4519

[PDF](https://uva.onlinejudge.org/external/16/p1644.pdf)



---

---
title: "素数环 Prime Ring Problem"
layout: "post"
diff: 普及/提高-
pid: UVA524
tag: ['搜索', '深度优先搜索 DFS', '素数判断,质数,筛法']
---

# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/564d6b149cca77cbaf1583cf2a35822a0f78251c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/3944acd7f0b0909cb25a01cbb113e5507c6e3a72.png)

## 样例 #1

### 输入

```
6
8
```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2
```



---

---
title: "Goldbach's Conjecture"
layout: "post"
diff: 普及/提高-
pid: UVA543
tag: ['搜索', '枚举', '素数判断,质数,筛法']
---

# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 输入格式

输入包含多组数据。

每组数据占一行，包含一个偶数 $n(n \le 10^6)$。 读入以 $0$ 结束。

## 输出格式

对于每组数据，输出形如 `n = a + b`，其中 $a,b$ 是奇质数。若有多组满足条件的 $a,b$，输出 $b−a$ 最大的一组。

若无解，输出 `Goldbach's conjecture is wrong.`。

## 样例 #1

### 输入

```
8
20
42
0
```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37
```



---



---

# 题号列表

- UVA10140 - Prime Distance
- UVA10235 - Simply Emirp
- UVA10375 - 选择与除法 Choose and divide
- UVA10948 - The primary problem
- UVA1210 - 连续素数之和 Sum of Consecutive Prime Numbers
- UVA1644 - 素数间隔 Prime Gap
- UVA524 - 素数环 Prime Ring Problem
- UVA543 - Goldbach's Conjecture


---

---
title: "Hats"
layout: "post"
diff: 普及/提高-
pid: UVA12024
tag: ['数学', '组合数学']
---

# Hats

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3175

[PDF](https://uva.onlinejudge.org/external/120/p12024.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/25a75cc3aa1181e89f3439302a46c65776fbdd03.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/6e06f4c8abc36d2c27721c4c1a100d96fdc1440a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/5795feaddca228bb541652bdb5a4f2bf8601a4e5.png)

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
1/2
2/6
9/24
```



---



---

# 题号列表

- UVA12024 - Hats


---

---
title: "Hats"
layout: "post"
diff: 普及/提高-
pid: UVA12024
tag: ['数学', '组合数学']
---

# Hats

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=242&page=show_problem&problem=3175

[PDF](https://uva.onlinejudge.org/external/120/p12024.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/25a75cc3aa1181e89f3439302a46c65776fbdd03.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/6e06f4c8abc36d2c27721c4c1a100d96fdc1440a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA12024/5795feaddca228bb541652bdb5a4f2bf8601a4e5.png)

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
1/2
2/6
9/24
```



---



---

# 题号列表

- UVA12024 - Hats


---

---
title: "Prime Distance"
layout: "post"
diff: 普及/提高-
pid: UVA10140
tag: ['枚举', '素数判断,质数,筛法']
---

# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/9848cf59ee0ece9e1a0dfd40a08e689a1c5c6604.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/6760a091328104551b134bb6b39accf505df0484.png)

## 样例 #1

### 输入

```
2 17
14 17
```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.
```



---

---
title: "Simply Emirp"
layout: "post"
diff: 普及/提高-
pid: UVA10235
tag: ['数论', '素数判断,质数,筛法']
---

# Simply Emirp

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1176

[PDF](https://uva.onlinejudge.org/external/102/p10235.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b3b8ea0ca3590b5800fc5123b088be54c52be882.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/47f9f19dfa96cceb92ba90ea3da8b9b3f734d82c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b48c8f0251bdbc8438a102dbda43364ddd5ec586.png)

## 样例 #1

### 输入

```
17
18
19
179
199
```

### 输出

```
17 is emirp.
18 is not prime.
19 is prime.
179 is emirp.
199 is emirp.
```



---

---
title: "选择与除法 Choose and divide"
layout: "post"
diff: 普及/提高-
pid: UVA10375
tag: ['数学', '素数判断,质数,筛法', '概率论']
---

# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/8ff851cc9926c4165c7c6485311457578bf77f44.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/1dd11724e900842b1855cb026891122b11c4b9c5.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998
```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960
```



---

---
title: "The primary problem"
layout: "post"
diff: 普及/提高-
pid: UVA10948
tag: ['枚举', '素数判断,质数,筛法']
---

# The primary problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1889

[PDF](https://uva.onlinejudge.org/external/109/p10948.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/e8db1ede82953ce1670162c4cb5dde5e02f35076.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/2b712e379782764e7b714ebada6c5d4d4ea8dfab.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/8ef2ba1bb7ff9690621ef3bff83005d37e831f21.png)

## 样例 #1

### 输入

```
4
5
6
7
9
10
11
0
```

### 输出

```
4:
2+2
5:
2+3
6:
3+3
7:
2+5
9:
2+7
10:
3+7
11:
NO WAY!
```



---

---
title: "连续素数之和 Sum of Consecutive Prime Numbers"
layout: "post"
diff: 普及/提高-
pid: UVA1210
tag: ['素数判断,质数,筛法', '前缀和']
---

# 连续素数之和 Sum of Consecutive Prime Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3651

[PDF](https://uva.onlinejudge.org/external/12/p1210.pdf)



---

---
title: "素数间隔 Prime Gap"
layout: "post"
diff: 普及/提高-
pid: UVA1644
tag: ['素数判断,质数,筛法']
---

# 素数间隔 Prime Gap

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4519

[PDF](https://uva.onlinejudge.org/external/16/p1644.pdf)



---

---
title: "素数环 Prime Ring Problem"
layout: "post"
diff: 普及/提高-
pid: UVA524
tag: ['搜索', '深度优先搜索 DFS', '素数判断,质数,筛法']
---

# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/564d6b149cca77cbaf1583cf2a35822a0f78251c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/3944acd7f0b0909cb25a01cbb113e5507c6e3a72.png)

## 样例 #1

### 输入

```
6
8
```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2
```



---

---
title: "Goldbach's Conjecture"
layout: "post"
diff: 普及/提高-
pid: UVA543
tag: ['搜索', '枚举', '素数判断,质数,筛法']
---

# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 输入格式

输入包含多组数据。

每组数据占一行，包含一个偶数 $n(n \le 10^6)$。 读入以 $0$ 结束。

## 输出格式

对于每组数据，输出形如 `n = a + b`，其中 $a,b$ 是奇质数。若有多组满足条件的 $a,b$，输出 $b−a$ 最大的一组。

若无解，输出 `Goldbach's conjecture is wrong.`。

## 样例 #1

### 输入

```
8
20
42
0
```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37
```



---



---

# 题号列表

- UVA10140 - Prime Distance
- UVA10235 - Simply Emirp
- UVA10375 - 选择与除法 Choose and divide
- UVA10948 - The primary problem
- UVA1210 - 连续素数之和 Sum of Consecutive Prime Numbers
- UVA1644 - 素数间隔 Prime Gap
- UVA524 - 素数环 Prime Ring Problem
- UVA543 - Goldbach's Conjecture


---

---
title: "Shoemaker's Problem"
layout: "post"
diff: 普及/提高-
pid: UVA10026
tag: ['贪心', '排序']
---

# Shoemaker's Problem

## 题目描述

有 $n$ 个任务，每个任务从接手开始每分钟罚款 $S_i$ 元，直到完成任务为止。然而每个任务需要花 $T_i$ 的时间去完成。你只能把一件任务完成才能去做下一件事情，问如何安排任务处理顺序，使得总罚款最小。注意，每个任务在第 $0$ 时刻就全部交给了你。

## 输入格式

第一行一个整数 $T$，表示多组测试数据数量。

对于每组数据，一个整数 $n$ 表示任务数量，接下来 $n$ 行每行两个整数 $T_i$ 和 $S_i$。

## 输出格式

每个多组数据，输出对应的安排顺序，若存在多种方案，请输出字典序最小的一个。

**注意相邻两个多组测试点中间需要隔一个空行**

## 样例 #1

### 输入

```
1
4
3 4
1 1000
2 2
5 5
```

### 输出

```
2 1 3 4
```



---

---
title: "Maximum Sum"
layout: "post"
diff: 普及/提高-
pid: UVA108
tag: ['贪心', '枚举', '前缀和']
---

# Maximum Sum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=44

[PDF](https://uva.onlinejudge.org/external/1/p108.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/9bad502ba34d25d0111329e7b191a1e73f37eafb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/396f13d4868ef41457d1488f0abfd926a952de29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA108/68309ab00fee7fe7c208d797f30252388b43c04b.png)

## 样例 #1

### 输入

```
4
0 -2 -7 0 
9 2 -6 2
-4 1 -4 1 
-1 8 0 -2
```

### 输出

```
15
```



---

---
title: "Radar Installation"
layout: "post"
diff: 普及/提高-
pid: UVA1193
tag: ['贪心', '排序', '优先队列']
---

# Radar Installation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3634

[PDF](https://uva.onlinejudge.org/external/11/p1193.pdf)

## 样例 #1

### 输入

```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---



---

# 题号列表

- UVA10026 - Shoemaker's Problem
- UVA108 - Maximum Sum
- UVA1193 - Radar Installation


---

---
title: "Software CRC"
layout: "post"
diff: 普及/提高-
pid: UVA128
tag: ['字符串', '递推', '进制']
---

# Software CRC

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=64

[PDF](https://uva.onlinejudge.org/external/1/p128.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/2ed0a2961b881ebefab6464e3345553e002df0c8.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/bfbdaaa48bb848a17ac2a5ab1bcae82f4ecb4334.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/48234fb6a73fd634750ac85257ec7843b5e06d8d.png)

## 样例 #1

### 输入

```
this is a test
A
#
```

### 输出

```
77 FD
00 00
0C 86
```



---

---
title: "数据库 Database"
layout: "post"
diff: 普及/提高-
pid: UVA1592
tag: ['字符串', '枚举', '进制']
---

# 数据库 Database

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4467

[PDF](https://uva.onlinejudge.org/external/15/p1592.pdf)



---

---
title: "信息解码 Message Decoding"
layout: "post"
diff: 普及/提高-
pid: UVA213
tag: ['模拟', '字符串', '进制']
---

# 信息解码 Message Decoding

## 题目描述

考虑下面的01串序列：
```
0，00，01，10，000，001，010，011，100，101，110，0000，0001，···，1101，1110，00000，···
```
首先是长度为1的串，然后是长度为2的串，依此类推。如果看成二进制，相同长度的后一个串等于前一个串加1。注意上述序列中不存在全为1的串。你的任务是是编写一个解码程序。

## 输出格式

感谢@hedwig 提供的翻译

## 样例 #1

### 输入

```
TNM AEIOU 
0010101100011 
1010001001110110011 
11000 
$#**\ 
0100000101101100011100101000
```

### 输出

```
TAN ME 
##*\$
```



---



---

# 题号列表

- UVA128 - Software CRC
- UVA1592 - 数据库 Database
- UVA213 - 信息解码 Message Decoding


---

---
title: "The Blocks Problem"
layout: "post"
diff: 普及/提高-
pid: UVA101
tag: ['模拟', '递归', '栈']
---

# The Blocks Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=37

[PDF](https://uva.onlinejudge.org/external/1/p101.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/4657c698576c8c299dbbf5655d7dbe63bf148978.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/0a0a9b4a15235d9e81d83d5d31ee89ce48870fed.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/ca24bcd0ff3af9dc6c1fcefd73c87532e9e05bd4.png)

## 样例 #1

### 输入

```
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit
```

### 输出

```
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:
```



---

---
title: "Tree Summing"
layout: "post"
diff: 普及/提高-
pid: UVA112
tag: ['递归']
---

# Tree Summing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=48

[PDF](https://uva.onlinejudge.org/external/1/p112.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA112/ee9b47e479d70c22d369ddb505af41da0aebc120.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA112/ed3ab11220fdaedeaca0d5d0762506623d0211e6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA112/7bc6b3b19fdaeb2394c8263c567feae640a649bc.png)

## 样例 #1

### 输入

```
22 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
20 (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
10 (3
(2 (4 () () )
(8 () () ) )
(1 (6 () () )
(4 () () ) ) )
5 ()
```

### 输出

```
yes
no
yes
no
```



---

---
title: "困难的串 Krypton Factor"
layout: "post"
diff: 普及/提高-
pid: UVA129
tag: ['搜索', '递归']
---

# 困难的串 Krypton Factor

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=65

[PDF](https://uva.onlinejudge.org/external/1/p129.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/acf4a8193efdffb3da55bab10c0c0b1353f2dc09.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/b923e93bcc47c02bfb54e49f8ec2dafc214ee3e7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA129/2bee9ae1cb76c0f477ce304cd2c16b191025d687.png)

## 样例 #1

### 输入

```
7 3
30 3
0 0
```

### 输出

```
ABAC ABA
7
ABAC ABCA CBAB CABA CABC ACBA CABA
28
```



---

---
title: "下落的树叶 The Falling Leaves"
layout: "post"
diff: 普及/提高-
pid: UVA699
tag: ['递归', '树的遍历', '概率论']
---

# 下落的树叶 The Falling Leaves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=640

[PDF](https://uva.onlinejudge.org/external/6/p699.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/735ce6ad24a18ffc8b70b3a6c28998f5211a95ce.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/3915803c372316917ebc2dfce3b293040c414d6d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA699/08403ba4d2bc8dd6492bc2a54f8c6fa4f6769708.png)

## 样例 #1

### 输入

```
5 7 -1 6 -1 -1 3 -1 -1
8 2 9 -1 -1 6 5 -1 -1 12 -1
-1 3 7 -1 -1 -1
-1
```

### 输出

```
Case 1:
7 11 3
Case 2:
9 7 21 15
```



---



---

# 题号列表

- UVA101 - The Blocks Problem
- UVA112 - Tree Summing
- UVA129 - 困难的串 Krypton Factor
- UVA699 - 下落的树叶 The Falling Leaves


---

---
title: "Tiling"
layout: "post"
diff: 普及/提高-
pid: UVA10359
tag: ['高精度', '递推']
---

# Tiling

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1300

[PDF](https://uva.onlinejudge.org/external/103/p10359.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10359/c7428324c83f2f2a32565e9cb9de7f4a9dd6d8c6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10359/5f7d6b3b875b531dbf04d2935d796899bac60e80.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10359/a48066612c927701f185de27df3bc0182f5c2d17.png)

## 样例 #1

### 输入

```
2
8
12
100
200
```

### 输出

```
3
171
2731
845100400152152934331135470251
1071292029505993517027974728227441735014801995855195223534251
```



---

---
title: "Software CRC"
layout: "post"
diff: 普及/提高-
pid: UVA128
tag: ['字符串', '递推', '进制']
---

# Software CRC

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=64

[PDF](https://uva.onlinejudge.org/external/1/p128.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/2ed0a2961b881ebefab6464e3345553e002df0c8.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/bfbdaaa48bb848a17ac2a5ab1bcae82f4ecb4334.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA128/48234fb6a73fd634750ac85257ec7843b5e06d8d.png)

## 样例 #1

### 输入

```
this is a test
A
#
```

### 输出

```
77 FD
00 00
0C 86
```



---



---

# 题号列表

- UVA10359 - Tiling
- UVA128 - Software CRC


---

---
title: "全部相加 Add All"
layout: "post"
diff: 普及/提高-
pid: UVA10954
tag: ['模拟', '优先队列', '队列']
---

# 全部相加 Add All

## 题目描述

## 题意翻译
给你 $n$ 个数，求将这 $n$ 个数合并成一个数的成本（成本即为此次相加之和）的最小值。

## 输入格式

本题多测，每组数据的第一行为 $n$，然后一行 $n$ 个整数，表示需要合并的数据。当 $n=0$ 时，表示输入结束。

## 输出格式

一行一个整数，表示成本的最小值。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^3$，$1 \leq a_i \leq 10^{5}$。

## 样例 #1

### 输入

```
3
1 2 3
4
1 2 3 4
0
```

### 输出

```
9
19
```



---

---
title: "Open Credit System"
layout: "post"
diff: 普及/提高-
pid: UVA11078
tag: ['枚举', '优先队列']
---

# Open Credit System

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2019

[PDF](https://uva.onlinejudge.org/external/110/p11078.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/25cd6848e8285209c3495ee0e4d8dbf426b85add.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/026441a9548841bf934643d0c612606f5cd27fd5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11078/94f6757afbd3bba1db2ec9c49cc54dadb565959d.png)

## 样例 #1

### 输入

```
3
2
100
20
4
4
3
2
1
4
1
2
3
4
```

### 输出

```
80
3
-1
```



---

---
title: "Radar Installation"
layout: "post"
diff: 普及/提高-
pid: UVA1193
tag: ['贪心', '排序', '优先队列']
---

# Radar Installation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3634

[PDF](https://uva.onlinejudge.org/external/11/p1193.pdf)

## 样例 #1

### 输入

```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---

---
title: "I Can Guess the Data Structure!"
layout: "post"
diff: 普及/提高-
pid: UVA11995
tag: ['模拟', '栈', '队列']
---

# I Can Guess the Data Structure!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3146

[PDF](https://uva.onlinejudge.org/external/119/p11995.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/55cb8a2c5cf1532ff4a8dff640c7538c0998c78c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/85c08a1b2399e94d2f430010d18cb8c7c42d2ddd.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/ca430d6d3039e2b5f45d99cd031ba66a1656ade0.png)

## 样例 #1

### 输入

```
6
1 1
1 2
1 3
2 1
2 2
2 3
6
1 1
1 2
1 3
2 3
2 2
2 1
2
1 1
2 2
4
1 2
1 1
2 1
2 2
7
1 2
1 5
1 1
1 3
2 5
1 4
2 4
```

### 输出

```
queue
not sure
impossible
stack
priority queue
```



---

---
title: "Argus"
layout: "post"
diff: 普及/提高-
pid: UVA1203
tag: ['优先队列', '队列']
---

# Argus

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3644

[PDF](https://uva.onlinejudge.org/external/12/p1203.pdf)



---

---
title: "Power Crisis"
layout: "post"
diff: 普及/提高-
pid: UVA151
tag: ['模拟', '枚举', '队列']
---

# Power Crisis

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=87

[PDF](https://uva.onlinejudge.org/external/1/p151.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/2b7fc9e4df48b383902b9f5285f0316b5f437407.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/e69ea5e0da52f9c6b45414318b78dab4f5faf403.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA151/47bd9da34308490bfea1a9eb4e0baa05fdd433d1.png)

## 样例 #1

### 输入

```
17
0
```

### 输出

```
7
```



---

---
title: "Domino Effect"
layout: "post"
diff: 普及/提高-
pid: UVA318
tag: ['优先队列', '最短路']
---

# Domino Effect

## 题目描述

@[lin_toto](/space/show?uid=256)

题目名字：多米诺骨牌效应

您是否知道多米诺骨牌除了玩之外还可以用来做其他事情？拿一些多米诺骨牌，然后将它们排成一排，并在它们之间只留一小段距离。如果你做得对，你可以推倒第一张多米诺骨牌并使所有其他的多米诺骨牌依次倒下（这就是“多米诺骨牌效应”的由来）。

数量太少的多米诺骨牌有点毫无意义，所以有些人在八十年代初就走向了相反的极端。他们使用数以百万计的不同颜色和材料的多米诺骨牌，用倒下的精美多米诺骨牌组成的图案填满整个大厅，来创造（短命的）艺术品。在这些过程中，通常不只有一排多米诺骨牌同时倒下。你可以发现，时间是一个重要的影响因素。 

现在你的任务是编写一个程序，给定由多米诺骨牌组成的系统，计算最后一个多米诺骨牌在何时何地倒下。该系统由几个简单的关键多米诺骨牌和其之间的多米诺骨牌连接而成。当一个关键的多米诺骨牌倒下时，连接到该关键多米诺骨牌的所有多米诺骨牌都开始倒下（除了那些已经倒下的多米诺骨牌）。当倒下的多米诺骨牌到达尚未倒下的其他关键多米诺骨牌时，这些关键多米诺骨牌也会倒下并且引起与它们相连的多米诺骨牌开始倒下。多米诺骨牌行可能会从任何一端开始倒下。甚至有可能同一多米诺骨牌行从两端开始倒下，在这种情况下，该行倒下的最后一张多米诺骨牌位于其行两端的关键多米诺骨牌之间。您可以假设行中的多米诺骨牌以均匀的速度倒下。

## 输入格式

输入文件包含几个多米诺骨牌系统的描述。每个描述的第一行包含两个整数：关键多米诺骨牌的数量n（1 <= n <500）和它们之间的行数m。关键的多米诺骨牌从1到n编号。在任何一对关键多米诺骨牌之间至多有一行并且多米诺骨牌图是连通的，即至少有一种方法可以通过多米诺骨牌行从一个关键多米诺骨牌到达任何其他多米诺骨牌。 

以下m行每行包含三个整数a，b和l，表示在关键的多米诺骨牌a和b之间有一行，从一端到另一端需要l秒。 

每个系统都是通过翻推倒编号为1的多米诺骨牌来启动的。 

文件以一组空的多米诺骨牌系统（n = m = 0）结束，你不应该处理此组数据。

## 输出格式

对于每组数据，输出一行说明数据的编号（'System ＃1'，'System ＃2'等）。然后输出一行，其中包含最后一张多米诺骨牌落下的时间，精确到小数点后一位数，以及最后一张多米诺骨牌倒下的位置，这个位置为某个关键多米诺骨牌或两个关键多米诺骨牌之间（在这种情况下 ，按升序输出两个关键多米诺骨牌编号）。按照输出示例的格式输出。输入保证只有一个解决方案。**在每组数据后输出一个空行。**

## 样例 #1

### 输入

```
2 1
1 2 27
3 3
1 2 5
1 3 5
2 3 5
0 0
```

### 输出

```
System #1
The last domino falls after 27.0 seconds, at key domino 2.
System #2
The last domino falls after 7.5 seconds, between key dominoes 2 and 3.
```



---

---
title: "骑士的移动 Knight Moves"
layout: "post"
diff: 普及/提高-
pid: UVA439
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# 骑士的移动 Knight Moves

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=380

[PDF](https://uva.onlinejudge.org/external/4/p439.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/49281f2a839995de267463a506fc7b04652bcf4a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/f986ca9c080d4c2fa5952f61f878eaafe27fdf4b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA439/e3265edbb46489790ff00e32193564840a6de7fe.png)

## 样例 #1

### 输入

```
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
```

### 输出

```
To get from e2 to e4 takes 2 knight moves.
To get from a1 to b2 takes 4 knight moves.
To get from b2 to c3 takes 2 knight moves.
To get from a1 to h8 takes 6 knight moves.
To get from a1 to h7 takes 5 knight moves.
To get from h8 to a1 takes 6 knight moves.
To get from b1 to c3 takes 1 knight moves.
To get from f6 to f6 takes 0 knight moves.
```



---

---
title: "Dungeon Master"
layout: "post"
diff: 普及/提高-
pid: UVA532
tag: ['搜索', '广度优先搜索 BFS', '队列']
---

# Dungeon Master

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=473

[PDF](https://uva.onlinejudge.org/external/5/p532.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/f5204064f9aec4c41d412eb29fbc006dac1f717c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/bc032dafb23822eecdf0192d86ea58ddcaa98ec5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/30d36b3bfe984f90284eb870b4006708e8229767.png)

## 样例 #1

### 输入

```
3 4 5
S....
.###.
.##..
###.#
#####
#####
##.##
##...
#####
#####
#.###
####E
1 3 3
S##
#E#
###
0 0 0
```

### 输出

```
Escaped in 11 minute(s).
Trapped!
```



---

---
title: "团体队列 Team Queue"
layout: "post"
diff: 普及/提高-
pid: UVA540
tag: ['模拟', '队列']
---

# 团体队列 Team Queue

## 题目描述

有 $t$ 个团队的人正在排长队。每有一个新来的人时，他会从队首开始向后搜寻，如果发现有队友正在排队，他就会插队到他队友的身后；如果没有发现任何一个队友排队，他就只好站在长队的队尾。

输入每个团队中所有队员的编号，要求支持如下 $3$ 种指令：

`ENQUEUE x`：编号为 $x$ 的人进入长队。

`DEQUEUE`：长队的队首出队。

`STOP`：停止模拟。

对于每个 `DEQUEUE` 指令，输出出队的人的编号。

## 输入格式

有多种测试数据，每组的数据的第一行为一个整数 $t$ （$1 \le t \le 1000$），表示有 $t$ 个团队。随后 $t$ 行描述每一个团队，即每一个团队有一个表示该团队人数的整数 $n$ （可能多达 $1000$ 个）和 $n$ 个整数编号（范围为 $0$ ~ $999999$）。

随后是指令列表（可能多达 $200000$ 条指令），有如题所示 $3$ 种不同的指令。

## 输出格式

对应每组测试数据，首先输出一行 `Scenario #k`，其中 $k$ 表示第几次测试；然后每一个 `DEQUEUE` 指令打印出队的人的编号（单独占一行）。

在每一组测试时局之后打印一空行，即使这组测试数据是最后一组。

## 样例 #1

### 输入

```
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
2
5 259001 259002 259003 259004 259005
6 260001 260002 260003 260004 260005 260006
ENQUEUE 259001
ENQUEUE 260001
ENQUEUE 259002
ENQUEUE 259003
ENQUEUE 259004
ENQUEUE 259005
DEQUEUE
DEQUEUE
ENQUEUE 260002
ENQUEUE 260003
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0
```

### 输出

```
Scenario #1
101
102
103
201
202
203

Scenario #2
259001
259002
259003
259004
259005
260001
```



---



---

# 题号列表

- UVA10954 - 全部相加 Add All
- UVA11078 - Open Credit System
- UVA1193 - Radar Installation
- UVA11995 - I Can Guess the Data Structure!
- UVA1203 - Argus
- UVA151 - Power Crisis
- UVA318 - Domino Effect
- UVA439 - 骑士的移动 Knight Moves
- UVA532 - Dungeon Master
- UVA540 - 团体队列 Team Queue


---

---
title: "Tiling"
layout: "post"
diff: 普及/提高-
pid: UVA10359
tag: ['高精度', '递推']
---

# Tiling

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1300

[PDF](https://uva.onlinejudge.org/external/103/p10359.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10359/c7428324c83f2f2a32565e9cb9de7f4a9dd6d8c6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10359/5f7d6b3b875b531dbf04d2935d796899bac60e80.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10359/a48066612c927701f185de27df3bc0182f5c2d17.png)

## 样例 #1

### 输入

```
2
8
12
100
200
```

### 输出

```
3
171
2731
845100400152152934331135470251
1071292029505993517027974728227441735014801995855195223534251
```



---

---
title: "Big Number"
layout: "post"
diff: 普及/提高-
pid: UVA1185
tag: ['数学', '高精度']
---

# Big Number

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3626

[PDF](https://uva.onlinejudge.org/external/11/p1185.pdf)



---

---
title: "Integer Inquiry"
layout: "post"
diff: 普及/提高-
pid: UVA424
tag: ['字符串', '高精度']
---

# Integer Inquiry

## 题目描述

BIT 的新超级计算机的第一批用户之一是 Chip Diller。他将他对 $3$ 的幂的探索扩展到了从 $0$ 到 $333$ 的范围，并研究了这些数字的各种和。

“这台超级计算机真棒，”Chip 说。“我只希望 Timothy 能在这里看到这些结果。”

（Chip 搬到了一个新公寓，一旦第三街 Lemon Sky 公寓三楼有空房，他就搬了进去。）

## 输入格式

输入最多包含 $100$ 行文本，每行包含一个非常大的整数。每个非常大的整数的长度不超过 $100$ 个字符，并且只包含数字（不会有负数）。

最后一行输入将仅包含一个单独的零。

## 输出格式

你的程序应该输出输入中给出的非常大的整数之和。

---

Translated by User 735713.

## 样例 #1

### 输入

```
123456789012345678901234567890
123456789012345678901234567890
123456789012345678901234567890
0
```

### 输出

```
370370367037037036703703703670
```



---



---

# 题号列表

- UVA10359 - Tiling
- UVA1185 - Big Number
- UVA424 - Integer Inquiry


---

---
title: "传说中的车 Fabled Rooks"
layout: "post"
diff: 普及+/提高
pid: UVA11134
tag: ['贪心', '排序', '二分图']
---

# 传说中的车 Fabled Rooks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2075

[PDF](https://uva.onlinejudge.org/external/111/p11134.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/bd6c0f2fb7433acc9184472bbe18e9f1a53f823f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/4e1549d0f9cab4c45c78627adabecc71e886e762.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/81fe8f66faa05106571245120e3fbecf732028ae.png)

## 样例 #1

### 输入

```
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
0
```

### 输出

```
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
```



---

---
title: "和为 0 的 4 个值 4 Values whose Sum is 0"
layout: "post"
diff: 普及+/提高
pid: UVA1152
tag: ['二分', '枚举', '排序']
---

# 和为 0 的 4 个值 4 Values whose Sum is 0

## 题目描述

给出四个数组  $A,B,C,D$ ，每个数组中有  $n$  个整数。求有多少组  $i,j,k,l$  满足  $A_i+B_j+C_k+D_l=0$ 。

## 输入格式

**本题有多组测试数据。**

第一行一个正整数  $T$ ，表示数据组数。

对于每组数据:

第一行一个整数  $n$ 。

接下来  $n$  行，一行四个整数，分别表示  $A_i,B_i,C_i,D_i$ 。

## 输出格式

共  $2\times T$  行。

对于每组数据：

第一行一个整数，表示该组测试数据的答案。

接下来输出一个空行。

## 说明/提示

$1\le n\le4000$ 。数组中所有数的绝对值不大于  $2^{28}$ 。



---



---

# 题号列表

- UVA11134 - 传说中的车 Fabled Rooks
- UVA1152 - 和为 0 的 4 个值 4 Values whose Sum is 0


---

---
title: "H(n)"
layout: "post"
diff: 普及+/提高
pid: UVA11526
tag: ['数学', '整除分块']
---

# H(n)

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521

[PDF](https://uva.onlinejudge.org/external/115/p11526.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/9afb4a892766896248d693ae925d518ab86d3d10.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/0f8c27b2e2d3e2232a7828505b7e1038020abc96.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/b8e0b2b685195f97c03927b5f479ece353c14d6f.png)

## 样例 #1

### 输入

```
2
5
10
```

### 输出

```
10
27
```



---



---

# 题号列表

- UVA11526 - H(n)


---

---
title: "City Game"
layout: "post"
diff: 普及+/提高
pid: UVA1330
tag: ['前缀和', '栈']
---

# City Game

## 题目描述

Bob爱上了一个策略游戏（Simcity？）游戏中一个城市由k个地区组成，每个地区都是一块长N×宽M大小的网格矩形,其中可能有些网格已被占用，用R表示;有些则是空地，用F表示。

游戏中可以在空着的空间上建一个矩形的建筑，同时每个建筑按它所占的空地网格数来收租，每占用一个网格可收租金3美元。Bob想知道每个地区中最大面积建筑物能收多少租金。

## 输入格式

第一行是地区个数k。然后接下给出k个地区的相关信息。 相关信息用以下方式输入：

第一行有两个整数n,m (n,m<= 1000),表示这个地区长n宽m

然后接下来有n行，每行m个字符表示网格的信息，相邻的两个用空格隔开。R表示该网格被占用；F表示该网格是空地，可使用。

## 输出格式

对于每一个地区，输出一行一个整数表示该地区中最大面积建筑物能收到的租金。

## 注意

POJ dicuss中有人反映数据输出可能不严格按照要求（例如：两个字符间有多个空格），建议使用cin等读入。

感谢@Rye_Catcher 提供的翻译

## 样例 #1

### 输入

```
3
3 3
R R F
F F F
F R F

5 6
R F F F F F
F R F F F F
F F R F F F
F F F R F F
F F F F R R

4 5
R R R R R
R R F R R
R R R R R
R R F R R
```

### 输出

```
9
27
3
```



---



---

# 题号列表

- UVA1330 - City Game


---

---
title: "Find the Winning Move"
layout: "post"
diff: 普及+/提高
pid: UVA10111
tag: ['剪枝']
---

# Find the Winning Move

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1052

[PDF](https://uva.onlinejudge.org/external/101/p10111.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/ebca7c72e9448d503158b6014fa855835320092f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/9055d46ebcb6e4c4c06061fdb646c962c6876665.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/2157b9dc71543030f751fb8a407ef6974e47cc6d.png)

## 样例 #1

### 输入

```
?
....
.xo.
.ox.
....
?
o...
.ox.
.xxx
xooo
$
```

### 输出

```
#####
(0,1)
```



---

---
title: "Robots on Ice"
layout: "post"
diff: 普及+/提高
pid: UVA1098
tag: ['搜索', '剪枝']
---

# Robots on Ice

## 题目描述

受哈尔滨冰雕的启发，来自北极机器人与自动机大学的参赛队员决定程序竞赛结束后在校园内举办自己的冰雪节。他们打算在冬天结冰的时候，从学校附近的一个湖里获取冰块。为了便于监测湖中冰层的厚度，他们先将湖面网格化，然后安置一个轻巧的机器人逐个方格测量冰层的厚度。在网格中有三个特殊方格被指定为“检查点”，对应着机器人在检查过程中经过整个行程的四分之一、二分之一、四分之三的位置，机器人在这三个特殊“检查点”会发送相应的进度报告。为了避免对冰面造成不必要的磨损和划痕而影响后续的使用，机器人需要从网格左下角坐标为 $(0，0)$ 的方格出发，经过所有方格仅且一次，然后返回位于坐标为 $(0，1)$ 的方格。如果有多种路线符合要求，则机器人每天会使用一条不同的路线。机器人只能沿北、南、东、西四个方向每次移动一个方格。  
给定网格的大小和三个检查点的位置，编写程序确定有多少种不同的检查路线。例如，湖面被划分为 $3 \times 6$ 的网格，三个检查点按访问的顺序分别为 $(2，1)，(2，4)$ 和 $(0，4)$，机器人必须从 $(0，0)$ 方格开始，路经 $18$ 个方格，最后终止于 $(0，1)$ 方格。机器人必须在第 $4（＝\left\lfloor\dfrac{18}{4}\right\rfloor）$ 步的时候经过 $(2，1)$ 方格，在第 $9（＝\left\lfloor\dfrac{18}{2}\right\rfloor）$ 步的时候经过 $(2，4)$ 方格，第 $13（＝\left\lfloor\dfrac{3 \times 18}{4}\right\rfloor）$ 步的时候经过 $(0，4)$ 方格，只有两种路线符合要求，如下图所示。  
![UVA1098 Robots on Ice](https://cdn.luogu.com.cn/upload/image_hosting/vy6tphyl.png)  
需要注意：（1）当网格的大小不是 $4$ 的倍数时，在计算步数时使用整除；（2）某些情况下可能不存在符合要求的路线，例如给定一个 $4 \times 3$的网格，三个检查点分别为 $(2，0)，(3，2)$ 和 $(0，2)$，那么将不存在从 $(0，0)$ 方格出发，结束于 $(0，1)$ 方格且满足要求的路线。

## 输入格式

**本题有多组数据**。  
每组测试数据的第一行包含两个整数 $m$ 和 $n（2 \leq m，n \leq 8）$，表示网格的行数和列数，接着的一行包含六个整数 $r_1，c_1，r_2，c_2，r_3，c_3$，其中 $0 \leq ri ＜ m，0 \leq c_i ＜ n（i＝1，2，3）$。输入的最后一行包含两个 $0$。

## 输出格式

从 $1$ 开始输出测试数据的组数，输出以下不同路线的数量：机器人从行 $0$ 列 $0$ 出发，在行 $0$ 列 $1$ 结束，在第 $\left\lfloor\dfrac{i \times m \times n}{4}\right\rfloor$ 步时经过行 $r_i$ 和列 $c_i（i＝1，2，3）$，能够路经所有方格仅且一次的路线。



---

---
title: "小木棍 Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA307
tag: ['搜索', '枚举', '剪枝']
---

# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/10cd3e738e54e4609c2084fe79f07f05c056540d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/4fe73bdc6626222b0f15df6a62fe404a56935dc3.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
```

### 输出

```
6
5
```



---



---

# 题号列表

- UVA10111 - Find the Winning Move
- UVA1098 - Robots on Ice
- UVA307 - 小木棍 Sticks


---

---
title: "Adventures in Moving - Part IV"
layout: "post"
diff: 普及+/提高
pid: UVA10201
tag: ['动态规划 DP']
---

# Adventures in Moving - Part IV

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1142

[PDF](https://uva.onlinejudge.org/external/102/p10201.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10201/382e6b4004094692dc950c88f7e270509288eaf7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10201/72509a337aae82bc2d3e9d348e2e040972a14fdc.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10201/1a8705f64a570aa029c03817e096ea99574c25a4.png)

## 样例 #1

### 输入

```
1
500
100 999
150 888
200 777
300 999
400 1009
450 1019
500 1399
```

### 输出

```
450550
```



---

---
title: "划分成回文串 Partitioning by Palindromes"
layout: "post"
diff: 普及+/提高
pid: UVA11584
tag: ['字符串', '动态规划 DP', '搜索']
---

# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 输入格式

第一行为正整数t(≤10)，表示数据组数；接下来t行，每行一个完全由小写字母组成的字符串，长度不超过1000。

## 输出格式

对于每组数据，输出最少回文子串数。

由 @C919 提供翻译

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb
```

### 输出

```
1
7
3
```



---

---
title: "单向TSP Unidirectional TSP"
layout: "post"
diff: 普及+/提高
pid: UVA116
tag: ['动态规划 DP', '排序', '最短路']
---

# 单向TSP Unidirectional TSP

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=52

[PDF](https://uva.onlinejudge.org/external/1/p116.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/8f55250e58c560c3ec06a86150f26e2b1e1f75c6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/801aba8894b1c630f564c73247a3de8b316ca7cf.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/f42899d4753927986e0c7f639bd537f5a3da0a4c.png)

## 样例 #1

### 输入

```
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 8 6 4
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 1 2 3
2 2
9 10 9 10
```

### 输出

```
1 2 3 4 4 5
16
1 2 1 5 4 5
11
1 1
19
```



---

---
title: "ICPC Team Strategy"
layout: "post"
diff: 普及+/提高
pid: UVA1240
tag: ['动态规划 DP', '搜索', '状态合并']
---

# ICPC Team Strategy

## 题目描述

ICPC（International Collegiate Programming Contest，国际大学生程序设计比赛），就像你所知道的那样，是大学生抱团参加的程序设计比赛。各个团队由 $3$ 个人组成，而他们将会解决一些程序设计问题。

安迪，布迪和坎达拉计划抱团参加 ICPC，至于团队策略，他们仨想到一个简易策略：

+ 在五个小时的比赛的前二十分钟，他们想要读所有的题目，而后他们三个人每个人给每一道题目标一个数字，即某个人 AC 某道题的最小时间，并且一定会 AC。
+ 每个队伍只有一台电脑，因而让一个队伍同时肝两道题是不可能的。
+ 为避免大脑烧毁或心肺骤停（他们比赛过太多次了），他们决定在每道题后交换角色，这样没有人会连续做两道题目。
+ 他们想要尽量多做题目，做题的顺序则无关紧要。

## 输入格式

$T$ 组数据。每组数据开头为整数 $n(1\le n\le 12)$，代表题目数量。第二行 $n$ 个整数 $a_{1\cdots n}(1\le a_i\le 300)$，代表安迪解每到题需要的时间，第三行和第四行分别是布迪和坎达拉解每到题所需的时间。限制同理。

## 输出格式

对于每组数据，输出一个数字，即团队最大可能解出的题目。

### 样例解释

第一组样例：安迪可以单独解出所有的题目，但是安迪不能连续解两道题。

第二组样例：团队可以解出所有的题目：让布迪解第二道题目，让安迪解第一道题目，让布迪解第三道题目，让坎达拉解最后一道题目，需要 $280$ 分钟。

## 样例 #1

### 输入

```
2
3
100 100 80
190 120 90
120 150 100
4
50 20 300 300
200 100 30 250
140 120 100 100
```

### 输出

```
2
4
```



---

---
title: "Exploring Pyramids"
layout: "post"
diff: 普及+/提高
pid: UVA1362
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---

# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 输入格式

输入包含多组测试数据。

对于每组测试数据：输入一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

对于每组测试数据：输出一行，一个整数表示答案。

## 样例 #1

### 输入

```
ABABABA
AB
```

### 输出

```
5
0
```



---

---
title: "统计问题 The Counting Problem"
layout: "post"
diff: 普及+/提高
pid: UVA1640
tag: ['动态规划 DP', '数位 DP']
---

# 统计问题 The Counting Problem

## 题目描述

给定两个整数 $a$ 和 $b$，求 $a$ 和 $b$ 之间的所有数字中 $0$ ~ $9$ 出现次数。

例如，$a$ = $1024$，$b$ = $1032$，则 $a$ 和 $b$ 之间共有 $9$ 个数如下：

`1024 1025 1026 1027 1028 1029 1030 1031 1032`

其中 `0` 出现 $10$ 次，`1` 出现 $10$ 次，`2` 出现 $7$ 次，`3` 出现 $3$ 次等等……

## 输入格式

输入包含至多 $500$ 行数据。每组输入数据占一行，包含两个整数 $a$ 和 $b$（$0<a,b<100000000$），以 `0 0` 作为结尾，且该行不作处理。

## 输出格式

每组数据输出一个结果，每个结果占一行，包含十个用空格隔开的数字，第一个数字表示 `0` 出现的次数，第二个数字表示 `1` 出现的次数，以此类推。

## 样例 #1

### 输入

```
1 10
44 497
346 542
1199 1748
1496 1403
1004 503
1714 190
1317 854
1976 494
1001 1960
0 0

```

### 输出

```
1 2 1 1 1 1 1 1 1 1
85 185 185 185 190 96 96 96 95 93
40 40 40 93 136 82 40 40 40 40
115 666 215 215 214 205 205 154 105 106
16 113 19 20 114 20 20 19 19 16
107 105 100 101 101 197 200 200 200 200
413 1133 503 503 503 502 502 417 402 412
196 512 186 104 87 93 97 97 142 196
398 1375 398 398 405 499 499 495 488 471
294 1256 296 296 296 296 287 286 286 247
```



---



---

# 题号列表

- UVA10201 - Adventures in Moving - Part IV
- UVA11584 - 划分成回文串 Partitioning by Palindromes
- UVA116 - 单向TSP Unidirectional TSP
- UVA1240 - ICPC Team Strategy
- UVA1362 - Exploring Pyramids
- UVA1640 - 统计问题 The Counting Problem


---

---
title: "这不是bug，而是特性 It's not a Bug, it's a Feature!"
layout: "post"
diff: 普及+/提高
pid: UVA658
tag: ['图论', '最短路', '进制']
---

# 这不是bug，而是特性 It's not a Bug, it's a Feature!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=599

[PDF](https://uva.onlinejudge.org/external/6/p658.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/3980280739ce31d9b96acdbe804068ca33cab9fc.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/7cd2a79ba43bd41cebdbf074b7d149ab2dda68b0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/369bfa04b6ac1cccb3b218de0bdd2f643cf70364.png)

## 样例 #1

### 输入

```
3 3
1 000 00-
1 00- 0-+
2 0-- -++
4 1
7 0-0+ ----
0 0
```

### 输出

```
Product 1
Fastest sequence takes 8 seconds.

Product 2
Bugs cannot be fixed.


```



---



---

# 题号列表

- UVA658 - 这不是bug，而是特性 It's not a Bug, it's a Feature!


---

---
title: "Power Strings"
layout: "post"
diff: 普及+/提高
pid: UVA10298
tag: ['字符串', '枚举', 'KMP 算法']
---

# Power Strings

## 题目描述

### 题意简述：

求一个字符串最多由多少个重复的子串连接而成。

例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由一个 `abcd` 连接而成。

## 输入格式

**本题多组数据**。

每一组数据仅有一行，这一行仅有一个字符串 $s$。

输入的结束标志为一个 `.`。

## 输出格式

对于每一组数据，输出这组字符串最多由多少个重复的子串连接而成。

## 说明/提示

$1\le |s|\le 10^6$。

## 样例 #1

### 输入

```
abcd
aaaa
ababab
.
```

### 输出

```
1
4
3
```



---

---
title: "划分成回文串 Partitioning by Palindromes"
layout: "post"
diff: 普及+/提高
pid: UVA11584
tag: ['字符串', '动态规划 DP', '搜索']
---

# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 输入格式

第一行为正整数t(≤10)，表示数据组数；接下来t行，每行一个完全由小写字母组成的字符串，长度不超过1000。

## 输出格式

对于每组数据，输出最少回文子串数。

由 @C919 提供翻译

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb
```

### 输出

```
1
7
3
```



---

---
title: ""strcmp()" Anyone?"
layout: "post"
diff: 普及+/提高
pid: UVA11732
tag: ['字符串', '概率论', '字典树 Trie']
---

# "strcmp()" Anyone?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2832

[PDF](https://uva.onlinejudge.org/external/117/p11732.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/f9f4156b815a0febb856755194643aee4268928f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/eb2d36585a3a7d37aed581131a6ea2ce899370cb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/8c26b864fca1312c55a0ae313d6d122bb1a75557.png)

## 样例 #1

### 输入

```
2
a
b
4
cat
hat
mat
sir
0
```

### 输出

```
Case 1: 1
Case 2: 6
```



---

---
title: "Period"
layout: "post"
diff: 普及+/提高
pid: UVA1328
tag: ['字符串', 'KMP 算法']
---

# Period

## 题目描述

对于给定字符串 $S$ 的每个前缀，我们想知道它是否为周期串（周期串定义为由若干最小循环节拼接而成的字符串），若是，输出前缀长度和循环节数量。

## 输入格式

多组数据，每组数据第一行一个整数 $n$，表示字符串 $s$ 的长度，若 $n=0$ 则结束输入。

若 $n\ne0$，则第二行一个字符串 $S$，如题意。

## 输出格式

对于第 $i$ 组输出，第一行一个字符串 `Test case #i`。

之后若干行一行两个整数，表示如果字符串 $S$ 的一个前缀是周期串，它的长度和循环节数量（注意这里的循环节是指**长度最小的**循环节）。

之后再空一行。

## 说明/提示

$n\leq10^6$，字符串 $S$ 均由小写字母构成。

## 样例 #1

### 输入

```
3
aaa
12
aabaabaabaab
0

```

### 输出

```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4

```



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---

---
title: "MPI Maelstrom"
layout: "post"
diff: 普及+/提高
pid: UVA423
tag: ['字符串']
---

# MPI Maelstrom

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=364

[PDF](https://uva.onlinejudge.org/external/4/p423.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/620b48e988d4826466e382f01c3dcee7d7e821bf.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/3df347ad588012e63a8fca84f52ca55091b02457.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/03cc7c4b3dd0f07be6457141bd0530655ffc8c03.png)

## 样例 #1

### 输入

```
5
50
30 5
100 20 50
10 x x 10
```

### 输出

```
35
```



---

---
title: "Immediate Decodability"
layout: "post"
diff: 普及+/提高
pid: UVA644
tag: ['字符串', '字典树 Trie']
---

# Immediate Decodability

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=585

[PDF](https://uva.onlinejudge.org/external/6/p644.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/ef8ec58ea23c0b0f28ccca6a9cb8b526b259834f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/0ee74805dbc651412fb0404c157882e6ec4e2061.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/7baa231aedb25634c7086f9142d101700faddf53.png)

## 样例 #1

### 输入

```
01
10
0010
0000
9
01
10
010
0000
9
```

### 输出

```
Set 1 is immediately decodable
Set 2 is not immediately decodable
```



---

---
title: "Permutations"
layout: "post"
diff: 普及+/提高
pid: UVA941
tag: ['字符串', '康托展开']
---

# Permutations

## 题目描述

## 题目大意：

输入一个不超过20个字符并且全由小写字母构成的字符串以及一个数N，输出原字符串重新排列顺序得到的所有字符串中字典序从小到大第N+1个的字符串。

## 输入格式

第一行：
一个数T，表示有T组数据。
此后每组数据两行，
第一行表示原字符串，
第二行表示N。

## 输出格式

对于每组数据，输出一行，表示第N+1小的字符串。


感谢 @JXPGSWT_54088  提供的翻译。

## 样例 #1

### 输入

```
2
abc
3
abcde
119
```

### 输出

```
bca
edcba
```



---



---

# 题号列表

- UVA10298 - Power Strings
- UVA11584 - 划分成回文串 Partitioning by Palindromes
- UVA11732 - "strcmp()" Anyone?
- UVA1328 - Period
- UVA1714 - Keyboarding
- UVA423 - MPI Maelstrom
- UVA644 - Immediate Decodability
- UVA941 - Permutations


---

---
title: "Supermarket"
layout: "post"
diff: 普及+/提高
pid: UVA1316
tag: ['贪心', '并查集', '排序']
---

# Supermarket

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 样例 #1

### 输入

```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10
```

### 输出

```
80 
185
```



---

---
title: "Corporative Network"
layout: "post"
diff: 普及+/提高
pid: UVA1329
tag: ['并查集']
---

# Corporative Network

## 题目描述

有 $N$ 个结点，初始时每个结点的父结点都不存在。你的任务是执行一次 $I$ 操作和 $E$ 操作，格式如下：  
- $I\ u\ v$：把结点 $u$ 的父结点设为 $v$，距离为 $|u-v| \bmod 1000$。输入保证执行指令前 $u$ 没有父结点。  
- $E\ u$：询问 $u$ 到根节点的距离。

## 输入格式

输入第一行为测试数据组数 $T$。每组数据第一行为 $n$ $(5\leq n\leq 20000)$。接下来有不超过 $20000$ 行，每行一条指令，以大写英文字母 `O` 结尾。$I$ 指令的个数小于 $n$。

## 输出格式

对于每条 $E$ 指令，输出查询结果。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O

```

### 输出

```
0
2
3
5

```



---



---

# 题号列表

- UVA1316 - Supermarket
- UVA1329 - Corporative Network


---

---
title: "Full Tank?"
layout: "post"
diff: 普及+/提高
pid: UVA11367
tag: ['广度优先搜索 BFS', '优先队列', '队列']
---

# Full Tank?

## 题目描述

有 $N$ 个城市和 $M$ 条道路，构成一条无向图。

在每个城市都有一个加油站，不同的加油站的价格都不一样。

通过一条道路的油耗就是该道路的边权。

现在你需要回答 $q$ 个问题，在每个问题中，请计算出一辆油箱容量为 $c$ 的，起始时油箱为空的车子，从起点 $s$ 到终点 $e$ 至少要花多少钱。

## 输入格式

第一行两个整数城市数 $N(1 \leq N \leq 1000)$，道路数$M(0 \leq M \leq 10000)$。

接下来 $N$ 个整数为每个城市的油的价格 $p_i(1 \leq p_i \leq 100)$。

接下来 $M$ 行每行三个整数$u,v,d$，描述 $u$ 城市到 $v$ 城市 $(0 \leq u,v < N)$ 有一条油耗为 $d(1 \leq d \leq 100)$ 的道路。

接下来的一个整数 $q(1 \leq q \leq 100)$ 为询问数量。

接下来的 $q$ 行每行三个整数 $c,s,e$。询问一辆容量为 $c$ 的车从 $s$ 城市到 $e$ 城市至少要花多少钱。

题目满足 $1 \leq c \leq 100$。

## 输出格式

对于每个询问，每一行回答一个数，为至少花费的钱。如果不能到达，输出`impossible`。

## 样例 #1

### 输入

```
5 5
10 10 20 12 13
0 1 9
0 2 8
1 2 1
1 3 11
2 3 7
2
10 0 3
20 1 4
```

### 输出

```
170
impossible
```



---

---
title: "Ocean Currents"
layout: "post"
diff: 普及+/提高
pid: UVA11573
tag: ['广度优先搜索 BFS']
---

# Ocean Currents

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2620

[PDF](https://uva.onlinejudge.org/external/115/p11573.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d1e2b8169cdc10fcb6efb334ec4201d016849d2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d920afe01202359d2e8d70a7653121b90d9c46b7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/a0f8203bb0b484bf784b764bfe0ccec8f2b61d46.png)

## 样例 #1

### 输入

```
5 5
04125
03355
64734
72377
02062
3
4 2 4 2
4 5 1 4
5 3 3 4
```

### 输出

```
0
2
1
```



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---



---

# 题号列表

- UVA11367 - Full Tank?
- UVA11573 - Ocean Currents
- UVA1714 - Keyboarding


---

---
title: "传说中的车 Fabled Rooks"
layout: "post"
diff: 普及+/提高
pid: UVA11134
tag: ['贪心', '排序', '二分图']
---

# 传说中的车 Fabled Rooks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2075

[PDF](https://uva.onlinejudge.org/external/111/p11134.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/bd6c0f2fb7433acc9184472bbe18e9f1a53f823f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/4e1549d0f9cab4c45c78627adabecc71e886e762.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/81fe8f66faa05106571245120e3fbecf732028ae.png)

## 样例 #1

### 输入

```
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
0
```

### 输出

```
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
```



---

---
title: "和为 0 的 4 个值 4 Values whose Sum is 0"
layout: "post"
diff: 普及+/提高
pid: UVA1152
tag: ['二分', '枚举', '排序']
---

# 和为 0 的 4 个值 4 Values whose Sum is 0

## 题目描述

给出四个数组  $A,B,C,D$ ，每个数组中有  $n$  个整数。求有多少组  $i,j,k,l$  满足  $A_i+B_j+C_k+D_l=0$ 。

## 输入格式

**本题有多组测试数据。**

第一行一个正整数  $T$ ，表示数据组数。

对于每组数据:

第一行一个整数  $n$ 。

接下来  $n$  行，一行四个整数，分别表示  $A_i,B_i,C_i,D_i$ 。

## 输出格式

共  $2\times T$  行。

对于每组数据：

第一行一个整数，表示该组测试数据的答案。

接下来输出一个空行。

## 说明/提示

$1\le n\le4000$ 。数组中所有数的绝对值不大于  $2^{28}$ 。



---

---
title: "单向TSP Unidirectional TSP"
layout: "post"
diff: 普及+/提高
pid: UVA116
tag: ['动态规划 DP', '排序', '最短路']
---

# 单向TSP Unidirectional TSP

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=52

[PDF](https://uva.onlinejudge.org/external/1/p116.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/8f55250e58c560c3ec06a86150f26e2b1e1f75c6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/801aba8894b1c630f564c73247a3de8b316ca7cf.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/f42899d4753927986e0c7f639bd537f5a3da0a4c.png)

## 样例 #1

### 输入

```
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 8 6 4
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 1 2 3
2 2
9 10 9 10
```

### 输出

```
1 2 3 4 4 5
16
1 2 1 5 4 5
11
1 1
19
```



---

---
title: "Supermarket"
layout: "post"
diff: 普及+/提高
pid: UVA1316
tag: ['贪心', '并查集', '排序']
---

# Supermarket

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 样例 #1

### 输入

```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10
```

### 输出

```
80 
185
```



---

---
title: "Hypertransmission"
layout: "post"
diff: 普及+/提高
pid: UVA1325
tag: ['枚举', '排序']
---

# Hypertransmission

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4071

[PDF](https://uva.onlinejudge.org/external/13/p1325.pdf)



---

---
title: "Anagram"
layout: "post"
diff: 普及+/提高
pid: UVA195
tag: ['排序']
---

# Anagram

## 输出格式

感谢@dogfar 提供的翻译

## 样例 #1

### 输入

```
3
aAb
abc
acba
```

### 输出

```
Aab
Aba
aAb
abA
bAa
baA
abc
acb
bac
bca
cab
cba
aabc
aacb
abac
abca
acab
acba
baac
baca
bcaa
caab
caba
cbaa
```



---



---

# 题号列表

- UVA11134 - 传说中的车 Fabled Rooks
- UVA1152 - 和为 0 的 4 个值 4 Values whose Sum is 0
- UVA116 - 单向TSP Unidirectional TSP
- UVA1316 - Supermarket
- UVA1325 - Hypertransmission
- UVA195 - Anagram


---

---
title: "切木棍 Cutting Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA10003
tag: ['搜索', '记忆化搜索']
---

# 切木棍 Cutting Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=944

[PDF](https://uva.onlinejudge.org/external/100/p10003.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/958525065661f78575790c5f6aa2ffbee907fc0b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/e46a5b9b0f145857448142f8f46dfaa75e9f6e02.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/c84a21fce404c85a1c20be6e70d4c5e2aac71537.png)

## 样例 #1

### 输入

```
100
3
25 50 75
10
4
4 5 7 8
0
```

### 输出

```
The minimum cutting is 200.
The minimum cutting is 22.
```



---

---
title: "倒水问题 Fill"
layout: "post"
diff: 普及+/提高
pid: UVA10603
tag: ['搜索', '优先队列', '最短路']
---

# 倒水问题 Fill

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1544

[PDF](https://uva.onlinejudge.org/external/106/p10603.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/2d3a044bd29738a849110d68bb92f13a9aef7016.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/0432604430c8dd3aff84cb657eb403f61d1750f6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/ed317ca6c29f5bac166d1f6428122bcd61d81d18.png)

## 样例 #1

### 输入

```
2
2 3 4 2
96 97 199 62
```

### 输出

```
2 2
9859 62
```



---

---
title: "Seven Seas"
layout: "post"
diff: 普及+/提高
pid: UVA10923
tag: ['搜索']
---

# Seven Seas

## 题目描述

Seven Seas 是一个很棒的游戏。在游戏中，你是一艘战舰的舰长。你身处茫茫大海之中，有一些敌舰试图追上你。你的任务是逃脱并尽你所能地摧毁敌舰。  
游戏在一个 $9 \times 8$ 的地图中进行，你可以向八个方向移动，每次移动一步。你先移动，然后敌舰移动。这些敌舰非常愚蠢，他们总是会移动到离你最近的位置，即使这个位置会摧毁他们的战舰。当一艘战舰移动到一个有岩石的位置就会被摧毁。如果两艘战舰移动到同一个位置，它们都会被摧毁，它们的残骸将会遗留在那个位置，所以如果另一艘战舰再移动到这个位置也会被摧毁。如果敌舰接触到你的战舰，你将会死亡，游戏结束。

## 输入格式

**本题有多组数据**。   
第一行为数据组数。每组数据都是 $9 \times 8$ 的地图。S 表示你的战舰，E 表示敌舰，# 表示岩石，. 表示大海。两组数据之间有一行空行。

## 输出格式

对于每一组数据，如果在10步之内可以将敌舰全部摧毁，输出 `I'm the king of the Seven Seas!`；否则输出 `Oh no! I'm a dead man!`。

## 样例 #1

### 输入

```
3
........
.E.#....
...E....
..#.....
........
........
..S.....
........
........
........
.E.E....
...S....
.E..E...
........
........
........
........
........
E......#
........
........
........
........
........
........
.......S
#.......
```

### 输出

```
I’m the king of the Seven Seas!
Oh no! I’m a dead man!
Oh no! I’m a dead man!
```



---

---
title: "Robots on Ice"
layout: "post"
diff: 普及+/提高
pid: UVA1098
tag: ['搜索', '剪枝']
---

# Robots on Ice

## 题目描述

受哈尔滨冰雕的启发，来自北极机器人与自动机大学的参赛队员决定程序竞赛结束后在校园内举办自己的冰雪节。他们打算在冬天结冰的时候，从学校附近的一个湖里获取冰块。为了便于监测湖中冰层的厚度，他们先将湖面网格化，然后安置一个轻巧的机器人逐个方格测量冰层的厚度。在网格中有三个特殊方格被指定为“检查点”，对应着机器人在检查过程中经过整个行程的四分之一、二分之一、四分之三的位置，机器人在这三个特殊“检查点”会发送相应的进度报告。为了避免对冰面造成不必要的磨损和划痕而影响后续的使用，机器人需要从网格左下角坐标为 $(0，0)$ 的方格出发，经过所有方格仅且一次，然后返回位于坐标为 $(0，1)$ 的方格。如果有多种路线符合要求，则机器人每天会使用一条不同的路线。机器人只能沿北、南、东、西四个方向每次移动一个方格。  
给定网格的大小和三个检查点的位置，编写程序确定有多少种不同的检查路线。例如，湖面被划分为 $3 \times 6$ 的网格，三个检查点按访问的顺序分别为 $(2，1)，(2，4)$ 和 $(0，4)$，机器人必须从 $(0，0)$ 方格开始，路经 $18$ 个方格，最后终止于 $(0，1)$ 方格。机器人必须在第 $4（＝\left\lfloor\dfrac{18}{4}\right\rfloor）$ 步的时候经过 $(2，1)$ 方格，在第 $9（＝\left\lfloor\dfrac{18}{2}\right\rfloor）$ 步的时候经过 $(2，4)$ 方格，第 $13（＝\left\lfloor\dfrac{3 \times 18}{4}\right\rfloor）$ 步的时候经过 $(0，4)$ 方格，只有两种路线符合要求，如下图所示。  
![UVA1098 Robots on Ice](https://cdn.luogu.com.cn/upload/image_hosting/vy6tphyl.png)  
需要注意：（1）当网格的大小不是 $4$ 的倍数时，在计算步数时使用整除；（2）某些情况下可能不存在符合要求的路线，例如给定一个 $4 \times 3$的网格，三个检查点分别为 $(2，0)，(3，2)$ 和 $(0，2)$，那么将不存在从 $(0，0)$ 方格出发，结束于 $(0，1)$ 方格且满足要求的路线。

## 输入格式

**本题有多组数据**。  
每组测试数据的第一行包含两个整数 $m$ 和 $n（2 \leq m，n \leq 8）$，表示网格的行数和列数，接着的一行包含六个整数 $r_1，c_1，r_2，c_2，r_3，c_3$，其中 $0 \leq ri ＜ m，0 \leq c_i ＜ n（i＝1，2，3）$。输入的最后一行包含两个 $0$。

## 输出格式

从 $1$ 开始输出测试数据的组数，输出以下不同路线的数量：机器人从行 $0$ 列 $0$ 出发，在行 $0$ 列 $1$ 结束，在第 $\left\lfloor\dfrac{i \times m \times n}{4}\right\rfloor$ 步时经过行 $r_i$ 和列 $c_i（i＝1，2，3）$，能够路经所有方格仅且一次的路线。



---

---
title: "条件概率 Probability|Given"
layout: "post"
diff: 普及+/提高
pid: UVA11181
tag: ['搜索', '递推', '枚举', '深度优先搜索 DFS']
---

# 条件概率 Probability|Given

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2122

[PDF](https://uva.onlinejudge.org/external/111/p11181.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/e7ff179b70470ecd5bcdd2c359c9dec606f308e3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/c4a19b7e08ff7186da01119426d98cce50c64096.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/67d5194f9e66ef7ce5d79ddcd6cfb38fc83c93ca.png)

## 样例 #1

### 输入

```
3 2
0.10
0.20
0.30
5 1
0.10
0.10
0.10
0.10
0.10
0 0
```

### 输出

```
Case 1:
0.413043
0.739130
0.847826
Case 2:
0.200000
0.200000
0.200000
0.200000
0.200000
```



---

---
title: "Full Tank?"
layout: "post"
diff: 普及+/提高
pid: UVA11367
tag: ['广度优先搜索 BFS', '优先队列', '队列']
---

# Full Tank?

## 题目描述

有 $N$ 个城市和 $M$ 条道路，构成一条无向图。

在每个城市都有一个加油站，不同的加油站的价格都不一样。

通过一条道路的油耗就是该道路的边权。

现在你需要回答 $q$ 个问题，在每个问题中，请计算出一辆油箱容量为 $c$ 的，起始时油箱为空的车子，从起点 $s$ 到终点 $e$ 至少要花多少钱。

## 输入格式

第一行两个整数城市数 $N(1 \leq N \leq 1000)$，道路数$M(0 \leq M \leq 10000)$。

接下来 $N$ 个整数为每个城市的油的价格 $p_i(1 \leq p_i \leq 100)$。

接下来 $M$ 行每行三个整数$u,v,d$，描述 $u$ 城市到 $v$ 城市 $(0 \leq u,v < N)$ 有一条油耗为 $d(1 \leq d \leq 100)$ 的道路。

接下来的一个整数 $q(1 \leq q \leq 100)$ 为询问数量。

接下来的 $q$ 行每行三个整数 $c,s,e$。询问一辆容量为 $c$ 的车从 $s$ 城市到 $e$ 城市至少要花多少钱。

题目满足 $1 \leq c \leq 100$。

## 输出格式

对于每个询问，每一行回答一个数，为至少花费的钱。如果不能到达，输出`impossible`。

## 样例 #1

### 输入

```
5 5
10 10 20 12 13
0 1 9
0 2 8
1 2 1
1 3 11
2 3 7
2
10 0 3
20 1 4
```

### 输出

```
170
impossible
```



---

---
title: "Ocean Currents"
layout: "post"
diff: 普及+/提高
pid: UVA11573
tag: ['广度优先搜索 BFS']
---

# Ocean Currents

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2620

[PDF](https://uva.onlinejudge.org/external/115/p11573.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d1e2b8169cdc10fcb6efb334ec4201d016849d2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/d920afe01202359d2e8d70a7653121b90d9c46b7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11573/a0f8203bb0b484bf784b764bfe0ccec8f2b61d46.png)

## 样例 #1

### 输入

```
5 5
04125
03355
64734
72377
02062
3
4 2 4 2
4 5 1 4
5 3 3 4
```

### 输出

```
0
2
1
```



---

---
title: "划分成回文串 Partitioning by Palindromes"
layout: "post"
diff: 普及+/提高
pid: UVA11584
tag: ['字符串', '动态规划 DP', '搜索']
---

# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 输入格式

第一行为正整数t(≤10)，表示数据组数；接下来t行，每行一个完全由小写字母组成的字符串，长度不超过1000。

## 输出格式

对于每组数据，输出最少回文子串数。

由 @C919 提供翻译

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb
```

### 输出

```
1
7
3
```



---

---
title: "ICPC Team Strategy"
layout: "post"
diff: 普及+/提高
pid: UVA1240
tag: ['动态规划 DP', '搜索', '状态合并']
---

# ICPC Team Strategy

## 题目描述

ICPC（International Collegiate Programming Contest，国际大学生程序设计比赛），就像你所知道的那样，是大学生抱团参加的程序设计比赛。各个团队由 $3$ 个人组成，而他们将会解决一些程序设计问题。

安迪，布迪和坎达拉计划抱团参加 ICPC，至于团队策略，他们仨想到一个简易策略：

+ 在五个小时的比赛的前二十分钟，他们想要读所有的题目，而后他们三个人每个人给每一道题目标一个数字，即某个人 AC 某道题的最小时间，并且一定会 AC。
+ 每个队伍只有一台电脑，因而让一个队伍同时肝两道题是不可能的。
+ 为避免大脑烧毁或心肺骤停（他们比赛过太多次了），他们决定在每道题后交换角色，这样没有人会连续做两道题目。
+ 他们想要尽量多做题目，做题的顺序则无关紧要。

## 输入格式

$T$ 组数据。每组数据开头为整数 $n(1\le n\le 12)$，代表题目数量。第二行 $n$ 个整数 $a_{1\cdots n}(1\le a_i\le 300)$，代表安迪解每到题需要的时间，第三行和第四行分别是布迪和坎达拉解每到题所需的时间。限制同理。

## 输出格式

对于每组数据，输出一个数字，即团队最大可能解出的题目。

### 样例解释

第一组样例：安迪可以单独解出所有的题目，但是安迪不能连续解两道题。

第二组样例：团队可以解出所有的题目：让布迪解第二道题目，让安迪解第一道题目，让布迪解第三道题目，让坎达拉解最后一道题目，需要 $280$ 分钟。

## 样例 #1

### 输入

```
2
3
100 100 80
190 120 90
120 150 100
4
50 20 300 300
200 100 30 250
140 120 100 100
```

### 输出

```
2
4
```



---

---
title: "密码 Password"
layout: "post"
diff: 普及+/提高
pid: UVA1262
tag: ['递归', '枚举', '深度优先搜索 DFS']
---

# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)



---

---
title: "Exploring Pyramids"
layout: "post"
diff: 普及+/提高
pid: UVA1362
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---

# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 输入格式

输入包含多组测试数据。

对于每组测试数据：输入一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

对于每组测试数据：输出一行，一个整数表示答案。

## 样例 #1

### 输入

```
ABABABA
AB
```

### 输出

```
5
0
```



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---

---
title: "小木棍 Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA307
tag: ['搜索', '枚举', '剪枝']
---

# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/10cd3e738e54e4609c2084fe79f07f05c056540d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/4fe73bdc6626222b0f15df6a62fe404a56935dc3.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
```

### 输出

```
6
5
```



---

---
title: "树 Tree"
layout: "post"
diff: 普及+/提高
pid: UVA548
tag: ['搜索', '递归', '深度优先搜索 DFS', '构造']
---

# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/d5af82d5dd26aa1f11be5b3e1cfa80708b9d2173.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/235ec8eb49fbab76e59891f6d6b4f6deb21da67a.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
```

### 输出

```
1
3
255
```



---



---

# 题号列表

- UVA10003 - 切木棍 Cutting Sticks
- UVA10603 - 倒水问题 Fill
- UVA10923 - Seven Seas
- UVA1098 - Robots on Ice
- UVA11181 - 条件概率 Probability|Given
- UVA11367 - Full Tank?
- UVA11573 - Ocean Currents
- UVA11584 - 划分成回文串 Partitioning by Palindromes
- UVA1240 - ICPC Team Strategy
- UVA1262 - 密码 Password
- UVA1362 - Exploring Pyramids
- UVA1714 - Keyboarding
- UVA307 - 小木棍 Sticks
- UVA548 - 树 Tree


---

---
title: "Funny Encryption Method"
layout: "post"
diff: 普及+/提高
pid: UVA10019
tag: ['数学', '数论']
---

# Funny Encryption Method

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=960

[PDF](https://uva.onlinejudge.org/external/100/p10019.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10019/ab61a55b13f53a52e7e0fb57d2b672a1a2942116.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10019/cfab7a928447536bcea014d82f9ea9adff1a9777.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10019/31236a58bbbccacc30d65b9bfbd294dfd53e0052.png)

## 样例 #1

### 输入

```
3
265
111
1234
```

### 输出

```
3 5
6 3
5 5
```



---

---
title: "Again Prime? No Time."
layout: "post"
diff: 普及+/提高
pid: UVA10780
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Again Prime? No Time.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1721

[PDF](https://uva.onlinejudge.org/external/107/p10780.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/3d0cf7af5612472e954446fcdb255b0fa3a5b319.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/ddfda16474dfe1b7303cd66fe53ee037e4720d73.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/093bfbb23aad985a5bf2688d43a9b41fa28421d1.png)

## 样例 #1

### 输入

```
2
2 10
2 100
```

### 输出

```
Case 1:
8
Case 2:
97
```



---

---
title: "Mixing Invitations"
layout: "post"
diff: 普及+/提高
pid: UVA11282
tag: ['数学', '组合数学']
---

# Mixing Invitations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2257

[PDF](https://uva.onlinejudge.org/external/112/p11282.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/110870a90869e55e6ec3515fe755ec5b158955d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/b4e7fdf072d0155249bf58edb79207686db0d3d3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/47758b1841a784e0d76de0fe038a80510f818f87.png)

## 样例 #1

### 输入

```
3 2
4 1
4 4
```

### 输出

```
5
17
24
```



---

---
title: "H(n)"
layout: "post"
diff: 普及+/提高
pid: UVA11526
tag: ['数学', '整除分块']
---

# H(n)

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521

[PDF](https://uva.onlinejudge.org/external/115/p11526.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/9afb4a892766896248d693ae925d518ab86d3d10.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/0f8c27b2e2d3e2232a7828505b7e1038020abc96.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11526/b8e0b2b685195f97c03927b5f479ece353c14d6f.png)

## 样例 #1

### 输入

```
2
5
10
```

### 输出

```
10
27
```



---

---
title: "Chess Queen"
layout: "post"
diff: 普及+/提高
pid: UVA11538
tag: ['数学', '枚举', '组合数学']
---

# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 输入格式

输入文件包含至多$5,000$行，每行包含两个非负整数$M,N(1< M,N \leq 10^6 )$，表示棋盘的规格为$M × N$。输入以$M=N=0$结束。

## 输出格式

对每组数据输出一行，表示可以使两个皇后互相攻击的放置方案数。

保证答案在$64$位有符号整数范围内。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0
```

### 输出

```
12
10907100
11514134000
```



---

---
title: "Benefit"
layout: "post"
diff: 普及+/提高
pid: UVA11889
tag: ['数学', '数论', '枚举', '最大公约数 gcd']
---

# Benefit

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2989

[PDF](https://uva.onlinejudge.org/external/118/p11889.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/1588740ad2fa4cdc66ad2b07066e440857631a2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/f5b692d330a8fdf0363839f65b9e9c8828b4274a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/3a5d4ba6e6d358c9a17c026a907c021a72350aa8.png)

## 样例 #1

### 输入

```
3
2 6
32 1760
7 16
```

### 输出

```
3
55
NO SOLUTION
```



---



---

# 题号列表

- UVA10019 - Funny Encryption Method
- UVA10780 - Again Prime? No Time.
- UVA11282 - Mixing Invitations
- UVA11526 - H(n)
- UVA11538 - Chess Queen
- UVA11889 - Benefit


---

---
title: "倒水问题 Fill"
layout: "post"
diff: 普及+/提高
pid: UVA10603
tag: ['搜索', '优先队列', '最短路']
---

# 倒水问题 Fill

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1544

[PDF](https://uva.onlinejudge.org/external/106/p10603.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/2d3a044bd29738a849110d68bb92f13a9aef7016.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/0432604430c8dd3aff84cb657eb403f61d1750f6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/ed317ca6c29f5bac166d1f6428122bcd61d81d18.png)

## 样例 #1

### 输入

```
2
2 3 4 2
96 97 199 62
```

### 输出

```
2 2
9859 62
```



---

---
title: "Walk Through the Forest"
layout: "post"
diff: 普及+/提高
pid: UVA10917
tag: ['最短路']
---

# Walk Through the Forest

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1858

[PDF](https://uva.onlinejudge.org/external/109/p10917.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10917/2cdbcbd2041975ba19703cf570f7a4087f3eb461.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10917/022b71bb9cb1ef7722eafa8c8a774ab2ecc38148.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10917/b53d3ce908136ede18b278727a3e9aeb6d23bbaf.png)

## 样例 #1

### 输入

```
5 6
1 3 2
1 4 2
3 4 3
1 5 12
4 2 34
5 2 24
7 8
1 3 1
1 4 1
3 7 1
7 4 1
7 5 1
6 7 1
5 2 1
6 2 1
0
```

### 输出

```
2
4
```



---

---
title: "单向TSP Unidirectional TSP"
layout: "post"
diff: 普及+/提高
pid: UVA116
tag: ['动态规划 DP', '排序', '最短路']
---

# 单向TSP Unidirectional TSP

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=52

[PDF](https://uva.onlinejudge.org/external/1/p116.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/8f55250e58c560c3ec06a86150f26e2b1e1f75c6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/801aba8894b1c630f564c73247a3de8b316ca7cf.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/f42899d4753927986e0c7f639bd537f5a3da0a4c.png)

## 样例 #1

### 输入

```
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 8 6 4
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 1 2 3
2 2
9 10 9 10
```

### 输出

```
1 2 3 4 4 5
16
1 2 1 5 4 5
11
1 1
19
```



---

---
title: "这不是bug，而是特性 It's not a Bug, it's a Feature!"
layout: "post"
diff: 普及+/提高
pid: UVA658
tag: ['图论', '最短路', '进制']
---

# 这不是bug，而是特性 It's not a Bug, it's a Feature!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=599

[PDF](https://uva.onlinejudge.org/external/6/p658.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/3980280739ce31d9b96acdbe804068ca33cab9fc.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/7cd2a79ba43bd41cebdbf074b7d149ab2dda68b0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/369bfa04b6ac1cccb3b218de0bdd2f643cf70364.png)

## 样例 #1

### 输入

```
3 3
1 000 00-
1 00- 0-+
2 0-- -++
4 1
7 0-0+ ----
0 0
```

### 输出

```
Product 1
Fastest sequence takes 8 seconds.

Product 2
Bugs cannot be fixed.


```



---



---

# 题号列表

- UVA10603 - 倒水问题 Fill
- UVA10917 - Walk Through the Forest
- UVA116 - 单向TSP Unidirectional TSP
- UVA658 - 这不是bug，而是特性 It's not a Bug, it's a Feature!


---

---
title: "Again Prime? No Time."
layout: "post"
diff: 普及+/提高
pid: UVA10780
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Again Prime? No Time.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1721

[PDF](https://uva.onlinejudge.org/external/107/p10780.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/3d0cf7af5612472e954446fcdb255b0fa3a5b319.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/ddfda16474dfe1b7303cd66fe53ee037e4720d73.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/093bfbb23aad985a5bf2688d43a9b41fa28421d1.png)

## 样例 #1

### 输入

```
2
2 10
2 100
```

### 输出

```
Case 1:
8
Case 2:
97
```



---

---
title: "树 Tree"
layout: "post"
diff: 普及+/提高
pid: UVA548
tag: ['搜索', '递归', '深度优先搜索 DFS', '构造']
---

# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/d5af82d5dd26aa1f11be5b3e1cfa80708b9d2173.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/235ec8eb49fbab76e59891f6d6b4f6deb21da67a.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
```

### 输出

```
1
3
255
```



---



---

# 题号列表

- UVA10780 - Again Prime? No Time.
- UVA548 - 树 Tree


---

---
title: "Power Strings"
layout: "post"
diff: 普及+/提高
pid: UVA10298
tag: ['字符串', '枚举', 'KMP 算法']
---

# Power Strings

## 题目描述

### 题意简述：

求一个字符串最多由多少个重复的子串连接而成。

例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由一个 `abcd` 连接而成。

## 输入格式

**本题多组数据**。

每一组数据仅有一行，这一行仅有一个字符串 $s$。

输入的结束标志为一个 `.`。

## 输出格式

对于每一组数据，输出这组字符串最多由多少个重复的子串连接而成。

## 说明/提示

$1\le |s|\le 10^6$。

## 样例 #1

### 输入

```
abcd
aaaa
ababab
.
```

### 输出

```
1
4
3
```



---

---
title: "The Lottery"
layout: "post"
diff: 普及+/提高
pid: UVA10325
tag: ['枚举', '容斥原理', '概率论']
---

# The Lottery

## 题目描述

给出 $n , m$，和 $m$ 个数 $a[1] \cdots a[m]$。

求 $1 \cdots n$ 中不被 $a[1] \cdots a[m]$ 中任意一个整除的数的个数。

## 输入格式

每组数据以 $n , m$ 为第一行。

第二行 $m$ 个数，表示 $a[i]$。

输入文件以 EOF 结尾。

## 输出格式

每组数据一行一个数字表示答案。

### 数据规模及约定

$ 10 \leqslant n < 2^{31} , m \leqslant 15$。

## 样例 #1

### 输入

```
10 2
2 3
20 2
2 4
```

### 输出

```
3
10
```



---

---
title: "Polynomial GCD"
layout: "post"
diff: 普及+/提高
pid: UVA10951
tag: ['多项式', '枚举', '最大公约数 gcd']
---

# Polynomial GCD

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1892

[PDF](https://uva.onlinejudge.org/external/109/p10951.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/27f28d739e35835743ed24591d9545837d82f420.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/360b18a2c9c0ae5abe1a36e006ef5f0c115af329.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/7ec15d368dfaec2cc7886207c522c4ae00b6990f.png)

## 样例 #1

### 输入

```
3
3 2 2 1 1
4 1 0 2 2 2
0
```

### 输出

```
Case 1: 2 1 2 1
```



---

---
title: "条件概率 Probability|Given"
layout: "post"
diff: 普及+/提高
pid: UVA11181
tag: ['搜索', '递推', '枚举', '深度优先搜索 DFS']
---

# 条件概率 Probability|Given

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2122

[PDF](https://uva.onlinejudge.org/external/111/p11181.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/e7ff179b70470ecd5bcdd2c359c9dec606f308e3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/c4a19b7e08ff7186da01119426d98cce50c64096.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/67d5194f9e66ef7ce5d79ddcd6cfb38fc83c93ca.png)

## 样例 #1

### 输入

```
3 2
0.10
0.20
0.30
5 1
0.10
0.10
0.10
0.10
0.10
0 0
```

### 输出

```
Case 1:
0.413043
0.739130
0.847826
Case 2:
0.200000
0.200000
0.200000
0.200000
0.200000
```



---

---
title: "和为 0 的 4 个值 4 Values whose Sum is 0"
layout: "post"
diff: 普及+/提高
pid: UVA1152
tag: ['二分', '枚举', '排序']
---

# 和为 0 的 4 个值 4 Values whose Sum is 0

## 题目描述

给出四个数组  $A,B,C,D$ ，每个数组中有  $n$  个整数。求有多少组  $i,j,k,l$  满足  $A_i+B_j+C_k+D_l=0$ 。

## 输入格式

**本题有多组测试数据。**

第一行一个正整数  $T$ ，表示数据组数。

对于每组数据:

第一行一个整数  $n$ 。

接下来  $n$  行，一行四个整数，分别表示  $A_i,B_i,C_i,D_i$ 。

## 输出格式

共  $2\times T$  行。

对于每组数据：

第一行一个整数，表示该组测试数据的答案。

接下来输出一个空行。

## 说明/提示

$1\le n\le4000$ 。数组中所有数的绝对值不大于  $2^{28}$ 。



---

---
title: "Chess Queen"
layout: "post"
diff: 普及+/提高
pid: UVA11538
tag: ['数学', '枚举', '组合数学']
---

# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 输入格式

输入文件包含至多$5,000$行，每行包含两个非负整数$M,N(1< M,N \leq 10^6 )$，表示棋盘的规格为$M × N$。输入以$M=N=0$结束。

## 输出格式

对每组数据输出一行，表示可以使两个皇后互相攻击的放置方案数。

保证答案在$64$位有符号整数范围内。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0
```

### 输出

```
12
10907100
11514134000
```



---

---
title: "Benefit"
layout: "post"
diff: 普及+/提高
pid: UVA11889
tag: ['数学', '数论', '枚举', '最大公约数 gcd']
---

# Benefit

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2989

[PDF](https://uva.onlinejudge.org/external/118/p11889.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/1588740ad2fa4cdc66ad2b07066e440857631a2c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/f5b692d330a8fdf0363839f65b9e9c8828b4274a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11889/3a5d4ba6e6d358c9a17c026a907c021a72350aa8.png)

## 样例 #1

### 输入

```
3
2 6
32 1760
7 16
```

### 输出

```
3
55
NO SOLUTION
```



---

---
title: "密码 Password"
layout: "post"
diff: 普及+/提高
pid: UVA1262
tag: ['递归', '枚举', '深度优先搜索 DFS']
---

# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)



---

---
title: "Hypertransmission"
layout: "post"
diff: 普及+/提高
pid: UVA1325
tag: ['枚举', '排序']
---

# Hypertransmission

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4071

[PDF](https://uva.onlinejudge.org/external/13/p1325.pdf)



---

---
title: "Exploring Pyramids"
layout: "post"
diff: 普及+/提高
pid: UVA1362
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---

# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 输入格式

输入包含多组测试数据。

对于每组测试数据：输入一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

对于每组测试数据：输出一行，一个整数表示答案。

## 样例 #1

### 输入

```
ABABABA
AB
```

### 输出

```
5
0
```



---

---
title: "Ping pong"
layout: "post"
diff: 普及+/提高
pid: UVA1428
tag: ['树状数组', '枚举']
---

# Ping pong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4174

[PDF](https://uva.onlinejudge.org/external/14/p1428.pdf)



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---

---
title: "小木棍 Sticks"
layout: "post"
diff: 普及+/提高
pid: UVA307
tag: ['搜索', '枚举', '剪枝']
---

# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/10cd3e738e54e4609c2084fe79f07f05c056540d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/4fe73bdc6626222b0f15df6a62fe404a56935dc3.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
```

### 输出

```
6
5
```



---



---

# 题号列表

- UVA10298 - Power Strings
- UVA10325 - The Lottery
- UVA10951 - Polynomial GCD
- UVA11181 - 条件概率 Probability|Given
- UVA1152 - 和为 0 的 4 个值 4 Values whose Sum is 0
- UVA11538 - Chess Queen
- UVA11889 - Benefit
- UVA1262 - 密码 Password
- UVA1325 - Hypertransmission
- UVA1362 - Exploring Pyramids
- UVA1428 - Ping pong
- UVA1714 - Keyboarding
- UVA307 - 小木棍 Sticks


---

---
title: "City Game"
layout: "post"
diff: 普及+/提高
pid: UVA1330
tag: ['前缀和', '栈']
---

# City Game

## 题目描述

Bob爱上了一个策略游戏（Simcity？）游戏中一个城市由k个地区组成，每个地区都是一块长N×宽M大小的网格矩形,其中可能有些网格已被占用，用R表示;有些则是空地，用F表示。

游戏中可以在空着的空间上建一个矩形的建筑，同时每个建筑按它所占的空地网格数来收租，每占用一个网格可收租金3美元。Bob想知道每个地区中最大面积建筑物能收多少租金。

## 输入格式

第一行是地区个数k。然后接下给出k个地区的相关信息。 相关信息用以下方式输入：

第一行有两个整数n,m (n,m<= 1000),表示这个地区长n宽m

然后接下来有n行，每行m个字符表示网格的信息，相邻的两个用空格隔开。R表示该网格被占用；F表示该网格是空地，可使用。

## 输出格式

对于每一个地区，输出一行一个整数表示该地区中最大面积建筑物能收到的租金。

## 注意

POJ dicuss中有人反映数据输出可能不严格按照要求（例如：两个字符间有多个空格），建议使用cin等读入。

感谢@Rye_Catcher 提供的翻译

## 样例 #1

### 输入

```
3
3 3
R R F
F F F
F R F

5 6
R F F F F F
F R F F F F
F F R F F F
F F F R F F
F F F F R R

4 5
R R R R R
R R F R R
R R R R R
R R F R R
```

### 输出

```
9
27
3
```



---



---

# 题号列表

- UVA1330 - City Game


---

---
title: "Ping pong"
layout: "post"
diff: 普及+/提高
pid: UVA1428
tag: ['树状数组', '枚举']
---

# Ping pong

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4174

[PDF](https://uva.onlinejudge.org/external/14/p1428.pdf)



---



---

# 题号列表

- UVA1428 - Ping pong


---

---
title: "The Lottery"
layout: "post"
diff: 普及+/提高
pid: UVA10325
tag: ['枚举', '容斥原理', '概率论']
---

# The Lottery

## 题目描述

给出 $n , m$，和 $m$ 个数 $a[1] \cdots a[m]$。

求 $1 \cdots n$ 中不被 $a[1] \cdots a[m]$ 中任意一个整除的数的个数。

## 输入格式

每组数据以 $n , m$ 为第一行。

第二行 $m$ 个数，表示 $a[i]$。

输入文件以 EOF 结尾。

## 输出格式

每组数据一行一个数字表示答案。

### 数据规模及约定

$ 10 \leqslant n < 2^{31} , m \leqslant 15$。

## 样例 #1

### 输入

```
10 2
2 3
20 2
2 4
```

### 输出

```
3
10
```



---

---
title: "Mayor's posters"
layout: "post"
diff: 普及+/提高
pid: UVA10587
tag: ['线段树', '离散化', '概率论']
---

# Mayor's posters

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1528

[PDF](https://uva.onlinejudge.org/external/105/p10587.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/cd78d581a1fc6c9ec2d9b3173f9b68a09424475e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/6436da42b41ec1428b97672792b9d28ec339a310.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/6242da124237600afd35badbcef3a1cefd8b37f9.png)

## 样例 #1

### 输入

```
1
5
1 4
2 6
8 10
3 4
7 10
```

### 输出

```
4
```



---

---
title: ""strcmp()" Anyone?"
layout: "post"
diff: 普及+/提高
pid: UVA11732
tag: ['字符串', '概率论', '字典树 Trie']
---

# "strcmp()" Anyone?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2832

[PDF](https://uva.onlinejudge.org/external/117/p11732.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/f9f4156b815a0febb856755194643aee4268928f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/eb2d36585a3a7d37aed581131a6ea2ce899370cb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/8c26b864fca1312c55a0ae313d6d122bb1a75557.png)

## 样例 #1

### 输入

```
2
a
b
4
cat
hat
mat
sir
0
```

### 输出

```
Case 1: 1
Case 2: 6
```



---



---

# 题号列表

- UVA10325 - The Lottery
- UVA10587 - Mayor's posters
- UVA11732 - "strcmp()" Anyone?


---

---
title: "A Star not a Tree?"
layout: "post"
diff: 普及+/提高
pid: UVA10228
tag: ['模拟', '模拟退火']
---

# A Star not a Tree?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1169

[PDF](https://uva.onlinejudge.org/external/102/p10228.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10228/ec51dc78227d21bb2d9c839ef3e178d8ab3ff99a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10228/b4ef7bceb18d8b9b8b09363d833ce3a0e856e2f6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10228/05c65a6fda8cb3452c59beb1fb29053e59eec8fd.png)

## 样例 #1

### 输入

```
1
4
0 0
0 10000
10000 10000
10000 0
```

### 输出

```
28284
```



---

---
title: "10-20-30游戏 10-20-30"
layout: "post"
diff: 普及+/提高
pid: UVA246
tag: ['模拟', '队列']
---

# 10-20-30游戏 10-20-30

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=182

[PDF](https://uva.onlinejudge.org/external/2/p246.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA246/750b0d9c12dd35c566d25df6556f0004e31f9989.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA246/76ced9299d9053998c0a1266b9f337443ba727a3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA246/6c47e475f14410b442b827c9b09864fd7ceb336b.png)

## 样例 #1

### 输入

```
2 6 5 10 10 4 10 10 10 4 5 10 4 5 10 9 7 6 1 7 6 9 5 3 10 10 4 10 9 2 1
10 1 10 10 10 3 10 9 8 10 8 7 1 2 8 6 7 3 3 8 2
4 3 2 10 8 10 6 8 9 5 8 10 5 3 5 4 6 9 9 1 7 6 3 5 10 10 8 10 9 10 10 7
2 6 10 10 4 10 1 3 10 1 1 10 2 2 10 4 10 7 7 10
10 5 4 3 5 7 10 8 2 3 9 10 8 4 5 1 7 6 7 2 6 9 10 2 3 10 3 4 4 9 10 1 1
10 5 10 10 1 8 10 7 8 10 6 10 10 10 9 6 2 10 10
0
```

### 输出

```
Win : 66
Loss: 82
Draw: 73
```



---



---

# 题号列表

- UVA10228 - A Star not a Tree?
- UVA246 - 10-20-30游戏 10-20-30


---

---
title: "条件概率 Probability|Given"
layout: "post"
diff: 普及+/提高
pid: UVA11181
tag: ['搜索', '递推', '枚举', '深度优先搜索 DFS']
---

# 条件概率 Probability|Given

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2122

[PDF](https://uva.onlinejudge.org/external/111/p11181.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/e7ff179b70470ecd5bcdd2c359c9dec606f308e3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/c4a19b7e08ff7186da01119426d98cce50c64096.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/67d5194f9e66ef7ce5d79ddcd6cfb38fc83c93ca.png)

## 样例 #1

### 输入

```
3 2
0.10
0.20
0.30
5 1
0.10
0.10
0.10
0.10
0.10
0 0
```

### 输出

```
Case 1:
0.413043
0.739130
0.847826
Case 2:
0.200000
0.200000
0.200000
0.200000
0.200000
```



---

---
title: "密码 Password"
layout: "post"
diff: 普及+/提高
pid: UVA1262
tag: ['递归', '枚举', '深度优先搜索 DFS']
---

# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)



---

---
title: "Exploring Pyramids"
layout: "post"
diff: 普及+/提高
pid: UVA1362
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS', '区间 DP']
---

# Exploring Pyramids

## 题目描述

虽然探索金字塔是极其老套的剧情，但是有一队探险家还是到了某金字塔脚下。

经过多年的研究，科学家对这座金字塔的内部结构已经有所了解。

首先，金字塔由若干房间组成，房间之间连有通道。

如果把房间看作节点，通道看作边的话，整个金字塔呈现一个有根树结构，节点的子树之间有序，金字塔有唯一的一个入口通向树根。

并且，每个房间的墙壁都涂有若干种颜色的一种。

探险队员打算进一步了解金字塔的结构，为此，他们使用了一种特殊设计的机器人。

这种机器人会从入口进入金字塔，之后对金字塔进行深度优先遍历。

机器人每进入一个房间（无论是第一次进入还是返回），都会记录这个房间的颜色。

最后，机器人会从入口退出金字塔。

显然，机器人会访问每个房间至少一次，并且穿越每条通道恰好两次（两个方向各一次）， 然后，机器人会得到一个颜色序列。

但是，探险队员发现这个颜色序列并不能唯一确定金字塔的结构。

现在他们想请你帮助他们计算，对于一个给定的颜色序列，有多少种可能的结构会得到这个序列。

因为结果可能会非常大，你只需要输出答案对 $10^9$ 取模之后的值。

## 输入格式

输入包含多组测试数据。

对于每组测试数据：输入一行，包含一个字符串 $S$，长度不超过 $300$，表示机器人得到的颜色序列。

## 输出格式

对于每组测试数据：输出一行，一个整数表示答案。

## 样例 #1

### 输入

```
ABABABA
AB
```

### 输出

```
5
0
```



---

---
title: "树 Tree"
layout: "post"
diff: 普及+/提高
pid: UVA548
tag: ['搜索', '递归', '深度优先搜索 DFS', '构造']
---

# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/d5af82d5dd26aa1f11be5b3e1cfa80708b9d2173.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/235ec8eb49fbab76e59891f6d6b4f6deb21da67a.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
```

### 输出

```
1
3
255
```



---



---

# 题号列表

- UVA11181 - 条件概率 Probability|Given
- UVA1262 - 密码 Password
- UVA1362 - Exploring Pyramids
- UVA548 - 树 Tree


---

---
title: "Mayor's posters"
layout: "post"
diff: 普及+/提高
pid: UVA10587
tag: ['线段树', '离散化', '概率论']
---

# Mayor's posters

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1528

[PDF](https://uva.onlinejudge.org/external/105/p10587.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/cd78d581a1fc6c9ec2d9b3173f9b68a09424475e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/6436da42b41ec1428b97672792b9d28ec339a310.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/6242da124237600afd35badbcef3a1cefd8b37f9.png)

## 样例 #1

### 输入

```
1
5
1 4
2 6
8 10
3 4
7 10
```

### 输出

```
4
```



---



---

# 题号列表

- UVA10587 - Mayor's posters


---

---
title: "Again Prime? No Time."
layout: "post"
diff: 普及+/提高
pid: UVA10780
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Again Prime? No Time.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1721

[PDF](https://uva.onlinejudge.org/external/107/p10780.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/3d0cf7af5612472e954446fcdb255b0fa3a5b319.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/ddfda16474dfe1b7303cd66fe53ee037e4720d73.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/093bfbb23aad985a5bf2688d43a9b41fa28421d1.png)

## 样例 #1

### 输入

```
2
2 10
2 100
```

### 输出

```
Case 1:
8
Case 2:
97
```



---



---

# 题号列表

- UVA10780 - Again Prime? No Time.


---

---
title: "Again Prime? No Time."
layout: "post"
diff: 普及+/提高
pid: UVA10780
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Again Prime? No Time.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1721

[PDF](https://uva.onlinejudge.org/external/107/p10780.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/3d0cf7af5612472e954446fcdb255b0fa3a5b319.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/ddfda16474dfe1b7303cd66fe53ee037e4720d73.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/093bfbb23aad985a5bf2688d43a9b41fa28421d1.png)

## 样例 #1

### 输入

```
2
2 10
2 100
```

### 输出

```
Case 1:
8
Case 2:
97
```



---



---

# 题号列表

- UVA10780 - Again Prime? No Time.


---

---
title: "Mayor's posters"
layout: "post"
diff: 普及+/提高
pid: UVA10587
tag: ['线段树', '离散化', '概率论']
---

# Mayor's posters

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1528

[PDF](https://uva.onlinejudge.org/external/105/p10587.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/cd78d581a1fc6c9ec2d9b3173f9b68a09424475e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/6436da42b41ec1428b97672792b9d28ec339a310.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10587/6242da124237600afd35badbcef3a1cefd8b37f9.png)

## 样例 #1

### 输入

```
1
5
1 4
2 6
8 10
3 4
7 10
```

### 输出

```
4
```



---



---

# 题号列表

- UVA10587 - Mayor's posters


---

---
title: "Mixing Invitations"
layout: "post"
diff: 普及+/提高
pid: UVA11282
tag: ['数学', '组合数学']
---

# Mixing Invitations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2257

[PDF](https://uva.onlinejudge.org/external/112/p11282.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/110870a90869e55e6ec3515fe755ec5b158955d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/b4e7fdf072d0155249bf58edb79207686db0d3d3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/47758b1841a784e0d76de0fe038a80510f818f87.png)

## 样例 #1

### 输入

```
3 2
4 1
4 4
```

### 输出

```
5
17
24
```



---

---
title: "Chess Queen"
layout: "post"
diff: 普及+/提高
pid: UVA11538
tag: ['数学', '枚举', '组合数学']
---

# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 输入格式

输入文件包含至多$5,000$行，每行包含两个非负整数$M,N(1< M,N \leq 10^6 )$，表示棋盘的规格为$M × N$。输入以$M=N=0$结束。

## 输出格式

对每组数据输出一行，表示可以使两个皇后互相攻击的放置方案数。

保证答案在$64$位有符号整数范围内。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0
```

### 输出

```
12
10907100
11514134000
```



---



---

# 题号列表

- UVA11282 - Mixing Invitations
- UVA11538 - Chess Queen


---

---
title: "Mixing Invitations"
layout: "post"
diff: 普及+/提高
pid: UVA11282
tag: ['数学', '组合数学']
---

# Mixing Invitations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2257

[PDF](https://uva.onlinejudge.org/external/112/p11282.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/110870a90869e55e6ec3515fe755ec5b158955d7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/b4e7fdf072d0155249bf58edb79207686db0d3d3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/47758b1841a784e0d76de0fe038a80510f818f87.png)

## 样例 #1

### 输入

```
3 2
4 1
4 4
```

### 输出

```
5
17
24
```



---

---
title: "Chess Queen"
layout: "post"
diff: 普及+/提高
pid: UVA11538
tag: ['数学', '枚举', '组合数学']
---

# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 输入格式

输入文件包含至多$5,000$行，每行包含两个非负整数$M,N(1< M,N \leq 10^6 )$，表示棋盘的规格为$M × N$。输入以$M=N=0$结束。

## 输出格式

对每组数据输出一行，表示可以使两个皇后互相攻击的放置方案数。

保证答案在$64$位有符号整数范围内。

Translation provided by @Zaoaa

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0
```

### 输出

```
12
10907100
11514134000
```



---



---

# 题号列表

- UVA11282 - Mixing Invitations
- UVA11538 - Chess Queen


---

---
title: "Again Prime? No Time."
layout: "post"
diff: 普及+/提高
pid: UVA10780
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Again Prime? No Time.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1721

[PDF](https://uva.onlinejudge.org/external/107/p10780.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/3d0cf7af5612472e954446fcdb255b0fa3a5b319.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/ddfda16474dfe1b7303cd66fe53ee037e4720d73.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10780/093bfbb23aad985a5bf2688d43a9b41fa28421d1.png)

## 样例 #1

### 输入

```
2
2 10
2 100
```

### 输出

```
Case 1:
8
Case 2:
97
```



---



---

# 题号列表

- UVA10780 - Again Prime? No Time.


---

---
title: "传说中的车 Fabled Rooks"
layout: "post"
diff: 普及+/提高
pid: UVA11134
tag: ['贪心', '排序', '二分图']
---

# 传说中的车 Fabled Rooks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2075

[PDF](https://uva.onlinejudge.org/external/111/p11134.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/bd6c0f2fb7433acc9184472bbe18e9f1a53f823f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/4e1549d0f9cab4c45c78627adabecc71e886e762.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/81fe8f66faa05106571245120e3fbecf732028ae.png)

## 样例 #1

### 输入

```
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
0
```

### 输出

```
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
```



---

---
title: "Supermarket"
layout: "post"
diff: 普及+/提高
pid: UVA1316
tag: ['贪心', '并查集', '排序']
---

# Supermarket

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 样例 #1

### 输入

```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10
```

### 输出

```
80 
185
```



---

---
title: "Tian Ji -- The Horse Racing"
layout: "post"
diff: 普及+/提高
pid: UVA1344
tag: ['贪心']
---

# Tian Ji -- The Horse Racing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4090

[PDF](https://uva.onlinejudge.org/external/13/p1344.pdf)

## 样例 #1

### 输入

```
3
92 83 71
95 87 74
2
20 20
20 20
2
20 19
22 18
0
```

### 输出

```
200
0
0
```



---



---

# 题号列表

- UVA11134 - 传说中的车 Fabled Rooks
- UVA1316 - Supermarket
- UVA1344 - Tian Ji -- The Horse Racing


---

---
title: "这不是bug，而是特性 It's not a Bug, it's a Feature!"
layout: "post"
diff: 普及+/提高
pid: UVA658
tag: ['图论', '最短路', '进制']
---

# 这不是bug，而是特性 It's not a Bug, it's a Feature!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=599

[PDF](https://uva.onlinejudge.org/external/6/p658.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/3980280739ce31d9b96acdbe804068ca33cab9fc.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/7cd2a79ba43bd41cebdbf074b7d149ab2dda68b0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA658/369bfa04b6ac1cccb3b218de0bdd2f643cf70364.png)

## 样例 #1

### 输入

```
3 3
1 000 00-
1 00- 0-+
2 0-- -++
4 1
7 0-0+ ----
0 0
```

### 输出

```
Product 1
Fastest sequence takes 8 seconds.

Product 2
Bugs cannot be fixed.


```



---



---

# 题号列表

- UVA658 - 这不是bug，而是特性 It's not a Bug, it's a Feature!


---

---
title: "密码 Password"
layout: "post"
diff: 普及+/提高
pid: UVA1262
tag: ['递归', '枚举', '深度优先搜索 DFS']
---

# 密码 Password

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=247&page=show_problem&problem=3703

[PDF](https://uva.onlinejudge.org/external/12/p1262.pdf)



---

---
title: "树 Tree"
layout: "post"
diff: 普及+/提高
pid: UVA548
tag: ['搜索', '递归', '深度优先搜索 DFS', '构造']
---

# 树 Tree

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=489

[PDF](https://uva.onlinejudge.org/external/5/p548.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/78473d26dddbe5f8314b7aac17e37af6d9c18840.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/d5af82d5dd26aa1f11be5b3e1cfa80708b9d2173.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA548/235ec8eb49fbab76e59891f6d6b4f6deb21da67a.png)

## 样例 #1

### 输入

```
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
```

### 输出

```
1
3
255
```



---



---

# 题号列表

- UVA1262 - 密码 Password
- UVA548 - 树 Tree


---

---
title: "条件概率 Probability|Given"
layout: "post"
diff: 普及+/提高
pid: UVA11181
tag: ['搜索', '递推', '枚举', '深度优先搜索 DFS']
---

# 条件概率 Probability|Given

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2122

[PDF](https://uva.onlinejudge.org/external/111/p11181.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/e7ff179b70470ecd5bcdd2c359c9dec606f308e3.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/c4a19b7e08ff7186da01119426d98cce50c64096.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11181/67d5194f9e66ef7ce5d79ddcd6cfb38fc83c93ca.png)

## 样例 #1

### 输入

```
3 2
0.10
0.20
0.30
5 1
0.10
0.10
0.10
0.10
0.10
0 0
```

### 输出

```
Case 1:
0.413043
0.739130
0.847826
Case 2:
0.200000
0.200000
0.200000
0.200000
0.200000
```



---

---
title: "统计有根树 Count"
layout: "post"
diff: 普及+/提高
pid: UVA1645
tag: ['递推']
---

# 统计有根树 Count

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4520

[PDF](https://uva.onlinejudge.org/external/16/p1645.pdf)



---



---

# 题号列表

- UVA11181 - 条件概率 Probability|Given
- UVA1645 - 统计有根树 Count


---

---
title: "倒水问题 Fill"
layout: "post"
diff: 普及+/提高
pid: UVA10603
tag: ['搜索', '优先队列', '最短路']
---

# 倒水问题 Fill

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1544

[PDF](https://uva.onlinejudge.org/external/106/p10603.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/2d3a044bd29738a849110d68bb92f13a9aef7016.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/0432604430c8dd3aff84cb657eb403f61d1750f6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10603/ed317ca6c29f5bac166d1f6428122bcd61d81d18.png)

## 样例 #1

### 输入

```
2
2 3 4 2
96 97 199 62
```

### 输出

```
2 2
9859 62
```



---

---
title: "Full Tank?"
layout: "post"
diff: 普及+/提高
pid: UVA11367
tag: ['广度优先搜索 BFS', '优先队列', '队列']
---

# Full Tank?

## 题目描述

有 $N$ 个城市和 $M$ 条道路，构成一条无向图。

在每个城市都有一个加油站，不同的加油站的价格都不一样。

通过一条道路的油耗就是该道路的边权。

现在你需要回答 $q$ 个问题，在每个问题中，请计算出一辆油箱容量为 $c$ 的，起始时油箱为空的车子，从起点 $s$ 到终点 $e$ 至少要花多少钱。

## 输入格式

第一行两个整数城市数 $N(1 \leq N \leq 1000)$，道路数$M(0 \leq M \leq 10000)$。

接下来 $N$ 个整数为每个城市的油的价格 $p_i(1 \leq p_i \leq 100)$。

接下来 $M$ 行每行三个整数$u,v,d$，描述 $u$ 城市到 $v$ 城市 $(0 \leq u,v < N)$ 有一条油耗为 $d(1 \leq d \leq 100)$ 的道路。

接下来的一个整数 $q(1 \leq q \leq 100)$ 为询问数量。

接下来的 $q$ 行每行三个整数 $c,s,e$。询问一辆容量为 $c$ 的车从 $s$ 城市到 $e$ 城市至少要花多少钱。

题目满足 $1 \leq c \leq 100$。

## 输出格式

对于每个询问，每一行回答一个数，为至少花费的钱。如果不能到达，输出`impossible`。

## 样例 #1

### 输入

```
5 5
10 10 20 12 13
0 1 9
0 2 8
1 2 1
1 3 11
2 3 7
2
10 0 3
20 1 4
```

### 输出

```
170
impossible
```



---

---
title: "10-20-30游戏 10-20-30"
layout: "post"
diff: 普及+/提高
pid: UVA246
tag: ['模拟', '队列']
---

# 10-20-30游戏 10-20-30

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=182

[PDF](https://uva.onlinejudge.org/external/2/p246.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA246/750b0d9c12dd35c566d25df6556f0004e31f9989.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA246/76ced9299d9053998c0a1266b9f337443ba727a3.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA246/6c47e475f14410b442b827c9b09864fd7ceb336b.png)

## 样例 #1

### 输入

```
2 6 5 10 10 4 10 10 10 4 5 10 4 5 10 9 7 6 1 7 6 9 5 3 10 10 4 10 9 2 1
10 1 10 10 10 3 10 9 8 10 8 7 1 2 8 6 7 3 3 8 2
4 3 2 10 8 10 6 8 9 5 8 10 5 3 5 4 6 9 9 1 7 6 3 5 10 10 8 10 9 10 10 7
2 6 10 10 4 10 1 3 10 1 1 10 2 2 10 4 10 7 7 10
10 5 4 3 5 7 10 8 2 3 9 10 8 4 5 1 7 6 7 2 6 9 10 2 3 10 3 4 4 9 10 1 1
10 5 10 10 1 8 10 7 8 10 6 10 10 10 9 6 2 10 10
0
```

### 输出

```
Win : 66
Loss: 82
Draw: 73
```



---



---

# 题号列表

- UVA10603 - 倒水问题 Fill
- UVA11367 - Full Tank?
- UVA246 - 10-20-30游戏 10-20-30


---

---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---



---

# 题号列表

- UVA10474 - 大理石在哪儿 Where is the Marble?


---

---
title: "IP网络 IP Networks"
layout: "post"
diff: 普及-
pid: UVA1590
tag: ['字符串', '进制', '位运算']
---

# IP网络 IP Networks

## 题目描述

亚历克斯是IP网络的管理员。他的客户每个人有一组单独的IP地址，他决定将所有IP地址分组到最小可能的IP网络中。

每个IP地址有四个部分组成，每个部分用小数点分离。格式如a,b,c,d每个部分都是一个十进制的数（0≤这个数≤255）且没有多余的前导零。

IP网络由两个4各部分的数字——网络地址和网络掩码组成。网络地址和网络掩码和IP地址写入方式相同。为了理解网络地址和网络掩码的含义，我们将它们用二进制来表述。IP地址、网络地址和网络掩码的二进制都由32位组成：a的8位（从最重要到最不重要），其次是b的8位，其次是c的8位，其次是d的8位。

IP网络包含一个2n个IP地址的范围，其中所有n>32。网络掩码始终存在32~n个第一部分设置为一，n个最后部分在二进制表示中设置为零。网络地址已任意32个n个第一部分，n个最后部分在其二进制表示中设置为零。IP网络所有的32个n位第一位相当于32位n个任意位的网络地址的所有IP地址最后一位。

我们说，一个IP网络比其他IP网络更小，那么它包含更少的IP地址。

## 输入格式

有多个测试数据。

输入文件的第一行包含一个整数m。下面m行都是一个IP地址。IP地址可能重复。

## 输出格式

每个测试数据在第一行写上网络地址，在第二行写上网络掩码。 网络地址和网络掩码代表的IP网络包括所有IP地址且最小。

## 样例输入输出：
### 样例输入#1
3

194.85.160.177

194.85.160.183

194.85.160.178

### 样例输出#1
194.85.160.176

255.255.255.248

## 说明/提示

一个IP网络的网络地址是194.85.160.176它的网络掩码是255.255.255.248

那么这个IP网络包含8个IP地址从194.85.160.176到194.85.160.183

0 ≤ n ≤ 32,1 ≤ m ≤ 1000

感谢@BIGmrsrz 提供翻译



---



---

# 题号列表

- UVA1590 - IP网络 IP Networks


---

---
title: "Gergovia的酒交易 Wine trading in Gergovia"
layout: "post"
diff: 普及-
pid: UVA11054
tag: ['贪心', '前缀和']
---

# Gergovia的酒交易 Wine trading in Gergovia

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1995

[PDF](https://uva.onlinejudge.org/external/110/p11054.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/ced1606866ddabe301a52d0310f9433bc4587f7e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/26ec5db5cf20e0de0ecadbcd24f88389305b92a4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/178f45e194980c55bc177e289c65e48b01d9fea5.png)

## 样例 #1

### 输入

```
5
5 -4 1 -3 1
6
-1000 -1000 -1000 1000 1000 1000
0
```

### 输出

```
9
9000
```



---

---
title: "最大乘积 Maximum Product"
layout: "post"
diff: 普及-
pid: UVA11059
tag: ['搜索', '枚举', '前缀和']
---

# 最大乘积 Maximum Product

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2000

[PDF](https://uva.onlinejudge.org/external/110/p11059.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/65771c7c6d1492d75695a5505a88282671afede0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/057abe21049b4423b1de44dfdc2de12075eae6eb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/341e4b9b0d67601bc1876729c0e2aae16988584e.png)

## 样例 #1

### 输入

```
3
2 4 -3
5
2 5 -1 2 -1
```

### 输出

```
Case #1: The maximum product is 8.

Case #2: The maximum product is 20.
```



---



---

# 题号列表

- UVA11054 - Gergovia的酒交易 Wine trading in Gergovia
- UVA11059 - 最大乘积 Maximum Product


---

---
title: "Weights and Measures"
layout: "post"
diff: 普及-
pid: UVA10154
tag: ['动态规划 DP']
---

# Weights and Measures

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1095

[PDF](https://uva.onlinejudge.org/external/101/p10154.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10154/c29ed6cce99dc9e3052d764393c705794c12e076.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10154/ceec69eaaace6da41513335f7cc0376e2ac2ca7d.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10154/dfac24d42709adece26e7d5794c4e00bfe684c0a.png)

## 样例 #1

### 输入

```
300 1000
1000 1200
200 600
100 101
```

### 输出

```
3
```



---



---

# 题号列表

- UVA10154 - Weights and Measures


---

---
title: "古老的密码 Ancient Cipher"
layout: "post"
diff: 普及-
pid: UVA1339
tag: ['字符串', '排序', '概率论']
---

# 古老的密码 Ancient Cipher

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4085

[PDF](https://uva.onlinejudge.org/external/13/p1339.pdf)

## 样例 #1

### 输入

```
JWPUDJSTVP
VICTORIOUS
MAMA
ROME
HAHA
HEHE
AAA
AAA
NEERCISTHEBEST
SECRETMESSAGES
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "DNA序列 DNA Consensus String"
layout: "post"
diff: 普及-
pid: UVA1368
tag: ['字符串', '贪心']
---

# DNA序列 DNA Consensus String

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4114

[PDF](https://uva.onlinejudge.org/external/13/p1368.pdf)



---

---
title: "UVA141 The Spot Game"
layout: "post"
diff: 普及-
pid: UVA141
tag: ['模拟', '字符串']
---

# UVA141 The Spot Game

## 题目背景

有一种叫做 Spot 的游戏，在一个 $N \times N$ 的棋盘上玩，下图是当 $N=4$ 时一些可能的样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/6j8s01tj.png)

游戏中，玩家可以在空的地方放置一颗黑棋或拿走一颗黑棋，从而产生多种图案。如果棋盘上的图案（或者旋转了 $90^{\circ}$ 或 $180^{\circ}$）在之前重复过，则产生了这个图案的玩家失败，另一个玩家胜利。

例如，如果上图中第一种图案出现过，那么另外三种都会结束游戏，但最后一种不会。

## 题目描述

现在给出若干个游戏中每个玩家的操作，请你判断游戏的胜负情况。

## 输入格式

输入包含若干个游戏，每一行首先输入一个整数 $N$ （$2 \leq N \leq 50$），代表棋盘的大小。

接下来有 $2N$ 行，每一行代表一个操作，每一行不一定是必要的。每一行都输入两个整数（$x,y$）代表棋盘上的一个坐标（$1 \leq x,y \leq N$），接着一个空格后输入一个字符```+```或```-```代表增加或者删除。

保证每一个操作中不会在已有棋子的地方放下棋子或在没有棋子的地方拿走棋子。

输入的最后一行为一个```0```。

## 输出格式

对于每个游戏，输出哪位玩家在游戏进行到第几步时获得了胜利。如果平局，则输出```Draw```。

## 说明/提示

在输入的第一个游戏中，第二位玩家在第 $3$ 步时取得胜利。

第二个游戏到最后没有出现重复的情况，因此平局。

## 样例 #1

### 输入

```
2
1 1 +
2 2 +
2 2 -
1 2 +
2
1 1 +
2 2 +
1 2 +
2 2 -
0
```

### 输出

```
Player 2 wins on move 3
Draw
```



---

---
title: "环状序列 Circular Sequence"
layout: "post"
diff: 普及-
pid: UVA1584
tag: ['模拟', '字符串']
---

# 环状序列 Circular Sequence

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4459

[PDF](https://uva.onlinejudge.org/external/15/p1584.pdf)



---

---
title: "分子量 Molar mass"
layout: "post"
diff: 普及-
pid: UVA1586
tag: ['字符串', '概率论']
---

# 分子量 Molar mass

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4461

[PDF](https://uva.onlinejudge.org/external/15/p1586.pdf)

## 样例 #1

### 输入

```
4
C
C6H5OH
NH2CH2COOH
C12H22O11
```

### 输出

```
12.010
94.108
75.070
342.296
```



---

---
title: "IP网络 IP Networks"
layout: "post"
diff: 普及-
pid: UVA1590
tag: ['字符串', '进制', '位运算']
---

# IP网络 IP Networks

## 题目描述

亚历克斯是IP网络的管理员。他的客户每个人有一组单独的IP地址，他决定将所有IP地址分组到最小可能的IP网络中。

每个IP地址有四个部分组成，每个部分用小数点分离。格式如a,b,c,d每个部分都是一个十进制的数（0≤这个数≤255）且没有多余的前导零。

IP网络由两个4各部分的数字——网络地址和网络掩码组成。网络地址和网络掩码和IP地址写入方式相同。为了理解网络地址和网络掩码的含义，我们将它们用二进制来表述。IP地址、网络地址和网络掩码的二进制都由32位组成：a的8位（从最重要到最不重要），其次是b的8位，其次是c的8位，其次是d的8位。

IP网络包含一个2n个IP地址的范围，其中所有n>32。网络掩码始终存在32~n个第一部分设置为一，n个最后部分在二进制表示中设置为零。网络地址已任意32个n个第一部分，n个最后部分在其二进制表示中设置为零。IP网络所有的32个n位第一位相当于32位n个任意位的网络地址的所有IP地址最后一位。

我们说，一个IP网络比其他IP网络更小，那么它包含更少的IP地址。

## 输入格式

有多个测试数据。

输入文件的第一行包含一个整数m。下面m行都是一个IP地址。IP地址可能重复。

## 输出格式

每个测试数据在第一行写上网络地址，在第二行写上网络掩码。 网络地址和网络掩码代表的IP网络包括所有IP地址且最小。

## 样例输入输出：
### 样例输入#1
3

194.85.160.177

194.85.160.183

194.85.160.178

### 样例输出#1
194.85.160.176

255.255.255.248

## 说明/提示

一个IP网络的网络地址是194.85.160.176它的网络掩码是255.255.255.248

那么这个IP网络包含8个IP地址从194.85.160.176到194.85.160.183

0 ≤ n ≤ 32,1 ≤ m ≤ 1000

感谢@BIGmrsrz 提供翻译



---

---
title: "纵横字谜的答案 Crossword Answers"
layout: "post"
diff: 普及-
pid: UVA232
tag: ['模拟', '字符串', '队列']
---

# 纵横字谜的答案 Crossword Answers

## 题目描述

有一个 $r$ 行 $c$ 列 $(1<r,c<10)$ 的网格，黑格为 `*` ，每个白格都填有一个字母。如果一个白格的左边相邻位置或者上边相邻位置没有白格（可能是黑格，也可能出了网格边界），则称这个白格是一个起始格。

你的任务是先找出网格中所有横向单词（`Across`）。这些单词必须从一个起始格（左边是黑格，或是第一列）开始，向右延伸到一个黑格的左边或者整个网格的最右列。然后找出所有竖向单词（`Down`），规则同上，这些单词必须从一个起始格（上边是黑格，或是第一行）开始，向下延伸到一个黑格的上边或者整个网格的最下行。

## 输入格式

有多个矩阵输入，对于第 $i$ 个矩阵，第一行输入 $r_i$ 和 $c_i$ 并以空格隔开。 $(1<r_i,c_i<10)$，表示此网格为 $r_i$ 行 $c_i$ 列，然后下面输入矩阵的内容，里面为大写字母或是 `*`，以 `0` 代表所有矩阵输入结束。

## 输出格式

每个谜题的输出包括谜题的标识符（如 `puzzle #1:`）和横向竖向单词列表。每个单词每行只输出一个并先输出以其相应定义的数量的递增顺序数字再输出单词。

数字的输出占据三个场宽并右对齐。

横向列表的标题是 `Across`，竖向单词列表的标题是 `Down`。

在列表为空的情况下（网格中的所有正方形均为黑色），`Across` 和 `Down` 标题仍应出现。

## 样例 #1

### 输入

```
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0
```

### 输出

```
puzzle #1:
Across
1.AT
3.O
Down
1.A
2.TO
puzzle #2:
Across
1.AIM
4.DEN
7.ME
8.ONE
9.UPON
11.TO
12.SO
13.ERIN
15.SA
17.OR
18.IES
19.DEA
Down
1.A
2.IMPOSE
3.MEO
4.DO
5.ENTIRE
6.NEON
9.US
10.NE
14.ROD
16.AS
18.I
20.A
```



---

---
title: "回文词 Palindromes"
layout: "post"
diff: 普及-
pid: UVA401
tag: ['字符串']
---

# 回文词 Palindromes

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=342

[PDF](https://uva.onlinejudge.org/external/4/p401.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/b6c215fa795465f551b5ca7a97ddc3a7f22e50ab.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/765d17adb8ebb1c9f9f633813a123b3fdc93dfa5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA401/d9c985cc6ed58c99115e4db79b3515accf10435d.png)

注意要换两次行。

## 样例 #1

### 输入

```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
```

### 输出

```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.
```



---

---
title: "刽子手的游戏 Hangman Judge"
layout: "post"
diff: 普及-
pid: UVA489
tag: ['模拟', '字符串', '搜索']
---

# 刽子手的游戏 Hangman Judge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=430

[PDF](https://uva.onlinejudge.org/external/4/p489.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/5235bc315d8684bc30728d37f52e7f53bcd8dccb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/c4ea20c647fbaae88cdeb4ee1428a3bc412a001f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/1fdc8a8950ad27b9c821b2ad0fbaf563f3f4bca0.png)

## 样例 #1

### 输入

```
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
```

### 输出

```
Round 1
You win.
Round 2
You chickened out.
Round 3
You lose.
```



---

---
title: "Word Amalgamation"
layout: "post"
diff: 普及-
pid: UVA642
tag: ['字符串', '排序']
---

# Word Amalgamation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=583

[PDF](https://uva.onlinejudge.org/external/6/p642.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/798288cf0a5caae5367a31141c3cf2e90bd3b5cb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/d85b48af6838aac4769be70e174b7480fc2b98e7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/d8237ee3b00c49d0666058cf53b6b711aad2bdf6.png)

## 样例 #1

### 输入

```
tarp
given
score
refund
only
trap
work
earn
course
pepper
part
XXXXXX
resco
nfudre
aptr
sett
oresuc
XXXXXX
```

### 输出

```
score
******
refund
******
part
tarp
trap
******
NOT A VALID WORD
******
course
******
```



---



---

# 题号列表

- UVA1339 - 古老的密码 Ancient Cipher
- UVA1368 - DNA序列 DNA Consensus String
- UVA141 - UVA141 The Spot Game
- UVA1584 - 环状序列 Circular Sequence
- UVA1586 - 分子量 Molar mass
- UVA1590 - IP网络 IP Networks
- UVA232 - 纵横字谜的答案 Crossword Answers
- UVA401 - 回文词 Palindromes
- UVA489 - 刽子手的游戏 Hangman Judge
- UVA642 - Word Amalgamation


---

---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---

---
title: "Dragon of Loowater"
layout: "post"
diff: 普及-
pid: UVA11292
tag: ['模拟', '贪心', '排序']
---

# Dragon of Loowater

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/tqycbsg2.png)

从前，在 Loowater 王国，一场小麻烦变成了一个大问题。Loowater 中部的 Rellau 溪岸一直是大雁繁殖的理想之地。由于缺乏天敌，大雁的数量失控。Loowater 的人民大多远离大雁。偶尔会有一只大雁袭击人们，可能会咬掉一两个手指，但总的来说，人民把大雁当作一个小麻烦忍受着。

有一天，一次奇怪的变异发生了，一只大雁产下了一条多头的喷火龙。当这条龙长大后，它威胁要把 Loowater 王国烧成灰烬。Loowater 遇到了一个大问题。国王十分惊恐，召集他的骑士们去屠龙，拯救王国。

骑士们解释道：“要屠龙，我们必须砍下它所有的头。每个骑士只能砍掉龙的一个头。龙的头大小不一。为了砍掉一个头，骑士必须至少和龙头的直径一样高。骑士工会要求，砍掉一个头的骑士必须得到相当于其身高每厘米一枚金币的报酬。”

有足够的骑士来打败这条龙吗？国王召集他的顾问们来帮他决定该雇佣多少骑士以及选择哪些骑士。在花费大量金钱建造米尔公园后，国王想要将屠龙的开支降到最低。作为顾问之一，你的任务是帮助国王。你非常认真地对待这个任务：如果失败了，你和整个王国都将被烧成灰烬！

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含两个介于 $1$ 和 $20000$ 之间（包括 $1$ 和 $20000$）的整数，分别表示龙的头数 $n$ 和王国中骑士的数量 $m$。接下来的 $n$ 行每行包含一个整数，给出龙头的直径，单位为厘米。接下来的 $m$ 行每行包含一个整数，指定卢沃特骑士的身高，单位为厘米。

输入的最后一个测试用例之后，接着一行 $\texttt{0 0}$ 表示输入结束。

## 输出格式

对于每个测试用例，输出一行，包含国王需要支付的最少金币数量来屠龙。如果卢沃特的骑士无法屠龙，输出 $\texttt{Loowater is doomed!}$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
2 3
5
4
7
8
4
2 1
5
5
10
0 0
```

### 输出

```
11
Loowater is doomed!
```



---

---
title: "Age Sort"
layout: "post"
diff: 普及-
pid: UVA11462
tag: ['排序', '优先队列', '队列']
---

# Age Sort

## 题目描述

给定一个国家所有人的年龄（以年为单位），且每个人的年龄至少为 $1$ 岁。你知道该国没有人活到 $100$ 岁或以上。现在，你有一个非常简单的任务：将所有年龄按升序排序。

## 输入格式

输入文件中有多个测试用例。每个测试用例以一个整数 $n$ 开头（$0 < n \le 2 \times 10 ^ 6$)，表示总人数。接下来的一行中有 $n$ 个整数，表示每个人的年龄。输入以 $n = 0$ 终止，这个测试用例不应被处理。

## 输出格式

对于每个测试用例，打印一行包含 $n$ 个用空格分隔的整数。这些整数是该国家按升序排列的年龄。

**注意**：输入数据非常大（约 25MB），因此需要使用更快的输入输出。

---

Translated by User 735713.

## 样例 #1

### 输入

```
5
3 4 2 1 5
5
2 3 2 3 1
0
```

### 输出

```
1 2 3 4 5
1 2 2 3 3
```



---

---
title: "Commando War"
layout: "post"
diff: 普及-
pid: UVA11729
tag: ['贪心', '排序']
---

# Commando War

## 题目描述

>  _我们在树林里等待命令，前线的消息却始终没有传来  
到傍晚，枪声已经遥远  
啊，我们悄悄地穿过阴影，轻轻地从树间溜走  
在薄雾中穿过他们的防线，跪着爬过田野  
而我所能看到的  
是空中的火焰，发出红光，映衬着随风飘散的烟雾_

有一场对你的国家来说形势并不乐观的战争。现在是时候行动了。你有一支突击队可以调遣，并计划对附近一个重要的敌军营地进行伏击。你的队伍里有 $N$ 名士兵。在你总体的计划中，每个士兵都有独特的职责，你不希望任何士兵知道其他人的计划，以便每个人都能专注于自己的任务。为了达成这一点，你分别向每个士兵简要说明任务，并在他们被派往战场之前单独进行简报。你知道每个士兵完成任务需要一定的时间。你也很清楚给每个士兵进行简报需要多长时间。由于你急于尽快完成整个行动，你需要找到一个简报顺序，使所有士兵完成任务的总时间最少。你可以假设，没有士兵的计划依赖于其他士兵的任务。换句话说，一旦士兵开始执行任务，他可以不间断地完成任务。

## 输入格式

输入文件中会有多个测试用例。每个测试用例以一个整数 $N$（$1 \le N \le 1000$）开始，表示士兵的数量。接下来 $N$ 行，每行描述一个士兵，并给出两个整数 $B$（$1 \le B \le 10000$）和 $J$（$1 \le J \le 10000$）。表示向该士兵简报所需的时间是 $B$ 秒，该士兵完成任务所需的时间是 $J$ 秒。输入由 $N = 0$ 表示结束，这个测试用例不应被处理。

## 输出格式

对于每个测试用例，按 $\texttt{Case }X\texttt{: }Y$ 的格式打印一行，其中 $X$ 是测试用例编号，$Y$ 是从第一次简报开始到所有任务完成所经过的总秒数。

---

Translated by User 735713.

## 样例 #1

### 输入

```
3
2 5
3 2
2 1
3
3 3
4 4
5 5
0
```

### 输出

```
Case 1: 8
Case 2: 15
```



---

---
title: "古老的密码 Ancient Cipher"
layout: "post"
diff: 普及-
pid: UVA1339
tag: ['字符串', '排序', '概率论']
---

# 古老的密码 Ancient Cipher

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4085

[PDF](https://uva.onlinejudge.org/external/13/p1339.pdf)

## 样例 #1

### 输入

```
JWPUDJSTVP
VICTORIOUS
MAMA
ROME
HAHA
HEHE
AAA
AAA
NEERCISTHEBEST
SECRETMESSAGES
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "盒子 Box"
layout: "post"
diff: 普及-
pid: UVA1587
tag: ['排序']
---

# 盒子 Box

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4462

[PDF](https://uva.onlinejudge.org/external/15/p1587.pdf)



---

---
title: "对称轴 Symmetry"
layout: "post"
diff: 普及-
pid: UVA1595
tag: ['枚举', '排序', '构造']
---

# 对称轴 Symmetry

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4470

[PDF](https://uva.onlinejudge.org/external/15/p1595.pdf)



---

---
title: "Word Amalgamation"
layout: "post"
diff: 普及-
pid: UVA642
tag: ['字符串', '排序']
---

# Word Amalgamation

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=583

[PDF](https://uva.onlinejudge.org/external/6/p642.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/798288cf0a5caae5367a31141c3cf2e90bd3b5cb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/d85b48af6838aac4769be70e174b7480fc2b98e7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA642/d8237ee3b00c49d0666058cf53b6b711aad2bdf6.png)

## 样例 #1

### 输入

```
tarp
given
score
refund
only
trap
work
earn
course
pepper
part
XXXXXX
resco
nfudre
aptr
sett
oresuc
XXXXXX
```

### 输出

```
score
******
refund
******
part
tarp
trap
******
NOT A VALID WORD
******
course
******
```



---



---

# 题号列表

- UVA10474 - 大理石在哪儿 Where is the Marble?
- UVA11292 - Dragon of Loowater
- UVA11462 - Age Sort
- UVA11729 - Commando War
- UVA1339 - 古老的密码 Ancient Cipher
- UVA1587 - 盒子 Box
- UVA1595 - 对称轴 Symmetry
- UVA642 - Word Amalgamation


---

---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---

---
title: "最大乘积 Maximum Product"
layout: "post"
diff: 普及-
pid: UVA11059
tag: ['搜索', '枚举', '前缀和']
---

# 最大乘积 Maximum Product

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2000

[PDF](https://uva.onlinejudge.org/external/110/p11059.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/65771c7c6d1492d75695a5505a88282671afede0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/057abe21049b4423b1de44dfdc2de12075eae6eb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/341e4b9b0d67601bc1876729c0e2aae16988584e.png)

## 样例 #1

### 输入

```
3
2 4 -3
5
2 5 -1 2 -1
```

### 输出

```
Case #1: The maximum product is 8.

Case #2: The maximum product is 20.
```



---

---
title: "刽子手的游戏 Hangman Judge"
layout: "post"
diff: 普及-
pid: UVA489
tag: ['模拟', '字符串', '搜索']
---

# 刽子手的游戏 Hangman Judge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=430

[PDF](https://uva.onlinejudge.org/external/4/p489.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/5235bc315d8684bc30728d37f52e7f53bcd8dccb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/c4ea20c647fbaae88cdeb4ee1428a3bc412a001f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/1fdc8a8950ad27b9c821b2ad0fbaf563f3f4bca0.png)

## 样例 #1

### 输入

```
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
```

### 输出

```
Round 1
You win.
Round 2
You chickened out.
Round 3
You lose.
```



---

---
title: "油田 Oil Deposits"
layout: "post"
diff: 普及-
pid: UVA572
tag: ['搜索', '深度优先搜索 DFS', '连通块']
---

# 油田 Oil Deposits

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=513

[PDF](https://uva.onlinejudge.org/external/5/p572.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/ce90a5dd1ff852d09612a3d726a859f2f238d409.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/e054765bf4e9769be3a53a455e412d62189dbbff.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/99ea5e1b8c71aa83bbd6eed7a0e27de87f60a175.png)

## 样例 #1

### 输入

```
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0
```

### 输出

```
0
1
2
2
```



---



---

# 题号列表

- UVA10474 - 大理石在哪儿 Where is the Marble?
- UVA11059 - 最大乘积 Maximum Product
- UVA489 - 刽子手的游戏 Hangman Judge
- UVA572 - 油田 Oil Deposits


---

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



---

# 题号列表

- UVA100 - The 3n + 1 problem
- UVA11401 - Triangle Counting
- UVA11461 - Square Numbers


---

---
title: "对称轴 Symmetry"
layout: "post"
diff: 普及-
pid: UVA1595
tag: ['枚举', '排序', '构造']
---

# 对称轴 Symmetry

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4470

[PDF](https://uva.onlinejudge.org/external/15/p1595.pdf)



---



---

# 题号列表

- UVA1595 - 对称轴 Symmetry


---

---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---

---
title: "The Wedding"
layout: "post"
diff: 普及-
pid: UVA10662
tag: ['枚举']
---

# The Wedding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1603

[PDF](https://uva.onlinejudge.org/external/106/p10662.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/ab41e0babb1499da2a267d5f5662f0b7680375d6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/e776e9cac9929d4317c383d59ddc5df445b4a597.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/ecea46e33e04efcd8549429096690e8743c70af2.png)

## 样例 #1

### 输入

```
2 2 2
12 0 0
1 1 1
34 0 0
3 1 1
21 1 0
2 1 0
2 2 2
12 0 0
1 0 0
34 0 0
3 0 0
21 0 0
2 0 0
5 5 6
970 0 1 1 1 0
856 0 0 0 0 0
1290 1 0 0 1 0
1361 0 0 1 0 0
82 0 0 0 0 1
1182 0 0 0 1 1 0
450 0 1 1 0 0 1
895 0 0 1 0 1 1
1865 0 1 0 0 1 1
183 1 1 1 1 1 0
252 1 1 1 0 1
1813 1 0 0 1 1
1429 0 0 1 0 0
1522 1 1 1 0 0
1762 0 0 1 0 1
1946 0 1 0 0 0
```

### 输出

```
Don't get married!
1 1 1:6
4 1 3:2054
```



---

---
title: "最大乘积 Maximum Product"
layout: "post"
diff: 普及-
pid: UVA11059
tag: ['搜索', '枚举', '前缀和']
---

# 最大乘积 Maximum Product

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2000

[PDF](https://uva.onlinejudge.org/external/110/p11059.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/65771c7c6d1492d75695a5505a88282671afede0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/057abe21049b4423b1de44dfdc2de12075eae6eb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/341e4b9b0d67601bc1876729c0e2aae16988584e.png)

## 样例 #1

### 输入

```
3
2 4 -3
5
2 5 -1 2 -1
```

### 输出

```
Case #1: The maximum product is 8.

Case #2: The maximum product is 20.
```



---

---
title: "GCD"
layout: "post"
diff: 普及-
pid: UVA11417
tag: ['枚举']
---

# GCD

## 题目描述

给定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 501$ 。

## 样例 #1

### 输入

```
10
100
500
0
```

### 输出

```
67
13015
442011
```



---

---
title: "Fill the Square"
layout: "post"
diff: 普及-
pid: UVA11520
tag: ['枚举']
---

# Fill the Square

## 题目描述

在一个$n*n$的网格中填了一些大写字母，你的任务是把剩下的格子中也填满大写字母，使得任意两个相邻的格子(即有公共边的格子)中的字母不同。如果有多种填法，则要求按照从上到下，从左到右的顺序把所以格子连接起来得到的字符串的字典序应该尽量小。

## 输入格式

输入的第一行为测试数据的组数$T$.每组数据的第一行为$n(1<=10)$,即网格的行数和列数；以下$n$行每行$n$个字符，表示整个网格。为了清楚起见，本题用小数点表示没有填字母的格子。

## 输出格式

对于每组数据，输出填满字母后的网格

感谢@洛谷万岁 提供的翻译

## 样例 #1

### 输入

```
2
3
...
...
...
3
...
A..
...
```

### 输出

```
Case 1:
ABA
BAB
ABA
Case 2:
BAB
ABA
BAB
```



---

---
title: "丑数 Ugly Numbers"
layout: "post"
diff: 普及-
pid: UVA136
tag: ['枚举', '优先队列', '队列']
---

# 丑数 Ugly Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=72

[PDF](https://uva.onlinejudge.org/external/1/p136.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/9235847457e3c8f707f609605cbc21fd7bb05029.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/ed5a845059370c8ba7ec4955b10f7eead4ab3787.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/c8116baef73c601c2156d6d31ee1e30b14b9b560.png)

## 样例 #1

### 输入

```

```

### 输出

```
The 1500'th ugly number is &lt;number&gt;.
```



---

---
title: "生成元 Digit Generator"
layout: "post"
diff: 普及-
pid: UVA1583
tag: ['枚举']
---

# 生成元 Digit Generator

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4458

[PDF](https://uva.onlinejudge.org/external/15/p1583.pdf)

## 样例 #1

### 输入

```
3
216
121
2005
```

### 输出

```
198
0
1979
```



---

---
title: "对称轴 Symmetry"
layout: "post"
diff: 普及-
pid: UVA1595
tag: ['枚举', '排序', '构造']
---

# 对称轴 Symmetry

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4470

[PDF](https://uva.onlinejudge.org/external/15/p1595.pdf)



---

---
title: "除法 Division"
layout: "post"
diff: 普及-
pid: UVA725
tag: ['枚举']
---

# 除法 Division

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=666

[PDF](https://uva.onlinejudge.org/external/7/p725.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/9177f6f6723402a8ca5cd51e53c7912c7289196b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/eb406bd4ea0c6d996b8d045c8d41bdca36a0713e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/03ea8e037e00b0eb98a658d2d9f018fa5375f0c6.png)

## 样例 #1

### 输入

```
61
62
0
```

### 输出

```
There are no solutions for 61.

79546 / 01283 = 62
94736 / 01528 = 62
```



---



---

# 题号列表

- UVA10474 - 大理石在哪儿 Where is the Marble?
- UVA10662 - The Wedding
- UVA11059 - 最大乘积 Maximum Product
- UVA11417 - GCD
- UVA11520 - Fill the Square
- UVA136 - 丑数 Ugly Numbers
- UVA1583 - 生成元 Digit Generator
- UVA1595 - 对称轴 Symmetry
- UVA725 - 除法 Division


---

---
title: "Clock Patience"
layout: "post"
diff: 普及-
pid: UVA170
tag: ['模拟', '栈', '队列']
---

# Clock Patience

## 题目描述

Card sharp Albert (Foxy) Smith 正在写一本有关于耐心游戏的书。为了仔细检查书中的例子，他正在编写程序以找到最佳玩法。

一个叫做 Clock Patience 的游戏的描述如下：

扑克牌面朝下按顺时针方向绕一个圆形发牌，代表一个时钟。每个小时上有一堆卡片，时钟中心还有一堆额外的卡片。第一张牌放在一点钟的位置，第二张放在两点钟，依此类推，顺时针方向放置，每第十三张牌放到时钟的中心。这就形成了十三堆，每堆里有四张牌是面朝下的。（下文中用 T 来代替 $10$）
![](https://cdn.luogu.com.cn/upload/image_hosting/zxlzflxl.png)

发完牌后游戏开始。K 牌堆的顶牌（即最后一张发的牌）作为当前牌。此后按照如下方式进行：

1. 将当前牌翻开，放在其点数对应的牌堆的最下面。
2. 当前牌堆的最上面的牌成为新的当前牌。
3. 如果当前牌正面朝上，游戏结束。

现在写一个程序，输入一叠被打乱的牌，然后玩这个游戏。

## 输入格式

（译者注：虽然原题面没提及，但根据译者的尝试，此题应该有多组测试数据）

此题有多组测试数据，每一个测试数据包含 $4$ 行，每行有 $13$ 张牌，每场牌用两个字母表示。第一个字母表示点数（用 T 来代替 $10$），第二个字母表示花色。输入是倒序输入的，因此放的第一张牌就是输入的最后一张牌。

输入以一行 ```#``` 结束。

## 输出格式

对于每一个测试数据输出一行。

每一行先包含一个数字，表示总共翻开了多少张牌。数字有两位，必要时在前面补 ```0```。接着紧接着是一个 ```,```，和最后的当前牌（按照输入的格式输出）。

## 样例 #1

### 输入

```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#
```

### 输出

```
44,KD
```



---

---
title: "铁轨 Rails"
layout: "post"
diff: 普及-
pid: UVA514
tag: ['模拟', '栈']
---

# 铁轨 Rails

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=455

[PDF](https://uva.onlinejudge.org/external/5/p514.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/a8f0af9a2adeaeaab1d1906c3f3116afa0c6b444.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/03b4e1924e74948bc01f3f42cd5a31502f1c39b6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/7e96780a876f827180dea25139c1c77bbfb94937.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0
```

### 输出

```
Yes
No

Yes
```



---



---

# 题号列表

- UVA170 - Clock Patience
- UVA514 - 铁轨 Rails


---

---
title: "古老的密码 Ancient Cipher"
layout: "post"
diff: 普及-
pid: UVA1339
tag: ['字符串', '排序', '概率论']
---

# 古老的密码 Ancient Cipher

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4085

[PDF](https://uva.onlinejudge.org/external/13/p1339.pdf)

## 样例 #1

### 输入

```
JWPUDJSTVP
VICTORIOUS
MAMA
ROME
HAHA
HEHE
AAA
AAA
NEERCISTHEBEST
SECRETMESSAGES
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "分子量 Molar mass"
layout: "post"
diff: 普及-
pid: UVA1586
tag: ['字符串', '概率论']
---

# 分子量 Molar mass

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4461

[PDF](https://uva.onlinejudge.org/external/15/p1586.pdf)

## 样例 #1

### 输入

```
4
C
C6H5OH
NH2CH2COOH
C12H22O11
```

### 输出

```
12.010
94.108
75.070
342.296
```



---



---

# 题号列表

- UVA1339 - 古老的密码 Ancient Cipher
- UVA1586 - 分子量 Molar mass


---

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
title: "卡片游戏 Throwing cards away I"
layout: "post"
diff: 普及-
pid: UVA10935
tag: ['模拟', '队列']
---

# 卡片游戏 Throwing cards away I

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1876

[PDF](https://uva.onlinejudge.org/external/109/p10935.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/04b5bf3f22988460c478d5e0eaad7b24fe43b5d4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/cc097601511901dac24f0e4d66cccd4367d03148.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/87cedea733d4be64fa50b2ae857327019eb4a64d.png)

## 样例 #1

### 输入

```
7
19
10
6
0
```

### 输出

```
Discarded cards: 1, 3, 5, 7, 4, 2
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 8, 12, 16, 2, 10, 18, 14
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 2, 6, 10, 8
Remaining card: 4
Discarded cards: 1, 3, 5, 2, 6
Remaining card: 4
```



---

---
title: "Dragon of Loowater"
layout: "post"
diff: 普及-
pid: UVA11292
tag: ['模拟', '贪心', '排序']
---

# Dragon of Loowater

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/tqycbsg2.png)

从前，在 Loowater 王国，一场小麻烦变成了一个大问题。Loowater 中部的 Rellau 溪岸一直是大雁繁殖的理想之地。由于缺乏天敌，大雁的数量失控。Loowater 的人民大多远离大雁。偶尔会有一只大雁袭击人们，可能会咬掉一两个手指，但总的来说，人民把大雁当作一个小麻烦忍受着。

有一天，一次奇怪的变异发生了，一只大雁产下了一条多头的喷火龙。当这条龙长大后，它威胁要把 Loowater 王国烧成灰烬。Loowater 遇到了一个大问题。国王十分惊恐，召集他的骑士们去屠龙，拯救王国。

骑士们解释道：“要屠龙，我们必须砍下它所有的头。每个骑士只能砍掉龙的一个头。龙的头大小不一。为了砍掉一个头，骑士必须至少和龙头的直径一样高。骑士工会要求，砍掉一个头的骑士必须得到相当于其身高每厘米一枚金币的报酬。”

有足够的骑士来打败这条龙吗？国王召集他的顾问们来帮他决定该雇佣多少骑士以及选择哪些骑士。在花费大量金钱建造米尔公园后，国王想要将屠龙的开支降到最低。作为顾问之一，你的任务是帮助国王。你非常认真地对待这个任务：如果失败了，你和整个王国都将被烧成灰烬！

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含两个介于 $1$ 和 $20000$ 之间（包括 $1$ 和 $20000$）的整数，分别表示龙的头数 $n$ 和王国中骑士的数量 $m$。接下来的 $n$ 行每行包含一个整数，给出龙头的直径，单位为厘米。接下来的 $m$ 行每行包含一个整数，指定卢沃特骑士的身高，单位为厘米。

输入的最后一个测试用例之后，接着一行 $\texttt{0 0}$ 表示输入结束。

## 输出格式

对于每个测试用例，输出一行，包含国王需要支付的最少金币数量来屠龙。如果卢沃特的骑士无法屠龙，输出 $\texttt{Loowater is doomed!}$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
2 3
5
4
7
8
4
2 1
5
5
10
0 0
```

### 输出

```
11
Loowater is doomed!
```



---

---
title: "Help is needed for Dexter"
layout: "post"
diff: 普及-
pid: UVA11384
tag: ['模拟', '递归']
---

# Help is needed for Dexter

## 题目描述

Dexter 对 Dee Dee 感到厌烦了，所以他决定让 Dee Dee 玩一个游戏来让她忙起来。这个游戏很容易玩，但至少对 Dee Dee 来说不容易赢。但是，Dexter 没有时间浪费在这种无聊的任务上，所以他需要你的帮助。

游戏中有一个按钮，当按下按钮时，电脑将随机选择一个数字 $N$。然后屏幕上会显示从 $1$ 到 $N$ 的数字。Dee Dee 可以从屏幕上的数字中选择任意数量的数字，然后她将命令计算机从所选数字中减去她选择的一个正整数（不一定是屏幕上的数字）。她的目标是让所有数字都变成 $0$。

例如，如果 $N = 3$，屏幕上将显示 $3$ 个数字：$1$、$2$、$3$。假设她现在选择 $1$ 和 $2$，命令计算机减去 $1$，那么屏幕上的数字将变为：$0$、$1$、$3$。然后她选择 $1$ 和 $3$，并命令减去 $1$，现在屏幕上的数字是 $0$、$0$、$2$。最后她选择 $2$ 并减去 $2$，所有数字变为 $0$。

Dexter 并不愚蠢，明白这可以很容易地完成，所以为了增加难度，他将为每个 $N$ 给出一个限制 $L$，并且确保 $L$ 是仍然能在 $L$ 步内完成的最小值。但 Dexter 没有时间去思考如何为每个 $N$ 确定 $L$，因此他请求你编写一个程序，输入 $N$，输出 $L$。

## 输入格式

输入由多行组成，每行包含一个 $N$，其中 $1 \le N \le 10 ^ 9$。输入将由文件末尾终止。

## 输出格式

对于每个 $N$，在单独的一行中输出对应的 $L$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1
2
3
```

### 输出

```
1
2
2
```



---

---
title: "UVA141 The Spot Game"
layout: "post"
diff: 普及-
pid: UVA141
tag: ['模拟', '字符串']
---

# UVA141 The Spot Game

## 题目背景

有一种叫做 Spot 的游戏，在一个 $N \times N$ 的棋盘上玩，下图是当 $N=4$ 时一些可能的样子：
![](https://cdn.luogu.com.cn/upload/image_hosting/6j8s01tj.png)

游戏中，玩家可以在空的地方放置一颗黑棋或拿走一颗黑棋，从而产生多种图案。如果棋盘上的图案（或者旋转了 $90^{\circ}$ 或 $180^{\circ}$）在之前重复过，则产生了这个图案的玩家失败，另一个玩家胜利。

例如，如果上图中第一种图案出现过，那么另外三种都会结束游戏，但最后一种不会。

## 题目描述

现在给出若干个游戏中每个玩家的操作，请你判断游戏的胜负情况。

## 输入格式

输入包含若干个游戏，每一行首先输入一个整数 $N$ （$2 \leq N \leq 50$），代表棋盘的大小。

接下来有 $2N$ 行，每一行代表一个操作，每一行不一定是必要的。每一行都输入两个整数（$x,y$）代表棋盘上的一个坐标（$1 \leq x,y \leq N$），接着一个空格后输入一个字符```+```或```-```代表增加或者删除。

保证每一个操作中不会在已有棋子的地方放下棋子或在没有棋子的地方拿走棋子。

输入的最后一行为一个```0```。

## 输出格式

对于每个游戏，输出哪位玩家在游戏进行到第几步时获得了胜利。如果平局，则输出```Draw```。

## 说明/提示

在输入的第一个游戏中，第二位玩家在第 $3$ 步时取得胜利。

第二个游戏到最后没有出现重复的情况，因此平局。

## 样例 #1

### 输入

```
2
1 1 +
2 2 +
2 2 -
1 2 +
2
1 1 +
2 2 +
1 2 +
2 2 -
0
```

### 输出

```
Player 2 wins on move 3
Draw
```



---

---
title: "环状序列 Circular Sequence"
layout: "post"
diff: 普及-
pid: UVA1584
tag: ['模拟', '字符串']
---

# 环状序列 Circular Sequence

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4459

[PDF](https://uva.onlinejudge.org/external/15/p1584.pdf)



---

---
title: "Ducci序列 Ducci Sequence"
layout: "post"
diff: 普及-
pid: UVA1594
tag: ['模拟']
---

# Ducci序列 Ducci Sequence

## 题目描述

对于一个 $n$ 元组（$a_1,a_2,\cdots,a_n$），可以对每个数求出它和下一个数的差的绝对值，得到一个新的 $n$ 元组（$|a_1-a_2|,|a_2-a_3|,\cdots,|a_n-a_1|$）。重复这个过程，得到的序列称为 Ducci 序列，例如：

$$(8,11,2,7)\rightarrow(3,9,5,1)\rightarrow(6,4,4,2)\rightarrow(2,0,2,4)\rightarrow(2,2,2,2)\rightarrow(0,0,0,0)$$

也有的 Ducci 序列最终会循环。输入 $n$ 元组（$3\le n\le15$），你的任务是判断它最终会变成0还是会循环。输入保证最多 $1000$ 步就会变成 $0$ 或循环。

## 输出格式

感谢 @andyli 提供的翻译

## 样例 #1

### 输入

```
4
4
8 11 2 7
5
4 2 0 2 0
7
0 0 0 0 0 0 0
6
1 2 3 1 2 3

```

### 输出

```
ZERO
LOOP
ZERO
LOOP

```



---

---
title: "Clock Patience"
layout: "post"
diff: 普及-
pid: UVA170
tag: ['模拟', '栈', '队列']
---

# Clock Patience

## 题目描述

Card sharp Albert (Foxy) Smith 正在写一本有关于耐心游戏的书。为了仔细检查书中的例子，他正在编写程序以找到最佳玩法。

一个叫做 Clock Patience 的游戏的描述如下：

扑克牌面朝下按顺时针方向绕一个圆形发牌，代表一个时钟。每个小时上有一堆卡片，时钟中心还有一堆额外的卡片。第一张牌放在一点钟的位置，第二张放在两点钟，依此类推，顺时针方向放置，每第十三张牌放到时钟的中心。这就形成了十三堆，每堆里有四张牌是面朝下的。（下文中用 T 来代替 $10$）
![](https://cdn.luogu.com.cn/upload/image_hosting/zxlzflxl.png)

发完牌后游戏开始。K 牌堆的顶牌（即最后一张发的牌）作为当前牌。此后按照如下方式进行：

1. 将当前牌翻开，放在其点数对应的牌堆的最下面。
2. 当前牌堆的最上面的牌成为新的当前牌。
3. 如果当前牌正面朝上，游戏结束。

现在写一个程序，输入一叠被打乱的牌，然后玩这个游戏。

## 输入格式

（译者注：虽然原题面没提及，但根据译者的尝试，此题应该有多组测试数据）

此题有多组测试数据，每一个测试数据包含 $4$ 行，每行有 $13$ 张牌，每场牌用两个字母表示。第一个字母表示点数（用 T 来代替 $10$），第二个字母表示花色。输入是倒序输入的，因此放的第一张牌就是输入的最后一张牌。

输入以一行 ```#``` 结束。

## 输出格式

对于每一个测试数据输出一行。

每一行先包含一个数字，表示总共翻开了多少张牌。数字有两位，必要时在前面补 ```0```。接着紧接着是一个 ```,```，和最后的当前牌（按照输入的格式输出）。

## 样例 #1

### 输入

```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#
```

### 输出

```
44,KD
```



---

---
title: "纵横字谜的答案 Crossword Answers"
layout: "post"
diff: 普及-
pid: UVA232
tag: ['模拟', '字符串', '队列']
---

# 纵横字谜的答案 Crossword Answers

## 题目描述

有一个 $r$ 行 $c$ 列 $(1<r,c<10)$ 的网格，黑格为 `*` ，每个白格都填有一个字母。如果一个白格的左边相邻位置或者上边相邻位置没有白格（可能是黑格，也可能出了网格边界），则称这个白格是一个起始格。

你的任务是先找出网格中所有横向单词（`Across`）。这些单词必须从一个起始格（左边是黑格，或是第一列）开始，向右延伸到一个黑格的左边或者整个网格的最右列。然后找出所有竖向单词（`Down`），规则同上，这些单词必须从一个起始格（上边是黑格，或是第一行）开始，向下延伸到一个黑格的上边或者整个网格的最下行。

## 输入格式

有多个矩阵输入，对于第 $i$ 个矩阵，第一行输入 $r_i$ 和 $c_i$ 并以空格隔开。 $(1<r_i,c_i<10)$，表示此网格为 $r_i$ 行 $c_i$ 列，然后下面输入矩阵的内容，里面为大写字母或是 `*`，以 `0` 代表所有矩阵输入结束。

## 输出格式

每个谜题的输出包括谜题的标识符（如 `puzzle #1:`）和横向竖向单词列表。每个单词每行只输出一个并先输出以其相应定义的数量的递增顺序数字再输出单词。

数字的输出占据三个场宽并右对齐。

横向列表的标题是 `Across`，竖向单词列表的标题是 `Down`。

在列表为空的情况下（网格中的所有正方形均为黑色），`Across` 和 `Down` 标题仍应出现。

## 样例 #1

### 输入

```
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0
```

### 输出

```
puzzle #1:
Across
1.AT
3.O
Down
1.A
2.TO
puzzle #2:
Across
1.AIM
4.DEN
7.ME
8.ONE
9.UPON
11.TO
12.SO
13.ERIN
15.SA
17.OR
18.IES
19.DEA
Down
1.A
2.IMPOSE
3.MEO
4.DO
5.ENTIRE
6.NEON
9.US
10.NE
14.ROD
16.AS
18.I
20.A
```



---

---
title: "Encoder and Decoder"
layout: "post"
diff: 普及-
pid: UVA444
tag: ['模拟']
---

# Encoder and Decoder

## 题目描述

### 题意简述
给定一串字符(长度$\le80$)，如果它是明文，转成密文，如果它是密文，转成明文。  
明文中只会出现以下字符：大小写字母，感叹号，逗号，句号，空格，冒号，分号，问号(均为英文标点)。  
加密方式是：把每个字符转换成对应的ASCII码，然后整体反转。  
e.g. 对于明文`abc`，首先将其转成对应的ASCII码：`97 98 99`，去除中间的空格：`979899`，整体反转输出：`998979`。

## 输入格式

输入有多组数据，每组数据一行，一个字符串表示明文或密文(需要自己判断)。

## 输出格式

对于每组数据，输出共一行，一个字符串表示答案。

## 样例 #1

### 输入

```
abc
798999
Have a Nice Day !
```

### 输出

```
998979
cba
332312179862310199501872379231018117927
```



---

---
title: "刽子手的游戏 Hangman Judge"
layout: "post"
diff: 普及-
pid: UVA489
tag: ['模拟', '字符串', '搜索']
---

# 刽子手的游戏 Hangman Judge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=430

[PDF](https://uva.onlinejudge.org/external/4/p489.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/5235bc315d8684bc30728d37f52e7f53bcd8dccb.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/c4ea20c647fbaae88cdeb4ee1428a3bc412a001f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/1fdc8a8950ad27b9c821b2ad0fbaf563f3f4bca0.png)

## 样例 #1

### 输入

```
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
```

### 输出

```
Round 1
You win.
Round 2
You chickened out.
Round 3
You lose.
```



---

---
title: "铁轨 Rails"
layout: "post"
diff: 普及-
pid: UVA514
tag: ['模拟', '栈']
---

# 铁轨 Rails

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=455

[PDF](https://uva.onlinejudge.org/external/5/p514.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/a8f0af9a2adeaeaab1d1906c3f3116afa0c6b444.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/03b4e1924e74948bc01f3f42cd5a31502f1c39b6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA514/7e96780a876f827180dea25139c1c77bbfb94937.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0
```

### 输出

```
Yes
No

Yes
```



---



---

# 题号列表

- UVA100 - The 3n + 1 problem
- UVA10935 - 卡片游戏 Throwing cards away I
- UVA11292 - Dragon of Loowater
- UVA11384 - Help is needed for Dexter
- UVA141 - UVA141 The Spot Game
- UVA1584 - 环状序列 Circular Sequence
- UVA1594 - Ducci序列 Ducci Sequence
- UVA170 - Clock Patience
- UVA232 - 纵横字谜的答案 Crossword Answers
- UVA444 - Encoder and Decoder
- UVA489 - 刽子手的游戏 Hangman Judge
- UVA514 - 铁轨 Rails


---

---
title: "油田 Oil Deposits"
layout: "post"
diff: 普及-
pid: UVA572
tag: ['搜索', '深度优先搜索 DFS', '连通块']
---

# 油田 Oil Deposits

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=513

[PDF](https://uva.onlinejudge.org/external/5/p572.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/ce90a5dd1ff852d09612a3d726a859f2f238d409.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/e054765bf4e9769be3a53a455e412d62189dbbff.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/99ea5e1b8c71aa83bbd6eed7a0e27de87f60a175.png)

## 样例 #1

### 输入

```
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0
```

### 输出

```
0
1
2
2
```



---



---

# 题号列表

- UVA572 - 油田 Oil Deposits


---

---
title: "Gergovia的酒交易 Wine trading in Gergovia"
layout: "post"
diff: 普及-
pid: UVA11054
tag: ['贪心', '前缀和']
---

# Gergovia的酒交易 Wine trading in Gergovia

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1995

[PDF](https://uva.onlinejudge.org/external/110/p11054.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/ced1606866ddabe301a52d0310f9433bc4587f7e.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/26ec5db5cf20e0de0ecadbcd24f88389305b92a4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/178f45e194980c55bc177e289c65e48b01d9fea5.png)

## 样例 #1

### 输入

```
5
5 -4 1 -3 1
6
-1000 -1000 -1000 1000 1000 1000
0
```

### 输出

```
9
9000
```



---

---
title: "Dragon of Loowater"
layout: "post"
diff: 普及-
pid: UVA11292
tag: ['模拟', '贪心', '排序']
---

# Dragon of Loowater

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/tqycbsg2.png)

从前，在 Loowater 王国，一场小麻烦变成了一个大问题。Loowater 中部的 Rellau 溪岸一直是大雁繁殖的理想之地。由于缺乏天敌，大雁的数量失控。Loowater 的人民大多远离大雁。偶尔会有一只大雁袭击人们，可能会咬掉一两个手指，但总的来说，人民把大雁当作一个小麻烦忍受着。

有一天，一次奇怪的变异发生了，一只大雁产下了一条多头的喷火龙。当这条龙长大后，它威胁要把 Loowater 王国烧成灰烬。Loowater 遇到了一个大问题。国王十分惊恐，召集他的骑士们去屠龙，拯救王国。

骑士们解释道：“要屠龙，我们必须砍下它所有的头。每个骑士只能砍掉龙的一个头。龙的头大小不一。为了砍掉一个头，骑士必须至少和龙头的直径一样高。骑士工会要求，砍掉一个头的骑士必须得到相当于其身高每厘米一枚金币的报酬。”

有足够的骑士来打败这条龙吗？国王召集他的顾问们来帮他决定该雇佣多少骑士以及选择哪些骑士。在花费大量金钱建造米尔公园后，国王想要将屠龙的开支降到最低。作为顾问之一，你的任务是帮助国王。你非常认真地对待这个任务：如果失败了，你和整个王国都将被烧成灰烬！

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含两个介于 $1$ 和 $20000$ 之间（包括 $1$ 和 $20000$）的整数，分别表示龙的头数 $n$ 和王国中骑士的数量 $m$。接下来的 $n$ 行每行包含一个整数，给出龙头的直径，单位为厘米。接下来的 $m$ 行每行包含一个整数，指定卢沃特骑士的身高，单位为厘米。

输入的最后一个测试用例之后，接着一行 $\texttt{0 0}$ 表示输入结束。

## 输出格式

对于每个测试用例，输出一行，包含国王需要支付的最少金币数量来屠龙。如果卢沃特的骑士无法屠龙，输出 $\texttt{Loowater is doomed!}$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
2 3
5
4
7
8
4
2 1
5
5
10
0 0
```

### 输出

```
11
Loowater is doomed!
```



---

---
title: "装箱 Bin Packing"
layout: "post"
diff: 普及-
pid: UVA1149
tag: ['贪心']
---

# 装箱 Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3590

[PDF](https://uva.onlinejudge.org/external/11/p1149.pdf)



---

---
title: "Commando War"
layout: "post"
diff: 普及-
pid: UVA11729
tag: ['贪心', '排序']
---

# Commando War

## 题目描述

>  _我们在树林里等待命令，前线的消息却始终没有传来  
到傍晚，枪声已经遥远  
啊，我们悄悄地穿过阴影，轻轻地从树间溜走  
在薄雾中穿过他们的防线，跪着爬过田野  
而我所能看到的  
是空中的火焰，发出红光，映衬着随风飘散的烟雾_

有一场对你的国家来说形势并不乐观的战争。现在是时候行动了。你有一支突击队可以调遣，并计划对附近一个重要的敌军营地进行伏击。你的队伍里有 $N$ 名士兵。在你总体的计划中，每个士兵都有独特的职责，你不希望任何士兵知道其他人的计划，以便每个人都能专注于自己的任务。为了达成这一点，你分别向每个士兵简要说明任务，并在他们被派往战场之前单独进行简报。你知道每个士兵完成任务需要一定的时间。你也很清楚给每个士兵进行简报需要多长时间。由于你急于尽快完成整个行动，你需要找到一个简报顺序，使所有士兵完成任务的总时间最少。你可以假设，没有士兵的计划依赖于其他士兵的任务。换句话说，一旦士兵开始执行任务，他可以不间断地完成任务。

## 输入格式

输入文件中会有多个测试用例。每个测试用例以一个整数 $N$（$1 \le N \le 1000$）开始，表示士兵的数量。接下来 $N$ 行，每行描述一个士兵，并给出两个整数 $B$（$1 \le B \le 10000$）和 $J$（$1 \le J \le 10000$）。表示向该士兵简报所需的时间是 $B$ 秒，该士兵完成任务所需的时间是 $J$ 秒。输入由 $N = 0$ 表示结束，这个测试用例不应被处理。

## 输出格式

对于每个测试用例，按 $\texttt{Case }X\texttt{: }Y$ 的格式打印一行，其中 $X$ 是测试用例编号，$Y$ 是从第一次简报开始到所有任务完成所经过的总秒数。

---

Translated by User 735713.

## 样例 #1

### 输入

```
3
2 5
3 2
2 1
3
3 3
4 4
5 5
0
```

### 输出

```
Case 1: 8
Case 2: 15
```



---

---
title: "DNA序列 DNA Consensus String"
layout: "post"
diff: 普及-
pid: UVA1368
tag: ['字符串', '贪心']
---

# DNA序列 DNA Consensus String

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4114

[PDF](https://uva.onlinejudge.org/external/13/p1368.pdf)



---



---

# 题号列表

- UVA11054 - Gergovia的酒交易 Wine trading in Gergovia
- UVA11292 - Dragon of Loowater
- UVA1149 - 装箱 Bin Packing
- UVA11729 - Commando War
- UVA1368 - DNA序列 DNA Consensus String


---

---
title: "Base -2"
layout: "post"
diff: 普及-
pid: UVA11121
tag: ['进制']
---

# Base -2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2062

[PDF](https://uva.onlinejudge.org/external/111/p11121.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11121/fa7bc9d210580e6415e9107212fb15b89e8de60a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11121/3aa143710fe378425d127ae13ec64d3203ae1bab.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11121/ad638c7f7cb8c6e5d2e5f18c771d0a308f6bd915.png)

## 样例 #1

### 输入

```
4
1
7
-2
0
```

### 输出

```
Case #1: 1
Case #2: 11011
Case #3: 10
Case #4: 0
```



---

---
title: "IP网络 IP Networks"
layout: "post"
diff: 普及-
pid: UVA1590
tag: ['字符串', '进制', '位运算']
---

# IP网络 IP Networks

## 题目描述

亚历克斯是IP网络的管理员。他的客户每个人有一组单独的IP地址，他决定将所有IP地址分组到最小可能的IP网络中。

每个IP地址有四个部分组成，每个部分用小数点分离。格式如a,b,c,d每个部分都是一个十进制的数（0≤这个数≤255）且没有多余的前导零。

IP网络由两个4各部分的数字——网络地址和网络掩码组成。网络地址和网络掩码和IP地址写入方式相同。为了理解网络地址和网络掩码的含义，我们将它们用二进制来表述。IP地址、网络地址和网络掩码的二进制都由32位组成：a的8位（从最重要到最不重要），其次是b的8位，其次是c的8位，其次是d的8位。

IP网络包含一个2n个IP地址的范围，其中所有n>32。网络掩码始终存在32~n个第一部分设置为一，n个最后部分在二进制表示中设置为零。网络地址已任意32个n个第一部分，n个最后部分在其二进制表示中设置为零。IP网络所有的32个n位第一位相当于32位n个任意位的网络地址的所有IP地址最后一位。

我们说，一个IP网络比其他IP网络更小，那么它包含更少的IP地址。

## 输入格式

有多个测试数据。

输入文件的第一行包含一个整数m。下面m行都是一个IP地址。IP地址可能重复。

## 输出格式

每个测试数据在第一行写上网络地址，在第二行写上网络掩码。 网络地址和网络掩码代表的IP网络包括所有IP地址且最小。

## 样例输入输出：
### 样例输入#1
3

194.85.160.177

194.85.160.183

194.85.160.178

### 样例输出#1
194.85.160.176

255.255.255.248

## 说明/提示

一个IP网络的网络地址是194.85.160.176它的网络掩码是255.255.255.248

那么这个IP网络包含8个IP地址从194.85.160.176到194.85.160.183

0 ≤ n ≤ 32,1 ≤ m ≤ 1000

感谢@BIGmrsrz 提供翻译



---



---

# 题号列表

- UVA11121 - Base -2
- UVA1590 - IP网络 IP Networks


---

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
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---

---
title: "Help is needed for Dexter"
layout: "post"
diff: 普及-
pid: UVA11384
tag: ['模拟', '递归']
---

# Help is needed for Dexter

## 题目描述

Dexter 对 Dee Dee 感到厌烦了，所以他决定让 Dee Dee 玩一个游戏来让她忙起来。这个游戏很容易玩，但至少对 Dee Dee 来说不容易赢。但是，Dexter 没有时间浪费在这种无聊的任务上，所以他需要你的帮助。

游戏中有一个按钮，当按下按钮时，电脑将随机选择一个数字 $N$。然后屏幕上会显示从 $1$ 到 $N$ 的数字。Dee Dee 可以从屏幕上的数字中选择任意数量的数字，然后她将命令计算机从所选数字中减去她选择的一个正整数（不一定是屏幕上的数字）。她的目标是让所有数字都变成 $0$。

例如，如果 $N = 3$，屏幕上将显示 $3$ 个数字：$1$、$2$、$3$。假设她现在选择 $1$ 和 $2$，命令计算机减去 $1$，那么屏幕上的数字将变为：$0$、$1$、$3$。然后她选择 $1$ 和 $3$，并命令减去 $1$，现在屏幕上的数字是 $0$、$0$、$2$。最后她选择 $2$ 并减去 $2$，所有数字变为 $0$。

Dexter 并不愚蠢，明白这可以很容易地完成，所以为了增加难度，他将为每个 $N$ 给出一个限制 $L$，并且确保 $L$ 是仍然能在 $L$ 步内完成的最小值。但 Dexter 没有时间去思考如何为每个 $N$ 确定 $L$，因此他请求你编写一个程序，输入 $N$，输出 $L$。

## 输入格式

输入由多行组成，每行包含一个 $N$，其中 $1 \le N \le 10 ^ 9$。输入将由文件末尾终止。

## 输出格式

对于每个 $N$，在单独的一行中输出对应的 $L$。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1
2
3
```

### 输出

```
1
2
2
```



---



---

# 题号列表

- UVA100 - The 3n + 1 problem
- UVA10474 - 大理石在哪儿 Where is the Marble?
- UVA11384 - Help is needed for Dexter


---

---
title: "卡片游戏 Throwing cards away I"
layout: "post"
diff: 普及-
pid: UVA10935
tag: ['模拟', '队列']
---

# 卡片游戏 Throwing cards away I

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1876

[PDF](https://uva.onlinejudge.org/external/109/p10935.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/04b5bf3f22988460c478d5e0eaad7b24fe43b5d4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/cc097601511901dac24f0e4d66cccd4367d03148.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10935/87cedea733d4be64fa50b2ae857327019eb4a64d.png)

## 样例 #1

### 输入

```
7
19
10
6
0
```

### 输出

```
Discarded cards: 1, 3, 5, 7, 4, 2
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 8, 12, 16, 2, 10, 18, 14
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 2, 6, 10, 8
Remaining card: 4
Discarded cards: 1, 3, 5, 2, 6
Remaining card: 4
```



---

---
title: "Age Sort"
layout: "post"
diff: 普及-
pid: UVA11462
tag: ['排序', '优先队列', '队列']
---

# Age Sort

## 题目描述

给定一个国家所有人的年龄（以年为单位），且每个人的年龄至少为 $1$ 岁。你知道该国没有人活到 $100$ 岁或以上。现在，你有一个非常简单的任务：将所有年龄按升序排序。

## 输入格式

输入文件中有多个测试用例。每个测试用例以一个整数 $n$ 开头（$0 < n \le 2 \times 10 ^ 6$)，表示总人数。接下来的一行中有 $n$ 个整数，表示每个人的年龄。输入以 $n = 0$ 终止，这个测试用例不应被处理。

## 输出格式

对于每个测试用例，打印一行包含 $n$ 个用空格分隔的整数。这些整数是该国家按升序排列的年龄。

**注意**：输入数据非常大（约 25MB），因此需要使用更快的输入输出。

---

Translated by User 735713.

## 样例 #1

### 输入

```
5
3 4 2 1 5
5
2 3 2 3 1
0
```

### 输出

```
1 2 3 4 5
1 2 2 3 3
```



---

---
title: "丑数 Ugly Numbers"
layout: "post"
diff: 普及-
pid: UVA136
tag: ['枚举', '优先队列', '队列']
---

# 丑数 Ugly Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=72

[PDF](https://uva.onlinejudge.org/external/1/p136.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/9235847457e3c8f707f609605cbc21fd7bb05029.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/ed5a845059370c8ba7ec4955b10f7eead4ab3787.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/c8116baef73c601c2156d6d31ee1e30b14b9b560.png)

## 样例 #1

### 输入

```

```

### 输出

```
The 1500'th ugly number is &lt;number&gt;.
```



---

---
title: "Clock Patience"
layout: "post"
diff: 普及-
pid: UVA170
tag: ['模拟', '栈', '队列']
---

# Clock Patience

## 题目描述

Card sharp Albert (Foxy) Smith 正在写一本有关于耐心游戏的书。为了仔细检查书中的例子，他正在编写程序以找到最佳玩法。

一个叫做 Clock Patience 的游戏的描述如下：

扑克牌面朝下按顺时针方向绕一个圆形发牌，代表一个时钟。每个小时上有一堆卡片，时钟中心还有一堆额外的卡片。第一张牌放在一点钟的位置，第二张放在两点钟，依此类推，顺时针方向放置，每第十三张牌放到时钟的中心。这就形成了十三堆，每堆里有四张牌是面朝下的。（下文中用 T 来代替 $10$）
![](https://cdn.luogu.com.cn/upload/image_hosting/zxlzflxl.png)

发完牌后游戏开始。K 牌堆的顶牌（即最后一张发的牌）作为当前牌。此后按照如下方式进行：

1. 将当前牌翻开，放在其点数对应的牌堆的最下面。
2. 当前牌堆的最上面的牌成为新的当前牌。
3. 如果当前牌正面朝上，游戏结束。

现在写一个程序，输入一叠被打乱的牌，然后玩这个游戏。

## 输入格式

（译者注：虽然原题面没提及，但根据译者的尝试，此题应该有多组测试数据）

此题有多组测试数据，每一个测试数据包含 $4$ 行，每行有 $13$ 张牌，每场牌用两个字母表示。第一个字母表示点数（用 T 来代替 $10$），第二个字母表示花色。输入是倒序输入的，因此放的第一张牌就是输入的最后一张牌。

输入以一行 ```#``` 结束。

## 输出格式

对于每一个测试数据输出一行。

每一行先包含一个数字，表示总共翻开了多少张牌。数字有两位，必要时在前面补 ```0```。接着紧接着是一个 ```,```，和最后的当前牌（按照输入的格式输出）。

## 样例 #1

### 输入

```
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#
```

### 输出

```
44,KD
```



---

---
title: "纵横字谜的答案 Crossword Answers"
layout: "post"
diff: 普及-
pid: UVA232
tag: ['模拟', '字符串', '队列']
---

# 纵横字谜的答案 Crossword Answers

## 题目描述

有一个 $r$ 行 $c$ 列 $(1<r,c<10)$ 的网格，黑格为 `*` ，每个白格都填有一个字母。如果一个白格的左边相邻位置或者上边相邻位置没有白格（可能是黑格，也可能出了网格边界），则称这个白格是一个起始格。

你的任务是先找出网格中所有横向单词（`Across`）。这些单词必须从一个起始格（左边是黑格，或是第一列）开始，向右延伸到一个黑格的左边或者整个网格的最右列。然后找出所有竖向单词（`Down`），规则同上，这些单词必须从一个起始格（上边是黑格，或是第一行）开始，向下延伸到一个黑格的上边或者整个网格的最下行。

## 输入格式

有多个矩阵输入，对于第 $i$ 个矩阵，第一行输入 $r_i$ 和 $c_i$ 并以空格隔开。 $(1<r_i,c_i<10)$，表示此网格为 $r_i$ 行 $c_i$ 列，然后下面输入矩阵的内容，里面为大写字母或是 `*`，以 `0` 代表所有矩阵输入结束。

## 输出格式

每个谜题的输出包括谜题的标识符（如 `puzzle #1:`）和横向竖向单词列表。每个单词每行只输出一个并先输出以其相应定义的数量的递增顺序数字再输出单词。

数字的输出占据三个场宽并右对齐。

横向列表的标题是 `Across`，竖向单词列表的标题是 `Down`。

在列表为空的情况下（网格中的所有正方形均为黑色），`Across` 和 `Down` 标题仍应出现。

## 样例 #1

### 输入

```
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0
```

### 输出

```
puzzle #1:
Across
1.AT
3.O
Down
1.A
2.TO
puzzle #2:
Across
1.AIM
4.DEN
7.ME
8.ONE
9.UPON
11.TO
12.SO
13.ERIN
15.SA
17.OR
18.IES
19.DEA
Down
1.A
2.IMPOSE
3.MEO
4.DO
5.ENTIRE
6.NEON
9.US
10.NE
14.ROD
16.AS
18.I
20.A
```



---



---

# 题号列表

- UVA10935 - 卡片游戏 Throwing cards away I
- UVA11462 - Age Sort
- UVA136 - 丑数 Ugly Numbers
- UVA170 - Clock Patience
- UVA232 - 纵横字谜的答案 Crossword Answers


---

---
title: "矩阵解压 Matrix Decompressing"
layout: "post"
diff: 省选/NOI-
pid: UVA11082
tag: ['网络流', '二分图']
---

# 矩阵解压 Matrix Decompressing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2023

[PDF](https://uva.onlinejudge.org/external/110/p11082.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/4bfbadba5826e7df25fe35bb6c563f54e80f8b54.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/1c9470803fa67b39a07afe5716e1afb7f904286c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11082/d5eaf050b2d4f97e173703f6c0ab39199cfec3a6.png)

## 样例 #1

### 输入

```
2
3 4
10 31 58
10 20 37 58
3 4
10 31 58
10 20 37 58
```

### 输出

```
Matrix 1
1 6 1 2
1 2 2 16
8 2 14 3
Matrix 2
1 1 1 7
1 1 7 12
8 8 9 2
```



---

---
title: "Halum"
layout: "post"
diff: 省选/NOI-
pid: UVA11478
tag: ['二分', '图论建模', '差分约束']
---

# Halum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2473

[PDF](https://uva.onlinejudge.org/external/114/p11478.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/fe7bd946fb4e049b4a2acc693bd285a050d606f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/d8a053537747d36f9bda3b53b2e300f24860c7fb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/59cf14738847dcbac078a3ffdf4966090114e0f4.png)

## 样例 #1

### 输入

```
2 1
1 2 10
2 1
1 2 -10
3 3
1 2 4
2 3 2
3 1 5
4 5
2 3 4
4 2 5
3 4 2
3 1 0
1 2 -1
```

### 输出

```
Infinite
Infinite
3
1
```



---

---
title: "Air Raid"
layout: "post"
diff: 省选/NOI-
pid: UVA1184
tag: ['网络流', '二分图']
---

# Air Raid

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3625

[PDF](https://uva.onlinejudge.org/external/11/p1184.pdf)

## 样例 #1

### 输入

```
2
4
3
3 4
1 3
2 3
3
3
1 3
1 2
2 3

```

### 输出

```
2
1

```



---

---
title: "Knights of the Round Table"
layout: "post"
diff: 省选/NOI-
pid: UVA1364
tag: ['双连通分量', '二分图']
---

# Knights of the Round Table

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4110

[PDF](https://uva.onlinejudge.org/external/13/p1364.pdf)



---

---
title: "Ants"
layout: "post"
diff: 省选/NOI-
pid: UVA1411
tag: ['网络流', '图论建模', '二分图', '费用流']
---

# Ants

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4157

[PDF](https://uva.onlinejudge.org/external/14/p1411.pdf)

给定平面上的 $N$ 个黑点和 $N$ 个白点（共 $2N$ 个点），请找到一种方案，对于每一个黑点，找到一个白点，用线段把黑点和白点连接，保证最后**任意两条线段无公共点（不相交）**。

## 输入格式

**可能有多组数据。**

对于每组输入数据，第一行一个整数 $N$，描述黑点和白点的数量；

接下来 $N$ 行，每行两个整数 $x,y$，描述**黑点**的坐标；

再接下来 $N$ 行，每行两个整数 $x,y$，描述**白点**的坐标；

## 输出格式

对于每组数据，输出 $N$ 行，每行一个整数，第 $i$ 行的整数 $j$ 表示第 $i$ 个黑点与第 $j$ （$1\leq j \leq N$）个白点相连。

**请在每组数据之间输出一个空行。**

若有多解，任意输出一个均可。

## 说明/提示

## 数据范围与提示

$1\leq N\leq 100, |x|, |y|\leq 10^4$。

保证无三点共线。数据保证有解。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -6
```

### 输出

```
4
2
1
5
3
```



---

---
title: "Jungle Outpost"
layout: "post"
diff: 省选/NOI-
pid: UVA1475
tag: ['二分', '半平面交']
---

# Jungle Outpost

## 题目描述

在丛林里有n个瞭望塔，瞭望塔的保护范围就是一个凸n多边形，敌人进攻会炸毁一些瞭望塔，使总部暴露在剩下的瞭望塔围成的凸多边形之外，请你选择一个点作为总部，使得敌人要炸毁的瞭望塔尽量多。

## 输入格式

多组数据，每组第一行一个数字n，接下来n行每行两个整数代表一个瞭望塔的坐标。结束标志为EOF。

## 输出格式

对于每组数据，输出当总部位置最优时，敌人需要炸毁的瞭望塔的数目。


感谢@TimeTraveller 提供的翻译

## 样例 #1

### 输入

```
3
0 0
50 50
60 10
5
0 0
0 10
10 20
20 10
25 0
```

### 输出

```
1
2
```



---

---
title: "团队分组 Team them up!"
layout: "post"
diff: 省选/NOI-
pid: UVA1627
tag: ['背包 DP', '二分图']
---

# 团队分组 Team them up!

## 题目描述

你的任务是按照以下要求将一些人员划分到两个队伍中。

1. 每个人都属于其中的一个队伍。

2. 每个队伍至少包含一个人。

3. 每个人都认识几个人，而同一个队伍中的人必须两两认识。

4. 两个队伍的人数尽可能的接近。

这个任务可能有多组解或无解，你只需要输出其中的任意一种或者宣布无解。

## 输入格式

第一行一个整数 t 表示共有 t 组测试数据

接下来 t 组数据，对于每组数据

第一行一个整数 n 表示一共有 n 个人且每个人的编号分别为1-n。

对于接下来 n 行，输入若干个整数，以输入'0'结束，第 i 行表示编号为 i 的人认识的人。

## 输出格式

对于每组数据以一个空行为间隔。

如果无解则输出'No solution'(不包括引号)。否则输出两行，分别表示两个队伍中的人员编号(编号之间以空格隔开)。你可以以任意的顺序输出方案。



---



---

# 题号列表

- UVA11082 - 矩阵解压 Matrix Decompressing
- UVA11478 - Halum
- UVA1184 - Air Raid
- UVA1364 - Knights of the Round Table
- UVA1411 - Ants
- UVA1475 - Jungle Outpost
- UVA1627 - 团队分组 Team them up!


---

---
title: "修缮长城 Fixing the Great Wall"
layout: "post"
diff: 省选/NOI-
pid: UVA1336
tag: ['动态规划 DP', '区间 DP', '前缀和']
---

# 修缮长城 Fixing the Great Wall

## 题目描述

为了简化这个问题，我们把长城看成是一条直线，每个需要修补的点都被用它离起点的距离（一个整数）标记了。GWARR被放在长城的一个随机位置上，并且可以以恒定的速度双向移动。每个点距离起点的距离，现在立即修复的花费，以及每过单位时间修复花费的增长量都已知。GWARR的工作效率极高，以至于它可以立即修复好经过的需要修复的地方。

## 输入格式

输入包含多组测试数据。每组测试数据的格式如下：
第一行包含$3$个整数$N, V, X$，分别表示点的数量，GWARR的移动速度，GWARR的出发点位置。  
接下来$n$行，每行$3$个整数$x,c,\Delta$，表示这个点的位置，现在立即修复的花费，以及每过单位时间修复花费的增长量。保证没有两个点的位置相同。  
输入以一行$N=V=X=0$作为结束标记。

## 输出格式

$N$行，每行一个整数，表示每组数据的最小总花费（**向下取整**），保证输出结果不超过$10^9$。

## 样例输入输出
### 样例输入\#1：
	3 1 1000
	1010 0 100
	998 0 300
	996 0 3
	3 1 1000
	1010 0 100
	998 0 3
	996 0 3
	0 0 0 
### 样例输出\#1：
	2084
    1138
### 样例输入输出解释：
对于第一种情况，我们选择先修复距离$998$处，花费$600$，然后是$1010$处，花费$1400$，然后是$996$处，花费$84$。合计$2084$。

由 @Sparky_14145 提供翻译

## 说明/提示

对于$100 \%$数据有：
$1 \leq N \leq 1000, 1 \leq V \leq 100,1 \leq X \leq 500,000$；  
$1 \leq x \leq 500,000, 1 \leq c \leq 50,000, 1 \leq \Delta \leq 50,000$。



---

---
title: "Parade"
layout: "post"
diff: 省选/NOI-
pid: UVA1427
tag: ['单调队列', '前缀和', '队列']
---

# Parade

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4173

[PDF](https://uva.onlinejudge.org/external/14/p1427.pdf)



---



---

# 题号列表

- UVA1336 - 修缮长城 Fixing the Great Wall
- UVA1427 - Parade


---

---
title: "编辑书稿 Editing a Book"
layout: "post"
diff: 省选/NOI-
pid: UVA11212
tag: ['搜索', '深度优先搜索 DFS', '剪枝']
---

# 编辑书稿 Editing a Book

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2153

[PDF](https://uva.onlinejudge.org/external/112/p11212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/cb36674ea3b096f313832bf9d1662a62d42ac8f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/22e9d9ac532d783c01ab518c2e636f8cb7ea6eec.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/9f3b00f1af2070ad6d631ffe71eb64da0a7d7b6f.png)

## 样例 #1

### 输入

```
6
2 4 1 5 3 6
5
3 4 5 1 2
0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---



---

# 题号列表

- UVA11212 - 编辑书稿 Editing a Book


---

---
title: "Manhattan Wiring"
layout: "post"
diff: 省选/NOI-
pid: UVA1214
tag: ['动态规划 DP', '图论', '进制']
---

# Manhattan Wiring

## 题目描述

题目大意

n×m网格里有空格和障碍，还有两个2和两个3.要求把这两个2和两个3各用一条折线连起来，使得总长度尽量小（线必须穿过格子中心，每个单位正方形的边长为1）。

限制条件如下：障碍格里不能有线，而每个空格里最多只能有一条线。由此可知，两条折线不能相交，每条折线不能自交。

如图所示，折线总长度为18（2、2、3、3格子中各有一条长度0.5的线）。

## 输入格式

输入包含多组数据。每组数据的第一行为正整数n、m（1≤n，m≤9），以下n行每行为m个整数，描述该网格。0表示空格，1表示障碍，2表示写有“2”的格子，3表示写有“3”的格子。

## 输出格式

对于每组数据输出一行，输出两条折线最小总长度，如果无解，输出0。



---

---
title: "修缮长城 Fixing the Great Wall"
layout: "post"
diff: 省选/NOI-
pid: UVA1336
tag: ['动态规划 DP', '区间 DP', '前缀和']
---

# 修缮长城 Fixing the Great Wall

## 题目描述

为了简化这个问题，我们把长城看成是一条直线，每个需要修补的点都被用它离起点的距离（一个整数）标记了。GWARR被放在长城的一个随机位置上，并且可以以恒定的速度双向移动。每个点距离起点的距离，现在立即修复的花费，以及每过单位时间修复花费的增长量都已知。GWARR的工作效率极高，以至于它可以立即修复好经过的需要修复的地方。

## 输入格式

输入包含多组测试数据。每组测试数据的格式如下：
第一行包含$3$个整数$N, V, X$，分别表示点的数量，GWARR的移动速度，GWARR的出发点位置。  
接下来$n$行，每行$3$个整数$x,c,\Delta$，表示这个点的位置，现在立即修复的花费，以及每过单位时间修复花费的增长量。保证没有两个点的位置相同。  
输入以一行$N=V=X=0$作为结束标记。

## 输出格式

$N$行，每行一个整数，表示每组数据的最小总花费（**向下取整**），保证输出结果不超过$10^9$。

## 样例输入输出
### 样例输入\#1：
	3 1 1000
	1010 0 100
	998 0 300
	996 0 3
	3 1 1000
	1010 0 100
	998 0 3
	996 0 3
	0 0 0 
### 样例输出\#1：
	2084
    1138
### 样例输入输出解释：
对于第一种情况，我们选择先修复距离$998$处，花费$600$，然后是$1010$处，花费$1400$，然后是$996$处，花费$84$。合计$2084$。

由 @Sparky_14145 提供翻译

## 说明/提示

对于$100 \%$数据有：
$1 \leq N \leq 1000, 1 \leq V \leq 100,1 \leq X \leq 500,000$；  
$1 \leq x \leq 500,000, 1 \leq c \leq 50,000, 1 \leq \Delta \leq 50,000$。



---

---
title: "String painter"
layout: "post"
diff: 省选/NOI-
pid: UVA1437
tag: ['动态规划 DP']
---

# String painter

## 题目描述

有两个仅含有小写字母的等长字符串 $A$ 和 $B$，每次操作可以将 $A$ 的其中一个子串的所有位置修改为同一个任意字符。求将 $A$ 覆盖成  $B$ 的最小操作次数。

$1\le |a |=|b|\le100。$

## 输入格式

输入包含多组数据，每组数据由两行组成，第一行为字符串 $A$，第二行为字符串 $B$。

## 输出格式

对于每组数据，输出最小操作次数。

## 样例 #1

### 输入

```
hfcnndeziymohaewnrbmquyhigwm
bcbysbjvxbzvmspshggrzaukbipm
jmmeqimjobpxyavjneyvyuuhhwiqowmme
kmpgpviubhzrjkezqqoilsuwgedctxkxl
ikynfrlcsltkrbdkdqpirtdnajhzhbhipeqtyxvskhkti
qmziwxbbjzjfymrzvflthsbaqgdoqmiduiudviqzztclb
vwysgqniecydcycqk
cqgudqbkgcsvimpdj
mcrrqwfegpnukyuk
vezrniuriscgtcth
rdjtgk
wzfycu
nwxqfdtigwj
rrhcndwcohx
knjmrwlwxfroyppgxhrknntrvbcqjrranufutrginldqydsjsfyjqfyqq
lghrdjsgvbffgfpclqmrzzoniyhlsoisgpbfdqpiblsbtirrbdjdjxsuy
nujagihmgqvwiwvbmbe
pnxicvskosnzneztzhd
bzjvffvyv
mnvjbgwdw
```

### 输出

```
20
26
33
15
13
6
8
43
15
8
```



---

---
title: "独占访问2 Exclusive Access 2"
layout: "post"
diff: 省选/NOI-
pid: UVA1439
tag: ['动态规划 DP']
---

# 独占访问2 Exclusive Access 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4185

[PDF](https://uva.onlinejudge.org/external/14/p1439.pdf)

## 样例 #1

### 输入

```
2
P Q
R S
6
P Q
Q R
R S
S T
T U
U P
4
P Q
P Q
P Q
P Q
3
P Q
Q R
R P
6
P Q
Q S
S R
R P
P S
R Q
```

### 输出

```
0
P Q
R S
0
P Q
R Q
R S
T S
T U
P U
0
P Q
P Q
P Q
P Q
1
P Q
Q R
P R
2
P Q
Q S
R S
P R
P S
R Q
```



---

---
title: "Alice and Bob"
layout: "post"
diff: 省选/NOI-
pid: UVA1500
tag: ['动态规划 DP', '博弈论']
---

# Alice and Bob

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4246

[PDF](https://uva.onlinejudge.org/external/15/p1500.pdf)



---

---
title: "串折叠 Folding"
layout: "post"
diff: 省选/NOI-
pid: UVA1630
tag: ['字符串', '动态规划 DP']
---

# 串折叠 Folding

## 题目描述

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

Translated by @_UKE自动机_

## 输入格式

**输入有多组数据**。

输入若干行，第 $i$ 行有一个仅由大写字母组成的，长度小于等于 $100$ 的字符串。

## 输出格式

对于每组输入，输出折叠后的字符串。

多解时可以输出任意解。

## 样例 #1

### 输入

```
AAAAAAAAAABABABCCD
NEERCYESYESYESNEERCYESYESYES
```

### 输出

```
9(A)3(AB)CCD
2(NEERC3(YES))
```



---



---

# 题号列表

- UVA1214 - Manhattan Wiring
- UVA1336 - 修缮长城 Fixing the Great Wall
- UVA1437 - String painter
- UVA1439 - 独占访问2 Exclusive Access 2
- UVA1500 - Alice and Bob
- UVA1630 - 串折叠 Folding


---

---
title: "Discrete Logging"
layout: "post"
diff: 省选/NOI-
pid: UVA10225
tag: ['数学', '哈希 hashing', '最大公约数 gcd']
---

# Discrete Logging

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1166

[PDF](https://uva.onlinejudge.org/external/102/p10225.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/8f3c646876319e7077dcca889242cfa7bc79674d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/f80b0cc11b35bd1a4af14fefb9512966c93efe2c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/7997482b668d371df1eef9a909e7fd16f82c356a.png)

## 样例 #1

### 输入

```
5 2 1
5 2 2
5 2 3
5 2 4
5 3 1
5 3 2
5 3 3
5 3 4
5 4 1
5 4 2
5 4 3
5 4 4
12345701 2 1111111
1111111121 65537 1111111111
```

### 输出

```
0
1
3
2
0
3
1
2
0
no solution
no solution
1
9584351
462803587
```



---

---
title: "Jewel Magic"
layout: "post"
diff: 省选/NOI-
pid: UVA11996
tag: ['字符串', '哈希 hashing', '概率论']
---

# Jewel Magic

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3147

[PDF](https://uva.onlinejudge.org/external/119/p11996.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/2bab589816720983ab635f9484728b78d4993b0f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/f01f1337a503a06d908bccf8ce9f1b2f678759c7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/07591e46a067540334a0ba60ca15ea251c41da0e.png)

## 样例 #1

### 输入

```
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3
```

### 输出

```
3
6
2
0
3
2
```



---



---

# 题号列表

- UVA10225 - Discrete Logging
- UVA11996 - Jewel Magic


---

---
title: "Halum"
layout: "post"
diff: 省选/NOI-
pid: UVA11478
tag: ['二分', '图论建模', '差分约束']
---

# Halum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2473

[PDF](https://uva.onlinejudge.org/external/114/p11478.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/fe7bd946fb4e049b4a2acc693bd285a050d606f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/d8a053537747d36f9bda3b53b2e300f24860c7fb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/59cf14738847dcbac078a3ffdf4966090114e0f4.png)

## 样例 #1

### 输入

```
2 1
1 2 10
2 1
1 2 -10
3 3
1 2 4
2 3 2
3 1 5
4 5
2 3 4
4 2 5
3 4 2
3 1 0
1 2 -1
```

### 输出

```
Infinite
Infinite
3
1
```



---

---
title: "Manhattan Wiring"
layout: "post"
diff: 省选/NOI-
pid: UVA1214
tag: ['动态规划 DP', '图论', '进制']
---

# Manhattan Wiring

## 题目描述

题目大意

n×m网格里有空格和障碍，还有两个2和两个3.要求把这两个2和两个3各用一条折线连起来，使得总长度尽量小（线必须穿过格子中心，每个单位正方形的边长为1）。

限制条件如下：障碍格里不能有线，而每个空格里最多只能有一条线。由此可知，两条折线不能相交，每条折线不能自交。

如图所示，折线总长度为18（2、2、3、3格子中各有一条长度0.5的线）。

## 输入格式

输入包含多组数据。每组数据的第一行为正整数n、m（1≤n，m≤9），以下n行每行为m个整数，描述该网格。0表示空格，1表示障碍，2表示写有“2”的格子，3表示写有“3”的格子。

## 输出格式

对于每组数据输出一行，输出两条折线最小总长度，如果无解，输出0。



---

---
title: "Ants"
layout: "post"
diff: 省选/NOI-
pid: UVA1411
tag: ['网络流', '图论建模', '二分图', '费用流']
---

# Ants

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4157

[PDF](https://uva.onlinejudge.org/external/14/p1411.pdf)

给定平面上的 $N$ 个黑点和 $N$ 个白点（共 $2N$ 个点），请找到一种方案，对于每一个黑点，找到一个白点，用线段把黑点和白点连接，保证最后**任意两条线段无公共点（不相交）**。

## 输入格式

**可能有多组数据。**

对于每组输入数据，第一行一个整数 $N$，描述黑点和白点的数量；

接下来 $N$ 行，每行两个整数 $x,y$，描述**黑点**的坐标；

再接下来 $N$ 行，每行两个整数 $x,y$，描述**白点**的坐标；

## 输出格式

对于每组数据，输出 $N$ 行，每行一个整数，第 $i$ 行的整数 $j$ 表示第 $i$ 个黑点与第 $j$ （$1\leq j \leq N$）个白点相连。

**请在每组数据之间输出一个空行。**

若有多解，任意输出一个均可。

## 说明/提示

## 数据范围与提示

$1\leq N\leq 100, |x|, |y|\leq 10^4$。

保证无三点共线。数据保证有解。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -6
```

### 输出

```
4
2
1
5
3
```



---

---
title: "UNIX插头 A Plug for UNIX"
layout: "post"
diff: 省选/NOI-
pid: UVA753
tag: ['图论建模']
---

# UNIX插头 A Plug for UNIX

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=694

[PDF](https://uva.onlinejudge.org/external/7/p753.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/bd8d54abcc7626a52e03f403121ef0c4cca175ba.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/85bc1d905b0ad29df832c8d7397d8a7fd9dca5b1.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA753/bde1b0921a746e5875af277006a66198bd24ffbb.png)

## 样例 #1

### 输入

```
1
4
A
B
C
D
5
laptop B
phone C
pager B
clock B
comb X
3
B X
X A
X D
```

### 输出

```
1
```



---



---

# 题号列表

- UVA11478 - Halum
- UVA1214 - Manhattan Wiring
- UVA1411 - Ants
- UVA753 - UNIX插头 A Plug for UNIX


---

---
title: "Always an integer"
layout: "post"
diff: 省选/NOI-
pid: UVA1069
tag: ['字符串']
---

# Always an integer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3510

[PDF](https://uva.onlinejudge.org/external/10/p1069.pdf)



---

---
title: "Jewel Magic"
layout: "post"
diff: 省选/NOI-
pid: UVA11996
tag: ['字符串', '哈希 hashing', '概率论']
---

# Jewel Magic

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3147

[PDF](https://uva.onlinejudge.org/external/119/p11996.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/2bab589816720983ab635f9484728b78d4993b0f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/f01f1337a503a06d908bccf8ce9f1b2f678759c7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/07591e46a067540334a0ba60ca15ea251c41da0e.png)

## 样例 #1

### 输入

```
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3
```

### 输出

```
3
6
2
0
3
2
```



---

---
title: "串折叠 Folding"
layout: "post"
diff: 省选/NOI-
pid: UVA1630
tag: ['字符串', '动态规划 DP']
---

# 串折叠 Folding

## 题目描述

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

Translated by @_UKE自动机_

## 输入格式

**输入有多组数据**。

输入若干行，第 $i$ 行有一个仅由大写字母组成的，长度小于等于 $100$ 的字符串。

## 输出格式

对于每组输入，输出折叠后的字符串。

多解时可以输出任意解。

## 样例 #1

### 输入

```
AAAAAAAAAABABABCCD
NEERCYESYESYESNEERCYESYESYES
```

### 输出

```
9(A)3(AB)CCD
2(NEERC3(YES))
```



---



---

# 题号列表

- UVA1069 - Always an integer
- UVA11996 - Jewel Magic
- UVA1630 - 串折叠 Folding


---

---
title: "Halum"
layout: "post"
diff: 省选/NOI-
pid: UVA11478
tag: ['二分', '图论建模', '差分约束']
---

# Halum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2473

[PDF](https://uva.onlinejudge.org/external/114/p11478.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/fe7bd946fb4e049b4a2acc693bd285a050d606f4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/d8a053537747d36f9bda3b53b2e300f24860c7fb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/59cf14738847dcbac078a3ffdf4966090114e0f4.png)

## 样例 #1

### 输入

```
2 1
1 2 10
2 1
1 2 -10
3 3
1 2 4
2 3 2
3 1 5
4 5
2 3 4
4 2 5
3 4 2
3 1 0
1 2 -1
```

### 输出

```
Infinite
Infinite
3
1
```



---



---

# 题号列表

- UVA11478 - Halum


---

---
title: "买还是建 Buy or Build"
layout: "post"
diff: 省选/NOI-
pid: UVA1151
tag: ['并查集', '状态合并', '生成树']
---

# 买还是建 Buy or Build

## 题目描述

万维网（WWN）是一家运营大型电信网络的领先公司。 WWN希望在Borduria建立一个新的网络，您需要帮助WWN确定如何以最低的总成本设置其网络。有几个本地公司运营着一些小型网络（以下称为子网），部分覆盖了Borduria的n个最大城市。 WWN希望建立一个连接所有n个城市的网络。 要实现这一目标，它可以从头开始在城市之间建设网络，也可以从本地公司购买一个或多个子网。 您需要帮助WWN决定如何以最低的总成本建设其网络。

1、所有n个城市都给出其二维坐标

2、存在q个子网。 如果q≥1,给出每个子网中连接的城市。（不用关心连接的形状）

3、每个子网只能购买，不能被分割

4、连接两个不相通的城市，必须建立一个边，其建设成本是城市之间欧几里德距离的平方。

您的任务是决定购买哪些现有网络以及建设哪些边，使得总成本最低。

## 输入格式

输入文件的第一行是一个整数T，表示测试数据的组数。接下来是一个空白行。每两组测试数据之间也有一个空白行。

对于每组测试数据：

第一行是两个整数，分别是城市的总数n和子网的数量q，1≤n≤1000，0≤q≤8。城市的编号从1到n

接下来q行，每行多个整数，第一个整数表示这个子网中的城市的数量m，第二个整数表示购买这个子网的费用（费用不超过2*10^6），剩下的m个整数表示这个子网包含的城市

接下来n行，每行两个整数，表示第i个城市的坐标（坐标的数字范围是0到3000）

## 输出格式

对于每组测试数据输出一行，输出建设网络的总费用。每组输出之间用一个空行隔开

Translated by @kevensice__

## 样例 #1

### 输入

```
1
7 3
2 4 1 2
3 3 3 6 7
3 9 2 4 5
0 2
4 0
2 0
4 2
1 3
0 5
4 4

```

### 输出

```
17

```



---

---
title: "Gokigen Naname谜题 Gokigen Naname"
layout: "post"
diff: 省选/NOI-
pid: UVA11694
tag: ['搜索', '并查集', '深度优先搜索 DFS']
---

# Gokigen Naname谜题 Gokigen Naname

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2741

[PDF](https://uva.onlinejudge.org/external/116/p11694.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/2821a2ff4c94a298109d6239ae84f49273f2c058.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/9c24649ccdd7cee6a77e317317cbe288310a0ac8.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/c93452858027f71971ba0f8875eec90de1b0dfe0.png)

## 样例 #1

### 输入

```
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11
```

### 输出

```
\//
\\\
/\/
/\\//
//\\\
\\\//
\/\\/
///\\
```



---

---
title: "占领新区域 Conquer a New Region"
layout: "post"
diff: 省选/NOI-
pid: UVA1664
tag: ['并查集', '排序']
---

# 占领新区域 Conquer a New Region

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4539

[PDF](https://uva.onlinejudge.org/external/16/p1664.pdf)

## 样例 #1

### 输入

```
4
1 2 2
2 4 1
2 3 1
4
1 2 1
2 4 1
2 3 1
```

### 输出

```
4
3
```



---

---
title: "岛屿 Islands"
layout: "post"
diff: 省选/NOI-
pid: UVA1665
tag: ['并查集', '枚举', '排序']
---

# 岛屿 Islands

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4540

[PDF](https://uva.onlinejudge.org/external/16/p1665.pdf)



---



---

# 题号列表

- UVA1151 - 买还是建 Buy or Build
- UVA11694 - Gokigen Naname谜题 Gokigen Naname
- UVA1664 - 占领新区域 Conquer a New Region
- UVA1665 - 岛屿 Islands


---

---
title: "Pushing Boxes"
layout: "post"
diff: 省选/NOI-
pid: UVA589
tag: ['广度优先搜索 BFS']
---

# Pushing Boxes

## 题目描述

### 题面翻译

想象你站在一个二维的迷宫里，迷宫由 $R$ 列 $C$ 行共 $R\times C$ 个方格组成，有些方格里是岩石（所以你与箱子不能走到这些格子上），而另外的则是空格子。你可以在一个空格子上向北（上）、南（下）、东（右）、西（左）移动到另外一个相邻的空格子上，这个操作叫做**步行**。

有一个空格子上放着一个箱子，你可以站在盒子旁边，向盒子的方向移动，使得你和箱子共同平移一格（当然平移到的地方不能有岩石）。我们把这样的操作叫做**推**。你只能用推的方式来移动箱子，这意味着，如果你把箱子推到了死角里，你就无法将它推出来了。

现在给定你的起始坐标、箱子的起始坐标和箱子要被推到的坐标，请你找出一个最优的推箱子的操作序列，或报告无解。具体地说：

1. 这个操作序列的**推**操作的次数是最少的。

2. 在满足 (1) 的条件下，若存在不止一个操作序列，则要求操作序列的**总操作次数**（包括**步行**操作和**推**操作）最少。

3. 若在满足 (1) (2) 的条件下，操作序列仍然不唯一，任意输出一个均可。

## 输入格式

**本题存在多组数据。**

对于每组数据，第一行是两个整数 $R,C$，描述迷宫的行数和列数。

接下来 $R$ 行，每行 $C$ 个字符，每个字符描述一个格子：

- `#` 表示有岩石的格子。
- `.` 表示空格子。
- `B` 表示箱子初始位置。**这是一个空格子。**
- `S` 表示你的初始位置。**这是一个空格子。**
- `T` 表示箱子目标位置。**这是一个空格子。**

每个测试点以 $R=C=0$ 结尾，无需处理该组数据。

## 输出格式

对于每组数据，第一行是一个字符串 `Maze #d`，其中 **$\boldsymbol{d}$ 表示这是第几组数据。**

如果无解，在第二行输出 `Impossible`.

否则输出一个符合题目要求的最优的（见上）的操作序列。具体地说：

用大写的 `N`（北）、`S`（南）、`E`（东）、`W`（西）表示**推**操作。

用小写的 `n`（北）、`s`（南）、`e`（东）、`w`（西）表示**步行**操作。

**请在两组测试数据之间输出额外的一行空行。**

## 说明/提示

$R,C \leq 20$。

## 样例 #1

### 输入

```
1 7
SB....T
1 7
SB..#.T
7 11
###########
#T##......#
#.#.#..####
#....B....#
#.######..#
#.....S...#
###########
8 4
....
.##.
.#..
.#..
.#.B
.##S
....
###T
0 0
```

### 输出

```
Maze #1
EEEEE

Maze #2
Impossible.

Maze #3
eennwwWWWWeeeeeesswwwwwwwnNN

Maze #4
swwwnnnnnneeesssSSS
```



---



---

# 题号列表

- UVA589 - Pushing Boxes


---

---
title: "DNA Regions"
layout: "post"
diff: 省选/NOI-
pid: UVA1392
tag: ['单调队列', '枚举', '排序']
---

# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 输入格式

包含多组数据。

对于每组数据，第一行为两个整数 $n$ 和 $q$。
接下来两行分别是 $A$ 和 $B$。

结束的标志是 $n=0$。

## 输出格式

对于每组数据，若有解，输出满足条件的区间长度的最大值，若无解，输出`No solution.`。

## 输入输出样例
### 输入
```
14 25
ACCGGTAACGTGAA
ACTGGATACGTAAA
14 24
ACCGGTAACGTGAA
ACTGGATACGTAAA
8 1
AAAAAAAA
CCCCCCCC
8 33
AAACAAAA
CCCCCCCC
0 0

```
### 输出
```
8
7
No solution.
1
```

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。



---

---
title: "Robotic Sort"
layout: "post"
diff: 省选/NOI-
pid: UVA1402
tag: ['排序', '期望', '栈']
---

# Robotic Sort

## 题目描述

通过一系列移动，将某些物品按顺序摆好。规定只能使用如下方式排序：
先找到编号最小的物品的位置P1，将区间[1,P1]反转，再找到编号第二小的物品的位置P2，将区间[2,P2]反转……

（如图）
上图是有6个物品的例子，编号最小的一个是在第4个位置。因此，最开始把前面4个物品反转，第二小的物品在最后一个位置，所以下一个操作是把2-6的物品反转，第三部操作则是把3-4的物品进行反转……
在数据中可能存在有相同的编号，如果有多个相同的编号，则按输入的原始次序操作。

## 输入格式

多组数据以0结尾，每组输入共两行，第一行为一个整数N，N表示物品的个数，1<=N<=100000
第二行为N个用空格隔开的正整数，表示N个物品最初排列的编号。

## 输出格式

每组数据输出一行，N个用空格隔开的正整数P1,P2,P3…Pn，Pi表示第i次操作前第i小的物品所在的位置。 注意：如果第i次操作前，第i小的物品己经在正确的位置Pi上，我们将区间[Pi,Pi]反转(单个物品)。

感谢@enor2017 提供翻译



---

---
title: "占领新区域 Conquer a New Region"
layout: "post"
diff: 省选/NOI-
pid: UVA1664
tag: ['并查集', '排序']
---

# 占领新区域 Conquer a New Region

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4539

[PDF](https://uva.onlinejudge.org/external/16/p1664.pdf)

## 样例 #1

### 输入

```
4
1 2 2
2 4 1
2 3 1
4
1 2 1
2 4 1
2 3 1
```

### 输出

```
4
3
```



---

---
title: "岛屿 Islands"
layout: "post"
diff: 省选/NOI-
pid: UVA1665
tag: ['并查集', '枚举', '排序']
---

# 岛屿 Islands

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4540

[PDF](https://uva.onlinejudge.org/external/16/p1665.pdf)



---



---

# 题号列表

- UVA1392 - DNA Regions
- UVA1402 - Robotic Sort
- UVA1664 - 占领新区域 Conquer a New Region
- UVA1665 - 岛屿 Islands


---

---
title: "方块消除 Blocks"
layout: "post"
diff: 省选/NOI-
pid: UVA10559
tag: ['搜索', '记忆化搜索', '区间 DP']
---

# 方块消除 Blocks

## 题目描述

有 $n$ 个带有颜色的方块，没消除一段长度为x的连续的相同颜色的方块可以得到 $x^2$ 的分数，让你用一种最优的顺序消除所有方块使得得分最多。

## 输入格式

第一行包含测试的次数 $t(1≤t≤15)$ 。

每个案例包含两行。

第一行包含整数 $n(1≤n≤200)$，即框数。

第二行包含 $n$ 个数，代表每个盒子的颜色。数字的大小 $1\sim n$ 内。

## 输出格式

输出 $\texttt{Case x: }y$，其中 $\texttt{x}$ 表示当前是第几组数据，$y$ 表示答案。

## 样例 #1

### 输入

```
2
9
1 2 2 2 2 3 3 3 1
1
1
```

### 输出

```
Case 1: 29
Case 2: 1
```



---

---
title: "Sharing Chocolate"
layout: "post"
diff: 省选/NOI-
pid: UVA1099
tag: ['搜索', '记忆化搜索', '状态合并']
---

# Sharing Chocolate

## 题目描述

（摘自《算法竞赛入门经典训练指南》，刘汝佳 陈峰 著）

给出一块长为 $x$, 宽为 $y$ 的矩形巧克力，每次操作可以沿一条直线把一块巧克力切割成两块长宽均为整数的巧克力（一次不能同时切割多块巧克力）。 

问：是否可以经过若干次操作得到 $n$ 块面积分别为 $a_1, a_2, ..., a_n$ 的巧克力。

## 输入格式

输入包含若干组数据：

每组数据第一行为一个整数 $n(1 \leq n \leq 15)$;

第二行两个整数 $x,y(1 \leq x, y \leq 100)$;

第三行 $n$ 个整数 $a_1,a_2, ... ,a_n$。

输入结束标志为 $n = 0$。

## 输出格式

对于每组数据，如果切割成功，输出 `Yes`，否则输出 `No`

## 样例 #1

### 输入

```
4
3 4
6 3 2 1
2
2 3
1 5
0
```

### 输出

```
Case 1: Yes
Case 2: No
```



---

---
title: "编辑书稿 Editing a Book"
layout: "post"
diff: 省选/NOI-
pid: UVA11212
tag: ['搜索', '深度优先搜索 DFS', '剪枝']
---

# 编辑书稿 Editing a Book

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2153

[PDF](https://uva.onlinejudge.org/external/112/p11212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/cb36674ea3b096f313832bf9d1662a62d42ac8f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/22e9d9ac532d783c01ab518c2e636f8cb7ea6eec.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/9f3b00f1af2070ad6d631ffe71eb64da0a7d7b6f.png)

## 样例 #1

### 输入

```
6
2 4 1 5 3 6
5
3 4 5 1 2
0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---

---
title: "Gokigen Naname谜题 Gokigen Naname"
layout: "post"
diff: 省选/NOI-
pid: UVA11694
tag: ['搜索', '并查集', '深度优先搜索 DFS']
---

# Gokigen Naname谜题 Gokigen Naname

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2741

[PDF](https://uva.onlinejudge.org/external/116/p11694.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/2821a2ff4c94a298109d6239ae84f49273f2c058.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/9c24649ccdd7cee6a77e317317cbe288310a0ac8.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/c93452858027f71971ba0f8875eec90de1b0dfe0.png)

## 样例 #1

### 输入

```
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11
```

### 输出

```
\//
\\\
/\/
/\\//
//\\\
\\\//
\/\\/
///\\
```



---

---
title: "Race to 1"
layout: "post"
diff: 省选/NOI-
pid: UVA11762
tag: ['搜索', '素数判断,质数,筛法', '期望']
---

# Race to 1

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2862

[PDF](https://uva.onlinejudge.org/external/117/p11762.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/b1ef1b689a23762fedd48e6bac11ed55518ccb60.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/a9e8aa18a999254778b847f800ff15db6efad8e6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/2f64db9ff88189d3cfead67b6fe9a973785d0c8c.png)

## 样例 #1

### 输入

```
3
1
3
13
```

### 输出

```
Case 1: 0.0000000000
Case 2: 2.0000000000
Case 3: 6.0000000000
```



---

---
title: "Pushing Boxes"
layout: "post"
diff: 省选/NOI-
pid: UVA589
tag: ['广度优先搜索 BFS']
---

# Pushing Boxes

## 题目描述

### 题面翻译

想象你站在一个二维的迷宫里，迷宫由 $R$ 列 $C$ 行共 $R\times C$ 个方格组成，有些方格里是岩石（所以你与箱子不能走到这些格子上），而另外的则是空格子。你可以在一个空格子上向北（上）、南（下）、东（右）、西（左）移动到另外一个相邻的空格子上，这个操作叫做**步行**。

有一个空格子上放着一个箱子，你可以站在盒子旁边，向盒子的方向移动，使得你和箱子共同平移一格（当然平移到的地方不能有岩石）。我们把这样的操作叫做**推**。你只能用推的方式来移动箱子，这意味着，如果你把箱子推到了死角里，你就无法将它推出来了。

现在给定你的起始坐标、箱子的起始坐标和箱子要被推到的坐标，请你找出一个最优的推箱子的操作序列，或报告无解。具体地说：

1. 这个操作序列的**推**操作的次数是最少的。

2. 在满足 (1) 的条件下，若存在不止一个操作序列，则要求操作序列的**总操作次数**（包括**步行**操作和**推**操作）最少。

3. 若在满足 (1) (2) 的条件下，操作序列仍然不唯一，任意输出一个均可。

## 输入格式

**本题存在多组数据。**

对于每组数据，第一行是两个整数 $R,C$，描述迷宫的行数和列数。

接下来 $R$ 行，每行 $C$ 个字符，每个字符描述一个格子：

- `#` 表示有岩石的格子。
- `.` 表示空格子。
- `B` 表示箱子初始位置。**这是一个空格子。**
- `S` 表示你的初始位置。**这是一个空格子。**
- `T` 表示箱子目标位置。**这是一个空格子。**

每个测试点以 $R=C=0$ 结尾，无需处理该组数据。

## 输出格式

对于每组数据，第一行是一个字符串 `Maze #d`，其中 **$\boldsymbol{d}$ 表示这是第几组数据。**

如果无解，在第二行输出 `Impossible`.

否则输出一个符合题目要求的最优的（见上）的操作序列。具体地说：

用大写的 `N`（北）、`S`（南）、`E`（东）、`W`（西）表示**推**操作。

用小写的 `n`（北）、`s`（南）、`e`（东）、`w`（西）表示**步行**操作。

**请在两组测试数据之间输出额外的一行空行。**

## 说明/提示

$R,C \leq 20$。

## 样例 #1

### 输入

```
1 7
SB....T
1 7
SB..#.T
7 11
###########
#T##......#
#.#.#..####
#....B....#
#.######..#
#.....S...#
###########
8 4
....
.##.
.#..
.#..
.#.B
.##S
....
###T
0 0
```

### 输出

```
Maze #1
EEEEE

Maze #2
Impossible.

Maze #3
eennwwWWWWeeeeeesswwwwwwwnNN

Maze #4
swwwnnnnnneeesssSSS
```



---



---

# 题号列表

- UVA10559 - 方块消除 Blocks
- UVA1099 - Sharing Chocolate
- UVA11212 - 编辑书稿 Editing a Book
- UVA11694 - Gokigen Naname谜题 Gokigen Naname
- UVA11762 - Race to 1
- UVA589 - Pushing Boxes


---

---
title: "Discrete Logging"
layout: "post"
diff: 省选/NOI-
pid: UVA10225
tag: ['数学', '哈希 hashing', '最大公约数 gcd']
---

# Discrete Logging

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1166

[PDF](https://uva.onlinejudge.org/external/102/p10225.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/8f3c646876319e7077dcca889242cfa7bc79674d.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/f80b0cc11b35bd1a4af14fefb9512966c93efe2c.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10225/7997482b668d371df1eef9a909e7fd16f82c356a.png)

## 样例 #1

### 输入

```
5 2 1
5 2 2
5 2 3
5 2 4
5 3 1
5 3 2
5 3 3
5 3 4
5 4 1
5 4 2
5 4 3
5 4 4
12345701 2 1111111
1111111121 65537 1111111111
```

### 输出

```
0
1
3
2
0
3
1
2
0
no solution
no solution
1
9584351
462803587
```



---

---
title: "That Nice Euler Circuit"
layout: "post"
diff: 省选/NOI-
pid: UVA1342
tag: ['数学', '计算几何', '枚举']
---

# That Nice Euler Circuit

## 题目描述

给出一个平面上$n-1$个点的回路，第$n$个顶点与第$1$个顶点相同，求它把整个平面分成了几个部分（包括内部围起来的部分和外面的无限大的区域）。

## 输入格式

本题包含多组数据$(\leqslant 25)$。

对于每组数据，第一行，一个整数$n$。

第二行，$2n$个整数，为$x_i,y_i$，表示这$n$个点的坐标，数据保证$x_n=x_1,y_n=y_1$.

$n=0$表示数据结束。

## 输出格式

对于每组数据，输出一行，以下列格式输出，其中$x$表示第$x$组数据，$w$是答案。

**Case** $x$**: There are **$w$** pieces.**

## 说明/提示

数据组数$\leqslant 25$

$4\leqslant n\leqslant 300$

$-300\leqslant x_i,y_i\leqslant 300$

感谢@AThousandMoon 提供的翻译



---

---
title: "Bridge"
layout: "post"
diff: 省选/NOI-
pid: UVA1356
tag: ['数学', '微积分', '积分']
---

# Bridge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4102

[PDF](https://uva.onlinejudge.org/external/13/p1356.pdf)



---



---

# 题号列表

- UVA10225 - Discrete Logging
- UVA1342 - That Nice Euler Circuit
- UVA1356 - Bridge


---

---
title: "Dijkstra, Dijkstra."
layout: "post"
diff: 省选/NOI-
pid: UVA10806
tag: ['枚举', '最短路']
---

# Dijkstra, Dijkstra.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1747

[PDF](https://uva.onlinejudge.org/external/108/p10806.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/e738bac0dde02ff0489078ea146317a0237c7c29.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/ee4a786c893868ed23aa2feb76f36addda229200.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/3114ba3008d7c18545f888edf30d40fc11724d13.png)

## 样例 #1

### 输入

```
2
1
1 2 999
3
3
1 3 10
2 1 20
3 2 50
9
12
1 2 10
1 3 10
1 4 10
2 5 10
3 5 10
4 5 10
5 7 10
6 7 10
7 8 10
6 9 10
7 9 10
8 9 10
0
```

### 输出

```
Back to jail
80
Back to jail
```



---

---
title: "Travel in Desert"
layout: "post"
diff: 省选/NOI-
pid: UVA10816
tag: ['枚举', '最短路', '生成树']
---

# Travel in Desert

## 题目描述

### 题目大意
沙漠中有$n$ 个绿洲（编号为$1-n$ ）和$e$ 条连接绿洲的双向道路。每条道路都有一个长度$d$ 和一个温度值$r$ 。给定起点绿洲编号$s$ 和终点绿洲编号$t$ ，求出一条$s$ 到$t$ 的路径，使得这条路径上经过的所有道路的最高温度尽量小，如果有多条路径，选择总长度最短的那一条。

## 输入格式

输入包含多组数据。

每组数据第一行为两个整数$n$ 和$e$ 。表示绿洲数量和连接绿洲的道路数量。

每组数据第二行为两个整数$s$ 和$t$ 。表示起点和终点的绿洲编号。

接下来$e$ 行，每行包含两个整数$x,y$ 以及两个实数$r,d$，表明在绿洲$x$ 和$y$ 之间有一条双向道路相连，长度为$d$ ，温度为$r$ 。

## 输出格式

对于输入的每组数据，应输出两行，第一行表示你找到的路线，第二行包含两个实数，为你找出的路线的总长度与途经的最高温度。

## 样例 #1

### 输入

```
6 9
1 6
1 2 37.1 10.2
2 3 40.5 20.7
3 4 42.8 19.0
3 1 38.3 15.8
4 5 39.7 11.1
6 3 36.0 22.5
5 6 43.9 10.2
2 6 44.2 15.2
4 6 34.2 17.4
```

### 输出

```
1 3 6
38.3 38.3
```



---

---
title: "Warfare And Logistics"
layout: "post"
diff: 省选/NOI-
pid: UVA1416
tag: ['枚举', '最短路', '概率论']
---

# Warfare And Logistics

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4162

[PDF](https://uva.onlinejudge.org/external/14/p1416.pdf)



---



---

# 题号列表

- UVA10806 - Dijkstra, Dijkstra.
- UVA10816 - Travel in Desert
- UVA1416 - Warfare And Logistics


---

---
title: "WonderTeam"
layout: "post"
diff: 省选/NOI-
pid: UVA1418
tag: ['构造']
---

# WonderTeam

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4164

[PDF](https://uva.onlinejudge.org/external/14/p1418.pdf)



---

---
title: "Picnic Planning"
layout: "post"
diff: 省选/NOI-
pid: UVA1537
tag: ['枚举', '生成树', '构造']
---

# Picnic Planning

## 题目描述

[PDF](https://onlinejudge.org/external/15/p1537.pdf)
# 题目背景
The Contortion Brothers是一组著名的马戏团小丑，以其令人难以置信的能力而闻名于世即使是最小的车辆，也能容纳无限的数量。在淡季期间，兄弟俩喜欢在当地公园聚在一起参加年度拳师大会。然而,兄弟俩不仅在狭小的空间里很紧张，而且在金钱上也很紧张，所以他们试图找到让每个人都参加聚会的方法，尽量**减少**每个人的汽车行驶里程（从而节省气体、磨损等）。为此，他们愿意在必要时把自己塞进少数几个车，尽量减少所有汽车的总里程。这经常导致许多兄弟开车去一个兄弟家，除了一辆车外，其他车都停在那里，然后挤进剩下的一个。然而，公园有一个限制：野餐地点的停车场可以只能容纳**有限数量**的汽车，因此必须将其纳入整体最小的计算中。同时，由于公园的入场费，一旦任何兄弟的车到达公园，它就会停在那里;他不会让乘客下车，然后去接其他兄弟。现在，对于你的普通马戏团来说，解决这个问题是一个挑战，所以留给你写一个程序来解决他们的最小化问题。

## 输入格式

第一行输入一个正整数 $ t $，**表示测试数据组数**

对于每一组测试样例:

**第一行**将包含一个整数 $ n ( n \leqslant 20) $，表示兄弟之间或兄弟与公园之间的公路连接数量。
空两行后接下来 $ n $ 行每行格式为“  $ name_1-name_2-dist $ ”  ，其中  $ name_1 $  和  $ name_2 $  要么是两个兄弟的名字。要么是“$ Park $ ”这个词和一个兄弟的姓名（**按任何顺序**），以及
$ dist $是它们之间的整数距离。这些道路都将是双向的。 

最后一行包含一个整数 $ s $ ，用于指定可以放在野餐地点停车场的汽车。你可以假设兄弟的房子都有一条路到公园，即每个问题都有解决方案。

**形式化地**:

给定一张 $ n $ 个点 $ n $ 条边的无向图，求出无向图的一棵最小生成树，满足一号节点的度数不超过给定的整数 $ s $.

## 输出格式

对于每个测试用例，输出必须遵循以下描述。连续两个案例的输出**将用空行分隔**。
对于每个测试用例，输出应该由以下组成:
```
Total miles driven: xxx
```
其中 `xxx` 是兄弟俩所有汽车的总行驶里程。
# 输入输出样例

### 输入 #1
```
2


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
3


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
1
```
### 输出 #1
```
Total miles driven: 183

Total miles driven: 255

```



---



---

# 题号列表

- UVA1418 - WonderTeam
- UVA1537 - Picnic Planning


---

---
title: "Dumb Bones"
layout: "post"
diff: 省选/NOI-
pid: UVA10529
tag: ['递推', '枚举', '期望']
---

# Dumb Bones

## 题目描述

你正在尝试用多米诺骨牌搭成一条直线，以便最后试验时推倒它们

（确实，搭建某些东西仅仅为了推倒看上去没啥意义，但你有一些奇怪的爱好）

然而你在搭建过程中可能会弄倒骨牌，这将波及到邻近的部分

现在需要你来求将骨牌搭建完成所需的期望步数

## 输入格式

若干组数据，以0结尾

一个整数n$(1 \leq n \leq 1000)$ 表示你需要搭的骨牌数量

两个整数$P_l,P_r$ 分别表示搭建某个骨牌时向左，向右倾倒的概率

## 输出格式

对于每组数据，输出一个实数，保留两位小数，为搭建完成的期望步数

翻译提供者：Captain_Paul

## 样例 #1

### 输入

```
10 0.25 0.25
10 0.1 0.4
10 0.0 0.5
0
```

### 输出

```
46.25
37.28
20.00
```



---

---
title: "Dijkstra, Dijkstra."
layout: "post"
diff: 省选/NOI-
pid: UVA10806
tag: ['枚举', '最短路']
---

# Dijkstra, Dijkstra.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1747

[PDF](https://uva.onlinejudge.org/external/108/p10806.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/e738bac0dde02ff0489078ea146317a0237c7c29.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/ee4a786c893868ed23aa2feb76f36addda229200.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10806/3114ba3008d7c18545f888edf30d40fc11724d13.png)

## 样例 #1

### 输入

```
2
1
1 2 999
3
3
1 3 10
2 1 20
3 2 50
9
12
1 2 10
1 3 10
1 4 10
2 5 10
3 5 10
4 5 10
5 7 10
6 7 10
7 8 10
6 9 10
7 9 10
8 9 10
0
```

### 输出

```
Back to jail
80
Back to jail
```



---

---
title: "Travel in Desert"
layout: "post"
diff: 省选/NOI-
pid: UVA10816
tag: ['枚举', '最短路', '生成树']
---

# Travel in Desert

## 题目描述

### 题目大意
沙漠中有$n$ 个绿洲（编号为$1-n$ ）和$e$ 条连接绿洲的双向道路。每条道路都有一个长度$d$ 和一个温度值$r$ 。给定起点绿洲编号$s$ 和终点绿洲编号$t$ ，求出一条$s$ 到$t$ 的路径，使得这条路径上经过的所有道路的最高温度尽量小，如果有多条路径，选择总长度最短的那一条。

## 输入格式

输入包含多组数据。

每组数据第一行为两个整数$n$ 和$e$ 。表示绿洲数量和连接绿洲的道路数量。

每组数据第二行为两个整数$s$ 和$t$ 。表示起点和终点的绿洲编号。

接下来$e$ 行，每行包含两个整数$x,y$ 以及两个实数$r,d$，表明在绿洲$x$ 和$y$ 之间有一条双向道路相连，长度为$d$ ，温度为$r$ 。

## 输出格式

对于输入的每组数据，应输出两行，第一行表示你找到的路线，第二行包含两个实数，为你找出的路线的总长度与途经的最高温度。

## 样例 #1

### 输入

```
6 9
1 6
1 2 37.1 10.2
2 3 40.5 20.7
3 4 42.8 19.0
3 1 38.3 15.8
4 5 39.7 11.1
6 3 36.0 22.5
5 6 43.9 10.2
2 6 44.2 15.2
4 6 34.2 17.4
```

### 输出

```
1 3 6
38.3 38.3
```



---

---
title: "Now or later"
layout: "post"
diff: 省选/NOI-
pid: UVA1146
tag: ['枚举', '2-SAT', '后缀数组 SA']
---

# Now or later

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3587

[PDF](https://uva.onlinejudge.org/external/11/p1146.pdf)



---

---
title: "The Super Powers"
layout: "post"
diff: 省选/NOI-
pid: UVA11752
tag: ['高精度', '枚举']
---

# The Super Powers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2852

[PDF](https://uva.onlinejudge.org/external/117/p11752.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/caccb369bd9149203faf09eaf595e5873b362929.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/3962a6191c1c4336a2bb19bfd7086e2d311306c0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/ee20a6418dc90b6edefd09d6018cfe0bb329ffe4.png)

## 样例 #1

### 输入

```

```

### 输出

```
1
16
64
81
256
512
.
.
.
```



---

---
title: "That Nice Euler Circuit"
layout: "post"
diff: 省选/NOI-
pid: UVA1342
tag: ['数学', '计算几何', '枚举']
---

# That Nice Euler Circuit

## 题目描述

给出一个平面上$n-1$个点的回路，第$n$个顶点与第$1$个顶点相同，求它把整个平面分成了几个部分（包括内部围起来的部分和外面的无限大的区域）。

## 输入格式

本题包含多组数据$(\leqslant 25)$。

对于每组数据，第一行，一个整数$n$。

第二行，$2n$个整数，为$x_i,y_i$，表示这$n$个点的坐标，数据保证$x_n=x_1,y_n=y_1$.

$n=0$表示数据结束。

## 输出格式

对于每组数据，输出一行，以下列格式输出，其中$x$表示第$x$组数据，$w$是答案。

**Case** $x$**: There are **$w$** pieces.**

## 说明/提示

数据组数$\leqslant 25$

$4\leqslant n\leqslant 300$

$-300\leqslant x_i,y_i\leqslant 300$

感谢@AThousandMoon 提供的翻译



---

---
title: "DNA Regions"
layout: "post"
diff: 省选/NOI-
pid: UVA1392
tag: ['单调队列', '枚举', '排序']
---

# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 输入格式

包含多组数据。

对于每组数据，第一行为两个整数 $n$ 和 $q$。
接下来两行分别是 $A$ 和 $B$。

结束的标志是 $n=0$。

## 输出格式

对于每组数据，若有解，输出满足条件的区间长度的最大值，若无解，输出`No solution.`。

## 输入输出样例
### 输入
```
14 25
ACCGGTAACGTGAA
ACTGGATACGTAAA
14 24
ACCGGTAACGTGAA
ACTGGATACGTAAA
8 1
AAAAAAAA
CCCCCCCC
8 33
AAACAAAA
CCCCCCCC
0 0

```
### 输出
```
8
7
No solution.
1
```

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。



---

---
title: "Warfare And Logistics"
layout: "post"
diff: 省选/NOI-
pid: UVA1416
tag: ['枚举', '最短路', '概率论']
---

# Warfare And Logistics

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4162

[PDF](https://uva.onlinejudge.org/external/14/p1416.pdf)



---

---
title: "Picnic Planning"
layout: "post"
diff: 省选/NOI-
pid: UVA1537
tag: ['枚举', '生成树', '构造']
---

# Picnic Planning

## 题目描述

[PDF](https://onlinejudge.org/external/15/p1537.pdf)
# 题目背景
The Contortion Brothers是一组著名的马戏团小丑，以其令人难以置信的能力而闻名于世即使是最小的车辆，也能容纳无限的数量。在淡季期间，兄弟俩喜欢在当地公园聚在一起参加年度拳师大会。然而,兄弟俩不仅在狭小的空间里很紧张，而且在金钱上也很紧张，所以他们试图找到让每个人都参加聚会的方法，尽量**减少**每个人的汽车行驶里程（从而节省气体、磨损等）。为此，他们愿意在必要时把自己塞进少数几个车，尽量减少所有汽车的总里程。这经常导致许多兄弟开车去一个兄弟家，除了一辆车外，其他车都停在那里，然后挤进剩下的一个。然而，公园有一个限制：野餐地点的停车场可以只能容纳**有限数量**的汽车，因此必须将其纳入整体最小的计算中。同时，由于公园的入场费，一旦任何兄弟的车到达公园，它就会停在那里;他不会让乘客下车，然后去接其他兄弟。现在，对于你的普通马戏团来说，解决这个问题是一个挑战，所以留给你写一个程序来解决他们的最小化问题。

## 输入格式

第一行输入一个正整数 $ t $，**表示测试数据组数**

对于每一组测试样例:

**第一行**将包含一个整数 $ n ( n \leqslant 20) $，表示兄弟之间或兄弟与公园之间的公路连接数量。
空两行后接下来 $ n $ 行每行格式为“  $ name_1-name_2-dist $ ”  ，其中  $ name_1 $  和  $ name_2 $  要么是两个兄弟的名字。要么是“$ Park $ ”这个词和一个兄弟的姓名（**按任何顺序**），以及
$ dist $是它们之间的整数距离。这些道路都将是双向的。 

最后一行包含一个整数 $ s $ ，用于指定可以放在野餐地点停车场的汽车。你可以假设兄弟的房子都有一条路到公园，即每个问题都有解决方案。

**形式化地**:

给定一张 $ n $ 个点 $ n $ 条边的无向图，求出无向图的一棵最小生成树，满足一号节点的度数不超过给定的整数 $ s $.

## 输出格式

对于每个测试用例，输出必须遵循以下描述。连续两个案例的输出**将用空行分隔**。
对于每个测试用例，输出应该由以下组成:
```
Total miles driven: xxx
```
其中 `xxx` 是兄弟俩所有汽车的总行驶里程。
# 输入输出样例

### 输入 #1
```
2


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
3


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
1
```
### 输出 #1
```
Total miles driven: 183

Total miles driven: 255

```



---

---
title: "岛屿 Islands"
layout: "post"
diff: 省选/NOI-
pid: UVA1665
tag: ['并查集', '枚举', '排序']
---

# 岛屿 Islands

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4540

[PDF](https://uva.onlinejudge.org/external/16/p1665.pdf)



---

---
title: "Jury Compromise"
layout: "post"
diff: 省选/NOI-
pid: UVA323
tag: ['枚举', '背包 DP', '状态合并']
---

# Jury Compromise

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=259

[PDF](https://uva.onlinejudge.org/external/3/p323.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/c7b6c683e8d99d641e6ceda5403d2046b1543157.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/549f8f7966cff47368b778a0f8cc36bf7e06dada.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/3a147f526328df86970adad2cdf916382d1282db.png)

## 样例 #1

### 输入

```
4 2
1 2
2 3
4 1
6 2
0 0

```

### 输出

```
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3

```



---



---

# 题号列表

- UVA10529 - Dumb Bones
- UVA10806 - Dijkstra, Dijkstra.
- UVA10816 - Travel in Desert
- UVA1146 - Now or later
- UVA11752 - The Super Powers
- UVA1342 - That Nice Euler Circuit
- UVA1392 - DNA Regions
- UVA1416 - Warfare And Logistics
- UVA1537 - Picnic Planning
- UVA1665 - 岛屿 Islands
- UVA323 - Jury Compromise


---

---
title: "Robotic Sort"
layout: "post"
diff: 省选/NOI-
pid: UVA1402
tag: ['排序', '期望', '栈']
---

# Robotic Sort

## 题目描述

通过一系列移动，将某些物品按顺序摆好。规定只能使用如下方式排序：
先找到编号最小的物品的位置P1，将区间[1,P1]反转，再找到编号第二小的物品的位置P2，将区间[2,P2]反转……

（如图）
上图是有6个物品的例子，编号最小的一个是在第4个位置。因此，最开始把前面4个物品反转，第二小的物品在最后一个位置，所以下一个操作是把2-6的物品反转，第三部操作则是把3-4的物品进行反转……
在数据中可能存在有相同的编号，如果有多个相同的编号，则按输入的原始次序操作。

## 输入格式

多组数据以0结尾，每组输入共两行，第一行为一个整数N，N表示物品的个数，1<=N<=100000
第二行为N个用空格隔开的正整数，表示N个物品最初排列的编号。

## 输出格式

每组数据输出一行，N个用空格隔开的正整数P1,P2,P3…Pn，Pi表示第i次操作前第i小的物品所在的位置。 注意：如果第i次操作前，第i小的物品己经在正确的位置Pi上，我们将区间[Pi,Pi]反转(单个物品)。

感谢@enor2017 提供翻译



---



---

# 题号列表

- UVA1402 - Robotic Sort


---

---
title: "Mining Your Own Business"
layout: "post"
diff: 省选/NOI-
pid: UVA1108
tag: ['离散化', '双连通分量', '概率论']
---

# Mining Your Own Business

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3549

[PDF](https://uva.onlinejudge.org/external/11/p1108.pdf)



---

---
title: "Jewel Magic"
layout: "post"
diff: 省选/NOI-
pid: UVA11996
tag: ['字符串', '哈希 hashing', '概率论']
---

# Jewel Magic

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3147

[PDF](https://uva.onlinejudge.org/external/119/p11996.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/2bab589816720983ab635f9484728b78d4993b0f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/f01f1337a503a06d908bccf8ce9f1b2f678759c7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/07591e46a067540334a0ba60ca15ea251c41da0e.png)

## 样例 #1

### 输入

```
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3
```

### 输出

```
3
6
2
0
3
2
```



---

---
title: "Warfare And Logistics"
layout: "post"
diff: 省选/NOI-
pid: UVA1416
tag: ['枚举', '最短路', '概率论']
---

# Warfare And Logistics

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4162

[PDF](https://uva.onlinejudge.org/external/14/p1416.pdf)



---



---

# 题号列表

- UVA1108 - Mining Your Own Business
- UVA11996 - Jewel Magic
- UVA1416 - Warfare And Logistics


---

---
title: "编辑书稿 Editing a Book"
layout: "post"
diff: 省选/NOI-
pid: UVA11212
tag: ['搜索', '深度优先搜索 DFS', '剪枝']
---

# 编辑书稿 Editing a Book

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2153

[PDF](https://uva.onlinejudge.org/external/112/p11212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/cb36674ea3b096f313832bf9d1662a62d42ac8f2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/22e9d9ac532d783c01ab518c2e636f8cb7ea6eec.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11212/9f3b00f1af2070ad6d631ffe71eb64da0a7d7b6f.png)

## 样例 #1

### 输入

```
6
2 4 1 5 3 6
5
3 4 5 1 2
0
```

### 输出

```
Case 1: 2
Case 2: 1
```



---

---
title: "Gokigen Naname谜题 Gokigen Naname"
layout: "post"
diff: 省选/NOI-
pid: UVA11694
tag: ['搜索', '并查集', '深度优先搜索 DFS']
---

# Gokigen Naname谜题 Gokigen Naname

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=78&page=show_problem&problem=2741

[PDF](https://uva.onlinejudge.org/external/116/p11694.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/2821a2ff4c94a298109d6239ae84f49273f2c058.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/9c24649ccdd7cee6a77e317317cbe288310a0ac8.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11694/c93452858027f71971ba0f8875eec90de1b0dfe0.png)

## 样例 #1

### 输入

```
3
1.1.
...0
.3..
..2.
5
.21...
..33.0
......
..33..
0..33.
....11
```

### 输出

```
\//
\\\
/\/
/\\//
//\\\
\\\//
\/\\/
///\\
```



---



---

# 题号列表

- UVA11212 - 编辑书稿 Editing a Book
- UVA11694 - Gokigen Naname谜题 Gokigen Naname


---

---
title: "Travel in Desert"
layout: "post"
diff: 省选/NOI-
pid: UVA10816
tag: ['枚举', '最短路', '生成树']
---

# Travel in Desert

## 题目描述

### 题目大意
沙漠中有$n$ 个绿洲（编号为$1-n$ ）和$e$ 条连接绿洲的双向道路。每条道路都有一个长度$d$ 和一个温度值$r$ 。给定起点绿洲编号$s$ 和终点绿洲编号$t$ ，求出一条$s$ 到$t$ 的路径，使得这条路径上经过的所有道路的最高温度尽量小，如果有多条路径，选择总长度最短的那一条。

## 输入格式

输入包含多组数据。

每组数据第一行为两个整数$n$ 和$e$ 。表示绿洲数量和连接绿洲的道路数量。

每组数据第二行为两个整数$s$ 和$t$ 。表示起点和终点的绿洲编号。

接下来$e$ 行，每行包含两个整数$x,y$ 以及两个实数$r,d$，表明在绿洲$x$ 和$y$ 之间有一条双向道路相连，长度为$d$ ，温度为$r$ 。

## 输出格式

对于输入的每组数据，应输出两行，第一行表示你找到的路线，第二行包含两个实数，为你找出的路线的总长度与途经的最高温度。

## 样例 #1

### 输入

```
6 9
1 6
1 2 37.1 10.2
2 3 40.5 20.7
3 4 42.8 19.0
3 1 38.3 15.8
4 5 39.7 11.1
6 3 36.0 22.5
5 6 43.9 10.2
2 6 44.2 15.2
4 6 34.2 17.4
```

### 输出

```
1 3 6
38.3 38.3
```



---

---
title: "买还是建 Buy or Build"
layout: "post"
diff: 省选/NOI-
pid: UVA1151
tag: ['并查集', '状态合并', '生成树']
---

# 买还是建 Buy or Build

## 题目描述

万维网（WWN）是一家运营大型电信网络的领先公司。 WWN希望在Borduria建立一个新的网络，您需要帮助WWN确定如何以最低的总成本设置其网络。有几个本地公司运营着一些小型网络（以下称为子网），部分覆盖了Borduria的n个最大城市。 WWN希望建立一个连接所有n个城市的网络。 要实现这一目标，它可以从头开始在城市之间建设网络，也可以从本地公司购买一个或多个子网。 您需要帮助WWN决定如何以最低的总成本建设其网络。

1、所有n个城市都给出其二维坐标

2、存在q个子网。 如果q≥1,给出每个子网中连接的城市。（不用关心连接的形状）

3、每个子网只能购买，不能被分割

4、连接两个不相通的城市，必须建立一个边，其建设成本是城市之间欧几里德距离的平方。

您的任务是决定购买哪些现有网络以及建设哪些边，使得总成本最低。

## 输入格式

输入文件的第一行是一个整数T，表示测试数据的组数。接下来是一个空白行。每两组测试数据之间也有一个空白行。

对于每组测试数据：

第一行是两个整数，分别是城市的总数n和子网的数量q，1≤n≤1000，0≤q≤8。城市的编号从1到n

接下来q行，每行多个整数，第一个整数表示这个子网中的城市的数量m，第二个整数表示购买这个子网的费用（费用不超过2*10^6），剩下的m个整数表示这个子网包含的城市

接下来n行，每行两个整数，表示第i个城市的坐标（坐标的数字范围是0到3000）

## 输出格式

对于每组测试数据输出一行，输出建设网络的总费用。每组输出之间用一个空行隔开

Translated by @kevensice__

## 样例 #1

### 输入

```
1
7 3
2 4 1 2
3 3 3 6 7
3 9 2 4 5
0 2
4 0
2 0
4 2
1 3
0 5
4 4

```

### 输出

```
17

```



---

---
title: "Picnic Planning"
layout: "post"
diff: 省选/NOI-
pid: UVA1537
tag: ['枚举', '生成树', '构造']
---

# Picnic Planning

## 题目描述

[PDF](https://onlinejudge.org/external/15/p1537.pdf)
# 题目背景
The Contortion Brothers是一组著名的马戏团小丑，以其令人难以置信的能力而闻名于世即使是最小的车辆，也能容纳无限的数量。在淡季期间，兄弟俩喜欢在当地公园聚在一起参加年度拳师大会。然而,兄弟俩不仅在狭小的空间里很紧张，而且在金钱上也很紧张，所以他们试图找到让每个人都参加聚会的方法，尽量**减少**每个人的汽车行驶里程（从而节省气体、磨损等）。为此，他们愿意在必要时把自己塞进少数几个车，尽量减少所有汽车的总里程。这经常导致许多兄弟开车去一个兄弟家，除了一辆车外，其他车都停在那里，然后挤进剩下的一个。然而，公园有一个限制：野餐地点的停车场可以只能容纳**有限数量**的汽车，因此必须将其纳入整体最小的计算中。同时，由于公园的入场费，一旦任何兄弟的车到达公园，它就会停在那里;他不会让乘客下车，然后去接其他兄弟。现在，对于你的普通马戏团来说，解决这个问题是一个挑战，所以留给你写一个程序来解决他们的最小化问题。

## 输入格式

第一行输入一个正整数 $ t $，**表示测试数据组数**

对于每一组测试样例:

**第一行**将包含一个整数 $ n ( n \leqslant 20) $，表示兄弟之间或兄弟与公园之间的公路连接数量。
空两行后接下来 $ n $ 行每行格式为“  $ name_1-name_2-dist $ ”  ，其中  $ name_1 $  和  $ name_2 $  要么是两个兄弟的名字。要么是“$ Park $ ”这个词和一个兄弟的姓名（**按任何顺序**），以及
$ dist $是它们之间的整数距离。这些道路都将是双向的。 

最后一行包含一个整数 $ s $ ，用于指定可以放在野餐地点停车场的汽车。你可以假设兄弟的房子都有一条路到公园，即每个问题都有解决方案。

**形式化地**:

给定一张 $ n $ 个点 $ n $ 条边的无向图，求出无向图的一棵最小生成树，满足一号节点的度数不超过给定的整数 $ s $.

## 输出格式

对于每个测试用例，输出必须遵循以下描述。连续两个案例的输出**将用空行分隔**。
对于每个测试用例，输出应该由以下组成:
```
Total miles driven: xxx
```
其中 `xxx` 是兄弟俩所有汽车的总行驶里程。
# 输入输出样例

### 输入 #1
```
2


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
3


10
Alphonzo Bernardo 32
Alphonzo Park 57
Alphonzo Eduardo 43
Bernardo Park 19
Bernardo Clemenzi 82
Clemenzi Park 65
Clemenzi Herb 90
Clemenzi Eduardo 109
Park Herb 24
Herb Eduardo 79
1
```
### 输出 #1
```
Total miles driven: 183

Total miles driven: 255

```



---



---

# 题号列表

- UVA10816 - Travel in Desert
- UVA1151 - 买还是建 Buy or Build
- UVA1537 - Picnic Planning


---

---
title: "Mining Your Own Business"
layout: "post"
diff: 省选/NOI-
pid: UVA1108
tag: ['离散化', '双连通分量', '概率论']
---

# Mining Your Own Business

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3549

[PDF](https://uva.onlinejudge.org/external/11/p1108.pdf)



---



---

# 题号列表

- UVA1108 - Mining Your Own Business


---

---
title: "Race to 1"
layout: "post"
diff: 省选/NOI-
pid: UVA11762
tag: ['搜索', '素数判断,质数,筛法', '期望']
---

# Race to 1

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2862

[PDF](https://uva.onlinejudge.org/external/117/p11762.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/b1ef1b689a23762fedd48e6bac11ed55518ccb60.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/a9e8aa18a999254778b847f800ff15db6efad8e6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/2f64db9ff88189d3cfead67b6fe9a973785d0c8c.png)

## 样例 #1

### 输入

```
3
1
3
13
```

### 输出

```
Case 1: 0.0000000000
Case 2: 2.0000000000
Case 3: 6.0000000000
```



---



---

# 题号列表

- UVA11762 - Race to 1


---

---
title: "Race to 1"
layout: "post"
diff: 省选/NOI-
pid: UVA11762
tag: ['搜索', '素数判断,质数,筛法', '期望']
---

# Race to 1

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2862

[PDF](https://uva.onlinejudge.org/external/117/p11762.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/b1ef1b689a23762fedd48e6bac11ed55518ccb60.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/a9e8aa18a999254778b847f800ff15db6efad8e6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/2f64db9ff88189d3cfead67b6fe9a973785d0c8c.png)

## 样例 #1

### 输入

```
3
1
3
13
```

### 输出

```
Case 1: 0.0000000000
Case 2: 2.0000000000
Case 3: 6.0000000000
```



---



---

# 题号列表

- UVA11762 - Race to 1


---

---
title: "Census"
layout: "post"
diff: 省选/NOI-
pid: UVA11297
tag: ['线段树', '未知标签231']
---

# Census

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2272

[PDF](https://uva.onlinejudge.org/external/112/p11297.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/dcd5caafdceb17224df6ccc10085a992416eab82.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/cee81df1c08070576dd90be67eb8b5af4a2692c0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11297/70670c305ce57048872cff5dbe6fe7d179bc2897.png)

## 样例 #1

### 输入

```
5
1 2 3 4 5
0 9 2 1 3
0 2 3 4 1
0 1 2 4 5
8 5 3 1 4
4
q 1 1 2 3
c 2 3 10
q 1 1 5 5
q 1 2 2 2
```

### 输出

```
9 0
10 0
9 2
```



---

---
title: "Robotruck"
layout: "post"
diff: 省选/NOI-
pid: UVA1169
tag: ['线段树', '单调队列', '队列']
---

# Robotruck

## 题目描述

有n个垃圾，第i个垃圾的坐标为(xi,yi)，重量为wi。有一个机器人，要按照编号从小到大的顺序捡起所有垃圾并扔进垃圾桶（垃圾桶在原点(0,0)）。机器人可以捡起几个垃圾以后一起扔掉，但任何时候其手中的垃圾总重量不能超过最大载重C。两点间的行走距离为曼哈顿距离（即横坐标之差的绝对值加上纵坐标之差的绝对值）。求出机器人行走的最短总路程（一开始，机器人在(0,0)处）。

## 输入格式

输入的第一行为数据组数。每组数据的第一行为最大承重C(1<=C<=100)；第二行为正整数n(1<=n<=100000)，即垃圾的数量；以下n行每行为两个非负整数x,y和一个正整数w，即坐标和重量（重量保证不超过C）。

## 输出格式

对于每组数据，输出总路径的最短长度。

输出每行一个解



---



---

# 题号列表

- UVA11297 - Census
- UVA1169 - Robotruck


---

---
title: "团队分组 Team them up!"
layout: "post"
diff: 省选/NOI-
pid: UVA1627
tag: ['背包 DP', '二分图']
---

# 团队分组 Team them up!

## 题目描述

你的任务是按照以下要求将一些人员划分到两个队伍中。

1. 每个人都属于其中的一个队伍。

2. 每个队伍至少包含一个人。

3. 每个人都认识几个人，而同一个队伍中的人必须两两认识。

4. 两个队伍的人数尽可能的接近。

这个任务可能有多组解或无解，你只需要输出其中的任意一种或者宣布无解。

## 输入格式

第一行一个整数 t 表示共有 t 组测试数据

接下来 t 组数据，对于每组数据

第一行一个整数 n 表示一共有 n 个人且每个人的编号分别为1-n。

对于接下来 n 行，输入若干个整数，以输入'0'结束，第 i 行表示编号为 i 的人认识的人。

## 输出格式

对于每组数据以一个空行为间隔。

如果无解则输出'No solution'(不包括引号)。否则输出两行，分别表示两个队伍中的人员编号(编号之间以空格隔开)。你可以以任意的顺序输出方案。



---

---
title: "Jury Compromise"
layout: "post"
diff: 省选/NOI-
pid: UVA323
tag: ['枚举', '背包 DP', '状态合并']
---

# Jury Compromise

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=259

[PDF](https://uva.onlinejudge.org/external/3/p323.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/c7b6c683e8d99d641e6ceda5403d2046b1543157.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/549f8f7966cff47368b778a0f8cc36bf7e06dada.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA323/3a147f526328df86970adad2cdf916382d1282db.png)

## 样例 #1

### 输入

```
4 2
1 2
2 3
4 1
6 2
0 0

```

### 输出

```
Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3

```



---



---

# 题号列表

- UVA1627 - 团队分组 Team them up!
- UVA323 - Jury Compromise


---

---
title: "Race to 1"
layout: "post"
diff: 省选/NOI-
pid: UVA11762
tag: ['搜索', '素数判断,质数,筛法', '期望']
---

# Race to 1

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2862

[PDF](https://uva.onlinejudge.org/external/117/p11762.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/b1ef1b689a23762fedd48e6bac11ed55518ccb60.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/a9e8aa18a999254778b847f800ff15db6efad8e6.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11762/2f64db9ff88189d3cfead67b6fe9a973785d0c8c.png)

## 样例 #1

### 输入

```
3
1
3
13
```

### 输出

```
Case 1: 0.0000000000
Case 2: 2.0000000000
Case 3: 6.0000000000
```



---



---

# 题号列表

- UVA11762 - Race to 1


---

---
title: "Manhattan Wiring"
layout: "post"
diff: 省选/NOI-
pid: UVA1214
tag: ['动态规划 DP', '图论', '进制']
---

# Manhattan Wiring

## 题目描述

题目大意

n×m网格里有空格和障碍，还有两个2和两个3.要求把这两个2和两个3各用一条折线连起来，使得总长度尽量小（线必须穿过格子中心，每个单位正方形的边长为1）。

限制条件如下：障碍格里不能有线，而每个空格里最多只能有一条线。由此可知，两条折线不能相交，每条折线不能自交。

如图所示，折线总长度为18（2、2、3、3格子中各有一条长度0.5的线）。

## 输入格式

输入包含多组数据。每组数据的第一行为正整数n、m（1≤n，m≤9），以下n行每行为m个整数，描述该网格。0表示空格，1表示障碍，2表示写有“2”的格子，3表示写有“3”的格子。

## 输出格式

对于每组数据输出一行，输出两条折线最小总长度，如果无解，输出0。



---



---

# 题号列表

- UVA1214 - Manhattan Wiring


---

---
title: "Coin Toss"
layout: "post"
diff: 省选/NOI-
pid: UVA10328
tag: ['高精度', '递推']
---

# Coin Toss

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1269

[PDF](https://uva.onlinejudge.org/external/103/p10328.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/79179092b3e0642a6c5e276c376ecc97c711e80c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/18b008ffc8ae086f399e7a71e233f58aa71d6a57.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/1cb895d961b7af0768846a0da986eb4618beedf3.png)

## 样例 #1

### 输入

```
4 1
4 2
4 3
4 4
6 2
```

### 输出

```
15
8
3
1
43
```



---

---
title: "Dumb Bones"
layout: "post"
diff: 省选/NOI-
pid: UVA10529
tag: ['递推', '枚举', '期望']
---

# Dumb Bones

## 题目描述

你正在尝试用多米诺骨牌搭成一条直线，以便最后试验时推倒它们

（确实，搭建某些东西仅仅为了推倒看上去没啥意义，但你有一些奇怪的爱好）

然而你在搭建过程中可能会弄倒骨牌，这将波及到邻近的部分

现在需要你来求将骨牌搭建完成所需的期望步数

## 输入格式

若干组数据，以0结尾

一个整数n$(1 \leq n \leq 1000)$ 表示你需要搭的骨牌数量

两个整数$P_l,P_r$ 分别表示搭建某个骨牌时向左，向右倾倒的概率

## 输出格式

对于每组数据，输出一个实数，保留两位小数，为搭建完成的期望步数

翻译提供者：Captain_Paul

## 样例 #1

### 输入

```
10 0.25 0.25
10 0.1 0.4
10 0.0 0.5
0
```

### 输出

```
46.25
37.28
20.00
```



---

---
title: "Contemplation! Algebra"
layout: "post"
diff: 省选/NOI-
pid: UVA10655
tag: ['递推', '矩阵加速', '线性递推']
---

# Contemplation! Algebra

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1596

[PDF](https://uva.onlinejudge.org/external/106/p10655.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10655/dbec0a8cf5c06f09ce23405958f51502311809a2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10655/208c2ee85a813765e3f129ae3c4df053aa8abdc5.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10655/6302967fa4db89f5c671e6a0834a6aa87e341678.png)

## 样例 #1

### 输入

```
10 16 2
7 12 3
0 0
```

### 输出

```
68
91
```



---



---

# 题号列表

- UVA10328 - Coin Toss
- UVA10529 - Dumb Bones
- UVA10655 - Contemplation! Algebra


---

---
title: "Robotruck"
layout: "post"
diff: 省选/NOI-
pid: UVA1169
tag: ['线段树', '单调队列', '队列']
---

# Robotruck

## 题目描述

有n个垃圾，第i个垃圾的坐标为(xi,yi)，重量为wi。有一个机器人，要按照编号从小到大的顺序捡起所有垃圾并扔进垃圾桶（垃圾桶在原点(0,0)）。机器人可以捡起几个垃圾以后一起扔掉，但任何时候其手中的垃圾总重量不能超过最大载重C。两点间的行走距离为曼哈顿距离（即横坐标之差的绝对值加上纵坐标之差的绝对值）。求出机器人行走的最短总路程（一开始，机器人在(0,0)处）。

## 输入格式

输入的第一行为数据组数。每组数据的第一行为最大承重C(1<=C<=100)；第二行为正整数n(1<=n<=100000)，即垃圾的数量；以下n行每行为两个非负整数x,y和一个正整数w，即坐标和重量（重量保证不超过C）。

## 输出格式

对于每组数据，输出总路径的最短长度。

输出每行一个解



---

---
title: "DNA Regions"
layout: "post"
diff: 省选/NOI-
pid: UVA1392
tag: ['单调队列', '枚举', '排序']
---

# DNA Regions

## 题目描述

## 题面
给定两个长度为 $n$ 的字符串 $A$ 和 $B$，满足 $A$ 和 $B$ 都只由大写字母 A、C、G、T 组成。

求一个长度最长的闭区间 $[L,R]$，满足对于 $i \in [L,R]$，有不超过 $p \%$ 的 $i$ 满足 $A_i \neq B_i$。

## 输入格式

包含多组数据。

对于每组数据，第一行为两个整数 $n$ 和 $q$。
接下来两行分别是 $A$ 和 $B$。

结束的标志是 $n=0$。

## 输出格式

对于每组数据，若有解，输出满足条件的区间长度的最大值，若无解，输出`No solution.`。

## 输入输出样例
### 输入
```
14 25
ACCGGTAACGTGAA
ACTGGATACGTAAA
14 24
ACCGGTAACGTGAA
ACTGGATACGTAAA
8 1
AAAAAAAA
CCCCCCCC
8 33
AAACAAAA
CCCCCCCC
0 0

```
### 输出
```
8
7
No solution.
1
```

## 说明/提示

$1 \le n \le 1.5 \times 10^5$，$1 \le p \le 99$。



---

---
title: "Parade"
layout: "post"
diff: 省选/NOI-
pid: UVA1427
tag: ['单调队列', '前缀和', '队列']
---

# Parade

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4173

[PDF](https://uva.onlinejudge.org/external/14/p1427.pdf)



---



---

# 题号列表

- UVA1169 - Robotruck
- UVA1392 - DNA Regions
- UVA1427 - Parade


---

---
title: "Coin Toss"
layout: "post"
diff: 省选/NOI-
pid: UVA10328
tag: ['高精度', '递推']
---

# Coin Toss

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1269

[PDF](https://uva.onlinejudge.org/external/103/p10328.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/79179092b3e0642a6c5e276c376ecc97c711e80c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/18b008ffc8ae086f399e7a71e233f58aa71d6a57.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/1cb895d961b7af0768846a0da986eb4618beedf3.png)

## 样例 #1

### 输入

```
4 1
4 2
4 3
4 4
6 2
```

### 输出

```
15
8
3
1
43
```



---

---
title: "The Super Powers"
layout: "post"
diff: 省选/NOI-
pid: UVA11752
tag: ['高精度', '枚举']
---

# The Super Powers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2852

[PDF](https://uva.onlinejudge.org/external/117/p11752.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/caccb369bd9149203faf09eaf595e5873b362929.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/3962a6191c1c4336a2bb19bfd7086e2d311306c0.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/ee20a6418dc90b6edefd09d6018cfe0bb329ffe4.png)

## 样例 #1

### 输入

```

```

### 输出

```
1
16
64
81
256
512
.
.
.
```



---



---

# 题号列表

- UVA10328 - Coin Toss
- UVA11752 - The Super Powers


---

