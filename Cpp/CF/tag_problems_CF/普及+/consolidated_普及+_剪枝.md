---
title: "Creative Snap"
layout: "post"
diff: 普及+/提高
pid: CF1111C
tag: ['二分', '递归', '剪枝']
---

# Creative Snap

## 题目描述

灭霸要摧毁复仇者们的基地！  

我们可以将复仇者的基地看成一个序列，每个位置都有可能有多个复仇者；但是每个复仇者只能占据一个位置。  
他们基地的长度刚好是$2$的整数幂，灭霸想要用最少的能量摧毁它们。他在摧毁过程中，可以选择：  
- 如果这段基地长度$\ge 2$，他可以将其分为相等长度的两半。  
- 烧掉这段基地。如果这段基地中没有复仇者，他需要消耗$A$的能量；如果有，则需要消耗$B*x*l$的能量。其中$l$是这段基地长度，$x$是这段中的复仇者数量。  

输出一个整数，表示他摧毁全部基地需要的最少能量。  
接下来一行$k$个整数，$a_i$表示第$i$个复仇者所在的位置

## 输出格式

一个整数，表示摧毁基地所需要的最少能量。

## 说明/提示

### 样例解释  
对于样例1，直接烧区间$[1,4]$需要能量为$4*2*2=16$。  
但是，如果将其分为$4$段，分别烧掉，所需能量只有$2+1+2+1=6$。  
可以证明没有更优的方案，所以输出`6`。 
对于全部数据：  
$1\le n \le 30$  
$1\le k \le 10^5$  
$1\le A,B \le 10^4$  
$1\le a_i \le 2^n$

## 样例 #1

### 输入

```
2 2 1 2
1 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 2 1 2
1 7

```

### 输出

```
8

```



---

---
title: "Lizards and Basements 2"
layout: "post"
diff: 普及+/提高
pid: CF6D
tag: ['枚举', '深度优先搜索 DFS', '剪枝']
---

# Lizards and Basements 2

## 题目描述

有一队人，第 $i$ 个人的血量为 $h_{i}$，你可以用火球点某个人，会对当前的人造成 $a$ 点伤害，对旁边的人造成 $b$ 点伤害。

火球不能打 $1$ 号和 $n$ 号，求最少多少发火球烧死所有人。血量为负数才算死。

## 输入格式

第一行输入三个整数 $n$, $a$, $b$；

第二行输入 $n$ 个 $h_{i}$，表示每个人的血量。

## 输出格式

第一行输出 $ t $，表示需要使用的火球总数。

第二行输出 $ t $ 个数，分别表示第 $i$ 个火球打在了哪个人身上。

## 样例 #1

### 输入

```
3 2 1
2 2 2

```

### 输出

```
3
2 2 2 
```

## 样例 #2

### 输入

```
4 3 1
1 4 1 1

```

### 输出

```
4
2 2 3 3 
```



---

---
title: "Garland"
layout: "post"
diff: 普及+/提高
pid: CF767C
tag: ['动态规划 DP', '剪枝', '树形 DP']
---

# Garland

## 题目描述

Once at New Year Dima had a dream in which he was presented a fairy garland. A garland is a set of lamps, some pairs of which are connected by wires. Dima remembered that each two lamps in the garland were connected directly or indirectly via some wires. Furthermore, the number of wires was exactly one less than the number of lamps.

There was something unusual about the garland. Each lamp had its own brightness which depended on the temperature of the lamp. Temperatures could be positive, negative or zero. Dima has two friends, so he decided to share the garland with them. He wants to cut two different wires so that the garland breaks up into three parts. Each part of the garland should shine equally, i. e. the sums of lamps' temperatures should be equal in each of the parts. Of course, each of the parts should be non-empty, i. e. each part should contain at least one lamp.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/c2b0d1858f505d34921dc11648298e7a84c2f7b5.png)Help Dima to find a suitable way to cut the garland, or determine that this is impossible.

While examining the garland, Dima lifted it up holding by one of the lamps. Thus, each of the lamps, except the one he is holding by, is now hanging on some wire. So, you should print two lamp ids as the answer which denote that Dima should cut the wires these lamps are hanging on. Of course, the lamp Dima is holding the garland by can't be included in the answer.

## 输入格式

The first line contains single integer $ n $ ( $ 3<=n<=10^{6} $ ) — the number of lamps in the garland.

Then $ n $ lines follow. The $ i $ -th of them contain the information about the $ i $ -th lamp: the number lamp $ a_{i} $ , it is hanging on (and $ 0 $ , if is there is no such lamp), and its temperature $ t_{i} $ ( $ -100<=t_{i}<=100 $ ). The lamps are numbered from $ 1 $ to $ n $ .

## 输出格式

If there is no solution, print -1.

Otherwise print two integers — the indexes of the lamps which mean Dima should cut the wires they are hanging on. If there are multiple answers, print any of them.

## 说明/提示

The garland and cuts scheme for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767C/578d2b3356505b1b3987876ed70f57ef1ae0c5b0.png)

## 样例 #1

### 输入

```
6
2 4
0 5
4 2
2 1
1 1
4 2

```

### 输出

```
1 4

```

## 样例 #2

### 输入

```
6
2 4
0 6
4 2
2 1
1 1
4 2

```

### 输出

```
-1

```



---

---
title: "Olya and Energy Drinks"
layout: "post"
diff: 普及+/提高
pid: CF877D
tag: ['广度优先搜索 BFS', '剪枝']
---

# Olya and Energy Drinks

## 题目描述

有一NxM的迷宫，'#'是墙，‘.’是路，一秒钟可以向四个方向中的一个移动1~k步，求从起点到终点的最短时间。

## 输入格式

第一行n、m、k，下面是NxM的迷宫，最后是起点到终点的坐标。

## 输出格式

输出最短时间。如果不能离开迷宫，输出-1。

## 样例 #1

### 输入

```
3 4 4
....
###.
....
1 1 3 1

```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4 1
....
###.
....
1 1 3 1

```

### 输出

```
8
```

## 样例 #3

### 输入

```
2 2 1
.#
#.
1 1 2 2

```

### 输出

```
-1
```



---

