# 题目信息

# Mike and Shortcuts

## 题目描述

Recently, Mike was very busy with studying for exams and contests. Now he is going to chill a bit by doing some sight seeing in the city.

City consists of $ n $ intersections numbered from $ 1 $ to $ n $ . Mike starts walking from his house located at the intersection number $ 1 $ and goes along some sequence of intersections. Walking from intersection number $ i $ to intersection $ j $ requires $ |i-j| $ units of energy. The total energy spent by Mike to visit a sequence of intersections $ p_{1}=1,p_{2},...,p_{k} $ is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689B/cc97750fb7205e858b8008fe7ee7f7055a90a20f.png) units of energy.

Of course, walking would be boring if there were no shortcuts. A shortcut is a special path that allows Mike walking from one intersection to another requiring only $ 1 $ unit of energy. There are exactly $ n $ shortcuts in Mike's city, the $ i^{th} $ of them allows walking from intersection $ i $ to intersection $ a_{i} $ ( $ i<=a_{i}<=a_{i+1} $ ) (but not in the opposite direction), thus there is exactly one shortcut starting at each intersection. Formally, if Mike chooses a sequence $ p_{1}=1,p_{2},...,p_{k} $ then for each $ 1<=i&lt;k $ satisfying $ p_{i+1}=a_{pi} $ and $ a_{pi}≠p_{i} $ Mike will spend only $ 1 $ unit of energy instead of $ |p_{i}-p_{i+1}| $ walking from the intersection $ p_{i} $ to intersection $ p_{i+1} $ . For example, if Mike chooses a sequence $ p_{1}=1,p_{2}=a_{p1},p_{3}=a_{p2},...,p_{k}=a_{pk-1} $ , he spends exactly $ k-1 $ units of total energy walking around them.

Before going on his adventure, Mike asks you to find the minimum amount of energy required to reach each of the intersections from his home. Formally, for each $ 1<=i<=n $ Mike is interested in finding minimum possible total energy of some sequence $ p_{1}=1,p_{2},...,p_{k}=i $ .

## 说明/提示

In the first sample case desired sequences are:

 $ 1:1 $ ; $ m_{1}=0 $ ;

 $ 2:1,2 $ ; $ m_{2}=1 $ ;

 $ 3:1,3 $ ; $ m_{3}=|3-1|=2 $ .

In the second sample case the sequence for any intersection $ 1&lt;i $ is always $ 1,i $ and $ m_{i}=|1-i| $ .

In the third sample case — consider the following intersection sequences:

 $ 1:1 $ ; $ m_{1}=0 $ ;

 $ 2:1,2 $ ; $ m_{2}=|2-1|=1 $ ;

 $ 3:1,4,3 $ ; $ m_{3}=1+|4-3|=2 $ ;

 $ 4:1,4 $ ; $ m_{4}=1 $ ;

 $ 5:1,4,5 $ ; $ m_{5}=1+|4-5|=2 $ ;

 $ 6:1,4,6 $ ; $ m_{6}=1+|4-6|=3 $ ;

 $ 7:1,4,5,7 $ ; $ m_{7}=1+|4-5|+1=3 $ .

## 样例 #1

### 输入

```
3
2 2 3
```

### 输出

```
0 1 2 
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0 1 2 3 4 
```

## 样例 #3

### 输入

```
7
4 4 4 4 7 7 7
```

### 输出

```
0 1 2 1 2 3 3 
```

# AI分析结果

### 题目内容
# Mike和捷径

## 题目描述
最近，Mike忙于备考和竞赛。现在他打算通过在城市中观光来放松一下。

城市由 $n$ 个十字路口组成，编号从 $1$ 到 $n$ 。Mike从位于十字路口 $1$ 的家出发，沿着一系列十字路口行走。从十字路口 $i$ 走到十字路口 $j$ 需要 $|i - j|$ 单位的能量。Mike访问一系列十字路口 $p_{1}=1,p_{2},\cdots,p_{k}$ 所花费的总能量等于 $\sum_{i = 1}^{k - 1}|p_{i}-p_{i + 1}|$ 单位能量。

