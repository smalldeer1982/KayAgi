---
title: "Military Problem"
layout: "post"
diff: 普及+/提高
pid: CF1006E
tag: ['深度优先搜索 DFS', '图论建模', '向量']
---

# Military Problem

## 题目描述

在这个问题中你需要帮助伯兰（？？我没找到有Berland这个国家）军队组织他们的指挥系统

伯兰军队中一共有n个军官。第一个官员是军队的指挥官，他并没有任何上级。其他的军官都有且只有一个直接的上级。如果一个军官a是军官b的上级，那么你也可以说军官b就是军官a的下属

如果满足下列条件，那么军官x就是军官y的下属（直接或非直接）：

1.y是x的直接上级 2.x的直接上级是y的下属

举个例子，下图的官员3的下属有:5,6,7,8,9

所以，在伯兰军队的结构中，除了指挥官，其他人都是指挥官的下属

形式上的，让我们把伯兰军队看成一棵拥有n个节点的树，树的节点u就代表了军官u。根（即一号节点）就相当于指挥官

伯兰战争部门命令你对q个查询给出答案。这q个查询会以（ui，ki）的形式给出，ui代表了某个军官，ki是正整数。你需要输出，编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

要处理第i个查询，想象一下ui的命令如何我下达到ui的下属。这里使用了典型的DFS（深度优先搜索）算法。

假设现在的军官是a，他要下达一个命令。a军官选择一个军官b——还没有收到这个命令的直接下属（即在树上的一个孩子）。如果有许多这样的直接下属，那么A选择编号最小的那一个。A军官向B军官发出命令。之后，B使用完全相同的方式将命令扩展到它的子树。在B完成命令后，军官A再次选择下一个直接下属（使用相同的策略）。当军官A不能选择任何还没有接到命令的直接下属时，军官A下达命令完成。

让我们看一下下面这个例子（看下面的图）：

如果军官1下达了命令，军官们收到命令的顺序是：1,2,3,5,6,8,7,9,4

如果军官3下达了命令，军官们收到命令的顺序是：3,5,6,8,7,9

如果军官7下达了命令，军官们收到命令的顺序是：7,9

如果军官9下达了命令，军官们收到命令的顺序是：9

你应当分开处理这些查询。一个查询不会影响其他查询的结果。

## 输入格式

第一行包括两个整数n,q，表示有n个军官和q个查询（2≤n≤2×10^5,1≤q≤2×10^5）

第二行包括n-1个整数,p2、p3……pn，(1≤p<i )表示编号为i的军官直接上级为pi。编号为1的为指挥官并且他没有上级，不在输入数据中。

接下来的q行是q个查询每行包含两个整数(ui,ki)（1≤ui,ki≤n）ui表示开始下达命令的军官，ki表示要输出的军官编号是第几个得知命令的

## 输出格式

一共q行，每行包含一个整数表示第i个查询的答案：编号为ui的军官下达命令后，第ki个得知此命令的军官编号是多少，如果传达人数不足ki个，输出-1。

感谢@hicc0305 提供的翻译

## 样例 #1

### 输入

```
9 6
1 1 1 3 5 3 5 7
3 1
1 5
3 4
7 3
1 8
1 9

```

### 输出

```
3
6
8
-1
9
4

```



---

---
title: "Nearest vectors"
layout: "post"
diff: 普及+/提高
pid: CF598C
tag: ['向量']
---

# Nearest vectors

## 题目描述

You are given the set of vectors on the plane, each of them starting at the origin. Your task is to find a pair of vectors with the minimal non-oriented angle between them.

Non-oriented angle is non-negative value, minimal between clockwise and counterclockwise direction angles. Non-oriented angle is always between $ 0 $ and $ π $ . For example, opposite directions vectors have angle equals to $ π $ .

## 输入格式

First line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the number of vectors.

The $ i $ -th of the following $ n $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ |x|,|y|<=10000,x^{2}+y^{2}&gt;0 $ ) — the coordinates of the $ i $ -th vector. Vectors are numbered from $ 1 $ to $ n $ in order of appearing in the input. It is guaranteed that no two vectors in the input share the same direction (but they still can have opposite directions).

## 输出格式

Print two integer numbers $ a $ and $ b $ ( $ a≠b $ ) — a pair of indices of vectors with the minimal non-oriented angle. You can print the numbers in any order. If there are many possible answers, print any.

## 样例 #1

### 输入

```
4
-1 0
0 -1
1 0
1 1

```

### 输出

```
3 4

```

## 样例 #2

### 输入

```
6
-1 0
0 -1
1 0
1 1
-4 -5
-4 -6

```

### 输出

```
6 5
```



---

---
title: "Five Dimensional Points"
layout: "post"
diff: 普及+/提高
pid: CF850A
tag: ['枚举', '向量']
---

# Five Dimensional Points

## 题目描述

You are given set of $ n $ points in 5-dimensional space. The points are labeled from $ 1 $ to $ n $ . No two points coincide.

