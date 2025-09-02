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

