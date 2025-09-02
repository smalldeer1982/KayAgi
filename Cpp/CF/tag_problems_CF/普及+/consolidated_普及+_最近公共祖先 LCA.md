---
title: "Fools and Roads"
layout: "post"
diff: 普及+/提高
pid: CF191C
tag: ['深度优先搜索 DFS', '最近公共祖先 LCA', '差分']
---

# Fools and Roads

## 题目描述

有一颗 $n$  个节点的树，$k$  次旅行，问每一条边被走过的次数。

## 输入格式

第一行一个整数 $n$  （$2\leq n\leq 10^5$ ）。

接下来 $n-1$  行，每行两个正整数 $x,y$  （$1\leq x,y\leq n,x\neq y$ ），表示 $x$  与 $y$  之间有一条连边。

接下来一个整数 $k$  （$0\leq k\leq 10^5$ ）。

接下来 $k$  行，每行两个正整数 $x,y$  （$1\leq x,y\leq n$ ），表示有一个从 $x$  到 $y$  的旅行。

## 输出格式

一行空格分隔的 $n - 1$ 个整数，按输入顺序输出每一条边被走过的次数。

Translated by @larryzhong

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
2
1 4
3 5

```

### 输出

```
2 1 1 1 

```

## 样例 #2

### 输入

```
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5

```

### 输出

```
3 1 1 1 

```



---

---
title: "Turtle and an Incomplete Sequence"
layout: "post"
diff: 普及+/提高
pid: CF1981C
tag: ['贪心', '最近公共祖先 LCA']
---

# Turtle and an Incomplete Sequence

## 题目描述

Turtle was playing with a sequence $ a_1, a_2, \ldots, a_n $ consisting of positive integers. Unfortunately, some of the integers went missing while playing.

Now the sequence becomes incomplete. There may exist an arbitrary number of indices $ i $ such that $ a_i $ becomes $ -1 $ . Let the new sequence be $ a' $ .

Turtle is sad. But Turtle remembers that for every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ a_i = \left\lfloor\frac{a_{i + 1}}{2}\right\rfloor $ or $ a_{i + 1} = \left\lfloor\frac{a_i}{2}\right\rfloor $ holds for the original sequence $ a $ .

Turtle wants you to help him complete the sequence. But sometimes Turtle makes mistakes, so you need to tell him if you can't complete the sequence.

Formally, you need to find another sequence $ b_1, b_2, \ldots, b_n $ consisting of positive integers such that:

- For every integer $ i $ from $ 1 $ to $ n $ , if $ a'_i \ne -1 $ , then $ b_i = a'_i $ .
- For every integer $ i $ from $ 1 $ to $ n - 1 $ , either $ b_i = \left\lfloor\frac{b_{i + 1}}{2}\right\rfloor $ or $ b_{i + 1} = \left\lfloor\frac{b_i}{2}\right\rfloor $ holds.
- For every integer $ i $ from $ 1 $ to $ n $ , $ 1 \le b_i \le 10^9 $ .

If there is no sequence $ b_1, b_2, \ldots, b_n $ that satisfies all of the conditions above, you need to report $ -1 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the length of the sequence.

The second line of each test case contains $ n $ integers $ a'_1, a'_2, \ldots, a'_n $ ( $ a'_i = -1 $ or $ 1 \le a'_i \le 10^8 $ ) — the elements of the sequence $ a' $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if there is no sequence $ b_1, b_2, \ldots, b_n $ that satisfies all of the conditions, output a single integer $ -1 $ .

Otherwise, output $ n $ integers $ b_1, b_2, \ldots, b_n $ — the elements of the sequence $ b_1, b_2, \ldots, b_n $ you find. The sequence should satisfy that $ 1 \le b_i \le 10^9 $ for every integer $ i $ from $ 1 $ to $ n $ . If there are multiple answers, print any of them.

## 说明/提示

In the first test case, $ [4, 2, 1, 2, 1, 2, 1, 3] $ can also be the answer, while $ [4, 2, 5, 10, 5, 2, 1, 3] $ and $ [4, 2, 1, 2, 1, 2, 1, 4] $ cannot.

In the second test case, $ [1, 2, 5, 2] $ can also be the answer.

From the fourth to the sixth test cases, it can be shown that there is no answer, so you should output $ -1 $ .

## 样例 #1

### 输入

```
9
8
-1 -1 -1 2 -1 -1 1 -1
4
-1 -1 -1 -1
6
3 -1 -1 -1 9 -1
4
-1 5 -1 6
4
2 -1 -1 3
4
1 2 3 4
2
4 2
5
-1 3 -1 3 6
13
-1 -1 3 -1 -1 -1 -1 7 -1 -1 3 -1 -1
```

### 输出

```
4 9 4 2 4 2 1 2
7 3 6 13
3 1 2 4 9 18
-1
-1
-1
4 2
6 3 1 3 6
3 1 3 1 3 7 3 7 3 1 3 1 3
```



---

---
title: "Knights"
layout: "post"
diff: 普及+/提高
pid: CF33D
tag: ['枚举', '最近公共祖先 LCA']
---

# Knights

## 题目描述

伯兰国不得不又一次面对黑♂暗势力的降临。邪恶领主~~Van♂De♂Mart~~范·德·马特正在计划征服整个王国。王国成立了由伯兰国王瓦莱丽领导的理事会。理事会由$n$个骑士组成。经过一番激烈的讨论，他们把整个国家分成了$n$个战略目标点，（如果黑暗势力控制了至少一个战略目标点，战争就失败了）

伯兰国可以被认为是由$m+1$个区域和$m$个栅栏组成的。同时，从一个区域到达另一个区域的唯一方法就是翻过栅栏。每个栅栏都是同一个平面上的圆，并且任意两个栅栏之间都没有交叉点，同时保证所有战略目标点都`不在`栅栏上。我们会给你$k$对整数$ai, bi$，对于每对整数，你都要解决：如果一个骑士想从战略控制点$ai$赶到$bi$，（为了防止范·德·马特突袭控制点bi），而每个骑士都骑着一匹马（把马从栅栏上扔过去太难了），那么，他最少爬过多少栅栏？

## 输入格式

第一行是两个正整数$n,m$（$1 ≤ n,m ≤ 1000$， $0 ≤ k ≤ 10000$）接下来$n$行， 两个数，$Kx_i, Ky_i$，（$-1 * 10^9 ≤ Kx_i, Ky_i ≤ 1 * 10^9$）描述第$i$个控制点的坐标。

接下来$m$行，每行描述一个栅栏，一个栅栏有三个参数，$r_i, Cx_i, Cy_i$分别表示这个栅栏的直径和坐标。（$-1 * 10^9 ≤ Cx_i, Cy_i ≤ 1 * 10^9$， $1 ≤ r_i ≤ 1 * 10^9$）

在接下来$k$行，每行两个整数，第$n+m+j$行表示$a_i$，$b_i$，（意义前面已经说了）

## 输出格式

正好k行，每行一个整数，对这$k$次询问的答案

_翻译 By 的卢_

## 样例 #1

### 输入

```
2 1 1
0 0
3 3
2 0 0
1 2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 3 1
0 0
4 4
1 0 0
2 0 0
3 0 0
1 2

```

### 输出

```
3

```



---

