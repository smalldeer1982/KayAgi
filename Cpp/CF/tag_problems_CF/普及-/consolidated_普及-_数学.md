---
title: "Packets"
layout: "post"
diff: 普及-
pid: CF1037A
tag: ['数学', '枚举', '进制']
---

# Packets

## 题目描述

你有$n$个硬币，每个硬币价值都为$1$。

你要把它们分成若干个小包裹，使得在$1$与$n$之间的所有面额都能用这其中某几个小包裹凑出。

每个小包裹只能作为一个整体使用。

请求出最少要分几个包裹。

## 输入格式

一个数$n$($1\le n\le 10^9$)。

## 输出格式

输出最少要分几个包裹。

### 样例解释1：

分成$3$个包裹：$[1,2,3]$，可以凑出$1$到$6$中所有的面额。

## 样例 #1

### 输入

```
6

```

### 输出

```
3
```

## 样例 #2

### 输入

```
2

```

### 输出

```
2
```



---

---
title: "Put Knight!"
layout: "post"
diff: 普及-
pid: CF120E
tag: ['数学']
---

# Put Knight!

## 题目描述

Petya and Gena play a very interesting game "Put a Knight!" on a chessboard $ n×n $ in size. In this game they take turns to put chess pieces called "knights" on the board so that no two knights could threat each other. A knight located in square $ (r,c) $ can threat squares $ (r-1,c+2) $ , $ (r-1,c-2) $ , $ (r+1,c+2) $ , $ (r+1,c-2) $ , $ (r-2,c+1) $ , $ (r-2,c-1) $ , $ (r+2,c+1) $ and $ (r+2,c-1) $ (some of the squares may be located outside the chessboard). The player who can't put a new knight during his move loses. Determine which player wins considering that both players play optimally well and Petya starts.

## 输入格式

The first line contains integer $ T $ ( $ 1<=T<=100 $ ) — the number of boards, for which you should determine the winning player. Next $ T $ lines contain $ T $ integers $ n_{i} $ ( $ 1<=n_{i}<=10000 $ ) — the sizes of the chessboards.

## 输出格式

For each $ n_{i}×n_{i} $ board print on a single line "0" if Petya wins considering both players play optimally well. Otherwise, print "1".

## 样例 #1

### 输入

```
2
2
1

```

### 输出

```
1
0

```



---

---
title: "Buying Shovels"
layout: "post"
diff: 普及-
pid: CF1360D
tag: ['数学', '数论', '枚举']
---

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       100 $ ) — the number of test cases in the input. Then, $ t $ test cases follow, one per line.

Each test case consists of two positive integers $ n $ ( $ 1       \le n \le 10^9 $ ) and $ k $ ( $ 1 \le k \le 10^9 $ ) — the number of shovels and the number of types of packages.

## 输出格式

Print $ t $ answers to the test cases. Each answer is a positive integer — the minimum number of packages.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733
```

### 输出

```
2
8
1
999999733
1
```



---

---
title: "Who's Opposite?"
layout: "post"
diff: 普及-
pid: CF1560B
tag: ['数学']
---

# Who's Opposite?

## 题目描述

Some number of people (this number is even) have stood in a circle. The people stand in the circle evenly. They are numbered clockwise starting from a person with the number $ 1 $ . Each person is looking through the circle's center at the opposite person.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560B/a3a7851777ae33a1527beddaa8761afd1adfcbd6.png)A sample of a circle of $ 6 $ persons. The orange arrows indicate who is looking at whom.You don't know the exact number of people standing in the circle (but this number is even, no doubt). It is known that the person with the number $ a $ is looking at the person with the number $ b $ (and vice versa, of course). What is the number associated with a person being looked at by the person with the number $ c $ ? If, for the specified $ a $ , $ b $ , and $ c $ , no such circle exists, output -1.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case consists of one line containing three distinct integers $ a $ , $ b $ , $ c $ ( $ 1 \le a,b,c \le 10^8 $ ).

## 输出格式

For each test case output in a separate line a single integer $ d $ — the number of the person being looked at by the person with the number $ c $ in a circle such that the person with the number $ a $ is looking at the person with the number $ b $ . If there are multiple solutions, print any of them. Output $ -1 $ if there's no circle meeting the given conditions.

## 说明/提示

In the first test case, there's a desired circle of $ 8 $ people. The person with the number $ 6 $ will look at the person with the number $ 2 $ and the person with the number $ 8 $ will look at the person with the number $ 4 $ .

In the second test case, there's no circle meeting the conditions. If the person with the number $ 2 $ is looking at the person with the number $ 3 $ , the circle consists of $ 2 $ people because these persons are neighbors. But, in this case, they must have the numbers $ 1 $ and $ 2 $ , but it doesn't meet the problem's conditions.

In the third test case, the only circle with the persons with the numbers $ 2 $ and $ 4 $ looking at each other consists of $ 4 $ people. Therefore, the person with the number $ 10 $ doesn't occur in the circle.

## 样例 #1

### 输入

```
7
6 2 4
2 3 1
2 4 10
5 3 4
1 3 2
2 5 4
4 3 2
```

### 输出

```
8
-1
-1
-1
4
1
-1
```



---

---
title: "Make it Divisible by 25"
layout: "post"
diff: 普及-
pid: CF1593B
tag: ['数学']
---

# Make it Divisible by 25

## 题目描述

给定一个**正整数** $n$，你可以对它进行操作。

对于每一次操作，你可以将这个正整数其中的**任意**一个数位删去，之后这个数剩下的左右两边会相接。

特别地：

- 如果一个数仅剩下一个数位，则不能再对它进行操作；
- 如果一个操作之后的数包含前导零，则这些前导零会被一并删除。

例如：

- 将 $32925$ 的第 $3$ 位删除后，它会变成 $3225$；
- 将 $20099050$ 的第 $1$ 位删除后，它会变成 $99050$（两个前导零被一并删除了）。

请你求出，最少经过多少次操作之后，可以得到一个能被 $25$ 整除的**正整数**。

## 输入格式

本题包含多组数据。

输入的第一行包含一个正整数 $t$，表示数据组数。

接下来 $t$ 行，每行一个正整数 $n$。

## 输出格式

对于每组数据，输出一行一个非负整数，表示答案。

## 说明/提示

- $1 \le t \le 10^4$；
- $25 \le n \le 10^{18}$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
5
100
71345
3259
50555
2050047
```

### 输出

```
0
3
1
3
2
```



---

---
title: "Make Even"
layout: "post"
diff: 普及-
pid: CF1611A
tag: ['字符串', '数学', '构造']
---

# Make Even

## 题目描述

Polycarp 有一个不包含数字 $0$ 的整数 $n$。他可以使用他的数字执行以下操作数次（可能为零）：

将 $n$ 的长度 $l\ (1 \leq l \leq |n|$，这里 $|n|$ 指 $n$ 的十进制长度 $)$ 的前缀反转，即反转 $n$ 的 前 $l$ 位数字。那么，第 $1$ 个数位（默认从左向右数，下文同理）将与第 $l$ 个数位交换，第 $2$ 个数位与第 $(l-1)$ 个交换......以此类推。

例如，如果 $n=123456789$ 且 $l=5$，则 $n$ 变换后的值将为 $543216789$。

对于不同的操作，$l$ 的值可能不同。

Polycarp 喜欢偶数，并且非常不耐烦。因此，他想用最少的操作次数使他的数字 $n$ 变成偶数。

**本题有多组数据。**

## 输入格式

第一行，一个整数 $t\ (1 \leq t \leq 10^4)$，表示数据的组数。

接下来 $t$ 行，每行一个数 $n\ (1 \leq n \leq 10^9)$。可以保证该数中各数位没有 $0$。

## 输出格式

共 $t$ 行，每行一个整数，表示将该数字变成偶数的最小操作次数。如果无论如何操作，都无法变为偶数，则输出 `-1`。

## 样例 #1

### 输入

```
4
3876
387
4489
3
```

### 输出

```
0
2
1
-1
```



---

---
title: "AvtoBus"
layout: "post"
diff: 普及-
pid: CF1679A
tag: ['数学']
---

# AvtoBus

## 题目描述

春天来了，车队的巴士需要更换轮胎。

轮胎有 $n$ 个，巴士有两种，第一种有 $4$ 个轮子，第二种有 $6$ 个。

求车队最少和最多有几辆巴士。

## 输入格式

第一行一个整数 $t$，表示测试数据的数量。

接下来 $t$ 行，每行一个整数 $n$，表示轮胎的总数。

## 输出格式

共 $t$ 行，每行两个整数，分别表示巴士数量的最小值和最大值。

若无解，输出 $-1$。

## 样例 #1

### 输入

```
4
4
7
24
998244353998244352
```

### 输出

```
1 1
-1
4 6
166374058999707392 249561088499561088
```



---

---
title: "Minimums and Maximums"
layout: "post"
diff: 普及-
pid: CF1680A
tag: ['数学']
---

# Minimums and Maximums

## 题目描述

LBW 想要一个数组，满足下面的条件：

- 设数组有 $n$ 个最小值，有 $n \in[l_1, r_1]$。

- 设数组有 $m$ 个最大值，有 $m \in[l_2, r_2]$。

LBW 比较吝啬，所以他希望数组元素个数尽可能少。

请帮助他求出这个最小值。

## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示有 $T$ 组数据。

对于每组数据，四个数，分别为 $l_1$，$r_1$，$l_2$，$r_2$。

## 输出格式

对于每组数据，输出一行，表示数组元素个数最小值。

## 说明/提示

$1 \le T \le 5000$

$1 \le l_1 \le r_1 \le 50$

$1 \le l_2 \le r_2 \le 50$

## 样例 #1

### 输入

```
7
3 5 4 6
5 8 5 5
3 3 10 12
1 5 3 3
1 1 2 2
2 2 1 1
6 6 6 6
```

### 输出

```
4
5
13
3
3
3
6
```



---

---
title: "Difference Operations"
layout: "post"
diff: 普及-
pid: CF1708A
tag: ['数学']
---

# Difference Operations

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers.

You are allowed to perform this operation any number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le n $ ), and change $ a_i $ to $ a_i - a_{i-1} $ .

Is it possible to make $ a_i=0 $ for all $ 2\le i\le n $ ?

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the length of array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

For each test case, print "YES" (without quotes), if it is possible to change $ a_i $ to $ 0 $ for all $ 2 \le i \le n $ , and "NO" (without quotes) otherwise.

You can print letters in any case (upper or lower).

## 说明/提示

In the first test case, the initial array is $ [5,10] $ . You can perform $ 2 $ operations to reach the goal:

1. Choose $ i=2 $ , and the array becomes $ [5,5] $ .
2. Choose $ i=2 $ , and the array becomes $ [5,0] $ .

In the second test case, the initial array is $ [1,2,3] $ . You can perform $ 4 $ operations to reach the goal:

1. Choose $ i=3 $ , and the array becomes $ [1,2,1] $ .
2. Choose $ i=2 $ , and the array becomes $ [1,1,1] $ .
3. Choose $ i=3 $ , and the array becomes $ [1,1,0] $ .
4. Choose $ i=2 $ , and the array becomes $ [1,0,0] $ .

In the third test case, you can choose indices in the order $ 4 $ , $ 3 $ , $ 2 $ .

## 样例 #1

### 输入

```
4
2
5 10
3
1 2 3
4
1 1 1 1
9
9 9 8 2 4 4 3 5 3
```

### 输出

```
YES
YES
YES
NO
```



---

---
title: "Traveling Salesman Problem"
layout: "post"
diff: 普及-
pid: CF1713A
tag: ['数学']
---

# Traveling Salesman Problem

## 题目描述

你正位于一个无限的笛卡尔坐标系的点 $ (x , y) $上，你可以进行四种操作：

- 向左移动至 $ (x - 1, y) $ 
- 向右移动至 $ (x + 1, y) $ 
- 向上移动至 $ (x, y + 1) $ 
- 向下移动至 $ (x, y - 1) $ 

有 $ n $ 个宝箱在这个平面上。 第 $ i $ 个 宝箱的坐标为 $ (x_i,y_i) $ . 保证每个宝箱都在 $ x $ 轴 或 $ y $ 轴上。即 $ x_i=0 $ 或 $ y_i=0 $。

你现在点 $ (0,0) $ 上，想将所有宝箱全部收入囊中，并回到原点。
你想知道你需要的最小移动次数是多少。
本题使用多组测试数据。

## 输入格式

第一行包含一个整数 $ t $（$ 1 \le t \le 100 $）— 测试组数

对于每一组数据，

第一行包含一个整数 $ n $（$ 1 \le n \le 100 $）— 宝箱数量

第 $ i+1 $ 行 $ n $ 包含两个整数 $ x_i $ 和 $ y_i $（$ -100 \le x_i, y_i \le 100 $）— 第 $i$ 个宝箱的坐标，保证 $ x_i=0 $ 或 $ y_i=0 $。

注意每一组数据的 $n$ 的和是无限制的

## 输出格式

共 $t$ 行，每行包含一个整数，即最小步数

## 样例 #1

### 输入

```
3
4
0 -2
1 0
-1 0
0 2
3
0 2
-3 0
0 -1
1
0 0
```

### 输出

```
12
12
0
```



---

---
title: "Deadly Laser"
layout: "post"
diff: 普及-
pid: CF1721B
tag: ['数学']
---

# Deadly Laser

## 题目描述

# Deadly Laser


The robot is placed in the top left corner of a grid, consisting of $ n $ rows and $ m $ columns, in a cell $ (1, 1) $ .

In one step, it can move into a cell, adjacent by a side to the current one:

- $ (x, y) \rightarrow (x, y + 1) $ ;
- $ (x, y) \rightarrow (x + 1, y) $ ;
- $ (x, y) \rightarrow (x, y - 1) $ ;
- $ (x, y) \rightarrow (x - 1, y) $ .

The robot can't move outside the grid.

The cell $ (s_x, s_y) $ contains a deadly laser. If the robot comes into some cell that has distance less than or equal to $ d $ to the laser, it gets evaporated. The distance between two cells $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ .

Print the smallest number of steps that the robot can take to reach the cell $ (n, m) $ without getting evaporated or moving outside the grid. If it's not possible to reach the cell $ (n, m) $ , print -1.

The laser is neither in the starting cell, nor in the ending cell. The starting cell always has distance greater than $ d $ to the laser.

有一个长$n$宽$m$的网格，一个机器人被放在此网格的左上角$(1,1)$。
每一步，机器人可以移动到与其所在格子相邻的四个格子：
- $(x,y) \rightarrow (x,y+1)$;
- $(x,y) \rightarrow (x+1,y)$;
- $(x,y) \rightarrow (x,y-1)$;
- $(x,y) \rightarrow (x-1,y)$。

机器人不能移出网格。\
在$(s_x,s_y)$处，放置着致命的激光。所有与激光所在格子的距离小于等于$d$的格子都不可通行。（$(x_1,y_1)$到$(x_2,y_2)$的距离为: $|x_1-x_2|+|y_1-y_2|$）\
输出机器人从$(1,1)$移至$(n,m)$的最小步数。如果机器人不能到达$(n,m)$，输出`-1`。

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The only line of each testcase contains five integers $ n, m, s_x, s_y, d $ ( $ 2 \le n, m \le 1000 $ ; $ 1 \le s_x \le n $ ; $ 1 \le s_y \le m $ ; $ 0 \le d \le n + m $ ) — the size of the grid, the cell that contains the laser and the evaporating distance of the laser.

The laser is neither in the starting cell, nor in the ending cell ( $ (s_x, s_y) \neq (1, 1) $ and $ (s_x, s_y) \neq (n, m) $ ). The starting cell $ (1, 1) $ always has distance greater than $ d $ to the laser ( $ |s_x - 1| + |s_y - 1| > d $ ).

第一行为一个整数$t$($1\leq t\leq 10^4$)，代表测试数据的数量。\
对于每一组测试数据，只有一行输入，包含5个整数：$n$, $m$, $s_x$, $s_y$, $d$ ($2\leq n,m\leq 1000$; $1\leq s_x \leq n$; $1\leq s_y \leq m$; $0\leq d\leq n+m$)，其意义与上方相同。\
输入数据保证激光既不在起点的格子，也不在终点的格子；保证起点的格子可以通行。（$(s_x,s_y)\neq(1,1)$; $(s_x,s_y)\neq(n,m)$; $|s_x-1|+|s_y-1|>d$）

## 输出格式

For each testcase, print a single integer. If it's possible to reach the cell $ (n, m) $ from $ (1, 1) $ without getting evaporated or moving outside the grid, then print the smallest amount of steps it can take the robot to reach it. Otherwise, print -1.

# 中文翻译
对于每组测试数据，输出一个整数。如果机器人可以达到终点，输出到达终点所需的最小步数。否则，输出`-1`

## 输入输出样例
### 样例输入
```
3
2 3 1 3 0
2 3 1 3 1
5 5 3 4 1
```
### 样例输出
```
3
-1
8
```

## 样例 #1

### 输入

```
3
2 3 1 3 0
2 3 1 3 1
5 5 3 4 1
```

### 输出

```
3
-1
8
```



---

---
title: "Kill Demodogs"
layout: "post"
diff: 普及-
pid: CF1731B
tag: ['数学', '贪心']
---

# Kill Demodogs

## 题目描述

给定一个数$n$,表示有一个 $n \times n$ 的方格。每个格子里都有一个数，第 $i$ 行第 $j$ 列的格子值为 $i⋅j$。现在Hawkins要从 $(1,1)$ 走到 $(n,n)$,每次只能从 $(i,j)$ 走到 $(i,j+1)$ 或 $(i+1,j)$, 每走到一个格子就能获得格子中的一个数，最大化数字之和。

## 输入格式

每个测试点包含多个测试样例。第一行包含测试样例的数量 $t$, 接下来 $t$ 行每行一个数 $n$。表示有 $n$ 行和 $n$ 列。

## 输出格式

共 $t$ 行，每行一个数，表所经过的格子乘 2022 后除以 $10^9 + 7$ 的余数。

## 样例 #1

### 输入

```
4
2
3
50
1000000000
```

### 输出

```
14154
44484
171010650
999589541
```



---

---
title: "Even-Odd Increments"
layout: "post"
diff: 普及-
pid: CF1744B
tag: ['模拟', '数学']
---

# Even-Odd Increments

## 题目描述

You are given $ n $ of integers $ a_1, a_2, \ldots, a_n $ . Process $ q $ queries of two types:

- query of the form "0 $ x_j $ ": add the value $ x_j $ to all even elements of the array $ a $ ,
- query of the form "1 $ x_j $ ": add the value $ x_j $ to all odd elements of the array $ a $ .

Note that when processing the query, we look specifically at the odd/even value of $ a_i $ , not its index.

After processing each query, print the sum of the elements of the array $ a $ .

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 输入格式

The first line of the input contains an integer $ t $ $ (1 \leq t \leq 10^4 $ ) — the number of test cases.

The descriptions of the test cases follow.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n $ , $ q \leq 10^5 $ ) — the length of array $ a $ and the number of queries.

The second line of each test case contains exactly $ n $ integers: $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — elements of the array $ a $ .

The following $ q $ lines contain queries as two integers $ type_j $ and $ x_j $ $ (0 \leq type_j \leq 1 $ , $ 1 \leq x_j \leq 10^4 $ ).

It is guaranteed that the sum of values $ n $ over all test cases in a test does not exceed $ 10^5 $ . Similarly, the sum of values $ q $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print $ q $ numbers: the sum of the elements of the array $ a $ after processing a query.

## 说明/提示

In the first test case, the array $ a = [2] $ after the first query.

In the third test case, the array $ a $ is modified as follows: $ [1, 3, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [10, 12, 10, 12, 18, 56] $ $ \rightarrow $ $ [22, 24, 22, 24, 30, 68] $ $ \rightarrow $ $ [23, 25, 23, 25, 31, 69] $ .

## 样例 #1

### 输入

```
4
1 1
1
1 1
3 3
1 2 4
0 2
1 3
0 5
6 7
1 3 2 4 10 48
1 6
0 5
0 4
0 5
1 3
0 12
0 1
6 7
1000000000 1000000000 1000000000 11 15 17
0 17
1 10000
1 51
0 92
0 53
1 16
0 1
```

### 输出

```
2
11
14
29
80
100
100
100
118
190
196
3000000094
3000060094
3000060400
3000060952
3000061270
3000061366
3000061366
```



---

---
title: "Doremy's Perfect Math Class"
layout: "post"
diff: 普及-
pid: CF1764B
tag: ['数学', '数论']
---

# Doremy's Perfect Math Class

## 题目描述

"Everybody! Doremy's Perfect Math Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's math class, Doremy is teaching everyone subtraction. Now she gives you a quiz to prove that you are paying attention in class.

You are given a set $ S $ containing positive integers. You may perform the following operation some (possibly zero) number of times:

- choose two integers $ x $ and $ y $ from the set $ S $ such that $ x > y $ and $ x - y $ is not in the set $ S $ .
- add $ x-y $ into the set $ S $ .

You need to tell Doremy the maximum possible number of integers in $ S $ if the operations are performed optimally. It can be proven that this number is finite.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line contains an integer $ n $ ( $ 2 \le n\le 10^5 $ ) — the size of the set $ S $ .

The second line contains $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1\le a_1 < a_2 < \cdots < a_n \le 10^9 $ ) — the positive integers in $ S $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, you need to output the maximum possible number of integers in $ S $ . It can be proven that this value is finite.

## 说明/提示

In the first test case, no such $ x $ and $ y $ exist. The maximum possible number of integers in $ S $ is $ 2 $ .

In the second test case,

- $ S=\{5,10,25\} $ at first. You can choose $ x=25 $ , $ y=10 $ , then add $ x-y=15 $ to the set.
- $ S=\{5,10,15,25\} $ now. You can choose $ x=25 $ , $ y=5 $ , then add $ x-y=20 $ to the set.
- $ S=\{5,10,15,20,25\} $ now. You can not perform any operation now.

After performing all operations, the number of integers in $ S $ is $ 5 $ . It can be proven that no other sequence of operations allows $ S $ to contain more than $ 5 $ integers.

## 样例 #1

### 输入

```
2
2
1 2
3
5 10 25
```

### 输出

```
2
5
```



---

---
title: "Permutation Printing"
layout: "post"
diff: 普及-
pid: CF1930B
tag: ['数学', '构造']
---

# Permutation Printing

## 题目描述

You are given a positive integer $ n $ .

Find a permutation $ ^\dagger $ $ p $ of length $ n $ such that there do not exist two distinct indices $ i $ and $ j $ ( $ 1 \leq i, j < n $ ; $ i \neq j $ ) such that $ p_i $ divides $ p_j $ and $ p_{i+1} $ divides $ p_{j+1} $ .

Refer to the Notes section for some examples.

Under the constraints of this problem, it can be proven that at least one $ p $ exists.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^5 $ ) — the length of the permutation $ p $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ p_1, p_2, \ldots, p_n $ .

If there are multiple solutions, you may output any one of them.

## 说明/提示

In the first test case, $ p=[4,1,2,3] $ is a valid permutation. However, the permutation $ p=[1,2,3,4] $ is not a valid permutation as we can choose $ i=1 $ and $ j=3 $ . Then $ p_1=1 $ divides $ p_3=3 $ and $ p_2=2 $ divides $ p_4=4 $ . Note that the permutation $ p=[3, 4, 2, 1] $ is also not a valid permutation as we can choose $ i=3 $ and $ j=2 $ . Then $ p_3=2 $ divides $ p_2=4 $ and $ p_4=1 $ divides $ p_3=2 $ .

In the second test case, $ p=[1,2,3] $ is a valid permutation. In fact, all $ 6 $ permutations of length $ 3 $ are valid.

## 样例 #1

### 输入

```
2
4
3
```

### 输出

```
4 1 2 3
1 2 3
```



---

---
title: "Turtle Math: Fast Three Task"
layout: "post"
diff: 普及-
pid: CF1933B
tag: ['数学']
---

# Turtle Math: Fast Three Task

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ .

In one move, you can perform either of the following two operations:

- Choose an element from the array and remove it from the array. As a result, the length of the array decreases by $ 1 $ ;
- Choose an element from the array and increase its value by $ 1 $ .

You can perform any number of moves. If the current array becomes empty, then no more moves can be made.

