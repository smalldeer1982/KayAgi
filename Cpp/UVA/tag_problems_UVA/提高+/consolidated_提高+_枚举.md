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

