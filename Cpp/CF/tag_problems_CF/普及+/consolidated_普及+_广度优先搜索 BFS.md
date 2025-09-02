---
title: "Minimum path"
layout: "post"
diff: 普及+/提高
pid: CF1031D
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS']
---

# Minimum path

## 题目描述

给你一个n×n的全是小写字母的矩阵,你能改变k个字母



你要从左上角走到右下角,且每步只能移动到右边或下边的字母上。



对于每一条路径都会得到一个由你经过的所有字母组成的字符串。当然,他的长度是2×n-1.



在你最多改动k个字母的情况下,找到一个得到字符串字典序最小的路径.



一个字符串a如果字典序比字符串b小,那他们第一个不同的字符在a中小于b.

## 输入格式

第一行包括两个整数n和k(1≤n≤2000,0≤k≤n2),矩阵的大小和你最多能改变的字母数.



下面n行,每行n个小写字母.

## 输出格式

在你最多改动k个字母的情况下,得到的一个字符串字典序最小的路径.

## 样例 #1

### 输入

```
4 2
abcd
bcde
bcad
bcde

```

### 输出

```
aaabcde

```

## 样例 #2

### 输入

```
5 3
bwwwz
hrhdh
sepsp
sqfaf
ajbvw

```

### 输出

```
aaaepfafw

```

## 样例 #3

### 输入

```
7 6
ypnxnnp
pnxonpm
nxanpou
xnnpmud
nhtdudu
npmuduh
pmutsnz

```

### 输出

```
aaaaaaadudsnz

```



---

---
title: "Turtle Mission: Robot and the Earthquake"
layout: "post"
diff: 普及+/提高
pid: CF1933F
tag: ['广度优先搜索 BFS']
---

# Turtle Mission: Robot and the Earthquake

## 题目描述

The world is a grid with $ n $ rows and $ m $ columns. The rows are numbered $ 0, 1, \ldots, n-1 $ , while the columns are numbered $ 0, 1, \ldots, m-1 $ . In this world, the columns are cyclic (i.e. the top and the bottom cells in each column are adjacent). The cell on the $ i $ -th row and the $ j $ -th column ( $ 0 \le i < n, 0 \le j < m $ ) is denoted as $ (i,j) $ .

At time $ 0 $ , the cell $ (i,j) $ (where $ 0 \le i < n, 0 \le j < m $ ) contains either a rock or nothing. The state of cell $ (i,j) $ can be described using the integer $ a_{i,j} $ :

- If $ a_{i,j} = 1 $ , there is a rock at $ (i,j) $ .
- If $ a_{i,j} = 0 $ , there is nothing at $ (i,j) $ .

As a result of aftershocks from the earthquake, the columns follow tectonic plate movements: each column moves cyclically upwards at a velocity of $ 1 $ cell per unit of time. Formally, for some $ 0 \le i < n, 0 \le j < m $ , if $ (i,j) $ contains a rock at the moment, it will move from $ (i, j) $ to $ (i - 1, j) $ (or to $ (n - 1, j) $ if $ i=0 $ ).

The robot called RT is initially positioned at $ (0,0) $ . It has to go to $ (n-1,m-1) $ to carry out an earthquake rescue operation (to the bottom rightmost cell). The earthquake doesn't change the position of the robot, they only change the position of rocks in the world.

Let RT's current position be $ (x,y) $ ( $ 0 \le x < n, 0 \le y < m $ ), it can perform the following operations:

- Go one cell cyclically upwards, i.e. from $ (x,y) $ to $ ((x+n-1) \bmod n, y) $ using $ 1 $ unit of time.
- Go one cell cyclically downwards, i.e. $ (x,y) $ to $ ((x+1) \bmod n, y) $ using $ 1 $ unit of time.
- Go one cell to the right, i.e. $ (x,y) $ to $ (x, y+1) $ using $ 1 $ unit of time. (RT may perform this operation only if $ y < m-1 $ .)

Note that RT cannot go left using the operations nor can he stay at a position.

Unfortunately, RT will explode upon colliding with a rock. As such, when RT is at $ (x,y) $ and there is a rock at $ ((x+1) \bmod n, y) $ or $ ((x+2) \bmod n, y) $ , RT cannot move down or it will be hit by the rock.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/e6c2eefb52b92661f33f40565f8703b698e45850.png)Similarly, if $ y+1 < m $ and there is a rock at $ ((x+1) \bmod n, y+1) $ , RT cannot move right or it will be hit by the rock.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/fb10a6984c9e2fa62a504f01d0bebb40cf60e8a4.png)However, it is worth noting that if there is a rock at $ (x \bmod n, y+1) $ and $ ((x+1) \bmod n, y) $ , RT can still move right safely.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/7a53bd04bd2915c103d70abe831abd04969b7ef5.png)Find the minimum amount of time RT needs to reach $ (n-1,m-1) $ without colliding with any rocks. If it is impossible to do so, output $ -1 $ .

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