Your task is to find the minimum number of moves required to make the sum of the elements of the array $ a $ divisible by $ 3 $ . It is possible that you may need $ 0 $ moves.

Note that the sum of the elements of an empty array (an array of length $ 0 $ ) is equal to $ 0 $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^4 $ ).

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the minimum number of moves.

## 说明/提示

In the first test case, initially the array $ a = [2, 2, 5, 4] $ . One of the optimal ways to make moves is:

- remove the current $ 4 $ th element and get $ a = [2, 2, 5] $ ;

 As a result, the sum of the elements of the array $ a $ will be divisible by $ 3 $ (indeed, $ a_1 + a_2 + a_3 = 2 + 2 + 5 = 9 $ ).In the second test case, initially, the sum of the array is $ 1+3+2 = 6 $ , which is divisible by $ 3 $ . Therefore, no moves are required. Hence, the answer is $ 0 $ .

In the fourth test case, initially, the sum of the array is $ 1 $ , which is not divisible by $ 3 $ . By removing its only element, you will get an empty array, so its sum is $ 0 $ . Hence, the answer is $ 1 $ .

## 样例 #1

### 输入

```
8
4
2 2 5 4
3
1 3 2
4
3 7 6 8
1
1
4
2 2 4 2
2
5 5
7
2 4 8 1 9 3 4
2
4 10
```

### 输出

```
1
0
0
1
1
2
1
1
```



---

---
title: "Yet Another Coin Problem"
layout: "post"
diff: 普及-
pid: CF1934B
tag: ['数学', '贪心']
---

# Yet Another Coin Problem

## 题目描述

You have $ 5 $ different types of coins, each with a value equal to one of the first $ 5 $ triangular numbers: $ 1 $ , $ 3 $ , $ 6 $ , $ 10 $ , and $ 15 $ . These coin types are available in abundance. Your goal is to find the minimum number of these coins required such that their total value sums up to exactly $ n $ .

We can show that the answer always exists.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 10^9 $ ) — the target value.

## 输出格式

For each test case, output a single number — the minimum number of coins required.

## 说明/提示

In the first test case, for $ n = 1 $ , the answer is $ 1 $ since only one $ 1 $ value coin is sufficient. $ 1 = 1 \cdot 1 $ .

In the fourth test case, for $ n = 5 $ , the answer is $ 3 $ , which can be achieved using two $ 1 $ value coins and one $ 3 $ value coin. $ 5 = 2 \cdot 1 + 1 \cdot 3 $ .

In the seventh test case, for $ n = 12 $ , the answer is $ 2 $ , which can be achieved using two $ 6 $ value coins.

In the ninth test case, for $ n = 16 $ , the answer is $ 2 $ , which can be achieved using one $ 1 $ value coin and one $ 15 $ value coin or using one $ 10 $ value coin and one $ 6 $ value coin. $ 16 = 1 \cdot 1 + 1 \cdot 15 = 1 \cdot 6 + 1 \cdot 10 $ .

## 样例 #1

### 输入

```
14
1
2
3
5
7
11
12
14
16
17
18
20
98
402931328
```

### 输出

```
1
2
1
3
2
2
2
3
2
3
2
2
8
26862090
```



---

---
title: "Shuffle Party"
layout: "post"
diff: 普及-
pid: CF1937A
tag: ['数学']
---

# Shuffle Party

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ . Initially, $ a_i=i $ for each $ 1 \le i \le n $ .

The operation $ \texttt{swap}(k) $ for an integer $ k \ge 2 $ is defined as follows:

- Let $ d $ be the largest divisor $ ^\dagger $ of $ k $ which is not equal to $ k $ itself. Then swap the elements $ a_d $ and $ a_k $ .

Suppose you perform $ \texttt{swap}(i) $ for each $ i=2,3,\ldots, n $ in this exact order. Find the position of $ 1 $ in the resulting array. In other words, find such $ j $ that $ a_j = 1 $ after performing these operations.

 $ ^\dagger $ An integer $ x $ is a divisor of $ y $ if there exists an integer $ z $ such that $ y = x \cdot z $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^9 $ ) — the length of the array $ a $ .

## 输出格式

For each test case, output the position of $ 1 $ in the resulting array.

## 说明/提示

In the first test case, the array is $ [1] $ and there are no operations performed.

In the second test case, $ a $ changes as follows:

- Initially, $ a $ is $ [1,2,3,4] $ .
- After performing $ \texttt{swap}(2) $ , $ a $ changes to $ [\underline{2},\underline{1},3,4] $ (the elements being swapped are underlined).
- After performing $ \texttt{swap}(3) $ , $ a $ changes to $ [\underline{3},1,\underline{2},4] $ .
- After performing $ \texttt{swap}(4) $ , $ a $ changes to $ [3,\underline{4},2,\underline{1}] $ .

Finally, the element $ 1 $ lies on index $ 4 $ (that is, $ a_4 = 1 $ ). Thus, the answer is $ 4 $ .

## 样例 #1

### 输入

```
4
1
4
5
120240229
```

### 输出

```
1
4
4
67108864
```



---

---
title: "Farmer John's Challenge"
layout: "post"
diff: 普及-
pid: CF1942A
tag: ['数学']
---

# Farmer John's Challenge

## 题目描述

[Trade Winds - Patrick Deng](https://soundcloud.com/patrick-deng-392681004/trade-winds-ft-alex-zhu)

⠀



Let's call an array $ a $ sorted if $ a_1 \leq a_2 \leq \ldots \leq a_{n - 1} \leq a_{n} $ .

You are given two of Farmer John's favorite integers, $ n $ and $ k $ . He challenges you to find any array $ a_1, a_2, \ldots, a_{n} $ satisfying the following requirements:

- $ 1 \leq a_i \leq 10^9 $ for each $ 1 \leq i \leq n $ ;
- Out of the $ n $ total cyclic shifts of $ a $ , exactly $ k $ of them are sorted. $ ^\dagger $

If there is no such array $ a $ , output $ -1 $ .

 $ ^\dagger $ The $ x $ -th ( $ 1 \leq x \leq n $ ) cyclic shift of the array $ a $ is $ a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1} $ . If $ c_{x, i} $ denotes the $ i $ 'th element of the $ x $ 'th cyclic shift of $ a $ , exactly $ k $ such $ x $ should satisfy $ c_{x,1} \leq c_{x,2} \leq \ldots \leq c_{x, n - 1} \leq c_{x, n} $ .

For example, the cyclic shifts for $ a = [1, 2, 3, 3] $ are the following:

- $ x = 1 $ : $ [1, 2, 3, 3] $ (sorted);
- $ x = 2 $ : $ [2, 3, 3, 1] $ (not sorted);
- $ x = 3 $ : $ [3, 3, 1, 2] $ (not sorted);
- $ x = 4 $ : $ [3, 1, 2, 3] $ (not sorted).

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

Each test case contains two integers $ n $ and $ k $ ( $ 1 \leq k \leq n \leq 10^3 $ ) — the length of $ a $ and the number of sorted cyclic shifts $ a $ must have.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^3 $ .

## 输出格式

For each test case, print a single line:

- if there is a valid array $ a $ , output $ n $ integers, representing $ a_1, a_2, \ldots, a_{n} $ ;
- otherwise, output $ -1 $ .

If there are multiple solutions, print any of them.

## 说明/提示

In the first testcase, $ a = [1, 1] $ satisfies $ n = 2, k = 2 $ :

The two cyclic shifts of $ a $ are $ [a_1, a_2] $ and $ [a_2, a_1] $ , which are both $ [1, 1] $ and are sorted.

In the second testcase, $ a = [69\,420, 69, 420] $ satisfies $ n = 3, k = 1 $ :

The three cyclic shifts of $ a $ are $ [a_1, a_2, a_3] $ , $ [a_2, a_3, a_1] $ , $ [a_3, a_1, a_2] $ , which are $ [69\,420, 69, 420] $ , $ [69, 420, 69\,420] $ , and $ [420, 69\,420, 69] $ , respectively.

Only $ [69, 420, 69\,420] $ is sorted.

## 样例 #1

### 输入

```
3
2 2
3 1
3 2
```

### 输出

```
1 1
69420 69 420
-1
```



---

---
title: "Bessie and MEX"
layout: "post"
diff: 普及-
pid: CF1942B
tag: ['数学']
---

# Bessie and MEX

## 题目描述

[MOOO! - Doja Cat](https://soundcloud.com/amalaofficial/mooo)

⠀



Farmer John has a permutation $ p_1, p_2, \ldots, p_n $ , where every integer from $ 0 $ to $ n-1 $ occurs exactly once. He gives Bessie an array $ a $ of length $ n $ and challenges her to construct $ p $ based on $ a $ .

The array $ a $ is constructed so that $ a_i $ = $ \texttt{MEX}(p_1, p_2, \ldots, p_i) - p_i $ , where the $ \texttt{MEX} $ of an array is the minimum non-negative integer that does not appear in that array. For example, $ \texttt{MEX}(1, 2, 3) = 0 $ and $ \texttt{MEX}(3, 1, 0) = 2 $ .

Help Bessie construct any valid permutation $ p $ that satisfies $ a $ . The input is given in such a way that at least one valid $ p $ exists. If there are multiple possible $ p $ , it is enough to print one of them.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the lengths of $ p $ and $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -n \leq a_i \leq n $ ) — the elements of array $ a $ .

It is guaranteed that there is at least one valid $ p $ for the given data.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers on a new line, the elements of $ p $ .

If there are multiple solutions, print any of them.

## 说明/提示

In the first case, $ p = [0, 1, 4, 2, 3] $ is one possible output.

 $ a $ will then be calculated as $ a_1 = \texttt{MEX}(0) - 0 = 1 $ , $ a_2 = \texttt{MEX}(0, 1) - 1 = 1 $ , $ a_3 = \texttt{MEX}(0, 1, 4) - 4 = -2 $ , $ a_4 = \texttt{MEX}(0, 1, 4, 2) - 2 = 1 $ , $ a_5 = \texttt{MEX}(0, 1, 4, 2, 3) - 3 = 2 $ .

So, as required, $ a $ will be $ [1, 1, -2, 1, 2] $ .

## 样例 #1

### 输入

```
3
5
1 1 -2 1 2
5
1 1 1 1 1
3
-2 1 2
```

### 输出

```
0 1 4 2 3 
0 1 2 3 4 
2 0 1
```



---

---
title: "Bessie's Birthday Cake (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1942C1
tag: ['数学']
---

# Bessie's Birthday Cake (Easy Version)

## 题目描述

[Proof Geometric Construction Can Solve All Love Affairs - manbo-p](https://soundcloud.com/alice-law-314125270/manbo-p-proof-geometric-construction-can-solve-all-love-affairs)

⠀



This is the easy version of the problem. The only difference between the two versions is the constraint on $ y $ . In this version $ y = 0 $ . You can make hacks only if both versions are solved.

Bessie has received a birthday cake from her best friend Elsie, and it came in the form of a regular polygon with $ n $ sides. The vertices of the cake are numbered from $ 1 $ to $ n $ clockwise. You and Bessie are going to choose some of those vertices to cut non-intersecting diagonals into the cake. In other words, the endpoints of the diagonals must be part of the chosen vertices.

Bessie would only like to give out pieces of cake which result in a triangle to keep consistency. The size of the pieces doesn't matter, and the whole cake does not have to be separated into all triangles (other shapes are allowed in the cake, but those will not be counted).

Bessie has already chosen $ x $ of those vertices that can be used to form diagonals. She wants you to choose no more than $ y $ other vertices such that the number of triangular pieces of cake she can give out is maximized.

What is the maximum number of triangular pieces of cake Bessie can give out?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers, $ n $ , $ x $ , and $ y $ ( $ 4 \leq n \leq 10^9 $ , $ 2 \leq x \leq \min(n, 2 \cdot 10^5) $ , $ y = 0 $ ) — the number of sides of the polygon, number of vertices Bessie has chosen, and the maximum number of other vertices you can choose.

The second line consists of $ x $ distinct integers from $ 1 $ to $ n $ , representing the vertices Bessie has chosen.

It is guaranteed the sum of $ x $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum number of non-intersecting triangular pieces of cake she can give out.

## 说明/提示

In test cases $ 1 $ , $ 2 $ and $ 3 $ , you can get $ 2 $ , $ 6 $ and $ 2 $ non-intersecting triangular pieces of cake, respectively. A possible construction is shown in the following pictures:

The green dots represent vertices that can be used, the blue lines represent diagonals that are drawn, and the red numbers represent triangles that are counted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1942C1/a4f3a6e3efd4b2b24052c536629245c4fd02196b.png)

## 样例 #1

### 输入

```
3
8 4 0
1 6 2 5
8 8 0
1 3 2 5 4 6 7 8
4 2 0
1 3
```

### 输出

```
2
6
2
```



---

---
title: "Fireworks"
layout: "post"
diff: 普及-
pid: CF1945B
tag: ['数学']
---

# Fireworks

## 题目描述

One of the days of the hike coincided with a holiday, so in the evening at the camp, it was decided to arrange a festive fireworks display. For this purpose, the organizers of the hike bought two installations for launching fireworks and a huge number of shells for launching.

Both installations are turned on simultaneously. The first installation launches fireworks every $ a $ minutes (i.e., after $ a, 2 \cdot a, 3 \cdot a, \dots $ minutes after launch). The second installation launches fireworks every $ b $ minutes (i.e., after $ b, 2 \cdot b, 3 \cdot b, \dots $ minutes after launch).

Each firework is visible in the sky for $ m + 1 $ minutes after launch, i.e., if a firework was launched after $ x $ minutes after the installations were turned on, it will be visible every minute from $ x $ to $ x + m $ , inclusive. If one firework was launched $ m $ minutes after another, both fireworks will be visible for one minute.

What is the maximum number of fireworks that could be seen in the sky at the same time?

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follow the descriptions of the test cases.

The first and only line of each test case contains integers $ a $ , $ b $ , $ m $ ( $ 1 \le a, b, m \le 10^{18} $ ) — the frequency of launching for the first installation, the second installation, and the time the firework is visible in the sky.

## 输出格式

For each set of input data, output a single number — the maximum number of fireworks that can be seen simultaneously.

## 说明/提示

In the first set of input data, the fireworks are visible in the sky for $ 5 $ minutes. Since the first installation launches fireworks every $ 6 $ minutes, and the second one every $ 7 $ minutes, two fireworks launched from the same installation will not be visible in the sky at the same time. At the same time, after $ 7 $ minutes from the start of the holiday, one firework from the first and one from the second camp will be visible. Thus, it is possible to see no more than $ 2 $ fireworks simultaneously.

In the third set of input data, $ 17 $ fireworks will be visible after $ 112 $ minutes:

- $ 9 $ fireworks launched from the first installation at times \[ $ 56, 63, 70, 77, 84, 91, 98, 105, 112 $ \];
- $ 8 $ fireworks launched from the second installation at times \[ $ 56, 64, 72, 80, 88, 96, 104, 112 $ \].

## 样例 #1

### 输入

```
6
6 7 4
3 4 10
7 8 56
5 6 78123459896
1 1 1
1 1 1000000000000000000
```

### 输出

```
2
7
17
28645268630
4
2000000000000000002
```



---

---
title: "Dual Trigger"
layout: "post"
diff: 普及-
pid: CF1951A
tag: ['数学']
---

# Dual Trigger

## 题目描述

[Ngọt - LẦN CUỐI (đi bên em xót xa người ơi)](https://youtu.be/kSjj0LlsqnI)

ඞ



There are $ n $ lamps numbered $ 1 $ to $ n $ lined up in a row, initially turned off. You can perform the following operation any number of times (possibly zero):

- Choose two non-adjacent $ {}^\dagger $ lamps that are currently turned off, then turn them on.

Determine whether you can reach configuration $ s $ , where $ s_i = 1 $ means the $ i $ -th lamp is turned on, and $ s_i = 0 $ otherwise.

 $ {}^\dagger $ Only lamp $ i $ and $ i + 1 $ are adjacent for all $ 1 \le i < n $ . Note that lamp $ n $ and $ 1 $ are not adjacent when $ n \ne 2 $ .

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 50 $ ) — the number of lamps.

The second line of each test case contains a binary string $ s $ of size $ n $ — the final desired configuration.

## 输出格式

For each test case, print on one line "YES" if we can reach the configuration $ s $ via applying the given operation any number of times. Otherwise, print "NO".

## 说明/提示

In the first test case, the sequence of operation could have been as follows (note that initially $ s $ is all zero): $ \mathtt{0000000000} \to \mathtt{\color{red}{1}0000000\color{red}{1}0} \to \mathtt{1\color{red}{1}00000\color{red}{1}10} \to \mathtt{110\color{red}{1}0\color{red}{1}0110} $ .

In the third test case, we don't have to do any operation.

In the fourth test case, we cannot do any operation, but we need the first lamp to be on. Therefore, it is impossible to achieve the desired state.

## 样例 #1

### 输入

```
5
10
1101010110
10
1001001110
6
000000
1
1
12
111111111111
```

### 输出

```
YES
NO
YES
NO
YES
```



---

---
title: "Painting the Ribbon"
layout: "post"
diff: 普及-
pid: CF1954A
tag: ['数学']
---

# Painting the Ribbon

## 题目描述

Alice and Bob have bought a ribbon consisting of $ n $ parts. Now they want to paint it.

First, Alice will paint every part of the ribbon into one of $ m $ colors. For each part, she can choose its color arbitrarily.

Then, Bob will choose at most $ k $  parts of the ribbon and repaint them into the same color (he chooses the affected parts and the color arbitrarily).

Bob would like all parts to have the same color. However, Alice thinks that this is too dull, so she wants to paint the ribbon in such a way that Bob cannot make all parts have the same color.

Is it possible to paint the ribbon in such a way?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of one line containing three integers $ n $ , $ m $ and $ k $ ( $ 1 \le m, k \le n \le 50 $ ) — the number of parts, the number of colors and the number of parts Bob can repaint, respectively.

## 输出格式

For each test case, print YES if Alice can paint the ribbon so that Bob cannot make all parts have the same color. Otherwise, print NO.

You can print every letter in any register. For example, Yes, yes, yEs will all be recognized as positive answer.

## 说明/提示

In the first test case, a ribbon consists of $ 1 $ part. So all its parts will always have the same color.

In the second test case, there is only $ 1 $ color.

In the third test case, Alice can paint the ribbon as follows: $ [1, 2, 1, 2, 1] $ . It's impossible to change the color of at most $ 1 $ part so that all parts have the same color.

In the fourth test case, no matter how Alice paints the ribbon, Bob will always be able to repaint $ 2 $ parts so that all parts have the same color.

In the fifth test case, Alice can paint the ribbon as follows: $ [1, 2, 3, 4, 5] $ . It's impossible to change the color of at most $ 3 $ parts so that all parts have the same color.

## 样例 #1

### 输入

```
5
1 1 1
5 1 1
5 2 1
5 2 2
5 5 3
```

### 输出

```
NO
NO
YES
NO
YES
```



---

---
title: "Make It Ugly"
layout: "post"
diff: 普及-
pid: CF1954B
tag: ['数学']
---

# Make It Ugly

## 题目描述

Let's call an array $ a $ beautiful if you can make all its elements the same by using the following operation an arbitrary number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le |a| - 1 $ ) such that $ a_{i - 1} = a_{i + 1} $ , and replace $ a_i $ with $ a_{i - 1} $ .

You are given a beautiful array $ a_1, a_2, \dots, a_n $ . What is the minimum number of elements you have to remove from it in order for it to stop being beautiful? Swapping elements is prohibited. If it is impossible to do so, then output -1.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Additional constraints on the input:

- in every test case, the given array $ a $ is beautiful;
- the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of elements you have to remove from the array $ a $ in order for it to stop being beautiful. If it is impossible, then output -1.

## 说明/提示

In the first testcase, it is impossible to modify the array in such a way that it stops being beautiful. An array consisting of identical numbers will remain beautiful no matter how many numbers we remove from it.

In the second testcase, you can remove the number at the index $ 5 $ , for example.

The resulting array will be $ [1, 2, 1, 2] $ . Let's check if it is beautiful. Two operations are available:

- Choose $ i = 2 $ : the array becomes $ [1, 1, 1, 2] $ . No more operations can be applied to it, and the numbers are not all the same.
- Choose $ i = 3 $ instead: the array becomes $ [1, 2, 2, 2] $ . No more operations can be applied to it either, and the numbers are still not all the same.

Thus, the array $ [1, 2, 1, 2] $ is not beautiful.

In the fourth testcase, you can remove the first three elements, for example. The resulting array $ [5, 3, 3, 3] $ is not beautiful.

## 样例 #1

### 输入

```
4
3
2 2 2
5
1 2 1 2 1
1
1
7
3 3 3 5 3 3 3
```

### 输出

```
-1
1
-1
3
```



---

---
title: "Stickogon"
layout: "post"
diff: 普及-
pid: CF1957A
tag: ['数学']
---

# Stickogon

## 题目描述

给定 $n$ 个木棍，第 $i$ 个长度为 $a_i$。

你需要保证：

* 构成的任意多边形每一边由一根木棍构成。

* 没有木棍用于多个多边形的边。

求通过这些木棍同时能构造的**正**多边形数量。

注：不可以破坏木棍。

## 输入格式

第一行一个整数 $t$，表示数据组数。

接下来对于每组数据，第一行一个整数 $n$。

接下来 $n$ 个整数，表示 $a_i$。

## 输出格式

共 $t$ 行，每行一个整数，表示答案。

## 说明/提示

对于第一组数据，显然一根木棍无法构造多边形。

对于第二组数据，显然两根木棍也无法构造多边形。

对于第三组数据，可以用四根长度为 $3$ 的木棍构造一个正方形。

对于第四组数据，可以用五根长度为 $2$ 的木棍构造一个五边形，然后用四根长度为 $4$ 的木棍构造一个正方形。


对于全部数据，满足 $1\le t,n,a_i\le100$。

## 样例 #1

### 输入

```
4
1
1
2
1 1
6
2 2 3 3 3 3
9
4 2 2 2 2 4 2 4 4
```

### 输出

```
0
0
1
2
```



---

---
title: "Maximize?"
layout: "post"
diff: 普及-
pid: CF1968A
tag: ['数学']
---

# Maximize?

## 题目描述

You are given an integer $ x $ . Your task is to find any integer $ y $ $ (1\le y<x) $ such that $ \gcd(x,y)+y $ is maximum possible.

Note that if there is more than one $ y $ which satisfies the statement, you are allowed to find any.

 $ \gcd(a,b) $ is the Greatest Common Divisor of $ a $ and $ b $ . For example, $ \gcd(6,4)=2 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each of the following $ t $ lines contains a single integer $ x $ ( $ 2 \le x \le 1000 $ ).

## 输出格式

For each test case, output any $ y $ ( $ 1 \le y < x $ ), which satisfies the statement.

## 样例 #1

### 输入

```
7
10
7
21
100
2
1000
6
```

### 输出

```
5
6
18
98
1
750
3
```



---

---
title: "Assembly via Remainders"
layout: "post"
diff: 普及-
pid: CF1968C
tag: ['数学']
---

# Assembly via Remainders

## 题目描述

You are given an array $ x_2,x_3,\dots,x_n $ . Your task is to find any array $ a_1,\dots,a_n $ , where:

- $ 1\le a_i\le 10^9 $ for all $ 1\le i\le n $ .
- $ x_i=a_i \bmod a_{i-1} $ for all $ 2\le i\le n $ .

Here $ c\bmod d $ denotes the remainder of the division of the integer $ c $ by the integer $ d $ . For example $ 5 \bmod 2 = 1 $ , $ 72 \bmod 3 = 0 $ , $ 143 \bmod 14 = 3 $ .

Note that if there is more than one $ a $ which satisfies the statement, you are allowed to find any.

## 输入格式

The first line contains a single integer $ t $ $ (1\le t\le 10^4) $ — the number of test cases.

The first line of each test case contains a single integer $ n $ $ (2\le n\le 500) $ — the number of elements in $ a $ .

The second line of each test case contains $ n-1 $ integers $ x_2,\dots,x_n $ $ (1\le x_i\le 500) $ — the elements of $ x $ .

It is guaranteed that the sum of values $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output any $ a_1,\dots,a_n $ ( $ 1 \le a_i \le 10^9 $ ) which satisfies the statement.

## 说明/提示

