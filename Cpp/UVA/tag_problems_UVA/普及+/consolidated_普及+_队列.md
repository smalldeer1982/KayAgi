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