We will call point $ a $ bad if there are different points $ b $ and $ c $ , not equal to $ a $ , from the given set such that angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0653dbc57091409c95cbdb75a14170af617d0442.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/bde2e95036e34134c1ea6bd6b9709d7dd49d1b09.png) is acute (i.e. strictly less than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png)). Otherwise, the point is called good.

The angle between vectors ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/2c10c8fe0b4dfc279c1514830bc9fce0b1aa6b49.png) in 5-dimensional space is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/d27dbfc0849680d0f326c5cde0af47140b2f6df3.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/0fea22328d6b3b4c1d11529ba4c9764cafce84d3.png) is the scalar product and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/f06b81b731bd497af38154f7447638a84ce787f2.png) is length of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/5a3a683029365387cf086e592ebfccb0e126e88a.png).

Given the list of points, print the indices of the good points in ascending order.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=10^{3} $ ) — the number of points.

The next $ n $ lines of input contain five integers $ a_{i},b_{i},c_{i},d_{i},e_{i} $ ( $ |a_{i}|,|b_{i}|,|c_{i}|,|d_{i}|,|e_{i}|<=10^{3} $ ) — the coordinates of the i-th point. All points are distinct.

## 输出格式

First, print a single integer $ k $ — the number of good points.

Then, print $ k $ integers, each on their own line — the indices of the good points in ascending order.

## 说明/提示

In the first sample, the first point forms exactly a ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/fe3c8011bb9ee15abb5ac0ee9f2f980eef59656c.png) angle with all other pairs of points, so it is good.

In the second sample, along the cd plane, we can see the points look as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850A/dc25f4e169ea69409034b12812dd7f4f82002152.png)

We can see that all angles here are acute, so no points are good.

## 样例 #1

### 输入

```
6
0 0 0 0 0
1 0 0 0 0
0 1 0 0 0
0 0 1 0 0
0 0 0 1 0
0 0 0 0 1

```

### 输出

```
1
1

```

## 样例 #2

### 输入

```
3
0 0 1 2 0
0 0 9 2 0
0 0 5 9 0

```

### 输出

```
0

```



---

---
title: "Knights of a Polygonal Table"
layout: "post"
diff: 普及+/提高
pid: CF994B
tag: ['贪心', '平衡树', '向量']
---

# Knights of a Polygonal Table

## 题目描述

有  $n$  个骑士想决战。每个骑士都有能力值，且身上带有一些金币。如果骑士  $A$  的能力值大于骑士  $B$ ，那么骑士  $A$  就可以杀死骑士  $B$ ，并获得骑士  $B$  身上的所有金币。但就算是骑士也不会残忍过度，他们最多只会杀死  $k$  个骑士。对于每一位骑士，请你求出在决战后他身上金币的最大值。

## 输入格式

第  $1$  行，有  $2$  个整数，分别为骑士人数  $n$  和杀人数上限  $k$ 。

（数据范围： $1 \leqslant n \leqslant 10^{5}$ , $0 \leqslant k \leqslant min(n - 1,\ 10)$ ）

第  $2$  行，有  $n$  个整数，表示每个骑士的能力值  $p_i$ 。

第  $3$  行，有  $n$  个整数，表示每个骑士原有的金币  $c_i$ 。

（数据范围： $1 \leqslant p_i \leqslant 10^{9}$ , $0 \leqslant c_i \leqslant 10^{9}$ ）

## 输出格式

$1$  行内输出  $n$  个整数，决战后每个骑士身上金币的最大值，每两个数间以单个空格隔开。

## 说明/提示

- 第  $1$  组样例的解释：

第  $1$  个骑士是最蒻的，因此他谁也不能杀，只能保留自己原有的金币。

第  $2$  个骑士只能杀死第  $1$  个骑士，因此他最多拥有  $2 + 1 = 3$  个金币。

第  $3$  个骑士是最蔃的，但他只能选择杀  $k = 2$  个骑士。显然他会杀死第  $2$  个骑士和
第  $4$  个骑士，因为他们身上的金币更多。因此他最多拥有  $11 + 2 + 33 = 46$  个金币。

第  $4$  个骑士应该杀死第  $1$  个和第  $2$  个骑士，因此他最多拥有  $33 + 1 + 2 = 36$  个金币。 

- 第  $2$  组样例的解释：

除了最蒻的第  $1$  个骑士谁也不能杀，其他骑士都能杀死前一个骑士并获得他的金币。

- 第  $3$  组样例的解释：

由于只有一个骑士在决战中，他无法杀死任何人。

感谢@Sooke 提供翻译

## 样例 #1

### 输入

```
4 2
4 5 9 7
1 2 11 33

```

### 输出

```
1 3 46 36 
```

## 样例 #2

### 输入

```
5 1
1 2 3 4 5
1 2 3 4 5

```

### 输出

```
1 3 5 7 9 
```

## 样例 #3

### 输入

```
1 0
2
3

```

### 输出

```
3 
```



---