In the first test case $ a=[3,5,4,9] $ satisfies the conditions, because:

- $ a_2\bmod a_1=5\bmod 3=2=x_2 $ ;
- $ a_3\bmod a_2=4\bmod 5=4=x_3 $ ;
- $ a_4\bmod a_3=9\bmod 4=1=x_4 $ ;

## 样例 #1

### 输入

```
5
4
2 4 1
3
1 1
6
4 2 5 1 2
2
500
3
1 5
```

### 输出

```
3 5 4 9
2 5 11
5 14 16 5 11 24
501 500
2 7 5
```



---

---
title: "Chess For Three"
layout: "post"
diff: 普及-
pid: CF1973A
tag: ['数学']
---

# Chess For Three

## 题目描述

Three friends gathered to play a few games of chess together.

In every game, two of them play against each other. The winner gets $ 2 $ points while the loser gets $ 0 $ , and in case of a draw, both players get $ 1 $ point each. Note that the same pair of players could have played any non-negative number of times (possibly zero). It is also possible that no games were played at all.

You've been told that their scores after all the games were played were $ p_1 $ , $ p_2 $ and $ p_3 $ . Additionally, it is guaranteed that $ p_1 \leq p_2 \leq p_3 $ holds.

Find the maximum number of draws that could have happened and print it. If there isn't any way to obtain $ p_1 $ , $ p_2 $ and $ p_3 $ as a result of a non-negative number of games between the three players, print $ -1 $ instead.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ p_1 $ , $ p_2 $ and $ p_3 $ ( $ 0 \leq p_1 \leq p_2 \leq p_3 \leq 30 $ ) — the scores of the three players, sorted non-decreasingly.

## 输出格式

For each testcase, print one number — the maximum possible number of draws that could've happened, or $ -1 $ if the scores aren't consistent with any valid set of games and results.

## 说明/提示

In the first example, no games were played at all, so no draws could occur either.

For the second example, exactly one game occurred between the second and the third player and it ended in draw, so the answer is $ 1 $ .

It's easy to see that there's no set of games achieving the scores in third example, so the answer for it is $ -1 $ .

## 样例 #1

### 输入

```
7
0 0 0
0 1 1
1 1 1
1 1 2
3 3 3
3 4 5
1 1 10
```

### 输出

```
0
1
-1
2
-1
6
2
```



---

---
title: "Phone Desktop"
layout: "post"
diff: 普及-
pid: CF1974A
tag: ['数学']
---

# Phone Desktop

## 题目描述

Little Rosie has a phone with a desktop (or launcher, as it is also called). The desktop can consist of several screens. Each screen is represented as a grid of size $ 5 \times 3 $ , i.e., five rows and three columns.

There are $ x $ applications with an icon size of $ 1 \times 1 $ cells; such an icon occupies only one cell of the screen. There are also $ y $ applications with an icon size of $ 2 \times 2 $ cells; such an icon occupies a square of $ 4 $ cells on the screen. Each cell of each screen can be occupied by no more than one icon.

Rosie wants to place the application icons on the minimum number of screens. Help her find the minimum number of screens needed.

## 输入格式

The first line of the input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two integers $ x $ and $ y $ ( $ 0 \leq x, y \leq 99 $ ) — the number of applications with a $ 1 \times 1 $ icon and the number of applications with a $ 2 \times 2 $ icon, respectively.

## 输出格式

For each test case, output the minimal number of required screens on a separate line.

## 说明/提示

The solution for the first test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/50fee263eb8faff81a1a0ba84255a68bc5871ae1.png) Blue squares represent empty spaces for icons, green squares represent $ 1 \times 1 $ icons, red squares represent $ 2 \times 2 $ iconsThe solution for the third test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/53e483ebe35e12a51af69c31e4cb0b1e5b05aee6.png)

## 样例 #1

### 输入

```
11
1 1
7 2
12 4
0 3
1 0
8 1
0 0
2 0
15 0
8 2
0 9
```

### 输出

```
1
1
2
2
1
1
0
1
1
2
5
```



---

---
title: "378QAQ and Mocha's Array"
layout: "post"
diff: 普及-
pid: CF1975B
tag: ['数学']
---

# 378QAQ and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, 378QAQ gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Mocha thinks that $ a $ is beautiful if there exist two numbers $ i $ and $ j $ ( $ 1\leq i,j\leq n $ , $ i\neq j $ ) such that for all $ k $ ( $ 1 \leq k \leq n $ ), $ a_k $ is divisible $ ^\dagger $ by either $ a_i $ or $ a_j $ .

Determine whether $ a $ is beautiful.

 $ ^\dagger $ $ x $ is divisible by $ y $ if there exists an integer $ z $ such that $ x = y \cdot z $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\leq t\leq 500 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3\leq n\leq 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\leq a_i \leq 10^9 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "Yes" if array $ a $ is beautiful, and output "No" otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the first test case, any two numbers in the array are coprime, so the answer is "No".

In the second test case, we can pick $ i=2 $ and $ j=1 $ . Since every number in the array is divisible by $ a_i = 1 $ , the answer is "Yes".

In the third test case, we can pick $ i=3 $ and $ j=5 $ . $ 2 $ and $ 4 $ is divisible by $ a_i = 2 $ while $ 3 $ , $ 6 $ and $ 12 $ is divisible by $ a_j = 3 $ , so the answer is "Yes".

## 样例 #1

### 输入

```
4
3
7 3 8
5
7 1 9 3 5
5
4 12 2 6 3
5
7 49 9 3 1000000000
```

### 输出

```
No
Yes
Yes
No
```



---

---
title: "New Bakery"
layout: "post"
diff: 普及-
pid: CF1978B
tag: ['数学', '贪心']
---

# New Bakery

## 题目描述

### 题意

有一个长度为 $n$ 的数列和两个常数 $a,b$ 以及一个正整数 $k(1 \leq k \leq n)$，数列按以下方式构造：

- 对于前 $k$ 项，第 $i$ 项的值为 $b-i+1$；
- 对于剩下的项，每一项的值都为 $a$。

整数 $k$ 的值由你决定，但你需要保证数列中所有的项均为**非负整数**。在此条件下，你需要求出这个数列的和的最大值。

## 输入格式

本题有 $T$ 组数据，第一行则为一个正整数，为数据组数 $T$。

每组数据有且只有一行三个非负整数 $n,a,b$。

## 输出格式

每组数据一行一个整数，为答案。

## 样例 #1

### 输入

```
7
4 4 5
5 5 9
10 10 5
5 5 11
1000000000 1000000000 1000000000
1000000000 1000000000 1
1000 1 1000
```

### 输出

```
17
35
100
45
1000000000000000000
1000000000000000000
500500
```



---

---
title: "Turtle and Piggy Are Playing a Game"
layout: "post"
diff: 普及-
pid: CF1981A
tag: ['数学']
---

# Turtle and Piggy Are Playing a Game

## 题目描述

Turtle and Piggy are playing a number game.

First, Turtle will choose an integer $ x $ , such that $ l \le x \le r $ , where $ l, r $ are given. It's also guaranteed that $ 2l \le r $ .

Then, Piggy will keep doing the following operation until $ x $ becomes $ 1 $ :

- Choose an integer $ p $ such that $ p \ge 2 $ and $ p \mid x $ (i.e. $ x $ is a multiple of $ p $ ).
- Set $ x $ to $ \frac{x}{p} $ , and the score will increase by $ 1 $ .

The score is initially $ 0 $ . Both Turtle and Piggy want to maximize the score. Please help them to calculate the maximum score.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ l, r $ ( $ 1 \le l \le r \le 10^9, 2l \le r $ ) — The range where Turtle can choose the integer from.

## 输出格式

For each test case, output a single integer — the maximum score.

## 说明/提示

In the first test case, Turtle can choose an integer $ x $ , such that $ 2 \le x \le 4 $ . He can choose $ x = 4 $ . Then Piggy can choose $ p = 2 $ for $ 2 $ times. After that, $ x $ will become $ 1 $ , and the score will be $ 2 $ , which is maximized.

In the second test case, Turtle can choose an integer $ 3 \le x \le 6 $ . He can choose $ x = 6 $ . Then Piggy can choose $ p = 2 $ , then choose $ p = 3 $ . After that, $ x $ will become $ 1 $ , and the score will be $ 2 $ , which is maximum.

In the third test case, Turtle can choose $ x = 12 $ .

In the fourth test case, Turtle can choose $ x = 16 $ .

## 样例 #1

### 输入

```
5
2 4
3 6
2 15
6 22
114514 1919810
```

### 输出

```
2
2
3
4
20
```



---

---
title: "Large Addition"
layout: "post"
diff: 普及-
pid: CF1984B
tag: ['数学']
---

# Large Addition

## 题目描述

A digit is large if it is between $ 5 $ and $ 9 $ , inclusive. A positive integer is large if all of its digits are large.

You are given an integer $ x $ . Can it be the sum of two large positive integers with the same number of digits?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The only line of each test case contains a single integer $ x $ ( $ 10 \leq x \leq 10^{18} $ ).

## 输出格式

For each test case, output $ \texttt{YES} $ if $ x $ satisfies the condition, and $ \texttt{NO} $ otherwise.

You can output $ \texttt{YES} $ and $ \texttt{NO} $ in any case (for example, strings $ \texttt{yES} $ , $ \texttt{yes} $ , and $ \texttt{Yes} $ will be recognized as a positive response).

## 说明/提示

In the first test case, we can have $ 658 + 679 = 1337 $ .

In the second test case, it can be shown that no numbers of equal length and only consisting of large digits can add to $ 200 $ .

In the third test case, we can have $ 696\,969 + 696\,969 = 1\,393\,938 $ .

In the fourth test case, we can have $ 777 + 657 = 1434 $ .

## 样例 #1

### 输入

```
11
1337
200
1393938
1434
98765432123456789
11111111111111111
420
1984
10
69
119
```

### 输出

```
YES
NO
YES
YES
NO
YES
NO
YES
YES
NO
NO
```



---

---
title: "Secret Box"
layout: "post"
diff: 普及-
pid: CF1985E
tag: ['数学', '枚举', '排列组合']
---

# Secret Box

## 题目描述

Ntarsis has a box $ B $ with side lengths $ x $ , $ y $ , and $ z $ . It lies in the 3D coordinate plane, extending from $ (0,0,0) $ to $ (x,y,z) $ .

Ntarsis has a secret box $ S $ . He wants to choose its dimensions such that all side lengths are positive integers, and the volume of $ S $ is $ k $ . He can place $ S $ somewhere within $ B $ such that:

- $ S $ is parallel to all axes.
- every corner of $ S $ lies on an integer coordinate.

 $ S $ is magical, so when placed at an integer location inside $ B $ , it will not fall to the ground.

Among all possible ways to choose the dimensions of $ S $ , determine the maximum number of distinct locations he can choose to place his secret box $ S $ inside $ B $ . Ntarsis does not rotate $ S $ once its side lengths are selected.

## 输入格式

The first line consists of an integer $ t $ , the number of test cases ( $ 1 \leq t \leq 2000 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ x, y, z $ and $ k $ ( $ 1 \leq x, y, z \leq 2000 $ , $ 1 \leq k \leq x \cdot y \cdot z $ ).

It is guaranteed the sum of all $ x $ , sum of all $ y $ , and sum of all $ z $ do not exceed $ 2000 $ over all test cases.

Note that $ k $ may not fit in a standard 32-bit integer data type.

## 输出格式

For each test case, output the answer as an integer on a new line. If there is no way to select the dimensions of $ S $ so it fits in $ B $ , output $ 0 $ .

## 说明/提示

For the first test case, it is optimal to choose $ S $ with side lengths $ 2 $ , $ 2 $ , and $ 2 $ , which has a volume of $ 2 \cdot 2 \cdot 2 = 8 $ . It can be shown there are $ 8 $ ways to put $ S $ inside $ B $ .

The coordinate with the least $ x $ , $ y $ , and $ z $ values for each possible arrangement of $ S $ are:

1. $ (0, 0, 0) $
2. $ (1, 0, 0) $
3. $ (0, 1, 0) $
4. $ (0, 0, 1) $
5. $ (1, 0, 1) $
6. $ (1, 1, 0) $
7. $ (0, 1, 1) $
8. $ (1, 1, 1) $

The arrangement of $ S $ with a coordinate of $ (0, 0, 0) $ is depicted below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1985E/47efaaa7005bda1e805807f94ece6c58f2ba3050.png)For the second test case, $ S $ with side lengths $ 2 $ , $ 3 $ , and $ 3 $ are optimal.

## 样例 #1

### 输入

```
7
3 3 3 8
3 3 3 18
5 1 1 1
2 2 2 7
3 4 2 12
4 3 1 6
1800 1800 1800 4913000000
```

### 输出

```
8
2
5
0
4
4
1030301
```



---

---
title: "Split the Multiset"
layout: "post"
diff: 普及-
pid: CF1988A
tag: ['数学']
---

# Split the Multiset

## 题目描述

A multiset is a set of numbers in which there can be equal elements, and the order of the numbers does not matter. For example, $ \{2,2,4\} $ is a multiset.

You have a multiset $ S $ . Initially, the multiset contains only one positive integer $ n $ . That is, $ S=\{n\} $ . Additionally, there is a given positive integer $ k $ .

In one operation, you can select any positive integer $ u $ in $ S $ and remove one copy of $ u $ from $ S $ . Then, insert no more than $ k $ positive integers into $ S $ so that the sum of all inserted integers is equal to $ u $ .

Find the minimum number of operations to make $ S $ contain $ n $ ones.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). Description of the test cases follows.

The only line of each testcase contains two integers $ n,k $ ( $ 1\le n\le 1000,2\le k\le 1000 $ ).

## 输出格式

For each testcase, print one integer, which is the required answer.

## 说明/提示

For the first test case, initially $ S=\{1\} $ , already satisfying the requirement. Therefore, we need zero operations.

For the second test case, initially $ S=\{5\} $ . We can apply the following operations:

- Select $ u=5 $ , remove $ u $ from $ S $ , and insert $ 2,3 $ into $ S $ . Now, $ S=\{2,3\} $ .
- Select $ u=2 $ , remove $ u $ from $ S $ , and insert $ 1,1 $ into $ S $ . Now, $ S=\{1,1,3\} $ .
- Select $ u=3 $ , remove $ u $ from $ S $ , and insert $ 1,2 $ into $ S $ . Now, $ S=\{1,1,1,2\} $ .
- Select $ u=2 $ , remove $ u $ from $ S $ , and insert $ 1,1 $ into $ S $ . Now, $ S=\{1,1,1,1,1\} $ .

Using $ 4 $ operations in total, we achieve the goal.

For the third test case, initially $ S=\{6\} $ . We can apply the following operations:

- Select $ u=6 $ , remove $ u $ from $ S $ , and insert $ 1,2,3 $ into $ S $ . Now, $ S=\{1,2,3\} $ .
- Select $ u=2 $ , remove $ u $ from $ S $ , and insert $ 1,1 $ into $ S $ . Now, $ S=\{1,1,1,3\} $ .
- Select $ u=3 $ , remove $ u $ from $ S $ , and insert $ 1,1,1 $ into $ S $ . Now, $ S=\{1,1,1,1,1,1\} $ .

Using $ 3 $ operations in total, we achieve the goal.

For the fourth test case, initially $ S=\{16\} $ . We can apply the following operations:

- Select $ u=16 $ , remove $ u $ from $ S $ , and insert $ 4,4,4,4 $ into $ S $ . Now, $ S=\{4,4,4,4\} $ .
- Repeat for $ 4 $ times: select $ u=4 $ , remove $ u $ from $ S $ , and insert $ 1,1,1,1 $ into $ S $ .

Using $ 5 $ operations in total, we achieve the goal.

## 样例 #1

### 输入

```
4
1 5
5 2
6 3
16 4
```

### 输出

```
0
4
3
5
```



---

---
title: "Only Pluses"
layout: "post"
diff: 普及-
pid: CF1992A
tag: ['数学', '贪心']
---

# Only Pluses

## 题目描述

Kmes has written three integers $ a $ , $ b $ and $ c $ in order to remember that he has to give Noobish\_Monk $ a \times b \times c $ bananas.

Noobish\_Monk has found these integers and decided to do the following at most $ 5 $ times:

- pick one of these integers;
- increase it by $ 1 $ .

For example, if $ a = 2 $ , $ b = 3 $ and $ c = 4 $ , then one can increase $ a $ three times by one and increase $ b $ two times. After that $ a = 5 $ , $ b = 5 $ , $ c = 4 $ . Then the total number of bananas will be $ 5 \times 5 \times 4 = 100 $ .

What is the maximum value of $ a \times b \times c $ Noobish\_Monk can achieve with these operations?

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of the test cases follows.

The first and only line of each test case contains three integers $ a $ , $ b $ and $ c $ ( $ 1 \le a, b, c \le 10 $ ) — Kmes's integers.

## 输出格式

For each test case, output a single integer — the maximum amount of bananas Noobish\_Monk can get.

## 样例 #1

### 输入

```
2
2 3 4
10 1 10
```

### 输出

```
100
600
```



---

---
title: "Diagonals"
layout: "post"
diff: 普及-
pid: CF1995A
tag: ['数学']
---

# Diagonals

## 题目描述

Vitaly503 is given a checkered board with a side of $ n $ and $ k $ chips. He realized that all these $ k $ chips need to be placed on the cells of the board (no more than one chip can be placed on a single cell).

Let's denote the cell in the $ i $ -th row and $ j $ -th column as $ (i ,j) $ . A diagonal is the set of cells for which the value $ i + j $ is the same. For example, cells $ (3, 1) $ , $ (2, 2) $ , and $ (1, 3) $ lie on the same diagonal, but $ (1, 2) $ and $ (2, 3) $ do not. A diagonal is called occupied if it contains at least one chip.

Determine what is the minimum possible number of occupied diagonals among all placements of $ k $ chips.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of sets of input data. Then follow the descriptions of the sets of input data.

The only line of each set of input data contains two integers $ n $ , $ k $ ( $ 1 \le n \le 100, 0 \le k \le n^2 $ ) — the side of the checkered board and the number of available chips, respectively.

## 输出格式

For each set of input data, output a single integer — the minimum number of occupied diagonals with at least one chip that he can get after placing all $ k $ chips.

## 说明/提示

In the first test case, there are no chips, so 0 diagonals will be occupied. In the second test case, both chips can be placed on diagonal $ (2, 1), (1, 2) $ , so the answer is 1. In the third test case, 3 chips can't be placed on one diagonal, but placing them on $ (1, 2), (2, 1), (1, 1) $ makes 2 diagonals occupied. In the 7th test case, chips will occupy all 5 diagonals in any valid placing.

## 样例 #1

### 输入

```
7
1 0
2 2
2 3
2 4
10 50
100 239
3 9
```

### 输出

```
0
1
2
3
6
3
5
```



---

---
title: "Find K Distinct Points with Fixed Center"
layout: "post"
diff: 普及-
pid: CF1998A
tag: ['数学']
---

# Find K Distinct Points with Fixed Center

## 题目描述

我没能给这道题想出一个好的标题，所以我决定去力扣学习。

——《孙子兵法》

给你三个整数 $x_c$，$y_c$ 和 $k$（$ -100 \leq x_c, y_c \leq 100 $ , $ 1 \leq k \leq 1000 $）。

在一个 2D 平面上，你需要找到 $k$ 个**不同的**具有整数坐标的点 ( $ x_1, y_1 $ ), ( $ x_2, y_2 $ ), $ \ldots $ , ( $ x_k, y_k $ )，满足：

- 它们的中心$ ^{\text{∗}} $ 为 ( $ x_c, y_c $ )。
- 从 $1$ 到 $k$，对于每一个 $i$，都有 $ -10^9 \leq x_i, y_i \leq 10^9 $。

可以证明至少有一组 $k$ 个不同的点满足以上条件。

 $ ^{\text{∗}} $ 任意 $ k $ 个点 ( $ x_1, y_1 $ ), ( $ x_2, y_2 $ ), $ \ldots $ , ( $ x_k, y_k $ ) 的中心是 $ \left( \frac{x_1 + x_2 + \ldots + x_k}{k}, \frac{y_1 + y_2 + \ldots + y_k}{k} \right) $。

## 输入格式

第一行包含一个正整数 $ t $ ( $ 1 \leq t \leq 100 $ )，表示测试数据的组数。

每组测试数据包含三个整数 $ x_c $ , $ y_c $ 和 $ k $ ( $ -100 \leq x_c, y_c \leq 100 $ , $ 1 \leq k \leq 1000 $ ) 表示中心的坐标和你需要找到不同点的个数。

保证 $ k $ 的总和不超过 $ 1000 $。

## 输出格式

对于每一个测试点，输出 $ k $ 行，第 $ i $ 行包含两个以空格分隔的整数，$ x_i $ 和 $ y_i $，( $ -10^9 \leq x_i, y_i \leq 10^9 $ )，表示第 $i$ 个点的坐标。

如果有多个答案，输出任意一个即可。可以证明在给定条件下必然有解。

## 说明/提示

对于第一组测试数据，$ \left( \frac{10}{1}, \frac{10}{1} \right) = (10, 10) $ .

对于第二组测试数据，$ \left( \frac{-1 + 5 - 4}{3}, \frac{-1 -1 + 2}{3} \right) = (0, 0) $ .

翻译：[@imnotcfz](https://www.luogu.com.cn/user/776004)

## 样例 #1

### 输入

```
4
10 10 1
0 0 3
-5 -8 8
4 -5 3
```

### 输出

```
10 10
-1 -1
5 -1
-4 2
-6 -7
-5 -7
-4 -7
-4 -8
-4 -9
-5 -9
-6 -9
-6 -8
1000 -1000
-996 995
8 -10
```



---

---
title: "Distanced Coloring"
layout: "post"
diff: 普及-
pid: CF2002A
tag: ['数学']
---

# Distanced Coloring

## 题目描述

You received an $ n\times m $ grid from a mysterious source. The source also gave you a magic positive integer constant $ k $ .

The source told you to color the grid with some colors, satisfying the following condition:

- If $ (x_1,y_1) $ , $ (x_2,y_2) $ are two distinct cells with the same color, then $ \max(|x_1-x_2|,|y_1-y_2|)\ge k $ .

You don't like using too many colors. Please find the minimum number of colors needed to color the grid.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1\le t\le1000 $ ). The description of the test cases follows.

The only line of each test case consists of three positive integers $ n $ , $ m $ , $ k $ ( $ 1\le n,m,k\le10^4 $ ) — the dimensions of the grid and the magic constant.

## 输出格式

For each test case, print a single integer — the minimum number of colors needed to color the grid.

## 说明/提示

In the first test case, one of the optimal constructions is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2002A/9ce95b69207ca02098572c656648bb834e503b1e.png)In the second test case, the color of all cells must be pairwise different, so the answer is $ 5 $ .

## 样例 #1

### 输入

```
6
3 3 2
5 1 10000
7 3 4
3 2 7
8 9 6
2 5 4
```

### 输出

```
4
5
12
6
36
8
```



---

---
title: "Black Circles"
layout: "post"
diff: 普及-
pid: CF2002C
tag: ['数学', '贪心']
---

# Black Circles

## 题目描述

在一个二维平面上有 $n$ 个圆。第 $i$ 个圆的圆心位于 $(x_i, y_i)$。最初，所有圆的半径都是 $0$。

这些圆的半径以每秒 $1$ 单位的速度增长。

你现在的位置是 $(x_s, y_s)$，你的目标是到达 $(x_t, y_t)$，并且在这个运动过程中不能碰到任何一个圆的边缘（包括你到达 $(x_t, y_t)$ 的那一刻）。你可以向任意方向移动。然而，你的速度被限制在每秒 $1$ 单位。

请判断是否有可能实现这一目标。

## 输入格式

每个测试样例包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接着是各个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^5$）——圆的数量。

接下来的 $n$ 行，每行包含两个整数 $x_i$ 和 $y_i$（$1 \le x_i, y_i \le 10^9$）——每个圆的圆心坐标。

最后一行包含四个整数 $x_s$，$y_s$，$x_t$，$y_t$（$1 \le x_s, y_s, x_t, y_t \le 10^9$）——起点和终点的坐标。

题目保证这 $n+2$ 个点是互不相同的。

题目还保证所有测试用例中 $n$ 的总和不超过 $10^5$。

## 输出格式