In each test case, the first line contains two integers $ n $ , $ m $ ( $ 3 \le n, m \le 10^3 $ ) — the size of the planet's boundaries.

Each of the next $ n $ lines contains $ m $ integers. The $ (j+1) $ -th integer on the $ (i+1) $ -th line ( $ 0 \le i < n, 0 \le j < m $ ) is $ a_{i,j} $ ( $ 0 \le a_{i,j} \le 1 $ ), which denotes whether or not there is a rock at $ (i,j) $ at time $ 0 $ .

Additionally, it is guaranteed that $ a_{0,0} = 0 $ , and $ a_{i, m-1} = 0 $ for $ 0 \le i < n $ . In other words, there is no rock at RT's initial position as well as column $ m-1 $ .

The sum of $ n \cdot m $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case:

- If the destination can be reached without colliding with any rocks, output a single integer — the minimum amount of time RT needs to reach $ (n-1,m-1) $ .
- Otherwise, output $ -1 $ .

## 说明/提示

Visual explanation of the first test case in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1933F/765b33690d3fb490f30273f591cef774fd4d800f.png)

## 样例 #1

### 输入

```
6
4 5
0 1 0 0 0
0 0 1 0 0
1 0 1 1 0
0 0 0 0 0
3 3
0 0 0
1 0 0
0 0 0
5 3
0 0 0
0 0 0
1 0 0
0 0 0
1 0 0
3 7
0 0 1 0 0 1 0
1 0 1 0 1 0 0
0 1 0 0 0 0 0
3 4
0 1 0 0
1 0 0 0
0 1 1 0
5 5
0 0 0 0 0
0 1 0 1 0
0 1 0 1 0
0 1 0 1 0
0 0 0 1 0
```

### 输出

```
7
3
3
8
-1
12
```

## 样例 #2

### 输入

```
6
3 3
0 0 0
0 0 0
0 0 0
4 3
0 1 0
1 0 0
0 1 0
1 0 0
4 3
0 1 0
0 1 0
0 1 0
0 1 0
3 3
0 0 0
1 1 0
0 0 0
3 3
0 1 0
0 0 0
0 1 0
5 5
0 0 0 0 0
0 1 1 0 0
0 1 1 0 0
0 0 0 0 0
0 0 1 0 0
```

### 输出

```
3
3
-1
-1
3
8
```



---

---
title: "Tree Jumps"
layout: "post"
diff: 普及+/提高
pid: CF2070D
tag: ['动态规划 DP', '广度优先搜索 BFS', '树的遍历']
---

# Tree Jumps

## 题目描述

给定一棵包含 $n$ 个顶点的有根树。树中顶点编号为 $1$ 到 $n$，根为顶点 $1$。定义 $d_x$ 为根到顶点 $x$ 的距离（最短路径上的边数）。

初始时，一个棋子被放置在根节点。你可以执行以下操作任意次（包括零次）：

- 将棋子从当前顶点 $v$ 移动到顶点 $u$，满足 $d_u = d_v + 1$。如果 $v$ 是根节点，可以选择任意满足此约束的顶点 $u$；但如果 $v$ 不是根节点，则 $u$ 不能是 $v$ 的邻居（即 $v$ 和 $u$ 之间不能有直接边相连）。

例如在上图的树结构中，允许的移动包括：$1 \rightarrow 2$，$1 \rightarrow 5$，$2 \rightarrow 7$，$5 \rightarrow 3$，$5 \rightarrow 4$，$3 \rightarrow 6$，$7 \rightarrow 6$。

如果一个顶点序列满足：存在一种棋子移动方式，使得棋子按顺序恰好访问序列中的所有顶点（且仅这些顶点），则该序列被称为有效的。

你的任务是计算有效顶点序列的数量。由于答案可能很大，请输出其对 $998244353$ 取模的结果。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 3 \cdot 10^5$）。

第二行包含 $n-1$ 个整数 $p_2, p_3, \dots, p_n$（$1 \le p_i < i$），其中 $p_i$ 表示第 $i$ 个顶点的父节点。顶点 $1$ 是根节点。

输入额外约束：所有测试用例的 $n$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——有效顶点序列的数量模 $998244353$ 的结果。

## 说明/提示

第一个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 4]$，$[1, 4, 3]$。

第二个示例中，有效序列为：$[1]$，$[1, 2]$。

第三个示例中，有效序列为：$[1]$，$[1, 2]$，$[1, 2, 7]$，$[1, 2, 7, 6]$，$[1, 5]$，$[1, 5, 3]$，$[1, 5, 3, 6]$，$[1, 5, 4]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
1 2 1
3
1 2
7
1 2 2 1 4 5
```

### 输出

```
4
2
8
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