当然，如果没有捷径，步行会很无聊。捷径是一种特殊的路径，它允许Mike从一个十字路口走到另一个十字路口只需要 $1$ 单位的能量。在Mike所在的城市中恰好有 $n$ 条捷径，第 $i$ 条捷径允许从十字路口 $i$ 走到十字路口 $a_{i}$（$i\leq a_{i}\leq a_{i + 1}$）（但不能反向行走），因此每个十字路口都恰好有一条捷径起始于此。正式地说，如果Mike选择一个序列 $p_{1}=1,p_{2},\cdots,p_{k}$，那么对于每个满足 $p_{i + 1}=a_{p_{i}}$ 且 $a_{p_{i}}\neq p_{i}$ 的 $1\leq i\lt k$，Mike从十字路口 $p_{i}$ 走到十字路口 $p_{i + 1}$ 将只花费 $1$ 单位能量，而不是 $|p_{i}-p_{i + 1}|$。例如，如果Mike选择一个序列 $p_{1}=1,p_{2}=a_{p_{1}},p_{3}=a_{p_{2}},\cdots,p_{k}=a_{p_{k - 1}}$，他在这些路口间行走总共恰好花费 $k - 1$ 单位能量。

在开始他的冒险之前，Mike请你找出从他家到达每个十字路口所需的最小能量。正式地说，对于每个 $1\leq i\leq n$，Mike想找到某个序列 $p_{1}=1,p_{2},\cdots,p_{k}=i$ 的最小可能总能量。

## 说明/提示
在第一个样例中，所需的序列如下：
 - $1:1$ ；$m_{1}=0$ ；
 - $2:1,2$ ；$m_{2}=1$ ；
 - $3:1,3$ ；$m_{3}=|3 - 1|=2$ 。

在第二个样例中，对于任何 $1\lt i$ 的十字路口，序列总是 $1,i$ ，且 $m_{i}=|1 - i|$ 。

在第三个样例中，考虑以下十字路口序列：
 - $1:1$ ；$m_{1}=0$ ；
 - $2:1,2$ ；$m_{2}=|2 - 1|=1$ ；
 - $3:1,4,3$ ；$m_{3}=1+|4 - 3|=2$ ；
 - $4:1,4$ ；$m_{4}=1$ ；
 - $5:1,4,5$ ；$m_{5}=1+|4 - 5|=2$ ；
 - $6:1,4,6$ ；$m_{6}=1+|4 - 6|=3$ ；
 - $7:1,4,5,7$ ；$m_{7}=1+|4 - 5|+1=3$ 。

## 样例 #1
### 输入
```
3
2 2 3
```
### 输出
```
0 1 2 
```

## 样例 #2
### 输入
```
5
1 2 3 4 5
```
### 输出
```
0 1 2 3 4 
```

## 样例 #3
### 输入
```
7
4 4 4 4 7 7 7
```
### 输出
```
0 1 2 1 2 3 3 
```

### 算法分类
最短路

### 题解综合分析与结论
这些题解的核心思路都是将问题转化为图论中的最短路问题。要点在于构建图的边，包括相邻节点间权值为1的双向边以及题目给定的从i到ai权值为1的单向边。难点在于如何在n较大时避免构建过多边导致复杂度爆炸，多个题解都提到只需构建相邻节点边和给定单向边，因为长距离边可由这些短边组合而成。大部分题解使用Dijkstra算法求解最短路，部分使用SPFA算法。在代码实现上，有使用邻接表、vector等不同方式存储图。

### 通用建议与扩展思路
对于此类最短路问题，关键在于合理建图，根据题目条件挖掘出图的边结构，避免不必要的边以降低复杂度。可拓展到其他涉及特殊路径权值、特定图结构的最短路问题。例如，一些图中存在不同类型的边，需根据条件选择合适的边组合来求最短路。

### 洛谷相似题目
- P3371 【模板】单源最短路径（弱化版）
- P4779 【模板】单源最短路径（标准版）
- P1339 热浪 

---
处理用时：39.47秒