对于每一个测试用例，如果能够不接触任何圆的边缘就能到达目标，则输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

你可以不区分大小写输出 $\texttt{YES}$ 和 $\texttt{NO}$（例如，$\texttt{yEs}$、$\texttt{yes}$、$\texttt{Yes}$ 和 $\texttt{YES}$ 都会被认为是肯定的回答）。

## 说明/提示

在第一个测试用例中，一种可行的移动方式如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2002C/e91b557a5335aaaa3689cd6df137ea06f9152e48.png)

## 样例 #1

### 输入

```
7
3
2 5
2 14
10 13
4 9 9 7
3
10 11
6 9
12 12
14 13 4 8
1
5 7
12 6 11 13
2
1000000000 2
2 1000000000
1 1 2 2
1
999999998 1000000000
999999999 999999999 1 1
1
1000000000 1
1 1000000000 1 1
10
989237121 2397081
206669655 527238537
522705783 380636165
532545346 320061691
207818728 199485303
884520552 315781807
992311437 802563521
205138355 324818663
223575704 395073023
281560523 236279118
216941610 572010615 323956540 794523071
```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
```



---

---
title: "Closest Point"
layout: "post"
diff: 普及-
pid: CF2004A
tag: ['数学']
---

# Closest Point

## 题目描述

考虑直线上的一个点集，$i$ 到 $j$ 的距离是 $\lvert i-j\rvert$。

$i$ 是集合中离 $j$ 最近的点，当且仅当不存在另一点 $k$，满足 $j$ 到 $k$ 的距离严格小于 $j$ 到 $i$ 的距离。换句话说，集合中其他所有点到 $j$ 的距离大于等于 $\lvert i-j\rvert$。

例如，考虑一个点集 $\{1,3,5,8\}$：

- 对于点 $1$，最近的点是 $3$（其他所有点到 $1$ 的距离大于 $\lvert 1-3\rvert=2$）；

- 对于点 $3$，有两个最近的点：$1$ 和 $5$；

- 对于点 $5$，最近的点是 $3$（而不是 $8$，因为它到 $5$ 的距离大于 $\lvert 3-5\rvert$）；

- 对于点 $8$，最近的点是 $5$。

给你一个点集，你必须往里面加入一个原本不存在于点集中的整数点，并使其成为点集中每个点的最近的点。你需要判断是否可能做到。

## 输入格式

第一行一个整数 $t(1\le t\le 1000)$，表示测试数据组数。

每一组数据包含以下两行：

- 第一行一个整数 $n(2\le n\le 40)$，表示点集的大小。

- 第二行 $n$ 个整数 $x_1,x_2,\dots,x_n(1\le x_1<x_2<\dots<x_n\le 100)$，表示点集中的点。

## 输出格式

对于每一组测试数据，如果可以加入一个点满足要求，输出 `YES`；否则输出 `NO`。

## 样例 #1

### 输入

```
3
2
3 8
2
5 6
6
1 2 3 4 5 10
```

### 输出

```
YES
NO
NO
```



---

---
title: "Simple Palindrome"
layout: "post"
diff: 普及-
pid: CF2005A
tag: ['数学', '贪心']
---

# Simple Palindrome

## 题目描述

构造一个 **长度为** $n$ ，且只由 $a$，$e$，$i$，$o$，$u$ **这 $5$ 种字母** 构成字符串，使得这个字符串的 **所有子序列** 是 **回文串** 的个数最少。请输出这个 **最小值** 。

## 输入格式

第一行一个正整数 $T$ ，表示有 $T$ 组数据。
 接下来 共 $T$ 行，每行一个 **正整数** $n$ ，需要构造的 **字符串的长度** 。

## 输出格式

共 $T$ 行，每行一个 **正整数** ，表示答案的最小值。

## 说明/提示

对于 $100\%$ 的测试点，$1\le T\le 100$， $1\le n\le 100$ 。

## 样例 #1

### 输入

```
3
2
3
6
```

### 输出

```
uo
iae
oeiiua
```



---

---
title: "The Strict Teacher (Easy Version)"
layout: "post"
diff: 普及-
pid: CF2005B1
tag: ['数学', '分类讨论']
---

# The Strict Teacher (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions are the constraints on $ m $ and $ q $ . In this version, $ m=2 $ and $ q=1 $ . You can make hacks only if both versions of the problem are solved.

Narek and Tsovak were busy preparing this round, so they have not managed to do their homework and decided to steal David's homework. Their strict teacher noticed that David has no homework and now wants to punish him. She hires other teachers to help her catch David. And now $ m $ teachers together are chasing him. Luckily, the classroom is big, so David has many places to hide.

The classroom can be represented as a one-dimensional line with cells from $ 1 $ to $ n $ , inclusive.

At the start, all $ m $ teachers and David are in distinct cells. Then they make moves. During each move

- David goes to an adjacent cell or stays at the current one.
- Then, each of the $ m $ teachers simultaneously goes to an adjacent cell or stays at the current one.

This continues until David is caught. David is caught if any of the teachers (possibly more than one) is located in the same cell as David. Everyone sees others' moves, so they all act optimally.

Your task is to find how many moves it will take for the teachers to catch David if they all act optimally.

Acting optimally means the student makes his moves in a way that maximizes the number of moves the teachers need to catch him; and the teachers coordinate with each other to make their moves in a way that minimizes the number of moves they need to catch the student.

Also, as Narek and Tsovak think this task is easy, they decided to give you $ q $ queries on David's position. Note: this is the easy version, and you are given only one query.

## 输入格式

In the first line of the input, you are given a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. The description of each test case follows.

In the first line of each test case, you are given three integers $ n $ , $ m $ , and $ q $ ( $ 3 \le n \le 10^9 $ , $ m=2 $ , $ q=1 $ ) — the number of cells on the line, the number of teachers, and the number of queries.

In the second line of each test case, you are given $ m $ distinct integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le n $ ) — the cell numbers of the teachers.

In the third line of each test case, you are given $ q $ integers $ a_1, a_2, \ldots, a_q $ ( $ 1 \le a_i \le n $ ) — David's cell number for every query.

It is guaranteed that for any $ i $ , $ j $ such that $ 1 \le i \le m $ and $ 1 \le j \le q $ , $ b_i \neq a_j $ .

## 输出格式

For each test case, output $ q $ lines, the $ i $ -th of them containing the answer of the $ i $ -th query.

## 说明/提示

In the first example, the student can just stay at cell $ 2 $ . The teacher, initially located in cell $ 1 $ , can reach cell $ 2 $ in one move. Therefore, the answer is $ 1 $ .

In the second example, the student should just stay at cell $ 1 $ . The teacher, initially located in cell $ 3 $ , can reach cell $ 1 $ in two moves. Therefore, the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8
```

### 输出

```
1
2
2
```



---

---
title: "Longest Good Array"
layout: "post"
diff: 普及-
pid: CF2008C
tag: ['数学']
---

# Longest Good Array

## 题目描述

Sakurako 今天在研究数组问题。我们说一个数组 $a$ 是“优秀的”，当且仅当：

- 这个数组是严格递增的，也就是对每个 $2 \le i \le n$，都有 $a_{i - 1} < a_i$；
- 相邻元素的差值也是严格递增的，即对于每个 $2 \le i < n$，都有 $a_i - a_{i-1} < a_{i+1} - a_i$。

Sakurako 给定了两个边界值 $l$ 和 $r$，她希望构造一个最长的优秀数组，使得数组中的每个元素 $a_i$ 满足 $l \le a_i \le r$。

请你帮助 Sakurako 找出在给定 $l$ 和 $r$ 条件下，最长优秀数组的长度。

## 输入格式

第一行是一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的总数。

接下来每个测试用例包含一行，由两个整数 $l$ 和 $r$ 组成（$1 \le l \le r \le 10^9$）。

## 输出格式

对于每个测试用例，输出一个整数，表示 Sakurako 可以构造的最长优秀数组的长度。

## 说明/提示

例如，当 $l=1$ 和 $r=5$ 时，一个可能的优秀数组是 $(1, 2, 5)$。可以证明，给定这些边界值，不存在长度为 $4$ 的优秀数组。

当 $l=2$ 和 $r=2$ 时，唯一的数组是 $(2)$。

当 $l=10$ 和 $r=20$ 时，一个唯一的优秀数组是 $(10, 11, 13, 16, 20)$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
1 2
1 5
2 2
10 20
1 1000000000
```

### 输出

```
2
3
1
5
44721
```



---

---
title: "The Legend of Freya the Frog"
layout: "post"
diff: 普及-
pid: CF2009C
tag: ['数学', '贪心']
---

# The Legend of Freya the Frog

## 题目描述

Freya the Frog is traveling on the 2D coordinate plane. She is currently at point $ (0,0) $ and wants to go to point $ (x,y) $ . In one move, she chooses an integer $ d $ such that $ 0 \leq d \leq k $ and jumps $ d $ spots forward in the direction she is facing.

Initially, she is facing the positive $ x $ direction. After every move, she will alternate between facing the positive $ x $ direction and the positive $ y $ direction (i.e., she will face the positive $ y $ direction on her second move, the positive $ x $ direction on her third move, and so on).

What is the minimum amount of moves she must perform to land on point $ (x,y) $ ?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case contains three integers $ x $ , $ y $ , and $ k $ ( $ 0 \leq x, y \leq 10^9, 1 \leq k \leq 10^9 $ ).

## 输出格式

For each test case, output the number of jumps Freya needs to make on a new line.

## 说明/提示

In the first sample, one optimal set of moves is if Freya jumps in the following way: ( $ 0,0 $ ) $ \rightarrow $ ( $ 2,0 $ ) $ \rightarrow $ ( $ 2,2 $ ) $ \rightarrow $ ( $ 3,2 $ ) $ \rightarrow $ ( $ 3,5 $ ) $ \rightarrow $ ( $ 6,5 $ ) $ \rightarrow $ ( $ 6,8 $ ) $ \rightarrow $ ( $ 9,8 $ ) $ \rightarrow $ ( $ 9,11 $ ). This takes 8 jumps.

## 样例 #1

### 输入

```
3
9 11 3
0 10 8
1000000 100000 10
```

### 输出

```
8
4
199999
```



---

---
title: "Robin Hood and the Major Oak"
layout: "post"
diff: 普及-
pid: CF2014B
tag: ['数学', '数论']
---

# Robin Hood and the Major Oak

## 题目描述

在 Sherwood（原文地名）里，树木是我们的庇护所，我们都是森林的孩子。

Sherwood 中的 Major Oak（原文物品名称）以它宏伟的树叶而闻名，这些树叶为 Robin Hood（原文人名）和他的快乐男男女女们提供了庇护。

Major Oak 在 $i$ 年长出 $i^i$ 片新叶子。它从第一年开始就有 $1$ 片叶子。

树叶在树上最多能持续 $k$ 年。换句话说，第 $i$ 年长出的树叶可以持续到第 $i$ 年到第 $i+k-1$ 年。

这段文本的意思是：Robin 认为偶数是幸运的。请帮助 Robin 确定 Major Oak 在第 $n$ 年是否有偶数片叶子。

## 输入格式

输入的第一行包含一个整数 $t$（$1\le t\le 10^4$）——测试用例的数量。

每个测试用例包含两个整数 $n$，$k$（$1\le n\le 10^9$，$1\le k\le n$）——请求的年份和叶子保持的时间长度。

## 输出格式

对于每个测试用例，输出一行，如果年份 $n$ 时，Major Oak 的叶子数量为偶数，则输出 `YES`；否则输出 `NO`。

你可以以任何大小写形式输出答案。例如，字符串 `yEs`、`yes`、`Yes` 和 `YES` 将被识别为肯定回答。

## 说明/提示

在第一个测试用例中，只有 $ 1 $ 片叶子。

在第二个测试用例中，$ k=1 $ ，所以第 $ 2 $ 年会有 $ 2^2=4 $ 片叶子。

在第三个测试用例中，$ k=2 $ ，所以第 $ 2 $ 年会有 $ 1+2^2=5 $ 片叶子。

在第四个测试用例中，$ k=2 $ ，所以第 $ 3 $ 年会有 $ 2^2 + 3^3 = 4 + 27 = 31 $ 片叶子。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
5
1 1
2 1
2 2
3 2
4 4
```

### 输出

```
NO
YES
NO
NO
YES
```



---

---
title: "Robin Hood in Town"
layout: "post"
diff: 普及-
pid: CF2014C
tag: ['数学', '二分']
---

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 输入格式

The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2\cdot10^5 $ ) — the total population.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — the wealth of each person.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the minimum number of gold that the richest person must find for Robin Hood to appear. If it is impossible, output $ -1 $ instead.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25
```

### 输出

```
-1
-1
0
15
16
0
```



---

---
title: "Brightness Begins"
layout: "post"
diff: 普及-
pid: CF2020B
tag: ['数学', '二分']
---

# Brightness Begins

## 题目描述

想象你有 $n$ 个编号为 $1, 2, \ldots, n$ 的灯泡。最初，所有灯泡都是开着的。翻转一个灯泡的状态意味着如果它原来是开着的，就把它关掉；否则就把它打开。

接下来，您需要执行以下操作：

对于每个 $i=1,2,\ldots,n$，翻转所有灯泡 $j$ 的状态，使得 $j$ 能被 $i^\dagger$ 整除。

在执行完所有操作后，将会有一些灯泡仍然亮着。你的目标是使这个数量恰好为 $k$。

找到最小的合适 $n$，使得执行操作后，灯泡的数量恰好为 $k$。我们可以证明答案总是存在的。

$ ^\dagger $ 如果存在一个整数 $ z $ 使得 $ x = y\cdot z $ ，那么一个整数 $ x $ 可以被 $ y $ 整除。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1\le t\le 10^4$）。测试用例的描述如下。

每个测试用例的唯一一行包含一个整数 $k$（$1\le k\le 10^{18}$）。

## 输出格式

对于每个测试用例，输出 $n$——最小灯泡数量。

## 说明/提示

在第一个测试用例中，最小数量的灯泡是 $2$。让我们用一个数组来表示所有灯泡的状态，其中$1$对应于打开的灯泡，$0$ 对应于关闭的灯泡。最初，数组是 $[1, 1]$。

- 在执行了 $i=1$ 的操作后，数组变成了 $[\underline{0},\underline{0}]$。
- 在执行了 $i=2$ 的操作后，数组变成了 $[0,\underline{1}]$。

最后，有 $k=1$ 个灯泡亮着。我们还可以证明答案不可能小于 $2$。

在第二个测试用例中，最小数量的灯泡是 $5$。最初，数组是 $[1, 1, 1, 1, 1]$。

- 在执行了 $i=1$ 的操作后，数组变成了 $[\underline{0},\underline{0},\underline{0},\underline{0},\underline{0}]$。
- 在执行了 $i=2$ 的操作后，数组变成了 $[0,\underline{1},0,\underline{1},0]$。
- 在执行了 $i=3$ 的操作后，数组变成了 $[0,1,\underline{1},1,0]$。
- 在执行了 $i=4$ 的操作后，数组变成了 $[0,1,1,\underline{0},0]$。
- 在执行了 $i=5$ 的操作后，数组变成了 $[0,1,1,0,\underline{1}]$。

最后，有 $k=3$ 个灯泡亮着。我们还可以证明答案不可能小于 $5$。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
3
1
3
8
```

### 输出

```
2
5
11
```



---

---
title: "Bus to Pénjamo"
layout: "post"
diff: 普及-
pid: CF2022A
tag: ['数学', '贪心']
---

# Bus to Pénjamo

## 题目描述

# 前往佩尼亚莫的巴士


Ya vamos llegando a Péeeenjamoo ♫♫

有 $n$ 个家庭前往佩恩哈莫，见证墨西哥有史以来最大规模的 "拴着绳子遛鸡 "马拉松比赛。其中 $i$ 个家庭有 $a_i$ 名家庭成员。所有家庭将乘坐一辆大巴，每辆大巴有 $r$ 排， $2$ 个座位。

一个人在以下情况下被认为是幸福的：

- 另一名家庭成员与他们坐在同一排，或
- 他们独自坐在自己那一排（旁边有一个空座位）。

确定最佳座位安排下最多有多少人开心。注意，**每个人**都必须坐在车上。

保证所有家庭成员都能上车。形式上，保证 $\displaystyle\sum_{i=1}^{n}a_i \le 2r$ 。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ( $1 \le t \le 1000$ )。测试用例说明如下。

每个测试用例的第一行包含两个整数 $n$ 和 $r$ ( $1 \le n \le 100$ ; $1 \le r \le 500$ )--总线中的族数和行数。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ （ $1 \le a_i \le 10$ ）。( $1 \le a_i \le 10$ ) - 每个家庭的家庭成员数。

## 输出格式

针对每个测试案例，输出最佳座位安排下最多可容纳的人数。

```input1
4
3 3
2 3 1
3 3
2 2 2
4 5
1 1 2 2
4 5
3 1 1 3
```


```output1
4
6
6
6
```

## 说明/提示

在第一个测试案例中，第一个家庭的两名成员可以一起坐在第一排，而第二个家庭的两名成员可以一起坐在第二排。第二家庭的其余成员可与第三家庭的一名成员一起坐在第三排。这种座位安排如下图所示，其中 $4$ 快乐的人被涂成绿色。

| $\color{green}{1}$ | $\color{green}{1}$ |
| --- | --- |
| $\color{green}{2}$ | $\color{green}{2}$ |
| $2$ | $3$ |

在第二个测试案例中，有 $6$ 个快乐的人的可能座位安排如下所示。

| $\color{green}{3}$ | $\color{green}{3}$ |
| --- | --- |
| $\color{green}{1}$ | $\color{green}{1}$ |
| $\color{green}{2}$ | $\color{green}{2}$ |

在第三个测试案例中，有 $6$ 个快乐的人的可能座位安排如下所示。

| $\color{green}{4}$ | $\color{green}{4}$ |
| --- | --- |
| | $\color{green}{2}$ |
| $\color{green}{3}$ | $\color{green}{3}$ |
| $\color{green}{1}$ | |
| | |

## 样例 #1

### 输入

```
4
3 3
2 3 1
3 3
2 2 2
4 5
1 1 2 2
4 5
3 1 1 3
```

### 输出

```
4
6
6
6
```



---

---
title: "Kar Salesman"
layout: "post"
diff: 普及-
pid: CF2022B
tag: ['数学', '贪心']
---

# Kar Salesman

## 题目描述

Karel is a salesman in a car dealership. The dealership has $ n $ different models of cars. There are $ a_i $ cars of the $ i $ -th model. Karel is an excellent salesperson and can convince customers to buy up to $ x $ cars (of Karel's choice), as long as the cars are from different models.

Determine the minimum number of customers Karel has to bring in to sell all the cars.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ x $ ( $ 1 \le n \le 5 \cdot 10^5 $ ; $ 1 \le x \le 10 $ ) — the number of different models of cars and the maximum number of cars Karel can convince a customer to buy.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the number of cars of each model.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output the minimum possible number of customers needed to sell all the cars.

## 说明/提示

For the first case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 2 $ cars with model $ 1 $ and $ 2 $ .
- Customer $ 3 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .

For the second case, Karel only needs to lure in $ 3 $ customers. He will convince the customers to buy the following models of cars:

- Customer $ 1 $ buys $ 2 $ cars with model $ 1 $ and $ 3 $ .
- Customer $ 2 $ buys $ 3 $ cars with model $ 1 $ , $ 2 $ and $ 3 $ .
- Customer $ 3 $ buys $ 1 $ car with model $ 3 $ .

## 样例 #1

### 输入

```
4
3 2
3 1 2
3 3
2 1 3
5 3
2 2 1 9 2
7 4
2 5 3 3 5 2 5
```

### 输出

```
3
3
9
7
```



---

---
title: "Perpendicular Segments"
layout: "post"
diff: 普及-
pid: CF2026A
tag: ['数学']
---

# Perpendicular Segments

## 题目描述

You are given a coordinate plane and three integers $ X $ , $ Y $ , and $ K $ . Find two line segments $ AB $ and $ CD $ such that

1. the coordinates of points $ A $ , $ B $ , $ C $ , and $ D $ are integers;
2. $ 0 \le A_x, B_x, C_x, D_x \le X $ and $ 0 \le A_y, B_y, C_y, D_y \le Y $ ;
3. the length of segment $ AB $ is at least $ K $ ;
4. the length of segment $ CD $ is at least $ K $ ;
5. segments $ AB $ and $ CD $ are perpendicular: if you draw lines that contain $ AB $ and $ CD $ , they will cross at a right angle.

Note that it's not necessary for segments to intersect. Segments are perpendicular as long as the lines they induce are perpendicular.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 5000 $ ) — the number of test cases. Next, $ t $ cases follow.

The first and only line of each test case contains three integers $ X $ , $ Y $ , and $ K $ ( $ 1 \le X, Y \le 1000 $ ; $ 1 \le K \le 1414 $ ).

Additional constraint on the input: the values of $ X $ , $ Y $ , and $ K $ are chosen in such a way that the answer exists.

## 输出格式

For each test case, print two lines. The first line should contain $ 4 $ integers $ A_x $ , $ A_y $ , $ B_x $ , and $ B_y $ — the coordinates of the first segment.

The second line should also contain $ 4 $ integers $ C_x $ , $ C_y $ , $ D_x $ , and $ D_y $ — the coordinates of the second segment.

If there are multiple answers, print any of them.

## 说明/提示

The answer for the first test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/ec912df39bb0649b8cac618bfc67861cbe33f3a9.png)  The answer for the second test case:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/16297a765040b390fcf117cbdd6958cb27cfd2f6.png)  The answer for the third test case:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/2fa935fca6647221cd973d5ea3b266eb1839dab4.png)  The answer for the fourth test case:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2026A/41df202ce65e0906ba528f2a40ffbcdc5a825158.png)

## 样例 #1

### 输入

```
4
1 1 1
3 4 1
4 3 3
3 4 4
```

### 输出

```
0 0 1 0
0 0 0 1
2 4 2 2
0 1 1 1
0 0 1 3
1 2 4 1
0 1 3 4
0 3 3 0
```



---

---
title: "Rectangle Arrangement"
layout: "post"
diff: 普及-
pid: CF2027A
tag: ['数学', '贪心']
---

# Rectangle Arrangement

## 题目描述

You are coloring an infinite square grid, in which all cells are initially white. To do this, you are given $ n $ stamps. Each stamp is a rectangle of width $ w_i $ and height $ h_i $ .

You will use each stamp exactly once to color a rectangle of the same size as the stamp on the grid in black. You cannot rotate the stamp, and for each cell, the stamp must either cover it fully or not cover it at all. You can use the stamp at any position on the grid, even if some or all of the cells covered by the stamping area are already black.

What is the minimum sum of the perimeters of the connected regions of black squares you can obtain after all the stamps have been used?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 500 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ).

The $ i $ -th of the next $ n $ lines contains two integers $ w_i $ and $ h_i $ ( $ 1 \le w_i, h_i \le 100 $ ).

## 输出格式

For each test case, output a single integer — the minimum sum of the perimeters of the connected regions of black squares you can obtain after all the stamps have been used.

## 说明/提示

In the first test case, the stamps can be used as shown on the left. Each stamp is highlighted in its own color for clarity.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2027A/eb6eb9753bb0b7d5590d43612099263639e3e940.png)After all these stamps are used, there is one black region (as shown on the right), and its perimeter is $ 20 $ . It can be shown that there is no way of using the stamps that yields a lower total perimeter.

In the second test case, the second and third stamps can be used entirely inside the first one, so the minimum perimeter is equal to $ 8 $ .

## 样例 #1

### 输入

```
5
5
1 5
2 4
3 3
4 2
5 1
3
2 2
1 1
1 2
1
3 2
3
100 100
100 100
100 100
4
1 4
2 3
1 5
3 2
```

### 输出

```
20
8
10
400
16
```



---

---
title: "Set"
layout: "post"
diff: 普及-
pid: CF2029A
tag: ['数学', '贪心']
---

# Set

## 题目描述

You are given a positive integer $ k $ and a set $ S $ of all integers from $ l $ to $ r $ (inclusive).

You can perform the following two-step operation any number of times (possibly zero):

1. First, choose a number $ x $ from the set $ S $ , such that there are at least $ k $ multiples of $ x $ in $ S $ (including $ x $ itself);
2. Then, remove $ x $ from $ S $ (note that nothing else is removed).

