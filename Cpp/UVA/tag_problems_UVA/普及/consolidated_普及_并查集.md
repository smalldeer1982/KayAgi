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

