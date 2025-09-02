---
title: "Sanae and Giant Robot"
layout: "post"
diff: 省选/NOI-
pid: CF1687C
tag: ['并查集', '广度优先搜索 BFS']
---

# Sanae and Giant Robot

## 题目描述

> 果然是那个吗！因为其实用性而无法被实现的！只能出现于憧憬中的，二足步行巨大机器人！——东风谷早苗，《东方非想天则》

早苗制造了一台巨大的机器人——非想天则，但是这个机器人出了一些故障。更糟糕的是，早苗不知道如何将其停止运行，因而早苗只能在机器人运行的时候对其修复。

非想天则的状态可以用一个正整数数列 $n$ 来表示。非想天则现在处于状态 $a_1,a_2,\dots a_n$，而早苗希望将其变为 $b_1,b_2,\dots,b_n$。

作为一位优秀的女子高中生，早苗非常了解复制粘贴的艺术。她有 $m$ 个可供选择的区间，在每一次操作中，早苗可以把序列 $b$ 中的一个可选择的区间对应位置地复制粘贴到序列 $a$ 中，前提是要求序列 $a$ 的每个数字的总和不变。形式化地来讲，早苗可以选择一个区间 $[l,r]$，执行操作 $a_i \leftarrow b_i (l \leq i \leq r)$，当且仅当 $\sum \limits_{i=1}^n a_i$ 不变。

请你判断早苗能否通过若干次这样的操作，将非想天则的状态由序列 $a$ 转化为序列 $b$。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 2 \times 10^4)$，表示输入数据组数。   
对于每组数据，首先输入两个正整数 $n,m(2 \leq n \leq 2 \times 10^5,1 \leq m \leq 10^5)$，分别表示数列 $a,b$ 的长度和可以操作的区间个数。        
第二行输入 $n$ 个正整数 $a_i(1 \leq a_i \leq 10^9)$，表示非想天则的状态。     
第三行输入 $n$ 个正整数 $b_i(1 \leq b_i \leq 10^9)$，表示早苗希望非想天则变成的状态。      
接下来输入 $m$ 行，每行两个正整数 $l,r(1 \leq l < r \leq n)$，表示早苗可以进行操作的区间。     
数据保证，$\sum n,\sum m \leq 2 \times 10^5$。

## 输出格式

如果早苗可以将数列 $a$ 转化为数列 $b$，则输出 `YES`，否则输出 `NO`，不区分大小写。

## 样例 #1

### 输入

```
2
5 2
1 5 4 2 3
3 2 5 4 1
1 3
2 5
5 2
1 5 4 2 3
3 2 4 5 1
1 2
2 4
```

### 输出

```
YES
NO
```



---

---
title: "Colorado Potato Beetle"
layout: "post"
diff: 省选/NOI-
pid: CF243C
tag: ['搜索', '离散化', '广度优先搜索 BFS']
---

# Colorado Potato Beetle

## 题目描述

Old MacDonald has a farm and a large potato field, $ (10^{10}+1)×(10^{10}+1) $ square meters in size. The field is divided into square garden beds, each bed takes up one square meter.

Old McDonald knows that the Colorado potato beetle is about to invade his farm and can destroy the entire harvest. To fight the insects, Old McDonald wants to spray some beds with insecticides.

So Old McDonald went to the field, stood at the center of the central field bed and sprayed this bed with insecticides. Now he's going to make a series of movements and spray a few more beds. During each movement Old McDonald moves left, right, up or down the field some integer number of meters. As Old McDonald moves, he sprays all the beds he steps on. In other words, the beds that have any intersection at all with Old McDonald's trajectory, are sprayed with insecticides.

When Old McDonald finished spraying, he wrote out all his movements on a piece of paper. Now he wants to know how many beds won't be infected after the invasion of the Colorado beetles.

It is known that the invasion of the Colorado beetles goes as follows. First some bed on the field border gets infected. Than any bed that hasn't been infected, hasn't been sprayed with insecticides and has a common side with an infected bed, gets infected as well. Help Old McDonald and determine the number of beds that won't be infected by the Colorado potato beetle.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=1000 $ ) — the number of Old McDonald's movements.

Next $ n $ lines contain the description of Old McDonald's movements. The $ i $ -th of these lines describes the $ i $ -th movement. Each movement is given in the format " $ d_{i} $ $ x_{i} $ ", where $ d_{i} $ is the character that determines the direction of the movement ("L", "R", "U" or "D" for directions "left", "right", "up" and "down", correspondingly), and $ x_{i} $ ( $ 1<=x_{i}<=10^{6} $ ) is an integer that determines the number of meters in the movement.

## 输出格式

Print a single integer — the number of beds that won't be infected by the Colorado potato beetle.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
5
R 8
U 9
L 9
D 8
L 2

```

### 输出

```
101
```

## 样例 #2

### 输入

```
7
R 10
D 2
L 7
U 9
D 2
R 3
D 10

```

### 输出

```
52
```



---

---
title: "AND Graph"
layout: "post"
diff: 省选/NOI-
pid: CF986C
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS', '位运算']
---

# AND Graph

## 题目描述

给定一个 $m$ 个整数的集合，每个整数在 $0$ 到 $2^n-1$ 之间，以每一个整数作为顶点建无向图，当两个点 $x$ 和 $y$ 做与运算值为 $0$ 时，则认为 $x$ 和 $y$ 是连通的，即 $x$ 和 $y$ 之间有一条无向边。请求出图中连通块的个数。

## 输入格式

第一行输入两个整数 $n$ 和 $m$（$0 \leq  n\leq22$，$1 \leq  m\leq2^n$）。  
第二行输入 $m$ 个整数，即集合里的元素。

## 输出格式

一个整数，表示图中连通块的个数。

## 样例 #1

### 输入

```
2 3
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 5
5 19 10 20 12

```

### 输出

```
2

```



---