Find the maximum possible number of operations that can be performed.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases. The description of test cases follows.

The only line of each test case contains three integers $ l $ , $ r $ , and $ k $ ( $ 1\le l\le r\leq 10^9 $ , $ 1\leq k\le r-l+1 $ ) — the minimum integer in $ S $ , the maximum integer in $ S $ , and the parameter $ k $ .

## 输出格式

For each test case, output a single integer — the maximum possible number of operations that can be performed.

## 说明/提示

In the first test case, initially, $ S = \{3,4,5,6,7,8,9\} $ . One possible optimal sequence of operations is:

1. Choose $ x = 4 $ for the first operation, since there are two multiples of $ 4 $ in $ S $ : $ 4 $ and $ 8 $ . $ S $ becomes equal to $ \{3,5,6,7,8,9\} $ ;
2. Choose $ x = 3 $ for the second operation, since there are three multiples of $ 3 $ in $ S $ : $ 3 $ , $ 6 $ , and $ 9 $ . $ S $ becomes equal to $ \{5,6,7,8,9\} $ .

In the second test case, initially, $ S=\{4,5,6,7,8,9\} $ . One possible optimal sequence of operations is:

1. Choose $ x = 5 $ , $ S $ becomes equal to $ \{4,6,7,8,9\} $ ;
2. Choose $ x = 6 $ , $ S $ becomes equal to $ \{4,7,8,9\} $ ;
3. Choose $ x = 4 $ , $ S $ becomes equal to $ \{7,8,9\} $ ;
4. Choose $ x = 8 $ , $ S $ becomes equal to $ \{7,9\} $ ;
5. Choose $ x = 7 $ , $ S $ becomes equal to $ \{9\} $ ;
6. Choose $ x = 9 $ , $ S $ becomes equal to $ \{\} $ .

In the third test case, initially, $ S=\{7,8,9\} $ . For each $ x $ in $ S $ , no multiple of $ x $ other than $ x $ itself can be found in $ S $ . Since $ k = 2 $ , you can perform no operations.

In the fourth test case, initially, $ S=\{2,3,4,5,6,7,8,9,10\} $ . One possible optimal sequence of operations is:

1. Choose $ x = 2 $ , $ S $ becomes equal to $ \{3,4,5,6,7,8,9,10\} $ ;
2. Choose $ x = 4 $ , $ S $ becomes equal to $ \{3,5,6,7,8,9,10\} $ ;
3. Choose $ x = 3 $ , $ S $ becomes equal to $ \{5,6,7,8,9,10\} $ ;
4. Choose $ x = 5 $ , $ S $ becomes equal to $ \{6,7,8,9,10\} $ .

## 样例 #1

### 输入

```
8
3 9 2
4 9 1
7 9 2
2 10 2
154 220 2
147 294 2
998 24435 3
1 1000000000 2
```

### 输出

```
2
6
0
4
0
1
7148
500000000
```



---

---
title: "A Gift From Orangutan"
layout: "post"
diff: 普及-
pid: CF2030A
tag: ['数学', '贪心']
---

# A Gift From Orangutan

## 题目描述

在丛林探险的时候，你遇到了一只罕见的戴着领结的猩猩！你和猩猩握了握手并给了它一些食物和水。作为回报……

猩猩给了你一个长度为 $n$ 的数组 $a$。通过数组 $a$ 你将会以下列的方式构造两个长度都为 $n$ 的数组 $b$ 和 $c$：

* $b_i = \text{min}(a_1,a_2,…,a_i),1 \le i \le n$。  
* $c_i = \text{max}(a_1,a_2,…,a_i),1 \le i \le n$。

定义 $a$ 的得分为 $\sum^n_{i=1} c_i-b_i$。在你计算分数之前，你可以任意修改 $a$ 中元素的顺序。

你需要求出可以获得的最高得分。

## 输入格式

**本题有多组测试数据**。

第一行包含一个正整数 $t(1 \le t \le 100)$，表示数据组数。

对于每组测试数据：  
第一行包含一个正整数 $n(1 \le n \le 1000)$，表示 $a$ 中元素的数量。  
第二行包含 $n$ 个正整数 $a_1,a_2,…,a_n(1 \le a_i \le 1000)$，表示 $a$ 中的元素。

保证单个测试点内的 $n$ 之和不超过 $1000$。

## 输出格式

对于每组数据，输出一行一个整数，表示可以获得的最高得分。

## 说明/提示

对于第一组数据，没有其他方法来重新排列 $a$，所以，$b=[69]$ 并且 $c=[69]$。唯一可能的得分为 $69-69=0$。

对于第二组数据，可以将 $a$ 重新排列为 $[7,5,6]$。这样，$b=[7,5,5]$ 并且 $c=[7,7,7]$。这种情况下的得分为 $(7-7)+(7-5)+(7-5)=4$。可以证明，这是可能的最高分数。

翻译来自 [Jason_Ming](https://www.luogu.com.cn/user/1014421)。

## 样例 #1

### 输入

```
3
1
69
3
7 6 5
5
1 1 1 2 2
```

### 输出

```
0
4
4
```



---

---
title: "Minimise Oneness"
layout: "post"
diff: 普及-
pid: CF2030B
tag: ['数学', '贪心']
---

# Minimise Oneness

## 题目描述

For an arbitrary binary string $ t $ $ ^{\text{∗}} $ , let $ f(t) $ be the number of non-empty subsequences $ ^{\text{†}} $ of $ t $ that contain only $ \mathtt{0} $ , and let $ g(t) $ be the number of non-empty subsequences of $ t $ that contain at least one $ \mathtt{1} $ .

Note that for $ f(t) $ and for $ g(t) $ , each subsequence is counted as many times as it appears in $ t $ . E.g., $ f(\mathtt{000}) = 7, g(\mathtt{100}) = 4 $ .

We define the oneness of the binary string $ t $ to be $ |f(t)-g(t)| $ , where for an arbitrary integer $ z $ , $ |z| $ represents the absolute value of $ z $ .

You are given a positive integer $ n $ . Find a binary string $ s $ of length $ n $ such that its oneness is as small as possible. If there are multiple strings, you can print any of them.

 $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements. For example, subsequences of $ \mathtt{1011101} $ are $ \mathtt{0} $ , $ \mathtt{1} $ , $ \mathtt{11111} $ , $ \mathtt{0111} $ , but not $ \mathtt{000} $ nor $ \mathtt{11100} $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The only line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of $ s $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, output $ s $ on a new line. If multiple answers exist, output any.

## 说明/提示

In the first test case, for the example output, $ f(t)=1 $ because there is one subsequence that contains only $ \mathtt{0} $ ( $ \mathtt{0} $ ), and $ g(t)=0 $ because there are no subsequences that contain at least one $ 1 $ . The oneness is $ |1-0|=1 $ . The output $ \mathtt{1} $ is correct as well because its oneness is $ |0-1|=1 $ .

For the example output of the second test case, $ f(t)=1 $ because there is one non-empty subsequence that contains only $ \mathtt{0} $ , and $ g(t)=2 $ because there are two non-empty subsequences that contain at least one $ \mathtt{1} $ ( $ \mathtt{01} $ and $ \mathtt{1} $ ). The oneness is thus $ |1-2|=1 $ . It can be shown that $ 1 $ is the minimum possible value of its oneness over all possible binary strings of size $ 2 $ .

## 样例 #1

### 输入

```
3
1
2
3
```

### 输出

```
0
01
010
```



---

---
title: "Sliding"
layout: "post"
diff: 普及-
pid: CF2035A
tag: ['数学']
---

# Sliding

## 题目描述

在有 $n$ 行和 $m$ 列的人群中，每个人都有一个编号，从左到右，从上到下排列。具体来说，第 $r$ 行第 $c$ 列的位置表示为 $(r, c)$，其编号为 $(r-1) \cdot m + c$。

现在，位于位置 $(r, c)$ 的人决定离开。假设这个人的编号是 $i$，那么所有编号大于 $i$ 的人会依次前移，占据编号 $j-1$ 的人的初始位置。例如：对于 $n=2$，$m=3$，$r=1$ 和 $c=2$ 的情况，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2035A/958314060b9182d5223494dfb5da32d06c99cb0a.png)

你的任务是计算每个受影响的人移动的曼哈顿距离之和。对于一个从位置 $(r_0, c_0)$ 移动到位置 $(r_1, c_1)$ 的人，其移动的曼哈顿距离定义为 $|r_0 - r_1| + |c_0 - c_1|$。

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

接下来每个测试用例包含四个整数 $n$，$m$，$r$ 和 $c$（$1 \le r \le n \le 10^6$，$1 \le c \le m \le 10^6$），表示行数、列数，以及离开者的初始位置。

## 输出格式

对于每个测试用例，输出一个整数，表示所有移动的人其曼哈顿距离之和。

## 说明/提示

- 对于第一个测试用例，编号为 $2$ 的人离开，编号为 $3$、$4$、$5$ 和 $6$ 的人需要移动，其移动距离分别为 $1$、$3$、$1$ 和 $1$。因此，答案是 $1 + 3 + 1 + 1 = 6$。
- 对于第二个测试用例，编号为 $3$ 的人离开，其后编号为 $4$ 的人移动，答案为 $1$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
2 3 1 2
2 2 2 1
1 1 1 1
1000000 1000000 1 1
```

### 输出

```
6
1
0
1999998000000
```



---

---
title: "Intercepted Inputs"
layout: "post"
diff: 普及-
pid: CF2037B
tag: ['数学']
---

# Intercepted Inputs

## 题目描述

### 题目翻译


为了帮助您准备即将到来的 Codeforces 竞赛，茜特菈莉设置了一个网格问题，并试图通过您的输入流为您提供一个 $n$ 乘 $m$ 的网格。具体来说，您的输入流应包含以下内容：

- 第一行包含 $n$ 和 $m$ 两个整数。- 网格的尺寸。
- 接下来的 $n$ 行分别包含 $m$ 个整数--网格值。

然而，有人截获了你的输入流，将所有给定的整数洗牌后放在一行！现在，一行中有 $k$ 个整数，而你却不知道每个整数原本属于哪一行。你决定自己确定 $n$ 和 $m$ 的值，而不是让茜特菈莉 重新发送输入。

输出茜特菈莉i 可能提供的 $n$ 和 $m$ 的任何可能值

## 输入格式

第一行包含一个整数 $t$ ( $1 \leq t \leq 10^4$ ) —— 测试用例的数量。

每个测试用例的第一行包含一个整数 $k$ ( $3 \leq k \leq 2 \cdot 10^5$ ) —— 输入流中的输入总数。

每个测试用例的下一行包含 $k$ 个整数 $a_1, a_2, \ldots, a_k$ ($1 \leq a_i \leq k$)  ) —— 输入流中经过洗牌的输入。保证 $n$ 和 $m$ 包含在 $k$ 整数中。

保证所有测试用例中 $k$ 的总和不超过 $2 \cdot 10^5$ 。

## 输出格式

对于每个测试用例，输出两个整数，分别为 $n$ 和 $m$ 中的一个可能值。如果存在多个可能答案，则输出任意答案。

## 样例 #1

### 输入

```
5
3
1 1 2
11
3 3 4 5 6 7 8 9 9 10 11
8
8 4 8 3 8 2 8 1
6
2 1 4 5 3 3
8
1 2 6 3 8 5 5 3
```

### 输出

```
1 1
3 3
2 3
4 1
1 6
```



---

---
title: "Superultra's Favorite Permutation"
layout: "post"
diff: 普及-
pid: CF2037C
tag: ['数学', '数论']
---

# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if it's not possible to construct $ p $ , output $ -1 $ on a new line. Otherwise, output $ n $ integers $ p_1, p_2, \ldots, p_n $ on a new line.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8
```

### 输出

```
-1
1 8 7 3 6 2 4 5
```



---

---
title: "Bridge Renovation"
layout: "post"
diff: 普及-
pid: CF2038L
tag: ['数学', '贪心']
---

# Bridge Renovation

## 题目描述

最近，Monocarp 开始在他家附近的一个公园担任董事。公园很大，所以它有一条小河甚至将其分成几个区域。这条河上建了几座桥。其中三座桥特别古老，需要维修。

所有三座桥的长度相同，但宽度不同。它们的宽度分别为 $18$，$21$，$25$ 个单位。

在公园翻新过程中，Monocarp 必须用新木板替换用作桥梁表面的旧木板。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2038L/85af0decbad9801e010ac724aebc06474601925e.png)

木板的标准长度为 $60$ 个单位。Monocarp 已经知道他每座桥都需要 $n$ 块木板。但是由于桥梁的宽度不同，第一座桥需要 $n$ 块长度为 $18$ 的木板，第二座桥需要 $n$ 块长度为 $21$ 的木板，最后一座桥需要 $n$ 块长度为 $25$ 的木板。

负责装修的工人可以将木板切成小块，但拒绝加入木板，因为它会产生薄弱点并且看起来很丑。

Monocarp 想尽可能少地购买木板，但难以计算所需的木板数量。你能帮他吗？

## 输入格式

第一行（也是唯一一行）包含一个整数 $n$（$1 \le n \le 1000$）— 三座桥中每座桥所需的木板数量。

## 输出格式

打印一个整数 — 如果木板可以切割成小块，Monocarp 需要覆盖所有三座桥的标准长度（$60$ 个单位）的最小木板数量。

## 说明/提示

在第一个例子中，可以将一块长度为 $60$ 的木板切割成三块长度为 $25$、$18$ 和 $17$ 的木板，并将另一块长度为 $60$ 的木板切割成两块长度为 $39$ 和 $21$ 的木板。这样，Monocarp 将拥有所有需要的木板。

## 样例 #1

### 输入

```
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1000
```

### 输出

```
1167
```



---

---
title: "Shohag Loves XOR (Easy Version)"
layout: "post"
diff: 普及-
pid: CF2039C1
tag: ['数学', '枚举', '位运算']
---

# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated integers $ x $ and $ m $ ( $ 1 \le x \le 10^6 $ , $ 1 \le m \le 10^{18} $ ).

It is guaranteed that the sum of $ x $ over all test cases does not exceed $ 10^7 $ .

## 输出格式

For each test case, print a single integer — the number of suitable $ y $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1
```

### 输出

```
3
2
1
1
0
```



---

---
title: "Paint a Strip"
layout: "post"
diff: 普及-
pid: CF2040B
tag: ['数学', '贪心']
---

# Paint a Strip

## 题目描述

你有一个长度为 $n$ 的数组 $a_1, a_2, \ldots, a_n$，其元素全为零。

可以对该数组进行两种操作：

1. 选择一个下标 $i$（满足 $1 \le i \le n$ 且 $a_i = 0$），将 $a_i$ 设为 $1$；
2. 选择一对下标 $l$ 和 $r$（满足 $1 \le l \le r \le n$、$a_l = 1$、$a_r = 1$ 且 $a_l + \ldots + a_r \ge \lceil\frac{r - l + 1}{2}\rceil$），将区间 $[l, r]$ 中所有元素设为 $1$。

你的任务是计算，使数组中所有元素都变为 $1$，至少需要多少次第一种操作？

## 输入格式

输入包含多组测试用例。第一行是整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。接下来每个测试用例用一行表示，包含一个整数 $n$（$1 \le n \le 10^5$），表示数组的长度。

需要注意，所有测试用例中 $n$ 的总和没有限制。

## 输出格式

对于每组测试用例，输出一个整数，表示完成任务所需的最少第一种操作次数。

## 说明/提示

- 对于第一个测试用例，你可以对 $i = 1$ 操作一次即可。
- 对于第二个测试用例，可以按以下步骤操作：
  1. 对 $i = 1$ 进行第一种操作，数组变为 $[1, 0]$。
  2. 对 $i = 2$ 进行第一种操作，数组变为 $[1, 1]$。

  第二个测试用例的操作步骤如下图所示：![图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040B/08c860ca61c18c2cea946aa6a8dc785c3721c9f1.png)

- 对于第三个测试用例，可以按以下步骤操作：
  1. 对 $i = 1$ 进行第一种操作，数组变为 $[1, 0, 0, 0]$。
  2. 对 $i = 4$ 进行第一种操作，数组变为 $[1, 0, 0, 1]$。
  3. 对 $l = 1$ 和 $r = 4$ 进行第二种操作，因为 $a_1 + a_2 + a_3 + a_4 = 2$，满足不小于 $\lceil\frac{r - l + 1}{2}\rceil = 2$，所以可以将区间内元素设为 $1$，数组变为 $[1, 1, 1, 1]$。

  第三个测试用例的操作步骤如下图所示：![图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040B/145510fed0c2c1fc91c16be016c113ca0ca5bb2f.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
2
4
20
```

### 输出

```
1
2
2
4
```



---

---
title: "Beautiful Array"
layout: "post"
diff: 普及-
pid: CF2041E
tag: ['数学', '构造']
---

# Beautiful Array

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041E/123e9f2378be455eca9fba5ff4bfa308ab2b1a77.png) Image generated by ChatGPT 4o.A-Ming's birthday is coming and his friend A-May decided to give him an integer array as a present. A-Ming has two favorite numbers $ a $ and $ b $ , and he thinks an array is beautiful if its mean is exactly $ a $ and its median is exactly $ b $ . Please help A-May find a beautiful array so her gift can impress A-Ming.

The mean of an array is its sum divided by its length. For example, the mean of array $ [3, -1, 5, 5] $ is $ 12 \div 4 = 3 $ .

The median of an array is its middle element after sorting if its length is odd, or the mean of two middle elements after sorting if its length is even. For example, the median of $ [1, 1, 2, 4, 8] $ is $ 2 $ and the median of $ [3, -1, 5, 5] $ is $ (3 + 5) \div 2 = 4 $ .

Note that the mean and median are not rounded to an integer. For example, the mean of array $ [1, 2] $ is $ 1.5 $ .

## 输入格式

The only line contains two integers $ a $ and $ b $ .

- $ -100 \leq a, b \leq 100 $ .
- The length of the array must be between $ 1 $ and $ 1000 $ .
- The elements of the array must be integers and their absolute values must not exceed $ 10^6 $ .

## 输出格式

In the first line, print the length of the array.

In the second line, print the elements of the array.

If there are multiple solutions, you can print any. It can be proved that, under the constraints of the problem, a solution always exists.

## 样例 #1

### 输入

```
3 4
```

### 输出

```
4
3 -1 5 5
```

## 样例 #2

### 输入

```
-100 -100
```

### 输出

```
1
-100
```



---

---
title: "Game with Colored Marbles"
layout: "post"
diff: 普及-
pid: CF2042B
tag: ['数学', '贪心']
---

# Game with Colored Marbles

## 题目描述

Alice 和 Bob 在玩一个游戏。一共有 $n$ 个石子，第 $i$ 个的颜色为 $c_i$。Alice 先手，两人轮流取走一颗石子，直到游戏结束。

Alice 的最终分数计算如下：

- 对于每一个颜色 $x$，如果 Alice 有至少一颗该颜色的石子，她获得 $1$ 分。
- 对于每一个颜色 $x$，如果她拥有全部该颜色的石子，她额外获得 $1$ 分（只考虑游戏中出现的颜色）。

比如，假设有颜色为 $[1,3,1,3,4]$ 的五颗石子，Alice 第一次拿第 $1$ 颗，Bob 拿第 $3$ 颗，然后 Alice 拿第 $5$ 颗，Bob 拿第 $2$ 颗，最后 Alice 拿第 $4$ 颗。最终，Alice 获得 $4$ 分：$3$ 分来自拿走至少一颗颜色为 $1,3,4$ 的石子，剩下 $1$ 分来自拿走全部颜色为 $4$ 的石子。**注意这一方案不一定是对双方最优的。**

Alice 想最大化她的分数，而 Bob 想最小化这个分数，假设两人都足够聪明。求 Alice 的最终得分。

## 输入格式

第一行，一个整数 $t$ ($1\le t \le 1000$)，表示数据组数。

对于每组数据，输入两行：

- 第一行，一个整数 $n$ ($1\le n\le 1000$)，表示石子个数。
- 第二行，$n$ 个整数 $c_1,c_2,\cdots,c_n$ ($1\le c_i\le n$)，表示石子的颜色。

保证所有 $n$ 之和不超过 $1000$。

## 输出格式

对于每组数据，输出一行，一个整数，表示 Alice 的最终分数。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
3
5
1 3 1 3 4
3
1 2 3
4
4 4 4 4
```

### 输出

```
4
4
1
```



---

---
title: "Hard Problem"
layout: "post"
diff: 普及-
pid: CF2044C
tag: ['数学']
---

# Hard Problem

## 题目描述

Ball 是折纸大学的一名老师。他的教室有 $2$ 行座位，每行有 $m$ 个座位。

Ball 在教 $a + b + c$ 只猴子，他希望能够让尽可能多的猴子坐在座位上。他知道有 $a$ 只猴子只想坐在第 $1$ 行，有 $b$ 只只想坐在第 $2$ 行，有 $c$ 只对座位没有偏好。每个座位上只能坐一只猴子，且入座的猴子的偏好必须被满足。

Ball 最多可以让多少只猴子就坐？

## 输入格式

第一行包含一个正整数 $t (1 \leq t \leq 10^4)$，代表测试样例数量。

接下来的 $t-1$ 行，每行代表一组测试样例，包括 4 个正整数 $m$ 、 $a$ 、 $b$ 和 $c$ （ $1 \leq m, a, b, c \leq 10^8$ ）。

## 输出格式

对于每组测试样例，输出猴子就坐数的最大值。

## 说明/提示

对于第二组测试样例，有 $6$ 只猴子想坐在第一行，但只有 $3$ 个座位。对座位没有偏好的猴子和喜欢坐在第二行的猴子可以一起坐在第二行。因此，答案是 $3+2=5$ 。

## 样例 #1

### 输入

```
5
10 5 5 10
3 6 1 1
15 14 12 4
1 1 1 1
420 6 9 69
```

### 输出

```
20
5
30
2
84
```



---

---
title: "Alyona and a Square Jigsaw Puzzle"
layout: "post"
diff: 普及-
pid: CF2047A
tag: ['数学']
---

# Alyona and a Square Jigsaw Puzzle

## 题目描述

Alyona 组装了一个特殊的方形拼图。在 $n$ 天中，她的组装规则如下：

- 在第一天，她将中心拼图放在桌子的中心点。
- 在接下来的每一天，她在中心的周围顺时针摆一定数量的拼图，一层拼图全部摆满后才会开始摆新的一层。

下图展示了她前 $14$ 块拼图的摆放方法：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2047A/79d4bc6fb70315d8b0bc2f84e7e9b7aaaaa1456d.png)

不同颜色表示不同的层，第三层还未摆满。如果在某一天，Alyona 没有任何未摆满的拼图层，她就会很开心。给出 Alyona 每天摆放拼图的块数，求 Alyona 开心的天数。

## 输入格式

本题有多组数据。第一行，一个整数 $t$ ($1\le t\le 500$)，表示数据组数。

对于每组数据：

第一行，一个整数 $n$ ($1\le n\le 100$)，表示拼图的天数。

第二行，$n$ 个整数 $a_1,a_2,\cdots,a_n$ ($1\le a_i\le 100, a_1=1$)，表示 Alyona 第 $i$ 天拼的拼图块个数。

保证在每组数据中，最后一天结束后没有未摆满的层。

## 输出格式

对于每组数据，输出一行一个整数，表示 Alyona 开心的天数。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
5
1
1
2
1 8
5
1 3 2 1 2
7
1 2 1 10 2 7 2
14
1 10 10 100 1 1 10 1 10 2 10 2 10 1
```

### 输出

```
1
2
2
2
3
```



---

---
title: "Transfusion"
layout: "post"
diff: 普及-
pid: CF2050B
tag: ['数学']
---

# Transfusion

## 题目描述

现给定一个数组 $a$ 和 数组的长度 $n$。规定在一次操作中，你可以从 $2$ 到 $n-1$ 中选取任意一个数 $i$，完成下面的一个操作：
- 令 $a_{i-1}$ 减 $1$，令 $a_{i+1}$  加 $1$。
- 令 $a_{i-1}$ 加 $1$，令 $a_{i+1}$  减 $1$。

**每次操作都要保证得到的数为非负数。**
在进行若干次操作后，能否使 $a$ 的每个数都相等？

## 输入格式

输入的第一行为一个整数 $t$ $(1≤t≤10^4)$ ，表示测试组数。

对于每组测试数据：

第一行 为一个整数 $n$ $(3≤n≤2 \times 10^5)$ 。  

第二行 由 $n$ 个整数 $a_i$ $( 1≤ai≤10^9 )$ 构成。

保证所有测试组数的 $n$ 总和不会超过 $2 \times10^5$。

## 输出格式

对于每次测试，如果经过若干次操作后，$a$ 的每个数都相等，输出 `“YES”`（不包括引号），否则就输出 `“NO”`（不包括引号）。  
输出不分大小写，也就意味着 `"yes"`, `"YeS"`, `"nO"` 等答案都会被认定为正确答案。

## 样例 #1

### 输入

```
8
3
3 2 1
3
1 1 3
4
1 2 5 4
4
1 6 6 1
5
6 2 1 4 2
4
1 4 2 1
5
3 1 2 1 3
3
2 4 2
```

### 输出

```
YES
NO
YES
NO
YES
NO
NO
NO
```



---

---
title: "Uninteresting Number"
layout: "post"
diff: 普及-
pid: CF2050C
tag: ['数学']
---

# Uninteresting Number

## 题目描述

给定一个数字 $n$，它的长度最多为 $10^5$。

你可以进行以下操作任意次数：选择它的某一位数字，将该数字平方，并将原来的数字替换成平方后的结果。新的数字必须是一个数字（即，如果你选择数字 $x$，那么 $x^2$ 必须小于 $10$）。

你的任务是判断，是否可以通过这些操作，将这个数字变成一个可以被 $9$ 整除的数字？

## 输入格式

第一行输入一个整数 $t$（$1 \le t \le 10^4$）,表示测试用例的个数。

对于每个测试用例：
- 第一行输入一个数字 $n$，该数字没有前导零，并且它的长度不超过 $10^5$。

## 输出格式

对于每个测试用例，输出 "YES" 如果可以通过上述操作得到一个可以被 $9$ 整除的数字，否则输出 "NO"。

你可以随意输出 "YES" 或 "NO" 的大小写形式，比如 "yEs"、"yes"、"Yes" 和 "YES" 都是有效的答案。

## 样例 #1

### 输入

```
9
123
322
333333333333
9997
5472778912773
1234567890
23
33
52254522632
```

### 输出

```
NO
YES
YES
NO
NO
YES
NO
YES
YES
```



---

---
title: "Journey"
layout: "post"
diff: 普及-
pid: CF2051B
tag: ['数学']
---

# Journey

## 题目描述

Monocarp 决定去进行一次漫长的徒步旅行。

他计划，第一天走 $a$ 公里，第二天走 $b$ 公里，第三天走 $c$ 公里，到第四天再像第一天那样走 $a$ 公里，第五天如同第二天走 $b$ 公里，第六天则重复第三天走 $c$ 公里，如此循环下去。

当他走过的总路程达到至少 $n$ 公里时，就完成了整个旅程。你的任务是找出 Monocarp 在哪一天达到了这个目标。

## 输入格式

输入的第一行包含一个整数 $t$，表示测试用例的数量（$1 \le t \le 10^4$）。

接下来的每一行包含四个整数 $n$、$a$、$b$、$c$，分别代表每个测试用例的数据（$1 \le n \le 10^9$; $1 \le a, b, c \le 10^6$）。

## 输出格式

对于每个测试用例，输出一个整数，表示 Monocarp 在走满至少 $n$ 公里并结束旅行的那一天。

## 说明/提示

在第一个例子中，Monocarp 在前四天总共走了 $1 + 5 + 3 + 1 = 10$ 公里。到了第五天，他又走了 $5$ 公里，总数达到 $15$ 公里。因为 $n = 12$，所以 Monocarp 在第五天实现了目标，完成了旅程。

在第二个例子中，Monocarp 第一天就走了 $6$ 公里。而由于 $n = 6$，他实际上一天就完成了旅程。

在第三个例子中，Monocarp 在六天内的总行程为 $3 + 4 + 1 + 3 + 4 + 1 = 16$ 公里。因为 $n = 16$，所以他在第六天达成旅程目标。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
12 1 5 3
6 6 7 4
16 3 4 1
1000000000 1 1 1
```

### 输出

```
5
1
6
1000000000
```



---

---
title: "Tender Carpenter"
layout: "post"
diff: 普及-
pid: CF2053A
tag: ['数学', '贪心']
---

# Tender Carpenter

## 题目描述

I would use a firework to announce, a wave to bid farewell, and a bow to say thanks: bygones are bygones; not only on the following path will I be walking leisurely and joyfully, but also the footsteps won't halt as time never leaves out flowing; for in the next year, we will meet again.

— Cocoly1990, [Goodbye 2022](https://www.luogu.com.cn/problem/P8941)



In his dream, Cocoly would go on a long holiday with no worries around him. So he would try out for many new things, such as... being a carpenter. To learn it well, Cocoly decides to become an apprentice of Master, but in front of him lies a hard task waiting for him to solve.

Cocoly is given an array $ a_1, a_2,\ldots, a_n $ . Master calls a set of integers $ S $ stable if and only if, for any possible $ u $ , $ v $ , and $ w $ from the set $ S $ (note that $ u $ , $ v $ , and $ w $ do not necessarily have to be pairwise distinct), sticks of length $ u $ , $ v $ , and $ w $ can form a non-degenerate triangle $ ^{\text{∗}} $ .

Cocoly is asked to partition the array $ a $ into several (possibly, $ 1 $ or $ n $ ) non-empty continuous subsegments $ ^{\text{†}} $ , such that: for each of the subsegments, the set containing all the elements in it is stable.

Master wants Cocoly to partition $ a $ in at least two different $ ^{\text{‡}} $ ways. You have to help him determine whether it is possible.

 $ ^{\text{∗}} $ A triangle with side lengths $ x $ , $ y $ , and $ z $ is called non-degenerate if and only if:

- $ x + y > z $ ,
- $ y + z > x $ , and
- $ z + x > y $ .

 $ ^{\text{†}} $ A sequence $ b $ is a subsegment of a sequence $ c $ if $ b $ can be obtained from $ c $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

 $ ^{\text{‡}} $ Two partitions are considered different if and only if at least one of the following holds:

- the numbers of continuous subsegments split in two partitions are different;
- there is an integer $ k $ such that the lengths of the $ k $ -th subsegment in two partitions are different.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 200 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \leq n \leq 200 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \leq a_i \leq 10^5 $ ) — the elements in the array $ a $ .

## 输出格式

For each test case, print $ \texttt{YES} $ if there are at least two ways to partition $ a $ , and $ \texttt{NO} $ otherwise.

You can output the answer in any case (upper or lower). For example, the strings $ \texttt{yEs} $ , $ \texttt{yes} $ , $ \texttt{Yes} $ , and $ \texttt{YES} $ will be recognized as positive responses.

## 说明/提示

In the first test case, here are two possible partitions:

- $ [2, 3], [5, 7] $ , since 
  - $ [2, 3] $ is stable because sticks of lengths $ (2, 2, 2), (2, 2, 3), (2, 3, 3), (3, 3, 3) $ respectively can all form non-degenerate triangles.
  - $ [5, 7] $ is stable because sticks of lengths $ (5, 5, 5), (5, 5, 7), (5, 7, 7), (7, 7, 7) $ respectively can all form non-degenerate triangles.
- and $ [2], [3, 5], [7] $ , since 
  - $ [2] $ is stable because sticks of lengths $ (2, 2, 2) $ respectively can form a non-degenerate triangle.
  - $ [3, 5] $ is stable because sticks of lengths $ (3, 3, 3), (3, 3, 5), (3, 5, 5), (5, 5, 5) $ respectively can all form non-degenerate triangles.
  - $ [7] $ is stable because sticks of lengths $ (7, 7, 7) $ respectively can form a non-degenerate triangle.

Note that some other partitions also satisfy the constraints, such as $ [2], [3], [5], [7] $ and $ [2], [3], [5, 7] $ .

In the second test case, Cocoly can only partition each element as a single subsegment, resulting in $ [115], [9], [2], [28] $ . Since we only have one possible partition, the answer is $ \texttt{NO} $ .

In the third test case, please note that the partition $ [8, 4], [1], [6], [2] $ does not satisfy the constraints, because $ \{8, 4\} $ is not a stable set: sticks of lengths $ 4 $ , $ 4 $ , and $ 8 $ cannot form a non-degenerate triangle.

## 样例 #1

### 输入

```
5
4
2 3 5 7
4
115 9 2 28
5
8 4 1 6 2
6
1 5 4 1 4 7
2
100000 100000
```

### 输出

```
YES
NO
NO
YES
YES
```



---

---
title: "Adjacent Digit Sums"
layout: "post"
diff: 普及-
pid: CF2067A
tag: ['数学']
---

# Adjacent Digit Sums

## 题目描述

给定两个数字 $x, y$。你需要判断是否存在一个整数 $n$ 使得 $S(n) = x$ 且 $S(n + 1) = y$。

其中，$S(a)$ 表示数字 $a$ 在十进制系统中的各位数字之和。


## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 500$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含两个整数 $x, y$（$1 \le x \le 1000, 1 \le y \le 1000$）。


## 输出格式

对于每个测试用例，如果不存在符合条件的 $n$，输出 "NO"。否则，输出 "YES"。

每个字母可以以任何大小写形式输出（例如 "YES"、"Yes"、"yes"、"yEs"、"yEs" 均会被识别为肯定答案）。


## 说明/提示

在第一个测试用例中，例如 $n = 100$ 满足条件。此时 $S(100) = 1$，$S(101) = 2$。

在第二个测试用例中，可以证明对于所有 $n$ 均有 $S(n) \neq S(n+1)$，因此答案为 No。

在第四个测试用例中，$n = 10^{111}-1$ 满足条件，这是一个由 $111$ 个 $9$ 组成的数字。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
1 2
77 77
997 999
999 1
1000 1
1 11
18 1
```

### 输出

```
Yes
No
No
Yes
No
No
Yes
```



---

---
title: "Robot Program"
layout: "post"
diff: 普及-
pid: CF2070B
tag: ['模拟', '数学']
---

# Robot Program

## 题目描述

在坐标轴上有一个机器人。初始时，机器人位于点 $x$（$x \ne 0$）。机器人有一个长度为 $n$ 的命令序列，由字符组成，其中 L 表示向左移动一个单位（从点 $p$ 移动到点 $(p-1)$），R 表示向右移动一个单位（从点 $p$ 移动到点 $(p+1)$）。

机器人开始执行这个命令序列（每秒执行一个命令，按顺序执行）。然而，每当机器人到达点 0 时，已执行命令的计数器会被重置（即它会从头开始重新执行整个命令序列）。如果机器人完成了所有命令且未处于 0 点，它将停止运行。

你的任务是计算在接下来的 $k$ 秒内，机器人会进入点 0 多少次。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$x$ 和 $k$（$1 \le n \le 2 \cdot 10^5$；$-n \le x \le n$；$n \le k \le 10^{18}$）。

每个测试用例的第二行包含一个由 $n$ 个字符 L 和/或 R 组成的字符串 $s$。

输入额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——在接下来的 $k$ 秒内机器人进入点 0 的次数。

## 说明/提示

第一个示例中，机器人移动路径为：$2 \rightarrow 1 \rightarrow \underline{0} \rightarrow -1 \rightarrow -2 \rightarrow -1$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，点 0 被进入 1 次。

第二个示例中，机器人移动路径为：$-1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1$。机器人运行了 8 秒，点 0 被进入 4 次。

第三个示例中，机器人移动路径为：$-2 \rightarrow -3 \rightarrow -2 \rightarrow -1 \rightarrow \underline{0} \rightarrow -1$。机器人运行了 5 秒，点 0 被进入 1 次。

第四个示例中，机器人移动路径为：$3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 3 \rightarrow 2$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，未到达点 0。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2 6
LLR
2 -1 8
RL
4 -2 5
LRRR
5 3 7
LRRLL
1 1 1
L
3 -1 4846549234412827
RLR
```

### 输出

```
1
4
1
0
1
2423274617206414
```



---

---
title: "The Play Never Ends"
layout: "post"
diff: 普及-
pid: CF2071A
tag: ['数学']
---

# The Play Never Ends

## 题目描述

我们引入一个双人游戏——乒乓球比赛，该游戏总能决出胜负，不存在平局。

三名玩家 Sosai、Fofo 和 Hohai 希望余生都进行乒乓球比赛。他们决定按照以下规则无限进行比赛：

- 每场比赛中，两名玩家对战，第三名作为观众。
- 为确保公平性，任何玩家不能连续参与三场比赛。若某玩家连续参与两次比赛，则必须在下一场比赛中作为观众，由另外两名玩家对战。否则，胜者将与观众进行下一场比赛，败者转为观众。

现在，完全沉浸在这种比赛无限循环中的玩家们要求你解决以下问题：

给定整数 $k$，判断第一场比赛的观众是否可能在第 $k$ 场比赛中再次成为观众。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 1000$）。接下来是各个测试用例的描述。

每个测试用例仅包含一行，包含一个整数 $k$（$1 \le k \le 10^9$）。

## 输出格式

对于每个测试用例，若第一场比赛的观众可能在第 $k$ 场比赛中成为观众，则输出 "YES"（不带引号），否则输出 "NO"（不带引号）。

答案可以以任意大小写形式输出。例如，"yEs"、"yes"、"Yes" 和 "YES" 都会被识别为肯定回答。

## 说明/提示

第一个测试用例中，第一场比赛的观众已经在第 $1$ 场比赛担任观众。

第二个测试用例中，无论第一场比赛结果如何，第一场比赛的观众都将在第 $2$ 场比赛中参赛。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1
2
333
1000000000
```

### 输出

```
YES
NO
NO
YES
```



---

---
title: "Perfecto"
layout: "post"
diff: 普及-
pid: CF2071B
tag: ['数学', '构造']
---

# Perfecto

## 题目描述

若一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$ 满足：对于每个下标 $i$（$1 \le i \le n$），前 $i$ 个元素的和 $p_1 + p_2 + \ldots + p_i$ 不是完全平方数 $^{\text{†}}$，则称该排列为完美排列。

你需要构造完美排列。给定正整数 $n$，找出一个长度为 $n$ 的完美排列，若不存在则输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（数字 $2$ 重复出现），$[1,3,4]$ 也不是排列（当 $n=3$ 时出现数字 $4$）。

$^{\text{†}}$ 完全平方数是指某个整数的平方，例如 $9=3^2$ 是完全平方数，但 $8$ 和 $14$ 不是。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例仅包含一行，包含一个整数 $n$（$1 \le n \le 5 \cdot 10^5$）。

保证所有测试用例的 $n$ 之和不超过 $10^6$。

## 输出格式

对于每个测试用例：

- 若无解，输出单个整数 $-1$；
- 否则，输出 $n$ 个整数 $p_1,p_2,\ldots,p_n$ —— 你找到的完美排列。

若存在多个解，输出任意一个即可。

## 说明/提示

第一个测试用例中，当 $n = 1$ 时唯一可能的排列是 $p = [1]$，但它不满足完美条件：
- $p_1 = 1 = x^2$（当 $x = 1$ 时成立）。

第二个测试用例中，当 $n = 4$ 时一个可能的完美排列是 $p = [2, 4, 1, 3]$：
- $p_1 = 2 \neq x^2$；
- $p_1 + p_2 = 2 + 4 = 6 \neq x^2$；
- $p_1 + p_2 + p_3 = 2 + 4 + 1 = 7 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 = 2 + 4 + 1 + 3 = 10 \neq x^2$。

第三个测试用例中，当 $n = 5$ 时一个可能的完美排列是 $p = [5, 1, 4, 3, 2]$：
- $p_1 = 5 \neq x^2$；
- $p_1 + p_2 = 5 + 1 = 6 \neq x^2$；
- $p_1 + p_2 + p_3 = 5 + 1 + 4 = 10 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 = 5 + 1 + 4 + 3 = 13 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 + p_5 = 5 + 1 + 4 + 3 + 2 = 15 \neq x^2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
1
4
5
```

### 输出

```
-1
2 4 1 3
5 1 4 3 2
```



---

---
title: "New World, New Me, New Array"
layout: "post"
diff: 普及-
pid: CF2072A
tag: ['数学']
---

# New World, New Me, New Array

## 题目描述

夏目章人（Natsume Akito）刚刚在一个新世界苏醒，便立即收到了他的第一个任务！系统为他提供了一个包含 $ n $ 个零的数组 $ a$，以及两个整数 $ k $ 和 $ p$。

在每次操作中，章人需要选择两个整数 $ i $ 和 $ x$（满足 $ 1 \le i \le n $ 且 $-p \le x \le p$），然后执行赋值操作 $ a_i = x$。

章人仍未完全适应如何控制他的新身体，因此请你帮他计算使数组所有元素之和等于 $ k $ 所需的最少操作次数，或者告诉他这是不可能的。

## 输入格式

第一行输入包含一个整数 $ t $（$ 1 \le t \le 1000$）—— 测试用例的数量。

每个测试用例的唯一一行包含三个整数 $ n $, $ k $, $ p$（$ 1 \le n \le 50$，$-2500 \le k \le 2500$，$ 1 \le p \le 50$）—— 分别表示数组长度、目标总和以及可替换数值的范围边界。

## 输出格式

对于每个测试用例，输出使数组最终总和为 $ k $ 所需的最少操作次数；若无法达成，则输出 $-1$。

## 说明/提示

第五个样例中，数组初始总和为零，因此无需任何操作。

第六个样例中，数组能达到的最大总和为 $ 9$（将唯一元素赋值为 $ 9$），因此无法通过任何操作得到总和 $ 10$。

第七个样例中，仅需一次操作 $ a_3 = -7$ 即可达成目标。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
21 100 10
9 -420 42
5 -7 2
13 37 7
10 0 49
1 10 9
7 -7 7
20 31 1
```

### 输出

```
10
-1
4
6
0
-1
1
-1
```



---

---
title: "The Third Side"
layout: "post"
diff: 普及-
pid: CF2074B
tag: ['数学', '贪心']
---

# The Third Side

## 题目描述

粉色士兵们给了你一个由 $n$ 个正整数组成的序列 $a$。

你必须重复执行以下操作直到序列中只剩下 $1$ 个元素：

- 选择两个不同的下标 $i$ 和 $j$
- 选择一个正整数 $x$，使得存在一个非退化三角形$^{\text{∗}}$，其边长为 $a_i$、$a_j$ 和 $x$
- 删除这两个元素 $a_i$ 和 $a_j$，并将 $x$ 追加到序列 $a$ 的末尾

请找出最终序列中唯一剩余元素可能的最大值。

$^{\text{∗}}$当边长为 $a$、$b$、$c$ 的三角形满足 $a + b > c$、$a + c > b$ 且 $b + c > a$ 时，该三角形是非退化的。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 1000$）——序列 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在单独一行中输出最终剩余元素的可能最大值。


## 说明/提示

在第一个测试用例中，序列已经只有一个元素。最终剩余元素的值为 $10$。

在第二个测试用例中，初始序列为 $[998, 244, 353]$。以下操作序列是合法的：

1. 删除 $a_2 = 244$ 和 $a_3 = 353$，并追加 $596$ 到序列末尾。此时 $a$ 变为 $[998, 596]$
2. 删除 $a_1 = 998$ 和 $a_2 = 596$，并追加 $1593$ 到序列末尾。此时 $a$ 变为 $[1593]$

可以证明最终元素不可能超过 $1593$。因此答案为 $1593$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1
10
3
998 244 353
5
1 2 3 4 5
9
9 9 8 2 4 4 3 5 3
```

### 输出

```
10
1593
11
39
```



---

---
title: "To Zero"
layout: "post"
diff: 普及-
pid: CF2075A
tag: ['数学', '贪心']
---

# To Zero

## 题目描述

给定两个整数 $n$ 和 $k$，其中 $k$ 是不小于 $3$ 的奇数。你的任务是将 $n$ 变为 $0$。

为此，你可以执行以下操作任意次数：从 $1$ 到 $k$ 中选择一个数 $x$，并将其从 $n$ 中减去。但需注意：
- 若当前 $n$ 是偶数（能被 $2$ 整除），则 $x$ 也必须是偶数；
- 若当前 $n$ 是奇数（不能被 $2$ 整除），则 $x$ 也必须是奇数。

在不同操作中，可以选择相同的 $x$ 值，但没有强制要求。因此，重复使用相同的 $x$ 没有限制。

请计算将 $n$ 变为 $0$ 所需的最少操作次数。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10000$）——测试用例的数量。

每个测试用例占一行，包含两个整数 $n$ 和 $k$（$3 \le k \le n \le 10^9$，且 $k$ 为奇数）。

## 输出格式

对于每个测试用例，输出一个整数——将 $n$ 变为 $0$ 所需的最少操作次数。

## 说明/提示

第一个示例中，可以按以下步骤操作：
1. 从 $39$ 中减去 $5$（奇校验），得到 $34$；
2. 执行五次减去 $6$（偶校验）的操作，得到 $4$；
3. 最后减去 $4$，得到 $0$。

第二个示例中，可以：
1. 先减去 $3$（奇校验）一次；
2. 再执行三次减去 $2$（偶校验）的操作。

第三个示例中，可以直接执行三次减去 $2$（偶校验）的操作。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
39 7
9 3
6 3
999967802 3
5 5
6 5
999999999 3
1000000000 3
```

### 输出

```
7
4
3
499983901
1
2
499999999
500000000
```



---

---
title: "Final Verdict"
layout: "post"
diff: 普及-
pid: CF2078A
tag: ['数学']
---

# Final Verdict

## 题目描述

[Testify - void (Mournfinale) feat. 星熊南巫](https://www.youtube.com/watch?v=xkUN_9HFNPg)

给定一个长度为 $n$ 的数组 $a$，你需要重复执行以下操作，直到 $a$ 的长度变为 $1$：

选择一个满足 $k < |a|$ 且 $\frac{|a|}{k}$ 为整数的正整数 $k$。将 $a$ 分割成 $k$ 个子序列 $^{\text{∗}}$ $s_1, s_2, \ldots, s_k$，并满足以下条件：
- $a$ 的每个元素恰好属于一个子序列。
- 每个子序列的长度相等。

之后，将 $a$ 替换为 $\left[ \operatorname{avg}(s_1), \operatorname{avg}(s_2), \ldots, \operatorname{avg}(s_k) \right]$，其中 $\operatorname{avg}(s) = \frac{\sum_{i = 1}^{|s|} s_i}{|s|}$ 表示子序列所有值的平均值。例如，$\operatorname{avg}([1, 2, 1, 1]) = \frac{5}{4} = 1.25$。

你的任务是判断是否存在一系列操作，使得最终 $a = [x]$。

$^{\text{∗}}$ 如果序列 $x$ 可以通过删除序列 $y$ 中的若干元素（可能为零个或全部）得到，则称 $x$ 是 $y$ 的子序列。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 500$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $x$（$1 \leq n, x \leq 100$）——数组 $a$ 的长度和最终期望的值。

第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \leq a_i \leq 100$）——数组 $a$。

## 输出格式

对于每个测试用例，如果存在满足条件的操作序列，输出 "YES"（不带引号），否则输出 "NO"（不带引号）。

你可以以任意大小写形式输出答案（例如字符串 "yES"、"yes" 和 "Yes" 均会被识别为肯定回答）。

## 说明/提示

在第一个测试用例中，$x = 3$ 且 $a = [3]$ 已经满足条件。

在第二个测试用例中，$x = 9$，且不存在任何操作序列能使最终 $a = [9]$。

在第三个测试用例中，$x = 9$，存在以下一种可能的操作序列：
1. 选择 $k = 2$，$s_1 = [1, 12, 8]$ 和 $s_2 = [9, 14, 10]$。此时 $a = [\operatorname{avg}(s_1), \operatorname{avg}(s_2)] = [7, 11]$。
2. 选择 $k = 1$ 且 $s_1 = [7, 11]$。此时 $a = [\operatorname{avg}(s_1)] = [9]$。

在第四个测试用例中，$x = 10$，存在以下一种可能的操作序列：
1. 选择 $k = 1$ 且 $s_1 = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]$。此时 $a = [\operatorname{avg}(s_1)] = [10]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
1 3
3
4 9
7 11 2 5
6 9
1 9 14 12 10 8
10 10
10 10 10 10 10 10 10 10 10 10
```

### 输出

```
YES
NO
YES
YES
```



---

---
title: "Vicious Labyrinth"
layout: "post"
diff: 普及-
pid: CF2078B
tag: ['数学']
---

# Vicious Labyrinth

## 题目描述

[Axium Crisis - ak+q](https://youtu.be/1HyuI8Bvnsg?si=6amlU5OPKnJiydZs)

迷宫中有 $n$ 个单元格，其中单元格 $i$（$1 \leq i \leq n$）距离出口有 $n - i$ 公里。特别地，单元格 $n$ 就是出口。注意每个单元格仅与出口相连，无法从其他任何单元格直接到达。

每个单元格最初恰好困住一个人。你希望通过在每个单元格 $i$（$1 \leq i \leq n$）安装传送器来帮助所有人尽可能接近出口，该传送器会将单元格 $i$ 中的人传送到另一个单元格 $a_i$。

迷宫主人发现了你的行为。她觉得有趣，但要求你满足以下条件：
- 每个人都必须恰好使用传送器 $k$ 次。
- 任何单元格的传送器都不能将人传送到自身所在的单元格。形式化地说，对所有 $1 \leq i \leq n$ 有 $a_i \neq i$。

你需要找到一个传送器配置方案，在满足迷宫主人限制条件的前提下，使所有人在使用传送器恰好 $k$ 次后到出口的距离之和最小。若存在多个可行方案，输出任意一个即可。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数 $t$（$1 \le t \le 10^4$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$2 \leq n \leq 2 \cdot 10^5$，$1 \leq k \leq 10^9$）——迷宫中的单元格数量及参数 $k$。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，按顺序输出 $n$ 个整数——传送器的目标单元格 $a_1, a_2, \ldots, a_n$（需满足 $1 \leq a_i \leq n$ 且 $a_i \neq i$）。

## 说明/提示

第一个测试用例中，每个人的位置变化如下：
- 传送前：$[1, 2]$
- 第一次传送后：$[2, 1]$

距离之和为 $(2-2) + (2-1) = 1$，这是可能的最小值。

第二个测试用例中，每个人的位置变化如下：
- 传送前：$[1, 2, 3]$
- 第一次传送后：$[2, 3, 2]$
- 第二次传送后：$[3, 2, 3]$

距离之和为 $(3-3) + (3-2) + (3-3) = 1$，这是可能的最小值。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
2 1
3 2
```

### 输出

```
2 1
2 3 2
```



---

---
title: "Max and Mod"
layout: "post"
diff: 普及-
pid: CF2084A
tag: ['数学']
---

# Max and Mod

## 题目描述

给定一个整数 $n$。请找出任意一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$，满足以下条件：

- 对于所有 $2 \le i \le n$，满足 $\max(p_{i - 1}, p_i) \bmod i$ $^{\text{†}}$ $= i - 1$。

如果无法找到这样的排列 $p$，请输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

$^{\text{†}}$ $x \bmod y$ 表示 $x$ 除以 $y$ 的余数。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 99$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 100$）。

## 输出格式

对于每个测试用例：

- 如果不存在满足条件的排列 $p$，输出一个整数 $-1$。
- 否则，输出 $n$ 个整数 $p_1, p_2, \ldots, p_n$ —— 你找到的排列 $p$。如果有多个答案，输出任意一个即可。

## 说明/提示

在第一个测试用例中，无法找到满足条件的排列 $p$，因此输出 $-1$。

在第四个测试用例中，$p = [1, 5, 2, 3, 4]$ 满足条件：

- 对于 $i = 2$，$\max(p_1, p_2) = 5$ 且 $5 \bmod 2 = 1$。
- 对于 $i = 3$，$\max(p_2, p_3) = 5$ 且 $5 \bmod 3 = 2$。
- 对于 $i = 4$，$\max(p_3, p_4) = 3$ 且 $3 \bmod 4 = 3$。
- 对于 $i = 5$，$\max(p_4, p_5) = 4$ 且 $4 \bmod 5 = 4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2
3
4
5
```

### 输出

```
-1
3 2 1
-1
1 5 2 3 4
```



---

---
title: "MIN = GCD"
layout: "post"
diff: 普及-
pid: CF2084B
tag: ['数学', '分类讨论']
---

# MIN = GCD

## 题目描述

给定一个长度为 $n$ 的正整数序列 $a$。判断是否可以重新排列 $a$，使得存在一个整数 $i$（$1 \le i < n$）满足：
$$
\min([a_1, a_2, \ldots, a_i]) = \gcd([a_{i+1}, a_{i+2}, \ldots, a_n]).
$$
其中，$\gcd(c)$ 表示 $c$ 的[最大公约数](https://en.wikipedia.org/wiki/Greatest_common_divisor)，即能整除 $c$ 中所有整数的最大正整数。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 10^5$）。  
第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^{18}$）。  

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，如果可能，输出 "Yes"；否则输出 "No"。  

答案可以以任意大小写形式输出（如 "yEs"、"yes"、"Yes" 或 "YES" 均被视为肯定回答）。


## 说明/提示

- 在第一个测试用例中，将 $a$ 重新排列为 $[1, 1]$ 并令 $i=1$，则 $\min([1]) = \gcd([1])$。  
- 在第二个测试用例中，可以证明不可能满足条件。  
- 在第三个测试用例中，将 $a$ 重新排列为 $[3, 2, 2]$ 并令 $i=2$，则 $\min([3, 2]) = \gcd([2])$。  
- 在第五个测试用例中，将 $a$ 重新排列为 $[3, 4, 5, 6, 9]$ 并令 $i=3$，则 $\min([3, 4, 5]) = \gcd([6, 9])$。  

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
2
1 1
2
1 2
3
2 2 3
3
2 3 4
5
4 5 6 9 3
3
998244359987710471 99824435698771045 1000000007
6
1 1 4 5 1 4
```

### 输出

```
Yes
No
Yes
No
Yes
Yes
Yes
```



---

---
title: "Combination Lock"
layout: "post"
diff: 普及-
pid: CF2091C
tag: ['数学', '构造']
---

# Combination Lock

## 题目描述

在 IT Campus "NEIMARK" 中，有几个开发重大编程竞赛题目的绝密房间。要进入其中一个房间，必须通过选择正确的密码来解锁一个圆形锁。该密码每天更新一次。

今天的密码是一个从 $1$ 到 $n$ 的排列$$$^{\text{∗}}$$$，且满足其每个循环位移$$$^{\text{†}}$$$中恰好有一个固定点。也就是说，在每一个循环位移中，存在且仅存在一个元素，其值等于它在排列中的位置。

请输出任意一个满足此条件的有效排列。请注意，有效的排列可能不存在，此时请输出 $-1$。

$$$^{\text{∗}}$$$排列的定义是一个长度为 $n$ 的序列，包含从 $1$ 到 $n$ 的整数，且每个数字恰好出现一次。例如，$(2\ 1\ 3)$、$(1)$、$(4\ 3\ 1\ 2)$ 是排列；而 $(1\ 2\ 2)$、$(3)$、$(1\ 3\ 2\ 5)$ 不是排列。

$$$^{\text{†}}$$$数组的循环位移是指将最后一个元素移动到数组开头得到的数组。一个长度为 $n$ 的排列恰好有 $n$ 个循环位移。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 500$)。接下来是每个测试用例的描述。

每个测试用例单独一行，包含一个整数 $n$ ($1 \leq n \leq 2 \cdot 10^5$)。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。


## 输出格式

对于每个测试用例，输出满足条件的排列。如果存在多个解，输出任意一个即可。如果不存在符合条件的排列，输出 $-1$。


## 说明/提示

在第二个样例中，存在一个排列使得每个循环位移中都有一个固定点（用深红色标出）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091C/97f07d8865b709e2ac05cf6cf0c154be7dc52ee5.png)  
第一行表示元素的位置编号，第二行展示了目标排列的所有循环位移。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
5
3
```

### 输出

```
-1
4 1 3 5 2
1 3 2
```



---

---
title: "Kamilka and the Sheep"
layout: "post"
diff: 普及-
pid: CF2092A
tag: ['数学', '排序']
---

# Kamilka and the Sheep

## 题目描述

Kamilka 有一群由 $n$ 只绵羊组成的羊群，第 $i$ 只绵羊的美丽值为 $a_i$。所有 $a_i$ 均互不相同。清晨已至，需要给绵羊喂食。Kamilka 可以选择一个非负整数 $d$ 并给每只绵羊喂食 $d$ 捆草。此后，每只绵羊的美丽值将增加 $d$。

傍晚时，Kamilka 必须选择恰好两只绵羊带往山区。若这两只绵羊的美丽值（在喂食后）分别为 $x$ 和 $y$，则 Kamilka 此次散步的乐趣等于 $\gcd(x, y)$，其中 $\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

任务是通过合理选择 $d$，求出 Kamilka 能获得的最大可能乐趣。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$ ($1 \leq t \leq 500$)，表示测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($2 \leq n \leq 100$)，表示 Kamilka 拥有的绵羊数量。

每个测试用例的第二行包含 $n$ 个互不相同的整数 $a_1, a_2, \ldots, a_n$ ($1 \leq a_i \leq 10^9$)，表示绵羊的美丽值。

保证所有 $a_i$ 均互不相同。

## 输出格式

对于每个测试用例，输出一个整数：Kamilka 能获得的最大可能乐趣。


## 说明/提示

第一个测试用例中，选择 $d=1$ 可行。此时乐趣为 $\gcd(1+1, 3+1)=\gcd(2, 4)=2$。可以证明无法获得更大的答案。

第二个测试用例中，选择 $d=3$。此时乐趣为 $\gcd(5+3, 1+3)=\gcd(8, 4)=4$。因此该测试用例的答案为 $4$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
2
1 3
5
5 4 3 2 1
3
5 6 7
3
1 11 10
```

### 输出

```
2
4
2
10
```



---

---
title: "Asuna and the Mosquitoes"
layout: "post"
diff: 普及-
pid: CF2092C
tag: ['数学']
---

# Asuna and the Mosquitoes

## 题目描述

在 Asuna 生日时，她的 $n$ 位仰慕者每人赠送了一座塔。第 $i$ 位仰慕者赠送的塔高度为 $a_i$。

Asuna 将礼物的美观度定义为 $\max(a_1, a_2, \ldots, a_n)$。她可以执行以下操作任意次数（包括零次）：

- 选择满足 $1 \leq i \neq j \leq n$ 的两个下标，使得 $a_i + a_j$ 为奇数且 $a_i > 0$。随后将 $a_i$ 减少 $1$，并将 $a_j$ 增加 $1$。

容易验证，在操作过程中塔的高度始终保持非负。请帮助 Asuna 求出经过任意次操作后可能达到的最大美观度。

## 输入格式

每个测试包含多个测试用例。输入数据第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) —— 测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($1 \leq n \leq 2 \cdot 10^5$) —— Asuna 的仰慕者数量。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ($1 \leq a_i \leq 10^9$) —— 各塔的高度。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数：Asuna 能获得的最大美观度。


## 说明/提示

第一个测试用例中，没有满足操作条件的塔对，因此无法进行任何操作。此时答案为 $\max(5, 3, 9) = 9$。

第二个测试用例中，可以对 $i=2$ 和 $j=1$ 执行两次操作。操作后数组变为：$a = [5, 0]$，因此答案为 5。

第三个测试用例中，可以执行以下操作序列：

1. 对 $i=1$ 和 $j=2$ 执行操作：  
   $$[1, 2, 2, 1] \quad \rightarrow \quad [0, 3, 2, 1]$$
2. 对 $i=3$ 和 $j=2$ 执行操作：  
   $$[0, 3, 2, 1] \quad \rightarrow \quad [0, 4, 1, 1]$$
3. 对 $i=3$ 和 $j=2$ 执行操作：  
   $$[0, 4, 1, 1] \quad \rightarrow \quad [0, 5, 0, 1]$$

此时 $\max(0, 5, 0, 1) = 5$，因此答案为 5。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
5 3 9
2
3 2
4
1 2 2 1
5
5 4 3 2 9
```

### 输出

```
9
5
5
21
```



---

---
title: "Ideal Generator"
layout: "post"
diff: 普及-
pid: CF2093A
tag: ['数学']
---

# Ideal Generator

## 题目描述

我们称一个由 $k$ 个正整数组成的数组 $a$ 为回文数组，如果 $[a_1, a_2, \dots, a_k] = [a_k, a_{k-1}, \dots, a_1]$。例如，数组 $[1, 2, 1]$ 和 $[5, 1, 1, 5]$ 是回文数组，而数组 $[1, 2, 3]$ 和 $[21, 12]$ 则不是。

我们称一个数 $k$ 为理想生成器，如果对于任意整数 $n$（$n \ge k$），$n$ 都可以表示为一个长度恰好为 $k$ 的回文数组的元素之和。数组中的每个元素都必须大于 $0$。

例如，数字 $1$ 是一个理想生成器，因为任何自然数 $n$ 都可以用数组 $[n]$ 来生成。然而，数字 $2$ 不是一个理想生成器——不存在长度为 $2$ 的回文数组，其元素之和为 $3$。

判断给定的数字 $k$ 是否为理想生成器。


## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$）——测试用例的数量。

每个测试用例的第一行也是唯一一行包含一个整数 $k$（$1 \le k \le 1000$）。


## 输出格式

对于每个数字 $k$，如果它是理想生成器，则输出 "YES"，否则输出 "NO"。

你可以以任何大小写形式输出 "Yes" 和 "No"（例如，字符串 "yES"、"yes" 和 "Yes" 都会被识别为肯定回答）。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1
2
3
73
1000
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
title: "Bobritto Bandito"
layout: "post"
diff: 普及-
pid: CF2094B
tag: ['数学']
---

# Bobritto Bandito

## 题目描述

在 Bobritto Bandito 居住的家乡，有一条无限延伸的数轴，上面分布着无数栋房屋，分别位于 $ \ldots, -2, -1, 0, 1, 2, \ldots $ 的位置。在第 $0$ 天时，他通过让 $0$ 号房屋的居民感染病毒，引发了一场瘟疫。在接下来的每一天，瘟疫都会恰好蔓延到一个与已感染房屋相邻的健康房屋。可以证明，每一天被感染的房屋都会形成一个连续的区间。

我们用 $[l, r]$ 表示从第 $l$ 栋房屋到第 $r$ 栋房屋的区间。已知在第 $n$ 天时，区间 $[l, r]$ 被完全感染。请找出在第 $m$ 天（$m \le n$）时可能被感染的任意一个区间 $[l', r']$。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 100$）——独立测试用例的数量。

每个测试用例仅包含一行，四个整数 $n$、$m$、$l$ 和 $r$（$1 \leq m \leq n \leq 2000$，$-n \leq l \leq 0 \leq r \leq n$，且 $r - l = n$）。

## 输出格式

对于每个测试用例，在一行中输出两个整数 $l'$ 和 $r'$。如果存在多个解，输出任意一个即可。

## 说明/提示

在第一个测试用例中，可能的情况是：
- 第 $1$ 天时感染区间为 $[-1,0]$
- 第 $2$ 天时为 $[-1,1]$
- 第 $3$ 天时为 $[-2,1]$

因此，$[-1,1]$ 是一个有效的输出。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 2 -2 2
4 1 0 4
3 3 -1 2
9 8 -6 3
```

### 输出

```
-1 1
0 1
-1 2
-5 3
```



---

---
title: "Wonderful Gloves"
layout: "post"
diff: 普及-
pid: CF2096B
tag: ['数学', '贪心']
---

# Wonderful Gloves

## 题目描述

你是许多彩色手套的骄傲拥有者，并将它们存放在一个抽屉里。每只手套的颜色编号为 $1$ 到 $n$。具体来说，对于每个 $i$（从 $1$ 到 $n$），你有 $l_i$ 只左手手套和 $r_i$ 只右手手套，颜色均为 $i$。

不幸的是，现在是深夜，你无法看清任何手套的颜色。换句话说，只有当你从抽屉中取出手套时，才能知道它的颜色和类型（左手或右手）。

颜色为 $i$ 的一副匹配手套由一只左手手套和一只右手手套组成（颜色均为 $i$）。请计算你需要从抽屉中取出的最少手套数量，以确保至少有 $k$ 副不同颜色的匹配手套。

形式化地说，找到最小的正整数 $x$，满足：
- 无论你从抽屉中取出哪 $x$ 只手套，总能保证至少有 $k$ 副不同颜色的匹配手套。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$（$1 \le t \le 10^4$）。接下来是各个测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $k$（$1 \leq k \leq n \leq 2 \cdot 10^5$）——不同颜色的数量，以及所需的不同颜色匹配手套的最小对数。

第二行包含 $n$ 个整数 $l_1, l_2, \ldots, l_n$（$1 \leq l_i \leq 10^9$）——每种颜色 $i$ 的左手手套数量。

第三行包含 $n$ 个整数 $r_1, r_2, \ldots, r_n$（$1 \leq r_i \leq 10^9$）——每种颜色 $i$ 的右手手套数量。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——你需要从抽屉中取出的最少手套数量。


## 说明/提示

在第一个测试用例中，你必须取出所有手套，因此答案是 $6$。

在第二个测试用例中，答案是 $101$。如果你取出 $100$ 只或更少的手套，那么可能所有取出的都是左手手套，这意味着你无法得到任何一副匹配手套。

在第三个测试用例中，答案是 $303$。如果你只取出 $302$ 只手套，那么可能出现以下情况：
- 颜色 $1$：$100$ 只左手手套，$200$ 只右手手套
- 颜色 $2$：$1$ 只左手手套，$0$ 只右手手套
- 颜色 $3$：$0$ 只左手手套，$1$ 只右手手套

此时你只有颜色 $1$ 的多副匹配手套，无法满足至少 $2$ 副不同颜色匹配手套的要求。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3 3
1 1 1
1 1 1
1 1
100
1
3 2
100 1 1
200 1 1
5 2
97 59 50 87 36
95 77 33 13 74
10 6
97 59 50 87 36 95 77 33 13 74
91 14 84 33 54 89 68 34 14 15
```

### 输出

```
6
101
303
481
1010
```



---

---
title: "Dinner Time"
layout: "post"
diff: 普及-
pid: CF2102A
tag: ['数学', '贪心']
---

# Dinner Time

## 题目描述

给定四个整数 $n$、$m$、$p$ 和 $q$，判断是否存在一个整数数组 $a_1, a_2, \ldots, a_n$（元素可以为负）满足以下条件：

- 数组中所有元素的和等于 $m$：
  $$a_1 + a_2 + \ldots + a_n = m$$
- 每 $p$ 个连续元素的和都等于 $q$：
  $$a_i + a_{i + 1} + \ldots + a_{i + p - 1} = q,\qquad\text{对于所有 }1 \le i \le n - p + 1$$

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行也是唯一一行包含四个整数 $n$、$m$、$p$ 和 $q$（$1 \le p \le n \le 100$，$1 \le q, m \le 100$）——分别表示数组长度、元素总和、子段长度和子段总和。


## 输出格式

对于每个测试用例，如果存在满足上述条件的数组，输出"YES"（不带引号），否则输出"NO"（不带引号）。

你可以以任意大小写形式输出"YES"和"NO"（例如字符串"yES"、"yes"和"Yes"都会被识别为有效响应）。


## 说明/提示

在第一个测试用例中，满足条件的数组示例是 $[1, 0, 1]$。这是因为：
- $a_1 + a_2 + a_3 = 1 + 0 + 1 = 2 = m$
- $a_1 + a_2 = 1 + 0 = 1 = q$
- $a_2 + a_3 = 0 + 1 = 1 = q$

在第二个测试用例中，唯一满足条件的数组是 $[1]$。

在第三个测试用例中，满足条件的数组示例是 $[-2, 5, -2, 5, -2]$。

在第四个测试用例中，可以证明不存在满足条件的数组。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3 2 2 1
1 1 1 1
5 4 2 3
10 7 5 2
4 4 1 3
```

### 输出

```
YES
YES
YES
NO
NO
```



---

---
title: "Common Multiple"
layout: "post"
diff: 普及-
pid: CF2103A
tag: ['数学', '贪心']
---

# Common Multiple

## 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$。我们称数组 $x_1, x_2, \ldots, x_m$ 是美丽的，如果存在一个数组 $y_1, y_2, \ldots, y_m$ 满足以下条件：
- $y$ 数组中的元素互不相同（即对于所有 $1 \le i < j \le m$ 有 $y_i \neq y_j$）
- 对于所有 $1 \le i \le m$，$x_i$ 和 $y_i$ 的乘积都相同（即对于所有 $1 \le i < j \le m$ 有 $x_i \cdot y_i = x_j \cdot y_j$）

你的任务是找出数组 $a$ 的最长子序列 $^{\text{∗}}$ 的长度，使得这个子序列是美丽的。

$^{\text{∗}}$ 序列 $b$ 是序列 $a$ 的子序列，当且仅当 $b$ 可以通过从 $a$ 中删除任意数量（可以是零个或全部）的元素得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 500$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 100$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）——数组 $a$ 的元素。

注意题目没有对所有测试用例的 $n$ 之和做出限制。

## 输出格式

对于每个测试用例，输出数组 $a$ 的最长美丽子序列的长度。


## 说明/提示

在第一个测试用例中，整个数组 $a = [1, 2, 3]$ 已经是美丽的。一个可能的 $y$ 数组是 $[6, 3, 2]$，这满足条件因为：
- $y$ 数组元素互不相同
- $1 \cdot 6 = 2 \cdot 3 = 3 \cdot 2 = 6$

在第二个测试用例中，子序列 $[3, 1, 4, 5]$ 是美丽的。一个可能的 $y$ 数组是 $[20, 60, 15, 12]$。可以证明整个数组 $a = [3, 1, 4, 1, 5]$ 不是美丽的，因此最长的美丽子序列长度是 $4$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
3
1 2 3
5
3 1 4 1 5
1
1
```

### 输出

```
3
4
1
```



---

---
title: "Binary Typewriter"
layout: "post"
diff: 普及-
pid: CF2103B
tag: ['数学', '分类讨论']
---

# Binary Typewriter

## 题目描述

给定一个长度为 $n$ 的二进制字符串 $s$ 和一个带有两个按钮（0 和 1）的打字机。初始时，你的手指放在按钮 0 上。你可以执行以下两种操作：

1. 按下当前手指所在的按钮。这将打出该按钮上的字符。
2. 将手指移动到另一个按钮。如果手指在按钮 0 上，则移动到按钮 1，反之亦然。

二进制字符串的代价定义为输入整个字符串所需的最少操作次数。

在输入之前，你可以选择最多反转 $s$ 的一个子串 $^{\text{∗}}$。更正式地说，你可以选择两个下标 $1 \le l \le r \le n$，并将子串 $s_{l \ldots r}$ 反转，得到新字符串 $s_1s_2 \ldots s_{l-1}s_rs_{r-1} \ldots s_ls_{r+1} \ldots s_n$。

你的任务是找出在最多进行一次子串反转后，所有可能得到的字符串中的最小可能代价。

$^{\text{∗}}$ 字符串 $a$ 是字符串 $b$ 的子串，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）字符得到。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——二进制字符串 $s$ 的长度。

每个测试用例的第二行包含一个二进制字符串 $s_1s_2 \ldots s_n$（$s_i = \mathtt{0}$ 或 $s_i = \mathtt{1}$）——二进制字符串 $s$ 的字符。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出在最多进行一次子串反转后，字符串 $s$ 的最小代价。


## 说明/提示

在第一个测试用例中，我们可以选择不反转任何子串。我们可以执行操作 1 三次来输入 000。

在第二个测试用例中，我们可以选择不反转任何子串。我们可以执行操作 2 将手指移动到按钮 1，然后执行操作 1 三次来输入 111。

在第三个测试用例中，我们可以选择不反转任何子串。我们可以执行操作 1 输入 0，然后执行操作 2 将手指移动到按钮 1，最后执行操作 1 两次输入 11，最终以 4 次操作得到字符串 011。

在第四个测试用例中，我们可以反转子串 $s_{1 \ldots 3}$，得到字符串 001。我们可以执行操作 1 两次输入 00，然后执行操作 2 将手指移动到按钮 1，最后执行操作 1 一次输入 1，最终以 4 次操作得到字符串 001。

在第五个测试用例中，我们可以反转子串 $s_{2 \ldots 3}$，得到字符串 11001。该字符串的代价为 8，操作序列如下：
- 执行操作 2 将手指移动到按钮 1。
- 执行操作 1 两次输入 11。
- 执行操作 2 将手指移动到按钮 0。
- 执行操作 1 两次输入 00。
- 执行操作 2 将手指移动到按钮 1。
- 执行操作 1 一次输入 1。

在第六个测试用例中，我们可以反转子串 $s_{5 \ldots 17}$，得到字符串 1101111011001001000。可以证明，输入该二进制字符串所需的最少操作次数为 29。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
3
000
3
111
3
011
3
100
5
10101
19
1101010010011011100
```

### 输出

```
3
4
4
4
8
29
```



---

---
title: "Three Decks"
layout: "post"
diff: 普及-
pid: CF2104A
tag: ['数学']
---

# Three Decks

## 题目描述

Monocarp 在桌上依次摆放了三副牌堆。第一副牌堆有 $a$ 张牌，第二副有 $b$ 张牌，第三副有 $c$ 张牌，且满足 $a < b < c$。

Monocarp 想从第三副牌堆中取出若干张牌（至少取一张，但不超过 $c$ 张），并将这些牌分配到前两副牌堆中，使得每张被取出的牌最终要么进入第一副牌堆，要么进入第二副牌堆。允许将所有从第三副牌堆取出的牌都分配到同一副牌堆中。

你的任务是判断 Monocarp 能否通过上述操作使得三副牌堆的牌数相同。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的唯一一行包含三个整数 $a$、$b$ 和 $c$（$1 \le a, b, c \le 10^8$）——分别表示第一、第二和第三副牌堆的牌数。

输入数据的额外约束：$a < b < c$。

## 输出格式

对于每个测试用例，如果 Monocarp 可以通过描述的操作使得三副牌堆的牌数相同，则输出 "YES"（不带引号）；否则输出 "NO"（不带引号）。


## 说明/提示

在第一个测试用例中，Monocarp 需要从第三副牌堆取出 $4$ 张牌，将其中 $3$ 张放入第一副牌堆，$1$ 张放入第二副牌堆。这样三副牌堆都将有 $6$ 张牌。

在第二个测试用例中，无法使三副牌堆的牌数相同。

在第三个测试用例中，Monocarp 需要从第三副牌堆取出 $2$ 张牌并全部放入第一副牌堆。这样三副牌堆都将有 $5$ 张牌。

在第四个测试用例中，同样无法使三副牌堆的牌数相同。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3 5 10
12 20 30
3 5 7
1 5 6
```

### 输出

```
YES
NO
YES
NO
```



---

---
title: "LRC and VIP"
layout: "post"
diff: 普及-
pid: CF2107A
tag: ['数学']
---

# LRC and VIP

## 题目描述

给你一个长为 $n$ 的数组 $a=(a_1,a_2,\cdots,a_n)$。

你需要把它分成两个子序列 $B$ 和 $C$，使得：
- $a$ 中的每个元素都属于两个子序列中的一个。
- 两个子序列都至少包含一个元素。
- 两个子序列的最大公因数不相等。

请判断是否有解，如果有解，请给出方案。

[最大公因数的定义——维基百科](https://en.wikipedia.org/wiki/Greatest_common_divisor)

## 输入格式

多组数据，第一行一个整数，为数据组数 $t(1\le t\le 500)$。

对于每组数据：第一行一个整数，表示 $n(2\le n\le 100)$。

第二行 $n$ 个整数 $a_1,a_2,\cdots a_n(1\le a_i\le 
10^4)$。

## 输出格式

对于每组数据，如果有解，第一行输出 `Yes`，否则第一行输出 `No`。大小写不敏感。

如果有解，你需要输出第二行表示一种方案，为空格隔开的 $n$ 个数字，第 $i$ 个数字为 $1$ 表示 $a_i$ 被划分到 $B$ 中，为 $2$ 则表示 $a_i$ 被划分到 $C$ 中。你需要保证 $1$ 和 $2$ 都至少出现一次。

如果有多种合法方案，输出任意一种均可。

## 说明/提示

第一组数据的输出中，$B=(51,9),C=(1,20)$。$\gcd(B_1,B_2)=3\ne1=\gcd(C_1,C_2)$。

对于第二组数据，没有合法的方案。存在方案 $B=(5,5,5),C=(5)$，但是 $\gcd(B_1,B_2,B_3)=5=\gcd(C_1)$，所以此方案非法。

By chenxi2009

## 样例 #1

### 输入

```
3
4
1 20 51 9
4
5 5 5 5
3
1 2 2
```

### 输出

```
Yes
2 2 1 1
No
Yes
1 2 2
```



---

---
title: "Shashliks"
layout: "post"
diff: 普及-
pid: CF2113A
tag: ['数学', '贪心']
---

# Shashliks

## 题目描述

You are the owner of a popular shashlik restaurant, and your grill is the heart of your kitchen. However, the grill has a peculiarity: after cooking each shashlik, its temperature drops.

You need to cook as many portions of shashlik as possible, and you have an unlimited number of portions of two types available for cooking:

- The first type requires a temperature of at least $ a $ degrees at the start of cooking, and after cooking, the grill's temperature decreases by $ x $ degrees.
- The second type requires a temperature of at least $ b $ degrees at the start of cooking, and after cooking, the grill's temperature decreases by $ y $ degrees.

Initially, the grill's temperature is $ k $ degrees. Determine the maximum total number of portions of shashlik that can be cooked.

Note that the grill's temperature can be negative.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains five integers $ k $ , $ a $ , $ b $ , $ x $ , and $ y $ ( $ 1 \le k, a, b, x, y \le 10^9 $ ) — the initial temperature of the grill, the required temperature for cooking the first and second types of shashlik, respectively, as well as the temperature drop after cooking the first and second types of shashlik, respectively.

## 输出格式

For each test case, output a single integer — the maximum number of portions of shashlik that you can cook.

## 说明/提示

In the first test case, it is advantageous to cook $ 7 $ portions of the second type of shashlik; after that, the grill's temperature will be $ 3 $ degrees, and we can cook one more portion of the first type of shashlik.

In the second test case, we cannot cook either type of shashlik because the grill is too cold.

In the fourth test case, it is advantageous to cook $ 8 $ portions of the first type of shashlik; after that, it will be possible to cook another $ 2 $ portions of the second type of shashlik.

## 样例 #1

### 输入

```
5
10 3 4 2 1
1 10 10 1 1
100 17 5 2 3
28 14 5 2 4
277 5 14 1 3
```

### 输出

```
8
0
46
10
273
```



---

---
title: "Good Start"
layout: "post"
diff: 普及-
pid: CF2113B
tag: ['数学', '构造']
---

# Good Start

## 题目描述

The roof is a rectangle of size $ w \times h $ with the bottom left corner at the point $ (0, 0) $ on the plane. Your team needs to completely cover this roof with identical roofing sheets of size $ a \times b $ , with the following conditions:

- The sheets cannot be rotated (not even by $ 90^\circ $ ).
- The sheets must not overlap (but they can touch at the edges).
- The sheets can extend beyond the boundaries of the rectangular roof.

A novice from your team has already placed two such sheets on the roof in such a way that the sheets do not overlap and each of them partially covers the roof.

Your task is to determine whether it is possible to completely tile the roof without removing either of the two already placed sheets.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains four integers $ w $ , $ h $ , $ a $ , and $ b $ ( $ 1 \le w, h, a, b \le 10^9 $ ) — the dimensions of the roof and the dimensions of the roofing sheets, respectively.

The second line of each test case contains four integers $ x_1 $ , $ y_1 $ , $ x_2 $ , and $ y_2 $ ( $ -a + 1 \le x_1, x_2 \le w - 1, -b + 1 \le y_1, y_2 \le h - 1 $ ) — the coordinates of the bottom left corners of the already placed roofing sheets. It is guaranteed that these sheets do not overlap.

## 输出格式

For each test case, output "Yes" (without quotes) if it is possible to completely tile the roof without removing either of the two already placed tiles, and "No" (without quotes) otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, it is possible to add $ 8 $ roofing sheets as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113B/93f36282728350193810dfbfa6e6dfdf291648d2.png)In the second test case, it is impossible to completely tile the roof:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113B/cebcd94b71d8b7130f37fb6e9fd22f74c727960b.png)

## 样例 #1

### 输入

```
7
6 5 2 3
-1 -2 5 4
4 4 2 2
0 0 3 1
10 9 3 2
0 0 4 3
10 9 3 2
0 0 6 3
5 5 2 2
-1 -1 4 -1
5 5 2 2
-1 -1 2 3
7 8 2 4
0 0 0 5
```

### 输出

```
Yes
No
No
Yes
No
Yes
No
```



---

---
title: "Gellyfish and Baby's Breath"
layout: "post"
diff: 普及-
pid: CF2116B
tag: ['数学', '贪心']
---

# Gellyfish and Baby's Breath

## 题目描述

Flower gives Gellyfish two permutations $ ^{\text{∗}} $ of $ [0, 1, \ldots, n-1] $ : $ p_0, p_1, \ldots, p_{n-1} $ and $ q_0, q_1, \ldots, q_{n-1} $ .

Now Gellyfish wants to calculate an array $ r_0,r_1,\ldots,r_{n-1} $ through the following method:

- For all $ i $ ( $ 0 \leq i \leq n-1 $ ), $ r_i = \max\limits_{j=0}^{i} \left(2^{p_j} + 2^{q_{i-j}} \right) $

But since Gellyfish is very lazy, you have to help her figure out the elements of $ r $ .

Since the elements of $ r $ are very large, you are only required to output the elements of $ r $ modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The second line of each test case contains $ n $ integers $ p_0, p_1, \ldots,p_{n-1} $ ( $ 0 \leq p_i < n $ ).

The third line of each test case contains $ n $ integers $ q_0, q_1, \ldots,q_{n-1} $ ( $ 0 \leq q_i < n $ ).

It is guaranteed that both $ p $ and $ q $ are permutations of $ [0, 1, \ldots, n-1] $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ n $ integers $ r_0, r_1, \ldots, r_{n-1} $ in a single line, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case:

- $ r_0 = 2^{p_0} + 2^{q_0} = 1+2=3 $
- $ r_1 = \max(2^{p_0} + 2^{q_1}, 2^{p_1} + 2^{q_0}) = \max(1+4, 4+2) = 6 $
- $ r_2 = \max(2^{p_0} + 2^{q_2}, 2^{p_1}+2^{q_1}, 2^{p_2}+2^{q_0}) = (1+1, 4+4, 2+2) = 8 $

## 样例 #1

### 输入

```
3
3
0 2 1
1 2 0
5
0 1 2 3 4
4 3 2 1 0
10
5 8 9 3 4 0 2 7 1 6
9 5 1 4 0 3 2 8 7 6
```

### 输出

```
3 6 8 
17 18 20 24 32 
544 768 1024 544 528 528 516 640 516 768
```



---

---
title: "Retaliation"
layout: "post"
diff: 普及-
pid: CF2117D
tag: ['数学', '差分']
---

# Retaliation

## 题目描述

Yousef 想要使数组 $a_1, a_2,\dots, a_n$ 爆炸。当一个数组的所有元素均为 $0$ 时，它就会爆炸。

在一次操作中，Yousef 可以选择执行下列选项之一：

- 对 $a$ 中所有的下标 $i$，令 $a_i$ 自减 $i$。
- 对 $a$ 中所有的下标 $i$，令 $a_i$ 自减 $n-i+1$。

你的任务是帮助 Yousef 判断能否通过一系列操作使得数组爆炸。

## 输入格式

输入数据包含多个测试用例。输入数据的第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的个数。

对于每个测试用例：

- 第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示数组的长度。
- 第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 10^9$），表示数组中的元素。

输入数据保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果 Yousef 可以使数组爆炸，输出 `YES`，否则输出 `NO`。

你可以以任意大小写输出答案。例如，`yEs`，`yes`，`Yes`，`YES` 都会被视为肯定回答。

## 说明/提示

对于第二个测试用例，我们可以进行如下操作：

- 进行 $1$ 次第一种操作，数组变为 $[20,16,12,8,4]$。
- 进行 $4$ 次第二种操作，数组变为 $[0,0,0,0,0]$。

对于第一、第三、第四、第六个测试用例，可以证明无法通过任何操作使得数组的元素全部变为零。

## 样例 #1

### 输入

```
6
4
3 6 6 3
5
21 18 15 12 9
10
2 6 10 2 5 5 1 2 4 10
7
10 2 16 12 8 20 4
2
52 101
2
10 2
```

### 输出

```
NO
YES
NO
NO
YES
NO
```



---

---
title: "Lucky Permutation Triple"
layout: "post"
diff: 普及-
pid: CF303A
tag: ['数学', '数论']
---

# Lucky Permutation Triple

## 题目描述

Bike is interested in permutations. A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ is not.

A permutation triple of permutations of length $ n $ $ (a,b,c) $ is called a Lucky Permutation Triple if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/bd0aa9c2cfa6e7dfc9681d8813c19703f16dbc42.png). The sign $ a_{i} $ denotes the $ i $ -th element of permutation $ a $ . The modular equality described above denotes that the remainders after dividing $ a_{i}+b_{i} $ by $ n $ and dividing $ c_{i} $ by $ n $ are equal.

Now, he has an integer $ n $ and wants to find a Lucky Permutation Triple. Could you please help him?

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ .

## 输出格式

If no Lucky Permutation Triple of length $ n $ exists print -1.

Otherwise, you need to print three lines. Each line contains $ n $ space-seperated integers. The first line must contain permutation $ a $ , the second line — permutation $ b $ , the third — permutation $ c $ .

If there are multiple solutions, print any of them.

## 说明/提示

In Sample 1, the permutation triple $ ([1,4,3,2,0],[1,0,2,4,3],[2,4,0,1,3]) $ is Lucky Permutation Triple, as following holds:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/6124807a627fcd49ae8fab0d91c9fa90239af12b.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/598c5f3180986ca384de6df51e7cb84d8ea4e757.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/66b44a153ea212b6a13d195278ac6715ce383457.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/dd4f61ae15bc4151613d0da9fe47b466aa949e1e.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/0ea0fc069d3b3e3451d396fd4b6ef6f3d9456398.png).

In Sample 2, you can easily notice that no lucky permutation triple exists.

## 样例 #1

### 输入

```
5

```

### 输出

```
1 4 3 2 0
1 0 2 4 3
2 4 0 1 3

```

## 样例 #2

### 输入

```
2

```

### 输出

```
-1

```



---

---
title: "The Wall"
layout: "post"
diff: 普及-
pid: CF340A
tag: ['数学']
---

# The Wall

## 题目描述

Iahub and his friend Floyd have started painting a wall. Iahub is painting the wall red and Floyd is painting it pink. You can consider the wall being made of a very large number of bricks, numbered $ 1 $ , $ 2 $ , $ 3 $ and so on.

Iahub has the following scheme of painting: he skips $ x-1 $ consecutive bricks, then he paints the $ x $ -th one. That is, he'll paint bricks $ x $ , $ 2·x $ , $ 3·x $ and so on red. Similarly, Floyd skips $ y-1 $ consecutive bricks, then he paints the $ y $ -th one. Hence he'll paint bricks $ y $ , $ 2·y $ , $ 3·y $ and so on pink.

After painting the wall all day, the boys observed that some bricks are painted both red and pink. Iahub has a lucky number $ a $ and Floyd has a lucky number $ b $ . Boys wonder how many bricks numbered no less than $ a $ and no greater than $ b $ are painted both red and pink. This is exactly your task: compute and print the answer to the question.

## 输入格式

The input will have a single line containing four integers in this order: $ x $ , $ y $ , $ a $ , $ b $ . ( $ 1<=x,y<=1000 $ , $ 1<=a,b<=2·10^{9} $ , $ a<=b $ ).

## 输出格式

Output a single integer — the number of bricks numbered no less than $ a $ and no greater than $ b $ that are painted both red and pink.

## 说明/提示

Let's look at the bricks from $ a $ to $ b $ $ (a=6,b=18) $ . The bricks colored in red are numbered 6, 8, 10, 12, 14, 16, 18. The bricks colored in pink are numbered 6, 9, 12, 15, 18. The bricks colored in both red and pink are numbered with 6, 12 and 18.

## 样例 #1

### 输入

```
2 3 6 18

```

### 输出

```
3
```



---

---
title: "Tricky Sum"
layout: "post"
diff: 普及-
pid: CF598A
tag: ['数学', '枚举']
---

# Tricky Sum

## 题目描述

In this problem you are to calculate the sum of all integers from $ 1 $ to $ n $ , but you should take all powers of two with minus in the sum.

For example, for $ n=4 $ the sum is equal to $ -1-2+3-4=-4 $ , because $ 1 $ , $ 2 $ and $ 4 $ are $ 2^{0} $ , $ 2^{1} $ and $ 2^{2} $ respectively.

Calculate the answer for $ t $ values of $ n $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1<=t<=100 $ ) — the number of values of $ n $ to be processed.

Each of next $ t $ lines contains a single integer $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Print the requested sum for each of $ t $ integers $ n $ given in the input.

## 说明/提示

The answer for the first sample is explained in the statement.

## 样例 #1

### 输入

```
2
4
1000000000

```

### 输出

```
-4
499999998352516354

```



---

---
title: "Infinite Sequence"
layout: "post"
diff: 普及-
pid: CF622A
tag: ['模拟', '数学']
---

# Infinite Sequence

## 题目描述

Consider the infinite sequence of integers: $ 1,1,2,1,2,3,1,2,3,4,1,2,3,4,5... $ . The sequence is built in the following way: at first the number $ 1 $ is written out, then the numbers from $ 1 $ to $ 2 $ , then the numbers from $ 1 $ to $ 3 $ , then the numbers from $ 1 $ to $ 4 $ and so on. Note that the sequence contains numbers, not digits. For example number $ 10 $ first appears in the sequence in position $ 55 $ (the elements are numerated from one).

Find the number on the $ n $ -th position of the sequence.

## 输入格式

The only line contains integer $ n $ ( $ 1<=n<=10^{14} $ ) — the position of the number to find.

Note that the given number is too large, so you should use $ 64 $ -bit integer type to store it. In C++ you can use the long long integer type and in Java you can use long integer type.

## 输出格式

Print the element in the $ n $ -th position of the sequence (the elements are numerated from one).

## 样例 #1

### 输入

```
3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
10

```

### 输出

```
4

```

## 样例 #4

### 输入

```
55

```

### 输出

```
10

```

## 样例 #5

### 输入

```
56

```

### 输出

```
1

```



---

---
title: "Exponential notation"
layout: "post"
diff: 普及-
pid: CF691C
tag: ['模拟', '数学']
---

# Exponential notation

## 题目描述

You are given a positive decimal number $ x $ .

Your task is to convert it to the "simple exponential notation".

Let $ x=a·10^{b} $ , where $ 1<=a&lt;10 $ , then in general case the "simple exponential notation" looks like "aEb". If $ b $ equals to zero, the part "Eb" should be skipped. If $ a $ is an integer, it should be written without decimal point. Also there should not be extra zeroes in $ a $ and $ b $ .

## 输入格式

The only line contains the positive decimal number $ x $ . The length of the line will not exceed $ 10^{6} $ . Note that you are given too large number, so you can't use standard built-in data types "float", "double" and other.

## 输出格式

Print the only line — the "simple exponential notation" of the given number $ x $ .

## 样例 #1

### 输入

```
16

```

### 输出

```
1.6E1

```

## 样例 #2

### 输入

```
01.23400

```

### 输出

```
1.234

```

## 样例 #3

### 输入

```
.100

```

### 输出

```
1E-1

```

## 样例 #4

### 输入

```
100.

```

### 输出

```
1E2

```



---

---
title: "Pineapple Incident"
layout: "post"
diff: 普及-
pid: CF697A
tag: ['模拟', '数学', '枚举']
---

# Pineapple Incident

## 题目描述

Ted有一个菠萝。这个菠萝可以像狗一样叫！在第 $t$ 秒它第一次叫。然后每隔 $s$ 秒之后它会叫一次，在叫这一次之后还会在后一秒再叫一次。意思就是说它会在 $t$ 秒，$t+s$ 秒，$t+s+1$ 秒，$t+2s$ 秒，$t+2s+1$ 秒分别叫一次，以此类推。 

Barney在早上醒来，他想吃个菠萝，但这只菠萝叫的时候Barney不能吃它。Barney打算在 $x$ 秒吃它，所以请你告诉Barney在x秒的时候，这个菠萝会不会叫。

## 输入格式

仅输入一行，输入 $t,s,x$($0\le t,x\le 10^9$，$2\leq s\leq 10^9$)分别为菠萝第一次叫的时间，叫的间隔以及Barney想吃的时间。

## 输出格式

如果菠萝要叫的话，输出YES，否则输出NO。

## 样例 #1

### 输入

```
3 10 4

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
3 10 3

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
3 8 51

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
3 8 52

```

### 输出

```
YES

```



---

---
title: "Tricky Alchemy"
layout: "post"
diff: 普及-
pid: CF912A
tag: ['模拟', '数学', '概率论']
---

# Tricky Alchemy

## 题目描述

During the winter holidays, the demand for Christmas balls is exceptionally high. Since it's already $ 2018 $ , the advances in alchemy allow easy and efficient ball creation by utilizing magic crystals.

Grisha needs to obtain some yellow, green and blue balls. It's known that to produce a yellow ball one needs two yellow crystals, green — one yellow and one blue, and for a blue ball, three blue crystals are enough.

Right now there are $ A $ yellow and $ B $ blue crystals in Grisha's disposal. Find out how many additional crystals he should acquire in order to produce the required number of balls.

## 输入格式

The first line features two integers $ A $ and $ B $ ( $ 0<=A,B<=10^{9} $ ), denoting the number of yellow and blue crystals respectively at Grisha's disposal.

The next line contains three integers $ x $ , $ y $ and $ z $ ( $ 0<=x,y,z<=10^{9} $ ) — the respective amounts of yellow, green and blue balls to be obtained.

## 输出格式

Print a single integer — the minimum number of crystals that Grisha should acquire in addition.

## 说明/提示

In the first sample case, Grisha needs five yellow and four blue crystals to create two yellow balls, one green ball, and one blue ball. To do that, Grisha needs to obtain two additional crystals: one yellow and one blue.

## 样例 #1

### 输入

```
4 3
2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 9
1 1 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
12345678 87654321
43043751 1000000000 53798715

```

### 输出

```
2147483648

```



---

---
title: "Splits"
layout: "post"
diff: 普及-
pid: CF964A
tag: ['数学', '贪心', '递归']
---

# Splits

## 题目描述

我们定义正整数$n$的分裂为一个由正整数组成的不上升序列，且序列数字和为$n$

举个栗子：下列这些序列都是$8$的分裂：$[4,4],[3,3,2],[2,2,1,1,1],[5,2,1]$

下列这些序列不是$8$的分裂：$[1,7],[5,4],[11,-3],[1,1,4,1,1]$

一个分裂的权是序列第一个数出现的次数，举个例子：$[1,1,1,1,1]$的权是$5$，$[5,5,3,3,3]$的权是$2$，$[9]$的权是$1$

现在给出$n$，求$n$的分裂有多少个不同的权

## 输入格式

第一行为$n(1\leq n \leq 10^9)$

## 输出格式

答案

## 样例 #1

### 输入

```
7

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8

```

### 输出

```
5

```

## 样例 #3

### 输入

```
9

```

### 输出

```
5

```



---

---
title: "Lara Croft and the New Game"
layout: "post"
diff: 普及-
pid: CF976B
tag: ['模拟', '数学']
---

# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 输入格式

The only line contains three integers $ n $ , $ m $ and $ k $ ( $ 2<=n,m<=10^{9} $ ,  $ n $ is always even, $ 0<=k<n·m $ ). Note that $ k $ doesn't fit into $ 32 $ -bit integer type!

## 输出格式

Print the cell (the row and the column where the cell is situated) where Lara ends up after she moves $ k $ times.

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0

```

### 输出

```
1 1

```

## 样例 #2

### 输入

```
4 3 11

```

### 输出

```
1 2

```

## 样例 #3

### 输入

```
4 3 7

```

### 输出

```
3 2

```



---

